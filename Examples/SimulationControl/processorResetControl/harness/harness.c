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

    // construction complete
    opRootModulePreSimulate(mr);

    // get reset nets
    optNetP reset1 = opObjectByName(mi, "reset1", OP_NET_EN).Net;
    optNetP reset2 = opObjectByName(mi, "reset2", OP_NET_EN).Net;

    // Hold both processors in reset
    opMessage("I", "HARNESS", "Reset processor cpu1 and cpu2");
    opNetWrite(reset1, 1);
    opNetWrite(reset2, 1);

    opMessage("I", "HARNESS", "Simulate to 0.001");
    opRootModuleSetSimulationStopTime(mr, 0.001);
    opRootModuleSimulate(mr);

    // Release processor1
    opMessage("I", "HARNESS", "Release processor cpu1");
    opNetWrite(reset1, 0);
    opNetWrite(reset2, 1);

    opMessage("I", "HARNESS", "Simulate to End");
    opRootModuleSimulate(mr);

    opMessage("I", "HARNESS", "Simulation finished\n");

    // get the handle for the processor in the module
    optProcessorP processor = 0;
    while ((processor = opProcessorNext(mi, processor))) {
        // print number of instructions executed at end of simulation and reason simulation stopped
        opMessage("I", "HARNESS", "%s executed "FMT_64u" instructions, StopReason '%s'\n",
                    opObjectName(processor),
                    opProcessorICount(processor),
                    opStopReasonString(opProcessorStopReason(processor))
        );
    }


    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

