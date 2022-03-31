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

set range    0x1000
set regWidth 32

imodelnewperipheral \
    -imagefile pse.pse \
    -name RtcPL031 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0  \
    -constructor constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM PL031 Real Time Clock (RTC)"
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "ARM PrimeCell Real Time Clock (PL031) Technical Reference Manual (ARM DDI 0224)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"

#   name  offset ac description              readFn   writeFn   bits
set registers {
    dr          0      r  "Data read"        readDR   0         0
    mr          1      rw "Match"            0        writeMR   0
    lr          2      rw "Data load"        0        writeLR   0
    cr          3      rw "Control"          readCR   writeCR   0
    im          4      rw "Interrupt mask"   0        writeIM   0
    is          5      r  "Raw interrupt"    0        0         0
    mis         6      r  "Masked interrupt" readMIS  0         0
    icr         7      w  "Interrupt clear"  0        writeICR  0
}

foreach { rname roffset raccess  desc readFn writeFn  bits } $registers {
    if { $readFn != 0 } {
        set r "-readfunction $readFn"
    } else { set r "" }
    if { $writeFn != 0 } {
        set w "-writefunction $writeFn"
    } else { set w "" }
    set offset [expr 4 * $roffset]
    set cmd "imodeladdmmregister -name $rname -width 32 -addressblock $addBlock -offset $offset -access $raccess $r $w"

    eval $cmd
    if { $desc != 0 } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }

    if { $bits != 0 } {
        foreach { n o } $bits {
            imodeladdfield -mmregister "$addBlock/$rname" -bitoffset $o -name $n
        }
    }
}

# ARM id codes
imodeladdmmregister                       \
     -name         id%u                   \
     -offset       4064                   \
     -addressblock $addBlock              \
     -access       r                      \
     -readfunction readID                 \
     -userdata     _index                 \
     -loarray      0                      \
     -hiarray      7 

imodeladdnetport -name irq -type output

iadddocumentation -name Description -text "ARM PL031 RTC"

