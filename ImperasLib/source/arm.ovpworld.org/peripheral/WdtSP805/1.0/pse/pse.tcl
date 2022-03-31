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
    -name    WdtSP805 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM SP805 Watchdog Registers."
iadddocumentation -name Limitations -text "Does NOT model watchdog functionality, just provides registers to allow code to run."
iadddocumentation -name Reference   -text "ARM Watchdog Module (SP805) Technical Reference Manual (ARM DDI 0270)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"


#   name     offset ac description             readFn     writeFn      bits

set registers {
    WdogLoad        0x00  rw   "                 "    -   -    -
    WdogValue       0x04  r    "                 "    -   -    -
    WdogControl     0x08  rw   "                 "    -   -    -
    WdogIntClr      0x0C  w    "                 "    -   -    -
    WdogRIS         0x10  r    "                 "    -   -    -
    WdogMIS         0x14  r    "                 "    -   -    -
    WdogLock        0xC00 rw   "                 "    -   -    -
    WdogITCR        0xF00 rw   "                 "    -   -    -
    WdogITOP        0xF04 w    "                 "    -   -    -
    PeriphID0       0xFE0   r    ""    readPeriphID0    -           -
    PeriphID1       0XFE4   r    ""    readPeriphID1    -           -
    PeriphID2       0XFE8   r    ""    readPeriphID2    -           -
    PeriphID3       0XFEC   r    ""    readPeriphID3    -           -
    PCellID0        0XFF0   r    ""    readPCellID0     -           -
    PCellID1        0XFF4   r    ""    readPCellID1     -           -
    PCellID2        0XFF8   r    ""    readPCellID2     -           -
    PCellID3        0XFFC   r    ""    readPCellID3     -           -
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


