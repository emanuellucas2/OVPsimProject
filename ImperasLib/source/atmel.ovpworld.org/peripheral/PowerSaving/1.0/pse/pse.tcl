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

#
# VLNV derived from pse.tcl location
#
set vendor  atmel.ovpworld.org
set library peripheral
set name    PowerSaving
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version

iadddocumentation -name Description -text "This model contains an accurate Register set interface.
The functionality has only been implemented to sufficiently boot uClinux
for more information visit http://www.atmel.com/products/at91"
iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

imodeladdbusslaveport -name bp1 -mustbeconnected -size 0x4000
imodeladdaddressblock -name REG -port bp1 -size 0x4000 -offset 0 -width 32

set registers {
  PS_CR   0x00 w 0x0   - PS_CR_wcb
  PS_PCER 0x00 w 0x0   - PS_PCER_wcb
  PS_PCDR 0x00 w 0x0   - PS_PCDR_wcb
  PS_PCSR 0x00 r 0x17c - -
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock bp1/REG -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc != "-" } {
    set command "${command} -readfunction $readFunc"
  }
  if { $writeFunc != "-" } {
    set command "${command} -writefunction $writeFunc"
  }
  
  eval $command

  imodeladdreset -mmregister bp1/REG/$rname -name resetNet -value $reset
}

#
# PS_CR
#
imodeladdfield -mmregister bp1/REG/PS_CR -name CPU -bitoffset 0 -width 1

#
# PS_PCER
#
imodeladdfield -mmregister bp1/REG/PS_PCER -name PIO -bitoffset 8 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCER -name TC2 -bitoffset 6 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCER -name TC1 -bitoffset 5 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCER -name TC0 -bitoffset 4 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCER -name US1 -bitoffset 3 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCER -name US0 -bitoffset 2 -width 1

#
# PS_PCDR
#
imodeladdfield -mmregister bp1/REG/PS_PCDR -name PIO -bitoffset 8 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCDR -name TC2 -bitoffset 6 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCDR -name TC1 -bitoffset 5 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCDR -name TC0 -bitoffset 4 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCDR -name US1 -bitoffset 3 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCDR -name US0 -bitoffset 2 -width 1

#
# PS_PCSR
#
imodeladdfield -mmregister bp1/REG/PS_PCSR -name PIO -bitoffset 8 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCSR -name TC2 -bitoffset 6 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCSR -name TC1 -bitoffset 5 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCSR -name TC0 -bitoffset 4 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCSR -name US1 -bitoffset 3 -width 1
imodeladdfield -mmregister bp1/REG/PS_PCSR -name US0 -bitoffset 2 -width 1
