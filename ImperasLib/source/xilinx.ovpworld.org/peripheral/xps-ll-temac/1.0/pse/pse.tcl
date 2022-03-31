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
set name    xps-ll-temac
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Microblaze LogiCORE IP XPS LL TEMAC Ethernet Core"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the registers but has no functional behavior"

iadddocumentation -name Reference -text "DS537 December 14, 2010 v2.03a"

imodeladdbusslaveport  -name plb -mustbeconnected -size 0x40
imodeladdaddressblock  -name REG -port plb -size 0x40 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name Interrupt -type output

######################################## Temporary ######################################
imodeladdlocalmemory  -name buffer -addressblock plb/REG -size 0x40 \
    -readfunction readMemCB -writefunction writeMemCB
######################################## Temporary ######################################

#set registers {
#  TCSR0 0x00 rw  0x0  auto auto
#}
set registers { }

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
# TCSR0
#
# imodeladdfield -mmregister plb/REG/TCSR0 -name MDT0  -bitoffset  0 -width 1


 
