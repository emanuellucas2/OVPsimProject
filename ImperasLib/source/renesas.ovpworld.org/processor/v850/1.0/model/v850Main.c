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

#include <string.h>

#include "hostapi/impAlloc.h"

#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

#include "v850Bus.h"
#include "v850Ports.h"
#include "v850Decode.h"
#include "v850Doc.h"
#include "v850MorphFP.h"
#include "v850Structure.h"
#include "v850Config.h"
#include "v850Functions.h"
#include "v850Parameters.h"
#include "v850Exceptions.h"

VMI_SAVE_STATE_FN(v850SaveState) {
    v850P v850 = (v850P)processor;

    switch(phase) {
        case SRT_BEGIN:
            // start of SMP cluster
            break;

        case SRT_BEGIN_CORE:
            // start of individual core
            break;

        case SRT_END_CORE:
            // end of individual core - save general fields
            VMIRT_SAVE_FIELD(cxt, v850, disable);
            VMIRT_SAVE_FIELD(cxt, v850, exception);
            VMIRT_SAVE_FIELD(cxt, v850, netPorts);
            VMIRT_SAVE_FIELD(cxt, v850, netValue);
            VMIRT_SAVE_FIELD(cxt, v850, FLG_INTPEND);
            VMIRT_SAVE_FIELD(cxt, v850, FLG_NMIPEND);
            VMIRT_SAVE_FIELD(cxt, v850, FLG_RSTPEND);
            VMIRT_SAVE_FIELD(cxt, v850, FLG_TMP);
            VMIRT_SAVE_FIELD(cxt, v850, FLG_LL);
            VMIRT_SAVE_FIELD(cxt, v850, REG_LL);
            VMIRT_SAVE_FIELD(cxt, v850, REG_RETMASK);
            VMIRT_SAVE_FIELD(cxt, v850, mode);
            break;

        case SRT_END:
            // end of SMP cluster
            break;

        default:
            // not reached
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }
}

VMI_RESTORE_STATE_FN(v850RestoreState) {
    v850P v850 = (v850P)processor;

    switch(phase) {
        case SRT_BEGIN:
            // start of SMP cluster
            break;

        case SRT_BEGIN_CORE:
            // start of individual core
            break;

        case SRT_END_CORE:
            // end of individual core - save general fields
            VMIRT_RESTORE_FIELD(cxt, v850, disable);
            VMIRT_RESTORE_FIELD(cxt, v850, exception);
            VMIRT_RESTORE_FIELD(cxt, v850, netPorts);
            VMIRT_RESTORE_FIELD(cxt, v850, netValue);
            VMIRT_RESTORE_FIELD(cxt, v850, FLG_INTPEND);
            VMIRT_RESTORE_FIELD(cxt, v850, FLG_NMIPEND);
            VMIRT_RESTORE_FIELD(cxt, v850, FLG_RSTPEND);
            VMIRT_RESTORE_FIELD(cxt, v850, FLG_TMP);
            VMIRT_RESTORE_FIELD(cxt, v850, FLG_LL);
            VMIRT_RESTORE_FIELD(cxt, v850, REG_LL);
            VMIRT_RESTORE_FIELD(cxt, v850, REG_RETMASK);
            VMIRT_RESTORE_FIELD(cxt, v850, mode);
            break;

        case SRT_END:
            // end of SMP cluster
            break;

        default:
            // not reached
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }
}

VMI_CONSTRUCTOR_FN(v850Constructor) {
    v850P v850 = (v850P)processor;
    v850ParamValuesP params = (v850ParamValuesP)parameterValues;

    v850->flags = vmirtProcessorFlags(processor);
    v850->configInfo = v850ConfigTable[params->variant];
    if (v850->configInfo.name == NULL) {
        // Assign value as First Variant
        v850->configInfo = v850ConfigTable[0];
    }
    Int32 iter;
    for (iter=0; iter<32; iter++) {
        v850->gpr[iter] = 0;
    }
    v850->SPR_EIPC.reg = 0; // readonly=0
    v850->SPR_EIPC_wmask.reg = ~0;
    v850->SPR_EIPC_rmask.reg = ~0;
    v850->SPR_EIPSW.reg = 0; // readonly=0
    v850->SPR_EIPSW_wmask.reg = ~0;
    v850->SPR_EIPSW_rmask.reg = ~0;
    v850->SPR_FEPC.reg = 0; // readonly=0
    v850->SPR_FEPC_wmask.reg = ~0;
    v850->SPR_FEPC_rmask.reg = ~0;
    v850->SPR_FEPSW.reg = 0; // readonly=0
    v850->SPR_FEPSW_wmask.reg = ~0;
    v850->SPR_FEPSW_rmask.reg = ~0;

    // ECR is an alias of EIIC FEIC
    v850->SPR_EIIC.reg = 0; // readonly=0
    v850->SPR_EIIC_wmask.reg = ~0;
    v850->SPR_EIIC_rmask.reg = ~0;
    v850->SPR_FEIC.reg = 0; // readonly=0
    v850->SPR_FEIC_wmask.reg = ~0;
    v850->SPR_FEIC_rmask.reg = ~0;
    v850->SPR_ECR.reg  = 0;
    v850->SPR_ECR_wmask.reg  = ~0;
    v850->SPR_ECR_rmask.reg  = ~0;

    v850->SPR_PSW.reg = 0x0; // readonly=0
    v850->SPR_PSW.ID  = 1;
    v850->SPR_PSW_wmask.reg = 0x000000ff;   // e0
    if (v850->configInfo.arch & ISA_E2) {
        v850->SPR_PSW_wmask.reg |= 0x00070e00;
    }
    v850->SPR_PSW_rmask.reg = ~0;

    v850->SPR_CTPC.reg = 0; // readonly=0
    v850->SPR_CTPC_wmask.reg = ~0;
    v850->SPR_CTPC_rmask.reg = ~0;
    v850->SPR_CTPSW.reg = 0; // readonly=0
    v850->SPR_CTPSW_wmask.reg = ~0;
    v850->SPR_CTPSW_rmask.reg = ~0;
    v850->SPR_DBPC.reg = 0; // readonly=0
    v850->SPR_DBPC_wmask.reg = ~0;
    v850->SPR_DBPC_rmask.reg = ~0;
    v850->SPR_DBPSW.reg = 0; // readonly=0
    v850->SPR_DBPSW_wmask.reg = ~0;
    v850->SPR_DBPSW_rmask.reg = ~0;
    v850->SPR_CTBP.reg = 0; // readonly=0
    v850->SPR_CTBP_wmask.reg = ~0;
    v850->SPR_CTBP_rmask.reg = ~0;
    v850->SPR_DIR.reg = 0; // readonly=0
    v850->SPR_DIR_wmask.reg = ~0;
    v850->SPR_DIR_rmask.reg = ~0;
    v850->SPR_BPC.reg = 0; // readonly=0
    v850->SPR_BPC_wmask.reg = ~0;
    v850->SPR_BPC_rmask.reg = ~0;
    v850->SPR_ASID.reg = 0; // readonly=0
    v850->SPR_ASID_wmask.reg = ~0;
    v850->SPR_ASID_rmask.reg = ~0;
    v850->SPR_BPAV.reg = 0; // readonly=0
    v850->SPR_BPAV_wmask.reg = ~0;
    v850->SPR_BPAV_rmask.reg = ~0;
    v850->SPR_BPAM.reg = 0; // readonly=0
    v850->SPR_BPAM_wmask.reg = ~0;
    v850->SPR_BPAM_rmask.reg = ~0;
    v850->SPR_BPDV.reg = 0; // readonly=0
    v850->SPR_BPDV_wmask.reg = ~0;
    v850->SPR_BPDV_rmask.reg = ~0;
    v850->SPR_BPDM.reg = 0; // readonly=0
    v850->SPR_BPDM_wmask.reg = ~0;
    v850->SPR_BPDM_rmask.reg = ~0;
    for (iter=0; iter<4; iter++) {
        v850->tmp[iter] = 0;
    }
    v850->FLG_PSW_SAT = 0; // readonly=0
    v850->FLG_PSW_ID = 1; // readonly=0
    v850->FLG_PSW_EP = 0; // readonly=0
    v850->FLG_PSW_NP = 0; // readonly=0
    v850->FLG_INTPEND = 0; // readonly=0
    v850->FLG_NMIPEND = 0; // readonly=0
    v850->FLG_TMP = 0; // readonly=0
    v850->iendian = params->SETBIT(endian) ? params->endian : MEM_ENDIAN_LITTLE;
    v850->dendian = params->SETBIT(endian) ? params->endian : MEM_ENDIAN_LITTLE;
    v850->exception = v850_E_reset;

    //
    // Variant specific setup
    //
    if (v850->configInfo.arch == V850E1F) {
        v850->SPR_EFG.reg = 0; // readonly=0
        v850->SPR_EFG_wmask.reg = 0x00000017; // 0000 0000 0000 0000 0000 0000 0001 0111 = 0x00003F17 TR OV S Z
        v850->SPR_EFG_rmask.reg = 0x00003F17; // 0000 0000 0000 0000 0011 1111 0001 0111 = 0x00003F17
        v850->SPR_ECT.reg = 0; // readonly=0
        v850->SPR_ECT_wmask.reg = 0x00001F00; // 0000 0000 0000 0000 0001 1111 0000 0000 = 0x00001F00
        v850->SPR_ECT_rmask.reg = 0x00001F00;
    }

    //
    // Variant specific setup
    //
    if (v850->configInfo.arch & ISA_E2) {
        v850->SPR_EIWR_wmask.reg = ~0;
        v850->SPR_EIWR_rmask.reg = ~0;
        v850->SPR_FEWR_wmask.reg = ~0;
        v850->SPR_FEWR_rmask.reg = ~0;
        v850->SPR_DBWR_wmask.reg = ~0;
        v850->SPR_DBWR_rmask.reg = ~0;

        v850->SPR_BSEL_wmask.reg = ~0;
        v850->SPR_BSEL_wmask.RSV0 = 0;
        v850->SPR_BSEL_rmask.reg = v850->SPR_BSEL_wmask.reg;

        v850->SPR_FPSR_wmask.reg = ~0;
        v850->SPR_FPSR_wmask.RSV0 = 0;
        v850->SPR_FPSR_wmask.RM = 0;
        v850->SPR_FPSR_wmask.FS = 0;
        v850->SPR_FPSR_rmask.reg = v850->SPR_FPSR_wmask.reg;
        v850->SPR_FPSR_rmask.FS = 1;

        v850->SPR_FPEPC_wmask.reg = ~0;
        v850->SPR_FPEPC_wmask.RSV0 = 0;
        v850->SPR_FPEPC_wmask.RSV1 = 0;
        v850->SPR_FPEPC_rmask.reg = v850->SPR_FPEPC_wmask.reg;

        v850->SPR_FPST_wmask.reg = ~0;
        if (v850->configInfo.arch & RSYS_VE2_VE2R) {
            // Register reserved on VE2
            v850->SPR_FPST_wmask.IF = 0;

            v850->SPR_SW_CFG_wmask.RINT = 1;
            v850->SPR_SW_CFG_rmask = v850->SPR_SW_CFG_wmask;
            v850->SPR_SW_BASE_wmask.BITS_28_TO_13 = ~0;
            v850->SPR_SW_BASE_rmask = v850->SPR_SW_BASE_wmask;

            v850->SPR_EH_CFG_wmask.reg  = 0;
            v850->SPR_EH_CFG_rmask.RINT = 1;
            v850->SPR_EH_BASE_wmask.reg = 0;
            v850->SPR_EH_BASE_rmask.BITS_28_TO_13 = ~0;
        }
        v850->SPR_FPST_wmask.RSV0 = 0;
        v850->SPR_FPST_wmask.RSV1 = 0;
        v850->SPR_FPST_wmask.RSV2 = 0;
        v850->SPR_FPST_rmask.reg = v850->SPR_FPST_wmask.reg;

        v850->SPR_FPCC_wmask.reg = ~0;
        v850->SPR_FPCC_wmask.RSV0 = 0;
        v850->SPR_FPCC_rmask.reg = v850->SPR_FPCC_wmask.reg;

        v850->SPR_FPCFG_wmask.reg = ~0;
        v850->SPR_FPCFG_wmask.RSV0 = 0;
        v850->SPR_FPCFG_wmask.RM   = 0;
        v850->SPR_FPCFG_wmask.RSV1 = 0;
        v850->SPR_FPCFG_rmask.reg = v850->SPR_FPCFG_wmask.reg;

        v850->SPR_FPEC_wmask.reg = ~0;
        v850->SPR_FPEC_wmask.RSV0 = 0;
        v850->SPR_FPEC_rmask.reg = v850->SPR_FPCC_wmask.reg;
    }

    //
    // Variant specific setup
    //
    if (v850->configInfo.arch == RH850G3M) {
        v850->SPR_PSW.reg = 0x0; // readonly=0
        v850->SPR_PSW.ID  = 1;
        v850->SPR_PSW_wmask.reg = ~0;
        v850->SPR_PSW_wmask.RSV0 = 0;
        v850->SPR_PSW_wmask.R_RSV1 = 0;
        v850->SPR_PSW_wmask.R_RSV2 = 0;
        v850->SPR_PSW_wmask.R_RSV3 = 0;
        v850->SPR_PSW_rmask.reg = v850->SPR_PSW_wmask.reg;

        v850->SPR_PSW_wmask_um.reg = ~0;
        v850->SPR_PSW_wmask_um.SAT = 0;
        v850->SPR_PSW_wmask_um.CY  = 0;
        v850->SPR_PSW_wmask_um.OV  = 0;
        v850->SPR_PSW_wmask_um.S   = 0;
        v850->SPR_PSW_wmask_um.Z   = 0;

        v850->SPR_EIPSW       = v850->SPR_PSW;
        v850->SPR_EIPSW_wmask = v850->SPR_PSW_wmask;
        v850->SPR_EIPSW_rmask = v850->SPR_PSW_rmask;

        v850->SPR_FEPSW       = v850->SPR_PSW;
        v850->SPR_FEPSW_wmask = v850->SPR_PSW_wmask;
        v850->SPR_FEPSW_rmask = v850->SPR_PSW_rmask;

        // BSEL is always zero so simply use the mask
        // Any read or write results in zero
        v850->SPR_BSEL_wmask.reg = 0;
        v850->SPR_BSEL_rmask.reg = 0;

        v850->SPR_MCFG0.reg = 0;
        v850->SPR_MCFG0_wmask.reg = ~0;
        v850->SPR_MCFG0_wmask.RSV0 = 0;
        v850->SPR_MCFG0_wmask.RSV1 = 0;
        v850->SPR_MCFG0_wmask.RSV2 = 0;
        v850->SPR_MCFG0_rmask.reg = v850->SPR_MCFG0_wmask.reg;
        v850->SPR_MCFG0.SPID = params->SPID;

        v850->SPR_RBASE.reg       = params->RBASE;
        v850->SPR_RBASE_wmask.reg = 0;
        v850->SPR_RBASE_rmask.reg = v850->SPR_RBASE_wmask.reg;

        v850->SPR_EBASE.reg = 0x0;
        v850->SPR_EBASE_wmask.reg = ~0;
        v850->SPR_EBASE_wmask.RSV0 = 0;
        v850->SPR_EBASE_rmask.reg = v850->SPR_EBASE_wmask.reg;

        v850->SPR_INTBP.reg = 0x0;
        v850->SPR_INTBP_wmask.reg = ~0;
        v850->SPR_INTBP_wmask.RSV0 = 0;
        v850->SPR_INTBP_rmask.reg = v850->SPR_INTBP_wmask.reg;

        v850->SPR_MCTL.reg = 0x80000000;
        v850->SPR_MCTL_wmask.reg = ~0;
        v850->SPR_MCTL_wmask.RSV0 = 0;
        v850->SPR_MCTL_rmask.reg = v850->SPR_MCTL_wmask.reg;

        v850->SPR_PID.reg = 0x0; // Implementation specific
        v850->SPR_PID_wmask.reg = 0;
        v850->SPR_PID_rmask.reg = v850->SPR_PID_wmask.reg;

        v850->SPR_FPIPR.reg = 0x80000000;
        v850->SPR_FPIPR_wmask.reg = ~0;
        v850->SPR_FPIPR_wmask.RSV0 = 0;
        v850->SPR_FPIPR_rmask.reg = v850->SPR_FPIPR_wmask.reg;

        v850->SPR_SCCFG.reg = 0x0;
        v850->SPR_SCCFG_wmask.reg = ~0;
        v850->SPR_SCCFG_wmask.RSV0 = 0;
        v850->SPR_SCCFG_rmask.reg = v850->SPR_SCCFG_wmask.reg;

        v850->SPR_SCBP.reg = 0x0;
        v850->SPR_SCBP_wmask.reg = ~0;
        v850->SPR_SCBP_wmask.SCBP_0_1 = 0;
        v850->SPR_SCBP_rmask.reg = v850->SPR_SCBP_wmask.reg;

        v850->SPR_HTCFG0.reg  = 0x0;
        v850->SPR_HTCFG0.PEID = params->PEID;
        v850->SPR_HTCFG0_wmask.reg = 0;
        v850->SPR_HTCFG0_rmask.reg = ~0;

        v850->SPR_MEA.reg = 0x0;
        v850->SPR_MEA_wmask.reg = ~0;
        v850->SPR_MEA_rmask.reg = v850->SPR_MEA_wmask.reg;

        v850->SPR_MEI.reg = 0x0;
        v850->SPR_MEI_wmask.reg = ~0;
        v850->SPR_MEI_wmask.RSV0 = 0;
        v850->SPR_MEI_wmask.RSV1 = 0;
        v850->SPR_MEI_wmask.RSV2 = 0;
        v850->SPR_MEI_rmask.reg = v850->SPR_MEI_wmask.reg;

        v850->SPR_ISPR.reg = 0x0;
        v850->SPR_ISPR_wmask.reg = ~0;
        v850->SPR_ISPR_wmask.RSV0 = 0;
        v850->SPR_ISPR_rmask.reg = v850->SPR_ISPR_wmask.reg;

        v850->SPR_PMR.reg = 0x0;
        v850->SPR_PMR_wmask.reg = ~0;
        v850->SPR_PMR_wmask.RSV0 = 0;
        v850->SPR_PMR_rmask.reg = v850->SPR_PMR_wmask.reg;

        v850->SPR_ICSR.reg = 0x0;
        v850->SPR_ICSR_wmask.reg = ~0;
        v850->SPR_ICSR_wmask.RSV0 = 0;
        v850->SPR_ICSR_rmask.reg = v850->SPR_ICSR_wmask.reg;

        v850->SPR_INTCFG.reg = 0x0;
        v850->SPR_INTCFG_wmask.reg = ~0;
        v850->SPR_INTCFG_wmask.RSV0 = 0;
        v850->SPR_INTCFG_rmask.reg = v850->SPR_INTCFG_wmask.reg;

        v850->SPR_MPM.reg = 0x0;
        v850->SPR_MPM_wmask.reg = 0;
        v850->SPR_MPM_wmask.MPE = 1;
        v850->SPR_MPM_wmask.SVP = 1;
        v850->SPR_MPM_rmask.reg = ~0;

        v850->SPR_MPRC.reg = 0x0;
        v850->SPR_MPRC_wmask.reg = ~0;
        v850->SPR_MPRC_wmask.RSV0 = 0;
        v850->SPR_MPRC_rmask.reg = v850->SPR_MPRC_wmask.reg;

        v850->SPR_MPBRGN.reg = 0x0;
        v850->SPR_MPBRGN_wmask.reg = 0;
        v850->SPR_MPBRGN_rmask.reg = v850->SPR_MPBRGN_wmask.reg;
        v850->SPR_MPBRGN_rmask.MPBRGN = ~0;

        v850->SPR_MPTRGN.reg = 0x0;
        v850->SPR_MPTRGN_wmask.reg = 0;
        v850->SPR_MPTRGN_rmask.reg = v850->SPR_MPTRGN_wmask.reg;
        v850->SPR_MPTRGN_rmask.MPTRGN = ~0;
        v850->SPR_MPTRGN.MPTRGN = 16;

        v850->SPR_MCA.reg = 0x0;
        v850->SPR_MCA_wmask.reg = ~0;
        v850->SPR_MCA_rmask.reg = v850->SPR_MCA_wmask.reg;

        v850->SPR_MCS.reg = 0x0;
        v850->SPR_MCS_wmask.reg = ~0;
        v850->SPR_MCS_rmask.reg = v850->SPR_MCS_wmask.reg;

        v850->SPR_MCC.reg = 0x0;
        v850->SPR_MCC_wmask.reg = ~0;
        v850->SPR_MCC_rmask.reg = 0;

        v850->SPR_MCR.reg = 0x0;
        v850->SPR_MCR_wmask.reg = ~0;
        v850->SPR_MCR_wmask.RSV0 = 0;
        v850->SPR_MCR_wmask.RSV1 = 0;
        v850->SPR_MCR_rmask.reg = v850->SPR_MCR_wmask.reg;

        // Duplicate MPLA
        int r;
        for (r=0; r<16; r++) {
            v850->SPR_MPLA[r].reg        = 0x0;
            v850->SPR_MPLA_wmask[r].reg  = ~0;
            v850->SPR_MPLA_wmask[r].RSV0 = 0;
            v850->SPR_MPLA_rmask[r].reg  = ~0;

            v850->SPR_MPUA[r].reg        = 0x0;
            v850->SPR_MPUA_wmask[r].reg  = ~0;
            v850->SPR_MPUA_wmask[r].RSV0 = 0;
            v850->SPR_MPUA_rmask[r].reg  = ~0;

            v850->SPR_MPAT[r].reg        = 0x0;
            v850->SPR_MPAT_wmask[r].reg  = ~0;
            v850->SPR_MPAT_wmask[r].RSV0 = 0;
            v850->SPR_MPAT_wmask[r].RSV1 = 0;
            v850->SPR_MPAT_rmask[r].reg  = ~0;

        }

        v850->SPR_ICTAGL.reg        = 0x0;
        v850->SPR_ICTAGL_wmask.reg  = ~0;
        v850->SPR_ICTAGL_wmask.RSV0 = 0;
        v850->SPR_ICTAGL_wmask.RSV1 = 0;
        v850->SPR_ICTAGL_wmask.RSV2 = 0;
        v850->SPR_ICTAGL_rmask.reg  = v850->SPR_ICTAGL_wmask.reg;

        v850->SPR_ICTAGH.reg        = 0x0;
        v850->SPR_ICTAGH_wmask.reg  = ~0;
        v850->SPR_ICTAGH_wmask.RSV0 = 0;
        v850->SPR_ICTAGH_wmask.RSV1 = 0;
        v850->SPR_ICTAGH_rmask.reg  = v850->SPR_ICTAGH_wmask.reg;

        v850->SPR_ICDATL.reg        = 0x0;
        v850->SPR_ICDATL_wmask.reg  = ~0;
        v850->SPR_ICDATL_rmask.reg  = v850->SPR_ICDATL_wmask.reg;

        v850->SPR_ICDATH.reg        = 0x0;
        v850->SPR_ICDATH_wmask.reg  = ~0;
        v850->SPR_ICDATH_rmask.reg  = v850->SPR_ICDATH_wmask.reg;

        v850->SPR_ICCTRL.reg        = 0x0;
        v850->SPR_ICCTRL_wmask.reg  = ~0;
        v850->SPR_ICCTRL_wmask.RSV0 = 0;
        v850->SPR_ICCTRL_wmask.RSV1 = 0;
        v850->SPR_ICCTRL_wmask.RSV2 = 0;
        v850->SPR_ICCTRL_rmask.reg  = v850->SPR_ICCTRL_wmask.reg;

        v850->SPR_ICCFG.reg        = 0x0;
        v850->SPR_ICCFG_wmask.reg  = 0;
        v850->SPR_ICCFG_rmask.reg  = ~0;

        v850->SPR_ICERR.reg        = 0x0;
        v850->SPR_ICERR_wmask.reg  = ~0;
        v850->SPR_ICERR_wmask.RSV0 = 0;
        v850->SPR_ICERR_wmask.RSV1 = 0;
        v850->SPR_ICERR_wmask.RSV2 = 0;
        v850->SPR_ICERR_wmask.RSV3 = 0;
        v850->SPR_ICERR_rmask.reg  = v850->SPR_ICERR_wmask.reg;

        v850->SPR_CDBCR.reg          = 0x0;
        v850->SPR_CDBCR_wmask.reg    = ~0;
        v850->SPR_CDBCR_wmask.RSV0   = 0;
        v850->SPR_CDBCR_rmask.reg    = v850->SPR_CDBCR_wmask.reg;
        v850->SPR_CDBCR_rmask.CDBCLR = 0;

    }

    // Store the parameters for later retrievel
    v850->params.GDBSIMMODE = params->GDBSIMMODE;
    v850->params.nofpu      = params->nofpu;
    v850->params.ucbank     = params->ucbank;
    v850->params.PEID       = params->PEID;
    v850->params.SPID       = params->SPID;

    //
    // allocate net port descriptions
    //
    v850NewNetPorts(v850);

    //
    // allocate bus port descriptions
    //
    v850NewBusPorts(v850);

    //
    // link the decoder callback
    //
    v850->decoder = v850Decode;

    //
    // Cause a reset exception
    //
    v850ProcessRESET(v850);

    //
    // Initialize FPU (if present)
    //
    v850ConfigureFPU(v850);
}

VMI_DESTRUCTOR_FN(v850Destructor) {
    v850P v850 = (v850P)processor;

    // free debugger interface structures
    if(v850->regInfoFrame) {
        STYPE_FREE(v850->regInfoFrame);
    }
    if(v850->regInfoVariant) {
        STYPE_FREE(v850->regInfoVariant);
    }

    //
    // free bus port descriptions
    //
    v850FreeBusPorts(v850);
}
