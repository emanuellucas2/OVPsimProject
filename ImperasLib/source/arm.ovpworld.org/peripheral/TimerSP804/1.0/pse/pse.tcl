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

imodelnewperipheral          \
    -imagefile pse.pse       \
    -name    TimerSP804      \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -destructor  destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "Timer SP804 Module"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "ARM Dual-Timer Module (SP804) Technical Reference Manual (ARM DDI 0271)" 

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"
set timerSize    256

#   name     offset ac description      readFn     writeFn      user
set registers {
    T0Load      0    rw   ""          readLoad    writeLoad      0
    T0Value     1    r    ""          readValue    -             0
    T0Control   2    rw   ""          readControl writeControl   0
    T0IntClr    3    w    ""          -           writeIntClr    0
    T0RIS       4    r    ""          readRIS     -              0
    T0MIS       5    r    ""          readMIS     -              0
    T0BGLoad    6    rw   ""          readLoad    writeBGLoad    0
    T1Load      8    rw   ""          readLoad    writeLoad      1
    T1Value     9    r    ""          readValue   -              1
    T1Control   10    rw   ""         readControl writeControl   1
    T1IntClr    11    w    ""         -           writeIntClr    1
    T1RIS       12    r    ""         readRIS     -              1
    T1MIS       13    r    ""         readMIS     -              1
    T1BGLoad    14    rw   ""         readLoad    writeBGLoad    1
    ITCR        960   rw   ""         -           -           -
    ITOP        961   w    ""         -           -           -
    PeriphID0   1016   r    ""    readPeriphID0    -           -
    PeriphID1   1017   r    ""    readPeriphID1    -           -
    PeriphID2   1018   r    ""    readPeriphID2    -           -
    PeriphID3   1019   r    ""    readPeriphID3    -           -
    PCellID0    1020   r    ""    readPCellID0     -           -
    PCellID1    1021   r    ""    readPCellID1     -           -
    PCellID2    1022   r    ""    readPCellID2     -           -
    PCellID3    1023   r    ""    readPCellID3     -           -
}


set ctrl_bits {
    ONESHOT      1 0
    M32BIT       1 1
    DIV          2 2
    IE           1 5
    PERIODIC     1 6
    ENABLE       1 7
}

foreach { name roffset raccess desc readFn writeFn timer } $registers {
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

    if { $timer != "-" } {
        set u "-userdata $timer"
    } else {
        set u ""
    }

    set offset [expr 4 * $roffset ]
    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $u"

    eval $cmd
    if { $desc != 0 } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }





}

foreach { bname bits offset } $ctrl_bits {
    imodeladdfield -name $bname -width $bits -bitoffset $offset -mmregister $addBlock/T0Control
    imodeladdfield -name $bname -width $bits -bitoffset $offset -mmregister $addBlock/T1Control
}

imodeladdnetport -name irq -type output
