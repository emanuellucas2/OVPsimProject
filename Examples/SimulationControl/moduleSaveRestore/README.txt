 
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


FILE:Imperas/Examples/SimulationControl/moduleSaveRestore/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains an example of how to save the simulation state
to a file during a simulation. A second run restores from the file then
resumes.

FILES --------------------------------------------------------------
1. Application; 
     application/application.c
2. A Platform; 
    harness/harness.c
3. A module with an OR1K processor and memory.
    module/module.c
    
   To illustrate the explicit saving of module data, the module
   counts the number of fetched instructions in a limited memory
   range. This count must be explicitly saved and restored so the 
   simulation results are not affected by save/restore.

BUILDING and EXECUTING ---------------------------------------------

> ./example.sh (or example.bat)

#
