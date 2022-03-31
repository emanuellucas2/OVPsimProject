#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
# Copyright (c) 2012-2018 MIPS Tech, LLC, www.mips.com
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

# NAME : axi-pcie

imodelnewperipheral  \
                -name    axi-pcie  \
                -vendor  xilinx.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -releasestatus ovp \
                -constructor constructor \
                -destructor  destructor

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Xilinx AXI to PCI Express bridge."

iadddocumentation  \
                -name Description  \
                -text "Diagnostic levels:"
iadddocumentation  \
                -name Description  \
                -text "PCIE_SLAVE           0x03"
iadddocumentation  \
                -name Description  \
                -text "PCIE_CONFIG_MASTER   0x04"
iadddocumentation  \
                -name Description  \
                -text "PCIE_EMPTY           0x08"
iadddocumentation  \
                -name Description  \
                -text "INT_ACK             0x10"
iadddocumentation  \
                -name Description  \
                -text "MAIN_BUS            0x20"
iadddocumentation  \
                -name Description  \
                -text "INFO                0x40"

iadddocumentation  \
                -name Limitations  \
                -text "This model has sufficient functionality to allow a Linux Kernel to Boot."

iadddocumentation  \
                -name Reference  \
                -text "LogiCORE IP AXI Bridge for PCI Express v2.3 Product Guide April 2, 2014."

# Main bus bridge to access PCI Express configuration bus
# TODO: Hacked -size 0x10000000 -> 0x1000
imodeladdbusslaveport \
                -name ecam \
                -size 0x1000 \
                -mustbeconnected \
                -remappable

# XXX: remove?
imodeladdbusslaveport  \
                -name busPort  \
                -size 0x1000  \
                -mustbeconnected  \
                -remappable

# Drives the PCI Express configuration bus, bridged from the main bus		
imodeladdbusmasterport  \
                -name PCIconfigM  \
                -addresswidth 28  \
                -mustbeconnected

# This devices' own entries on the PCI Express configuration bus
imodeladdbusslaveport  \
                -name PCIconfig  \
		-addresswidth 16  \
                -remappable

# One-word bus to acknowledge interrupts
imodeladdbusmasterport  \
                -name PCIackM  \
                -addresswidth 0

imodeladdnetport -name intOut -type output
imodeladdnetport -name intA   -type input
imodeladdnetport -name intB   -type input
imodeladdnetport -name intC   -type input
imodeladdnetport -name intD   -type input

imodeladdformal   -name PCIbus       -type uns32
iadddocumentation -name Description  -text "Specify which PCI Express bus the device occupies."

imodeladdformal   -name PCIslot      -type uns32
iadddocumentation -name Description  -text "Specify which PCI Express slot the device occupies."

imodeladdformal   -name PCIfunction  -type uns32
iadddocumentation -name Description  -text "Specify which PCI Express function the device implements."
