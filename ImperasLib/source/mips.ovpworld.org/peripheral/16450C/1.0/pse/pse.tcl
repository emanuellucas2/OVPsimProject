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
# NAME : 16450C

imodelnewperipheral  \
                -name    16450C  \
                -vendor  mips.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -releasestatus ovp \
                -constructor constructor \
                -destructor  destructor
                

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Model of 16550/16450 UART."
iadddocumentation  \
                -name Description  \
                -text "Special version with register addresses for MIPS MALTA C-BUS."
iadddocumentation  \
                -name Description  \
                -text "Connects to a bus by a slave port and optionally to a processor by an interrupt signal."
iadddocumentation  \
                -name Description  \
                -text "The serial input/output ports are modelled by socket connection which must be attached to a process outside the simulation environment."
iadddocumentation  \
                -name Description  \
                -text "Note that on start:up, the UART model will block the simulator, pending a connection to the socket."

iadddocumentation  \
                -name Limitations  \
                -text "No modelling of baud:rate."
iadddocumentation  \
                -name Limitations  \
                -text "No modem support (DTR etc)."
iadddocumentation  \
                -name Limitations  \
                -text "No support for parity."
iadddocumentation  \
                -name Limitations  \
                -text "No means to simulate errors."

iadddocumentation  \
                -name Reference  \
                -text "MIPS Malta Datasheet"

imodeladdbusslaveport -name bport1  -mustbeconnected   -size 0x40

iadddocumentation  \
                -name Description  \
                -text "Byte:wide access to control and status registers."

imodeladdnetport -name intOut -type output
iadddocumentation -name Description -text "Interrupt output."

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

imodeladdformal -name uart16550 -type bool
iadddocumentation  -name Description  -text "Enable 16550 mode (with FIFOS)"

imodeladdformal -name simulatebaud -type bool
iadddocumentation  -name Description  -text "If true, transmit at the programmed baud rate (the default is to transmit without any delay)."

imodeladdformal -name defaultbaud -type uns32 -defaultvalue 9
iadddocumentation  -name Description  -text "Set the default baud rate multiplier. Default is 9."

imodeladdformal -name charmode -type bool
iadddocumentation  -name Description  -text "Puts the telnet server into char mode Default is line mode"
