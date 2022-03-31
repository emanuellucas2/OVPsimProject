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
set name    KinetisUSB
set version 1.0
set desc "Model of the USB peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x118 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
PERID           0x00 r  - - - - 0x04 - "Peripheral ID Register, offset: 0x0 "   
IDCOMP          0x04 r  - - - - 0xfb - "Peripheral ID Complement Register, offset: 0x4 "    
REV             0x08 r  - - - - 0x33 - "Peripheral Revision Register, offset: 0x8 " 
ADDINFO         0x0c r  - - - - 0x01 - "Peripheral Additional Info Register, offset: 0xC "  
OTGISTAT        0x10 rw - - - - 0x00 0xed "OTG Interrupt Status Register, offset: 0x10 "    
OTGICR          0x14 rw - - - - 0x00 0xed "OTG Interrupt Control Register, offset: 0x14 "   
OTGSTAT         0x18 rw - - - - 0x00 0xed "OTG Status Register, offset: 0x18 "  
OTGCTL          0x1c rw - - - - 0x00 0xb4 "OTG Control Register, offset: 0x1C " 
ISTAT           0x80 rw - - - - 0x00 0xff "Interrupt Status Register, offset: 0x80 "    
INTEN           0x84 rw - - - - 0x00 0xff "Interrupt Enable Register, offset: 0x84 "    
ERRSTAT         0x88 rw - - - - 0x00 0xbf "Error Interrupt Status Register, offset: 0x88 "  
ERREN           0x8c rw - - - - 0x00 0xbf "Error Interrupt Enable Register, offset: 0x8C "  
STAT            0x90 r  - - - - 0x00 - "Status Register, offset: 0x90 " 
CTL             0x94 rw - - - - 0x00 0xff "Control Register, offset: 0x94 " 
ADDR            0x98 rw - - - - 0x00 0xff "Address Register, offset: 0x98 " 
BDTPAGE1        0x9c rw - - - - 0x00 0xfe "BDT Page Register 1, offset: 0x9C "  
FRMNUML         0xa0 rw - - - - 0x00 0xff "Frame Number Register Low, offset: 0xA0 "    
FRMNUMH         0xa4 rw - - - - 0x00 0x07 "Frame Number Register High, offset: 0xA4 "   
TOKEN           0xa8 rw - - - - 0x00 0xff "Token Register, offset: 0xA8 "   
SOFTHLD         0xac rw - - - - 0x00 0xff "SOF Threshold Register, offset: 0xAC "   
BDTPAGE2        0xb0 rw - - - - 0x00 0xff "BDT Page Register 2, offset: 0xB0 "  
BDTPAGE3        0xb4 rw - - - - 0x00 0xff "BDT Page Register 3, offset: 0xB4 "  
ENDPOINT0       0xc0 rw - - - - 0x00 0xdf "Endpoint Control Register 0, offset 0xc0"
ENDPOINT1       0xc4 rw - - - - 0x00 0xdf "Endpoint Control Register 1, offset 0xc4"    
ENDPOINT2       0xc8 rw - - - - 0x00 0xdf "Endpoint Control Register 2, offset 0xc8"    
ENDPOINT3       0xcc rw - - - - 0x00 0xdf "Endpoint Control Register 3, offset 0xcc"    
ENDPOINT4       0xd0 rw - - - - 0x00 0xdf "Endpoint Control Register 4, offset 0xd0"    
ENDPOINT5       0xd4 rw - - - - 0x00 0xdf "Endpoint Control Register 5, offset 0xd4"    
ENDPOINT6       0xd8 rw - - - - 0x00 0xdf "Endpoint Control Register 6, offset 0xd8"    
ENDPOINT7       0xdc rw - - - - 0x00 0xdf "Endpoint Control Register 7, offset 0xdc"    
ENDPOINT8       0xe0 rw - - - - 0x00 0xdf "Endpoint Control Register 8, offset 0xe0"    
ENDPOINT9       0xe4 rw - - - - 0x00 0xdf "Endpoint Control Register 9, offset 0xe4"    
ENDPOINT10      0xe8 rw - - - - 0x00 0xdf "Endpoint Control Register 10, offset 0xe8"   
ENDPOINT11      0xec rw - - - - 0x00 0xdf "Endpoint Control Register 11, offset 0xec"   
ENDPOINT12      0xf0 rw - - - - 0x00 0xdf "Endpoint Control Register 12, offset 0xf0"   
ENDPOINT13      0xf4 rw - - - - 0x00 0xdf "Endpoint Control Register 13, offset 0xf4"   
ENDPOINT14      0xf8 rw - - - - 0x00 0xdf "Endpoint Control Register 14, offset 0xf8"   
ENDPOINT15      0xfc rw - - - - 0x00 0xdf "Endpoint Control Register 15, offset 0xfc"   
USBCTRL         0x100 rw - - - - 0xc0 0xc0 "USB Control Register, offset: 0x100 "   
OBSERVE         0x104 r  - - - - 0x50 - "USB OTG Observe Register, offset: 0x104 "  
CONTROL         0x108 rw - - - - 0x00 0x10 "USB OTG Control Register, offset: 0x108 "   
USBTRC0         0x10c rw - - - - 0x00 0xa0 "USB Transceiver Control Register 0, offset: 0x10C " 
USBFRMADJUST    0x114 rw - - - - 0x00 0xff "Frame Adjust Register, offset: 0x114 "
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

    
 
imodeladdfield -mmregister $addBlock/PERID -name ID -bitoffset 0  -width 6  
 
imodeladdfield -mmregister $addBlock/IDCOMP -name NID -bitoffset 0  -width 6    
 
imodeladdfield -mmregister $addBlock/REV -name REV -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/ADDINFO -name IEHOST -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ADDINFO -name IRQNUM -bitoffset 3  -width 5    
 
imodeladdfield -mmregister $addBlock/OTGISTAT -name AVBUSCHG -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/OTGISTAT -name B_SESS_CHG -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/OTGISTAT -name IDCHG -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/OTGISTAT -name LINE_STATE_CHG -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OTGISTAT -name ONEMSEC -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OTGISTAT -name SESSVLDCHG -bitoffset 3  -width 1   
 
imodeladdfield -mmregister $addBlock/OTGICR -name AVBUSEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/OTGICR -name BSESSEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/OTGICR -name IDEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/OTGICR -name LINESTATEEN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OTGICR -name ONEMSECEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OTGICR -name SESSVLDEN -bitoffset 3  -width 1  
 
imodeladdfield -mmregister $addBlock/OTGSTAT -name AVBUSVLD -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/OTGSTAT -name BSESSEND -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/OTGSTAT -name ID -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/OTGSTAT -name LINESTATESTABLE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OTGSTAT -name ONEMSECEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OTGSTAT -name SESS_VLD -bitoffset 3  -width 1  
 
imodeladdfield -mmregister $addBlock/OTGCTL -name DMLOW -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/OTGCTL -name DPHIGH -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/OTGCTL -name DPLOW -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OTGCTL -name OTGEN -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/ISTAT -name ATTACH -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name ERROR -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name RESUME -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name SLEEP -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name SOFTOK -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name STALL -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name TOKDNE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ISTAT -name USBRST -bitoffset 0  -width 1  
 
imodeladdfield -mmregister $addBlock/INTEN -name ATTACHEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name ERROREN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name RESUMEEN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name SLEEPEN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name SOFTOKEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name STALLEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name TOKDNEEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/INTEN -name USBRSTEN -bitoffset 0  -width 1    
 
imodeladdfield -mmregister $addBlock/ERRSTAT -name BTOERR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ERRSTAT -name BTSERR -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ERRSTAT -name CRC16 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ERRSTAT -name CRC5EOF -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ERRSTAT -name DFN8 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ERRSTAT -name DMAERR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ERRSTAT -name PIDERR -bitoffset 0  -width 1    
 
imodeladdfield -mmregister $addBlock/ERREN -name BTOERREN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ERREN -name BTSERREN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ERREN -name CRC16EN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ERREN -name CRC5EOFEN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ERREN -name DFN8EN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ERREN -name DMAERREN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ERREN -name PIDERREN -bitoffset 0  -width 1    
 
imodeladdfield -mmregister $addBlock/STAT -name ENDP -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/STAT -name ODD -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/STAT -name TX -bitoffset 3  -width 1   
 
imodeladdfield -mmregister $addBlock/CTL -name HOSTMODEEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CTL -name JSTATE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CTL -name ODDRST -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/CTL -name RESET -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CTL -name RESUME -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/CTL -name SE0 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/CTL -name TXSUSPENDTOKENBUSY -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CTL -name USBENSOFEN -bitoffset 0  -width 1    
 
imodeladdfield -mmregister $addBlock/ADDR -name ADDR -bitoffset 0  -width 7
imodeladdfield -mmregister $addBlock/ADDR -name LSEN -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/BDTPAGE1 -name BDTBA -bitoffset 1  -width 7    
 
imodeladdfield -mmregister $addBlock/FRMNUML -name FRM -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/FRMNUMH -name FRM -bitoffset 0  -width 3   
 
imodeladdfield -mmregister $addBlock/TOKEN -name TOKENENDPT -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/TOKEN -name TOKENPID -bitoffset 4  -width 4    
 
imodeladdfield -mmregister $addBlock/SOFTHLD -name CNT -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/BDTPAGE2 -name BDTBA -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/BDTPAGE3 -name BDTBA -bitoffset 0  -width 8    

for {set idx  0} {$idx < 16} {incr idx} {
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name EPCTLDIS -bitoffset 4  -width 1"
    eval $cmd
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name EPHSHK -bitoffset 0  -width 1"
    eval $cmd
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name EPRXEN -bitoffset 3  -width 1"
    eval $cmd
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name EPSTALL -bitoffset 1  -width 1"
    eval $cmd
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name EPTXEN -bitoffset 2  -width 1"
    eval $cmd
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name HOSTWOHUB -bitoffset 7  -width 1"
    eval $cmd
    set cmd "imodeladdfield -mmregister $addBlock/ENDPOINT$idx -name RETRYDIS -bitoffset 6  -width 1"
    eval $cmd
} 
 
imodeladdfield -mmregister $addBlock/USBCTRL -name PDE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/USBCTRL -name SUSP -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/OBSERVE -name DMPD -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/OBSERVE -name DPPD -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OBSERVE -name DPPU -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/CONTROL -name DPPULLUPNONOTG -bitoffset 4  -width 1    
 
imodeladdfield -mmregister $addBlock/USBTRC0 -name SYNC_DET -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/USBTRC0 -name USB_RESUME_INT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/USBTRC0 -name USBRESET -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/USBTRC0 -name USBRESMEN -bitoffset 5  -width 1 
 
imodeladdfield -mmregister $addBlock/USBFRMADJUST -name ADJ -bitoffset 0  -width 8
