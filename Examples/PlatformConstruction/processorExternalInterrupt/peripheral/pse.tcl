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
    -name simpleTimer \
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
    -text "Simple timer tick generation"

iadddocumentation  \
    -name Limitations  \
    -text "This is an example"

iadddocumentation  \
	   -name Reference  \
	   -text "None"

# Slave port for register
imodeladdbusslaveport -name SP -size 0x4 -mustbeconnected
iadddocumentation -name Description -text "Register Slave Port"
   
# Address block for 32 bit register
imodeladdaddressblock -port SP -name ab -width 32  -offset 0 -size 0x4
   
# registers
imodeladdmmregister -addressblock SP/ab -name intAck  -offset 0x00 -access w  -writefunction intAck 
iadddocumentation -name Description -text "interrupt acknowledge" -handle SP/ab/intAck
           
imodeladdnetport -name tickOut -type output
iadddocumentation -name Description -text "Timer tick"

set defaultRate 10000
imodeladdformal -name rate -type Uns32 -defaultvalue $defaultRate
iadddocumentation -name Description -text "Timer tick rate in microSeconds (default $defaultRate uS / [expr $defaultRate / 1000000] S)"
