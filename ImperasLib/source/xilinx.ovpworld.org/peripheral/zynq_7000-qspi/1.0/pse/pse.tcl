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
set name    zynq_7000-qspi
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Quad-SPI Registers and incorporates Flash Memory (Spansion and Micron) for Zync zc702/zc706 boards"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers but not all flash memory accesses are supported."
iadddocumentation  \
    -name Limitations  \
    -text "The model is tested using Xilinx Example Project for R/W a QPSI memory on ZC702 platform using Polled and Interrupt driven Transfers.
    https://github.com/Xilinx/embeddedsw/tree/master/XilinxProcessorIPLib/drivers/qspips/examples"
iadddocumentation  \
    -name Limitations  \
    -text "The AXI mode of operation is not tested. There is no write protection implemented for memory access when in AXI mode."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"
iadddocumentation -name Reference -text "https://xilinx.github.io/embeddedsw.github.io/qspips/doc/html/api/index.html"

imodeladdformal -name image -type string
iadddocumentation -name Description -text "Specify a file to initialize flash memory. String of form <file>\[@<offset>\]"

imodeladdformal -name imageout -type string
iadddocumentation -name Description -text "Specify a file to write the flash memory at the end of simulation. String of form <file>\[@<offset>\]\[:<size>\]"

imodeladdformal -name flash -type string -defaultvalue "micron"
iadddocumentation -name Description -text "Specify the type of flash memory, 'spansion' or 'micron' (default)"
iadddocumentation -name Limitations -text "The Spansion Flash memory device is not tested."
iadddocumentation -name Limitations -text "The Micron flash memory device is tested using the Xilinx example program."

set portm  bpAXI
set blockm abm
set sizem  0x2000000

imodeladdbusslaveport  -name ${portm} -mustbeconnected -size ${sizem}
imodeladdaddressblock  -name ${blockm} -port ${portm} -size ${sizem} -offset 0 -width 32

imodeladdlocalmemory -name flash -addressblock ${portm}/${blockm} -size ${sizem}

set port  bpAPB
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    Config_reg              0x00000000 32 rw 0x80020000 -       wrConfig  0x8409ffff  {leg_flsh 31 1 endian 26 1 holdb_dr 19 1 man_start_com 16 1 manual_cs 15 1 pcs 10 1 ref_clk 8 1 fifo_width 6 2 baud_rate_dic 3 3 clk_ph 2 1 clk_pol 1 1 mode_sel 0 1}  "QSPI configuration register"
    Intr_status_REG         0x00000004 32 rw 0x00000004 -       wrIntStat 0x00000041  {TXUF 6 1 RXFULL 5 1 RXNEMPTY 4 1 TXFULL 3 1 TXOW 2 1 RXOVR 0 1}  "QSPI interrupt status register"
    Intrpt_en_REG           0x00000008 32 rw 0x00000000 rtnZero wrIntEn   0x0000007d  {TXUF 6 1 RXFULL 5 1 RXNEMPTY 4 1 TXFULL 3 1 TXOW 2 1 RXOVR 0 1}  "Interrupt Enable register."
    Intrpt_dis_REG          0x0000000C 32 rw 0x00000000 rtnZero wrIntDis  0x0000007d  {TXUF 6 1 RXFULL 5 1 RXNEMPTY 4 1 TXFULL 3 1 TXOW 2 1 RXOVR 0 1}  "Interrupt disable register."
    Intrpt_mask_REG         0x00000010 32 r  0x00000000 -       -         -           {TXUF 6 1 RXFULL 5 1 RXNEMPTY 4 1 TXFULL 3 1 TXOW 2 1 RXOVR 0 1}  "Interrupt mask register"
    En_REG                  0x00000014 32 rw 0x00000000 -       wrEn      0x00000001  {ENABLE 0 1}  "SPI_Enable Register"
    Delay_REG               0x00000018 32 rw 0x00000000 -       -         -           {NSS 24 8 BTWN 16 8 AFTER 8 8 INIT 0 8}  "Delay Register"
    TXD0                    0x0000001C 32 rw 0x00000000 -       txData0   -           -  "Transmit Data Register. Keyhole addresses for the Transmit data FIFO. See also TXD1-3."
    Rx_data_REG             0x00000020 32 r  0x00000000 rxData  -         -           -  "Receive Data Register"
    Slave_Idle_count_REG    0x00000024 32 rw 0x000000FF -       -         0x000000ff  {MASK 0 8}  "Slave Idle Count Register"
    TX_thres_REG            0x00000028 32 rw 0x00000001 -       -         -           -  "TX_FIFO Threshold Register"
    RX_thres_REG            0x0000002C 32 rw 0x00000001 -       -         -           -  "RX FIFO Threshold Register"
    GPIO                    0x00000030 32 rw 0x00000001 -       -         -           {WP 0 1}  "General Purpose Inputs and Outputs Register for the Quad-SPI Controller core"
    LPBK_DLY_ADJ            0x00000038 32 rw 0x00000033 -       -         -           -  "Loopback Master Clock Delay Adjustment Register"
    TXD1                    0x00000080 32 rw 0x00000000 rtnZero txData1   -           -  "Transmit Data Register. Keyhole addresses for the Transmit data FIFO."
    TXD2                    0x00000084 32 rw 0x00000000 rtnZero txData2   -           -  "Transmit Data Register. Keyhole addresses for the Transmit data FIFO."
    TXD3                    0x00000088 32 rw 0x00000000 rtnZero txData3   -           -  "Transmit Data Register. Keyhole addresses for the Transmit data FIFO."
    LQSPI_CFG               0x000000A0 32 rw 0x07a002eb -       -         -           {LQ_MODE 31 1 TWO_MEM 30 1 SEP_BUS 29 1 U_PAGE 28 1 MODE_EN 25 1 MODE_ON 24 1 MODE_BITS 16 8 DUMMY 8 3 INST 0 8}  "Configuration Register specifically for the Linear Quad-SPI Controller"
    LQSPI_STS               0x000000A4  9 rw 0x00000000 -       -         0x000000ff  {D_FSM_ERR 2 1 WR_RECVD 1 1}  "Status Register specifically for the Linear Quad-SPI Controller"
    MOD_ID                  0x000000FC 32 rw 0x01090101 -       -         -           -  "Module Identification register"
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

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

imodeladdnetport -name interrupt -type output
iadddocumentation -name Description -text "Interrupt signal"
 
