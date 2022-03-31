 
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


FILE:Imperas/Examples/SimulationControl/debugSystemC_TLM2.0WithGDB/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVP Debugging 
Applications with GDB User Guide.

It should be used in conjunction with the user guide but is briefly 
described here.

This example shows how the GDB debugger can be attached to processor 
instance instantiated within a SystemC TLM2.0 platform.

FILES --------------------------------------------------------------
There are two parts to the example
1. An application with Makefile; this is found in the application
   directory as application.c and Makefile respectively.
2. A SystemC TLM2.0 platform instantiating an OVP processor; this is 
   found as platform/platform.cpp. Also within this directory are 
   scripts that can be used to build the platform.

BUILDING THE SIMULATION --------------------------------------------
To build the application

> cd application
> make CROSS=<CROSS>

OR 
 
> make -C application CROSS=<CROSS>

To build the TLM2.0 Platform
This requires that there are valid installations of SystemC and TLM2.0
available and that the buildsystem Makefiles, Makefile.TLM.platform.<OS>, 
found in Imperas/ImperasLib/buildutils are updated to refer to
the installed directories.

In the platform directory

Linux
> make -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.TLM.platform \
    PLATFORM=platform.cpp
    
Windows    
> mingw32-make -f %IMPERAS_HOME%/ImperasLib/buildutils/Makefile.TLM.platform ^
    PLATFORM=platform.cpp
    
RUNNING THE EXAMPLE ------------------------------------------------

Start the platform in a shell or Window the platform

> platform/platform.<OS>.exe application/application.<CROSS>.elf

Start in another shell or Window GDB for the OR1K

Linux
> Imperas/lib/${IMPERAS_ARCH}/CrossCompiler/or32-elf/bin/or32-elf-gdb

Windows
> Imperas/lib/${IMPERAS_ARCH}/CrossCompiler/or32-elf/bin/or32-elf-gdb.exe

Connect GDB to the processor running in the platform
NOTE: The <port number> is reported by the simulator when it boots.

Load file to debug and connect to the simulator

gdb> file application/application.<CROSS>.elf
gdb> target remote :<port number>

Set a break point at main and run the program

gdb> break main
gdb> continue

then run the program to completion and quit

gdb> continue
gdb> quit

