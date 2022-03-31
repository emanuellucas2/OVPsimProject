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

# A big hole in the middle, a few regs at each end
set range 0x1000

imodelnewperipheral \
    -imagefile pse.pse \
    -name UartPL011 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0  \
    -constructor constructor \
    -destructor closeDown \
    -releasestatus ovp
    
iadddocumentation -name Description -text "ARM PL011 UART"
iadddocumentation -name Limitations -text "This is not a complete model of the PL011. There is no modeling of physical aspects of the UART, such as baud rates etc."
iadddocumentation -name Reference   -text "ARM PrimeCell UART (PL011) Technical Reference Manual (ARM DDI 0183)"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -port bport1 -width 32 -size $range

imodeladdformal -name variant -type enumeration
    imodeladdenumeration -formal variant -name ARM
    imodeladdenumeration -formal variant -name LUMINARY

imodeladdformal -name charmode -type boolean

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

set addBlock     "bport1/ab"
set regWidth     32

#   name        offset ac description  readFn   writeFn   bits
set registers {
    dr          0      rw UARTDR       readDR   writeDR   0
    ecr         1      rw UARTECR      readECR  writeECR  { OE 3 }
    flags       6      r  UARTFR       0        0         { TXFE 7 RXFF 6 TXFF 5 RXFE 4 }
    ilpr        8      rw UARTILPR     0        0         0
    ibrd        9      rw UARTIBRD     0        0         0
    vbrd        10     rw UARTFBRD     0        0         0
    lcr         11     rw UARTLCR_H    0        writeLCR  { FEN 4 }
    cr          12     rw UARTCR       0        0         0
    ifl         13     rw UARTIFS      0        writeIFL  0
    int_enabled 14     rw UARTIMSC     0        writeIMSC 0
    int_level   15     r  UARTRIS      0        0         { TX 5 RX 4 }
    mis         16     r  UARTMIS      readMIS  0         0
    icr         17      w UARTDICR     0        writeICR  0
    dmacr       18     rw UARTDMACR    0        writeDMA  0
}

foreach { rname roffset raccess  desc readFn writeFn  bits } $registers {

    set offset [expr 4 * $roffset]

    if { "$raccess" == "r" && $readFn == 0 } {
        # add a memory rather than callback (better performance when polled)
        imodeladdlocalmemory -name $rname -addressblock $addBlock -offset $offset -access r -size 4
    } else {
        if { $readFn != 0 } {
            set r "-readfunction $readFn"
        } else { set r "" }
        if { $writeFn != 0 } {
            set w "-writefunction $writeFn"
        } else { set w "" }

        set cmd "imodeladdmmregister -width 32 -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w"
    	
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

imodeladdnetport -name irq -type output

#
# UART Direct Read/Write
#

# Net Ports
imodeladdnetport -name DirectWrite -type output
imodeladdnetport -name DirectRead  -type input  -updatefunction directReadCB

# Formals
imodeladdformal   -name directReadWrite -type bool
iadddocumentation -name Description                                                                      \
          -text "Enable the use of the DirectRead and DirectWrite connections"
