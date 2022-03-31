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
set name    KinetisPMC
set version 1.0
set desc "Model of the PMC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x03 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
LVDSC1          0x00 rw - - - - 0x10 0x73 "Low Voltage Detect Status and Control 1 Register, offset: 0x0 "  
LVDSC2          0x01 rw - - - - 0x00 0x63 "Low Voltage Detect Status and Control 2 Register, offset: 0x1 "  
REGSC           0x02 rw - - - - 0x04 0x09 "Regulator Status and Control Register, offset: 0x2 "
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

    
 
imodeladdfield -mmregister $addBlock/LVDSC1 -name LVDACK -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/LVDSC1 -name LVDF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/LVDSC1 -name LVDIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/LVDSC1 -name LVDRE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/LVDSC1 -name LVDV -bitoffset 0  -width 2   
 
imodeladdfield -mmregister $addBlock/LVDSC2 -name LVWACK -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/LVDSC2 -name LVWF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/LVDSC2 -name LVWIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/LVDSC2 -name LVWV -bitoffset 0  -width 2   
 
imodeladdfield -mmregister $addBlock/REGSC -name ACKISO -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/REGSC -name BGBE -bitoffset 0  -width 1
# 08-30-2014 PRE - Register BGEN not in documentation
imodeladdfield -mmregister $addBlock/REGSC -name BGEN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/REGSC -name REGONS -bitoffset 2  -width 1
