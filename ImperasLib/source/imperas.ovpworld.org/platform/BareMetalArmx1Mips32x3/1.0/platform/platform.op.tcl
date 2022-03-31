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
# NAME : BareMetalArmx1Mips32x3

ihwnew -name BareMetalArmx1Mips32x3  \
                -vendor imperas.ovpworld.org  \
                -library platform  \
                -version 1.0 \
		-stoponctrlc \
		-purpose baremetal -releasestatus imperas

iadddocumentation  \
                -name Description  \
                -text "
    This is a platform that instantiates 1 ARM processor and 3 MIPS processors.
    Each processor has private independent memory areas from 0x00000000 to 0x9fffffff.
    the ARM processor also has private memory (for stack) from 0xf0000000 to 0xffffffff.
    There is a shared area of memory that appears from 0xa0000000 to 0xbfffffff in each processor memory map. "

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations \
    -text "BareMetal platform for execution of specific example applications for MIPS32 and ARM Cortex-A."
iadddocumentation  \
    -name "Reference" \
    -text "None, BareMetal platform definition"

    # Use command line parser
    ihwaddclp -allargs

############################ buses ############################
    
    
  ihwaddbus -instancename bus0  \
                -addresswidth 32

  ihwaddbus -instancename bus1  \
                -addresswidth 32

  ihwaddbus -instancename bus2  \
                -addresswidth 32

  ihwaddbus -instancename bus3  \
                -addresswidth 32

  ihwaddbus -instancename busS  \
		-addresswidth 32


############################ processor ############################

  ihwaddprocessor  \
                -instancename CPU-0  \
                -vendor arm.ovpworld.org \
                -endian little \
                -type arm \
                -imagefile writer.ARM_CORTEX_A9UP.elf \
                -useobjectentry \
                -enableintercepts

    ihwsetparameter  \
                -handle CPU-0  \
                -name variant  \
                -value Cortex-A9UP \
                -type enum

    ihwsetparameter  \
                -handle CPU-0  \
                -name compatibility  \
                -value nopSVC \
                -type enum



############################ processor ############################

  ihwaddprocessor  \
                -instancename CPU-1  \
                -vendor mips.ovpworld.org \
                -id 1  \
                -endian little \
                -type mips32_r1r5 \
                -imagefile reader1.CS_MIPS32LE.elf \
                -useobjectentry

  ihwsetparameter  \
                -handle CPU-1  \
                -name variant  \
                -value 24KEc \
                -type enum



############################ processor ############################

  ihwaddprocessor  \
                -instancename CPU-2  \
                -id 2  \
                -vendor mips.ovpworld.org \
                -endian little \
              -type mips32_r1r5 \
              -imagefile reader2.CS_MIPS32LE.elf \
              -useobjectentry


  ihwsetparameter  \
                 -handle CPU-2  \
                 -name variant  \
                 -value 24KEc \
                -type enum



############################ processor ############################

  ihwaddprocessor  \
                -instancename CPU-3  \
                -id 3  \
                -vendor mips.ovpworld.org \
                -endian little \
                -type mips32_r1r5 \
                -imagefile reader3.CS_MIPS32LE.elf \
                -useobjectentry


  ihwsetparameter  \
                -handle CPU-3  \
                -name variant  \
                -value 24KEc \
                -type enum


############################## memory #############################

  ihwaddmemory -instancename mem0  \
                -type ram


  ihwaddmemory -instancename mem1  \
                -type ram

  ihwaddmemory -instancename mem2  \
                -type ram

  ihwaddmemory -instancename mem3  \
                -type ram

  ihwaddmemory -instancename shared  \
                -type ram


########################### connections ###########################

#### Processor ####
              
    ihwconnect -instancename CPU-0  \
                -busmasterport INSTRUCTION  \
                -bus bus0

    ihwconnect -instancename CPU-0  \
                -busmasterport DATA  \
                -bus bus0

    ihwconnect -instancename CPU-1  \
                -busmasterport INSTRUCTION  \
                -bus bus1

    ihwconnect -instancename CPU-1  \
                -busmasterport DATA  \
                -bus bus1

    ihwconnect -instancename CPU-2  \
                -busmasterport INSTRUCTION  \
                -bus bus2

    ihwconnect -instancename CPU-2  \
                -busmasterport DATA  \
                -bus bus2

    ihwconnect -instancename CPU-3  \
                -busmasterport INSTRUCTION  \
                -bus bus3

    ihwconnect -instancename CPU-3  \
                -busmasterport DATA  \
                -bus bus3

#### Memory ####

    ihwconnect -instancename mem0  \
                -busslaveport sp1  \
                -bus bus0  \
                -loaddress 0x00000000  \
                -hiaddress 0x01ffffff


    ihwconnect -instancename mem1  \
                -busslaveport sp1  \
                -bus bus1  \
                -loaddress 0x00000000  \
                -hiaddress 0x01ffffff

    ihwconnect -instancename mem2  \
                -busslaveport sp1  \
                -bus bus2  \
                -loaddress 0x00000000  \
                -hiaddress 0x01ffffff

    ihwconnect -instancename mem3  \
                -busslaveport sp1  \
                -bus bus3  \
                -loaddress 0x00000000  \
                -hiaddress 0x01ffffff

########################### sharing ###########################

# bridge buses 
ihwaddbridge -instancename br0
ihwconnect -instancename br0 -busslaveport sp1  -bus bus0 -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwconnect -instancename br0 -busmasterport mp1  -bus busS -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwaddbridge -instancename br1
ihwconnect -instancename br1 -busslaveport sp1  -bus bus1 -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwconnect -instancename br1 -busmasterport mp1  -bus busS -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwaddbridge -instancename br2
ihwconnect -instancename br2 -busslaveport sp1  -bus bus2 -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwconnect -instancename br2 -busmasterport mp1  -bus busS -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwaddbridge -instancename br3
ihwconnect -instancename br3 -busslaveport sp1  -bus bus3 -loaddress 0x02000000 -hiaddress 0x02ffffff
ihwconnect -instancename br3 -busmasterport mp1  -bus busS -loaddress 0x02000000 -hiaddress 0x02ffffff

    ihwconnect -instancename shared  \
                -busslaveport sp1  \
                -bus busS  \
                -loaddress 0x02000000  \
                -hiaddress 0x02ffffff
