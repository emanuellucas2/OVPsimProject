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
set name    dma
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas DMA Controller"
iadddocumentation -name Limitations -text "Initial implementation to support CAN DMA message transfer only"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# Master port
#
imodeladdbusmasterport -name DMAPM -addresswidth 28

#
# Slave port
#
# DMAP0 allows access to fixed address DMA Wait Control Registers
imodeladdbusslaveport -name DMAP0 -size 0x10
# DMAP1 allows access to registers at 'base' address
imodeladdbusslaveport -name DMAP1 -size 0x100

#
# Registers
#
imodeladdaddressblock -port DMAP0 -name abc -size 0x10 -offset 0 -width  16

#
# DMA Wait Control Register (fixed address)
#
set regName DMAWC0
imodeladdmmregister -addressblock DMAP0/abc -name ${regName} -width 16  -offset 0 -access rw -writefunction write${regName} -readfunction read${regName}
iadddocumentation   -handle DMAP0/abc/${regName} -name Description -text "DMA Controller Wait Control Register 0"

imodeladdreset -mmregister DMAP0/abc/${regName} -name reset -value 0x37

set regName DMAWC1
imodeladdmmregister -addressblock DMAP0/abc -name ${regName} -width 16  -offset 2 -access rw -writefunction write${regName} -readfunction read${regName}
iadddocumentation   -handle DMAP0/abc/${regName} -name Description -text "DMA Controller Wait Control Register 1"

imodeladdreset -mmregister DMAP0/abc/${regName} -name reset -value 0x07

#
# DMA Registers (located from base)
#
# 16-bit wide registers
set abwbase 0x00
# 8-bit wide registers, start at SAR0 0x24
set abbbase 0x24
imodeladdaddressblock -port DMAP1 -name abw -size ${abbbase}                -offset ${abwbase} -width  16
imodeladdaddressblock -port DMAP1 -name abb -size [expr 0x100 - ${abbbase}] -offset ${abbbase} -width  8


set offset [expr 0x24 - $abbbase]
set regName SAR%u
imodeladdmmregister -addressblock DMAP1/abb -name ${regName} -width 8 -offset $offset -access rw -writefunction writeSAR -writemask 0x0f -readfunction readSAR -userdata _index -loarray 2 -hiarray 3
iadddocumentation   -handle DMAP1/abb/${regName} -name Description -text "DMA Controller Transfer SFR Start Adrress Register"
imodeladdreset -mmregister DMAP1/abb/${regName} -name reset -value 0x00
imodeladdfield -mmregister DMAP1/abb/${regName} -name SAR -bitoffset 0 -width 4
    

set regName MAR%u
set offset 0
imodeladdmmregister -addressblock DMAP1/abw -name ${regName} -width 16  -offset ${offset} -access rw  -writefunction writeMAR -readfunction readMAR -userdata _index -loarray 0 -hiarray 9
iadddocumentation   -handle DMAP1/abw/${regName} -name Description -text "DMA Controller Transfer Memory Start Address Register"
imodeladdreset -mmregister DMAP1/abw/${regName} -name reset -value 0x00


set regName DTFR%u
set offset [expr 0x80 - $abbbase]
imodeladdmmregister -addressblock DMAP1/abb -name ${regName} -width 8  -offset ${offset} -access rw -writefunction writeDTFR -readfunction readDTFR -userdata _index -loarray 4 -hiarray 7
iadddocumentation   -handle DMAP1/abb/${regName} -name Description -text "DMA Controller Trigger Factor register"
imodeladdreset -mmregister DMAP1/abb/${regName} -name reset -value 0x00
imodeladdfield -mmregister DMAP1/abb/${regName} -name IFCn -bitoffset 0 -width 3


set regName DTCR%u
set offset [expr 0x40 - $abbbase]
imodeladdmmregister -addressblock DMAP1/abb -name ${regName} -width 8  -offset ${offset} -access rw   -writefunction writeDTCR -readfunction readDTCR -userdata _index -loarray 0 -hiarray 9
iadddocumentation   -handle DMAP1/abb/${regName} -name Description -text "DMA Controller Transfer Count register"
imodeladdreset -mmregister DMAP1/abb/${regName} -name reset -value 0x00


set regName DMASL
set offset [expr 0x62 - $abbbase]
imodeladdmmregister -addressblock DMAP1/abb -name ${regName} -width 8  -offset ${offset} -access rw  -writefunction write${regName} -readfunction read${regName}
iadddocumentation   -handle DMAP1/abb/${regName} -name Description -text "DMA Controller Status Register"

imodeladdreset -mmregister DMAP1/abb/${regName} -name reset -value 0x00

imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS7 -bitoffset 7 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS6 -bitoffset 6 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS5 -bitoffset 5 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS4 -bitoffset 4 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS3 -bitoffset 3 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS2 -bitoffset 2 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS1 -bitoffset 1 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMAS0 -bitoffset 0 -width 1

set regName DMAMCL
set offset [expr 0x60 - $abbbase]
imodeladdmmregister -addressblock DMAP1/abb -name ${regName} -width 8  -offset ${offset} -access rw  -writefunction write${regName} -readfunction read${regName}
iadddocumentation   -handle DMAP1/abb/${regName} -name Description -text "DMA Controller Mode Control Register"

imodeladdreset -mmregister DMAP1/abb/${regName} -name reset -value 0x00

imodeladdfield -mmregister DMAP1/abb/${regName} -name DE7 -bitoffset 7 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE6 -bitoffset 6 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE5 -bitoffset 5 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE4 -bitoffset 4 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE3 -bitoffset 3 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE2 -bitoffset 2 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE1 -bitoffset 1 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DE0 -bitoffset 0 -width 1

set regName DMADSCL
set offset [expr 0x64 - $abbbase]
imodeladdmmregister -addressblock DMAP1/abb -name ${regName} -width 8  -offset ${offset} -access rw -writefunction write${regName} -writemask 0xf0 -readfunction read${regName}
iadddocumentation   -handle DMAP1/abb/${regName} -name Description -text "DMA Controller Data Size Control Register"

imodeladdreset -mmregister DMAP1/abb/${regName} -name reset -value 0x00

imodeladdfield -mmregister DMAP1/abb/${regName} -name DMADCS7 -bitoffset 7 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMADCS6 -bitoffset 6 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMADCS5 -bitoffset 5 -width 1
imodeladdfield -mmregister DMAP1/abb/${regName} -name DMADCS4 -bitoffset 4 -width 1

#
# Input and Output nets
#
imodeladdnetport -name INTDMA%u -type output -updatefunctionargument _index -loarray 0 -hiarray 9

imodeladdnetport -name DMA0EN -type output
imodeladdnetport -name DMA1EN -type output

foreach trigger {ADDMARQ0 ADDMARQ1 INTTS0CD INTTS1CD INTCE0C INTCE1C INTBE0R INTBE1R INTUC0R INTUC1R INTUC2R} {
    imodeladdnetport -name $trigger -type input -updatefunction trigger$trigger
}
