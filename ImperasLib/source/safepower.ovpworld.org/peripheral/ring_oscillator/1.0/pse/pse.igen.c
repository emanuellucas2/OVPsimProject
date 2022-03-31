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

bport1_REG_dataT bport1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "ring_oscillator", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "REG_COUNT",
            "Count Value (default 2097152 = 25oC)",
            handles.bport1,
            0x0,
            4,
            ReadCOUNT,
            0,
            view32,
            &(bport1_REG_data.COUNT.value),
            True
        );
    }
    {
        registerHandle REGINIT_TIME_reg = ppmCreateRegister(
            "REG_INIT_TIME",
            "Init Time and Control",
            handles.bport1,
            0x4,
            4,
            ReadINIT_TIME,
            WriteINIT_TIME,
            view32,
            &(bport1_REG_data.INIT_TIME.value),
            True
        );

        ppmCreateRegisterField(REGINIT_TIME_reg, "INIT", 0, 8, 24, 1, 1);
        ppmCreateRegisterField(REGINIT_TIME_reg, "CTRL", 0, 0, 8, 1, 1);
    }
    {
        ppmCreateRegister(
            "REG_CAPTURE_TIME",
            "Capture Time",
            handles.bport1,
            0x8,
            4,
            ReadCAPTURE_TIME,
            WriteCAPTURE_TIME,
            view32,
            &(bport1_REG_data.CAPTURE_TIME.value),
            True
        );
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.rocount = ppmOpenAddressSpace("rocount");
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_REG_data.CAPTURE_TIME.value = (Uns32)(bport1_REG_data.CAPTURE_TIME.value & ~(0xffffffff)) | ((0xffffffff) & (0x0010ff00));
        bport1_REG_data.INIT_TIME.value = (Uns32)(bport1_REG_data.INIT_TIME.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.COUNT.value = (Uns32)(bport1_REG_data.COUNT.value & ~(0xffffffff)) | ((0xffffffff) & (2097152));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Ring Oscillator");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is a register only model that returns the COUNT value from a memory location.");
        ppmDocAddText(doc_22_node, "No behavior is currently included in the model, the COUNT register value is provided by a memory location, initialized to (2097152 = 25oC).");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Ikerlan");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    reset_resetNet(1,0);
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

