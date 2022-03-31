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

#define HARNESS_NAME "harness"

// Name of the nets
#define TOPNETDRV        "topNetDrive"
#define TOPNETRECV       "topNetRecv"
// name of the module ports
#define TOPNETDRVPORT    "slavePort"
#define TOPNETRECVPORT   "masterPort"
// net handles
optNetP topNetDrive;
optNetP topNetRecv;

static OP_NET_WRITE_FN(netCallback) {
    optNetP net = userData;
    opPrintf("%g: top_netCallback: %s = %d\n", (double)opModuleCurrentTime(opObjectRootModule(net)), opObjectHierName(net), (Uns32)value);
}

static void monitorNets(optModuleP mi) {
    opPrintf("\nmonitorNets: %s : setting up callback on nets\n", HARNESS_NAME);

    if(!topNetDrive) {
        opMessage("E", HARNESS_NAME, "Cannot find net '" TOPNETDRV "' in module");
    }
    if(!topNetRecv) {
        opMessage("E", HARNESS_NAME, "Cannot find net '" TOPNETRECV "' in module");
    }

    opNetWriteMonitorAdd(topNetRecv, netCallback, topNetRecv);

    opPrintf("monitorNets: %s : done\n", HARNESS_NAME);
}

static void constructModule(optModuleP mi) {
    topNetDrive = opNetNew(mi, TOPNETDRV, 0, 0);
    topNetRecv  = opNetNew(mi, TOPNETRECV, 0, 0);

    opModuleNew(
        mi,       // parent module
        "module/model",       // modelfile
        "u1",   // name
        OP_CONNECTIONS(
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(topNetDrive, "slavePort"),
                OP_NET_CONNECT(topNetRecv, "masterPort")
            )
        ),
        0
    );
}

static void simulate(optModuleP mi) {
    opPrintf("\n%g: simulate: %s starting\n", (double)opModuleCurrentTime(mi), HARNESS_NAME);

    opRootModuleSetSimulationStopTime(mi, 0.001) ;
    opRootModuleSimulate(mi);

    opPrintf("\n%g: simulate: %s writing 0\n", (double)opModuleCurrentTime(mi), opObjectHierName(topNetDrive));
    opNetWrite(topNetDrive, 0);

    opRootModuleSetSimulationStopTime(mi, 0.002);
    opRootModuleSimulate(mi);

    opPrintf("\n%g: simulate: %s writing 1\n", (double)opModuleCurrentTime(mi), opObjectHierName(topNetDrive));
    opNetWrite(topNetDrive, 1);

    opRootModuleSetSimulationStopTime(mi, 0.003);
    opRootModuleSimulate(mi);

    opPrintf("\n%g: simulate: %s done\n\n", (double)opModuleCurrentTime(mi), HARNESS_NAME);
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    optModuleP mi = opRootModuleNew(0, 0, 0);
    constructModule(mi);

    monitorNets(mi);

    opNetShow(topNetDrive);
    opNetShow(topNetRecv);

    opRootModulePreSimulate(mi);
    simulate(mi);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

/* from a module.op.tcl
ihwnew -name module

ihwaddnet -instancename topNetDrive
ihwaddnet -instancename topNetRecv

ihwaddmodule -instancename u1 -modelfile module/model
ihwconnect -instancename u1 -netport slavePort -net topNetDrive
ihwconnect -instancename u1 -netport masterPort -net topNetRecv
*/
