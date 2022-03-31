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

# NAME : ArmCortexMFreeRTOS

ihwnew -name ArmCortexMFreeRTOS  \
       -vendor imperas.ovpworld.org  \
       -library module  \
       -version 1.0 \
       -stoponctrlc \
       -purpose module -releasestatus ovp

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

############################ bus ############################

ihwaddbus -instancename bus1  \
       -addresswidth 32

############################ processor ############################

  ihwaddprocessor  \
       -instancename cpu1  \
       -type   armm \
       -vendor arm.ovpworld.org \
       -endian little \
       -simulateexceptions

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
               
  ihwaddperipheral -instancename led \
                   -vendor ovpworld.org \
                   -type ledRegister
                              
  ihwconnect -instancename led  \
             -busslaveport busPort  \
             -bus bus1  \
             -loaddress 0x40004000  \
             -hiaddress 0x40004007


 ihwsetparameter  -handle led -name availableLEDS -value 8       -type uns32
  
############################ switch pse ##############################
               
  ihwaddperipheral -instancename sw \
                   -vendor ovpworld.org \
                   -type switchRegister
                              
  ihwconnect -instancename sw  \
             -busslaveport busPort  \
             -bus bus1  \
             -loaddress 0x40006000  \
             -hiaddress 0x40006007

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

ihwaddnet -instancename uart_irq
ihwconnect -instancename cpu1  -netport int -net uart_irq
ihwconnect -instancename UART0 -netport irq -net uart_irq

#####################################################################################
# Export Bus to allow external connections
#####################################################################################
ihwaddbusport -instancename pBusP
ihwaddbus     -instancename pBusMapped -addresswidth 32
ihwconnect    -busport pBusP -bus pBusMapped
# Map unused space in ARM memory map 0x40000000 to 0x4010ffff to bottom of bus port 
ihwaddbridge  -instancename pBusBridge
ihwconnect    -instancename pBusBridge -busslaveport  sp1 -bus bus1       -loaddress 0x40100000 -hiaddress 0x4010ffff
ihwconnect    -instancename pBusBridge -busmasterport mp1 -bus pBusMapped -loaddress 0x00000000 -hiaddress 0x0000ffff
