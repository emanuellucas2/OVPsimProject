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

set vendor  ti.ovpworld.org
set library peripheral
set name    UartInterface
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation -name Description -text "
UART: Universal Asynchronous Receiver Transmitter
This model contains an accurate Register set interface for the TI Stellaris ARM Cortex-M3 based device."

iadddocumentation -name Limitations -text "
The functionality of this model is limited. 
Basic status flag setting allows character reception and transmission."

iadddocumentation -name Reference -text "
FreeRTOS Cortex-M3 / GCC Port LM3S102 with GCC for Luminary Micros Stellaris microcontrollers
http://www.freertos.org/portcortexgcc.html"

iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

imodeladdformalmacro -name  BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name  BHM_RECORD_REPLAY_FORMALS

imodeladdformal   -name loopback -type bool
iadddocumentation -name Description                                                                      \
                  -text "When enabled transmit data is looped back to the receiver data register." 

imodeladdbusslaveport -name bport1 -mustbeconnected -size 0x1000
imodeladdaddressblock -name ab -port bport1 -size 0x1000 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name irq -type output

set addBlock     "bport1/ab"
set regWidth     32

#   name        offset ac description  readFn           writeFn       user    reset
set registers {                                                       
    dr        0x00      rw UARTDR        readDR         writeDR       -       0x00
    rsrecr    0x04      rw UARTRSRECR    readSRRECR     writeSRRECR   -       0x00
    fr        0x18      r  UARTFR        readSR         -             -       0x90
    fbrd      0x24      rw UARTFBDR      -              -             -       0x00
    ibrd      0x28      rw UARTIBRD      -              -             -       0x00
    lcrh      0x2c      rw UARTLCRH      -              -             -       0x00
    ctl       0x30      rw UARTLCTL      readCTL        writeCTL      -       0x00
    ifls      0x34      rw UARTIFLS      -              -             -       0x12

    im        0x38      rw UARTIM        readIM         writeIM       -       0x00
    ris       0x3c      rw UARTRIS       readRIS        writeRIS      -       0x0f
    mis       0x40      rw UARTMIS       readMIS        writeMIS      -       0x00
    icr       0x44      rw UARTICR       readICR        writeICR      -       0x00
}

foreach { rname offset raccess  desc readFn writeFn user rreset } $registers {
    if { $readFn != "-" } {
	set r "-readfunction $readFn"
    } else { set r "" }
    if { $writeFn != "-" } {
	set w "-writefunction $writeFn"
    } else { set w "" }
    if { $user != "-" } {
	set u "-userdata $user"
    } else { set u "" }
    set cmd "imodeladdmmregister -width 32 -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $u"
	
    eval $cmd
    imodeladdreset -mmregister "$addBlock/$rname" -name reset -value $rreset
    if { $desc != "-" } {
	iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }
}

#id codes
set idRegBase 0xFD0
imodeladdmmregister -name pid0 -offset [expr ( 0 * 4) + $idRegBase ] -addressblock $addBlock -access r
imodeladdmmregister -name pid1 -offset [expr ( 1 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name pid2 -offset [expr ( 2 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name pid3 -offset [expr ( 3 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name pid4 -offset [expr ( 4 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name pid5 -offset [expr ( 5 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name pid6 -offset [expr ( 6 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name pid7 -offset [expr ( 7 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name cid0 -offset [expr ( 8 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name cid1 -offset [expr ( 9 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name cid2 -offset [expr (10 * 4) + $idRegBase ] -addressblock $addBlock -access r 
imodeladdmmregister -name cid3 -offset [expr (11 * 4) + $idRegBase ] -addressblock $addBlock -access r 

imodeladdreset -mmregister "$addBlock/pid0" -name reset -value 0x11
imodeladdreset -mmregister "$addBlock/pid1" -name reset -value 0x00
imodeladdreset -mmregister "$addBlock/pid2" -name reset -value 0x18
imodeladdreset -mmregister "$addBlock/pid3" -name reset -value 0x01
imodeladdreset -mmregister "$addBlock/pid4" -name reset -value 0x00
imodeladdreset -mmregister "$addBlock/pid5" -name reset -value 0x00
imodeladdreset -mmregister "$addBlock/pid6" -name reset -value 0x00
imodeladdreset -mmregister "$addBlock/pid7" -name reset -value 0x00
imodeladdreset -mmregister "$addBlock/cid0" -name reset -value 0x0d
imodeladdreset -mmregister "$addBlock/cid1" -name reset -value 0xf0
imodeladdreset -mmregister "$addBlock/cid2" -name reset -value 0x05
imodeladdreset -mmregister "$addBlock/cid3" -name reset -value 0xb1

 # UARTDR
imodeladdfield -mmregister $addBlock/dr -name OE    -bitoffset 11 -width 1
imodeladdfield -mmregister $addBlock/dr -name BE    -bitoffset 10 -width 1
imodeladdfield -mmregister $addBlock/dr -name PE    -bitoffset  9 -width 1
imodeladdfield -mmregister $addBlock/dr -name FE    -bitoffset  8 -width 1
imodeladdfield -mmregister $addBlock/dr -name DATA  -bitoffset  0 -width 8

# UARTRSRECR
imodeladdfield -mmregister $addBlock/rsrecr -name OE    -bitoffset  3 -width 1
imodeladdfield -mmregister $addBlock/rsrecr -name BE    -bitoffset  2 -width 1
imodeladdfield -mmregister $addBlock/rsrecr -name PE    -bitoffset  1 -width 1
imodeladdfield -mmregister $addBlock/rsrecr -name FE    -bitoffset  0 -width 1

# UARTFR
imodeladdfield -mmregister $addBlock/fr -name TXFE  -bitoffset  7 -width 1
imodeladdfield -mmregister $addBlock/fr -name RXFF  -bitoffset  6 -width 1
imodeladdfield -mmregister $addBlock/fr -name TXFF  -bitoffset  5 -width 1
imodeladdfield -mmregister $addBlock/fr -name RXFE  -bitoffset  4 -width 1
imodeladdfield -mmregister $addBlock/fr -name BUSY  -bitoffset  3 -width 1

# UARTIBRD
imodeladdfield -mmregister $addBlock/ibrd -name DIVINT -bitoffset  0 -width 16

# UARTFBRD
imodeladdfield -mmregister $addBlock/fbrd -name DIVFRAC -bitoffset  0 -width 6

# UARTLCRH
imodeladdfield -mmregister $addBlock/lcrh -name SPS  -bitoffset  7 -width 1
imodeladdfield -mmregister $addBlock/lcrh -name WLEN -bitoffset  5 -width 2
imodeladdfield -mmregister $addBlock/lcrh -name FEN  -bitoffset  4 -width 1
imodeladdfield -mmregister $addBlock/lcrh -name STP2 -bitoffset  3 -width 1
imodeladdfield -mmregister $addBlock/lcrh -name EPS  -bitoffset  2 -width 1
imodeladdfield -mmregister $addBlock/lcrh -name PEN  -bitoffset  1 -width 1
imodeladdfield -mmregister $addBlock/lcrh -name BRK  -bitoffset  0 -width 1
 
# UARTCTL
imodeladdfield -mmregister $addBlock/ctl -name RXE    -bitoffset  9 -width 1
imodeladdfield -mmregister $addBlock/ctl -name TXE    -bitoffset  8 -width 1
imodeladdfield -mmregister $addBlock/ctl -name LBE    -bitoffset  7 -width 1
imodeladdfield -mmregister $addBlock/ctl -name UARTEN -bitoffset  0 -width 1
 
# UARTIFLS
imodeladdfield -mmregister $addBlock/ifls -name RXIFLSEL -bitoffset  3 -width 3
imodeladdfield -mmregister $addBlock/ifls -name TXIFLSEL -bitoffset  0 -width 3

# UARTIM
imodeladdfield -mmregister $addBlock/im -name OEIM  -bitoffset  6 -width 1
imodeladdfield -mmregister $addBlock/im -name BEIM  -bitoffset  5 -width 1
imodeladdfield -mmregister $addBlock/im -name PEIM  -bitoffset  4 -width 1
imodeladdfield -mmregister $addBlock/im -name FEIM  -bitoffset  3 -width 1
imodeladdfield -mmregister $addBlock/im -name RTIM  -bitoffset  2 -width 1
imodeladdfield -mmregister $addBlock/im -name TXIM  -bitoffset  1 -width 1
imodeladdfield -mmregister $addBlock/im -name RXIM  -bitoffset  0 -width 1
  
# UARTRIS
imodeladdfield -mmregister $addBlock/ris -name OERIS  -bitoffset  6 -width 1
imodeladdfield -mmregister $addBlock/ris -name BERIS  -bitoffset  5 -width 1
imodeladdfield -mmregister $addBlock/ris -name PERIS  -bitoffset  4 -width 1
imodeladdfield -mmregister $addBlock/ris -name FERIS  -bitoffset  3 -width 1
imodeladdfield -mmregister $addBlock/ris -name RTRIS  -bitoffset  2 -width 1
imodeladdfield -mmregister $addBlock/ris -name TXRIS  -bitoffset  1 -width 1
imodeladdfield -mmregister $addBlock/ris -name RXRIS  -bitoffset  0 -width 1

# UARTMIS
imodeladdfield -mmregister $addBlock/mis -name OEMIS  -bitoffset  6 -width 1
imodeladdfield -mmregister $addBlock/mis -name BEMIS  -bitoffset  5 -width 1
imodeladdfield -mmregister $addBlock/mis -name PEMIS  -bitoffset  4 -width 1
imodeladdfield -mmregister $addBlock/mis -name FEMIS  -bitoffset  3 -width 1
imodeladdfield -mmregister $addBlock/mis -name RTMIS  -bitoffset  2 -width 1
imodeladdfield -mmregister $addBlock/mis -name TXMIS  -bitoffset  1 -width 1
imodeladdfield -mmregister $addBlock/mis -name RXMIS  -bitoffset  0 -width 1
 
# UARTICR
imodeladdfield -mmregister $addBlock/icr -name OEIC  -bitoffset  6 -width 1
imodeladdfield -mmregister $addBlock/icr -name BEIC  -bitoffset  5 -width 1
imodeladdfield -mmregister $addBlock/icr -name PEIC  -bitoffset  4 -width 1
imodeladdfield -mmregister $addBlock/icr -name FEIC  -bitoffset  3 -width 1
imodeladdfield -mmregister $addBlock/icr -name RTIC  -bitoffset  2 -width 1
imodeladdfield -mmregister $addBlock/icr -name TXIC  -bitoffset  1 -width 1
imodeladdfield -mmregister $addBlock/icr -name RXIC  -bitoffset  0 -width 1
