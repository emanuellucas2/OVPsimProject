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
set name    zynq_7000-devcfg
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor \
    -extensionfile model

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Platform Device Configuration Registers (devcfg)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation \
    -name Limitations \
    -text "This is mainly a register only interface model.
           It provides behavior to access the power rails using the XADC interface. The power rail data is provided by values stored in memory which can be updated externally.
           It provides the ability to lock and un-lock registers."
    
iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

imodeladdbusmasterport  -name xadc

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    CTRL                0x00000000 32 rw 0x0c006000 -           auto auto {FORCE_RST 31 1 PCFG_PROG_B 30 1 PCFG_POR_CNT_4K 29 1 PCAP_PR 27 1 PCAP_MODE 26 1 PCAP_RATE_EN 25 1 MULTIBOOT_EN 24 1 JTAG_CHAIN_DIS 23 1 PCFG_AES_FUSE 12 1 PCFG_AES_EN 9 3 SEU_EN 8 1 SEC_EN 7 1 SPNIDEN 6 1 SPIDEN 5 1 NIDEN 4 1 DBGEN 3 1 DAP_EN 0 3} "Control Register"
    LOCK                0x00000004 32 rw 0x00000000 -           auto auto {AES_FUSE_LOCK 4 1 AES_EN_LOCK 3 1 SEU_LOCK 2 1 SEC_LOCK 1 1 DBG_LOCK 0 1} "LOCK"
    CFG                 0x00000008 32 rw 0x00000508 -           auto auto -  "Configuration Register"
    INT_STS             0x0000000c 32 rw 0x00000000 -           auto auto -  "Interrupt Status Register"
    INT_MASK            0x00000010 32 rw 0xffffffff -           auto auto -  "Interrupt Mask Register"
    STATUS              0x00000014 32 rw 0x40000820 -           auto auto -  "Status Register"
    DMA_SRC_ADDR        0x00000018 32 rw 0x00000000 -           auto auto -  "DMA Source address Register"
    DMA_DST_ADDR        0x0000001C 32 rw 0x00000000 -           auto auto -  "DMA Destination address Register"
    DMA_SRC_LEN         0x00000020 32 rw 0x00000000 -           auto auto -  "DMA Source transfer Length Register"
    DMA_DEST_LEN        0x00000024 32 rw 0x00000000 -           auto auto -  "DMA Destination transfer Length Register"
    ROM_SHADOW          0x00000028 32 rw 0x00000000 -           auto auto -  "ROM_SHADOW"
    MULTIBOOT_ADDR      0x0000002C 13 rw 0x00000000 -           auto auto -  "MULTI Boot Addr Pointer Register"
    UNLOCK              0x00000034 32 rw 0x00000000 -           auto auto -  "Unlock Register. The boot ROM will unlock the DEVCI by writing 0x757BDF0D to this register."
    MCTRL               0x00000080 32 rw 0x10200000 -           auto auto -  "Miscellaneous control Register PS_VERSION=1 (v2.0 Silicon)"
    XADCIF_CFG          0x00000100 32 rw 0x00001114 0x80ff331f  auto auto {ENABLE 31 1 CFIFOTH 20 4 DFIFOTH 16 4 WEDGE 13 1 REDGE 12 1 TCKARTE 8 2 IGAP 0 5}  "XADC Interface Configuration Register"
    XADCIF_INT_STS      0x00000104 32 rw 0x00000200 0x0000003f  auto auto {CFIFO_LTH 9 1 DFIFO_GTH 8 1 OT 7 1 ALM 0 7} "XADC Interface Interrupt Status Register"
    XADCIF_INT_MASK     0x00000108 32 rw 0x3FFFFFFF 0x0000003f  auto auto {CFIFO_LTH 9 1 DFIFO_GTH 8 1 OT 7 1 ALM 0 7} "XADC Interface Interrupt Mask Register"
    XADCIF_MSTS         0x0000010C 32 r  0x00000500 -           auto -    {CFIFO_LVL 16 4 DFIFO_LVL 12 4 CFIFOF 11 1 CFIFOE 10 1 DFIFOF 9 1 DFIFOE 8 1 OT 7 1 ALM 0 6}  "XADC Interface miscellaneous Status Register"
    XADCIF_CMDFIFO      0x00000110 32  w 0x00000000 -           -    auto {CMD 26 4 ADDR 16 10 DATA 0 16}  "XADC Interface Command FIFO Register"
    XADCIF_RDFIFO       0x00000114 32 r  0x00000000 -           auto -    {                    DATA 0 16}  "XADC Interface Data FIFO Register"
    XADCIF_MCTL         0x00000118 32 rw 0x00000010 0x00000010  auto auto {RESET 4 1 }  "XADC Interface Miscellaneous Control Register"
}

foreach {rname roffset rsize raccess reset mask readFunc writeFunc bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      set rsize 32
#      puts "Register $rname is not 32-bits ignored"
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

  if { $mask != "-" } {
    set command "${command} -writemask $mask"
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

imodeladdnetport -name intOut -type output
iadddocumentation -name Description -text "Interrupt signal"

imodeladdnetport  -name xadcmux -type input -updatefunction xadcMuxSelect
iadddocumentation -name Description -text "Selects the channel for the XADC interface sample"

set defaultBoard "zc706"
imodeladdformal -name board -type string -defaultvalue ${defaultBoard}
iadddocumentation -name Description -text "The XADC interface includes default data values, access is board dependent so must be configured. Valid 'zc706' or 'zc702' (default ${defaultBoard})"

# Add initialisation file
imodeladdformal -name config -type string
iadddocumentation -name Description -text "The configuratation file defining default values and Voltage Monitor names"

# include common formals
source $env(IMPERAS_HOME)/ImperasLib/source/pmbus.ovpworld.org/modelSupport/pmbus/1.0/pse/pmbus.pse.tcl
