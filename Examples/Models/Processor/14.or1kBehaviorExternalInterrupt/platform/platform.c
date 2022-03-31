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
// Simulation main loop
//
static Bool simulate(icmProcessorP processor, Uns64 instructions) {

    icmStopReason stopReason = icmSimulate(processor, instructions);

    switch(stopReason) {

       case ICM_SR_SCHED:
           // hit the scheduler limit
           return True;

       case ICM_SR_HALT:
           // processor halted in reset
           return True;

       case ICM_SR_EXIT:
           // processor has exited
           return False;

       case ICM_SR_FINISH:
           // simulation must end
           return False;

        case ICM_SR_RD_PRIV:
        case ICM_SR_WR_PRIV:
        case ICM_SR_RD_ALIGN:
        case ICM_SR_WR_ALIGN:
           // unhandled processor exception: simulation must end
           return False;

       default:
           icmPrintf("unimplemented stopReason %u\n", stopReason);
           return False;
    }
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

    // get semihost library to exit simulation
    const char *semihostFile = icmGetVlnvString(
        0, "ovpworld.org", "modelSupport", "imperasExit", "1.0", "model"
    );

    // create a processor instance
    const char *modelFile = "model."IMPERAS_SHRSUF;
    icmProcessorP processor = icmNewProcessor(
        "cpu1", "or1k", 0, 0, 32, modelFile, 0, ICM_ATTR_DEFAULT, 0, semihostFile, 0
    );

    // create the processor bus
    icmBusP bus = icmNewBus("bus", 32);

    // connect the processors onto the busses
    icmConnectProcessorBusses(processor, bus, bus);

    // create memory
    icmMemoryP local = icmNewMemory("local", ICM_PRIV_RWX, 0xffffffff);

    // connect the memory onto the busses
    icmConnectMemoryToBus(bus, "mp1", local, 0x00000000);

    // create intr0, intr1 and reset nets and connect them to the processor
    icmNetP intr0Net = icmNewNet("intr0Net");
    icmNetP intr1Net = icmNewNet("intr1Net");
    icmNetP resetNet = icmNewNet("resetNet");
    icmConnectProcessorNet(processor, intr0Net, "intr0", ICM_INPUT);
    icmConnectProcessorNet(processor, intr1Net, "intr1", ICM_INPUT);
    icmConnectProcessorNet(processor, resetNet, "reset", ICM_INPUT);

    // run processor for 9 instructions
    simulate(processor, 9);

    // raise reset for five instructions
    icmWriteNet(resetNet, 1);
    simulate(processor, 5);
    icmWriteNet(resetNet, 0);

    // run processor for 9 instructions
    simulate(processor, 9);

    // raise intr0 for one instruction
    icmWriteNet(intr0Net, 1);
    simulate(processor, 1);
    icmWriteNet(intr0Net, 0);

    // run processor for 9 instructions
    simulate(processor, 9);

    // raise intr1 for one instruction
    icmWriteNet(intr1Net, 1);
    simulate(processor, 1);
    icmWriteNet(intr1Net, 0);

    // run processor until done (no instruction limit)
    while(simulate(processor, -1)) {
        // keep going while processor is still running
    }

    // dump the final register contents
    icmDumpRegisters(processor);

    // report the total number of instructions executed
    icmPrintf(
        "processor has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor)
    );

    // terminate the simulation session
    icmTerminate();

    return 0;
}
