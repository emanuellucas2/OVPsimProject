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


#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define MODULE_NAME "simpleCpuMemoryUart"

typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;

static OP_NET_WRITE_FN(netCallback) {
    optNetP net = userData;
    opPrintf("netCallback(%s) = %c\n", opObjectName(net), (Uns32)value);
}

////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {

    // set up net monitoring
    optNetP net = 0;
    while ((net = opNetNext(mi, net))) {
        opPrintf ("monitorNets(%s)\n", opObjectHierName(net));
        opNetWriteMonitorAdd(net, netCallback, net);
    }
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}

#include "module.igen.h"
