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
set name    KinetisUSBHS
set version 1.0
set desc "Model of the USBHS peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

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
iadddocumentation -name Reference -text "www.freescale.com/Kinetis"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x204 -port bport1 -width 32

set addBlock     "bport1/ab"


# 09-01-2014 PRE: DCIVERSION is a 16 bit register in the documentation. Needed to change it's offset
#                 to 120 (is 122) in documentation so that igen can compile pse.tcl file.

#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
ID              0x00 r  - - - - 0xe461fa05 - "Identification Register, offset: 0x0 "    
HWGENERAL       0x04 r  - - - - 0x00000085 - "General Hardware Parameters Register, offset: 0x4 "   
HWHOST          0x08 r  - - - - 0x10020001 - "Host Hardware Parameters Register, offset: 0x8 "  
HWDEVICE        0x0c r  - - - - 0x00000009 - "Device Hardware Parameters Register, offset: 0xC "    
HWTXBUF         0x10 r  - - - - 0x80070908 - "Transmit Buffer Hardware Parameters Register, offset: 0x10 "  
HWRXBUF         0x14 r  - - - - 0x00000808 - "Receive Buffer Hardware Parameters Register, offset: 0x14 "   
GPTIMER0LD      0x80 rw - - - - 0x00000000 0x00ffffff "General Purpose Timer n Load Register, offset: 0x80 "    
GPTIMER0CTL     0x84 rw - - - - 0x00000000 0xc1000000 "General Purpose Timer n Control Register, offset: 0x84 " 
GPTIMER1LD      0x88 rw - - - - 0x00000000 0x00ffffff "General Purpose Timer n Load Register, offset: 0x88 "    
GPTIMER1CTL     0x8c rw - - - - 0x00000000 0xc1000000 "General Purpose Timer n Control Register, offset: 0x8C " 
SBUSCFG         0x90 rw - - - - 0x00000000 0x00000007 "System Bus Interface Configuration Register, offset: 0x90 "
HCIVERSION      0x100 r  - - - - 0x01000040 - "Host Controller Interface Version Register, offset: 0x100 "  
HCSPARAMS       0x104 r  - - - - 0x00010011 - "Host Controller Structural Parameters Register, offset: 0x104 "  
HCCPARAMS       0x108 r  - - - - 0x00000006 - "Host Controller Capability Parameters Register, offset: 0x108 "  
DCIVERSION      0x120 r  - - - - 0x00000001 - "Device Controller Interface Version, offset: 0x122, 16bit "  
DCCPARAMS       0x124 r  - - - - 0x00000184 - "Device Controller Capability Parameters, offset: 0x124 " 
USBCMD          0x140 rw - - - - 0x00080000 0x00ffeb7f "USB Command Register, offset: 0x140 "   
USBSTS          0x144 rw - - - - 0x00000000 0x030a01ff "USB Status Register, offset: 0x144 "    
USBINTR         0x148 rw - - - - 0x00000000 0x030d05ff "USB Interrupt Enable Register, offset: 0x148 "  
FRINDEX         0x14c rw - - - - 0x00000000 0x00003fff "Frame Index Register, offset: 0x14C "   
DEVICEADDR      0x154 rw - - - - 0x00000000 0xfffff000 "Device Address Register, offset: 0x154 "    
ASYNCLISTADDR   0x158 rw - - - - 0x00000000 0xffffffe0 "Current Asynchronous List Address Register, offset: 0x158 " 
TTCTRL          0x15c rw - - - - 0x00000000 0x00000000 "Host TT Asynchronous Buffer Control, offset: 0x15C "    
BURSTSIZE       0x160 rw - - - - 0x00008080 0x0000ffff "Master Interface Data Burst Size Register, offset: 0x160 "  
TXFILLTUNING    0x164 rw - - - - 0x00000000 0x003f1f7f "Transmit FIFO Tuning Control Register, offset: 0x164 "  
ULPI_VIEWPORT   0x170 rw - - - - 0x00000000 0xefff00ff "ULPI Register Access, offset: 0x170 "   
ENDPTNAK        0x178 rw - - - - 0x00000000 0x000f000f "ULPI Register Access, offset: 0x170 "   
ENDPTNAKEN      0x17c rw - - - - 0x00000000 0x000f000f "ULPI Register Access, offset: 0x170 "   
CONFIGFLAG      0x180 rw - - - - 0x00000001 0x00000000 "Configure Flag Register, offset: 0x180 "    
PORTSC1         0x184 rw - - - - 0x80000000 0xc1fff1ee "Port Status and Control Registers, offset: 0x184 "  
OTGSC           0x1a4 rw - - - - 0x00001020 0x7f7f00bf "On-the-Go Status and Control Register, offset: 0x1A4 "  
USBMODE         0x1a8 rw - - - - 0x00005000 0x0000701f "USB Mode Register, offset: 0x1A8 "  
EPSETUPSR       0x1ac rw - - - - 0x00000000 0x0000000f "Endpoint Setup Status Register, offset: 0x1AC " 
EPPRIME         0x1b0 rw - - - - 0x00000000 0x000f000f "Endpoint Initialization Register, offset: 0x1B0 "   
EPFLUSH         0x1b4 rw - - - - 0x00000000 0x000f000f "Endpoint Flush Register, offset: 0x1B4 "    
EPSR            0x1b8 r  - - - - 0x00000000 -          "Endpoint Status Register, offset: 0x1B8 "   
EPCOMPLETE      0x1bc rw - - - - 0x00000000 0x000f000f "Endpoint Complete Register, offset: 0x1BC " 
EPCR0           0x1c0 rw - - - - 0x00800080 0x00010001 "Endpoint Control Register 0, offset: 0x1C0 "    
EPCR1           0x1c4 rw - - - - 0x00000000 0x00ef00ef "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 " 
EPCR2           0x1c8 rw - - - - 0x00000000 0x00ef00ef "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 " 
EPCR3           0x1cc rw - - - - 0x00000000 0x00ef00ef "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 "
USBGENCTRL      0x200 rw - - - - 0x00000000 0x00000023 "General Control Regiser, offset: 0x20 "
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
# 08-31-2014 PRE: following 4 registers differ from documentation, only REVISON (with different
#                 offset/width (16/8) in .h)
imodeladdfield -mmregister $addBlock/ID -name TAG -bitoffset 16  -width 5   
imodeladdfield -mmregister $addBlock/ID -name REVISION -bitoffset 21  -width 4  
imodeladdfield -mmregister $addBlock/ID -name VERSION -bitoffset 25  -width 4   
imodeladdfield -mmregister $addBlock/ID -name VERSIONID -bitoffset 29  -width 3 
 
imodeladdfield -mmregister $addBlock/HWGENERAL -name PHYM -bitoffset 6  -width 3
imodeladdfield -mmregister $addBlock/HWGENERAL -name SM -bitoffset 9  -width 2  
# 08-31-2014 PRE: PHYW not in documentation
#imodeladdfield -mmregister $addBlock/HWGENERAL -name PHYW -bitoffset 4  -width 2
 
imodeladdfield -mmregister $addBlock/HWHOST -name HC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HWHOST -name NPORT -bitoffset 1  -width 3
imodeladdfield -mmregister $addBlock/HWHOST -name TTASY -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/HWHOST -name TTPER -bitoffset 24  -width 8 
 
imodeladdfield -mmregister $addBlock/HWDEVICE -name DC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HWDEVICE -name DEVEP -bitoffset 1  -width 5    
 
imodeladdfield -mmregister $addBlock/HWTXBUF -name TXADD -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/HWTXBUF -name TXBURST -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/HWTXBUF -name TXCHANADD -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/HWTXBUF -name TXLC -bitoffset 31  -width 1 
 
imodeladdfield -mmregister $addBlock/HWRXBUF -name RXADD -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/HWRXBUF -name RXBURST -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/GPTIMER0LD -name GPTLD -bitoffset 0  -width 24 
 
imodeladdfield -mmregister $addBlock/GPTIMER0CTL -name GPTCNT -bitoffset 0  -width 24
imodeladdfield -mmregister $addBlock/GPTIMER0CTL -name MODE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER0CTL -name RST -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER0CTL -name RUN -bitoffset 31  -width 1  
 
imodeladdfield -mmregister $addBlock/GPTIMER1LD -name GPTLD -bitoffset 0  -width 24 
 
imodeladdfield -mmregister $addBlock/GPTIMER1CTL -name GPTCNT -bitoffset 0  -width 24
imodeladdfield -mmregister $addBlock/GPTIMER1CTL -name MODE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER1CTL -name RST -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/GPTIMER1CTL -name RUN -bitoffset 31  -width 1  

# 08-31-2014 PRE: The following register not in the .h file.
imodeladdfield -mmregister $addBlock/SBUSCFG -name BURSTMODE -bitoffset 0  -width 3     
 
imodeladdfield -mmregister $addBlock/HCIVERSION -name HCIVERSION -bitoffset 16  -width 16   
imodeladdfield -mmregister $addBlock/HCIVERSION -name CAPLENGTH -bitoffset 0  -width 8  
 
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
 
# 09-01-2014 PRE: DCIVERSION is a 16 bit register in the documentation. Needed to change it's offset
#                 to 120 (is 122) in documentation so that igen can compile pse.tcl file.
imodeladdfield -mmregister $addBlock/DCIVERSION -name DCIVERSION -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/DCCPARAMS -name DC -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/DCCPARAMS -name DEN -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/DCCPARAMS -name HC -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/USBCMD -name ASE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name ASP -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/USBCMD -name ASPE -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name ATDTW -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/USBCMD -name FS -bitoffset 2  -width 2
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
imodeladdfield -mmregister $addBlock/USBSTS -name UAI -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UEI -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UI -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name ULPII -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/USBSTS -name UPI -bitoffset 19  -width 1
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
 
# 08-31-2014 PRE: The DEVICEADDR/PERIODICLISTBASE share a register space.
imodeladdfield -mmregister $addBlock/DEVICEADDR -name USBADR -bitoffset 25  -width 7    
imodeladdfield -mmregister $addBlock/DEVICEADDR -name USBADRA -bitoffset 24  -width 1   
#imodeladdfield -mmregister $addBlock/PERIODICLISTBASE -name PERBASE -bitoffset 12  -width 20   
    
# 08-31-2014 PRE: The ASYNCLISTADDR/EPLISTADDR share a register space.
imodeladdfield -mmregister $addBlock/ASYNCLISTADDR -name ASYBASE -bitoffset 5  -width 27    
#imodeladdfield -mmregister $addBlock/EPLISTADDR -name EPBASE -bitoffset 11  -width 21  
    
imodeladdfield -mmregister $addBlock/TTCTRL -name TTHA -bitoffset 24  -width 7  
 
imodeladdfield -mmregister $addBlock/BURSTSIZE -name RXPBURST -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/BURSTSIZE -name TXPBURST -bitoffset 8  -width 8    
 
imodeladdfield -mmregister $addBlock/TXFILLTUNING -name TXFIFOTHRES -bitoffset 16  -width 6
imodeladdfield -mmregister $addBlock/TXFILLTUNING -name TXSCHHEALTH -bitoffset 8  -width 5
# 08-31-2014 PRE: .h file had width of TXSCHOH as 8
imodeladdfield -mmregister $addBlock/TXFILLTUNING -name TXSCHOH -bitoffset 0  -width 7  
 
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_ADDR -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_DATRD -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_DATWR -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_PORT -bitoffset 24  -width 3
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_RUN -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_RW -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_SS -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/ULPI_VIEWPORT -name ULPI_WU -bitoffset 31  -width 1    

# 08-31-2014 PRE: Register ENDPTNAK and ENDPTNAKEN not in .h file.
imodeladdfield -mmregister $addBlock/ENDPTNAK -name EPTNE -bitoffset 16  -width 4   
imodeladdfield -mmregister $addBlock/ENDPTNAK -name EPRNE -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/ENDPTNAKEN -name EPTNE -bitoffset 16  -width 4 
imodeladdfield -mmregister $addBlock/ENDPTNAKEN -name EPRNE -bitoffset 0  -width 4  
 
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
imodeladdfield -mmregister $addBlock/PORTSC1 -name PTS -bitoffset 30  -width 2
imodeladdfield -mmregister $addBlock/PORTSC1 -name SUSP -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name WKCN -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name WKDS -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PORTSC1 -name WKOC -bitoffset 22  -width 1 
 
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
imodeladdfield -mmregister $addBlock/OTGSC -name DP -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name DPIE -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name DPIS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name DPS -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name ID -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name IDIE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name IDIS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name IDPU -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name MSE -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name MSS -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name MST -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name OT -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name VC -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/OTGSC -name VD -bitoffset 0  -width 1  
# 08-31-2014 PRE: Following two registers not in .h file
imodeladdfield -mmregister $addBlock/OTGSC -name HABA -bitoffset 7  -width 1    
imodeladdfield -mmregister $addBlock/OTGSC -name HAAR -bitoffset 2  -width 1    
 
imodeladdfield -mmregister $addBlock/USBMODE -name CM -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/USBMODE -name ES -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/USBMODE -name SDIS -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/USBMODE -name SLOM -bitoffset 3  -width 1  
# 08-31-2014 PRE: TXHSD not in .h file
imodeladdfield -mmregister $addBlock/USBMODE -name TXHSD -bitoffset 12  -width 3    
 
imodeladdfield -mmregister $addBlock/EPSETUPSR -name EPSETUPSTAT -bitoffset 0  -width 4 
 
imodeladdfield -mmregister $addBlock/EPPRIME -name PERB -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/EPPRIME -name PETB -bitoffset 16  -width 4 
 
imodeladdfield -mmregister $addBlock/EPFLUSH -name FERB -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/EPFLUSH -name FETB -bitoffset 16  -width 4 
 
imodeladdfield -mmregister $addBlock/EPSR -name ERBR -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/EPSR -name ETBR -bitoffset 16  -width 4    
 
imodeladdfield -mmregister $addBlock/EPCOMPLETE -name ERCE -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/EPCOMPLETE -name ETCE -bitoffset 16  -width 4  
 
imodeladdfield -mmregister $addBlock/EPCR0 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/EPCR0 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EPCR0 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/EPCR0 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EPCR0 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EPCR0 -name TXT -bitoffset 18  -width 2    
 
imodeladdfield -mmregister $addBlock/EPCR1 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/EPCR1 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EPCR1 -name TXT -bitoffset 18  -width 2    
 
imodeladdfield -mmregister $addBlock/EPCR2 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/EPCR2 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EPCR2 -name TXT -bitoffset 18  -width 2    
 
imodeladdfield -mmregister $addBlock/EPCR3 -name RXD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name RXE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name RXI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name RXR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name RXS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name RXT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/EPCR3 -name TXD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name TXE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name TXI -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name TXR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name TXS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EPCR3 -name TXT -bitoffset 18  -width 2

# 8-31-2014 PRE: Following not in .h File
imodeladdfield -mmregister $addBlock/USBGENCTRL -name WU_INT_CLR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/USBGENCTRL -name WU_ULPI_EN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/USBGENCTRL -name WU_IE -bitoffset 0  -width 1

