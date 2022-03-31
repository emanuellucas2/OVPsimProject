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
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

#include "pse.igen.h"

#define PREFIX "TRAP"

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(readMemCB) {

    Uns32 offset = addr - handles.bport1;
    Uns32 ret    = 0;

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "%d byte read at offset %d (0x%x)", bytes, offset, offset);
    }

    switch (bytes) {
    case 1: ret = *(Uns8 *) addr; break;
    case 2: ret = *(Uns16 *)addr; break;
    case 4: ret = *(Uns32 *)addr; break;
    default:
        bhmMessage("E", PREFIX, "Unsupported %d byte read at offset %d (0x%x)", bytes, offset, offset);
        break;
    }
    return ret;
}

PPM_WRITE_CB(writeMemCB) {

    Uns32 offset = addr - handles.bport1;

    if (PSE_DIAG_LOW) {
        bhmMessage(
            "I", PREFIX, "%d byte write value=0x%x at offset %d (0x%x)", bytes, data, offset, offset);
    }

    switch (bytes) {
    case 1: *(Uns8 *) addr = data; break;
    case 2: *(Uns16 *)addr = data; break;
    case 4: *(Uns32 *)addr = data; break;
    default:
        bhmMessage("E", PREFIX, "Unsupported %d byte write at offset %d (0x%x)", bytes, offset, offset);
        break;
    }

}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();


    Uns32 portAddress = 0;
    Uns32 portSize    = 1;

    // Get port size or set to default
    bhmUns32ParamValue("portSize", &portSize);

    // The user must set the port address in the platform
    if (!bhmUns32ParamValue("portAddress", &portAddress)) {
        bhmMessage("E", PREFIX, "portAddress parameter must be defined");

        // allow it to carry on for doc generation
        portAddress = 0;
    }

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "portAddress 0x%08x:0x%08x: portSize 0x%08x (%u)",
                portAddress, portAddress+portSize-1, portSize, (Uns32)portSize);
    }

    handles.bport1 = malloc(portSize*sizeof(Uns8));

    if(handles.bport1) {
        ppmCreateDynamicSlavePort(
                "bport1",               // slavePort,
                portAddress,            // slaveLoAddress,
                portSize*sizeof(Uns8),  // sizeInBytes,
                handles.bport1          // localLowAddress
        );
    } else {
        bhmMessage("E", PREFIX, "Failed to allocate memory (%u bytes)",
                (Uns32)(portSize*sizeof(Uns8)));
    }

    Bool implementCallbacks;
    bhmBoolParamValue("cbEnable", &implementCallbacks);
    if(implementCallbacks) {
        if(PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "Adding Read and Write callbacks");
        }
        // Add memory read and write callbacks instead of memory
        ppmInstallReadCallback(readMemCB,   0, handles.bport1, portSize*sizeof(Uns8));
        ppmInstallWriteCallback(writeMemCB, 0, handles.bport1, portSize*sizeof(Uns8));
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
