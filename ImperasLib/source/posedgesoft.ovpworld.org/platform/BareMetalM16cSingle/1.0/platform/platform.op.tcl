#
# Copyright (c) 2011-2016 Posedge Software, Inc., www.posedgesoft.com
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

# NAME : BareMetalM16cSingle

ihwnew -name BareMetalM16cSingle  \
                -vendor posedgesoft.ovpworld.org  \
                -library platform  \
                -version 1.0 \
		-releasestatus ovp       \
		-visibility    visible    \
		-purpose       baremetal \
        -verbose -stoponctrlc

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an M16C Processor.
    The bare metal platform instantiates a single M16C processor instance. 
    The processor operate using big endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an M16C elf format.
    ./platform.<OS>.exe --program application.elf"

iadddocumentation  \
               -name Licensing  \
               -text "Open Source Apache 2.0"

iadddocumentation  \
               -name Limitations  \
               -text "BareMetal platform for execution of M16C binary files compiled with M16C CrossCompiler toolchain."

iadddocumentation  \
               -name Reference  \
               -text "None, baremetal platform definition"

# Use command line parser
ihwaddclp -allargs
    
############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -vendor posedgesoft.ovpworld.org -library processor \
                -type m16c -version 1.0 \
                -semihostvendor posedgesoft.ovpworld.org -semihostname m16cNewlib  \
                -mips 20.0

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
