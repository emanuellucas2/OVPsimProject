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

#
# iGen include file for the 16550 standard functionality provided in 16550.c.h
#
# Many UART peripherals implement a superset of the standard 16550 UART.
# This model support directory provides a model for the base 16550 functionality that
# may be extended in any model that includes it.
#
# This file should be included in the iGen source file for the peripheral, and it will define
# the registers, parameters and netports implemented by 16550.c.h.
#
# Caller must set pseRoot to handle for peripheral root
# Caller must set REGISTERALIGN to alignment of the 16550 registers (1 for byte, 4 for word, etc.)
# Caller must create an address block with at least 8*REGISTERALIGN bytes.
# Caller must set addBlock to name of address block that holds the 16550 registers in the first 8 locations
#

iadddocumentation -handle $pseRoot -name Description -text "16550 UART model"
iadddocumentation -handle $pseRoot -name Description -text "The serial input/output from the simulator is implemented using the Serial Device Support described in OVP BHM and PPM API Functions Reference, which describes the parameters that control how the model interacts with the host computer."
iadddocumentation -handle $pseRoot -name Description -text "Interrupts and FIFOs are supported."
iadddocumentation -handle $pseRoot -name Description -text "Registers are aligned on $REGISTERALIGN byte boundaries."

iadddocumentation -handle $pseRoot -name Limitations -text "Resolution of the baud rate is limited to the simulation time slice (aka quantum) size."
iadddocumentation -handle $pseRoot -name Limitations -text "Values written to the MCR are ignored. Loopback mode is not supported."
iadddocumentation -handle $pseRoot -name Limitations -text "The LSR is read-only. The model never sets the LSR 'Parity Error', 'Framing Error', 'Break Interrupt' or 'Error in RCVR FIFO' bits."
iadddocumentation -handle $pseRoot -name Limitations -text "The MSR 'Data Set Ready' and 'Clear To Send' bits are set at reset and all other MSR bits are cleared. MSR bits will only be changed by writes to the MSR and values written to the Modem Status Register do not effect the operation of the model."

iadddocumentation -handle $pseRoot -name Reference   -text "PC16550D Universal Asynchronous Receiver/Transmitter with FIFOs datasheet (http://www.ti.com/lit/ds/symlink/pc16550d.pdf)"

#
# Define standard 16550 registers
#

#   name          index  ac readFn      writeFn      viewFn      user reset   mask description   
set registers {
    rbr_dll       0x0    r  readRBR_DLL -            viewRBR_DLL -    0x00    -    "UART Receiver Buffer Register/Divisor Latch Low Read (LCR.DLAB=1)"
    thr_dll       0x0    w  -           writeTHR_DLL viewTHR_DLL -    0x00    -    "UART Transmitter Holding Register/Divisor Latch Low Write (LCR.DLAB=1)"
    ier_dlh       0x1    rw readIER_DLH writeIER_DLH viewIER_DLH -    0x00    -    "UART Interrupt Enable Register/Divisor Latch High (LCR.DLAB=1)"
    iir           0x2    r  readIIR     -            viewIIR     -    0x01    -    "UART Interrupt Identity Register"
    fcr           0x2    w  -           writeFCR     -           -    0x00    -    "UART FIFO Control Register"
    lcr           0x3    rw -           writeLCR     -           -    0x00    -    "UART Line Control Register"
    mcr           0x4    rw -           -            -           -    0x00    0x1f "UART MODEM Control Register"
    lsr           0x5    r  readLSR     -            viewLSR     -    -       -    "UART Line Status Register"
    msr           0x6    rw -           -            -           -    0xb0    -    "UART MODEM Status Register"
    scr           0x7    rw -           -            -           -    -       -    "UART Scratch Register"
}

foreach { rname index raccess readFn writeFn viewFn user reset mask desc } $registers {
    set r ""
    set w ""
    set v ""
    set u ""
    set m ""
    if { $readFn  != "-" } { set r "-readfunction  $readFn"   }
    if { $writeFn != "-" } { set w "-writefunction $writeFn"  }
    if { $viewFn  != "-" } { set v "-viewfunction  $viewFn"   }
    if { $user    != "-" } { set u "-userdata $user"          }
    if { $mask    != "-" } { set m "-writemask $mask"         }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset [expr $REGISTERALIGN * $index] -width 8 -access $raccess $r $w $v $u $m"
    eval $cmd
    
    if { $reset != "-" } {
        imodeladdreset -mmregister $addBlock/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
}

proc description { text } {
    iadddocumentation -name Description -text $text
}

#
# Register fields
#
imodeladdfield -mmregister $addBlock/ier_dlh -name erbfi    -bitoffset 0 -width 1
imodeladdfield -mmregister $addBlock/ier_dlh -name etbei    -bitoffset 1 -width 1
imodeladdfield -mmregister $addBlock/ier_dlh -name elsi     -bitoffset 2 -width 1
imodeladdfield -mmregister $addBlock/ier_dlh -name edssi    -bitoffset 3 -width 1

imodeladdfield -mmregister $addBlock/iir     -name intid    -bitoffset 0 -width 4
imodeladdfield -mmregister $addBlock/iir     -name fifoen   -bitoffset 6 -width 2

imodeladdfield -mmregister $addBlock/fcr     -name fifoEn       -bitoffset 0 -width 1
imodeladdfield -mmregister $addBlock/fcr     -name fifoRcvrRst  -bitoffset 1 -width 1
imodeladdfield -mmregister $addBlock/fcr     -name fifoXmitRst  -bitoffset 2 -width 1
imodeladdfield -mmregister $addBlock/fcr     -name dmaModeSel   -bitoffset 3 -width 1
imodeladdfield -mmregister $addBlock/fcr     -name fifoXmitTrig -bitoffset 4 -width 2
imodeladdfield -mmregister $addBlock/fcr     -name fifoRcvrTrig -bitoffset 6 -width 2

imodeladdfield -mmregister $addBlock/lcr     -name dls          -bitoffset 0 -width 2
imodeladdfield -mmregister $addBlock/lcr     -name stop         -bitoffset 2 -width 1
imodeladdfield -mmregister $addBlock/lcr     -name pen          -bitoffset 3 -width 1
imodeladdfield -mmregister $addBlock/lcr     -name eps          -bitoffset 4 -width 1
imodeladdfield -mmregister $addBlock/lcr     -name stick        -bitoffset 5 -width 1
imodeladdfield -mmregister $addBlock/lcr     -name brk          -bitoffset 6 -width 1
imodeladdfield -mmregister $addBlock/lcr     -name dlab         -bitoffset 7 -width 1

imodeladdfield -mmregister $addBlock/lsr     -name dr           -bitoffset 0 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name oe           -bitoffset 1 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name pe           -bitoffset 2 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name fe           -bitoffset 3 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name bi           -bitoffset 4 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name thre         -bitoffset 5 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name temt         -bitoffset 6 -width 1
imodeladdfield -mmregister $addBlock/lsr     -name rfe          -bitoffset 7 -width 1

#
# Net Ports
#
imodeladdnetport -name reset_uart  -type input -updatefunction resetCB
imodeladdnetport -name intOut      -type output

#
# Parameters
# 
imodeladdformal -name uart16450  -type bool
description "Run in 16450 mode (no FIFOs)"

imodeladdformal -name fifoSize  -type uns32
description "Size of fifos"

imodeladdformal -name refClkFreq  -type uns32
description "Frequency (in hertz) of reference clock rate used in baud rate calculation"

imodeladdformal  -name simulatebaud -type bool
description "Set to true to simulate baud delay determined by the Divisor Latch register value and reference clock frequency."
description "Set to false to run without delay - next read data is made available immediately upon read of Receiver Buffer Register."
description "Defaults to false"

imodeladdformal  -name charmode -type bool
description "Set to true when the port is used to connect to a Telnet program and character mode is desired rather than the default Telnet line mode."
description "When set to true a Telnet command sequence is sent at startup that configures the Telnet program into character mode. In addition null bytes are stripped from the data received." 

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
