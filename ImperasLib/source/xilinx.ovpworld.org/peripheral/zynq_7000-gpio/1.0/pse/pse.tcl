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
set name    zynq_7000-gpio
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Platform GPIO Registers (gpio)"

iadddocumentation  \
    -name Description  \
    -text "Included is the visualization of LED and SW connectivity for the ZC702/ZC706 devices."

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements only the registers for generation of input or output data values."
iadddocumentation  \
    -name Limitations  \
    -text "No interrupt generation is currently included in the model."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set PORT    bport1
set AB      REG
set AB_SIZE 0x1000

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width 32

imodeladdlocalmemory -name buffer0 -addressblock $PORT/$AB -size 60 -offset 0 \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead
# gap 0x60-0x70 where read only data registers implemented as memory
imodeladdlocalmemory -name buffer1 -addressblock $PORT/$AB -size [expr $AB_SIZE-0x70] -offset 0x70 \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead
                     

#   name            offset   size access reset   readFunc      writeFunc  user bits                   description
set registers {
    MASK_DATA_0_LSW 0x00000000 32 rw  0x00000000 rMASK         wMASK         0 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank0, MIO, Lower 16bits)"
    MASK_DATA_0_MSW 0x00000004 32 rw  0x00000000 rMASK         wMASK         1 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank0, MIO, Upper 16bits)"
    MASK_DATA_1_LSW 0x00000008 32 rw  0x00000000 rMASK         wMASK         2 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank1, MIO, Lower 16bits)"
    MASK_DATA_1_MSW 0x0000000C 22 rw  0x00000000 rMASK         wMASK         3 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank1, MIO, Upper 6bits)"
    MASK_DATA_2_LSW 0x00000010 32 rw  0x00000000 rMASK         wMASK         4 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank2, EMIO, Lower 16bits)"
    MASK_DATA_2_MSW 0x00000014 32 rw  0x00000000 rMASK         wMASK         5 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank2, EMIO, Upper 16bits)"
    MASK_DATA_3_LSW 0x00000018 32 rw  0x00000000 rMASK         wMASK         6 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank3, EMIO, Lower 16bits)"
    MASK_DATA_3_MSW 0x0000001C 32 rw  0x00000000 rMASK         wMASK         7 {DATA 0 16 MASK 16 16} "Maskable Output Data (GPIO Bank3, EMIO, Upper 16bits)"
    DATA_0          0x00000040 32 rw  0x00000000 rDATA         wDATA         0 {LOW 0 16 HIGH 16 16}  "Output Data (GPIO Bank0, MIO)"
    DATA_1          0x00000044 22 rw  0x00000000 rDATA         wDATA         1 {LOW 0 16 HIGH 16 16}  "Output Data (GPIO Bank1, MIO)"
    DATA_2          0x00000048 32 rw  0x00000000 rDATA         wDATA         2 {LOW 0 16 HIGH 16 16}  "Output Data (GPIO Bank2, EMIO)"
    DATA_3          0x0000004C 32 rw  0x00000000 rDATA         wDATA         3 {LOW 0 16 HIGH 16 16}  "Output Data (GPIO Bank3, EMIO)"
    DIRM_0          0x00000204 32 rw  0x00000000 rDIRM         wDIRM         0 -                      "Direction mode (GPIO Bank0,MIO)"
    OEN_0           0x00000208 32 rw  0x00000000 rOEN          wOEN          0 -                      "Output enable (GPIO Bank0,MIO)"
    INT_MASK_0      0x0000020C 32 r   0x00000000 rINT_MASK     -             0 -                      "Interrupt Mask Status (GPIO Bank0, MIO)"
    INT_EN_0        0x00000210 32  w  0x00000000 -             wINT_EN       0 -                      "Interrupt Enable/Unmask (GPIO Bank0, MIO)"
    INT_DIS_0       0x00000214 32  w  0x00000000 -             wINT_DIS      0 -                      "Interrupt Disable/Mask (GPIO Bank0, MIO)"
    INT_STAT_0      0x00000218 32  w  0x00000000 -             wINT_STAT     0 -                      "Interrupt Status (GPIO Bank0, MIO)"
    INT_TYPE_0      0x0000021C 32 rw  0xFFFFFFFF rINT_TYPE     wINT_TYPE     0 -                      "Interrupt Type (GPIO Bank0, MIO)"
    INT_POLARITY_0  0x00000220 32 rw  0x00000000 rINT_POLARITY wINT_POLARITY 0 -                      "Interrupt Polarity (GPIO Bank0, MIO)"
    INT_ANY_0       0x00000224 32 rw  0x00000000 rINT_ANY      wINT_ANY      0 -                      "Interrupt Any Edge Sensitive (GPIO Bank0, MIO)"
    DIRM_1          0x00000244 22 rw  0x00000000 rDIRM         wDIRM         1 -                      "Direction mode (GPIO Bank1, MIO)"
    OEN_1           0x00000248 22 rw  0x00000000 rOEN          wOEN          1 -                      "Output enable (GPIO Bank1, MIO)"
    INT_MASK_1      0x0000024C 22 r   0x00000000 rINT_MASK     -             1 -                      "Interrupt Mask Status (GPIO Bank1, MIO)"
    INT_EN_1        0x00000250 22  w  0x00000000 -             wINT_EN       1 -                      "Interrupt Enable/Unmask (GPIO Bank1, MIO)"
    INT_DIS_1       0x00000254 22  w  0x00000000 -             wINT_DIS      1 -                      "Interrupt Disable/Mask (GPIO Bank1, MIO)"
    INT_STAT_1      0x00000258 22  w  0x00000000 -             wINT_STAT     1 -                      "Interrupt Status (GPIO Bank1, MIO)"
    INT_TYPE_1      0x0000025C 22 rw  0x003FFFFF rINT_TYPE     wINT_TYPE     1 -                      "Interrupt Type (GPIO Bank1, MIO)"
    INT_POLARITY_1  0x00000260 22 rw  0x00000000 rINT_POLARITY wINT_POLARITY 1 -                      "Interrupt Polarity (GPIO Bank1, MIO)"
    INT_ANY_1       0x00000264 22 rw  0x00000000 rINT_ANY      wINT_ANY      1 -                      "Interrupt Any Edge Sensitive (GPIO Bank1, MIO)"
    DIRM_2          0x00000284 32 rw  0x00000000 rDIRM         wDIRM         2 -                      "Direction mode (GPIO Bank2, EMIO)"
    OEN_2           0x00000288 32 rw  0x00000000 rOEN          wOEN          2 -                      "Output enable (GPIO Bank2, EMIO)"
    INT_MASK_2      0x0000028C 32 r   0x00000000 rINT_MASK     -             2 -                      "Interrupt Mask Status (GPIO Bank2, EMIO)"
    INT_EN_2        0x00000290 32  w  0x00000000 -             wINT_EN       2 -                      "Interrupt Enable/Unmask (GPIO Bank2, EMIO)"
    INT_DIS_2       0x00000294 32  w  0x00000000 -             wINT_DIS      2 -                      "Interrupt Disable/Mask (GPIO Bank2, EMIO)"
    INT_STAT_2      0x00000298 32  w  0x00000000 -             wINT_STAT     2 -                      "Interrupt Status (GPIO Bank2, EMIO)"
    INT_TYPE_2      0x0000029C 32 rw  0xFFFFFFFF rINT_TYPE     wINT_TYPE     2 -                      "Interrupt Type (GPIO Bank2, EMIO)"
    INT_POLARITY_2  0x000002A0 32 rw  0x00000000 rINT_POLARITY wINT_POLARITY 2 -                      "Interrupt Polarity (GPIO Bank2, EMIO)"
    INT_ANY_2       0x000002A4 32 rw  0x00000000 rINT_ANY      wINT_ANY      2 -                      "Interrupt Any Edge Sensitive (GPIO Bank2, EMIO)"
    DIRM_3          0x000002C4 32 rw  0x00000000 rDIRM         wDIRM         3 -                      "Direction mode (GPIO Bank3, EMIO)"
    OEN_3           0x000002C8 32 rw  0x00000000 rOEN          wOEN          3 -                      "Output enable (GPIO Bank3, EMIO)"
    INT_MASK_3      0x000002CC 32 r   0x00000000 rINT_MASK     -             3 -                      "Interrupt Mask Status (GPIO Bank3, EMIO)"
    INT_EN_3        0x000002D0 32  w  0x00000000 -             wINT_EN       3 -                      "Interrupt Enable/Unmask (GPIO Bank3, EMIO)"
    INT_DIS_3       0x000002D4 32  w  0x00000000 -             wINT_DIS      3 -                      "Interrupt Disable/Mask (GPIO Bank3, EMIO)"
    INT_STAT_3      0x000002D8 32  w  0x00000000 -             wINT_STAT     3 -                      "Interrupt Status (GPIO Bank3, EMIO)"
    INT_TYPE_3      0x000002DC 32 rw  0xFFFFFFFF rINT_TYPE     wINT_TYPE     3 -                      "Interrupt Type (GPIO Bank3, EMIO)"
    INT_POLARITY_3  0x000002E0 32 rw  0x00000000 rINT_POLARITY wINT_POLARITY 3 -                      "Interrupt Polarity (GPIO Bank3, EMIO)"
    INT_ANY_3       0x000002E4 32 rw  0x00000000 rINT_ANY      wINT_ANY      3 -                      "Interrupt Any Edge Sensitive (GPIO Bank3, EMIO)"
                                
}

# the following registers are removed from above and implemented using memory and updated when changes to input pins (no overhead when reading)
#    DATA_0_RO       0x00000060 32 r   0x00000000 rDATARO       -             0 -                      "Input Data (GPIO Bank0, MIO)"
#    DATA_1_RO       0x00000064 22 r   0x00000000 rDATARO       -             1 -                      "Input Data (GPIO Bank1, MIO)"
#    DATA_2_RO       0x00000068 32 r   0x00000000 rDATARO       -             2 -                      "Input Data (GPIO Bank2, EMIO)"
#    DATA_3_RO       0x0000006C 32 r   0x00000000 rDATARO       -             3 -                      "Input Data (GPIO Bank3, EMIO)"
imodeladdlocalmemory -name DATA_0_RO -addressblock $PORT/$AB -size 4 -offset 0x00000060 
imodeladdlocalmemory -name DATA_1_RO -addressblock $PORT/$AB -size 4 -offset 0x00000064 
imodeladdlocalmemory -name DATA_2_RO -addressblock $PORT/$AB -size 4 -offset 0x00000068 
imodeladdlocalmemory -name DATA_3_RO -addressblock $PORT/$AB -size 4 -offset 0x0000006C 

foreach {rname roffset rsize raccess reset readFunc writeFunc user bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      set rsize 32
  }

  set command "imodeladdmmregister -addressblock $PORT/$AB -name $rname -width 32 -offset $roffset -access $raccess"
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

  if { $user != "-" } {
    set command "${command} -userdata $user"
  }
  
  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle $PORT/$AB/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w } $bits {
      imodeladdfield -mmregister $PORT/$AB/$rname -bitoffset $o -width $w -name $n
    }
  }
  
  imodeladdreset -mmregister $PORT/$AB/$rname -name resetNet -value $reset
}

# interrupt output
imodeladdnetport -type output -name interrupt

# GPIO Ports
imodeladdnetport -type input  -name gpio_bank0_in  \
                 -updatefunction gpio_in_change    \
		 -updatefunctionargument 0
imodeladdnetport -type output -name gpio_bank0_out
imodeladdnetport -type input  -name gpio_bank1_in  \
                 -updatefunction gpio_in_change    \
		 -updatefunctionargument 1
imodeladdnetport -type output -name gpio_bank1_out
imodeladdnetport -type input  -name gpio_bank2_in  \
                 -updatefunction gpio_in_change    \
		 -updatefunctionargument 2
imodeladdnetport -type output -name gpio_bank2_out
imodeladdnetport -type output -name gpio_bank2_oen_out
imodeladdnetport -type input  -name gpio_bank3_in  \
                 -updatefunction gpio_in_change    \
		 -updatefunctionargument 3
imodeladdnetport -type output -name gpio_bank3_out
imodeladdnetport -type output -name gpio_bank3_oen_out

# Configuration for test and debug output
imodeladdformal -name config -type enum -defaultvalue zc702
iadddocumentation -name Description -text "LED/Switch Board Configuration (zc702/zc706)"
  imodeladdenumeration -formal config -name zc702
  imodeladdenumeration -formal config -name zc706

imodeladdformal -name swtest -type Bool -defaultvalue 0
iadddocumentation -name Description -text "Enable Switch and LED Test pattern generation"

imodeladdnetport -name intOut -type output
iadddocumentation -name Description -text "Interrupt signal"
 
