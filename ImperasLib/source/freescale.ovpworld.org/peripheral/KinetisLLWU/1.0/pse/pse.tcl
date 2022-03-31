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
set name    KinetisLLWU
set version 1.0
set desc "Model of the LLWU peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x0b -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
PE1             0x00 rw - - - - 0x00 0xff "LLWU Pin Enable 1 Register, offset: 0x0 "    
PE2             0x01 rw - - - - 0x00 0xff "LLWU Pin Enable 2 Register, offset: 0x1 "    
PE3             0x02 rw - - - - 0x00 0xff "LLWU Pin Enable 3 Register, offset: 0x2 "    
PE4             0x03 rw - - - - 0x00 0xff "LLWU Pin Enable 4 Register, offset: 0x3 "    
ME              0x04 rw - - - - 0x00 0xff "LLWU Module Enable Register, offset: 0x4 "   
F1              0x05 rw - - - - 0x00 0xff "LLWU Flag 1 Register, offset: 0x5 "  
F2              0x06 rw - - - - 0x00 0xff "LLWU Flag 2 Register, offset: 0x6 "  
F3              0x07 rw - - - - 0x00 0x00 "LLWU Flag 3 Register, offset: 0x7 "  
FILT1           0x08 rw - - - - 0x00 0xef "LLWU Pin Filter 1 Register, offset: 0x8 "    
FILT2           0x09 rw - - - - 0x00 0xef "LLWU Pin Filter 2 Register, offset: 0x9 "    
RST             0x0a rw - - - - 0x02 0x03 "LLWU Reset Enable Register, offset: 0xA "
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

    
 
imodeladdfield -mmregister $addBlock/PE1 -name WUPE0 -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/PE1 -name WUPE1 -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/PE1 -name WUPE2 -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/PE1 -name WUPE3 -bitoffset 6  -width 2 
 
imodeladdfield -mmregister $addBlock/PE2 -name WUPE4 -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/PE2 -name WUPE5 -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/PE2 -name WUPE6 -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/PE2 -name WUPE7 -bitoffset 6  -width 2 
 
imodeladdfield -mmregister $addBlock/PE3 -name WUPE10 -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/PE3 -name WUPE11 -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/PE3 -name WUPE8 -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/PE3 -name WUPE9 -bitoffset 2  -width 2 
 
imodeladdfield -mmregister $addBlock/PE4 -name WUPE12 -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/PE4 -name WUPE13 -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/PE4 -name WUPE14 -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/PE4 -name WUPE15 -bitoffset 6  -width 2    
 
imodeladdfield -mmregister $addBlock/ME -name WUME0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ME -name WUME7 -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/F1 -name WUF0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/F1 -name WUF7 -bitoffset 7  -width 1   
 
imodeladdfield -mmregister $addBlock/F2 -name WUF10 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF11 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF12 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF13 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF14 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF15 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF8 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/F2 -name WUF9 -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/F3 -name MWUF0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/F3 -name MWUF7 -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/FILT1 -name FILTE -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/FILT1 -name FILTF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FILT1 -name FILTSEL -bitoffset 0  -width 4 
 
imodeladdfield -mmregister $addBlock/FILT2 -name FILTE -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/FILT2 -name FILTF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FILT2 -name FILTSEL -bitoffset 0  -width 4 
 
imodeladdfield -mmregister $addBlock/RST -name LLRSTE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/RST -name RSTFILT -bitoffset 0  -width 1
