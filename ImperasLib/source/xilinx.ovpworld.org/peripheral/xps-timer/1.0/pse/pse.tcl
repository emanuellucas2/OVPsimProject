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
set name    xps-timer
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "Microblaze LogiCORE IP XPS Timer/Counter"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "Resolution of this timer is limited to the simulation time slice (aka quantum) size"

iadddocumentation -name Reference -text "DS573 April 19, 2010 v1.02a"

set defaultFrequency 125000000
imodeladdformal -name frequency -type uns32 -defaultvalue ${defaultFrequency} -min 1 -max 1000000000
iadddocumentation -name Description  \
                  -text "Specify frequency of the counters in Hz (default ${defaultFrequency} Hz)"

imodeladdbusslaveport  -name plb -mustbeconnected -size 0x20
imodeladdaddressblock  -name REG -port plb -size 0x20 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name Interrupt -type output

set registers {
  TCSR0 0x00 rw  0x00000000  auto auto
  TLR0  0x04 rw  0x00000000  auto auto
  TCR0  0x08 r   0x00000000  auto -
  TCSR1 0x10 rw  0x00000000  auto auto
  TLR1  0x14 rw  0x00000000  auto auto
  TCR1  0x18 r   0x00000000  auto -
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock plb/REG -name $rname -width 32 -offset $roffset -access $raccess -userdata $roffset"
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

  imodeladdreset -mmregister plb/REG/$rname -name resetNet -value $reset
}

#
# TCSR0
#
imodeladdfield -mmregister plb/REG/TCSR0 -name MDT0  -bitoffset  0 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name UDT0  -bitoffset  1 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name GENT0 -bitoffset  2 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name CAPT0 -bitoffset  3 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name ARHT0 -bitoffset  4 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name LOAD0 -bitoffset  5 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name ENIT0 -bitoffset  6 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name ENT0  -bitoffset  7 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name T0INT -bitoffset  8 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name PWMA0 -bitoffset  9 -width 1
imodeladdfield -mmregister plb/REG/TCSR0 -name ENALL -bitoffset 10 -width 1

#
# TCSR1
#
imodeladdfield -mmregister plb/REG/TCSR1 -name MDT1  -bitoffset  0 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name UDT1  -bitoffset  1 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name GENT1 -bitoffset  2 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name CAPT1 -bitoffset  3 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name ARHT1 -bitoffset  4 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name LOAD1 -bitoffset  5 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name ENIT1 -bitoffset  6 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name ENT1  -bitoffset  7 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name T1INT -bitoffset  8 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name PWMA1 -bitoffset  9 -width 1
imodeladdfield -mmregister plb/REG/TCSR1 -name ENALL -bitoffset 10 -width 1

set defaultEndian "big"
imodeladdformal -name endian -type string -defaultvalue ${defaultEndian}
iadddocumentation  \
               -name Description  \
               -text "Specify the endian of the processor interface (default ${defaultEndian} endian)"
 
