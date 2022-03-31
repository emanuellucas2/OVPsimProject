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

ihwnew -name byteSwapperMMC

ihwaddbus -instancename busMain -addresswidth 32
ihwaddbus -instancename busInter -addresswidth 32
ihwaddbus -instancename busPeripheral -addresswidth 32

#
# Add a processor to do some reading and writing
#
ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
		-variant generic \
		-semihostname or1kNewlib
ihwconnect -bus busMain -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus busMain -instancename cpu1 -busmasterport DATA

#
# Memory on the main bus - directly mapped to processor
#
ihwaddmemory -instancename ramM -type ram
ihwconnect -bus busMain -instancename ramM -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0000ffff
ihwaddmemory -instancename ramMStack -type ram
ihwconnect -bus busMain -instancename ramMStack -busslaveport sp1 -loaddress 0xffff0000 -hiaddress 0xffffffff

#
# bridge so only required address range goes through MMC
#
ihwaddbridge -instancename br1
ihwconnect -bus busMain  -busslaveport  ps -instancename br1 -loaddress 0x80000000 -hiaddress 0x8000000f
ihwconnect -bus busInter -busmasterport pm -instancename br1 -loaddress 0x80000000 -hiaddress 0x8000000f

#
# Add MMC byte Swapper
#
ihwaddmmc -instancename swap \
    -vendor "ovpworld.org" -library "mmc" -type "endianSwap" -version "1.0"
ihwconnect -bus busInter -instancename swap -busslaveport sp1
ihwconnect -bus busPeripheral -instancename swap -busmasterport mp1

#
# Add a peripheral as the target of the reading and writing
#
ihwaddperipheral -instancename Simple32 -modelfile "peripheral/pse.pse"
ihwconnect -bus busPeripheral -instancename Simple32 -busslaveport sp1 -loaddress 0x80000000 -hiaddress 0x8000000f
