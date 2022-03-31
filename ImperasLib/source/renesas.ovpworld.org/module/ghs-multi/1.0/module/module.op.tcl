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
# NAME : ghs-multi

ihwnew -name ghs-multi  \
       -vendor renesas.ovpworld.org  \
       -library module  \
       -version 1.0 \
       -stoponctrlc \
       -purpose module -releasestatus ovp

iadddocumentation  \
                -name Description  \
                -text "Platform Compatible with Greenhills Compiler Output for a V850E1 Processor.
    The bare metal platform instantiates a single V850 processor instance. 
    The processor operate using big endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The ICM platform can be passed any application compiled to an V850 elf format.
    ./platform.<OS>.exe --program application.elf"

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "BareMetal platform to support images generated with Greenhills Compiler targeting a V850E1 Processor"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"


############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -type v850 \
                -semihostname v850Newlib \
                -vendor renesas.ovpworld.org \
                -library processor \
                -version 1.0 \
		        -mips 100 

  ihwsetparameter -handle cpu1 -name variant       -value V850E1    -type enum
    
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
