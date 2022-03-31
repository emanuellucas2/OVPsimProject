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

imodelnewperipheral  \
    -name        dynamicPortPSE \
    -vendor      test.ovpworld.org  \
    -library     peripheral \
    -version     1.0 \
    -constructor constructor \
    -destructor  destructor  \
    -nbyteregisters

# Dynamic slave port connection
imodeladdbusslaveport -name hostif -size 4 -mustbeconnected -remappable

# Address block
imodeladdaddressblock -name ab -port hostif -width 32  -offset 0x0 -size 4

# Register
imodeladdmmregister -name remap  -addressblock hostif/ab -offset 0x0  -access rw -writefunction writeRemap

# Register reset values
imodeladdreset -name reset -mmregister hostif/ab/remap   -value 0x10000000
