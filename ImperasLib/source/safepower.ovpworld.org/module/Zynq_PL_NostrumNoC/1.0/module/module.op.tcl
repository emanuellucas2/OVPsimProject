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

set desc "This module implements a configuration for Xilinx Zynq Programmable Logic (PL).
This PL configuration instances four Xilinx MicroBlaze processor based NoC sub-systems (Zync_PL_NoC_node), each with a MicroBlaze processor, local memory and NoC interface Peripheral.
Also included is a NoC interface peripheral that is accessible from the Zynq_PS ARM processors."

set limitations "This is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    Zynq_PL_NostrumNoC
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
# Top Level NoC connection (memory interface to ARM Sub-System)
#

# Include the default interconnect ports and signals for the PL to PS
source "$env(IMPERAS_HOME)/ImperasLib/source/xilinx.ovpworld.org/module/Zynq_PL_Default/1.0/module/PS_PL_interconnect.tcl"

#
# network connection
#
ihwaddpacketnet -instancename network
# heartbeat sync
ihwaddnet -instancename sync

# Main Bus
ihwaddbus -instancename mBus  -addresswidth 32
# GPIO Bus
ihwaddbus -instancename gpiodprBus  -addresswidth 32

# Bridge local memory from input port
# 0x40000000 to 0x400fffff
ihwaddbridge  -instancename smem_extPort
ihwconnect    -instancename smem_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x40000000 -hiaddress 0x400fffff
ihwconnect    -instancename smem_extPort -busmasterport mp1 -bus mBus       -loaddress 0x40000000 -hiaddress 0x400fffff

# 0x41000000 to 0x410fffff
ihwaddbridge  -instancename smem2_extPort
ihwconnect    -instancename smem2_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x41000000 -hiaddress 0x41000fff
ihwconnect    -instancename smem2_extPort -busmasterport mp1 -bus gpiodprBus -loaddress 0x41000000 -hiaddress 0x41000fff

# Bridge NoC node registers from input port
# 0x70020000 to 0x7003ffff
ihwaddbridge  -instancename nocif_extPort
ihwconnect    -instancename nocif_extPort -busslaveport  sp1 -bus extPortBus -loaddress 0x70020000 -hiaddress 0x7003ffff
ihwconnect    -instancename nocif_extPort -busmasterport mp1 -bus mBus       -loaddress 0x70020000 -hiaddress 0x7003ffff

# 0x40000000    0x400001fff      AXI GPIO
ihwaddperipheral -instancename gpio -type axi-gpio -vendor xilinx.ovpworld.org
ihwconnect       -instancename gpio -bus mBus -busslaveport  sp1 -loaddress 0x40000000 -hiaddress 0x400001ff
# connections to Zync GPIO
ihwaddnet  -instancename pio_0_0_gpio_out
ihwconnect -instancename gpio -netport gpio_out -net pio_0_0_gpio_out
ihwaddnet  -instancename pio_0_0_gpio2_in
ihwconnect -instancename gpio -netport gpio2_in -net pio_0_0_gpio2_in

# NoC node
ihwaddperipheral -instancename NoC_0_0 -type NostrumNode -vendor safepower.ovpworld.org
ihwconnect -instancename NoC_0_0 -bus mBus -busslaveport hostif -loaddress 0x70020000 -hiaddress 0x7003ffff
ihwsetparameter  -handle NoC_0_0 -name id -type uns32 -value 0
ihwsetparameter  -handle NoC_0_0 -name generateSync -type bool -value 1
ihwconnect -instancename NoC_0_0 -packetnet network -packetnetport network
ihwconnect -instancename NoC_0_0 -net sync -netport syncOut
# configuration for NoC message buffers and control word
ihwsetparameter  -handle NoC_0_0 -name sendChannelSize -type uns32 -value 3
ihwsetparameter  -handle NoC_0_0 -name mboxSize -type uns32 -value 16

# 0x41000000    0x410001ff      AXI GPIO
ihwaddperipheral -instancename gpio_dpr -type axi-gpio -vendor xilinx.ovpworld.org
ihwconnect       -instancename gpio_dpr -bus gpiodprBus -busslaveport  sp1 -loaddress 0x41000000 -hiaddress 0x410001ff
# connections to Zync GPIO
ihwaddnet        -instancename pio_dpr_gpio_out
#ihwaddnet        -instancename pio_dpr_gpio2_in
ihwconnect       -instancename gpio_dpr -netport gpio_out -net pio_dpr_gpio_out
# gpio_dpr and gpio_0_0 have same input connection from SW_S
ihwconnect       -instancename gpio_dpr -netport gpio2_in -net pio_0_0_gpio2_in

#
# Microblaze NoC 0_1
#
ihwaddmodule -instancename NoC_0_1 \
             -vendor safepower.ovpworld.org -type Zynq_PL_NostrumNoC_node \
             -library module -version 1.0
ihwsetparameter  -handle NoC_0_1 -name nocid -type uns32 -value 1
ihwconnect   -instancename NoC_0_1 -packetnet network -packetnetport networkNodePort
ihwconnect   -instancename NoC_0_1 -net sync -netport syncInPort
# configuration for NoC message buffers and control word
ihwsetparameter  -handle NoC_0_1 -name sendChannelSize -type uns32 -value 3
ihwsetparameter  -handle NoC_0_1 -name mboxSize -type uns32 -value 16
ihwconnect    -instancename NoC_0_1 -busport gpiodprPort -bus gpiodprBus
ihwaddnet   -instancename pio_0_1_gpio_out
ihwaddnet   -instancename pio_0_1_gpio2_in
ihwconnect    -instancename NoC_0_1 -netport gpio_outP -net pio_0_1_gpio_out
ihwconnect    -instancename NoC_0_1 -netport gpio2_inP -net pio_0_1_gpio2_in


#
# Microblaze NoC 1_0
#
ihwaddmodule -instancename NoC_1_0 \
	     -vendor safepower.ovpworld.org -type Zynq_PL_NostrumNoC_node \
	     -library module -version 1.0
ihwsetparameter  -handle NoC_1_0 -name nocid -type uns32 -value 2
ihwconnect   -instancename NoC_1_0 -packetnet network -packetnetport networkNodePort
ihwconnect   -instancename NoC_1_0 -net sync -netport syncInPort
# configuration for NoC message buffers and control word
ihwsetparameter  -handle NoC_1_0 -name sendChannelSize -type uns32 -value 2
ihwsetparameter  -handle NoC_1_0 -name mboxSize        -type uns32 -value 16
ihwconnect    -instancename NoC_1_0 -busport gpiodprPort -bus gpiodprBus
ihwaddnet   -instancename pio_1_0_gpio_out
ihwaddnet   -instancename pio_1_0_gpio2_in
ihwconnect    -instancename NoC_1_0 -netport gpio_outP -net pio_1_0_gpio_out
ihwconnect    -instancename NoC_1_0 -netport gpio2_inP -net pio_1_0_gpio2_in

#
# Microblaze NoC 1_1
#
ihwaddmodule -instancename NoC_1_1 \
	     -vendor safepower.ovpworld.org -type Zynq_PL_NostrumNoC_node \
	     -library module -version 1.0
ihwsetparameter  -handle NoC_1_1 -name nocid -type uns32 -value 3
ihwconnect   -instancename NoC_1_1 -packetnet network -packetnetport networkNodePort
ihwconnect   -instancename NoC_1_1 -net sync -netport syncInPort
# configuration for NoC message buffers and control word
ihwsetparameter  -handle NoC_1_1 -name sendChannelSize -type uns32 -value 2
ihwsetparameter  -handle NoC_1_1 -name mboxSize -type uns32 -value 16
ihwconnect    -instancename NoC_1_1 -busport gpiodprPort -bus gpiodprBus
ihwaddnet     -instancename pio_1_1_gpio_out
ihwaddnet     -instancename pio_1_1_gpio2_in
ihwconnect    -instancename NoC_1_1 -netport gpio_outP -net pio_1_1_gpio_out
ihwconnect    -instancename NoC_1_1 -netport gpio2_inP -net pio_1_1_gpio2_in

