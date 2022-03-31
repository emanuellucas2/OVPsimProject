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

#include "op/op.h"

// Define simulation module to load
#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"
#define CPU_INSTANCE    "cpu1"

// Define application to load
#define APP_DIR         "application"
#define APP_ASMTEST     "asmtest.OR1K.elf"
#define APP_LDR_CTRL    OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR

// List of breakpoint addresses (Empty for this example)
const static Addr breakpoints[] = {
    0               // terminator
};

// Enumerator to specify type(s) of watchpoint to set
typedef enum watchTypeE {
    WATCH_READ,
    WATCH_WRITE,
    WATCH_RW,
    WATCH_MODE,
    WATCH_EXCEPTION,
} watchType;

// Static data for watchpoint id
static UnsPS id;

//
// Apply the passed breakpoints on the passed processor
//
static void applyBreakpoints(optProcessorP processor, const Addr breakpoints[]) {

    Uns32 i;

    for(i=0; breakpoints[i]; i++) {
        opProcessorBreakpointAddrSet(processor, breakpoints[i]);
    }
}

//
// Clear the passed breakpoints on the passed processor
//
static void clearBreakpoints(optProcessorP processor, const Addr breakpoints[]) {

    Uns32 i;

    for(i=0; breakpoints[i]; i++) {
        opProcessorBreakpointAddrClear(processor, breakpoints[i]);
    }
}

//
// Return watchpoint id
//
static Uns32 getWatchpointId(optWatchpointP watchpoint) {
    return (UnsPS)opWatchpointUserData(watchpoint);
}

//
// Apply a watchpoint on a processor memory location
//
static void applyWatchpoint(
    optProcessorP proc,
    Addr          address,
    Addr          size,
    watchType     type
) {

    optWatchpointP wp;
    const char    *typeName = "???";

    switch(type) {

    case (WATCH_RW):
        // create access watchpoint
        wp = opProcessorAccessWatchpointNew(
            proc, False, address, address+size-1, (void *)(id++), 0
        );
        typeName = "ACCESS";
        break;

    case (WATCH_READ):
        // create read watchpoint
        wp = opProcessorReadWatchpointNew(
            proc, False, address, address+size-1, (void *)(id++), 0
        );
        typeName = "READ";
        break;

    case (WATCH_WRITE):
        wp = opProcessorWriteWatchpointNew(
            proc, False, address, address+size-1, (void *)(id++), 0
        );
        typeName = "WRITE";
        break;

    case (WATCH_MODE):
        wp = opProcessorModeWatchpointNew(
            proc, (void *)(id++), 0
        );
        typeName = "MODE";
        break;

    case (WATCH_EXCEPTION):
        wp = opProcessorExceptionWatchpointNew(
            proc, (void *)(id++), 0
        );
        typeName = "EXCEPTION";
        break;

    default:
        opPrintf("Invalid watchpoint type %d requested\n", type);
        return;

    }

    opPrintf("%s: %s watchpoint is %u\n", opObjectName(proc), typeName, getWatchpointId(wp));

}

//
// Handle all active watchpoints
//
static void handleWatchpoints(optModuleP mi) {

    optWatchpointP wp;

    while((wp=opRootModuleWatchpointNext(mi))) {

        Uns32             id        = getWatchpointId(wp);
        optProcessorP     processor = opWatchpointTriggeredBy(wp);
        optWatchpointType type      = opWatchpointType(wp);

        switch(type) {

            case OP_WP_MODE: {

                // a mode switch watchpoint was triggered
                optModeP    mode     = opProcessorModeCurrent(processor);
                Uns32       modeCode = mode ? opModeCode(mode) : 0;
                const char *modeName = mode ? opModeName(mode) : "none";

                // report new mode
                opPrintf(
                    "  watchpoint %u (processor %s:MODE) triggered mode -> %d (%s)\n",
                    id,
                    opObjectName(processor),
                    modeCode,
                    modeName ?: ""
                );

                opWatchpointReset(wp);

                break;
            }

            case OP_WP_EXCEPTION: {

                // an exception watchpoint was triggered
                optExceptionP except = opProcessorExceptionCurrent(processor);
                Uns32       exceptCode = except ? opExceptionCode(except) : 0;
                const char *exceptName = except ? opExceptionName(except) : "none";
                const char *exceptDesc = except ? opExceptionDescription(except) : "";

                // report current exception
                opPrintf(
                    "  watchpoint %u (processor %s:EXCEPTION) triggered exception -> %d %s: %s)\n",
                    id,
                    opObjectName(processor),
                    exceptCode,
                    exceptName ?: "",
                    exceptDesc ?: ""
                );

                opWatchpointReset(wp);

                break;
            }

            default: {

                opPrintf(
                    "  unknown watchpoint type %u triggered by processor %s\n",
                    type,
                    opObjectName (processor)
                );

                opWatchpointReset(wp);

                break;
            }
        }
    }
}

//
// Main routine
//
int main(int argc, const char *argv[]) {

    // Start up simulator and parse command line arguments
    opSessionInit(OP_VERSION);
    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    // Load the design
    optModuleP root = opRootModuleNew(0, 0, 0);
    opModuleNew(root, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    // Get processor handles
    optProcessorP processor = opObjectByName(root, MODULE_INSTANCE "/" CPU_INSTANCE, OP_PROCESSOR_EN).Processor;

    // Load application programs
    opProcessorApplicationLoad(processor, APP_DIR "/" APP_ASMTEST, APP_LDR_CTRL, 0);

    // Must advance simulator phase before setting watchpoints
    opRootModulePreSimulate(root);

    // Apply watchpoints on mode switches and exceptions
    applyWatchpoint(processor, 0, 0, WATCH_MODE);
    applyWatchpoint(processor, 0, 0, WATCH_EXCEPTION);

    Bool          stepOver      = False;
    Bool          finished      = False;
    optProcessorP stopProcessor = 0;

    // Simulation loop
    while(!finished) {

        // Simulate the platform using the default scheduler
        // All breakpoints are set and cleared together, ala gdb behavior
        if(stepOver) {
            opProcessorBreakpointICountSet(stopProcessor, 1);
            stopProcessor = opRootModuleSimulate (root);
            stepOver = False;
        } else {
            applyBreakpoints(processor, breakpoints);
            stopProcessor = opRootModuleSimulate(root);
            clearBreakpoints(processor, breakpoints);
        }

        optStopReason sr = stopProcessor ? opProcessorStopReason(stopProcessor)
                                         : OP_SR_EXIT;
        switch(sr) {

            case OP_SR_EXIT:
            case OP_SR_FINISH:
                finished = True;
                break;

            case OP_SR_BP_ICOUNT:
                opPrintf(
                    "Processor %s icount %u stopped at icount\n",
                     opObjectName (stopProcessor),
                    (Uns32)opProcessorICount(stopProcessor)
                );
                break;

            case OP_SR_BP_ADDRESS:
                opPrintf(
                    "Processor %s icount %u breakpoint at address 0x%08x\n",
                    opObjectName (stopProcessor),
                    (Uns32)opProcessorICount(stopProcessor),
                    (Uns32)opProcessorPC(stopProcessor)
                );
                stepOver = True;
                break;

            case OP_SR_WATCHPOINT:
                opPrintf(
                    "Processor %s icount %u stopped at watchpoint\n",
                     opObjectName (stopProcessor),
                    (Uns32)opProcessorICount(stopProcessor)
                );
                handleWatchpoints(root);
                break;

            default:
                opPrintf(
                    "Processor %s icount %u stopped with unexpected reason 0x%x (%s)\n",
                    opObjectName (stopProcessor),
                    (Uns32)opProcessorICount(stopProcessor),
                    sr,
                    opStopReasonString(sr)
                );
                break;
        }
    }

    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

