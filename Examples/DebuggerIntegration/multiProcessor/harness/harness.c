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

// Include shared memory address info from application
#include "../application/shared.h"

// Define simulation module to load
#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"
#define CPU0_INSTANCE   "P0"
#define CPU1_INSTANCE   "P1"

// Define applications to load
#define APP_DIR         "application"
#define APP_ENCRYPT     "encrypt.OR1K.elf"
#define APP_DECRYPT     "decrypt.OR1K.elf"
#define APP_LDR_CTRL    OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR

// List of breakpoint addresses for processor 0 (encrypt)
// (Values are from application's objdump output - in a real debugger
//  these would be extracted from debug info in the ELF file.)
const static Addr breakpoints0[] = {
    0xf2c,          // main
    0               // terminator
};

// List of breakpoint addresses for processor 1 (decrypt)
const static Addr breakpoints1[] = {
    0x0f2c,         // waitForFrame
    0x1000,         // main
    0               // terminator
};

// Enumerator to specify type(s) of watchpoint to set
typedef enum watchTypeE {
    WATCH_READ  = 0x1,
    WATCH_WRITE = 0x2,
    WATCH_RW    = WATCH_READ | WATCH_WRITE
} watchType;

// Static data for register watchpoint invocation count and watchpoint id
static Uns32 regWatchPointCount;
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

    if (type == WATCH_RW) {

        // create access watchpoint
        optWatchpointP rwp = opProcessorAccessWatchpointNew(
            proc, False, address, address+size-1, (void *)(id++), 0
        );
        opPrintf("%s: ACCESS watchpoint is %u\n", opObjectName(proc), getWatchpointId(rwp));

    } else if (type == WATCH_READ) {

        // create read watchpoint
        optWatchpointP rwp = opProcessorReadWatchpointNew(
            proc, False, address, address+size-1, (void *)(id++), 0
        );
        opPrintf("%s: READ watchpoint is %u\n", opObjectName(proc), getWatchpointId(rwp));

    } else  if (type == WATCH_WRITE) {

        // create write watchpoint
        optWatchpointP wwp = opProcessorWriteWatchpointNew(
            proc, False, address, address+size-1, (void *)(id++), 0
        );
        opPrintf("%s: WRITE watchpoint is %u\n", opObjectName(proc), getWatchpointId(wwp));

    }
}

//
// Set register watchpoints for registers r3, r9 and the stack pointer in the
// passed processor
//
static void applyRegWatchpoints(optProcessorP processor) {

    optWatchpointP rwp1 = opProcessorRegWatchpointNew(
        processor, opProcessorRegByName(processor, "r3"), OP_RWP_CHANGE, (void *)(id++), 0
    );

    optWatchpointP rwp2 = opProcessorRegWatchpointNew(
        processor, opProcessorRegByName(processor, "r9"), OP_RWP_CHANGE, (void *)(id++), 0
    );

    optWatchpointP rwp3 = opProcessorRegWatchpointNew(
        processor, opProcessorRegByUsage(processor, OP_REG_SP), OP_RWP_CHANGE, (void *)(id++), 0
    );

    opPrintf("REGISTER watchpoint 1 is %u\n", getWatchpointId(rwp1));
    opPrintf("REGISTER watchpoint 2 is %u\n", getWatchpointId(rwp2));
    opPrintf("REGISTER watchpoint 3 is %u\n", getWatchpointId(rwp3));

}

//
// Query registers and register groups in the passed processor
//
static void queryRegisters(optProcessorP processor) {

    opPrintf("%s REGISTERS\n", opObjectName(processor));

    optRegGroupP group = 0;

    while((group=opProcessorRegGroupNext(processor, group))) {

        opPrintf("  GROUP %s\n", opRegGroupName(group));

        optRegP reg = 0;

        while((reg=opRegGroupRegNext(processor, group, reg))) {
            opPrintf("    REGISTER %s\n", opRegName(reg));
        }
    }
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

            case OP_WP_REG: {

                // a register watchpoint was triggered
                optRegP reg       = opWatchpointReg(wp);
                Uns32  *newValueP = (Uns32 *)opWatchpointRegCurrentValue(wp);
                Uns32  *oldValueP = (Uns32 *)opWatchpointRegPreviousValue(wp);

                // indicate old and new value of the affected register
                opPrintf(
                    "  Register watchpoint %u (processor %s:%s) triggered 0x%08x->0x%08x\n",
                    id,
                    opObjectName(processor),
                    opRegName(reg),
                    *oldValueP,
                    *newValueP
                );

                // delete watchpoint after 100 triggerings
                if(regWatchPointCount++>100) {
                    opWatchpointDelete(wp);
                } else {
                    opWatchpointReset(wp);
                }

                break;
            }

            case OP_WP_MEM_READ:
            case OP_WP_MEM_WRITE:
            case OP_WP_MEM_ACCESS: {

                // a memory watchpoint was triggered
                opPrintf(
                    "  %s watchpoint %u (range 0x%08x:0x%08x) triggered by processor %s\n",
                    (type==OP_WP_MEM_READ) ? "Read" : (type==OP_WP_MEM_WRITE) ? "Write" : "Access",
                    id,
                    (Uns32)opWatchpointAddressLo(wp),
                    (Uns32)opWatchpointAddressHi(wp),
                    opObjectName(processor)
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
    optProcessorP processor0 = opObjectByName(root, MODULE_INSTANCE "/" CPU0_INSTANCE, OP_PROCESSOR_EN).Processor;
    optProcessorP processor1 = opObjectByName(root, MODULE_INSTANCE "/" CPU1_INSTANCE, OP_PROCESSOR_EN).Processor;

    // Load application programs
    opProcessorApplicationLoad(processor0, APP_DIR "/" APP_ENCRYPT, APP_LDR_CTRL, 0);
    opProcessorApplicationLoad(processor1, APP_DIR "/" APP_DECRYPT, APP_LDR_CTRL, 0);

    // Must advance simulator phase before setting watchpoints
    opRootModulePreSimulate(root);

    // Apply watchpoint on writes to the first word of shared memory address (ENCRYPT_INDEX)
    // (only needs to be added for one of the processors since it is shared memory)
    applyWatchpoint(processor0, SHARED_LOW, 4, WATCH_WRITE);

    // Set register watchpoints for processor0
    applyRegWatchpoints(processor0);

    // Report registers and register groups in processor0
    queryRegisters(processor0);

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
            applyBreakpoints(processor0, breakpoints0);
            applyBreakpoints(processor1, breakpoints1);
            stopProcessor = opRootModuleSimulate(root);
            clearBreakpoints(processor0, breakpoints0);
            clearBreakpoints(processor1, breakpoints1);
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

