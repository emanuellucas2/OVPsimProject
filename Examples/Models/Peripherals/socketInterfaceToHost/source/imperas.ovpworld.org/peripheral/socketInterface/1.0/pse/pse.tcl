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

set vendor  imperas.ovpworld.org
set library peripheral
set name    socketInterface
set version 1.0

imodelnewperipheral \
    -name $name -imagefile pse.pse \
    -library $library -vendor $vendor \
    -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Showing a simple socket interface to host program"
iadddocumentation -name Limitations -text "Under Development."
iadddocumentation -name Reference   -text "none"

set portm  mp

imodeladdbusmasterport -name ${portm}

set ports  sp
set blocks abs
set sizes  0x10

imodeladdbusslaveport  -name ${ports} -mustbeconnected -size ${sizes} -defaultfunctions
imodeladdaddressblock  -name ${blocks} -port ${ports} -size ${sizes} -offset 0 -width 32

#   rname                roffset    rsize raccess reset readFunc writeFunc writeMask description bits 
set registers {
    Control              0x00000000 32 rw 0x00000000 -         wrControl   -  "Control Register"                        {
        dmaInEn        0 1 "The DMA Address register is valid for incoming transfers"
        dmaOutEn       1 1 "The DMA Address register is valid for outgoing transfers"
        messageToSend  4 1 "There is a message in the DMA outgoing buffer to send"
        count         16 8 "The word size of the message to send"
    }
    Status               0x00000004 32 rw 0x00000000 rdStatus  wrStatus    -  "Status Register"                         {
        messageReceived 0 1 "A message is written into the DMA incoming buffer"
        messageOverflow 1 1 "Another message is received before incoming buffer available"
        messageSent     4 1 "The message in the DMA outgoing buffer was sent"
        count          16 8 "The word size of the received message"
        end            31 1 "All transfers complete"
    }
    DMAAddressIn         0x00000008 32 rw 0x00000000 -         -           -  "DMA Incoming Message Address Register"   -
    DMAAddressOut        0x0000000c 32 rw 0x00000000 -         -           -  "DMA Outgoing Message Address Register"   -
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock ${ports}/${blocks} -name $rname -width 32 -offset $roffset -access $raccess"
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
      iadddocumentation  -handle ${ports}/${blocks}/$rname -name Description -text $description
  }

  if { $bits != "-" } {
    foreach { n o w d } $bits {
        imodeladdfield -mmregister ${ports}/${blocks}/$rname -bitoffset $o -width $w -name $n
        if { $d != "-" } {
              iadddocumentation  -handle ${ports}/${blocks}/$rname/$n -name Description -text $d
        }
    }
  }

  imodeladdreset -mmregister ${ports}/${blocks}/$rname -name resetNet -value $reset
}

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

