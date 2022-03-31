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
# NAME : BareMetalMips32Dual

ihwnew -name BareMetalMipsDual  \
                -vendor mips.ovpworld.org  \
                -library platform  \
                -version 1.0 \
		-stoponctrlc \
		-purpose baremetal \
                -releasestatus ovp \
                -visibility visible 

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for a MIPS32 Processor (default 74Kc).
    The bare metal platform instantiates two MIPS32 processor instances. 
    The processor operates using big endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to a MIPS elf format.
    The same application executes on each processor. There is no sharing of data.
    It may also be passed a new variant to be used (default 74Kc)
    ./platform.OS.exe --program application.CROSS.elf \[--variant <model variant>\]"

iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

iadddocumentation  \
	-name Limitations  \
	-text "BareMetal platform for execution of MIPS MIPS32 binary files compiled with CodeSourcery CrossCompiler toolchain."

iadddocumentation  \
	-name Reference  \
	-text "None"

# Use command line parser
ihwaddclp -allargs
    
for {set instance 0} {$instance < 2} { incr instance} {

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu${instance}  \
                -type mips32_r1r5 \
                -endian big \
                -vendor mips.ovpworld.org \
                -library processor \
                -semihostname mips32Newlib \
                -semihostvendor mips.ovpworld.org \
                -enableintercepts

  ihwsetparameter  \
                -handle cpu${instance}  \
                -name variant  \
                -value 74Kc    \
                -type enum

  ihwaddbus -instancename bus${instance}  \
                -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory${instance}  \
                -type ram


########################### connections ###########################

  ihwconnect -instancename cpu${instance}  \
                -busmasterport INSTRUCTION  \
                -bus bus${instance}

  ihwconnect -instancename cpu${instance}  \
                -busmasterport DATA  \
                -bus bus${instance}

  ihwconnect -instancename memory${instance}  \
                -busslaveport sp1  \
                -bus bus${instance}  \
                -loaddress 0x00000000  \
                -hiaddress 0xffffffff

}
