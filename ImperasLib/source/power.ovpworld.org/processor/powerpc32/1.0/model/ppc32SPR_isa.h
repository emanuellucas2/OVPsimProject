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

#ifndef PPC32_SPR_ISA_H
#define PPC32_SPR_ISA_H
#include "vmi/vmiTypes.h"

typedef union {
    Uns64 reg;
    struct {
        Uns64       DPFD : 3;
        Uns64        SSE : 1;
        Uns64       RSV0 : 60;
    } bits;
} TYPE_DSCR;

typedef union {
    Uns64 reg;
    struct {
        Uns64   HTABSIZE : 5;
        Uns64       RSV1 : 13;
        Uns64    HTABORG : 42;
        Uns64       RSV0 : 4;
    } bits;
} TYPE_SDR1;

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
    Uns64 reg;
    struct {
        Uns64       RSV0 : 2;
        Uns64       CFAR : 62;
    } bits;
} TYPE_CFAR;

typedef union {
    Uns64 reg;
    struct {
        Uns64      Key31 : 2;
        Uns64      Key30 : 2;
        Uns64      Key29 : 2;
        Uns64      Key28 : 2;
        Uns64      Key27 : 2;
        Uns64      Key26 : 2;
        Uns64      Key25 : 2;
        Uns64      Key24 : 2;
        Uns64      Key23 : 2;
        Uns64      Key22 : 2;
        Uns64      Key21 : 2;
        Uns64      Key20 : 2;
        Uns64      Key19 : 2;
        Uns64      Key18 : 2;
        Uns64      Key17 : 2;
        Uns64      Key16 : 2;
        Uns64      Key15 : 2;
        Uns64      Key14 : 2;
        Uns64      Key13 : 2;
        Uns64      Key12 : 2;
        Uns64      Key11 : 2;
        Uns64      Key10 : 2;
        Uns64       Key9 : 2;
        Uns64       Key8 : 2;
        Uns64       Key7 : 2;
        Uns64       Key6 : 2;
        Uns64       Key5 : 2;
        Uns64       Key4 : 2;
        Uns64       Key3 : 2;
        Uns64       Key2 : 2;
        Uns64       Key1 : 2;
        Uns64       Key0 : 2;
    } bits;
} TYPE_AMR;

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
    Uns32 reg;
    struct {
        Uns32        RUN : 1;
        Uns32       RSV0 : 31;
    } bits;
} TYPE_CTRL;

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
        Uns32        RID : 6;
        Uns32        RSV : 25;
        Uns32          E : 1;
    } bits;
} TYPE_EAR;

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
    Uns64 reg;
    struct {
        Uns64        RMO : 60;
        Uns64       RSV0 : 4;
    } bits;
} TYPE_RMOR;

typedef union {
    Uns64 reg;
    struct {
        Uns64       HRMO : 60;
        Uns64       RSV0 : 4;
    } bits;
} TYPE_HRMOR;

typedef union {
    Uns64 reg;
    struct {
        Uns64       RSV0 : 2;
        Uns64      HSRR0 : 62;
    } bits;
} TYPE_HSRR0;

typedef union {
    Uns64 reg;
    struct {
        Uns64      HDICE : 1;
        Uns64       RSV5 : 1;
        Uns64       LPES : 2;
        Uns64       RSV4 : 5;
        Uns64         TC : 1;
        Uns64       RSV3 : 1;
        Uns64        MER : 1;
        Uns64       PECE : 3;
        Uns64       RSV2 : 10;
        Uns64        ILE : 1;
        Uns64       RMLS : 4;
        Uns64       RSV1 : 17;
        Uns64     VRMASD : 5;
        Uns64       DPFD : 3;
        Uns64       RSV0 : 6;
        Uns64         VC : 3;
    } bits;
} TYPE_LPCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       LPID : 32;
    } bits;
} TYPE_LPIDR;

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
    Uns64 reg;
    struct {
        Uns64       V204 : 1;
        Uns64       RSV0 : 62;
        Uns64     VECTOR : 1;
    } bits;
} TYPE_PCR;

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
        Uns64       ATBL : 32;
        Uns64       ATBU : 32;
    } bits;
} TYPE_ATB;

typedef union {
    Uns32 reg;
    struct {
        Uns32         NV : 12;
        Uns32       RSV1 : 4;
        Uns32       ESEL : 12;
        Uns32     TLBSEL : 2;
        Uns32       RSV0 : 2;
    } bits;
} TYPE_MAS0;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV1 : 8;
        Uns32      TSIZE : 4;
        Uns32         TS : 1;
        Uns32       RSV0 : 3;
        Uns32        TID : 14;
        Uns32      IPROT : 1;
        Uns32          V : 1;
    } bits;
} TYPE_MAS1;

typedef union {
    Uns64 reg;
    struct {
        Uns64          E : 1;
        Uns64          G : 1;
        Uns64          M : 1;
        Uns64          I : 1;
        Uns64          W : 1;
        Uns64        VLE : 1;
        Uns64        ACM : 2;
        Uns64       RSV0 : 4;
        Uns64        EPN : 52;
    } bits;
} TYPE_MAS2;

typedef union {
    Uns32 reg;
    struct {
        Uns32         SR : 1;
        Uns32         UR : 1;
        Uns32         SW : 1;
        Uns32         UW : 1;
        Uns32         SX : 1;
        Uns32         UX : 1;
        Uns32          U : 4;
        Uns32       RSV0 : 2;
        Uns32       RPNL : 20;
    } bits;
} TYPE_MAS3;

typedef union {
    Uns32 reg;
    struct {
        Uns32         ED : 1;
        Uns32         GD : 1;
        Uns32         MD : 1;
        Uns32         ID : 1;
        Uns32         WD : 1;
        Uns32       VLED : 1;
        Uns32       ACMD : 2;
        Uns32     TSIZED : 4;
        Uns32       RSV2 : 4;
        Uns32    TIDSELD : 4;
        Uns32       RSV1 : 8;
        Uns32     TLBSEL : 2;
        Uns32       RSV0 : 2;
    } bits;
} TYPE_MAS4;

typedef union {
    Uns32 reg;
    struct {
        Uns32        SAS : 1;
        Uns32       RSV1 : 15;
        Uns32      SPID0 : 14;
        Uns32       RSV0 : 2;
    } bits;
} TYPE_MAS6;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RPNU : 32;
    } bits;
} TYPE_MAS7;

typedef union {
    Uns32 reg;
    struct {
        Uns32        PID : 14;
        Uns32       RSV0 : 18;
    } bits;
} TYPE_PID1;

typedef union {
    Uns32 reg;
    struct {
        Uns32        PID : 14;
        Uns32       RSV0 : 18;
    } bits;
} TYPE_PID2;

typedef union {
    Uns32 reg;
    struct {
        Uns32     NENTRY : 12;
        Uns32       RSV0 : 2;
        Uns32      AVAIL : 1;
        Uns32      IPROT : 1;
        Uns32    MAXSIZE : 4;
        Uns32    MINSIZE : 4;
        Uns32      ASSOC : 8;
    } bits;
} TYPE_TLB0CFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32     NENTRY : 12;
        Uns32       RSV0 : 2;
        Uns32      AVAIL : 1;
        Uns32      IPROT : 1;
        Uns32    MAXSIZE : 4;
        Uns32    MINSIZE : 4;
        Uns32      ASSOC : 8;
    } bits;
} TYPE_TLB1CFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32     NENTRY : 12;
        Uns32       RSV0 : 2;
        Uns32      AVAIL : 1;
        Uns32      IPROT : 1;
        Uns32    MAXSIZE : 4;
        Uns32    MINSIZE : 4;
        Uns32      ASSOC : 8;
    } bits;
} TYPE_TLB2CFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32     NENTRY : 12;
        Uns32       RSV0 : 2;
        Uns32      AVAIL : 1;
        Uns32      IPROT : 1;
        Uns32    MAXSIZE : 4;
        Uns32    MINSIZE : 4;
        Uns32      ASSOC : 8;
    } bits;
} TYPE_TLB3CFG;

typedef union {
    Uns64 reg;
    struct {
        Uns64    IMPDEP1 : 20;
        Uns64       RSV1 : 30;
        Uns64        PRI : 3;
        Uns64       RSV0 : 11;
    } bits;
} TYPE_PPR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       EPID : 14;
        Uns32       RSV0 : 16;
        Uns32        EAS : 1;
        Uns32        EPR : 1;
    } bits;
} TYPE_EPLC;

typedef union {
    Uns32 reg;
    struct {
        Uns32       EPID : 14;
        Uns32       RSV0 : 16;
        Uns32        EAS : 1;
        Uns32        EPR : 1;
    } bits;
} TYPE_EPSC;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV2 : 1;
        Uns32    TLB0_FI : 1;
        Uns32    TLB1_FI : 1;
        Uns32       RSV1 : 2;
        Uns32    TLB2_FI : 1;
        Uns32    TLB3_FI : 1;
        Uns32    TLB0_PS : 4;
        Uns32    TLB1_PS : 4;
        Uns32    TLB2_PS : 4;
        Uns32    TLB3_PS : 4;
        Uns32       RSV0 : 9;
    } bits;
} TYPE_MMUCSR0;

typedef union {
    Uns64 reg;
    struct {
        Uns64         DR : 1;
        Uns64         DW : 1;
        Uns64         BT : 1;
        Uns64        DAB : 61;
    } bits;
} TYPE_DABR;

typedef union {
    Uns64 reg;
    struct {
        Uns64        PRO : 1;
        Uns64        PNH : 1;
        Uns64        HYP : 1;
        Uns64        BTI : 1;
        Uns64       RSV0 : 61;
    } bits;
} TYPE_DABRX;

typedef union {
    Uns32 reg;
    struct {
        Uns32       MAVN : 2;
        Uns32      NTLBS : 2;
        Uns32       RSV2 : 2;
        Uns32    PIDSIZE : 5;
        Uns32      NPIDS : 4;
        Uns32       RSV1 : 2;
        Uns32     RASIZE : 7;
        Uns32       RSV0 : 8;
    } bits;
} TYPE_MMUCFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32        SAT : 1;
        Uns32       RSV1 : 15;
        Uns32         NJ : 1;
        Uns32       RSV0 : 15;
    } bits;
} TYPE_VSCR;

typedef union {
    Uns64 reg;
    struct {
        Uns64         LE : 1;
        Uns64         RI : 1;
        Uns64        PMM : 1;
        Uns64       RSV5 : 1;
        Uns64         DR : 1;
        Uns64         IR : 1;
        Uns64       RSV4 : 2;
        Uns64        FE1 : 1;
        Uns64         BE : 1;
        Uns64         SE : 1;
        Uns64        FE0 : 1;
        Uns64         ME : 1;
        Uns64         FP : 1;
        Uns64         PR : 1;
        Uns64         EE : 1;
        Uns64       RSV3 : 1;
        Uns64       RSV2 : 8;
        Uns64        VEC : 1;
        Uns64       RSV1 : 34;
        Uns64         HV : 1;
        Uns64       RSV0 : 2;
        Uns64         SF : 1;
    } bits;
} TYPE_MSR;

typedef struct ppc32sprS {
    TYPE_MSR MSR, MSR_rmask, MSR_wmask;
    TYPE_DSCR DSCR, DSCR_rmask, DSCR_wmask;
    Uns32 DSISR;
    Uns64 DAR;
    Uns32 DEC;
    Uns64 DEC_tmr;
    TYPE_SDR1 SDR1, SDR1_rmask, SDR1_wmask;
    TYPE_SRR0 SRR0, SRR0_rmask, SRR0_wmask;
    TYPE_SRR1 SRR1, SRR1_rmask, SRR1_wmask;
    TYPE_CFAR CFAR, CFAR_rmask, CFAR_wmask;
    TYPE_AMR AMR, AMR_rmask, AMR_wmask;
    TYPE_PID0 PID0, PID0_rmask, PID0_wmask;
    Uns32 DECAR;
    Uns64 CSRR0;
    Uns32 CSRR1;
    Uns64 DEAR;
    TYPE_ESR ESR, ESR_rmask, ESR_wmask;
    TYPE_IVPR IVPR, IVPR_rmask, IVPR_wmask;
    TYPE_CTRL CTRL, CTRL_rmask, CTRL_wmask;
    Uns32 VRSAVE;
    Uns64 SPRG0;
    Uns64 SPRG1;
    Uns64 SPRG2;
    Uns64 SPRG3;
    Uns64 SPRG4;
    Uns64 SPRG5;
    Uns64 SPRG6;
    Uns64 SPRG7;
    TYPE_TB TB, TB_rmask, TB_wmask;
    TYPE_TBU TBU, TBU_rmask, TBU_wmask;
    TYPE_EAR EAR, EAR_rmask, EAR_wmask;
    TYPE_PIR PIR, PIR_rmask, PIR_wmask;
    TYPE_PVR PVR, PVR_rmask, PVR_wmask;
    Uns64 HSPRG[2];
    TYPE_DBSR DBSR, DBSR_rmask, DBSR_wmask;
    Uns32 HDSISR;
    Uns64 HDAR;
    TYPE_DBCR0 DBCR0, DBCR0_rmask, DBCR0_wmask;
    Uns64 SPURR;
    Uns64 PURR;
    TYPE_DBCR1 DBCR1, DBCR1_rmask, DBCR1_wmask;
    Uns32 HDEC;
    TYPE_DBCR2 DBCR2, DBCR2_rmask, DBCR2_wmask;
    TYPE_RMOR RMOR, RMOR_rmask, RMOR_wmask;
    Uns64 IAC1;
    Uns64 IAC2;
    Uns64 IAC3;
    Uns64 IAC4;
    TYPE_HRMOR HRMOR, HRMOR_rmask, HRMOR_wmask;
    TYPE_HSRR0 HSRR0, HSRR0_rmask, HSRR0_wmask;
    Uns64 HSRR1;
    Uns64 DAC1;
    Uns64 DAC2;
    TYPE_LPCR LPCR, LPCR_rmask, LPCR_wmask;
    Uns64 DVC1;
    Uns64 DVC2;
    TYPE_LPIDR LPIDR, LPIDR_rmask, LPIDR_wmask;
    TYPE_TSR TSR, TSR_rmask, TSR_wmask;
    Uns64 HMER;
    Uns64 HMEER;
    TYPE_PCR PCR, PCR_rmask, PCR_wmask;
    Uns32 HEIR;
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
    TYPE_ATB ATB, ATB_rmask, ATB_wmask;
    Uns32 IVOR32;
    Uns32 IVOR33;
    Uns32 IVOR34;
    Uns32 IVOR35;
    Uns32 IVOR36;
    Uns32 IVOR37;
    Uns64 MCSRR0;
    Uns32 MCSRR1;
    Uns64 MCSR;
    Uns64 DSRR0;
    Uns32 DSRR1;
    Uns64 SPRG8;
    Uns64 SPRG9;
    TYPE_MAS0 MAS0, MAS0_rmask, MAS0_wmask;
    TYPE_MAS1 MAS1, MAS1_rmask, MAS1_wmask;
    TYPE_MAS2 MAS2, MAS2_rmask, MAS2_wmask;
    TYPE_MAS3 MAS3, MAS3_rmask, MAS3_wmask;
    TYPE_MAS4 MAS4, MAS4_rmask, MAS4_wmask;
    TYPE_MAS6 MAS6, MAS6_rmask, MAS6_wmask;
    TYPE_MAS7 MAS7, MAS7_rmask, MAS7_wmask;
    TYPE_PID1 PID1, PID1_rmask, PID1_wmask;
    TYPE_PID2 PID2, PID2_rmask, PID2_wmask;
    TYPE_TLB0CFG TLB0CFG, TLB0CFG_rmask, TLB0CFG_wmask;
    TYPE_TLB1CFG TLB1CFG, TLB1CFG_rmask, TLB1CFG_wmask;
    TYPE_TLB2CFG TLB2CFG, TLB2CFG_rmask, TLB2CFG_wmask;
    TYPE_TLB3CFG TLB3CFG, TLB3CFG_rmask, TLB3CFG_wmask;
    Uns32 EPR;
    Uns64 perf_mon[16];
    TYPE_PPR PPR, PPR_rmask, PPR_wmask;
    Uns32 DCDBTRL;
    Uns32 DCDBTRH;
    Uns32 ICDBTRL;
    Uns32 ICDBTRH;
    TYPE_EPLC EPLC, EPLC_rmask, EPLC_wmask;
    TYPE_EPSC EPSC, EPSC_rmask, EPSC_wmask;
    Uns32 ICDBDR;
    TYPE_MMUCSR0 MMUCSR0, MMUCSR0_rmask, MMUCSR0_wmask;
    TYPE_DABR DABR, DABR_rmask, DABR_wmask;
    TYPE_DABRX DABRX, DABRX_rmask, DABRX_wmask;
    TYPE_MMUCFG MMUCFG, MMUCFG_rmask, MMUCFG_wmask;
    TYPE_VSCR VSCR, VSCR_rmask, VSCR_wmask;
    Uns64 Accumulator;
} ppc32spr;

typedef enum {
    UNDEF,      // no access (- in table)
    NO,         // User Level (no in table)
    YES,        // Privileged Level (yes in table)
    HYPV        // Hypervisor Privileged
} privAccessE;

typedef enum {
    XER      = 1,   // Special registers not part of SPR
    LR       = 8,   // Special registers not part of SPR
    CTR      = 9,   // Special registers not part of SPR
    DSCR     = 17,
    DSISR    = 18,
    DAR      = 19,
    DEC      = 22,
    SRR0     = 26,
    SRR1     = 27,
    CFAR     = 28,
    AMR      = 29,
    PID      = 48,
    DECAR    = 54,
    CSRR0    = 58,
    CSRR1    = 59,
    DEAR     = 61,
    ESR      = 62,
    IVPR     = 63,
    VRSAVE   = 256,
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
    EAR      = 282,
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
//  SPEFSCR  = 512,
    ATBL     = 526,
    ATBU     = 527,
    IVOR32   = 528,
    IVOR33   = 529,
    IVOR34   = 530,
    IVOR35   = 531,
    IVOR36   = 532,
    IVOR37   = 533,
    MCSSR0   = 570,
    MCSSR1   = 571,
    MCSSR    = 572,
    DSSR0    = 574,
    DSSR1    = 575,
    SPRG8    = 604,
    SPRG9    = 605,
    MAS0     = 624,
    MAS1     = 625,
    MAS2     = 626,
    MAS3     = 627,
    MAS4     = 628,
    MAS6     = 630,
    PID1     = 633,
    PID2     = 634,
    TLB0CFG  = 688,
    TLB1CFG  = 689,
    TLB2CFG  = 690,
    TLB3CFG  = 691,
    EPR      = 702,
    DCDBTRL  = 924,
    DCDBTRH  = 925,
    ICDBTRL  = 926,
    ICDBTRH  = 927,
    MAS7     = 944,
    EPLC     = 947,
    EPSC     = 948,
    ICDBDR   = 979,
    MMUCSR0  = 1012,
    MMUCFG   = 1015,
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
        SPR_ENTRY(XER,         NO,    NO,    64),  // These registers are not actually part ofthe SPR block
        SPR_ENTRY(LR,          NO,    NO,    64),  // These registers are not actually part ofthe SPR block
        SPR_ENTRY(CTR,         NO,    NO,    64),  // These registers are not actually part ofthe SPR block
        SPR_ENTRY(DSCR,       YES,   YES,    64),
        SPR_ENTRY(DSISR,      YES,   YES,    32),
        SPR_ENTRY(DAR,        YES,   YES,    64),
        SPR_ENTRY(DEC,        YES,   YES,    32),
        SPR_ENTRY(SRR0,       YES,   YES,    64),
//      SPR_ENTRY(SDR1,      HYPV,  HYPV,    64),
        SPR_ENTRY(SRR1,       YES,   YES,    64),
        SPR_ENTRY(CFAR,       YES,   YES,    64),
        SPR_ENTRY(AMR,        YES,   YES,    64),
        SPR_ENTRY(PID,        YES,   YES,    32),
        SPR_ENTRY(DECAR,      YES,   YES,    32),
        SPR_ENTRY(CSRR0,      YES,   YES,    64),
        SPR_ENTRY(CSRR1,      YES,   YES,    32),
        SPR_ENTRY(DEAR,       YES,   YES,    64),
        SPR_ENTRY(ESR,        YES,   YES,    32),
        SPR_ENTRY(IVPR,       YES,   YES,    64),
        SPR_ENTRY(VRSAVE,      NO,    NO,    64),
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
        SPR_ENTRY(EAR,       HYPV,  HYPV,    32),
        SPR_ENTRY(TBL_2,      YES, UNDEF,    32),
        SPR_ENTRY(TBU_2,      YES, UNDEF,    32),
//      SPR_ENTRY(TBU40,     HYPV, UNDEF,    64),
        SPR_ENTRY(PIR,      UNDEF,   YES,    32),
        SPR_ENTRY(PVR,      UNDEF,   YES,    32),
//      SPR_ENTRY(HSPRG0,    HYPV,  HYPV,    64),
        SPR_ENTRY(DBSR,       YES,   YES,    32),
//      SPR_ENTRY(HSPRG1,    HYPV,  HYPV,    64),
//      SPR_ENTRY(HDSISR,    HYPV,  HYPV,    32),
//      SPR_ENTRY(HDAR,      HYPV,  HYPV,    64),
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
//      SPR_ENTRY(SPEFSCR,     NO,    NO,    32),
        SPR_ENTRY(ATBL,     UNDEF,    NO,    64),
        SPR_ENTRY(ATBU,     UNDEF,    NO,    32),
        SPR_ENTRY(IVOR32,     YES,   YES,    32),
        SPR_ENTRY(IVOR33,     YES,   YES,    32),
        SPR_ENTRY(IVOR34,     YES,   YES,    32),
        SPR_ENTRY(IVOR35,     YES,   YES,    32),
        SPR_ENTRY(IVOR36,     YES,   YES,    32),
        SPR_ENTRY(IVOR37,     YES,   YES,    32),
        SPR_ENTRY(MCSSR0,     YES,   YES,    64),
        SPR_ENTRY(MCSSR1,     YES,   YES,    32),
        SPR_ENTRY(MCSSR,      YES,   YES,    32),
        SPR_ENTRY(DSSR0,      YES,   YES,    64),
        SPR_ENTRY(DSSR1,      YES,   YES,    32),
        SPR_ENTRY(SPRG8,      YES,   YES,    64),
        SPR_ENTRY(SPRG9,      YES,   YES,    64),
        SPR_ENTRY(MAS0,       YES,   YES,    32),
        SPR_ENTRY(MAS1,       YES,   YES,    32),
        SPR_ENTRY(MAS2,       YES,   YES,    64),
        SPR_ENTRY(MAS3,       YES,   YES,    32),
        SPR_ENTRY(MAS4,       YES,   YES,    32),
        SPR_ENTRY(MAS6,       YES,   YES,    32),
        SPR_ENTRY(PID1,       YES,   YES,    32),
        SPR_ENTRY(PID2,       YES,   YES,    32),
        SPR_ENTRY(TLB0CFG,    YES,   YES,    32),
        SPR_ENTRY(TLB1CFG,    YES,   YES,    32),
        SPR_ENTRY(TLB2CFG,    YES,   YES,    32),
        SPR_ENTRY(TLB3CFG,    YES,   YES,    32),
        SPR_ENTRY(EPR,      UNDEF,   YES,    32),
        SPR_ENTRY(DCDBTRL,  UNDEF,   YES,    32),
        SPR_ENTRY(DCDBTRH,  UNDEF,   YES,    32),
        SPR_ENTRY(ICDBTRL,  UNDEF,   YES,    32),
        SPR_ENTRY(ICDBTRH,  UNDEF,   YES,    32),
        SPR_ENTRY(MAS7,       YES,   YES,    32),
        SPR_ENTRY(EPLC,       YES,   YES,    32),
        SPR_ENTRY(EPSC,       YES,   YES,    32),
        SPR_ENTRY(ICDBDR,   UNDEF,   YES,    32),
        SPR_ENTRY(MMUCSR0,    YES,   YES,    32),
        SPR_ENTRY(MMUCFG,     YES,   YES,    32),
};

#endif
