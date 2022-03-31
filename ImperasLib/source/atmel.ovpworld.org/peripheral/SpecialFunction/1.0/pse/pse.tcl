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

set vendor  atmel.ovpworld.org
set library peripheral
set name    SpecialFunction
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version

iadddocumentation -name Description -text "This model contains an accurate Register set interface.
The functionality has only been implemented to sufficiently boot uClinux
The AT91FR40162SB provides registers that implement the following special functions.
 Chip Identification
 RESET Status
 Protect Mode
for more information visit http://www.atmel.com/products/at91"

iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

imodeladdbusslaveport -name bp1 -mustbeconnected -size 0x4000
imodeladdaddressblock -name REG -port bp1 -size 0x4000 -offset 0 -width 32

#
# Atmel Product Reference (SF_CIDR)
#   {armulator   0x14000040}
#	{AT91M40800  0x14080044}
#	{AT91M40800A 0x14080045}
#	{AT91R40807  0x14080746}
#	{AT91M40807  0x14080745}
#	{AT91M40008  0x44080840}

set registers {
  SF_CIDR 0x00 r  0x14000040 - -
  SF_EXID 0x04 r  0x00000000 - -
  SF_RSR  0x08 r  0x00000000 - -
  SF_RSV0 0x10 -  0x00000000 - -
  SF_RSV1 0x14 -  0x00000000 - -
  SF_PMR  0x18 rw 0x00000000 - SF_PMR_wcb
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
# SF_CIDR
#
imodeladdfield -mmregister bp1/REG/SF_CIDR  -name EXT     -bitoffset 31 -width 1
imodeladdfield -mmregister bp1/REG/SF_CIDR  -name ARCH    -bitoffset 20 -width 8
imodeladdfield -mmregister bp1/REG/SF_CIDR  -name VDSIZ   -bitoffset 16 -width 4
imodeladdfield -mmregister bp1/REG/SF_CIDR  -name NVDSIZ  -bitoffset 12 -width 4
imodeladdfield -mmregister bp1/REG/SF_CIDR  -name NVPSIZ  -bitoffset 8  -width 4
imodeladdfield -mmregister bp1/REG/SF_CIDR  -name VERSION -bitoffset 0  -width 5

#
# SF_RSR
#
imodeladdfield -mmregister bp1/REG/SF_EXID -name RESET -bitoffset 0 -width 8

#
# SF_PMR
#
imodeladdfield -mmregister bp1/REG/SF_PMR -name PMRKEY -bitoffset 16 -width 16
imodeladdfield -mmregister bp1/REG/SF_PMR -name AIC    -bitoffset  5 -width 1

