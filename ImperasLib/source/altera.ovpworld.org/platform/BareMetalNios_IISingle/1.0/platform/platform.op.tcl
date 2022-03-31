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
# NAME : BareMetalNios_IISingle

ihwnew -name BareMetalNios_IISingle  \
                -vendor altera.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal \
                -releasestatus ovp

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an Nios_II Processor.
    The bare metal platform instantiates a single Nios_II processor instance. 
    The processor operate using big endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an Nios_II elf format.
    ./platform.exe application.elf"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "BareMetal platform for execution of Nios_II binary files compiled with CodeSourcery CrossCompiler toolchain."

iadddocumentation  \
    -name Reference  \
    -text "None, baremetal platform definition"

# Use command line parser
ihwaddclp -allargs

 ############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
		-vendor altera.ovpworld.org \
		-library processor \
                -type nios_ii \
		-version 1.0 \
                -semihostvendor altera.ovpworld.org \
                -semihostlibrary semihosting \
                -semihostname nios_iiNewlib \
                -semihostversion 1.0

  ihwaddbus -instancename bus1  \
                -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory  \
		-vendor ovpworld.org \
		-library memory \
                -type ram \
		-version 1.0


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
