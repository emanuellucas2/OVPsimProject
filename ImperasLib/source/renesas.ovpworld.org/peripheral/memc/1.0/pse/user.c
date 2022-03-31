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
//                          Mon Sep 10 17:57:21 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writeAWC) {
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeBCC) {
    //
    // Apply the Write Masking
    //
    if (data & 0x5555) {
        bhmMessage("W", "MEMC", "Register BCC Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = data & 0xAAAA;
}

PPM_REG_WRITE_CB(writeBCT0) {
    //
    // Apply the Write Masking
    //
    if ((data & 0x7777) != 0x4444) {
        bhmMessage("W", "MEMC", "Register BCT0 Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = (*(Uns16*)user & 0x7777) | (data & 0x8888);
}

PPM_REG_WRITE_CB(writeBCT1) {
    //
    // Apply the Write Masking
    //
    if ((data & 0x7777) != 0x4444) {
        bhmMessage("W", "MEMC", "Register BCT1 Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = (data & 0x8888 ) | 0x4444;
}

PPM_REG_WRITE_CB(writeDVC) {
    //
    // Apply the Write Masking
    //
    if (data & 0x7e) {
        bhmMessage("W", "MEMC", "Register DVC Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = data & ~(0x7e);
}

PPM_REG_WRITE_CB(writeDWC0) {
    //
    // Apply the Write Masking
    //
    if (data & 0x8888) {
        bhmMessage("W", "MEMC", "Register DWC0 Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = data & 0x7777;
}

PPM_REG_WRITE_CB(writeDWC1) {
    //
    // Apply the Write Masking
    //
    if (data & 0x8888) {
        bhmMessage("W", "MEMC", "Register DWC1 Illegal value 0x%04x\n", data);
    }
    *(Uns16*)user = data & 0x7777;
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

