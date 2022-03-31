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
set name    KinetisUART
set version 1.0
set desc "Model of the UART peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x35 -port bport1 -width 8

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
BDH             0x00 rw -         writeBDH    -        -    0x00 0xdf "UART Baud Rate Registers:High, offset: 0x0 " 
BDL             0x01 rw -         writeBDL    -        -    0x04 0xff "UART Baud Rate Registers: Low, offset: 0x1 " 
C1              0x02 rw -         -           -        -    0x00 0xff "UART Control Register 1, offset: 0x2 "   
C2              0x03 rw -         writeC2     -        -    0x00 0xff "UART Control Register 2, offset: 0x3 "   
S1              0x04 r  readS1    -           viewS1   -    0xc0 - "UART Status Register 1, offset: 0x4 "   
S2              0x05 rw -         -           -        -    0x00 0xfe "UART Status Register 2, offset: 0x5 "    
C3              0x06 rw -         -           -        -    0x00 0x7f "UART Control Register 3, offset: 0x6 "   
D               0x07 rw readD     writeD      -        -    0x00 0xff "UART Data Register, offset: 0x7 "    
MA1             0x08 rw -         -           -        -    0x00 0xff "UART Match Address Registers 1, offset: 0x8 "    
MA2             0x09 rw -         -           -        -    0x00 0xff "UART Match Address Registers 2, offset: 0x9 "    
C4              0x0a rw -         writeC4     -        -    0x00 0xff "UART Control Register 4, offset: 0xA "   
C5              0x0b rw -         -           -        -    0x00 0xa0 "UART Control Register 5, offset: 0xB "   
ED              0x0c r  -         -           -        -    0x00 - "UART Extended Data Register, offset: 0xC "  
MODEM           0x0d rw -         -           -        -    0x00 0x0f "UART Modem Register, offset: 0xD "   
IR              0x0e rw -         -           -        -    0x00 0x07 "UART Infrared Register, offset: 0xE "    
PFIFO           0x10 rw -         -           -        -    0x00 0x88 "UART FIFO Parameters, offset: 0x10 " 
CFIFO           0x11 rw -         writeCFIFO  -        -    0x00 0xc3 "UART FIFO Control Register, offset: 0x11 "   
SFIFO           0x12 rw -         -           -        -    0xc0 0x03 "UART FIFO Status Register, offset: 0x12 "    
TWFIFO          0x13 rw -         writeTWFIFO -        -    0x00 0xff "UART FIFO Transmit Watermark, offset: 0x13 " 
TCFIFO          0x14 r  -         -           -        -    0x00 - "UART FIFO Transmit Count, offset: 0x14 "    
RWFIFO          0x15 rw -         writeRWFIFO -        -    0x01 0xff "UART FIFO Receive Watermark, offset: 0x15 "  
RCFIFO          0x16 r  -         -           -        -    0x00 - "UART FIFO Receive Count, offset: 0x16 " 
C7816           0x18 rw - - - - 0x00 0x1f "UART 7816 Control Register, offset: 0x18 "   
IE7816          0x19 rw - - - - 0x00 0xf7 "UART 7816 Interrupt Enable Register, offset: 0x19 "  
IS7816          0x1a rw - - - - 0x00 0xf7 "UART 7816 Interrupt Status Register, offset: 0x1A "  
WP7816T0        0x1b rw - - - - 0x0a 0xff "UART 7816 Wait Parameter Register, offset: 0x1B "    
WN7816          0x1c rw - - - - 0x00 0xff "UART 7816 Wait N Register, offset: 0x1C "    
WF7816          0x1d rw - - - - 0x01 0xff "UART 7816 Wait FD Register, offset: 0x1D "   
ET7816          0x1e rw - - - - 0x00 0xff "UART 7816 Error Threshold Register, offset: 0x1E "   
TL7816          0x1f rw - - - - 0x00 0xff "UART 7816 Transmit Length Register, offset: 0x1F "   
C6              0x21 rw - - - - 0x00 0xf0 "UART CEA709.1-B Control Register 6, offset: 0x21 "   
PCTH            0x22 rw - - - - 0x00 0xff "UART CEA709.1-B Packet Cycle Time Counter High, offset: 0x22 "   
PCTL            0x23 rw - - - - 0x00 0xff "UART CEA709.1-B Packet Cycle Time Counter Low, offset: 0x23 "    
B1T             0x24 rw - - - - 0x00 0xff "UART CEA709.1-B Beta1 Timer, offset: 0x24 "  
SDTH            0x25 rw - - - - 0x00 0xff "UART CEA709.1-B Secondary Delay Timer High, offset: 0x25 "   
SDTL            0x26 rw - - - - 0x00 0xff "UART CEA709.1-B Secondary Delay Timer Low, offset: 0x26 "    
PRE             0x27 rw - - - - 0x00 0xff "UART CEA709.1-B Preamble, offset: 0x27 " 
TPL             0x28 rw - - - - 0x00 0xff "UART CEA709.1-B Transmit Packet Length, offset: 0x28 "   
IE              0x29 rw - - - - 0x00 0x7f "UART CEA709.1-B Interrupt Enable Register, offset: 0x29 "    
WB              0x2a rw - - - - 0x00 0xff "UART CEA709.1-B WBASE, offset: 0x2A "    
S3              0x2b rw - - - - 0x00 0xdf "UART CEA709.1-B Status Register, offset: 0x2B "  
S4              0x2c rw - - - - 0x00 0x0f "UART CEA709.1-B Status Register, offset: 0x2C "  
RPL             0x2d r  - - - - 0x00 - "UART CEA709.1-B Received Packet Length, offset: 0x2D "  
RPREL           0x2e r  - - - - 0x00 - "UART CEA709.1-B Received Preamble Length, offset: 0x2E "    
CPW             0x2f rw - - - - 0x00 0xff "UART CEA709.1-B Collision Pulse Width, offset: 0x2F "    
RIDT            0x30 rw - - - - 0x00 0xff "UART CEA709.1-B Receive Indeterminate Time, offset: 0x30 "   
TIDT            0x31 rw - - - - 0x00 0xff "UART CEA709.1-B Transmit Indeterminate Time, offset: 0x31 "
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

    
 
imodeladdfield -mmregister $addBlock/BDH -name LBKDIE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/BDH -name RXEDGIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/BDH -name SBR -bitoffset 0  -width 5   
 
imodeladdfield -mmregister $addBlock/BDL -name SBR -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/C1 -name ILT -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C1 -name LOOPS -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C1 -name M -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C1 -name PE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/C1 -name PT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C1 -name RSRC -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C1 -name UARTSWAI -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C1 -name WAKE -bitoffset 3  -width 1   
 
imodeladdfield -mmregister $addBlock/C2 -name ILIE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C2 -name RE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C2 -name RIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C2 -name RWU -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/C2 -name SBK -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C2 -name TCIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C2 -name TE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C2 -name TIE -bitoffset 7  -width 1    
 
imodeladdfield -mmregister $addBlock/S1 -name FE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S1 -name IDLE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/S1 -name NF -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/S1 -name OR -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/S1 -name PF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S1 -name RDRF -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/S1 -name TC -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/S1 -name TDRE -bitoffset 7  -width 1   
 
imodeladdfield -mmregister $addBlock/S2 -name BRK13 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/S2 -name LBKDE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S2 -name LBKDIF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/S2 -name MSBF -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/S2 -name RAF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S2 -name RWUID -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/S2 -name RXEDGIF -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/S2 -name RXINV -bitoffset 4  -width 1  
 
imodeladdfield -mmregister $addBlock/C3 -name FEIE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/C3 -name NEIE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C3 -name ORIE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C3 -name PEIE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C3 -name R8 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C3 -name T8 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C3 -name TXDIR -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C3 -name TXINV -bitoffset 4  -width 1  
 
imodeladdfield -mmregister $addBlock/D -name RT -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/MA1 -name MA -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/MA2 -name MA -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/C4 -name BRFA -bitoffset 0  -width 5
imodeladdfield -mmregister $addBlock/C4 -name M10 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C4 -name MAEN1 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C4 -name MAEN2 -bitoffset 6  -width 1  
 
imodeladdfield -mmregister $addBlock/C5 -name RDMAS -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C5 -name TDMAS -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/ED -name NOISY -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ED -name PARITYE -bitoffset 6  -width 1    
 
imodeladdfield -mmregister $addBlock/MODEM -name RXRTSE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/MODEM -name TXCTSE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/MODEM -name TXRTSE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/MODEM -name TXRTSPOL -bitoffset 2  -width 1    
 
imodeladdfield -mmregister $addBlock/IR -name IREN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IR -name TNP -bitoffset 0  -width 2    
 
imodeladdfield -mmregister $addBlock/PFIFO -name RXFE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PFIFO -name RXFIFOSIZE -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/PFIFO -name TXFE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PFIFO -name TXFIFOSIZE -bitoffset 4  -width 3  
 
imodeladdfield -mmregister $addBlock/CFIFO -name RXFLUSH -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/CFIFO -name RXUFE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/CFIFO -name TXFLUSH -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/CFIFO -name TXOFE -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/SFIFO -name RXEMPT -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SFIFO -name RXUF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SFIFO -name TXEMPT -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SFIFO -name TXOF -bitoffset 1  -width 1    
 
imodeladdfield -mmregister $addBlock/TWFIFO -name TXWATER -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/TCFIFO -name TXCOUNT -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/RWFIFO -name RXWATER -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/RCFIFO -name RXCOUNT -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/C7816 -name ANACK -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C7816 -name INIT -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C7816 -name ISO_7816E -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C7816 -name ONACK -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C7816 -name TTYPE -bitoffset 1  -width 1   
 
imodeladdfield -mmregister $addBlock/IE7816 -name BWTE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IE7816 -name CWTE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IE7816 -name GTVE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IE7816 -name INITDE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IE7816 -name RXTE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IE7816 -name TXTE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/IE7816 -name WTE -bitoffset 7  -width 1    
 
imodeladdfield -mmregister $addBlock/IS7816 -name BWT -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IS7816 -name CWT -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/IS7816 -name GTV -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IS7816 -name INITD -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IS7816 -name RXT -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IS7816 -name TXT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/IS7816 -name WT -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/WP7816T0 -name WI -bitoffset 0  -width 8   
 
# 08-31-2014 PRE: Following use for WP7816T0 with type 2
#imodeladdfield -mmregister $addBlock/WP7816T0 -name BWI -bitoffset 0  -width 4
#imodeladdfield -mmregister $addBlock/WP7816T0 -name CWI -bitoffset 4  -width 4 
    
 
imodeladdfield -mmregister $addBlock/WN7816 -name GTN -bitoffset 0  -width 8    
 
imodeladdfield -mmregister $addBlock/WF7816 -name GTFD -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/ET7816 -name RXTHRESHOLD -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/ET7816 -name TXTHRESHOLD -bitoffset 4  -width 4    
 
imodeladdfield -mmregister $addBlock/TL7816 -name TLEN -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/C6 -name CE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/C6 -name CP -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C6 -name EN709 -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C6 -name TX709 -bitoffset 6  -width 1  
 
imodeladdfield -mmregister $addBlock/PCTH -name PCTH -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/PCTL -name PCTL -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/B1T -name B1T -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/SDTH -name SDTH -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/SDTL -name SDTL -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/PRE -name PREAMBLE -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/TPL -name TPL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/IE -name ISDIE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/IE -name PCTEIE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/IE -name PRXIE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/IE -name PSIE -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/IE -name PTXIE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/IE -name TXFIE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/IE -name WBEIE -bitoffset 6  -width 1  
 
imodeladdfield -mmregister $addBlock/WB -name WBASE -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/S3 -name ISD -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/S3 -name PCTEF -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/S3 -name PEF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/S3 -name PRXF -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/S3 -name PSF -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S3 -name PTXF -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/S3 -name TXFF -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S3 -name WBEF -bitoffset 6  -width 1   
 
imodeladdfield -mmregister $addBlock/S4 -name CDET -bitoffset 2  -width 2
imodeladdfield -mmregister $addBlock/S4 -name FE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/S4 -name ILCV -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/S4 -name INITF -bitoffset 4  -width 1  
 
imodeladdfield -mmregister $addBlock/RPL -name RPL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/RPREL -name RPREL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/CPW -name CPW -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/RIDT -name RIDT -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/TIDT -name TIDT -bitoffset 0  -width 8



#
# Net Ports
#
imodeladdnetport -name DirectWrite -type output
imodeladdnetport -name DirectRead  -type input  -updatefunction directReadCB
imodeladdnetport -name Interrupt   -type output
imodeladdnetport -name Reset       -type input  -updatefunction resetCB

#
# Formals
#
imodeladdformal   -name directReadWrite -type bool
iadddocumentation -name Description                                                                      \
          -text "Enable the use of the DirectRead and DirectWrite connections"

imodeladdformal   -name fifoSize  -type uns32 -defaultvalue 128 -min 1 -max 128
iadddocumentation -name Description                                                                      \
          -text "Size of fifos (default 128)"
imodeladdformal   -name moduleClkFreq  -type uns32 -defaultvalue 10200000
iadddocumentation -name Description                                                                      \
          -text "Frequency (in hertz) of module clock used in baud rate calculation (default=10.2 MHz)"

# This set of parameters are ALWAYS present on a socket connection using the bhmSerOpenAuto
imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
