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


#ifndef M16C_STRUCTURE_H
#define M16C_STRUCTURE_H

// VMI header files
#include "vmi/vmiTypes.h"

// model header files
#include "m16cVariant.h"
#include "m16cTypeRefs.h"

// processor flags

#define M16C_CLI_DISASSEMBLE_MASK     0x00000001
#define M16C_CLI_DISASSEMBLE(_P)      ((_P)->flags & M16C_CLI_DISASSEMBLE_MASK)

#define M16C_ENDIAN MEM_ENDIAN_LITTLE

#define M16C_REGS  50            // basic m16c registers
#define BOOL_BITS  8

typedef enum m16cCompatE {
    COMPAT_ISA,                 // documented ISA
    COMPAT_GDB,                 // GDB compatability mode
    COMPAT_NOPBRK               // Ignore brk instruction
} m16cCompat;

// processor-specific net port list
typedef struct m16cNetPortS *m16cNetPortP, **m16cNetPortPP;

typedef enum m16cExceptionsS {
    m16c_E_Undefined,
    m16c_E_Overflow ,
    m16c_E_BRK      ,
    m16c_E_AdrMatch ,
    m16c_E_SStep    ,
    m16c_E_Wdt      ,
    m16c_E_DBC      ,
    m16c_E_NMI      ,
    m16c_E_Reset    ,
    m16c_E_Fetch    ,
} m16cException;

// decoder callback function to decode instruction at the passed address
#define M16C_DECODER_FN(_NAME) void _NAME( \
    m16cP                m16c,    \
    Uns32                thisPC,  \
    m16cInstructionInfoP info     \
)
typedef M16C_DECODER_FN((*m16cDecoderFn));

// processor structure
typedef struct m16cS {
    //
    // Processor Flags - part of FLG
    //
    Bool        carryFlag;
    Bool        debugFlag;
    Bool        zeroFlag;
    Bool        signFlag;
    Bool        regBankSelectFlag;
    Bool        overflowFlag;
    Bool        intEnableFlag;
    Bool        spSelectFlag;

    Bool        tempFlag;

    Uns8        intPriorityLevel;

    // Keep all registers in the same array(same indexing), as normal instructions may access both.
    Uns8       regs[M16C_REGS];        // Basic Registers

    //
    // Simulator support
    //
    Uns32       tempS;
    Uns32       tempD;
    Uns32       tempA;

    Uns32       flags;   // processor configuration flags
    Bool        verbose;
    m16cCompat  compat;
    m16cVariant variant;
    m16cDecoderFn decoderCB;            // generic instruction decoder
    m16cNetPortP netPorts;
    vmiBusPortP  busPorts;

    //
    // Internal State
    //
    Uns32 reset;                        // reset State
    Uns32 nmiPending;                   // nmi[0-2] State
    Uns32 nmiHandler;                   // nmi Handler Address
    Uns32 intpPending;                  // intp State
    Uns32 intpHandler;                  // intp Handler Address
    Uns32 intpLevel;                    // intp priority level
    Uns32 intack;                       // interrupt acknowledge
    // Uns32 mireti;                       // Maskable Interrupt RETI
    m16cException exception;            // remember last exception
} m16c;




#define M16C_REG_R0L    0  // 2  // Changed order of registers to allow for compound registers R2R0 and R3R1
#define M16C_REG_R0H    1  // 3
#define M16C_REG_R0     0  // 2
#define M16C_REG_R2     2  // 0
#define M16C_REG_R2R0   0
#define M16C_REG_R1L    4  // 6
#define M16C_REG_R1H    5  // 7
#define M16C_REG_R1     4  // 6
#define M16C_REG_R3     6  // 4
#define M16C_REG_R3R1   4
#define M16C_REG_A0     8
#define M16C_REG_A1     10
#define M16C_REG_A1A0   8
#define M16C_REG_FB     14
#define BANK0_LAST      M16C_REG_FB + 2

// Alternate bank of registers.  Instead of explicitly labeling bank1 and bank2, just have currently
// selected bank, and switch with alternate when FLG[U] changes.
#define M16C_REG_R0LB   BANK0_LAST + M16C_REG_R0L   // Changed order of registers to allow for compound registers R2R0 and R3R1
#define M16C_REG_R0HB   BANK0_LAST + M16C_REG_R0H
#define M16C_REG_R0B    BANK0_LAST + M16C_REG_R0
#define M16C_REG_R1LB   BANK0_LAST + M16C_REG_R1L
#define M16C_REG_R1HB   BANK0_LAST + M16C_REG_R1H
#define M16C_REG_R1B    BANK0_LAST + M16C_REG_R1
#define M16C_REG_R2B    BANK0_LAST + M16C_REG_R2
#define M16C_REG_R2R0B  BANK0_LAST + M16C_REG_R2R0
#define M16C_REG_R3B    BANK0_LAST + M16C_REG_R3
#define M16C_REG_R3R1B  BANK0_LAST + M16C_REG_R3R1
#define M16C_REG_A0B    BANK0_LAST + M16C_REG_A0
#define M16C_REG_A1B    BANK0_LAST + M16C_REG_A1
#define M16C_REG_A1A0B  BANK0_LAST + M16C_REG_A1A0
#define M16C_REG_FBB    BANK0_LAST + M16C_REG_FB


#define M16C_REG_USP    32
#define M16C_REG_ISP    36
#define M16C_REG_SP     36
#define M16C_REG_SB     40
#define M16C_REG_FLG    42
#define M16C_REG_INTBH  44
#define M16C_REG_INTBL  46
#define M16C_REG_INTB   46

#define M16C_REG_NONE   48


// macros to specify target registers in VARIABLE expressions
#define M16C_CPU_REG(_F)            VMI_CPU_REG(m16cP, _F)
#define M16C_CPU_TEMP(_F)           VMI_CPU_TEMP(m16cP, _F)
#define M16C_REG(_R)                M16C_CPU_REG(regs[_R])
#define M16C_TEMPS_REG              M16C_CPU_TEMP(tempS)
#define M16C_TEMPD_REG              M16C_CPU_TEMP(tempD)
#define M16C_TEMPA_REG              M16C_CPU_TEMP(tempA)
#define M16C_SP_REG                 (m16cP.spSelectFlag) ? M16C_REG(M16C_REG_USP) : M16C_REG(M16C_REG_ISP)


#define M16C_CARRYF_REG             M16C_CPU_REG(carryFlag)
#define M16C_DEBUGF_REG             M16C_CPU_REG(debugFlag)
#define M16C_ZEROF_REG              M16C_CPU_REG(zeroFlag)
#define M16C_SIGNF_REG              M16C_CPU_REG(signFlag)
#define M16C_REGBANKSELF_REG        M16C_CPU_REG(regBankSelectFlag)
#define M16C_OVERFLOWF_REG          M16C_CPU_REG(overflowFlag)
#define M16C_INTENABLE_REG          M16C_CPU_REG(intEnableFlag)
#define M16C_SPSELECTF_REG          M16C_CPU_REG(spSelectFlag)

#define M16C_IPL_REG                M16C_CPU_REG(intPriorityLevel)

#define M16C_TEMPF_REG              M16C_CPU_REG(tempFlag)



// macros to specify target registers in CONSTANT expressions
#define M16C_CPU_OFFSET(_F)     VMI_CPU_OFFSET(m16cP, _F)
#define M16C_CPU_REG_CONST(_F)  VMI_CPU_REG_CONST(m16cP, _F)
#define M16C_CPU_TEMP_CONST(_F) VMI_CPU_TEMP_CONST(m16cP, _F)
#define M16C_REG_CONST(_R)      M16C_CPU_REG_CONST(regs[_R])
#define M16C_CARRY_CONST        M16C_CPU_REG_CONST(carryFlag)
#define M16C_DEBUG_CONST        M16C_CPU_REG_CONST(debugFlag)
#define M16C_ZERO_CONST         M16C_CPU_REG_CONST(zeroFlag)
#define M16C_SIGN_CONST         M16C_CPU_REG_CONST(signFlag)
#define M16C_BANKSEL_CONST      M16C_CPU_REG_CONST(regBankSelectFlag)
#define M16C_OVERFLOW_CONST     M16C_CPU_REG_CONST(overflowFlag)
#define M16C_INTENABLE_CONST    M16C_CPU_REG_CONST(intEnableFlag)
#define M16C_SPSELECT_CONST     M16C_CPU_REG_CONST(spSelectFlag)

// Bit definitions for the FLG register
#define M16C_FLG_C              0x00000001  // carry Flag
#define M16C_FLG_D              0x00000002  // debug Flag
#define M16C_FLG_Z              0x00000004  // zero Flag
#define M16C_FLG_S              0x00000008  // sign Flag
#define M16C_FLG_B              0x00000010  // Bank select Flag
#define M16C_FLG_O              0x00000020  // overflow Flag
#define M16C_FLG_I              0x00000040  // IntEnable Flag
#define M16C_FLG_U              0x00000080  // SP select Flag

#define M16C_ADDRESS_MASK 0x000fffff

// Prefix string (for error messages)
#define CPU_PREFIX "M16C"

// MWH this might be the wrong endian!
// The intent is to read two 8bit registers as a 16bit
// At time of writing, code coverage of the use of this macro is ZERO
#define GET_REG16(_p,_i) ((_p->regs[_i]) | (_p->regs[_i+1] << 8))


#endif

