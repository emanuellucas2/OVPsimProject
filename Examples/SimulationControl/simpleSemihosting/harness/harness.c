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

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    optModuleP mi = opRootModuleNew(0, 0, 0);
    optModuleP u1 = opModuleNew(mi, "module", "u1", 0, 0);

    // add semihost library
    optProcessorP cpu1 = opObjectByName(u1, "cpu1", OP_PROCESSOR_EN).Processor;
    const char *shpath = opVLNVString(0, "ovpworld.org", "modelSupport", "imperasExit", 0, OP_EXTENSION, OP_VLNV_FATAL);
    opProcessorExtensionNew(cpu1, shpath, "sh1", 0);

    opRootModuleSimulate(mi);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}
