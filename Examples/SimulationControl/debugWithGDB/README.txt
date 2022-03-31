 
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


FILE:Imperas/Examples/SimulationControl/debugWithGDB/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows how the GDB debugger can be attached to a CpuManager 
instance.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/application.c
2. the hardware definition; this is found as module/module.op.tcl
3. A makefile to build 1 and 2; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the Module

> make -C module

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.<IMPERAS_ARCH>.exe --program 12345 &

Run up GDB for the OR1K

> Imperas/lib/${IMPERAS_ARCH}/CrossCompiler/or32-elf/bin/or32-elf-gdb

load file to debug and connect to the simulator

gdb> file application/application.<CROSS>.elf
gdb> target remote localhost:12345

set a break point at main and run the program

gdb> break main
gdb> continue

then run the program to completion and quit

gdb> continue
gdb> quit

