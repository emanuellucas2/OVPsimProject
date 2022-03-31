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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "DebugLedAndDipSwitch", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_LED_ALPHA",
            "Alphanumeric Characters register",
            handles.bport1,
            0x0,
            4,
            read_32,
            writeAlpha,
            view32,
            &(bport1_ab_data.LED_ALPHA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LED_LIGHTS",
            "LED Control register",
            handles.bport1,
            0x4,
            4,
            read_32,
            writeLED,
            view32,
            &(bport1_ab_data.LED_LIGHTS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LED_SWITCHES",
            "DIP Switch register",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.LED_SWITCHES.value),
            True
        );
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.LED_SWITCHES.value = (Uns32)(bport1_ab_data.LED_SWITCHES.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.LED_LIGHTS.value = (Uns32)(bport1_ab_data.LED_LIGHTS.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.LED_ALPHA.value = (Uns32)(bport1_ab_data.LED_ALPHA.value & ~(0xffffffff)) | ((0xffffffff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM Integrator Board Debug LEDs and DIP Switch Interface");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
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
    periphConstructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

