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
//                          Mon Sep 10 15:13:25 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writeBEC) {
    //
    // Check legal values
    //
    if (data & 0xAAAA) {
        bhmMessage("W", "BCU", "Register BEC Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = data & ~(0xAAAA);
}

//
// This register controls the Peripheral access window
//
PPM_REG_WRITE_CB(writeBPC) {
    //
    // Check legal values
    //
    if (data & 0x4000) {
        bhmMessage("W", "BCU", "Register BEC Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = data & ~(0x4000);
}

PPM_REG_WRITE_CB(writeBSC) {
    // YOUR CODE HERE (writeBSC)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeCSC1) {
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeCSCO) {
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeVSWC) {
    //
    // Only legal values are 0x37 or 0x24
    //
    if (data == 0x37 || data == 0x24) {
        *(Uns8*)user = data;
    } else {
        bhmMessage("W", "BCU", "Register VSWC Illegal value 0x%02x\n", data);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

