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
set name    KinetisRFVBAT
set version 1.0
set desc "Model of the RFVBAT peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x20 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
REGA            0x00 rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGB            0x04 rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGC            0x08 rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGD            0x0c rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGE            0x10 rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGF            0x14 rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGG            0x18 rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "  
REGH            0x1c rw - - - - 0 - "VBAT register file register, array offset: 0x0, array step: 0x4 "
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

    
 
imodeladdfield -mmregister $addBlock/REGA -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGA -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGA -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGA -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGB -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGB -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGB -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGB -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGC -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGC -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGC -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGC -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGD -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGD -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGD -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGD -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGE -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGE -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGE -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGE -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGF -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGF -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGF -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGF -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGG -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGG -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGG -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGG -name LL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/REGH -name HH -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/REGH -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/REGH -name LH -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/REGH -name LL -bitoffset 0  -width 8
