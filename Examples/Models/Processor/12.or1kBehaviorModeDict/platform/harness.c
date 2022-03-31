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

    // create a processor instance
    const char *modelFile = "model."IMPERAS_SHRSUF;
    optProcessorP processor = opProcessorNew(mr, modelFile, "cpu1", 0, 0);

    // get semihost library to exit simulation
    const char *semihostFile = opVLNVString( 0, "ovpworld.org", "modelSupport", "imperasExit", "1.0", OP_EXTENSION, OP_VLNV_FATAL);

    // attach imperasExit semihost library to processor
    opProcessorExtensionNew(processor, semihostFile, "imperasExit", 0);

    // create the processor bus
    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    // connect processor instruction and data ports to the common bus
    opProcessorBusConnect(processor, bus, "INSTRUCTION");
    opProcessorBusConnect(processor, bus, "DATA");

    // create memory
    optMemoryP memory = opMemoryNew(mr, "local", OP_PRIV_RWX, 0xffffffff, 0, 0);

    // connect the memory onto the bus
    opMemoryBusConnect(memory, bus, "mp1", 0x00000000, 0xffffffff);

    // run platform
    opRootModuleSimulate(mr);

    // dump the final register contents
    opProcessorRegDump(processor);

    // report the total number of instructions executed
    opPrintf(
        "processor has executed " FMT_64u " instructions\n",
        opProcessorICount(processor)
    );

    // terminate the simulation session
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

