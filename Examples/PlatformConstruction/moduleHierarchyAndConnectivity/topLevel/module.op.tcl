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

ihwnew -name topLevel

# instance sub-modules
ihwaddmodule -instancename sys0   -modelfile processorSubSystem

ihwaddmodule -instancename sys1   -modelfile processorSubSystem

ihwaddmodule -instancename shmem  -modelfile sharedMemorySubSystem

# connections
# Sys0
ihwaddbus -instancename busSys0In -addresswidth 32
ihwconnect -instancename sys0 -busport busPortIn -bus busSys0In  

ihwaddbus -instancename busSys0Out -addresswidth 32
ihwconnect -instancename sys0 -busport busPortOut -bus busSys0Out  

#Sys1
ihwaddbus  -instancename busSys1In -addresswidth 32
ihwconnect -instancename sys1 -busport busPortIn -bus busSys1In 

ihwaddbus  -instancename busSys1Out -addresswidth 32
ihwconnect -instancename sys1 -busport busPortOut -bus busSys1Out 

# Shared Memory
ihwaddbus -instancename busSM -addresswidth 32
ihwconnect -instancename shmem -busport busPort -bus busSM 

# connect out port from Sys1 to Sys0 in port for Mailbox
ihwaddbridge -instancename bridgeSys0MB
ihwconnect   -instancename bridgeSys0MB -busslaveport  "sp" -bus busSys1Out -loaddress "0x20000000" -hiaddress "0x20000fff"
ihwconnect   -instancename bridgeSys0MB -busmasterport "mp" -bus busSys0In  -loaddress "0x10000000" -hiaddress "0x10000fff"
# connect out port from Sys1 to Shared Memory
ihwaddbridge -instancename bridgeSys0SM
ihwconnect   -instancename bridgeSys0SM -busslaveport  "sp" -bus busSys1Out -loaddress "0xe0000000" -hiaddress "0xe0000fff"
ihwconnect   -instancename bridgeSys0SM -busmasterport "mp" -bus busSM      -loaddress "0x00000000" -hiaddress "0x00000fff"


 # connect out port from Sys0 to Sys1 in port for Mailbox
ihwaddbridge -instancename bridgeSys1MB
ihwconnect   -instancename bridgeSys1MB -busslaveport  "sp" -bus busSys0Out -loaddress "0x20000000" -hiaddress "0x20000fff"
ihwconnect   -instancename bridgeSys1MB -busmasterport "mp" -bus busSys1In  -loaddress "0x10000000" -hiaddress "0x10000fff"
# connect out port from Sys0 to Shared Memory
ihwaddbridge -instancename bridgeSys1SM
ihwconnect   -instancename bridgeSys1SM -busslaveport  "sp" -bus busSys0Out -loaddress "0xe0000000" -hiaddress "0xe0000fff"
ihwconnect   -instancename bridgeSys1SM -busmasterport "mp" -bus busSM      -loaddress "0x00000000" -hiaddress "0x00000fff"
