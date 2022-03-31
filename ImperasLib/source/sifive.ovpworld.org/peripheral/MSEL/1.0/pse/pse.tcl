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

set vendor  sifive.ovpworld.org
set library peripheral
set name    MSEL
set version 1.0

imodelnewperipheral  \
	-name ${name} -vendor ${vendor} -library ${library} -version ${version}  \
	-imagefile pse.pse \
	-constructor constructor \
	-releasestatus ovp

iadddocumentation -name Description -text "Mode Select reset module. Entered on reset and calls boot code based on MSEL pin state. 
Override the MSEL parameter to specify the initial value for the MSEL pin state (default 0xf). 
From application code or debugger write to the MSEL register at offset 0 to change the MSEL pin state."

iadddocumentation -name Limitations -text "None"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)"

imodeladdbusslaveport -name bport1 -mustbeconnected -size 0x1000

# MSEL register located at offset 0 and parameter to specify initial value
imodeladdaddressblock -name REG  -port bport1 -size 0x4 -offset 0 -width 32
imodeladdmmregister   -name MSEL -addressblock bport1/REG -width 32 -offset 0 -access rw -writemask 0xf
imodeladdformal       -name MSEL -type uns32 -min 0 -max 0xf -defaultvalue 0xf

# Local memory block to hold reset instructions - initialized in constructor
imodeladdaddressblock -name CODE     -port bport1 -size 0x20   -offset 4 -width 32
imodeladdlocalmemory  -name RESET    -addressblock bport1/CODE -offset 0 -size 0x20 -access r

# Local memory block to hold jump table values - initialized in constructor
imodeladdaddressblock -name TABLE    -port bport1 -size 0x80    -offset 0x100 -width 32
imodeladdlocalmemory  -name JUMPADDR -addressblock bport1/TABLE -offset 0x0 -size 0x80 -access r 

