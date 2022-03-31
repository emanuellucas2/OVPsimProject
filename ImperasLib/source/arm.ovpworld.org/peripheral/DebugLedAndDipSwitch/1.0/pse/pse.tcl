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

imodelnewperipheral        \
    -imagefile pse.pse     \
    -name    DebugLedAndDipSwitch    \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0  \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM Integrator Board Debug LEDs and DIP Switch Interface"
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"


#   name     offset ac description                           reset readFn     writeFn     bits
set registers {
    LED_ALPHA    0   rw  "Alphanumeric Characters register"  0     -          writeAlpha  -
	LED_LIGHTS   1   rw  "LED Control register"              0     -          writeLED    -
	LED_SWITCHES 2   r   "DIP Switch register"               0     -          -
}


foreach { name roffset raccess desc reset readFn writeFn bits } $registers {
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
	if { $reset != "-" } {
		imodeladdreset -mmregister "$addBlock/$rname" -name reset -value $reset
	}

    if { $bits != "-" } {
        foreach { n o } $bits {
            imodeladdfield -mmregister "$addBlock/$rname" -bitoffset $o -name $n
        }
    }
}

