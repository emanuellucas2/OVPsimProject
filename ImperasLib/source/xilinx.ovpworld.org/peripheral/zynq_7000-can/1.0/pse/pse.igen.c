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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-can", "Example");
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

static PPM_WRITE_CB(bport1_ab_AFR_maskWrite) {
    bport1_ab_data.AFR.value = (bport1_ab_data.AFR.value & BPORT1_AB_AFR_WRNMASK) | (data & BPORT1_AB_AFR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BRPR_maskWrite) {
    bport1_ab_data.BRPR.value = (bport1_ab_data.BRPR.value & BPORT1_AB_BRPR_WRNMASK) | (data & BPORT1_AB_BRPR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BTR_maskWrite) {
    bport1_ab_data.BTR.value = (bport1_ab_data.BTR.value & BPORT1_AB_BTR_WRNMASK) | (data & BPORT1_AB_BTR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ESR_maskWrite) {
    bport1_ab_data.ESR.value = (bport1_ab_data.ESR.value & BPORT1_AB_ESR_WRNMASK) | (data & BPORT1_AB_ESR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ICR_maskWrite) {
    bport1_ab_data.ICR.value = (bport1_ab_data.ICR.value & BPORT1_AB_ICR_WRNMASK) | (data & BPORT1_AB_ICR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IER_maskWrite) {
    bport1_ab_data.IER.value = (bport1_ab_data.IER.value & BPORT1_AB_IER_WRNMASK) | (data & BPORT1_AB_IER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ISR_maskWrite) {
    bport1_ab_data.ISR.value = (bport1_ab_data.ISR.value & BPORT1_AB_ISR_WRNMASK) | (data & BPORT1_AB_ISR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MSR_maskWrite) {
    bport1_ab_data.MSR.value = (bport1_ab_data.MSR.value & BPORT1_AB_MSR_WRNMASK) | (data & BPORT1_AB_MSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXFIFO_DLC_maskWrite) {
    bport1_ab_data.RXFIFO_DLC.value = (bport1_ab_data.RXFIFO_DLC.value & BPORT1_AB_RXFIFO_DLC_WRNMASK) | (data & BPORT1_AB_RXFIFO_DLC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SRR_maskWrite) {
    bport1_ab_data.SRR.value = (bport1_ab_data.SRR.value & BPORT1_AB_SRR_WRNMASK) | (data & BPORT1_AB_SRR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & BPORT1_AB_SR_WRNMASK) | (data & BPORT1_AB_SR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & BPORT1_AB_TCR_WRNMASK) | (data & BPORT1_AB_TCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WIR_maskWrite) {
    bport1_ab_data.WIR.value = (bport1_ab_data.WIR.value & BPORT1_AB_WIR_WRNMASK) | (data & BPORT1_AB_WIR_WRMASK);
}

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
        ppmCreateRegister(
            "ab_SRR",
            "Software Reset Register",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_SRR_maskWrite,
            view32,
            &(bport1_ab_data.SRR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MSR",
            "Mode Select Register",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_MSR_maskWrite,
            view32,
            &(bport1_ab_data.MSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_BRPR",
            "Baud Rate Prescaler Register",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_BRPR_maskWrite,
            view32,
            &(bport1_ab_data.BRPR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_BTR",
            "Bit Timing Register",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_BTR_maskWrite,
            view32,
            &(bport1_ab_data.BTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ECR",
            "Error Counter Register",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ECR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ESR",
            "Error Status Register",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_ESR_maskWrite,
            view32,
            &(bport1_ab_data.ESR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SR",
            "Status Register",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_SR_maskWrite,
            view32,
            &(bport1_ab_data.SR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ISR",
            "Interrupt Status Register",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_ISR_maskWrite,
            view32,
            &(bport1_ab_data.ISR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IER",
            "Interrupt Enable Register",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_IER_maskWrite,
            view32,
            &(bport1_ab_data.IER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ICR",
            "Interrupt Clear Register",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_ICR_maskWrite,
            view32,
            &(bport1_ab_data.ICR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCR",
            "Timestamp Control Register",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_TCR_maskWrite,
            view32,
            &(bport1_ab_data.TCR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_WIR",
            "Watermark Interrupt Register",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_WIR_maskWrite,
            view32,
            &(bport1_ab_data.WIR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXFIFO_ID",
            "transmit message fifo message identifier",
            handles.bport1,
            0x30,
            4,
            0,
            wrFIFOId,
            view32,
            &(bport1_ab_data.TXFIFO_ID.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXFIFO_DLC",
            "transmit message fifo data length code",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXFIFO_DLC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXFIFO_DATA1",
            "transmit message fifo data word 1",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXFIFO_DATA1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXFIFO_DATA2",
            "transmit message fifo data word 2",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXFIFO_DATA2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXHPB_ID",
            "transmit high priority buffer message identifier",
            handles.bport1,
            0x40,
            4,
            0,
            wrHPBId,
            view32,
            &(bport1_ab_data.TXHPB_ID.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXHPB_DLC",
            "transmit high priority buffer data length code",
            handles.bport1,
            0x44,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXHPB_DLC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXHPB_DATA1",
            "transmit high priority buffer data word 1",
            handles.bport1,
            0x48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXHPB_DATA1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXHPB_DATA2",
            "transmit high priority buffer data word 2",
            handles.bport1,
            0x4c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXHPB_DATA2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RXFIFO_ID",
            "receive message fifo message identifier",
            handles.bport1,
            0x50,
            4,
            rxFIFOId,
            0,
            view32,
            &(bport1_ab_data.RXFIFO_ID.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RXFIFO_DLC",
            "receive message fifo data length code",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_RXFIFO_DLC_maskWrite,
            view32,
            &(bport1_ab_data.RXFIFO_DLC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RXFIFO_DATA1",
            "receive message fifo data word 1",
            handles.bport1,
            0x58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.RXFIFO_DATA1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RXFIFO_DATA2",
            "receive message fifo data word 2",
            handles.bport1,
            0x5c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.RXFIFO_DATA2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFR",
            "Acceptance Filter Register",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_AFR_maskWrite,
            view32,
            &(bport1_ab_data.AFR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFMR1",
            "Acceptance Filter Mask Register 1",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFMR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFIR1",
            "Acceptance Filter ID Register 1",
            handles.bport1,
            0x68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFIR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFMR2",
            "Acceptance Filter Mask Register 2",
            handles.bport1,
            0x6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFMR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFIR2",
            "Acceptance Filter ID Register 2",
            handles.bport1,
            0x70,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFIR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFMR3",
            "Acceptance Filter Mask Register 3",
            handles.bport1,
            0x74,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFMR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFIR3",
            "Acceptance Filter ID Register 3",
            handles.bport1,
            0x78,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFIR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFMR4",
            "Acceptance Filter Mask Register 4",
            handles.bport1,
            0x7c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFMR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_AFIR4",
            "Acceptance Filter ID Register 4",
            handles.bport1,
            0x80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.AFIR4.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.AFIR4.value = (Uns32)(bport1_ab_data.AFIR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFMR4.value = (Uns32)(bport1_ab_data.AFMR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFIR3.value = (Uns32)(bport1_ab_data.AFIR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFMR3.value = (Uns32)(bport1_ab_data.AFMR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFIR2.value = (Uns32)(bport1_ab_data.AFIR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFMR2.value = (Uns32)(bport1_ab_data.AFMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFIR1.value = (Uns32)(bport1_ab_data.AFIR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFMR1.value = (Uns32)(bport1_ab_data.AFMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.AFR.value = (Uns32)(bport1_ab_data.AFR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFIFO_DATA2.value = (Uns32)(bport1_ab_data.RXFIFO_DATA2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFIFO_DATA1.value = (Uns32)(bport1_ab_data.RXFIFO_DATA1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFIFO_DLC.value = (Uns32)(bport1_ab_data.RXFIFO_DLC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFIFO_ID.value = (Uns32)(bport1_ab_data.RXFIFO_ID.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXHPB_DATA2.value = (Uns32)(bport1_ab_data.TXHPB_DATA2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXHPB_DATA1.value = (Uns32)(bport1_ab_data.TXHPB_DATA1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXHPB_DLC.value = (Uns32)(bport1_ab_data.TXHPB_DLC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXHPB_ID.value = (Uns32)(bport1_ab_data.TXHPB_ID.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFIFO_DATA2.value = (Uns32)(bport1_ab_data.TXFIFO_DATA2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFIFO_DATA1.value = (Uns32)(bport1_ab_data.TXFIFO_DATA1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFIFO_DLC.value = (Uns32)(bport1_ab_data.TXFIFO_DLC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFIFO_ID.value = (Uns32)(bport1_ab_data.TXFIFO_ID.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.WIR.value = (Uns32)(bport1_ab_data.WIR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003F3F));
        bport1_ab_data.TCR.value = (Uns32)(bport1_ab_data.TCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ICR.value = (Uns32)(bport1_ab_data.ICR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IER.value = (Uns32)(bport1_ab_data.IER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ISR.value = (Uns32)(bport1_ab_data.ISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00006000));
        bport1_ab_data.SR.value = (Uns32)(bport1_ab_data.SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.ESR.value = (Uns32)(bport1_ab_data.ESR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ECR.value = (Uns32)(bport1_ab_data.ECR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BTR.value = (Uns32)(bport1_ab_data.BTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BRPR.value = (Uns32)(bport1_ab_data.BRPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MSR.value = (Uns32)(bport1_ab_data.MSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRR.value = (Uns32)(bport1_ab_data.SRR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 CAN Registers");
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

