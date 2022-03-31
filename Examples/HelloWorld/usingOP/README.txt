 
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


File:Imperas/Examples/HelloWorld/usingOP/README.txt

INTRODUCTION -------------------------------------------------------
This example shows a simple Application which will print
    Hello World
to the console
This Application can be cross compiled to any supported processor type
or endian. This example includes a platform that is written to support ARM7TDMI,
RISCV32 and MIPS32 processor types.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/application.c
2. A CpuManager/OVPsim platform; this is found as platform/platform.c
3. A Makefile to build the application in 1; this is found as application/Makefile,
   In addition a standard Makefile is used to build the platform. This is included
   into platform/Makefile and is found at IMPERAS_HOME/ImperasLib/buildutils/Makefile.platform

BUILDING THE SIMULATION --------------------------------------------

> make -C application CROSS=RISCV32
This will build the application 'application.RISCV32.elf' for processor riscv, this is also
the default.

> make -C platform SRC=platform.c NOVLNV=1
This will build the platform 'platform.IMPERAS_ARCH.exe

if the value for 'CROSS' in the call to make the application is replaced with 
either IMG_MIPS32R2 or ARM7TDMI, the files which are built will change accordingly for use with
the processortype mips32 and arm respectively. 

These may then be run using the same platform by changing the processor type selected 
on the command line.

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.IMPERAS_ARCH.exe \
                            --program application/application.RISCV32.elf \
                            --processortype riscv

Alternative Processor Vendor
In some releases processor models may be provided by alternative vendors.
If the release being used has a processor model from a vendor not specified 
as the default supplied in the OVPsim installation it may be specified on 
the platform command line, as the final argument

> platform/platform.IMPERAS_ARCH.exe \
                            --program application/application.IMG_MIPS32R2.elf \
                            --processortype mips32 \
                            --alternatevendor mips.com 
