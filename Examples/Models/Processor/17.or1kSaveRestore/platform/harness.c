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
// This structure holds a pair of processors and an indication of which should
// run next
//
typedef struct procPairS {
    optProcessorP processors[2];
    Bool          nextRun;
    Bool          doRestore;
} procPair, *procPairP;

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
static Bool simulate(
    procPairP pair,
    Uns32     clocks,
    optNetP   intr0Net,
    Bool      intr0Value,
    optNetP   resetNet,
    Bool      resetValue
) {
    const char *stateFile = "checkpoint.txt";
    Uns32       i;

    // simulate on alternate processors, one instruction at a time
    for(i=0; i<clocks; i++) {

        // get next processor to simulate
        optProcessorP processor = pair->processors[pair->nextRun];

        // restore processor state before simulation if required
        if(pair->doRestore) {
            opProcessorStateRestoreFile(processor, stateFile);
        }

        // if not the first iteration, apply interrupt net stimulus
        if(!i) {
            opNetWrite(intr0Net, intr0Value);
            opNetWrite(resetNet, resetValue);
        }

        optStopReason stopReason = opProcessorSimulate(processor, 1);

        // save processor after simulation
        opProcessorStateSaveFile(processor, stateFile);

        // prepare for next iteration
        pair->nextRun   = !pair->nextRun;
        pair->doRestore = True;

        switch(stopReason) {

           case OP_SR_SCHED:
               // hit the scheduler limit
               break;

           case OP_SR_HALT:
               // processor halted in reset
               break;

           case OP_SR_EXIT:
               // processor has exited
               return False;

           case OP_SR_FINISH:
               // simulation must end
               return False;

           default:
               opPrintf("unexpected stopReason %s\n", opStopReasonString(stopReason));
               return False;
        }
    }

    // here when the required number of instructions have been executed
    return True;
}

//
// Create a new pair processor
//
static void createProcessor(
    optModuleP  mr,
    procPairP   pair,
    const char *name,
    const char *modelFile,
    const char *semihostFile,
    optBusP     bus,
    optNetP     intr0Net,
    optNetP     resetNet
) {
    // create processor instance
    optProcessorP processor = opProcessorNew(mr, modelFile, name, 0, 0);

    // attach imperasExit semihost library to processor
    opProcessorExtensionNew(processor, semihostFile, "imperasExit", 0);

    // connect processor instruction and data ports to the common bus
    opProcessorBusConnect(processor, bus, "INSTRUCTION");
    opProcessorBusConnect(processor, bus, "DATA");

    // connect intr0 and reset nets to the processor
    opObjectNetConnect(processor, intr0Net, "intr0");
    opObjectNetConnect(processor, resetNet, "reset");

    // fill next processor slot
    pair->processors[pair->nextRun] = processor;
    pair->nextRun = !pair->nextRun;
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
    // CREATE SHARED MEMORY BUS AND INTERRUPT NETS
    ////////////////////////////////////////////////////////////////////////////

    // create the processor bus
    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    // create memory
    optMemoryP memory = opMemoryNew(mr, "local", OP_PRIV_RWX, 0xffffffff, 0, 0);

    // connect the memory onto the bus
    opMemoryBusConnect(memory, bus, "mp1", 0x00000000, 0xffffffff);

    // create intr0 and reset nets
    optNetP intr0Net = opNetNew(mr, "intr0Net", 0, 0);
    optNetP resetNet = opNetNew(mr, "resetNet", 0, 0);

    ////////////////////////////////////////////////////////////////////////////
    // CREATE PROCESSOR PAIR
    ////////////////////////////////////////////////////////////////////////////

    procPair pair = {{0}};
    createProcessor(
        mr, &pair, "procA", modelFile, semihostFile, bus, intr0Net, resetNet
    );
    createProcessor(
        mr, &pair, "procB", modelFile, semihostFile, bus, intr0Net, resetNet
    );

    ////////////////////////////////////////////////////////////////////////////
    // SIMULATE
    ////////////////////////////////////////////////////////////////////////////

    // force elaboration of simulation data structures
    opRootModulePreSimulate(mr);

    // run for 9 instructions
    simulate(&pair, 9, intr0Net,0, resetNet,0);

    // assert reset for 5 instructions
    simulate(&pair, 5, intr0Net,0, resetNet,1);

    // run for 9 instructions
    simulate(&pair, 9, intr0Net,0, resetNet,0);

    // assert interrupt for 1 instruction
    simulate(&pair, 1, intr0Net,1, resetNet,0);

    // run for 9 instructions
    simulate(&pair, 9, intr0Net,0, resetNet,0);

    // assert interrupt for 1 instruction
    simulate(&pair, 1, intr0Net,1, resetNet,0);

    // run processor until done
    simulate(&pair, -1, intr0Net,0, resetNet,0);

    // terminate the simulation session
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

