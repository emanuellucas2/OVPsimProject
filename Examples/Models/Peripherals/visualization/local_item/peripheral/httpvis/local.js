// local.js
// when displaying, local function if defined is called: localClassDecoder (classname, idname, value)
// when processing switches, local function if defined is called: localSwitchDecoder (classname, idname)

// process (display) local item, return true if ok, else false if not found etc
function localClassDecoder (classname, idname, value) {
    //trace ("in localClassDecoder ("+classname+", "+idname+", "+value+")");
    switch (classname) {
        case 'localitem_a':
            if (value & 0x01 == 1) {
                document.getElementById(idname).innerHTML="<img src=minus.jpg>";
            } else {
                document.getElementById(idname).innerHTML="<img src=plus.jpg>";
            }
            return true; // good return, processed
            break;
        default:
            return false; // error return, not found
            break;
    }
}

// process local item, return true if ok, else false if not found etc
function localSwitchDecoder (classname, idname) {
    //trace ("in localSwitchDecoder ("+classname+", "+idname+")");
    switch (classname) {
        case 'localitem_a':
            var request = new XMLHttpRequest();
            request.open('POST', "/?click", true);
            request.send(idname+"=clicked");
            return true; // good return, processed
            break;
        default:
            return false; // error return, not found
            break;
    }
}