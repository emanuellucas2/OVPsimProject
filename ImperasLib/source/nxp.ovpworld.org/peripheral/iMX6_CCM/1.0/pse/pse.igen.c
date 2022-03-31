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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_CCM", "Example");
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
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_CCM_CCR",
            "CCM Control Register",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCDR",
            "CCM Control Divider Register",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CSR",
            "CCM Status Register",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CCM_CSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCSR",
            "CCM Clock Switcher Register",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CACRR",
            "CCM Arm Clock Root Register",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CACRR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CBCDR",
            "CCM Bus Clock Divider Register",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CBCDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CBCMR",
            "CCM Bus Clock Multiplexer Register",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CBCMR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CSCMR1",
            "CCM Serial Clock Multiplexer Register 1",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CSCMR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CSCMR2",
            "CCM Serial Clock Multiplexer Register 2",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CSCMR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CSCDR1",
            "CCM Serial Clock Divider Register 1",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CSCDR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CS1CDR",
            "CCM SSI1 Clock Divider Register",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CS1CDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CS2CDR",
            "CCM SSI2 Clock Divider Register",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CS2CDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CDCDR",
            "CCM D1 Clock Divider Register",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CDCDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CHSCCDR",
            "CCM HSC Clock Divider Register",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CHSCCDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CSCDR2",
            "CCM Serial Clock Divider Register 2 (modified reset value)",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CSCDR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CSCDR3",
            "CCM Serial Clock Divider Register 3",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CSCDR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CDHIPR",
            "CCM Divider Handshake In-Process Register",
            handles.bport1,
            0x48,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CCM_CDHIPR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CLPCR",
            "CCM Low Power Control Register",
            handles.bport1,
            0x54,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CLPCR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CISR",
            "CCM Interrupt Status Register",
            handles.bport1,
            0x58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CISR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CIMR",
            "CCM Interrupt Mask Register",
            handles.bport1,
            0x5c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CIMR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCOSR",
            "CCM Clock Output Source Register",
            handles.bport1,
            0x60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCOSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CGPR",
            "CCM General Purpose Register",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CGPR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR0",
            "CCM Clock Gating Register 0",
            handles.bport1,
            0x68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR1",
            "CCM Clock Gating Register 1",
            handles.bport1,
            0x6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR2",
            "CCM Clock Gating Register 2",
            handles.bport1,
            0x70,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR3",
            "CCM Clock Gating Register 3",
            handles.bport1,
            0x74,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR4",
            "CCM Clock Gating Register 4",
            handles.bport1,
            0x78,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR5",
            "CCM Clock Gating Register 5",
            handles.bport1,
            0x7c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CCGR6",
            "CCM Clock Gating Register 6",
            handles.bport1,
            0x80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CCGR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CCM_CMEOR",
            "CCM Module Enable Overide Register",
            handles.bport1,
            0x88,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CCM_CMEOR.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.CCM_CMEOR.value = (Uns32)(bport1_ab_data.CCM_CMEOR.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CCGR6.value = (Uns32)(bport1_ab_data.CCM_CCGR6.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CCGR5.value = (Uns32)(bport1_ab_data.CCM_CCGR5.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CCGR4.value = (Uns32)(bport1_ab_data.CCM_CCGR4.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CCGR3.value = (Uns32)(bport1_ab_data.CCM_CCGR3.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CCGR2.value = (Uns32)(bport1_ab_data.CCM_CCGR2.value & ~(0xffffffff)) | ((0xffffffff) & (0xFC3FFFFF));
        bport1_ab_data.CCM_CCGR1.value = (Uns32)(bport1_ab_data.CCM_CCGR1.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CCGR0.value = (Uns32)(bport1_ab_data.CCM_CCGR0.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CGPR.value = (Uns32)(bport1_ab_data.CCM_CGPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000FE62));
        bport1_ab_data.CCM_CCOSR.value = (Uns32)(bport1_ab_data.CCM_CCOSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x000A0001));
        bport1_ab_data.CCM_CIMR.value = (Uns32)(bport1_ab_data.CCM_CIMR.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.CCM_CISR.value = (Uns32)(bport1_ab_data.CCM_CISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CCM_CLPCR.value = (Uns32)(bport1_ab_data.CCM_CLPCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000079));
        bport1_ab_data.CCM_CDHIPR.value = (Uns32)(bport1_ab_data.CCM_CDHIPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CCM_CSCDR3.value = (Uns32)(bport1_ab_data.CCM_CSCDR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010841));
        bport1_ab_data.CCM_CSCDR2.value = (Uns32)(bport1_ab_data.CCM_CSCDR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00029948));
        bport1_ab_data.CCM_CHSCCDR.value = (Uns32)(bport1_ab_data.CCM_CHSCCDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0002A150));
        bport1_ab_data.CCM_CDCDR.value = (Uns32)(bport1_ab_data.CCM_CDCDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x33F71F92));
        bport1_ab_data.CCM_CS2CDR.value = (Uns32)(bport1_ab_data.CCM_CS2CDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x000736C1));
        bport1_ab_data.CCM_CS1CDR.value = (Uns32)(bport1_ab_data.CCM_CS1CDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0EC102C1));
        bport1_ab_data.CCM_CSCDR1.value = (Uns32)(bport1_ab_data.CCM_CSCDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00490B00));
        bport1_ab_data.CCM_CSCMR2.value = (Uns32)(bport1_ab_data.CCM_CSCMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00F00000));
        bport1_ab_data.CCM_CSCMR1.value = (Uns32)(bport1_ab_data.CCM_CSCMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00F00000));
        bport1_ab_data.CCM_CBCMR.value = (Uns32)(bport1_ab_data.CCM_CBCMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00820324));
        bport1_ab_data.CCM_CBCDR.value = (Uns32)(bport1_ab_data.CCM_CBCDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00018D00));
        bport1_ab_data.CCM_CACRR.value = (Uns32)(bport1_ab_data.CCM_CACRR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CCM_CCSR.value = (Uns32)(bport1_ab_data.CCM_CCSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000100));
        bport1_ab_data.CCM_CSR.value = (Uns32)(bport1_ab_data.CCM_CSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000010));
        bport1_ab_data.CCM_CCDR.value = (Uns32)(bport1_ab_data.CCM_CCDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CCM_CCR.value = (Uns32)(bport1_ab_data.CCM_CCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x040116FF));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "NXP i.MX6 CCM Clock Controller Module");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "\nThis is a register only interface model. No functionality is implemented.\nThe reset value for the CCM_CSCDR2 epdc_pix_clk_sel field (bits 11:9) has been modified from the documented value. The documented value (0x5) is reserved and causes a Linux Kernel Panic\n");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

