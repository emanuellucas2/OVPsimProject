 
  Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.

  The contents of this file are provided under the Software License
  Agreement that you accepted before downloading this file.

  This source forms part of the Software and can be used for educational,
  training, and demonstration purposes but cannot be used for derivative
  works except in cases where the derivative works require OVP technology
  to run.

  For open source models released under licenses that you can use for
  derivative works, please visit www.ovpworld.org or www.imperas.com
  for the location of the open source models.


FILE:Imperas/Examples/SimulationControl/callingInstalledCommands/README.txt

INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows the use of the API functions to create a platform that
is used to show how additional tool commands can be called.

This example can only be used with an Imperas Professional Tool installation.

FILES --------------------------------------------------------------
There are four parts to the example
1. An application; this is found as application/application.c
2. A harness that loads a module and calls the API functions; this is found as harness/harness.c
3. The hardware definition; this is found as module/module.op.tcl
4. A makefile to build 1, 2 and 3; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the Harness

> make -C harness

To build the Module

> make -C module

RUNNING THE EXAMPLE ------------------------------------------------

> harness/harness.<IMPERAS_ARCH>.exe --program application.<CROSS>.elf

