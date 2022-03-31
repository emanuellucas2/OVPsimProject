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

port0_reg_dataT port0_reg_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "NCEPLIC100", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.port0 = ppmCreateSlaveBusPort("port0", 4194304);

    ppmInstallNByteCallbacks(reservedRD, reservedWR, 0, handles.port0, 0x0, 0x400000, 1, 1, 1, BHM_ENDIAN_LITTLE);
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "PLIC Interrupt Controller");
        ppmDocAddText(doc_12_node, "Base riscv.ovpworld.org PLIC model plus these Andes extension features:");
        ppmDocAddText(doc_12_node, " - Software-programmable interrupt generation (writable pending registers)");
        ppmDocAddText(doc_12_node, " - Configurable interrupt trigger types");
        ppmDocAddText(doc_12_node, " - Preemptive priority interrupts");
        ppmDocAddText(doc_12_node, " - Vectored Interrupts");
        ppmDocAddText(doc_12_node, "If vectored interrupts are to be used then additional connections between the plic and processor are required. For an interrupt target port t<x>_eip connected to one of the M/S/UExternalInterrupt ports of a processor, the corresponding ports must be connected as follows:");
        ppmDocAddText(doc_12_node, " - The PLIC output port t<x>_eiid must be connected to the M/S/UExternalInterruptID processor port");
        ppmDocAddText(doc_12_node, " - The PLIC output port t<x>_eiack must be connected to the M/S/UExternalInterruptACK processor port");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "The ASYNC_INT configuration option is not configurable since the difference between asynch/synch behavior is not modeled by the simulator");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Various AndesCore Processor Data Sheets, e.g. AndesCore AX45MP Data Sheet V1.1 (DS185-11)");
        ppmDocAddText(doc_32_node, "AndeStar V5 Platform-Level Interrupt Controller Specification - UM166-13");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

