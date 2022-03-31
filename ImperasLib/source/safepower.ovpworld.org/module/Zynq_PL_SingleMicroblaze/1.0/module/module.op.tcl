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
This PL configuration instances one Xilinx MicroBlaze processor and local memory.
Also included is an area of shared memory that can be accessed by the Microblaze processor or other external master."

set limitations "The is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_SingleMicroblaze
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
# sBus (shared resources)
#
ihwaddbus -instancename sBus  -addresswidth 32

# 0x00000000    0x03ffffff      RAM (shared)
ihwaddmemory -instancename ramS -type ram
ihwconnect   -instancename ramS -bus sBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff

#
# Address Map
#
# Local Processor Access
# 0x54000000 0xffffffff No Device
# 0x50000000 0x53ffffff External Port (master)
# 0x40000000 0x43ffffff RAM (shared)
# 0x04000000 0x3fffffff No Device
# 0x00000000 0x03ffffff RAM 
#
# External Port (incoming) Access
# 0x00000000 0x03ffffff RAM (shared) 

# Local Processor
# 0x00000000    0x03ffffff RAM
ihwaddmemory -instancename ram -type ram
ihwconnect   -instancename ram -bus pBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff

# Local Processor (shared memory)
# 0x40000000    0x43ffffff
ihwaddbridge  -instancename pBusToMem
ihwconnect    -instancename pBusToMem -busslaveport  sp1 -bus pBus -loaddress 0x40000000 -hiaddress 0x43ffffff
ihwconnect    -instancename pBusToMem -busmasterport mp1 -bus sBus -loaddress 0x00000000 -hiaddress 0x03ffffff

# Local Processor (Access to External Processor Sub-System)
# 0x50000000    0x53ffffff
ihwaddbridge  -instancename cpuToextPort
ihwconnect    -instancename cpuToextPort -busslaveport  sp1 -bus pBus       -loaddress 0x50000000 -hiaddress 0x53ffffff
ihwconnect    -instancename cpuToextPort -busmasterport mp1 -bus extPortBus -loaddress 0x00000000 -hiaddress 0x03ffffff


#
# External devices access
#
# 0x00000000    0x03ffffff      RAM (external port access)
ihwaddbridge  -instancename extPortToMem
ihwconnect    -instancename extPortToMem -busslaveport  sp1 -bus extPortBus -loaddress 0x00000000 -hiaddress 0x03ffffff
ihwconnect    -instancename extPortToMem -busmasterport mp1 -bus sBus       -loaddress 0x00000000 -hiaddress 0x03ffffff
