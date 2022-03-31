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

#define PREFIX "IO_EXPANDER"

// Enum to track current state
typedef enum {
    IDLE    = 0,
    DATA1   = 1,
    DATA2   = 2,
} stateE;

stateE status;

#define MAXREGS 8
typedef struct registersS {
    union {
        Uns8 regA[MAXREGS];
        struct {
            Uns8 inPort0;
            Uns8 inPort1;
            Uns8 outPort0;
            Uns8 outPort1;
            Uns8 polInv0;
            Uns8 polInv1;
            Uns8 config0;
            Uns8 config1;
        } regD;
    } reg;
    Uns8 control;
} registersT;

registersT reg;

const char *regNames[MAXREGS] = {
    "inPort0",
    "inPort1",
    "outPort0",
    "outPort1",
    "polInv0",
    "polInv1",
    "config0",
    "config1"
};

static void storeData(Uns8 data) {
    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX "_WD","Write data 0x%x to reg %d (%s)", data,
                reg.control,
                (reg.control >= MAXREGS) ? "exceeds max so ignored" : regNames[reg.control]);
    }
    if (reg.control < MAXREGS) {
        reg.reg.regA[reg.control] = data;
    }
    reg.control++;
}

static Uns8 getData() {
    Uns8 data = 0;  // default
    if (reg.control < MAXREGS) {
        data = reg.reg.regA[reg.control];
    }
    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX "_RD","Read data 0x%x from reg %d (%s)", data,
                reg.control,
                (reg.control >= MAXREGS) ? "exceeds max so ignored" : regNames[reg.control]);
    }
    reg.control++;
    return data;
}
//////////////////////////////// Callback stubs ////////////////////////////////


PPM_REG_WRITE_CB(writeI2C) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_WR","0x%x", data);
    }
    switch (status){
    case IDLE:
        reg.control = data;
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_WC","Command 0x%x", reg.control);
        }
        status = DATA1;
        break;
    case DATA1:
        // first data word
        storeData(data);
        status = DATA2;
        break;
    case DATA2:
        // second data word
        storeData(data);
        status = IDLE;
        break;
    default:
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX "_CMD","Write of 0x%0x when not idle ignored", data);
        }
        status = IDLE;
        break;
    }

    // outputs map back to input ports (config bit = 0)
    reg.reg.regD.inPort0 = (reg.reg.regD.inPort0  &  reg.reg.regD.config0) |
                           (reg.reg.regD.outPort0 & ~reg.reg.regD.config0);
    reg.reg.regD.inPort1 = (reg.reg.regD.inPort1  &  reg.reg.regD.config1) |
                           (reg.reg.regD.outPort1 & ~reg.reg.regD.config1);

    // XADC Mux is selected with bits 4-6 when configured as output
    #define XADC_MUX_BITS  3
    #define XADC_MUX_SHIFT 4
    #define XADC_MUX_MASK  ((~(1<<XADC_MUX_BITS)) << XADC_MUX_SHIFT)
    Uns32 xadcmux = (Uns32)(((reg.reg.regD.outPort1 & ~reg.reg.regD.config1) & XADC_MUX_MASK) >> XADC_MUX_SHIFT);
    if(ppmReadNet(handles.xadcmux) != xadcmux) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_WMUX","Write XADC MUX %d", xadcmux);
        }
        ppmWriteNet(handles.xadcmux, xadcmux);
    }
    *(Uns8*)user = data;
}

PPM_REG_READ_CB(readI2C) {
    Uns8 data = 0;
    switch (status) {
        case IDLE:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("W", PREFIX "_FR","Attempting read before command written");
            }
            break;
        case DATA1:
            // first data word
            data = getData();
            status = DATA2;
            break;
        case DATA2:
            // second data word
            data = getData();
            status = IDLE;
            break;
        default:
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("W", PREFIX "_FRD","Unexpected state for read (%d)", status);
            }
            status = IDLE;
            break;
    }

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_RD","0x%x", data);
    }
    *(Uns8*)user = data;
    return *(Uns8*)user;
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Initialize registers
    reg.reg.regD.outPort0 = 0xff;
    reg.reg.regD.outPort1 = 0xff;
    reg.reg.regD.config0  = 0xff;
    reg.reg.regD.config1  = 0xff;

    if (!handles.xadcmux) {
        bhmMessage("E", PREFIX, "No XADC MUX connection");
    }

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
