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

#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define HARNESS_NAME "harness"


static OP_BUS_SLAVE_READ_FN(readCallback) {

    const char *busName = userData;

    opMessage(
        "I", HARNESS_NAME "_RCB",
        "readCallback: %s, 0x" FMT_Ax,
        busName,
        addr
    );

}

static OP_BUS_SLAVE_WRITE_FN(writeCallback) {

    const char *busName = userData;

    opMessage(
        "I", HARNESS_NAME "_WCB",
        "writeCallback: %s, 0x" FMT_Ax,
        busName,
        addr
    );

}

//
// Simulate the processor for the indicated number of instructions
//
static void simulateProc(optProcessorP proc, Uns32 numInstr) {

    opMessage(
        "I", HARNESS_NAME,
        "Processor '%s': Run for %d instructions",
        opObjectHierName(proc),
        numInstr
    );

    optStopReason reason = opProcessorSimulate(proc, numInstr);

    opMessage(
        "I", HARNESS_NAME,
        "Processor '%s' stopped for reason '%s'",
        opObjectHierName(proc),
        opStopReasonString(reason)
    );

}


int main(int argc, const char *argv[]) {

    optBusP busLocal;           // the bus contained in the module
    optBusP busMapped;          // the bus contained in the module
    optBusP busExternal;        // a test bus defined in the testbench harness

    opSessionInit(OP_VERSION);
    opCmdParseStd(HARNESS_NAME, OP_AC_ALL, argc, argv);

    optModuleP mi = opRootModuleNew(0, 0, 0);

    optModuleP module = opModuleNew(mi, "module", "u1", 0, 0);
    if (!module) opMessage("F", "CONSTRUCT", "No Module 'u1' Created");

    busExternal = opBusNew(mi, "busExternal", 32, 0, 0);
    if (!busExternal) opMessage("F", "CONSTRUCT", "No Bus 'busExternal' Created");

    //
    // create a 'test' bus that uses callbacks to indicate reads and writes
    //
    opMessage("I", HARNESS_NAME, "Setting up bus regions as callbacks on test bus (busExternal)");
    opBusSlaveNew(busExternal, "all", 0, OP_PRIV_RWX, 0, 0xffffffff, readCallback, writeCallback, 0, "busExternal");

    //
    // get the name of the two busses we wish to perform mapping between
    //
    busLocal  = opObjectByName(mi, "u1/busLocal", OP_BUS_EN ).Bus;
    busMapped = opObjectByName(mi, "u1/busMapped", OP_BUS_EN ).Bus;

    //
    // enter pre-simulation phase (construction complete)
    //
    opMessage("I", HARNESS_NAME, "Root Module Simulate Phase");
    opRootModulePreSimulate(mi);

    // find the processor we will run instructions on
    opMessage("I", HARNESS_NAME, "Find processor 'u1/cpu1'");
    optProcessorP proc = opObjectByName(mi, "u1/cpu1", OP_PROCESSOR_EN).Processor;
    if(!proc) {
        opMessage("F", HARNESS_NAME "_NOCPU", "Could not find processor 'u1/cpu1'");
    }

    // Run 10 instructions on processor - this will cause a read access
    simulateProc(proc, 10);

    //
    // bridge region of busLocal to test bus 'busExternal'
    //
    opMessage("I", HARNESS_NAME, "Bridge region of 'busLocal' to 'busExternal'");
    opDynamicBridge(busLocal,busExternal, 0x00400000, 0x004000ff,0x00400000);

    // Run 4 instructions on processor - this will cause a read access
    simulateProc(proc, 4);

    //
    // bridge part of the region back to busMapped
    //
    opMessage("I", HARNESS_NAME, "Bridge partial region of 'busLocal' back to 'busLocal'");
    opDynamicBridge(busLocal,busMapped, 0x00400000, 0x0040000f,0x00400000);

    // Run 4 instructions on processor - this will cause a read access
    simulateProc(proc, 4);

    //
    // un-bridge region
    //
    opMessage("I", HARNESS_NAME, "UnBridge region of 'busLocal'");
    opDynamicUnbridge(busLocal, 0x00400000, 0x004000ff);

    // Run 4 instructions on processor - this will cause a 'Read privilege exception'
    simulateProc(proc, 4);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors

}

