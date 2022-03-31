/*
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

#ifndef PPC32_STRUCTURE_H
#define PPC32_STRUCTURE_H

#include "vmi/vmiTypes.h"
#include "ppc32TypeRefs.h"
#include "ppc32Variant.h"
#include "ppc32Config.h"
#include "ppc32SPR.h"

#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))
#define PPC32_DISASSEMBLE_MASK 0x00000001
#define PPC32_DISASSEMBLE(_P) ((_P)->flags & PPC32_DISASSEMBLE_MASK)

// decoder callback function to decode instruction at the passed address
#define PPC32_DECODER_FN(_NAME) void _NAME ( \
    ppc32P ppc32, \
    Uns32 thisPC, \
    ppc32InstructionInfoP info \
)
typedef PPC32_DECODER_FN((*ppc32DecoderFn));

typedef enum ppc32ExceptionsS {
    ppc32_E_Reset    ,
    ppc32_E_Undefined,
    ppc32_E_Arith    ,
    ppc32_E_RdAlign  ,
    ppc32_E_WrAlign  ,
    ppc32_E_RdAbort  ,
    ppc32_E_WrAbort  ,
    ppc32_E_RdPriv   ,
    ppc32_E_WrPriv   ,
    ppc32_E_Fetch    ,
} ppc32Exception;

typedef enum ppc32VMModeE {
    VM_MODE_REAL         = 0,
    VM_MODE_REAL_PRIV    = VM_MODE_REAL,
    VM_MODE_REAL_USER,
    VM_MODE_REAL_HYPV,

    VM_MODE_FIRST_VIRTUAL,
    VM_MODE_VIRTUAL_PRIV_D = VM_MODE_FIRST_VIRTUAL,
    VM_MODE_VIRTUAL_PRIV_I,
    VM_MODE_VIRTUAL_PRIV_DI,

    VM_MODE_VIRTUAL_USER_D,
    VM_MODE_VIRTUAL_USER_I,
    VM_MODE_VIRTUAL_USER_DI,

    VM_MODE_VIRTUAL_HYPV_D,
    VM_MODE_VIRTUAL_HYPV_I,
    VM_MODE_VIRTUAL_HYPV_DI,

    VM_MODE_LAST_VIRTUAL = VM_MODE_VIRTUAL_HYPV_DI,
    VM_MODE_LAST
} ppc32VMMode;

// this enumeration specifies modes enabling instruction subsets
typedef enum ppc32BlockMask {
    BM_NONE     = 0x0000,      // no requirement
    BM_FP_AVAIL = 0x0001,      // requires enabled floating point unit
} ppc32BlockMask;

//
// Enum to indicate the type of FPU operation for checks in
//
typedef struct ppc32NetPortS *ppc32NetPortP, **ppc32NetPortPP;

typedef union {
    Uns32 reg;
    struct {
        Uns32        CR7 : 4;   // LT, GT, EQ, SO
        Uns32        CR6 : 4;   // LT, GT, EQ, SO
        Uns32        CR5 : 4;   // LT, GT, EQ, SO
        Uns32        CR4 : 4;   // LT, GT, EQ, SO
        Uns32        CR3 : 4;   // LT, GT, EQ, SO
        Uns32        CR2 : 4;   // LT, GT, EQ, SO
        Uns32        CR1 : 4;   // LT, GT, EQ, SO
        Uns32        CR0 : 4;   // LT, GT, EQ, SO
    } bits;
} TYPE_CR;

typedef union {
    Uns32 reg;
    struct {
        Uns32         RN : 2;
        Uns32         NI : 1;   // None-ieee mode, RESERVED
        Uns32         XE : 1;

        Uns32         ZE : 1;
        Uns32         UE : 1;
        Uns32         OE : 1;
        Uns32         VE : 1;

        Uns32      VXCVI : 1;   // Sticky flags
        Uns32     VXSQRT : 1;   // Sticky flags
        Uns32     VXSOFT : 1;   // Sticky flags
        Uns32       RSV1 : 1;

        Uns32         FU : 1;   // NaN     ->FLG_FP_FU
        Uns32         FE : 1;   // EQ-ZERO ->FLG_FP_FE
        Uns32         FG : 1;   // GT-ZERO ->FLG_FP_FG
        Uns32         FL : 1;   // LT-ZERO ->FLG_FP_FL

        Uns32          C : 1;   // FPCC    ->FLG_FP_C
        Uns32         FI : 1;   // Inexact during rounding, or disabled overflow
        Uns32         FR : 1;
        Uns32       VXVC : 1;   // Sticky flags

        Uns32      VXIMZ : 1;   // Sticky flags
        Uns32      VXZDZ : 1;   // Sticky flags
        Uns32      VXIDI : 1;   // Sticky flags
        Uns32      VXISI : 1;   // Sticky flags

        Uns32     VXSNAN : 1;   // Sticky flags
        Uns32         XX : 1;   // Sticky flags (FI)
        Uns32         ZX : 1;   // Sticky flags
        Uns32         UX : 1;   // Sticky flags

        Uns32         OX : 1;   // Sticky flags
        Uns32         VX : 1;
        Uns32        FEX : 1;
        Uns32         FX : 1;
    } bits;
} TYPE_FPSCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       FRMC : 2;
        Uns32      FOVFE : 1;
        Uns32      FUNFE : 1;
        Uns32      FDBZE : 1;
        Uns32      FINVE : 1;
        Uns32      FINXE : 1;
        Uns32       RSV2 : 1;
        Uns32       FOVF : 1;
        Uns32       FUNF : 1;
        Uns32       FDBZ : 1;
        Uns32       FINV : 1;
        Uns32         FX : 1;
        Uns32         FG : 1;
        Uns32         SO : 1;
        Uns32        SOV : 1;
        Uns32       RSV1 : 1;
        Uns32      FOVFS : 1;
        Uns32      FUNFS : 1;
        Uns32      FDBZS : 1;
        Uns32      FINVS : 1;
        Uns32      FINXS : 1;
        Uns32       RSV0 : 2;
        Uns32      FOVFH : 1;
        Uns32      FUNFH : 1;
        Uns32      FDBZH : 1;
        Uns32      FINVH : 1;
        Uns32        FXH : 1;
        Uns32        FGH : 1;
        Uns32        OVH : 1;
        Uns32       SOVH : 1;
    } bits;
} TYPE_SPEFSCR;

typedef union {
    Uns64 reg;
    struct {
        Uns64      BYTES : 7;
        Uns64       RSV1 : 22;
        Uns64         CA : 1;
        Uns64         OV : 1;
        Uns64         SO : 1;
        Uns64       RSV0 : 32;
    } bits;
} TYPE_XER;

typedef struct ppc32sprS *ppc32sprP;

typedef struct ppc32S {
    //
    // User Defined and Builtin Registers
    //
    Uns32 GPR[32];
    Uns64 FPR[32];
    Uns64 VR[32];
    TYPE_CR           CR,      CR_rmask,      CR_wmask;
    TYPE_FPSCR     FPSCR,   FPSCR_rmask,   FPSCR_wmask;
    TYPE_SPEFSCR SPEFSCR, SPEFSCR_rmask, SPEFSCR_wmask;
    TYPE_XER         XER,     XER_rmask,     XER_wmask;
    Uns64 LR;
    Uns64 CTR;

    Uns8  XER_SO;
    Uns8  XER_OV;
    Uns8  XER_CA;
    Uns8  LT[8];
    Uns8  GT[8];
    Uns8  EQ[8];
    Uns8  SO[8];
    Uns32 TEMP[4];

    //
    // Exception holding register
    //
    Uns64 except;

    //
    // SPR Structure and Delta offset
    //
    ppc32sprP SPR;
    UnsPS     SPRdelta;

    Uns64 RESERVE_ADDR;
    Uns8  RESERVE_LENGTH;
    Uns8  RESERVE;

    //
    // Integer OPS flags
    //
    Bool  FLG_CI;
    Bool  FLG_CO;
    Bool  FLG_PA;
    Bool  FLG_ZR;
    Bool  FLG_SI;
    Bool  FLG_OV;

    Bool  FLG_TEMP;

    //
    // FLoating point Flags
    //
    Uns64 FPU_TEMP[4];                  // Last FPU Arguments for future Flag Reference
    Uns64 FPU_RES;                      // Last FPU calculated result for future Flag Reference
    Uns32 FPU_OP;                       // BINOP(8), OP(8)
    // Flags Relation
    // UNORDERED=0x1, EQ=0x2, LT=0x4 GT=0x8
    Uns8  FPU_REL, FPU_REL_GEN;         // FPU_REL and flag to indicate when to generate
    Uns8  QNAN_FLG;                     // Flag to indicate QNAN handler called
    Uns8  TEMP_REL; // only used for comparison ops - not saved to FPSCR
    // Flags FPU Operations
    // P, U, O, Z, D, I
    Uns8  FPU_FLG, FPU_FLG_STICKY;
    Uns8  CMP_FLG;
    Uns8  CNV32_FLG, CNV32_REL, CNV64_FLG;
    // Flags additional
    Uns8  FLG_FP_SI;
    // Other Sticky flags
    Uns8  FLG_FPSCR_VXCVI;
    Uns8  FLG_FPSCR_VXSQRT;
    Uns8  FLG_FPSCR_VXSOFT;
    Uns8  FLG_FPSCR_VXVC;
    Uns8  FLG_FPSCR_VXIMZ;
    Uns8  FLG_FPSCR_VXZDZ;
    Uns8  FLG_FPSCR_VXIDI;
    Uns8  FLG_FPSCR_VXISI;
    Uns8  FLG_FPSCR_VXSNAN;

    //
    // Flags to help with Load/Store alignment checks
    //
    Bool  FLG_FP_LDST;
    Bool  FLG_ST;

    //
    // Model Support Registers
    //
    Uns32 flags;
    ppc32Config configInfo;
    Bool verbose;
    memEndian dendian;
    memEndian iendian;
    ppc32Exception exception;
    ppc32BlockMask blockMask;

    struct {
        Bool UISA_I_B;
        Bool UISA_I_BCDA;
        Bool UISA_I_S;
        Bool UISA_I_E;
        Bool UISA_I_E_PC;
        Bool UISA_I_E_PD;
        Bool UISA_I_EC;
        Bool UISA_I_FP;
        Bool UISA_I_DFP;
        Bool UISA_I_MA;
        Bool UISA_I_SP;
        Bool UISA_I_V;
        Bool UISA_I_LMA;
        Bool UISA_I_WT;
        Bool UISA_I_VLE;
        Bool ENABLE_FPU;
        Bool UNIMP_TO_NOP;
        Bool WARN_NOP;
    } params;

    // Bus ports
    vmiBusPortP busPorts;

    // Net ports
    ppc32NetPortP netPorts;

    // generic instruction decoder
    ppc32DecoderFn decoder;

} ppc32;

#define PPC32_FLAG_BITS (sizeof(Uns8) * 8)

#define PPC32_CPU_OFFSET(_F) VMI_CPU_OFFSET(ppc32P, _F)
#define PPC32_CPU_REG(_F) VMI_CPU_REG(ppc32P, _F)
#define PPC32_TEMP_REG(_F) VMI_CPU_TEMP(ppc32P, _F)

#define PPC32_SPR_REG(_P, _F) VMI_CPU_REG_DELTA(ppc32sprP, _F, _P->SPRdelta)

#define PPC32_GPR_BITS (sizeof(Uns32) * 8)
#define PPC32_GPR_RD(_R) PPC32_CPU_REG(GPR[_R])
#define PPC32_GPR_WR(_R) PPC32_CPU_REG(GPR[_R])

#define PPC32_FPR_BITS (sizeof(Uns64) * 8)
#define PPC32_FPR_RD(_R)   PPC32_CPU_REG(FPR[_R])
#define PPC32_FPR_WR(_R)   PPC32_CPU_REG(FPR[_R])
#define PPC32_FPU_RES      PPC32_CPU_REG(FPU_RES)
#define PPC32_FPU_TEMP(_R) PPC32_CPU_REG(FPU_TEMP[_R])

#define PPC32_VR_BITS (sizeof(Uns64) * 8)
#define PPC32_VR_RD(_R) PPC32_CPU_REG(VR[_R])
#define PPC32_VR_WR(_R) PPC32_CPU_REG(VR[_R])

#define PPC32_CR_BITS (sizeof(Uns32) * 8)
#define PPC32_CR_RD PPC32_CPU_REG(CR)
#define PPC32_CR_WR PPC32_CPU_REG(CR)

#define PPC32_XER_BITS (sizeof(Uns64) * 8)
#define PPC32_XER_RD PPC32_CPU_REG(XER)
#define PPC32_XER_WR PPC32_CPU_REG(XER)
#define PPC32_XER_SO_BITS (sizeof(Uns8) * 8)
#define PPC32_XER_SO_RD PPC32_CPU_REG(XER_SO)
#define PPC32_XER_SO_WR PPC32_CPU_REG(XER_SO)
#define PPC32_XER_OV_BITS (sizeof(Uns8) * 8)
#define PPC32_XER_OV_RD PPC32_CPU_REG(XER_OV)
#define PPC32_XER_OV_WR PPC32_CPU_REG(XER_OV)
#define PPC32_XER_CA_BITS (sizeof(Uns8) * 8)
#define PPC32_XER_CA_RD PPC32_CPU_REG(XER_CA)
#define PPC32_XER_CA_WR PPC32_CPU_REG(XER_CA)

#define PPC32_LT_BITS (sizeof(Uns8) * 8)
#define PPC32_LT_RD(_R) PPC32_CPU_REG(LT[_R])
#define PPC32_LT_WR(_R) PPC32_CPU_REG(LT[_R])

#define PPC32_GT_BITS (sizeof(Uns8) * 8)
#define PPC32_GT_RD(_R) PPC32_CPU_REG(GT[_R])
#define PPC32_GT_WR(_R) PPC32_CPU_REG(GT[_R])

#define PPC32_EQ_BITS (sizeof(Uns8) * 8)
#define PPC32_EQ_RD(_R) PPC32_CPU_REG(EQ[_R])
#define PPC32_EQ_WR(_R) PPC32_CPU_REG(EQ[_R])

#define PPC32_SO_BITS (sizeof(Uns8) * 8)
#define PPC32_SO_RD(_R) PPC32_CPU_REG(SO[_R])
#define PPC32_SO_WR(_R) PPC32_CPU_REG(SO[_R])

#define PPC32_TEMP_BITS (sizeof(Uns32) * 8)
#define PPC32_TEMP(_R) PPC32_TEMP_REG(TEMP[_R])

#define PPC32_LR_BITS (sizeof(Uns64) * 8)
#define PPC32_LR_RD PPC32_CPU_REG(LR)
#define PPC32_LR_WR PPC32_CPU_REG(LR)

#define PPC32_CTR_BITS (sizeof(Uns64) * 8)
#define PPC32_CTR_RD PPC32_CPU_REG(CTR)
#define PPC32_CTR_WR PPC32_CPU_REG(CTR)

#define PPC32_DSCR_BITS (sizeof(Uns64) * 8)
#define PPC32_DSCR_RD PPC32_CPU_REG(DSCR)
#define PPC32_DSCR_WR PPC32_CPU_REG(DSCR)

#define PPC32_DSISR_BITS (sizeof(Uns32) * 8)
#define PPC32_DSISR_RD PPC32_CPU_REG(DSISR)
#define PPC32_DSISR_WR PPC32_CPU_REG(DSISR)

#define PPC32_DAR_BITS (sizeof(Uns64) * 8)
#define PPC32_DAR_RD PPC32_CPU_REG(DAR)
#define PPC32_DAR_WR PPC32_CPU_REG(DAR)

#define PPC32_DEC_BITS (sizeof(Uns32) * 8)
#define PPC32_DEC_RD PPC32_CPU_REG(DEC)
#define PPC32_DEC_WR PPC32_CPU_REG(DEC)

#define PPC32_DEC_TMR_BITS (sizeof(Uns64) * 8)
#define PPC32_DEC_TMR_RD PPC32_CPU_REG(DEC_tmr)
#define PPC32_DEC_TMR_WR PPC32_CPU_REG(DEC_tmr)

#define PPC32_SDR1_BITS (sizeof(Uns64) * 8)
#define PPC32_SDR1_RD PPC32_CPU_REG(SDR1)
#define PPC32_SDR1_WR PPC32_CPU_REG(SDR1)

#define PPC32_SRR0_BITS (sizeof(Uns64) * 8)
#define PPC32_SRR0_RD PPC32_CPU_REG(SRR0)
#define PPC32_SRR0_WR PPC32_CPU_REG(SRR0)

#define PPC32_SRR1_BITS (sizeof(Uns64) * 8)
#define PPC32_SRR1_RD PPC32_CPU_REG(SRR1)
#define PPC32_SRR1_WR PPC32_CPU_REG(SRR1)

#define PPC32_CFAR_BITS (sizeof(Uns64) * 8)
#define PPC32_CFAR_RD PPC32_CPU_REG(CFAR)
#define PPC32_CFAR_WR PPC32_CPU_REG(CFAR)

#define PPC32_AMR_BITS (sizeof(Uns64) * 8)
#define PPC32_AMR_RD PPC32_CPU_REG(AMR)
#define PPC32_AMR_WR PPC32_CPU_REG(AMR)

#define PPC32_PID0_BITS (sizeof(Uns32) * 8)
#define PPC32_PID0_RD PPC32_CPU_REG(PID0)
#define PPC32_PID0_WR PPC32_CPU_REG(PID0)

#define PPC32_DECAR_BITS (sizeof(Uns32) * 8)
#define PPC32_DECAR_RD PPC32_CPU_REG(DECAR)
#define PPC32_DECAR_WR PPC32_CPU_REG(DECAR)

#define PPC32_CSRR0_BITS (sizeof(Uns64) * 8)
#define PPC32_CSRR0_RD PPC32_CPU_REG(CSRR0)
#define PPC32_CSRR0_WR PPC32_CPU_REG(CSRR0)

#define PPC32_CSRR1_BITS (sizeof(Uns32) * 8)
#define PPC32_CSRR1_RD PPC32_CPU_REG(CSRR1)
#define PPC32_CSRR1_WR PPC32_CPU_REG(CSRR1)

#define PPC32_DEAR_BITS (sizeof(Uns64) * 8)
#define PPC32_DEAR_RD PPC32_CPU_REG(DEAR)
#define PPC32_DEAR_WR PPC32_CPU_REG(DEAR)

#define PPC32_ESR_BITS (sizeof(Uns32) * 8)
#define PPC32_ESR_RD PPC32_CPU_REG(ESR)
#define PPC32_ESR_WR PPC32_CPU_REG(ESR)

#define PPC32_IVPR_BITS (sizeof(Uns64) * 8)
#define PPC32_IVPR_RD PPC32_CPU_REG(IVPR)
#define PPC32_IVPR_WR PPC32_CPU_REG(IVPR)

#define PPC32_CTRL_BITS (sizeof(Uns32) * 8)
#define PPC32_CTRL_RD PPC32_CPU_REG(CTRL)
#define PPC32_CTRL_WR PPC32_CPU_REG(CTRL)

#define PPC32_VRSAVE_BITS (sizeof(Uns32) * 8)
#define PPC32_VRSAVE_RD PPC32_CPU_REG(VRSAVE)
#define PPC32_VRSAVE_WR PPC32_CPU_REG(VRSAVE)

#define PPC32_SPRG0_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG0_RD PPC32_CPU_REG(SPRG0)
#define PPC32_SPRG0_WR PPC32_CPU_REG(SPRG0)

#define PPC32_SPRG1_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG1_RD PPC32_CPU_REG(SPRG1)
#define PPC32_SPRG1_WR PPC32_CPU_REG(SPRG1)

#define PPC32_SPRG2_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG2_RD PPC32_CPU_REG(SPRG2)
#define PPC32_SPRG2_WR PPC32_CPU_REG(SPRG2)

#define PPC32_SPRG3_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG3_RD PPC32_CPU_REG(SPRG3)
#define PPC32_SPRG3_WR PPC32_CPU_REG(SPRG3)

#define PPC32_SPRG4_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG4_RD PPC32_CPU_REG(SPRG4)
#define PPC32_SPRG4_WR PPC32_CPU_REG(SPRG4)

#define PPC32_SPRG5_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG5_RD PPC32_CPU_REG(SPRG5)
#define PPC32_SPRG5_WR PPC32_CPU_REG(SPRG5)

#define PPC32_SPRG6_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG6_RD PPC32_CPU_REG(SPRG6)
#define PPC32_SPRG6_WR PPC32_CPU_REG(SPRG6)

#define PPC32_SPRG7_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG7_RD PPC32_CPU_REG(SPRG7)
#define PPC32_SPRG7_WR PPC32_CPU_REG(SPRG7)

#define PPC32_TB_BITS (sizeof(Uns64) * 8)
#define PPC32_TB_RD PPC32_CPU_REG(TB)
#define PPC32_TB_WR PPC32_CPU_REG(TB)

#define PPC32_TBU_BITS (sizeof(Uns64) * 8)
#define PPC32_TBU_RD PPC32_CPU_REG(TBU)
#define PPC32_TBU_WR PPC32_CPU_REG(TBU)

#define PPC32_EAR_BITS (sizeof(Uns32) * 8)
#define PPC32_EAR_RD PPC32_CPU_REG(EAR)
#define PPC32_EAR_WR PPC32_CPU_REG(EAR)

#define PPC32_PIR_BITS (sizeof(Uns32) * 8)
#define PPC32_PIR_RD PPC32_CPU_REG(PIR)
#define PPC32_PIR_WR PPC32_CPU_REG(PIR)

#define PPC32_PVR_BITS (sizeof(Uns32) * 8)
#define PPC32_PVR_RD PPC32_CPU_REG(PVR)
#define PPC32_PVR_WR PPC32_CPU_REG(PVR)

#define PPC32_HSPRG_BITS (sizeof(Uns64) * 8)
#define PPC32_HSPRG_RD(_R) PPC32_CPU_REG(HSPRG[_R])
#define PPC32_HSPRG_WR(_R) PPC32_CPU_REG(HSPRG[_R])

#define PPC32_DBSR_BITS (sizeof(Uns32) * 8)
#define PPC32_DBSR_RD PPC32_CPU_REG(DBSR)
#define PPC32_DBSR_WR PPC32_CPU_REG(DBSR)

#define PPC32_HDSISR_BITS (sizeof(Uns32) * 8)
#define PPC32_HDSISR_RD PPC32_CPU_REG(HDSISR)
#define PPC32_HDSISR_WR PPC32_CPU_REG(HDSISR)

#define PPC32_HDAR_BITS (sizeof(Uns64) * 8)
#define PPC32_HDAR_RD PPC32_CPU_REG(HDAR)
#define PPC32_HDAR_WR PPC32_CPU_REG(HDAR)

#define PPC32_DBCR0_BITS (sizeof(Uns32) * 8)
#define PPC32_DBCR0_RD PPC32_CPU_REG(DBCR0)
#define PPC32_DBCR0_WR PPC32_CPU_REG(DBCR0)

#define PPC32_SPURR_BITS (sizeof(Uns64) * 8)
#define PPC32_SPURR_RD PPC32_CPU_REG(SPURR)
#define PPC32_SPURR_WR PPC32_CPU_REG(SPURR)

#define PPC32_PURR_BITS (sizeof(Uns64) * 8)
#define PPC32_PURR_RD PPC32_CPU_REG(PURR)
#define PPC32_PURR_WR PPC32_CPU_REG(PURR)

#define PPC32_DBCR1_BITS (sizeof(Uns32) * 8)
#define PPC32_DBCR1_RD PPC32_CPU_REG(DBCR1)
#define PPC32_DBCR1_WR PPC32_CPU_REG(DBCR1)

#define PPC32_HDEC_BITS (sizeof(Uns32) * 8)
#define PPC32_HDEC_RD PPC32_CPU_REG(HDEC)
#define PPC32_HDEC_WR PPC32_CPU_REG(HDEC)

#define PPC32_DBCR2_BITS (sizeof(Uns32) * 8)
#define PPC32_DBCR2_RD PPC32_CPU_REG(DBCR2)
#define PPC32_DBCR2_WR PPC32_CPU_REG(DBCR2)

#define PPC32_RMOR_BITS (sizeof(Uns64) * 8)
#define PPC32_RMOR_RD PPC32_CPU_REG(RMOR)
#define PPC32_RMOR_WR PPC32_CPU_REG(RMOR)

#define PPC32_IAC1_BITS (sizeof(Uns64) * 8)
#define PPC32_IAC1_RD PPC32_CPU_REG(IAC1)
#define PPC32_IAC1_WR PPC32_CPU_REG(IAC1)

#define PPC32_IAC2_BITS (sizeof(Uns64) * 8)
#define PPC32_IAC2_RD PPC32_CPU_REG(IAC2)
#define PPC32_IAC2_WR PPC32_CPU_REG(IAC2)

#define PPC32_IAC3_BITS (sizeof(Uns64) * 8)
#define PPC32_IAC3_RD PPC32_CPU_REG(IAC3)
#define PPC32_IAC3_WR PPC32_CPU_REG(IAC3)

#define PPC32_IAC4_BITS (sizeof(Uns64) * 8)
#define PPC32_IAC4_RD PPC32_CPU_REG(IAC4)
#define PPC32_IAC4_WR PPC32_CPU_REG(IAC4)

#define PPC32_HRMOR_BITS (sizeof(Uns64) * 8)
#define PPC32_HRMOR_RD PPC32_CPU_REG(HRMOR)
#define PPC32_HRMOR_WR PPC32_CPU_REG(HRMOR)

#define PPC32_HSRR0_BITS (sizeof(Uns64) * 8)
#define PPC32_HSRR0_RD PPC32_CPU_REG(HSRR0)
#define PPC32_HSRR0_WR PPC32_CPU_REG(HSRR0)

#define PPC32_HSRR1_BITS (sizeof(Uns64) * 8)
#define PPC32_HSRR1_RD PPC32_CPU_REG(HSRR1)
#define PPC32_HSRR1_WR PPC32_CPU_REG(HSRR1)

#define PPC32_DAC1_BITS (sizeof(Uns64) * 8)
#define PPC32_DAC1_RD PPC32_CPU_REG(DAC1)
#define PPC32_DAC1_WR PPC32_CPU_REG(DAC1)

#define PPC32_DAC2_BITS (sizeof(Uns64) * 8)
#define PPC32_DAC2_RD PPC32_CPU_REG(DAC2)
#define PPC32_DAC2_WR PPC32_CPU_REG(DAC2)

#define PPC32_LPCR_BITS (sizeof(Uns64) * 8)
#define PPC32_LPCR_RD PPC32_CPU_REG(LPCR)
#define PPC32_LPCR_WR PPC32_CPU_REG(LPCR)

#define PPC32_DVC1_BITS (sizeof(Uns64) * 8)
#define PPC32_DVC1_RD PPC32_CPU_REG(DVC1)
#define PPC32_DVC1_WR PPC32_CPU_REG(DVC1)

#define PPC32_DVC2_BITS (sizeof(Uns64) * 8)
#define PPC32_DVC2_RD PPC32_CPU_REG(DVC2)
#define PPC32_DVC2_WR PPC32_CPU_REG(DVC2)

#define PPC32_LPIDR_BITS (sizeof(Uns32) * 8)
#define PPC32_LPIDR_RD PPC32_CPU_REG(LPIDR)
#define PPC32_LPIDR_WR PPC32_CPU_REG(LPIDR)

#define PPC32_TSR_BITS (sizeof(Uns32) * 8)
#define PPC32_TSR_RD PPC32_CPU_REG(TSR)
#define PPC32_TSR_WR PPC32_CPU_REG(TSR)

#define PPC32_HMER_BITS (sizeof(Uns64) * 8)
#define PPC32_HMER_RD PPC32_CPU_REG(HMER)
#define PPC32_HMER_WR PPC32_CPU_REG(HMER)

#define PPC32_HMEER_BITS (sizeof(Uns64) * 8)
#define PPC32_HMEER_RD PPC32_CPU_REG(HMEER)
#define PPC32_HMEER_WR PPC32_CPU_REG(HMEER)

#define PPC32_PCR_BITS (sizeof(Uns64) * 8)
#define PPC32_PCR_RD PPC32_CPU_REG(PCR)
#define PPC32_PCR_WR PPC32_CPU_REG(PCR)

#define PPC32_HEIR_BITS (sizeof(Uns32) * 8)
#define PPC32_HEIR_RD PPC32_CPU_REG(HEIR)
#define PPC32_HEIR_WR PPC32_CPU_REG(HEIR)

#define PPC32_TCR_BITS (sizeof(Uns32) * 8)
#define PPC32_TCR_RD PPC32_CPU_REG(TCR)
#define PPC32_TCR_WR PPC32_CPU_REG(TCR)

#define PPC32_IVOR0_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR0_RD PPC32_CPU_REG(IVOR0)
#define PPC32_IVOR0_WR PPC32_CPU_REG(IVOR0)

#define PPC32_IVOR1_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR1_RD PPC32_CPU_REG(IVOR1)
#define PPC32_IVOR1_WR PPC32_CPU_REG(IVOR1)

#define PPC32_IVOR2_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR2_RD PPC32_CPU_REG(IVOR2)
#define PPC32_IVOR2_WR PPC32_CPU_REG(IVOR2)

#define PPC32_IVOR3_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR3_RD PPC32_CPU_REG(IVOR3)
#define PPC32_IVOR3_WR PPC32_CPU_REG(IVOR3)

#define PPC32_IVOR4_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR4_RD PPC32_CPU_REG(IVOR4)
#define PPC32_IVOR4_WR PPC32_CPU_REG(IVOR4)

#define PPC32_IVOR5_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR5_RD PPC32_CPU_REG(IVOR5)
#define PPC32_IVOR5_WR PPC32_CPU_REG(IVOR5)

#define PPC32_IVOR6_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR6_RD PPC32_CPU_REG(IVOR6)
#define PPC32_IVOR6_WR PPC32_CPU_REG(IVOR6)

#define PPC32_IVOR7_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR7_RD PPC32_CPU_REG(IVOR7)
#define PPC32_IVOR7_WR PPC32_CPU_REG(IVOR7)

#define PPC32_IVOR8_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR8_RD PPC32_CPU_REG(IVOR8)
#define PPC32_IVOR8_WR PPC32_CPU_REG(IVOR8)

#define PPC32_IVOR9_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR9_RD PPC32_CPU_REG(IVOR9)
#define PPC32_IVOR9_WR PPC32_CPU_REG(IVOR9)

#define PPC32_IVOR10_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR10_RD PPC32_CPU_REG(IVOR10)
#define PPC32_IVOR10_WR PPC32_CPU_REG(IVOR10)

#define PPC32_IVOR11_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR11_RD PPC32_CPU_REG(IVOR11)
#define PPC32_IVOR11_WR PPC32_CPU_REG(IVOR11)

#define PPC32_IVOR12_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR12_RD PPC32_CPU_REG(IVOR12)
#define PPC32_IVOR12_WR PPC32_CPU_REG(IVOR12)

#define PPC32_IVOR13_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR13_RD PPC32_CPU_REG(IVOR13)
#define PPC32_IVOR13_WR PPC32_CPU_REG(IVOR13)

#define PPC32_IVOR14_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR14_RD PPC32_CPU_REG(IVOR14)
#define PPC32_IVOR14_WR PPC32_CPU_REG(IVOR14)

#define PPC32_IVOR15_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR15_RD PPC32_CPU_REG(IVOR15)
#define PPC32_IVOR15_WR PPC32_CPU_REG(IVOR15)

#define PPC32_SPEFSCR_BITS (sizeof(Uns32) * 8)
#define PPC32_SPEFSCR_RD PPC32_CPU_REG(SPEFSCR)
#define PPC32_SPEFSCR_WR PPC32_CPU_REG(SPEFSCR)

#define PPC32_ATB_BITS (sizeof(Uns64) * 8)
#define PPC32_ATB_RD PPC32_CPU_REG(ATB)
#define PPC32_ATB_WR PPC32_CPU_REG(ATB)

#define PPC32_IVOR32_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR32_RD PPC32_CPU_REG(IVOR32)
#define PPC32_IVOR32_WR PPC32_CPU_REG(IVOR32)

#define PPC32_IVOR33_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR33_RD PPC32_CPU_REG(IVOR33)
#define PPC32_IVOR33_WR PPC32_CPU_REG(IVOR33)

#define PPC32_IVOR34_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR34_RD PPC32_CPU_REG(IVOR34)
#define PPC32_IVOR34_WR PPC32_CPU_REG(IVOR34)

#define PPC32_IVOR35_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR35_RD PPC32_CPU_REG(IVOR35)
#define PPC32_IVOR35_WR PPC32_CPU_REG(IVOR35)

#define PPC32_IVOR36_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR36_RD PPC32_CPU_REG(IVOR36)
#define PPC32_IVOR36_WR PPC32_CPU_REG(IVOR36)

#define PPC32_IVOR37_BITS (sizeof(Uns32) * 8)
#define PPC32_IVOR37_RD PPC32_CPU_REG(IVOR37)
#define PPC32_IVOR37_WR PPC32_CPU_REG(IVOR37)

#define PPC32_MCSRR0_BITS (sizeof(Uns64) * 8)
#define PPC32_MCSRR0_RD PPC32_CPU_REG(MCSRR0)
#define PPC32_MCSRR0_WR PPC32_CPU_REG(MCSRR0)

#define PPC32_MCSRR1_BITS (sizeof(Uns32) * 8)
#define PPC32_MCSRR1_RD PPC32_CPU_REG(MCSRR1)
#define PPC32_MCSRR1_WR PPC32_CPU_REG(MCSRR1)

#define PPC32_MCSR_BITS (sizeof(Uns64) * 8)
#define PPC32_MCSR_RD PPC32_CPU_REG(MCSR)
#define PPC32_MCSR_WR PPC32_CPU_REG(MCSR)

#define PPC32_DSRR0_BITS (sizeof(Uns64) * 8)
#define PPC32_DSRR0_RD PPC32_CPU_REG(DSRR0)
#define PPC32_DSRR0_WR PPC32_CPU_REG(DSRR0)

#define PPC32_DSRR1_BITS (sizeof(Uns32) * 8)
#define PPC32_DSRR1_RD PPC32_CPU_REG(DSRR1)
#define PPC32_DSRR1_WR PPC32_CPU_REG(DSRR1)

#define PPC32_SPRG8_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG8_RD PPC32_CPU_REG(SPRG8)
#define PPC32_SPRG8_WR PPC32_CPU_REG(SPRG8)

#define PPC32_SPRG9_BITS (sizeof(Uns64) * 8)
#define PPC32_SPRG9_RD PPC32_CPU_REG(SPRG9)
#define PPC32_SPRG9_WR PPC32_CPU_REG(SPRG9)

#define PPC32_MAS0_BITS (sizeof(Uns32) * 8)
#define PPC32_MAS0_RD PPC32_CPU_REG(MAS0)
#define PPC32_MAS0_WR PPC32_CPU_REG(MAS0)

#define PPC32_MAS1_BITS (sizeof(Uns32) * 8)
#define PPC32_MAS1_RD PPC32_CPU_REG(MAS1)
#define PPC32_MAS1_WR PPC32_CPU_REG(MAS1)

#define PPC32_MAS2_BITS (sizeof(Uns64) * 8)
#define PPC32_MAS2_RD PPC32_CPU_REG(MAS2)
#define PPC32_MAS2_WR PPC32_CPU_REG(MAS2)

#define PPC32_MAS3_BITS (sizeof(Uns32) * 8)
#define PPC32_MAS3_RD PPC32_CPU_REG(MAS3)
#define PPC32_MAS3_WR PPC32_CPU_REG(MAS3)

#define PPC32_MAS4_BITS (sizeof(Uns32) * 8)
#define PPC32_MAS4_RD PPC32_CPU_REG(MAS4)
#define PPC32_MAS4_WR PPC32_CPU_REG(MAS4)

#define PPC32_MAS6_BITS (sizeof(Uns32) * 8)
#define PPC32_MAS6_RD PPC32_CPU_REG(MAS6)
#define PPC32_MAS6_WR PPC32_CPU_REG(MAS6)

#define PPC32_MAS7_BITS (sizeof(Uns32) * 8)
#define PPC32_MAS7_RD PPC32_CPU_REG(MAS7)
#define PPC32_MAS7_WR PPC32_CPU_REG(MAS7)

#define PPC32_PID1_BITS (sizeof(Uns32) * 8)
#define PPC32_PID1_RD PPC32_CPU_REG(PID1)
#define PPC32_PID1_WR PPC32_CPU_REG(PID1)

#define PPC32_PID2_BITS (sizeof(Uns32) * 8)
#define PPC32_PID2_RD PPC32_CPU_REG(PID2)
#define PPC32_PID2_WR PPC32_CPU_REG(PID2)

#define PPC32_TLB0CFG_BITS (sizeof(Uns32) * 8)
#define PPC32_TLB0CFG_RD PPC32_CPU_REG(TLB0CFG)
#define PPC32_TLB0CFG_WR PPC32_CPU_REG(TLB0CFG)

#define PPC32_TLB1CFG_BITS (sizeof(Uns32) * 8)
#define PPC32_TLB1CFG_RD PPC32_CPU_REG(TLB1CFG)
#define PPC32_TLB1CFG_WR PPC32_CPU_REG(TLB1CFG)

#define PPC32_TLB2CFG_BITS (sizeof(Uns32) * 8)
#define PPC32_TLB2CFG_RD PPC32_CPU_REG(TLB2CFG)
#define PPC32_TLB2CFG_WR PPC32_CPU_REG(TLB2CFG)

#define PPC32_TLB3CFG_BITS (sizeof(Uns32) * 8)
#define PPC32_TLB3CFG_RD PPC32_CPU_REG(TLB3CFG)
#define PPC32_TLB3CFG_WR PPC32_CPU_REG(TLB3CFG)

#define PPC32_EPR_BITS (sizeof(Uns32) * 8)
#define PPC32_EPR_RD PPC32_CPU_REG(EPR)
#define PPC32_EPR_WR PPC32_CPU_REG(EPR)

#define PPC32_PERF_MON_BITS (sizeof(Uns64) * 8)
#define PPC32_PERF_MON_RD(_R) PPC32_CPU_REG(perf_mon[_R])
#define PPC32_PERF_MON_WR(_R) PPC32_CPU_REG(perf_mon[_R])

#define PPC32_PPR_BITS (sizeof(Uns64) * 8)
#define PPC32_PPR_RD PPC32_CPU_REG(PPR)
#define PPC32_PPR_WR PPC32_CPU_REG(PPR)

#define PPC32_DCDBTRL_BITS (sizeof(Uns32) * 8)
#define PPC32_DCDBTRL_RD PPC32_CPU_REG(DCDBTRL)
#define PPC32_DCDBTRL_WR PPC32_CPU_REG(DCDBTRL)

#define PPC32_DCDBTRH_BITS (sizeof(Uns32) * 8)
#define PPC32_DCDBTRH_RD PPC32_CPU_REG(DCDBTRH)
#define PPC32_DCDBTRH_WR PPC32_CPU_REG(DCDBTRH)

#define PPC32_ICDBTRL_BITS (sizeof(Uns32) * 8)
#define PPC32_ICDBTRL_RD PPC32_CPU_REG(ICDBTRL)
#define PPC32_ICDBTRL_WR PPC32_CPU_REG(ICDBTRL)

#define PPC32_ICDBTRH_BITS (sizeof(Uns32) * 8)
#define PPC32_ICDBTRH_RD PPC32_CPU_REG(ICDBTRH)
#define PPC32_ICDBTRH_WR PPC32_CPU_REG(ICDBTRH)

#define PPC32_EPLC_BITS (sizeof(Uns32) * 8)
#define PPC32_EPLC_RD PPC32_CPU_REG(EPLC)
#define PPC32_EPLC_WR PPC32_CPU_REG(EPLC)

#define PPC32_EPSC_BITS (sizeof(Uns32) * 8)
#define PPC32_EPSC_RD PPC32_CPU_REG(EPSC)
#define PPC32_EPSC_WR PPC32_CPU_REG(EPSC)

#define PPC32_ICDBDR_BITS (sizeof(Uns32) * 8)
#define PPC32_ICDBDR_RD PPC32_CPU_REG(ICDBDR)
#define PPC32_ICDBDR_WR PPC32_CPU_REG(ICDBDR)

#define PPC32_MMUCSR0_BITS (sizeof(Uns32) * 8)
#define PPC32_MMUCSR0_RD PPC32_CPU_REG(MMUCSR0)
#define PPC32_MMUCSR0_WR PPC32_CPU_REG(MMUCSR0)

#define PPC32_DABR_BITS (sizeof(Uns64) * 8)
#define PPC32_DABR_RD PPC32_CPU_REG(DABR)
#define PPC32_DABR_WR PPC32_CPU_REG(DABR)

#define PPC32_DABRX_BITS (sizeof(Uns64) * 8)
#define PPC32_DABRX_RD PPC32_CPU_REG(DABRX)
#define PPC32_DABRX_WR PPC32_CPU_REG(DABRX)

#define PPC32_MMUCFG_BITS (sizeof(Uns32) * 8)
#define PPC32_MMUCFG_RD PPC32_CPU_REG(MMUCFG)
#define PPC32_MMUCFG_WR PPC32_CPU_REG(MMUCFG)

#define PPC32_FPSCR_BITS (sizeof(Uns64) * 8)
#define PPC32_FPSCR_RD PPC32_CPU_REG(FPSCR)
#define PPC32_FPSCR_WR PPC32_CPU_REG(FPSCR)

#define PPC32_VSCR_BITS (sizeof(Uns32) * 8)
#define PPC32_VSCR_RD PPC32_CPU_REG(VSCR)
#define PPC32_VSCR_WR PPC32_CPU_REG(VSCR)

#define PPC32_ACCUMULATOR_BITS (sizeof(Uns64) * 8)
#define PPC32_ACCUMULATOR_RD PPC32_CPU_REG(Accumulator)
#define PPC32_ACCUMULATOR_WR PPC32_CPU_REG(Accumulator)

#define PPC32_MSR_BITS (sizeof(Uns64) * 8)
#define PPC32_MSR_RD(_P) PPC32_SPR_REG(_P, MSR)
#define PPC32_MSR_WR(_P) PPC32_SPR_REG(_P, MSR)

#define PPC32_RESERVE_ADDR_BITS (sizeof(Uns64) * 8)
#define PPC32_RESERVE_ADDR_RD PPC32_CPU_REG(RESERVE_ADDR)
#define PPC32_RESERVE_ADDR_WR PPC32_CPU_REG(RESERVE_ADDR)

#define PPC32_RESERVE_LENGTH_BITS (sizeof(Uns8) * 8)
#define PPC32_RESERVE_LENGTH_RD PPC32_CPU_REG(RESERVE_LENGTH)
#define PPC32_RESERVE_LENGTH_WR PPC32_CPU_REG(RESERVE_LENGTH)

#define PPC32_RESERVE_BITS (sizeof(Uns8) * 8)
#define PPC32_RESERVE_RD PPC32_CPU_REG(RESERVE)
#define PPC32_RESERVE_WR PPC32_CPU_REG(RESERVE)

#define PPC32_FLG_CI PPC32_CPU_REG(FLG_CI)
#define PPC32_FLG_CO PPC32_CPU_REG(FLG_CO)
#define PPC32_FLG_PA PPC32_CPU_REG(FLG_PA)
#define PPC32_FLG_ZR PPC32_CPU_REG(FLG_ZR)
#define PPC32_FLG_SI PPC32_CPU_REG(FLG_SI)
#define PPC32_FLG_OV PPC32_CPU_REG(FLG_OV)
#define PPC32_FLG_TEMP PPC32_CPU_REG(FLG_TEMP)

#define PPC32_FPU_FLG PPC32_CPU_REG(FPU_FLG)
#define PPC32_FPU_FLG_STICKY PPC32_CPU_REG(FPU_FLG_STICKY)
#define PPC32_CMP_FLG PPC32_CPU_REG(CMP_FLG)
#define PPC32_CNV32_FLG PPC32_CPU_REG(CNV32_FLG)
#define PPC32_CNV64_FLG PPC32_CPU_REG(CNV64_FLG)
#define PPC32_QNAN_FLG PPC32_CPU_REG(QNAN_FLG)

#define PPC32_FLG_FP_SI PPC32_CPU_REG(FLG_FP_SI)

#define PPC32_FLG_FPSCR_VXCVI  PPC32_CPU_REG(FLG_FPSCR_VXCVI)
#define PPC32_FLG_FPSCR_VXSQRT PPC32_CPU_REG(FLG_FPSCR_VXSQRT)
#define PPC32_FLG_FPSCR_VXSOFT PPC32_CPU_REG(FLG_FPSCR_VXSOFT)
#define PPC32_FLG_FPSCR_VXVC   PPC32_CPU_REG(FLG_FPSCR_VXVC)
#define PPC32_FLG_FPSCR_VXIMZ  PPC32_CPU_REG(FLG_FPSCR_VXIMZ)
#define PPC32_FLG_FPSCR_VXZDZ  PPC32_CPU_REG(FLG_FPSCR_VXZDZ)
#define PPC32_FLG_FPSCR_VXIDI  PPC32_CPU_REG(FLG_FPSCR_VXIDI)
#define PPC32_FLG_FPSCR_VXISI  PPC32_CPU_REG(FLG_FPSCR_VXISI)
#define PPC32_FLG_FPSCR_VXSNAN PPC32_CPU_REG(FLG_FPSCR_VXSNAN)

#define PPC32_FPU_OP_BITS (sizeof(Uns8) * 32)
#define PPC32_FPU_OP PPC32_CPU_REG(FPU_OP)

#define PPC32_FPU_REL_GEN PPC32_CPU_REG(FPU_REL_GEN)
#define PPC32_FPU_REL PPC32_CPU_REG(FPU_REL)
#define PPC32_CNV32_REL PPC32_CPU_REG(CNV32_REL)
#define PPC32_TEMP_REL PPC32_CPU_REG(TEMP_REL)
#define PPC32_FLG_FP_LDST PPC32_CPU_REG(FLG_FP_LDST)

#define PPC32_CPU_REG_CONST(_F) VMI_CPU_REG_CONST(ppc32P, _F)
#define PPC32_GPR_CONST(_R) PPC32_CPU_REG_CONST(GPR[_R])

#define PPC32_FPR_CONST(_R) PPC32_CPU_REG_CONST(FPR[_R])

#define PPC32_VR_CONST(_R) PPC32_CPU_REG_CONST(VR[_R])

#define PPC32_CR_CONST PPC32_CPU_REG_CONST(CR)

#define PPC32_XER_CONST PPC32_CPU_REG_CONST(XER)

#define PPC32_XER_SO_CONST PPC32_CPU_REG_CONST(XER_SO)

#define PPC32_XER_OV_CONST PPC32_CPU_REG_CONST(XER_OV)

#define PPC32_XER_CA_CONST PPC32_CPU_REG_CONST(XER_CA)

#define PPC32_LT_CONST(_R) PPC32_CPU_REG_CONST(LT[_R])

#define PPC32_GT_CONST(_R) PPC32_CPU_REG_CONST(GT[_R])

#define PPC32_EQ_CONST(_R) PPC32_CPU_REG_CONST(EQ[_R])

#define PPC32_SO_CONST(_R) PPC32_CPU_REG_CONST(SO[_R])

#define PPC32_TEMP_CONST(_R) PPC32_CPU_TEMP_CONST(TEMP[_R])

#define PPC32_LR_CONST PPC32_CPU_REG_CONST(LR)

#define PPC32_CTR_CONST PPC32_CPU_REG_CONST(CTR)

#define PPC32_DSCR_CONST PPC32_CPU_REG_CONST(DSCR)

#define PPC32_DSISR_CONST PPC32_CPU_REG_CONST(DSISR)

#define PPC32_DAR_CONST PPC32_CPU_REG_CONST(DAR)

#define PPC32_DEC_CONST PPC32_CPU_REG_CONST(DEC)

#define PPC32_DEC_TMR_CONST PPC32_CPU_REG_CONST(DEC_tmr)

#define PPC32_SDR1_CONST PPC32_CPU_REG_CONST(SDR1)

#define PPC32_SRR0_CONST PPC32_CPU_REG_CONST(SRR0)

#define PPC32_SRR1_CONST PPC32_CPU_REG_CONST(SRR1)

#define PPC32_CFAR_CONST PPC32_CPU_REG_CONST(CFAR)

#define PPC32_AMR_CONST PPC32_CPU_REG_CONST(AMR)

#define PPC32_PID0_CONST PPC32_CPU_REG_CONST(PID0)

#define PPC32_DECAR_CONST PPC32_CPU_REG_CONST(DECAR)

#define PPC32_CSRR0_CONST PPC32_CPU_REG_CONST(CSRR0)

#define PPC32_CSRR1_CONST PPC32_CPU_REG_CONST(CSRR1)

#define PPC32_DEAR_CONST PPC32_CPU_REG_CONST(DEAR)

#define PPC32_ESR_CONST PPC32_CPU_REG_CONST(ESR)

#define PPC32_IVPR_CONST PPC32_CPU_REG_CONST(IVPR)

#define PPC32_CTRL_CONST PPC32_CPU_REG_CONST(CTRL)

#define PPC32_VRSAVE_CONST PPC32_CPU_REG_CONST(VRSAVE)

#define PPC32_SPRG0_CONST PPC32_CPU_REG_CONST(SPRG0)

#define PPC32_SPRG1_CONST PPC32_CPU_REG_CONST(SPRG1)

#define PPC32_SPRG2_CONST PPC32_CPU_REG_CONST(SPRG2)

#define PPC32_SPRG3_CONST PPC32_CPU_REG_CONST(SPRG3)

#define PPC32_SPRG4_CONST PPC32_CPU_REG_CONST(SPRG4)

#define PPC32_SPRG5_CONST PPC32_CPU_REG_CONST(SPRG5)

#define PPC32_SPRG6_CONST PPC32_CPU_REG_CONST(SPRG6)

#define PPC32_SPRG7_CONST PPC32_CPU_REG_CONST(SPRG7)

#define PPC32_TB_CONST PPC32_CPU_REG_CONST(TB)

#define PPC32_TBU_CONST PPC32_CPU_REG_CONST(TBU)

#define PPC32_EAR_CONST PPC32_CPU_REG_CONST(EAR)

#define PPC32_PIR_CONST PPC32_CPU_REG_CONST(PIR)

#define PPC32_PVR_CONST PPC32_CPU_REG_CONST(PVR)

#define PPC32_HSPRG_CONST(_R) PPC32_CPU_REG_CONST(HSPRG[_R])

#define PPC32_DBSR_CONST PPC32_CPU_REG_CONST(DBSR)

#define PPC32_HDSISR_CONST PPC32_CPU_REG_CONST(HDSISR)

#define PPC32_HDAR_CONST PPC32_CPU_REG_CONST(HDAR)

#define PPC32_DBCR0_CONST PPC32_CPU_REG_CONST(DBCR0)

#define PPC32_SPURR_CONST PPC32_CPU_REG_CONST(SPURR)

#define PPC32_PURR_CONST PPC32_CPU_REG_CONST(PURR)

#define PPC32_DBCR1_CONST PPC32_CPU_REG_CONST(DBCR1)

#define PPC32_HDEC_CONST PPC32_CPU_REG_CONST(HDEC)

#define PPC32_DBCR2_CONST PPC32_CPU_REG_CONST(DBCR2)

#define PPC32_RMOR_CONST PPC32_CPU_REG_CONST(RMOR)

#define PPC32_IAC1_CONST PPC32_CPU_REG_CONST(IAC1)

#define PPC32_IAC2_CONST PPC32_CPU_REG_CONST(IAC2)

#define PPC32_IAC3_CONST PPC32_CPU_REG_CONST(IAC3)

#define PPC32_IAC4_CONST PPC32_CPU_REG_CONST(IAC4)

#define PPC32_HRMOR_CONST PPC32_CPU_REG_CONST(HRMOR)

#define PPC32_HSRR0_CONST PPC32_CPU_REG_CONST(HSRR0)

#define PPC32_HSRR1_CONST PPC32_CPU_REG_CONST(HSRR1)

#define PPC32_DAC1_CONST PPC32_CPU_REG_CONST(DAC1)

#define PPC32_DAC2_CONST PPC32_CPU_REG_CONST(DAC2)

#define PPC32_LPCR_CONST PPC32_CPU_REG_CONST(LPCR)

#define PPC32_DVC1_CONST PPC32_CPU_REG_CONST(DVC1)

#define PPC32_DVC2_CONST PPC32_CPU_REG_CONST(DVC2)

#define PPC32_LPIDR_CONST PPC32_CPU_REG_CONST(LPIDR)

#define PPC32_TSR_CONST PPC32_CPU_REG_CONST(TSR)

#define PPC32_HMER_CONST PPC32_CPU_REG_CONST(HMER)

#define PPC32_HMEER_CONST PPC32_CPU_REG_CONST(HMEER)

#define PPC32_PCR_CONST PPC32_CPU_REG_CONST(PCR)

#define PPC32_HEIR_CONST PPC32_CPU_REG_CONST(HEIR)

#define PPC32_TCR_CONST PPC32_CPU_REG_CONST(TCR)

#define PPC32_IVOR0_CONST PPC32_CPU_REG_CONST(IVOR0)

#define PPC32_IVOR1_CONST PPC32_CPU_REG_CONST(IVOR1)

#define PPC32_IVOR2_CONST PPC32_CPU_REG_CONST(IVOR2)

#define PPC32_IVOR3_CONST PPC32_CPU_REG_CONST(IVOR3)

#define PPC32_IVOR4_CONST PPC32_CPU_REG_CONST(IVOR4)

#define PPC32_IVOR5_CONST PPC32_CPU_REG_CONST(IVOR5)

#define PPC32_IVOR6_CONST PPC32_CPU_REG_CONST(IVOR6)

#define PPC32_IVOR7_CONST PPC32_CPU_REG_CONST(IVOR7)

#define PPC32_IVOR8_CONST PPC32_CPU_REG_CONST(IVOR8)

#define PPC32_IVOR9_CONST PPC32_CPU_REG_CONST(IVOR9)

#define PPC32_IVOR10_CONST PPC32_CPU_REG_CONST(IVOR10)

#define PPC32_IVOR11_CONST PPC32_CPU_REG_CONST(IVOR11)

#define PPC32_IVOR12_CONST PPC32_CPU_REG_CONST(IVOR12)

#define PPC32_IVOR13_CONST PPC32_CPU_REG_CONST(IVOR13)

#define PPC32_IVOR14_CONST PPC32_CPU_REG_CONST(IVOR14)

#define PPC32_IVOR15_CONST PPC32_CPU_REG_CONST(IVOR15)

#define PPC32_SPEFSCR_CONST PPC32_CPU_REG_CONST(SPEFSCR)

#define PPC32_ATB_CONST PPC32_CPU_REG_CONST(ATB)

#define PPC32_IVOR32_CONST PPC32_CPU_REG_CONST(IVOR32)

#define PPC32_IVOR33_CONST PPC32_CPU_REG_CONST(IVOR33)

#define PPC32_IVOR34_CONST PPC32_CPU_REG_CONST(IVOR34)

#define PPC32_IVOR35_CONST PPC32_CPU_REG_CONST(IVOR35)

#define PPC32_IVOR36_CONST PPC32_CPU_REG_CONST(IVOR36)

#define PPC32_IVOR37_CONST PPC32_CPU_REG_CONST(IVOR37)

#define PPC32_MCSRR0_CONST PPC32_CPU_REG_CONST(MCSRR0)

#define PPC32_MCSRR1_CONST PPC32_CPU_REG_CONST(MCSRR1)

#define PPC32_MCSR_CONST PPC32_CPU_REG_CONST(MCSR)

#define PPC32_DSRR0_CONST PPC32_CPU_REG_CONST(DSRR0)

#define PPC32_DSRR1_CONST PPC32_CPU_REG_CONST(DSRR1)

#define PPC32_SPRG8_CONST PPC32_CPU_REG_CONST(SPRG8)

#define PPC32_SPRG9_CONST PPC32_CPU_REG_CONST(SPRG9)

#define PPC32_MAS0_CONST PPC32_CPU_REG_CONST(MAS0)

#define PPC32_MAS1_CONST PPC32_CPU_REG_CONST(MAS1)

#define PPC32_MAS2_CONST PPC32_CPU_REG_CONST(MAS2)

#define PPC32_MAS3_CONST PPC32_CPU_REG_CONST(MAS3)

#define PPC32_MAS4_CONST PPC32_CPU_REG_CONST(MAS4)

#define PPC32_MAS6_CONST PPC32_CPU_REG_CONST(MAS6)

#define PPC32_MAS7_CONST PPC32_CPU_REG_CONST(MAS7)

#define PPC32_PID1_CONST PPC32_CPU_REG_CONST(PID1)

#define PPC32_PID2_CONST PPC32_CPU_REG_CONST(PID2)

#define PPC32_TLB0CFG_CONST PPC32_CPU_REG_CONST(TLB0CFG)

#define PPC32_TLB1CFG_CONST PPC32_CPU_REG_CONST(TLB1CFG)

#define PPC32_TLB2CFG_CONST PPC32_CPU_REG_CONST(TLB2CFG)

#define PPC32_TLB3CFG_CONST PPC32_CPU_REG_CONST(TLB3CFG)

#define PPC32_EPR_CONST PPC32_CPU_REG_CONST(EPR)

#define PPC32_PERF_MON_CONST(_R) PPC32_CPU_REG_CONST(perf_mon[_R])

#define PPC32_PPR_CONST PPC32_CPU_REG_CONST(PPR)

#define PPC32_DCDBTRL_CONST PPC32_CPU_REG_CONST(DCDBTRL)

#define PPC32_DCDBTRH_CONST PPC32_CPU_REG_CONST(DCDBTRH)

#define PPC32_ICDBTRL_CONST PPC32_CPU_REG_CONST(ICDBTRL)

#define PPC32_ICDBTRH_CONST PPC32_CPU_REG_CONST(ICDBTRH)

#define PPC32_EPLC_CONST PPC32_CPU_REG_CONST(EPLC)

#define PPC32_EPSC_CONST PPC32_CPU_REG_CONST(EPSC)

#define PPC32_ICDBDR_CONST PPC32_CPU_REG_CONST(ICDBDR)

#define PPC32_MMUCSR0_CONST PPC32_CPU_REG_CONST(MMUCSR0)

#define PPC32_DABR_CONST PPC32_CPU_REG_CONST(DABR)

#define PPC32_DABRX_CONST PPC32_CPU_REG_CONST(DABRX)

#define PPC32_MMUCFG_CONST PPC32_CPU_REG_CONST(MMUCFG)

#define PPC32_FPSCR_CONST PPC32_CPU_REG_CONST(FPSCR)

#define PPC32_VSCR_CONST PPC32_CPU_REG_CONST(VSCR)

#define PPC32_ACCUMULATOR_CONST PPC32_CPU_REG_CONST(Accumulator)

#define PPC32_MSR_CONST PPC32_CPU_REG_CONST(MSR)

#define PPC32_RESERVE_ADDR_CONST PPC32_CPU_REG_CONST(RESERVE_ADDR)

#define PPC32_RESERVE_CONST PPC32_CPU_REG_CONST(RESERVE)

#define PPC32_FLG_CI_CONST PPC32_CPU_REG_CONST(FLG_CI)

#define PPC32_FLG_CO_CONST PPC32_CPU_REG_CONST(FLG_CO)

#define PPC32_FLG_PA_CONST PPC32_CPU_REG_CONST(FLG_PA)

#define PPC32_FLG_ZR_CONST PPC32_CPU_REG_CONST(FLG_ZR)

#define PPC32_FLG_SI_CONST PPC32_CPU_REG_CONST(FLG_SI)

#define PPC32_FLG_OV_CONST PPC32_CPU_REG_CONST(FLG_OV)

#define PPC32_FLG_TEMP_CONST PPC32_CPU_REG_CONST(FLG_TEMP)

#define PPC32_FLG_FP_SI_CONST PPC32_CPU_REG_CONST(FLG_FP_SI)

static inline const char *getstr_AALK(int index) {
    static const char *lookup[] = {
        [0] "",
        [1] "L",
        [2] "A",
        [3] "LA",
    };
    return lookup[index];
}

static inline const char *getstr_BITSTR(int index) {
    static const char *lookup[] = {
        [0] "DNZF-",
        [1] "DNZF+",
        [2] "DZF-",
        [3] "DZF+",
        [4] "NZF-",
        [5] "NZF+",
        [6] "ZF-",
        [7] "ZF+",
        [8] "DNZT-",
        [9] "DNZT+",
        [10] "DZT-",
        [11] "DZT+",
        [12] "NZT-",
        [13] "NZT+",
        [14] "ZT-",
        [15] "ZT+",
    };
    return lookup[index];
}

static inline const char *getstr_BITSTR32(int index) {
    static const char *lookup[] = {
        [0] "F",
        [1] "T",
        [2] "DNZ",
        [3] "DZ",
    };
    return lookup[index];
}

static inline const char *getstr_CR(int index) {
    static const char *lookup[] = {
        [0] "LT",
        [1] "GT",
        [2] "EQ",
        [3] "SO",
        [4] "4*CR1+LT",
        [5] "4*CR1+GT",
        [6] "4*CR1+EQ",
        [7] "4*CR1+SO",
        [8] "4*CR2+LT",
        [9] "4*CR2+GT",
        [10] "4*CR2+EQ",
        [11] "4*CR2+SO",
        [12] "4*CR3+LT",
        [13] "4*CR3+GT",
        [14] "4*CR3+EQ",
        [15] "4*CR3+SO",
        [16] "4*CR4+LT",
        [17] "4*CR4+GT",
        [18] "4*CR4+EQ",
        [19] "4*CR4+SO",
        [20] "4*CR5+LT",
        [21] "4*CR5+GT",
        [22] "4*CR5+EQ",
        [23] "4*CR5+SO",
        [24] "4*CR6+LT",
        [25] "4*CR6+GT",
        [26] "4*CR6+EQ",
        [27] "4*CR6+SO",
        [28] "4*CR7+LT",
        [29] "4*CR7+GT",
        [30] "4*CR7+EQ",
        [31] "4*CR7+SO",
    };
    return lookup[index];
}

static inline const char *getstr_CRVLE(int index) {
    static const char *lookup[] = {
        [0] "CR0+LT",
        [1] "CR0+GT",
        [2] "CR0+EQ",
        [3] "CR0+SO",
        [4] "CR1+LT",
        [5] "CR1+GT",
        [6] "CR1+EQ",
        [7] "CR1+SO",
        [8] "CR2+LT",
        [9] "CR2+GT",
        [10] "CR2+EQ",
        [11] "CR2+SO",
        [12] "CR3+LT",
        [13] "CR3+GT",
        [14] "CR3+EQ",
        [15] "CR3+SO",
    };
    return lookup[index];
}

static inline const char *getstr_EH(int index) {
    static const char *lookup[] = {
        [1] "_1",
    };
    return lookup[index];
}

static inline const char *getstr_RA(int index) {
    static const char *lookup[] = {
        [0] "0",
        [1] "R1",
        [2] "R2",
        [3] "R3",
        [4] "R4",
        [5] "R5",
        [6] "R6",
        [7] "R7",
        [8] "R8",
        [9] "R9",
        [10] "R10",
        [11] "R11",
        [12] "R12",
        [13] "R13",
        [14] "R14",
        [15] "R15",
        [16] "R16",
        [17] "R17",
        [18] "R18",
        [19] "R19",
        [20] "R20",
        [21] "R21",
        [22] "R22",
        [23] "R23",
        [24] "R24",
        [25] "R25",
        [26] "R26",
        [27] "R27",
        [28] "R28",
        [29] "R29",
        [30] "R30",
        [31] "R31",
    };
    return lookup[index];
}

static inline const char *getstr_TO(int index) {
    static const char *lookup[] = {
        [1] "LGT",
        [2] "LLT",
        [4] "EQ",
        [5] "LGE",
        [6] "LLE",
        [8] "GT",
        [12] "GE",
        [16] "LT",
        [20] "LE",
        [24] "NE",
    };
    return lookup[index];
}

#define CPU_PREFIX "PPC32"

typedef Uns32 ppc32Addr;

#endif // PPC32_NE_H
