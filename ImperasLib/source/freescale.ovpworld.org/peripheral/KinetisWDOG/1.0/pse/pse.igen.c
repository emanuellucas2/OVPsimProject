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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisWDOG", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_PRESC_maskWrite) {
    bport1_ab_data.PRESC.value = (bport1_ab_data.PRESC.value & BPORT1_AB_PRESC_WRNMASK) | (data & BPORT1_AB_PRESC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_REFRESH_maskWrite) {
    bport1_ab_data.REFRESH.value = (bport1_ab_data.REFRESH.value & BPORT1_AB_REFRESH_WRNMASK) | (data & BPORT1_AB_REFRESH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RSTCNT_maskWrite) {
    bport1_ab_data.RSTCNT.value = (bport1_ab_data.RSTCNT.value & BPORT1_AB_RSTCNT_WRNMASK) | (data & BPORT1_AB_RSTCNT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_STCTRLH_maskWrite) {
    bport1_ab_data.STCTRLH.value = (bport1_ab_data.STCTRLH.value & BPORT1_AB_STCTRLH_WRNMASK) | (data & BPORT1_AB_STCTRLH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_STCTRLL_maskWrite) {
    bport1_ab_data.STCTRLL.value = (bport1_ab_data.STCTRLL.value & BPORT1_AB_STCTRLL_WRNMASK) | (data & BPORT1_AB_STCTRLL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TMROUTH_maskWrite) {
    bport1_ab_data.TMROUTH.value = (bport1_ab_data.TMROUTH.value & BPORT1_AB_TMROUTH_WRNMASK) | (data & BPORT1_AB_TMROUTH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TMROUTL_maskWrite) {
    bport1_ab_data.TMROUTL.value = (bport1_ab_data.TMROUTL.value & BPORT1_AB_TMROUTL_WRNMASK) | (data & BPORT1_AB_TMROUTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TOVALH_maskWrite) {
    bport1_ab_data.TOVALH.value = (bport1_ab_data.TOVALH.value & BPORT1_AB_TOVALH_WRNMASK) | (data & BPORT1_AB_TOVALH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TOVALL_maskWrite) {
    bport1_ab_data.TOVALL.value = (bport1_ab_data.TOVALL.value & BPORT1_AB_TOVALL_WRNMASK) | (data & BPORT1_AB_TOVALL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_UNLOCK_maskWrite) {
    bport1_ab_data.UNLOCK.value = (bport1_ab_data.UNLOCK.value & BPORT1_AB_UNLOCK_WRNMASK) | (data & BPORT1_AB_UNLOCK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WINH_maskWrite) {
    bport1_ab_data.WINH.value = (bport1_ab_data.WINH.value & BPORT1_AB_WINH_WRNMASK) | (data & BPORT1_AB_WINH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WINL_maskWrite) {
    bport1_ab_data.WINL.value = (bport1_ab_data.WINL.value & BPORT1_AB_WINL_WRNMASK) | (data & BPORT1_AB_WINL_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSTCTRLH_reg = ppmCreateRegister(
            "ab_STCTRLH",
            "Watchdog Status and Control Register High, offset: 0x0 ",
            handles.bport1,
            0x0,
            2,
            read_16,
            bport1_ab_STCTRLH_maskWrite,
            view16,
            &(bport1_ab_data.STCTRLH.value),
            True
        );

        ppmCreateRegisterField(abSTCTRLH_reg, "ALLOWUPDATE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "BYTESEL", 0, 12, 2, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "CLKSRC", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "DBGEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "DISTESTWDOG", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "IRQRSTEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "STNDBYEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "STOPEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "TESTSEL", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "TESTWDOG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "WAITEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "WDOGEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSTCTRLH_reg, "WINEN", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abSTCTRLL_reg = ppmCreateRegister(
            "ab_STCTRLL",
            "Watchdog Status and Control Register Low, offset: 0x2 ",
            handles.bport1,
            0x2,
            2,
            read_16,
            bport1_ab_STCTRLL_maskWrite,
            view16,
            &(bport1_ab_data.STCTRLL.value),
            True
        );

        ppmCreateRegisterField(abSTCTRLL_reg, "INTFLG", 0, 15, 1, 1, 1);
    }
    {
        registerHandle abTOVALH_reg = ppmCreateRegister(
            "ab_TOVALH",
            "Watchdog Time-out Value Register High, offset: 0x4 ",
            handles.bport1,
            0x4,
            2,
            read_16,
            bport1_ab_TOVALH_maskWrite,
            view16,
            &(bport1_ab_data.TOVALH.value),
            True
        );

        ppmCreateRegisterField(abTOVALH_reg, "TOVALHIGH", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abTOVALL_reg = ppmCreateRegister(
            "ab_TOVALL",
            "Watchdog Time-out Value Register Low, offset: 0x6 ",
            handles.bport1,
            0x6,
            2,
            read_16,
            bport1_ab_TOVALL_maskWrite,
            view16,
            &(bport1_ab_data.TOVALL.value),
            True
        );

        ppmCreateRegisterField(abTOVALL_reg, "TOVALLOW", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abWINH_reg = ppmCreateRegister(
            "ab_WINH",
            "Watchdog Window Register High, offset: 0x8 ",
            handles.bport1,
            0x8,
            2,
            read_16,
            bport1_ab_WINH_maskWrite,
            view16,
            &(bport1_ab_data.WINH.value),
            True
        );

        ppmCreateRegisterField(abWINH_reg, "WINHIGH", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abWINL_reg = ppmCreateRegister(
            "ab_WINL",
            "Watchdog Window Register Low, offset: 0xA ",
            handles.bport1,
            0xa,
            2,
            read_16,
            bport1_ab_WINL_maskWrite,
            view16,
            &(bport1_ab_data.WINL.value),
            True
        );

        ppmCreateRegisterField(abWINL_reg, "WINLOW", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abREFRESH_reg = ppmCreateRegister(
            "ab_REFRESH",
            "Watchdog Refresh Register, offset: 0xC ",
            handles.bport1,
            0xc,
            2,
            read_16,
            bport1_ab_REFRESH_maskWrite,
            view16,
            &(bport1_ab_data.REFRESH.value),
            True
        );

        ppmCreateRegisterField(abREFRESH_reg, "WDOGREFRESH", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abUNLOCK_reg = ppmCreateRegister(
            "ab_UNLOCK",
            "Watchdog Unlock Register, offset: 0xE ",
            handles.bport1,
            0xe,
            2,
            read_16,
            bport1_ab_UNLOCK_maskWrite,
            view16,
            &(bport1_ab_data.UNLOCK.value),
            True
        );

        ppmCreateRegisterField(abUNLOCK_reg, "WDOGUNLOCK", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abTMROUTH_reg = ppmCreateRegister(
            "ab_TMROUTH",
            "Watchdog Timer Output Register High, offset: 0x10 ",
            handles.bport1,
            0x10,
            2,
            read_16,
            bport1_ab_TMROUTH_maskWrite,
            view16,
            &(bport1_ab_data.TMROUTH.value),
            True
        );

        ppmCreateRegisterField(abTMROUTH_reg, "TIMEROUTHIGH", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abTMROUTL_reg = ppmCreateRegister(
            "ab_TMROUTL",
            "Watchdog Timer Output Register Low, offset: 0x12 ",
            handles.bport1,
            0x12,
            2,
            read_16,
            bport1_ab_TMROUTL_maskWrite,
            view16,
            &(bport1_ab_data.TMROUTL.value),
            True
        );

        ppmCreateRegisterField(abTMROUTL_reg, "TIMEROUTLOW", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abRSTCNT_reg = ppmCreateRegister(
            "ab_RSTCNT",
            "Watchdog Reset Count Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            2,
            read_16,
            bport1_ab_RSTCNT_maskWrite,
            view16,
            &(bport1_ab_data.RSTCNT.value),
            True
        );

        ppmCreateRegisterField(abRSTCNT_reg, "RSTCNT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPRESC_reg = ppmCreateRegister(
            "ab_PRESC",
            "Watchdog Prescaler Register, offset: 0x16 ",
            handles.bport1,
            0x16,
            2,
            read_16,
            bport1_ab_PRESC_maskWrite,
            view16,
            &(bport1_ab_data.PRESC.value),
            True
        );

        ppmCreateRegisterField(abPRESC_reg, "PRESCVAL", 0, 8, 3, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PRESC.value = (Uns16)(bport1_ab_data.PRESC.value & ~(0xffff)) | ((0xffff) & (0x0400));
        bport1_ab_data.RSTCNT.value = (Uns16)(bport1_ab_data.RSTCNT.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.TMROUTL.value = (Uns16)(bport1_ab_data.TMROUTL.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.TMROUTH.value = (Uns16)(bport1_ab_data.TMROUTH.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.UNLOCK.value = (Uns16)(bport1_ab_data.UNLOCK.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.REFRESH.value = (Uns16)(bport1_ab_data.REFRESH.value & ~(0xffff)) | ((0xffff) & (0xb480));
        bport1_ab_data.WINL.value = (Uns16)(bport1_ab_data.WINL.value & ~(0xffff)) | ((0xffff) & (0x0010));
        bport1_ab_data.WINH.value = (Uns16)(bport1_ab_data.WINH.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.TOVALL.value = (Uns16)(bport1_ab_data.TOVALL.value & ~(0xffff)) | ((0xffff) & (0x4b4c));
        bport1_ab_data.TOVALH.value = (Uns16)(bport1_ab_data.TOVALH.value & ~(0xffff)) | ((0xffff) & (0x004c));
        bport1_ab_data.STCTRLL.value = (Uns16)(bport1_ab_data.STCTRLL.value & ~(0xffff)) | ((0xffff) & (0x0001));
        bport1_ab_data.STCTRLH.value = (Uns16)(bport1_ab_data.STCTRLH.value & ~(0xffff)) | ((0xffff) & (0x01d3));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the WDOG peripheral used on the Freescale Kinetis platform");
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

