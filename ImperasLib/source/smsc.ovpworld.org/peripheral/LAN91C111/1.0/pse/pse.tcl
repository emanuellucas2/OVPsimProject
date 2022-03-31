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

set range    0x1000
set regWidth 16

imodelnewperipheral  \
    -imagefile pse.pse  \
    -name    LAN91C111 \
    -vendor  smsc.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp


iadddocumentation -name Description -text "SMSC LAN91C111"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "Not all registers and device features are implemented.  Only 16-bit bus interface currently supported."
iadddocumentation -name Reference   -text "SMSC LAN91C111 10/100 Non-PCI Ethernet Single Chip MAC + PHY Datasheet Revision 1.91 (06-01-09)"

# Irq net port
imodeladdnetport -name irq -type output
iadddocumentation -name Description -text "IRQ Pin"

#
# Interface to the packetnet network. The maxbytes parameter sets the maximum
# packet length supported by this network, enforced by the simulator.
# Max Ethernet Frame = 1522 bytes
# size indicator 2 bytes (unsigned short int)
# total = 1524

imodeladdpacketnetport -name phy -maxbytes 1524 
iadddocumentation -name Description -text "The port to connect the packetnet virtual network"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"

imodeladdmmregister -name BANK_SEL -addressblock $addBlock -offset 0xE -width 16 -access rw -userdata 0xE -readfunction readReg16 -writefunction writeReg16

set i 0
while {$i < 14} {
    set rname "REG_$i"
    imodeladdmmregister -name $rname -addressblock $addBlock -offset $i -width 16 -access rw -userdata $i -readfunction readReg16 -writefunction writeReg16
    incr i
    incr i
}

#
# Formal attributes
#
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
imodeladdformalmacro -name BHM_ETHERNET_OPEN_AUTO_FORMALS

