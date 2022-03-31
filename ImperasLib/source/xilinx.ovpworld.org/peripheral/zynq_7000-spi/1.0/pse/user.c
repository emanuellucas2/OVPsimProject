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

#include <string.h>

#include "pse.igen.h"

#define PREFIX "SPI"

Uns32 spiAddress;       // the address of the current SPI access

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_REG_WRITE_CB(wrData) {
    *(Uns32*)user = (*(Uns32*)user & 0xfffffd00) | (data & 0x2ff);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_WD", "SPI Write 0x%08x:0x%08x", spiAddress, *(Uns32*)user);

    ppmWriteAddressSpace (handles.SPI,  spiAddress, sizeof(Uns32), (Uns32*)user);

    spiAddress +=4;         // increment address (4 byte registers access)

}

PPM_REG_READ_CB(rdData) {

    ppmReadAddressSpace (handles.SPI,  spiAddress, sizeof(Uns32), (Uns32*)user);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_RD", "SPI Read 0x%08x:0x%08x", spiAddress, *(Uns32*)user);

    spiAddress +=4;         // increment address (4 byte registers access)

    return *(Uns32*)user;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

