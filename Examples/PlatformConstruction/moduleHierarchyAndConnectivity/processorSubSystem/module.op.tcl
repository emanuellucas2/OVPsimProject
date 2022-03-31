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

# module.op.tcl

ihwnew -name processorSubSystem

# local memory Map
# 0xf0000000 - 0xffffffff   Local Memory
# 0x20000000 - 0xefffffff   External Access
# 0x10001000 - 0x1fffffff   
# 0x10000000 - 0x10000fff   Local MailBox
# 0x01000000 - 0xffffffff
# 0x00000000 - 0x00ffffff   Local memory

# external memory map
# 0x10000000 - 0x10000fff   MailBox


# create and name the module's external bus ports
ihwaddbusport -instancename busPortIn
ihwaddbusport -instancename busPortOut

# busses connecting ports
ihwaddbus -instancename busPIn  -addresswidth "32"
ihwaddbus -instancename busPOut -addresswidth "32"

# connect the external mailbox bus ports to the bus
ihwconnect -busport busPortIn  -bus busPIn
ihwconnect -busport busPortOut -bus busPOut


# add the processor
ihwaddprocessor -instancename cpu -type or1k -semihostname  or1kNewlib -variant generic

# main bus 
ihwaddbus -instancename bus -addresswidth "32"

# add processor connections to bus
ihwconnect -instancename cpu -bus bus -busmasterport "INSTRUCTION"
ihwconnect -instancename cpu -bus bus -busmasterport "DATA"

# add memories
# processor local memory
ihwaddmemory -instancename ramLow  -type ram
ihwconnect   -instancename ramLow  -bus bus \
             -busslaveport  "sp" -loaddress "0x00000000" -hiaddress "0x00ffffff"
ihwaddmemory -instancename ramHigh -type ram 
ihwconnect   -instancename ramHigh -bus bus \
             -busslaveport  "sp" -loaddress "0xf0000000" -hiaddress "0xffffffff"

# MailBox memory
ihwaddmemory -instancename ramMB -type ram 
ihwconnect   -instancename ramMB -bus busMB \
             -busslaveport  "sp" -loaddress "0x00000000" -hiaddress "0x00000fff"

# bus from external port to MailBox memory
ihwaddbus -instancename busMB   -addresswidth "32"

# external connections
# outgoing bridge 
ihwaddbridge -instancename bridgeOutMB
ihwconnect   -instancename bridgeOutMB -bus bus     \
             -busslaveport  "sp" -loaddress "0x20000000" -hiaddress "0xefffffff"
ihwconnect   -instancename bridgeOutMB -bus busPOut \
             -busmasterport "mp" -loaddress "0x20000000" -hiaddress "0xefffffff"

# incoming connection
ihwaddbridge -instancename bridgeIn
ihwconnect   -instancename bridgeIn -bus busPIn \
             -busslaveport "sp" -loaddress "0x10000000" -hiaddress "0x10000fff"
ihwconnect   -instancename bridgeIn -bus busMB  \
             -busmasterport "mp" -loaddress "0x00000000" -hiaddress "0x00000fff"

# internal connection
ihwaddbridge -instancename bridgeLocal
ihwconnect   -instancename bridgeLocal -bus bus   \
             -busslaveport "sp" -loaddress "0x10000000" -hiaddress "0x10000fff"
ihwconnect   -instancename bridgeLocal -bus busMB \
             -busmasterport "mp" -loaddress "0x00000000" -hiaddress "0x00000fff"
