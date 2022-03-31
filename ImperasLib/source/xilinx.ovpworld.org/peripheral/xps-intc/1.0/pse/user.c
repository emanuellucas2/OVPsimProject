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
#include "bus.c.h"

#define PREFIX "xps-intc"

struct {
    Uns32 Irq;
} state;

// processor interface is big endian by default
Bool bigEndian = True;

//
// Write the Interrupt if the value changes
//
void write_Irq(Uns32 value) {
    if (state.Irq != value) {
        state.Irq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting Irq=%d @ %eUS\n", state.Irq, bhmGetCurrentTime());
        ppmWriteNet(handles.Irq, state.Irq);
    }
}

void eval_status() {
    plb_REG_data.IPR.value = plb_REG_data.ISR.value & plb_REG_data.IER.value;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ISR=0x%08x\n", plb_REG_data.ISR.value);
        bhmMessage("I", PREFIX, "IER=0x%08x\n", plb_REG_data.IER.value);
        bhmMessage("I", PREFIX, "IPR=0x%08x\n", plb_REG_data.IPR.value);
    }

    //
    // Set interrupt accordingly
    //
    if (plb_REG_data.IPR.value == 0) {
        plb_REG_data.IVR.value = 0xffffffff;
        //
        // Clear Interrupt signal
        //
        write_Irq(0);
    } else {
        //
        // Calculate the IVR
        //
        Int32 i;
        for (i=0; i<32; i++) {
            if ((plb_REG_data.IPR.value >> i) & 0x1) {
                plb_REG_data.IVR.value = i;
                break;
            }
        }

        //
        // Set Interrupt signal
        //
        write_Irq(1);
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////
PPM_NET_CB(WriteIntr) {
    // YOUR CODE HERE (WriteIntr)
    Uns32 input = PTR_TO_UNS32(userData);
    plb_REG_data.ISR.value |= value << input;
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Pin Intr_%d = %d\n", input, (Uns32)value);

    eval_status();
}

PPM_REG_READ_CB(ReadIER) {
    return GETBE(bigEndian,plb_REG_data.IER.value);
}

PPM_REG_READ_CB(ReadIPR) {
    return GETBE(bigEndian,plb_REG_data.IPR.value);
}

PPM_REG_READ_CB(ReadISR) {
    return GETBE(bigEndian,plb_REG_data.ISR.value);
}

PPM_REG_READ_CB(ReadIVR) {
    return GETBE(bigEndian,plb_REG_data.IVR.value);
}

PPM_REG_READ_CB(ReadMER) {
    return GETBE(bigEndian,plb_REG_data.MER.value);
}

//
// Writing the IAR clears the ISR
//
PPM_REG_WRITE_CB(WriteIAR) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.ISR.value &= ~d;
    eval_status();
}

PPM_REG_WRITE_CB(WriteIER) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.IER.value = d;
    eval_status();
}

PPM_REG_WRITE_CB(WriteISR) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.ISR.value = d;
    eval_status();
}

PPM_REG_WRITE_CB(WriteMER) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.MER.value = d;
    eval_status();
}

PPM_REG_WRITE_CB(WriteCIE) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.IER.value &= ~d;
    eval_status();
}

PPM_REG_WRITE_CB(WriteSIE) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.IER.value |= d;
    eval_status();
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    // get endian
    char endian[16];
    if(bhmStringParamValue("endian", endian, sizeof(endian))) {
        if(!strcmp(endian, "little")) {
            bigEndian = False;
        }
    }

    if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "Model interface configured %s endian",
            bigEndian ? "big" : "little");

    write_Irq(0);
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

