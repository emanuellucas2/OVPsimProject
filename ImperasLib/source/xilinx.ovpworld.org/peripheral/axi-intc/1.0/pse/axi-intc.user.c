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

#define PREFIX "AXI_INTC"

struct {
    Uns32   irq;                    // current interrupt out level

    Uns32   numberINTR;
    Uns32   numberSWINTR;

    Bool    hasIPR;
    Bool    hasSIE;
    Bool    hasCIE;
    Bool    hasIMR;
    Bool    hasFAST;
    Bool    enableCASCADE;
    Bool    setCASCADEMASTER;

} state;


#define ALLINTERRUPTS    (state.numberINTR + state.numberSWINTR)
#define HWINTERRUPTS     (state.numberINTR)

// filter the input data so only enabled interrupt bits are retained
#define FILTERENABLED(_d) (_d & ((1 << ALLINTERRUPTS) -1 ))

//
// Write the Interrupt if the value changes
//
void write_Irq(Uns32 value) {
    if (state.irq != value) {
        if (bport1_ab_data.MER.bits.ME) {
            state.irq = value;
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting Irq=%d @ %eUS", state.irq, bhmGetCurrentTime());
            ppmWriteNet(handles.irq, state.irq);
        } else {
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Disabled Irq=%d->%d @ %eUS", state.irq, value, bhmGetCurrentTime());
        }
    }
}

//
// Write the Interrupt Vector Address
//
void write_IrqAddr(Uns32 index) {

    if((state.hasFAST) &&
       ((bport1_ab_data.IMR.value >> index) & 0x1)) {
          // Fast interrupt enabled
          Uns32 vectorAddress = bport1_ab_data.IVAR[index].value;

          if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting Irq%d Vector Address 0x%08x", index, vectorAddress);

          ppmWriteNet(handles.irq_addr_out, vectorAddress);
      }

}

void eval_status() {

    bport1_ab_data.IPR.value = bport1_ab_data.ISR.value & bport1_ab_data.IER.value;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ISR=0x%08x IER=0x%08x IPR=0x%08x ILR=0x%08x",
                    bport1_ab_data.ISR.value,
                    bport1_ab_data.IER.value,
                    bport1_ab_data.IPR.value,
                    bport1_ab_data.ILR.value);
    }

    //
    // Set interrupt accordingly
    //
    if (bport1_ab_data.IPR.value == 0) {
        bport1_ab_data.IVR.value = 0xffffffff;

        // Clear Interrupt signal
        write_Irq(0);
    } else {

        // Calculate the IVR
        Int32 i;
        Uns32 max = ALLINTERRUPTS;
        for (i=0; i<max; i++) {
            if ((bport1_ab_data.IPR.value >> i) & 0x1) {
                // check this level is enabled
                if (i < bport1_ab_data.ILR.value) {
                    bport1_ab_data.IVR.value = i;

                    // Set Interrupt signal
                    write_IrqAddr(i);
                    write_Irq(1);
                }
                break;
            }
        }
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(intrInput) {
    Uns32 input = PTR_TO_UNS32(userData);
    if(bport1_ab_data.MER.bits.HIE) {
        bport1_ab_data.ISR.value |= value << input;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Pin Intr_%d = %d", input, (Uns32)value);

        eval_status();
    } else {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Pin Intr_%d = %d"
                                       " : Hardware Interrupts disabled: Ignored",
                                       input, (Uns32)value);
    }
}

PPM_NET_CB(ackInput) {
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Fast Acknowledge %d", (Uns32)value);
    bport1_ab_data.ISR.value &= ~value;

    eval_status();

}

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

//
// Writing the IAR clears the ISR
//
PPM_REG_WRITE_CB(WriteIAR) {
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Acknowledge %d", FILTERENABLED(data));
    bport1_ab_data.ISR.value &= ~FILTERENABLED(data);
    eval_status();
}

PPM_REG_WRITE_CB(WriteIER) {
    bport1_ab_data.IER.value = FILTERENABLED(data);
    eval_status();
}

PPM_REG_WRITE_CB(WriteISR) {
    if(bport1_ab_data.MER.bits.HIE) {
        // can no longer write to the hardware interrupt bits, mask
        data &= ((1 << HWINTERRUPTS)-1);
    }
    bport1_ab_data.ISR.value = FILTERENABLED(data);
    eval_status();
}

PPM_REG_WRITE_CB(WriteMER) {
    bport1_ab_data.MER.value = FILTERENABLED(data);
    eval_status();
}

PPM_REG_WRITE_CB(WriteCIE) {
    if(state.hasCIE) {
        bport1_ab_data.IER.value &= ~FILTERENABLED(data);
        eval_status();
    } else {
        if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX, "CIE not present");
    }
}

PPM_REG_WRITE_CB(WriteSIE) {
    if(state.hasSIE) {
        bport1_ab_data.IER.value |= FILTERENABLED(data);
        eval_status();
    } else {
        if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX, "SIE not present");
    }
}

PPM_REG_WRITE_CB(WriteIMR) {
    if(state.hasIMR) {
        *(Uns32*)user = FILTERENABLED(data);
        eval_status();
    } else {
        if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX, "IMR not present");
    }
}

PPM_REG_WRITE_CB(WriteIPR) {
    if (PSE_DIAG_MEDIUM) bhmMessage("W", PREFIX,
                        "Attempt to write read-only IPR%s",
                        state.hasIPR ? "" : "(not present)");

    if(state.hasIPR) {
        *(Uns32*)user = FILTERENABLED(data);
    }
}
PPM_REG_READ_CB(ReadIPR) {
    Uns32 value = 0;
    if(state.hasIPR) {
        value = *(Uns32*)user;
    } else {
        if (PSE_DIAG_HIGH) bhmMessage("W", PREFIX, "IPR not present");
    }
    return value;
}


PPM_NBYTE_WRITE_CB(WriteIVAR) {
    Uns32 index = (offset-0xc)/0x4;

    if(bytes != 4) {
        bhmMessage("W", PREFIX, "IVAR write bytes %d, expected 4", bytes);
    }

    if( index <= ALLINTERRUPTS) {
        memcpy(&(bport1_ab_data.IVAR[index].value), data, bytes);
    } else {
        if (PSE_DIAG_MEDIUM) bhmMessage("W", PREFIX, "IVAR index %d above enabled interrupts %d",
                                      index, ALLINTERRUPTS);
    }
}

PPM_NBYTE_READ_CB(ReadIVAR) {
    Uns32 index = (offset-0x100)/0x4;

    if(bytes != 4) {
        bhmMessage("W", PREFIX, "IVAR read bytes %d, expected 4", bytes);
    }

    if( index <= ALLINTERRUPTS) {
        memcpy(data, &(bport1_ab_data.IVAR[index].value), bytes);
    } else {
        if (PSE_DIAG_MEDIUM) bhmMessage("W", PREFIX, "IVAR index %d above enabled interrupts %d",
                                      index, ALLINTERRUPTS);
    }

}


PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    // Get configuration (Vivado Design Suite Options)
    bhmBoolParamValue("C_HAS_IPR",          &state.hasIPR);
    bhmBoolParamValue("C_HAS_SIE",          &state.hasSIE);
    bhmBoolParamValue("C_HAS_CIE",          &state.hasCIE);
    bhmBoolParamValue("C_HAS_IMR",          &state.hasIMR);
    bhmBoolParamValue("C_HAS_FAST",         &state.hasFAST);

    bhmBoolParamValue("C_EN_CASCADE_MODE",  &state.enableCASCADE);
    bhmBoolParamValue("C_CASCADE_MASTER",   &state.setCASCADEMASTER);
    if(state.enableCASCADE || state.setCASCADEMASTER) {
        if (PSE_DIAG_MEDIUM)
            bhmMessage("W", PREFIX, "Cascaded operation is not available");
    }

    bhmUns32ParamValue("C_NUM_INTR_INPUTS", &state.numberINTR);
    bhmUns32ParamValue("C_NUM_SW_INTR",     &state.numberSWINTR);
    if(ALLINTERRUPTS > 32){
        bhmMessage("W", PREFIX, "Interrupt Configuration exceeds maximum"
                                "HW/SW Interrupts %d/%d",
                state.numberINTR, state.numberSWINTR);
        if(state.numberINTR < 32) {
            state.numberSWINTR = 32 - state.numberINTR;
            bhmMessage("I", PREFIX, "SW Interrupts reduced to %d",
                            state.numberSWINTR);
        }
    }

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

