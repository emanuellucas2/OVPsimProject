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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "ATCUART100", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_OSCR_maskWrite) {
    bport1_ab_data.OSCR.value = (bport1_ab_data.OSCR.value & BPORT1_AB_OSCR_WRNMASK) | (data & BPORT1_AB_OSCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SCR_maskWrite) {
    bport1_ab_data.SCR.value = (bport1_ab_data.SCR.value & BPORT1_AB_SCR_WRNMASK) | (data & BPORT1_AB_SCR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 64);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallNByteCallbacks(defaultMemRead, defaultMemWrite, 0, handles.bport1, 0x0, 0x40, True, True, False, BHM_ENDIAN_LITTLE);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abIDREV_reg = ppmCreateRegister(
            "ab_IDREV",
            "ID and Revision Register",
            handles.bport1,
            0x0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IDREV.value),
            True
        );

        ppmCreateRegisterField(abIDREV_reg, "ID", "ID Number of ACTUART100", 16, 16, 1, 0);
        ppmCreateRegisterField(abIDREV_reg, "MAJOR", "Major Revision Number", 4, 12, 1, 0);
        ppmCreateRegisterField(abIDREV_reg, "MINOR", "Minor Revision Number", 0, 4, 1, 0);
    }
    {
        registerHandle abCFG_reg = ppmCreateRegister(
            "ab_CFG",
            "Hardware Configure Register",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CFG.value),
            True
        );

        ppmCreateRegisterField(abCFG_reg, "FIFO_DEPTH", "Depth of Rx and Tx FIFO", 0, 2, 1, 0);
    }
    {
        registerHandle abOSCR_reg = ppmCreateRegister(
            "ab_OSCR",
            "Over Sample Control Register",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_OSCR_maskWrite,
            view32,
            &(bport1_ab_data.OSCR.value),
            True
        );

        ppmCreateRegisterField(abOSCR_reg, "OSC", "Over-sample Control", 0, 5, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_RBR_DLL",
            "Receiver Buffer Register / Divisor Latch LSB",
            handles.bport1,
            0x20,
            4,
            rdRBR_DLL,
            0,
            view32,
            &(bport1_ab_data.RBR_DLL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_THR_DLL",
            "Transmitter Holding Register / Divisor Latch LSB",
            handles.bport1,
            0x20,
            4,
            0,
            wrTHR_DLL,
            view32,
            &(bport1_ab_data.THR_DLL.value),
            True
        );
    }
    {
        registerHandle abIER_DLM_reg = ppmCreateRegister(
            "ab_IER_DLM",
            "Interrupt Enable Register / Divisor Latch MSB",
            handles.bport1,
            0x24,
            4,
            rdIER_DLM,
            wrIER_DLM,
            view32,
            &(bport1_ab_data.IER_DLM.value),
            True
        );

        ppmCreateRegisterField(abIER_DLM_reg, "ERBI", "Receive Data Ready Interrupt Enable", 0, 1, 1, 1);
        ppmCreateRegisterField(abIER_DLM_reg, "ETHEI", "Transmitter Holding Register Interrupt Enable", 1, 1, 1, 1);
        ppmCreateRegisterField(abIER_DLM_reg, "ELSI", "Receive Line Status Interrupt Enable", 2, 1, 1, 1);
        ppmCreateRegisterField(abIER_DLM_reg, "EMSI", "Modem Status Interrupt Enable", 3, 1, 1, 1);
    }
    {
        registerHandle abIIR_reg = ppmCreateRegister(
            "ab_IIR",
            "Interrupt Identification Register",
            handles.bport1,
            0x28,
            4,
            rdIIR,
            0,
            view32,
            &(bport1_ab_data.IIR.value),
            True
        );

        ppmCreateRegisterField(abIIR_reg, "FIFOED", "FIFOs Enabled", 6, 2, 1, 0);
        ppmCreateRegisterField(abIIR_reg, "INTRID", "Interrupt ID", 0, 4, 1, 0);
    }
    {
        registerHandle abFCR_reg = ppmCreateRegister(
            "ab_FCR",
            "FIFO ControlRegister",
            handles.bport1,
            0x28,
            4,
            0,
            wrFCR,
            view32,
            &(bport1_ab_data.FCR.value),
            True
        );

        ppmCreateRegisterField(abFCR_reg, "RFIFOT", "Receiver FIFO Trigger Level", 6, 2, 0, 1);
        ppmCreateRegisterField(abFCR_reg, "TFIFOT", "Transmitter FIFO Trigger Level", 4, 2, 0, 1);
        ppmCreateRegisterField(abFCR_reg, "DMAE", "DMA Enable", 3, 1, 0, 1);
        ppmCreateRegisterField(abFCR_reg, "TFIFORST", "Transmitter FIFO Reset", 2, 1, 0, 1);
        ppmCreateRegisterField(abFCR_reg, "RFIFORST", "Receiver FIFO Reset", 1, 1, 0, 1);
        ppmCreateRegisterField(abFCR_reg, "FIFOE", "FIFO Enable", 0, 1, 0, 1);
    }
    {
        registerHandle abLCR_reg = ppmCreateRegister(
            "ab_LCR",
            "Line Control Register",
            handles.bport1,
            0x2c,
            4,
            read_32,
            wrLCR,
            view32,
            &(bport1_ab_data.LCR.value),
            True
        );

        ppmCreateRegisterField(abLCR_reg, "DLAB", "Divisor Latch Access Bit", 7, 1, 1, 1);
        ppmCreateRegisterField(abLCR_reg, "BC", "Break Control", 6, 1, 1, 1);
        ppmCreateRegisterField(abLCR_reg, "SPS", "Stick Parity", 5, 1, 1, 1);
        ppmCreateRegisterField(abLCR_reg, "EPS", "Even Parity Select", 4, 1, 1, 1);
        ppmCreateRegisterField(abLCR_reg, "PEN", "Parity Enable", 3, 1, 1, 1);
        ppmCreateRegisterField(abLCR_reg, "STB", "Number of STOP bits", 2, 1, 1, 1);
        ppmCreateRegisterField(abLCR_reg, "WLS", "Word Length Setting", 0, 2, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_MCR",
            "Modem Control Register",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MCR.value),
            True
        );
    }
    {
        registerHandle abLSR_reg = ppmCreateRegister(
            "ab_LSR",
            "Line Status Register",
            handles.bport1,
            0x34,
            4,
            rdLSR,
            write_32,
            view32,
            &(bport1_ab_data.LSR.value),
            True
        );

        ppmCreateRegisterField(abLSR_reg, "RDR", "Data Ready", 0, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "OE", "Overrun Error", 1, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "PE", "Parity Error", 2, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "FE", "Framing Error", 3, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "LBreak", "Line Break", 4, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "THRE", "THR/FIFO Empty", 5, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "TEMT", "THR/FIFO and TFR Empty", 6, 1, 1, 1);
        ppmCreateRegisterField(abLSR_reg, "ERRF", "Receive FIFO Data Error", 7, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_MSR",
            "Modem Status Register",
            handles.bport1,
            0x38,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SCR",
            "Scratch Register",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_SCR_maskWrite,
            view32,
            &(bport1_ab_data.SCR.value),
            True
        );
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.SCR.value = (Uns32)(bport1_ab_data.SCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MSR.value = (Uns32)(bport1_ab_data.MSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LSR.value = (Uns32)(bport1_ab_data.LSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000060));
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCR.value = (Uns32)(bport1_ab_data.LCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FCR.value = (Uns32)(bport1_ab_data.FCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IIR.value = (Uns32)(bport1_ab_data.IIR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IER_DLM.value = (Uns32)(bport1_ab_data.IER_DLM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.THR_DLL.value = (Uns32)(bport1_ab_data.THR_DLL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBR_DLL.value = (Uns32)(bport1_ab_data.RBR_DLL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OSCR.value = (Uns32)(bport1_ab_data.OSCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CFG.value = (Uns32)(bport1_ab_data.CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IDREV.value = (Uns32)(bport1_ab_data.IDREV.value & ~(0xffffffff)) | ((0xffffffff) & (0x02010000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Andes UART");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "DMA not supported");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Andes AE350 Platform User Manual");
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

