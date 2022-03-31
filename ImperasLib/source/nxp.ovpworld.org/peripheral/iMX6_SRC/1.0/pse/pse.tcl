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
set name    iMX6_SRC
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "NXP i.MX6 System Reset Control (SRC)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

set limitations "Implements the power on reset and core1 enable requirements."
iadddocumentation -name Limitations -text $limitations

iadddocumentation \
    -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

# ARM Processor reset control
imodeladdnetport  -name resetCore0 -type output
iadddocumentation -name Description  -text "Reset control for ARM Core 0"
imodeladdnetport  -name resetCore1 -type output
iadddocumentation -name Description  -text "Reset control for ARM Core 1 (power up active)"
    
set port  bport1
set block ab
set size  0x4000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

# define a general function if an access to an area in which there is no register defined
imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    SRC_SCR   0x00  rw 0x00000521 0x02666fff  auto auto "SRC Control Register (SRC_SCR)"              
                        {   DBG_RST_MSK     25 1 
                            CORE1EN         22 1 
                            CORES_DBG_RST   21 1 
                            CORE1_DBG_RST   18 1 
                            CORE0_DBG_RST   17 1 
                            CORE1_RST       14 1 
                            CORE0_RST       13 1 
                            EIM_RST         11 1 
                            MSK_WDG_RST      7 4 
                            WRM_RST_BYPASS   5 2 
                            SW_OPVG_RST      4 1 
                            SW_IPU1_RST      3 1 
                            SW_VPU_RST       2 1 
                            SW_GPU_RST       1 1 
                            WARM_RST_EN      0 1
                        }
    SRC_SBMR1 0x04  r  0x00000000 -           -    -    "SRC Boot Mode Register 1 (SRC_SBMR1)"
                        {
                            BOOT_CFG4 24 8 
                            BOOT_CFG3 16 8 
                            BOOT_CFG2  8 8 
                            BOOT_CFG1  0 8
                        }
    SRC_SRSR  0x08  rw 0x00000001 0x00010007d auto auto "SRC Reset Status Register (SRC_SRSR)"
                        {
                            WARM_BOOT    16 1
                            JTAG_SW_RST   6 1
                            JTAG_RST      5 1
                            WDOG_RST      4 1
                            IPP_USER_RST  3 1
                            CSU_RST       2 1 
                            IPP_RST       0 1
                        }
    SRC_SISR  0x0c  r  0x00000000 -           auto -    "SRC Interrupt Status Register (SRC_SISR)"
                        {
                            CORE1_WDOG 6 1 
                            CORE0_WDOG 5 1 
                            OP_VG_PASS 3 1 
                            IPU1_PASS  2 1 
                            VPU_PASS   1 1 
                            GPU_PASS   0 1
                        }
    SRC_SIMR  0x10  rw 0x0000001F 0x00000000f auto auto "SRC Interrupt Mask Register (SRC_SIMR)"
                        {
                            OP_VG_PASS 3 1 
                            IPU1_PASS  2 1 
                            VPU_PASS   1 1 
                            GPU_PASS   0 1 
                        }
    SRC_SBMR2 0x14  r  0x00000000 -           -    -    "SRC Boot Mode Register 2 (SRC_SBMR2)"
                        {
                            BMOD        24 2 
                            BT_FUSE_SEL  4 1 
                            DIR_BT_DIS   3 1 
                            SEC_CONFIG   0 2
                        }
    SRC_GPR1  0x18  rw 0x00000000 -           -    -    "SRC General Purpose Register 1 (SRC_GPR1)"   -
    SRC_GPR2  0x1c  rw 0x00000000 -           -    -    "SRC General Purpose Register 2 (SRC_GPR2)"   -
    SRC_GPR3  0x20  rw 0x00000000 -           -    -    "SRC General Purpose Register 3 (SRC_GPR3)"   -
    SRC_GPR4  0x24  rw 0x00000000 -           -    -    "SRC General Purpose Register 4 (SRC_GPR4)"   -
    SRC_GPR5  0x28  rw 0x00000000 -           -    -    "SRC General Purpose Register 5 (SRC_GPR5)"   -
    SRC_GPR6  0x2c  rw 0x00000000 -           -    -    "SRC General Purpose Register 6 (SRC_GPR6)"   -
    SRC_GPR7  0x30  rw 0x00000000 -           -    -    "SRC General Purpose Register 7 (SRC_GPR7)"   -
    SRC_GPR8  0x34  rw 0x00000000 -           -    -    "SRC General Purpose Register 8 (SRC_GPR8)"   -
    SRC_GPR9  0x38  rw 0x00000000 -           -    -    "SRC General Purpose Register 9 (SRC_GPR9)"   -
    SRC_GPR10 0x3c  rw 0x00000000 -           -    -    "SRC General Purpose Register 10 (SRC_GPR10)" -
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
    foreach { n o w } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}
