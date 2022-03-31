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

set vendor  intel.ovpworld.org
set library peripheral
set name    8253
set version 1.0

imodelnewperipheral -name $name -library $library -vendor $vendor -version $version \
     -constructor constructor \
     -nbyteregisters

iadddocumentation  \
    -name Description  \
    -text "Intel 8253 Programmable Interval Timer (PIT)"

iadddocumentation  \
    -name Limitations  \
    -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform.
           Not all modes are supported."

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Reference \
    -text "Intel 8253 Datasheet. MIPS Malta Platform Reference Guide."

#
# Contains only 2 address bits
#
# imodeladdbusslaveport -name bport1 -mustbeconnected -size 4
imodeladdbusslaveport -name bport1 -size 4

#
# Signals
#
imodeladdnetport -name clk%u  -type input  -loarray 0 -hiarray 2
imodeladdnetport -name gate%u -type input  -loarray 0 -hiarray 2
imodeladdnetport -name out%u  -type output -loarray 0 -hiarray 2

#
# A1 A0
#  0  0  Counter 0
#  0  1  Counter 1
#  1  0  Counter 2
#  1  1  Control Word Register
#
imodeladdaddressblock -port bport1 -name reg -width 8 -size 4 -offset 0

imodeladdmmregister -name CTR%u -width 8 -offset 0 -access rw -writefunction writeCTR -readfunction readCTR -loarray 0 -hiarray 2
imodeladdmmregister -name CNTL  -width 8 -offset 3 -access rw -writefunction writeCNTL -readfunction readCNTL

#
# Fields of Control Register
#
imodeladdfield -mmregister bport1/reg/CNTL -name BCD -bitoffset 0 -width 1
imodeladdfield -mmregister bport1/reg/CNTL -name M   -bitoffset 1 -width 3
imodeladdfield -mmregister bport1/reg/CNTL -name RW  -bitoffset 4 -width 2
imodeladdfield -mmregister bport1/reg/CNTL -name SC  -bitoffset 6 -width 2
