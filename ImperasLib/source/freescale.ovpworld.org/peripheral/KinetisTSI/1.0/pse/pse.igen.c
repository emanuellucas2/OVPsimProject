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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisTSI", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_GENCS_maskWrite) {
    bport1_ab_data.GENCS.value = (bport1_ab_data.GENCS.value & BPORT1_AB_GENCS_WRNMASK) | (data & BPORT1_AB_GENCS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PEN_maskWrite) {
    bport1_ab_data.PEN.value = (bport1_ab_data.PEN.value & BPORT1_AB_PEN_WRNMASK) | (data & BPORT1_AB_PEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCANC_maskWrite) {
    bport1_ab_data.SCANC.value = (bport1_ab_data.SCANC.value & BPORT1_AB_SCANC_WRNMASK) | (data & BPORT1_AB_SCANC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_THRESHOLD_maskWrite) {
    bport1_ab_data.THRESHOLD.value = (bport1_ab_data.THRESHOLD.value & BPORT1_AB_THRESHOLD_WRNMASK) | (data & BPORT1_AB_THRESHOLD_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abGENCS_reg = ppmCreateRegister(
            "ab_GENCS",
            "General Control and Status Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_GENCS_maskWrite,
            view32,
            &(bport1_ab_data.GENCS.value),
            True
        );

        ppmCreateRegisterField(abGENCS_reg, "EOSF", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "ERIE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "ESOR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "EXTERF", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "LPCLKS", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "LPSCNITV", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "NSCN", 0, 19, 5, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "OUTRGF", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "OVRF", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "PS", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "SCNIP", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "STM", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "STPE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "SWTS", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "TSIEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abGENCS_reg, "TSIIE", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abSCANC_reg = ppmCreateRegister(
            "ab_SCANC",
            "SCAN Control Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_SCANC_maskWrite,
            view32,
            &(bport1_ab_data.SCANC.value),
            True
        );

        ppmCreateRegisterField(abSCANC_reg, "AMCLKS", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(abSCANC_reg, "AMPSC", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abSCANC_reg, "EXTCHRG", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abSCANC_reg, "REFCHRG", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abSCANC_reg, "SMOD", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abPEN_reg = ppmCreateRegister(
            "ab_PEN",
            "Pin Enable Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_PEN_maskWrite,
            view32,
            &(bport1_ab_data.PEN.value),
            True
        );

        ppmCreateRegisterField(abPEN_reg, "LPSP", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPEN_reg, "PEN9", 0, 9, 1, 1, 1);
    }
    {
        registerHandle abWUCNTR_reg = ppmCreateRegister(
            "ab_WUCNTR",
            "Wake-Up Channel Counter Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.WUCNTR.value),
            True
        );

        ppmCreateRegisterField(abWUCNTR_reg, "WUCNT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCNTR1_reg = ppmCreateRegister(
            "ab_CNTR1",
            "Counter Register, offset: 0x100 ",
            handles.bport1,
            0x100,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR1.value),
            True
        );

        ppmCreateRegisterField(abCNTR1_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR1_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR3_reg = ppmCreateRegister(
            "ab_CNTR3",
            "Counter Register, offset: 0x104 ",
            handles.bport1,
            0x104,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR3.value),
            True
        );

        ppmCreateRegisterField(abCNTR3_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR3_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR5_reg = ppmCreateRegister(
            "ab_CNTR5",
            "Counter Register, offset: 0x108 ",
            handles.bport1,
            0x108,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR5.value),
            True
        );

        ppmCreateRegisterField(abCNTR5_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR5_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR7_reg = ppmCreateRegister(
            "ab_CNTR7",
            "Counter Register, offset: 0x10C ",
            handles.bport1,
            0x10c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR7.value),
            True
        );

        ppmCreateRegisterField(abCNTR7_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR7_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR9_reg = ppmCreateRegister(
            "ab_CNTR9",
            "Counter Register, offset: 0x110 ",
            handles.bport1,
            0x110,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR9.value),
            True
        );

        ppmCreateRegisterField(abCNTR9_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR9_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR11_reg = ppmCreateRegister(
            "ab_CNTR11",
            "Counter Register, offset: 0x114 ",
            handles.bport1,
            0x114,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR11.value),
            True
        );

        ppmCreateRegisterField(abCNTR11_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR11_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR13_reg = ppmCreateRegister(
            "ab_CNTR13",
            "Counter Register, offset: 0x118 ",
            handles.bport1,
            0x118,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR13.value),
            True
        );

        ppmCreateRegisterField(abCNTR13_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR13_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abCNTR15_reg = ppmCreateRegister(
            "ab_CNTR15",
            "Counter Register, offset: 0x11C ",
            handles.bport1,
            0x11c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CNTR15.value),
            True
        );

        ppmCreateRegisterField(abCNTR15_reg, "CTN", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abCNTR15_reg, "CTN1", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abTHRESHOLD_reg = ppmCreateRegister(
            "ab_THRESHOLD",
            "Low Power Channel Threshold Register, offset: 0x120 ",
            handles.bport1,
            0x120,
            4,
            read_32,
            bport1_ab_THRESHOLD_maskWrite,
            view32,
            &(bport1_ab_data.THRESHOLD.value),
            True
        );

        ppmCreateRegisterField(abTHRESHOLD_reg, "HTHH", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abTHRESHOLD_reg, "LTHH", 0, 16, 16, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.THRESHOLD.value = (Uns32)(bport1_ab_data.THRESHOLD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR15.value = (Uns32)(bport1_ab_data.CNTR15.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR13.value = (Uns32)(bport1_ab_data.CNTR13.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR11.value = (Uns32)(bport1_ab_data.CNTR11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR9.value = (Uns32)(bport1_ab_data.CNTR9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR7.value = (Uns32)(bport1_ab_data.CNTR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR5.value = (Uns32)(bport1_ab_data.CNTR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR3.value = (Uns32)(bport1_ab_data.CNTR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTR1.value = (Uns32)(bport1_ab_data.CNTR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.WUCNTR.value = (Uns32)(bport1_ab_data.WUCNTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PEN.value = (Uns32)(bport1_ab_data.PEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SCANC.value = (Uns32)(bport1_ab_data.SCANC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GENCS.value = (Uns32)(bport1_ab_data.GENCS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the TSI peripheral used on the Freescale Kinetis platform");
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

