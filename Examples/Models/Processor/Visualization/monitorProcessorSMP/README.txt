 
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


RUNNING THE EXAMPLE -----------------------------------------------

This example is based on the 
    Imperas\Demo\Platforms\uKernel_arm_Cortex-A9MPx4 demonstration.
    There are instructions for this demo included below.
    
Binary Intercept Libraries
    The monitoring of the processor and the power button are loaded from the
    ImperasLib imperas.com/intercept libraries: processorMonitorHttpvis, and
    powerButtonHttpvis.
    
Running the example
    The example is run using the shell script (example.sh/.bat).
    
    You will be asked if you want to run the browser to see the visualization.
    
    You can run any browser if you connect it to the correct machine/portnumber. The
    portnumber is specified in the run script (example.sh/.bat).
    
    Note that this examples uses the Imperas harness.exe program and a pre-built
    module from the ImperasLib. The application (cli.axf) is also provide 
    pre-built.
    
HTML File
    There is a also the visualization.html file. This is really a template so you 
    can see how to run up the visualization with your own page style.
    Note it defines the portnumber(s) to use (these are defined in the
    example.sh/.bat file.
    
    You start the simulation, until it has opened the HTTP port(s), and then you 
    load this file in your browser and it should connect to the opened HTTP
    port(s) in the simulator.
    
Image showing platform configuration
    There is a .jpg file in this directory which shows a picture of the module
    and configuration of the example being run.

INSTRUCTIONS FOR THE CLI 
-----------------------
Taken from Imperas\Demo\Platforms\uKernel_arm_Cortex-A9MPx4/README.txt

Instructions for running the demo (using the provided command line)

This directory contains a copy of the ARM MPCore Boot and 
Synchronization Example Code (cli.axf) running on a platform that 
instantiates a 4 core ARM Cortex-A9 with a UART for communication.

OBTAINING SOURCE AND BUILDING APPLICATION CLI.axf -------------------

The Command Line Interface (CLI) example code is used in this demo.

The source of the uKernel was obtained from 
http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php

It is built using the ARM DS-5 toolsuite on a Linux host platform 
(installation DS500-BN-00004-r5p0-05rel0/ds5_d966_Linux)

Setup Arm DS-5 Tools by adding the binary directory of the installation 
to the PATH and locating a valid license key

It is then possible to build using the following commands (these example 
commands shown are for a Linux host)

> make TARGET=CORTEXA9 NUMCPUS=4 cli RVCT40BIN=1

NOTE: The definition 'RVCT40BIN=1' was added as the software provided by 
ARM contained a Makefile expecting that the toolchain used to build 
would be RVCT version 4.0 and checked for this variable. Rather than 
modifying the Makefiles we added the definition.  

RUNNING THE DEMO ----------------------------------------------------

Start the simulation using the RUN_* script. 
A console will be started with a connection made to the simulation 
platform.

You should see output such as
 
Serial channel initialized.

    ------------------------------------------------
    ARM MPCore Boot and Synchronization Example Code
    ------------------------------------------------
    Built Jun 24 2011 13:02:59

    Number of CPUs: 4
    Level 1 cache: ON
    Level 2 cache: OFF
    Snoop Control Unit: ON
    Primary GIC: ON
    Secondary GIC: ON
    ------------------------------------------------

    CORTEXA9>

The command set of this program that are used in this example are:

   h            : Print the previously used commands
   infinite     : Never exiting thread
   ver          : Print version and build date
   ps           : Print snapshot of currently active threads
   ls           : Print list of available commands
   kill         : Cancels a job

NOTE: No other commands are supported.

Use the command "infinite &" to start a number of infinite programs running
followed by the "ps" command to show on which processor cores they are 
running. When you are running more 'infinite' programs than there are CPUs 
available subsequent 'ps' commands will show 'main' moving between the 
cores.

Output such as the following should be seen on subsequent 'ps' commands.

     CORTEXA9> ps
    
      TID   CPUID  SLEEPING DETACHED  DESCHEDULED  CANCELLED       THREAD
        2     0        N       Y          N            N           infinite
       16     1        N       N          N            N               main
        3     2        N       Y          N            N           infinite
        0     3        N       Y          N            N           infinite
        1   queued     N       Y          N            N           infinite
       17   queued     N       N          N            N              dummy
       18   queued     N       N          N            N              dummy
       19   queued     N       N          N            N              dummy
    CORTEXA9> ps
    
      TID   CPUID  SLEEPING DETACHED  DESCHEDULED  CANCELLED       THREAD
       16     0        N       N          N            N               main
        0     1        N       Y          N            N           infinite
        2     2        N       Y          N            N           infinite
        1     3        N       Y          N            N           infinite
        3   queued     N       Y          N            N           infinite
       17   queued     N       N          N            N              dummy
       18   queued     N       N          N            N              dummy
       19   queued     N       N          N            N              dummy
    CORTEXA9>


PLATFORM FILE -------------------------------------------------------
The harness.exe program is used to load the module ArmuKernel (that defines
 the components and connectivity)from the VLNV library as
    imperas.ovpworld.org/module/ArmuKernel

