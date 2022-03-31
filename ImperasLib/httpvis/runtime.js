// runtime.js
/*
 *
 * Copyright (c) 2005-2016 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

function startRefresh(path, rate) {
    sendCommand(path,'Refresh','none');
    setTimeout('startRefresh("'+path+'", '+rate+')', rate);
}

// used for testing
var ovpClasses = ["ovplabel", "ovpled", "ovpbuttonled", "ovplcd7seg", "ovplcd2x16", "ovpswitch", "ovpswitchpush", "ovpswitchdip", "ovpswitchtoggle", "ovpbar", "ovpvertbar",
    "ovppower", "ovptext", "ovpgauge", "ovphistogram"];

var powerIsOn = true;
    
function sendCommand(path, command, scvalue) {
    var request = new XMLHttpRequest();
    request.open('GET', path+'?command='+command+'&value='+scvalue, true);
    request.onreadystatechange = function()     {
      if ((request.readyState==4) && (request.status==200))         {       // 3 = LOADING, 200 = DONE
            if (request.responseText[0] == "<") {
                logalert ("runtime.js sendCommand ( Your C code function (BHM_HTTP_POST_FN/OCL_HTTP_POST_FN) has an oddity.\n\n"+request.responseText);
            } else {
                try{
                    var data = JSON.parse(request.responseText); // get all the data from the responseText in JSON format and do a write to each...
                }catch(e){
                        logalert ("runtime.js sendCommand ( json data string ) error. Your C code function (BHM_HTTP_GET_FN/OCL_HTTP_GET_FN) has syntax error in the string. "+e+"\n\n"+request.responseText);
                        return;
                    //}
                }
            }
            //trace(data.ovpelement.length);
            for (i = 0; i < data.ovpelement.length; i++) { 
                var value = data.ovpelement[i].idvalue;
                var idname = data.ovpelement[i].idname;
                if (document.getElementById(data.ovpelement[i].idname) === null) {
                    logalert ("runtime.js sendCommand ( json data string ) error. Your C code function (BHM_HTTP_GET_FN/OCL_HTTP_GET_FN) has element ("+data.ovpelement[i].idname+") which is undefined in the html");
                    return;
                }
                var classname = document.getElementById(data.ovpelement[i].idname).className;
                trace(classname+" "+idname+" "+value);
                switch (classname) {
                    case 'ovpled':
                        (new Image()).src = "led-red.jpg"; // cache images we might need
                        (new Image()).src = "led-black.jpg";
                        if ((value & 0x01) == 1) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=led-red.jpg>";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=led-black.jpg>";
                        }
                        break;
                    case 'ovpbuttonled':
                        (new Image()).src = "button-led-red.jpg"; // cache images we might need
                        (new Image()).src = "button-led-green.jpg";
                        if ((value & 0x01) == 1) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=button-led-red.jpg onmouseover=this.style.cursor='pointer'>";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=button-led-green.jpg onmouseover=this.style.cursor='pointer'>";
                        }
                        break;
                    case 'ovplcd7seg':
                        // cache all images we might need
                        var imgArray = new Array("seg7.png", 
                            "seg7-0.png", "seg7-1.png", "seg7-2.png", "seg7-3.png",
                            "seg7-4.png", "seg7-5.png", "seg7-6.png", "seg7-7.png",
                            "seg7-8.png", "seg7-9.png", "seg7-a.png", "seg7-b.png",
                            "seg7-c.png", "seg7-d.png", "seg7-e.png", "seg7-f.png"
                            );
                        for (var iii=0; iii<imgArray.length; iii++) {
                            (new Image()).src = imgArray[iii];
                        }
                        var lcdimg = "seg7.png";
                        switch (value & 0x0f) {
                            case 0x00: lcdimg = "seg7-0.png" ; break;
                            case 0x01: lcdimg = "seg7-1.png" ; break;
                            case 0x02: lcdimg = "seg7-2.png" ; break;
                            case 0x03: lcdimg = "seg7-3.png" ; break;
                            case 0x04: lcdimg = "seg7-4.png" ; break;
                            case 0x05: lcdimg = "seg7-5.png" ; break;
                            case 0x06: lcdimg = "seg7-6.png" ; break;
                            case 0x07: lcdimg = "seg7-7.png" ; break;
                            case 0x08: lcdimg = "seg7-8.png" ; break;
                            case 0x09: lcdimg = "seg7-9.png" ; break;
                            case 0x0A: lcdimg = "seg7-a.png" ; break;
                            case 0x0B: lcdimg = "seg7-b.png" ; break;
                            case 0x0C: lcdimg = "seg7-c.png" ; break;
                            case 0x0D: lcdimg = "seg7-d.png" ; break;
                            case 0x0E: lcdimg = "seg7-e.png" ; break;
                            case 0x0F: lcdimg = "seg7-f.png" ; break;
                        }
                        document.getElementById(data.ovpelement[i].idname).innerHTML="<img src="+lcdimg+" >";
                        break;
                    case 'ovplcd2x16':
                            (new Image()).src = "lcd2x16.jpg";  // cache all images we might need
                            var line1 = value.substring(0,16);
                            var line2 = value.substring(16,32);
                            document.getElementById(data.ovpelement[i].idname).innerHTML=
                                "<img id='ovplcd2x16_image' src='lcd2x16.jpg'>"+
                                "<p class='ovplcd2x16_line1'>"+line1+"</p>"+
                                "<p class='ovplcd2x16_line2'>"+line2+"</p>";
                        break;
                    case 'ovpswitch':
                        (new Image()).src = "sw-off.jpg";  // cache all images we might need
                        (new Image()).src = "sw-on.jpg";  
                        if ((value & 0x01) == 0) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-off.jpg onmouseover=this.style.cursor='pointer'>";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-on.jpg onmouseover=this.style.cursor='pointer'>";
                        }
                        break;
                    case 'ovpswitchpush':
                        (new Image()).src = "sw-push.jpg";  // cache all images we might need
                        (new Image()).src = "sw-push-down.jpg";  
                        if ((value & 0x01) == 0) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-push.jpg onmouseover=this.style.cursor='pointer'>";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-push-down.jpg onmouseover=this.style.cursor='pointer'>";
                        }
                        break;
                    case 'ovpswitchdip':
                        (new Image()).src = "sw-dipx1-up.jpg";  // cache all images we might need
                        (new Image()).src = "sw-dipx1-down.jpg";  
                        if ((value & 0x01) == 0) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-dipx1-up.jpg  title='click me' onmouseover=this.style.cursor='pointer'>";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-dipx1-down.jpg  title='click me' onmouseover=this.style.cursor='pointer'>";
                        }
                        break;
                    case 'ovpswitchtoggle':
                        (new Image()).src = "sw-toggle-up.jpg";  // cache all images we might need
                        (new Image()).src = "sw-toggle-down.jpg";  
                        if ((value & 0x01) == 0) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-toggle-up.jpg onmouseover=this.style.cursor='pointer' >";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-toggle-down.jpg onmouseover=this.style.cursor='pointer'>";
                        }
                        break;
                    case 'ovpswitchbutton':
                        (new Image()).src = "btn_on.png";  // cache all images we might need
                        (new Image()).src = "btn_off.png";  
                        if ((value & 0x01) == 0) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=btn_on.png onmouseover=this.style.cursor='pointer' >";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=btn_off.png onmouseover=this.style.cursor='pointer'>";
                        }
                        break;
                    case 'ovpbar':
                        document.getElementById(data.ovpelement[i].idname).innerHTML=
                            "<table border=0 cellspacing=0 cellpadding=1><td class='ovpbarline'>"+
                            "<img src=bar-emerald.png width='"+(value)+"%' height=20 alt='"+(value)+"%'>"+
                            "<img src=bar-snow.png width='"+(100-value)+"%' height=20 alt='"+(100-value)+"%'>"+
                            "</td></table>"
                        break;
                    case 'ovpvertbar': // assumes value is 0-100
                        document.getElementById(data.ovpelement[i].idname).innerHTML=
                            "<table border=0 cellspacing=0 cellpadding=1><td class='ovpvertbarline'>"+
                            "<img src=bar-black.png height='"+(100-value)+"%' width=10 alt='"+(100-value)+"%'>"+
                            "<img src=bar-emerald.png height='"+(value)+"%' width=10 alt='"+(value)+"%'>"+
                            "</td></table>"
                        break;
                    case 'ovppower':
                            (new Image()).src = "power.png";  // cache all images we might need
                            if (powerIsOn) {
                                document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=power.png>";
                            } else {
                                document.getElementById(data.ovpelement[i].idname).innerHTML="SIMULATION STOPPED";
                            }
                        break;
                    case 'ovpreset':
                        (new Image()).src = "sw-reset-red.png";  // cache all images we might need
                        (new Image()).src = "sw-reset-blue.png";  
                        if ((value & 0x01) == 0) {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-reset-red.png>";
                        } else {
                            document.getElementById(data.ovpelement[i].idname).innerHTML="<img src=sw-reset-blue.png>";
                        }
                        break;
                    case 'ovptext':
                            document.getElementById(data.ovpelement[i].idname).innerHTML=value;
                        break;
                    case 'ovpgauge':
                        var id = data.ovpelement[i].idname;
                        var minValue = window[id].min;
                        var maxValue = window[id].max;
                        if (value > maxValue) value = maxValue;
                        if (value < minValue) value = minValue;
                        var id = data.ovpelement[i].idname;
                        window[id].draw( value );
                        break;
                    case 'ovphistogram': // assumes value is 0-100
                        var idname = data.ovpelement[i].idname;
                        var lineWidth = Number(document.getElementById(idname).getAttribute("linewidth"));
                        var canvasHeight = Number(document.getElementById(idname).getAttribute("height"));
                        var canvasWidth = Number(document.getElementById(idname).getAttribute("width"));
                        var canvas = document.getElementById(idname);
                        ctx = canvas.getContext('2d');
                        ctx.lineWidth = lineWidth;
                        
                        // move it all to the right
                        var imgData = ctx.getImageData(0,0, canvasWidth-lineWidth, canvasHeight);
                        ctx.putImageData(imgData,lineWidth,0);
                        
                        // calc line y pos
                        var y = canvasHeight - Math.round((value/100)*canvasHeight);
                        
                        // draw top bit of line in black
                        ctx.beginPath();
                        ctx.strokeStyle = '#000000'; // black
                        ctx.moveTo(0,0);
                        ctx.lineTo(0,y);
                        ctx.stroke();
                        
                        // then bottonm part in green
                        ctx.beginPath();
                        ctx.strokeStyle = '#00FF00'; // green
                        ctx.moveTo(0,y+1);
                        ctx.lineTo(0,canvasHeight);
                        ctx.stroke();
                        break;
                	case 'imp_image':
                		document.getElementById(idname).innerHTML="<img src=imperas.png>";
                        break;
                    case '': // ignore, so we dont get empty alerts to screen...
                        break;
                    default:
                        // this is not a built-in, try one of user local ones
                        var ok = false;
                        if (typeof localClassDecoder === "function") {
                            ok = localClassDecoder (classname, data.ovpelement[i].idname, value);
                        } 
                        if (!ok) {
                            logalert ("runtime.js sendCommand ( json data string ) has classname ("+classname+") not recognised.");
                            return;
                        }
                        break;

                }
            }            
            //trace(data); // to see in javascript console
        } else {
        }
    }
    request.send();
}

function logalert (s) {
    trace (s);
    alert(s);
}

function trace (s) {
    var logtoscreen = 0; // 0 or 1
    
    if (window.console) { // if got a console, eg chrome, later firefox, safari etc...
        if (typeof console.log === "function") {
            console.log(s);
        }
    }
    
    if (logtoscreen) {
        document.getElementById("console").innerHTML += s +"<br/>"; // as firefox on linux does not allow console.log
    }
}

function ovpswitchclicked (e) {
    var targ;
    if (e.target) {
        targ = e.target;
    } else if (e.srcElement) {
        targ = e.srcElement;
    } else {
        alert ("ovpswitchclicked() targ not set");
    }
	if (targ.nodeType == 3) {
        // defeat Safari bug
		targ = targ.parentNode;
    }
	if (targ.firstChild) {
		targ = targ.firstChild;
    }
    var tname;
    var idname;
    tname = targ.tagName; // tag type == img
    idname = targ.parentNode.id; // get div above's id
    classname = targ.parentNode.className; // get div above's class 
    trace ("You clicked on " + tname + " element: id="+idname+" Class="+classname);
    if ((classname == 'ovpswitch') || (classname == 'ovpswitchtoggle') ||
        (classname == 'ovpswitchpush') ||
        (classname == 'ovpswitchdip') || (classname == 'ovppower') ||
        (classname == 'ovpbuttonled') || (classname == 'ovpreset')
          )  { // same functionality, different class, so can get different image    
        if (classname == 'ovppower') { // special
            powerIsOn = false;
            document.getElementById(idname).innerHTML="";
        }
        var request = new XMLHttpRequest();
        request.open('POST', "/?click", false);
        request.send(idname+"=clicked");
        //sendCommand("/",'Refresh','none');

    } else {
        // switch not one of the built-in's try user local one
        var ok = false;
        if (typeof localSwitchDecoder === "function") {
            //trace ("runtime.js found localSwitchDecoder() to decode: "+classname+" "+idname);
            ok = localSwitchDecoder (classname, idname);
        } 
        if (!ok) {
            if (classname == '') {
                // do nothing if get blank clicks...
            } else {
                logalert ("runtime.js ovpswitchclicked ( classname: "+classname+", id: "+idname+" ) not recognized: ");
            }
        }
    }
}
