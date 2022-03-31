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
//                          Tue Aug 27 12:57:13 2019
//
////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define MODULE_NAME "ArmVersatileExpress"

struct optionsS {
    const char*          kernel;
    const char*          ramdisk;
    const char*          command;
    const char*          sdcard;
    const char*          bootcode;
    Uns64                uartport;
    Bool                 uartconsole;
    Bool                 nographics;
} options = {
    0
};

typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;

OP_PROCESSOR_ITERATOR_FN(setStartAddress) {

    Uns32 start = 0x60000000;
    opMessage("I", MODULE_NAME"_STARTUP", "Set start address for %s to 0x%08x", opObjectHierName(processor), start);
    opProcessorPCSet(processor, start);
}

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);
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

#define UART0       "uart0"
#define UART1       "uart1"
#define SMARTLOADER "smartLoader"
#define MMC         "mmc1"
#define LCD         "lcd1"

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);
    opCmdUsageMessage(parser, "Basic Usage. Linux ArmVersatileExpress executable --kernel <kernel image> --ramdisk <initial ramdisk>");

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    //
    // Check to see what UART options are used
    //
    Bool setUartport = opCmdArgUsed (parser,"uartport");
    if (options.uartconsole && setUartport) {
        opMessage("E", MODULE_NAME"_CFG", "Can only specify one of --uartport and --uartconsole");
    } else if (setUartport) {
        opParamUns32Override(NULL, MODULE_NAME"/"UART0"/portnum", options.uartport);            // Override the parameter to cause the UART0 to open port "portnum"
        opParamUns32Override(NULL, MODULE_NAME"/"UART1"/portnum", options.uartport + 1);            // Override the parameter to cause the UART1 to open port "portnum+1"

    } else if (options.uartconsole) {
        opParamBoolOverride(NULL, MODULE_NAME"/"UART0"/console", 1);            // Override the parameter to cause the UART0 to open a console
        opParamBoolOverride(NULL, MODULE_NAME"/"UART1"/console", 1);            // Override the parameter to cause the UART1 to open a console
    }
    if (options.uartconsole || setUartport) {
        opParamBoolOverride(NULL, MODULE_NAME"/"UART0"/finishOnDisconnect", 1);
        opParamUns32Override(NULL, MODULE_NAME"/"UART0"/diagnosticlevel", 1);
        opParamBoolOverride(NULL, MODULE_NAME"/"UART1"/finishOnDisconnect", 1);
        opParamUns32Override(NULL, MODULE_NAME"/"UART1"/diagnosticlevel", 1);
    }

    if(options.nographics) {
        opParamBoolOverride(NULL, MODULE_NAME"/"LCD"/noGraphics", 1);
    }

    //
    // Setup the Linux command line
    //
    char command[256] = "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0";
    if(opCmdArgUsed (parser,"command")) {
        // Android boot requires "androidboot.console=ttyAMA0 vga=771", specified on command line
        strcat(command, " ");
        strcat(command, options.command);
    }
    opParamStringOverride(NULL, MODULE_NAME"/"SMARTLOADER"/command", command);

    //
    // Setup the SmartLoader for the Linux Kernel and ramdisk
    //
    if(options.kernel) {
        opParamStringOverride(NULL, MODULE_NAME"/"SMARTLOADER"/kernel", options.kernel);
    }
    if(options.ramdisk) {
        opParamStringOverride(NULL, MODULE_NAME"/"SMARTLOADER"/initrd", options.ramdisk);
    }

    if(opCmdArgUsed (parser,"sdcard")) {
        opParamStringOverride(NULL, MODULE_NAME"/"MMC"/SD_DRIVE", options.sdcard);
    }

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        OP_PARAMS(
             OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    if(opCmdArgUsed (parser,"bootcode")) {
        optBusP smbus_b = opObjectByName(mi, "smbus", OP_BUS_EN).Bus;
        if(!smbus_b) opMessage("E", MODULE_NAME, "Could not find Bus for loading Application '%s'", options.bootcode);
        optApplicationP image = opBusApplicationLoad(smbus_b, options.bootcode, OP_LDR_VERBOSE, 0);
        if (image) {
            opParamUns32Override(NULL, MODULE_NAME"/"SMARTLOADER"/bootaddr", opApplicationEntry(image));
        } else {
            opMessage("E", MODULE_NAME, "Failed to load '%s'", options.bootcode);
        }
    }

    optProcessorP cpu_c = opObjectByName(mi, "cpu", OP_PROCESSOR_EN).Processor;
    if(!cpu_c) opMessage("E", MODULE_NAME, "Could not find Processor");
    opProcessorIterChildren(cpu_c, setStartAddress, 0);

    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////////////
