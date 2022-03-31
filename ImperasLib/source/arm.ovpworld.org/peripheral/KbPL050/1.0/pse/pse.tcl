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

imodelnewperipheral   \
    -imagefile      pse.pse \
    -extensionfile  model    \
    -name KbPL050 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -destructor  destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM PL050 PS2 Keyboard or mouse controller"
iadddocumentation -name Limitations -text "None" 
iadddocumentation -name Reference   -text "ARM PrimeCell PS2 Keyboard/Mouse Interface (PL050) Technical Reference Manual (ARM DDI 0143)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdformal   -name isMouse     -type bool
iadddocumentation -name Description -handle isMouse -text "if non:zero, this device is the mouse (isKeyboard should be 0)"
imodeladdformal   -name isKeyboard  -type bool
iadddocumentation -name Description -handle isKeyboard -text "if non:zero, this device is the keyboard (isMouse should be 0)"

imodeladdformal   -name grabDisable -type bool
iadddocumentation -name Description -text "If non:zero, disables grabbing of the mouse by the VGA/input window."

imodeladdformal   -name cursorEnable -type bool
iadddocumentation -name Description  -text "If non:zero, shows a basic software cursor in the VGA/input window at the mouse position."

imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

imodeladdbusslaveport -name bport1 -size $range

imodeladdaddressblock -name ab -port bport1 -width 32 -size $range

set addBlock     "bport1/ab"
set regWidth     8

#   name  offset ac description        readFn   writeFn   bits
set registers {
    cr          0      rw KMICR        0        writeCR   0
    stat        1      rw KMISTAT      readSTAT 0         { TXEMPTY 6 TXBUSY 5 RXFULL 4 RXBUSY 3 RXPARITY 2 KMIC 1 KMID 0 }
    data        2      rw KMIDATA      readDATA writeDATA 0
    clk         3      rw KMICLKDIV    0        0         0
    iir         4      r  KMIIR        readIIR  0         0
}

foreach { rname roffset raccess  desc readFn writeFn  bits } $registers {
    if { $readFn != 0 } {
        set r "-readfunction $readFn"
    } else { set r "" }
    if { $writeFn != 0 } {
        set w "-writefunction $writeFn"
    } else { set w "" }
    set offset [expr 4 * $roffset]
    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -width $regWidth -offset $offset -access $raccess $r $w"

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

imodeladdmmregister -name id%u -offset 4064 -addressblock $addBlock -access r -readfunction readID -loarray 0 -hiarray 7 

imodeladdnetport -name irq -type output


