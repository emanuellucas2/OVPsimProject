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
set name    KinetisPDB
set version 1.0
set desc "Model of the PDB peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x1a4 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
SC              0x00 rw - - - - 0x00000000 0x000fffef "Status and Control Register, offset: 0x0 "   
MOD             0x04 rw - - - - 0x0000ffff 0x0000ffff "Modulus Register, offset: 0x4 "  
CNT             0x08 r  - - - - 0x00000000 - "Counter Register, offset: 0x8 "   
IDLY            0x0c rw - - - - 0x0000ffff 0x0000ffff "Interrupt Delay Register, offset: 0xC "  
CH0C1           0x10 rw - - - - 0x00000000 0x00ffffff "Channel n Control Register 1, array offset: 0x10, array step: 0x28 " 
CH0S            0x14 rw - - - - 0x00000000 0x00ff00ff "Channel n Status Register, array offset: 0x14, array step: 0x28 "    
CH0DLY0         0x18 rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH0DLY1         0x1c rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH1C1           0x38 rw - - - - 0x00000000 0x00ffffff "Channel n Control Register 1, array offset: 0x10, array step: 0x28 " 
CH1S            0x3c rw - - - - 0x00000000 0x00ff00ff "Channel n Status Register, array offset: 0x14, array step: 0x28 "    
CH1DLY0         0x40 rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH1DLY1         0x44 rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH2C1           0x60 rw - - - - 0x00000000 0x00ffffff "Channel n Control Register 1, array offset: 0x10, array step: 0x28 " 
CH2S            0x64 rw - - - - 0x00000000 0x00ff00ff "Channel n Status Register, array offset: 0x14, array step: 0x28 "    
CH2DLY0         0x68 rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH2DLY1         0x6c rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH3C1           0x88 rw - - - - 0x00000000 0x00ffffff "Channel n Control Register 1, array offset: 0x10, array step: 0x28 " 
CH3S            0x8c rw - - - - 0x00000000 0x00ff00ff "Channel n Status Register, array offset: 0x14, array step: 0x28 "    
CH3DLY0         0x90 rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
CH3DLY1         0x94 rw - - - - 0x00000000 0x0000ffff "Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 " 
DACINTC0        0x150 rw - - - - 0x00000000 0x00000003 "DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 " 
DACINT0         0x154 rw - - - - 0x00000000 0x0000ffff "DAC Interval n Register, array offset: 0x154, array step: 0x8 " 
DACINTC1        0x158 rw - - - - 0x00000000 0x00000003 "DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 " 
DACINT1         0x15c rw - - - - 0x00000000 0x0000ffff "DAC Interval n Register, array offset: 0x154, array step: 0x8 " 
POEN            0x190 rw - - - - 0x00000000 0x000000ff "Pulse-Out n Enable Register, offset: 0x190 "    
PO0DLY          0x194 rw - - - - 0x00000000 0xffffffff "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 "  
PO1DLY          0x198 rw - - - - 0x00000000 0xffffffff "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 "  
PO2DLY          0x19c rw - - - - 0x00000000 0xffffffff "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 "  
PO3DLY          0x1a0 rw - - - - 0x00000000 0xffffffff "Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 "
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

    
 
imodeladdfield -mmregister $addBlock/SC -name CONT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SC -name DMAEN -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/SC -name LDMOD -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/SC -name LDOK -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SC -name MULT -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/SC -name PDBEIE -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/SC -name PDBEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC -name PDBIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SC -name PDBIF -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SC -name PRESCALER -bitoffset 12  -width 3
imodeladdfield -mmregister $addBlock/SC -name SWTRIG -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/SC -name TRGSEL -bitoffset 8  -width 4 
 
imodeladdfield -mmregister $addBlock/MOD -name MOD -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/CNT -name CNT -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/IDLY -name IDLY -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/CH0C1 -name BB -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH0C1 -name EN -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CH0C1 -name TOS -bitoffset 8  -width 8 
imodeladdfield -mmregister $addBlock/CH1C1 -name BB -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH1C1 -name EN -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CH1C1 -name TOS -bitoffset 8  -width 8 
imodeladdfield -mmregister $addBlock/CH2C1 -name BB -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH2C1 -name EN -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CH2C1 -name TOS -bitoffset 8  -width 8 
imodeladdfield -mmregister $addBlock/CH3C1 -name BB -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH3C1 -name EN -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CH3C1 -name TOS -bitoffset 8  -width 8 
 
imodeladdfield -mmregister $addBlock/CH0S -name CF -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH0S -name ERR -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/CH1S -name CF -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH1S -name ERR -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/CH2S -name CF -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH2S -name ERR -bitoffset 0  -width 8  
imodeladdfield -mmregister $addBlock/CH3S -name CF -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CH3S -name ERR -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/CH0DLY0 -name DLY -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/CH1DLY0 -name DLY -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/CH2DLY0 -name DLY -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/CH3DLY0 -name DLY -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/CH0DLY1 -name DLY -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/CH1DLY1 -name DLY -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/CH2DLY1 -name DLY -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/CH3DLY1 -name DLY -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/DACINTC0 -name EXT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/DACINTC0 -name TOE -bitoffset 0  -width 1  
imodeladdfield -mmregister $addBlock/DACINTC1 -name EXT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/DACINTC1 -name TOE -bitoffset 0  -width 1  
 
imodeladdfield -mmregister $addBlock/DACINT0 -name INT -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/DACINT1 -name INT -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/POEN -name POEN -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/PO0DLY -name DLY1 -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/PO0DLY -name DLY2 -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/PO1DLY -name DLY1 -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/PO1DLY -name DLY2 -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/PO2DLY -name DLY1 -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/PO2DLY -name DLY2 -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/PO3DLY -name DLY1 -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/PO3DLY -name DLY2 -bitoffset 0  -width 16
