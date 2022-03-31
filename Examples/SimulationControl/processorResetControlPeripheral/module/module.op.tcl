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
# NAME : systemReset

ihwnew -name systemReset  \
          -vendor example.ovpworld.org  \
          -library module  \
          -version 1.0 \
          -purpose baremetal -releasestatus ovp

iadddocumentation  \
          -name Description  \
          -text "Module instancing an ARM processor and a peripheral 
                 that can generate reset when commanded via a socket connection."

iadddocumentation  \
          -name Licensing  \
          -text "Open Source Apache 2.0"

iadddocumentation  \
          -name Limitations  \
          -text "None"

iadddocumentation  \
          -name Reference  \
          -text "Simple example platform."

############################### net ###############################

  ihwaddnet \
          -instancename reset

############################### bus ###############################

  ihwaddbus \
          -instancename bus1  \
          -addresswidth 32

############################ processor ############################

  ihwaddprocessor  \
          -instancename cpu0  \
          -type arm \
          -endian little \
          -vendor arm.ovpworld.org \
          -semihostname armNewlib \
          -semihostvendor arm.ovpworld.org

  ihwsetparameter  \
          -handle cpu0  \
          -name variant  \
          -value ARM7TDMI \
          -type enum

  ihwconnect -instancename cpu0  \
          -busmasterport INSTRUCTION  \
          -bus bus1

  ihwconnect -instancename cpu0  \
          -busmasterport DATA  \
          -bus bus1

  ihwconnect -instancename cpu0  \
          -netport reset  \
          -net reset

############################## memory #############################

  ihwaddmemory \
          -instancename memory  \
          -type ram

  ihwconnect \
          -instancename memory  \
          -busslaveport sp1  \
          -bus bus1  \
          -loaddress 0x00000000  \
          -hiaddress 0xffffffff

########################### reset peripheral ###########################

  ihwaddperipheral \
          -instancename resetGeneration  \
          -type resetControl \
          -modelfile peripheral/pse.pse
    
  ihwconnect \
          -instancename resetGeneration  \
          -netport resetOut  \
          -net reset
