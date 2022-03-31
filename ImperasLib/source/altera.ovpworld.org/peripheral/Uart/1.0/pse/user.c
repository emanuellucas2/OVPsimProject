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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Mon Jul 29 11:23:31 2013
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _PSE_
#    define _PSE_
#endif
#include "pse.igen.h"

#define DEFAULT_RX_DELAY 2000
#define PREFIX "UART"

struct {
    Uns32 irq;
    Int32 channel;
    Bool  writeError;       // An error has occurred on most recent write
} state;

void write_irq(Uns32 value) {
    if (state.irq != value) {
        state.irq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting irq=%d @ %eUS", state.irq, bhmGetCurrentTime());
        ppmWriteNet(handles.irq, state.irq);
    }
}

void eval_interrupts () {
    if (0) {
        write_irq(1);
        write_irq(0);
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

static void getChars(void *user)
{
    Uns8 c;

    while(1) {
        double d = DEFAULT_RX_DELAY;

        //
        // keep getting chars till we fill the fifo
        //
        bhmWaitDelay(d);
        Int32 bytes = readInput(&c, 1);
        if (bytes > 0) {
            //
            // We have got a char, so insert to register
            //
            sp1_reg0_data.rxdata.value = c;
            eval_interrupts();
        }
        bhmWaitDelay(d);

        eval_interrupts();
    }
}

static void putChars()
{
    Uns8 c = sp1_reg0_data.txdata.value;

    //
    // keep sending characters whilst the TX fifo is not empty
    //
    writeOutput(&c, 1);

    eval_interrupts();

}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(read_control) {
    // YOUR CODE HERE (read_control)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(read_divisor) {
    // YOUR CODE HERE (read_divisor)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(read_eop) {
    // YOUR CODE HERE (read_eop)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(read_rxdata) {
    return sp1_reg0_data.rxdata.value;
}

PPM_REG_READ_CB(read_status) {
    // YOUR CODE HERE (read_status)
    return *(Uns16*)user;
}

PPM_REG_WRITE_CB(write_control) {
    // YOUR CODE HERE (write_control)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(write_divisor) {
    // YOUR CODE HERE (write_divisor)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(write_eop) {
    // YOUR CODE HERE (write_eop)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(write_status) {
    // YOUR CODE HERE (write_status)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(write_txdata) {
    sp1_reg0_data.txdata.value = data;
    putChars();
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    openFiles();
    bhmCreateThread(getChars, NULL, "getchars", 0);

    write_irq(0);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

