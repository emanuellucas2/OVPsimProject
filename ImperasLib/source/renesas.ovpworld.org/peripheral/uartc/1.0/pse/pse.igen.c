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

UARTP0_reg0_dataT UARTP0_reg0_data;

UARTP0_reg1_dataT UARTP0_reg1_data;

UARTP0_reg2_dataT UARTP0_reg2_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "uartc", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.UARTP0 = ppmCreateSlaveBusPort("UARTP0", 16);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0CTL0_reg = ppmCreateRegister(
            "reg0_CTL0",
            0,
            handles.UARTP0,
            0x0,
            1,
            read_8,
            writeCTL0,
            view8,
            &(UARTP0_reg0_data.CTL0.value),
            True
        );

        ppmCreateRegisterField(reg0CTL0_reg, "SL", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "CL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "PS", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "DIR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "RXE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "TXE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "PWR", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0CTL1_reg = ppmCreateRegister(
            "reg0_CTL1",
            0,
            handles.UARTP0,
            0x1,
            1,
            read_8,
            writeCTL1,
            view8,
            &(UARTP0_reg0_data.CTL1.value),
            True
        );

        ppmCreateRegisterField(reg0CTL1_reg, "CKS", 0, 0, 4, 1, 1);
    }
    {
        registerHandle reg0CTL2_reg = ppmCreateRegister(
            "reg0_CTL2",
            0,
            handles.UARTP0,
            0x2,
            1,
            read_8,
            writeCTL2,
            view8,
            &(UARTP0_reg0_data.CTL2.value),
            True
        );

        ppmCreateRegisterField(reg0CTL2_reg, "BRS", 0, 0, 8, 1, 1);
    }
    {
        registerHandle reg0OPT0_reg = ppmCreateRegister(
            "reg0_OPT0",
            0,
            handles.UARTP0,
            0x3,
            1,
            read_8,
            writeOPT0,
            view8,
            &(UARTP0_reg0_data.OPT0.value),
            True
        );

        ppmCreateRegisterField(reg0OPT0_reg, "RDL", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0OPT0_reg, "TDL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0OPT0_reg, "SLS", 0, 2, 3, 1, 1);
        ppmCreateRegisterField(reg0OPT0_reg, "STT", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg0OPT0_reg, "SRT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg0OPT0_reg, "SRF", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0STR_reg = ppmCreateRegister(
            "reg0_STR",
            0,
            handles.UARTP0,
            0x4,
            1,
            read_8,
            writeSTR,
            view8,
            &(UARTP0_reg0_data.STR.value),
            True
        );

        ppmCreateRegisterField(reg0STR_reg, "OVE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0STR_reg, "FE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0STR_reg, "PE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0STR_reg, "TSF", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg1RX_reg = ppmCreateRegister(
            "reg1_RX",
            0,
            handles.UARTP0,
            0x6,
            2,
            readRX,
            0,
            view16,
            &(UARTP0_reg1_data.RX.value),
            True
        );

        ppmCreateRegisterField(reg1RX_reg, "RXL", 0, 0, 8, 1, 0);
        ppmCreateRegisterField(reg1RX_reg, "B9", 0, 8, 1, 1, 0);
    }
    {
        registerHandle reg1TX_reg = ppmCreateRegister(
            "reg1_TX",
            0,
            handles.UARTP0,
            0x8,
            2,
            readTX,
            writeTX,
            view16,
            &(UARTP0_reg1_data.TX.value),
            True
        );

        ppmCreateRegisterField(reg1TX_reg, "TXL", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(reg1TX_reg, "B9", 0, 8, 1, 1, 1);
    }
    {
        registerHandle reg2OPT1_reg = ppmCreateRegister(
            "reg2_OPT1",
            0,
            handles.UARTP0,
            0xa,
            1,
            read_8,
            writeOPT1,
            view8,
            &(UARTP0_reg2_data.OPT1.value),
            True
        );

        ppmCreateRegisterField(reg2OPT1_reg, "EBE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle reg2OPT2_reg = ppmCreateRegister(
            "reg2_OPT2",
            0,
            handles.UARTP0,
            0xb,
            1,
            read_8,
            0,
            view8,
            &(UARTP0_reg2_data.OPT2.value),
            True
        );

        ppmCreateRegisterField(reg2OPT2_reg, "RSF", 0, 0, 1, 1, 0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        UARTP0_reg2_data.OPT2.value = (Uns8)(UARTP0_reg2_data.OPT2.value & ~(0xff)) | ((0xff) & (0x00));
        UARTP0_reg2_data.OPT1.value = (Uns8)(UARTP0_reg2_data.OPT1.value & ~(0xff)) | ((0xff) & (0x00));
        UARTP0_reg1_data.TX.value = (Uns16)(UARTP0_reg1_data.TX.value & ~(0xffff)) | ((0xffff) & (0x01FF));
        UARTP0_reg1_data.RX.value = (Uns16)(UARTP0_reg1_data.RX.value & ~(0xffff)) | ((0xffff) & (0x01FF));
        UARTP0_reg0_data.STR.value = (Uns8)(UARTP0_reg0_data.STR.value & ~(0xff)) | ((0xff) & (0x00));
        UARTP0_reg0_data.OPT0.value = (Uns8)(UARTP0_reg0_data.OPT0.value & ~(0xff)) | ((0xff) & (0x14));
        UARTP0_reg0_data.CTL2.value = (Uns8)(UARTP0_reg0_data.CTL2.value & ~(0xff)) | ((0xff) & (0xFF));
        UARTP0_reg0_data.CTL1.value = (Uns8)(UARTP0_reg0_data.CTL1.value & ~(0xff)) | ((0xff) & (0x00));
        UARTP0_reg0_data.CTL0.value = (Uns8)(UARTP0_reg0_data.CTL0.value & ~(0xff)) | ((0xff) & (0x10));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas UARTC Asynchronous Serial Interface");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No Support for pin level transitions");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

