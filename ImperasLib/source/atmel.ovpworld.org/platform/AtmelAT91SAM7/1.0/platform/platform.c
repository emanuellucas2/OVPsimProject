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


#define MODULE_NAME "AtmelAT91SAM7"

struct optionsS {
    const char*          kernel;
    Uns32                uartport;
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

#define USART0  "USART0"

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
    // Check to see if UART options are provided
    //
    Uns32 setUartport = opCmdArgUsed (parser,"uartport");
    if (setUartport) {
        opMessage("I", MODULE_NAME"_CFG", "uartport %d", options.uartport);
        // Override the parameter to cause the UART0 to open port "portnum"
        paramList = opParamUns32Set(paramList, USART0"/portnum", options.uartport);
    } else {
        // Override the parameter to cause the UART0 to open a terminal
        paramList = opParamBoolSet(paramList, USART0"/console",  1);
    }
    // add finish when UART socket disconnected and diagnostics messages
    paramList = opParamBoolSet(paramList,  USART0"/finishOnDisconnect", 1);
    paramList = opParamUns32Set(paramList, USART0"/diagnosticlevel",    1);

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        paramList
    );

    // Load default image if not specified
    if(!options.kernel) {
        options.kernel="linux";
    }

    opMessage("I", MODULE_NAME"_LD", "Loading kernel file %s", options.kernel);
    // get the handle for the processor in the module (only one)
    optProcessorP processor = opProcessorNext(mi, 0);
    optLoaderControls loadOptions = OP_LDR_SET_START | OP_LDR_VERBOSE;
    if(!opProcessorApplicationLoad(processor, options.kernel, loadOptions, 0)){
        opMessage("E", MODULE_NAME "_LDF", "Failed to load kernel file '%s'", options.kernel);
        opSessionExit(1);
        return 1;
    }

    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

