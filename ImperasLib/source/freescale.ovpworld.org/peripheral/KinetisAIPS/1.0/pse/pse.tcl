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
set name    KinetisAIPS
set version 1.0
set desc "Model of the AIPS peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x70 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
MPRA            0x00 rw - - - - 0 0x77777777 "Master Privilege Register A, offset: 0x0 "    
PACRA           0x20 rw - - - - 0x44444444 0x77777777 "Peripheral Access Control Register, offset: 0x20 "   
PACRB           0x24 rw - - - - 0x44444444 0x77777777 "Peripheral Access Control Register, offset: 0x24 "   
PACRC           0x28 rw - - - - 0x44444444 0x77777777 "Peripheral Access Control Register, offset: 0x28 "   
PACRD           0x2c rw - - - - 0x44444444 0x77777777 "Peripheral Access Control Register, offset: 0x2C "   
PACRE           0x40 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x40 "    
PACRF           0x44 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x44 "    
PACRG           0x48 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x48 "    
PACRH           0x4c rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x4C "    
PACRI           0x50 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x50 "    
PACRJ           0x54 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x54 "    
PACRK           0x58 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x58 "    
PACRL           0x5c rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x5C "    
PACRM           0x60 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x60 "    
PACRN           0x64 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x64 "    
PACRO           0x68 rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x68 "    
PACRP           0x6c rw - - - - 0 0x77777777 "Peripheral Access Control Register, offset: 0x6C "
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

    
 
imodeladdfield -mmregister $addBlock/MPRA -name MPL7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MPL0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTW0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/MPRA -name MTR0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRA -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRA -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRB -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRB -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRC -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRC -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRD -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRD -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRE -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRE -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRF -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRF -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRG -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRG -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRH -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRH -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRI -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRI -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRJ -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRJ -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRK -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRK -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRL -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRL -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRM -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRM -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRN -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRN -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRO -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRO -name SP0 -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/PACRP -name TP7 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP7 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP7 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP6 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP6 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP5 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP5 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP5 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP4 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP4 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP4 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP3 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP3 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP3 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP1 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP1 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name TP0 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name WP0 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/PACRP -name SP0 -bitoffset 30  -width 1
