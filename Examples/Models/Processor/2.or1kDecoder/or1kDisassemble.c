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
#include "or1kFunctions.h"


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

    // default disassembly just shows instruction pattern
    sprintf(result, "??? instruction:0x%08x", info->instruction);

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

