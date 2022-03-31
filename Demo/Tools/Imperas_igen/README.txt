###############################################################################
# Imperas Generator (igen.exe) productivity tool
#  
# Creating 
#      Processor Model SystemC TLM2.0 Interface
#      Virtual Platform Definitions
#         Module    (OVP C API)
#         Platforms (OVP C API and SystemC TLM2.0)
#      Peripheral Model Template
#      Peripheral Model SystemC TLM2.0 Interface 
#      Extension/Intercept Library Template
#

###############################################################################
# Pre-requisites
###############################################################################

On Windows it is required that an installation of MSYS and MinGW are available.
The bin directories of these installations must be available on the Windows PATH
as certain utilities are required in this demo.

###############################################################################
# Purpose of Demo
###############################################################################

The Imperas Generator (iGen) can create C and SystemC TLM2.0 model 
representations of components from a description of the component or platform. 
This greatly increases productivity for the creation of models and platforms.

Further, output templates in C can be generated for Peripheral models and 
Extension/Intercept libraries. These templates can be compiled as generated and
immediately used within a simulation. This is of great use to generate a
peripheral that may not immediately require any behavior to be modeled 
i.e. it provides a set of registers that may be initialized, read or written.

###############################################################################
# Pre-requisites for Running Demonstration
###############################################################################
This demonstration will create a peripheral model template and also compile that
template to a shared object (pse.pse) that will allow the peripheral to be used 
within a module and platform.
In order for this compilation to complete the PSE Toolchain must be installed.

###############################################################################
# Component Library Structure
###############################################################################
The component templates are created into a source library and then compiled 
from here to create an output binary library. The library structure follows a
VLNV hierarchy, that is Vendor/Library/Name/Version
Vendor  : a unique identifier for the company creating the model, typically the 
          website e.g. ovpworld.org
Library : identifies a grouping of components e.g. peripheral
Name    : a unique name for the component
Version : a version e.g. 1.0

###############################################################################
# 2 Running IGEN
###############################################################################
Scripts are provided to launch the Imperas Generator tool, iGen.

These are provided prefixed with 'BUILD_'

The script uses a commands to define
1) the peripheral model register interface to create the C source and header 
   files for the peripheral.
2) the hardware definition as a module. A module can be executed as a virtual
   platform using the harness.exe or can be included, hierarchically, into 
   another module or a platform.
3) the hardware definition as a platform. A platform only change from a module is
   to include the Command Line Parser (CLP) which causes files containing a main
   to be generated that are compiled to an executable.
4) the extension/intercept library command structure and template.

A further script is provided prefixed with 'GENERATE_'

This script uses iGen to generate a SystemC TLM2.0 interface files for a processor
model. The processor is identified in the library by its VLNV and can be configured
using the variant parameter and overrides to generate an specific interface file.

###############################################################################
# 3 Running Simulation
###############################################################################
Scripts are provided to launch the Imperas simulator and execute a virtual 
platform that uses the generated peripheral, intercept library and module or platform.

These are provided prefixed with 'RUN_'

The scripts 
1) Use the harness.exe program to load the module
2) Execute the platform executable directly.

Both the module and platform are generated from the same hardware definitions. The
module + harness.exe provides the same virtual platform as the platform.
 
A script is provided prefixed with 'DEBUG_VIEW_' that will run a simulation 
under the Imperas Multi-Processor Debug (MPD) debug environment.
This loads and executes commands from a batch file, 'commands.mdb', that are used
to show the automatically generated programmers view for the peripheral model.
