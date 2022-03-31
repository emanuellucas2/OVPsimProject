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
set name    VybridQUADSPI
set version 1.0
set desc "Model of the QUADSPI peripheral used on the Freescale Vybrid platform"
set limitations "Provides the base behaviour for the OVP Freescale Vybrid platforms"

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
iadddocumentation -name Reference -text "Development based on document number: VYBRIDRM Rev. 5, 07/2013"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x410 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
MCR             0x00 rw - - - - 0x000f4000 0xff004ccf "Module Configuration Register, offset: 0x0"	
IPCR            0x08 rw - - - - 0x00000000 0x0f01ffff "IP Configuration Register, offset: 0x8"	
FLSHCR          0x0c rw - - - - 0x00000303 0x00000f0f "Flash Configuration Register, offset: 0xC"	
BUF0CR          0x10 rw - - - - 0x00000000 0x8000ff0f "Buffer0 Configuration Register, offset: 0x10"	
BUF1CR          0x14 rw - - - - 0x00000000 0x0000ff0f "Buffer1 Configuration Register, offset: 0x14"	
BUF2CR          0x18 rw - - - - 0x00000000 0x0000ff0f "Buffer2 Configuration Register, offset: 0x18"	
BUF3CR          0x1c rw - - - - 0x00000000 0x8000ff0f "Buffer3 Configuration Register, offset: 0x1C"	
BFGENCR         0x20 rw - - - - 0x00000000 0x0001f000 "Buffer Generic Configuration Register, offset: 0x20"	
BUF0IND         0x30 rw - - - - 0x00000000 0xfffffff8 "Buffer0 Top Index Register, offset: 0x30"	
BUF1IND         0x34 rw - - - - 0x00000000 0xfffffff8 "Buffer1 Top Index Register, offset: 0x34"	
BUF2IND         0x38 rw - - - - 0x00000000 0xfffffff8 "Buffer2 Top Index Register, offset: 0x38"	
SFAR            0x100 rw - - - - 0x00000000 0xffffffff "Serial Flash Address Register, offset: 0x100"	
SMPR            0x108 rw - - - - 0x00000000 0x00070067 "Sampling Register, offset: 0x108"	
RBSR            0x10c r  - - - - 0x00000000 - "RX Buffer Status Register, offset: 0x10C"	
RBCT            0x110 rw - - - - 0x00000000 0x0000011f "RX Buffer Control Register, offset: 0x110"	
TBSR            0x150 r  - - - - 0x00000000 - "TX Buffer Status Register, offset: 0x150"	
TBDR            0x154 rw - - - - 0x00000000 0xffffffff "TX Buffer Data Register, offset: 0x154"	
SR              0x15c r  - - - - 0x00003800 - "Status Register, offset: 0x15C"	
FR              0x160 rw - - - - 0x08000000 0x8c8398d1 "Flag Register, offset: 0x160"	
RSER            0x164 rw - - - - 0x00000000 0x8c8398d1 "Interrupt and DMA Request Select and Enable Register, offset: 0x164"	
SPNDST          0x168 r  - - - - 0x00000000 - "Sequence Suspend Status Register, offset: 0x168"	
SPTRCLR         0x16c rw - - - - 0x00000000 0x00000101 "Sequence Pointer Clear Register, offset: 0x16C"	
SFA1AD          0x180 rw - - - - 0x00000000 0xfffffc00 "Serial Flash A1 Top Address, offset: 0x180"	
SFA2AD          0x184 rw - - - - 0x00000000 0xfffffc00 "Serial Flash A2 Top Address, offset: 0x184"	
SFB1AD          0x188 rw - - - - 0x00000000 0xfffffc00 "Serial Flash B1Top Address, offset: 0x188"	
SFB2AD          0x18c rw - - - - 0x00000000 0xfffffc00 "Serial Flash B2Top Address, offset: 0x18C"	
LUTKEY          0x300 rw readLutKey writeLutKey - - 0x5af05af0 0xffffffff "LUT Key Register, offset: 0x300"	
LCKCR           0x304 rw readLutLck writeLutLck - - 0x00000002 0x00000003 "LUT Lock Configuration Register, offset: 0x304"	
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

# RBDR0-31        0x200 rw - - - - 0x00000000 - "RX Buffer Data Register, offset: 0x200"	
set RBDRBaseAddress 0x200
for {set idx 0} {$idx < 64} {incr idx} {	
	set locOffset [expr $RBDRBaseAddress + ($idx * 0x4)]
	set locName RBDR${idx}

	imodeladdmmregister -name $locName -addressblock $addBlock -offset $locOffset -access rw -writemask 0xffffffff
	imodeladdreset -mmregister $addBlock/$locName -name Reset -value 0x00000000
	iadddocumentation -name Description -text "RX Buffer DataRegister $idx offset base 0x200: array step: 0x4" -handle "$addBlock/$locName"
}

# LUT0-63         0x310 rw - - - - 0x00000000 - "Look-up Table register, array offset: 0x310, array step: 0x4"
set LutBaseAddress 0x310
for {set idx 0} {$idx < 64} {incr idx} {	
	set locOffset [expr $LutBaseAddress + ($idx * 0x4)]
	set locName LUT${idx}

	imodeladdmmregister -name $locName -addressblock $addBlock -offset $locOffset -access rw -writemask 0xffffffff
	imodeladdreset -mmregister $addBlock/$locName -name Reset -value 0x00000000
	iadddocumentation -name Description -text "Look-up Table register $idx, array offset base 0x310:  , array step: 0x4" -handle "$addBlock/$locName"
}

imodeladdnetport -name Reset     -type input
 
imodeladdfield -mmregister $addBlock/MCR -name CLR_RXF -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/MCR -name CLR_TXF -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/MCR -name DDR_EN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/MCR -name DQS_EN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/MCR -name END_CFG -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/MCR -name MDIS -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SCLKCFG -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/MCR -name SWRSTHD -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SWRSTSD -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/IPCR -name IDATSZ -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/IPCR -name PAR_EN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/IPCR -name SEQID -bitoffset 24  -width 4	
 
imodeladdfield -mmregister $addBlock/FLSHCR -name TCSH -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/FLSHCR -name TCSS -bitoffset 0  -width 4	
 
imodeladdfield -mmregister $addBlock/BUF0CR -name ADATSZ -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/BUF0CR -name HP_EN -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/BUF0CR -name MSTRID -bitoffset 0  -width 4	
 
imodeladdfield -mmregister $addBlock/BUF1CR -name ADATSZ -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/BUF1CR -name MSTRID -bitoffset 0  -width 4	
 
imodeladdfield -mmregister $addBlock/BUF2CR -name ADATSZ -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/BUF2CR -name MSTRID -bitoffset 0  -width 4	
 
imodeladdfield -mmregister $addBlock/BUF3CR -name ADATSZ -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/BUF3CR -name ALLMST -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/BUF3CR -name MSTRID -bitoffset 0  -width 4	
 
imodeladdfield -mmregister $addBlock/BFGENCR -name PAR_EN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/BFGENCR -name SEQID -bitoffset 12  -width 4	
 
imodeladdfield -mmregister $addBlock/BUF0IND -name TPINDX0 -bitoffset 3  -width 29	
 
imodeladdfield -mmregister $addBlock/BUF1IND -name TPINDX1 -bitoffset 3  -width 29	
 
imodeladdfield -mmregister $addBlock/BUF2IND -name TPINDX2 -bitoffset 3  -width 29	

imodeladdfield -mmregister $addBlock/SFAR -name SFADR -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/SMPR -name DDRSMP -bitoffset 16  -width 3
imodeladdfield -mmregister $addBlock/SMPR -name FSDLY -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SMPR -name FSPHS -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SMPR -name HSDLY -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SMPR -name HSENA -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SMPR -name HSPHS -bitoffset 1  -width 1	
 
imodeladdfield -mmregister $addBlock/RBSR -name RDBFL -bitoffset 8  -width 6
imodeladdfield -mmregister $addBlock/RBSR -name RDCTR -bitoffset 16  -width 16	
 
imodeladdfield -mmregister $addBlock/RBCT -name RXBRD -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/RBCT -name WMRK -bitoffset 0  -width 5	
 
imodeladdfield -mmregister $addBlock/TBSR -name TRBFL -bitoffset 8  -width 5
imodeladdfield -mmregister $addBlock/TBSR -name TRCTR -bitoffset 16  -width 16	
 
imodeladdfield -mmregister $addBlock/TBDR -name TXDATA -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/SR -name AHB0FUL -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB0NE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB1FUL -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB1NE -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB2FUL -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB2NE -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB3FUL -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB3NE -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHB_ACC -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHBGNT -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SR -name AHBTRN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SR -name BUSY -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SR -name DLPSMP -bitoffset 29  -width 3
imodeladdfield -mmregister $addBlock/SR -name IP_ACC -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SR -name RXDMA -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/SR -name RXFULL -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/SR -name RXWE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/SR -name TXFULL -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/SR -name TXNE -bitoffset 24  -width 1	
 
imodeladdfield -mmregister $addBlock/FR -name ABOF -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/FR -name ABSEF -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/FR -name DLPFF -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/FR -name ILLINE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/FR -name IPAEF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FR -name IPGEF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/FR -name IPIEF -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/FR -name IUEF -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/FR -name RBDF -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/FR -name RBOF -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/FR -name TBFF -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/FR -name TBUF -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/FR -name TFF -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/RSER -name ABOIE -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/RSER -name ABSEIE -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/RSER -name DLPFIE -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/RSER -name ILLINIE -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/RSER -name IPAEIE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/RSER -name IPGEIE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/RSER -name IPIEIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/RSER -name IUEIE -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/RSER -name RBDDE -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/RSER -name RBDIE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/RSER -name RBOIE -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TBFIE -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TBUIE -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TFIE -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/SPNDST -name DATLFT -bitoffset 9  -width 7
imodeladdfield -mmregister $addBlock/SPNDST -name SPDBUF -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/SPNDST -name SUSPND -bitoffset 0  -width 1	
 
imodeladdfield -mmregister $addBlock/SPTRCLR -name BFPTRC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SPTRCLR -name IPPTRC -bitoffset 8  -width 1	
 
imodeladdfield -mmregister $addBlock/SFA1AD -name TPADA1 -bitoffset 10  -width 22	
 
imodeladdfield -mmregister $addBlock/SFA2AD -name TPADA2 -bitoffset 10  -width 22	
 
imodeladdfield -mmregister $addBlock/SFB1AD -name TPADB1 -bitoffset 10  -width 22	
 
imodeladdfield -mmregister $addBlock/SFB2AD -name TPADB2 -bitoffset 10  -width 22	
 
for {set idx 0} {$idx < 31} {incr idx} {	
	imodeladdfield -mmregister $addBlock/RBDR$idx -name RXDATA -bitoffset 0  -width 32	
}
 
imodeladdfield -mmregister $addBlock/LUTKEY -name KEY -bitoffset 0  -width 32	
 
imodeladdfield -mmregister $addBlock/LCKCR -name LOCK -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/LCKCR -name UNLOCK -bitoffset 1  -width 1

for {set idx 0} {$idx < 64} {incr idx} {	
	imodeladdfield -mmregister $addBlock/LUT$idx -name OPRND0 -bitoffset 0  -width 8	
	imodeladdfield -mmregister $addBlock/LUT$idx -name PAD0 -bitoffset 8  -width 2	
	imodeladdfield -mmregister $addBlock/LUT$idx -name INSTR0 -bitoffset 10  -width 6	
	imodeladdfield -mmregister $addBlock/LUT$idx -name OPRND1 -bitoffset 16  -width 8	
	imodeladdfield -mmregister $addBlock/LUT$idx -name PAD1 -bitoffset 24  -width 2	
	imodeladdfield -mmregister $addBlock/LUT$idx -name INSTR1 -bitoffset 26  -width 6	
}

