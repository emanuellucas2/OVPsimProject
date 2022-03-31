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

ihwnew -name test

ihwaddbus -instancename mainBus -addresswidth 32

ihwaddprocessor -instancename cpu1 -vendor ovpworld.org -library processor \
    -type or1k -version 1.0 -semihostname or1kNewlib -variant generic
ihwconnect -bus mainBus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus mainBus -instancename cpu1 -busmasterport DATA

ihwaddmemory -instancename ram1 -type ram
ihwaddmemory -instancename ram2 -type ram
ihwconnect -bus mainBus -instancename ram1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0fffffff
ihwconnect -bus mainBus -instancename ram2 -busslaveport sp1 -loaddress 0xf0000000 -hiaddress 0xffffffff


#
# LCD 7 SEG
#
ihwaddperipheral -instancename pse0 -modelfile peripheral/pse.pse
ihwconnect -bus mainBus -instancename pse0 -busslaveport bport \
    -loaddress 0x80000000 -hiaddress 0x8000001f

    
