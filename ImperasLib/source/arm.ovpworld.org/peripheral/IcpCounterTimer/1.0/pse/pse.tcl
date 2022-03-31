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
    -name    IcpCounterTimer      \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -destructor  destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM Integrator Board Counter/Timer Module"
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"
set timerSize    256

#   name  offset ac description         readFn      writeFn      user
set registers {
    load     0   rw "Timer Load"        readLimit   writeLimit   $timer
    limit    1   rw "Timer Value"       readValue   writeValue   $timer
    control  2   rw "Timer Control"     readControl writeControl $timer
    intclr   3   w  "Interrupt Clear"   -           writeClear   $timer
    intlevel 4   r  "Interrupt level"   -           -            -
    mis      5   r  "Timer MIS"         readMIS     -            $timer
    bgload   6   w  "Timer BG Load"     -           writeBG      $timer
}

set ctrl_bits {
    ONESHOT      1 0
    M32BIT       1 1
    DIV          2 2
    IE           1 5
    PERIODIC     1 6
    ENABLE       1 7
}

for { set timer 0 } { $timer < 3 } { incr timer } {

    foreach { name roffset raccess  desc readFn writeFn user } $registers {
        set rname ${name}${timer}

        if { $readFn != "-" } {
            set r "-readfunction $readFn"
        } else { set r "" }
        if { $writeFn != "-" } {
            set w "-writefunction $writeFn"
        } else { set w "" }

        if { $user != "-" } {
            set u "-userdata $timer"
        } else { set u "" }
        
        set offset [expr (4 * $roffset) + ($timer * $timerSize)]
        set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $u"

        eval $cmd
        if { $desc != 0 } {
            iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
        }
    }
    foreach { bname bits offset } $ctrl_bits {
        imodeladdfield -name $bname -width $bits -bitoffset $offset -mmregister $addBlock/control${timer}
    }

    imodeladdnetport -name irq${timer} -type output
}
