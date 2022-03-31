 
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


FILE:Imperas/Examples/SimulationControl/loadingApplicationProgramIntelHexFormatFile/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains an example shows how simple functions can be
used in conjunction with the API memory access functions to create
custom file (or data) loaders.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as
        a) an assembler test file; application/asmtest.S
        b) a Makefile to build an ELF and HEX file; application/Makefile
2. A C harness; this is found as
        a) harness/harness.c, containing the loader code
        b) Makefile to build
3. A module defining the hardware; this is found as
        a) module/module.op.tcl
        b) Makefile to build

BUILDING THE SIMULATION --------------------------------------------
To build the application 
NOTE: The elf file output is not used directly. The objectcopy
program is used to generate an Intel Hex file. 

> make -C application CROSS=<CROSS>

To build the Test Harness

> make -C harness

To build the Hardware Module

> make -C module

RUNNING THE EXAMPLE ------------------------------------------------

To run using the assembler file

> platform/platform.<IMPERAS_ARCH>.exe --hexfile application/asmtest.<CROSS>.hex

NOTE: There is no symbolic information loaded and as such the normal 
termination by detecting exit in the semihosting library does not work.
Instead this example terminates after executing 100 instructions. In fact
the assembler program executes a wfi at which point the simulator detects no 
further instructions will be executed and jumps forward and terminates.
