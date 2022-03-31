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

// Utility routines and structures for the OR1K decoder

#ifndef OR1KDECODE_H
#define OR1KDECODE_H

// basic number types
#include "hostapi/impTypes.h"

// VMI header files
#include "vmi/vmiTypes.h"

// model header files
#include "or1kStructure.h"

//
// Instruction type enumeration
//
typedef enum or1kInstructionTypeE {

    // movhi instruction
    OR1K_IT_MOVHI,

    // arithmetic instructions (second argument constant)
    OR1K_IT_ADDI,
    OR1K_IT_ADDIC,
    OR1K_IT_ANDI,
    OR1K_IT_ORI,
    OR1K_IT_XORI,
    OR1K_IT_MULI,

    // arithmetic instructions (second argument register)
    OR1K_IT_ADD,
    OR1K_IT_ADDC,
    OR1K_IT_SUB,
    OR1K_IT_AND,
    OR1K_IT_OR,
    OR1K_IT_XOR,
    OR1K_IT_MUL,
    OR1K_IT_DIV,
    OR1K_IT_DIVU,

    // shift/rotate instructions (second argument constant)
    OR1K_IT_SLLI,
    OR1K_IT_SRLI,
    OR1K_IT_SRAI,
    OR1K_IT_RORI,

    // shift/rotate instructions (second argument register)
    OR1K_IT_SLL,
    OR1K_IT_SRL,
    OR1K_IT_SRA,
    OR1K_IT_ROR,

    // branch instructions
    OR1K_IT_BF,
    OR1K_IT_BNF,
    OR1K_IT_J,
    OR1K_IT_JR,
    OR1K_IT_JAL,
    OR1K_IT_JALR,

    // load instructions
    OR1K_IT_LWZ,
    OR1K_IT_LWS,
    OR1K_IT_LBZ,
    OR1K_IT_LBS,
    OR1K_IT_LHZ,
    OR1K_IT_LHS,

    // store instructions
    OR1K_IT_SW,
    OR1K_IT_SB,
    OR1K_IT_SH,

    // comparison instructions
    OR1K_IT_SF,
    OR1K_IT_SFI,

    // nop instruction
    OR1K_IT_NOP,

    // KEEP LAST: for sizing the array
    OR1K_IT_LAST

} or1kInstructionType;

//
// This type enumerates implemented condition codes
//
typedef enum or1kConditionE {
    OR1K_COND_NA,               // no condition
    OR1K_COND_EQ,               // 0x0: a == b
    OR1K_COND_NE,               // 0x1: a != b
    OR1K_COND_GTU,              // 0x2: a >  b (unsigned)
    OR1K_COND_GEU,              // 0x3: a >= b (unsigned)
    OR1K_COND_LTU,              // 0x4: a <  b (unsigned)
    OR1K_COND_LEU,              // 0x5: a <= b (unsigned)
    OR1K_COND_GTS,              // 0xa: a >  b (signed)
    OR1K_COND_GES,              // 0xb: a >= b (signed)
    OR1K_COND_LTS,              // 0xc: a <  b (signed)
    OR1K_COND_LES,              // 0xd: a <= b (signed)
    OR1K_COND_BAD,              // invalid condition
    OR1K_COND_LAST,             // for sizing
} or1kCondition;

//
// This type enumerates implemented condition codes
//
typedef enum or1kExtendE {
    OR1K_EXTEND_NA,             // no extension
    OR1K_EXTEND_S,              // sign extension
    OR1K_EXTEND_Z,              // zero extension
} or1kExtend;

//
// This structure is filled with information extracted from the decoded
// instruction
//
typedef struct or1kInstructionInfoS {
    const char         *opcode;         // opcode name
    const char         *format;         // disassembly format string
    or1kInstructionType type;           // instruction type
    Uns32               thisPC;         // instruction address
    Uns32               instruction;    // raw instruction
    Uns32               r1;             // register 1
    Uns32               r2;             // register 2
    Uns32               r3;             // register 3
    Uns32               c;              // constant value
    Uns32               bytes;          // load/store bytes (1, 2 or 4)
    or1kExtend          extend;         // load sign/zero extension
    or1kCondition       cond;           // condition
    Bool                iSuffix;        // does opcode require 'i' suffix?
} or1kInstructionInfo, *or1kInstructionInfoP;

//
// Decode the instruction at the passed address. The 'info' structure is filled
// with details of the instruction.
//
void or1kDecode(or1kP or1k, Uns32 thisPC, or1kInstructionInfoP info);

#endif

