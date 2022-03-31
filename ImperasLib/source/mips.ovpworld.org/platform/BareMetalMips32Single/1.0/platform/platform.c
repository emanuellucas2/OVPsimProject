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
#include <string.h>

#include "op/op.h"

#define PLATFORM "BareMetalMips32Single"

// Function Prototypes declaration
static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);

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

    const char *mipsModel    = opVLNVString(NULL, "mips.ovpworld.org", "processor", "mips32_r1r5", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);

    // Setup the configuration attributes for the MIPS model
    optParamP paramsCpu = NULL;
    paramsCpu = opParamEndianSet(paramsCpu, OP_FP_ENDIAN, OP_ENDIAN_BIG);
    paramsCpu = opParamEnumSet(paramsCpu, "variant", "4KEm");
    paramsCpu = opParamBoolSet(paramsCpu, OP_FP_DEFAULTSEMIHOST, True);

    optBusP bus = opBusNew(mr, "bus", 32, 0, 0);

    opProcessorNew(
        mr,
        mipsModel,
        "mips32",
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

    addPlatformDocumentation();

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

static Bool cmdParser(int argc, const char *argv[]) {
    optCmdParserP parser = opCmdParserNew(PLATFORM, OP_AC_ALL);
    const char *message =
                     "Basic Usage\n  %E --program <elf file>\n"
                     "Debug Options\n"
                     "    --port <port number>  : open debug port\n"
                     "    --gbdconsole/--gdbegui : start and connect remote debugger in console or eGui mode\n"
                     "Configuration Options\n"
                     "    --variant <variant>   : set the processor variant configuration\n";
    opCmdUsageMessage(parser, message);
    Bool ok = opCmdParseArgs(parser, (Uns32)argc, (const char **)argv);

    if (!opCmdArgUsed (parser,"program")) {
        opMessage("E", PLATFORM, "Argument '--program' must be specified");
        ok = False;
    }
    return ok;
}

static void addPlatformDocumentation() {

    optDocNodeP Root1_node = opDocSectionAdd(0, "Root");
    {
        optDocNodeP doc2_node = opDocSectionAdd(Root1_node, "Licensing");
        opDocTextAdd(doc2_node, "Open Source Apache 2.0");
        optDocNodeP doc_12_node = opDocSectionAdd(Root1_node, "Description");
        opDocTextAdd(doc_12_node, "Bare Metal Platform for an MIPS32 Processor (variant 4Km)."
                                    "The bare metal platform instantiates a single MIPS32 processor instance. "
                                    "The processor operate using big endian data ordering."
                                    "It creates contiguous memory from 0x00000000 to 0xFFFFFFFF."
                                    "The platform can be passed any application compiled to an MIPS32 elf format as the first argument."
                                    "./platform.<OS>.exe --program application.elf");
        optDocNodeP doc_22_node = opDocSectionAdd(Root1_node, "Limitations");
        opDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS MIPS32 binary files compiled with MIPS SDE CrossCompiler toolchain");
        optDocNodeP doc_32_node = opDocSectionAdd(Root1_node, "Reference");
        opDocTextAdd(doc_32_node, "None");
    }
}
