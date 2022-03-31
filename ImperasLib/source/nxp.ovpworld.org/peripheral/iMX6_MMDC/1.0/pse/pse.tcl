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
set name    iMX6_MMDC
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation -name Description -text "NXP i.MX6 MMDC"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations \
                  -text "This is a register only model with acknowledgement of auto power saving"

iadddocumentation -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

#
# slave port
#
set port  bport1
set block ab
set size  0x4000
set width 32 

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width ${width}

# define a general function if an access to an area in which there is no register defined
imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

#
# Registers
#
set registers {
 MMDC_MDCTL         0x0000 rw 0x03110000 -         -    -    "MMDC Core Control Register"                                              -
 MMDC_MDPDC         0x0004 rw 0x00030012 -         -    -    "MMDC Core Power Down Control Register"                                   -
 MMDC_MDOTC         0x0008 rw 0x12272000 -         -    -    "MMDC Core ODT Timing Control Register"                                   -
 MMDC_MDCFG0        0x000C rw 0x323622D3 -         -    -    "MMDC Core Timing Configuration Register 0"                               -
 MMDC_MDCFG1        0x0010 rw 0xB6B18A23 -         -    -    "MMDC Core Timing Configuration Register 1"                               -
 MMDC_MDCFG2        0x0014 rw 0x00C70092 -         -    -    "MMDC Core Timing Configuration Register 2"                               -
 MMDC_MDMISC        0x0018 rw 0x00001600 -         -    -    "MMDC Core Miscellaneous Register"                                        -
 MMDC_MDSCR         0x001C rw 0x00000000 -         -    -    "MMDC Core Special Command Register"                                      -
 MMDC_MDREF         0x0020 rw 0x0000C000 -         -    -    "MMDC Core Refresh Control Register"                                      -
 MMDC_MDRWD         0x002C rw 0x0F9F26D2 -         -    -    "MMDC Core Read/Write Command Delay Register"                             -
 MMDC_MDOR          0x0030 rw 0x009F0E0E -         -    -    "MMDC Core Out of Reset Delays Register"                                  -
 MMDC_MDMRR         0x0034 r  0x00000000 -         -    -    "MMDC Core MRR Data Register"                                             -
 MMDC_MDCFG3LP      0x0038 rw 0x00000000 -         -    -    "MMDC Core Timing Configuration Register 3"                               -
 MMDC_MDMR4         0x003C rw 0x00000000 -         -    -    "MMDC Core MR4 Derating Register"                                         -
 MMDC_MDASP         0x0040 rw 0x0000003F -         -    -    "MMDC Core Address Space Partition Register"                              -
 MMDC_MAARCR        0x0400 rw 0x514201F0 -         -    -    "MMDC Core AXI Reordering Control Register"                               -
 MMDC_MAPSR         0x0404 rw 0x00001007 0x0330871 -    auto "MMDC Core Power Saving Control and Status Register"
 {   
     DVACK 25 1 "DVFS/Self-Refresh acknowledge"
     LPACK 24 1 "General low-power acknowledge"
     DVFS  21 1 "DVFS/Self-Refresh request"
     LPMD  20 1 "General LPMD request"
     PST   8  8 "Automatic Power saving timer."
     WIS   6  1 "Write Idle Status."
     RIS   5  1 "Read Idle Status"
     PSS   4  1 "Power Saving Status"
     PSD   0  1 "Automatic Power Saving Disable"
 }
 MMDC_MAEXIDR0      0x0408 rw 0x00200000 -         -    -   "MMDC Core Exclusive ID Monitor Register0"                                -
 MMDC_MAEXIDR1      0x040C rw 0x00600040 -         -    -   "MMDC Core Exclusive ID Monitor Register1"                                -
 MMDC_MADPCR0       0x0410 rw 0x00000000 -         -    -   "MMDC Core Debug and Profiling Control Register 0"                        -
 MMDC_MADPCR1       0x0414 rw 0x00000000 -         -    -   "MMDC Core Debug and Profiling Control Register 1"                        -
 MMDC_MADPSR0       0x0418 r  0x00000000 -         -    -   "MMDC Core Debug and Profiling Status Register 0"                         -
 MMDC_MADPSR1       0x041C r  0x00000000 -         -    -   "MMDC Core Debug and Profiling Status Register 1"                         -
 MMDC_MADPSR2       0x0420 r  0x00000000 -         -    -   "MMDC Core Debug and Profiling Status Register 2"                         -
 MMDC_MADPSR3       0x0424 r  0x00000000 -         -    -   "MMDC Core Debug and Profiling Status Register 3"                         -
 MMDC_MADPSR4       0x0428 r  0x00000000 -         -    -   "MMDC Core Debug and Profiling Status Register 4"                         -
 MMDC_MADPSR5       0x042C r  0x00000000 -         -    -   "MMDC Core Debug and Profiling Status Register 5"                         -
 MMDC_MASBS0        0x0430 r  0x00000000 -         -    -   "MMDC Core Step By Step Address Register"                                 -
 MMDC_MASBS1        0x0434 r  0x00000000 -         -    -   "MMDC Core Step By Step Address Attributes Register"                      -
 MMDC_MAGENP        0x0440 rw 0x00000000 -         -    -   "MMDC Core General Purpose Register"                                      -
 MMDC_MPZQHWCTRL    0x0800 rw 0xA1380000 -         -    -   "MMDC PHY ZQ HW control register"                                         -
 MMDC_MPZQSWCTRL    0x0804 rw 0x00000000 -         -    -   "MMDC PHY ZQ SW control register"                                         -
 MMDC_MPWLGCR       0x0808 rw 0x00000000 -         -    -   "MMDC PHY Write Leveling Configuration and Error Status Register"         -
 MMDC_MPWLDECTRL0   0x080C rw 0x00000000 -         -    -   "MMDC PHY Write Leveling Delay Control Register 0"                        -
 MMDC_MPWLDECTRL1   0x0810 rw 0x00000000 -         -    -   "MMDC PHY Write Leveling Delay Control Register 1"                        -
 MMDC_MPWLDLST      0x0814 r  0x00000000 -         -    -   "MMDC PHY Write Leveling delay-line Status Register"                      -
 MMDC_MPODTCTRL     0x0818 rw 0x00000000 -         -    -   "MMDC PHY ODT control register"                                           -
 MMDC_MPRDDQBY0DL   0x081C rw 0x00000000 -         -    -   "MMDC PHY Read DQ Byte0 Delay Register"                                   -
 MMDC_MPRDDQBY1DL   0x0820 rw 0x00000000 -         -    -   "MMDC PHY Read DQ Byte1 Delay Register"                                   -
 MMDC_MPRDDQBY2DL   0x0824 rw 0x00000000 -         -    -   "MMDC PHY Read DQ Byte2 Delay Register"                                   -
 MMDC_MPRDDQBY3DL   0x0828 rw 0x00000000 -         -    -   "MMDC PHY Read DQ Byte3 Delay Register"                                   -
 MMDC_MPWRDQBY0DL   0x082C rw 0x00000000 -         -    -   "MMDC PHY Write DQ Byte0 Delay Register"                                  -
 MMDC_MPWRDQBY1DL   0x0830 rw 0x00000000 -         -    -   "MMDC PHY Write DQ Byte1 Delay Register"                                  -
 MMDC_MPWRDQBY2DL   0x0834 rw 0x00000000 -         -    -   "MMDC PHY Write DQ Byte2 Delay Register"                                  -
 MMDC_MPWRDQBY3DL   0x0838 rw 0x00000000 -         -    -   "MMDC PHY Write DQ Byte3 Delay Register"                                  -
 MMDC_MPDGCTRL0     0x083C rw 0x00000000 -         -    -   "MMDC PHY Read DQS Gating Control Register 0"                             -
 MMDC_MPDGCTRL1     0x0840 rw 0x00000000 -         -    -   "MMDC PHY Read DQS Gating Control Register 1"                             -
 MMDC_MPDGDLST0     0x0844 r  0x00000000 -         -    -   "MMDC PHY Read DQS Gating delay-line Status Register"                     -
 MMDC_MPRDDLCTL     0x0848 rw 0x40404040 -         -    -   "MMDC PHY Read delay-lines Configuration Register"                        -
 MMDC_MPRDDLST      0x084C r  0x00000000 -         -    -   "MMDC PHY Read delay-lines Status Register"                               -
 MMDC_MPWRDLCTL     0x0850 rw 0x40404040 -         -    -   "MMDC PHY Write delay-lines Configuration Register"                       -
 MMDC_MPWRDLST      0x0854 r  0x00000000 -         -    -   "MMDC PHY Write delay-lines Status Register"                              -
 MMDC_MPSDCTRL      0x0858 rw 0x00000000 -         -    -   "MMDC PHY CK Control Register"                                            -
 MMDC_MPZQLP2CTL    0x085C rw 0x1B5F0109 -         -    -   "MMDC ZQ LPDDR2 HW Control Register"                                      -
 MMDC_MPRDDLHWCTL   0x0860 rw 0x00000000 -         -    -   "MMDC PHY Read Delay HW Calibration Control Register"                     -
 MMDC_MPWRDLHWCTL   0x0864 rw 0x00000000 -         -    -   "MMDC PHY Write Delay HW Calibration Control Register"                    -
 MMDC_MPRDDLHWST0   0x0868 r  0x00000000 -         -    -   "MMDC PHY Read Delay HW Calibration Status Register 0"                    -
 MMDC_MPRDDLHWST1   0x086C r  0x00000000 -         -    -   "MMDC PHY Read Delay HW Calibration Status Register 1"                    -
 MMDC_MPWRDLHWST0   0x0870 r  0x00000000 -         -    -   "MMDC PHY Write Delay HW Calibration Status Register 0"                   -
 MMDC_MPWRDLHWST1   0x0874 r  0x00000000 -         -    -   "MMDC PHY Write Delay HW Calibration Status Register 1"                   -
 MMDC_MPWLHWERR     0x0878 rw 0x00000000 -         -    -   "MMDC PHY Write Leveling HW Error Register"                               -
 MMDC_MPDGHWST0     0x087C r  0x00000000 -         -    -   "MMDC PHY Read DQS Gating HW Status Register 0"                           -
 MMDC_MPDGHWST1     0x0880 r  0x00000000 -         -    -   "MMDC PHY Read DQS Gating HW Status Register 1"                           -
 MMDC_MPDGHWST2     0x0884 r  0x00000000 -         -    -   "MMDC PHY Read DQS Gating HW Status Register 2"                           -
 MMDC_MPDGHWST3     0x0888 r  0x00000000 -         -    -   "MMDC PHY Read DQS Gating HW Status Register 3"                           -
 MMDC_MPPDCMPR1     0x088C rw 0x00000000 -         -    -   "MMDC PHY Pre-defined Compare Register 1"                                 -
 MMDC_MPPDCMPR2     0x0890 rw 0x00400000 -         -    -   "MMDC PHY Pre-defined Compare and CA delay-line Configuration Register"   -
 MMDC_MPSWDAR0      0x0894 rw 0x00000000 -         -    -   "MMDC PHY SW Dummy Access Register"                                       -
 MMDC_MPSWDRDR0     0x0898 r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 0"                                  -
 MMDC_MPSWDRDR1     0x089C r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 1"                                  -
 MMDC_MPSWDRDR2     0x08A0 r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 2"                                  -
 MMDC_MPSWDRDR3     0x08A4 r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 3"                                  -
 MMDC_MPSWDRDR4     0x08A8 r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 4"                                  -
 MMDC_MPSWDRDR5     0x08AC r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 5"                                  -
 MMDC_MPSWDRDR6     0x08B0 r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 6"                                  -
 MMDC_MPSWDRDR7     0x08B4 r  0xFFFFFFFF -         -    -   "MMDC PHY SW Dummy Read Data Register 7"                                  -
 MMDC_MPMUR0        0x08B8 rw 0x00000000 -         -    -   "MMDC PHY Measure Unit Register"                                          -
 MMDC_MPWRCADL      0x08BC rw 0x00000000 -         -    -   "MMDC Write CA delay-line controller"                                     -
 MMDC_MPDCCR        0x08C0 rw 0x24922492 -         -    -   "MMDC Duty Cycle Control Register"                                        -
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

