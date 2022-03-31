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



////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                          Wed Nov  3 14:26:13 2010
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "op/op.h"

struct optionsS {
    const char*   program;
} options = {
    0
};

void createPlatform(optModuleP mi) {

////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus_b
////////////////////////////////////////////////////////////////////////////////

    optBusP bus_b = opBusNew(mi, "bus_b", 32, 0, 0);

////////////////////////////////////////////////////////////////////////////////
//                                Processor cpu
////////////////////////////////////////////////////////////////////////////////

    // Create processor instance using MORPHER_FILE, defined in Makefile
    optProcessorP cpu_c = opProcessorNew(
        mi,
        MORPHER_FILE,
        "cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus_b, "DATA")
            )
        ),
        OP_PARAMS(
            OP_PARAM_DOUBLE_SET("mips", 100.0)
        )
    );


////////////////////////////////////////////////////////////////////////////////
//                                 Memory mem
////////////////////////////////////////////////////////////////////////////////

    opMemoryNew(
        mi,
        "mem_m",
        OP_PRIV_RWX,
        0xffffffff,
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x00000000, .addrHi=0xffffffff)
            )
        ),
        0
    );

////////////////////////////////////////////////////////////////////////////////
//                                 Load Memory
////////////////////////////////////////////////////////////////////////////////

    int data, addr;
    char line[256];
    char *pline = line;
    int reset;

    FILE *fp = fopen(options.program, "r");
    if (fp == NULL) {
        opMessage("E", "LOAD_ERR", "cannot open '%s'", options.program);
    }
    while (fgets(pline, 256, fp)) {
        if(sscanf(pline, "%08x: %08x", &addr, &data) == 2) {
            // <address>: <data> line to load
            opProcessorWrite(cpu_c,                 // processor
                             addr,                  // memory address
                             &data,                 // data buffer of data to write
                             sizeof(int), 4,        // access size
                             True,                  // debug access
                             OP_HOSTENDIAN_TARGET); // endian

        } else if (sscanf(pline, "_start: %08x", &reset) == 1) {
            // do nothing
        } else {
            // error
            opMessage("E", "PARSE_ERR", "cannot parse '%s'", pline);
        }
    }
    opProcessorPCSet(cpu_c, reset);
}


////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew("BareMetalRisc32", OP_AC_ALL);
    opCmdUsageMessage(parser, "Basic Usage. BareMetalRisc32 platform executable --program <program file to load>");

    opCmdParserReplace(parser, "program"  , 0 , 0, 0, OP_FT_STRINGVAL     , &options.program, "", OP_AC_ALL, 0, 0);

    opCmdParseArgs(parser, argc, argv);

    // the platform constructor
    optModuleP mi = opRootModuleNew(0, 0,
            OP_PARAMS(
                    OP_PARAM_BOOL_SET(OP_FP_STOPONCONTROLC, 1),
                    OP_PARAM_BOOL_SET(OP_FP_VERBOSE, 1)
                     )
            );

    createPlatform(mi);

    // run till the end
    opRootModuleSimulate(mi);

    // finish and clean up
    opSessionTerminate();


    return (opErrors() ? 1 : 0);    // check for errors
}

////////////////////////////////////////////////////////////////////////////////
