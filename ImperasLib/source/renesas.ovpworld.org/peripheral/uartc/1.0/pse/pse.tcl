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
set name    uartc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas UARTC Asynchronous Serial Interface"
iadddocumentation -name Limitations -text "No Support for pin level transitions"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# PCLKx formal container
#
foreach i {0 1 2 3 4 5 7 9} {
    imodeladdformal -name PCLK${i} -type uns32
}

#
# Signal outputs
#
foreach output {INTUCT INTUCR INTUCRE TXDC} {
	imodeladdnetport -name ${output} -type output
}

#
# Signal inputs
#
imodeladdnetport -name RXDC -type input -updatefunction P_RXDC

#
# Slave port
#
imodeladdbusslaveport -name UARTP0 -size 16

#
# Registers
#
imodeladdaddressblock -name reg0 -port UARTP0 -size 5 -offset  0 -width 8
imodeladdaddressblock -name reg1 -port UARTP0 -size 4 -offset  6 -width 16
imodeladdaddressblock -name reg2 -port UARTP0 -size 5 -offset 10 -width 8

#
# Registers
#
imodeladdmmregister -addressblock UARTP0/reg0 -name CTL0 -width 8  -offset 0 -access rw -writefunction writeCTL0
imodeladdmmregister -addressblock UARTP0/reg0 -name CTL1 -width 8  -offset 1 -access rw -writefunction writeCTL1
imodeladdmmregister -addressblock UARTP0/reg0 -name CTL2 -width 8  -offset 2 -access rw -writefunction writeCTL2
imodeladdmmregister -addressblock UARTP0/reg0 -name OPT0 -width 8  -offset 3 -access rw -writefunction writeOPT0
imodeladdmmregister -addressblock UARTP0/reg0 -name STR  -width 8  -offset 4 -access rw -writefunction writeSTR  -writemask 0x87

imodeladdmmregister -addressblock UARTP0/reg1 -name RX   -width 16 -offset 0 -access r  -readfunction readRX
imodeladdmmregister -addressblock UARTP0/reg1 -name TX   -width 16 -offset 2 -access rw -writefunction writeTX -readfunction readTX

imodeladdmmregister -addressblock UARTP0/reg2 -name OPT1 -width 8  -offset 0 -access rw -writefunction writeOPT1 -writemask 0x01
imodeladdmmregister -addressblock UARTP0/reg2 -name OPT2 -width 8  -offset 1 -access r

#
# Resets
#
imodeladdreset -mmregister UARTP0/reg0/CTL0 -name IRESET -value 0x10
imodeladdreset -mmregister UARTP0/reg0/CTL1 -name IRESET -value 0x00
imodeladdreset -mmregister UARTP0/reg0/CTL2 -name IRESET -value 0xFF
imodeladdreset -mmregister UARTP0/reg0/OPT0 -name IRESET -value 0x14
imodeladdreset -mmregister UARTP0/reg0/STR  -name IRESET -value 0x00

imodeladdreset -mmregister UARTP0/reg1/RX   -name IRESET -value 0x01FF
imodeladdreset -mmregister UARTP0/reg1/TX   -name IRESET -value 0x01FF

imodeladdreset -mmregister UARTP0/reg2/OPT1 -name IRESET -value 0x00
imodeladdreset -mmregister UARTP0/reg2/OPT2 -name IRESET -value 0x00

#
# Bit Fields
#
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name SL  -bitoffset 0 -width 1
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name CL  -bitoffset 1 -width 1
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name PS  -bitoffset 2 -width 2
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name DIR -bitoffset 4 -width 1
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name RXE -bitoffset 5 -width 1
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name TXE -bitoffset 6 -width 1
imodeladdfield -mmregister UARTP0/reg0/CTL0 -name PWR -bitoffset 7 -width 1

imodeladdfield -mmregister UARTP0/reg0/CTL1 -name CKS -bitoffset 0 -width 4

imodeladdfield -mmregister UARTP0/reg0/CTL2 -name BRS -bitoffset 0 -width 8

imodeladdfield -mmregister UARTP0/reg0/OPT0 -name RDL -bitoffset 0 -width 1
imodeladdfield -mmregister UARTP0/reg0/OPT0 -name TDL -bitoffset 1 -width 1
imodeladdfield -mmregister UARTP0/reg0/OPT0 -name SLS -bitoffset 2 -width 3
imodeladdfield -mmregister UARTP0/reg0/OPT0 -name STT -bitoffset 5 -width 1
imodeladdfield -mmregister UARTP0/reg0/OPT0 -name SRT -bitoffset 6 -width 1
imodeladdfield -mmregister UARTP0/reg0/OPT0 -name SRF -bitoffset 7 -width 1

imodeladdfield -mmregister UARTP0/reg0/STR  -name OVE -bitoffset 0 -width 1
imodeladdfield -mmregister UARTP0/reg0/STR  -name FE  -bitoffset 1 -width 1
imodeladdfield -mmregister UARTP0/reg0/STR  -name PE  -bitoffset 2 -width 1
imodeladdfield -mmregister UARTP0/reg0/STR  -name TSF -bitoffset 7 -width 1

imodeladdfield -mmregister UARTP0/reg1/RX   -name RXL -bitoffset 0 -width 8
imodeladdfield -mmregister UARTP0/reg1/RX   -name B9  -bitoffset 8 -width 1
imodeladdfield -mmregister UARTP0/reg1/TX   -name TXL -bitoffset 0 -width 8
imodeladdfield -mmregister UARTP0/reg1/TX   -name B9  -bitoffset 8 -width 1

imodeladdfield -mmregister UARTP0/reg2/OPT1 -name EBE -bitoffset 0 -width 1

imodeladdfield -mmregister UARTP0/reg2/OPT2 -name RSF -bitoffset 0 -width 1

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

