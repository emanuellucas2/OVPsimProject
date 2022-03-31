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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisUART", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_B1T_maskWrite) {
    bport1_ab_data.B1T.value = (bport1_ab_data.B1T.value & BPORT1_AB_B1T_WRNMASK) | (data & BPORT1_AB_B1T_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & BPORT1_AB_C1_WRNMASK) | (data & BPORT1_AB_C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C3_maskWrite) {
    bport1_ab_data.C3.value = (bport1_ab_data.C3.value & BPORT1_AB_C3_WRNMASK) | (data & BPORT1_AB_C3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C5_maskWrite) {
    bport1_ab_data.C5.value = (bport1_ab_data.C5.value & BPORT1_AB_C5_WRNMASK) | (data & BPORT1_AB_C5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C6_maskWrite) {
    bport1_ab_data.C6.value = (bport1_ab_data.C6.value & BPORT1_AB_C6_WRNMASK) | (data & BPORT1_AB_C6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C7816_maskWrite) {
    bport1_ab_data.C7816.value = (bport1_ab_data.C7816.value & BPORT1_AB_C7816_WRNMASK) | (data & BPORT1_AB_C7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CPW_maskWrite) {
    bport1_ab_data.CPW.value = (bport1_ab_data.CPW.value & BPORT1_AB_CPW_WRNMASK) | (data & BPORT1_AB_CPW_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ET7816_maskWrite) {
    bport1_ab_data.ET7816.value = (bport1_ab_data.ET7816.value & BPORT1_AB_ET7816_WRNMASK) | (data & BPORT1_AB_ET7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IE7816_maskWrite) {
    bport1_ab_data.IE7816.value = (bport1_ab_data.IE7816.value & BPORT1_AB_IE7816_WRNMASK) | (data & BPORT1_AB_IE7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IE_maskWrite) {
    bport1_ab_data.IE.value = (bport1_ab_data.IE.value & BPORT1_AB_IE_WRNMASK) | (data & BPORT1_AB_IE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IR_maskWrite) {
    bport1_ab_data.IR.value = (bport1_ab_data.IR.value & BPORT1_AB_IR_WRNMASK) | (data & BPORT1_AB_IR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IS7816_maskWrite) {
    bport1_ab_data.IS7816.value = (bport1_ab_data.IS7816.value & BPORT1_AB_IS7816_WRNMASK) | (data & BPORT1_AB_IS7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MA1_maskWrite) {
    bport1_ab_data.MA1.value = (bport1_ab_data.MA1.value & BPORT1_AB_MA1_WRNMASK) | (data & BPORT1_AB_MA1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MA2_maskWrite) {
    bport1_ab_data.MA2.value = (bport1_ab_data.MA2.value & BPORT1_AB_MA2_WRNMASK) | (data & BPORT1_AB_MA2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MODEM_maskWrite) {
    bport1_ab_data.MODEM.value = (bport1_ab_data.MODEM.value & BPORT1_AB_MODEM_WRNMASK) | (data & BPORT1_AB_MODEM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCTH_maskWrite) {
    bport1_ab_data.PCTH.value = (bport1_ab_data.PCTH.value & BPORT1_AB_PCTH_WRNMASK) | (data & BPORT1_AB_PCTH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCTL_maskWrite) {
    bport1_ab_data.PCTL.value = (bport1_ab_data.PCTL.value & BPORT1_AB_PCTL_WRNMASK) | (data & BPORT1_AB_PCTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PFIFO_maskWrite) {
    bport1_ab_data.PFIFO.value = (bport1_ab_data.PFIFO.value & BPORT1_AB_PFIFO_WRNMASK) | (data & BPORT1_AB_PFIFO_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PRE_maskWrite) {
    bport1_ab_data.PRE.value = (bport1_ab_data.PRE.value & BPORT1_AB_PRE_WRNMASK) | (data & BPORT1_AB_PRE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RIDT_maskWrite) {
    bport1_ab_data.RIDT.value = (bport1_ab_data.RIDT.value & BPORT1_AB_RIDT_WRNMASK) | (data & BPORT1_AB_RIDT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_S2_maskWrite) {
    bport1_ab_data.S2.value = (bport1_ab_data.S2.value & BPORT1_AB_S2_WRNMASK) | (data & BPORT1_AB_S2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_S3_maskWrite) {
    bport1_ab_data.S3.value = (bport1_ab_data.S3.value & BPORT1_AB_S3_WRNMASK) | (data & BPORT1_AB_S3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_S4_maskWrite) {
    bport1_ab_data.S4.value = (bport1_ab_data.S4.value & BPORT1_AB_S4_WRNMASK) | (data & BPORT1_AB_S4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SDTH_maskWrite) {
    bport1_ab_data.SDTH.value = (bport1_ab_data.SDTH.value & BPORT1_AB_SDTH_WRNMASK) | (data & BPORT1_AB_SDTH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SDTL_maskWrite) {
    bport1_ab_data.SDTL.value = (bport1_ab_data.SDTL.value & BPORT1_AB_SDTL_WRNMASK) | (data & BPORT1_AB_SDTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SFIFO_maskWrite) {
    bport1_ab_data.SFIFO.value = (bport1_ab_data.SFIFO.value & BPORT1_AB_SFIFO_WRNMASK) | (data & BPORT1_AB_SFIFO_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIDT_maskWrite) {
    bport1_ab_data.TIDT.value = (bport1_ab_data.TIDT.value & BPORT1_AB_TIDT_WRNMASK) | (data & BPORT1_AB_TIDT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TL7816_maskWrite) {
    bport1_ab_data.TL7816.value = (bport1_ab_data.TL7816.value & BPORT1_AB_TL7816_WRNMASK) | (data & BPORT1_AB_TL7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TPL_maskWrite) {
    bport1_ab_data.TPL.value = (bport1_ab_data.TPL.value & BPORT1_AB_TPL_WRNMASK) | (data & BPORT1_AB_TPL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WB_maskWrite) {
    bport1_ab_data.WB.value = (bport1_ab_data.WB.value & BPORT1_AB_WB_WRNMASK) | (data & BPORT1_AB_WB_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WF7816_maskWrite) {
    bport1_ab_data.WF7816.value = (bport1_ab_data.WF7816.value & BPORT1_AB_WF7816_WRNMASK) | (data & BPORT1_AB_WF7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WN7816_maskWrite) {
    bport1_ab_data.WN7816.value = (bport1_ab_data.WN7816.value & BPORT1_AB_WN7816_WRNMASK) | (data & BPORT1_AB_WN7816_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WP7816T0_maskWrite) {
    bport1_ab_data.WP7816T0.value = (bport1_ab_data.WP7816T0.value & BPORT1_AB_WP7816T0_WRNMASK) | (data & BPORT1_AB_WP7816T0_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abBDH_reg = ppmCreateRegister(
            "ab_BDH",
            "UART Baud Rate Registers:High, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            writeBDH,
            view8,
            &(bport1_ab_data.BDH.value),
            True
        );

        ppmCreateRegisterField(abBDH_reg, "LBKDIE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abBDH_reg, "RXEDGIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abBDH_reg, "SBR", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abBDL_reg = ppmCreateRegister(
            "ab_BDL",
            "UART Baud Rate Registers: Low, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            writeBDL,
            view8,
            &(bport1_ab_data.BDL.value),
            True
        );

        ppmCreateRegisterField(abBDL_reg, "SBR", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abC1_reg = ppmCreateRegister(
            "ab_C1",
            "UART Control Register 1, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_C1_maskWrite,
            view8,
            &(bport1_ab_data.C1.value),
            True
        );

        ppmCreateRegisterField(abC1_reg, "ILT", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "LOOPS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "M", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "PT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "RSRC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "UARTSWAI", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "WAKE", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abC2_reg = ppmCreateRegister(
            "ab_C2",
            "UART Control Register 2, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            writeC2,
            view8,
            &(bport1_ab_data.C2.value),
            True
        );

        ppmCreateRegisterField(abC2_reg, "ILIE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "RE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "RIE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "RWU", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "SBK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "TCIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "TE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC2_reg, "TIE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abS1_reg = ppmCreateRegister(
            "ab_S1",
            "UART Status Register 1, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            readS1,
            0,
            viewS1,
            &(bport1_ab_data.S1.value),
            True
        );

        ppmCreateRegisterField(abS1_reg, "FE", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "IDLE", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "NF", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "OR", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "PF", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "RDRF", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "TC", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abS1_reg, "TDRE", 0, 7, 1, 1, 0);
    }
    {
        registerHandle abS2_reg = ppmCreateRegister(
            "ab_S2",
            "UART Status Register 2, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_S2_maskWrite,
            view8,
            &(bport1_ab_data.S2.value),
            True
        );

        ppmCreateRegisterField(abS2_reg, "BRK13", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "LBKDE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "LBKDIF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "MSBF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "RAF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "RWUID", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "RXEDGIF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abS2_reg, "RXINV", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abC3_reg = ppmCreateRegister(
            "ab_C3",
            "UART Control Register 3, offset: 0x6 ",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_C3_maskWrite,
            view8,
            &(bport1_ab_data.C3.value),
            True
        );

        ppmCreateRegisterField(abC3_reg, "FEIE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "NEIE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "ORIE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "PEIE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "R8", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "T8", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "TXDIR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC3_reg, "TXINV", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abD_reg = ppmCreateRegister(
            "ab_D",
            "UART Data Register, offset: 0x7 ",
            handles.bport1,
            0x7,
            1,
            readD,
            writeD,
            view8,
            &(bport1_ab_data.D.value),
            True
        );

        ppmCreateRegisterField(abD_reg, "RT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abMA1_reg = ppmCreateRegister(
            "ab_MA1",
            "UART Match Address Registers 1, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_MA1_maskWrite,
            view8,
            &(bport1_ab_data.MA1.value),
            True
        );

        ppmCreateRegisterField(abMA1_reg, "MA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abMA2_reg = ppmCreateRegister(
            "ab_MA2",
            "UART Match Address Registers 2, offset: 0x9 ",
            handles.bport1,
            0x9,
            1,
            read_8,
            bport1_ab_MA2_maskWrite,
            view8,
            &(bport1_ab_data.MA2.value),
            True
        );

        ppmCreateRegisterField(abMA2_reg, "MA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abC4_reg = ppmCreateRegister(
            "ab_C4",
            "UART Control Register 4, offset: 0xA ",
            handles.bport1,
            0xa,
            1,
            read_8,
            writeC4,
            view8,
            &(bport1_ab_data.C4.value),
            True
        );

        ppmCreateRegisterField(abC4_reg, "BRFA", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abC4_reg, "M10", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC4_reg, "MAEN1", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC4_reg, "MAEN2", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abC5_reg = ppmCreateRegister(
            "ab_C5",
            "UART Control Register 5, offset: 0xB ",
            handles.bport1,
            0xb,
            1,
            read_8,
            bport1_ab_C5_maskWrite,
            view8,
            &(bport1_ab_data.C5.value),
            True
        );

        ppmCreateRegisterField(abC5_reg, "RDMAS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC5_reg, "TDMAS", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abED_reg = ppmCreateRegister(
            "ab_ED",
            "UART Extended Data Register, offset: 0xC ",
            handles.bport1,
            0xc,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.ED.value),
            True
        );

        ppmCreateRegisterField(abED_reg, "NOISY", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abED_reg, "PARITYE", 0, 6, 1, 1, 0);
    }
    {
        registerHandle abMODEM_reg = ppmCreateRegister(
            "ab_MODEM",
            "UART Modem Register, offset: 0xD ",
            handles.bport1,
            0xd,
            1,
            read_8,
            bport1_ab_MODEM_maskWrite,
            view8,
            &(bport1_ab_data.MODEM.value),
            True
        );

        ppmCreateRegisterField(abMODEM_reg, "RXRTSE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abMODEM_reg, "TXCTSE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abMODEM_reg, "TXRTSE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abMODEM_reg, "TXRTSPOL", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abIR_reg = ppmCreateRegister(
            "ab_IR",
            "UART Infrared Register, offset: 0xE ",
            handles.bport1,
            0xe,
            1,
            read_8,
            bport1_ab_IR_maskWrite,
            view8,
            &(bport1_ab_data.IR.value),
            True
        );

        ppmCreateRegisterField(abIR_reg, "IREN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIR_reg, "TNP", 0, 0, 2, 1, 1);
    }
    {
        registerHandle abPFIFO_reg = ppmCreateRegister(
            "ab_PFIFO",
            "UART FIFO Parameters, offset: 0x10 ",
            handles.bport1,
            0x10,
            1,
            read_8,
            bport1_ab_PFIFO_maskWrite,
            view8,
            &(bport1_ab_data.PFIFO.value),
            True
        );

        ppmCreateRegisterField(abPFIFO_reg, "RXFE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPFIFO_reg, "RXFIFOSIZE", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPFIFO_reg, "TXFE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPFIFO_reg, "TXFIFOSIZE", 0, 4, 3, 1, 1);
    }
    {
        registerHandle abCFIFO_reg = ppmCreateRegister(
            "ab_CFIFO",
            "UART FIFO Control Register, offset: 0x11 ",
            handles.bport1,
            0x11,
            1,
            read_8,
            writeCFIFO,
            view8,
            &(bport1_ab_data.CFIFO.value),
            True
        );

        ppmCreateRegisterField(abCFIFO_reg, "RXFLUSH", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCFIFO_reg, "RXUFE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCFIFO_reg, "TXFLUSH", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCFIFO_reg, "TXOFE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abSFIFO_reg = ppmCreateRegister(
            "ab_SFIFO",
            "UART FIFO Status Register, offset: 0x12 ",
            handles.bport1,
            0x12,
            1,
            read_8,
            bport1_ab_SFIFO_maskWrite,
            view8,
            &(bport1_ab_data.SFIFO.value),
            True
        );

        ppmCreateRegisterField(abSFIFO_reg, "RXEMPT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSFIFO_reg, "RXUF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSFIFO_reg, "TXEMPT", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSFIFO_reg, "TXOF", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abTWFIFO_reg = ppmCreateRegister(
            "ab_TWFIFO",
            "UART FIFO Transmit Watermark, offset: 0x13 ",
            handles.bport1,
            0x13,
            1,
            read_8,
            writeTWFIFO,
            view8,
            &(bport1_ab_data.TWFIFO.value),
            True
        );

        ppmCreateRegisterField(abTWFIFO_reg, "TXWATER", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTCFIFO_reg = ppmCreateRegister(
            "ab_TCFIFO",
            "UART FIFO Transmit Count, offset: 0x14 ",
            handles.bport1,
            0x14,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.TCFIFO.value),
            True
        );

        ppmCreateRegisterField(abTCFIFO_reg, "TXCOUNT", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abRWFIFO_reg = ppmCreateRegister(
            "ab_RWFIFO",
            "UART FIFO Receive Watermark, offset: 0x15 ",
            handles.bport1,
            0x15,
            1,
            read_8,
            writeRWFIFO,
            view8,
            &(bport1_ab_data.RWFIFO.value),
            True
        );

        ppmCreateRegisterField(abRWFIFO_reg, "RXWATER", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRCFIFO_reg = ppmCreateRegister(
            "ab_RCFIFO",
            "UART FIFO Receive Count, offset: 0x16 ",
            handles.bport1,
            0x16,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.RCFIFO.value),
            True
        );

        ppmCreateRegisterField(abRCFIFO_reg, "RXCOUNT", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abC7816_reg = ppmCreateRegister(
            "ab_C7816",
            "UART 7816 Control Register, offset: 0x18 ",
            handles.bport1,
            0x18,
            1,
            read_8,
            bport1_ab_C7816_maskWrite,
            view8,
            &(bport1_ab_data.C7816.value),
            True
        );

        ppmCreateRegisterField(abC7816_reg, "ANACK", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC7816_reg, "INIT", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC7816_reg, "ISO_7816E", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC7816_reg, "ONACK", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC7816_reg, "TTYPE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abIE7816_reg = ppmCreateRegister(
            "ab_IE7816",
            "UART 7816 Interrupt Enable Register, offset: 0x19 ",
            handles.bport1,
            0x19,
            1,
            read_8,
            bport1_ab_IE7816_maskWrite,
            view8,
            &(bport1_ab_data.IE7816.value),
            True
        );

        ppmCreateRegisterField(abIE7816_reg, "BWTE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIE7816_reg, "CWTE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIE7816_reg, "GTVE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIE7816_reg, "INITDE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIE7816_reg, "RXTE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIE7816_reg, "TXTE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIE7816_reg, "WTE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abIS7816_reg = ppmCreateRegister(
            "ab_IS7816",
            "UART 7816 Interrupt Status Register, offset: 0x1A ",
            handles.bport1,
            0x1a,
            1,
            read_8,
            bport1_ab_IS7816_maskWrite,
            view8,
            &(bport1_ab_data.IS7816.value),
            True
        );

        ppmCreateRegisterField(abIS7816_reg, "BWT", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIS7816_reg, "CWT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIS7816_reg, "GTV", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIS7816_reg, "INITD", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIS7816_reg, "RXT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIS7816_reg, "TXT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIS7816_reg, "WT", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abWP7816T0_reg = ppmCreateRegister(
            "ab_WP7816T0",
            "UART 7816 Wait Parameter Register, offset: 0x1B ",
            handles.bport1,
            0x1b,
            1,
            read_8,
            bport1_ab_WP7816T0_maskWrite,
            view8,
            &(bport1_ab_data.WP7816T0.value),
            True
        );

        ppmCreateRegisterField(abWP7816T0_reg, "WI", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abWN7816_reg = ppmCreateRegister(
            "ab_WN7816",
            "UART 7816 Wait N Register, offset: 0x1C ",
            handles.bport1,
            0x1c,
            1,
            read_8,
            bport1_ab_WN7816_maskWrite,
            view8,
            &(bport1_ab_data.WN7816.value),
            True
        );

        ppmCreateRegisterField(abWN7816_reg, "GTN", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abWF7816_reg = ppmCreateRegister(
            "ab_WF7816",
            "UART 7816 Wait FD Register, offset: 0x1D ",
            handles.bport1,
            0x1d,
            1,
            read_8,
            bport1_ab_WF7816_maskWrite,
            view8,
            &(bport1_ab_data.WF7816.value),
            True
        );

        ppmCreateRegisterField(abWF7816_reg, "GTFD", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abET7816_reg = ppmCreateRegister(
            "ab_ET7816",
            "UART 7816 Error Threshold Register, offset: 0x1E ",
            handles.bport1,
            0x1e,
            1,
            read_8,
            bport1_ab_ET7816_maskWrite,
            view8,
            &(bport1_ab_data.ET7816.value),
            True
        );

        ppmCreateRegisterField(abET7816_reg, "RXTHRESHOLD", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abET7816_reg, "TXTHRESHOLD", 0, 4, 4, 1, 1);
    }
    {
        registerHandle abTL7816_reg = ppmCreateRegister(
            "ab_TL7816",
            "UART 7816 Transmit Length Register, offset: 0x1F ",
            handles.bport1,
            0x1f,
            1,
            read_8,
            bport1_ab_TL7816_maskWrite,
            view8,
            &(bport1_ab_data.TL7816.value),
            True
        );

        ppmCreateRegisterField(abTL7816_reg, "TLEN", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abC6_reg = ppmCreateRegister(
            "ab_C6",
            "UART CEA709.1-B Control Register 6, offset: 0x21 ",
            handles.bport1,
            0x21,
            1,
            read_8,
            bport1_ab_C6_maskWrite,
            view8,
            &(bport1_ab_data.C6.value),
            True
        );

        ppmCreateRegisterField(abC6_reg, "CE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC6_reg, "CP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC6_reg, "EN709", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC6_reg, "TX709", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abPCTH_reg = ppmCreateRegister(
            "ab_PCTH",
            "UART CEA709.1-B Packet Cycle Time Counter High, offset: 0x22 ",
            handles.bport1,
            0x22,
            1,
            read_8,
            bport1_ab_PCTH_maskWrite,
            view8,
            &(bport1_ab_data.PCTH.value),
            True
        );

        ppmCreateRegisterField(abPCTH_reg, "PCTH", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abPCTL_reg = ppmCreateRegister(
            "ab_PCTL",
            "UART CEA709.1-B Packet Cycle Time Counter Low, offset: 0x23 ",
            handles.bport1,
            0x23,
            1,
            read_8,
            bport1_ab_PCTL_maskWrite,
            view8,
            &(bport1_ab_data.PCTL.value),
            True
        );

        ppmCreateRegisterField(abPCTL_reg, "PCTL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abB1T_reg = ppmCreateRegister(
            "ab_B1T",
            "UART CEA709.1-B Beta1 Timer, offset: 0x24 ",
            handles.bport1,
            0x24,
            1,
            read_8,
            bport1_ab_B1T_maskWrite,
            view8,
            &(bport1_ab_data.B1T.value),
            True
        );

        ppmCreateRegisterField(abB1T_reg, "B1T", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abSDTH_reg = ppmCreateRegister(
            "ab_SDTH",
            "UART CEA709.1-B Secondary Delay Timer High, offset: 0x25 ",
            handles.bport1,
            0x25,
            1,
            read_8,
            bport1_ab_SDTH_maskWrite,
            view8,
            &(bport1_ab_data.SDTH.value),
            True
        );

        ppmCreateRegisterField(abSDTH_reg, "SDTH", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abSDTL_reg = ppmCreateRegister(
            "ab_SDTL",
            "UART CEA709.1-B Secondary Delay Timer Low, offset: 0x26 ",
            handles.bport1,
            0x26,
            1,
            read_8,
            bport1_ab_SDTL_maskWrite,
            view8,
            &(bport1_ab_data.SDTL.value),
            True
        );

        ppmCreateRegisterField(abSDTL_reg, "SDTL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abPRE_reg = ppmCreateRegister(
            "ab_PRE",
            "UART CEA709.1-B Preamble, offset: 0x27 ",
            handles.bport1,
            0x27,
            1,
            read_8,
            bport1_ab_PRE_maskWrite,
            view8,
            &(bport1_ab_data.PRE.value),
            True
        );

        ppmCreateRegisterField(abPRE_reg, "PREAMBLE", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTPL_reg = ppmCreateRegister(
            "ab_TPL",
            "UART CEA709.1-B Transmit Packet Length, offset: 0x28 ",
            handles.bport1,
            0x28,
            1,
            read_8,
            bport1_ab_TPL_maskWrite,
            view8,
            &(bport1_ab_data.TPL.value),
            True
        );

        ppmCreateRegisterField(abTPL_reg, "TPL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abIE_reg = ppmCreateRegister(
            "ab_IE",
            "UART CEA709.1-B Interrupt Enable Register, offset: 0x29 ",
            handles.bport1,
            0x29,
            1,
            read_8,
            bport1_ab_IE_maskWrite,
            view8,
            &(bport1_ab_data.IE.value),
            True
        );

        ppmCreateRegisterField(abIE_reg, "ISDIE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIE_reg, "PCTEIE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIE_reg, "PRXIE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIE_reg, "PSIE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIE_reg, "PTXIE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIE_reg, "TXFIE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIE_reg, "WBEIE", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abWB_reg = ppmCreateRegister(
            "ab_WB",
            "UART CEA709.1-B WBASE, offset: 0x2A ",
            handles.bport1,
            0x2a,
            1,
            read_8,
            bport1_ab_WB_maskWrite,
            view8,
            &(bport1_ab_data.WB.value),
            True
        );

        ppmCreateRegisterField(abWB_reg, "WBASE", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abS3_reg = ppmCreateRegister(
            "ab_S3",
            "UART CEA709.1-B Status Register, offset: 0x2B ",
            handles.bport1,
            0x2b,
            1,
            read_8,
            bport1_ab_S3_maskWrite,
            view8,
            &(bport1_ab_data.S3.value),
            True
        );

        ppmCreateRegisterField(abS3_reg, "ISD", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "PCTEF", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "PEF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "PRXF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "PSF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "PTXF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "TXFF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abS3_reg, "WBEF", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abS4_reg = ppmCreateRegister(
            "ab_S4",
            "UART CEA709.1-B Status Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            1,
            read_8,
            bport1_ab_S4_maskWrite,
            view8,
            &(bport1_ab_data.S4.value),
            True
        );

        ppmCreateRegisterField(abS4_reg, "CDET", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abS4_reg, "FE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abS4_reg, "ILCV", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abS4_reg, "INITF", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abRPL_reg = ppmCreateRegister(
            "ab_RPL",
            "UART CEA709.1-B Received Packet Length, offset: 0x2D ",
            handles.bport1,
            0x2d,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.RPL.value),
            True
        );

        ppmCreateRegisterField(abRPL_reg, "RPL", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abRPREL_reg = ppmCreateRegister(
            "ab_RPREL",
            "UART CEA709.1-B Received Preamble Length, offset: 0x2E ",
            handles.bport1,
            0x2e,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.RPREL.value),
            True
        );

        ppmCreateRegisterField(abRPREL_reg, "RPREL", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abCPW_reg = ppmCreateRegister(
            "ab_CPW",
            "UART CEA709.1-B Collision Pulse Width, offset: 0x2F ",
            handles.bport1,
            0x2f,
            1,
            read_8,
            bport1_ab_CPW_maskWrite,
            view8,
            &(bport1_ab_data.CPW.value),
            True
        );

        ppmCreateRegisterField(abCPW_reg, "CPW", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRIDT_reg = ppmCreateRegister(
            "ab_RIDT",
            "UART CEA709.1-B Receive Indeterminate Time, offset: 0x30 ",
            handles.bport1,
            0x30,
            1,
            read_8,
            bport1_ab_RIDT_maskWrite,
            view8,
            &(bport1_ab_data.RIDT.value),
            True
        );

        ppmCreateRegisterField(abRIDT_reg, "RIDT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTIDT_reg = ppmCreateRegister(
            "ab_TIDT",
            "UART CEA709.1-B Transmit Indeterminate Time, offset: 0x31 ",
            handles.bport1,
            0x31,
            1,
            read_8,
            bport1_ab_TIDT_maskWrite,
            view8,
            &(bport1_ab_data.TIDT.value),
            True
        );

        ppmCreateRegisterField(abTIDT_reg, "TIDT", 0, 0, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.TIDT.value = (Uns8)(bport1_ab_data.TIDT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RIDT.value = (Uns8)(bport1_ab_data.RIDT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.CPW.value = (Uns8)(bport1_ab_data.CPW.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RPREL.value = (Uns8)(bport1_ab_data.RPREL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RPL.value = (Uns8)(bport1_ab_data.RPL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.S4.value = (Uns8)(bport1_ab_data.S4.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.S3.value = (Uns8)(bport1_ab_data.S3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.WB.value = (Uns8)(bport1_ab_data.WB.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IE.value = (Uns8)(bport1_ab_data.IE.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.TPL.value = (Uns8)(bport1_ab_data.TPL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PRE.value = (Uns8)(bport1_ab_data.PRE.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SDTL.value = (Uns8)(bport1_ab_data.SDTL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SDTH.value = (Uns8)(bport1_ab_data.SDTH.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.B1T.value = (Uns8)(bport1_ab_data.B1T.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PCTL.value = (Uns8)(bport1_ab_data.PCTL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PCTH.value = (Uns8)(bport1_ab_data.PCTH.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C6.value = (Uns8)(bport1_ab_data.C6.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.TL7816.value = (Uns8)(bport1_ab_data.TL7816.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ET7816.value = (Uns8)(bport1_ab_data.ET7816.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.WF7816.value = (Uns8)(bport1_ab_data.WF7816.value & ~(0xff)) | ((0xff) & (0x01));
        bport1_ab_data.WN7816.value = (Uns8)(bport1_ab_data.WN7816.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.WP7816T0.value = (Uns8)(bport1_ab_data.WP7816T0.value & ~(0xff)) | ((0xff) & (0x0a));
        bport1_ab_data.IS7816.value = (Uns8)(bport1_ab_data.IS7816.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IE7816.value = (Uns8)(bport1_ab_data.IE7816.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C7816.value = (Uns8)(bport1_ab_data.C7816.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RCFIFO.value = (Uns8)(bport1_ab_data.RCFIFO.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.RWFIFO.value = (Uns8)(bport1_ab_data.RWFIFO.value & ~(0xff)) | ((0xff) & (0x01));
        bport1_ab_data.TCFIFO.value = (Uns8)(bport1_ab_data.TCFIFO.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.TWFIFO.value = (Uns8)(bport1_ab_data.TWFIFO.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SFIFO.value = (Uns8)(bport1_ab_data.SFIFO.value & ~(0xff)) | ((0xff) & (0xc0));
        bport1_ab_data.CFIFO.value = (Uns8)(bport1_ab_data.CFIFO.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.PFIFO.value = (Uns8)(bport1_ab_data.PFIFO.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IR.value = (Uns8)(bport1_ab_data.IR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.MODEM.value = (Uns8)(bport1_ab_data.MODEM.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ED.value = (Uns8)(bport1_ab_data.ED.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C5.value = (Uns8)(bport1_ab_data.C5.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C4.value = (Uns8)(bport1_ab_data.C4.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.MA2.value = (Uns8)(bport1_ab_data.MA2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.MA1.value = (Uns8)(bport1_ab_data.MA1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.D.value = (Uns8)(bport1_ab_data.D.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C3.value = (Uns8)(bport1_ab_data.C3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.S2.value = (Uns8)(bport1_ab_data.S2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.S1.value = (Uns8)(bport1_ab_data.S1.value & ~(0xff)) | ((0xff) & (0xc0));
        bport1_ab_data.C2.value = (Uns8)(bport1_ab_data.C2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C1.value = (Uns8)(bport1_ab_data.C1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.BDL.value = (Uns8)(bport1_ab_data.BDL.value & ~(0xff)) | ((0xff) & (0x04));
        bport1_ab_data.BDH.value = (Uns8)(bport1_ab_data.BDH.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the UART peripheral used on the Freescale Kinetis platform");
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

