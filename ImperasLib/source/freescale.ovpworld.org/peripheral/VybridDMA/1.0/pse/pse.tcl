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
set name    VybridDMA
set version 1.0
set desc "Freescale Vybrid Direct Memory Access Controller"
set limitations "Only models control register read/write - control register CX and ECX bits are modeled as RAZ/WI"
set reference "Freescale Vybrid Peripheral User Guide"

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
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text $reference

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x1400 -port bport1 -width 32  

set addBlock     "bport1/ab"



# Temporarily changed CR Mask from 0x00030ffe for MQX to boot
#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
CR              0x00 rw regReadCR regWriteCR - - 0x00000400 0x000305fe "Control Register, offset: 0x0 "	
ES              0x04 r  regReadES -          - -          0x00000000 - "Error Status Register, offset: 0x4 "	
ERQ             0x0c rw regRead32 regWrite32 - - 0x00000000 0xffffffff "Enable Request Register, offset: 0xC "	
EEI             0x14 rw regRead32 regWrite32 - - 0x00000000 0xffffffff ""	

CS_EEI_ERC      0x18 rw regReadZero regSetGroup - - - 0xdfdfdfdf "Clear/Set EEI, ERC"
DNE_SRT_ERR_INT 0x1c rw regReadZero regSetGroup - - - 0xdfdfdfdf "Clear/Set DNE, START, ERR, INT registers"	

INT             0x24 rw regRead32 regWrite1c - - 0x00000000 0xffffffff ""	
ERR             0x2c rw regRead32 regWrite1c - - 0x00000000 0xffffffff "Error Register, offset: 0x2C "	
HRS             0x34 rw regRead32 regWrite32 - - 0x00000000 0xffffffff ""	
EARS            0x44 rw - - - - 0x00000000 0xffffffff "Enable Asyncronous Request"
DCHPRI3_0       0x100 rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf "Channel n Priority Registers 3 to 0"	
DCHPRI7_4       0x104 rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
DCHPRI11_8      0x108 rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
DCHPRI15_12     0x10c rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
DCHPRI19_16     0x110 rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
DCHPRI23_20     0x114 rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
DCHPRI27_24     0x118 rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
DCHPRI31_28     0x11c rw regReadCHPRI regWriteCHPRI - - - 0xcfcfcfcf ""	
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

# There are 32 sets of the following registers with the name:
#	TCDn_<regName>
#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set tcd_registers {	
SADDR           0x1000 rw regReadTCD   regWriteTCD    - - - 0xffffffff "TCD Source Address"	
SOFF_ATTR       0x1004 rw regReadTCD16 regWriteTCD16  - - - 0xffffffff "TCD Signed Source Address Offset"	
NBYTES          0x1008 rw regReadTCD   regWriteTCD    - - - 0xffffffff "TCD Signed Minor Loop Offset, Minor Loop Disabled"
SLAST           0x100c rw regReadTCD   regWriteTCD    - - - 0xffffffff ""	
DADDR           0x1010 rw regReadTCD   regWriteTCD    - - - 0xffffffff ""	
DOFF_CITER      0x1014 rw regReadTCD16 regWriteTCD16  - - - 0xffffffff ""	
DLASTSGA        0x1018 rw regReadTCD   regWriteTCD    - - - 0xffffffff ""	
CSR_BITER       0x101c rw regReadTCD16 regWriteTCD16  - - - 0xffffffff ""	
}

for {set idx 0} {$idx < 32} {incr idx} {
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

		set locOffset [expr $offset + ($idx * 0x20)]
		set locName TCD${idx}_${rname}

    	set cmd "imodeladdmmregister -name $locName -addressblock $addBlock -offset $locOffset -access $raccess $r $w $v $u $m"
    	eval $cmd

    	if { $reset != "-" } {
        	imodeladdreset -mmregister $addBlock/$locName -name Reset -value $reset
    	}

    	iadddocumentation -name Description -text $desc -handle "$addBlock/$locName"
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
	iadddocumentation -name Description -text "DMA Done. Interrupt port"


# 09-21-2014 PRE:
# 	The Channel priority (DCHPRI0-31) and TCD(0-31) are mapped by a structure inside
# 	the model. So no registers are added in the pse.tcl. 	
 
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
 
imodeladdfield -mmregister $addBlock/ERQ -name ERQ0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ24 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ25 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ26 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ27 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ28 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ29 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ30 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ31 -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/ERQ -name ERQ9 -bitoffset 9  -width 1	
 
imodeladdfield -mmregister $addBlock/EEI -name EEI0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI24 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI25 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI26 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI27 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI28 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI29 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI30 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI31 -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/EEI -name EEI9 -bitoffset 9  -width 1	
 
# 09-21-2014 PRE: The combined CEEI, SEEI, CERQ, SERQ, CDNE, SSRT, CERR, and CINT
#  are tracked by an internal structure in the model. No registers are required.
 
imodeladdfield -mmregister $addBlock/INT -name INT0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT24 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT25 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT26 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT27 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT28 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT29 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT30 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT31 -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/INT -name INT9 -bitoffset 9  -width 1	
 
imodeladdfield -mmregister $addBlock/ERR -name ERR0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR24 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR25 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR26 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR27 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR28 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR29 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR30 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR31 -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/ERR -name ERR9 -bitoffset 9  -width 1	
 
imodeladdfield -mmregister $addBlock/HRS -name HRS0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS24 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS25 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS26 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS27 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS28 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS29 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS30 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS31 -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/HRS -name HRS9 -bitoffset 9  -width 1	

imodeladdfield -mmregister $addBlock/EARS -name EDREQ_0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_10 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_11 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_12 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_13 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_14 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_15 -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_16 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_17 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_18 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_19 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_20 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_21 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_22 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_23 -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_24 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_25 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_26 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_27 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_28 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_29 -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_30 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_31 -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_7 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_8 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/EARS -name EDREQ_9 -bitoffset 9  -width 1	
 

