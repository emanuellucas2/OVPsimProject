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


ihwnew -name Hetero_ARM_RISCV_NeuralNetwork  \
 -vendor imperas.ovpworld.org \
 -library module \
 -version 1.0 \
 -stoponctrlc \
 -purpose module \
 -releasestatus imperas

iadddocumentation -name Description -text "Platform for FreeRTOS bring"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "Created to demostrate specific Nerual network applications"

iadddocumentation -name Reference -text "Alexnet and Minst Neural Networks"


# ARM CPU
ihwaddprocessor -instancename arm_cpu -type arm -vendor arm.ovpworld.org -endian little -simulateexceptions -mips 50 -enableintercepts

ihwsetparameter -handle arm_cpu -name variant -type enum -value Cortex-A57MPx1  
ihwsetparameter -handle arm_cpu -name compatibility -type enum -value ISA             
ihwsetparameter -handle arm_cpu -name showHiddenRegs -type bool -value 0               

# ARM bus
ihwaddbus -instancename arm_bus -addresswidth 44

ihwconnect -instancename arm_cpu -busmasterport INSTRUCTION -bus arm_bus
ihwconnect -instancename arm_cpu -busmasterport DATA        -bus arm_bus

ihwaddmemory -instancename arm_ram -type ram
ihwconnect -instancename arm_ram -busslaveport sp1 -bus arm_bus -loaddress 0x00000000 -hiaddress 0x0fffffff

ihwaddperipheral -instancename fb   -vendor imperas.ovpworld.org -library peripheral -version 1.0 -type frameBuffer
ihwconnect   -instancename fb   -busslaveport sp -bus arm_bus  -loaddress 0x10000000  -hiaddress 0x10000fff
ihwconnect   -instancename fb   -busslaveport mp -bus arm_bus

set numberHarts 17

# RISC-V CPUs
ihwaddprocessor -instancename rv64_cpu -type riscv -vendor sifive.ovpworld.org -library processor -version 1.0 -mips 200 -simulateexceptions

ihwsetparameter -handle rv64_cpu -name variant       -type enum  -value U54
ihwsetparameter -handle rv64_cpu -name local_int_num -type Uns32 -value 48
ihwsetparameter -handle rv64_cpu -name numHarts      -type Uns32 -value ${numberHarts}
ihwsetparameter -handle rv64_cpu -name wfi_is_nop    -type bool  -value 0

# Override default value of mstatus.FS to 1:Initial
ihwsetparameter -handle rv64_cpu -name mstatus_FS -type Uns32 -value 1

# RISC-V bus
ihwaddbus -instancename rv64_bus -addresswidth 38

ihwconnect -instancename rv64_cpu -busmasterport INSTRUCTION -bus rv64_bus
ihwconnect -instancename rv64_cpu -busmasterport DATA        -bus rv64_bus

ihwaddmemory -instancename rv64_ram -type ram
ihwconnect -instancename rv64_ram -busslaveport sp1 -bus rv64_bus -loaddress 0x00000000 -hiaddress 0x0fffffff


#
# shared resources
#
ihwaddbus -instancename shared_bus -addresswidth 38
ihwaddmemory -instancename shared_ram -type ram
ihwconnect -instancename shared_ram -busslaveport sp1 -bus shared_bus -loaddress 0x20000000 -hiaddress 0x2fffffff

ihwaddbridge -instancename arm_bridge
ihwaddbridge -instancename rv64_bridge
ihwconnect -instancename arm_bridge  -busslaveport  sp -bus arm_bus    -loaddress 0x20000000 -hiaddress 0x3fffffff
ihwconnect -instancename arm_bridge  -busmasterport mp -bus shared_bus -loaddress 0x20000000 -hiaddress 0x3fffffff
ihwconnect -instancename rv64_bridge -busslaveport  sp -bus rv64_bus   -loaddress 0x20000000 -hiaddress 0x3fffffff
ihwconnect -instancename rv64_bridge -busmasterport mp -bus shared_bus -loaddress 0x20000000 -hiaddress 0x3fffffff

#
# peripherals
#

# UART
for {set i 0} {$i <= ${numberHarts}} {incr i} {
    ihwaddperipheral -instancename uart${i} -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type UART
    set loaddr [expr 0x30010000 + ($i * 0x1000)]
    set hiaddr [expr $loaddr + 0x1b]
    ihwconnect -instancename uart${i} -bus shared_bus -busslaveport bport1 -loaddress $loaddr -hiaddress $hiaddr
    # scaling default size of consoles 0:ARM,  17:RISC-V control, 1-16:RISC-V array
    # only open UART on ARM UART 0 and RISCV UART 17
    if { $i == 0 } {
        # arm application processor
        ihwsetparameter -handle uart${i} -name ychars -type uns32 -value 30
        ihwsetparameter -handle uart${i} -type boolean -name console            -value 1
        ihwsetparameter -handle uart${i} -type boolean -name finishOnDisconnect -value 1
    } elseif { $i == 10 } {
        # onf of processing array
        ihwsetparameter -handle uart${i} -name ychars -type uns32 -value 30
        ihwsetparameter -handle uart${i} -type boolean -name console            -value 1
        ihwsetparameter -handle uart${i} -type boolean -name finishOnDisconnect -value 1
    } elseif { $i == ${numberHarts}} {
        # control processor
        ihwsetparameter -handle uart${i} -name ychars -type uns32 -value 20
        ihwsetparameter -handle uart${i} -type boolean -name console            -value 1
        ihwsetparameter -handle uart${i} -type boolean -name finishOnDisconnect -value 1
    } else {
        ihwsetparameter -handle uart${i} -name ychars -type uns32 -value 7
    }
}

# load analysis ram - written by processor when active
ihwaddmemory -instancename cpuload -type ram
ihwconnect   -instancename cpuload -busslaveport sp1 -bus shared_bus -loaddress 0x30030000 -hiaddress 0x300300ff

# uSecond Counter
ihwaddperipheral -instancename usecCount -vendor imperas.ovpworld.org -library peripheral -version 1.0 -type usecCounter
ihwconnect       -instancename usecCount -bus shared_bus -busslaveport bport1 -loaddress 0x30040000 -hiaddress 0x30040003

# CLINT
ihwaddperipheral -instancename clint -vendor riscv.ovpworld.org -library peripheral -version 1.0 -type CLINT
ihwconnect       -instancename clint -bus shared_bus -busslaveport port0 -loaddress 0x30100000 -hiaddress 0x3010BFFF
ihwsetparameter -handle clint -name num_harts -type Uns32  -value 17
ihwsetparameter -handle clint -name clockMHz  -type double -value 1.0

# connect interrupts
for {set i 0} {$i < ${numberHarts}} {incr i} {
    # Connect Timer interrupt to CLINT
    ihwaddnet -instancename MTimerInterrupt${i}
    ihwconnect -instancename clint -netport MTimerInterrupt${i} -net MTimerInterrupt${i} 

    # Connect SW interrupt to CLINT
    ihwaddnet -instancename MSWInterrupt${i}
    ihwconnect -instancename clint -netport MSWInterrupt${i} -net MSWInterrupt${i}

    # Connect interrupts to RISC-V cpu hart
    ihwconnect -instancename rv64_cpu -netport hart${i}_MTimerInterrupt -net MTimerInterrupt${i} 
    ihwconnect -instancename rv64_cpu -netport hart${i}_MSWInterrupt    -net MSWInterrupt${i} 
}
