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


#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define MODULE_NAME "dualCpuMemory"

typedef struct optModuleObjectS {
} optModuleObject;

//
// external memory read and write callback functions
//
OP_ADDR_WATCHPOINT_CONDITION_FN(memoryAccess) {
    Uns32 data = SWAP_4_BYTE(*(Uns32*)value);

    opMessage("I", "MEMORY_ACCESS", "%s %s at address 0x" FMT_Ax " (0x" FMT_Ax") data 0x%08x (%d)",
                processor ? opObjectHierName(processor) : "artifact", (const char *)userData, VA, PA, data, data);

    if (processor && (data == 610)) {
        opInterrupt();
    }

    if (processor && (data == 6765)) {
        opProcessorYield(processor);
    }

    // watchpoint does not cause simulation to stop
    return True;
}

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    // insert pre simulation code here
}

#define ADDRESSLOW   0xe0001004
#define ADDRESSHIGH  0xe0001007

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // get bus in the module
    optBusP busS = opObjectByName(mi, "busS", OP_BUS_EN).Bus;
    optWatchpointP wpW = 0;
    optWatchpointP wpR = 0;
    if(busS) {
        wpW = opBusWriteWatchpointNew (
                        busS,
                        ADDRESSLOW, ADDRESSHIGH,
                        "Write",
                        memoryAccess);
        wpR = opBusReadWatchpointNew (
                        busS,
                        ADDRESSLOW, ADDRESSHIGH,
                        "Read",
                        memoryAccess);
    }

    if (!busS || !wpW || !wpR) {
        opMessage("W", "SET_WATCH", "Failed to set watchpoint");
    } else {
        opMessage("I", "SET_WATCH", "Set Read and Write watchpoints 0x%08x to 0x%08x", ADDRESSLOW, ADDRESSHIGH);
    }
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}


#include "module.igen.h"
