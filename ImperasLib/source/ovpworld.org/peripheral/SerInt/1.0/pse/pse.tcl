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

# pse.tcl
# The serial interrupt control registers in the FDC 37M817 SuperIO device.

set name    SerInt
set vendor  ovpworld.org
set library peripheral
set version 1.0

imodelnewperipheral       \
    -name      $name      \
    -vendor    $vendor    \
    -library   $library   \
    -version   $version   \
    -releasestatus ovp        \
    -visibility    visible \
    -constructor constructor \
    -destructor  destructor
	
    iadddocumentation -name Description -text "The serial interrupt control registers in the FDC 37M817 SuperIO device."
    iadddocumentation -name Limitations -text "This is a register description only. The model does not contain any functionality."
    iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
    iadddocumentation -name Reference   -text "SMsC FDC 37M817 SuperIO device datasheet"


    imodeladdbusslaveport -name bport1 -mustbeconnected -size 0x4

    imodeladdaddressblock -name A -port bport1 -size 0x4 -offset 0 -width 32

    imodeladdmmregister -addressblock bport1/A -name R0 -width 32 -offset 0 -access rw
    imodeladdreset      -mmregister bport1/A/R0 -name resetNet -value 0

