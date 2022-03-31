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
//                          Fri Jan  6 11:38:59 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "RING_OSC"

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

PPM_REG_READ_CB(ReadCOUNT) {

    // if memory connected update
    if(handles.rocount) {
        Bool ok = ppmReadAddressSpace(handles.rocount, 0, sizeof(Uns32), (Uns32*)user);
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_CRD", "Updating RO Count Data (%s)", ok ? "ok" : "failed");
    }

    bhmMessage("I", PREFIX "_COUNT","Read Temperature Count (%d)", *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadCAPTURE_TIME) {
    bhmMessage("I", PREFIX "_CTR","Read Capture Time (%d)", *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteCAPTURE_TIME) {
    bhmMessage("I", PREFIX "_CTW","Write Capture Time (%d)", (Uns32)data);
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteINIT_TIME) {
    *(Uns32*)user = data;
    bhmMessage("I", PREFIX "_CTW","Write Init Time (%d) and Control 0x%02x",
                                bport1_REG_data.INIT_TIME.bits.INIT,
                                bport1_REG_data.INIT_TIME.bits.CTRL);
}

PPM_REG_READ_CB(ReadINIT_TIME) {
    bhmMessage("I", PREFIX "_ITR","Read Init Time (%d) and Control 0x%02x",
            bport1_REG_data.INIT_TIME.bits.INIT,
            bport1_REG_data.INIT_TIME.bits.CTRL);
    return *(Uns32*)user;
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    Uns32 countInit;
    if(bhmUns32ParamValue("countinit", &countInit)) {
        bport1_REG_data.COUNT.value = countInit;
    }

    if(handles.rocount) {
        Bool ok = ppmWriteAddressSpace(handles.rocount, 0,
                                 sizeof(bport1_REG_data.COUNT.value),
                                 &bport1_REG_data.COUNT.value);

        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_CN", "Initializing RO Count Data (%s)",
                                           ok ? "ok" : "fail");
    }
}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}

