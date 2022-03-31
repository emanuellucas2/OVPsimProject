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

#include "pse.igen.h"

#define PREFIX "UART"

// Default for baud rate delay (in uSecs):
#define DEFAULT_BAUD_DELAY 100

// Default frequency of UART Module clock
#define DEFAULT_MODULE_CLK_FREQ (10200000)

// Maximum FIFO depth supported
#define MAXFIFO 128

// Default fifo depth
#define DEFAULT_FIFO_SIZE   MAXFIFO

struct {
    Uns32 intStatus;        // Current status of the interrupt line
    Int32 channel;          // Serial channel returned by bhmSerOpenAuto()
    Uns32 baudDelay;        // Baud rate delay in uSecs
    Uns32 moduleClkFreq;    // Clock freq used in baud rate calculations
    Uns32 fifoSize;         // Number of entries available in fifo
    Uns8  bdhTemp;          // Value written to bdh - not used until bdl is written
    Bool  directMode;       // Use directmode rather than BHM Serial channel
    Bool  writeError;       // An error has occurred on most recent write

} state = {
    .channel       = -1,
    .baudDelay     = DEFAULT_BAUD_DELAY,
    .moduleClkFreq = DEFAULT_MODULE_CLK_FREQ,
    .fifoSize      = DEFAULT_FIFO_SIZE
};

typedef struct fifoBufferS {
    Uns8 buffer[MAXFIFO];   // fifo buffer
    Uns8 rdp, wrp;          // pointers to read and write points
    Bool full, empty;       // flags when full or empty
} fifoBufferT, *fifoBufferP;

fifoBufferT Rx, Tx;

//
// fifo operations
//
static void fifoInit(fifoBufferP fifo) {
    fifo->rdp = 0;
    fifo->wrp = 0;
    fifo->full = False;
    fifo->empty = True;
}

//
// Convert the pfifo size field to the indicated fifo depth
//
static Uns32 fifoFieldToDepth(Uns32 field) {

    Uns32 depth;

    // value of 0 is special case
    if (field == 0) {
        depth = 1;
    } else {
        depth = 1 << (field+1);
    }

    return depth;
}

//
// Initialize the pfifo register fields that specify the fifo size
//
static void initFifoSize() {

    Uns32 size = state.fifoSize;

    if (size > MAXFIFO) {
        bhmMessage(
            "W", PREFIX "_FTL",
            "Specified fifoSize=%d too large. Using max value %d",
            state.fifoSize,
            MAXFIFO
        );
        size = state.fifoSize = MAXFIFO;
    }

    Uns32 sizeField = 0;

    while (fifoFieldToDepth(sizeField) < size) {
        sizeField++;
    }

    // Set pfifo size fields to configured value
    // (note this is read only so can't be changed by a write to the register)
    bport1_ab_data.pfifo.bits.txfifosize = sizeField;
    bport1_ab_data.pfifo.bits.rxfifosize = sizeField;

}

//
// return the current pfifo register fifosize field for the fifo
// (Returns 0 if fifos disabled)
//
static Uns32 fifoDepthField(fifoBufferP fifo) {

    Uns32 depth = 0;

    if (fifo == &Rx) {
        if (bport1_ab_data.pfifo.bits.rxfe) {
            depth = bport1_ab_data.pfifo.bits.rxfifosize;
        }
    } else if (fifo == &Tx) {
        if (bport1_ab_data.pfifo.bits.txfe) {
            depth = bport1_ab_data.pfifo.bits.txfifosize;
        }
    } else {
        bhmMessage("F", PREFIX "_IF", "Invalid fifo");
    }

    return depth;
}

//
// Return currently configured depth for the fifo
//
static Uns32 fifoDepth(fifoBufferP fifo) {

    Uns32 field = fifoDepthField(fifo);
    Uns32 depth = fifoFieldToDepth(field);

    return (depth > state.fifoSize)?  state.fifoSize : depth;

}

//
// Push element onto fifo buffer and update full and empty flags
// Return False if unable to complet because fifo is full
//
Bool fifoPush (fifoBufferP fifo, Uns8 value) {

    if (fifo->full) {
        return False;
    } else {
        fifo->buffer[fifo->wrp] = value;
        fifo->wrp = (fifo->wrp + 1) % fifoDepth(fifo);

        // Test for buffer now being full
        fifo->full  = (fifo->rdp == fifo->wrp) ? True : False;
        fifo->empty = False;

        return True;
    }
}

//
// Pop element from fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is empty
//
Bool fifoPop (fifoBufferP fifo, Uns8 *value) {
    if (fifo->empty) {
        return False;
    } else {
        *value = fifo->buffer[fifo->rdp];
        fifo->rdp = (fifo->rdp + 1) % fifoDepth(fifo);

        // Test for buffer now being empty
        fifo->empty = (fifo->rdp == fifo->wrp) ? True : False;
        fifo->full  = False;

        return True;
    }
}

//
// Return number of entries in the fifo
//
Uns8 fifoCount(fifoBufferP fifo) {

    Uns32 depth = fifoDepth(fifo);

    if (fifo->full) {
        return depth;
    } else if (fifo->empty) {
        return 0;
    } else if (fifo->wrp < fifo->rdp) {
        return (depth - fifo->rdp + fifo->wrp);
    } else {
        return(fifo->wrp - fifo->rdp);
    }
}

//
// Return the delay in uSec for the currently configured baud rate
//
Uns32 getBaudDelay() {

    Uns32 sbrh      = bport1_ab_data.bdh.bits.sbr << 8;
    Uns32 sbrl      = bport1_ab_data.bdl.value;
    Uns32 brfa      = bport1_ab_data.c4.bits.brfa;
    Uns32 sbr       = (sbrh << 8) | sbrl;
    Uns32 baudDelay = 0;
    Uns32 oldDelay  = state.baudDelay;

    if (sbr > 0) {

        // Compute baud rate (in HZ) indicated by registers
        Uns32 baud = state.moduleClkFreq / ((16 * sbr) + (brfa/2));

        if (baud != 0) {

            // Convert baud rate in Hz to uSec delay between chars (8 bits per char)
            baudDelay = 8*(1000*1000)/baud;

            if (PSE_DIAG_MEDIUM && baudDelay != oldDelay) {
                bhmMessage(
                    "I", PREFIX "_BRC",
                    "Baud rate changed to %d",
                    baud
                );
            }
        }
    }

    // baudDelay = 0 really disables tx/rx but we are not modeling that
    return baudDelay ? baudDelay : DEFAULT_BAUD_DELAY;

}

//
// Set interrupt line to value (if connected)
//
void writeInterrupt(Uns32 value) {

    // Only update if value changes from current  state
    if (state.intStatus != value) {

        state.intStatus = value;

        if (handles.Interrupt) {

            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_SI",
                    "Setting Interrupt=%d @ %0.0fuS",
                    state.intStatus, bhmGetCurrentTime()
                );
            }

            ppmWriteNet(handles.Interrupt, state.intStatus);

        }
    }
}

static inline Bool txDataEmpty() {
    return fifoCount(&Tx) <= bport1_ab_data.twfifo.value;
}

static inline Bool txComplete() {
    return Tx.empty;
}

static inline Bool rxDataFull() {
    return fifoCount(&Rx) >= bport1_ab_data.rwfifo.value;
}

static inline Bool idle() {
    return Rx.empty;
}

//
// update interrupt line based on current state
//
void updateInterrupt() {

    Bool txEmptyInt = (bport1_ab_data.c2.bits.tie  && txDataEmpty());
    Bool txComplInt = (bport1_ab_data.c2.bits.tcie && txComplete());
    Bool rxFullInt  = (bport1_ab_data.c2.bits.rie  && rxDataFull());
    Bool idleInt    = (bport1_ab_data.c2.bits.ilie && idle());
    Bool activeInt  =  txEmptyInt | txComplInt | rxFullInt | idleInt;

    if (activeInt && PSE_DIAG_HIGH) {
        bhmMessage(
            "I", PREFIX "_AI",
            "Uart active interrupts:%s%s%s%s",
            txEmptyInt ? " TxEmpty" : "",
            txComplInt ? " TxComplete" : "",
            rxFullInt  ? " RxFull" : "",
            idleInt    ? " Idle" : ""
        );
    }
    writeInterrupt(activeInt);
}

//
// Write data to the channel
// return 0 if channel is not available
//
static Uns32 writeOutput(Uns8 *buffer, Uns32 length) {

    Uns32 rc = 0;

    if (state.channel >= 0) {

        rc = bhmSerWriteN(state.channel, buffer, length);

        if (rc != length) {
            if (!state.writeError) {
                bhmMessage("W", "US", "Channel write error (%u). Channel closed?", bhmSerLastError(state.channel));
                state.writeError = True;
            }
        } else {
            state.writeError = False;
        }
    }

    return rc;

}

//
// Open the UART communication channel
//
static void openChannel(void) {
    state.channel = bhmSerOpenAuto();
}

//
// This continuously runs in its own thread,
// checking for data from the serial channel
// when the rx fifo is not full and the receiver is enabled
// and placing data that is read into the rx fifo
//
#define MAXREAD 256
static void channelReadThread(void *user) {

    if (state.directMode) {
        bhmMessage("F", PREFIX "_NCM", "Not in channel mode");
    }

    while (1) {
        //
        // Blocking read
        //
        Uns8 buffer[MAXREAD];
        Uns8 bytes = bhmSerReadB(state.channel, buffer, MAXREAD);
        Uns32 i;
        for(i=0; i<bytes; i++) {
            bhmWaitDelay(state.baudDelay);

            if (bport1_ab_data.c2.bits.re && !Rx.full) {
                Uns8 c = buffer[i];

                fifoPush(&Rx, c);

                if (PSE_DIAG_HIGH) {
                    bhmMessage(
                        "I", PREFIX "_URS",
                        "Uart read data 0x%2x ('%c') @ %0.0fuS%s",
                        c, c ? c : ' ',
                        bhmGetCurrentTime(),
                        Rx.full ? " (RX now full)" : ""
                    );
                }

                updateInterrupt();
            }
        }
    }
}

//
// This continuously runs in its own thread,
// checking for data to write in the TX fifo
// when the transmiter is enabled
//
static void directWriteThread(void *user) {

    if (!state.directMode) {
        bhmMessage("F", PREFIX "_NDM", "Not in direct mode");
    }

    while (1) {

        bhmWaitDelay(state.baudDelay);

        // write char if transmitter is enabled and fifo is not empty
        if (bport1_ab_data.c2.bits.te && !Tx.empty) {

            Uns8 c;

            fifoPop(&Tx, &c);

            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX "_UWD",
                    "Uart write data 0x%2x ('%c') @ %0.0fuS%s",
                    c, c ? c : ' ',
                    bhmGetCurrentTime(),
                    Tx.empty ? " (TX now empty)" : ""
                );
            }

            // Write to serial to maintain logging
            writeOutput(&c, 1);
            ppmWriteNet(handles.DirectWrite, c);
            updateInterrupt();

        }
    }
}

//
// Write tx data fifo to serial output channel if transmitter is enabled
//
static void putChars() {
    if (bport1_ab_data.c2.bits.te) {
        Uns8 c;
        while (fifoPop(&Tx, &c)) {
            writeOutput(&c, 1);
        }
    }
}

//
// Write data to c2 register and update interrupt line
//
PPM_REG_WRITE_CB(writeC2) {
    bport1_ab_data.c2.value = (Uns8)data;
    updateInterrupt();
}

//
// Write data to c4 register and update baud rate
//
PPM_REG_WRITE_CB(writeC4) {
    bport1_ab_data.c4.value = (Uns8)data;
    state.baudDelay = getBaudDelay();
}

//
// Write data to bdl register and update baud rate
// bdh changes take effect now
//
PPM_REG_WRITE_CB(writeBDL) {
    bport1_ab_data.bdl.value = (Uns8)data;
    bport1_ab_data.bdh.value = state.bdhTemp;
    state.baudDelay = getBaudDelay();
}

//
// Record value written but do not move into reg until bdl is written
//
PPM_REG_WRITE_CB(writeBDH) {
    state.bdhTemp = (Uns8)data;
}

//
// write the cfifo register - flush fifos if indicated
//
PPM_REG_WRITE_CB(writeCFIFO) {

    bport1_ab_data.cfifo.value = (Uns8)data & 0xcf;

    if (bport1_ab_data.cfifo.bits.txflush) {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_TFF", "Transmitter fifo flushed");
        }

        fifoInit(&Tx);

    }

    if (bport1_ab_data.cfifo.bits.rxflush) {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_RFF", "Receiver fifo flushed");
        }

        fifoInit(&Rx);

    }

    updateInterrupt();

}

//
// write the twfifo register - may change interrupt state
//
PPM_REG_WRITE_CB(writeTWFIFO) {

    bport1_ab_data.twfifo.value = (Uns8)data;

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(
            "I", PREFIX "_TFT",
            "Transmitter fifo threshold set to %d",
            bport1_ab_data.rwfifo.value
        );
    }

    updateInterrupt();

}

//
// write the rwfifo register - may change interrupt state
//
PPM_REG_WRITE_CB(writeRWFIFO) {

    bport1_ab_data.rwfifo.value = (Uns8)data;

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(
            "I", PREFIX "_RFT",
            "Receiver fifo threshold set to %d",
            bport1_ab_data.rwfifo.value
        );

    }

    updateInterrupt();

}

//
// Data port read - pop data from the fifo
//
PPM_REG_READ_CB(readD) {

    Uns8 c;

    if (!fifoPop(&Rx, &c)) {

        // Underflow - error conditions not modeled yet
        bhmMessage(
            "W", PREFIX "_UUT",
            "Transmitter underflow: D register read when no data available"
        );

    } else {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX "_UR",
                "Read from Data register:0x%02x ('%c')%s",
                c, c ? c : ' ',
                Rx.empty ? " (RX now empty)" : ""
            );
        }

        updateInterrupt();

    }

    bport1_ab_data.d.value = c;
    return c;

}

//
// Data port write - push data on fifo and
// write fifo data to serial channel if in serial mode
//
PPM_REG_WRITE_CB(writeD) {

    Uns8 c = data & 0xff;

    if (!fifoPush(&Tx, c)) {

        // Overflow - error conditions not modeled yet
        bhmMessage(
            "W", PREFIX "_UOT",
            "Transmitter overflow: data=0x%02x ('%c') lost",
            c, c ? c : ' '
        );

    } else {

        // Write to serial channel if not in direct mode
        if (!state.directMode) {
            putChars();
        }

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX "_UW",
                "Write to Data register: data=0x%02x ('%c')%s",
                c, c ? c : ' ',
                Tx.full ? " (TX now full)" : ""
            );
        }

        updateInterrupt();

    }
}

//
// Form value for s1 reg from current state
//
static Uns8 getS1() {

    bport1_ab_data.s1.value = 0;

    bport1_ab_data.s1.bits.tdre = fifoCount(&Tx) <= bport1_ab_data.twfifo.value;
    bport1_ab_data.s1.bits.tc   = Tx.empty;
    bport1_ab_data.s1.bits.rdrf = fifoCount(&Rx) >= bport1_ab_data.rwfifo.value;
    bport1_ab_data.s1.bits.idle = Rx.empty;

    return bport1_ab_data.s1.value;

}

//
// Read the s1 register - must form value when read
//
PPM_REG_READ_CB(readS1) {
    return getS1();
}

//
// View the s1 register - must form value when read
//
PPM_REG_VIEW_CB(viewMCG_s) {
    *(Uns8 *)data = getS1();
}

//
// Reset net value changed
//
PPM_NET_CB(resetCB) {
    reset_Reset(value, 0);
    updateInterrupt();
}

//
// Callback on write to directRead input net
//
PPM_NET_CB(directReadCB) {

    Uns8 c = value & 0xff;

    if (!fifoPush(&Rx, c)) {

        // overrun - error conditions not modeled yet
        bhmMessage(
            "W", PREFIX "_UOR",
            "Receiver overrun: data=0x%02x ('%c') lost",
            c, c ? c : ' '
        );

    } else if (PSE_DIAG_HIGH) {

        bhmMessage(
            "I", PREFIX "_URD",
            "Uart read  data 0x%2x ('%c')",
            c, c ? c : ' '
        );

    }

    updateInterrupt();

}

PPM_CONSTRUCTOR_CB(constructor) {

    // Get user configuration attributes
    bhmUns32ParamValue("fifoSize",       &state.fifoSize);
    bhmUns32ParamValue("moduleClkFreq",  &state.moduleClkFreq);

    // Initialize fifo size info in model
    initFifoSize();

    // Initialize the fifos
    fifoInit(&Rx);
    fifoInit(&Tx);

    // Construct the model
    periphConstructor();

    Uns32 portnum;
    // If DirectRead and DirectWrite nets are connected then use direct mode when enabled
    Bool directRW, console;
    bhmBoolParamValue("directReadWrite", &directRW);
    bhmBoolParamValue("console", &console);

    state.directMode = directRW && !console && !bhmUns32ParamValue("portnum", &portnum);

    if(state.directMode && !(handles.DirectRead && handles.DirectWrite)) {
        bhmMessage(
            "E", PREFIX "_DRWNC",
            "Uart initialized in direct connect mode but DirectRead/DirectWrite nets are not connected"
        );
    }

    // Initialize the interrupt net
    writeInterrupt(0);

    if (state.directMode) {

        // Create write thread in direct mode
        bhmCreateThread(directWriteThread, NULL, "directWriteThread", 0);

        if (PSE_DIAG_LOW) {
            bhmMessage(
                "I", PREFIX "_UID",
                "Uart initialized in direct connect mode"
            );
        }

    } else {

        // open channel and create read thread in serial mode
        openChannel();
        bhmCreateThread(channelReadThread, NULL, "channelReadThread", 0);

        if (PSE_DIAG_LOW) {
            bhmMessage(
                "I", PREFIX "_UIS",
                "Uart initialized in serial channel mode"
            );
        }
    }
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

