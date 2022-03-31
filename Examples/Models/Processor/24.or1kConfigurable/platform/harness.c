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

// OP interface includes
#include "op/op.h"

//
// Name for root and root module
//
#define MODULE_NAME "platform"

//
// Standard command line parser
//
static Bool cmdParser(int argc, const char *argv[]) {

    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    return opCmdParseArgs(parser, argc, argv);
}

//
// Query net ports in the passed processor
//
static void queryNetPorts(optProcessorP processor) {

    const char *name = opObjectHierName(processor);

    if(!opObjectNetPortNext(processor, 0)) {

        opPrintf("%s HAS NO NET PORTS\n", name);

    } else {

        opPrintf("%s NET PORTS\n", name);

        optNetPortP netPort = 0;

        while((netPort=opObjectNetPortNext(processor, netPort))) {
            opPrintf(
                "  %s (%s)\n",
                opObjectName(netPort),
                opNetPortTypeString(netPort)
            );
        }
    }

    opPrintf("\n");
}

//
// Virtual platform construction and simulation
//
int main(int argc, const char **argv) {

    // initialize simulation session before calling any other OP functions
    opSessionInit(OP_VERSION);

    // check arguments
    if(!cmdParser(argc, argv)) {
        opMessage("E", "CLI", "Command Line parser error");
        return 1;
    }

    // create root module, enabling simulation interruption if Ctrl-C is pressed
    optModuleP mr = opRootModuleNew(
        0,
        MODULE_NAME,
        OP_PARAMS (
            OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    // get processor model file
    const char *modelFile = "model."IMPERAS_SHRSUF;

    // get semihost library to exit simulation
    const char *semihostFile = opVLNVString( 0, "ovpworld.org", "modelSupport", "imperasExit", "1.0", OP_EXTENSION, OP_VLNV_FATAL);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE PROCESSOR procA
    ////////////////////////////////////////////////////////////////////////////

    // create processor instance procA
    optProcessorP procA = opProcessorNew(
        mr,
        modelFile,
        "procA",
        0,
        OP_PARAMS (
            OP_PARAM_BOOL_SET(OP_FP_SIMULATEEXCEPTIONS, 1)
        )
    );

    // attach imperasExit semihost library to processor procA
    opProcessorExtensionNew(procA, semihostFile, "imperasExit", 0);

    // create the processor bus
    optBusP busA = opBusNew(mr, "busA", 32, 0, 0);

    // connect processor instruction and data ports to the common bus
    opProcessorBusConnect(procA, busA, "INSTRUCTION");
    opProcessorBusConnect(procA, busA, "DATA");

    // create memory
    optMemoryP localA = opMemoryNew(mr, "localA", OP_PRIV_RWX, 0xffffffff, 0, 0);

    // connect the memory onto the bus
    opMemoryBusConnect(localA, busA, "mp1", 0x00000000, 0xffffffff);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE PARAMETERIZED PROCESSOR procB
    ////////////////////////////////////////////////////////////////////////////

    // create processor instance procB
    optProcessorP procB = opProcessorNew(
        mr,
        modelFile,
        "procB",
        0,
        OP_PARAMS (
            OP_PARAM_BOOL_SET(OP_FP_SIMULATEEXCEPTIONS, 1),
            OP_PARAM_BOOL_SET(OP_FP_VERBOSE, 1),
            OP_PARAM_UNS32_SET("extinterrupts", 2),
            OP_PARAM_STRING_SET("extintlogfile", "test.log")
        )
    );

    // attach imperasExit semihost library to processor procA
    opProcessorExtensionNew(procB, semihostFile, "imperasExit", 0);

    // create the processor bus
    optBusP busB = opBusNew(mr, "busB", 32, 0, 0);

    // connect processor instruction and data ports to the common bus
    opProcessorBusConnect(procB, busB, "INSTRUCTION");
    opProcessorBusConnect(procB, busB, "DATA");

    // create memory
    optMemoryP localB = opMemoryNew(mr, "localB", OP_PRIV_RWX, 0xffffffff, 0, 0);

    // connect the memory onto the busses
    opMemoryBusConnect(localB, busB, "mp1", 0x00000000, 0xffffffff);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE AND CONNECT NETS
    ////////////////////////////////////////////////////////////////////////////

    // create nets
    optNetP n1 = opNetNew(mr, "n1", 0, 0);
    optNetP n2 = opNetNew(mr, "n2", 0, 0);
    optNetP n3 = opNetNew(mr, "n3", 0, 0);

    // connect nets to processors
    opObjectNetConnect(procA, n1, "intr0");
    opObjectNetConnect(procB, n2, "intr0");
    opObjectNetConnect(procB, n3, "intr1");

    ////////////////////////////////////////////////////////////////////////////
    // SHOW NET PORTS ON EACH INSTANCE
    ////////////////////////////////////////////////////////////////////////////

    // print net ports
    queryNetPorts(procA);
    queryNetPorts(procB);

    ////////////////////////////////////////////////////////////////////////////
    // SIMULATE
    ////////////////////////////////////////////////////////////////////////////

    // advance the processors, then interrupt
    opProcessorSimulate(procA, 9);
    opProcessorSimulate(procB, 9);

    opPrintf("Interrupting A & B\n");
    opNetWrite(n1, 1);
    opNetWrite(n3, 1);
    opProcessorSimulate(procA, 1);
    opProcessorSimulate(procB, 1);
    opNetWrite(n1, 0);
    opNetWrite(n3, 0);
    opProcessorSimulate(procA, 9);
    opProcessorSimulate(procB, 9);

    opPrintf("Interrupting B\n");
    opNetWrite(n2, 1);
    opProcessorSimulate(procA, 1);
    opProcessorSimulate(procB, 1);
    opNetWrite(n2, 0);
    opProcessorSimulate(procA, 10);
    opProcessorSimulate(procB, 10);

    // report the total number of instructions executed
    opPrintf(
        "processor A has executed " FMT_64u " instructions\n",
        opProcessorICount(procA)
    );
    opPrintf(
        "processor B has executed " FMT_64u " instructions\n",
        opProcessorICount(procB)
    );

    // terminate the simulation session
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

