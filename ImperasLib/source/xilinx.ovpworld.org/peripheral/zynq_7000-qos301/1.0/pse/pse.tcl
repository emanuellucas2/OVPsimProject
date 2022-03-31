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
set name    zynq_7000-qos301
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Platform Interconnect QoS (qos301)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers. There is no behavior included."

iadddocumentation \
    -name Reference \
    -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

#   rname roffset rsize raccess reset readFunc writeFunc writeMask bits description
set registers {
qos_cntl    0x0000010C 32 rw 0x00000000 -    -    -    -  "The QoS control register contains the enable bits for all the regulators."
max_ot      0x00000110 32 rw 0x00000000 -    -    -    -  "Maximum number of outstanding transactions"
max_comb_ot 0x00000114 32 rw 0x00000000 -    -    -    -  "Maximum number of combined outstanding transactions"
aw_p        0x00000118 32 rw 0x00000000 -    -    -    -  "AW channel peak rate"
aw_b        0x0000011C 32 rw 0x00000000 -    -    -    -  "AW channel burstiness allowance"
aw_r        0x00000120 32 rw 0x00000000 -    -    -    -  "AW channel average rate"
ar_p        0x00000124 32 rw 0x00000000 -    -    -    -  "AR channel peak rate"
ar_b        0x00000128 32 rw 0x00000000 -    -    -    -  "AR channel burstiness allowance"
ar_r        0x0000012C 32 rw 0x00000000 -    -    -    -  "AR channel average rate"

}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {($raccess != "rw") || ($raccess != "w") || ($raccess != "r")} {
    set raccess "rw"
  }
  if {$reset == "x"} {
    set reset 0x00000000
  }
  if {$rsize != "32"} {
      set rsize 32
#      puts"Register $rname is not 32-bits ignored"
#      continue
  }

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
 
