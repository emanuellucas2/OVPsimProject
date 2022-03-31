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
set name    VybridI2C
set version 1.0
set desc "Model of the I2C peripheral used on the Freescale Vybrid platform"
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
imodeladdaddressblock -name ab     -size 0x07 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers {	
IBAD            0x00 rw - - - - 0x00 0xfe "I2C Bus Address Register, offset: 0x0"	
IBFD            0x01 rw - - - - 0x00 0xff "I2C Bus Frequency Divider Register, offset: 0x1"	
IBCR            0x02 rw - - - - 0x80 0xfe "I2C Bus Control Register, offset: 0x2"	
IBSR            0x03 rw - BSRWrite1C - - 0x80 0x12 "I2C Bus Status Register, offset: 0x3"	
IBDR            0x04 rw - - - - 0x00 0xff "I2C Bus Data I/O Register, offset: 0x4"	
IBIC            0x05 rw - - - - 0x00 0x80 "I2C Bus Interrupt Config Register, offset: 0x5"	
IBDBG           0x06 rw - - - - 0x00 0x01 "I2C Bus Debug Register, offset: 0x6"
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

	
 
imodeladdfield -mmregister $addBlock/IBAD -name ADR -bitoffset 1  -width 7	
 
imodeladdfield -mmregister $addBlock/IBFD -name IBC -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/IBCR -name DMAEN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/IBCR -name IBIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IBCR -name MDIS -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/IBCR -name MSSL -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IBCR -name NOACK -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/IBCR -name RSTA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IBCR -name TXRX -bitoffset 4  -width 1	
 
imodeladdfield -mmregister $addBlock/IBSR -name IAAS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IBSR -name IBAL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IBSR -name IBB -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IBSR -name IBIF -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/IBSR -name RXAK -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IBSR -name SRW -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IBSR -name TCF -bitoffset 7  -width 1	
 
imodeladdfield -mmregister $addBlock/IBDR -name DATA -bitoffset 0  -width 8	
 
imodeladdfield -mmregister $addBlock/IBIC -name BIIE -bitoffset 7  -width 1	
 
imodeladdfield -mmregister $addBlock/IBDBG -name IPG_DEBUG_EN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IBDBG -name IPG_DEBUG_HALTED -bitoffset 1  -width 1
