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

ihwnew -name dualCpuMemory

# first sub-system
ihwaddbus -instancename bus1 -addresswidth 32

ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -semihostname or1kNewlib \
                -variant generic

ihwconnect -bus bus1 -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus1 -instancename cpu1 -busmasterport DATA

ihwaddmemory -instancename mem1_1 -type ram
ihwconnect   -instancename mem1_1 -bus bus1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0xdfffffff
ihwaddmemory -instancename mem1_2 -type ram
ihwconnect   -instancename mem1_2 -bus bus1 -busslaveport sp1 -loaddress 0xf0000000 -hiaddress 0xffffffff

# second sub-system
ihwaddbus -instancename bus2 -addresswidth 32

ihwaddprocessor -instancename cpu2 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -semihostname or1kNewlib \
                -variant generic

ihwconnect -bus bus2 -instancename cpu2 -busmasterport INSTRUCTION
ihwconnect -bus bus2 -instancename cpu2 -busmasterport DATA

ihwaddmemory -instancename mem2_1 -type ram
ihwconnect   -instancename mem2_1 -bus bus2 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0xdfffffff
ihwaddmemory -instancename mem2_2 -type ram
ihwconnect   -instancename mem2_2 -bus bus2 -busslaveport sp1 -loaddress 0xf0000000 -hiaddress 0xffffffff

# Shared memory region
ihwaddbus -instancename busS -addresswidth 32

# bridge bus1 to busS
ihwaddbridge -instancename br1
ihwconnect   -instancename br1 -busslaveport  br1_sp1 -bus bus1 -loaddress 0xe0000000 -hiaddress 0xefffffff
ihwconnect   -instancename br1 -busmasterport br1_mp1 -bus busS -loaddress 0xe0000000 -hiaddress 0xefffffff

# bridge bus2 to busS
ihwaddbridge -instancename br2
ihwconnect   -instancename br2 -busslaveport  br2_sp1 -bus bus2 -loaddress 0xe0000000 -hiaddress 0xefffffff
ihwconnect   -instancename br2 -busmasterport br2_mp1 -bus busS -loaddress 0xe0000000 -hiaddress 0xefffffff

# shared memory
ihwaddmemory -instancename memS -type ram
ihwconnect   -instancename memS -bus busS -busslaveport sp1 -loaddress 0xe0000000 -hiaddress 0xefffffff
