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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H                      

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#ifdef _PSE_
//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW                    (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM                 (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))

#define PSE_DIAG_HIGH                   (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST               (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

#endif
/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
    } ddrc_ctrl;
    union { 
        Uns32 value;
    } Two_rank_cfg;
    union { 
        Uns32 value;
    } HPR_reg;
    union { 
        Uns32 value;
    } LPR_reg;
    union { 
        Uns32 value;
    } WR_reg;
    union { 
        Uns32 value;
    } DRAM_param_reg0;
    union { 
        Uns32 value;
    } DRAM_param_reg1;
    union { 
        Uns32 value;
    } DRAM_param_reg2;
    union { 
        Uns32 value;
    } DRAM_param_reg3;
    union { 
        Uns32 value;
    } DRAM_param_reg4;
    union { 
        Uns32 value;
    } DRAM_init_param;
    union { 
        Uns32 value;
    } DRAM_EMR_reg;
    union { 
        Uns32 value;
    } DRAM_EMR_MR_reg;
    union { 
        Uns32 value;
    } DRAM_burst8_rdwr;
    union { 
        Uns32 value;
    } DRAM_disable_DQ;
    union { 
        Uns32 value;
    } DRAM_addr_map_bank;
    union { 
        Uns32 value;
    } DRAM_addr_map_col;
    union { 
        Uns32 value;
    } DRAM_addr_map_row;
    union { 
        Uns32 value;
    } DRAM_ODT_reg;
    union { 
        Uns32 value;
    } phy_dbg_reg;
    union { 
        Uns32 value;
    } phy_cmd_timeout_rddata_cpt;
    union { 
        Uns32 value;
    } mode_sts_reg;
    union { 
        Uns32 value;
    } DLL_calib;
    union { 
        Uns32 value;
    } ODT_delay_hold;
    union { 
        Uns32 value;
    } ctrl_reg1;
    union { 
        Uns32 value;
    } ctrl_reg2;
    union { 
        Uns32 value;
    } ctrl_reg3;
    union { 
        Uns32 value;
    } ctrl_reg4;
    union { 
        Uns32 value;
    } ctrl_reg5;
    union { 
        Uns32 value;
    } ctrl_reg6;
    union { 
        Uns32 value;
    } CHE_REFRESH_TIMER01;
    union { 
        Uns32 value;
    } CHE_T_ZQ;
    union { 
        Uns32 value;
    } CHE_T_ZQ_Short_Interval_Reg;
    union { 
        Uns32 value;
    } deep_pwrdwn_reg;
    union { 
        Uns32 value;
    } reg_2c;
    union { 
        Uns32 value;
    } reg_2d;
    union { 
        Uns32 value;
    } dfi_timing;
    union { 
        Uns32 value;
    } CHE_ECC_CONTROL_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_CORR_ECC_LOG_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_CORR_ECC_ADDR_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_CORR_ECC_DATA_31_0_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_CORR_ECC_DATA_63_32_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_CORR_ECC_DATA_71_64_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_UNCORR_ECC_LOG_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_UNCORR_ECC_ADDR_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_ECC_STATS_REG_OFFSET;
    union { 
        Uns32 value;
    } ECC_scrub;
    union { 
        Uns32 value;
    } CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET;
    union { 
        Uns32 value;
    } CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET;
    union { 
        Uns32 value;
    } phy_rcvr_enable;
    union { 
        Uns32 value;
    } PHY_Config0;
    union { 
        Uns32 value;
    } PHY_Config1;
    union { 
        Uns32 value;
    } PHY_Config2;
    union { 
        Uns32 value;
    } PHY_Config3;
    union { 
        Uns32 value;
    } phy_init_ratio0;
    union { 
        Uns32 value;
    } phy_init_ratio1;
    union { 
        Uns32 value;
    } phy_init_ratio2;
    union { 
        Uns32 value;
    } phy_init_ratio3;
    union { 
        Uns32 value;
    } phy_rd_dqs_cfg0;
    union { 
        Uns32 value;
    } phy_rd_dqs_cfg1;
    union { 
        Uns32 value;
    } phy_rd_dqs_cfg2;
    union { 
        Uns32 value;
    } phy_rd_dqs_cfg3;
    union { 
        Uns32 value;
    } phy_wr_dqs_cfg0;
    union { 
        Uns32 value;
    } phy_wr_dqs_cfg1;
    union { 
        Uns32 value;
    } phy_wr_dqs_cfg2;
    union { 
        Uns32 value;
    } phy_wr_dqs_cfg3;
    union { 
        Uns32 value;
    } phy_we_cfg0;
    union { 
        Uns32 value;
    } phy_we_cfg1;
    union { 
        Uns32 value;
    } phy_we_cfg2;
    union { 
        Uns32 value;
    } phy_we_cfg3;
    union { 
        Uns32 value;
    } wr_data_slv0;
    union { 
        Uns32 value;
    } wr_data_slv1;
    union { 
        Uns32 value;
    } wr_data_slv2;
    union { 
        Uns32 value;
    } wr_data_slv3;
    union { 
        Uns32 value;
    } reg_64;
    union { 
        Uns32 value;
    } reg_65;
    union { 
        Uns32 value;
    } reg69_6a0;
    union { 
        Uns32 value;
    } reg69_6a1;
    union { 
        Uns32 value;
    } reg6c_6d2;
    union { 
        Uns32 value;
    } reg6c_6d3;
    union { 
        Uns32 value;
    } reg6e_710;
    union { 
        Uns32 value;
    } reg6e_711;
    union { 
        Uns32 value;
    } reg6e_712;
    union { 
        Uns32 value;
    } reg6e_713;
    union { 
        Uns32 value;
    } phy_dll_sts0;
    union { 
        Uns32 value;
    } phy_dll_sts1;
    union { 
        Uns32 value;
    } phy_dll_sts2;
    union { 
        Uns32 value;
    } phy_dll_sts3;
    union { 
        Uns32 value;
    } dll_lock_sts;
    union { 
        Uns32 value;
    } phy_ctrl_sts;
    union { 
        Uns32 value;
    } phy_ctrl_sts_reg2;
    union { 
        Uns32 value;
    } axi_id;
    union { 
        Uns32 value;
    } axi_priority_wr_port0;
    union { 
        Uns32 value;
    } axi_priority_wr_port1;
    union { 
        Uns32 value;
    } axi_priority_wr_port2;
    union { 
        Uns32 value;
    } axi_priority_wr_port3;
    union { 
        Uns32 value;
    } axi_priority_rd_port0;
    union { 
        Uns32 value;
    } axi_priority_rd_port1;
    union { 
        Uns32 value;
    } axi_priority_rd_port2;
    union { 
        Uns32 value;
    } axi_priority_rd_port3;
    union { 
        Uns32 value;
    } excl_access_cfg0;
    union { 
        Uns32 value;
    } excl_access_cfg1;
    union { 
        Uns32 value;
    } excl_access_cfg2;
    union { 
        Uns32 value;
    } excl_access_cfg3;
    union { 
        Uns32 value;
    } mode_reg_read;
    union { 
        Uns32 value;
    } lpddr_ctrl0;
    union { 
        Uns32 value;
    } lpddr_ctrl1;
    union { 
        Uns32 value;
    } lpddr_ctrl2;
    union { 
        Uns32 value;
    } lpddr_ctrl3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_DDRC_CTRL_WIDTH       32
#define BPORT1_AB_TWO_RANK_CFG_WIDTH    32
#define BPORT1_AB_HPR_REG_WIDTH         32
#define BPORT1_AB_LPR_REG_WIDTH         32
#define BPORT1_AB_WR_REG_WIDTH          32
#define BPORT1_AB_DRAM_PARAM_REG0_WIDTH  32
#define BPORT1_AB_DRAM_PARAM_REG1_WIDTH  32
#define BPORT1_AB_DRAM_PARAM_REG2_WIDTH  32
#define BPORT1_AB_DRAM_PARAM_REG3_WIDTH  32
#define BPORT1_AB_DRAM_PARAM_REG4_WIDTH  32
#define BPORT1_AB_DRAM_INIT_PARAM_WIDTH  32
#define BPORT1_AB_DRAM_EMR_REG_WIDTH    32
#define BPORT1_AB_DRAM_EMR_MR_REG_WIDTH  32
#define BPORT1_AB_DRAM_BURST8_RDWR_WIDTH  32
#define BPORT1_AB_DRAM_DISABLE_DQ_WIDTH  32
#define BPORT1_AB_DRAM_ADDR_MAP_BANK_WIDTH  32
#define BPORT1_AB_DRAM_ADDR_MAP_COL_WIDTH  32
#define BPORT1_AB_DRAM_ADDR_MAP_ROW_WIDTH  32
#define BPORT1_AB_DRAM_ODT_REG_WIDTH    32
#define BPORT1_AB_PHY_DBG_REG_WIDTH     32
#define BPORT1_AB_PHY_CMD_TIMEOUT_RDDATA_CPT_WIDTH  32
#define BPORT1_AB_MODE_STS_REG_WIDTH    32
#define BPORT1_AB_DLL_CALIB_WIDTH       32
#define BPORT1_AB_ODT_DELAY_HOLD_WIDTH  32
#define BPORT1_AB_CTRL_REG1_WIDTH       32
#define BPORT1_AB_CTRL_REG2_WIDTH       32
#define BPORT1_AB_CTRL_REG3_WIDTH       32
#define BPORT1_AB_CTRL_REG4_WIDTH       32
#define BPORT1_AB_CTRL_REG5_WIDTH       32
#define BPORT1_AB_CTRL_REG6_WIDTH       32
#define BPORT1_AB_CHE_REFRESH_TIMER01_WIDTH  32
#define BPORT1_AB_CHE_T_ZQ_WIDTH        32
#define BPORT1_AB_CHE_T_ZQ_SHORT_INTERVAL_REG_WIDTH  32
#define BPORT1_AB_DEEP_PWRDWN_REG_WIDTH  32
#define BPORT1_AB_REG_2C_WIDTH          32
#define BPORT1_AB_REG_2D_WIDTH          32
#define BPORT1_AB_DFI_TIMING_WIDTH      32
#define BPORT1_AB_CHE_ECC_CONTROL_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_CORR_ECC_LOG_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_CORR_ECC_ADDR_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_CORR_ECC_DATA_31_0_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_CORR_ECC_DATA_63_32_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_CORR_ECC_DATA_71_64_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_UNCORR_ECC_LOG_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_UNCORR_ECC_ADDR_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_ECC_STATS_REG_OFFSET_WIDTH  32
#define BPORT1_AB_ECC_SCRUB_WIDTH       32
#define BPORT1_AB_CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET_WIDTH  32
#define BPORT1_AB_CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET_WIDTH  32
#define BPORT1_AB_PHY_RCVR_ENABLE_WIDTH  32
#define BPORT1_AB_PHY_CONFIG0_WIDTH     32
#define BPORT1_AB_PHY_CONFIG1_WIDTH     32
#define BPORT1_AB_PHY_CONFIG2_WIDTH     32
#define BPORT1_AB_PHY_CONFIG3_WIDTH     32
#define BPORT1_AB_PHY_INIT_RATIO0_WIDTH  32
#define BPORT1_AB_PHY_INIT_RATIO1_WIDTH  32
#define BPORT1_AB_PHY_INIT_RATIO2_WIDTH  32
#define BPORT1_AB_PHY_INIT_RATIO3_WIDTH  32
#define BPORT1_AB_PHY_RD_DQS_CFG0_WIDTH  32
#define BPORT1_AB_PHY_RD_DQS_CFG1_WIDTH  32
#define BPORT1_AB_PHY_RD_DQS_CFG2_WIDTH  32
#define BPORT1_AB_PHY_RD_DQS_CFG3_WIDTH  32
#define BPORT1_AB_PHY_WR_DQS_CFG0_WIDTH  32
#define BPORT1_AB_PHY_WR_DQS_CFG1_WIDTH  32
#define BPORT1_AB_PHY_WR_DQS_CFG2_WIDTH  32
#define BPORT1_AB_PHY_WR_DQS_CFG3_WIDTH  32
#define BPORT1_AB_PHY_WE_CFG0_WIDTH     32
#define BPORT1_AB_PHY_WE_CFG1_WIDTH     32
#define BPORT1_AB_PHY_WE_CFG2_WIDTH     32
#define BPORT1_AB_PHY_WE_CFG3_WIDTH     32
#define BPORT1_AB_WR_DATA_SLV0_WIDTH    32
#define BPORT1_AB_WR_DATA_SLV1_WIDTH    32
#define BPORT1_AB_WR_DATA_SLV2_WIDTH    32
#define BPORT1_AB_WR_DATA_SLV3_WIDTH    32
#define BPORT1_AB_REG_64_WIDTH          32
#define BPORT1_AB_REG_65_WIDTH          32
#define BPORT1_AB_REG69_6A0_WIDTH       32
#define BPORT1_AB_REG69_6A1_WIDTH       32
#define BPORT1_AB_REG6C_6D2_WIDTH       32
#define BPORT1_AB_REG6C_6D3_WIDTH       32
#define BPORT1_AB_REG6E_710_WIDTH       32
#define BPORT1_AB_REG6E_711_WIDTH       32
#define BPORT1_AB_REG6E_712_WIDTH       32
#define BPORT1_AB_REG6E_713_WIDTH       32
#define BPORT1_AB_PHY_DLL_STS0_WIDTH    32
#define BPORT1_AB_PHY_DLL_STS1_WIDTH    32
#define BPORT1_AB_PHY_DLL_STS2_WIDTH    32
#define BPORT1_AB_PHY_DLL_STS3_WIDTH    32
#define BPORT1_AB_DLL_LOCK_STS_WIDTH    32
#define BPORT1_AB_PHY_CTRL_STS_WIDTH    32
#define BPORT1_AB_PHY_CTRL_STS_REG2_WIDTH  32
#define BPORT1_AB_AXI_ID_WIDTH          32
#define BPORT1_AB_AXI_PRIORITY_WR_PORT0_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_WR_PORT1_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_WR_PORT2_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_WR_PORT3_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_RD_PORT0_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_RD_PORT1_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_RD_PORT2_WIDTH  32
#define BPORT1_AB_AXI_PRIORITY_RD_PORT3_WIDTH  32
#define BPORT1_AB_EXCL_ACCESS_CFG0_WIDTH  32
#define BPORT1_AB_EXCL_ACCESS_CFG1_WIDTH  32
#define BPORT1_AB_EXCL_ACCESS_CFG2_WIDTH  32
#define BPORT1_AB_EXCL_ACCESS_CFG3_WIDTH  32
#define BPORT1_AB_MODE_REG_READ_WIDTH   32
#define BPORT1_AB_LPDDR_CTRL0_WIDTH     32
#define BPORT1_AB_LPDDR_CTRL1_WIDTH     32
#define BPORT1_AB_LPDDR_CTRL2_WIDTH     32
#define BPORT1_AB_LPDDR_CTRL3_WIDTH     32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
