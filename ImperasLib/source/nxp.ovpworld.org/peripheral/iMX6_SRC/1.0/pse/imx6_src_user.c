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

#define PREFIX "SRC"

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

PPM_REG_READ_CB(ReadSRC_SCR) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_RSCR", "0x%08x", *(Uns32*)user);

    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadSRC_SIMR) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_RSIMR", "0x%08x", *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadSRC_SISR) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_RSISR", "0x%08x", *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadSRC_SRSR) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_RSRSR", "0x%08x", *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteSRC_SCR) {
    *(Uns32*)user = (*(Uns32*)user & 0xfd999000) | (data & 0x2666fff);

    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "SCR : CR1 EN %d C1 RST %d C0 RST %d",
                bport1_ab_data.SRC_SCR.bits.CORE1EN,
                bport1_ab_data.SRC_SCR.bits.CORE1_RST,
                bport1_ab_data.SRC_SCR.bits.CORE0_RST);
    }
    if(bport1_ab_data.SRC_SCR.bits.CORE1EN) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "SCR : Core 1 Enabled");

        if(ppmReadNet(handles.resetCore1)) {
            ppmWriteNet(handles.resetCore1, 0);
        }
    }
    if(bport1_ab_data.SRC_SCR.bits.CORE1_RST) {
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "SCR : Core 1 Reset");
        ppmWriteNet(handles.resetCore1, 1);
        ppmWriteNet(handles.resetCore1, 0);
    }
    if(bport1_ab_data.SRC_SCR.bits.CORE0_RST) {
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "SCR : Core 0 Reset");
        ppmWriteNet(handles.resetCore0, 1);
        ppmWriteNet(handles.resetCore0, 0);
    }

    // clear non-latching bits
    *(Uns32*)user = (*(Uns32*)user & 0xffd9cfe1);
}

PPM_REG_WRITE_CB(WriteSRC_SIMR) {
    *(Uns32*)user = (*(Uns32*)user & 0xfffffff0) | (data & 0xf);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_WSIMR", "0x%08x", *(Uns32*)user);

}

PPM_REG_WRITE_CB(WriteSRC_SRSR) {
    *(Uns32*)user = (*(Uns32*)user & 0xffefffff) | (data & 0x100000);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_WSRSR", "0x%08x", *(Uns32*)user);

    // clear status bits 6-0 that are written one
    *(Uns32*)user = (*(Uns32*)user & ~(data & 0x7d));
}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    ppmWriteNet(handles.resetCore1, 1);  // force core 1 into reset

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

