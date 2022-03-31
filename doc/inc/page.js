// page.js, build dynamic doc page based on .js data
// copy to website as inc/ovpdoc_page.js

var pageExists = 1;
var pageIsOnWebsite;

// declare globals to be set in data file
var dataExists;
var pageTitle;
var documentName;
var headerGraphic;
var versionDate;
var webSite;
var secTitle ;
var secFile ;
var secDescr ;
var secGroupTitle ;

var img = "<img src=../inc/link.png height='10' border='0'>";

// internal variables
if(typeof dir == "undefined") {
	var dir = "../";
}
if(typeof incDir == "undefined") {
	var incDir = "../inc/";
}

function error (str) {
    document.write('<h2>Error: '+str+'</h2>');
}

function checkExist() {
	if(typeof dataExists == "undefined") {
		// we don't have the data file - so init some....
		dataExists = 0;
		pageTitle = "Undefined OVP/Imperas Page";
		documentName = "OVP/Imperas unknown document";
		headerGraphic = "doc_header.gif";
		versionDate = "(October 10) 2010wxyz.0";
	} else {
		if (secTitle.length < 1) {
			error ('The Imperas Documentation system is not installed properly (secTitle.length < 1).');
		}
		if (secTitle.length != secDescr.length) {
			error ('The Imperas Documentation system is not installed properly (secTitle.length != secDescr.length).');
		}		
	}
	// and for optionals
	if(typeof webSite == "undefined") {
		webSite = "";
	}
}

function headerDraw () {
    var line ="";
	
    line += "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.0 Transitional//EN'>";
    line += "<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>";
	line += "<head>";
	line += "<link rel='stylesheet' href='"+incDir+"style.css' type='text/css' media='screen' />";
	line += "<title>"+pageTitle+"</title>";
	line += "</head><body>";
	line += "<div style='width: 800px; height: 102px'>";
    line += "<a href='"+dir+"/index.html' title='click to go the main Imperas/OVP local documentation page'>";
    line += "	<img src='"+incDir+headerGraphic+"' alt='Document Header' height='120' width='800' border='0'>";
    line += "</a>";
	line += "<div >";
    line += "<table cellpadding='0' cellspacing='0' style='margin: 0px; padding: 0px; border: 0px; margin-left: 35px;'>";
    line += "  <tbody><tr>";
    line += "    <td valign='top' class='presentation'>";

    document.write(line);
}

function introDraw() {
    var line ="";
	
    // line += "<h1>** Welcome to the Imperas/OVP LOCAL Documentation on "+documentName+"<br/>** "+versionDate+"</h1>";
    line += "<h1>** Welcome to the Imperas/OVP LOCAL Documentation on "+documentName+"</h1>";
    line += "<p>You are looking at the local documentation that is part of your installation.</p>";
    line += "<p>To visit the <a href=http://www.ovpworld.org title='click to visit'>www.OVPworld.org website - go here...</a> ";
    line += " for <a href=http://www.imperas.com title='click to visit'>www.imperas.com website - go here...</a></p>";
	if (webSite != "") {
		line += "<p>To visit the <a href=http://"+webSite+" title='click to visit'>"+webSite+" website - go here...</a></p>";
	}

    document.write(line);
}

function secGroupTitleDraw (secGroupName) {
    var line = "";
    line += "<br/>";
    line += "<br/>";
    line += "<hr>";
    line += "<hr>";
    line += "<h2><span><center>"+secGroupName+"</center></span></h2>";
    document.write(line);
}

function sectionDraw (i) {
	var doit = 0;
	if (typeof secExist[i] == "undefined") {
		doit = 1;
	} else {
		if (secExist[i] == "") {
			doit = 1;
		} else {
			var proof = secExist[i];
			//document.write('<br/>proof='+proof);
			var val = eval(proof);
			//document.writeln('<br/>val='+val);
			if (val == 1) {
				doit = 1;
			}
		}
	}
	
	if (doit) {
		var line = "";
		if (typeof secGroupTitle[i] == "undefined") {
        } else {
            secGroupTitleDraw (secGroupTitle[i]);
        }
		line += "<hr>";
		line += "<h2>"+secTitle[i]+"</h2>";
		if (typeof secFile[i] == "undefined") {
		} else {
			if (typeof secDoxygen[i] == "undefined") {
				if (pageIsOnWebsite == 1) { // links
					line += "<a href=/documents/"+secFile[i]+" title='click to view file' >"+secFile[i]+"</a><br/>";
				} else if (pageIsOnWebsite == 2) { // downloads
					line += "<a href=/documentation.php?doc="+secFile[i]+" title='click to download file' >"+secFile[i]+"</a><br/>";
				} else {
					line += "<a href="+secFile[i]+" title='click to view file' >"+secFile[i]+" "+img+"</a><br/>";
				}
			} else {
				if (pageIsOnWebsite) { // on website
					line += "" + secFile[i] + " (ONLY IN LOCAL INSTALLATION)<br/>";
				} else {
					line += "<a href="+secDoxygen[i]+" title='click to view API Reference (Doxygen)' >"+secFile[i]+" "+img+"</a><br/>";
				}
			}
		}


		line += ""+secDescr[i]+"<br/><br/>";

		document.write(line);
	} else {
	}
}

function contentDraw() {
    var line ="";

	if(! dataExists) {
		line += "<h2>Documentation Missing</h2>";
		line += "<p>For some reason this page is blank - please report this to your supplier...</p>";
	} else {
		for (var i=0;i<secTitle.length;i++) {
			sectionDraw(i);
		}
	}
	
    document.write(line);
}

function libraryDraw () {
    var line ="";
	line += "<hr>";
	line += "<h2>Library Documentation</h2>";
	line += "For documentation on the  ";
	line += "<a href="+dir+"/library/index.html title='click to view'>Imperas Library click here.</a><br/><br/>";	
	document.write(line);
}

function datasheetsDraw () {
	if(typeof datasheetsExist == "undefined") {
	} else {
        secGroupTitleDraw("IMPERAS / OVP DATASHEETS, APPS NOTES, LIBRARY DOCUMENTATION");
		var line ="";
		line += "<hr>";
		line += "<h2>OVP and Imperas Datasheets</h2>";
		line += "For datasheets related to OVP and Imperas products, ";
		line += "<a href="+dir+"/datasheets/index.html title='click to view'>visit here.</a><br/><br/>";		
		document.write(line);
	}
}

function appnotesDraw () {
	if(typeof appnotesExist == "undefined") {
	} else {
		var line ="";
		line += "<hr>";
		line += "<h2>OVP and Imperas Application Notes</h2>";
		line += "For Application Notes related to OVP and Imperas products, ";
		line += "<a href="+dir+"/appnotes/index.html title='click to view'>visit here.</a><br/><br/>";		
		document.write(line);
	}
}

function tailDraw () {
    var line ="";

	line += "<hr>";
 	line += "</td>";
    line += "<td valign='top' class='right'></td>";
    line += "</tr></tbody>";
    line += "</table>";
    line += "<div style='width: 800px; height: 14px;'><img src='"+incDir+"footer.gif' alt='footer' height='14' width='800' border='0'></div>";
    line += "</body></html>";
	
    document.write(line);
}



function screenDraw () {
	pageIsOnWebsite = 0;
	checkExist();
    headerDraw();
	introDraw();
	contentDraw();
	datasheetsDraw();
	appnotesDraw();
	libraryDraw();
    tailDraw();
}

function screenDrawWebSite (pnws) { // 1 for links, 2 for downloads
	pageIsOnWebsite = pnws;
	checkExist();
    //headerDraw();
	//introDraw();
	contentDraw();
	//datasheetsDraw();
	//libraryDraw();
    //tailDraw();
}