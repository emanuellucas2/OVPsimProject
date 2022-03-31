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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisUSBDCD", "Example");
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

static PPM_WRITE_CB(bport1_ab_CLOCK_maskWrite) {
    bport1_ab_data.CLOCK.value = (bport1_ab_data.CLOCK.value & BPORT1_AB_CLOCK_WRNMASK) | (data & BPORT1_AB_CLOCK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CONTROL_maskWrite) {
    bport1_ab_data.CONTROL.value = (bport1_ab_data.CONTROL.value & BPORT1_AB_CONTROL_WRNMASK) | (data & BPORT1_AB_CONTROL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIMER0_maskWrite) {
    bport1_ab_data.TIMER0.value = (bport1_ab_data.TIMER0.value & BPORT1_AB_TIMER0_WRNMASK) | (data & BPORT1_AB_TIMER0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIMER1_maskWrite) {
    bport1_ab_data.TIMER1.value = (bport1_ab_data.TIMER1.value & BPORT1_AB_TIMER1_WRNMASK) | (data & BPORT1_AB_TIMER1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIMER2_maskWrite) {
    bport1_ab_data.TIMER2.value = (bport1_ab_data.TIMER2.value & BPORT1_AB_TIMER2_WRNMASK) | (data & BPORT1_AB_TIMER2_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCONTROL_reg = ppmCreateRegister(
            "ab_CONTROL",
            "Control Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_CONTROL_maskWrite,
            view32,
            &(bport1_ab_data.CONTROL.value),
            True
        );

        ppmCreateRegisterField(abCONTROL_reg, "IACK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCONTROL_reg, "IE", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCONTROL_reg, "IF", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCONTROL_reg, "SR", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCONTROL_reg, "START", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abCLOCK_reg = ppmCreateRegister(
            "ab_CLOCK",
            "Clock Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_CLOCK_maskWrite,
            view32,
            &(bport1_ab_data.CLOCK.value),
            True
        );

        ppmCreateRegisterField(abCLOCK_reg, "CLOCK_SPEED", 0, 2, 10, 1, 1);
        ppmCreateRegisterField(abCLOCK_reg, "CLOCK_UNIT", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSTATUS_reg = ppmCreateRegister(
            "ab_STATUS",
            "Status Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.STATUS.value),
            True
        );

        ppmCreateRegisterField(abSTATUS_reg, "ACTIVE", 0, 22, 1, 1, 0);
        ppmCreateRegisterField(abSTATUS_reg, "ERR", 0, 20, 1, 1, 0);
        ppmCreateRegisterField(abSTATUS_reg, "SEQ_RES", 0, 16, 2, 1, 0);
        ppmCreateRegisterField(abSTATUS_reg, "SEQ_STAT", 0, 18, 2, 1, 0);
        ppmCreateRegisterField(abSTATUS_reg, "TO", 0, 21, 1, 1, 0);
    }
    {
        registerHandle abTIMER0_reg = ppmCreateRegister(
            "ab_TIMER0",
            "TIMER0 Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_TIMER0_maskWrite,
            view32,
            &(bport1_ab_data.TIMER0.value),
            True
        );

        ppmCreateRegisterField(abTIMER0_reg, "TSEQ_INIT", 0, 16, 10, 1, 1);
        ppmCreateRegisterField(abTIMER0_reg, "TUNITCON", 0, 0, 12, 1, 1);
    }
    {
        registerHandle abTIMER1_reg = ppmCreateRegister(
            "ab_TIMER1",
            "TIMER1 Register, offset: 0x14",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_TIMER1_maskWrite,
            view32,
            &(bport1_ab_data.TIMER1.value),
            True
        );

        ppmCreateRegisterField(abTIMER1_reg, "TDCD_DBNC", 0, 16, 10, 1, 1);
        ppmCreateRegisterField(abTIMER1_reg, "TVDPSRC_ON", 0, 0, 10, 1, 1);
    }
    {
        registerHandle abTIMER2_reg = ppmCreateRegister(
            "ab_TIMER2",
            "TIMER2 Register, offset: 0x18 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_TIMER2_maskWrite,
            view32,
            &(bport1_ab_data.TIMER2.value),
            True
        );

        ppmCreateRegisterField(abTIMER2_reg, "CHECK_DM", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abTIMER2_reg, "TVDPSRC_CON", 0, 16, 10, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.TIMER2.value = (Uns32)(bport1_ab_data.TIMER2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0028000a));
        bport1_ab_data.TIMER1.value = (Uns32)(bport1_ab_data.TIMER1.value & ~(0xffffffff)) | ((0xffffffff) & (0x000a0028));
        bport1_ab_data.TIMER0.value = (Uns32)(bport1_ab_data.TIMER0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00100000));
        bport1_ab_data.STATUS.value = (Uns32)(bport1_ab_data.STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CLOCK.value = (Uns32)(bport1_ab_data.CLOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000c1));
        bport1_ab_data.CONTROL.value = (Uns32)(bport1_ab_data.CONTROL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the USBDCD peripheral used on the Freescale Kinetis platform");
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

