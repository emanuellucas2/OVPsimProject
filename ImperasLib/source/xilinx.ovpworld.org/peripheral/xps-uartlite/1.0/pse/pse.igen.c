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

plb_REG_dataT plb_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "xps-uartlite", "Example");
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
    handles.plb = ppmCreateSlaveBusPort("plb", 16);
    if (!handles.plb) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'plb'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "REG_RxFifo",
            0,
            handles.plb,
            0x0,
            4,
            ReadRxFifo,
            0,
            view32,
            &(plb_REG_data.RxFifo.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_TxFifo",
            0,
            handles.plb,
            0x4,
            4,
            0,
            WriteTxFifo,
            view32,
            &(plb_REG_data.TxFifo.value),
            True
        );
    }
    {
        registerHandle REGStat_reg = ppmCreateRegister(
            "REG_Stat",
            0,
            handles.plb,
            0x8,
            4,
            ReadStat,
            0,
            view32,
            &(plb_REG_data.Stat.value),
            True
        );

        ppmCreateRegisterField(REGStat_reg, "RxFifoValidData", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "RxFifoFull", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "TxFifoEmpty", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "TxFifoFull", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "IntrEnabled", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "OverrunError", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "FrameError", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGStat_reg, "ParityError", 0, 7, 1, 1, 0);
    }
    {
        registerHandle REGCtrl_reg = ppmCreateRegister(
            "REG_Ctrl",
            0,
            handles.plb,
            0xc,
            4,
            0,
            WriteCtrl,
            view32,
            &(plb_REG_data.Ctrl.value),
            True
        );

        ppmCreateRegisterField(REGCtrl_reg, "RstTxFifo", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(REGCtrl_reg, "RstRxFifo", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGCtrl_reg, "EnableIntr", 0, 4, 1, 0, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        plb_REG_data.Ctrl.value = (Uns32)(plb_REG_data.Ctrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.Stat.value = (Uns32)(plb_REG_data.Stat.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000002));
        plb_REG_data.TxFifo.value = (Uns32)(plb_REG_data.TxFifo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.RxFifo.value = (Uns32)(plb_REG_data.RxFifo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Xilinx Uart-Lite");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Register Accurate & Functional Model");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "DS573 Jun 22, 2011 v1.02.a");
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

