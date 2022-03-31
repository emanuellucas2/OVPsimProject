/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>

#include "op/op.h"


#define MODULE_NAME "FaultInjector"


typedef struct optModuleObjectS {
    // insert module persistent data here
    optTime          nextTime;
    optTime          timeIncr;
    optTriggerEventP trigger;
    optModuleP       root;
    optModuleP       board;
    optNetP          netReset;
    optMemoryP       mem[5];
} optModuleObject;


optModuleObject object;

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    // insert pre simulation code here
    Bool valid;
    Uns32 param1 = opObjectParamUns32Value(mi, "config", &valid);

    opMessage("I", MODULE_NAME, "Pre-Simulate; find objects (%d/%u)", param1, valid);

    // find components in the virtual platform we wish to inject faults into
    // get parent
    object->root = opObjectParent(mi).Module;
    // get the board (assumes there is a single module that represents the board)
    object->board = opModuleNext(object->root, NULL);
    // the board contains the Zynq Module

    // memories
    object->mem[0] = opObjectByName(object->board, "Zynq/Zynq_PS/DDR0", OP_MEMORY_EN).Memory;
    object->mem[1] = opObjectByName(object->board, "Zynq/Zynq_PS/DDR1", OP_MEMORY_EN).Memory;
    object->mem[2] = opObjectByName(object->board, "Zynq/Zynq_PS/DDR2", OP_MEMORY_EN).Memory;
    Uns32 i;
    for (i=0;i<3;i++) {
        if(object->mem[i]) opMessage("I", MODULE_NAME, "Found Memory DDR%d", i);
    }


    // nets
    object->netReset  = opObjectByName(object->board, "Zynq/Zynq_PS/reset_A9_CPU1",  OP_NET_EN).Net;
    if(object->netReset) {
        opMessage("I", MODULE_NAME, "Found CPU1 reset net");
    }
}

OP_TRIGGER_FN(timeTrigger) {
    optModuleObjectP object = (optModuleObjectP) userData;

    object->nextTime += object->timeIncr;

    opMessage("I", MODULE_NAME, "Time Trigger CB: Now %g Next Stop Time %g",
                        (double)now,
                        (double)object->nextTime);
    // TODO: Inject faults

    // finish simulation or setup next callback
    if(now < 10.0) {
        object->trigger = opModuleTriggerAdd(mi, object->timeIncr, timeTrigger, (void*)object);
    } else {
        opMessage("I", MODULE_NAME, "Time Trigger CB: Finish Simulation at %g",
                            (double)now);
        opModuleFinish(object->root, 0);
    }
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    opMessage("I", MODULE_NAME, "moduleSimulateStart");

    // set next time callback
    object->timeIncr = 0.01;
    object->nextTime += object->timeIncr;

    object->trigger = opModuleTriggerAdd(mi, object->timeIncr, timeTrigger, (void*)object);

    opMessage("I", MODULE_NAME, "moduleSimulateStart: Now %g Next Stop Time %g",
                        (double)opModuleCurrentTime(object->root),
                        (double)object->nextTime);
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    opMessage("I", MODULE_NAME, "modulePostSimulate");
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}

#include "module.igen.h"
