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
# NAME : BareMetalPowerPc32Single

ihwnew -name BareMetalPowerPc32Single  \
                -vendor power.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal \
                -releasestatus ovp

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an PowerPc32 Processor.
    The bare metal platform instantiates a single PowerPc32 processor instance. 
    The processor operates using big and little endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an PowerPc32 elf format.
    ./platform.<OS>exe --program application.elf"
iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation  \
-name Limitations  \
-text "BareMetal platform for execution of PowerPc32 binary files."

iadddocumentation  \
-name Reference  \
-text "None, baremetal platform definition"


# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -vendor power.ovpworld.org \
                -type powerpc32 \
                -endian big \
                -semihostname powerpc32Newlib

  ihwaddbus -instancename bus1  \
                -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory  \
                -type ram


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

