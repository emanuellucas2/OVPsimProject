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


#define MODULE_NAME "BareMetalOr1kSingle"

struct optionsS {
} options = {
};


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;



// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    // insert pre simulation code here
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}

#include "platform.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(&modelAttrs, MODULE_NAME,
                        OP_PARAMS (
                                    OP_PARAM_BOOL_SET  (OP_FP_VERBOSE,        1),
                                    OP_PARAM_BOOL_SET  (OP_FP_STOPONCONTROLC, 1)
                                  ));

    optProcessorP final = opRootModuleSimulate(mi);

    // was simulation interrupted or did it complete
    if(final && (opProcessorStopReason(final)==OP_SR_INTERRUPT)) {
        opPrintf("*** simulation interrupted\n");
    }

    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

