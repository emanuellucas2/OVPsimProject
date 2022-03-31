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
// This structure holds a pair of processors and an indication of which should
// run next
//
typedef struct procPairS {
    icmProcessorP processors[2];
    Bool          nextRun;
    Bool          doRestore;
} procPair, *procPairP;

//
// Standard command line parser
//
static Bool cmdParser(int argc, const char *argv[]) {

    icmCLPP parser = icmCLParser(PLATFORM, ICM_AC_ALL);

    return icmCLParseArgs(parser, argc, argv);
}

//
// Simulation main loop
//
static Bool simulate(
    procPairP pair,
    Uns32     clocks,
    icmNetP   intr0Net,
    Bool      intr0Value,
    icmNetP   resetNet,
    Bool      resetValue
) {
    const char *stateFile = "checkpoint.txt";
    Uns32       i;

    // simulate on alternate processors, one instruction at a time
    for(i=0; i<clocks; i++) {

        // get next processor to simulate
        icmProcessorP processor = pair->processors[pair->nextRun];

        // restore processor state before simulation if required
        if(pair->doRestore) {
            icmProcessorRestoreStateFile(processor, stateFile);
        }

        // if not the first iteration, apply interrupt net stimulus
        if(!i) {
            icmWriteNet(intr0Net, intr0Value);
            icmWriteNet(resetNet, resetValue);
        }

        icmStopReason stopReason = icmSimulate(processor, 1);

        // save processor after simulation
        icmProcessorSaveStateFile(processor, stateFile);

        // prepare for next iteration
        pair->nextRun   = !pair->nextRun;
        pair->doRestore = True;

        switch(stopReason) {

           case ICM_SR_SCHED:
               // hit the scheduler limit
               break;

           case ICM_SR_HALT:
               // processor halted in reset
               break;

           case ICM_SR_EXIT:
               // processor has exited
               return False;

           case ICM_SR_FINISH:
               // simulation must end
               return False;

           default:
               icmPrintf("unexpected stopReason %u\n", stopReason);
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
    procPairP   pair,
    const char *name,
    const char *modelFile,
    const char *semihostFile,
    icmBusP     bus,
    icmNetP     intr0Net,
    icmNetP     resetNet
) {
    // create processor instance
    icmProcessorP processor = icmNewProcessor(
        name, "or1k", 0, 0, 32, modelFile, 0, ICM_ATTR_DEFAULT, 0, semihostFile, 0
    );

    // connect processor instruction and data ports to the common bus
    icmConnectProcessorBusses(processor, bus, bus);

    // connect intr0 and reset nets to the processor
    icmConnectProcessorNet(processor, intr0Net, "intr0", ICM_INPUT);
    icmConnectProcessorNet(processor, resetNet, "reset", ICM_INPUT);

    // fill next processor slot
    pair->processors[pair->nextRun] = processor;
    pair->nextRun = !pair->nextRun;
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
    // CREATE SHARED MEMORY BUS AND INTERRUPT NETS
    ////////////////////////////////////////////////////////////////////////////

    // create the processor bus
    icmBusP bus = icmNewBus("bus", 32);

    // create memory
    icmMemoryP local = icmNewMemory("local", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the bus
    icmConnectMemoryToBus(bus, "mp1", local, 0x00000000);

    // create intr0 and reset nets
    icmNetP intr0Net = icmNewNet("intr0Net");
    icmNetP resetNet = icmNewNet("resetNet");

    ////////////////////////////////////////////////////////////////////////////
    // CREATE PROCESSOR PAIR
    ////////////////////////////////////////////////////////////////////////////

    procPair pair = {{0}};
    createProcessor(
        &pair, "procA", modelFile, semihostFile, bus, intr0Net, resetNet
    );
    createProcessor(
        &pair, "procB", modelFile, semihostFile, bus, intr0Net, resetNet
    );

    ////////////////////////////////////////////////////////////////////////////
    // SIMULATE
    ////////////////////////////////////////////////////////////////////////////

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
    icmTerminate();

    return 0;
}
