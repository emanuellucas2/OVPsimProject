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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridLCD", "Example");
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

static PPM_WRITE_CB(bport1_ab_ENFPR0_maskWrite) {
    bport1_ab_data.ENFPR0.value = (bport1_ab_data.ENFPR0.value & BPORT1_AB_ENFPR0_WRNMASK) | (data & BPORT1_AB_ENFPR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENFPR1_maskWrite) {
    bport1_ab_data.ENFPR1.value = (bport1_ab_data.ENFPR1.value & BPORT1_AB_ENFPR1_WRNMASK) | (data & BPORT1_AB_ENFPR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDCCR_maskWrite) {
    bport1_ab_data.LCDCCR.value = (bport1_ab_data.LCDCCR.value & BPORT1_AB_LCDCCR_WRNMASK) | (data & BPORT1_AB_LCDCCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDCR_maskWrite) {
    bport1_ab_data.LCDCR.value = (bport1_ab_data.LCDCR.value & BPORT1_AB_LCDCR_WRNMASK) | (data & BPORT1_AB_LCDCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDPCR_maskWrite) {
    bport1_ab_data.LCDPCR.value = (bport1_ab_data.LCDPCR.value & BPORT1_AB_LCDPCR_WRNMASK) | (data & BPORT1_AB_LCDPCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM0_maskWrite) {
    bport1_ab_data.LCDRAM0.value = (bport1_ab_data.LCDRAM0.value & BPORT1_AB_LCDRAM0_WRNMASK) | (data & BPORT1_AB_LCDRAM0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM10_maskWrite) {
    bport1_ab_data.LCDRAM10.value = (bport1_ab_data.LCDRAM10.value & BPORT1_AB_LCDRAM10_WRNMASK) | (data & BPORT1_AB_LCDRAM10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM11_maskWrite) {
    bport1_ab_data.LCDRAM11.value = (bport1_ab_data.LCDRAM11.value & BPORT1_AB_LCDRAM11_WRNMASK) | (data & BPORT1_AB_LCDRAM11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM12_maskWrite) {
    bport1_ab_data.LCDRAM12.value = (bport1_ab_data.LCDRAM12.value & BPORT1_AB_LCDRAM12_WRNMASK) | (data & BPORT1_AB_LCDRAM12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM13_maskWrite) {
    bport1_ab_data.LCDRAM13.value = (bport1_ab_data.LCDRAM13.value & BPORT1_AB_LCDRAM13_WRNMASK) | (data & BPORT1_AB_LCDRAM13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM14_maskWrite) {
    bport1_ab_data.LCDRAM14.value = (bport1_ab_data.LCDRAM14.value & BPORT1_AB_LCDRAM14_WRNMASK) | (data & BPORT1_AB_LCDRAM14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM15_maskWrite) {
    bport1_ab_data.LCDRAM15.value = (bport1_ab_data.LCDRAM15.value & BPORT1_AB_LCDRAM15_WRNMASK) | (data & BPORT1_AB_LCDRAM15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM1_maskWrite) {
    bport1_ab_data.LCDRAM1.value = (bport1_ab_data.LCDRAM1.value & BPORT1_AB_LCDRAM1_WRNMASK) | (data & BPORT1_AB_LCDRAM1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM2_maskWrite) {
    bport1_ab_data.LCDRAM2.value = (bport1_ab_data.LCDRAM2.value & BPORT1_AB_LCDRAM2_WRNMASK) | (data & BPORT1_AB_LCDRAM2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM3_maskWrite) {
    bport1_ab_data.LCDRAM3.value = (bport1_ab_data.LCDRAM3.value & BPORT1_AB_LCDRAM3_WRNMASK) | (data & BPORT1_AB_LCDRAM3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM4_maskWrite) {
    bport1_ab_data.LCDRAM4.value = (bport1_ab_data.LCDRAM4.value & BPORT1_AB_LCDRAM4_WRNMASK) | (data & BPORT1_AB_LCDRAM4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM5_maskWrite) {
    bport1_ab_data.LCDRAM5.value = (bport1_ab_data.LCDRAM5.value & BPORT1_AB_LCDRAM5_WRNMASK) | (data & BPORT1_AB_LCDRAM5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM6_maskWrite) {
    bport1_ab_data.LCDRAM6.value = (bport1_ab_data.LCDRAM6.value & BPORT1_AB_LCDRAM6_WRNMASK) | (data & BPORT1_AB_LCDRAM6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM7_maskWrite) {
    bport1_ab_data.LCDRAM7.value = (bport1_ab_data.LCDRAM7.value & BPORT1_AB_LCDRAM7_WRNMASK) | (data & BPORT1_AB_LCDRAM7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM8_maskWrite) {
    bport1_ab_data.LCDRAM8.value = (bport1_ab_data.LCDRAM8.value & BPORT1_AB_LCDRAM8_WRNMASK) | (data & BPORT1_AB_LCDRAM8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LCDRAM9_maskWrite) {
    bport1_ab_data.LCDRAM9.value = (bport1_ab_data.LCDRAM9.value & BPORT1_AB_LCDRAM9_WRNMASK) | (data & BPORT1_AB_LCDRAM9_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abLCDCR_reg = ppmCreateRegister(
            "ab_LCDCR",
            "LCD Control Register, offset: 0x0",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_LCDCR_maskWrite,
            view32,
            &(bport1_ab_data.LCDCR.value),
            True
        );

        ppmCreateRegisterField(abLCDCR_reg, "BIAS", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "BSTAO", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "BSTEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "BSTSEL", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "DUTY", 0, 26, 3, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "EOF", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDBPA", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDBPS", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDEN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDINT", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDOCS", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDRCS", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "LCDRST", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "NOF", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "PWR", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abLCDCR_reg, "VLCDS", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abLCDPCR_reg = ppmCreateRegister(
            "ab_LCDPCR",
            "LCD Prescaler Control Register, offset: 0x4",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_LCDPCR_maskWrite,
            view32,
            &(bport1_ab_data.LCDPCR.value),
            True
        );

        ppmCreateRegisterField(abLCDPCR_reg, "LCLK", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abLCDCCR_reg = ppmCreateRegister(
            "ab_LCDCCR",
            "LCD Contrast Control Register, offset: 0x8",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_LCDCCR_maskWrite,
            view32,
            &(bport1_ab_data.LCDCCR.value),
            True
        );

        ppmCreateRegisterField(abLCDCCR_reg, "CCEN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abLCDCCR_reg, "LCC", 0, 16, 11, 1, 1);
    }
    {
        registerHandle abENFPR0_reg = ppmCreateRegister(
            "ab_ENFPR0",
            "LCD Frontplane Enable Register 0, offset: 0x10",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_ENFPR0_maskWrite,
            view32,
            &(bport1_ab_data.ENFPR0.value),
            True
        );

        ppmCreateRegisterField(abENFPR0_reg, "ENFP", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abENFPR1_reg = ppmCreateRegister(
            "ab_ENFPR1",
            "LCD Frontplane Enable Register 1, offset: 0x14",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_ENFPR1_maskWrite,
            view32,
            &(bport1_ab_data.ENFPR1.value),
            True
        );

        ppmCreateRegisterField(abENFPR1_reg, "ENFP", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abLCDRAM0_reg = ppmCreateRegister(
            "ab_LCDRAM0",
            "LCDRAM, offset: 0x20",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_LCDRAM0_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM0.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM0_reg, "FP0_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM0_reg, "FP1_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM0_reg, "FP2_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM0_reg, "FP3_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM1_reg = ppmCreateRegister(
            "ab_LCDRAM1",
            "LCDRAM, offset: 0x24",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_LCDRAM1_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM1.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM1_reg, "FP4_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM1_reg, "FP5_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM1_reg, "FP6_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM1_reg, "FP7_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM2_reg = ppmCreateRegister(
            "ab_LCDRAM2",
            "LCDRAM, offset: 0x28",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_LCDRAM2_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM2.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM2_reg, "FP10_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM2_reg, "FP11_BP", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM2_reg, "FP8_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM2_reg, "FP9_BP", 0, 16, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM3_reg = ppmCreateRegister(
            "ab_LCDRAM3",
            "LCDRAM, offset: 0x2C",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_LCDRAM3_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM3.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM3_reg, "FP12_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM3_reg, "FP13_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM3_reg, "FP14_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM3_reg, "FP15_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM4_reg = ppmCreateRegister(
            "ab_LCDRAM4",
            "LCDRAM, offset: 0x30",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_LCDRAM4_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM4.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM4_reg, "FP16_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM4_reg, "FP17_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM4_reg, "FP18_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM4_reg, "FP19_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM5_reg = ppmCreateRegister(
            "ab_LCDRAM5",
            "LCDRAM, offset: 0x34",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_LCDRAM5_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM5.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM5_reg, "FP20_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM5_reg, "FP21_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM5_reg, "FP22_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM5_reg, "FP23_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM6_reg = ppmCreateRegister(
            "ab_LCDRAM6",
            "LCDRAM, offset: 0x38",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_LCDRAM6_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM6.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM6_reg, "FP24_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM6_reg, "FP25_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM6_reg, "FP26_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM6_reg, "FP27_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM7_reg = ppmCreateRegister(
            "ab_LCDRAM7",
            "LCDRAM, offset: 0x3C",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_LCDRAM7_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM7.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM7_reg, "FP28_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM7_reg, "FP29_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM7_reg, "FP30_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM7_reg, "FP31_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM8_reg = ppmCreateRegister(
            "ab_LCDRAM8",
            "LCDRAM, offset: 0x40",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_LCDRAM8_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM8.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM8_reg, "FP32_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM8_reg, "FP33_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM8_reg, "FP34_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM8_reg, "FP35_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM9_reg = ppmCreateRegister(
            "ab_LCDRAM9",
            "LCDRAM, offset: 0x44",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_LCDRAM9_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM9.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM9_reg, "FP36_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM9_reg, "FP37_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM9_reg, "FP38_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM9_reg, "FP39_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM10_reg = ppmCreateRegister(
            "ab_LCDRAM10",
            "LCDRAM, offset: 0x48",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_LCDRAM10_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM10.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM10_reg, "FP40_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM10_reg, "FP41_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM10_reg, "FP42_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM10_reg, "FP43_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM11_reg = ppmCreateRegister(
            "ab_LCDRAM11",
            "LCDRAM, offset: 0x4c",
            handles.bport1,
            0x4c,
            4,
            read_32,
            bport1_ab_LCDRAM11_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM11.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM11_reg, "FP44_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM11_reg, "FP45_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM11_reg, "FP46_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM11_reg, "FP47_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM12_reg = ppmCreateRegister(
            "ab_LCDRAM12",
            "LCDRAM, offset: 0x50",
            handles.bport1,
            0x50,
            4,
            read_32,
            bport1_ab_LCDRAM12_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM12.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM12_reg, "FP48_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM12_reg, "FP49_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM12_reg, "FP50_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM12_reg, "FP51_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM13_reg = ppmCreateRegister(
            "ab_LCDRAM13",
            "LCDRAM, offset: 0x54",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_LCDRAM13_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM13.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM13_reg, "FP52_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM13_reg, "FP53_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM13_reg, "FP54_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM13_reg, "FP55_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM14_reg = ppmCreateRegister(
            "ab_LCDRAM14",
            "LCDRAM, offset: 0x58",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_LCDRAM14_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM14.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM14_reg, "FP56_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM14_reg, "FP57_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM14_reg, "FP58_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM14_reg, "FP59_BP", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLCDRAM15_reg = ppmCreateRegister(
            "ab_LCDRAM15",
            "LCDRAM, offset: 0x5c",
            handles.bport1,
            0x5c,
            4,
            read_32,
            bport1_ab_LCDRAM15_maskWrite,
            view32,
            &(bport1_ab_data.LCDRAM15.value),
            True
        );

        ppmCreateRegisterField(abLCDRAM15_reg, "FP60_BP", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM15_reg, "FP61_BP", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM15_reg, "FP62_BP", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abLCDRAM15_reg, "FP63_BP", 0, 0, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.LCDRAM15.value = (Uns32)(bport1_ab_data.LCDRAM15.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM14.value = (Uns32)(bport1_ab_data.LCDRAM14.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM13.value = (Uns32)(bport1_ab_data.LCDRAM13.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM12.value = (Uns32)(bport1_ab_data.LCDRAM12.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM11.value = (Uns32)(bport1_ab_data.LCDRAM11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM10.value = (Uns32)(bport1_ab_data.LCDRAM10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM9.value = (Uns32)(bport1_ab_data.LCDRAM9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM8.value = (Uns32)(bport1_ab_data.LCDRAM8.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM7.value = (Uns32)(bport1_ab_data.LCDRAM7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM6.value = (Uns32)(bport1_ab_data.LCDRAM6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM5.value = (Uns32)(bport1_ab_data.LCDRAM5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM4.value = (Uns32)(bport1_ab_data.LCDRAM4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM3.value = (Uns32)(bport1_ab_data.LCDRAM3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM2.value = (Uns32)(bport1_ab_data.LCDRAM2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM1.value = (Uns32)(bport1_ab_data.LCDRAM1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDRAM0.value = (Uns32)(bport1_ab_data.LCDRAM0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENFPR1.value = (Uns32)(bport1_ab_data.ENFPR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENFPR0.value = (Uns32)(bport1_ab_data.ENFPR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDCCR.value = (Uns32)(bport1_ab_data.LCDCCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDPCR.value = (Uns32)(bport1_ab_data.LCDPCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCDCR.value = (Uns32)(bport1_ab_data.LCDCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the LCD peripheral used on the Freescale Vybrid platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Vybrid platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Development based on document number: VYBRIDRM Rev. 5, 07/2013");
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

