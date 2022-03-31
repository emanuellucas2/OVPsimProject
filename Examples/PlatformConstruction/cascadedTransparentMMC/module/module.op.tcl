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

ihwnew -name cascadedTransparentMMC

ihwaddbus -instancename PIbus -addresswidth 32
ihwaddbus -instancename PDbus -addresswidth 32
ihwaddbus -instancename L1Ibus -addresswidth 32
ihwaddbus -instancename L1Dbus -addresswidth 32
ihwaddbus -instancename mbus -addresswidth 32

#
# Add a processor to do some reading and writing
#
ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -variant generic \
                -semihostname or1kNewlib
ihwconnect -bus PIbus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus PDbus -instancename cpu1 -busmasterport DATA

#
# Add MMC L1 Instruction Cache
#
ihwaddmmc -instancename mmcl1i \
    -vendor "ovpworld.org" -library "mmc" -type "wb_1way_32byteline_2048tags" -version "1.0" \
    -transparent
ihwconnect -bus PIbus -instancename mmcl1i -busslaveport sp1
ihwconnect -bus L1Ibus -instancename mmcl1i -busmasterport mp1

#
# Add MMC L1 Data Cache
#
ihwaddmmc -instancename mmcl1d \
    -vendor "ovpworld.org" -library "mmc" -type "wb_1way_32byteline_2048tags" -version "1.0" \
    -transparent
ihwconnect -bus PDbus -instancename mmcl1d -busslaveport sp1
ihwconnect -bus L1Dbus -instancename mmcl1d -busmasterport mp1


#
# Add MMC L2 Cache
#
ihwaddmmc -instancename mmcl2 \
    -vendor "ovpworld.org" -library "mmc" -type "wb_1way_32byteline_2048tags" -version "1.0" \
    -transparent
ihwconnect -bus L1Ibus -instancename mmcl2 -busslaveport sp1
ihwconnect -bus L1Dbus -instancename mmcl2 -busslaveport sp2
ihwconnect -bus mbus   -instancename mmcl2 -busmasterport mp1
ihwsetparameter -handle mmcl2 -name numSlavePorts -value 2 -type Uns32

#
# Memory on the main bus
#
ihwaddmemory -instancename ramM -type ram
ihwconnect -bus mbus -instancename ramM -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x003fffff
ihwaddmemory -instancename ramMStack -type ram
ihwconnect -bus mbus -instancename ramMStack -busslaveport sp1 -loaddress 0x00401000 -hiaddress 0xffffffff
