/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., All Rights Reserved.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
 * OF IMPERAS SOFTWARE LTD. USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
 * EXCEPT AS MAY BE PROVIDED FOR IN A WRITTEN AGREEMENT WITH
 * IMPERAS SOFTWARE LTD.
 *
 */

/*
 * This is a working example of an object reader.
 * It reads Motorola S-Records (types 0, 2 & 8), plus improvised symbol records
 * of the form <type> <name> <address>
 * where
 * <type> is  T (text section) B,D or R (data sections).
 * <name> is  the symbol name (no spaces allowed)
 * <address> is in hexadecimal.
 *
 * Note that no form of relocation is allowed.
 * The last S8 record is used to specify the start address of the program.
 *
 * This reader tells the simulator that the program is for a
 * big-endian OR32 (Open RISC) architecture processor.
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
// This is the public interface to the object loader
//
#include "ord/ordObjAttrs.h"

//#define CPU_ARCHITECTURE   40
//#define CPU_ENDIAN         CPU_END_LITTLE

#define CPU_ARCHITECTURE   0x8472
#define CPU_ENDIAN         CPU_END_BIG

//
// Context information passed to all functions
//
typedef struct contextS {
    const char         *filename;
    const char         *targetName;
    FILE               *inputfs;
    Bool                verbose;
    Uns32               byteSwap;
    ordObjectInfoP      info;
    ordCallbacksP       callbacks;

    // for information
    Uns32               symbolCount;
    Uns32               recordCount;
    void               *userData;

} context, *contextP, **contextPP;

//
// convert single hex character to a number
//
static unsigned char fromHex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

//
// convert pairs of hex character to a number
//
static unsigned int getHexValue(const char *p, int bytes) {
    unsigned int r = 0;
    while(bytes--) {
        unsigned char t;
        t  = fromHex(*p++) << 4;
        t |= fromHex(*p++);
        r = (r << 8) + t;
    }
    return r;
}

//
// Symbol records start with one of these characters
//
static Bool isSymbol(char s) {
    return (strchr("BDRT", s) != 0);
}

//
// Convert from symbol type character to an enumeration
//
static ordSymbolType toSymbolType(char s) {
    switch (s) {
        case 'T': return ORD_SYMBOL_TYPE_FUNC;

        case 'B':
        case 'D':
        case 'R':
        default:
            return ORD_SYMBOL_TYPE_OBJECT;
    }
}

//
// The file must start with ASCII "S0" (Start record)
//
static Bool getHeader(contextP ctx) {
    FILE* inputfs = ctx->inputfs;
    char  buffer[1024];

    // read the start record
    if (fgets(buffer, sizeof(buffer),inputfs)) {
        if(buffer[0] == 'S' && buffer[1] == '0') {
            return 1;
        }
    }
    return 0;
}

//
// Byte swap the buffer
//
static void byteSwap(contextP ctx, Uns8 *data, Uns32 dataBytes) {
    Uns32 i;
    Uns32 b = ctx->byteSwap;
    if(dataBytes % b != 0) {
        ctx->callbacks->message("E", "SR_BSE", "Unable to byte-swap record length of %d", dataBytes);
    } else if (b == 2) {
        for(i = 0; i < dataBytes; i += b ) {
            SWAP_2_BYTE((Uns16)data[i]);
        }
    } else if (b == 4) {
        for(i = 0; i < dataBytes; i += b ) {
            SWAP_4_BYTE((Uns32)data[i]);
        }
    } else if (b == 8) {
        for(i = 0; i < dataBytes; i += b ) {
            SWAP_8_BYTE((Uns64)data[i]);
        }
    } else {
        ctx->callbacks->message("E", "SR_BSU", "Unable to byte-swap by %d", b);
    }
}

//
// Fetch ASCII hex from the text buffer and convert to raw binary
//
static void getDataBytes(contextP ctx, Uns8 *data, Uns32 dataBytes, const char *hex) {

    Uns32 i;
    for(i= 0; i < dataBytes; i++) {
        Uns8 t = getHexValue(&hex[i*2], 1);
        data[i] = t;
    }
    if(ctx->byteSwap) {
        byteSwap(ctx, data, dataBytes);
    }
}


//
// Load the data records and count the symbols
//
static Bool loadRecords(contextP ctx) {
    FILE* inputfs = ctx->inputfs;
    char buffer[1024];

    // Assume the file is line-based.
    // S-Records must be of type 0, 2 or 8
    while (fgets(buffer, sizeof(buffer),inputfs)) {
        if(buffer[0] == 'S') {
            switch(buffer[1]) {
                case '1': {
                    // A data record with 16-bit load address
                    ctx->recordCount++;
                    Uns32 length    = getHexValue(&buffer[2], 1);
                    Uns32 addr      = getHexValue(&buffer[4], 2);
                    Uns32 dataBytes = length - 2 - 1;
                    if (ctx->callbacks->listSection) {
                        // Tell simulator about this section record
                        ctx->callbacks->listSection("S1", addr, dataBytes, dataBytes, 1, ctx->userData);
                    }
                    if (ctx->callbacks->loadSection) {
                        Uns8  data[dataBytes];
                        getDataBytes(ctx, data, dataBytes, &buffer[8]);
                        // Tell simulator to load this section record
                        ctx->callbacks->loadSection("S1", addr, data, dataBytes, 1, ctx->userData);
                    }
                    break;
                }
                case '2': {
                    // A data record with 24bit load address
                    ctx->recordCount++;
                    Uns32 length    = getHexValue(&buffer[2], 1);
                    Uns32 addr      = getHexValue(&buffer[4], 3);
                    Uns32 dataBytes = length - 3 - 1;
                    if (ctx->callbacks->listSection) {
                        // Tell simulator about this section record
                        ctx->callbacks->listSection("S2", addr, dataBytes, dataBytes, 1, ctx->userData);
                    }
                    if (ctx->callbacks->loadSection) {
                        Uns8  data[dataBytes];
                        getDataBytes(ctx, data, dataBytes, &buffer[10]);
                        // Tell simulator to load this section record
                        ctx->callbacks->loadSection("S2", addr, data, dataBytes, 1, ctx->userData);
                    }
                    break;
                }
                case '8': {
                    // A stop record with 24bit start address
                    Uns32 addr   = getHexValue(&buffer[4], 3);

                    // Write back the start address
                    ctx->info->entry = addr;
                    break;
                }
                case '9': {
                    // A stop record with 16bit start address
                    Uns32 addr   = getHexValue(&buffer[4], 2);

                    // Write back the start address
                    ctx->info->entry = addr;
                    break;
                }
                default: {
                    ctx->callbacks->message("E", "SR_USR",
                        "Giving up on unknown S-record (type S%c).\n",
                        buffer[1]
                    );
                    return 0;
                    break;
                }
            }
        } else if (!isSymbol( buffer[0])) {
             ctx->callbacks->message("E", "SR_UR",
                "Giving up on unknown record (%s).\n",
                buffer
            );
            return 0;
        }
    }
    return 1;
}

//
// Count the symbols
//
static Bool countSymbols(contextP ctx){
    FILE* inputfs = ctx->inputfs;
    char buffer[512];

    // back to the beginning to read the symbols
    fseek(inputfs, 0, SEEK_SET);

    // Read each line again, skipping the uninteresting records.
    while (fgets(buffer, sizeof(buffer),inputfs)) {
        if(isSymbol(buffer[0])) {
            ctx->symbolCount++;
        }
    }
    return 1;
}


//
// Read the symbol records
//
static Bool loadSymbols(contextP ctx){
    FILE* inputfs = ctx->inputfs;

    // back to the beginning to read the symbols
    fseek(inputfs, 0, SEEK_SET);

    const char *file = NULL;
    char buffer[512];

    // Read each line again, skipping the uninteresting records.
    while (fgets(buffer, sizeof(buffer),inputfs)) {
        char what[32];
        char name[128];
        unsigned int addr;
        if(isSymbol(buffer[0]) && sscanf(buffer, "%s %s %x", what, name, &addr) == 3) {
            // Tell the simulator about this symbol
            ctx->callbacks->addSymbol(name, file, addr, 0, toSymbolType(what[0]), ORD_SYMBOL_BIND_GLOBAL, ctx->userData);
        }
    }
    return 1;
}

static Bool hexReadContext(contextP ctx)
{
    FILE* inputfs = ctx->inputfs;
    Bool ok = True;

    // If this is not an S-Record file, return 0
    if (!getHeader(ctx)) {
        fclose(inputfs);
        return 0;
    }

    // In this example the architecture information is hard coded.
    // It's usually extracted from the object file.
    ctx->info->cpuType  = CPU_ARCHITECTURE;
    ctx->info->endian   = CPU_ENDIAN;

    if (CPU_ENDIAN != CPU_END_LITTLE) {
        ctx->byteSwap = 4;
    }

    // Note that the loader will be called more than once, firstly without callbacks.
    // If there are no callbacks, the loader should verify the file and set the architecture
    // and endian.
    if (ctx->callbacks->listSection || ctx->callbacks->loadSection) {
        ok = loadRecords(ctx);
    }

    // If symbols are required, read them now.
    if (ok && ctx->callbacks->addSymbol) {

        ok = countSymbols(ctx);
        if (ctx->symbolCount) {
            ok = loadSymbols(ctx);
        }
    }
    fclose(inputfs);
    return ok;
}

//
// entry point to ELF object reader.
// Sets the context then calls the main routine.
//
static OBJREADER_FN(hexReader) {

    context ctx;
    Bool ok = False;
    if ((ctx.inputfs = fopen(filename, "rb"))) {
        ctx.filename       = filename;   // The file to be read
        ctx.targetName     = targetName; // String to be used in error messages
        ctx.callbacks      = callbacks;
        ctx.verbose        = attrs & ORD_LOAD_VERBOSE;
        ctx.info           = info;
        ctx.byteSwap       = 0;

        ctx.symbolCount    = 0;
        ctx.recordCount    = 0;
        ctx.userData       = userData;

        ok = hexReadContext(&ctx);

        if (ctx.verbose) {
            ctx.callbacks->message("I", "SR_I", "Loading program for processor %s\n", ctx.targetName);
            ctx.callbacks->message("I", "SR_R", "Records       : %d\n",   ctx.recordCount);
            ctx.callbacks->message("I", "SR_S", "Symbols       : %d\n",   ctx.symbolCount);
            ctx.callbacks->message("I", "SR_A", "Start address : 0x%x\n", ctx.info->entry);
        }
    }
    return ok;
}

//
// Attributes table. This is found (by name) by the dynamic loader, then used to
// find the entry points to the demonstration object reader.
//
ordObjReaderAttrs modelAttrs = {
        .interfaceVersion = ORD_OBJREADER_VERSION,
        .readerName       = "hexReader",
        .description      = "Demonstration Object Reader",
        .objReader        = hexReader,                     // object reader entry function
        .debugReader      = NULL
};
