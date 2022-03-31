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
set name    KinetisFB
set version 1.0
set desc "Model of the FB peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x64 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CSAR0           0x00 rw - - - - 0x00000000 0xffff0000 "Chip select address register, array offset: 0x0, array step: 0xC "   
CSMR0           0x04 rw - - - - 0x00000000 0xffff0100 "Chip select mask register, array offset: 0x4, array step: 0xC "  
CSCR0           0x08 rw - - - - 0x00000000 0xfcfffff8 "Chip select control register, array offset: 0x8, array step: 0xC "   
CSAR1           0x0c rw - - - - 0x00000000 0xffff0000 "Chip select address register, array offset: 0x0, array step: 0xC "   
CSMR1           0x10 rw - - - - 0x00000000 0xffff0100 "Chip select mask register, array offset: 0x4, array step: 0xC "  
CSCR1           0x14 rw - - - - 0x00000000 0xfcfffff8 "Chip select control register, array offset: 0x8, array step: 0xC "   
CSAR2           0x18 rw - - - - 0x00000000 0xffff0000 "Chip select address register, array offset: 0x0, array step: 0xC "   
CSMR2           0x1c rw - - - - 0x00000000 0xffff0100 "Chip select mask register, array offset: 0x4, array step: 0xC "  
CSCR2           0x20 rw - - - - 0x00000000 0xfcfffff8 "Chip select control register, array offset: 0x8, array step: 0xC "   
CSAR3           0x24 rw - - - - 0x00000000 0xffff0000 "Chip select address register, array offset: 0x0, array step: 0xC "   
CSMR3           0x28 rw - - - - 0x00000000 0xffff0100 "Chip select mask register, array offset: 0x4, array step: 0xC "  
CSCR3           0x2c rw - - - - 0x00000000 0xfcfffff8 "Chip select control register, array offset: 0x8, array step: 0xC "   
CSAR4           0x30 rw - - - - 0x00000000 0xffff0000 "Chip select address register, array offset: 0x0, array step: 0xC "   
CSMR4           0x34 rw - - - - 0x00000000 0xffff0100 "Chip select mask register, array offset: 0x4, array step: 0xC "  
CSCR4           0x38 rw - - - - 0x00000000 0xfcfffff8 "Chip select control register, array offset: 0x8, array step: 0xC "   
CSAR5           0x3c rw - - - - 0x00000000 0xffff0000 "Chip select address register, array offset: 0x0, array step: 0xC "   
CSMR5           0x40 rw - - - - 0x00000000 0xffff0100 "Chip select mask register, array offset: 0x4, array step: 0xC "  
CSCR5           0x44 rw - - - - 0x00000000 0xfcfffff8 "Chip select control register, array offset: 0x8, array step: 0xC "   
CSPMCR          0x60 rw - - - - 0x00000000 0xfffff000 "Chip select port multiplexing control register, offset: 0x60 "
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

    
 
imodeladdfield -mmregister $addBlock/CSAR0 -name BA -bitoffset 16  -width 16    
imodeladdfield -mmregister $addBlock/CSAR1 -name BA -bitoffset 16  -width 16    
imodeladdfield -mmregister $addBlock/CSAR2 -name BA -bitoffset 16  -width 16    
imodeladdfield -mmregister $addBlock/CSAR3 -name BA -bitoffset 16  -width 16    
imodeladdfield -mmregister $addBlock/CSAR4 -name BA -bitoffset 16  -width 16    
imodeladdfield -mmregister $addBlock/CSAR5 -name BA -bitoffset 16  -width 16    
 
imodeladdfield -mmregister $addBlock/CSMR0 -name BAM -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CSMR0 -name V -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CSMR0 -name WP -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CSMR1 -name BAM -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CSMR1 -name V -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CSMR1 -name WP -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CSMR2 -name BAM -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CSMR2 -name V -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CSMR2 -name WP -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CSMR3 -name BAM -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CSMR3 -name V -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CSMR3 -name WP -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CSMR4 -name BAM -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CSMR4 -name V -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CSMR4 -name WP -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CSMR5 -name BAM -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/CSMR5 -name V -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CSMR5 -name WP -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CSCR0 -name AA -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name ASET -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CSCR0 -name BEM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name BLS -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name BSTR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name BSTW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name EXTS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name PS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CSCR0 -name RDAH -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/CSCR0 -name SWS -bitoffset 26  -width 6
imodeladdfield -mmregister $addBlock/CSCR0 -name SWSEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/CSCR0 -name WRAH -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CSCR0 -name WS -bitoffset 10  -width 6 

imodeladdfield -mmregister $addBlock/CSCR1 -name AA -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name ASET -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CSCR1 -name BEM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name BLS -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name BSTR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name BSTW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name EXTS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name PS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CSCR1 -name RDAH -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/CSCR1 -name SWS -bitoffset 26  -width 6
imodeladdfield -mmregister $addBlock/CSCR1 -name SWSEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/CSCR1 -name WRAH -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CSCR1 -name WS -bitoffset 10  -width 6 

imodeladdfield -mmregister $addBlock/CSCR2 -name AA -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name ASET -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CSCR2 -name BEM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name BLS -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name BSTR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name BSTW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name EXTS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name PS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CSCR2 -name RDAH -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/CSCR2 -name SWS -bitoffset 26  -width 6
imodeladdfield -mmregister $addBlock/CSCR2 -name SWSEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/CSCR2 -name WRAH -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CSCR2 -name WS -bitoffset 10  -width 6 

imodeladdfield -mmregister $addBlock/CSCR3 -name AA -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name ASET -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CSCR3 -name BEM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name BLS -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name BSTR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name BSTW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name EXTS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name PS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CSCR3 -name RDAH -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/CSCR3 -name SWS -bitoffset 26  -width 6
imodeladdfield -mmregister $addBlock/CSCR3 -name SWSEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/CSCR3 -name WRAH -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CSCR3 -name WS -bitoffset 10  -width 6 

imodeladdfield -mmregister $addBlock/CSCR4 -name AA -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name ASET -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CSCR4 -name BEM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name BLS -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name BSTR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name BSTW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name EXTS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name PS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CSCR4 -name RDAH -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/CSCR4 -name SWS -bitoffset 26  -width 6
imodeladdfield -mmregister $addBlock/CSCR4 -name SWSEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/CSCR4 -name WRAH -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CSCR4 -name WS -bitoffset 10  -width 6 

imodeladdfield -mmregister $addBlock/CSCR5 -name AA -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name ASET -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CSCR5 -name BEM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name BLS -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name BSTR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name BSTW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name EXTS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name PS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CSCR5 -name RDAH -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/CSCR5 -name SWS -bitoffset 26  -width 6
imodeladdfield -mmregister $addBlock/CSCR5 -name SWSEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/CSCR5 -name WRAH -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CSCR5 -name WS -bitoffset 10  -width 6 

imodeladdfield -mmregister $addBlock/CSPMCR -name GROUP1 -bitoffset 28  -width 4
imodeladdfield -mmregister $addBlock/CSPMCR -name GROUP2 -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/CSPMCR -name GROUP3 -bitoffset 20  -width 4
imodeladdfield -mmregister $addBlock/CSPMCR -name GROUP4 -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CSPMCR -name GROUP5 -bitoffset 12  -width 4
