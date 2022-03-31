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
//                          Tue Feb 12 20:07:25 2013
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "RSTMGR"

typedef struct rstmgrDataS {

    Bool   cpu0ResetValue;     // status of CPU0 reset line
    Bool   cpu1ResetValue;     // status of CPU1 reset line

} rstmgrData, *rstmgrDataP;

static rstmgrData rstmgr;

//
// Bring the reset net up to date
//
static void updateReset(char *name, ppmNetHandle net, Uns32 assert, Bool *value) {

    Bool newValue = assert!=0;
    if (*value != newValue) {

        *value  = newValue;

        if (net) {

            // Status of reset line has changed
            if (PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "%s Reset changed to %d", name, newValue);
            }

            ppmWriteNet(net, newValue);

        }
    }
}

//
// Update the reset net outputs
//
static void Updatempumodrst() {
    updateReset("CPU0", handles.cpu0Reset, bport1_REGS_data.mpumodrst.bits.cpu0, &rstmgr.cpu0ResetValue);
    updateReset("CPU1", handles.cpu1Reset, bport1_REGS_data.mpumodrst.bits.cpu1, &rstmgr.cpu1ResetValue);
}

//////////////////////////////// Callback stubs ////////////////////////////////

//
// Write to mpumodrst register
// Only cpu0/1 resets bit fields supported
//
PPM_REG_WRITE_CB(Writempumodrst) {

    bport1_REGS_data.mpumodrst.value = data;

    Updatempumodrst();

}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    Updatempumodrst();
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

