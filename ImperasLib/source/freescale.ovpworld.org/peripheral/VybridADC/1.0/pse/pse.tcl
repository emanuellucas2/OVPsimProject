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
set name    VybridADC
set version 1.0
set desc "Model of the ADC peripheral used on the Freescale Vybrid platform"
set limitations "Provides the base behaviour for the OVP Freescale Vybrid platforms"

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
iadddocumentation -name Reference -text "Development based on document number: VYBRIDRM Rev. 5, 07/2013"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x34 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
HC0             0x00 rw - - - - 0x0000001f 0x0000009f "Control register for hardware triggers, offset: 0x0"	
HC1             0x04 rw - - - - 0x0000001f 0x0000009f "Control register for hardware triggers, offset: 0x4"	
HS              0x08 r  - - - - 0x00000000 0x00000000 "Status register for HW triggers, offset: 0x8"	
R0              0x0c rw - - - - 0x00000000 0x00000000 "Data result register for HW triggers, offset: 0xC"	
R1              0x10 rw - - - - 0x00000000 0x00000000 "Data result register for HW triggers, offset: 0x10"	
CFG             0x14 rw - - - - 0x00000200 0x0001ffff "Configuration register, offset: 0x14"	
GC              0x18 rw - - - - 0x00000000 0x000000ff "General control register, offset: 0x18"	
GS              0x1c rw - GSWrite1C - - 0x00000000 0x00000006 "General status register, offset: 0x1C"	
CV              0x20 rw - - - - 0x00000000 0x0fff0fff "Compare value register, offset: 0x20"	
OFS             0x24 rw - - - - 0x00000000 0x00001fff "Offset correction value register, offset: 0x24"	
CAL             0x28 rw - - - - 0x00000000 0x0000000f "Calibration value register, offset: 0x28"	
PCTL            0x30 rw - - - - 0x00000000 0x00ffffff "Pin control register, offset: 0x30"
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

	
 
imodeladdfield -mmregister $addBlock/HC0 -name ADCH -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/HC0 -name AIEN -bitoffset 7  -width 1	
 
imodeladdfield -mmregister $addBlock/HC1 -name ADCH -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/HC1 -name AIEN -bitoffset 7  -width 1	
 
imodeladdfield -mmregister $addBlock/HS -name COCO1 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HS -name COCO2 -bitoffset 1  -width 1	
 
imodeladdfield -mmregister $addBlock/R0 -name D -bitoffset 0  -width 12	
 
imodeladdfield -mmregister $addBlock/R1 -name D -bitoffset 0  -width 12	
 
imodeladdfield -mmregister $addBlock/CFG -name ADHSC -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/CFG -name ADICLK -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CFG -name ADIV -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/CFG -name ADLPC -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CFG -name ADLSMP -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CFG -name ADSTS -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/CFG -name ADTRG -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/CFG -name AVGS -bitoffset 14  -width 2
imodeladdfield -mmregister $addBlock/CFG -name MODE -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/CFG -name OVWREN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CFG -name REFSEL -bitoffset 11  -width 2	
 
imodeladdfield -mmregister $addBlock/GC -name ACFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/GC -name ACFGT -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/GC -name ACREN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/GC -name ADACKEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/GC -name ADCO -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/GC -name AVGE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/GC -name CAL -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/GC -name DMAEN -bitoffset 1  -width 1	
 
imodeladdfield -mmregister $addBlock/GS -name ADACT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/GS -name AWKST -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/GS -name CALF -bitoffset 1  -width 1	
 
imodeladdfield -mmregister $addBlock/CV -name CV1 -bitoffset 0  -width 12
imodeladdfield -mmregister $addBlock/CV -name CV2 -bitoffset 16  -width 12	
 
imodeladdfield -mmregister $addBlock/OFS -name OFS -bitoffset 0  -width 12
imodeladdfield -mmregister $addBlock/OFS -name SIGN -bitoffset 12  -width 1	
 
imodeladdfield -mmregister $addBlock/CAL -name CAL_CODE -bitoffset 0  -width 4	
 
imodeladdfield -mmregister $addBlock/PCTL -name ADPC0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PCTL -name ADPC9 -bitoffset 9  -width 1
