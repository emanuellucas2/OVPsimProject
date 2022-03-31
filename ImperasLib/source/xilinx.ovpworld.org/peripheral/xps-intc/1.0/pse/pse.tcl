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
set name    xps-intc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Microblaze LogiCORE IP XPS Interrupt Controller"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements all of the required behavior sufficient to boot Linux"

iadddocumentation -name Reference -text "DS572 April 19, 2010 v2.01a"

imodeladdbusslaveport  -name plb -mustbeconnected -size 0x20
imodeladdaddressblock  -name REG -port plb -size 0x20 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name Irq -type output
imodeladdnetport -name Intr%u -updatefunction WriteIntr -updatefunctionargument _index -type input -loarray 0 -hiarray 31

set registers {
  ISR 0x00 rw 0x00000000 auto auto
  IPR 0x04 r  0x00000000 auto -
  IER 0x08 rw 0x00000000 auto auto
  IAR 0x0c w  0x00000000 -    auto
  SIE 0x10 w  0x00000000 -    auto
  CIE 0x14 w  0x00000000 -    auto
  IVR 0x18 r  0xFFFFFFFF auto -
  MER 0x1c rw 0x00000000 auto auto
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock plb/REG -name $rname -width 32 -offset $roffset -access $raccess"
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
# ISR, IPR, IER, IAR, SIE, CIE, IVR
#
for {set i 0} {$i <= 31} {incr i} {
    imodeladdfield -mmregister plb/REG/ISR -name INT${i} -bitoffset ${i} -width 1
    imodeladdfield -mmregister plb/REG/IPR -name INT${i} -bitoffset ${i} -width 1
    imodeladdfield -mmregister plb/REG/IER -name INT${i} -bitoffset ${i} -width 1
    imodeladdfield -mmregister plb/REG/IAR -name INT${i} -bitoffset ${i} -width 1
    imodeladdfield -mmregister plb/REG/SIE -name INT${i} -bitoffset ${i} -width 1
    imodeladdfield -mmregister plb/REG/CIE -name INT${i} -bitoffset ${i} -width 1
}

#
# MER
#
imodeladdfield -mmregister plb/REG/MER -name ME  -bitoffset 0 -width 1
imodeladdfield -mmregister plb/REG/MER -name HIE -bitoffset 1 -width 1

set defaultEndian "big"
imodeladdformal -name endian -type string -defaultValue $defaultEndian
iadddocumentation  \
               -name Description  \
               -text "Specify the endian of the processor interface (default $defaultEndian endian)"
 
