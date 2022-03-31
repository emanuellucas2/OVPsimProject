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

set vendor  altera.ovpworld.org
set library peripheral
set name    SystemIDCore
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Altera Avalon System ID Core"
iadddocumentation -name Limitations -text "No Support for pin level transitions"
iadddocumentation -name Reference   -text "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011"

imodeladdformal -name id        -type uns64
imodeladdformal -name timestamp -type uns64

#
# Slave port
#
imodeladdbusslaveport -name sp1 -size 8

#
# Registers
#
imodeladdaddressblock -name reg0 -port sp1 -offset 0 -size 8 -width 32

#
# Registers
#
imodeladdmmregister -addressblock sp1/reg0 -name id        -width 32 -offset 0  -access r -readfunction read_id
imodeladdmmregister -addressblock sp1/reg0 -name timestamp -width 32 -offset 4  -access r -readfunction read_timestamp
