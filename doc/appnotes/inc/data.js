var dataExists = 1; // must exist and be set to 1

var pageTitle = "Imperas/OVP Application Notes";
var documentName = "Application Notes";
var headerGraphic = "doc_header.gif";

//var versionDate = "(October 10) 20101004.0"; 

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();
var secGroupTitle = new Array();

var z = 0;

secGroupTitle[z]  = "APPLICATION NOTES";

secTitle[z]  = "RISC-V Custom Instruction Flow Application Note";
 secFile[z]  = "Imperas_RISCV_Custom_Instruction_Flow_Application_Note.pdf";
secDescr[z]  = "A RISC-V processor has several defined decode spaces, for example custom0, custom1 etc. into which new custom instructions can be added. OVP Fast processor models can be extended without modification to the pre-compiled and verified base processor model source code using one or more extension libraries. An extension library can be loaded as part of a virtual platform definition in addition to the base processor model and can provide decode and implementation of behavior for the instructions as well as additional registers.";
secDescr[z] += "<br/><br/>Including more timing information for the instruction execution provides a cycle approximate simulation. This provides a better approximation to the time of the execution of an application on the actual hardware. The additional timing information is loaded into the virtual platform as an extension library so there is no change to the functional behavior provided by the processor model.";
secDescr[z] += "<br/><br/>This application goes through the complete flow of functional validation of the application, extension of the processor with custom instructions, analysis of the application execution and optimization of the custom instruction implementation and its documentation.";
secDescr[z] += "<br/><br/>Note that some of the Imperas product features used in this example require Imperas Professional tools.";
z++;

secTitle[z]  = "ARM TrustZone Platform Modeling Application Note";
 secFile[z]  = "Imperas_ARM_TrustZone_Platform_Modeling_Application_Note.pdf";
secDescr[z]  = "The ARM TrustZone technology adds a secure mode to the ARM processor architecture and additional security signals to the AMBA bus, which are used by TrustZone-aware peripherals to prevent access to certain bus addresses when the processor (or other bus master) is not in secure mode.";
secDescr[z] += "<br/><br/>As ARM TrustZone features are used for embedded systems, it becomes important to be able to comprehensively test the software that makes use of the TrustZone features. Key to comprehensive testing is the performance, controllability and visibility that virtual platforms provide.";
secDescr[z] += "<br/><br/>This document focuses on best known methods for modeling TrustZone-aware peripherals in OVP to achieve optimal performance.";
z++;



/* add more sections if needed */