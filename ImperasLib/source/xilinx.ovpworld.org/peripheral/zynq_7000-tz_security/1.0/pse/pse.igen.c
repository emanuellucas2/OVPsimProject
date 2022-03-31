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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-tz_security", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_security2_sdio0_maskWrite) {
    bport1_ab_data.security2_sdio0.value = (bport1_ab_data.security2_sdio0.value & BPORT1_AB_SECURITY2_SDIO0_WRNMASK) | (data & BPORT1_AB_SECURITY2_SDIO0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_security3_sdio1_maskWrite) {
    bport1_ab_data.security3_sdio1.value = (bport1_ab_data.security3_sdio1.value & BPORT1_AB_SECURITY3_SDIO1_WRNMASK) | (data & BPORT1_AB_SECURITY3_SDIO1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_security4_qspi_maskWrite) {
    bport1_ab_data.security4_qspi.value = (bport1_ab_data.security4_qspi.value & BPORT1_AB_SECURITY4_QSPI_WRNMASK) | (data & BPORT1_AB_SECURITY4_QSPI_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_security6_apb_slaves_maskWrite) {
    bport1_ab_data.security6_apb_slaves.value = (bport1_ab_data.security6_apb_slaves.value & BPORT1_AB_SECURITY6_APB_SLAVES_WRNMASK) | (data & BPORT1_AB_SECURITY6_APB_SLAVES_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_security7_smc_maskWrite) {
    bport1_ab_data.security7_smc.value = (bport1_ab_data.security7_smc.value & BPORT1_AB_SECURITY7_SMC_WRNMASK) | (data & BPORT1_AB_SECURITY7_SMC_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 32);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x20);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x20);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_security2_sdio0",
            "Trust Zone Slave Security 2 (SDIO0)",
            handles.bport1,
            0x8,
            4,
            0,
            bport1_ab_security2_sdio0_maskWrite,
            view32,
            &(bport1_ab_data.security2_sdio0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_security3_sdio1",
            "Trust Zone Slave Security 3 (SDIO1)",
            handles.bport1,
            0xc,
            4,
            0,
            bport1_ab_security3_sdio1_maskWrite,
            view32,
            &(bport1_ab_data.security3_sdio1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_security4_qspi",
            "Trust Zone Slave Security 4 (QSPI)",
            handles.bport1,
            0x10,
            4,
            0,
            bport1_ab_security4_qspi_maskWrite,
            view32,
            &(bport1_ab_data.security4_qspi.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_security6_apb_slaves",
            "Trust Zone Slave Security 6 (APB Slave)",
            handles.bport1,
            0x18,
            4,
            0,
            bport1_ab_security6_apb_slaves_maskWrite,
            view32,
            &(bport1_ab_data.security6_apb_slaves.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_security7_smc",
            "Trust Zone Slave Security 7 (SMC)",
            handles.bport1,
            0x1c,
            4,
            0,
            bport1_ab_security7_smc_maskWrite,
            view32,
            &(bport1_ab_data.security7_smc.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.security7_smc.value = (Uns32)(bport1_ab_data.security7_smc.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.security6_apb_slaves.value = (Uns32)(bport1_ab_data.security6_apb_slaves.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.security4_qspi.value = (Uns32)(bport1_ab_data.security4_qspi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.security3_sdio1.value = (Uns32)(bport1_ab_data.security3_sdio1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.security2_sdio0.value = (Uns32)(bport1_ab_data.security2_sdio0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Trust Zone Security Registers");
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

