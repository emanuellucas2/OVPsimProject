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

set desc "This module implements a NoC node used to implement an example NoC in the Xilinx Zynq Programmable Logic (PL).
This PL configuration instances one Xilinx MicroBlaze processor with a local memory and a NoC interface peripheral."

set limitations "This is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_NoC_node
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference

#
# pBus
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename cpu -type microblaze -vendor xilinx.ovpworld.org -version 1.0 \
		-defaultsemihost

ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA

#
# Address Map
#
# Local Processor Access
# 0x40000030 0xffffffff No Device
# 0x04000000 0x0400002f NoC peripheral registers
# 0x00000000 0x03ffffff RAM 
#

# the NoC node Id is passed in
ihwaddformalparameter -name nocid -type uns32

# 0x00000000    0x03ffffff      RAM
ihwaddmemory -instancename ramS -type ram
ihwconnect   -instancename ramS -bus pBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff

# 0x40000000    0x4000002f      NoC peripheral
ihwaddperipheral -instancename node -type node -vendor safepower.ovpworld.org
ihwconnect   -instancename node -bus pBus -busslaveport hostif -loaddress 0x04000000 -hiaddress 0x040003ff
ihwsetparameter  -handle node -name id -type uns32 -value nocid
# microblaze is big endian so need to configure peripheral register interface
ihwsetparameter  -handle node -name endian -type string -value big

#
# External PacketNet Port
#
ihwaddpacketnetport -instancename networkNodePort -mustbeconnected
ihwaddpacketnet     -instancename networkNode
ihwconnect          -packetnet networkNode -packetnetport networkNodePort

# Connect NoC Peripheral
ihwconnect -instancename node -packetnetport network -packetnet networkNode
