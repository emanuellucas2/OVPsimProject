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
set name    iMX6_WDOG
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor  \
    -releasestatus ovp

iadddocumentation -name Description -text "iMX6 WDOG"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This is an incomplete model of the WDOG."
iadddocumentation -name Limitations -text "It has basic functionality to support the iMX6 platform."

iadddocumentation -name Reference \
                  -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

set port  bport1
set block ab
set size  0x4000
set width 16
imodeladdbusslaveport  -name $port -mustbeconnected -size $size
imodeladdaddressblock  -name $block -port $port -size $size -offset 0 -width $width

imodeladdlocalmemory -name buffer -addressblock $port/$block -size $size \
                     -writefunction regNoDefinitionRead -readfunction regNoDefinitionWrite

set registers {
    WDOG_WCR   0x00  16 rw 0x0030 -     -    auto "Watchdog Control Register"
        {   WT      8 8 "Watchdog Time-out Field (0.5 to 128 seconds)"
            WDW     7 1 "Watchdog Disable for Wait"
            SRE     6 1 "Software reset extension, an option way to generate software reset"
            WDA     5 1 "WDOG_B assertion. Controls the software assertion of the WDOG_B signal"
            SRS     4 1 "Software Reset Signal. Controls the software assertion of the WDOG-generated reset signal WDOG_RESET_B_DEB"
            WDT     3 1 "WDOG_B Time-out assertion. Determines if the WDOG_B gets asserted upon a Watchdog Time-out Event"
            WDE     2 1 "Watchdog Enable. Enables or disables the WDOG block"
            WDBG    1 1 "Watchdog DEBUG Enable. Determines the operation of the WDOG during DEBUG mode"
            WDZST   0 1 "Watchdog Low Power. Determines the operation of the WDOG during low-power modes"
        }
    WDOG_WSR   0x02  16 rw 0x0000 -     -    auto "Watchdog Service Register"                -
    WDOG_WRSR  0x04  16 r  0x0000 -     -    -    "Watchdog Reset Status Register"
        {   POR  4 1 "Power On Reset. Indicates whether the reset is the result of a power on reset"
            TOUT 1 1 "Timeout. Indicates whether the reset is the result of a WDOG timeout"
            SFTW 0 1 "Software Reset. Indicates whether the reset is the result of a WDOG software reset by asserting SRS bit"
        }
    WDOG_WICR  0x06  16 rw 0x0004 0x80ff -    auto "Watchdog Interrupt Control Register"
        {   WIE     15 1 "Watchdog Timer Interrupt enable bit"
            WTIS    14 1 "Watchdog TImer Interrupt Status bit will reflect the timer interrupt status"
            WICT     0 8 "Watchdog Interrupt Count Time-out (WICT) field determines, how long before the counter time-out must the interrupt occur"
        }
    WDOG_WMCR  0x08  16 rw 0x0001 0x0001 -    auto "Watchdog Miscellaneous Control Register"
        {   PDE 0 1 "Power Down Enable bit" }
}

foreach {rname roffset rsize raccess reset maskWrite readFunc writeFunc description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != $width} {
      puts "Register $rname is not ${width}-bits ignored"
      continue
  }

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

  if { $maskWrite == "-" } {
    set defaultcb 1
  } else {
    set command "${command} -writemask $maskWrite"
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
            iadddocumentation  -handle $port/$block/$rname -name Description -text $d
        }
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}

# Watchdog timeout, used as a reset source
imodeladdnetport -name WDOG -type output
iadddocumentation  -handle WDOG -name Description -text "WDOG failure"

imodeladdnetport -name interrupt -type output
iadddocumentation  -handle interrupt -name Description -text "Interrupt line."

imodeladdnetport -name wdog_rst -type output
iadddocumentation  -handle wdog_rst -name Description -text "WDOG Reset"
