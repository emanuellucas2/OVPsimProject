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
set name    spi
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  -name Description -text "SiFive coreip-s51-arty SPI Registers and Memory (spi)"

iadddocumentation -name Licensing    -text "Open Source Apache 2.0"
    
iadddocumentation -name Limitations  -text "This model implements only the registers and memory. It contains no SPI behaviour."
    
iadddocumentation -name Reference    -text "SiFive Freedom E SDK coreip-s51-arty Board Support Package details."

set MPORT    mport1
set MAB      MEM
set MAB_SIZE 0x20000000
set MNAME    mem
set mwidth   32

imodeladdbusslaveport  -name $MPORT -size $MAB_SIZE -mustbeconnected 
imodeladdaddressblock  -name $MAB   -size $MAB_SIZE -port $MPORT -offset 0 -width ${mwidth}
imodeladdlocalmemory   -name $MNAME -size $MAB_SIZE -addressblock $MPORT/$MAB

set PORT    bport1
set AB      REG
set AB_SIZE 0x1000
set width   32

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE -defaultfunctions
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width ${width}

#   name    offset size access reset       readFunc writeFunc  writeMask  description                    bits
set registers {
    sckdiv  0x000  32   rw     0x00000003  -        wrSckdiv   0x00000fff "Serial clock divisor"          
    {
        scale 0 12 "Divisor for serial clock"
    }
    sckmode 0x004  32   rw     0x00000000  -        wrSckmode  0x00000003 "Serial clock mode"             
    {
        pha 0 1 "Serial clock phase"
        pol 1 1 "Serial clock polarity"
    }
    csid    0x010  32   rw     0x00000000  -        -          -          "Chip select ID"                -
    csdef   0x014  32   rw     0x00000001  -        -          -          "Chip select default"           -
    csmode  0x018  32   rw     0x00000000  -        wrCsmode   0x00000003 "Chip select mode"              
    {
        mode 0 2 ""
    }
    delay0  0x028  32   rw     0x00000000  -        -          -         "Delay control 0"               
    {
        cssck  0 8 "CS to SCK Delay"
        sckcs 16 8 "SCK to CS Delay"
    }
    delay1  0x02C  32   rw     0x00000000  -        -          -         "Delay control 1"
    {
        intercs   0 8 "Minimum CS inactive time"
        interxfr 16 8 "Maximum interframe delay"
    }
    fmt     0x040  32   rw     0x00080008  -        -          -         "Frame format"
    {
        proto  0 2 "SPI Protocol"
        endian 2 1 "SPI endinanness"
        dir    3 1 "SPI I/O Direction"
        len   16 4 "Number of bits per frame"
    }
    txdata  0x048  32   rw     0x00000000  rdTx     wrTx       0x000000ff "Tx FIFO data"
    {
        data  0 8 "Transmit data"
        full 31 1 "FIFO full flag"
    }
    rxdata  0x04C  32   r      0x00000000  rdRx     -          -         "Rx FIFO data"
    {
        data  0 8 "Received data"
        empty 31 1 "FIFO empty flag"
    }
    txmark  0x050  32   rw     0x00000001  -        wrTxMark   0x00000003 "Tx FIFO watermark"
    {
        txmark 0 3 "Transmit watermark"
    }
    rxmark  0x054  32   rw     0x00000001  -        wrRxMark   0x00000003 "Rx FIFO watermark"
    {
        rxmark 0 3 "receive watermark"
    }
    fctrl   0x060  32   rw     0x00000001  -        -          -         "SPI flash interface control"
    {
        en 0 1 "SPI Flash Mode Select"
    }
    ffmt    0x064  32   rw     0x00030007  -        -          -         "SPI flash instruction format"
    {
        cmd_en      0 1 "Enable sending of command"
        addr_len    1 3 "Number of address bytes(0 to 4)"
        pad_cnt     4 4 "Number of dummy cycles"
        cmd_proto   8 2 "Protocol for transmitting command"
        addr_proto 10 2 "Protocol for transmitting address and padding"
        data_proto 12 2 "Protocol for receiving data bytes"
        cmd_code   16 8 "Value of command byte"
        pad_code   24 8 "First 8 bits to transmit during dummy cycles"
    }
    ie      0x070  32   r     0x00000000   -        -          -         "SPI interrupt enable"
    {
        txwm  0 1 "Transmit watermark enable"
        rxwm  1 1 "Receive watermark enable"
    }
    ip      0x074  32   r     0x00000000   -        -          -         "SPI interrupt pending"
    {
        txwm  0 1 "Transmit watermark pending"
        rxwm  1 1 "Receive watermark pending"
    }
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "${width}"} {
      set rsize ${width}
  }

#  puts "# $rname $roffset $rsize $raccess $reset $readFunc $writeFunc $writeMask $description $bits"

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

  if { $writeMask == "-" } {
    set defaultcb 1
  } else {
    set command "${command} -writemask $writeMask"
  }
  
  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle $PORT/$AB/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w d } $bits {
      imodeladdfield -mmregister $PORT/$AB/$rname -bitoffset $o -width $w -name $n
      if { $d != "-" } {
          iadddocumentation  -handle $PORT/$AB/$rname \
                             -name Description  \
                             -text $d
      }
    }
  }
  
  imodeladdreset -mmregister $PORT/$AB/$rname -name resetNet -value $reset
}

# reset input
imodeladdnetport -type input -name resetNet -updatefunction resetCB

