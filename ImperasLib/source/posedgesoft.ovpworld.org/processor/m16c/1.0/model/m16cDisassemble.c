/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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
#include <stdio.h>

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "m16cDecode.h"
#include "m16cFunctions.h"
#include "m16cDisassemble.h"

//
// This defines the minimum string width to use for the opcode
//
#define OP_WIDTH 8


#define FMT_UNKNOWN     "__undef__"

/*
static const char *branchConditionCode[16] = {
    "v",  "l",  "e",  "nh",
    "n",  "r",  "lt", "le",
    "nv", "nl", "ne", "h",
    "p",  "sa", "ge", "gt"
};

*/
static const char *conditionCode[15] = {
    "",
    "eq",
    "geu",
    "gtu",
    "leu",
    "ltu",
    "n",
    "ne",
    "pz",
    "ge",
    "gt",
    "le",
    "lt",
    "no",
    "o"
};

static const char *directionCode[5] = {
    "",
    "ll",
    "lh",
    "hl",
    "hh",
};





static const char *registerAliasB[50] = {
    // bank 0
    "r0l",       "r0h",
    "r2",        0,
    "r1l",       "r1h",
    "r3",        0,
    "a0",        0,
    "a1",        0,
    0,           0,
    "fb",        0,
    "r2",        0,
    // bank 1
    "r0",        0,
    "r3",        0,
    "r1",        0,
    "a0",        0,
    "a1",        0,
    "fb",        0,
    0,           0,
    "sp",        0,
    0,           0,
    "sp",        0,
    0,           0,
    "sb",        0,
    "flg",       0,
    "intbh",     0,
    "intbl",     0,
    0,           0
};

static const char *registerAliasW[50] = {
    // bank 0
    "r0",        0,
    "r2",        0,
    "r1",        0,
    "r3",        0,
    "a0",        0,
    "a1",        0,
    0,           0,
    "fb",        0,
    "r2",        0,
    // bank 1
    "r0",        0,
    "r3",        0,
    "r1",        0,
    "a0",        0,
    "a1",        0,
    "fb",        0,
    0,           0,
    "sp",        0,
    0,           0,
    "sp",        0,
    0,           0,
    "sb",        0,
    "flg",       0,
    "intbh",     0,
    "intbl",     0,
    "none",      0
};

static const char *registerAliasA[50] = {
    // bank 0
    "r2r0",      0,
    0,           0,
    "r3r1",      0,
    0,           0,
    "a1a0",      0,
    0,           0,
    0,           0,
    "fb",        0,
    "r2",        0,
    // bank 1
    "r0",        0,
    "r3",        0,
    "r1",        0,
    "a0",        0,
    "a1",        0,
    "fb",        0,
    0,           0,
    "sp",        0,
    0,           0,
    "sp",        0,
    0,           0,
    "sb",        0,
    "flg",       0,
    "intbh",     0,
    "intbl",     0,
    "none",      0
};




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
    while ((ch=*string++)) {
        *tail++ = ch;
    }

    // add null terminator
    *tail = 0;

    // update the tail pointer
    *result = tail;
}

//
// Emit decimal argument using format 0x%x
//

static void put0xS32(char **result, Int32 value) {
    char tmp[32];
    sprintf(tmp, "0x%x", value);
    putString(result, tmp);
}

static void put0dS32(char **result, Int32 value) {
    char tmp[32];
    sprintf(tmp, "%d", value);
    putString(result, tmp);
}

/*
static void put0dU32(char **result, Uns32 value) {
    char tmp[32];
    sprintf(tmp, "%u", value);
    putString(result, tmp);
}
//
// Emit register argument
//
static void putUserReg(char **result, Uns32 value) {
    char tmp[32];

    // Special case for r3, r4, r30, r31
    const char *regAlias = userRegisterAlias[value];

    if (regAlias) {
        sprintf(tmp, "%s", regAlias);
    } else {
        sprintf(tmp, "r%d", value);
    }
    putString(result, tmp);
}
*/
//
// Emit register argument
//
static void putReg(char **result, sizeSpec size, Uns32 value) {
    char tmp[32];


    const char *regAlias;


    if (size == W)
        regAlias = registerAliasW[value];
    else if ((size == A) || (size == L))
        regAlias = registerAliasA[value];
    else
        regAlias = registerAliasB[value];

    if (regAlias) {
        sprintf(tmp, "%s", regAlias);
    } else {
        sprintf(tmp, "?reg %d", value);
    }
    putString(result, tmp);
}


static void putRegI(char **result, sizeSpec size, Uns32 value) {
    char tmp[32];


    const char *regAlias;


    regAlias = registerAliasW[value];

    if (regAlias) {
        sprintf(tmp, "%s", regAlias);
    } else {
        sprintf(tmp, "?reg %d", value);
    }

    putString(result, tmp);
}


//
// Generate instruction disassembly using the format string
//
static void disassembleFormat(
    m16cP                m16c,
    m16cInstructionInfoP info,
    char              **result
) {


    // generate opcode text
    putString(result, info->opcode);

    if (info->cond != COND_NA) {
        putString(result, conditionCode[info->cond]);
    }
    if (info->dir != DIR_NA) {
        putString(result, directionCode[info->dir]);
    }


    putChar(result, ' ');
    switch (info->srcMode)
    {
        case  MODE_NA:
            break;
        case  MODE_REG:
            putReg(result, info->sz, info->rs1);
            break;
        case  MODE_REGB:
            putReg(result, B, info->rs1);
            break;
        case  MODE_IMM6:
        case  MODE_IMM:
            putChar(result, '#');
            if (info->imm > -10 && info->imm < 10) {
                put0dS32(result, info->imm);
            } else {
                put0xS32(result, info->imm);
            }
            break;
        case  MODE_REGO:
            if (info->offsetS != 0 || info->rs1 == M16C_REG_NONE) {
                // put0xS32(result,info->offsetS);
                put0dS32(result, info->offsetS);
            }
    //  case  MODE_REGI:
            if (info->rs1 != M16C_REG_NONE) {
                putChar(result, '[');
                putRegI(result, info->sz, info->rs1);
                putChar(result, ']');
            }
            break;
        case  MODE_ADDRI:
            putString(result, "[a1a0]");
            break;
    //  case  MODE_ABS:
    //      put0xS32(result,info->offsetS);
        case  MODE_ABS16_ABS20:
        case  MODE_LDINTB:
            break;
        case  MODE_ZERO:
             putChar(result, '#');
             putChar(result, '0');
             break;
        default:
            break;
    }

    if ((info->srcMode != MODE_NA) && (info->destMode != MODE_NA)) {
        putChar(result, ',');
    }

    switch (info->destMode)
    {
        case  MODE_NA:
            break;
        case  MODE_REG:
            putReg(result, info->sz, info->rd1);
            break;
        case  MODE_IMM:
            // Error
            break;
        case  MODE_REGO:
            if (info->offsetD != 0 || info->rd1 == M16C_REG_NONE) {
                // put0xS32(result,info->offsetD);
                put0dS32(result, info->offsetD);
            }
            if (info->rd1 != M16C_REG_NONE) {
                putChar(result, '[');
                putRegI(result, info->sz, info->rd1);
                putChar(result, ']');
            }
            // put0xS32(result,info->offsetD);
            break;
        case  MODE_ADDRI:
            putString(result, "[a1a0]");
            break;
        case  MODE_LABEL:
            put0xS32(result, info->offsetD);
            break;
        case MODE_B:
            putChar(result, 'b');
            break;
        case MODE_C:
            putChar(result, 'c');
            break;
        case MODE_D:
            putChar(result, 'd');
            break;
        case MODE_I:
            putChar(result, 'i');
            break;
        case MODE_O:
            putChar(result, 'o');
            break;
        case MODE_S:
            putChar(result, 's');
            break;
        case MODE_U:
            putChar(result, 'u');
            break;
        case MODE_Z:
            putChar(result, 'z');
            break;
        case  MODE_ABS16_ABS20:
        case  MODE_LDINTB:

             break;
        default:
            break;
    }

    if (info->cons != 0) {
        putChar(result, ',');
        put0xS32(result, info->cons);
    }

    // strip trailing whitespace and commas
    char *tail = (*result)-1;
    while ((*tail == ' ') || (*tail == ',')) {
        *tail-- = 0;
    }
}


//
// M16C disassembler, decoded instruction interface
//
const char *m16cDisassembleInfo(m16cP m16c, m16cInstructionInfoP info) {
    // static buffer to hold disassembly result
    static char result[256];
    //    const char *format;
    char       *tail = result;

    disassembleFormat(m16c, info, &tail);

    // return the result
    return result;
}


//
// m16c disassembler
//
VMI_DISASSEMBLE_FN(m16cDisassemble) {
    // static buffer to hold disassembly result
    m16cP               m16c = (m16cP)processor;
    m16cInstructionInfo info;

    // get instruction and instruction type
    m16cDecode(m16c, thisPC, &info);

    // return disassembled instruction
    return m16cDisassembleInfo(m16c, &info);
}

