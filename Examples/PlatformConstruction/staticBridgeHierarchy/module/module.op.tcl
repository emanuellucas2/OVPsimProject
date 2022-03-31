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

ihwnew -name staticBridge

#
# this is the master
#
ihwaddbus -instancename busM -addresswidth 32

#
# This is the slave
#
ihwaddbus -instancename busS -addresswidth 32

#
# bridge
#
ihwaddbridge -instancename br1

#
# the range of addresses 0x10000000 - 0x10002fff go through the bridge
#
ihwconnect -bus busM  -busslaveport  ps -instancename br1 -loaddress 0x10000000 -hiaddress 0x10001fff

#
# addresses going through the bridge get 0x10000000 added
#
ihwconnect -bus busS  -busmasterport pm -instancename br1 -loaddress 0x20000000 -hiaddress 0x20001fff

#
# Add a processor to do some reading and writing
#
ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -variant generic \
                -semihostname or1kNewlib
ihwconnect -bus busM -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus busM -instancename cpu1 -busmasterport DATA

#
# Memory on the master bus - directly mapped to processor
#
ihwaddmemory -instancename ramM -type ram
ihwconnect -bus busM -instancename ramM -busslaveport sp1 -loaddress 0x0 -hiaddress 0x0fffffff
ihwaddmemory -instancename ramMStack -type ram
ihwconnect -bus busM -instancename ramMStack -busslaveport sp1 -loaddress 0x1fff0000 -hiaddress 0xffffffff

#
# Memory on the slave bus - mapped using bridge to processor
#
ihwaddmemory -instancename ramS -type ram
ihwconnect -bus busS -instancename ramS -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0x20001fff
