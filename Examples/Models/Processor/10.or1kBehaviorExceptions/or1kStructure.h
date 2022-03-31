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

#ifndef OR1K_STRUCTURE_H
#define OR1K_STRUCTURE_H

// VMI header files
#include "vmi/vmiTypes.h"

// prefix string (for error messages)
#define CPU_PREFIX "OR1K"

#define OR1K_REGS 32            // basic OR1K registers
#define OR1K_BITS 32            // register size in bits
#define OR1K_LINK  9            // link register index (R9)

// processor structure
typedef struct or1kS {

    Bool       carryFlag;       // carry flag
    Bool       overflowFlag;    // overflow flag
    Bool       branchFlag;      // branch flag

    Uns32      regs[OR1K_REGS]; // basic registers

    Uns32      SR;              // status register
    Uns32      ESR;             // exception status register
    Uns32      EPC;             // exception program counter register
    Uns32      EEAR;            // exception effective address register

    vmiBusPortP busPorts;       // bus port descriptions

} or1k, *or1kP;

// macros to specify target registers in VARIABLE expressions
#define OR1K_CPU_REG(_F)        VMI_CPU_REG(or1kP, _F)
#define OR1K_REG(_R)            OR1K_CPU_REG(regs[_R])
#define OR1K_CARRY              OR1K_CPU_REG(carryFlag)
#define OR1K_OVERFLOW           OR1K_CPU_REG(overflowFlag)
#define OR1K_BRANCH             OR1K_CPU_REG(branchFlag)
#define OR1K_LINKREG            OR1K_REG(OR1K_LINK)
#define OR1K_ESR                OR1K_CPU_REG(ESR)
#define OR1K_EPC                OR1K_CPU_REG(EPC)
#define OR1K_EEAR               OR1K_CPU_REG(EEAR)

// macros to specify target registers in CONSTANT expressions
#define OR1K_CPU_REG_CONST(_F)  VMI_CPU_REG_CONST(or1kP, _F)
#define OR1K_REG_CONST(_R)      OR1K_CPU_REG_CONST(regs[_R])
#define OR1K_CARRY_CONST        OR1K_CPU_REG_CONST(carryFlag)
#define OR1K_OVERFLOW_CONST     OR1K_CPU_REG_CONST(overflowFlag)

// Bit definitions for the SR register
#define SPR_SR_CID      0xf0000000  // Context ID
#define SPR_SR_SUMRA    0x00010000  // Supervisor SPR read access
#define SPR_SR_FO       0x00008000  // Fixed one
#define SPR_SR_EPH      0x00004000  // Exception Prefix High
#define SPR_SR_DSX      0x00002000  // Delay Slot Exception
#define SPR_SR_OVE      0x00001000  // Overflow flag Exception
#define SPR_SR_OV       0x00000800  // Overflow flag
#define SPR_SR_CY       0x00000400  // Carry flag
#define SPR_SR_F        0x00000200  // Condition Flag
#define SPR_SR_CE       0x00000100  // CID Enable
#define SPR_SR_LEE      0x00000080  // Little Endian Enable
#define SPR_SR_IME      0x00000040  // Instruction MMU Enable
#define SPR_SR_DME      0x00000020  // Data MMU Enable
#define SPR_SR_ICE      0x00000010  // Instruction Cache Enable
#define SPR_SR_DCE      0x00000008  // Data Cache Enable
#define SPR_SR_IEE      0x00000004  // Interrupt Exception Enable
#define SPR_SR_TEE      0x00000002  // Tick timer Exception Enable
#define SPR_SR_SM       0x00000001  // Supervisor Mode

#endif

