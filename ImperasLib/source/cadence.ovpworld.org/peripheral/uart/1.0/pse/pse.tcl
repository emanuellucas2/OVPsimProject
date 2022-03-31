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

set vendor  cadence.ovpworld.org
set library peripheral
set name    uart
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor  \
    -releasestatus ovp

iadddocumentation  \
    -name Description  \
    -text "Cadence UART (Xilinx Zync Platform)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

set limitation1 "This is an incomplete model of the Cadence UART (uartps) as used on the Xilinx Zync devices."
set limitation2 "It has basic functionality to support Linux boot on the Xilinx Zync platform."
set limitation3 "There is no modeling of physical aspects of the UART, such as baud rates etc."
iadddocumentation -name Limitations -text $limitation1
iadddocumentation -name Limitations -text $limitation2
iadddocumentation -name Limitations -text $limitation3

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

imodeladdformal -name charmode -type boolean

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

set port  bport1
set block ab
set size  0x1000
imodeladdbusslaveport  -name $port -mustbeconnected -size $size
imodeladdaddressblock  -name $block -port $port -size $size -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock $port/$block -size $size \
                     -writefunction regNoDefinitionRead -readfunction regNoDefinitionWrite

set registers {
    Control                 0x00000000 32 rw 0x00000128 0x0000001f  -   auto {STPBRK 8 1 STTBRK 7 1 RSTT0 6 1 TXDIS 5 1 TXEN 4 1 RXDIS 3 1 RXEN 2 1 TXRES 1 1 RXRES 0 1} "UART Control Register"
    mode                    0x00000004 32 rw 0x00000000 0x000007ff  -   -    {CHMODE 8 2 NBSTOP 6 2 PAR 3 3 CHRL 1 2 CLKS 0 1} "UART Mode Register (no effect)"
    Intrpt_en               0x00000008 32 rw 0x00000000 0x00001fff  -   auto {TOVR 12 1 TNFUL 11 1 TTRIG 10 1 DMSI 9 1 TIMEOUT 8 1 PARE 7 1 FRAME 6 1 ROVR 5 1 TFUL 4 1 TEMPTY 3 1 RFUL 2 1 REMPTY 1 1 RTRIG 0 1} "Interrupt Enable Register"
    Intrpt_dis              0x0000000C 32 rw 0x00000000 0x00001fff  -   auto {TOVR 12 1 TNFUL 11 1 TTRIG 10 1 DMSI 9 1 TIMEOUT 8 1 PARE 7 1 FRAME 6 1 ROVR 5 1 TFUL 4 1 TEMPTY 3 1 RFUL 2 1 REMPTY 1 1 RTRIG 0 1} "Interrupt Disable Register"
    Intrpt_mask             0x00000010 32 r  0x00000000 -          auto  -   {TOVR 12 1 TNFUL 11 1 TTRIG 10 1 DMSI 9 1 TIMEOUT 8 1 PARE 7 1 FRAME 6 1 ROVR 5 1 TFUL 4 1 TEMPTY 3 1 RFUL 2 1 REMPTY 1 1 RTRIG 0 1} "Interrupt Mask Register"
    Chnl_int_sts            0x00000014 32 rw 0x00000000 0x00001fff  -   auto {TOVR 12 1 TNFUL 11 1 TTRIG 10 1 DMSI 9 1 TIMEOUT 8 1 PARE 7 1 FRAME 6 1 ROVR 5 1 TFUL 4 1 TEMPTY 3 1 RFUL 2 1 REMPTY 1 1 RTRIG 0 1} "Channel Interrupt Status Register"
    Baud_rate_gen           0x00000018 32 rw 0x0000028B 0x0000ffff  -    -   {CD 0 16} "Baud Rate Generator Register (no effect)"
    Rcvr_timeout            0x0000001C 32 rw 0x00000000 0x000000ff  -    -   {RTO 0 8} "Receiver Timeout Register (no effect)"
    Rcvr_FIFO_trigger_level 0x00000020 32 rw 0x00000020 0x0000003f  -    -   {RTRIG 0 6} "Receiver FIFO Trigger Level Register"
    Modem_ctrl              0x00000024 32 rw 0x00000000 0x00000013  -    -   {FCM 5 1 RTS 1 1 DTR 0 1} "Modem Control Register (no effect)"
    Modem_sts               0x00000028 32 rw 0x00000000 0x000001ff  -    -   {FCMS 8 1 DCD 7 1 RI 6 1 DSR 5 1 CTS 4 1 DDCD 3 1 TERI 2 1 DDSR 1 1 DCTS 0 1} "Modem Status Register (no effect)"
    Channel_sts             0x0000002C 32 r  0x00000000 -          auto  -   {TNFUL 14 1 TTRIG 13 1 FDELT 12 1 TACTIVE 11 1 RACTIVE 10 1 TFUL 4 1 TEMPTY 3 1 RFUL 2 1 REMPTY 1 1 RTRIG 0 1} "Channel Status Register"
    TX_RX_FIFO              0x00000030 32 rw 0x00000000 -          auto auto {FIF0 0 8} "Transmit and Receive FIFO"
    Baud_rate_divider       0x00000034 32 rw 0x0000000F 0x000000ff  -    -   {BDIV 0 8} "Baud Rate Divider Register (no effect)"
    Flow_delay              0x00000038 32 rw 0x00000000 0x0000001f  -    -   {FDEL 0 6} "Flow Control Delay Register (no effect)"
    Tx_FIFO_trigger_level   0x00000044 32 rw 0x00000020 0x0000001f  -    -   {TTRIG 0 6} "Transmitter FIFO Trigger Level Register (no effect)"
}

foreach {rname roffset rsize raccess reset maskWrite readFunc writeFunc bits description} $registers {
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
    foreach { n o w } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}

# Interrupt line
imodeladdnetport -name irq -type output
