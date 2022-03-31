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

#pragma once

// base model header files
#include "riscvCSR.h"
#include "riscvModelCallbacks.h"
#include "riscvModelCallbackTypes.h"


////////////////////////////////////////////////////////////////////////////////
// CSR ENUMERATION
////////////////////////////////////////////////////////////////////////////////

//
// Construct enumeration member names from the given base and indices 0..3
//
#define XCSR_ID_0_3(_R)  \
    XCSR_ID(_R##0),      \
    XCSR_ID(_R##1),      \
    XCSR_ID(_R##2),      \
    XCSR_ID(_R##3)

//
// Construct enumeration member names from the given base and indices 3..6
//
#define XCSR_ID_3_6(_R)  \
    XCSR_ID(_R##3),      \
    XCSR_ID(_R##4),      \
    XCSR_ID(_R##5),      \
    XCSR_ID(_R##6)

//
// Construct enumeration member names from the given base and indices 0..9
//
#define XCSR_ID_0_9(_R)  \
    XCSR_ID(_R##0),      \
    XCSR_ID(_R##1),      \
    XCSR_ID(_R##2),      \
    XCSR_ID(_R##3),      \
    XCSR_ID(_R##4),      \
    XCSR_ID(_R##5),      \
    XCSR_ID(_R##6),      \
    XCSR_ID(_R##7),      \
    XCSR_ID(_R##8),      \
    XCSR_ID(_R##9)

//
// Construct enumeration member names from the given base and indices 0..15
//
#define XCSR_ID_0_15(_R) \
    XCSR_ID_0_9(_R),     \
    XCSR_ID(_R##10),     \
    XCSR_ID(_R##11),     \
    XCSR_ID(_R##12),     \
    XCSR_ID(_R##13),     \
    XCSR_ID(_R##14),     \
    XCSR_ID(_R##15)

//
// Identifiers for each implemented CSR
//
typedef enum extCSRIdE {

    // Standard U-mode CSRs with Andes-specific behavior
    XCSR_ID      (cycle),           // 0xC00
    XCSR_ID      (time),            // 0xC01
    XCSR_ID      (instret),         // 0xC02
    XCSR_ID_3_6  (hpmcounter),      // 0xC03-0xC06
    XCSR_ID      (cycleh),          // 0xC80
    XCSR_ID      (timeh),           // 0xC80
    XCSR_ID      (instreth),        // 0xC80
    XCSR_ID_3_6  (hpmcounterh),     // 0xC83-0xC86

    // Standard M-mode CSRs with Andes-specific behavior
    XCSR_ID      (mcycle),          // 0xB00
    XCSR_ID      (minstret),        // 0xB02
    XCSR_ID_3_6  (mhpmcounter),     // 0xB03-0xB06
    XCSR_ID      (mcycleh),         // 0xB80
    XCSR_ID      (minstreth),       // 0xB82
    XCSR_ID_3_6  (mhpmcounterh),    // 0xB83-0xB86
    XCSR_ID_3_6  (mhpmevent),       // 0x323-0x326

    // AndeStar V5m configuration control and status registers
    XCSR_ID      (micm_cfg),        // 0xFC0
    XCSR_ID      (mdcm_cfg),        // 0xFC1
    XCSR_ID      (mmsc_cfg),        // 0xFC2
    XCSR_ID      (mmsc_cfg2),       // 0xFC3
    XCSR_ID      (mvec_cfg),        // 0xFC7
    XCSR_ID      (ml2c_ctl_base),   // 0xFCF

    // AndeStar V5m memory and miscellaneous CSRs
    XCSR_ID      (milmb),           // 0x7C0
    XCSR_ID      (mdlmb),           // 0x7C1
//  XCSR_ID      (mecc_code),       // 0x7C2     TODO: not yet implemented
    XCSR_ID      (mnvec),           // 0x7C3
    XCSR_ID      (mpft_ctl),        // 0x7C5
    XCSR_ID      (mcache_ctl),      // 0x7CA
    XCSR_ID      (mcctlbeginaddr),  // 0x7CB
    XCSR_ID      (mcctlcommand),    // 0x7CC
    XCSR_ID      (mcctldata),       // 0x7CD
    XCSR_ID      (mmisc_ctl),       // 0x7D0

    // AndeStar V5m trap related CSRs
    XCSR_ID      (mxstatus),        // 0x7C4
    XCSR_ID      (mdcause),         // 0x7C9

    // AndeStar V5m hardware stack protection and recording CSRs
    XCSR_ID      (mhsp_ctl),        // 0x7C6
    XCSR_ID      (msp_bound),       // 0x7C7
    XCSR_ID      (msp_base),        // 0x7C8

    // AndeStar V5m machine-mode counter-related CSRs
    XCSR_ID      (mcounterwen),     // 0x7CE
    XCSR_ID      (mcounterinten),   // 0x7CF
    XCSR_ID      (mcountermask_m),  // 0x7D1
    XCSR_ID      (mcountermask_s),  // 0x7D2
    XCSR_ID      (mcountermask_u),  // 0x7D3
    XCSR_ID      (mcounterovf),     // 0x7D4

    // AndeStar V5m supervisor-mode counter-related CSRs
    XCSR_ID      (scounterinten),   // 0x9CF
    XCSR_ID      (scountermask_m),  // 0x9D1
    XCSR_ID      (scountermask_s),  // 0x9D2
    XCSR_ID      (scountermask_u),  // 0x9D3
    XCSR_ID      (scounterovf),     // 0x9D4
    XCSR_ID_3_6  (shpmevent),       // 0x9E3-0x9E6

    // AndeStar V5m debug mode control and status registers
//  XCSR_ID      (dexc2dbg),        // 0x7E0     TODO: not yet implemented
//  XCSR_ID      (ddcause),         // 0x7E1     TODO: not yet implemented

    // AndeStar V5m user mode control and status registers
    XCSR_ID      (uitb),            // 0x800
    XCSR_ID      (ucctlbeginaddr),  // 0x80B
    XCSR_ID      (ucctlcommand),    // 0x80C

    // AndeStar V5m PMA related CSRs
    XCSR_ID_0_3  (pmacfg),          // 0xBC0-0xBC3
    XCSR_ID_0_15 (pmaaddr),         // 0xBD0-0xBDF

    // keep last (used to define size of the enumeration)
    XCSR_ID      (LAST)

} extCSRId;


// -----------------------------------------------------------------------------
// micm_cfg     (id 0xFC0)
// mdcm_cfg     (id 0xFC1)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 SET       : 3;
    Uns32 WAY       : 3;
    Uns32 SZ        : 3;
    Uns32 LCK       : 1;
    Uns32 C_ECC     : 2;
    Uns32 LMB       : 3;
    Uns32 LMSZ      : 5;
    Uns32 ULM_2BANK : 1;
    Uns32 LM_ECC    : 2;
    Uns32 _u1       : 9;
} CSR_REG_TYPE_32(mcm_cfg);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(mcm_cfg);

// define alias types
typedef CSR_REG_TYPE(mcm_cfg) CSR_REG_TYPE(micm_cfg);
typedef CSR_REG_TYPE(mcm_cfg) CSR_REG_TYPE(mdcm_cfg);


// -----------------------------------------------------------------------------
// mmsc_cfg     (id 0xFC2)
// -----------------------------------------------------------------------------

// 64-bit view
typedef struct {
    Uns32 ECC        :  1;
    Uns32 TLB_ECC    :  2;
    Uns32 ECD        :  1;
    Uns32 PFT        :  1;
    Uns32 HSP        :  1;
    Uns32 ACE        :  1;
    Uns32 PMPE       :  5;
    Uns32 VPLIC      :  1;
    Uns32 EV5MPE     :  1;
    Uns32 LMSLVP     :  1;
    Uns32 PMNDS      :  1;
    Uns32 CCTLCSR    :  1;  // (bit 16)
    Uns32 EFHW       :  1;
    Uns32 _u1        :  2;  // (bits 19:18)
    Uns32 EXCSVL     :  2;  // TODO: not implemented
    Uns32 NOPMC      :  1;  // TODO: not implemented
    Uns32 SPE_AFT    :  1;  // TODO: not implemented
    Uns32 ESLEEP     :  1;  // TODO: not implemented
    Uns32 PPI        :  1;  // TODO: not implemented
    Uns32 FIO        :  1;  // TODO: not implemented
    Uns32 CLIC       :  1;  // TODO: not implemented
    Uns32 ECLIC      :  1;  // TODO: not implemented
    Uns32 EDSP       :  1;
    Uns32 DPMA       :  1;
    Uns32 MSC_EXT    :  1;
    Uns32 BF16CVT    :  1;  // (bit 32)
    Uns32 ZFH        :  1;
    Uns32 VL4        :  1;
    Uns32 CRASHSSAVE :  1;  // TODO: not implemented
    Uns32 VECCFG     :  1;
    Uns32 FINV       :  1;  // TODO: not implemented
    Uns32 PP16       :  1;  // TODO: not implemented
    Uns32 PP32       :  1;  // TODO: not implemented
    Uns32 VSIH       :  1;  // TODO: not implemented
    Uns32 ECDV       :  2;  // TODO: not implemented
    Uns32 VDOT       :  1;  // TODO: not implemented
    Uns32 VPFH       :  1;
    Uns32 L2CMP_CFG  :  1;
    Uns32 L2C        :  1;
    Uns32 IOCP       :  1;  // TODO: not implemented
    Uns32 CORE_PCLUS :  4;  // (bits 51:48)
    Uns32 _u2        : 12;  // (bits 63:52)
} CSR_REG_TYPE_64(mmsc_cfg);

// define 64 bit type
CSR_REG_STRUCT_DECL_64(mmsc_cfg);

// -----------------------------------------------------------------------------
// mvec_cfg     (id 0xFC7)
// -----------------------------------------------------------------------------

// 64-bit view
typedef struct {
    Uns32 MINOR :  4;
    Uns32 MAJOR :  4;
    Uns32 DW    :  3;
    Uns32 MW    :  3;
    Uns32 MISEW :  2;
    Uns32 MFSEW :  2;
    Uns32 _u2   : 14;
} CSR_REG_TYPE_32(mvec_cfg);

// define 64 bit type
CSR_REG_STRUCT_DECL_32(mvec_cfg);

// -----------------------------------------------------------------------------
// ml2c_ctl_base  (id 0xFCF)
// -----------------------------------------------------------------------------

// 64-bit view
typedef struct {
    Uns64 L2C_CTL_BASE : 64;
} CSR_REG_TYPE_64(ml2c_ctl_base);

// define 32/64 bit type
CSR_REG_STRUCT_DECL_64(ml2c_ctl_base);

// -----------------------------------------------------------------------------
// milmb        (id 0x7C0)
// mdlmb        (id 0x7C1)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 EN    :  1;
    Uns32 ECCEN :  2;
    Uns32 RWECC :  1;
    Uns32 _u1   :  6;
    Uns32 BPA   : 22;
} CSR_REG_TYPE_32(mlmb);

// 64-bit view
typedef struct {
    Uns64 EN    :  1;
    Uns64 ECCEN :  2;
    Uns64 RWECC :  1;
    Uns64 _u1   :  6;
    Uns64 BPA   : 54;
} CSR_REG_TYPE_64(mlmb);

// define 32/64 bit type
CSR_REG_STRUCT_DECL_32_64(mlmb);

// define alias types
typedef CSR_REG_TYPE(mlmb) CSR_REG_TYPE(milmb);
typedef CSR_REG_TYPE(mlmb) CSR_REG_TYPE(mdlmb);

// -----------------------------------------------------------------------------
// mnvec        (id 0x7C3)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 _u1  :  2;
    Uns32 ADDR : 30;
} CSR_REG_TYPE_32(mnvec);

// 64-bit view
typedef struct {
    Uns64 _u1  :  2;
    Uns64 ADDR : 62;
} CSR_REG_TYPE_64(mnvec);

// define 32/64 bit type
CSR_REG_STRUCT_DECL_32_64(mnvec);

// define write masks
#define WM32_mnvec -4
#define WM64_mnvec -4

// -----------------------------------------------------------------------------
// mpft_ctl     (id 0x7C5)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 _u1      :  4;
    Uns32 T_LEVEL  :  4;
    Uns32 FAST_INT :  1;
    Uns32 _u2      : 23;
} CSR_REG_TYPE_32(mpft_ctl);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(mpft_ctl);

// define write masks
#define WM32_mpft_ctl 0x1f0
#define WM64_mpft_ctl 0x1f0

// -----------------------------------------------------------------------------
// mcache_ctl   (id 0x7CA)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 IC_EN     :  1;
    Uns32 DC_EN     :  1;
    Uns32 IC_ECCEN  :  2;
    Uns32 DC_ECCEN  :  2;
    Uns32 IC_RWECC  :  1;
    Uns32 DC_RWECC  :  1;
    Uns32 CCTL_SUEN :  1;
    Uns32 _u1       : 23;
} CSR_REG_TYPE_32(mcache_ctl);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(mcache_ctl);

// -----------------------------------------------------------------------------
// mcctlbeginaddr   (id 0x7CB)
// mcctlcommand     (id 0x7CC)
// mcctldata        (id 0x7CD)
// -----------------------------------------------------------------------------

typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(mcctlbeginaddr);
typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(mcctlcommand);
typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(mcctldata);

// define write masks
#define WM32_mcctlbeginaddr -1
#define WM64_mcctlbeginaddr -1
#define WM32_mcctlcommand   0x1f
#define WM64_mcctlcommand   0x1f
#define WM32_mcctldata      -1
#define WM64_mcctldata      -1

// -----------------------------------------------------------------------------
// mmisc_ctl    (id 0x7D0)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 ACE      :  1;
    Uns32 VEC_PLIC :  1;
    Uns32 RVCOMPM  :  1;
    Uns32 BRPE     :  1;
    Uns32 ACES     :  2;
    Uns32 MSA_UNA  :  1;
    Uns32 _u1      :  1;
    Uns32 NBLD_EN  :  1;
    Uns32 _u2      : 23;
} CSR_REG_TYPE_32(mmisc_ctl);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(mmisc_ctl);

// define write masks
#define WM32_mmisc_ctl 0x46
#define WM64_mmisc_ctl 0x46

// -----------------------------------------------------------------------------
// mxstatus     (id 0x7C4)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 PFT_EN  :  1;
    Uns32 PPFT_EN :  1;
    Uns32 IME     :  1;
    Uns32 PIME    :  1;
    Uns32 DME     :  1;
    Uns32 PDME    :  1;
    Uns32 _u0     : 26;
} CSR_REG_TYPE_32(mxstatus);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(mxstatus);

// -----------------------------------------------------------------------------
// mdcause      (id 0x7C9)
// -----------------------------------------------------------------------------

typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(mdcause);

// define write masks
#define WM32_mdcause -1
#define WM64_mdcause -1

// -----------------------------------------------------------------------------
// mhsp_ctl     (id 0x7C6)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 OVF_EN :  1;
    Uns32 UDF_EN :  1;
    Uns32 SCHM   :  1;
    Uns32 U      :  1;
    Uns32 S      :  1;
    Uns32 M      :  1;
    Uns32 _u1    : 26;
} CSR_REG_TYPE_32(mhsp_ctl);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(mhsp_ctl);

// define write masks
#define WM32_mhsp_ctl 0x3f
#define WM64_mhsp_ctl 0x3f

// -----------------------------------------------------------------------------
// msp_bound    (id 0x7C7)
// -----------------------------------------------------------------------------

typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(msp_bound);

// define write masks
#define WM32_msp_bound -1
#define WM64_msp_bound -1

// -----------------------------------------------------------------------------
// msp_base     (id 0x7C8)
// -----------------------------------------------------------------------------

typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(msp_base);

// define write masks
#define WM32_msp_base -1
#define WM64_msp_base -1

// -----------------------------------------------------------------------------
// mcounterwen      (id 0x7CE)
// mcounterinten    (id 0x7CF)
// mcountermask_m   (id 0x7D1)
// mcountermask_s   (id 0x7D2)
// mcountermask_u   (id 0x7D3)
// mcounterovf      (id 0x7D4)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 CY  : 1;
    Uns32 TM  : 1;
    Uns32 IR  : 1;
    Uns32 HPM : 29;
} CSR_REG_TYPE_32(countermask);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(countermask);

// define alias types
typedef CSR_REG_TYPE(countermask) CSR_REG_TYPE(mcounterwen);
typedef CSR_REG_TYPE(countermask) CSR_REG_TYPE(mcounterinten);
typedef CSR_REG_TYPE(countermask) CSR_REG_TYPE(mcountermask_m);
typedef CSR_REG_TYPE(countermask) CSR_REG_TYPE(mcountermask_s);
typedef CSR_REG_TYPE(countermask) CSR_REG_TYPE(mcountermask_u);
typedef CSR_REG_TYPE(countermask) CSR_REG_TYPE(mcounterovf);

// -----------------------------------------------------------------------------
// mhpmevent3-6     (id 0x323-0x326)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 TYPE : 4;
    Uns32 SEL  : 5;
    Uns32 _u1  : 23;
} CSR_REG_TYPE_32(andes_event);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(andes_event);

// -----------------------------------------------------------------------------
// uitb         (id 0x800)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 HW   :  1;
    Uns32 _u1  :  1;
    Uns32 ADDR : 30;
} CSR_REG_TYPE_32(uitb);

// 64-bit view
typedef struct {
    Uns64 HW   :  1;
    Uns64 _u1  :  1;
    Uns64 ADDR : 62;
} CSR_REG_TYPE_64(uitb);

// define 32/64 bit type
CSR_REG_STRUCT_DECL_64(uitb);

// define write masks
#define WM32_uitb -4
#define WM64_uitb -4

// -----------------------------------------------------------------------------
// ucctlbeginaddr   (id 0x80B)
// ucctlcommand     (id 0x80C)
// -----------------------------------------------------------------------------

typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(ucctlbeginaddr);
typedef CSR_REG_TYPE(genericXLEN) CSR_REG_TYPE(ucctlcommand);

// define write masks
#define WM32_ucctlbeginaddr -1
#define WM64_ucctlbeginaddr -1
#define WM32_ucctlcommand   0x1f
#define WM64_ucctlcommand   0x1f

// -----------------------------------------------------------------------------
// pmacfg           (id 0xBC0-0xBC3)
// -----------------------------------------------------------------------------

// define write masks
#define WM64_pmacfg 0x7f7f7f7f7f7f7f7fULL


////////////////////////////////////////////////////////////////////////////////
// INITIALIZATION
////////////////////////////////////////////////////////////////////////////////

//
// Initialize CSR state
//
void andesCSRInit(vmiosObjectP object);

//
// Free CSR state
//
void andesCSRFree(vmiosObjectP object);


////////////////////////////////////////////////////////////////////////////////
// HARDWARE STACK PROTECTION SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Record old value of SP if hardware stack protection check if required
//
void andesRecordSP(riscvP riscv, vmiosObjectP object);

//
// Add hardware stack protection check if required
//
void andesCheckHSP(riscvP riscv, vmiosObjectP object);


////////////////////////////////////////////////////////////////////////////////
// PHYSICAL MEMORY ATTRIBUTE AND DLM/ILM SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Indicate whether PMA protection is implemented
//
RISCV_PMA_ENABLE_FN(andesPMAEnable);

//
// Implement PMA check for the given address range
//
RISCV_PMA_CHECK_FN(andesPMACheck);

//
// Install ILM/DLM domains if required
//
RISCV_PHYS_MEM_FN(andesInstallPhysicalMem);


////////////////////////////////////////////////////////////////////////////////
// SYSTEM REGISTER CONTAINER
////////////////////////////////////////////////////////////////////////////////

//
// This type defines the CSRs implemented as true registers in the processor
// structure
//
typedef struct andesCSRsS {

    // USER MODE CSRS
    CSR_REG_DECL(uitb);             // 0x800
    CSR_REG_DECL(ucctlbeginaddr);   // 0x80B
    CSR_REG_DECL(ucctlcommand);     // 0x80C

    // MACHINE MODE CSRS
    CSR_REG_DECL(milmb);            // 0x7C0
    CSR_REG_DECL(mdlmb);            // 0x7C1
    CSR_REG_DECL(mnvec);            // 0x7C3
    CSR_REG_DECL(mxstatus);         // 0x7C4
    CSR_REG_DECL(mpft_ctl);         // 0x7C5
    CSR_REG_DECL(mhsp_ctl);         // 0x7C6
    CSR_REG_DECL(msp_bound);        // 0x7C7
    CSR_REG_DECL(msp_base);         // 0x7C8
    CSR_REG_DECL(mdcause);          // 0x7C9
    CSR_REG_DECL(mcache_ctl);       // 0x7CA
    CSR_REG_DECL(mcctlbeginaddr);   // 0x7CB
    CSR_REG_DECL(mcctlcommand);     // 0x7CC
    CSR_REG_DECL(mcctldata);        // 0x7CD
    CSR_REG_DECL(mcounterwen);      // 0x7CE
    CSR_REG_DECL(mcounterinten);    // 0x7CF
    CSR_REG_DECL(mcountermask_m);   // 0x7D1
    CSR_REG_DECL(mcountermask_s);   // 0x7D2
    CSR_REG_DECL(mcountermask_u);   // 0x7D3
    CSR_REG_DECL(mcounterovf);      // 0x7D4
    CSR_REG_DECL(mmisc_ctl);        // 0x7D0
    CSR_REG_DECL(micm_cfg);         // 0xFC0
    CSR_REG_DECL(mdcm_cfg);         // 0xFC1
    CSR_REG_DECL(mmsc_cfg);         // 0xFC2
    CSR_REG_DECL(mvec_cfg);         // 0xFC7
    CSR_REG_DECL(ml2c_ctl_base);    // 0xFCF

} andesCSRs;


////////////////////////////////////////////////////////////////////////////////
// SYSTEM REGISTER WRITE MASKS
////////////////////////////////////////////////////////////////////////////////

//
// This type defines write masks for CSRs
//
typedef struct andesCSRMasksS {

    // USER MODE CSRS
    CSR_REG_DECL(uitb);             // 0x800

    // MACHINE MODE CSRS
    CSR_REG_DECL(milmb);            // 0x7C0
    CSR_REG_DECL(mdlmb);            // 0x7C1
    CSR_REG_DECL(mxstatus);         // 0x7C4
    CSR_REG_DECL(mcache_ctl);       // 0x7CA
    CSR_REG_DECL(mcounterwen);      // 0x7CE
    CSR_REG_DECL(mcounterinten);    // 0x7CF
    CSR_REG_DECL(mcountermask_m);   // 0x7D1
    CSR_REG_DECL(mcountermask_s);   // 0x7D2
    CSR_REG_DECL(mcountermask_u);   // 0x7D3
    CSR_REG_DECL(mcounterovf);      // 0x7D4

} andesCSRMasks;

