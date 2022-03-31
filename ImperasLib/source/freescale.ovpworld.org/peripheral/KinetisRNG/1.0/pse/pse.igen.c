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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisRNG", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CR_maskWrite) {
    bport1_ab_data.CR.value = (bport1_ab_data.CR.value & BPORT1_AB_CR_WRNMASK) | (data & BPORT1_AB_CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ER_maskWrite) {
    bport1_ab_data.ER.value = (bport1_ab_data.ER.value & BPORT1_AB_ER_WRNMASK) | (data & BPORT1_AB_ER_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCR_reg = ppmCreateRegister(
            "ab_CR",
            "RNGA Control Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_CR_maskWrite,
            view32,
            &(bport1_ab_data.CR.value),
            True
        );

        ppmCreateRegisterField(abCR_reg, "CLRI", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "GO", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "HA", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "INTM", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SLP", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abSR_reg = ppmCreateRegister(
            "ab_SR",
            "RNGA Status Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SR.value),
            True
        );

        ppmCreateRegisterField(abSR_reg, "ERRI", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "LRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "OREG_LVL", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abSR_reg, "OREG_SIZE", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abSR_reg, "ORU", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "SECV", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "SLP", 0, 4, 1, 1, 0);
    }
    {
        registerHandle abER_reg = ppmCreateRegister(
            "ab_ER",
            "RNGA Entropy Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            0,
            bport1_ab_ER_maskWrite,
            view32,
            &(bport1_ab_data.ER.value),
            True
        );

        ppmCreateRegisterField(abER_reg, "EXT_ENT", 0, 0, 32, 0, 1);
    }
    {
        registerHandle abOR_reg = ppmCreateRegister(
            "ab_OR",
            "RNGA Output Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.OR.value),
            True
        );

        ppmCreateRegisterField(abOR_reg, "RANDOUT", 0, 0, 32, 1, 0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.OR.value = (Uns32)(bport1_ab_data.OR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ER.value = (Uns32)(bport1_ab_data.ER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SR.value = (Uns32)(bport1_ab_data.SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
        bport1_ab_data.CR.value = (Uns32)(bport1_ab_data.CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the RNG peripheral used on the Freescale Kinetis platform");
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

