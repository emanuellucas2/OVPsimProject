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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisLPTMR", "Example");
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

static PPM_WRITE_CB(bport1_ab_CMR_maskWrite) {
    bport1_ab_data.CMR.value = (bport1_ab_data.CMR.value & BPORT1_AB_CMR_WRNMASK) | (data & BPORT1_AB_CMR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSR_maskWrite) {
    bport1_ab_data.CSR.value = (bport1_ab_data.CSR.value & BPORT1_AB_CSR_WRNMASK) | (data & BPORT1_AB_CSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PSR_maskWrite) {
    bport1_ab_data.PSR.value = (bport1_ab_data.PSR.value & BPORT1_AB_PSR_WRNMASK) | (data & BPORT1_AB_PSR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCSR_reg = ppmCreateRegister(
            "ab_CSR",
            "Low Power Timer Control Status Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_CSR_maskWrite,
            view32,
            &(bport1_ab_data.CSR.value),
            True
        );

        ppmCreateRegisterField(abCSR_reg, "TCF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCSR_reg, "TEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSR_reg, "TFC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCSR_reg, "TIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCSR_reg, "TMS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCSR_reg, "TPP", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSR_reg, "TPS", 0, 4, 2, 1, 1);
    }
    {
        registerHandle abPSR_reg = ppmCreateRegister(
            "ab_PSR",
            "Low Power Timer Prescale Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_PSR_maskWrite,
            view32,
            &(bport1_ab_data.PSR.value),
            True
        );

        ppmCreateRegisterField(abPSR_reg, "PBYP", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPSR_reg, "PCS", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abPSR_reg, "PRESCALE", 0, 3, 4, 1, 1);
    }
    {
        registerHandle abCMR_reg = ppmCreateRegister(
            "ab_CMR",
            "Low Power Timer Compare Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_CMR_maskWrite,
            view32,
            &(bport1_ab_data.CMR.value),
            True
        );

        ppmCreateRegisterField(abCMR_reg, "COMPARE", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCNR_reg = ppmCreateRegister(
            "ab_CNR",
            "Low Power Timer Counter Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNR.value),
            True
        );

        ppmCreateRegisterField(abCNR_reg, "COUNTER", 0, 0, 16, 1, 0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CNR.value = (Uns32)(bport1_ab_data.CNR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMR.value = (Uns32)(bport1_ab_data.CMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PSR.value = (Uns32)(bport1_ab_data.PSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSR.value = (Uns32)(bport1_ab_data.CSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the LPTMR peripheral used on the Freescale Kinetis platform");
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

