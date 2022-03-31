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

#define PREFIX           "FlashDevice"

//
// Changing these requires changes to model.xml
//
#define FLASH_PORT_NAME  "flash"

static Uns32             diagLevel = 0;

FUNCTOHOST(void, flashInit, const char *portName, const char *fileName, const char *endian)

FUNCTOHOST(void, flashSetDiag, Uns32 diag)

//
// Set the local diag level
//
static void setDiagLevel(Uns32 d)
{
    diagLevel = d & 0x0f;
    flashSetDiag((d & 0xf0)>>4);

}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    const char initFile[BHM_MAX_PATH];
    const char *initFileP= NULL;
    const char endian[16] = "little";

    bhmInstallDiagCB(setDiagLevel);

    if (bhmStringParamValue("init", (char *)initFile, sizeof(initFile))) {
        initFileP = initFile;
    }

    bhmStringParamValue("endian", (char *)endian, sizeof(endian));

    flashInit(FLASH_PORT_NAME, initFileP, endian);

    // now sit and wait for things to happen
    if(BHM_DIAG_LOW) bhmMessage("I", PREFIX, "main done");

}


PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

