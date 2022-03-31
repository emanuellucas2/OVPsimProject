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

#ifndef V850_STRUCTURE_H
#define V850_STRUCTURE_H

#include "vmi/vmiTypes.h"
#include "v850TypeRefs.h"
#include "v850Variant.h"
#include "v850Config.h"
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

#define V850_DISASSEMBLE_MASK 0x00000001
#define V850_DEBUG_MPU_MASK   0x00000002
#define V850_DISASSEMBLE(_P) ((_P)->flags & V850_DISASSEMBLE_MASK)
#define V850_DEBUG_MPU(_P)   ((_P)->flags & V850_DEBUG_MPU_MASK)

// decoder callback function to decode instruction at the passed address
#define V850_DECODER_FN(_NAME) void _NAME ( \
    v850P v850, \
    Uns32 thisPC, \
    v850InstructionInfoP info \
)
typedef V850_DECODER_FN((*v850DecoderFn));

typedef enum v850ModeS {
    RH850_M_SUPERVISOR,
    RH850_M_USER,
    RH850_M_SUPERVISOR_MPU,
    RH850_M_USER_MPU,
    RH850_M_LAST
} v850Mode;

typedef enum v850ExceptionsS {
    v850_E_reset,

    v850_E_nmi0,
    v850_E_nmi1,
    v850_E_nmi2,
    v850_E_intp,
    v850_E_fetrap,
    v850_E_trap0,
    v850_E_trap1,
    v850_E_ilgop,
    v850_E_rie,

    v850_E_LAST
} v850Exception;

typedef enum rh850ExceptionsS {
    rh850_E_reset = v850_E_reset,
    rh850_E_syserr,
    rh850_E_fetrap,
    rh850_E_trap0,
    rh850_E_trap1,
    rh850_E_rie,
    rh850_E_fpp,
    rh850_E_fpi,
    rh850_E_ucpop,
    rh850_E_mip,
    rh850_E_mdp,
    rh850_E_pie,
    rh850_E_debug,
    rh850_E_mae,
    rh850_E_fenmi,
    rh850_E_feint,
    rh850_E_eiint,
    rh850_E_syscall,

    rh850_E_LAST
} rh850Exception;

typedef enum v850DisableE {
    V850_ACTIVE      = 0x0000,    // processor active
    V850_RESET       = 0x0001,    // halted by reset high
    V850_STOP        = 0x0002,    // stopped by external debugger
} v850Disable;

typedef enum v850NotifyE {
    V850_NOTIFY_NULL  = 0x00000000,    // Null condition
    V850_NOTIFY_FPEXC = 0x00000001,    // Floating Point Exception
} v850Notify;

typedef struct v850NetPortS *v850NetPortP, **v850NetPortPP;
typedef struct v850NetValueS {
    Uns32 intp; // Input
    Uns32 nmi0; // Input
    Uns32 nmi1; // Input
    Uns32 nmi2; // Input
    Uns32 reset; // Input
    Uns32 mireti; // Output
    Uns32 intack; // Output
} v850NetValue;

typedef union {
    Uns32 reg;
    struct {
        Uns32       EIWR : 32;
    };
} TYPE_SPR_EIWR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       FEWR : 32;
    };
} TYPE_SPR_FEWR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       DBWR : 32;
    };
} TYPE_SPR_DBWR;

typedef union {
    Uns32 reg;
    struct {
        Uns32        BNK : 8;
        Uns32        GRP : 8;
        Uns32       RSV0 : 16;
    };
} TYPE_SPR_BSEL;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32         PC : 28;
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_EIPC;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32         PC : 28;
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_FEPC;

//
// This is now an alias to the EICC and FECC registers
//
typedef union {
    Uns32 reg;
    struct {
        Uns32       EICC : 16;
        Uns32       FECC : 16;
    };
} TYPE_SPR_ECR;

typedef union {
    Uns32 reg;
    struct {            // Common Fields
        Uns32          Z : 1;
        Uns32          S : 1;
        Uns32         OV : 1;
        Uns32         CY : 1;
        Uns32        SAT : 1;
        Uns32         ID : 1;
        Uns32         EP : 1;
        Uns32         NP : 1;
        Uns32       RSV0 : 1;
    };
    struct {            // V Fields
        Uns32      _PAD0 : 9;
        Uns32         SE : 1;
        Uns32         SB : 1;
        Uns32         SS : 1;
        Uns32     V_RSV1 : 4;
        Uns32        IMP : 1;
        Uns32        DMP : 1;
        Uns32        NPV : 1;
        Uns32     V_RSV2 : 1;
    };
    struct {            // RH Fields
        Uns32      _PAD1 : 9;
        Uns32     _DEBUG : 3;
        Uns32     R_RSV1 : 3;
        Uns32        EBV : 1;
        Uns32         CU : 3;
        Uns32     R_RSV2 : 11;
        Uns32         UM : 1;
        Uns32     R_RSV3 : 1;
    };
} TYPE_SPR_PSW;

typedef union {
    Uns32 reg;
    struct {
        Uns32     ECC : 16;
//        Uns32      UR : 1;
//        Uns32      UW : 1;
//        Uns32      UX : 1;
//        Uns32      SR : 1;
//        Uns32      SW : 1;
//        Uns32      SX : 1;
//        Uns32     RMW : 1;
//        Uns32      BL : 1;
//        Uns32      MS : 1;
    };
} TYPE_SPR_EIIC;

typedef union {
    Uns32 reg;
    struct {
        Uns32     ECC : 16;
        Uns32      UR : 1;
        Uns32      UW : 1;
        Uns32      UX : 1;
        Uns32      SR : 1;
        Uns32      SW : 1;
        Uns32      SX : 1;
        Uns32     RMW : 1;
        Uns32      BL : 1;
        Uns32      MS : 1;
    };
} TYPE_SPR_FEIC;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_DBIC;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32         PC : 28;
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_CTPC;

typedef union {
    Uns32 reg;
    struct {
        Uns32          Z : 1;
        Uns32          S : 1;
        Uns32         OV : 1;
        Uns32         CY : 1;
        Uns32        SAT : 1;
        Uns32         ID : 1;
        Uns32         EP : 1;
        Uns32         NP : 1;
        Uns32       RSV0 : 1;
        Uns32         SE : 1;
        Uns32         SB : 1;
        Uns32         SS : 1;
        Uns32       RSV1 : 4;
        Uns32        IMP : 1;
        Uns32        DMP : 1;
        Uns32        NPV : 1;
        Uns32       RSV2 : 1;
    };
} TYPE_SPR_CTPSW;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32         PC : 28;
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_DBPC;

typedef union {
    Uns32 reg;
    struct {
        Uns32          Z : 1;
        Uns32          S : 1;
        Uns32         OV : 1;
        Uns32         CY : 1;
        Uns32        SAT : 1;
        Uns32         ID : 1;
        Uns32         EP : 1;
        Uns32         NP : 1;
        Uns32       RSV0 : 1;
        Uns32         SE : 1;
        Uns32         SB : 1;
        Uns32         SS : 1;
        Uns32       RSV1 : 4;
        Uns32        IMP : 1;
        Uns32        DMP : 1;
        Uns32        NPV : 1;
        Uns32       RSV2 : 1;
    };
} TYPE_SPR_DBPSW;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32         PC : 28;
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_CTBP;

typedef union {
    Uns32 reg;
    struct {
        Uns32         DM : 1;
        Uns32         AT : 1;
        Uns32         MT : 1;
        Uns32         CM : 1;
        Uns32         T0 : 1;
        Uns32         T1 : 1;
        Uns32         IN : 1;
        Uns32         SE : 1;
        Uns32         AE : 1;
        Uns32         MA : 1;
        Uns32         CE : 1;
        Uns32         CS : 1;
        Uns32         RE : 1;
        Uns32         SQ : 1;
    };
} TYPE_SPR_DIR;

typedef union {
    Uns32 reg;
    struct {
        Uns32        SET : 1;
    };
} TYPE_SPR_SW_CTL;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RINT : 1;
        Uns32       RSV0 : 31;
    };
} TYPE_SPR_SW_CFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 13;
        Uns32 BITS_28_TO_13 : 16;
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_SW_BASE;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RINT : 1;
        Uns32       RSV0 : 31;
    };
} TYPE_SPR_EH_CFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32          RSV0 : 13;
        Uns32 BITS_28_TO_13 : 16;
        Uns32          RSV1 : 3;
    };
} TYPE_SPR_EH_BASE;

typedef union {
    Uns32 reg;
    struct {
        Uns32          RSV0 : 13;
        Uns32 BITS_28_TO_13 : 16;
        Uns32          RSV1 : 3;
    };
} TYPE_SPR_EH_RESET;

typedef union {
    Uns32 reg;
    struct {
        Uns32        MPE : 1;
        Uns32        AUE : 1;
        Uns32        SPS : 1;
        Uns32       RSV0 : 5;
    }; // V850
    struct {
        Uns32       MPE_ : 1;
        Uns32        SVP : 1;
        Uns32      RSV0_ : 6;   // Reserved - should be set to 0
        Uns32         DR : 1;
        Uns32         DW : 1;
        Uns32         DX : 1;
    }; // RH850
} TYPE_SPR_MPM;

typedef union {
    Uns32 reg;
    struct {
        Uns32       ALDS : 1;
    };
} TYPE_SPR_MPC;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_TID;

typedef union {
    Uns32 reg;
    struct {
        Uns32       PPC0 : 1;
        Uns32       PPC1 : 1;
        Uns32       PPC2 : 1;
        Uns32       PPC3 : 1;
        Uns32       PPC4 : 1;
        Uns32       PPC5 : 1;
        Uns32       PPC6 : 1;
        Uns32       PPC7 : 1;
        Uns32       PPC8 : 1;
        Uns32       PPC9 : 1;
        Uns32      PPC10 : 1;
        Uns32      PPC11 : 1;
        Uns32      PPC12 : 1;
        Uns32      PPC13 : 1;
        Uns32      PPC14 : 1;
        Uns32      PPC15 : 1;
        Uns32      PPC16 : 1;
        Uns32      PPC17 : 1;
        Uns32      PPC18 : 1;
        Uns32      PPC19 : 1;
        Uns32      PPC20 : 1;
        Uns32      PPC21 : 1;
        Uns32      PPC22 : 1;
        Uns32      PPC23 : 1;
        Uns32      PPC24 : 1;
        Uns32      PPC25 : 1;
        Uns32      PPC26 : 1;
        Uns32      PPC27 : 1;
        Uns32      PPC28 : 1;
        Uns32      PPC29 : 1;
        Uns32      PPC30 : 1;
        Uns32      PPC31 : 1;
    };
} TYPE_SPR_PPC;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DCE : 1;
        Uns32        EXE : 1;
        Uns32       RSV0 : 2;
        Uns32       RSV1 : 4;
        Uns32       DCM0 : 1;
        Uns32       DCM1 : 1;
        Uns32       DCM2 : 1;
        Uns32       DCM3 : 1;
        Uns32       DCM4 : 1;
        Uns32       DCM5 : 1;
        Uns32       DCM6 : 1;
        Uns32       DCM7 : 1;
    };
} TYPE_SPR_DCC0;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_DCV0;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DCE : 1;
        Uns32        EXE : 1;
        Uns32       RSV0 : 2;
        Uns32       RSV1 : 4;
        Uns32       DCM0 : 1;
        Uns32       DCM1 : 1;
        Uns32       DCM2 : 1;
        Uns32       DCM3 : 1;
        Uns32       DCM4 : 1;
        Uns32       DCM5 : 1;
        Uns32       DCM6 : 1;
        Uns32       DCM7 : 1;
    };
} TYPE_SPR_DCC1;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_DCV1;

typedef union {
    Uns32 reg;
    struct {
        Uns32        IPE : 1;
        Uns32        IPX : 1;
        Uns32        IPR : 1;
        Uns32       RSV0 : 1;
        Uns32        IPS : 1;
        Uns32        IPT : 1;
        Uns32       RSV1 : 1;
        Uns32      IPAL7 : 1;
        Uns32      IPAL8 : 1;
        Uns32      IPAL9 : 1;
        Uns32     IPAL10 : 1;
        Uns32     IPAL11 : 1;
        Uns32     IPAL12 : 1;
        Uns32     IPAL13 : 1;
        Uns32     IPAL14 : 1;
        Uns32     IPAL15 : 1;
        Uns32     IPAL16 : 1;
        Uns32     IPAL17 : 1;
        Uns32     IPAL18 : 1;
        Uns32     IPAL19 : 1;
        Uns32     IPAL20 : 1;
        Uns32     IPAL21 : 1;
        Uns32     IPAL22 : 1;
        Uns32     IPAL23 : 1;
        Uns32     IPAL24 : 1;
        Uns32     IPAL25 : 1;
        Uns32     IPAL26 : 1;
        Uns32     IPAL27 : 1;
        Uns32     IPAL28 : 1;
    };
} TYPE_SPR_IPA0L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      IPAU7 : 1;
        Uns32      IPAU8 : 1;
        Uns32      IPAU9 : 1;
        Uns32     IPAU10 : 1;
        Uns32     IPAU11 : 1;
        Uns32     IPAU12 : 1;
        Uns32     IPAU13 : 1;
        Uns32     IPAU14 : 1;
        Uns32     IPAU15 : 1;
        Uns32     IPAU16 : 1;
        Uns32     IPAU17 : 1;
        Uns32     IPAU18 : 1;
        Uns32     IPAU19 : 1;
        Uns32     IPAU20 : 1;
        Uns32     IPAU21 : 1;
        Uns32     IPAU22 : 1;
        Uns32     IPAU23 : 1;
        Uns32     IPAU24 : 1;
        Uns32     IPAU25 : 1;
        Uns32     IPAU26 : 1;
        Uns32     IPAU27 : 1;
        Uns32     IPAU28 : 1;
    };
} TYPE_SPR_IPA0U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        IPE : 1;
        Uns32        IPX : 1;
        Uns32        IPR : 1;
        Uns32       RSV0 : 1;
        Uns32        IPS : 1;
        Uns32        IPT : 1;
        Uns32       RSV1 : 1;
        Uns32      IPAL7 : 1;
        Uns32      IPAL8 : 1;
        Uns32      IPAL9 : 1;
        Uns32     IPAL10 : 1;
        Uns32     IPAL11 : 1;
        Uns32     IPAL12 : 1;
        Uns32     IPAL13 : 1;
        Uns32     IPAL14 : 1;
        Uns32     IPAL15 : 1;
        Uns32     IPAL16 : 1;
        Uns32     IPAL17 : 1;
        Uns32     IPAL18 : 1;
        Uns32     IPAL19 : 1;
        Uns32     IPAL20 : 1;
        Uns32     IPAL21 : 1;
        Uns32     IPAL22 : 1;
        Uns32     IPAL23 : 1;
        Uns32     IPAL24 : 1;
        Uns32     IPAL25 : 1;
        Uns32     IPAL26 : 1;
        Uns32     IPAL27 : 1;
        Uns32     IPAL28 : 1;
    };
} TYPE_SPR_IPA1L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      IPAU7 : 1;
        Uns32      IPAU8 : 1;
        Uns32      IPAU9 : 1;
        Uns32     IPAU10 : 1;
        Uns32     IPAU11 : 1;
        Uns32     IPAU12 : 1;
        Uns32     IPAU13 : 1;
        Uns32     IPAU14 : 1;
        Uns32     IPAU15 : 1;
        Uns32     IPAU16 : 1;
        Uns32     IPAU17 : 1;
        Uns32     IPAU18 : 1;
        Uns32     IPAU19 : 1;
        Uns32     IPAU20 : 1;
        Uns32     IPAU21 : 1;
        Uns32     IPAU22 : 1;
        Uns32     IPAU23 : 1;
        Uns32     IPAU24 : 1;
        Uns32     IPAU25 : 1;
        Uns32     IPAU26 : 1;
        Uns32     IPAU27 : 1;
        Uns32     IPAU28 : 1;
    };
} TYPE_SPR_IPA1U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        IPE : 1;
        Uns32        IPX : 1;
        Uns32        IPR : 1;
        Uns32       RSV0 : 1;
        Uns32        IPS : 1;
        Uns32        IPT : 1;
        Uns32       RSV1 : 1;
        Uns32      IPAL7 : 1;
        Uns32      IPAL8 : 1;
        Uns32      IPAL9 : 1;
        Uns32     IPAL10 : 1;
        Uns32     IPAL11 : 1;
        Uns32     IPAL12 : 1;
        Uns32     IPAL13 : 1;
        Uns32     IPAL14 : 1;
        Uns32     IPAL15 : 1;
        Uns32     IPAL16 : 1;
        Uns32     IPAL17 : 1;
        Uns32     IPAL18 : 1;
        Uns32     IPAL19 : 1;
        Uns32     IPAL20 : 1;
        Uns32     IPAL21 : 1;
        Uns32     IPAL22 : 1;
        Uns32     IPAL23 : 1;
        Uns32     IPAL24 : 1;
        Uns32     IPAL25 : 1;
        Uns32     IPAL26 : 1;
        Uns32     IPAL27 : 1;
        Uns32     IPAL28 : 1;
    };
} TYPE_SPR_IPA2L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      IPAU7 : 1;
        Uns32      IPAU8 : 1;
        Uns32      IPAU9 : 1;
        Uns32     IPAU10 : 1;
        Uns32     IPAU11 : 1;
        Uns32     IPAU12 : 1;
        Uns32     IPAU13 : 1;
        Uns32     IPAU14 : 1;
        Uns32     IPAU15 : 1;
        Uns32     IPAU16 : 1;
        Uns32     IPAU17 : 1;
        Uns32     IPAU18 : 1;
        Uns32     IPAU19 : 1;
        Uns32     IPAU20 : 1;
        Uns32     IPAU21 : 1;
        Uns32     IPAU22 : 1;
        Uns32     IPAU23 : 1;
        Uns32     IPAU24 : 1;
        Uns32     IPAU25 : 1;
        Uns32     IPAU26 : 1;
        Uns32     IPAU27 : 1;
        Uns32     IPAU28 : 1;
    };
} TYPE_SPR_IPA2U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        IPE : 1;
        Uns32        IPX : 1;
        Uns32        IPR : 1;
        Uns32       RSV0 : 1;
        Uns32        IPS : 1;
        Uns32        IPT : 1;
        Uns32       RSV1 : 1;
        Uns32      IPAL7 : 1;
        Uns32      IPAL8 : 1;
        Uns32      IPAL9 : 1;
        Uns32     IPAL10 : 1;
        Uns32     IPAL11 : 1;
        Uns32     IPAL12 : 1;
        Uns32     IPAL13 : 1;
        Uns32     IPAL14 : 1;
        Uns32     IPAL15 : 1;
        Uns32     IPAL16 : 1;
        Uns32     IPAL17 : 1;
        Uns32     IPAL18 : 1;
        Uns32     IPAL19 : 1;
        Uns32     IPAL20 : 1;
        Uns32     IPAL21 : 1;
        Uns32     IPAL22 : 1;
        Uns32     IPAL23 : 1;
        Uns32     IPAL24 : 1;
        Uns32     IPAL25 : 1;
        Uns32     IPAL26 : 1;
        Uns32     IPAL27 : 1;
        Uns32     IPAL28 : 1;
    };
} TYPE_SPR_IPA3L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      IPAU7 : 1;
        Uns32      IPAU8 : 1;
        Uns32      IPAU9 : 1;
        Uns32     IPAU10 : 1;
        Uns32     IPAU11 : 1;
        Uns32     IPAU12 : 1;
        Uns32     IPAU13 : 1;
        Uns32     IPAU14 : 1;
        Uns32     IPAU15 : 1;
        Uns32     IPAU16 : 1;
        Uns32     IPAU17 : 1;
        Uns32     IPAU18 : 1;
        Uns32     IPAU19 : 1;
        Uns32     IPAU20 : 1;
        Uns32     IPAU21 : 1;
        Uns32     IPAU22 : 1;
        Uns32     IPAU23 : 1;
        Uns32     IPAU24 : 1;
        Uns32     IPAU25 : 1;
        Uns32     IPAU26 : 1;
        Uns32     IPAU27 : 1;
        Uns32     IPAU28 : 1;
    };
} TYPE_SPR_IPA3U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DPE : 1;
        Uns32       RSV0 : 1;
        Uns32        DPR : 1;
        Uns32        DPW : 1;
        Uns32        DPS : 1;
        Uns32        DPT : 1;
        Uns32       RSV1 : 1;
        Uns32      DPAL7 : 1;
        Uns32      DPAL8 : 1;
        Uns32      DPAL9 : 1;
        Uns32     DPAL10 : 1;
        Uns32     DPAL11 : 1;
        Uns32     DPAL12 : 1;
        Uns32     DPAL13 : 1;
        Uns32     DPAL14 : 1;
        Uns32     DPAL15 : 1;
        Uns32     DPAL16 : 1;
        Uns32     DPAL17 : 1;
        Uns32     DPAL18 : 1;
        Uns32     DPAL19 : 1;
        Uns32     DPAL20 : 1;
        Uns32     DPAL21 : 1;
        Uns32     DPAL22 : 1;
        Uns32     DPAL23 : 1;
        Uns32     DPAL24 : 1;
        Uns32     DPAL25 : 1;
        Uns32     DPAL26 : 1;
        Uns32     DPAL27 : 1;
        Uns32     DPAL28 : 1;
    };
} TYPE_SPR_DPA0L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      DPAU7 : 1;
        Uns32      DPAU8 : 1;
        Uns32      DPAU9 : 1;
        Uns32     DPAU10 : 1;
        Uns32     DPAU11 : 1;
        Uns32     DPAU12 : 1;
        Uns32     DPAU13 : 1;
        Uns32     DPAU14 : 1;
        Uns32     DPAU15 : 1;
        Uns32     DPAU16 : 1;
        Uns32     DPAU17 : 1;
        Uns32     DPAU18 : 1;
        Uns32     DPAU19 : 1;
        Uns32     DPAU20 : 1;
        Uns32     DPAU21 : 1;
        Uns32     DPAU22 : 1;
        Uns32     DPAU23 : 1;
        Uns32     DPAU24 : 1;
        Uns32     DPAU25 : 1;
        Uns32     DPAU26 : 1;
        Uns32     DPAU27 : 1;
        Uns32     DPAU28 : 1;
    };
} TYPE_SPR_DPA0U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DPE : 1;
        Uns32       RSV0 : 1;
        Uns32        DPR : 1;
        Uns32        DPW : 1;
        Uns32        DPS : 1;
        Uns32        DPT : 1;
        Uns32       RSV1 : 1;
        Uns32      DPAL7 : 1;
        Uns32      DPAL8 : 1;
        Uns32      DPAL9 : 1;
        Uns32     DPAL10 : 1;
        Uns32     DPAL11 : 1;
        Uns32     DPAL12 : 1;
        Uns32     DPAL13 : 1;
        Uns32     DPAL14 : 1;
        Uns32     DPAL15 : 1;
        Uns32     DPAL16 : 1;
        Uns32     DPAL17 : 1;
        Uns32     DPAL18 : 1;
        Uns32     DPAL19 : 1;
        Uns32     DPAL20 : 1;
        Uns32     DPAL21 : 1;
        Uns32     DPAL22 : 1;
        Uns32     DPAL23 : 1;
        Uns32     DPAL24 : 1;
        Uns32     DPAL25 : 1;
        Uns32     DPAL26 : 1;
        Uns32     DPAL27 : 1;
        Uns32     DPAL28 : 1;
    };
} TYPE_SPR_DPA1L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      DPAU7 : 1;
        Uns32      DPAU8 : 1;
        Uns32      DPAU9 : 1;
        Uns32     DPAU10 : 1;
        Uns32     DPAU11 : 1;
        Uns32     DPAU12 : 1;
        Uns32     DPAU13 : 1;
        Uns32     DPAU14 : 1;
        Uns32     DPAU15 : 1;
        Uns32     DPAU16 : 1;
        Uns32     DPAU17 : 1;
        Uns32     DPAU18 : 1;
        Uns32     DPAU19 : 1;
        Uns32     DPAU20 : 1;
        Uns32     DPAU21 : 1;
        Uns32     DPAU22 : 1;
        Uns32     DPAU23 : 1;
        Uns32     DPAU24 : 1;
        Uns32     DPAU25 : 1;
        Uns32     DPAU26 : 1;
        Uns32     DPAU27 : 1;
        Uns32     DPAU28 : 1;
    };
} TYPE_SPR_DPA1U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DPE : 1;
        Uns32       RSV0 : 1;
        Uns32        DPR : 1;
        Uns32        DPW : 1;
        Uns32        DPS : 1;
        Uns32        DPT : 1;
        Uns32       RSV1 : 1;
        Uns32      DPAL7 : 1;
        Uns32      DPAL8 : 1;
        Uns32      DPAL9 : 1;
        Uns32     DPAL10 : 1;
        Uns32     DPAL11 : 1;
        Uns32     DPAL12 : 1;
        Uns32     DPAL13 : 1;
        Uns32     DPAL14 : 1;
        Uns32     DPAL15 : 1;
        Uns32     DPAL16 : 1;
        Uns32     DPAL17 : 1;
        Uns32     DPAL18 : 1;
        Uns32     DPAL19 : 1;
        Uns32     DPAL20 : 1;
        Uns32     DPAL21 : 1;
        Uns32     DPAL22 : 1;
        Uns32     DPAL23 : 1;
        Uns32     DPAL24 : 1;
        Uns32     DPAL25 : 1;
        Uns32     DPAL26 : 1;
        Uns32     DPAL27 : 1;
        Uns32     DPAL28 : 1;
    };
} TYPE_SPR_DPA2L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      DPAU7 : 1;
        Uns32      DPAU8 : 1;
        Uns32      DPAU9 : 1;
        Uns32     DPAU10 : 1;
        Uns32     DPAU11 : 1;
        Uns32     DPAU12 : 1;
        Uns32     DPAU13 : 1;
        Uns32     DPAU14 : 1;
        Uns32     DPAU15 : 1;
        Uns32     DPAU16 : 1;
        Uns32     DPAU17 : 1;
        Uns32     DPAU18 : 1;
        Uns32     DPAU19 : 1;
        Uns32     DPAU20 : 1;
        Uns32     DPAU21 : 1;
        Uns32     DPAU22 : 1;
        Uns32     DPAU23 : 1;
        Uns32     DPAU24 : 1;
        Uns32     DPAU25 : 1;
        Uns32     DPAU26 : 1;
        Uns32     DPAU27 : 1;
        Uns32     DPAU28 : 1;
    };
} TYPE_SPR_DPA2U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DPE : 1;
        Uns32       RSV0 : 1;
        Uns32        DPR : 1;
        Uns32        DPW : 1;
        Uns32        DPS : 1;
        Uns32        DPT : 1;
        Uns32       RSV1 : 1;
        Uns32      DPAL7 : 1;
        Uns32      DPAL8 : 1;
        Uns32      DPAL9 : 1;
        Uns32     DPAL10 : 1;
        Uns32     DPAL11 : 1;
        Uns32     DPAL12 : 1;
        Uns32     DPAL13 : 1;
        Uns32     DPAL14 : 1;
        Uns32     DPAL15 : 1;
        Uns32     DPAL16 : 1;
        Uns32     DPAL17 : 1;
        Uns32     DPAL18 : 1;
        Uns32     DPAL19 : 1;
        Uns32     DPAL20 : 1;
        Uns32     DPAL21 : 1;
        Uns32     DPAL22 : 1;
        Uns32     DPAL23 : 1;
        Uns32     DPAL24 : 1;
        Uns32     DPAL25 : 1;
        Uns32     DPAL26 : 1;
        Uns32     DPAL27 : 1;
        Uns32     DPAL28 : 1;
    };
} TYPE_SPR_DPA3L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      DPAU7 : 1;
        Uns32      DPAU8 : 1;
        Uns32      DPAU9 : 1;
        Uns32     DPAU10 : 1;
        Uns32     DPAU11 : 1;
        Uns32     DPAU12 : 1;
        Uns32     DPAU13 : 1;
        Uns32     DPAU14 : 1;
        Uns32     DPAU15 : 1;
        Uns32     DPAU16 : 1;
        Uns32     DPAU17 : 1;
        Uns32     DPAU18 : 1;
        Uns32     DPAU19 : 1;
        Uns32     DPAU20 : 1;
        Uns32     DPAU21 : 1;
        Uns32     DPAU22 : 1;
        Uns32     DPAU23 : 1;
        Uns32     DPAU24 : 1;
        Uns32     DPAU25 : 1;
        Uns32     DPAU26 : 1;
        Uns32     DPAU27 : 1;
        Uns32     DPAU28 : 1;
    };
} TYPE_SPR_DPA3U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DPE : 1;
        Uns32       RSV0 : 1;
        Uns32        DPR : 1;
        Uns32        DPW : 1;
        Uns32        DPS : 1;
        Uns32        DPT : 1;
        Uns32       RSV1 : 1;
        Uns32      DPAL7 : 1;
        Uns32      DPAL8 : 1;
        Uns32      DPAL9 : 1;
        Uns32     DPAL10 : 1;
        Uns32     DPAL11 : 1;
        Uns32     DPAL12 : 1;
        Uns32     DPAL13 : 1;
        Uns32     DPAL14 : 1;
        Uns32     DPAL15 : 1;
        Uns32     DPAL16 : 1;
        Uns32     DPAL17 : 1;
        Uns32     DPAL18 : 1;
        Uns32     DPAL19 : 1;
        Uns32     DPAL20 : 1;
        Uns32     DPAL21 : 1;
        Uns32     DPAL22 : 1;
        Uns32     DPAL23 : 1;
        Uns32     DPAL24 : 1;
        Uns32     DPAL25 : 1;
        Uns32     DPAL26 : 1;
        Uns32     DPAL27 : 1;
        Uns32     DPAL28 : 1;
    };
} TYPE_SPR_DPA4L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      DPAU7 : 1;
        Uns32      DPAU8 : 1;
        Uns32      DPAU9 : 1;
        Uns32     DPAU10 : 1;
        Uns32     DPAU11 : 1;
        Uns32     DPAU12 : 1;
        Uns32     DPAU13 : 1;
        Uns32     DPAU14 : 1;
        Uns32     DPAU15 : 1;
        Uns32     DPAU16 : 1;
        Uns32     DPAU17 : 1;
        Uns32     DPAU18 : 1;
        Uns32     DPAU19 : 1;
        Uns32     DPAU20 : 1;
        Uns32     DPAU21 : 1;
        Uns32     DPAU22 : 1;
        Uns32     DPAU23 : 1;
        Uns32     DPAU24 : 1;
        Uns32     DPAU25 : 1;
        Uns32     DPAU26 : 1;
        Uns32     DPAU27 : 1;
        Uns32     DPAU28 : 1;
    };
} TYPE_SPR_DPA4U;

typedef union {
    Uns32 reg;
    struct {
        Uns32        DPE : 1;
        Uns32       RSV0 : 1;
        Uns32        DPR : 1;
        Uns32        DPW : 1;
        Uns32        DPS : 1;
        Uns32        DPT : 1;
        Uns32       RSV1 : 1;
        Uns32      DPAL7 : 1;
        Uns32      DPAL8 : 1;
        Uns32      DPAL9 : 1;
        Uns32     DPAL10 : 1;
        Uns32     DPAL11 : 1;
        Uns32     DPAL12 : 1;
        Uns32     DPAL13 : 1;
        Uns32     DPAL14 : 1;
        Uns32     DPAL15 : 1;
        Uns32     DPAL16 : 1;
        Uns32     DPAL17 : 1;
        Uns32     DPAL18 : 1;
        Uns32     DPAL19 : 1;
        Uns32     DPAL20 : 1;
        Uns32     DPAL21 : 1;
        Uns32     DPAL22 : 1;
        Uns32     DPAL23 : 1;
        Uns32     DPAL24 : 1;
        Uns32     DPAL25 : 1;
        Uns32     DPAL26 : 1;
        Uns32     DPAL27 : 1;
        Uns32     DPAL28 : 1;
    };
} TYPE_SPR_DPA5L;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 7;
        Uns32      DPAU7 : 1;
        Uns32      DPAU8 : 1;
        Uns32      DPAU9 : 1;
        Uns32     DPAU10 : 1;
        Uns32     DPAU11 : 1;
        Uns32     DPAU12 : 1;
        Uns32     DPAU13 : 1;
        Uns32     DPAU14 : 1;
        Uns32     DPAU15 : 1;
        Uns32     DPAU16 : 1;
        Uns32     DPAU17 : 1;
        Uns32     DPAU18 : 1;
        Uns32     DPAU19 : 1;
        Uns32     DPAU20 : 1;
        Uns32     DPAU21 : 1;
        Uns32     DPAU22 : 1;
        Uns32     DPAU23 : 1;
        Uns32     DPAU24 : 1;
        Uns32     DPAU25 : 1;
        Uns32     DPAU26 : 1;
        Uns32     DPAU27 : 1;
        Uns32     DPAU28 : 1;
    };
} TYPE_SPR_DPA5U;

typedef union {
    Uns32 reg;
    struct {
        Uns32         DC : 1;
        Uns32         PP : 1;
    };
} TYPE_SPR_VIP;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32        VMX : 1;
        Uns32        VMR : 1;
        Uns32        VMW : 1;
        Uns32        VMS : 1;
        Uns32      VMRMW : 1;
        Uns32       VMMS : 1;
    };
} TYPE_SPR_VMECR;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VMTID;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VMADR;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VPECR;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VPTID;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VPADR;

typedef union {
    Uns32 reg;
    struct {
        Uns32        VDC : 1;
    };
} TYPE_SPR_VDECR0;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VDTID0;

typedef union {
    Uns32 reg;
    struct {
        Uns32        VDC : 1;
    };
} TYPE_SPR_VDECR1;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_VDTID1;

typedef union {
    Uns32 reg;
    struct { // V850
        Uns32       XP_I : 1;
        Uns32       XP_U : 1;
        Uns32       XP_O : 1;
        Uns32       XP_Z : 1;
        Uns32       XP_V : 1;
        Uns32       XE_I : 1;
        Uns32       XE_U : 1;
        Uns32       XE_O : 1;
        Uns32       XE_Z : 1;
        Uns32       XE_V : 1;
        Uns32       XC_I : 1;
        Uns32       XC_U : 1;
        Uns32       XC_O : 1;
        Uns32       XC_Z : 1;
        Uns32       XC_V : 1;
        Uns32       XC_E : 1;
        Uns32         PR : 1; // RH850 = 0
        Uns32         FS : 1;
        Uns32         RM : 2;
        Uns32        SEM : 1; // RH850 = 0
        Uns32        DEM : 1; // V850=DEM, RH850=PEM
        Uns32       RSV0 : 2;
        Uns32        CC0 : 1;
        Uns32        CC1 : 1;
        Uns32        CC2 : 1;
        Uns32        CC3 : 1;
        Uns32        CC4 : 1;
        Uns32        CC5 : 1;
        Uns32        CC6 : 1;
        Uns32        CC7 : 1;
    };
    struct { // RH850
        Uns32     VOID_0 : 21;
        Uns32        PEM : 1; // V850=DEM, RH850=PEM
        Uns32     VOID_1 : 10;
    };
} TYPE_SPR_FPSR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 1;
        Uns32         PC : 28; // R/W
        Uns32       RSV1 : 3;
    };
} TYPE_SPR_FPEPC;

//
// Copy of bits from FPSR
//
typedef union {
    Uns32 reg;
    struct { // V850
        Uns32       XP_I : 1;
        Uns32       XP_U : 1;
        Uns32       XP_O : 1;
        Uns32       XP_Z : 1;
        Uns32       XP_V : 1;
        Uns32       RSV0 : 3;
        Uns32       XC_I : 1;
        Uns32       XC_U : 1;
        Uns32       XC_O : 1;
        Uns32       XC_Z : 1;
        Uns32       XC_V : 1;
        Uns32       XC_E : 1;
        Uns32       RSV1 : 1;
        Uns32         PR : 1; // Not availabl on RH850
        Uns32       RSV2 : 16;
    };
    struct { // RH850
        Uns32     VOID_0 : 5;
        Uns32         IF : 1;
        Uns32     VOID_1 : 26;
    };
} TYPE_SPR_FPST;

//
// Copy of bits from FPSR
//
typedef union {
    Uns32 reg;
    struct {
        Uns32        CC0 : 1;
        Uns32        CC1 : 1;
        Uns32        CC2 : 1;
        Uns32        CC3 : 1;
        Uns32        CC4 : 1;
        Uns32        CC5 : 1;
        Uns32        CC6 : 1;
        Uns32        CC7 : 1;
        Uns32       RSV0 : 24;
    };
} TYPE_SPR_FPCC;

//
// Copy of bits from FPSR
//
typedef union {
    Uns32 reg;
    struct {
        Uns32       XE_I : 1;
        Uns32       XE_U : 1;
        Uns32       XE_O : 1;
        Uns32       XE_Z : 1;
        Uns32       XE_V : 1;
        Uns32       RSV0 : 3;
        Uns32         RM : 2;
        Uns32       RSV1 : 22;
    };
} TYPE_SPR_FPCFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32      FPIVD : 1; // R/W
        Uns32       RSV0 : 31;
    };
} TYPE_SPR_FPEC;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_BPC;

typedef union {
    Uns32 reg;
    struct {
        Uns32       ASID : 10;
        Uns32       RSV0 : 22;
    };
} TYPE_SPR_ASID;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_BPAV;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_BPAM;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_BPDV;

typedef union {
    Uns32 reg;
    struct {
        Uns32      value : 32;
    };
} TYPE_SPR_BPDM;

typedef union {
    Uns32 reg;
    struct {
        Uns32          Z : 1;
        Uns32          S : 1;
        Uns32         OV : 1;
        Uns32       RSV0 : 1;
        Uns32         TR : 1;
        Uns32       RSV1 : 3;
        Uns32         PR : 1;
        Uns32         UD : 1;
        Uns32         VF : 1;
        Uns32         ZD : 1;
        Uns32         IV : 1;
        Uns32         RO : 1;
    };
} TYPE_SPR_EFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 8;
        Uns32         PT : 1;
        Uns32         UT : 1;
        Uns32         VT : 1;
        Uns32         ZT : 1;
        Uns32         IT : 1;
    };
} TYPE_SPR_ECT;

//
// Registers added for RH850
//
typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 2;
        Uns32       BIT1 : 1;
        Uns32       RSV1 : 13;
        Uns32       SPID : 8;
        Uns32       RSV2 : 8;
    };
} TYPE_SPR_MCFG0;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RINT :  1;
        Uns32       RSV0 :  8;
        Uns32      RBASE : 23;
    };
} TYPE_SPR_RBASE;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RINT :  1;
        Uns32       RSV0 :  8;
        Uns32      EBASE : 23;
    };
} TYPE_SPR_EBASE;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 :  9;
        Uns32      INTBP : 23;
    };
} TYPE_SPR_INTBP;

typedef union {
    Uns32 reg;
    struct {
        Uns32        UIC :  1;
        Uns32         MA :  1;
        Uns32       RSV0 : 29;
        Uns32       BIT1 :  1;
    };
} TYPE_SPR_MCTL;

typedef union {
    Uns32 reg;
    struct {
        Uns32      VERSION :  8;
        Uns32     FUNCTION : 16;
        Uns32 ARCHITECTURE :  8;
    };
} TYPE_SPR_PID;

typedef union {
    Uns32 reg;
    struct {
        Uns32      FPIPR : 5; // R/W
        Uns32       RSV0 : 27;
    };
} TYPE_SPR_FPIPR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       SIZE :  8;
        Uns32       RSV0 : 24;
    };
} TYPE_SPR_SCCFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32   SCBP_0_1 :  2;
        Uns32  SCBP_31_2 : 30;
    };
} TYPE_SPR_SCBP;

typedef union {
    Uns32 reg;
    struct {
        Uns32      RSV0 : 15;
        Uns32      BIT1 : 1;
        Uns32      PEID : 3;
        Uns32      RSV1 : 13;
    };
} TYPE_SPR_HTCFG0;

typedef union {
    Uns32 reg;
    struct {
        Uns32      MEA : 32;
    };
} TYPE_SPR_MEA;

typedef union {
    Uns32 reg;
    struct {
        Uns32        RW :  1;
        Uns32     ITYPE :  5;
        Uns32      RSV0 :  2;
        Uns32         U :  1;
        Uns32        DS :  2;
        Uns32      RSV1 :  5;
        Uns32       REG :  5;
        Uns32      RSV2 : 11;
    };
} TYPE_SPR_MEI;

typedef union {
    Uns32 reg;
    struct {
        Uns32        ISP : 16; // R
        Uns32       RSV0 : 16;
    };
} TYPE_SPR_ISPR;

typedef union {
    Uns32 reg;
    struct {
        Uns32        PMR : 16; // R/W
        Uns32       RSV0 : 16;
    };
} TYPE_SPR_PMR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       PMEI : 1; // R
        Uns32       PMFP : 1; // R
        Uns32       RSV0 : 30;
    };
} TYPE_SPR_ICSR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       ISPC : 1; // R/W
        Uns32       RSV0 : 31;
    };
} TYPE_SPR_INTCFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32          E : 16; // R/W
        Uns32       RSV0 : 16;
    };
} TYPE_SPR_MPRC;

typedef union {
    Uns32 reg;
    struct {
        Uns32     MPBRGN :  5; // R
        Uns32       RSV0 : 27;
    };
} TYPE_SPR_MPBRGN;

typedef union {
    Uns32 reg;
    struct {
        Uns32     MPTRGN :  5; // R
        Uns32       RSV0 : 27;
    };
} TYPE_SPR_MPTRGN;

typedef union {
    Uns32 reg;
    struct {
        Uns32        MCA : 32; // R/W
    };
} TYPE_SPR_MCA;

typedef union {
    Uns32 reg;
    struct {
        Uns32        MCS : 32; // R/W
    };
} TYPE_SPR_MCS;

typedef union {
    Uns32 reg;
    struct {
        Uns32        MCC : 32; // R/W
    };
} TYPE_SPR_MCC;

typedef union {
    Uns32 reg;
    struct {
        Uns32        URE : 1;
        Uns32        UWE : 1;
        Uns32        UXE : 1;
        Uns32        SRE : 1;
        Uns32        SWE : 1;
        Uns32        SXE : 1;
        Uns32       RSV0 : 2;
        Uns32         OV : 1;
        Uns32       RSV1 : 23;
    };
} TYPE_SPR_MCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 2;
        Uns32       MPLA : 30;
    };
} TYPE_SPR_MPLA;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 2;
        Uns32       MPUA : 30;
    };
} TYPE_SPR_MPUA;

typedef union {
    Uns32 reg;
    struct {
        Uns32         UR : 1;
        Uns32         UW : 1;
        Uns32         UX : 1;
        Uns32         SR : 1;
        Uns32         SW : 1;
        Uns32         SX : 1;
        Uns32          G : 1;
        Uns32          E : 1;
        Uns32       RSV0 : 8;
        Uns32       ASID : 10;
        Uns32       RSV1 : 6;
    };
} TYPE_SPR_MPAT;


typedef union {
    Uns32 reg;
    struct {
        Uns32          V : 1;
        Uns32       RSV0 : 1;
        Uns32          L : 1;
        Uns32       RSV1 : 1;
        Uns32        LRU : 2;
        Uns32       RSV2 : 4;
        Uns32        LPN : 22;
    };
} TYPE_SPR_ICTAGL;

typedef union {
    Uns32 reg;
    struct {
        Uns32       RSV0 : 8;
        Uns32     TAGECC : 8;
        Uns32    DATAECC : 8;
        Uns32       RSV1 : 4;
        Uns32         PT : 1;
        Uns32         WT : 1;
        Uns32         PD : 1;
        Uns32         WD : 1;
    };
} TYPE_SPR_ICTAGH;

typedef union {
    Uns32 reg;
    struct {
        Uns32      DATAL : 32;
    };
} TYPE_SPR_ICDATL;

typedef union {
    Uns32 reg;
    struct {
        Uns32      DATAH : 32;
    };
} TYPE_SPR_ICDATH;

typedef union {
    Uns32 reg;
    struct {
        Uns32      ICHEN : 1;
        Uns32     ICHEMK : 1;
        Uns32     ICHEIV : 1;
        Uns32       RSV0 : 5;
        Uns32     ICHCLR : 1;
        Uns32       RSV1 : 7;
        Uns32      BIT16 : 1;
        Uns32      D1EIV : 1;
        Uns32       RSV2 : 14;
    };
} TYPE_SPR_ICCTRL;

typedef union {
    Uns32 reg;
    struct {
        Uns32     ICHWAY : 4;
        Uns32    ICHLINE : 4;
        Uns32    ICHSIZE : 7;
        Uns32       RSV0 : 1;
        Uns32      BIT16 : 1;
        Uns32       RSV1 : 15;
    };
} TYPE_SPR_ICCFG;

typedef union {
    Uns32 reg;
    struct {
        Uns32     ICHERR : 1;
        Uns32       RSV0 : 1;
        Uns32      ICHET : 1;
        Uns32      ICHED : 1;
        Uns32     ICHERQ : 1;
        Uns32     ICHEIX : 8;
        Uns32     ICHWAY : 2;
        Uns32       RSV1 : 1;
        Uns32      ERMDE : 1;
        Uns32      ERMDC : 1;
        Uns32     ERMTE2 : 1;
        Uns32     ERMTE1 : 1;
        Uns32    ERMPBSE : 1;
        Uns32     ERMTMH : 1;
        Uns32       RSV2 : 2;
        Uns32       ESDE : 1;
        Uns32       ESDC : 1;
        Uns32      ESTE2 : 1;
        Uns32      ESTE1 : 1;
        Uns32     ESPBSE : 1;
        Uns32       ESMH : 1;
        Uns32       RSV3 : 1;
        Uns32      CISTW : 1;
    };
} TYPE_SPR_ICERR;

typedef union {
    Uns32 reg;
    struct {
        Uns32      CDBEN : 1; // R/W
        Uns32     CDBCLR : 1; // W
        Uns32       RSV0 : 30;
    };
} TYPE_SPR_CDBCR;

typedef union {
    Uns32 reg;
    struct {
        Uns32       XC_I : 1;
        Uns32       XC_U : 1;
        Uns32       XC_O : 1;
        Uns32       XC_Z : 1;
        Uns32       XC_V : 1;
        Uns32       XC_E : 1;
    };
} EXT_FPU_FLG;

typedef union {
    Uns32 reg;
    struct {
        Uns32        VAL : 1;
        Uns32        IDX : 3;
    };
} EXT_FPU_CC;

typedef struct v850S {
    //
    // User Defined and Builtin Registers
    //
    Uns32 gpr[32];

    TYPE_SPR_EIWR     SPR_EIWR,     SPR_EIWR_rmask,     SPR_EIWR_wmask;
    TYPE_SPR_FEWR     SPR_FEWR,     SPR_FEWR_rmask,     SPR_FEWR_wmask;
    TYPE_SPR_DBWR     SPR_DBWR,     SPR_DBWR_rmask,     SPR_DBWR_wmask;
    TYPE_SPR_BSEL     SPR_BSEL,     SPR_BSEL_rmask,     SPR_BSEL_wmask;
    TYPE_SPR_EIPC     SPR_EIPC,     SPR_EIPC_rmask,     SPR_EIPC_wmask;
    TYPE_SPR_PSW      SPR_EIPSW,    SPR_EIPSW_rmask,    SPR_EIPSW_wmask;
    TYPE_SPR_FEPC     SPR_FEPC,     SPR_FEPC_rmask,     SPR_FEPC_wmask;
    TYPE_SPR_PSW      SPR_FEPSW,    SPR_FEPSW_rmask,    SPR_FEPSW_wmask;
    TYPE_SPR_ECR      SPR_ECR,      SPR_ECR_rmask,      SPR_ECR_wmask;
    TYPE_SPR_PSW      SPR_PSW,      SPR_PSW_rmask,      SPR_PSW_wmask,    SPR_PSW_wmask_um;
    TYPE_SPR_EIIC     SPR_EIIC,     SPR_EIIC_rmask,     SPR_EIIC_wmask;
    TYPE_SPR_FEIC     SPR_FEIC,     SPR_FEIC_rmask,     SPR_FEIC_wmask;
    TYPE_SPR_DBIC     SPR_DBIC,     SPR_DBIC_rmask,     SPR_DBIC_wmask;
    TYPE_SPR_CTPC     SPR_CTPC,     SPR_CTPC_rmask,     SPR_CTPC_wmask;
    TYPE_SPR_CTPSW    SPR_CTPSW,    SPR_CTPSW_rmask,    SPR_CTPSW_wmask;
    TYPE_SPR_DBPC     SPR_DBPC,     SPR_DBPC_rmask,     SPR_DBPC_wmask;
    TYPE_SPR_DBPSW    SPR_DBPSW,    SPR_DBPSW_rmask,    SPR_DBPSW_wmask;
    TYPE_SPR_CTBP     SPR_CTBP,     SPR_CTBP_rmask,     SPR_CTBP_wmask;
    TYPE_SPR_DIR      SPR_DIR,      SPR_DIR_rmask,      SPR_DIR_wmask;
    TYPE_SPR_SW_CTL   SPR_SW_CTL,   SPR_SW_CTL_rmask,   SPR_SW_CTL_wmask;
    TYPE_SPR_SW_CFG   SPR_SW_CFG,   SPR_SW_CFG_rmask,   SPR_SW_CFG_wmask;
    TYPE_SPR_SW_BASE  SPR_SW_BASE,  SPR_SW_BASE_rmask,  SPR_SW_BASE_wmask;
    TYPE_SPR_EH_CFG   SPR_EH_CFG,   SPR_EH_CFG_rmask,   SPR_EH_CFG_wmask;
    TYPE_SPR_EH_BASE  SPR_EH_BASE,  SPR_EH_BASE_rmask,  SPR_EH_BASE_wmask;
    TYPE_SPR_EH_RESET SPR_EH_RESET, SPR_EH_RESET_rmask, SPR_EH_RESET_wmask;
    TYPE_SPR_MPM      SPR_MPM,      SPR_MPM_rmask,      SPR_MPM_wmask;
    TYPE_SPR_MPC      SPR_MPC,      SPR_MPC_rmask,      SPR_MPC_wmask;
    TYPE_SPR_TID      SPR_TID,      SPR_TID_rmask,      SPR_TID_wmask;
    TYPE_SPR_PPC      SPR_PPC,      SPR_PPC_rmask,      SPR_PPC_wmask;
    TYPE_SPR_DCC0     SPR_DCC0,     SPR_DCC0_rmask,     SPR_DCC0_wmask;
    TYPE_SPR_DCV0     SPR_DCV0,     SPR_DCV0_rmask,     SPR_DCV0_wmask;
    TYPE_SPR_DCC1     SPR_DCC1,     SPR_DCC1_rmask,     SPR_DCC1_wmask;
    TYPE_SPR_DCV1     SPR_DCV1,     SPR_DCV1_rmask,     SPR_DCV1_wmask;
    TYPE_SPR_IPA0L    SPR_IPA0L,    SPR_IPA0L_rmask,    SPR_IPA0L_wmask;
    TYPE_SPR_IPA0U    SPR_IPA0U,    SPR_IPA0U_rmask,    SPR_IPA0U_wmask;
    TYPE_SPR_IPA1L    SPR_IPA1L,    SPR_IPA1L_rmask,    SPR_IPA1L_wmask;
    TYPE_SPR_IPA1U    SPR_IPA1U,    SPR_IPA1U_rmask,    SPR_IPA1U_wmask;
    TYPE_SPR_IPA2L    SPR_IPA2L,    SPR_IPA2L_rmask,    SPR_IPA2L_wmask;
    TYPE_SPR_IPA2U    SPR_IPA2U,    SPR_IPA2U_rmask,    SPR_IPA2U_wmask;
    TYPE_SPR_IPA3L    SPR_IPA3L,    SPR_IPA3L_rmask,    SPR_IPA3L_wmask;
    TYPE_SPR_IPA3U    SPR_IPA3U,    SPR_IPA3U_rmask,    SPR_IPA3U_wmask;
    TYPE_SPR_DPA0L    SPR_DPA0L,    SPR_DPA0L_rmask,    SPR_DPA0L_wmask;
    TYPE_SPR_DPA0U    SPR_DPA0U,    SPR_DPA0U_rmask,    SPR_DPA0U_wmask;
    TYPE_SPR_DPA1L    SPR_DPA1L,    SPR_DPA1L_rmask,    SPR_DPA1L_wmask;
    TYPE_SPR_DPA1U    SPR_DPA1U,    SPR_DPA1U_rmask,    SPR_DPA1U_wmask;
    TYPE_SPR_DPA2L    SPR_DPA2L,    SPR_DPA2L_rmask,    SPR_DPA2L_wmask;
    TYPE_SPR_DPA2U    SPR_DPA2U,    SPR_DPA2U_rmask,    SPR_DPA2U_wmask;
    TYPE_SPR_DPA3L    SPR_DPA3L,    SPR_DPA3L_rmask,    SPR_DPA3L_wmask;
    TYPE_SPR_DPA3U    SPR_DPA3U,    SPR_DPA3U_rmask,    SPR_DPA3U_wmask;
    TYPE_SPR_DPA4L    SPR_DPA4L,    SPR_DPA4L_rmask,    SPR_DPA4L_wmask;
    TYPE_SPR_DPA4U    SPR_DPA4U,    SPR_DPA4U_rmask,    SPR_DPA4U_wmask;
    TYPE_SPR_DPA5L    SPR_DPA5L,    SPR_DPA5L_rmask,    SPR_DPA5L_wmask;
    TYPE_SPR_DPA5U    SPR_DPA5U,    SPR_DPA5U_rmask,    SPR_DPA5U_wmask;
    TYPE_SPR_VIP      SPR_VIP,      SPR_VIP_rmask,      SPR_VIP_wmask;
    TYPE_SPR_VMECR    SPR_VMECR,    SPR_VMECR_rmask,    SPR_VMECR_wmask;
    TYPE_SPR_VMTID    SPR_VMTID,    SPR_VMTID_rmask,    SPR_VMTID_wmask;
    TYPE_SPR_VMADR    SPR_VMADR,    SPR_VMADR_rmask,    SPR_VMADR_wmask;
    TYPE_SPR_VPECR    SPR_VPECR,    SPR_VPECR_rmask,    SPR_VPECR_wmask;
    TYPE_SPR_VPTID    SPR_VPTID,    SPR_VPTID_rmask,    SPR_VPTID_wmask;
    TYPE_SPR_VPADR    SPR_VPADR,    SPR_VPADR_rmask,    SPR_VPADR_wmask;
    TYPE_SPR_VDECR0   SPR_VDECR0,   SPR_VDECR0_rmask,   SPR_VDECR0_wmask;
    TYPE_SPR_VDTID0   SPR_VDTID0,   SPR_VDTID0_rmask,   SPR_VDTID0_wmask;
    TYPE_SPR_VDECR1   SPR_VDECR1,   SPR_VDECR1_rmask,   SPR_VDECR1_wmask;
    TYPE_SPR_VDTID1   SPR_VDTID1,   SPR_VDTID1_rmask,   SPR_VDTID1_wmask;
    TYPE_SPR_FPSR     SPR_FPSR,     SPR_FPSR_rmask,     SPR_FPSR_wmask;
    TYPE_SPR_FPEPC    SPR_FPEPC,    SPR_FPEPC_rmask,    SPR_FPEPC_wmask;
    TYPE_SPR_FPST     SPR_FPST,     SPR_FPST_rmask,     SPR_FPST_wmask;
    TYPE_SPR_FPCC     SPR_FPCC,     SPR_FPCC_rmask,     SPR_FPCC_wmask;
    TYPE_SPR_FPCFG    SPR_FPCFG,    SPR_FPCFG_rmask,    SPR_FPCFG_wmask;
    TYPE_SPR_FPEC     SPR_FPEC,     SPR_FPEC_rmask,     SPR_FPEC_wmask;
    TYPE_SPR_BPC      SPR_BPC,      SPR_BPC_rmask,      SPR_BPC_wmask;
    TYPE_SPR_ASID     SPR_ASID,     SPR_ASID_rmask,     SPR_ASID_wmask;
    TYPE_SPR_BPAV     SPR_BPAV,     SPR_BPAV_rmask,     SPR_BPAV_wmask;
    TYPE_SPR_BPAM     SPR_BPAM,     SPR_BPAM_rmask,     SPR_BPAM_wmask;
    TYPE_SPR_BPDV     SPR_BPDV,     SPR_BPDV_rmask,     SPR_BPDV_wmask;
    TYPE_SPR_BPDM     SPR_BPDM,     SPR_BPDM_rmask,     SPR_BPDM_wmask;
    TYPE_SPR_EFG      SPR_EFG,      SPR_EFG_rmask,      SPR_EFG_wmask;
    TYPE_SPR_ECT      SPR_ECT,      SPR_ECT_rmask,      SPR_ECT_wmask;

    //
    // RH850 regs
    //
    TYPE_SPR_MCFG0    SPR_MCFG0,    SPR_MCFG0_rmask,    SPR_MCFG0_wmask;
    TYPE_SPR_RBASE    SPR_RBASE,    SPR_RBASE_rmask,    SPR_RBASE_wmask;
    TYPE_SPR_EBASE    SPR_EBASE,    SPR_EBASE_rmask,    SPR_EBASE_wmask;
    TYPE_SPR_INTBP    SPR_INTBP,    SPR_INTBP_rmask,    SPR_INTBP_wmask;
    TYPE_SPR_MCTL     SPR_MCTL,     SPR_MCTL_rmask,     SPR_MCTL_wmask;
    TYPE_SPR_PID      SPR_PID,      SPR_PID_rmask,      SPR_PID_wmask;
    TYPE_SPR_FPIPR    SPR_FPIPR,    SPR_FPIPR_rmask,    SPR_FPIPR_wmask;
    TYPE_SPR_SCCFG    SPR_SCCFG,    SPR_SCCFG_rmask,    SPR_SCCFG_wmask;
    TYPE_SPR_SCBP     SPR_SCBP,     SPR_SCBP_rmask,     SPR_SCBP_wmask;
    TYPE_SPR_HTCFG0   SPR_HTCFG0,   SPR_HTCFG0_rmask,   SPR_HTCFG0_wmask;
    TYPE_SPR_MEA      SPR_MEA,      SPR_MEA_rmask,      SPR_MEA_wmask;
  //TYPE_SPR_ASID -defined as part of V850
    TYPE_SPR_MEI      SPR_MEI,      SPR_MEI_rmask,      SPR_MEI_wmask;
    TYPE_SPR_ISPR     SPR_ISPR,     SPR_ISPR_rmask,     SPR_ISPR_wmask;
    TYPE_SPR_PMR      SPR_PMR,      SPR_PMR_rmask,      SPR_PMR_wmask;
    TYPE_SPR_ICSR     SPR_ICSR,     SPR_ICSR_rmask,     SPR_ICSR_wmask;
    TYPE_SPR_INTCFG   SPR_INTCFG,   SPR_INTCFG_rmask,   SPR_INTCFG_wmask;
    // MPM - defined above for V850 E2R
    TYPE_SPR_MPRC     SPR_MPRC,     SPR_MPRC_rmask,     SPR_MPRC_wmask;
    TYPE_SPR_MPBRGN   SPR_MPBRGN,   SPR_MPBRGN_rmask,   SPR_MPBRGN_wmask;
    TYPE_SPR_MPTRGN   SPR_MPTRGN,   SPR_MPTRGN_rmask,   SPR_MPTRGN_wmask;
    TYPE_SPR_MCA      SPR_MCA,      SPR_MCA_rmask,      SPR_MCA_wmask;
    TYPE_SPR_MCS      SPR_MCS,      SPR_MCS_rmask,      SPR_MCS_wmask;
    TYPE_SPR_MCC      SPR_MCC,      SPR_MCC_rmask,      SPR_MCC_wmask;
    TYPE_SPR_MCR      SPR_MCR,      SPR_MCR_rmask,      SPR_MCR_wmask;

    TYPE_SPR_MPLA     SPR_MPLA[16], SPR_MPLA_rmask[16], SPR_MPLA_wmask[16];
    TYPE_SPR_MPUA     SPR_MPUA[16], SPR_MPUA_rmask[16], SPR_MPUA_wmask[16];
    TYPE_SPR_MPAT     SPR_MPAT[16], SPR_MPAT_rmask[16], SPR_MPAT_wmask[16];

    TYPE_SPR_ICTAGL   SPR_ICTAGL,   SPR_ICTAGL_rmask,   SPR_ICTAGL_wmask;
    TYPE_SPR_ICTAGH   SPR_ICTAGH,   SPR_ICTAGH_rmask,   SPR_ICTAGH_wmask;
    TYPE_SPR_ICDATL   SPR_ICDATL,   SPR_ICDATL_rmask,   SPR_ICDATL_wmask;
    TYPE_SPR_ICDATH   SPR_ICDATH,   SPR_ICDATH_rmask,   SPR_ICDATH_wmask;
    TYPE_SPR_ICCTRL   SPR_ICCTRL,   SPR_ICCTRL_rmask,   SPR_ICCTRL_wmask;
    TYPE_SPR_ICCFG    SPR_ICCFG,    SPR_ICCFG_rmask,    SPR_ICCFG_wmask;
    TYPE_SPR_ICERR    SPR_ICERR,    SPR_ICERR_rmask,    SPR_ICERR_wmask;

    TYPE_SPR_CDBCR    SPR_CDBCR,    SPR_CDBCR_rmask,    SPR_CDBCR_wmask;

    vmiRegInfoP regInfoVariant;     // True representation of the model system registers
    vmiRegInfoP regInfoFrame;       // GDB Frame view of the model system registers

    Uns32 tmp[4];

    //
    // PSW Individual bits
    //
    Bool FLG_PSW_SAT;
    Bool FLG_PSW_ID;
    Bool FLG_PSW_EP;
    Bool FLG_PSW_NP;
    Bool FLG_PSW_ZR;
    Bool FLG_PSW_SI;
    Bool FLG_PSW_OV;
    Bool FLG_PSW_CO;

    //
    // EFG/FPSR individual bits
    //
    Uns8 FLG_FPF;
    Uns8 FLG_FPF_STICKY;

    //
    // EFG
    //
    Bool FLG_EFG_FPZ;
    Bool FLG_EFG_FPS;
    Bool FLG_EFG_FPOV;

    //
    // FPSR
    //
    Bool FLG_FPSR_CC[8];

    Uns8 FLG_FCMP;      // really a temporary ?
    Bool FLG_INTPEND;
    Bool FLG_NMIPEND;
    Bool FLG_RSTPEND;

    Bool FLG_TMP;

    //
    // Mutual Exclusion control
    //
    Bool  FLG_LL;
    Uns32 REG_LL;

    Uns32 REG_RETMASK;

    // Psuedo-registers to handle a debug halt
    v850Disable disable;
    v850Notify  notify;
    // Pseudo registers for external FPU interaction
    Uns32       ResultHi, ResultLo;
    Uns8        ResultSz;
    Uns8        ResultId;
    EXT_FPU_FLG ResultFlg;
    EXT_FPU_CC  ResultCC;

    //
    // Model Support Registers
    //
    v850Mode      mode;
    Uns32         flags;
    v850Config    configInfo;
    Bool          verbose;
    memEndian     dendian;
    memEndian     iendian;
    v850Exception exception;
    struct {
        Bool  GDBSIMMODE;
        Bool  nofpu;
        Bool  ucbank;
        Uns32 PEID;
        Uns8  SPID;
    } params;

    // Bus, Net, Values
    vmiBusPortP  busPorts;
    v850NetPortP netPorts;
    v850NetValue netValue;

    // generic instruction decoder
    v850DecoderFn decoder;

    // virtual memory domain
    memDomainP physDomainC;
    memDomainP physDomainD;
    memDomainP virtDomainC[RH850_M_LAST];
    memDomainP virtDomainD[RH850_M_LAST];

} v850;

#define V850_CPU_OFFSET(_F) VMI_CPU_OFFSET(v850P, _F)
#define V850_CPU_REG(_F) VMI_CPU_REG(v850P, _F)
#define V850_CPU_TEMP(_F) VMI_CPU_TEMP(v850P, _F)
#define V850_CPU_RMASK(_F) V850_CPU_OFFSET(_F##_rmask)
#define V850_CPU_WMASK(_F) V850_CPU_OFFSET(_F##_wmask)

#define V850_GPR_BITS (sizeof(Uns32) * 8)
#define V850_GPR_RD(_R) V850_CPU_REG(gpr[_R])
#define V850_GPR_WR(_R) ((_R==0)) ? VMI_NOREG : V850_CPU_REG(gpr[_R])

#define V850_SPR_EIWR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EIWR_RD    V850_CPU_REG(SPR_EIWR)
#define V850_SPR_EIWR_RMASK V850_CPU_RMASK(SPR_EIWR)
#define V850_SPR_EIWR_WR    V850_CPU_REG(SPR_EIWR)
#define V850_SPR_EIWR_WMASK V850_CPU_WMASK(SPR_EIWR)

#define V850_SPR_FEWR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FEWR_RD    V850_CPU_REG(SPR_FEWR)
#define V850_SPR_FEWR_RMASK V850_CPU_RMASK(SPR_FEWR)
#define V850_SPR_FEWR_WR    V850_CPU_REG(SPR_FEWR)
#define V850_SPR_FEWR_WMASK V850_CPU_WMASK(SPR_FEWR)

#define V850_SPR_DBWR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DBWR_RD    V850_CPU_REG(SPR_DBWR)
#define V850_SPR_DBWR_RMASK V850_CPU_RMASK(SPR_DBWR)
#define V850_SPR_DBWR_WR    V850_CPU_REG(SPR_DBWR)
#define V850_SPR_DBWR_WMASK V850_CPU_WMASK(SPR_DBWR)

#define V850_SPR_BSEL_BITS (sizeof(Uns32) * 8)
#define V850_SPR_BSEL_RD    V850_CPU_REG(SPR_BSEL)
#define V850_SPR_BSEL_RMASK V850_CPU_RMASK(SPR_BSEL)
#define V850_SPR_BSEL_WR    V850_CPU_REG(SPR_BSEL)
#define V850_SPR_BSEL_WMASK V850_CPU_WMASK(SPR_BSEL)

#define V850_SPR_EIPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EIPC_RD    V850_CPU_REG(SPR_EIPC)
#define V850_SPR_EIPC_RMASK V850_CPU_RMASK(SPR_EIPC)
#define V850_SPR_EIPC_WR    V850_CPU_REG(SPR_EIPC)
#define V850_SPR_EIPC_WMASK V850_CPU_WMASK(SPR_EIPC)

#define V850_SPR_EIPSW_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EIPSW_RD    V850_CPU_REG(SPR_EIPSW)
#define V850_SPR_EIPSW_RMASK V850_CPU_RMASK(SPR_EIPSW)
#define V850_SPR_EIPSW_WR    V850_CPU_REG(SPR_EIPSW)
#define V850_SPR_EIPSW_WMASK V850_CPU_WMASK(SPR_EIPSW)

#define V850_SPR_FEPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FEPC_RD    V850_CPU_REG(SPR_FEPC)
#define V850_SPR_FEPC_RMASK V850_CPU_RMASK(SPR_FEPC)
#define V850_SPR_FEPC_WR    V850_CPU_REG(SPR_FEPC)
#define V850_SPR_FEPC_WMASK V850_CPU_WMASK(SPR_FEPC)

#define V850_SPR_FEPSW_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FEPSW_RD    V850_CPU_REG(SPR_FEPSW)
#define V850_SPR_FEPSW_RMASK V850_CPU_RMASK(SPR_FEPSW)
#define V850_SPR_FEPSW_WR    V850_CPU_REG(SPR_FEPSW)
#define V850_SPR_FEPSW_WMASK V850_CPU_WMASK(SPR_FEPSW)

#define V850_SPR_ECR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ECR_RD    V850_CPU_REG(SPR_ECR)
#define V850_SPR_ECR_RMASK V850_CPU_RMASK(SPR_ECR)
#define V850_SPR_ECR_WR    V850_CPU_REG(SPR_ECR)
#define V850_SPR_ECR_WMASK V850_CPU_WMASK(SPR_ECR)

#define V850_SPR_PSW_BITS (sizeof(Uns32) * 8)
#define V850_SPR_PSW_RD    V850_CPU_REG(SPR_PSW)
#define V850_SPR_PSW_RMASK V850_CPU_RMASK(SPR_PSW)
#define V850_SPR_PSW_WR    V850_CPU_REG(SPR_PSW)
#define V850_SPR_PSW_WMASK V850_CPU_WMASK(SPR_PSW)

#define V850_SPR_EIIC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EIIC_RD    V850_CPU_REG(SPR_EIIC)
#define V850_SPR_EIIC_RMASK V850_CPU_RMASK(SPR_EIIC)
#define V850_SPR_EIIC_WR    V850_CPU_REG(SPR_EIIC)
#define V850_SPR_EIIC_WMASK V850_CPU_WMASK(SPR_EIIC)

#define V850_SPR_FEIC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FEIC_RD    V850_CPU_REG(SPR_FEIC)
#define V850_SPR_FEIC_RMASK V850_CPU_RMASK(SPR_FEIC)
#define V850_SPR_FEIC_WR    V850_CPU_REG(SPR_FEIC)
#define V850_SPR_FEIC_WMASK V850_CPU_WMASK(SPR_FEIC)

#define V850_SPR_DBIC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DBIC_RD    V850_CPU_REG(SPR_DBIC)
#define V850_SPR_DBIC_RMASK V850_CPU_RMASK(SPR_DBIC)
#define V850_SPR_DBIC_WR    V850_CPU_REG(SPR_DBIC)
#define V850_SPR_DBIC_WMASK V850_CPU_WMASK(SPR_DBIC)

#define V850_SPR_CTPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_CTPC_RD    V850_CPU_REG(SPR_CTPC)
#define V850_SPR_CTPC_RMASK V850_CPU_RMASK(SPR_CTPC)
#define V850_SPR_CTPC_WR    V850_CPU_REG(SPR_CTPC)
#define V850_SPR_CTPC_WMASK V850_CPU_WMASK(SPR_CTPC)

#define V850_SPR_CTPSW_BITS (sizeof(Uns32) * 8)
#define V850_SPR_CTPSW_RD    V850_CPU_REG(SPR_CTPSW)
#define V850_SPR_CTPSW_RMASK V850_CPU_RMASK(SPR_CTPSW)
#define V850_SPR_CTPSW_WR    V850_CPU_REG(SPR_CTPSW)
#define V850_SPR_CTPSW_WMASK V850_CPU_WMASK(SPR_CTPSW)

#define V850_SPR_DBPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DBPC_RD    V850_CPU_REG(SPR_DBPC)
#define V850_SPR_DBPC_RMASK V850_CPU_RMASK(SPR_DBPC)
#define V850_SPR_DBPC_WR    V850_CPU_REG(SPR_DBPC)
#define V850_SPR_DBPC_WMASK V850_CPU_WMASK(SPR_DBPC)

#define V850_SPR_DBPSW_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DBPSW_RD    V850_CPU_REG(SPR_DBPSW)
#define V850_SPR_DBPSW_RMASK V850_CPU_RMASK(SPR_DBPSW)
#define V850_SPR_DBPSW_WR    V850_CPU_REG(SPR_DBPSW)
#define V850_SPR_DBPSW_WMASK V850_CPU_WMASK(SPR_DBPSW)

#define V850_SPR_CTBP_BITS (sizeof(Uns32) * 8)
#define V850_SPR_CTBP_RD    V850_CPU_REG(SPR_CTBP)
#define V850_SPR_CTBP_RMASK V850_CPU_RMASK(SPR_CTBP)
#define V850_SPR_CTBP_WR    V850_CPU_REG(SPR_CTBP)
#define V850_SPR_CTBP_WMASK V850_CPU_WMASK(SPR_CTBP)

#define V850_SPR_DIR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DIR_RD    V850_CPU_REG(SPR_DIR)
#define V850_SPR_DIR_RMASK V850_CPU_RMASK(SPR_DIR)
#define V850_SPR_DIR_WR    V850_CPU_REG(SPR_DIR)
#define V850_SPR_DIR_WMASK V850_CPU_WMASK(SPR_DIR)

#define V850_SPR_SW_CTL_BITS (sizeof(Uns32) * 8)
#define V850_SPR_SW_CTL_RD    V850_CPU_REG(SPR_SW_CTL)
#define V850_SPR_SW_CTL_RMASK V850_CPU_RMASK(SPR_SW_CTL)
#define V850_SPR_SW_CTL_WR    V850_CPU_REG(SPR_SW_CTL)
#define V850_SPR_SW_CTL_WMASK V850_CPU_WMASK(SPR_SW_CTL)

#define V850_SPR_SW_CFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_SW_CFG_RD    V850_CPU_REG(SPR_SW_CFG)
#define V850_SPR_SW_CFG_RMASK V850_CPU_RMASK(SPR_SW_CFG)
#define V850_SPR_SW_CFG_WR    V850_CPU_REG(SPR_SW_CFG)
#define V850_SPR_SW_CFG_WMASK V850_CPU_WMASK(SPR_SW_CFG)

#define V850_SPR_SW_BASE_BITS (sizeof(Uns32) * 8)
#define V850_SPR_SW_BASE_RD    V850_CPU_REG(SPR_SW_BASE)
#define V850_SPR_SW_BASE_RMASK V850_CPU_RMASK(SPR_SW_BASE)
#define V850_SPR_SW_BASE_WR    V850_CPU_REG(SPR_SW_BASE)
#define V850_SPR_SW_BASE_WMASK V850_CPU_WMASK(SPR_SW_BASE)

#define V850_SPR_EH_CFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EH_CFG_RD    V850_CPU_REG(SPR_EH_CFG)
#define V850_SPR_EH_CFG_RMASK V850_CPU_RMASK(SPR_EH_CFG)
#define V850_SPR_EH_CFG_WR    V850_CPU_REG(SPR_EH_CFG)
#define V850_SPR_EH_CFG_WMASK V850_CPU_WMASK(SPR_EH_CFG)

#define V850_SPR_EH_BASE_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EH_BASE_RD    V850_CPU_REG(SPR_EH_BASE)
#define V850_SPR_EH_BASE_RMASK V850_CPU_RMASK(SPR_EH_BASE)
#define V850_SPR_EH_BASE_WR    V850_CPU_REG(SPR_EH_BASE)
#define V850_SPR_EH_BASE_WMASK V850_CPU_WMASK(SPR_EH_BASE)

#define V850_SPR_EH_RESET_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EH_RESET_RD    V850_CPU_REG(SPR_EH_RESET)
#define V850_SPR_EH_RESET_RMASK V850_CPU_RMASK(SPR_EH_RESET)
#define V850_SPR_EH_RESET_WR    V850_CPU_REG(SPR_EH_RESET)
#define V850_SPR_EH_RESET_WMASK V850_CPU_WMASK(SPR_EH_RESET)

#define V850_SPR_MPM_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPM_RD    V850_CPU_REG(SPR_MPM)
#define V850_SPR_MPM_RMASK V850_CPU_RMASK(SPR_MPM)
#define V850_SPR_MPM_WR    V850_CPU_REG(SPR_MPM)
#define V850_SPR_MPM_WMASK V850_CPU_WMASK(SPR_MPM)

#define V850_SPR_MPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPC_RD    V850_CPU_REG(SPR_MPC)
#define V850_SPR_MPC_RMASK V850_CPU_RMASK(SPR_MPC)
#define V850_SPR_MPC_WR    V850_CPU_REG(SPR_MPC)
#define V850_SPR_MPC_WMASK V850_CPU_WMASK(SPR_MPC)

#define V850_SPR_TID_BITS (sizeof(Uns32) * 8)
#define V850_SPR_TID_RD    V850_CPU_REG(SPR_TID)
#define V850_SPR_TID_RMASK V850_CPU_RMASK(SPR_TID)
#define V850_SPR_TID_WR    V850_CPU_REG(SPR_TID)
#define V850_SPR_TID_WMASK V850_CPU_WMASK(SPR_TID)

#define V850_SPR_PPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_PPC_RD    V850_CPU_REG(SPR_PPC)
#define V850_SPR_PPC_RMASK V850_CPU_RMASK(SPR_PPC)
#define V850_SPR_PPC_WR    V850_CPU_REG(SPR_PPC)
#define V850_SPR_PPC_WMASK V850_CPU_WMASK(SPR_PPC)

#define V850_SPR_DCC0_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DCC0_RD    V850_CPU_REG(SPR_DCC0)
#define V850_SPR_DCC0_RMASK V850_CPU_RMASK(SPR_DCC0)
#define V850_SPR_DCC0_WR    V850_CPU_REG(SPR_DCC0)
#define V850_SPR_DCC0_WMASK V850_CPU_WMASK(SPR_DCC0)

#define V850_SPR_DCV0_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DCV0_RD    V850_CPU_REG(SPR_DCV0)
#define V850_SPR_DCV0_RMASK V850_CPU_RMASK(SPR_DCV0)
#define V850_SPR_DCV0_WR    V850_CPU_REG(SPR_DCV0)
#define V850_SPR_DCV0_WMASK V850_CPU_WMASK(SPR_DCV0)

#define V850_SPR_DCC1_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DCC1_RD    V850_CPU_REG(SPR_DCC1)
#define V850_SPR_DCC1_RMASK V850_CPU_RMASK(SPR_DCC1)
#define V850_SPR_DCC1_WR    V850_CPU_REG(SPR_DCC1)
#define V850_SPR_DCC1_WMASK V850_CPU_WMASK(SPR_DCC1)

#define V850_SPR_DCV1_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DCV1_RD    V850_CPU_REG(SPR_DCV1)
#define V850_SPR_DCV1_RMASK V850_CPU_RMASK(SPR_DCV1)
#define V850_SPR_DCV1_WR    V850_CPU_REG(SPR_DCV1)
#define V850_SPR_DCV1_WMASK V850_CPU_WMASK(SPR_DCV1)

#define V850_SPR_IPA0L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA0L_RD    V850_CPU_REG(SPR_IPA0L)
#define V850_SPR_IPA0L_RMASK V850_CPU_RMASK(SPR_IPA0L)
#define V850_SPR_IPA0L_WR    V850_CPU_REG(SPR_IPA0L)
#define V850_SPR_IPA0L_WMASK V850_CPU_WMASK(SPR_IPA0L)

#define V850_SPR_IPA0U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA0U_RD    V850_CPU_REG(SPR_IPA0U)
#define V850_SPR_IPA0U_RMASK V850_CPU_RMASK(SPR_IPA0U)
#define V850_SPR_IPA0U_WR    V850_CPU_REG(SPR_IPA0U)
#define V850_SPR_IPA0U_WMASK V850_CPU_WMASK(SPR_IPA0U)

#define V850_SPR_IPA1L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA1L_RD    V850_CPU_REG(SPR_IPA1L)
#define V850_SPR_IPA1L_RMASK V850_CPU_RMASK(SPR_IPA1L)
#define V850_SPR_IPA1L_WR    V850_CPU_REG(SPR_IPA1L)
#define V850_SPR_IPA1L_WMASK V850_CPU_WMASK(SPR_IPA1L)

#define V850_SPR_IPA1U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA1U_RD    V850_CPU_REG(SPR_IPA1U)
#define V850_SPR_IPA1U_RMASK V850_CPU_RMASK(SPR_IPA1U)
#define V850_SPR_IPA1U_WR    V850_CPU_REG(SPR_IPA1U)
#define V850_SPR_IPA1U_WMASK V850_CPU_WMASK(SPR_IPA1U)

#define V850_SPR_IPA2L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA2L_RD    V850_CPU_REG(SPR_IPA2L)
#define V850_SPR_IPA2L_RMASK V850_CPU_RMASK(SPR_IPA2L)
#define V850_SPR_IPA2L_WR    V850_CPU_REG(SPR_IPA2L)
#define V850_SPR_IPA2L_WMASK V850_CPU_WMASK(SPR_IPA2L)

#define V850_SPR_IPA2U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA2U_RD    V850_CPU_REG(SPR_IPA2U)
#define V850_SPR_IPA2U_RMASK V850_CPU_RMASK(SPR_IPA2U)
#define V850_SPR_IPA2U_WR    V850_CPU_REG(SPR_IPA2U)
#define V850_SPR_IPA2U_WMASK V850_CPU_WMASK(SPR_IPA2U)

#define V850_SPR_IPA3L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA3L_RD    V850_CPU_REG(SPR_IPA3L)
#define V850_SPR_IPA3L_RMASK V850_CPU_RMASK(SPR_IPA3L)
#define V850_SPR_IPA3L_WR    V850_CPU_REG(SPR_IPA3L)
#define V850_SPR_IPA3L_WMASK V850_CPU_WMASK(SPR_IPA3L)

#define V850_SPR_IPA3U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_IPA3U_RD    V850_CPU_REG(SPR_IPA3U)
#define V850_SPR_IPA3U_RMASK V850_CPU_RMASK(SPR_IPA3U)
#define V850_SPR_IPA3U_WR    V850_CPU_REG(SPR_IPA3U)
#define V850_SPR_IPA3U_WMASK V850_CPU_WMASK(SPR_IPA3U)

#define V850_SPR_DPA0L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA0L_RD    V850_CPU_REG(SPR_DPA0L)
#define V850_SPR_DPA0L_RMASK V850_CPU_RMASK(SPR_DPA0L)
#define V850_SPR_DPA0L_WR    V850_CPU_REG(SPR_DPA0L)
#define V850_SPR_DPA0L_WMASK V850_CPU_WMASK(SPR_DPA0L)

#define V850_SPR_DPA0U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA0U_RD    V850_CPU_REG(SPR_DPA0U)
#define V850_SPR_DPA0U_RMASK V850_CPU_RMASK(SPR_DPA0U)
#define V850_SPR_DPA0U_WR    V850_CPU_REG(SPR_DPA0U)
#define V850_SPR_DPA0U_WMASK V850_CPU_WMASK(SPR_DPA0U)

#define V850_SPR_DPA1L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA1L_RD    V850_CPU_REG(SPR_DPA1L)
#define V850_SPR_DPA1L_RMASK V850_CPU_RMASK(SPR_DPA1L)
#define V850_SPR_DPA1L_WR    V850_CPU_REG(SPR_DPA1L)
#define V850_SPR_DPA1L_WMASK V850_CPU_WMASK(SPR_DPA1L)

#define V850_SPR_DPA1U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA1U_RD    V850_CPU_REG(SPR_DPA1U)
#define V850_SPR_DPA1U_RMASK V850_CPU_RMASK(SPR_DPA1U)
#define V850_SPR_DPA1U_WR    V850_CPU_REG(SPR_DPA1U)
#define V850_SPR_DPA1U_WMASK V850_CPU_WMASK(SPR_DPA1U)

#define V850_SPR_DPA2L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA2L_RD    V850_CPU_REG(SPR_DPA2L)
#define V850_SPR_DPA2L_RMASK V850_CPU_RMASK(SPR_DPA2L)
#define V850_SPR_DPA2L_WR    V850_CPU_REG(SPR_DPA2L)
#define V850_SPR_DPA2L_WMASK V850_CPU_WMASK(SPR_DPA2L)

#define V850_SPR_DPA2U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA2U_RD    V850_CPU_REG(SPR_DPA2U)
#define V850_SPR_DPA2U_RMASK V850_CPU_RMASK(SPR_DPA2U)
#define V850_SPR_DPA2U_WR    V850_CPU_REG(SPR_DPA2U)
#define V850_SPR_DPA2U_WMASK V850_CPU_WMASK(SPR_DPA2U)

#define V850_SPR_DPA3L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA3L_RD    V850_CPU_REG(SPR_DPA3L)
#define V850_SPR_DPA3L_RMASK V850_CPU_RMASK(SPR_DPA3L)
#define V850_SPR_DPA3L_WR    V850_CPU_REG(SPR_DPA3L)
#define V850_SPR_DPA3L_WMASK V850_CPU_WMASK(SPR_DPA3L)

#define V850_SPR_DPA3U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA3U_RD    V850_CPU_REG(SPR_DPA3U)
#define V850_SPR_DPA3U_RMASK V850_CPU_RMASK(SPR_DPA3U)
#define V850_SPR_DPA3U_WR    V850_CPU_REG(SPR_DPA3U)
#define V850_SPR_DPA3U_WMASK V850_CPU_WMASK(SPR_DPA3U)

#define V850_SPR_DPA4L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA4L_RD    V850_CPU_REG(SPR_DPA4L)
#define V850_SPR_DPA4L_RMASK V850_CPU_RMASK(SPR_DPA4L)
#define V850_SPR_DPA4L_WR    V850_CPU_REG(SPR_DPA4L)
#define V850_SPR_DPA4L_WMASK V850_CPU_WMASK(SPR_DPA4L)

#define V850_SPR_DPA4U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA4U_RD    V850_CPU_REG(SPR_DPA4U)
#define V850_SPR_DPA4U_RMASK V850_CPU_RMASK(SPR_DPA4U)
#define V850_SPR_DPA4U_WR    V850_CPU_REG(SPR_DPA4U)
#define V850_SPR_DPA4U_WMASK V850_CPU_WMASK(SPR_DPA4U)

#define V850_SPR_DPA5L_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA5L_RD    V850_CPU_REG(SPR_DPA5L)
#define V850_SPR_DPA5L_RMASK V850_CPU_RMASK(SPR_DPA5L)
#define V850_SPR_DPA5L_WR    V850_CPU_REG(SPR_DPA5L)
#define V850_SPR_DPA5L_WMASK V850_CPU_WMASK(SPR_DPA5L)

#define V850_SPR_DPA5U_BITS (sizeof(Uns32) * 8)
#define V850_SPR_DPA5U_RD    V850_CPU_REG(SPR_DPA5U)
#define V850_SPR_DPA5U_RMASK V850_CPU_RMASK(SPR_DPA5U)
#define V850_SPR_DPA5U_WR    V850_CPU_REG(SPR_DPA5U)
#define V850_SPR_DPA5U_WMASK V850_CPU_WMASK(SPR_DPA5U)

#define V850_SPR_VIP_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VIP_RD    V850_CPU_REG(SPR_VIP)
#define V850_SPR_VIP_RMASK V850_CPU_RMASK(SPR_VIP)
#define V850_SPR_VIP_WR    V850_CPU_REG(SPR_VIP)
#define V850_SPR_VIP_WMASK V850_CPU_WMASK(SPR_VIP)

#define V850_SPR_VMECR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VMECR_RD    V850_CPU_REG(SPR_VMECR)
#define V850_SPR_VMECR_RMASK V850_CPU_RMASK(SPR_VMECR)
#define V850_SPR_VMECR_WR    V850_CPU_REG(SPR_VMECR)
#define V850_SPR_VMECR_WMASK V850_CPU_WMASK(SPR_VMECR)

#define V850_SPR_VMTID_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VMTID_RD    V850_CPU_REG(SPR_VMTID)
#define V850_SPR_VMTID_RMASK V850_CPU_RMASK(SPR_VMTID)
#define V850_SPR_VMTID_WR    V850_CPU_REG(SPR_VMTID)
#define V850_SPR_VMTID_WMASK V850_CPU_WMASK(SPR_VMTID)

#define V850_SPR_VMADR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VMADR_RD    V850_CPU_REG(SPR_VMADR)
#define V850_SPR_VMADR_RMASK V850_CPU_RMASK(SPR_VMADR)
#define V850_SPR_VMADR_WR    V850_CPU_REG(SPR_VMADR)
#define V850_SPR_VMADR_WMASK V850_CPU_WMASK(SPR_VMADR)

#define V850_SPR_VPECR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VPECR_RD    V850_CPU_REG(SPR_VPECR)
#define V850_SPR_VPECR_RMASK V850_CPU_RMASK(SPR_VPECR)
#define V850_SPR_VPECR_WR    V850_CPU_REG(SPR_VPECR)
#define V850_SPR_VPECR_WMASK V850_CPU_WMASK(SPR_VPECR)

#define V850_SPR_VPTID_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VPTID_RD    V850_CPU_REG(SPR_VPTID)
#define V850_SPR_VPTID_RMASK V850_CPU_RMASK(SPR_VPTID)
#define V850_SPR_VPTID_WR    V850_CPU_REG(SPR_VPTID)
#define V850_SPR_VPTID_WMASK V850_CPU_WMASK(SPR_VPTID)

#define V850_SPR_VPADR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VPADR_RD    V850_CPU_REG(SPR_VPADR)
#define V850_SPR_VPADR_RMASK V850_CPU_RMASK(SPR_VPADR)
#define V850_SPR_VPADR_WR    V850_CPU_REG(SPR_VPADR)
#define V850_SPR_VPADR_WMASK V850_CPU_WMASK(SPR_VPADR)

#define V850_SPR_VDECR0_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VDECR0_RD    V850_CPU_REG(SPR_VDECR0)
#define V850_SPR_VDECR0_RMASK V850_CPU_RMASK(SPR_VDECR0)
#define V850_SPR_VDECR0_WR    V850_CPU_REG(SPR_VDECR0)
#define V850_SPR_VDECR0_WMASK V850_CPU_WMASK(SPR_VDECR0)

#define V850_SPR_VDTID0_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VDTID0_RD    V850_CPU_REG(SPR_VDTID0)
#define V850_SPR_VDTID0_RMASK V850_CPU_RMASK(SPR_VDTID0)
#define V850_SPR_VDTID0_WR    V850_CPU_REG(SPR_VDTID0)
#define V850_SPR_VDTID0_WMASK V850_CPU_WMASK(SPR_VDTID0)

#define V850_SPR_VDECR1_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VDECR1_RD    V850_CPU_REG(SPR_VDECR1)
#define V850_SPR_VDECR1_RMASK V850_CPU_RMASK(SPR_VDECR1)
#define V850_SPR_VDECR1_WR    V850_CPU_REG(SPR_VDECR1)
#define V850_SPR_VDECR1_WMASK V850_CPU_WMASK(SPR_VDECR1)

#define V850_SPR_VDTID1_BITS (sizeof(Uns32) * 8)
#define V850_SPR_VDTID1_RD    V850_CPU_REG(SPR_VDTID1)
#define V850_SPR_VDTID1_RMASK V850_CPU_RMASK(SPR_VDTID1)
#define V850_SPR_VDTID1_WR    V850_CPU_REG(SPR_VDTID1)
#define V850_SPR_VDTID1_WMASK V850_CPU_WMASK(SPR_VDTID1)

#define V850_SPR_FPSR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPSR_RD    V850_CPU_REG(SPR_FPSR)
#define V850_SPR_FPSR_RMASK V850_CPU_RMASK(SPR_FPSR)
#define V850_SPR_FPSR_WR    V850_CPU_REG(SPR_FPSR)
#define V850_SPR_FPSR_WMASK V850_CPU_WMASK(SPR_FPSR)

#define V850_SPR_FPEPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPEPC_RD    V850_CPU_REG(SPR_FPEPC)
#define V850_SPR_FPEPC_RMASK V850_CPU_RMASK(SPR_FPEPC)
#define V850_SPR_FPEPC_WR    V850_CPU_REG(SPR_FPEPC)
#define V850_SPR_FPEPC_WMASK V850_CPU_WMASK(SPR_FPEPC)

#define V850_SPR_FPST_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPST_RD    V850_CPU_REG(SPR_FPST)
#define V850_SPR_FPST_RMASK V850_CPU_RMASK(SPR_FPST)
#define V850_SPR_FPST_WR    V850_CPU_REG(SPR_FPST)
#define V850_SPR_FPST_WMASK V850_CPU_WMASK(SPR_FPST)

#define V850_SPR_FPCC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPCC_RD    V850_CPU_REG(SPR_FPCC)
#define V850_SPR_FPCC_RMASK V850_CPU_RMASK(SPR_FPCC)
#define V850_SPR_FPCC_WR    V850_CPU_REG(SPR_FPCC)
#define V850_SPR_FPCC_WMASK V850_CPU_WMASK(SPR_FPCC)

#define V850_SPR_FPCFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPCFG_RD    V850_CPU_REG(SPR_FPCFG)
#define V850_SPR_FPCFG_RMASK V850_CPU_RMASK(SPR_FPCFG)
#define V850_SPR_FPCFG_WR    V850_CPU_REG(SPR_FPCFG)
#define V850_SPR_FPCFG_WMASK V850_CPU_WMASK(SPR_FPCFG)

#define V850_SPR_FPEC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPEC_RD    V850_CPU_REG(SPR_FPEC)
#define V850_SPR_FPEC_RMASK V850_CPU_RMASK(SPR_FPEC)
#define V850_SPR_FPEC_WR    V850_CPU_REG(SPR_FPEC)
#define V850_SPR_FPEC_WMASK V850_CPU_WMASK(SPR_FPEC)

#define V850_SPR_BPC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_BPC_RD    V850_CPU_REG(SPR_BPC)
#define V850_SPR_BPC_RMASK V850_CPU_RMASK(SPR_BPC)
#define V850_SPR_BPC_WR    V850_CPU_REG(SPR_BPC)
#define V850_SPR_BPC_WMASK V850_CPU_WMASK(SPR_BPC)

#define V850_SPR_ASID_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ASID_RD    V850_CPU_REG(SPR_ASID)
#define V850_SPR_ASID_RMASK V850_CPU_RMASK(SPR_ASID)
#define V850_SPR_ASID_WR    V850_CPU_REG(SPR_ASID)
#define V850_SPR_ASID_WMASK V850_CPU_WMASK(SPR_ASID)

#define V850_SPR_BPAV_BITS (sizeof(Uns32) * 8)
#define V850_SPR_BPAV_RD    V850_CPU_REG(SPR_BPAV)
#define V850_SPR_BPAV_RMASK V850_CPU_RMASK(SPR_BPAV)
#define V850_SPR_BPAV_WR    V850_CPU_REG(SPR_BPAV)
#define V850_SPR_BPAV_WMASK V850_CPU_WMASK(SPR_BPAV)

#define V850_SPR_BPAM_BITS (sizeof(Uns32) * 8)
#define V850_SPR_BPAM_RD    V850_CPU_REG(SPR_BPAM)
#define V850_SPR_BPAM_RMASK V850_CPU_RMASK(SPR_BPAM)
#define V850_SPR_BPAM_WR    V850_CPU_REG(SPR_BPAM)
#define V850_SPR_BPAM_WMASK V850_CPU_WMASK(SPR_BPAM)

#define V850_SPR_BPDV_BITS (sizeof(Uns32) * 8)
#define V850_SPR_BPDV_RD    V850_CPU_REG(SPR_BPDV)
#define V850_SPR_BPDV_RMASK V850_CPU_RMASK(SPR_BPDV)
#define V850_SPR_BPDV_WR    V850_CPU_REG(SPR_BPDV)
#define V850_SPR_BPDV_WMASK V850_CPU_WMASK(SPR_BPDV)

#define V850_SPR_BPDM_BITS (sizeof(Uns32) * 8)
#define V850_SPR_BPDM_RD    V850_CPU_REG(SPR_BPDM)
#define V850_SPR_BPDM_RMASK V850_CPU_RMASK(SPR_BPDM)
#define V850_SPR_BPDM_WR    V850_CPU_REG(SPR_BPDM)
#define V850_SPR_BPDM_WMASK V850_CPU_WMASK(SPR_BPDM)

#define V850_SPR_EFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EFG_RD V850_CPU_REG(SPR_EFG)
#define V850_SPR_EFG_WR V850_CPU_REG(SPR_EFG)
#define V850_SPR_EFG_RMASK V850_CPU_RMASK(SPR_EFG)
#define V850_SPR_EFG_WMASK V850_CPU_WMASK(SPR_EFG)

#define V850_SPR_ECT_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ECT_RD V850_CPU_REG(SPR_ECT)
#define V850_SPR_ECT_WR V850_CPU_REG(SPR_ECT)
#define V850_SPR_ECT_WMASK V850_CPU_WMASK(SPR_ECT)

#define V850_SPR_MCFG0_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MCFG0_RD V850_CPU_REG(SPR_MCFG0)
#define V850_SPR_MCFG0_WR V850_CPU_REG(SPR_MCFG0)
#define V850_SPR_MCFG0_RMASK V850_CPU_RMASK(SPR_MCFG0)
#define V850_SPR_MCFG0_WMASK V850_CPU_WMASK(SPR_MCFG0)

#define V850_SPR_RBASE_BITS (sizeof(Uns32) * 8)
#define V850_SPR_RBASE_RD V850_CPU_REG(SPR_RBASE)
#define V850_SPR_RBASE_WR V850_CPU_REG(SPR_RBASE)
#define V850_SPR_RBASE_RMASK V850_CPU_RMASK(SPR_RBASE)
#define V850_SPR_RBASE_WMASK V850_CPU_WMASK(SPR_RBASE)

#define V850_SPR_EBASE_BITS (sizeof(Uns32) * 8)
#define V850_SPR_EBASE_RD V850_CPU_REG(SPR_EBASE)
#define V850_SPR_EBASE_WR V850_CPU_REG(SPR_EBASE)
#define V850_SPR_EBASE_RMASK V850_CPU_RMASK(SPR_EBASE)
#define V850_SPR_EBASE_WMASK V850_CPU_WMASK(SPR_EBASE)

#define V850_SPR_INTBP_BITS (sizeof(Uns32) * 8)
#define V850_SPR_INTBP_RD V850_CPU_REG(SPR_INTBP)
#define V850_SPR_INTBP_WR V850_CPU_REG(SPR_INTBP)
#define V850_SPR_INTBP_RMASK V850_CPU_RMASK(SPR_INTBP)
#define V850_SPR_INTBP_WMASK V850_CPU_WMASK(SPR_INTBP)

#define V850_SPR_MCTL_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MCTL_RD V850_CPU_REG(SPR_MCTL)
#define V850_SPR_MCTL_WR V850_CPU_REG(SPR_MCTL)
#define V850_SPR_MCTL_RMASK V850_CPU_RMASK(SPR_MCTL)
#define V850_SPR_MCTL_WMASK V850_CPU_WMASK(SPR_MCTL)

#define V850_SPR_PID_BITS (sizeof(Uns32) * 8)
#define V850_SPR_PID_RD V850_CPU_REG(SPR_PID)
#define V850_SPR_PID_WR V850_CPU_REG(SPR_PID)
#define V850_SPR_PID_RMASK V850_CPU_RMASK(SPR_PID)
#define V850_SPR_PID_WMASK V850_CPU_WMASK(SPR_PID)

#define V850_SPR_FPIPR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_FPIPR_RD V850_CPU_REG(SPR_FPIPR)
#define V850_SPR_FPIPR_WR V850_CPU_REG(SPR_FPIPR)
#define V850_SPR_FPIPR_RMASK V850_CPU_RMASK(SPR_FPIPR)
#define V850_SPR_FPIPR_WMASK V850_CPU_WMASK(SPR_FPIPR)

#define V850_SPR_SCCFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_SCCFG_RD V850_CPU_REG(SPR_SCCFG)
#define V850_SPR_SCCFG_WR V850_CPU_REG(SPR_SCCFG)
#define V850_SPR_SCCFG_RMASK V850_CPU_RMASK(SPR_SCCFG)
#define V850_SPR_SCCFG_WMASK V850_CPU_WMASK(SPR_SCCFG)

#define V850_SPR_SCBP_BITS (sizeof(Uns32) * 8)
#define V850_SPR_SCBP_RD V850_CPU_REG(SPR_SCBP)
#define V850_SPR_SCBP_WR V850_CPU_REG(SPR_SCBP)
#define V850_SPR_SCBP_RMASK V850_CPU_RMASK(SPR_SCBP)
#define V850_SPR_SCBP_WMASK V850_CPU_WMASK(SPR_SCBP)

#define V850_SPR_HTCFG0_BITS (sizeof(Uns32) * 8)
#define V850_SPR_HTCFG0_RD V850_CPU_REG(SPR_HTCFG0)
#define V850_SPR_HTCFG0_WR V850_CPU_REG(SPR_HTCFG0)
#define V850_SPR_HTCFG0_RMASK V850_CPU_RMASK(SPR_HTCFG0)
#define V850_SPR_HTCFG0_WMASK V850_CPU_WMASK(SPR_HTCFG0)

#define V850_SPR_MEA_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MEA_RD V850_CPU_REG(SPR_MEA)
#define V850_SPR_MEA_WR V850_CPU_REG(SPR_MEA)
#define V850_SPR_MEA_RMASK V850_CPU_RMASK(SPR_MEA)
#define V850_SPR_MEA_WMASK V850_CPU_WMASK(SPR_MEA)

#define V850_SPR_MEI_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MEI_RD V850_CPU_REG(SPR_MEI)
#define V850_SPR_MEI_WR V850_CPU_REG(SPR_MEI)
#define V850_SPR_MEI_RMASK V850_CPU_RMASK(SPR_MEI)
#define V850_SPR_MEI_WMASK V850_CPU_WMASK(SPR_MEI)

#define V850_SPR_ISPR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ISPR_RD V850_CPU_REG(SPR_ISPR)
#define V850_SPR_ISPR_WR V850_CPU_REG(SPR_ISPR)
#define V850_SPR_ISPR_RMASK V850_CPU_RMASK(SPR_ISPR)
#define V850_SPR_ISPR_WMASK V850_CPU_WMASK(SPR_ISPR)

#define V850_SPR_PMR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_PMR_RD V850_CPU_REG(SPR_PMR)
#define V850_SPR_PMR_WR V850_CPU_REG(SPR_PMR)
#define V850_SPR_PMR_RMASK V850_CPU_RMASK(SPR_PMR)
#define V850_SPR_PMR_WMASK V850_CPU_WMASK(SPR_PMR)

#define V850_SPR_ICSR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICSR_RD V850_CPU_REG(SPR_ICSR)
#define V850_SPR_ICSR_WR V850_CPU_REG(SPR_ICSR)
#define V850_SPR_ICSR_RMASK V850_CPU_RMASK(SPR_ICSR)
#define V850_SPR_ICSR_WMASK V850_CPU_WMASK(SPR_ICSR)

#define V850_SPR_INTCFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_INTCFG_RD V850_CPU_REG(SPR_INTCFG)
#define V850_SPR_INTCFG_WR V850_CPU_REG(SPR_INTCFG)
#define V850_SPR_INTCFG_RMASK V850_CPU_RMASK(SPR_INTCFG)
#define V850_SPR_INTCFG_WMASK V850_CPU_WMASK(SPR_INTCFG)

#define V850_SPR_MPRC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPRC_RD V850_CPU_REG(SPR_MPRC)
#define V850_SPR_MPRC_WR V850_CPU_REG(SPR_MPRC)
#define V850_SPR_MPRC_RMASK V850_CPU_RMASK(SPR_MPRC)
#define V850_SPR_MPRC_WMASK V850_CPU_WMASK(SPR_MPRC)

#define V850_SPR_MPBRGN_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPBRGN_RD V850_CPU_REG(SPR_MPBRGN)
#define V850_SPR_MPBRGN_WR V850_CPU_REG(SPR_MPBRGN)
#define V850_SPR_MPBRGN_RMASK V850_CPU_RMASK(SPR_MPBRGN)
#define V850_SPR_MPBRGN_WMASK V850_CPU_WMASK(SPR_MPBRGN)

#define V850_SPR_MPTRGN_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPTRGN_RD V850_CPU_REG(SPR_MPTRGN)
#define V850_SPR_MPTRGN_WR V850_CPU_REG(SPR_MPTRGN)
#define V850_SPR_MPTRGN_RMASK V850_CPU_RMASK(SPR_MPTRGN)
#define V850_SPR_MPTRGN_WMASK V850_CPU_WMASK(SPR_MPTRGN)

#define V850_SPR_MCA_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MCA_RD V850_CPU_REG(SPR_MCA)
#define V850_SPR_MCA_WR V850_CPU_REG(SPR_MCA)
#define V850_SPR_MCA_RMASK V850_CPU_RMASK(SPR_MCA)
#define V850_SPR_MCA_WMASK V850_CPU_WMASK(SPR_MCA)

#define V850_SPR_MCS_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MCS_RD V850_CPU_REG(SPR_MCS)
#define V850_SPR_MCS_WR V850_CPU_REG(SPR_MCS)
#define V850_SPR_MCS_RMASK V850_CPU_RMASK(SPR_MCS)
#define V850_SPR_MCS_WMASK V850_CPU_WMASK(SPR_MCS)

#define V850_SPR_MCC_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MCC_RD V850_CPU_REG(SPR_MCC)
#define V850_SPR_MCC_WR V850_CPU_REG(SPR_MCC)
#define V850_SPR_MCC_RMASK V850_CPU_RMASK(SPR_MCC)
#define V850_SPR_MCC_WMASK V850_CPU_WMASK(SPR_MCC)

#define V850_SPR_MCR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MCR_RD V850_CPU_REG(SPR_MCR)
#define V850_SPR_MCR_WR V850_CPU_REG(SPR_MCR)
#define V850_SPR_MCR_RMASK V850_CPU_RMASK(SPR_MCR)
#define V850_SPR_MCR_WMASK V850_CPU_WMASK(SPR_MCR)

#define V850_SPR_MPLA_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPLA_RD(_I)    V850_CPU_REG(SPR_MPLA[_I])
#define V850_SPR_MPLA_WR(_I)    V850_CPU_REG(SPR_MPLA[_I])
#define V850_SPR_MPLA_RMASK(_I) V850_CPU_OFFSET(SPR_MPLA_rmask[_I])
#define V850_SPR_MPLA_WMASK(_I) V850_CPU_OFFSET(SPR_MPLA_wmask[_I])

#define V850_SPR_MPUA_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPUA_RD(_I)    V850_CPU_REG(SPR_MPUA[_I])
#define V850_SPR_MPUA_WR(_I)    V850_CPU_REG(SPR_MPUA[_I])
#define V850_SPR_MPUA_RMASK(_I) V850_CPU_OFFSET(SPR_MPUA_rmask[_I])
#define V850_SPR_MPUA_WMASK(_I) V850_CPU_OFFSET(SPR_MPUA_wmask[_I])

#define V850_SPR_MPAT_BITS (sizeof(Uns32) * 8)
#define V850_SPR_MPAT_RD(_I)    V850_CPU_REG(SPR_MPAT[_I])
#define V850_SPR_MPAT_WR(_I)    V850_CPU_REG(SPR_MPAT[_I])
#define V850_SPR_MPAT_RMASK(_I) V850_CPU_OFFSET(SPR_MPAT_rmask[_I])
#define V850_SPR_MPAT_WMASK(_I) V850_CPU_OFFSET(SPR_MPAT_wmask[_I])

#define V850_SPR_ICTAGL_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICTAGL_RD      V850_CPU_REG(SPR_ICTAGL)
#define V850_SPR_ICTAGL_WR      V850_CPU_REG(SPR_ICTAGL)
#define V850_SPR_ICTAGL_RMASK V850_CPU_RMASK(SPR_ICTAGL)
#define V850_SPR_ICTAGL_WMASK V850_CPU_WMASK(SPR_ICTAGL)

#define V850_SPR_ICTAGH_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICTAGH_RD      V850_CPU_REG(SPR_ICTAGH)
#define V850_SPR_ICTAGH_WR      V850_CPU_REG(SPR_ICTAGH)
#define V850_SPR_ICTAGH_RMASK V850_CPU_RMASK(SPR_ICTAGH)
#define V850_SPR_ICTAGH_WMASK V850_CPU_WMASK(SPR_ICTAGH)

#define V850_SPR_ICDATL_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICDATL_RD      V850_CPU_REG(SPR_ICDATL)
#define V850_SPR_ICDATL_WR      V850_CPU_REG(SPR_ICDATL)
#define V850_SPR_ICDATL_RMASK V850_CPU_RMASK(SPR_ICDATL)
#define V850_SPR_ICDATL_WMASK V850_CPU_WMASK(SPR_ICDATL)

#define V850_SPR_ICDATH_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICDATH_RD      V850_CPU_REG(SPR_ICDATH)
#define V850_SPR_ICDATH_WR      V850_CPU_REG(SPR_ICDATH)
#define V850_SPR_ICDATH_RMASK V850_CPU_RMASK(SPR_ICDATH)
#define V850_SPR_ICDATH_WMASK V850_CPU_WMASK(SPR_ICDATH)

#define V850_SPR_ICCTRL_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICCTRL_RD      V850_CPU_REG(SPR_ICCTRL)
#define V850_SPR_ICCTRL_WR      V850_CPU_REG(SPR_ICCTRL)
#define V850_SPR_ICCTRL_RMASK V850_CPU_RMASK(SPR_ICCTRL)
#define V850_SPR_ICCTRL_WMASK V850_CPU_WMASK(SPR_ICCTRL)

#define V850_SPR_ICCFG_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICCFG_RD      V850_CPU_REG(SPR_ICCFG)
#define V850_SPR_ICCFG_WR      V850_CPU_REG(SPR_ICCFG)
#define V850_SPR_ICCFG_RMASK V850_CPU_RMASK(SPR_ICCFG)
#define V850_SPR_ICCFG_WMASK V850_CPU_WMASK(SPR_ICCFG)

#define V850_SPR_ICERR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_ICERR_RD      V850_CPU_REG(SPR_ICERR)
#define V850_SPR_ICERR_WR      V850_CPU_REG(SPR_ICERR)
#define V850_SPR_ICERR_RMASK V850_CPU_RMASK(SPR_ICERR)
#define V850_SPR_ICERR_WMASK V850_CPU_WMASK(SPR_ICERR)

#define V850_SPR_CDBCR_BITS (sizeof(Uns32) * 8)
#define V850_SPR_CDBCR_RD      V850_CPU_REG(SPR_CDBCR)
#define V850_SPR_CDBCR_WR      V850_CPU_REG(SPR_CDBCR)
#define V850_SPR_CDBCR_RMASK V850_CPU_RMASK(SPR_CDBCR)
#define V850_SPR_CDBCR_WMASK V850_CPU_WMASK(SPR_CDBCR)

#define V850_TMP_BITS (sizeof(Uns32) * 8)
#define V850_TMP_RD(_R) V850_CPU_TEMP(tmp[_R])
#define V850_TMP_WR(_R) V850_CPU_TEMP(tmp[_R])

#define V850_FLG_PSW_SAT_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_SAT_RD V850_CPU_REG(FLG_PSW_SAT)
#define V850_FLG_PSW_SAT_WR V850_CPU_REG(FLG_PSW_SAT)

#define V850_FLG_PSW_ID_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_ID_RD V850_CPU_REG(FLG_PSW_ID)
#define V850_FLG_PSW_ID_WR V850_CPU_REG(FLG_PSW_ID)

#define V850_FLG_PSW_EP_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_EP_RD V850_CPU_REG(FLG_PSW_EP)
#define V850_FLG_PSW_EP_WR V850_CPU_REG(FLG_PSW_EP)

#define V850_FLG_PSW_NP_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_NP_RD V850_CPU_REG(FLG_PSW_NP)
#define V850_FLG_PSW_NP_WR V850_CPU_REG(FLG_PSW_NP)

#define V850_FLG_FPF_BITS (sizeof(Uns8) * 8)
#define V850_FLG_FPF_RD V850_CPU_REG(FLG_FPF)
#define V850_FLG_FPF_WR V850_CPU_REG(FLG_FPF)

#define V850_FLG_FPF_STICKY_BITS (sizeof(Uns8) * 8)
#define V850_FLG_FPF_STICKY_RD V850_CPU_REG(FLG_FPF_STICKY)
#define V850_FLG_FPF_STICKY_WR V850_CPU_REG(FLG_FPF_STICKY)

#define V850_FLG_EFG_FPZ_BITS (sizeof(Bool) * 8)
#define V850_FLG_EFG_FPZ_RD V850_CPU_REG(FLG_EFG_FPZ)
#define V850_FLG_EFG_FPZ_WR V850_CPU_REG(FLG_EFG_FPZ)

#define V850_FLG_EFG_FPS_BITS (sizeof(Bool) * 8)
#define V850_FLG_EFG_FPS_RD V850_CPU_REG(FLG_EFG_FPS)
#define V850_FLG_EFG_FPS_WR V850_CPU_REG(FLG_EFG_FPS)

#define V850_FLG_EFG_FPOV_BITS (sizeof(Bool) * 8)
#define V850_FLG_EFG_FPOV_RD V850_CPU_REG(FLG_EFG_FPOV)
#define V850_FLG_EFG_FPOV_WR V850_CPU_REG(FLG_EFG_FPOV)

#define V850_FLG_FCMP_BITS (sizeof(Uns8) * 8)
#define V850_FLG_FCMP_RD V850_CPU_TEMP(FLG_FCMP)
#define V850_FLG_FCMP_WR V850_CPU_TEMP(FLG_FCMP)

#define V850_FLG_INTPEND_BITS (sizeof(Bool) * 8)
#define V850_FLG_INTPEND_RD V850_CPU_REG(FLG_INTPEND)
#define V850_FLG_INTPEND_WR V850_CPU_REG(FLG_INTPEND)

#define V850_FLG_NMIPEND_BITS (sizeof(Bool) * 8)
#define V850_FLG_NMIPEND_RD V850_CPU_REG(FLG_NMIPEND)
#define V850_FLG_NMIPEND_WR V850_CPU_REG(FLG_NMIPEND)

#define V850_FLG_TMP_BITS (sizeof(Bool) * 8)
#define V850_FLG_TMP_RD V850_CPU_TEMP(FLG_TMP)
#define V850_FLG_TMP_WR V850_CPU_TEMP(FLG_TMP)

#define V850_FLG_PSW_CO_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_CO_RD V850_CPU_REG(FLG_PSW_CO)
#define V850_FLG_PSW_CO_WR V850_CPU_REG(FLG_PSW_CO)

#define V850_FLG_PSW_ZR_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_ZR_RD V850_CPU_REG(FLG_PSW_ZR)
#define V850_FLG_PSW_ZR_WR V850_CPU_REG(FLG_PSW_ZR)

#define V850_FLG_PSW_SI_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_SI_RD V850_CPU_REG(FLG_PSW_SI)
#define V850_FLG_PSW_SI_WR V850_CPU_REG(FLG_PSW_SI)

#define V850_FLG_PSW_OV_BITS (sizeof(Bool) * 8)
#define V850_FLG_PSW_OV_RD V850_CPU_REG(FLG_PSW_OV)
#define V850_FLG_PSW_OV_WR V850_CPU_REG(FLG_PSW_OV)

#define V850_LLSIZE 32

#define V850_FLG_LL_BITS (sizeof(Bool) * 8)
#define V850_FLG_LL V850_CPU_REG(FLG_LL)

#define V850_REG_LL_BITS (sizeof(Uns32) * 8)
#define V850_REG_LL V850_CPU_REG(REG_LL)

#define V850_FLG_FPSR_CC_BITS (sizeof(Uns8) * 8)
#define V850_FLG_FPSR_CC_RD(_R) V850_CPU_REG(FLG_FPSR_CC[_R])
#define V850_FLG_FPSR_CC_WR(_R) V850_CPU_REG(FLG_FPSR_CC[_R])

#define V850_CPU_REG_CONST(_F) VMI_CPU_REG_CONST(v850P, _F)
#define V850_CPU_TEMP_CONST(_F) VMI_CPU_TEMP_CONST(v850P, _F)
#define V850_GPR_CONST(_R) V850_CPU_REG_CONST(gpr[_R])

#define V850_SPR_EIWR_CONST V850_CPU_REG_CONST(SPR_EIWR)

#define V850_SPR_FEWR_CONST V850_CPU_REG_CONST(SPR_FEWR)

#define V850_SPR_DBWR_CONST V850_CPU_REG_CONST(SPR_DBWR)

#define V850_SPR_BSEL_CONST V850_CPU_REG_CONST(SPR_BSEL)

#define V850_SPR_EIPC_CONST V850_CPU_REG_CONST(SPR_EIPC)

#define V850_SPR_EIPSW_CONST V850_CPU_REG_CONST(SPR_EIPSW)

#define V850_SPR_FEPC_CONST V850_CPU_REG_CONST(SPR_FEPC)

#define V850_SPR_FEPSW_CONST V850_CPU_REG_CONST(SPR_FEPSW)

#define V850_SPR_ECR_CONST V850_CPU_REG_CONST(SPR_ECR)

#define V850_SPR_PSW_CONST V850_CPU_REG_CONST(SPR_PSW)

#define V850_SPR_EIIC_CONST V850_CPU_REG_CONST(SPR_EIIC)

#define V850_SPR_FEIC_CONST V850_CPU_REG_CONST(SPR_FEIC)

#define V850_SPR_DBIC_CONST V850_CPU_REG_CONST(SPR_DBIC)

#define V850_SPR_CTPC_CONST V850_CPU_REG_CONST(SPR_CTPC)

#define V850_SPR_CTPSW_CONST V850_CPU_REG_CONST(SPR_CTPSW)

#define V850_SPR_DBPC_CONST V850_CPU_REG_CONST(SPR_DBPC)

#define V850_SPR_DBPSW_CONST V850_CPU_REG_CONST(SPR_DBPSW)

#define V850_SPR_CTBP_CONST V850_CPU_REG_CONST(SPR_CTBP)

#define V850_SPR_DIR_CONST V850_CPU_REG_CONST(SPR_DIR)

#define V850_SPR_SW_CTL_CONST V850_CPU_REG_CONST(SPR_SW_CTL)

#define V850_SPR_SW_CFG_CONST V850_CPU_REG_CONST(SPR_SW_CFG)

#define V850_SPR_SW_BASE_CONST V850_CPU_REG_CONST(SPR_SW_BASE)

#define V850_SPR_EH_CFG_CONST V850_CPU_REG_CONST(SPR_EH_CFG)

#define V850_SPR_EH_BASE_CONST V850_CPU_REG_CONST(SPR_EH_BASE)

#define V850_SPR_EH_RESET_CONST V850_CPU_REG_CONST(SPR_EH_RESET)

#define V850_SPR_MPM_CONST V850_CPU_REG_CONST(SPR_MPM)

#define V850_SPR_MPC_CONST V850_CPU_REG_CONST(SPR_MPC)

#define V850_SPR_TID_CONST V850_CPU_REG_CONST(SPR_TID)

#define V850_SPR_PPC_CONST V850_CPU_REG_CONST(SPR_PPC)

#define V850_SPR_DCC0_CONST V850_CPU_REG_CONST(SPR_DCC0)

#define V850_SPR_DCV0_CONST V850_CPU_REG_CONST(SPR_DCV0)

#define V850_SPR_DCC1_CONST V850_CPU_REG_CONST(SPR_DCC1)

#define V850_SPR_DCV1_CONST V850_CPU_REG_CONST(SPR_DCV1)

#define V850_SPR_IPA0L_CONST V850_CPU_REG_CONST(SPR_IPA0L)

#define V850_SPR_IPA0U_CONST V850_CPU_REG_CONST(SPR_IPA0U)

#define V850_SPR_IPA1L_CONST V850_CPU_REG_CONST(SPR_IPA1L)

#define V850_SPR_IPA1U_CONST V850_CPU_REG_CONST(SPR_IPA1U)

#define V850_SPR_IPA2L_CONST V850_CPU_REG_CONST(SPR_IPA2L)

#define V850_SPR_IPA2U_CONST V850_CPU_REG_CONST(SPR_IPA2U)

#define V850_SPR_IPA3L_CONST V850_CPU_REG_CONST(SPR_IPA3L)

#define V850_SPR_IPA3U_CONST V850_CPU_REG_CONST(SPR_IPA3U)

#define V850_SPR_DPA0L_CONST V850_CPU_REG_CONST(SPR_DPA0L)

#define V850_SPR_DPA0U_CONST V850_CPU_REG_CONST(SPR_DPA0U)

#define V850_SPR_DPA1L_CONST V850_CPU_REG_CONST(SPR_DPA1L)

#define V850_SPR_DPA1U_CONST V850_CPU_REG_CONST(SPR_DPA1U)

#define V850_SPR_DPA2L_CONST V850_CPU_REG_CONST(SPR_DPA2L)

#define V850_SPR_DPA2U_CONST V850_CPU_REG_CONST(SPR_DPA2U)

#define V850_SPR_DPA3L_CONST V850_CPU_REG_CONST(SPR_DPA3L)

#define V850_SPR_DPA3U_CONST V850_CPU_REG_CONST(SPR_DPA3U)

#define V850_SPR_DPA4L_CONST V850_CPU_REG_CONST(SPR_DPA4L)

#define V850_SPR_DPA4U_CONST V850_CPU_REG_CONST(SPR_DPA4U)

#define V850_SPR_DPA5L_CONST V850_CPU_REG_CONST(SPR_DPA5L)

#define V850_SPR_DPA5U_CONST V850_CPU_REG_CONST(SPR_DPA5U)

#define V850_SPR_VIP_CONST V850_CPU_REG_CONST(SPR_VIP)

#define V850_SPR_VMECR_CONST V850_CPU_REG_CONST(SPR_VMECR)

#define V850_SPR_VMTID_CONST V850_CPU_REG_CONST(SPR_VMTID)

#define V850_SPR_VMADR_CONST V850_CPU_REG_CONST(SPR_VMADR)

#define V850_SPR_VPECR_CONST V850_CPU_REG_CONST(SPR_VPECR)

#define V850_SPR_VPTID_CONST V850_CPU_REG_CONST(SPR_VPTID)

#define V850_SPR_VPADR_CONST V850_CPU_REG_CONST(SPR_VPADR)

#define V850_SPR_VDECR0_CONST V850_CPU_REG_CONST(SPR_VDECR0)

#define V850_SPR_VDTID0_CONST V850_CPU_REG_CONST(SPR_VDTID0)

#define V850_SPR_VDECR1_CONST V850_CPU_REG_CONST(SPR_VDECR1)

#define V850_SPR_VDTID1_CONST V850_CPU_REG_CONST(SPR_VDTID1)

#define V850_SPR_FPSR_CONST V850_CPU_REG_CONST(SPR_FPSR)

#define V850_SPR_FPEPC_CONST V850_CPU_REG_CONST(SPR_FPEPC)

#define V850_SPR_FPST_CONST V850_CPU_REG_CONST(SPR_FPST)

#define V850_SPR_FPCC_CONST V850_CPU_REG_CONST(SPR_FPCC)

#define V850_SPR_FPCFG_CONST V850_CPU_REG_CONST(SPR_FPCFG)

#define V850_SPR_FPEC_CONST V850_CPU_REG_CONST(SPR_FPEC)

#define V850_SPR_BPC_CONST V850_CPU_REG_CONST(SPR_BPC)

#define V850_SPR_ASID_CONST V850_CPU_REG_CONST(SPR_ASID)

#define V850_SPR_BPAV_CONST V850_CPU_REG_CONST(SPR_BPAV)

#define V850_SPR_BPAM_CONST V850_CPU_REG_CONST(SPR_BPAM)

#define V850_SPR_BPDV_CONST V850_CPU_REG_CONST(SPR_BPDV)

#define V850_SPR_BPDM_CONST V850_CPU_REG_CONST(SPR_BPDM)

#define V850_SPR_EFG_CONST V850_CPU_REG_CONST(SPR_EFG)

#define V850_SPR_ECT_CONST V850_CPU_REG_CONST(SPR_ECT)

#define V850_SPR_MCFG0_CONST V850_CPU_REG_CONST(SPR_MCFG0)

#define V850_SPR_RBASE_CONST V850_CPU_REG_CONST(SPR_RBASE)

#define V850_SPR_EBASE_CONST V850_CPU_REG_CONST(SPR_EBASE)

#define V850_SPR_INTBP_CONST V850_CPU_REG_CONST(SPR_INTBP)

#define V850_SPR_MCTL_CONST V850_CPU_REG_CONST(SPR_MCTL)

#define V850_SPR_PID_CONST V850_CPU_REG_CONST(SPR_PID)

#define V850_SPR_FPIPR_CONST V850_CPU_REG_CONST(SPR_FPIPR)

#define V850_SPR_SCCFG_CONST V850_CPU_REG_CONST(SPR_SCCFG)

#define V850_SPR_SCBP_CONST V850_CPU_REG_CONST(SPR_SCBP)

#define V850_SPR_HTCFG0_CONST V850_CPU_REG_CONST(SPR_HTCFG0)

#define V850_SPR_MEA_CONST V850_CPU_REG_CONST(SPR_MEA)

#define V850_SPR_MEI_CONST V850_CPU_REG_CONST(SPR_MEI)

#define V850_SPR_ISPR_CONST V850_CPU_REG_CONST(SPR_ISPR)

#define V850_SPR_PMR_CONST V850_CPU_REG_CONST(SPR_PMR)

#define V850_SPR_ICSR_CONST V850_CPU_REG_CONST(SPR_ICSR)

#define V850_SPR_INTCFG_CONST V850_CPU_REG_CONST(SPR_INTCFG)

#define V850_SPR_MPRC_CONST V850_CPU_REG_CONST(SPR_MPRC)

#define V850_SPR_MPBRGN_CONST V850_CPU_REG_CONST(SPR_MPBRGN)

#define V850_SPR_MPTRGN_CONST V850_CPU_REG_CONST(SPR_MPTRGN)

#define V850_SPR_MCA_CONST V850_CPU_REG_CONST(SPR_MCA)

#define V850_SPR_MCS_CONST V850_CPU_REG_CONST(SPR_MCS)

#define V850_SPR_MCC_CONST V850_CPU_REG_CONST(SPR_MCC)

#define V850_SPR_MCR_CONST V850_CPU_REG_CONST(SPR_MCR)

#define V850_SPR_MPLA0_CONST  V850_CPU_REG_CONST(SPR_MPLA0)
#define V850_SPR_MPLA1_CONST  V850_CPU_REG_CONST(SPR_MPLA1)
#define V850_SPR_MPLA2_CONST  V850_CPU_REG_CONST(SPR_MPLA2)
#define V850_SPR_MPLA3_CONST  V850_CPU_REG_CONST(SPR_MPLA3)
#define V850_SPR_MPLA4_CONST  V850_CPU_REG_CONST(SPR_MPLA4)
#define V850_SPR_MPLA5_CONST  V850_CPU_REG_CONST(SPR_MPLA5)
#define V850_SPR_MPLA6_CONST  V850_CPU_REG_CONST(SPR_MPLA6)
#define V850_SPR_MPLA7_CONST  V850_CPU_REG_CONST(SPR_MPLA7)
#define V850_SPR_MPLA8_CONST  V850_CPU_REG_CONST(SPR_MPLA8)
#define V850_SPR_MPLA9_CONST  V850_CPU_REG_CONST(SPR_MPLA9)
#define V850_SPR_MPLA10_CONST V850_CPU_REG_CONST(SPR_MPLA10)
#define V850_SPR_MPLA11_CONST V850_CPU_REG_CONST(SPR_MPLA11)
#define V850_SPR_MPLA12_CONST V850_CPU_REG_CONST(SPR_MPLA12)
#define V850_SPR_MPLA13_CONST V850_CPU_REG_CONST(SPR_MPLA13)
#define V850_SPR_MPLA14_CONST V850_CPU_REG_CONST(SPR_MPLA14)
#define V850_SPR_MPLA15_CONST V850_CPU_REG_CONST(SPR_MPLA15)

#define V850_SPR_MPUA0_CONST  V850_CPU_REG_CONST(SPR_MPUA0)
#define V850_SPR_MPUA1_CONST  V850_CPU_REG_CONST(SPR_MPUA1)
#define V850_SPR_MPUA2_CONST  V850_CPU_REG_CONST(SPR_MPUA2)
#define V850_SPR_MPUA3_CONST  V850_CPU_REG_CONST(SPR_MPUA3)
#define V850_SPR_MPUA4_CONST  V850_CPU_REG_CONST(SPR_MPUA4)
#define V850_SPR_MPUA5_CONST  V850_CPU_REG_CONST(SPR_MPUA5)
#define V850_SPR_MPUA6_CONST  V850_CPU_REG_CONST(SPR_MPUA6)
#define V850_SPR_MPUA7_CONST  V850_CPU_REG_CONST(SPR_MPUA7)
#define V850_SPR_MPUA8_CONST  V850_CPU_REG_CONST(SPR_MPUA8)
#define V850_SPR_MPUA9_CONST  V850_CPU_REG_CONST(SPR_MPUA9)
#define V850_SPR_MPUA10_CONST V850_CPU_REG_CONST(SPR_MPUA10)
#define V850_SPR_MPUA11_CONST V850_CPU_REG_CONST(SPR_MPUA11)
#define V850_SPR_MPUA12_CONST V850_CPU_REG_CONST(SPR_MPUA12)
#define V850_SPR_MPUA13_CONST V850_CPU_REG_CONST(SPR_MPUA13)
#define V850_SPR_MPUA14_CONST V850_CPU_REG_CONST(SPR_MPUA14)
#define V850_SPR_MPUA15_CONST V850_CPU_REG_CONST(SPR_MPUA15)

#define V850_SPR_MPAT0_CONST  V850_CPU_REG_CONST(SPR_MPAT0)
#define V850_SPR_MPAT1_CONST  V850_CPU_REG_CONST(SPR_MPAT1)
#define V850_SPR_MPAT2_CONST  V850_CPU_REG_CONST(SPR_MPAT2)
#define V850_SPR_MPAT3_CONST  V850_CPU_REG_CONST(SPR_MPAT3)
#define V850_SPR_MPAT4_CONST  V850_CPU_REG_CONST(SPR_MPAT4)
#define V850_SPR_MPAT5_CONST  V850_CPU_REG_CONST(SPR_MPAT5)
#define V850_SPR_MPAT6_CONST  V850_CPU_REG_CONST(SPR_MPAT6)
#define V850_SPR_MPAT7_CONST  V850_CPU_REG_CONST(SPR_MPAT7)
#define V850_SPR_MPAT8_CONST  V850_CPU_REG_CONST(SPR_MPAT8)
#define V850_SPR_MPAT9_CONST  V850_CPU_REG_CONST(SPR_MPAT9)
#define V850_SPR_MPAT10_CONST V850_CPU_REG_CONST(SPR_MPAT10)
#define V850_SPR_MPAT11_CONST V850_CPU_REG_CONST(SPR_MPAT11)
#define V850_SPR_MPAT12_CONST V850_CPU_REG_CONST(SPR_MPAT12)
#define V850_SPR_MPAT13_CONST V850_CPU_REG_CONST(SPR_MPAT13)
#define V850_SPR_MPAT14_CONST V850_CPU_REG_CONST(SPR_MPAT14)
#define V850_SPR_MPAT15_CONST V850_CPU_REG_CONST(SPR_MPAT15)

#define V850_SPR_ICTAGL_CONST V850_CPU_REG_CONST(SPR_ICTAGL)
#define V850_SPR_ICTAGH_CONST V850_CPU_REG_CONST(SPR_ICTAGH)
#define V850_SPR_ICDATL_CONST V850_CPU_REG_CONST(SPR_ICDATL)
#define V850_SPR_ICDATH_CONST V850_CPU_REG_CONST(SPR_ICDATH)
#define V850_SPR_ICCTRL_CONST V850_CPU_REG_CONST(SPR_ICCTRL)
#define V850_SPR_ICCFG_CONST  V850_CPU_REG_CONST(SPR_ICCFG)
#define V850_SPR_ICERR_CONST  V850_CPU_REG_CONST(SPR_ICERR)

#define V850_SPR_CDBCR_CONST  V850_CPU_REG_CONST(SPR_CDBCR)

#define V850_TMP_CONST(_R) V850_CPU_REG_CONST(tmp[_R])

#define V850_FLG_PSW_SAT_CONST V850_CPU_REG_CONST(FLG_PSW_SAT)

#define V850_FLG_PSW_ID_CONST V850_CPU_REG_CONST(FLG_PSW_ID)

#define V850_FLG_PSW_EP_CONST V850_CPU_REG_CONST(FLG_PSW_EP)

#define V850_FLG_PSW_NP_CONST V850_CPU_REG_CONST(FLG_PSW_NP)

#define V850_FLG_FPF_CONST V850_CPU_REG_CONST(FLG_FPF)

#define V850_FLG_FPF_STICKY_CONST V850_CPU_REG_CONST(FLG_FPF_STICKY)

#define V850_FLG_EFG_FPZ_CONST V850_CPU_REG_CONST(FLG_EFG_FPZ)

#define V850_FLG_EFG_FPS_CONST V850_CPU_REG_CONST(FLG_EFG_FPS)

#define V850_FLG_EFG_FPOV_CONST V850_CPU_REG_CONST(FLG_EFG_FPOV)

#define V850_FLG_FCMP_CONST V850_CPU_REG_CONST(FLG_FCMP)

#define V850_FLG_INTPEND_CONST V850_CPU_REG_CONST(FLG_INTPEND)

#define V850_FLG_NMIPEND_CONST V850_CPU_REG_CONST(FLG_NMIPEND)

#define V850_FLG_TMP_CONST V850_CPU_TEMP_CONST(FLG_TMP)

#define V850_FLG_PSW_CO_CONST V850_CPU_REG_CONST(FLG_PSW_CO)

#define V850_FLG_PSW_ZR_CONST V850_CPU_REG_CONST(FLG_PSW_ZR)

#define V850_FLG_PSW_SI_CONST V850_CPU_REG_CONST(FLG_PSW_SI)

#define V850_FLG_PSW_OV_CONST V850_CPU_REG_CONST(FLG_PSW_OV)

#define V850_FLG_LL_CONST    V850_CPU_REG_CONST(FLG_LL)
#define V850_REG_LL_CONST   V850_CPU_REG_CONST(REG_LL)

#define V850_BCCODE_V 0
#define V850_BCCODE_L 1
#define V850_BCCODE_E 2
#define V850_BCCODE_NH 3
#define V850_BCCODE_N 4
#define V850_BCCODE_R 5
#define V850_BCCODE_LT 6
#define V850_BCCODE_LE 7
#define V850_BCCODE_NV 8
#define V850_BCCODE_NL 9
#define V850_BCCODE_NE 10
#define V850_BCCODE_H 11
#define V850_BCCODE_P 12
#define V850_BCCODE_SA 13
#define V850_BCCODE_GE 14
#define V850_BCCODE_GT 15
static inline const char *getstr_BCCODE(int index) {
    static const char *lookup[] = {
         [0] "V",
         [1] "L",
         [2] "E",
         [3] "NH",
         [4] "N",
         [5] "R",
         [6] "LT",
         [7] "LE",
         [8] "NV",
         [9] "NL",
        [10] "NE",
        [11] "H",
        [12] "P",
        [13] "SA",
        [14] "GE",
        [15] "GT",
    };
    return lookup[index];
}

#define V850_FCCODE_V 0
#define V850_FCCODE_C_L 1
#define V850_FCCODE_Z 2
#define V850_FCCODE_NH 3
#define V850_FCCODE_S_N 4
#define V850_FCCODE_T 5
#define V850_FCCODE_LT 6
#define V850_FCCODE_LE 7
#define V850_FCCODE_NV 8
#define V850_FCCODE_NC_NL 9
#define V850_FCCODE_NZ 10
#define V850_FCCODE_H 11
#define V850_FCCODE_NS_P 12
#define V850_FCCODE_SA 13
#define V850_FCCODE_GE 14
#define V850_FCCODE_GT 15
static inline const char *getstr_FCCODE(int index) {
    static const char *lookup[] = {
         [0] "V",
         [1] "C_L",
         [2] "Z",
         [3] "NH",
         [4] "S_N",
         [5] "T",
         [6] "LT",
         [7] "LE",
         [8] "NV",
         [9] "NC_NL",
        [10] "NZ",
        [11] "H",
        [12] "NS_P",
        [13] "SA",
        [14] "GE",
        [15] "GT",
    };
    return lookup[index];
}

#define V850_FPCMPCODE_F    0
#define V850_FPCMPCODE_UN   1
#define V850_FPCMPCODE_EQ   2
#define V850_FPCMPCODE_UEQ  3
#define V850_FPCMPCODE_OLT  4
#define V850_FPCMPCODE_ULT  5
#define V850_FPCMPCODE_OLE  6
#define V850_FPCMPCODE_ULE  7
#define V850_FPCMPCODE_SF   8
#define V850_FPCMPCODE_NGLE 9
#define V850_FPCMPCODE_SEQ  10
#define V850_FPCMPCODE_NGL  11
#define V850_FPCMPCODE_LT   12
#define V850_FPCMPCODE_NGE  13
#define V850_FPCMPCODE_LE   14
#define V850_FPCMPCODE_NGT  15
static inline const char *getstr_FPCMPCODE(int index) {
    static const char *lookup[] = {
         [0] "F_T",
         [1] "UN_OR",
         [2] "EQ_NEQ",
         [3] "UEQ_OGL",
         [4] "OLT_UGE",
         [5] "ULT_OGE",
         [6] "OLE_UGT",
         [7] "ULE_OGT",
         [8] "SF_ST",
         [9] "NGLE_GLE",
        [10] "SEQ_SNE",
        [11] "NGL_GL",
        [12] "LT_NLT",
        [13] "NGE_GE",
        [14] "LE_NLE",
        [15] "NGT_GT",
    };
    return lookup[index];
}

#define V850_GPR_SP 3
#define V850_GPR_GP 4
#define V850_GPR_EP 30
#define V850_GPR_LP 31
static inline const char *getstr_GPR(int index) {
    static const char *lookup[] = {
        [3] "SP",
        [4] "GP",
        [30] "EP",
        [31] "LP",
    };
    return lookup[index];
}

//
// E0/E1 Register indices
// E2 GRP=0x00 BNK=0x00
//
#define V850_SPR_EIPC  0
#define V850_SPR_EIPSW 1
#define V850_SPR_FEPC  2
#define V850_SPR_FEPSW 3
#define V850_SPR_ECR   4
#define V850_SPR_PSW   5
#define V850_SPR_CTPC  16
#define V850_SPR_CTPSW 17
#define V850_SPR_DBPC  18
#define V850_SPR_DBPSW 19
#define V850_SPR_CTBP  20
#define V850_SPR_DIR   21
#define V850_SPR_BPC   22
#define V850_SPR_ASID  23
#define V850_SPR_BPAV  24
#define V850_SPR_BPAM  25
#define V850_SPR_BPDV  26
#define V850_SPR_BPDM  27

//
// E2 Register indices (Main)
// GRP=0x00 BNK=0x00
//
#define V850_SPR_EIIC   13
#define V850_SPR_FEIC   14
#define V850_SPR_DBIC   15

//
// E2 Bank independant regs
// GRP=0x** BNK=0x**
//
#define V850_SPR_EIWR  28
#define V850_SPR_FEWR  29
#define V850_SPR_DBWR  30
#define V850_SPR_BSEL  31

//
// E2 Register indices (EHSW0)
// GRP=0x00 BNK=0x10
//
#define V850_SPR_SW_CTL  0
#define V850_SPR_SW_CFG  1
#define V850_SPR_SW_BASE 3

//
// E2 Register indices (EHSW1)
// GRP=0x00 BNK=0x11
//
#define V850_SPR_EH_CFG   1
#define V850_SPR_EH_RESET 2
#define V850_SPR_EH_BASE  3

//
// E2 Register indices (FPU)
// GRP=0x20 BNK=0x00
//
#define V850_SPR_FPSR   6
#define V850_SPR_FPEPC  7
#define V850_SPR_FPST   8
#define V850_SPR_FPCC   9
#define V850_SPR_FPCFG  10
#define V850_SPR_FPEC   11

//
// E2 Register indices (MPV)
// GRP=0x10 BNK=0x00
//
#define V850_SPR_VIP    0
#define V850_SPR_VMECR  4
#define V850_SPR_VMTID  5
#define V850_SPR_VMADR  6
#define V850_SPR_VPECR  8
#define V850_SPR_VPTID  9
#define V850_SPR_VPADR  10
#define V850_SPR_VDECR0 12
#define V850_SPR_VDTID0 13
#define V850_SPR_VDECR1 14
#define V850_SPR_VDTID1 15

//
// E2 Register indices (MPU)
// GRP=0x10 BNK=0x01
//
#define V850_SPR_MPM    0
#define V850_SPR_MPC    1
#define V850_SPR_TID    2
#define V850_SPR_PPC    3
#define V850_SPR_DCC0   4
#define V850_SPR_DCV0   5
#define V850_SPR_DCC1   6
#define V850_SPR_DCV1   7
#define V850_SPR_IPA0L  8
#define V850_SPR_IPA0U  9
#define V850_SPR_IPA1L  10
#define V850_SPR_IPA1U  11
#define V850_SPR_IPA2L  12
#define V850_SPR_IPA2U  13
#define V850_SPR_IPA3L  14
#define V850_SPR_IPA3U  15
#define V850_SPR_DPA0L  16
#define V850_SPR_DPA0U  17
#define V850_SPR_DPA1L  18
#define V850_SPR_DPA1U  19
#define V850_SPR_DPA2L  20
#define V850_SPR_DPA2U  21
#define V850_SPR_DPA3L  22
#define V850_SPR_DPA3U  23
#define V850_SPR_DPA4L  24
#define V850_SPR_DPA4U  25
#define V850_SPR_DPA5L  26
#define V850_SPR_DPA5U  27

//
// RH850
//
//      SELID 0
#define V850_SPR_SEL_FPEC   11
//      SELID 1
#define V850_SPR_SEL_MCFG0  0
#define V850_SPR_SEL_RBASE  2
#define V850_SPR_SEL_EBASE  3
#define V850_SPR_SEL_INTBP  4
#define V850_SPR_SEL_MCTL   5
#define V850_SPR_SEL_PID    6
#define V850_SPR_SEL_FPIPR  7
#define V850_SPR_SEL_SCCFG  11
#define V850_SPR_SEL_SCBP   12
//      SELID 2
#define V850_SPR_SEL_HTCFG0 0
#define V850_SPR_SEL_MEA    6
#define V850_SPR_SEL_ASID   7
#define V850_SPR_SEL_MEI    8
#define V850_SPR_SEL_ISPR   10
#define V850_SPR_SEL_PMR    11
#define V850_SPR_SEL_ICSR   12
#define V850_SPR_SEL_INTCFG 13
//      SELID 4
#define V850_SPR_SEL_ICTAGL 16
#define V850_SPR_SEL_ICTAGH 17
#define V850_SPR_SEL_ICDATL 18
#define V850_SPR_SEL_ICDATH 19
#define V850_SPR_SEL_ICCTRL 24
#define V850_SPR_SEL_ICCFG  26
#define V850_SPR_SEL_ICERR  28
//      SELID 5
#define V850_SPR_SEL_MPM    0
#define V850_SPR_SEL_MPRC   1
#define V850_SPR_SEL_MPBRGN 4
#define V850_SPR_SEL_MPTRGN 5
#define V850_SPR_SEL_MCA    8
#define V850_SPR_SEL_MCS    9
#define V850_SPR_SEL_MCC    10
#define V850_SPR_SEL_MCR    11
//      SELID 6
#define V850_SPR_SEL_MPLA0  0
#define V850_SPR_SEL_MPUA0  1
#define V850_SPR_SEL_MPAT0  2
#define V850_SPR_SEL_MPLA1  4
#define V850_SPR_SEL_MPUA1  5
#define V850_SPR_SEL_MPAT1  6
#define V850_SPR_SEL_MPLA2  8
#define V850_SPR_SEL_MPUA2  9
#define V850_SPR_SEL_MPAT2  10
#define V850_SPR_SEL_MPLA3  12
#define V850_SPR_SEL_MPUA3  13
#define V850_SPR_SEL_MPAT3  14
#define V850_SPR_SEL_MPLA4  16
#define V850_SPR_SEL_MPUA4  17
#define V850_SPR_SEL_MPAT4  18
#define V850_SPR_SEL_MPLA5  20
#define V850_SPR_SEL_MPUA5  21
#define V850_SPR_SEL_MPAT5  22
#define V850_SPR_SEL_MPLA6  24
#define V850_SPR_SEL_MPUA6  25
#define V850_SPR_SEL_MPAT6  26
#define V850_SPR_SEL_MPLA7  28
#define V850_SPR_SEL_MPUA7  29
#define V850_SPR_SEL_MPAT7  30
//      SELID 7
#define V850_SPR_SEL_MPLA8  0
#define V850_SPR_SEL_MPUA8  1
#define V850_SPR_SEL_MPAT8  2
#define V850_SPR_SEL_MPLA9  4
#define V850_SPR_SEL_MPUA9  5
#define V850_SPR_SEL_MPAT9  6
#define V850_SPR_SEL_MPLA10 8
#define V850_SPR_SEL_MPUA10 9
#define V850_SPR_SEL_MPAT10 10
#define V850_SPR_SEL_MPLA11 12
#define V850_SPR_SEL_MPUA11 13
#define V850_SPR_SEL_MPAT11 14
#define V850_SPR_SEL_MPLA12 16
#define V850_SPR_SEL_MPUA12 17
#define V850_SPR_SEL_MPAT12 18
#define V850_SPR_SEL_MPLA13 20
#define V850_SPR_SEL_MPUA13 21
#define V850_SPR_SEL_MPAT13 22
#define V850_SPR_SEL_MPLA14 24
#define V850_SPR_SEL_MPUA14 25
#define V850_SPR_SEL_MPAT14 26
#define V850_SPR_SEL_MPLA15 28
#define V850_SPR_SEL_MPUA15 29
#define V850_SPR_SEL_MPAT15 30
//      SELID 13
#define V850_SPR_SEL_CDBCR  24


static inline const char *getstr_SPR(int index) {
    static const char *lookup[] = {
        [0]  "EIPC",
        [1]  "EIPSW",
        [2]  "FEPC",
        [3]  "FEPSW",
        [4]  "ECR",
        [5]  "PSW",
        [16] "CTPC",
        [17] "CTPSW",
        [18] "DBPC",
        [19] "DBPSW",
        [20] "CTBP",
        [21] "DIR",
        [22] "BPC",
        [23] "ASID",
        [24] "BPAV",
        [25] "BPAM",
        [26] "BPDV",
        [27] "BPDM",
    };
    return lookup[index];
}

static inline Uns32 getSPRMask(v850P v850, IntPS maskOffset) {
    return *(Uns32 *)(((UnsPS)v850) + maskOffset);
}

#define CPU_PREFIX "V850"

typedef Uns32 v850Addr;

#endif // V850_BPDM_H
