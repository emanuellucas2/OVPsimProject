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
# 

ihwnew -name RiscvRV32FreeRTOS  \
  -vendor imperas.ovpworld.org  \
  -library module               \
  -version 1.0                  \
  -stoponctrlc                  \
  -purpose module               \
  -releasestatus ovp

iadddocumentation -name Licensing -text "Open Source Apache 2.0"
iadddocumentation -name Description  -text "Example platform to instance RISCV RV32I processor core with extensions M and SU. Peripherals and memory address layout to boot pre-compiled FreeRTOS operating system."
iadddocumentation -name Reference -text "https://github.com/RISCV-on-Microsemi-FPGA/FreeRTOS/tree/master/FreeRTOS_on_Mi-V_Processor"
iadddocumentation -name Limitations -text "Created to executed the specific software"

############################ bus ##################################

ihwaddbus -instancename bus0  -addresswidth 32

############################ processor ############################

ihwaddprocessor -instancename cpu0  \
  -type riscv -vendor riscv.ovpworld.org -library processor -version 1.0 \
  -mips 50 -simulateexceptions

ihwsetparameter -handle cpu0 -name variant        -value RVB32I -type enum
ihwsetparameter -handle cpu0 -name add_Extensions -value MSU      -type string

ihwconnect -instancename cpu0  -busmasterport INSTRUCTION -bus bus0
ihwconnect -instancename cpu0  -busmasterport DATA        -bus bus0
  

############################## memory #############################

ihwaddmemory -instancename nvram -type ram
ihwconnect   -instancename nvram -busslaveport sp1 -bus bus0 -loaddress 0x60000000 -hiaddress 0x6003FFFF

ihwaddmemory -instancename ddr   -type ram
ihwconnect   -instancename ddr   -busslaveport sp1 -bus bus0 -loaddress 0x80000000 -hiaddress 0x8FFFFFFF

ihwaddmemory -instancename stk   -type ram
ihwconnect   -instancename stk   -busslaveport sp1 -bus bus0 -loaddress 0xfff00000 -hiaddress 0xFFFFFFFF

########################### peripherals ###########################

# From FreeRTOS hw_platform.h
#define COREUARTAPB0_BASE_ADDR 0x70001000UL
#define COREGPIO_IN_BASE_ADDR  0x70002000UL
#define CORETIMER0_BASE_ADDR   0x70003000UL
#define CORETIMER1_BASE_ADDR   0x70004000UL
#define COREGPIO_OUT_BASE_ADDR 0x70005000UL
#define CORE16550_BASE_ADDR    0x70007000UL
#define PLIC_BASE_ADDR         0x40000000UL

ihwaddperipheral -instancename uart0 \
                 -vendor microsemi.ovpworld.org -library peripheral -type CoreUARTapb -version 1.0
ihwconnect -instancename uart0 -bus bus0 -busslaveport port0 -loaddress 0x70001000 -hiaddress 0x70001017

ihwaddperipheral -instancename plic0 -vendor riscv.ovpworld.org -library peripheral -type PLIC -version 1.0
ihwconnect -instancename plic0 -bus bus0 -busslaveport port0 -loaddress 0x40000000 -hiaddress 0x43FFFFFF
ihwsetparameter -name num_sources -handle plic0 -type Uns32 -value 256
ihwsetparameter -name num_targets -handle plic0 -type Uns32 -value 1

ihwaddperipheral -instancename prci0 -vendor riscv.ovpworld.org -library peripheral -type CLINT -version 1.0
ihwconnect -instancename prci0 -bus bus0 -busslaveport port0 -loaddress 0x44000000 -hiaddress 0x4400BFFF
ihwsetparameter -name clockMHz -handle prci0 -type double -value 1.0

########################### interrupts ############################

# External Interrupt Port
ihwaddnet -instancename eip
ihwconnect -net eip -instancename plic0 -netport irqT0
ihwconnect -net eip -instancename cpu0  -netport MExternalInterrupt

# Local Interrupt Port
ihwaddnet -instancename MTimerInterrupt
ihwconnect -net MTimerInterrupt -instancename prci0 -netport MTimerInterrupt0
ihwconnect -net MTimerInterrupt -instancename cpu0  -netport MTimerInterrupt
ihwaddnet -instancename MSWInterrupt
ihwconnect -net MSWInterrupt -instancename prci0 -netport MSWInterrupt0
ihwconnect -net MSWInterrupt -instancename cpu0  -netport MSWInterrupt
