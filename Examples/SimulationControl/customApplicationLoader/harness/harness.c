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

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd(HARNESS_NAME, OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, 0, 0);

    opModuleNew(mr, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    const char *loader = "loader/loader." IMPERAS_SHRSUF;
    if (!opApplicationLoaderInstall(loader)) {
        opMessage("F", HARNESS_NAME , "Failed to load application loader '%s'", loader);
    } else {
        opMessage("I", HARNESS_NAME , "Loaded application loader '%s'", loader);
    }

#ifdef LOADINPLATFORM
    // single processor in single module, so find it
    optModuleP mi = opModuleNext(mr, NULL);
    optProcessorP processor = opProcessorNext(mi, NULL);
    // application load (or on command line using --program <application>
    const char *application = "application/hello.OR1K.s19";
    if (!opProcessorApplicationLoad(processor, application, OP_LDR_SET_START | OP_LDR_FAIL_IS_ERROR | OP_LDR_VERBOSE, 0)) {
        opMessage("F", HARNESS_NAME "_ALF", "Failed to load application '%s'", application);
    } else {
        opMessage("I", HARNESS_NAME "_AL", "Loaded application '%s'", application);
    }
#endif

    opRootModuleSimulate(mr);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

