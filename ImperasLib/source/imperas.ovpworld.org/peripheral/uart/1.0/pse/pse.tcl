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

set vendor  imperas.ovpworld.org
set library peripheral
set name    uart
set version 1.0

imodelnewperipheral \
    -name $name \
    -imagefile pse.pse \
    -vendor $vendor \
    -library $library \
    -version $version \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "Simple UART model"
    
iadddocumentation -name Limitations -text "Provides the base functionality to allow read/write character communication."
    
iadddocumentation -name Reference   -text "Example Linux Kernel Driver"
    
iadddocumentation -name Licensing  -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size 0x20  -mustbeconnected
imodeladdaddressblock -name ab     -size 0x20  -port bport1 -width 8

set REGISTERALIGN 4

#
# Define registers
#

#   name     index  ac readFn writeFn viewFn user reset  mask description   
set registers {
    rbr_dll    0    r  readRBR_DLL -            viewRBR_DLL -    0x00    -    "UART Receiver Buffer Register"
    thr_dll    1    w  -           writeTHR_DLL viewTHR_DLL -    0x00    -    "UART Transmitter Register"
    sz         2    r  readSZ      -            -           -    0x00    -    "UART Receive FIFO Fill Size Register"
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

    set cmd "imodeladdmmregister -name $rname -addressblock bport1/ab -offset [expr $REGISTERALIGN * $index] -width 8 -access $raccess $r $w $v $u $m"
    eval $cmd
    
    if { $reset != "-" } {
        imodeladdreset -mmregister bport1/ab/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc -handle bport1/ab/$rname
}

#
# Net Ports
#
imodeladdnetport -name reset  -type input -updatefunction resetCB
imodeladdnetport -name intOut -type output

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
