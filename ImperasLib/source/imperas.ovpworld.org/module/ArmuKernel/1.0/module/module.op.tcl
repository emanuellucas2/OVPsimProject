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
# NAME : ArmuKernel  

ihwnew -name ArmuKernel  \
       -vendor imperas.ovpworld.org  \
       -library module  \
       -version 1.0  \
       -stoponctrlc \
       -purpose module -releasestatus ovp

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Description  \
    -text "
    Bare Metal Platform for an ARM Cortex-A9MPx4 to execute the SMP UKernel.
    This platform  executes the ARM MPCore Boot and Synchronization Example Code"

iadddocumentation  \
    -name Limitations  \
    -text "BareMetal platform for execution of ARM binary uKernel file"

iadddocumentation  \
    -name Reference  \
    -text "http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php"

ihwaddnet -instancename  irq

ihwaddformalmacro -name OP_HTTP_VIS_PORT_FORMALS

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -endian little  \
                -type    arm \
                -vendor  arm.ovpworld.org \
                -version 1.0 \
                \
                -semihostname armNewlib \
                -semihostvendor arm.ovpworld.org \
                \
                -mips 100.0 \
                \
                -simulateexceptions \
                \
                -imagefile cli.axf \
                -useobjectentry

  ihwaddbus -instancename bus1  \
                -addresswidth 32

  ihwsetparameter -handle cpu1 \
                -name variant -value Cortex-A9MPx4 -type enum

  ihwsetparameter -handle cpu1 \
                -name UAL -value 1 -type bool
                
  ihwsetparameter -handle cpu1 \
                -name override_CBAR -value 0x1f000000 -type uns32

  ihwconnect  -instancename cpu1  \
              -busmasterport INSTRUCTION  \
              -bus bus1

  ihwconnect -instancename cpu1  \
             -busmasterport DATA  \
             -bus bus1

  ihwconnect -net irq -instancename cpu1 -netport SPI36
#  ihwconnect -net irq -instancename cpu1 -netport irq_CPU0
#  ihwconnect -net fiq -instancename cpu1 -netport fiq

############################## memory #############################

  ihwaddmemory -type ram -instancename memory1

  ihwconnect -instancename memory1 \
               -busslaveport sp1  \
               -bus bus1  \
               -loaddress 0x00000000  \
               -hiaddress 0x0fffffff

  ihwaddmemory -type ram -instancename deviceDummy1
   
  ihwconnect -instancename deviceDummy1 \
             -busslaveport sp1  \
             -bus bus1  \
             -loaddress 0x10000000  \
             -hiaddress 0x10008fff

  #
  # Uart
  #
  set uartSize  0x1000
  set uart1Base 0x10009000

  # Set the name for the uart logfile, allowing it to be changed
  ihwaddformalparameter -name uart1logname -defaultvalue "uart1.log" -type string

  ihwaddperipheral -instancename uart1  -type UartPL011 -vendor  arm.ovpworld.org
  ihwsetparameter    -handle       uart1  -name variant -value ARM               -type enum
  ihwsetparameter    -handle       uart1  -name outfile -expression uart1logname -type string
  ihwsetparameter    -handle       uart1  -name portnum                          -type uns32
  ihwsetparameter    -handle       uart1  -name console -value 1                 -type bool
  ihwsetparameter    -handle       uart1  -name finishOnDisconnect -value 1      -type bool
  ihwconnect       -instancename uart1  -bus bus1 -busslaveport bport1 -loaddress $uart1Base -hiaddress [expr $uart1Base + $uartSize - 1]
  ihwconnect       -instancename uart1  -net irq -netport irq


  ihwaddmemory -type ram -instancename deviceDummy2

  ihwconnect -instancename deviceDummy2 \
             -busslaveport sp1  \
             -bus bus1  \
             -loaddress 0x1000a000  \
             -hiaddress 0xffffffff

