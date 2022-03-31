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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCRC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CRC_maskWrite) {
    bport1_ab_data.CRC.value = (bport1_ab_data.CRC.value & BPORT1_AB_CRC_WRNMASK) | (data & BPORT1_AB_CRC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CTRL_maskWrite) {
    bport1_ab_data.CTRL.value = (bport1_ab_data.CTRL.value & BPORT1_AB_CTRL_WRNMASK) | (data & BPORT1_AB_CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPOLY_maskWrite) {
    bport1_ab_data.GPOLY.value = (bport1_ab_data.GPOLY.value & BPORT1_AB_GPOLY_WRNMASK) | (data & BPORT1_AB_GPOLY_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCRC_reg = ppmCreateRegister(
            "ab_CRC",
            "CRC Data Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_CRC_maskWrite,
            view32,
            &(bport1_ab_data.CRC.value),
            True
        );

        ppmCreateRegisterField(abCRC_reg, "LL", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCRC_reg, "LU", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abCRC_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCRC_reg, "HU", 0, 24, 8, 1, 1);
    }
    {
        registerHandle abGPOLY_reg = ppmCreateRegister(
            "ab_GPOLY",
            "CRC Polynomial Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_GPOLY_maskWrite,
            view32,
            &(bport1_ab_data.GPOLY.value),
            True
        );

        ppmCreateRegisterField(abGPOLY_reg, "LOW", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abGPOLY_reg, "HIGH", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCTRL_reg = ppmCreateRegister(
            "ab_CTRL",
            "CRC Control Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_CTRL_maskWrite,
            view32,
            &(bport1_ab_data.CTRL.value),
            True
        );

        ppmCreateRegisterField(abCTRL_reg, "TCRC", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "WAS", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "FXOR", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "TOTR", 0, 28, 2, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "TOT", 0, 30, 2, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CTRL.value = (Uns32)(bport1_ab_data.CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPOLY.value = (Uns32)(bport1_ab_data.GPOLY.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001021));
        bport1_ab_data.CRC.value = (Uns32)(bport1_ab_data.CRC.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the CRC peripheral used on the Freescale Kinetis platform");
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

