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

set vendor  renesas.ovpworld.org
set library peripheral
set name    rng
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Random Number Generator (RNG)"
iadddocumentation -name Limitations -text "Register View Model Only"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# Slave port
#
imodeladdbusslaveport -name RNGP0 -size 2

#
# Registers
#
imodeladdaddressblock -name reg0 -port RNGP0 -size 2 -offset 0 -width 16

#
# RNGP0
#
imodeladdmmregister -addressblock RNGP0/reg0 -name RNG -width 16 -offset 0 -access r -readfunction readRNG

#
# Resets
#
imodeladdreset -mmregister RNGP0/reg0/RNG -name IRESET -value 0x0001
