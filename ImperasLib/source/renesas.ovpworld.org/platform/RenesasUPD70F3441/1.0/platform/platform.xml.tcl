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

ihwnew \
       -name RenesasUPD70F3441  \
       -vendor renesas.ovpworld.org  \
       -library platform  \
       -version 1.0 \
       -stoponctrlc \
       -purpose epk -releasestatus ovp

       
# Add argument parser
ihwaddclp -allargs

iadddocumentation -name Licensing -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "The Renesas uPD70F3441 - V850/PHO3 platform"
iadddocumentation -name Limitations -text "Limitiations of peripheral functionality is documented within the peripheral component.
Unimplemented Components:
    System Controller
    Standby Controller
    Bus Control Unit
    Memory Controller
    CAN Controller
    FlexRay
    I/O Ports
    CPU-CRC
    DATA-CRC
    On-chip Debug Unit
    NBD
Partially Implemented Components (not complete - only certain modes or features modeled or tested)
    DMA
"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

proc bridgeMem {bus mem alias size} {
    set name bridge_${bus}_${mem}_${alias}
    ihwaddbridge -instancename ${name}
    ihwconnect   -instancename ${name} -bus ${bus} -busslaveport  sp -loaddress ${alias} -hiaddress [expr ${alias} + ${size} - 1]
    ihwconnect   -instancename ${name} -bus ${bus} -busmasterport mp -loaddress ${mem}   -hiaddress [expr ${mem}   + ${size} - 1]
}

#
# PCLK0 = 32Mhz, each subsequent clock is divide by 2
#
set PCLK(0) [expr int(pow(2,25))]
set t $PCLK(0)
for {set c 1} {$c <= 9} {incr c} {
    set t [expr $t / 2]
    set PCLK($c) $t
}

proc addConnectNet {instance port net } {
    ihwaddnet  -instancename ${net}
    ihwconnect -net          ${net} -instancename ${instance} -netport ${port}
}

#################################################################
# Processor V850ES - 28 bit bus causes mirroring at 0x*0000000
#################################################################
ihwaddprocessor -instancename CPU -type v850 -mips 128 -variant V850ES -vendor renesas.ovpworld.org -library processor -enableintercepts
ihwaddbus -instancename vfb -addresswidth 28
ihwaddpacketnet -instancename vcan0
ihwaddpacketnet -instancename vcan1

#ihwaddbus -instancename vdb -addresswidth 28
#ihwaddbus -instancename vsb -addresswidth 28
#ihwaddbus -instancename npb -addresswidth 28

ihwconnect -instancename CPU -bus vfb       -busmasterport INSTRUCTION
ihwconnect -instancename CPU -bus vfb       -busmasterport DATA
addConnectNet CPU reset  INTRESET
addConnectNet CPU nmi0   INTNMI
addConnectNet CPU intp   INTINTP
addConnectNet CPU mireti INTMIRETI
addConnectNet CPU intack INTINTACK

#################################################################
# Platform Logic
#################################################################
ihwaddperipheral -instancename LOGIC -vendor renesas.ovpworld.org -library peripheral -type UPD70F3441Logic -version 1.0
ihwconnect       -instancename LOGIC -bus vfb -busslaveport LOGICP0 -loaddress 0x0ffff6d0 -hiaddress 0x0ffff6d3
ihwconnect       -instancename LOGIC -bus vfb -busslaveport LOGICP1 -loaddress 0x0ffff400 -hiaddress 0x0ffff475
ihwconnect       -instancename LOGIC -bus vfb -busslaveport LOGICP2 -loaddress 0x0ffff888 -hiaddress 0x0ffff893
ihwconnect       -instancename LOGIC -bus vfb -busslaveport LOGICP3 -loaddress 0x0ffff1fc -hiaddress 0x0ffff1fc

#ihwconnect       -instancename LOGIC -netport NMIIN    -net PIN_NMIIN  
#ihwconnect       -instancename LOGIC -netport INTDEDF  -net INTDEDF
#ihwconnect       -instancename LOGIC -netport INTDEDR  -net INTDEDR
#ihwconnect       -instancename LOGIC -netport INTDEDFR -net INTDEDFR
#ihwconnect       -instancename LOGIC -netport INTOSD   -net INTOSD
addConnectNet LOGIC NMIOUT   INTNMI0
addConnectNet LOGIC INT0     INTINT0
addConnectNet LOGIC INT1     INTINT1

#ihwconnect       -instancename LOGIC -netport INTP4
addConnectNet LOGIC INTUC0R  INTUC0R
addConnectNet LOGIC INT6     INTINT6

#ihwconnect       -instancename LOGIC -netport INTP5
addConnectNet LOGIC INTUC1R  INTUC1R
addConnectNet LOGIC INT7     INTINT7

addConnectNet LOGIC INTBRG0  INTBRG0
addConnectNet LOGIC INTBRG1  INTBRG1 
addConnectNet LOGIC INT75    INTINT75

addConnectNet LOGIC INTCB0T  INTCB0T
addConnectNet LOGIC INTUC2T  INTUC2T
addConnectNet LOGIC INT99    INTINT99

addConnectNet LOGIC INTCB0R  INTCB0R
addConnectNet LOGIC INTUC2R  INTUC2R
#addConnectNet LOGIC -netport INTP13 
addConnectNet LOGIC INT100   INTINT100

addConnectNet LOGIC INTCB0RE INTCB0RE
addConnectNet LOGIC INTUC2RE INTUC2RE
addConnectNet LOGIC INT101   INTINT101

#ihwconnect       -instancename LOGIC -netport INTDMA3 
#ihwconnect       -instancename LOGIC -netport INTFL
addConnectNet LOGIC INT116   INTINT116

#################################################################
# Interrupt Controller
#################################################################
ihwaddperipheral -instancename INTC -vendor renesas.ovpworld.org -library peripheral -type intc -version 1.0
ihwconnect       -instancename INTC -bus vfb -busslaveport INTCP0 -loaddress 0x0ffff100 -hiaddress 0x0ffff1fb

# Internal Pin Connections
ihwconnect -instancename INTC -netport RESET  -net INTRESET  
ihwconnect -instancename INTC -netport NMI0   -net INTNMI   
ihwconnect -instancename INTC -netport INTP   -net INTINTP   
ihwconnect -instancename INTC -netport MIRETI -net INTMIRETI 
ihwconnect -instancename INTC -netport INTACK -net INTINTACK 

# Inputs to INTC
ihwconnect -instancename INTC -netport NMI_00 -net INTNMI0

ihwconnect -instancename INTC -netport INT_00 -net INTINT0
ihwconnect -instancename INTC -netport INT_01 -net INTINT1
# INTP0,3
ihwconnect -instancename INTC -netport INT_06 -net INTINT6
ihwconnect -instancename INTC -netport INT_07 -net INTINT7
# INTP6,12
addConnectNet INTC INT_15  INTTS0OV
addConnectNet INTC INT_16  INTTS0CC0
addConnectNet INTC INT_17  INTTS0CC1
addConnectNet INTC INT_18  INTTS0CC2
addConnectNet INTC INT_19  INTTS0CC3
addConnectNet INTC INT_20  INTTS0CC4
addConnectNet INTC INT_21  INTTS0CC5
addConnectNet INTC INT_22  INTTS0CD0
addConnectNet INTC INT_23  INTTS0OD
addConnectNet INTC INT_24  INTTS0ER
addConnectNet INTC INT_25  INTTS0WN
addConnectNet INTC INT_26  INTTS1OV
addConnectNet INTC INT_27  INTTS1CC0
addConnectNet INTC INT_28  INTTS1CC1
addConnectNet INTC INT_29  INTTS1CC2
addConnectNet INTC INT_30  INTTS1CC3
addConnectNet INTC INT_31  INTTS1CC4
addConnectNet INTC INT_32  INTTS1CC5
addConnectNet INTC INT_33  INTTS1CD0
addConnectNet INTC INT_34  INTTS1OD
addConnectNet INTC INT_35  INTTS1ER
addConnectNet INTC INT_36  INTTS1WN
addConnectNet INTC INT_37  INTTT0OV
addConnectNet INTC INT_38  INTTT0CC0
addConnectNet INTC INT_39  INTTT0CC1
addConnectNet INTC INT_40  INTTT0EC
addConnectNet INTC INT_41  INTTT1OV
addConnectNet INTC INT_42  INTTT1CC0
addConnectNet INTC INT_43  INTTT1CC1
addConnectNet INTC INT_44  INTTT1EC
addConnectNet INTC INT_45  INTTAA0OV
addConnectNet INTC INT_46  INTTAA0CC0
addConnectNet INTC INT_47  INTTAA0CC1
addConnectNet INTC INT_48  INTTAA1OV
addConnectNet INTC INT_49  INTTAA1CC0
addConnectNet INTC INT_50  INTTAA1CC1
addConnectNet INTC INT_51  INTTAA2OV
addConnectNet INTC INT_52  INTTAA2CC0
addConnectNet INTC INT_53  INTTAA2CC1
addConnectNet INTC INT_54  INTTAA3OV
addConnectNet INTC INT_55  INTTAA3CC0
addConnectNet INTC INT_56  INTTAA3CC1
addConnectNet INTC INT_57  INTTAA4OV
addConnectNet INTC INT_58  INTTAA4CC0
addConnectNet INTC INT_59  INTTAA4CC1
addConnectNet INTC INT_60  INTTAA5OV
addConnectNet INTC INT_61  INTTAA5CC0
addConnectNet INTC INT_62  INTTAA5CC1
addConnectNet INTC INT_63  INTTAA6OV
addConnectNet INTC INT_64  INTTAA6CC0
addConnectNet INTC INT_65  INTTAA6CC1
addConnectNet INTC INT_66  INTTAA7OV
addConnectNet INTC INT_67  INTTAA7CC0
addConnectNet INTC INT_68  INTTAA7CC1
addConnectNet INTC INT_69  INTTAA8OV
addConnectNet INTC INT_70  INTTAA8CC0
addConnectNet INTC INT_71  INTTAA8CC1
addConnectNet INTC INT_72  INTTAA9OV
addConnectNet INTC INT_73  INTTAA9CC0
addConnectNet INTC INT_74  INTTAA9CC1
ihwconnect -instancename INTC -netport INT_75  -net INTINT75
addConnectNet INTC INT_76  INTBRG2
# Flexray
addConnectNet INTC INT_83  INTC0ERR
addConnectNet INTC INT_84  INTC0WUPIC
addConnectNet INTC INT_85  INTC0REC
addConnectNet INTC INT_86  INTC0TRX
addConnectNet INTC INT_87  INTC1ERR
addConnectNet INTC INT_88  INTC1WUPIC
addConnectNet INTC INT_89  INTC1REC
addConnectNet INTC INT_90  INTC1TRX
# TMS0,1
ihwconnect -instancename INTC -netport INT_99  -net INTINT99
ihwconnect -instancename INTC -netport INT_100 -net INTINT100
ihwconnect -instancename INTC -netport INT_101 -net INTINT101
addConnectNet INTC INT_102 INTCB1T
addConnectNet INTC INT_103 INTCB1R
addConnectNet INTC INT_104 INTCB1RE
# CSIE0,1
addConnectNet INTC INT_109 INTUC0RE
addConnectNet INTC INT_110 INTUC0T
addConnectNet INTC INT_111 INTUC1RE
addConnectNet INTC INT_112 INTUC1T
addConnectNet INTC INT_113 INTAD0
addConnectNet INTC INT_114 INTAD1
# DMA
ihwconnect -instancename INTC -netport INT_116 -net INTINT116

# External Pin Connections
###ihwconnect       -instancename INTC -net N_IRESET -netport IRESET
###ihwconnect       -instancename INTC -net NMI      -netport NMI_00
###ihwconnect       -instancename INTC -net INTDEDF  -netport NMI_01

#################################################################
############################## crc ##############################
#################################################################
ihwaddperipheral -instancename CRC -vendor renesas.ovpworld.org -library peripheral -type crc -version 1.0
ihwconnect       -instancename CRC -bus vfb -busslaveport CRCP0 -loaddress 0x0fe00000 -hiaddress 0x0fe0007f

#################################################################
# Clock Generator
#################################################################
ihwaddperipheral -instancename CLKGEN -vendor renesas.ovpworld.org -library peripheral -type clkgen -version 1.0
ihwconnect       -instancename CLKGEN -bus vfb -busslaveport CLKGENP0 -loaddress 0x0ffff860 -hiaddress 0x0ffff860
ihwconnect       -instancename CLKGEN -bus vfb -busslaveport CLKGENP1 -loaddress 0x0ffffca0 -hiaddress 0x0ffffca0

#################################################################
# Flash Memory
#################################################################
set rom ram
ihwaddmemory -instancename CodeFlash -type $rom
ihwconnect   -instancename CodeFlash -bus vfb -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x000F7FFF
ihwaddmemory -instancename DataFlash -type ram
ihwconnect   -instancename DataFlash -bus vfb -busslaveport sp1 -loaddress 0x03E00000 -hiaddress 0x03E07FFF

#################################################################
# Internal Ram 60Kb at 0x03FF0000 - 0x03FFEFFF
# Mirrored at          0x0FFF0000 - 0x0FFFEFFF
#################################################################
ihwaddmemory -instancename iRam      -type ram
ihwconnect   -instancename iRam      -bus vfb -busslaveport sp1 -loaddress 0x03FF0000 -hiaddress 0x03FFEFFF
bridgeMem vfb 0x03FF0000 0x0FFF0000 0xF000

#################################################################
# Data Protection and Security - TBD
#################################################################

#################################################################
# Bus and Memory Control
#################################################################
ihwaddperipheral -instancename BCU -vendor renesas.ovpworld.org -library peripheral -type bcu -version 1.0
ihwconnect       -instancename BCU -bus vfb -busslaveport BCUP0 -loaddress 0x0ffff060 -hiaddress 0x0ffff06f
ihwaddperipheral -instancename MEMC -vendor renesas.ovpworld.org -library peripheral -type memc -version 1.0
ihwconnect       -instancename MEMC -bus vfb -busslaveport MEMCP0 -loaddress 0x0ffff480 -hiaddress 0x0ffff48f

#################################################################
# DMA Functions
#################################################################
ihwaddperipheral -instancename DMA -vendor renesas.ovpworld.org -library peripheral -type dma -version 1.0
ihwconnect       -instancename DMA -bus vfb -busslaveport DMAP0 -loaddress 0x0ffffe00 -hiaddress 0x0ffffe0f
ihwconnect       -instancename DMA -bus vfb -busslaveport DMAP1 -loaddress 0x0ffff300 -hiaddress 0x0ffff3ff
ihwconnect       -instancename DMA -bus vfb -busmasterport DMAPM

ihwconnect       -instancename DMA -netport INTDMA0 -net INTAD0
ihwconnect       -instancename DMA -netport INTDMA1 -net INTAD1
addConnectNet DMA DMA0EN  DMA0EN
addConnectNet DMA DMA1EN  DMA1EN

addConnectNet DMA ADDMARQ0 ADDMARQ0
addConnectNet DMA ADDMARQ1 ADDMARQ1

#ihwconnect       -instancename DMA -netport INTTS0CD  -net INTTS0CD
#ihwconnect       -instancename DMA -netport INTTS1CD  -net INTTS1CD
#ihwconnect       -instancename DMA -netport INTCE0C   -net INTCE0C
#ihwconnect       -instancename DMA -netport INTCE1C   -net INTCE1C
#ihwconnect       -instancename DMA -netport INTBE0R   -net INTBE0R
#ihwconnect       -instancename DMA -netport INTBE1R   -net INTBE1R
ihwconnect       -instancename DMA -netport INTUC0R   -net INTUC0R
ihwconnect       -instancename DMA -netport INTUC1R   -net INTUC1R
ihwconnect       -instancename DMA -netport INTUC2R   -net INTUC2R

#################################################################
# Asynchronous Serial Interface
#################################################################
ihwaddperipheral -instancename UARTC0 -vendor renesas.ovpworld.org -library peripheral -type uartc -version 1.0
ihwconnect       -instancename UARTC0 -bus vfb -busslaveport UARTP0 -loaddress 0x0ffffa00 -hiaddress 0x0ffffa0f
ihwconnect       -instancename UARTC0 -netport INTUCT  -net INTUC0T
ihwconnect       -instancename UARTC0 -netport INTUCR  -net INTUC0R
ihwconnect       -instancename UARTC0 -netport INTUCRE -net INTUC0RE
ihwaddperipheral -instancename UARTC1 -vendor renesas.ovpworld.org -library peripheral -type uartc -version 1.0
ihwconnect       -instancename UARTC1 -bus vfb -busslaveport UARTP0 -loaddress 0x0ffffa20 -hiaddress 0x0ffffa2f
ihwconnect       -instancename UARTC1 -netport INTUCT  -net INTUC1T
ihwconnect       -instancename UARTC1 -netport INTUCR  -net INTUC1R
ihwconnect       -instancename UARTC1 -netport INTUCRE -net INTUC1RE
ihwaddperipheral -instancename UARTC2 -vendor renesas.ovpworld.org -library peripheral -type uartc -version 1.0
ihwconnect       -instancename UARTC2 -bus vfb -busslaveport UARTP0 -loaddress 0x0ffffa40 -hiaddress 0x0ffffa4f
ihwconnect       -instancename UARTC2 -netport INTUCT  -net INTUC2T
ihwconnect       -instancename UARTC2 -netport INTUCR  -net INTUC2R
ihwconnect       -instancename UARTC2 -netport INTUCRE -net INTUC2RE
#
# PCLK connections
#
foreach i {0 1 2 } {
    foreach c {0 1 2 3 4 5 7 9} {
        ihwsetparameter -handle UARTC${i} -name PCLK${c} -value $PCLK($c) -type uns32
    }
    ihwsetparameter -handle UARTC${i} -name console            -value 1  -type bool
    ihwsetparameter -handle UARTC${i} -name finishOnDisconnect -value 1  -type bool
}
#################################################################
# Clocked Serial Interface
#################################################################
ihwaddperipheral -instancename CSIB0 -vendor renesas.ovpworld.org -library peripheral -type csib -version 1.0
ihwconnect       -instancename CSIB0 -bus vfb -busslaveport CSIBP0 -loaddress 0x0ffffd00 -hiaddress 0x0ffffd07
ihwconnect       -instancename CSIB0 -netport INTCBT  -net INTCB0T
ihwconnect       -instancename CSIB0 -netport INTCBR  -net INTCB0R
ihwconnect       -instancename CSIB0 -netport INTCBRE -net INTCB0RE

ihwaddperipheral -instancename CSIB1 -vendor renesas.ovpworld.org -library peripheral -type csib -version 1.0
ihwconnect       -instancename CSIB1 -bus vfb -busslaveport CSIBP0 -loaddress 0x0ffffd20 -hiaddress 0x0ffffd27
ihwconnect       -instancename CSIB1 -netport INTCBT  -net INTCB1T
ihwconnect       -instancename CSIB1 -netport INTCBR  -net INTCB1R
ihwconnect       -instancename CSIB1 -netport INTCBRE -net INTCB1RE
#
# PCLK connections
#
foreach i {0 1 } {
    foreach c {1 2 3 4 5 6} {
        ihwsetparameter -handle CSIB${i} -name PCLK${c} -value $PCLK($c)   -type uns32
    }
}
#################################################################
# Enhanced Queued Clocked Serial Interface
#################################################################
ihwaddperipheral -instancename CSIE0 -vendor renesas.ovpworld.org -library peripheral -type csie -version 1.0
ihwconnect       -instancename CSIE0 -bus vfb -busslaveport CSIEP0 -loaddress 0x0ffffd40 -hiaddress 0x0ffffd5f
ihwsetparameter    -handle       CSIE0 -name PCLK0 -value $PCLK(0)      -type uns32

ihwaddperipheral -instancename CSIE1 -vendor renesas.ovpworld.org -library peripheral -type csie -version 1.0
ihwconnect       -instancename CSIE1 -bus vfb -busslaveport CSIEP0 -loaddress 0x0ffffd80 -hiaddress 0x0ffffd9f
ihwsetparameter    -handle       CSIE1 -name PCLK0 -value $PCLK(0)      -type uns32

#################################################################
# CAN Controller
#################################################################
#
# PBA                                          = 08400000
# C0RBaseAddr CAN0 Registers       - PBA + 000 = 08400000
# C0MBaseAddr CAN0 Message Buffers - PBA + 100 = 08400100
# C1RBaseAddr CAN1 Registers       - PBA + 600 = 08400600
# C1MBaseAddr CAN1 Message Buffers - PBA + 700 = 08400700
#
set PBA  0x08400000
set C0RB [expr $PBA + 0x000]
set C0MB [expr $PBA + 0x100]
ihwaddperipheral -instancename CAN0 -vendor renesas.ovpworld.org -library peripheral -type can -version 1.0
ihwconnect       -instancename CAN0 -bus vfb -busslaveport busPortGR -loaddress $C0RB -hiaddress [expr $C0MB - 1]
ihwconnect       -instancename CAN0 -packetnetport CAN    -packetnet vcan0 
ihwconnect       -instancename CAN0 -netport       INTERR -net       INTC0ERR  
ihwconnect       -instancename CAN0 -netport       INTREC -net       INTC0REC
ihwconnect       -instancename CAN0 -netport       INTTRX -net       INTC0TRX  
ihwconnect       -instancename CAN0 -netport       INTWUP -net       INTC0WUPIC  

set C1RB [expr $PBA + 0x600]
set C1MB [expr $PBA + 0x700]
ihwaddperipheral -instancename CAN1 -vendor renesas.ovpworld.org -library peripheral -type can -version 1.0
ihwconnect       -instancename CAN1 -bus vfb -busslaveport busPortGR -loaddress $C1RB -hiaddress [expr $C1MB - 1]
ihwconnect       -instancename CAN1 -packetnetport CAN    -packetnet vcan0     
ihwconnect       -instancename CAN1 -netport       INTERR -net       INTC0ERR  
ihwconnect       -instancename CAN1 -netport       INTREC -net       INTC0REC
ihwconnect       -instancename CAN1 -netport       INTTRX -net       INTC0TRX  
ihwconnect       -instancename CAN1 -netport       INTWUP -net       INTC0WUPIC  

#################################################################
# A/D Converter
#################################################################
ihwaddperipheral -instancename ADC0 -vendor renesas.ovpworld.org -library peripheral -type adc -version 1.0
ihwconnect       -instancename ADC0 -bus vfb -busslaveport ADCP0 -loaddress 0x0ffff200 -hiaddress 0x0ffff22f
ihwconnect       -instancename ADC0 -bus vfb -busslaveport ADCP1 -loaddress 0x0ffff270 -hiaddress 0x0ffff270
ihwsetparameter    -handle     ADC0 -name PCLK1 -value $PCLK(1)  -type uns32
ihwsetparameter    -handle     ADC0 -name sample -value 100      -type double

#ihwconnect       -instancename ADC0 -netport ADTRG    -net 
addConnectNet ADC0 TS0ADT0 TS0ADTRG0
addConnectNet ADC0 TS0ADT1 TS0ADTRG1
addConnectNet ADC0 TS1ADT0 TS1ADTRG0
addConnectNet ADC0 TS1ADT1 TS1ADTRG1

ihwconnect       -instancename ADC0 -netport INTTS0OD -net INTTS0OD
ihwconnect       -instancename ADC0 -netport INTTS0CD -net INTTS0CD0
ihwconnect       -instancename ADC0 -netport INTTS1OD -net INTTS1OD
ihwconnect       -instancename ADC0 -netport INTTS1CD -net INTTS1CD0
ihwconnect       -instancename ADC0 -netport INTAD    -net INTAD0
ihwconnect       -instancename ADC0 -netport ADDMARQ  -net ADDMARQ0
# Simulation artifact signal to disable ADC int generation
ihwconnect       -instancename ADC0 -netport INTADEN  -net DMA0EN

ihwaddperipheral -instancename ADC1 -vendor renesas.ovpworld.org -library peripheral -type adc -version 1.0
ihwconnect       -instancename ADC1 -bus vfb -busslaveport ADCP0 -loaddress 0x0ffff240 -hiaddress 0x0ffff26f
ihwconnect       -instancename ADC1 -bus vfb -busslaveport ADCP1 -loaddress 0x0ffff272 -hiaddress 0x0ffff272
ihwsetparameter    -handle     ADC1 -name PCLK1 -value $PCLK(1)  -type uns32
ihwsetparameter    -handle     ADC1 -name sample -value 100      -type double

#ihwconnect       -instancename ADC1 -netport ADTRG    -net 
ihwconnect       -instancename ADC1 -netport TS0ADT0  -net TS0ADTRG0
ihwconnect       -instancename ADC1 -netport TS0ADT1  -net TS0ADTRG1
ihwconnect       -instancename ADC1 -netport TS1ADT0  -net TS1ADTRG0
ihwconnect       -instancename ADC1 -netport TS1ADT1  -net TS1ADTRG1

ihwconnect       -instancename ADC1 -netport INTTS0OD -net INTTS0OD
ihwconnect       -instancename ADC1 -netport INTTS0CD -net INTTS0CD0
ihwconnect       -instancename ADC1 -netport INTTS1OD -net INTTS1OD
ihwconnect       -instancename ADC1 -netport INTTS1CD -net INTTS1CD0
ihwconnect       -instancename ADC1 -netport INTAD    -net INTAD1
ihwconnect       -instancename ADC1 -netport ADDMARQ  -net ADDMARQ1
# Simulation artifact signal to disacle ADC int generation
ihwconnect       -instancename ADC1 -netport INTADEN  -net DMA1EN

#################################################################
# 16-Bit Timer/Event Counter AA
#################################################################
ihwaddperipheral -instancename TAA0 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA0 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff600 -hiaddress 0x0ffff60f
ihwconnect       -instancename TAA0 -netport INTTAAOV  -net INTTAA0OV
ihwconnect       -instancename TAA0 -netport INTTAACC0 -net INTTAA0CC0
ihwconnect       -instancename TAA0 -netport INTTAACC1 -net INTTAA0CC1

ihwaddperipheral -instancename TAA1 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA1 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff610 -hiaddress 0x0ffff61f
ihwconnect       -instancename TAA1 -netport INTTAAOV  -net INTTAA1OV
ihwconnect       -instancename TAA1 -netport INTTAACC0 -net INTTAA1CC0
ihwconnect       -instancename TAA1 -netport INTTAACC1 -net INTTAA1CC1

ihwaddperipheral -instancename TAA2 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA2 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff620 -hiaddress 0x0ffff62f
ihwconnect       -instancename TAA2 -netport INTTAAOV  -net INTTAA2OV
ihwconnect       -instancename TAA2 -netport INTTAACC0 -net INTTAA2CC0
ihwconnect       -instancename TAA2 -netport INTTAACC1 -net INTTAA2CC1

ihwaddperipheral -instancename TAA3 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA3 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff630 -hiaddress 0x0ffff63f
ihwconnect       -instancename TAA3 -netport INTTAAOV  -net INTTAA3OV
ihwconnect       -instancename TAA3 -netport INTTAACC0 -net INTTAA3CC0
ihwconnect       -instancename TAA3 -netport INTTAACC1 -net INTTAA3CC1

ihwaddperipheral -instancename TAA4 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA4 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff640 -hiaddress 0x0ffff64f
ihwconnect       -instancename TAA4 -netport INTTAAOV  -net INTTAA4OV
ihwconnect       -instancename TAA4 -netport INTTAACC0 -net INTTAA4CC0
ihwconnect       -instancename TAA4 -netport INTTAACC1 -net INTTAA4CC1

ihwaddperipheral -instancename TAA5 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA5 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff650 -hiaddress 0x0ffff65f
ihwconnect       -instancename TAA5 -netport INTTAAOV  -net INTTAA5OV
ihwconnect       -instancename TAA5 -netport INTTAACC0 -net INTTAA5CC0
ihwconnect       -instancename TAA5 -netport INTTAACC1 -net INTTAA5CC1

ihwaddperipheral -instancename TAA6 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA6 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff660 -hiaddress 0x0ffff66f
ihwconnect       -instancename TAA6 -netport INTTAAOV  -net INTTAA6OV
ihwconnect       -instancename TAA6 -netport INTTAACC0 -net INTTAA6CC0
ihwconnect       -instancename TAA6 -netport INTTAACC1 -net INTTAA6CC1

ihwaddperipheral -instancename TAA7 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA7 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff670 -hiaddress 0x0ffff67f
ihwconnect       -instancename TAA7 -netport INTTAAOV  -net INTTAA7OV
ihwconnect       -instancename TAA7 -netport INTTAACC0 -net INTTAA7CC0
ihwconnect       -instancename TAA7 -netport INTTAACC1 -net INTTAA7CC1

ihwaddperipheral -instancename TAA8 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA8 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff680 -hiaddress 0x0ffff68f
ihwconnect       -instancename TAA8 -netport INTTAAOV  -net INTTAA8OV
ihwconnect       -instancename TAA8 -netport INTTAACC0 -net INTTAA8CC0
ihwconnect       -instancename TAA8 -netport INTTAACC1 -net INTTAA8CC1

ihwaddperipheral -instancename TAA9 -vendor renesas.ovpworld.org -library peripheral -type taa -version 1.0
ihwconnect       -instancename TAA9 -bus vfb -busslaveport TAAP0 -loaddress 0x0ffff6b0 -hiaddress 0x0ffff6bf
ihwconnect       -instancename TAA9 -netport INTTAAOV  -net INTTAA9OV
ihwconnect       -instancename TAA9 -netport INTTAACC0 -net INTTAA9CC0
ihwconnect       -instancename TAA9 -netport INTTAACC1 -net INTTAA9CC1

#
# PCLK connections
#
for {set tmr 0} {$tmr <= 9} {incr tmr} {
    foreach c {0 1 2 3 4 5 7 9} {
        ihwsetparameter -handle TAA${tmr} -name PCLK${c} -value $PCLK($c)      -type uns32
    }
}

#################################################################
# 16-Bit Timer/Event Counter S
#################################################################
ihwaddperipheral -instancename TMS0 -vendor renesas.ovpworld.org -library peripheral -type tms -version 1.0
ihwconnect       -instancename TMS0 -bus vfb -busslaveport TMSP0 -loaddress 0x0ffff580 -hiaddress 0x0ffff5a9
ihwconnect       -instancename TMS0 -netport INTTSOV  -net INTTS0OV
ihwconnect       -instancename TMS0 -netport INTTSCC0 -net INTTS0CC0
ihwconnect       -instancename TMS0 -netport INTTSCC1 -net INTTS0CC1
ihwconnect       -instancename TMS0 -netport INTTSCC2 -net INTTS0CC2
ihwconnect       -instancename TMS0 -netport INTTSCC3 -net INTTS0CC3
ihwconnect       -instancename TMS0 -netport INTTSCC4 -net INTTS0CC4
ihwconnect       -instancename TMS0 -netport INTTSCC5 -net INTTS0CC5
ihwconnect       -instancename TMS0 -netport INTTSCD0 -net INTTS0CD0
ihwconnect       -instancename TMS0 -netport INTTSOD  -net INTTS0OD
ihwconnect       -instancename TMS0 -netport INTTSER  -net INTTS0ER
ihwconnect       -instancename TMS0 -netport INTTSWN  -net INTTS0WN

ihwconnect       -instancename TMS0 -netport TSADTRG0 -net TS0ADTRG0
ihwconnect       -instancename TMS0 -netport TSADTRG1 -net TS0ADTRG1

#
# A number of registers are bridged 
#
bridgeMem vfb 0x0FFFF58A 0x0FFFFB48 10
bridgeMem vfb 0x0FFFF598 0x0FFFFB56 8

ihwaddperipheral -instancename TMS1 -vendor renesas.ovpworld.org -library peripheral -type tms -version 1.0
ihwconnect       -instancename TMS1 -bus vfb -busslaveport TMSP0 -loaddress 0x0ffff5c0 -hiaddress 0x0ffff5e9
ihwconnect       -instancename TMS1 -netport INTTSOV  -net INTTS1OV
ihwconnect       -instancename TMS1 -netport INTTSCC0 -net INTTS1CC0
ihwconnect       -instancename TMS1 -netport INTTSCC1 -net INTTS1CC1
ihwconnect       -instancename TMS1 -netport INTTSCC2 -net INTTS1CC2
ihwconnect       -instancename TMS1 -netport INTTSCC3 -net INTTS1CC3
ihwconnect       -instancename TMS1 -netport INTTSCC4 -net INTTS1CC4
ihwconnect       -instancename TMS1 -netport INTTSCC5 -net INTTS1CC5
ihwconnect       -instancename TMS1 -netport INTTSCD0 -net INTTS1CD0
ihwconnect       -instancename TMS1 -netport INTTSOD  -net INTTS1OD
ihwconnect       -instancename TMS1 -netport INTTSER  -net INTTS1ER
ihwconnect       -instancename TMS1 -netport INTTSWN  -net INTTS1WN

ihwconnect       -instancename TMS1 -netport TSADTRG0 -net TS1ADTRG0
ihwconnect       -instancename TMS1 -netport TSADTRG1 -net TS1ADTRG1

#
# A number of registers are bridged 
#
bridgeMem vfb 0x0FFFF5CA 0x0FFFFBC8 10
bridgeMem vfb 0x0FFFF5D8 0x0FFFFBD6 8

#
# PCLK connections
#
for {set tmr 0} {$tmr <= 1} {incr tmr} {
    foreach c {0 1 2 3 4 5 7 9} {
        ihwsetparameter -handle TMS${tmr} -name PCLK${c} -value $PCLK($c)      -type uns32
    }
}

#################################################################
# 16-Bit Timer/Event Counter T
#################################################################
ihwaddperipheral -instancename TMT0 -vendor renesas.ovpworld.org -library peripheral -type tmt -version 1.0
ihwconnect       -instancename TMT0 -bus vfb -busslaveport TMTP0 -loaddress 0x0ffff690 -hiaddress 0x0ffff69f
ihwconnect       -instancename TMT0 -bus vfb -busslaveport TMTP1 -loaddress 0x0ffff990 -hiaddress 0x0ffff991
ihwconnect       -instancename TMT0 -netport INTTTOV  -net INTTT0OV
ihwconnect       -instancename TMT0 -netport INTTTCC0 -net INTTT0CC0
ihwconnect       -instancename TMT0 -netport INTTTCC1 -net INTTT0CC1
ihwconnect       -instancename TMT0 -netport INTTTEC  -net INTTT0EC

ihwaddperipheral -instancename TMT1 -vendor renesas.ovpworld.org -library peripheral -type tmt -version 1.0
ihwconnect       -instancename TMT1 -bus vfb -busslaveport TMTP0 -loaddress 0x0ffff6a0 -hiaddress 0x0ffff6af
ihwconnect       -instancename TMT1 -bus vfb -busslaveport TMTP1 -loaddress 0x0ffff9a0 -hiaddress 0x0ffff9a1
ihwconnect       -instancename TMT1 -netport INTTTOV  -net INTTT1OV
ihwconnect       -instancename TMT1 -netport INTTTCC0 -net INTTT1CC0
ihwconnect       -instancename TMT1 -netport INTTTCC1 -net INTTT1CC1
ihwconnect       -instancename TMT1 -netport INTTTEC  -net INTTT1EC

#
# PCLK connections
#
for {set tmr 0} {$tmr <= 1} {incr tmr} {
    foreach c {0 1 2 3 4 5 7 9} {
        ihwsetparameter -handle TMT${tmr} -name PCLK${c} -value $PCLK($c)      -type uns32
    }
}

#################################################################
# Timer Interconnection
#################################################################

#################################################################
# On-Chip Debug Unit - TBD
#################################################################

#################################################################
# Random Number Generator
#################################################################
ihwaddperipheral -instancename RNG0 -vendor renesas.ovpworld.org -library peripheral -type rng -version 1.0
ihwconnect       -instancename RNG0 -bus vfb -busslaveport RNGP0 -loaddress 0x0ffff700 -hiaddress 0x0ffff701

#################################################################
# Baud Rate Generators 
# BRG[0:1] clocked at 16Mhz
# BRG[2]   clocked at 32Mhz
#################################################################
ihwaddperipheral -instancename BRG0 -vendor renesas.ovpworld.org -library peripheral -type brg -version 1.0
ihwconnect       -instancename BRG0 -bus vfb -busslaveport BRGP0 -loaddress 0x0ffffdc0 -hiaddress 0x0ffffdc1
ihwconnect       -instancename BRG0 -netport INTBRG -net INTBRG0
ihwsetparameter    -handle BRG0 -name PCLK -value $PCLK(1)      -type uns32

ihwaddperipheral -instancename BRG1 -vendor renesas.ovpworld.org -library peripheral -type brg -version 1.0
ihwconnect       -instancename BRG1 -bus vfb -busslaveport BRGP0 -loaddress 0x0ffffdd0 -hiaddress 0x0ffffdd1
ihwconnect       -instancename BRG1 -netport INTBRG -net INTBRG1
ihwsetparameter    -handle BRG1 -name PCLK -value $PCLK(1)      -type uns32

ihwaddperipheral -instancename BRG2  -vendor renesas.ovpworld.org -library peripheral -type brg -version 1.0
ihwconnect       -instancename BRG2  -bus vfb -busslaveport BRGP0 -loaddress 0x0ffffde0 -hiaddress 0x0ffffde1
ihwconnect       -instancename BRG2  -netport INTBRG -net INTBRG2
ihwsetparameter    -handle BRG2 -name PCLK -value $PCLK(0)      -type uns32

##################################################################
## Auxilliary Frequency Output Function
##################################################################
#ihwaddperipheral -instancename AFO -vendor renesas.ovpworld.org -library peripheral -type afo -version 1.0
#ihwconnect       -instancename AFO -bus vfb -busslaveport AFOP0 -loaddress 0x0ffffde0 -hiaddress 0x0ffffde1
#ihwconnect       -instancename AFO -netport INTBRG2 -net INTBRG2

#################################################################
# Non Break Debug Unit - TBD
#################################################################

#################################################################
# FlexRayTM - TBD
#################################################################
