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


set desc "This platform models the ARM Versatile Express development board with the Legacy memory map.
It provides the peripherals required to boot and run Operating Systems such as Linux or Android.
The main processor is an ARM Cortex-A9UP.
This platform is deprecated in favor of the ArmVersatileExpress-CA9 platform which models additional behavior, including TrustZone."

# Setup variables for platform info
set vendor  arm.ovpworld.org
set library platform
set name    ArmVersatileExpress
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose epk -releasestatus ovp

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text $desc

iadddocumentation -name Limitations -text "No known limitations for executing Linux operating system."

iadddocumentation -name Reference   -text "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express"

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
ihwaddnet -instancename ir15
ihwaddnet -instancename ir16
ihwaddnet -instancename ir44
ihwaddnet -instancename ir48
ihwaddnet -instancename cardin
ihwaddnet -instancename wprot

#
# Static Memory Bus (SMB)
#
ihwaddbus -instancename smbus -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -version 1.0 \
                -endian little \
                -simulateexceptions \
                -mips 448.0

ihwsetparameter -handle cpu -name variant            -value Cortex-A9MPx1   -type enum
ihwsetparameter -handle cpu -name compatibility      -value ISA             -type enum
ihwsetparameter -handle cpu -name UAL                -value 1               -type bool
ihwsetparameter -handle cpu -name showHiddenRegs     -value 0               -type bool
ihwsetparameter -handle cpu -name override_CBAR      -value 0x1e000000      -type uns32


#
# Connect processor to bus
#
ihwconnect -bus smbus -instancename cpu -busmasterport INSTRUCTION
ihwconnect -bus smbus -instancename cpu -busmasterport DATA


foreach i { 2 3 4 5 6 7 8 9 10 12 13 15 16 44 48 } {
    ihwconnect -net ir${i} -instancename cpu -netport SPI[expr $i + 32]
}


# 0x10000000    0x10000fff  VexpressSysRegs System registers
ihwaddperipheral -instancename sysRegs -type VexpressSysRegs -vendor arm.ovpworld.org
ihwconnect       -instancename sysRegs -bus smbus  -busslaveport  bport1 -loaddress 0x10000000 -hiaddress 0x10000fff
ihwconnect       -instancename sysRegs -net cardin -netport cardin
ihwconnect       -instancename sysRegs -net wprot  -netport wprot

# 0x10001000    0x10001fff      SP810 system control
ihwaddperipheral -instancename sysCtrl -type SysCtrlSP810 -vendor arm.ovpworld.org
ihwconnect       -instancename sysCtrl -bus smbus  -busslaveport  bport1 -loaddress 0x10001000 -hiaddress 0x10001fff

# 0x10002000    0x10002fff      serial bus PCI

# 0x10004000    0x10004fff      PL041 audio
ihwaddperipheral -instancename aac1 -type AaciPL041 -vendor arm.ovpworld.org
ihwconnect       -instancename aac1 -bus smbus  -busslaveport  bport1 -loaddress 0x10004000 -hiaddress 0x10004fff


# 0x10005000    0x10005fff  MmciPL181   pl181
ihwaddperipheral -instancename mmc1 -type MmciPL181 -vendor arm.ovpworld.org
ihwconnect       -instancename mmc1 -bus smbus  -busslaveport  bport1 -loaddress 0x10005000 -hiaddress 0x10005fff
ihwconnect       -instancename mmc1  -net ir9 -netport irq0
ihwconnect       -instancename mmc1  -net ir10 -netport irq1

ihwconnect       -instancename mmc1  -net cardin -netport cardin
ihwconnect       -instancename mmc1  -net wprot  -netport wprot


# 0x10006000    0x10006fff  KbPL050 pl050_keyboard
ihwaddperipheral -instancename kb1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename kb1 -bus smbus  -busslaveport  bport1 -loaddress 0x10006000 -hiaddress 0x10006fff
ihwconnect       -instancename kb1  -net ir12 -netport irq
ihwsetparameter    -handle       kb1 -name isKeyboard  -value 1       -type bool
ihwsetparameter    -handle       kb1 -name grabDisable -value 1       -type bool

# 0x10007000    0x10007fff  KbPL050 pl050_mouse
ihwaddperipheral -instancename ms1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename ms1 -bus smbus  -busslaveport  bport1 -loaddress 0x10007000 -hiaddress 0x10007fff
ihwconnect       -instancename ms1  -net ir13 -netport irq
ihwsetparameter    -handle       ms1 -name isMouse     -value 1       -type bool
ihwsetparameter    -handle       ms1 -name grabDisable -value 1       -type bool


# 0x10009000    0x10009fff  UartPL011   pl011
ihwaddperipheral -instancename uart0  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter    -handle       uart0  -name variant  -value ARM         -type enum
ihwsetparameter    -handle       uart0  -name outfile  -value uart0.log   -type string
ihwsetparameter    -handle       uart0  -name finishOnDisconnect -value 1 -type bool
ihwconnect       -instancename uart0  -bus smbus  -busslaveport  bport1 -loaddress 0x10009000 -hiaddress 0x10009fff
ihwconnect       -instancename uart0  -net ir5 -netport irq

# 0x1000a000    0x1000afff  UartPL011   pl011
ihwaddperipheral -instancename uart1  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter    -handle       uart1  -name variant  -value ARM         -type enum
ihwsetparameter    -handle       uart1  -name outfile -value uart1.log    -type string
ihwsetparameter    -handle       uart1  -name finishOnDisconnect -value 1 -type bool
ihwconnect       -instancename uart1  -bus smbus  -busslaveport  bport1 -loaddress 0x1000a000 -hiaddress 0x1000afff
ihwconnect       -instancename uart1  -net ir6 -netport irq

# 0x1000b000    0x1000bfff  UartPL011   pl011
ihwaddperipheral -instancename uart2  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter  -handle       uart2  -name variant  -value ARM              -type enum
ihwconnect       -instancename uart2  -bus smbus  -busslaveport  bport1 -loaddress 0x1000b000 -hiaddress 0x1000bfff
ihwconnect       -instancename uart2  -net ir7 -netport irq

# 0x1000c000    0x1000cfff  UartPL011   pl011
ihwaddperipheral -instancename uart3  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter    -handle       uart3  -name variant  -value ARM              -type enum
ihwconnect       -instancename uart3  -bus smbus  -busslaveport  bport1 -loaddress 0x1000c000 -hiaddress 0x1000cfff
ihwconnect       -instancename uart3  -net ir8 -netport irq

# 0x1000f000    0x1000ffff      SP805 WDT
ihwaddperipheral -instancename wdt1 -type WdtSP805 -vendor arm.ovpworld.org
ihwconnect       -instancename wdt1 -bus smbus  -busslaveport  bport1 -loaddress 0x1000f000 -hiaddress 0x1000ffff


# 0x10011000    0x10011fff  TimerSP804  sp804 Timer
ihwaddperipheral -instancename timer01 -type TimerSP804 -vendor arm.ovpworld.org
ihwconnect       -instancename timer01 -bus smbus  -busslaveport  bport1 -loaddress 0x10011000 -hiaddress 0x10011fff
ihwconnect       -instancename timer01  -net ir2 -netport irq

# 0x10012000    0x10012fff  TimerSP804  sp804 Timer
ihwaddperipheral -instancename timer23 -type TimerSP804 -vendor arm.ovpworld.org
ihwconnect       -instancename timer23 -bus smbus  -busslaveport  bport1 -loaddress 0x10012000 -hiaddress 0x10012fff
ihwconnect       -instancename timer23  -net ir3 -netport irq


# 0x10016000    0x10016fff      Serial Bus DVI
ihwaddperipheral -instancename dvi1 -type SerBusDviRegs -vendor arm.ovpworld.org
ihwconnect       -instancename dvi1 -bus smbus  -busslaveport  bport1 -loaddress 0x10016000 -hiaddress 0x10016fff

# 0x10017000    0x10017fff  RtcPL031    pl031 RTC
ihwaddperipheral -instancename rtc1 -type RtcPL031 -vendor arm.ovpworld.org
ihwconnect       -instancename rtc1 -bus smbus  -busslaveport  bport1 -loaddress 0x10017000 -hiaddress 0x10017fff
ihwconnect       -instancename rtc1 -net ir4 -netport irq

# 0x1001a000    0x1001afff      Compact Flash
ihwaddperipheral -instancename cf1 -type CompactFlashRegs -vendor arm.ovpworld.org
ihwconnect       -instancename cf1 -bus smbus  -busslaveport  bport1 -loaddress 0x1001a000 -hiaddress 0x1001afff

# 0x1001f000    0x1001ffff  LcdPL110    PL111 CLCD (motherboard)
# Use daughterboard CLCD instead, map as RAM
ihwaddmemory -instancename lcd2  -type ram
ihwconnect -bus smbus -instancename lcd2 -busslaveport sp1 -loaddress 0x1001f000 -hiaddress 0x1001ffff

# 0x10020000    0x1002ffff  LcdPL110    PL111 CLCD (daughterboard)
ihwaddperipheral -instancename lcd1 -type LcdPL110 -vendor arm.ovpworld.org
ihwconnect       -instancename lcd1 -bus smbus  -busslaveport  bport1 -loaddress 0x10020000 -hiaddress 0x10020fff
ihwconnect       -instancename lcd1 -bus smbus -busslaveport memory
ihwsetparameter    -handle       lcd1 -name resolution -value xga              -type enum
ihwconnect       -instancename lcd1  -net ir44 -netport irq


# 0x10060000    0x100dffff      AXI RAM
# Not implemented - documentation incomplete?

# 0x100e0000    0x100e0fff      PL341 Dynamic Memory Controller
ihwaddperipheral -instancename dmc1 -type DMemCtrlPL341 -vendor arm.ovpworld.org
ihwconnect       -instancename dmc1 -bus smbus  -busslaveport  bport1 -loaddress 0x100e0000 -hiaddress 0x100e0fff

# 0x100e1000    0x100e1fff      PL354 Static Memory Controller
ihwaddperipheral -instancename smc1 -type SMemCtrlPL354 -vendor arm.ovpworld.org
ihwconnect       -instancename smc1 -bus smbus  -busslaveport  bport1 -loaddress 0x100e1000 -hiaddress 0x100e1fff

# 0x100e2000    0x100e2fff      System Configuration Controller

# 0x100e4000    0x100e4fff  TimerSP804  sp804
ihwaddperipheral -instancename timer45 -type TimerSP804 -vendor arm.ovpworld.org
ihwconnect       -instancename timer45 -bus smbus  -busslaveport  bport1 -loaddress 0x100e4000 -hiaddress 0x100e4fff
ihwconnect       -instancename timer45 -net ir48 -netport irq


# 0x100e5000    0x100e5fff      SP805 Watchdog module
# Not implemented

# 0x100e6000    0x100e6fff      BP147 TrustZone Protection Controller
# Not implemented

# 0x100e8000    0x100e8fff  GPIO  - dummy - not documented
ihwaddperipheral -instancename gpio0 -vendor ovpworld.org -type trap
ihwconnect       -instancename gpio0 -busslaveport bport1 -bus smbus
ihwsetparameter  -handle       gpio0 -name portAddress -value 0x100e8000 -type uns32

# 0x100e9000    0x100e9fff      PL301 'Fast' AXI matrix
# Not implemented

# 0x100ea000    0x100eafff      PL301 'Slow' AXI matrix
# Not implemented

# 0x100ec000    0x100ecfff      TrustZone Address Space Controller
# Not implemented

# 0x10200000    0x103fffff      CoreSight debug APB
# Not implemented

# 0x1e00a000    0x1e00afff      PL310 L2 Cache Controller
ihwaddperipheral -instancename l2regs -type L2CachePL310 -vendor arm.ovpworld.org
ihwconnect       -instancename l2regs -bus smbus  -busslaveport  bport1 -loaddress 0x1e00a000 -hiaddress 0x1e00afff

# 0x40000000    0x43ffffff      CS0: NOR0 flash
ihwaddmemory -instancename nor0  -type ram
ihwconnect -bus smbus -instancename nor0 -busslaveport sp1 -loaddress 0x40000000 -hiaddress 0x43ffffff

# 0x44000000    0x47ffffff      CS4: NOR1 flash
ihwaddmemory -instancename nor1  -type ram
ihwconnect -bus smbus -instancename nor1 -busslaveport sp1 -loaddress 0x44000000 -hiaddress 0x47ffffff

# 0x48000000    0x4bffffff  RAM CS2: SRAM
ihwaddmemory -instancename sram1  -type ram
ihwconnect -bus smbus -instancename sram1 -busslaveport sp1 -loaddress 0x48000000 -hiaddress 0x4bffffff

# 0x4c000000    0x4c7fffff  RAM Video RAM
ihwaddmemory -instancename vram1  -type ram
ihwconnect -bus smbus -instancename vram1 -busslaveport sp1 -loaddress 0x4c000000 -hiaddress 0x4c7fffff

# 0x4e000000    0x4effffff      LAN9118 Ethernet
ihwaddperipheral -instancename eth0 -vendor smsc.ovpworld.org -type LAN9118
ihwconnect       -instancename eth0 -bus smbus  -busslaveport  bport1 -loaddress 0x4e000000 -hiaddress 0x4e000fff
ihwconnect       -instancename eth0 -net ir15 -netport irq

# 0x4f000000    0x4fffffff      ISP1761 USB
ihwaddperipheral -instancename usb0 -vendor philips.ovpworld.org -type ISP1761
ihwconnect       -instancename usb0 -bus smbus  -busslaveport  bport1 -loaddress 0x4f000000 -hiaddress 0x4f00ffff
ihwconnect       -instancename usb0 -net ir16 -netport hc_irq

# 0x60000000    0x7fffffff  RAM DDR2 Lower
# 0x80000000    0x83ffffff  RAM Remap
# 0x84000000    0x9fffffff  RAM DDR2 Upper

ihwaddbus -instancename ddr2bus -addresswidth 32

ihwaddmemory -instancename ddr2ram  -type ram
ihwconnect -bus ddr2bus -instancename ddr2ram -busslaveport sp1 -loaddress 0 -hiaddress 0x3fffffff

ihwaddbridge -instancename ddr2RamBridge
ihwconnect -bus smbus   -instancename ddr2RamBridge -busslaveport  sp -loaddress 0x60000000 -hiaddress 0x9fffffff
ihwconnect -bus ddr2bus -instancename ddr2RamBridge -busmasterport mp -loaddress 0 -hiaddress 0x3fffffff

# 0x00000000    0x03ffffff  RAM DDR2 Remapped
ihwaddbridge -instancename ddr2RemapBridge
ihwconnect -bus smbus   -instancename ddr2RemapBridge -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x03ffffff
ihwconnect -bus ddr2bus -instancename ddr2RemapBridge -busmasterport mp -loaddress 0x20000000 -hiaddress 0x23ffffff


# Linux BootLoader
ihwaddperipheral -instancename smartLoader  -type SmartLoaderArmLinux -vendor arm.ovpworld.org -version 1.0
ihwconnect       -instancename smartLoader  -bus smbus -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter    -handle       smartLoader  -name command -value "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0" -type string
ihwsetparameter    -handle       smartLoader  -name physicalbase -value 0x60000000                                                                      -type uns32
ihwsetparameter    -handle       smartLoader  -name memsize -value 0x10000000                                                                           -type uns32
ihwsetparameter    -handle       smartLoader  -name boardid -value 0x8e0                                                                                -type uns32

############################## Command Line Parser ##################################################

ihwaddclp -allargs -usagemessage "Basic Usage. Linux ArmVersatileExpress executable --kernel <kernel image> --ramdisk <initial ramdisk>"
ihwaddclparg -name kernel      -type stringvar -group "user platform config Linux" -description "set the kernel to load"                                    
ihwaddclparg -name ramdisk     -type stringvar -group "user platform config Linux" -description "Specify the ramdisk image e.g. initrd.gz or fs.img for boot"
ihwaddclparg -name command     -type stringvar -group "user platform config Linux" -description "Add additional Linux Kernel command line options"
ihwaddclparg -name sdcard      -type stringvar -group "user platform config Linux" -description "The name of an image file to load by SD Card"
ihwaddclparg -name bootcode    -type stringvar -group "user platform config Linux" -description "Boot code to load and execute"
ihwaddclparg -name uartport    -type uns64var  -group "user platform config Linux" -description "set the port number to open on the UART"
ihwaddclparg -name uartconsole -type boolvar   -group "user platform config Linux" -description "open a console terminal on the UART"
ihwaddclparg -name nographics  -type boolvar   -group "user platform config" -description "Disable the LCD graphics window."
