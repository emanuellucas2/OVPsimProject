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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisRFSYS", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abREGA_reg = ppmCreateRegister(
            "ab_REGA",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGA.value),
            True
        );

        ppmCreateRegisterField(abREGA_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGA_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGA_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGA_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGB_reg = ppmCreateRegister(
            "ab_REGB",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGB.value),
            True
        );

        ppmCreateRegisterField(abREGB_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGB_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGB_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGB_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGC_reg = ppmCreateRegister(
            "ab_REGC",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGC.value),
            True
        );

        ppmCreateRegisterField(abREGC_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGC_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGC_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGC_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGD_reg = ppmCreateRegister(
            "ab_REGD",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGD.value),
            True
        );

        ppmCreateRegisterField(abREGD_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGD_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGD_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGD_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGE_reg = ppmCreateRegister(
            "ab_REGE",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGE.value),
            True
        );

        ppmCreateRegisterField(abREGE_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGE_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGE_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGE_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGF_reg = ppmCreateRegister(
            "ab_REGF",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGF.value),
            True
        );

        ppmCreateRegisterField(abREGF_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGF_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGF_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGF_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGG_reg = ppmCreateRegister(
            "ab_REGG",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGG.value),
            True
        );

        ppmCreateRegisterField(abREGG_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGG_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGG_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGG_reg, "LL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abREGH_reg = ppmCreateRegister(
            "ab_REGH",
            "Register file register, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REGH.value),
            True
        );

        ppmCreateRegisterField(abREGH_reg, "HH", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abREGH_reg, "HL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abREGH_reg, "LH", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abREGH_reg, "LL", 0, 0, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.REGH.value = (Uns32)(bport1_ab_data.REGH.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGG.value = (Uns32)(bport1_ab_data.REGG.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGF.value = (Uns32)(bport1_ab_data.REGF.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGE.value = (Uns32)(bport1_ab_data.REGE.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGD.value = (Uns32)(bport1_ab_data.REGD.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGC.value = (Uns32)(bport1_ab_data.REGC.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGB.value = (Uns32)(bport1_ab_data.REGB.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.REGA.value = (Uns32)(bport1_ab_data.REGA.value & ~(0xffffffff)) | ((0xffffffff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the RFSYS peripheral used on the Freescale Kinetis platform");
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

