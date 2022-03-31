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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_UART", "Example");
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

static PPM_WRITE_CB(bport1_ab_UART_ONEMS_maskWrite) {
    bport1_ab_data.UART_ONEMS.value = (bport1_ab_data.UART_ONEMS.value & BPORT1_AB_UART_ONEMS_WRNMASK) | (data & BPORT1_AB_UART_ONEMS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_UART_UBIR_maskWrite) {
    bport1_ab_data.UART_UBIR.value = (bport1_ab_data.UART_UBIR.value & BPORT1_AB_UART_UBIR_WRNMASK) | (data & BPORT1_AB_UART_UBIR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_UART_UBMR_maskWrite) {
    bport1_ab_data.UART_UBMR.value = (bport1_ab_data.UART_UBMR.value & BPORT1_AB_UART_UBMR_WRNMASK) | (data & BPORT1_AB_UART_UBMR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_UART_UESC_maskWrite) {
    bport1_ab_data.UART_UESC.value = (bport1_ab_data.UART_UESC.value & BPORT1_AB_UART_UESC_WRNMASK) | (data & BPORT1_AB_UART_UESC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_UART_UTIM_maskWrite) {
    bport1_ab_data.UART_UTIM.value = (bport1_ab_data.UART_UTIM.value & BPORT1_AB_UART_UTIM_WRNMASK) | (data & BPORT1_AB_UART_UTIM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_UART_UTS_maskWrite) {
    bport1_ab_data.UART_UTS.value = (bport1_ab_data.UART_UTS.value & BPORT1_AB_UART_UTS_WRNMASK) | (data & BPORT1_AB_UART_UTS_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x4000);
    ppmInstallWriteCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x4000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abUART_URXD_reg = ppmCreateRegister(
            "ab_UART_URXD",
            "UART Receiver Register (UART_URXD)",
            handles.bport1,
            0x0,
            4,
            ReadUART_URXD,
            0,
            view32,
            &(bport1_ab_data.UART_URXD.value),
            True
        );

        ppmCreateRegisterField(abUART_URXD_reg, "CHARRDY", 0, 15, 1, 1, 0);
        ppmCreateRegisterField(abUART_URXD_reg, "ERR", 0, 14, 1, 1, 0);
        ppmCreateRegisterField(abUART_URXD_reg, "OVRRUN", 0, 13, 1, 1, 0);
        ppmCreateRegisterField(abUART_URXD_reg, "FRMERR", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(abUART_URXD_reg, "BRK", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abUART_URXD_reg, "PRERR", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abUART_URXD_reg, "DATA", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abUART_UTXD_reg = ppmCreateRegister(
            "ab_UART_UTXD",
            "Description\nUART Transmitter Register (UART_UTXD)\n\n",
            handles.bport1,
            0x40,
            4,
            0,
            WriteUART_UTXD,
            view32,
            &(bport1_ab_data.UART_UTXD.value),
            True
        );

        ppmCreateRegisterField(abUART_UTXD_reg, "DATA", 0, 0, 8, 0, 1);
    }
    {
        registerHandle abUART_UCR1_reg = ppmCreateRegister(
            "ab_UART_UCR1",
            "UART Control Register 1 (UART_UCR1)",
            handles.bport1,
            0x80,
            4,
            read_32,
            WriteUART_UCR1,
            view32,
            &(bport1_ab_data.UART_UCR1.value),
            True
        );

        ppmCreateRegisterField(abUART_UCR1_reg, "ADEN", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "ADBR", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "TRDYEN", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "IDEN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "ICD", 0, 10, 2, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "RRDYEN", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "RXDMAEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "IREN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "TXMPTYEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "RTSDEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "SNDBRK", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "TXDMAEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "ATDMAEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "DOZE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR1_reg, "UARTEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUART_UCR2_reg = ppmCreateRegister(
            "ab_UART_UCR2",
            "UART Control Register 2 (UART_UCR2)",
            handles.bport1,
            0x84,
            4,
            read_32,
            WriteUART_UCR2,
            view32,
            &(bport1_ab_data.UART_UCR2.value),
            True
        );

        ppmCreateRegisterField(abUART_UCR2_reg, "ESCI", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "IRTS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "CTSC", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "CTS", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "ESCEN", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "RTEC", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "PREN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "PROE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "STPB", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "WS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "RTSEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "ATEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "TXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "RXEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR2_reg, "SRST", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUART_UCR3_reg = ppmCreateRegister(
            "ab_UART_UCR3",
            "UART Control Register 3 (UART_UCR3)",
            handles.bport1,
            0x88,
            4,
            read_32,
            WriteUART_UCR3,
            view32,
            &(bport1_ab_data.UART_UCR3.value),
            True
        );

        ppmCreateRegisterField(abUART_UCR3_reg, "DPEC", 0, 14, 2, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "DTREN", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "PARERREN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "FRAERREN", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "DSR", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "DCD", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "RI", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "ADNIMP", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "RXDSEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "AIRINTEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "AWAKEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "DTRDEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "RXDMUXSEL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "INVT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR3_reg, "ACIEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUART_UCR4_reg = ppmCreateRegister(
            "ab_UART_UCR4",
            "UART Control Register 4 (UART_UCR4)",
            handles.bport1,
            0x8c,
            4,
            read_32,
            WriteUART_UCR4,
            view32,
            &(bport1_ab_data.UART_UCR4.value),
            True
        );

        ppmCreateRegisterField(abUART_UCR4_reg, "CTSTL", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "INVR", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "ENIRI", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "WKEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "IDDMAEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "IRSC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "LPBYP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "TCEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "BKEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "OREN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUART_UCR4_reg, "DREN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUART_UFCR_reg = ppmCreateRegister(
            "ab_UART_UFCR",
            "UART FIFO Control Register (UART_UFCR)",
            handles.bport1,
            0x90,
            4,
            read_32,
            WriteUART_UFCR,
            view32,
            &(bport1_ab_data.UART_UFCR.value),
            True
        );

        ppmCreateRegisterField(abUART_UFCR_reg, "TXTL", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abUART_UFCR_reg, "RFDIV", 0, 7, 3, 1, 1);
        ppmCreateRegisterField(abUART_UFCR_reg, "DCEDTE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_UFCR_reg, "RXTL", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abUART_USR1_reg = ppmCreateRegister(
            "ab_UART_USR1",
            "Description\nUART Status Register 1 (UART_USR1)\nTransmitter Ready Interrupt\nReceiver Ready Interrupt\nReceiver Idle\n",
            handles.bport1,
            0x94,
            4,
            read_32,
            WriteUART_USR1,
            view32,
            &(bport1_ab_data.UART_USR1.value),
            True
        );

        ppmCreateRegisterField(abUART_USR1_reg, "PARITYERR", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "RTSS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "TRDY", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "RTSD", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "ESCF", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "FRAMERR", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "RRDY", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "AGTIM", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "DTRD", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "RXDS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "AIRINT", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "AWAKE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR1_reg, "SAD", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abUART_USR2_reg = ppmCreateRegister(
            "ab_UART_USR2",
            "UART Status Register 2 (UART_USR2)",
            handles.bport1,
            0x98,
            4,
            read_32,
            WriteUART_USR2,
            view32,
            &(bport1_ab_data.UART_USR2.value),
            True
        );

        ppmCreateRegisterField(abUART_USR2_reg, "ADET", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "TXFE", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "DTRF", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "IDLE", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "ACST", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "RIDELT", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "RIIN", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "IRINT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "WAKE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "DCDDELT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "DCDIN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "RTSF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "TXDC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "BRCD", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "ORE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUART_USR2_reg, "RDR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUART_UESC_reg = ppmCreateRegister(
            "ab_UART_UESC",
            "UART Escape Character Register (UART_UESC)",
            handles.bport1,
            0x9c,
            4,
            read_32,
            bport1_ab_UART_UESC_maskWrite,
            view32,
            &(bport1_ab_data.UART_UESC.value),
            True
        );

        ppmCreateRegisterField(abUART_UESC_reg, "ESC_CHAR", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abUART_UTIM_reg = ppmCreateRegister(
            "ab_UART_UTIM",
            "UART Escape Timer Register (UART_UTIM)",
            handles.bport1,
            0xa0,
            4,
            read_32,
            bport1_ab_UART_UTIM_maskWrite,
            view32,
            &(bport1_ab_data.UART_UTIM.value),
            True
        );

        ppmCreateRegisterField(abUART_UTIM_reg, "TIM", 0, 0, 12, 1, 1);
    }
    {
        registerHandle abUART_UBIR_reg = ppmCreateRegister(
            "ab_UART_UBIR",
            "UART BRM Incremental Register (UART_UBIR)",
            handles.bport1,
            0xa4,
            4,
            read_32,
            bport1_ab_UART_UBIR_maskWrite,
            view32,
            &(bport1_ab_data.UART_UBIR.value),
            True
        );

        ppmCreateRegisterField(abUART_UBIR_reg, "INC", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abUART_UBMR_reg = ppmCreateRegister(
            "ab_UART_UBMR",
            "UART BRM Modulator Register (UART_UBMR)",
            handles.bport1,
            0xa8,
            4,
            read_32,
            bport1_ab_UART_UBMR_maskWrite,
            view32,
            &(bport1_ab_data.UART_UBMR.value),
            True
        );

        ppmCreateRegisterField(abUART_UBMR_reg, "MOD", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abUART_UBRC_reg = ppmCreateRegister(
            "ab_UART_UBRC",
            "UART Baud Rate Count Register (UART_UBRC)",
            handles.bport1,
            0xac,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.UART_UBRC.value),
            True
        );

        ppmCreateRegisterField(abUART_UBRC_reg, "BCNT", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abUART_ONEMS_reg = ppmCreateRegister(
            "ab_UART_ONEMS",
            "UART One Millisecond Register (UART_ONEMS",
            handles.bport1,
            0xb0,
            4,
            read_32,
            bport1_ab_UART_ONEMS_maskWrite,
            view32,
            &(bport1_ab_data.UART_ONEMS.value),
            True
        );

        ppmCreateRegisterField(abUART_ONEMS_reg, "ONEMS", 0, 0, 24, 1, 1);
    }
    {
        registerHandle abUART_UTS_reg = ppmCreateRegister(
            "ab_UART_UTS",
            "UART Test Register (UART_UTS)",
            handles.bport1,
            0xb4,
            4,
            read_32,
            bport1_ab_UART_UTS_maskWrite,
            view32,
            &(bport1_ab_data.UART_UTS.value),
            True
        );

        ppmCreateRegisterField(abUART_UTS_reg, "FRCPERR", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "LOOP", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "DBGEN", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "LOOPIR", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "RXDBG", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "TXEMPTY", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "RXEMPTY", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "TXFULL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "RXFULL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_UTS_reg, "SOFTRST", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUART_UMCR_reg = ppmCreateRegister(
            "ab_UART_UMCR",
            "UART RS-485 Mode Control Register (UART_UMCR)",
            handles.bport1,
            0xb8,
            4,
            read_32,
            WriteUART_UMCR,
            view32,
            &(bport1_ab_data.UART_UMCR.value),
            True
        );

        ppmCreateRegisterField(abUART_UMCR_reg, "SLADDR", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abUART_UMCR_reg, "SADEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUART_UMCR_reg, "TXB8", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUART_UMCR_reg, "SLAM", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUART_UMCR_reg, "MDEN", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.UART_UMCR.value = (Uns32)(bport1_ab_data.UART_UMCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_UTS.value = (Uns32)(bport1_ab_data.UART_UTS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000060));
        bport1_ab_data.UART_ONEMS.value = (Uns32)(bport1_ab_data.UART_ONEMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_UBRC.value = (Uns32)(bport1_ab_data.UART_UBRC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.UART_UBMR.value = (Uns32)(bport1_ab_data.UART_UBMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_UBIR.value = (Uns32)(bport1_ab_data.UART_UBIR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_UTIM.value = (Uns32)(bport1_ab_data.UART_UTIM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_UESC.value = (Uns32)(bport1_ab_data.UART_UESC.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000002B));
        bport1_ab_data.UART_USR2.value = (Uns32)(bport1_ab_data.UART_USR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00004028));
        bport1_ab_data.UART_USR1.value = (Uns32)(bport1_ab_data.UART_USR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00002040));
        bport1_ab_data.UART_UFCR.value = (Uns32)(bport1_ab_data.UART_UFCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000801));
        bport1_ab_data.UART_UCR4.value = (Uns32)(bport1_ab_data.UART_UCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00008000));
        bport1_ab_data.UART_UCR3.value = (Uns32)(bport1_ab_data.UART_UCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000700));
        bport1_ab_data.UART_UCR2.value = (Uns32)(bport1_ab_data.UART_UCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.UART_UCR1.value = (Uns32)(bport1_ab_data.UART_UCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_UTXD.value = (Uns32)(bport1_ab_data.UART_UTXD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_URXD.value = (Uns32)(bport1_ab_data.UART_URXD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "iMX6 UART");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is an incomplete model of the UART.");
        ppmDocAddText(doc_22_node, "It has basic functionality to support the iMX6 platform, Rx and Tx of data only.");
        ppmDocAddText(doc_22_node, "There is no modeling of physical aspects of the UART, such as baud rates etc.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf");
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

