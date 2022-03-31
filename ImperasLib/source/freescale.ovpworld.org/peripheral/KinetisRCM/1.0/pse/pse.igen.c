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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisRCM", "Example");
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

static PPM_WRITE_CB(bport1_ab_RPFC_maskWrite) {
    bport1_ab_data.RPFC.value = (bport1_ab_data.RPFC.value & BPORT1_AB_RPFC_WRNMASK) | (data & BPORT1_AB_RPFC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RPFW_maskWrite) {
    bport1_ab_data.RPFW.value = (bport1_ab_data.RPFW.value & BPORT1_AB_RPFW_WRNMASK) | (data & BPORT1_AB_RPFW_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSRS0_reg = ppmCreateRegister(
            "ab_SRS0",
            "System Reset Status Register 0, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.SRS0.value),
            True
        );

        ppmCreateRegisterField(abSRS0_reg, "LOC", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abSRS0_reg, "LVD", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abSRS0_reg, "PIN", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abSRS0_reg, "POR", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abSRS0_reg, "WAKEUP", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abSRS0_reg, "WDOG", 0, 5, 1, 1, 0);
    }
    {
        registerHandle abSRS1_reg = ppmCreateRegister(
            "ab_SRS1",
            "System Reset Status Register 1, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.SRS1.value),
            True
        );

        ppmCreateRegisterField(abSRS1_reg, "EZPT", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abSRS1_reg, "JTAG", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abSRS1_reg, "LOCKUP", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abSRS1_reg, "MDM_AP", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abSRS1_reg, "SACKERR", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abSRS1_reg, "SW", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abSRS1_reg, "TAMPER", 0, 7, 1, 1, 0);
    }
    {
        registerHandle abRPFC_reg = ppmCreateRegister(
            "ab_RPFC",
            "Reset Pin Filter Control Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_RPFC_maskWrite,
            view8,
            &(bport1_ab_data.RPFC.value),
            True
        );

        ppmCreateRegisterField(abRPFC_reg, "RSTFLTSRW", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abRPFC_reg, "RSTFLTSS", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abRPFW_reg = ppmCreateRegister(
            "ab_RPFW",
            "Reset Pin Filter Width Register, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_RPFW_maskWrite,
            view8,
            &(bport1_ab_data.RPFW.value),
            True
        );

        ppmCreateRegisterField(abRPFW_reg, "RSTFLTSEL", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abMR_reg = ppmCreateRegister(
            "ab_MR",
            "Mode Register, offset: 0x7 ",
            handles.bport1,
            0x7,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.MR.value),
            True
        );

        ppmCreateRegisterField(abMR_reg, "EZP_MS", 0, 1, 1, 1, 0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.MR.value = (Uns8)(bport1_ab_data.MR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RPFW.value = (Uns8)(bport1_ab_data.RPFW.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RPFC.value = (Uns8)(bport1_ab_data.RPFC.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SRS1.value = (Uns8)(bport1_ab_data.SRS1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SRS0.value = (Uns8)(bport1_ab_data.SRS0.value & ~(0xff)) | ((0xff) & (0x82));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the RCM peripheral used on the Freescale Kinetis platform");
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

