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
# NAME : BareMetalArmCortexADual

ihwnew -name BareMetalArmCortexADual  \
                -vendor arm.ovpworld.org  \
                -library platform  \
                -version 1.0 \
		-stoponctrlc \
                -purpose baremetal -releasestatus ovp

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an ARM Cortex-A series Processor (default Cortex-A9UP).
    The bare metal platform instantiates two ARM Cortex-A series processor instances. 
    The processor operates using little endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an ARM elf format. The
    same application executes on each processor. There is no sharing of data.
    It may also be passed a new variant to be used (default Cortex-A9UP)
    ./platform.OS.exe application.CROSS.elf \[model variant\]"

iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

iadddocumentation  \
  -name Limitations  \
  -text "BareMetal platform for execution of ARM binary files compiled with Linaro 32-bit CrossCompiler toolchain for Cortex-A."

iadddocumentation  \
  -name Reference  \
  -text "None"

for {set instance 0} {$instance < 2} { incr instance} {

# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu${instance}  \
                -type arm \
                -endian little \
                -vendor arm.ovpworld.org \
                -semihostname armNewlib \
                -semihostvendor arm.ovpworld.org \
                -enableintercepts

    ihwsetparameter  \
                -handle cpu${instance}  \
                -name   variant  \
                -value  Cortex-A9UP \
                -type   enum

    ihwsetparameter  \
                -handle cpu${instance}  \
                -name   compatibility  \
                -value  nopSVC \
                -type   enum

    ihwsetparameter  \
                -handle cpu${instance}  \
                -name   UAL  \
                -value  1 \
                -type   bool



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
