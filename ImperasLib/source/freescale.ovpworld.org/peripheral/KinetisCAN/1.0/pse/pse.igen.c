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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisCAN", "Example");
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

static PPM_WRITE_CB(bport1_ab_CTRL1_maskWrite) {
    bport1_ab_data.CTRL1.value = (bport1_ab_data.CTRL1.value & BPORT1_AB_CTRL1_WRNMASK) | (data & BPORT1_AB_CTRL1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CTRL2_maskWrite) {
    bport1_ab_data.CTRL2.value = (bport1_ab_data.CTRL2.value & BPORT1_AB_CTRL2_WRNMASK) | (data & BPORT1_AB_CTRL2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ECR_maskWrite) {
    bport1_ab_data.ECR.value = (bport1_ab_data.ECR.value & BPORT1_AB_ECR_WRNMASK) | (data & BPORT1_AB_ECR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ESR1_maskWrite) {
    bport1_ab_data.ESR1.value = (bport1_ab_data.ESR1.value & BPORT1_AB_ESR1_WRNMASK) | (data & BPORT1_AB_ESR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IFLAG1_maskWrite) {
    bport1_ab_data.IFLAG1.value = (bport1_ab_data.IFLAG1.value & BPORT1_AB_IFLAG1_WRNMASK) | (data & BPORT1_AB_IFLAG1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IFLAG2_maskWrite) {
    bport1_ab_data.IFLAG2.value = (bport1_ab_data.IFLAG2.value & BPORT1_AB_IFLAG2_WRNMASK) | (data & BPORT1_AB_IFLAG2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IMASK1_maskWrite) {
    bport1_ab_data.IMASK1.value = (bport1_ab_data.IMASK1.value & BPORT1_AB_IMASK1_WRNMASK) | (data & BPORT1_AB_IMASK1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IMASK2_maskWrite) {
    bport1_ab_data.IMASK2.value = (bport1_ab_data.IMASK2.value & BPORT1_AB_IMASK2_WRNMASK) | (data & BPORT1_AB_IMASK2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & BPORT1_AB_MCR_WRNMASK) | (data & BPORT1_AB_MCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RX14MASK_maskWrite) {
    bport1_ab_data.RX14MASK.value = (bport1_ab_data.RX14MASK.value & BPORT1_AB_RX14MASK_WRNMASK) | (data & BPORT1_AB_RX14MASK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RX15MASK_maskWrite) {
    bport1_ab_data.RX15MASK.value = (bport1_ab_data.RX15MASK.value & BPORT1_AB_RX15MASK_WRNMASK) | (data & BPORT1_AB_RX15MASK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXFGMASK_maskWrite) {
    bport1_ab_data.RXFGMASK.value = (bport1_ab_data.RXFGMASK.value & BPORT1_AB_RXFGMASK_WRNMASK) | (data & BPORT1_AB_RXFGMASK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR0_maskWrite) {
    bport1_ab_data.RXIMR0.value = (bport1_ab_data.RXIMR0.value & BPORT1_AB_RXIMR0_WRNMASK) | (data & BPORT1_AB_RXIMR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR10_maskWrite) {
    bport1_ab_data.RXIMR10.value = (bport1_ab_data.RXIMR10.value & BPORT1_AB_RXIMR10_WRNMASK) | (data & BPORT1_AB_RXIMR10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR11_maskWrite) {
    bport1_ab_data.RXIMR11.value = (bport1_ab_data.RXIMR11.value & BPORT1_AB_RXIMR11_WRNMASK) | (data & BPORT1_AB_RXIMR11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR12_maskWrite) {
    bport1_ab_data.RXIMR12.value = (bport1_ab_data.RXIMR12.value & BPORT1_AB_RXIMR12_WRNMASK) | (data & BPORT1_AB_RXIMR12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR13_maskWrite) {
    bport1_ab_data.RXIMR13.value = (bport1_ab_data.RXIMR13.value & BPORT1_AB_RXIMR13_WRNMASK) | (data & BPORT1_AB_RXIMR13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR14_maskWrite) {
    bport1_ab_data.RXIMR14.value = (bport1_ab_data.RXIMR14.value & BPORT1_AB_RXIMR14_WRNMASK) | (data & BPORT1_AB_RXIMR14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR15_maskWrite) {
    bport1_ab_data.RXIMR15.value = (bport1_ab_data.RXIMR15.value & BPORT1_AB_RXIMR15_WRNMASK) | (data & BPORT1_AB_RXIMR15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR1_maskWrite) {
    bport1_ab_data.RXIMR1.value = (bport1_ab_data.RXIMR1.value & BPORT1_AB_RXIMR1_WRNMASK) | (data & BPORT1_AB_RXIMR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR2_maskWrite) {
    bport1_ab_data.RXIMR2.value = (bport1_ab_data.RXIMR2.value & BPORT1_AB_RXIMR2_WRNMASK) | (data & BPORT1_AB_RXIMR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR3_maskWrite) {
    bport1_ab_data.RXIMR3.value = (bport1_ab_data.RXIMR3.value & BPORT1_AB_RXIMR3_WRNMASK) | (data & BPORT1_AB_RXIMR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR4_maskWrite) {
    bport1_ab_data.RXIMR4.value = (bport1_ab_data.RXIMR4.value & BPORT1_AB_RXIMR4_WRNMASK) | (data & BPORT1_AB_RXIMR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR5_maskWrite) {
    bport1_ab_data.RXIMR5.value = (bport1_ab_data.RXIMR5.value & BPORT1_AB_RXIMR5_WRNMASK) | (data & BPORT1_AB_RXIMR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR6_maskWrite) {
    bport1_ab_data.RXIMR6.value = (bport1_ab_data.RXIMR6.value & BPORT1_AB_RXIMR6_WRNMASK) | (data & BPORT1_AB_RXIMR6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR7_maskWrite) {
    bport1_ab_data.RXIMR7.value = (bport1_ab_data.RXIMR7.value & BPORT1_AB_RXIMR7_WRNMASK) | (data & BPORT1_AB_RXIMR7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR8_maskWrite) {
    bport1_ab_data.RXIMR8.value = (bport1_ab_data.RXIMR8.value & BPORT1_AB_RXIMR8_WRNMASK) | (data & BPORT1_AB_RXIMR8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXIMR9_maskWrite) {
    bport1_ab_data.RXIMR9.value = (bport1_ab_data.RXIMR9.value & BPORT1_AB_RXIMR9_WRNMASK) | (data & BPORT1_AB_RXIMR9_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RXMGMASK_maskWrite) {
    bport1_ab_data.RXMGMASK.value = (bport1_ab_data.RXMGMASK.value & BPORT1_AB_RXMGMASK_WRNMASK) | (data & BPORT1_AB_RXMGMASK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIMER_maskWrite) {
    bport1_ab_data.TIMER.value = (bport1_ab_data.TIMER.value & BPORT1_AB_TIMER_WRNMASK) | (data & BPORT1_AB_TIMER_WRMASK);
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
            "Module Configuration Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_MCR_maskWrite,
            view32,
            &(bport1_ab_data.MCR.value),
            True
        );

        ppmCreateRegisterField(abMCR_reg, "MAXMB", 0, 0, 7, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "IDAM", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "AEN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "LPRIOEN", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "IRMQ", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SRXDIS", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DOZE", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "LPMACK", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "WRNEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SLFWAK", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SUPV", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "FRZACK", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SOFTRST", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "WAKMSK", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "NOTRDY", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "HALT", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "RFEN", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "FRZ", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MDIS", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abCTRL1_reg = ppmCreateRegister(
            "ab_CTRL1",
            "Control 1 Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_CTRL1_maskWrite,
            view32,
            &(bport1_ab_data.CTRL1.value),
            True
        );

        ppmCreateRegisterField(abCTRL1_reg, "PROPSEG", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "LOM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "LBUF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "TSYN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "BOFFREC", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "SMP", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "RWRNMSK", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "TWRNMSK", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "LPB", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "CLKSRC", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "ERRMSK", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "BOFFMSK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "PSEG2", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "PSEG1", 0, 19, 3, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "RJW", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abCTRL1_reg, "PRESDIV", 0, 24, 8, 1, 1);
    }
    {
        registerHandle abTIMER_reg = ppmCreateRegister(
            "ab_TIMER",
            "Free Running Timer, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_TIMER_maskWrite,
            view32,
            &(bport1_ab_data.TIMER.value),
            True
        );

        ppmCreateRegisterField(abTIMER_reg, "TIMER", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abRXMGMASK_reg = ppmCreateRegister(
            "ab_RXMGMASK",
            "Rx Mailboxes Global Mask Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_RXMGMASK_maskWrite,
            view32,
            &(bport1_ab_data.RXMGMASK.value),
            True
        );

        ppmCreateRegisterField(abRXMGMASK_reg, "MG", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRX14MASK_reg = ppmCreateRegister(
            "ab_RX14MASK",
            "Rx 14 Mask Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_RX14MASK_maskWrite,
            view32,
            &(bport1_ab_data.RX14MASK.value),
            True
        );

        ppmCreateRegisterField(abRX14MASK_reg, "RX14M", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRX15MASK_reg = ppmCreateRegister(
            "ab_RX15MASK",
            "Rx 15 Mask Register, offset: 0x18 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_RX15MASK_maskWrite,
            view32,
            &(bport1_ab_data.RX15MASK.value),
            True
        );

        ppmCreateRegisterField(abRX15MASK_reg, "RX15M", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abECR_reg = ppmCreateRegister(
            "ab_ECR",
            "Error Counter, offset: 0x1C ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_ECR_maskWrite,
            view32,
            &(bport1_ab_data.ECR.value),
            True
        );

        ppmCreateRegisterField(abECR_reg, "TXERRCNT", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abECR_reg, "RXERRCNT", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abESR1_reg = ppmCreateRegister(
            "ab_ESR1",
            "Error and Status 1 Register, offset: 0x20 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_ESR1_maskWrite,
            view32,
            &(bport1_ab_data.ESR1.value),
            True
        );

        ppmCreateRegisterField(abESR1_reg, "WAKINT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "ERRINT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "BOFFINT", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "RX", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "FLTCONF", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "TX", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "IDLE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "RXWRN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "TXWRN", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "STFERR", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "FRMERR", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "CRCERR", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "ACKERR", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "BIT0ERR", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "BIT1ERR", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "RWRNINT", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "TWRNINT", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abESR1_reg, "SYNCH", 0, 18, 1, 1, 1);
    }
    {
        registerHandle abIMASK2_reg = ppmCreateRegister(
            "ab_IMASK2",
            "Interrupt Masks 2 Register, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_IMASK2_maskWrite,
            view32,
            &(bport1_ab_data.IMASK2.value),
            True
        );

        ppmCreateRegisterField(abIMASK2_reg, "BUFHM", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abIMASK1_reg = ppmCreateRegister(
            "ab_IMASK1",
            "Interrupt Masks 1 Register, offset: 0x28 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_IMASK1_maskWrite,
            view32,
            &(bport1_ab_data.IMASK1.value),
            True
        );

        ppmCreateRegisterField(abIMASK1_reg, "BUFLM", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abIFLAG2_reg = ppmCreateRegister(
            "ab_IFLAG2",
            "Interrupt Flags 2 Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_IFLAG2_maskWrite,
            view32,
            &(bport1_ab_data.IFLAG2.value),
            True
        );

        ppmCreateRegisterField(abIFLAG2_reg, "BUFHI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abIFLAG1_reg = ppmCreateRegister(
            "ab_IFLAG1",
            "Interrupt Flags 1 Register, offset: 0x30 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_IFLAG1_maskWrite,
            view32,
            &(bport1_ab_data.IFLAG1.value),
            True
        );

        ppmCreateRegisterField(abIFLAG1_reg, "BUF4TO0I", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abIFLAG1_reg, "BUF5I", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIFLAG1_reg, "BUF6I", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIFLAG1_reg, "BUF7I", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIFLAG1_reg, "BUF31TO8I", 0, 8, 24, 1, 1);
    }
    {
        registerHandle abCTRL2_reg = ppmCreateRegister(
            "ab_CTRL2",
            "Control 2 Register, offset: 0x34 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_CTRL2_maskWrite,
            view32,
            &(bport1_ab_data.CTRL2.value),
            True
        );

        ppmCreateRegisterField(abCTRL2_reg, "EACEN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCTRL2_reg, "RRS", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abCTRL2_reg, "MRP", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abCTRL2_reg, "TASD", 0, 19, 5, 1, 1);
        ppmCreateRegisterField(abCTRL2_reg, "RFFN", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abCTRL2_reg, "WRMFRZ", 0, 28, 1, 1, 1);
    }
    {
        registerHandle abESR2_reg = ppmCreateRegister(
            "ab_ESR2",
            "Error and Status 2 Register, offset: 0x38 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ESR2.value),
            True
        );

        ppmCreateRegisterField(abESR2_reg, "IMB", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abESR2_reg, "VPS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abESR2_reg, "LPTM", 0, 16, 7, 1, 1);
    }
    {
        registerHandle abCRCR_reg = ppmCreateRegister(
            "ab_CRCR",
            "CRC Register, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CRCR.value),
            True
        );

        ppmCreateRegisterField(abCRCR_reg, "TXCRC", 0, 0, 15, 1, 0);
        ppmCreateRegisterField(abCRCR_reg, "MBCRC", 0, 16, 7, 1, 0);
    }
    {
        registerHandle abRXFGMASK_reg = ppmCreateRegister(
            "ab_RXFGMASK",
            "Rx FIFO Global Mask Register, offset: 0x48 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_RXFGMASK_maskWrite,
            view32,
            &(bport1_ab_data.RXFGMASK.value),
            True
        );

        ppmCreateRegisterField(abRXFGMASK_reg, "FGM", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXFIR_reg = ppmCreateRegister(
            "ab_RXFIR",
            "Rx FIFO Information Register, offset: 0x4C ",
            handles.bport1,
            0x4c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RXFIR.value),
            True
        );

        ppmCreateRegisterField(abRXFIR_reg, "IDHIT", 0, 0, 9, 1, 0);
    }
    {
        registerHandle abRXIMR0_reg = ppmCreateRegister(
            "ab_RXIMR0",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x880,
            4,
            read_32,
            bport1_ab_RXIMR0_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR0.value),
            True
        );

        ppmCreateRegisterField(abRXIMR0_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR1_reg = ppmCreateRegister(
            "ab_RXIMR1",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x884,
            4,
            read_32,
            bport1_ab_RXIMR1_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR1.value),
            True
        );

        ppmCreateRegisterField(abRXIMR1_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR2_reg = ppmCreateRegister(
            "ab_RXIMR2",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x888,
            4,
            read_32,
            bport1_ab_RXIMR2_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR2.value),
            True
        );

        ppmCreateRegisterField(abRXIMR2_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR3_reg = ppmCreateRegister(
            "ab_RXIMR3",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x88c,
            4,
            read_32,
            bport1_ab_RXIMR3_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR3.value),
            True
        );

        ppmCreateRegisterField(abRXIMR3_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR4_reg = ppmCreateRegister(
            "ab_RXIMR4",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x890,
            4,
            read_32,
            bport1_ab_RXIMR4_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR4.value),
            True
        );

        ppmCreateRegisterField(abRXIMR4_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR5_reg = ppmCreateRegister(
            "ab_RXIMR5",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x894,
            4,
            read_32,
            bport1_ab_RXIMR5_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR5.value),
            True
        );

        ppmCreateRegisterField(abRXIMR5_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR6_reg = ppmCreateRegister(
            "ab_RXIMR6",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x898,
            4,
            read_32,
            bport1_ab_RXIMR6_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR6.value),
            True
        );

        ppmCreateRegisterField(abRXIMR6_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR7_reg = ppmCreateRegister(
            "ab_RXIMR7",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x89c,
            4,
            read_32,
            bport1_ab_RXIMR7_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR7.value),
            True
        );

        ppmCreateRegisterField(abRXIMR7_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR8_reg = ppmCreateRegister(
            "ab_RXIMR8",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8a0,
            4,
            read_32,
            bport1_ab_RXIMR8_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR8.value),
            True
        );

        ppmCreateRegisterField(abRXIMR8_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR9_reg = ppmCreateRegister(
            "ab_RXIMR9",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8a4,
            4,
            read_32,
            bport1_ab_RXIMR9_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR9.value),
            True
        );

        ppmCreateRegisterField(abRXIMR9_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR10_reg = ppmCreateRegister(
            "ab_RXIMR10",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8a8,
            4,
            read_32,
            bport1_ab_RXIMR10_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR10.value),
            True
        );

        ppmCreateRegisterField(abRXIMR10_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR11_reg = ppmCreateRegister(
            "ab_RXIMR11",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8ac,
            4,
            read_32,
            bport1_ab_RXIMR11_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR11.value),
            True
        );

        ppmCreateRegisterField(abRXIMR11_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR12_reg = ppmCreateRegister(
            "ab_RXIMR12",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8b0,
            4,
            read_32,
            bport1_ab_RXIMR12_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR12.value),
            True
        );

        ppmCreateRegisterField(abRXIMR12_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR13_reg = ppmCreateRegister(
            "ab_RXIMR13",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8b4,
            4,
            read_32,
            bport1_ab_RXIMR13_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR13.value),
            True
        );

        ppmCreateRegisterField(abRXIMR13_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR14_reg = ppmCreateRegister(
            "ab_RXIMR14",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8b8,
            4,
            read_32,
            bport1_ab_RXIMR14_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR14.value),
            True
        );

        ppmCreateRegisterField(abRXIMR14_reg, "MI", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRXIMR15_reg = ppmCreateRegister(
            "ab_RXIMR15",
            "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 ",
            handles.bport1,
            0x8bc,
            4,
            read_32,
            bport1_ab_RXIMR15_maskWrite,
            view32,
            &(bport1_ab_data.RXIMR15.value),
            True
        );

        ppmCreateRegisterField(abRXIMR15_reg, "MI", 0, 0, 32, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.RXFGMASK.value = (Uns32)(bport1_ab_data.RXFGMASK.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.CRCR.value = (Uns32)(bport1_ab_data.CRCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ESR2.value = (Uns32)(bport1_ab_data.ESR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CTRL2.value = (Uns32)(bport1_ab_data.CTRL2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00b00000));
        bport1_ab_data.IFLAG1.value = (Uns32)(bport1_ab_data.IFLAG1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IFLAG2.value = (Uns32)(bport1_ab_data.IFLAG2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IMASK1.value = (Uns32)(bport1_ab_data.IMASK1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IMASK2.value = (Uns32)(bport1_ab_data.IMASK2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ESR1.value = (Uns32)(bport1_ab_data.ESR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ECR.value = (Uns32)(bport1_ab_data.ECR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RX15MASK.value = (Uns32)(bport1_ab_data.RX15MASK.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.RX14MASK.value = (Uns32)(bport1_ab_data.RX14MASK.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.RXMGMASK.value = (Uns32)(bport1_ab_data.RXMGMASK.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.TIMER.value = (Uns32)(bport1_ab_data.TIMER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CTRL1.value = (Uns32)(bport1_ab_data.CTRL1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0xd890000f));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the CAN peripheral used on the Freescale Kinetis platform");
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

