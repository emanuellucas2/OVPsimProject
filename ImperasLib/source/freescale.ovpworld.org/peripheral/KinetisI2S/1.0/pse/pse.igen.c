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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisI2S", "Example");
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

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & BPORT1_AB_MCR_WRNMASK) | (data & BPORT1_AB_MCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MDR_maskWrite) {
    bport1_ab_data.MDR.value = (bport1_ab_data.MDR.value & BPORT1_AB_MDR_WRNMASK) | (data & BPORT1_AB_MDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCR1_maskWrite) {
    bport1_ab_data.RCR1.value = (bport1_ab_data.RCR1.value & BPORT1_AB_RCR1_WRNMASK) | (data & BPORT1_AB_RCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCR2_maskWrite) {
    bport1_ab_data.RCR2.value = (bport1_ab_data.RCR2.value & BPORT1_AB_RCR2_WRNMASK) | (data & BPORT1_AB_RCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCR3_maskWrite) {
    bport1_ab_data.RCR3.value = (bport1_ab_data.RCR3.value & BPORT1_AB_RCR3_WRNMASK) | (data & BPORT1_AB_RCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCR4_maskWrite) {
    bport1_ab_data.RCR4.value = (bport1_ab_data.RCR4.value & BPORT1_AB_RCR4_WRNMASK) | (data & BPORT1_AB_RCR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCR5_maskWrite) {
    bport1_ab_data.RCR5.value = (bport1_ab_data.RCR5.value & BPORT1_AB_RCR5_WRNMASK) | (data & BPORT1_AB_RCR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RCSR_maskWrite) {
    bport1_ab_data.RCSR.value = (bport1_ab_data.RCSR.value & BPORT1_AB_RCSR_WRNMASK) | (data & BPORT1_AB_RCSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RMR_maskWrite) {
    bport1_ab_data.RMR.value = (bport1_ab_data.RMR.value & BPORT1_AB_RMR_WRNMASK) | (data & BPORT1_AB_RMR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR1_maskWrite) {
    bport1_ab_data.TCR1.value = (bport1_ab_data.TCR1.value & BPORT1_AB_TCR1_WRNMASK) | (data & BPORT1_AB_TCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR2_maskWrite) {
    bport1_ab_data.TCR2.value = (bport1_ab_data.TCR2.value & BPORT1_AB_TCR2_WRNMASK) | (data & BPORT1_AB_TCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR3_maskWrite) {
    bport1_ab_data.TCR3.value = (bport1_ab_data.TCR3.value & BPORT1_AB_TCR3_WRNMASK) | (data & BPORT1_AB_TCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR4_maskWrite) {
    bport1_ab_data.TCR4.value = (bport1_ab_data.TCR4.value & BPORT1_AB_TCR4_WRNMASK) | (data & BPORT1_AB_TCR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR5_maskWrite) {
    bport1_ab_data.TCR5.value = (bport1_ab_data.TCR5.value & BPORT1_AB_TCR5_WRNMASK) | (data & BPORT1_AB_TCR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCSR_maskWrite) {
    bport1_ab_data.TCSR.value = (bport1_ab_data.TCSR.value & BPORT1_AB_TCSR_WRNMASK) | (data & BPORT1_AB_TCSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TDR0_maskWrite) {
    bport1_ab_data.TDR0.value = (bport1_ab_data.TDR0.value & BPORT1_AB_TDR0_WRNMASK) | (data & BPORT1_AB_TDR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TDR1_maskWrite) {
    bport1_ab_data.TDR1.value = (bport1_ab_data.TDR1.value & BPORT1_AB_TDR1_WRNMASK) | (data & BPORT1_AB_TDR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TMR_maskWrite) {
    bport1_ab_data.TMR.value = (bport1_ab_data.TMR.value & BPORT1_AB_TMR_WRNMASK) | (data & BPORT1_AB_TMR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abTCSR_reg = ppmCreateRegister(
            "ab_TCSR",
            "SAI Transmit Control Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_TCSR_maskWrite,
            view32,
            &(bport1_ab_data.TCSR.value),
            True
        );

        ppmCreateRegisterField(abTCSR_reg, "BCE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "DBGE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FEF", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FEIE", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FR", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FRDE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FRF", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FRIE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FWDE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FWF", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "FWIE", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "SEF", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "SEIE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "SR", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "STOPE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "TE", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "WSF", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abTCSR_reg, "WSIE", 0, 12, 1, 1, 1);
    }
    {
        registerHandle abTCR1_reg = ppmCreateRegister(
            "ab_TCR1",
            "SAI Transmit Configuration 1 Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_TCR1_maskWrite,
            view32,
            &(bport1_ab_data.TCR1.value),
            True
        );

        ppmCreateRegisterField(abTCR1_reg, "TFW", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abTCR2_reg = ppmCreateRegister(
            "ab_TCR2",
            "SAI Transmit Configuration 2 Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_TCR2_maskWrite,
            view32,
            &(bport1_ab_data.TCR2.value),
            True
        );

        ppmCreateRegisterField(abTCR2_reg, "BCD", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abTCR2_reg, "BCI", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abTCR2_reg, "BCP", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abTCR2_reg, "BCS", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abTCR2_reg, "DIV", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abTCR2_reg, "MSEL", 0, 26, 2, 1, 1);
        ppmCreateRegisterField(abTCR2_reg, "SYNC", 0, 30, 2, 1, 1);
    }
    {
        registerHandle abTCR3_reg = ppmCreateRegister(
            "ab_TCR3",
            "SAI Transmit Configuration 3 Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_TCR3_maskWrite,
            view32,
            &(bport1_ab_data.TCR3.value),
            True
        );

        ppmCreateRegisterField(abTCR3_reg, "TCE", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abTCR3_reg, "WDFL", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abTCR4_reg = ppmCreateRegister(
            "ab_TCR4",
            "SAI Transmit Configuration 4 Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_TCR4_maskWrite,
            view32,
            &(bport1_ab_data.TCR4.value),
            True
        );

        ppmCreateRegisterField(abTCR4_reg, "FRSZ", 0, 16, 5, 1, 1);
        ppmCreateRegisterField(abTCR4_reg, "FSD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCR4_reg, "FSE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTCR4_reg, "FSP", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abTCR4_reg, "MF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTCR4_reg, "SYWD", 0, 8, 5, 1, 1);
    }
    {
        registerHandle abTCR5_reg = ppmCreateRegister(
            "ab_TCR5",
            "SAI Transmit Configuration 5 Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_TCR5_maskWrite,
            view32,
            &(bport1_ab_data.TCR5.value),
            True
        );

        ppmCreateRegisterField(abTCR5_reg, "FBT", 0, 8, 5, 1, 1);
        ppmCreateRegisterField(abTCR5_reg, "W0W", 0, 16, 5, 1, 1);
        ppmCreateRegisterField(abTCR5_reg, "WNW", 0, 24, 5, 1, 1);
    }
    {
        registerHandle abTDR0_reg = ppmCreateRegister(
            "ab_TDR0",
            "SAI Transmit Data Register, array offset: 0x20, array step: 0x4 ",
            handles.bport1,
            0x20,
            4,
            0,
            bport1_ab_TDR0_maskWrite,
            view32,
            &(bport1_ab_data.TDR0.value),
            True
        );

        ppmCreateRegisterField(abTDR0_reg, "TDR", 0, 0, 32, 0, 1);
    }
    {
        registerHandle abTDR1_reg = ppmCreateRegister(
            "ab_TDR1",
            "SAI Transmit Data Register, array offset: 0x20, array step: 0x4 ",
            handles.bport1,
            0x24,
            4,
            0,
            bport1_ab_TDR1_maskWrite,
            view32,
            &(bport1_ab_data.TDR1.value),
            True
        );

        ppmCreateRegisterField(abTDR1_reg, "TDR", 0, 0, 32, 0, 1);
    }
    {
        registerHandle abTFR0_reg = ppmCreateRegister(
            "ab_TFR0",
            "SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TFR0.value),
            True
        );

        ppmCreateRegisterField(abTFR0_reg, "RFP", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abTFR0_reg, "WFP", 0, 16, 4, 1, 0);
    }
    {
        registerHandle abTFR1_reg = ppmCreateRegister(
            "ab_TFR1",
            "SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TFR1.value),
            True
        );

        ppmCreateRegisterField(abTFR1_reg, "RFP", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abTFR1_reg, "WFP", 0, 16, 4, 1, 0);
    }
    {
        registerHandle abTMR_reg = ppmCreateRegister(
            "ab_TMR",
            "SAI Transmit Mask Register, offset: 0x60 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_TMR_maskWrite,
            view32,
            &(bport1_ab_data.TMR.value),
            True
        );

        ppmCreateRegisterField(abTMR_reg, "TWM", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRCSR_reg = ppmCreateRegister(
            "ab_RCSR",
            "SAI Receive Control Register, offset: 0x80 ",
            handles.bport1,
            0x80,
            4,
            read_32,
            bport1_ab_RCSR_maskWrite,
            view32,
            &(bport1_ab_data.RCSR.value),
            True
        );

        ppmCreateRegisterField(abRCSR_reg, "BCE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "DBGE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FEF", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FEIE", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FR", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FRDE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FRF", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FRIE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FWDE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FWF", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "FWIE", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "RE", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "SEF", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "SEIE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "SR", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "STOPE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "WSF", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abRCSR_reg, "WSIE", 0, 12, 1, 1, 1);
    }
    {
        registerHandle abRCR1_reg = ppmCreateRegister(
            "ab_RCR1",
            "SAI Receive Configuration 1 Register, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            read_32,
            bport1_ab_RCR1_maskWrite,
            view32,
            &(bport1_ab_data.RCR1.value),
            True
        );

        ppmCreateRegisterField(abRCR1_reg, "RFW", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abRCR2_reg = ppmCreateRegister(
            "ab_RCR2",
            "SAI Receive Configuration 2 Register, offset: 0x88 ",
            handles.bport1,
            0x88,
            4,
            read_32,
            bport1_ab_RCR2_maskWrite,
            view32,
            &(bport1_ab_data.RCR2.value),
            True
        );

        ppmCreateRegisterField(abRCR2_reg, "BCD", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abRCR2_reg, "BCI", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abRCR2_reg, "BCP", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abRCR2_reg, "BCS", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abRCR2_reg, "DIV", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abRCR2_reg, "MSEL", 0, 26, 2, 1, 1);
        ppmCreateRegisterField(abRCR2_reg, "SYNC", 0, 30, 2, 1, 1);
    }
    {
        registerHandle abRCR3_reg = ppmCreateRegister(
            "ab_RCR3",
            "SAI Receive Configuration 3 Register, offset: 0x8C ",
            handles.bport1,
            0x8c,
            4,
            read_32,
            bport1_ab_RCR3_maskWrite,
            view32,
            &(bport1_ab_data.RCR3.value),
            True
        );

        ppmCreateRegisterField(abRCR3_reg, "RCE", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abRCR3_reg, "WDFL", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abRCR4_reg = ppmCreateRegister(
            "ab_RCR4",
            "SAI Receive Configuration 4 Register, offset: 0x90 ",
            handles.bport1,
            0x90,
            4,
            read_32,
            bport1_ab_RCR4_maskWrite,
            view32,
            &(bport1_ab_data.RCR4.value),
            True
        );

        ppmCreateRegisterField(abRCR4_reg, "FRSZ", 0, 16, 5, 1, 1);
        ppmCreateRegisterField(abRCR4_reg, "FSD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abRCR4_reg, "FSE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abRCR4_reg, "FSP", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abRCR4_reg, "MF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abRCR4_reg, "SYWD", 0, 8, 5, 1, 1);
    }
    {
        registerHandle abRCR5_reg = ppmCreateRegister(
            "ab_RCR5",
            "SAI Receive Configuration 5 Register, offset: 0x94 ",
            handles.bport1,
            0x94,
            4,
            read_32,
            bport1_ab_RCR5_maskWrite,
            view32,
            &(bport1_ab_data.RCR5.value),
            True
        );

        ppmCreateRegisterField(abRCR5_reg, "FBT", 0, 8, 5, 1, 1);
        ppmCreateRegisterField(abRCR5_reg, "W0W", 0, 16, 5, 1, 1);
        ppmCreateRegisterField(abRCR5_reg, "WNW", 0, 24, 5, 1, 1);
    }
    {
        registerHandle abRDR0_reg = ppmCreateRegister(
            "ab_RDR0",
            "SAI Receive Data Register, array offset: 0xA0, array step: 0x4 ",
            handles.bport1,
            0xa0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RDR0.value),
            True
        );

        ppmCreateRegisterField(abRDR0_reg, "RDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abRDR1_reg = ppmCreateRegister(
            "ab_RDR1",
            "SAI Receive Data Register, array offset: 0xA0, array step: 0x4 ",
            handles.bport1,
            0xa4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RDR1.value),
            True
        );

        ppmCreateRegisterField(abRDR1_reg, "RDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abRFR0_reg = ppmCreateRegister(
            "ab_RFR0",
            "SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 ",
            handles.bport1,
            0xc0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RFR0.value),
            True
        );

        ppmCreateRegisterField(abRFR0_reg, "RFP", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abRFR0_reg, "WFP", 0, 16, 4, 1, 0);
    }
    {
        registerHandle abRFR1_reg = ppmCreateRegister(
            "ab_RFR1",
            "SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 ",
            handles.bport1,
            0xc4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RFR1.value),
            True
        );

        ppmCreateRegisterField(abRFR1_reg, "RFP", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abRFR1_reg, "WFP", 0, 16, 4, 1, 0);
    }
    {
        registerHandle abRMR_reg = ppmCreateRegister(
            "ab_RMR",
            "SAI Receive Mask Register, offset: 0xE0 ",
            handles.bport1,
            0xe0,
            4,
            read_32,
            bport1_ab_RMR_maskWrite,
            view32,
            &(bport1_ab_data.RMR.value),
            True
        );

        ppmCreateRegisterField(abRMR_reg, "RWM", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abMCR_reg = ppmCreateRegister(
            "ab_MCR",
            "SAI MCLK Control Register, offset: 0x100 ",
            handles.bport1,
            0x100,
            4,
            read_32,
            bport1_ab_MCR_maskWrite,
            view32,
            &(bport1_ab_data.MCR.value),
            True
        );

        ppmCreateRegisterField(abMCR_reg, "DUF", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MICS", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MOE", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abMDR_reg = ppmCreateRegister(
            "ab_MDR",
            "MCLK Divide Register, offset: 0x104 ",
            handles.bport1,
            0x104,
            4,
            read_32,
            bport1_ab_MDR_maskWrite,
            view32,
            &(bport1_ab_data.MDR.value),
            True
        );

        ppmCreateRegisterField(abMDR_reg, "DIVIDE", 0, 0, 12, 1, 1);
        ppmCreateRegisterField(abMDR_reg, "FRACT", 0, 12, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.MDR.value = (Uns32)(bport1_ab_data.MDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RMR.value = (Uns32)(bport1_ab_data.RMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RFR1.value = (Uns32)(bport1_ab_data.RFR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RFR0.value = (Uns32)(bport1_ab_data.RFR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RDR1.value = (Uns32)(bport1_ab_data.RDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RDR0.value = (Uns32)(bport1_ab_data.RDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCR5.value = (Uns32)(bport1_ab_data.RCR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCR4.value = (Uns32)(bport1_ab_data.RCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCR3.value = (Uns32)(bport1_ab_data.RCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCR2.value = (Uns32)(bport1_ab_data.RCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCR1.value = (Uns32)(bport1_ab_data.RCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RCSR.value = (Uns32)(bport1_ab_data.RCSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TMR.value = (Uns32)(bport1_ab_data.TMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TFR1.value = (Uns32)(bport1_ab_data.TFR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TFR0.value = (Uns32)(bport1_ab_data.TFR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TDR1.value = (Uns32)(bport1_ab_data.TDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TDR0.value = (Uns32)(bport1_ab_data.TDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR5.value = (Uns32)(bport1_ab_data.TCR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR4.value = (Uns32)(bport1_ab_data.TCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR3.value = (Uns32)(bport1_ab_data.TCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR2.value = (Uns32)(bport1_ab_data.TCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR1.value = (Uns32)(bport1_ab_data.TCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCSR.value = (Uns32)(bport1_ab_data.TCSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the I2S peripheral used on the Freescale Kinetis platform");
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

