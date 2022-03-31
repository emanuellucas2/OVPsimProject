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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-swdt", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

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
        registerHandle abMODE_reg = ppmCreateRegister(
            "ab_MODE",
            "WD zero mode register",
            handles.bport1,
            0x0,
            4,
            0,
            wrMode,
            view32,
            &(bport1_ab_data.MODE.value),
            True
        );

        ppmCreateRegisterField(abMODE_reg, "ZKEY", 0, 12, 12, 0, 1);
        ppmCreateRegisterField(abMODE_reg, "IRQLN", 0, 7, 2, 0, 1);
        ppmCreateRegisterField(abMODE_reg, "IRQEN", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(abMODE_reg, "RSTEN", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(abMODE_reg, "WDEN", 0, 0, 1, 0, 1);
    }
    {
        registerHandle abCONTROL_reg = ppmCreateRegister(
            "ab_CONTROL",
            "Counter Control Register",
            handles.bport1,
            0x4,
            4,
            rdControl,
            wrControl,
            view32,
            &(bport1_ab_data.CONTROL.value),
            True
        );

        ppmCreateRegisterField(abCONTROL_reg, "CKEY", 0, 14, 12, 1, 1);
        ppmCreateRegisterField(abCONTROL_reg, "CRV", 0, 2, 12, 1, 1);
        ppmCreateRegisterField(abCONTROL_reg, "CLKSEL", 0, 0, 2, 1, 1);
    }
    {
        registerHandle abRESTART_reg = ppmCreateRegister(
            "ab_RESTART",
            "Restart key register - this not a real register as no data is stored",
            handles.bport1,
            0x8,
            4,
            0,
            wrReStart,
            view32,
            &(bport1_ab_data.RESTART.value),
            True
        );

        ppmCreateRegisterField(abRESTART_reg, "RSTKEY", 0, 0, 16, 0, 1);
    }
    {
        registerHandle abSTATUS_reg = ppmCreateRegister(
            "ab_STATUS",
            "Status Register",
            handles.bport1,
            0xc,
            4,
            rdStatus,
            0,
            view32,
            &(bport1_ab_data.STATUS.value),
            True
        );

        ppmCreateRegisterField(abSTATUS_reg, "WDZ", 0, 0, 1, 1, 0);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.STATUS.value = (Uns32)(bport1_ab_data.STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RESTART.value = (Uns32)(bport1_ab_data.RESTART.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CONTROL.value = (Uns32)(bport1_ab_data.CONTROL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003FFC));
        bport1_ab_data.MODE.value = (Uns32)(bport1_ab_data.MODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x000001C0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 System Watchdog Timer Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers but no behavior.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
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

