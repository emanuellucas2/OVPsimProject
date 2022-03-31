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

set platform MipsMalta
set cache 0

set connectusb 0
set connectvga 1

#
# Platform
#
ihwnew -name ${platform} -vendor mips.ovpworld.org -library module -version 1.0 -stoponctrlc -releasestatus ovp -visibility visible -purpose module

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "This is a platform representing a MIPS Malta development board.
    It provides the peripherals required to boot and run a Linux Operating System.
    A single MIPS32 architecture processor is instantiated in this platform.
    This instance could be duplicated to instantiate further processors to easily create an SMP platform.
    Attributes are provided for configuration of the generic ISA model for a specific processor.
    The processor model is configured to operate as a MIPS32 4KEc.

    The main SDRAM and Flash memory is modeled using RAM models. Both are initialised in places by the
    'SmartLoaderLinux'. The SmartLoaderLinux allows ease of use of changing kernel command lines,
    loading an initial ram disk and creating the boot flash(s). The operation of the SmartloaderLinux is configured
    using a number of attributes.  
       The kernel attribute of the SmartLoaderLinux and the imagefile of the processor must be consistent.

    NOTE: a non Mips Malta peripheral 'AlphaDisplay16x2' has been defined in this platform definition
          to be used for demo purposes. It should be removed if there is a memory error in the address space 0x18000100-0x18000103

    If this platform is not part of your installation, then it is available for download from www.OVPworld.org/ip-vendor-mips."

    iadddocumentation  \
    -name Limitations \
    -text "Verification has only been carried out using Little Endian memory ordering."

iadddocumentation  \
    -name Reference \
    -text "MIPS Malta User's Manual MD00048-2B-MALTA-USM-1.07.pdf
           MIPS Malta-R Development Platform User's Manual MD00627-2B-MALTA_R-USM-01.01.pdf    
           CoreFPGA User's Manual MD00116-2B-COREFPGA-USM-01.00.pdf
           Linux for the MIPS Malta Development Platform User's Guide MD00646-2B-LINUXMALTA-USM-01.03.pdf"

# formal parameter allows the main bus size to be modified (required to support 64-bit processors)
set mainBusAddressBits 32
ihwaddformalparameter -name addressbits  -defaultvalue ${mainBusAddressBits} -max 64 -min 32 -type uns32
iadddocumentation -name Description -text "Formal parameter addressbits allows the address bits for the main bus to be modified (default $mainBusAddressBits)"

# formal parameter allows the interrupt connection to the processor to be modified e.g use of direct interrupts or GIC
set intName "hwint0"
ihwaddformalparameter -name processorinterrupt -defaultvalue ${intName} -type string
iadddocumentation -name Description -text "Formal parameter processorinterrupt allows the interrupt pin used on the processor to be modified to select direct interrupts or GIC interrupts (default $intName)"

ihwaddnet -instancename intCtl_ir1
ihwaddnet -instancename intCtl_ir3
ihwaddnet -instancename intCtl_ir4
ihwaddnet -instancename intCtl_ir8
ihwaddnet -instancename intCtl_ir10
ihwaddnet -instancename intCtl_ir12
ihwaddnet -instancename intCtl_ir14
ihwaddnet -instancename intCtl_ir15

ihwaddnet -instancename i8259Int
ihwaddnet -instancename i8259Cascade

#
# main bus
#
ihwaddbus -instancename bus1 -addresswidth {addressbits}

#
# PCI bus default mapping base at
#
set pciBaseAddress 0x18000000

ihwaddbus -instancename busPCI -addresswidth 32

# The processor can see this PCI address space
ihwaddbridge -instancename pciBr
ihwconnect -bus bus1   -instancename pciBr -busslaveport  sp1 -loaddress 0x10000000 -hiaddress 0x1bffffff
ihwconnect -bus busPCI -instancename pciBr -busmasterport mp1 -loaddress 0x10000000 -hiaddress 0x1bffffff

# The PCI master devices see this main memory address space
ihwaddbridge -instancename pciMBr
ihwconnect -bus busPCI   -instancename pciMBr -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x0fffffff
ihwconnect -bus bus1     -instancename pciMBr -busmasterport mp1 -loaddress 0x00000000 -hiaddress 0x0fffffff

# Component remapping is performed for some PCI devices
ihwaddbus -instancename busPCIReMap -addresswidth 32

#
# Create a dynamic bridge instance between the busPCI and busPCIReMap 
# map the instance onto the bus busPCIReMap
#
proc addPCIConnectAndReMap { instancename port loaddress hiaddress } {

    global pciBaseAddress

    # and is performed with a Dynamic remapping instance by changing spLoAddress
    ihwaddperipheral -instancename pciBrD_${instancename}_${port} -type DynamicBridge -vendor ovpworld.org
    ihwconnect       -instancename pciBrD_${instancename}_${port} -bus busPCI      -busslaveport  "sp"
    ihwconnect       -instancename pciBrD_${instancename}_${port} -bus busPCIReMap -busmasterport "mp"
    set mappedloaddress [expr ${pciBaseAddress} + ${loaddress}]
    set mappedhiaddress [expr ${pciBaseAddress} + ${hiaddress}]
    set size            [expr (${hiaddress} +1) - ${loaddress}]
    ihwsetparameter    -handle pciBrD_${instancename}_${port} -name spLoAddress  -value ${mappedloaddress} -type uns64
    ihwsetparameter    -handle pciBrD_${instancename}_${port} -name mpLoAddress  -value ${mappedloaddress} -type uns64
    ihwsetparameter    -handle pciBrD_${instancename}_${port} -name portSize     -value ${size} -type uns64
    ihwsetparameter    -handle pciBrD_${instancename}_${port} -name enableBridge -value 1       -type bool
    ihwconnect -instancename  ${instancename} -bus busPCIReMap -busslaveport ${port} -loaddress ${mappedloaddress} -hiaddress ${mappedhiaddress}
}

ihwaddbus -instancename PCIconfigBus -addresswidth 16

#
# 1-word connection to interrupt controller
#
ihwaddbus -instancename PCIackBus    -addresswidth 0

#
# interrupt controller master to slave
#
ihwaddbus -instancename cascadeBus   -addresswidth 3

#
# main processor
#
ihwaddprocessor -instancename mipsle1 -type mips32_r1r5 -library processor -vendor mips.ovpworld.org -endian little -simulateexceptions -mips 100.0

#
# processor (default) attributes
#
ihwsetparameter -handle mipsle1 -name variant           -value 34Kc -type enum
ihwsetparameter -handle mipsle1 -name vectoredinterrupt -value 0    -type bool
ihwsetparameter -handle mipsle1 -name config1MMUSizeM1  -value 63   -type uns32

#
# Connect processor to bus
#
ihwconnect -bus bus1 -instancename mipsle1 -busmasterport INSTRUCTION
ihwconnect -bus bus1 -instancename mipsle1 -busmasterport DATA

# interrupt to processor from interrupt controller
ihwconnect -net i8259Int -instancename mipsle1 -netport {processorinterrupt}

#
# SDRAM
#
ihwaddmemory -instancename Core_Board_SDRAM  -type ram
ihwconnect -bus bus1 -instancename Core_Board_SDRAM -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0fffffff
ihwaddmemory -instancename Core_Board_SDRAM2  -type ram
ihwconnect -bus bus1 -instancename Core_Board_SDRAM2 -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0x5fffffff

#
# smart PROM device
#
ihwaddperipheral     -instancename Core_Board_SDRAM_promInit -vendor mips.ovpworld.org -library peripheral -version 1.0 -type SmartLoaderLinux
ihwconnect -bus bus1 -instancename Core_Board_SDRAM_promInit -busmasterport mport  -loaddress 0x0 -hiaddress 0xffffffff
ihwconnect -bus bus1 -instancename Core_Board_SDRAM_promInit -busslaveport idport  -loaddress 0x1fc00010 -hiaddress 0x1fc00013

#
# Flash Memory and mapping
#
ihwaddbus    -instancename flashBus -addresswidth 32
ihwaddmemory -instancename Monitor_Flash -type ram
ihwconnect   -instancename Monitor_Flash -bus flashBus -busslaveport sp1 -loaddress 0x1e000000 -hiaddress 0x1e3fffff

# Map flash onto main bus at 0x1e000000
ihwaddbridge -instancename map
ihwconnect -bus bus1     -instancename map -busslaveport sp1 -loaddress 0x1e000000 -hiaddress 0x1e3fffff
ihwconnect -bus flashBus -instancename map -busmasterport mp1 -loaddress 0x1e000000 -hiaddress 0x1e3fffff

# Map flash onto main bus at 0x1fc00000 except the boardId at 0x1fc00010
ihwaddbridge -instancename remap1
ihwaddbridge -instancename remap2

ihwconnect -bus bus1     -instancename remap1 -busslaveport  sp1 -loaddress 0x1fc00000 -hiaddress 0x1fc0000F
ihwconnect -bus flashBus -instancename remap1 -busmasterport mp1 -loaddress 0x1e000000 -hiaddress 0x1e00000f
ihwconnect -bus bus1     -instancename remap2 -busslaveport  sp1 -loaddress 0x1fc00014 -hiaddress 0x1fffffff
ihwconnect -bus flashBus -instancename remap2 -busmasterport mp1 -loaddress 0x1e000014 -hiaddress 0x1e3fffff

#
# system controller
#
ihwaddperipheral -instancename sysControl -vendor marvell.ovpworld.org -library peripheral -version 1.0 -type GT6412x
ihwconnect -bus busPCI         -instancename sysControl -busslaveport  busPort

ihwconnect -bus PCIconfigBus -instancename sysControl -busmasterport PCIconfigM
ihwconnect -bus PCIconfigBus -instancename sysControl -busslaveport PCIconfig

ihwconnect -bus PCIackBus    -instancename sysControl -busmasterport PCIackM

# PCI base
ihwaddperipheral -instancename PIIX4 -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 82371EB
ihwconnect       -instancename PIIX4 -busslaveport PCIconfig  -bus PCIconfigBus
ihwsetparameter    -handle PIIX4       -name PCIslot -value 10 -type uns32

#
# IDE
#
ihwaddperipheral -instancename PIIX4-IDE -vendor intel.ovpworld.org -library peripheral -version 1.0 -type PciIDE
ihwsetparameter -handle PIIX4-IDE -name PCIslot     -value 10 -type uns32
ihwsetparameter -handle PIIX4-IDE -name PCIfunction -value 1  -type uns32

ihwconnect -bus PCIconfigBus -instancename PIIX4-IDE -busslaveport  PCIconfig
ihwconnect -bus busPCI       -instancename PIIX4-IDE -busslaveport  busPort
ihwconnect -bus busPCI       -instancename PIIX4-IDE -busmasterport dmaPort

ihwconnect -net intCtl_ir14 -instancename PIIX4-IDE -netport intOut0
ihwconnect -net intCtl_ir15 -instancename PIIX4-IDE -netport intOut1

#
# USB
#
if {${connectusb}} {
    ihwaddperipheral -instancename PCI_USB -vendor intel.ovpworld.org -library peripheral -version 1.0 -type PciUSB
    ihwsetparameter    -handle       PCI_USB -name PCIslot     -value 10 -type uns32
    ihwsetparameter    -handle       PCI_USB -name PCIfunction -value 2  -type uns32
    
    ihwconnect -bus PCIconfigBus -instancename PCI_USB -busslaveport  PCIconfig
    ihwconnect -bus busPCI         -instancename PCI_USB -busslaveport  busPort
}
#
# Power Manager
#
ihwaddperipheral -instancename PCI_PM -vendor intel.ovpworld.org -library peripheral -version 1.0 -type PciPM
ihwsetparameter -handle PCI_PM -name PCIslot     -value 10 -type uns32
ihwsetparameter -handle PCI_PM -name PCIfunction -value 3  -type uns32

ihwconnect -bus PCIconfigBus -instancename PCI_PM -busslaveport  PCIconfig
ihwconnect -bus busPCI         -instancename PCI_PM -busslaveport  busPort

#
# Network
#
ihwaddperipheral -instancename PCI_NET -vendor amd.ovpworld.org -library peripheral -version 1.0 -type 79C970
ihwsetparameter -handle PCI_NET -name PCIslot     -value 11   -type uns32
ihwsetparameter -handle PCI_NET -name PCIfunction -value 0    -type uns32

ihwconnect -bus PCIconfigBus   -instancename PCI_NET -busslaveport  PCIconfig
ihwconnect -bus busPCI         -instancename PCI_NET -busslaveport  busPort
ihwconnect -bus busPCI         -instancename PCI_NET -busmasterport dmaPort

ihwconnect -net intCtl_ir10  -instancename PCI_NET -netport       intOut0

#
# Interrupt controller Master
#
ihwaddperipheral -instancename intCtrlMaster -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 8259A
addPCIConnectAndReMap intCtrlMaster io 0x0020 0x0021
#connectFixedPCI intCtrlMaster io 0x0020 0x0021
addPCIConnectAndReMap intCtrlMaster elcr 0x04d0 0x04d0
#connectFixedPCI intCtrlMaster elcr 0x04d0 0x04d0
ihwconnect -bus cascadeBus -instancename intCtrlMaster  -busmasterport cascade
ihwconnect -bus PCIackBus -instancename intCtrlMaster   -busslaveport  PCIackS -loaddress 0                  -hiaddress 0

ihwconnect -net i8259Int     -instancename intCtrlMaster -netport       intp
#ihwconnect -net intCtl_ir0   -instancename intCtrlMaster -netport       ir0
ihwconnect -net intCtl_ir1   -instancename intCtrlMaster -netport       ir1
ihwconnect -net i8259Cascade -instancename intCtrlMaster -netport       ir2
ihwconnect -net intCtl_ir3   -instancename intCtrlMaster -netport       ir3
ihwconnect -net intCtl_ir4   -instancename intCtrlMaster -netport       ir4

ihwsetparameter -handle intCtrlMaster -name spen -value master    -type enum

#
# Interrupt controller Slave
#
ihwaddperipheral -instancename intCtrlSlave -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 8259A
addPCIConnectAndReMap intCtrlSlave   io      0x00a0 0x00a1
addPCIConnectAndReMap intCtrlSlave   elcr    0x04d1 0x04d1
ihwconnect -bus cascadeBus -instancename intCtrlSlave   -busslaveport  PCIackS -loaddress 2          -hiaddress 2

ihwconnect -net intCtl_ir8   -instancename intCtrlSlave -netport       ir0
ihwconnect -net intCtl_ir10  -instancename intCtrlSlave -netport       ir2
#
# Add keyboard interrupt
#
ihwconnect -net intCtl_ir12  -instancename intCtrlSlave -netport       ir4

ihwconnect -net intCtl_ir14  -instancename intCtrlSlave -netport       ir6
ihwconnect -net intCtl_ir15  -instancename intCtrlSlave -netport       ir7
ihwconnect -net i8259Cascade -instancename intCtrlSlave -netport       intp

ihwsetparameter -handle intCtrlSlave -name spen -value slave    -type enum

ihwaddperipheral -instancename _SUPERIO_REG_ -type SerInt  -vendor ovpworld.org
addPCIConnectAndReMap _SUPERIO_REG_ bport1 0xb0 0xb3

#
# VGA
#
if {${connectvga}} {
    ihwaddperipheral -instancename vga -vendor cirrus.ovpworld.org -library peripheral -version 1.0 -type GD5446
    ihwsetparameter -handle vga -name scanDelay -value 50000 -type uns32
    ihwsetparameter -handle vga -name PCIslot   -value 18    -type uns32
    ihwsetparameter -handle vga -name title     -value "Imperas MIPS32 Malta"   -type string
    
    ihwconnect -bus PCIconfigBus -instancename vga -busslaveport  PCIconfig
    addPCIConnectAndReMap vga config    0x03b0 0x03df
    ihwconnect -bus busPCI         -instancename vga -busslaveport  memory
    
    # insert VGA Default (inert) memory
    ihwaddmemory -instancename vgaMemRegion -type rom
    ihwconnect -bus busPCI -instancename vgaMemRegion -busslaveport sp1 -loaddress 0x100a0000 -hiaddress 0x100bffff
}

#
# ps2if
#
ihwaddperipheral -instancename ps2if -vendor intel.ovpworld.org -library peripheral -version 1.0 -type Ps2Control
ihwsetparameter    -handle       ps2if -name pollPeriod   -value 50000 -type uns32
ihwsetparameter    -handle       ps2if -name grabDisable  -value 1     -type bool

addPCIConnectAndReMap ps2if config  0x0060 0x0067
#
# Add keyboard/mouse interrupt
#
ihwconnect       -instancename ps2if -net intCtl_ir1  -netport  kbdInterrupt
ihwconnect       -instancename ps2if -net intCtl_ir12 -netport  mouseInterrupt

#
# Programmable Interval Timer
#
ihwaddperipheral -instancename  pit -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 8253
addPCIConnectAndReMap pit bport1 0x0040 0x0043
#ihwconnect       -instancename  pit -net intCtl_ir0 -netport out0

#
# RTC
#
ihwaddperipheral -instancename rtc -vendor motorola.ovpworld.org -library peripheral -version 1.0 -type MC146818
addPCIConnectAndReMap rtc busPort  0x0070 0x0071
ihwconnect       -instancename rtc -net intCtl_ir8 -netport       timerInt

#
# Uart0
#
ihwaddperipheral -instancename uartTTY0 -vendor national.ovpworld.org -library peripheral -version 1.0 -type 16550
ihwsetparameter    -handle       uartTTY0 -name outfile            -value uartTTY0.log     -type string
ihwsetparameter    -handle       uartTTY0 -name finishOnDisconnect -value 1                -type bool
addPCIConnectAndReMap uartTTY0 bport1   0x03f8 0x03ff
ihwconnect       -instancename uartTTY0 -net intCtl_ir4 -netport      intOut

#
# Uart1
#
ihwaddperipheral -instancename uartTTY1 -vendor national.ovpworld.org -library peripheral -version 1.0 -type 16550
ihwsetparameter    -handle       uartTTY1 -name outfile            -value uartTTY1.log  -type string
ihwsetparameter    -handle       uartTTY1 -name finishOnDisconnect -value 1              -type bool
addPCIConnectAndReMap uartTTY1 bport1   0x02f8 0x02ff
ihwconnect       -instancename uartTTY1 -net intCtl_ir3 -netport      intOut

#
# Floppy disk controller
#
ihwaddperipheral -instancename fd0 -vendor intel.ovpworld.org -library peripheral -version 1.0 -type 82077AA
addPCIConnectAndReMap fd0 bport1 0x03f0 0x03f7

#
# Uart CBUS
#
ihwaddperipheral -instancename uartCBUS -vendor mips.ovpworld.org -library peripheral -version 1.0 -type 16450C
ihwsetparameter    -handle       uartCBUS -name outfile            -value uartCBUS.log     -type string
ihwconnect       -instancename uartCBUS -bus bus1       -busslaveport bport1   -loaddress 0x1F000900 -hiaddress 0x1F00093F

#
# FPGA
#
ihwaddperipheral -instancename maltaFpga -vendor mips.ovpworld.org -library peripheral -version 1.0 -type MaltaFPGA
ihwsetparameter    -handle       maltaFpga -name stoponsoftreset  -value 1 -type bool
ihwconnect       -instancename maltaFpga -bus bus1       -busslaveport busPort1   -loaddress 0x1f000000 -hiaddress 0x1f0008ff
ihwconnect       -instancename maltaFpga -bus bus1       -busslaveport busPort2   -loaddress 0x1f000a00 -hiaddress 0x1f000fff


# ALias high 2GB of bus to low 2GB (Expected by Linux kernel with EVA configured)
ihwaddbridge -instancename high2low
ihwconnect -instancename high2low -bus bus1  -busslaveport  sp1 -loaddress 0x80000000 -hiaddress 0xffffffff
ihwconnect -instancename high2low -bus bus1  -busmasterport mp1 -loaddress 0x00000000 -hiaddress 0x7fffffff
# NOTE: This should really be done between separate busses so that a SystemC platform can be generated

##########################################################################################################################
#
# Non Mips Malta Peripheral
# This peripheral device is added to the Mips Malta platform definition for demo purposes
# It should be removed if there is a memory clash
# AlphaDisplay16x2
#
ihwaddperipheral -instancename alphaDisplay -type Alpha2x16Display   -vendor ovpworld.org
addPCIConnectAndReMap alphaDisplay busPort   0x0100 0x0103

##########################################################################################################################

