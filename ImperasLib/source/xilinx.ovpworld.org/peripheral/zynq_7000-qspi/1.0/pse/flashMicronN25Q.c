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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Tue Oct 14 00:49:54 2014
//
////////////////////////////////////////////////////////////////////////////////

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pse.igen.h"

#include "flash.h"

#define LCLPREFIX PREFIX"_MICRON_N25Q"

// Commands
// Micron N25Q128A
// https://www.micron.com/parts/nor-flash/serial-nor-flash/n25q128a11esf40g

//RESET Operations
#define CMD_RESET_ENABLE                            0x66
#define CMD_RESET_MEMORY                            0x99
// IDENTIFICATION Operations
#define CMD_READ_ID_1                               0x9E
#define CMD_READ_ID_2                               0x9F
#define CMD_MULTIPLE_IO_READ_ID                     0xAF
#define CMD_READ_SERIAL_FLASH_DISCOVERY_PARAMETER   0x5A
//READ Operations
#define CMD_READ                                    0x03
#define CMD_FAST_READ                               0x0B
#define CMD_DUAL_OUTPUT_FAST_READ                   0x3B
#define CMD_DUAL_IO_FAST_READ                       0xBB
#define CMD_QUAD_OUTPUT_FAST_READ                   0x6B
#define CMD_QUAD_IO_FAST_READ                       0xEB
// WRITE Operations
#define CMD_WRITE_ENABLE                            0x06
#define CMD_WRITE_DISABLE                           0x04
// REGISTER Operations
#define CMD_READ_STATUS                             0x05
#define CMD_WRITE_STATUS                            0x01
#define CMD_READ_LOCK                               0xE8
#define CMD_WRITE_LOCK                              0xE5
#define CMD_READ_FLAG_STATUS                        0x70
#define CMD_CLEAR_FLAG_STATUS                       0x50
#define CMD_READ_NONVOLATILE_CONFIGURATION          0xB5
#define CMD_WRITE_NONVOLATILE_CONFIGURATION         0xB1
#define CMD_READ_VOLATILE_CONFIGURATION             0x85
#define CMD_WRITE_VOLATILE_CONFIGURATION            0x81
#define CMD_READ_ENHANCED_VOLATILE_CONFIGURATION    0x65
#define CMD_WRITE_ENHANCED_VOLATILE_CONFIGURATION   0x61
// PROGRAM Operations
#define CMD_PAGE_PROGRAM                            0x02
#define CMD_DUAL_INPUT_FAST_PROGRAM                 0xA2
#define CMD_EXTENDED_DUAL_INPUT_FAST_PROGRAM        0xD2
#define CMD_QUAD_INPUT_FAST_PROGRAM                 0x32
#define CMD_EXTENDED_QUAD_INPUT_FAST_PROGRAM        0x12
// ERASE Operations
#define CMD_SUBSECTOR_ERASE                         0x20
#define CMD_SECTOR_ERASE                            0xD8
#define CMD_BULK_ERASE                              0xC7
#define CMD_PROGRAM_ERASE_RESUME                    0x7A
#define CMD_PROGRAM_ERASE_SUSPEND                   0x75
// ONE-TIME PROGRAMMABLE (OTP) Operations
#define CMD_READ_OTP_ARRAY                          0x4B
#define CMD_PROGRAM_OTP_ARRAY                       0x42
// Deep Power-Down
#define CMD_DPD                                     0xB9
#define CMD_RDPD                                    0xAB


// 0x20 = Micron
#define READ_ID_MANUFACTURER                  0x20
// 0x18 = 128-MBit
#define READ_ID_DEVICE_MEMORY_TYPE            0x17
#define READ_ID_DEVICE_MEMORY_CAPACITY        0x18

// Read Device Identifier Data CMD_READ_ID (REMS)
static Uns8 deviceIdData[] = {
/*00h*/ 0x20, 0xbb, 0x18, 0x10, // Manufacturer, Device Id (128MB), UID
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
};


typedef enum flashStateE {
    state_IDLE = 0,         // Initial state
    state_READ_ARRAY,
    state_DELAY_READ_ARRAY,
    state_WRITE_ENABLE,
    state_PROGRAM,
    state_PAGE_PROGRAM,
    state_SECTOR_ERASE,
    state_BULK_ERASE,
    state_LOCK,
    state_READ_ID,
    state_PROTECT,
    state_CONFIG
} flashStateT;

#define STATE_ENUM_STRING(_N)  [state_##_N] = #_N
static const char *flashStateNames[] = {
    STATE_ENUM_STRING(IDLE),
    STATE_ENUM_STRING(READ_ARRAY),
    STATE_ENUM_STRING(DELAY_READ_ARRAY),
    STATE_ENUM_STRING(WRITE_ENABLE),
    STATE_ENUM_STRING(PROGRAM),
    STATE_ENUM_STRING(PAGE_PROGRAM),
    STATE_ENUM_STRING(SECTOR_ERASE),
    STATE_ENUM_STRING(BULK_ERASE),
    STATE_ENUM_STRING(LOCK),
    STATE_ENUM_STRING(PROTECT),
    STATE_ENUM_STRING(CONFIG)
};

typedef union flashStatusU {
    struct {
        Uns32   WIP:    1;   // Write in Progress
        Uns32   WEL:    1;   // Write Enable Latch
        Uns32   BP:     4;   // Block Protect
        Uns32   TB:     1;   // Top/Bottom
        Uns32   SRWREN: 1;   // Status Register Write Enable
    } flags;
    Uns32 value;
} flashStatusT;
//static const flashStatusT sequenceError = { .flags = {.ES=1, .PS=1} };
//static const flashStatusT clearStatus   = { .value = 0 };
typedef union flashFlagStatusU {
    struct {
        Uns32   WIP:     1;   //
        Uns32   PROT:    1;   //
        Uns32   PS:      1;   //
        Uns32   VPP:     1;   //
        Uns32   PROGRAM: 1;   //
        Uns32   ERASE:   1;   //
        Uns32   ESP:     1;   //
        Uns32   BSY:     1;   //
    } flags;
    Uns32 value;
} flashFlagStatusT;

// Current Command state
static flashStateT currentState = state_IDLE;

// Current Status register (initialize DWS=1 to indicate ready)
static flashStatusT currentStatus = { .value = 0 };

//
// Called to create the Flash model state.
//
void flashMicronN25QInit() {

    if(PSE_DIAG_HIGH)
        bhmMessage("I", LCLPREFIX"_INI", "Initialize");

    char imageFileString[BHM_MAX_PATH];

    // Initialize flash memory to all 1's
    initFlashMemory();

    // Load image file(s), if specified
    if (bhmStringParamValue("image", (char *)imageFileString, sizeof(imageFileString))) {
        processImageFiles(imageFileString, True);
    } else {
        if (PSE_DIAG_LOW) {
            bhmMessage(
                "W", LCLPREFIX "_NFI",
                "No image file(s) specified for initializing flash memory"
            );
        }
    }

}

//
// Called when flash memory is disabled (chip select removed)
//
Uns32 flashAddress;
void flashMicronN25QDisable() {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", LCLPREFIX"_DIS", "Disable");

    currentState = state_IDLE;
}



//
// Called when an access is made to the flash memory
//
Uns32 flashMicronN25QAccess(Uns32 commandOrData, Uns32 size) {

    Bool         programData    = False;
    flashStateT  thisState      = currentState;
    flashStateT  nextState      = currentState;
    static Uns32 readValue      = 0;
    const char  *readType       = "read";
    static Uns32 readDelay      = 0;    // how many bytes are delayed on initial read data
    static Uns32 deviceIdOffset = 0;    // index into deviceId array while in state_READ_ID


    if(PSE_DIAG_HIGH)
        bhmMessage(
        "I", LCLPREFIX"_FS",
        "Flash State : %s",
        flashStateNames[thisState]);

    if ((thisState == state_IDLE) ||
        (thisState == state_WRITE_ENABLE)){
        // Valid states to accept commands

        deviceIdOffset = 0; // reset

        // Write data is a command
        Uns8   cmd = GET_CMD(commandOrData);
        Uns32 addr = GET_ADDR24(commandOrData);

        if(PSE_DIAG_HIGH) {
            bhmMessage("I", LCLPREFIX"_CMD","Command:0x%x addr=0x%03x size:%d", cmd, addr, size);
        }

        switch (cmd) {
        case CMD_WRITE_ENABLE:
            currentStatus.flags.WEL = 1;
            nextState = state_WRITE_ENABLE;
            break;
        case CMD_WRITE_DISABLE:
            currentStatus.flags.WEL = 0;
            nextState = state_IDLE;
            break;
        case CMD_DUAL_IO_FAST_READ:
        case CMD_QUAD_IO_FAST_READ:
        case CMD_FAST_READ:
        case CMD_DUAL_OUTPUT_FAST_READ:
        case CMD_QUAD_OUTPUT_FAST_READ:
            // TODO: The actual number of bytes delayed is dependent upon the
            //       Volatile Configuration Register Bit Definitions field 7:4
            readDelay = 1;
            flashAddress = addr;
            nextState = state_DELAY_READ_ARRAY;
            break;
        case CMD_READ:
            readDelay = 0;
            flashAddress = addr;
            nextState = state_DELAY_READ_ARRAY;
            break;
        case CMD_READ_STATUS:
            readValue = currentStatus.value;
            readType = "read status";
            break;
        case CMD_READ_ID_1:
        case CMD_READ_ID_2:
            readDelay = 1;
            nextState = state_READ_ID;
            readType = "read id";
            break;
        case CMD_MULTIPLE_IO_READ_ID:
            // Return Device Identifier Info
            // The Manufacturer Id and Device Memory Info (2 byte access)
            readDelay = 1;
            readArray(((Uns8 *)&readValue)+(4-size-readDelay), (Uns8 *)&deviceIdData[1], size-readDelay);
            readType = "read id";
            break;
        case CMD_SECTOR_ERASE:
            if(PSE_DIAG_MEDIUM)
                bhmMessage(
                "I", LCLPREFIX"_SE",
                "Sector Erase 0x%08x", addr);
            eraseBlock(addr, False);
            break;
        case CMD_SUBSECTOR_ERASE:
            if(PSE_DIAG_MEDIUM)
                bhmMessage(
                "I", LCLPREFIX"_SE",
                "Sub-Sector Erase 0x%08x", addr);
            eraseBlock(addr, True);
            break;
        case CMD_PAGE_PROGRAM:
        case CMD_DUAL_INPUT_FAST_PROGRAM:
        case CMD_EXTENDED_DUAL_INPUT_FAST_PROGRAM:
        case CMD_QUAD_INPUT_FAST_PROGRAM:
        case CMD_EXTENDED_QUAD_INPUT_FAST_PROGRAM:
            if(currentStatus.flags.WEL) {
                flashAddress = addr;
                nextState = state_PAGE_PROGRAM;
// TODO: Check this is needed in the model i.e. write is immediate
//                    currentStatus.flags.WIP = 1;
                if(PSE_DIAG_MEDIUM)
                    bhmMessage(
                    "I", LCLPREFIX"_PP",
                    "Page Program 0x%08x", addr);
            } else {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage(
                    "W", LCLPREFIX"_PPD",
                    "Page Program 0x%08x when write disabled", addr);
            }
            break;
            //RESET Operations
        case CMD_RESET_ENABLE:
        case CMD_RESET_MEMORY:
            // IDENTIFICATION Operations
        case CMD_READ_SERIAL_FLASH_DISCOVERY_PARAMETER:
            // REGISTER Operations
        case CMD_WRITE_STATUS:
        case CMD_READ_LOCK:
        case CMD_WRITE_LOCK:
        case CMD_READ_FLAG_STATUS:
        case CMD_CLEAR_FLAG_STATUS:
        case CMD_READ_NONVOLATILE_CONFIGURATION:
        case CMD_WRITE_NONVOLATILE_CONFIGURATION:
        case CMD_READ_VOLATILE_CONFIGURATION:
        case CMD_WRITE_VOLATILE_CONFIGURATION:
        case CMD_READ_ENHANCED_VOLATILE_CONFIGURATION:
        case CMD_WRITE_ENHANCED_VOLATILE_CONFIGURATION:
            // ERASE Operations
        case CMD_BULK_ERASE:
        case CMD_PROGRAM_ERASE_RESUME:
        case CMD_PROGRAM_ERASE_SUSPEND:
            // ONE-TIME PROGRAMMABLE (OTP) Operations
        case CMD_READ_OTP_ARRAY:
        case CMD_PROGRAM_OTP_ARRAY:
            // Deep Power-Down
        case CMD_DPD:
        case CMD_RDPD:
            bhmMessage(
                "W", LCLPREFIX"_NIMP",
                "flash command 0x%x not implemented",
                cmd
            );
            break;

        default:
            bhmMessage(
                "W", LCLPREFIX"_UFC",
                "Unrecognized flash command 0x%x in state %s",
                cmd,
                flashStateNames[thisState]
            );
            break;
        }
    } else if ((thisState == state_PROGRAM) ||
               (thisState == state_PAGE_PROGRAM)){

        // Program the data
        programData = True;

    } else if (thisState == state_DELAY_READ_ARRAY) {
        nextState = state_READ_ARRAY;
    }



    if (PSE_DIAG_MEDIUM) {
        if (thisState != nextState) {
            bhmMessage(
                "I", LCLPREFIX"_FSC",
                "Flash State changed: %s->%s",
                flashStateNames[thisState],
                flashStateNames[nextState]
            );
        }
    }

    // TODO: this is not how this flash model works
    //       we need to write the data as it is presented to the FLASH
    if (programData) {
        // do a program of the flash memory array
        programArray(FLASH+flashAddress, (Uns8 *)&commandOrData, size);
        flashAddress += size;
    }

    currentState = nextState;

    if (currentState == state_READ_ARRAY) {

        // do a read from the flash memory
        // delayed data offsets
        readArray(((Uns8 *)&readValue)+readDelay, FLASH+flashAddress, size-readDelay);

        if (PSE_DIAG_MEDIUM) {
            printData(flashAddress, &readValue, size, readType);
        }
        flashAddress += (size-readDelay);
        readDelay=0;

    } else if (currentState == state_READ_ID) {

        // Return CFI Query Structure Info
        Uns32 deviceIdInfo = 0;

        if (deviceIdOffset < sizeof(deviceIdData)) {

            // The Manufacturer Id and Device Memory Info
            readArray(((Uns8 *)&deviceIdInfo)+readDelay, (Uns8 *)&deviceIdData[deviceIdOffset], size-readDelay);

            if(PSE_DIAG_HIGH)
                bhmMessage(
                "I", LCLPREFIX"_DID",
                "0x%x (0x%x)", deviceIdInfo, deviceIdData[deviceIdOffset]);

        } else {
            if(PSE_DIAG_HIGH)
                bhmMessage(
                "I", LCLPREFIX"_DID_OV", "Device ID Index Overflowed");
        }
        deviceIdOffset+=size-readDelay;    // move to next element

        readDelay = 0;
        readValue = deviceIdInfo;
        readType  = "read id";
    }

    return readValue;
}

// defined in qpsi.user.c
extern char *imageFileP;
void flashMicronN25QFinish() {

    if(PSE_DIAG_HIGH)
        bhmMessage("I", LCLPREFIX"_FIN", "Finish");

    // write image back out if specified
    if (imageFileP) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", LCLPREFIX"_WIM", "Write Flash Image Output to %s", imageFileP);

        processImageFiles(imageFileP, False);
    }
}
