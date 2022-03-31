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

bpAXI_abm_dataT bpAXI_abm_data;

bpAPB_ab_dataT bpAPB_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-qspi", "Example");
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

static PPM_WRITE_CB(bpAPB_ab_LQSPI_STS_maskWrite) {
    bpAPB_ab_data.LQSPI_STS.value = (bpAPB_ab_data.LQSPI_STS.value & BPAPB_AB_LQSPI_STS_WRNMASK) | (data & BPAPB_AB_LQSPI_STS_WRMASK);
}

static PPM_WRITE_CB(bpAPB_ab_Slave_Idle_count_REG_maskWrite) {
    bpAPB_ab_data.Slave_Idle_count_REG.value = (bpAPB_ab_data.Slave_Idle_count_REG.value & BPAPB_AB_SLAVE_IDLE_COUNT_REG_WRNMASK) | (data & BPAPB_AB_SLAVE_IDLE_COUNT_REG_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bpAXI = ppmCreateSlaveBusPort("bpAXI", 33554432);
    if (!handles.bpAXI) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bpAXI'");
    }

    handles.bpAPB = ppmCreateSlaveBusPort("bpAPB", 4096);
    if (!handles.bpAPB) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bpAPB'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bpAPB + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bpAPB + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {


    {
        registerHandle abConfig_reg_reg = ppmCreateRegister(
            "ab_Config_reg",
            "QSPI configuration register",
            handles.bpAPB,
            0x0,
            4,
            read_32,
            wrConfig,
            view32,
            &(bpAPB_ab_data.Config_reg.value),
            True
        );

        ppmCreateRegisterField(abConfig_reg_reg, "leg_flsh", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "endian", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "holdb_dr", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "man_start_com", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "manual_cs", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "pcs", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "ref_clk", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "fifo_width", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "baud_rate_dic", 0, 3, 3, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "clk_ph", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "clk_pol", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abConfig_reg_reg, "mode_sel", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntr_status_REG_reg = ppmCreateRegister(
            "ab_Intr_status_REG",
            "QSPI interrupt status register",
            handles.bpAPB,
            0x4,
            4,
            read_32,
            wrIntStat,
            view32,
            &(bpAPB_ab_data.Intr_status_REG.value),
            True
        );

        ppmCreateRegisterField(abIntr_status_REG_reg, "TXUF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIntr_status_REG_reg, "RXFULL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIntr_status_REG_reg, "RXNEMPTY", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIntr_status_REG_reg, "TXFULL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIntr_status_REG_reg, "TXOW", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIntr_status_REG_reg, "RXOVR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntrpt_en_REG_reg = ppmCreateRegister(
            "ab_Intrpt_en_REG",
            "Interrupt Enable register.",
            handles.bpAPB,
            0x8,
            4,
            rtnZero,
            wrIntEn,
            view32,
            &(bpAPB_ab_data.Intrpt_en_REG.value),
            True
        );

        ppmCreateRegisterField(abIntrpt_en_REG_reg, "TXUF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_REG_reg, "RXFULL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_REG_reg, "RXNEMPTY", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_REG_reg, "TXFULL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_REG_reg, "TXOW", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_en_REG_reg, "RXOVR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntrpt_dis_REG_reg = ppmCreateRegister(
            "ab_Intrpt_dis_REG",
            "Interrupt disable register.",
            handles.bpAPB,
            0xc,
            4,
            rtnZero,
            wrIntDis,
            view32,
            &(bpAPB_ab_data.Intrpt_dis_REG.value),
            True
        );

        ppmCreateRegisterField(abIntrpt_dis_REG_reg, "TXUF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_REG_reg, "RXFULL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_REG_reg, "RXNEMPTY", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_REG_reg, "TXFULL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_REG_reg, "TXOW", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIntrpt_dis_REG_reg, "RXOVR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIntrpt_mask_REG_reg = ppmCreateRegister(
            "ab_Intrpt_mask_REG",
            "Interrupt mask register",
            handles.bpAPB,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bpAPB_ab_data.Intrpt_mask_REG.value),
            True
        );

        ppmCreateRegisterField(abIntrpt_mask_REG_reg, "TXUF", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_REG_reg, "RXFULL", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_REG_reg, "RXNEMPTY", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_REG_reg, "TXFULL", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_REG_reg, "TXOW", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abIntrpt_mask_REG_reg, "RXOVR", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abEn_REG_reg = ppmCreateRegister(
            "ab_En_REG",
            "SPI_Enable Register",
            handles.bpAPB,
            0x14,
            4,
            read_32,
            wrEn,
            view32,
            &(bpAPB_ab_data.En_REG.value),
            True
        );

        ppmCreateRegisterField(abEn_REG_reg, "ENABLE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abDelay_REG_reg = ppmCreateRegister(
            "ab_Delay_REG",
            "Delay Register",
            handles.bpAPB,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.Delay_REG.value),
            True
        );

        ppmCreateRegisterField(abDelay_REG_reg, "NSS", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abDelay_REG_reg, "BTWN", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abDelay_REG_reg, "AFTER", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abDelay_REG_reg, "INIT", 0, 0, 8, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_TXD0",
            "Transmit Data Register. Keyhole addresses for the Transmit data FIFO. See also TXD1-3.",
            handles.bpAPB,
            0x1c,
            4,
            read_32,
            txData0,
            view32,
            &(bpAPB_ab_data.TXD0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Rx_data_REG",
            "Receive Data Register",
            handles.bpAPB,
            0x20,
            4,
            rxData,
            0,
            view32,
            &(bpAPB_ab_data.Rx_data_REG.value),
            True
        );
    }
    {
        registerHandle abSlave_Idle_count_REG_reg = ppmCreateRegister(
            "ab_Slave_Idle_count_REG",
            "Slave Idle Count Register",
            handles.bpAPB,
            0x24,
            4,
            read_32,
            bpAPB_ab_Slave_Idle_count_REG_maskWrite,
            view32,
            &(bpAPB_ab_data.Slave_Idle_count_REG.value),
            True
        );

        ppmCreateRegisterField(abSlave_Idle_count_REG_reg, "MASK", 0, 0, 8, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_TX_thres_REG",
            "TX_FIFO Threshold Register",
            handles.bpAPB,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.TX_thres_REG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_thres_REG",
            "RX FIFO Threshold Register",
            handles.bpAPB,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.RX_thres_REG.value),
            True
        );
    }
    {
        registerHandle abGPIO_reg = ppmCreateRegister(
            "ab_GPIO",
            "General Purpose Inputs and Outputs Register for the Quad-SPI Controller core",
            handles.bpAPB,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.GPIO.value),
            True
        );

        ppmCreateRegisterField(abGPIO_reg, "WP", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_LPBK_DLY_ADJ",
            "Loopback Master Clock Delay Adjustment Register",
            handles.bpAPB,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.LPBK_DLY_ADJ.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXD1",
            "Transmit Data Register. Keyhole addresses for the Transmit data FIFO.",
            handles.bpAPB,
            0x80,
            4,
            rtnZero,
            txData1,
            view32,
            &(bpAPB_ab_data.TXD1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXD2",
            "Transmit Data Register. Keyhole addresses for the Transmit data FIFO.",
            handles.bpAPB,
            0x84,
            4,
            rtnZero,
            txData2,
            view32,
            &(bpAPB_ab_data.TXD2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXD3",
            "Transmit Data Register. Keyhole addresses for the Transmit data FIFO.",
            handles.bpAPB,
            0x88,
            4,
            rtnZero,
            txData3,
            view32,
            &(bpAPB_ab_data.TXD3.value),
            True
        );
    }
    {
        registerHandle abLQSPI_CFG_reg = ppmCreateRegister(
            "ab_LQSPI_CFG",
            "Configuration Register specifically for the Linear Quad-SPI Controller",
            handles.bpAPB,
            0xa0,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.LQSPI_CFG.value),
            True
        );

        ppmCreateRegisterField(abLQSPI_CFG_reg, "LQ_MODE", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "TWO_MEM", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "SEP_BUS", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "U_PAGE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "MODE_EN", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "MODE_ON", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "MODE_BITS", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "DUMMY", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abLQSPI_CFG_reg, "INST", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abLQSPI_STS_reg = ppmCreateRegister(
            "ab_LQSPI_STS",
            "Status Register specifically for the Linear Quad-SPI Controller",
            handles.bpAPB,
            0xa4,
            4,
            read_32,
            bpAPB_ab_LQSPI_STS_maskWrite,
            view32,
            &(bpAPB_ab_data.LQSPI_STS.value),
            True
        );

        ppmCreateRegisterField(abLQSPI_STS_reg, "D_FSM_ERR", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abLQSPI_STS_reg, "WR_RECVD", 0, 1, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_MOD_ID",
            "Module Identification register",
            handles.bpAPB,
            0xfc,
            4,
            read_32,
            write_32,
            view32,
            &(bpAPB_ab_data.MOD_ID.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bpAPB_ab_data.MOD_ID.value = (Uns32)(bpAPB_ab_data.MOD_ID.value & ~(0xffffffff)) | ((0xffffffff) & (0x01090101));
        bpAPB_ab_data.LQSPI_STS.value = (Uns32)(bpAPB_ab_data.LQSPI_STS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.LQSPI_CFG.value = (Uns32)(bpAPB_ab_data.LQSPI_CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x07a002eb));
        bpAPB_ab_data.TXD3.value = (Uns32)(bpAPB_ab_data.TXD3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.TXD2.value = (Uns32)(bpAPB_ab_data.TXD2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.TXD1.value = (Uns32)(bpAPB_ab_data.TXD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.LPBK_DLY_ADJ.value = (Uns32)(bpAPB_ab_data.LPBK_DLY_ADJ.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000033));
        bpAPB_ab_data.GPIO.value = (Uns32)(bpAPB_ab_data.GPIO.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bpAPB_ab_data.RX_thres_REG.value = (Uns32)(bpAPB_ab_data.RX_thres_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bpAPB_ab_data.TX_thres_REG.value = (Uns32)(bpAPB_ab_data.TX_thres_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bpAPB_ab_data.Slave_Idle_count_REG.value = (Uns32)(bpAPB_ab_data.Slave_Idle_count_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000FF));
        bpAPB_ab_data.Rx_data_REG.value = (Uns32)(bpAPB_ab_data.Rx_data_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.TXD0.value = (Uns32)(bpAPB_ab_data.TXD0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.Delay_REG.value = (Uns32)(bpAPB_ab_data.Delay_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.En_REG.value = (Uns32)(bpAPB_ab_data.En_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.Intrpt_mask_REG.value = (Uns32)(bpAPB_ab_data.Intrpt_mask_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.Intrpt_dis_REG.value = (Uns32)(bpAPB_ab_data.Intrpt_dis_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.Intrpt_en_REG.value = (Uns32)(bpAPB_ab_data.Intrpt_en_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bpAPB_ab_data.Intr_status_REG.value = (Uns32)(bpAPB_ab_data.Intr_status_REG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bpAPB_ab_data.Config_reg.value = (Uns32)(bpAPB_ab_data.Config_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x80020000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Quad-SPI Registers and incorporates Flash Memory (Spansion and Micron) for Zync zc702/zc706 boards");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers but not all flash memory accesses are supported.");
        ppmDocAddText(doc_22_node, "The model is tested using Xilinx Example Project for R/W a QPSI memory on ZC702 platform using Polled and Interrupt driven Transfers.\n    https://github.com/Xilinx/embeddedsw/tree/master/XilinxProcessorIPLib/drivers/qspips/examples");
        ppmDocAddText(doc_22_node, "The AXI mode of operation is not tested. There is no write protection implemented for memory access when in AXI mode.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
        ppmDocAddText(doc_32_node, "https://xilinx.github.io/embeddedsw.github.io/qspips/doc/html/api/index.html");
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

