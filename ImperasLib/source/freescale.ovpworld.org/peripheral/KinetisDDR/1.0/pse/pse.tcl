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
set name    KinetisDDR
set version 1.0
set desc "Model of the DDR peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x184 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
CR00            0x00 rw - - - - 0 - "DDR Control Register 0, offset: 0x0 "  
CR01            0x04 rw - - - - 0 - "DDR Control Register 1, offset: 0x4 "  
CR02            0x08 rw - - - - 0 - "DDR Control Register 2, offset: 0x8 "  
CR03            0x0c rw - - - - 0 - "DDR Control Register 3, offset: 0xC "  
CR04            0x10 rw - - - - 0 - "DDR Control Register 4, offset: 0x10 " 
CR05            0x14 rw - - - - 0 - "DDR Control Register 5, offset: 0x14 " 
CR06            0x18 rw - - - - 0 - "DDR Control Register 6, offset: 0x18 " 
CR07            0x1c rw - - - - 0 - "DDR Control Register 7, offset: 0x1C " 
CR08            0x20 rw - - - - 0 - "DDR Control Register 8, offset: 0x20 " 
CR09            0x24 rw - - - - 0 - "DDR Control Register 9, offset: 0x24 " 
CR10            0x28 rw - - - - 0 - "DDR Control Register 10, offset: 0x28 "    
CR11            0x2c rw - - - - 0 - "DDR Control Register 11, offset: 0x2C "    
CR12            0x30 rw - - - - 0 - "DDR Control Register 12, offset: 0x30 "    
CR13            0x34 rw - - - - 0 - "DDR Control Register 13, offset: 0x34 "    
CR14            0x38 rw - - - - 0 - "DDR Control Register 14, offset: 0x38 "    
CR15            0x3c rw - - - - 0 - "DDR Control Register 15, offset: 0x3C "    
CR16            0x40 rw - - - - 0 - "DDR Control Register 16, offset: 0x40 "    
CR17            0x44 rw - - - - 0 - "DDR Control Register 17, offset: 0x44 "    
CR18            0x48 rw - - - - 0 - "DDR Control Register 18, offset: 0x48 "    
CR19            0x4c rw - - - - 0 - "DDR Control Register 19, offset: 0x4C "    
CR20            0x50 rw - - - - 0 - "DDR Control Register 20, offset: 0x50 "    
CR21            0x54 rw - - - - 0 - "DDR Control Register 21, offset: 0x54 "    
CR22            0x58 rw - - - - 0 - "DDR Control Register 22, offset: 0x58 "    
CR23            0x5c rw - - - - 0 - "DDR Control Register 23, offset: 0x5C "    
CR24            0x60 rw - - - - 0 - "DDR Control Register 24, offset: 0x60 "    
CR25            0x64 rw - - - - 0 - "DDR Control Register 25, offset: 0x64 "    
CR26            0x68 rw - - - - 0 - "DDR Control Register 26, offset: 0x68 "    
CR27            0x6c rw - - - - 0 - "DDR Control Register 27, offset: 0x6C "    
CR28            0x70 rw - - - - 0 - "DDR Control Register 28, offset: 0x70 "    
CR29            0x74 rw - - - - 0 - "DDR Control Register 29, offset: 0x74 "    
CR30            0x78 rw - - - - 0 - "DDR Control Register 30, offset: 0x78 "    
CR31            0x7c rw - - - - 0 - "DDR Control Register 31, offset: 0x7C "    
CR32            0x80 rw - - - - 0 - "DDR Control Register 32, offset: 0x80 "    
CR33            0x84 rw - - - - 0 - "DDR Control Register 33, offset: 0x84 "    
CR34            0x88 rw - - - - 0 - "DDR Control Register 34, offset: 0x88 "    
CR35            0x8c rw - - - - 0 - "DDR Control Register 35, offset: 0x8C "    
CR36            0x90 rw - - - - 0 - "DDR Control Register 36, offset: 0x90 "    
CR37            0x94 rw - - - - 0 - "DDR Control Register 37, offset: 0x94 "    
CR38            0x98 rw - - - - 0 - "DDR Control Register 38, offset: 0x98 "    
CR39            0x9c rw - - - - 0 - "DDR Control Register 39, offset: 0x9C "    
CR40            0xa0 rw - - - - 0 - "DDR Control Register 40, offset: 0xA0 "    
CR41            0xa4 rw - - - - 0 - "DDR Control Register 41, offset: 0xA4 "    
CR42            0xa8 rw - - - - 0 - "DDR Control Register 42, offset: 0xA8 "    
CR43            0xac rw - - - - 0 - "DDR Control Register 43, offset: 0xAC "    
CR44            0xb0 rw - - - - 0 - "DDR Control Register 44, offset: 0xB0 "    
CR45            0xb4 rw - - - - 0 - "DDR Control Register 45, offset: 0xB4 "    
CR46            0xb8 rw - - - - 0 - "DDR Control Register 46, offset: 0xB8 "    
CR47            0xbc rw - - - - 0 - "DDR Control Register 47, offset: 0xBC "    
CR48            0xc0 rw - - - - 0 - "DDR Control Register 48, offset: 0xC0 "    
CR49            0xc4 rw - - - - 0 - "DDR Control Register 49, offset: 0xC4 "    
CR50            0xc8 rw - - - - 0 - "DDR Control Register 50, offset: 0xC8 "    
CR51            0xcc rw - - - - 0 - "DDR Control Register 51, offset: 0xCC "    
CR52            0xd0 rw - - - - 0 - "DDR Control Register 52, offset: 0xD0 "    
CR53            0xd4 rw - - - - 0 - "DDR Control Register 53, offset: 0xD4 "    
CR54            0xd8 rw - - - - 0 - "DDR Control Register 54, offset: 0xD8 "    
CR55            0xdc rw - - - - 0 - "DDR Control Register 55, offset: 0xDC "    
CR56            0xe0 rw - - - - 0 - "DDR Control Register 56, offset: 0xE0 "    
CR57            0xe4 rw - - - - 0 - "DDR Control Register 57, offset: 0xE4 "    
CR58            0xe8 rw - - - - 0 - "DDR Control Register 58, offset: 0xE8 "    
CR59            0xec rw - - - - 0 - "DDR Control Register 59, offset: 0xEC "    
CR60            0xf0 rw - - - - 0 - "DDR Control Register 60, offset: 0xF0 "    
CR61            0xf4 rw - - - - 0 - "DDR Control Register 61, offset: 0xF4 "    
CR62            0xf8 rw - - - - 0 - "DDR Control Register 62, offset: 0xF8 "    
CR63            0xfc rw - - - - 0 - "DDR Control Register 63, offset: 0xFC "    
RCR             0x180 rw - - - - 0 - "RCR Control Register, offset: 0x180 "
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

    
 
imodeladdfield -mmregister $addBlock/CR00 -name DDRCLS -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR00 -name START -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR00 -name VERSION -bitoffset 16  -width 16    
 
imodeladdfield -mmregister $addBlock/CR01 -name CSMAX -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CR01 -name MAXCOL -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR01 -name MAXROW -bitoffset 0  -width 5   
 
imodeladdfield -mmregister $addBlock/CR02 -name INITAREF -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/CR02 -name TINIT -bitoffset 0  -width 24   
 
imodeladdfield -mmregister $addBlock/CR03 -name LATGATE -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR03 -name LATLIN -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR03 -name TCCD -bitoffset 24  -width 5
imodeladdfield -mmregister $addBlock/CR03 -name WRLAT -bitoffset 16  -width 4   
 
imodeladdfield -mmregister $addBlock/CR04 -name TBINT -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/CR04 -name TRASMIN -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/CR04 -name TRC -bitoffset 16  -width 6
imodeladdfield -mmregister $addBlock/CR04 -name TRRD -bitoffset 8  -width 3 
 
imodeladdfield -mmregister $addBlock/CR05 -name TMRD -bitoffset 24  -width 5
imodeladdfield -mmregister $addBlock/CR05 -name TRP -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR05 -name TRTP -bitoffset 16  -width 3
imodeladdfield -mmregister $addBlock/CR05 -name TWTR -bitoffset 0  -width 4 
 
imodeladdfield -mmregister $addBlock/CR06 -name INTWBR -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CR06 -name TMOD -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CR06 -name TRASMAX -bitoffset 8  -width 16 
 
imodeladdfield -mmregister $addBlock/CR07 -name AP -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR07 -name CCAPEN -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CR07 -name CLKPW -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/CR07 -name TCKESR -bitoffset 8  -width 5   
 
imodeladdfield -mmregister $addBlock/CR08 -name TDAL -bitoffset 24  -width 5
imodeladdfield -mmregister $addBlock/CR08 -name TRAS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR08 -name TRASDI -bitoffset 8  -width 8
imodeladdfield -mmregister $addBlock/CR08 -name TWR -bitoffset 16  -width 5 
 
imodeladdfield -mmregister $addBlock/CR09 -name BSTLEN -bitoffset 24  -width 3
imodeladdfield -mmregister $addBlock/CR09 -name NOCMD -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR09 -name TDLL -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/CR10 -name TCPD -bitoffset 8  -width 16
imodeladdfield -mmregister $addBlock/CR10 -name TFAW -bitoffset 0  -width 6
imodeladdfield -mmregister $addBlock/CR10 -name TRPAB -bitoffset 24  -width 4   
 
imodeladdfield -mmregister $addBlock/CR11 -name AREF -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CR11 -name AREFMODE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR11 -name REGDIMM -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR11 -name TREFEN -bitoffset 24  -width 1  
 
imodeladdfield -mmregister $addBlock/CR12 -name TREF -bitoffset 16  -width 14
imodeladdfield -mmregister $addBlock/CR12 -name TRFC -bitoffset 0  -width 10    
 
imodeladdfield -mmregister $addBlock/CR13 -name PD -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR13 -name TREFINT -bitoffset 0  -width 14 
 
imodeladdfield -mmregister $addBlock/CR14 -name TPDEX -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR14 -name TXSR -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR15 -name PUREF -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CR15 -name SREF -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR15 -name TXSNR -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/CR16 -name CLKDLY -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/CR16 -name LPCTRL -bitoffset 16  -width 5
imodeladdfield -mmregister $addBlock/CR16 -name QKREF -bitoffset 0  -width 1    
 
imodeladdfield -mmregister $addBlock/CR17 -name LPPDCNT -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR17 -name LPRFCNT -bitoffset 16  -width 16    
 
imodeladdfield -mmregister $addBlock/CR18 -name LPAUTO -bitoffset 16  -width 5
imodeladdfield -mmregister $addBlock/CR18 -name LPEXTCNT -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/CR19 -name LPINTCNT -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR19 -name LPRFHOLD -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR20 -name CKSRE -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR20 -name CKSRX -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CR20 -name LPRE -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CR20 -name WRMD -bitoffset 24  -width 1    
 
imodeladdfield -mmregister $addBlock/CR21 -name MR0DAT0 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR21 -name MR1DAT0 -bitoffset 16  -width 16    
 
imodeladdfield -mmregister $addBlock/CR22 -name MR2DATA0 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR22 -name MR3DAT0 -bitoffset 16  -width 16    
 
imodeladdfield -mmregister $addBlock/CR23 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR23 -name NOT_USED -bitoffset 16  -width 16   
    
 
imodeladdfield -mmregister $addBlock/CR25 -name ADDPINS -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/CR25 -name APREBIT -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/CR25 -name BNK8 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR25 -name COLSIZ -bitoffset 16  -width 3  
 
imodeladdfield -mmregister $addBlock/CR26 -name ADDCOL -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR26 -name AGECNT -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/CR26 -name BNKSPT -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CR26 -name CMDAGE -bitoffset 8  -width 8   
 
imodeladdfield -mmregister $addBlock/CR27 -name PLEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR27 -name PRIEN -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CR27 -name RWEN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR27 -name SWPEN -bitoffset 24  -width 1   
 
imodeladdfield -mmregister $addBlock/CR28 -name BIGEND -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR28 -name CMDLATR -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CR28 -name CSMAP -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR28 -name REDUC -bitoffset 8  -width 1    
 
imodeladdfield -mmregister $addBlock/CR29 -name FSTWR -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CR29 -name QFULL -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CR29 -name RESYNC -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/CR29 -name WRLATR -bitoffset 0  -width 1   
 
imodeladdfield -mmregister $addBlock/CR30 -name INTACK -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/CR30 -name INTSTAT -bitoffset 8  -width 9
imodeladdfield -mmregister $addBlock/CR30 -name RSYNCRF -bitoffset 0  -width 1  
 
imodeladdfield -mmregister $addBlock/CR31 -name INTMASK -bitoffset 0  -width 9  
 
imodeladdfield -mmregister $addBlock/CR32 -name OORAD -bitoffset 0  -width 32   
 
imodeladdfield -mmregister $addBlock/CR33 -name OORID -bitoffset 24  -width 2
imodeladdfield -mmregister $addBlock/CR33 -name OORLEN -bitoffset 0  -width 10
imodeladdfield -mmregister $addBlock/CR33 -name OORTYP -bitoffset 16  -width 6  
 
imodeladdfield -mmregister $addBlock/CR34 -name ODTRDC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR34 -name ODTWRCS -bitoffset 8  -width 1  
 
imodeladdfield -mmregister $addBlock/CR35 -name R2WSMCS -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR35 -name W2RSMCS -bitoffset 8  -width 4  
 
imodeladdfield -mmregister $addBlock/CR36 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR36 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR37 -name R2RSAME -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/CR37 -name R2WSAME -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/CR37 -name W2RSAME -bitoffset 16  -width 3
imodeladdfield -mmregister $addBlock/CR37 -name W2WSAME -bitoffset 24  -width 3 
 
imodeladdfield -mmregister $addBlock/CR38 -name PDNCS -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/CR38 -name PUPCS -bitoffset 8  -width 5
imodeladdfield -mmregister $addBlock/CR38 -name PWRCNT -bitoffset 16  -width 11 
 
imodeladdfield -mmregister $addBlock/CR39 -name P0RDCNT -bitoffset 0  -width 11
imodeladdfield -mmregister $addBlock/CR39 -name RP0 -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CR39 -name WP0 -bitoffset 24  -width 2 
 
imodeladdfield -mmregister $addBlock/CR40 -name P0TYP -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CR40 -name P1WRCNT -bitoffset 8  -width 11 
 
imodeladdfield -mmregister $addBlock/CR41 -name P1RDCNT -bitoffset 0  -width 11
imodeladdfield -mmregister $addBlock/CR41 -name RP1 -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CR41 -name WP1 -bitoffset 24  -width 2 
 
imodeladdfield -mmregister $addBlock/CR42 -name P1TYP -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CR42 -name P2WRCNT -bitoffset 8  -width 11 
 
imodeladdfield -mmregister $addBlock/CR43 -name P2RDCNT -bitoffset 0  -width 11
imodeladdfield -mmregister $addBlock/CR43 -name RP2 -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CR43 -name WP2 -bitoffset 24  -width 2 
 
imodeladdfield -mmregister $addBlock/CR44 -name P2TYP -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CR44 -name WRRERR -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/CR44 -name WRRLAT -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/CR44 -name WRRSHARE -bitoffset 16  -width 1    
 
imodeladdfield -mmregister $addBlock/CR45 -name P0PRI0 -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR45 -name P0PRI1 -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR45 -name P0PRI2 -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CR45 -name P0PRI3 -bitoffset 24  -width 4  
 
imodeladdfield -mmregister $addBlock/CR46 -name P0ORD -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/CR46 -name P0PRIRLX -bitoffset 8  -width 10
imodeladdfield -mmregister $addBlock/CR46 -name P1PRI0 -bitoffset 24  -width 4  
 
imodeladdfield -mmregister $addBlock/CR47 -name P1ORD -bitoffset 24  -width 2
imodeladdfield -mmregister $addBlock/CR47 -name P1PRI1 -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR47 -name P1PRI2 -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR47 -name P1PRI3 -bitoffset 16  -width 4  
 
imodeladdfield -mmregister $addBlock/CR48 -name P1PRIRLX -bitoffset 0  -width 10
imodeladdfield -mmregister $addBlock/CR48 -name P2PRI0 -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CR48 -name P2PRI1 -bitoffset 24  -width 4  
 
imodeladdfield -mmregister $addBlock/CR49 -name P2ORD -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/CR49 -name P2PRI2 -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR49 -name P2PRI3 -bitoffset 8  -width 4   
 
imodeladdfield -mmregister $addBlock/CR50 -name CLKSTATUS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/CR50 -name P2PRIRLX -bitoffset 0  -width 10    
 
imodeladdfield -mmregister $addBlock/CR51 -name DLLRADLY -bitoffset 16  -width 8
imodeladdfield -mmregister $addBlock/CR51 -name DLLRSTDLY -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR51 -name PHYWRLAT -bitoffset 24  -width 4    
 
imodeladdfield -mmregister $addBlock/CR52 -name PHYRDLAT -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR52 -name PYWRLTBS -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR52 -name RDDATAEN -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CR52 -name RDDTENBAS -bitoffset 24  -width 4   
 
imodeladdfield -mmregister $addBlock/CR53 -name CLKDISCS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CR53 -name CRTLUPDMN -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/CR53 -name CTRLUPDMX -bitoffset 16  -width 14  
 
imodeladdfield -mmregister $addBlock/CR54 -name PHYUPDTY0 -bitoffset 0  -width 14
imodeladdfield -mmregister $addBlock/CR54 -name PHYUPDTY1 -bitoffset 16  -width 14  
 
imodeladdfield -mmregister $addBlock/CR55 -name PHYUPDTY2 -bitoffset 0  -width 14
imodeladdfield -mmregister $addBlock/CR55 -name PHYUPDTY3 -bitoffset 16  -width 14  
 
imodeladdfield -mmregister $addBlock/CR56 -name PHYUPDRESP -bitoffset 0  -width 14
imodeladdfield -mmregister $addBlock/CR56 -name RDLATADJ -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CR56 -name WRLATADJ -bitoffset 24  -width 4    
 
imodeladdfield -mmregister $addBlock/CR57 -name CLKDISDLY -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/CR57 -name CLKENDLY -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/CR57 -name CMDDLY -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/CR57 -name ODTALTEN -bitoffset 24  -width 1    
 
imodeladdfield -mmregister $addBlock/CR58 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR58 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR59 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR59 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR60 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR60 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR61 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR61 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR62 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR62 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/CR63 -name NOT_USED2 -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/CR63 -name NOT_USED -bitoffset 16  -width 16   
 
imodeladdfield -mmregister $addBlock/RCR -name RST -bitoffset 30  -width 1
