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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCMT", "Example");
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

static PPM_WRITE_CB(bport1_ab_CGH1_maskWrite) {
    bport1_ab_data.CGH1.value = (bport1_ab_data.CGH1.value & BPORT1_AB_CGH1_WRNMASK) | (data & BPORT1_AB_CGH1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CGH2_maskWrite) {
    bport1_ab_data.CGH2.value = (bport1_ab_data.CGH2.value & BPORT1_AB_CGH2_WRNMASK) | (data & BPORT1_AB_CGH2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CGL1_maskWrite) {
    bport1_ab_data.CGL1.value = (bport1_ab_data.CGL1.value & BPORT1_AB_CGL1_WRNMASK) | (data & BPORT1_AB_CGL1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CGL2_maskWrite) {
    bport1_ab_data.CGL2.value = (bport1_ab_data.CGL2.value & BPORT1_AB_CGL2_WRNMASK) | (data & BPORT1_AB_CGL2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMD1_maskWrite) {
    bport1_ab_data.CMD1.value = (bport1_ab_data.CMD1.value & BPORT1_AB_CMD1_WRNMASK) | (data & BPORT1_AB_CMD1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMD2_maskWrite) {
    bport1_ab_data.CMD2.value = (bport1_ab_data.CMD2.value & BPORT1_AB_CMD2_WRNMASK) | (data & BPORT1_AB_CMD2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMD3_maskWrite) {
    bport1_ab_data.CMD3.value = (bport1_ab_data.CMD3.value & BPORT1_AB_CMD3_WRNMASK) | (data & BPORT1_AB_CMD3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMD4_maskWrite) {
    bport1_ab_data.CMD4.value = (bport1_ab_data.CMD4.value & BPORT1_AB_CMD4_WRNMASK) | (data & BPORT1_AB_CMD4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DMA_maskWrite) {
    bport1_ab_data.DMA.value = (bport1_ab_data.DMA.value & BPORT1_AB_DMA_WRNMASK) | (data & BPORT1_AB_DMA_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MSC_maskWrite) {
    bport1_ab_data.MSC.value = (bport1_ab_data.MSC.value & BPORT1_AB_MSC_WRNMASK) | (data & BPORT1_AB_MSC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OC_maskWrite) {
    bport1_ab_data.OC.value = (bport1_ab_data.OC.value & BPORT1_AB_OC_WRNMASK) | (data & BPORT1_AB_OC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PPS_maskWrite) {
    bport1_ab_data.PPS.value = (bport1_ab_data.PPS.value & BPORT1_AB_PPS_WRNMASK) | (data & BPORT1_AB_PPS_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCGH1_reg = ppmCreateRegister(
            "ab_CGH1",
            "CMT Carrier Generator High Data Register 1, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_CGH1_maskWrite,
            view8,
            &(bport1_ab_data.CGH1.value),
            True
        );

        ppmCreateRegisterField(abCGH1_reg, "PH", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCGL1_reg = ppmCreateRegister(
            "ab_CGL1",
            "CMT Carrier Generator Low Data Register 1, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_CGL1_maskWrite,
            view8,
            &(bport1_ab_data.CGL1.value),
            True
        );

        ppmCreateRegisterField(abCGL1_reg, "PL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCGH2_reg = ppmCreateRegister(
            "ab_CGH2",
            "CMT Carrier Generator High Data Register 2, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_CGH2_maskWrite,
            view8,
            &(bport1_ab_data.CGH2.value),
            True
        );

        ppmCreateRegisterField(abCGH2_reg, "SH", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCGL2_reg = ppmCreateRegister(
            "ab_CGL2",
            "CMT Carrier Generator Low Data Register 2, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            bport1_ab_CGL2_maskWrite,
            view8,
            &(bport1_ab_data.CGL2.value),
            True
        );

        ppmCreateRegisterField(abCGL2_reg, "SL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abOC_reg = ppmCreateRegister(
            "ab_OC",
            "CMT Output Control Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_OC_maskWrite,
            view8,
            &(bport1_ab_data.OC.value),
            True
        );

        ppmCreateRegisterField(abOC_reg, "CMTPOL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abOC_reg, "IROL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abOC_reg, "IROPEN", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abMSC_reg = ppmCreateRegister(
            "ab_MSC",
            "CMT Modulator Status and Control Register, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_MSC_maskWrite,
            view8,
            &(bport1_ab_data.MSC.value),
            True
        );

        ppmCreateRegisterField(abMSC_reg, "BASE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abMSC_reg, "CMTDIV", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abMSC_reg, "EOCF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abMSC_reg, "EOCIE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abMSC_reg, "EXSPC", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abMSC_reg, "FSK", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abMSC_reg, "MCGEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCMD1_reg = ppmCreateRegister(
            "ab_CMD1",
            "CMT Modulator Data Register Mark High, offset: 0x6 ",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_CMD1_maskWrite,
            view8,
            &(bport1_ab_data.CMD1.value),
            True
        );

        ppmCreateRegisterField(abCMD1_reg, "MB", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCMD2_reg = ppmCreateRegister(
            "ab_CMD2",
            "CMT Modulator Data Register Mark Low, offset: 0x7 ",
            handles.bport1,
            0x7,
            1,
            read_8,
            bport1_ab_CMD2_maskWrite,
            view8,
            &(bport1_ab_data.CMD2.value),
            True
        );

        ppmCreateRegisterField(abCMD2_reg, "MB", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCMD3_reg = ppmCreateRegister(
            "ab_CMD3",
            "CMT Modulator Data Register Space High, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_CMD3_maskWrite,
            view8,
            &(bport1_ab_data.CMD3.value),
            True
        );

        ppmCreateRegisterField(abCMD3_reg, "SB", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abCMD4_reg = ppmCreateRegister(
            "ab_CMD4",
            "CMT Modulator Data Register Space Low, offset: 0x9 ",
            handles.bport1,
            0x9,
            1,
            read_8,
            bport1_ab_CMD4_maskWrite,
            view8,
            &(bport1_ab_data.CMD4.value),
            True
        );

        ppmCreateRegisterField(abCMD4_reg, "SB", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abPPS_reg = ppmCreateRegister(
            "ab_PPS",
            "CMT Primary Prescaler Register, offset: 0xA ",
            handles.bport1,
            0xa,
            1,
            read_8,
            bport1_ab_PPS_maskWrite,
            view8,
            &(bport1_ab_data.PPS.value),
            True
        );

        ppmCreateRegisterField(abPPS_reg, "PPSDIV", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDMA_reg = ppmCreateRegister(
            "ab_DMA",
            "CMT Direct Memory Access, offset: 0xB ",
            handles.bport1,
            0xb,
            1,
            read_8,
            bport1_ab_DMA_maskWrite,
            view8,
            &(bport1_ab_data.DMA.value),
            True
        );

        ppmCreateRegisterField(abDMA_reg, "DMA", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.DMA.value = (Uns8)(bport1_ab_data.DMA.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PPS.value = (Uns8)(bport1_ab_data.PPS.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.MSC.value = (Uns8)(bport1_ab_data.MSC.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.OC.value = (Uns8)(bport1_ab_data.OC.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the CMT peripheral used on the Freescale Kinetis platform");
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

