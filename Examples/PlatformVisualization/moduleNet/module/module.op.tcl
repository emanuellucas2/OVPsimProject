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

ihwnew -name processorExternalInterrupt  \
        -vendor example.ovpworld.org  \
        -library platform  \
        -version 1.0 \
        -purpose baremetal -releasestatus ovp

iadddocumentation  \
        -name Description  \
        -text "Design instancing a processor and a peripheral
               that generates a timer tick connected to the processor interrupt line."

iadddocumentation  \
        -name Licensing  \
        -text "Open Source Apache 2.0"

iadddocumentation  \
        -name Limitations  \
        -text "None"

iadddocumentation  \
        -name Reference  \
        -text "Simple example hardware module design."

ihwaddbus -instancename bus1 -addresswidth 32

# interrupt connection
ihwaddnet -instancename tickInterrupt

ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -semihostname or1kNewlib \
                -variant generic \
                -simulateexceptions

ihwconnect -bus bus1 -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus1 -instancename cpu1 -busmasterport DATA

# connect tickInterrupt to cpu1 intr0
ihwconnect -instancename cpu1 -netport intr0 -net tickInterrupt

ihwaddmemory -instancename mem1 -type ram
ihwconnect   -instancename mem1 -bus bus1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x1fffffff
ihwaddmemory -instancename mem2 -type ram
ihwconnect   -instancename mem2 -bus bus1 -busslaveport sp1 -loaddress 0xf0000000 -hiaddress 0xffffffff

########################### timer peripheral ###########################

ihwaddperipheral -instancename timerPeripheral  \
                 -type simpleTimer \
                 -modelfile peripheral/pse.pse

# acknowledge register
ihwconnect   -instancename timerPeripheral -bus bus1 -busslaveport SP -loaddress 0xe0000000 -hiaddress 0xe0000003

# timer tick interrupt
ihwconnect -instancename timerPeripheral -netport tickOut  -net tickInterrupt

ihwaddformalmacro -name OP_HTTP_VIS_PORT_FORMALS
