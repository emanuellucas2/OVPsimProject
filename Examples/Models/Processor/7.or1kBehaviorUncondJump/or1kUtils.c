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
#include "vmi/vmiDbg.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kFunctions.h"
#include "or1kStructure.h"

//
// Set the value of a bit in a word
//
#define SET_BIT(_R, _C, _M) \
    if(_C) {                    \
        (_R) = (_R) | (_M);     \
    } else {                    \
        (_R) = (_R) & ~(_M);    \
    }

//
// Get the value of a bit in a word
//
#define GET_BIT(_R, _M) \
    (((_R) & (_M)) ? 1 : 0)

//
// Fill the full current value of the SR register, including bits normally
// maintained in separate flags fields
//
inline static void fillSR(or1kP or1k) {
    SET_BIT(or1k->SR, or1k->branchFlag,   SPR_SR_F);
    SET_BIT(or1k->SR, or1k->carryFlag,    SPR_SR_CY);
    SET_BIT(or1k->SR, or1k->overflowFlag, SPR_SR_OV);
}

//
// Return the current value of the SR register
//
Uns32 or1kGetSR(or1kP or1k) {
    fillSR(or1k);
    return or1k->SR;
}

//
// Set the current value of the SR register
//
void or1kSetSR(or1kP or1k, Uns32 value) {

    // it is never possible to clear the fixed-one (FO) bit
    value |= SPR_SR_FO;

    // set the SR
    or1k->SR = value;

    // set the current branch flag, carry flag and overflow flag from the SR
    or1k->branchFlag   = GET_BIT(value, SPR_SR_F);
    or1k->carryFlag    = GET_BIT(value, SPR_SR_CY);
    or1k->overflowFlag = GET_BIT(value, SPR_SR_OV);
}

//
// Dump OR1K registers
//
VMI_DEBUG_FN(or1kDumpRegisters) {
    
    or1kP or1k = (or1kP)processor;
    Uns32 i    = 0;

    vmiPrintf("--------------- --------------- --------------- ---------------\n");

    // print general-purpose registers
    while(i<OR1K_REGS) {
        vmiPrintf(" R%-2u: %08x", i, or1k->regs[i]);
        i++;
        if(!(i&3)) {
            vmiPrintf("\n");
        } else {
            vmiPrintf("  ");
        }
    }

    // newline if required before derived registers
    if(i&3) {
        vmiPrintf("\n");
    }

    // flags
    vmiPrintf(
        " BF:%u CF:%u OF:%u ",
        or1k->branchFlag,
        or1k->carryFlag,
        or1k->overflowFlag
    );

    // program counter
    vmiPrintf(" PC : %08x  ", (Uns32)vmirtGetPC(processor));

    // status register
    vmiPrintf(" SR : %08x  ", or1kGetSR(or1k));

    vmiPrintf("\n--------------- --------------- --------------- ---------------\n\n");
}

//
// This returns the endianness of the OR1K processor
//
VMI_ENDIAN_FN(or1kGetEndian) {
    return MEM_ENDIAN_BIG;
}

//
// Return the next instruction address after 'thisPC'.
//
VMI_NEXT_PC_FN(or1kNextInstruction) {
    Uns32 nextAddress = (Uns32)(thisPC + 4);
    return nextAddress;
}

