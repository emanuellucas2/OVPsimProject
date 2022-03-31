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

set desc "This platform models the Altera Cyclone III 3c120.

The processor is an Altera Nios_II procesor, Nios_II_F."

set limit "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux."

set reference "Altera Cyclone III 3c120 Reference Guide"

proc define {name {value 1}} {
    upvar $name l_name
    set l_name $value
}

proc mkram { name bus lo hi } {
    ihwaddmemory -instancename ${name} -type ram
    ihwconnect -bus $bus -instancename ${name} -busslaveport sp1 -loaddress ${lo} -hiaddress ${hi}
}

### grep define system.h | sed 's/#//' > system.tcl
### source system.tcl
###
define NIOS2_BREAK_ADDR                    0xc7fff820
define NIOS2_EXCEPTION_ADDR                0xd0000020
define NIOS2_RESET_ADDR                    0xc2800000
define NIOS2_FAST_TLB_MISS_EXCEPTION_ADDR  0xc7fff400
define NIOS2_HARDWARE_DIVIDE_PRESENT       1
define NIOS2_HARDWARE_MULTIPLY_PRESENT     1
define NIOS2_HARDWARE_MULX_PRESENT         0
define NIOS2_TLB_NUM_WAYS                  16
define NIOS2_TLB_NUM_ENTRIES               128
define NIOS2_PROCESS_ID_NUM_BITS           8
define NIOS2_DATA_ADDR_WIDTH               29
define NIOS2_INST_ADDR_WIDTH               29
###
###
###

# Setup variables for platform info
set vendor  altera.ovpworld.org
set library platform
set name    AlteraCycloneIII_3c120
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -verbose -purpose epk -releasestatus ovp

#
# Documentation
#
iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limit
iadddocumentation -name Reference   -text $reference

#
# command line parser
#
ihwaddclp -allargs

#
# nets
#
ihwaddnet -instancename irq10
ihwaddnet -instancename irq1
ihwaddnet -instancename irq11

#
# Processor
#
ihwaddprocessor \
	-instancename cpu \
	-type nios_ii \
	-vendor altera.ovpworld.org \
	-version 1.0 \
	-endian little \
	-simulateexceptions -mips 125.0
ihwsetparameter -handle cpu -name variant                         -value Nios_II_F                                -type enum
ihwsetparameter -handle cpu -name BREAK_VECTOR                    -value ${NIOS2_BREAK_ADDR}                      -type uns32
ihwsetparameter -handle cpu -name EXCEPTION_VECTOR                -value ${NIOS2_EXCEPTION_ADDR}                  -type uns32
ihwsetparameter -handle cpu -name RESET_VECTOR                    -value ${NIOS2_RESET_ADDR}                      -type uns32
ihwsetparameter -handle cpu -name FAST_TLB_MISS_EXCEPTION_VECTOR  -value ${NIOS2_FAST_TLB_MISS_EXCEPTION_ADDR}    -type uns32
ihwsetparameter -handle cpu -name HW_DIVIDE                       -value ${NIOS2_HARDWARE_DIVIDE_PRESENT}         -type bool
ihwsetparameter -handle cpu -name HW_MULTIPLY                     -value ${NIOS2_HARDWARE_MULTIPLY_PRESENT}       -type bool
ihwsetparameter -handle cpu -name HW_MULX                         -value ${NIOS2_HARDWARE_MULX_PRESENT}           -type bool
ihwsetparameter -handle cpu -name INCLUDE_MMU                     -value 1                                        -type bool
ihwsetparameter -handle cpu -name MMU_TLB_SET_ASSOCIATIVITY       -value ${NIOS2_TLB_NUM_WAYS}                    -type string
ihwsetparameter -handle cpu -name MMU_TLB_ENTRIES                 -value ${NIOS2_TLB_NUM_ENTRIES}                 -type string
ihwsetparameter -handle cpu -name MMU_PID_BITS                    -value ${NIOS2_PROCESS_ID_NUM_BITS}             -type uns32
ihwsetparameter -handle cpu -name DATA_ADDR_WIDTH                 -value ${NIOS2_DATA_ADDR_WIDTH}                 -type uns32
ihwsetparameter -handle cpu -name INST_ADDR_WIDTH                 -value ${NIOS2_INST_ADDR_WIDTH}                 -type uns32
ihwsetparameter -handle cpu -name TEST_HALT_EXIT                  -value 1                                        -type bool

#
# Kernel may need this set ?
#
ihwsetparameter -handle cpu -name EXCEPTION_EXTRA_INFORMATION     -value 1                                        -type bool


#
# Static Memory Bus (SMB)
#
ihwaddbus -instancename smbus -addresswidth 32

#
# Static IO Bus (SMB)
#
ihwaddbus -instancename iobus -addresswidth 32

#
# Individual I & D Bus
#
ihwaddbus -instancename dbus  -addresswidth 32
ihwaddbus -instancename ibus  -addresswidth 32

#
# Connect processor to bus
#
ihwconnect -bus ibus -instancename cpu -busmasterport INSTRUCTION -loaddress 0 -hiaddress 0xFFFFFFFF
ihwconnect -bus dbus -instancename cpu -busmasterport DATA        -loaddress 0 -hiaddress 0xFFFFFFFF

ihwaddbridge -instancename pb_ibus_to_smbus
ihwconnect   -instancename pb_ibus_to_smbus -busslaveport  sp1 -bus ibus  -loaddress 0x00000000 -hiaddress 0xFFFFFFFF
ihwconnect   -instancename pb_ibus_to_smbus -busmasterport mp1 -bus smbus -loaddress 0x00000000 -hiaddress 0xFFFFFFFF

ihwaddbridge -instancename pb_dbus_to_smbus_1
ihwconnect   -instancename pb_dbus_to_smbus_1 -busslaveport  sp1 -bus dbus  -loaddress 0x00000000 -hiaddress 0x07FFFFFF
ihwconnect   -instancename pb_dbus_to_smbus_1 -busmasterport mp1 -bus smbus -loaddress 0x00000000 -hiaddress 0x07FFFFFF

ihwaddbridge -instancename pb_dbus_to_smbus_2
ihwconnect   -instancename pb_dbus_to_smbus_2 -busslaveport  sp1 -bus dbus  -loaddress 0x08800000 -hiaddress 0xFFFFFFFF
ihwconnect   -instancename pb_dbus_to_smbus_2 -busmasterport mp1 -bus smbus -loaddress 0x08800000 -hiaddress 0xFFFFFFFF

#
# Memory
#
mkram pb_cpu_to_ddr2_bot   smbus 0x10000000 0x17FFFFFF
mkram tlb_miss_ram_1k      smbus 0x07FFF400 0x07FFF7FF

#
# Flash memory ?
#
mkram flash_mem_64m        smbus 0x00000000 0x03FFFFFF

#
# IO bus bridgepb_cpu_to_io 0x0800_0000 0x087F_FFFF
#
ihwaddbridge -instancename pb_cpu_to_io
ihwconnect   -instancename pb_cpu_to_io -busslaveport  sp1 -bus dbus  -loaddress 0x08000000 -hiaddress 0x087FFFFF
ihwconnect   -instancename pb_cpu_to_io -busmasterport mp1 -bus iobus -loaddress 0x00000000 -hiaddress 0x007FFFFF 

# 0x2000 - 0x3FFF descriptor_memory
# 0x4000 - 0x43FF tse_mac_control
# 0x4400 - 0x443F sgdma_rx
# 0x4800 - 0x483F sgdma_tx

# 0x4C80 - 0x4C9F uart.s1
ihwaddperipheral -instancename uart_s1 -vendor altera.ovpworld.org -type Uart
ihwconnect       -instancename uart_s1 -bus iobus -busslaveport sp1 -loaddress 0x00004C80 -hiaddress 0x00004C9F
ihwconnect       -instancename uart_s1 -netport irq      -net irq10
ihwconnect       -instancename cpu     -netport d_irq10  -net irq10

# 0x4CC0 - 0x4CCF user_led_pio
# 0x4CE0 - 0x4CEF user_dipsw_pio
# 0x4D00 - 0x4D0F user_pb_pio

# 0x4D40 - 0x4D47 sysid 
ihwaddperipheral -instancename sysid -vendor altera.ovpworld.org -type SystemIDCore
ihwconnect       -instancename sysid -bus iobus -busslaveport sp1 -loaddress 0x00004D40 -hiaddress 0x00004D47

# 0x4D50 - 0x4D57 jtag_uart 
ihwaddperipheral -instancename jtag_uart -vendor altera.ovpworld.org -type JtagUart
ihwconnect       -instancename jtag_uart -bus iobus -busslaveport sp1 -loaddress 0x00004D50 -hiaddress 0x00004D57
ihwsetparameter    -handle       jtag_uart -name writeIRQThreshold  -value 8    -type uns32
ihwsetparameter    -handle       jtag_uart -name readIRQThreshold   -value 8    -type uns32
ihwsetparameter    -handle       jtag_uart -name writeBufferDepth   -value 64   -type uns32
ihwsetparameter    -handle       jtag_uart -name readBufferDepth    -value 64   -type uns32
ihwsetparameter    -handle       jtag_uart -name console            -value 1    -type bool
ihwsetparameter    -handle       jtag_uart -name finishOnDisconnect -value 1    -type bool
ihwconnect       -instancename jtag_uart -netport irq     -net irq1
ihwconnect       -instancename cpu       -netport d_irq1  -net irq1

# 0x00400000 - 0x00400017 timer_1ms
ihwaddperipheral -instancename timer_1ms -vendor altera.ovpworld.org -type IntervalTimer32Core
ihwconnect       -instancename timer_1ms -bus iobus -busslaveport sp1 -loaddress 0x00400000 -hiaddress 0x00400017
ihwconnect       -instancename timer_1ms -netport irq     -net irq11
ihwconnect       -instancename cpu       -netport d_irq11 -net irq11

