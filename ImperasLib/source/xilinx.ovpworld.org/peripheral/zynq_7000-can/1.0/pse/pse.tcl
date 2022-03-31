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
set name    zynq_7000-can
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 CAN Registers"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers but no behavior."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    SRR             0x00000000 32 rw    0x00000000  -        -         0x0003      -  "Software Reset Register"
    MSR             0x00000004 32 rw    0x00000000  -        -         0x0007      -  "Mode Select Register"
    BRPR            0x00000008 32 rw    0x00000000  -        -         0x00ff      -  "Baud Rate Prescaler Register"
    BTR             0x0000000C 32 rw    0x00000000  -        -         0x01ff      -  "Bit Timing Register"
    ECR             0x00000010 32 r     0x00000000  -        -         -           -  "Error Counter Register"
    ESR             0x00000014 32 rw    0x00000000  -        -         0x001f      -  "Error Status Register"
    SR              0x00000018 32 rw    0x00000001  -        -         0x0fff      -  "Status Register"
    ISR             0x0000001C 32 rw    0x00006000  -        -         0x7fff      -  "Interrupt Status Register"
    IER             0x00000020 32 rw    0x00000000  -        -         0x7fff      -  "Interrupt Enable Register"
    ICR             0x00000024 32 rw    0x00000000  -        -         0x7fff      -  "Interrupt Clear Register"
    TCR             0x00000028 32 rw    0x00000000  -        -         0x0001      -  "Timestamp Control Register"
    WIR             0x0000002C 32 rw    0x00003F3F  -        -         0xffff      -  "Watermark Interrupt Register"
    TXFIFO_ID       0x00000030 32  w    0x00000000  -        wrFIFOId  -           -  "transmit message fifo message identifier"
    TXFIFO_DLC      0x00000034 32 rw    0x00000000  -        -         -           -  "transmit message fifo data length code"
    TXFIFO_DATA1    0x00000038 32 rw    0x00000000  -        -         -           -  "transmit message fifo data word 1"
    TXFIFO_DATA2    0x0000003C 32 rw    0x00000000  -        -         -           -  "transmit message fifo data word 2"
    TXHPB_ID        0x00000040 32  w    0x00000000  -        wrHPBId   -           -  "transmit high priority buffer message identifier"
    TXHPB_DLC       0x00000044 32 rw    0x00000000  -        -         -           -  "transmit high priority buffer data length code"
    TXHPB_DATA1     0x00000048 32 rw    0x00000000  -        -         -           -  "transmit high priority buffer data word 1"
    TXHPB_DATA2     0x0000004C 32 rw    0x00000000  -        -         -           -  "transmit high priority buffer data word 2"
    RXFIFO_ID       0x00000050 32 r     0x00000000  rxFIFOId -         -           -  "receive message fifo message identifier"
    RXFIFO_DLC      0x00000054 32 rw    0x00000000  -        -         0xf000ffff  -  "receive message fifo data length code"
    RXFIFO_DATA1    0x00000058 32 rw    0x00000000  -        -         -           -  "receive message fifo data word 1"
    RXFIFO_DATA2    0x0000005C 32 rw    0x00000000  -        -         -           -  "receive message fifo data word 2"
    AFR             0x00000060 32 rw    0x00000000  -        -         0x0007      -  "Acceptance Filter Register"
    AFMR1           0x00000064 32 rw    0x00000000  -        -         -           -  "Acceptance Filter Mask Register 1"
    AFIR1           0x00000068 32 rw    0x00000000  -        -         -           -  "Acceptance Filter ID Register 1"
    AFMR2           0x0000006C 32 rw    0x00000000  -        -         -           -  "Acceptance Filter Mask Register 2"
    AFIR2           0x00000070 32 rw    0x00000000  -        -         -           -  "Acceptance Filter ID Register 2"
    AFMR3           0x00000074 32 rw    0x00000000  -        -         -           -  "Acceptance Filter Mask Register 3"
    AFIR3           0x00000078 32 rw    0x00000000  -        -         -           -  "Acceptance Filter ID Register 3"
    AFMR4           0x0000007C 32 rw    0x00000000  -        -         -           -  "Acceptance Filter Mask Register 4"
    AFIR4           0x00000080 32 rw    0x00000000  -        -         -           -  "Acceptance Filter ID Register 4"
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
 
