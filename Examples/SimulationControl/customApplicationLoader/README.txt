 
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


FILE:Imperas/Examples/SimulationControl/customApplicationLoader/README.txt

INTRODUCTION -------------------------------------------------------

This example shows how to write your own object code reader and use it
with CpuManager or the Imperas Simulator.

The features described are not available in the OVPsim simulator, only
the Imperas Professional Simulator.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/hello.c
2. The example loader; this is found as loader/loader.c
3. The module design; this is found as module/module.op.tcl
4. The harness; this is found as harness/harness.c

BUILDING THE COMPONENTS --------------------------------------------

To build the application
> make -C application

To build the loader
> make -C loader

To build the hardware design and test
> make -C harness
> make -C module


RUNNING THE EXAMPLE ------------------------------------------------

> harness/harness.<IMPERAS_ARCH>.exe --program application/hello.<CROSS>.s19


