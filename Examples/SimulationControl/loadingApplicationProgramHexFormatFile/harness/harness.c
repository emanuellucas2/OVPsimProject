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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define HARNESS_NAME    "harness"
#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"

struct optionsS {
    const char * hexfile;
} options = {
    .hexfile = NULL,
};

static int loadHexFile(optProcessorP processor, const char *fileName);

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "hexfile", 0, "string", "user", OP_FT_STRINGVAL, &options.hexfile,
                           "the application hex format file to load.", OP_AC_ALL, 0, 0);

    if (!opCmdParseArgs(parser, argc, argv)) {
        opMessage("E", HARNESS_NAME, "Command line parse incomplete");
    }

    optModuleP mi = opRootModuleNew(0, 0, 0);

    optModuleP ui = opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    // Advance to next phase for the API calls that follow
    opRootModulePreSimulate(mi);

    // Get first Processor (assumes a single processor module)
    optProcessorP   proc    = opProcessorNext(ui, NULL);

    // Loading application hex file
    // Load Hex file into Processor Memory
    if (loadHexFile(proc, options.hexfile)) {
        opMessage("E", HARNESS_NAME, "Load of Hex File '%s' Failed", options.hexfile);
    }

    opRootModuleSimulate(mi);

    opSessionTerminate();
    return 0;
}


//
// Load a hex file into simulation memory
//
#define MAX_LINE_LENGTH 64

static int loadHexFile(optProcessorP processor, const char *fileName) {

    FILE *fp;
    char inBuf[MAX_LINE_LENGTH + 1];
    int address, endAddress, data, dataCheck;

    fp = fopen(fileName, "r");

    if (!fp) {
        opMessage("E", HARNESS_NAME "_HEX_LDR",
                                    "Failed to open Memory Initialization File '%s'",
                                    fileName);
        return -1;
    }

    opMessage("I", HARNESS_NAME "_HEX_LDR",
                                "Loading Hex file '%s'",
                                fileName);

    while ( fgets( inBuf,MAX_LINE_LENGTH, fp) != 0 ) {

        if ( inBuf[0] == '#') {
            // ignore header
        } else if ( inBuf[0] == ':') {
            // symbol
            Uns32 symbolAddress;
            char  symbol[16];
            if ( sscanf(inBuf, ":%08x %s", &symbolAddress, symbol) == 2 ) {
                opMessage("I", HARNESS_NAME "_HEX_LDR_SYM", "Found symbol '%s' at address 0x%08x",
                                                    symbol,
                                                    symbolAddress);

                const char *runTime=getenv("IMPERAS_RUNTIME");
                if(runTime && strcmp(runTime, "CpuManager") == 0) {
                    opProcessorApplicationSymbolAdd(processor,
                                                    symbol,
                                                    symbolAddress,
                                                    4,
                                                    ORD_SYMBOL_TYPE_FUNC,
                                                    ORD_SYMBOL_BIND_GLOBAL);
                } else {
                    opMessage("W", HARNESS_NAME "_HEX_LDR_SF",
                                                "Symbols cannot be loaded with this product runtime (%s), "
                                                "supported in Imperas Professional simulator",
                                                runTime);
                }
                if(strcmp(symbol, "_start") == 0) {
                    opMessage("I", HARNESS_NAME "_HEX_LDR_START",
                                                "Set start address to 0x%08x",
                                                symbolAddress);
                    opProcessorPCSet(processor, symbolAddress);
                }

            } else {
                opMessage("W", HARNESS_NAME "_HEX_LDR_SND",
                                            "Found symbol line '%s' but not decoded",
                                            inBuf);
            }

        } else {
            if ( sscanf(inBuf, "%08x-%08x %08x ;", &address, &endAddress, &data) != 3 ) {
                sscanf(inBuf, "%08x %08x ;", &address, &data);
                endAddress = address;
            }

            do {
                //
                // Access the memory through the processor memory space
                //
                if(!opProcessorWrite(
                    processor,      // processor
                    address,        // memory address
                    &data,          // data buffer of data to write
                    4,              // number of bytes in one object
                    1,              // number of objects
                    True,           // debug access (not a true processor access)
                    OP_HOSTENDIAN_TARGET
                )) {
                    opMessage("E", HARNESS_NAME "_HEX_LDR_FW",
                                                "Failed Data Write at 0x%08x",
                                                (Uns32)address);
                    return -1;
                }

                opProcessorRead(
                    processor,
                    address,
                    &dataCheck,
                    4,
                    1,
                    True,
                    OP_HOSTENDIAN_TARGET
                );

                if(data != dataCheck) {
                    opMessage("E", HARNESS_NAME "_HEX_LDR_FRB",
                                                "Failed Data Read Back at 0x%08x (0x%08x 0x%08x)",
                                                (Uns32)address, data, dataCheck);
                    return -1;
                }

                opMessage("I", HARNESS_NAME "_HEX_LDR_LD",
                                            "Load address 0x%08x : 0x%08x",
                                            address, data);

            } while ( address++ < endAddress);
        }
    }

    opMessage("I", HARNESS_NAME "_HEX_LDR",
                                "Load Complete");

    if (fclose(fp)!=0) {
        opMessage("E", HARNESS_NAME "_HEX_LDR_CF",
                                    "Failed to close Memory Initialization File");
        return -1;
    }


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}
