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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisLLWU", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_F1_maskWrite) {
    bport1_ab_data.F1.value = (bport1_ab_data.F1.value & BPORT1_AB_F1_WRNMASK) | (data & BPORT1_AB_F1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_F2_maskWrite) {
    bport1_ab_data.F2.value = (bport1_ab_data.F2.value & BPORT1_AB_F2_WRNMASK) | (data & BPORT1_AB_F2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FILT1_maskWrite) {
    bport1_ab_data.FILT1.value = (bport1_ab_data.FILT1.value & BPORT1_AB_FILT1_WRNMASK) | (data & BPORT1_AB_FILT1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FILT2_maskWrite) {
    bport1_ab_data.FILT2.value = (bport1_ab_data.FILT2.value & BPORT1_AB_FILT2_WRNMASK) | (data & BPORT1_AB_FILT2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ME_maskWrite) {
    bport1_ab_data.ME.value = (bport1_ab_data.ME.value & BPORT1_AB_ME_WRNMASK) | (data & BPORT1_AB_ME_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PE1_maskWrite) {
    bport1_ab_data.PE1.value = (bport1_ab_data.PE1.value & BPORT1_AB_PE1_WRNMASK) | (data & BPORT1_AB_PE1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PE2_maskWrite) {
    bport1_ab_data.PE2.value = (bport1_ab_data.PE2.value & BPORT1_AB_PE2_WRNMASK) | (data & BPORT1_AB_PE2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PE3_maskWrite) {
    bport1_ab_data.PE3.value = (bport1_ab_data.PE3.value & BPORT1_AB_PE3_WRNMASK) | (data & BPORT1_AB_PE3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PE4_maskWrite) {
    bport1_ab_data.PE4.value = (bport1_ab_data.PE4.value & BPORT1_AB_PE4_WRNMASK) | (data & BPORT1_AB_PE4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RST_maskWrite) {
    bport1_ab_data.RST.value = (bport1_ab_data.RST.value & BPORT1_AB_RST_WRNMASK) | (data & BPORT1_AB_RST_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abPE1_reg = ppmCreateRegister(
            "ab_PE1",
            "LLWU Pin Enable 1 Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_PE1_maskWrite,
            view8,
            &(bport1_ab_data.PE1.value),
            True
        );

        ppmCreateRegisterField(abPE1_reg, "WUPE0", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abPE1_reg, "WUPE1", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abPE1_reg, "WUPE2", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPE1_reg, "WUPE3", 0, 6, 2, 1, 1);
    }
    {
        registerHandle abPE2_reg = ppmCreateRegister(
            "ab_PE2",
            "LLWU Pin Enable 2 Register, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_PE2_maskWrite,
            view8,
            &(bport1_ab_data.PE2.value),
            True
        );

        ppmCreateRegisterField(abPE2_reg, "WUPE4", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abPE2_reg, "WUPE5", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abPE2_reg, "WUPE6", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPE2_reg, "WUPE7", 0, 6, 2, 1, 1);
    }
    {
        registerHandle abPE3_reg = ppmCreateRegister(
            "ab_PE3",
            "LLWU Pin Enable 3 Register, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_PE3_maskWrite,
            view8,
            &(bport1_ab_data.PE3.value),
            True
        );

        ppmCreateRegisterField(abPE3_reg, "WUPE10", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPE3_reg, "WUPE11", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abPE3_reg, "WUPE8", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abPE3_reg, "WUPE9", 0, 2, 2, 1, 1);
    }
    {
        registerHandle abPE4_reg = ppmCreateRegister(
            "ab_PE4",
            "LLWU Pin Enable 4 Register, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            bport1_ab_PE4_maskWrite,
            view8,
            &(bport1_ab_data.PE4.value),
            True
        );

        ppmCreateRegisterField(abPE4_reg, "WUPE12", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abPE4_reg, "WUPE13", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abPE4_reg, "WUPE14", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPE4_reg, "WUPE15", 0, 6, 2, 1, 1);
    }
    {
        registerHandle abME_reg = ppmCreateRegister(
            "ab_ME",
            "LLWU Module Enable Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_ME_maskWrite,
            view8,
            &(bport1_ab_data.ME.value),
            True
        );

        ppmCreateRegisterField(abME_reg, "WUME0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abME_reg, "WUME7", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abF1_reg = ppmCreateRegister(
            "ab_F1",
            "LLWU Flag 1 Register, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_F1_maskWrite,
            view8,
            &(bport1_ab_data.F1.value),
            True
        );

        ppmCreateRegisterField(abF1_reg, "WUF0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abF1_reg, "WUF7", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abF2_reg = ppmCreateRegister(
            "ab_F2",
            "LLWU Flag 2 Register, offset: 0x6 ",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_F2_maskWrite,
            view8,
            &(bport1_ab_data.F2.value),
            True
        );

        ppmCreateRegisterField(abF2_reg, "WUF10", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF11", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF12", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF13", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF14", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF15", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF8", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abF2_reg, "WUF9", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abF3_reg = ppmCreateRegister(
            "ab_F3",
            "LLWU Flag 3 Register, offset: 0x7 ",
            handles.bport1,
            0x7,
            1,
            read_8,
            write_8,
            view8,
            &(bport1_ab_data.F3.value),
            True
        );

        ppmCreateRegisterField(abF3_reg, "MWUF0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abF3_reg, "MWUF7", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abFILT1_reg = ppmCreateRegister(
            "ab_FILT1",
            "LLWU Pin Filter 1 Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_FILT1_maskWrite,
            view8,
            &(bport1_ab_data.FILT1.value),
            True
        );

        ppmCreateRegisterField(abFILT1_reg, "FILTE", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abFILT1_reg, "FILTF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFILT1_reg, "FILTSEL", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abFILT2_reg = ppmCreateRegister(
            "ab_FILT2",
            "LLWU Pin Filter 2 Register, offset: 0x9 ",
            handles.bport1,
            0x9,
            1,
            read_8,
            bport1_ab_FILT2_maskWrite,
            view8,
            &(bport1_ab_data.FILT2.value),
            True
        );

        ppmCreateRegisterField(abFILT2_reg, "FILTE", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abFILT2_reg, "FILTF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFILT2_reg, "FILTSEL", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abRST_reg = ppmCreateRegister(
            "ab_RST",
            "LLWU Reset Enable Register, offset: 0xA ",
            handles.bport1,
            0xa,
            1,
            read_8,
            bport1_ab_RST_maskWrite,
            view8,
            &(bport1_ab_data.RST.value),
            True
        );

        ppmCreateRegisterField(abRST_reg, "LLRSTE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abRST_reg, "RSTFILT", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.RST.value = (Uns8)(bport1_ab_data.RST.value & ~(0xff)) | ((0xff) & (0x02));
        bport1_ab_data.FILT2.value = (Uns8)(bport1_ab_data.FILT2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FILT1.value = (Uns8)(bport1_ab_data.FILT1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.F3.value = (Uns8)(bport1_ab_data.F3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.F2.value = (Uns8)(bport1_ab_data.F2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.F1.value = (Uns8)(bport1_ab_data.F1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ME.value = (Uns8)(bport1_ab_data.ME.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PE4.value = (Uns8)(bport1_ab_data.PE4.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PE3.value = (Uns8)(bport1_ab_data.PE3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PE2.value = (Uns8)(bport1_ab_data.PE2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PE1.value = (Uns8)(bport1_ab_data.PE1.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the LLWU peripheral used on the Freescale Kinetis platform");
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

