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
set name    KinetisRTC
set version 1.0
set desc "Model of the RTC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x808 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
TSR             0x00 rw - - - - 0x00000000 0xffffffff "RTC Time Seconds Register, offset: 0x0 " 
TPR             0x04 rw - - - - 0x00000000 0x0000ffff "RTC Time Prescaler Register, offset: 0x4 "   
TAR             0x08 rw - - - - 0x00000000 0xffffffff "RTC Time Alarm Register, offset: 0x8 "   
TCR             0x0c rw - - - - 0x00000000 0x0000ffff "RTC Time Compensation Register, offset: 0xC "    
CR              0x10 rw - - - - 0x00000000 0x00003f0f "RTC Control Register, offset: 0x10 " 
SR              0x14 rw - - - - 0x00000001 0x00000010 "RTC Status Register, offset: 0x14 "  
LR              0x18 rw - - - - 0x0000ffff 0x0000ff78 "RTC Lock Register, offset: 0x18 "    
IER             0x1c rw - - - - 0x00000007 0x0000001f "RTC Interrupt Enable Register, offset: 0x1C "    
TTSR            0x20 r  - - - - 0x00000000 0x00000000 "RTC Tamper Time Seconds Register, offset: 0x20 " 
MER             0x24 rw - - - - 0x00000000 0x0000001f "RTC Monotonic Enable Register, offset: 0x24 "    
MCLR            0x28 rw - - - - 0x00000000 0xffffffff "RTC Monotonic Counter Low Register, offset: 0x28 "   
MCHR            0x2c rw - - - - 0x00000000 0xffffffff "RTC Monotonic Counter High Register, offset: 0x2C "  
TER             0x30 rw - - - - 0x00000000 0x0000003e "RTC Tamper Enable Register, offset: 0x30 "   
TDR             0x34 rw - - - - 0x00000000 0x0000003e "RTC Tamper Detect Register, offset: 0x34 "   
TTR             0x38 rw - - - - 0x00000000 0x0003ffff "RTC Tamper Trim Register, offset: 0x38 " 
TIR             0x3c rw - - - - 0x00000000 0x0000003e "RTC Tamper Interrupt Register, offset: 0x3C "    
WAR             0x800 rw - - - - 0x0000ffff 0x0000ffff "RTC Write Access Register, offset: 0x800 "  
RAR             0x804 rw - - - - 0x0000ffff 0x0000ffff "RTC Read Access Register, offset: 0x804 "
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

    
 
imodeladdfield -mmregister $addBlock/TSR -name TSR -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/TPR -name TPR -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/TAR -name TAR -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/TCR -name CIC -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/TCR -name CIR -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/TCR -name TCR -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/TCR -name TCV -bitoffset 16  -width 8  
 
imodeladdfield -mmregister $addBlock/CR -name CLKO -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CR -name OSCE -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CR -name SC16P -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/CR -name SC2P -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/CR -name SC4P -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/CR -name SC8P -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/CR -name SUP -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/CR -name SWR -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR -name UM -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CR -name WPE -bitoffset 1  -width 1    
 
imodeladdfield -mmregister $addBlock/SR -name MOF -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SR -name TAF -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SR -name TCE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SR -name TIF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SR -name TOF -bitoffset 1  -width 1    
 
imodeladdfield -mmregister $addBlock/LR -name CRL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/LR -name LRL -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/LR -name MCHL -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/LR -name MCLL -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/LR -name MEL -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/LR -name SRL -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/LR -name TCL -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/LR -name TDL -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/LR -name TEL -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/LR -name TIL -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/LR -name TTL -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/LR -name TTSL -bitoffset 8  -width 1   
 
imodeladdfield -mmregister $addBlock/IER -name MOIE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/IER -name TAIE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IER -name TIIE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IER -name TOIE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/IER -name TSIE -bitoffset 4  -width 1  
 
imodeladdfield -mmregister $addBlock/TTSR -name TTS -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/MER -name MCE -bitoffset 4  -width 1   
 
imodeladdfield -mmregister $addBlock/MCLR -name MCL -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/MCHR -name MCH -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/TER -name CTE -bitoffset 2  -width 1
# 8_28_2014 PRE - DTE not found in documentation
imodeladdfield -mmregister $addBlock/TER -name DTE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TER -name FSE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/TER -name TME -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/TER -name TTE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/TER -name VTE -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/TDR -name CTF -bitoffset 2  -width 1
# 8_28_2014 PRE - DTF not found in documentation
imodeladdfield -mmregister $addBlock/TDR -name DTF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TDR -name FSF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/TDR -name TMF -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/TDR -name TTF -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/TDR -name VTF -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/TTR -name CDTH -bitoffset 6  -width 3
imodeladdfield -mmregister $addBlock/TTR -name CDTL -bitoffset 9  -width 3
imodeladdfield -mmregister $addBlock/TTR -name TDTH -bitoffset 12  -width 3
imodeladdfield -mmregister $addBlock/TTR -name TDTL -bitoffset 15  -width 3
imodeladdfield -mmregister $addBlock/TTR -name VDTH -bitoffset 3  -width 3  
imodeladdfield -mmregister $addBlock/TTR -name VDTL -bitoffset 0  -width 3  
 
imodeladdfield -mmregister $addBlock/TIR -name CTIE -bitoffset 2  -width 1
# 8_28_2014 PRE - DTIE at offset 0, not found in documentation
imodeladdfield -mmregister $addBlock/TIR -name DTIE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TIR -name FSIE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/TIR -name TMIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/TIR -name TTIE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/TIR -name VTIE -bitoffset 1  -width 1  
 
imodeladdfield -mmregister $addBlock/WAR -name CRW -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/WAR -name IERW -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/WAR -name LRW -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/WAR -name MCHW -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/WAR -name MCLW -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/WAR -name MERW -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/WAR -name SRW -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TARW -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TCRW -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TDRW -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TERW -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TIRW -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TPRW -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TSRW -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TTRW -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/WAR -name TTSW -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/RAR -name CRR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/RAR -name IERR -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/RAR -name LRR -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/RAR -name MCHR -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/RAR -name MCLR -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/RAR -name MERR -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/RAR -name SRR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TARR -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TCRR -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TDRR -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TERR -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TIRR -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TPRR -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TSRR -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TTRR -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/RAR -name TTSR -bitoffset 8  -width 1
