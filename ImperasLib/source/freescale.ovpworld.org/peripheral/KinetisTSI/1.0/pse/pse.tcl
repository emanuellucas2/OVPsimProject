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
set name    KinetisTSI
set version 1.0
set desc "Model of the TSI peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x124 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
GENCS           0x00  rw - - - - 0x00000000 0x1ffff1f3 "General Control and Status Register, offset: 0x0 "  
SCANC           0x04  rw - - - - 0x00000000 0x0f0fff1f "SCAN Control Register, offset: 0x4 "    
PEN             0x08  rw - - - - 0x00000000 0x000fffff "Pin Enable Register, offset: 0x8 "  
WUCNTR          0x10  rw - - - - 0x00000000 0x00000000 "Wake-Up Channel Counter Register, offset: 0x10 "    
CNTR1           0x100 r  - - - - 0x00000000 - "Counter Register, offset: 0x100 "    
CNTR3           0x104 r  - - - - 0x00000000 - "Counter Register, offset: 0x104 "    
CNTR5           0x108 r  - - - - 0x00000000 - "Counter Register, offset: 0x108 "    
CNTR7           0x10c r  - - - - 0x00000000 - "Counter Register, offset: 0x10C "    
CNTR9           0x110 r  - - - - 0x00000000 - "Counter Register, offset: 0x110 "    
CNTR11          0x114 r  - - - - 0x00000000 - "Counter Register, offset: 0x114 "    
CNTR13          0x118 r  - - - - 0x00000000 - "Counter Register, offset: 0x118 "    
CNTR15          0x11c r  - - - - 0x00000000 - "Counter Register, offset: 0x11C "    
THRESHOLD       0x120 rw - - - - 0x00000000 0xfffffff "Low Power Channel Threshold Register, offset: 0x120 "
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

    
 
imodeladdfield -mmregister $addBlock/GENCS -name EOSF -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name ERIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name ESOR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name EXTERF -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name LPCLKS -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name LPSCNITV -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/GENCS -name NSCN -bitoffset 19  -width 5
imodeladdfield -mmregister $addBlock/GENCS -name OUTRGF -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name OVRF -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name PS -bitoffset 16  -width 3
imodeladdfield -mmregister $addBlock/GENCS -name SCNIP -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name STM -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name STPE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name SWTS -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name TSIEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/GENCS -name TSIIE -bitoffset 6  -width 1   
 
imodeladdfield -mmregister $addBlock/SCANC -name AMCLKS -bitoffset 3  -width 2
imodeladdfield -mmregister $addBlock/SCANC -name AMPSC -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/SCANC -name EXTCHRG -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/SCANC -name REFCHRG -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/SCANC -name SMOD -bitoffset 8  -width 8    
 
imodeladdfield -mmregister $addBlock/PEN -name LPSP -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PEN -name PEN0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PEN -name PEN9 -bitoffset 9  -width 1  
 
imodeladdfield -mmregister $addBlock/WUCNTR -name WUCNT -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/CNTR1 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR1 -name CTN1 -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/CNTR3 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR3 -name CTN1 -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/CNTR5 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR5 -name CTN1 -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/CNTR7 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR7 -name CTN1 -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/CNTR9 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR9 -name CTN1 -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/CNTR11 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR11 -name CTN1 -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/CNTR13 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR13 -name CTN1 -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/CNTR15 -name CTN -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CNTR15 -name CTN1 -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/THRESHOLD -name HTHH -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/THRESHOLD -name LTHH -bitoffset 16  -width 16
