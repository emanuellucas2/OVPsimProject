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
ihwnew -name bridge

ihwaddbus -instancename busM -addresswidth 32
iadddocumentation -name Description -text "master bus"

ihwaddbus -instancename busS -addresswidth 32
iadddocumentation -name Description -text "slave bus"

#
# bridge
#
ihwaddbridge -instancename br1

#
# the range of addresses 0x1000 - 0x2fff go through the bridge, coming out at addresses
# 0x10000000 - 0x10001fff
#
ihwconnect -bus busM  -busslaveport  ps -instancename br1 -loaddress 0x1000 -hiaddress 0x2fff

#
# addresses going through the bridge changed to start at 0x10000000
#
ihwconnect -bus busS  -busmasterport pm -instancename br1 -loaddress 0x10000000 -hiaddress 0x10001fff

# create and name the module's external bus ports

ihwaddbusport -instancename busMport
ihwaddbusport -instancename busSport

# connect the external bus ports to the buses

ihwconnect -busport busMport -bus busM
ihwconnect -busport busSport -bus busS


