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


#define MODULE_NAME "top"



static OP_BUS_SLAVE_READ_FN(readCallback) {
    const char *bus = userData;
    opPrintf("readCallback: %s, 0x"FMT_Ax "\n", bus, addr);
}

static OP_BUS_SLAVE_WRITE_FN(writeCallback) {
    const char *bus = userData;
    opPrintf("writeCallback: %s, 0x"FMT_Ax "\n", bus, addr);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mr = opRootModuleNew(0, MODULE_NAME, 0);

    //
    // create top level busses
    //
    optBusP topBusM_b = opBusNew(mr, "topBusM", 32, 0, 0);    // This is the bus that will be driven

    optBusP topBusS_b = opBusNew(mr, "topBusS", 32, 0, 0);

    //
    // Intance module
    //
    opModuleNew(
        mr,                                   // parent module
        "module/model." IMPERAS_SHRSUF,       // modelfile
        "uut",                                // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(topBusM_b, "busMport"),
                OP_BUS_CONNECT(topBusS_b, "busSport")
            )
        ),
        0                                     // parameters
    );

    //
    // Install callbacks (readCallback and writeCallback)
    // which will be called when this bus is accessed.
    //
    opPrintf("%s setting up callbacks on slave bus\n", opObjectHierName(mr));

    char *busName = "topBusS";
    optBusP bus = opObjectByName(mr, busName, OP_BUS_EN).Bus;
    opBusSlaveNew(bus, "all", 0, OP_PRIV_RWX, 0, 0xffffffff, readCallback, writeCallback, 0, busName);

    opPrintf("%s done\n", opObjectHierName(mr));

    // data to be written
    char b = 0xff;

    opPrintf("%s starting\n", opObjectHierName(mr));
    Addr base;
    for (base = 0; base < 0x1000*4; base += 0x1000) {
        opPrintf("%s reading and writing to 0x"FMT_Ax "\n", opObjectHierName(mr), base);
        Bool okRead  = opBusRead  (topBusM_b, 0, base, &b, sizeof(b), 0);
        Bool okWrite = opBusWrite (topBusM_b, 0, base, &b, sizeof(b), 0);
        opPrintf("%s           read: %u, write: %u\n", opObjectHierName(mr), okRead, okWrite);
    }
    opPrintf("%s done\n", opObjectHierName(mr));

    opRootModuleSimulate(mr);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

