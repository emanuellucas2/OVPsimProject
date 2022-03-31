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
// Query registers and register groups in the passed processor
//
static void queryRegisters(icmProcessorP processor) {

    icmPrintf("%s REGISTERS\n", icmGetProcessorName(processor, "/"));

    icmRegGroupP group = NULL;

    while((group=icmGetNextRegGroup(processor, group))) {

        icmPrintf("  GROUP %s\n", icmGetRegGroupName(group));

        icmRegInfoP reg = NULL;

        while((reg=icmGetNextRegInGroup(processor, group, reg))) {
            icmPrintf("    REGISTER %s\n", icmGetRegInfoName(reg));
        }
    }

    icmPrintf("\n");
}

//
// Query exceptions in the passed processor
//
static void queryExceptions(icmProcessorP processor) {

    const char *name = icmGetProcessorName(processor, "/");

    if(!icmGetNextException(processor, 0)) {

        icmPrintf("%s HAS NO EXCEPTION INFORMATION\n", name);

    } else {

        icmPrintf("%s EXCEPTIONS\n", name);

        icmExceptionInfoP info = NULL;

        while((info=icmGetNextException(processor, info))) {
            icmPrintf(
                "  %s (code %u)\n",
                icmGetExceptionInfoName(info),
                icmGetExceptionInfoCode(info)
            );
        }

        if((info=icmGetException(processor))) {
            icmPrintf(
                "current: %s (code %u)\n",
                icmGetExceptionInfoName(info),
                icmGetExceptionInfoCode(info)
            );
        }
    }

    icmPrintf("\n");
}

//
// Query modes in the passed processor
//
static void queryModes(icmProcessorP processor) {

    const char *name = icmGetProcessorName(processor, "/");

    if(!icmGetNextMode(processor, 0)) {

        icmPrintf("%s HAS NO MODE INFORMATION\n", name);

    } else {

        icmPrintf("%s MODES\n", name);

        icmModeInfoP info = NULL;

        while((info=icmGetNextMode(processor, info))) {
            icmPrintf(
                "  %s (code %u)\n",
                icmGetModeInfoName(info),
                icmGetModeInfoCode(info)
            );
        }

        if((info=icmGetMode(processor))) {
            icmPrintf(
                "current: %s (code %u)\n",
                icmGetModeInfoName(info),
                icmGetModeInfoCode(info)
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

    icmSimulationStarting();

    // query processor registers, execeptions and modes
    queryRegisters(processor);
    queryExceptions(processor);
    queryModes(processor);

    // run processor until done (no instruction limit)
    while(simulate(processor, -1)) {
        // keep going while processor is still running
    }

    // report the total number of instructions executed
    icmPrintf(
        "processor has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor)
    );

    // terminate the simulation session
    icmTerminate();

    return 0;
}
