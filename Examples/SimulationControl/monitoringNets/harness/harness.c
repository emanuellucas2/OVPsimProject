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

#define HARNESS_NAME    "harness"
#define MODULE_DIR      "topmodule"
#define MODULE_INSTANCE "simpleHierarchy"

static OP_NET_WRITE_FN(netCallback) {
    optNetP net = userData;
    opPrintf("netCallback(%s) = %c\n", opObjectName(net), (Uns32)value);
}

static void monitorNets(optModuleP mi) {
    optModuleP mod;
    if (!(mod = opObjectByName (mi, MODULE_INSTANCE, OP_MODULE_EN).Module)) {
        opMessage ("F", "HN_MNE", "Can not find module(%s)", MODULE_INSTANCE);
    }

    optNetP net = 0;
    while ((net = opNetNext(mod, net))) {
        opPrintf ("monitorNets(%s)\n", opObjectHierName(net));
        opNetWriteMonitorAdd(net, netCallback, net);
    }
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (HARNESS_NAME, OP_AC_ALL, argc, argv);

    optModuleP mi = opRootModuleNew(0, 0, 0);
    opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    monitorNets(mi);

    opRootModuleSimulate(mi);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

