#
# Copyright (c) 2011-2016 Posedge Software, Inc., www.posedgesoft.com
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


set vendor  freescale.ovpworld.org
set library peripheral
set name    VybridUSB
set version 1.0
set desc "Model of the USB peripheral used on the Freescale Vybrid platform"
set limitations "Provides the base behaviour for the OVP Freescale Vybrid platforms"

set range 0x1000

imodelnewperipheral           \
    -imagefile   pse.pse      \
    -name        $name        \
    -vendor      $vendor      \
    -library     $library     \
    -version     $version     \
    -constructor constructor  \
    -releasestatus ovp

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference -text "Development based on document number: VYBRIDRM Rev. 5, 07/2013"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x81c -port bport1 -width 32

set addBlock     "bport1/ab"


#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
ID               0x00 r  - - - - 0xe481fa05 - "Identification register, offset: 0x0"	
HWGENERAL        0x04 r  - - - - 0x00000015 - "Hardware General, offset: 0x4"	
HWHOST           0x08 r  - - - - 0x10020001 - "Host Hardware Parameters, offset: 0x8"	
HWDEVICE         0x0c r  - - - - 0x0000000d - "Device Hardware Parameters, offset: 0xC"	
HWTXBUF          0x10 r  - - - - 0x80080b04 - "TX Buffer Hardware Parameters, offset: 0x10"	
HWRXBUF          0x14 r  - - - - 0x00000904 - "RX Buffer Hardware Parameters, offset: 0x14"	
GPTIMER0LD       0x80 rw - - - - 0x00000000 0x00ffffff "General Purpose Timer #0 Load, offset: 0x80"	
GPTIMER0CTRL     0x84 rw - - - - 0x00000000 0xc1ffffff "General Purpose Timer #0 Controller, offset: 0x84"	
GPTIMER1LD       0x88 rw - - - - 0x00000000 0x00ffffff "General Purpose Timer #1 Load, offset: 0x88"	
GPTIMER1CTRL     0x8c rw - - - - 0x00000000 0xc1ffffff "General Purpose Timer #1 Controller, offset: 0x8C"	
SBUSCFG          0x90 rw -              -             - - 0x00000001 0x00000007 "System Bus Config, offset: 0x90"	
CAPVERSION      0x100 r  readCapVersion -             - - 0x40 - "Capability Register Length, offset: 0x100"	
HCSPARAMS       0x104 r  -              -             - - 0x00010011 - "Host Controller Structural Parameters, offset: 0x104"	
HCCPARAMS       0x108 r  -              -             - - 0x00000006 - "Host Controller Capability Parameters, offset: 0x108"	
DCIVERSION      0x120 r  readDCIVersion -             - - 0x0001 - "Device Controller Interface Version, offset: 0x120"	
DCCPARAMS       0x124 r  -              -             - - 0x00000186 - "Device Controller Capability Parameters, offset: 0x124"	
USBCMD          0x140 rw -              -             - - 0x00080000 0x00ffeb7f "USB Command Register, offset: 0x140"	
USBSTS          0x144 rw -              -             - - 0x00000000 0x030cf5ff "USB Status Register, offset: 0x144"	
USBINTR         0x148 rw -              -             - - 0x00000000 0x030c05ff "Interrupt Enable Register, offset: 0x148"	
FRINDEX         0x14c rw -              -             - - 0x00000000 0x00003fff "USB Frame Index, offset: 0x14C"	
DEVICEADDR      0x154 rw readShare154h writeShare154h - - 0x00000000 0xffffffff "Device_FrameList Base Address, offset: 0x154"	
ASYNCLISTADDR   0x158 rw readShare158h writeShare154h - - 0x00000000 0xffffffff "Next Asynch._Enpoint List Address, offset: 0x158"	
BURSTSIZE       0x160 rw -             -              - - 0x00001010 0x0001fff "Programmable Burst Size, offset: 0x160"	
TXFILLTUNING    0x164 rw - - - - 0x00000808 0x003f1fff "TX FIFO Fill Tuning, offset: 0x164"	
ENDPTNAK        0x178 rw - - - - 0x00000000 0x003f003f "Endpoint NAK, offset: 0x178"	
ENDPTNAKEN      0x17c rw - - - - 0x00000000 0x003f003f "Endpoint NAK Enable, offset: 0x17C"	
PORTSC1         0x184 rw - - - - 0x10000000 0xffffffff "Port Status & Control, offset: 0x184"	
OTGSC           0x1a4 rw - - - - 0x00000220 0x7f7f7f29 "On-The-Go Status & control, offset: 0x1A4"	
USBMODE         0x1a8 rw - - - - 0x00005002 0x0000001f "USB Device Mode, offset: 0x1A8"	
ENDPTSETUPSTAT  0x1ac rw - - - - 0x00000000 0x0000ffff "Endpoint Setup Status, offset: 0x1AC"	
ENDPTPRIME      0x1b0 rw - - - - 0x00000000 0x003f003f "Endpoint Initialization, offset: 0x1B0"	
ENDPTFLUSH      0x1b4 rw - - - - 0x00000000 0x003f003f "Endpoint De-Initialize, offset: 0x1B4"	
ENDPTSTAT       0x1b8 r  - - - - 0x00000000 -          "Endpoint Status, offset: 0x1B8"	
ENDPTCOMPLETE   0x1bc rw - - - - 0x00000000 0x003f003f "Endpoint Complete, offset: 0x1BC"	
ENDPTCTRL0      0x1c0 rw - - - - 0x00800080 0x008d008d "Endpoint Control0, offset: 0x1C0"	
ENDPTCTRL1      0x1c4 rw - - - - 0x00000000 0x00ef00ef "Endpoint Control1, offset: 0x1C4"	
ENDPTCTRL2      0x1c8 rw - - - - 0x00000000 0x00ef00ef "Endpoint Control2, offset: 0x1C8"	
ENDPTCTRL3      0x1cc rw - - - - 0x00000000 0x00ef00ef "Endpoint Control3, offset: 0x1Cc"	
ENDPTCTRL4      0x1d0 rw - - - - 0x00000000 0x00ef00ef "Endpoint Control4, offset: 0x1d0"
ENDPTCTRL5      0x1d4 rw - - - - 0x00000000 0x00ef00ef "Endpoint Control5, offset: 0x1d4"	
CTRL            0x800 rw - - - - 0x00003000 0x0302ff80 "Non-Core Register: USB Control Register"
PHY             0x818 rw - PHYWrite1c - - 0x00000000 0x80000007 "Non-Core Register: USB PHY Control Register"
}

foreach { rname offset raccess readFn writeFn viewFn user reset mask desc } $registers {
    set r ""
    set w ""
    set v ""
    set u ""
    set m ""
    if { $readFn  != "-" } { set r "-readfunction  $readFn"   }
    if { $writeFn != "-" } { set w "-writefunction $writeFn"  }
    if { $viewFn  != "-" } { set v "-viewfunction  $viewFn"   }
    if { $user    != "-" } { set u "-userdata      $user"     }
    if { $mask    != "-" } { set m "-writemask     $mask"     }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $v $u $m"
    eval $cmd

    if { $reset != "-" } {
        imodeladdreset -mmregister $addBlock/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
}

imodeladdnetport -name Reset     -type input

	
 
imodeladdfield -mmregister $addBlock/ID -name ID -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ID -name NID -bitoffset 8  -width 6
imodeladdfield -mmregister $addBlock/ID -name REVISION -bitoffset 16  -width 8	
 
imodeladdfield -mmregister $addBlock/HWGENERAL -name PHYM -bitoffset 6  -width 3
imodeladdfield -mmregister $addBlock/HWGENERAL -name PHYW -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/HWGENERAL -name SM -bitoffset 9  -width 2	
 
imodeladdfield -mmregister $addBlock/HWHOST -name HC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HWHOST -name NPORT -bitoffset 1  -width 3	
 
imodeladdfield -mmregister $addBlock/HWDEVICE -name DC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HWDEVICE -name DEVEP -bitoffset 1  -width 5	
 
imodeladdfield -mmregister $addBlock/HWTXBUF -name TXBURST -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/HWTXBUF -name TXCHANADD -bitoffset 16  -width 8	
 
imodeladdfield -mmregister $addBlock/HWRXBUF -name RXADD -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/HWRXBUF -name RXBURST -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/GPTIMER0LD -name GPTLD -bitoffset 0  -width 24	
 
imodeladdfield -mmregister $addBlock/GPTIMER0CTRL -name GPTCNT -bitoffset 0  -width 24
imodeladdfield -mmregister $addBlock/GPTIMER0CTRL -name GPTMODE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER0CTRL -name GPTRST -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER0CTRL -name GPTRUN -bitoffset 31  -width 1	
 
imodeladdfield -mmregister $addBlock/GPTIMER1LD -name GPTLD -bitoffset 0  -width 24	
 
imodeladdfield -mmregister $addBlock/GPTIMER1CTRL -name GPTCNT -bitoffset 0  -width 24
imodeladdfield -mmregister $addBlock/GPTIMER1CTRL -name GPTMODE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER1CTRL -name GPTRST -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER1CTRL -name GPTRUN -bitoffset 31  -width 1	
 
imodeladdfield -mmregister $addBlock/SBUSCFG -name AHBBRST -bitoffset 0  -width 3	
 
# CAPLENGTH is 8 bit register (on 32 bit boundry),
# HCIVERSION is 16 bit register (on 32 bit boundry),
# These share a common read/write function.
#          CAP: 0x100, reset = 0x40, 
#   HCIVERSION: 0x102, reset = 0x10
 
imodeladdfield -mmregister $addBlock/HCSPARAMS -name N_CC -bitoffset 12  -width 4
imodeladdfield -mmregister $addBlock/HCSPARAMS -name N_PCC -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/HCSPARAMS -name N_PORTS -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/HCSPARAMS -name N_PTT -bitoffset 20  -width 4
imodeladdfield -mmregister $addBlock/HCSPARAMS -name N_TT -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/HCSPARAMS -name PI -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/HCSPARAMS -name PPC -bitoffset 4  -width 1	
 
imodeladdfield -mmregister $addBlock/HCCPARAMS -name ADC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HCCPARAMS -name ASP -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/HCCPARAMS -name EECP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/HCCPARAMS -name IST -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/HCCPARAMS -name PFL -bitoffset 1  -width 1	
 
# DCIVERSION is 16 bit register (on 32 bit boundry), manage this through special r/w routines 
#    DCIVERSION: 0x120, reset = 0x01
 
imodeladdfield -mmregister $addBlock/DCCPARAMS -name DC -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/DCCPARAMS -name DEN -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/DCCPARAMS -name HC -bitoffset 8  -width 1	
 
imodeladdfield -mmregister $addBlock/USBCMD -name ASE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name ASP -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/USBCMD -name ASPE -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name ATDTW -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name FS1 -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/USBCMD -name FS2 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name IAA -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name ITC -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/USBCMD -name PSE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name RS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name RST -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name SUTW -bitoffset 13  -width 1	
 
imodeladdfield -mmregister $addBlock/USBSTS -name AAI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name AS -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name FRI -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name HCH -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name NAKI -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name PCI -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name PS -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name RCL -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name SEI -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name SLI -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name SRI -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name TI0 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name TI1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UEI -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UI -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UPI -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UAI -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name ULPII -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name URI -bitoffset 6  -width 1	
 
imodeladdfield -mmregister $addBlock/USBINTR -name AAE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name FRE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name NAKE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name PCE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name SEE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name SLE -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name SRE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name TIE0 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name TIE1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name UAIE -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name UE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name UEE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name ULPIE -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name UPIE -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/USBINTR -name URE -bitoffset 6  -width 1	
 
imodeladdfield -mmregister $addBlock/FRINDEX -name FRINDEX -bitoffset 0  -width 14	
 
# DEVICEADDR/PERIODICLISTBASE removed, as this is a shared register. The read/write funtions need to
# manage these registers
#    PERIODICLISTBASE base Addr: 0x154, BASEADR, offset=12, width=20
#    DeviceAddr: 0x154, USBADRA, offset=24, width=1
#                       USBADR, offset=25, width=7
# ENDPTLISTADDR/ASYNCLISTADDR
#	ASYNYCLISTADDR: 0x158, ASYBASE, offset=5, width=27
#   ENDPTLISTADDR:  0x158, EPBASE, offset=11, width=21
 
imodeladdfield -mmregister $addBlock/BURSTSIZE -name RXPBURST -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/BURSTSIZE -name TXPBURST -bitoffset 8  -width 9	
 
imodeladdfield -mmregister $addBlock/TXFILLTUNING -name TXFIFOTHRES -bitoffset 16  -width 6
imodeladdfield -mmregister $addBlock/TXFILLTUNING -name TXSCHHEALTH -bitoffset 8  -width 5
imodeladdfield -mmregister $addBlock/TXFILLTUNING -name TXSCHOH -bitoffset 0  -width 8	

# IC_USB register not in specification.
 
imodeladdfield -mmregister $addBlock/ENDPTNAK -name EPRN -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ENDPTNAK -name EPTN -bitoffset 16  -width 6	
 
imodeladdfield -mmregister $addBlock/ENDPTNAKEN -name EPRNE -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ENDPTNAKEN -name EPTNE -bitoffset 16  -width 6	
 
imodeladdfield -mmregister $addBlock/PORTSC1 -name CCS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name CSC -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name FPR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name HSP -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name LS -bitoffset 10  -width 2
imodeladdfield -mmregister $addBlock/PORTSC1 -name OCA -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name OCC -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PEC -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PFSC -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PHCD -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PIC -bitoffset 14  -width 2
imodeladdfield -mmregister $addBlock/PORTSC1 -name PO -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PP -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PR -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PSPD -bitoffset 26  -width 2
imodeladdfield -mmregister $addBlock/PORTSC1 -name PTC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PORTSC1 -name PTS1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name PTS2 -bitoffset 30  -width 2
imodeladdfield -mmregister $addBlock/PORTSC1 -name PTW -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name STS -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name SUSP -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name WKCN -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name WKDC -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name WKOC -bitoffset 22  -width 1	
 
# Names had 1 at begining, not liked by compiler.
imodeladdfield -mmregister $addBlock/OTGSC -name MSS1 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name MSSE1 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name MST1 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name ASV -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name ASVIE -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name ASVIS -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name AVV -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name AVVIE -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name AVVIS -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name BSE -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name BSEIE -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name BSEIS -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name BSV -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name BSVIE -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name BSVIS -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name DPIE -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name DPIS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name DPS -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name ID -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name IDIE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name IDIS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name IDPU -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name OT -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name VD -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/USBMODE -name CM -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/USBMODE -name ES -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/USBMODE -name SDIS -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/USBMODE -name SLOM -bitoffset 3  -width 1	
 
imodeladdfield -mmregister $addBlock/ENDPTSETUPSTAT -name ENDPTSETUPSTAT -bitoffset 0  -width 16	
 
imodeladdfield -mmregister $addBlock/ENDPTPRIME -name PERB -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ENDPTPRIME -name PETB -bitoffset 16  -width 6	
 
imodeladdfield -mmregister $addBlock/ENDPTFLUSH -name FERB -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ENDPTFLUSH -name FETB -bitoffset 16  -width 6	
 
imodeladdfield -mmregister $addBlock/ENDPTSTAT -name ERBR -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ENDPTSTAT -name ETBR -bitoffset 16  -width 6	
 
imodeladdfield -mmregister $addBlock/ENDPTCOMPLETE -name ERCE -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/ENDPTCOMPLETE -name ETCE -bitoffset 16  -width 6	
 
imodeladdfield -mmregister $addBlock/ENDPTCTRL0 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL0 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL0 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ENDPTCTRL0 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL0 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL0 -name TXT -bitoffset 18  -width 2	
 
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL1 -name TXT -bitoffset 18  -width 2
 
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL2 -name TXT -bitoffset 18  -width 2
 
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL3 -name TXT -bitoffset 18  -width 2
 
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL4 -name TXT -bitoffset 18  -width 2

imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ENDPTCTRL5 -name TXT -bitoffset 18  -width 2

imodeladdfield -mmregister $addBlock/CTRL -name WIR -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name VBUS_CH_INT_MASK -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name VBUS_CH_STAT -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name WKUP_VBUS_EN -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name WKUP_SW -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name WKUP_SW_EN -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name ETMI_ON_CLOSK -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name SUSPENDM -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name RESET -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name WIE -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name PM -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name OVER_CUR_POL -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name OVER_CUR_DIS -bitoffset 7  -width 1

imodeladdfield -mmregister $addBlock/PHY -name UTMI_CLK_VLD -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/PHY -name CHRGDET -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PHY -name CHRGDET_INT_EN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PHY -name CHRGDET_INT_FLG -bitoffset 0  -width 1
