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
set name    KinetisAXBS
set version 1.0
set desc "Model of the AXBS peripheral used on the Freescale Kinetis platform"
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
#imodeladdaddressblock -name ab     -size 0xf04 -port bport1 -width 32

imodeladdaddressblock -port bport1 -width 32 -name ab%u -size 0x100 -loarray 0 -hiarray 7 

imodeladdmmregister -name PRS -addressblock  bport1/ab%u -offset 0x0 -access rw -writemask 0x77777777
  imodeladdreset  -name Reset -value 0x76543210
  iadddocumentation -name Description -text "Priority Registers Slave, array offset: 0x0, array step: 0x100"
    imodeladdfield  -name M0 -bitoffset 0  -width 3
    imodeladdfield  -name M1 -bitoffset 4  -width 3
    imodeladdfield  -name M2 -bitoffset 8  -width 3
    imodeladdfield  -name M3 -bitoffset 12  -width 3
    imodeladdfield  -name M4 -bitoffset 16  -width 3
    imodeladdfield  -name M5 -bitoffset 20  -width 3
    imodeladdfield  -name M6 -bitoffset 24  -width 3
    imodeladdfield  -name M7 -bitoffset 28  -width 3   

imodeladdmmregister -name CRS -addressblock  bport1/ab%u -offset 0x10 -access rw -writemask 0x77777777
  imodeladdreset  -name Reset -value 0x00000337
  iadddocumentation -name Description -text "Control Register, array offset: 0x10, array step: 0x100"
    imodeladdfield  -name ARB -bitoffset 8  -width 2
    imodeladdfield  -name HLP -bitoffset 30  -width 1
    imodeladdfield  -name PARK -bitoffset 0  -width 3
    imodeladdfield  -name PCTL -bitoffset 4  -width 2
    imodeladdfield  -name RO -bitoffset 31  -width 1   

set registers { 
  
MGPCR0          0x000 rw - - - - 0 0x7 "Master General Purpose Control Register, offset: 0x800 "    
MGPCR1          0x100 rw - - - - 0 0x7 "Master General Purpose Control Register, offset: 0x900 "    
MGPCR2          0x200 rw - - - - 0 0x7 "Master General Purpose Control Register, offset: 0xA00 "    
MGPCR3          0x300 rw - - - - 0 0x7 "Master General Purpose Control Register, offset: 0xB00 "    
MGPCR6          0x600 rw - - - - 0 0x7 "Master General Purpose Control Register, offset: 0xE00 "    
MGPCR7          0x700 rw - - - - 0 0x7 "Master General Purpose Control Register, offset: 0xF00 "
}

imodeladdaddressblock -port bport1 -width 32 -name ac -size 0x800 -offset 0x800

set addBlock "bport1/ac"

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

imodeladdfield -mmregister $addBlock/MGPCR0 -name AULB -bitoffset 0  -width 3   
imodeladdfield -mmregister $addBlock/MGPCR1 -name AULB -bitoffset 0  -width 3   
imodeladdfield -mmregister $addBlock/MGPCR2 -name AULB -bitoffset 0  -width 3   
imodeladdfield -mmregister $addBlock/MGPCR3 -name AULB -bitoffset 0  -width 3   
imodeladdfield -mmregister $addBlock/MGPCR6 -name AULB -bitoffset 0  -width 3   
imodeladdfield -mmregister $addBlock/MGPCR7 -name AULB -bitoffset 0  -width 3
