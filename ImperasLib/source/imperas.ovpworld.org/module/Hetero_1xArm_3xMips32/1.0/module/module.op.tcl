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

ihwnew \
    -name Hetero_1xArm_3xMips32  \
    -vendor imperas.ovpworld.org  \
    -library module  \
    -version 1.0 \
    -stoponctrlc \
    -purpose module -releasestatus imperas

iadddocumentation  \
    -name Description  \
    -text "This is a hardware definition that instantiates 1 ARM processor and 3 MIPS processors.
           Each processor has private independent memory areas from 0x00000000 to 0x01ffffff and from 0x0fff0000 to 0x0fffffff.
           There is a shared area of memory that appears from 0x02000000 to 0x02ffffff in each processor memory map. "

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

############################ Shared Memory ############################
    
    ihwaddbus -instancename busS  -addresswidth 32

    ihwaddmemory -instancename sharedMem  -type ram

    ihwconnect -instancename sharedMem  \
               -busslaveport sp1  -bus busS  \
               -loaddress 0x02000000 -hiaddress 0x02ffffff

############################ processor ARM (Cortex-A9UP) #######################

  ihwaddprocessor  \
                -instancename CPU0_ARM  \
                -vendor arm.ovpworld.org \
                -id 0  \
                -endian little \
                -type arm \
                -enableintercepts \
                -defaultsemihost

    ihwsetparameter  -handle CPU0_ARM  \
                     -name variant -value Cortex-A9UP -type enum

    ihwsetparameter  -handle CPU0_ARM  \
                     -name compatibility -value nopSVC -type enum

    ihwaddbus -instancename bus0  -addresswidth 32
        
    ihwconnect -instancename CPU0_ARM -busmasterport INSTRUCTION -bus bus0

    ihwconnect -instancename CPU0_ARM -busmasterport DATA -bus bus0

    ihwaddmemory -instancename mem0 -type ram

    ihwconnect -instancename mem0  \
               -busslaveport sp1 -bus bus0  \
               -loaddress 0x00000000 -hiaddress 0x01ffffff

    ihwaddmemory -instancename mem0h -type ram

    ihwconnect -instancename mem0h  \
               -busslaveport sp1 -bus bus0  \
               -loaddress 0x0fff0000 -hiaddress 0x0fffffff

    ihwaddbridge -instancename br0
    ihwconnect -instancename br0 \
               -busslaveport sp1  -bus bus0 \
               -loaddress 0x02000000 -hiaddress 0x02ffffff
    ihwconnect -instancename br0 \
               -busmasterport mp1  -bus busS \
               -loaddress 0x02000000 -hiaddress 0x02ffffff

############################ processor MIPS32 (24KEc) ##########################

    ihwaddprocessor  \
                -instancename CPU1_MIPS  \
                -vendor mips.ovpworld.org \
                -id 1  \
                -endian little \
                -type mips32_r1r5 \
                -enableintercepts \
                -defaultsemihost

    ihwsetparameter -handle CPU1_MIPS -name variant -value 24KEc -type enum

    ihwaddbus -instancename bus1  -addresswidth 32

    ihwconnect -instancename CPU1_MIPS -busmasterport INSTRUCTION -bus bus1

    ihwconnect -instancename CPU1_MIPS -busmasterport DATA -bus bus1

    ihwaddmemory -instancename mem1 -type ram

    ihwconnect -instancename mem1  \
               -busslaveport sp1 -bus bus1  \
               -loaddress 0x00000000 -hiaddress 0x01ffffff

    ihwaddmemory -instancename mem1h -type ram
    
    ihwconnect -instancename mem1h  \
               -busslaveport sp1 -bus bus1  \
               -loaddress 0x0fff0000 -hiaddress 0x0fffffff
    
    ihwaddbridge -instancename br1
    ihwconnect -instancename br1 \
               -busslaveport sp1  -bus bus1 \
               -loaddress 0x02000000 -hiaddress 0x02ffffff
    ihwconnect -instancename br1 \
               -busmasterport mp1  -bus busS \
               -loaddress 0x02000000 -hiaddress 0x02ffffff


############################ processor ############################

    ihwaddprocessor  \
                -instancename CPU2_MIPS  \
                -id 2  \
                -vendor mips.ovpworld.org \
                -endian little \
                -type mips32_r1r5 \
                -enableintercepts \
                -defaultsemihost

    ihwsetparameter -handle CPU2_MIPS -name variant -value 24KEc -type enum

    ihwaddbus -instancename bus2  -addresswidth 32

    ihwconnect -instancename CPU2_MIPS -busmasterport INSTRUCTION -bus bus2

    ihwconnect -instancename CPU2_MIPS -busmasterport DATA -bus bus2

    ihwaddmemory -instancename mem2 -type ram

    ihwconnect -instancename mem2  \
               -busslaveport sp1 -bus bus2  \
               -loaddress 0x00000000 -hiaddress 0x01ffffff

    ihwaddmemory -instancename mem2h -type ram
    
    ihwconnect -instancename mem2h  \
               -busslaveport sp1 -bus bus2  \
               -loaddress 0x0fff0000 -hiaddress 0x0fffffff
    
    # bridge to shared bus 
    ihwaddbridge -instancename br2
    ihwconnect -instancename br2 \
               -busslaveport sp1  -bus bus2 \
               -loaddress 0x02000000 -hiaddress 0x02ffffff
    ihwconnect -instancename br2 \
               -busmasterport mp1  -bus busS \
               -loaddress 0x02000000 -hiaddress 0x02ffffff

############################ processor ############################

    ihwaddprocessor  \
                -instancename CPU3_MIPS  \
                -id 3  \
                -vendor mips.ovpworld.org \
                -endian little \
                -type mips32_r1r5 \
                -enableintercepts \
                -defaultsemihost

    ihwsetparameter -handle CPU3_MIPS -name variant -value 24KEc -type enum

    ihwaddbus -instancename bus3  -addresswidth 32

    ihwconnect -instancename CPU3_MIPS -busmasterport INSTRUCTION -bus bus3

    ihwconnect -instancename CPU3_MIPS -busmasterport DATA -bus bus3

    ihwaddmemory -instancename mem3 -type ram

    ihwconnect -instancename mem3  \
               -busslaveport sp1 -bus bus3  \
               -loaddress 0x00000000 -hiaddress 0x01ffffff

    ihwaddmemory -instancename mem3h -type ram

    ihwconnect -instancename mem3h  \
               -busslaveport sp1 -bus bus3  \
               -loaddress 0x0fff0000 -hiaddress 0x0fffffff

    # bridge to shared bus 
    ihwaddbridge -instancename br3
    ihwconnect -instancename br3 \
               -busslaveport sp1  -bus bus3 \
               -loaddress 0x02000000 -hiaddress 0x02ffffff
    ihwconnect -instancename br3 \
               -busmasterport mp1  -bus busS \
               -loaddress 0x02000000 -hiaddress 0x02ffffff
