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

ihwnew \
  -name    dualFifo  \
  -vendor  vendor.com  \
  -library module  \
  -version 1.0 \
  -purpose module \
  -releasestatus imperas \
  -stoponctrlc 
  
iadddocumentation -name Licensing    -text "Open Source Apache 2.0"
iadddocumentation -name Description  -text "Example platform with riscv processor with custom FIFO extensions communicating with a peripheral using FIFOs.
The processor's output FIFO port is connected to the input FIFO port of the peripheral and vice versa."
iadddocumentation -name Limitations -text "None."
iadddocumentation -name Reference   -text "No Reference, created as an example"

ihwaddbus -instancename mainBus -addresswidth 32
    
ihwaddmemory -instancename ram -type ram
ihwconnect -bus mainBus -instancename ram -busslaveport sp1 -loaddress 0x0 -hiaddress 0xffffffff

ihwaddprocessor -instancename proc -type riscv -vendor vendor.com -library processor  -variant RV32X -defaultsemihost
ihwconnect -bus mainBus -instancename proc -busmasterport INSTRUCTION
ihwconnect -bus mainBus -instancename proc -busmasterport DATA

ihwaddperipheral -instancename periph -type fifo -vendor vendor.com
								
ihwaddfifo -instancename fifo01 -width 32 -depth 16
ihwaddfifo -instancename fifo10 -width 32 -depth 16

ihwconnect -fifo fifo01 -instancename proc   -fifoport fifoPortOut
ihwconnect -fifo fifo01 -instancename periph -fifoport fifoPortIn

ihwconnect -fifo fifo10 -instancename periph -fifoport fifoPortOut
ihwconnect -fifo fifo10 -instancename proc   -fifoport fifoPortIn



