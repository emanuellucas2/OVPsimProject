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

ihwnew -name singleCpuMemory

ihwaddbus -instancename bus1 -addresswidth 32

ihwaddprocessor -instancename cpu1 \
                -vendor riscv.ovpworld.org -library processor -type riscv -version 1.0 \
                -variant RV32IMAC
ihwconnect -bus bus1 -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus1 -instancename cpu1 -busmasterport DATA

# Memory from 0x00000000 to 0xffffffff
ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus bus1 -instancename ram1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0xffffffff
