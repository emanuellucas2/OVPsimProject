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
    -name IntICP \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.01 \
    -constructor constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM Integrator Board interrupt controller"
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Reference   -text "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width 32 -size $range

set addBlock     "bport1/ab"

#   name  offset ac description         readFn    writeFn    bits
set registers {
    status   0   r  "IRQ_STATUS"        readIRQ    0          0
    level    1   r  "IRQ_RAWSTAT"       0          0          0
    enable   2   rw "IRQ_ENABLE_SET"    0          writeSET   0
    clr      3   w  "IRQ_ENABLE_CLR"    0          writeCLR   0
    softset  4   rw "INT_SOFTSET"       readLEV    writeSST   0
    softclr  5   w  "INT_SOFTCLR"       0          writeSCL   0
    frqstat  8   r  "FRQ_STATUS"        readFIQ    0          0
    rawstat  9   r  "FRQ_RAWSTAT"       readLevel  0          0
    fiqen    10  w  "FIQ_ENABLESET"     0          writeFIQS  0
    fiqenclr 11  w  "FRQ_ENABLECLR"     0          writeFIQC 0
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

imodeladdnetport -name irq -type output
imodeladdnetport -name fiq -type output

imodeladdnetport -name ir%u -type input -updatefunction irqUpdate -updatefunctionargument _index -loarray 0 -hiarray 31


