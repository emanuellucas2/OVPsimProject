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
set name    Zynq_PL_NostrumNoC_node
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
# 0x40000000 0xffffffff No Device (except as below)
# 0x70020000 0x7003ffff NoC peripheral registers
# 0x41000000 0x410001ff AXI GPIO
# 0x40000000 0x400001ff AXI GPIO
# 0x00000000 0x03ffffff RAM 
#

# the NoC node Id is passed in
ihwaddformalparameter -name nocid -type uns32
ihwaddformalparameter -name generateSync -type bool
ihwaddformalparameter -name sendChannelSize -type uns32
ihwaddformalparameter -name mboxSize -type uns32

# 0x00000000    0x03ffffff      RAM
ihwaddmemory -instancename ramS -type ram
ihwconnect   -instancename ramS -bus pBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff

# 0x40000000    0x400001fff      AXI GPIO
ihwaddperipheral -instancename gpio -type axi-gpio -vendor xilinx.ovpworld.org
ihwconnect       -instancename gpio -bus pBus -busslaveport  sp1 -loaddress 0x40000000 -hiaddress 0x400001ff
# connections to Zync GPIO
ihwaddnet   -instancename gpio_out
ihwconnect  -instancename gpio -netport gpio_out  -net gpio_out
ihwaddnet   -instancename gpio2_out
ihwconnect  -instancename gpio -netport gpio2_out -net gpio2_out
ihwaddnet   -instancename gpio_in
ihwconnect  -instancename gpio -netport gpio_in   -net gpio_in
ihwaddnet   -instancename gpio2_in
ihwconnect  -instancename gpio -netport gpio2_in  -net gpio2_in

# 0x41000000    0x410001ff      AXI GPIO
ihwaddbus     -instancename gpiodprBus -addresswidth 32
ihwaddbridge  -instancename gpiodprBridge
ihwconnect    -instancename gpiodprBridge -busslaveport  sp1 -bus pBus       -loaddress 0x41000000 -hiaddress 0x410001ff
ihwconnect    -instancename gpiodprBridge -busmasterport mp1 -bus gpiodprBus -loaddress 0x41000000 -hiaddress 0x410001ff

ihwaddbusport -instancename gpiodprPort
ihwconnect    -bus gpiodprBus  -busport gpiodprPort


# 0x70020000 0x7003ffff NoC peripheral registers
ihwaddperipheral -instancename node -type NostrumNode -vendor safepower.ovpworld.org
ihwconnect   -instancename node -bus pBus -busslaveport hostif -loaddress 0x70020000 -hiaddress 0x7003ffff
ihwsetparameter  -handle node -name id -type uns32 -value nocid
# pass down the parameter from the module
ihwsetparameter  -handle node -name generateSync    -expression generateSync    -type bool
ihwsetparameter  -handle node -name sendChannelSize -expression sendChannelSize -type uns32
ihwsetparameter  -handle node -name mboxSize        -expression mboxSize -type uns32

#
# External PacketNet Port
#
ihwaddpacketnetport -instancename networkNodePort -mustbeconnected
ihwaddpacketnet     -instancename networkNode
ihwconnect          -packetnet networkNode -packetnetport networkNodePort

# Connect NoC Peripheral
ihwconnect -instancename node -packetnetport network -packetnet networkNode

#
# External network Sync Net
#
ihwaddnetport -instancename syncInPort
ihwaddnetport -instancename syncOutPort
ihwaddnet     -instancename syncIn
ihwaddnet     -instancename syncOut
ihwconnect    -net syncIn  -netport syncInPort
ihwconnect    -net syncOut -netport syncOutPort

# Connect NoC Peripheral
ihwconnect -instancename node -netport syncIn  -net syncIn
ihwconnect -instancename node -netport syncOut -net syncOut

# GPIO connections of LED and SWI

ihwaddnetport -instancename gpio_outP
ihwconnect    -netport gpio_outP -net gpio_out
ihwaddnetport -instancename gpio2_outP
ihwconnect    -netport gpio2_outP -net gpio2_out

ihwaddnetport -instancename gpio_inP
ihwconnect    -netport gpio_inP -net gpio_in
ihwaddnetport -instancename gpio2_inP
ihwconnect    -netport gpio2_inP -net gpio2_in
