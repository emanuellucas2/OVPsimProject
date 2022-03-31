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
#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"

struct optionsS {
    Bool         myarg;
    const char*  newstring;
} options = {
    .myarg = 0,
    .newstring = NULL,
};

OP_CMD_ERROR_HANDLER_FN(localErrorHandler) {
    opMessage("I", HARNESS_NAME, "localErrorHandler called and Argument (flag) not recognized (%s)", flag);
    return 1;
}

static void cmdParser(optCmdParserP parser) {
    opCmdParserAdd(parser, "myarg",    "m", "bool",   "myargs group", OP_FT_BOOLVAL,   &options.myarg,     "This is my description [default: 0]", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "newstring", 0 , "string", "myargs group", OP_FT_STRINGVAL, &options.newstring, "A new string",                        OP_AC_ALL, 0, 0);
    opCmdErrorHandler(parser, localErrorHandler, 0);
}

static void cmdParserCheck(optCmdParserP parser) {
    if (!opCmdArgUsed (parser,"program")) {
        opMessage("F", HARNESS_NAME, "Argument '--program' must be specified");
    }
    if (options.myarg) {
        opMessage("I", HARNESS_NAME, "Argument 'myarg' specified");
    }
    if (options.newstring) {
        opMessage("I", HARNESS_NAME, "Argument 'newstring' specified (\"%s\")", options.newstring);
    }
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    cmdParser(parser);
    if (!opCmdParseArgs(parser, argc, argv)) {
        opMessage("E", HARNESS_NAME, "Command line parse incomplete");
    }
    cmdParserCheck(parser);
    opMessage("I", HARNESS_NAME, "Application specified as %s ", opCmdDefaultApplication());

    optModuleP mi = opRootModuleNew(0, 0, 0);
    opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);
    opRootModuleSimulate(mi);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

