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

imodelnewperipheral  \
    -imagefile pse.pse  \
    -name   AaciPL041 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM PL041 PrimeCell Advanced Audio CODEC Interface Registers"
iadddocumentation -name Limitations -text "Programmers View, register model only. Does NOT model functionality, just provides registers to allow code to run." 
iadddocumentation -name Reference   -text "ARM PrimeCell Advanced Audio CODEC Interface (PL041) Technical Reference Manual (ARM DDI 0173)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"


#   name     offset ac description             readFn     writeFn      bits

set registers {

    PeriphID0       0xFE0   r    ""    -         -           -
    PeriphID1       0XFE4   r    ""    -         -           -
    PeriphID2       0XFE8   r    ""    -         -           -
    PeriphID3       0XFEC   r    ""    -         -           -
    PCellID0        0XFF0   r    ""    -         -           -
    PCellID1        0XFF4   r    ""    -         -           -
    PCellID2        0XFF8   r    ""    -         -           -
    PCellID3        0XFFC   r    ""    -         -           -
}

foreach { name roffset raccess desc readFn writeFn bits } $registers {
    set rname ${name}

    if { $readFn != "-" } {
        set r "-readfunction $readFn"
    } else {
        set r ""
    }
    if { $writeFn != "-" } {
        set w "-writefunction $writeFn"
    } else {
        set w ""
    }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $roffset -access $raccess $r $w"

    eval $cmd
    if { $desc != 0 } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }

    if { $bits != "-" } {
        foreach { n o } $bits {
            imodeladdfield -mmregister "$addBlock/$rname" -bitoffset $o -name $n
        }
    }
}


