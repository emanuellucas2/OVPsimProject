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

set vendor  nxp.ovpworld.org
set library peripheral
set name    iMX6_SDHC
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor \
    -extensionfile model
    

iadddocumentation -name Description -text "NXP i.MX6 SDHC Ultra Secured Digital Host Controller"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "Not Complete. Register interface only."
iadddocumentation -name Limitations -text "Support only for memory card features."

iadddocumentation -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

#
# master port
#
imodeladdbusmasterport -name mport -addresswidth 32 -mustbeconnected
iadddocumentation -name Description -text "Master port for DMA accesses"
    
#
# slave port
#
set port  bport1
set block ab
set size  0x4000
set width 32

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
iadddocumentation -name Description -text "Slave port for register and data accesses"
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width ${width}

#
# Registers
#
set registers {
    uSDHC_DS_ADDR              0x0000 rw 0x00000000 0xfffffffe -    -    "DMA System Address"
                {   BLKCNT  16 16 "Blocks Count For Current Transfer"
                    BLKSIZE  0 13 "Transfer Block Size"
                }
    uSDHC_BLK_ATT              0x0004 rw 0x00000000 0xffff1fff -    -    "Block Attributes"              -
    uSDHC_CMD_ARG              0x0008 rw 0x00000000 -          -    auto "Command Argument"              -
    uSDHC_CMD_XFR_TYP          0x000C rw 0x00000000 0x3ffb0000 -    auto "Command Transfer Type"
                {   CMDINX 24 6 "Command Index"
                    CMDTYP 22 2 "Command Type"
                    DPSEL  21 1 "Data Present Select"
                    CICEN  20 1 "Command Index Check Enable"
                    CCCEN  19 1 "Command CRC Check Enable"
                    RSPTYP 16 2 "Response Type Select"
                }
    uSDHC_CMD_RSP0             0x0010 r  0x00000000 -          -    -    "Command Response0"             -
    uSDHC_CMD_RSP1             0x0014 r  0x00000000 -          -    -    "Command Response1"             -
    uSDHC_CMD_RSP2             0x0018 r  0x00000000 -          -    -    "Command Response2"             -
    uSDHC_CMD_RSP3             0x001C r  0x00000000 -          -    -    "Command Response3"             -
    uSDHC_DATA_BUFF_ACC_PORT   0x0020 rw 0x00000000 -          -    -    "Data Buffer Access Port"       -
    uSDHC_PRES_STATE           0x0024 r  0x00000000 -          -    -    "Present State"
                {   DLSL        24 8 "Data Line Signal Level"
                    CLSL        23 1 "CMD Line Signal Level"
                    WPSPL       19 1 "Write Protect Switch Pin Level"
                    CDPL        18 1 "Card Detect Pin Level"
                    CINST       16 1 "Card Inserted"
                    RTR         12 1 "Re-Tuning Request (only for SD3.0 SDR104 mode)"
                    BREN        11 1 "Buffer Read Enable"
                    BWEN        10 1 "Buffer Write Enable"
                    RTA          9 1 "Read Transfer Active"
                    WTA          8 1 "Write Transfer Active"
                    SDOFF        7 1 "SD Clock Gated Off Internally"
                    PEROFF       6 1 "IPG_PERCLK Gated Off Internally"
                    HCKOFF       5 1 "HCLK Gated Off Internally"
                    IPGOFF       4 1 "IPG_CLK Gated Off Internally"
                    SDSTB        3 1 "SD Clock Stable"
                    DLA          2 1 "Data Line Active"
                    CDIHB        1 1 "Command Inhibit (DATA)"
                    CIHB         0 1 "Command Inhibit (CMD)"
                }
    uSDHC_PROT_CTRL            0x0028 rw 0x08800020 0x7f1f03ff -    auto "Protocol Control"
                {
                    NON_EXACT_BLK_RD    30 1 "Current block read is non-exact block read. It is only used for SDIO."
                    BURST_LEN_EN        27 3 "BURST length enable for INCR, INCR4 / INCR8 / INCR16, INCR4-WRAP / INCR8-WRAP / INCR16-WRAP"
                    WECRM               26 1 "Wakeup Event Enable On SD Card Removal"
                    WECINS              25 1 "Wakeup Event Enable On SD Card Insertion"
                    WECINT              24 1 "Wakeup Event Enable On Card Interrupt"
                    RD_DONE_NO_8CLK     20 1 "Read done no 8 clock"
                    IABG                19 1 "Interrupt At Block Gap"
                    RWCTL               18 1 "Read Wait Control"
                    CREQ                17 1 "Continue Request"
                    SABGREQ             16 1 "Stop At Block Gap Request"
                    DMASEL               8 2 "DMA Select"
                    CDSS                 7 1 "Card Detect Signal Selection"
                    CDTL                 6 1 "Card Detect Test Level"
                    EMODE                4 2 "Endian Mode"
                    D3CD                 3 1 "DATA3 as Card Detection Pin"
                    DTW                  1 2 "Data Transfer Width"
                    LCTL                 0 1 "LED Control"
                }
    uSDHC_SYS_CTRL             0x002C rw 0x0080800F 0x0f8ffff0 auto auto "System Control"                 
                {   INITA     27 1 "Initialization Active"
                    RSTD      26 1 "Software Reset For DATA Line"
                    RSTC      25 1 "Software Reset For CMD Line"
                    RSTA      24 1 "Software Reset For ALL"
                    IPP_RST_N 23 1 "hardware reset of the card"
                    DTOCV     16 4 "Data Timeout Counter Value"
                    SDCLKFS    8 7 "SDCLK Frequency Select"
                    DVS        4 3 "Divisor"
                }
    uSDHC_INT_STATUS           0x0030  w 0x00000000 0x157f51ff -    auto "Interrupt Status"
                {   
                    DMAE    28 1 "DMA Error"
                    TNE     26 1 "Tuning Error: (only for SD3.0 SDR104 mode)"
                    AC12E   24 1 "Auto CMD12 Error"
                    DEBE    22 1 "Data End Bit Error"
                    DCE     21 1 "Data CRC Error"
                    DTOE    20 1 "Data Timeout Error"
                    CIE     19 1 "Command Index Error"
                    CEBE    18 1 "Command End Bit Error"
                    CCE     17 1 "Command CRC Error"
                    CTOE    16 1 "Command Timeout Error"
                    TP      14 1 "Tuning Pass:(only for SD3.0 SDR104 mode)"
                    RTE     12 1 "Re-Tuning Event: (only for SD3.0 SDR104 mode)"
                    CINT     8 1 "Card Interrupt"
                    CRM      7 1 "Card Removal"
                    CINS     6 1 "Card Insertion"
                    BRR      5 1 "Buffer Read Ready"
                    BWR      4 1 "Buffer Write Ready"
                    DINT     3 1 "DMA Interrupt"
                    BGE      2 1 "Block Gap Event"
                    TC       1 1 "Transfer Complete"
                    CC       0 1 "Command Complete"
                }
    uSDHC_INT_STATUS_EN        0x0034 rw 0x00000000 0x157f51ff -    auto "Interrupt Status Enable"
                {   
                    DMAESEN  28 1 "DMA Error"
                    TNESEN   26 1 "Tuning Error: (only for SD3.0 SDR104 mode)"
                    AC12ESEN 24 1 "Auto CMD12 Error"
                    DEBESEN  22 1 "Data End Bit Error"
                    DCESEN   21 1 "Data CRC Error"
                    DTOESEN  20 1 "Data Timeout Error"
                    CIESEN   19 1 "Command Index Error"
                    CEBESEN  18 1 "Command End Bit Error"
                    CCESEN   17 1 "Command CRC Error"
                    CTOESEN  16 1 "Command Timeout Error"
                    TPSEN    14 1 "Tuning Pass:(only for SD3.0 SDR104 mode)"
                    RTESEN   12 1 "Re-Tuning Event: (only for SD3.0 SDR104 mode)"
                    CINTSEN   8 1 "Card Interrupt"
                    CRMSEN    7 1 "Card Removal"
                    CINSSEN   6 1 "Card Insertion"
                    BRRSEN    5 1 "Buffer Read Ready"
                    BWRSEN    4 1 "Buffer Write Ready"
                    DINTSEN   3 1 "DMA Interrupt"
                    BGESEN    2 1 "Block Gap Event"
                    TCSEN     1 1 "Transfer Complete"
                    CCSEN     0 1 "Command Complete"
                }
    uSDHC_INT_SIGNAL_EN        0x0038 rw 0x00000000 0x157f51ff -    auto "Interrupt Signal Enable"
                {   
                    DMAEIEN  28 1 "DMA Error"
                    TNEIEN   26 1 "Tuning Error: (only for SD3.0 SDR104 mode)"
                    AC12EIEN 24 1 "Auto CMD12 Error"
                    DEBEIEN  22 1 "Data End Bit Error"
                    DCEIEN   21 1 "Data CRC Error"
                    DTOEIEN  20 1 "Data Timeout Error"
                    CIEIEN   19 1 "Command Index Error"
                    CEBEIEN  18 1 "Command End Bit Error"
                    CCEIEN   17 1 "Command CRC Error"
                    CTOEIEN  16 1 "Command Timeout Error"
                    TPIEN    14 1 "Tuning Pass:(only for SD3.0 SDR104 mode)"
                    RTEIEN   12 1 "Re-Tuning Event: (only for SD3.0 SDR104 mode)"
                    CINTIEN   8 1 "Card Interrupt"
                    CRMIEN    7 1 "Card Removal"
                    CINSIEN   6 1 "Card Insertion"
                    BRRIEN    5 1 "Buffer Read Ready"
                    BWRIEN    4 1 "Buffer Write Ready"
                    DINTIEN   3 1 "DMA Interrupt"
                    BGEIEN    2 1 "Block Gap Event"
                    TCIEN     1 1 "Transfer Complete"
                    CCIEN     0 1 "Command Complete"
                }
    uSDHC_AUTOCMD12_ERR_STATUS 0x003C r  0x00000000 -         -    -    "Auto CMD12 Error Status"
                {
                    CNIBAC12E 7 1 "Command Not Issued By Auto CMD12 Error"
                    AC12IE    4 1 "Auto CMD12/23 Index Error"
                    AC12CE    3 1 "Auto CMD12/23 CRC Error"
                    AC12EBE   2 1 "Auto CMD12/23 End Bit Error"
                    AC12TOE   1 1 "Auto CMD12/23 Timeout Error"
                    AC12NE    0 1 "Auto CMD12 Not Executed"
                }
    uSDHC_HOST_CTRL_CAP        0x0040 r  0x07F30000 -          -    -    "Host Controller Capabilities"
                {   VS18    26 1 "Voltage Support 1.8 V"
                    VS30    25 1 "Voltage Support 3.0 V"
                    VS33    24 1 "Voltage Support 3.3V"
                    SRS     23 1 "Suspend / Resume Support"
                    DMAS    22 1 "DMA Support"
                    HSS     21 1 "High Speed Support"
                    ADMAS   20 1 "ADMA Support (Advanced DMA Support)"
                    MBL     16 3 "Max Block Length"
                }
    uSDHC_WTMK_LVL             0x0044 rw 0x08100810 0x1fff1fff -    auto "Watermark Level"
                {   WR_BRST_LEN 24 5 "Write Burst Length 1"
                    WR_WML      16 8 "Write Watermark Level"
                    RD_BRST_LEN  8 5 "Read Burst Length 2"
                    RD_WML       0 8 "Read Watermark Level"
                }
    uSDHC_MIX_CTRL             0x0048 rw 0x80000000 0x1e0000ff -    -    "Mixer Control"
                {   FBCLK_SEL    25 1 "Feedback Clock Source Selection (Only used for SD3.0, SDR104 mode)"
                    AUTO_TUNE_EN 24 1 "Auto Tuning Enable (Only used for SD3.0, SDR104 mode)"
                    SMP_CLK_SEL  23 1 "Tuned clock or Fixed clock is used to sample data / cmd (Only used for SD3.0, SDR104 mode)"
                    EXE_TUNE     22 1 "Execute Tuning: (Only used for SD3.0, SDR104 mode)"
                    AC23EN        7 1 "Auto CMD23 Enable"
                    NIBBLE_POS    6 1 "In DDR 4-bit mode nibble position indictation"
                    MSBSEL        5 1 "Multi / Single Block Select"
                    DTDSEL        4 1 "Data Transfer Direction Select"
                    DDR_EN        3 1 "Dual Data Rate mode selection"
                    AC12EN        2 1 "Auto CMD12 Enable"
                    BCEN          1 1 "Block Count Enable"
                    DMAEN         0 1 "DMA Enable"
                }
    uSDHC_FORCE_EVENT          0x0050  w 0x00000000 0x957f009f -    auto "Force Event"
                {   FEVTCINT       31 1 "Force Event Card Interrupt"
                    FEVTDMAE       28 1 "Force Event DMA Error"
                    FEVTTNE        26 1 "Force Tuning Error"
                    FEVTAC12E      24 1 "Force Event Auto Command 12 Error"
                    FEVTDEBE       22 1 "Force Event Data End Bit Error"
                    FEVTDCE        21 1 "Force Event Data CRC Error"
                    FEVTDTOE       20 1 "Force Event Data Time Out Error"
                    FEVTCIE        19 1 "Force Event Command Index Error"
                    FEVTCEBE       18 1 "Force Event Command End Bit Error"
                    FEVTCCE        17 1 "Force Event Command CRC Error"
                    FEVTCTOE       16 1 "Force Event Command Time Out Error"
                    FEVTCNIBAC12E   7 1 "Force Event Command Not Executed By Auto Command 12 Error"
                    FEVTAC12IE      4 1 "Force Event Auto Command 12 Index Error"
                    FEVTAC12EBE     3 1 "Force Event Auto Command 12 End Bit Error"
                    FEVTAC12CE      2 1 "Force Event Auto Command 12 CRC Error"
                    FEVTAC12TOE     1 1 "Force Event Auto Command 12 Time Out Error"
                    FEVTAC12NE      0 1 "Force Event Auto Command 12 Not Executed"
                }
    uSDHC_ADMA_ERR_STATUS      0x0054 r  0x00000000 -          -    -    "ADMA Error Status Register"
                {   ADMADCE 3 1 "ADMA Descritor Error"
                    ADMALME 2 1 "ADMA Length Mismatch Error"
                    ADMAES  0 2 "ADMA Error State (when ADMA Error is occurred)"
                }
    uSDHC_ADMA_SYS_ADDR        0x0058 rw 0x00000000 0xfffffffe -    -    "ADMA System Address"           -
    uSDHC_DLL_CTRL             0x0060 rw 0x00000200 0xfff7ffff -    -    "DLL (Delay Line) Control"
                {   DLL_CTRL_REF_UPDATE_INT   28 4 "DLL control loop update interval"
                    DLL_CTRL_SLV_UPDATE_INT   20 8 "Slave delay line update interval"
                    DLL_CTRL_SLV_DLY_TARGET1  16 3 "Refer to DLL_CTRL_SLV_DLY_TARGET0"
                    DLL_CTRL_SLV_OVERRIDE_VAL  9 6 "When SLV_OVERRIDE = 1 This field is used to select 1 of 128 physical taps manually. A value of 0 selects tap 1, and a value of 0x7f selects tap 128."
                    DLL_CTRL_SLV_OVERRIDE      8 1 "Enable manual override for slave delay chain using SLV_OVERRIDE_VAL"
                    DLL_CTRL_GATE_UPDATE       7 1 "Prevent the DLL from updating"
                    DLL_CTRL_SLV_DLY_TARGET0   3 4 "The delay target for the uSDHC loopback read clock"
                    DLL_CTRL_SLV_FORCE_UPD     2 1 "Force the slave delay line to update to the DLL calibrated value immediately"
                    DLL_CTRL_RESET             1 1 "Force a reset on DLL"
                    DLL_CTRL_ENABLE            0 1 "Enable the DLL and delay chain"
                }
    uSDHC_DLL_STATUS           0x0064 r  0x00000000 -          -    -    "DLL Status"
                {   DLL_STS_REF_SEL     9 7 "Reference delay line select taps"
                    DLL_STS_SLV_SEL     2 7 "Slave delay line select status"
                    DLL_STS_REF_LOCK    1 1 "Reference DLL lock status"
                    DLL_STS_SLV_LOCK    0 1 "Slave delay-line lock status"
                }
    uSDHC_CLK_TUNE_CTRL_STATUS 0x0068 rw 0x00000000 0x00007fff -    -    "CLK Tuning Control and Status"
                {   PRE_ERR            31 1 "PRE error"
                    TAP_SEL_PRE        24 7 "Number of delay cells added on the feedback clock between the feedback clock and CLK_PRE"
                    TAP_SEL_OUT        20 4 "Number of delay cells added on the feedback clock between CLK_PRE and CLK_OUT"
                    TAP_SEL_POST       16 4 "Number of delay cells added on the feedback clock between CLK_OUT and CLK_POST"
                    NXT_ERR            15 1 "NXT error"
                    DLY_CELL_SET_PRE    8 7 "Number of delay cells on the feedback clock between the feedback clock and CLK_PRE"
                    DLY_CELL_SET_OUT    4 3 "Number of delay cells on the feedback clock between CLK_PRE and CLK_OUT"
                    DLY_CELL_SET_POST   0 3 "Number of delay cells on the feedback clock between CLK_OUT and CLK_POST"
                }
    uSDHC_VEND_SPEC            0x00C0 rw 0x20007809 0x8000f9ff -    -    "Vendor Specific Register"
                {   CMD_BYTE_EN        31 1 "Byte access Enable"
                    INT_ST_VAL         16 8 "Internal State Value"
                    CRC_CHK_DIS        15 1 "CRC Check Disable"
                    CARD_CLK_SOFT_EN   14 1 "Card Clock Software Enable"
                    IPG_PERCLK_SOFT_EN 13 1 "IPG_PERCLK Software Enable"
                    HCLK_SOFT_EN       12 1 "AHB Clock Software Enable"
                    IPG_CLK_SOFT_EN    11 1 "IPG_CLK Software Enable"
                    FRC_SDCLK_ON        8 1 "Force CLK output active"
                    CLKONJ_IN_ABORT     7 1 "Only for debug. Force CLK output active when sending Abort command"
                    WP_POL              6 1 "Only for debug. Polarity of the WP pin"
                    CD_POL              5 1 "Only for debug.Polarity of the CD_B pin"
                    DAT3_CD_POL         4 1 "Only for debug.Polarity of DATA3 pin when it is used as card detection"
                    AC12_WR_CHKBUSY_EN  3 1 "Check busy enable after auto CMD12 for write data packet"
                    CONFLICT_CHK_EN     2 1 "Conflict check enable"
                    VSELECT             1 1 "Voltage Selection"
                    EXT_DMA_EN          0 1 "External DMA Request Enable"
                }
    uSDHC_MMC_BOOT             0x00C4 rw 0x00000000 0xffff1fff -    -    "MMC Boot Register"
                {
                    BOOT_BLK_CNT        16 16 "Stop At Block Gap value of automatic mode"
                    DISABLE_TIME_OUT     8  1 "Disable Time Out"
                    AUTO_SABG_EN         7  1 "Enable auto stop at block gap function"
                    BOOT_EN              6  1 "Boot mode enable"
                    BOOT_MODE            5  1 "Boot mode select"
                    BOOT_ACK             4  1 "Boot ACK mode select"
                    DTOCV_ACK            0  4 "Boot ACK time out counter value"
                }
    uSDHC_VEND_SPEC2           0x00C8 rw 0x00000006 0x000003ff -    -    "Vendor Specific 2 Register"
                {   CARD_INT_AUTO_CLR_DIS   7 1 "Disable the feature to clear the Card interrupt status bit when Card Interrupt status enable bit is cleared"
                    TUNING_CMD_EN           6 1 "Enable the auto tuning circuit to check the CMD line"
                    TUNING_1bit_EN          5 1 "Enable the auto tuning circuit to check the DATA0 only. It is used with the TUNING_8bit_EN together."
                    TUNING_8bit_EN          4 1 "Enable the auto tuning circuit to check the DATA[7:0]. It is used with the TUNING_1bit_EN together."
                    CARD_INT_D3_TEST        3 1 "Card Interrupt Detection Test"
                    SDR104_NSD_DIS          2 1 "Interrupt window after abort command is sent."
                    SDR104_OE_DIS           1 1 "CMD_OE / DATA_OE logic generation test."
                    SDR104_TIMING_DIS       0 1 "Timeout counter test."
                }
}
set next 0
foreach {rname roffset raccess reset writeMask readFunc writeFunc description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  # Set default callbacks where no register defined (assumes register defintion ordered)
  if {$roffset != $next} {
      set extent [expr $roffset-$next]
      imodeladdlocalmemory -name buffer$next -addressblock ${port}/${block} -offset $next -size $extent \
                           -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead
  }
  set next [expr $roffset+($width/8)]

  set command "imodeladdmmregister -addressblock $port/$block -name $rname -width $width -offset $roffset -access $raccess"
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
    foreach { n o w d } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        if { $d != "-" } {
            iadddocumentation  -handle $port/$block/$rname -name Description -text $d
        }
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}

#
# net ports
#
imodeladdnetport  -name interrupt -type output
iadddocumentation -name Description  -text "Interrupt Output"

# SD Card
imodeladdnetport  -name CD -type input
iadddocumentation -name Description  -text "SD Card Detect"
imodeladdnetport  -name WP -type input
iadddocumentation -name Description  -text "SD Card Write Protect"
imodeladdnetport  -name LCTL -type output
iadddocumentation -name Description  -text "SD Card Interface busy LED drive"



imodeladdformal    -name SD_DRIVE       -type string
iadddocumentation  -name Description    -text "The name of the Image file used for the SD Drive"
imodeladdformal    -name SD_DRIVE_DELTA -type bool
iadddocumentation  -name Description    -text "If present the SD Drive uses delta writes"
                     
imodeladdnetport   -name reset -type input -updatefunction resetFunction