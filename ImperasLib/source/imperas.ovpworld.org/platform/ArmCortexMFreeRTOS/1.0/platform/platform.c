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
//                           Imperas/OVP Development
//                          Tue Aug  6 14:20:42 2019
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>

#include "op/op.h"


#define MODULE_NAME "ArmCortexMFreeRTOS"

struct optionsS {
    const char*          rtos;
} options = {
    0
};

typedef struct optModuleObjectS {
} optModuleObject;

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    instantiateComponents(mi, object);
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
}

static OP_DESTRUCT_FN(moduleDestruct) {
}

#include "platform.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        OP_PARAMS(
             OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    optProcessorP cpu1_c = opProcessorNext (mi, NULL); // Get processor - only one

    if (options.rtos) {
        // load the FreeRTOS image into memory
        if (!opProcessorApplicationLoad(cpu1_c, options.rtos, OP_LDR_DEFAULT, 0)) {
            opPrintf("%s", opLastMessage());
            opSessionTerminate();
            opSessionExit(1);
        }
    }

    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////////////
