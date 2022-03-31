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
set name    KinetisDMA
set version 1.0
set desc "Model of the DMA peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

set range 0x2000

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
imodeladdaddressblock -name ab     -size 0x1000 -port bport1 -width 32  

set addBlock     "bport1/ab"



# Temporarily changed CR Mask from 0x00030ffe for MQX to boot
#   name      offset ac readFn    writeFn          viewFn   user reset      mask description   
set registers { 
CR              0x00  rw regReadCR    regWriteCR    -       -    0x00000000 0x00030ffe "Control Register, offset: 0x0" 
ES              0x04  r  regReadES    -             -       -    0x00000000 -          "Error Status Register, offset: 0x4"    
ERQ             0x0c  rw regRead32    regWrite32    -       -    0x00000000 0xffffffff "Enable Request Register, offset: 0xC"  
EEI             0x14  rw regRead32    regWrite32    -       -    0x00000000 0xffffffff ""   
                                                                 
CS_EEI_ERC      0x18  rw regReadZero  regSetGroup   -       -    -          0xdfdfdfdf "Clear/Set EEI, ERC"
DNE_SRT_ERR_INT 0x1c  rw regReadZero  regSetGroup   -       -    -          0xdfdfdfdf "Clear/Set DNE, START, ERR, INT registers" 
                                                                            
INT             0x24  rw regRead32    regWrite1c    -       -    0x00000000 0xffffffff ""   
ERR             0x2c  rw regRead32    regWrite1c    -       -    0x00000000 0xffffffff "Error Register, offset: 0x2C"  
HRS             0x34  rw regRead32    regWrite32    -       -    0x00000000 0xffffffff ""   
DCHPRI3_0       0x100 rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "Channel n Priority Registers 3 to 0"  
DCHPRI7_4       0x104 rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
DCHPRI11_8      0x108 rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
DCHPRI15_12     0x10c rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
DCHPRI19_16     0x110 rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
DCHPRI23_20     0x114 rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
DCHPRI27_24     0x118 rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
DCHPRI31_28     0x11c rw regReadCHPRI regWriteCHPRI -       -    -          0xcf       "" 
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

imodeladdaddressblock -name TCD%u   -offset 0x1000   -size 0x20 -port bport1 -width 32   -loarray 0 -hiarray 31

# There are 32 sets of the following registers with the name:
#   TCDn_<regName>
#   name        offset ac  readFn      writeFn       viewFn   user reset  mask  description   
set tcd_registers { 
SADDR           0x0000 rw regReadTCD   regWriteTCD    -       -    -     -      "TCD Source Address" 
SOFF_ATTR       0x0004 rw regReadTCD16 regWriteTCD16  -       -    -     -      "TCD Signed Source Address Offset"   
NBYTES          0x0008 rw regReadTCD   regWriteTCD    -       -    -     -      "TCD Signed Minor Loop Offset, Minor Loop Disabled"
SLAST           0x000c rw regReadTCD   regWriteTCD    -       -    -     -      ""   
DADDR           0x0010 rw regReadTCD   regWriteTCD    -       -    -     -      ""   
DOFF_CITER      0x0014 rw regReadTCD16 regWriteTCD16  -       -    -     -      ""   
DLASTSGA        0x0018 rw regReadTCD   regWriteTCD    -       -    -     -      ""   
CSR_BITER       0x001c rw regReadTCD16 regWriteTCD16  -       -    -     -      ""   
}                                                                  

foreach { rname offset raccess readFn writeFn viewFn user reset mask desc } $tcd_registers {
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

    set cmd "imodeladdmmregister -name $rname -addressblock bport1/TCD%u -offset 0 -access $raccess $r $w $v $u $m"
    eval $cmd

    iadddocumentation -name Description -text $desc

    if { $reset != "-" } {
        imodeladdreset -name Reset -value $reset
    }
}

imodeladdnetport -name Reset     -type input -updatefunction DMAReset

imodeladdnetport -name eDMARequest -type input -updatefunction DMARequest
imodeladdnetport -name eDMADone -type output

# Read/Write of SRAM.
imodeladdbusmasterport -name "MREAD" -addresswidth 32
iadddocumentation -name Description -text "DMA Master Read of address space"
imodeladdbusmasterport -name "MWRITE" -addresswidth 32
iadddocumentation -name Description -text "DMA Master Write of address space"

# Error/DMADone interrupts.
imodeladdnetport -name errorInterrupt -type output
iadddocumentation -name Description -text "DMA Error Interrupt port"

imodeladdnetport -name dmaInterrupt_ch%u -type output -loarray 0 -hiarray 31
    iadddocumentation -name Description -text "DMA Done Interrupt"

# 09-21-2014 PRE:
#   The Channel priority (DCHPRI0-31) and TCD(0-31) are mapped by a structure inside
#   the model. So no registers are added in the pse.tcl.    
 
imodeladdfield -mmregister $addBlock/CR -name CLM -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/CR -name CX -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/CR -name ECX -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR -name EDBG -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/CR -name EMLM -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CR -name ERCA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/CR -name ERGA -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/CR -name GRP0PRI -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/CR -name GRP1PRI -bitoffset 10  -width 2
imodeladdfield -mmregister $addBlock/CR -name HALT -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/CR -name HOE -bitoffset 4  -width 1    
 
imodeladdfield -mmregister $addBlock/ES -name CPE -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/ES -name DAE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ES -name DBE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ES -name DOE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ES -name ECX -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ES -name ERRCHN -bitoffset 8  -width 5
imodeladdfield -mmregister $addBlock/ES -name GPE -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/ES -name NCE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ES -name SAE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ES -name SBE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ES -name SGE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ES -name SOE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ES -name VLD -bitoffset 31  -width 1   
 
for {set idx 0} {$idx < 32} {incr idx} {
    imodeladdfield -mmregister $addBlock/ERQ -name ERQ$idx  -bitoffset $idx  -width 1
    imodeladdfield -mmregister $addBlock/EEI -name EEI0$idx -bitoffset $idx  -width 1
    imodeladdfield -mmregister $addBlock/INT -name INT$idx  -bitoffset $idx  -width 1
    imodeladdfield -mmregister $addBlock/ERR -name ERR$idx  -bitoffset $idx  -width 1
    imodeladdfield -mmregister $addBlock/HRS -name HRS$idx  -bitoffset $idx  -width 1
}
 
# 09-21-2014 PRE: The combined CEEI, SEEI, CERQ, SERQ, CDNE, SSRT, CERR, and CINT
#  are tracked by an internal structure in the model. No registers are required.
 

 

