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


#define MODULE_NAME "HeteroArmNucleusMIPSLinux"

struct optionsS {
    Bool                 uartconsole;
    Uns32                uartport;
    Bool                 nographics;
} options = {
    0
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

//
// Component names
//
#define ARMUART1    "armSub1uart1"
#define ARMUART2    "armSub1uart2"
#define MIPSVGA     "mipsMainvga"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    optParamP paramList = NULL;

    //
    // Check to see what UART options are used
    //
    Uns32 setUartport = opCmdArgUsed (parser,"uartport");
    if (options.uartconsole && setUartport) {
        // Error
        opMessage("E", MODULE_NAME"_CFG", "Can only specify one of --uartport and --uartconsole");
    } else if (setUartport) {
        opMessage("I", MODULE_NAME"_CFG", "uartport %d", options.uartport);
        // Override the parameter to cause the UART0 to open port "portnum"
        paramList = opParamUns32Set(paramList,  ARMUART1"/portnum", options.uartport);

    } else if (options.uartconsole) {
        opMessage("I", MODULE_NAME"_CFG", "uartconsole %d", options.uartconsole);
        // Override the parameter to cause the UART1 to open a console
        paramList = opParamBoolSet(paramList,  ARMUART1"/console", 1);
    }

    if (options.uartconsole || setUartport) {
        opMessage("I", MODULE_NAME"_CFG", "disconnect & diag");
        paramList = opParamBoolSet(paramList,  ARMUART1"/finishOnDisconnect", 1);
        paramList = opParamUns32Set(paramList,  ARMUART1"/diagnosticlevel", 1);
    }

    if (options.nographics) {
        opMessage("I", MODULE_NAME"_CFG", "disable graphics");
        paramList = opParamBoolSet(paramList,  MIPSVGA"/disable", 1);
    }

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        paramList
    );
    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

