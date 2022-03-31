var dataExists = 1; // must exist and be set to 1

var pageTitle = "Imperas/OVP Documentation";
var documentName = "Imperas / OVP Main Documentation Page";
var headerGraphic = "doc_header.gif";
//var webSite = "www.mine.com"; // optional

//var versionDate = "For Product v20101004.0 created Wed Oct  6 15:18:24 2010";

// internal variables
if(typeof dDir == "undefined") {
	var dDir = "../"; // or ./ if in main dir
}
if(typeof docDir == "undefined") {
	var docDir = "./"; // or ./doc if in main dir
}

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();
var secGroupTitle = new Array();

var z = 0;

secGroupTitle[z]  = "INTRODUCTION";
secTitle[z]  = "Getting Started with Imperas and OVP";
secDescr[z]  = "When you download different packages from Imperas and OVPworld you get the documentation populated.";
secDescr[z] += "<br/><br/>An installation of the Imperas Developer product does include the OVP documentation.";
secDescr[z] += "<br/><br/>An installation of the Imperas SDK product does include the OVP and Imperas Developer documentation.";
secDescr[z] += "<br/><br/>An installation of OVP does not include any of the Imperas software or documentation.";
z++;

secGroupTitle[z]  = "OVP";
secTitle[z]  = "OVP: Open Virtual Platforms Documentation (including all OVP defined APIs)";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/ovp/index.html'>Open Virtual Platforms (OVP) Products click here</a>.";
secExist[z]  = "ovpExists";
var ovpExists;
z++;

secTitle[z]  = "OVP: Open Virtual Platforms CHANGELOGs";
secDescr[z]  = "Open the <a href='"+dDir+"/CHANGELOG.OVP.txt'>CHANGELOG,OVP</a> for news on the latest changes in the Open Virtual Platforms (OVP) Products.";
secDescr[z]  += "<br/><br/>Open the <a href='"+dDir+"/CHANGELOG.MODEL.ARM.txt'>CHANGELOG ARM</a> for news on the latest changes in the ARM processor models.";
secDescr[z]  += "<br/>Open the <a href='"+dDir+"/CHANGELOG.MODEL.MIPS.txt'>CHANGELOG MIPS</a> for news on the latest changes in the MIPS processor models.";
secDescr[z]  += "<br/>Open the <a href='"+dDir+"/CHANGELOG.MODEL.RISCV.txt'>CHANGELOG RISCV</a> for news on the latest changes in the RISC-V processor models.";
secExist[z]  = "ovpExists";
var ovpExists;
z++;

secGroupTitle[z]  = "IMPERAS";
secTitle[z]  = "Imperas Developer Documentation";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/imperas/index.html'>Imperas Developer Products click here</a>."; // changed
secExist[z]  = "imperasDEVExists";
var imperasDEVExists;
z++;

secTitle[z]  = "Imperas SDK Documentation";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/imperas/index.html'>Imperas SDK Products click here</a>."; // changed
secExist[z]  = "imperasSDKExists";
var imperasSDKExists;
z++;

secTitle[z]  = "Imperas CPU Model Generator Documentation";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/imperas/index.html'>Imperas CPU Model Generator Products click here</a>."; // changed
secExist[z]  = "imperasCPUGENExists";
var imperasCPUGENExists;
z++;

secTitle[z]  = "CHANGELOG Imperas SDK";
secDescr[z]  = "Open the <a href='"+dDir+"/CHANGELOG.SDK.txt'>CHANGELOG</a> for news on the latest changes in the Imperas SDK Products.";
secExist[z]  = "imperasSDKExists";
var imperasSDKExists;
z++;

secTitle[z]  = "CHANGELOG Imperas iGen"; 
secDescr[z]  = "Open the <a href='"+dDir+"CHANGELOG.iGen.txt'>CHANGELOG</a> for news on the latest changes in Imperas iGen.";
secExist[z]  = "imperasDEVExists";
var imperasDEVExists;
z++;

secTitle[z]  = "CHANGELOG Imperas DEV"; // new
secDescr[z]  = "Open the <a href='"+dDir+"CHANGELOG.DEV.txt'>CHANGELOG</a> for news on the latest changes in the Imperas DEV Products.";
secExist[z]  = "imperasDEVExists";
var imperasDEVExists;
z++;

secGroupTitle[z]  = "MIPS";
secTitle[z]  = "OVPsimMIPS: Instruction Accurate Simulation from MIPS Technologies Inc.";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/MIPS/index.html'>MIPS IASim products</a>.";
secExist[z]  = "MIPSExists";
var MIPSExists;
z++;

secTitle[z]  = "OVPsimMIPS: CHANGELOG";
secDescr[z]  = "Open the <a href='"+dDir+"/CHANGELOG.OEM.MIPS.txt'>CHANGELOG</a> for news on the latest changes in the OVPsimMIPS Products.";
secExist[z]  = "MIPSExists";
var MIPSExists;
z++;

secGroupTitle[z]  = "CADENCE";
secTitle[z]  = "Cadence: Documentation related to Cadence use of OVP / Imperas products.";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/Cadence/index.html'>Cadence use of OVP/Imperas products</a>.";
secExist[z]  = "CadenceExists";
var CadenceExists;
z++;

/* add more sections if needed */