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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisAIPS", "Example");
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

static PPM_WRITE_CB(bport1_ab_MPRA_maskWrite) {
    bport1_ab_data.MPRA.value = (bport1_ab_data.MPRA.value & BPORT1_AB_MPRA_WRNMASK) | (data & BPORT1_AB_MPRA_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRA_maskWrite) {
    bport1_ab_data.PACRA.value = (bport1_ab_data.PACRA.value & BPORT1_AB_PACRA_WRNMASK) | (data & BPORT1_AB_PACRA_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRB_maskWrite) {
    bport1_ab_data.PACRB.value = (bport1_ab_data.PACRB.value & BPORT1_AB_PACRB_WRNMASK) | (data & BPORT1_AB_PACRB_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRC_maskWrite) {
    bport1_ab_data.PACRC.value = (bport1_ab_data.PACRC.value & BPORT1_AB_PACRC_WRNMASK) | (data & BPORT1_AB_PACRC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRD_maskWrite) {
    bport1_ab_data.PACRD.value = (bport1_ab_data.PACRD.value & BPORT1_AB_PACRD_WRNMASK) | (data & BPORT1_AB_PACRD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRE_maskWrite) {
    bport1_ab_data.PACRE.value = (bport1_ab_data.PACRE.value & BPORT1_AB_PACRE_WRNMASK) | (data & BPORT1_AB_PACRE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRF_maskWrite) {
    bport1_ab_data.PACRF.value = (bport1_ab_data.PACRF.value & BPORT1_AB_PACRF_WRNMASK) | (data & BPORT1_AB_PACRF_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRG_maskWrite) {
    bport1_ab_data.PACRG.value = (bport1_ab_data.PACRG.value & BPORT1_AB_PACRG_WRNMASK) | (data & BPORT1_AB_PACRG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRH_maskWrite) {
    bport1_ab_data.PACRH.value = (bport1_ab_data.PACRH.value & BPORT1_AB_PACRH_WRNMASK) | (data & BPORT1_AB_PACRH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRI_maskWrite) {
    bport1_ab_data.PACRI.value = (bport1_ab_data.PACRI.value & BPORT1_AB_PACRI_WRNMASK) | (data & BPORT1_AB_PACRI_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRJ_maskWrite) {
    bport1_ab_data.PACRJ.value = (bport1_ab_data.PACRJ.value & BPORT1_AB_PACRJ_WRNMASK) | (data & BPORT1_AB_PACRJ_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRK_maskWrite) {
    bport1_ab_data.PACRK.value = (bport1_ab_data.PACRK.value & BPORT1_AB_PACRK_WRNMASK) | (data & BPORT1_AB_PACRK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRL_maskWrite) {
    bport1_ab_data.PACRL.value = (bport1_ab_data.PACRL.value & BPORT1_AB_PACRL_WRNMASK) | (data & BPORT1_AB_PACRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRM_maskWrite) {
    bport1_ab_data.PACRM.value = (bport1_ab_data.PACRM.value & BPORT1_AB_PACRM_WRNMASK) | (data & BPORT1_AB_PACRM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRN_maskWrite) {
    bport1_ab_data.PACRN.value = (bport1_ab_data.PACRN.value & BPORT1_AB_PACRN_WRNMASK) | (data & BPORT1_AB_PACRN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRO_maskWrite) {
    bport1_ab_data.PACRO.value = (bport1_ab_data.PACRO.value & BPORT1_AB_PACRO_WRNMASK) | (data & BPORT1_AB_PACRO_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PACRP_maskWrite) {
    bport1_ab_data.PACRP.value = (bport1_ab_data.PACRP.value & BPORT1_AB_PACRP_WRNMASK) | (data & BPORT1_AB_PACRP_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abMPRA_reg = ppmCreateRegister(
            "ab_MPRA",
            "Master Privilege Register A, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_MPRA_maskWrite,
            view32,
            &(bport1_ab_data.MPRA.value),
            True
        );

        ppmCreateRegisterField(abMPRA_reg, "MPL7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MPL0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTW0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abMPRA_reg, "MTR0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRA_reg = ppmCreateRegister(
            "ab_PACRA",
            "Peripheral Access Control Register, offset: 0x20 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_PACRA_maskWrite,
            view32,
            &(bport1_ab_data.PACRA.value),
            True
        );

        ppmCreateRegisterField(abPACRA_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRA_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRB_reg = ppmCreateRegister(
            "ab_PACRB",
            "Peripheral Access Control Register, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_PACRB_maskWrite,
            view32,
            &(bport1_ab_data.PACRB.value),
            True
        );

        ppmCreateRegisterField(abPACRB_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRB_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRC_reg = ppmCreateRegister(
            "ab_PACRC",
            "Peripheral Access Control Register, offset: 0x28 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_PACRC_maskWrite,
            view32,
            &(bport1_ab_data.PACRC.value),
            True
        );

        ppmCreateRegisterField(abPACRC_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRC_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRD_reg = ppmCreateRegister(
            "ab_PACRD",
            "Peripheral Access Control Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_PACRD_maskWrite,
            view32,
            &(bport1_ab_data.PACRD.value),
            True
        );

        ppmCreateRegisterField(abPACRD_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRD_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRE_reg = ppmCreateRegister(
            "ab_PACRE",
            "Peripheral Access Control Register, offset: 0x40 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_PACRE_maskWrite,
            view32,
            &(bport1_ab_data.PACRE.value),
            True
        );

        ppmCreateRegisterField(abPACRE_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRE_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRF_reg = ppmCreateRegister(
            "ab_PACRF",
            "Peripheral Access Control Register, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_PACRF_maskWrite,
            view32,
            &(bport1_ab_data.PACRF.value),
            True
        );

        ppmCreateRegisterField(abPACRF_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRF_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRG_reg = ppmCreateRegister(
            "ab_PACRG",
            "Peripheral Access Control Register, offset: 0x48 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_PACRG_maskWrite,
            view32,
            &(bport1_ab_data.PACRG.value),
            True
        );

        ppmCreateRegisterField(abPACRG_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRG_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRH_reg = ppmCreateRegister(
            "ab_PACRH",
            "Peripheral Access Control Register, offset: 0x4C ",
            handles.bport1,
            0x4c,
            4,
            read_32,
            bport1_ab_PACRH_maskWrite,
            view32,
            &(bport1_ab_data.PACRH.value),
            True
        );

        ppmCreateRegisterField(abPACRH_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRH_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRI_reg = ppmCreateRegister(
            "ab_PACRI",
            "Peripheral Access Control Register, offset: 0x50 ",
            handles.bport1,
            0x50,
            4,
            read_32,
            bport1_ab_PACRI_maskWrite,
            view32,
            &(bport1_ab_data.PACRI.value),
            True
        );

        ppmCreateRegisterField(abPACRI_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRI_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRJ_reg = ppmCreateRegister(
            "ab_PACRJ",
            "Peripheral Access Control Register, offset: 0x54 ",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_PACRJ_maskWrite,
            view32,
            &(bport1_ab_data.PACRJ.value),
            True
        );

        ppmCreateRegisterField(abPACRJ_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRJ_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRK_reg = ppmCreateRegister(
            "ab_PACRK",
            "Peripheral Access Control Register, offset: 0x58 ",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_PACRK_maskWrite,
            view32,
            &(bport1_ab_data.PACRK.value),
            True
        );

        ppmCreateRegisterField(abPACRK_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRK_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRL_reg = ppmCreateRegister(
            "ab_PACRL",
            "Peripheral Access Control Register, offset: 0x5C ",
            handles.bport1,
            0x5c,
            4,
            read_32,
            bport1_ab_PACRL_maskWrite,
            view32,
            &(bport1_ab_data.PACRL.value),
            True
        );

        ppmCreateRegisterField(abPACRL_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRL_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRM_reg = ppmCreateRegister(
            "ab_PACRM",
            "Peripheral Access Control Register, offset: 0x60 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_PACRM_maskWrite,
            view32,
            &(bport1_ab_data.PACRM.value),
            True
        );

        ppmCreateRegisterField(abPACRM_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRM_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRN_reg = ppmCreateRegister(
            "ab_PACRN",
            "Peripheral Access Control Register, offset: 0x64 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            bport1_ab_PACRN_maskWrite,
            view32,
            &(bport1_ab_data.PACRN.value),
            True
        );

        ppmCreateRegisterField(abPACRN_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRN_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRO_reg = ppmCreateRegister(
            "ab_PACRO",
            "Peripheral Access Control Register, offset: 0x68 ",
            handles.bport1,
            0x68,
            4,
            read_32,
            bport1_ab_PACRO_maskWrite,
            view32,
            &(bport1_ab_data.PACRO.value),
            True
        );

        ppmCreateRegisterField(abPACRO_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRO_reg, "SP0", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abPACRP_reg = ppmCreateRegister(
            "ab_PACRP",
            "Peripheral Access Control Register, offset: 0x6C ",
            handles.bport1,
            0x6c,
            4,
            read_32,
            bport1_ab_PACRP_maskWrite,
            view32,
            &(bport1_ab_data.PACRP.value),
            True
        );

        ppmCreateRegisterField(abPACRP_reg, "TP7", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP7", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP7", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP6", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP6", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP5", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP5", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP4", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP4", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP4", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP3", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP3", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP3", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP1", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP1", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "TP0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "WP0", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPACRP_reg, "SP0", 0, 30, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PACRP.value = (Uns32)(bport1_ab_data.PACRP.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRO.value = (Uns32)(bport1_ab_data.PACRO.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRN.value = (Uns32)(bport1_ab_data.PACRN.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRM.value = (Uns32)(bport1_ab_data.PACRM.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRL.value = (Uns32)(bport1_ab_data.PACRL.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRK.value = (Uns32)(bport1_ab_data.PACRK.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRJ.value = (Uns32)(bport1_ab_data.PACRJ.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRI.value = (Uns32)(bport1_ab_data.PACRI.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRH.value = (Uns32)(bport1_ab_data.PACRH.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRG.value = (Uns32)(bport1_ab_data.PACRG.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRF.value = (Uns32)(bport1_ab_data.PACRF.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRE.value = (Uns32)(bport1_ab_data.PACRE.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PACRD.value = (Uns32)(bport1_ab_data.PACRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x44444444));
        bport1_ab_data.PACRC.value = (Uns32)(bport1_ab_data.PACRC.value & ~(0xffffffff)) | ((0xffffffff) & (0x44444444));
        bport1_ab_data.PACRB.value = (Uns32)(bport1_ab_data.PACRB.value & ~(0xffffffff)) | ((0xffffffff) & (0x44444444));
        bport1_ab_data.PACRA.value = (Uns32)(bport1_ab_data.PACRA.value & ~(0xffffffff)) | ((0xffffffff) & (0x44444444));
        bport1_ab_data.MPRA.value = (Uns32)(bport1_ab_data.MPRA.value & ~(0xffffffff)) | ((0xffffffff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the AIPS peripheral used on the Freescale Kinetis platform");
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

