 
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


FILE:Imperas/Examples/PlatformConstruction/moduleHierarchyAndConnectivity/README.txt

INTRODUCTION -------------------------------------------------------
This directory contains an example from the iGen Platform and Module
Creation User Guide.

The example illustrates the use of iGen to construct a platform with
two processors with some shared memory.

FILES --------------------------------------------------------------
1. An application; application/*.[ch]
2. A Processor sub-system; 
    processorSubSystem/module.op.tcl        the module description for input to iGen
3. A shared memory sub-system; 
    sharedMemorySubSystem/module.op.tcl     the module description for input to iGen
4. A top level instancing the sub-systems; 
    topLevel/module.op.tcl                  the module description for input to iGen

BUILDING and EXECUTING ---------------------------------------------

> ./example.sh (or example.bat)

Note in this example, to simulate a module, the harness.exe program is used.

#
