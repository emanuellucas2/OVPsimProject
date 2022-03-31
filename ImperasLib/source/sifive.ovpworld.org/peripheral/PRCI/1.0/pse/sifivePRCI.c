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
//////////////////////////////// Callback stubs ////////////////////////////////

// holds reset value, can be configured from default using parameter
static Uns32 corepllcfg0_Reset;

PPM_REG_WRITE_CB(hfxosccfgWrite) {
    // YOUR CODE HERE (hfxosccfgWrite)
    *(Uns32*)user = (*(Uns32*)user & 0xbfffffff) | (data & 0x40000000);
}

PPM_NET_CB(resetCB) {
    // YOUR CODE HERE (resetCB)
    reset_reset(1,0);
    // update value of corepllcfg0
    bport1_REG_data.corepllcfg0.value = corepllcfg0_Reset;
}

PPM_READ_CB(reservedRD) {
    // YOUR CODE HERE (reservedRD)
    return 0;
}

PPM_WRITE_CB(reservedWR) {
    // YOUR CODE HERE (reservedWR)
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    // get reset value from parameter
    bhmUns32ParamValue("corepllcfg0_Reset", &corepllcfg0_Reset);

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


