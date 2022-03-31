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
# NAME : BareMetalArcSingle

ihwnew -name BareMetalArcSingle  \
                -vendor arc.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal -releasestatus ovp \
                -verbose -stoponctrlc

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an ARC Processor.
    The bare metal platform instantiates a single ARC processor instance. 
    The processor operates using little endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an ARC elf format.
    ./platform.<OS>.exe --program application.<CROSS>.elf"
iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "BareMetal platform for execution of ARC binary files compiled with FOSS for Synopsys DesignWare ARC Processors CrossCompiler toolchain."

iadddocumentation  \
    -name Reference  \
    -text "None, baremetal platform definition"

# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -vendor arc.ovpworld.org -library processor -type arc -version 1.0 \
                -semihostvendor arc.ovpworld.org -semihostname arcNewlib

  ihwsetparameter -handle cpu1 -name variant -type enum -value 700

  ihwaddbus -instancename bus -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory  \
                -vendor ovpworld.org \
                -library memory \
                -type ram \
                -version 1.0


########################### connections ###########################

    ihwconnect -instancename cpu1  \
                -busmasterport INSTRUCTION  \
                -bus bus

    ihwconnect -instancename cpu1  \
                -busmasterport DATA  \
                -bus bus

    ihwconnect -instancename memory  \
                -busslaveport sp1  \
                -bus bus  \
                -loaddress 0x00000000  \
                -hiaddress 0xffffffff
