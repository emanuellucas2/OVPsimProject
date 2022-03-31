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
set name    VybridLCD
set version 1.0
set desc "Model of the LCD peripheral used on the Freescale Vybrid platform"
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
imodeladdaddressblock -name ab     -size 0x60 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
LCDCR         0x00 rw - - - - 0x00000000 0xffffff37 "LCD Control Register, offset: 0x0"	
LCDPCR        0x04 rw - - - - 0x00000000 0x0f000000 "LCD Prescaler Control Register, offset: 0x4"	
LCDCCR        0x08 rw - - - - 0x00000000 0x87ff0000 "LCD Contrast Control Register, offset: 0x8"	
ENFPR0        0x10 rw - - - - 0x00000000 0xffffffff "LCD Frontplane Enable Register 0, offset: 0x10"	
ENFPR1        0x14 rw - - - - 0x00000000 0xffffffff "LCD Frontplane Enable Register 1, offset: 0x14"	
LCDRAM0       0x20 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x20"	
LCDRAM1       0x24 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x24"	
LCDRAM2       0x28 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x28"	
LCDRAM3       0x2c rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x2C"	
LCDRAM4       0x30 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x30"	
LCDRAM5       0x34 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x34"	
LCDRAM6       0x38 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x38"	
LCDRAM7       0x3c rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x3C"	
LCDRAM8       0x40 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x40"	
LCDRAM9       0x44 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x44"	
LCDRAM10      0x48 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x48"	
LCDRAM11      0x4c rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x4c"	
LCDRAM12      0x50 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x50"	
LCDRAM13      0x54 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x54"	
LCDRAM14      0x58 rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x58"	
LCDRAM15      0x5c rw - - - - 0x00000000 0xffffffff "LCDRAM, offset: 0x5c"	
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
 
imodeladdfield -mmregister $addBlock/LCDCR -name BIAS -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name BSTAO -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name BSTEN -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name BSTSEL -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name DUTY -bitoffset 26  -width 3
imodeladdfield -mmregister $addBlock/LCDCR -name EOF -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name LCDBPA -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/LCDCR -name LCDBPS -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/LCDCR -name LCDEN -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name LCDINT -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name LCDOCS -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name LCDRCS -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name LCDRST -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/LCDCR -name NOF -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDCR -name PWR -bitoffset 22  -width 2
imodeladdfield -mmregister $addBlock/LCDCR -name VLCDS -bitoffset 24  -width 1	
 
imodeladdfield -mmregister $addBlock/LCDPCR -name LCLK -bitoffset 24  -width 4	
 
imodeladdfield -mmregister $addBlock/LCDCCR -name CCEN -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/LCDCCR -name LCC -bitoffset 16  -width 11	
 
imodeladdfield -mmregister $addBlock/ENFPR0 -name ENFP -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/ENFPR1 -name ENFP -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/LCDRAM0 -name FP0_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM0 -name FP1_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM0 -name FP2_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM0 -name FP3_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM1 -name FP4_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM1 -name FP5_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM1 -name FP6_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM1 -name FP7_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM2 -name FP10_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM2 -name FP11_BP -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM2 -name FP8_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM2 -name FP9_BP -bitoffset 16  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM3 -name FP12_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM3 -name FP13_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM3 -name FP14_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM3 -name FP15_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM4 -name FP16_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM4 -name FP17_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM4 -name FP18_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM4 -name FP19_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM5 -name FP20_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM5 -name FP21_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM5 -name FP22_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM5 -name FP23_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM6 -name FP24_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM6 -name FP25_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM6 -name FP26_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM6 -name FP27_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM7 -name FP28_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM7 -name FP29_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM7 -name FP30_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM7 -name FP31_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM8 -name FP32_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM8 -name FP33_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM8 -name FP34_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM8 -name FP35_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM9 -name FP36_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM9 -name FP37_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM9 -name FP38_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM9 -name FP39_BP -bitoffset 0  -width 8	

# 11/26/2014 PRE: Documentation only had LCDRAM1-9, .h file had thru 15, so put 
# them all in.
imodeladdfield -mmregister $addBlock/LCDRAM10 -name FP40_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM10 -name FP41_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM10 -name FP42_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM10 -name FP43_BP -bitoffset 0  -width 8	

imodeladdfield -mmregister $addBlock/LCDRAM11 -name FP44_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM11 -name FP45_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM11 -name FP46_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM11 -name FP47_BP -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/LCDRAM12 -name FP48_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM12 -name FP49_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM12 -name FP50_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM12 -name FP51_BP -bitoffset 0  -width 8	

imodeladdfield -mmregister $addBlock/LCDRAM13 -name FP52_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM13 -name FP53_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM13 -name FP54_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM13 -name FP55_BP -bitoffset 0  -width 8	

imodeladdfield -mmregister $addBlock/LCDRAM14 -name FP56_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM14 -name FP57_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM14 -name FP58_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM14 -name FP59_BP -bitoffset 0  -width 8	

imodeladdfield -mmregister $addBlock/LCDRAM15 -name FP60_BP -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM15 -name FP61_BP -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM15 -name FP62_BP -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/LCDRAM15 -name FP63_BP -bitoffset 0  -width 8	
