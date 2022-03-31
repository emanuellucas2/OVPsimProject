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
set name    bcu
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas BCU Bus Control Unit"
iadddocumentation -name Limitations -text "Register View Model Only"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# Output Signals
#
# imodeladdnetport -name ${output} -type output

#
# Input Signals
#
# imodeladdnetport -name ${input} -type input -updatefunction ${inputCB}

#
# Slave port
#
imodeladdbusslaveport -name BCUP0 -size 16

#
# Registers
#
imodeladdaddressblock -name reg0 -port BCUP0 -size 10 -offset  0 -width 16
imodeladdaddressblock -name reg1 -port BCUP0 -size  1 -offset 15 -width  8

imodeladdmmregister -addressblock BCUP0/reg0 -name CSC0 -width 16 -offset 0 -access rw -writefunction writeCSCO
imodeladdreset -mmregister BCUP0/reg0/CSC0 -name IRESET -value 0x2C11
imodeladdfield -mmregister BCUP0/reg0/CSC0 -name CS0 -bitoffset  0 -width 4
imodeladdfield -mmregister BCUP0/reg0/CSC0 -name CS1 -bitoffset  4 -width 4
imodeladdfield -mmregister BCUP0/reg0/CSC0 -name CS2 -bitoffset  8 -width 4
imodeladdfield -mmregister BCUP0/reg0/CSC0 -name CS3 -bitoffset 12 -width 4

imodeladdmmregister -addressblock BCUP0/reg0 -name CSC1 -width 16 -offset 2 -access rw -writefunction writeCSC1
imodeladdreset -mmregister BCUP0/reg0/CSC1 -name IRESET -value 0x2C11
imodeladdfield -mmregister BCUP0/reg0/CSC1 -name CS7 -bitoffset  0 -width 4
imodeladdfield -mmregister BCUP0/reg0/CSC1 -name CS6 -bitoffset  4 -width 4
imodeladdfield -mmregister BCUP0/reg0/CSC1 -name CS5 -bitoffset  8 -width 4
imodeladdfield -mmregister BCUP0/reg0/CSC1 -name CS4 -bitoffset 12 -width 4

imodeladdmmregister -addressblock BCUP0/reg0 -name BPC -width 16 -offset  4 -access rw -writefunction writeBPC -writemask 0xbfff
imodeladdreset -mmregister BCUP0/reg0/BPC -name IRESET -value 0x0000

imodeladdmmregister -addressblock BCUP0/reg0 -name BSC -width 16 -offset  6 -access rw -writefunction writeBSC
imodeladdreset -mmregister BCUP0/reg0/BSC -name IRESET -value 0xAAAA
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS0 -bitoffset  0 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS1 -bitoffset  2 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS2 -bitoffset  4 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS3 -bitoffset  6 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS4 -bitoffset  8 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS5 -bitoffset 10 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS6 -bitoffset 12 -width 2
imodeladdfield -mmregister BCUP0/reg0/BSC -name BS7 -bitoffset 14 -width 2

imodeladdmmregister -addressblock BCUP0/reg0 -name BEC -width 16 -offset  8 -access rw -writefunction writeBEC -writemask 0x5555
imodeladdreset -mmregister BCUP0/reg0/BEC -name IRESET -value 0x0000
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE00 -bitoffset  0 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE10 -bitoffset  2 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE20 -bitoffset  4 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE30 -bitoffset  6 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE40 -bitoffset  8 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE50 -bitoffset 10 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE60 -bitoffset 12 -width 1
imodeladdfield -mmregister BCUP0/reg0/BEC -name BE70 -bitoffset 14 -width 1

imodeladdmmregister -addressblock BCUP0/reg1 -name VSWC -width   8 -offset 0 -access rw -writefunction writeVSWC
imodeladdreset -mmregister BCUP0/reg1/VSWC -name IRESET -value 0x77
