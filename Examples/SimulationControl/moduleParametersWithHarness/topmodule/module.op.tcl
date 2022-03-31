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

ihwnew -name topmodule

#
# Add formal parameters that can be set when module instanced
#
ihwaddformalparameter -name subUart0Address -type address
iadddocumentation -name Description -text "Set base address of UART in sub-system 0"
# If this variable is 1 we will have two separate base address parameters
#   otherwise both based from same with offset 0x10
set dualbase 1
if { $dualbase == 1 } {
  ihwaddformalparameter -name subUart1Address -type address
  iadddocumentation -name Description -text "Set base address of UART in sub-system 1"
}

# add bus
ihwaddbus -instancename mainBus -addresswidth 32

# add processor
ihwaddprocessor -instancename cpu1 \
                -vendor riscv.ovpworld.org -library processor -type riscv -version 1.0 \
                -variant RV32I \
                -semihostvendor riscv.ovpworld.org -semihostname pk

# connect processor to bus
ihwconnect -bus mainBus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus mainBus -instancename cpu1 -busmasterport DATA

# add memories
ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus mainBus -instancename ram1 -busslaveport sp1 -loaddress 0x0 -hiaddress 0x0fffffff

ihwaddmemory -instancename ram2 -type ram
ihwconnect -bus mainBus -instancename ram2 -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0xffffffff

# Add instance 0 of the submodule
ihwaddmodule -instancename subUart0 -modelfile submodule/model
ihwconnect -instancename subUart0 -busport mainBusPort -bus mainBus
# configure parameters
ihwsetparameter -handle subUart0 -name baseAddress -value {subUart0Address}     -type uns64

# Add instance 1 of the submodule
ihwaddmodule -instancename subUart1 -modelfile submodule/model
ihwconnect -instancename subUart1 -busport mainBusPort -bus mainBus 
# configure parameters
if { $dualbase == 1 } {
  ihwsetparameter -handle subUart1 -name baseAddress -value {subUart1Address}   -type uns64
} else {
  # equally we could use a single formal and base all other devices on this
  ihwsetparameter -handle subUart1 -name baseAddress -value {subUart0Address + 0x10} -type uns64
}
