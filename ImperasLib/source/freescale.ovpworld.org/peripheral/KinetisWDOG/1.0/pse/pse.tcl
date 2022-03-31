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
set name    KinetisWDOG
set version 1.0
set desc "Model of the WDOG peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x18 -port bport1 -width 16

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
STCTRLH         0x00 rw - - - - 0x01d3 0x7cff "Watchdog Status and Control Register High, offset: 0x0 " 
STCTRLL         0x02 rw - - - - 0x0001 0x8000 "Watchdog Status and Control Register Low, offset: 0x2 "  
TOVALH          0x04 rw - - - - 0x004c 0xffff "Watchdog Time-out Value Register High, offset: 0x4 " 
TOVALL          0x06 rw - - - - 0x4b4c 0xffff "Watchdog Time-out Value Register Low, offset: 0x6 "  
WINH            0x08 rw - - - - 0x0000 0xffff "Watchdog Window Register High, offset: 0x8 " 
WINL            0x0a rw - - - - 0x0010 0xffff "Watchdog Window Register Low, offset: 0xA "  
REFRESH         0x0c rw - - - - 0xb480 0xffff "Watchdog Refresh Register, offset: 0xC " 
UNLOCK          0x0e rw - - - - 0x0000 0xffff "Watchdog Unlock Register, offset: 0xE "  
TMROUTH         0x10 rw - - - - 0x0000 0xffff "Watchdog Timer Output Register High, offset: 0x10 "  
TMROUTL         0x12 rw - - - - 0x0000 0xffff "Watchdog Timer Output Register Low, offset: 0x12 "   
RSTCNT          0x14 rw - - - - 0x0000 0xffff "Watchdog Reset Count Register, offset: 0x14 "    
PRESC           0x16 rw - - - - 0x0400 0x0700 "Watchdog Prescaler Register, offset: 0x16 "
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

    
 
imodeladdfield -mmregister $addBlock/STCTRLH -name ALLOWUPDATE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name BYTESEL -bitoffset 12  -width 2
imodeladdfield -mmregister $addBlock/STCTRLH -name CLKSRC -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name DBGEN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name DISTESTWDOG -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name IRQRSTEN -bitoffset 2  -width 1
# 08_26_2014 PRE: STNDBYEN is listed as 'Reserved' in Documentation. Leaving in place for now.
imodeladdfield -mmregister $addBlock/STCTRLH -name STNDBYEN -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name STOPEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name TESTSEL -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name TESTWDOG -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name WAITEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name WDOGEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/STCTRLH -name WINEN -bitoffset 3  -width 1 
 
imodeladdfield -mmregister $addBlock/STCTRLL -name INTFLG -bitoffset 15  -width 1   
 
imodeladdfield -mmregister $addBlock/TOVALH -name TOVALHIGH -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/TOVALL -name TOVALLOW -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/WINH -name WINHIGH -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/WINL -name WINLOW -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/REFRESH -name WDOGREFRESH -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/UNLOCK -name WDOGUNLOCK -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/TMROUTH -name TIMEROUTHIGH -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/TMROUTL -name TIMEROUTLOW -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/RSTCNT -name RSTCNT -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/PRESC -name PRESCVAL -bitoffset 8  -width 3
