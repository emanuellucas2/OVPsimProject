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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisENET", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_ATCOR_maskWrite) {
    bport1_ab_data.ATCOR.value = (bport1_ab_data.ATCOR.value & BPORT1_AB_ATCOR_WRNMASK) | (data & BPORT1_AB_ATCOR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATCR_maskWrite) {
    bport1_ab_data.ATCR.value = (bport1_ab_data.ATCR.value & BPORT1_AB_ATCR_WRNMASK) | (data & BPORT1_AB_ATCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATINC_maskWrite) {
    bport1_ab_data.ATINC.value = (bport1_ab_data.ATINC.value & BPORT1_AB_ATINC_WRNMASK) | (data & BPORT1_AB_ATINC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATOFF_maskWrite) {
    bport1_ab_data.ATOFF.value = (bport1_ab_data.ATOFF.value & BPORT1_AB_ATOFF_WRNMASK) | (data & BPORT1_AB_ATOFF_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATPER_maskWrite) {
    bport1_ab_data.ATPER.value = (bport1_ab_data.ATPER.value & BPORT1_AB_ATPER_WRNMASK) | (data & BPORT1_AB_ATPER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATSTMP_maskWrite) {
    bport1_ab_data.ATSTMP.value = (bport1_ab_data.ATSTMP.value & BPORT1_AB_ATSTMP_WRNMASK) | (data & BPORT1_AB_ATSTMP_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATVR_maskWrite) {
    bport1_ab_data.ATVR.value = (bport1_ab_data.ATVR.value & BPORT1_AB_ATVR_WRNMASK) | (data & BPORT1_AB_ATVR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ECR_maskWrite) {
    bport1_ab_data.ECR.value = (bport1_ab_data.ECR.value & BPORT1_AB_ECR_WRNMASK) | (data & BPORT1_AB_ECR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EIMR_maskWrite) {
    bport1_ab_data.EIMR.value = (bport1_ab_data.EIMR.value & BPORT1_AB_EIMR_WRNMASK) | (data & BPORT1_AB_EIMR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EIR_maskWrite) {
    bport1_ab_data.EIR.value = (bport1_ab_data.EIR.value & BPORT1_AB_EIR_WRNMASK) | (data & BPORT1_AB_EIR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FTRL_maskWrite) {
    bport1_ab_data.FTRL.value = (bport1_ab_data.FTRL.value & BPORT1_AB_FTRL_WRNMASK) | (data & BPORT1_AB_FTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GALR_maskWrite) {
    bport1_ab_data.GALR.value = (bport1_ab_data.GALR.value & BPORT1_AB_GALR_WRNMASK) | (data & BPORT1_AB_GALR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GAUR_maskWrite) {
    bport1_ab_data.GAUR.value = (bport1_ab_data.GAUR.value & BPORT1_AB_GAUR_WRNMASK) | (data & BPORT1_AB_GAUR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IALR_maskWrite) {
    bport1_ab_data.IALR.value = (bport1_ab_data.IALR.value & BPORT1_AB_IALR_WRNMASK) | (data & BPORT1_AB_IALR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IAUR_maskWrite) {
    bport1_ab_data.IAUR.value = (bport1_ab_data.IAUR.value & BPORT1_AB_IAUR_WRNMASK) | (data & BPORT1_AB_IAUR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIBC_maskWrite) {
    bport1_ab_data.MIBC.value = (bport1_ab_data.MIBC.value & BPORT1_AB_MIBC_WRNMASK) | (data & BPORT1_AB_MIBC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MMFR_maskWrite) {
    bport1_ab_data.MMFR.value = (bport1_ab_data.MMFR.value & BPORT1_AB_MMFR_WRNMASK) | (data & BPORT1_AB_MMFR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MRBR_maskWrite) {
    bport1_ab_data.MRBR.value = (bport1_ab_data.MRBR.value & BPORT1_AB_MRBR_WRNMASK) | (data & BPORT1_AB_MRBR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MSCR_maskWrite) {
    bport1_ab_data.MSCR.value = (bport1_ab_data.MSCR.value & BPORT1_AB_MSCR_WRNMASK) | (data & BPORT1_AB_MSCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OPD_maskWrite) {
    bport1_ab_data.OPD.value = (bport1_ab_data.OPD.value & BPORT1_AB_OPD_WRNMASK) | (data & BPORT1_AB_OPD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PALR_maskWrite) {
    bport1_ab_data.PALR.value = (bport1_ab_data.PALR.value & BPORT1_AB_PALR_WRNMASK) | (data & BPORT1_AB_PALR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PAUR_maskWrite) {
    bport1_ab_data.PAUR.value = (bport1_ab_data.PAUR.value & BPORT1_AB_PAUR_WRNMASK) | (data & BPORT1_AB_PAUR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RACC_maskWrite) {
    bport1_ab_data.RACC.value = (bport1_ab_data.RACC.value & BPORT1_AB_RACC_WRNMASK) | (data & BPORT1_AB_RACC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RAEM_maskWrite) {
    bport1_ab_data.RAEM.value = (bport1_ab_data.RAEM.value & BPORT1_AB_RAEM_WRNMASK) | (data & BPORT1_AB_RAEM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RAFL_maskWrite) {
    bport1_ab_data.RAFL.value = (bport1_ab_data.RAFL.value & BPORT1_AB_RAFL_WRNMASK) | (data & BPORT1_AB_RAFL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCR_maskWrite) {
    bport1_ab_data.RCR.value = (bport1_ab_data.RCR.value & BPORT1_AB_RCR_WRNMASK) | (data & BPORT1_AB_RCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RDAR_maskWrite) {
    bport1_ab_data.RDAR.value = (bport1_ab_data.RDAR.value & BPORT1_AB_RDAR_WRNMASK) | (data & BPORT1_AB_RDAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RDSR_maskWrite) {
    bport1_ab_data.RDSR.value = (bport1_ab_data.RDSR.value & BPORT1_AB_RDSR_WRNMASK) | (data & BPORT1_AB_RDSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RSEM_maskWrite) {
    bport1_ab_data.RSEM.value = (bport1_ab_data.RSEM.value & BPORT1_AB_RSEM_WRNMASK) | (data & BPORT1_AB_RSEM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RSFL_maskWrite) {
    bport1_ab_data.RSFL.value = (bport1_ab_data.RSFL.value & BPORT1_AB_RSFL_WRNMASK) | (data & BPORT1_AB_RSFL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TACC_maskWrite) {
    bport1_ab_data.TACC.value = (bport1_ab_data.TACC.value & BPORT1_AB_TACC_WRNMASK) | (data & BPORT1_AB_TACC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAEM_maskWrite) {
    bport1_ab_data.TAEM.value = (bport1_ab_data.TAEM.value & BPORT1_AB_TAEM_WRNMASK) | (data & BPORT1_AB_TAEM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAFL_maskWrite) {
    bport1_ab_data.TAFL.value = (bport1_ab_data.TAFL.value & BPORT1_AB_TAFL_WRNMASK) | (data & BPORT1_AB_TAFL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCCR0_maskWrite) {
    bport1_ab_data.TCCR0.value = (bport1_ab_data.TCCR0.value & BPORT1_AB_TCCR0_WRNMASK) | (data & BPORT1_AB_TCCR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCCR1_maskWrite) {
    bport1_ab_data.TCCR1.value = (bport1_ab_data.TCCR1.value & BPORT1_AB_TCCR1_WRNMASK) | (data & BPORT1_AB_TCCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCCR2_maskWrite) {
    bport1_ab_data.TCCR2.value = (bport1_ab_data.TCCR2.value & BPORT1_AB_TCCR2_WRNMASK) | (data & BPORT1_AB_TCCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCCR3_maskWrite) {
    bport1_ab_data.TCCR3.value = (bport1_ab_data.TCCR3.value & BPORT1_AB_TCCR3_WRNMASK) | (data & BPORT1_AB_TCCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & BPORT1_AB_TCR_WRNMASK) | (data & BPORT1_AB_TCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCSR0_maskWrite) {
    bport1_ab_data.TCSR0.value = (bport1_ab_data.TCSR0.value & BPORT1_AB_TCSR0_WRNMASK) | (data & BPORT1_AB_TCSR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCSR1_maskWrite) {
    bport1_ab_data.TCSR1.value = (bport1_ab_data.TCSR1.value & BPORT1_AB_TCSR1_WRNMASK) | (data & BPORT1_AB_TCSR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCSR2_maskWrite) {
    bport1_ab_data.TCSR2.value = (bport1_ab_data.TCSR2.value & BPORT1_AB_TCSR2_WRNMASK) | (data & BPORT1_AB_TCSR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCSR3_maskWrite) {
    bport1_ab_data.TCSR3.value = (bport1_ab_data.TCSR3.value & BPORT1_AB_TCSR3_WRNMASK) | (data & BPORT1_AB_TCSR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TDAR_maskWrite) {
    bport1_ab_data.TDAR.value = (bport1_ab_data.TDAR.value & BPORT1_AB_TDAR_WRNMASK) | (data & BPORT1_AB_TDAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TDSR_maskWrite) {
    bport1_ab_data.TDSR.value = (bport1_ab_data.TDSR.value & BPORT1_AB_TDSR_WRNMASK) | (data & BPORT1_AB_TDSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TFWR_maskWrite) {
    bport1_ab_data.TFWR.value = (bport1_ab_data.TFWR.value & BPORT1_AB_TFWR_WRNMASK) | (data & BPORT1_AB_TFWR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TGSR_maskWrite) {
    bport1_ab_data.TGSR.value = (bport1_ab_data.TGSR.value & BPORT1_AB_TGSR_WRNMASK) | (data & BPORT1_AB_TGSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIPG_maskWrite) {
    bport1_ab_data.TIPG.value = (bport1_ab_data.TIPG.value & BPORT1_AB_TIPG_WRNMASK) | (data & BPORT1_AB_TIPG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TSEM_maskWrite) {
    bport1_ab_data.TSEM.value = (bport1_ab_data.TSEM.value & BPORT1_AB_TSEM_WRNMASK) | (data & BPORT1_AB_TSEM_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abEIR_reg = ppmCreateRegister(
            "ab_EIR",
            "Interrupt Event Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_EIR_maskWrite,
            view32,
            &(bport1_ab_data.EIR.value),
            True
        );

        ppmCreateRegisterField(abEIR_reg, "BABR", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "BABT", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "EBERR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "GRA", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "LC", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "MII", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "PLR", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "RL", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "RXB", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "RXF", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "TS_AVAIL", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "TS_TIMER", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "TXB", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "TXF", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "UN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abEIR_reg, "WAKEUP", 0, 17, 1, 1, 1);
    }
    {
        registerHandle abEIMR_reg = ppmCreateRegister(
            "ab_EIMR",
            "Interrupt Mask Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_EIMR_maskWrite,
            view32,
            &(bport1_ab_data.EIMR.value),
            True
        );

        ppmCreateRegisterField(abEIMR_reg, "BABR", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "BABT", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "EBERR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "GRA", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "LC", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "MII", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "PLR", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "RL", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "RXB", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "RXF", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "TS_AVAIL", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "TS_TIMER", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "TXB", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "TXF", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "UN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abEIMR_reg, "WAKEUP", 0, 17, 1, 1, 1);
    }
    {
        registerHandle abRDAR_reg = ppmCreateRegister(
            "ab_RDAR",
            "Receive Descriptor Active Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_RDAR_maskWrite,
            view32,
            &(bport1_ab_data.RDAR.value),
            True
        );

        ppmCreateRegisterField(abRDAR_reg, "RDAR", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abTDAR_reg = ppmCreateRegister(
            "ab_TDAR",
            "Transmit Descriptor Active Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_TDAR_maskWrite,
            view32,
            &(bport1_ab_data.TDAR.value),
            True
        );

        ppmCreateRegisterField(abTDAR_reg, "TDAR", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abECR_reg = ppmCreateRegister(
            "ab_ECR",
            "Ethernet Control Register, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_ECR_maskWrite,
            view32,
            &(bport1_ab_data.ECR.value),
            True
        );

        ppmCreateRegisterField(abECR_reg, "DBGEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "DBSWP", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "EN1588", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "ETHEREN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "MAGICEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "RESET", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "SLEEP", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abECR_reg, "STOPEN", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abMMFR_reg = ppmCreateRegister(
            "ab_MMFR",
            "MII Management Frame Register, offset: 0x40 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_MMFR_maskWrite,
            view32,
            &(bport1_ab_data.MMFR.value),
            True
        );

        ppmCreateRegisterField(abMMFR_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abMMFR_reg, "OP", 0, 28, 2, 1, 1);
        ppmCreateRegisterField(abMMFR_reg, "PA", 0, 23, 5, 1, 1);
        ppmCreateRegisterField(abMMFR_reg, "RA", 0, 18, 5, 1, 1);
        ppmCreateRegisterField(abMMFR_reg, "ST", 0, 30, 2, 1, 1);
        ppmCreateRegisterField(abMMFR_reg, "TA", 0, 16, 2, 1, 1);
    }
    {
        registerHandle abMSCR_reg = ppmCreateRegister(
            "ab_MSCR",
            "MII Speed Control Register, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_MSCR_maskWrite,
            view32,
            &(bport1_ab_data.MSCR.value),
            True
        );

        ppmCreateRegisterField(abMSCR_reg, "DIS_PRE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abMSCR_reg, "HOLDTIME", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abMSCR_reg, "MII_SPEED", 0, 1, 6, 1, 1);
    }
    {
        registerHandle abMIBC_reg = ppmCreateRegister(
            "ab_MIBC",
            "MIB Control Register, offset: 0x64 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            bport1_ab_MIBC_maskWrite,
            view32,
            &(bport1_ab_data.MIBC.value),
            True
        );

        ppmCreateRegisterField(abMIBC_reg, "MIB_CLEAR", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abMIBC_reg, "MIB_DIS", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abMIBC_reg, "MIB_IDLE", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abRCR_reg = ppmCreateRegister(
            "ab_RCR",
            "Receive Control Register, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            read_32,
            bport1_ab_RCR_maskWrite,
            view32,
            &(bport1_ab_data.RCR.value),
            True
        );

        ppmCreateRegisterField(abRCR_reg, "BC_REJ", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "CFEN", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "CRCFWD", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "DRT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "FCE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "GRS", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "LOOP", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "MAX_FL", 0, 16, 14, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "MII_MODE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "NLC", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "PADEN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "PAUFWD", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "PROM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "RMII_10T", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abRCR_reg, "RMII_MODE", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abTCR_reg = ppmCreateRegister(
            "ab_TCR",
            "Transmit Control Register, offset: 0xC4 ",
            handles.bport1,
            0xc4,
            4,
            read_32,
            bport1_ab_TCR_maskWrite,
            view32,
            &(bport1_ab_data.TCR.value),
            True
        );

        ppmCreateRegisterField(abTCR_reg, "ADDINS", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "ADDSEL", 0, 5, 3, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "CRCFWD", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "FDEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "GTS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "RFC_PAUSE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "TFC_PAUSE", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abPALR_reg = ppmCreateRegister(
            "ab_PALR",
            "Physical Address Lower Register, offset: 0xE4 ",
            handles.bport1,
            0xe4,
            4,
            read_32,
            bport1_ab_PALR_maskWrite,
            view32,
            &(bport1_ab_data.PALR.value),
            True
        );

        ppmCreateRegisterField(abPALR_reg, "PADDR1", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abPAUR_reg = ppmCreateRegister(
            "ab_PAUR",
            "Physical Address Upper Register, offset: 0xE8 ",
            handles.bport1,
            0xe8,
            4,
            read_32,
            bport1_ab_PAUR_maskWrite,
            view32,
            &(bport1_ab_data.PAUR.value),
            True
        );

        ppmCreateRegisterField(abPAUR_reg, "PADDR2", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abPAUR_reg, "TYPE", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abOPD_reg = ppmCreateRegister(
            "ab_OPD",
            "Opcode/Pause Duration Register, offset: 0xEC ",
            handles.bport1,
            0xec,
            4,
            read_32,
            bport1_ab_OPD_maskWrite,
            view32,
            &(bport1_ab_data.OPD.value),
            True
        );

        ppmCreateRegisterField(abOPD_reg, "OPCODE", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abOPD_reg, "PAUSE_DUR", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abIAUR_reg = ppmCreateRegister(
            "ab_IAUR",
            "Descriptor Individual Upper Address Register, offset: 0x118 ",
            handles.bport1,
            0x118,
            4,
            read_32,
            bport1_ab_IAUR_maskWrite,
            view32,
            &(bport1_ab_data.IAUR.value),
            True
        );

        ppmCreateRegisterField(abIAUR_reg, "IADDR1", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abIALR_reg = ppmCreateRegister(
            "ab_IALR",
            "Descriptor Individual Lower Address Register, offset: 0x11C ",
            handles.bport1,
            0x11c,
            4,
            read_32,
            bport1_ab_IALR_maskWrite,
            view32,
            &(bport1_ab_data.IALR.value),
            True
        );

        ppmCreateRegisterField(abIALR_reg, "IADDR2", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abGAUR_reg = ppmCreateRegister(
            "ab_GAUR",
            "Descriptor Group Upper Address Register, offset: 0x120 ",
            handles.bport1,
            0x120,
            4,
            read_32,
            bport1_ab_GAUR_maskWrite,
            view32,
            &(bport1_ab_data.GAUR.value),
            True
        );

        ppmCreateRegisterField(abGAUR_reg, "GADDR1", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abGALR_reg = ppmCreateRegister(
            "ab_GALR",
            "Descriptor Group Lower Address Register, offset: 0x124 ",
            handles.bport1,
            0x124,
            4,
            read_32,
            bport1_ab_GALR_maskWrite,
            view32,
            &(bport1_ab_data.GALR.value),
            True
        );

        ppmCreateRegisterField(abGALR_reg, "GADDR2", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTFWR_reg = ppmCreateRegister(
            "ab_TFWR",
            "Transmit FIFO Watermark Register, offset: 0x144 ",
            handles.bport1,
            0x144,
            4,
            read_32,
            bport1_ab_TFWR_maskWrite,
            view32,
            &(bport1_ab_data.TFWR.value),
            True
        );

        ppmCreateRegisterField(abTFWR_reg, "STRFWD", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abTFWR_reg, "TFWR", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abRDSR_reg = ppmCreateRegister(
            "ab_RDSR",
            "Receive Descriptor Ring Start Register, offset: 0x180 ",
            handles.bport1,
            0x180,
            4,
            read_32,
            bport1_ab_RDSR_maskWrite,
            view32,
            &(bport1_ab_data.RDSR.value),
            True
        );

        ppmCreateRegisterField(abRDSR_reg, "R_DES_START", 0, 3, 29, 1, 1);
    }
    {
        registerHandle abTDSR_reg = ppmCreateRegister(
            "ab_TDSR",
            "Transmit Buffer Descriptor Ring Start Register, offset: 0x184 ",
            handles.bport1,
            0x184,
            4,
            read_32,
            bport1_ab_TDSR_maskWrite,
            view32,
            &(bport1_ab_data.TDSR.value),
            True
        );

        ppmCreateRegisterField(abTDSR_reg, "X_DES_START", 0, 3, 29, 1, 1);
    }
    {
        registerHandle abMRBR_reg = ppmCreateRegister(
            "ab_MRBR",
            "Maximum Receive Buffer Size Register, offset: 0x188 ",
            handles.bport1,
            0x188,
            4,
            read_32,
            bport1_ab_MRBR_maskWrite,
            view32,
            &(bport1_ab_data.MRBR.value),
            True
        );

        ppmCreateRegisterField(abMRBR_reg, "R_BUF_SIZE", 0, 4, 10, 1, 1);
    }
    {
        registerHandle abRSFL_reg = ppmCreateRegister(
            "ab_RSFL",
            "Receive FIFO Section Full Threshold, offset: 0x190 ",
            handles.bport1,
            0x190,
            4,
            read_32,
            bport1_ab_RSFL_maskWrite,
            view32,
            &(bport1_ab_data.RSFL.value),
            True
        );

        ppmCreateRegisterField(abRSFL_reg, "RX_SECTION_FULL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRSEM_reg = ppmCreateRegister(
            "ab_RSEM",
            "Receive FIFO Section Empty Threshold, offset: 0x194 ",
            handles.bport1,
            0x194,
            4,
            read_32,
            bport1_ab_RSEM_maskWrite,
            view32,
            &(bport1_ab_data.RSEM.value),
            True
        );

        ppmCreateRegisterField(abRSEM_reg, "RX_SECTION_EMPTY", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRAEM_reg = ppmCreateRegister(
            "ab_RAEM",
            "Receive FIFO Almost Empty Threshold, offset: 0x198 ",
            handles.bport1,
            0x198,
            4,
            read_32,
            bport1_ab_RAEM_maskWrite,
            view32,
            &(bport1_ab_data.RAEM.value),
            True
        );

        ppmCreateRegisterField(abRAEM_reg, "RX_ALMOST_EMPTY", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRAFL_reg = ppmCreateRegister(
            "ab_RAFL",
            "Receive FIFO Almost Full Threshold, offset: 0x19C ",
            handles.bport1,
            0x19c,
            4,
            read_32,
            bport1_ab_RAFL_maskWrite,
            view32,
            &(bport1_ab_data.RAFL.value),
            True
        );

        ppmCreateRegisterField(abRAFL_reg, "RX_ALMOST_FULL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTSEM_reg = ppmCreateRegister(
            "ab_TSEM",
            "Transmit FIFO Section Empty Threshold, offset: 0x1A0 ",
            handles.bport1,
            0x1a0,
            4,
            read_32,
            bport1_ab_TSEM_maskWrite,
            view32,
            &(bport1_ab_data.TSEM.value),
            True
        );

        ppmCreateRegisterField(abTSEM_reg, "TX_SECTION_EMPTY", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTAEM_reg = ppmCreateRegister(
            "ab_TAEM",
            "Transmit FIFO Almost Empty Threshold, offset: 0x1A4 ",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            bport1_ab_TAEM_maskWrite,
            view32,
            &(bport1_ab_data.TAEM.value),
            True
        );

        ppmCreateRegisterField(abTAEM_reg, "TX_ALMOST_EMPTY", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTAFL_reg = ppmCreateRegister(
            "ab_TAFL",
            "Transmit FIFO Almost Full Threshold, offset: 0x1A8 ",
            handles.bport1,
            0x1a8,
            4,
            read_32,
            bport1_ab_TAFL_maskWrite,
            view32,
            &(bport1_ab_data.TAFL.value),
            True
        );

        ppmCreateRegisterField(abTAFL_reg, "TX_ALMOST_FULL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTIPG_reg = ppmCreateRegister(
            "ab_TIPG",
            "Transmit Inter-Packet Gap, offset: 0x1AC ",
            handles.bport1,
            0x1ac,
            4,
            read_32,
            bport1_ab_TIPG_maskWrite,
            view32,
            &(bport1_ab_data.TIPG.value),
            True
        );

        ppmCreateRegisterField(abTIPG_reg, "IPG", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abFTRL_reg = ppmCreateRegister(
            "ab_FTRL",
            "Frame Truncation Length, offset: 0x1B0 ",
            handles.bport1,
            0x1b0,
            4,
            read_32,
            bport1_ab_FTRL_maskWrite,
            view32,
            &(bport1_ab_data.FTRL.value),
            True
        );

        ppmCreateRegisterField(abFTRL_reg, "TRUNC_FL", 0, 0, 14, 1, 1);
    }
    {
        registerHandle abTACC_reg = ppmCreateRegister(
            "ab_TACC",
            "Transmit Accelerator Function Configuration, offset: 0x1C0 ",
            handles.bport1,
            0x1c0,
            4,
            read_32,
            bport1_ab_TACC_maskWrite,
            view32,
            &(bport1_ab_data.TACC.value),
            True
        );

        ppmCreateRegisterField(abTACC_reg, "IPCHK", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTACC_reg, "PROCHK", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTACC_reg, "SHIFT16", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abRACC_reg = ppmCreateRegister(
            "ab_RACC",
            "Receive Accelerator Function Configuration, offset: 0x1C4 ",
            handles.bport1,
            0x1c4,
            4,
            read_32,
            bport1_ab_RACC_maskWrite,
            view32,
            &(bport1_ab_data.RACC.value),
            True
        );

        ppmCreateRegisterField(abRACC_reg, "IPDIS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abRACC_reg, "LINEDIS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abRACC_reg, "PADREM", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abRACC_reg, "PRODIS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abRACC_reg, "SHIFT16", 0, 7, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_DROP",
            "Count of frames not counted correctly (RMON_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x200 ",
            handles.bport1,
            0x200,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_DROP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_PACKETS",
            "RMON Tx packet count (RMON_T_PACKETS), offset: 0x204 ",
            handles.bport1,
            0x204,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_PACKETS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_BC_PKT",
            "RMON Tx Broadcast Packets (RMON_T_BC_PKT), offset: 0x208 ",
            handles.bport1,
            0x208,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_BC_PKT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_MC_PKT",
            "RMON Tx Multicast Packets (RMON_T_MC_PKT), offset: 0x20C ",
            handles.bport1,
            0x20c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_MC_PKT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_CRC_ALIGN",
            "RMON Tx Packets w CRC/Align error (RMON_T_CRC_ALIGN), offset: 0x210 ",
            handles.bport1,
            0x210,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_CRC_ALIGN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_UNDERSIZE",
            "RMON Tx Packets < 64 bytes, good CRC (RMON_T_UNDERSIZE), offset: 0x214 ",
            handles.bport1,
            0x214,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_UNDERSIZE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_OVERSIZE",
            "RMON Tx Packets > MAX_FL bytes, good CRC (RMON_T_OVERSIZE), offset: 0x218 ",
            handles.bport1,
            0x218,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_OVERSIZE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_FRAG",
            "RMON Tx Packets < 64 bytes, bad CRC (RMON_T_FRAG), offset: 0x21C ",
            handles.bport1,
            0x21c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_FRAG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_JAB",
            "RMON Tx Packets > MAX_FL bytes, bad CRC (RMON_T_JAB), offset: 0x220 ",
            handles.bport1,
            0x220,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_JAB.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_COL",
            "RMON Tx collision count (RMON_T_COL), offset: 0x224 ",
            handles.bport1,
            0x224,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_COL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P64",
            "RMON Tx 64 byte packets (RMON_T_P64), offset: 0x228 ",
            handles.bport1,
            0x228,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P64.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P65TO127",
            "RMON Tx 65 to 127 byte packets (RMON_T_P65TO127), offset: 0x22C ",
            handles.bport1,
            0x22c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P65TO127.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P128TO255",
            "RMON Tx 128 to 255 byte packets (RMON_T_P128TO255), offset: 0x230 ",
            handles.bport1,
            0x230,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P128TO255.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P256TO511",
            "RMON Tx 256 to 511 byte packets (RMON_T_P256TO511), offset: 0x234 ",
            handles.bport1,
            0x234,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P256TO511.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P512TO1023",
            "RMON Tx 512 to 1023 byte packets (RMON_T_P512TO1023), offset: 0x238 ",
            handles.bport1,
            0x238,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P512TO1023.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P1024TO2047",
            "RMON Tx 1024 to 2047 byte packets (RMON_T_P1024TO2047), offset: 0x23C ",
            handles.bport1,
            0x23c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P1024TO2047.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_P_GTE2048",
            "RMON Tx packets w > 2048 bytes (RMON_T_P_GTE2048), offset: 0x240 ",
            handles.bport1,
            0x240,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_P_GTE2048.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_T_OCTETS",
            "RMON Tx Octets (RMON_T_OCTETS), offset: 0x244 ",
            handles.bport1,
            0x244,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_T_OCTETS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_DROP",
            "Count of frames not counted correctly (IEEE_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x248 ",
            handles.bport1,
            0x248,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_DROP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_FRAME_OK",
            "Frames Transmitted OK (IEEE_T_FRAME_OK), offset: 0x24C ",
            handles.bport1,
            0x24c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_FRAME_OK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_1COL",
            "Frames Transmitted with Single Collision (IEEE_T_1COL), offset: 0x250 ",
            handles.bport1,
            0x250,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_1COL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_MCOL",
            "Frames Transmitted with Multiple Collisions (IEEE_T_MCOL), offset: 0x254 ",
            handles.bport1,
            0x254,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_MCOL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_DEF",
            "Frames Transmitted after Deferral Delay (IEEE_T_DEF), offset: 0x258 ",
            handles.bport1,
            0x258,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_DEF.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_LCOL",
            "Frames Transmitted with Late Collision (IEEE_T_LCOL), offset: 0x25C ",
            handles.bport1,
            0x25c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_LCOL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_EXCOL",
            "Frames Transmitted with Excessive Collisions (IEEE_T_EXCOL), offset: 0x260 ",
            handles.bport1,
            0x260,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_EXCOL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_MACERR",
            "Frames Transmitted with Tx FIFO Underrun (IEEE_T_MACERR), offset: 0x264 ",
            handles.bport1,
            0x264,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_MACERR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_CSERR",
            "Frames Transmitted with Carrier Sense Error (IEEE_T_CSERR), offset: 0x268 ",
            handles.bport1,
            0x268,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_CSERR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_SQE",
            "Frames Transmitted with SQE Error (IEEE_T_SQE). NOTE: Counter not implemented (read 0 always) as no SQE information is available., offset: 0x26C ",
            handles.bport1,
            0x26c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_SQE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_FDXFC",
            "Flow Control Pause frames transmitted (IEEE_T_FDXFC), offset: 0x270 ",
            handles.bport1,
            0x270,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_FDXFC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_T_OCTETS_OK",
            "Octet count for Frames Transmitted w/o Error (IEEE_T_OCTETS_OK). NOTE: Counts total octets (includes header and FCS fields)., offset: 0x274 ",
            handles.bport1,
            0x274,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_T_OCTETS_OK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_PACKETS",
            "RMON Rx packet count (RMON_R_PACKETS), offset: 0x284 ",
            handles.bport1,
            0x284,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_PACKETS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_BC_PKT",
            "RMON Rx Broadcast Packets (RMON_R_BC_PKT), offset: 0x288 ",
            handles.bport1,
            0x288,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_BC_PKT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_MC_PKT",
            "RMON Rx Multicast Packets (RMON_R_MC_PKT), offset: 0x28C ",
            handles.bport1,
            0x28c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_MC_PKT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_CRC_ALIGN",
            "RMON Rx Packets w CRC/Align error (RMON_R_CRC_ALIGN), offset: 0x290 ",
            handles.bport1,
            0x290,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_CRC_ALIGN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_UNDERSIZE",
            "RMON Rx Packets < 64 bytes, good CRC (RMON_R_UNDERSIZE), offset: 0x294 ",
            handles.bport1,
            0x294,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_UNDERSIZE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_OVERSIZE",
            "RMON Rx Packets > MAX_FL bytes, good CRC (RMON_R_OVERSIZE), offset: 0x298 ",
            handles.bport1,
            0x298,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_OVERSIZE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_FRAG",
            "RMON Rx Packets < 64 bytes, bad CRC (RMON_R_FRAG), offset: 0x29C ",
            handles.bport1,
            0x29c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_FRAG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_JAB",
            "RMON Rx Packets > MAX_FL bytes, bad CRC (RMON_R_JAB), offset: 0x2A0 ",
            handles.bport1,
            0x2a0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_JAB.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_RESVD_0",
            "Reserved (RMON_R_RESVD_0), offset: 0x2A4 ",
            handles.bport1,
            0x2a4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_RESVD_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P64",
            "RMON Rx 64 byte packets (RMON_R_P64), offset: 0x2A8 ",
            handles.bport1,
            0x2a8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P64.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P65TO127",
            "RMON Rx 65 to 127 byte packets (RMON_R_P65TO127), offset: 0x2AC ",
            handles.bport1,
            0x2ac,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P65TO127.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P128TO255",
            "RMON Rx 128 to 255 byte packets (RMON_R_P128TO255), offset: 0x2B0 ",
            handles.bport1,
            0x2b0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P128TO255.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P256TO511",
            "RMON Rx 256 to 511 byte packets (RMON_R_P256TO511), offset: 0x2B4 ",
            handles.bport1,
            0x2b4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P256TO511.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P512TO1023",
            "RMON Rx 512 to 1023 byte packets (RMON_R_P512TO1023), offset: 0x2B8 ",
            handles.bport1,
            0x2b8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P512TO1023.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P1024TO2047",
            "RMON Rx 1024 to 2047 byte packets (RMON_R_P1024TO2047), offset: 0x2BC ",
            handles.bport1,
            0x2bc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P1024TO2047.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_P_GTE2048",
            "RMON Rx packets w > 2048 bytes (RMON_R_P_GTE2048), offset: 0x2C0 ",
            handles.bport1,
            0x2c0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_P_GTE2048.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_OCTETS",
            "RMON Rx Octets (RMON_R_OCTETS), offset: 0x2C4 ",
            handles.bport1,
            0x2c4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_OCTETS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_DROP",
            "Count of frames not counted correctly (IEEE_R_DROP). NOTE: Counter increments if a frame with valid/missing SFD character is detected and has been dropped. None of the other counters increments if this counter increments., offset: 0x2C8 ",
            handles.bport1,
            0x2c8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_DROP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RMON_R_FRAME_OK",
            "Frames Received OK (IEEE_R_FRAME_OK), offset: 0x2CC ",
            handles.bport1,
            0x2cc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RMON_R_FRAME_OK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_R_CRC",
            "Frames Received with CRC Error (IEEE_R_CRC), offset: 0x2D0 ",
            handles.bport1,
            0x2d0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_R_CRC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_R_ALIGN",
            "Frames Received with Alignment Error (IEEE_R_ALIGN), offset: 0x2D4 ",
            handles.bport1,
            0x2d4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_R_ALIGN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_R_MACERR",
            "Receive Fifo Overflow count (IEEE_R_MACERR), offset: 0x2D8 ",
            handles.bport1,
            0x2d8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_R_MACERR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_R_FDXFC",
            "Flow Control Pause frames received (IEEE_R_FDXFC), offset: 0x2DC ",
            handles.bport1,
            0x2dc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_R_FDXFC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IEEE_R_OCTETS_OK",
            "Octet count for Frames Rcvd w/o Error (IEEE_R_OCTETS_OK). Counts total octets (includes header and FCS fields)., offset: 0x2E0 ",
            handles.bport1,
            0x2e0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IEEE_R_OCTETS_OK.value),
            True
        );
    }
    {
        registerHandle abATCR_reg = ppmCreateRegister(
            "ab_ATCR",
            "Timer Control Register, offset: 0x400 ",
            handles.bport1,
            0x400,
            4,
            read_32,
            bport1_ab_ATCR_maskWrite,
            view32,
            &(bport1_ab_data.ATCR.value),
            True
        );

        ppmCreateRegisterField(abATCR_reg, "CAPTURE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "EN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "OFFEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "OFFRST", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "PEREN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "PINPER", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "RESTART", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abATCR_reg, "SLAVE", 0, 13, 1, 1, 1);
    }
    {
        registerHandle abATVR_reg = ppmCreateRegister(
            "ab_ATVR",
            "Timer Value Register, offset: 0x404 ",
            handles.bport1,
            0x404,
            4,
            read_32,
            bport1_ab_ATVR_maskWrite,
            view32,
            &(bport1_ab_data.ATVR.value),
            True
        );

        ppmCreateRegisterField(abATVR_reg, "ATIME", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abATOFF_reg = ppmCreateRegister(
            "ab_ATOFF",
            "Timer Offset Register, offset: 0x408 ",
            handles.bport1,
            0x408,
            4,
            read_32,
            bport1_ab_ATOFF_maskWrite,
            view32,
            &(bport1_ab_data.ATOFF.value),
            True
        );

        ppmCreateRegisterField(abATOFF_reg, "OFFSET", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abATPER_reg = ppmCreateRegister(
            "ab_ATPER",
            "Timer Period Register, offset: 0x40C ",
            handles.bport1,
            0x40c,
            4,
            read_32,
            bport1_ab_ATPER_maskWrite,
            view32,
            &(bport1_ab_data.ATPER.value),
            True
        );

        ppmCreateRegisterField(abATPER_reg, "PERIOD", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abATCOR_reg = ppmCreateRegister(
            "ab_ATCOR",
            "Timer Correction Register, offset: 0x410 ",
            handles.bport1,
            0x410,
            4,
            read_32,
            bport1_ab_ATCOR_maskWrite,
            view32,
            &(bport1_ab_data.ATCOR.value),
            True
        );

        ppmCreateRegisterField(abATCOR_reg, "COR", 0, 0, 31, 1, 1);
    }
    {
        registerHandle abATINC_reg = ppmCreateRegister(
            "ab_ATINC",
            "Time-Stamping Clock Period Register, offset: 0x414 ",
            handles.bport1,
            0x414,
            4,
            read_32,
            bport1_ab_ATINC_maskWrite,
            view32,
            &(bport1_ab_data.ATINC.value),
            True
        );

        ppmCreateRegisterField(abATINC_reg, "INC", 0, 0, 7, 1, 1);
        ppmCreateRegisterField(abATINC_reg, "INC_CORR", 0, 8, 7, 1, 1);
    }
    {
        registerHandle abATSTMP_reg = ppmCreateRegister(
            "ab_ATSTMP",
            "Timestamp of Last Transmitted Frame, offset: 0x418 ",
            handles.bport1,
            0x418,
            4,
            read_32,
            bport1_ab_ATSTMP_maskWrite,
            view32,
            &(bport1_ab_data.ATSTMP.value),
            True
        );

        ppmCreateRegisterField(abATSTMP_reg, "TIMESTAMP", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTGSR_reg = ppmCreateRegister(
            "ab_TGSR",
            "Timer Global Status Register, offset: 0x604 ",
            handles.bport1,
            0x604,
            4,
            read_32,
            bport1_ab_TGSR_maskWrite,
            view32,
            &(bport1_ab_data.TGSR.value),
            True
        );

        ppmCreateRegisterField(abTGSR_reg, "TF0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTGSR_reg, "TF1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abTGSR_reg, "TF2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTGSR_reg, "TF3", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abTCSR0_reg = ppmCreateRegister(
            "ab_TCSR0",
            "Timer Control Status Register, array offset: 0x608, array step: 0x8 ",
            handles.bport1,
            0x608,
            4,
            read_32,
            bport1_ab_TCSR0_maskWrite,
            view32,
            &(bport1_ab_data.TCSR0.value),
            True
        );

        ppmCreateRegisterField(abTCSR0_reg, "TDRE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "TF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "TIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "TMODE", 0, 2, 4, 1, 1);
    }
    {
        registerHandle abTCCR0_reg = ppmCreateRegister(
            "ab_TCCR0",
            "Timer Compare Capture Register, array offset: 0x60C, array step: 0x8 ",
            handles.bport1,
            0x60c,
            4,
            read_32,
            bport1_ab_TCCR0_maskWrite,
            view32,
            &(bport1_ab_data.TCCR0.value),
            True
        );

        ppmCreateRegisterField(abTCCR0_reg, "TCC", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTCSR1_reg = ppmCreateRegister(
            "ab_TCSR1",
            "Timer Control Status Register, array offset: 0x610, array step: 0x8 ",
            handles.bport1,
            0x610,
            4,
            read_32,
            bport1_ab_TCSR1_maskWrite,
            view32,
            &(bport1_ab_data.TCSR1.value),
            True
        );

        ppmCreateRegisterField(abTCSR1_reg, "TDRE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "TF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "TIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "TMODE", 0, 2, 4, 1, 1);
    }
    {
        registerHandle abTCCR1_reg = ppmCreateRegister(
            "ab_TCCR1",
            "Timer Compare Capture Register, array offset: 0x614, array step: 0x8 ",
            handles.bport1,
            0x614,
            4,
            read_32,
            bport1_ab_TCCR1_maskWrite,
            view32,
            &(bport1_ab_data.TCCR1.value),
            True
        );

        ppmCreateRegisterField(abTCCR1_reg, "TCC", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTCSR2_reg = ppmCreateRegister(
            "ab_TCSR2",
            "Timer Control Status Register, array offset: 0x618, array step: 0x8 ",
            handles.bport1,
            0x618,
            4,
            read_32,
            bport1_ab_TCSR2_maskWrite,
            view32,
            &(bport1_ab_data.TCSR2.value),
            True
        );

        ppmCreateRegisterField(abTCSR2_reg, "TDRE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR2_reg, "TF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abTCSR2_reg, "TIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abTCSR2_reg, "TMODE", 0, 2, 4, 1, 1);
    }
    {
        registerHandle abTCCR2_reg = ppmCreateRegister(
            "ab_TCCR2",
            "Timer Compare Capture Register, array offset: 0x61c, array step: 0x8 ",
            handles.bport1,
            0x61c,
            4,
            read_32,
            bport1_ab_TCCR2_maskWrite,
            view32,
            &(bport1_ab_data.TCCR2.value),
            True
        );

        ppmCreateRegisterField(abTCCR2_reg, "TCC", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTCSR3_reg = ppmCreateRegister(
            "ab_TCSR3",
            "Timer Control Status Register, array offset: 0x620, array step: 0x8 ",
            handles.bport1,
            0x620,
            4,
            read_32,
            bport1_ab_TCSR3_maskWrite,
            view32,
            &(bport1_ab_data.TCSR3.value),
            True
        );

        ppmCreateRegisterField(abTCSR3_reg, "TDRE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR3_reg, "TF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abTCSR3_reg, "TIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abTCSR3_reg, "TMODE", 0, 2, 4, 1, 1);
    }
    {
        registerHandle abTCCR3_reg = ppmCreateRegister(
            "ab_TCCR3",
            "Timer Compare Capture Register, array offset: 0x624, array step: 0x8 ",
            handles.bport1,
            0x624,
            4,
            read_32,
            bport1_ab_TCCR3_maskWrite,
            view32,
            &(bport1_ab_data.TCCR3.value),
            True
        );

        ppmCreateRegisterField(abTCCR3_reg, "TCC", 0, 0, 32, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.TCCR3.value = (Uns32)(bport1_ab_data.TCCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCSR3.value = (Uns32)(bport1_ab_data.TCSR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCCR2.value = (Uns32)(bport1_ab_data.TCCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCSR2.value = (Uns32)(bport1_ab_data.TCSR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCCR1.value = (Uns32)(bport1_ab_data.TCCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCSR1.value = (Uns32)(bport1_ab_data.TCSR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCCR0.value = (Uns32)(bport1_ab_data.TCCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCSR0.value = (Uns32)(bport1_ab_data.TCSR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TGSR.value = (Uns32)(bport1_ab_data.TGSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ATSTMP.value = (Uns32)(bport1_ab_data.ATSTMP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ATINC.value = (Uns32)(bport1_ab_data.ATINC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ATCOR.value = (Uns32)(bport1_ab_data.ATCOR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ATPER.value = (Uns32)(bport1_ab_data.ATPER.value & ~(0xffffffff)) | ((0xffffffff) & (0x3b9aca00));
        bport1_ab_data.ATOFF.value = (Uns32)(bport1_ab_data.ATOFF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ATVR.value = (Uns32)(bport1_ab_data.ATVR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ATCR.value = (Uns32)(bport1_ab_data.ATCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IEEE_R_OCTETS_OK.value = (Uns32)(bport1_ab_data.IEEE_R_OCTETS_OK.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_R_FDXFC.value = (Uns32)(bport1_ab_data.IEEE_R_FDXFC.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_R_MACERR.value = (Uns32)(bport1_ab_data.IEEE_R_MACERR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_R_ALIGN.value = (Uns32)(bport1_ab_data.IEEE_R_ALIGN.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_R_CRC.value = (Uns32)(bport1_ab_data.IEEE_R_CRC.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_FRAME_OK.value = (Uns32)(bport1_ab_data.RMON_R_FRAME_OK.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_DROP.value = (Uns32)(bport1_ab_data.RMON_R_DROP.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_OCTETS.value = (Uns32)(bport1_ab_data.RMON_R_OCTETS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P_GTE2048.value = (Uns32)(bport1_ab_data.RMON_R_P_GTE2048.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P1024TO2047.value = (Uns32)(bport1_ab_data.RMON_R_P1024TO2047.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P512TO1023.value = (Uns32)(bport1_ab_data.RMON_R_P512TO1023.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P256TO511.value = (Uns32)(bport1_ab_data.RMON_R_P256TO511.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P128TO255.value = (Uns32)(bport1_ab_data.RMON_R_P128TO255.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P65TO127.value = (Uns32)(bport1_ab_data.RMON_R_P65TO127.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_P64.value = (Uns32)(bport1_ab_data.RMON_R_P64.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_RESVD_0.value = (Uns32)(bport1_ab_data.RMON_R_RESVD_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_JAB.value = (Uns32)(bport1_ab_data.RMON_R_JAB.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_FRAG.value = (Uns32)(bport1_ab_data.RMON_R_FRAG.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_OVERSIZE.value = (Uns32)(bport1_ab_data.RMON_R_OVERSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_UNDERSIZE.value = (Uns32)(bport1_ab_data.RMON_R_UNDERSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_CRC_ALIGN.value = (Uns32)(bport1_ab_data.RMON_R_CRC_ALIGN.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_MC_PKT.value = (Uns32)(bport1_ab_data.RMON_R_MC_PKT.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_BC_PKT.value = (Uns32)(bport1_ab_data.RMON_R_BC_PKT.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_R_PACKETS.value = (Uns32)(bport1_ab_data.RMON_R_PACKETS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_OCTETS_OK.value = (Uns32)(bport1_ab_data.IEEE_T_OCTETS_OK.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_FDXFC.value = (Uns32)(bport1_ab_data.IEEE_T_FDXFC.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_SQE.value = (Uns32)(bport1_ab_data.IEEE_T_SQE.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_CSERR.value = (Uns32)(bport1_ab_data.IEEE_T_CSERR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_MACERR.value = (Uns32)(bport1_ab_data.IEEE_T_MACERR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_EXCOL.value = (Uns32)(bport1_ab_data.IEEE_T_EXCOL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_LCOL.value = (Uns32)(bport1_ab_data.IEEE_T_LCOL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_DEF.value = (Uns32)(bport1_ab_data.IEEE_T_DEF.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_MCOL.value = (Uns32)(bport1_ab_data.IEEE_T_MCOL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_1COL.value = (Uns32)(bport1_ab_data.IEEE_T_1COL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_FRAME_OK.value = (Uns32)(bport1_ab_data.IEEE_T_FRAME_OK.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IEEE_T_DROP.value = (Uns32)(bport1_ab_data.IEEE_T_DROP.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_OCTETS.value = (Uns32)(bport1_ab_data.RMON_T_OCTETS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P_GTE2048.value = (Uns32)(bport1_ab_data.RMON_T_P_GTE2048.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P1024TO2047.value = (Uns32)(bport1_ab_data.RMON_T_P1024TO2047.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P512TO1023.value = (Uns32)(bport1_ab_data.RMON_T_P512TO1023.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P256TO511.value = (Uns32)(bport1_ab_data.RMON_T_P256TO511.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P128TO255.value = (Uns32)(bport1_ab_data.RMON_T_P128TO255.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P65TO127.value = (Uns32)(bport1_ab_data.RMON_T_P65TO127.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_P64.value = (Uns32)(bport1_ab_data.RMON_T_P64.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_COL.value = (Uns32)(bport1_ab_data.RMON_T_COL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_JAB.value = (Uns32)(bport1_ab_data.RMON_T_JAB.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_FRAG.value = (Uns32)(bport1_ab_data.RMON_T_FRAG.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_OVERSIZE.value = (Uns32)(bport1_ab_data.RMON_T_OVERSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_UNDERSIZE.value = (Uns32)(bport1_ab_data.RMON_T_UNDERSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_CRC_ALIGN.value = (Uns32)(bport1_ab_data.RMON_T_CRC_ALIGN.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_MC_PKT.value = (Uns32)(bport1_ab_data.RMON_T_MC_PKT.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_BC_PKT.value = (Uns32)(bport1_ab_data.RMON_T_BC_PKT.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_PACKETS.value = (Uns32)(bport1_ab_data.RMON_T_PACKETS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RMON_T_DROP.value = (Uns32)(bport1_ab_data.RMON_T_DROP.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.RACC.value = (Uns32)(bport1_ab_data.RACC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TACC.value = (Uns32)(bport1_ab_data.TACC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FTRL.value = (Uns32)(bport1_ab_data.FTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x000007ff));
        bport1_ab_data.TIPG.value = (Uns32)(bport1_ab_data.TIPG.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000000c));
        bport1_ab_data.TAFL.value = (Uns32)(bport1_ab_data.TAFL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000008));
        bport1_ab_data.TAEM.value = (Uns32)(bport1_ab_data.TAEM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.TSEM.value = (Uns32)(bport1_ab_data.TSEM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RAFL.value = (Uns32)(bport1_ab_data.RAFL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.RAEM.value = (Uns32)(bport1_ab_data.RAEM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.RSEM.value = (Uns32)(bport1_ab_data.RSEM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RSFL.value = (Uns32)(bport1_ab_data.RSFL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MRBR.value = (Uns32)(bport1_ab_data.MRBR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TDSR.value = (Uns32)(bport1_ab_data.TDSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RDSR.value = (Uns32)(bport1_ab_data.RDSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TFWR.value = (Uns32)(bport1_ab_data.TFWR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GALR.value = (Uns32)(bport1_ab_data.GALR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GAUR.value = (Uns32)(bport1_ab_data.GAUR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IALR.value = (Uns32)(bport1_ab_data.IALR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IAUR.value = (Uns32)(bport1_ab_data.IAUR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OPD.value = (Uns32)(bport1_ab_data.OPD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
        bport1_ab_data.PAUR.value = (Uns32)(bport1_ab_data.PAUR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00008808));
        bport1_ab_data.PALR.value = (Uns32)(bport1_ab_data.PALR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR.value = (Uns32)(bport1_ab_data.TCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCR.value = (Uns32)(bport1_ab_data.RCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0fee0001));
        bport1_ab_data.MIBC.value = (Uns32)(bport1_ab_data.MIBC.value & ~(0xffffffff)) | ((0xffffffff) & (0xc0000000));
        bport1_ab_data.MSCR.value = (Uns32)(bport1_ab_data.MSCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMFR.value = (Uns32)(bport1_ab_data.MMFR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ECR.value = (Uns32)(bport1_ab_data.ECR.value & ~(0xffffffff)) | ((0xffffffff) & (0xf0000000));
        bport1_ab_data.TDAR.value = (Uns32)(bport1_ab_data.TDAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RDAR.value = (Uns32)(bport1_ab_data.RDAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EIMR.value = (Uns32)(bport1_ab_data.EIMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EIR.value = (Uns32)(bport1_ab_data.EIR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the ENET peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

