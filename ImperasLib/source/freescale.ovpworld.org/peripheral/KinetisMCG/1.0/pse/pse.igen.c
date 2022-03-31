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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisMCG", "Example");
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

static PPM_WRITE_CB(bport1_ab_ATCVH_maskWrite) {
    bport1_ab_data.ATCVH.value = (bport1_ab_data.ATCVH.value & BPORT1_AB_ATCVH_WRNMASK) | (data & BPORT1_AB_ATCVH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ATCVL_maskWrite) {
    bport1_ab_data.ATCVL.value = (bport1_ab_data.ATCVL.value & BPORT1_AB_ATCVL_WRNMASK) | (data & BPORT1_AB_ATCVL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C10_maskWrite) {
    bport1_ab_data.C10.value = (bport1_ab_data.C10.value & BPORT1_AB_C10_WRNMASK) | (data & BPORT1_AB_C10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C11_maskWrite) {
    bport1_ab_data.C11.value = (bport1_ab_data.C11.value & BPORT1_AB_C11_WRNMASK) | (data & BPORT1_AB_C11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C12_maskWrite) {
    bport1_ab_data.C12.value = (bport1_ab_data.C12.value & BPORT1_AB_C12_WRNMASK) | (data & BPORT1_AB_C12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & BPORT1_AB_C1_WRNMASK) | (data & BPORT1_AB_C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C2_maskWrite) {
    bport1_ab_data.C2.value = (bport1_ab_data.C2.value & BPORT1_AB_C2_WRNMASK) | (data & BPORT1_AB_C2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C3_maskWrite) {
    bport1_ab_data.C3.value = (bport1_ab_data.C3.value & BPORT1_AB_C3_WRNMASK) | (data & BPORT1_AB_C3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C4_maskWrite) {
    bport1_ab_data.C4.value = (bport1_ab_data.C4.value & BPORT1_AB_C4_WRNMASK) | (data & BPORT1_AB_C4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C5_maskWrite) {
    bport1_ab_data.C5.value = (bport1_ab_data.C5.value & BPORT1_AB_C5_WRNMASK) | (data & BPORT1_AB_C5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C6_maskWrite) {
    bport1_ab_data.C6.value = (bport1_ab_data.C6.value & BPORT1_AB_C6_WRNMASK) | (data & BPORT1_AB_C6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C7_maskWrite) {
    bport1_ab_data.C7.value = (bport1_ab_data.C7.value & BPORT1_AB_C7_WRNMASK) | (data & BPORT1_AB_C7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C8_maskWrite) {
    bport1_ab_data.C8.value = (bport1_ab_data.C8.value & BPORT1_AB_C8_WRNMASK) | (data & BPORT1_AB_C8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SC_maskWrite) {
    bport1_ab_data.SC.value = (bport1_ab_data.SC.value & BPORT1_AB_SC_WRNMASK) | (data & BPORT1_AB_SC_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abC1_reg = ppmCreateRegister(
            "ab_C1",
            "MCG Control 1 Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_C1_maskWrite,
            view8,
            &(bport1_ab_data.C1.value),
            True
        );

        ppmCreateRegisterField(abC1_reg, "CLKS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abC1_reg, "FRDIV", 0, 3, 3, 1, 1);
        ppmCreateRegisterField(abC1_reg, "IRCLKEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "IREFS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "IREFSTEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abC2_reg = ppmCreateRegister(
            "ab_C2",
            "MCG Control 2 Register, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_C2_maskWrite,
            view8,
            &(bport1_ab_data.C2.value),
            True
        );

        ppmCreateRegisterField(abC2_reg, "EREFS0", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "HGO0", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "IRCS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "LOCRE0", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "LP", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "RANGE0", 0, 4, 2, 1, 1);
    }
    {
        registerHandle abC3_reg = ppmCreateRegister(
            "ab_C3",
            "MCG Control 3 Register, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_C3_maskWrite,
            view8,
            &(bport1_ab_data.C3.value),
            True
        );

        ppmCreateRegisterField(abC3_reg, "SCTRIM", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abC4_reg = ppmCreateRegister(
            "ab_C4",
            "MCG Control 4 Register, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            bport1_ab_C4_maskWrite,
            view8,
            &(bport1_ab_data.C4.value),
            True
        );

        ppmCreateRegisterField(abC4_reg, "DMX32", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC4_reg, "DRST_DRS", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abC4_reg, "FCTRIM", 0, 1, 4, 1, 1);
        ppmCreateRegisterField(abC4_reg, "SCFTRIM", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abC5_reg = ppmCreateRegister(
            "ab_C5",
            "MCG Control 5 Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_C5_maskWrite,
            view8,
            &(bport1_ab_data.C5.value),
            True
        );

        ppmCreateRegisterField(abC5_reg, "PLLCLKEN0", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC5_reg, "PLLREFSEL0", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC5_reg, "PLLSTEN0", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC5_reg, "PRDIV0", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abC6_reg = ppmCreateRegister(
            "ab_C6",
            "MCG Control 6 Register, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_C6_maskWrite,
            view8,
            &(bport1_ab_data.C6.value),
            True
        );

        ppmCreateRegisterField(abC6_reg, "CME0", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC6_reg, "LOLIE0", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC6_reg, "PLLS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC6_reg, "VDIV0", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abS_reg = ppmCreateRegister(
            "ab_S",
            "MCG Status Register, offset: 0x6 ",
            handles.bport1,
            0x6,
            1,
            readS,
            0,
            viewS,
            &(bport1_ab_data.S.value),
            True
        );

        ppmCreateRegisterField(abS_reg, "CLKST", 0, 2, 2, 1, 0);
        ppmCreateRegisterField(abS_reg, "IRCST", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abS_reg, "IREFST", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abS_reg, "LOCK0", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abS_reg, "LOLS0", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abS_reg, "OSCINIT0", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abS_reg, "PLLST", 0, 5, 1, 1, 0);
    }
    {
        registerHandle abSC_reg = ppmCreateRegister(
            "ab_SC",
            "MCG Status and Control Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_SC_maskWrite,
            view8,
            &(bport1_ab_data.SC.value),
            True
        );

        ppmCreateRegisterField(abSC_reg, "ATME", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "ATMF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "ATMS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "FCIRDIV", 0, 1, 3, 1, 1);
        ppmCreateRegisterField(abSC_reg, "FLTPRSRV", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "LOCS0", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abATCVH_reg = ppmCreateRegister(
            "ab_ATCVH",
            "MCG Auto Trim Compare Value High Register, offset: 0xA ",
            handles.bport1,
            0xa,
            1,
            read_8,
            bport1_ab_ATCVH_maskWrite,
            view8,
            &(bport1_ab_data.ATCVH.value),
            True
        );

        ppmCreateRegisterField(abATCVH_reg, "ATCVH", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abATCVL_reg = ppmCreateRegister(
            "ab_ATCVL",
            "MCG Auto Trim Compare Value Low Register, offset: 0xB ",
            handles.bport1,
            0xb,
            1,
            read_8,
            bport1_ab_ATCVL_maskWrite,
            view8,
            &(bport1_ab_data.ATCVL.value),
            True
        );

        ppmCreateRegisterField(abATCVL_reg, "ATCVL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abC7_reg = ppmCreateRegister(
            "ab_C7",
            "MCG Control 7 Register, offset: 0xC ",
            handles.bport1,
            0xc,
            1,
            read_8,
            bport1_ab_C7_maskWrite,
            view8,
            &(bport1_ab_data.C7.value),
            True
        );

        ppmCreateRegisterField(abC7_reg, "OSCSEL", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abC8_reg = ppmCreateRegister(
            "ab_C8",
            "MCG Control 8 Register, offset: 0xD ",
            handles.bport1,
            0xd,
            1,
            read_8,
            bport1_ab_C8_maskWrite,
            view8,
            &(bport1_ab_data.C8.value),
            True
        );

        ppmCreateRegisterField(abC8_reg, "CME1", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC8_reg, "LOCRE1", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC8_reg, "LOCS1", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abC10_reg = ppmCreateRegister(
            "ab_C10",
            "MCG Control 10 Register, offset: 0xF ",
            handles.bport1,
            0xf,
            1,
            read_8,
            bport1_ab_C10_maskWrite,
            view8,
            &(bport1_ab_data.C10.value),
            True
        );

        ppmCreateRegisterField(abC10_reg, "EREFS1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC10_reg, "HGO1", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC10_reg, "LOCRE2", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC10_reg, "RANGE1", 0, 4, 2, 1, 1);
    }
    {
        registerHandle abC11_reg = ppmCreateRegister(
            "ab_C11",
            "MCG Control 11 Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            1,
            read_8,
            bport1_ab_C11_maskWrite,
            view8,
            &(bport1_ab_data.C11.value),
            True
        );

        ppmCreateRegisterField(abC11_reg, "PLLCLKEN1", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC11_reg, "PLLCS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC11_reg, "PLLREFSEL1", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC11_reg, "PLLSTEN1", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC11_reg, "PRDIV1", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abC12_reg = ppmCreateRegister(
            "ab_C12",
            "MCG Control 12 Register, offset: 0x11 ",
            handles.bport1,
            0x11,
            1,
            read_8,
            bport1_ab_C12_maskWrite,
            view8,
            &(bport1_ab_data.C12.value),
            True
        );

        ppmCreateRegisterField(abC12_reg, "CME2", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC12_reg, "LOLIE1", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC12_reg, "VDIV1", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abS2_reg = ppmCreateRegister(
            "ab_S2",
            "MCG Status 2 Register, offset: 0x12 ",
            handles.bport1,
            0x12,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.S2.value),
            True
        );

        ppmCreateRegisterField(abS2_reg, "LOCK2", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abS2_reg, "LOCS2", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abS2_reg, "LOLS2", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abS2_reg, "OSCINIT2", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abS2_reg, "PLLCST", 0, 4, 1, 1, 0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.S2.value = (Uns8)(bport1_ab_data.S2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C12.value = (Uns8)(bport1_ab_data.C12.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C11.value = (Uns8)(bport1_ab_data.C11.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C10.value = (Uns8)(bport1_ab_data.C10.value & ~(0xff)) | ((0xff) & (0x80));
        bport1_ab_data.C8.value = (Uns8)(bport1_ab_data.C8.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C7.value = (Uns8)(bport1_ab_data.C7.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ATCVL.value = (Uns8)(bport1_ab_data.ATCVL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ATCVH.value = (Uns8)(bport1_ab_data.ATCVH.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SC.value = (Uns8)(bport1_ab_data.SC.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.S.value = (Uns8)(bport1_ab_data.S.value & ~(0xff)) | ((0xff) & (0x6a));
        bport1_ab_data.C6.value = (Uns8)(bport1_ab_data.C6.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C5.value = (Uns8)(bport1_ab_data.C5.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C4.value = (Uns8)(bport1_ab_data.C4.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C2.value = (Uns8)(bport1_ab_data.C2.value & ~(0xff)) | ((0xff) & (0x80));
        bport1_ab_data.C1.value = (Uns8)(bport1_ab_data.C1.value & ~(0xff)) | ((0xff) & (0x04));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Freescale Multipurpose Clock Generator");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Only models status register reads, based on writes to configuration registers\n\natc register ATME bit is modeled as RAZ/WI");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Freescale Kinetis MCG");
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

