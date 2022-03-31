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

BCUP0_reg0_dataT BCUP0_reg0_data;

BCUP0_reg1_dataT BCUP0_reg1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "bcu", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.BCUP0 = ppmCreateSlaveBusPort("BCUP0", 16);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0CSC0_reg = ppmCreateRegister(
            "reg0_CSC0",
            0,
            handles.BCUP0,
            0x0,
            2,
            read_16,
            writeCSCO,
            view16,
            &(BCUP0_reg0_data.CSC0.value),
            True
        );

        ppmCreateRegisterField(reg0CSC0_reg, "CS0", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg0CSC0_reg, "CS1", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(reg0CSC0_reg, "CS2", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(reg0CSC0_reg, "CS3", 0, 12, 4, 1, 1);
    }
    {
        registerHandle reg0CSC1_reg = ppmCreateRegister(
            "reg0_CSC1",
            0,
            handles.BCUP0,
            0x2,
            2,
            read_16,
            writeCSC1,
            view16,
            &(BCUP0_reg0_data.CSC1.value),
            True
        );

        ppmCreateRegisterField(reg0CSC1_reg, "CS7", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg0CSC1_reg, "CS6", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(reg0CSC1_reg, "CS5", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(reg0CSC1_reg, "CS4", 0, 12, 4, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg0_BPC",
            0,
            handles.BCUP0,
            0x4,
            2,
            read_16,
            writeBPC,
            view16,
            &(BCUP0_reg0_data.BPC.value),
            True
        );
    }
    {
        registerHandle reg0BSC_reg = ppmCreateRegister(
            "reg0_BSC",
            0,
            handles.BCUP0,
            0x6,
            2,
            read_16,
            writeBSC,
            view16,
            &(BCUP0_reg0_data.BSC.value),
            True
        );

        ppmCreateRegisterField(reg0BSC_reg, "BS0", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS1", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS2", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS3", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS4", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS5", 0, 10, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS6", 0, 12, 2, 1, 1);
        ppmCreateRegisterField(reg0BSC_reg, "BS7", 0, 14, 2, 1, 1);
    }
    {
        registerHandle reg0BEC_reg = ppmCreateRegister(
            "reg0_BEC",
            0,
            handles.BCUP0,
            0x8,
            2,
            read_16,
            writeBEC,
            view16,
            &(BCUP0_reg0_data.BEC.value),
            True
        );

        ppmCreateRegisterField(reg0BEC_reg, "BE00", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE10", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE20", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE30", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE40", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE50", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE60", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(reg0BEC_reg, "BE70", 0, 14, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg1_VSWC",
            0,
            handles.BCUP0,
            0xf,
            1,
            read_8,
            writeVSWC,
            view8,
            &(BCUP0_reg1_data.VSWC.value),
            True
        );
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        BCUP0_reg1_data.VSWC.value = (Uns8)(BCUP0_reg1_data.VSWC.value & ~(0xff)) | ((0xff) & (0x77));
        BCUP0_reg0_data.BEC.value = (Uns16)(BCUP0_reg0_data.BEC.value & ~(0xffff)) | ((0xffff) & (0x0000));
        BCUP0_reg0_data.BSC.value = (Uns16)(BCUP0_reg0_data.BSC.value & ~(0xffff)) | ((0xffff) & (0xAAAA));
        BCUP0_reg0_data.BPC.value = (Uns16)(BCUP0_reg0_data.BPC.value & ~(0xffff)) | ((0xffff) & (0x0000));
        BCUP0_reg0_data.CSC1.value = (Uns16)(BCUP0_reg0_data.CSC1.value & ~(0xffff)) | ((0xffff) & (0x2C11));
        BCUP0_reg0_data.CSC0.value = (Uns16)(BCUP0_reg0_data.CSC0.value & ~(0xffff)) | ((0xffff) & (0x2C11));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas BCU Bus Control Unit");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Register View Model Only");
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

