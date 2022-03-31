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
set name    axi-timer
set version 1.0

imodelnewperipheral \
    -vendor $vendor -library $library -name $name -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "Xilinx AXI Timer"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "Resolution of this timer is limited to the simulation time slice (aka quantum) size"

iadddocumentation -name Reference -text "pg079-axi-timer, Vivado Design Suite, October t, 2016"

#
# Parameters for configuration
#
set defaultFrequency 125
imodeladdformal -name frequency -type double -defaultvalue ${defaultFrequency} -min 1 -max 1000
iadddocumentation -name Description  \
                  -text "Specify frequency of the counters in MHz (default ${defaultFrequency}MHz)"

set defaultWidth 32
imodeladdformal -name width -type uns32 -defaultvalue ${defaultWidth}
iadddocumentation -name Description -text "Specify the size of the timer registers (default ${defaultWidth})"

imodeladdformal -name timer1 -type bool -defaultvalue True
iadddocumentation  -name Description -text "Enable for timer 1 (default enabled)"

#
# Bus Slave Port and slave access registers
#
imodeladdbusslaveport  -name sp -mustbeconnected -size 0x20
imodeladdaddressblock  -name ab -port sp -size 0x20 -offset 0 -width 32

imodeladdlocalmemory -name reserved0 -addressblock sp/ab -size 4 -offset 0x0c \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead
imodeladdlocalmemory -name reserved1 -addressblock sp/ab -size 4 -offset 0x1c \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

#
# Interrupt Signal Block output
#
imodeladdnetport -name Interrupt -type output

set registers {
  TCSR0 0x00 rw  0x00000000  auto auto {MDT0 0 1 UDT0 1 1 GENT0  2 1 CAPT0  3 1 ARHT0  4 1 LOAD0  5 1 ENIT0 6 1 ENT0 7 1 T0INT 8 1 PWMA0 9 1 ENALL0 10 1 CASC0 11 1}
  TLR0  0x04 rw  0x00000000  auto auto -
  TCR0  0x08 r   0x00000000  auto -    -
  TCSR1 0x10 rw  0x00000000  auto auto {MDT1 0 1 UDT1 1 1 GENT1  2 1 CAPT1  3 1 ARHT1  4 1 LOAD1  5 1 ENIT1 6 1 ENT1 7 1 T1INT 8 1 PWMA1 9 1 ENALL1 10 1}
  TLR1  0x14 rw  0x00000000  auto auto -
  TCR1  0x18 r   0x00000000  auto -    -
}


foreach {rname roffset raccess reset readFunc writeFunc bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock sp/ab -name $rname -width 32 -offset $roffset -access $raccess -userdata $roffset"
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
  
  eval $command
  if { $bits != "-" } {
    foreach { n o w } $bits {
      imodeladdfield -mmregister sp/ab/$rname -bitoffset $o -width $w -name $n
    }
  }

  imodeladdreset -mmregister sp/ab/$rname -name resetNet -value $reset
}

set defaultEndian "little"
imodeladdformal -name endian -type string -defaultvalue ${defaultEndian}
iadddocumentation  \
               -name Description  \
               -text "Specify the endian of the processor interface (default ${defaultEndian} endian)"
 
