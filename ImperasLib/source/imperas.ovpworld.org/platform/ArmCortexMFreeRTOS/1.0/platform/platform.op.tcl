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
# NAME : BareMetalArmCortexMFreeRTOS

ihwnew -name ArmCortexMFreeRTOS  \
       -vendor imperas.ovpworld.org  \
       -library platform  \
       -version 1.0 \
       -stoponctrlc \
       -purpose baremetal -releasestatus ovp

  iadddocumentation  \
       -name Description  \
       -text "Platform for FreeRTOS bring"

  iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

iadddocumentation  \
  -name Limitations  \
  -text "BareMetal platform for bring up of FreeRTOS on ARM Cortex-M3 processor"

iadddocumentation  \
  -name Reference  \
  -text "www.freertos.org"

############################ command line parser ############################
ihwaddclp -allargs
ihwaddclparg -name rtos -type stringvar -group "user platform config" -description "the FreeRTOS image" -mustbespecified

############################ irq ############################

ihwaddnet -instancename uart_irq

############################ bus ############################

ihwaddbus -instancename bus1  \
       -addresswidth 32

############################ processor ############################

  ihwaddprocessor  \
       -instancename cpu1  \
       -type   armm \
       -vendor arm.ovpworld.org \
       -semihostname   armNewlib \
       -semihostvendor arm.ovpworld.org \
       -endian little \
       -simulateexceptions \
       -mips 12
       

  ihwsetparameter  -handle cpu1 -name variant -value Cortex-M3  -type enum
  ihwsetparameter  -handle cpu1 -name UAL -value 1              -type bool

  ihwconnect -instancename cpu1  \
		-busmasterport INSTRUCTION  \
		-bus bus1
   
  ihwconnect -instancename cpu1  \
		-busmasterport DATA  \
		-bus bus1
   
############################## memory #############################

  ihwaddmemory -instancename memory1  \
               -type ram
  ihwconnect -instancename memory1  \
               -busslaveport sp1  \
               -bus bus1  \
               -loaddress 0x00000000  \
               -hiaddress 0x3fffffff

  ihwaddmemory -instancename memory2  \
               -type ram

  ihwconnect -instancename memory2  \
	       -busslaveport sp1  \
	       -bus bus1  \
	       -loaddress 0x41000000  \
	       -hiaddress 0xffffffff

############################ led pse ##############################
               
  ihwaddperipheral -instancename LEDRegister \
                   -vendor ovpworld.org \
                   -type ledRegister
                              
  ihwconnect -instancename LEDRegister  \
             -busslaveport busPort  \
             -bus bus1  \
             -loaddress 0x40004000  \
             -hiaddress 0x40004007

 ihwsetparameter  -handle LEDRegister -name availableLEDS -value 8       -type uns32
  
############################ uart pse ##############################
	     
ihwaddperipheral -instancename UART0 \
		 -vendor ti.ovpworld.org \
		 -type UartInterface
			    
ihwconnect -instancename UART0  \
	   -busslaveport bport1  \
	   -bus bus1  \
	   -loaddress 0x4000c000  \
	   -hiaddress 0x4000cfff
	   
ihwsetparameter  -handle UART0 -name console            -value 1      -type bool
ihwsetparameter  -handle UART0 -name finishOnDisconnect -value 1      -type bool
ihwsetparameter  -handle UART0 -name loopback           -value 1      -type bool

ihwconnect -instancename cpu1  -netport int -net uart_irq
ihwconnect -instancename UART0 -netport irq -net uart_irq

