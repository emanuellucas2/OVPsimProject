 
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


File:Imperas/Examples/HelloWorld/usingISS/README.txt

INTRODUCTION -------------------------------------------------------
This example shows the use if the Imperas Instruction Set Simulator (ISS)
which is the simplest way to run & debug software running on simulated
models of embedded processors.

It provides a simple Application which will print
    Hello World
to the console.

This Application can be cross compiled to any supported processor type
or endian.

The ISS is run with a simple command and takes many command line arguments.

FILES --------------------------------------------------------------
There are several parts to the example
1. An application; this is found as application/application.c
2. A Makefile to build the application; this is found as Makefile,
3. The ISS (selected with environment variable IMPERAS_ISS) provided in the 
   Imperas/OVP installation bin directory

COMPILING THE APPLICATION --------------------------------------------

> make -C application CROSS=RISCV32
This will build the application 'application.RISCV32.elf' for processor riscv, this is also
the default.

If the value for 'CROSS' in the call to make the application is replaced with, for example 
either IMG_MIPS32R2 or ARM_CORTEX_A, the files which are built will change accordingly for use with
the appropriate processor type.

RUNNING THE ISS ------------------------------------------------
The ISS can be either iss.exe or issdemo.exe, the version used is identified with 
the IMPERAS_ISS environment variable

The ISS can be run as in the following example:
> $IMPERAS_ISS --program application/application.RISCV32.elf --processortype RISCV32 --variant RV32I

Try some of the other processor families/variants.
Note that you need to install the appropriate cross compiler to compile the applications.

For example:
CrossCompiler       Package                         Processor               Variant
----------          ------------------              ------------            ----------
RISCV32             riscv.toolchain                 riscv                   RV32I
IMG_MIPS32R2        mips-mti.toolchain              mips32                  24KEf
ARM_CORTEX_A        armv7.toolchain                 arm                     Cortex-A9UP
AARCH64             armv8.toolchain                 arm                     Cortex-A72MPx1

> $IMPERAS_ISS --program application/application.RISCV32.elf --processortype riscv --variant RV32I

Note that in several cases you need to add the processor vendor, eg:
> $IMPERAS_ISS --program application/application.IMG_MIPS32R2.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 24KEf 

GETTING HELP ---------------------------------------------
Use:
> $IMPERAS_ISS --help
To get full help listing of all command line arguments.

Look in Examples/Demo/Processors for further examples.

#