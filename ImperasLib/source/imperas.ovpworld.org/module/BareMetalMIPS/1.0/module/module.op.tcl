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


ihwnew -name BareMetalMIPS  \
                -vendor  imperas.ovpworld.org  \
                -library module  \
                -version 1.0 \
                -purpose module \
                -releasestatus ovp \
                -visibility visible

iadddocumentation -name Description  \
                  -text "Bare Metal hardware defintion with an MIPS32 Processor."

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "BareMetal platform for execution of MIPS MIPS32 binary elf files."

iadddocumentation -name Reference   -text "None"

# formal parameter allows the main bus size to be modified (required to support 64-bit processors)
set mainBusAddressBits 32
ihwaddformalparameter -name addressbits  -defaultvalue ${mainBusAddressBits} -max 64 -min 32 -type uns32
iadddocumentation -name Description -text "Allows the address bits for the main bus to be modified (default $mainBusAddressBits)"

ihwaddbus -instancename bus -addresswidth {addressbits}

ihwaddprocessor -instancename cpu  \
                -vendor  mips.ovpworld.org -library processor -type    mips32_r1r5 \
                -defaultsemihost

ihwconnect -instancename cpu -busmasterport INSTRUCTION -bus bus
ihwconnect -instancename cpu -busmasterport DATA        -bus bus

ihwaddmemory -instancename memory1 -type ram
ihwconnect   -instancename memory1  \
             -busslaveport sp1 -bus bus \
             -loaddress 0x00000000 -hiaddress 0x400fffff \
                
ihwaddmemory -instancename memory2 -type ram
ihwconnect   -instancename memory2  \
             -busslaveport sp1 -bus bus \
             -loaddress 0x40110000 -hiaddress 0xffffffff \

#####################################################################################
# Export Bus to allow external connections
#####################################################################################
ihwaddbusport -instancename pBusP
ihwaddbus     -instancename pBusMapped -addresswidth 32
ihwconnect    -busport pBusP -bus pBusMapped
# Map memory map 0x40000000 to 0x4010ffff to bottom of bus port 
ihwaddbridge  -instancename pBusBridge
ihwconnect    -instancename pBusBridge -busslaveport  sp1 -bus bus        -loaddress 0x40100000 -hiaddress 0x4010ffff
ihwconnect    -instancename pBusBridge -busmasterport mp1 -bus pBusMapped -loaddress 0x00000000 -hiaddress 0x0000ffff
