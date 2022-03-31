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

#define HARNESS_NAME    "harness"
#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"

#define NUM_INPUTS  32

// Control structure
struct controlS {

    optTime   delta;
    Uns32     timeslot;

    optNetP   inputs[NUM_INPUTS];
    Bool      current[NUM_INPUTS];

} control;

static Bool stimulusTable[][NUM_INPUTS] = {

    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

#define TIMESLOTS (sizeof(stimulusTable) / sizeof(stimulusTable[0]))

static void stimulate(optModuleP mi) {

    Uns32 pin;
    for(pin = 0; pin < NUM_INPUTS; pin++) {
        Bool v = stimulusTable[control.timeslot][pin];

        if(v != control.current[pin]) {
            opMessage("I", HARNESS_NAME, "At %f (timeslot %u)  pin %u = %u\n",
                            (float)opModuleCurrentTime(mi),
                            control.timeslot,
                            pin,
                            v);
            opNetWrite(control.inputs[pin], v);
            control.current[pin] = v;
        }
    }
    control.timeslot++;
}

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd (argv[0], OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, 0, 0);
    optModuleP mi = opModuleNew(mr, "module", "u1", 0, 0);

    // Indicate that platform construction complete
    opRootModulePreSimulate(mr);

    control.delta        = 0.001;  // 1mS
    control.timeslot     = 0;

    Uns32 i;
    for(i= 0; i < NUM_INPUTS; i++) {
        control.inputs[i] = opObjectByName(mi, opSprintf("int%u", i), OP_NET_EN).Net;
    }

    // get processor in the module (only one)
    optProcessorP processor = opProcessorNext(mi, 0);

    // run simulation
    optTime       myTime     = control.delta;
    optStopReason stopReason = OP_SR_SCHED;
    Uns32         instr      = 100000;
    do {

        // move time forward by time slice on root module
        // NOTE: This matches the standard scheduler which moves time forward in
        //       the system and then executes instructions on all processors
        opRootModuleTimeAdvance(mr, myTime);

        // run processor for number of instructions calculated for time slice
        stopReason = opProcessorSimulate(processor, instr);

        // check stop reason
        if ((stopReason!=OP_SR_SCHED) && (stopReason!=OP_SR_HALT)) {

            opMessage(
                "I", HARNESS_NAME,
                "Simulation Complete (%s)",
                opStopReasonString(stopReason)
            );

            break;  // finish simulation loop

        }

        stimulate(mi);              // generate interrupt net stimulus

        myTime += control.delta;    // set next simulation time

    } while (control.timeslot < TIMESLOTS);

    opMessage("I", HARNESS_NAME, "Finished at timeslot: %u\n", control.timeslot);

    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

