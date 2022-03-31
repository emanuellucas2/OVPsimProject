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
set name    VybridGPIO
set version 1.0
set desc "Model of the GPIO peripheral used on the Freescale Vybrid platform"
set limitations "Provides the base behaviour for the OVP Freescale Vybrid platforms"

set range 0x40

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
imodeladdaddressblock -name ab     -size 0x14 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
PDOR            0x00 rw - - - - 0x0 0xffffffff "Port Data Output Register, offset: 0x0"	
PSOR            0x04 w  - writePSOR - - 0x0 0xffffffff "Port Set Output Register, offset: 0x4"	
PCOR            0x08 w  - writePCOR - - 0x0 0xffffffff "Port Clear Output Register, offset: 0x8"	
PTOR            0x0c w  - writePTOR - - 0x0 0xffffffff "Port Toggle Output Register, offset: 0xC"	
PDIR            0x10 r  - - - - 0x0 - "Port Data Input Register, offset: 0x10"
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

	
 
imodeladdfield -mmregister $addBlock/PDOR -name PDO -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/PSOR -name PTSO -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/PCOR -name PTCO -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/PTOR -name PTTO -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/PDIR -name PDI -bitoffset 0  -width 32
