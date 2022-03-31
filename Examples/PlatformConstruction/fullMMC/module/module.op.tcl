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

ihwnew -name fullMMC

ihwaddbus -instancename ibus -addresswidth 32
ihwaddbus -instancename dbus -addresswidth 32
ihwaddbus -instancename mbus -addresswidth 32

#
# Add a processor to do some reading and writing
#
ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
		-variant generic \
                -semihostname or1kNewlib
ihwconnect -bus ibus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus dbus -instancename cpu1 -busmasterport DATA

#
# Add MMC Instruction Cache
#
ihwaddmmc -instancename mmci \
    -vendor "ovpworld.org" -library "mmc" -type "wb_1way_32byteline_2048tags" -version "1.0"
ihwconnect -bus ibus -instancename mmci -busslaveport sp1
ihwconnect -bus mbus -instancename mmci -busmasterport mp1

#
# Add MMC Data Cache
#
ihwaddmmc -instancename mmcd \
    -vendor "ovpworld.org" -library "mmc" -type "wb_1way_32byteline_2048tags" -version "1.0"
ihwconnect -bus dbus -instancename mmcd -busslaveport sp1
ihwconnect -bus mbus -instancename mmcd -busmasterport mp1

#
# Memory on the main bus
#
ihwaddmemory -instancename ramM -type ram
ihwconnect -bus mbus -instancename ramM -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x003fffff
ihwaddmemory -instancename ramMStack -type ram
ihwconnect -bus mbus -instancename ramMStack -busslaveport sp1 -loaddress 0x00401000 -hiaddress 0xffffffff
