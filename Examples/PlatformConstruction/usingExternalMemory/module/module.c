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

#define MODULE_NAME "externalMemory"

typedef struct optModuleObjectS {
} optModuleObject;

//
// external memory read and write callback functions
//
OP_BUS_SLAVE_READ_FN(extMemoryRead) {
    opMessage("I", "EXTERNAL_MEMORY_READ", "%s access at address 0x" FMT_Ax,
                initiator.Processor ? opObjectHierName(initiator.Processor) : "artifact", addr);
    // dummy data value
    *(Uns32 *)data = 0xfeedface;
}
OP_BUS_SLAVE_WRITE_FN(extMemoryWrite) {
    opMessage("I", "EXTERNAL_MEMORY_WRITE", "%s access at address 0x" FMT_Ax " data 0x%08x",
            initiator.Processor ? opObjectHierName(initiator.Processor) : "artifact", addr, *(Uns32 *)data);
}

//
// callbacks causing an access to abort if called
//
OP_BUS_SLAVE_READ_FN(extAbortRead) {
    opMessage("I", "MEMORY_READ_ABORT", "%s access at address 0x" FMT_Ax,
            initiator.Processor ? opObjectHierName(initiator.Processor) : "artifact", addr);
    opProcessorReadAbort(initiator.Processor, addr);
}
OP_BUS_SLAVE_WRITE_FN(extAbortWrite) {
    opMessage("I", "MEMORY_WRITE_ABORT", "%s access at address 0x" FMT_Ax,
            initiator.Processor ? opObjectHierName(initiator.Processor) : "artifact", addr);
    opProcessorWriteAbort(initiator.Processor, addr);
}

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // get bus in the module (only one)
    optBusP bus = opBusNext(mi, 0);
    opBusSlaveNew(bus, "externalRW", 0,
                        OP_PRIV_RW,
                        0x00400000, 0x004000ff,
                        extMemoryRead, extMemoryWrite,
                        0, 0);
    opBusSlaveNew(bus, "abort", 0,
                        OP_PRIV_RW,
                        0x00400100, 0x0040010f,
                        extAbortRead, extAbortWrite,
                        0, 0);
    opBusSlaveNew(bus, "externalR", 0,
                        OP_PRIV_R,
                        0x00400110, 0x00400fff,
                        extMemoryRead, extMemoryWrite,
                        0, 0);
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
}

static OP_DESTRUCT_FN(moduleDestruct) {
}

#include "module.igen.h"
