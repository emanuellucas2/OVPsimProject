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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op/op.h"

#define PLATFORM "BareMetalM14KSingle"

// Function Prototypes early declaration
static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);
static const char *selectVendor(void);

// vendor options for processor model
const char *vendor[] = {"mips.ovpworld.org", "mips.com", 0};
#define NUMBER_VENDORS 2

// Set of valid model variants
const char *modelVariantList[] = { "M14K", "M14KcFMM", "M14KcTLB", "microAptivC", "microAptivP",   0};

//
// Main routine
//
int main(int argc, const char **argv) {

    // initialize CpuManager
    opSessionInit(OP_VERSION);

    // Check arguments and ensure application to load specified
    if(!cmdParser(argc, argv)) {
        opMessage("E", PLATFORM, "Command Line parser error");
        opSessionExit(1);
        return 1;
    }

    optParamP paramsSim = NULL;
    paramsSim = opParamBoolSet(paramsSim, OP_FP_VERBOSE,        True);
    paramsSim = opParamBoolSet(paramsSim, OP_FP_STOPONCONTROLC, True);

    optModuleAttr attrs = { 0 };
    attrs.visibility    = OP_VISIBLE;
    attrs.releaseStatus = OP_OVP;
    attrs.purpose       = OP_PP_BAREMETAL;
    optModuleP  mr = opRootModuleNew (&attrs, PLATFORM, paramsSim);

    addPlatformDocumentation();

    // Select components from library
    const char *vendorP = selectVendor();
    const char *mipsModel = opVLNVString(NULL, vendorP, "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);

    // Setup the configuration attributes for the MIPS model
    optParamP paramsCpu = NULL;
    paramsCpu = opParamEndianSet(paramsCpu, OP_FP_ENDIAN, OP_ENDIAN_BIG);
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_DEFAULTSEMIHOST, True);
    paramsCpu = opParamEnumSet(paramsCpu, "variant", "M14K");

    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    // The complete configuration of the Processor Model uses the configuration parameters
    // defined for the processor.
    // The attributes available to further configure a processor model are detailed
    // in the library listing in the README.txt or XML file.
    // Further attributes should be added to the userAttrs list.

    opProcessorNew(
        mr,
        mipsModel,
        "M14K_1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus, "INSTRUCTION"),
                OP_BUS_CONNECT(bus, "DATA")
            )
        ),
        paramsCpu
    );

    // create memory
    opMemoryNew(
            mr,
            "local",
            OP_PRIV_RWX,
            0xffffffffULL,
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(bus, "sp1", .slave=1, .addrLo=0x000000000ULL, .addrHi=0xffffffffULL)
                )
            ),
            0
    );

    // Ignore specific Info messages
    opMessageDisable ("MIPS32_IAS_COP0_READ");
    opMessageDisable ("MIPS32_IAS_COP0_WRITE");

    // simulate the platform
    optProcessorP final = opRootModuleSimulate(mr);

    // was simulation interrupted or did it complete
    if(final && (opProcessorStopReason(final)==OP_SR_INTERRUPT)) {
        opPrintf("*** simulation interrupted\n");
    }

    // finish and clean up
    opSessionTerminate();

    opSessionExit(0);
    return opErrors() ? 1 : 0;
}




struct optionsS {
    const char    *vendor;
} options;

static Bool cmdParser(int argc, const char *argv[]) {
    optCmdParserP parser = opCmdParserNew(PLATFORM, OP_AC_ALL);
    char message[1024];
    strcat(message, "Basic Usage\n  %E --program <elf file>\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbegui : start and connect remote debugger in console or eGui mode\n"
                     "Configuration Options\n"
                     "    --vendor <vendor>     : set the vendor for model loading e.g mips.ovpworld.org, mips.com \n"
                     "    --variant <variant>   : set the processor variant configuration (");
    int i;
    for(i=0;modelVariantList[i];i++) {
        char tmp[32];
        sprintf(tmp, " %s", modelVariantList[i]);
        strcat(message, tmp);
    }
    strcat(message, " )\n");

    opCmdUsageMessage(parser, message);
    opCmdParserAdd(parser, "vendor"  , 0 , "string", "user configuration", OP_FT_STRINGVAL, &options.vendor, "set the vendor for model loading e.g mips.ovpworld.org, mips.com ", OP_AC_ALL, 0, 0);
    Bool ok = opCmdParseArgs(parser, (Uns32)argc, (const char **)argv);

    if (!opCmdArgUsed (parser,"program")) {
        opMessage("E", PLATFORM, "Argument '--program' must be specified");
        ok = False;
    }
    return ok;
}

//
// Select vendor to use for models
//
static const char *selectVendor() {
    Uns32 i, index = 0;

    if(options.vendor) {
        return options.vendor;
    } else {
        // Select default model vendor to be used to load model
        char *runtime = getenv("IMPERAS_RUNTIME");
        if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
            ;        // leave default index
        } else {
            index++; // start from next vendor
        }
        for(i=0;i<NUMBER_VENDORS;i++){
            const char *mipsModel    = opVLNVString(NULL, vendor[index], "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_QUIET);
            const char *mipsSemihost = opVLNVString(NULL, vendor[index], "semihosting", "mips32Newlib", "1.0", OP_EXTENSION, OP_VLNV_QUIET);
            if(mipsModel && mipsSemihost) {
                return vendor[index];
            }
            // Select next in list, if zero back to first
            if (!vendor[++index]) index = 0;
        }

        opMessage("F", "MODEL", "No Model Available");
        // Will never reach here
        return NULL;
    }
}

static void addPlatformDocumentation() {

    optDocNodeP Root1_node = opDocSectionAdd(0, "Root");
    {
        optDocNodeP doc2_node = opDocSectionAdd(Root1_node, "Licensing");
        opDocTextAdd(doc2_node, "Open Source Apache 2.0");
        optDocNodeP doc_12_node = opDocSectionAdd(Root1_node, "Description");
        opDocTextAdd(doc_12_node, "Bare Metal Platform for a MIPS M14K Processor."
                "The bare metal platform instantiates a single M14K processor instance, using little endian data ordering."
                ""
                "The platform can be passed any application compiled to a MIPS elf format as the argument"
                "It will also allow a port number to be specified to allow the connection of a remote GDB debugger."
                ""
                "platform.OS.exe --program application.CROSS.elf [--port <gdb port>]"
                ""
                "Where OS is Linux or Windows");
        optDocNodeP doc_22_node = opDocSectionAdd(Root1_node, "Limitations");
        opDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS M14K binary files compiled with CodeSourcery CrossCompiler toolchain.");
        optDocNodeP doc_32_node = opDocSectionAdd(Root1_node, "Reference");
        opDocTextAdd(doc_32_node, "None");
    }
}
