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

set vendor  renesas.ovpworld.org
set library peripheral
set name    csib
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas CSIB Clocked Serial Interface"
iadddocumentation -name Limitations -text "No Support for pin level transitions Clock selection for BRG0, BRG1 or SCKB defaults to PCLK6"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# PCLKx formal container
#
foreach i {1 2 3 4 5 6} {
    imodeladdformal -name PCLK${i} -type uns32
}

#
# Signal outputs
#
foreach pin {INTCBT INTCBR INTCBRE SOB} {
    imodeladdnetport -name ${pin} -type output
}

#
# Signal inputs
#
foreach pin {SIB SSB} {
    imodeladdnetport -name ${pin} -type input -updatefunction P_${pin}
}

#
# Signal inout
#
imodeladdnetport -name SCKB -type inout -updatefunction P_SCKB

#
# Slave port
#
imodeladdbusslaveport -name CSIBP0 -size 8

#
# Registers
#
imodeladdaddressblock -name reg0 -port CSIBP0 -size 4 -offset  0 -width 8
imodeladdaddressblock -name reg1 -port CSIBP0 -size 4 -offset  4 -width 16

#
# Registers
#
imodeladdmmregister -addressblock CSIBP0/reg0 -name CTL0  -width 8  -offset 0 -access rw -writefunction writeCTL0 -writemask 0xf7
imodeladdmmregister -addressblock CSIBP0/reg0 -name CTL1  -width 8  -offset 1 -access rw -writefunction writeCTL1 -writemask 0x1f
imodeladdmmregister -addressblock CSIBP0/reg0 -name CTL2  -width 8  -offset 2 -access rw -writefunction writeCTL2 -writemask 0x0f
imodeladdmmregister -addressblock CSIBP0/reg0 -name STR   -width 8  -offset 3 -access rw -writefunction writeSTR  -writemask 0x81

imodeladdmmregister -addressblock CSIBP0/reg1 -name RX    -width 16 -offset 0 -access r  -readfunction readRX
imodeladdmmregister -addressblock CSIBP0/reg1 -name TX    -width 16 -offset 2 -access rw -writefunction writeTX -readfunction readTX

#
# Resets
#
imodeladdreset -mmregister CSIBP0/reg0/CTL0 -name IRESET -value 0x01
imodeladdreset -mmregister CSIBP0/reg0/CTL1 -name IRESET -value 0x00
imodeladdreset -mmregister CSIBP0/reg0/CTL2 -name IRESET -value 0x00
imodeladdreset -mmregister CSIBP0/reg0/STR  -name IRESET -value 0x00

imodeladdreset -mmregister CSIBP0/reg1/RX   -name IRESET -value 0x0000
imodeladdreset -mmregister CSIBP0/reg1/TX   -name IRESET -value 0x0000

#
# Bit Fields
#
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name SCE -bitoffset 0 -width 1
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name TMS -bitoffset 1 -width 1
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name SSE -bitoffset 2 -width 1
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name DIR -bitoffset 4 -width 1
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name RXE -bitoffset 5 -width 1
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name TXE -bitoffset 6 -width 1
imodeladdfield -mmregister CSIBP0/reg0/CTL0 -name PWR -bitoffset 7 -width 1

imodeladdfield -mmregister CSIBP0/reg0/CTL1 -name CKS -bitoffset 0 -width 4

imodeladdfield -mmregister CSIBP0/reg0/CTL2 -name CL  -bitoffset 0 -width 4

imodeladdfield -mmregister CSIBP0/reg0/STR  -name OVE -bitoffset 0 -width 1
imodeladdfield -mmregister CSIBP0/reg0/STR  -name TSF -bitoffset 7 -width 1

imodeladdfield -mmregister CSIBP0/reg1/RX   -name RXL -bitoffset 0 -width 8
imodeladdfield -mmregister CSIBP0/reg1/RX   -name RXH -bitoffset 8 -width 8
imodeladdfield -mmregister CSIBP0/reg1/TX   -name TXL -bitoffset 0 -width 8
imodeladdfield -mmregister CSIBP0/reg1/TX   -name TXH -bitoffset 8 -width 8

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

