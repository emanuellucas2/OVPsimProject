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
set name    iMX6_GPIO
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "NXP i.MX6 GPIO"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

set limitations "No behaviour is implemented."
iadddocumentation -name Limitations -text $limitations

iadddocumentation \
    -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

set port  bport1
set block ab
set size  0x4000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

# define a general function if an access to an area in which there is no register defined
imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
  DR        0x00    rw  0x00000000 -  -    -    "GPIO Data Register"                      -
  GDIR      0x04    rw  0x00000000 -  -    -    "GPIO Direction Register"                 -
  PSR       0x08     r  0x00000000 -  -    -    "GPIO PAD Status Register"                -
  ICR1      0x0c    rw  0x00000000 -  -    -    "GPIO interrupt configuration register1"  -
  ICR2      0x10    rw  0x00000000 -  -    -    "GPIO interrupt configuration register2"  -
  IMR1      0x14    rw  0x00000000 -  -    -    "GPIO interrupt mask register"            -
  ISR       0x18    rw  0x00000000 -  -    -    "GPIO interrupt status register"          -
  EDGE_SEL  0x1c    rw  0x00000000 -  -    -    "GPIO edge select register"               -
}

foreach {rname roffset raccess reset writeMask readFunc writeFunc description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

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
    foreach { n o w d } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        if { $d != "-" } {
            iadddocumentation  -handle ${port}/${block}/$rname -name Description -text $d
        }
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}
