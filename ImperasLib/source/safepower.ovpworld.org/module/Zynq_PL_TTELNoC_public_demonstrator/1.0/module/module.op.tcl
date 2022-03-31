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

set desc "This module implements the Top Level SafePower Public Demonstrator Xilinx Zynq Programmable Logic (PL).
This PL configuration instances SafePower Public Demonstrator Processing Node modules and a Sensor Actor Node module. 
These modules are all interconnected by a TTEL NoC. 
Also included is a TTEL NoC interface peripheral that is accessible from the Zynq_PS ARM processors."

set limitations "Provides a baremetal implementation."

set reference "SafePower Public Demonstrator"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_TTELNoC_public_demonstrator
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


# Main Bus
ihwaddbus -instancename mBus  -addresswidth 32

# PL GP0
ihwaddbridge  -instancename smem_extPort
ihwconnect    -instancename smem_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x40000000 -hiaddress 0x7fffffff
ihwconnect    -instancename smem_extPort -busmasterport mp1 -bus mBus       -loaddress 0x40000000 -hiaddress 0x7fffffff

# PL GP1
ihwaddbridge  -instancename nocif_extPort
ihwconnect    -instancename nocif_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x80000000 -hiaddress 0xbfffffff
ihwconnect    -instancename nocif_extPort -busmasterport mp1 -bus mBus       -loaddress 0x80000000 -hiaddress 0xbfffffff


# NoC node
ihwaddperipheral -instancename NoC_0_0 -type TTELNode -vendor safepower.ovpworld.org
ihwconnect -instancename NoC_0_0 -bus mBus -busslaveport hostif -loaddress 0x40000000 -hiaddress 0x40ffffff
ihwsetparameter  -handle NoC_0_0 -name cluster -type uns32 -value 0
ihwsetparameter  -handle NoC_0_0 -name tile    -type uns32 -value 0
ihwsetparameter  -handle NoC_0_0 -name node    -type uns32 -value 0
ihwconnect -instancename NoC_0_0 -packetnet network -packetnetport network

# NoC timestamp region (provide dummy)
ihwaddperipheral -instancename dummy -type trap -vendor ovpworld.org
ihwconnect       -instancename dummy -busslaveport bport1 -bus mBus
ihwsetparameter  -handle dummy -name portAddress -value 0x60000000 -type uns32
ihwsetparameter  -handle dummy -name portSize    -value 0x30000    -type uns32
ihwsetparameter  -handle dummy -name cbEnable    -value 1          -type bool

# Add periodic interrupt to ARM
ihwconnect -instancename NoC_0_0 -netport PeriodInterrupt -net irqf2p0
ihwconnect -instancename NoC_0_0 -netport CoreInterrupt -net irqf2p1

#
# Microblaze NoC 0_1
#
ihwaddmodule -instancename NoC_0_1 \
             -vendor safepower.ovpworld.org -type Zynq_PL_TTELNoC_sensor_actor_node_public_demonstrator \
             -library module -version 1.0
ihwsetparameter  -handle NoC_0_1 -name cluster -type uns32 -value 0
ihwsetparameter  -handle NoC_0_1 -name tile    -type uns32 -value 0
ihwsetparameter  -handle NoC_0_1 -name node    -type uns32 -value 1
ihwconnect -instancename NoC_0_1 -packetnet network -packetnetport networkNodePort

#
# Microblaze NoC 1_0
#
ihwaddmodule -instancename NoC_1_0 \
	         -vendor safepower.ovpworld.org -type Zynq_PL_TTELNoC_processing_node_public_demonstrator \
	         -library module -version 1.0
ihwsetparameter  -handle NoC_1_0 -name cluster -type uns32 -value 0
ihwsetparameter  -handle NoC_1_0 -name tile    -type uns32 -value 0
ihwsetparameter  -handle NoC_1_0 -name node    -type uns32 -value 2
ihwconnect -instancename NoC_1_0 -packetnet network -packetnetport networkNodePort

#
# Microblaze NoC 1_1
#
ihwaddmodule -instancename NoC_1_1 \
	         -vendor safepower.ovpworld.org -type Zynq_PL_TTELNoC_processing_node_public_demonstrator \
	         -library module -version 1.0
ihwsetparameter  -handle NoC_1_1 -name cluster -type uns32 -value 0
ihwsetparameter  -handle NoC_1_1 -name tile    -type uns32 -value 0
ihwsetparameter  -handle NoC_1_1 -name node    -type uns32 -value 3
ihwconnect -instancename NoC_1_1 -packetnet network -packetnetport networkNodePort
