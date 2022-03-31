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


// This file declares functions to be implemented by the user.
// Be careful to avoid overwriting any edits should igen be re-run.


#include <string.h>
#include <stdlib.h>

#include "op/op.h"


// Change the name here if required.

#define MODULE_NAME "top"

typedef struct optModuleObjectS {
    // insert module persistent data here

    optNetP topNetRecv;
    optNetP topNetDrive;

} optModuleObject;

static OP_NET_WRITE_FN(netCallback) {

    opPrintf("uut: netCallback: topNetRecv = %u\n", (Uns32)value);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    opCmdParseStd(MODULE_NAME, OP_AC_ALL, argc, argv);

    optModuleP top = opRootModuleNew(0, 0, 0);

    optNetP topNetDrive = opNetNew(top, "topNetDrive", 0, 0);
    optNetP topNetRecv  = opNetNew(top, "topNetRecv", 0, 0);

    optModuleP mi = opModuleNew(top, "module", "uut",
        OP_CONNECTIONS(
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(topNetDrive, "netInPort"),
                OP_NET_CONNECT(topNetRecv, "netOutPort")
            )
        ),
        0
    );

    opPrintf("%s: setting up callback on net '%s'\n",
                                opObjectHierName(mi),
                                opObjectHierName(topNetRecv));

    opNetWriteMonitorAdd(topNetRecv, netCallback, 0);

    opRootModulePreSimulate(top);

    opPrintf("%s: simulate: writing net '%s' to 0\n",
                                opObjectHierName(mi),
                                opObjectHierName(topNetRecv));
    opNetWrite(topNetDrive, 0);

    opPrintf("%s: simulate: writing net '%s' to 1\n",
                                opObjectHierName(mi),
                                opObjectHierName(topNetRecv));
    opNetWrite(topNetDrive, 1);

    opPrintf("%s: simulate: done\n", opObjectHierName(mi));

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

