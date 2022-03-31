/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


//  2x16 Alphanumeric Display programmers View

#include "peripheral/ppm.h"

#include "pse.igen.h"
#include "user.h"

extern Uns8 dataArray[33];
//
// Event handles for view events
//

ppmViewEvent writeEnableEvent;
ppmViewEvent writeDisableEvent;
ppmViewEvent writeSetEvent;
ppmViewEvent writeClearEvent;

void actionCB (void * userData) {

    if (PSE_DIAG_HIGH) bhmMessage("I", "ACTION TRIGGER","Clear Display");

    clearDisplay();
}

//
// Initialize programmer's view of timer peripheral
//
void initProgrammersView(){

    //
    // databus read/write
    //
    // Create view object for databus read/write
    ppmViewObject busView = ppmAddViewObject(
        NULL,
        "databus",
        "last 8-bit value written on bus to this peripheral"
    );

    // Associate register view object with C "display.bus" variable (read for value)
    ppmSetViewObjectRefValue(busView, PPM_VVT_UNS8, &busPort_A_data.data.value);

    //
    // Control register
    //
    // Create view object for control register
    ppmViewObject controlView = ppmAddViewObject(
        NULL,
        "controlEvents",
        "8-bit control register defined events"
    );

    // Associate register view object with C "display.control" variable (read for value)
    ppmSetViewObjectRefValue(controlView, PPM_VVT_UNS8, &busPort_A_data.control.value);

    // Special events
    writeEnableEvent  = ppmAddViewEvent(controlView, "enable",  "The display is enabled");
    writeDisableEvent = ppmAddViewEvent(controlView, "disable", "The display is disabled");
    writeSetEvent     = ppmAddViewEvent(controlView, "set",     "All segments of the display are set");
    writeClearEvent   = ppmAddViewEvent(controlView, "clear",   "All segments of the display are cleared");

    //
    // Display
    //
    // Create view object for control register
    ppmViewObject displayView = ppmAddViewObject(
        NULL,
        "display",
        "32x 8-bit data registers"
    );

    // Associate register view object with C "display.data" variable (read for value)
    ppmSetViewObjectRefValue(displayView, PPM_VVT_STRING, &dataArray[busPort_A_data.address.value]);

    // An action on the display causing the display to be cleared
    ppmAddViewAction(displayView, "clear", "clear display", &actionCB, 0);


}

