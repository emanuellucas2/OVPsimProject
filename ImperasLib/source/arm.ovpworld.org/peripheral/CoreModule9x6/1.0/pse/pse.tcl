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
    -name    CoreModule9x6 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor  \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM Integrator Board 9x6 Core Module Registers "
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "ARM Integrator CM926EJ-S, CM946E-S, CM966E-S, CM1026EJ-S, and CM1136JF-S User Guide (DUI 0138)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"

#   name     offset ac description             readFn     writeFn      bits
set registers {
    id          0   r   "Identification"       readID     -            -
    proc        1   r   "Proc"                 readProc   -            -
    osc         2   rw  "Oscillator"           -          -            -
    ctrl        3   rw  "Control"              -          writeCtrl    -
    stat        4   r   "Status"               readStat   -            -
    lock        5   r   "Lock"                 readLock   -            -
    lmbuscnt    6   r   "Hi Freq timer"        -          -            -
    auxosc      7   rw  "Aux Osc"              -          -            -
    sdram       8   rw  "SDRAM"                -          -            -
    init        9   rw  "Init"                 -          -            -
    refct      10   r   "SDRAM"                -          -            -
    flags      12   rw  "Flags"                -          -            -
    flagsc     13   w   "Flagsc"               -          -            -
    nvflags    14   rw  "NV Flags"             -          -            -
    nvflagss   15   w   "NV FlagsS"            -          -            -
    irqstat    16   r   "IRQ Status"           -          -            -
    irqrstat   17   r   "IRQ RSTATUS"          -          -            -
    irqenset   18   rw  "IRQ EN SET"           -          -            -
    irqenclr   19   w   "IRQ EN Clear"         -          -            -
    softintset 20   r   "Soft Interrupt Set"   -          -            -
    softintclr 21   w   "Soft Interrupt Clear" -          -            -
    fiqstat    24   r   "FIQ Status"           -          -            -
    fiqrstat   25   r   "FIQ RStatus"          -          -            -
    fiqenset   26   rw  "FIQ EN Set"           -          -            -
    fiqenclr   27   rw  "FIQ EN Clear"         -          -            -
    volt0      32   rw  "Voltage CTL0"         -          -            -
    volt1      33   rw  "Voltage CTL1"         -          -            -
    volt2      34   rw  "Voltage CTL2"         -          -            -
    volt3      35   rw  "Voltage CTL3"         -          -            -
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

    set offset [expr 4 * $roffset ]
    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w"

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
