###############################################################################
    Date : 20211231                        Version : 20211118.0
###############################################################################

Welcome to the README for Imperas and Open Virtual Platforms installations.

**
If you have installed the OVP or Imperas products 
Please go to -> doc/index.html with a web browser for full documentation.

If you have installed stand-alone demos then the documentation will not be available
in this installation. Please visit www.ovpworld.org->documentation

You should initially read the "Installation and Getting Started Guide" found in Imperas/doc 
**

--------------------------------------------------------------------------------
-- Linux Installation from Self Extracting Packages
--------------------------------------------------------------------------------
To Install under Linux, run the self extracting packages these will be files of the form:

    <Package>.<Release Major>.<Release Minor>.<Host Architecture>.exe

where
  <Release Major> is the major release number of the product
  <Release Minor> is the minor release number of the product
  <Package> is the name of a package to install.
  <Host Architecture> is either Linux32 or Linux64, host architecture dependent.

For Example,
    OVPsim.20211118.0.Linux32.exe
    Imperas_SDK.20211118.0.Linux64.exe
    mips32.toolchain.20211118.0.Linux32.exe

NOTES:
  1. Releases with the same <Release Major> version support compatible versions of the public APIs.
  2. 64-bit Host packages are only available to download from Imperas.

It may be required to make the packages executable, this can be done using the command

  % chmod +x <Package>.<Release Major>.<Release Minor>.<Host Architecture>.exe

When you run the self extracting packages, depending upon the licensing restrictions of the
packages, you may be prompted to agree to the terms and conditions, failure to do so will
result in a failure to extract the package.

--------------------------------------------------------------------------------
-- Installation Directory
--------------------------------------------------------------------------------
Imperas or OVP are installed (by default) into a directory of the form 

	/home/user1/Imperas.<Release Major>

where <Release Major> is the Major release number of the product, e.g. __IMPERAS_MAJOR_VERSION__ 

Created in this directory is the file InstallLog.txt that will list the components and packages 
that have been successfully installed.

--------------------------------------------------------------------------------
-- Execution Environment
--------------------------------------------------------------------------------
It is required that the following environment variables are set:
  IMPERAS_HOME    is the root of the Imperas installation
  IMPERAS_ARCH    should be set to Linux32 or Linux64 (host architecture dependent)
  IMPERAS_UNAME   should be set to Linux
  IMPERAS_SHRSUF  should be set to so
  IMPERAS_VLNV    is the root of the component model library
  PATH            is updated with the library and binary directories of the installation
  LD_LIBRARY_PATH is set to the runtime library directory
  LM_LICENSE_FILE is set to point at the license file or port of the server if using
                  a license server

  IMPERAS_ISS     selects the version of the Imperas ISS that is used, iss.exe or 
                  issdemo.exe (requires no license but is limited)

  IMPERAS_RUNTIME this is the simulator runtime library which can be the OVPsim 
                  simulator, or CpuManager the Imperas Professional Simulator.

This environment setup can be done by sourcing a script, which is supplied, in 
bash shell and executing a function as follows

  % source Imperas.__IMPERAS_MAJOR_VERSION__/bin/setup.sh
  % setupImperas <Full PATH>/Imperas.__IMPERAS_MAJOR_VERSION__

This should set the following variables
  IMPERAS_HOME=<install directory>/Imperas.__IMPERAS_MAJOR_VERSION__
  IMPERAS_ARCH=Linux32 (or Linux64)
  IMPERAS_UNAME=Linux
  IMPERAS_UNAME=so
  IMPERAS_VLNV=$IMPERAS_HOME/lib/$IMPERAS_ARCH/ImperasLib
  PATH=$PATH:$IMPERAS_HOME/bin/$IMPERAS_ARCH
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMPERAS_HOME/bin/$IMPERAS_ARCH:$IMPERAS_HOME/lib/$IMPERAS_ARCH/External/lib


  IMPERAS_PERSONALITY MUST also be set to configure the Imperas Professional Simulator.

When installing the Imperas products the setup of this environment variable 
will be requested by the installer.

This can also be done by sourcing a script, which is supplied, in a bash shell and
executing a function as follows

  % source Imperas.__IMPERAS_MAJOR_VERSION__/bin/selectPersonality.sh
  % selectPersonalityImperas


--------------------------------------------------------------------------------
-- Setup License
--------------------------------------------------------------------------------
An OVPsim license can be obtained from the OVP website and copied into the file
   Imperas.__IMPERAS_MAJOR_VERSION__/OVPsim.lic

If saved into a different location or if using a floating license from a server 
the license to use is defined by 
   LM_LICENSE_FILE or IMPERASD_LICENSE_FILE

  For an OVPsim static license this should be set as follows
    export LM_LICENSE_FILE=$LM_LICENSE_FILE:/path/to/license/file.lic

  For an Imperas floating license this should be set to the port on the server
  as follows
    export LM_LICENSE_FILE=2700@host-ip_address

--------------------------------------------------------------------------------
-- Simulator Runtime Selection
--------------------------------------------------------------------------------
The simulator runtime is loaded according to IMPERAS_RUNTIME, this may be NULL 
or set to one of the simulators available. The setting for IMPERAS_RUNTIME could
be
  NULL       : Selects OVPsim simulator
  OVPsim     : Selects OVPsim simulator
  CpuManager : Selects CpuManager, Imperas Professional, simulator

At runtime the simulator dynamic link library is loaded into the platform. By default
the OVPsim simulator is loaded from libOVPsim.so. 
It is possible to select an alternative simulator such as CpuManager provided with the 
Imperas Professional Tools by setting an environment variable IMPERAS_RUNTIME. 
This can be done in an MSYS shell, for example
> export IMPERAS_RUNTIME=CpuManager

--------------------------------------------------------------------------------
-- Simulator Personality Selection (Imperas Professional Products)
--------------------------------------------------------------------------------
The environment variable IMPERAS_PERSONALITY is used with the Imperas Developer 
and SDK products or other specific products to modify the behaviour and features of
the simulator. This also modifies the license feature(s) required.
There are four options available; Controller, Standard and Multi in the Developer 
Product and SDK that have specific feature sets available to them.
The personality is selected using the IMPERAS_PERSONALITY environment variable.
The Imperas professional simulator personalities are
   Controller | CPUMAN_CONTROLLER | C*DEV 
   Standard   | CPUMAN_STANDARD   | S*DEV
   Multi      | CPUMAN_MULTI      | M*DEV
   SDK        | CPUMAN_MULTI      | M*SDK

The personality can be selected using the selectPersonalityImperas function as follows 

  % selectPersonalityImperas

--------------------------------------------------------------------------------
-- Setup for a 32-bit product installation on a 64-bit Host machine
--------------------------------------------------------------------------------
It is possible to run a Linux32 product installation on a 'Linux64' host if 32-bit 
compatibility libraries are available on the host machine. To setup the environment 
in the current shell the setupImperas function may be used as follows

  % setupImperas <install directory>/Imperas.__IMPERAS_MAJOR_VERSION__ -m32

--------------------------------------------------------------------------------
-- Obtaining a License to run the OVPsim Simulator / iGen model building wizard
--------------------------------------------------------------------------------
A free demonstration/evaluation license to run the OVPsim simulator / iGen model
building wizard may be obtained from the downloads page of the OVPworld website,
under the heading 'Obtaining a license key' 

Once you have your license key you should, either
1. Place it on your machine and point to it using the environment variable
   IMPERASD_LICENSE_FILE (or add to LM_LICENSE_FILE), or
2. Place the license data in the default file found, for example, at 
   Imperas.__IMPERAS_MAJOR_VERSION__/OVPsim.lic

CAUTION: If using the default location in the Imperas installation this will be 
overwritten if a new installation is carried out or deleted if an installation 
is uninstalled. 

--------------------------------------------------------------------------------
-- Installation Information
--------------------------------------------------------------------------------
Below we describe the different installations you can have performed on this machine.
It describes the directory and file structure for a full download.
If you have not downloaded everything, then you may not have all the files present.

You can install the Imperas products and OVP in the same place and they are designed to co-exist.

For OVP please go to www.ovpworld.org/download.php, register, login, and download what you need.
Any questions - please ask in the ovpworld forums, or email us at info@ovpworld.org.

For Imperas products, please contact Imperas info@imperas.com for product information.

--------------------------------------------------------------------------------
-- Model Source Code
--------------------------------------------------------------------------------
The model source code is provided in the source library provided as part of a 
FULL OVP or Imperas product installation. It is not provided with demo example 
installation packages. Note that some models do not include source code.

The library is found at IMPERAS_HOME/ImperasLib/source
The library (source and binary) is structured as Vendor/Library/Name/Version (VLNV)  
Rebuilding of individual components or the complete library is carried out using the build 
system, files for which are found in IMPERAS_HOME/ImperasLib/source/buildutils

The source model consists of a model directory containing the source and a tlm
directory containing the TLM2.0 interface for the OP API.

For further information please consult the Installation and Getting Started guide 

--------------------------------------------------------------------------------
-- OVP Fast Processor Model Variant Documentation
--------------------------------------------------------------------------------
An OVP Fast Processor Model will normally support several variants. For example,
the 'arm' model supports ARM7TDMI, Cortex-A9MPx4, Cortex-A53MP etc, the 'mips32'
model supports 74Kc, 1004Kf, M14K etc.
Each variant has a document to provide it's specific configuration. These are 
found with the processor model source in a doc directory parallel to the model
source directory within the VLNV. For example, the V850E2 variant documentation
is found at

  Imperas.__IMPERAS_MAJOR_VERSION__/ImperasLib/source/renesas.ovpworld.org/processor/v850/1.0/doc/OVP_Model_Specific_Information_v850_V850E2.pdf

--------------------------------------------------------------------------------
-- Product Licenses
--------------------------------------------------------------------------------
Licenses
    IMPERAS_LICENSE
    OVP_IMPERAS_LICENSE
    OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0
-----------------------------------------------
The software and contents of this directory tree are covered by one or more Software License Agreements. 
For OVP you will have accepted OVP click through license to have unpacked these files. The SLA is 
contained in the file: OVP_IMPERAS_LICENSE, available in txt, rtf and pdf formats.
For the Imperas Professional products you will have a signed license agreement that covers your usage 
of the Imperas commercial products, that is contained in IMPERAS_LICENSE, available in txt, rtf and
pdf formats.
The model source code is provided under a modified Apache 2.0 license contained in the 
file OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf

--------------------------------------------------------------------------------
-- Demos
--------------------------------------------------------------------------------
This is where the self contained demos live.
Some Demos are installed as part of the main packages, such as Demo/Processors and 
some are installed by specific packages, for example: 
Demo/Platforms/FreeRTOS_arm
If you go into these directories, you will find a README.txt/.html which explains what 
is in that directory and how to run it. There will be source files of applications 
and platform, executables, and a .jpg showing the structure of the demo platform etc.

--------------------------------------------------------------------------------
-- Documentation - doc (installed as part of OVPsim, and Imperas)
--------------------------------------------------------------------------------
There is an index.html file that is the starting point of our Browser based documentation.
Click your browser on doc/index.html to look at the documentation.
There are .pdf user and reference guides, and .html API documentation created from the .h 
files using Doxygen.

--------------------------------------------------------------------------------
-- Examples
--------------------------------------------------------------------------------
This is where the OVP and Imperas examples live. You will find examples of simple 
platforms, simple benchmarks / applications and Makefiles etc to build them.
For Imperas installations you will also find here examples of debugging with the 
Imperas Multicore Debugger and also the Imperas Verification/Analysis/Profiling tools.

Examples/HelloWorld - the simplest example as several sub directories to show different forms.
    There are examples of usage of harness.exe, iss.exe, C, SystemC, etc.
Examples/PlatformConstruction - a directory for each example of building platforms
    Several of these examples use C or C++ directly, and several use the Imperas iGen 
        product to generate the platform.
Examples/SimulationControl - a directory of examples using OP and harness.exe to control simulations
Examples/Models/Processors - a directory for each example of building a processor with VMI
Examples/Models/Peripherals - a directory for each walked through peripheral model using BHM/PPM
Examples/Vap  - a directory of examples of using the Imperas VAP tools
Examples/PlatformsICM - a directory for each example of building platforms using ICM (deprecated)

--------------------------------------------------------------------------------
-- ImperasLib (for Imperas created model source files)
--------------------------------------------------------------------------------
For library components shipped as source (created by Imperas):
ImperasLib\source\imperas.com\peripheral
ImperasLib\source\imperas.com\processor (empty until open source released)

--------------------------------------------------------------------------------
-- lib (for binaries)
--------------------------------------------------------------------------------
For library components shipped as binaries (created by Imperas):
lib\<Host Architecture>\ImperasLib\imperas.com\peripheral\
lib\<Host Architecture>\ImperasLib\imperas.com\processor\
lib\<Host Architecture>\ImperasLib\imperas.com\semihosting\

For Cross Compiler components to build applications etc:
lib\<Host Architecture>\CrossCompiler
lib\<Host Architecture>\TargetLibraries\

--------------------------------------------------------------------------------
-- bin
--------------------------------------------------------------------------------
This is where the binaries of the simulator and its libraries live.
Other utility programs are also put here.

bin/<Host Architecture>/imperasOVP_versionCheck.exe

This release includes a feature which will access the OVPworld website to see if
a newer version of the simulator is available. Your accessing of the OVPworld 
website is recorded. If you wish to disable this feature, after installation 
please delete the executable from the installation Directory, the executable
 to remove is called :-
    "imperasOVP_versionCheck.exe"

--------------------------------------------------------------------------------
-- cfg
--------------------------------------------------------------------------------
used during build/release process - ignore


--------------------------------------------------------------------------------
-- Change Logs
--------------------------------------------------------------------------------
These documents detail the recent changes made to the Imperas / OVP products
since the last release. The contents of the files cover:
  CHANGELOG.SDK.txt        : Imperas Professional Product M*SDK
  CHANGELOG.iGen.txt       : Imperas Model Framework Generator
  CHANGELOG.CpuManager.txt : Imperas Professional Simulator M*SIM
  CHANGELOG.OVP.txt        : OVP Products
  CHANGELOG.eGui.txt       : Eclipse based eGui

--------------------------------------------------------------------------------
Uninstall
--------------------------------------------------------------------------------
To uninstall the installed OVP and Imperas products remove the installation 
directory Imperas.__IMPERAS_MAJOR_VERSION__

 ** WARNING **
This will remove all files here and below - including any that you have created.
We suggest you do NOT put any modified files in this directory or tree.
Our suggestion is always copy Examples etc into your own working directories
and when creating your own models do so in a separate VLNV library separate from 
an installation.

--------------------------------------------------------------------------------
-- Product Testing
--------------------------------------------------------------------------------
Testing is carried out on 
  Linux32 Fedora Core version 12 (2.6.31.5-127.fc12.i686 #1 SMP Sat Nov 7 21:41:45 EST 2009 i686 i686 i386 GNU/Linux)
  Linux64 Fedora Core version 18 (3.8.5-201.fc18.x86_64 #1 SMP Thu Mar 28 21:01:19 UTC 2013 x86_64 x86_64 x86_64 GNU/Linux)

(README.Linux.txt v1.15)
##

