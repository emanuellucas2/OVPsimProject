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
set name    KinetisUSBDCD
set version 1.0
set desc "Model of the USBDCD peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x1c -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CONTROL         0x00 rw - - - - 0x00010000 0x03010001 "Control Register, offset: 0x0 "  
CLOCK           0x04 rw - - - - 0x000000c1 0x00000ffd "Clock Register, offset: 0x4 "    
STATUS          0x08 r  - - - - 0x00000000 - "Status Register, offset: 0x8 "    
TIMER0          0x10 rw - - - - 0x00100000 0x01ff0000 "TIMER0 Register, offset: 0x10 "  
TIMER1          0x14 rw - - - - 0x000a0028 0x03ff03ff "TIMER1 Register, offset: 0x14"   
TIMER2          0x18 rw - - - - 0x0028000a 0x03ff000f "TIMER2 Register, offset: 0x18 "
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

    
 
imodeladdfield -mmregister $addBlock/CONTROL -name IACK -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CONTROL -name IE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CONTROL -name IF -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CONTROL -name SR -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/CONTROL -name START -bitoffset 24  -width 1    
 
imodeladdfield -mmregister $addBlock/CLOCK -name CLOCK_SPEED -bitoffset 2  -width 10
imodeladdfield -mmregister $addBlock/CLOCK -name CLOCK_UNIT -bitoffset 0  -width 1  
 
imodeladdfield -mmregister $addBlock/STATUS -name ACTIVE -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name ERR -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name SEQ_RES -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/STATUS -name SEQ_STAT -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/STATUS -name TO -bitoffset 21  -width 1    
 
imodeladdfield -mmregister $addBlock/TIMER0 -name TSEQ_INIT -bitoffset 16  -width 10
imodeladdfield -mmregister $addBlock/TIMER0 -name TUNITCON -bitoffset 0  -width 12  
 
imodeladdfield -mmregister $addBlock/TIMER1 -name TDCD_DBNC -bitoffset 16  -width 10
imodeladdfield -mmregister $addBlock/TIMER1 -name TVDPSRC_ON -bitoffset 0  -width 10    
 
imodeladdfield -mmregister $addBlock/TIMER2 -name CHECK_DM -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/TIMER2 -name TVDPSRC_CON -bitoffset 16  -width 10
