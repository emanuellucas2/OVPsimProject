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
set name    KinetisCMT
set version 1.0
set desc "Model of the CMT peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x0c -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CGH1            0x00 rw - - - - -    0xff "CMT Carrier Generator High Data Register 1, offset: 0x0 "    
CGL1            0x01 rw - - - - -    0xff "CMT Carrier Generator Low Data Register 1, offset: 0x1 " 
CGH2            0x02 rw - - - - -    0xff "CMT Carrier Generator High Data Register 2, offset: 0x2 "    
CGL2            0x03 rw - - - - -    0xff "CMT Carrier Generator Low Data Register 2, offset: 0x3 " 
OC              0x04 rw - - - - 0x00 0xe0 "CMT Output Control Register, offset: 0x4 "   
MSC             0x05 rw - - - - 0x00 0x7f "CMT Modulator Status and Control Register, offset: 0x5 " 
CMD1            0x06 rw - - - - -    0xff "CMT Modulator Data Register Mark High, offset: 0x6 " 
CMD2            0x07 rw - - - - -    0xff "CMT Modulator Data Register Mark Low, offset: 0x7 "  
CMD3            0x08 rw - - - - -    0xff "CMT Modulator Data Register Space High, offset: 0x8 "    
CMD4            0x09 rw - - - - -    0xff "CMT Modulator Data Register Space Low, offset: 0x9 " 
PPS             0x0a rw - - - - 0x00 0x0f "CMT Primary Prescaler Register, offset: 0xA "    
DMA             0x0b rw - - - - 0x00 0x01 "CMT Direct Memory Access, offset: 0xB "
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

    
 
imodeladdfield -mmregister $addBlock/CGH1 -name PH -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CGL1 -name PL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CGH2 -name SH -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CGL2 -name SL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/OC -name CMTPOL -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OC -name IROL -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/OC -name IROPEN -bitoffset 5  -width 1 
 
imodeladdfield -mmregister $addBlock/MSC -name BASE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/MSC -name CMTDIV -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/MSC -name EOCF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/MSC -name EOCIE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/MSC -name EXSPC -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/MSC -name FSK -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/MSC -name MCGEN -bitoffset 0  -width 1 
 
imodeladdfield -mmregister $addBlock/CMD1 -name MB -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CMD2 -name MB -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CMD3 -name SB -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CMD4 -name SB -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/PPS -name PPSDIV -bitoffset 0  -width 4    
 
imodeladdfield -mmregister $addBlock/DMA -name DMA -bitoffset 0  -width 1
