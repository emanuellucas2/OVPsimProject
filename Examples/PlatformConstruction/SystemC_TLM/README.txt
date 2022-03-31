 
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


File:Imperas/Examples/PlatformConstruction/SystemC_TLM/README.txt

PREREQUISITES-------------------------------------------------------

It is assumed that you are familiar with SystemC.

If you are using a Windows environment, you will need to obtain 
and install MSYS

If you are using Linux you will need a gnu tool-chain (g++, ld etc) that
supports the SystemC distribution.

You will need to obtain and install SystemC.
    www.accellera.org/downloads/standards/systemc
    
You will need to obtain and install a toolchain for the processor.

INTRODUCTION -------------------------------------------------------
This example shows the use of OVP technology in a SystemC TLM2.0
environment. It is described in detail in the document "OVPsim Using OVP 
Models in SystemC TLM2.0 Platforms" available in the Imperas/doc directory of
this installation.

This example platform contains one processor.

FILES --------------------------------------------------------------
There are two parts to the example
1. The application; code which runs on the OR1K processor model;
   this is in application/main.c

2. The platform; this is in platform/platform.tlm.tcl and uses iGen to
   generate the source files (.cpp and .hpp) 
 

And scripts to build and run
        example.bat       Build and run for Windows
        example.sh        Build and run for Linux 
        

HOW IT WORKS --------------------------------------------------------------
    The example platform (hardware defined in platform.tlm.tcl) includes an
    OR1K processor model with memory and a uart peripheral. The test program
    runs through a loop writing characters to the uart. The uart raises an
    interrupt when each character is sent. The uart logs output characters 
    to a file
    
    The platform is executed using the command line:
        platform/platform.<IMPERAS_ARCH>.exe -program <application/application.<CROSS>.elf>
                   
The Cpu Model.
    $IMPERAS_HOME/ImpPublic/source/host/tlm/tlmProcessor.cpp
  and
    $IMPERAS_HOME/ImpPublic/include/host/tlm/tlmProcessor.hpp
    
  The TLM support code is built with other TLM support files into an archive tlm.a
  which is referenced by the environment variable IMPERAS_TLM_SUPPORT_ARCHIVE.
  If the environment variable or the TLM archive does not exist it is built 
  into the local directory tlmSupport.
  
  The processor is instantiated into the platform by a processor-specific C++ 
  interface which is in the tlm directory with the model source, in this case in
  ImperasLib/source/ovpworld.org/processor/or1k/1.0/tlm2/processor.igen.hpp
    
  Each processor runs in a SystemC thread which runs a certain number of instructions
  (with SystemC time 'frozen') then sleeps for a 'quantum'.
  The ratio of instructions per quantum to quantum duration gives the effective MIPS
  rating of the processor. The quantum itself controls the
  accuracy with which the processor will interact with other SystemC models; a shorter
  quantum gives better accuracy, but increases the simulation overhead. Note that
  this wrapper will only work with TLM blocking transactions.

  Interrupts are effected by calling a processor interrupt routine via a SystemC signal.
  An interrupt will cause the processor to finish the current instruction then branch
  to the interrupt routine as expected. The processor will still execute the correct
  number of instructions in the quantum.
  Note that since a SystemC thread is not normally interrupted, the only source that
  can interrupt a processor during its quantum is something affected by the processor 
  execution e.g. the processor accessing a model which raises the interrupt. An interrupt
  raised by another model or processor will be serviced next time the processor is 
  scheduled.
  
BUILDING THE PLATFORM ----------------------------------------------------------

The installation of OVPsim (www.ovpworld.org) provides this Example directory. 
In addition
  Obtain and install the cross compiler toolchain for the OR1K.
  Obtain and install MSYS and GNU toolchain
  Obtain SystemC and build it using MSYS.

It is required that the built installation for both SystemC (including TLM2.0) is available. 

Environment variable SYSTEMC_HOME is used by the Makefile to build the source
files to an executable. These should be set to the installation paths for SYSTEMC 
before attempting to re-compile.

Platform compilation is carried out in the platform_cpp directory.

The Makefile includes two standard Makefiles
  IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.igen     : Generate source files using iGen
  IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform : Compile source files to executable


In the Windows MSYS shell or a Linux shell use the Makefile to build
> make -C platform_cpp

Consistency in Libraries and Archives ---------------------------------------------

The SystemC library, the OP C++ library and the TLM archive must all be built using the same 
host toolchain version and settings.
If you get link errors it is often the case that there is an inconsistency and the SystemC 
and/or OP C++ library require to be re-built.

The OP C++ library is provided pre-built as IMPERAS_HOME/bin/IMPERAS_ARCH/libRuntimeLoader++.IMPERAS_SHRSUF
and it may be that this is consistent with your system and can be used directly.

To re-build the OP C++ library set the environment variable IMPERAS_OP_CPP_LIBRARY to a 
directory and a library name. A separate directory must be defined e.g. $(pwd)/opLib/libOP++.a

The TLM archive, by default is built into the local directory tlmSupport/tlm.a. However, if you
wish to use a common or pre-built archive set the environment variable IMPERAS_TLM_SUPPORT_ARCHIVE to a 
directory and an archive name. A separate directory must be defined e.g. $(pwd)/tlmSupport/tlm.a

The directory containing the OP C++ library must be specified on the LD_LIBRARY_PATH or the PATH 
environment variable for Linus or Windows respectively so that it can be found by the executable.
 

BUILDING THE APPLICATION ----------------------------------------------------------

The application program int.elf is built using a Makefile in the application 
directory. This will also require that the OR1K toolchain has been downloaded
and installed.

In a MINGW/MSYS shell on Windows or at a Linux prompt go to the application directory
and type
> make -C application

RE-BUILDING THE PLATFORM -----------------------------------------------------------
To clean and rebuild the platform the 'clean' target should first be used to remove
the current files and then make can be used again to build the platform from the
iGen input file.

> make -C platform_cpp clean
> make -C platform_cpp

RUNNING THE PLATFORM ---------------------------------------------------------------

To run the platform
> platform_cpp/platform.<ARCH>.exe -program application/int.OR1K.elf
