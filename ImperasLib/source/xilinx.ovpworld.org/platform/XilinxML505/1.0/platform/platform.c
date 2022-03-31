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


#include "op/op.h"

#define MODULE_NAME "XilinxML505"

struct optionsS {
    const char*          kernel;
    Bool                 uartconsole;
    Uns64                uartport;
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

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);
    opCmdUsageMessage(parser, "Basic Usage. <Linux Xilinx ML505 executable> --kernel <kernel image> --uartconsole");

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        0
    );

    optProcessorP cpu_c = opProcessorNext (mi, 0); // Get processor - only one

    if(options.kernel) {
        if (!opProcessorApplicationLoad(cpu_c, options.kernel, OP_LDR_VERBOSE|OP_LDR_SET_START, 0)) {
            opMessage("F", MODULE_NAME, "Failed to load %s", options.kernel);
            opSessionExit(1);
            return 1;
        }
    } else {
        opMessage("F", MODULE_NAME, "Must specify argument --kernel");
    }

    Bool setUartport = opCmdArgUsed (parser,"uartport");
    if (setUartport) {
        opParamUns64Override(mi, "RS232_Uart_1/portnum",  options.uartport);
    } else if (options.uartconsole) {
        opParamBoolOverride(mi, "RS232_Uart_1/console",  1);
    }

    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}


////////////////////////////////////////////////////////////////////////////////
