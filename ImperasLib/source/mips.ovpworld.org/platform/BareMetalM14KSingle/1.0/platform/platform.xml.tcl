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
# NAME : BareMetalM14KSingle

ihwnew -name BareMetalM14KSingle  \
                -vendor mips.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal \
                -releasestatus ovp

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for a MIPS M14K Processor.
                The bare metal platform instantiates a single M14K processor instance, using big endian data ordering.
                        
                The platform can be passed any application compiled to a MIPS elf format as the argument 
                It will also allow a port number to be specified to allow the connection of a remote GDB debugger.
                
                platform.OS.exe -program application.CROSS.elf \[-port <gdb port number>\]
                
                Where OS is Linux or Windows"

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
		-name Limitations  \
		-text "BareMetal platform for execution of MIPS M14K binary files compiled with CodeSourcery CrossCompiler toolchain."

iadddocumentation  \
		-name Reference  \
		-text "None"

# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu0  \
                -endian big  \
                -type    mips32_r1r5 \
                -library processor \
                -vendor  mips.ovpworld.org \
                -variant M14K \
                -semihostvendor mips.ovpworld.org \
                -semihostlibrary semihosting \
                -semihostname mips32Newlib \
                -semihostversion 1.0

  ihwaddbus -instancename bus1  \
                -addresswidth 32

############################## memory #############################

  ihwaddmemory -type ram -instancename memory

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
