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

    optModuleP mr = opRootModuleNew(0, 0, 0);
    optModuleP mi = opModuleNew(mr, "module", "u1", 0, 0);

    opRootModulePreSimulate(mr);

    // Get first processor
    optProcessorP processor = opProcessorNext(mi, NULL);

    if(!processor)
        opMessage("F", "MODULE", "No Processor Found");

    opMessage("I", "MODULE", "Trace processor '%s'", opObjectName(processor));

    optStopReason stopreason = OP_SR_SCHED;
    while (stopreason == OP_SR_SCHED) {
        opProcessorSimulate(processor, 1);  // simulate a single instruction
        opPrintf(FMT_64d " : 0x" FMT_Ax " : %s\n",
                            opProcessorICount(processor),
                            opProcessorPC(processor),
                            opProcessorDisassemble(processor, opProcessorPC(processor), OP_DSA_NORMAL)
                );
        stopreason = opProcessorStopReason(processor);
    }
    opPrintf("Simulation finished, stop reason '%s' after " FMT_64u " instructions executed\n",
                                                 opStopReasonString(stopreason),
                                                 opProcessorICount(processor));

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

