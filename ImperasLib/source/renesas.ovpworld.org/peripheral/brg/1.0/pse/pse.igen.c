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

BRGP0_reg0_dataT BRGP0_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "brg", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.BRGP0 = ppmCreateSlaveBusPort("BRGP0", 2);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0PRSM_reg = ppmCreateRegister(
            "reg0_PRSM",
            0,
            handles.BRGP0,
            0x0,
            1,
            read_8,
            writePRSM,
            view8,
            &(BRGP0_reg0_data.PRSM.value),
            True
        );

        ppmCreateRegisterField(reg0PRSM_reg, "BGCS", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(reg0PRSM_reg, "TODIS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0PRSM_reg, "BGCE", 0, 4, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg0_PRSCM",
            0,
            handles.BRGP0,
            0x1,
            1,
            read_8,
            writePRSCM,
            view8,
            &(BRGP0_reg0_data.PRSCM.value),
            True
        );
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        BRGP0_reg0_data.PRSCM.value = (Uns8)(BRGP0_reg0_data.PRSCM.value & ~(0xff)) | ((0xff) & (0x00));
        BRGP0_reg0_data.PRSM.value = (Uns8)(BRGP0_reg0_data.PRSM.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas BRG Baud Rate Generator");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Fully Supported");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

