 
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


FILE:Imperas/Examples/PlatformConstruction/netHierarchy/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains an example from the OP Platform Modeling
Guide.

The example shows how to connect nets across the hierarchy.

FILES --------------------------------------------------------------
1. A module instance definition:
   module/module.op.tcl - hardware definition input file to iGen.

2. A test harness containing two nets which will be connected by a repeater;
   harness/harness.c    - test harness that drives one net and detects 
                          accesses on the other net.

BUILDING and EXECUTING ---------------------------------------------

> ./example.sh (or example.bat)

