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
set name    KinetisMCG
set version 1.0
set desc "Freescale Multipurpose Clock Generator"
set limitations "Only models status register reads, based on writes to configuration registers

atc register ATME bit is modeled as RAZ/WI"
set reference "Freescale Kinetis MCG"

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
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference -text $reference

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x13 -port bport1 -width 8

set addBlock     "bport1/ab"


# Changed reset val of S from 0x10 and SC from 0x02, and SC mask from 0xde as needed for MQX startup
#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
C1              0x00 rw - - - - 0x04 0xff "MCG Control 1 Register, offset: 0x0 "	
C2              0x01 rw - - - - 0x80 0xbf "MCG Control 2 Register, offset: 0x1 "	
C3              0x02 rw - - - - -    0xff "MCG Control 3 Register, offset: 0x2 "	
C4              0x03 rw - - - - 0x00 0xff "MCG Control 4 Register, offset: 0x3 "	
C5              0x04 rw - - - - 0x00 0xe7 "MCG Control 5 Register, offset: 0x4 "	
C6              0x05 rw - - - - 0x00 0xff "MCG Control 6 Register, offset: 0x5 "	
S               0x06 r  readS - viewS - 0x6a -    "MCG Status Register, offset: 0x6 "	
SC              0x08 rw - - - - 0x00 0x40 "MCG Status and Control Register, offset: 0x8 "	
ATCVH           0x0a rw - - - - 0x00 0xff "MCG Auto Trim Compare Value High Register, offset: 0xA "	
ATCVL           0x0b rw - - - - 0x00 0xff "MCG Auto Trim Compare Value Low Register, offset: 0xB "	
C7              0x0c rw - - - - 0x00 0x01 "MCG Control 7 Register, offset: 0xC "	
C8              0x0d rw - - - - 0x00 0xa0 "MCG Control 8 Register, offset: 0xD "	
C10             0x0f rw - - - - 0x80 0xbc "MCG Control 10 Register, offset: 0xF "	
C11             0x10 rw - - - - 0x00 0xf7 "MCG Control 11 Register, offset: 0x10 "	
C12             0x11 rw - - - - 0x00 0xbf "MCG Control 12 Register, offset: 0x11 "	
S2              0x12 r  - - - - 0x00 - "MCG Status 2 Register, offset: 0x12 "
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

	
 
imodeladdfield -mmregister $addBlock/C1 -name CLKS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/C1 -name FRDIV -bitoffset 3  -width 3
imodeladdfield -mmregister $addBlock/C1 -name IRCLKEN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/C1 -name IREFS -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C1 -name IREFSTEN -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/C2 -name EREFS0 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C2 -name HGO0 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C2 -name IRCS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C2 -name LOCRE0 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C2 -name LP -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/C2 -name RANGE0 -bitoffset 4  -width 2	
 
imodeladdfield -mmregister $addBlock/C3 -name SCTRIM -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/C4 -name DMX32 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C4 -name DRST_DRS -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/C4 -name FCTRIM -bitoffset 1  -width 4
imodeladdfield -mmregister $addBlock/C4 -name SCFTRIM -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/C5 -name PLLCLKEN0 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C5 -name PLLREFSEL0 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C5 -name PLLSTEN0 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C5 -name PRDIV0 -bitoffset 0  -width 3	
 
imodeladdfield -mmregister $addBlock/C6 -name CME0 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C6 -name LOLIE0 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C6 -name PLLS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C6 -name VDIV0 -bitoffset 0  -width 5	
 
imodeladdfield -mmregister $addBlock/S -name CLKST -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/S -name IRCST -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S -name IREFST -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/S -name LOCK0 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/S -name LOLS0 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/S -name OSCINIT0 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S -name PLLST -bitoffset 5  -width 1	
 
imodeladdfield -mmregister $addBlock/SC -name ATME -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC -name ATMF -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SC -name ATMS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SC -name FCIRDIV -bitoffset 1  -width 3
imodeladdfield -mmregister $addBlock/SC -name FLTPRSRV -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SC -name LOCS0 -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/ATCVH -name ATCVH -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/ATCVL -name ATCVL -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/C7 -name OSCSEL -bitoffset 0  -width 1	
 
# 8-31-2014 PRE - Documentation has 1's the .h had 2's and 3's in the name.
imodeladdfield -mmregister $addBlock/C8 -name CME1 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C8 -name LOCRE1 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C8 -name LOCS1 -bitoffset 0  -width 1	
 	
# 8-31-2014 PRE - Documentation has 1's the .h had 2's in the name.
imodeladdfield -mmregister $addBlock/C10 -name EREFS1 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C10 -name HGO1 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C10 -name LOCRE2 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C10 -name RANGE1 -bitoffset 4  -width 2	
 
# 8-31-2014 PRE - Documentation has 1's the .h had 2's in the name.
imodeladdfield -mmregister $addBlock/C11 -name PLLCLKEN1 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C11 -name PLLCS -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C11 -name PLLREFSEL1 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C11 -name PLLSTEN1 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C11 -name PRDIV1 -bitoffset 0  -width 3	
 
# 8-31-2014 PRE - Documentation has LOLIE1, VDIV1, .h had 2's in the name.
imodeladdfield -mmregister $addBlock/C12 -name CME2 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C12 -name LOLIE1 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C12 -name VDIV1 -bitoffset 0  -width 5	
 
imodeladdfield -mmregister $addBlock/S2 -name LOCK2 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/S2 -name LOCS2 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S2 -name LOLS2 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/S2 -name OSCINIT2 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S2 -name PLLCST -bitoffset 4  -width 1
