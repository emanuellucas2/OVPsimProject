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

set range    0x1000
set regWidth 32

imodelnewperipheral  \
    -imagefile     pse.pse  \
    -name          TzpcBP147 \
    -vendor        arm.ovpworld.org  \
    -library       peripheral \
    -version       1.0 \
    -constructor   constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM BP147 TrustZone Protection Controller."
iadddocumentation -name Description -text "There are 24 output net ports (TZPCDECPROT0_0 thru TZPCDECPROT2_7) corresponding to the 24 enables defined as 3 banks of 8 enables."
iadddocumentation -name Description -text "Each net port may be used to drive a net connected to a peripheral such as the DynamicBridge which can enable/disable a BusBridge mapping under control of an input net."
iadddocumentation -name Limitations -text "none" 
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text "ARM PrimeCell Infrastructure AMBA3 TrustZone Protection Controller (BP147) Technical Overview (ARM DTO 0015)" 

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"

set registers {
  TZPCR0SIZE       0x000 rw 0x00000200  -    auto
  TZPCDECPROT0Stat 0x800 r  0x0         -    -   
  TZPCDECPROT0Set  0x804 w  -           -    auto
  TZPCDECPROT0Clr  0x808 w  -           -    auto
  TZPCDECPROT1Stat 0x80c r  0x0         -    -   
  TZPCDECPROT1Set  0x810 w  -           -    auto
  TZPCDECPROT1Clr  0x814 w  -           -    auto
  TZPCDECPROT2Stat 0x818 r  0x0         -    -   
  TZPCDECPROT2Set  0x81c w  -           -    auto
  TZPCDECPROT2Clr  0x820 w  -           -    auto
  TZPCPERIPHID0    0xFE0 r  0x00000070  -    -
  TZPCPERIPHID1    0xFE4 r  0x00000018  -    -
  TZPCPERIPHID2    0xFE8 r  0x00000004  -    -
  TZPCPERIPHID3    0xFEC r  0x00000000  -    -
  TZPCPCELLID0     0xFF0 r  0x0000000D  -    -
  TZPCPCELLID1     0xFF4 r  0x000000F0  -    -
  TZPCPCELLID2     0xFF8 r  0x00000005  -    -
  TZPCPCELLID3     0xFFC r  0x00000081  -    -
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  
  set useUserdata 0

  set command "imodeladdmmregister -addressblock $addBlock -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
    set useUserdata 1
  } else {
    set command "${command} -readfunction $readFunc"
    set useUserdata 1
  }
  
  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
    set useUserdata 1
  } else {
    set command "${command} -writefunction $writeFunc"
    set useUserdata 1
  }
  
  eval $command

  if { $reset != "-" } {
    imodeladdreset -mmregister $addBlock/$rname -name resetNet -value $reset
  }
}

imodeladdnetport -name resetNet   -type input
imodeladdnetport -name TZPCR0SIZE -type output

set numBank 3
set perBank 16
for { set i 0 } { $i < $numBank } { incr i } {
    for { set j 0 } { $j < $perBank } { incr j } {
        imodeladdnetport -name TZPCDECPROT${i}_${j} -type output
    }
}
