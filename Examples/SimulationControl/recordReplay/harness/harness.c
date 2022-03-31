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

#define HARNESS_NAME        "harness"
#define MODULE_DIR          "module"
#define MODULE_INSTANCE     "u1"
#define PERIPHERAL_INSTANCE "uart0"

struct optionsS {
    Bool                 record;
    Bool                 replay;
    Bool                 useport;
} options = {
    .record  = 0,
    .replay  = 0,
    .useport = 0,
};

static void cmdParser(optCmdParserP parser) {
    opCmdParserAdd(parser, "myrecord", "", "bool", "myargs group", OP_FT_BOOLVAL, 
        &options.record, "Record from UART to file", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "myreplay", "", "bool", "myargs group" , OP_FT_BOOLVAL, 
        &options.replay, "Replay UART from file", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "myuseport", "", "bool", "myargs group" , OP_FT_BOOLVAL, 
        &options.useport, "Use manual port connection", OP_AC_ALL, 0, 0);
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    cmdParser(parser);
    opCmdParseArgs(parser, argc, argv);

    opParamBoolOverride(0, OP_FP_STOPONCONTROLC, 1);
    if (options.record) {
        opParamStringOverride(0, MODULE_INSTANCE "/" PERIPHERAL_INSTANCE "/" "record", "recdir/uart0.record");
    } else if (options.replay) {
        opParamStringOverride(0, MODULE_INSTANCE "/" PERIPHERAL_INSTANCE "/" "replay", "recdir/uart0.record");
    }
    if (options.useport) {
        opParamUns32Override(0, MODULE_INSTANCE "/" PERIPHERAL_INSTANCE "/" "portnum", 0);
    } else {
        opParamBoolOverride (0, MODULE_INSTANCE "/" PERIPHERAL_INSTANCE "/" "console", 1);
    }
    // stop when a UART console terminal is closed
    opParamBoolOverride (0, MODULE_INSTANCE "/" PERIPHERAL_INSTANCE "/" "finishOnDisconnect", 1);
 
    optModuleP mi = opRootModuleNew(0, 0, 0);
    opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    opRootModuleSimulate(mi);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

