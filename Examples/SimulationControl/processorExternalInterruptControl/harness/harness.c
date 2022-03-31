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

#define INTERRUPT_PORT_NAME "intr0"

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

    // get the handle for the processor in the module (only one)
    optProcessorP processor = opProcessorNext(mi, 0);

    // get interrupt port connection on processor (if made)
    optNetPortConnP intNC = opObjectByName(processor,
                                           INTERRUPT_PORT_NAME,
                                           OP_NETPORTCONN_EN).NetPortConn;
    optNetP intr0 = 0;
    opMessage("I", "HARNESS", "%s net connection to '%s' on '%s'",
                                   intNC ? "Found" : "Creating",
                                   INTERRUPT_PORT_NAME,
                                   opObjectName(processor));
    if(!intNC) {
        intr0 = opNetNew(mi, INTERRUPT_PORT_NAME "_net", 0, 0);
        opObjectNetConnect( processor, intr0, INTERRUPT_PORT_NAME);
    } else {
        intr0 = opNetPortConnNet(intNC);
    }

    // construction complete
    opRootModulePreSimulate(mr);

    opMessage("I", "HARNESS", "Simulate 20 instructions");
    opProcessorSimulate(processor, 20);

    opMessage("I", "HARNESS", "Generate Interrupt on 'intr0'");
    opNetWrite(intr0, 1);

    // We should simulate with the interrupt line active so that it is detected
    opMessage("I", "HARNESS", "Simulate 1 instruction");
    opProcessorSimulate(processor, 1);

    opMessage("I", "HARNESS", "Release Interrupt on 'intr0'");
    opNetWrite(intr0, 0);

    opMessage("I", "HARNESS", "Simulate 20 instructions");
    opProcessorSimulate(processor, 20);

    opMessage("I", "HARNESS", "Simulation finished\n");

    // print number of instructions executed at end of simulation and reason simulation stopped
    opMessage("I", "HARNESS", "%s executed "FMT_64u" instructions, StopReason '%s'\n",
                opObjectName(processor),
                opProcessorICount(processor),
                opStopReasonString(opProcessorStopReason(processor))
    );

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

