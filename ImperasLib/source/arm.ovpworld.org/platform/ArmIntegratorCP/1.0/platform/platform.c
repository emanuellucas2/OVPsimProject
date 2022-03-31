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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"


#define MODULE_NAME "ArmIntegratorCP"

struct optionsS {
    const char*          kernel;
    const char*          ramdisk;
    Uns64                uartport;
    Bool                 uartconsole;
    const char*          semihost;
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

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

#define UART        "uart1"
#define SMARTLOADER "smartLoader"
#define LCD         "lcd"
#define CPU         "arm1"

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);
    opCmdUsageMessage(parser, "Basic Usage. Linux ArmIntegratorCP --kernel <kernel image> --ramdisk <initial ramdisk>. BareMetal ArmIntegratorCP --program <elf file> --nographics");

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        OP_PARAMS(
             OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    //
    // Check to see what UART options are used
    //
    Bool setUartport = opCmdArgUsed (parser,"uartport");
    if (options.uartconsole && setUartport) {
        opMessage("E", MODULE_NAME"_CFG", "Can only specify one of --uartport and --uartconsole");
    } else if (setUartport) {
        opParamUns32Override(NULL, MODULE_NAME"/"UART"/portnum", options.uartport);            // Override the parameter to cause the UART to open port "portnum"

    } else if (options.uartconsole) {
        opParamBoolOverride(NULL, MODULE_NAME"/"UART"/console", "1");            // Override the parameter to cause the UART to open a console
    }

    if(options.nographics) {
        opParamBoolOverride(NULL, MODULE_NAME"/"LCD"/noGraphics", "1");
    }

    // Check to see if the program argument is loading a non Linux Kernel
    if(opCmdArgUsed (parser,"program")) {
        if(opCmdArgUsed (parser,"kernel")) {
            opMessage("E", MODULE_NAME, "Arguments '--program' and '--kernel' cannot be used together");
        } else {
            opMessage("I", MODULE_NAME, "Loading baremetal application, disabling '%s'", SMARTLOADER);
            opParamBoolOverride(NULL, MODULE_NAME"/"SMARTLOADER"/disable", "1");
        }

    } else {
        if(options.kernel) {
            opParamStringOverride(NULL, MODULE_NAME"/"SMARTLOADER"/kernel", options.kernel);
        }
        if(options.ramdisk) {
            opParamStringOverride(NULL, MODULE_NAME"/"SMARTLOADER"/initrd", options.ramdisk);
        }
    }

    if(opCmdArgUsed (parser,"program") && (options.semihost)) {
        // get processor (only one so can obtain next)
        optProcessorP processor =  opProcessorNext(mi, NULL);
        opProcessorExtensionNew (processor, options.semihost, "semihost", NULL);
    }


    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////////////
