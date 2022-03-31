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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisADC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CFG1_maskWrite) {
    bport1_ab_data.CFG1.value = (bport1_ab_data.CFG1.value & BPORT1_AB_CFG1_WRNMASK) | (data & BPORT1_AB_CFG1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CFG2_maskWrite) {
    bport1_ab_data.CFG2.value = (bport1_ab_data.CFG2.value & BPORT1_AB_CFG2_WRNMASK) | (data & BPORT1_AB_CFG2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLM0_maskWrite) {
    bport1_ab_data.CLM0.value = (bport1_ab_data.CLM0.value & BPORT1_AB_CLM0_WRNMASK) | (data & BPORT1_AB_CLM0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLM1_maskWrite) {
    bport1_ab_data.CLM1.value = (bport1_ab_data.CLM1.value & BPORT1_AB_CLM1_WRNMASK) | (data & BPORT1_AB_CLM1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLM2_maskWrite) {
    bport1_ab_data.CLM2.value = (bport1_ab_data.CLM2.value & BPORT1_AB_CLM2_WRNMASK) | (data & BPORT1_AB_CLM2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLM3_maskWrite) {
    bport1_ab_data.CLM3.value = (bport1_ab_data.CLM3.value & BPORT1_AB_CLM3_WRNMASK) | (data & BPORT1_AB_CLM3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLM4_maskWrite) {
    bport1_ab_data.CLM4.value = (bport1_ab_data.CLM4.value & BPORT1_AB_CLM4_WRNMASK) | (data & BPORT1_AB_CLM4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLMD_maskWrite) {
    bport1_ab_data.CLMD.value = (bport1_ab_data.CLMD.value & BPORT1_AB_CLMD_WRNMASK) | (data & BPORT1_AB_CLMD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLMS_maskWrite) {
    bport1_ab_data.CLMS.value = (bport1_ab_data.CLMS.value & BPORT1_AB_CLMS_WRNMASK) | (data & BPORT1_AB_CLMS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLP0_maskWrite) {
    bport1_ab_data.CLP0.value = (bport1_ab_data.CLP0.value & BPORT1_AB_CLP0_WRNMASK) | (data & BPORT1_AB_CLP0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLP1_maskWrite) {
    bport1_ab_data.CLP1.value = (bport1_ab_data.CLP1.value & BPORT1_AB_CLP1_WRNMASK) | (data & BPORT1_AB_CLP1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLP2_maskWrite) {
    bport1_ab_data.CLP2.value = (bport1_ab_data.CLP2.value & BPORT1_AB_CLP2_WRNMASK) | (data & BPORT1_AB_CLP2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLP3_maskWrite) {
    bport1_ab_data.CLP3.value = (bport1_ab_data.CLP3.value & BPORT1_AB_CLP3_WRNMASK) | (data & BPORT1_AB_CLP3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLP4_maskWrite) {
    bport1_ab_data.CLP4.value = (bport1_ab_data.CLP4.value & BPORT1_AB_CLP4_WRNMASK) | (data & BPORT1_AB_CLP4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLPD_maskWrite) {
    bport1_ab_data.CLPD.value = (bport1_ab_data.CLPD.value & BPORT1_AB_CLPD_WRNMASK) | (data & BPORT1_AB_CLPD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLPS_maskWrite) {
    bport1_ab_data.CLPS.value = (bport1_ab_data.CLPS.value & BPORT1_AB_CLPS_WRNMASK) | (data & BPORT1_AB_CLPS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CV1_maskWrite) {
    bport1_ab_data.CV1.value = (bport1_ab_data.CV1.value & BPORT1_AB_CV1_WRNMASK) | (data & BPORT1_AB_CV1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CV2_maskWrite) {
    bport1_ab_data.CV2.value = (bport1_ab_data.CV2.value & BPORT1_AB_CV2_WRNMASK) | (data & BPORT1_AB_CV2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MG_maskWrite) {
    bport1_ab_data.MG.value = (bport1_ab_data.MG.value & BPORT1_AB_MG_WRNMASK) | (data & BPORT1_AB_MG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OFS_maskWrite) {
    bport1_ab_data.OFS.value = (bport1_ab_data.OFS.value & BPORT1_AB_OFS_WRNMASK) | (data & BPORT1_AB_OFS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PGA_maskWrite) {
    bport1_ab_data.PGA.value = (bport1_ab_data.PGA.value & BPORT1_AB_PGA_WRNMASK) | (data & BPORT1_AB_PGA_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PG_maskWrite) {
    bport1_ab_data.PG.value = (bport1_ab_data.PG.value & BPORT1_AB_PG_WRNMASK) | (data & BPORT1_AB_PG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SC1A_maskWrite) {
    bport1_ab_data.SC1A.value = (bport1_ab_data.SC1A.value & BPORT1_AB_SC1A_WRNMASK) | (data & BPORT1_AB_SC1A_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SC1B_maskWrite) {
    bport1_ab_data.SC1B.value = (bport1_ab_data.SC1B.value & BPORT1_AB_SC1B_WRNMASK) | (data & BPORT1_AB_SC1B_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SC2_maskWrite) {
    bport1_ab_data.SC2.value = (bport1_ab_data.SC2.value & BPORT1_AB_SC2_WRNMASK) | (data & BPORT1_AB_SC2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SC3_maskWrite) {
    bport1_ab_data.SC3.value = (bport1_ab_data.SC3.value & BPORT1_AB_SC3_WRNMASK) | (data & BPORT1_AB_SC3_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSC1A_reg = ppmCreateRegister(
            "ab_SC1A",
            "ADC status and control registers 1, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_SC1A_maskWrite,
            view32,
            &(bport1_ab_data.SC1A.value),
            True
        );

        ppmCreateRegisterField(abSC1A_reg, "ADCH", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abSC1A_reg, "AIEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSC1A_reg, "COCO", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC1A_reg, "DIFF", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abSC1B_reg = ppmCreateRegister(
            "ab_SC1B",
            "ADC status and control registers 1, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_SC1B_maskWrite,
            view32,
            &(bport1_ab_data.SC1B.value),
            True
        );

        ppmCreateRegisterField(abSC1B_reg, "ADCH", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abSC1B_reg, "AIEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSC1B_reg, "COCO", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC1B_reg, "DIFF", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abCFG1_reg = ppmCreateRegister(
            "ab_CFG1",
            "ADC configuration register 1, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_CFG1_maskWrite,
            view32,
            &(bport1_ab_data.CFG1.value),
            True
        );

        ppmCreateRegisterField(abCFG1_reg, "ADICLK", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCFG1_reg, "ADIV", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abCFG1_reg, "ADLPC", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCFG1_reg, "ADLSMP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCFG1_reg, "MODE", 0, 2, 2, 1, 1);
    }
    {
        registerHandle abCFG2_reg = ppmCreateRegister(
            "ab_CFG2",
            "Configuration register 2, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_CFG2_maskWrite,
            view32,
            &(bport1_ab_data.CFG2.value),
            True
        );

        ppmCreateRegisterField(abCFG2_reg, "ADACKEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCFG2_reg, "ADHSC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCFG2_reg, "ADLSTS", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCFG2_reg, "MUXSEL", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abRA_reg = ppmCreateRegister(
            "ab_RA",
            "ADC data result register, array offset: 0x10, array step: 0x4 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RA.value),
            True
        );

        ppmCreateRegisterField(abRA_reg, "D", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abRB_reg = ppmCreateRegister(
            "ab_RB",
            "ADC data result register, array offset: 0x10, array step: 0x4 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RB.value),
            True
        );

        ppmCreateRegisterField(abRB_reg, "D", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCV1_reg = ppmCreateRegister(
            "ab_CV1",
            "Compare value registers, offset: 0x18 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_CV1_maskWrite,
            view32,
            &(bport1_ab_data.CV1.value),
            True
        );

        ppmCreateRegisterField(abCV1_reg, "CV", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCV2_reg = ppmCreateRegister(
            "ab_CV2",
            "Compare value registers, offset: 0x1C ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_CV2_maskWrite,
            view32,
            &(bport1_ab_data.CV2.value),
            True
        );

        ppmCreateRegisterField(abCV2_reg, "CV", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abSC2_reg = ppmCreateRegister(
            "ab_SC2",
            "Status and control register 2, offset: 0x20 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_SC2_maskWrite,
            view32,
            &(bport1_ab_data.SC2.value),
            True
        );

        ppmCreateRegisterField(abSC2_reg, "ACFE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSC2_reg, "ACFGT", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSC2_reg, "ACREN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSC2_reg, "ADACT", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC2_reg, "ADTRG", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSC2_reg, "DMAEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSC2_reg, "REFSEL", 0, 0, 2, 1, 1);
    }
    {
        registerHandle abSC3_reg = ppmCreateRegister(
            "ab_SC3",
            "Status and control register 3, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_SC3_maskWrite,
            view32,
            &(bport1_ab_data.SC3.value),
            True
        );

        ppmCreateRegisterField(abSC3_reg, "ADCO", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSC3_reg, "AVGE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSC3_reg, "AVGS", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abSC3_reg, "CAL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC3_reg, "CALF", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abOFS_reg = ppmCreateRegister(
            "ab_OFS",
            "ADC offset correction register, offset: 0x28 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_OFS_maskWrite,
            view32,
            &(bport1_ab_data.OFS.value),
            True
        );

        ppmCreateRegisterField(abOFS_reg, "OFS", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPG_reg = ppmCreateRegister(
            "ab_PG",
            "ADC plus-side gain register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_PG_maskWrite,
            view32,
            &(bport1_ab_data.PG.value),
            True
        );

        ppmCreateRegisterField(abPG_reg, "PG", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abMG_reg = ppmCreateRegister(
            "ab_MG",
            "ADC minus-side gain register, offset: 0x30 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_MG_maskWrite,
            view32,
            &(bport1_ab_data.MG.value),
            True
        );

        ppmCreateRegisterField(abMG_reg, "MG", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCLPD_reg = ppmCreateRegister(
            "ab_CLPD",
            "ADC plus-side general calibration value register, offset: 0x34 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_CLPD_maskWrite,
            view32,
            &(bport1_ab_data.CLPD.value),
            True
        );

        ppmCreateRegisterField(abCLPD_reg, "CLPD", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abCLPS_reg = ppmCreateRegister(
            "ab_CLPS",
            "ADC plus-side general calibration value register, offset: 0x38 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_CLPS_maskWrite,
            view32,
            &(bport1_ab_data.CLPS.value),
            True
        );

        ppmCreateRegisterField(abCLPS_reg, "CLPS", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abCLP4_reg = ppmCreateRegister(
            "ab_CLP4",
            "ADC plus-side general calibration value register, offset: 0x3C ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_CLP4_maskWrite,
            view32,
            &(bport1_ab_data.CLP4.value),
            True
        );

        ppmCreateRegisterField(abCLP4_reg, "CLP4", 0, 0, 10, 1, 1);
    }
    {
        registerHandle abCLP3_reg = ppmCreateRegister(
            "ab_CLP3",
            "ADC plus-side general calibration value register, offset: 0x40 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_CLP3_maskWrite,
            view32,
            &(bport1_ab_data.CLP3.value),
            True
        );

        ppmCreateRegisterField(abCLP3_reg, "CLP3", 0, 0, 9, 1, 1);
    }
    {
        registerHandle abCLP2_reg = ppmCreateRegister(
            "ab_CLP2",
            "ADC plus-side general calibration value register, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_CLP2_maskWrite,
            view32,
            &(bport1_ab_data.CLP2.value),
            True
        );

        ppmCreateRegisterField(abCLP2_reg, "CLP2", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCLP1_reg = ppmCreateRegister(
            "ab_CLP1",
            "ADC plus-side general calibration value register, offset: 0x48 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_CLP1_maskWrite,
            view32,
            &(bport1_ab_data.CLP1.value),
            True
        );

        ppmCreateRegisterField(abCLP1_reg, "CLP1", 0, 0, 7, 1, 1);
    }
    {
        registerHandle abCLP0_reg = ppmCreateRegister(
            "ab_CLP0",
            "ADC plus-side general calibration value register, offset: 0x4C ",
            handles.bport1,
            0x4c,
            4,
            read_32,
            bport1_ab_CLP0_maskWrite,
            view32,
            &(bport1_ab_data.CLP0.value),
            True
        );

        ppmCreateRegisterField(abCLP0_reg, "CLP0", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abPGA_reg = ppmCreateRegister(
            "ab_PGA",
            "ADC PGA register, offset: 0x50 ",
            handles.bport1,
            0x50,
            4,
            read_32,
            bport1_ab_PGA_maskWrite,
            view32,
            &(bport1_ab_data.PGA.value),
            True
        );

        ppmCreateRegisterField(abPGA_reg, "PGACHPb", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPGA_reg, "PGAEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abPGA_reg, "PGAG", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPGA_reg, "PGALPb", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPGA_reg, "PGAOFSM", 0, 14, 1, 1, 1);
    }
    {
        registerHandle abCLMD_reg = ppmCreateRegister(
            "ab_CLMD",
            "ADC minus-side general calibration value register, offset: 0x54 ",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_CLMD_maskWrite,
            view32,
            &(bport1_ab_data.CLMD.value),
            True
        );

        ppmCreateRegisterField(abCLMD_reg, "CLMD", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abCLMS_reg = ppmCreateRegister(
            "ab_CLMS",
            "ADC minus-side general calibration value register, offset: 0x58 ",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_CLMS_maskWrite,
            view32,
            &(bport1_ab_data.CLMS.value),
            True
        );

        ppmCreateRegisterField(abCLMS_reg, "CLMS", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abCLM4_reg = ppmCreateRegister(
            "ab_CLM4",
            "ADC minus-side general calibration value register, offset: 0x5C ",
            handles.bport1,
            0x5c,
            4,
            read_32,
            bport1_ab_CLM4_maskWrite,
            view32,
            &(bport1_ab_data.CLM4.value),
            True
        );

        ppmCreateRegisterField(abCLM4_reg, "CLM4", 0, 0, 10, 1, 1);
    }
    {
        registerHandle abCLM3_reg = ppmCreateRegister(
            "ab_CLM3",
            "ADC minus-side general calibration value register, offset: 0x60 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_CLM3_maskWrite,
            view32,
            &(bport1_ab_data.CLM3.value),
            True
        );

        ppmCreateRegisterField(abCLM3_reg, "CLM3", 0, 0, 9, 1, 1);
    }
    {
        registerHandle abCLM2_reg = ppmCreateRegister(
            "ab_CLM2",
            "ADC minus-side general calibration value register, offset: 0x64 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            bport1_ab_CLM2_maskWrite,
            view32,
            &(bport1_ab_data.CLM2.value),
            True
        );

        ppmCreateRegisterField(abCLM2_reg, "CLM2", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCLM1_reg = ppmCreateRegister(
            "ab_CLM1",
            "ADC minus-side general calibration value register, offset: 0x68 ",
            handles.bport1,
            0x68,
            4,
            read_32,
            bport1_ab_CLM1_maskWrite,
            view32,
            &(bport1_ab_data.CLM1.value),
            True
        );

        ppmCreateRegisterField(abCLM1_reg, "CLM1", 0, 0, 7, 1, 1);
    }
    {
        registerHandle abCLM0_reg = ppmCreateRegister(
            "ab_CLM0",
            "ADC minus-side general calibration value register, offset: 0x6C ",
            handles.bport1,
            0x6c,
            4,
            read_32,
            bport1_ab_CLM0_maskWrite,
            view32,
            &(bport1_ab_data.CLM0.value),
            True
        );

        ppmCreateRegisterField(abCLM0_reg, "CLM0", 0, 0, 6, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CLM0.value = (Uns32)(bport1_ab_data.CLM0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0020));
        bport1_ab_data.CLM1.value = (Uns32)(bport1_ab_data.CLM1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0040));
        bport1_ab_data.CLM2.value = (Uns32)(bport1_ab_data.CLM2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0080));
        bport1_ab_data.CLM3.value = (Uns32)(bport1_ab_data.CLM3.value & ~(0xffffffff)) | ((0xffffffff) & (0x0100));
        bport1_ab_data.CLM4.value = (Uns32)(bport1_ab_data.CLM4.value & ~(0xffffffff)) | ((0xffffffff) & (0x0200));
        bport1_ab_data.CLMS.value = (Uns32)(bport1_ab_data.CLMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0020));
        bport1_ab_data.CLMD.value = (Uns32)(bport1_ab_data.CLMD.value & ~(0xffffffff)) | ((0xffffffff) & (0x000a));
        bport1_ab_data.PGA.value = (Uns32)(bport1_ab_data.PGA.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.CLP0.value = (Uns32)(bport1_ab_data.CLP0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0020));
        bport1_ab_data.CLP1.value = (Uns32)(bport1_ab_data.CLP1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0040));
        bport1_ab_data.CLP2.value = (Uns32)(bport1_ab_data.CLP2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0080));
        bport1_ab_data.CLP3.value = (Uns32)(bport1_ab_data.CLP3.value & ~(0xffffffff)) | ((0xffffffff) & (0x0100));
        bport1_ab_data.CLP4.value = (Uns32)(bport1_ab_data.CLP4.value & ~(0xffffffff)) | ((0xffffffff) & (0x0200));
        bport1_ab_data.CLPS.value = (Uns32)(bport1_ab_data.CLPS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0020));
        bport1_ab_data.CLPD.value = (Uns32)(bport1_ab_data.CLPD.value & ~(0xffffffff)) | ((0xffffffff) & (0x000a));
        bport1_ab_data.MG.value = (Uns32)(bport1_ab_data.MG.value & ~(0xffffffff)) | ((0xffffffff) & (0x8200));
        bport1_ab_data.PG.value = (Uns32)(bport1_ab_data.PG.value & ~(0xffffffff)) | ((0xffffffff) & (0x8200));
        bport1_ab_data.OFS.value = (Uns32)(bport1_ab_data.OFS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0004));
        bport1_ab_data.SC3.value = (Uns32)(bport1_ab_data.SC3.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.SC2.value = (Uns32)(bport1_ab_data.SC2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.CV2.value = (Uns32)(bport1_ab_data.CV2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.CV1.value = (Uns32)(bport1_ab_data.CV1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.RB.value = (Uns32)(bport1_ab_data.RB.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.RA.value = (Uns32)(bport1_ab_data.RA.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.CFG2.value = (Uns32)(bport1_ab_data.CFG2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.CFG1.value = (Uns32)(bport1_ab_data.CFG1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000));
        bport1_ab_data.SC1B.value = (Uns32)(bport1_ab_data.SC1B.value & ~(0xffffffff)) | ((0xffffffff) & (0x001f));
        bport1_ab_data.SC1A.value = (Uns32)(bport1_ab_data.SC1A.value & ~(0xffffffff)) | ((0xffffffff) & (0x001f));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the ADC peripheral used on the Freescale Kinetis platform");
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

