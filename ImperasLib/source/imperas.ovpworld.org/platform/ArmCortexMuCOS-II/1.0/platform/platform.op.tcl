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
# NAME : BareMetalArmCortexMuCOS-II

ihwnew -name ArmCortexMuCOS-II  \
       -vendor imperas.ovpworld.org  \
       -library platform  \
       -version 1.0 -purpose baremetal -releasestatus ovp

  iadddocumentation  \
       -name Description  \
       -text "Platform for Micrium uc/OS-II bring up and simple LED access"

  iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

iadddocumentation  \
  -name Limitations  \
  -text "BareMetal platform for bring up of uc/OS-II on ARM Cortex-M3 processor"

iadddocumentation  \
  -name Reference  \
  -text "www.micrium.com/page/products/rtos/os-ii"


############################ command line parser ############################
ihwaddclp -allargs
ihwaddclparg -name kernel -type stringvar -group "user platform config" -description "the uc/OS-II image" -mustbespecified

############################ processor ############################

  ihwaddprocessor  \
       -instancename cpu1  \
       -type   armm \
       -vendor arm.ovpworld.org \
       -semihostname   armNewlib \
       -semihostvendor arm.ovpworld.org \
       -endian little \
       -simulateexceptions \
       -imagefile ucosiiDemoApplication.ARM_CORTEX_M3.elf \
       -mips 100.0
       

  ihwsetparameter  -handle cpu1 -name variant       -value Cortex-M3  -type enum
  ihwsetparameter  -handle cpu1 -name compatibility -value gdb        -type enum

  ihwaddbus -instancename bus1  \
                -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory1  \
               -type ram
  ihwaddmemory -instancename memory2  \
               -type ram

############################ led pse ##############################
               
  ihwaddperipheral -instancename led \
                   -vendor ovpworld.org \
                   -type ledRegister
                              
########################### connections ###########################

  ihwconnect -instancename cpu1  \
             -busmasterport INSTRUCTION  \
             -bus bus1

  ihwconnect -instancename cpu1  \
             -busmasterport DATA  \
             -bus bus1

  ihwconnect -instancename memory1  \
             -busslaveport sp1  \
             -bus bus1  \
             -loaddress 0x00000000  \
             -hiaddress 0x0fffffff

  ihwconnect -instancename memory2  \
             -busslaveport sp1  \
             -bus bus1  \
             -loaddress 0x20000000  \
             -hiaddress 0xffffffff

  ihwconnect -instancename led  \
             -busslaveport busPort  \
             -bus bus1  \
             -loaddress 0x10000000  \
             -hiaddress 0x10000007
