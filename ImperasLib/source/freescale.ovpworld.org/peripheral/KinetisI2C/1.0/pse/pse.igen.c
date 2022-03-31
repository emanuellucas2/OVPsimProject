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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisI2C", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_A1_maskWrite) {
    bport1_ab_data.A1.value = (bport1_ab_data.A1.value & BPORT1_AB_A1_WRNMASK) | (data & BPORT1_AB_A1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_A2_maskWrite) {
    bport1_ab_data.A2.value = (bport1_ab_data.A2.value & BPORT1_AB_A2_WRNMASK) | (data & BPORT1_AB_A2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & BPORT1_AB_C1_WRNMASK) | (data & BPORT1_AB_C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C2_maskWrite) {
    bport1_ab_data.C2.value = (bport1_ab_data.C2.value & BPORT1_AB_C2_WRNMASK) | (data & BPORT1_AB_C2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_D_maskWrite) {
    bport1_ab_data.D.value = (bport1_ab_data.D.value & BPORT1_AB_D_WRNMASK) | (data & BPORT1_AB_D_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FLT_maskWrite) {
    bport1_ab_data.FLT.value = (bport1_ab_data.FLT.value & BPORT1_AB_FLT_WRNMASK) | (data & BPORT1_AB_FLT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_F_maskWrite) {
    bport1_ab_data.F.value = (bport1_ab_data.F.value & BPORT1_AB_F_WRNMASK) | (data & BPORT1_AB_F_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RA_maskWrite) {
    bport1_ab_data.RA.value = (bport1_ab_data.RA.value & BPORT1_AB_RA_WRNMASK) | (data & BPORT1_AB_RA_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SLTH_maskWrite) {
    bport1_ab_data.SLTH.value = (bport1_ab_data.SLTH.value & BPORT1_AB_SLTH_WRNMASK) | (data & BPORT1_AB_SLTH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SLTL_maskWrite) {
    bport1_ab_data.SLTL.value = (bport1_ab_data.SLTL.value & BPORT1_AB_SLTL_WRNMASK) | (data & BPORT1_AB_SLTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SMB_maskWrite) {
    bport1_ab_data.SMB.value = (bport1_ab_data.SMB.value & BPORT1_AB_SMB_WRNMASK) | (data & BPORT1_AB_SMB_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_S_maskWrite) {
    bport1_ab_data.S.value = (bport1_ab_data.S.value & BPORT1_AB_S_WRNMASK) | (data & BPORT1_AB_S_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abA1_reg = ppmCreateRegister(
            "ab_A1",
            "I2C Address Register 1, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_A1_maskWrite,
            view8,
            &(bport1_ab_data.A1.value),
            True
        );

        ppmCreateRegisterField(abA1_reg, "AD", 0, 1, 7, 1, 1);
    }
    {
        registerHandle abF_reg = ppmCreateRegister(
            "ab_F",
            "I2C Frequency Divider register, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_F_maskWrite,
            view8,
            &(bport1_ab_data.F.value),
            True
        );

        ppmCreateRegisterField(abF_reg, "ICR", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abF_reg, "MULT", 0, 6, 2, 1, 1);
    }
    {
        registerHandle abC1_reg = ppmCreateRegister(
            "ab_C1",
            "I2C Control Register 1, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_C1_maskWrite,
            view8,
            &(bport1_ab_data.C1.value),
            True
        );

        ppmCreateRegisterField(abC1_reg, "DMAEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "IICEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "IICIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "MST", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "RSTA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "TX", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "TXAK", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "WUEN", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abS_reg = ppmCreateRegister(
            "ab_S",
            "I2C Status Register, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            bport1_ab_S_maskWrite,
            view8,
            &(bport1_ab_data.S.value),
            True
        );

        ppmCreateRegisterField(abS_reg, "ARBL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "BUSY", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "IAAS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "IICIF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "RAM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "RXAK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "SRW", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abS_reg, "TCF", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abD_reg = ppmCreateRegister(
            "ab_D",
            "I2C Data I/O register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_D_maskWrite,
            view8,
            &(bport1_ab_data.D.value),
            True
        );

        ppmCreateRegisterField(abD_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abC2_reg = ppmCreateRegister(
            "ab_C2",
            "I2C Control Register 2, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_C2_maskWrite,
            view8,
            &(bport1_ab_data.C2.value),
            True
        );

        ppmCreateRegisterField(abC2_reg, "AD", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abC2_reg, "ADEXT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "GCAEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "HDRS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "RMEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "SBRC", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abFLT_reg = ppmCreateRegister(
            "ab_FLT",
            "I2C Programmable Input Glitch Filter register, offset: 0x6 ",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_FLT_maskWrite,
            view8,
            &(bport1_ab_data.FLT.value),
            True
        );

        ppmCreateRegisterField(abFLT_reg, "FLT", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abRA_reg = ppmCreateRegister(
            "ab_RA",
            "I2C Range Address register, offset: 0x7 ",
            handles.bport1,
            0x7,
            1,
            read_8,
            bport1_ab_RA_maskWrite,
            view8,
            &(bport1_ab_data.RA.value),
            True
        );

        ppmCreateRegisterField(abRA_reg, "RAD", 0, 1, 7, 1, 1);
    }
    {
        registerHandle abSMB_reg = ppmCreateRegister(
            "ab_SMB",
            "I2C SMBus Control and Status register, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_SMB_maskWrite,
            view8,
            &(bport1_ab_data.SMB.value),
            True
        );

        ppmCreateRegisterField(abSMB_reg, "ALERTEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "FACK", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "SHTF1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "SHTF2", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "SHTF2IE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "SIICAEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "SLTF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSMB_reg, "TCKSEL", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abA2_reg = ppmCreateRegister(
            "ab_A2",
            "I2C Address Register 2, offset: 0x9 ",
            handles.bport1,
            0x9,
            1,
            read_8,
            bport1_ab_A2_maskWrite,
            view8,
            &(bport1_ab_data.A2.value),
            True
        );

        ppmCreateRegisterField(abA2_reg, "SAD", 0, 1, 7, 1, 1);
    }
    {
        registerHandle abSLTH_reg = ppmCreateRegister(
            "ab_SLTH",
            "I2C SCL Low Timeout Register High, offset: 0xA ",
            handles.bport1,
            0xa,
            1,
            read_8,
            bport1_ab_SLTH_maskWrite,
            view8,
            &(bport1_ab_data.SLTH.value),
            True
        );

        ppmCreateRegisterField(abSLTH_reg, "SSLT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abSLTL_reg = ppmCreateRegister(
            "ab_SLTL",
            "I2C SCL Low Timeout Register Low, offset: 0xB ",
            handles.bport1,
            0xb,
            1,
            read_8,
            bport1_ab_SLTL_maskWrite,
            view8,
            &(bport1_ab_data.SLTL.value),
            True
        );

        ppmCreateRegisterField(abSLTL_reg, "SSLT", 0, 0, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.SLTL.value = (Uns8)(bport1_ab_data.SLTL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SLTH.value = (Uns8)(bport1_ab_data.SLTH.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.A2.value = (Uns8)(bport1_ab_data.A2.value & ~(0xff)) | ((0xff) & (0xc2));
        bport1_ab_data.SMB.value = (Uns8)(bport1_ab_data.SMB.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RA.value = (Uns8)(bport1_ab_data.RA.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FLT.value = (Uns8)(bport1_ab_data.FLT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C2.value = (Uns8)(bport1_ab_data.C2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.D.value = (Uns8)(bport1_ab_data.D.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.S.value = (Uns8)(bport1_ab_data.S.value & ~(0xff)) | ((0xff) & (0x80));
        bport1_ab_data.C1.value = (Uns8)(bport1_ab_data.C1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.F.value = (Uns8)(bport1_ab_data.F.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.A1.value = (Uns8)(bport1_ab_data.A1.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the I2C peripheral used on the Freescale Kinetis platform");
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

