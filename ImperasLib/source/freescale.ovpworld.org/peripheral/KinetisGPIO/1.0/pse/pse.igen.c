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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisGPIO", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 64);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abPDOR_reg = ppmCreateRegister(
            "ab_PDOR",
            "Port Data Output Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            writeDOR,
            view32,
            &(bport1_ab_data.PDOR.value),
            True
        );

        ppmCreateRegisterField(abPDOR_reg, "PDO", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abPSOR_reg = ppmCreateRegister(
            "ab_PSOR",
            "Port Set Output Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            0,
            writeSOR,
            view32,
            &(bport1_ab_data.PSOR.value),
            True
        );

        ppmCreateRegisterField(abPSOR_reg, "PTSO", 0, 0, 32, 0, 1);
    }
    {
        registerHandle abPCOR_reg = ppmCreateRegister(
            "ab_PCOR",
            "Port Clear Output Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            0,
            writeCOR,
            view32,
            &(bport1_ab_data.PCOR.value),
            True
        );

        ppmCreateRegisterField(abPCOR_reg, "PTCO", 0, 0, 32, 0, 1);
    }
    {
        registerHandle abPTOR_reg = ppmCreateRegister(
            "ab_PTOR",
            "Port Toggle Output Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            0,
            writeTOR,
            view32,
            &(bport1_ab_data.PTOR.value),
            True
        );

        ppmCreateRegisterField(abPTOR_reg, "PTTO", 0, 0, 32, 0, 1);
    }
    {
        registerHandle abPDIR_reg = ppmCreateRegister(
            "ab_PDIR",
            "Port Data Input Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.PDIR.value),
            True
        );

        ppmCreateRegisterField(abPDIR_reg, "PDI", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abPDDR_reg = ppmCreateRegister(
            "ab_PDDR",
            "Port Data Direction Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            writeDDR,
            view32,
            &(bport1_ab_data.PDDR.value),
            True
        );

        ppmCreateRegisterField(abPDDR_reg, "PDD", 0, 0, 32, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PDDR.value = (Uns32)(bport1_ab_data.PDDR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PDIR.value = (Uns32)(bport1_ab_data.PDIR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PTOR.value = (Uns32)(bport1_ab_data.PTOR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PCOR.value = (Uns32)(bport1_ab_data.PCOR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PSOR.value = (Uns32)(bport1_ab_data.PSOR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.PDOR.value = (Uns32)(bport1_ab_data.PDOR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the GPIO peripheral used on the Freescale Kinetis platform");
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

