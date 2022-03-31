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

// standard includes
#include <stdio.h>

// model header files
#include "or1kDecode.h"
#include "or1kDisassembleFormats.h"
#include "or1kFunctions.h"


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
// Emit unsigned value
//
static void putU(char **result, Uns32 value) {

    char tmp[32];

    sprintf(tmp, "%u", value);

    putString(result, tmp);
}

//
// Emit hexadecimal value
//
static void putX(char **result, Uns32 value) {

    char tmp[32];

    sprintf(tmp, "0x%x", value);

    putString(result, tmp);
}

//
// Emit hexadecimal target address
//
static void putTarget(char **result, Uns32 value) {

    char tmp[32];

    sprintf(tmp, "0x%08x", value);

    putString(result, tmp);
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
// Emit condition string
//
static void putCondition(char **result, or1kCondition cond) {

    static const char *map[] = {
        [OR1K_COND_NA]  = "",
        [OR1K_COND_EQ]  = "eq",
        [OR1K_COND_NE]  = "ne",
        [OR1K_COND_GTU] = "gtu",
        [OR1K_COND_GEU] = "geu",
        [OR1K_COND_LTU] = "ltu",
        [OR1K_COND_LEU] = "leu",
        [OR1K_COND_GTS] = "gts",
        [OR1K_COND_GES] = "ges",
        [OR1K_COND_LTS] = "lts",
        [OR1K_COND_LES] = "les",
        [OR1K_COND_BAD] = "???",
    };

    putString(result, map[cond]);
}

//
// Emit "i" suffix if required
//
static void putISuffix(char **result, Bool iSuffix) {

    if(iSuffix) {
        putChar(result, 'i');
    }
}

//
// Emit register description
//
static void putRegister(char **result, Uns32 r) {
    putChar(result, 'r');
    putU(result, r);
}

//
// Generate instruction disassembly using the format string
//
static void disassembleFormat(
    or1kP                or1k,
    or1kInstructionInfoP info,
    char               **result,
    const char          *format,
    Bool                 uncooked
) {
    char *argStart = (*result)+9;
    char  ch;

    // emit opcode
    putString(result, "l.");
    putString(result, info->opcode);
    putCondition(result, info->cond);
    putISuffix(result, info->iSuffix);

    if(*format) {

        // pad opcode to start of arguments
        if(!uncooked) {

            putChar(result, ' ');

            while(*result!=argStart) {
                putChar(result, ' ');
            }
        }

        // generate arguments in appropriate format
        while((ch=*format++)) {

            switch(ch) {

                case EMIT_R1:
                    putUncookedKey(result, " R1", uncooked);
                    putRegister(result, info->r1);
                    break;

                case EMIT_R2:
                    putUncookedKey(result, " R2", uncooked);
                    putRegister(result, info->r2);
                    break;

                case EMIT_R3:
                    putUncookedKey(result, " R3", uncooked);
                    putRegister(result, info->r3);
                    break;

                case EMIT_XIMM:
                    putUncookedKey(result, " CX", uncooked);
                    putX(result, info->c);
                    break;

                case EMIT_TARGET:
                    putUncookedKey(result, " T", uncooked);
                    putTarget(result, info->c);
                    break;

                default:
                    if(!uncooked) {putChar(result, ch);}
                    break;
            }
        }
    }
}

//
// OR1K disassembler, decoded instruction interface
//
static const char *disassembleInfo(
    or1kP                or1k,
    or1kInstructionInfoP info,
    vmiDisassAttrs       attrs
) {
    // static buffer to hold result
    static char result[256];
    const char *format = info->format;
    char       *tail   = result;

    // disassemble using the format for the type
    if(format) {
        disassembleFormat(or1k, info, &tail, format, attrs==DSA_UNCOOKED);
    } else {
        sprintf(result, "??? instruction:0x%08x", info->instruction);
    }

    // return the result
    return result;
}

//
// OR1K disassembler, VMI interface
//
VMI_DISASSEMBLE_FN(or1kDisassemble) {

    // static buffer to hold disassembly result
    or1kP               or1k = (or1kP)processor;
    or1kInstructionInfo info;

    // decode instruction
    or1kDecode(or1k, thisPC, &info);

    // return disassembled instruction
    return disassembleInfo(or1k, &info, attrs);
}

