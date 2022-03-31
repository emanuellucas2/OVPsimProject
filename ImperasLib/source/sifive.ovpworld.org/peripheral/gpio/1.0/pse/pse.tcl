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

set vendor  sifive.ovpworld.org
set library peripheral
set name    gpio
set version 1.0

imodelnewperipheral -imagefile pse.pse \
    -vendor  $vendor \
    -library $library \
    -name    $name \
    -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "SiFive coreip-s51-arty GPIO Registers (gpio)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements only the registers for generation of input or output data values."

iadddocumentation -name Reference    -text "SiFive Freedom E SDK coreip-s51-arty Board Support Package details."

set PORT    bport1
set AB      REG
set AB_SIZE 0x1000
set width   32

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE -defaultfunctions
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width ${width}

#   name          offset size access reset       readFunc writeFunc  bits                   description
set registers {
    VALUE          0     32   rw     0x00000000  -        -          -                      "Pin Value"
    INPUT_EN       4     32   rw     0x00000000  -        wrInputEn  -                      "Enable Input bits"
    OUTPUT_EN      8     32   rw     0x00000000  -        wrOutputEn -                      "Enable Output bits"
    PORT          12     32   rw     0x00000000  -        wrPort     -                      "Output Port Value"
    PUE           16     32   rw     0x00000000  -        -          -                      "Internal pull-up enabled"
    DS            20     32   rw     0x00000000  -        -          -                      "Pin Drive Strength"
    RISE_IE       24     32   rw     0x00000000  -        wrRIE      -                      "Rising edge interupt enable"
    RISE_IP       28     32   rw     0x00000000  -        -          -                      "Rising interrupt pending"
    FALL_IE       32     32   rw     0x00000000  -        wrFIE      -                      "Falling edge interupt enable"
    FALL_IP       36     32   rw     0x00000000  -        -          -                      "Falling interrupt pending"
    HIGH_IE       40     32   rw     0x00000000  -        wrHIE      -                      "High level edge interupt enable"
    HIGH_IP       44     32   rw     0x00000000  -        -          -                      "High level interrupt pending"
    LOW_IE        48     32   rw     0x00000000  -        wrLIE      -                      "Low level interupt enable"
    LOW_IP        52     32   rw     0x00000000  -        -          -                      "Low level interrupt pending"
    IOF_EN        56     32   rw     0x00000000  -        -          -                      "H/W I/O Function enable"
    IOF_SEL       60     32   rw     0x00000000  -        -          -                      "H/W I/O Function Select"
    OUT_XOR       64     32   rw     0x00000000  -        -          -                      "Output XOR (invert)"
}

foreach {rname roffset rsize raccess reset readFunc writeFunc bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "${width}"} {
      set rsize ${width}
  }

  set command "imodeladdmmregister -addressblock $PORT/$AB -name $rname -width ${width} -offset $roffset -access $raccess"
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

# reset input
imodeladdnetport -type input -name resetNet -updatefunction resetCB


# interrupt outputs (16)
for {set i 0} {$i < 16} {incr i} {
  imodeladdnetport -type output -name intOut${i}
}

# GPIO connections
for {set i 0} {$i < 16} {incr i} {
  imodeladdnetport -type inout  -name gpios${i} -updatefunction gpioInCB -updatefunctionargument $i
}
#
# Formal attributes (visualization)
#
imodeladdformalmacro -name BHM_HTTP_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
