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

#include <string.h>

#include "pse.igen.h"

#define FUNC_NAME __FUNCTION__

struct {
    Uns32 pins;
    Uns32 activeInt;
    Uns32 irq;
    Int32 channel;
    Bool rxen, txen;
    Bool loopback;
    Bool writeError;       // An error has occurred on most recent write

} state;

#define DEFAULT_RX_DELAY 2000
#define PREFIX "UART"

//
// Write the irq if the value changes
//
void write_irq(Uns32 value) {
    if (state.irq != value) {
        state.irq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting Interrupt IRQ=%d\n", state.irq);
        ppmWriteNet(handles.irq, state.irq);
    }
}

static Int32 readInput(Uns8 *buffer, Uns32 length) {
    Int32 bytes = 0;
    if (state.channel >= 0) {
        bytes = bhmSerReadN(state.channel, buffer, length);
    }
    return bytes;
}

static void getChars(void *user)
{
    while(1) {
        double d = DEFAULT_RX_DELAY;

        bhmWaitDelay(d);
        Uns8 c;

        if (readInput(&c, 1)) {
            bport1_ab_data.dr.value = c;
            bport1_ab_data.fr.bits.RXFE = 0;
            // Test for generating an interrupt
            if (bport1_ab_data.im.bits.RXIM) {
                write_irq(1);
            } else {
                write_irq(0);
            }
        }
    }
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

static void openFiles(void)
{
    state.channel = bhmSerOpenAuto();
}


//////////////////////////////// Callback functions ////////////////////////////////

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    openFiles();
    bhmCreateThread(getChars, NULL, "getchars", 0);

    write_irq(0);

    bhmBoolParamValue("loopback", &state.loopback);
    if (state.loopback) {
        bhmMessage("I", PREFIX, "Loopback mode enabled");
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    if(state.channel >= 0) {
        bhmSerClose(state.channel);
    }
}

PPM_REG_READ_CB(readDR) {
    *(Uns32*)user = bport1_ab_data.dr.value;
    bport1_ab_data.fr.bits.RXFE = 1;
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(writeDR) {
    *(Uns32*)user = data;
    writeOutput((Uns8*)user, 1);
    if(state.loopback) {
        if (diagnosticLevel > 0) bhmMessage("I", "UartInterface", "LoopBack Data 0x%x (%c)", data, data);
        bport1_ab_data.dr.value = data;
        bport1_ab_data.fr.bits.RXFE = 0;
    }
    if(bport1_ab_data.im.bits.TXIM || (state.loopback && bport1_ab_data.im.bits.RXIM)) {
        if (diagnosticLevel > 0)
           bhmMessage("I", "UartInterface", "Interrupt%s%s",
                   state.loopback && bport1_ab_data.im.bits.RXIM ? " RX" : "",
                   bport1_ab_data.im.bits.TXIM ? " TX" : "");
        write_irq(1);
    } else {
        write_irq(0);
    }
}

PPM_REG_WRITE_CB(writeICR) {
    *(Uns32*)user = data;
    // clear interrupt bits corresponding
    bport1_ab_data.fr.value &= ~data;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readCTL) {
    // YOUR CODE HERE (readCTL)
    return *(Uns32*)user;
}


PPM_REG_READ_CB(readICR) {
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readIM) {
    // YOUR CODE HERE (readIM)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readMIS) {
    // YOUR CODE HERE (readMIS)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readRIS) {
    // YOUR CODE HERE (readRIS)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readSR) {
    // YOUR CODE HERE (readSR)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readSRRECR) {
    // YOUR CODE HERE (readSRRECR)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(writeCTL) {
    // YOUR CODE HERE (writeCTL)
    *(Uns32*)user = data;
}



PPM_REG_WRITE_CB(writeIM) {
    // YOUR CODE HERE (writeIM)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeMIS) {
    // YOUR CODE HERE (writeMIS)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeRIS) {
    // YOUR CODE HERE (writeRIS)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeSRRECR) {
    // YOUR CODE HERE (writeSRRECR)
    *(Uns32*)user = data;
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

