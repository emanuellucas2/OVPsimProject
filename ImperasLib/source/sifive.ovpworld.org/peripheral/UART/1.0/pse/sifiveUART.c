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

#include "pse.igen.h"

#define BPORT1 handles.bport1
#include "pse.macros.igen.h"

#include <ctype.h>

#ifndef PREFIX
#define PREFIX "UART"
#endif

#ifndef DEFAULT_REF_CLK_FREQ
// Default frequency of UART Reference clock
#define DEFAULT_REF_CLK_FREQ 33333333
#endif

#ifndef MAXFIFO
// Maximum FIFO depth supported
#define MAXFIFO 8
#endif

#ifndef DEFAULT_FIFO_SIZE
// Default fifo depth
#define DEFAULT_FIFO_SIZE   8
#endif

// Enum to track currently active interrupts
typedef enum {
    INT_NONE           = 0x0,
    INT_RX_DATA_AVAIL  = 0x1,
    INT_TX_EMPTY       = 0x2
} intStateE;

struct {
    intStateE intState;         // Current state for the interrupt line
    Int32     channel;          // Serial channel returned by bhmSerOpenAuto()
    Uns32     baudDelay;        // Baud rate delay in uSecs
    Uns32     refClkFreq;       // Clock freq used in baud rate calculations
    Uns32     fifoSize;         // Number of entries available in fifo
    Bool      charMode;         // Run in Telnet char mode
    Bool      simulateBaud;     // Simulate baud rate delay
    Bool      writeError;       // An error has occurred on most recent write

    // Programmers view events
    bhmEventHandle  charOut;
    bhmEventHandle  charIn;     // Character received by UART
    bhmEventHandle  charRead;   // Char read from rxdata
    bhmEventHandle  interrupt;

} state = {
    .channel       = -1,
    .refClkFreq    = DEFAULT_REF_CLK_FREQ,
    .baudDelay     = 8,
};

typedef struct fifoBufferS {
    Uns8  buffer[MAXFIFO];   // fifo buffer
    Uns8  rdp, wrp;          // pointers to read and write points
    Bool  full, empty;       // flags when full or empty
} fifoBufferT, *fifoBufferP;

static fifoBufferT Rx, Tx;

/////////////////////
// BAUD RATE DELAY //
/////////////////////

static inline Uns32 baud_rate   (void) { return state.refClkFreq / ((bport1_ab_data.div.bits.DIV) + 1); }

static inline Uns32 microseconds_per_char(void) {
    return (1000000 / baud_rate()) ?: 1;
}

//
// Thread handling functions
//
static void channelReadThread(void *user);

bhmThreadHandle rxThreadHandle = 0;

static void stopRxThread() {
    if (rxThreadHandle) {
        bhmDeleteThread(rxThreadHandle);
        rxThreadHandle = 0;
    }
}

static void startRxThread() {
    stopRxThread();
    rxThreadHandle = bhmCreateThread(channelReadThread, NULL, "channelReadThread", 0);
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
            "baud rate=%d  character delay=%dusec",
            baud_rate(),
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
        return state.fifoSize;
}

//
// Reset the indicated fifo buffer
//
static void resetFifo(fifoBufferP fifo) {
    fifo->rdp = 0;
    fifo->wrp = 0;
    fifo->full = False;
    fifo->empty = True;

    if (fifo == &Rx) {
        startRxThread();
    }
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
    return fifoCount < bport1_ab_data.txctrl.bits.TXCNT;
}


//
// Is the Rx fifo at a level that should trigger an interrupt?
//
static inline Bool rxTrigger() {
    Uns32 fifoCount = getFifoCount(&Rx);
    return fifoCount > bport1_ab_data.rxctrl.bits.RXCNT;
}

//
// update interrupt line based on current state
//
static intStateE getInterruptState() {

    intStateE intState = INT_NONE;

    bport1_ab_data.ip.bits.TXWM = txTrigger();
    bport1_ab_data.ip.bits.RXWM = rxTrigger();

    if (bport1_ab_data.ie.bits.TXWM && bport1_ab_data.ip.bits.TXWM) {
        intState |= INT_TX_EMPTY;
    }
    if (bport1_ab_data.ie.bits.RXWM && bport1_ab_data.ip.bits.RXWM) {
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
            "Uart active interrupts:%s%s",
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
        updateInterrupt();
    }
}

#define READ_ACCESS True
#define WRITE_ACCESS False

static Bool checkAlignedAccess(
    Uns32 bytes,
    Uns32 offset,
    char *name,
    Bool  isRead,
    Bool  okay
) {
    if (!bytes || ((bytes&(bytes-1))!=0) || ((offset&(bytes-1)))!=0) {
        bhmMessage(
            "W", PREFIX"_UAA",
            "Unaligned %d byte access at offset %d on %s %s",
            bytes, offset, name, isRead ? "read" : "write"
        );
        okay = False;
    }
    if (!okay) {
        if (isRead) {
            ppmReadAbort();
        } else {
            ppmWriteAbort();
        }
    }
    return okay;
}

static Bool checkAlignedWordAccess(Uns32 bytes, void *addr, char *name, Bool isRead) {
    Bool okay = True;

    if (bytes != 4) {
        bhmMessage(
            "W", PREFIX"_USS",
            "Unsupported size %d on %s %s",
            bytes, name, isRead ? "read" : "write"
        );
        okay = False;
    }

    okay = checkAlignedAccess(bytes, addr-BPORT1, name, isRead, okay);

    return okay;
}

PPM_REG_WRITE_CB(divWrite) {
    if (checkAlignedWordAccess(bytes, addr, "div", WRITE_ACCESS)) {
        bport1_ab_data.div.bits.DIV = data;
        setBaudDelay();
    }
}

PPM_REG_WRITE_CB(txdataWrite) {

    if (checkAlignedWordAccess(bytes, addr, "txdata", WRITE_ACCESS)) {
        Uns8 c = data & 0xff;

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX "_DWR",
                "txdata write: data=0x%02x ('%c')",
                c, isprint(c) ? c : ' '
            );
        }

        if (Tx.full) {

            // Transmitter Full
            // atomic swap instruction may be used to both speculatively write
            // data and detect full condition, so just ignore writes when full

        } else {

            pushTxFifo(c);
            updateInterrupt();
            putChars();

        }
    }
}

static Uns32 getTxdata() {
    bport1_ab_data.txdata.value     = 0;
    bport1_ab_data.txdata.bits.FULL = Tx.full;
    return bport1_ab_data.txdata.value;
}

PPM_REG_READ_CB(txdataRead) {
    checkAlignedWordAccess(bytes, addr, "txdata", READ_ACCESS);
    return getTxdata();
}

PPM_REG_VIEW_CB(txdataView) {
    *(Uns32 *)data = getTxdata();
}

PPM_REG_READ_CB(rxdataRead) {
    if (checkAlignedWordAccess(bytes, addr, "rxdata", READ_ACCESS)) {
        Uns8 c         = 0;
        Bool charFound = popFifo(&Rx, &c);

        if (charFound) {

            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_UR",
                    "txread read: 0x%02x ('%c')%s",
                    c, isprint(c) ? c : ' ',
                    Rx.empty ? " (RX now empty)" : ""
                );
            }

            bport1_ab_data.rxdata.bits.DATA  = c;
            bport1_ab_data.rxdata.bits.EMPTY = 0;

            // Trigger charRead event on each character read
            bhmTriggerEvent(state.charRead);

            updateInterrupt();

        } else {

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_UR", "txread read: <Empty>");
            }

            bport1_ab_data.rxdata.bits.EMPTY = 1;

        }
    }

    return bport1_ab_data.rxdata.value;
}

PPM_REG_VIEW_CB(rxdataView) {
    Uns8 c = 0;

    if (viewFifo(&Rx, &c)) {
        bport1_ab_data.rxdata.bits.DATA  = c;
        bport1_ab_data.rxdata.bits.EMPTY = 0;
    } else {
        bport1_ab_data.rxdata.bits.EMPTY = 1;
    }

    *(Uns32 *)data = bport1_ab_data.rxdata.value;
}

PPM_REG_WRITE_CB(txctrlWrite) {
    if (checkAlignedWordAccess(bytes, addr, "txctrl", WRITE_ACCESS)) {
        bport1_ab_data.txctrl.value = data & 0x00070003;
        updateInterrupt();
    }
}

PPM_REG_WRITE_CB(rxctrlWrite) {
    if (checkAlignedWordAccess(bytes, addr, "rxctrl", WRITE_ACCESS)) {
        bport1_ab_data.rxctrl.value = data & 0x00070001;
        updateInterrupt();
    }
}

PPM_REG_WRITE_CB(ieWrite) {
    if (checkAlignedWordAccess(bytes, addr, "ie", WRITE_ACCESS)) {
        bport1_ab_data.ie.value = data & 0x03;
        updateInterrupt();
    }
}

static Uns32 getIp() {
    bport1_ab_data.ip.value = 0;
    bport1_ab_data.ip.bits.TXWM = txTrigger();
    bport1_ab_data.ip.bits.RXWM = rxTrigger();
    return bport1_ab_data.ip.value;
}

PPM_REG_READ_CB(ipRead) {
    checkAlignedWordAccess(bytes, addr, "ip", READ_ACCESS);
    return getIp();
}

PPM_REG_VIEW_CB(ipView) {
    *(Uns32 *)data = getIp();
}

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
    reset_reset(value, NULL);
    updateInterrupt();
}

////////////////////
// INITIALIZATION //
////////////////////

static void initFifos() {
    setFifoSize(DEFAULT_FIFO_SIZE);
    resetFifo(&Rx);
    resetFifo(&Tx);
}

static void initEvents() {
    state.charOut   = bhmCreateNamedEvent("charOut",   "Uart character output event");
    state.charIn    = bhmCreateNamedEvent("charIn",    "Uart character input event");
    state.charRead  = bhmCreateNamedEvent("charRead",  "Uart character read event");
    state.interrupt = bhmCreateNamedEvent("interrupt", "Interrupt generated");
}

static void initBaudDelay() {

    bhmBoolParamValue("simulatebaud", &state.simulateBaud);
    if (state.simulateBaud) {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX"_STD", "Simulating transmission delays.");
        }
    }

    Uns32 newRefClkFreq;
    if(bhmUns32ParamValue("refClkFreq",  &newRefClkFreq)) {
        // Override default refClkFreq if specified by user
        state.refClkFreq = newRefClkFreq;
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

static void initUART() {

    // Initialize the fifos
    initFifos();

    // Initialize events
    initEvents();

    // Initialize baud rate delay settings
    initBaudDelay();

    // open channel and create read thread
    state.channel = bhmSerOpenAuto();

    // Init char mode setting
    initCharMode();

    // Initialize the interrupt net
    writeInterrupt(INT_NONE);

}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    initUART();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


