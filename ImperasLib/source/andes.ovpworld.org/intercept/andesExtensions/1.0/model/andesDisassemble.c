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

// standard includes
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// VMI header files
#include "vmi/vmiMessage.h"

// model header files
#include "andesACE.h"
#include "andesDecode.h"
#include "andesDecodeTypes.h"
#include "andesDisassembleFormats.h"
#include "andesFunctions.h"
#include "andesUtils.h"


//
// Prefix for messages from this module
//
#define CPU_PREFIX "ANDES_DISASS"


////////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Append the character to to the result
//
static void putChar(char **result, char ch) {

    // get the tail pointer
    char *tail = *result;

    // do the append
    *tail++ = ch;

    // add null terminator
    *tail = 0;

    // update the tail pointer
    *result = tail;
}

//
// Append the string to to the result
//
static void putString(char **result, const char *string) {

    // get the tail pointer
    char *tail = *result;
    char  ch;

    // do the append
    while((ch=*string++)) {
        *tail++ = ch;
    }

    // add null terminator
    *tail = 0;

    // update the tail pointer
    *result = tail;
}

//
// Emit key for uncooked value if required
//
static void putUncookedKey(char **result, const char *key, Bool uncooked) {
    if(uncooked) {
        putString(result, key);
        putChar(result, ':');
    }
}

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

//
// This defines the minimum string width to use for the opcode
//
#define OP_WIDTH 7

//
// Emit instruction format if required
//
static void putInstruction(andesInstrInfoP info, char **result) {

    const char *fmt;
    char tmp[32];

    // select format string
    if(info->bytes==2) {
        fmt = "%04x     ";
    } else {
        fmt = "%08x ";
    }

    // emit basic opcode string
    sprintf(tmp, fmt, info->instruction);
    putString(result, tmp);
}

//
// Append comma separator, unless previous character is space or comma (allows
// for omitted optional arguments)
//
static void putComma(char **result, Bool uncooked) {

    if(!uncooked) {

        char *tail = *result;

        switch(tail[-1]) {
            case ',':
            case ' ':
                break;
            default:
                putChar(result, ',');
                break;
        }
    }
}

//
// Emit signed argument
//
static void putD(char **result, Uns32 value) {
    char tmp[32];
    sprintf(tmp, "%d", value);
    putString(result, tmp);
}

//
// Emit target address argument
//
static void putTarget(char **result, Uns64 value) {
    char tmp[32];
    sprintf(tmp, FMT_Ax, value);
    putString(result, tmp);
}

//
// Emit register argument
//
static void putReg(
    riscvP       riscv,
    char       **result,
    riscvRegDesc r,
    Bool         uncooked
) {
    Uns32 index = getRIndex(r);

    if(isXReg(r)) {
        putString(result, andesGetXRegName(riscv, index));
    } else if(isFReg(r)) {
        putString(result, andesGetFRegName(riscv, index));
    } else if(isVReg(r)) {
        putString(result, andesGetVRegName(riscv, index));
    } else {
        VMI_ABORT("Bad register specifier 0x%x", r); // LCOV_EXCL_LINE
    }
}

//
// Emit optional mask register argument
//
static void putOptMask(
    riscvP       riscv,
    char       **result,
    riscvRegDesc mask,
    const char  *suffix,
    Bool         uncooked
) {
    if(mask) {

        putUncookedKey(result, " MASK", uncooked);

        putString(result, andesGetVRegName(riscv, getRIndex(mask)));

        if(!uncooked) {
            putString(result, suffix);
        }
    }
}

//
// Add opcode string to result
//
static void putOpcode(riscvP riscv, char **result, andesInstrInfoP info) {

    // emit basic opcode
    putString(result, info->opcode);

    // emit size modifier if required
    switch(info->memBits) {
        case 8:  putChar(result, 'b'); break;
        case 16: putChar(result, 'h'); break;
        case 32: putChar(result, 'w'); break;
        case 64: putChar(result, 'd'); break;
    }

    // emit 32-bit unsigned modifier if required
    if(info->ze32) {
        putString(result, ".ze");
    }

    // emit unsigned modifier if required
    if(info->unsExt && !info->unsExtQ) {
        putChar(result, 'u');
    }

    // emit implicit register argument if required
    if(info->rImplicit) {
        putReg(riscv, result, info->rImplicit, False);
    }

    // emit implicit F32 conversion indication if required
    if(info->cvtF32) {
        putChar(result, 'w');
    }
}

//
// Generate instruction disassembly using the format string
//
static void disassembleFormat(
    riscvP          riscv,
    andesInstrInfoP info,
    char          **result,
    const char     *format,
    Bool            uncooked
) {
    // generate instruction pattern
    if(!uncooked) {
        putInstruction(info, result);
    }

    // get offset at opcode start
    const char *opcodeStart = *result;

    // add opcode string to result
    putOpcode(riscv, result, info);

    if(*format) {

        // calculate length of opcode text
        const char *opcodeEnd = *result;
        Uns32       len       = opcodeEnd-opcodeStart;
        char        ch;

        // emit formatted space if cooked output
        if(!uncooked)  {

            // pad to minimum width
            for(; len<OP_WIDTH; len++) {
                putChar(result, ' ');
            }

            // emit space before arguments
            putChar(result, ' ');
        }

       // generate arguments in appropriate format
        while((ch=*format++)) {

            switch(ch) {
                case EMIT_R1:
                    putUncookedKey(result, " R1", uncooked);
                    putReg(riscv, result, info->r[0], uncooked);
                    break;
                case EMIT_R2:
                    putUncookedKey(result, " R2", uncooked);
                    putReg(riscv, result, info->r[1], uncooked);
                    break;
                case EMIT_R3:
                    putUncookedKey(result, " R3", uncooked);
                    putReg(riscv, result, info->r[2], uncooked);
                    break;
                case EMIT_CS1:
                    putUncookedKey(result, " C1", uncooked);
                    putD(result, info->c1);
                    break;
                case EMIT_CS2:
                    putUncookedKey(result, " C2", uncooked);
                    putD(result, info->c2);
                    break;
                case EMIT_TGT:
                    putUncookedKey(result, " T", uncooked);
                    putTarget(result, info->c1);
                    break;
                case EMIT_RM:
                    putOptMask(riscv, result, info->mask, ".t", uncooked);
                    break;
                case ',':
                    putComma(result, uncooked);
                    break;
                default:
                    if(!uncooked) {putChar(result, ch);}
                    break;
            }
        }

        // emit comma before optional rounding mode
        putComma(result, uncooked);
    }

    // strip trailing whitespace and commas
    char *tail = (*result)-1;
    while((*tail == ' ') || (*tail == ',')) {
        *tail-- = 0;
    }
}

//
// This defines the size of the disassembly buffer
//
#define DISASS_BUFFER_SIZE 256

//
// andes disassembler, decoded instruction interface
//
static const char *disassembleInfo(
    riscvP          riscv,
    andesInstrInfoP info,
    vmiDisassAttrs  attrs
) {
    // static buffer to hold disassembly result
    static char result[DISASS_BUFFER_SIZE];
    const char *format = info->format;
    char       *tail   = result;

    // sanity check format is specified
    VMI_ASSERT(format, "null instruction format");

    // disassemble using the format for the type
    disassembleFormat(riscv, info, &tail, format, attrs==DSA_UNCOOKED);

    // validate disassembly buffer has not overflowed
    VMI_ASSERT(
        tail <= &result[DISASS_BUFFER_SIZE-1],
        "buffer overflow for instruction '%s'\n",
        result
    );

    // return the result
    return result;
}

//
// andes disassembler, VMI interface
//
VMIOS_DISASSEMBLE_FN(andesDisassemble) {

    riscvP         riscv  = (riscvP)processor;
    const char    *result = 0;
    andesInstrInfo info;

    // decode instruction
    andesDecode(riscv, object, thisPC, &info);

    // return disassembled instruction
    if(info.type==AN_IT_MSA_UNA) {
        // base model instruction affected by alignment
    } else if(info.type!=AN_IT_LAST) {
        result = disassembleInfo(riscv, &info, attrs);
    } else {
        result = andesACEDisassemble(object, info.instruction);
    }

    return result;
}

