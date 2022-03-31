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

bport1_REG_dataT bport1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-gpio", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_0_LSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_0_LSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_0_MSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_0_MSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_1_LSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_1_LSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_1_MSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_1_MSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_2_LSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_2_LSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_2_MSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_2_MSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_3_LSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_3_LSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_MASK_DATA_3_MSW) {
    *(Uns32*)data = bport1_REG_data.MASK_DATA_3_MSW.value;
}

static PPM_VIEW_CB(view_bport1_REG_DATA_0) {
    *(Uns32*)data = bport1_REG_data.DATA_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_DATA_1) {
    *(Uns32*)data = bport1_REG_data.DATA_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_DATA_2) {
    *(Uns32*)data = bport1_REG_data.DATA_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_DATA_3) {
    *(Uns32*)data = bport1_REG_data.DATA_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_DIRM_0) {
    *(Uns32*)data = bport1_REG_data.DIRM_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_OEN_0) {
    *(Uns32*)data = bport1_REG_data.OEN_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_MASK_0) {
    *(Uns32*)data = bport1_REG_data.INT_MASK_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_EN_0) {
    *(Uns32*)data = bport1_REG_data.INT_EN_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_DIS_0) {
    *(Uns32*)data = bport1_REG_data.INT_DIS_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_STAT_0) {
    *(Uns32*)data = bport1_REG_data.INT_STAT_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_TYPE_0) {
    *(Uns32*)data = bport1_REG_data.INT_TYPE_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_POLARITY_0) {
    *(Uns32*)data = bport1_REG_data.INT_POLARITY_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_ANY_0) {
    *(Uns32*)data = bport1_REG_data.INT_ANY_0.value;
}

static PPM_VIEW_CB(view_bport1_REG_DIRM_1) {
    *(Uns32*)data = bport1_REG_data.DIRM_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_OEN_1) {
    *(Uns32*)data = bport1_REG_data.OEN_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_MASK_1) {
    *(Uns32*)data = bport1_REG_data.INT_MASK_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_EN_1) {
    *(Uns32*)data = bport1_REG_data.INT_EN_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_DIS_1) {
    *(Uns32*)data = bport1_REG_data.INT_DIS_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_STAT_1) {
    *(Uns32*)data = bport1_REG_data.INT_STAT_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_TYPE_1) {
    *(Uns32*)data = bport1_REG_data.INT_TYPE_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_POLARITY_1) {
    *(Uns32*)data = bport1_REG_data.INT_POLARITY_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_ANY_1) {
    *(Uns32*)data = bport1_REG_data.INT_ANY_1.value;
}

static PPM_VIEW_CB(view_bport1_REG_DIRM_2) {
    *(Uns32*)data = bport1_REG_data.DIRM_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_OEN_2) {
    *(Uns32*)data = bport1_REG_data.OEN_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_MASK_2) {
    *(Uns32*)data = bport1_REG_data.INT_MASK_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_EN_2) {
    *(Uns32*)data = bport1_REG_data.INT_EN_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_DIS_2) {
    *(Uns32*)data = bport1_REG_data.INT_DIS_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_STAT_2) {
    *(Uns32*)data = bport1_REG_data.INT_STAT_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_TYPE_2) {
    *(Uns32*)data = bport1_REG_data.INT_TYPE_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_POLARITY_2) {
    *(Uns32*)data = bport1_REG_data.INT_POLARITY_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_ANY_2) {
    *(Uns32*)data = bport1_REG_data.INT_ANY_2.value;
}

static PPM_VIEW_CB(view_bport1_REG_DIRM_3) {
    *(Uns32*)data = bport1_REG_data.DIRM_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_OEN_3) {
    *(Uns32*)data = bport1_REG_data.OEN_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_MASK_3) {
    *(Uns32*)data = bport1_REG_data.INT_MASK_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_EN_3) {
    *(Uns32*)data = bport1_REG_data.INT_EN_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_DIS_3) {
    *(Uns32*)data = bport1_REG_data.INT_DIS_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_STAT_3) {
    *(Uns32*)data = bport1_REG_data.INT_STAT_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_TYPE_3) {
    *(Uns32*)data = bport1_REG_data.INT_TYPE_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_POLARITY_3) {
    *(Uns32*)data = bport1_REG_data.INT_POLARITY_3.value;
}

static PPM_VIEW_CB(view_bport1_REG_INT_ANY_3) {
    *(Uns32*)data = bport1_REG_data.INT_ANY_3.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x3c);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x3c);
    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x70, 0xf90);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x70, 0xf90);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGMASK_DATA_0_LSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_0_LSW",
            "Maskable Output Data (GPIO Bank0, MIO, Lower 16bits)",
            handles.bport1,
            0x0,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_0_LSW,
            (void*)0,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_0_LSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_0_LSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_0_MSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_0_MSW",
            "Maskable Output Data (GPIO Bank0, MIO, Upper 16bits)",
            handles.bport1,
            0x4,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_0_MSW,
            (void*)1,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_0_MSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_0_MSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_1_LSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_1_LSW",
            "Maskable Output Data (GPIO Bank1, MIO, Lower 16bits)",
            handles.bport1,
            0x8,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_1_LSW,
            (void*)2,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_1_LSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_1_LSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_1_MSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_1_MSW",
            "Maskable Output Data (GPIO Bank1, MIO, Upper 6bits)",
            handles.bport1,
            0xc,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_1_MSW,
            (void*)3,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_1_MSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_1_MSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_2_LSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_2_LSW",
            "Maskable Output Data (GPIO Bank2, EMIO, Lower 16bits)",
            handles.bport1,
            0x10,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_2_LSW,
            (void*)4,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_2_LSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_2_LSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_2_MSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_2_MSW",
            "Maskable Output Data (GPIO Bank2, EMIO, Upper 16bits)",
            handles.bport1,
            0x14,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_2_MSW,
            (void*)5,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_2_MSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_2_MSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_3_LSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_3_LSW",
            "Maskable Output Data (GPIO Bank3, EMIO, Lower 16bits)",
            handles.bport1,
            0x18,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_3_LSW,
            (void*)6,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_3_LSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_3_LSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGMASK_DATA_3_MSW_reg = ppmCreateRegister(
            "REG_MASK_DATA_3_MSW",
            "Maskable Output Data (GPIO Bank3, EMIO, Upper 16bits)",
            handles.bport1,
            0x1c,
            4,
            rMASK,
            wMASK,
            view_bport1_REG_MASK_DATA_3_MSW,
            (void*)7,
            True
        );

        ppmCreateRegisterField(REGMASK_DATA_3_MSW_reg, "DATA", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGMASK_DATA_3_MSW_reg, "MASK", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGDATA_0_reg = ppmCreateRegister(
            "REG_DATA_0",
            "Output Data (GPIO Bank0, MIO)",
            handles.bport1,
            0x40,
            4,
            rDATA,
            wDATA,
            view_bport1_REG_DATA_0,
            (void*)0,
            True
        );

        ppmCreateRegisterField(REGDATA_0_reg, "LOW", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGDATA_0_reg, "HIGH", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGDATA_1_reg = ppmCreateRegister(
            "REG_DATA_1",
            "Output Data (GPIO Bank1, MIO)",
            handles.bport1,
            0x44,
            4,
            rDATA,
            wDATA,
            view_bport1_REG_DATA_1,
            (void*)1,
            True
        );

        ppmCreateRegisterField(REGDATA_1_reg, "LOW", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGDATA_1_reg, "HIGH", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGDATA_2_reg = ppmCreateRegister(
            "REG_DATA_2",
            "Output Data (GPIO Bank2, EMIO)",
            handles.bport1,
            0x48,
            4,
            rDATA,
            wDATA,
            view_bport1_REG_DATA_2,
            (void*)2,
            True
        );

        ppmCreateRegisterField(REGDATA_2_reg, "LOW", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGDATA_2_reg, "HIGH", 0, 16, 16, 1, 1);
    }
    {
        registerHandle REGDATA_3_reg = ppmCreateRegister(
            "REG_DATA_3",
            "Output Data (GPIO Bank3, EMIO)",
            handles.bport1,
            0x4c,
            4,
            rDATA,
            wDATA,
            view_bport1_REG_DATA_3,
            (void*)3,
            True
        );

        ppmCreateRegisterField(REGDATA_3_reg, "LOW", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(REGDATA_3_reg, "HIGH", 0, 16, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "REG_DIRM_0",
            "Direction mode (GPIO Bank0,MIO)",
            handles.bport1,
            0x204,
            4,
            rDIRM,
            wDIRM,
            view_bport1_REG_DIRM_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_OEN_0",
            "Output enable (GPIO Bank0,MIO)",
            handles.bport1,
            0x208,
            4,
            rOEN,
            wOEN,
            view_bport1_REG_OEN_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_MASK_0",
            "Interrupt Mask Status (GPIO Bank0, MIO)",
            handles.bport1,
            0x20c,
            4,
            rINT_MASK,
            0,
            view_bport1_REG_INT_MASK_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_EN_0",
            "Interrupt Enable/Unmask (GPIO Bank0, MIO)",
            handles.bport1,
            0x210,
            4,
            0,
            wINT_EN,
            view_bport1_REG_INT_EN_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_DIS_0",
            "Interrupt Disable/Mask (GPIO Bank0, MIO)",
            handles.bport1,
            0x214,
            4,
            0,
            wINT_DIS,
            view_bport1_REG_INT_DIS_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_STAT_0",
            "Interrupt Status (GPIO Bank0, MIO)",
            handles.bport1,
            0x218,
            4,
            0,
            wINT_STAT,
            view_bport1_REG_INT_STAT_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_TYPE_0",
            "Interrupt Type (GPIO Bank0, MIO)",
            handles.bport1,
            0x21c,
            4,
            rINT_TYPE,
            wINT_TYPE,
            view_bport1_REG_INT_TYPE_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_POLARITY_0",
            "Interrupt Polarity (GPIO Bank0, MIO)",
            handles.bport1,
            0x220,
            4,
            rINT_POLARITY,
            wINT_POLARITY,
            view_bport1_REG_INT_POLARITY_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_ANY_0",
            "Interrupt Any Edge Sensitive (GPIO Bank0, MIO)",
            handles.bport1,
            0x224,
            4,
            rINT_ANY,
            wINT_ANY,
            view_bport1_REG_INT_ANY_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_DIRM_1",
            "Direction mode (GPIO Bank1, MIO)",
            handles.bport1,
            0x244,
            4,
            rDIRM,
            wDIRM,
            view_bport1_REG_DIRM_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_OEN_1",
            "Output enable (GPIO Bank1, MIO)",
            handles.bport1,
            0x248,
            4,
            rOEN,
            wOEN,
            view_bport1_REG_OEN_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_MASK_1",
            "Interrupt Mask Status (GPIO Bank1, MIO)",
            handles.bport1,
            0x24c,
            4,
            rINT_MASK,
            0,
            view_bport1_REG_INT_MASK_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_EN_1",
            "Interrupt Enable/Unmask (GPIO Bank1, MIO)",
            handles.bport1,
            0x250,
            4,
            0,
            wINT_EN,
            view_bport1_REG_INT_EN_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_DIS_1",
            "Interrupt Disable/Mask (GPIO Bank1, MIO)",
            handles.bport1,
            0x254,
            4,
            0,
            wINT_DIS,
            view_bport1_REG_INT_DIS_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_STAT_1",
            "Interrupt Status (GPIO Bank1, MIO)",
            handles.bport1,
            0x258,
            4,
            0,
            wINT_STAT,
            view_bport1_REG_INT_STAT_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_TYPE_1",
            "Interrupt Type (GPIO Bank1, MIO)",
            handles.bport1,
            0x25c,
            4,
            rINT_TYPE,
            wINT_TYPE,
            view_bport1_REG_INT_TYPE_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_POLARITY_1",
            "Interrupt Polarity (GPIO Bank1, MIO)",
            handles.bport1,
            0x260,
            4,
            rINT_POLARITY,
            wINT_POLARITY,
            view_bport1_REG_INT_POLARITY_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_ANY_1",
            "Interrupt Any Edge Sensitive (GPIO Bank1, MIO)",
            handles.bport1,
            0x264,
            4,
            rINT_ANY,
            wINT_ANY,
            view_bport1_REG_INT_ANY_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_DIRM_2",
            "Direction mode (GPIO Bank2, EMIO)",
            handles.bport1,
            0x284,
            4,
            rDIRM,
            wDIRM,
            view_bport1_REG_DIRM_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_OEN_2",
            "Output enable (GPIO Bank2, EMIO)",
            handles.bport1,
            0x288,
            4,
            rOEN,
            wOEN,
            view_bport1_REG_OEN_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_MASK_2",
            "Interrupt Mask Status (GPIO Bank2, EMIO)",
            handles.bport1,
            0x28c,
            4,
            rINT_MASK,
            0,
            view_bport1_REG_INT_MASK_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_EN_2",
            "Interrupt Enable/Unmask (GPIO Bank2, EMIO)",
            handles.bport1,
            0x290,
            4,
            0,
            wINT_EN,
            view_bport1_REG_INT_EN_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_DIS_2",
            "Interrupt Disable/Mask (GPIO Bank2, EMIO)",
            handles.bport1,
            0x294,
            4,
            0,
            wINT_DIS,
            view_bport1_REG_INT_DIS_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_STAT_2",
            "Interrupt Status (GPIO Bank2, EMIO)",
            handles.bport1,
            0x298,
            4,
            0,
            wINT_STAT,
            view_bport1_REG_INT_STAT_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_TYPE_2",
            "Interrupt Type (GPIO Bank2, EMIO)",
            handles.bport1,
            0x29c,
            4,
            rINT_TYPE,
            wINT_TYPE,
            view_bport1_REG_INT_TYPE_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_POLARITY_2",
            "Interrupt Polarity (GPIO Bank2, EMIO)",
            handles.bport1,
            0x2a0,
            4,
            rINT_POLARITY,
            wINT_POLARITY,
            view_bport1_REG_INT_POLARITY_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_ANY_2",
            "Interrupt Any Edge Sensitive (GPIO Bank2, EMIO)",
            handles.bport1,
            0x2a4,
            4,
            rINT_ANY,
            wINT_ANY,
            view_bport1_REG_INT_ANY_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_DIRM_3",
            "Direction mode (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2c4,
            4,
            rDIRM,
            wDIRM,
            view_bport1_REG_DIRM_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_OEN_3",
            "Output enable (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2c8,
            4,
            rOEN,
            wOEN,
            view_bport1_REG_OEN_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_MASK_3",
            "Interrupt Mask Status (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2cc,
            4,
            rINT_MASK,
            0,
            view_bport1_REG_INT_MASK_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_EN_3",
            "Interrupt Enable/Unmask (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2d0,
            4,
            0,
            wINT_EN,
            view_bport1_REG_INT_EN_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_DIS_3",
            "Interrupt Disable/Mask (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2d4,
            4,
            0,
            wINT_DIS,
            view_bport1_REG_INT_DIS_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_STAT_3",
            "Interrupt Status (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2d8,
            4,
            0,
            wINT_STAT,
            view_bport1_REG_INT_STAT_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_TYPE_3",
            "Interrupt Type (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2dc,
            4,
            rINT_TYPE,
            wINT_TYPE,
            view_bport1_REG_INT_TYPE_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_POLARITY_3",
            "Interrupt Polarity (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2e0,
            4,
            rINT_POLARITY,
            wINT_POLARITY,
            view_bport1_REG_INT_POLARITY_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INT_ANY_3",
            "Interrupt Any Edge Sensitive (GPIO Bank3, EMIO)",
            handles.bport1,
            0x2e4,
            4,
            rINT_ANY,
            wINT_ANY,
            view_bport1_REG_INT_ANY_3,
            (void*)3,
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_REG_data.INT_ANY_3.value = (Uns32)(bport1_REG_data.INT_ANY_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_POLARITY_3.value = (Uns32)(bport1_REG_data.INT_POLARITY_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_TYPE_3.value = (Uns32)(bport1_REG_data.INT_TYPE_3.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_REG_data.INT_STAT_3.value = (Uns32)(bport1_REG_data.INT_STAT_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_DIS_3.value = (Uns32)(bport1_REG_data.INT_DIS_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_EN_3.value = (Uns32)(bport1_REG_data.INT_EN_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_MASK_3.value = (Uns32)(bport1_REG_data.INT_MASK_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.OEN_3.value = (Uns32)(bport1_REG_data.OEN_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DIRM_3.value = (Uns32)(bport1_REG_data.DIRM_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_ANY_2.value = (Uns32)(bport1_REG_data.INT_ANY_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_POLARITY_2.value = (Uns32)(bport1_REG_data.INT_POLARITY_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_TYPE_2.value = (Uns32)(bport1_REG_data.INT_TYPE_2.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_REG_data.INT_STAT_2.value = (Uns32)(bport1_REG_data.INT_STAT_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_DIS_2.value = (Uns32)(bport1_REG_data.INT_DIS_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_EN_2.value = (Uns32)(bport1_REG_data.INT_EN_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_MASK_2.value = (Uns32)(bport1_REG_data.INT_MASK_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.OEN_2.value = (Uns32)(bport1_REG_data.OEN_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DIRM_2.value = (Uns32)(bport1_REG_data.DIRM_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_ANY_1.value = (Uns32)(bport1_REG_data.INT_ANY_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_POLARITY_1.value = (Uns32)(bport1_REG_data.INT_POLARITY_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_TYPE_1.value = (Uns32)(bport1_REG_data.INT_TYPE_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x003FFFFF));
        bport1_REG_data.INT_STAT_1.value = (Uns32)(bport1_REG_data.INT_STAT_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_DIS_1.value = (Uns32)(bport1_REG_data.INT_DIS_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_EN_1.value = (Uns32)(bport1_REG_data.INT_EN_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_MASK_1.value = (Uns32)(bport1_REG_data.INT_MASK_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.OEN_1.value = (Uns32)(bport1_REG_data.OEN_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DIRM_1.value = (Uns32)(bport1_REG_data.DIRM_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_ANY_0.value = (Uns32)(bport1_REG_data.INT_ANY_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_POLARITY_0.value = (Uns32)(bport1_REG_data.INT_POLARITY_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_TYPE_0.value = (Uns32)(bport1_REG_data.INT_TYPE_0.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_REG_data.INT_STAT_0.value = (Uns32)(bport1_REG_data.INT_STAT_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_DIS_0.value = (Uns32)(bport1_REG_data.INT_DIS_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_EN_0.value = (Uns32)(bport1_REG_data.INT_EN_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INT_MASK_0.value = (Uns32)(bport1_REG_data.INT_MASK_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.OEN_0.value = (Uns32)(bport1_REG_data.OEN_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DIRM_0.value = (Uns32)(bport1_REG_data.DIRM_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DATA_3.value = (Uns32)(bport1_REG_data.DATA_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DATA_2.value = (Uns32)(bport1_REG_data.DATA_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DATA_1.value = (Uns32)(bport1_REG_data.DATA_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DATA_0.value = (Uns32)(bport1_REG_data.DATA_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_3_MSW.value = (Uns32)(bport1_REG_data.MASK_DATA_3_MSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_3_LSW.value = (Uns32)(bport1_REG_data.MASK_DATA_3_LSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_2_MSW.value = (Uns32)(bport1_REG_data.MASK_DATA_2_MSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_2_LSW.value = (Uns32)(bport1_REG_data.MASK_DATA_2_LSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_1_MSW.value = (Uns32)(bport1_REG_data.MASK_DATA_1_MSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_1_LSW.value = (Uns32)(bport1_REG_data.MASK_DATA_1_LSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_0_MSW.value = (Uns32)(bport1_REG_data.MASK_DATA_0_MSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.MASK_DATA_0_LSW.value = (Uns32)(bport1_REG_data.MASK_DATA_0_LSW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform GPIO Registers (gpio)");
        ppmDocAddText(doc2_node, "Included is the visualization of LED and SW connectivity for the ZC702/ZC706 devices.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements only the registers for generation of input or output data values.");
        ppmDocAddText(doc_22_node, "No interrupt generation is currently included in the model.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

