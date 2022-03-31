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

# Setup variables for platform info

set vendor  demo.ovpworld.org
set library platform
set name    simple
set version 1.0


#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version

#
# Install the Imperas Command Line Parser (this is the main difference between a platform and module)
#
ihwaddclp -allargs

#
# Nets
#
ihwaddnet -instancename interrupt
ihwaddnet -instancename intUart

#
# add main bus
#
ihwaddbus -instancename bus1 -addresswidth 32

#
# add main processor with program to load and semihosting selected
#
ihwaddprocessor -instancename cpu1 -type or1k -vendor ovpworld.org \
                -semihostname or1kNewlib
# Connect processor to bus (separate instruction and data buses)
ihwconnect -bus bus1 -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus1 -instancename cpu1 -busmasterport DATA

# Connect processor interrupt line
ihwconnect -net interrupt -instancename  cpu1 -netport intr0

#
# create memory instances and connect to bus at correct address map
#
ihwaddmemory -instancename memory1  -type ram 
ihwconnect -bus bus1 -instancename memory1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0fffffff
ihwaddmemory -instancename memory2  -type ram 
ihwconnect -bus bus1 -instancename memory2 -busslaveport sp1 -loaddress 0xf0000000 -hiaddress 0xffffffff

#
# Add Interrupt Controller Peripheral
#
ihwaddperipheral -instancename intControl -type IntCtrlT -vendor demo.ovpworld.org
# Connect ports onto bus at correct address map
ihwconnect -bus bus1 -instancename  intControl -busslaveport bportscan  -loaddress 0x80000000 -hiaddress 0x80000003
ihwconnect -bus bus1 -instancename  intControl -busslaveport bportien   -loaddress 0x80000100 -hiaddress 0x8000010f
ihwconnect -bus bus1 -instancename  intControl -busslaveport bportlevel -loaddress 0x80000200 -hiaddress 0x8000023f

# connect interrupt lines
ihwconnect -net interrupt -instancename intControl -netport intOut
ihwconnect -net intUart   -instancename intControl -netport int0

#
# Add 16550 UART Peripheral
#
ihwaddperipheral -instancename uart1 -vendor national.ovpworld.org -library peripheral -version 1.0 -type 16550

# Connect ports onto bus at correct address map
ihwconnect       -instancename uart1 -bus bus1 -busslaveport bport1 \
                 -loaddress 0x90000000  \
                 -hiaddress 0x90000007
ihwsetparameter -handle uart1 -type bool -name console            -value 1
ihwsetparameter -handle uart1 -type bool -name finishOnDisconnect -value 1

# connect interrupt line
ihwconnect       -net intUart -instancename uart1 -netport intOut
                 
