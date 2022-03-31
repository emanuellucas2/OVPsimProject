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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridADC", "Example");
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

static PPM_WRITE_CB(bport1_ab_CAL_maskWrite) {
    bport1_ab_data.CAL.value = (bport1_ab_data.CAL.value & BPORT1_AB_CAL_WRNMASK) | (data & BPORT1_AB_CAL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CFG_maskWrite) {
    bport1_ab_data.CFG.value = (bport1_ab_data.CFG.value & BPORT1_AB_CFG_WRNMASK) | (data & BPORT1_AB_CFG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CV_maskWrite) {
    bport1_ab_data.CV.value = (bport1_ab_data.CV.value & BPORT1_AB_CV_WRNMASK) | (data & BPORT1_AB_CV_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GC_maskWrite) {
    bport1_ab_data.GC.value = (bport1_ab_data.GC.value & BPORT1_AB_GC_WRNMASK) | (data & BPORT1_AB_GC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_HC0_maskWrite) {
    bport1_ab_data.HC0.value = (bport1_ab_data.HC0.value & BPORT1_AB_HC0_WRNMASK) | (data & BPORT1_AB_HC0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_HC1_maskWrite) {
    bport1_ab_data.HC1.value = (bport1_ab_data.HC1.value & BPORT1_AB_HC1_WRNMASK) | (data & BPORT1_AB_HC1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OFS_maskWrite) {
    bport1_ab_data.OFS.value = (bport1_ab_data.OFS.value & BPORT1_AB_OFS_WRNMASK) | (data & BPORT1_AB_OFS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCTL_maskWrite) {
    bport1_ab_data.PCTL.value = (bport1_ab_data.PCTL.value & BPORT1_AB_PCTL_WRNMASK) | (data & BPORT1_AB_PCTL_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abHC0_reg = ppmCreateRegister(
            "ab_HC0",
            "Control register for hardware triggers, offset: 0x0",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_HC0_maskWrite,
            view32,
            &(bport1_ab_data.HC0.value),
            True
        );

        ppmCreateRegisterField(abHC0_reg, "ADCH", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abHC0_reg, "AIEN", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abHC1_reg = ppmCreateRegister(
            "ab_HC1",
            "Control register for hardware triggers, offset: 0x4",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_HC1_maskWrite,
            view32,
            &(bport1_ab_data.HC1.value),
            True
        );

        ppmCreateRegisterField(abHC1_reg, "ADCH", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abHC1_reg, "AIEN", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abHS_reg = ppmCreateRegister(
            "ab_HS",
            "Status register for HW triggers, offset: 0x8",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HS.value),
            True
        );

        ppmCreateRegisterField(abHS_reg, "COCO1", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abHS_reg, "COCO2", 0, 1, 1, 1, 0);
    }
    {
        registerHandle abR0_reg = ppmCreateRegister(
            "ab_R0",
            "Data result register for HW triggers, offset: 0xC",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.R0.value),
            True
        );

        ppmCreateRegisterField(abR0_reg, "D", 0, 0, 12, 1, 1);
    }
    {
        registerHandle abR1_reg = ppmCreateRegister(
            "ab_R1",
            "Data result register for HW triggers, offset: 0x10",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.R1.value),
            True
        );

        ppmCreateRegisterField(abR1_reg, "D", 0, 0, 12, 1, 1);
    }
    {
        registerHandle abCFG_reg = ppmCreateRegister(
            "ab_CFG",
            "Configuration register, offset: 0x14",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_CFG_maskWrite,
            view32,
            &(bport1_ab_data.CFG.value),
            True
        );

        ppmCreateRegisterField(abCFG_reg, "ADHSC", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ADICLK", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ADIV", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ADLPC", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ADLSMP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ADSTS", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ADTRG", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "AVGS", 0, 14, 2, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "MODE", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "OVWREN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "REFSEL", 0, 11, 2, 1, 1);
    }
    {
        registerHandle abGC_reg = ppmCreateRegister(
            "ab_GC",
            "General control register, offset: 0x18",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_GC_maskWrite,
            view32,
            &(bport1_ab_data.GC.value),
            True
        );

        ppmCreateRegisterField(abGC_reg, "ACFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "ACFGT", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "ACREN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "ADACKEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "ADCO", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "AVGE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "CAL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abGC_reg, "DMAEN", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abGS_reg = ppmCreateRegister(
            "ab_GS",
            "General status register, offset: 0x1C",
            handles.bport1,
            0x1c,
            4,
            read_32,
            GSWrite1C,
            view32,
            &(bport1_ab_data.GS.value),
            True
        );

        ppmCreateRegisterField(abGS_reg, "ADACT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abGS_reg, "AWKST", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abGS_reg, "CALF", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abCV_reg = ppmCreateRegister(
            "ab_CV",
            "Compare value register, offset: 0x20",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_CV_maskWrite,
            view32,
            &(bport1_ab_data.CV.value),
            True
        );

        ppmCreateRegisterField(abCV_reg, "CV1", 0, 0, 12, 1, 1);
        ppmCreateRegisterField(abCV_reg, "CV2", 0, 16, 12, 1, 1);
    }
    {
        registerHandle abOFS_reg = ppmCreateRegister(
            "ab_OFS",
            "Offset correction value register, offset: 0x24",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_OFS_maskWrite,
            view32,
            &(bport1_ab_data.OFS.value),
            True
        );

        ppmCreateRegisterField(abOFS_reg, "OFS", 0, 0, 12, 1, 1);
        ppmCreateRegisterField(abOFS_reg, "SIGN", 0, 12, 1, 1, 1);
    }
    {
        registerHandle abCAL_reg = ppmCreateRegister(
            "ab_CAL",
            "Calibration value register, offset: 0x28",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_CAL_maskWrite,
            view32,
            &(bport1_ab_data.CAL.value),
            True
        );

        ppmCreateRegisterField(abCAL_reg, "CAL_CODE", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abPCTL_reg = ppmCreateRegister(
            "ab_PCTL",
            "Pin control register, offset: 0x30",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_PCTL_maskWrite,
            view32,
            &(bport1_ab_data.PCTL.value),
            True
        );

        ppmCreateRegisterField(abPCTL_reg, "ADPC0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPCTL_reg, "ADPC9", 0, 9, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PCTL.value = (Uns32)(bport1_ab_data.PCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CAL.value = (Uns32)(bport1_ab_data.CAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OFS.value = (Uns32)(bport1_ab_data.OFS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CV.value = (Uns32)(bport1_ab_data.CV.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GS.value = (Uns32)(bport1_ab_data.GS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GC.value = (Uns32)(bport1_ab_data.GC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CFG.value = (Uns32)(bport1_ab_data.CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000200));
        bport1_ab_data.R1.value = (Uns32)(bport1_ab_data.R1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.R0.value = (Uns32)(bport1_ab_data.R0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.HS.value = (Uns32)(bport1_ab_data.HS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.HC1.value = (Uns32)(bport1_ab_data.HC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_ab_data.HC0.value = (Uns32)(bport1_ab_data.HC0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the ADC peripheral used on the Freescale Vybrid platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Vybrid platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Development based on document number: VYBRIDRM Rev. 5, 07/2013");
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

