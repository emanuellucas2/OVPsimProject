
var dataExists = 1; // must exist and be set to 1

var pageTitle = "OVP LOCAL Documentation";
var documentName = "the OVP Products";
var headerGraphic = "doc_header.gif";

var img = "<img src=../inc/link.png height='10' border='0'>";

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();
var secGroupTitle = new Array();

var z = 0;

secGroupTitle[z]  = "INTRODUCTION";

secTitle[z] = "Installation, Getting Started with OVP, and Cross-Compiling Applications";
secDescr[z] = "<a href=../Imperas_Installation_and_Getting_Started.pdf> Imperas_Installation_and_Getting_Started.pdf"+" "+img+"</a> ";
secDescr[z] += "<br/><b>Contents:</b><br/>Initial readme and installation notes.<br/>Where and how to get MinGW (Minimalist Gnu system for Windows) and MSYS shell.<br/>How to download and install the different processor toolkits from the OVPworld.org site.<br/><b>Cross Compiling Applications</b> for the different processors (GCC etc).<br/>An introduction to Compiling platforms & harnesses written with the OVP OP API.<br/>Loading applications to run on embedded processor models.<br/>Putting it all together with an application running on an OVP platform.<br/>A more detailed look at cross compiling applications on Windows.";
z++;
secTitle[z]  = "Imperas Tools Overview";
secFile[z]  = "Imperas_Tools_Overview.pdf";
secDescr[z]  = "<b>Contents:</b>";
secDescr[z] += "<br/>The Imperas simulators and their differences.";
secDescr[z] += "<br/>Debug, verification, and productivity tools.";
z++;

secGroupTitle[z]  = "CREATING AND USING PLATFORMS IN C / C++";
secTitle[z] = "Creating Platforms / Modules in C with OP API";
secFile[z]  = "Writing_Platforms_and_Modules_in_C_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b>";
secDescr[z] +="<br/>Discussion of different approaches to platform construction.";
secDescr[z] +="<br/>Introduction to different simulation environments.";
secDescr[z] +="<br/>Usage of Doxygen API reference documentation.";
secDescr[z] +="<br/>Combining Test Harness and platform in one file.";
secDescr[z] +="<br/>C Harness and separate platform approach.";
secDescr[z] +="<br/>Introducing modules and platform hierarchy.";
secDescr[z] +="<br/>Using harness.exe to simulate modules.";
z++;

secTitle[z] = "OVP OP (OVP Platforms) C API Doxygen Documentation";
secDoxygen[z] = "../api/op/html/index.html";
secFile[z] = "Doxygen OP C APIs : C Function Reference from headers.";
secDescr[z] = "Browsable walk through the OP C APIs header file and examples as hyperlinked documentation.";
z++;


//secTitle[z] = "Creating & Using Platforms and Models in C++ with OP API";
//secFile[z]  = "Writing_and_Using_Platforms_and_Models_in_CPP_User_Guide.pdf";
//secDescr[z] = "<b>Contents: (DOCUMENT UNDER CONSTRUCTION)</b>";
//secDescr[z] +="<br/>Introduction to platform construction using C++.";
//secDescr[z] +="<br/>Controlling platforms using C++.";
//secDescr[z] +="<br/>Usage of Doxygen C++ API reference documentation.";
//z++;

//secTitle[z] = "OVP OP (OVP Platforms) C++ API Doxygen Documentation (Not Yet Released)";
//secDoxygen[z] = "../api/opcpp/html/index.html";
//secFile[z] = "Doxygen OP C++ APIs : C++ Function Reference from headers.";
//secDescr[z] = "Browsable walk through the OP C++ APIs header file and examples as hyperlinked documentation.";
//z++;

secTitle[z] = "Using OVP models with OSCI SystemC TLM2.0 platforms";
secFile[z] = "OVPsim_Using_OVP_Models_in_SystemC_TLM2.0_Platforms.pdf";
secDescr[z] = "<b>Contents:</b><br/>Using OVPsim running with a SystemC TLM2.0 platform. <br/>Compiling the TLM2.0 examples with OVP models.<br/>Instancing fast OVP CPU models in a TLM2.0 platform.<br/>SystemC TLM2.0 platform construction, stack size, DMI, and simulation artifacts.<br/>Using OVP Peripheral models in TLM2.0 platforms.<br/>Detailed workthrough of example platform.<br/>Common problems.";
z++;

secGroupTitle[z]  = "CREATING PLATFORMS AND MODELS WITH IGEN WIZARD";

secTitle[z] = "iGen Productivity tools and files";
secFile[z]  = "iGen_Model_Generator_Introduction.pdf";
secDescr[z] = "<b>Contents:</b>";
secDescr[z] += "<br/>Overview and Installing iGen.";
secDescr[z] += "<br/>iGen Command Line Arguments and Listing all iGen API Functions.";
secDescr[z] += "<br/>Using Libraries and VLNV.";
secDescr[z] += "<br/>Creating Components: Testbench, Harness, Platform, Modules.";
secDescr[z] += "<br/>Creating peripheral model, processor model, extension library templates.";
secDescr[z] += "<br/>Creating MMCs.";
secDescr[z] += "<br/>Writing SystemC TLM2 interface layers.";
secDescr[z] += "<br/>Full list of iGen Command Line Arguments.";
secDescr[z] += "<br/>All iGen API calls.";
z++;

secTitle[z] = "iGen Platform Generator Wizard";
secFile[z]  = "iGen_Platform_and_Module_Creation_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b>";
secDescr[z] += "<br/>Compiling examples, shared objects and executables.";
secDescr[z] += "<br/>Platforms, Modules and shared objects.";
secDescr[z] += "<br/>Simulating Modules using <b>harness.exe</b>.";
secDescr[z] += "<br/>Describing virtual platform hardware and the design hierarchy.";
secDescr[z] += "<br/>A first simulation, defining the platform and controlling it.";
secDescr[z] += "<br/>How to use iGen.";
secDescr[z] += "<br/>How to use harness.exe.";
secDescr[z] += "<br/>Creating a module with a peripheral (a UART).";
secDescr[z] += "<br/>Adding nets.";
secDescr[z] += "<br/>Changing processor being instanced.";
secDescr[z] += "<br/>Static and Dynamic bridges, aliased address regions.";
secDescr[z] += "<br/>Byte swapping (endian correction).";
secDescr[z] += "<br/>Two processors and shared memory.";
secDescr[z] += "<br/>MMC operation, creation, and use.";
secDescr[z] += "<br/>Module Hierarchy.";
secDescr[z] += "<br/>Passing parameters, buses, nets down the hierarchy.";
secDescr[z] += "<br/>Using VLNV or direct paths to store your components.";
secDescr[z] += "<br/>Loading programs into designs.";
secDescr[z] += "<br/>Setting Model Parameters and control of models.";
secDescr[z] += "<br/>Advanced information and usage of iGen.";
secDescr[z] += "<br/>iGen error messages.";
z++;

secTitle[z]  = "iGen Peripheral Generator Wizard";
secFile[z]  = "iGen_Peripheral_Generator_User_Guide.pdf";
secDescr[z]  = "<b>Contents:</b>";
secDescr[z] += "<br/>Using TCL and the iGen tool to generate a Peripheral Template and SystemC interface file.";
secDescr[z] += "<br/>The template C and Header files can be compiled to create a model instance.";
secDescr[z] += "<br/>The model can be used (basic register read/write behaviour included in template) in an OP C or SystemC platform.";
z++;

secTitle[z]      = "iGen Platform, Module, and Peripheral Command API Documentation";
secFile[z]  = "Platform, Module, and Peripheral Command Reference from Headers";
secDoxygen[z]    = "../api/igen/html/index.html";
secDescr[z]      = "Browsable walk through of the iGen Platform, Module, and Peripheral Commands.";
z++;

secGroupTitle[z]  = "ADDING VISUALIZATION TO VIRTUAL PLATFORMS";
secTitle[z] = "Visualization used in Virtual Platforms";
secFile[z]  = "Visualization_for_Platforms_Modules_Peripherals_and_Intercept_Libraries.pdf";
secDescr[z] ="User guide illustrating how visualization can be included into Virtual Platforms and generated from hardware descriptions in Platforms and Modules, from peripheral component descriptions or by using Imperas binary interception technology.";
secDescr[z] += "<br/><b>Contents:</b>";
secDescr[z] +="<br/>Turning Visualization on/off.";
secDescr[z] +="<br/>Creating Visusalization peripherals, harness, module and binary intercept libraries.";
secDescr[z] +="<br/>Using existing plugins at run time.";
secDescr[z] +="<br/>Explanation and list of provided examples.";
secDescr[z] +="<br/>Reference on Imperas Visualization Infrastructure.";
secDescr[z] +="<br/>Classes, images, Javascript code.";
secDescr[z] +="<br/>Constructors, get and post callbacks.";
secDescr[z] +="<br/>List of visualization classes.";
secDescr[z] +="<br/>Common problems.";
z++;

secGroupTitle[z]  = "RUNNING SIMULATIONS";
secTitle[z] = "An Introduction to Simulation for OVP and Imperas users";
secFile[z]  = "Simulation_Control_of_Platforms_and_Modules_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b>";
secDescr[z] +="<br/>Simulating Modules using harness.exe.";
secDescr[z] +="<br/>Imperas Simulation Overview.";
secDescr[z] +="<br/>Separation of iGen modules and C harness / testbench.";
secDescr[z] +="<br/>Documentation on the OP API.";
secDescr[z] +="<br/>Introducing a C harness / testbench.";
secDescr[z] +="<br/>The top level or root module.";
secDescr[z] +="<br/>Configuring the Simulation using parameters.";
secDescr[z] +="<br/>Controlling the simulation using the Command Line.";
secDescr[z] +="<br/>Writing your own harness.exe.";
secDescr[z] +="<br/>Monitoring / Tracing during simulation.";
secDescr[z] +="<br/>Simulating Processor Exceptions.";
secDescr[z] +="<br/>Semihosting and Intercept Libraries.";
secDescr[z] +="<br/>Simulator Control Files.";
secDescr[z] +="<br/>Loading an Application Program file.";
secDescr[z] +="<br/>Attaching a debugger.";
secDescr[z] +="<br/>Imperas Graphical Debug Environments.";
secDescr[z] +="<br/>Controlling Record and Replay of Virtualized Peripheral Input.";
secDescr[z] +="<br/>OP API Compatibility with deprecated ICM API.";
z++;

secTitle[z] = "Advanced Test Harnesses & Simulation Control for OVP and Imperas users";
secFile[z]  = "Advanced_Simulation_Control_of_Platforms_and_Modules_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b>";
secDescr[z] +="<br/>Tracing the API calls and seeing what is happening.";
secDescr[z] +="<br/>Detailed OP API Documentation.";
secDescr[z] +="<br/>Structure of Harnesses/Modules & Simulation Phases.";
secDescr[z] +="<br/>Modules revisited (using the OP API and C).";
secDescr[z] +="<br/>Adding C code to a module.";
secDescr[z] +="<br/>Introducing basic introspection.";
secDescr[z] +="<br/>Simulating a platform.";
secDescr[z] +="<br/>Standard Multiprocessor Scheduling Algorithm.";
secDescr[z] +="<br/>Writing a custom scheduler.";
secDescr[z] +="<br/>Parallel Simulation: QuantumLeap.";
secDescr[z] +="<br/>Combining External and Native Memory.";
secDescr[z] +="<br/>Adding Memory Callbacks.";
secDescr[z] +="<br/>Simulation Optimization.";
secDescr[z] +="<br/>Enabling Peripheral Diagnostics.";
secDescr[z] +="<br/>Adding New Plugin Commands.";
secDescr[z] +="<br/>Introspecting / Querying components in the simulation.";
secDescr[z] +="<br/>Save / Restore.";
secDescr[z] +="<br/>Encapsulating Models for use in other Environments (C, C++, SystemC).";
secDescr[z] +="<br/>Integration with Client Debuggers.";
z++;

secTitle[z] = "OVP OP (OVP Platforms) API Doxygen Documentation";
secDoxygen[z] = "../api/op/html/index.html";
secFile[z] = "Doxygen OP APIs : Function Reference from headers.";
secDescr[z] = "Browsable walk through the OP APIs header file and Examples as hyperlinked documentation.";
z++;

secTitle[z] = "OVP OCL (OVP Common Library) API Doxygen Documentation";
secDoxygen[z] = "../api/ocl/html/index.html";
secFile[z] = "Doxygen OCL APIs : Function Reference from headers.";
secDescr[z] = "Browsable walk through the OCL APIs header file documentation.";
z++;

secTitle[z] = "Simulator Trace User Guide";
secFile[z]  = "OVP_Trace_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>A description of the tracing features built into the Virtual Platform Simulator. ";
secDescr[z] += "The OVP simulator implements a powerful generic instruction tracing capability.<br/>";
secDescr[z] += "The instructions can be displayed as they are executed together with information such as registers changed or written, or memory accesses performed by a processor as each instruction executes.<br/>";
secDescr[z] += "Tracing can be controlled either by simulator command line arguments, or interactively by a debugger, or by functions in the OP API, or by model commands.";
z++;


secTitle[z] = "Control File User Guide";
secFile[z]  = "OVP_Control_File_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>How a Control File can be used to override the configuration of a virtual platform and its components. How it can be used to control the simulation. This allows changes to a platform for which a user has no source or to allow changes without the need to re-compile. ";
secDescr[z] += "It also allows control when the model is buried in, for example a SystemC platform.<br/>";
secDescr[z] += "Examples of uses of a control file: debugger connection, loading programs/libraries, overriding model parameters, control of time precision, quantum size, finish times, verbosity and message control.";
z++;

secTitle[z] = "Using OVP Fast Processor Models with OVP / Imperas and other simulators";
secFile[z] = "OVP_Guide_To_Using_Processor_Models.pdf";
secDescr[z] = "Description of OVP Fast Processor Models and how to use them.<br/>Also see the model variant specific documentation for very detailed information.";
z++;

secTitle[z] = "OVP Target / Application API Function Reference Doxygen Documentation";
secDoxygen[z] = "../api/base/html/index.html";
secFile[z] = "Doxygen Target / Application APIs : Function Reference from headers.";
secDescr[z] = "Browsable walk through the Target / Application APIs header files as hyperlinked documentation.";
z++;

secGroupTitle[z]  = "DEBUGGING";
secTitle[z] = "Debugging Applications with GDB running on OVP platforms";
secFile[z] = "OVPsim_Debugging_Applications_with_GDB_User_Guide.pdf";
secDescr[z] = "How to use GDB with OVPsim.";
z++;

secTitle[z] = "Debugging Applications with Imperas eGui - An Eclipse based IDE";
secFile[z] = "eGui_Eclipse_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b>";
secDescr[z] +="<br/>Installing eGui_Eclipse package.";
secDescr[z] +="<br/>Starting Debug Sessions.";
secDescr[z] +="<br/>Standalone eGui Debug Demos.";
secDescr[z] +="<br/>An Eclipse Project Example.";
secDescr[z] +="<br/>An Example Debug Session.";
z++;

secTitle[z] = "Debugging Applications with Eclipse CDT running on OVP platforms";
secFile[z] = "OVPsim_Debugging_Applications_with_Eclipse_User_Guide.pdf";
secDescr[z] = "How to use Eclipse CDT with OVPsim.<br/>There is also a video walking through this guide - it shows installation, setup and use - <a href=http://www.ovpworld.org/download_demos.php#sectionDemoDebug>click here</a>.";
z++;

secTitle[z] = "Debugging Applications with ARM DS-5 running on OVP platforms";
secDescr[z] = "<a href=../imperas/Imperas_Debugging_with_ARM_DS-5.pdf> Imperas_Debugging_with_ARM_DS-5.pdf"+" "+img+"</a> ";
secDescr[z] += "<br/><b>Contents:</b><br/>Using ARM DS-5 with OVP Virtual Platforms.<br/>How to setup ARM DS-5 for use with OVP Virtual Platforms.";
secDescr[z] += "<br/>Examples using DS-5 with OVP platforms of Cortex-A5UP and CortexA9MPx2 (SMP).";
z++;

secTitle[z] = "Debugging Applications with INSIGHT running on OVP platforms";
secFile[z] = "OVPsim_Debugging_with_INSIGHT_User_Guide.pdf";
secDescr[z] = "How to use INSIGHT with OVPsim.";
z++;

secGroupTitle[z]  = "WRITING BEHAVIORAL (PERIPHERAL) MODELS";
secTitle[z] = "Creating Behavioral (Peripheral) components using BHM/PPM APIs and adding them to Platforms";
secFile[z] = "OVP_Peripheral_Modeling_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>How to write and use behavioral components.<br/>Overview of OVP simulation.<br/>BHM introduction - for behavior.<br/>PPM introduction - for peripheral platform interconnections.<br/>Function interception.<br/>A multithreaded DMA example.<br/>Interrupts and signals.";
z++;

secTitle[z] = "Function Reference Guide for OVP BHM / PPM APIs for Behavioral Component Modeling";
secFile[z] = "OVP_BHM_PPM_Function_Reference.pdf";
secDescr[z] = "Description of each BHM and PPM Function.";
z++;

secTitle[z] = "OVP BHM/PPM API Function Reference Doxygen Documentation";
secDoxygen[z] = "../api/peripheral/html/index.html";
secFile[z] = "Doxygen BHM/PPM APIs : Function Reference from headers.";
secDescr[z] = "Browsable walk through the BHM/PPM APIs Behavioral Component Modeling header files as hyperlinked documentation.";
z++;

secGroupTitle[z]  = "WRITING CPU MODELS";
secTitle[z] = "Creating Instruction Accurate Processor models using the VMI API";
secFile[z] = "OVP_Processor_Modeling_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>How to write and use processor models using the Virtual Machine Interface (VMI API).<br/>Simulation overview. Introduction to Processor Modeling. Creating a processor outline.<br/>Endianness. Fetching Instructions. Attribute tables.<br/>Building a test platform. Creating an application testcase.<br/>Implementing the Instruction Decode. More complex decoders.<br/>Implementing an Instruction Disassembler. Implementing simple behavior.<br/>An introduction to Code Morphing.<br/>Processor flags and register dumping. Jump instructions.<br/>Memory access instructions. Fibonnacci example.<br/>Modeling Exceptions. Modeling mode-dependent behavior.<br/>Timers. Modeling interrupts. Debug Interface.<br/>Implementing Virtual Memory. Higher speed processor models.<br/>Semihosting. Implementing efficient Cache and memory subsystems.";
z++;

secTitle[z]  = "Extending RISC-V Models with Custom Extensions";
secFile[z]   = "OVP_RISCV_Model_Custom_Extension_Guide.pdf";
secDescr[z]  = "<b>Contents:</b><br/>"
secDescr[z] += "A introduction into the best way to extend an OVP RISC-V model.<br/>";
secDescr[z] += "Creating a new model based on the 'base model' source - the linked model.<br/>";
secDescr[z] += "Linked model creation.<br/>";
secDescr[z] += "Custom configuration options.<br/>";
secDescr[z] += "Adding custom instructions.<br/>";
secDescr[z] += "Adding custom CSRs.<br/>";
secDescr[z] += "Adding custom exceptions.<br/>";
secDescr[z] += "Adding custom local interrupts.<br/>";
secDescr[z] += "Adding custom FIFOs.<br/>";
secDescr[z] += "Listing and description of standard instruction patterns.<br/>";
secDescr[z] += "Listing and description of base model service functions.<br/>";
secDescr[z] += "Extension object interface functions.";
z++;

secTitle[z] = "Building Semihost Libraries (virtualizing host OS functions)";
secFile[z]  = "OVP_Processor_Modeling_Guide.pdf";
secDescr[z] = "Intercept libraries for semi-hosting are introduced in the OVP_Processor_Modeling_Guide.pdf document.";
secDescr[z] += "<br/>An example library for newlib is available as a template in the OVPsim download examples of processors, as 19.or1kSemiHosting.";
z++;

secGroupTitle[z]  = "VMI API";
secTitle[z] = "VMI Morph Time (VMI MT) API Reference Guide";
secFile[z] = "OVP_VMI_Morph_Time_Function_Reference.pdf";
secDescr[z] = "Description of each VMI Morph Time Function";
z++;

secTitle[z] = "VMI Run Time (VMI RT) API Reference Guide";
secFile[z] = "OVP_VMI_Run_Time_Function_Reference.pdf";
secDescr[z] = "Description of each VMI Run Time Function";
z++;

secTitle[z] = "VMI Memory Modeled Component (VMI MMC) API Reference Guide";
secFile[z] = "OVP_VMI_Memory_Model_Component_Function_Reference.pdf";
secDescr[z] = "Description of each MMC Function (includes Cache Modeling).";
z++;

secTitle[z] = "VMI Operating System support (VMI OS) API Reference Guide";
secFile[z] = "OVP_VMI_OS_Support_Function_Reference.pdf";
secDescr[z] = "Description of each VMI OS Function.";
z++;

secTitle[z] = "VMI Programmers Views (VMI VIEW) API Reference Guide.";
secFile[z] = "OVP_VMI_View_Function_Reference.pdf";
secDescr[z] = "Description of each function of VMI View API for creating Programmers View objects and events in models.";
z++;

secTitle[z] = "VMI API Function Reference Doxygen Documentation";
secDoxygen[z] = "../api/vmi/html/index.html";
secFile[z] = "Doxygen VMI APIs : Function Reference from headers.";
secDescr[z] = "Browsable walk through the VMI APIs header files as hyperlinked documentation.";
z++;
