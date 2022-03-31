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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UART", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 28);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abtxdata_reg = ppmCreateRegister(
            "ab_txdata",
            0,
            handles.bport1,
            0x0,
            4,
            txdataRead,
            txdataWrite,
            txdataView,
            &(bport1_ab_data.txdata.value),
            True
        );

        ppmCreateRegisterField(abtxdata_reg, "DATA", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abtxdata_reg, "FULL", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abrxdata_reg = ppmCreateRegister(
            "ab_rxdata",
            0,
            handles.bport1,
            0x4,
            4,
            rxdataRead,
            0,
            view32,
            &(bport1_ab_data.rxdata.value),
            True
        );

        ppmCreateRegisterField(abrxdata_reg, "DATA", 0, 0, 8, 1, 0);
        ppmCreateRegisterField(abrxdata_reg, "EMPTY", 0, 31, 1, 1, 0);
    }
    {
        registerHandle abtxctrl_reg = ppmCreateRegister(
            "ab_txctrl",
            0,
            handles.bport1,
            0x8,
            4,
            read_32,
            txctrlWrite,
            view32,
            &(bport1_ab_data.txctrl.value),
            True
        );

        ppmCreateRegisterField(abtxctrl_reg, "TXEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abtxctrl_reg, "NSTOP", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abtxctrl_reg, "TXCNT", 0, 16, 3, 1, 1);
    }
    {
        registerHandle abrxctrl_reg = ppmCreateRegister(
            "ab_rxctrl",
            0,
            handles.bport1,
            0xc,
            4,
            read_32,
            rxctrlWrite,
            view32,
            &(bport1_ab_data.rxctrl.value),
            True
        );

        ppmCreateRegisterField(abrxctrl_reg, "RXEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abrxctrl_reg, "RXCNT", 0, 16, 3, 1, 1);
    }
    {
        registerHandle abie_reg = ppmCreateRegister(
            "ab_ie",
            0,
            handles.bport1,
            0x10,
            4,
            read_32,
            ieWrite,
            view32,
            &(bport1_ab_data.ie.value),
            True
        );

        ppmCreateRegisterField(abie_reg, "TXWM", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abie_reg, "RXWM", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abip_reg = ppmCreateRegister(
            "ab_ip",
            0,
            handles.bport1,
            0x14,
            4,
            ipRead,
            0,
            view32,
            &(bport1_ab_data.ip.value),
            True
        );

        ppmCreateRegisterField(abip_reg, "TXWM", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abip_reg, "RXWM", 0, 1, 1, 1, 0);
    }
    {
        registerHandle abdiv_reg = ppmCreateRegister(
            "ab_div",
            0,
            handles.bport1,
            0x18,
            4,
            read_32,
            divWrite,
            view32,
            &(bport1_ab_data.div.value),
            True
        );

        ppmCreateRegisterField(abdiv_reg, "DIV", 0, 0, 20, 1, 1);
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.div.value = (Uns32)(bport1_ab_data.div.value & ~(0xffffffff)) | ((0xffffffff) & (289));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Sifive UART");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "When simulatebaud parameter is set to true baud rate delays are modeled for receive only, not transmit. Data always sent immediately.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

