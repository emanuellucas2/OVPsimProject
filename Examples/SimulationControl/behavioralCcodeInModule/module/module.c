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


#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define MODULE_NAME "Module"
#define MY_MODULE_NAME "Module"

typedef struct optModuleObjectS {
    // insert module persistent data here

    optNetP netIn;
    optNetP netOut;

} optModuleObject;

#define NETIN    "netIn"
#define NETOUT   "netOut"

//
// This function is called when the input net is written
// It writes a value 0 or 1 to the output net
// as the inverse of the input net being set or zero respectively
//
static OP_NET_WRITE_FN(netCallback) {
    optModuleObjectP object = userData;

    Uns32 newValue = (value) ? 0 : 1;
    opPrintf("%g: sub_netCallback: %s = %u\n",
                         (double)opModuleCurrentTime(opObjectRootModule(object->netOut)),
                         opObjectHierName(object->netOut), newValue);

    opNetWrite(object->netOut, newValue);
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

    opPrintf("\nmodulePreSimulate: %s setting up callback on " NETIN "\n", opObjectHierName(mi));

    //
    // Get handles to the two nets
    //
    object->netIn  = opObjectByName(mi, NETIN,  OP_NET_EN).Net;
    object->netOut = opObjectByName(mi, NETOUT, OP_NET_EN).Net;

    // ensure nets have been found
    assert(object->netIn != NULL && object->netOut != NULL);

    opNetWriteMonitorAdd(object->netIn, netCallback, object);

    opPrintf("modulePreSimulate: %s done\n", opObjectHierName(mi));
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
