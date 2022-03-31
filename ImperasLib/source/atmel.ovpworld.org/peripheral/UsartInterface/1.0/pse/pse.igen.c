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

apb_REG_dataT apb_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UsartInterface", "Example");
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
    handles.apb = ppmCreateSlaveBusPort("apb", 16384);
    if (!handles.apb) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'apb'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGUS_CR_reg = ppmCreateRegister(
            "REG_US_CR",
            0,
            handles.apb,
            0x0,
            4,
            0,
            US_CR_wcb,
            view32,
            &(apb_REG_data.US_CR.value),
            True
        );

        ppmCreateRegisterField(REGUS_CR_reg, "SENDA", 0, 12, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "STTTO", 0, 11, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "STPBRK", 0, 10, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "STTBRK", 0, 9, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "RSTSTA", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "TXDIS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "TXEN", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "RXDIS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "RXEN", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "RSTTX", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGUS_CR_reg, "RSTRX", 0, 2, 1, 0, 1);
    }
    {
        registerHandle REGUS_MR_reg = ppmCreateRegister(
            "REG_US_MR",
            0,
            handles.apb,
            0x4,
            4,
            read_32,
            US_MR_wcb,
            view32,
            &(apb_REG_data.US_MR.value),
            True
        );

        ppmCreateRegisterField(REGUS_MR_reg, "CLKO", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "MODE9", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "CHMODE", 0, 14, 2, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "NBSTOP", 0, 12, 2, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "PAR", 0, 9, 3, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "SYNC", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "CHRL", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(REGUS_MR_reg, "HSCLKS", 0, 4, 2, 1, 1);
    }
    {
        registerHandle REGUS_IER_reg = ppmCreateRegister(
            "REG_US_IER",
            0,
            handles.apb,
            0x8,
            4,
            0,
            US_IER_wcb,
            view32,
            &(apb_REG_data.US_IER.value),
            True
        );

        ppmCreateRegisterField(REGUS_IER_reg, "TXEMPTY", 0, 9, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "TIMEOUT", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "PARE", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "FRAME", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "OVRE", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "ENDTX", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "ENDRX", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "RXBRK", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "TXRDY", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IER_reg, "RXRDY", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGUS_IDR_reg = ppmCreateRegister(
            "REG_US_IDR",
            0,
            handles.apb,
            0xc,
            4,
            0,
            US_IDR_wcb,
            view32,
            &(apb_REG_data.US_IDR.value),
            True
        );

        ppmCreateRegisterField(REGUS_IDR_reg, "TXEMPTY", 0, 9, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "TIMEOUT", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "PARE", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "FRAME", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "OVRE", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "ENDTX", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "ENDRX", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "RXBRK", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "TXRDY", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGUS_IDR_reg, "RXRDY", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGUS_IMR_reg = ppmCreateRegister(
            "REG_US_IMR",
            0,
            handles.apb,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(apb_REG_data.US_IMR.value),
            True
        );

        ppmCreateRegisterField(REGUS_IMR_reg, "TXEMPTY", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "TIMEOUT", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "PARE", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "FRAME", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "OVRE", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "ENDTX", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "ENDRX", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "RXBRK", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "TXRDY", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGUS_IMR_reg, "RXRDY", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGUS_CSR_reg = ppmCreateRegister(
            "REG_US_CSR",
            0,
            handles.apb,
            0x14,
            4,
            US_RHR_rcb,
            0,
            view32,
            &(apb_REG_data.US_CSR.value),
            True
        );

        ppmCreateRegisterField(REGUS_CSR_reg, "TXEMPTY", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "TIMEOUT", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "PARE", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "FRAME", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "OVRE", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "ENDTX", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "ENDRX", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "RXBRK", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "TXRDY", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGUS_CSR_reg, "RXRDY", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGUS_RHR_reg = ppmCreateRegister(
            "REG_US_RHR",
            0,
            handles.apb,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(apb_REG_data.US_RHR.value),
            True
        );

        ppmCreateRegisterField(REGUS_RHR_reg, "RXCHR", 0, 0, 8, 1, 0);
    }
    {
        registerHandle REGUS_THR_reg = ppmCreateRegister(
            "REG_US_THR",
            0,
            handles.apb,
            0x1c,
            4,
            0,
            US_THR_wcb,
            view32,
            &(apb_REG_data.US_THR.value),
            True
        );

        ppmCreateRegisterField(REGUS_THR_reg, "TXCHR", 0, 0, 8, 0, 1);
    }
    {
        registerHandle REGUS_BRGR_reg = ppmCreateRegister(
            "REG_US_BRGR",
            0,
            handles.apb,
            0x20,
            4,
            read_32,
            US_BRGR_wcb,
            view32,
            &(apb_REG_data.US_BRGR.value),
            True
        );

        ppmCreateRegisterField(REGUS_BRGR_reg, "CD", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGUS_RTOR_reg = ppmCreateRegister(
            "REG_US_RTOR",
            0,
            handles.apb,
            0x24,
            4,
            read_32,
            US_RTOR_wcb,
            view32,
            &(apb_REG_data.US_RTOR.value),
            True
        );

        ppmCreateRegisterField(REGUS_RTOR_reg, "TO", 0, 0, 8, 1, 1);
    }
    {
        registerHandle REGUS_TTGR_reg = ppmCreateRegister(
            "REG_US_TTGR",
            0,
            handles.apb,
            0x28,
            4,
            read_32,
            US_TTGR_wcb,
            view32,
            &(apb_REG_data.US_TTGR.value),
            True
        );

        ppmCreateRegisterField(REGUS_TTGR_reg, "TG", 0, 0, 8, 1, 1);
    }
    {
        registerHandle REGUS_RPR_reg = ppmCreateRegister(
            "REG_US_RPR",
            0,
            handles.apb,
            0x30,
            4,
            read_32,
            US_RPR_wcb,
            view32,
            &(apb_REG_data.US_RPR.value),
            True
        );

        ppmCreateRegisterField(REGUS_RPR_reg, "RXPTR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGUS_RCR_reg = ppmCreateRegister(
            "REG_US_RCR",
            0,
            handles.apb,
            0x34,
            4,
            read_32,
            US_RCR_wcb,
            view32,
            &(apb_REG_data.US_RCR.value),
            True
        );

        ppmCreateRegisterField(REGUS_RCR_reg, "RXCTR", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGUS_TPR_reg = ppmCreateRegister(
            "REG_US_TPR",
            0,
            handles.apb,
            0x38,
            4,
            read_32,
            US_TPR_wcb,
            view32,
            &(apb_REG_data.US_TPR.value),
            True
        );

        ppmCreateRegisterField(REGUS_TPR_reg, "TXPTR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGUS_TCR_reg = ppmCreateRegister(
            "REG_US_TCR",
            0,
            handles.apb,
            0x3c,
            4,
            read_32,
            US_TCR_wcb,
            view32,
            &(apb_REG_data.US_TCR.value),
            True
        );

        ppmCreateRegisterField(REGUS_TCR_reg, "TXCTR", 0, 0, 16, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.asb = ppmOpenAddressSpace("asb");
    if (!handles.asb) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'asb'");
    }
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        apb_REG_data.US_TCR.value = (Uns32)(apb_REG_data.US_TCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_TPR.value = (Uns32)(apb_REG_data.US_TPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_RCR.value = (Uns32)(apb_REG_data.US_RCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_RPR.value = (Uns32)(apb_REG_data.US_RPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_TTGR.value = (Uns32)(apb_REG_data.US_TTGR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_RTOR.value = (Uns32)(apb_REG_data.US_RTOR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_BRGR.value = (Uns32)(apb_REG_data.US_BRGR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_THR.value = (Uns32)(apb_REG_data.US_THR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_RHR.value = (Uns32)(apb_REG_data.US_RHR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_CSR.value = (Uns32)(apb_REG_data.US_CSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x18));
        apb_REG_data.US_IMR.value = (Uns32)(apb_REG_data.US_IMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_IDR.value = (Uns32)(apb_REG_data.US_IDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_IER.value = (Uns32)(apb_REG_data.US_IER.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_MR.value = (Uns32)(apb_REG_data.US_MR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        apb_REG_data.US_CR.value = (Uns32)(apb_REG_data.US_CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "USART: Universal Synchronous/Asynchronous Receiver Transmitter\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux.\nThe USART has its own baud rate generator, and two dedicated Peripheral Data Controller.\nchannels. The data format includes a start bit, up to 8 data bits, an optional programmable parity bit and up to 2 stop bits.\nThe USART also features a Receiver Timeout register, facilitating variable length frame support\nwhen it is working with the PDC, and a Time-guard register, used when interfacing with slow remote equipment.\nfor more information visit http://www.atmel.com/products/at91");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D ARM08/02");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
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

