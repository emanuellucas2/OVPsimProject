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

imodelnewperipheral  \
    -name           vEthernet_Bridge \
    -vendor         ovpworld.org  \
    -library        peripheral \
    -version        1.0 \
    -constructor    constructor \
    -destructor     destructor \
    -releasestatus  ovp

iadddocumentation -name Description -text "Bridges between a packetnet and the host's network"
iadddocumentation -name Limitations -text "None."
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text "This is not based upon the operation of a real device but is used in a virtual platform to connect the internal virtual Ethernet bus to the host network."

#
# Interface to the packetnet network. The maxbytes parameter sets the maximum
# packet length supported by this network, enforced by the simulator.
# Max Ethernet Frame = 1522 bytes
# size indicator 2 bytes (unsigned short int)
# total = 1524
imodeladdpacketnetport \
    -name phyBridge \
    -maxbytes 1524 \
    -updatefunction pktTrigger
iadddocumentation -name Description -text "The port to connect the packetnet virtual network"


imodeladdformalmacro -name BHM_ETHERNET_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
