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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCMP", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CR0_maskWrite) {
    bport1_ab_data.CR0.value = (bport1_ab_data.CR0.value & BPORT1_AB_CR0_WRNMASK) | (data & BPORT1_AB_CR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FPR_maskWrite) {
    bport1_ab_data.FPR.value = (bport1_ab_data.FPR.value & BPORT1_AB_FPR_WRNMASK) | (data & BPORT1_AB_FPR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 8);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCR0_reg = ppmCreateRegister(
            "ab_CR0",
            "CMP Control Register 0, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_CR0_maskWrite,
            view8,
            &(bport1_ab_data.CR0.value),
            True
        );

        ppmCreateRegisterField(abCR0_reg, "FILTER_CNT", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abCR0_reg, "HYSTCTR", 0, 0, 2, 1, 1);
    }
    {
        registerHandle abCR1_reg = ppmCreateRegister(
            "ab_CR1",
            "CMP Control Register 1, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            writeCR1,
            view8,
            &(bport1_ab_data.CR1.value),
            True
        );

        ppmCreateRegisterField(abCR1_reg, "COS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCR1_reg, "EN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR1_reg, "INV", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCR1_reg, "OPE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCR1_reg, "PMODE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCR1_reg, "SE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCR1_reg, "WE", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abFPR_reg = ppmCreateRegister(
            "ab_FPR",
            "CMP Filter Period Register, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_FPR_maskWrite,
            view8,
            &(bport1_ab_data.FPR.value),
            True
        );

        ppmCreateRegisterField(abFPR_reg, "FILT_PER", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abSCR_reg = ppmCreateRegister(
            "ab_SCR",
            "CMP Status and Control Register, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            writeSCR,
            view8,
            &(bport1_ab_data.SCR.value),
            True
        );

        ppmCreateRegisterField(abSCR_reg, "CFF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSCR_reg, "CFR", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSCR_reg, "COUT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSCR_reg, "DMAEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSCR_reg, "IEF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSCR_reg, "IER", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abDACCR_reg = ppmCreateRegister(
            "ab_DACCR",
            "DAC Control Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            writeDAC,
            view8,
            &(bport1_ab_data.DACCR.value),
            True
        );

        ppmCreateRegisterField(abDACCR_reg, "DACEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abDACCR_reg, "VOSEL", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abDACCR_reg, "VRSEL", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abMUXCR_reg = ppmCreateRegister(
            "ab_MUXCR",
            "MUX Control Register, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            writeMUX,
            view8,
            &(bport1_ab_data.MUXCR.value),
            True
        );

        ppmCreateRegisterField(abMUXCR_reg, "MSEL", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abMUXCR_reg, "PSEL", 0, 3, 3, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.MUXCR.value = (Uns8)(bport1_ab_data.MUXCR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DACCR.value = (Uns8)(bport1_ab_data.DACCR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SCR.value = (Uns8)(bport1_ab_data.SCR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FPR.value = (Uns8)(bport1_ab_data.FPR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.CR1.value = (Uns8)(bport1_ab_data.CR1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.CR0.value = (Uns8)(bport1_ab_data.CR0.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the CMP peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

