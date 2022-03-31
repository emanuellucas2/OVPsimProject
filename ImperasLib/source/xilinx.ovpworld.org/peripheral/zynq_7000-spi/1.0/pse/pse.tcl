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
set name    zynq_7000-spi
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 SPI Registers"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers but no behavior."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

imodeladdbusmasterport  -name SPI -addresswidth 32

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    Config           0x00000000 32 rw 0x00020000 -      -      - - "SPI configuration register"
    Intr_status      0x00000004 32 rw 0x00000004 -      -      - - "SPI interrupt status register"
    Intrpt_en        0x00000008 32 rw 0x00000000 -      -      - - "Interrupt Enable register"
    Intrpt_dis       0x0000000C 32 rw 0x00000000 -      -      - - "Interrupt disable register"
    Intrpt_mask      0x00000010 32 r  0x00000000 -      -      - - "Interrupt mask register"
    En               0x00000014 32 rw 0x00000000 -      -      - - "SPI_Enable Register"
    Delay            0x00000018 32 rw 0x00000000 -      -      - - "Delay Register"
    Tx_data          0x0000001C 32  w 0x00000000 -      wrData - - "Transmit Data Register."
    Rx_data          0x00000020 32 r  0x00000000 rdData -      - - "Receive Data Register"
    Slave_Idle_count 0x00000024 32 rw 0x000000FF -      -      - - "Slave Idle Count Register"
    TX_thres         0x00000028 32 rw 0x00000001 -      -      - - "TX_FIFO Threshold Register"
    RX_thres         0x0000002C 32 rw 0x00000001 -      -      - - "RX FIFO Threshold Register"
    Mod_id           0x000000FC 32 r  0x00090106 -      -      - - "Module ID register"
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

imodeladdnetport -name intOut -type output
iadddocumentation -name Description -text "Interrupt signal"
 
