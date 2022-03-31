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
set name    KinetisI2S
set version 1.0
set desc "Model of the I2S peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x108 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
TCSR            0x00 rw - - - - 0x00000000 0xf31c1f03 "SAI Transmit Control Register, offset: 0x0 " 
TCR1            0x04 rw - - - - 0x00000000 0x00000007 "SAI Transmit Configuration 1 Register, offset: 0x4 " 
TCR2            0x08 rw - - - - 0x00000000 0xff0000ff "SAI Transmit Configuration 2 Register, offset: 0x8 " 
TCR3            0x0c rw - - - - 0x00000000 0x0003001f "SAI Transmit Configuration 3 Register, offset: 0xC " 
TCR4            0x10 rw - - - - 0x00000000 0x001f1f1b "SAI Transmit Configuration 4 Register, offset: 0x10 "    
TCR5            0x14 rw - - - - 0x00000000 0x1f1f1f00 "SAI Transmit Configuration 5 Register, offset: 0x14 "    
TDR0            0x20 w  - - - - 0x00000000 0xffffffff "SAI Transmit Data Register, array offset: 0x20, array step: 0x4 "    
TDR1            0x24 w  - - - - 0x00000000 0xffffffff "SAI Transmit Data Register, array offset: 0x20, array step: 0x4 "    
TFR0            0x40 r  - - - - 0x00000000 - "SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 " 
TFR1            0x44 r  - - - - 0x00000000 - "SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 " 
TMR             0x60 rw - - - - 0x00000000 0xffffffff "SAI Transmit Mask Register, offset: 0x60 "   
RCSR            0x80 rw - - - - 0x00000000 0xf31c1f03 "SAI Receive Control Register, offset: 0x80 " 
RCR1            0x84 rw - - - - 0x00000000 0x00000007 "SAI Receive Configuration 1 Register, offset: 0x84 " 
RCR2            0x88 rw - - - - 0x00000000 0xff0000ff "SAI Receive Configuration 2 Register, offset: 0x88 " 
RCR3            0x8c rw - - - - 0x00000000 0x0003001f "SAI Receive Configuration 3 Register, offset: 0x8C " 
RCR4            0x90 rw - - - - 0x00000000 0x001f1f1b "SAI Receive Configuration 4 Register, offset: 0x90 " 
RCR5            0x94 rw - - - - 0x00000000 0x1f1f1f00 "SAI Receive Configuration 5 Register, offset: 0x94 " 
RDR0            0xa0 r  - - - - 0x00000000 - "SAI Receive Data Register, array offset: 0xA0, array step: 0x4 "  
RDR1            0xa4 r  - - - - 0x00000000 - "SAI Receive Data Register, array offset: 0xA0, array step: 0x4 "  
RFR0            0xc0 r  - - - - 0x00000000 - "SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 "  
RFR1            0xc4 r  - - - - 0x00000000 - "SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 "  
RMR             0xe0 rw - - - - 0x00000000 0xffffffff "SAI Receive Mask Register, offset: 0xE0 "    
MCR             0x100 rw - - - - 0x00000000 0x43000000 "SAI MCLK Control Register, offset: 0x100 "  
MDR             0x104 rw - - - - 0x00000000 0x000fffff "MCLK Divide Register, offset: 0x104 "
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

    
 
imodeladdfield -mmregister $addBlock/TCSR -name BCE -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name DBGE -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FEF -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FEIE -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FR -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FRDE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FRF -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FRIE -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FWDE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FWF -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name FWIE -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name SEF -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name SEIE -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name SR -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name STOPE -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name TE -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name WSF -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/TCSR -name WSIE -bitoffset 12  -width 1    
 
imodeladdfield -mmregister $addBlock/TCR1 -name TFW -bitoffset 0  -width 3  
 
imodeladdfield -mmregister $addBlock/TCR2 -name BCD -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/TCR2 -name BCI -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/TCR2 -name BCP -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/TCR2 -name BCS -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/TCR2 -name DIV -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/TCR2 -name MSEL -bitoffset 26  -width 2
imodeladdfield -mmregister $addBlock/TCR2 -name SYNC -bitoffset 30  -width 2    
 
imodeladdfield -mmregister $addBlock/TCR3 -name TCE -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/TCR3 -name WDFL -bitoffset 0  -width 5 
 
imodeladdfield -mmregister $addBlock/TCR4 -name FRSZ -bitoffset 16  -width 5
imodeladdfield -mmregister $addBlock/TCR4 -name FSD -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCR4 -name FSE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/TCR4 -name FSP -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/TCR4 -name MF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/TCR4 -name SYWD -bitoffset 8  -width 5 
 
imodeladdfield -mmregister $addBlock/TCR5 -name FBT -bitoffset 8  -width 5
imodeladdfield -mmregister $addBlock/TCR5 -name W0W -bitoffset 16  -width 5
imodeladdfield -mmregister $addBlock/TCR5 -name WNW -bitoffset 24  -width 5 
 
imodeladdfield -mmregister $addBlock/TDR0 -name TDR -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/TDR1 -name TDR -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/TFR0 -name RFP -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/TFR0 -name WFP -bitoffset 16  -width 4 
 
imodeladdfield -mmregister $addBlock/TFR1 -name RFP -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/TFR1 -name WFP -bitoffset 16  -width 4 
 
imodeladdfield -mmregister $addBlock/TMR -name TWM -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/RCSR -name BCE -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name DBGE -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FEF -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FEIE -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FR -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FRDE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FRF -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FRIE -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FWDE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FWF -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name FWIE -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name RE -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name SEF -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name SEIE -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name SR -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name STOPE -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name WSF -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/RCSR -name WSIE -bitoffset 12  -width 1    
 
imodeladdfield -mmregister $addBlock/RCR1 -name RFW -bitoffset 0  -width 3  
 
imodeladdfield -mmregister $addBlock/RCR2 -name BCD -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/RCR2 -name BCI -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/RCR2 -name BCP -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/RCR2 -name BCS -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/RCR2 -name DIV -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/RCR2 -name MSEL -bitoffset 26  -width 2
imodeladdfield -mmregister $addBlock/RCR2 -name SYNC -bitoffset 30  -width 2    
 
imodeladdfield -mmregister $addBlock/RCR3 -name RCE -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/RCR3 -name WDFL -bitoffset 0  -width 5 
 
imodeladdfield -mmregister $addBlock/RCR4 -name FRSZ -bitoffset 16  -width 5
imodeladdfield -mmregister $addBlock/RCR4 -name FSD -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/RCR4 -name FSE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/RCR4 -name FSP -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/RCR4 -name MF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/RCR4 -name SYWD -bitoffset 8  -width 5 
 
imodeladdfield -mmregister $addBlock/RCR5 -name FBT -bitoffset 8  -width 5
imodeladdfield -mmregister $addBlock/RCR5 -name W0W -bitoffset 16  -width 5
imodeladdfield -mmregister $addBlock/RCR5 -name WNW -bitoffset 24  -width 5 
 
imodeladdfield -mmregister $addBlock/RDR0 -name RDR -bitoffset 0  -width 32 
imodeladdfield -mmregister $addBlock/RDR1 -name RDR -bitoffset 0  -width 32 

imodeladdfield -mmregister $addBlock/RFR0 -name RFP -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/RFR0 -name WFP -bitoffset 16  -width 4 
imodeladdfield -mmregister $addBlock/RFR1 -name RFP -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/RFR1 -name WFP -bitoffset 16  -width 4 
 
imodeladdfield -mmregister $addBlock/RMR -name RWM -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/MCR -name DUF -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/MCR -name MICS -bitoffset 24  -width 2
imodeladdfield -mmregister $addBlock/MCR -name MOE -bitoffset 30  -width 1  
 
imodeladdfield -mmregister $addBlock/MDR -name DIVIDE -bitoffset 0  -width 12
imodeladdfield -mmregister $addBlock/MDR -name FRACT -bitoffset 12  -width 8
