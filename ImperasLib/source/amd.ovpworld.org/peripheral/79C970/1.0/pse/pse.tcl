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
# NAME : 79C970

imodelnewperipheral  \
                -vendor  amd.ovpworld.org  \
                -library peripheral  \
                -name    79C970  \
                -version 1.0  \
                -constructor constructor \
                -destructor  destructor
            
iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Implements part of the AMD AM79C97xx series Ethernet devices."

iadddocumentation  \
                -name Description  \
                -text "diagnosticlevel:
    bits 0:1 give levels for the network hardware.
    bits 2:3 give levels for the user:mode SLIRP interface."

iadddocumentation  \
                -name Limitations  \
                -text "Sufficient is implemented to Boot MIPS Linux and support ethernet TCP/IP services."

iadddocumentation  \
		-name Reference  \
		-text "AMD Am79C973/Am79C975 PCnet-FAST III Single-Chip 10/100 Mbps PCI Ethernet Controller with Integrated PHY Datasheet"

imodeladdbusslaveport  \
                -name busPort  \
                -size 8  \
                -mustbeconnected  \
                -remappable

iadddocumentation  \
                -name Description  \
                -text "PCI main bus connection for register access."

  imodeladdbusslaveport  \
                -name PCIconfig  \
                -size 0x800  \
                -remappable

iadddocumentation  \
                -name Description  \
                -text "PCI configuration bus connection."

imodeladdbusmasterport  \
                -name dmaPort  \
                -addresswidthmin 32 \
                -addresswidthmax 40 

iadddocumentation  \
                -name Description  \
                -text "PCI DMA bus connection."

imodeladdnetport  \
                -name intOut0   \
                -type output

imodeladdformal  \
                -name PCIslot  \
                -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Set the PCI slot at which the Ethernet card is installed"


imodeladdformal  \
                -name PCIfunction  \
                -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Set the PCI function of the device. The default of 0 is correct for this device."


#
# Interface to the packetnet network. The maxbytes parameter sets the maximum
# packet length supported by this network, enforced by the simulator.
# Max Ethernet Frame = 1522 bytes
# size indicator 2 bytes (unsigned short int)
# total = 1524
imodeladdpacketnetport \
    -name phy \
    -maxbytes 1524
iadddocumentation -name Description -text "The port to connect the packetnet virtual network"


imodeladdformalmacro -name BHM_ETHERNET_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
