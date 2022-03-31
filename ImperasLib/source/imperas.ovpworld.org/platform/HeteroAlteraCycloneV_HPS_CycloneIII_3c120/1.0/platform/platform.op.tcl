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


set desc "This platform merges the Altera Cyclone V (ARM) and Cyclone III (Nios_II) processor systems"

set limit "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux."

set ref "Altera Cyclone III 3c120 Reference Guide and Cyclone V Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30"

# Setup variables for platform info
set vendor  imperas.ovpworld.org
set library platform
set name    HeteroAlteraCycloneV_HPS_CycloneIII_3c120
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose fixed -releasestatus imperas

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limit
iadddocumentation -name Reference -text $ref

#
# nets
#

ihwaddnet -instancename ir199
ihwaddnet -instancename ir200
ihwaddnet -instancename ir201
ihwaddnet -instancename ir202
ihwaddnet -instancename ir194
ihwaddnet -instancename ir195
ihwaddnet -instancename cpu0Reset
ihwaddnet -instancename cpu1Reset
ihwaddnet -instancename irq10
ihwaddnet -instancename irq1
ihwaddnet -instancename irq11

###############################################################################################################################
# CycloneV system (Begin)
###############################################################################################################################
#
# Static Memory Bus (SMB)
#
ihwaddbus -instancename smbus_HPS -addresswidth 32

#
# Processor
#

ihwaddprocessor -instancename cpu_A9MPx2 -type arm -vendor arm.ovpworld.org -version 1.0 -endian little \
                -simulateexceptions -mips 100.0
ihwsetparameter -handle cpu_A9MPx2 -name variant                     -value Cortex-A9MPx2    -type enum
ihwsetparameter -handle cpu_A9MPx2 -name compatibility               -value ISA              -type enum
ihwsetparameter -handle cpu_A9MPx2 -name UAL                         -value 1                -type bool
ihwsetparameter -handle cpu_A9MPx2 -name showHiddenRegs              -value 0                -type bool
ihwsetparameter -handle cpu_A9MPx2 -name override_CBAR               -value 0xfffec000       -type uns32
ihwsetparameter -handle cpu_A9MPx2 -name override_GICD_TYPER_ITLines -value 6                -type uns32

# Connect processor to bus
ihwconnect -bus smbus_HPS -instancename cpu_A9MPx2 -busmasterport INSTRUCTION
ihwconnect -bus smbus_HPS -instancename cpu_A9MPx2 -busmasterport DATA

#
# RAM
#

# 0x00000000    0x3fffffff  SRAM (default 1GB)
ihwaddmemory -instancename sram1  -type ram
ihwconnect -bus smbus_HPS -instancename sram1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x3fffffff

#
# PERIPHERALS
#

# 0xfffef000    0xfffeffff  PL310 L2 Cache Controller
ihwaddperipheral -instancename L2 -type L2CachePL310 -vendor arm.ovpworld.org
ihwconnect       -instancename L2 -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xfffef000 -hiaddress 0xfffeffff

# 0xffc08000    0xffc08fff    timer0  dw-apb-timer
ihwaddperipheral -instancename timer0 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer0 -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffc08000 -hiaddress 0xffc08fff
ihwconnect       -instancename timer0 -net ir199 -netport irq
ihwconnect       -instancename cpu_A9MPx2    -net ir199 -netport SPI199

# 0xffc09000    0xffc09fff    timer1  dw-apb-timer
ihwaddperipheral -instancename timer1 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer1 -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffc09000 -hiaddress 0xffc09fff
ihwconnect       -instancename timer1 -net ir200 -netport irq
ihwconnect       -instancename cpu_A9MPx2    -net ir200 -netport SPI200

# 0xffd00000    0xffd00fff    timer2  dw-apb-timer
ihwaddperipheral -instancename timer2 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer2 -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffd00000 -hiaddress 0xffd00fff
ihwconnect       -instancename timer2 -net ir201 -netport irq
ihwconnect       -instancename cpu_A9MPx2    -net ir201 -netport SPI201

# 0xffd01000    0xffd01fff    timer3  dw-apb-timer
ihwaddperipheral -instancename timer3 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer3 -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffd01000 -hiaddress 0xffd01fff
ihwconnect       -instancename timer3 -net ir202 -netport irq
ihwconnect       -instancename cpu_A9MPx2    -net ir202 -netport SPI202

# 0xffc02000    0x0xffc02fff  uart0 dw-apb-uart
ihwaddperipheral -instancename uart0  -type dw-apb-uart -vendor altera.ovpworld.org
ihwsetparameter    -handle       uart0  -name outfile            -value uart0.log   -type string
ihwsetparameter    -handle       uart0  -name console            -value 1           -type bool
ihwsetparameter    -handle       uart0  -name finishOnDisconnect -value 1           -type bool
ihwconnect       -instancename uart0  -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffc02000 -hiaddress 0xffc02fff
ihwconnect       -instancename uart0  -net ir194 -netport intOut
ihwconnect       -instancename cpu_A9MPx2    -net ir194 -netport SPI194

# 0xffc03000    0x0xffc03fff  uart1 dw-apb-uart
ihwaddperipheral -instancename uart1  -type dw-apb-uart -vendor altera.ovpworld.org
ihwsetparameter    -handle       uart1  -name outfile -value uart1.log    -type string
ihwsetparameter    -handle       uart1  -name console -value 1            -type bool
ihwconnect       -instancename uart1  -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffc03000 -hiaddress 0xffc03fff
ihwconnect       -instancename uart1  -net ir195 -netport intOut
ihwconnect       -instancename cpu_A9MPx2    -net ir195 -netport SPI195

# 0xffd05000    0xffd05fff  RSTMGR Reset Manager 
ihwaddperipheral -instancename RSTMGR0 -vendor altera.ovpworld.org -type RSTMGR
ihwconnect       -instancename RSTMGR0 -bus smbus_HPS  -busslaveport  bport1 -loaddress 0xffd05000 -hiaddress 0xffd05fff
ihwconnect       -instancename RSTMGR0 -net cpu0Reset -netport cpu0Reset
ihwconnect       -instancename RSTMGR0 -net cpu1Reset -netport cpu1Reset
ihwconnect       -instancename cpu_A9MPx2    -net cpu0Reset -netport reset_CPU0
ihwconnect       -instancename cpu_A9MPx2    -net cpu1Reset -netport reset_CPU1

# Dummy Peripherals:

# 0xffd08000    0xffd08fff  SYSMGR System Manager - dummy
ihwaddperipheral -instancename SYSMGR0  -vendor ovpworld.org -type trap
ihwconnect       -instancename SYSMGR0 -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       SYSMGR0 -name portAddress -value 0xffd08000 -type uns32

# 0xffd04000    0xffd04fff  CLKMGR Clock Manager - dummy
ihwaddperipheral -instancename CLKMGR0 -vendor ovpworld.org -type trap
ihwconnect       -instancename CLKMGR0 -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       CLKMGR0 -name portAddress -value 0xffd04000 -type uns32

# 0xffe01000    0xffe01fff  pdma DMA device - dummy
ihwaddperipheral -instancename pdma0 -vendor ovpworld.org -type trap
ihwconnect       -instancename pdma0 -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       pdma0 -name portAddress -value 0xffe01000 -type uns32

# 0xff700000    0xff700fff  gmac0 Ethernet device - dummy
ihwaddperipheral -instancename gmac0 -vendor ovpworld.org -type trap
ihwconnect       -instancename gmac0 -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       gmac0 -name portAddress -value 0xff700000 -type uns32

# 0xff701000    0xff701fff  emac0_dma Ethernet dma device - dummy
ihwaddperipheral -instancename emac0_dma -vendor ovpworld.org -type trap
ihwconnect       -instancename emac0_dma -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       emac0_dma -name portAddress -value 0xff701000 -type uns32

# 0xff702000    0xff702fff  gmac1 Ethernet device - dummy
ihwaddperipheral -instancename gmac1 -vendor ovpworld.org -type trap
ihwconnect       -instancename gmac1 -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       gmac1 -name portAddress -value 0xff702000 -type uns32

# 0xff703000    0xff703fff  emac1_dma Ethernet dma device - dummy
ihwaddperipheral -instancename emac1_dma -vendor ovpworld.org -type trap
ihwconnect       -instancename emac1_dma -busslaveport bport1 -bus smbus_HPS
ihwsetparameter  -handle       emac1_dma -name portAddress -value 0xff703000 -type uns32

#
# Linux BootLoader
#

ihwaddperipheral -instancename smartLoader  -type SmartLoaderArmLinux -vendor arm.ovpworld.org
ihwconnect       -instancename smartLoader  -bus smbus_HPS -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter  -handle       smartLoader  -name boardid      -value 0xffffffff                 -type uns32
ihwsetparameter  -handle       smartLoader  -name kernel       -value zImage                     -type string
ihwsetparameter  -handle       smartLoader  -name initrd       -value fs.img                     -type string
ihwsetparameter  -handle       smartLoader  -name command      -value "mem=1024M console=ttyS0"  -type string
ihwsetparameter  -handle       smartLoader  -name physicalbase -value 0x0                        -type uns32
ihwsetparameter  -handle       smartLoader  -name memsize      -value 0x40000000                 -type uns32
ihwsetparameter  -handle       smartLoader  -name disable      -value 0                          -type bool

###############################################################################################################################
# CycloneV system (End)
###############################################################################################################################

###############################################################################################################################
# CycloneIII system (Begin)
###############################################################################################################################

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

#
# Processor
#
ihwaddprocessor \
    -instancename cpu_Nios_II \
    -type nios_ii \
    -vendor altera.ovpworld.org \
    -version 1.0 \
    -endian little \
    -simulateexceptions -mips 125.0
ihwsetparameter -handle cpu_Nios_II -name variant                         -value Nios_II_F                             -type enum
ihwsetparameter -handle cpu_Nios_II -name BREAK_VECTOR                    -value ${NIOS2_BREAK_ADDR}                   -type uns32
ihwsetparameter -handle cpu_Nios_II -name EXCEPTION_VECTOR                -value ${NIOS2_EXCEPTION_ADDR}               -type uns32
ihwsetparameter -handle cpu_Nios_II -name RESET_VECTOR                    -value ${NIOS2_RESET_ADDR}                   -type uns32
ihwsetparameter -handle cpu_Nios_II -name FAST_TLB_MISS_EXCEPTION_VECTOR  -value ${NIOS2_FAST_TLB_MISS_EXCEPTION_ADDR} -type uns32
ihwsetparameter -handle cpu_Nios_II -name HW_DIVIDE                       -value ${NIOS2_HARDWARE_DIVIDE_PRESENT}      -type bool
ihwsetparameter -handle cpu_Nios_II -name HW_MULTIPLY                     -value ${NIOS2_HARDWARE_MULTIPLY_PRESENT}    -type bool
ihwsetparameter -handle cpu_Nios_II -name HW_MULX                         -value ${NIOS2_HARDWARE_MULX_PRESENT}        -type bool
ihwsetparameter -handle cpu_Nios_II -name INCLUDE_MMU                     -value 1                                     -type bool
ihwsetparameter -handle cpu_Nios_II -name MMU_TLB_SET_ASSOCIATIVITY       -value ${NIOS2_TLB_NUM_WAYS}                 -type string
ihwsetparameter -handle cpu_Nios_II -name MMU_TLB_ENTRIES                 -value ${NIOS2_TLB_NUM_ENTRIES}              -type string
ihwsetparameter -handle cpu_Nios_II -name MMU_PID_BITS                    -value ${NIOS2_PROCESS_ID_NUM_BITS}          -type uns32
ihwsetparameter -handle cpu_Nios_II -name DATA_ADDR_WIDTH                 -value ${NIOS2_DATA_ADDR_WIDTH}              -type uns32
ihwsetparameter -handle cpu_Nios_II -name INST_ADDR_WIDTH                 -value ${NIOS2_INST_ADDR_WIDTH}              -type uns32
ihwsetparameter -handle cpu_Nios_II -name TEST_HALT_EXIT                  -value 1                                     -type bool

#
# Kernel may need this set ?
#
ihwsetparameter -handle cpu_Nios_II -name EXCEPTION_EXTRA_INFORMATION     -value 1                                    -type bool

#
# Static Memory Bus (SMB)
#
ihwaddbus -instancename smbus_3c120 -addresswidth 32

#
# Static IO Bus (SMB)
#
ihwaddbus -instancename iobus_3c120 -addresswidth 32

#
# Individual I & D Bus
#
ihwaddbus -instancename dbus_3c120  -addresswidth 32
ihwaddbus -instancename ibus_3c120  -addresswidth 32

#
# Connect processor to bus
#
ihwconnect -bus ibus_3c120 -instancename cpu_Nios_II -busmasterport INSTRUCTION -loaddress 0 -hiaddress 0xFFFFFFFF
ihwconnect -bus dbus_3c120 -instancename cpu_Nios_II -busmasterport DATA        -loaddress 0 -hiaddress 0xFFFFFFFF

ihwaddbridge -instancename pb_ibus_to_smbus_3c120
ihwconnect   -instancename pb_ibus_to_smbus_3c120 -busslaveport  sp1 -bus ibus_3c120  -loaddress 0x00000000 -hiaddress 0xFFFFFFFF
ihwconnect   -instancename pb_ibus_to_smbus_3c120 -busmasterport mp1 -bus smbus_3c120 -loaddress 0x00000000 -hiaddress 0xFFFFFFFF

ihwaddbridge -instancename pb_dbus_to_smbus_3c120_1
ihwconnect   -instancename pb_dbus_to_smbus_3c120_1 -busslaveport  sp1 -bus dbus_3c120  -loaddress 0x00000000 -hiaddress 0x07FFFFFF
ihwconnect   -instancename pb_dbus_to_smbus_3c120_1 -busmasterport mp1 -bus smbus_3c120 -loaddress 0x00000000 -hiaddress 0x07FFFFFF

ihwaddbridge -instancename pb_dbus_to_smbus_3c120_2
ihwconnect   -instancename pb_dbus_to_smbus_3c120_2 -busslaveport  sp1 -bus dbus_3c120  -loaddress 0x08800000 -hiaddress 0xFFFFFFFF
ihwconnect   -instancename pb_dbus_to_smbus_3c120_2 -busmasterport mp1 -bus smbus_3c120 -loaddress 0x08800000 -hiaddress 0xFFFFFFFF

#
# Memory
#
mkram pb_cpu_to_ddr2_bot   smbus_3c120 0x10000000 0x17FFFFFF
mkram tlb_miss_ram_1k      smbus_3c120 0x07FFF400 0x07FFF7FF

#
# Flash memory ?
#
mkram flash_mem_64m        smbus_3c120 0x00000000 0x03FFFFFF

#
# IO bus bridgepb_cpu_to_io 0x0800_0000 0x087F_FFFF
#
ihwaddbridge -instancename pb_cpu_to_io
ihwconnect   -instancename pb_cpu_to_io -busslaveport  sp1 -bus dbus_3c120  -loaddress 0x08000000 -hiaddress 0x087FFFFF
ihwconnect   -instancename pb_cpu_to_io -busmasterport mp1 -bus iobus_3c120 -loaddress 0x00000000 -hiaddress 0x007FFFFF 

# 0x2000 - 0x3FFF descriptor_memory
# 0x4000 - 0x43FF tse_mac_control
# 0x4400 - 0x443F sgdma_rx
# 0x4800 - 0x483F sgdma_tx

# 0x4C80 - 0x4C9F uart.s1
ihwaddperipheral -instancename uart_s1 -vendor altera.ovpworld.org -type Uart
ihwconnect       -instancename uart_s1 -bus iobus_3c120 -busslaveport sp1 -loaddress 0x00004C80 -hiaddress 0x00004C9F
ihwconnect       -instancename uart_s1 -netport irq      -net irq10
ihwconnect       -instancename cpu_Nios_II     -netport d_irq10  -net irq10

# 0x4CC0 - 0x4CCF user_led_pio
# 0x4CE0 - 0x4CEF user_dipsw_pio
# 0x4D00 - 0x4D0F user_pb_pio

# 0x4D40 - 0x4D47 sysid 
ihwaddperipheral -instancename sysid -vendor altera.ovpworld.org -type SystemIDCore
ihwconnect       -instancename sysid -bus iobus_3c120 -busslaveport sp1 -loaddress 0x00004D40 -hiaddress 0x00004D47

# 0x4D50 - 0x4D57 jtag_uart 
ihwaddperipheral -instancename jtag_uart -vendor altera.ovpworld.org -type JtagUart
ihwconnect       -instancename jtag_uart -bus iobus_3c120 -busslaveport sp1 -loaddress 0x00004D50 -hiaddress 0x00004D57
ihwsetparameter    -handle       jtag_uart -name writeIRQThreshold  -value 8      -type uns32
ihwsetparameter    -handle       jtag_uart -name readIRQThreshold   -value 8      -type uns32
ihwsetparameter    -handle       jtag_uart -name writeBufferDepth   -value 64     -type uns32
ihwsetparameter    -handle       jtag_uart -name readBufferDepth    -value 64     -type uns32
ihwsetparameter    -handle       jtag_uart -name console            -value 1      -type bool
ihwsetparameter    -handle       jtag_uart -name outfile -value jtag_uart.log     -type string
ihwsetparameter    -handle       jtag_uart -name finishOnDisconnect -value 1      -type bool
ihwconnect       -instancename jtag_uart -netport irq     -net irq1
ihwconnect       -instancename cpu_Nios_II       -netport d_irq1  -net irq1

# 0x00400000 - 0x00400017 timer_1ms
ihwaddperipheral -instancename timer_1ms -vendor altera.ovpworld.org -type IntervalTimer32Core
ihwconnect       -instancename timer_1ms -bus iobus_3c120 -busslaveport sp1 -loaddress 0x00400000 -hiaddress 0x00400017
ihwconnect       -instancename timer_1ms -netport irq     -net irq11
ihwconnect       -instancename cpu_Nios_II       -netport d_irq11 -net irq11

###############################################################################################################################
# CycloneIII system (End)
###############################################################################################################################

#
# Command line arguments
#
ihwaddclp -allargs
ihwaddclparg -name  ZIMAGE     -type stringvar -description "Linux zImage file to load using smartLoader"
ihwaddclparg -name  ZIMAGEADDR -type uns64var  -description "Physical address to load zImage file (default 0x04000000)"
ihwaddclparg -name  INITRD     -type stringvar -description "Linux initrd file to load using smartLoader"
ihwaddclparg -name  INITRDADDR -type uns64var  -description "Physical address to load initrd file (default 0x06000000)"
ihwaddclparg -name  LINUXSYM   -type stringvar -description "Linux ELF file with symbolic debug info (CpuManger only)"
ihwaddclparg -name  BOARDID    -type int32var  -description "Value to pass to Linux as the boardid (default (0xffffffff)"
ihwaddclparg -name  LINUXMEM   -type uns64var  -description "Amount of memory allocated to Linux (required in AMP mode)"
ihwaddclparg -name  LINUXCMD   -type stringvar -description "Linux command line (default: 'mem=1024M console=ttyS0', with mem value adjusted if LINUXMEM or MEMSIZE specified)"
ihwaddclparg -name  APP0       -type stringvar -description "ELF file to load on CPU0 instead of Linux (Precludes use of Linux options)"
ihwaddclparg -name  APP1       -type stringvar -description "ELF file to load on CPU1 for AMP"
ihwaddclparg -name  BOOT       -type stringvar -description "ELF file with boot code (both processors will start at its entry)"
ihwaddclparg -name  IMAGE0     -type stringvar -description "Image file to load on cpu0"
ihwaddclparg -name  IMAGE0ADDR -type uns64var  -description "load address for image on cpu0 (IMAGE0 must be specified)"
ihwaddclparg -name  IMAGE0SYM  -type stringvar -description "Elf file with symbolic debug info for image on cpu0 (IMAGE0 must be specified, CpuManger only)"
ihwaddclparg -name  IMAGE1     -type stringvar -description "Image file to load on cpu1"
ihwaddclparg -name  IMAGE1ADDR -type uns64var  -description "Load address for image on cpu1 (IMAGE1 must be specified)"
ihwaddclparg -name  IMAGE1SYM  -type stringvar -description "Elf file with symbolic debug info for image on cpu1 (IMAGE1 must be specified, CpuManger only)"
ihwaddclparg -name  UART0PORT  -type stringvar -description "Uart0 port: 'auto' for automatic console, 0 for simulator-chosen port, or number for specific port"
ihwaddclparg -name  UART1PORT  -type stringvar -description "Uart1 port: 'auto' for automatic console, 0 for simulator-chosen port, or number for specific port"

ihwaddclparg -name  NIOSBOOT   -type stringvar -description "vmlinux to load onto "
