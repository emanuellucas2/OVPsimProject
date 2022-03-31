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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UartInterface", "Example");
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

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abdr_reg = ppmCreateRegister(
            "ab_dr",
            "UARTDR",
            handles.bport1,
            0x0,
            4,
            readDR,
            writeDR,
            view32,
            &(bport1_ab_data.dr.value),
            True
        );

        ppmCreateRegisterField(abdr_reg, "OE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abdr_reg, "BE", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abdr_reg, "PE", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abdr_reg, "FE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abdr_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abrsrecr_reg = ppmCreateRegister(
            "ab_rsrecr",
            "UARTRSRECR",
            handles.bport1,
            0x4,
            4,
            readSRRECR,
            writeSRRECR,
            view32,
            &(bport1_ab_data.rsrecr.value),
            True
        );

        ppmCreateRegisterField(abrsrecr_reg, "OE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abrsrecr_reg, "BE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abrsrecr_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abrsrecr_reg, "FE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abfr_reg = ppmCreateRegister(
            "ab_fr",
            "UARTFR",
            handles.bport1,
            0x18,
            4,
            readSR,
            0,
            view32,
            &(bport1_ab_data.fr.value),
            True
        );

        ppmCreateRegisterField(abfr_reg, "TXFE", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abfr_reg, "RXFF", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abfr_reg, "TXFF", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abfr_reg, "RXFE", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abfr_reg, "BUSY", 0, 3, 1, 1, 0);
    }
    {
        registerHandle abfbrd_reg = ppmCreateRegister(
            "ab_fbrd",
            "UARTFBDR",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.fbrd.value),
            True
        );

        ppmCreateRegisterField(abfbrd_reg, "DIVFRAC", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abibrd_reg = ppmCreateRegister(
            "ab_ibrd",
            "UARTIBRD",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ibrd.value),
            True
        );

        ppmCreateRegisterField(abibrd_reg, "DIVINT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle ablcrh_reg = ppmCreateRegister(
            "ab_lcrh",
            "UARTLCRH",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.lcrh.value),
            True
        );

        ppmCreateRegisterField(ablcrh_reg, "SPS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(ablcrh_reg, "WLEN", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(ablcrh_reg, "FEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(ablcrh_reg, "STP2", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(ablcrh_reg, "EPS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(ablcrh_reg, "PEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(ablcrh_reg, "BRK", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abctl_reg = ppmCreateRegister(
            "ab_ctl",
            "UARTLCTL",
            handles.bport1,
            0x30,
            4,
            readCTL,
            writeCTL,
            view32,
            &(bport1_ab_data.ctl.value),
            True
        );

        ppmCreateRegisterField(abctl_reg, "RXE", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abctl_reg, "TXE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abctl_reg, "LBE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abctl_reg, "UARTEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abifls_reg = ppmCreateRegister(
            "ab_ifls",
            "UARTIFLS",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ifls.value),
            True
        );

        ppmCreateRegisterField(abifls_reg, "RXIFLSEL", 0, 3, 3, 1, 1);
        ppmCreateRegisterField(abifls_reg, "TXIFLSEL", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abim_reg = ppmCreateRegister(
            "ab_im",
            "UARTIM",
            handles.bport1,
            0x38,
            4,
            readIM,
            writeIM,
            view32,
            &(bport1_ab_data.im.value),
            True
        );

        ppmCreateRegisterField(abim_reg, "OEIM", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abim_reg, "BEIM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abim_reg, "PEIM", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abim_reg, "FEIM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abim_reg, "RTIM", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abim_reg, "TXIM", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abim_reg, "RXIM", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abris_reg = ppmCreateRegister(
            "ab_ris",
            "UARTRIS",
            handles.bport1,
            0x3c,
            4,
            readRIS,
            writeRIS,
            view32,
            &(bport1_ab_data.ris.value),
            True
        );

        ppmCreateRegisterField(abris_reg, "OERIS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abris_reg, "BERIS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abris_reg, "PERIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abris_reg, "FERIS", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abris_reg, "RTRIS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abris_reg, "TXRIS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abris_reg, "RXRIS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abmis_reg = ppmCreateRegister(
            "ab_mis",
            "UARTMIS",
            handles.bport1,
            0x40,
            4,
            readMIS,
            writeMIS,
            view32,
            &(bport1_ab_data.mis.value),
            True
        );

        ppmCreateRegisterField(abmis_reg, "OEMIS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abmis_reg, "BEMIS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abmis_reg, "PEMIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abmis_reg, "FEMIS", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abmis_reg, "RTMIS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abmis_reg, "TXMIS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abmis_reg, "RXMIS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abicr_reg = ppmCreateRegister(
            "ab_icr",
            "UARTICR",
            handles.bport1,
            0x44,
            4,
            readICR,
            writeICR,
            view32,
            &(bport1_ab_data.icr.value),
            True
        );

        ppmCreateRegisterField(abicr_reg, "OEIC", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abicr_reg, "BEIC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abicr_reg, "PEIC", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abicr_reg, "FEIC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abicr_reg, "RTIC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abicr_reg, "TXIC", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abicr_reg, "RXIC", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_pid0",
            0,
            handles.bport1,
            0xfd0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid1",
            0,
            handles.bport1,
            0xfd4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid2",
            0,
            handles.bport1,
            0xfd8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid3",
            0,
            handles.bport1,
            0xfdc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid4",
            0,
            handles.bport1,
            0xfe0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid5",
            0,
            handles.bport1,
            0xfe4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid6",
            0,
            handles.bport1,
            0xfe8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_pid7",
            0,
            handles.bport1,
            0xfec,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.pid7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_cid0",
            0,
            handles.bport1,
            0xff0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.cid0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_cid1",
            0,
            handles.bport1,
            0xff4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.cid1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_cid2",
            0,
            handles.bport1,
            0xff8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.cid2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_cid3",
            0,
            handles.bport1,
            0xffc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.cid3.value),
            True
        );
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.cid3.value = (Uns32)(bport1_ab_data.cid3.value & ~(0xffffffff)) | ((0xffffffff) & (0xb1));
        bport1_ab_data.cid2.value = (Uns32)(bport1_ab_data.cid2.value & ~(0xffffffff)) | ((0xffffffff) & (0x05));
        bport1_ab_data.cid1.value = (Uns32)(bport1_ab_data.cid1.value & ~(0xffffffff)) | ((0xffffffff) & (0xf0));
        bport1_ab_data.cid0.value = (Uns32)(bport1_ab_data.cid0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0d));
        bport1_ab_data.pid7.value = (Uns32)(bport1_ab_data.pid7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.pid6.value = (Uns32)(bport1_ab_data.pid6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.pid5.value = (Uns32)(bport1_ab_data.pid5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.pid4.value = (Uns32)(bport1_ab_data.pid4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.pid3.value = (Uns32)(bport1_ab_data.pid3.value & ~(0xffffffff)) | ((0xffffffff) & (0x01));
        bport1_ab_data.pid2.value = (Uns32)(bport1_ab_data.pid2.value & ~(0xffffffff)) | ((0xffffffff) & (0x18));
        bport1_ab_data.pid1.value = (Uns32)(bport1_ab_data.pid1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.pid0.value = (Uns32)(bport1_ab_data.pid0.value & ~(0xffffffff)) | ((0xffffffff) & (0x11));
        bport1_ab_data.icr.value = (Uns32)(bport1_ab_data.icr.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.mis.value = (Uns32)(bport1_ab_data.mis.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.ris.value = (Uns32)(bport1_ab_data.ris.value & ~(0xffffffff)) | ((0xffffffff) & (0x0f));
        bport1_ab_data.im.value = (Uns32)(bport1_ab_data.im.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.ifls.value = (Uns32)(bport1_ab_data.ifls.value & ~(0xffffffff)) | ((0xffffffff) & (0x12));
        bport1_ab_data.ctl.value = (Uns32)(bport1_ab_data.ctl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.lcrh.value = (Uns32)(bport1_ab_data.lcrh.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.ibrd.value = (Uns32)(bport1_ab_data.ibrd.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.fbrd.value = (Uns32)(bport1_ab_data.fbrd.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.fr.value = (Uns32)(bport1_ab_data.fr.value & ~(0xffffffff)) | ((0xffffffff) & (0x90));
        bport1_ab_data.rsrecr.value = (Uns32)(bport1_ab_data.rsrecr.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
        bport1_ab_data.dr.value = (Uns32)(bport1_ab_data.dr.value & ~(0xffffffff)) | ((0xffffffff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\nUART: Universal Asynchronous Receiver Transmitter\nThis model contains an accurate Register set interface for the TI Stellaris ARM Cortex-M3 based device.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "\nThe functionality of this model is limited. \nBasic status flag setting allows character reception and transmission.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "\nFreeRTOS Cortex-M3 / GCC Port LM3S102 with GCC for Luminary Micros Stellaris microcontrollers\nhttp://www.freertos.org/portcortexgcc.html");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
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
    destructor();
    return 0;
}

