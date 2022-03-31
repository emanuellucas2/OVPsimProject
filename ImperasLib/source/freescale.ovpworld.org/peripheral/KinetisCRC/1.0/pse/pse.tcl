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
set name    KinetisCRC
set version 1.0
set desc "Model of the CRC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x0c -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CRC             0x00 rw - - - - 0xffffffff 0xffffffff "CRC Data Register, offset: 0x0 " 
GPOLY           0x04 rw - - - - 0x00001021 0xffffffff "CRC Polynomial Register, offset: 0x4 "   
CTRL            0x08 rw - - - - 0x00000000 0xf7000000 "CRC Control Register, offset: 0x8 "  
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

    
imodeladdfield -mmregister $addBlock/CRC -name LL -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CRC -name LU -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/CRC -name HL -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CRC -name HU -bitoffset 24  -width 8   
 
imodeladdfield -mmregister $addBlock/GPOLY -name LOW -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/GPOLY -name HIGH -bitoffset 16  -width 16  
 
imodeladdfield -mmregister $addBlock/CTRL -name TCRC -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name WAS -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name FXOR -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/CTRL -name TOTR -bitoffset 28  -width 2
imodeladdfield -mmregister $addBlock/CTRL -name TOT -bitoffset 30  -width 2 
 
