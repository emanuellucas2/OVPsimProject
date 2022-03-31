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
set name    brg
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas BRG Baud Rate Generator"
iadddocumentation -name Limitations -text "Fully Supported"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# PCLK formal container
#
imodeladdformal -name PCLK -type uns32

#
# Signal outputs
#
foreach pin {BRGOUT INTBRG} {
    imodeladdnetport -name ${pin} -type output
}

#
# Slave port
#
imodeladdbusslaveport -name BRGP0 -size 2

#
# Registers
#
imodeladdaddressblock -name reg0 -port BRGP0 -size 2 -offset  0 -width 8

#
# Registers
#
imodeladdmmregister -addressblock BRGP0/reg0 -name PRSM  -width 8 -offset 0 -access rw -writefunction writePRSM  -writemask 0x17
imodeladdmmregister -addressblock BRGP0/reg0 -name PRSCM -width 8 -offset 1 -access rw -writefunction writePRSCM -writemask 0xff

#
# Resets
#
imodeladdreset -mmregister BRGP0/reg0/PRSM  -name IRESET -value 0x00
imodeladdreset -mmregister BRGP0/reg0/PRSCM -name IRESET -value 0x00

#
# Bit Fields
#
imodeladdfield -mmregister BRGP0/reg0/PRSM -name BGCS  -bitoffset 0 -width 2
imodeladdfield -mmregister BRGP0/reg0/PRSM -name TODIS -bitoffset 2 -width 1
imodeladdfield -mmregister BRGP0/reg0/PRSM -name BGCE  -bitoffset 4 -width 1
