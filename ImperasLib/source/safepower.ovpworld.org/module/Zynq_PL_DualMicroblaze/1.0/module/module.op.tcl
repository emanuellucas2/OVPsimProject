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
This PL configuration instances two Xilinx MicroBlaze processors sub-systems, each with a local and shared memory.
Also included is an area of shared memory that can be accessed by the Microblaze sub-systems or other external master."

set limitations "This is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_DualMicroblaze
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
# Microblaze sub-module 1
#
ihwaddmodule -instancename mbsub1 \
             -vendor safepower.ovpworld.org -type Zynq_PL_SingleMicroblaze \
             -library module -version 1.0
ihwaddbus    -instancename mbsub1_PortBus -addresswidth 32
ihwconnect   -instancename mbsub1 -busport extPort -bus mbsub1_PortBus

#
# Microblaze sub-module 2
#
ihwaddmodule -instancename mbsub2 \
             -vendor safepower.ovpworld.org -type Zynq_PL_SingleMicroblaze \
             -library module -version 1.0
ihwaddbus    -instancename mbsub2_PortBus -addresswidth 32
ihwconnect   -instancename mbsub2 -busport extPort -bus mbsub2_PortBus

#
# Top Level Shared Memory
#
ihwaddbus    -instancename shrmem_Bus -addresswidth 32
ihwaddmemory -instancename shrmem -type ram
ihwconnect   -instancename shrmem -bus shrmem_Bus -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x000fffff

#
# Address Mapping
#
# Input from ARM PS
# 0x41000000 0x44ffffff to mbsub1 shared memory
# 0x45000000 0x48ffffff to mbsub2 shared memory
# 0x4a000000 0x4a0fffff to top level shared memory

# Shared Memory
# 0x00000000 0x000fffff to Shared Memory
# Output to ARM PS
# 0x00100000 0x03ffffff to ARM Processing Sub-system


# Bridge mbsub1 from input port
# 0x41000000 to 0x44ffffff
ihwaddbridge  -instancename msub1_extPort
ihwconnect    -instancename msub1_extPort -busslaveport  sp1 -bus extPortBus     -loaddress 0x41000000 -hiaddress 0x44ffffff
ihwconnect    -instancename msub1_extPort -busmasterport mp1 -bus mbsub1_PortBus -loaddress 0x00000000 -hiaddress 0x03ffffff
# Bridge mbsub2 from input port
# 0x45000000 to 0x48ffffff
ihwaddbridge  -instancename msub2_extPort
ihwconnect    -instancename msub2_extPort -busslaveport  sp1 -bus extPortBus     -loaddress 0x45000000 -hiaddress 0x48ffffff
ihwconnect    -instancename msub2_extPort -busmasterport mp1 -bus mbsub2_PortBus -loaddress 0x00000000 -hiaddress 0x03ffffff
# Bridge shared memory from input port
# 0x4a000000 to 0x4affffff
ihwaddbridge  -instancename shrmem_extPort
ihwconnect    -instancename shrmem_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x4a000000 -hiaddress 0x4a0fffff
ihwconnect    -instancename shrmem_extPort -busmasterport mp1 -bus shrmem_Bus -loaddress 0x00000000 -hiaddress 0x000fffff

# Bridge mbsub1 to output port
# 0x00100000 to 0x03ffffff
ihwaddbridge  -instancename msub1_out_extPort
ihwconnect    -instancename msub1_out_extPort -busslaveport  sp1 -bus mbsub1_PortBus -loaddress 0x00100000 -hiaddress 0x03ffffff
ihwconnect    -instancename msub1_out_extPort -busmasterport mp1 -bus extPortBus     -loaddress 0x00100000 -hiaddress 0x03ffffff
# Bridge mbsub2 to output port
# 0x00100000 to 0x03ffffff
ihwaddbridge  -instancename msub2_out_extPort
ihwconnect    -instancename msub2_out_extPort -busslaveport  sp1 -bus mbsub2_PortBus -loaddress 0x00100000 -hiaddress 0x03ffffff
ihwconnect    -instancename msub2_out_extPort -busmasterport mp1 -bus extPortBus     -loaddress 0x00100000 -hiaddress 0x03ffffff

# Bridge mbsub1 to shared memory 
# 0x00000000 to 0x000fffff
ihwaddbridge  -instancename msub1_shrmem
ihwconnect    -instancename msub1_shrmem -busslaveport  sp1 -bus mbsub1_PortBus -loaddress 0x00000000 -hiaddress 0x000fffff
ihwconnect    -instancename msub1_shrmem -busmasterport mp1 -bus shrmem_Bus     -loaddress 0x00000000 -hiaddress 0x000fffff
# Bridge mbsub2 to shared memory 
# 0x00000000 to 0x000fffff
ihwaddbridge  -instancename msub2_shrmem
ihwconnect    -instancename msub2_shrmem -busslaveport  sp1 -bus mbsub2_PortBus -loaddress 0x00000000 -hiaddress 0x000fffff
ihwconnect    -instancename msub2_shrmem -busmasterport mp1 -bus shrmem_Bus     -loaddress 0x00000000 -hiaddress 0x000fffff

