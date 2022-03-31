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

set vendor  sifive.ovpworld.org
set library peripheral
set name    UART
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version \
                    -constructor constructor -releasestatus ovp

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Sifive UART"
iadddocumentation -name Limitations -text "When simulatebaud parameter is set to true baud rate delays are modeled for receive only, not transmit. Data always sent immediately."
iadddocumentation -name Reference   -text "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)"

set portName    bport1
set addrBlkName ab

imodeladdbusslaveport -name ${portName} -size 0x1C

imodeladdaddressblock -name ${addrBlkName} -port ${portName} -size 0x1C -offset 0x00000000 -width 32

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name txdata -offset 0x00 -access rw -writefunction txdataWrite -readfunction txdataRead -viewfunction txdataView -writemask 0x800000ff
    imodeladdfield -name DATA   -bitoffset  0 -width 8  
    imodeladdfield -name FULL   -bitoffset 31 -width 1  

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name rxdata -offset 0x04 -access r -readfunction rxdataRead
    imodeladdfield -name DATA   -bitoffset  0 -width 8  
    imodeladdfield -name EMPTY  -bitoffset 31 -width 1  

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name txctrl -offset 0x08 -access rw -writefunction txctrlWrite -writemask 0x00070003
    imodeladdfield -name TXEN   -bitoffset  0 -width 1  
    imodeladdfield -name NSTOP  -bitoffset  1 -width 1  
    imodeladdfield -name TXCNT  -bitoffset 16 -width 3  

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name rxctrl -offset 0x0C -access rw -writefunction rxctrlWrite -writemask 0x00070001
    imodeladdfield -name RXEN   -bitoffset  0 -width 1  
    imodeladdfield -name RXCNT  -bitoffset 16 -width 3  

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name ie     -offset 0x10 -access rw -writefunction ieWrite
    imodeladdfield -name TXWM   -bitoffset  0 -width 1  
    imodeladdfield -name RXWM   -bitoffset  1 -width 1  

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name ip     -offset 0x14 -access r -readfunction ipRead
    imodeladdfield -name TXWM   -bitoffset  0 -width 1  
    imodeladdfield -name RXWM   -bitoffset  1 -width 1  

imodeladdmmregister -addressblock ${portName}/${addrBlkName} -name div    -offset 0x018 -access rw -writefunction divWrite
    imodeladdfield -name DIV    -bitoffset  0 -width 20 
    imodeladdreset -name reset  -value 289              

imodeladdnetport -name intOut -type output
imodeladdnetport -name reset  -type input  -updatefunction resetCB

imodeladdformal  -name simulatebaud -type bool
iadddocumentation -name Description -text "Set to true to simulate baud delay determined by the div register value and reference clock frequency."
iadddocumentation -name Description -text "Set to false to run without delay - next read data is made available immediately upon read of Receiver Buffer Register."
iadddocumentation -name Description -text "Defaults to false"

imodeladdformal  -name charmode -type bool
iadddocumentation -name Description -text "Set to true when the port is used to connect to a Telnet program and character mode is desired rather than the default Telnet line mode."
iadddocumentation -name Description -text "When set to true a Telnet command sequence is sent at startup that configures the Telnet program into character mode. In addition null bytes are stripped from the data received." 

imodeladdformal -name refClkFreq  -type uns32 -defaultvalue 33333333
iadddocumentation -name Description -text "Frequency (in hertz) of reference clock rate used in baud rate calculation"

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
