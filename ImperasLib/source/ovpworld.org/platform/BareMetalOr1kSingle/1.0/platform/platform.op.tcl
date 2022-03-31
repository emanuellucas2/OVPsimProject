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
# NAME : BareMetalOr1kSingle

ihwnew -name BareMetalOr1kSingle  \
    -vendor ovpworld.org  \
    -library platform  \
    -version 1.0 \
    -releasestatus ovp       \
    -visibility    visible   \
    -purpose       baremetal \
    -verbose \
    -stoponctrlc

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an OR1K Processor.
    The bare metal platform instantiates a single OR1K processor instance. 
    The processor operate using big endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an OR1K elf format.
    ./platform.<ARCH>.exe application.<CROSS>.elf"
iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "BareMetal platform for execution of OR1K binary files compiled with OR1K CrossCompiler toolchain."

iadddocumentation  \
    -name Reference  \
    -text "None"

# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -vendor ovpworld.org -library processor -type or1k \
                -semihostvendor ovpworld.org -semihostname or1kNewlib

  ihwaddbus -instancename bus1 -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory -type ram


########################### connections ###########################

    ihwconnect -instancename cpu1  \
                -busmasterport INSTRUCTION  \
                -bus bus1

    ihwconnect -instancename cpu1  \
                -busmasterport DATA  \
                -bus bus1

    ihwconnect -instancename memory  \
                -busslaveport sp1  \
                -bus bus1  \
                -loaddress 0x00000000  \
                -hiaddress 0xffffffff

