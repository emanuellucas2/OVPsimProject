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

set vendor  atmel.ovpworld.org
set library peripheral
set name    TimerCounter
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Description -text "TC: Timer Counter
This model contains an accurate Register set interface.
The functionality has only been implemented to sufficiently boot uClinux
The Timer Counter block includes three identical 16-bit timer
counter channels. Each channel can be independently programmed to perform a wide range of
functions including frequency measurement, event counting, interval measurement, pulse generation,
delay timing and pulse width modulation.
The Timer Counter can be used in Capture or Waveform mode, and all three counter channels
can be started simultaneously and chained together.
for more information visit http://www.atmel.com/products/at91"

iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

imodeladdbusslaveport -name bp1 -mustbeconnected -size 0x4000
imodeladdaddressblock -name REG -port bp1 -size 0x4000 -offset 0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name IRQ0 -type output
imodeladdnetport -name IRQ1 -type output
imodeladdnetport -name IRQ2 -type output

set tcChannelMemoryMapRegisters {
  TC_CCR  0x00 w  0x0 - TC_CCR_wcb
  TC_CMR  0x04 rw 0x0 - TC_CMR_wcb
  TC_RSV0 0x08 -    - - -
  TC_RSV1 0x0c -    - - -
  TC_CVR  0x10 rw 0x0 - TC_CVR_wcb
  TC_RA   0x14 rw 0x0 - TC_RA_wcb
  TC_RB   0x18 rw 0x0 - TC_RB_wcb
  TC_RC   0x1c rw 0x0 - TC_RC_wcb
  TC_SR   0x20 r  0x0 - -
  TC_IER  0x24 w  0x0 - TC_IER_wcb
  TC_IDR  0x28 w  0x0 - TC_IDR_wcb
  TC_IMR  0x2c r  0x0 - -
}

set registers {
  TC_BCR  0xc0 w  0x0 - TC_BCR_wcb
  TC_BMR  0xc4 w  0x0 - TC_BMR_wcb
}

#
# Channel based registers
#
foreach channel {0 1 2} {
  set addressShift [expr $channel << 6]

  foreach {chname choffset raccess reset readFunc writeFunc} $tcChannelMemoryMapRegisters {
    # Ignore reserved registers
    if {$raccess == "-"} {continue}

    set roffset [format 0x%08x [expr $choffset + $addressShift]]
    set rname ${chname}${channel}

    set command "imodeladdmmregister -addressblock bp1/REG -name $rname -width 32 -offset $roffset -access $raccess"
    
    if { $readFunc != "-" } {
      set command "${command} -readfunction ${readFunc}${channel}"
    }
    if { $writeFunc != "-" } {
      set command "${command} -writefunction ${writeFunc}${channel}"
    }
  
    eval $command

    imodeladdreset -mmregister bp1/REG/$rname -name resetNet -value $reset
  }

  #
  # TC_CCR
  #
  imodeladdfield -mmregister bp1/REG/TC_CCR${channel} -name SWTRG  -bitoffset 2 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CCR${channel} -name CLKDIS -bitoffset 1 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CCR${channel} -name CLKEN  -bitoffset 0 -width 1

  #
  # TC_CMR (capture Mode)
  #
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name LDRB    -bitoffset 18 -width 2
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name LDRA    -bitoffset 16 -width 2
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name WAVE    -bitoffset 15 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name CPCTRG  -bitoffset 14 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name ABETRG  -bitoffset 10 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name ETRGEDG -bitoffset  8 -width 2
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name LDBDIS  -bitoffset  7 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name LDBSTOP -bitoffset  6 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name BURST   -bitoffset  4 -width 2
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name CLKI    -bitoffset  3 -width 1
  imodeladdfield -mmregister bp1/REG/TC_CMR${channel} -name TCCLKS  -bitoffset  0 -width 3

  #
  # TC_CVR (capture Mode)
  #
  imodeladdfield -mmregister bp1/REG/TC_CVR${channel} -name CV -bitoffset 0 -width 16

  #
  # TC_RA,B,C
  #
  imodeladdfield -mmregister bp1/REG/TC_RA${channel} -name RA -bitoffset 0 -width 16
  imodeladdfield -mmregister bp1/REG/TC_RB${channel} -name RB -bitoffset 0 -width 16
  imodeladdfield -mmregister bp1/REG/TC_RC${channel} -name RC -bitoffset 0 -width 16

  #
  # TC_SR
  #
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name MTIOB  -bitoffset 18 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name MTIOA  -bitoffset 17 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name CLKSTA -bitoffset 16 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name ETRGS  -bitoffset  7 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name LDRBS  -bitoffset  6 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name LDRAS  -bitoffset  5 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name CPCS   -bitoffset  4 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name CPBS   -bitoffset  3 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name CPAS   -bitoffset  2 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name LOVRS  -bitoffset  1 -width 1
  imodeladdfield -mmregister bp1/REG/TC_SR${channel} -name COVFS  -bitoffset  0 -width 1

  #
  # TC_IER
  #
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name ETRGS  -bitoffset  7 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name LDRBS  -bitoffset  6 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name LDRAS  -bitoffset  5 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name CPCS   -bitoffset  4 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name CPBS   -bitoffset  3 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name CPAS   -bitoffset  2 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name LOVRS  -bitoffset  1 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IER${channel} -name COVFS  -bitoffset  0 -width 1

  #
  # TC_IDR
  #
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name ETRGS  -bitoffset  7 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name LDRBS  -bitoffset  6 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name LDRAS  -bitoffset  5 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name CPCS   -bitoffset  4 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name CPBS   -bitoffset  3 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name CPAS   -bitoffset  2 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name LOVRS  -bitoffset  1 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IDR${channel} -name COVFS  -bitoffset  0 -width 1

  #
  # TC_IMR
  #
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name ETRGS  -bitoffset  7 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name LDRBS  -bitoffset  6 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name LDRAS  -bitoffset  5 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name CPCS   -bitoffset  4 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name CPBS   -bitoffset  3 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name CPAS   -bitoffset  2 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name LOVRS  -bitoffset  1 -width 1
  imodeladdfield -mmregister bp1/REG/TC_IMR${channel} -name COVFS  -bitoffset  0 -width 1

}

#
# Block Based Registers
#
foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock bp1/REG -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc != "-" } {
    set command "${command} -readfunction $readFunc"
  }
  if { $writeFunc != "-" } {
    set command "${command} -writefunction $writeFunc"
  }
  
  eval $command

  imodeladdreset -mmregister bp1/REG/$rname -name resetNet -value $reset
}

#
# TC_BCR
#
imodeladdfield -mmregister bp1/REG/TC_BCR -name SYNC -bitoffset 0 -width 1

#
# TC_BMR
#
imodeladdfield -mmregister bp1/REG/TC_BMR -name TC2X2CS -bitoffset 4 -width 2
imodeladdfield -mmregister bp1/REG/TC_BMR -name TC1X1CS -bitoffset 2 -width 2
imodeladdfield -mmregister bp1/REG/TC_BMR -name TC0X0CS -bitoffset 0 -width 2

