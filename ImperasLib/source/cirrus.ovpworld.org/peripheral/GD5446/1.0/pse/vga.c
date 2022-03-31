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

#include "string.h"

#include "pse.igen.h"

#include "pci.h"

#include "cirrus_constants.h"

#define PREFIX "VGA"

//
// Changing these requires changes to model.xml
//
#define RAM_PORT_NAME         "memory"
#define ISA_PORT_NAME         "config"
#define SCAN_DELAY_ATTRIBUTE  "scanDelay"

// opaque handles that can hold native pointers on both 32-bit and 64-bit hosts
typedef Uns64 vgaStateHandle;
typedef Uns64 displayStateHandle;

static displayStateHandle ds;
static vgaStateHandle     vs;

// statistics
static Uns32 updates     = 0;
static Uns32 ISAwrites   = 0;
static Uns32 ISAreads    = 0;

//
///////////////////// Intercepted by vga SHL ///////////////////////
//

FUNCTOHOST(displayStateHandle, displayInit, char * title)

FUNCTOHOST(vgaStateHandle, cirrusInit, Uns32 size, const char *portName, Uns32 id)

FUNCTOHOST(void, vgaDisplay, vgaStateHandle vga, displayStateHandle ds)

FUNCTOHOST(void, mapDisplay, vgaStateHandle vga, Uns32 base)

FUNCTOHOST(Uns32, ioportRead, vgaStateHandle vgaState, Uns32 address, Uns32 diag)

FUNCTOHOST(void, ioportWrite, vgaStateHandle vgaState, Uns32 address, Uns32 bytes, Uns32 diag)

static void setupDisplay(Uns32 base, Uns32 size, Bool install, void *user)
{
    if (!install) {
        bhmMessage("F", PREFIX, "model does not support unmapping");
    }
    // TODO : explain why a PCI VGA falls outside the PCI memory mapped region!!
    mapDisplay(vs, base & 0x10000000);
}

static void mapGPIO(Uns32 base, Uns32 size, Bool install, void *user)
{
    if (!install) {
        bhmMessage("F", PREFIX, "model does not support unmapping");
    }
    bhmMessage("I", PREFIX, "Writing PCI config GPIO Base 0x%x - this is unsupported.", base);
}

static void pciInit(void)
{
    pciConfig.vendorID       = PCI_VENDOR_CIRRUS;
    pciConfig.deviceID       = CIRRUS_ID_CLGD5446;
    pciConfig.command        = 0; //PCI_COMMAND_IOACCESS | PCI_COMMAND_MEMACCESS;
    pciConfig.classCode[1]   = PCI_CLASS_SUB_VGA;
    pciConfig.classCode[2]   = PCI_CLASS_BASE_DISPLAY;
    pciConfig.headerType     = PCI_CLASS_HEADERTYPE_00h;
    pciConfig.baseAddress[0] = 0x08;
    pciConnectConfigSlavePort(PREFIX, NULL);
    pciInstallRegion(0x10, 0xfe000008, 0,  setupDisplay,  VGA_RAM_SIZE);
    pciInstallRegion(0x14, 0xfffff000, 0,  mapGPIO, 0x1000);
}

//
// ISA configuration registers
//
static unsigned char ISAconfigWindow [0x30];

static PPM_READ_CB(ISAconfigRead) {
    Uns32 off  = (unsigned char*)addr - &ISAconfigWindow[0x0] + 0x3b0;
    ISAreads++;
    Uns16 res;
    switch(bytes) {
        case 1: {
            res = ioportRead(vs, off, diagnosticLevel);
            break;
        }
        case 2: {
            Uns8 lo = ioportRead(vs, off, diagnosticLevel);
            Uns8 hi = ioportRead(vs, off+1, diagnosticLevel);
            res = lo | (hi<<8);
            break;
        }
        default:
            bhmMessage("E", PREFIX, "Attempting %u byte read", bytes);
            return 0;
    }
    return res;
}

static PPM_WRITE_CB(ISAconfigWrite) {
    Uns32 off  = (unsigned char*)addr - &ISAconfigWindow[0x0] + 0x3b0;

    ISAwrites++;
    switch(bytes) {
        case 1:
            ioportWrite(vs, off, data, diagnosticLevel);
            break;
        case 2:
            ioportWrite(vs, off,   data&0xff, diagnosticLevel);
            ioportWrite(vs, off+1, data>>8,   diagnosticLevel);
            break;
         default:
            bhmMessage("E", PREFIX, "Attempting %u byte write", bytes);
    }
}

static void updateDisplay(void)
{
    vgaDisplay(vs, ds);
}

//
// Connect bus ports
//
static void ISAconfigConnection(const char *portName)
{
    // TODO : this should be set up by the PCI I/O config base register
    // but it doesn't make sense to me.
    if( ppmOpenSlaveBusPort(
        portName,
        ISAconfigWindow,
        sizeof(ISAconfigWindow)
    )) {
        ppmInstallReadCallback(
            ISAconfigRead,
            0,
            &ISAconfigWindow[0x0],
            sizeof(ISAconfigWindow)
        );
        ppmInstallWriteCallback(
            ISAconfigWrite,
            0,
            &ISAconfigWindow[0x0],
            sizeof(ISAconfigWindow)
        );
        if(PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX,
                "Connected ISA configuration port '%s'",
                portName
            );
        }
    } else {
        bhmMessage("F", "Failed to connect to '%s'", portName);
    }
}

FUNCTOHOST(Uns32, ImperasTestModeTimeout, double * timeout)

double ImperasTestTimeout = 0.0;
//
// thread waits for a specified time and finishes simulation
//
static void ImperasTestModeTimeoutThread(void *user) {
    bhmWaitDelay(ImperasTestTimeout*1000000); // timeout in seconds
    bhmFinish();
}

static Uns32 delay;

//
// This thread polls for input
//
static void pollingTask()
{
    while(1) {
    // wait for poll period
        bhmWaitDelay(delay);
        updateDisplay();
        updates++;
    }
}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();


    if(ImperasTestModeTimeout(&ImperasTestTimeout)) {
        bhmCreateThread(ImperasTestModeTimeoutThread, 0, "ImperasTestModeTimeoutThread", 0);
    }

    ISAconfigConnection(ISA_PORT_NAME);

    char title[32];
    char* titleP = 0;
    if (bhmStringParamValue("title", title, sizeof(title))) {
        titleP = title;
    }

    ds = displayInit(titleP);
    vs = cirrusInit( VGA_RAM_SIZE, RAM_PORT_NAME, CIRRUS_ID_CLGD5446);
    vgaDisplay(vs, ds);

    bhmUns32ParamValue(SCAN_DELAY_ATTRIBUTE, &delay);
    if(delay==0) {
        bhmMessage("E", PREFIX, SCAN_DELAY_ATTRIBUTE " must be non-zero");
    }

    pciInit();

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Starting. Diagnostic level:%d. Scan delay:%d", diagnosticLevel, delay);
    }

    // start polling thread
    bhmCreateThread(pollingTask, NULL, "pollingTask", 0);

}

PPM_DESTRUCTOR_CB(destructor) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Statistics:");
        bhmPrintf("Screen updates :    %d\n", updates);
        bhmPrintf("ISA reads      :    %d\n", ISAreads);
        bhmPrintf("ISA writes     :    %d\n", ISAwrites);
    }
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
