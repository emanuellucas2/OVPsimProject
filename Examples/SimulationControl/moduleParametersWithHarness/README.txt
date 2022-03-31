 
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


FILE:Imperas/Examples/SimulationControl/moduleParametersWithHarness/README.txt

INTRODUCTION -------------------------------------------------------
This directory contains an example that illustrates how a harness can 
be used to modify parameters of modules and components in the platform.


FILES --------------------------------------------------------------
1. Application; application/application.c
2. Modules;
    topmodule/module.op.tcl   module instancing a processor and two sub-modules
    submodule/module.op.tcl   module instances a UART peripheral
3. Harness;
    harness/harness.c         sets parameters to locate the UART base addresses
                              and to define the UART output logfiles 

BUILDING and EXECUTING ---------------------------------------------

> ./example.sh (or example.bat)

#
