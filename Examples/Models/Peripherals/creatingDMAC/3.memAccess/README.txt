 
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


FILE:Imperas/Examples/Models/Peripherals/creatingDMAC/3.memAccess/README.txt


INTRODUCTION -------------------------------------------------------

This directory contains an example described in the OVP Peripheral Modeling Guide.

Please see the file creatingDMAC/INFORMATION.README.txt for further information

This example adds memory access using master ports.

RUNNING THE EXAMPLE -----------------------------------------------

Building

>make -C application
>make -C module           NOVLNV=1 
>make -C peripheral/pse   NOVLNV=1 

Running
    The example uses the harness.exe program to load and execute a module that
    defines the hardware.

    In a Linux terminal or in a Windows MSYS shell use the following command line
    
> harness.exe --modulefile module/model.${IMPERAS_SHRSUF} --program application/dmaTest.RISCV32.elf
