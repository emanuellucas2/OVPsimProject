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
#include "ocl/oclhttp.h"


#define MODULE_NAME "processorExternalInterrupt"
#define PREFIX "MOD_INT"


typedef struct optModuleObjectS {
    // insert module persistent data here
    optModuleP  mi;
    optNetP     intNet;
    Uns32       intNetValue;
    const char  *intNetName;
} optModuleObject;


static OCL_HTTP_GET_FN(get) {
    optModuleObjectP object = userData;
    oclHTTPElementOpen(ch, "ovpelement");

    oclHTTPKeyPrintf(ch, "moduleInstName0", opObjectName(object->mi));
    oclHTTPKeyPrintf(ch, "moduleSimTime0","%g", (double)opModuleCurrentTime(opObjectRootModule(object->intNet)) );
    oclHTTPKeyPrintf(ch, "netName0", object->intNetName);
    oclHTTPKeyPrintf(ch, "netValue0", "%d", object->intNetValue);
    oclHTTPKeyPrintf(ch, "led0", "%d", object->intNetValue);

    oclHTTPKeyPrintf(ch, "power0", "0");
    oclHTTPElementClose(ch, "ovpelement");
    oclHTTPSend(ch);
}

static OCL_HTTP_POST_FN(post) {
    optModuleObjectP object = userData;
    if (strstr(body, "power0=clicked")) {
        opMessage("I", PREFIX "_SW", "Power Switch pushed - terminating simulation.");
        opModuleFinish(object->mi, 0);
    }
}

static OP_NET_WRITE_FN(netCallback) {
    optModuleObjectP object = userData;
    object->intNetValue = value;
}

static void monitorNets(optModuleObjectP object) {
    optNetP net = opObjectByName (object->mi, "tickInterrupt", OP_NET_EN).Net;
    if (!net) {
        opMessage ("F", "NNF", "monitorNets (net not found)");
    } else {
        opPrintf ("monitorNets(%s)\n", opObjectHierName(net));
        opNetWriteMonitorAdd(net, netCallback, object);
        object->intNet = net;
        object->intNetName = opObjectName(net);
    }
}

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    Uns32 httpvisportnum  = opObjectParamUns32Value (mi,   "httpvisportnum" , 0);
    octHTTPMethods m = { .get=get, .post=post, .userData=object };
    opModuleHTTPOpen(mi, &m, httpvisportnum, "httpvis");
    object->mi = mi;
    monitorNets (object);
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
