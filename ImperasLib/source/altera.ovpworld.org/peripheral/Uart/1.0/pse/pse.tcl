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
set name    Uart
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Altera Avalon UART"
iadddocumentation -name Limitations -text "No Support for pin level transitions"
iadddocumentation -name Reference   -text "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011"

#
# Signals CPU
#
imodeladdnetport -name irq           -type output
imodeladdnetport -name endofpacket   -type output
imodeladdnetport -name dataavailable -type output
imodeladdnetport -name readyfordata  -type output

#
# Signals External
#
imodeladdnetport -name RXD           -type input
imodeladdnetport -name CTS           -type input
imodeladdnetport -name TXD           -type output
imodeladdnetport -name RTS           -type output

#
# Parameters
#

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

imodeladdformal -type uns64 -name baud
imodeladdformal -type uns64 -name dataBits
imodeladdformal -type uns64 -name fixedBaud

imodeladdformal -type enumeration -name parity
    imodeladdenumeration -formal parity -name None
    imodeladdenumeration -formal parity -name Even
    imodeladdenumeration -formal parity -name Odd

imodeladdformal -type uns64 -name stopBits
imodeladdformal -type uns64 -name syncRegDepth
imodeladdformal -type uns64 -name useCtsRts
imodeladdformal -type uns64 -name useEopRegister

#
# Slave port
# NOTE: 32 is wrong, this only presents 12 bytes
#
imodeladdbusslaveport -name sp1 -size 32

#
# Registers
#
imodeladdaddressblock -name reg0 -port sp1 -offset 0 -size 32 -width 32

#
# Registers
#
imodeladdmmregister -addressblock sp1/reg0 -name rxdata  -width 32 -offset 0  -access r  -readfunction  read_rxdata
imodeladdmmregister -addressblock sp1/reg0 -name txdata  -width 32 -offset 4  -access  w -writefunction write_txdata
imodeladdmmregister -addressblock sp1/reg0 -name status  -width 32 -offset 8  -access rw -readfunction  read_status  -writefunction write_status
imodeladdmmregister -addressblock sp1/reg0 -name control -width 32 -offset 12 -access rw -readfunction  read_control -writefunction write_control
imodeladdmmregister -addressblock sp1/reg0 -name divisor -width 32 -offset 16 -access rw -readfunction  read_divisor -writefunction write_divisor
imodeladdmmregister -addressblock sp1/reg0 -name eop     -width 32 -offset 20 -access rw -readfunction  read_eop     -writefunction write_eop

#
# Resets
#
imodeladdreset -mmregister sp1/reg0/rxdata  -name IRESET -value 0x0000
imodeladdreset -mmregister sp1/reg0/txdata  -name IRESET -value 0x0000
imodeladdreset -mmregister sp1/reg0/status  -name IRESET -value 0x0c60
imodeladdreset -mmregister sp1/reg0/control -name IRESET -value 0x0000
imodeladdreset -mmregister sp1/reg0/divisor -name IRESET -value 0x0000
imodeladdreset -mmregister sp1/reg0/eop     -name IRESET -value 0x0000

#
# Bit Fields
#
imodeladdfield -mmregister sp1/reg0/status  -name pe   -bitoffset 0  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name fe   -bitoffset 1  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name brk  -bitoffset 2  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name roe  -bitoffset 3  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name toe  -bitoffset 4  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name tmt  -bitoffset 5  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name trdy -bitoffset 6  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name rrdy -bitoffset 7  -width 1
imodeladdfield -mmregister sp1/reg0/status  -name e    -bitoffset 8  -width 2
imodeladdfield -mmregister sp1/reg0/status  -name dcts -bitoffset 10 -width 1
imodeladdfield -mmregister sp1/reg0/status  -name cts  -bitoffset 11 -width 1
imodeladdfield -mmregister sp1/reg0/status  -name eop  -bitoffset 12 -width 1

imodeladdfield -mmregister sp1/reg0/control  -name ipe   -bitoffset 0  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name ife   -bitoffset 1  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name ibrk  -bitoffset 2  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name iroe  -bitoffset 3  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name itoe  -bitoffset 4  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name itmt  -bitoffset 5  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name itrdy -bitoffset 6  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name irrdy -bitoffset 7  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name ie    -bitoffset 8  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name trbk  -bitoffset 9  -width 1
imodeladdfield -mmregister sp1/reg0/control  -name idcts -bitoffset 10 -width 1
imodeladdfield -mmregister sp1/reg0/control  -name rts   -bitoffset 11 -width 1
imodeladdfield -mmregister sp1/reg0/control  -name ieop  -bitoffset 12 -width 1

