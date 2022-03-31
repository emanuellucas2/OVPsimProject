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
# NAME : BareMetalMips64Single

ihwnew -name BareMetalMips64Single  \
                -vendor mips.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal \
                -releasestatus ovp \
                -visibility visible

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an MIPS64 Processor.
    The bare metal platform instantiates a single MIPS64 processor instance. 
    The processor operate using big endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an MIPS64 elf format.
    ./platform.OS.exe --program application.CROSS.elf
    
    If this platform is not part of your installation, then it is available for download from www.OVPworld.org."

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"
iadddocumentation  \
	-name Limitations  \
	-text "BareMetal platform for execution of MIPS MIPS64 binary files compiled with MIPS SDK CrossCompiler toolchain."

iadddocumentation  \
	-name Reference  \
	-text "None"

# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu0  \
                -endian big  \
                -type mips64_r1r5 \
                -library processor \
                -vendor mips.ovpworld.org \
                -semihostvendor mips.ovpworld.org \
                -semihostlibrary semihosting \
                -semihostname mips64Newlib \
                -semihostversion 1.0



  ihwaddbus -instancename bus1  \
                -addresswidth 36

############################## memory #############################

  ihwaddmemory -instancename memory  \
                -type ram


########################### connections ###########################

    ihwconnect -instancename cpu0  \
                -busmasterport INSTRUCTION  \
                -bus bus1

    ihwconnect -instancename cpu0  \
                -busmasterport DATA  \
                -bus bus1

    ihwconnect -instancename memory  \
                -busslaveport sp1  \
                -bus bus1  \
                -loaddress 0x00000000  \
                -hiaddress 0xffffffff

