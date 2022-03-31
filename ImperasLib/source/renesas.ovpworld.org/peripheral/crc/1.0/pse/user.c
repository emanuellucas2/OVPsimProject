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
//                          Tue Sep 11 15:35:02 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writeCCRCD0) {
    // YOUR CODE HERE (writeCCRCD0)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCD1) {
    // YOUR CODE HERE (writeCCRCD1)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCD2) {
    // YOUR CODE HERE (writeCCRCD2)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCD3) {
    // YOUR CODE HERE (writeCCRCD3)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCD4) {
    // YOUR CODE HERE (writeCCRCD4)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCIN0) {
    // YOUR CODE HERE (writeCCRCIN0)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCIN1) {
    // YOUR CODE HERE (writeCCRCIN1)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCIN2) {
    // YOUR CODE HERE (writeCCRCIN2)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCIN3) {
    // YOUR CODE HERE (writeCCRCIN3)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCCRCIN4) {
    // YOUR CODE HERE (writeCCRCIN4)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeCRCC) {
    //
    // Perform write bit mask
    //
    *(Uns32*)user = data & (0x00001F07);
}

PPM_REG_WRITE_CB(writeDCRCD) {
    // YOUR CODE HERE (writeDCRCD)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeDCRCIN) {
    // YOUR CODE HERE (writeDCRCIN)
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

