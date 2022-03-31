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
//                           Version eng.20111102.0
//                          Tue Nov 15 13:13:57 2011
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////


PPM_REG_READ_CB(readPCellID0) {
    return 0x0d;
}

PPM_REG_READ_CB(readPCellID1) {
    return 0xf0;
}

PPM_REG_READ_CB(readPCellID2) {
    return 0x05;
}

PPM_REG_READ_CB(readPCellID3) {
    return 0xb1;
}

PPM_REG_READ_CB(readPeriphID0) {
    return 0x50;
}

PPM_REG_READ_CB(readPeriphID1) {
    return 0x13;
}

PPM_REG_READ_CB(readPeriphID2) {
    return 0x14;
}

PPM_REG_READ_CB(readPeriphID3) {
    return 0x0;
}


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();

    // YOUR CODE HERE (post constructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

