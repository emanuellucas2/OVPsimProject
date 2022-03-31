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
set name    KinetisCAN
set version 1.0
set desc "Model of the CAN peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x8c0 -port bport1 -width 32

set addBlock     "bport1/ab"



# 8/25/2014 PRE - offset 0x80 to 0x47c is used for message buffer structures. Depending on mode the layout could be different.
# Need to figure out how to map this section. It is left blank for now.

#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
MCR             0x00 rw - - - - 0xd890000f 0xf6e7337f "Module Configuration Register, offset: 0x0 " 
CTRL1           0x04 rw - - - - 0x00000000 0xfffffcff "Control 1 Register, offset: 0x4 "    
TIMER           0x08 rw - - - - 0x00000000 0x0000ffff "Free Running Timer, offset: 0x8 "    
RXMGMASK        0x10 rw - - - - 0xffffffff 0xffffffff "Rx Mailboxes Global Mask Register, offset: 0x10 "    
RX14MASK        0x14 rw - - - - 0xffffffff 0xffffffff "Rx 14 Mask Register, offset: 0x14 "  
RX15MASK        0x18 rw - - - - 0xffffffff 0xffffffff "Rx 15 Mask Register, offset: 0x18 "  
ECR             0x1c rw - - - - 0x00000000 0x0000ffff "Error Counter, offset: 0x1C "    
ESR1            0x20 rw - - - - 0x00000000 0x00030007 "Error and Status 1 Register, offset: 0x20 "  
IMASK2          0x24 rw - - - - 0x00000000 0xffffffff "Interrupt Masks 2 Register, offset: 0x24 "   
IMASK1          0x28 rw - - - - 0x00000000 0xffffffff "Interrupt Masks 1 Register, offset: 0x28 "   
IFLAG2          0x2c rw - - - - 0x00000000 0xffffffff "Interrupt Flags 2 Register, offset: 0x2C "   
IFLAG1          0x30 rw - - - - 0x00000000 0xffffffff "Interrupt Flags 1 Register, offset: 0x30 "   
CTRL2           0x34 rw - - - - 0x00b00000 0x1fff0000 "Control 2 Register, offset: 0x34 "   
ESR2            0x38 rw - - - - 0x00000000 0x00000000 "Error and Status 2 Register, offset: 0x38 "  
CRCR            0x44 r  - - - - 0x00000000 0x00000000 "CRC Register, offset: 0x44 " 
RXFGMASK        0x48 rw - - - - 0xffffffff 0xffffffff "Rx FIFO Global Mask Register, offset: 0x48 " 
RXFIR           0x4c r  - - - - -          0x00000000  "Rx FIFO Information Register, offset: 0x4C "    


RXIMR0          0x880 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR1          0x884 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR2          0x888 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR3          0x88c rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR4          0x890 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR5          0x894 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR6          0x898 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR7          0x89c rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR8          0x8a0 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR9          0x8a4 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR10         0x8a8 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR11         0x8ac rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR12         0x8b0 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR13         0x8b4 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR14         0x8b8 rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 " 
RXIMR15         0x8bc rw - - - - - 0xffffffff "Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 "
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
    
 
imodeladdfield -mmregister $addBlock/MCR -name MAXMB -bitoffset 0  -width 7
imodeladdfield -mmregister $addBlock/MCR -name IDAM -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/MCR -name AEN -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/MCR -name LPRIOEN -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/MCR -name IRMQ -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SRXDIS -bitoffset 17  -width 1
# 8/25/2014 PRE - DOZE not in K60 documentation, leaving in for now.
imodeladdfield -mmregister $addBlock/MCR -name DOZE -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/MCR -name LPMACK -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/MCR -name WRNEN -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SLFWAK -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SUPV -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/MCR -name FRZACK -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SOFTRST -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/MCR -name WAKMSK -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/MCR -name NOTRDY -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/MCR -name HALT -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/MCR -name RFEN -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/MCR -name FRZ -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/MCR -name MDIS -bitoffset 31  -width 1 
 
imodeladdfield -mmregister $addBlock/CTRL1 -name PROPSEG -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/CTRL1 -name LOM -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name LBUF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name TSYN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name BOFFREC -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name SMP -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name RWRNMSK -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name TWRNMSK -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name LPB -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name CLKSRC -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name ERRMSK -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name BOFFMSK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/CTRL1 -name PSEG2 -bitoffset 16  -width 3
imodeladdfield -mmregister $addBlock/CTRL1 -name PSEG1 -bitoffset 19  -width 3
imodeladdfield -mmregister $addBlock/CTRL1 -name RJW -bitoffset 22  -width 2
imodeladdfield -mmregister $addBlock/CTRL1 -name PRESDIV -bitoffset 24  -width 8    
 
imodeladdfield -mmregister $addBlock/TIMER -name TIMER -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/RXMGMASK -name MG -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/RX14MASK -name RX14M -bitoffset 0  -width 32   
 
imodeladdfield -mmregister $addBlock/RX15MASK -name RX15M -bitoffset 0  -width 32   
 
imodeladdfield -mmregister $addBlock/ECR -name TXERRCNT -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/ECR -name RXERRCNT -bitoffset 8  -width 8  
 
imodeladdfield -mmregister $addBlock/ESR1 -name WAKINT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name ERRINT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name BOFFINT -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name RX -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name FLTCONF -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/ESR1 -name TX -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name IDLE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name RXWRN -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name TXWRN -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name STFERR -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name FRMERR -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name CRCERR -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name ACKERR -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name BIT0ERR -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name BIT1ERR -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name RWRNINT -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name TWRNINT -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ESR1 -name SYNCH -bitoffset 18  -width 1   
 
imodeladdfield -mmregister $addBlock/IMASK2 -name BUFHM -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/IMASK1 -name BUFLM -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/IFLAG2 -name BUFHI -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/IFLAG1 -name BUF4TO0I -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/IFLAG1 -name BUF5I -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IFLAG1 -name BUF6I -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IFLAG1 -name BUF7I -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/IFLAG1 -name BUF31TO8I -bitoffset 8  -width 24 
 
imodeladdfield -mmregister $addBlock/CTRL2 -name EACEN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CTRL2 -name RRS -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/CTRL2 -name MRP -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/CTRL2 -name TASD -bitoffset 19  -width 5
imodeladdfield -mmregister $addBlock/CTRL2 -name RFFN -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/CTRL2 -name WRMFRZ -bitoffset 28  -width 1 
 
imodeladdfield -mmregister $addBlock/ESR2 -name IMB -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/ESR2 -name VPS -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/ESR2 -name LPTM -bitoffset 16  -width 7    
 
imodeladdfield -mmregister $addBlock/CRCR -name TXCRC -bitoffset 0  -width 15
imodeladdfield -mmregister $addBlock/CRCR -name MBCRC -bitoffset 16  -width 7   
 
imodeladdfield -mmregister $addBlock/RXFGMASK -name FGM -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/RXFIR -name IDHIT -bitoffset 0  -width 9   

# 8/25/2014 PRE - THe CS, ID, WORD0, and WORD1 are the mappings for the MB structure
# There are 255 of these needed, so not sure of the correct way to map these at 
# the current time. 
#imodeladdfield -mmregister $addBlock/CS -name TIME_STAMP -bitoffset 0  -width 4
#imodeladdfield -mmregister $addBlock/CS -name DLC -bitoffset 16  -width 1
#imodeladdfield -mmregister $addBlock/CS -name RTR -bitoffset 20  -width 1
#imodeladdfield -mmregister $addBlock/CS -name IDE -bitoffset 21  -width 1
#imodeladdfield -mmregister $addBlock/CS -name SRR -bitoffset 22  -width 1
#imodeladdfield -mmregister $addBlock/CS -name CODE -bitoffset 24  -width 1 
 
#imodeladdfield -mmregister $addBlock/ID -name EXT -bitoffset 0  -width 3
#imodeladdfield -mmregister $addBlock/ID -name STD -bitoffset 18  -width 1
#imodeladdfield -mmregister $addBlock/ID -name PRIO -bitoffset 29  -width 1 
 
#imodeladdfield -mmregister $addBlock/WORD0 -name DATA_BYTE_3 -bitoffset 0  -width 8
#imodeladdfield -mmregister $addBlock/WORD0 -name DATA_BYTE_2 -bitoffset 8  -width 1
#imodeladdfield -mmregister $addBlock/WORD0 -name DATA_BYTE_1 -bitoffset 16  -width 1
#imodeladdfield -mmregister $addBlock/WORD0 -name DATA_BYTE_0 -bitoffset 24  -width 1   
 
#imodeladdfield -mmregister $addBlock/WORD1 -name DATA_BYTE_7 -bitoffset 0  -width 8
#imodeladdfield -mmregister $addBlock/WORD1 -name DATA_BYTE_6 -bitoffset 8  -width 1
#imodeladdfield -mmregister $addBlock/WORD1 -name DATA_BYTE_5 -bitoffset 16  -width 1
#imodeladdfield -mmregister $addBlock/WORD1 -name DATA_BYTE_4 -bitoffset 24  -width 1   
 
imodeladdfield -mmregister $addBlock/RXIMR0 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR1 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR2 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR3 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR4 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR5 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR6 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR7 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR8 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR9 -name MI -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/RXIMR10 -name MI -bitoffset 0  -width 32   
imodeladdfield -mmregister $addBlock/RXIMR11 -name MI -bitoffset 0  -width 32   
imodeladdfield -mmregister $addBlock/RXIMR12 -name MI -bitoffset 0  -width 32   
imodeladdfield -mmregister $addBlock/RXIMR13 -name MI -bitoffset 0  -width 32   
imodeladdfield -mmregister $addBlock/RXIMR14 -name MI -bitoffset 0  -width 32   
imodeladdfield -mmregister $addBlock/RXIMR15 -name MI -bitoffset 0  -width 32
