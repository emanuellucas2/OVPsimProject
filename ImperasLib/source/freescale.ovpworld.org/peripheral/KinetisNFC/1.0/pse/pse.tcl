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
set name    KinetisNFC
set version 1.0
set desc "Model of the NFC peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

set range 0x4000

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
imodeladdaddressblock -name ab     -size 0x3c -port bport1 -width 32 -offset 0x3f00

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CMD1            0x00 rw - - - - 0x30ff0000 0xffff0000 "Flash command 1, offset: 0x3F00 "    
CMD2            0x04 rw - - - - 0x007ee000 0xffffff07 "Flash command 2, offset: 0x3F04 "    
CAR             0x08 rw - - - - 0x00000000 0x0000ffff "Column address, offset: 0x3F08 " 
RAR             0x0c rw - - - - 0x11000000 0x33ffffff "Row address, offset: 0x3F0C "    
RPT             0x10 rw - - - - 0x00000000 0x0000ffff "Flash command repeat, offset: 0x3F10 "   
RAI             0x14 rw - - - - 0x00000000 0x00ffffff "Row address increment, offset: 0x3F14 "  
SR1             0x18 r  - - - - 0x00000000 - "Flash status 1, offset: 0x3F18 "  
SR2             0x1c r  - - - - 0x00000000 - "Flash status 2, offset: 0x3F1C "  
DMA1            0x20 rw - - - - 0x00000000 0xffffffff "DMA channel 1 address, offset: 0x3F20 "  
DMACFG          0x24 rw - - - - 0x00000000 0xfffffe03 "DMA configuration, offset: 0x3F24 "  
SWAP            0x28 rw - - - - 0x0ffe0ffe 0x0fff0ffe "Cach swap, offset: 0x3F28 "  
SECSZ           0x2c rw - - - - 0x00000420 0x00001fff "Sector size, offset: 0x3F2C "    
CFG             0x30 rw - - - - 0x000ea631 0xffffffbf "Flash configuration, offset: 0x3F30 "    
DMA2            0x34 rw - - - - 0x00000000 0xffffffff "DMA channel 2 address, offset: 0x3F34 "  
ISR             0x38 rw - - - - 0x60000000 0x007e0000 "Interrupt status, offset: 0x3F38 "
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

    
 
imodeladdfield -mmregister $addBlock/CMD1 -name BYTE2 -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/CMD1 -name BYTE3 -bitoffset 16  -width 8   
 
imodeladdfield -mmregister $addBlock/CMD2 -name BUFNO -bitoffset 1  -width 2
imodeladdfield -mmregister $addBlock/CMD2 -name BUSY_START -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CMD2 -name BYTE1 -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/CMD2 -name CODE -bitoffset 8  -width 16    
 
imodeladdfield -mmregister $addBlock/CAR -name BYTE1 -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CAR -name BYTE2 -bitoffset 8  -width 8 
 
imodeladdfield -mmregister $addBlock/RAR -name BYTE1 -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/RAR -name BYTE2 -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/RAR -name BYTE3 -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/RAR -name CS0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/RAR -name CS1 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/RAR -name RB0 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/RAR -name RB1 -bitoffset 25  -width 1  
 
imodeladdfield -mmregister $addBlock/RPT -name COUNT -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/RAI -name INC1 -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/RAI -name INC2 -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/RAI -name INC3 -bitoffset 16  -width 8 
 
imodeladdfield -mmregister $addBlock/SR1 -name ID1 -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/SR1 -name ID2 -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/SR1 -name ID3 -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/SR1 -name ID4 -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/SR2 -name ID5 -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/SR2 -name STATUS1 -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/DMA1 -name ADDRESS -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/DMACFG -name ACT1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/DMACFG -name ACT2 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/DMACFG -name COUNT1 -bitoffset 20  -width 12
imodeladdfield -mmregister $addBlock/DMACFG -name COUNT2 -bitoffset 13  -width 7
imodeladdfield -mmregister $addBlock/DMACFG -name OFFSET2 -bitoffset 9  -width 4    
 
imodeladdfield -mmregister $addBlock/SWAP -name ADDR1 -bitoffset 17  -width 11
imodeladdfield -mmregister $addBlock/SWAP -name ADDR2 -bitoffset 1  -width 11   
 
imodeladdfield -mmregister $addBlock/SECSZ -name SIZE -bitoffset 0  -width 13   
 
imodeladdfield -mmregister $addBlock/CFG -name AIAD -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CFG -name AIBN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CFG -name BITWIDTH -bitoffset 7  -width 1
# 08-31-2014 PRE: BTMD Not in documentation
imodeladdfield -mmregister $addBlock/CFG -name BTMD -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/CFG -name DMAREQ -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/CFG -name ECCAD -bitoffset 22  -width 9
imodeladdfield -mmregister $addBlock/CFG -name ECCMODE -bitoffset 17  -width 3
imodeladdfield -mmregister $addBlock/CFG -name ECCSRAM -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/CFG -name FAST -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CFG -name IDCNT -bitoffset 13  -width 3
imodeladdfield -mmregister $addBlock/CFG -name PAGECNT -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CFG -name STOPWERR -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/CFG -name TIMEOUT -bitoffset 8  -width 5   
 
imodeladdfield -mmregister $addBlock/DMA2 -name ADDRESS -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/ISR -name CMDBUSY -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/ISR -name DMABN -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/ISR -name DMABUSY -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ISR -name DONE -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/ISR -name DONECLR -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/ISR -name DONEEN -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ISR -name ECCBN -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/ISR -name ECCBUSY -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/ISR -name IDLE -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/ISR -name IDLECLR -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ISR -name IDLEEN -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/ISR -name RESBN -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/ISR -name RESBUSY -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/ISR -name WERR -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/ISR -name WERRCLR -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/ISR -name WERREN -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ISR -name WERRNS -bitoffset 27  -width 1
