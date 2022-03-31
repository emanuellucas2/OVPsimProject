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

set range    16
set regWidth 32

imodelnewperipheral \
    -imagefile pse.pse \
    -name IcpControl \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0  \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM Integrator Board Controller Module"
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"

#   name  offset ac description         readFn    writeFn    bits
set registers {
    id       0   r  CP_IDFIELD          readID     0          0
    flash    1   r  CP_FLASHPROG        readZero   0          0
    intreg   2   r  CP_INTREG           readZero   0          0
    decode   3   r  CP_DECODE           readDecode 0          0
}

foreach { rname roffset raccess  desc readFn writeFn  bits } $registers {
    if { $readFn != 0 } {
        set r "-readfunction $readFn"
    } else { set r "" }
    if { $writeFn != 0 } {
        set w "-writefunction $writeFn"
    } else { set w "" }
    set offset [expr 4 * $roffset]
    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w"

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
