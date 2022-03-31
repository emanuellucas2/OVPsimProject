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

ihwnew -name test -vendor ovpworld.org

ihwaddbus -instancename bus -addresswidth 32

ihwaddprocessor -instancename CPU1 \
                -vendor riscv.ovpworld.org -library processor -type riscv -version 1.0 \
                -variant RVB32I \
                -semihostvendor riscv.ovpworld.org -semihostname pk

ihwsetparameter  -handle CPU1 -name add_Extensions -value MSU  -type string

ihwconnect -bus bus  -instancename CPU1 -busmasterport INSTRUCTION
ihwconnect -bus bus  -instancename CPU1 -busmasterport DATA

ihwaddmemory -instancename memoryL -type ram
ihwconnect -bus bus -instancename memoryL -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x00ffffff

ihwaddmemory -instancename memoryH -type ram
ihwconnect -bus bus -instancename memoryH -busslaveport sp1 -loaddress 0xf0000000 -hiaddress 0xffffffff

ihwaddperipheral -instancename PER1 -modelfile peripheral/pse.pse
ihwconnect -instancename PER1 -busslaveport bport1 -bus bus -loaddress 0x10000000 -hiaddress 0x100000ff
