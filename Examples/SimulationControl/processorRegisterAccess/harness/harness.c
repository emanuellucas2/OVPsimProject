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
#define MODULE_INSTANCE "u1"

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd(MODULE_NAME, OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, MODULE_NAME, 0);

    const char *u1_path = "module";
    optModuleP mi = opModuleNew(
        mr,                 // parent module
        u1_path,            // modelfile
        MODULE_INSTANCE,    // name
        0,
        0
    );

    // get the handle for the processor in the module
    optProcessorP processor = opObjectByName(mi, "cpu1", OP_PROCESSOR_EN).Processor;

    // construction complete
    opRootModulePreSimulate(mr);

    Bool done = False;
    while(!done) {

        Uns32 currentPC = (Uns32)opProcessorPC(processor);

        // disassemble instruction at current PC
        opPrintf("** Instruction Disassemble\n");
        opPrintf(
            "0x%08x : %s\n",
                currentPC,
                opProcessorDisassemble(processor, currentPC, OP_DSA_NORMAL)
        );

        // execute one instruction and check for none scheduler return
        opPrintf("** Instruction Execution\n");
        done = (opProcessorSimulate(processor, 1) != OP_SR_SCHED);

        // dump registers
        opPrintf("** Register Dump\n");
        opProcessorRegDump(processor);
    }

    // print number of instructions executed at end of simulation and reason simulation stopped
    opPrintf(
        "Simulation finished, "FMT_64u" instructions executed, StopReason is '%s'\n",
                opProcessorICount(processor),
                opStopReasonString(opProcessorStopReason(processor))
    );

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

