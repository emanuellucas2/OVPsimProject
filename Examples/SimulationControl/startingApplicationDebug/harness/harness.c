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

    optModuleP mi;

    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "configurecpuinstance", 0, 0, "user", OP_FT_BOOLVAL, &options.configurecpuinstance,
                           "Add configuration to enable debug to CPU instance", OP_AC_ALL, 0, 0);
    if (!opCmdParseArgs(parser, argc, argv)) {
        opMessage("W", HARNESS_NAME, "Command line parse incomplete");
    }

    // use a custom argument to control if we add to the processor instance configuration
    if (options.configurecpuinstance) {

        opMessage(
            "I", HARNESS_NAME,
            "Adding GDB Console override to root module and selecting %s for debug",
            MODULE_INSTANCE "/" CPU_INSTANCE
        );

        // enable debugging
        mi = opRootModuleNew(0, 0, OP_PARAMS (OP_PARAM_BOOL_SET(OP_FP_GDBCONSOLE, 1)));

        // configure the use of an alternate GDB with an initialisation file
        // opParamStringOverride(mi, MODULE_INSTANCE "/" CPU_INSTANCE "/" OP_FP_ALTERNATEGDBPATH, "/path/to/my/new/gdb/gdbexe");   // set a new GDB to use
        // opParamStringOverride(mi, MODULE_INSTANCE "/" CPU_INSTANCE "/" OP_FP_ALTERNATEGDBINIT, "gdb.init");                     // set a new initialisation file

        optModuleP u1 = opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

        // select the processor to debug
        // searching the module for all processors to find a match
        optProcessorP proc = NULL;
        while ((proc = opProcessorNext(u1, proc))) {
            opPrintf("found %s\n", opObjectName(proc));
            if (strcmp(CPU_INSTANCE, opObjectName(proc)) == 0) {
                opProcessorDebug(proc);
            }
        }
        // selecting a specific cpu instance by name
        //optProcessorP proc = opModuleObjectByHierName(mi, MODULE_INSTANCE "/" CPU_INSTANCE, OP_PROCESSOR_EN).Processor;
        //opProcessorDebug(proc);
    } else {
        // standard operation (use command line)
        mi = opRootModuleNew(0, 0, 0);
        opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);
    }

    opRootModuleSimulate(mi);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

