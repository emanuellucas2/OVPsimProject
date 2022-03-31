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


#define MODULE_NAME "MipsMalta"

#ifdef PREFIX
#define PREFIX PREFIX "_PLATFORM_INIT"
#else
#define PREFIX        "PLATFORM_INIT"
#endif

struct optionsS {
    const char*          kernel;
    const char*          ramdisk;
    const char*          disk;
    const char*          root;
    Uns64                pagebits;
    const char*          console;
    Bool                 finishonhalt;
    Bool                 redir;
    Bool                 nographics;
    const char*          tftproot;
    const char*          bootimage;
} options = {
    0
};


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;


#define SMARTLOADER "Core_Board_SDRAM_promInit/"
#define NIC         "PCI_NET/"
#define VGA         "vga/"
#define FPGA        "maltaFpga/"
#define IDE         "PIIX4-IDE/"
#define UART0       "uartTTY0/"


// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    if (options.kernel) {
        opParamStringOverride(mi, SMARTLOADER "kernel", options.kernel);
    }
    if (options.ramdisk) {
        opParamStringOverride(mi, SMARTLOADER "initrd", options.ramdisk);
    }
    if (options.root) {
        opParamStringOverride(mi, SMARTLOADER "root", options.root);    // Set the root boot
    }
    if (options.disk) {
        opParamStringOverride(mi, IDE "Drive0Name", options.disk);        // Set the file used for the drive
    }
    if (options.finishonhalt) {
        opParamBoolOverride(mi, FPGA "stoponsoftreset",  1);
    }
    if (options.redir) {
        opParamStringOverride(mi, NIC "redir", "tcp:15901:10.0.2.15:5901,tcp:11001:10.0.2.15:11001");
    }
    if(options.tftproot) {
        opParamStringOverride(mi, NIC "tftpPrefix", options.tftproot);
    }
    if(options.nographics) {
        opParamBoolOverride(mi, VGA "noGraphics", 1);
        opParamBoolOverride(mi, UART0 "console", 1);
    }
    if (options.bootimage) {
        opParamStringOverride(mi, SMARTLOADER "bootimage", options.bootimage);
    }
    if (options.pagebits) {
        opParamUns64Override(mi, SMARTLOADER "pagebits", options.pagebits);
    }
    if (options.console) {
        char buf[64];
        snprintf(buf, sizeof(buf), "console=%s", options.console);
        opParamStringOverride(mi, SMARTLOADER "command",  buf);
    }

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    // insert pre simulation code here
    if (options.kernel) {
        // assume single processor
        optProcessorP   processor = opProcessorNext(mi, NULL);
        // load the Linux kernel image into memory
        opProcessorApplicationLoad(processor, options.kernel,  OP_LDR_DEFAULT, 0);
    }
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
    opCmdUsageMessage(parser, "Basic Usage. Linux MipsMalta executable --kernel <kernel image> --console <Linux boot console> --ramdisk <initial ramdisk> --disk <disk file> --root <root partition to boot from disk");

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(&modelAttrs, MODULE_NAME, 0);
    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

