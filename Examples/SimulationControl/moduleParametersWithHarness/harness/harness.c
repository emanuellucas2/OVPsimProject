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

// Set the defines to show alternate ways of setting parameters
#define PARAMLIST
//#define TOPLEVEL
// Define separate formal parameters for each sub module uart (set dualbase in topmodule/module.op.tcl)
#define DUALBASE

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    // root module
    optModuleP mi = opRootModuleNew(0, 0, 0);

#ifdef PARAMLIST
    opMessage("I", "HARNESS", "Define parameters using optParamP parameter list");
    optParamP paramList = NULL;

#ifdef TOPLEVEL
    // Set formal parameter on the top level module to change uart addresses in submodule
    opMessage("I", "HARNESS", "Set formal parameters on topmodule");
    paramList = opParamUns64Set(paramList,  "subUart0Address",        0x100003e8);
#ifdef DUALBASE
    // Two separate base addresses at top level
    paramList = opParamUns64Set(paramList,  "subUart1Address",        0x100003f8);
#endif
#else /* !TOPLEVEL */
    // Set formal parameter directly on the sub level module to change uart addresses on UARTs
    opMessage("I", "HARNESS", "Set formal parameters on submodule");
    paramList = opParamUns64Set(paramList,  "subUart0/baseAddress",   0x100003e8);
    paramList = opParamUns64Set(paramList,  "subUart1/baseAddress",   0x100003f8);
#endif

    // Set parameter on instance of uarts to set logfiles
    paramList = opParamStringSet(paramList, "subUart0/uart0/outfile", "subUart0-uart0.txt");
    paramList = opParamStringSet(paramList, "subUart1/uart0/outfile", "subUart1-uart0.txt");

    // instance the topmodule into the root module
    opModuleNew(mi, "./topmodule", "top", 0, paramList);

#else /* !PARAMLIST */

    opMessage("I", "HARNESS", "Define parameters using OP_PARAMS Macro list");
    // instance the topmodule into the root module
    opModuleNew(mi, "./topmodule", "top", 0,
            OP_PARAMS (
                    OP_PARAM_UNS64_SET  ("subUart0/baseAddress",      0x100003e8),
                    OP_PARAM_UNS64_SET  ("subUart1/baseAddress",      0x100003f8),
                    OP_PARAM_STRING_SET ("subUart0/uart0/outfile",    "subUart0-uart0.txt"),
                    OP_PARAM_STRING_SET ("subUart1/uart0/outfile",    "subUart1-uart0.txt")
                     )
            );
#endif

    // run simulation
    opRootModuleSimulate(mi);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

