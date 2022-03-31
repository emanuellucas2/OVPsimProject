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


set vendor  andes.ovpworld.org
set library peripheral
set name    ATCUART100
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Andes UART"
iadddocumentation -name Limitations -text "DMA not supported"
iadddocumentation -name Reference   -text "Andes AE350 Platform User Manual"


set port  bport1
set block ab
set size  0x40
set width 32

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size} -defaultfunctions
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width ${width}

set registers {
    IDREV       0x00000000 32 r  0x02010000 -         -          -  "ID and Revision Register"
    {    ID 16 16   "ID Number of ACTUART100"
         MAJOR 4 12 "Major Revision Number"
         MINOR 0  4 "Minor Revision Number"
    }
    CFG         0x00000010 32 r  0x00000000 -         -          -  "Hardware Configure Register"
    {    FIFO_DEPTH 0 2 "Depth of Rx and Tx FIFO"
    }
    OSCR        0x00000014 32 rw 0x00000000 -         -          0x0000001f  "Over Sample Control Register"
    {    OSC        0 5 "Over-sample Control"
    }
    RBR_DLL 0x00000020 32 r  0x00000000 rdRBR_DLL -          -  "Receiver Buffer Register / Divisor Latch LSB" -
    THR_DLL 0x00000020 32  w 0x00000000 -         wrTHR_DLL  -  "Transmitter Holding Register / Divisor Latch LSB" -
    IER_DLM     0x00000024 32 rw 0x00000001 rdIER_DLM wrIER_DLM  -  "Interrupt Enable Register / Divisor Latch MSB"  
    {   ERBI   0 1 "Receive Data Ready Interrupt Enable"
        ETHEI  1 1 "Transmitter Holding Register Interrupt Enable"
        ELSI   2 1 "Receive Line Status Interrupt Enable"
        EMSI   3 1 "Modem Status Interrupt Enable"
    }
    IIR         0x00000028 32 r  0x00000000 rdIIR     -      -  "Interrupt Identification Register" 
    {   FIFOED      6 2  "FIFOs Enabled"
        INTRID      0 4  "Interrupt ID"
    }
    FCR         0x00000028 32  w 0x00000000 -         wrFCR      -  "FIFO ControlRegister" 
    {   RFIFOT     6 2  "Receiver FIFO Trigger Level"
        TFIFOT     4 2  "Transmitter FIFO Trigger Level"
        DMAE       3 1  "DMA Enable"
        TFIFORST   2 1  "Transmitter FIFO Reset"
        RFIFORST   1 1  "Receiver FIFO Reset"
        FIFOE      0 1  "FIFO Enable"
    }
    LCR         0x0000002c 32 rw 0x00000000 -         wrLCR     -  "Line Control Register"
    {   DLAB        7 1 "Divisor Latch Access Bit"
        BC          6 1 "Break Control"
        SPS         5 1 "Stick Parity"
        EPS         4 1 "Even Parity Select"
        PEN         3 1 "Parity Enable"
        STB         2 1 "Number of STOP bits"
        WLS         0 2 "Word Length Setting"
    }
    MCR         0x00000030 32 rw 0x00000000 -         -        -  "Modem Control Register" -
    LSR         0x00000034 32 rw 0x00000060 rdLSR     -        -  "Line Status Register"
    {   RDR    0  1   "Data Ready"
        OE     1  1   "Overrun Error"
        PE     2  1   "Parity Error"
        FE     3  1   "Framing Error"
        LBreak 4  1   "Line Break"
        THRE   5  1   "THR/FIFO Empty"
        TEMT   6  1   "THR/FIFO and TFR Empty"
        ERRF   7  1   "Receive FIFO Data Error"
    }
    MSR         0x00000038 32 r  0x00000000 -         -        -    "Modem Status Register"  -
    SCR         0x0000003c 32 rw 0x00000000 -         -        0xff "Scratch Register"       -
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width ${width} -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
  } else {
    set command "${command} -readfunction $readFunc"
  }
  
  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
  } else {
    set command "${command} -writefunction $writeFunc"
  }

  if { $writeMask != "-" } {
    set command "${command} -writemask $writeMask"
  }
  
  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w d } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        if { $d != "-" } {
            iadddocumentation  -handle ${port}/${block}/$rname/$n \
                           -name Description  \
                           -text $d
        }
    }
  }
  
  imodeladdreset -mmregister ${port}/${block}/$rname -name reset -value $reset
}

imodeladdnetport -name reset -type input -updatefunction resetCB
iadddocumentation -name Description -text "Reset signal"

imodeladdnetport -name intOut -type output
iadddocumentation -name Description -text "Interrupt signal"

#
# Parameters
# 
imodeladdformal -name uart16450  -type bool
iadddocumentation -name Description -text "Run in 16450 mode (no FIFOs)"

imodeladdformal -name fifoSize  -type uns32
iadddocumentation -name Description -text "Size of fifos"

imodeladdformal -name refClkFreq  -type uns32
iadddocumentation -name Description -text "Frequency (in hertz) of reference clock rate used in baud rate calculation"

imodeladdformal  -name simulatebaud -type bool
iadddocumentation -name Description -text "Set to true to simulate baud delay determined by the Divisor Latch register value and reference clock frequency."
iadddocumentation -name Description -text "Set to false to run without delay - next read data is made available immediately upon read of Receiver Buffer Register."
iadddocumentation -name Description -text "Defaults to false"

imodeladdformal  -name charmode -type bool
iadddocumentation -name Description -text "Set to true when the port is used to connect to a Telnet program and character mode is desired rather than the default Telnet line mode."
iadddocumentation -name Description -text "When set to true a Telnet command sequence is sent at startup that configures the Telnet program into character mode. In addition null bytes are stripped from the data received." 

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
