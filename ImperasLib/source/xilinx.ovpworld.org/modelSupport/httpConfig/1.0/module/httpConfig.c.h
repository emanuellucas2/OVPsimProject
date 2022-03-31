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
#include <stdlib.h>

#include "op/op.h"
#include "ocl/oclhttp.h"

#ifndef MODULE_NAME
#define MODULE_NAME "Visualization"
#endif

typedef struct optModuleObjectS {
    // insert module persistent data here
    optModuleP  mi;     // root module
    optModuleP  mps;    // PS module
    optModuleP  mpl;    // PL module
    Uns32       diag;   // diagnostic level
} optModuleObject;

// Led and switch information for board
Uns32    ledNumber;        // number of LEDs
Uns32    switchNumber;     // number of switches
Uns32    ledMask;          // mask for ease of use

typedef struct netInfoS {
    Uns32   position;       // position in visualization array
    Uns32   bit;            // position in net
    optNetP net;            // net handle
    char *  netName;        // net name
} netInfo, *netInfoP;

#define MAX_BITS 16
netInfo  ledInfo[MAX_BITS];     // array of positions in GPIO register containing LED bits
netInfo  switchInfo[MAX_BITS];  // array of positions in GPIO register containing SWI bits

Uns32     gpioRegSw;        // current GPIO Switch value
Uns32     gpioRegLed;       // current GPIO LED value

static void redraw (octHTTPChannelP ch) {

    oclHTTPElementOpen(ch, "ovpelement");

    Uns32 i;
    for (i=0;i<ledNumber;i++) {
        char led[8];
        sprintf(led, "led%d", i);
        oclHTTPKeyPrintf(ch, led, "%d", (gpioRegLed & (1<<ledInfo[i].position))?1:0);
    }
    for (i=0;i<switchNumber;i++) {
        char sw[8];
        sprintf(sw, "sw%d", i);
        oclHTTPKeyPrintf(ch, sw, "%d", (gpioRegSw & (1<<switchInfo[i].position))?1:0);
    }

    oclHTTPKeyPrintf(ch, "power0", "0");
    oclHTTPElementClose(ch, "ovpelement");
    oclHTTPSend(ch);
}

static OCL_HTTP_GET_FN(get) {
    redraw (ch);
}

#define FLIP_BIT(_d, _b) ((_d & (1<<_b)) ? (_d &= ~(1<<_b)) : (_d |= (1<<_b)))
#define GET_BIT(_d, _b)  ((_d & (1<<_b)) ? 1 : 0

static OCL_HTTP_POST_FN(post) {
    optModuleObjectP object = userData;

    Uns32 item;
    char  action[32];

    // check for switches
    if(sscanf(body,"sw%d=%s", &item, action)==2) {
        if(strstr(action, "clicked")) {
            FLIP_BIT(gpioRegSw, switchInfo[item].position);
            if(switchInfo[item].net) {
                Uns32 sw = opNetValue(switchInfo[item].net);     // read current net value
                if (switchInfo[item].bit != -1)
                    FLIP_BIT(sw, switchInfo[item].bit);     // flip bit
                else
                    FLIP_BIT(sw, 0);                        // flip bit
                    if(object->diag > 1)
                        opMessage("I", MODULE_NAME "_HTTP",
                                  "switch %d action %s write switches (bit %d position %d gpio 0x%08x/0x%08x)",
                                  item, action,
                                  switchInfo[sw].bit != -1 ? switchInfo[sw].bit : 0 ,
                                  switchInfo[item].position, sw, gpioRegSw);

                opNetWrite(switchInfo[item].net, sw);       // write back to net
            } else {
                if(object->diag > 1)
                    opMessage("I", MODULE_NAME "_HTTP", "switch %d action %s No Net Registered (gpio 0x%08x)",
                            item, action, gpioRegSw);

            }
        }

    // check for power button
    } else if (sscanf(body,"power%d=%s",&item, action)==2) {
        if(strstr(action, "clicked")) {
            opMessage("I", MODULE_NAME "_SW", "Power Switch pushed - terminating simulation.");
            opModuleFinish(object->mi, 0);
        }
    } else {
        opMessage("W", MODULE_NAME "_HTTP", "Unknown input '%s' - ignored", body);
    }
    redraw (ch);
}

OP_NET_WRITE_FN(gpioChangeCallback) {

    Uns32 led  = (Uns32)(UnsPS) userData;
    Uns32 mask = 1 << ledInfo[led].position;
    Uns32 ledOut;
    if (ledInfo[led].bit != -1)
        ledOut = (value >> ledInfo[led].bit) & 1;
    else
        ledOut = value & 1;

    // only change the modified LED position value
    if (ledInfo[led].bit != -1) {
        gpioRegLed = (gpioRegLed & ~mask) | (ledOut << ledInfo[led].position);
    } else {
        gpioRegLed = (gpioRegLed & ~mask) |  ledOut;
    }

//        opMessage("I", MODULE_NAME "_HTTP", "Net %d (%d) value %d (gpio 0x%08x)",
//                led, ledInfo[led].position, ledOut, gpioRegLed);

}

static Bool monitorGPIO(optModuleObjectP object, char *name, Uns32 led) {

    ledInfo[led].net = opObjectByName(object->mps, name, OP_NET_EN).Net;
    if(!ledInfo[led].net) {
        ledInfo[led].net = opObjectByName(object->mpl, name, OP_NET_EN).Net;
    }

    if(object->diag)
        opMessage("I", MODULE_NAME "_LED_NET", "Add net callback for '%s' (led %d %d/%d)",
                                 name, led,
                                 ledInfo[led].position,
                                 ledInfo[led].bit != -1 ? ledInfo[led].bit : 0);


    if (ledInfo[led].net) {
        opNetWriteMonitorAdd(ledInfo[led].net, gpioChangeCallback, (void*)(UnsPS)led);
        return True;
    } else {
        opMessage("W", MODULE_NAME "_NET_LED", "Cannot find LED GPIO net '%s' (led %d %d/%d)",
                                 name, led,
                                 ledInfo[led].position,
                                 ledInfo[led].bit != -1 ? ledInfo[led].bit : 0);

        return False;
    }
}

static Bool gpioSwitchUpdateNet(optModuleObjectP object, char *name, Uns32 sw) {

    switchInfo[sw].net = opObjectByName(object->mps, name , OP_NET_EN).Net;
    if(!switchInfo[sw].net) {
        switchInfo[sw].net = opObjectByName(object->mpl, name , OP_NET_EN).Net;
    }

    if(switchInfo[sw].net) {
        if(object->diag)
            opMessage("I", MODULE_NAME "_SW_NET", "Find net '%s' (sw %d %d/%d)",
                                    name, sw,
                                    switchInfo[sw].position,
                                    switchInfo[sw].bit != -1 ? switchInfo[sw].bit : 0);

        return True;
    }

    opMessage("W", MODULE_NAME "_SW_NET", "Cannot find net '%s'  (sw %d %d/%d)",
                                    name, sw,
                                    switchInfo[sw].position,
                                    switchInfo[sw].bit != -1 ? switchInfo[sw].bit : 0);
    return False;
}

void configFileRead (optModuleObjectP object, const char * configfile) {
    //
    // Configuration of the LED and Switch GPIO usage
    //
    #define MAXLINE  1024
    FILE *configFileFP = NULL;

    if(configfile) {
        if(object->diag)
            opMessage("I", MODULE_NAME "_CFG", "Configuring GPIO LEDs and Switches using '%s'", configfile);


        if(!(configFileFP = fopen(configfile, "r"))) {
            opMessage("E", MODULE_NAME "_NCF", "Could not open config file '%s', "
                           "specify using 'configfile' argument", configfile);
        } else {
            // Read configuration information
            char line[MAXLINE];
            while (fgets(line, MAXLINE, configFileFP) != NULL){
                if (line[0] == '#') {
                    // Ignore comment line
                } else {
                    Uns32 items, number, position, bitfield;
                    char gpionetname[32];  // name of the GPIO connection carrying data

                    // Check for definition of number of LEDs
                    if ((items = sscanf(line, "lednumber %d", &number)) == 1) {
                        ledNumber = number;
                        if(object->diag)
                            opMessage("I", MODULE_NAME "_LN", "led Number set %d",
                                    number);


                    // Check for definition an LED
                    } else if ((items = sscanf(line, "led %d %d %s %d", &number, &position, gpionetname, &bitfield)) == 4) {
                        ledInfo[number].position = position;
                        ledInfo[number].bit      = bitfield;
                        ledInfo[number].netName  = strdup(gpionetname);
                        if(object->diag)
                            opMessage("I", MODULE_NAME "_LP", "led %d at %d (net %s, bit %d)",
                                    number,
                                    position,
                                    gpionetname,
                                    bitfield);

                        if(strncmp("-", gpionetname, 1))  // defined a GPIO net
                            monitorGPIO(object, gpionetname, number);

                    // Check for definition an LED
                    } else if ((items = sscanf(line, "led %d %d %s", &number, &position, gpionetname)) == 3) {
                        ledInfo[number].position = position;
                        ledInfo[number].bit      = -1;
                        ledInfo[number].netName  = strdup(gpionetname);
                        if(object->diag)
                            opMessage("I", MODULE_NAME "_LP", "led %d at %d (net %s)",
                                    number,
                                    position,
                                    gpionetname);

                        if(strncmp("-", gpionetname, 1))  // defined a GPIO net
                            monitorGPIO(object, gpionetname, number);


                    // Check for definition of number of Switches
                    } else if ((items = sscanf(line, "swinumber %d", &number)) == 1) {
                        switchNumber = number;
                        if(object->diag)
                        opMessage("I", MODULE_NAME "_LN", "swi Number set %d", number);


                    // Check for definition of a switch
                    } else if ((items = sscanf(line, "swi %d %d %s %d", &number, &position, gpionetname, &bitfield)) == 4) {
                        switchInfo[number].position = position;
                        switchInfo[number].bit      = bitfield;
                        switchInfo[number].netName  = strdup(gpionetname);
                        if(object->diag)
                            opMessage("I", MODULE_NAME "_LP", "swi %d at %d (net %s, bit %d)",
                                    number,
                                    position,
                                    gpionetname,
                                    bitfield);

                        if(strncmp("-", gpionetname, 1))  // defined a GPIO net
                            gpioSwitchUpdateNet(object, gpionetname, number);

                    // Check for definition of a switch
                    } else if ((items = sscanf(line, "swi %d %d %s", &number, &position, gpionetname)) == 3) {
                        switchInfo[number].position = position;
                        switchInfo[number].bit      = -1;
                        switchInfo[number].netName  = strdup(gpionetname);
                        if(object->diag)
                            opMessage("I", MODULE_NAME "_LP", "swi %d at %d (net %s)",
                                    number,
                                    position,
                                    gpionetname);

                        if(strncmp("-", gpionetname, 1))  // defined a GPIO net
                            gpioSwitchUpdateNet(object, gpionetname, number);

                    } else {
                        opMessage("E", MODULE_NAME "_FTP", "Failed to parse line '%s'", line);
                    }
                }
            }
        }
    }

// DEBUG
    if(object->diag) {
        Uns32 i;
        for (i=0;i<ledNumber;i++) {
            if (ledInfo[i].bit != -1 )
                opMessage("I", MODULE_NAME "_LED", "led%d %d %s (bit %d)",
                        i,
                        ledInfo[i].position,
                        ledInfo[i].netName,
                        ledInfo[i].bit);
            else
                opMessage("I", MODULE_NAME "_LED", "led%d %d %s",
                        i,
                        ledInfo[i].position,
                        ledInfo[i].netName);
        }
        for (i=0;i<switchNumber;i++) {
            if (switchInfo[i].bit != -1)
                opMessage("I", MODULE_NAME "_SWI", "sw%d %d %s (bit %d)",
                        i,
                        switchInfo[i].position,
                        switchInfo[i].netName,
                        switchInfo[i].bit != -1 ? switchInfo[i].bit : 0);
            else
                opMessage("I", MODULE_NAME "_SWI", "sw%d %d %s",
                        i,
                        switchInfo[i].position,
                        switchInfo[i].netName);
        }
    }


}

