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

#define PREFIX              "PIIX4"

static void pciInit(void)
{
    /* setup PCI configuration registers */
    pciConfig.vendorID         = 0x8086;
    pciConfig.deviceID         = 0x7110;

    pciConfig.command          = 0x0007;
    pciConfig.status           = 0x0200;

    pciConfig.revisionID       = 0x00;
    pciConfig.classCode[0]     = 0x00;
    pciConfig.classCode[1]     = 0x01;
    pciConfig.classCode[2]     = 0x06;

    pciConfig.headerType       = 0x80;

    pciConfig.user.bytes[0x20] = 0x0a;
    pciConfig.user.bytes[0x21] = 0x0a;
    pciConfig.user.bytes[0x22] = 0x0b;
    pciConfig.user.bytes[0x23] = 0x0b;

    pciConfig.user.bytes[0x28] = 0x00;
    pciConfig.user.bytes[0x29] = 0x02;
    pciConfig.user.bytes[0x2a] = 0x00;
    pciConfig.user.bytes[0x2b] = 0x00;

    pciConfig.user.bytes[0x32] = 0x02; /* SMRAM */
    pciInstallUserWritable(0x40, 4, NULL, NULL);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    pciInit();
    pciConnectConfigSlavePort(PREFIX, NULL);
    pciInstallUserWritable(0x68, 4, NULL, NULL);
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

