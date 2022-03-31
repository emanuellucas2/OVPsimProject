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

#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"

// Select one of the following to use as the command parse useMask option
#define USE_MASK OP_AC_ALL
//#define USE_MASK OP_AC_BASIC
//#define USE_MASK OP_AC_SIM
//#define USE_MASK OP_AC_NONE

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd(argv[0], USE_MASK, argc, argv);

    optModuleP mi = opRootModuleNew(0, 0, 0);
    opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    opRootModuleSimulate(mi);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

