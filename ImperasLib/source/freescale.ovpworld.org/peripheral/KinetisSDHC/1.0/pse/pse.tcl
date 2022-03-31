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
set name    KinetisSDHC
set version 1.0
set desc "Model of the SDHC peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x100 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
DSADDR          0x00 rw - - - - 0x00000000 0xfffffffc "DMA System Address Register, offset: 0x0 "   
BLKATTR         0x04 rw - - - - 0x00000000 0xffff1fff "Block Attributes Register, offset: 0x4 " 
CMDARG          0x08 rw - - - - 0x00000000 0xffffffff "Command Argument Register, offset: 0x8 " 
XFERTYP         0x0c rw - - - - 0x00000000 0x3ffb0037 "Transfer Type Register, offset: 0xC "    
CMDRSP0         0x10 r  - - - - 0x00000000 -          "Command Response 0, offset: 0x10, array step: 0x4 "  
CMDRSP1         0x14 r  - - - - 0x00000000 -          "Command Response 1, offset: 0x10, array step: 0x4 "  
CMDRSP2         0x18 r  - - - - 0x00000000 -          "Command Response 2, offset: 0x10, array step: 0x4 "  
CMDRSP3         0x1c r  - - - - 0x00000000 -          "Command Response 3, offset: 0x10, array step: 0x4 "  
DATPORT         0x20 rw - - - - 0x00000000 0xffffffff "Buffer Data Port Register, offset: 0x20 "    
PRSSTAT         0x24 r  - - - - 0x00000000 -          "Present State Register, offset: 0x24 "   
PROCTL          0x28 rw - - - - 0x00000020 0x070f03ff "Protocol Control Register, offset: 0x28 "    
SYSCTL          0x2c rw - - - - 0x00008008 0x0f0fffff "System Control Register, offset: 0x2C "  
IRQSTAT         0x30 rw - - - - 0x00000000 0x113f01ff "Interrupt Status Register, offset: 0x30 "    
IRQSTATEN       0x34 rw - - - - 0x117f013f 0x113f01ff "Interrupt Status Enable Register, offset: 0x34 " 
IRQSIGEN        0x38 rw - - - - 0x00000000 0x113f01ff "Interrupt Signal Enable Register, offset: 0x38 " 
AC12ERR         0x3c r  - - - - 0x00000000 -          "Auto CMD12 Error Status Register, offset: 0x3C " 
HTCAPBLT        0x40 r  - - - - 0x07f30000 -          "Host Controller Capabilities, offset: 0x40 " 
WML             0x44 rw - - - - 0x00100010 0x00ff00ff "Watermark Level Register, offset: 0x44 " 
FEVT            0x50  w - - - - 0x00000000 0x917f009f "Force Event Register, offset: 0x50 " 
ADMAES          0x54 r  - - - - 0x00000000 -          "ADMA Error Status Register, offset: 0x54 "   
ADSADDR         0x58 rw - - - - 0x00000000 0xfffffffc "ADMA System Address Register, offset: 0x58 " 
VENDOR          0xc0 rw - - - - 0x00000001 0x00000003 "Vendor Specific Register, offset: 0xC0 " 
MMCBOOT         0xc4 rw - - - - 0x00000000 0x000000ff "MMC Boot Register, offset: 0xC4 "    
HOSTVER         0xfc r  - - - - 0x00001201 -          "Host Controller Version, offset: 0xFC "
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

    
 
imodeladdfield -mmregister $addBlock/DSADDR -name DSADDR -bitoffset 2  -width 30    
 
imodeladdfield -mmregister $addBlock/BLKATTR -name BLKCNT -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/BLKATTR -name BLKSIZE -bitoffset 0  -width 13  
 
imodeladdfield -mmregister $addBlock/CMDARG -name CMDARG -bitoffset 0  -width 32    
 
imodeladdfield -mmregister $addBlock/XFERTYP -name AC12EN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name BCEN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name CCCEN -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name CICEN -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name CMDINX -bitoffset 24  -width 6
imodeladdfield -mmregister $addBlock/XFERTYP -name CMDTYP -bitoffset 22  -width 2
imodeladdfield -mmregister $addBlock/XFERTYP -name DMAEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name DPSEL -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name DTDSEL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name MSBSEL -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/XFERTYP -name RSPTYP -bitoffset 16  -width 2   
 
imodeladdfield -mmregister $addBlock/CMDRSP0 -name CMDRSP0 -bitoffset 0  -width 32
 
imodeladdfield -mmregister $addBlock/CMDRSP1 -name CMDRSP1 -bitoffset 0  -width 32
 
imodeladdfield -mmregister $addBlock/CMDRSP2 -name CMDRSP2 -bitoffset 0  -width 32
 
imodeladdfield -mmregister $addBlock/CMDRSP3 -name CMDRSP3 -bitoffset 0  -width 32
 
imodeladdfield -mmregister $addBlock/DATPORT -name DATCONT -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/PRSSTAT -name BREN -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name BWEN -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name CDIHB -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name CIHB -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name CINS -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name CLSL -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name DLA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name DLSL -bitoffset 24  -width 8
imodeladdfield -mmregister $addBlock/PRSSTAT -name HCKOFF -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name IPGOFF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name PEROFF -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name RTA -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name SDOFF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name SDSTB -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PRSSTAT -name WTA -bitoffset 8  -width 1   
 
imodeladdfield -mmregister $addBlock/PROCTL -name CDSS -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name CDTL -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name CREQ -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name D3CD -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name DMAS -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/PROCTL -name DTW -bitoffset 1  -width 2
imodeladdfield -mmregister $addBlock/PROCTL -name EMODE -bitoffset 4  -width 2
imodeladdfield -mmregister $addBlock/PROCTL -name IABG -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name LCTL -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name RWCTL -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name SABGREQ -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name WECINS -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name WECINT -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/PROCTL -name WECRM -bitoffset 26  -width 1 
 
imodeladdfield -mmregister $addBlock/SYSCTL -name DTOCV -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/SYSCTL -name DVS -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/SYSCTL -name HCKEN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name INITA -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name IPGEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name PEREN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name RSTA -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name RSTC -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name RSTD -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name SDCLKEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SYSCTL -name SDCLKFS -bitoffset 8  -width 8    
 
imodeladdfield -mmregister $addBlock/IRQSTAT -name AC12E -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name BGE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name BRR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name BWR -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CCE -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CEBE -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CIE -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CINS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CINT -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CRM -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name CTOE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name DCE -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name DEBE -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name DINT -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name DMAE -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name DTOE -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/IRQSTAT -name TC -bitoffset 1  -width 1    
 
imodeladdfield -mmregister $addBlock/IRQSTATEN -name AC12ESEN -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name BGESEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name BRRSEN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name BWRSEN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CCESEN -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CCSEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CEBESEN -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CIESEN -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CINSEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CINTSEN -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CRMSEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name CTOESEN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name DCESEN -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name DEBESEN -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name DINTSEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name DMAESEN -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name DTOESEN -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/IRQSTATEN -name TCSEN -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/IRQSIGEN -name AC12EIEN -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name BGEIEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name BRRIEN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name BWRIEN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CCEIEN -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CCIEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CEBEIEN -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CIEIEN -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CINSIEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CINTIEN -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CRMIEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name CTOEIEN -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name DCEIEN -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name DEBEIEN -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name DINTIEN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name DMAEIEN -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name DTOEIEN -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/IRQSIGEN -name TCIEN -bitoffset 1  -width 1    
 
imodeladdfield -mmregister $addBlock/AC12ERR -name AC12CE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/AC12ERR -name AC12EBE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/AC12ERR -name AC12IE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/AC12ERR -name AC12NE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/AC12ERR -name AC12TOE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/AC12ERR -name CNIBAC12E -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/HTCAPBLT -name ADMAS -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/HTCAPBLT -name DMAS -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/HTCAPBLT -name HSS -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/HTCAPBLT -name MBL -bitoffset 16  -width 3
imodeladdfield -mmregister $addBlock/HTCAPBLT -name SRS -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/HTCAPBLT -name VS18 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/HTCAPBLT -name VS30 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/HTCAPBLT -name VS33 -bitoffset 24  -width 1    
 
imodeladdfield -mmregister $addBlock/WML -name RDWML -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/WML -name WRWML -bitoffset 16  -width 8    
# 8-31-2014 PRE: WRBRSTLEN not in documentation
imodeladdfield -mmregister $addBlock/WML -name WRBRSTLEN -bitoffset 24  -width 5
 
imodeladdfield -mmregister $addBlock/FEVT -name AC12CE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name AC12E -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name AC12EBE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name AC12IE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name AC12NE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name AC12TOE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name CCE -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name CEBE -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name CIE -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name CINT -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name CNIBAC12E -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name CTOE -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name DCE -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name DEBE -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name DMAE -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/FEVT -name DTOE -bitoffset 20  -width 1    
 
imodeladdfield -mmregister $addBlock/ADMAES -name ADMADCE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ADMAES -name ADMAES -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/ADMAES -name ADMALME -bitoffset 2  -width 1    
 
imodeladdfield -mmregister $addBlock/ADSADDR -name ADSADDR -bitoffset 2  -width 30  
 
imodeladdfield -mmregister $addBlock/VENDOR -name EXBLKNU -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/VENDOR -name EXTDMAEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/VENDOR -name INTSTVAL -bitoffset 16  -width 8  
 
imodeladdfield -mmregister $addBlock/MMCBOOT -name AUTOSABGEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/MMCBOOT -name BOOTACK -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/MMCBOOT -name BOOTBLKCNT -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/MMCBOOT -name BOOTEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/MMCBOOT -name BOOTMODE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/MMCBOOT -name DTOCVACK -bitoffset 0  -width 4  
 
imodeladdfield -mmregister $addBlock/HOSTVER -name SVN -bitoffset 0  -width 8
imodeladdfield -mmregister $addBlock/HOSTVER -name VVN -bitoffset 8  -width 8
