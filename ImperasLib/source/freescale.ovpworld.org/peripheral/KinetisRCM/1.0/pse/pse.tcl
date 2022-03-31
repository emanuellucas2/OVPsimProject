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
set name    KinetisRCM
set version 1.0
set desc "Model of the RCM peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x08 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
SRS0            0x00 r  - - - - 0x82 -    "System Reset Status Register 0, offset: 0x0 "    
SRS1            0x01 r  - - - - 0x00 -    "System Reset Status Register 1, offset: 0x1 "    
RPFC            0x04 rw - - - - 0x00 0x07 "Reset Pin Filter Control Register, offset: 0x4 " 
RPFW            0x05 rw - - - - 0x00 0x1f "Reset Pin Filter Width Register, offset: 0x5 "   
MR              0x07 r  - - - - 0x00 -    "Mode Register, offset: 0x7 "
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

    
 
imodeladdfield -mmregister $addBlock/SRS0 -name LOC -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SRS0 -name LVD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SRS0 -name PIN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SRS0 -name POR -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SRS0 -name WAKEUP -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SRS0 -name WDOG -bitoffset 5  -width 1 
 
imodeladdfield -mmregister $addBlock/SRS1 -name EZPT -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SRS1 -name JTAG -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SRS1 -name LOCKUP -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SRS1 -name MDM_AP -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SRS1 -name SACKERR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SRS1 -name SW -bitoffset 2  -width 1
# 8-30-2014 PRE - Regsiter TAMPER not in documentation.
imodeladdfield -mmregister $addBlock/SRS1 -name TAMPER -bitoffset 7  -width 1   
 
imodeladdfield -mmregister $addBlock/RPFC -name RSTFLTSRW -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/RPFC -name RSTFLTSS -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/RPFW -name RSTFLTSEL -bitoffset 0  -width 5    
 
imodeladdfield -mmregister $addBlock/MR -name EZP_MS -bitoffset 1  -width 1
