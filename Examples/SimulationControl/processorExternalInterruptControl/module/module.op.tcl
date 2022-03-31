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

ihwnew -name processorExternalInterruptControl  \
        -vendor example.ovpworld.org  \
        -library platform  \
        -version 1.0 \
        -purpose baremetal -releasestatus ovp

iadddocumentation  \
        -name Description  \
        -text "Design instancing two processors and a peripheral
               that controls the reset of the processors and 
               that can generate reset when commanded via a socket connection."

iadddocumentation  \
        -name Licensing  \
        -text "Open Source Apache 2.0"

iadddocumentation  \
        -name Limitations  \
        -text "None"

iadddocumentation  \
        -name Reference  \
        -text "Simple example hardware module design."


ihwaddbus -instancename bus -addresswidth 32

ihwaddprocessor -instancename cpu \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -semihostname or1kNewlib \
                -variant generic

ihwconnect -bus bus -instancename cpu -busmasterport INSTRUCTION
ihwconnect -bus bus -instancename cpu -busmasterport DATA

ihwaddmemory -instancename mem -type ram
ihwconnect   -instancename mem -bus bus -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0xffffffff

