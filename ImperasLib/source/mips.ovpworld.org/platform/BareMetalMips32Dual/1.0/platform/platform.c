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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "op/op.h"

#define PLATFORM "BareMetalMips32Dual"


////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]);
static void addPlatformDocumentation(void);

int main(int argc, const char *argv[])
{

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
    optParamP paramsCpu0 = NULL;
    paramsCpu0 = opParamEndianSet(paramsCpu0, OP_FP_ENDIAN, OP_ENDIAN_BIG);
    paramsCpu0 = opParamEnumSet(paramsCpu0, "variant", "4Km");
    paramsCpu0 = opParamBoolSet(paramsCpu0, OP_FP_DEFAULTSEMIHOST, True);
    paramsCpu0 = opParamUns32Set(paramsCpu0, OP_FP_CPUID, 0);

    optBusP bus0 = opBusNew(mr, "bus0", 32, 0, 0);

    opProcessorNew(
        mr,
        mipsModel,
        "cpu0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0, "DATA")
            )
        ),
        paramsCpu0
    );

    // create memory
    opMemoryNew(
            mr,
            "local0",
            OP_PRIV_RWX,
            0xffffffffULL,
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(bus0, "sp1", .slave=1, .addrLo=0x000000000ULL, .addrHi=0xffffffffULL)
                )
            ),
            0
    );

    // Setup the configuration attributes for the MIPS model
    optParamP paramsCpu1 = NULL;
    paramsCpu1 = opParamEndianSet(paramsCpu1, OP_FP_ENDIAN, OP_ENDIAN_BIG);
    paramsCpu1 = opParamEnumSet(paramsCpu1, "variant", "4Km");
    paramsCpu1 = opParamBoolSet(paramsCpu1, OP_FP_DEFAULTSEMIHOST, True);
    paramsCpu1 = opParamUns32Set(paramsCpu1, OP_FP_CPUID, 0);

    optBusP bus1 = opBusNew(mr, "bus1", 32, 0, 0);

    opProcessorNew(
        mr,
        mipsModel,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1, "DATA")
            )
        ),
        paramsCpu1
    );

    // create memory
    opMemoryNew(
            mr,
            "local1",
            OP_PRIV_RWX,
            0xffffffffULL,
            OP_CONNECTIONS(
                OP_BUS_CONNECTIONS(
                    OP_BUS_CONNECT(bus1, "sp1", .slave=1, .addrLo=0x000000000ULL, .addrHi=0xffffffffULL)
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

////////////////////////////////////////////////////////////////////////////////

static Bool cmdParser(int argc, const char *argv[]) {
    optCmdParserP parser = opCmdParserNew(PLATFORM, OP_AC_ALL);
    const char *message =
                     "Basic Usage\n"
                     "  %E --program <elf file>             : load same application onto all processors\n"
                     "  %E --program <cpu name>=<elf file>  : load specified processor with application\n"
                     "Debug Options\n"
                     "    --port <port number>        : open debug port\n"
                     "    --gbdconsole/--gdbegui      : start and connect remote debugger in console or eGui mode\n"
                     "    --debugprocessor <instance> : select the processor to attach GDB (OVPsim allows single GDB connection, Imperas allows debug of all)";
    opCmdUsageMessage(parser, message);
    Bool ok = opCmdParseArgs(parser, (Uns32)argc, (const char **)argv);

    if (!opCmdArgUsed (parser,"program")) {
        opMessage("E", PLATFORM, "Argument '--program' must be specified");
        ok = False;
    }
    return ok;
}

////////////////////////////////////////////////////////////////////////////////

static void addPlatformDocumentation() {

    optDocNodeP Root1_node = opDocSectionAdd(0, "Root");
    {
        optDocNodeP doc2_node = opDocSectionAdd(Root1_node, "Licensing");
        opDocTextAdd(doc2_node, "Open Source Apache 2.0");
        optDocNodeP doc_12_node = opDocSectionAdd(Root1_node, "Description");
        opDocTextAdd(doc_12_node, "Bare Metal Platform for a MIPS32 Processor (default 4Km)."
    "The bare metal platform instantiates two MIPS32 processor instances. "
    "The processor operates using big endian data ordering."
    "It creates contiguous memory from 0x00000000 to 0xFFFFFFFF."
    "The platform can be passed any application compiled to a MIPS elf format as the first argument. The"
    "same application executes on each processor. There is no sharing of data."
    "It may also be passed a new variant to be used (default 4Km)"
    "./platform.OS.exe --program application.CROSS.elf [--variant <model variant>]");
        optDocNodeP doc_22_node = opDocSectionAdd(Root1_node, "Limitations");
        opDocTextAdd(doc_22_node, "BareMetal platform for execution of MIPS MIPS32 binary files compiled with CodeSourcery CrossCompiler toolchain.");
        optDocNodeP doc_32_node = opDocSectionAdd(Root1_node, "Reference");
        opDocTextAdd(doc_32_node, "None");
    }
}
