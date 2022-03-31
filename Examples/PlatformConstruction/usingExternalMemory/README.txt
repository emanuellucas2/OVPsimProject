 
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


FILE:Imperas/Examples/PlatformConstruction/usingExternalMemory/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the Simulation Guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows how memory can be mapped externally to the memory provided 
by the simulator as part of the processor instance and how different access
privileges can be applied.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/asmtest.S
2. An module; this is found as module/module.c and module/module.op.tcl

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the module

> make -C module

RUNNING THE EXAMPLE ------------------------------------------------

> harness.exe --modulefile module \
            --program application/asmtest.<CROSS>.elf \
            --trace --showbusses --showdomains \
            $@
 