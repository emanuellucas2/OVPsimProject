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
set name    ParallelIOController
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version

iadddocumentation -name Description -text "PIO: Parallel I/O Controller
This model contains an accurate Register set interface.
The functionality has only been implemented to sufficiently boot uClinux
The Parallel I/O Controller has 32 programmable I/O lines. Six pins are dedicated as general-purpose
I/O pins. Other I/O lines are multiplexed with an external signal of a peripheral to optimize
the use of available package pins. The PIO controller enables generation of an interrupt on input
change and insertion of a simple input glitch filter on any of the PIO pins.
for more information visit http://www.atmel.com/products/at91"

iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

imodeladdbusslaveport -name bp1 -mustbeconnected -size 0x4000
imodeladdaddressblock -name REG -port bp1 -size 0x4000 -offset 0 -width 32

#
# P I/O interface
#
imodeladdnetport -name P%u -type inout -updatefunction P_wcb -loarray 0 -hiarray 31 -updatefunctionargument _index

#
# Interrupt Signal Block output
#
imodeladdnetport -name IRQ -type output

set registers {
  PIO_PER  0x00 w 0x0  - PIO_PER_wcb
  PIO_PDR  0x04 w 0x0  - PIO_PDR_wcb
  PIO_PSR  0x08 r 0x01ffffff - -
  PIO_RSV0 0x0c -   -  - -
  PIO_OER  0x10 w 0x0  - PIO_OER_wcb
  PIO_ODR  0x14 w 0x0  - PIO_ODR_wcb
  PIO_OSR  0x18 r 0x0  - -
  PIO_RSV1 0x1c -   -  - -
  PIO_IFER 0x20 w 0x0  - PIO_IFER_wcb
  PIO_IFDR 0x24 w 0x0  - PIO_IFDR_wcb
  PIO_IFSR 0x28 r 0x0  - -
  PIO_RSV2 0x2c -   -  - -
  PIO_SODR 0x30 w 0x0  - PIO_SODR_wcb
  PIO_CODR 0x34 w 0x0  - PIO_CODR_wcb
  PIO_ODSR 0x38 r 0x0  - -
  PIO_PDSR 0x3c r 0x0  - -
  PIO_IER  0x40 w 0x0  - PIO_IER_wcb
  PIO_IDR  0x44 w 0x0  - PIO_IDR_wcb
  PIO_IMR  0x48 r 0x0  - -
  PIO_ISR  0x4c r 0x0  - -
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

