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

set desc "This module implements a Sensor/Actor Node for the SafePower Public Demonstrator in the Xilinx Zynq Programmable Logic (PL).
This PL configuration instances one Xilinx MicroBlaze processor with a local memory and a TTEL NoC interface peripheral."

set limitations "Provides a baremetal implementation."

set reference "SafePower Public Demonstrator"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_TTELNoC_sensor_actor_node_public_demonstrator
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference

#
# pBus
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# Nets
#
ihwaddnet -instancename timer_intc
ihwaddnet -instancename period_intc
ihwaddnet -instancename core_intc
ihwaddnet -instancename intc_mb

#
# Processor
#
ihwaddprocessor -instancename cpu -type microblaze -vendor xilinx.ovpworld.org -version 1.0 \
		-defaultsemihost

ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA

ihwsetparameter  -handle cpu -name C_ENDIANNESS -type uns32 -value 1
ihwsetparameter  -handle cpu -name C_USE_INTERRUPT -type uns32 -value 1
ihwsetparameter  -handle cpu -name C_INTERCONNECT -type uns32 -value 2
ihwsetparameter  -handle cpu -name C_USE_FPU -type uns32 -value 1
ihwsetparameter  -handle cpu -name C_USE_HW_MUL -type uns32 -value 2
ihwsetparameter  -handle cpu -name C_USE_DIV -type boolean -value 1

#
# Address Map
#
# Local Processor Access
# 0x00000000 0x03ffffff RAM
# 0x41200000 0x412001ff Xilinx AXI-INTC
# 0x41c00000 0x41c0001f Xilinx AXI-Timer
# 0x40600000 0x4060000f Xilinx UART-Lite
# 0x40810000 0x4081ffff RAM (iic_bu)
# 0x40800000 0x4080ffff RAM (iic_imu)
# 0x40820000 0x4082ffff RAM (iic_motor)
# 0x40000000 0x4003ffff RAM (debug_gpio_led_gimbal)
# 0x44A10000 0x44A1ffff RAM (spi_bg)
# 0x44A00000 0x44A0ffff RAM (ppm)
# 0x44A20000 0x44A2ffff RAM (xadc)
# 0x44A30000 0x44A3ffff RAM (clock_control)
# 0x80000000 0x80ffffff NoC peripheral registers
#

# the NoC node Id is passed in
ihwaddformalparameter -name cluster -type uns32
ihwaddformalparameter -name tile    -type uns32
ihwaddformalparameter -name node    -type uns32

# 0x00000000    0x03ffffff      RAM
ihwaddmemory -instancename ramS -type ram
ihwconnect   -instancename ramS -bus pBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff

# 0x80000000 0x80ffffff NoC peripheral registers
ihwaddperipheral -instancename ni -type TTELNode -vendor safepower.ovpworld.org
ihwconnect   -instancename ni -bus pBus -busslaveport hostif -loaddress 0x80000000 -hiaddress 0x80ffffff
ihwconnect -instancename ni -netport PeriodInterrupt -net period_intc
ihwconnect -instancename ni -netport CoreInterrupt -net core_intc
# the NoC node Id is configured using cluster, tile and node
ihwsetparameter  -handle ni -name cluster -type uns32 -value cluster
ihwsetparameter  -handle ni -name tile    -type uns32 -value tile
ihwsetparameter  -handle ni -name node    -type uns32 -value node

#
# External PacketNet Port
#
ihwaddpacketnetport -instancename networkNodePort -mustbeconnected
ihwaddpacketnet     -instancename networkNode
ihwconnect          -packetnet networkNode -packetnetport networkNodePort

# Connect NoC Peripheral
ihwconnect -instancename ni -packetnetport network -packetnet networkNode

#
# Peripherals
#

# 0x41200000 0x412001ff Xilinx AXI-INTC
ihwaddperipheral -instancename intc -type axi-intc -vendor xilinx.ovpworld.org -version 1.0 
ihwconnect -instancename intc -busslaveport bport1 -bus pBus -loaddress 0x41200000 -hiaddress 0x412001ff
ihwconnect -instancename intc -netport intr3 -net timer_intc
ihwconnect -instancename intc -netport intr2 -net core_intc
ihwconnect -instancename intc -netport intr0 -net period_intc
ihwconnect -instancename intc -netport irq -net intc_mb

ihwconnect -instancename cpu -netport Interrupt -net intc_mb

# 0x41c00000 0x41c0001f Xilinx AXI-Timer
ihwaddperipheral -instancename timer -type axi-timer -vendor xilinx.ovpworld.org -version 1.0 
ihwconnect -instancename timer -busslaveport sp -bus pBus -loaddress 0x41c00000 -hiaddress 0x41c0001f
ihwconnect -instancename timer -netport Interrupt -net timer_intc
ihwsetparameter  -handle timer -name endian -type string -value "little"
ihwsetparameter  -handle timer -name frequency -type double -value 100.000000

# 0x40600000 0x4060000f Xilinx UART-Lite
ihwaddperipheral -instancename uart -type xps-uartlite -vendor xilinx.ovpworld.org -version 1.0 
ihwconnect -instancename uart -busslaveport plb -bus pBus -loaddress 0x40600000 -hiaddress 0x4060000f
ihwsetparameter  -handle uart -name endian -type string -value "little"
ihwsetparameter  -handle uart -name finishOnDisconnect -type bool -value 1

# 0x40810000 0x4081ffff RAM (iic_bu)
ihwaddmemory  -instancename iic_bu -type ram
ihwconnect    -instancename iic_bu -busslaveport sp1 -bus pBus        -loaddress 0x40810000 -hiaddress 0x4081ffff

# 0x40800000 0x4080ffff RAM (iic_imu)
ihwaddmemory  -instancename iic_imu -type ram
ihwconnect    -instancename iic_imu -busslaveport sp1 -bus pBus       -loaddress 0x40800000 -hiaddress 0x4080ffff

# 0x40820000 0x4082ffff RAM (iic_motor)
ihwaddmemory  -instancename iic_motor -type ram
ihwconnect    -instancename iic_motor -busslaveport sp1 -bus pBus     -loaddress 0x40820000 -hiaddress 0x4082ffff

# 0x40000000 0x4003ffff RAM (debug_gpio_led_gimbal)
ihwaddmemory  -instancename debug_gpio_led_gimbal -type ram
ihwconnect    -instancename debug_gpio_led_gimbal -busslaveport sp1 -bus pBus -loaddress 0x40000000 -hiaddress 0x4003ffff

# 0x44A10000 0x44A1ffff RAM (spi_bg)
ihwaddmemory  -instancename spi_bg -type ram
ihwconnect    -instancename spi_bg -busslaveport sp1 -bus pBus        -loaddress 0x44A10000 -hiaddress 0x44A1ffff

# 0x44A00000 0x44A0ffff RAM (ppm)
ihwaddmemory  -instancename ppm -type ram
ihwconnect    -instancename ppm -busslaveport sp1 -bus pBus           -loaddress 0x44A00000 -hiaddress 0x44A0ffff

# 0x44A20000 0x44A2ffff RAM (xadc)
ihwaddmemory  -instancename xadc -type ram
ihwconnect    -instancename xadc -busslaveport sp1 -bus pBus          -loaddress 0x44A20000 -hiaddress 0x44A2ffff

#  0x44A30000 0x44A3ffff RAM (clock_control)
ihwaddmemory  -instancename clock_control -type ram
ihwconnect    -instancename clock_control -busslaveport sp1 -bus pBus -loaddress 0x44A30000 -hiaddress 0x44A3ffff

# 0x44A40000 0x44A4ffff RAM (ttel_clock)
ihwaddmemory  -instancename ttel_clock -type ram
ihwconnect    -instancename ttel_clock -busslaveport sp1 -bus pBus    -loaddress 0x44A40000 -hiaddress 0x44A4ffff
