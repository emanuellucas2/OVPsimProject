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

# SUB MODULE definition

ihwnew -name sub
iadddocumentation -name Description -text "This a sub module that includes CPU Memory and UART"
 
ihwaddbus -instancename mainBus -addresswidth 32
ihwaddnet -instancename directWrite
ihwaddnet -instancename directRead

ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -variant generic \
                -semihostname or1kNewlib

ihwconnect -bus mainBus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus mainBus -instancename cpu1 -busmasterport DATA

ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus mainBus -instancename ram1 -busslaveport sp1 -loaddress 0x0 -hiaddress 0x0fffffff

ihwaddmemory -instancename ram2 -type ram
ihwconnect -bus mainBus -instancename ram2 -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0xffffffff

ihwaddperipheral -instancename uart0 -vendor freescale.ovpworld.org -library peripheral -type KinetisUART -version 1.0
ihwconnect -bus mainBus -instancename uart0 -busslaveport  bport1 -loaddress 0x100003f8 -hiaddress 0x100013f7
ihwconnect -net directWrite -instancename uart0 -netport  DirectWrite
ihwconnect -net directRead -instancename uart0 -netport  DirectRead
ihwsetparameter -handle uart0 -name directReadWrite -value 1 -type bool

ihwaddnetport -instancename directWritePort
ihwaddnetport -instancename directReadPort

ihwconnect -netport directWritePort -net directWrite
ihwconnect -netport directReadPort -net directRead



