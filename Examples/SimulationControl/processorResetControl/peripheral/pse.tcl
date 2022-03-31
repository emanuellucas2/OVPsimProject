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
# NAME : 16450

imodelnewperipheral  \
    -name resetControl \
    -vendor example.ovpworld.org  \
    -library peripheral  \
    -version 1.0  \
    -imagefile pse.pse \
    -constructor constructor

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Description  \
    -text "Simple reset generation on control register write or when r read from socket"

iadddocumentation  \
    -name Limitations  \
    -text "This is an example"

iadddocumentation  \
	   -name Reference  \
	   -text "None"

# Slave port for control register
imodeladdbusslaveport -name SP -size 4
iadddocumentation -name Description -text "Register Slave Port"

# Address block for 32 bit register
imodeladdaddressblock -port SP -name ab -width 32  -offset 0 -size 4

# 32 bit register
imodeladdmmregister -addressblock SP/ab -name control -offset 0x00 -access rw  -writefunction controlRegisterWrite 
iadddocumentation -name Description -text "register to control reset lines"

imodeladdnetport -name resetOut1 -type output
iadddocumentation -name Description -text "Reset output signal 1"
imodeladdnetport -name resetOut2 -type output
iadddocumentation -name Description -text "Reset output signal 2"

# Standard formals when using BHM socket interface
imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
