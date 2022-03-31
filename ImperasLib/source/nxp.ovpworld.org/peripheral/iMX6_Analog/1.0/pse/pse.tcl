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
set name    iMX6_Analog
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "NXP i.MX6 ANALOG: (PLLs, PFDs, Regulators, LDOs, Temp Sensor) Registers"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

set limitations "
This is a register only interface model. No functionality is implemented.
The reset values for registers have been modified from those specified in the documentation to set the lock bit (bit 31) on PLL registers.
"
iadddocumentation -name Limitations -text $limitations
    
iadddocumentation \
    -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

# define a general function if an access to an area in which there is no register defined
imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

#   rname                        roffset rsize raccess reset      mask       readF writeF macro description                                                         bits 
set registers {                                                                                                                                                          
    CCM_ANALOG_PLL_ARM               0x000   32    rw  0x80013042 -          -     -        y   "Analog ARM PLL control Register"                                   -
    CCM_ANALOG_PLL_USB1              0x010   32    rw  0x80012000 -          -     -        y   "Analog USB1 480MHz PLL Control Register"                           -
    CCM_ANALOG_PLL_USB2              0x020   32    rw  0x80012000 -          -     -        y   "Analog USB2 480MHz PLL Control Register"                           -
    CCM_ANALOG_PLL_SYS               0x030   32    rw  0x80013001 -          -     -        y   "Analog System PLL Control Register (modified reset value)"         -
    CCM_ANALOG_PLL_SYS_SS            0x040   32    rw  0x00000000 -          -     -        -   "528MHz System PLL Spread Spectrum Register"                        -
    CCM_ANALOG_PLL_SYS_SYS_NUM       0x050   32    rw  0x00000000 -          -     -        -   "Numerator of 528MHz System PLL Fractional Loop Divider Register"   -
    CCM_ANALOG_PLL_SYS_SYS_DENOM     0x060   32    rw  0x00000012 -          -     -        -   "Denominator of 528MHz System PLL Fractional Loop Divider Register" -
    CCM_ANALOG_PLL_AUDIO             0x070   32    rw  0x80011006 -          -     -        y   "Analog Audio PLL control Register"                                 -
    CCM_ANALOG_PLL_AUDIO_NUM         0x080   32    rw  0x05F5E100 -          -     -        y   "Numerator of Audio PLL Fractional Loop Divider Register"           -
    CCM_ANALOG_PLL_AUDIO_DENOM       0x090   32    rw  0x2964619C -          -     -        y   "Denominator of Audio PLL Fractional Loop Divider Register"         -
    CCM_ANALOG_PLL_VIDEO             0x0a0   32    rw  0x8001100C -          -     -        y   "Analog Video PLL control Register"                                 -
    CCM_ANALOG_PLL_VIDEO_NUM         0x0b0   32    rw  0x05F5E100 -          -     -        y   "Numerator of Video PLL Fractional Loop Divider Register"           -
    CCM_ANALOG_PLL_VIDEO_DENOM       0x0c0   32    rw  0x10A24447 -          -     -        y   "Denominator of Video PLL Fractional Loop Divider Register"         -
    CCM_ANALOG_PLL_MLB               0x0d0   32    rw  0x80010000 -          -     -        y   "Analog MLB PLL Control Register"                                   -
    CCM_ANALOG_PLL_ENET              0x0e0   32    rw  0x80011001 -          -     -        y   "Analog ENET PLL Control Register"                                  -
    CCM_ANALOG_PFD_480               0x0f0   32    rw  0x1311100C -          -     -        y   "480MHz Clock (PLL3) Phase Fractional Divider Control Register"     -
    CCM_ANALOG_PFD_528               0x100   32    rw  0x1018101B -          -     -        y   "528MHz Clock (PLL2) Phase Fractional Divider Control Register"     -
    PMU_REG_1P1                      0x110   32    rw  0x00001073 -          -     -        y   "Regulator 1P1 Register"                                            -
    PMU_REG_3P0                      0x120   32    rw  0x00000f74 -          -     -        y   "Regulator 3P0 Register"                                            -
    PMU_REG_2P5                      0x130   32    rw  0x00005071 -          -     -        y   "Regulator 2P5 Register"                                            -
    PMU_REG_CORE                     0x140   32    rw  0x00402010 -          -     -        y   "Digital Regulator Core Registerr"                                  -
    MISC0                            0x150   32    rw  0x04000000 -          -     -        y   "Miscellaneous Register 0"                                          -
    MISC1                            0x160   32    rw  0x00000000 -          -     -        y   "Miscellaneous Register 1"                                          -
    MISC2                            0x170   32    rw  0x00272727 -          -     -        y   "Miscellaneous Register 2"                                          -
    USB_ANALOG_USB1_VBUS_DETECT      0x1a0   32    rw  0x00100004 -          -     -        y   "USB VBUS Detect Register"                                          -
    USB_ANALOG_USB1_CHRG_DETECT      0x1b0   32    rw  0x00000000 -          -     -        y   "USB Charger Detect Register"                                       -
    USB_ANALOG_USB1_VBUS_DETECT_STAT 0x1c0   32    r   0x00000000 -          -     -        -   "USB VBUS Detect Status Register"                                   -
    USB_ANALOG_USB1_CHRG_DETECT_STAT 0x1d0   32    r   0x00000000 -          -     -        -   "USB Charger Detect Status Register"                                -
    USB_ANALOG_USB1_MISC             0x1f0   32    rw  0x00000002 -          -     -        y   "USB Misc Register"                                                 -
    USB_ANALOG_USB2_VBUS_DETECT      0x200   32    rw  0x00100004 -          -     -        y   "USB VBUS Detect Register"                                          -
    USB_ANALOG_USB2_CHRG_DETECT      0x210   32    rw  0x00000000 -          -     -        y   "USB Charger Detect Register"                                       -
    USB_ANALOG_USB2_VBUS_DETECT_STAT 0x220   32    r   0x00000000 -          -     -        -   "USB VBUS Detect Status Register"                                   -
    USB_ANALOG_USB2_CHRG_DETECT_STAT 0x230   32    r   0x00000000 -          -     -        -   "USB Charger Detect Status Register"                                -
    USB_ANALOG_USB2_MISC             0x250   32    rw  0x00000002 -          -     -        y   "USB Misc Register"                                                 -
    USB_ANALOG_DIGPROG               0x260   32    r   0x00610000 -          -     -        y   "Chip Silicon Version (modified reset value)"                       -
}

foreach {rname roffset rsize raccess reset mask readFunc writeFunc macro description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      set rsize 32
#      puts "Register $rname is not 32-bits ignored"
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

  if { $mask != "-" } {
    set command "${command} -writemask $mask"
  }

  eval $command
  
  if { $macro != "-" } {
	  # Add Set/Clear/Toggle Registers (See section 1.1.5.2 Register Macro Usage in i.MX6 Reference Manual) 
	  imodeladdmmregister -addressblock ${port}/${block} -name ${rname}_SET -width 32 -offset [expr $roffset + 4]  -access rw -readfunction ReadZero -writefunction SetBits 
	  imodeladdmmregister -addressblock ${port}/${block} -name ${rname}_CLR -width 32 -offset [expr $roffset + 8]  -access rw -readfunction ReadZero -writefunction ClrBits 
	  imodeladdmmregister -addressblock ${port}/${block} -name ${rname}_TOG -width 32 -offset [expr $roffset + 12] -access rw -readfunction ReadZero -writefunction TogBits 
  }
 
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
  
  imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $reset
}
