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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisPDB", "Example");
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

static PPM_WRITE_CB(bport1_ab_CH0C1_maskWrite) {
    bport1_ab_data.CH0C1.value = (bport1_ab_data.CH0C1.value & BPORT1_AB_CH0C1_WRNMASK) | (data & BPORT1_AB_CH0C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH0DLY0_maskWrite) {
    bport1_ab_data.CH0DLY0.value = (bport1_ab_data.CH0DLY0.value & BPORT1_AB_CH0DLY0_WRNMASK) | (data & BPORT1_AB_CH0DLY0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH0DLY1_maskWrite) {
    bport1_ab_data.CH0DLY1.value = (bport1_ab_data.CH0DLY1.value & BPORT1_AB_CH0DLY1_WRNMASK) | (data & BPORT1_AB_CH0DLY1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH0S_maskWrite) {
    bport1_ab_data.CH0S.value = (bport1_ab_data.CH0S.value & BPORT1_AB_CH0S_WRNMASK) | (data & BPORT1_AB_CH0S_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH1C1_maskWrite) {
    bport1_ab_data.CH1C1.value = (bport1_ab_data.CH1C1.value & BPORT1_AB_CH1C1_WRNMASK) | (data & BPORT1_AB_CH1C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH1DLY0_maskWrite) {
    bport1_ab_data.CH1DLY0.value = (bport1_ab_data.CH1DLY0.value & BPORT1_AB_CH1DLY0_WRNMASK) | (data & BPORT1_AB_CH1DLY0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH1DLY1_maskWrite) {
    bport1_ab_data.CH1DLY1.value = (bport1_ab_data.CH1DLY1.value & BPORT1_AB_CH1DLY1_WRNMASK) | (data & BPORT1_AB_CH1DLY1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH1S_maskWrite) {
    bport1_ab_data.CH1S.value = (bport1_ab_data.CH1S.value & BPORT1_AB_CH1S_WRNMASK) | (data & BPORT1_AB_CH1S_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH2C1_maskWrite) {
    bport1_ab_data.CH2C1.value = (bport1_ab_data.CH2C1.value & BPORT1_AB_CH2C1_WRNMASK) | (data & BPORT1_AB_CH2C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH2DLY0_maskWrite) {
    bport1_ab_data.CH2DLY0.value = (bport1_ab_data.CH2DLY0.value & BPORT1_AB_CH2DLY0_WRNMASK) | (data & BPORT1_AB_CH2DLY0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH2DLY1_maskWrite) {
    bport1_ab_data.CH2DLY1.value = (bport1_ab_data.CH2DLY1.value & BPORT1_AB_CH2DLY1_WRNMASK) | (data & BPORT1_AB_CH2DLY1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH2S_maskWrite) {
    bport1_ab_data.CH2S.value = (bport1_ab_data.CH2S.value & BPORT1_AB_CH2S_WRNMASK) | (data & BPORT1_AB_CH2S_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH3C1_maskWrite) {
    bport1_ab_data.CH3C1.value = (bport1_ab_data.CH3C1.value & BPORT1_AB_CH3C1_WRNMASK) | (data & BPORT1_AB_CH3C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH3DLY0_maskWrite) {
    bport1_ab_data.CH3DLY0.value = (bport1_ab_data.CH3DLY0.value & BPORT1_AB_CH3DLY0_WRNMASK) | (data & BPORT1_AB_CH3DLY0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH3DLY1_maskWrite) {
    bport1_ab_data.CH3DLY1.value = (bport1_ab_data.CH3DLY1.value & BPORT1_AB_CH3DLY1_WRNMASK) | (data & BPORT1_AB_CH3DLY1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CH3S_maskWrite) {
    bport1_ab_data.CH3S.value = (bport1_ab_data.CH3S.value & BPORT1_AB_CH3S_WRNMASK) | (data & BPORT1_AB_CH3S_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DACINT0_maskWrite) {
    bport1_ab_data.DACINT0.value = (bport1_ab_data.DACINT0.value & BPORT1_AB_DACINT0_WRNMASK) | (data & BPORT1_AB_DACINT0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DACINT1_maskWrite) {
    bport1_ab_data.DACINT1.value = (bport1_ab_data.DACINT1.value & BPORT1_AB_DACINT1_WRNMASK) | (data & BPORT1_AB_DACINT1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DACINTC0_maskWrite) {
    bport1_ab_data.DACINTC0.value = (bport1_ab_data.DACINTC0.value & BPORT1_AB_DACINTC0_WRNMASK) | (data & BPORT1_AB_DACINTC0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DACINTC1_maskWrite) {
    bport1_ab_data.DACINTC1.value = (bport1_ab_data.DACINTC1.value & BPORT1_AB_DACINTC1_WRNMASK) | (data & BPORT1_AB_DACINTC1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IDLY_maskWrite) {
    bport1_ab_data.IDLY.value = (bport1_ab_data.IDLY.value & BPORT1_AB_IDLY_WRNMASK) | (data & BPORT1_AB_IDLY_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MOD_maskWrite) {
    bport1_ab_data.MOD.value = (bport1_ab_data.MOD.value & BPORT1_AB_MOD_WRNMASK) | (data & BPORT1_AB_MOD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PO0DLY_maskWrite) {
    bport1_ab_data.PO0DLY.value = (bport1_ab_data.PO0DLY.value & BPORT1_AB_PO0DLY_WRNMASK) | (data & BPORT1_AB_PO0DLY_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PO1DLY_maskWrite) {
    bport1_ab_data.PO1DLY.value = (bport1_ab_data.PO1DLY.value & BPORT1_AB_PO1DLY_WRNMASK) | (data & BPORT1_AB_PO1DLY_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PO2DLY_maskWrite) {
    bport1_ab_data.PO2DLY.value = (bport1_ab_data.PO2DLY.value & BPORT1_AB_PO2DLY_WRNMASK) | (data & BPORT1_AB_PO2DLY_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PO3DLY_maskWrite) {
    bport1_ab_data.PO3DLY.value = (bport1_ab_data.PO3DLY.value & BPORT1_AB_PO3DLY_WRNMASK) | (data & BPORT1_AB_PO3DLY_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_POEN_maskWrite) {
    bport1_ab_data.POEN.value = (bport1_ab_data.POEN.value & BPORT1_AB_POEN_WRNMASK) | (data & BPORT1_AB_POEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SC_maskWrite) {
    bport1_ab_data.SC.value = (bport1_ab_data.SC.value & BPORT1_AB_SC_WRNMASK) | (data & BPORT1_AB_SC_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSC_reg = ppmCreateRegister(
            "ab_SC",
            "Status and Control Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_SC_maskWrite,
            view32,
            &(bport1_ab_data.SC.value),
            True
        );

        ppmCreateRegisterField(abSC_reg, "CONT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "DMAEN", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "LDMOD", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abSC_reg, "LDOK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "MULT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abSC_reg, "PDBEIE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "PDBEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "PDBIE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "PDBIF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "PRESCALER", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abSC_reg, "SWTRIG", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "TRGSEL", 0, 8, 4, 1, 1);
    }
    {
        registerHandle abMOD_reg = ppmCreateRegister(
            "ab_MOD",
            "Modulus Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_MOD_maskWrite,
            view32,
            &(bport1_ab_data.MOD.value),
            True
        );

        ppmCreateRegisterField(abMOD_reg, "MOD", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCNT_reg = ppmCreateRegister(
            "ab_CNT",
            "Counter Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNT.value),
            True
        );

        ppmCreateRegisterField(abCNT_reg, "CNT", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abIDLY_reg = ppmCreateRegister(
            "ab_IDLY",
            "Interrupt Delay Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_IDLY_maskWrite,
            view32,
            &(bport1_ab_data.IDLY.value),
            True
        );

        ppmCreateRegisterField(abIDLY_reg, "IDLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH0C1_reg = ppmCreateRegister(
            "ab_CH0C1",
            "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_CH0C1_maskWrite,
            view32,
            &(bport1_ab_data.CH0C1.value),
            True
        );

        ppmCreateRegisterField(abCH0C1_reg, "BB", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH0C1_reg, "EN", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCH0C1_reg, "TOS", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abCH0S_reg = ppmCreateRegister(
            "ab_CH0S",
            "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_CH0S_maskWrite,
            view32,
            &(bport1_ab_data.CH0S.value),
            True
        );

        ppmCreateRegisterField(abCH0S_reg, "CF", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH0S_reg, "ERR", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCH0DLY0_reg = ppmCreateRegister(
            "ab_CH0DLY0",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_CH0DLY0_maskWrite,
            view32,
            &(bport1_ab_data.CH0DLY0.value),
            True
        );

        ppmCreateRegisterField(abCH0DLY0_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH0DLY1_reg = ppmCreateRegister(
            "ab_CH0DLY1",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_CH0DLY1_maskWrite,
            view32,
            &(bport1_ab_data.CH0DLY1.value),
            True
        );

        ppmCreateRegisterField(abCH0DLY1_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH1C1_reg = ppmCreateRegister(
            "ab_CH1C1",
            "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_CH1C1_maskWrite,
            view32,
            &(bport1_ab_data.CH1C1.value),
            True
        );

        ppmCreateRegisterField(abCH1C1_reg, "BB", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH1C1_reg, "EN", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCH1C1_reg, "TOS", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abCH1S_reg = ppmCreateRegister(
            "ab_CH1S",
            "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_CH1S_maskWrite,
            view32,
            &(bport1_ab_data.CH1S.value),
            True
        );

        ppmCreateRegisterField(abCH1S_reg, "CF", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH1S_reg, "ERR", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCH1DLY0_reg = ppmCreateRegister(
            "ab_CH1DLY0",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_CH1DLY0_maskWrite,
            view32,
            &(bport1_ab_data.CH1DLY0.value),
            True
        );

        ppmCreateRegisterField(abCH1DLY0_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH1DLY1_reg = ppmCreateRegister(
            "ab_CH1DLY1",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_CH1DLY1_maskWrite,
            view32,
            &(bport1_ab_data.CH1DLY1.value),
            True
        );

        ppmCreateRegisterField(abCH1DLY1_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH2C1_reg = ppmCreateRegister(
            "ab_CH2C1",
            "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_CH2C1_maskWrite,
            view32,
            &(bport1_ab_data.CH2C1.value),
            True
        );

        ppmCreateRegisterField(abCH2C1_reg, "BB", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH2C1_reg, "EN", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCH2C1_reg, "TOS", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abCH2S_reg = ppmCreateRegister(
            "ab_CH2S",
            "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            bport1_ab_CH2S_maskWrite,
            view32,
            &(bport1_ab_data.CH2S.value),
            True
        );

        ppmCreateRegisterField(abCH2S_reg, "CF", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH2S_reg, "ERR", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCH2DLY0_reg = ppmCreateRegister(
            "ab_CH2DLY0",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x68,
            4,
            read_32,
            bport1_ab_CH2DLY0_maskWrite,
            view32,
            &(bport1_ab_data.CH2DLY0.value),
            True
        );

        ppmCreateRegisterField(abCH2DLY0_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH2DLY1_reg = ppmCreateRegister(
            "ab_CH2DLY1",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x6c,
            4,
            read_32,
            bport1_ab_CH2DLY1_maskWrite,
            view32,
            &(bport1_ab_data.CH2DLY1.value),
            True
        );

        ppmCreateRegisterField(abCH2DLY1_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH3C1_reg = ppmCreateRegister(
            "ab_CH3C1",
            "Channel n Control Register 1, array offset: 0x10, array step: 0x28 ",
            handles.bport1,
            0x88,
            4,
            read_32,
            bport1_ab_CH3C1_maskWrite,
            view32,
            &(bport1_ab_data.CH3C1.value),
            True
        );

        ppmCreateRegisterField(abCH3C1_reg, "BB", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH3C1_reg, "EN", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCH3C1_reg, "TOS", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abCH3S_reg = ppmCreateRegister(
            "ab_CH3S",
            "Channel n Status Register, array offset: 0x14, array step: 0x28 ",
            handles.bport1,
            0x8c,
            4,
            read_32,
            bport1_ab_CH3S_maskWrite,
            view32,
            &(bport1_ab_data.CH3S.value),
            True
        );

        ppmCreateRegisterField(abCH3S_reg, "CF", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCH3S_reg, "ERR", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCH3DLY0_reg = ppmCreateRegister(
            "ab_CH3DLY0",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x90,
            4,
            read_32,
            bport1_ab_CH3DLY0_maskWrite,
            view32,
            &(bport1_ab_data.CH3DLY0.value),
            True
        );

        ppmCreateRegisterField(abCH3DLY0_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCH3DLY1_reg = ppmCreateRegister(
            "ab_CH3DLY1",
            "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 ",
            handles.bport1,
            0x94,
            4,
            read_32,
            bport1_ab_CH3DLY1_maskWrite,
            view32,
            &(bport1_ab_data.CH3DLY1.value),
            True
        );

        ppmCreateRegisterField(abCH3DLY1_reg, "DLY", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abDACINTC0_reg = ppmCreateRegister(
            "ab_DACINTC0",
            "DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 ",
            handles.bport1,
            0x150,
            4,
            read_32,
            bport1_ab_DACINTC0_maskWrite,
            view32,
            &(bport1_ab_data.DACINTC0.value),
            True
        );

        ppmCreateRegisterField(abDACINTC0_reg, "EXT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abDACINTC0_reg, "TOE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abDACINT0_reg = ppmCreateRegister(
            "ab_DACINT0",
            "DAC Interval n Register, array offset: 0x154, array step: 0x8 ",
            handles.bport1,
            0x154,
            4,
            read_32,
            bport1_ab_DACINT0_maskWrite,
            view32,
            &(bport1_ab_data.DACINT0.value),
            True
        );

        ppmCreateRegisterField(abDACINT0_reg, "INT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abDACINTC1_reg = ppmCreateRegister(
            "ab_DACINTC1",
            "DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 ",
            handles.bport1,
            0x158,
            4,
            read_32,
            bport1_ab_DACINTC1_maskWrite,
            view32,
            &(bport1_ab_data.DACINTC1.value),
            True
        );

        ppmCreateRegisterField(abDACINTC1_reg, "EXT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abDACINTC1_reg, "TOE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abDACINT1_reg = ppmCreateRegister(
            "ab_DACINT1",
            "DAC Interval n Register, array offset: 0x154, array step: 0x8 ",
            handles.bport1,
            0x15c,
            4,
            read_32,
            bport1_ab_DACINT1_maskWrite,
            view32,
            &(bport1_ab_data.DACINT1.value),
            True
        );

        ppmCreateRegisterField(abDACINT1_reg, "INT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPOEN_reg = ppmCreateRegister(
            "ab_POEN",
            "Pulse-Out n Enable Register, offset: 0x190 ",
            handles.bport1,
            0x190,
            4,
            read_32,
            bport1_ab_POEN_maskWrite,
            view32,
            &(bport1_ab_data.POEN.value),
            True
        );

        ppmCreateRegisterField(abPOEN_reg, "POEN", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abPO0DLY_reg = ppmCreateRegister(
            "ab_PO0DLY",
            "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
            handles.bport1,
            0x194,
            4,
            read_32,
            bport1_ab_PO0DLY_maskWrite,
            view32,
            &(bport1_ab_data.PO0DLY.value),
            True
        );

        ppmCreateRegisterField(abPO0DLY_reg, "DLY1", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abPO0DLY_reg, "DLY2", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPO1DLY_reg = ppmCreateRegister(
            "ab_PO1DLY",
            "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
            handles.bport1,
            0x198,
            4,
            read_32,
            bport1_ab_PO1DLY_maskWrite,
            view32,
            &(bport1_ab_data.PO1DLY.value),
            True
        );

        ppmCreateRegisterField(abPO1DLY_reg, "DLY1", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abPO1DLY_reg, "DLY2", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPO2DLY_reg = ppmCreateRegister(
            "ab_PO2DLY",
            "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
            handles.bport1,
            0x19c,
            4,
            read_32,
            bport1_ab_PO2DLY_maskWrite,
            view32,
            &(bport1_ab_data.PO2DLY.value),
            True
        );

        ppmCreateRegisterField(abPO2DLY_reg, "DLY1", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abPO2DLY_reg, "DLY2", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPO3DLY_reg = ppmCreateRegister(
            "ab_PO3DLY",
            "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 ",
            handles.bport1,
            0x1a0,
            4,
            read_32,
            bport1_ab_PO3DLY_maskWrite,
            view32,
            &(bport1_ab_data.PO3DLY.value),
            True
        );

        ppmCreateRegisterField(abPO3DLY_reg, "DLY1", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abPO3DLY_reg, "DLY2", 0, 0, 16, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PO3DLY.value = (Uns32)(bport1_ab_data.PO3DLY.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PO2DLY.value = (Uns32)(bport1_ab_data.PO2DLY.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PO1DLY.value = (Uns32)(bport1_ab_data.PO1DLY.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PO0DLY.value = (Uns32)(bport1_ab_data.PO0DLY.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.POEN.value = (Uns32)(bport1_ab_data.POEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DACINT1.value = (Uns32)(bport1_ab_data.DACINT1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DACINTC1.value = (Uns32)(bport1_ab_data.DACINTC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DACINT0.value = (Uns32)(bport1_ab_data.DACINT0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DACINTC0.value = (Uns32)(bport1_ab_data.DACINTC0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH3DLY1.value = (Uns32)(bport1_ab_data.CH3DLY1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH3DLY0.value = (Uns32)(bport1_ab_data.CH3DLY0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH3S.value = (Uns32)(bport1_ab_data.CH3S.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH3C1.value = (Uns32)(bport1_ab_data.CH3C1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH2DLY1.value = (Uns32)(bport1_ab_data.CH2DLY1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH2DLY0.value = (Uns32)(bport1_ab_data.CH2DLY0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH2S.value = (Uns32)(bport1_ab_data.CH2S.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH2C1.value = (Uns32)(bport1_ab_data.CH2C1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH1DLY1.value = (Uns32)(bport1_ab_data.CH1DLY1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH1DLY0.value = (Uns32)(bport1_ab_data.CH1DLY0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH1S.value = (Uns32)(bport1_ab_data.CH1S.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH1C1.value = (Uns32)(bport1_ab_data.CH1C1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH0DLY1.value = (Uns32)(bport1_ab_data.CH0DLY1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH0DLY0.value = (Uns32)(bport1_ab_data.CH0DLY0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH0S.value = (Uns32)(bport1_ab_data.CH0S.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CH0C1.value = (Uns32)(bport1_ab_data.CH0C1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IDLY.value = (Uns32)(bport1_ab_data.IDLY.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000ffff));
        bport1_ab_data.CNT.value = (Uns32)(bport1_ab_data.CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MOD.value = (Uns32)(bport1_ab_data.MOD.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000ffff));
        bport1_ab_data.SC.value = (Uns32)(bport1_ab_data.SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the PDB peripheral used on the Freescale Kinetis platform");
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

