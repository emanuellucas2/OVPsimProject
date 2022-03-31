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

#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"
#include "v850Structure.h"
#include "v850Exceptions.h"
#include "v850Instructions.h"
#include "v850Morph.h"
#include "v850MorphFP.h"
#include "v850MPU.h"
#include "v850SPR.h"
#include "v850Utils.h"

//
// Forward reference
//
static V850_REG_WRITE_FN(wModelPSW);

typedef enum {
    SPR_STORE = 0,
    SPR_LOAD  = 1
} sprLoadStoreE;

#define SYS_STORE 0

//
// Undefined registers are handled as if having SV permission
//
static void vmic_PIW(v850P v850, Uns32 regID, Uns32 selID, sprLoadStoreE ldst) {
    const char *instr = ldst ? "LDSR" : "STSR";
    if (v850->configInfo.arch == RH850G3M) {
        vmiMessage("W", instr, "Undefined Register regID=%d, selID=%d", regID, selID);
    } else {
        vmiMessage("W", instr, "Undefined Register regID=%d, GRP=%02X, BNK=%02X",
            regID, v850->SPR_BSEL.GRP, v850->SPR_BSEL.BNK);
    }
}
static void vmic_PIE(v850P v850, Uns32 regID, Uns32 selID, Uns32 ldst, Uns32 gpr) {
    const char *instr = ldst ? "LDSR" : "STSR";
    vmiMessage("W", instr, "Privileged Instruction Exception %s PSW.UM=%d regID=%d, selID=%d gpr=%d",
        instr, v850->SPR_PSW.UM, regID, selID, gpr);
    v850ProcessPIE(v850);
    if (ldst == SPR_STORE) {
        if (gpr != 0) v850->gpr[gpr] = 0xdeadbeef;
    }
}

static v850SystemRegisterT sysRegs[] = {
    //
    // VE0/VE1 Register indices
    // VE2 GRP=0x00 BNK=0x00
    //
    //      ARCH            REG    NAME   GRP   BNK   PRIV      ENDB R     W
    BANKREG(RSYS_VE0_RHG3M, EIPC,  eipc,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_RHG3M, EIPSW, eipsw, 0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_RHG3M, FEPC,  fepc,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_RHG3M, FEPSW, fepsw, 0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  ECR,   ecr,   0x00, 0x00, PRIV_SV,  0,   rECR, wECR),  // Not present in REG_RH850G3M
    BANKREG(RSYS_VE0_RHG3M, PSW,   psw,   0x00, 0x00, PRIV_PSW, 1,   rPSW, wModelPSW),
    BANKREG(RSYS_VE0_RHG3M, CTPC,  ctpc,  0x00, 0x00, PRIV_UM,  0,   0,    0),
    BANKREG(RSYS_VE0_RHG3M, CTPSW, ctpsw, 0x00, 0x00, PRIV_UM,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  DBPC,  dbpc,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  DBPSW, dbpsw, 0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_RHG3M, CTBP,  ctbp,  0x00, 0x00, PRIV_UM,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  DIR,   dir,   0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  BPC,   bpc,   0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  ASID,  asid,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  BPAV,  bpav,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  BPAM,  bpam,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  BPDV,  bpdv,  0x00, 0x00, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  BPDM,  bpdm,  0x00, 0x00, PRIV_SV,  0,   0,    0),

    //
    // VE2 Bank independant regs
    //
    //      ARCH             REG    NAME   GRP   BNK   PRIV     ENDB R  W
    BANKREG(RSYS_VE2R_RHG3M, EIWR,  eiwr,  0x00, 0x00, PRIV_SV, 0,   0, 0),
    BANKREG(RSYS_VE2R_RHG3M, FEWR,  fewr,  0x00, 0x00, PRIV_SV, 0,   0, 0),
    BANKREG(RSYS_VE0_VE2R,   DBWR,  dbwr,  0x00, 0x00, PRIV_SV, 0,   0, 0),
    BANKREG(RSYS_VE2R_RHG3M, BSEL,  bsel,  0x00, 0x00, PRIV_SV, 1,   0, wBSEL),

    //
    // VE2 Register indices (Main)
    // GRP=0x00 BNK=0x00
    //
    //      ARCH             REG    NAME   GRP   BNK   PRIV     ENDB R     W
    BANKREG(RSYS_VE2R_RHG3M, EIIC,  eiic,  0x00, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE2R_RHG3M, FEIC,  feic,  0x00, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DBIC,  dbic,  0x00, 0x00, PRIV_SV, 0,   0,    0),

    //
    // VE0/VE1 Register indices (ESWH0)
    // VE2 GRP=0x00 BNK=0x10
    //
    //      ARCH            REG      NAME     GRP   BNK   PRIV      ENDB R     W
    BANKREG(RSYS_VE0_VE2R,  SW_CTL,  sw_ctl,  0x00, 0x10, PRIV_SV,  0,   0,    wSW_CTL),
    BANKREG(RSYS_VE0_VE2R,  SW_CFG,  sw_cfg,  0x00, 0x10, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  SW_BASE, sw_base, 0x00, 0x10, PRIV_SV,  0,   0,    0),

    //
    // VE0/VE1 Register indices (ESWH1)
    // VE2 GRP=0x00 BNK=0x11
    //
    //      ARCH            REG       NAME      GRP   BNK   PRIV      ENDB R     W
    BANKREG(RSYS_VE0_VE2R,  EH_CFG,   eh_cfg,   0x00, 0x11, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  EH_RESET, eh_reset, 0x00, 0x11, PRIV_SV,  0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,  EH_BASE,  eh_base,  0x00, 0x11, PRIV_SV,  0,   0,    0),

    //
    // VE2 Register indices (FPU)
    // GRP=0x20 BNK=0x00
    //
    //      ARCH             REG    NAME   GRP   BNK   PRIV         ENDB R      W
    BANKREG(RSYS_VE2R_RHG3M, FPSR,  fpsr,  0x20, 0x00, PRIV_CU0_SV, 0,   rFPSR, wFPSR),
    BANKREG(RSYS_VE2R_RHG3M, FPEPC, fpepc, 0x20, 0x00, PRIV_CU0_SV, 0,   0,     0),
    BANKREG(RSYS_VE2R_RHG3M, FPST,  fpst,  0x20, 0x00, PRIV_CU0,    0,   rFPST, wFPST),
    BANKREG(RSYS_VE2R_RHG3M, FPCC,  fpcc,  0x20, 0x00, PRIV_CU0,    0,   rFPCC, wFPCC),
    BANKREG(RSYS_VE2R_RHG3M, FPCFG, fpcfg, 0x20, 0x00, PRIV_CU0,    0,   rFPCFG,wFPCFG),

    //
    // VE2 Register indices (MPV)
    // GRP=0x10 BNK=0x00
    //
    //      ARCH             REG     NAME    GRP   BNK   PRIV     ENDB R     W
    BANKREG(RSYS_VE0_VE2R,   VIP,    vip,    0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VMECR,  vmecr,  0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VMTID,  vmtid,  0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VMADR,  vmadr,  0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VPECR,  vpecr,  0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VPTID,  vptid,  0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VPADR,  vpadr,  0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VDECR0, vdecr0, 0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VDTID0, vdtid0, 0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VDECR1, vdecr1, 0x10, 0x00, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   VDTID1, vdtid1, 0x10, 0x00, PRIV_SV, 0,   0,    0),

    //
    // VE2 Register indices (MPU)
    // GRP=0x10 BNK=0x01
    //
    //      ARCH             REG    NAME    GRP   BNK   PRIV     ENDB R     W
    BANKREG(RSYS_VE0_VE2R,   MPM,   mpm,    0x10, 0x01, PRIV_SV, 0,   0,    wMPM),
    BANKREG(RSYS_VE0_VE2R,   MPC,   mpc,    0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   TID,   tid,    0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   PPC,   ppc,    0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DCC0,  dcc0,   0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DCV0,  dcv0,   0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DCC1,  dcc1,   0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DCV1,  dcv1,   0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA0L, ipa0l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA0U, ipa0u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA1L, ipa1l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA1U, ipa1u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA2L, ipa2l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA2U, ipa2u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA3L, ipa3l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   IPA3U, ipa3u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA0L, dpa0l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA0U, dpa0u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA1L, dpa1l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA1U, dpa1u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA2L, dpa2l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA2U, dpa2u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA3L, dpa3l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA3U, dpa3u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA4L, dpa4l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA4U, dpa4u,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA5L, dpa5l,  0x10, 0x01, PRIV_SV, 0,   0,    0),
    BANKREG(RSYS_VE0_VE2R,   DPA5U, dpa5u,  0x10, 0x01, PRIV_SV, 0,   0,    0),

    //
    // VE2 Register indices (User)
    // GRP=0xFF BNK=0x00
    //
    //      ARCH            REG    NAME    GRP   BNK  PRIV      ENDB R       W
    BANKREG(RSYS_VE0_VE2R,  PSW,   psw,   0xFF, 0x00, PRIV_PSW, 1,   rPSW,   wModelPSW),
    BANKREG(RSYS_VE0_VE2R,  FPST,  fpst,  0xFF, 0x00, PRIV_CU0, 0,   rFPST,  wFPST),
    BANKREG(RSYS_VE0_VE2R,  FPCC,  fpcc,  0xFF, 0x00, PRIV_CU0, 0,   rFPCC,  wFPCC),
    BANKREG(RSYS_VE0_VE2R,  FPCFG, fpcfg, 0xFF, 0x00, PRIV_CU0, 0,   rFPCFG, wFPCFG),
    BANKREG(RSYS_VE0_VE2R,  CTPC,  ctpc,  0xFF, 0x00, PRIV_UM,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,  CTPSW, ctpsw, 0xFF, 0x00, PRIV_UM,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,  CTBP,  ctbp,  0xFF, 0x00, PRIV_UM,  0,   0,      0),

    //
    // VE2 Register indices (User-compatible) requires parameter setting
    // GRP=0xFF BNK=0xFF
    //
    //      ARCH             REG    NAME    GRP   BNK   PRIV     ENDB R       W
    BANKREG(RSYS_VE0_VE2R,   EIPC,  eipc,  0xFF, 0xFF, PRIV_SV,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   EIPSW, eipsw, 0xFF, 0xFF, PRIV_SV,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   FEPC,  fepc,  0xFF, 0xFF, PRIV_SV,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   FEPSW, fepsw, 0xFF, 0xFF, PRIV_SV,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   ECR,   ecr,   0xFF, 0xFF, PRIV_SV,  0,   rECR,   wECR),  // Not present in REG_RH850G3M
    BANKREG(RSYS_VE0_VE2R,   PSW,   psw,   0xFF, 0xFF, PRIV_PSW, 1,   rPSW,   wModelPSW),
    BANKREG(RSYS_VE0_VE2R,   FPST,  fpst,  0xFF, 0xFF, PRIV_CU0, 0,   rFPST,  wFPST),
    BANKREG(RSYS_VE0_VE2R,   FPCC,  fpcc,  0xFF, 0xFF, PRIV_CU0, 0,   rFPCC,  wFPCC),
    BANKREG(RSYS_VE0_VE2R,   FPCFG, fpcfg, 0xFF, 0xFF, PRIV_CU0, 0,   rFPCFG, wFPCFG),
    BANKREG(RSYS_VE0_VE2R,   EIIC,  eiic,  0xFF, 0xFF, PRIV_SV,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   FEIC,  feic,  0xFF, 0xFF, PRIV_SV,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   CTPC,  ctpc,  0xFF, 0xFF, PRIV_UM,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   CTPSW, ctpsw, 0xFF, 0xFF, PRIV_UM,  0,   0,      0),
    BANKREG(RSYS_VE0_VE2R,   CTBP,  ctbp,  0xFF, 0xFF, PRIV_UM,  0,   0,      0),

    //
    // RH850G3M Register indices
    //
    //     ARCH        REG     NAME    SEL  PRIV         R     W
    SELREG(RSYS_RHG3M, FPEC,   fpec,   0x0, PRIV_CU0_SV, 0,    0),
    // SEL 1
    SELREG(RSYS_RHG3M, MCFG0,  mcfg0,  0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, RBASE,  rbase,  0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, EBASE,  ebase,  0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, INTBP,  intbp,  0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, MCTL,   mctl,   0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, PID,    pid,    0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, FPIPR,  fpipr,  0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, SCCFG,  sccfg,  0x1, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, SCBP,   scbp,   0x1, PRIV_SV,     0,    0),
    // SEL 2
    SELREG(RSYS_RHG3M, HTCFG0, htcfg0, 0x2, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, MEA,    mea,    0x2, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ASID,   asid,   0x2, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, MEI,    mei,    0x2, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ISPR,   ispr,   0x2, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, PMR,    pmr,    0x2, PRIV_SV,     0,    wPMR),
    SELREG(RSYS_RHG3M, ICSR,   icsr,   0x2, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, INTCFG, intcfg, 0x2, PRIV_SV,     0,    0),
    // SEL 4
    SELREG(RSYS_RHG3M, ICTAGL, ictagl, 0x4, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ICTAGH, ictagh, 0x4, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ICDATL, icdatl, 0x4, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ICDATH, icdath, 0x4, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ICCTRL, icctrl, 0x4, PRIV_SV,     rICCTRL,    0),
    SELREG(RSYS_RHG3M, ICCFG,  iccfg,  0x4, PRIV_SV,     0,    0),
    SELREG(RSYS_RHG3M, ICERR,  icerr,  0x4, PRIV_SV,     0,    0),
    // SEL 5
    SELREG(RSYS_RHG3M, MPM,    mpm,    0x5, PRIV_SV,     0,    wMPM),
    SELREG(RSYS_RHG3M, MPRC,   mprc,   0x5, PRIV_SV,     0,    wMPRC),
    SELREG(RSYS_RHG3M, MPBRGN, mpbrgn, 0x5, PRIV_SV,     0,    wMPBRGN),
    SELREG(RSYS_RHG3M, MPTRGN, mptrgn, 0x5, PRIV_SV,     0,    wMPTRGN),
    SELREG(RSYS_RHG3M, MCA,    mca,    0x5, PRIV_SV,     0,    wMCA),
    SELREG(RSYS_RHG3M, MCS,    mcs,    0x5, PRIV_SV,     0,    wMCS),
    SELREG(RSYS_RHG3M, MCC,    mcc,    0x5, PRIV_SV,     0,    wMCC),
    SELREG(RSYS_RHG3M, MCR,    mcr,    0x5, PRIV_SV,     0,    wMCR),
    // SEL 6
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 0,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 0,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 0,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 1,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 1,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 1,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 2,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 2,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 2,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 3,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 3,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 3,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 4,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 4,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 4,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 5,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 5,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 5,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 6,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 6,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 6,  0x6, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA,  mpla, 7,  0x6, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA,  mpua, 7,  0x6, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT,  mpat, 7,  0x6, PRIV_SV,     0,    wMPAT),
    // SEL 7
    SELREGIDX(RSYS_RHG3M, MPLA, mpla,  8, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua,  8, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat,  8, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla,  9, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua,  9, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat,  9, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla, 10, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua, 10, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat, 10, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla, 11, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua, 11, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat, 11, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla, 12, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua, 12, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat, 12, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla, 13, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua, 13, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat, 13, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla, 14, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua, 14, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat, 14, 0x7, PRIV_SV,     0,    wMPAT),
    SELREGIDX(RSYS_RHG3M, MPLA, mpla, 15, 0x7, PRIV_SV,     0,    wMPLA),
    SELREGIDX(RSYS_RHG3M, MPUA, mpua, 15, 0x7, PRIV_SV,     0,    wMPUA),
    SELREGIDX(RSYS_RHG3M, MPAT, mpat, 15, 0x7, PRIV_SV,     0,    wMPAT),
    // SEL 13
    SELREG(RSYS_RHG3M, CDBCR,  cdbcr,  0xD, PRIV_SV,     0,    0),

    {0}
};


inline static Uns32 getBlockMask(v850P v850) {
    return v850->SPR_BSEL.reg;
}

#define RT_READ(SREG) \
   v850->SPR_ ## SREG .reg & v850->SPR_ ## SREG ## _rmask.reg

V850_REG_READ_FN(rECR) {
    v850PackECR(v850);
    return RT_READ(ECR);
}
V850_REG_READ_FN(rPSW) {
    //
    // Read cannot generate Privilege exception
    //
    v850PackPSW(v850);
    return RT_READ(PSW);
}
V850_REG_READ_FN(rEFG) {
    v850PackEFG(v850);
    return RT_READ(EFG);
}
V850_REG_READ_FN(rFPSR) {
    v850PackFPSR(v850);
    return RT_READ(FPSR);
}
V850_REG_READ_FN(rFPST) {
    v850PackFPST(v850);
    return RT_READ(FPST);
}
V850_REG_READ_FN(rFPCC) {
    v850PackFPCC(v850);
    return RT_READ(FPCC);
}
V850_REG_READ_FN(rFPCFG) {
    v850PackFPCFG(v850);
    return RT_READ(FPCFG);
}
V850_REG_READ_FN(rICCTRL) {
    return 0;
}

#define RT_WRITE(SREG, VALUE) { \
    Uns32 mask    = v850->SPR_ ## SREG ## _wmask.reg; \
    Uns32 prevREG = v850->SPR_ ## SREG .reg & ~mask;  \
    Uns32 nextREG = VALUE &  mask;  \
    v850->SPR_ ## SREG .reg = prevREG | nextREG;      \
}
#define RT_WRITE_ARR(SREG, IDX, VALUE) { \
    Uns32 mask    = v850->SPR_ ## SREG ## _wmask[IDX].reg; \
    Uns32 prevREG = v850->SPR_ ## SREG [IDX].reg & ~mask;  \
    Uns32 nextREG = VALUE & mask;  \
    v850->SPR_ ## SREG [IDX].reg = prevREG | nextREG; \
}

V850_REG_WRITE_FN(wBSEL) {
    RT_WRITE(BSEL, value);
    vmirtSetBlockMask((vmiProcessorP)v850, getBlockMask(v850));
}

V850_REG_WRITE_FN(wECR) {
    RT_WRITE(ECR, value);
    v850UnPackECR(v850);
}

V850_REG_WRITE_FN(wPSW) {
    RT_WRITE(PSW, value);
    v850UnPackPSW(v850);
    v850TestInterrupt(v850);
}

V850_REG_WRITE_FN(wEFG) {
    RT_WRITE(EFG, value);
    v850UnPackEFG(v850);
}

V850_REG_WRITE_FN(wPMR) {
    RT_WRITE(PMR, value);
    RT_WRITE(ICSR, 0);
    v850TestInterrupt(v850);
}

static V850_REG_WRITE_FN(wModelPSW) {
    //
    // Write of certain bits can generate Privilege exception
    //
    Bool priv_violation = False;
    //
    // User mode Write Check
    //
    if (v850->SPR_PSW.UM) {
        Uns32 setbits = (v850->SPR_PSW.reg ^ value) & v850->SPR_PSW_wmask_um.reg;
         if (setbits) {
            // Attempt to write privileged bits
            priv_violation = True;
        }
    }

    if (priv_violation) {
        vmic_PIE(v850, 5, 0, SPR_LOAD, 0);
    } else {
        wPSW(v850, value, 0);
    }

    //
    // Could have flipped between USER/SUPV Modes
    //
    v850SetVMMode(v850);
}

V850_REG_WRITE_FN(wFPSR) {
    RT_WRITE(FPSR, value);
    v850UnPackFPSR(v850);
    v850UpdateFPControlWord(v850);
}
V850_REG_WRITE_FN(wFPST) {
    RT_WRITE(FPST, value);
    v850UnPackFPST(v850);
}
V850_REG_WRITE_FN(wFPCC) {
    RT_WRITE(FPCC, value);
    v850UnPackFPCC(v850);
}
V850_REG_WRITE_FN(wFPCFG) {
    RT_WRITE(FPCFG, value);
    v850UnPackFPCFG(v850);
    v850UpdateFPControlWord(v850);
}

V850_REG_WRITE_FN(wSW_CTL) {
    TYPE_SPR_SW_CTL SPR_SW_CTL;
    SPR_SW_CTL.reg = value;

    if (SPR_SW_CTL.SET) {
        v850->SPR_EH_CFG.reg  = v850->SPR_SW_CFG.reg;
        v850->SPR_EH_BASE.reg = v850->SPR_SW_BASE.reg;
    }
}

//
// MPU
//
V850_REG_WRITE_FN(wMPM) {
    v850WriteMPU_MPM(v850, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMPRC) {
    v850WriteMPU_MPRC(v850, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMPBRGN) {
    RT_WRITE(MPBRGN, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMPTRGN) {
    RT_WRITE(MPTRGN, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMCA) {
    RT_WRITE(MCA, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMCS) {
    RT_WRITE(MCS, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMCC) {
    RT_WRITE(MCC, value);
    v850WriteMPU_MCC(v850, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMCR) {
    RT_WRITE(MCR, value);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMPLA) {
    v850WriteMPU_MPLA(v850, value, arrIDX);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMPUA) {
    v850WriteMPU_MPUA(v850, value, arrIDX);
//    v850PrintMPU(v850, 16);
}
V850_REG_WRITE_FN(wMPAT) {
    v850WriteMPU_MPAT(v850, value, arrIDX);
//    v850PrintMPU(v850, 16);
}

//
// regArch is the arch field in the BANKREG
// cpuArch is the arch field on the CPU
//
static Bool isRegSupported(v850Architecture cpuArch, v850Architecture regArch) {
    if (cpuArch & regArch) {
        return True;
    } else {
        return False;
    }
}

static v850SystemRegisterP lookupEntryC(v850P v850, Uns8 regID, Uns8 selID) {
    v850SystemRegisterP reg = sysRegs;
    while (reg->name) {

        Bool regInArch = isRegSupported(v850->configInfo.arch, reg->arch);

        if (regInArch) {
            if (regID==reg->regID && selID==reg->selID) {
                return reg;
            }
        }
        reg++;
    }
    return 0;
}

static v850SystemRegisterP lookupEntryV(v850P v850, Uns8 regID, Bool isMorph) {

    Uns8 grp = v850->SPR_BSEL.GRP;
    Uns8 bnk = v850->SPR_BSEL.BNK;

    if (isMorph) {
        Uns32 blockMask = getBlockMask(v850);
        vmimtValidateBlockMask(blockMask);
    }

    v850SystemRegisterP reg = sysRegs;
    while (reg->name) {

        Bool regInArch = isRegSupported(v850->configInfo.arch, reg->arch);

        if (regInArch) {
            if (regID>=V850_SPR_EIWR && regID<=V850_SPR_BSEL) {
                //
                // Bank Independant selection
                //
                if (regID==reg->regID) {
                    return reg;
                }
            } else {
                //
                // Banked registers
                //
                if (regID==reg->regID && grp==reg->GRP && bnk==reg->BNK) {
                    if (grp==0xFF && bnk==0xFF) {
                        //
                        // User Compatible Bank enabled ?
                        //
                        if (v850->params.ucbank) {
                            return reg;
                        }
                    } else {
                        return reg;
                    }
                }
            }
        }
        reg++;
    }
    return 0;
}

v850SystemRegisterP v850GetSystemRegister(v850P v850, Uns8 regID, Uns8 selID, Bool isMorph) {
    if (v850->configInfo.arch == RH850G3M) {
        // decode GRP, BNK from selID
        return lookupEntryC(v850, regID, selID);
    } else {
        return lookupEntryV(v850, regID, isMorph);
    }
}

/*
 * The BSEL register is non functional for the RH850
 * all accesses to BANK>0 use the new LDSR/STSR instructions which use
 * a selID parameter
 */

//
// STSR regID, reg2
// GR[reg2] <- SR[regID]
//
V850_MORPH_FN(morphSTSR_F09SR) {

    Uns8   regID = state->info.reg1;
    Uns8   reg2  = state->info.reg2;
    Uns8   selID = state->info.reg3;
    vmiReg rd    = V850_GPR_WR(reg2);

    v850SystemRegisterP entry = v850GetSystemRegister(state->v850, regID, selID, True);

    Bool UserMode = (state->v850->mode==RH850_M_USER) || (state->v850->mode==RH850_M_USER_MPU);

    //
    // If the register is PSW, this needs special handling of the Access Permissions
    //


    if (!entry) {
        vmimtArgProcessor();
        vmimtArgUns32(regID);
        vmimtArgUns32(selID);
        vmimtArgUns32(SPR_STORE);
        vmimtArgUns32(reg2);

        if (UserMode) {
            // Exception
            vmimtCall((vmiCallFn)vmic_PIE);
        } else {
            // Warn Undefined register
            vmimtCall((vmiCallFn)vmic_PIW);
        }

    } else if (UserMode && ((entry->priv&PRIV_SV)==PRIV_SV)) {
        // take a privilege instruction exception (PIE)
        vmimtArgProcessor();
        vmimtArgUns32(regID);
        vmimtArgUns32(selID);
        vmimtArgUns32(SPR_STORE);
        vmimtArgUns32(reg2);

        vmimtCall((vmiCallFn)vmic_PIE);

    } else if(entry->readCB) {

        //
        // PRIV_PSW goes down this branch
        //
        // using callback
        vmimtRegReadImpl(entry->name);
        vmimtArgProcessor();
        vmimtArgUns32(entry->arrIDX);
        vmimtCallResult((vmiCallFn)entry->readCB, V850_GPR_BITS, rd);

    } else {

        // using raw register
        Uns32 mask = getSPRMask(state->v850, entry->rMask);
        vmimtBinopRRC(V850_GPR_BITS, vmi_AND, rd, entry->raw, mask, 0);
    }
}

//
// LDSR reg2, regID
// SR[regID] <- GR[reg2]
//
V850_MORPH_FN(morphLDSR_F09RS1) {

    Uns8   regID = state->info.reg2;
    Uns8   reg1  = state->info.reg1;
    Uns8   selID = state->info.reg3;
    vmiReg rs    = V850_GPR_RD(reg1);

    v850SystemRegisterP entry = v850GetSystemRegister(state->v850, regID, selID, True);

    Bool UserMode = (state->v850->mode==RH850_M_USER) || (state->v850->mode==RH850_M_USER_MPU);

    //
    // If the register is PSW, this needs special handling of the Access Permissions
    //

    if (!entry) {
        vmimtArgProcessor();
        vmimtArgUns32(regID);
        vmimtArgUns32(selID);
        vmimtArgUns32(SPR_LOAD);
        vmimtArgUns32(reg1);

        if (UserMode) {
            // Exception
            vmimtCall((vmiCallFn)vmic_PIE);
        } else {
            // Warn Undefined register
            vmimtCall((vmiCallFn)vmic_PIW);
        }

    } else if (UserMode && ((entry->priv&PRIV_SV)==PRIV_SV)) {
        // take a privilege instruction exception (PIE)
        vmimtArgProcessor();
        vmimtArgUns32(regID);
        vmimtArgUns32(selID);
        vmimtArgUns32(SPR_LOAD);
        vmimtArgUns32(reg1);

        vmimtCall((vmiCallFn)vmic_PIE);

    } else {

        if(entry->endBlock) {
            vmimtEndBlock();
        }

        if(entry->writeCB) {

            //
            // PRIV_PSW goes down this branch
            //
            // using callback
            vmimtRegWriteImpl(entry->name);
            vmimtArgProcessor();
            vmimtArgReg(V850_GPR_BITS, rs);
            vmimtArgUns32(entry->arrIDX);
            vmimtCall((vmiCallFn)entry->writeCB);

        } else {

            // using raw register
            Uns32 mask = getSPRMask(state->v850, entry->wMask);
            vmimtRegNotReadR(V850_GPR_BITS, entry->raw);
            vmimtBinopRC (V850_GPR_BITS, vmi_ANDN, entry->raw, mask, 0);
            vmimtBinopRRC(V850_GPR_BITS, vmi_AND,  V850_TMP_WR(0), rs, mask, 0);
            vmimtBinopRR (V850_GPR_BITS, vmi_OR,   entry->raw, V850_TMP_WR(0), 0);
        }
    }
}
