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

set desc "This module implements a default of the Xilinx Zynq Programmable Logic (PL).
This PL configuration instances no devices or memory."

set limitations "The is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_RO
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

# Bus
ihwaddbus -instancename mBus  -addresswidth 32

# Bridge local memory from input port
# 0x43C10000 to 0x43C3ffff
ihwaddbridge  -instancename smem_extPort
ihwconnect    -instancename smem_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x43C10000 -hiaddress 0x43C3ffff
ihwconnect    -instancename smem_extPort -busmasterport mp1 -bus mBus       -loaddress 0x43C10000 -hiaddress 0x43C3ffff


# Ring Oscillators
ihwaddperipheral -instancename ro0 -type ring_oscillator -vendor safepower.ovpworld.org
ihwconnect       -instancename ro0 -bus mBus -busslaveport bport1 -loaddress 0x43c10000 -hiaddress 0x43c10fff

ihwaddperipheral -instancename ro1 -type ring_oscillator -vendor safepower.ovpworld.org
ihwconnect       -instancename ro1 -bus mBus -busslaveport bport1 -loaddress 0x43c20000 -hiaddress 0x43c20fff

ihwaddperipheral -instancename ro2 -type ring_oscillator -vendor safepower.ovpworld.org
ihwconnect       -instancename ro2 -bus mBus -busslaveport bport1 -loaddress 0x43c30000 -hiaddress 0x43c30fff


# The Ring Oscillators provide a count value to software
# The current count value may be in a memory if one is connected
# This is initialised then may be updated by a harness or intercept library access
for {set i 0} {$i < 3} {incr i} {
    # ROi Count Value Memory
    ihwaddmemory -instancename ro${i}M -type ram
    ihwaddbus    -instancename ro${i}CntBus  -addresswidth 2
    ihwconnect   -instancename ro${i}  -bus ro${i}CntBus -busmasterport rocount
    ihwconnect   -instancename ro${i}M -bus ro${i}CntBus -busslaveport sp1 -loaddress 0x0 -hiaddress 0x3
}
