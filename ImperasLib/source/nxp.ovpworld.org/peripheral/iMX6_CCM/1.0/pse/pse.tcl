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
set name    iMX6_CCM
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "NXP i.MX6 CCM Clock Controller Module"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

set limitations "
This is a register only interface model. No functionality is implemented.
The reset value for the CCM_CSCDR2 epdc_pix_clk_sel field (bits 11:9) has been modified from the documented value. The documented value (0x5) is reserved and causes a Linux Kernel Panic
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

#   rname           roffset rsize raccess reset      mask       readF writeF description              bits 
set registers {
    CCM_CCR         0x000   32    rw      0x040116FF -          -     -      "CCM Control Register"                                       -
    CCM_CCDR        0x004   32    rw      0x00000000 -          -     -      "CCM Control Divider Register"                               -
    CCM_CSR         0x008   32    r       0x00000010 -          -     -      "CCM Status Register"                                        -
    CCM_CCSR        0x00c   32    rw      0x00000100 -          -     -      "CCM Clock Switcher Register"                                -
    CCM_CACRR       0x010   32    rw      0x00000000 -          -     -      "CCM Arm Clock Root Register"                                -
    CCM_CBCDR       0x014   32    rw      0x00018D00 -          -     -      "CCM Bus Clock Divider Register"                             -
    CCM_CBCMR       0x018   32    rw      0x00820324 -          -     -      "CCM Bus Clock Multiplexer Register"                         -
    CCM_CSCMR1      0x01c   32    rw      0x00F00000 -          -     -      "CCM Serial Clock Multiplexer Register 1"                    -
    CCM_CSCMR2      0x020   32    rw      0x00F00000 -          -     -      "CCM Serial Clock Multiplexer Register 2"                    -
    CCM_CSCDR1      0x024   32    rw      0x00490B00 -          -     -      "CCM Serial Clock Divider Register 1"                        -
    CCM_CS1CDR      0x028   32    rw      0x0EC102C1 -          -     -      "CCM SSI1 Clock Divider Register"                            -
    CCM_CS2CDR      0x02c   32    rw      0x000736C1 -          -     -      "CCM SSI2 Clock Divider Register"                            -
    CCM_CDCDR       0x030   32    rw      0x33F71F92 -          -     -      "CCM D1 Clock Divider Register"                              -
    CCM_CHSCCDR     0x034   32    rw      0x0002A150 -          -     -      "CCM HSC Clock Divider Register"                             -
    CCM_CSCDR2      0x038   32    rw      0x00029948 -          -     -      "CCM Serial Clock Divider Register 2 (modified reset value)" -
    CCM_CSCDR3      0x03c   32    rw      0x00010841 -          -     -      "CCM Serial Clock Divider Register 3"                        -
    CCM_CDHIPR      0x048   32    r       0x00000000 -          -     -      "CCM Divider Handshake In-Process Register"                  -
    CCM_CLPCR       0x054   32    rw      0x00000079 -          -     -      "CCM Low Power Control Register"                             -
    CCM_CISR        0x058   32    rw      0x00000000 -          -     -      "CCM Interrupt Status Register"                              -
    CCM_CIMR        0x05c   32    rw      0xFFFFFFFF -          -     -      "CCM Interrupt Mask Register"                                -
    CCM_CCOSR       0x060   32    rw      0x000A0001 -          -     -      "CCM Clock Output Source Register"                           -
    CCM_CGPR        0x064   32    rw      0x0000FE62 -          -     -      "CCM General Purpose Register"                               -
    CCM_CCGR0       0x068   32    rw      0xFFFFFFFF -          -     -      "CCM Clock Gating Register 0"                                -
    CCM_CCGR1       0x06c   32    rw      0xFFFFFFFF -          -     -      "CCM Clock Gating Register 1"                                -
    CCM_CCGR2       0x070   32    rw      0xFC3FFFFF -          -     -      "CCM Clock Gating Register 2"                                -
    CCM_CCGR3       0x074   32    rw      0xFFFFFFFF -          -     -      "CCM Clock Gating Register 3"                                -
    CCM_CCGR4       0x078   32    rw      0xFFFFFFFF -          -     -      "CCM Clock Gating Register 4"                                -
    CCM_CCGR5       0x07c   32    rw      0xFFFFFFFF -          -     -      "CCM Clock Gating Register 5"                                -
    CCM_CCGR6       0x080   32    rw      0xFFFFFFFF -          -     -      "CCM Clock Gating Register 6"                                -
    CCM_CMEOR       0x088   32    rw      0xFFFFFFFF -          -     -      "CCM Module Enable Overide Register"                         -
}

foreach {rname roffset rsize raccess reset mask readFunc writeFunc description bits} $registers {
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
