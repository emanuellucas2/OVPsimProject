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

sp1_reg_dataT sp1_reg_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "axi-gpio", "Example");
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
    handles.sp1 = ppmCreateSlaveBusPort("sp1", 512);
    if (!handles.sp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'sp1'");
    }

    ppmInstallChangeCallback(writeData, (void*)0 , handles.sp1 + 0x0, 0x4);
    ppmInstallChangeCallback(writeData2, (void*)0 , handles.sp1 + 0x8, 0x4);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "reg_gpio_tri",
            0,
            handles.sp1,
            0x4,
            4,
            read_32,
            writeTri,
            view32,
            &(sp1_reg_data.gpio_tri.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_gpio2_tri",
            0,
            handles.sp1,
            0xc,
            4,
            read_32,
            writeTri2,
            view32,
            &(sp1_reg_data.gpio2_tri.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_gier",
            0,
            handles.sp1,
            0x11c,
            4,
            readGier,
            writeGier,
            view32,
            &(sp1_reg_data.gier.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_ip_ier",
            0,
            handles.sp1,
            0x128,
            4,
            readIer,
            writeIer,
            view32,
            &(sp1_reg_data.ip_ier.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_ip_isr",
            0,
            handles.sp1,
            0x120,
            4,
            readIsr,
            writeIsr,
            view32,
            &(sp1_reg_data.ip_isr.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Xilinx AXI General Purpose IO");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the AXI GPIO");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "pg144-axi-gpio Vivado Design Suite October 5, 2016");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
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

