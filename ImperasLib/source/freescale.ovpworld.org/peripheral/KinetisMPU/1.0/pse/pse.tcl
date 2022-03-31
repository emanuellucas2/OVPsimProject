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
set name    KinetisMPU
set version 1.0
set desc "Model of the MPU peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

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

# RDG0_WORD0      0x400 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 0,  Word 0, offset: 0x400 "
# RDG0_WORD1      0x404 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 0,  Word 1, offset: 0x404 "
# RDG0_WORD2      0x408 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 0,  Word 2, offset: 0x408 "
# RDG0_WORD3      0x40c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 0,  Word 3, offset: 0x40c "
# RDG1_WORD0      0x410 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 1,  Word 0, offset: 0x410 "
# RDG1_WORD1      0x414 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 1,  Word 1, offset: 0x414 "
# RDG1_WORD2      0x418 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 1,  Word 2, offset: 0x418 "
# RDG1_WORD3      0x41c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 1,  Word 3, offset: 0x41c "
# RDG2_WORD0      0x420 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 2,  Word 0, offset: 0x420 "
# RDG2_WORD1      0x424 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 2,  Word 1, offset: 0x424 "
# RDG2_WORD2      0x428 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 2,  Word 2, offset: 0x428 "
# RDG2_WORD3      0x42c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 2,  Word 3, offset: 0x42c "
# RDG3_WORD0      0x430 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 3,  Word 0, offset: 0x430 "
# RDG3_WORD1      0x434 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 3,  Word 1, offset: 0x434 "
# RDG3_WORD2      0x438 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 3,  Word 2, offset: 0x438 "
# RDG3_WORD3      0x43c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 3,  Word 3, offset: 0x43c "
# RDG4_WORD0      0x440 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 4,  Word 0, offset: 0x440 "
# RDG4_WORD1      0x444 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 4,  Word 1, offset: 0x444 "
# RDG4_WORD2      0x448 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 4,  Word 2, offset: 0x448 "
# RDG4_WORD3      0x44c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 4,  Word 3, offset: 0x44c "
# RDG5_WORD0      0x450 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 5,  Word 0, offset: 0x450 "
# RDG5_WORD1      0x454 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 5,  Word 1, offset: 0x454 "
# RDG5_WORD2      0x458 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 5,  Word 2, offset: 0x458 "
# RDG5_WORD3      0x45c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 5,  Word 3, offset: 0x45c "
# RDG6_WORD0      0x460 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 6,  Word 0, offset: 0x460 "
# RDG6_WORD1      0x464 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 6,  Word 1, offset: 0x464 "
# RDG6_WORD2      0x468 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 6,  Word 2, offset: 0x468 "
# RDG6_WORD3      0x46c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 6,  Word 3, offset: 0x46c "
# RDG7_WORD0      0x470 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 7,  Word 0, offset: 0x470 "
# RDG7_WORD1      0x474 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 7,  Word 1, offset: 0x474 "
# RDG7_WORD2      0x478 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 7,  Word 2, offset: 0x478 "
# RDG7_WORD3      0x47c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 7,  Word 3, offset: 0x47c "
# RDG8_WORD0      0x480 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 8,  Word 0, offset: 0x480 "
# RDG8_WORD1      0x484 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 8,  Word 1, offset: 0x484 "
# RDG8_WORD2      0x488 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 8,  Word 2, offset: 0x488 "
# RDG8_WORD3      0x48c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 8,  Word 3, offset: 0x48c "
# RDG9_WORD0      0x490 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 9,  Word 0, offset: 0x490 "
# RDG9_WORD1      0x494 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 9,  Word 1, offset: 0x494 "
# RDG9_WORD2      0x498 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 9,  Word 2, offset: 0x498 "
# RDG9_WORD3      0x49c rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 9,  Word 3, offset: 0x49c "
# RDG10_WORD0     0x4a0 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 10, Word 0, offset: 0x4a0 "
# RDG10_WORD1     0x4a4 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 10, Word 1, offset: 0x4a4 "
# RDG10_WORD2     0x4a8 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 10, Word 2, offset: 0x4a8 "
# RDG10_WORD3     0x4ac rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 10, Word 3, offset: 0x4ac "
# RDG11_WORD0     0x4b0 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 11, Word 0, offset: 0x4b0 "
# RDG11_WORD1     0x4b4 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 11, Word 1, offset: 0x4b4 "
# RDG11_WORD2     0x4b8 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 11, Word 2, offset: 0x4b8 "
# RDG11_WORD3     0x4bc rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 11, Word 3, offset: 0x4bc "
# RDG12_WORD0     0x4c0 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 12, Word 0, offset: 0x4c0 "
# RDG12_WORD1     0x4c4 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 12, Word 1, offset: 0x4c4 "
# RDG12_WORD2     0x4c8 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 12, Word 2, offset: 0x4c8 "
# RDG12_WORD3     0x4cc rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 12, Word 3, offset: 0x4cc "
# RDG13_WORD0     0x4d0 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 13, Word 0, offset: 0x4d0 "
# RDG13_WORD1     0x4d4 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 13, Word 1, offset: 0x4d4 "
# RDG13_WORD2     0x4d8 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 13, Word 2, offset: 0x4d8 "
# RDG13_WORD3     0x4dc rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 13, Word 3, offset: 0x4dc "
# RDG14_WORD0     0x4e0 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 14, Word 0, offset: 0x4e0 "
# RDG14_WORD1     0x4e4 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 14, Word 1, offset: 0x4e4 "
# RDG14_WORD2     0x4e8 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 14, Word 2, offset: 0x4e8 "
# RDG14_WORD3     0x4ec rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 14, Word 3, offset: 0x4ec "
# RDG15_WORD0     0x4f0 rw - - - -                          0x00000000 0xffffffe0 "Region Descriptor 15, Word 0, offset: 0x4f0 "
# RDG15_WORD1     0x4f4 rw - - - -                          0x0000001f 0xffffffe0 "Region Descriptor 15, Word 1, offset: 0x4f4 "
# RDG15_WORD2     0x4f8 rw - - - -                          0x00000000 0xffffffff "Region Descriptor 15, Word 2, offset: 0x4f8 "
# RDG15_WORD3     0x4fc rw - - - -                          0x00000000 0xffff0001 "Region Descriptor 15, Word 3, offset: 0x4fc "


#   name      offset ac readFn    writeFn   viewFn   user reset      mask       description   
set registers { 
CESR            0x00 rw - - - -                           0x00818201 0xff000001 "Control/Error Status Register, offset: 0x0 " 
EAR0            0x10 r  - - - -                           -          -          "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 "    
EDR0            0x14 r  - - - -                           -          -          "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 " 
EAR1            0x18 r  - - - -                           -          -          "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 "    
EDR1            0x1c r  - - - -                           -          -          "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 " 
EAR2            0x20 r  - - - -                           -          -          "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 "    
EDR2            0x24 r  - - - -                           -          -          "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 " 
EAR3            0x28 r  - - - -                           -          -          "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 "    
EDR3            0x2c r  - - - -                           -          -          "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 " 
EAR4            0x30 r  - - - -                           -          -          "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 "    
EDR4            0x34 r  - - - -                           -          -          "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 " 
}

imodeladdbusslaveport -name bport1 -size 0x1000
imodeladdaddressblock -name ab     -size 0x100 -port bport1 -width 32

set addBlock     "bport1/ab"

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

    eval "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $v $u $m"
    if { $reset != "-" } {
        imodeladdreset -mmregister $addBlock/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc
}

imodeladdfield -mmregister $addBlock/CESR -name VLD   -bitoffset  0  -width 1  
imodeladdfield -mmregister $addBlock/CESR -name NRGD  -bitoffset  8  -width 4
imodeladdfield -mmregister $addBlock/CESR -name NSP   -bitoffset 12  -width 4
imodeladdfield -mmregister $addBlock/CESR -name HRL   -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CESR -name SPERR -bitoffset 24  -width 8

for {set idx 0} {$idx < 5} {incr idx} { 
    imodeladdfield -mmregister $addBlock/EAR${idx} -name EADDR -bitoffset  0  -width 32
    imodeladdfield -mmregister $addBlock/EDR${idx} -name ERW   -bitoffset  0  -width 1
    imodeladdfield -mmregister $addBlock/EDR${idx} -name EATTR -bitoffset  1  -width 3
    imodeladdfield -mmregister $addBlock/EDR${idx} -name EMN   -bitoffset  4  -width 4
    imodeladdfield -mmregister $addBlock/EDR${idx} -name EPID  -bitoffset  8  -width 8
    imodeladdfield -mmregister $addBlock/EDR${idx} -name EACD  -bitoffset 16  -width 16
}
    


imodeladdaddressblock  -name RGD%u  -width 32 -size 16 -offset 0x400 -loarray 0 -hiarray 15
   imodeladdmmregister    -name WORD0 -width 32 -offset 0    -writemask 0xffffffe0
      iadddocumentation -name Description -text "Region Descriptor"
      imodeladdreset    -name Reset -value 0
      imodeladdfield    -name SRTADDR -bitoffset 5  -width 27
      
   imodeladdmmregister    -name WORD1 -width 32 -offset 4    -writemask 0xffffffe0
      iadddocumentation -name Description -text "Region Descriptor"
      imodeladdreset    -name Reset -value  0x0000001f 
      imodeladdfield    -name ENDADDR -bitoffset 5  -width 27
      
   imodeladdmmregister    -name WORD2 -width 32 -offset 8   
      iadddocumentation -name Description -text "Region Descriptor"
      imodeladdreset    -name Reset -value  0 
      imodeladdfield    -name M0UM -bitoffset 0   -width 3
      imodeladdfield    -name M0SM -bitoffset 3   -width 2
      imodeladdfield    -name M0PE -bitoffset 5   -width 1
      imodeladdfield    -name M1UM -bitoffset 6   -width 3
      imodeladdfield    -name M1SM -bitoffset 9   -width 2
      imodeladdfield    -name M1PE -bitoffset 11  -width 1
      imodeladdfield    -name M2UM -bitoffset 12  -width 3
      imodeladdfield    -name M2SM -bitoffset 15  -width 2
      imodeladdfield    -name M2PE -bitoffset 17  -width 1
      imodeladdfield    -name M3UM -bitoffset 18  -width 3
      imodeladdfield    -name M3SM -bitoffset 21  -width 2
      imodeladdfield    -name M3PE -bitoffset 23  -width 1
      imodeladdfield    -name M4WE -bitoffset 24  -width 1
      imodeladdfield    -name M4RE -bitoffset 25  -width 1
      imodeladdfield    -name M5WE -bitoffset 26  -width 1
      imodeladdfield    -name M5RE -bitoffset 27  -width 1
      imodeladdfield    -name M6WE -bitoffset 28  -width 1
      imodeladdfield    -name M6RE -bitoffset 29  -width 1
      imodeladdfield    -name M7WE -bitoffset 30  -width 1
      imodeladdfield    -name M7RE -bitoffset 31  -width 1
      
   imodeladdmmregister    -name WORD3 -width 32 -offset 12   -writemask 0xffff0001
      iadddocumentation -name Description -text "Region Descriptor"
      imodeladdreset    -name Reset -value  0
      imodeladdfield    -name PID     -bitoffset 24 -width 8
      imodeladdfield    -name PIDMASK -bitoffset 16 -width 8
      imodeladdfield    -name VLD     -bitoffset  0 -width 1
    

imodeladdaddressblock -name AAC -offset 0x800 -size 0x40 -width 32

imodeladdmmregister -name RGDAAC%u  -offset 0   -loarray 0 -hiarray 15 
  iadddocumentation -name Description -text "Region Descriptor Alternate Access Control"
    imodeladdfield -name M0UM -bitoffset 0   -width 3
    imodeladdfield -name M0SM -bitoffset 3   -width 2
    imodeladdfield -name M0PE -bitoffset 5   -width 1
    imodeladdfield -name M1UM -bitoffset 6   -width 3
    imodeladdfield -name M1SM -bitoffset 9   -width 2
    imodeladdfield -name M1PE -bitoffset 11  -width 1
    imodeladdfield -name M2UM -bitoffset 12  -width 3
    imodeladdfield -name M2SM -bitoffset 15  -width 2
    imodeladdfield -name M2PE -bitoffset 17  -width 1
    imodeladdfield -name M3UM -bitoffset 18  -width 3
    imodeladdfield -name M3SM -bitoffset 21  -width 2
    imodeladdfield -name M3PE -bitoffset 23  -width 1
    imodeladdfield -name M4WE -bitoffset 24  -width 1
    imodeladdfield -name M4RE -bitoffset 25  -width 1
    imodeladdfield -name M5WE -bitoffset 26  -width 1
    imodeladdfield -name M5RE -bitoffset 27  -width 1
    imodeladdfield -name M6WE -bitoffset 28  -width 1
    imodeladdfield -name M6RE -bitoffset 29  -width 1
    imodeladdfield -name M7WE -bitoffset 30  -width 1
    imodeladdfield -name M7RE -bitoffset 31  -width 1

imodeladdnetport -name Reset     -type input

    
# 08-31-2014 PRE: .h file had width of 5, offset 27 for SPERR
 

