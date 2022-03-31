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

#define PREFIX  "PCI_PM"

#define PCI_IO_WINDOW_SIZE 8
Uns8 pciBusWindow[PCI_IO_WINDOW_SIZE];

#define SUS_EN (1 << 13)

static PPM_WRITE_CB(ioRegWrite) {
    bhmMessage("I", PREFIX, "ioRegWrite");

    Uns32 offset = (addr - (void*)&pciBusWindow[0]) & 0x3f;
    Uns32 val    = data;

    switch(offset) {
    case 0x00:
        break;
    case 0x02:
        break;
    case 0x04:
        {
            int sus_typ;
            if (val & SUS_EN) {
                /* change suspend type */
                sus_typ = (val >> 10) & 3;
                switch(sus_typ) {
                case 0: /* soft power off */
                    bhmMessage("I", PREFIX, "Soft Power Off: Simulation will finish");
                    bhmFinish();
                    break;
                default:
                    break;
                }
            }
        }
        break;
    default:
        break;
    }

}

static PPM_READ_CB(ioRegRead){
    bhmMessage("I", PREFIX, "ioRegRead");
    return 0;
}

static void pciInit(void)
{
    /* setup PCI configuration registers */
    Uns32 io_base = 0x1100;

    pciConfig.vendorID       = 0x8086;
    pciConfig.deviceID       = 0x7113;
    pciConfig.command        = 0x0000;
    pciConfig.status         = 0x0280;

    pciConfig.revisionID     = 0x00;
    pciConfig.classCode[0]   = 0x00;
    pciConfig.classCode[1]   = 0x00;
    pciConfig.classCode[2]   = 0x02;

    pciConfig.headerType     = 0x00;

    pciConfig.interruptPin   = 1;       // interrupt pin 0
    pciConfig.headerType     = 0x00;
    pciConfig.classCode[1]   = 0x80;
    pciConfig.classCode[2]   = 0x06;

    pciConfig.user.bytes[0] = 0x01;  // PM io base read only bit

   /* The i82731AB has different mappings */

    pciConfig.user.bytes[0x1f] = 0x90;
    pciConfig.user.bytes[0x23] = 0x60;
    pciConfig.user.bytes[0x27] = 0x08;

    pciConfig.user.bytes[0x50] = io_base | 1;
    pciConfig.user.bytes[0x51] = io_base >> 8;
    pciConfig.user.bytes[0x90] = 0x09;

    ppmInstallWriteCallback(ioRegWrite, 0, pciBusWindow, PCI_IO_WINDOW_SIZE);
    ppmInstallReadCallback (ioRegRead,  0, pciBusWindow, PCI_IO_WINDOW_SIZE);

    pciInstallRegion(0x80, 0xffffffc0, pciBusWindow, NULL, PCI_IO_WINDOW_SIZE);
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
