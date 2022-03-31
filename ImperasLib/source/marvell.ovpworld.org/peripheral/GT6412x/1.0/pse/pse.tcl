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
# NAME : GT6412x

imodelnewperipheral  \
                -name    GT6412x  \
                -vendor  marvell.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -releasestatus ovp \
                -constructor constructor \
                -destructor  destructor \
                -recursive

iadddocumentation  \
            -name Licensing  \
            -text "Open Source Apache 2.0"

iadddocumentation  \
            -name Description  \
            -text "GT64120 System Controller."

iadddocumentation  \
            -name Description  \
            -text "Diagnostic levels:"
iadddocumentation  \
            -name Description  \
            -text "PCI_SLAVE           0x03"
iadddocumentation  \
            -name Description  \
            -text "PCI_CONFIG_MASTER   0x04"
iadddocumentation  \
            -name Description  \
            -text "PCI_EMPTY           0x08"
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
            -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform."

iadddocumentation  \
            -name Reference  \
            -text "GT64121A System Controller for RC4650/4700/5000 and RM526X/527X/7000 CPUs Datasheet Revision 1.0 MAR 14, 2000"
            
  # Main bus bridge to access PCI configuration bus
  imodeladdbusslaveport  \
                -name busPort  \
                -size 0x1000  \
                -mustbeconnected  \
                -remappable

  # Drives the PCI configuration bus, bridged from the main bus		
  imodeladdbusmasterport  \
                -name PCIconfigM  \
                -addresswidth 16  \
                -mustbeconnected

  # Catches access to empty PCI configuration bus slots
#  imodeladdbusslaveport  \
#                -name PCIconfigS  \
#                -size 0x10000  \
#                -mustbeconnected

  # This devices own entries on the PCI configuration bus
  imodeladdbusslaveport  \
                -name PCIconfig  \
		-addresswidth 16  \
                -remappable

  # One-word bus to acknowledge interrupts
  imodeladdbusmasterport  \
                -name PCIackM  \
                -addresswidth 0

  imodeladdnetport -name timerInt -type output
  
imodeladdformal     -name PCIslot      -type uns32
iadddocumentation   -name Description  -text "Specify which PCI slot the device occupies."


imodeladdformal   -name PCIfunction  -type uns32
iadddocumentation -name Description  -text "Specify which PCI function the device implements."

