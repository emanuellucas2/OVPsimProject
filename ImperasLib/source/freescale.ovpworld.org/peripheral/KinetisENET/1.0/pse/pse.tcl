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
set name    KinetisENET
set version 1.0
set desc "Model of the ENET peripheral used on the Freescale Kinetis platform"
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
imodeladdaddressblock -name ab     -size 0x628 -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
EIR             0x04 rw - - - - 0x00000000 0x7fff8000 "Interrupt Event Register, offset: 0x4 "  
EIMR            0x08 rw - - - - 0x00000000 0x7fff8000 "Interrupt Mask Register, offset: 0x8 "   
RDAR            0x10 rw - - - - 0x00000000 0x01000000 "Receive Descriptor Active Register, offset: 0x10 "   
TDAR            0x14 rw - - - - 0x00000000 0x01000000 "Transmit Descriptor Active Register, offset: 0x14 "  
ECR             0x24 rw - - - - 0xf0000000 0x000001df "Ethernet Control Register, offset: 0x24 "    
MMFR            0x40 rw - - - - 0x00000000 0xffffffff "MII Management Frame Register, offset: 0x40 "    
MSCR            0x44 rw - - - - 0x00000000 0x000007fe "MII Speed Control Register, offset: 0x44 "   
MIBC            0x64 rw - - - - 0xc0000000 0xa0000000 "MIB Control Register, offset: 0x64 " 
RCR             0x84 rw - - - - 0x0fee0001 0x47fff33f "Receive Control Register, offset: 0x84 " 
TCR             0xc4 rw - - - - 0x00000000 0x000003ed "Transmit Control Register, offset: 0xC4 "    
PALR            0xe4 rw - - - - 0x00000000 0xffffffff "Physical Address Lower Register, offset: 0xE4 "  
PAUR            0xe8 rw - - - - 0x00008808 0xffff0000 "Physical Address Upper Register, offset: 0xE8 "  
OPD             0xec rw - - - - 0x00010000 0x0000ffff "Opcode/Pause Duration Register, offset: 0xEC "   
IAUR            0x118 rw - - - - 0x00000000 0xffffffff "Descriptor Individual Upper Address Register, offset: 0x118 "   
IALR            0x11c rw - - - - 0x00000000 0xffffffff "Descriptor Individual Lower Address Register, offset: 0x11C "   
GAUR            0x120 rw - - - - 0x00000000 0xffffffff "Descriptor Group Upper Address Register, offset: 0x120 "    
GALR            0x124 rw - - - - 0x00000000 0xffffffff "Descriptor Group Lower Address Register, offset: 0x124 "    
TFWR            0x144 rw - - - - 0x00000000 0x0000013f "Transmit FIFO Watermark Register, offset: 0x144 "   
RDSR            0x180 rw - - - - 0x00000000 0xfffffff8 "Receive Descriptor Ring Start Register, offset: 0x180 " 
TDSR            0x184 rw - - - - 0x00000000 0xfffffff8 "Transmit Buffer Descriptor Ring Start Register, offset: 0x184 " 
MRBR            0x188 rw - - - - 0x00000000 0x00003ff0 "Maximum Receive Buffer Size Register, offset: 0x188 "   
RSFL            0x190 rw - - - - 0x00000000 0x000000ff "Receive FIFO Section Full Threshold, offset: 0x190 "    
RSEM            0x194 rw - - - - 0x00000000 0x000000ff "Receive FIFO Section Empty Threshold, offset: 0x194 "   
RAEM            0x198 rw - - - - 0x00000004 0x000000ff "Receive FIFO Almost Empty Threshold, offset: 0x198 "    
RAFL            0x19c rw - - - - 0x00000004 0x000000ff "Receive FIFO Almost Full Threshold, offset: 0x19C " 
TSEM            0x1a0 rw - - - - 0x00000000 0x000000ff "Transmit FIFO Section Empty Threshold, offset: 0x1A0 "  
TAEM            0x1a4 rw - - - - 0x00000004 0x000000ff "Transmit FIFO Almost Empty Threshold, offset: 0x1A4 "   
TAFL            0x1a8 rw - - - - 0x00000008 0x000000ff "Transmit FIFO Almost Full Threshold, offset: 0x1A8 "    
TIPG            0x1ac rw - - - - 0x0000000c 0x0000001f "Transmit Inter-Packet Gap, offset: 0x1AC "  
FTRL            0x1b0 rw - - - - 0x000007ff 0x00003fff "Frame Truncation Length, offset: 0x1B0 "    
TACC            0x1c0 rw - - - - 0x00000000 0x00000019 "Transmit Accelerator Function Configuration, offset: 0x1C0 "    
RACC            0x1c4 rw - - - - 0x00000000 0x000000c7 "Receive Accelerator Function Configuration, offset: 0x1C4 " 
RMON_T_DROP        0x200 r - - - - 0x0 0x0 "Count of frames not counted correctly (RMON_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x200 "  
RMON_T_PACKETS     0x204 r - - - - 0x0 0x0 "RMON Tx packet count (RMON_T_PACKETS), offset: 0x204 "  
RMON_T_BC_PKT      0x208 r - - - - 0x0 0x0 "RMON Tx Broadcast Packets (RMON_T_BC_PKT), offset: 0x208 "  
RMON_T_MC_PKT      0x20c r - - - - 0x0 0x0 "RMON Tx Multicast Packets (RMON_T_MC_PKT), offset: 0x20C "  
RMON_T_CRC_ALIGN   0x210 r - - - - 0x0 0x0 "RMON Tx Packets w CRC/Align error (RMON_T_CRC_ALIGN), offset: 0x210 "   
RMON_T_UNDERSIZE   0x214 r - - - - 0x0 0x0 "RMON Tx Packets < 64 bytes, good CRC (RMON_T_UNDERSIZE), offset: 0x214 "    
RMON_T_OVERSIZE    0x218 r - - - - 0x0 0x0 "RMON Tx Packets > MAX_FL bytes, good CRC (RMON_T_OVERSIZE), offset: 0x218 " 
RMON_T_FRAG        0x21c r - - - - 0x0 0x0 "RMON Tx Packets < 64 bytes, bad CRC (RMON_T_FRAG), offset: 0x21C "  
RMON_T_JAB         0x220 r - - - - 0x0 0x0 "RMON Tx Packets > MAX_FL bytes, bad CRC (RMON_T_JAB), offset: 0x220 "   
RMON_T_COL         0x224 r - - - - 0x0 0x0 "RMON Tx collision count (RMON_T_COL), offset: 0x224 "   
RMON_T_P64         0x228 r - - - - 0x0 0x0 "RMON Tx 64 byte packets (RMON_T_P64), offset: 0x228 "   
RMON_T_P65TO127    0x22c r - - - - 0x0 0x0 "RMON Tx 65 to 127 byte packets (RMON_T_P65TO127), offset: 0x22C "   
RMON_T_P128TO255   0x230 r - - - - 0x0 0x0 "RMON Tx 128 to 255 byte packets (RMON_T_P128TO255), offset: 0x230 " 
RMON_T_P256TO511   0x234 r - - - - 0x0 0x0 "RMON Tx 256 to 511 byte packets (RMON_T_P256TO511), offset: 0x234 " 
RMON_T_P512TO1023  0x238 r - - - - 0x0 0x0 "RMON Tx 512 to 1023 byte packets (RMON_T_P512TO1023), offset: 0x238 "   
RMON_T_P1024TO2047 0x23c r - - - - 0x0 0x0 "RMON Tx 1024 to 2047 byte packets (RMON_T_P1024TO2047), offset: 0x23C " 
RMON_T_P_GTE2048   0x240 r - - - - 0x0 0x0 "RMON Tx packets w > 2048 bytes (RMON_T_P_GTE2048), offset: 0x240 "  
RMON_T_OCTETS      0x244 r - - - - 0x0 0x0 "RMON Tx Octets (RMON_T_OCTETS), offset: 0x244 " 
IEEE_T_DROP        0x248 r - - - - 0x0 0x0 "Count of frames not counted correctly (IEEE_T_DROP). NOTE: Counter not implemented (read 0 always) as not applicable., offset: 0x248 "  
IEEE_T_FRAME_OK    0x24c r - - - - 0x0 0x0 "Frames Transmitted OK (IEEE_T_FRAME_OK), offset: 0x24C "    
IEEE_T_1COL        0x250 r - - - - 0x0 0x0 "Frames Transmitted with Single Collision (IEEE_T_1COL), offset: 0x250 " 
IEEE_T_MCOL        0x254 r - - - - 0x0 0x0 "Frames Transmitted with Multiple Collisions (IEEE_T_MCOL), offset: 0x254 "  
IEEE_T_DEF         0x258 r - - - - 0x0 0x0 "Frames Transmitted after Deferral Delay (IEEE_T_DEF), offset: 0x258 "   
IEEE_T_LCOL        0x25c r - - - - 0x0 0x0 "Frames Transmitted with Late Collision (IEEE_T_LCOL), offset: 0x25C "   
IEEE_T_EXCOL       0x260 r - - - - 0x0 0x0 "Frames Transmitted with Excessive Collisions (IEEE_T_EXCOL), offset: 0x260 "    
IEEE_T_MACERR      0x264 r - - - - 0x0 0x0 "Frames Transmitted with Tx FIFO Underrun (IEEE_T_MACERR), offset: 0x264 "   
IEEE_T_CSERR       0x268 r - - - - 0x0 0x0 "Frames Transmitted with Carrier Sense Error (IEEE_T_CSERR), offset: 0x268 " 
IEEE_T_SQE         0x26c r - - - - 0x0 0x0 "Frames Transmitted with SQE Error (IEEE_T_SQE). NOTE: Counter not implemented (read 0 always) as no SQE information is available., offset: 0x26C "  
IEEE_T_FDXFC       0x270 r - - - - 0x0 0x0 "Flow Control Pause frames transmitted (IEEE_T_FDXFC), offset: 0x270 "   
IEEE_T_OCTETS_OK   0x274 r - - - - 0x0 0x0 "Octet count for Frames Transmitted w/o Error (IEEE_T_OCTETS_OK). NOTE: Counts total octets (includes header and FCS fields)., offset: 0x274 "   
RMON_R_PACKETS     0x284 r - - - - 0x0 0x0 "RMON Rx packet count (RMON_R_PACKETS), offset: 0x284 "  
RMON_R_BC_PKT      0x288 r - - - - 0x0 0x0 "RMON Rx Broadcast Packets (RMON_R_BC_PKT), offset: 0x288 "  
RMON_R_MC_PKT      0x28c r - - - - 0x0 0x0 "RMON Rx Multicast Packets (RMON_R_MC_PKT), offset: 0x28C "  
RMON_R_CRC_ALIGN   0x290 r - - - - 0x0 0x0 "RMON Rx Packets w CRC/Align error (RMON_R_CRC_ALIGN), offset: 0x290 "   
RMON_R_UNDERSIZE   0x294 r - - - - 0x0 0x0 "RMON Rx Packets < 64 bytes, good CRC (RMON_R_UNDERSIZE), offset: 0x294 "    
RMON_R_OVERSIZE    0x298 r - - - - 0x0 0x0 "RMON Rx Packets > MAX_FL bytes, good CRC (RMON_R_OVERSIZE), offset: 0x298 " 
RMON_R_FRAG        0x29c r - - - - 0x0 0x0 "RMON Rx Packets < 64 bytes, bad CRC (RMON_R_FRAG), offset: 0x29C "  
RMON_R_JAB         0x2a0 r - - - - 0x0 0x0 "RMON Rx Packets > MAX_FL bytes, bad CRC (RMON_R_JAB), offset: 0x2A0 "   
RMON_R_RESVD_0     0x2a4 r - - - - 0x0 0x0 "Reserved (RMON_R_RESVD_0), offset: 0x2A4 "  
RMON_R_P64         0x2a8 r - - - - 0x0 0x0 "RMON Rx 64 byte packets (RMON_R_P64), offset: 0x2A8 "   
RMON_R_P65TO127    0x2ac r - - - - 0x0 0x0 "RMON Rx 65 to 127 byte packets (RMON_R_P65TO127), offset: 0x2AC "   
RMON_R_P128TO255   0x2b0 r - - - - 0x0 0x0 "RMON Rx 128 to 255 byte packets (RMON_R_P128TO255), offset: 0x2B0 " 
RMON_R_P256TO511   0x2b4 r - - - - 0x0 0x0 "RMON Rx 256 to 511 byte packets (RMON_R_P256TO511), offset: 0x2B4 " 
RMON_R_P512TO1023  0x2b8 r - - - - 0x0 0x0 "RMON Rx 512 to 1023 byte packets (RMON_R_P512TO1023), offset: 0x2B8 "   
RMON_R_P1024TO2047 0x2bc r - - - - 0x0 0x0 "RMON Rx 1024 to 2047 byte packets (RMON_R_P1024TO2047), offset: 0x2BC " 
RMON_R_P_GTE2048   0x2c0 r - - - - 0x0 0x0 "RMON Rx packets w > 2048 bytes (RMON_R_P_GTE2048), offset: 0x2C0 "  
RMON_R_OCTETS      0x2c4 r - - - - 0x0 0x0 "RMON Rx Octets (RMON_R_OCTETS), offset: 0x2C4 " 
RMON_R_DROP        0x2c8 r - - - - 0x0 0x0 "Count of frames not counted correctly (IEEE_R_DROP). NOTE: Counter increments if a frame with valid/missing SFD character is detected and has been dropped. None of the other counters increments if this counter increments., offset: 0x2C8 "  
RMON_R_FRAME_OK    0x2cc r - - - - 0x0 0x0 "Frames Received OK (IEEE_R_FRAME_OK), offset: 0x2CC "   
IEEE_R_CRC         0x2d0 r - - - - 0x0 0x0 "Frames Received with CRC Error (IEEE_R_CRC), offset: 0x2D0 "    
IEEE_R_ALIGN       0x2d4 r - - - - 0x0 0x0 "Frames Received with Alignment Error (IEEE_R_ALIGN), offset: 0x2D4 "    
IEEE_R_MACERR      0x2d8 r - - - - 0x0 0x0 "Receive Fifo Overflow count (IEEE_R_MACERR), offset: 0x2D8 "    
IEEE_R_FDXFC       0x2dc r - - - - 0x0 0x0 "Flow Control Pause frames received (IEEE_R_FDXFC), offset: 0x2DC "  
IEEE_R_OCTETS_OK   0x2e0 r - - - - 0x0 0x0 "Octet count for Frames Rcvd w/o Error (IEEE_R_OCTETS_OK). Counts total octets (includes header and FCS fields)., offset: 0x2E0 "    
ATCR            0x400 rw - - - - 0x00000000 0x00002a9d "Timer Control Register, offset: 0x400 " 
ATVR            0x404 rw - - - - 0x00000000 0xffffffff "Timer Value Register, offset: 0x404 "   
ATOFF           0x408 rw - - - - 0x00000000 0xffffffff "Timer Offset Register, offset: 0x408 "  
ATPER           0x40c rw - - - - 0x3b9aca00 0xffffffff "Timer Period Register, offset: 0x40C "  
ATCOR           0x410 rw - - - - 0x00000000 0x7fffffff "Timer Correction Register, offset: 0x410 "  
ATINC           0x414 rw - - - - 0x00000000 0x00007e7f "Time-Stamping Clock Period Register, offset: 0x414 "    
ATSTMP          0x418 rw - - - - 0x00000000 0xffffffff "Timestamp of Last Transmitted Frame, offset: 0x418 "    
TGSR            0x604 rw - - - - 0x00000000 0x0000000f "Timer Global Status Register, offset: 0x604 "   
TCSR0           0x608 rw - - - - 0x00000000 0x000000fd "Timer Control Status Register, array offset: 0x608, array step: 0x8 "   
TCCR0           0x60c rw - - - - 0x00000000 0xffffffff "Timer Compare Capture Register, array offset: 0x60C, array step: 0x8 "  
TCSR1           0x610 rw - - - - 0x00000000 0x000000fd "Timer Control Status Register, array offset: 0x610, array step: 0x8 "   
TCCR1           0x614 rw - - - - 0x00000000 0xffffffff "Timer Compare Capture Register, array offset: 0x614, array step: 0x8 "  
TCSR2           0x618 rw - - - - 0x00000000 0x000000fd "Timer Control Status Register, array offset: 0x618, array step: 0x8 "   
TCCR2           0x61c rw - - - - 0x00000000 0xffffffff "Timer Compare Capture Register, array offset: 0x61c, array step: 0x8 "  
TCSR3           0x620 rw - - - - 0x00000000 0x000000fd "Timer Control Status Register, array offset: 0x620, array step: 0x8 "   
TCCR3           0x624 rw - - - - 0x00000000 0xffffffff "Timer Compare Capture Register, array offset: 0x624, array step: 0x8 "  
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

    
 
imodeladdfield -mmregister $addBlock/EIR -name BABR -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/EIR -name BABT -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/EIR -name EBERR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EIR -name GRA -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/EIR -name LC -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EIR -name MII -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EIR -name PLR -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/EIR -name RL -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/EIR -name RXB -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/EIR -name RXF -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/EIR -name TS_AVAIL -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EIR -name TS_TIMER -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/EIR -name TXB -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/EIR -name TXF -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/EIR -name UN -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/EIR -name WAKEUP -bitoffset 17  -width 1   
 
imodeladdfield -mmregister $addBlock/EIMR -name BABR -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name BABT -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name EBERR -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name GRA -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name LC -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name MII -bitoffset 23  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name PLR -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name RL -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name RXB -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name RXF -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name TS_AVAIL -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name TS_TIMER -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name TXB -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name TXF -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name UN -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/EIMR -name WAKEUP -bitoffset 17  -width 1  
 
imodeladdfield -mmregister $addBlock/RDAR -name RDAR -bitoffset 24  -width 1    
 
imodeladdfield -mmregister $addBlock/TDAR -name TDAR -bitoffset 24  -width 1    
 
imodeladdfield -mmregister $addBlock/ECR -name DBGEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/ECR -name DBSWP -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/ECR -name EN1588 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ECR -name ETHEREN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/ECR -name MAGICEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ECR -name RESET -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ECR -name SLEEP -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ECR -name STOPEN -bitoffset 7  -width 1    
 
imodeladdfield -mmregister $addBlock/MMFR -name DATA -bitoffset 0  -width 16
imodeladdfield -mmregister $addBlock/MMFR -name OP -bitoffset 28  -width 2
imodeladdfield -mmregister $addBlock/MMFR -name PA -bitoffset 23  -width 5
imodeladdfield -mmregister $addBlock/MMFR -name RA -bitoffset 18  -width 5
imodeladdfield -mmregister $addBlock/MMFR -name ST -bitoffset 30  -width 2
imodeladdfield -mmregister $addBlock/MMFR -name TA -bitoffset 16  -width 2  
 
imodeladdfield -mmregister $addBlock/MSCR -name DIS_PRE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/MSCR -name HOLDTIME -bitoffset 8  -width 3
imodeladdfield -mmregister $addBlock/MSCR -name MII_SPEED -bitoffset 1  -width 6    
 
imodeladdfield -mmregister $addBlock/MIBC -name MIB_CLEAR -bitoffset 29  -width 1
imodeladdfield -mmregister $addBlock/MIBC -name MIB_DIS -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/MIBC -name MIB_IDLE -bitoffset 30  -width 1    
 
imodeladdfield -mmregister $addBlock/RCR -name BC_REJ -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/RCR -name CFEN -bitoffset 15  -width 1
imodeladdfield -mmregister $addBlock/RCR -name CRCFWD -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/RCR -name DRT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/RCR -name FCE -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/RCR -name GRS -bitoffset 31  -width 1
imodeladdfield -mmregister $addBlock/RCR -name LOOP -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/RCR -name MAX_FL -bitoffset 16  -width 14
imodeladdfield -mmregister $addBlock/RCR -name MII_MODE -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/RCR -name NLC -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/RCR -name PADEN -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/RCR -name PAUFWD -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/RCR -name PROM -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/RCR -name RMII_10T -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/RCR -name RMII_MODE -bitoffset 8  -width 1 
 
imodeladdfield -mmregister $addBlock/TCR -name ADDINS -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/TCR -name ADDSEL -bitoffset 5  -width 3
imodeladdfield -mmregister $addBlock/TCR -name CRCFWD -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/TCR -name FDEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/TCR -name GTS -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCR -name RFC_PAUSE -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/TCR -name TFC_PAUSE -bitoffset 3  -width 1 
 
imodeladdfield -mmregister $addBlock/PALR -name PADDR1 -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/PAUR -name PADDR2 -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/PAUR -name TYPE -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/OPD -name OPCODE -bitoffset 16  -width 16
imodeladdfield -mmregister $addBlock/OPD -name PAUSE_DUR -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/IAUR -name IADDR1 -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/IALR -name IADDR2 -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/GAUR -name GADDR1 -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/GALR -name GADDR2 -bitoffset 0  -width 32  
 
imodeladdfield -mmregister $addBlock/TFWR -name STRFWD -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/TFWR -name TFWR -bitoffset 0  -width 6 
 
imodeladdfield -mmregister $addBlock/RDSR -name R_DES_START -bitoffset 3  -width 29 
 
imodeladdfield -mmregister $addBlock/TDSR -name X_DES_START -bitoffset 3  -width 29 
 
imodeladdfield -mmregister $addBlock/MRBR -name R_BUF_SIZE -bitoffset 4  -width 10  
 
imodeladdfield -mmregister $addBlock/RSFL -name RX_SECTION_FULL -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/RSEM -name RX_SECTION_EMPTY -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/RAEM -name RX_ALMOST_EMPTY -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/RAFL -name RX_ALMOST_FULL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/TSEM -name TX_SECTION_EMPTY -bitoffset 0  -width 8 
 
imodeladdfield -mmregister $addBlock/TAEM -name TX_ALMOST_EMPTY -bitoffset 0  -width 8  
 
imodeladdfield -mmregister $addBlock/TAFL -name TX_ALMOST_FULL -bitoffset 0  -width 8   
 
imodeladdfield -mmregister $addBlock/TIPG -name IPG -bitoffset 0  -width 5  
 
imodeladdfield -mmregister $addBlock/FTRL -name TRUNC_FL -bitoffset 0  -width 14    
 
imodeladdfield -mmregister $addBlock/TACC -name IPCHK -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/TACC -name PROCHK -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/TACC -name SHIFT16 -bitoffset 0  -width 1  
 
imodeladdfield -mmregister $addBlock/RACC -name IPDIS -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/RACC -name LINEDIS -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/RACC -name PADREM -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/RACC -name PRODIS -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/RACC -name SHIFT16 -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/ATCR -name CAPTURE -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name EN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name OFFEN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name OFFRST -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name PEREN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name PINPER -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name RESTART -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/ATCR -name SLAVE -bitoffset 13  -width 1   
 
imodeladdfield -mmregister $addBlock/ATVR -name ATIME -bitoffset 0  -width 32   
 
imodeladdfield -mmregister $addBlock/ATOFF -name OFFSET -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/ATPER -name PERIOD -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/ATCOR -name COR -bitoffset 0  -width 31    
 
imodeladdfield -mmregister $addBlock/ATINC -name INC -bitoffset 0  -width 7
imodeladdfield -mmregister $addBlock/ATINC -name INC_CORR -bitoffset 8  -width 7    
 
imodeladdfield -mmregister $addBlock/ATSTMP -name TIMESTAMP -bitoffset 0  -width 32 
 
imodeladdfield -mmregister $addBlock/TGSR -name TF0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TGSR -name TF1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/TGSR -name TF2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/TGSR -name TF3 -bitoffset 3  -width 1  
 
imodeladdfield -mmregister $addBlock/TCSR0 -name TDRE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCSR0 -name TF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/TCSR0 -name TIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/TCSR0 -name TMODE -bitoffset 2  -width 4   

imodeladdfield -mmregister $addBlock/TCSR1 -name TDRE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCSR1 -name TF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/TCSR1 -name TIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/TCSR1 -name TMODE -bitoffset 2  -width 4   

imodeladdfield -mmregister $addBlock/TCSR2 -name TDRE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCSR2 -name TF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/TCSR2 -name TIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/TCSR2 -name TMODE -bitoffset 2  -width 4   

imodeladdfield -mmregister $addBlock/TCSR3 -name TDRE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/TCSR3 -name TF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/TCSR3 -name TIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/TCSR3 -name TMODE -bitoffset 2  -width 4   
 
imodeladdfield -mmregister $addBlock/TCCR0 -name TCC -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/TCCR1 -name TCC -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/TCCR2 -name TCC -bitoffset 0  -width 32    
imodeladdfield -mmregister $addBlock/TCCR3 -name TCC -bitoffset 0  -width 32    
    
    
    
 
