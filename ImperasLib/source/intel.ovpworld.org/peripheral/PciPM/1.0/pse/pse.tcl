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
# NAME : PciPM

imodelnewperipheral  \
                -name    PciPM  \
                -vendor  intel.ovpworld.org  \
                -library peripheral  \
                -version 1.0 \
                -releasestatus ovp \
                -constructor constructor \
                -destructor  destructor

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "PCI Power Manager."

iadddocumentation  \
                -name Limitations  \
                -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform."

iadddocumentation  \
		-name Reference  \
		-text "Intel 82371EB South Bridge Chipset Datasheet"

  imodeladdbusslaveport  \
                -name PCIconfig  \
                -size 0x800  \
                -remappable

  imodeladdbusslaveport  \
                -name busPort  \
                -size 0x8  \
                -remappable

  imodeladdformal -name PCIslot -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Specify which PCI slot the device occupies."


  imodeladdformal -name PCIfunction -type uns32
  iadddocumentation  \
                -name Description  \
                -text "Specify which PCI function:code the device implements."



