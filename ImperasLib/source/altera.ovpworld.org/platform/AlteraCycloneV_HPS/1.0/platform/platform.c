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
//                          Fri Aug 30 10:31:40 2019
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "op/op.h"

#define MODULE_NAME "AlteraCycloneV_HPS"

struct optionsS {
    const char*          ZIMAGE;
    Uns32                ZIMAGEADDR;
    const char*          INITRD;
    Uns32                INITRDADDR;
    const char*          LINUXSYM;
    Uns32                BOARDID;
    Uns32                LINUXMEM;
    const char*          LINUXCMD;
    const char*          APP0;
    const char*          APP1;
    const char*          BOOT;
    const char*          IMAGE0;
    Uns32                IMAGE0ADDR;
    const char*          IMAGE0SYM;
    const char*          IMAGE1;
    Uns32                IMAGE1ADDR;
    const char*          IMAGE1SYM;
    const char*          UART0PORT;
    const char*          UART1PORT;
} options = {
    0
};

typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;


// Platform defaults to 1GB memory
#define MEM_SIZE  0x40000000

// Default Linux Command line
#define CMD_LINE "console=ttyS0"

//
// Return the entry address in the Boot file, if one is specified.
// Cache the result so we don't read the file over and over
//
static Uns32 getBootElfEntry() {

    static Addr bootElfEntry = -1ULL;

    if (bootElfEntry != -1ULL) {

        // Already set - no action

    } else if (options.BOOT) {
        ordObjectInfo info;
        if(!opApplicationHeaderRead(options.BOOT, &info)) {
            opMessage("E", MODULE_NAME"_URB", "Unable to load Boot code file '%s'", options.BOOT);
        }
        if(info.entry>>32) {
            opMessage("E", MODULE_NAME"_EE", "Entry address for '%s' exceeds 32-bit address", options.BOOT);
        }
        bootElfEntry = info.entry;

    }

    return bootElfEntry;

}

//
// Set non-zero default configuration values - may be overridden from command line
//
static void setDefaults() {

    options.IMAGE0ADDR = -1;   // Allows detecting when not set
    options.IMAGE1ADDR = -1;
    options.ZIMAGEADDR = -1;
    options.INITRDADDR = -1;
    options.BOARDID    = -1;

}

#define SMARTLOADER MODULE_NAME"/smartLoader/"
#define UART0       MODULE_NAME"/uart0/"
#define UART1       MODULE_NAME"/uart1/"

//
// Set overrides for attributes affected by command line options
//
static void setOverrides() {

    if (options.ZIMAGE) {

        // Linux is being used - override any Linux command line options
        Uns32 memsize = options.LINUXMEM ? options.LINUXMEM : MEM_SIZE;

        opParamStringOverride(NULL, SMARTLOADER"kernel", options.ZIMAGE);

        if (options.LINUXCMD || options.LINUXMEM) {

            if(!options.LINUXCMD || (strstr(options.LINUXCMD, "mem=")==NULL)) {
                // Add configured memory size to command string
                char commandstr[1024];
                snprintf (
                    commandstr, sizeof(commandstr),
                    "mem=%uM %s",
                    memsize>>20,
                    options.LINUXCMD ? options.LINUXCMD : CMD_LINE
                );
                opParamStringOverride(NULL, SMARTLOADER"command", commandstr);
            } else {
                opParamStringOverride(NULL, SMARTLOADER"command", options.LINUXCMD);
            }

        }

        if (options.BOARDID != -1) {
            opParamUns32Override(NULL, SMARTLOADER"boardid", options.BOARDID);
        }

        if (options.LINUXMEM) {
            opParamUns32Override(NULL, SMARTLOADER"memsize", (Uns32)memsize);
        }

        if (options.ZIMAGEADDR != -1) {
            opParamUns32Override(NULL, SMARTLOADER"kerneladdr", options.ZIMAGEADDR);
        }

        if (options.BOOT) {
            opParamUns32Override(NULL, SMARTLOADER"bootaddr", getBootElfEntry() );
        }

        if (options.INITRD) {
            opParamStringOverride(NULL, SMARTLOADER"initrd",     options.INITRD);
        }
        if (options.INITRDADDR != -1) {
            opParamUns32Override(NULL, SMARTLOADER"initrdaddr", options.INITRDADDR);
        }

    } else {

        // Disable smart loader if LINUX is not used
        opParamStringOverride(NULL, SMARTLOADER"disable", "1");

    }

    if (options.UART0PORT) {
        Uns32 portNum;
        if (strcmp(options.UART0PORT, "auto") == 0) {
            opParamStringOverride(NULL, UART0"console", "1");
        } else if (sscanf(options.UART0PORT, "%i", &portNum) == 1) {
            opParamStringOverride(NULL, UART0"portnum", options.UART0PORT);
        } else {
            opMessage(
                "W", MODULE_NAME"_IO",
                "Invalid argument for uart0port: '%s'. Must be 'auto' or a number.",
                options.UART0PORT
            );
        }
    }

    if (options.UART1PORT) {
        Uns32 portNum;
        if (strcmp(options.UART1PORT, "auto") == 0) {
            opParamStringOverride(NULL, UART1"console", "1");
        } else if (sscanf(options.UART1PORT, "%i", &portNum) == 1) {
            opParamStringOverride(NULL, UART1"portnum", options.UART1PORT);
        } else {
            opMessage(
                "W", MODULE_NAME"_IO",
                "Invalid argument for uart1port: '%s'. Must be 'auto' or a number.",
                options.UART1PORT
            );
        }
    }

}

//
// Load an ELF file on the processor
//
static optApplicationP loadElf(optProcessorP processor, const char *appName) {

    optApplicationP image;

    image = opProcessorApplicationLoad(processor, appName, OP_LDR_VERBOSE, 0);

    if (!image) {
        opMessage(
            "F", MODULE_NAME"_ULF",
            "unable to load file %s on %s",
            appName, opObjectHierName(processor)
        );
    }

    return image;

}

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

//
// Load the binary image file at the indicated address
// Returns number of bytes loaded or 0 if an error
//
static Uns32 loadImage(optProcessorP processor, const char *filename, Uns32 addr) {

    Int32 fd = open(filename, O_RDONLY | O_BINARY);

    if (fd < 0) {
        opMessage("E", MODULE_NAME, "Cannot open image file %s", filename);
        return 0;
    }

    // Get the size of the file
    Int32 size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    // Copy the file to simulated memory
    Uns32 bytes = size;
    Uns32 dest  = addr;
    char  buff[BYTES_PER_ACCESS];
    while (bytes) {

        Uns32 thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;

        thisAccess = read(fd, buff, thisAccess);

        if (!opProcessorWrite(processor, dest, buff, sizeof(Uns32), thisAccess, True, OP_HOSTENDIAN_TARGET)) {

            opMessage(
                "E", MODULE_NAME"_UWI",
                "Unable to write image file %s to simulated memory: failed at 0x%08x",
                filename, dest
            );

            close(fd);
            return 0;

        }

        dest  += thisAccess;
        bytes -= thisAccess;

    }

    close(fd);

    opMessage(
            "I", MODULE_NAME"_IFL",
            "Image file %s loaded (%u bytes) on %s",
            filename, size, opObjectHierName(processor)
    );

    return size;
}

//
// Load a symbol file on a processor
//
static void loadSymbols(optProcessorP processor, const char *symFile) {
    opProcessorApplicationLoad(processor, symFile, OP_LDR_SYMBOLS_ONLY, 0);
    opMessage(
        "I", MODULE_NAME"_SFL",
        "Symbols file %s loaded on %s",
        symFile, opObjectHierName(processor)
    );
}

//
// Do application setup for each leaf processor
//
static OP_PROCESSOR_ITERATOR_FN(setupApplication) {

    if (opProcessorIsLeaf(processor)) {

        Uns32 smpIndex = opProcessorIndex(processor);

        if (smpIndex > 1) {

            opMessage(
                "E", MODULE_NAME"_TMP",
                "%s: Only 2 processor cores supported on this platform",
                opObjectHierName(processor)
            );

        } else {

            const char *appName = smpIndex==0 ? options.APP0       : options.APP1;
            const char *imgName = smpIndex==0 ? options.IMAGE0     : options.IMAGE1;
            const char *imgSyms = smpIndex==0 ? options.IMAGE0SYM  : options.IMAGE1SYM;
            Uns32       imgAddr = smpIndex==0 ? options.IMAGE0ADDR : options.IMAGE1ADDR;
            Uns32       start   = 0;

            // Is this processor running Linux?
            // (Linux runs on both processors if no application for cpu1 specified)
            if (options.ZIMAGE && (smpIndex==0 || (!appName && !imgName))) {

                // Running Linux on this processor
                appName = "Linux";

                // Linux image file is loaded by smartLoader peripheral
                // so just load a symbol file here, if one was specified,
                if (options.LINUXSYM) loadSymbols(processor, options.LINUXSYM);

            } else if (appName) {

                // Load application file on the processor
                optApplicationP image = loadElf(processor, appName);

                // Get start address from ELF file if not using boot code
                start = options.BOOT ? getBootElfEntry() : (Uns32)opApplicationEntry(image);

            }

            // Load image file if indicated
            if (imgName) {

                Uns32 imageSize = loadImage(processor, imgName, imgAddr);

                if (imageSize) {
                    if (imgSyms) {
                        loadSymbols(processor, imgSyms);
                    }
                    if (!appName) {
                        appName = imgName;
                        start = options.BOOT ? getBootElfEntry() : imgAddr;
                    }
                }
            }

            // Set processor's starting address
            opProcessorPCSet(processor, start);

            opMessage(
                "I", MODULE_NAME"_LAF",
                "%s loaded on %s (start address set to 0x%08x)",
                appName ? appName : "nothing", opObjectHierName(processor), start
            );

        }
    }
}

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
    // Initialize options to default values
    setDefaults();

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    Bool ok = True;

    // Check args for errors
    if (!options.ZIMAGE && !options.APP0 && !options.BOOT && !options.IMAGE0) {
        opMessage("E", MODULE_NAME, "None of ZIMAGE, APP0, IMAGE0 or BOOT specified. Must specify at least one\n");
        ok = False;
    }

    if (!options.ZIMAGE && (options.INITRD || options.LINUXSYM || options.LINUXCMD)) {
        opMessage("E", MODULE_NAME, "Linux-only argument specified with out specifying ZIMAGE\n");
        ok = False;
    }

    if (options.ZIMAGE && options.APP0) {
        opMessage("E", MODULE_NAME, "Both IMAGE and APP0 specified. Must be only one or the other\n");
        ok = False;
    }

    if (options.ZIMAGE && options.APP1 && (options.LINUXMEM==0)) {
        opMessage("E", MODULE_NAME, "Running Linux with AMP application without LINUXMEM specified to limit Linux memory usage\n");
        ok = False;
    }

    if (!options.IMAGE0 && options.IMAGE0SYM) {
        opMessage("E", MODULE_NAME, "IMAGE0SYM specified without IMAGE0\n");
        ok = False;
    }

    if (!options.IMAGE1 && options.IMAGE1SYM) {
        opMessage("E", MODULE_NAME, "IMAGE1SYM specified without IMAGE1\n");
        ok = False;
    }

    if (options.IMAGE0 && options.IMAGE0ADDR==-1) {
        opMessage("E", MODULE_NAME, "IMAGE0SYM specified without IMAGE0ADDR\n");
        ok = False;
    }

    if (options.IMAGE1 && options.IMAGE1ADDR==-1) {
        opMessage("E", MODULE_NAME, "IMAGE1SYM specified without IMAGE1ADDR\n");
        ok = False;
    }

    if (ok) {
        setOverrides();
    }

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        OP_PARAMS(
             OP_PARAM_BOOL_SET(OP_FP_VERBOSE, 1)
            ,OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    if (options.BOOT) {
        // Load the boot file
        optBusP smbus_b = opObjectByName(mi, "smbus", OP_BUS_EN).Bus;
        if(!smbus_b) opMessage("E", MODULE_NAME, "Could not find Bus 'smbus' for loading Application '%s'", options.BOOT);
        opBusApplicationLoad(smbus_b, options.BOOT, OP_LDR_VERBOSE, 0);
    }

    // Setup application on each leaf processor
    optProcessorP cpu_c = opObjectByName(mi, "cpu", OP_PROCESSOR_EN).Processor;
    if(!cpu_c) opMessage("E", MODULE_NAME, "Could not find processor 'cpu'");
    opProcessorIterDescendants(cpu_c, setupApplication, NULL);

    opRootModuleSimulate(mi);
    opSessionTerminate();
    return opErrors() ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////////////
