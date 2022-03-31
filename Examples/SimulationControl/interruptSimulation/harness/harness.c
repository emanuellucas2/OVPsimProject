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


// By default use the internal handler for Control-C when the simulator initialised with OP_FP_STOPONCTRLC
// This is valid for both Linux and Windows Hosts

// Alternatively, on Linux only, use this define to use this included Linux control-C handler
//#define EXTERNALHANDLER
// or build platform with make -C platform CFLAGS="-D EXTERNALHANDLER"

// This is a custom handler that is only valid when compiled for a Linux host system
#ifdef EXTERNALHANDLER

#include <signal.h>

//
// LINUX signal handler to interrupt the running simulation
//
static void ctrlCHandler(Int32 nativeSigNum, siginfo_t *sigInfo, void *context) {
    // On Linux the API call may be used directly as the simulator is frozen on a signal
    // On Windows the simulator must be suspended before issuing this call

    printf("External Users Ctrl-C Handler Triggered\n");
    opInterrupt();
}

//
// Install a LINUX signal handler to trap any CtrlC
//
static void installCtrlCHandler(void) {

    struct sigaction sa = {{0}};
    sa.sa_sigaction = ctrlCHandler;
    sa.sa_flags     = SA_SIGINFO;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}

#define MODULEINIT (OP_PARAMS (
                       OP_PARAM_BOOL_SET (OP_FP_VERBOSE, 1) \
                              )                            \
                   )

#else

#define MODULEINIT (OP_PARAMS (                                    \
                       OP_PARAM_BOOL_SET(OP_FP_VERBOSE, 1),        \
                       OP_PARAM_BOOL_SET (OP_FP_STOPONCONTROLC, 1) \
                              )                                    \
                   )

#endif

int main(int argc, const char *argv[]) {

#ifdef EXTERNALHANDLER

    // install a signal handler to trap any CtrlC
    installCtrlCHandler();

#endif

    opSessionInit(OP_VERSION);

    opCmdParseStd(MODULE_NAME, OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, MODULE_NAME, MODULEINIT);

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

    // run simulation
    optProcessorP stoppedProcessor;

    // simulate until done, yield or ctrl-C
    Bool continueExecution = True;
    while(continueExecution) {

        stoppedProcessor = opRootModuleSimulate(mr);

        if(stoppedProcessor) {
            optStopReason stopReason = opProcessorStopReason(stoppedProcessor);

            switch(stopReason) {
                   case OP_SR_INTERRUPT:
                   case OP_SR_YIELD:
                       opMessage( "I", "HARNESS",
                           "%s: interrupt after " FMT_64u " instructions '%s'",
                           opObjectName(stoppedProcessor),
                           opProcessorICount(stoppedProcessor),
                           opStopReasonString(stopReason));
                       break;
                   default:
                       // some other stop reason encountered
                       continueExecution = False;
                       break;
            }
        } else {
            // The simulation can stop without a processor handle
            // i.e when all processors are finished
            // use module stop reason
            optStopReason stopReason = opRootModuleStopReason(mr);
            opMessage( "I", "HARNESS",
                "Simulation stopped '%s'", opStopReasonString(stopReason));
            continueExecution = False;
        }
    }

    // print number of instructions executed at end of simulation and reason simulation stopped
    opPrintf("Simulation finished '%s'\n", opStopReasonString(opRootModuleStopReason(mr)));
    opPrintf("instructions executed cpu1 "FMT_64u" and cpu2 "FMT_64u"\n",
                opProcessorICount(opObjectByName(mi, "cpu1", OP_PROCESSOR_EN).Processor),
                opProcessorICount(opObjectByName(mi, "cpu2", OP_PROCESSOR_EN).Processor)
    );

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

