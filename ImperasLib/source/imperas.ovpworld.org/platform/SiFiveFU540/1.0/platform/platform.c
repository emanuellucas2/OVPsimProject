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


#define MODULE_NAME "SiFiveFU540"

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


struct optionsS {
    const char*  bblElf;
    const char*  bblBin;
    const char*  diskImage;
    const char*  dtb;
} options = {
    .bblElf     = NULL,
    .bblBin     = NULL,
    .diskImage  = NULL,
    .dtb        = NULL,
};

static void cmdParser(optCmdParserP parser) {
    opCmdParserAdd(parser, "bblelf",       0,  "string", "FixedPlatform", OP_FT_STRINGVAL,   &options.bblElf,     "Name of bbl ELF file to load", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "bblbin",       0,  "string", "FixedPlatform", OP_FT_STRINGVAL,   &options.bblBin,     "Name of bbl binary image file to load", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "dtb",          0,  "string", "FixedPlatform", OP_FT_STRINGVAL,   &options.dtb,        "Name of dtb file to load", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "diskimage",    0,  "string", "FixedPlatform", OP_FT_STRINGVAL,   &options.diskImage,  "Name of disk image to use in delta mode (writes not saved)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "diskimagerw",  0,  "string", "FixedPlatform", OP_FT_STRINGVAL,   &options.diskImage,  "Name of disk image to use in rw mode (writes written to disk image - disk corruption possible if not shut down properly)", OP_AC_ALL, 0, 0);
}

static const char *helpMessage =
        "\n"
        "To see all command line options:\n"
        "    %E --helpall\n"
        "To boot Linux using a bbl elf file:\n"
        "    %E --bblelf <bbl ELF file name> --dtb <Device Tree Blob file name>\n"
        "To run a baremetal elf file, starting simulation at the elf file start address:\n"
        "    %E --program <ELF file name>\n"
        "To attach a disk drive image in delta mode (writes not saved):\n"
        "       --diskimage < drive image file name>\n"
        "To attach a disk drive image in read/write mode (writes written to disk image):\n"
        "       --diskimagerw < drive image file name>\n"
        "To trace instructions:\n"
        "       --trace\n"
        "To start and connect to gdb:\n"
        "       --gdbconsole\n"
       "Examples:\n"
        "    %E --bblelf Linux/bbl --dtb Linux/FU540.dtb\n"
        ;

static void exitWithErrors(void) {
    opSessionExit(1);
}

static void cmdParserCheck(optCmdParserP parser, optParamP *params) {

    Bool showoverrides      = opCmdArgUsed(parser, "showoverrides")
                            | opCmdArgUsed(parser, "showmodeloverrides")
                            | opCmdArgUsed(parser, "showsystemoverrides");
    Bool showvariants       = opCmdArgUsed(parser, "showvariants");
    Bool showinstances      = opCmdArgUsed(parser, "showinstances");

    if (opCmdArgUsed(parser,"nosimulation") || opCmdArgUsed(parser,"writexml")) {

        // No checking when simulation inhibited
        // (used during build to extract modules, xml, documentation, etc...)

    } else if (showoverrides|showvariants|showinstances) {

        // Not running so don't check for valid params

    } else {

        Uns32 programsSpecified = opCmdArgUsed(parser,"bblelf")
                                + opCmdArgUsed(parser,"bblbin")
                                + opCmdArgUsed(parser,"objfileuseentry")
                                + opCmdArgUsed(parser,"program")
                                + opCmdArgUsed(parser,"objfile")
                                + opCmdArgUsed(parser,"objfilenoentry");

        if (programsSpecified == 0) {

            opMessage("E", MODULE_NAME, "Must specify a program to be loaded using one of --bblelf, --bblbin, --program, or --objfile*");
            exitWithErrors();

        } else if (programsSpecified > 1) {

            opMessage("E", MODULE_NAME, "Only one of --bblelf, --bblbin, --program, or --objfile* may be specified");
            exitWithErrors();

        } else {

            Bool linuxUsed = False;

            if (opCmdArgUsed (parser, "bblelf")) {
                // Load the specified elf file after module created
                linuxUsed = True;
            }

            if (opCmdArgUsed (parser, "bblbin")) {
                // Pass the image file name to the smart loader
                *params = opParamStringSet(*params, MODULE_NAME "/smartLoader/bootimage", options.bblBin);
                linuxUsed = True;
            }

            if (opCmdArgUsed (parser,"dtb")) {
                // Pass the dtb file name to the smart loader
                *params = opParamStringSet(*params, MODULE_NAME "/smartLoader/dtb", options.dtb);
            } else if (linuxUsed) {
                opMessage("E", MODULE_NAME, "Must specify --dtb when running bbl");
                exitWithErrors();
            }

            if (opCmdArgUsed (parser,"diskimage") || opCmdArgUsed (parser,"diskimagerw")) {
                // Pass the disk image file name to the virtio block device
                *params = opParamStringSet(*params, MODULE_NAME "/vbd0/VB_DRIVE", options.diskImage);
                if (!opCmdArgUsed (parser,"diskimagerw")) {
                    // Open the disk image file in delta mode
                    *params = opParamBoolSet(*params, MODULE_NAME "/vbd0/VB_DRIVE_DELTA", True);
                }
            }
        }
    }
}

//
// Add overrides for local command line parameters
//
static void overrideParams(optModuleP mi, optCmdParserP parser) {
    if (opCmdArgUsed (parser, "bblelf")) {
        optProcessorP processor = opObjectByName(mi, MODULE_NAME "/E51_hart0", OP_PROCESSOR_EN).Processor;
        opProcessorApplicationLoad(processor, options.bblElf, OP_LDR_DEFAULT, 0);
    }
}

int main(int argc, const char *argv[]) {

#if (IMPERAS_FIXED_PLATFORM)
    opSessionInit2(OP_VERSION, personality, vfs);
#else
    opSessionInit(OP_VERSION);
#endif

    optParamP     params = NULL;
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_EXT2);

    // Add local options and help to parser
    cmdParser(parser);
    opCmdUsageMessage(parser, helpMessage);

    if (!opCmdParseArgs(parser, argc, argv)) {
        opMessage("E", MODULE_NAME, "Command line error. Simulation will not be run");
        exitWithErrors();
    } else {
        cmdParserCheck(parser, &params);
    }

    // turn off the CSR unimplemented message, some kernels expect to trap on certain registers e.g. rdtime
    opMessageDisable ("RISCV_IHPMU");

    // Linux Kernel and Berkeley Boot Loader 
    //    supplied by SiFive with their HiFive Freedom Unleashed board
    //    source available from https://github.com/sifive/freedom-u-sdk
    // There is inter-core interaction in stop_machine.c:175 multi_cpu_stop() that waits for all processors
    // to reach the same state. This causes apparent slow simulation without the reduction in quantum size.
    params = opParamDoubleSet(params, OP_FP_QUANTUM, 0.00005);

    optModuleP mi = opRootModuleNew(&modelAttrs, "", params);

    overrideParams(mi, parser);

    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

