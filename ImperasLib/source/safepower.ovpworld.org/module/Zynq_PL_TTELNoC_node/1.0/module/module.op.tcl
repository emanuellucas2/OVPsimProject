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

set desc "This module implements a NoC ni used to implement an example TTEL NoC in the Xilinx Zynq Programmable Logic (PL).
This PL configuration instances one Xilinx MicroBlaze processor with a local memory and a TTEL NoC interface peripheral."

set limitations "This is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_TTELNoC_node
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
# Interrupts
#
ihwaddnet -instancename CoreInterrupt
ihwaddnet -instancename pIntToCore


#
# Processor
#
ihwaddprocessor -instancename cpu -type microblaze -vendor xilinx.ovpworld.org -version 1.0 \
		-defaultsemihost

ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA

# TODO: Which interrupt is used
#ihwconnect   -instancename cpu -netport ??? -net pIntToCore

#
# Address Map
#
# Local Processor Access
# 0x40000000 0xffffffff No Device (except as below)
# 0x70000000 0x70ffffff NoC peripheral registers
# 0x00000000 0x03ffffff RAM 
#

# the NoC node Id is passed in
ihwaddformalparameter -name cluster -type uns32
ihwaddformalparameter -name tile    -type uns32
ihwaddformalparameter -name node    -type uns32

# 0x00000000    0x03ffffff      RAM
ihwaddmemory -instancename ramS -type ram
ihwconnect   -instancename ramS -bus pBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff

# 0x70000000 0x700fffff NoC peripheral registers
ihwaddperipheral -instancename ni -type TTELNode -vendor safepower.ovpworld.org
ihwconnect   -instancename ni -bus pBus -busslaveport hostif -loaddress 0x80000000 -hiaddress 0x80ffffff
# the NoC node Id is configured using cluster, tile and node
ihwsetparameter  -handle ni -name cluster -type uns32 -value cluster
ihwsetparameter  -handle ni -name tile    -type uns32 -value tile
ihwsetparameter  -handle ni -name node    -type uns32 -value node
# scheduled core interrupt
ihwconnect   -instancename ni -netport CoreInterrupt -net CoreInterrupt
# packet received interrupt
ihwconnect   -instancename ni -netport pIntToCore -net pIntToCore

#
# External PacketNet Port
#
ihwaddpacketnetport -instancename networkNodePort -mustbeconnected
ihwaddpacketnet     -instancename networkNode
ihwconnect          -packetnet networkNode -packetnetport networkNodePort

# Connect NoC Peripheral
ihwconnect -instancename ni -packetnetport network -packetnet networkNode
