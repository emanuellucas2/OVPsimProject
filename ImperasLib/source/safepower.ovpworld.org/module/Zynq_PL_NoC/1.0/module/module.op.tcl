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

set desc "This module implements a configuration for Xilinx Zynq Programmable Logic (PL).
This PL configuration instances four Xilinx MicroBlaze processor based NoC sub-systems (Zync_PL_NoC_node), each with a MicroBlaze processor, local memory and NoC interface Peripheral.
Also included is a NoC interface peripheral that is accessible from the Zynq_PS ARM processors."

set limitations "This is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_NoC
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference

# Include the default interconnect ports and signals for the PL to PS
source "$env(IMPERAS_HOME)/ImperasLib/source/xilinx.ovpworld.org/module/Zynq_PL_Default/1.0/module/PS_PL_interconnect.tcl"

#
# network connection
#
ihwaddpacketnet -instancename network


# Bus
ihwaddbus -instancename mBus  -addresswidth 32

# Bridge local memory from input port
# 0x41000000 to 0x410fffff
ihwaddbridge  -instancename smem_extPort
ihwconnect    -instancename smem_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x41000000 -hiaddress 0x410fffff
ihwconnect    -instancename smem_extPort -busmasterport mp1 -bus mBus       -loaddress 0x00000000 -hiaddress 0x000fffff
# Bridge NoC node registers from input port
# 0x41000000 to 0x410fffff
ihwaddbridge  -instancename nocif_extPort
ihwconnect    -instancename nocif_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x44000000 -hiaddress 0x440003ff
ihwconnect    -instancename nocif_extPort -busmasterport mp1 -bus mBus       -loaddress 0x04000000 -hiaddress 0x040003ff

# NoC node
ihwaddperipheral -instancename node -type node -vendor safepower.ovpworld.org
ihwconnect   -instancename node -bus mBus -busslaveport hostif -loaddress 0x04000000 -hiaddress 0x040003ff
ihwsetparameter  -handle node -name id -type uns32 -value 5
ihwconnect   -instancename node -packetnet network -packetnetport network

# Memory
ihwaddmemory -instancename smem -type ram
ihwconnect   -instancename smem -bus mBus -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x000fffff

#
# Microblaze NoC 1
#
ihwaddmodule -instancename mbNoC1 \
             -vendor safepower.ovpworld.org -type Zynq_PL_NoC_node \
             -library module -version 1.0
ihwsetparameter  -handle mbNoC1 -name nocid -type uns32 -value 1
ihwconnect   -instancename mbNoC1 -packetnet network -packetnetport networkNodePort

#
# Microblaze NoC 2
#
ihwaddmodule -instancename mbNoC2 \
	     -vendor safepower.ovpworld.org -type Zynq_PL_NoC_node \
	     -library module -version 1.0
ihwsetparameter  -handle mbNoC2 -name nocid -type uns32 -value 2
ihwconnect   -instancename mbNoC2 -packetnet network -packetnetport networkNodePort

#
# Microblaze NoC 3
#
ihwaddmodule -instancename mbNoC3 \
	     -vendor safepower.ovpworld.org -type Zynq_PL_NoC_node \
	     -library module -version 1.0
ihwsetparameter  -handle mbNoC3 -name nocid -type uns32 -value 3
ihwconnect   -instancename mbNoC3 -packetnet network -packetnetport networkNodePort

#
# Microblaze NoC 4
#
ihwaddmodule -instancename mbNoC4 \
             -vendor safepower.ovpworld.org -type Zynq_PL_NoC_node \
             -library module -version 1.0
ihwsetparameter  -handle mbNoC4 -name nocid -type uns32 -value 4
ihwconnect   -instancename mbNoC4 -packetnet network -packetnetport networkNodePort
	     	     	     
