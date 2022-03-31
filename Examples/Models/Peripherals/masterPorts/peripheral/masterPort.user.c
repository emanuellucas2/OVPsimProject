/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

#include "pse.igen.h"

#define PREFIX "MASTER_PORT_PSE"

// The name of the master port
#define MPORTNAME "mport"

// A delay used in the peripheral
//#define DELAY QUANTUM_DELAY
#define DELAY 1000

////////////////////////////////////////////////////////////////////////////////
// Common functions to read and write
//    local memory space
//    master port address space
////////////////////////////////////////////////////////////////////////////////

// read a 32-bit value from an address space
void readAddressSpace(ppmAddressSpaceHandle addressSpace, Uns32 address) {
    Uns32 tmpBuffer = 0;
    // read 4 bytes from address on master port
    if(ppmReadAddressSpace(addressSpace, address, 4, &tmpBuffer)) {
        bhmMessage("I", PREFIX, "Address Space Read 0x%08x:0x%08x", address, tmpBuffer);
    } else {
        bhmMessage("E", PREFIX, "Failed to Read Address Space 0x%08x", address);
    }
}

// write a 32-bit value to an address space
void writeAddressSpace(ppmAddressSpaceHandle addressSpace, Uns32 address, Uns32 *data) {
    bhmMessage("I", PREFIX, "Address Space Write 0x%08x:0x%08x", address, *data);
    // write 4 bytes to address on master port
    if(ppmWriteAddressSpace(addressSpace, address, 4, data)) {
        bhmMessage("I", PREFIX, "Completed Address Space Write 0x%08x:0x%08x", address, *data);
    } else {
        bhmMessage("E", PREFIX, "Failed to Write Address Space 0x%08x", address);
    }

}

// read and display values from a local memory
void readLocalSpace (Uns32 *localSpace) {
    Uns32 i;
    bhmMessage("I", PREFIX, "Read localSpace[]");
    bhmPrintf("localSpace[]:");
    for (i=0; i<10; i++) {
        bhmPrintf(" 0x%08x", localSpace[i]);
    }
    bhmPrintf("\n\n");
}

// update a local memory with a walking 1 data
void updateLocalSpace (Uns32 *localSpace, Uns32 baseValue) {
    Uns32 i;
    bhmMessage("I", PREFIX, "Write localSpace[] (base 0x%08x)", baseValue);
    for (i=0; i<10; i++) {
        localSpace[i] = baseValue + (1<<i);
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_CONSTRUCTOR_CB(constructor) {

    // local variables
    Uns32 i;                        // loop variable
    Uns32 tmpBuffer;                // buffer holding read/write values
    Uns32 address = 0x10000000;        // address for base of mapped region and accesses
    Uns32 localSpace[10];            // local space mapped to master port

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "%s:", __FUNCTION__);

    //
    // Peripheral construction, connect ports, add registers etc
    //
    periphConstructor();

    //
    // Open a bus port and bridge remote bus to local memory
    // Local memory mapping to port
    //
    ppmExternalBusHandle busHandle;
    busHandle = ppmOpenMasterBusPort(MPORTNAME, &localSpace[0], sizeof(localSpace), address);
    if(!busHandle) {
        bhmMessage("E", PREFIX, "Bus Could not be opened as master port at 0x%08x", address);
    }

    //
    // wait for the simulation to start i.e. construction completed
    //
    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION));

    //
    // Master write access using mapped localSpace
    //
    bhmMessage("I", PREFIX, "Write localSpace[]");
    for (i=0; i<10; i++) {
        localSpace[i] = (1<<i);
    }

    //
    // Master read and write access using Address space
    //

    //
    // Read
    //
    if(ppmReadAddressSpace(handles.mport, address+0x10, 4, &tmpBuffer)) {
        bhmMessage("I", PREFIX, "Address Space Read 0x%08x:0x%08x", address+0x10, tmpBuffer);
    } else {
        bhmMessage("E", PREFIX, "Failed to Read Address Space 0x%08x", address+0x10);
    }

    //
    // Write
    //
    tmpBuffer = 0xa5a55a5a;
    bhmMessage("I", PREFIX, "Address Space Write 0x%08x:0x%08x", address+0x10, tmpBuffer);
    if(ppmWriteAddressSpace(handles.mport, address+0x10, 4, &tmpBuffer)) {
        bhmMessage("I", PREFIX, "Completed Address Space Write at 0x%08x", address+0x10);
    } else {
        bhmMessage("E", PREFIX, "Failed to Write Address Space 0x%08x", address+0x10);
    }

    //
    // Master read access using mapped localSpace
    //
    bhmMessage("I", PREFIX, "Read localSpace[]");
    bhmPrintf("localSpace[]:");
    for (i=0; i<10; i++) {
        bhmPrintf(" 0x%08x", localSpace[i]);
    }
    bhmPrintf("\n");

    ppmChangeRemoteLoAddress(busHandle, 0x20000000);

    bhmMessage("I", PREFIX, "Read localSpace[]");
    bhmPrintf("localSpace[]:");
    for (i=0; i<10; i++) {
        bhmPrintf(" 0x%08x", localSpace[i]);
    }
    bhmPrintf("\n");

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

