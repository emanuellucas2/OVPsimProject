 
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


FILE:Imperas/Examples/PlatformConstruction/busHierarchy/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains an example from the OP Platform Modeling
Guide.

The example illustrates the use of the OP API to bridge between two
buses, and shows how to connect buses through the hierarchy.

FILES --------------------------------------------------------------
1. A test-bench:
   harness/harness.c          - behavioral code that drives one bus
                                and detects accesses on the other bus.

2. A module to define hardware:
   module/module.op.tcl       - two bus ports connect to two busses
                                which are bridged

BUILDING and EXECUTING ---------------------------------------------

> ./example.sh (or example.bat)

