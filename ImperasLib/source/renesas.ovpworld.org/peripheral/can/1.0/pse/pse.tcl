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

#
# This peripheral is intended for the UPD70F3610
#

set vendor  renesas.ovpworld.org
set library peripheral
set name    can
set version 1.0

imodelnewperipheral \
    -name $name -imagefile pse.pse \
    -library $library -vendor $vendor \
    -version $version -constructor constructor

iadddocumentation -name Description -text "Renesas CAN interface. This is an interface between the CAN controller register interface and a PacketNet can interface."
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "No CRC generation or checking."
iadddocumentation -name Reference   -text "V850E/PHO3 uPD70F3441, uPD70F3483: R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# Interrupt lines
#
imodeladdnetport -name INTTRX -type output
imodeladdnetport -name INTREC -type output
imodeladdnetport -name INTERR -type output
imodeladdnetport -name INTWUP -type output

#
# CAN Transceiver
#
imodeladdpacketnetport -name CAN -updatefunction canrx -maxbytes 128

#
# Global & Module Registers 0x000 - 0x066
#
imodeladdbusslaveport -name busPortGR -mustbeconnected -size 0x100
imodeladdaddressblock -port busPortGR -name GR1        -size 0x52 -offset 0x00 -width 16
imodeladdaddressblock -port busPortGR -name GR2        -size 0x02 -offset 0x52 -width 8
imodeladdaddressblock -port busPortGR -name GR3        -size 0x14 -offset 0x54 -width 16

#imodeladdbusslaveport -name busPortMD -mustbeconnected -size 0x600
#imodeladdaddressblock -port busPortMD -name MD1        -size 0x600 -offset 0x00 -width 32

#imodeladdbusslaveport -name busPortCR    -mustbeconnected -size 0x30

#imodeladdbusslaveport -name busPortMR   -mustbeconnected -size 0x300
#imodeladdbusslaveport -name busPortMDB  -mustbeconnected -size 0x100
#imodeladdbusslaveport -name busPortMDB  -mustbeconnected -size 0x100
#imodeladdbusslaveport -name busPortMDH  -mustbeconnected -size 0x1000
#imodeladdbusslaveport -name busPortMDW  -mustbeconnected -size 0x1000
#imodeladdbusslaveport -name busPortECC  -mustbeconnected -size 0x4
#imodeladdbusslaveport -name busPortGR   -mustbeconnected -size 0x200
#imodeladdbusslaveport -name busPortCR   -mustbeconnected -size 0x200
#imodeladdbusslaveport -name busPortCRW  -mustbeconnected -size 0x100

#imodeladdaddressblock -name MR  -port busPortMR  -size  0x300 -offset 0 -width 16
#imodeladdaddressblock -name ECC -port busPortECC -size    0x4 -offset 0 -width 16
#imodeladdaddressblock -name GR  -port busPortGR  -size  0x200 -offset 0 -width 16
#imodeladdaddressblock -name CR  -port busPortCR  -size  0x200 -offset 0 -width 16
#imodeladdaddressblock -name CRW -port busPortCRW -size  0x100 -offset 0 -width 32
#imodeladdaddressblock -name MDW -port busPortMDW -size 0x1000 -offset 0 -width 32
#imodeladdaddressblock -name MDH -port busPortMDH -size 0x1000 -offset 0 -width 16
#imodeladdaddressblock -name MDB -port busPortMDB -size  0x100 -offset 0 -width 8

#
# CAN Global Control Register CnGMCTRL
#
imodeladdmmregister -addressblock busPortGR/GR1 -name GMCTRL -width 16 \
    -offset 0 -access rw \
    -readfunction readGMCTRL -writefunction writeGMCTRL -viewfunction viewGMCTRL

imodeladdmmregister -addressblock busPortGR/GR1 -name GMCS -width 8 \
    -offset 0x02 -access rw \
    -readfunction readGMCS -writefunction writeGMCS -viewfunction viewGMCS

imodeladdmmregister -addressblock busPortGR/GR1 -name GMABT -width 16 \
    -offset 0x06 -access rw \
    -readfunction readGMABT -writefunction writeGMABT -viewfunction viewGMABT

imodeladdmmregister -addressblock busPortGR/GR1 -name GMABTD -width 8 \
    -offset 0x08 -access rw \
    -readfunction readGMABTD -writefunction writeGMABTD -viewfunction viewGMABTD

#
# Control & Mask registers
#
for {set i 1} {$i < 5} {incr i} {
    # mask registers
    set offset [expr 0x40 + (($i - 1) * 4)]
    imodeladdmmregister -addressblock busPortGR/GR1 -name MASK${i}L -width 16 \
        -offset ${offset} -access rw \
        -readfunction readMASKL -writefunction writeMASKL -viewfunction viewMASKL \
        -userdata ${i}
    
    set offset [expr ${offset} + 2]
    imodeladdmmregister -addressblock busPortGR/GR1 -name MASK${i}H -width 16 \
        -offset ${offset} -access rw \
        -readfunction readMASKH -writefunction writeMASKH -viewfunction viewMASKH \
        -userdata ${i}
}

imodeladdmmregister -addressblock busPortGR/GR1 -name CTRL -width 16 \
    -offset 0x50 -access rw \
    -readfunction readCTRL -writefunction writeCTRL -viewfunction viewCTRL

set offset 0
imodeladdmmregister -addressblock busPortGR/GR2 -name LEC -width 8 \
    -offset [incr offset 0] -access rw \
    -readfunction readLEC -writefunction writeLEC -viewfunction viewLEC

imodeladdmmregister -addressblock busPortGR/GR2 -name INFO -width 8 \
    -offset [incr offset 1] -access r \
    -readfunction readINFO -viewfunction viewINFO

set offset 0
imodeladdmmregister -addressblock busPortGR/GR3 -name ERC -width 16 \
    -offset [incr offset 0] -access r \
    -readfunction readERC -viewfunction viewERC

imodeladdmmregister -addressblock busPortGR/GR3 -name IE -width 16 \
    -offset [incr offset 2] -access rw \
    -readfunction readIE -writefunction writeIE -viewfunction viewIE

imodeladdmmregister -addressblock busPortGR/GR3 -name INTS -width 16 \
    -offset [incr offset 2] -access rw \
    -readfunction readINTS -writefunction writeINTS -viewfunction viewINTS

imodeladdmmregister -addressblock busPortGR/GR3 -name BRP -width 8 \
    -offset [incr offset 2] -access rw \
    -readfunction readBRP -writefunction writeBRP -viewfunction viewBRP

imodeladdmmregister -addressblock busPortGR/GR3 -name BTR -width 16 \
    -offset [incr offset 2] -access rw \
    -readfunction readBTR -writefunction writeBTR -viewfunction viewBTR

imodeladdmmregister -addressblock busPortGR/GR3 -name LIPT -width 8 \
    -offset [incr offset 2] -access r \
    -readfunction readLIPT -viewfunction viewLIPT

imodeladdmmregister -addressblock busPortGR/GR3 -name RGPT -width 16 \
    -offset [incr offset 2] -access rw \
    -readfunction readRGPT -writefunction writeRGPT -viewfunction viewRGPT

imodeladdmmregister -addressblock busPortGR/GR3 -name LOPT -width 8 \
    -offset [incr offset 2] -access r \
    -readfunction readLOPT -viewfunction viewLOPT

imodeladdmmregister -addressblock busPortGR/GR3 -name TGPT -width 16 \
    -offset [incr offset 2] -access rw \
    -readfunction readTGPT -writefunction writeTGPT -viewfunction viewTGPT

imodeladdmmregister -addressblock busPortGR/GR3 -name TS -width 16 \
    -offset [incr offset 2] -access rw \
    -readfunction readTS -writefunction writeTS -viewfunction viewTS

    
###for {set i 0} {$i < 32} {incr i} {
###    set reg16Base   [expr $i * 0x80]
###    set regIndex    [format "%02d" $i]
###
###    for {set j 0} {$j < 8} {incr j} {
###        set reg16Offset [expr $reg16Base + (4 * $j)]
###        
###        set regName MDATA${j}${regIndex}
###        set userdata [expr (${i}<<3) | ${j}]
###        imodeladdmmregister -addressblock busPortMDB/MDB -name $regName -width 8 \
###            -offset $reg16Offset -access rw \
###            -readfunction readMDATA8 -writefunction writeMDATA8 -viewfunction viewMDATA8 \
###            -userdata $userdata
###    }
###    
###    incr reg16Offset 4
###    set regName MDLC$regIndex
###    set userdata ${i}
###    imodeladdmmregister -addressblock busPortMDB/MDB -name $regName -width 8 \
###        -offset $reg16Offset -access rw \
###        -readfunction readMDLC -writefunction writeMDLC -viewfunction viewMDLC \
###        -userdata $userdata
###
###    incr reg16Offset 4
###    set regName MCONF$regIndex
###    imodeladdmmregister -addressblock busPortMDB/MDB -name $regName -width 8 \
###        -offset $reg16Offset -access rw \
###        -readfunction readMCONF -writefunction writeMCONF -viewfunction viewMCONF \
###        -userdata $userdata
###}
### 
### #
### # 16bit message data
### #
### for {set i 0} {$i < 32} {incr i} {
###     # mask registers
###     set reg16Base   [expr $i * 0x80]
###     set regIndex    [format "%02d" $i]
### 
###     set reg16Offset $reg16Base
###     set regName MDATA01$regIndex
###     set userdata [expr ($i<<2) | 0x0]
###     imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMDATA16 -writefunction writeMDATA16 -viewfunction viewMDATA16 \
###         -userdata $userdata
### 
###     incr reg16Offset 8
###     set regName MDATA23$regIndex
###     set userdata [expr ($i<<2) | 0x1]
###     imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMDATA16 -writefunction writeMDATA16 -viewfunction viewMDATA16 \
###         -userdata $userdata
### 
###     incr reg16Offset 8
###     set regName MDATA45$regIndex
###     set userdata [expr ($i<<2) | 0x2]
###         imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMDATA16 -writefunction writeMDATA16 -viewfunction viewMDATA16 \
###         -userdata $userdata
### 
###     incr reg16Offset 8
###     set regName MDATA67$regIndex
###     set userdata [expr ($i<<2) | 0x3]
###         imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMDATA16 -writefunction writeMDATA16 -viewfunction viewMDATA16 \
###         -userdata $userdata
### 
###     incr reg16Offset 8
###     
###     incr reg16Offset 8
###     set regName MIDL$regIndex
###     imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMIDL -writefunction writeMIDL -viewfunction viewMIDL \
###         -userdata $i
### 
###     incr reg16Offset 8
###     set regName MIDH$regIndex
###     imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMIDH -writefunction writeMIDH -viewfunction viewMIDH \
###         -userdata $i
### 
###     incr reg16Offset 8
###     set regName MCTRL$regIndex
###     imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMCTRL -writefunction writeMCTRL -viewfunction viewMCTRL \
###         -writemask 0x0b1f -userdata $i
### }
### 
### #
### # 32bit message data
### #
### for {set i 0} {$i < 32} {incr i} {
###     # mask registers
###     set reg16Base   [expr $i * 0x80]
###     set reg16Offset $reg16Base
###     set regIndex    [format "%02d" $i]
### 
###     set regName MDATA0123$regIndex
###     set userdata [expr ($i<<1) | 0x0]
###         imodeladdmmregister -addressblock busPortMDW/MDW -name $regName -width 32 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMDATA32 -writefunction writeMDATA32 -viewfunction viewMDATA32 \
###         -userdata $userdata
###     
###     incr reg16Offset 16
###     set regName MDATA4567$regIndex
###     set userdata [expr ($i<<1) | 0x1]
###         imodeladdmmregister -addressblock busPortMDW/MDW -name $regName -width 32 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMDATA32 -writefunction writeMDATA32 -viewfunction viewMDATA32 \
###         -userdata $userdata
### 
###     incr reg16Offset 16
###     set regName MID$regIndex
###     set userdata ${i}
###     imodeladdmmregister -addressblock busPortMDW/MDW -name $regName -width 32 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMID -writefunction writeMID -viewfunction viewMID \
###         -userdata $userdata
### }
### 
### 
### 
### set reg16Offset [expr $reg16Offset + 8]
### imodeladdmmregister -addressblock busPortCR/CR -name CTRL -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readCTRL -writefunction writeCTRL -viewfunction viewCTRL
### 
### set reg16Offset [expr $reg16Offset + 16]
### imodeladdmmregister -addressblock busPortCR/CR -name ERC -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readERC -writefunction writeERC -viewfunction viewERC
### 
### set reg16Offset [expr $reg16Offset + 8]
### imodeladdmmregister -addressblock busPortCR/CR -name IE -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readIE -writefunction writeIE -viewfunction viewIE
### 
### set reg16Offset [expr $reg16Offset + 8]
### imodeladdmmregister -addressblock busPortCR/CR -name INTS -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readINTS -writefunction writeINTS -viewfunction viewINTS
### 
### set reg16Offset [expr $reg16Offset + 16]
### imodeladdmmregister -addressblock busPortCR/CR -name BTR -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readBTR -writefunction writeBTR -viewfunction viewBTR
### 
### set reg16Offset [expr $reg16Offset + 16]
### imodeladdmmregister -addressblock busPortCR/CR -name RGPT -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readRGPT -writefunction writeRGPT -viewfunction viewRGPT
### 
### set reg16Offset [expr $reg16Offset + 16]
### imodeladdmmregister -addressblock busPortCR/CR -name TGPT -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readTGPT -writefunction writeTGPT -viewfunction viewTGPT
### 
### set reg16Offset [expr $reg16Offset + 8]
### imodeladdmmregister -addressblock busPortCR/CR -name TS -width 16 \
###     -offset $reg16Offset -access rw \
###     -readfunction readTS -writefunction writeTS -viewfunction viewTS
### 
### for {set i 1} {$i < 5} {incr i} {
###     # mask registers
###     set reg16Offset [expr ($i - 1) * 16]
###     imodeladdmmregister -addressblock busPortCRW/CRW -name MASK${i} -width 16 \
###         -offset $reg16Offset -access rw \
###         -readfunction readMASK -writefunction writeMASK -viewfunction viewMASK \
###         -userdata ${i}
### }

