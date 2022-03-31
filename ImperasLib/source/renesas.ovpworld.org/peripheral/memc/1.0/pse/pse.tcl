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
set name    memc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas MEMC Bus Control Unit"
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
imodeladdbusslaveport -name MEMCP0 -size 16

#
# Registers
#
imodeladdaddressblock -name reg0 -port MEMCP0 -size 12 -offset  0 -width 16
imodeladdaddressblock -name reg1 -port MEMCP0 -size  1 -offset 15 -width  8

imodeladdmmregister -addressblock MEMCP0/reg0 -name BCT0 -width 16 -offset 0 -access rw -writefunction writeBCT0 -writemask 0x8888
imodeladdreset -mmregister MEMCP0/reg0/BCT0 -name IRESET -value 0x4444
imodeladdfield -mmregister MEMCP0/reg0/BCT0 -name ME0 -bitoffset  3 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCT0 -name ME1 -bitoffset  7 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCT0 -name ME2 -bitoffset 11 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCT0 -name ME3 -bitoffset 15 -width 1

imodeladdmmregister -addressblock MEMCP0/reg0 -name BCT1 -width 16 -offset 2 -access rw -writefunction writeBCT1 -writemask 0x8888
imodeladdreset -mmregister MEMCP0/reg0/BCT1 -name IRESET -value 0x4444
imodeladdfield -mmregister MEMCP0/reg0/BCT1 -name ME4 -bitoffset  3 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCT1 -name ME5 -bitoffset  7 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCT1 -name ME6 -bitoffset 11 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCT1 -name ME7 -bitoffset 15 -width 1

imodeladdmmregister -addressblock MEMCP0/reg0 -name DWC0 -width 16 -offset 4 -access rw -writefunction writeDWC0 -writemask 0x7777
imodeladdreset -mmregister MEMCP0/reg0/DWC0 -name IRESET -value 0x7777
imodeladdfield -mmregister MEMCP0/reg0/DWC0 -name DW0 -bitoffset  0 -width 3
imodeladdfield -mmregister MEMCP0/reg0/DWC0 -name DW1 -bitoffset  4 -width 3
imodeladdfield -mmregister MEMCP0/reg0/DWC0 -name DW2 -bitoffset  8 -width 3
imodeladdfield -mmregister MEMCP0/reg0/DWC0 -name DW3 -bitoffset 12 -width 3

imodeladdmmregister -addressblock MEMCP0/reg0 -name DWC1 -width 16 -offset 6 -access rw -writefunction writeDWC1 -writemask 0x7777
imodeladdreset -mmregister MEMCP0/reg0/DWC1 -name IRESET -value 0x7777
imodeladdfield -mmregister MEMCP0/reg0/DWC1 -name DW4 -bitoffset  0 -width 3
imodeladdfield -mmregister MEMCP0/reg0/DWC1 -name DW5 -bitoffset  4 -width 3
imodeladdfield -mmregister MEMCP0/reg0/DWC1 -name DW6 -bitoffset  8 -width 3
imodeladdfield -mmregister MEMCP0/reg0/DWC1 -name DW7 -bitoffset 12 -width 3

imodeladdmmregister -addressblock MEMCP0/reg0 -name AWC -width 16 -offset 8 -access rw -writefunction writeAWC
imodeladdreset -mmregister MEMCP0/reg0/AWC -name IRESET -value 0xFFFF
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW0 -bitoffset  0 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW0 -bitoffset  1 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW1 -bitoffset  2 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW1 -bitoffset  3 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW2 -bitoffset  4 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW2 -bitoffset  5 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW3 -bitoffset  6 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW3 -bitoffset  7 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW4 -bitoffset  8 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW4 -bitoffset  9 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW5 -bitoffset 10 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW5 -bitoffset 11 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW6 -bitoffset 12 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW6 -bitoffset 13 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name ASW7 -bitoffset 14 -width 1
imodeladdfield -mmregister MEMCP0/reg0/AWC -name AHW7 -bitoffset 15 -width 1

imodeladdmmregister -addressblock MEMCP0/reg0 -name BCC -width 16 -offset 10 -access rw -writefunction writeBCC -writemask 0xAAAA
imodeladdreset -mmregister MEMCP0/reg0/BCC -name IRESET -value 0xAAAA
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC01 -bitoffset  1 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC11 -bitoffset  3 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC21 -bitoffset  5 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC31 -bitoffset  7 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC41 -bitoffset  9 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC51 -bitoffset 11 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC61 -bitoffset 13 -width 1
imodeladdfield -mmregister MEMCP0/reg0/BCC -name BC71 -bitoffset 15 -width 1

imodeladdmmregister -addressblock MEMCP0/reg1 -name DVC -width   8 -offset 0 -access rw -writefunction writeDVC -writemask 0x81
imodeladdreset -mmregister MEMCP0/reg1/DVC -name IRESET -value 0x00
