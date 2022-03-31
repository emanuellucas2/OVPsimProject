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
set name    KinetisI2C
set version 1.0
set desc "Model of the I2C peripheral used on the Freescale Kinetis platform"
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
A1              0x00 rw - - - - 0x00 0xfe "I2C Address Register 1, offset: 0x0 "    
F               0x01 rw - - - - 0x00 0xff "I2C Frequency Divider register, offset: 0x1 "    
C1              0x02 rw - - - - 0x00 0xff "I2C Control Register 1, offset: 0x2 "    
S               0x03 rw - - - - 0x80 0x56 "I2C Status Register, offset: 0x3 "   
D               0x04 rw - - - - 0x00 0xff "I2C Data I/O register, offset: 0x4 " 
C2              0x05 rw - - - - 0x00 0xff "I2C Control Register 2, offset: 0x5 "    
FLT             0x06 rw - - - - 0x00 0x1f "I2C Programmable Input Glitch Filter register, offset: 0x6 " 
RA              0x07 rw - - - - 0x00 0xfe "I2C Range Address register, offset: 0x7 "    
SMB             0x08 rw - - - - 0x00 0xfb "I2C SMBus Control and Status register, offset: 0x8 " 
A2              0x09 rw - - - - 0xc2 0xfe "I2C Address Register 2, offset: 0x9 "    
SLTH            0x0a rw - - - - 0x00 0xff "I2C SCL Low Timeout Register High, offset: 0xA " 
SLTL            0x0b rw - - - - 0x00 0xff "I2C SCL Low Timeout Register Low, offset: 0xB "
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

    
 
imodeladdfield -mmregister $addBlock/A1 -name AD -bitoffset 1  -width 7 
 
imodeladdfield -mmregister $addBlock/F -name ICR -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/F -name MULT -bitoffset 6  -width 2    
 
imodeladdfield -mmregister $addBlock/C1 -name DMAEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C1 -name IICEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C1 -name IICIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C1 -name MST -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C1 -name RSTA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C1 -name TX -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C1 -name TXAK -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C1 -name WUEN -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/S -name ARBL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/S -name BUSY -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/S -name IAAS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/S -name IICIF -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S -name RAM -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/S -name RXAK -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S -name SRW -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/S -name TCF -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/D -name DATA -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/C2 -name AD -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/C2 -name ADEXT -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C2 -name GCAEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C2 -name HDRS -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C2 -name RMEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C2 -name SBRC -bitoffset 4  -width 1   
 
imodeladdfield -mmregister $addBlock/FLT -name FLT -bitoffset 0  -width 5   
 
imodeladdfield -mmregister $addBlock/RA -name RAD -bitoffset 1  -width 7    
 
imodeladdfield -mmregister $addBlock/SMB -name ALERTEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SMB -name FACK -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SMB -name SHTF1 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SMB -name SHTF2 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SMB -name SHTF2IE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SMB -name SIICAEN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SMB -name SLTF -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SMB -name TCKSEL -bitoffset 4  -width 1    
 
imodeladdfield -mmregister $addBlock/A2 -name SAD -bitoffset 1  -width 7    
 
imodeladdfield -mmregister $addBlock/SLTH -name SSLT -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/SLTL -name SSLT -bitoffset 0  -width 8
