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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisSPI", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CTAR0_maskWrite) {
    bport1_ab_data.CTAR0.value = (bport1_ab_data.CTAR0.value & BPORT1_AB_CTAR0_WRNMASK) | (data & BPORT1_AB_CTAR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CTAR1_maskWrite) {
    bport1_ab_data.CTAR1.value = (bport1_ab_data.CTAR1.value & BPORT1_AB_CTAR1_WRNMASK) | (data & BPORT1_AB_CTAR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & BPORT1_AB_MCR_WRNMASK) | (data & BPORT1_AB_MCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PUSHR_maskWrite) {
    bport1_ab_data.PUSHR.value = (bport1_ab_data.PUSHR.value & BPORT1_AB_PUSHR_WRNMASK) | (data & BPORT1_AB_PUSHR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RSER_maskWrite) {
    bport1_ab_data.RSER.value = (bport1_ab_data.RSER.value & BPORT1_AB_RSER_WRNMASK) | (data & BPORT1_AB_RSER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & BPORT1_AB_SR_WRNMASK) | (data & BPORT1_AB_SR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & BPORT1_AB_TCR_WRNMASK) | (data & BPORT1_AB_TCR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abMCR_reg = ppmCreateRegister(
            "ab_MCR",
            "DSPI Module Configuration Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_MCR_maskWrite,
            view32,
            &(bport1_ab_data.MCR.value),
            True
        );

        ppmCreateRegisterField(abMCR_reg, "CLR_RXF", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "CLR_TXF", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "CONT_SCKE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DCONF", 0, 28, 2, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DIS_RXF", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DIS_TXF", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DOZE", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "FRZ", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "HALT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MDIS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MSTR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MTFE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "PCSIS", 0, 16, 6, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "PCSSE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "ROOE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SMPL_PT", 0, 8, 2, 1, 1);
    }
    {
        registerHandle abTCR_reg = ppmCreateRegister(
            "ab_TCR",
            "DSPI Transfer Count Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_TCR_maskWrite,
            view32,
            &(bport1_ab_data.TCR.value),
            True
        );

        ppmCreateRegisterField(abTCR_reg, "SPI_TCNT", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCTAR0_reg = ppmCreateRegister(
            "ab_CTAR0",
            "DSPI Clock and Transfer Attributes Register 0, Master/Slave modes, offset 0x0c",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_CTAR0_maskWrite,
            view32,
            &(bport1_ab_data.CTAR0.value),
            True
        );

        ppmCreateRegisterField(abCTAR0_reg, "ASC", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "BR", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "CPHA", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "CPOL", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "CSSCK", 0, 12, 4, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "DBR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "DT", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "FMSZ", 0, 27, 4, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "LSBFE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "PASC", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "PBR", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "PCSSCK", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abCTAR0_reg, "PDT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abCTAR1_reg = ppmCreateRegister(
            "ab_CTAR1",
            "DSPI Clock and Transfer Attributes Register 1, Master mode, offset 0x10",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_CTAR1_maskWrite,
            view32,
            &(bport1_ab_data.CTAR1.value),
            True
        );

        ppmCreateRegisterField(abCTAR1_reg, "ASC", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "BR", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "CPHA", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "CPOL", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "CSSCK", 0, 12, 4, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "DBR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "DT", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "FMSZ", 0, 27, 4, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "LSBFE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "PASC", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "PBR", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "PCSSCK", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abCTAR1_reg, "PDT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abSR_reg = ppmCreateRegister(
            "ab_SR",
            "DSPI Status Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_SR_maskWrite,
            view32,
            &(bport1_ab_data.SR.value),
            True
        );

        ppmCreateRegisterField(abSR_reg, "EOQF", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "POPNXTPTR", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abSR_reg, "RFDF", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "RFOF", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "RXCTR", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TCF", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TFFF", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TFUF", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TXCTR", 0, 12, 4, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TXNXTPTR", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TXRXS", 0, 30, 1, 1, 1);
    }
    {
        registerHandle abRSER_reg = ppmCreateRegister(
            "ab_RSER",
            "DSPI DMA/Interrupt Request Select and Enable Register, offset: 0x30 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_RSER_maskWrite,
            view32,
            &(bport1_ab_data.RSER.value),
            True
        );

        ppmCreateRegisterField(abRSER_reg, "EOQF_RE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "RFDF_DIRS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "RFDF_RE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "RFOF_RE", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TCF_RE", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TFFF_DIRS", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TFFF_RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TFUF_RE", 0, 27, 1, 1, 1);
    }
    {
        registerHandle abPUSHR_reg = ppmCreateRegister(
            "ab_PUSHR",
            "DSPI PUSH TX FIFO Register In Master Mode, offset: 0x34 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_PUSHR_maskWrite,
            view32,
            &(bport1_ab_data.PUSHR.value),
            True
        );

        ppmCreateRegisterField(abPUSHR_reg, "CONT", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abPUSHR_reg, "CTAS", 0, 28, 3, 1, 1);
        ppmCreateRegisterField(abPUSHR_reg, "CTCNT", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abPUSHR_reg, "EOQ", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abPUSHR_reg, "PCS", 0, 16, 6, 1, 1);
        ppmCreateRegisterField(abPUSHR_reg, "TXDATA", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abPOPR_reg = ppmCreateRegister(
            "ab_POPR",
            "DSPI POP RX FIFO Register, offset: 0x38 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.POPR.value),
            True
        );

        ppmCreateRegisterField(abPOPR_reg, "RXDATA", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abTXFR0_reg = ppmCreateRegister(
            "ab_TXFR0",
            "DSPI Transmit FIFO Registers, offset: 0x3C ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TXFR0.value),
            True
        );

        ppmCreateRegisterField(abTXFR0_reg, "TXCMD_TXDATA", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abTXFR0_reg, "TXDATA", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abTXFR1_reg = ppmCreateRegister(
            "ab_TXFR1",
            "DSPI Transmit FIFO Registers, offset: 0x40 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TXFR1.value),
            True
        );

        ppmCreateRegisterField(abTXFR1_reg, "TXCMD_TXDATA", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abTXFR1_reg, "TXDATA", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abTXFR2_reg = ppmCreateRegister(
            "ab_TXFR2",
            "DSPI Transmit FIFO Registers, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TXFR2.value),
            True
        );

        ppmCreateRegisterField(abTXFR2_reg, "TXCMD_TXDATA", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abTXFR2_reg, "TXDATA", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abTXFR3_reg = ppmCreateRegister(
            "ab_TXFR3",
            "DSPI Transmit FIFO Registers, offset: 0x48 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TXFR3.value),
            True
        );

        ppmCreateRegisterField(abTXFR3_reg, "TXCMD_TXDATA", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abTXFR3_reg, "TXDATA", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abRXFR0_reg = ppmCreateRegister(
            "ab_RXFR0",
            "DSPI Receive FIFO Registers, offset: 0x7C ",
            handles.bport1,
            0x7c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RXFR0.value),
            True
        );

        ppmCreateRegisterField(abRXFR0_reg, "RXDATA", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abRXFR1_reg = ppmCreateRegister(
            "ab_RXFR1",
            "DSPI Receive FIFO Registers, offset: 0x80 ",
            handles.bport1,
            0x80,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RXFR1.value),
            True
        );

        ppmCreateRegisterField(abRXFR1_reg, "RXDATA", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abRXFR2_reg = ppmCreateRegister(
            "ab_RXFR2",
            "DSPI Receive FIFO Registers, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RXFR2.value),
            True
        );

        ppmCreateRegisterField(abRXFR2_reg, "RXDATA", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abRXFR3_reg = ppmCreateRegister(
            "ab_RXFR3",
            "DSPI Receive FIFO Registers, offset: 0x88 ",
            handles.bport1,
            0x88,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RXFR3.value),
            True
        );

        ppmCreateRegisterField(abRXFR3_reg, "RXDATA", 0, 0, 32, 1, 0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.RXFR3.value = (Uns32)(bport1_ab_data.RXFR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFR2.value = (Uns32)(bport1_ab_data.RXFR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFR1.value = (Uns32)(bport1_ab_data.RXFR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RXFR0.value = (Uns32)(bport1_ab_data.RXFR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFR3.value = (Uns32)(bport1_ab_data.TXFR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFR2.value = (Uns32)(bport1_ab_data.TXFR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFR1.value = (Uns32)(bport1_ab_data.TXFR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFR0.value = (Uns32)(bport1_ab_data.TXFR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.POPR.value = (Uns32)(bport1_ab_data.POPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PUSHR.value = (Uns32)(bport1_ab_data.PUSHR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RSER.value = (Uns32)(bport1_ab_data.RSER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SR.value = (Uns32)(bport1_ab_data.SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CTAR1.value = (Uns32)(bport1_ab_data.CTAR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x78000000));
        bport1_ab_data.CTAR0.value = (Uns32)(bport1_ab_data.CTAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x78000000));
        bport1_ab_data.TCR.value = (Uns32)(bport1_ab_data.TCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00004001));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the SPI peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
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
    return 0;
}

