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
# NAME : Or1kUclinux

ihwnew -name Or1kUclinux  \
                -vendor imperas.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal -releasestatus ovp \
                -verbose -stoponctrlc

iadddocumentation  \
                -name Description  \
                -text "Platform for an Or1k Processor to execute uCLinux."
            
iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "Provides sufficient functionality to execute uCLinux operating system and OR1K elf files"

iadddocumentation  \
-name Reference  \
-text "none"

ihwaddnet -instancename int1

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -type or1k \
                -vendor ovpworld.org
                
############################## bus #############################

   ihwaddbus -instancename bus1 -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename mem1  \
               -type ram

  ihwaddmemory -instancename mem2  \
               -type ram
               
############################## UART ##############################

   ihwaddperipheral -instancename uart1 \
                    -type 16550 \
                    -vendor national.ovpworld.org
   ihwsetparameter  -handle uart1 -name finishOnDisconnect -value 1 -type bool
                    
########################## CONNECTIONS ###########################

   ihwconnect -instancename cpu1 \
       -bus bus1 \
       -busmasterport INSTRUCTION
       
   ihwconnect -instancename cpu1 \
       -bus bus1 \
       -busmasterport DATA
       
   ihwconnect -instancename mem1 \
       -bus bus1 \
       -busslaveport sp1 \
       -loaddress 0x00000000 \
       -hiaddress 0x8FFFFFFF
       
    ihwconnect -instancename mem2 \
       -bus bus1 \
       -busslaveport sp1 \
       -loaddress 0x90000008 \
       -hiaddress 0xFFFFFFFF
       
    ihwconnect -instancename uart1 \
       -bus bus1 \
       -busslaveport bport1 \
       -loaddress 0x90000000 \
       -hiaddress 0x90000007
       
    ihwconnect -instancename uart1 -netport intOut -net int1
    ihwconnect -instancename cpu1  -netport intr2  -net int1


# Command line parser
ihwaddclp -allargs
