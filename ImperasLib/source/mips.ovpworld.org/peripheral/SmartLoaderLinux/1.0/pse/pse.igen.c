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

idport_ab_dataT idport_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "SmartLoaderLinux", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.idport = ppmCreateSlaveBusPort("idport", 4);

    ppmInstallReadCallback(readBoardId, (void*)0 , handles.idport + 0x0, 0x4);
    ppmInstallWriteCallback(writeBoardId, (void*)0 , handles.idport + 0x0, 0x4);
}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.mport = ppmOpenAddressSpace("mport");
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Smart peripheral creates memory initialisation for a MIPS32 based Linux kernel boot.\n    Performs the generation of boot code at the reset vector (virtual address 0xbfc00000) of the MIPS32 processor. \n    Loads both the linux kernel and initial ramdisk into memory and patches the boot code to jump to the kernel start. \n    Initialises the MIPS32 registers and Linux command line.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "MIPS Malta User Manual. MIPS Boot code reference.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_32_node, "None");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installMasterPorts();
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

