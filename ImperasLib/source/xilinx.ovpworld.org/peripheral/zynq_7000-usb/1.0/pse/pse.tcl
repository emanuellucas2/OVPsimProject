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
set name    zynq_7000-usb
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 USB Registers"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers but no behavior."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

# rname roffset rsize raccess reset readFunc writeFunc writeMask bits description
set registers {
    ID                                 0x00000000 32 r     0xE441FA05 -    -    -    -   "IP version and revision, read-only"
    HWGENERAL                          0x00000004 12 r     0x00000083 -    -    -    -   "Misc IP config constants, read-only"
    HWHOST                             0x00000008 32 r     0x10020001 -    -    -    -   "Host Mode IP config constants, read-only"
    HWDEVICE                           0x0000000C  6 r     0x00000019 -    -    -    -   "Device Mode IP config constants, read-only"
    HWTXBUF                            0x00000010 32 r     0x80060A10 -    -    -    -   "TxBuffer IP config constants, read-only"
    HWRXBUF                            0x00000014 32 r     0x00000A10 -    -    -    -   "IP constants, RX buffer constants, read-only"
    GPTIMER0LD                         0x00000080 24 rw    0x00000000 -    -    -    -   "GP Timer 0 Load Value"
    GPTIMER0CTRL                       0x00000084 32 rw    0x00000000 -    -    -    -   "GP Timer 1 Control"
    GPTIMER1LD                         0x00000088 24 rw    0x00000000 -    -    -    -   "GP Timer 1 Load Value"
    GPTIMER1CTRL                       0x0000008C 32 rw    0x00000000 -    -    -    -   "GP Timer 1 Control"
    SBUSCFG                            0x00000090  3 rw    0x00000003 -    -    -    -   "DMA Master AHB Burst Mode "
    CAPLENGTH_HCIVERSION               0x00000100 32 r     0x01000040 -    -    -    -   "EHCI Addr Space and HCI constants, read-only"
    HCSPARAMS                          0x00000104 28 r     0x00010011 -    -    -    -   "TT counts and EHCI HCS constants, read-only"
    HCCPARAMS                          0x00000108 16 r     0x00000006 -    -    -    -   "EHCI Host configuration constants"
    DCIVERSION                         0x00000120 16 r     0x00000001 -    -    -    -   "Device Mode CI version constant"
    DCCPARAMS                          0x00000124  9 r     0x0000018C -    -    -    -   "EHCI, device and endpoint capabilities"
    USBCMD                             0x00000140 24 rw    0x00080000 -    -    -    -   "USB Commands (EHCI extended)"
    USBSTS                             0x00000144 26 rw    0x00000000 -    -    -    -   "Interrupt/Raw Status (EHCI extended) (Host/Device)"
    USBINTR                            0x00000148 26 rw    0x00000000 -    -    -    -   "Interrrupts and Enables"
    FRINDEX                            0x0000014C 14 rw    0x00000000 -    -    -    -   "Frame List Index"
    PERIODICLISTBASE_DEVICEADDR        0x00000154 32 rw    0x00000000 -    -    -    -   "Host/Device Address dual-use"
    ASYNCLISTADDR_ENDPOINTLISTADDR     0x00000158 32 rw    0x00000000 -    -    -    -   "Host/Device dual-use"
    TTCTRL                             0x0000015C 32 rw    0x00000000 -    -    -    -   "TT Control"
    BURSTSIZE                          0x00000160 17 rw    0x00001010 -    -    -    -   "Burst Size"
    TXFILLTUNING                       0x00000164 22 rw    0x00000000 -    -    -    -   "TxFIFO Fill Tuning"
    TXTTFILLTUNING                     0x00000168 13 rw    0x00000000 -    -    -    -   "TT TX latency FIFO"
    IC_USB                             0x0000016C 32 rw    0x00000000 -    -    -    -   "Low and Fast Speed Control constants"
    ULPI_VIEWPORT                      0x00000170 32 rw    0x08000000 -    wrVP -    -   "ULPI Viewport"
    ENDPTNAK                           0x00000178 32 w     0x00000000 -    -    -    -   "Endpoint NAK (Device mode)"
    ENDPTNAKEN                         0x0000017C 32 rw    0x00000000 -    -    -    -   "Endpoint NAK (Device mode)"
    CONFIGFLAG                         0x00000180 32 r     0x00000001 -    -    -    -   "reserved"
    PORTSC1                            0x00000184 32 rw    0x8C000004 -    -    -    -   "Port Status & Control"
    OTGSC                              0x000001A4 32 rw    0x00001020 -    -    -    -   "OTG Status and Control"
    USBMODE                            0x000001A8 32 rw    0x00000000 -    -    -    -   "USB Mode Selection"
    ENDPTSETUPSTAT                     0x000001AC 16  w    0x00000000 -    -    -    -   "Endpoint Status Setup (Device mode)"
    ENDPTPRIME                         0x000001B0 32  w    0x00000000 -    -    -    -   "Endpoint Primer (Device mode)"
    ENDPTFLUSH                         0x000001B4 32  w    0x00000000 -    -    -    -   "Endpoint Flush (Device mode)"
    ENDPTSTAT                          0x000001B8 32 r     0x00000000 -    -    -    -   "Endpoint Buffer Ready Status (Device mode), RO"
    ENDPTCOMPLETE                      0x000001BC 32 rw    0x00000000 -    -    -    -   "Endpoint Tx Complete (Device mode)"
    ENDPTCTRL0                         0x000001C0 24 rw    0x00800080 -    -    -    -   "Endpoint 0 (Device mode)"
    ENDPTCTRL1                         0x000001C4 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL2                         0x000001C8 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL3                         0x000001CC 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL4                         0x000001D0 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL5                         0x000001D4 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"    
    ENDPTCTRL6                         0x000001D8 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL7                         0x000001DC 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL8                         0x000001E0 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL9                         0x000001E4 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL10                        0x000001E8 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"
    ENDPTCTRL11                        0x000001EC 24 rw    0x00000000 -    -    -    -   "Endpoints 1 to 11 (Device mode)"

}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  # 32 bit registers
  if {$rsize != 32} {set rsize 32}

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

imodeladdnetport -name intOut -type output
 
