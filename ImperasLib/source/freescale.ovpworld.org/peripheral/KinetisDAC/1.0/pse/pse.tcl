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
set name    KinetisDAC
set version 1.0
set desc "Model of the DAC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x24 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
DAT0L           0x00 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT0H           0x01 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT1L           0x02 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT1H           0x03 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT2L           0x04 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT2H           0x05 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT3L           0x06 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT3H           0x07 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT4L           0x08 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT4H           0x09 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT5L           0x0a rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT5H           0x0b rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT6L           0x0c rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT6H           0x0d rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT7L           0x0e rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT7H           0x0f rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT8L           0x10 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT8H           0x11 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT9L           0x12 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT9H           0x13 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT10L          0x14 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT10H          0x15 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT11L          0x16 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT11H          0x17 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT12L          0x18 rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT12H          0x19 rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT13L          0x1a rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT13H          0x1b rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT14L          0x1c rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT14H          0x1d rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
DAT15L          0x1e rw - - - - 0x00 0xff "DAC Data Low Register, array offset: 0x0, array step: 0x2 "  
DAT15H          0x1f rw - - - - 0x00 0x0f "DAC Data High Register, array offset: 0x1, array step: 0x2 " 
SR              0x20 rw - - - - 0x02 0x07 "DAC Status Register, offset: 0x20 "  
C0              0x21 rw - - - - 0x00 0xff "DAC Control Register, offset: 0x21 " 
C1              0x22 rw - - - - 0x00 0x9f "DAC Control Register 1, offset: 0x22 "   
C2              0x23 rw - - - - 0x0f 0xff "DAC Control Register 2, offset: 0x23 "
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

    
 
imodeladdfield -mmregister $addBlock/DAT0L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT1L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT2L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT3L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT4L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT6L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT7L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT8L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT9L -name DATA -bitoffset 0  -width 8    
imodeladdfield -mmregister $addBlock/DAT10L -name DATA -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/DAT11L -name DATA -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/DAT12L -name DATA -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/DAT13L -name DATA -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/DAT14L -name DATA -bitoffset 0  -width 8   
imodeladdfield -mmregister $addBlock/DAT15L -name DATA -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/DAT0H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT1H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT2H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT3H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT4H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT5H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT6H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT7H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT8H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT9H -name DATA -bitoffset 0  -width 4    
imodeladdfield -mmregister $addBlock/DAT10H -name DATA -bitoffset 0  -width 4   
imodeladdfield -mmregister $addBlock/DAT11H -name DATA -bitoffset 0  -width 4   
imodeladdfield -mmregister $addBlock/DAT12H -name DATA -bitoffset 0  -width 4   
imodeladdfield -mmregister $addBlock/DAT13H -name DATA -bitoffset 0  -width 4   
imodeladdfield -mmregister $addBlock/DAT14H -name DATA -bitoffset 0  -width 4   
imodeladdfield -mmregister $addBlock/DAT15H -name DATA -bitoffset 0  -width 4   

imodeladdfield -mmregister $addBlock/SR -name DACBFRPBF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SR -name DACBFRPTF -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SR -name DACBFWMF -bitoffset 2  -width 1   
 
imodeladdfield -mmregister $addBlock/C0 -name DACBBIEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C0 -name DACBTIEN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/C0 -name DACBWIEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C0 -name LPEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C0 -name DACSWTRG -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C0 -name DACTRGSEL -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C0 -name DACRFS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C0 -name DACEN -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/C1 -name DACBFEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C1 -name DACBFMD -bitoffset 1  -width 2
imodeladdfield -mmregister $addBlock/C1 -name DACBFWM -bitoffset 3  -width 2
imodeladdfield -mmregister $addBlock/C1 -name DMAEN -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/C2 -name DACBFUP -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/C2 -name DACBFRP -bitoffset 4  -width 4
