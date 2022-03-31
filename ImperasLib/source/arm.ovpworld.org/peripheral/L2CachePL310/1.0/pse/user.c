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
//                             Version 20110906.3
//                          Tue Oct 25 21:20:20 2011
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readAux) {
    return 0x02020000;
}

PPM_REG_READ_CB(readCleanInvWay) {

    return 0;
}

PPM_REG_READ_CB(readCleanWay) {

    return 0;
}

PPM_REG_READ_CB(readCtrl) {
    // YOUR CODE HERE (readCtrl)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readId) {
    return 0x410000C8;
}

PPM_REG_READ_CB(readInvWay) {
    return 0;
}

PPM_REG_READ_CB(readType) {
    return 0x1C100100;
}

PPM_REG_WRITE_CB(writeAux) {
    // YOUR CODE HERE (writeAux)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCtrl) {
    // YOUR CODE HERE (writeCtrl)
    *(Uns32*)user = data;
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

