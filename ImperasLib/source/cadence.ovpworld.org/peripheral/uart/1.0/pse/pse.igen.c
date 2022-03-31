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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "uart", "Example");
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

static PPM_WRITE_CB(bport1_ab_Baud_rate_divider_maskWrite) {
    bport1_ab_data.Baud_rate_divider.value = (bport1_ab_data.Baud_rate_divider.value & BPORT1_AB_BAUD_RATE_DIVIDER_WRNMASK) | (data & BPORT1_AB_BAUD_RATE_DIVIDER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Baud_rate_gen_maskWrite) {
    bport1_ab_data.Baud_rate_gen.value = (bport1_ab_data.Baud_rate_gen.value & BPORT1_AB_BAUD_RATE_GEN_WRNMASK) | (data & BPORT1_AB_BAUD_RATE_GEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Flow_delay_maskWrite) {
    bport1_ab_data.Flow_delay.value = (bport1_ab_data.Flow_delay.value & BPORT1_AB_FLOW_DELAY_WRNMASK) | (data & BPORT1_AB_FLOW_DELAY_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Modem_ctrl_maskWrite) {
    bport1_ab_data.Modem_ctrl.value = (bport1_ab_data.Modem_ctrl.value & BPORT1_AB_MODEM_CTRL_WRNMASK) | (data & BPORT1_AB_MODEM_CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Modem_sts_maskWrite) {
    bport1_ab_data.Modem_sts.value = (bport1_ab_data.Modem_sts.value & BPORT1_AB_MODEM_STS_WRNMASK) | (data & BPORT1_AB_MODEM_STS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Rcvr_FIFO_trigger_level_maskWrite) {
    bport1_ab_data.Rcvr_FIFO_trigger_level.value = (bport1_ab_data.Rcvr_FIFO_trigger_level.value & BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_WRNMASK) | (data & BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Rcvr_timeout_maskWrite) {
    bport1_ab_data.Rcvr_timeout.value = (bport1_ab_data.Rcvr_timeout.value & BPORT1_AB_RCVR_TIMEOUT_WRNMASK) | (data & BPORT1_AB_RCVR_TIMEOUT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Tx_FIFO_trigger_level_maskWrite) {
    bport1_ab_data.Tx_FIFO_trigger_level.value = (bport1_ab_data.Tx_FIFO_trigger_level.value & BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_WRNMASK) | (data & BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_mode_maskWrite) {
    bport1_ab_data.mode.value = (bport1_ab_data.mode.value & BPORT1_AB_MODE_WRNMASK) | (data & BPORT1_AB_MODE_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abControl_reg = ppmCreateRegister(
            "ab_Control",
            "UART Control Register",
            handles.bport1,
            0x0,
            4,
            read_32,
            WriteControl,
            view32,
            &(bport1_ab_data.Control.value),
            True
        );

        ppmCreateRegisterField(abControl_reg, "STPBRK", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "STTBRK", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "RSTT0", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "TXDIS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "TXEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "RXDIS", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "RXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "TXRES", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "RXRES", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abmode_reg = ppmCreateRegister(
            "ab_mode",
            "UART Mode Register (no effect)",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_mode_maskWrite,
            view32,
            &(bport1_ab_data.mode.value),
            True
        );

        ppmCreateRegisterField(abmode_reg, "CHMODE", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abmode_reg, "NBSTOP", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abmode_reg, "PAR", 0, 3, 3, 1, 1);
        ppmCreateRegisterField(abmode_reg, "CHRL", 0, 1, 2, 1, 1);
        ppmCreateRegisterField(abmode_reg, "CLKS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntrpt_en_reg = ppmCreateRegister(
            "ab_Intrpt_en",
            "Interrupt Enable Register",
            handles.bport1,
            0x8,
            4,
            read_32,
            WriteIntrpt_en,
            view32,
            &(bport1_ab_data.Intrpt_en.value),
            True
        );

        ppmCreateRegisterField(abIntrpt_en_reg, "TOVR", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "TNFUL", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "TTRIG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "DMSI", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "TIMEOUT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "PARE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "FRAME", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "ROVR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "TFUL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "TEMPTY", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "RFUL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "REMPTY", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_reg, "RTRIG", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntrpt_dis_reg = ppmCreateRegister(
            "ab_Intrpt_dis",
            "Interrupt Disable Register",
            handles.bport1,
            0xc,
            4,
            read_32,
            WriteIntrpt_dis,
            view32,
            &(bport1_ab_data.Intrpt_dis.value),
            True
        );

        ppmCreateRegisterField(abIntrpt_dis_reg, "TOVR", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "TNFUL", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "TTRIG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "DMSI", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "TIMEOUT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "PARE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "FRAME", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "ROVR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "TFUL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "TEMPTY", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "RFUL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "REMPTY", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_reg, "RTRIG", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntrpt_mask_reg = ppmCreateRegister(
            "ab_Intrpt_mask",
            "Interrupt Mask Register",
            handles.bport1,
            0x10,
            4,
            ReadIntrpt_mask,
            0,
            view32,
            &(bport1_ab_data.Intrpt_mask.value),
            True
        );

        ppmCreateRegisterField(abIntrpt_mask_reg, "TOVR", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "TNFUL", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "TTRIG", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "DMSI", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "TIMEOUT", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "PARE", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "FRAME", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "ROVR", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "TFUL", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "TEMPTY", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "RFUL", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "REMPTY", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_reg, "RTRIG", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abChnl_int_sts_reg = ppmCreateRegister(
            "ab_Chnl_int_sts",
            "Channel Interrupt Status Register",
            handles.bport1,
            0x14,
            4,
            read_32,
            WriteChnl_int_sts,
            view32,
            &(bport1_ab_data.Chnl_int_sts.value),
            True
        );

        ppmCreateRegisterField(abChnl_int_sts_reg, "TOVR", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "TNFUL", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "TTRIG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "DMSI", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "TIMEOUT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "PARE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "FRAME", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "ROVR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "TFUL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "TEMPTY", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "RFUL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "REMPTY", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abChnl_int_sts_reg, "RTRIG", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abBaud_rate_gen_reg = ppmCreateRegister(
            "ab_Baud_rate_gen",
            "Baud Rate Generator Register (no effect)",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_Baud_rate_gen_maskWrite,
            view32,
            &(bport1_ab_data.Baud_rate_gen.value),
            True
        );

        ppmCreateRegisterField(abBaud_rate_gen_reg, "CD", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abRcvr_timeout_reg = ppmCreateRegister(
            "ab_Rcvr_timeout",
            "Receiver Timeout Register (no effect)",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_Rcvr_timeout_maskWrite,
            view32,
            &(bport1_ab_data.Rcvr_timeout.value),
            True
        );

        ppmCreateRegisterField(abRcvr_timeout_reg, "RTO", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRcvr_FIFO_trigger_level_reg = ppmCreateRegister(
            "ab_Rcvr_FIFO_trigger_level",
            "Receiver FIFO Trigger Level Register",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_Rcvr_FIFO_trigger_level_maskWrite,
            view32,
            &(bport1_ab_data.Rcvr_FIFO_trigger_level.value),
            True
        );

        ppmCreateRegisterField(abRcvr_FIFO_trigger_level_reg, "RTRIG", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abModem_ctrl_reg = ppmCreateRegister(
            "ab_Modem_ctrl",
            "Modem Control Register (no effect)",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_Modem_ctrl_maskWrite,
            view32,
            &(bport1_ab_data.Modem_ctrl.value),
            True
        );

        ppmCreateRegisterField(abModem_ctrl_reg, "FCM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abModem_ctrl_reg, "RTS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abModem_ctrl_reg, "DTR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abModem_sts_reg = ppmCreateRegister(
            "ab_Modem_sts",
            "Modem Status Register (no effect)",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_Modem_sts_maskWrite,
            view32,
            &(bport1_ab_data.Modem_sts.value),
            True
        );

        ppmCreateRegisterField(abModem_sts_reg, "FCMS", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "DCD", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "RI", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "DSR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "CTS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "DDCD", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "TERI", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "DDSR", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abModem_sts_reg, "DCTS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abChannel_sts_reg = ppmCreateRegister(
            "ab_Channel_sts",
            "Channel Status Register",
            handles.bport1,
            0x2c,
            4,
            ReadChannel_sts,
            0,
            view32,
            &(bport1_ab_data.Channel_sts.value),
            True
        );

        ppmCreateRegisterField(abChannel_sts_reg, "TNFUL", 0, 14, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "TTRIG", 0, 13, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "FDELT", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "TACTIVE", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "RACTIVE", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "TFUL", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "TEMPTY", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "RFUL", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "REMPTY", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abChannel_sts_reg, "RTRIG", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abTX_RX_FIFO_reg = ppmCreateRegister(
            "ab_TX_RX_FIFO",
            "Transmit and Receive FIFO",
            handles.bport1,
            0x30,
            4,
            ReadTX_RX_FIFO,
            WriteTX_RX_FIFO,
            view32,
            &(bport1_ab_data.TX_RX_FIFO.value),
            True
        );

        ppmCreateRegisterField(abTX_RX_FIFO_reg, "FIF0", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abBaud_rate_divider_reg = ppmCreateRegister(
            "ab_Baud_rate_divider",
            "Baud Rate Divider Register (no effect)",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_Baud_rate_divider_maskWrite,
            view32,
            &(bport1_ab_data.Baud_rate_divider.value),
            True
        );

        ppmCreateRegisterField(abBaud_rate_divider_reg, "BDIV", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFlow_delay_reg = ppmCreateRegister(
            "ab_Flow_delay",
            "Flow Control Delay Register (no effect)",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_Flow_delay_maskWrite,
            view32,
            &(bport1_ab_data.Flow_delay.value),
            True
        );

        ppmCreateRegisterField(abFlow_delay_reg, "FDEL", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abTx_FIFO_trigger_level_reg = ppmCreateRegister(
            "ab_Tx_FIFO_trigger_level",
            "Transmitter FIFO Trigger Level Register (no effect)",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_Tx_FIFO_trigger_level_maskWrite,
            view32,
            &(bport1_ab_data.Tx_FIFO_trigger_level.value),
            True
        );

        ppmCreateRegisterField(abTx_FIFO_trigger_level_reg, "TTRIG", 0, 0, 6, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.Tx_FIFO_trigger_level.value = (Uns32)(bport1_ab_data.Tx_FIFO_trigger_level.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000020));
        bport1_ab_data.Flow_delay.value = (Uns32)(bport1_ab_data.Flow_delay.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Baud_rate_divider.value = (Uns32)(bport1_ab_data.Baud_rate_divider.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000000F));
        bport1_ab_data.TX_RX_FIFO.value = (Uns32)(bport1_ab_data.TX_RX_FIFO.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Channel_sts.value = (Uns32)(bport1_ab_data.Channel_sts.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Modem_sts.value = (Uns32)(bport1_ab_data.Modem_sts.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Modem_ctrl.value = (Uns32)(bport1_ab_data.Modem_ctrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Rcvr_FIFO_trigger_level.value = (Uns32)(bport1_ab_data.Rcvr_FIFO_trigger_level.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000020));
        bport1_ab_data.Rcvr_timeout.value = (Uns32)(bport1_ab_data.Rcvr_timeout.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Baud_rate_gen.value = (Uns32)(bport1_ab_data.Baud_rate_gen.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000028B));
        bport1_ab_data.Chnl_int_sts.value = (Uns32)(bport1_ab_data.Chnl_int_sts.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intrpt_mask.value = (Uns32)(bport1_ab_data.Intrpt_mask.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intrpt_dis.value = (Uns32)(bport1_ab_data.Intrpt_dis.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intrpt_en.value = (Uns32)(bport1_ab_data.Intrpt_en.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.mode.value = (Uns32)(bport1_ab_data.mode.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Control.value = (Uns32)(bport1_ab_data.Control.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000128));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Cadence UART (Xilinx Zync Platform)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is an incomplete model of the Cadence UART (uartps) as used on the Xilinx Zync devices.");
        ppmDocAddText(doc_22_node, "It has basic functionality to support Linux boot on the Xilinx Zync platform.");
        ppmDocAddText(doc_22_node, "There is no modeling of physical aspects of the UART, such as baud rates etc.");
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

