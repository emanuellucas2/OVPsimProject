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

# module.op.tcl

ihwnew -name twoProcessorShared

#
# Sub-System Zero
#

# add the processor
ihwaddprocessor -type or1k -instancename P0 -semihostname  or1kNewlib -variant generic

# add local memory
ihwaddmemory -type ram -instancename localLow0
ihwaddmemory -type ram -instancename localHigh0

# add the local bus
ihwaddbus -instancename bus0 -addresswidth "32"

# add the bus bridge
ihwaddbridge -instancename bridge0

# add connections to bus0
ihwconnect -bus bus0 -instancename P0         -busmasterport "INSTRUCTION"
ihwconnect -bus bus0 -instancename P0         -busmasterport "DATA"
ihwconnect -bus bus0 -instancename localLow0  -busslaveport  "sp0" -loaddress "0x00000000" -hiaddress "0x10ffffff"
ihwconnect -bus bus0 -instancename bridge0    -busslaveport  "sp0" -loaddress "0x11000000" -hiaddress "0x11ffffff"
ihwconnect -bus bus0 -instancename localHigh0 -busslaveport  "sp0" -loaddress "0x12000000" -hiaddress "0xffffffff"

#
# Sub-System One
#

# add the processor
ihwaddprocessor -type or1k -instancename P1 -semihostname  or1kNewlib -variant generic

# add the local memory
ihwaddmemory -type ram -instancename localLow1
ihwaddmemory -type ram -instancename localHigh1

# add the bus
ihwaddbus -instancename bus1 -addresswidth "32"

# add the bus bridge
ihwaddbridge -instancename bridge1

# add connections to bus1
ihwconnect -bus bus1 -instancename P1         -busmasterport "INSTRUCTION"
ihwconnect -bus bus1 -instancename P1         -busmasterport "DATA"
ihwconnect -bus bus1 -instancename localLow1  -busslaveport  "sp1" -loaddress "0x00000000" -hiaddress "0x10ffffff"
ihwconnect -bus bus1 -instancename bridge1    -busslaveport  "sp1" -loaddress "0x11000000" -hiaddress "0x11ffffff"
ihwconnect -bus bus1 -instancename localHigh1 -busslaveport  "sp1" -loaddress "0x12000000" -hiaddress "0xffffffff"


#
# Shared Resources
#

# add the shared memory
ihwaddmemory -type ram -instancename ramShared

# add the shared bus
ihwaddbus -instancename busShare -addresswidth "32"

# add connections to busShare
# bridge master connections mapping from processor sub-systems
ihwconnect -bus busShare -instancename bridge0   -busmasterport "mp0" -loaddress "0x00000000" -hiaddress "0x00ffffff" 
ihwconnect -bus busShare -instancename bridge1   -busmasterport "mp1" -loaddress "0x00000000" -hiaddress "0x00ffffff"
# connection of shared memory
ihwconnect -bus busShare -instancename ramShared -busslaveport  "sp0" -loaddress "0x00000000" -hiaddress "0x00ffffff" 
