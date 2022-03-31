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
set name    KinetisFMC
set version 1.0
set desc "Model of the FMC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x300 -port bport1 -width 32

set addBlock     "bport1/ab"


#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
PFAPR           0x00 rw - - - - 0x00f8003f 0x00ffffff "Flash Access Protection Register, offset: 0x0 "  
PFB01CR         0x04 rw - - - - 0x3004001f 0x0f0800ff "Flash Bank 0-1 Control Register, offset: 0x4 "   
PFB23CR         0x08 rw - - - - 0x3004001f 0x0000001f "Flash Bank 2-3 Control Register, offset: 0x8 "   
TAGVDW0S0       0x100 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW0S1       0x104 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW0S2       0x108 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW0S3       0x10c rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW1S0       0x110 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW1S1       0x114 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW1S2       0x118 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW1S3       0x11c rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW2S0       0x120 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW2S1       0x124 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW2S2       0x128 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW2S3       0x12c rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW3S0       0x130 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW3S1       0x134 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW3S2       0x138 rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
TAGVDW3S3       0x13c rw - - - - 0x00000000 0x000fffc1 "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 "    
DATAW0S0UM      0x200 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW0S0MU      0x204 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW0S0ML      0x208 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW0S0LM      0x20c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW0S1UM      0x210 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW0S1MU      0x214 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW0S1ML      0x218 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW0S1LM      0x21c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW0S2UM      0x220 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW0S2MU      0x224 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW0S2ML      0x228 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW0S2LM      0x22c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW0S3UM      0x230 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW0S3MU      0x234 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW0S3ML      0x238 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW0S3LM      0x23c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW1S0UM      0x240 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW1S0MU      0x244 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW1S0ML      0x248 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW1S0LM      0x24c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW1S1UM      0x250 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW1S1MU      0x254 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW1S1ML      0x258 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW1S1LM      0x25c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW1S2UM      0x260 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW1S2MU      0x264 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW1S2ML      0x268 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW1S2LM      0x26c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW1S3UM      0x270 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW1S3MU      0x274 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW1S3ML      0x278 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW1S3LM      0x27c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW2S0UM      0x280 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW2S0MU      0x284 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW2S0ML      0x288 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW2S0LM      0x28c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW2S1UM      0x290 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW2S1MU      0x294 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW2S1ML      0x298 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW2S1LM      0x29c rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW2S2UM      0x2a0 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW2S2MU      0x2a4 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW2S2ML      0x2a8 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW2S2LM      0x2ac rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW2S3UM      0x2b0 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW2S3MU      0x2b4 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW2S3ML      0x2b8 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW2S3LM      0x2bc rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW3S0UM      0x2c0 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW3S0MU      0x2c4 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW3S0ML      0x2c8 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW3S0LM      0x2cc rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW3S1UM      0x2d0 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW3S1MU      0x2d4 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW3S1ML      0x2d8 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW3S1LM      0x2dc rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW3S2UM      0x2e0 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW3S2MU      0x2e4 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW3S2ML      0x2e8 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW3S2LM      0x2ec rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
DATAW3S3UM      0x2f0 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 " 
DATAW3S3MU      0x2f4 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 " 
DATAW3S3ML      0x2f8 rw - - - - 0x00000000 0xffffffff "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 " 
DATAW3S3LM      0x2fc rw - - - - 0x00000000 0xffffffff "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 " 
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

    
 
imodeladdfield -mmregister $addBlock/PFAPR -name M0AP -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M0PFD -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M1AP -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M1PFD -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M2AP -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M2PFD -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M3AP -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M3PFD -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M4AP -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M4PFD -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M5AP -bitoffset 10  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M5PFD -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M6AP -bitoffset 12  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M6PFD -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PFAPR -name M7AP -bitoffset 14  -width 2
imodeladdfield -mmregister $addBlock/PFAPR -name M7PFD -bitoffset 23  -width 1  
 
imodeladdfield -mmregister $addBlock/PFB01CR -name B01DCE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PFB01CR -name B01DPE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PFB01CR -name B01ICE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PFB01CR -name B01IPE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PFB01CR -name B01MW -bitoffset 17  -width 2
imodeladdfield -mmregister $addBlock/PFB01CR -name B01RWSC -bitoffset 28  -width 4
imodeladdfield -mmregister $addBlock/PFB01CR -name B01SEBE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PFB01CR -name CINV_WAY -bitoffset 20  -width 4
imodeladdfield -mmregister $addBlock/PFB01CR -name CLCK_WAY -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/PFB01CR -name CRC -bitoffset 5  -width 3
imodeladdfield -mmregister $addBlock/PFB01CR -name S_B_INV -bitoffset 19  -width 1  
 
imodeladdfield -mmregister $addBlock/PFB23CR -name B23DCE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PFB23CR -name B23DPE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PFB23CR -name B23ICE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PFB23CR -name B23IPE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PFB23CR -name B23MW -bitoffset 17  -width 2
imodeladdfield -mmregister $addBlock/PFB23CR -name B23RWSC -bitoffset 28  -width 4
imodeladdfield -mmregister $addBlock/PFB23CR -name B23SEBE -bitoffset 0  -width 1   
 
imodeladdfield -mmregister $addBlock/TAGVDW0S0 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW0S0 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW0S1 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW0S1 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW0S2 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW0S2 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW0S3 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW0S3 -name valid -bitoffset 0  -width 1   

imodeladdfield -mmregister $addBlock/TAGVDW1S0 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW1S0 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW1S1 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW1S1 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW1S2 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW1S2 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW1S3 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW1S3 -name valid -bitoffset 0  -width 1   

imodeladdfield -mmregister $addBlock/TAGVDW2S0 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW2S0 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW2S1 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW2S1 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW2S2 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW2S2 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW2S3 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW2S3 -name valid -bitoffset 0  -width 1   

imodeladdfield -mmregister $addBlock/TAGVDW3S0 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW3S0 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW3S1 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW3S1 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW3S2 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW3S2 -name valid -bitoffset 0  -width 1   
imodeladdfield -mmregister $addBlock/TAGVDW3S3 -name tag -bitoffset 6  -width 14
imodeladdfield -mmregister $addBlock/TAGVDW3S3 -name valid -bitoffset 0  -width 1   
 
imodeladdfield -mmregister $addBlock/DATAW0S0UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S0MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S0ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S0LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S1UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S1MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S1ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S1LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S2UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S2MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S2ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S2LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S3UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S3MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S3ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW0S3LM -name data -bitoffset 0  -width 32  

imodeladdfield -mmregister $addBlock/DATAW1S0UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S0MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S0ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S0LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S1UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S1MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S1ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S1LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S2UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S2MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S2ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S2LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S3UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S3MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S3ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW1S3LM -name data -bitoffset 0  -width 32  
    
imodeladdfield -mmregister $addBlock/DATAW2S0UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S0MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S0ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S0LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S1UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S1MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S1ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S1LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S2UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S2MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S2ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S2LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S3UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S3MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S3ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW2S3LM -name data -bitoffset 0  -width 32  
    
imodeladdfield -mmregister $addBlock/DATAW3S0UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S0MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S0ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S0LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S1UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S1MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S1ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S1LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S2UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S2MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S2ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S2LM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S3UM -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S3MU -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S3ML -name data -bitoffset 0  -width 32  
imodeladdfield -mmregister $addBlock/DATAW3S3LM -name data -bitoffset 0  -width 32  
    
    
    
 
