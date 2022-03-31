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
    const char * intelhexfile;  // the file to load
    Uns32        offset;       // the offset address of memory to load
    Uns32        diag;          // diagnostics for loader
} options = {
    .intelhexfile = NULL,
    .offset      = 0,
    .diag         = 0,
};

#define DIAG_LOW     (options.diag>0)
#define DIAG_MEDIUM  (options.diag>1)
#define DIAG_HIGH    (options.diag>2)

static int loadIntelHexFile(optMemoryP memory, const char *fileName, Uns32 baseAddress);

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "intelhexfile", 0, "string", "user", OP_FT_STRINGVAL, &options.intelhexfile,
                           "the application Intel Hex format file to load.", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "offset", 0, "uns32", "user", OP_FT_UNS32VAL, &options.offset,
                           "the offset address in memory for loading the application Hex file.", OP_AC_ALL, 0, 0);
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
    if (loadIntelHexFile(memory, options.intelhexfile, options.offset)) {
        opMessage("E", HARNESS_NAME, "Load of Intel Hex File '%s' Failed", options.intelhexfile);
    }

    opRootModuleSimulate(mi);

    opSessionTerminate();
    return 0;
}


//
// Load a hex file into simulation memory
//
#define MAX_LINE_LENGTH 64

static int loadIntelHexFile(optMemoryP memory, const char *fileName, Uns32 baseAddress) {

    FILE *fp;
    char inBuf[MAX_LINE_LENGTH + 1];
    int address = baseAddress;

    fp = fopen(fileName, "r");

    if (!fp) {
        opMessage("E", HARNESS_NAME "_HEX_LDR",
                                    "Failed to open Memory Initialization File '%s'",
                                    fileName);
        return -1;
    }

    if(DIAG_LOW)
        opMessage("I", HARNESS_NAME "_HEX_LDR",
                                    "Loading Hex file '%s'",
                                    fileName);

    while ( fgets( inBuf,MAX_LINE_LENGTH, fp) != 0 ) {

        if(options.diag>1)
            opMessage("I", HARNESS_NAME "_HEX_LDR_LINE","%s", inBuf);

        if ( inBuf[0] == '#') {
            // ignore header
            if(options.diag>1)
                opMessage("I", HARNESS_NAME "_HEX_LDR_LINE","ignored");
        } else if ( inBuf[0] == ':') {
            // data line to load
            Uns32 bytes = 0, offset = 0, type = 0, i;
            // Get header into local buffer
            char inBufHeader[16];
            for (i=0;i<8;i++) {
                inBufHeader[i] = inBuf[i+1];
            }
            inBufHeader[i]=0;
            if ( sscanf(inBufHeader, "%02x%04x%02x", &bytes, &offset, &type) != 3 ) {
                // error
                opMessage("E", HARNESS_NAME "_HEX_LDR_FEH","Failure during load");
                return -1;
            }
            if(options.diag>1)
                opMessage("I", HARNESS_NAME "_HEX_LDR_HDR","bytes %d offset 0x%04x type %d", bytes, offset, type);
            if (type == 0) {
                Uns8 b = 0;
                while (b < bytes) {
                    Uns32 data;
                    char inBufData[4];
                    for (i=0;i<2;i++) {
                        inBufData[i] = inBuf[9+(b*2)+i];
                    }
                    inBufData[i]=0;

                    if ( sscanf(inBufData, "%02x", &data) != 1 ) {
                        // error
                        opMessage("E", HARNESS_NAME "_HEX_LDR_FED","Failure during load");
                        return -1;
                    }
                    //
                    // Access the memory
                    //
                    if(DIAG_HIGH)
                        opMessage("I", HARNESS_NAME "_HEX_LDR_LB","Load 0x%04x:0x%02x", address+offset+b, data);
                    if(!opMemoryWrite(
                        memory,           // memory
                        address+offset+b, // memory address offset
                        &data,            // data buffer of data to write
                        1,                // number of bytes
                        True
                    )) {
                        opMessage("E", HARNESS_NAME "_HEX_LDR_FW",
                                                    "Failed Data Write at 0x%08x",
                                                    (Uns32)address);
                        return -1;
                    }
                    b++;
                };
            } else {
                if(DIAG_MEDIUM)
                    opMessage("I", HARNESS_NAME "_HEX_LDR_HDR","type %d - ignored", type);
            }
        }
    }

    if(DIAG_LOW)
        opMessage("I", HARNESS_NAME "_HEX_LDR",
                                    "Load Complete");

    if (fclose(fp)!=0) {
        opMessage("E", HARNESS_NAME "_HEX_LDR_CF",
                                    "Failed to close Memory Initialization File");
        return -1;
    }


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}
