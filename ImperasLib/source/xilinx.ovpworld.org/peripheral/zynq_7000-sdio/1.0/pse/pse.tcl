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
set name    zynq_7000-sdio
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 SD/SDIO Registers"

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

set registers {
    SDMA_system_address_register            0x00000000 32 rw 0x00000000  -      -          -           -  "System DMA Address Register"
    Block_Size_Block_Count                  0x00000004 32 rw 0x00000000  -      -          -           -  "Block size register / Block count register" 
    Argument                                0x00000008 32 rw 0x00000000  -      -          -           -  "Argument register"
    Transfer_Mode_Command                   0x0000000C 32 rw 0x00000000  -      -          -           -  "Transfer mode register / Command register"
    Response0                               0x00000010 32 r  0x00000000  -      -          -           -  "Response register"
    Response1                               0x00000014 32 r  0x00000000  -      -          -           -  "Response register"
    Response2                               0x00000018 32 r  0x00000000  -      -          -           -  "Response register"
    Response3                               0x0000001C 32 r  0x00000000  -      -          -           -  "Response register"
    Buffer_Data_Port                        0x00000020 32 rw 0x00000000  -      -          -           -  "Buffer data port register"
    Present_State                           0x00000024 32 r  0x01F20000  -      -          -           -  "Present State register"
    Host_Power_Block_Gap_Wakeup_control     0x00000028 32 rw 0x00000000  -      wrPwrCtrl  0x070f0fef  {LED 0 1}  "(Host_control_Power_control_Block_Gap_Control_Wakeup_control) Host control register / Power control register / Block gap control register / Wake-up control register"
    Clock_Timeout_control_Software_reset    0x0000002C 32 rw 0x00000000  -      wrClkCtrl  0x070fff07  {SWRST_DAT 26 1 SWRST_CMD 25 1 SWRST_ALL 24 1 ICLKST 1 1 ICLKEN 0 1}  "(Clock_Control_Timeout_control_Software_reset) Clock Control register / Timeout control register / Software reset register"
    Interrupt_status                        0x00000030 30 rw 0x00000000  -      -          0x3fffffff  -  "(Normal_interrupt_status_Error_interrupt_status) Normal interrupt status register / Error interrupt status register"
    Interrupt_status_enable                 0x00000034 30 rw 0x00000000  -      -          0x3fffffff  -  "(Normal_interrupt_status_enable_Error_interrupt_status_enable) Normal interrupt status enable register / Error interrupt status enable register"   
    Interrupt_signal_enable                 0x00000038 30 rw 0x00000000  -      -          0x3fffffff  -  "(Normal_interrupt_signal_enable_Error_interrupt_signal_enable) Normal interrupt signal enable   register / Error interrupt signal enable register"
    Auto_CMD12_error_status                 0x0000003C  8 r  0x00000000  -      -          -           -  "Auto CMD12 error status register"
    Capabilities                            0x00000040 31 r  0x69EC0080  -      -          -           -  "Capabilities register"
    Maximum_current_capabilities            0x00000048 24 r  0x00000001  -      -          -           -  "Maximum current capabilities register"
    Force_event                             0x00000050 32 rw 0x00000000  -      -          -           -  "(Force_event_for_AutoCmd12_Error_Status_Force_event_register_for_error_interrupt_status) Force event register for Auto CMD12 error status register / Force event register for error interrupt status"
    ADMA_error_status                       0x00000054  3 rw 0x00000000  -      -          0x00000007  -  "ADMA error status register"
    ADMA_system_address                     0x00000058 32 rw 0x00000000  -      -          -           -  "ADMA system address register"
    Boot_Timeout_control                    0x00000060 32 rw 0x00000000  -      -          -           -  "Boot Timeout control register"
    Debug_Selection                         0x00000064  1  w 0x00000000  -      wrDebugSel 0x00000001  -  "Debug Selection Register"
    SPI_interrupt_support                   0x000000F0  8 rw 0x00000000  -      -          0x000000ff  -  "SPI interrupt support register"
    Slot_status_Host_version                0x000000FC 32 r  0x89010000  -      -          -           -  "(Slot_interrupt_status_Host_controller_version) Slot interrupt status register and Host controller version register"   
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  # all register 32-bit aligned
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
iadddocumentation -name Description -text "Interrupt signal"
 
