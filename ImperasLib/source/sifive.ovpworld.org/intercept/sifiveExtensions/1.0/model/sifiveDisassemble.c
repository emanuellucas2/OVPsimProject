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
#include "sifiveDecode.h"
#include "sifiveDecodeTypes.h"
#include "sifiveDisassembleFormats.h"
#include "sifiveFunctions.h"
#include "sifiveUtils.h"


//
// Prefix for messages from this module
//
#define CPU_PREFIX "SIFIVE_DISASS"


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
static void putInstruction(sifiveInstrInfoP info, char **result) {

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
        putString(result, sifiveGetXRegName(riscv, index));
    } else if(isFReg(r)) {
        putString(result, sifiveGetFRegName(riscv, index));
    } else if(isVReg(r)) {
        putString(result, sifiveGetVRegName(riscv, index));
    } else {
        VMI_ABORT("Bad register specifier 0x%x", r); // LCOV_EXCL_LINE
    }
}

//
// Add opcode string to result
//
static void putOpcode(riscvP riscv, char **result, sifiveInstrInfoP info) {

    // emit basic opcode
    putString(result, info->opcode);
}

//
// Generate instruction disassembly using the format string
//
static void disassembleFormat(
    riscvP          riscv,
    sifiveInstrInfoP info,
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
// sifive disassembler, decoded instruction interface
//
static const char *disassembleInfo(
    riscvP          riscv,
    sifiveInstrInfoP info,
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
// sifive disassembler, VMI interface
//
VMIOS_DISASSEMBLE_FN(sifiveDisassemble) {

    riscvP         riscv = (riscvP)processor;
    sifiveInstrInfo info;

    // decode instruction
    sifiveDecode(riscv, object, thisPC, &info);

    // return disassembled instruction
    return (info.type!=S5_IT_LAST) ? disassembleInfo(riscv, &info, attrs) : 0;
}

