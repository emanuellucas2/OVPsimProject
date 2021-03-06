#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
#
# The contents of this file are provided under the Software License
# Agreement that you accepted before downloading this file.
#
# This source forms part of the Software and can be used for educational,
# training, and demonstration purposes but cannot be used for derivative
# works except in cases where the derivative works require OVP technology
# to run.
#
# For open source models released under licenses that you can use for
# derivative works, please visit www.OVPworld.org or www.imperas.com
# for the location of the open source models.
#

set vendor  xilinx.ovpworld.org
set library peripheral
set name    zynq_7000-ddrc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Platform DDR Memory Controller (DDRC)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers. There is no behavior included."

iadddocumentation \
    -name Reference \
    -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead
                     
#   rname roffset rsize raccess reset readFunc writeFunc writeMask bits description
set registers {
    ddrc_ctrl                              0x00000000 32 rw      0x00000200 -    -    -  -   "DDRC Control"
    Two_rank_cfg                           0x00000004 29 rw      0x000C1076 -    -    -  -   "Two Rank Configuration"
    HPR_reg                                0x00000008 26 rw      0x03C0780F -    -    -  -   "HPR Queue control"
    LPR_reg                                0x0000000C 26 rw      0x03C0780F -    -    -  -   "LPR Queue control"
    WR_reg                                 0x00000010 26 rw      0x0007F80F -    -    -  -   "WR Queue control"
    DRAM_param_reg0                        0x00000014 21 rw      0x00041016 -    -    -  -   "DRAM Parameters 0"
    DRAM_param_reg1                        0x00000018 32 rw      0x351B48D9 -    -    -  -   "DRAM Parameters 1"
    DRAM_param_reg2                        0x0000001C 32 rw      0x83015904 -    -    -  -   "DRAM Parameters 2"
    DRAM_param_reg3                        0x00000020 32 mixed   0x250882D0 -    -    -  -   "DRAM Parameters 3"
    DRAM_param_reg4                        0x00000024 28 mixed   0x0000003C -    -    -  -   "DRAM Parameters 4"
    DRAM_init_param                        0x00000028 14 rw      0x00002007 -    -    -  -   "DRAM Initialization Parameters"
    DRAM_EMR_reg                           0x0000002C 32 rw      0x00000008 -    -    -  -   "DRAM EMR2, EMR3 access"
    DRAM_EMR_MR_reg                        0x00000030 32 rw      0x00000940 -    -    -  -   "DRAM EMR, MR access"
    DRAM_burst8_rdwr                       0x00000034 29 mixed   0x00020034 -    -    -  -   "DRAM Burst 8 read/write"
    DRAM_disable_DQ                        0x00000038 13 mixed   0x00000000 -    -    -  -   "DRAM Disable DQ"
    DRAM_addr_map_bank                     0x0000003C 20 rw      0x00000F77 -    -    -  -   "Row/Column address bits"
    DRAM_addr_map_col                      0x00000040 32 rw      0xFFF00000 -    -    -  -   "Column address bits"
    DRAM_addr_map_row                      0x00000044 28 rw      0x0FF55555 -    -    -  -   "Select DRAM row address bits"
    DRAM_ODT_reg                           0x00000048 30 rw      0x00000249 -    -    -  -   "DRAM ODT control"
    phy_dbg_reg                            0x0000004C 20 r       0x00000000 -    -    -  -   "PHY debug"
    phy_cmd_timeout_rddata_cpt             0x00000050 32 mixed   0x00010200 -    -    -  -   "PHY command time out and read data capture FIFO"
    mode_sts_reg                           0x00000054 21 r       0x00000000 -    -    -  -   "Controller operation mode status"
    DLL_calib                              0x00000058 17 rw      0x00000101 -    -    -  -   "DLL calibration"
    ODT_delay_hold                         0x0000005C 16 rw      0x00000023 -    -    -  -   "ODT delay and ODT hold"
    ctrl_reg1                              0x00000060 13 mixed   0x0000003E -    -    -  -   "Controller 1"
    ctrl_reg2                              0x00000064 18 mixed   0x00020000 -    -    -  -   "Controller 2"
    ctrl_reg3                              0x00000068 26 rw      0x00284027 -    -    -  -   "Controller 3"
    ctrl_reg4                              0x0000006C 16 rw      0x00001610 -    -    -  -   "Controller 4"
    ctrl_reg5                              0x00000078 32 mixed   0x00455111 -    -    -  -   "Controller register 5"
    ctrl_reg6                              0x0000007C 32 mixed   0x00032222 -    -    -  -   "Controller register 6"
    CHE_REFRESH_TIMER01                    0x000000A0 24 rw      0x00008000 -    -    -  -   "CHE_REFRESH_TIMER01"
    CHE_T_ZQ                               0x000000A4 32 rw      0x10300802 -    -    -  -   "ZQ parameters"
    CHE_T_ZQ_Short_Interval_Reg            0x000000A8 28 rw      0x0020003A -    -    -  -   "Misc parameters"
    deep_pwrdwn_reg                        0x000000AC 9  rw      0x00000000 -    -    -  -   "Deep powerdown (LPDDR2)"
    reg_2c                                 0x000000B0 29 mixed   0x00000000 -    -    -  -   "Training control"
    reg_2d                                 0x000000B4 11 rw      0x00000200 -    -    -  -   "Misc Debug"
    dfi_timing                             0x000000B8 25 rw      0x00200067 -    -    -  -   "DFI timing"
    CHE_ECC_CONTROL_REG_OFFSET             0x000000C4 2  rw      0x00000000 -    -    -  -   "ECC error clear"
    CHE_CORR_ECC_LOG_REG_OFFSET            0x000000C8 8  mixed   0x00000000 -    -    -  -   "ECC error correction"
    CHE_CORR_ECC_ADDR_REG_OFFSET           0x000000CC 31 r       0x00000000 -    -    -  -   "ECC error correction address log"
    CHE_CORR_ECC_DATA_31_0_REG_OFFSET      0x000000D0 32 r       0x00000000 -    -    -  -   "ECC error correction data log low"
    CHE_CORR_ECC_DATA_63_32_REG_OFFSET     0x000000D4 32 r       0x00000000 -    -    -  -   "ECC error correction data log mid"
    CHE_CORR_ECC_DATA_71_64_REG_OFFSET     0x000000D8 8  r       0x00000000 -    -    -  -   "ECC error correction data log high"
    CHE_UNCORR_ECC_LOG_REG_OFFSET          0x000000DC 1  clronwr 0x00000000 -    -    -  -   "ECC unrecoverable error status"
    CHE_UNCORR_ECC_ADDR_REG_OFFSET         0x000000E0 31 r       0x00000000 -    -    -  -   "ECC unrecoverable error address"
    CHE_UNCORR_ECC_DATA_31_0_REG_OFFSET    0x000000E4 32 r       0x00000000 -    -    -  -   "ECC unrecoverable error data low"
    CHE_UNCORR_ECC_DATA_63_32_REG_OFFSET   0x000000E8 32 r       0x00000000 -    -    -  -   "ECC unrecoverable error data middle"
    CHE_UNCORR_ECC_DATA_71_64_REG_OFFSET   0x000000EC 8  r       0x00000000 -    -    -  -   "ECC unrecoverable error data high"
    CHE_ECC_STATS_REG_OFFSET               0x000000F0 16 clronwr 0x00000000 -    -    -  -   "ECC error count"
    ECC_scrub                              0x000000F4 4  rw      0x00000008 -    -    -  -   "ECC mode/scrub"
    CHE_ECC_CORR_BIT_MASK_31_0_REG_OFFSET  0x000000F8 32 r       0x00000000 -    -    -  -   "ECC data mask low"
    CHE_ECC_CORR_BIT_MASK_63_32_REG_OFFSET 0x000000FC 32 r       0x00000000 -    -    -  -   "ECC data mask high"
    phy_rcvr_enable                        0x00000114 8  rw      0x00000000 -    -    -  -   "Phy receiver enable register"
    PHY_Config0                            0x00000118 31 rw      0x40000001 -    -    -  -   "PHY configuration register for data slice 0."
    PHY_Config1                            0x0000011C 31 rw      0x40000001 -    -    -  -   "PHY configuration register for data slice 1."
    PHY_Config2                            0x00000120 31 rw      0x40000001 -    -    -  -   "PHY configuration register for data slice 2."
    PHY_Config3                            0x00000124 31 rw      0x40000001 -    -    -  -   "PHY configuration register for data slice 3."
    phy_init_ratio0                        0x0000012C 20 rw      0x00000000 -    -    -  -   "PHY init ratio register for data slice 0."
    phy_init_ratio1                        0x00000130 20 rw      0x00000000 -    -    -  -   "PHY init ratio register for data slice 1."
    phy_init_ratio2                        0x00000134 20 rw      0x00000000 -    -    -  -   "PHY init ratio register for data slice 2."
    phy_init_ratio3                        0x00000138 20 rw      0x00000000 -    -    -  -   "PHY init ratio register for data slice 3."
    phy_rd_dqs_cfg0                        0x00000140 20 rw      0x00000040 -    -    -  -   "PHY read DQS configuration register for data slice 0."
    phy_rd_dqs_cfg1                        0x00000144 20 rw      0x00000040 -    -    -  -   "PHY read DQS configuration register for data slice 1."
    phy_rd_dqs_cfg2                        0x00000148 20 rw      0x00000040 -    -    -  -   "PHY read DQS configuration register for data slice 2."
    phy_rd_dqs_cfg3                        0x0000014C 20 rw      0x00000040 -    -    -  -   "PHY read DQS configuration register for data slice 3."
    phy_wr_dqs_cfg0                        0x00000154 20 rw      0x00000000 -    -    -  -   "PHY write DQS configuration register for data slice 0."
    phy_wr_dqs_cfg1                        0x00000158 20 rw      0x00000000 -    -    -  -   "PHY write DQS configuration register for data slice 1."
    phy_wr_dqs_cfg2                        0x0000015C 20 rw      0x00000000 -    -    -  -   "PHY write DQS configuration register for data slice 2."
    phy_wr_dqs_cfg3                        0x00000160 20 rw      0x00000000 -    -    -  -   "PHY write DQS configuration register for data slice 3."
    phy_we_cfg0                            0x00000168 21 rw      0x00000040 -    -    -  -   "PHY FIFO write enable configuration for data slice 0."
    phy_we_cfg1                            0x0000016C 21 rw      0x00000040 -    -    -  -   "PHY FIFO write enable configuration for data slice 1."
    phy_we_cfg2                            0x00000170 21 rw      0x00000040 -    -    -  -   "PHY FIFO write enable configuration for data slice 2."
    phy_we_cfg3                            0x00000174 21 rw      0x00000040 -    -    -  -   "PHY FIFO write enable configuration for data slice 3."
    wr_data_slv0                           0x0000017C 20 rw      0x00000080 -    -    -  -   "PHY write data slave ratio config for data slice 0."
    wr_data_slv1                           0x00000180 20 rw      0x00000080 -    -    -  -   "PHY write data slave ratio config for data slice 1."
    wr_data_slv2                           0x00000184 20 rw      0x00000080 -    -    -  -   "PHY write data slave ratio config for data slice 2."
    wr_data_slv3                           0x00000188 20 rw      0x00000080 -    -    -  -   "PHY write data slave ratio config for data slice 3."
    reg_64                                 0x00000190 32 rw      0x10020000 -    -    -  -   "Training control 2"
    reg_65                                 0x00000194 20 rw      0x00000000 -    -    -  -   "Training control 3"
    reg69_6a0                              0x000001A4 29 r       0x00070000 -    -    -  -   "Training results for data slice 0."
    reg69_6a1                              0x000001A8 29 r       0x00060200 -    -    -  -   "Training results for data slice 1."
    reg6c_6d2                              0x000001B0 28 r       0x00040600 -    -    -  -   "Training results for data slice 2."
    reg6c_6d3                              0x000001B4 28 r       0x00000E00 -    -    -  -   "Training results for data slice 3."
    reg6e_710                              0x000001B8 30 r       x          -    -    -  -   "Training results (2) for data slice 0."
    reg6e_711                              0x000001BC 30 r       x          -    -    -  -   "Training results (2) for data slice 1."
    reg6e_712                              0x000001C0 30 r       x          -    -    -  -   "Training results (2) for data slice 2."
    reg6e_713                              0x000001C4 30 r       x          -    -    -  -   "Training results (2) for data slice 3."
    phy_dll_sts0                           0x000001CC 27 r       0x00000000 -    -    -  -   "Slave DLL results for data slice 0."
    phy_dll_sts1                           0x000001D0 27 r       0x00000000 -    -    -  -   "Slave DLL results for data slice 1."
    phy_dll_sts2                           0x000001D4 27 r       0x00000000 -    -    -  -   "Slave DLL results for data slice 2."
    phy_dll_sts3                           0x000001D8 27 r       0x00000000 -    -    -  -   "Slave DLL results for data slice 3."
    dll_lock_sts                           0x000001E0 24 r       0x00F00000 -    -    -  -   "DLL Lock Status, read"
    phy_ctrl_sts                           0x000001E4 30 r       x          -    -    -  -   "PHY Control status, read"
    phy_ctrl_sts_reg2                      0x000001E8 27 r       0x00000013 -    -    -  -   "PHY Control status (2), read"
    axi_id                                 0x00000200 26 r       0x00153042 -    -    -  -   "ID and revision information page_mask 0x00000204 32 rw 0x00000000 Page mask"
    axi_priority_wr_port0                  0x00000208 20 mixed   0x000803FF -    -    -  -   "AXI Priority control for write port 0."
    axi_priority_wr_port1                  0x0000020C 20 mixed   0x000803FF -    -    -  -   "AXI Priority control for write port 1."
    axi_priority_wr_port2                  0x00000210 20 mixed   0x000803FF -    -    -  -   "AXI Priority control for write port 2."
    axi_priority_wr_port3                  0x00000214 20 mixed   0x000803FF -    -    -  -   "AXI Priority control for write port 3."
    axi_priority_rd_port0                  0x00000218 20 mixed   0x000003FF -    -    -  -   "AXI Priority control for read port 0."
    axi_priority_rd_port1                  0x0000021C 20 mixed   0x000003FF -    -    -  -   "AXI Priority control for read port 1."
    axi_priority_rd_port2                  0x00000220 20 mixed   0x000003FF -    -    -  -   "AXI Priority control for read port 2."
    axi_priority_rd_port3                  0x00000224 20 mixed   0x000003FF -    -    -  -   "AXI Priority control for read port 3."
    excl_access_cfg0                       0x00000294 18 rw      0x00000000 -    -    -  -   "Exclusive access configuration for port 0."
    excl_access_cfg1                       0x00000298 18 rw      0x00000000 -    -    -  -   "Exclusive access configuration for port 1."
    excl_access_cfg2                       0x0000029C 18 rw      0x00000000 -    -    -  -   "Exclusive access configuration for port 2."
    excl_access_cfg3                       0x000002A0 18 rw      0x00000000 -    -    -  -   "Exclusive access configuration for port 3."
    mode_reg_read                          0x000002A4 32 r       0x00000000 -    -    -  -   "Mode register read data"
    lpddr_ctrl0                            0x000002A8 12 rw      0x00000000 -    -    -  -   "LPDDR2 Control 0"
    lpddr_ctrl1                            0x000002AC 32 rw      0x00000000 -    -    -  -   "LPDDR2 Control 1"
    lpddr_ctrl2                            0x000002B0 22 rw      0x003C0015 -    -    -  -   "LPDDR2 Control 2"
    lpddr_ctrl3                            0x000002B4 18 rw      0x00000601 -    -    -  -   "LPDDR2 Control 3"
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {($raccess != "rw") || ($raccess != "w") || ($raccess != "r")} {
    set raccess "rw"
  }
  if {$reset == "x"} {
    set reset 0x00000000
  }
  if {$rsize != "32"} {
      set rsize 32
#      puts"Register $rname is not 32-bits ignored"
#      continue
  }

  set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
  } else {
    set command "${command} -readfunction $readFunc"
  }
  
  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
  } else {
    set command "${command} -writefunction $writeFunc"
  }

  if { $writeMask != "-" } {
    set command "${command} -writemask $writeMask"
  }

  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
    }
  }
  
  imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $reset
}
 
