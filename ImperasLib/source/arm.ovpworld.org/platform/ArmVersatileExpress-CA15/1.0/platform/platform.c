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
//                          Tue Aug 27 13:20:30 2019
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


#define MODULE_NAME "ArmVersatileExpress-CA15"

struct optionsS {
    const char*          zimage;
    Uns64                zimageaddr;
    const char*          initrd;
    Uns64                initrdaddr;
    const char*          linuxsym;
    const char*          linuxcmd;
    Int32                boardid;
    Uns64                linuxmem;
    const char*          boot;
    const char*          image0;
    Uns64                image0addr;
    const char*          image0sym;
    const char*          image1;
    Uns64                image1addr;
    const char*          image1sym;
    const char*          uart0port;
    const char*          uart1port;
    Bool                 nographics;
} options = {
    0
};


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;


// Physical address of base of RAM - use as start address
#define PHYS_BASE 0x80000000

//
// Return the entry address in the Boot file, if one is specified.
// Cache the result so we don't read the file over and over
//
static Addr getBootElfEntry() {

    static Addr bootElfEntry = -1ULL;

    if (bootElfEntry != -1ULL) {

        // Already set - no action

    } else if (options.boot) {

        ordObjectInfo info;
        if(!opApplicationHeaderRead(options.boot, &info)) {
            opMessage("F", MODULE_NAME"_URB", "Unable to load Boot code file '%s'", options.boot);
        }
        bootElfEntry = info.entry;
    }

    return bootElfEntry;

}

//
// Set non-zero default configuration values - may be overridden from command line
//
static void setDefaults() {

    // Allows detecting when not set, since 0 is a valid value
    options.image0addr = -1ULL;
    options.image1addr = -1ULL;
    options.zimageaddr = -1ULL;
    options.initrdaddr = -1ULL;
    options.boardid    = -1;

}


#define SMARTLOADER MODULE_NAME"/smartLoader/"
#define UART0       MODULE_NAME"/uart0/"
#define UART1       MODULE_NAME"/uart1/"
#define CLCD        MODULE_NAME"/clcd/"
//
// Set overrides for attributes affected by command line options
//
static void setOverrides() {

    if (options.zimage) {

        opParamStringOverride(NULL, SMARTLOADER"kernel", options.zimage);

        if (options.linuxcmd) {
            opParamStringOverride(NULL, SMARTLOADER"command", options.linuxcmd);
        }

        if (options.boardid != -1) {
            opParamUns32Override(NULL, SMARTLOADER"boardid", options.boardid);
        }

        if (options.linuxmem) {
            opParamUns64Override(NULL, SMARTLOADER"memsize", options.linuxmem);
        }

        if (options.zimageaddr != -1ULL) {
            opParamUns64Override(NULL, SMARTLOADER"kerneladdr", options.zimageaddr);
        }

        if (options.boot) {
            opParamUns32Override(NULL, SMARTLOADER"bootaddr", getBootElfEntry() );
        }

        if (options.initrd) {
            opParamStringOverride(NULL, SMARTLOADER"initrd",     options.initrd);
        }

        if (options.initrdaddr != -1ULL) {
            opParamUns64Override(NULL, SMARTLOADER"initrdaddr", options.initrdaddr);
        }

    } else {

        // Disable smart loader if LINUX is not used
        opParamStringOverride(NULL, SMARTLOADER"disable", "1");

    }

    if (options.uart0port) {
        Uns32 portNum;
        if (strcmp(options.uart0port, "auto") == 0) {
            opParamStringOverride(NULL, UART0"console", "1");
        } else if (sscanf(options.uart0port, "%i", &portNum) == 1) {
            opParamStringOverride(NULL, UART0"portnum", options.uart0port);
        } else {
            opMessage(
                "W", MODULE_NAME"_IO",
                "Invalid argument for uart0port: '%s'. Must be 'auto' or a number.",
                options.uart0port
            );
        }
    }

    if (options.uart1port) {
        Uns32 portNum;
        if (strcmp(options.uart1port, "auto") == 0) {
            opParamStringOverride(NULL, UART1"console", "1");
        } else if (sscanf(options.uart1port, "%i", &portNum) == 1) {
            opParamStringOverride(NULL, UART1"portnum", options.uart1port);
        } else {
            opMessage(
                "W", MODULE_NAME"_IO",
                "Invalid argument for uart1port: '%s'. Must be 'auto' or a number.",
                options.uart1port
            );
        }
    }

    if (options.nographics) {
        opParamBoolOverride(NULL, CLCD"noGraphics", options.nographics);
    }

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

        const char *appName = NULL;
        const char *imgName = smpIndex==0 ? options.image0     : options.image1;
        const char *imgSyms = smpIndex==0 ? options.image0sym  : options.image1sym;
        Uns32       imgAddr = smpIndex==0 ? options.image0addr : options.image1addr;
        Addr        start   = 0;

        // Is this processor running Linux?
        // (Linux runs on both processors if no application for cpu1 specified)
        if (options.zimage && (smpIndex==0 || !imgName)) {

            // Running Linux on this processor
            appName = "Linux";

            // Linux image file is loaded by smartLoader peripheral
            // so just load a symbol file here, if one was specified,
            if (options.linuxsym) loadSymbols(processor, options.linuxsym);

            // Set start address to physical base, where smartLoader writes the boot code
            start = PHYS_BASE;

        }

        // Load image file if indicated
        if (imgName) {

            Uns32 imageSize = loadImage(processor, imgName, imgAddr);

            if (imageSize) {
                if (imgSyms) {
                    loadSymbols(processor, imgSyms);
                }
            }
            if (!appName) appName = imgName;
            start = options.boot ? getBootElfEntry() : imgAddr;
        }

        // Set processor's starting address
        opProcessorPCSet(processor, start);

        opMessage(
            "I", MODULE_NAME"_LAF",
            "%s loaded on %s (start address set to 0x"FMT_A08x")",
            appName ? appName : "nothing", opObjectHierName(processor), start
        );

    }
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

int main(int argc, const char *argv[]) {

    setDefaults();

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    //
    // Check for valid command line arguments specified
    //
    Bool ok = True;

    // Check args for errors
    if (!options.zimage && !options.boot && !options.image0) {
        opMessage("W", MODULE_NAME, "None of zimage, image0 or boot specified. Must specify executable some other way");
    }

    if (!options.zimage && (options.initrd || options.linuxsym || options.linuxcmd || options.linuxmem)) {
        opMessage("E", MODULE_NAME, "Linux-only argument specified with out specifying zimage");
        ok = False;
    }

    if (!options.image0 && options.image0sym) {
        opMessage("E", MODULE_NAME, "image0sym specified without image0");
        ok = False;
    }

    if (!options.image1 && options.image1sym) {
        opMessage("E", MODULE_NAME, "image1sym specified without image1");
        ok = False;
    }

    if (options.image0 && options.image0addr==-1ULL) {
        opMessage("E", MODULE_NAME, "image0sym specified without image0addr");
        ok = False;
    }

    if (options.image1 && options.image1addr==-1ULL) {
        opMessage("E", MODULE_NAME, "image1sym specified without image1addr");
        ok = False;
    }

    if (ok) {
        setOverrides();
    }

    optModuleP mi = opRootModuleNew(
        &modelAttrs,
        MODULE_NAME,
        OP_PARAMS(
             OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1)
        )
    );

    if (options.boot) {
        // Load the boot file
        optBusP pBus_b = opObjectByName(mi, "pBus", OP_BUS_EN).Bus;
        if(!pBus_b) opMessage("E", MODULE_NAME, "Could not find Bus 'pBus' for loading Application '%s'", options.boot);
        opBusApplicationLoad(pBus_b, options.boot, OP_LDR_VERBOSE, 0);
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
