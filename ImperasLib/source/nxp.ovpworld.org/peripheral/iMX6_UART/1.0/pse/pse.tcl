#
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

set vendor  nxp.ovpworld.org
set library peripheral
set name    iMX6_UART
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor  \
    -releasestatus ovp

iadddocumentation -name Description -text "iMX6 UART"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This is an incomplete model of the UART."
iadddocumentation -name Limitations -text "It has basic functionality to support the iMX6 platform, Rx and Tx of data only."
iadddocumentation -name Limitations -text "There is no modeling of physical aspects of the UART, such as baud rates etc."

iadddocumentation -name Reference \
                  -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

imodeladdformal -name charmode -type boolean

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

set port  bport1
set block ab
set size  0x4000
imodeladdbusslaveport  -name $port -mustbeconnected -size $size
imodeladdaddressblock  -name $block -port $port -size $size -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock $port/$block -size $size \
                     -writefunction regNoDefinitionRead -readfunction regNoDefinitionWrite

set registers {
    UART_URXD  0x00  32 r  0x00000000 -          auto -    "UART Receiver Register (UART_URXD)"
        {   CHARRDY  15 1 -
            ERR      14 1 -
            OVRRUN   13 1 -
            FRMERR   12 1 -
            BRK      11 1 -
            PRERR    10 1 -
            DATA      0 8 -
        }    
    UART_UTXD  0x40  32  w 0x00000000 0x000000ff -    auto "UART Transmitter Register (UART_UTXD)"
        {   DATA 0 8   }
    UART_UCR1  0x80  32 rw 0x00000000 0x0000ffff -    auto "UART Control Register 1 (UART_UCR1)"
        {   ADEN     15 1 -
            ADBR     14 1 -
            TRDYEN   13 1 -
            IDEN     12 1 -
            ICD      10 2 -
            RRDYEN    9 1 -
            RXDMAEN   8 1 -
            IREN      7 1 -
            TXMPTYEN  6 1 -
            RTSDEN    5 1 -
            SNDBRK    4 1 -
            TXDMAEN   3 1 -
            ATDMAEN   2 1 -
            DOZE      1 1 -
            UARTEN    0 1 -
        }
    UART_UCR2  0x84  32 rw 0x00000001 0x0000ffff -    auto "UART Control Register 2 (UART_UCR2)"
        {   ESCI  15 1 -
            IRTS  14 1 -
            CTSC  13 1 -
            CTS   12 1 -
            ESCEN 11 1 -
            RTEC   9 2 -
            PREN   8 1 -
            PROE   7 1 -
            STPB   6 1 -
            WS     5 1 -
            RTSEN  4 1 -
            ATEN   3 1 -
            TXEN   2 1 -
            RXEN   1 1 -
            SRST   0 1 -
        }
    UART_UCR3  0x88  32 rw 0x00000700 0x0000ffff -    auto "UART Control Register 3 (UART_UCR3)"
        {   DPEC     14 2 -
            DTREN    13 1 -
            PARERREN 12 1 -
            FRAERREN 11 1 -
            DSR      10 1 -
            DCD       9 1 -
            RI        8 1 -
            ADNIMP    7 1 -
            RXDSEN    6 1 -
            AIRINTEN  5 1 -
            AWAKEN    4 1 -
            DTRDEN    3 1 -
            RXDMUXSEL 2 1 -
            INVT      1 1 -
            ACIEN     0 1 -
        }
    UART_UCR4  0x8c  32 rw 0x00008000 0x0000ffff -    auto "UART Control Register 4 (UART_UCR4)"
        {   CTSTL  10 6 -
            INVR    9 1 -
            ENIRI   8 1 -
            WKEN    7 1 -
            IDDMAEN 6 1 -
            IRSC    5 1 -
            LPBYP   4 1 -
            TCEN    3 1 -
            BKEN    2 1 -
            OREN    1 1 -
            DREN    0 1 -
        }
    UART_UFCR  0x90  32 rw 0x00000801 0x0000ffff -    auto "UART FIFO Control Register (UART_UFCR)"
        {   TXTL  10 6 -
            RFDIV  7 3 -
            DCEDTE 6 1 -
            RXTL   0 6 -
        }
    UART_USR1  0x94  32 rw 0x00002040 0x00009db8 -    auto "UART Status Register 1 (UART_USR1)"
        {   PARITYERR 15 1 -
            RTSS      14 1 -
            TRDY      13 1 "Transmitter Ready Interrupt"
            RTSD      12 1 -
            ESCF      11 1 -
            FRAMERR   10 1 -
            RRDY       9 1 "Receiver Ready Interrupt"
            AGTIM      8 1 -
            DTRD       7 1 -
            RXDS       6 1 "Receiver Idle"
            AIRINT     5 1 -
            AWAKE      4 1 -
            SAD        3 1 -
        }
    UART_USR2  0x98  32 rw 0x00004028 0x0000bdd6 -    auto "UART Status Register 2 (UART_USR2)"
        {   ADET   15 1 -
            TXFE   14 1 -
            DTRF   13 1 -
            IDLE   12 1 -
            ACST   11 1 -
            RIDELT 10 1 -
            RIIN    9 1 -
            IRINT   8 1 -
            WAKE    7 1 -
            DCDDELT 6 1 -
            DCDIN   5 1 -
            RTSF    4 1 -
            TXDC    3 1 -
            BRCD    2 1 -
            ORE     1 1 -
            RDR     0 1 -
        }
    UART_UESC  0x9c  32 rw 0x0000002B 0x000000ff -    -    "UART Escape Character Register (UART_UESC)"
        {   ESC_CHAR 0 8 - }
    UART_UTIM  0xa0  32 rw 0x00000000 0x00000fff -    -    "UART Escape Timer Register (UART_UTIM)"
        {   TIM 0 12 - }  
    UART_UBIR  0xa4  32 rw 0x00000000 0x0000ffff -    -    "UART BRM Incremental Register (UART_UBIR)"
        {   INC 0 16 -}  
    UART_UBMR  0xa8  32 rw 0x00000000 0x0000ffff -    -    "UART BRM Modulator Register (UART_UBMR)"
        {   MOD 0 16 - }  
    UART_UBRC  0xac  32 r  0x00000004 -          -    -    "UART Baud Rate Count Register (UART_UBRC)"
        {   BCNT 0 16 - } 
    UART_ONEMS 0xb0  32 rw 0x00000000 0x00ffffff -    -    "UART One Millisecond Register (UART_ONEMS"
        {   ONEMS 0 24 - }
    UART_UTS   0xb4  32 rw 0x00000060 0x00003e79 -    -    "UART Test Register (UART_UTS)"
        {   FRCPERR 13 1 -
            LOOP    12 1 -
            DBGEN   11 1 -
            LOOPIR  10 1 -
            RXDBG    9 1 -
            TXEMPTY  6 1 -
            RXEMPTY  5 1 -
            TXFULL   4 1 -
            RXFULL   3 1 -
            SOFTRST  0 1 -
        }
    UART_UMCR  0xb8  32 rw 0x00000000 0x0000ff0f -    auto "UART RS-485 Mode Control Register (UART_UMCR)"
        {   SLADDR 8 8 -
            SADEN  3 1 -
            TXB8   2 1 -
            SLAM   1 1 -
            MDEN   0 1 -
        }
}

foreach {rname roffset rsize raccess reset maskWrite readFunc writeFunc description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      puts "Register $rname is not 32-bits ignored"
      continue
  }

  set command "imodeladdmmregister -addressblock $port/$block -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
  } else {
    set command "${command} -readfunction $readFunc"
  }
  
  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
  } else {
    set command "${command} -writefunction $writeFunc"
  }

  if { $maskWrite == "-" } {
    set defaultcb 1
  } else {
    set command "${command} -writemask $maskWrite"
  }
  
  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != 0 } {
    foreach { n o w d } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        if { $d != "-" } {
            iadddocumentation  -handle $port/$block/$rname -name Description -text $d
        }
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}

# Interrupt line
imodeladdnetport -name irq -type output
