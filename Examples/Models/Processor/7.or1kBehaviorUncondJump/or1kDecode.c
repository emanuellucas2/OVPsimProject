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

// VMI header files
#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"

// model header files
#include "or1kDecode.h"
#include "or1kDisassembleFormats.h"


////////////////////////////////////////////////////////////////////////////////
// FIELD EXTRACTION MACROS
////////////////////////////////////////////////////////////////////////////////

#define WIDTH(_W, _ARG) ((_ARG) & ((1<<(_W))-1))

#define OP_D(_I)        WIDTH(5,(_I)>>21)
#define OP_A(_I)        WIDTH(5,(_I)>>16)
#define OP_B(_I)        WIDTH(5,(_I)>>11)
#define OP_U1(_I)       WIDTH(16,(_I)>>0)
#define OP_S1(_I)       ((Int16)OP_U1(_I))
#define OP_T(_I)        (((Int32)(WIDTH(26,(_I)>>0)<<6))>>4)


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION ATTRIBUTE TABLE
////////////////////////////////////////////////////////////////////////////////

//
// Define the location of register in an instruction
//
typedef enum regSpecE {
    R_NA,                       // no register
    R_D,                        // register at bits 25:21
    R_A,                        // register at bits 20:16
    R_B,                        // register at bits 15:11
} regSpec;

//
// Define the location of constant in an instruction
//
typedef enum constSpecE {
    C_NA,                       // no register
    C_S1,                       // signed constant in bits 15:0
    C_U1,                       // unsigned constant in bits 15:0
    C_T,                        // signed target offset in bits 25:0
} constSpec;

//
// Structure defining characteristics of each opcode type
//
typedef struct opAttrsS {
    const char *member;         // enumeration member name
    const char *opcode;         // opcode name
    const char *format;         // format string
    const char *decode;         // decode string
    regSpec     r1      : 8;    // register 1 specification
    regSpec     r2      : 8;    // register 2 specification
    constSpec   c       : 8;    // constant value specification
} opAttrs, *opAttrsP;

//
// Attributes for instructions like ADDI
//
#define ATTR_SET_ADDI(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_R2_XIMM,    \
        decode : _DECODE,           \
        r1     : R_D,               \
        r2     : R_A,               \
        c      : C_S1               \
    }

//
// Attributes for instructions like ANDI
//
#define ATTR_SET_ANDI(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_R2_XIMM,    \
        decode : _DECODE,           \
        r1     : R_D,               \
        r2     : R_A,               \
        c      : C_U1               \
    }

//
// Attributes for instructions like BF
//
#define ATTR_SET_BF(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_TARGET,        \
        decode : _DECODE,           \
        c      : C_T                \
    }

//
// Attributes for instructions like JR
//
#define ATTR_SET_JR(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1,            \
        decode : _DECODE,           \
        r1     : R_B                \
    }

//
// This specifies attributes for each opcode
//
const static opAttrs attrsArray[OR1K_IT_LAST+1] = {

    // handle arithmetic instructions (second argument constant)
    ATTR_SET_ADDI (ADDI,  "addi",  "|100111..........................|"),
    ATTR_SET_ADDI (ADDIC, "addic", "|101000..........................|"),
    ATTR_SET_ANDI (ANDI,  "andi",  "|101001..........................|"),
    ATTR_SET_ANDI (ORI,   "ori",   "|101010..........................|"),
    ATTR_SET_ADDI (XORI,  "xori",  "|101011..........................|"),
    ATTR_SET_ADDI (MULI,  "muli",  "|101100..........................|"),

    // handle branch instructions
    ATTR_SET_BF   (J,     "j",     "|000000..........................|"),
    ATTR_SET_JR   (JR,    "jr",    "|010001..........................|"),
    ATTR_SET_BF   (JAL,   "jal",   "|000001..........................|"),
    ATTR_SET_JR   (JALR,  "jalr",  "|010010..........................|"),
};


////////////////////////////////////////////////////////////////////////////////
// DECODE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Create the OR1K decode table
//
static vmidDecodeTableP createDecodeTable(void) {

    vmidDecodeTableP    table = vmidNewDecodeTable(32, OR1K_IT_LAST);
    or1kInstructionType type;

    for(type=0; type<OR1K_IT_LAST; type++) {
        const opAttrs *attrs = &attrsArray[type];
        vmidNewEntryFmtBin(table, attrs->member, type, attrs->decode, 0);
    }

    return table;
}

//
// Extract register index from instruction
//
static Uns32 getReg(Uns32 instruction, regSpec rs) {

    Uns32 result = 0;

    switch(rs) {
        case R_NA:
            break;
        case R_D:
            result = OP_D(instruction);
            break;
        case R_A:
            result = OP_A(instruction);
            break;
        case R_B:
            result = OP_B(instruction);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Extract constant value from instruction
//
static Uns32 getConst(Uns32 instruction, constSpec cs, Uns32 thisPC) {

    Uns32 result = 0;

    switch(cs) {
        case C_NA:
            break;
        case C_S1:
            result = OP_S1(instruction);
            break;
        case C_U1:
            result = OP_U1(instruction);
            break;
        case C_T:
            // PC-relative address
            result = thisPC + OP_T(instruction);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Decode the instruction at the passed address. The 'info' structure is filled
// with details of the instruction.
//
void or1kDecode(or1kP or1k, Uns32 thisPC, or1kInstructionInfoP info) {

    // get the instruction at the passed address - always 4 bytes on OR1K
    vmiProcessorP processor   = (vmiProcessorP)or1k;
    Uns32         instruction = vmicxtFetch4Byte(processor, thisPC);

    // get the OR1K decode table
    static vmidDecodeTableP decodeTable;
    if(!decodeTable) {
        decodeTable = createDecodeTable();
    }

    // decode the instruction to get the type and attributes
    or1kInstructionType type  = vmidDecode(decodeTable, instruction);
    const opAttrs      *attrs = &attrsArray[type];

    // fill structure fields
    info->opcode      = attrs->opcode;
    info->format      = attrs->format;
    info->type        = type;
    info->thisPC      = thisPC;
    info->instruction = instruction;
    info->r1          = getReg(instruction, attrs->r1);
    info->r2          = getReg(instruction, attrs->r2);
    info->c           = getConst(instruction, attrs->c, thisPC);
}
