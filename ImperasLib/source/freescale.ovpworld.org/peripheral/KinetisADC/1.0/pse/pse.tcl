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
set name    KinetisADC
set version 1.0
set desc "Model of the ADC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x70     -port bport1 -width 32 

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {
    
SC1A            0x00 rw - - - - 0x001f 0x007f "ADC status and control registers 1, array offset: 0x0, array step: 0x4 " 
SC1B            0x04 rw - - - - 0x001f 0x007f "ADC status and control registers 1, array offset: 0x0, array step: 0x4 " 
CFG1            0x08 rw - - - - 0x0000 0x00ff "ADC configuration register 1, offset: 0x8 "  
CFG2            0x0c rw - - - - 0x0000 0x001f "Configuration register 2, offset: 0xC "  
RA              0x10 r  - - - - 0x0000 0x0 "ADC data result register, array offset: 0x10, array step: 0x4 " 
RB              0x14 r  - - - - 0x0000 0x0 "ADC data result register, array offset: 0x10, array step: 0x4 " 
CV1             0x18 rw - - - - 0x0000 0xffff "Compare value registers, offset: 0x18 "  
CV2             0x1c rw - - - - 0x0000 0xffff "Compare value registers, offset: 0x1C "  
SC2             0x20 rw - - - - 0x0000 0x007f "Status and control register 2, offset: 0x20 "    
SC3             0x24 rw - - - - 0x0000 0x008f "Status and control register 3, offset: 0x24 "    
OFS             0x28 rw - - - - 0x0004 0xffff "ADC offset correction register, offset: 0x28 "   
PG              0x2c rw - - - - 0x8200 0xffff "ADC plus-side gain register, offset: 0x2C "  
MG              0x30 rw - - - - 0x8200 0xffff "ADC minus-side gain register, offset: 0x30 " 
CLPD            0x34 rw - - - - 0x000a 0x003f "ADC plus-side general calibration value register, offset: 0x34 " 
CLPS            0x38 rw - - - - 0x0020 0x003f "ADC plus-side general calibration value register, offset: 0x38 " 
CLP4            0x3c rw - - - - 0x0200 0x03ff "ADC plus-side general calibration value register, offset: 0x3C " 
CLP3            0x40 rw - - - - 0x0100 0x01ff "ADC plus-side general calibration value register, offset: 0x40 " 
CLP2            0x44 rw - - - - 0x0080 0x00ff "ADC plus-side general calibration value register, offset: 0x44 " 
CLP1            0x48 rw - - - - 0x0040 0x007f "ADC plus-side general calibration value register, offset: 0x48 " 
CLP0            0x4c rw - - - - 0x0020 0x003f "ADC plus-side general calibration value register, offset: 0x4C " 
PGA             0x50 rw - - - - 0x0000 0xbf4000 "ADC PGA register, offset: 0x50 "   
CLMD            0x54 rw - - - - 0x000a 0x003f "ADC minus-side general calibration value register, offset: 0x54 "    
CLMS            0x58 rw - - - - 0x0020 0x003f "ADC minus-side general calibration value register, offset: 0x58 "    
CLM4            0x5c rw - - - - 0x0200 0x03ff "ADC minus-side general calibration value register, offset: 0x5C "    
CLM3            0x60 rw - - - - 0x0100 0x01ff "ADC minus-side general calibration value register, offset: 0x60 "    
CLM2            0x64 rw - - - - 0x0080 0x00ff "ADC minus-side general calibration value register, offset: 0x64 "    
CLM1            0x68 rw - - - - 0x0040 0x007f "ADC minus-side general calibration value register, offset: 0x68 "    
CLM0            0x6c rw - - - - 0x0020 0x003f "ADC minus-side general calibration value register, offset: 0x6C "
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
    
imodeladdnetport -name AltClk    -type input -updatefunction altClkCB
imodeladdnetport -name HwTrig    -type input -updatefunction hwTrigCB
imodeladdnetport -name AdIn      -type input
imodeladdnetport -name Vrefsh    -type input
imodeladdnetport -name Vrefsl    -type input
imodeladdnetport -name AdInId    -type output
imodeladdnetport -name Interrupt -type output
imodeladdnetport -name DmaReq    -type output


imodeladdfield -mmregister $addBlock/SC1A -name ADCH -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/SC1A -name AIEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SC1A -name COCO -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC1A -name DIFF -bitoffset 5  -width 1 

imodeladdfield -mmregister $addBlock/SC1B -name ADCH -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/SC1B -name AIEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SC1B -name COCO -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC1B -name DIFF -bitoffset 5  -width 1 

imodeladdfield -mmregister $addBlock/CFG1 -name ADICLK -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CFG1 -name ADIV -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/CFG1 -name ADLPC -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CFG1 -name ADLSMP -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/CFG1 -name MODE -bitoffset 2  -width 2 

imodeladdfield -mmregister $addBlock/CFG2 -name ADACKEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CFG2 -name ADHSC -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/CFG2 -name ADLSTS -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CFG2 -name MUXSEL -bitoffset 4  -width 1   

imodeladdfield -mmregister $addBlock/RA -name D -bitoffset 0  -width 16 

imodeladdfield -mmregister $addBlock/RB -name D -bitoffset 0  -width 16 

imodeladdfield -mmregister $addBlock/CV1 -name CV -bitoffset 0  -width 16   

imodeladdfield -mmregister $addBlock/CV2 -name CV -bitoffset 0  -width 16   

imodeladdfield -mmregister $addBlock/SC2 -name ACFE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SC2 -name ACFGT -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SC2 -name ACREN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SC2 -name ADACT -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC2 -name ADTRG -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SC2 -name DMAEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SC2 -name REFSEL -bitoffset 0  -width 2    

imodeladdfield -mmregister $addBlock/SC3 -name ADCO -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SC3 -name AVGE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SC3 -name AVGS -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/SC3 -name CAL -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC3 -name CALF -bitoffset 6  -width 1  

imodeladdfield -mmregister $addBlock/OFS -name OFS -bitoffset 0  -width 16  

imodeladdfield -mmregister $addBlock/PG -name PG -bitoffset 0  -width 16    

imodeladdfield -mmregister $addBlock/MG -name MG -bitoffset 0  -width 16    

imodeladdfield -mmregister $addBlock/CLPD -name CLPD -bitoffset 0  -width 6 

imodeladdfield -mmregister $addBlock/CLPS -name CLPS -bitoffset 0  -width 6 

imodeladdfield -mmregister $addBlock/CLP4 -name CLP4 -bitoffset 0  -width 10    

imodeladdfield -mmregister $addBlock/CLP3 -name CLP3 -bitoffset 0  -width 9 

imodeladdfield -mmregister $addBlock/CLP2 -name CLP2 -bitoffset 0  -width 8 

imodeladdfield -mmregister $addBlock/CLP1 -name CLP1 -bitoffset 0  -width 7 

imodeladdfield -mmregister $addBlock/CLP0 -name CLP0 -bitoffset 0  -width 6 

imodeladdfield -mmregister $addBlock/PGA -name PGACHPb -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/PGA -name PGAEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/PGA -name PGAG -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/PGA -name PGALPb -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/PGA -name PGAOFSM -bitoffset 14  -width 1  

imodeladdfield -mmregister $addBlock/CLMD -name CLMD -bitoffset 0  -width 6 

imodeladdfield -mmregister $addBlock/CLMS -name CLMS -bitoffset 0  -width 6 

imodeladdfield -mmregister $addBlock/CLM4 -name CLM4 -bitoffset 0  -width 10    

imodeladdfield -mmregister $addBlock/CLM3 -name CLM3 -bitoffset 0  -width 9 

imodeladdfield -mmregister $addBlock/CLM2 -name CLM2 -bitoffset 0  -width 8 

imodeladdfield -mmregister $addBlock/CLM1 -name CLM1 -bitoffset 0  -width 7 

imodeladdfield -mmregister $addBlock/CLM0 -name CLM0 -bitoffset 0  -width 6




imodeladdformal -name stimFile0 -type string
imodeladdformal -name bus_clock_freq -type uns32
imodeladdformal -name configure_sc1a -type uns32
imodeladdformal -name configure_sc1b -type uns32
imodeladdformal -name configure_cfg1 -type uns32
imodeladdformal -name configure_cfg2 -type uns32
imodeladdformal -name configure_cv1 -type uns32
imodeladdformal -name configure_cv2 -type uns32
imodeladdformal -name configure_sc2 -type uns32
imodeladdformal -name configure_sc3 -type uns32
imodeladdformal -name input_vrefh -type uns32
imodeladdformal -name input_vrefl -type uns32
