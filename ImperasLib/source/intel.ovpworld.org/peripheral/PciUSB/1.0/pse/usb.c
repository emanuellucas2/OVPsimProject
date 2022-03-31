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

#include <string.h>

#include "pse.igen.h"

#include "pci.h"

#define PREFIX "PCI_USB"

/////////////////// PCI main IO bus window ///////////////////

#define PCI_IO_WINDOW_SIZE 14

Uns8 pciBusWindow[PCI_IO_WINDOW_SIZE];

static PPM_WRITE_CB(ioRegWrite) {
    bhmMessage("I", PREFIX, "ioRegWrite");
}

static PPM_READ_CB(ioRegRead) {
    bhmMessage("I", PREFIX, "ioRegRead");
    return 0;
}

static void pciInit(void)
{
    /* setup PCI configuration registers */
    pciConfig.vendorID       = 0x8086;
    pciConfig.deviceID       = 0x7112;
    pciConfig.revisionID     = 0x01;
    pciConfig.classCode[0]   = 0x00;
    pciConfig.classCode[1]   = 0x03;
    pciConfig.classCode[2]   = 0x0C;
    pciConfig.interruptPin   = 0x04;
    pciConfig.user.bytes[20] = 0x10;
    pciConfig.baseAddress[4] = 0x00000001;

    pciInstallRegion(0x20, 0xffffffe1, pciBusWindow, NULL, PCI_IO_WINDOW_SIZE);
    ppmInstallWriteCallback(ioRegWrite, 0, pciBusWindow, PCI_IO_WINDOW_SIZE);
    ppmInstallReadCallback (ioRegRead,  0, pciBusWindow, PCI_IO_WINDOW_SIZE);
}



PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    pciInit();
    pciConnectConfigSlavePort(PREFIX, NULL);
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Starting.");
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

