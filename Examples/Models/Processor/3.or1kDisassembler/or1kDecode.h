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

    // arithmetic instructions
    OR1K_IT_ADDI,
    OR1K_IT_ADDIC,
    OR1K_IT_ANDI,
    OR1K_IT_ORI,
    OR1K_IT_XORI,
    OR1K_IT_MULI,

    // KEEP LAST: for sizing the array
    OR1K_IT_LAST

} or1kInstructionType;

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
    Uns32               c;              // constant value
} or1kInstructionInfo, *or1kInstructionInfoP;

//
// Decode the instruction at the passed address. The 'info' structure is filled
// with details of the instruction.
//
void or1kDecode(or1kP or1k, Uns32 thisPC, or1kInstructionInfoP info);

#endif

