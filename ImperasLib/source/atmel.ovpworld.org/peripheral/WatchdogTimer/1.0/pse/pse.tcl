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
set name    WatchdogTimer
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version

iadddocumentation -name Description -text "WD: Watchdog
The Watchdog is built around a 16-bit counter and is used to prevent system lock-up if the software
becomes trapped in a deadlock. It can generate an internal reset or interrupt, or assert an
active level on the dedicated pin NWDOVF. All programming registers are password-protected to prevent unintentional programming.
for more information visit http://www.atmel.com/products/at91"

iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

imodeladdbusslaveport -name bp1 -mustbeconnected -size 0x4000
imodeladdaddressblock -name REG -port bp1 -size 0x4000 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name IRQ -type output

set registers {
  WD_OMR 0x00 rw 0x0 - WD_OMR_wcb
  WD_CMR 0x00 rw 0x0 - WD_CMR_wcb
  WD_CR  0x00 w  0x0 - WD_CR_wcb
  WD_SR  0x00 r  0x0 - -
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
# WD_OMR
#
imodeladdfield -mmregister bp1/REG/WD_OMR -name OKEY  -bitoffset 4 -width 12
imodeladdfield -mmregister bp1/REG/WD_OMR -name EXTEN -bitoffset 3 -width 1
imodeladdfield -mmregister bp1/REG/WD_OMR -name IRQEN -bitoffset 2 -width 1
imodeladdfield -mmregister bp1/REG/WD_OMR -name RSTEN -bitoffset 1 -width 1
imodeladdfield -mmregister bp1/REG/WD_OMR -name WDEN  -bitoffset 0 -width 1

#
# WD_CMR
#
imodeladdfield -mmregister bp1/REG/WD_CMR -name CKEY   -bitoffset 7 -width 9
imodeladdfield -mmregister bp1/REG/WD_CMR -name HPCV   -bitoffset 2 -width 4
imodeladdfield -mmregister bp1/REG/WD_CMR -name WDCLKS -bitoffset 0 -width 2

#
# WD_CR
#
imodeladdfield -mmregister bp1/REG/WD_CR -name RSTKEY -bitoffset 0 -width 16

#
# WD_SR
#
imodeladdfield -mmregister bp1/REG/WD_SR -name WDOVF -bitoffset 0 -width 1
