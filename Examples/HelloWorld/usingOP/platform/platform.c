/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <string.h>
#include <stdlib.h>

#include "op/op.h"


#define MODULE_NAME "test"

struct optionsS {
    const char*          processortype;
    const char*          alternatevendor;
} options = {
    .processortype = "riscv"
};

// instantiate module components
static OP_CONSTRUCT_FN(instantiateComponents) {


    // Processor model and semihosting, selected from VLNV library below
    const char *model       = NULL;
    const char *semihosting = NULL;

    if (strcmp(options.processortype, "riscv") == 0) {
        model       = opVLNVString(0, options.alternatevendor ? options.alternatevendor :
                                             "riscv.ovpworld.org", "processor",   "riscv",         "1.0", OP_EXTENSION, OP_VLNV_QUIET);
        semihosting = opVLNVString(0,        "riscv.ovpworld.org", "semihosting", "pk", "1.0", OP_EXTENSION, OP_VLNV_QUIET);

    } else if (strcmp(options.processortype, "mips32") == 0) {
        model       = opVLNVString(0, options.alternatevendor ? options.alternatevendor :
                                             "mips.ovpworld.org", "processor",   "mips32_r1r5",  "1.0", OP_EXTENSION, OP_VLNV_QUIET);
        semihosting = opVLNVString(0,        "mips.ovpworld.org", "semihosting", "mips32Newlib", "1.0", OP_EXTENSION, OP_VLNV_QUIET);

    } else if (strcmp(options.processortype, "arm") == 0) {
        model       = opVLNVString(0,options.alternatevendor ? options.alternatevendor :
                                             "arm.ovpworld.org", "processor",   "arm",       "1.0", OP_EXTENSION, OP_VLNV_QUIET);
        semihosting = opVLNVString(0,        "arm.ovpworld.org", "semihosting", "armNewlib", "1.0", OP_EXTENSION, OP_VLNV_QUIET);

    } else {
        opMessage("W", "PROC", "Processor type '%s' not recognized. "
                                "Please try 'riscv', 'mips32' or 'arm'", options.processortype);
    }

    if (!model || !semihosting) {
        opMessage("F", "LIBRARY", "Failed to find model or semihost library components"
                                  " for processor type '%s ' (or vendor '%s')",
                                  options.processortype, options.alternatevendor);
    }


    // Bus bus
    optBusP bus_b = opBusNew(mi, "bus", 32, 0, 0);

    // Processor CPU1
    optProcessorP CPU1_c = opProcessorNew(
        mi,
        model,
        "CPU1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus_b, "DATA")
            )
        ),
        0
    );

    opProcessorExtensionNew(CPU1_c, semihosting, "semihost", 0 );

    // Memory
    opMemoryNew(
        mi,
        "memory",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

}

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);
}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_PLATFORM,
    .name                 = MODULE_NAME,
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "ovpworld.org",
        .library = "platform",
        .name    = "platform",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "processortype",   0 , 0, "user platform config", OP_FT_STRINGVAL, &options.processortype,   "Specify the processor type to use. riscv, mips32 or arm", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "alternatevendor", 0 , 0, "user platform config", OP_FT_STRINGVAL, &options.alternatevendor, "Specify an alternative vendor for processor model",      OP_AC_ALL, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    cmdParserAddUserArgs(parser);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mi = opRootModuleNew(&modelAttrs,
                                    MODULE_NAME,
                                    OP_PARAMS (
                                            OP_PARAM_BOOL_SET (OP_FP_STOPONCONTROLC, 1),
                                            OP_PARAM_BOOL_SET (OP_FP_VERBOSE, 1)
                                    )
                    );
    opRootModuleSimulate(mi);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // check for errors
}
