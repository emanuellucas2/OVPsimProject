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

port0_Reg_dataT port0_Reg_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "CoreUARTapb", "Example");
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
    handles.port0 = ppmCreateSlaveBusPort("port0", 24);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "Reg_TxData",
            0,
            handles.port0,
            0x0,
            4,
            0,
            TxDataWrite,
            view32,
            &(port0_Reg_data.TxData.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "Reg_RxData",
            0,
            handles.port0,
            0x4,
            4,
            RxDataRead,
            0,
            view32,
            &(port0_Reg_data.RxData.value),
            True
        );
    }
    {
        registerHandle RegCtrl1_reg = ppmCreateRegister(
            "Reg_Ctrl1",
            0,
            handles.port0,
            0x8,
            4,
            Ctrl1Read,
            Ctrl1Write,
            view32,
            &(port0_Reg_data.Ctrl1.value),
            True
        );

        ppmCreateRegisterField(RegCtrl1_reg, "BAUD_VALUE", 0, 0, 8, 1, 1);
    }
    {
        registerHandle RegCtrl2_reg = ppmCreateRegister(
            "Reg_Ctrl2",
            0,
            handles.port0,
            0xc,
            4,
            Ctrl2Read,
            Ctrl2Write,
            view32,
            &(port0_Reg_data.Ctrl2.value),
            True
        );

        ppmCreateRegisterField(RegCtrl2_reg, "BIT8", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(RegCtrl2_reg, "PARITY_EN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(RegCtrl2_reg, "ODD_N_EVEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(RegCtrl2_reg, "BAUD_VALUE", 0, 3, 5, 1, 1);
    }
    {
        registerHandle RegStatus_reg = ppmCreateRegister(
            "Reg_Status",
            0,
            handles.port0,
            0x10,
            4,
            StatusRead,
            0,
            view32,
            &(port0_Reg_data.Status.value),
            True
        );

        ppmCreateRegisterField(RegStatus_reg, "TXRDY", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(RegStatus_reg, "RXRDY", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(RegStatus_reg, "PARITY_ERR", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(RegStatus_reg, "OVERFLOW", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(RegStatus_reg, "FRAMING_ERR", 0, 4, 1, 1, 0);
    }
    {
        registerHandle RegCtrl3_reg = ppmCreateRegister(
            "Reg_Ctrl3",
            0,
            handles.port0,
            0x14,
            4,
            Ctrl3Read,
            Ctrl3Write,
            view32,
            &(port0_Reg_data.Ctrl3.value),
            True
        );

        ppmCreateRegisterField(RegCtrl3_reg, "BAUD_VALUE_FRACTION", 0, 0, 3, 1, 1);
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Microsemi CoreUARTapb");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Basic functionality for transmit and receive");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "CoreUARTapb handbook v5.2 https://www.microsemi.com/document-portal/doc_view/130958-coreuartapb-handbook");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

