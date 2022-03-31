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

imodelnewperipheral            \
    -imagefile pse.pse         \
    -name LcdPL110             \
    -vendor  arm.ovpworld.org  \
    -library peripheral        \
    -version 1.0               \
    -constructor constructor   \
    -extensionfile  model      \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM PL110 LCD Controller"
iadddocumentation -name Limitations -text "The VGA display refresh is not optimised resulting in the VGA peripheral causing a limit on the maximum performance of a platform it contains to be around 300 MIPS (actual dependent upon refresh rate of LCD)."
iadddocumentation -name Limitations -text "The LCD peripheral utilises memory watchpoints to optimise display refresh. This requires the use of ICM memory for the frame buffers, which currently may stop its use in SystemC TLM2 platforms."
iadddocumentation -name Limitations -text "Interrupts are not supported"
iadddocumentation -name Reference   -text "ARM PrimeCell Color LCD Controller (PL111) Technical Reference Manual (ARM DDI 0293)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdformal -name busOffset   -type uns32
iadddocumentation  -name Description  -text "Set an offset for the display memory window"

imodeladdformal -name scanDelay   -type uns32  -defaultvalue 20000
iadddocumentation  -name Description  -text "Set the rate of the display refresh (default 20000)"

imodeladdformal -name noGraphics  -type bool
iadddocumentation  -name Description  -text "Disable the graphics output"

imodeladdformal -name resolution  -type string -defaultvalue "vga"
iadddocumentation  -name Description  -text "Set the resolution of the display. VGA (default), SVGA, XVGA/XGA."

imodeladdformal -name pixelChecksum -type bool			  
iadddocumentation -name Description -text "Write a checksum of each screen contents"

imodeladdformal -name packedPixels  -type bool
iadddocumentation  -name Description  -text "Only valid when 24BPP used. Set to enable pixel packing in data buffer. Default 24 bit pixel stored in 32-bit data word."

imodeladdformal -name title  -type string -defaultvalue "PL110 LCD"
iadddocumentation  -name Description  -text "Set the title of the display window"

imodeladdbusslaveport -name memory -remappable -addresswidth 32

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width 32 -size $range

set addBlock     "bport1/ab"
set regWidth     32

# Note: in Pl110 imsc is at offset 6, control at offset 7
#       in PL111 imsc is at offset 7, control at offset 6

#   name   offset  ac description      readFn      writeFn      user
set registers {
    timing0     0  rw "LCD Timing 0"   readTiming  writeTiming  0
    timing1     1  rw "LCD Timing 1"   readTiming  writeTiming  1
    timing2     2  rw "LCD Timing 2"   readTiming  writeTiming  2
    timing3     3  rw "LCD Timing 3"   readTiming  writeTiming  3
    upbase      4  rw "LCD UP Base"    -           writeUP      -
    lpbase      5  rw "LCD LP Base"    -           writeLP      -
    imsc        6  rw "LCD IMSC"       readIMSC    writeIMSC    -
    control     7  rw "LCD Control"    readControl writeControl -
    int_status  8  r  "LCD RIS"        -           -            -
    int_mis     9  r  "LCD MIS"        readMIS     -            -
    int_clr    10  w  "LCD ICR"        -           writeICR     -
    upbase2    11  r  "LCD UP current" readUP      -            -
    lpbase2    12  r  "LCD LP current" readLP      -            -
}

foreach { rname roffset raccess  desc readFn writeFn  user } $registers {
    set r ""
    set w ""
    set u ""
    if { $readFn  != "-" } { set r "-readfunction  $readFn"   }
    if { $writeFn != "-" } { set w "-writefunction $writeFn"  }
    if { $user    != "-" } { set u "-userdata $user"          }

    set offset [expr 4 * $roffset]
    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $u"
    eval $cmd

    iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
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

imodeladdfield -mmregister "$addBlock/control" -bitoffset  0 -name EN
imodeladdfield -mmregister "$addBlock/control" -bitoffset  8 -name BGR
imodeladdfield -mmregister "$addBlock/control" -bitoffset  9 -name BEBO
imodeladdfield -mmregister "$addBlock/control" -bitoffset 10 -name BEPO
imodeladdfield -mmregister "$addBlock/control" -bitoffset 11 -name PWR

imodeladdnetport -name irq -type output

