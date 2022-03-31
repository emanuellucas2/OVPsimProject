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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "16550_4bytes", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_mcr_maskWrite) {
    bport1_ab_data.mcr.value = (bport1_ab_data.mcr.value & BPORT1_AB_MCR_WRNMASK) | (data & BPORT1_AB_MCR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 64);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_rbr_dll",
            "UART Receiver Buffer Register/Divisor Latch Low Read (LCR.DLAB=1)",
            handles.bport1,
            0x0,
            1,
            readRBR_DLL,
            0,
            viewRBR_DLL,
            &(bport1_ab_data.rbr_dll.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_thr_dll",
            "UART Transmitter Holding Register/Divisor Latch Low Write (LCR.DLAB=1)",
            handles.bport1,
            0x0,
            1,
            0,
            writeTHR_DLL,
            viewTHR_DLL,
            &(bport1_ab_data.thr_dll.value),
            True
        );
    }
    {
        registerHandle abier_dlh_reg = ppmCreateRegister(
            "ab_ier_dlh",
            "UART Interrupt Enable Register/Divisor Latch High (LCR.DLAB=1)",
            handles.bport1,
            0x4,
            1,
            readIER_DLH,
            writeIER_DLH,
            viewIER_DLH,
            &(bport1_ab_data.ier_dlh.value),
            True
        );

        ppmCreateRegisterField(abier_dlh_reg, "erbfi", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abier_dlh_reg, "etbei", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abier_dlh_reg, "elsi", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abier_dlh_reg, "edssi", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abiir_reg = ppmCreateRegister(
            "ab_iir",
            "UART Interrupt Identity Register",
            handles.bport1,
            0x8,
            1,
            readIIR,
            0,
            viewIIR,
            &(bport1_ab_data.iir.value),
            True
        );

        ppmCreateRegisterField(abiir_reg, "intid", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abiir_reg, "fifoen", 0, 6, 2, 1, 0);
    }
    {
        registerHandle abfcr_reg = ppmCreateRegister(
            "ab_fcr",
            "UART FIFO Control Register",
            handles.bport1,
            0x8,
            1,
            0,
            writeFCR,
            view8,
            &(bport1_ab_data.fcr.value),
            True
        );

        ppmCreateRegisterField(abfcr_reg, "fifoEn", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(abfcr_reg, "fifoRcvrRst", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(abfcr_reg, "fifoXmitRst", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(abfcr_reg, "dmaModeSel", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(abfcr_reg, "fifoXmitTrig", 0, 4, 2, 0, 1);
        ppmCreateRegisterField(abfcr_reg, "fifoRcvrTrig", 0, 6, 2, 0, 1);
    }
    {
        registerHandle ablcr_reg = ppmCreateRegister(
            "ab_lcr",
            "UART Line Control Register",
            handles.bport1,
            0xc,
            1,
            read_8,
            writeLCR,
            view8,
            &(bport1_ab_data.lcr.value),
            True
        );

        ppmCreateRegisterField(ablcr_reg, "dls", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(ablcr_reg, "stop", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(ablcr_reg, "pen", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(ablcr_reg, "eps", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(ablcr_reg, "stick", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(ablcr_reg, "brk", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(ablcr_reg, "dlab", 0, 7, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_mcr",
            "UART MODEM Control Register",
            handles.bport1,
            0x10,
            1,
            read_8,
            bport1_ab_mcr_maskWrite,
            view8,
            &(bport1_ab_data.mcr.value),
            True
        );
    }
    {
        registerHandle ablsr_reg = ppmCreateRegister(
            "ab_lsr",
            "UART Line Status Register",
            handles.bport1,
            0x14,
            1,
            readLSR,
            0,
            viewLSR,
            &(bport1_ab_data.lsr.value),
            True
        );

        ppmCreateRegisterField(ablsr_reg, "dr", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "oe", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "pe", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "fe", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "bi", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "thre", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "temt", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(ablsr_reg, "rfe", 0, 7, 1, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_msr",
            "UART MODEM Status Register",
            handles.bport1,
            0x18,
            1,
            read_8,
            write_8,
            view8,
            &(bport1_ab_data.msr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_scr",
            "UART Scratch Register",
            handles.bport1,
            0x1c,
            1,
            read_8,
            write_8,
            view8,
            &(bport1_ab_data.scr.value),
            True
        );
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.msr.value = (Uns8)(bport1_ab_data.msr.value & ~(0xff)) | ((0xff) & (0xb0));
        bport1_ab_data.mcr.value = (Uns8)(bport1_ab_data.mcr.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.lcr.value = (Uns8)(bport1_ab_data.lcr.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.fcr.value = (Uns8)(bport1_ab_data.fcr.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.iir.value = (Uns8)(bport1_ab_data.iir.value & ~(0xff)) | ((0xff) & (0x01));
        bport1_ab_data.ier_dlh.value = (Uns8)(bport1_ab_data.ier_dlh.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.thr_dll.value = (Uns8)(bport1_ab_data.thr_dll.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.rbr_dll.value = (Uns8)(bport1_ab_data.rbr_dll.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "16550 UART model");
        ppmDocAddText(doc_12_node, "The serial input/output from the simulator is implemented using the Serial Device Support described in OVP BHM and PPM API Functions Reference, which describes the parameters that control how the model interacts with the host computer.");
        ppmDocAddText(doc_12_node, "Interrupts and FIFOs are supported.");
        ppmDocAddText(doc_12_node, "Registers are aligned on 4 byte boundaries.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Resolution of the baud rate is limited to the simulation time slice (aka quantum) size.");
        ppmDocAddText(doc_22_node, "Values written to the MCR are ignored. Loopback mode is not supported.");
        ppmDocAddText(doc_22_node, "The LSR is read-only. The model never sets the LSR 'Parity Error', 'Framing Error', 'Break Interrupt' or 'Error in RCVR FIFO' bits.");
        ppmDocAddText(doc_22_node, "The MSR 'Data Set Ready' and 'Clear To Send' bits are set at reset and all other MSR bits are cleared. MSR bits will only be changed by writes to the MSR and values written to the Modem Status Register do not effect the operation of the model.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "PC16550D Universal Asynchronous Receiver/Transmitter with FIFOs datasheet (http://www.ti.com/lit/ds/symlink/pc16550d.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
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

