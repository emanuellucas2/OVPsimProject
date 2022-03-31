 
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


FILE:Imperas/Examples/SimulationControl/loadingApplicationProgramHexFormatFile/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CpuManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows how simple functions can be used in conjunction with the 
API memory access functions to create custom file (or data) loaders.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as
                   a) an assembler file to load; application/asmtest.S
                   b) as a hex file to load; application/asmtest.hex
2. A C harness; this is found as harness/harness.c
3. A makefile to build 1 and 2; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application 
NOTE: The elf file output is not used directly. The objectdump
program is used to generate a listing that can be used for the hex
file input. 

> make -C application asmtest.<CROSS>.elf.dump CROSS=<CROSS>

To build the C Platform

> make -C platform

RUNNING THE EXAMPLE ------------------------------------------------

To run using the assembler file

> platform/platform.<IMPERAS_ARCH>.exe --hexfile application/asmtest.hex

NOTE: If there is no symbolic information loaded and as such the normal 
termination by detecting exit in the semihosting library does not work
this example will terminate with a load exception when the program
tries to read from an unmapped area of memory (0x00000000)

If using the Imperas professional simulator 
The symbols information can be loaded using the command line argument 
   --symbolfile application/asmtest.<CROSS>.elf

 
RE-CREATING THE HEX FILE IN THE EXAMPLE ----------------------------

The hex file can be re-created from the asmtest.S assembler source 
file using the OBJDUMP command. This is included in the Makefile

> make -C application CROSS=<CROSS>.dump

This file should then be edited to create a hex format file; lines 
containing the required data such as 
" 1000074:       9c 20 00 00     l.addi r1,r0,0x0"
should become
"1000074 0000209c"
and any unwanted lines should be deleted or pre-pended with a '#' to make
them a comment; for example "01000074 <_start>:" becomes "#01000074 <_start>:"

Swapping the bytes can be done in the harness.c file by enabling swapping 
on the hex load function.
