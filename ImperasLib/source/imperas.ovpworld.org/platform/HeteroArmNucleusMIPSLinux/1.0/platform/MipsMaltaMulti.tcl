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

set cache 0
if {[info exists env(CACHE)]} {
    set cache $env(CACHE)
}

if {![info exists mSys]} {
	set mSys mipsMain
}


#
# main bus
#
ihwaddbus -instancename bus${mSys} -addresswidth 32

#
# PCI configuration bus
# Mapping base at
#
if     {${platform} == "MipsMaltaLinux"} {
  set pciBaseAddress 0x18000000
} elseif {${platform} == "MipsMaltaNucleus"} {
  set pciBaseAddress 0x1b000000
} else {
  return -code 1
}
proc pciOffset { address } {
    global pciBaseAddress
    return [format 0x%08x [expr ${pciBaseAddress} + ${address}]]
}
ihwaddbus -instancename PCIconfigBus${mSys} -addresswidth 16

#
# 1-word connection to interrupt controller
#
ihwaddbus -instancename PCIackBus${mSys}    -addresswidth 1

#
# interrupt controller master to slave
#
ihwaddbus -instancename cascadeBus${mSys}   -addresswidth 3

#
# main processor
#
if {${platform} == "MipsMaltaLinux"} {
  ihwaddprocessor -instancename mipsle1 -type mips32_r1r5 -vendor mips.ovpworld.org -endian little -simulateexceptions -mips 100 -imagefile mips.vmlinux
}
if {${platform} == "MipsMaltaNucleus"} {
  ihwaddprocessor -instancename mipsle1 -type mips32_r1r5 -vendor mips.ovpworld.org -endian little -simulateexceptions -mips 100 -imagefile mips.vmlinux
}

#
# processor attributes
#
ihwsetparameter -handle mipsle1 -name variant           -value 34Kf    -type enum
ihwsetparameter -handle mipsle1 -name vectoredinterrupt -value 0       -type bool
ihwsetparameter -handle mipsle1 -name config1MMUSizeM1  -value 63      -type uns32

#
# Connect processor to bus
#
ihwconnect -bus bus${mSys} -instancename mipsle1 -busmasterport INSTRUCTION
ihwconnect -bus bus${mSys} -instancename mipsle1 -busmasterport DATA

# procesor to interrupt
ihwconnect -net i8259Int -instancename mipsle1 -netport hwint0

#
# SDRAM
#
ihwaddmemory -instancename Core_Board_SDRAM  -type ram
ihwconnect -bus bus${mSys} -instancename Core_Board_SDRAM -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x07ffffff

if {${platform} == "MipsMaltaLinux"} {
  #
  # smart PROM device
  #
  ihwaddperipheral -instancename Core_Board_SDRAM_promInit -vendor mips.ovpworld.org -library peripheral -version 1.0 -type SmartLoaderLinux
  ihwconnect -bus bus${mSys} -instancename Core_Board_SDRAM_promInit -busmasterport mport  -loaddress 0x0 -hiaddress 0x7fffffff
  ihwconnect -bus bus${mSys} -instancename Core_Board_SDRAM_promInit -busslaveport idport  -loaddress 0x1fc00010 -hiaddress 0x1fc00013

  ihwsetparameter -handle Core_Board_SDRAM_promInit -name kernel      -value mips.vmlinux     -type string
  ihwsetparameter -handle Core_Board_SDRAM_promInit -name boardid     -value 0x00000420       -type uns32
  ihwsetparameter -handle Core_Board_SDRAM_promInit -name initrd      -value mips.initrd.gz   -type string
  ihwsetparameter -handle Core_Board_SDRAM_promInit -name command     -value "console=tty0"   -type string
}

#
# Flash Memory and mapping
#
ihwaddbus    -instancename flashBus -addresswidth 32
ihwaddmemory -instancename Monitor_Flash -type ram
ihwconnect   -instancename Monitor_Flash -bus flashBus -busslaveport sp1 -loaddress 0x1e000000 -hiaddress 0x1e3fffff

# Map flash onto main bus at 0x1e000000
ihwaddbridge -instancename map
ihwconnect -bus bus${mSys} -instancename map -busslaveport sp1 -loaddress 0x1e000000 -hiaddress 0x1e3fffff
ihwconnect -bus flashBus -instancename map -busmasterport mp1 -loaddress 0x1e000000 -hiaddress 0x1e3fffff

# Map flash onto main bus at 0x1fc00000 except the boardId at 0x1fc00010
ihwaddbridge -instancename remap1
ihwaddbridge -instancename remap2

ihwconnect -bus bus${mSys} -instancename remap1 -busslaveport  sp1 -loaddress 0x1fc00000 -hiaddress 0x1fc0000F
ihwconnect -bus flashBus -instancename remap1 -busmasterport mp1 -loaddress 0x1e000000 -hiaddress 0x1e00000f
ihwconnect -bus bus${mSys} -instancename remap2 -busslaveport  sp1 -loaddress 0x1fc00014 -hiaddress 0x1fffffff
ihwconnect -bus flashBus -instancename remap2 -busmasterport mp1 -loaddress 0x1e000014 -hiaddress 0x1e3fffff

#
# system controller
#
ihwaddperipheral -instancename sysControl -vendor marvell.ovpworld.org -library peripheral -version 1.0 -type GT6412x
ihwconnect -bus bus${mSys}         -instancename sysControl -busslaveport  busPort

ihwconnect -bus PCIconfigBus${mSys} -instancename sysControl -busmasterport PCIconfigM
ihwconnect -bus PCIconfigBus${mSys} -instancename sysControl -busslaveport PCIconfig
ihwconnect -bus PCIackBus${mSys}    -instancename sysControl -busmasterport PCIackM

# PCI base
ihwaddperipheral -instancename PIIX4 -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 82371EB
ihwconnect       -instancename PIIX4 -busslaveport PCIconfig  -bus PCIconfigBus${mSys}
ihwsetparameter    -handle PIIX4       -name PCIslot -value 10     -type uns32

#
# IDE
#
ihwaddperipheral -instancename PIIX4-IDE -vendor intel.ovpworld.org -library peripheral -version 1.0 -type PciIDE

ihwsetparameter -handle PIIX4-IDE -name PCIslot     -value 10            -type uns32
ihwsetparameter -handle PIIX4-IDE -name PCIfunction -value 1             -type uns32
ihwsetparameter -handle PIIX4-IDE -name Drive0Name  -value mipsel_hda    -type string
ihwsetparameter -handle PIIX4-IDE -name Drive1Name  -value mipsel_hdb    -type string
ihwsetparameter -handle PIIX4-IDE -name Drive2Name  -value mipsel_cd     -type string

ihwconnect -bus PCIconfigBus${mSys} -instancename PIIX4-IDE -busslaveport  PCIconfig
ihwconnect -bus bus${mSys}         -instancename PIIX4-IDE -busslaveport  busPort
ihwconnect -bus bus${mSys}         -instancename PIIX4-IDE -busmasterport dmaPort

ihwconnect -net intCtl_ir14 -instancename PIIX4-IDE -netport intOut0
ihwconnect -net intCtl_ir15 -instancename PIIX4-IDE -netport intOut1

#
# USB
#
ihwaddperipheral -instancename PCI_USB -vendor intel.ovpworld.org -library peripheral -version 1.0 -type PciUSB
ihwsetparameter    -handle PCI_USB -name PCIslot     -value 10           -type uns32
ihwsetparameter    -handle PCI_USB -name PCIfunction -value 2            -type uns32

ihwconnect -bus PCIconfigBus${mSys} -instancename PCI_USB -busslaveport  PCIconfig
ihwconnect -bus bus${mSys}          -instancename PCI_USB -busslaveport  busPort

#
# Power Manager
#
ihwaddperipheral -instancename PCI_PM -vendor intel.ovpworld.org -library peripheral -version 1.0 -type PciPM
ihwsetparameter -handle PCI_PM -name PCIslot     -value 10               -type uns32
ihwsetparameter -handle PCI_PM -name PCIfunction -value 3                -type uns32

ihwconnect -bus PCIconfigBus${mSys} -instancename PCI_PM -busslaveport  PCIconfig
ihwconnect -bus bus${mSys}         -instancename PCI_PM -busslaveport  busPort

#
# Network
#
ihwaddperipheral -instancename PCI_NET -vendor amd.ovpworld.org -library peripheral -version 1.0 -type 79C970
ihwsetparameter -handle PCI_NET -name PCIslot     -value 11            -type uns32
ihwsetparameter -handle PCI_NET -name PCIfunction -value 0             -type uns32

ihwconnect -bus PCIconfigBus${mSys} -instancename PCI_NET -busslaveport  PCIconfig
ihwconnect -bus bus${mSys}         -instancename PCI_NET -busslaveport  busPort
ihwconnect -bus bus${mSys}         -instancename PCI_NET -busmasterport dmaPort

ihwconnect -net intCtl_ir10  -instancename PCI_NET -netport       intOut0

#
# Interrupt controller Master
#
ihwaddperipheral -instancename intCtrlMaster -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 8259A

ihwconnect -bus bus${mSys}      -instancename intCtrlMaster   -busslaveport  io      -loaddress [pciOffset 0x0020] -hiaddress [pciOffset 0x0021]
ihwconnect -bus bus${mSys}      -instancename intCtrlMaster   -busslaveport  elcr    -loaddress [pciOffset 0x04d0] -hiaddress [pciOffset 0x04d0]
ihwconnect -bus cascadeBus${mSys} -instancename intCtrlMaster  -busmasterport cascade
ihwconnect -bus PCIackBus${mSys} -instancename intCtrlMaster   -busslaveport  PCIackS -loaddress 0                  -hiaddress 0

ihwconnect -net i8259Int     -instancename intCtrlMaster -netport       intp
if {${platform} == "MipsMaltaLinux"} {
  ihwconnect -net intCtl_ir1   -instancename intCtrlMaster -netport       ir1
}
ihwconnect -net intCtl_ir3   -instancename intCtrlMaster -netport       ir3
ihwconnect -net intCtl_ir4   -instancename intCtrlMaster -netport       ir4
ihwconnect -net i8259Cascade -instancename intCtrlMaster -netport       ir2

ihwsetparameter -handle intCtrlMaster -name spen -value master          -type enum

#
# Interrupt controller Slave
#
ihwaddperipheral -instancename intCtrlSlave -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 8259A

ihwconnect -bus bus${mSys}       -instancename intCtrlSlave   -busslaveport  io      -loaddress [pciOffset 0x00a0] -hiaddress [pciOffset 0x00a1]
ihwconnect -bus bus${mSys}       -instancename intCtrlSlave   -busslaveport  elcr    -loaddress [pciOffset 0x04d1] -hiaddress [pciOffset 0x04d1]
ihwconnect -bus cascadeBus${mSys} -instancename intCtrlSlave   -busslaveport  PCIackS -loaddress 2          -hiaddress 2

ihwconnect -net intCtl_ir8   -instancename intCtrlSlave -netport       ir0
ihwconnect -net intCtl_ir10  -instancename intCtrlSlave -netport       ir2
if {${platform} == "MipsMaltaLinux"} {
  #
  # Add keyboard interrupt
  #
  ihwconnect -net intCtl_ir12  -instancename intCtrlSlave -netport       ir4
}
ihwconnect -net intCtl_ir14  -instancename intCtrlSlave -netport       ir6
ihwconnect -net intCtl_ir15  -instancename intCtrlSlave -netport       ir7
ihwconnect -net i8259Cascade -instancename intCtrlSlave -netport       intp

ihwsetparameter -handle intCtrlSlave -name spen -value slave          -type enum

#
# Serial interrupt encoder - part of SUPERIO device
#
if {${platform} == "MipsMaltaNucleus"} {
  ihwaddperipheral -instancename _SUPERIO_REG_  -type SerInt -vendor ovpworld.org
  ihwconnect -bus bus${mSys} -instancename _SUPERIO_REG_ -busslaveport bport1 -loaddress [pciOffset 0xb0] -hiaddress [pciOffset 0xb3]
}

#
# VGA
#
ihwaddperipheral -instancename vga -vendor cirrus.ovpworld.org -library peripheral -version 1.0 -type GD5446
ihwsetparameter -handle vga -name scanDelay -value 50000                  -type uns32
ihwsetparameter -handle vga -name PCIslot   -value 18                     -type uns32
ihwsetparameter -handle vga -name title     -value "Imperas MIPS32 Malta" -type string
ihwsetparameter -handle vga -name noGraphics                              -type bool

ihwconnect -bus PCIconfigBus${mSys} -instancename vga -busslaveport  PCIconfig
ihwconnect -bus bus${mSys}         -instancename vga -busslaveport  config    -loaddress [pciOffset 0x03b0] -hiaddress [pciOffset 0x03df]
ihwconnect -bus bus${mSys}         -instancename vga -busslaveport  memory

#
# Ps2Control
#
ihwaddperipheral -instancename Ps2Control -vendor intel.ovpworld.org -library peripheral -version 1.0 -type Ps2Control

ihwsetparameter    -handle Ps2Control -name pollPeriod   -value 5000     -type uns32
ihwsetparameter    -handle Ps2Control -name grabDisable  -value 1        -type bool

ihwconnect       -instancename Ps2Control -bus bus${mSys}        -busslaveport  config  -loaddress [pciOffset 0x0060] -hiaddress [pciOffset 0x0067]
if {${platform} == "MipsMaltaLinux"} {
  #
  # Add keyboard/mouse interrupt
  #
  ihwconnect       -instancename Ps2Control -net intCtl_ir1  -netport  kbdInterrupt
  ihwconnect       -instancename Ps2Control -net intCtl_ir12 -netport  mouseInterrupt
}

#
# Programmable Interval Timer
#
ihwaddperipheral -instancename mpit -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 8253
ihwconnect       -instancename mpit -bus bus${mSys} -busslaveport  bport1 -loaddress [pciOffset 0x0040] -hiaddress [pciOffset 0x0043]

#
# RTC
#
ihwaddperipheral -instancename mrtc -vendor motorola.ovpworld.org -library peripheral -version 1.0 -type MC146818
ihwconnect       -instancename mrtc -bus bus${mSys}       -busslaveport  busPort  -loaddress [pciOffset 0x0070] -hiaddress [pciOffset 0x0071]
ihwconnect       -instancename mrtc -net intCtl_ir8 -netport       timerInt

#
# Uart0
#
ihwaddperipheral -instancename uartTTY0 -vendor national.ovpworld.org -library peripheral -version 1.0 -type 16550
ihwconnect       -instancename uartTTY0 -bus bus${mSys}       -busslaveport bport1   -loaddress [pciOffset 0x03f8] -hiaddress [pciOffset 0x03ff]
ihwconnect       -instancename uartTTY0 -net intCtl_ir4 -netport      intOut

#
# Uart1
#
ihwaddperipheral -instancename uartTTY1 -vendor national.ovpworld.org -library peripheral -version 1.0 -type 16550
ihwconnect       -instancename uartTTY1 -bus bus${mSys}       -busslaveport bport1   -loaddress [pciOffset 0x02f8] -hiaddress [pciOffset 0x02ff]
ihwconnect       -instancename uartTTY1 -net intCtl_ir3 -netport      intOut

#
# Uart CBUS
#
ihwaddperipheral -instancename uartCBUS -vendor mips.ovpworld.org -library peripheral -version 1.0 -type 16450C
ihwconnect       -instancename uartCBUS -bus bus${mSys}       -busslaveport bport1   -loaddress 0x1F000900 -hiaddress 0x1F00093F
ihwconnect       -instancename uartCBUS -net intCtl_ir3 -netport      intOut

#
# Floppy disk controller
#
ihwaddperipheral -instancename fd0 -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 82077AA
ihwconnect       -instancename fd0 -bus bus${mSys} -busslaveport bport1 -loaddress [pciOffset 0x03f0] -hiaddress [pciOffset 0x03f7]

#
# FPGA
#
ihwaddperipheral -instancename maltaFpga -vendor mips.ovpworld.org -library peripheral -version 1.0 -type MaltaFPGA 
ihwsetparameter    -handle maltaFpga -name stoponsoftreset  -value 1    -type bool
ihwconnect       -instancename maltaFpga -bus bus${mSys}       -busslaveport busPort1   -loaddress 0x1f000000 -hiaddress 0x1f0008ff
ihwconnect       -instancename maltaFpga -bus bus${mSys}       -busslaveport busPort2   -loaddress 0x1f000a00 -hiaddress 0x1f000fff

if {$cache == 1} {
  #
  # iCache attributes
  #
  ihwsetparameter -handle mipsle1 -name config1IS -value 2     -type uns32
  ihwsetparameter -handle mipsle1 -name config1IL -value 4     -type uns32
  ihwsetparameter -handle mipsle1 -name config1IA -value 3     -type uns32

  #
  # dCache attributes
  #
  ihwsetparameter -handle mipsle1 -name config1DS -value 2     -type uns32
  ihwsetparameter -handle mipsle1 -name config1DL -value 4     -type uns32
  ihwsetparameter -handle mipsle1 -name config1DA -value 3     -type uns32

  # Set non aliased D Cache
  ihwsetparameter -handle mipsle1 -name config7AR -value 1     -type bool

  #
  # extension libraries for L1 data and instruction caches
  #
  ihwaddextensionlibrary -instancename iCache -handle mipsle1 -type mips32L1Cache
  ihwaddextensionlibrary -instancename dCache -handle mipsle1 -type mips32L1Cache

  #
  # cache attributes
  #
  ihwsetparameter -handle mipsle1/iCache -name type -value instruction    -type enum
  ihwsetparameter -handle mipsle1/dCache -name type -value data           -type enum
}

