 
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


FILE:Imperas/Examples/Models/Peripherals/registerArrays/README.txt


INTRODUCTION -------------------------------------------------------

This directory contains an example described in the OVP Peripheral Modeling Guide.

This example illustrates generating arrays of registers in peripheral models. The

CONTENTS
application    : an application that responds to interrupts generated
harness        : a test harness that stimulates interrupt lines connected to interrupt controller
module         : the hardware definition; including processor, memory and interrupt controller
intc           : the peripheral model interrupt controller

BUILDING

Each item is built locally

>make -C application
>make -C harness    NOVLNV=1 
>make -C module     NOVLNV=1 
>make -C intc/pse   NOVLNV=1 

RUNNING
    The example uses a test harness to load a module (that defines the hardware), run an 
    application on the processor and stimulate the interrupt nets input to the interrupt 
    controller.

    In a Linux terminal or in a Windows MSYS shell use this command line
    
> harness/harness.${IMPERAS_SHRSUF}.exe --program application/test.RISCV32.elf
