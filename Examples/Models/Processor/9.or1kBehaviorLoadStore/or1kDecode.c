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
#define OP_U2(_I)       ((WIDTH(5,(_I)>>21)<<11) | WIDTH(11,(_I)>>0))
#define OP_S2(_I)       ((Int16)OP_U2(_I))
#define OP_CMPOP(_I)    WIDTH(4,(_I)>>21)
#define OP_L(_I)        WIDTH(6,(_I)>>0)
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
    C_S2,                       // signed constant in bits 25:21,10:0
    C_L,                        // constant in bits 5:0
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
    regSpec     r3      : 8;    // register 3 specification
    constSpec   c       : 8;    // constant value specification
    Uns32       bytes   : 8;    // load/store size specification
    or1kExtend  extend  : 8;    // load/store sign extension
    Bool        isCond  : 1;    // is instruction conditional?
    Bool        iSuffix : 1;    // does opcode require 'i' suffix?
} opAttrs, *opAttrsP;

//
// Attributes for instructions like MOVHI
//
#define ATTR_SET_MOVHI(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_XIMM,       \
        decode : _DECODE,           \
        r1     : R_D,               \
        c      : C_U1               \
    }

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
// Attributes for instructions like ADD
//
#define ATTR_SET_ADD(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_R2_R3,      \
        decode : _DECODE,           \
        r1     : R_D,               \
        r2     : R_A,               \
        r3     : R_B                \
    }

//
// Attributes for instructions like SLLI
//
#define ATTR_SET_SLLI(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_R2_XIMM,    \
        decode : _DECODE,           \
        r1     : R_D,               \
        r2     : R_A,               \
        c      : C_L                \
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
// Attributes for instructions like LWZ
//
#define ATTR_SET_LWZ(_NAME, _OPCODE, _DECODE, _BYTES, _EXT) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_OFFSET_R2,  \
        decode : _DECODE,           \
        r1     : R_D,               \
        r2     : R_A,               \
        c      : C_S1,              \
        bytes  : _BYTES,            \
        extend : OR1K_EXTEND_##_EXT \
    }

//
// Attributes for instructions like SW
//
#define ATTR_SET_SW(_NAME, _OPCODE, _DECODE, _BYTES) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_OFFSET_R1_R2,  \
        decode : _DECODE,           \
        r1     : R_A,               \
        r2     : R_B,               \
        c      : C_S2,              \
        bytes  : _BYTES             \
    }

//
// Attributes for instructions like SF
//
#define ATTR_SET_SF(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_R2,         \
        decode : _DECODE,           \
        r1     : R_A,               \
        r2     : R_B,               \
        isCond : True               \
    }

//
// Attributes for instructions like SFI
//
#define ATTR_SET_SFI(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_R1_XIMM,       \
        decode : _DECODE,           \
        r1     : R_A,               \
        c      : C_S1,              \
        isCond : True,              \
        iSuffix: True               \
    }

//
// Attributes for instructions like NOP
//
#define ATTR_SET_NOP(_NAME, _OPCODE, _DECODE) \
    [OR1K_IT_##_NAME] = {           \
        member : #_NAME,            \
        opcode : _OPCODE,           \
        format : FMT_XIMM,          \
        decode : _DECODE,           \
        c      : C_U1               \
    }

//
// This specifies attributes for each opcode
//
const static opAttrs attrsArray[OR1K_IT_LAST+1] = {

    // handle movhi instruction
    ATTR_SET_MOVHI(MOVHI, "movhi", "|000110.........0................|"),

    // handle arithmetic instructions (second argument constant)
    ATTR_SET_ADDI (ADDI,  "addi",  "|100111..........................|"),
    ATTR_SET_ADDI (ADDIC, "addic", "|101000..........................|"),
    ATTR_SET_ANDI (ANDI,  "andi",  "|101001..........................|"),
    ATTR_SET_ANDI (ORI,   "ori",   "|101010..........................|"),
    ATTR_SET_ADDI (XORI,  "xori",  "|101011..........................|"),
    ATTR_SET_ADDI (MULI,  "muli",  "|101100..........................|"),

    // handle arithmetic instructions (second argument register)
    ATTR_SET_ADD  (ADD,   "add",   "|111000................00....0000|"),
    ATTR_SET_ADD  (ADDC,  "addc",  "|111000................00....0001|"),
    ATTR_SET_ADD  (SUB,   "sub",   "|111000................00....0010|"),
    ATTR_SET_ADD  (AND,   "and",   "|111000................00....0011|"),
    ATTR_SET_ADD  (OR,    "or",    "|111000................00....0100|"),
    ATTR_SET_ADD  (XOR,   "xor",   "|111000................00....0101|"),
    ATTR_SET_ADD  (MUL,   "mul",   "|111000................11....0110|"),
    ATTR_SET_ADD  (DIV,   "div",   "|111000................11....1001|"),
    ATTR_SET_ADD  (DIVU,  "divu",  "|111000................11....1010|"),

    // handle shift/rotate instructions (second argument constant)
    ATTR_SET_SLLI (SLLI,  "slli",  "|101110..................00......|"),
    ATTR_SET_SLLI (SRLI,  "srli",  "|101110..................01......|"),
    ATTR_SET_SLLI (SRAI,  "srai",  "|101110..................10......|"),
    ATTR_SET_SLLI (RORI,  "rori",  "|101110..................11......|"),

    // handle shift/rotate instructions (second argument register)
    ATTR_SET_ADD  (SLL,   "sll",   "|111000................0000..1000|"),
    ATTR_SET_ADD  (SRL,   "srl",   "|111000................0001..1000|"),
    ATTR_SET_ADD  (SRA,   "sra",   "|111000................0010..1000|"),
    ATTR_SET_ADD  (ROR,   "ror",   "|111000................0011..1000|"),

    // handle branch instructions
    ATTR_SET_BF   (BF,    "bf",    "|000100..........................|"),
    ATTR_SET_BF   (BNF,   "bnf",   "|000011..........................|"),
    ATTR_SET_BF   (J,     "j",     "|000000..........................|"),
    ATTR_SET_JR   (JR,    "jr",    "|010001..........................|"),
    ATTR_SET_BF   (JAL,   "jal",   "|000001..........................|"),
    ATTR_SET_JR   (JALR,  "jalr",  "|010010..........................|"),

    // handle load instructions
    ATTR_SET_LWZ  (LWZ,   "l",     "|100001..........................|", 4, Z),
    ATTR_SET_LWZ  (LWS,   "l",     "|100010..........................|", 4, S),
    ATTR_SET_LWZ  (LBZ,   "l",     "|100011..........................|", 1, Z),
    ATTR_SET_LWZ  (LBS,   "l",     "|100100..........................|", 1, S),
    ATTR_SET_LWZ  (LHZ,   "l",     "|100101..........................|", 2, Z),
    ATTR_SET_LWZ  (LHS,   "l",     "|100110..........................|", 2, S),

    // handle store instructions
    ATTR_SET_SW   (SW,    "s",     "|110101..........................|", 4),
    ATTR_SET_SW   (SB,    "s",     "|110110..........................|", 1),
    ATTR_SET_SW   (SH,    "s",     "|110111..........................|", 2),

    // handle comparison instructions
    ATTR_SET_SF   (SF,    "sf",    "|1110010.........................|"),
    ATTR_SET_SFI  (SFI,   "sf",    "|1011110.........................|"),

    // handle nop instruction
    ATTR_SET_NOP  (NOP,   "nop",   "|00010101........................|")
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
        case C_S2:
            result = OP_S2(instruction);
            break;
        case C_L:
            result = OP_L(instruction);
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
// Extract condition from instruction
//
or1kCondition getCondition(Uns32 instruction, Bool isCond) {

    or1kCondition result = OR1K_COND_NA;

    if(isCond) {

        const static or1kCondition map[16] = {
            OR1K_COND_EQ,   // 0x0: a == b
            OR1K_COND_NE,   // 0x1: a != b
            OR1K_COND_GTU,  // 0x2: a >  b (unsigned)
            OR1K_COND_GEU,  // 0x3: a >= b (unsigned)
            OR1K_COND_LTU,  // 0x4: a <  b (unsigned)
            OR1K_COND_LEU,  // 0x5: a <= b (unsigned)
            OR1K_COND_BAD,  // 0x6: invalid
            OR1K_COND_BAD,  // 0x7: invalid
            OR1K_COND_BAD,  // 0x8: invalid
            OR1K_COND_BAD,  // 0x9: invalid
            OR1K_COND_GTS,  // 0xa: a >  b (signed)
            OR1K_COND_GES,  // 0xb: a >= b (signed)
            OR1K_COND_LTS,  // 0xc: a <  b (signed)
            OR1K_COND_LES,  // 0xd: a <= b (signed)
            OR1K_COND_BAD,  // 0xe: invalid
            OR1K_COND_BAD   // 0xf: invalid
        };

        result = map[OP_CMPOP(instruction)];
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
    info->r3          = getReg(instruction, attrs->r3);
    info->c           = getConst(instruction, attrs->c, thisPC);
    info->bytes       = attrs->bytes;
    info->extend      = attrs->extend;
    info->cond        = getCondition(instruction, attrs->isCond);
    info->iSuffix     = attrs->iSuffix;

    // detect invalid condition and indicate that decode failed if found
    if(info->cond==OR1K_COND_BAD) {
        info->type = OR1K_IT_LAST;
    }
}
