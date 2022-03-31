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

imodelnewperipheral  \
    -name        dmac \
    -vendor      ovpworld.org  \
    -library     peripheral \
    -version     1.0 \
    -constructor constructor \
    -destructor  destructor  \
    -nbyteregisters \
    -endianparam endian \
    -formalvalues \
    -extensionfile ../model

iadddocumentation -name Description -text "DMAC peripheral model"

imodeladdformal -name readNativeDataChannel -type boolean
iadddocumentation  \
            -name Description  \
            -text "Use native code for DMA operation"

imodeladdnetport -name RESET -type input
imodeladdnetport -name INTTC -type output
iadddocumentation -name Description -text "Interrupt Request"

# Master read and write ports
set mstrPrtRd "MREAD"
set mstrPrtWr "MWRITE"
imodeladdbusmasterport -name ${mstrPrtRd}  -addresswidth 32 -mustbeconnected
iadddocumentation -name Description -text "DMA Registers Master Port - Read"
imodeladdbusmasterport -name ${mstrPrtWr}  -addresswidth 32 -mustbeconnected
iadddocumentation -name Description -text "DMA Registers Master Port - Write"

set slvPrt     "DMACSP"
set slvPrtSize 0x140
# Slave port for all control registers
imodeladdbusslaveport -name ${slvPrt} -size 0x140 -mustbeconnected
iadddocumentation -name Description -text "DMA Registers Slave Port"

set adrBlk8     "ab8"
set adrBlkWidth 8
set adrBlkSize  0x40
# Address block for 8 bit control registers
imodeladdaddressblock -port ${slvPrt} -name ${adrBlk8} -width ${adrBlkWidth}  -offset 0 -size ${adrBlkSize}

# 8 bit control registers
imodeladdmmregister -addressblock ${slvPrt}/${adrBlk8} -name intStatus    -offset 0x00 -access r
imodeladdmmregister -addressblock ${slvPrt}/${adrBlk8} -name intTCstatus  -offset 0x04 -access rw -writefunction TCclearWr
imodeladdmmregister -addressblock ${slvPrt}/${adrBlk8} -name rawTCstatus  -offset 0x14 -access r
imodeladdmmregister -addressblock ${slvPrt}/${adrBlk8} -name enbldChns    -offset 0x1C -access r

imodeladdmmregister -addressblock ${slvPrt}/${adrBlk8} -name config       -offset 0x30 -access rw -writefunction configWr
imodeladdfield      -mmregister ${slvPrt}/${adrBlk8}/config -name burstSize -bitoffset 0 -width 2 -reset 0

imodeladdreset -name RESET -mmregister ${slvPrt}/${adrBlk8}/intStatus     -value 0
imodeladdreset -name RESET -mmregister ${slvPrt}/${adrBlk8}/intTCstatus   -value 0
imodeladdreset -name RESET -mmregister ${slvPrt}/${adrBlk8}/rawTCstatus   -value 0
imodeladdreset -name RESET -mmregister ${slvPrt}/${adrBlk8}/enbldChns     -value 0
imodeladdreset -name RESET -mmregister ${slvPrt}/${adrBlk8}/config        

iadddocumentation -name Description -text "internal status"       -handle ${slvPrt}/${adrBlk8}/intStatus
iadddocumentation -name Description -text "internal TC status"    -handle ${slvPrt}/${adrBlk8}/intTCstatus
iadddocumentation -name Description -text "raw TC status"         -handle ${slvPrt}/${adrBlk8}/rawTCstatus
iadddocumentation -name Description -text "enabled channels"      -handle ${slvPrt}/${adrBlk8}/enbldChns
iadddocumentation -name Description -text "configuration"         -handle ${slvPrt}/${adrBlk8}/config
iadddocumentation -name Description -text "size for each burst transfer"  -handle ${slvPrt}/${adrBlk8}/config/burstSize

# Array of 2 sets of 32 bit registers, one per DMA channel

set adrBlk32 "ab32"

imodeladdaddressblock -name ${adrBlk32}  \
          -width 32 \
          -offset 0x100 \
          -size 0x20 \
          -loarray 0 \
          -hiarray 1

imodeladdmmregister -addressblock ${slvPrt}/${adrBlk32} -name srcAddr -offset 0x0 -access rw
imodeladdmmregister -addressblock ${slvPrt}/${adrBlk32} -name dstAddr -offset 0x4 -access rw

imodeladdmmregister -addressblock ${slvPrt}/${adrBlk32} -name control -offset 0xC -access rw
imodeladdfield      -mmregister ${slvPrt}/${adrBlk32}/control -name transferSize -bitoffset 0 -width 12

imodeladdmmregister -addressblock ${slvPrt}/${adrBlk32} -name config -offset 0x10 -access rw -writefunction configChWr -userdata _addressblockindex
imodeladdfield      -mmregister ${slvPrt}/${adrBlk32}/config -name enable -bitoffset 0  -width 1
imodeladdfield      -mmregister ${slvPrt}/${adrBlk32}/config -name inten  -bitoffset 15 -width 1
imodeladdfield      -mmregister ${slvPrt}/${adrBlk32}/config -name halt   -bitoffset 18 -width 1

iadddocumentation -name Description -text "source address" -handle ${slvPrt}/${adrBlk32}/srcAddr
iadddocumentation -name Description -text "dest address"   -handle ${slvPrt}/${adrBlk32}/dstAddr
iadddocumentation -name Description -text "control"        -handle ${slvPrt}/${adrBlk32}/control
iadddocumentation -name Description -text "configuration"  -handle ${slvPrt}/${adrBlk32}/config


