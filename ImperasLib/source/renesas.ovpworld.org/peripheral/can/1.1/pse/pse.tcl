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
# This peripheral is intended for the VFOREST
#

set vendor  renesas.ovpworld.org
set library peripheral
set name    can
set version 1.1

imodelnewperipheral \
    -name $name -imagefile pse.pse \
    -library $library -vendor $vendor \
    -version $version -constructor constructor

iadddocumentation -name Description -text "Renesas CAN interface. This is an interface between the CAN controller register interface and a PacketNet can interface."
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "No CRC generation or checking."
iadddocumentation -name Reference   -text "VFOREST: R01UH0021EJ0200, Rev. 2.00, Aug 5, 2010"

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

imodeladdbusslaveport -name busPortMR   -mustbeconnected -size 0x300
imodeladdbusslaveport -name busPortMDB  -mustbeconnected -size 0x1000
imodeladdbusslaveport -name busPortMDH  -mustbeconnected -size 0x1000
imodeladdbusslaveport -name busPortMDW  -mustbeconnected -size 0x1000
imodeladdbusslaveport -name busPortECC  -mustbeconnected -size 0x4
imodeladdbusslaveport -name busPortGR   -mustbeconnected -size 0x200
imodeladdbusslaveport -name busPortCR   -mustbeconnected -size 0x200
imodeladdbusslaveport -name busPortCRW  -mustbeconnected -size 0x100

imodeladdaddressblock -name MR  -port busPortMR  -size  0x300 -offset 0 -width 16
imodeladdaddressblock -name ECC -port busPortECC -size    0x4 -offset 0 -width 16
imodeladdaddressblock -name GR  -port busPortGR  -size  0x200 -offset 0 -width 16
imodeladdaddressblock -name CR  -port busPortCR  -size  0x200 -offset 0 -width 16
imodeladdaddressblock -name CRW -port busPortCRW -size  0x100 -offset 0 -width 32
imodeladdaddressblock -name MDW -port busPortMDW -size 0x1000 -offset 0 -width 32
imodeladdaddressblock -name MDH -port busPortMDH -size 0x1000 -offset 0 -width 32
imodeladdaddressblock -name MDB -port busPortMDB -size 0x1000 -offset 0 -width 32

#
# CAN Global Control Register CnGMCTRL
#
imodeladdmmregister -addressblock busPortGR/GR -name GMCTRL -width 16 \
    -offset 0 -access rw \
    -readfunction readGMCTRL -writefunction writeGMCTRL -viewfunction viewGMCTRL

imodeladdmmregister -addressblock busPortMR/MR -name GMCS -width 8 \
    -offset 0x08 -access rw \
    -readfunction readGMCS -writefunction writeGMCS -viewfunction viewGMCS

imodeladdmmregister -addressblock busPortGR/GR -name GMABT -width 16 \
    -offset 0x18 -access rw \
    -readfunction readGMABT -writefunction writeGMABT -viewfunction viewGMABT

imodeladdmmregister -addressblock busPortGR/GR -name GMCONF -width 16 \
    -offset 0x10 -access rw \
    -readfunction readGMCONF -viewfunction viewGMCONF

imodeladdmmregister -addressblock busPortMR/MR -name GMABTD -width 8 \
    -offset 0x20 -access rw \
    -readfunction readGMABTD -writefunction writeGMABTD -viewfunction viewGMABTD

# ECC Control register
imodeladdmmregister -addressblock busPortECC/ECC -name E6A0CTL -width 16 \
    -offset 0 -access rw \
    -readfunction readE6A0CTL -writefunction writeE6A0CTL -viewfunction viewE6A0CTL

set regName LEC
imodeladdmmregister -addressblock busPortMR/MR -name LEC -width 8 \
    -offset 0x248 -access rw \
    -readfunction readLEC -writefunction writeLEC -viewfunction viewLEC

set regName INFO
imodeladdmmregister -addressblock busPortMR/MR -name INFO -width 8 \
    -offset 0x24c -access rw \
    -readfunction readINFO -writefunction writeINFO -viewfunction viewINFO

set regName BRP
imodeladdmmregister -addressblock busPortMR/MR -name BRP -width 8 \
    -offset 0x268 -access rw \
    -readfunction readBRP -writefunction writeBRP -viewfunction viewBRP

set regName LIPT
imodeladdmmregister -addressblock busPortMR/MR -name LIPT -width 8 \
    -offset 0x278 -access rw \
    -readfunction readLIPT -viewfunction viewLIPT

set regName LOPT
imodeladdmmregister -addressblock busPortMR/MR -name LOPT -width 8 \
    -offset 0x288 -access rw \
    -readfunction readLOPT -viewfunction viewLOPT

# 8bit message data
#
for {set i 0} {$i < 32} {incr i} {
    set reg16Base   [expr $i * 0x80]
    set regIndex    [format "%02d" $i]

    for {set j 0} {$j < 8} {incr j} {
        set reg16Offset [expr $reg16Base + (4 * $j)]
        
        set regName MDATA${j}${regIndex}
        set userdata [expr (${i}<<3) | ${j}]
        imodeladdmmregister -addressblock busPortMDB/MDB -name $regName -width 32 \
            -offset $reg16Offset -access rw \
            -readfunction readMDATA -writefunction writeMDATA \
            -userdata $userdata
    }
    
    incr reg16Offset 4
    set regName MDLC$regIndex
    set userdata ${i}
    imodeladdmmregister -addressblock busPortMDB/MDB -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDLC -writefunction writeMDLC -viewfunction viewMDLC \
        -userdata $userdata

    incr reg16Offset 4
    set regName MCONF$regIndex
    imodeladdmmregister -addressblock busPortMDB/MDB -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMCONF -writefunction writeMCONF -viewfunction viewMCONF \
        -userdata $userdata
}

#
# 16bit message data
#
for {set i 0} {$i < 32} {incr i} {
    # mask registers
    set reg16Base   [expr $i * 0x80]
    set regIndex    [format "%02d" $i]

    set reg16Offset $reg16Base
    set regName MDATA01$regIndex
    set userdata [expr ($i<<2) | 0x0]
    imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDATA -writefunction writeMDATA \
        -userdata $userdata

    incr reg16Offset 8
    set regName MDATA23$regIndex
    set userdata [expr ($i<<2) | 0x1]
    imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDATA -writefunction writeMDATA \
        -userdata $userdata

    incr reg16Offset 8
    set regName MDATA45$regIndex
    set userdata [expr ($i<<2) | 0x2]
        imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDATA -writefunction writeMDATA \
        -userdata $userdata

    incr reg16Offset 8
    set regName MDATA67$regIndex
    set userdata [expr ($i<<2) | 0x3]
        imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDATA -writefunction writeMDATA \
        -userdata $userdata

    incr reg16Offset 8
    
    incr reg16Offset 8
    set regName MIDL$regIndex
    imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
        -offset $reg16Offset -access rw \
        -readfunction readMIDL -writefunction writeMIDL -viewfunction viewMIDL \
        -userdata $i

    incr reg16Offset 8
    set regName MIDH$regIndex
    imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
        -offset $reg16Offset -access rw \
        -readfunction readMIDH -writefunction writeMIDH -viewfunction viewMIDH \
        -userdata $i

    incr reg16Offset 8
    set regName MCTRL$regIndex
    imodeladdmmregister -addressblock busPortMDH/MDH -name $regName -width 16 \
        -offset $reg16Offset -access rw \
        -readfunction readMCTRL -writefunction writeMCTRL -viewfunction viewMCTRL \
        -writemask 0x0b1f -userdata $i
}

#
# 32bit message data
#
for {set i 0} {$i < 32} {incr i} {
    # mask registers
    set reg16Base   [expr $i * 0x80]
    set reg16Offset $reg16Base
    set regIndex    [format "%02d" $i]

    set regName MDATA0123$regIndex
    set userdata [expr ($i<<1) | 0x0]
    imodeladdmmregister -addressblock busPortMDW/MDW -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDATA -writefunction writeMDATA \
        -userdata $userdata
    
    incr reg16Offset 16
    set regName MDATA4567$regIndex
    set userdata [expr ($i<<1) | 0x1]
    imodeladdmmregister -addressblock busPortMDW/MDW -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMDATA -writefunction writeMDATA \
        -userdata $userdata

    incr reg16Offset 16
    set regName MID$regIndex
    set userdata ${i}
    imodeladdmmregister -addressblock busPortMDW/MDW -name $regName -width 32 \
        -offset $reg16Offset -access rw \
        -readfunction readMID -writefunction writeMID -viewfunction viewMID \
        -userdata $userdata
}

#
# Control registers
#
for {set i 1} {$i < 5} {incr i} {
    # mask registers
    set reg16Offset [expr ($i - 1) * 16]
    imodeladdmmregister -addressblock busPortCR/CR -name MASK${i}L -width 16 \
        -offset $reg16Offset -access rw \
        -readfunction readMASKL -writefunction writeMASKL -viewfunction viewMASKL \
        -userdata ${i}
    
    set reg16Offset [expr $reg16Offset + 8]
    imodeladdmmregister -addressblock busPortCR/CR -name MASK${i}H -width 16 \
        -offset $reg16Offset -access rw \
        -readfunction readMASKH -writefunction writeMASKH -viewfunction viewMASKH \
        -userdata ${i}
}

set reg16Offset [expr $reg16Offset + 8]
imodeladdmmregister -addressblock busPortCR/CR -name CTRL -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readCTRL -writefunction writeCTRL -viewfunction viewCTRL

set reg16Offset [expr $reg16Offset + 16]
imodeladdmmregister -addressblock busPortCR/CR -name ERC -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readERC -writefunction writeERC -viewfunction viewERC

set reg16Offset [expr $reg16Offset + 8]
imodeladdmmregister -addressblock busPortCR/CR -name IE -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readIE -writefunction writeIE -viewfunction viewIE

set reg16Offset [expr $reg16Offset + 8]
imodeladdmmregister -addressblock busPortCR/CR -name INTS -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readINTS -writefunction writeINTS -viewfunction viewINTS

set reg16Offset [expr $reg16Offset + 16]
imodeladdmmregister -addressblock busPortCR/CR -name BTR -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readBTR -writefunction writeBTR -viewfunction viewBTR

set reg16Offset [expr $reg16Offset + 16]
imodeladdmmregister -addressblock busPortCR/CR -name RGPT -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readRGPT -writefunction writeRGPT -viewfunction viewRGPT

set reg16Offset [expr $reg16Offset + 16]
imodeladdmmregister -addressblock busPortCR/CR -name TGPT -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readTGPT -writefunction writeTGPT -viewfunction viewTGPT

set reg16Offset [expr $reg16Offset + 8]
imodeladdmmregister -addressblock busPortCR/CR -name TS -width 16 \
    -offset $reg16Offset -access rw \
    -readfunction readTS -writefunction writeTS -viewfunction viewTS

for {set i 1} {$i < 5} {incr i} {
    # mask registers
    set reg16Offset [expr ($i - 1) * 16]
    imodeladdmmregister -addressblock busPortCRW/CRW -name MASK${i} -width 16 \
        -offset $reg16Offset -access rw \
        -readfunction readMASK -writefunction writeMASK -viewfunction viewMASK \
        -userdata ${i}
}

