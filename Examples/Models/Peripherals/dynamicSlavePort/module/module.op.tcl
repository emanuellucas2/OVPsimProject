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


ihwnew -name testDynamic

# Bus
ihwaddbus -instancename bus -addresswidth 32

# Processor (ARM7TDMI)
ihwaddprocessor -instancename cpu1 \
           -vendor arm.ovpworld.org -library processor -type arm -version 1.0 \
	   -semihostvendor arm.ovpworld.org -semihostname armNewlib \
	   -variant ARM7TDMI
ihwconnect -bus bus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus -instancename cpu1 -busmasterport DATA

# low memory
ihwaddmemory -instancename mem1 -type ram
ihwconnect -bus bus -instancename mem1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0fffffff

# high memory
ihwaddmemory -instancename mem2 -type ram
ihwconnect -bus bus -instancename mem2 -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0xffffffff

# Dynamic peripheral (behavior loaded from local file)
# has a dynamic slave port (default mapping 0x10000000 : 0x1000001f)
ihwaddperipheral -instancename dynamic -modelfile peripheral/pse.pse
ihwconnect -instancename dynamic -bus bus -busslaveport hostif
