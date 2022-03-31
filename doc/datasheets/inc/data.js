var dataExists = 1; // must exist and be set to 1

var pageTitle = "Imperas/OVP Datasheets Documentation";
var documentName = "Datasheets";
//var webSite = "www.mips.com"; // optional
var headerGraphic = "doc_header.gif";

//var versionDate = "(October 10) 20101004.0"; 

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();
var secGroupTitle = new Array();

var z = 0;

secGroupTitle[z]  = "OVP DATASHEETS";
secTitle[z]  = "OVP Overview Datasheet";
 secFile[z]  = "OVP_Overview_Datasheet.pdf";
secDescr[z]  = "This data sheet provides an overview of OVP.";
z++;

secTitle[z]  = "OVP Processor / Core Models Datasheet";
 secFile[z]  = "OVP_Fast_Processor_Models_Datasheet.pdf";
secDescr[z]  = "Introduces the OVP processor modeling technology.";
secDescr[z] += "<br/>It lists the current processors and explains how they can be used.";
secDescr[z] += "<br/>Provides up to date performance numbers.";
z++;

secTitle[z]  = "OVP Available Virtual Platforms Datasheet";
 secFile[z]  = "OVP_Virtual_Platforms_Datasheet.pdf";
secDescr[z]  = "Describes some of the available virtual platforms.";
z++;

secTitle[z]  = "OVPsim Specification";
 secFile[z]  = "OVP_OVPsim_Specification.pdf";
secDescr[z]  = "This document provides a detailed description of OVPsim, the OVP simulator made available at www.OVPworld.org.";
z++;

secGroupTitle[z]  = "IMPERAS DATASHEETS";
secTitle[z]  = "Imperas Datasheets";
secDescr[z]  = "Introduces the different Imperas Professional tools and lists key capabilities.";
secDescr[z] += "<br/><br/><a href=Imperas-ISS-The_Imperas_Instruction_Set_Simulator_Datasheet.pdf> Imperas Instruction Set Simulator (ISS) - for easy embedded software development.</a> "; 
secDescr[z] += "<br/><a href=Imperas-M_SDK-Advanced_Multicore_Software_Development_Kit_Datasheet.pdf> Imperas M*SDK, advanced multicore software development kit.</a> "; 
secDescr[z] += "<br/><a href=Imperas-DEV-Virtual_Platform_Development_and_Simulation_Datasheet.pdf> Imperas C*DEV, S*DEV and M*DEV, for virtual platform development and simulation.</a> ";
secDescr[z] += "<br/><a href=Imperas-QuantumLeap-Virtual_Platform_Simulation_Acceleration_Datasheet.pdf> Imperas QuantumLeap technology utilises available host processor resources for increased simulation performance of MP systems.</a> ";
secDescr[z] += "<br/><a href=Imperas-cpuGen-CPU_Model_Generation_Datasheet.pdf> Imperas cpuGen, a generation tool for CPU models.</a> ";
secDescr[z] += "<br/><br/>If you are an OVP user this provides some information on how you can upgrade your capability to provide a much more efficient embedded software development environment based around use of virtual platforms / simulation and the Imperas Professional Tools.";
secDescr[z] += "<br/><br/>More information is available from <a href=http://www.Imperas.com title='click to visit'>www.Imperas.com</a> ";
z++;

/* add more sections if needed */
