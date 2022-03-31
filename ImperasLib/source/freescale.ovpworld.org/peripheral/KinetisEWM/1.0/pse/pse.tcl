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
set name    KinetisEWM
set version 1.0
set desc "Model of the EWM peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x04 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CTRL            0x00 rw - - - - 0x00 0x0f "Control Register, offset: 0x0 "  
SERV            0x01 w  - - - - 0x00 0xff "Service Register, offset: 0x1 "  
CMPL            0x02 rw - - - - 0x00 0xff "Compare Low Register, offset: 0x2 "  
CMPH            0x03 rw - - - - 0xff 0xff "Compare High Register, offset: 0x3 "
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

    
 
imodeladdfield -mmregister $addBlock/CTRL -name ASSIN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name EWMEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name INEN -bitoffset 2  -width 1 
imodeladdfield -mmregister $addBlock/CTRL -name INTEN -bitoffset 3  -width 1    
 
imodeladdfield -mmregister $addBlock/SERV -name SERVICE -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/CMPL -name COMPAREL -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/CMPH -name COMPAREH -bitoffset 0  -width 8
