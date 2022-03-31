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

set vendor  microsemi.ovpworld.org
set library peripheral
set name    CoreUARTapb
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor -releasestatus ovp

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Microsemi CoreUARTapb"
iadddocumentation -name Limitations -text "Basic functionality for transmit and receive"
iadddocumentation -name Reference   -text "CoreUARTapb handbook v5.2 https://www.microsemi.com/document-portal/doc_view/130958-coreuartapb-handbook"

#
# Slave ports
#

imodeladdbusslaveport -name port0 -size 0x18

imodeladdaddressblock -name Reg -port port0 -size 0x18 -offset 0x00000000 -width 32


imodeladdmmregister -addressblock port0/Reg -name TxData -width 32 -offset 0x000 -access  w -writefunction TxDataWrite
imodeladdmmregister -addressblock port0/Reg -name RxData -width 32 -offset 0x004 -access r                              -readfunction RxDataRead

imodeladdmmregister -addressblock port0/Reg -name Ctrl1  -width 32 -offset 0x008 -access rw -writefunction Ctrl1Write   -readfunction Ctrl1Read
imodeladdfield -mmregister port0/Reg/Ctrl1 -name BAUD_VALUE -bitoffset 0 -width 8

imodeladdmmregister -addressblock port0/Reg -name Ctrl2  -width 32 -offset 0x00C -access rw -writefunction Ctrl2Write   -readfunction Ctrl2Read
imodeladdfield -mmregister port0/Reg/Ctrl2 -name BIT8       -bitoffset 0 -width 1
imodeladdfield -mmregister port0/Reg/Ctrl2 -name PARITY_EN  -bitoffset 1 -width 1
imodeladdfield -mmregister port0/Reg/Ctrl2 -name ODD_N_EVEN -bitoffset 2 -width 1
imodeladdfield -mmregister port0/Reg/Ctrl2 -name BAUD_VALUE -bitoffset 3 -width 5

imodeladdmmregister -addressblock port0/Reg -name Status -width 32 -offset 0x010 -access r                              -readfunction StatusRead
imodeladdfield -mmregister port0/Reg/Status -name TXRDY       -bitoffset 0 -width 1
imodeladdfield -mmregister port0/Reg/Status -name RXRDY       -bitoffset 1 -width 1
imodeladdfield -mmregister port0/Reg/Status -name PARITY_ERR  -bitoffset 2 -width 1
imodeladdfield -mmregister port0/Reg/Status -name OVERFLOW    -bitoffset 3 -width 1
imodeladdfield -mmregister port0/Reg/Status -name FRAMING_ERR -bitoffset 4 -width 1

imodeladdmmregister -addressblock port0/Reg -name Ctrl3  -width 32 -offset 0x014 -access rw -writefunction Ctrl3Write   -readfunction Ctrl3Read
imodeladdfield -mmregister port0/Reg/Ctrl3 -name BAUD_VALUE_FRACTION -bitoffset 0 -width 3

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
