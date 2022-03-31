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

set vendor  national.ovpworld.org
set library peripheral
set name    16550
set version 1.0

# 16550.include.tcl requires pseRoot set to the handle for the peripheral
set pseRoot [ \
  imodelnewperipheral \
    -name $name \
    -imagefile pse.pse \
    -vendor $vendor \
    -library $library \
    -version $version \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp \
  ]

iadddocumentation -handle $pseRoot -name Licensing  -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size 0x8  -mustbeconnected
imodeladdaddressblock -name ab     -size 0x8  -port bport1 -width 8

#
# Import 16550 base functions
#
# align the standard 16550 registers on byte boundaries
set REGISTERALIGN 1

# name of address block holding 16550 registers
set addBlock     "bport1/ab"

# include 16550 base functionality
set IMPERAS_HOME $env(IMPERAS_HOME)
source $IMPERAS_HOME/ImperasLib/source/ovpworld.org/modelSupport/uart16550/1.0/pse/16550.include.tcl
