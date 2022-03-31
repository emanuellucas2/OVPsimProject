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

#define MODULE_NAME "FreescaleKinetis64"

struct optionsS {
    Bool                 uart0console;
    Bool                 uart1console;
    Bool                 uart2console;
    Bool                 uart3console;
    Bool                 uart4console;
    Bool                 uart5console;
} options = {
    0
};


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;

#define UART0  MODULE_NAME "/uart0/"
#define UART1  MODULE_NAME "/uart1/"
#define UART2  MODULE_NAME "/uart2/"
#define UART3  MODULE_NAME "/uart3/"
#define UART4  MODULE_NAME "/uart4/"
#define UART5  MODULE_NAME "/uart5/"


////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

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
    // Set simulation time slice to value smaller than
    // character rate for 115000 baud rate (~70 uS per char)
    opRootModuleSetSimulationTimeSlice (mi, 0.0000035);
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

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    if (options.uart0console) {
        opParamBoolOverride(0, UART0 "console", True);
    }
    if (options.uart1console) {
        opParamBoolOverride(0, UART1 "console", True);
    }
    if (options.uart2console) {
        opParamBoolOverride(0, UART2 "console", True);
    }
    if (options.uart3console) {
        opParamBoolOverride(0, UART3 "console", True);
    }
    if (options.uart4console) {
        opParamBoolOverride(0, UART4 "console", True);
    }
    if (options.uart5console) {
        opParamBoolOverride(0, UART5 "console", True);
    }

    optModuleP mi = opRootModuleNew(&modelAttrs, MODULE_NAME, 0);
    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

