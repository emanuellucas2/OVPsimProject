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

ihwnew -name intcTest

# Bus
ihwaddbus -instancename bus -addresswidth 32

# Interrupt from controller to processor
ihwaddnet -instancename intCpu1

# Interrupts to controller
for {set i 0} {$i <32} {incr i} {
    ihwaddnet -instancename int$i
}

# Processor
ihwaddprocessor -instancename cpu1 \
                -vendor riscv.ovpworld.org -library processor -type riscv -version 1.0 \
                -semihostname pk \
                -variant RV32I
ihwconnect -instancename cpu1 -busmasterport INSTRUCTION        -bus bus 
ihwconnect -instancename cpu1 -busmasterport DATA               -bus bus 
ihwconnect -instancename cpu1 -netport       MExternalInterrupt -net intCpu1

# Memory
# High and low regions
ihwaddmemory -instancename ram1 -type ram
ihwconnect   -instancename ram1 -busslaveport sp1 -bus bus \
                                -loaddress 0x00000000 -hiaddress 0x7fffffff

ihwaddmemory -instancename ram2 -type ram
ihwconnect   -instancename ram2 -busslaveport sp1 -bus bus \
                                -loaddress 0xc0000000 -hiaddress 0xffffffff

# Interrupt controller peripheral
# Directly load the model file rather than using a VLNV library reference 
ihwaddperipheral -instancename intc -modelfile intc/pse
ihwconnect       -instancename intc -busslaveport sp1 -bus bus \
                                    -loaddress 0x80000000 -hiaddress 0x8000007f

# connect interrupt line
ihwconnect       -instancename intc -netport intout_1      -net intCpu1

# Interrupts to controller
for {set i 0} {$i <32} {incr i} {
    ihwconnect -instancename intc -netport intin$i -net int$i
}
