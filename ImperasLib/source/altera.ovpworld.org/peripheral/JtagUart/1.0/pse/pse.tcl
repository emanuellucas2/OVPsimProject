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
set name    JtagUart
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Altera Avalon JTAG UART"
iadddocumentation -name Limitations -text "No Support for pin level transitions"
iadddocumentation -name Reference   -text "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011"

imodeladdformal -name readBufferDepth   -type uns32 -min 8 -max 32767 -defaultvalue 64
imodeladdformal -name readIRQThreshold  -type uns32 -min 8 -max 32767 -defaultvalue 8
imodeladdformal -name writeBufferDepth  -type uns32 -min 8 -max 32767 -defaultvalue 64
imodeladdformal -name writeIRQThreshold -type uns32 -min 8 -max 32767 -defaultvalue 8

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

imodeladdnetport -name irq   -type output
imodeladdnetport -name reset -type input

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
imodeladdmmregister -addressblock sp1/reg0 -name data    -width 32 -offset 0 -access rw -writefunction write_data    -readfunction read_data
imodeladdmmregister -addressblock sp1/reg0 -name control -width 32 -offset 4 -access rw -writefunction write_control -readfunction read_control

#
# Resets
#
imodeladdreset -mmregister sp1/reg0/data    -name IRESET -value 0x00000000
imodeladdreset -mmregister sp1/reg0/control -name IRESET -value 0x00000000

#
# Bit Fields
#
imodeladdfield -mmregister sp1/reg0/data    -name DATA   -bitoffset 0  -width 8
imodeladdfield -mmregister sp1/reg0/data    -name RVALID -bitoffset 15 -width 1
imodeladdfield -mmregister sp1/reg0/data    -name RAVAIL -bitoffset 16 -width 16 
imodeladdfield -mmregister sp1/reg0/control -name RE     -bitoffset 0  -width 1
imodeladdfield -mmregister sp1/reg0/control -name WE     -bitoffset 1  -width 1
imodeladdfield -mmregister sp1/reg0/control -name RI     -bitoffset 8  -width 1
imodeladdfield -mmregister sp1/reg0/control -name WI     -bitoffset 9  -width 1
imodeladdfield -mmregister sp1/reg0/control -name AC     -bitoffset 10 -width 1
imodeladdfield -mmregister sp1/reg0/control -name WSPACE -bitoffset 16 -width 16

