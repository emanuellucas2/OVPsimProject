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

ihwnew -name simpleMonitor

ihwaddbus -instancename bus -addresswidth 32

#ihwaddnet -instancename directWrite
#ihwaddnet -instancename directRead

ihwaddprocessor -instancename cpu1 \
                -vendor arm.ovpworld.org -library processor -type arm -version 1.0 \
	        -variant ARM7TDMI \
		-semihostvendor arm.ovpworld.org -semihostname armNewlib
ihwconnect -bus bus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus bus -instancename cpu1 -busmasterport DATA

ihwaddmemory -instancename mem1 -type ram
ihwconnect -bus bus -instancename mem1 \
           -busslaveport sp1 -loaddress 0x0 -hiaddress 0xffffffff

ihwaddperipheral -instancename radar -modelfile peripheral/pse.pse
ihwconnect -instancename radar -bus bus -busmasterport MPORT
