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

# This is a simple OVP platform using an OR1K processor to stimulate
# a peripheral model that drives a packetnet interconnect.
#
ihwnew -name submodule

# outward FIFO interface
ihwaddfifoport -instancename f0    -mustbeconnected    
ihwaddfifoport -instancename f1    -mustbeconnected   

#
# processor bus
#
ihwaddbus -instancename mainBus -addresswidth 32

#
# processor
#
ihwaddprocessor -instancename cpu1 -type or1k -semihostname or1kNewlib
ihwsetparameter -handle cpu1 -name fifos -value 1 -type bool

#
# Connect processor to bus
#
ihwconnect -bus mainBus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus mainBus -instancename cpu1 -busmasterport DATA

#
# RAM for program, static data and stack
#
ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus mainBus -instancename ram1 -busslaveport sp1 -loaddress 0x0000 -hiaddress 0xffffffff

#
# FIFOs used as interconnects
#
ihwaddfifo -instancename fifo0 -width 32 -depth 32
ihwaddfifo -instancename fifo1 -width 32 -depth 32

#
# connect the FIFO to CPU and external port
#
ihwconnect -fifo fifo0 -instancename cpu1 -fifoport fifoIn
ihwconnect -fifo fifo0 -fifoport f0

#
# connect the FIFO to CPU and external port
#
ihwconnect -fifo fifo1 -instancename cpu1 -fifoport fifoOut
ihwconnect -fifo fifo1 -fifoport f1


