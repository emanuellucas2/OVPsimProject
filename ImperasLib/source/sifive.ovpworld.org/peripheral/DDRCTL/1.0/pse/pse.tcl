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
    -name          DDRCTL \
    -vendor        sifive.ovpworld.org \
    -library       peripheral \
    -version       1.0 \
    -constructor   constructor \
    -releasestatus ovp        \
    -visibility    visible \
	-nbyteregisters

iadddocumentation -name Description -text "DDR Controller Register Block for SiFive FU540 chip"

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)"
iadddocumentation -name Limitations -text "Register only model. Register address space modeled as RAM except for registers that require write masks or reset values."

# Define Control Registers input port, and add backing memory for default registers
imodeladdbusslaveport -name CONTROL  -size 0x4000 -mustbeconnected
imodeladdaddressblock -name REGS     -size 0x4000 -port CONTROL  -offset 0 -width 32
imodeladdlocalmemory  -name ctrlRegs -size 0x4000 -addressblock CONTROL/REGS -readfunction readControlMem -writefunction writeControlMem

# Control Register 33 (at offset 132=0x84) must return bit 8 set to 0 for boot to proceed
imodeladdmmregister -name reg33 -offset 0x84 -access rw -writefunction writeMaskedControlReg -userData 0xfffffeff

# Define Bus Blocker input port, and add backing memory for default register
imodeladdbusslaveport -name BLOCKER -size 0x8 -mustbeconnected
imodeladdaddressblock -name REGS    -size 0x8 -port BLOCKER  -offset 0 -width 64
imodeladdlocalmemory  -name blkRegs -size 0x8 -addressblock BLOCKER/REGS -readfunction readBlockerMem -writefunction writeBlockerMem
