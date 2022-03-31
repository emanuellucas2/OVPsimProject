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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisSIM", "Example");
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

static PPM_WRITE_CB(bport1_ab_CLKDIV1_maskWrite) {
    bport1_ab_data.CLKDIV1.value = (bport1_ab_data.CLKDIV1.value & BPORT1_AB_CLKDIV1_WRNMASK) | (data & BPORT1_AB_CLKDIV1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLKDIV2_maskWrite) {
    bport1_ab_data.CLKDIV2.value = (bport1_ab_data.CLKDIV2.value & BPORT1_AB_CLKDIV2_WRNMASK) | (data & BPORT1_AB_CLKDIV2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CLKDIV4_maskWrite) {
    bport1_ab_data.CLKDIV4.value = (bport1_ab_data.CLKDIV4.value & BPORT1_AB_CLKDIV4_WRNMASK) | (data & BPORT1_AB_CLKDIV4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCFG1_maskWrite) {
    bport1_ab_data.FCFG1.value = (bport1_ab_data.FCFG1.value & BPORT1_AB_FCFG1_WRNMASK) | (data & BPORT1_AB_FCFG1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & BPORT1_AB_MCR_WRNMASK) | (data & BPORT1_AB_MCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC1_maskWrite) {
    bport1_ab_data.SCGC1.value = (bport1_ab_data.SCGC1.value & BPORT1_AB_SCGC1_WRNMASK) | (data & BPORT1_AB_SCGC1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC2_maskWrite) {
    bport1_ab_data.SCGC2.value = (bport1_ab_data.SCGC2.value & BPORT1_AB_SCGC2_WRNMASK) | (data & BPORT1_AB_SCGC2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC3_maskWrite) {
    bport1_ab_data.SCGC3.value = (bport1_ab_data.SCGC3.value & BPORT1_AB_SCGC3_WRNMASK) | (data & BPORT1_AB_SCGC3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC4_maskWrite) {
    bport1_ab_data.SCGC4.value = (bport1_ab_data.SCGC4.value & BPORT1_AB_SCGC4_WRNMASK) | (data & BPORT1_AB_SCGC4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC5_maskWrite) {
    bport1_ab_data.SCGC5.value = (bport1_ab_data.SCGC5.value & BPORT1_AB_SCGC5_WRNMASK) | (data & BPORT1_AB_SCGC5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC6_maskWrite) {
    bport1_ab_data.SCGC6.value = (bport1_ab_data.SCGC6.value & BPORT1_AB_SCGC6_WRNMASK) | (data & BPORT1_AB_SCGC6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCGC7_maskWrite) {
    bport1_ab_data.SCGC7.value = (bport1_ab_data.SCGC7.value & BPORT1_AB_SCGC7_WRNMASK) | (data & BPORT1_AB_SCGC7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT1CFG_maskWrite) {
    bport1_ab_data.SOPT1CFG.value = (bport1_ab_data.SOPT1CFG.value & BPORT1_AB_SOPT1CFG_WRNMASK) | (data & BPORT1_AB_SOPT1CFG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT1_maskWrite) {
    bport1_ab_data.SOPT1.value = (bport1_ab_data.SOPT1.value & BPORT1_AB_SOPT1_WRNMASK) | (data & BPORT1_AB_SOPT1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT2_maskWrite) {
    bport1_ab_data.SOPT2.value = (bport1_ab_data.SOPT2.value & BPORT1_AB_SOPT2_WRNMASK) | (data & BPORT1_AB_SOPT2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT4_maskWrite) {
    bport1_ab_data.SOPT4.value = (bport1_ab_data.SOPT4.value & BPORT1_AB_SOPT4_WRNMASK) | (data & BPORT1_AB_SOPT4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT5_maskWrite) {
    bport1_ab_data.SOPT5.value = (bport1_ab_data.SOPT5.value & BPORT1_AB_SOPT5_WRNMASK) | (data & BPORT1_AB_SOPT5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT6_maskWrite) {
    bport1_ab_data.SOPT6.value = (bport1_ab_data.SOPT6.value & BPORT1_AB_SOPT6_WRNMASK) | (data & BPORT1_AB_SOPT6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOPT7_maskWrite) {
    bport1_ab_data.SOPT7.value = (bport1_ab_data.SOPT7.value & BPORT1_AB_SOPT7_WRNMASK) | (data & BPORT1_AB_SOPT7_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 8192);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSOPT1_reg = ppmCreateRegister(
            "ab_SOPT1",
            "System Options Register 1, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_SOPT1_maskWrite,
            view32,
            &(bport1_ab_data.SOPT1.value),
            True
        );

        ppmCreateRegisterField(abSOPT1_reg, "OSC32KSEL", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abSOPT1_reg, "USBREGEN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abSOPT1_reg, "USBSSTBY", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abSOPT1_reg, "USBVSTBY", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abSOPT1_reg, "RAMSIZE", 0, 12, 4, 1, 1);
    }
    {
        registerHandle abSOPT1CFG_reg = ppmCreateRegister(
            "ab_SOPT1CFG",
            "SOPT1 Configuration Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_SOPT1CFG_maskWrite,
            view32,
            &(bport1_ab_data.SOPT1CFG.value),
            True
        );

        ppmCreateRegisterField(abSOPT1CFG_reg, "URWE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abSOPT1CFG_reg, "USSWE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abSOPT1CFG_reg, "UVSWE", 0, 25, 1, 1, 1);
    }
    {
        registerHandle abSOPT2_reg = ppmCreateRegister(
            "ab_SOPT2",
            "System Options Register 2, offset: 0x1004 ",
            handles.bport1,
            0x1004,
            4,
            read_32,
            bport1_ab_SOPT2_maskWrite,
            view32,
            &(bport1_ab_data.SOPT2.value),
            True
        );

        ppmCreateRegisterField(abSOPT2_reg, "CLKOUTSEL", 0, 5, 3, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "CMTUARTPAD", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "ESDHCSRC", 0, 28, 2, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "FBSL", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "NFC_CLKSEL", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "NFCSRC", 0, 30, 2, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "PLLFLLSEL", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "RTCCLKOUTSEL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "TIMESRC", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "TRACECLKSEL", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "USBF_CLKSEL", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "USBFSRC", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "USBH_CLKSEL", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSOPT2_reg, "USBHSRC", 0, 2, 2, 1, 1);
    }
    {
        registerHandle abSOPT4_reg = ppmCreateRegister(
            "ab_SOPT4",
            "System Options Register 4, offset: 0x100C ",
            handles.bport1,
            0x100c,
            4,
            read_32,
            bport1_ab_SOPT4_maskWrite,
            view32,
            &(bport1_ab_data.SOPT4.value),
            True
        );

        ppmCreateRegisterField(abSOPT4_reg, "FTM0CLKSEL", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM0FLT0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM0FLT1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM0FLT2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM0FLT3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM0TRG0SRC", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM0TRG1SRC", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM1CH0SRC", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM1CLKSEL", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM1FLT0", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM2CH0SRC", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM2CLKSEL", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM2FLT0", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM3CLKSEL", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM3FLT0", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM3TRG0SRC", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abSOPT4_reg, "FTM3TRG1SRC", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abSOPT5_reg = ppmCreateRegister(
            "ab_SOPT5",
            "System Options Register 5, offset: 0x1010 ",
            handles.bport1,
            0x1010,
            4,
            read_32,
            bport1_ab_SOPT5_maskWrite,
            view32,
            &(bport1_ab_data.SOPT5.value),
            True
        );

        ppmCreateRegisterField(abSOPT5_reg, "UART0RXSRC", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abSOPT5_reg, "UART0TXSRC", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abSOPT5_reg, "UART1RXSRC", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abSOPT5_reg, "UART1TXSRC", 0, 4, 2, 1, 1);
    }
    {
        registerHandle abSOPT6_reg = ppmCreateRegister(
            "ab_SOPT6",
            "System Options Register 6, offset: 0x1014 ",
            handles.bport1,
            0x1014,
            4,
            read_32,
            bport1_ab_SOPT6_maskWrite,
            view32,
            &(bport1_ab_data.SOPT6.value),
            True
        );

        ppmCreateRegisterField(abSOPT6_reg, "MCC", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abSOPT6_reg, "PCR", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abSOPT6_reg, "RSTFLTEN", 0, 29, 3, 1, 1);
        ppmCreateRegisterField(abSOPT6_reg, "RSTFLTSEL", 0, 24, 5, 1, 1);
    }
    {
        registerHandle abSOPT7_reg = ppmCreateRegister(
            "ab_SOPT7",
            "System Options Register 7, offset: 0x1018 ",
            handles.bport1,
            0x1018,
            4,
            read_32,
            bport1_ab_SOPT7_maskWrite,
            view32,
            &(bport1_ab_data.SOPT7.value),
            True
        );

        ppmCreateRegisterField(abSOPT7_reg, "ADC0ALTTRGEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC0PRETRGSEL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC0TRGSEL", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC1ALTTRGEN", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC1PRETRGSEL", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC1TRGSEL", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC2ALTTRGEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC2PRETRGSEL", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC2TRGSEL", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC3ALTTRGEN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC3PRETRGSEL", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abSOPT7_reg, "ADC3TRGSEL", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abSDID_reg = ppmCreateRegister(
            "ab_SDID",
            "System Device Identification Register, offset: 0x1024 ",
            handles.bport1,
            0x1024,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SDID.value),
            True
        );

        ppmCreateRegisterField(abSDID_reg, "PINID", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abSDID_reg, "FAMID", 0, 4, 3, 1, 0);
        ppmCreateRegisterField(abSDID_reg, "REVID", 0, 12, 4, 1, 0);
    }
    {
        registerHandle abSCGC1_reg = ppmCreateRegister(
            "ab_SCGC1",
            "System Clock Gating Control Register 1, offset: 0x1028 ",
            handles.bport1,
            0x1028,
            4,
            read_32,
            bport1_ab_SCGC1_maskWrite,
            view32,
            &(bport1_ab_data.SCGC1.value),
            True
        );

        ppmCreateRegisterField(abSCGC1_reg, "UART4", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSCGC1_reg, "UART5", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSCGC1_reg, "OSC1", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abSCGC2_reg = ppmCreateRegister(
            "ab_SCGC2",
            "System Clock Gating Control Register 2, offset: 0x102C ",
            handles.bport1,
            0x102c,
            4,
            read_32,
            bport1_ab_SCGC2_maskWrite,
            view32,
            &(bport1_ab_data.SCGC2.value),
            True
        );

        ppmCreateRegisterField(abSCGC2_reg, "DAC0", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSCGC2_reg, "DAC1", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abSCGC2_reg, "ENET", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSCGC3_reg = ppmCreateRegister(
            "ab_SCGC3",
            "System Clock Gating Control Register 3, offset: 0x1030 ",
            handles.bport1,
            0x1030,
            4,
            read_32,
            bport1_ab_SCGC3_maskWrite,
            view32,
            &(bport1_ab_data.SCGC3.value),
            True
        );

        ppmCreateRegisterField(abSCGC3_reg, "ADC1", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "ADC3", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "DDR", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "DSPI2", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "ESDHC", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "FLEXCAN1", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "FTM2", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "FTM3", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "NFC", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "RNGA", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSCGC3_reg, "SAI1", 0, 15, 1, 1, 1);
    }
    {
        registerHandle abSCGC4_reg = ppmCreateRegister(
            "ab_SCGC4",
            "System Clock Gating Control Register 4, offset: 0x1034 ",
            handles.bport1,
            0x1034,
            4,
            read_32,
            bport1_ab_SCGC4_maskWrite,
            view32,
            &(bport1_ab_data.SCGC4.value),
            True
        );

        ppmCreateRegisterField(abSCGC4_reg, "CMP", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "CMT", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "EWM", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "IIC1", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "IIC0", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "LLWU", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "MCG", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "OSC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "PMC", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "RCM", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "SMC", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "UART0", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "UART1", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "UART2", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "UART3", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "USBFS", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abSCGC4_reg, "VREF", 0, 20, 1, 1, 1);
    }
    {
        registerHandle abSCGC5_reg = ppmCreateRegister(
            "ab_SCGC5",
            "System Clock Gating Control Register 5, offset: 0x1038 ",
            handles.bport1,
            0x1038,
            4,
            read_32,
            bport1_ab_SCGC5_maskWrite,
            view32,
            &(bport1_ab_data.SCGC5.value),
            True
        );

        ppmCreateRegisterField(abSCGC5_reg, "LPTIMER", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "PORTA", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "PORTB", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "PORTC", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "PORTD", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "PORTE", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "PORTF", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "REGFILE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "TSI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "ATX", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "DRYICE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "DRYICESECREG", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "SIM", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "SIMDGO", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSCGC5_reg, "WDT", 0, 18, 1, 1, 1);
    }
    {
        registerHandle abSCGC6_reg = ppmCreateRegister(
            "ab_SCGC6",
            "System Clock Gating Control Register 6, offset: 0x103C ",
            handles.bport1,
            0x103c,
            4,
            read_32,
            bport1_ab_SCGC6_maskWrite,
            view32,
            &(bport1_ab_data.SCGC6.value),
            True
        );

        ppmCreateRegisterField(abSCGC6_reg, "ADC0", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "ADC2", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "CRC", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "DMAMUX0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "DMAMUX1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "DSPI0", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "DSPI1", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "FLEXCAN0", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "FTM0", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "FTM1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "PDB", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "PIT", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "RTC", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "SAI0", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "USBHS", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "USBDCD", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abSCGC6_reg, "FTF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSCGC7_reg = ppmCreateRegister(
            "ab_SCGC7",
            "System Clock Gating Control Register 7, offset: 0x1040 ",
            handles.bport1,
            0x1040,
            4,
            read_32,
            bport1_ab_SCGC7_maskWrite,
            view32,
            &(bport1_ab_data.SCGC7.value),
            True
        );

        ppmCreateRegisterField(abSCGC7_reg, "FLEXBUS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSCGC7_reg, "DMA", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSCGC7_reg, "MPU", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abCLKDIV1_reg = ppmCreateRegister(
            "ab_CLKDIV1",
            "System Clock Divider Register 1, offset: 0x1044 ",
            handles.bport1,
            0x1044,
            4,
            read_32,
            bport1_ab_CLKDIV1_maskWrite,
            view32,
            &(bport1_ab_data.CLKDIV1.value),
            True
        );

        ppmCreateRegisterField(abCLKDIV1_reg, "OUTDIV1", 0, 28, 4, 1, 1);
        ppmCreateRegisterField(abCLKDIV1_reg, "OUTDIV2", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abCLKDIV1_reg, "OUTDIV3", 0, 20, 4, 1, 1);
        ppmCreateRegisterField(abCLKDIV1_reg, "OUTDIV4", 0, 16, 4, 1, 1);
    }
    {
        registerHandle abCLKDIV2_reg = ppmCreateRegister(
            "ab_CLKDIV2",
            "System Clock Divider Register 2, offset: 0x1048 ",
            handles.bport1,
            0x1048,
            4,
            read_32,
            bport1_ab_CLKDIV2_maskWrite,
            view32,
            &(bport1_ab_data.CLKDIV2.value),
            True
        );

        ppmCreateRegisterField(abCLKDIV2_reg, "USBFSDIV", 0, 1, 3, 1, 1);
        ppmCreateRegisterField(abCLKDIV2_reg, "USBFSFRAC", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCLKDIV2_reg, "USBHSDIV", 0, 9, 3, 1, 1);
        ppmCreateRegisterField(abCLKDIV2_reg, "USBHSFRAC", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abFCFG1_reg = ppmCreateRegister(
            "ab_FCFG1",
            "Flash Configuration Register 1, offset: 0x104C ",
            handles.bport1,
            0x104c,
            4,
            read_32,
            bport1_ab_FCFG1_maskWrite,
            view32,
            &(bport1_ab_data.FCFG1.value),
            True
        );

        ppmCreateRegisterField(abFCFG1_reg, "DEPART", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abFCFG1_reg, "EESIZE", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abFCFG1_reg, "PFSIZE", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abFCFG1_reg, "NVMSIZE", 0, 28, 4, 1, 1);
        ppmCreateRegisterField(abFCFG1_reg, "FTFDIS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abFCFG2_reg = ppmCreateRegister(
            "ab_FCFG2",
            "Flash Configuration Register 2, offset: 0x1050 ",
            handles.bport1,
            0x1050,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.FCFG2.value),
            True
        );

        ppmCreateRegisterField(abFCFG2_reg, "MAXADDR01", 0, 24, 6, 1, 0);
        ppmCreateRegisterField(abFCFG2_reg, "MAXADDR23", 0, 16, 6, 1, 0);
    }
    {
        registerHandle abUIDH_reg = ppmCreateRegister(
            "ab_UIDH",
            "Unique Identification Register High, offset: 0x1054 ",
            handles.bport1,
            0x1054,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.UIDH.value),
            True
        );

        ppmCreateRegisterField(abUIDH_reg, "UID", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abUIDMH_reg = ppmCreateRegister(
            "ab_UIDMH",
            "Unique Identification Register Mid-High, offset: 0x1058 ",
            handles.bport1,
            0x1058,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.UIDMH.value),
            True
        );

        ppmCreateRegisterField(abUIDMH_reg, "UID", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abUIDML_reg = ppmCreateRegister(
            "ab_UIDML",
            "Unique Identification Register Mid Low, offset: 0x105C ",
            handles.bport1,
            0x105c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.UIDML.value),
            True
        );

        ppmCreateRegisterField(abUIDML_reg, "UID", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abUIDL_reg = ppmCreateRegister(
            "ab_UIDL",
            "Unique Identification Register Low, offset: 0x1060 ",
            handles.bport1,
            0x1060,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.UIDL.value),
            True
        );

        ppmCreateRegisterField(abUIDL_reg, "UID", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abCLKDIV4_reg = ppmCreateRegister(
            "ab_CLKDIV4",
            "System Clock Divider Register 4, offset: 0x1068 ",
            handles.bport1,
            0x1068,
            4,
            read_32,
            bport1_ab_CLKDIV4_maskWrite,
            view32,
            &(bport1_ab_data.CLKDIV4.value),
            True
        );

        ppmCreateRegisterField(abCLKDIV4_reg, "NFCDIV", 0, 27, 5, 1, 1);
        ppmCreateRegisterField(abCLKDIV4_reg, "NFCFRAC", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abCLKDIV4_reg, "TRACEDIV", 0, 1, 3, 1, 1);
        ppmCreateRegisterField(abCLKDIV4_reg, "TRACEFRAC", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abMCR_reg = ppmCreateRegister(
            "ab_MCR",
            "Misc Control Register, offset: 0x106C ",
            handles.bport1,
            0x106c,
            4,
            read_32,
            bport1_ab_MCR_maskWrite,
            view32,
            &(bport1_ab_data.MCR.value),
            True
        );

        ppmCreateRegisterField(abMCR_reg, "PDBLOOP", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "TRACECLKDIS", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "ULPICLKOBE", 0, 30, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CLKDIV4.value = (Uns32)(bport1_ab_data.CLKDIV4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000002));
        bport1_ab_data.FCFG2.value = (Uns32)(bport1_ab_data.FCFG2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FCFG1.value = (Uns32)(bport1_ab_data.FCFG1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CLKDIV2.value = (Uns32)(bport1_ab_data.CLKDIV2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CLKDIV1.value = (Uns32)(bport1_ab_data.CLKDIV1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SCGC7.value = (Uns32)(bport1_ab_data.SCGC7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000007));
        bport1_ab_data.SCGC6.value = (Uns32)(bport1_ab_data.SCGC6.value & ~(0xffffffff)) | ((0xffffffff) & (0x40000001));
        bport1_ab_data.SCGC5.value = (Uns32)(bport1_ab_data.SCGC5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00040180));
        bport1_ab_data.SCGC4.value = (Uns32)(bport1_ab_data.SCGC4.value & ~(0xffffffff)) | ((0xffffffff) & (0xf0100030));
        bport1_ab_data.SCGC3.value = (Uns32)(bport1_ab_data.SCGC3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SCGC2.value = (Uns32)(bport1_ab_data.SCGC2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SCGC1.value = (Uns32)(bport1_ab_data.SCGC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SDID.value = (Uns32)(bport1_ab_data.SDID.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000180));
        bport1_ab_data.SOPT7.value = (Uns32)(bport1_ab_data.SOPT7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SOPT6.value = (Uns32)(bport1_ab_data.SOPT6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SOPT5.value = (Uns32)(bport1_ab_data.SOPT5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SOPT4.value = (Uns32)(bport1_ab_data.SOPT4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SOPT2.value = (Uns32)(bport1_ab_data.SOPT2.value & ~(0xffffffff)) | ((0xffffffff) & (0x44001004));
        bport1_ab_data.SOPT1CFG.value = (Uns32)(bport1_ab_data.SOPT1CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SOPT1.value = (Uns32)(bport1_ab_data.SOPT1.value & ~(0xffffffff)) | ((0xffffffff) & (0x10009000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the SIM peripheral used on the Freescale Kinetis platform");
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

