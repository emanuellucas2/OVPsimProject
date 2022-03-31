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

#include "hostapi/impAlloc.h"

#include "op/op.h"

#define MODULE_NAME "nativeMemory"

typedef struct optModuleObjectS {
    Uns32 msize;    // size of allocated memory
    void *mem;      // allocated memory
} optModuleObject;

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // create native memory (64K)
    object->msize = 0x10000;
    object->mem   = STYPE_ALLOC_N(Uns8, object->msize);

    // terminate if memory allocation failed
    if (!object->mem)
        opMessage("F", "MODULE", "Failed to allocate native memory");

    // get first bus in module
    optBusP bus = opBusNext(mi, NULL);
    if (!bus)
        opMessage("F", "MODULE", "Did not find a bus in module '%s'", opObjectName(mi));

    // connect memory to bus at address range 0x0000:0xffff
    opMemoryNativeNew(
        mi, "native", OP_PRIV_RWX, object->msize-1, object->mem,
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "sp1", .addrLo=0x0, .addrHi=object->msize-1)
            )
        ),
        0
    );
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    // insert pre simulation code here
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // free native memory
    STYPE_FREE(object->mem);
}

#include "module.igen.h"
