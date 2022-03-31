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
//                          Fri Sep 13 15:57:01 2013
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(read_ev) {
    // YOUR CODE HERE (read_ev)
    return 0;
}

PPM_REG_READ_CB(read_hi) {
    // YOUR CODE HERE (read_hi)
    return 0;
}

PPM_REG_READ_CB(read_lo) {
    // YOUR CODE HERE (read_lo)
    return 0;
}

PPM_REG_WRITE_CB(write_ev) {
    // YOUR CODE HERE (write_ev)
}

PPM_REG_WRITE_CB(write_hi) {
    // YOUR CODE HERE (write_hi)
}

PPM_REG_WRITE_CB(write_lo) {
    // YOUR CODE HERE (write_lo)
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

