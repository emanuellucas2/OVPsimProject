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
#define CPU_INSTANCE    "cpu1"

struct optionsS {
    Bool         configurecpuinstance;
} options = {
    .configurecpuinstance = False,
};

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "configurecpuinstance", 0, "bool", "user", OP_FT_BOOLVAL,
                           &options.configurecpuinstance,
                           "Add configuration to enable Imperas Intercepts to CPU instance",
                           OP_AC_ALL, 0, 0);
    if (!opCmdParseArgs(parser, argc, argv)) {
        opMessage("E", HARNESS_NAME, "Command line parse incomplete");
    }

    optModuleP mi = opRootModuleNew(0, 0, 0);

    // use a custom argument to control if we add to the processor instance configuration
    if (options.configurecpuinstance) {
        opMessage("I", HARNESS_NAME, "Adding Imperas intercept overrides to cpu instance %s", MODULE_INSTANCE "/" CPU_INSTANCE);
        opParamBoolOverride(mi, MODULE_INSTANCE "/" CPU_INSTANCE "/" OP_FP_ENABLEIMPERASINTERCEPTS, 1); // enabling intercepts
    }
    opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    opRootModuleSimulate(mi);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

