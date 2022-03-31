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
# NAME : dw-apb-uart

imodelnewperipheral  \
    -name dw-apb-uart \
    -vendor altera.ovpworld.org  \
    -library peripheral  \
    -version 1.0  \
    -constructor constructor \
    -destructor  destructor
                
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "Model of dw-apb-uart UART for CycloneV platform."

iadddocumentation -name Limitations -text "No modeling of baudrate."
iadddocumentation -name Limitations -text "No modem support (DTR etc)."
iadddocumentation -name Limitations -text "No support for parity."
iadddocumentation -name Limitations -text "No means to simulate errors."
iadddocumentation -name Limitations -text "Derived from national.ovpworld.org 16450 model. Just enough to do basic tty capabilities."
iadddocumentation -name Limitations -text "Only first 8 registers implemented."  

iadddocumentation  -name Reference  -text "Cyclone V Device Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30"

imodeladdbusslaveport -name bport1 -mustbeconnected -size 0x1000

iadddocumentation  \
    -name Description  \
    -text "Byte:wide access to control and status registers."

imodeladdnetport -name intOut -type output
iadddocumentation -name Description -text "Interrupt output."
         
imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

imodeladdformal -name uart16550 -type bool
iadddocumentation  -name Description  -text "Enable 16550 mode (with FIFOS) - not implemented yet."

imodeladdformal -name simulatebaud -type bool
iadddocumentation  -name Description  -text "If true, transmit at the programmed baud rate (the default is to transmit without any delay)."

imodeladdformal -name defaultbaud -type uns32 -defaultvalue 9
iadddocumentation  -name Description  -text "Set the default baud rate multiplier. Default is 9."

imodeladdformal -name charmode -type bool
iadddocumentation  -name Description  -text "Puts the telnet server into char mode Default is line mode"
 
