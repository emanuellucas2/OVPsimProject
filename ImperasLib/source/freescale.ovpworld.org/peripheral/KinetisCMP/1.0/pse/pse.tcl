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
set name    KinetisCMP
set version 1.0
set desc "Model of the CMP peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

set range 0x08

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
imodeladdaddressblock -name ab     -size 0x08 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CR0             0x00 rw - - - - 0x00 0x73 "CMP Control Register 0, offset: 0x0 "    
CR1             0x01 rw - writeCR1 - - 0x00 0xd7 "CMP Control Register 1, offset: 0x1 " 
FPR             0x02 rw - - - - 0x00 0xff "CMP Filter Period Register, offset: 0x2 "    
SCR             0x03 rw - writeSCR - - 0x00 0x5e "CMP Status and Control Register, offset: 0x3 "    
DACCR           0x04 rw - writeDAC - - 0x00 0xff "DAC Control Register, offset: 0x4 "   
MUXCR           0x05 rw - writeMUX - - 0x00 0x3f "MUX Control Register, offset: 0x5 "
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

imodeladdnetport -name ExtSample -type input -updatefunction extSampleCB
imodeladdnetport -name Vin1      -type input
imodeladdnetport -name Vin2      -type input
imodeladdnetport -name Input0    -type input -updatefunction input0CB
imodeladdnetport -name Input1    -type input -updatefunction input1CB
imodeladdnetport -name Input2    -type input -updatefunction input2CB
imodeladdnetport -name Input3    -type input -updatefunction input3CB
imodeladdnetport -name Input4    -type input -updatefunction input4CB
imodeladdnetport -name Input5    -type input -updatefunction input5CB
imodeladdnetport -name Input6    -type input -updatefunction input6CB
imodeladdnetport -name Input7    -type input -updatefunction input7CB
imodeladdnetport -name DacOutput -type output
imodeladdnetport -name CoutSoc   -type output
imodeladdnetport -name Interrupt -type output
imodeladdnetport -name DmaReq    -type output
imodeladdnetport -name CmpOPad   -type output

 
imodeladdfield -mmregister $addBlock/CR0 -name FILTER_CNT -bitoffset 4  -width 3
imodeladdfield -mmregister $addBlock/CR0 -name HYSTCTR -bitoffset 0  -width 2   
 
imodeladdfield -mmregister $addBlock/CR1 -name COS -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/CR1 -name EN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR1 -name INV -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CR1 -name OPE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/CR1 -name PMODE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CR1 -name SE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CR1 -name WE -bitoffset 6  -width 1    
 
imodeladdfield -mmregister $addBlock/FPR -name FILT_PER -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/SCR -name CFF -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SCR -name CFR -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SCR -name COUT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SCR -name DMAEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SCR -name IEF -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SCR -name IER -bitoffset 4  -width 1   
 
imodeladdfield -mmregister $addBlock/DACCR -name DACEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/DACCR -name VOSEL -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/DACCR -name VRSEL -bitoffset 6  -width 1   
 
imodeladdfield -mmregister $addBlock/MUXCR -name MSEL -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/MUXCR -name PSEL -bitoffset 3  -width 3

#
# Formals
#
imodeladdformal -name cmpNumber -type uns32 -min 0 -max 3
iadddocumentation -name Description -text "Comparator channel number: 0,1,2 or3  (default 0)"
imodeladdformal -name stimFile -type string 
iadddocumentation -name Description -text "Stimulus file for the comparator"

imodeladdformal -name configure_cr0 -type uns32 
imodeladdformal -name configure_cr1 -type uns32 
imodeladdformal -name configure_fpr -type uns32 
imodeladdformal -name configure_scr -type uns32 
imodeladdformal -name configure_daccr -type uns32 
imodeladdformal -name configure_muxcr -type uns32 
