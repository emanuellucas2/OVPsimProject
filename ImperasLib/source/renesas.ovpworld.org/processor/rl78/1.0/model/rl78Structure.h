/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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

#ifndef RL78_STRUCTURE_H
#define RL78_STRUCTURE_H

#include <stdio.h>

// VMI header files
#include "vmi/vmiTypes.h"

#include "rl78Exceptions.h"            // rl78Exception


#define RL78_REGS    32                // 8reg * 4bank


typedef enum rl78ModeE {
    RL78_MODE_RB0,
    RL78_MODE_RB1,
    RL78_MODE_RB2,
    RL78_MODE_RB3,
    RL78_MODE_LAST
} rl78kMode;

enum FlagUpdate {
    en_flag____ = 0x000,
    en_flag___C = 0x001,
    en_flag__AC = 0x011,
    en_flag_Z__ = 0x100,
    en_flag_Z_C = 0x101,
    en_flag_ZA_ = 0x110,
    en_flag_ZAC = 0x111,
};

typedef enum en_CondE {
    en_Cond_C,            // CY == 1
    en_Cond_NC,           // CY == 0
    en_Cond_Z,            // Z  == 1
    en_Cond_NZ,           // Z  == 0
    en_Cond_H,            // Z V CY == 0
    en_Cond_NH,           // Z V CY == 1
    en_Cond_T,            // bit == 1
    en_Cond_F,            // bit == 0
    en_Cond_TCLR          // bit == 1, then bit <- 0
} en_Cond;

// processor structure
typedef struct rl78S {

    Bool            PSW_IE;             // :7   interrupt enable            // 0
    Bool            PSW_Z;              // :6   zero                        // 1
    Uns8            PSW_RBS;            // :5,3 register bank select        // 2
    Bool            PSW_AC;             // :4   auxiliary carry                // 3
    Uns8            PSW_ISP;            // :2,1 inservice priority flag        // 4
    Bool            PSW_CY;             // :0   carry                        // 5
    Uns8            PSW;                // real : 8bit                        // 6
    Bool            BRANCH;             // tmp : branch condition            // 7
    struct {
        Uns16        low;               // tmp  : 16-bit offset                // 8
        Uns16        ES ;               // real : 8bit                        // 10
    } ES_Addr;

    struct {
        Uns16        low;               // tmp  : 16-bit offset                // 12
        Uns16        CS ;               // real : 8bit                        // 14
    } CS_Addr;

    Uns16            SP;                // real : 16bit                        // 16

    union {
        struct {
            Uns8    TMP_B0;             // tmp : 8bit                        // 20
            Uns8    TMP_B1;             // tmp : 8bit                        // 21
            Uns8    TMP_B2;             // tmp : 8bit                        // 22
            Uns8    TMP_B3;             // tmp : 8bit                        // 23
        };
        struct {
            Uns16    TMP_L;             // tmp : 16bit                        // 20
            Uns16    TMP_H;             // tmp : 16bit                        // 22
        };
        Uns32        TMP;               // tmp : 32bit                        // 20
    };
    Uns32            THL;               // tmp : [HL+B], [HL+C] addressing    // 24
    Uns32            TBIT;              // tmp : bit operation                // 28
    Uns32            SWAP;              // tmp : swap operation                // 32
    Uns32            T4BIT_RA;          // tmp : calculation for PSW.AC        // 36
    Uns32            T4BIT_RB;          // tmp : calculation for PSW.AC        // 40
    Uns32            T4BIT_RD;          // tmp : calculation for PSW.AC        // 44

    Uns8            regs[RL78_REGS];    // real : 8bit                        // 48

    Bool            TCMPS;              // tmp : CMPS instruction            // 80
    Uns32            PMC;               // processor mode control register    // 84
    Uns32            MACR;              // real : 32bit                        // 88
    Uns32            MEM;

    Uns32            reset;             // whether the processor is being reset        // Set when NET port received
    Uns32            irq_vect;          // pedding exception vector address            // Set when NET port received
    Uns32            irq_prio;          // pedding exception priority (PR0x, PR1x)    // Set when NET port received
    rl78Exception    exception;         // for rl78GetException()

    vmiBusPortP        busPorts;        // bus port descriptions
    Uns32            netAck;            // net handle
    vmiViewObjectP    exObject;         // view object for address exception info
    vmiViewEventP    addrExEvent;       // event generated on an address exception

    // Memory management
    memDomainP      dataDomain16;       // data domain for 16-bit address loads and stores

    // Parameters
    Bool            sim_ac_flag;
    Bool            exit_on_halt;
    Bool            verbose;
    Uns32            variant;
    Uns32            mirror_rom_addr;
    Uns32            mirror_start_addr;
    Uns32            mirror_end_addr;

    // Variables below are valid only in morph time.
    Uns32            len_instByte;
    Uns32            len_instMnem;
    Uns32            len_instPrefix;
    Uns32            len_instByteAndSkip;
    en_Cond         skipCondition;
    Uns32            bol_setTo4bit;
    enum FlagUpdate    flagUpdate;

} rl78, *rl78P;

// macros to specify target registers in VARIABLE expressions
#define RL78_OFFSET(_F)            VMI_CPU_REG(rl78P, _F)
#define RL78_REG(_R)               VMI_CPU_REG(rl78P, regs[_R])
#define RL78_IE                    VMI_CPU_REG(rl78P, PSW_IE)
#define RL78_ZERO                  VMI_CPU_REG(rl78P, PSW_Z)
#define RL78_RBS                   VMI_CPU_REG(rl78P, PSW_RBS)
#define RL78_AUXCARRY              VMI_CPU_REG(rl78P, PSW_AC)
#define RL78_ISP                   VMI_CPU_REG(rl78P, PSW_ISP)
#define RL78_CARRY                 VMI_CPU_REG(rl78P, PSW_CY)
#define RL78_ES_ADDR               VMI_CPU_TEMP(rl78P, ES_Addr)
#define RL78_ES                    VMI_CPU_REG(rl78P, ES_Addr.ES)
#define RL78_CS_ADDR               VMI_CPU_TEMP(rl78P, CS_Addr)
#define RL78_CS                    VMI_CPU_REG(rl78P, CS_Addr.CS)
#define RL78_SP                    VMI_CPU_REG(rl78P, SP)
#define RL78_PSW                   VMI_CPU_REG(rl78P, PSW)
#define RL78_PMC                   VMI_CPU_REG(rl78P, PMC)
#define RL78_MACR                  VMI_CPU_REG(rl78P, MACR)
#define RL78_TMP                   VMI_CPU_TEMP(rl78P, TMP)
#define RL78_TMP_L                 VMI_CPU_TEMP(rl78P, TMP_L)
#define RL78_TMP_H                 VMI_CPU_TEMP(rl78P, TMP_H)
#define RL78_TMP_B3                VMI_CPU_TEMP(rl78P, TMP_B3)
#define RL78_THL                   VMI_CPU_TEMP(rl78P, THL)
#define RL78_TBIT                  VMI_CPU_TEMP(rl78P, TBIT)
#define RL78_SWAP                  VMI_CPU_TEMP(rl78P, SWAP)
#define RL78_BRANCH                VMI_CPU_TEMP(rl78P, BRANCH)
#define    RL78_TCMPS              VMI_CPU_TEMP(rl78P, TCMPS)
#define    RL78_T4BIT_RA           VMI_CPU_TEMP(rl78P, T4BIT_RA)
#define    RL78_T4BIT_RB           VMI_CPU_TEMP(rl78P, T4BIT_RB)
#define    RL78_T4BIT_RD           VMI_CPU_TEMP(rl78P, T4BIT_RD)

// macros to specify target registers in CONSTANT expressions
#define RL78_OFFSET_CONST(_F)      VMI_CPU_REG_CONST(rl78P, _F)
#define RL78_REG_CONST(_R)         VMI_CPU_REG_CONST(rl78P, regs[_R])
#define RL78_ZERO_CONST            VMI_CPU_REG_CONST(rl78P, PSW_Z)
#define RL78_AUXCARRY_CONST        VMI_CPU_REG_CONST(rl78P, PSW_AC)
#define RL78_CARRY_CONST           VMI_CPU_REG_CONST(rl78P, PSW_CY)

// Bit definitions for the SR register
#define MASK_PSW_IE       0x00000080  // interrupt enable
#define MASK_PSW_Z        0x00000040  // zero
#define MASK_PSW_RBS1     0x00000020  // register bank select
#define MASK_PSW_AC       0x00000010  // auxiliary carry
#define MASK_PSW_RBS0     0x00000008  // register bank select
#define MASK_PSW_ISP1     0x00000004  // inservice priority flag
#define MASK_PSW_ISP0     0x00000002  // inservice priority flag
#define MASK_PSW_CY       0x00000001  // carry

// Serial number for general purpose registers
#define    R_X        0
#define    R_A        1
#define    R_C        2
#define    R_B        3
#define    R_E        4
#define    R_D        5
#define    R_L        6
#define    R_H        7

#define    R_AX       0
#define    R_BC       1
#define    R_DE       2
#define    R_HL       3

#define    R_BCAX     0
#define    R_HLDE     1

// Numbering for convenience
#define    R_ES     101        // ES : 8bit
#define    R_CS     102        // CS : 8bit
#define    R_PSW    103        // PSW: 8bit
#define    R_CY     104        // CY : 8bit
#define    R_SP     201        // SP : 16bit


// Prefix string (for error messages)
#define CPU_PREFIX "RL78"

#endif
