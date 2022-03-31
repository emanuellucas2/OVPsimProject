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
set name    KinetisSPI
set version 1.0
set desc "Model of the SPI peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x8c -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
MCR             0x00 rw - - - - 0x00004001 0xff3fff01 "DSPI Module Configuration Register, offset: 0x0 "    
TCR             0x08 rw - - - - 0x00000000 0xffff0000 "DSPI Transfer Count Register, offset: 0x8 "  
CTAR0           0x0c rw - - - - 0x78000000 0xffffffff "DSPI Clock and Transfer Attributes Register 0, Master/Slave modes, offset 0x0c"  
CTAR1           0x10 rw - - - - 0x78000000 0xffffffff "DSPI Clock and Transfer Attributes Register 1, Master mode, offset 0x10" 
SR              0x2c rw - - - - 0x00000000 0xda0a0000 "DSPI Status Register, offset: 0x2C " 
RSER            0x30 rw - - - - 0x00000000 0x9b0b0000 "DSPI DMA/Interrupt Request Select and Enable Register, offset: 0x30 "    
PUSHR           0x34 rw - - - - 0x00000000 0xffffffff "DSPI PUSH TX FIFO Register In Master Mode, offset: 0x34 "    
POPR            0x38 r  - - - - 0x00000000 - "DSPI POP RX FIFO Register, offset: 0x38 " 
TXFR0           0x3c r  - - - - 0x00000000 - "DSPI Transmit FIFO Registers, offset: 0x3C "  
TXFR1           0x40 r  - - - - 0x00000000 - "DSPI Transmit FIFO Registers, offset: 0x40 "  
TXFR2           0x44 r  - - - - 0x00000000 - "DSPI Transmit FIFO Registers, offset: 0x44 "  
TXFR3           0x48 r  - - - - 0x00000000 - "DSPI Transmit FIFO Registers, offset: 0x48 "  
RXFR0           0x7c r  - - - - 0x00000000 - "DSPI Receive FIFO Registers, offset: 0x7C "   
RXFR1           0x80 r  - - - - 0x00000000 - "DSPI Receive FIFO Registers, offset: 0x80 "   
RXFR2           0x84 r  - - - - 0x00000000 - "DSPI Receive FIFO Registers, offset: 0x84 "   
RXFR3           0x88 r  - - - - 0x00000000 - "DSPI Receive FIFO Registers, offset: 0x88 "
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

    
 
imodeladdfield -mmregister $addBlock/MCR -name CLR_RXF -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/MCR -name CLR_TXF -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/MCR -name CONT_SCKE -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/MCR -name DCONF -bitoffset 28  -width 2
imodeladdfield -mmregister $addBlock/MCR -name DIS_RXF -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/MCR -name DIS_TXF -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/MCR -name DOZE -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/MCR -name FRZ -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/MCR -name HALT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/MCR -name MDIS -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/MCR -name MSTR -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/MCR -name MTFE -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/MCR -name PCSIS -bitoffset 16  -width 6
imodeladdfield -mmregister $addBlock/MCR -name PCSSE -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/MCR -name ROOE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/MCR -name SMPL_PT -bitoffset 8  -width 2   
 
imodeladdfield -mmregister $addBlock/TCR -name SPI_TCNT -bitoffset 16  -width 16    
 
imodeladdfield -mmregister $addBlock/CTAR0 -name ASC -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CTAR0 -name BR -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CTAR0 -name CPHA -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/CTAR0 -name CPOL -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/CTAR0 -name CSSCK -bitoffset 12  -width 4
imodeladdfield -mmregister $addBlock/CTAR0 -name DBR -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/CTAR0 -name DT -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/CTAR0 -name FMSZ -bitoffset 27  -width 4
imodeladdfield -mmregister $addBlock/CTAR0 -name LSBFE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CTAR0 -name PASC -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CTAR0 -name PBR -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CTAR0 -name PCSSCK -bitoffset 22  -width 2
imodeladdfield -mmregister $addBlock/CTAR0 -name PDT -bitoffset 18  -width 2
# 08-31-2014 PRE: Following three are defined for 'Slave mode' in CTAR0
#imodeladdfield -mmregister $addBlock/CTAR0 -name SLAVE_CPHA -bitoffset 25  -width 1
#imodeladdfield -mmregister $addBlock/CTAR0 -name SLAVE_CPOL -bitoffset 26  -width 1
#imodeladdfield -mmregister $addBlock/CTAR0 -name SLAVE_FMSZ -bitoffset 27  -width 5    
 
imodeladdfield -mmregister $addBlock/CTAR1 -name ASC -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CTAR1 -name BR -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CTAR1 -name CPHA -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/CTAR1 -name CPOL -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/CTAR1 -name CSSCK -bitoffset 12  -width 4
imodeladdfield -mmregister $addBlock/CTAR1 -name DBR -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/CTAR1 -name DT -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/CTAR1 -name FMSZ -bitoffset 27  -width 4
imodeladdfield -mmregister $addBlock/CTAR1 -name LSBFE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CTAR1 -name PASC -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/CTAR1 -name PBR -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CTAR1 -name PCSSCK -bitoffset 22  -width 2
imodeladdfield -mmregister $addBlock/CTAR1 -name PDT -bitoffset 18  -width 2
 
imodeladdfield -mmregister $addBlock/SR -name EOQF -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/SR -name POPNXTPTR -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/SR -name RFDF -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/SR -name RFOF -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/SR -name RXCTR -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/SR -name TCF -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/SR -name TFFF -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/SR -name TFUF -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/SR -name TXCTR -bitoffset 12  -width 4
imodeladdfield -mmregister $addBlock/SR -name TXNXTPTR -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/SR -name TXRXS -bitoffset 30  -width 1 
 
imodeladdfield -mmregister $addBlock/RSER -name EOQF_RE -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/RSER -name RFDF_DIRS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/RSER -name RFDF_RE -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/RSER -name RFOF_RE -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TCF_RE -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TFFF_DIRS -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TFFF_RE -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/RSER -name TFUF_RE -bitoffset 27  -width 1 
 
imodeladdfield -mmregister $addBlock/PUSHR -name CONT -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/PUSHR -name CTAS -bitoffset 28  -width 3
imodeladdfield -mmregister $addBlock/PUSHR -name CTCNT -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/PUSHR -name EOQ -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/PUSHR -name PCS -bitoffset 16  -width 6
imodeladdfield -mmregister $addBlock/PUSHR -name TXDATA -bitoffset 0  -width 16 
# 08-31-2014 PRE: Following defined for Slave mode
#imodeladdfield -mmregister $addBlock/PUSHR -name SLAVE_TXDATA -bitoffset 0  -width 32
 
imodeladdfield -mmregister $addBlock/POPR -name RXDATA -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/TXFR0 -name TXCMD_TXDATA -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/TXFR0 -name TXDATA -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/TXFR1 -name TXCMD_TXDATA -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/TXFR1 -name TXDATA -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/TXFR2 -name TXCMD_TXDATA -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/TXFR2 -name TXDATA -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/TXFR3 -name TXCMD_TXDATA -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/TXFR3 -name TXDATA -bitoffset 0  -width 16 
 
imodeladdfield -mmregister $addBlock/RXFR0 -name RXDATA -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/RXFR1 -name RXDATA -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/RXFR2 -name RXDATA -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/RXFR3 -name RXDATA -bitoffset 0  -width 32
