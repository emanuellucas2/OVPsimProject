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
set name    usecCounter
set version 1.0

imodelnewperipheral \
    -name $name \
    -imagefile pse.pse \
    -vendor $vendor \
    -library $library \
    -version $version 

iadddocumentation -name Description -text "Provides a register with a Microsecond Counter"
    
iadddocumentation -name Limitations -text "Changes at simulator resolution"
    
iadddocumentation -name Reference   -text "None"
    
iadddocumentation -name Licensing  -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size 4 -mustbeconnected 

imodeladdaddressblock -name ab -width 32 -offset 0 -size 4

imodeladdmmregister   -name USEC    -addressblock bport1/ab  -offset  0   -width 32  -access r  -readfunction rdUSEC

