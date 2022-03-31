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
set name    KinetisFTFE
set version 1.0
set desc "Model of the FTFE peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x18 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
FSTAT           0x00 rw - - - - 0x00 0xf0 "Flash Status Register, offset: 0x0 " 
FCNFG           0x01 rw - - - - 0x00 0xd0 "Flash Configuration Register, offset: 0x1 "  
FSEC            0x02 r  - - - - -    -    "Flash Security Register, offset: 0x2 "   
FOPT            0x03 r  - - - - -    -    "Flash Option Register, offset: 0x3 " 
FCCOB3          0x04 rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0x4 " 
FCCOB2          0x05 rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0x5 " 
FCCOB1          0x06 rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0x6 " 
FCCOB0          0x07 rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0x7 " 
FCCOB7          0x08 rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0x8 " 
FCCOB6          0x09 rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0x9 " 
FCCOB5          0x0a rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0xA " 
FCCOB4          0x0b rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0xB " 
FCCOBB          0x0c rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0xC " 
FCCOBA          0x0d rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0xD " 
FCCOB9          0x0e rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0xE " 
FCCOB8          0x0f rw - - - - 0x00 0xff "Flash Common Command Object Registers, offset: 0xF " 
FPROT3          0x10 rw - - - - -    0xff "Program Flash Protection Registers, offset: 0x10 "   
FPROT2          0x11 rw - - - - -    0xff "Program Flash Protection Registers, offset: 0x11 "   
FPROT1          0x12 rw - - - - -    0xff "Program Flash Protection Registers, offset: 0x12 "   
FPROT0          0x13 rw - - - - -    0xff "Program Flash Protection Registers, offset: 0x13 "   
FEPROT          0x16 rw - - - - -    0xff "EEPROM Protection Register, offset: 0x16 "   
FDPROT          0x17 rw - - - - -    0xff "Data Flash Protection Register, offset: 0x17 "
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

    
 
imodeladdfield -mmregister $addBlock/FSTAT -name ACCERR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/FSTAT -name CCIF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FSTAT -name FPVIOL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/FSTAT -name MGSTAT0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/FSTAT -name RDCOLERR -bitoffset 6  -width 1    
 
imodeladdfield -mmregister $addBlock/FCNFG -name CCIE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name EEERDY -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name ERSAREQ -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name ERSSUSP -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name PFLSH -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name RAMRDY -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name RDCOLLIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/FCNFG -name SWAP -bitoffset 3  -width 1    
 
imodeladdfield -mmregister $addBlock/FSEC -name FSLACC -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/FSEC -name KEYEN -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/FSEC -name MEEN -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/FSEC -name SEC -bitoffset 0  -width 2  
 
imodeladdfield -mmregister $addBlock/FOPT -name OPT -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/FCCOB3 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB2 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB1 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB0 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB7 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB5 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB4 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOBB -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOBA -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB9 -name CCOBn -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FCCOB8 -name CCOBn -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/FPROT3 -name PROT -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/FPROT2 -name PROT -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/FPROT1 -name PROT -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/FPROT0 -name PROT -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/FEPROT -name EPROT -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/FDPROT -name DPROT -bitoffset 0  -width 8
