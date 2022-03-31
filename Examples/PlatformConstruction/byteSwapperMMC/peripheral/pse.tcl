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
#
# Test peripheral. 4 registers of 4 bytes each.
#

imodelnewperipheral         \
    -name      Simple32     \
    -vendor    ovpworld.com \
    -library   peripheral   \
    -version   1.0          \
    -imagefile pse.pse      \
    -constructor init

imodeladdbusslaveport -name sp1   -mustbeconnected -size 0x10

    imodeladdaddressblock -name ab1 -port  sp1 -size 0x10 -width 32

    imodeladdmmregister -addressblock sp1/ab1 -name r0 -access r -offset 0
    imodeladdreset -name reset -mmregister sp1/ab1/r0 -value 0x01020304

    imodeladdmmregister -addressblock sp1/ab1 -name r1 -access r -offset 4
    imodeladdreset -name reset -mmregister sp1/ab1/r1 -value 0x11121314

    imodeladdmmregister -addressblock sp1/ab1 -name r2 -access r -offset 8
    imodeladdreset -name reset -mmregister sp1/ab1/r2 -value 0x21222324

    imodeladdmmregister -addressblock sp1/ab1 -name r3 -access r -offset 12
    imodeladdreset -name reset -mmregister sp1/ab1/r3 -value 0x31323334

imodeladdnetport -name reset -type input -updatefunction reset