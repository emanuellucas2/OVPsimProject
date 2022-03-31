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
//                          Tue Sep 11 12:06:26 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writeCANCKSEL) {
    //
    // Apply the Write Masking
    //
    if (!(data & 0x1)) {
        bhmMessage("W", "CLKGEN", "Register CANCKSEL Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xfe) | (data & 0x1);
}

PPM_REG_WRITE_CB(writeCLM) {
    //
    // Apply the Write Masking
    //
    if (!(data & 0x3)) {
        bhmMessage("W", "CLKGEN", "Register CLM Illegal value 0x%02x\n", data);
    }

    //
    // the CLME bit can only be set, in order to clear, a system reset must be called
    //
    if (data & 0x1) {
        CLKGENP1_reg0_data.CLM.bits.CLME = 1;
    }

    Uns8 CLMD = (data >> 1) & 0x1;
    if (CLMD != CLKGENP1_reg0_data.CLM.bits.CLMD) {
        //
        // Error to change CLMD when CLME = 1
        //
        if (CLKGENP1_reg0_data.CLM.bits.CLME) {
            bhmMessage("E", "CLKGEN", "Register CLM.CLMD changed from %d to %d when CLM.CLME=1\n",
                CLKGENP1_reg0_data.CLM.bits.CLMD, CLMD);
        } else {
            CLKGENP1_reg0_data.CLM.bits.CLMD = CLMD;
        }
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

