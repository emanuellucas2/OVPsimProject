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
# NAME : XilinxML505 

ihwnew -name XilinxML505 \
                -vendor xilinx.ovpworld.org \
                -library module \
                -version 1.0 \
                -releasestatus ovp -purpose module


iadddocumentation \
                -name Description \
                -text "Xilinx ML505 Reference Platform"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This platform provides a subset of the full platform functionality. It is provided to boot the Linux operating system.
           Other software may be used but the operation cannot be guaranteed."

iadddocumentation -name Limitations -text "Platform capable of booting linux"
iadddocumentation -name Reference -text "UG347 (v3.1.2) May 16, 2011"
           

############################ processor ############################

ihwaddprocessor     -instancename microblaze_0 \
                    -type microblaze \
                    -vendor xilinx.ovpworld.org \
                    -library processor \
                    -version 1.0 \
                    -endian big \
                    -mips 125 \
                    -simulateexceptions

ihwconnect -net Interrupt_net -instancename microblaze_0 -netport Interrupt

ihwsetparameter    -handle microblaze_0 -name C_USE_MMU                   -value 3     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_MMU_ITLB_SIZE             -value 2     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_MMU_DTLB_SIZE             -value 4     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_MMU_TLB_ACCESS            -value 3     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_MMU_ZONES                 -value 16    -type uns32
ihwsetparameter    -handle microblaze_0 -name C_USE_EXTENDED_FSL_INSTR    -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_FSL_EXCEPTION             -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_USE_HW_MUL                -value 2     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_PVR                       -value 2     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_OPCODE_0x0_ILLEGAL        -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_FPU_EXCEPTION             -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_UNALIGNED_EXCEPTIONS      -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_ILL_OPCODE_EXCEPTION      -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_DIV_ZERO_EXCEPTION        -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_INTERCONNECT              -value 1     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_USE_BARREL                -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_USE_DIV                   -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_FSL_LINKS                 -value 4     -type uns32
ihwsetparameter    -handle microblaze_0 -name C_DEBUG_ENABLED             -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_I_LMB                     -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_D_LMB                     -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_USE_FPU                   -value 2     -type Uns32
ihwsetparameter    -handle microblaze_0 -name C_USE_MSR_INSTR             -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_USE_PCMP_INSTR            -value 1     -type bool
ihwsetparameter    -handle microblaze_0 -name C_FAMILY                    -value 12    -type uns32

########################### busses      ###########################
ihwaddbus -instancename bus1 -addresswidth 32

############################## memory #############################
ihwaddmemory -instancename BOOTMEM        -type ram
ihwaddmemory -instancename DDR2_SDRAM     -type ram
ihwaddmemory -instancename UNKNOWN_PERIPH -type ram
########################### connections ###########################
ihwconnect -instancename microblaze_0 \
                -busmasterport INSTRUCTION \
                -bus bus1

ihwconnect -instancename microblaze_0  \
                -busmasterport DATA \
                -bus bus1

########################## BOOT MEMORY  ###########################
ihwconnect -instancename BOOTMEM \
                -busslaveport sp1 \
                -bus bus1 \
                -loaddress 0x00000000 \
                -hiaddress 0x01FFFFFF
                
                #-hiaddress 0x0001FFFF

########################## nets  ###########################
ihwaddnet -instancename Interrupt_net
ihwaddnet -instancename Interrupt_3
ihwaddnet -instancename Interrupt_8

########################## LEDs_8Bit ############################
ihwaddperipheral -instancename LEDs_8Bit -type xps-gpio -vendor xilinx.ovpworld.org
ihwconnect       -instancename LEDs_8Bit -bus bus1 -busslaveport plb -loaddress 0x81400000 -hiaddress 0x8140FFFF

########################## IIC_EEPROM ############################
ihwaddperipheral -instancename IIC_EEPROM -type xps-iic -vendor xilinx.ovpworld.org
ihwconnect       -instancename IIC_EEPROM -bus bus1 -busslaveport plb -loaddress 0x81600000 -hiaddress 0x8160FFFF

########################## xps_intc_0 ############################
ihwaddperipheral -instancename xps_intc_0 -type xps-intc -vendor xilinx.ovpworld.org
ihwconnect       -instancename xps_intc_0 -bus bus1 -busslaveport plb -loaddress 0x81800000 -hiaddress 0x8180001F
ihwconnect       -net Interrupt_net -instancename xps_intc_0 -netport Irq
ihwconnect       -net Interrupt_3   -instancename xps_intc_0 -netport Intr3
ihwconnect       -net Interrupt_8   -instancename xps_intc_0 -netport Intr8

########################## Hard_Ethernet_MAC ############################
ihwaddperipheral -instancename Hard_Ethernet_MAC -type xps-ll-temac -vendor xilinx.ovpworld.org
ihwconnect       -instancename Hard_Ethernet_MAC -bus bus1 -busslaveport plb -loaddress 0x81C00000 -hiaddress 0x81C0003F

########################## SysACE_CompactFlash ############################
ihwaddperipheral -instancename SysACE_CompactFlash -type xps-sysace -vendor xilinx.ovpworld.org
ihwconnect       -instancename SysACE_CompactFlash -bus bus1 -busslaveport plb -loaddress 0x83600000 -hiaddress 0x8360FFFF

########################## xps_timer_1 ############################
ihwaddperipheral -instancename xps_timer_1 -type xps-timer -vendor xilinx.ovpworld.org
ihwconnect       -instancename xps_timer_1 -bus bus1 -busslaveport plb -loaddress 0x83C00000 -hiaddress 0x83C0001F
ihwconnect       -net Interrupt_3 -instancename xps_timer_1 -netport Interrupt

########################## RS232_Uart_1 ###########################
ihwaddperipheral -instancename RS232_Uart_1 -type xps-uartlite -vendor xilinx.ovpworld.org
ihwconnect       -instancename RS232_Uart_1 -bus bus1 -busslaveport plb -loaddress 0x84000000 -hiaddress 0x8400000F
ihwconnect       -net Interrupt_8 -instancename RS232_Uart_1 -netport Interrupt
ihwsetparameter    -handle       RS232_Uart_1 -name outfile            -value RS232_Uart_1.log     -type string
ihwsetparameter    -handle       RS232_Uart_1 -name finishOnDisconnect -value 1                    -type bool

########################## debug_module ############################
ihwaddperipheral -instancename debug_module -type mdm -vendor xilinx.ovpworld.org
ihwconnect       -instancename debug_module -bus bus1 -busslaveport plb -loaddress 0x84400000 -hiaddress 0x8440FFFF

########################## mpmc ####################################
ihwaddperipheral -instancename mpmc -type mpmc -vendor xilinx.ovpworld.org
ihwconnect       -instancename mpmc -bus bus1 -busslaveport plb -loaddress 0x84600180 -hiaddress 0x846001FF

########################## MAIN MEMORY  ############################
ihwconnect -instancename DDR2_SDRAM \
                -busslaveport sp1 \
                -bus bus1 \
                -loaddress 0x90000000 \
                -hiaddress 0x9FFFFFFF

ihwconnect -instancename UNKNOWN_PERIPH \
                -busslaveport sp1 \
                -bus bus1 \
                -loaddress 0x8FFFF000 \
                -hiaddress 0x8FFFFFFF

########################### mb_plb #################################
ihwaddperipheral -instancename mb_plb -type xps-mch-emc -vendor xilinx.ovpworld.org
ihwconnect       -instancename mb_plb -bus bus1 -busslaveport plb -loaddress 0xA0000000 -hiaddress 0xA1FFFFFF

#
# Possible parameter overrides
#
# C_ADDR_TAG_BITS
# C_ALLOW_DCACHE_WR
# C_ALLOW_ICACHE_WR
# C_AREA_OPTIMIZED
# C_BRANCH_TARGET_CACHE_SIZE
# C_CACHE_BYTE_SIZE
# C_DCACHE_ADDR_TAG
# C_DCACHE_ALWAYS_USED
# C_DCACHE_BASEADDR
# C_DCACHE_BYTE_SIZE
# C_DCACHE_DATA_WIDTH
# C_DCACHE_FORCE_TAG_LUTRAM
# C_DCACHE_HIGHADDR
# C_DCACHE_INTERFACE
# C_DCACHE_LINE_LEN
# C_DCACHE_USE_FSL
# C_DCACHE_USE_WRITEBACK
# C_DCACHE_VICTIMS
# C_DEBUG_ENABLED
# C_DIV_ZERO_EXCEPTION
# C_DPLB_BUS_EXCEPTION
# C_D_AXI
# C_D_LMB
# C_D_PLB
# C_ECC_USE_CE_EXCEPTION
# C_EDGE_IS_POSITIVE
# C_ENDIANNESS
# C_FAMILY
# C_FAULT_TOLERANT
# C_FPU_EXCEPTION
# C_FSL_EXCEPTION
# C_FSL_LINKS
# C_ICACHE_ALWAYS_USED
# C_ICACHE_BASEADDR
# C_ICACHE_DATA_WIDTH
# C_ICACHE_FORCE_TAG_LUTRAM
# C_ICACHE_HIGHADDR
# C_ICACHE_INTERFACE
# C_ICACHE_LINE_LEN
# C_ICACHE_STREAMS
# C_ICACHE_USE_FSL
# C_ICACHE_VICTIMS
# C_ILL_OPCODE_EXCEPTION
# C_INTERCONNECT
# C_INTERRUPT_IS_EDGE
# C_IPLB_BUS_EXCEPTION
# C_I_AXI
# C_I_LMB
# C_I_PLB
# C_MMU_DTLB_SIZE
# C_MMU_ITLB_SIZE
# C_MMU_PRIVILEGED_INSTR
# C_MMU_TLB_ACCESS
# C_MMU_ZONES
# C_M_AXI_D_BUS_EXCEPTION
# C_M_AXI_I_BUS_EXCEPTION
# C_NUMBER_OF_PC_BRK
# C_NUMBER_OF_RD_ADDR_BRK
# C_NUMBER_OF_WR_ADDR_BRK
# C_OPCODE_0x0_ILLEGAL
# C_PVR
# C_PVR_USER1
# C_PVR_USER2
# C_RESET_MSR
# C_STREAM_INTERCONNECT
# C_UNALIGNED_EXCEPTIONS
# C_USE_BARREL
# C_USE_BRANCH_TARGET_CACHE
# C_USE_DCACHE
# C_USE_DIV
# C_USE_EXTENDED_FSL_INSTR
# C_USE_EXT_BRK
# C_USE_EXT_NM_BRK
# C_USE_FPU
# C_USE_HW_MUL
# C_USE_ICACHE
# C_USE_INTERRUPT
# C_USE_MMU
# C_USE_MSR_INSTR
# C_USE_PCMP_INSTR
# C_USE_STACK_PROTECTION
