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
set name    iMX6_GPC
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation -name Description -text "NXP i.MX6 GPC General Power Controller"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations \
                  -text "This is a register only model"

iadddocumentation -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

#
# slave port
#
set port  bport1
set block ab
set size  0x260
set width 32

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width $width

# define a general function if an access to an area in which there is no register defined
imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

#
# Registers
#
set registers {
    
    GPC_CNTR  0x00 rw 0x00100000 0x00200003   -   auto "GPC Interface control register"
    {   GPCIRQM 21 1 "GPC interrupt/event masking" 
        VPU_PUP  1 1 "GPU/VPU Power Up request"
        VPU_PDN  0 1 "GPU/VPU Power Down request" 
    }
    GPC_PGR   0x04 rw 0x00000000 0x60000000   -   -    "GPC Power Gating Register"      {DRCIC 29 2}
    GPC_IMR1  0x08 rw 0x00000000 0x00000000   -   -    "IRQ masking register 1"         -
    GPC_IMR2  0x0C rw 0x00000000 0x00000000   -   -    "IRQ masking register 2"         -
    GPC_IMR3  0x10 rw 0x00000000 0x00000000   -   -    "IRQ masking register 3"         -
    GPC_IMR4  0x14 rw 0x00000000 0x00000000   -   -    "IRQ masking register 4"         -
    GPC_ISR1  0x18 r  0x00000000 -            -   -    "IRQ status resister 1"          -
    GPC_ISR2  0x1C r  0x00000000 -            -   -    "IRQ status resister 2"          -
    GPC_ISR3  0x20 r  0x00000000 -            -   -    "IRQ status resister 3"          -
    GPC_ISR4  0x24 r  0x00000000 -            -   -    "IRQ status resister 4"          -
}

foreach {rname roffset raccess reset writeMask readFunc writeFunc description bits} $registers {

  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock $port/$block -name $rname -width $width -offset $roffset -access $raccess"
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

# monitors the status of all interrupts
for {set i 32} {$i <= 159 } {incr i} {
    imodeladdnetport -name irq$i -type input -updatefunction interruptIn -updatefunctionargument $i
}