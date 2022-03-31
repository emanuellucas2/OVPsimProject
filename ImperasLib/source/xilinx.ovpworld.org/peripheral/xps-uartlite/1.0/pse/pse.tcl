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
set name    xps-uartlite
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation -name Description -text "Xilinx Uart-Lite"

iadddocumentation -name Limitations -text "Register Accurate & Functional Model"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation -name Reference -text "DS573 Jun 22, 2011 v1.02.a"

imodeladdformalmacro -name  BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name  BHM_RECORD_REPLAY_FORMALS

imodeladdbusslaveport  -name plb -mustbeconnected -size 0x10
imodeladdaddressblock  -name REG -port plb -size 0x10 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name Interrupt -type output

set registers {
  RxFifo  0x00 r  0x00000000  auto -
  TxFifo  0x04 w  0x00000000  -    auto
  Stat    0x08 r  0x00000002  auto -
  Ctrl    0x0c w  0x00000000  -    auto
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
# Ctrl
#
imodeladdfield -mmregister plb/REG/Ctrl -name RstTxFifo  -bitoffset 0 -width 1
imodeladdfield -mmregister plb/REG/Ctrl -name RstRxFifo  -bitoffset 1 -width 1
imodeladdfield -mmregister plb/REG/Ctrl -name EnableIntr -bitoffset 4 -width 1

#
# Stat
#
imodeladdfield -mmregister plb/REG/Stat -name RxFifoValidData -bitoffset 0 -width 1
imodeladdfield -mmregister plb/REG/Stat -name RxFifoFull      -bitoffset 1 -width 1
imodeladdfield -mmregister plb/REG/Stat -name TxFifoEmpty     -bitoffset 2 -width 1
imodeladdfield -mmregister plb/REG/Stat -name TxFifoFull      -bitoffset 3 -width 1
imodeladdfield -mmregister plb/REG/Stat -name IntrEnabled     -bitoffset 4 -width 1
imodeladdfield -mmregister plb/REG/Stat -name OverrunError    -bitoffset 5 -width 1
imodeladdfield -mmregister plb/REG/Stat -name FrameError      -bitoffset 6 -width 1
imodeladdfield -mmregister plb/REG/Stat -name ParityError     -bitoffset 7 -width 1

set defaultEndian "big"
imodeladdformal -name endian -type string -defaultValue $defaultEndian
iadddocumentation  \
               -name Description  \
               -text "Specify the endian of the processor interface (default $defaultEndian endian)"
 
