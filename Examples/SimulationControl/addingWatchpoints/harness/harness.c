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

//
// callbacks causing an access to abort if called
//
OP_ADDR_WATCHPOINT_CONDITION_FN(readNotifier) {

    opMessage("I", "READ_NOTIFIER", "(%d) %s access "
                                           "at address 0x" FMT_Ax " (0x" FMT_Ax ")"
                                           " for '%s'",
                opWatchpointType(watchpoint),
                processor ? opObjectHierName(processor) : "artifact",
                VA, PA,
                (const char *)userData);

    return False;
}
OP_ADDR_WATCHPOINT_CONDITION_FN(writeNotifier) {

    opMessage("I", "WRITE_NOTIFIER", "(%d) %s access "
                                           "at address 0x" FMT_Ax " (0x" FMT_Ax ")"
                                           " for '%s'",
                opWatchpointType(watchpoint),
                processor ? opObjectHierName(processor) : "artifact",
                VA, PA,
                ((char const *)userData));

    return True;
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, 0, 0);
    optModuleP mi = opModuleNew(mr, "module", "u1", 0, 0);

    // Indicate that platform construction complete
    opRootModulePreSimulate(mr);

    // get bus in the module (only one)
    optBusP bus = opBusNext(mi, 0);
    if (!opBusReadWatchpointNew(
            bus,
            0x00400000, 0x0040000f,
            "bus read watchpoint",
            readNotifier
       )) {
        opMessage("E", "HARNESS", "Failed to set bus read watchpoint 0x00400000, 0x0040000f");
    }
    if (!opBusWriteWatchpointNew(
            bus,
            0x00400000, 0x0040000f,
            "bus write watchpoint",
            writeNotifier
       )) {
        opMessage("E", "HARNESS", "Failed to set bus write watchpoint 0x00400000, 0x0040000f");
    }

    // get memory in the module (only one)
    optMemoryP memory = opMemoryNext(mi, 0);
    if (!opMemoryReadWatchpointNew(
            memory,
            0x00400100, 0x0040010f,
            "memory read watchpoint",
            readNotifier
       )) {
        opMessage("E", "HARNESS", "Failed to set memory read watchpoint 0x00400100, 0x0040010f");
    }
    if (!opMemoryWriteWatchpointNew(
            memory,
            0x00400100, 0x0040010f,
            "memory write watchpoint",
            writeNotifier
       )) {
        opMessage("E", "HARNESS", "Failed to set bus memory watchpoint 0x00400100, 0x0040010f");
    }

    // get processor in the module (only one)
    optProcessorP processor = opProcessorNext(mi, 0);
    if (!opProcessorReadWatchpointNew(
            processor,
            False, 0x00400200, 0x0040020f,
            "processor virtual addressed read watchpoint",
            readNotifier
       )) {
        opMessage("E", "HARNESS", "Failed to set processor read watchpoint 0x00400200, 0x0040020f");
    }
    if (!opProcessorWriteWatchpointNew(
            processor,
            False, 0x00400200, 0x0040020f,
            "processor virtual addressed write watchpoint",
            writeNotifier
       )) {
        opMessage("E", "HARNESS", "Failed to set processor write watchpoint 0x00400200, 0x0040020f");
    }

    optStopReason stopReason = OP_SR_SCHED;

    processor = opRootModuleSimulate(mr);
    stopReason = processor ? opProcessorStopReason(processor) : OP_SR_EXIT;
    opMessage("I", "HARNESS", "Simulation stopped on processor '%s' for reason '%s'",
            processor ? opObjectName(processor) : "none",
            opStopReasonString(stopReason));

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

