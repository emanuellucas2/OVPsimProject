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
set name    KinetisSIM
set version 1.0
set desc "Model of the SIM peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x1070 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
SOPT1           0x00 rw - - - -   0x10009000 0xe0080000 "System Options Register 1, offset: 0x0 "   
SOPT1CFG        0x04 rw - - - -   0x00000000 0x07000000 "SOPT1 Configuration Register, offset: 0x4 "    
SOPT2           0x1004 rw - - - - 0x44001004 0xf0f79bfc "System Options Register 2, offset: 0x1004 "    
SOPT4           0x100c rw - - - - 0x00000000 0xff3c111f "System Options Register 4, offset: 0x100C "    
SOPT5           0x1010 rw - - - - 0x00000000 0x000000ff "System Options Register 5, offset: 0x1010 "    
SOPT6           0x1014 rw - - - - 0x00000000 0x000fffff "System Options Register 6, offset: 0x1014 "    
SOPT7           0x1018 rw - - - - 0x00000000 0x9f9f9f9f "System Options Register 7, offset: 0x1018 "    
SDID            0x1024 r  - - - - 0x00000180 -           "System Device Identification Register, offset: 0x1024 "   
SCGC1           0x1028 rw - - - - 0x00000000 0x00000c20 "System Clock Gating Control Register 1, offset: 0x1028 "   
SCGC2           0x102c rw - - - - 0x00000000 0x00003001 "System Clock Gating Control Register 2, offset: 0x102C "   
SCGC3           0x1030 rw - - - - 0x00000000 0x1b029111 "System Clock Gating Control Register 3, offset: 0x1030 "   
SCGC4           0x1034 rw - - - - 0xf0100030 0x101c3cc6 "System Clock Gating Control Register 4, offset: 0x1034 "   
SCGC5           0x1038 rw - - - - 0x00040180 0x00007e23 "System Clock Gating Control Register 5, offset: 0x1038 "   
SCGC6           0x103c rw - - - - 0x40000001 0x3bf4b016 "System Clock Gating Control Register 6, offset: 0x103C "   
SCGC7           0x1040 rw - - - - 0x00000007 0x00000007 "System Clock Gating Control Register 7, offset: 0x1040 "   
CLKDIV1         0x1044 rw - - - - 0x00000000 0xffff0000 "System Clock Divider Register 1, offset: 0x1044 "  
CLKDIV2         0x1048 rw - - - - 0x00000000 0x00000f0f "System Clock Divider Register 2, offset: 0x1048 "  
FCFG1           0x104c rw - - - - 0x00000000 0x00000001 "Flash Configuration Register 1, offset: 0x104C "   
FCFG2           0x1050 r  - - - - 0x00000000 -          "Flash Configuration Register 2, offset: 0x1050 "   
UIDH            0x1054 r  - - - - -          -          "Unique Identification Register High, offset: 0x1054 "  
UIDMH           0x1058 r  - - - - -          -          "Unique Identification Register Mid-High, offset: 0x1058 "  
UIDML           0x105c r  - - - - -          -          "Unique Identification Register Mid Low, offset: 0x105C "   
UIDL            0x1060 r  - - - - -          -          "Unique Identification Register Low, offset: 0x1060 "   
CLKDIV4         0x1068 rw - - - - 0x00000002 0xff00000f "System Clock Divider Register 4, offset: 0x1068 "  
MCR             0x106c rw - - - - 0x00000000 0xe0000000 "Misc Control Register, offset: 0x106C "
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

    
 
imodeladdfield -mmregister $addBlock/SOPT1 -name OSC32KSEL -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/SOPT1 -name USBREGEN -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/SOPT1 -name USBSSTBY -bitoffset 30  -width 1
# 08-31-2014 PRE: Documentation had USBVSTBY, .h was USBSTBY
imodeladdfield -mmregister $addBlock/SOPT1 -name USBVSTBY -bitoffset 29  -width 1   
# 08-31-2014 PRE: .h missing ramsize.
imodeladdfield -mmregister $addBlock/SOPT1 -name RAMSIZE -bitoffset 12  -width 4    
 
imodeladdfield -mmregister $addBlock/SOPT1CFG -name URWE -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/SOPT1CFG -name USSWE -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/SOPT1CFG -name UVSWE -bitoffset 25  -width 1   
 
imodeladdfield -mmregister $addBlock/SOPT2 -name CLKOUTSEL -bitoffset 5  -width 3
imodeladdfield -mmregister $addBlock/SOPT2 -name CMTUARTPAD -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/SOPT2 -name ESDHCSRC -bitoffset 28  -width 2
imodeladdfield -mmregister $addBlock/SOPT2 -name FBSL -bitoffset 8  -width 2
imodeladdfield -mmregister $addBlock/SOPT2 -name NFC_CLKSEL -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/SOPT2 -name NFCSRC -bitoffset 30  -width 2
imodeladdfield -mmregister $addBlock/SOPT2 -name PLLFLLSEL -bitoffset 16  -width 2
imodeladdfield -mmregister $addBlock/SOPT2 -name RTCCLKOUTSEL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SOPT2 -name TIMESRC -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/SOPT2 -name TRACECLKSEL -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SOPT2 -name USBF_CLKSEL -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/SOPT2 -name USBFSRC -bitoffset 22  -width 2
# 08-31-2014 PRE: USBH_CLKSEL not in documentation
imodeladdfield -mmregister $addBlock/SOPT2 -name USBH_CLKSEL -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SOPT2 -name USBHSRC -bitoffset 2  -width 2 
 
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0CLKSEL -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0FLT0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0FLT1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0FLT2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0FLT3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0TRG0SRC -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM0TRG1SRC -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM1CH0SRC -bitoffset 18  -width 2
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM1CLKSEL -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM1FLT0 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM2CH0SRC -bitoffset 20  -width 2
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM2CLKSEL -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM2FLT0 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM3CLKSEL -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM3FLT0 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM3TRG0SRC -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/SOPT4 -name FTM3TRG1SRC -bitoffset 31  -width 1    
 
imodeladdfield -mmregister $addBlock/SOPT5 -name UART0RXSRC -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/SOPT5 -name UART0TXSRC -bitoffset 0  -width 2
imodeladdfield -mmregister $addBlock/SOPT5 -name UART1RXSRC -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/SOPT5 -name UART1TXSRC -bitoffset 4  -width 2  
 
imodeladdfield -mmregister $addBlock/SOPT6 -name MCC -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/SOPT6 -name PCR -bitoffset 16  -width 4
# 08-31-2014 PRE: RSTFLTEN, RSTFLTSEL not in documentation.
imodeladdfield -mmregister $addBlock/SOPT6 -name RSTFLTEN -bitoffset 29  -width 3
imodeladdfield -mmregister $addBlock/SOPT6 -name RSTFLTSEL -bitoffset 24  -width 5  
 
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC0ALTTRGEN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC0PRETRGSEL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC0TRGSEL -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC1ALTTRGEN -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC1PRETRGSEL -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC1TRGSEL -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC2ALTTRGEN -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC2PRETRGSEL -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC2TRGSEL -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC3ALTTRGEN -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC3PRETRGSEL -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/SOPT7 -name ADC3TRGSEL -bitoffset 24  -width 4 
 
# 08-31-2014 PRE: PINID and FAMID differ in name from .h file
imodeladdfield -mmregister $addBlock/SDID -name PINID -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/SDID -name FAMID -bitoffset 4  -width 3
imodeladdfield -mmregister $addBlock/SDID -name REVID -bitoffset 12  -width 4   
 
# 08-31-2014 PRE: Missing OSC1 in .h file
imodeladdfield -mmregister $addBlock/SCGC1 -name UART4 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SCGC1 -name UART5 -bitoffset 11  -width 1  
imodeladdfield -mmregister $addBlock/SCGC1 -name OSC1 -bitoffset 5  -width 1    
 
imodeladdfield -mmregister $addBlock/SCGC2 -name DAC0 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SCGC2 -name DAC1 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/SCGC2 -name ENET -bitoffset 0  -width 1    
 
imodeladdfield -mmregister $addBlock/SCGC3 -name ADC1 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name ADC3 -bitoffset 28  -width 1
# 08-31-2014 PRE: DDR not in documentation
imodeladdfield -mmregister $addBlock/SCGC3 -name DDR -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name DSPI2 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name ESDHC -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name FLEXCAN1 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name FTM2 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name FTM3 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name NFC -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name RNGA -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SCGC3 -name SAI1 -bitoffset 15  -width 1   

# 08-31-2014 PRE: CMP named ANL in .h file 
imodeladdfield -mmregister $addBlock/SCGC4 -name CMP -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name CMT -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name EWM -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name IIC1 -bitoffset 7  -width 1
# 08-31-2014 PRE: IIC0 named IIC2 in .h file
imodeladdfield -mmregister $addBlock/SCGC4 -name IIC0 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name LLWU -bitoffset 28  -width 1
# 08-31-2014 PRE: MCG, OSC, PMC, RCM, SMC not in Docmentation
imodeladdfield -mmregister $addBlock/SCGC4 -name MCG -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name OSC -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name PMC -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name RCM -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name SMC -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name UART0 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name UART1 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name UART2 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name UART3 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name USBFS -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/SCGC4 -name VREF -bitoffset 20  -width 1   
 
imodeladdfield -mmregister $addBlock/SCGC5 -name LPTIMER -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name PORTA -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name PORTB -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name PORTC -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name PORTD -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name PORTE -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name PORTF -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name REGFILE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name TSI -bitoffset 5  -width 1
# 08-31-2014 PRE: Following 6 registers not in documentation
imodeladdfield -mmregister $addBlock/SCGC5 -name ATX -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name DRYICE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name DRYICESECREG -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name SIM -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name SIMDGO -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SCGC5 -name WDT -bitoffset 18  -width 1    
 
imodeladdfield -mmregister $addBlock/SCGC6 -name ADC0 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name ADC2 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name CRC -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name DMAMUX0 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name DMAMUX1 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name DSPI0 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name DSPI1 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name FLEXCAN0 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name FTM0 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name FTM1 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name PDB -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name PIT -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name RTC -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name SAI0 -bitoffset 15  -width 1
# 08-31-2014 PRE: USBHS called USB20TG in .h file
imodeladdfield -mmregister $addBlock/SCGC6 -name USBHS -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/SCGC6 -name USBDCD -bitoffset 21  -width 1 
# 08-31-2014 PRE: FTF not in documentation
imodeladdfield -mmregister $addBlock/SCGC6 -name FTF -bitoffset 0  -width 1
 
imodeladdfield -mmregister $addBlock/SCGC7 -name FLEXBUS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SCGC7 -name DMA -bitoffset 1  -width 1
# 08-31-2014 PRE: MPU offset 2 in documentation, PFLEXNVM not defined in DOC.
#                 MPU offset 3 in .h, 
#imodeladdfield -mmregister $addBlock/SCGC7 -name PFLEXNVM -bitoffset 2  -width 1   
imodeladdfield -mmregister $addBlock/SCGC7 -name MPU -bitoffset 2  -width 1
 
imodeladdfield -mmregister $addBlock/CLKDIV1 -name OUTDIV1 -bitoffset 28  -width 4
imodeladdfield -mmregister $addBlock/CLKDIV1 -name OUTDIV2 -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/CLKDIV1 -name OUTDIV3 -bitoffset 20  -width 4
imodeladdfield -mmregister $addBlock/CLKDIV1 -name OUTDIV4 -bitoffset 16  -width 4  
 
imodeladdfield -mmregister $addBlock/CLKDIV2 -name USBFSDIV -bitoffset 1  -width 3
imodeladdfield -mmregister $addBlock/CLKDIV2 -name USBFSFRAC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CLKDIV2 -name USBHSDIV -bitoffset 9  -width 3
imodeladdfield -mmregister $addBlock/CLKDIV2 -name USBHSFRAC -bitoffset 8  -width 1 
 
imodeladdfield -mmregister $addBlock/FCFG1 -name DEPART -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/FCFG1 -name EESIZE -bitoffset 16  -width 4
imodeladdfield -mmregister $addBlock/FCFG1 -name PFSIZE -bitoffset 24  -width 4
imodeladdfield -mmregister $addBlock/FCFG1 -name NVMSIZE -bitoffset 28  -width 4
imodeladdfield -mmregister $addBlock/FCFG1 -name FTFDIS -bitoffset 0  -width 1  
# 08-31-2014 PRE: Following is the definition in .h file
#imodeladdfield -mmregister $addBlock/FCFG1 -name DEPART -bitoffset 8  -width 4
#imodeladdfield -mmregister $addBlock/FCFG1 -name EESIZE -bitoffset 16  -width 4
#imodeladdfield -mmregister $addBlock/FCFG1 -name FSIZE -bitoffset 24  -width 8
#imodeladdfield -mmregister $addBlock/FCFG1 -name FTFDIS -bitoffset 0  -width 1 
 
imodeladdfield -mmregister $addBlock/FCFG2 -name MAXADDR01 -bitoffset 24  -width 6
imodeladdfield -mmregister $addBlock/FCFG2 -name MAXADDR23 -bitoffset 16  -width 6
# 08-31-2014 PRE: Following is the definition in .h file
#imodeladdfield -mmregister $addBlock/FCFG2 -name MAXADDR0 -bitoffset 24  -width 6
#imodeladdfield -mmregister $addBlock/FCFG2 -name MAXADDR1 -bitoffset 16  -width 6
#imodeladdfield -mmregister $addBlock/FCFG2 -name PFLSH -bitoffset 23  -width 1
#imodeladdfield -mmregister $addBlock/FCFG2 -name SWAPPFLSH -bitoffset 31  -width 1 
 
imodeladdfield -mmregister $addBlock/UIDH -name UID -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/UIDMH -name UID -bitoffset 0  -width 32    
 
imodeladdfield -mmregister $addBlock/UIDML -name UID -bitoffset 0  -width 32    
 
imodeladdfield -mmregister $addBlock/UIDL -name UID -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/CLKDIV4 -name NFCDIV -bitoffset 27  -width 5
imodeladdfield -mmregister $addBlock/CLKDIV4 -name NFCFRAC -bitoffset 24  -width 3
imodeladdfield -mmregister $addBlock/CLKDIV4 -name TRACEDIV -bitoffset 1  -width 3
imodeladdfield -mmregister $addBlock/CLKDIV4 -name TRACEFRAC -bitoffset 0  -width 1 
 
imodeladdfield -mmregister $addBlock/MCR -name PDBLOOP -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/MCR -name TRACECLKDIS -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/MCR -name ULPICLKOBE -bitoffset 30  -width 1
# 08-31-2014 PRE: Following not defined in documentation
#imodeladdfield -mmregister $addBlock/MCR -name DDRS -bitoffset 1  -width 1
#imodeladdfield -mmregister $addBlock/MCR -name DDRSREN -bitoffset 0  -width 1
#imodeladdfield -mmregister $addBlock/MCR -name RCRRST -bitoffset 9  -width 1
#imodeladdfield -mmregister $addBlock/MCR -name RCRRSTEN -bitoffset 8  -width 1
