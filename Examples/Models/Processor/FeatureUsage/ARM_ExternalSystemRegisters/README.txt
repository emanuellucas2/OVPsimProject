
 Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com

 The contents of this file are provided under the Software License
 Agreement that you accepted before downloading this file.

 This source forms part of the Software and can be used for educational,
 training, and demonstration purposes but cannot be used for derivative
 works except in cases where the derivative works require OVP technology
 to run.

 For open source models released under licenses that you can use for
 derivative works, please visit www.ovpworld.org or www.imperas.com
 for the location of the open source models.



File:Imperas/Examples/Models/Processor/FeatureUsage/ARM_ExternalSystemRegisters/README.txt

INTRODUCTION -------------------------------------------------------

This directory contains an example of using a harness to attach to either the
1) System Registers monitoring port (e.g. for CPU0 it is SystemMonitor_CPU0), or
2) System Registers implementation port (e.g. for CPU0 it is System_CPU0)
These two artifact bus ports allow a user to either monitor or implement the 
system registers of the model.

A harness is provided that will load the module defining the ARMv8-A-FMv1
hardware and then connect to the two bus ports within the module using locally
created busses. Callbacks are then implemented on the local busses for 
monitoring or implementation of the system registers.

The harness source may be found in harness/harness.c. The included Makefile will
compile and link the harness.

RUNNING THE EXAMPLE ------------------------------------------------

The harness is built using the command
  make -C harness
  
The harness is automatically rebuilt as part of the execution scripts provided

To monitor the accesses to the system registers during the Linux Kernel boot run
the script for Linux (Windows)
 
  MONITOR_SystemRegisters.sh(.bat)

To re-implement the timer registers with functions in the harness during the 
Linux Kernel boot run the script for Linux (Windows)

  REIMPLEMENT_TimerRegisters.sh(.bat)
