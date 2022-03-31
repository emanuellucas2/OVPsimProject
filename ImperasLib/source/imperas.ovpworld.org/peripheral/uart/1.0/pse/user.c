/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdio.h>
#include <ctype.h>

#include "pse.igen.h"

#define PREFIX "16550"

// Default frequency of UART Reference clock
#define DEFAULT_REF_CLK_FREQ 18432000

// Maximum FIFO depth supported
#define MAXFIFO 128

// Default fifo depth
#define DEFAULT_FIFO_SIZE   16

// Enum to track currently active interrupts
typedef enum {
    INT_NONE           = 0x0,
    INT_RX_LINE_STATUS = 0x1,
    INT_RX_DATA_AVAIL  = 0x2,
    INT_TX_EMPTY       = 0x4
} intStateE;

struct {
    intStateE intState;         // Current state for the interrupt line
    Int32     channel;          // Serial channel returned by bhmSerOpenAuto()
    Uns32     baudDelay;        // Baud rate delay in uSecs
    Uns32     refClkFreq;       // Clock freq used in baud rate calculations
    Uns32     fifoSize;         // Number of entries available in fifo
    Uns32     rxTrigLvl;        // Number of entries in Rx FIFO to trigger interrupt
    Uns32     txTrigLvl;        // Number of entries in Tx FIFO to trigger interrupt
    Uns16     divLatch;         // Value written to divisor Latch high/low
    Bool      noFifo;           // Run in 16450 mode (no Fifos)
    Bool      charMode;         // Run in Telnet char mode
    Bool      simulateBaud;     // Simulate baud rate delay
    Bool      overrunErr;       // Overrun error flag
    Bool      threInterrupt;    // Set when transmit holding reg empty interrupt is active
    Bool      writeError;       // An error has occurred on most recent write

    // Programmers view events
    bhmEventHandle  charOut;
    bhmEventHandle  charIn;     // Character received by UART
    bhmEventHandle  charRead;   // Char read from RBR
    bhmEventHandle  overrun;
    bhmEventHandle  interrupt;

} state = {
    .channel       = -1,
    .refClkFreq    = DEFAULT_REF_CLK_FREQ,
    .divLatch      = 1
};

typedef struct fifoBufferS {
    Uns8  buffer[MAXFIFO];   // fifo buffer
    Uns8  rdp, wrp;          // pointers to read and write points
    Bool  full, empty;       // flags when full or empty
} fifoBufferT, *fifoBufferP;

static fifoBufferT Rx, Tx;

///////////////////////////////
// Dummy Register structures //
///////////////////////////////
union {
    Uns8 value;
    struct {
        unsigned fifoEn : 1;
        unsigned fifoRcvrRst : 1;
        unsigned fifoXmitRst : 1;
        unsigned dmaModeSel : 1;
        unsigned fifoXmitTrig : 2;
        unsigned fifoRcvrTrig : 2;
    } bits;
} fcr;
union {
    Uns8 value;
    struct {
        unsigned dls : 2;
        unsigned stop : 1;
        unsigned pen : 1;
        unsigned eps : 1;
        unsigned stick : 1;
        unsigned brk : 1;
        unsigned dlab : 1;
    } bits;
} lcr;
union {
    Uns8 value;
    struct {
        unsigned erbfi : 1;
        unsigned etbei : 1;
        unsigned elsi : 1;
        unsigned edssi : 1;
    } bits;
} ier_dlh;
union {
    Uns8 value;
    struct {
        unsigned intid : 4;
        unsigned __pad4 : 2;
        unsigned fifoen : 2;
    } bits;
} iir;
union {
    Uns8 value;
    struct {
        unsigned dr : 1;
        unsigned oe : 1;
        unsigned pe : 1;
        unsigned fe : 1;
        unsigned bi : 1;
        unsigned thre : 1;
        unsigned temt : 1;
        unsigned rfe : 1;
    } bits;
} lsr;

/////////////////////
// BAUD RATE DELAY //
/////////////////////

// reference clock pre scale factor
#define PRESCALE 16

//
// extract register bits and calculate baud rate
//
static inline Uns32 data_bits   (void) { return (lcr.bits.dls + 5);      }
static inline Uns32 parity_bits (void) { return (lcr.bits.pen);          }
static inline Uns32 parity_sense(void) { return (lcr.bits.eps);          }
static inline Uns32 stop_bits   (void) { return (lcr.bits.stop ? 2 : 1); }
static inline Uns32 start_bits  (void) { return 1;                                      }

static inline Uns32 baud_rate   (void) { return state.refClkFreq / ((state.divLatch ?: 1)  * PRESCALE); }

static inline char  parity      (void) { return parity_bits() ? (parity_sense() ? 'E' : 'O') : 'N'; }

static inline Uns32 bits(void) {
    return start_bits() + data_bits() + parity_bits() + stop_bits();
}

static inline Uns32 microseconds_per_char(void) {
    return (bits() * 1000000) /  (baud_rate() ?: 1);
}

//
// Set the delay in uSec for the currently configured baud rate
//
static void setBaudDelay() {

    Uns32 oldDelay  = state.baudDelay;
    Uns32 newDelay  = microseconds_per_char() ?: 1;

    if (PSE_DIAG_LOW && (newDelay != oldDelay)) {
        bhmMessage(
            "I", PREFIX"_BRS",
            "baud rate=%d  parity=%c  data bits=%d  total bits=%d character delay=%dusec",
            baud_rate(),
            parity(),
            data_bits(),
            bits(),
            newDelay
        );
    }

    state.baudDelay = newDelay;

}

/////////////////////
// FIFO OPERATIONS //
/////////////////////

//
// Set the fifoSize, adjusting if out of range
//
static void setFifoSize(Uns32 size) {
    if (size > MAXFIFO) {
        bhmMessage(
            "W", PREFIX "_FTL",
            "Specified fifoSize=%d too large. Using max value %d",
            state.fifoSize,
            MAXFIFO
        );
        size = MAXFIFO;
    }
    state.fifoSize = size;
}

//
// Return size of the fifo
//
static Uns32 getFifoSize() {
    if (fcr.bits.fifoEn) {
        return state.fifoSize;
    } else {
        // FIFOs are not enabled, equivalent to one byte fifo
        return 1;
    }
}

//
// Reset the indicated fifo buffer
//
static void resetFifo(fifoBufferP fifo) {
    fifo->rdp = 0;
    fifo->wrp = 0;
    fifo->full = False;
    fifo->empty = True;
}

//
// Push element onto fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is full
//
static Bool pushFifo (fifoBufferP fifo, Uns8 value) {
    if (fifo->full) {
        return False;
    } else {
        fifo->buffer[fifo->wrp] = value;
        fifo->wrp = (fifo->wrp + 1) % getFifoSize();

        // Test for buffer now being full
        fifo->full  = (fifo->rdp == fifo->wrp);
        fifo->empty = False;

        return True;
    }
}

static Bool pushRxFifo(Uns8 value) {
    return pushFifo(&Rx, value);
}

static Bool pushTxFifo(Uns8 value) {
    return pushFifo(&Tx, value);
}

//
// View element on top of fifo buffer
// Return False if unable to complete because fifo is empty
//
static Bool viewFifo (fifoBufferP fifo, Uns8 *value) {
    if (fifo->empty) {
        return False;
    } else {
        *value = fifo->buffer[fifo->rdp];
        return True;
    }
}

//
// Pop element from fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is empty
//
static Bool popFifo (fifoBufferP fifo, Uns8 *value) {

    if (!viewFifo(fifo, value)) {

        return False;

    } else {

        fifo->rdp = (fifo->rdp + 1) % getFifoSize();

        // Test for buffer now being empty
        fifo->empty = (fifo->rdp == fifo->wrp);
        fifo->full  = False;

        return True;
    }
}

//
// Return number of entries in the fifo
//
static Uns32 getFifoCount(fifoBufferP fifo) {

    Uns32 size = getFifoSize();

    if (fifo->full) {
        return size;
    } else if (fifo->empty) {
        return 0;
    } else if (fifo->wrp < fifo->rdp) {
        return (size - fifo->rdp + fifo->wrp);
    } else {
        return(fifo->wrp - fifo->rdp);
    }
}

////////////////
// INTERRUPTS //
////////////////

//
// Is the Tx fifo at a level that should trigger an interrupt?
//
static inline Bool txTrigger() {

    Uns32 fifoCount = getFifoCount(&Tx);

    if (fcr.bits.fifoEn) {
        // When in fifo mode, indicate if trigger level has been reached
        return fifoCount <= state.txTrigLvl;
    } else {
        // When not in fifo mode just indicate if tx is empty
        return fifoCount == 0;
    }
}


//
// Is the Rx fifo at a level that should trigger an interrupt?
//
static inline Bool rxTrigger() {

    Uns32 fifoCount = getFifoCount(&Rx);

    if (fcr.bits.fifoEn && (state.rxTrigLvl != 0)) {
        // When in fifo mode, indicate if trigger level has been reached
        return fifoCount >= state.rxTrigLvl;
    } else {
        // When not in fifo mode just indicate if any data is available
        return fifoCount > 0;
    }
}

//
// update interrupt line based on current state
//
static intStateE getInterruptState() {

    intStateE intState = INT_NONE;

    if (ier_dlh.bits.elsi && state.overrunErr) {
        intState |= INT_RX_LINE_STATUS;
    }
    if (ier_dlh.bits.etbei && state.threInterrupt) {
        intState |= INT_TX_EMPTY;
    }
    // TODO: Based on the 16550 specification, this test should use rxTrigger()
    //       but Linux does not work when implemented this way!
    //if (ier_dlh.bits.erbfi && rxTrigger()) {
    if (ier_dlh.bits.erbfi && !Rx.empty) {
        intState |= INT_RX_DATA_AVAIL;
    }

    return intState;

}

//
// Change interrupt line according to newState
//
static void writeInterrupt(intStateE newState) {

    // Only update if interrupt changes from set to clear or clear to set
    if ((state.intState==INT_NONE) != (newState==INT_NONE)) {

        Bool intActive = (newState != INT_NONE);

        if (handles.intOut) {

            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_SI",
                    "%s interrupt @ %0.0fuS",
                    intActive ? "Setting " : "Clearing",
                    bhmGetCurrentTime()
                );
            }

            if (intActive) {
                bhmTriggerEvent(state.interrupt);
            }
            ppmWriteNet(handles.intOut, intActive);

        }
    }

    // Save interrupt state
    state.intState = newState;

}

static void reportIntState(intStateE intState) {
    if (intState != INT_NONE) {
        bhmMessage(
            "I", PREFIX "_AI",
            "Uart active interrupts:%s%s%s",
            intState & INT_RX_LINE_STATUS ? " LineStatus"  : "",
            intState & INT_RX_DATA_AVAIL  ? " RxDataAvail" : "",
            intState & INT_TX_EMPTY       ? " TxEmpty"     : ""
        );
    }
}

//
// update interrupt line based on current state
//
static void updateInterrupt() {

    intStateE newState = getInterruptState();

    if ((newState != state.intState)) {
        if (PSE_DIAG_HIGH) {
            reportIntState(newState);
        }
        writeInterrupt(newState);
    }
}

/////////////////////
// SERIAL DATA I/O //
/////////////////////

//
// Write data to the channel
// return 0 if channel is not available
//
static Int32 writeOutput(Uns8 *buffer, Uns32 length) {

    int rc = 0;

    if (state.channel >= 0) {

        rc = bhmSerWriteN(state.channel, buffer, length);

        if (rc != length) {
            if (!state.writeError) {
                bhmMessage("W", PREFIX"_CWE", "Serial channel write error (%u). Channel closed?", bhmSerLastError(state.channel));
                state.writeError = True;
            }
        } else {
            state.writeError = False;
        }
    }

    return rc;

}

//
// This continuously runs in its own thread,
// checking for data from the serial channel
// and placing data that is read into the rx fifo
//
//
static void channelReadThread(void *user) {

    while (1) {

        // Blocking read - thread will be blocked until input data is available
        Uns8  buffer[256];
        Uns32 bytes = bhmSerReadB(state.channel, buffer, sizeof(buffer)-1);

        if (PSE_DIAG_HIGH) {
            bhmMessage(
                "I", PREFIX"_RSD",
                "%d bytes received from serial channel",
                bytes
            );
        }

        // Process data, simulating baud rate delays if indicated
        Uns32 i;
        for (i = 0; i < bytes; i++) {

            char c = buffer[i];

            if (state.charMode && (c==0)) {

                // Ignore NULL chars in character mode
                // TODO: This was in 16450 model, not sure why - see if it can be removed
                if (PSE_DIAG_HIGH) {
                    bhmMessage(
                        "I", PREFIX"_NCI",
                        "Read of 0 ignored in char mode"
                    );
                }

            } else {

                if (state.simulateBaud) {
                    // Simulate the currently set baud rate delay
                    bhmWaitDelay(state.baudDelay);
                }

                // Push character onto fifo
                pushRxFifo(c);

                if (PSE_DIAG_HIGH) {
                    bhmMessage(
                        "I", PREFIX "_URS",
                        "Uart read data ready: 0x%02x ('%c') @ %0.0fuS%s",
                        c, isprint(c) ? c : ' ',
                        bhmGetCurrentTime(),
                        Rx.full ? " (RX now full)" : ""
                    );
                }

                // Trigger charIn event on each character read
                bhmTriggerEvent(state.charIn);

                // Update based on new state of fifo
                updateInterrupt();

                if (!state.simulateBaud && Rx.full) {
                    // When not simulating baud rate delays, when fifo fills up wait until
                    // character is read before getting anymore data from serial channel
                    bhmWaitEvent(state.charRead);
                }
            }
        }
    }
}

//
// Write tx data fifo to serial output channel if transmitter is enabled
//
static void putChars() {

    Uns8 c;
    while (popFifo(&Tx, &c)) {
        bhmTriggerEvent(state.charOut);
        writeOutput(&c, 1);
        state.threInterrupt = txTrigger();
        updateInterrupt();
    }
}

//////////////////////////
// SZ REGISTER //
//////////////////////////

PPM_REG_READ_CB(readSZ) {
    Uns32 fifoCount = getFifoCount(&Rx);

    return fifoCount;
}

//////////////////////////
// RBR_THR_DLL REGISTER //
//////////////////////////

//
// When LCR.DLAB=0: Transmitter Holding Register write - push data on fifo and
//                  write fifo data to serial channel if in serial mode
// When LCR.DLAB=1: Divisor Latch Low write
//
PPM_REG_WRITE_CB(writeTHR_DLL) {

    if (lcr.bits.dlab) {

        state.divLatch  = (state.divLatch & 0xff00) | (data & 0xff);
        setBaudDelay();

    } else {

        Uns8 c = data & 0xff;

        bport1_ab_data.thr_dll.value = c;

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX "_UWR",
                "Write to Data register: data=0x%02x ('%c')",
                c, isprint(c) ? c : ' '
            );
        }

        if (Tx.full) {

            // Transmitter overflow - indicates a program error
            bhmMessage(
                "W", PREFIX "_TOF",
                "Transmitter overflow: Write when transmitter full - data=0x%02x ('%c') lost",
                c, isprint(c) ? c : ' '
            );

        } else {

            pushTxFifo(c);
            updateInterrupt();
            putChars();

        }
    }
}

//
// View the THR_DLL write register
//   Return last value written to register
//   lcr.dlab determines if THE or DLL is currentl active
//
PPM_REG_VIEW_CB(viewTHR_DLL) {

    if (lcr.bits.dlab) {

        *(Uns8 *)data = state.divLatch & 0xff;

    } else {

        // Return last value written to thr
        *(Uns8 *)data = bport1_ab_data.thr_dll.value;

    }
}

//
// When LCR.DLAB=0: Receiver Buffer Register read - pop data off fifo
// When LCR.DLAB=1: Divisor Latch Low read
//
PPM_REG_READ_CB(readRBR_DLL) {

    if (lcr.bits.dlab) {

        return state.divLatch & 0xff;

    } else {

        Uns8 c = 0;

        popFifo(&Rx, &c);

        if (PSE_DIAG_HIGH) {
            bhmMessage(
                "I", PREFIX "_UR",
                "Read from Data register:0x%02x ('%c')%s",
                c, isprint(c) ? c : ' ',
                Rx.empty ? " (RX now empty)" : ""
            );
        }

        // Trigger charRead event on each character read
        bhmTriggerEvent(state.charRead);

        updateInterrupt();

        bport1_ab_data.rbr_dll.value = c;
        return c;

    }
}

//
// View the RBR_DLL read register - must form value when read
//
PPM_REG_VIEW_CB(viewRBR_DLL) {

    if (lcr.bits.dlab) {

        *(Uns8 *)data = state.divLatch & 0xff;

    } else {

        // Return character on top of fifo if any,
        // otherwise return last value read
        if (!viewFifo(&Rx, (Uns8 *)data)) {
            *(Uns8 *)data = bport1_ab_data.rbr_dll.value;
        }
    }
}

#if 0
//////////////////////
// IER_DLH Register //
//////////////////////

//
// When LCR.DLAB=0: Interrupt Enable Register
// When LCR.DLAB=1: Divisor Latch High write
//
PPM_REG_WRITE_CB(writeIER_DLH) {

    if (lcr.bits.dlab) {

        state.divLatch  = (state.divLatch & 0xff) | ((data & 0xff) << 8);
        setBaudDelay();

    } else {

        Bool etbeiOld = ier_dlh.bits.etbei;

        ier_dlh.value = data & 0x0f;

        if (!etbeiOld && ier_dlh.bits.etbei) {
            // Reset threInterrupt when that interrupt is enabled
            state.threInterrupt = txTrigger();
        }

        updateInterrupt();

    }
}

//
// When LCR.DLAB=0: Interrupt Enable Register read
// When LCR.DLAB=1: Divisor Latch High read
//
static Uns8 getIerDlh() {

    if (lcr.bits.dlab) {

        return (state.divLatch >> 8) & 0xff;

    } else {

        return ier_dlh.value;

    }
}

PPM_REG_VIEW_CB(viewIER_DLH) {
    *(Uns8 *)data = getIerDlh();
}

PPM_REG_READ_CB(readIER_DLH) {
    return getIerDlh();
}

//////////////////
// IIR Register //
//////////////////

// Values for the IIR intid field
#define INT_ID_MODEM_STATUS   0x0
#define INT_ID_NO_INT         0x1
#define INT_TD_TX_EMPTY       0x2
#define INT_ID_RX_DATA_AVAIL  0x4
#define INT_ID_RX_LINE_STATUS 0x6
#define INT_ID_CHAR_TIMEOUT   0xc

static Uns8 getIir() {

    intStateE intState = state.intState;

    // set interrupt id field according to flags in current
    // interrupt state, checking from highest to lowest priority
    if (intState & INT_RX_LINE_STATUS) {
        iir.bits.intid = INT_ID_RX_LINE_STATUS;
    } else if (intState & INT_RX_DATA_AVAIL) {
        iir.bits.intid = INT_ID_RX_DATA_AVAIL;
    } else if (intState & INT_TX_EMPTY) {
        iir.bits.intid = INT_TD_TX_EMPTY;
    } else {
        iir.bits.intid = INT_ID_NO_INT;
    }

    // both bits of fifoen field set when fifos are enabled
    if (fcr.bits.fifoEn) {
        iir.bits.fifoen |= 0x3;
    }

    return iir.value;

}

PPM_REG_READ_CB(readIIR) {

    Uns8 iir =  getIir();

    // Reading IIR clears transmitter holding register empty interrupt
    if (!artifactAccess && state.threInterrupt) {
        state.threInterrupt = False;
        updateInterrupt();
    }

    return iir;

}

PPM_REG_VIEW_CB(viewIIR) {
    *(Uns32*)data = getIir();
}

//////////////////
// LCR Register //
//////////////////

PPM_REG_WRITE_CB(writeLCR) {

    Uns8 oldLcr = lcr.value;

    lcr.value = data;

    if (lcr.value != oldLcr) {
        setBaudDelay();
    }
}

//////////////////
// FCR Register //
//////////////////

PPM_REG_WRITE_CB(writeFCR) {

    if (state.noFifo) {

        // Ignore writes to FCR when in 16440 mode

    } else {

        Bool oldFifoEn = fcr.bits.fifoEn;

        fcr.value = (data & 0xcf);

        Bool newFifoEn     = fcr.bits.fifoEn;
        Bool enableChanged = (oldFifoEn != newFifoEn);

        // Reset fifo when enable changes or corresponding reset bit is set
        if (enableChanged || fcr.bits.fifoRcvrRst) {
            fcr.bits.fifoRcvrRst = 0;    // self clearing bit
            resetFifo(&Rx);
        }
        if (enableChanged || fcr.bits.fifoXmitRst) {
            fcr.bits.fifoXmitRst = 0;    // self clearing bit
            resetFifo(&Tx);
        }

        // Set trigger level
        if (newFifoEn) {
            Uns32 size = getFifoSize();
            switch (fcr.bits.fifoRcvrTrig) {
                case 0: state.rxTrigLvl = 1;         break;
                case 1: state.rxTrigLvl = size >> 2; break;
                case 2: state.rxTrigLvl = size >> 1; break;
                case 3: state.rxTrigLvl = size  - 2; break;
                default: bhmMessage("F", PREFIX, "fifoRcvrTrig out of range"); // LCOV_EXCL_LINE
            }
            switch (fcr.bits.fifoXmitTrig) {
                case 0: state.txTrigLvl = 0;         break;
                case 1: state.txTrigLvl = 2;         break;
                case 2: state.txTrigLvl = size >> 2; break;
                case 3: state.txTrigLvl = size >> 1; break;
                default: bhmMessage("F", PREFIX, "fifoRcvrTrig out of range"); // LCOV_EXCL_LINE
            }
        } else {
            state.rxTrigLvl = 0;
            state.txTrigLvl = 0;
        }

        updateInterrupt();

    }
}

//////////////////
// LSR Register //
//////////////////

static Uns8 getLsr() {

    lsr.value = 0;
    lsr.bits.dr   = !Rx.empty;
    lsr.bits.oe   = state.overrunErr;
    lsr.bits.thre = Tx.empty;
    lsr.bits.temt = Tx.empty;

    return lsr.value;

}

PPM_REG_VIEW_CB(viewLSR) {
    *(Uns32*)data = getLsr();
}

PPM_REG_READ_CB(readLSR) {

    Uns8 lsr =  getLsr();

    // Reading LSR clears errors
    if (!artifactAccess && state.overrunErr) {
        state.overrunErr = False;
        updateInterrupt();
    }

    return lsr;
}
#endif

///////////////
// RESET NET //
///////////////

PPM_NET_CB(resetCB) {
    if (PSE_DIAG_LOW) {
        bhmMessage(
            "I", PREFIX "_RNC",
            "Reset net set to %d",
            (Uns32)value
        );
    }
    reset_Reset(value, NULL);
    updateInterrupt();
}

////////////////////
// INITIALIZATION //
////////////////////

static void initFifos() {

    bhmBoolParamValue("uart16450", &state.noFifo);
    if (state.noFifo) {

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX"_NFM", "Running in 16450 mode (no FIFOs)");
        }

        setFifoSize(1);

    } else {

        Uns32 fifoSize = DEFAULT_FIFO_SIZE;
        bhmUns32ParamValue("fifoSize", &fifoSize);
        setFifoSize(fifoSize);

    }

    // Initialize the fifos
    resetFifo(&Rx);
    resetFifo(&Tx);

}

static void initEvents() {
    state.charOut   = bhmCreateNamedEvent("charOut",   "Uart character output event");
    state.charIn    = bhmCreateNamedEvent("charIn",    "Uart character input event");
    state.charRead  = bhmCreateNamedEvent("charRead",  "Uart character read event");
    state.overrun   = bhmCreateNamedEvent("overrun",   "Transmit or Receive overrun");
    state.interrupt = bhmCreateNamedEvent("interrupt", "Interrupt generated");
}

static void initBaudDelay() {

    bhmBoolParamValue("simulatebaud", &state.simulateBaud);
    if (state.simulateBaud && PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX"_STD", "Simulating transmission delays.");
    }

    // Override default refClkFreq if specified by user
    Uns32 newRefClock;
    if(bhmUns32ParamValue("refClkFreq",  &newRefClock)){
        state.refClkFreq = newRefClock;
    }

    // Set the baud delay
    setBaudDelay();

}

static void initCharMode() {

    Bool charMode;
    bhmBoolParamValue("charmode", &charMode);

    if (charMode) {

        state.charMode = True;

        bhmMessage(
            "I", PREFIX"_STC",
            "Sending Telnet commands to configure for character mode"
        );

        //
        // Issue Telnet Protocol Commands to configure for character mode
        // (Required for curses library to work for example)
        //
        // IAC WILL ECHO IAC WILL SUPPRESS_GO_AHEAD IAC WONT LINEMODE
        // 255  251    1 255  251                 3 255  252       34
        //
        Uns8 buffer[] = {255, 251, 1, 255, 251, 3, 255, 252, 34};

        if (bhmSerWriteN(state.channel, buffer, sizeof(buffer)) != sizeof(buffer)) {
            bhmMessage(
                "W", PREFIX"_TCE",
                "Error sending Telnet initialization string for charmode"
            );
        }
    }
}

static void init16550() {

    // Initialize the fifos
    initFifos();

    // Initialize events
    initEvents();

    // Initialize baud rate delay settings
    initBaudDelay();

    // Construct the model
    periphConstructor();

    // open channel and create read thread
    state.channel = bhmSerOpenAuto();
    bhmCreateThread(channelReadThread, NULL, "channelReadThread", 0);

    // Init char mode setting
    initCharMode();

    // Initialize the interrupt net
    writeInterrupt(INT_NONE);

}

PPM_CONSTRUCTOR_CB(constructor) {

    init16550();

}

PPM_DESTRUCTOR_CB(destructor) {

    if(state.channel >= 0) {
        bhmSerClose(state.channel);
    }

}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

