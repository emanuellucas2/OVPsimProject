

/* to do list
??
*/

/* wish list for html/javasccript
- sort tree lists
*/

/* limitiations
- if you put two vlnvroots one for windows one for linux - you get it with two entries for each item.. - I think.. - ie it does not handle more than one platform type...

*/

var processorsLibs = new Array();
var tLibraries = new Array();

var tree = new Array();
tree['platform']=new Array();
tree['module']=new Array();
tree['harness']=new Array();
tree['memory']=new Array();
tree['mmc']=new Array();
tree['peripheral']=new Array();
tree['processor']=new Array();
tree['semihosting']=new Array();
tree['intercept']=new Array();
tree['modelSupport']=new Array();
tree['cpuHelper']=new Array();
tree['osHelper']=new Array();
tree['tools']=new Array();

function log (s) {
    document.writeln ("LOG: "+s+"<br/>");
}

function error (str) {
    document.getElementById('imperasdocs').innerHTML = 'Error: '+str;
    // todo - should really kill the page...
}

function checkFileListInstalled () {
    if(typeof numFiles == "undefined") {
        error ('The Imperas Library Documentation system is not installed correctly (libDocItems.js not found). To correct, please move into the $IMPERAS_HOME/doc/library directory and run the libDocGen.bat or libDocGen.bash script.');
        return;
    }
    if(typeof maker == "undefined") {
        error ('The Imperas Library Documentation system is not installed (utilities.js not found).');
        return;
    }
    if(typeof toggleFolder == "undefined") {
        error ('The Imperas Library Documentation system is not installed (tree.js not found).');
        return;
    }
    if (navigator.appName != "Netscape") {
        error ('The Imperas Library Documentation system does not work with Internet Explorer, please use FireFox or Chrome.');
        return;
    }
}

var table = maker("table"), tr = maker("tr"), th = maker("th"), td = maker("td"), fs = maker("fieldset"), href = maker("href"); //, lg = maker("legend");

function display_header (fd, fileIndex, x, treeName, needsCommercialLicense) {
    var filePath = fileNames[fileIndex];
    var library = x.getAttribute ("library");
    var name = x.getAttribute ("name");
    var vendor = x.getAttribute ("vendor");
    var version = x.getAttribute ("version");
    var Licensing;
    var Limitations = new Array();
    var numLimitations = 0;
    var Descriptions = new Array();
    var numDescriptions = 0;
    var Features = new Array();
    var numFeatures = 0;
    var doneOneDescription = 0;
    
    /* old style 10 feb 2015
    var documentation = x.getElementsByTagName("documentation");
    for (var i=0;i<f;i++) {f
        var docType = documentation[i].getAttribute("name");
        if (docType == "Licensing") {
            Licensing = documentation[i].childNodes[0].nodeValue;
        } else if (docType == "Limitations") {
            Limitations[numLimitations++] = dfocumentation[i].childNodes[0].nodeValue;
        } else if (docType == "Features") {
            Features[numFeatures++] = documentation[i].childNodes[0].nodeValue;
        } else if (((docType == "Description")||(docType == "description")) && (!doneOneDescription)) {
            Description = documentation[i].childNodes[0].nodeValue;
            doneOneDescription = 1;
       } 
    }
    */
    // new approach using docsections 10 feb 2015
    var docSections = x.getElementsByTagName("docsection");
    for (var i=0;i<docSections.length;i++) {
       var docType = docSections[i].getAttribute("text");
        if (docType == "Licensing") {
			var texts = docSections[i].getElementsByTagName("doctext");
			for (var ii=0;ii<texts.length;ii++) {
				Licensing  = texts[ii].getAttribute("text"); 
			}
		} else if (((docType == "Description")||(docType == "description") ) && (!doneOneDescription)) {
			var texts = docSections[i].getElementsByTagName("doctext");
			for (var ii=0;ii<texts.length;ii++) {
				Descriptions[numDescriptions++] =  docSections[i].getElementsByTagName("doctext")[ii].getAttribute("text"); 
			}
			doneOneDescription = 1;
		} else if (docType == "Limitations") {
			var texts = docSections[i].getElementsByTagName("doctext");
			for (var ii=0;ii<texts.length;ii++) {
				Limitations[numLimitations++]  = texts[ii].getAttribute("text"); 
			}
		} else if (docType == "Features") {
			var texts = docSections[i].getElementsByTagName("doctext");
			for (var ii=0;ii<texts.length;ii++) {
				Features[numFeatures++]  = texts[ii].getAttribute("text"); 
			}
		}
	}    
    
    var sss;
    if (needsCommercialLicense) {
        sss = "         [** Needs Commercial License from Imperas **]";
    } else {
        sss = "";
    }
    var fieldset = fs({border:1}, make("b",treeName+": "+name+sss));
    fd.appendChild(fieldset);

	var tab = table({border:1}, tr([th("Name"), th("Value")]));
	fieldset.appendChild(tab);
	tab.appendChild(tr([td("vendor"), td(vendor)]));
	tab.appendChild(tr([td("library"), td(library)]));
	tab.appendChild(tr([td("name"), td(name)]));
	tab.appendChild(tr([td("version"), td(version)]));
    for (var i=0;i<Descriptions.length;i++) {
		if (i == 0) {
			tab.appendChild(tr([td("Description"), td(Descriptions[i])]));
		} else { 
			tab.appendChild(tr([td("..."), td(Descriptions[i])]));
		}
	}
    for (var i=0;i<Features.length;i++) {
		if (i == 0) {
			tab.appendChild(tr([td("Features"), td(Features[i])]));
		} else { 
			tab.appendChild(tr([td("..."), td(Features[i])]));
		}
	}
    for (var i=0;i<Limitations.length;i++) {
		if (i == 0) {
			tab.appendChild(tr([td("Limitations"), td(Limitations[i])]));
		} else { 
			tab.appendChild(tr([td("..."), td(Limitations[i])]));
		}
	}
	tab.appendChild(tr([td("Licensing"), td(Licensing)]));

    return tab;
}

function display_tail (tab, fileIndex, x) {
	return;
	
	// not yet included.... SJD todo
	
    var txt = " ";
    tab.appendChild(tr([td(" "), txt]));
    tab.appendChild(tr([td("More_Detailed_Information:"), txt]));
    tab.appendChild(tr([td(" "), txt]));
    
    var allElements = x.getElementsByTagName("formalattribute");
    for (var i=0;i<allElements.length;i++) {
    	var allAttributes = allElements[i].attributes;
     	for (var j=0;j<allAttributes.length;j++) {
	    	var nodeName = allAttributes[j].nodeName;
	    	var nodeType = allAttributes[j].nodeType;
	    	var nodeTypeString = nodeType.toString();
	    	var nodeValue = allAttributes[j].nodeValue;
	        tab.appendChild(tr([td(nodeName), td(nodeTypeString), td(nodeValue)]));
        }
    }
    
    // find attributes at top level = nodeType=2 nodeName, nodeValue
    // tag = find tagname=documentation =  whose child node whose nodeName=name use nodeValue, 
    // 		and node Text is in a node of type nodeType=3 and use its value
    // tag == tagname = formalattribute, child of type=2 whose nodeName=name
}

function display_semihostlibrary (fd, fileIndex, x) {
    var attributetable = x.getAttribute ("attributetable");
    var autoload = x.getAttribute ("autoload");
    var imagefile = x.getAttribute ("imagefile");
    var supportedProcessors = new Array();
    var commands = new Array();
    var packages = new Array();

    var supProc = x.getElementsByTagName("supportedprocessor");
    for (var i=0;i<supProc.length;i++) {
        if (supProc[i].getElementsByTagName("vlnvreference").length > 0) { 
            supportedProcessors.push(supProc[i].getElementsByTagName("vlnvreference")[0].getAttribute("name"));
        }
    }

    var npackage = x.getElementsByTagName("package");
    for (var i=0; i<npackage.length; i++) {
        var ipack = npackage[i].getAttribute("name");
        packages.push(ipack);
    }
  
    var comms = x.getElementsByTagName("command");
    for (var i=0;i<comms.length;i++) {
        var commandName = comms[i].getAttribute("name");
        commands.push(commandName);
    }
    
    var needsCommercialLicense = 1;
    if ((x.getAttribute ("library") == "semihosting")||(x.getAttribute ("library") == "modelSupport")) {
        needsCommercialLicense = 0;
    }
    
    // now start of displaying...
    var tab = display_header (fd, fileIndex, x, "semihosting", needsCommercialLicense);

    for (var i=0;i<packages.length;i++) {
        tab.appendChild(tr([td("Package"), td(packages[i])]));
    }
 
    for (var i=0;i<supportedProcessors.length;i++) {
    	if (i == 0) {
        	tab.appendChild(tr([td("Supported Processor"), td(supportedProcessors[i])]));
        } else {
        	tab.appendChild(tr([td("..."), td(supportedProcessors[i])]));
        }
    }
    
    for (var i=0;i<commands.length;i++) {
    	if (i == 0) {
       		tab.appendChild(tr([td("tool command"), td(commands[i])]));
       	} else {
         	tab.appendChild(tr([td("..."), td(commands[i])]));
        }
    }

    display_tail (tab, fileIndex, x);
}

function appendItemDoc (tab, title, vendor, library, name, version, fileRoot) {
    var lpath = location.pathname;
    var twoSlashes = lpath.indexOf("//");

    var filename = fileRoot+name+".pdf";
    var path = "ImperasLib/source/"+vendor+"/"+library+"/"+name+"/"+version+"/doc/"+filename;
    var pathStr = "$IMPERAS_HOME/"+path;
    
    if (twoSlashes > 0) {
        var link = "../../../"+path;
    } else {
        var link = "../../"+path;
    }
    
    //alert (location.pathname+" "+twoSlashes+" "+link);
   
    var tre = document.createElement ('tr');
    
    var tdl = document.createElement ('td');
    tre.appendChild(tdl);
    var text = document.createTextNode(title);
    tdl.appendChild(text);
    
    var tdr = document.createElement ('td');
    tre.appendChild(tdr);
    var a = document.createElement ('a');
    
    a.setAttribute('href',link);
    a.setAttribute('title',"click to view pdf documentation ("+link+") for this item (if it exists) ");
    a.setAttribute('target',"_blank");
    a.innerHTML = pathStr;
    tdr.appendChild(a);
    
    tab.appendChild(tre);
}

function display_platform (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "platform", 0);
    var platformname = x.getAttribute ("name");
    var vendor = x.getAttribute ("vendor");
    var library = x.getAttribute ("library");
    var version = x.getAttribute ("version");
    
    if (x.getAttribute ('wallclock')) {
        tab.appendChild(tr([td("wallclock"), td(x.getAttribute ('wallclock'))]));
    }
    appendItemDoc (tab, "Documentation", vendor, library, platformname, version, "Imperas_Platform_User_Guide_");

    display_tail (tab, fileIndex, x);
}

function display_module (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "module", 0);
    var modulename = x.getAttribute ("name");
    var vendor = x.getAttribute ("vendor");
    var library = x.getAttribute ("library");
    var version = x.getAttribute ("version");
    
    appendItemDoc (tab, "Documentation", vendor, library, modulename, version, "Imperas_Platform_User_Guide_");

    display_tail (tab, fileIndex, x);
}

function display_harness (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "harness", 0);
    
    display_tail (tab, fileIndex, x);
}

function appendVariantDoc (tab, title, vendor, library, name, version, variant) {
    //alert (title+" "+vendor+" "+library+" "+name+ " "+variant);
    
    // if in here: Imperas/doc/library/index.html ->  /imperas/home/simond/Imperas/doc/library/index.html
    // if in here: Imperas/doc/index.html ->  /imperas/home/simond/Imperas/doc//library/index.html
    // if in here: Imperas/INDEX.html ->  /imperas/home/simond/Imperas/doc//library/index.html
    var lpath = location.pathname;
    var twoSlashes = lpath.indexOf("//");

	if (vendor == "andes.ovpworld.org") {
		fullname = "andes_";
	} else if (vendor == "microsemi.ovpworld.org") {
		fullname = "microsemi_";
	} else if (vendor == "sifive.ovpworld.org") {
		fullname = "sifive_";
	} else if (vendor == "lowrisc.ovpworld.org") {
		fullname = "lowrisc_";
	} else {
		fullname = "";
	}
    var filename = "OVP_Model_Specific_Information_"+fullname+name+"_"+variant+".pdf";
    var path = "ImperasLib/source/"+vendor+"/"+library+"/"+name+"/"+version+"/doc/"+filename;
    var pathStr = "$IMPERAS_HOME/"+path;
    
    if (twoSlashes > 0) {
        var link = "../../../"+path;
    } else {
        var link = "../../"+path;
    }
    
    //alert (location.pathname+" "+twoSlashes+" "+link);
   
    var tre = document.createElement ('tr');
    
    var tdl = document.createElement ('td');
    tre.appendChild(tdl);
    var text = document.createTextNode(title);
    tdl.appendChild(text);
    
    var tdr = document.createElement ('td');
    tre.appendChild(tdr);
    var a = document.createElement ('a');
    
    a.setAttribute('href',link);
    a.setAttribute('title',"click to view pdf documentation ("+pathStr+") for this processor (if it exists) ");
    a.setAttribute('target',"_blank");
    a.innerHTML = variant;
    tdr.appendChild(a);
    
    tab.appendChild(tre);
}

function display_processor (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "processor", 0);
    var cpuname = x.getAttribute ("name");
    var vendor = x.getAttribute ("vendor");
    var library = x.getAttribute ("library");
    var version = x.getAttribute ("version");

    if (x.getAttribute ('procdoc')) {
        // tab.appendChild(tr([td("Full Documentation"), td(x.getAttribute ('procdoc'))]));
        tab.appendChild(tr([td("Full Documentation"), td("click on the variant names below to see the full variant specific documentation (if it exists)")]));
    }

    var formalAttribute = x.getElementsByTagName("formalattribute");
    for (var i=0;i<formalAttribute.length;i++) {
        var name = formalAttribute[i].getAttribute("name");
        var type = formalAttribute[i].getAttribute("type");
        if ((name == "variant") &&  (type =="enumeration")) {
            var enums = formalAttribute[i].getElementsByTagName("enum");
            for (var e=0; e<enums.length; e++) {
                var variant = enums[e].getAttribute("name");
                if (e == 0) {
					//tab.appendChild(tr([td("variant available"), td(variant)]));
                    appendVariantDoc (tab, "variant available", vendor, library, cpuname, version, variant);
				} else {
					//tab.appendChild(tr([td("..."), td(variant)]));
                    appendVariantDoc (tab, "...", vendor, library, cpuname, version, variant);
				}
            }
        } 
    } 
    
    tab.appendChild(tr([td("elfcode"), td(x.getAttribute ('elfcode'))]));
    tab.appendChild(tr([td("endian"), td(x.getAttribute ('endian'))]));
    if (x.getAttribute ('defaultsemihostname')) tab.appendChild(tr([td("defaultsemihostname"), td(x.getAttribute ('defaultsemihostname'))]));
    for (var i=0; i<processorsLibs[cpuname].length; i++) {
        if (i == 0) {
			tab.appendChild(tr([td("compatible library"), td(processorsLibs[cpuname][i])]));
		} else {
			tab.appendChild(tr([td("..."), td(processorsLibs[cpuname][i])]));
		}
    }
    if (x.getAttribute ('gdbpath')) tab.appendChild(tr([td("gdbpath"), td(x.getAttribute ('gdbpath'))]));
    
    display_tail (tab, fileIndex, x);
}

function display_peripheral (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "peripheral", 0);
    var psename = x.getAttribute ("name");
    var vendor = x.getAttribute ("vendor");
    var library = x.getAttribute ("library");
    var version = x.getAttribute ("version");
    
    appendItemDoc (tab, "Documentation", vendor, library, psename, version, "OVP_Peripheral_Specific_Information_");
    
    display_tail (tab, fileIndex, x);
}

function display_memory (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "memory", 0);
    display_tail (tab, fileIndex, x);
}

function display_mmc (fd, fileIndex, x) {
    var tab = display_header (fd, fileIndex, x, "memory", 0);
    display_tail (tab, fileIndex, x);
}

function show (i, name) {
    var p = parent.mainfrm.document.getElementById("maindata");
    if (i == -1) { 
        // we are a library... not an item
       p.innerHTML = "<h3>About the '"+name+"' library</h3>";
       if (name == "platform") {
      		p.innerHTML += "The platform library holds all the platforms that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "A platform is an interconnection of behavioral models of processors and peripherals. ";
      		p.innerHTML += "Platforms can be written in C or C++ or SystemC or TLM2.0 for OVP and for Imperas they can be written in TCL and XML using appropriate Imperas productivity tools. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of platforms by opening the tree list and then click on the list to see information about each platform. ";
       } else if (name == "module") {
      		p.innerHTML += "The module library holds all the modules that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "A module is an interconnection of behavioral models of modules, processors, and peripherals etc. ";
      		p.innerHTML += "A module is often a level or sub-system, of a hierarchical system. ";
      		p.innerHTML += "Modules can be written in C or in TCL using iGen, one of the Imperas productivity tools. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of modules by opening the tree list and then click on the list to see information about each module. ";
       } else if (name == "harness") {
      		p.innerHTML += "The harness library holds all the harnesses that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "A harness is a testbench that instances modules and other components (like a platform). ";
      		p.innerHTML += "Harnesses can be written in C, C++, SystemC, or SystemC TLM. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of harnesses by opening the tree list and then click on the list to see information about each harness. ";
        } else if (name == "processor") {
      		p.innerHTML += "The processor library holds all the processors that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "An OVP processor is a behavioral model of the processor. It is written in C using the OVP VMI (Virtual Machine Interface) API. ";
            p.innerHTML += "The VMI API implements all the functonality needed and when run uses advanced Just-In-Time Binary Translation code morphing to transform target processor instructions into host instructions. ";
      		p.innerHTML += "<br/><br/>";
            p.innerHTML += "All OVP processor models can be used in C, C++, SystemC and TLM2.0 platforms and come with all the needed source header files. ";
            p.innerHTML += "All the OVP processor models can be used in OVPsim with a single GDB (if a GNU GDB is available). The OVPworld web site has downloads for the most popular processor's tool chains including the GCC and GDB tools. ";
      		p.innerHTML += "<br/><br/>";
            p.innerHTML += "The Imperas tools include a sophisticated multi core debugger that can simultaneously debug platforms of many processors (homogeneous or heterogeneous) and also uniquely can debug peripherals as part of the simulation. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of processors by opening the tree list and then click on the list to see information about each processor. ";
       } else if (name == "semihosting") {
       		p.innerHTML += "The semihosting library holds all the semihost programs that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
            p.innerHTML += "Semihosting allows behavior that would normally occur on a simulated system to be implemented using features of the host system instead. Semihost libraries use intercept features of the underlying simulator. ";
      		p.innerHTML += "<br/><br/>";
            p.innerHTML += "The libraries provided with OVP include functionality to semi host the C runtime library NewLib. Using a newlib semihost library for the processor you are using allows you to have your target cross compiled application call functions such as 'printf' and the output come to the smulation console. ";
      		p.innerHTML += "<br/><br/>";
            p.innerHTML += "Semihost libraries are written in C or C++ and use standard OVP APIs and can be written for any processor. The Semihost libraries provided with OVP are provided as binaries. ";
            p.innerHTML += "The Imperas tools include source examples of writing semihost libraries. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of semihost programs by opening the tree list and then click on the list to see information about each semihost program. ";
       } else if (name == "peripheral") {
       		p.innerHTML += "The peripheral library holds all the peripherals that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "An OVP peripheral model is a behavioral model of a component including its programmers views but normally very little of its internal details. In its simplest form an OVP peripheral can be just the user accessible registers and no behavior. ";
      		p.innerHTML += "OVP Peripherals can be written in C or C++ and can be wrapped with SystemC or TLM2.0 headers for use with other simulators. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "The Imperas productivity tools include a peripheral generator that enables models to be created by just a few lines of TCL. XML can also be used as input to the appropriate Imperas productivity tools. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "OVP periheral models are provided as binaries and source and many include SystemC TLM2.0 wrappers. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of peripherals by opening the tree list and then click on the list to see information about each peripheral. ";
       } else if (name == "memory") {
       		p.innerHTML += "The memory library holds all the memories that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of memories by opening the tree list and then click on the list to see information about each memory. ";
       } else if (name == "mmc") {
       		p.innerHTML += "The mmc library holds all the memory mapped components (MMCs) that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "An MMC is a component that is located on a bus between a processor and memory and performs some address or data transformation. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "MMCs are used very effectively for modeling cache and memory hierarchies. ";
          	p.innerHTML += "Caches can be modeled as transparent or opaque. A transparent cache is really a monitor which can report hits and misses but does not affect the data passing through it. ";
          	p.innerHTML += "An opaque cache can model the actual operation of a cache and can reduce downstream memory accesses by actually caching the instructions/data. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of MMCs by opening the tree list and then click on the list to see information about each MMC. ";
       } else if (name == "intercept") {
       		p.innerHTML += "The intercept library holds all the intercept programs that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "Intercept programs can be used to extend an OVP compliant simulator in many ways. OVPsim is very restricted in how it implements intercept functionality. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "The Imperas Professional simulator implements the full OVP intercept functionality and allows the user to extend the simulator to provide extremely efficient verification, analysis, and profiling capabilities.";
          	p.innerHTML += "The Imperas tools include intercept programs that provide cpu personality for debugging and analysis, and also operating system awareness in the tools.";
          	p.innerHTML += "The intercept programs included with the Imperas tools support most processors and operating systems that are available for OVP simulation. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of intercept programs by opening the tree list and then click on the list to see information about each intercept program. ";
       } else if (name == "modelSupport") {
       		p.innerHTML += "The modelSupport library holds several support programs that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "ModelSupport programs are normally utility programs to be used by many models. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of modelSupport programs by opening the tree list and then click on the list to see information about each modelSupport program. ";
       } else if (name == "cpuHelper") {
       		p.innerHTML += "The cpuHelper library holds several intercept programs that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "CpuHelper programs are advanced intercept programs that allow the Imperas tools to 'understand' how a processor executes a program in terms if its stack, registers, etc. ";
          	p.innerHTML += "These programs allow higher level tools to be written that are independent of processor specifics. The Imperas tools include cpuHelpers for each OVP supported processor. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "User written cpuHelpers can be added to the library and can extend the simulation system in many different ways. The Imperas cpuHelper documentation provides comprehensive examples. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of cpuHelper programs by opening the tree list and then click on the list to see information about each cpuHelper program. ";
       } else if (name == "osHelper") {
       		p.innerHTML += "The osHelper library holds several intercept programs that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "osHelper programs are advanced intercept programs that allow the Imperas tools to 'understand' how an operating system executes and runs user applications, etc. ";
          	p.innerHTML += "These programs allow higher level tools to be written that are independent of operating system specifics. The Imperas tools include osHelpers for each OVP supported operating system. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "User written osHelpers can be added to the library and can extend the simulation system in many different ways. The Imperas osHelper documentation provides comprehensive examples. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of osHelper programs by opening the tree list and then click on the list to see information about each osHelper program. ";
       } else { /* tools */
       		p.innerHTML += "The tools library holds all the tools that have been placed in the Imperas/OVP directory trees. ";
      		p.innerHTML += "<br/><br/>";
          	p.innerHTML += "The Imperas Professional product includes a tool suite called 'vapTools'. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "The vapTools are a sophisticated intercept library / tool suite that by using the cpuHelper and osHelper layers/programs are independent of specific cpu or operating system.";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "It is the vapTools that provide the much of the functionality of the higher level Imperas Verification, Analysis, and Profiling (VAP) commands/tools. Example commands/tools are cache profiling, line coverage, function profiling, operating system schedule trace, etc. All the vapTools are completely non-intrusive and can work with pre-compiled user application binaries. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "User written tools can be added to the library and can extend the simulation system in many different ways. The Imperas tool documentation provides comprehensive examples. ";
      		p.innerHTML += "<br/><br/>";
      		p.innerHTML += "Browse the list of tools by opening the tree list and then click on the list to see the commands implemented in the tools. ";
       }
                       
    } else {
        var parser = new DOMParser();
        var xmlDoc = parser.parseFromString(files[i], "text/xml");
        var n;
        p.innerHTML = "";
        if ((n = xmlDoc.getElementsByTagName("semihostlibrary").length) > 0) {
            display_semihostlibrary (p, i, xmlDoc.getElementsByTagName("semihostlibrary")[0]);
        } else if ((n = xmlDoc.getElementsByTagName("hw").length) > 0) {
            if (  xmlDoc.getElementsByTagName("hw")[0].getAttribute ("library") == 'platform') {
                display_platform (p, i, xmlDoc.getElementsByTagName("hw")[0]);
            } else if (  xmlDoc.getElementsByTagName("hw")[0].getAttribute ("library") == 'module'){
                display_module (p, i, xmlDoc.getElementsByTagName("hw")[0]);
            } else if (  xmlDoc.getElementsByTagName("hw")[0].getAttribute ("library") == 'harness'){
                display_harness (p, i, xmlDoc.getElementsByTagName("hw")[0]);
            }
        } else if ((n = xmlDoc.getElementsByTagName("processor").length) > 0) {
            display_processor (p, i, xmlDoc.getElementsByTagName("processor")[0]);
        } else if ((n = xmlDoc.getElementsByTagName("peripheral").length) > 0) {
            display_peripheral (p, i, xmlDoc.getElementsByTagName("peripheral")[0]);
        } else if ((n = xmlDoc.getElementsByTagName("memory").length) > 0) {
            display_memory (p, i, xmlDoc.getElementsByTagName("memory")[0]);
        } else if ((n = xmlDoc.getElementsByTagName("mmc").length) > 0) {
            display_mmc (p, i, xmlDoc.getElementsByTagName("mmc")[0]);
        } else {
            p.innerHTML = i+" "+name;
        }
    }
}

function setProcLib(libName, cpuname) {
   for (var l=0; l<tree[libName].length; l++) {
        var fileIndex = tree[libName][l];
        var parser = new DOMParser();
        var xmlDoc = parser.parseFromString(files[fileIndex], "text/xml");
        var semi = xmlDoc.getElementsByTagName("semihostlibrary")[0];
        var seminame = semi.getAttribute ("name");
        var supProc = semi.getElementsByTagName("supportedprocessor");
        for (var i=0;i<supProc.length;i++) {
                if (supProc[i].getAttribute ("name") == "any") {
                    tLibraries.push(seminame);
                    //log(cpuname+" "+seminame+" : any");
                }
                if (supProc[i].getElementsByTagName("vlnvreference").length > 0) {
                var procSup = supProc[i].getElementsByTagName("vlnvreference")[0].getAttribute("name");
                if (cpuname == procSup) {
                    tLibraries.push(seminame);
                    //log(cpuname+" "+seminame+" : "+procSup);
                }
            }
        }
    }
}

function setProcessorLibraries() {
    for (var p=0; p<tree['processor'].length; p++) {
        var fileIndex = tree['processor'][p];
        var parser = new DOMParser();
        var xmlDoc = parser.parseFromString(files[fileIndex], "text/xml");
        var x = xmlDoc.getElementsByTagName("processor")[0];
        var cpuname = x.getAttribute ("name");
        tLibraries = [];
        setProcLib('semihosting', cpuname)
        setProcLib('intercept', cpuname)
        setProcLib('modelSupport', cpuname)
        processorsLibs[cpuname] = tLibraries;
    }
}

function buildTree () {
    if( numFiles < 1) {
        error ('The Imperas Library Documentation system is not installed properly (numFiles < 1).');
        return;
    }

    if (files.length < 1) {
        error ('The Imperas Library Documentation system is not installed properly (files.length < 1).');
        return;
    }
    
    parent.treefrm.document.getElementById("filedata").innerHTML = "";
    parent.treefrm.document.getElementById("numcomponents").innerHTML = "("+files.length+" components)";
    parent.treefrm.document.getElementById("numcomponents").style.fontSize='10';
    
    for (var i=0;i<files.length;i++) {
        //log('buildTree: '+i);
        var parser = new DOMParser();
        var xmlDoc = parser.parseFromString(files[i], "text/xml");
        var n;
        // only search for root tags.
        if      ((n = xmlDoc.getElementsByTagName("hw").length) > 0) {
            if (  xmlDoc.getElementsByTagName("hw")[0].getAttribute ("library") == 'platform') {
                tree['platform'].push(i);
            } else if (  xmlDoc.getElementsByTagName("hw")[0].getAttribute ("library") == 'module') {
                tree['module'].push(i);
            } else {
                tree['harness'].push(i);
            }
        } else if ((n = xmlDoc.getElementsByTagName("memory").length) > 0) {
            tree['memory'].push(i);
        } else if ((n = xmlDoc.getElementsByTagName("mmc").length) > 0) {
            tree['mmc'].push(i);
        //else if ((n = xmlDoc.getElementsByTagName("overrides").length) > 0) tree['overrides'].push(i);
        //else if ((n = xmlDoc.getElementsByTagName("pac").length) > 0) tree['pac'].push(i);
        } else if ((n = xmlDoc.getElementsByTagName("peripheral").length) > 0) {
            tree['peripheral'].push(i);
        } else if ((n = xmlDoc.getElementsByTagName("processor").length) > 0) {
            var name = xmlDoc.getElementsByTagName("processor")[0].getAttribute ("name");
            //if (name != "pse") {
                tree['processor'].push(i);
            //}
        } else if ((n = xmlDoc.getElementsByTagName("semihostlibrary").length) > 0) {
            var library = xmlDoc.getElementsByTagName("semihostlibrary")[0].getAttribute ("library");
            if (typeof library == "undefined")
                continue;
            if (typeof tree[library] != "undefined")
                tree[library].push(i);
            if (library == "intercept") {
                var packages = xmlDoc.getElementsByTagName("semihostlibrary")[0].getElementsByTagName("package");
                for (var p=0; p<packages.length; p++) {
                    if (packages[p] != "undefined") {
                        if (typeof tree[packages[p].getAttribute("name")] != "undefined")
                        tree[packages[p].getAttribute("name")].push(i);
                    }
                }
            }
        }
    }
}

function addImg (parent, i, alt, w, h, on) {
    var img = document.createElement("img");
	img.setAttribute ('src', "inc/_images/"+i+".png");
	img.setAttribute ('alt', alt);
	img.setAttribute ('width', w);
	img.setAttribute ('height', h);
	img.setAttribute ('onclick', on);
	img.setAttribute ('onmouseover', "this.style.cursor='hand'");
	img.setAttribute ('title', "click to open/close");
    parent.appendChild(img);
}

function addClick (parent, name, i) {
    var a = document.createElement("a");
	a.setAttribute ('style', "cursor:default");
    a.setAttribute ('onclick', "parent.show("+i+",'"+name+"')");
	a.setAttribute ('onmouseover', "this.style.cursor='hand'");
	a.setAttribute ('title', "click to find out more about "+name);
    a.innerHTML = name;
    parent.appendChild(a);
}

function addHeader (p, name, last) {
    addImg (p, (last)?"plastnode":"pnode", '+', 16, 22, "parent.toggleFolder('folder_"+name+"', this)")
    addImg (p, "folderclosed", '+', 24, 22, "parent.toggleFolder('folder_"+name+"', this)")
    addClick (p, name, -1);
}

function addItem (div, name, last, lasti, i) {
    var p = parent.treefrm.document.createElement("p");
    div.appendChild(p);
    addImg (p, (last)?"blank":"vertline", '|', 16, 22);
    addImg (p, (lasti)?"lastnode":"node", '+', 16, 22);
    addImg (p, "doc", '*', 24, 22);
    addClick (p, name, i);
}

/*
function getName (itemIndex, tagName) {
    var parser = new DOMParser();
    var xmlDoc = parser.parseFromString(files[itemIndex], "text/xml");
    var ee = xmlDoc.getElementsByTagName(tagName)[0];
    if (typeof ee == "undefined")
        return "";
    var name = ee.getAttribute ("name");
    if (typeof name == "undefined")
        return "";
    return name;
}
*/

function addFolder (name, treeName, tagName, last) {
    var list = tree[treeName];
    var fd = parent.treefrm.document.getElementById("filedata");
    var p = parent.treefrm.document.createElement("p");
    fd.appendChild(p);
    addHeader (p, name, last);
    var div = parent.treefrm.document.createElement("div");
    div.setAttribute ('id', "folder_"+name);
    fd.appendChild(div);
    for (var i=0; i<list.length; i++) {
        var itemIndex = list[i];
        var parser = new DOMParser();
        var xmlDoc = parser.parseFromString(files[itemIndex], "text/xml");
        if ((tagName != "module")&&((tagName != "harness"))) {
            var ee = xmlDoc.getElementsByTagName(tagName)[0]; 
        } else {
            var ee = xmlDoc.getElementsByTagName("hw")[0];
        }
        if (typeof ee == "undefined")
            continue;
        var xx = ee.getAttribute ("name");
        if (typeof xx == "undefined")
            continue;
        var itemName = xx;
        var version = ee.getAttribute ("version");
        var vendor = ee.getAttribute ("vendor");
        
        addItem (div, 
            (version=="1.0") ? (itemName) : (itemName+" | "+vendor+" | "+version),
            last, 
            (i==list.length-1)?1:0, 
            itemIndex);
    }
}

function displayTree () {
    addFolder ("platform", 'platform', 'hw', 0);
    addFolder ("module", 'module', 'module', 0);
    addFolder ("harness", 'harness', 'harness', 0);
    addFolder ("processor", 'processor', 'processor', 0);
    addFolder ("semihosting", 'semihosting', 'semihostlibrary', 0);
    addFolder ("peripheral", 'peripheral', 'peripheral', 0);
    addFolder ("memory", 'memory', 'memory', 0);
    addFolder ("mmc", 'mmc', 'mmc', 0);
    addFolder ("intercept", 'intercept', 'semihostlibrary', 0);
    addFolder ("modelSupport", 'modelSupport', 'semihostlibrary', 0);
    addFolder ("cpuHelper", 'cpuHelper', 'semihostlibrary', 0);
    addFolder ("osHelper", 'osHelper', 'semihostlibrary', 0);
    addFolder ("tools", 'tools', 'semihostlibrary', 1);
    
    // and when initializing this tree, reset the main page text
    var p = parent.mainfrm.document.getElementById("maindata");
    var line = "<b>This is the main page for Imperas and OVP local library documentation.</b><br/>";
    line += "If you click on the left hand tree browser you can see what is available.<br/>";
    line += "(Click on the Libary Documentation title to return to this page.)<br/>";
    line += "If you click on a specific item you can see here its main parameters.<br/><br/>";
    line += "If you click on the top of this page you return to the main Local Documentation page.<br/><br/>";
    line += "If you remove, add, or install any new library items, then re-run the library documentation generator as described below.<br/>";
    line += "<p><b>Running libDocGen - the Library Documentation Generator</b><br/>";
    line += "1) In a linux/bash or minsys/shell cd/move into $IMPERAS_HOME/doc/library.<br/>";
    line += "2) Run libDocGen.bat or libDocGen.bash to generate uptodate library documentation.<br/><br/>";
    line += "If you have added vlnv root directories not underneath $IMPERAS_HOME/lib then edit the libDocGen scripts and re-run to include your directories.<br/></p>";
    line += "<b>Last time libDocGen was run was: "+lastRunDate+".</b><br/>";
    line += "<b>File name output was: "+fileNameRun+".</b><br/>";
    p.innerHTML = line;
}

