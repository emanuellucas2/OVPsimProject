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
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "GPC"

#define GPC_CNTR bport1_ab_data.GPC_CNTR
#define GPC_ISR1 bport1_ab_data.GPC_ISR1.value
#define GPC_ISR2 bport1_ab_data.GPC_ISR2.value
#define GPC_ISR3 bport1_ab_data.GPC_ISR3.value
#define GPC_ISR4 bport1_ab_data.GPC_ISR4.value

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

#define MODIFYBIT(_reg,_value,_bit)  _reg = ((_reg & ~(1<<_bit)) | (_value<<_bit))

PPM_NET_CB(interruptIn) {
    Uns32 intNumber = PTR_TO_UNS32(userData);
    Uns32 reg = (intNumber - 32) / 32;  // register containing changed bit
    Uns32 bit = (intNumber - 32) % 32;  // bit position in register

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "IRQ %d (ISR%d/%d)", intNumber, reg+1, bit);

    switch(reg) {
        case 0:
            MODIFYBIT(GPC_ISR1, value, bit);
            break;
        case 1:
            MODIFYBIT(GPC_ISR2, value, bit);
            break;
        case 2:
            MODIFYBIT(GPC_ISR3, value, bit);
            break;
        case 3:
            MODIFYBIT(GPC_ISR4, value, bit);
            break;
        default:
            bhmMessage("W", PREFIX, "Failed to update ISR register for int %d", intNumber);
            break;
    }
}

PPM_REG_WRITE_CB(WriteGPC_CNTR) {
    // YOUR CODE HERE (WriteGPC_CNTR)
    *(Uns32*)user = (*(Uns32*)user & 0xffdffffc) | (data & 0x200003);
    if(GPC_CNTR.bits.VPU_PUP) {
        GPC_CNTR.bits.VPU_PUP = 0; // self cleared
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "GPU/VPU Power Up Request");
    }
    if(GPC_CNTR.bits.VPU_PDN) {
        GPC_CNTR.bits.VPU_PDN = 0; // self cleared
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "GPU/VPU Power Down Request");
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

