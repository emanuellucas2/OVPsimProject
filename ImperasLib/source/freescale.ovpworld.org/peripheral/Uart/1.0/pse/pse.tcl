#
# Copyright (c) 2011-2016 Posedge Software, Inc., www.posedgesoft.com
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

set vendor  freescale.ovpworld.org
set library peripheral
set name    Uart
set version 1.0
set desc "Freescale UART - Supports interrupts and fifos."
set limitations "
Error conditions, DMA, ISO7816 mode and Wake up are not supported.
"
set reference "Freescale Kinetis Peripheral User Guide"

set range 0x1000

imodelnewperipheral           \
    -imagefile   pse.pse      \
    -name        $name        \
    -vendor      $vendor      \
    -library     $library     \
    -version     $version     \
    -constructor constructor  \
    -releasestatus ovp

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text $reference

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x20     -port bport1 -width 8 

set addBlock     "bport1/ab"

#   name          offset ac readFn    writeFn     viewFn   user reset   mask description   
set registers {
    bdh           0x0    rw -         writeBDH    -        -    0x00    0xdf "UART Baud Rate Registers:High"
    bdl           0x1    rw -         writeBDL    -        -    0x04    -    "UART Baud Rate Registers:Low"
    c1            0x2    rw -         -           -        -    0x00    -    "UART Control Register 1"
    c2            0x3    rw -         writeC2     -        -    0x00    -    "UART Control Register 2"
    s1            0x4    r  readS1    -           viewS1   -    0xC0    -    "UART Status Register 1"
    s2            0x5    rw -         -           -        -    0x00    0xfe "UART Status Register 2"
    c3            0x6    rw -         -           -        -    0x00    0x7f "UART Control Register 3"
    d             0x7    rw readD     writeD      -        -    0x00    -    "UART Data Register"
    ma1           0x8    rw -         -           -        -    0x00    -    "UART Match Address Registers 1"
    ma2           0x9    rw -         -           -        -    0x00    -    "UART Match Address Registers 2"
    c4            0xa    rw -         writeC4     -        -    0x00    -    "UART Control Register 4"
    c5            0xb    rw -         -           -        -    0x00    0xa0 "UART Control Register 5"
    ed            0xc    r  -         -           -        -    0x00    -    "UART Extended Data Register"
    modem         0xd    rw -         -           -        -    0x00    0x0f "UART Modem Register"
    infrared      0xe    rw -         -           -        -    0x00    0x07 "UART Infrared Register"
    pfifo         0x10   rw -         -           -        -    0x22    0x88 "UART FIFO Parameters Register"
    cfifo         0x11   rw -         writeCFIFO  -        -    0x00    0xc3 "UART FIFO Control Register"
    sfifo         0x12   rw -         -           -        -    0xc0    0x03 "UART FIFO Status Register"
    twfifo        0x13   rw -         writeTWFIFO -        -    0x00    -    "UART FIFO Transmit Watermark Register"
    tcfifo        0x14   r  -         -           -        -    0x00    -    "UART FIFO Transmit Count Register"
    rwfifo        0x15   rw -         writeRWFIFO -        -    0x01    -    "UART FIFO Receive Watermark Register"
    rcfifo        0x16   r  -         -           -        -    0x00    -    "UART FIFO Receive Count Register"
}

foreach { rname offset raccess readFn writeFn viewFn user reset mask desc } $registers {
    set r ""
    set w ""
    set v ""
    set u ""
    set m ""
    if { $readFn  != "-" } { set r "-readfunction  $readFn"   }
    if { $writeFn != "-" } { set w "-writefunction $writeFn"  }
    if { $viewFn  != "-" } { set v "-writefunction $viewFn"   }
    if { $user    != "-" } { set u "-userdata $user"          }
    if { $mask    != "-" } { set m "-writemask $mask"         }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $u $m"
    eval $cmd

    if { $reset != "-" } {
        imodeladdreset -mmregister $addBlock/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
}

#
# Register fields
#
imodeladdfield -mmregister $addBlock/s1 -name tdre    -bitoffset 7 -width 1
imodeladdfield -mmregister $addBlock/s1 -name tc      -bitoffset 6 -width 1
imodeladdfield -mmregister $addBlock/s1 -name rdrf    -bitoffset 5 -width 1
imodeladdfield -mmregister $addBlock/s1 -name idle    -bitoffset 4 -width 1

imodeladdfield -mmregister $addBlock/c2 -name tie     -bitoffset 7 -width 1
imodeladdfield -mmregister $addBlock/c2 -name tcie    -bitoffset 6 -width 1
imodeladdfield -mmregister $addBlock/c2 -name rie     -bitoffset 5 -width 1
imodeladdfield -mmregister $addBlock/c2 -name ilie    -bitoffset 4 -width 1
imodeladdfield -mmregister $addBlock/c2 -name te      -bitoffset 3 -width 1
imodeladdfield -mmregister $addBlock/c2 -name re      -bitoffset 2 -width 1

imodeladdfield -mmregister $addBlock/pfifo -name txfe       -bitoffset 7 -width 1
imodeladdfield -mmregister $addBlock/pfifo -name txfifosize -bitoffset 4 -width 3
imodeladdfield -mmregister $addBlock/pfifo -name rxfe       -bitoffset 3 -width 1
imodeladdfield -mmregister $addBlock/pfifo -name rxfifosize -bitoffset 0 -width 3

imodeladdfield -mmregister $addBlock/cfifo -name txflush    -bitoffset 7 -width 1
imodeladdfield -mmregister $addBlock/cfifo -name rxflush    -bitoffset 6 -width 1

imodeladdfield -mmregister $addBlock/bdh -name sbr    -bitoffset 0 -width 5

imodeladdfield -mmregister $addBlock/c4 -name brfa    -bitoffset 0 -width 5

#
# Net Ports
#
imodeladdnetport -name DirectWrite -type output
imodeladdnetport -name DirectRead  -type input  -updatefunction directReadCB
imodeladdnetport -name Interrupt   -type output
imodeladdnetport -name Reset       -type input  -updatefunction resetCB

#
# Formals
#
imodeladdformal   -name directReadWrite -type bool
iadddocumentation -name Description                                                                      \
          -text "Enable the use of the DirectRead and DirectWrite connections"

imodeladdformal   -name fifoSize  -type uns32
iadddocumentation -name Description                                                                      \
          -text "Size of fifos (default 128)"
imodeladdformal   -name moduleClkFreq  -type uns32
iadddocumentation -name Description                                                                      \
          -text "Frequency (in hertz) of module clock used in baud rate calculation (default=10.2 MHz)"

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS


