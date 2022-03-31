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

# add bus
ihwaddbus -instancename mainBus -addresswidth 32

# add processor
ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -variant generic \
                -semihostname or1kNewlib

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
ihwsetparameter -handle subUart0 -name baseAddress -value 0x100003e8    -type uns64
ihwsetparameter -handle subUart0 -name logFileName -value uartTTY0.log  -type string

# Add instance 1 of the submodule
ihwaddmodule -instancename subUart1 -modelfile submodule/model
ihwconnect -instancename subUart1 -busport mainBusPort -bus mainBus 
# configure parameters
ihwsetparameter -handle subUart1 -name baseAddress -value 0x100003f8     -type uns64
ihwsetparameter -handle subUart1 -name logFileName -value uartTTY1.log   -type string
