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


/*******************************************************************************
 * NOTE: this harness is written using the legacy ICM API and is equivalent to
 * the OP API harness.c file in this directory. It is present for reference
 * purposes.
 *
 * To compile this harness, use:
 *     make -C platform BUILD_ICM_LEGACY=1
 * in the example directory.
 ******************************************************************************/


// ICM interface includes
#include "icm/icmCpuManager.h"

//
// Name for platform
//
#define PLATFORM "platform"

//
// Standard command line parser
//
static Bool cmdParser(int argc, const char *argv[]) {

    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);

    return icmCLParseArgs(parser, argc, argv);
}

//
// Create attribute list for processor procB
//
static icmAttrListP attrsForB(void) {

    icmAttrListP userAttrs = icmNewAttrList();

    icmAddUns64Attr (userAttrs, "verbose", 1);
    icmAddUns64Attr (userAttrs, "extinterrupts", 2);
    icmAddStringAttr(userAttrs, "extintlogfile", "test.log");

    return userAttrs;
}

//
// Query registers and register groups in the passed processor
//
static void queryNetPorts(icmProcessorP processor) {

    const char *name = icmGetProcessorName(processor, 0);

    if(!icmGetNextProcessorNetPortInfo(processor, 0)) {

        icmPrintf("%s HAS NO NET PORTS\n", name);

    } else {

        icmPrintf("%s NET PORTS\n", name);

        icmNetPortInfoP netPort = 0;

        while((netPort=icmGetNextProcessorNetPortInfo(processor, netPort))) {
            icmPrintf(
                "  %s (%s)\n",
                icmGetNetPortName(netPort),
                icmGetNetPortTypeString(netPort)
            );
        }
    }

    icmPrintf("\n");
}

//
// Virtual platform construction and simulation
//
int main(int argc, const char **argv) {

    // check arguments
    if(!cmdParser(argc, argv)) {
        icmMessage("E", "CLI", "Command Line parser error");
        return 1;
    }

    // initialize ICM, enabling simulation interruption if Ctrl-C is pressed
    icmInitPlatform(ICM_VERSION, ICM_STOP_ON_CTRLC, 0, 0, PLATFORM);

    // get processor model file
    const char *modelFile = "model."IMPERAS_SHRSUF;

    // get semihost library to exit simulation
    const char *semihostFile = icmGetVlnvString(
        0, "ovpworld.org", "modelSupport", "imperasExit", "1.0", "model"
    );

    ////////////////////////////////////////////////////////////////////////////
    // CREATE PROCESSOR procA
    ////////////////////////////////////////////////////////////////////////////

    // create processor instance procA
    icmProcessorP procA = icmNewProcessor(
        "procA", "or1k", 0, 0, 32, modelFile, 0, ICM_ATTR_SIMEX, 0,
        semihostFile, 0
    );

    // create the processor bus
    icmBusP busA = icmNewBus("busA", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(procA, busA, busA);

    // create memory
    icmMemoryP localA = icmNewMemory("localA", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(busA, "mp1", localA, 0x00000000);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE PARAMETERIZED PROCESSOR procB
    ////////////////////////////////////////////////////////////////////////////

    // create processor instance procB
    icmProcessorP procB = icmNewProcessor(
        "procB", "or1k", 0, 0, 32, modelFile, 0, ICM_ATTR_SIMEX, attrsForB(),
        semihostFile, 0
    );

    // create the processor bus
    icmBusP busB = icmNewBus("busB", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(procB, busB, busB);

    // create memory
    icmMemoryP localB = icmNewMemory("localB", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(busB, "mp1", localB, 0x00000000);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE AND CONNECT NETS
    ////////////////////////////////////////////////////////////////////////////

    icmNetP n1 = icmNewNet("n1");
    icmNetP n2 = icmNewNet("n2");
    icmNetP n3 = icmNewNet("n3");

    icmConnectProcessorNet(procA, n1, "intr0", ICM_INPUT);
    icmConnectProcessorNet(procB, n2, "intr0", ICM_INPUT);
    icmConnectProcessorNet(procB, n3, "intr1", ICM_INPUT);

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
    icmSimulate(procA, 9);
    icmSimulate(procB, 9);
    icmPrintf("Interrupting A & B\n");
    icmWriteNet(n1, 1);
    icmWriteNet(n3, 1);
    icmSimulate(procA, 1);
    icmSimulate(procB, 1);
    icmWriteNet(n1, 0);
    icmWriteNet(n3, 0);
    icmSimulate(procA, 9);
    icmSimulate(procB, 9);

    icmPrintf("Interrupting B\n");
    icmWriteNet(n2, 1);
    icmSimulate(procA, 1);
    icmSimulate(procB, 1);
    icmWriteNet(n2, 0);
    icmSimulate(procA, 10);
    icmSimulate(procB, 10);

    // report the total number of instructions executed
    icmPrintf(
        "processor A has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(procA)
    );
    icmPrintf(
        "processor B has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(procB)
    );

    // terminate the simulation session
    icmTerminate();

    return 0;
}
