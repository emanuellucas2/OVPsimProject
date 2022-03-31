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

bport1_reg_dataT bport1_reg_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "8253", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateNByteRegister(
            "reg_CTR0",
            0,
            handles.bport1,
            0x0,
            1,
            readCTR,
            writeCTR,
            0,
            &(bport1_reg_data.CTR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg_CTR1",
            0,
            handles.bport1,
            0x1,
            1,
            readCTR,
            writeCTR,
            0,
            &(bport1_reg_data.CTR[1].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg_CTR2",
            0,
            handles.bport1,
            0x2,
            1,
            readCTR,
            writeCTR,
            0,
            &(bport1_reg_data.CTR[2].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        registerHandle regCNTL_reg = ppmCreateNByteRegister(
            "reg_CNTL",
            0,
            handles.bport1,
            0x3,
            1,
            readCNTL,
            writeCNTL,
            0,
            &(bport1_reg_data.CNTL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(regCNTL_reg, "BCD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(regCNTL_reg, "M", 0, 1, 3, 1, 1);
        ppmCreateRegisterField(regCNTL_reg, "RW", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(regCNTL_reg, "SC", 0, 6, 2, 1, 1);
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Intel 8253 Programmable Interval Timer (PIT)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform.\n           Not all modes are supported.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Intel 8253 Datasheet. MIPS Malta Platform Reference Guide.");
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

