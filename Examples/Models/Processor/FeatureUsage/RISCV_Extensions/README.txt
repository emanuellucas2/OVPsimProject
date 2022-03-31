

 Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com

 The contents of this file are provided under the Software License
 Agreement that you accepted before downloading this file.

 This source forms part of the Software and can be used for educational,
 training, and demonstration purposes but cannot be used for derivative
 works except in cases where the derivative works require OVP technology
 to run.

 For open source models released under licenses that you can use for
 derivative works, please visit www.ovpworld.org or www.imperas.com
 for the location of the open source models.



File:README.txt

INTRODUCTION -------------------------------------------------------

This example shows the use of specific extensions to the RISC-V processor.

It includes examples of the extensions
   Vector in directory vector
   Bit Manipulation in directory bitmanip


VECTOR EXTENSION ---------------------------------------------------
  This directory contains a number of examples executing the RISC-V 
  vector instruction set on the RISC-V processor using the RVB64I variant
  with additional extensions MAFDCV and SU added.
  
  The vector examples are all taken from the RISC-V Vector specification that
  conforms to the the model vector specification defined by vector_version=0.8

  Vector Examples ---------------------------------------------------
    The name follows either the specific name of the example or the 
    section number from which they were taken.  
        - memcpy
        - mixed-width-mask
        - 16.7
        - saxpy
        - 7.7
        - vector-vector-add
        - conditional
        - 6.4

  ELF Compilation ---------------------------------------------------
    These examples are provided pre-compiled. There are RISCV toolchains
    available that can be used to re-compile. A pre-compiled toolchain
    that supports v0.8 vector instructions may be obtained from the
    GitHub repository Imperas/riscv-toolchain branch rvv-0.8.x

  Running the Example -----------------------------------------------
    A script is provided RUN_VECTOR_EXAMPLE as both sh for Linux
    and bat for Windows hosts.
    The script configures the RISC-V processor for the variant RVB64I 
    with extensions MAFDCV and SU added and configures the vector 
    extension.
    When executed a list of the available ELF files to execute will be 
    provided and a selection should be made.
    By selecting an ELF file it will be loaded into the memory of the 
    virtual platform and executed by the RISC-V processor.

  Tracing the Instruction Execution ---------------------------------
    The simulator command line allows the instructions executed to be 
    traced.
    By enabling tracing the execution of the Vector instructions can 
    be observed.
    The standard command line arguments available to do this are
        --trace
        --tracechange
        --traceafter
        --tracecount
  
    For Example
     > RUN_VECTOR_EXAMPLE.sh --trace --tracechange




BIT MANIPULATION EXTENSION ------------------------------------------
  This directory contains a number of examples executing the RISC-V 
  bit manipulation instruction set on the RISC-V processor using the 
  RVB64I variant with extensions MAFDCB and SU added.

  Bit Manipulation Example ELF Files --------------------------------
    A few example assembler files have been provided to show the 
    execution of some of the available Bit Manipulation instructions.
        - bdep
        - clz
        - pcnt
        - bext
        - ctz

  ELF Compilation ---------------------------------------------------
    The Bit Manipulation examples are all compiled using the RISC-V 
    Cross Compiler toolchain provided as the riscv.toolchain package 
    from OVP World or Imperas.
    A Makefile is provided that will build all the Bit Manipulation 
    assembler files to ELF files.
    
    NOTE: The RISC-V Cross Compiler does not support the Bit Manipulation
    instructions which are added into the assembler files as literal 
    data values. The data values are define in the file extB.S.include. 
    

  Running the Example -----------------------------------------------
    A script is provided RUN_BITMANIP_EXAMPLE as both sh for 
    Linux and bat for Windows hosts.
    The script configures the RISC-V processor for the base variant 
    RVB64I with extensions MAFDC and other required parameters for 
    the Bit Manipulation extension.
    When executed a list of the available ELF files to execute will 
    be provided and a selection should be made.
    By selecting an ELF file it will be loaded into the memory of the 
    virtual platform and executed by the RISC-V processor.

    For Example
       > RUN_BITMANIP_EXAMPLE.sh
 
  Tracing the Instruction Execution ---------------------------------
    The simulator command line allows the instructions executed to be 
    traced.
    By enabling tracing the execution of the Bit Manipulation 
    instructions can be observed.
    The standard command line arguments available to do this are
        --trace        : Enable instruction tracing
        --tracechange  : Add reporting of changes to register values
        --traceafter   : Specify the instruction number from which to start the tracing
        --tracecount   : Specify the number of instructions to trace
  
    For Example
     > RUN_BITMANIP_EXAMPLE.sh --trace --tracechange
