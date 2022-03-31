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

CONTROL_REGS_dataT CONTROL_REGS_data;

BLOCKER_REGS_dataT BLOCKER_REGS_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "DDRCTL", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.CONTROL = ppmCreateSlaveBusPort("CONTROL", 16384);
    if (!handles.CONTROL) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'CONTROL'");
    }

    ppmInstallNByteCallbacks(readControlMem, writeControlMem, 0, handles.CONTROL, 0x0, 0x4000, 1, 1, 1, BHM_ENDIAN_LITTLE);
    handles.BLOCKER = ppmCreateSlaveBusPort("BLOCKER", 8);
    if (!handles.BLOCKER) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'BLOCKER'");
    }

    ppmInstallNByteCallbacks(readBlockerMem, writeBlockerMem, 0, handles.BLOCKER, 0x0, 0x8, 1, 1, 1, BHM_ENDIAN_LITTLE);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateNByteRegister(
            "REGS_reg33",
            0,
            handles.CONTROL,
            0x84,
            4,
            0,
            writeMaskedControlReg,
            0,
            &(CONTROL_REGS_data.reg33.value),
            (void*)0xfffffeff,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }


}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "DDR Controller Register Block for SiFive FU540 chip");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_32_node, "Register only model. Register address space modeled as RAM except for registers that require write masks or reset values.");
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
    return 0;
}

