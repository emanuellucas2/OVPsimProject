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

ihwnew -name externalMemory

ihwaddbus -instancename bus -addresswidth 32

ihwaddprocessor -instancename cpu1 -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -semihostname or1kNewlib \
                -variant generic

ihwconnect -bus bus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus -instancename cpu1 -busmasterport DATA

# memory map
# 0x00000000 - 0x003fffff : fixed memory mem1
# 0x00400000 - 0x00400fff : external memory (callbacks). see module.c
# 0x00401000 - 0xffffffff : fixed memory mem2
ihwaddmemory -instancename mem1 -type ram
ihwconnect -bus bus -instancename mem1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x003fffff
ihwaddmemory -instancename mem2 -type ram
ihwconnect -bus bus -instancename mem2 -busslaveport sp1 -loaddress 0x00401000 -hiaddress 0xffffffff
