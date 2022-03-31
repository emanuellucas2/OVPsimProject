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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define MODULE_NAME "top"

int main(int argc, const char *argv[]) {
    const char *save    = 0;
    const char *restore = 0;
    opSessionInit(OP_VERSION);
    
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "save",    0, "file", "platform", OP_FT_STRINGVAL, &save,    "save",    0, 0, 0);
    opCmdParserAdd(parser, "restore", 0, "file", "platform", OP_FT_STRINGVAL, &restore, "restore", 0, 0, 0);
    opCmdParseArgs(parser, argc, argv);
    
    optModuleP mi = opRootModuleNew(0, MODULE_NAME, 0);

    opModuleNew( mi, "module", "u1", 0,0);
    opRootModulePreSimulate(mi);
    
    if(restore) {
        opPrintf("Restoring\n");
        opRootModuleStateRestoreFile(mi, restore);

        opPrintf("Running\n");
        opRootModuleSimulate(mi);
    } else if(save) {
        opPrintf("Running (to instruction 100)\n");
        optProcessorP processor = opObjectByName(mi, "u1/cpu1", OP_PROCESSOR_EN).Processor;
        opProcessorBreakpointICountSet(processor, 100);

        opRootModuleSimulate(mi);
        opPrintf("Saving\n");
        opRootModuleStateSaveFile(mi, save);
    } else {
        opPrintf("Running\n");
        opRootModuleSimulate(mi);
    }
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

