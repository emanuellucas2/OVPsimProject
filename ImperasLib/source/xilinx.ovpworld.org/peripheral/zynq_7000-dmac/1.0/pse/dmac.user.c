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

#include <string.h>

#include "pse.igen.h"

#define PREFIX "DMAC"


//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionReadNS) {
    Uns32 offset = addr - handles.bportNS;
    bhmMessage("W", PREFIX, "No Read Register Defined for Non-Secure access at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWriteNS) {
    Uns32 offset = addr - handles.bportNS;
    bhmMessage("W", PREFIX, "No Write Register Defined for Non-Secure access at offset 0x%04x", offset);
}

PPM_READ_CB(regNoDefinitionReadS) {
    Uns32 offset = addr - handles.bportS;
    bhmMessage("W", PREFIX, "No Read Register Defined for Secure access at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWriteS) {
    Uns32 offset = addr - handles.bportS;
    bhmMessage("W", PREFIX, "No Write Register Defined for Secure access at offset 0x%04x", offset);
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

