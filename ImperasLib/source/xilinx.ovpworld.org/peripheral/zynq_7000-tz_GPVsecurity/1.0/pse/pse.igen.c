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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-tz_GPVsecurity", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_security_apb_maskWrite) {
    bport1_ab_data.security_apb.value = (bport1_ab_data.security_apb.value & BPORT1_AB_SECURITY_APB_WRNMASK) | (data & BPORT1_AB_SECURITY_APB_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_security_gp0_axi_maskWrite) {
    bport1_ab_data.security_gp0_axi.value = (bport1_ab_data.security_gp0_axi.value & BPORT1_AB_SECURITY_GP0_AXI_WRNMASK) | (data & BPORT1_AB_SECURITY_GP0_AXI_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_security_gp1_axi_maskWrite) {
    bport1_ab_data.security_gp1_axi.value = (bport1_ab_data.security_gp1_axi.value & BPORT1_AB_SECURITY_GP1_AXI_WRNMASK) | (data & BPORT1_AB_SECURITY_GP1_AXI_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 64);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x40);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x40);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_security_gp0_axi",
            "M_AXI_GP0 security setting",
            handles.bport1,
            0x1c,
            4,
            0,
            bport1_ab_security_gp0_axi_maskWrite,
            view32,
            &(bport1_ab_data.security_gp0_axi.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_security_gp1_axi",
            "M_AXI_GP1 security setting",
            handles.bport1,
            0x20,
            4,
            0,
            bport1_ab_security_gp1_axi_maskWrite,
            view32,
            &(bport1_ab_data.security_gp1_axi.value),
            True
        );
    }
    {
        registerHandle absecurity_apb_reg = ppmCreateRegister(
            "ab_security_apb",
            "APB boot secure setting port",
            handles.bport1,
            0x28,
            4,
            0,
            bport1_ab_security_apb_maskWrite,
            view32,
            &(bport1_ab_data.security_apb.value),
            True
        );

        ppmCreateRegisterField(absecurity_apb_reg, "DDRC", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(absecurity_apb_reg, "TTC1", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(absecurity_apb_reg, "AFI3", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(absecurity_apb_reg, "AFI2", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(absecurity_apb_reg, "AFI1", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(absecurity_apb_reg, "AFI0", 0, 0, 1, 0, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.security_apb.value = (Uns32)(bport1_ab_data.security_apb.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.security_gp1_axi.value = (Uns32)(bport1_ab_data.security_gp1_axi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.security_gp0_axi.value = (Uns32)(bport1_ab_data.security_gp0_axi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Trust Zone GPV Security Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the set of registers but no behavior.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf) and ug1019-zynq-trustzone");
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

