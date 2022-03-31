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
set name    crc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas Cyclic Redundancy Generator"
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
imodeladdbusslaveport -name CRCP0 -size 128

#
# Registers
#
imodeladdaddressblock -name reg0 -port CRCP0 -size 72 -offset 0 -width 32

imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCIN0 -width 32 -offset  0 -access rw -writefunction writeCCRCIN0
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCD0  -width 32 -offset  4 -access rw -writefunction writeCCRCD0
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCIN1 -width 32 -offset  8 -access rw -writefunction writeCCRCIN1
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCD1  -width 32 -offset 12 -access rw -writefunction writeCCRCD1
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCIN2 -width 32 -offset 16 -access rw -writefunction writeCCRCIN2
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCD2  -width 32 -offset 20 -access rw -writefunction writeCCRCD2
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCIN3 -width 32 -offset 24 -access rw -writefunction writeCCRCIN3
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCD3  -width 32 -offset 28 -access rw -writefunction writeCCRCD3
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCIN4 -width 32 -offset 32 -access rw -writefunction writeCCRCIN4
imodeladdmmregister -addressblock CRCP0/reg0 -name CCRCD4  -width 32 -offset 36 -access rw -writefunction writeCCRCD4
imodeladdmmregister -addressblock CRCP0/reg0 -name DCRCIN  -width 32 -offset 48 -access rw -writefunction writeDCRCIN
imodeladdmmregister -addressblock CRCP0/reg0 -name DCRCD   -width 32 -offset 52 -access rw -writefunction writeDCRCD
imodeladdmmregister -addressblock CRCP0/reg0 -name CRCC    -width 32 -offset 64 -access rw -writefunction writeCRCC

imodeladdreset -mmregister CRCP0/reg0/CCRCIN0 -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCIN1 -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCIN2 -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCIN3 -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCIN4 -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCD0  -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCD1  -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCD2  -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCD3  -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CCRCD4  -name IRESET -value 0x00000000
imodeladdreset -mmregister CRCP0/reg0/CRCC    -name IRESET -value 0x00000000

imodeladdfield -mmregister CRCP0/reg0/CRCC -name POL    -bitoffset  0 -width 1
imodeladdfield -mmregister CRCP0/reg0/CRCC -name ISZ    -bitoffset  1 -width 2
imodeladdfield -mmregister CRCP0/reg0/CRCC -name CRCEN0 -bitoffset  8 -width 1
imodeladdfield -mmregister CRCP0/reg0/CRCC -name CRCEN1 -bitoffset  9 -width 1
imodeladdfield -mmregister CRCP0/reg0/CRCC -name CRCEN2 -bitoffset 10 -width 1
imodeladdfield -mmregister CRCP0/reg0/CRCC -name CRCEN3 -bitoffset 11 -width 1
imodeladdfield -mmregister CRCP0/reg0/CRCC -name CRCEN4 -bitoffset 12 -width 1
