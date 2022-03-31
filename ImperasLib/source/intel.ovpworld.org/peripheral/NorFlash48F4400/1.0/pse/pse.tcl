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
# NAME : NorFlash48F4400

# Set size to 64MB/512-Mbit (This must match the setting of FLASH_SIZE in NorFlash48F4400.c) 
set SIZE 0x4000000

imodelnewperipheral  \
	-name          NorFlash48F4400  \
	-vendor        intel.ovpworld.org \
	-library       peripheral  \
	-version       1.0  \
	-constructor   constructor \
	-destructor    destructor \
	-releasestatus ovp
	
iadddocumentation -name Description -text "Intel StrataFlash P30 Memory: 64MB (512-Mbit), 2x16, Top configuration."
iadddocumentation -name Description -text "Organized in a 2x16 configuration (2 16 bit wide data chips, requiring commands to be repeated in data bits 0:15 and 16:31)."  
iadddocumentation -name Description -text "Top configuration (last 4 blocks are 64KB parameter blocks)."

iadddocumentation -name Limitations -text "No flash program timing is modeled, all operations including erase take effect immediately, and suspend commands are NOPs."
iadddocumentation -name Limitations -text "Block Locking, Lock-down and OTP (One-Time Programmable) features are not modeled (Blocks are always reported to be unlocked)."
iadddocumentation -name Limitations -text "Burst-Mode reads and the Read Configuration register are not modeled."
iadddocumentation -name Limitations -text "Buffered writes are written immediately, not held until confirm command is issued."

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Reference   -text "Intel Nor Flash Datasheet as used on Xilinx ML505 board: http://www.xilinx.com/products/boards/ml505/datasheets/30666604.pdf"

# Flash memory port 
imodeladdbusslaveport -name flash -mustbeconnected -size $SIZE

# Usr-definable Model Parameters
imodeladdformal    -name image -type string
iadddocumentation  -name Description    -text "Binary image file name(s) for flash memory initial value"