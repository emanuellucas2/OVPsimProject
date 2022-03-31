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

#ifndef _PSE_
#    define _PSE_
#endif
#include "pse.igen.h"

#define DEFAULT_RX_DELAY 10
#define DEFAULT_TX_DELAY 10

#define PREFIX "JTAG-UART"
#define MAXBUFFER 32768

#define MODE 1

/*
 * Nios Writes to   WriteFifo
 * PC   reads  from WriteFifo
 *
 * Nios Reads  from ReadFifo
 * PC   Writes to   ReadFifo
 */
struct {
    Uns32 irq;
    Int32 channel;
    Bool  writeError;       // An error has occurred on most recent write
} state;

typedef struct {
    Uns8  buffer[MAXBUFFER];
    Uns8  rdp, wrp;
    Uns32 depth;
    Uns32 threshold;

    Bool  full,     empty;
    Bool  thr_full, thr_empty;
} fifoBufferT, *fifoBufferP;

fifoBufferT Rx, Tx;

//
// fifo operations
//
void fifoInit(fifoBufferP fifo, Uns32 depth, Uns32 threshold) {
    fifo->rdp       = 0;
    fifo->wrp       = 0;

    fifo->depth     = depth;
    fifo->threshold = threshold;

    fifo->full      = False;
    fifo->empty     = True;
    fifo->thr_full  = False;
    fifo->thr_empty = True;
}

Uns32 fifoSlotsUsed(fifoBufferP fifo) {
    Uns32 used = 0;
    if (fifo->full) {
        used = fifo->depth;

    } else if (fifo->empty) {
        used = 0;

    } else if (fifo->wrp >= fifo->rdp) {
        //
        // Buffer is not wrapped
        //
        used = (fifo->wrp - fifo->rdp);

    } else {
        //
        // Buffer is wrapped
        //
        used = ((fifo->wrp + fifo->depth) - fifo->rdp);

    }

    return used;
}

Uns32 fifoSlotsAvail(fifoBufferP fifo) {
    Uns32 used  = fifoSlotsUsed(fifo);
    Uns32 avail = fifo->depth - used;

    return avail;
}

Bool fifoPush (fifoBufferP fifo, Uns8 value) {
    if (fifo->full) {
        return False;
    }
    fifo->buffer[fifo->wrp] = value;
    fifo->wrp = (fifo->wrp + 1) % fifo->depth;

    //
    // Test for buffer now being full/nearlyfull
    //
    fifo->full  = (fifo->rdp == fifo->wrp) ? True : False;
    fifo->empty = False;

    //
    // Test for buffer now being empty within threshold
    //
    Uns32 used = fifoSlotsUsed(fifo);
    fifo->thr_empty = (used <= fifo->threshold);
    fifo->thr_full  = (used >= (fifo->depth - fifo->threshold - 1));

    if (PSE_DIAG_HIGH) {
        bhmPrintf("fifoPush: full=%d empty=%d thr_full=%d thr_empty=%d used=%d\n",
            fifo->full, fifo->empty,
            fifo->thr_full, fifo->thr_empty, used);
    }

    return True;
}

Bool fifoPop (fifoBufferP fifo, Uns8 *value) {
    if (fifo->empty) {
        return False;
    }
    *value = fifo->buffer[fifo->rdp];
    fifo->rdp = (fifo->rdp + 1) % fifo->depth;

    //
    // Test for buffer now being empty
    //
    fifo->empty = (fifo->rdp == fifo->wrp) ? True : False;
    fifo->full  = False;

    //
    // Test for buffer now being empty within threshold
    //
    Uns32 used = fifoSlotsUsed(fifo);
    fifo->thr_empty = (used <= fifo->threshold);
    fifo->thr_full  = (used >= (fifo->depth - fifo->threshold - 1));

    if (PSE_DIAG_HIGH) {
        bhmPrintf("fifoPop: full=%d empty=%d thr_full=%d thr_empty=%d used=%d\n",
            fifo->full, fifo->empty,
            fifo->thr_full, fifo->thr_empty, used);
    }

    return True;
}

//
// Write the irq if the value changes
//
void write_irq(Uns32 value) {
    if (state.irq != value) {
        state.irq = value;
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Setting irq=%d @ %eUS", state.irq, bhmGetCurrentTime());
        ppmWriteNet(handles.irq, state.irq);
    }
}

//
// If the TX <= Thresh or the RX >= Thresh
//
void eval_interrupts () {
    Bool RE = sp1_reg0_data.control.bits.RE;
    Bool WE = sp1_reg0_data.control.bits.WE;
    Bool RI = 0;
    Bool WI = 0;

    //
    // Read Interrupt ?
    // If read buffer is greater than or equal to threshold
    // or if it is one and no more expected ????????
    //RI = (RE && Rx.thr_full);
    RI = (RE && !Rx.empty);

    //
    // Write Interrupt ?
    // If write buffer is less than or equal to threshold
    //
    WI = (WE && Tx.thr_empty);

    //
    // Any interrupts ?
    //
    if (WI || RI) {
        write_irq(1);
    } else {
        write_irq(0);
    }

    sp1_reg0_data.control.bits.RI = RI;
    sp1_reg0_data.control.bits.WI = WI;
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
                bhmMessage("W", PREFIX, "Serial channel write error (%u). Channel closed?", bhmSerLastError(state.channel));
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

/*
 * getChars is data from PC->Nios
 * Interrupts generated when PC writes too fast for Nios
 */
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
                // Make it look as though there has been JTAG activity
                //
                sp1_reg0_data.control.bits.AC = 1;

                //
                // We have got a char, so insert to buffer
                //
                fifoPush(&Rx, c);
                eval_interrupts();
            }
            bhmWaitDelay(d);
        }
        eval_interrupts();
    }
}

/*
 * putChars is data from Nios->PC
 * Interrupts generated when Nios to fast for PC
 */
static void putChars(void *user)
{
    Bool ok;
    Uns8 c;

    while(1) {
        double d = DEFAULT_TX_DELAY;

        //
        // keep getting chars till we fill the fifo
        //
        bhmWaitDelay(d);
        while (!Tx.empty) {
            //
            // Make it look as though there has been JTAG activity
            //
            sp1_reg0_data.control.bits.AC = 1;

            ok = fifoPop(&Tx, &c);

            if (ok) {
                writeOutput(&c, 1);
            }
        }
        eval_interrupts();
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(read_control) {
    //
    // Calculate the write spaces
    //
    Uns32 avail = fifoSlotsAvail(&Tx);
    sp1_reg0_data.control.bits.WSPACE = avail;

    return sp1_reg0_data.control.value;
}

PPM_REG_READ_CB(read_data) {
    Bool ok;
    Uns8 c;

    sp1_reg0_data.data.bits.RVALID = 0;
    if (!Rx.empty) {
        ok = fifoPop(&Rx, &c);
        if (ok) {
            sp1_reg0_data.data.bits.DATA = c;
            sp1_reg0_data.data.bits.RVALID = 1;
        }
    }

    Uns32 avail = fifoSlotsAvail(&Rx);
    sp1_reg0_data.data.bits.RAVAIL = avail;
    eval_interrupts();

    return sp1_reg0_data.data.value;
}

PPM_REG_WRITE_CB(write_control) {

    // Only writable bits are 0,1,10
    sp1_reg0_dataT local;
    local.control.value = data;

    sp1_reg0_data.control.bits.RE = local.control.bits.RE;
    sp1_reg0_data.control.bits.WE = local.control.bits.WE;

    //
    // This is a Read/Clear bit
    //
    if (local.control.bits.AC == 1) {
        sp1_reg0_data.control.bits.AC = 0;
    }

    //
    // Re-evaluate any pending interrupts
    //
    eval_interrupts();
}

PPM_REG_WRITE_CB(write_data) {
    sp1_reg0_dataT local;
    local.data.value = data;

    sp1_reg0_data.data.bits.DATA = local.data.bits.DATA;

    fifoPush(&Tx, sp1_reg0_data.data.bits.DATA);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    //
    // Get the Attributes (defaults in pse.tcl)
    //
    Uns32 readBufferDepth;
    Uns32 readIRQThreshold;
    Uns32 writeBufferDepth;
    Uns32 writeIRQThreshold;
    bhmUns32ParamValue("readBufferDepth",   &readBufferDepth);
    bhmUns32ParamValue("readIRQThreshold",  &readIRQThreshold);
    bhmUns32ParamValue("writeBufferDepth",  &writeBufferDepth);
    bhmUns32ParamValue("writeIRQThreshold", &writeIRQThreshold);

    fifoInit(&Rx, readBufferDepth,  readIRQThreshold);
    fifoInit(&Tx, writeBufferDepth, writeIRQThreshold);

    openFiles();
    bhmCreateThread(getChars, NULL, "getChars", 0);
    bhmCreateThread(putChars, NULL, "putChars", 0);

    write_irq(0);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

