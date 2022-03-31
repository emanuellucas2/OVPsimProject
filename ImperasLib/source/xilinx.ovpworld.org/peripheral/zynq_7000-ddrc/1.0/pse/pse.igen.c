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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-ddrc", "Example");
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
            "ab_ddrc_ctrl",
            "DDRC Control",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ddrc_ctrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Two_rank_cfg",
            "Two Rank Configuration",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Two_rank_cfg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HPR_reg",
            "HPR Queue control",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.HPR_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LPR_reg",
            "LPR Queue control",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.LPR_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_WR_reg",
            "WR Queue control",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.WR_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_param_reg0",
            "DRAM Parameters 0",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_param_reg0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_param_reg1",
            "DRAM Parameters 1",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_param_reg1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_param_reg2",
            "DRAM Parameters 2",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_param_reg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_param_reg3",
            "DRAM Parameters 3",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_param_reg3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_param_reg4",
            "DRAM Parameters 4",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_param_reg4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_init_param",
            "DRAM Initialization Parameters",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_init_param.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_EMR_reg",
            "DRAM EMR2, EMR3 access",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_EMR_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_EMR_MR_reg",
            "DRAM EMR, MR access",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_EMR_MR_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_burst8_rdwr",
            "DRAM Burst 8 read/write",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_burst8_rdwr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_disable_DQ",
            "DRAM Disable DQ",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_disable_DQ.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_addr_map_bank",
            "Row/Column address bits",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_addr_map_bank.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_addr_map_col",
            "Column address bits",
            handles.bport1,
            0x40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_addr_map_col.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_addr_map_row",
            "Select DRAM row address bits",
            handles.bport1,
            0x44,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_addr_map_row.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DRAM_ODT_reg",
            "DRAM ODT control",
            handles.bport1,
            0x48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DRAM_ODT_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_dbg_reg",
            "PHY debug",
            handles.bport1,
            0x4c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_dbg_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_cmd_timeout_rddata_cpt",
            "PHY command time out and read data capture FIFO",
            handles.bport1,
            0x50,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_cmd_timeout_rddata_cpt.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_mode_sts_reg",
            "Controller operation mode status",
            handles.bport1,
            0x54,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.mode_sts_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DLL_calib",
            "DLL calibration",
            handles.bport1,
            0x58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DLL_calib.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ODT_delay_hold",
            "ODT delay and ODT hold",
            handles.bport1,
            0x5c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ODT_delay_hold.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl_reg1",
            "Controller 1",
            handles.bport1,
            0x60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ctrl_reg1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl_reg2",
            "Controller 2",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ctrl_reg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl_reg3",
            "Controller 3",
            handles.bport1,
            0x68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ctrl_reg3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl_reg4",
            "Controller 4",
            handles.bport1,
            0x6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ctrl_reg4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl_reg5",
            "Controller register 5",
            handles.bport1,
            0x78,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ctrl_reg5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl_reg6",
            "Controller register 6",
            handles.bport1,
            0x7c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ctrl_reg6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_REFRESH_TIMER01",
            "CHE_REFRESH_TIMER01",
            handles.bport1,
            0xa0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_REFRESH_TIMER01.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_T_ZQ",
            "ZQ parameters",
            handles.bport1,
            0xa4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_T_ZQ.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_T_ZQ_Short_Interval_Reg",
            "Misc parameters",
            handles.bport1,
            0xa8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_T_ZQ_Short_Interval_Reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_deep_pwrdwn_reg",
            "Deep powerdown (LPDDR2)",
            handles.bport1,
            0xac,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.deep_pwrdwn_reg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg_2c",
            "Training control",
            handles.bport1,
            0xb0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg_2c.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg_2d",
            "Misc Debug",
            handles.bport1,
            0xb4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg_2d.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_dfi_timing",
            "DFI timing",
            handles.bport1,
            0xb8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.dfi_timing.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_ECC_CONTROL_REG_OFFSET",
            "ECC error clear",
            handles.bport1,
            0xc4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_ECC_CONTROL_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_CORR_ECC_LOG_REG_OFFSET",
            "ECC error correction",
            handles.bport1,
            0xc8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_CORR_ECC_LOG_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_CORR_ECC_ADDR_REG_OFFSET",
            "ECC error correction address log",
            handles.bport1,
            0xcc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_CORR_ECC_ADDR_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_CORR_ECC_DATA_31_0_REG_OFFSET",
            "ECC error correction data log low",
            handles.bport1,
            0xd0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_CORR_ECC_DATA_31_0_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_CORR_ECC_DATA_63_32_REG_OFFSET",
            "ECC error correction data log mid",
            handles.bport1,
            0xd4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_CORR_ECC_DATA_63_32_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_CORR_ECC_DATA_71_64_REG_OFFSET",
            "ECC error correction data log high",
            handles.bport1,
            0xd8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_CORR_ECC_DATA_71_64_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_UNCORR_ECC_LOG_REG_OFFSET",
            "ECC unrecoverable error status",
            handles.bport1,
            0xdc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_UNCORR_ECC_LOG_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_UNCORR_ECC_ADDR_REG_OFFSET",
            "ECC unrecoverable error address",
            handles.bport1,
            0xe0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_UNCORR_ECC_ADDR_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET",
            "ECC unrecoverable error data low",
            handles.bport1,
            0xe4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET",
            "ECC unrecoverable error data middle",
            handles.bport1,
            0xe8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET",
            "ECC unrecoverable error data high",
            handles.bport1,
            0xec,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_ECC_STATS_REG_OFFSET",
            "ECC error count",
            handles.bport1,
            0xf0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_ECC_STATS_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ECC_scrub",
            "ECC mode/scrub",
            handles.bport1,
            0xf4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ECC_scrub.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET",
            "ECC data mask low",
            handles.bport1,
            0xf8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET",
            "ECC data mask high",
            handles.bport1,
            0xfc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_rcvr_enable",
            "Phy receiver enable register",
            handles.bport1,
            0x114,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_rcvr_enable.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PHY_Config0",
            "PHY configuration register for data slice 0.",
            handles.bport1,
            0x118,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PHY_Config0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PHY_Config1",
            "PHY configuration register for data slice 1.",
            handles.bport1,
            0x11c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PHY_Config1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PHY_Config2",
            "PHY configuration register for data slice 2.",
            handles.bport1,
            0x120,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PHY_Config2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PHY_Config3",
            "PHY configuration register for data slice 3.",
            handles.bport1,
            0x124,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PHY_Config3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_init_ratio0",
            "PHY init ratio register for data slice 0.",
            handles.bport1,
            0x12c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_init_ratio0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_init_ratio1",
            "PHY init ratio register for data slice 1.",
            handles.bport1,
            0x130,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_init_ratio1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_init_ratio2",
            "PHY init ratio register for data slice 2.",
            handles.bport1,
            0x134,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_init_ratio2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_init_ratio3",
            "PHY init ratio register for data slice 3.",
            handles.bport1,
            0x138,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_init_ratio3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_rd_dqs_cfg0",
            "PHY read DQS configuration register for data slice 0.",
            handles.bport1,
            0x140,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_rd_dqs_cfg0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_rd_dqs_cfg1",
            "PHY read DQS configuration register for data slice 1.",
            handles.bport1,
            0x144,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_rd_dqs_cfg1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_rd_dqs_cfg2",
            "PHY read DQS configuration register for data slice 2.",
            handles.bport1,
            0x148,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_rd_dqs_cfg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_rd_dqs_cfg3",
            "PHY read DQS configuration register for data slice 3.",
            handles.bport1,
            0x14c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_rd_dqs_cfg3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_wr_dqs_cfg0",
            "PHY write DQS configuration register for data slice 0.",
            handles.bport1,
            0x154,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_wr_dqs_cfg0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_wr_dqs_cfg1",
            "PHY write DQS configuration register for data slice 1.",
            handles.bport1,
            0x158,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_wr_dqs_cfg1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_wr_dqs_cfg2",
            "PHY write DQS configuration register for data slice 2.",
            handles.bport1,
            0x15c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_wr_dqs_cfg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_wr_dqs_cfg3",
            "PHY write DQS configuration register for data slice 3.",
            handles.bport1,
            0x160,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_wr_dqs_cfg3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_we_cfg0",
            "PHY FIFO write enable configuration for data slice 0.",
            handles.bport1,
            0x168,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_we_cfg0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_we_cfg1",
            "PHY FIFO write enable configuration for data slice 1.",
            handles.bport1,
            0x16c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_we_cfg1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_we_cfg2",
            "PHY FIFO write enable configuration for data slice 2.",
            handles.bport1,
            0x170,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_we_cfg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_we_cfg3",
            "PHY FIFO write enable configuration for data slice 3.",
            handles.bport1,
            0x174,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_we_cfg3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_wr_data_slv0",
            "PHY write data slave ratio config for data slice 0.",
            handles.bport1,
            0x17c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.wr_data_slv0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_wr_data_slv1",
            "PHY write data slave ratio config for data slice 1.",
            handles.bport1,
            0x180,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.wr_data_slv1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_wr_data_slv2",
            "PHY write data slave ratio config for data slice 2.",
            handles.bport1,
            0x184,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.wr_data_slv2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_wr_data_slv3",
            "PHY write data slave ratio config for data slice 3.",
            handles.bport1,
            0x188,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.wr_data_slv3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg_64",
            "Training control 2",
            handles.bport1,
            0x190,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg_64.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg_65",
            "Training control 3",
            handles.bport1,
            0x194,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg_65.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg69_6a0",
            "Training results for data slice 0.",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg69_6a0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg69_6a1",
            "Training results for data slice 1.",
            handles.bport1,
            0x1a8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg69_6a1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg6c_6d2",
            "Training results for data slice 2.",
            handles.bport1,
            0x1b0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg6c_6d2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg6c_6d3",
            "Training results for data slice 3.",
            handles.bport1,
            0x1b4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg6c_6d3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg6e_710",
            "Training results (2) for data slice 0.",
            handles.bport1,
            0x1b8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg6e_710.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg6e_711",
            "Training results (2) for data slice 1.",
            handles.bport1,
            0x1bc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg6e_711.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg6e_712",
            "Training results (2) for data slice 2.",
            handles.bport1,
            0x1c0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg6e_712.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg6e_713",
            "Training results (2) for data slice 3.",
            handles.bport1,
            0x1c4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg6e_713.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_dll_sts0",
            "Slave DLL results for data slice 0.",
            handles.bport1,
            0x1cc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_dll_sts0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_dll_sts1",
            "Slave DLL results for data slice 1.",
            handles.bport1,
            0x1d0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_dll_sts1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_dll_sts2",
            "Slave DLL results for data slice 2.",
            handles.bport1,
            0x1d4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_dll_sts2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_dll_sts3",
            "Slave DLL results for data slice 3.",
            handles.bport1,
            0x1d8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_dll_sts3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_dll_lock_sts",
            "DLL Lock Status, read",
            handles.bport1,
            0x1e0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.dll_lock_sts.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_ctrl_sts",
            "PHY Control status, read",
            handles.bport1,
            0x1e4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_ctrl_sts.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_phy_ctrl_sts_reg2",
            "PHY Control status (2), read",
            handles.bport1,
            0x1e8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.phy_ctrl_sts_reg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_id",
            "ID and revision information page_mask 0x00000204 32 rw 0x00000000 Page mask",
            handles.bport1,
            0x200,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_id.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_wr_port0",
            "AXI Priority control for write port 0.",
            handles.bport1,
            0x208,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_wr_port0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_wr_port1",
            "AXI Priority control for write port 1.",
            handles.bport1,
            0x20c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_wr_port1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_wr_port2",
            "AXI Priority control for write port 2.",
            handles.bport1,
            0x210,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_wr_port2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_wr_port3",
            "AXI Priority control for write port 3.",
            handles.bport1,
            0x214,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_wr_port3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_rd_port0",
            "AXI Priority control for read port 0.",
            handles.bport1,
            0x218,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_rd_port0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_rd_port1",
            "AXI Priority control for read port 1.",
            handles.bport1,
            0x21c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_rd_port1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_rd_port2",
            "AXI Priority control for read port 2.",
            handles.bport1,
            0x220,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_rd_port2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_axi_priority_rd_port3",
            "AXI Priority control for read port 3.",
            handles.bport1,
            0x224,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.axi_priority_rd_port3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_excl_access_cfg0",
            "Exclusive access configuration for port 0.",
            handles.bport1,
            0x294,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.excl_access_cfg0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_excl_access_cfg1",
            "Exclusive access configuration for port 1.",
            handles.bport1,
            0x298,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.excl_access_cfg1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_excl_access_cfg2",
            "Exclusive access configuration for port 2.",
            handles.bport1,
            0x29c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.excl_access_cfg2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_excl_access_cfg3",
            "Exclusive access configuration for port 3.",
            handles.bport1,
            0x2a0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.excl_access_cfg3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_mode_reg_read",
            "Mode register read data",
            handles.bport1,
            0x2a4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.mode_reg_read.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lpddr_ctrl0",
            "LPDDR2 Control 0",
            handles.bport1,
            0x2a8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.lpddr_ctrl0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lpddr_ctrl1",
            "LPDDR2 Control 1",
            handles.bport1,
            0x2ac,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.lpddr_ctrl1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lpddr_ctrl2",
            "LPDDR2 Control 2",
            handles.bport1,
            0x2b0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.lpddr_ctrl2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lpddr_ctrl3",
            "LPDDR2 Control 3",
            handles.bport1,
            0x2b4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.lpddr_ctrl3.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.lpddr_ctrl3.value = (Uns32)(bport1_ab_data.lpddr_ctrl3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.lpddr_ctrl2.value = (Uns32)(bport1_ab_data.lpddr_ctrl2.value & ~(0xffffffff)) | ((0xffffffff) & (0x003C0015));
        bport1_ab_data.lpddr_ctrl1.value = (Uns32)(bport1_ab_data.lpddr_ctrl1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.lpddr_ctrl0.value = (Uns32)(bport1_ab_data.lpddr_ctrl0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.mode_reg_read.value = (Uns32)(bport1_ab_data.mode_reg_read.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.excl_access_cfg3.value = (Uns32)(bport1_ab_data.excl_access_cfg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.excl_access_cfg2.value = (Uns32)(bport1_ab_data.excl_access_cfg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.excl_access_cfg1.value = (Uns32)(bport1_ab_data.excl_access_cfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.excl_access_cfg0.value = (Uns32)(bport1_ab_data.excl_access_cfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.axi_priority_rd_port3.value = (Uns32)(bport1_ab_data.axi_priority_rd_port3.value & ~(0xffffffff)) | ((0xffffffff) & (0x000003FF));
        bport1_ab_data.axi_priority_rd_port2.value = (Uns32)(bport1_ab_data.axi_priority_rd_port2.value & ~(0xffffffff)) | ((0xffffffff) & (0x000003FF));
        bport1_ab_data.axi_priority_rd_port1.value = (Uns32)(bport1_ab_data.axi_priority_rd_port1.value & ~(0xffffffff)) | ((0xffffffff) & (0x000003FF));
        bport1_ab_data.axi_priority_rd_port0.value = (Uns32)(bport1_ab_data.axi_priority_rd_port0.value & ~(0xffffffff)) | ((0xffffffff) & (0x000003FF));
        bport1_ab_data.axi_priority_wr_port3.value = (Uns32)(bport1_ab_data.axi_priority_wr_port3.value & ~(0xffffffff)) | ((0xffffffff) & (0x000803FF));
        bport1_ab_data.axi_priority_wr_port2.value = (Uns32)(bport1_ab_data.axi_priority_wr_port2.value & ~(0xffffffff)) | ((0xffffffff) & (0x000803FF));
        bport1_ab_data.axi_priority_wr_port1.value = (Uns32)(bport1_ab_data.axi_priority_wr_port1.value & ~(0xffffffff)) | ((0xffffffff) & (0x000803FF));
        bport1_ab_data.axi_priority_wr_port0.value = (Uns32)(bport1_ab_data.axi_priority_wr_port0.value & ~(0xffffffff)) | ((0xffffffff) & (0x000803FF));
        bport1_ab_data.axi_id.value = (Uns32)(bport1_ab_data.axi_id.value & ~(0xffffffff)) | ((0xffffffff) & (0x00153042));
        bport1_ab_data.phy_ctrl_sts_reg2.value = (Uns32)(bport1_ab_data.phy_ctrl_sts_reg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000013));
        bport1_ab_data.phy_ctrl_sts.value = (Uns32)(bport1_ab_data.phy_ctrl_sts.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.dll_lock_sts.value = (Uns32)(bport1_ab_data.dll_lock_sts.value & ~(0xffffffff)) | ((0xffffffff) & (0x00F00000));
        bport1_ab_data.phy_dll_sts3.value = (Uns32)(bport1_ab_data.phy_dll_sts3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_dll_sts2.value = (Uns32)(bport1_ab_data.phy_dll_sts2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_dll_sts1.value = (Uns32)(bport1_ab_data.phy_dll_sts1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_dll_sts0.value = (Uns32)(bport1_ab_data.phy_dll_sts0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.reg6e_713.value = (Uns32)(bport1_ab_data.reg6e_713.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.reg6e_712.value = (Uns32)(bport1_ab_data.reg6e_712.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.reg6e_711.value = (Uns32)(bport1_ab_data.reg6e_711.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.reg6e_710.value = (Uns32)(bport1_ab_data.reg6e_710.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.reg6c_6d3.value = (Uns32)(bport1_ab_data.reg6c_6d3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000E00));
        bport1_ab_data.reg6c_6d2.value = (Uns32)(bport1_ab_data.reg6c_6d2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00040600));
        bport1_ab_data.reg69_6a1.value = (Uns32)(bport1_ab_data.reg69_6a1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00060200));
        bport1_ab_data.reg69_6a0.value = (Uns32)(bport1_ab_data.reg69_6a0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00070000));
        bport1_ab_data.reg_65.value = (Uns32)(bport1_ab_data.reg_65.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.reg_64.value = (Uns32)(bport1_ab_data.reg_64.value & ~(0xffffffff)) | ((0xffffffff) & (0x10020000));
        bport1_ab_data.wr_data_slv3.value = (Uns32)(bport1_ab_data.wr_data_slv3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000080));
        bport1_ab_data.wr_data_slv2.value = (Uns32)(bport1_ab_data.wr_data_slv2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000080));
        bport1_ab_data.wr_data_slv1.value = (Uns32)(bport1_ab_data.wr_data_slv1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000080));
        bport1_ab_data.wr_data_slv0.value = (Uns32)(bport1_ab_data.wr_data_slv0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000080));
        bport1_ab_data.phy_we_cfg3.value = (Uns32)(bport1_ab_data.phy_we_cfg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_we_cfg2.value = (Uns32)(bport1_ab_data.phy_we_cfg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_we_cfg1.value = (Uns32)(bport1_ab_data.phy_we_cfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_we_cfg0.value = (Uns32)(bport1_ab_data.phy_we_cfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_wr_dqs_cfg3.value = (Uns32)(bport1_ab_data.phy_wr_dqs_cfg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_wr_dqs_cfg2.value = (Uns32)(bport1_ab_data.phy_wr_dqs_cfg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_wr_dqs_cfg1.value = (Uns32)(bport1_ab_data.phy_wr_dqs_cfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_wr_dqs_cfg0.value = (Uns32)(bport1_ab_data.phy_wr_dqs_cfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_rd_dqs_cfg3.value = (Uns32)(bport1_ab_data.phy_rd_dqs_cfg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_rd_dqs_cfg2.value = (Uns32)(bport1_ab_data.phy_rd_dqs_cfg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_rd_dqs_cfg1.value = (Uns32)(bport1_ab_data.phy_rd_dqs_cfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_rd_dqs_cfg0.value = (Uns32)(bport1_ab_data.phy_rd_dqs_cfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000040));
        bport1_ab_data.phy_init_ratio3.value = (Uns32)(bport1_ab_data.phy_init_ratio3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_init_ratio2.value = (Uns32)(bport1_ab_data.phy_init_ratio2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_init_ratio1.value = (Uns32)(bport1_ab_data.phy_init_ratio1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_init_ratio0.value = (Uns32)(bport1_ab_data.phy_init_ratio0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PHY_Config3.value = (Uns32)(bport1_ab_data.PHY_Config3.value & ~(0xffffffff)) | ((0xffffffff) & (0x40000001));
        bport1_ab_data.PHY_Config2.value = (Uns32)(bport1_ab_data.PHY_Config2.value & ~(0xffffffff)) | ((0xffffffff) & (0x40000001));
        bport1_ab_data.PHY_Config1.value = (Uns32)(bport1_ab_data.PHY_Config1.value & ~(0xffffffff)) | ((0xffffffff) & (0x40000001));
        bport1_ab_data.PHY_Config0.value = (Uns32)(bport1_ab_data.PHY_Config0.value & ~(0xffffffff)) | ((0xffffffff) & (0x40000001));
        bport1_ab_data.phy_rcvr_enable.value = (Uns32)(bport1_ab_data.phy_rcvr_enable.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ECC_scrub.value = (Uns32)(bport1_ab_data.ECC_scrub.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000008));
        bport1_ab_data.CHE_ECC_STATS_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_ECC_STATS_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_UNCORR_ECC_ADDR_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_UNCORR_ECC_ADDR_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_UNCORR_ECC_LOG_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_UNCORR_ECC_LOG_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_CORR_ECC_DATA_71_64_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_CORR_ECC_DATA_71_64_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_CORR_ECC_DATA_63_32_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_CORR_ECC_DATA_63_32_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_CORR_ECC_DATA_31_0_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_CORR_ECC_DATA_31_0_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_CORR_ECC_ADDR_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_CORR_ECC_ADDR_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_CORR_ECC_LOG_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_CORR_ECC_LOG_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_ECC_CONTROL_REG_OFFSET.value = (Uns32)(bport1_ab_data.CHE_ECC_CONTROL_REG_OFFSET.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.dfi_timing.value = (Uns32)(bport1_ab_data.dfi_timing.value & ~(0xffffffff)) | ((0xffffffff) & (0x00200067));
        bport1_ab_data.reg_2d.value = (Uns32)(bport1_ab_data.reg_2d.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000200));
        bport1_ab_data.reg_2c.value = (Uns32)(bport1_ab_data.reg_2c.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.deep_pwrdwn_reg.value = (Uns32)(bport1_ab_data.deep_pwrdwn_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CHE_T_ZQ_Short_Interval_Reg.value = (Uns32)(bport1_ab_data.CHE_T_ZQ_Short_Interval_Reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x0020003A));
        bport1_ab_data.CHE_T_ZQ.value = (Uns32)(bport1_ab_data.CHE_T_ZQ.value & ~(0xffffffff)) | ((0xffffffff) & (0x10300802));
        bport1_ab_data.CHE_REFRESH_TIMER01.value = (Uns32)(bport1_ab_data.CHE_REFRESH_TIMER01.value & ~(0xffffffff)) | ((0xffffffff) & (0x00008000));
        bport1_ab_data.ctrl_reg6.value = (Uns32)(bport1_ab_data.ctrl_reg6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00032222));
        bport1_ab_data.ctrl_reg5.value = (Uns32)(bport1_ab_data.ctrl_reg5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00455111));
        bport1_ab_data.ctrl_reg4.value = (Uns32)(bport1_ab_data.ctrl_reg4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001610));
        bport1_ab_data.ctrl_reg3.value = (Uns32)(bport1_ab_data.ctrl_reg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00284027));
        bport1_ab_data.ctrl_reg2.value = (Uns32)(bport1_ab_data.ctrl_reg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00020000));
        bport1_ab_data.ctrl_reg1.value = (Uns32)(bport1_ab_data.ctrl_reg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000003E));
        bport1_ab_data.ODT_delay_hold.value = (Uns32)(bport1_ab_data.ODT_delay_hold.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000023));
        bport1_ab_data.DLL_calib.value = (Uns32)(bport1_ab_data.DLL_calib.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000101));
        bport1_ab_data.mode_sts_reg.value = (Uns32)(bport1_ab_data.mode_sts_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.phy_cmd_timeout_rddata_cpt.value = (Uns32)(bport1_ab_data.phy_cmd_timeout_rddata_cpt.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010200));
        bport1_ab_data.phy_dbg_reg.value = (Uns32)(bport1_ab_data.phy_dbg_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DRAM_ODT_reg.value = (Uns32)(bport1_ab_data.DRAM_ODT_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000249));
        bport1_ab_data.DRAM_addr_map_row.value = (Uns32)(bport1_ab_data.DRAM_addr_map_row.value & ~(0xffffffff)) | ((0xffffffff) & (0x0FF55555));
        bport1_ab_data.DRAM_addr_map_col.value = (Uns32)(bport1_ab_data.DRAM_addr_map_col.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFF00000));
        bport1_ab_data.DRAM_addr_map_bank.value = (Uns32)(bport1_ab_data.DRAM_addr_map_bank.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000F77));
        bport1_ab_data.DRAM_disable_DQ.value = (Uns32)(bport1_ab_data.DRAM_disable_DQ.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DRAM_burst8_rdwr.value = (Uns32)(bport1_ab_data.DRAM_burst8_rdwr.value & ~(0xffffffff)) | ((0xffffffff) & (0x00020034));
        bport1_ab_data.DRAM_EMR_MR_reg.value = (Uns32)(bport1_ab_data.DRAM_EMR_MR_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000940));
        bport1_ab_data.DRAM_EMR_reg.value = (Uns32)(bport1_ab_data.DRAM_EMR_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000008));
        bport1_ab_data.DRAM_init_param.value = (Uns32)(bport1_ab_data.DRAM_init_param.value & ~(0xffffffff)) | ((0xffffffff) & (0x00002007));
        bport1_ab_data.DRAM_param_reg4.value = (Uns32)(bport1_ab_data.DRAM_param_reg4.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000003C));
        bport1_ab_data.DRAM_param_reg3.value = (Uns32)(bport1_ab_data.DRAM_param_reg3.value & ~(0xffffffff)) | ((0xffffffff) & (0x250882D0));
        bport1_ab_data.DRAM_param_reg2.value = (Uns32)(bport1_ab_data.DRAM_param_reg2.value & ~(0xffffffff)) | ((0xffffffff) & (0x83015904));
        bport1_ab_data.DRAM_param_reg1.value = (Uns32)(bport1_ab_data.DRAM_param_reg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x351B48D9));
        bport1_ab_data.DRAM_param_reg0.value = (Uns32)(bport1_ab_data.DRAM_param_reg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00041016));
        bport1_ab_data.WR_reg.value = (Uns32)(bport1_ab_data.WR_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x0007F80F));
        bport1_ab_data.LPR_reg.value = (Uns32)(bport1_ab_data.LPR_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x03C0780F));
        bport1_ab_data.HPR_reg.value = (Uns32)(bport1_ab_data.HPR_reg.value & ~(0xffffffff)) | ((0xffffffff) & (0x03C0780F));
        bport1_ab_data.Two_rank_cfg.value = (Uns32)(bport1_ab_data.Two_rank_cfg.value & ~(0xffffffff)) | ((0xffffffff) & (0x000C1076));
        bport1_ab_data.ddrc_ctrl.value = (Uns32)(bport1_ab_data.ddrc_ctrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000200));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform DDR Memory Controller (DDRC)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers. There is no behavior included.");
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

