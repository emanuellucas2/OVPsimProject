 
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


FILE:Imperas/Examples/PlatformConstruction/byteSwapperMMC/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains an example from the OP Platform Modeling
Guide.

The example illustrates the use of an MMC to model a byte swapping
(endian correction) function.
It should be used in conjunction with the user guide but is briefly
described here.

FILES --------------------------------------------------------------
There are four parts to the example:
1. An application; application/application.c
2. A module defining the hardware; module/module.op.tcl
3. A trivial peripheral model to illustrate the byte swapping; peripheral

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=OR1K

To build the hardware definition and peripheral

> make -C module
> make -C peripheral

EXECUTE THE SIMULATION --------------------------------------------
The execution of the simulation uses the standard harness to load 
the module definition and an application executable.

> harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
              --program application/application.${CROSS}.elf

RUNNING THE EXAMPLE ------------------------------------------------

Alternatively a script is provided to do all of the above

> example.sh (.bat)
