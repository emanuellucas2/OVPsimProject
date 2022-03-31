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

set desc "
This platform models the ARM Versatile Express development board with a CoreTile Express A15x2 (V2P-CA15) Daughterboard.
See the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0604E_v2p_ca15_tc1_trm.pdf for details of the hardware being modeled. 
Note this platform implements the motherboard's 'Cortex-A Series' memory map.

The default processor is an ARM Cortex-A15MPx2, which may be changed.
"

set limitations "
This platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.
Some of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.

CoreSight software debug and trace ports are not modeled.

Remap option not modeled.

The CLCD does not work in Linux
"

# Setup variables for platform info
set vendor  arm.ovpworld.org
set library platform
set name    ArmVersatileExpress-CA15
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -purpose epk -releasestatus ovp 
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2"

#
# nets
#
ihwaddnet -instancename ir2
ihwaddnet -instancename ir3
ihwaddnet -instancename ir4
ihwaddnet -instancename ir5
ihwaddnet -instancename ir6
ihwaddnet -instancename ir7
ihwaddnet -instancename ir8
ihwaddnet -instancename ir9
ihwaddnet -instancename ir10
ihwaddnet -instancename ir12
ihwaddnet -instancename ir13
ihwaddnet -instancename ir14
ihwaddnet -instancename ir15
ihwaddnet -instancename ir16
ihwaddnet -instancename wprot
ihwaddnet -instancename cardin

#
# pBus  - 40 bits of address (LPAE supported)
#
ihwaddbus -instancename pBus  -addresswidth 40

#
# Processor
#
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -version 1.0 \
                -endian little \
                -simulateexceptions \
                -mips 1000
ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA
ihwsetparameter -handle       cpu -name variant                     -value Cortex-A15MPx2      -type enum
ihwsetparameter -handle       cpu -name compatibility               -value ISA                 -type enum
ihwsetparameter -handle       cpu -name UAL                         -value 1                   -type bool
ihwsetparameter -handle       cpu -name override_CBAR               -value 0x2c000000          -type uns32
ihwsetparameter -handle       cpu -name override_GICD_TYPER_ITLines -value 4                   -type uns32

#
# Connect the supported interrupt request nets 
# to the processor's Shared Peripheral Interrupt ports
#
foreach i { 2 3 4 5 6 7 8 9 10 12 13 14 15 16} {
    ihwconnect -net ir${i} -instancename cpu -netport SPI[expr $i + 32]
}

####################################    CS0     #####################################
# ARM Versatile Motherboard Express uATX (V2M-P1) Peripherals (Cortex-A Series Memory Map)
#  0x00000000:0x03ffffff CS0 - on the motherboard
#  0x08000000:0x0bffffff CS0 aliased
#####################################################################################

# CS0: 0x00000000    0x03ffffff      NOR0 flash (use own bus because it is aliased)
ihwaddbus    -instancename nor0bus    -addresswidth 32
ihwaddmemory -instancename nor0       -type ram
ihwconnect   -instancename nor0       -bus nor0bus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff
ihwaddbridge -instancename nor0Bridge
ihwconnect   -instancename nor0Bridge -bus nor0bus -busmasterport mp  -loaddress 0x00000000 -hiaddress 0x03ffffff
ihwconnect   -instancename nor0Bridge -bus pBus    -busslaveport  sp  -loaddress 0x00000000 -hiaddress 0x03ffffff

# CS0: 0x08000000    0x0bffffff      NOR0 flash alias
ihwaddbridge -instancename nor0Remap
ihwconnect   -instancename nor0Remap  -bus nor0bus -busmasterport mp  -loaddress 0x00000000 -hiaddress 0x03ffffff
ihwconnect   -instancename nor0Remap  -bus pBus    -busslaveport  sp  -loaddress 0x08000000 -hiaddress 0x0bffffff


####################################    CS4     #####################################
# ARM Versatile Motherboard Express uATX (V2M-P1) Peripherals (Cortex-A Series Memory Map)
#  0x0c000000:0x0fffffff CS4 - on the motherboard
#####################################################################################

# CS4: 0x0c000000    0x0fffffff      NOR1 flash
ihwaddmemory -instancename nor1  -type ram
ihwconnect -bus pBus -instancename nor1 -busslaveport sp1 -loaddress 0x0c000000 -hiaddress 0x0fffffff


####################################    CS5     #####################################
# ARM Versatile Motherboard Express uATX (V2M-P1) Peripherals (Cortex-A Series Memory Map)
#  0x10000000:0x13ffffff CS5 - on the motherboard
#####################################################################################

# Reserved


####################################    CS1     #####################################
# ARM Versatile Motherboard Express uATX (V2M-P1) Peripherals (Cortex-A Series Memory Map)
#  0x14000000:0x17ffffff CS1 - on the motherboard
#####################################################################################

# CS1: 0x14000000    0x1bffffff  User SRAM
ihwaddmemory -instancename sram1 -type ram
ihwconnect   -instancename sram1 -bus pBus -busslaveport sp1 -loaddress 0x14000000 -hiaddress 0x17ffffff


####################################    CS2     #####################################
# ARM Versatile Motherboard Express uATX (V2M-P1) Peripherals (Cortex-A Series Memory Map)
#  0x18000000:0x1bffffff CS2 - on the motherboard
#####################################################################################

# CS2: 0x18000000    0x19ffffff      RAM Video RAM
ihwaddmemory -instancename vram1 -type ram
ihwconnect   -instancename vram1 -bus pBus -busslaveport sp1 -loaddress 0x18000000 -hiaddress 0x19ffffff

# CS2: 0x1a000000    0x1a000fff      LAN9118 Ethernet
ihwaddperipheral -instancename eth0 -vendor smsc.ovpworld.org -type LAN9118
ihwconnect       -instancename eth0 -bus pBus  -busslaveport  bport1 -loaddress 0x1a000000 -hiaddress 0x1a000fff
ihwconnect       -instancename eth0 -net ir15 -netport irq

# CS2: 0x1b000000    0x1b00ffff      ISP1761 USB
ihwaddperipheral -instancename usb0 -vendor philips.ovpworld.org -type ISP1761
ihwconnect       -instancename usb0 -bus pBus  -busslaveport  bport1 -loaddress 0x1b000000 -hiaddress 0x1b00ffff
ihwconnect       -instancename usb0 -net ir16 -netport hc_irq


####################################    CS3     #####################################
# ARM Versatile Motherboard Express uATX (V2M-P1) Peripherals (Cortex-A Series Memory Map)
#  0x1c000000:0x1fffffff CS3 - on the motherboard
#####################################################################################

# CS3: 0x1c010000    0x1c010fff  VexpressSysRegs System registers
ihwaddperipheral -instancename sysRegs  -type VexpressSysRegs -vendor arm.ovpworld.org
ihwconnect       -instancename sysRegs  -bus pBus  -busslaveport  bport1 -loaddress 0x1c010000 -hiaddress 0x1c010fff
ihwconnect       -instancename sysRegs  -net wprot  -netport wprot
ihwconnect       -instancename sysRegs  -net cardin -netport cardin
ihwsetparameter    -handle       sysRegs  -name SYS_PROCID0  -value 0x14000237        -type uns32

# CS3: 0x1c020000    0x1c020fff      SP810 system control
ihwaddperipheral -instancename sysCtrl -type SysCtrlSP810 -vendor arm.ovpworld.org
ihwconnect       -instancename sysCtrl -bus pBus  -busslaveport  bport1 -loaddress 0x1c020000 -hiaddress 0x1c020fff

# CS3: 0x1c030000    0x1c030fff      serial bus PCI
# Not implemented

# CS3: 0x1c040000    0x1c040fff      PL041 audio
ihwaddperipheral -instancename aac1 -type AaciPL041 -vendor arm.ovpworld.org
ihwconnect       -instancename aac1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c040000 -hiaddress 0x1c040fff

# CS3: 0x1c050000    0x1c050fff  MmciPL181   pl181
ihwaddperipheral -instancename mmc1 -type MmciPL181 -vendor arm.ovpworld.org
ihwconnect       -instancename mmc1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c050000 -hiaddress 0x1c050fff
ihwconnect       -instancename mmc1  -net ir9    -netport irq0
ihwconnect       -instancename mmc1  -net ir10   -netport irq1
ihwconnect       -instancename mmc1  -net wprot  -netport wprot
ihwconnect       -instancename mmc1  -net cardin -netport cardin

# CS3: 0x1c060000    0x1c060fff  KbPL050 pl050_keyboard
ihwaddperipheral -instancename kb1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename kb1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c060000 -hiaddress 0x1c060fff
ihwconnect       -instancename kb1 -net ir12 -netport irq
ihwsetparameter    -handle       kb1 -name isKeyboard  -value 1         -type bool
ihwsetparameter    -handle       kb1 -name grabDisable -value 1         -type bool

# CS3: 0x1c070000    0x1c070fff  KbPL050 pl050_mouse
ihwaddperipheral -instancename ms1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename ms1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c070000 -hiaddress 0x1c070fff
ihwconnect       -instancename ms1 -net ir13 -netport irq
ihwsetparameter    -handle       ms1 -name isMouse     -value 1         -type bool
ihwsetparameter    -handle       ms1 -name grabDisable -value 1         -type bool

# CS3: 0x1c090000    0x1c090fff  UartPL011   pl011
ihwaddperipheral -instancename uart0  -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart0  -bus pBus -busslaveport  bport1 -loaddress 0x1c090000 -hiaddress 0x1c090fff
ihwconnect       -instancename uart0  -net ir5  -netport irq
ihwsetparameter    -handle       uart0  -name variant  -value ARM           -type enum
ihwsetparameter    -handle       uart0  -name outfile -value uart0.log      -type string
ihwsetparameter    -handle       uart0  -name finishOnDisconnect -value 1   -type bool

# CS3: 0x1c0a0000    0x1c0a0fff  UartPL011   pl011
ihwaddperipheral -instancename uart1  -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart1  -bus pBus -busslaveport  bport1 -loaddress 0x1c0a0000 -hiaddress 0x1c0a0fff
ihwconnect       -instancename uart1  -net ir6  -netport irq
ihwsetparameter    -handle       uart1  -name variant  -value ARM          -type enum
ihwsetparameter    -handle       uart1  -name outfile -value uart1.log     -type string

# CS3: 0x1c0b0000    0x1c0b0fff  UartPL011   pl011
ihwaddperipheral -instancename uart2  -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart2  -bus pBus -busslaveport  bport1 -loaddress 0x1c0b0000 -hiaddress 0x1c0b0fff
ihwconnect       -instancename uart2  -net ir7  -netport irq
ihwsetparameter    -handle       uart2  -name variant  -value ARM          -type enum

# CS3: 0x1c0c0000    0x1c0c0fff  UartPL011   pl011
ihwaddperipheral -instancename uart3  -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart3  -bus pBus -busslaveport  bport1 -loaddress 0x1c0c0000 -hiaddress 0x1c0c0fff
ihwconnect       -instancename uart3  -net ir8  -netport irq
ihwsetparameter    -handle       uart3  -name variant  -value ARM          -type enum

# CS3: 0x1c0f0000    0x1c0f0fff      SP805 WDT
ihwaddperipheral -instancename wdt1 -type WdtSP805 -vendor arm.ovpworld.org
ihwconnect       -instancename wdt1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c0f0000 -hiaddress 0x1c0f0fff

# CS3: 0x1c110000    0x1c110fff  TimerSP804  sp804 Timer
ihwaddperipheral -instancename timer01 -type TimerSP804 -vendor arm.ovpworld.org
ihwconnect       -instancename timer01 -bus pBus -busslaveport  bport1 -loaddress 0x1c110000 -hiaddress 0x1c110fff
ihwconnect       -instancename timer01 -net ir2  -netport irq

# CS3: 0x1c120000    0x1c120fff  TimerSP804  sp804 Timer
ihwaddperipheral -instancename timer23 -type TimerSP804 -vendor arm.ovpworld.org
ihwconnect       -instancename timer23 -bus pBus -busslaveport  bport1 -loaddress 0x1c120000 -hiaddress 0x1c120fff
ihwconnect       -instancename timer23 -net ir3  -netport irq

# CS3: 0x1c160000    0x1c160fff      Serial Bus DVI
ihwaddperipheral -instancename dvi1 -type SerBusDviRegs -vendor arm.ovpworld.org
ihwconnect       -instancename dvi1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c160000 -hiaddress 0x1c160fff

# CS3: 0x1c170000    0x1c170fff  RtcPL031    pl031 RTC
ihwaddperipheral -instancename rtc1 -type RtcPL031 -vendor arm.ovpworld.org
ihwconnect       -instancename rtc1 -bus pBus  -busslaveport  bport1 -loaddress 0x1c170000 -hiaddress 0x1c170fff
ihwconnect       -instancename rtc1 -net ir4 -netport irq

# CS3: 0x1c1a0000    0x1c1a0fff      Compact Flash
ihwaddperipheral -instancename cf1 -type CompactFlashRegs -vendor arm.ovpworld.org
ihwconnect       -instancename cf1 -bus pBus  -busslaveport  bport1 -loaddress 0x1001a000 -hiaddress 0x1001afff

# CS3: 0x1c1b0000    0x1c1b0fff  UartPL011   pl011
ihwaddperipheral -instancename uart4  -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart4  -bus pBus -busslaveport  bport1 -loaddress 0x1c1b0000 -hiaddress 0x1c1b0fff
ihwsetparameter    -handle       uart4  -name variant  -value ARM          -type enum

# CS3: 0x1c1f0000    0x1c1f0fff  LcdPL110    PL111 CLCD (motherboard)
ihwaddperipheral -instancename clcd -type LcdPL110 -vendor arm.ovpworld.org
ihwconnect       -instancename clcd -bus pBus  -busslaveport  bport1 -loaddress 0x1c1f0000 -hiaddress 0x1c1f0fff
ihwconnect       -instancename clcd -bus pBus -busslaveport memory
ihwconnect       -instancename clcd -net ir14 -netport irq
ihwsetparameter    -handle       clcd -name resolution -value xga          -type enum
# Does not work in Linux so disable by default
ihwsetparameter    -handle       clcd -name noGraphics -value 1            -type bool


##############################  Test Chip Peripherals ###############################
# ARM Versatile CoreTile Express A15X2 (V2P-CA15) Daughterboard Peripherals
#  0x20000000:0x2fffffff Test Chip Peripherals
#####################################################################################

# 0x20000000    0x27ffffff      CoreSight debug APB
# Not modeled

# 0x2a000000    0x2a0fffff      AXI network interconnect NIC-301
# Not modeled

# 0x2a420000    0x2a42ffff      SCC System Configuration Controller, Aliased
# Not modeled

# 0x2a430000    0x2a430013      System counter
# Not modeled

# 0x2b000000    0x2b00024f  HDLCD    HDLCD (daughterboard)
# Not modeled

# 0x2b060000    0x2b060fff      SP805 System Watchdo
ihwaddperipheral -instancename wdt2 -type WdtSP805 -vendor arm.ovpworld.org
ihwconnect       -instancename wdt2 -bus pBus  -busslaveport  bport1 -loaddress 0x2b060000 -hiaddress 0x2b060fff

# 0x2b0a0000    0x2b0a0fff      PL341 Dynamic Memory Controller
ihwaddperipheral -instancename dmc1 -type DMemCtrlPL341 -vendor arm.ovpworld.org
ihwconnect       -instancename dmc1 -bus pBus  -busslaveport  bport1 -loaddress 0x2b0a0000 -hiaddress 0x2b0a0fff

# 0x2c000000    0x2c007fff      GIC Geneirc Intrrupt Controller
# Part of processor model

# 0x2e000000    0x2e00ffff      64KB System SRAM
# Not modeled


#####################################################################################
# External AXI Master Interface
#####################################################################################

# 0x7fef0000                    DMC PHY configuration
# Not modeled

# 0x7ffb0000    0x7ffb0fff      DMA-330 Direct memory access controller (Dummy Port)
ihwaddperipheral -instancename dma0 -vendor ovpworld.org -type trap
ihwconnect       -instancename dma0 -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       dma0 -name portAddress -value 0x7ffb0000 -type uns32

# 0x7ffd0000    0x7ffd0fff      PL354 Static Memory Controller
ihwaddperipheral -instancename smc1 -type SMemCtrlPL354 -vendor arm.ovpworld.org
ihwconnect       -instancename smc1 -bus pBus  -busslaveport  bport1 -loaddress 0x7ffd0000 -hiaddress 0x7ffd0fff

# 0x7fff0000    0x7fffffff      SCC System Configuration Controller
# Not modeled


#####################################################################################
# Daughterboard memory
#####################################################################################

# 0x00_80000000    0x00_ffffffff  DDR2 2GB
ihwaddbus    -instancename ddr2bus    -addresswidth 32
ihwaddmemory -instancename ddr2ram    -type ram
ihwconnect   -instancename ddr2ram    -bus ddr2bus -busslaveport  sp1 -loaddress 0 -hiaddress 0x7fffffff
ihwaddbridge -instancename ddr2Bridge
ihwconnect   -instancename ddr2Bridge -bus ddr2bus -busmasterport mp  -loaddress   0x00000000 -hiaddress   0x7fffffff
ihwconnect   -instancename ddr2Bridge -bus pBus    -busslaveport  sp  -loaddress 0x0080000000 -hiaddress 0x00ffffffff

# 0x08_00000000    0x08_7fffffff  DDR2 2GB Alias
ihwaddbridge -instancename ddr2Remap1
ihwconnect   -instancename ddr2Remap1 -bus ddr2bus -busmasterport mp  -loaddress   0x00000000 -hiaddress   0x7fffffff
ihwconnect   -instancename ddr2Remap1 -bus pBus    -busslaveport  sp  -loaddress 0x0800000000 -hiaddress 0x087fffffff

# 0x08_80000000    0x08_ffffffff  DDR2 2GB Alias
ihwaddbridge -instancename ddr2Remap2
ihwconnect   -instancename ddr2Remap2 -bus ddr2bus -busmasterport mp  -loaddress   0x00000000 -hiaddress   0x7fffffff
ihwconnect   -instancename ddr2Remap2 -bus pBus    -busslaveport  sp  -loaddress 0x0880000000 -hiaddress 0x08ffffffff

# 0x80_00000000    0x08_7fffffff  DDR2 2GB Alias
ihwaddbridge -instancename ddr2Remap3
ihwconnect   -instancename ddr2Remap3 -bus ddr2bus -busmasterport mp  -loaddress   0x00000000 -hiaddress   0x7fffffff
ihwconnect   -instancename ddr2Remap3 -bus pBus    -busslaveport  sp  -loaddress 0x8000000000 -hiaddress 0x807fffffff

# 0x80_80000000    0x08_ffffffff  DDR2 2GB Alias
ihwaddbridge -instancename ddr2Remap4
ihwconnect   -instancename ddr2Remap4 -bus ddr2bus -busmasterport mp  -loaddress   0x00000000 -hiaddress   0x7fffffff
ihwconnect   -instancename ddr2Remap4 -bus pBus    -busslaveport  sp  -loaddress 0x8080000000 -hiaddress 0x80ffffffff


#####################################################################################
# OVPworld Linux BootLoader
#####################################################################################

ihwaddperipheral -instancename smartLoader  -type SmartLoaderArmLinux -vendor arm.ovpworld.org -version 1.0
ihwconnect       -instancename smartLoader  -bus pBus -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter    -handle       smartLoader  -name command      -value "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0" -type string
ihwsetparameter    -handle       smartLoader  -name physicalbase -value 0x80000000   -type uns32
ihwsetparameter    -handle       smartLoader  -name memsize      -value 0x80000000   -type uns32
ihwsetparameter    -handle       smartLoader  -name boardid      -value 0x8e0        -type uns32

#####################################################################################
# Command line arguments
#####################################################################################
ihwaddclp -allargs
ihwaddclparg -name  zimage     -group userPlatformConfig -type stringvar -description "Linux zImage file to load using smartLoader"
ihwaddclparg -name  zimageaddr -group userPlatformConfig -type uns64var  -description "Physical address to load zImage file (default:physicalbase + 0x00010000)"
ihwaddclparg -name  initrd     -group userPlatformConfig -type stringvar -description "Linux initrd file to load using smartLoader"
ihwaddclparg -name  initrdaddr -group userPlatformConfig -type uns64var  -description "Physical address to load initrd file (default:physicalbase + 0x00d00000)"
ihwaddclparg -name  linuxsym   -group userPlatformConfig -type stringvar -description "Linux ELF file with symbolic debug info (CpuManger only)"
ihwaddclparg -name  linuxcmd   -group userPlatformConfig -type stringvar -description "Linux command line (default: 'mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0"
ihwaddclparg -name  boardid    -group userPlatformConfig -type int32var  -description "Value to pass to Linux as the boardid (default (0x8e0)"
ihwaddclparg -name  linuxmem   -group userPlatformConfig -type uns64var  -description "Amount of memory allocated to Linux (required in AMP mode)"
ihwaddclparg -name  boot       -group userPlatformConfig -type stringvar -description "Boot code object file (If specified, smartLoader will jump to this rather than zImage)"
ihwaddclparg -name  image0     -group userPlatformConfig -type stringvar -description "Image file to load on cpu0"
ihwaddclparg -name  image0addr -group userPlatformConfig -type uns64var  -description "load address for image on cpu0 (IMAGE0 must be specified)"
ihwaddclparg -name  image0sym  -group userPlatformConfig -type stringvar -description "Elf file with symbolic debug info for image on cpu0 (IMAGE0 must be specified, CpuManger only)"
ihwaddclparg -name  image1     -group userPlatformConfig -type stringvar -description "Image file to load on cpu1 to n"
ihwaddclparg -name  image1addr -group userPlatformConfig -type uns64var  -description "Load address for image on cpu1 to n (IMAGE1 must be specified)"
ihwaddclparg -name  image1sym  -group userPlatformConfig -type stringvar -description "Elf file with symbolic debug info for image on cpu1 to n (IMAGE1 must be specified, CpuManger only)"
ihwaddclparg -name  uart0port  -group userPlatformConfig -type stringvar -description "Uart0 port: 'auto' for automatic console, 0 for simulator chosen port #, or number of specific port"
ihwaddclparg -name  uart1port  -group userPlatformConfig -type stringvar -description "Uart1 port: 'auto' for automatic console, 0 for simulator chosen port #, or number of specific port"
ihwaddclparg -name  nographics -group userPlatformConfig -type boolvar   -description "Inhibit opening of the lcd graphics window"
