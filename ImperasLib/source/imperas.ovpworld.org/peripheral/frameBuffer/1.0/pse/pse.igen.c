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

sp_A_dataT sp_A_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "frameBuffer", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp = ppmCreateSlaveBusPort("sp", 4096);
    if (!handles.sp) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'sp'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {


    {
        ppmCreateRegister(
            "A_FB_SET_BASE",
            0,
            handles.sp,
            0x0,
            4,
            0,
            writeBASE,
            view32,
            &(sp_A_data.FB_SET_BASE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "A_FB_SET_BLANK",
            0,
            handles.sp,
            0x10,
            4,
            0,
            writeBLANK,
            view32,
            &(sp_A_data.FB_SET_BLANK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "A_FB_SET_TITLE",
            0,
            handles.sp,
            0x20,
            4,
            0,
            writeTITLE,
            view32,
            &(sp_A_data.FB_SET_TITLE.value),
            True
        );
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        sp_A_data.FB_SET_TITLE.value = (Uns32)(sp_A_data.FB_SET_TITLE.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        sp_A_data.FB_SET_BLANK.value = (Uns32)(sp_A_data.FB_SET_BLANK.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        sp_A_data.FB_SET_BASE.value = (Uns32)(sp_A_data.FB_SET_BASE.value & ~(0xffffffff)) | ((0xffffffff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Provides Frame Buffer output.");
        ppmDocAddText(doc_12_node, "Supports frame buffer formats used in Neural Network demo application i.e. RGB565 16-bit float for Alexnet application.");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_reset(1,0);
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

