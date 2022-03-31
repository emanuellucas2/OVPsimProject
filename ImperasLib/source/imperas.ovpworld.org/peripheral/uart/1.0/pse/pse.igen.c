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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "uart", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 32);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_rbr_dll",
            "UART Receiver Buffer Register",
            handles.bport1,
            0x0,
            1,
            readRBR_DLL,
            0,
            viewRBR_DLL,
            &(bport1_ab_data.rbr_dll.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_thr_dll",
            "UART Transmitter Register",
            handles.bport1,
            0x4,
            1,
            0,
            writeTHR_DLL,
            viewTHR_DLL,
            &(bport1_ab_data.thr_dll.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_sz",
            "UART Receive FIFO Fill Size Register",
            handles.bport1,
            0x8,
            1,
            readSZ,
            0,
            view8,
            &(bport1_ab_data.sz.value),
            True
        );
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.sz.value = (Uns8)(bport1_ab_data.sz.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.thr_dll.value = (Uns8)(bport1_ab_data.thr_dll.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.rbr_dll.value = (Uns8)(bport1_ab_data.rbr_dll.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Simple UART model");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base functionality to allow read/write character communication.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Example Linux Kernel Driver");
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
    destructor();
    return 0;
}

