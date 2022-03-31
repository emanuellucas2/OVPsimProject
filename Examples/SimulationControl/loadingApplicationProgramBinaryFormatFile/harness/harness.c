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
    const char * binaryfile;    // the file to load
    Uns32        offset;       // the offset address of memory to load
    Uns32        diag;          // diagnostics for loader
} options = {
    .binaryfile = NULL,
    .offset    = 0,
    .diag       = 0,
};

#define DIAG_LOW     (options.diag>0)
#define DIAG_MEDIUM  (options.diag>1)
#define DIAG_HIGH    (options.diag>2)

static int loadBinaryFile(optMemoryP memory, const char *fileName, Uns32 baseAddress);

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "binaryfile", 0, "string", "user", OP_FT_STRINGVAL, &options.binaryfile,
                           "the application binary format file to load.", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "offset", 0, "uns32", "user", OP_FT_UNS32VAL, &options.offset,
                           "the offset address for loading the application binary format file.", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "diagnostics", 0, "uns32", "user", OP_FT_UNS32VAL, &options.diag,
                           "enable diagnostics on the loader.", OP_AC_ALL, 0, 0);

    if (!opCmdParseArgs(parser, argc, argv)) {
        opMessage("E", HARNESS_NAME, "Command line parse incomplete");
    }

    optModuleP mi = opRootModuleNew(0, 0, 0);

    optModuleP ui = opModuleNew(mi, MODULE_DIR, MODULE_INSTANCE, 0, 0);

    // Advance to next phase for the API calls that follow
    opRootModulePreSimulate(mi);

    // Get first Memory (assumes a single memory in module)
    optMemoryP memory = opMemoryNext(ui, NULL);

    // Loading application binary file
    // Load binary file into Processor Memory
    if (loadBinaryFile(memory, options.binaryfile, options.offset)) {
        opMessage("E", HARNESS_NAME, "Load of Binary File '%s' Failed", options.binaryfile);
    }

    opRootModuleSimulate(mi);

    opSessionTerminate();
    return 0;
}


//
// Load a binary file into simulation memory
//
#define MAX_LINE_LENGTH 32

static int loadBinaryFile(optMemoryP memory, const char *fileName, Uns32 baseAddress) {

    FILE *fp;
    char inBuf[MAX_LINE_LENGTH + 1];
    int address = baseAddress;

    fp = fopen(fileName, "rb");

    if (!fp) {
        opMessage("E", HARNESS_NAME "_BIN_LDR",
                                    "Failed to open Memory Initialization File '%s'",
                                    fileName);
        return -1;
    }

    if(DIAG_LOW)
        opMessage("I", HARNESS_NAME "_BIN_LDR",
                                    "Loading binary file '%s'",
                                    fileName);

    Uns32 bytesRead = 0;
    while ( (bytesRead = fread( inBuf, 1, MAX_LINE_LENGTH, fp)) != 0 ) {
        //
        // Access the memory
        //
        if(!opMemoryWrite(
                memory,     // memory instance
                address,    // address offset into memory
                inBuf,      // bytes to write
                bytesRead,  // number of bytes to write
                True        // artifact access
        )) {
            opMessage("E", HARNESS_NAME "_BIN_LDR_FW",
                                        "Failed Data Write at 0x%08x",
                                        address);
            return -1;
        }

        if(DIAG_MEDIUM)
            opMessage("I", HARNESS_NAME "_BIN_LDR_LD",
                                        "Load address 0x%08x %u bytes",
                                        address, bytesRead);
        address += bytesRead;
    }

    if(DIAG_LOW)
        opMessage("I", HARNESS_NAME "_BIN_LDR",
                                    "Load Complete");

    if (fclose(fp)!=0) {
        opMessage("E", HARNESS_NAME "_BIN_LDR_CF",
                                    "Failed to close Memory Initialization File");
        return -1;
    }


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}
