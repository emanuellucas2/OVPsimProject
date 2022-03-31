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

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#include "ucd9012a.user.h"

#define PREFIX "PMBUS_UCD9012A"

// create the monitor structure
vmonT vmon;

// include common powermonitor functions
#include "ovpworld.org/modelSupport/powermonitor/1.0/pse/powermonitor.user.c.h"

// include common pmbus access functions
#include "pmbus.ovpworld.org/modelSupport/pmbus/1.0/pse/pmbus.user.c.h"


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    char configfile[BHM_MAX_PATH];
    if (!bhmStringParamValue("config", configfile, sizeof(configfile))) {
        // not specified
    } else {
        // Read configuration information
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_CN", "Initializing Data");

        // setup using the configuration file
        readConfiguration(configfile);
    }

    readDefaultConfiguration();    // initialise static read values

    // Configure native
    Uns32 nativeDiag = (diagnosticLevel & 0xc) >> 2;
    if(initNative(nativeDiag)){
        if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX ,"Native Initialised (diag %d)", nativeDiag);
    }

    // Must be last thing in constructor
    initPowerMonitorData();
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
