FreeRTOS_arm

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show the FreeRTOS operating system can be used on the
OVP ARM Cortex-M3 processor model.

The simulation executables were compiled using 
MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# FreeRTOS Operating System
###############################################################################
This demo is executing a compiled version of FreeRTOS ported to the 
ARM Cortex-M3 processor.

For operating system source and further information please view the FreeRTOS
website www.freertos.org

###############################################################################
# Running the simulation
###############################################################################
The simulation is executed from one of the following directories:
  harness    : this executes the C API version of the virtual platform
  harnessTLM : this executes a SystemC TLM version of the virtual platform

Launch the simulation platform by double clicking 'RUN_FreeRTOS.bat' in a Windows
explorer or execute the script 'RUN_FreeRTOS.sh' in a Linux shell or Windows MSYS
shell.

The simulation will start and a UART Console will be launched. 

The UART Console will print messages and a representation of the LED state will
be printed into the simulation terminal. 

The simulation will continue indefinitely but can be terminated by closing the
UART console.

Statistics will be printed upon completion of the simulation.

NOTE:
The processor MIPS rate is reduced to 12 MIPS to allow the changes to the
output to be observed.

###############################################################################
# Application, Module and TLM Platform
###############################################################################

Application -------------------------------------------------------------------

Source found in the directory 'Application' is based upon example code provided
by FreeRTOS to show a minimal system executing. This creates an application 
using the FreeRTOS operating system release version 7.1.1

This is a simple application that creates two tasks and uses the crflash.c 
co-routines.
Each task, Task One and Task two, will relinquish control for a period of time
and then when re-scheduled will access an 'LED' register to toggle the LED state.

The 'LED' access is provided by code in the BoardSupportPackage directory.

The application can be rebuilt using the provided Makefile. This uses the 
FreeRTOS source, version 7.1.1, that is provided with this example.

Platform ----------------------------------------------------------------------

The platform instantiates an ARM Cortex-M model (OVP armm model configured 
as a Cortex-M3) and a peripheral model that provides a single register to control
a bank of LEDs.

###############################################################################
# Re-Building Application and Platform
###############################################################################
         
In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or either of the Imperas Professional Tools M*SDK 
or M*DEV 'Imperas' packages.
The 'OVPsim' installer is OVPsim.<major version>.<minor version>.<OS>.exe
The 'Imperas' installers are Imperas_SDK.<major version>.<minor version>.<OS>.exe
and Imperas_DEV.<major version>.<minor version>.<OS>.exe

Application -------------------------------------------------------------------

The provided Makefile and linker script (standalone.ld) in the FreeRTOS directory
can be used to rebuild the FreeRTOS demonstration application.

> make -C Application
or 
> cd Application
> make

Module ----------------------------------------------------------------------

The module contains the hardware definition and is found in the 'module' 
directory in this demo.
This is a copy of the module definition that is contained in the VLNV library 
at VLNV imperas.ovpworld.org/platform/ArmCortexMFreeRTOS/1.0

Building of the module is carried out using the standard Makefile provided in 
either a Linux or an MSYS/MinGW shell.

For Example to re-build the module, the following can be used

> make -C module NOVLNV=1
or
> cd module
> make NOVLNV=1

TLM Platform  ----------------------------------------------------------------

The TLM platform includes the module definition of the hardware definition and
also the standard command line parser to generate an executable. It is found
in the 'harnessTLM' directory in this demo.

Building of the TLM platform is carried out using the standard Makefile provided
in either a Linux or an MSYS/MinGW shell.

For Example to re-build the TLM platform, the following can be used

> make -C harnessTLM NOVLNV=1
or
> cd harnessTLM
> make NOVLNV=1
          
###############################################################################
# Using with Imperas Eclipse (eGui)
###############################################################################
The FreeRTOS kernel may be debugged using the Imperas Eclipse (eGui). The package
eGui_Eclipse must be installed.

Please see the additional README file, README.EGUI.txt, for full instructions
