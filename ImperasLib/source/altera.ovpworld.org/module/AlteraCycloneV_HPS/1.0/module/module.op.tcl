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

# Setup variables for platform info
set vendor  altera.ovpworld.org
set library module
set name    AlteraCycloneV_HPS
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -releasestatus ovp -purpose module

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "This platform models the Altera Cyclone V SOC FPGA chip Hard Processor System."
iadddocumentation -name Description -text "The processor is an ARM Cortex-A9MPx2."

iadddocumentation -name Limitations -text "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux."

iadddocumentation -name Reference   -text "Cyclone V Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30."

#
# Static Memory Bus (SMB)
#
ihwaddbus -instancename smbus -addresswidth 32

#
# Processor
#

ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -version 1.0 -endian little \
                -simulateexceptions -mips 100.0
ihwsetparameter -handle cpu -name variant                     -value Cortex-A9MPx2   -type enum
ihwsetparameter -handle cpu -name compatibility               -value ISA             -type enum
ihwsetparameter -handle cpu -name UAL                         -value 1               -type bool
ihwsetparameter -handle cpu -name showHiddenRegs              -value 0               -type bool
ihwsetparameter -handle cpu -name override_CBAR               -value 0xfffec000      -type uns32
ihwsetparameter -handle cpu -name override_GICD_TYPER_ITLines -value 6               -type uns32

# Connect processor to bus
ihwconnect -bus smbus -instancename cpu -busmasterport INSTRUCTION
ihwconnect -bus smbus -instancename cpu -busmasterport DATA

#
# RAM
#

# 0x00000000    0x3fffffff  SRAM (default 1GB)
ihwaddmemory -instancename sram1  -type ram
ihwconnect -bus smbus -instancename sram1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x3fffffff

#
# PERIPHERALS
#

# 0xfffef000    0xfffeffff  PL310 L2 Cache Controller
ihwaddperipheral -instancename L2 -type L2CachePL310 -vendor arm.ovpworld.org
ihwconnect       -instancename L2 -bus smbus  -busslaveport  bport1 -loaddress 0xfffef000 -hiaddress 0xfffeffff

# 0xffc08000    0xffc08fff    timer0  dw-apb-timer
ihwaddperipheral -instancename timer0 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer0 -bus smbus  -busslaveport  bport1 -loaddress 0xffc08000 -hiaddress 0xffc08fff
ihwaddnet        -instancename ir199
ihwconnect       -instancename timer0 -net ir199 -netport irq
ihwconnect       -instancename cpu    -net ir199 -netport SPI199

# 0xffc09000    0xffc09fff    timer1  dw-apb-timer
ihwaddperipheral -instancename timer1 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer1 -bus smbus  -busslaveport  bport1 -loaddress 0xffc09000 -hiaddress 0xffc09fff
ihwaddnet        -instancename ir200
ihwconnect       -instancename timer1 -net ir200 -netport irq
ihwconnect       -instancename cpu    -net ir200 -netport SPI200

# 0xffd00000    0xffd00fff    timer2  dw-apb-timer
ihwaddperipheral -instancename timer2 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer2 -bus smbus  -busslaveport  bport1 -loaddress 0xffd00000 -hiaddress 0xffd00fff
ihwaddnet        -instancename ir201
ihwconnect       -instancename timer2 -net ir201 -netport irq
ihwconnect       -instancename cpu    -net ir201 -netport SPI201

# 0xffd01000    0xffd01fff    timer3  dw-apb-timer
ihwaddperipheral -instancename timer3 -type dw-apb-timer -vendor altera.ovpworld.org
ihwconnect       -instancename timer3 -bus smbus  -busslaveport  bport1 -loaddress 0xffd01000 -hiaddress 0xffd01fff
ihwaddnet        -instancename ir202
ihwconnect       -instancename timer3 -net ir202 -netport irq
ihwconnect       -instancename cpu    -net ir202 -netport SPI202

# 0xffc02000    0x0xffc02fff  uart0 dw-apb-uart
ihwaddperipheral -instancename uart0  -type dw-apb-uart -vendor altera.ovpworld.org
ihwsetparameter    -handle       uart0  -name outfile -value uart0.log     -type string
ihwsetparameter    -handle       uart0  -name console -value 1             -type bool
ihwsetparameter    -handle       uart0  -name finishOnDisconnect -value 1  -type bool
ihwconnect       -instancename uart0  -bus smbus  -busslaveport  bport1 -loaddress 0xffc02000 -hiaddress 0xffc02fff
ihwaddnet        -instancename ir194
ihwconnect       -instancename uart0  -net ir194 -netport intOut
ihwconnect       -instancename cpu    -net ir194 -netport SPI194

# 0xffc03000    0x0xffc03fff  uart1 dw-apb-uart
ihwaddperipheral -instancename uart1  -type dw-apb-uart -vendor altera.ovpworld.org
ihwsetparameter    -handle       uart1  -name outfile -value uart1.log   -type string
ihwsetparameter    -handle       uart1  -name console -value 1           -type bool
ihwsetparameter    -handle       uart1  -name finishOnDisconnect         -type bool
ihwconnect       -instancename uart1  -bus smbus  -busslaveport  bport1 -loaddress 0xffc03000 -hiaddress 0xffc03fff
ihwaddnet        -instancename ir195
ihwconnect       -instancename uart1  -net ir195 -netport intOut
ihwconnect       -instancename cpu    -net ir195 -netport SPI195

# 0xffd05000    0xffd05fff  RSTMGR Reset Manager 
ihwaddnet        -instancename cpu0Reset
ihwaddnet        -instancename cpu1Reset
ihwaddperipheral -instancename RSTMGR0 -vendor altera.ovpworld.org -type RSTMGR
ihwconnect       -instancename RSTMGR0 -bus smbus  -busslaveport  bport1 -loaddress 0xffd05000 -hiaddress 0xffd05fff
ihwconnect       -instancename RSTMGR0 -net cpu0Reset -netport cpu0Reset
ihwconnect       -instancename RSTMGR0 -net cpu1Reset -netport cpu1Reset
ihwconnect       -instancename cpu    -net cpu0Reset -netport reset_CPU0
ihwconnect       -instancename cpu    -net cpu1Reset -netport reset_CPU1

# Dummy Peripherals:

# 0xffd08000    0xffd08fff  SYSMGR System Manager - dummy
ihwaddperipheral -instancename SYSMGR0  -vendor ovpworld.org -type trap
ihwconnect       -instancename SYSMGR0 -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       SYSMGR0 -name portAddress -value 0xffd08000 -type uns32

# 0xffd04000    0xffd04fff  CLKMGR Clock Manager - dummy
ihwaddperipheral -instancename CLKMGR0 -vendor ovpworld.org -type trap
ihwconnect       -instancename CLKMGR0 -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       CLKMGR0 -name portAddress -value 0xffd04000 -type uns32

# 0xffe01000    0xffe01fff  pdma DMA device - dummy
ihwaddperipheral -instancename pdma0 -vendor ovpworld.org -type trap
ihwconnect       -instancename pdma0 -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       pdma0 -name portAddress -value 0xffe01000 -type uns32

# 0xff700000    0xff700fff  gmac0 Ethernet device - dummy
ihwaddperipheral -instancename gmac0 -vendor ovpworld.org -type trap
ihwconnect       -instancename gmac0 -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       gmac0 -name portAddress -value 0xff700000 -type uns32

# 0xff701000    0xff701fff  emac0_dma Ethernet dma device - dummy
ihwaddperipheral -instancename emac0_dma -vendor ovpworld.org -type trap
ihwconnect       -instancename emac0_dma -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       emac0_dma -name portAddress    -value 0xff701000 -type uns32

# 0xff702000    0xff702fff  gmac1 Ethernet device - dummy
ihwaddperipheral -instancename gmac1 -vendor ovpworld.org -type trap
ihwconnect       -instancename gmac1 -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       gmac1 -name portAddress -value 0xff702000 -type uns32

# 0xff703000    0xff703fff  emac1_dma Ethernet dma device - dummy
ihwaddperipheral -instancename emac1_dma -vendor ovpworld.org -type trap
ihwconnect       -instancename emac1_dma -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       emac1_dma -name portAddress -value 0xff703000 -type uns32

#
# Linux BootLoader
#

ihwaddperipheral -instancename smartLoader  -type SmartLoaderArmLinux  -vendor arm.ovpworld.org
ihwconnect       -instancename smartLoader  -bus smbus -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter  -handle       smartLoader  -name boardid      -value 0xffffffff                  -type uns32
ihwsetparameter  -handle       smartLoader  -name kernel       -value zImage                      -type string
ihwsetparameter  -handle       smartLoader  -name initrd       -value fs.img                      -type string
ihwsetparameter  -handle       smartLoader  -name command      -value "mem=1024M console=ttyS0"   -type string
ihwsetparameter  -handle       smartLoader  -name physicalbase -value 0x00000000                  -type uns32
ihwsetparameter  -handle       smartLoader  -name memsize      -value 0x40000000                  -type uns32
ihwsetparameter  -handle       smartLoader  -name disable      -value 0                           -type bool
