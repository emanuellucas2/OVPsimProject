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
set name    KinetisPORT
set version 1.0
set desc "Model of the PORT peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0xcc -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
PCR0            0x00 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR1            0x04 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR2            0x08 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR3            0x0c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR4            0x10 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR5            0x14 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR6            0x18 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR7            0x1c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR8            0x20 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR9            0x24 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR10           0x28 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR11           0x2c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR12           0x30 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR13           0x34 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR14           0x38 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR15           0x3c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR16           0x40 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR17           0x44 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR18           0x48 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR19           0x4c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR20           0x50 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR21           0x54 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR22           0x58 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR23           0x5c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR24           0x60 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR25           0x64 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR26           0x68 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR27           0x6c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR28           0x70 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR29           0x74 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR30           0x78 rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
PCR31           0x7c rw - - - - 0x00000000 0x010f8777 "Pin Control Register n, array offset: 0x0, array step: 0x4 " 
GPCLR           0x80  w - - - - 0x00000000 0xffffffff "Global Pin Control Low Register, offset: 0x80 "  
GPCHR           0x84  w - - - - 0x00000000 0xffffffff "Global Pin Control High Register, offset: 0x84 " 
ISFR            0xa0 rw - - - - 0x00000000 0xffffffff "Interrupt Status Flag Register, offset: 0xA0 "   
DFER            0xc0 rw - - - - 0x00000000 0xffffffff "Digital Filter Enable Register, offset: 0xC0 "   
DFCR            0xc4 rw - - - - 0x00000000 0x00000001 "Digital Filter Clock Register, offset: 0xC4 "    
DFWR            0xc8 rw - - - - 0x00000000 0x0000001f "Digital Filter Width Register, offset: 0xC8 "
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

    
 
imodeladdfield -mmregister $addBlock/PCR0 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR0 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR0 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR0 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR1 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR1 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR1 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR1 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR2 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR2 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR2 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR2 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR3 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR3 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR3 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR3 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR4 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR4 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR4 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR4 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR5 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR5 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR5 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR5 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR6 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR6 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR6 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR6 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR7 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR7 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR7 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR7 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR8 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR8 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR8 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR8 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR9 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR9 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR9 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR9 -name SRE -bitoffset 2  -width 1  
 
imodeladdfield -mmregister $addBlock/PCR10 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR10 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR10 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR10 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR11 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR11 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR11 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR11 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR12 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR12 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR12 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR12 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR13 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR13 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR13 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR13 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR14 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR14 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR14 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR14 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR15 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR15 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR15 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR15 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR16 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR16 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR16 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR16 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR17 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR17 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR17 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR17 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR18 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR18 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR18 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR18 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR19 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR19 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR19 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR19 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR20 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR20 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR20 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR20 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR21 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR21 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR21 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR21 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR22 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR22 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR22 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR22 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR23 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR23 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR23 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR23 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR24 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR24 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR24 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR24 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR25 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR25 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR25 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR25 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR26 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR26 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR26 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR26 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR27 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR27 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR27 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR27 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR28 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR28 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR28 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR28 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR29 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR29 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR29 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR29 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR30 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR30 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR30 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR30 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/PCR31 -name DSE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name IRQC -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PCR31 -name ISF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name LK -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name MUX -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/PCR31 -name ODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name PFE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name PS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PCR31 -name SRE -bitoffset 2  -width 1 
 
imodeladdfield -mmregister $addBlock/GPCLR -name GPWD -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/GPCLR -name GPWE -bitoffset 16  -width 16  
 
imodeladdfield -mmregister $addBlock/GPCHR -name GPWD -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/GPCHR -name GPWE -bitoffset 16  -width 16  
 
imodeladdfield -mmregister $addBlock/ISFR -name ISF -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/DFER -name DFE -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/DFCR -name CS -bitoffset 0  -width 1   
 
imodeladdfield -mmregister $addBlock/DFWR -name FILT -bitoffset 0  -width 5
