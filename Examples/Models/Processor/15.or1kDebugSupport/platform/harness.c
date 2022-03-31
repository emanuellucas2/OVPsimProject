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
// Simulation main loop
//
static Bool simulate(optProcessorP processor, Uns64 clocks) {

    optStopReason stopReason = opProcessorSimulate(processor, clocks);

    switch(stopReason) {

       case OP_SR_SCHED:
           // hit the scheduler limit
           return True;

       case OP_SR_EXIT:
           // processor has exited
           return False;

       case OP_SR_FINISH:
           // simulation must end
           return False;

       case OP_SR_RD_PRIV:
       case OP_SR_WR_PRIV:
       case OP_SR_RD_ALIGN:
       case OP_SR_WR_ALIGN:
          // unhandled processor exception: simulation must end
          return False;

       default:
           opPrintf("unexpected stopReason %s\n", opStopReasonString(stopReason));
           return False;
    }
}

//
// Query registers and register groups in the passed processor
//
static void queryRegisters(optProcessorP processor) {

    opPrintf("%s REGISTERS\n", opObjectHierName(processor));

    optRegGroupP group = 0;

    while((group=opProcessorRegGroupNext(processor, group))) {

        opPrintf("  GROUP %s\n", opRegGroupName(group));

        optRegP reg = 0;

        while((reg=opRegGroupRegNext(processor, group, reg))) {
            opPrintf("    REGISTER %s\n", opRegName(reg));
        }
    }

    opPrintf("\n");
}

//
// Query exceptions in the passed processor
//
static void queryExceptions(optProcessorP processor) {

    const char *name = opObjectHierName(processor);

    if(!opProcessorExceptionNext(processor, 0)) {

        opPrintf("%s HAS NO EXCEPTION INFORMATION\n", name);

    } else {

        opPrintf("%s EXCEPTIONS\n", name);

        optExceptionP info = 0;

        while((info=opProcessorExceptionNext(processor, info))) {
            opPrintf(
                "  %s (code %u)\n",
                opExceptionName(info),
                opExceptionCode(info)
            );
        }

        if((info=opProcessorExceptionCurrent(processor))) {
            opPrintf(
                "current: %s (code %u)\n",
                opExceptionName(info),
                opExceptionCode(info)
            );
        }
    }

    opPrintf("\n");
}

//
// Query modes in the passed processor
//
static void queryModes(optProcessorP processor) {

    const char *name = opObjectHierName(processor);

    if(!opProcessorModeNext(processor, 0)) {

        opPrintf("%s HAS NO MODE INFORMATION\n", name);

    } else {

        opPrintf("%s MODES\n", name);

        optModeP info = 0;

        while((info=opProcessorModeNext(processor, info))) {
            opPrintf(
                "  %s (code %u)\n",
                opModeName(info),
                opModeCode(info)
            );
        }

        if((info=opProcessorModeCurrent(processor))) {
            opPrintf(
                "current: %s (code %u)\n",
                opModeName(info),
                opModeCode(info)
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

    // force elaboration of simulation data structures
    opRootModulePreSimulate(mr);

    // query processor registers, execeptions and modes
    queryRegisters(processor);
    queryExceptions(processor);
    queryModes(processor);

    // run processor, one instruction at a time
    while(simulate(processor, 1)) {
        // keep going while processor is still running
    }

    // report the total number of instructions executed
    opPrintf(
        "processor has executed " FMT_64u " instructions\n",
        opProcessorICount(processor)
    );

    // terminate the simulation session
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

