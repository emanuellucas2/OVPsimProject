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

set vendor  xilinx.ovpworld.org
set library peripheral
set name    zynq_7000-ttc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Triple Timer Counter Registers"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers and basic behavior. It is not yet completed."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    Clock_Control_1       0x00000000  7 rw 0x00000000 -          wrClkCtrl1  0x7f {E 6 1 SRC 5 1 PS_V 1 4 PS_EN 0 1} "Clock Control register"
    Clock_Control_2       0x00000004  7 rw 0x00000000 -          wrClkCtrl2  0x7f {E 6 1 SRC 5 1 PS_V 1 4 PS_EN 0 1} "Clock Control register"
    Clock_Control_3       0x00000008  7 rw 0x00000000 -          wrClkCtrl3  0x7f {E 6 1 SRC 5 1 PS_V 1 4 PS_EN 0 1} "Clock Control register"
    Counter_Control_1     0x0000000C  7 rw 0x00000021 -          wrCntrCtrl1 0x7f {WAVPOL 6 1 WAVEN 5 1 RST 4 1 MATCH 3 1 DEC 2 1 INT 1 1 DIS 0 1} "Operational mode and reset"
    Counter_Control_2     0x00000010  7 rw 0x00000021 -          wrCntrCtrl2 0x7f {WAVPOL 6 1 WAVEN 5 1 RST 4 1 MATCH 3 1 DEC 2 1 INT 1 1 DIS 0 1} "Operational mode and reset"
    Counter_Control_3     0x00000014  7 rw 0x00000021 -          wrCntrCtrl3 0x7f {WAVPOL 6 1 WAVEN 5 1 RST 4 1 MATCH 3 1 DEC 2 1 INT 1 1 DIS 0 1} "Operational mode and reset"
    Counter_Value_1       0x00000018 16 r  0x00000000 rdCurrent1 -          -    - "Current counter value"
    Counter_Value_2       0x0000001C 16 r  0x00000000 rdCurrent2 -          -    - "Current counter value"
    Counter_Value_3       0x00000020 16 r  0x00000000 rdCurrent3 -          -    - "Current counter value"
    Interval_Counter_1    0x00000024 16 rw 0x00000000 -          -          -    - "Interval value"
    Interval_Counter_2    0x00000028 16 rw 0x00000000 -          -          -    - "Interval value"
    Interval_Counter_3    0x0000002C 16 rw 0x00000000 -          -          -    - "Interval value"
    Match_1_Counter_1     0x00000030 16 rw 0x00000000 -          -          -    - "Match value"
    Match_1_Counter_2     0x00000034 16 rw 0x00000000 -          -          -    - "Match value"
    Match_1_Counter_3     0x00000038 16 rw 0x00000000 -          -          -    - "Match value"
    Match_2_Counter_1     0x0000003C 16 rw 0x00000000 -          -          -    - "Match value"
    Match_2_Counter_2     0x00000040 16 rw 0x00000000 -          -          -    - "Match value"
    Match_2_Counter_3     0x00000044 16 rw 0x00000000 -          -          -    - "Match value"
    Match_3_Counter_1     0x00000048 16 rw 0x00000000 -          -          -    - "Match value"
    Match_3_Counter_2     0x0000004C 16 rw 0x00000000 -          -          -    - "Match value"
    Match_3_Counter_3     0x00000050 16 rw 0x00000000 -          -          -    - "Match value"
    Interrupt_Register_1  0x00000054  6 rw 0x00000000 rdInt1     wrInt      -    {EV 5 1 OV 4 1 M3 3 1 M2 2 1 M1 1 1 IV 0 1} "Counter 1 Interval, Match, Overflow and Event interrupts"
    Interrupt_Register_2  0x00000058  6 rw 0x00000000 rdInt2     wrInt      -    {EV 5 1 OV 4 1 M3 3 1 M2 2 1 M1 1 1 IV 0 1} "Counter 2 Interval, Match, Overflow and Event interrupts"
    Interrupt_Register_3  0x0000005C  6 rw 0x00000000 rdInt3     wrInt      -    {EV 5 1 OV 4 1 M3 3 1 M2 2 1 M1 1 1 IV 0 1} "Counter 3 Interval, Match, Overflow and Event interrupts"
    Interrupt_Enable_1    0x00000060  6 rw 0x00000000 -          -          -    - "ANDed with corresponding Interrupt Register"
    Interrupt_Enable_2    0x00000064  6 rw 0x00000000 -          -          -    - "ANDed with corresponding Interrupt Register"
    Interrupt_Enable_3    0x00000068  6 rw 0x00000000 -          -          -    - "ANDed with corresponding Interrupt Register"
    Event_Control_Timer_1 0x0000006C  3 rw 0x00000000 -          -          -    {OV 2 1 LO 1 1 EN 0 1 } "Enable, pulse and overflow"
    Event_Control_Timer_2 0x00000070  3 rw 0x00000000 -          -          -    {OV 2 1 LO 1 1 EN 0 1 } "Enable, pulse and overflow"
    Event_Control_Timer_3 0x00000074  3 rw 0x00000000 -          -          -    {OV 2 1 LO 1 1 EN 0 1 } "Enable, pulse and overflow"
    Event_Register_1      0x00000078 16 r  0x00000000 -          -          -    - "pclk cycle count for event"
    Event_Register_2      0x0000007C 16 r  0x00000000 -          -          -    - "pclk cycle count for event"
    Event_Register_3      0x00000080 16 r  0x00000000 -          -          -    - "pclk cycle count for event"
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width 32 -offset $roffset -access $raccess"
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

  if { $writeMask != "-" } {
    set command "${command} -writemask $writeMask"
  }

  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
    }
  }
  
  imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $reset
}

imodeladdnetport  -name int1 -type output
iadddocumentation -name Description  -text "Interrupt Timer 1"

imodeladdnetport  -name int2 -type output
iadddocumentation -name Description  -text "Interrupt Timer 2"

imodeladdnetport  -name int3 -type output
iadddocumentation -name Description  -text "Interrupt Timer 3"

# default pclk
set pclk 33
imodeladdformal   -name clk1 -type uns32 -defaultvalue ${pclk}
iadddocumentation -name Description   -text "Timer 1 Clock Rate MHz (default ${pclk}MHz)"

imodeladdformal   -name clk2 -type uns32 -defaultvalue ${pclk}
iadddocumentation -name Description   -text "Timer 2 Clock Rate MHz (default ${pclk}MHz)"

imodeladdformal   -name clk3 -type uns32 -defaultvalue ${pclk}
iadddocumentation -name Description   -text "Timer 3 Clock Rate MHz (default ${pclk}MHz)"

set defaultEndian "little"
imodeladdformal -name endian -type string -defaultvalue ${defaultEndian} 
iadddocumentation  -name Description -text "Specify the endian of the processor interface (default ${defaultEndian} endian)"
 
