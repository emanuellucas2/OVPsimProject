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
# NAME : PciIDE

imodelnewperipheral  \
                -name    PciIDE  \
                -vendor  intel.ovpworld.org  \
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
                -text "PCI:IDE interface.
This forms part of the 82371 PIIX4 chip.
It implements 4 IDE interfaces and 2 DMA controllers."

iadddocumentation  \
                -name Limitations  \
                -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform."

iadddocumentation  \
		-name Reference  \
		-text "Intel 82371EB South Bridge Chipset Datasheet"

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

imodeladdnetport  \
                -name intOut1   \
                -type output

imodeladdformal     -name PCIslot      -type uns32
iadddocumentation   -name Description  -text "Specify which PCI slot the device occupies."


imodeladdformal   -name PCIfunction  -type uns32
iadddocumentation -name Description  -text "Specify which PCI function:code the device implements."

foreach i {0 1 2 3} {
    imodeladdformal -name "Drive${i}Name"  -type string
    iadddocumentation  -name Description  -text "Virtual disk file for IDE channel ${i}"

    imodeladdformal -name "Drive${i}Delta"  -type string
    iadddocumentation  -name Description  -text "Delta file for IDE channel ${i}. This feature is incomplete."
}


imodeladdformal -name endian -type string -defaultValue "little"
iadddocumentation  \
                -name Description  \
                -text "Set the system endian, \"big\" or \"little\"; used for writing boot code. Default is \"little\" endian."

imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

