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
#include <string.h>

#include "pse.igen.h"
#include "bus.c.h"

#define DEFAULT_RX_DELAY 2000
#define PREFIX "xps-uartlite"

struct {
    Uns32 Interrupt;
    Int32 channel;
    Bool  writeError;       // An error has occurred on most recent write
} state;

#define FIFOSIZE 16
typedef struct fifoBufferS {
    Uns8 buffer[FIFOSIZE];
    Uns8 rdp, wrp;
    Bool full, empty;
} fifoBufferT, *fifoBufferP;

fifoBufferT Rx, Tx;

// processor interface is big endian by default
Bool bigEndian = True;

//
// fifo operations
//
void fifoInit(fifoBufferP fifo) {
    fifo->rdp = 0;
    fifo->wrp = 0;
    fifo->full = False;
    fifo->empty = True;
}

Bool fifoPush (fifoBufferP fifo, Uns8 value) {
    if (fifo->full) {
        return False;
    }
    fifo->buffer[fifo->wrp] = value;
    fifo->wrp = (fifo->wrp + 1) % FIFOSIZE;

    //
    // Test for buffer now being full
    //
    fifo->full  = (fifo->rdp == fifo->wrp) ? True : False;
    fifo->empty = False;

    return True;
}

Bool fifoPop (fifoBufferP fifo, Uns8 *value) {
    if (fifo->empty) {
        return False;
    }
    *value = fifo->buffer[fifo->rdp];
    fifo->rdp = (fifo->rdp + 1) % FIFOSIZE;

    //
    // Test for buffer now being empty
    //
    fifo->empty = (fifo->rdp == fifo->wrp) ? True : False;
    fifo->full  = False;

    return True;
}

//
// Write the Interrupt if the value changes
//
void write_Interrupt(Uns32 value) {
    if (state.Interrupt != value) {
        state.Interrupt = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting Interrupt=%d @ %eUS", state.Interrupt, bhmGetCurrentTime());
        ppmWriteNet(handles.Interrupt, state.Interrupt);
    }
}

//
// If the TX is !empty->empty or the RX is !empty
//
void eval_interrupts () {
    Uns32 irq = 0;

    irq = plb_REG_data.Stat.bits.IntrEnabled && (Tx.empty || !Rx.empty);
    if (irq) {
        write_Interrupt(1);
        write_Interrupt(0);
    }
}

static Int32 readInput(Uns8 *buffer, Uns32 length) {
    Int32 bytes = 0;
    if (state.channel >= 0) {
        bytes = bhmSerReadN(state.channel, buffer, length);
    }
    return bytes;
}

static Uns32 writeOutput(Uns8 *buffer, Uns32 length)
{
    Uns32 rc = 0;

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

void openFiles(void)
{
    state.channel = bhmSerOpenAuto();
}

static void getChars(void *user)
{
    Uns8 c;

    while(1) {
        double d = DEFAULT_RX_DELAY;

        //
        // keep getting chars till we fill the fifo
        //
        bhmWaitDelay(d);
        while (!Rx.full) {
            Int32 bytes = readInput(&c, 1);
            if (bytes > 0) {
                //
                // We have got a char, so insert to buffer
                //
                fifoPush(&Rx, c);
                eval_interrupts();
            }
            bhmWaitDelay(d);
        }
        if (!Rx.empty) {
            eval_interrupts();
        }
    }
}

static void putChars()
{
    Bool ok;
    Uns8 c;

    //
    // keep sending characters whilst the TX fifo is not empty
    //
    if (!Tx.empty) {
        ok = fifoPop(&Tx, &c);
        if (ok) {
            writeOutput(&c, 1);
        }
    }

    if (Tx.empty) {
        //
        // Generate an interrupt if enabled
        //
        eval_interrupts();
    } else {
        if (PSE_DIAG_HIGH) bhmMessage("F", PREFIX, "Tx.empty is false !!!");
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(ReadRxFifo) {
    Bool ok;
    Uns8 c;

    if (!Rx.empty) {
        ok = fifoPop(&Rx, &c);
        if (ok) {
            plb_REG_data.RxFifo.value = c;
        }
    }

    return GETBE(bigEndian,plb_REG_data.RxFifo.value);
}

PPM_REG_READ_CB(ReadStat) {

    plb_REG_data.Stat.bits.TxFifoEmpty      = Tx.empty;
    plb_REG_data.Stat.bits.TxFifoFull       = Tx.full;
    plb_REG_data.Stat.bits.RxFifoFull       = Rx.full;
    plb_REG_data.Stat.bits.RxFifoValidData  = !Rx.empty;

    return GETBE(bigEndian,plb_REG_data.Stat.value);
}

PPM_REG_WRITE_CB(WriteCtrl) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.Ctrl.value = d;

    if (plb_REG_data.Ctrl.bits.RstRxFifo) {
        fifoInit(&Rx);
    }
    if (plb_REG_data.Ctrl.bits.RstTxFifo) {
        fifoInit(&Tx);
    }

    plb_REG_data.Stat.bits.IntrEnabled = plb_REG_data.Ctrl.bits.EnableIntr;

    //
    // Re-evaluate any pending interrupts
    //
    eval_interrupts();
}

PPM_REG_WRITE_CB(WriteTxFifo) {
    Uns32 d = GETLE(bigEndian,data);

    fifoPush(&Tx, (Uns8)d);
    putChars();
}

PPM_CONSTRUCTOR_CB(constructor) {
    fifoInit(&Rx);
    fifoInit(&Tx);

    periphConstructor();

    openFiles();
    bhmCreateThread(getChars, NULL, "getchars", 0);

    // get endian
    char endian[16];
    if(bhmStringParamValue("endian", endian, sizeof(endian))) {
        if(!strcmp(endian, "little")) {
            bigEndian = False;
        }
    }
    if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "Model interface configured %s endian",
            bigEndian ? "big" : "little");

    write_Interrupt(0);
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

