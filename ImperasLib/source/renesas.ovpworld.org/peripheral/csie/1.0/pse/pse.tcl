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
set name    csie
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas CSIE Enhanced Queued Clocked Serial Interface"
iadddocumentation -name Limitations -text "Register View Model Only"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# PCLKx formal container
#
imodeladdformal -name PCLK0 -type uns32

#
# Signal outputs
#
foreach pin {INTCEOF INTCEC SOE SCSE0 SCSE1 SCSE2 SCSE3 SCSE4 SCSE5 SCSE6 SCSE7} {
  imodeladdnetport -name ${pin} -type output
}

#
# Signal inputs
#
foreach pin {SIE} {
  imodeladdnetport -name ${pin} -type input -updatefunction P_${pin}
}

#
# Signal inout
#
imodeladdnetport -name SCKE -type inout -updatefunction P_SCKE

#
# Slave port
#
imodeladdbusslaveport -name CSIEP0 -size 32

#
# Registers
#
imodeladdaddressblock -name reg0 -port CSIEP0 -size  2 -offset  0 -width  8
imodeladdaddressblock -name reg1 -port CSIEP0 -size  6 -offset  2 -width 16
imodeladdaddressblock -name reg2 -port CSIEP0 -size  6 -offset  8 -width  8
imodeladdaddressblock -name reg3 -port CSIEP0 -size 16 -offset 16 -width 16

#
# Registers
#
imodeladdmmregister -addressblock CSIEP0/reg0 -name CTL0 -width 8  -offset 0 -access rw -writefunction writeCTL0
imodeladdmmregister -addressblock CSIEP0/reg0 -name CTL1 -width 8  -offset 0 -access rw -writefunction writeCTL1

imodeladdmmregister -addressblock CSIEP0/reg1 -name RX   -width 16 -offset 0 -access r  -readfunction  readRX
imodeladdmmregister -addressblock CSIEP0/reg1 -name CS   -width 16 -offset 2 -access rw -writefunction writeCS -writemask 0x000f
imodeladdmmregister -addressblock CSIEP0/reg1 -name TX   -width 16 -offset 4 -access rw -writefunction writeTX -readfunction readTX

imodeladdmmregister -addressblock CSIEP0/reg2 -name STR  -width 8  -offset 0 -access rw -writefunction writeSTR
imodeladdmmregister -addressblock CSIEP0/reg2 -name CTL2 -width 8  -offset 1 -access rw -writefunction writeCTL2
imodeladdmmregister -addressblock CSIEP0/reg2 -name CTL3 -width 8  -offset 4 -access rw -writefunction writeCTL3 -writemask 0x0f
imodeladdmmregister -addressblock CSIEP0/reg2 -name CTL4 -width 8  -offset 5 -access rw -writefunction writeCTL4


imodeladdmmregister -addressblock CSIEP0/reg3 -name OPT%u -width 16 -offset 0 -access rw -writefunction writeOPT -userdata _index -loarray 0 -hiarray 7

#
# Resets
#
imodeladdreset -mmregister CSIEP0/reg0/CTL0 -name IRESET -value 0x00
imodeladdreset -mmregister CSIEP0/reg0/CTL1 -name IRESET -value 0x07
imodeladdreset -mmregister CSIEP0/reg1/RX   -name IRESET -value 0x0000
imodeladdreset -mmregister CSIEP0/reg1/CS   -name IRESET -value 0xffff 
imodeladdreset -mmregister CSIEP0/reg1/TX   -name IRESET -value 0x0000
imodeladdreset -mmregister CSIEP0/reg2/STR  -name IRESET -value 0x20
imodeladdreset -mmregister CSIEP0/reg2/CTL2 -name IRESET -value 0x00
imodeladdreset -mmregister CSIEP0/reg2/CTL3 -name IRESET -value 0x00
imodeladdreset -mmregister CSIEP0/reg2/CTL4 -name IRESET -value 0x00
imodeladdreset -mmregister CSIEP0/reg3/OPT%u -name IRESET -value 0x0002


#
# Bit Fields
#
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name CSM -bitoffset 0 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name WE  -bitoffset 1 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name SIT -bitoffset 2 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name DIR -bitoffset 3 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name TMS -bitoffset 4 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name RXE -bitoffset 5 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name TXE -bitoffset 6 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL0 -name PWR -bitoffset 7 -width 1

imodeladdfield -mmregister CSIEP0/reg0/CTL1 -name CKS -bitoffset 0 -width 3
imodeladdfield -mmregister CSIEP0/reg0/CTL1 -name DAP -bitoffset 3 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL1 -name CKP -bitoffset 4 -width 1
imodeladdfield -mmregister CSIEP0/reg0/CTL1 -name MDL -bitoffset 5 -width 3

imodeladdfield -mmregister CSIEP0/reg2/CTL2 -name DL  -bitoffset 0 -width 4
imodeladdfield -mmregister CSIEP0/reg2/CTL2 -name CSL -bitoffset 4 -width 4

imodeladdfield -mmregister CSIEP0/reg2/CTL3 -name SFN -bitoffset 0 -width 4

imodeladdfield -mmregister CSIEP0/reg2/CTL4 -name MD  -bitoffset 0 -width 1
imodeladdfield -mmregister CSIEP0/reg2/CTL4 -name OPE -bitoffset 1 -width 1
imodeladdfield -mmregister CSIEP0/reg2/CTL4 -name DPA -bitoffset 2 -width 1
imodeladdfield -mmregister CSIEP0/reg2/CTL4 -name CPA -bitoffset 3 -width 1
imodeladdfield -mmregister CSIEP0/reg2/CTL4 -name CSL -bitoffset 4 -width 4

imodeladdfield -mmregister CSIEP0/reg1/CS   -name CS  -bitoffset 0 -width 4

imodeladdfield -mmregister CSIEP0/reg2/STR  -name SFP -bitoffset 0 -width 4
imodeladdfield -mmregister CSIEP0/reg2/STR  -name TSF -bitoffset 4 -width 1
imodeladdfield -mmregister CSIEP0/reg2/STR  -name EMF -bitoffset 5 -width 1
imodeladdfield -mmregister CSIEP0/reg2/STR  -name FLF -bitoffset 6 -width 1
imodeladdfield -mmregister CSIEP0/reg2/STR  -name PCT -bitoffset 7 -width 1

#
# Not bothering with bit levels on OPT
#
