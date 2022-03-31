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

#ifndef PPC32_SPR_400_H
#define PPC32_SPR_400_H
#include "vmi/vmiTypes.h"

typedef union {
    Uns64 reg;
    struct {
        Uns64       RSV0 : 2;
        Uns64       SRR0 : 62;
    } bits;
} TYPE_SRR0;

typedef union {
    Uns64 reg;
    struct {
        Uns64       SRR1 : 64;
    } bits;
} TYPE_SRR1;

typedef union {
    Uns32 reg;
    struct {
        Uns32        PID : 14;
        Uns32       RSV0 : 18;
    } bits;
} TYPE_PID0;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV2 : 1;
        Uns32        MIF : 1;
        Uns32    IMPDEP2 : 3;
        Uns32      VLEMI : 1;
        Uns32       EPID : 1;
        Uns32        SPV : 1;
        Uns32       RSV1 : 8;
        Uns32        PIE : 1;
        Uns32         BO : 1;
        Uns32        PUO : 1;
        Uns32         AP : 1;
        Uns32       DLK1 : 1;
        Uns32       DLK0 : 1;
        Uns32       RSV0 : 1;
        Uns32         ST : 1;
        Uns32         FP : 1;
        Uns32        PTR : 1;
        Uns32        PPR : 1;
        Uns32        PIL : 1;
        Uns32    IMPDEP1 : 4;
    } bits;
} TYPE_ESR;

typedef union {
    Uns64 reg;
    struct {
        Uns64       RSV0 : 16;
        Uns64      ADDR0 : 48;
    } bits;
} TYPE_IVPR;

typedef union {
    Uns64 reg;
    struct {
        Uns64        TBL : 32;
        Uns64        TBU : 32;
    } bits;
} TYPE_TB;

typedef union {
    Uns64 reg;
    struct {
        Uns64       RSV0 : 24;
        Uns64      TBU40 : 40;
    } bits;
} TYPE_TBU;

typedef union {
    Uns32 reg;
    struct {
        Uns32     PROCID : 32;
    } bits;
} TYPE_PIR;

typedef union {
    Uns32 reg;
    struct {
        Uns32   Revision : 16;
        Uns32    Version : 16;
    } bits;
} TYPE_PVR;

typedef union {
    Uns32 reg;
    struct {
        Uns32    IMPDEP2 : 5;
        Uns32       CRET : 1;
        Uns32      CIRPT : 1;
        Uns32    IMPDEP1 : 4;
        Uns32       RSV0 : 4;
        Uns32        RET : 1;
        Uns32      DAC2W : 1;
        Uns32      DAC2R : 1;
        Uns32      DAC1W : 1;
        Uns32      DAC1R : 1;
        Uns32       IAC4 : 1;
        Uns32       IAC3 : 1;
        Uns32       IAC2 : 1;
        Uns32       IAC1 : 1;
        Uns32       TRAP : 1;
        Uns32       IRPT : 1;
        Uns32        BRT : 1;
        Uns32       ICMP : 1;
        Uns32        MRR : 2;
        Uns32        UDE : 1;
        Uns32        IDE : 1;
    } bits;
} TYPE_DBSR;

typedef union {
    Uns32 reg;
    struct {
        Uns32         FT : 1;
        Uns32    IMPDEP1 : 4;
        Uns32       CRET : 1;
        Uns32      CIRPT : 1;
        Uns32       RSV0 : 8;
        Uns32        RET : 1;
        Uns32       DAC2 : 2;
        Uns32       DAC1 : 2;
        Uns32       IAC4 : 1;
        Uns32       IAC3 : 1;
        Uns32       IAC2 : 1;
        Uns32       IAC1 : 1;
        Uns32       TRAP : 1;
        Uns32       IRPT : 1;
        Uns32        BRT : 1;
        Uns32       ICMP : 1;
        Uns32        RST : 2;
        Uns32        IDM : 1;
        Uns32        EDM : 1;
    } bits;
} TYPE_DBCR0;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV1 : 6;
        Uns32     IAC34M : 2;
        Uns32     IAC4ER : 2;
        Uns32     IAC4US : 2;
        Uns32     IAC3ER : 2;
        Uns32     IAC3US : 2;
        Uns32       RSV0 : 6;
        Uns32     IAC12M : 2;
        Uns32     IAC2ER : 2;
        Uns32     IAC2US : 2;
        Uns32     IAC1ER : 2;
        Uns32     IAC1US : 2;
    } bits;
} TYPE_DBCR1;

typedef union {
    Uns32 reg;
    struct {
        Uns32     DVC2BE : 8;
        Uns32     DVC1BE : 8;
        Uns32      DVC2M : 2;
        Uns32      DVC1M : 2;
        Uns32       RSV0 : 2;
        Uns32     DAC12M : 2;
        Uns32     DAC2ER : 2;
        Uns32     DAC2US : 2;
        Uns32     DAC1ER : 2;
        Uns32     DAC1US : 2;
    } bits;
} TYPE_DBCR2;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 26;
        Uns32        FIS : 1;
        Uns32        DIS : 1;
        Uns32        WRS : 2;
        Uns32        WIS : 1;
        Uns32        ENW : 1;
    } bits;
} TYPE_TSR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 21;
        Uns32    IMPDEP1 : 1;
        Uns32        ARE : 1;
        Uns32        FIE : 1;
        Uns32         FP : 2;
        Uns32        DIE : 1;
        Uns32        WIE : 1;
        Uns32        WRC : 2;
        Uns32         WP : 2;
    } bits;
} TYPE_TCR;

typedef union {
    Uns64 reg;
    struct {
        Uns64       RSV0 : 1;  // LE
        Uns64       RSV1 : 1;  // RI
        Uns64        PMM : 1;  //
        Uns64       RSV2 : 1;  //
        Uns64         DS : 1;  // DR
        Uns64         IS : 1;  // IR
        Uns64       RSV3 : 2;  //
        Uns64        FE1 : 1;  //
        Uns64         DE : 1;  // BE
        Uns64        DWE : 1;  // SE
        Uns64        FE0 : 1;  //
        Uns64         ME : 1;  //
        Uns64         FP : 1;  //
        Uns64         PR : 1;  //
        Uns64         EE : 1;  //
        Uns64       RSV4 : 1;  //
        Uns64         CE : 1;  // RSV
        Uns64         WE : 1;  // RSV
    } bits;
} TYPE_MSR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32      IQWPM : 1;
        Uns32      DQWPM : 2;
        Uns32       RSV1 : 4;
        Uns32      FLSTA : 1;
        Uns32       RSV2 : 6;
        Uns32        DTB : 1;
        Uns32    ICWRIDX : 4;
        Uns32     DAPUIB : 1;
        Uns32        ICS : 1;
        Uns32       RSV3 : 5;
        Uns32       CRPE : 1;
        Uns32       RSV4 : 2;
        Uns32        PRE : 1;
        Uns32       RSV5 : 1;
    } bits;
} TYPE_CCR0;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 8;
        Uns32        TCS : 2;
        Uns32        DPC : 1;
        Uns32       RSV1 : 1;
        Uns32        TSS : 1;
        Uns32       RSV2 : 1;
        Uns32    MMUDPEI : 1;
        Uns32    MMUTPEI : 1;
        Uns32     DCTPEI : 2;
        Uns32     DCLPEI : 2;
        Uns32     DCDPEI : 2;
        Uns32     ICTPEI : 2;
        Uns32     ICLPEI : 2;
        Uns32     ICDPEI : 2;
        Uns32     FPRPEI : 2;
        Uns32     GPRPEI : 2;
    } bits;
} TYPE_CCR1;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 10;
        Uns32      MCDTO : 1;
        Uns32     SPC5C1 : 1;
        Uns32       RSV1 : 3;
        Uns32      DISTG : 1;
        Uns32     STGCTR : 4;
        Uns32     DCSTGW : 1;
        Uns32       RSV2 : 1;
        Uns32       PMUD : 1;
        Uns32       RSV3 : 4;
        Uns32       DSTI : 1;
        Uns32       RSV4 : 1;
        Uns32      DLFPD : 1;
        Uns32       DSTG : 2;
    } bits;
} TYPE_CCR2;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 2;
        Uns32    DCDAAPU : 1;
        Uns32    DCDAHIT : 1;
        Uns32    DCSNPPE : 1;
        Uns32    DCLRUPE : 1;
        Uns32       RSV1 : 1;
        Uns32     DCTAPE : 1;
        Uns32     DCDAPE : 1;
        Uns32   DCINDXPE : 7;
        Uns32     DCOSPE : 4;
        Uns32     DCESPE : 4;
        Uns32       RSV2 : 4;
        Uns32     DCRDPE : 4;
    } bits;
} TYPE_DCESR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 10;
        Uns32        UOA : 22;
    } bits;
} TYPE_DCRIPR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 22;
        Uns32     PARITY : 2;
        Uns32        IPB : 8;
    } bits;
} TYPE_ICDBDR1;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 24;
        Uns32     IOCR2U : 1;
        Uns32     IOCR1U : 1;
        Uns32    IOCR2ME : 1;
        Uns32    IOCR1ME : 1;
        Uns32     IOCR2M : 1;
        Uns32    IOCR2EN : 1;
        Uns32     IOCR1M : 1;
        Uns32    IOCR1EN : 1;
    } bits;
} TYPE_IOCCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32    SECMASK : 10;
        Uns32    PRIMASK : 6;
        Uns32        SEC : 10;
        Uns32        PRI : 6;
    } bits;
} TYPE_IOCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 20;
        Uns32        DCR : 1;
        Uns32         L2 : 1;
        Uns32        IMP : 1;
        Uns32        FPR : 1;
        Uns32        GPR : 1;
        Uns32         DC : 1;
        Uns32         IC : 1;
        Uns32        TLB : 1;
        Uns32       RSV1 : 3;
        Uns32        MCS : 1;
    } bits;
} TYPE_MCSR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       VBE2 : 1;
        Uns32       VBE1 : 1;
        Uns32       VBE0 : 1;
        Uns32       RSV0 : 5;
        Uns32       IBE2 : 8;
        Uns32       IBE1 : 8;
        Uns32       IBE0 : 8;
    } bits;
} TYPE_MMUBE0;

typedef union {
    Uns32 reg;
    struct {
        Uns32       VBE5 : 1;
        Uns32       VBE4 : 1;
        Uns32       VBE3 : 1;
        Uns32       RSV0 : 5;
        Uns32       IBE5 : 8;
        Uns32       IBE4 : 8;
        Uns32       IBE3 : 8;
    } bits;
} TYPE_MMUBE1;

typedef union {
    Uns32 reg;
    struct {
        Uns32       STID : 16;
        Uns32        STS : 1;
        Uns32     LINDEX : 8;
        Uns32       RSV0 : 1;
        Uns32      IULXE : 1;
        Uns32      DULXE : 1;
        Uns32     LVALID : 1;
        Uns32       LWAY : 2;
        Uns32      REALE : 1;
    } bits;
} TYPE_MMUCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 31;
        Uns32        FAC : 1;
    } bits;
} TYPE_PMUCC0;

typedef union {
    Uns32 reg;
    struct {
        Uns32          U : 4;
        Uns32         UW : 1;
        Uns32         UR : 1;
        Uns32         UX : 1;
        Uns32         SW : 1;
        Uns32         SR : 1;
        Uns32         SX : 1;
        Uns32       RSV0 : 2;
        Uns32       IL1D : 1;
        Uns32       IL1I : 1;
        Uns32          E : 1;
        Uns32          G : 1;
        Uns32          M : 1;
        Uns32          I : 1;
        Uns32          W : 1;
        Uns32       RSV1 : 1;
        Uns32       ERPN : 10;
        Uns32       RSV2 : 2;
    } bits;
} TYPE_RMPD;

typedef union {
    Uns32 reg;
    struct {
        Uns32          U : 4;
        Uns32       RSV0 : 10;
        Uns32          E : 1;
        Uns32       RSV1 : 5;
        Uns32       ERPN : 10;
        Uns32       RSV2 : 2;
    } bits;
} TYPE_RSTCFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 4;
        Uns32       ORD7 : 4;
        Uns32       ORD6 : 4;
        Uns32       ORD5 : 4;
        Uns32       ORD4 : 4;
        Uns32       ORD3 : 4;
        Uns32       ORD2 : 4;
        Uns32       ORD1 : 4;
    } bits;
} TYPE_SSPCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 4;
        Uns32       ORD7 : 3;
        Uns32       RSV1 : 1;
        Uns32       ORD6 : 3;
        Uns32       RSV2 : 1;
        Uns32       ORD5 : 3;
        Uns32       RSV3 : 1;
        Uns32       ORD4 : 3;
        Uns32       RSV4 : 1;
        Uns32       ORD3 : 3;
        Uns32       RSV5 : 1;
        Uns32       ORD2 : 3;
        Uns32       RSV6 : 1;
        Uns32       ORD1 : 3;
        Uns32       RSV7 : 1;
    } bits;
} TYPE_ISPCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 4;
        Uns32       ORD7 : 4;
        Uns32       ORD6 : 4;
        Uns32       ORD5 : 4;
        Uns32       ORD4 : 4;
        Uns32       ORD3 : 4;
        Uns32       ORD2 : 4;
        Uns32       ORD1 : 4;
    } bits;
} TYPE_USPCR;

typedef struct ppc32sprS {
    TYPE_MSR MSR, MSR_rmask, MSR_wmask;

    TYPE_CCR0       CCR0,    CCR0_rmask,    CCR0_wmask;
    TYPE_CCR1       CCR1,    CCR1_rmask,    CCR1_wmask;
    TYPE_CCR2       CCR2,    CCR2_rmask,    CCR2_wmask;
    TYPE_DCESR     DCESR,   DCESR_rmask,   DCESR_wmask;
    TYPE_DCRIPR   DCRIPR,  DCRIPR_rmask,  DCRIPR_wmask;
    Uns32           DBDR;
    Uns32        ICDBDR0;
    TYPE_ICDBDR1 ICDBDR1, ICDBDR1_rmask, ICDBDR1_wmask;
    TYPE_IOCCR     IOCCR,   IOCCR_rmask,   IOCCR_wmask;
    TYPE_IOCR      IOCR1,   IOCR1_rmask,   IOCR1_wmask;
    TYPE_IOCR      IOCR2,   IOCR2_rmask,   IOCR2_wmask;
    TYPE_MCSR       MCSR,    MCSR_rmask,    MCSR_wmask;
    TYPE_MMUBE0   MMUBE0,  MMUBE0_rmask,  MMUBE0_wmask;
    TYPE_MMUBE1   MMUBE1,  MMUBE1_rmask,  MMUBE1_wmask;
    TYPE_MMUCR     MMUCR,   MMUCR_rmask,   MMUCR_wmask;
    TYPE_PMUCC0   PMUCC0,  PMUCC0_rmask,  PMUCC0_wmask;
    Uns32            PWM;
    TYPE_RMPD       RMPD,    RMPD_rmask,    RMPD_wmask;
    TYPE_RSTCFG   RSTCFG,  RSTCFG_rmask,  RSTCFG_wmask;
    TYPE_SSPCR     SSPCR,   SSPCR_rmask,   SSPCR_wmask;
    TYPE_ISPCR     ISPCR,   ISPCR_rmask,   ISPCR_wmask;
    TYPE_USPCR     USPCR,   USPCR_rmask,   USPCR_wmask;
    Uns32         USPGR0;

    Uns32 DEC;
    Uns64 DEC_tmr;
    TYPE_SRR0 SRR0, SRR0_rmask, SRR0_wmask;
    TYPE_SRR1 SRR1, SRR1_rmask, SRR1_wmask;
    TYPE_PID0 PID0, PID0_rmask, PID0_wmask;
    Uns32 DECAR;
    Uns64 CSRR0;
    Uns32 CSRR1;
    Uns64 DEAR;
    TYPE_ESR ESR, ESR_rmask, ESR_wmask;
    TYPE_IVPR IVPR, IVPR_rmask, IVPR_wmask;
    Uns64 SPRG3;
    Uns64 SPRG4;
    Uns64 SPRG5;
    Uns64 SPRG6;
    Uns64 SPRG7;
    TYPE_TB TB, TB_rmask, TB_wmask;
    TYPE_TBU TBU, TBU_rmask, TBU_wmask;
    Uns64 SPRG0;
    Uns64 SPRG1;
    Uns64 SPRG2;
    TYPE_PIR PIR, PIR_rmask, PIR_wmask;
    TYPE_PVR PVR, PVR_rmask, PVR_wmask;
    TYPE_DBSR DBSR, DBSR_rmask, DBSR_wmask;
    TYPE_DBCR0 DBCR0, DBCR0_rmask, DBCR0_wmask;
    TYPE_DBCR1 DBCR1, DBCR1_rmask, DBCR1_wmask;
    TYPE_DBCR2 DBCR2, DBCR2_rmask, DBCR2_wmask;
    Uns64 IAC1;
    Uns64 IAC2;
    Uns64 IAC3;
    Uns64 IAC4;
    Uns64 DAC1;
    Uns64 DAC2;
    Uns64 DVC1;
    Uns64 DVC2;
    TYPE_TSR TSR, TSR_rmask, TSR_wmask;
    TYPE_TCR TCR, TCR_rmask, TCR_wmask;
    Uns32 IVOR0;
    Uns32 IVOR1;
    Uns32 IVOR2;
    Uns32 IVOR3;
    Uns32 IVOR4;
    Uns32 IVOR5;
    Uns32 IVOR6;
    Uns32 IVOR7;
    Uns32 IVOR8;
    Uns32 IVOR9;
    Uns32 IVOR10;
    Uns32 IVOR11;
    Uns32 IVOR12;
    Uns32 IVOR13;
    Uns32 IVOR14;
    Uns32 IVOR15;
    Uns64 MCSRR0;
    Uns32 MCSRR1;
    Uns64 SPRG8;
    Uns32 DCDBTRL;
    Uns32 DCDBTRH;
    Uns32 ICDBTRL;
    Uns32 ICDBTRH;
} ppc32spr;

typedef enum {
    UNDEF,      // no access (- in table)
    NO,         // User Level (no in table)
    YES,        // Privileged Level (yes in table)
    HYPV        // Hypervisor Privileged
} privAccessE;

//
// 400 Encodings
//
typedef enum {
    XER      = 1,
    LR       = 8,
    CTR      = 9,
    DEC      = 22,
    SRR0     = 26,
    SRR1     = 27,
    PID      = 48,
    DECAR    = 54,
    CSRR0    = 58,
    CSRR1    = 59,
    DEAR     = 61,
    ESR      = 62,
    IVPR     = 63,
    USPGR0   = 256,
    SPRG3_1  = 259,
    SPRG4_1  = 260,
    SPRG5_1  = 261,
    SPRG6_1  = 262,
    SPRG7_1  = 263,
    TBL_1    = 268,
    TBU_1    = 269,
    SPRG0    = 272,
    SPRG1    = 273,
    SPRG2    = 274,
    SPRG3_2  = 275,
    SPRG4_2  = 276,
    SPRG5_2  = 277,
    SPRG6_2  = 278,
    SPRG7_2  = 279,
    TBL_2    = 284,
    TBU_2    = 285,
    PIR      = 286,
    PVR      = 287,
    DBSR     = 304,
    DBCR0    = 308,
    DBCR1    = 309,
    DBCR2    = 310,
    IAC1     = 312,
    IAC2     = 313,
    IAC3     = 314,
    IAC4     = 315,
    DAC1     = 316,
    DAC2     = 317,
    DVC1     = 318,
    DVC2     = 319,
    TSR      = 336,
    TCR      = 340,
    IVOR0    = 400,
    IVOR1    = 401,
    IVOR2    = 402,
    IVOR3    = 403,
    IVOR4    = 404,
    IVOR5    = 405,
    IVOR6    = 406,
    IVOR7    = 407,
    IVOR8    = 408,
    IVOR9    = 409,
    IVOR10   = 410,
    IVOR11   = 411,
    IVOR12   = 412,
    IVOR13   = 413,
    IVOR14   = 414,
    IVOR15   = 415,
    MCSRR0   = 570,
    MCSRR1   = 571,
    MCSR     = 572,
    SPRG8    = 604,
    DBSR_W   = 816,
    MMUBE0   = 820,
    MMUBE1   = 821,
    RMPD     = 825,
    MCSR_C   = 828,
    ISPCR    = 829,
    SSPCR    = 830,
    USPCR    = 831,
    PMUCC0_R = 842,
    TSR_W    = 848,
    DCESR    = 850,
    PMUCC0_RW = 858,
    IOCCR    = 860,
    IOCR1    = 861,
    IOCR2    = 862,
    PWM      = 886,
    CCR1     = 888,
    CCR2     = 889,
    DCRIPR   = 891,
    RSTCFG   = 923,
    DCDBTRL  = 924,
    DCDBTRH  = 925,
    ICDBTRL  = 926,
    ICDBTRH  = 927,
    CCR0     = 947,
    MMUCR    = 946,
    ICDBDR0  = 979,
    ICDBDR1  = 980,
    DBDR     = 1011,
} specialPurposeRegE;

typedef struct specialPurposeRegAccessPermS {
    const char *name;
    privAccessE mtspr;
    privAccessE mfspr;
    Uns8        length;
} specialPurposeRegAccessPerm;

#define SPR_ENTRY(_NAME, _MT, _MF, _LEN) \
    [_NAME] = {name:#_NAME, mtspr:_MT, mfspr:_MF, length:_LEN}

static const specialPurposeRegAccessPerm SPR_ACCESS[1024] = {
        //
        //       name       mtspr, mfspr, length
        //
        SPR_ENTRY(XER,         NO,    NO,    64),
        SPR_ENTRY(LR,          NO,    NO,    64),
        SPR_ENTRY(CTR,         NO,    NO,    64),
        SPR_ENTRY(DEC,        YES,   YES,    32),
        SPR_ENTRY(SRR0,       YES,   YES,    64),
        SPR_ENTRY(SRR1,       YES,   YES,    64),
        SPR_ENTRY(PID,        YES,   YES,    32),
        SPR_ENTRY(DECAR,      YES,   YES,    32),
        SPR_ENTRY(CSRR0,      YES,   YES,    64),
        SPR_ENTRY(CSRR1,      YES,   YES,    32),
        SPR_ENTRY(DEAR,       YES,   YES,    64),
        SPR_ENTRY(ESR,        YES,   YES,    32),
        SPR_ENTRY(IVPR,       YES,   YES,    64),
        SPR_ENTRY(SPRG3_1,  UNDEF,    NO,    64),
        SPR_ENTRY(SPRG4_1,  UNDEF,    NO,    64),
        SPR_ENTRY(SPRG5_1,  UNDEF,    NO,    64),
        SPR_ENTRY(SPRG6_1,  UNDEF,    NO,    64),
        SPR_ENTRY(SPRG7_1,  UNDEF,    NO,    64),
        SPR_ENTRY(TBL_1,    UNDEF,    NO,    64),
        SPR_ENTRY(TBU_1,    UNDEF,    NO,    32),
        SPR_ENTRY(SPRG0,      YES,   YES,    64),
        SPR_ENTRY(SPRG1,      YES,   YES,    64),
        SPR_ENTRY(SPRG2,      YES,   YES,    64),
        SPR_ENTRY(SPRG3_2,    YES,   YES,    64),
        SPR_ENTRY(SPRG4_2,    YES,   YES,    64),
        SPR_ENTRY(SPRG5_2,    YES,   YES,    64),
        SPR_ENTRY(SPRG6_2,    YES,   YES,    64),
        SPR_ENTRY(SPRG7_2,    YES,   YES,    64),
        SPR_ENTRY(TBL_2,      YES, UNDEF,    32),
        SPR_ENTRY(TBU_2,      YES, UNDEF,    32),
        SPR_ENTRY(PIR,      UNDEF,   YES,    32),
        SPR_ENTRY(PVR,      UNDEF,   YES,    32),
        SPR_ENTRY(DBSR,       YES,   YES,    32),
        SPR_ENTRY(DBCR0,      YES,   YES,    32),
        SPR_ENTRY(DBCR1,      YES,   YES,    32),
        SPR_ENTRY(DBCR2,      YES,   YES,    32),
        SPR_ENTRY(IAC1,       YES,   YES,    64),
        SPR_ENTRY(IAC2,       YES,   YES,    64),
        SPR_ENTRY(IAC3,       YES,   YES,    64),
        SPR_ENTRY(IAC4,       YES,   YES,    64),
        SPR_ENTRY(DAC1,       YES,   YES,    64),
        SPR_ENTRY(DAC2,       YES,   YES,    64),
        SPR_ENTRY(DVC1,       YES,   YES,    64),
        SPR_ENTRY(DVC2,       YES,   YES,    64),
        SPR_ENTRY(TSR,        YES,   YES,    32),
        SPR_ENTRY(TCR,        YES,   YES,    32),
        SPR_ENTRY(IVOR0,      YES,   YES,    32),
        SPR_ENTRY(IVOR1,      YES,   YES,    32),
        SPR_ENTRY(IVOR2,      YES,   YES,    32),
        SPR_ENTRY(IVOR3,      YES,   YES,    32),
        SPR_ENTRY(IVOR4,      YES,   YES,    32),
        SPR_ENTRY(IVOR5,      YES,   YES,    32),
        SPR_ENTRY(IVOR6,      YES,   YES,    32),
        SPR_ENTRY(IVOR7,      YES,   YES,    32),
        SPR_ENTRY(IVOR8,      YES,   YES,    32),
        SPR_ENTRY(IVOR9,      YES,   YES,    32),
        SPR_ENTRY(IVOR10,     YES,   YES,    32),
        SPR_ENTRY(IVOR11,     YES,   YES,    32),
        SPR_ENTRY(IVOR12,     YES,   YES,    32),
        SPR_ENTRY(IVOR13,     YES,   YES,    32),
        SPR_ENTRY(IVOR14,     YES,   YES,    32),
        SPR_ENTRY(IVOR15,     YES,   YES,    32),
        SPR_ENTRY(MCSRR0,     YES,   YES,    64),
        SPR_ENTRY(MCSRR1,     YES,   YES,    32),
        SPR_ENTRY(MCSR,       YES,   YES,    32),
        SPR_ENTRY(SPRG8,      YES,   YES,    64),
        SPR_ENTRY(DCDBTRL,  UNDEF,   YES,    32),
        SPR_ENTRY(DCDBTRH,  UNDEF,   YES,    32),
        SPR_ENTRY(ICDBTRL,  UNDEF,   YES,    32),
        SPR_ENTRY(ICDBTRH,  UNDEF,   YES,    32),
        SPR_ENTRY(CCR0,       YES,   YES,    32),
        SPR_ENTRY(CCR1,       YES,   YES,    32),
        SPR_ENTRY(CCR2,       YES,   YES,    32),
};

#endif
