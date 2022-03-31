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

// These must match definition in pse.tcl
#ifndef FLASH_PORT_NAME
#define FLASH_PORT_NAME "flash"
#endif
#ifndef FLASH_SIZE
#define FLASH_SIZE 0x04000000
#endif

// Pointer to simulator allocated flash memory space
#define FLASH ((Uns8 *)handles.flash)

// Must keep backup copy of flash memory. Used to
// preserve memory when flash commands are written,
// (which do not change the flash memory values),
// since simulator updates the memory before we are called
static Uns8 backingStore[FLASH_SIZE];

//
// Device access macros for modeling 2x16 data bit chips implementing 32 data bits
// Note: cannot model with 16 data bit single chips because a peripheral
//       model may not connect to just the high/low 16 bits of bus.
//

// Each command is sent simultaneously to both chips,
// i.e. at the lower 16 bits AND at the higher 16 bits
#define CMD_MASK                0xffff
#define LOW_CMD(_V)             ((_V) & CMD_MASK)
#define HIGH_CMD(_V)            (LOW_CMD((_V >> 16)))
#define CMDS_MATCH(_V)          (LOW_CMD(_V) == HIGH_CMD(_V))
#define DUAL_VALUE(_V)          (((_V) << 16) | ((_V) & 0xffff))

// Blocks are organized as 256KB Main blocks (128KB per chip in the 2x16 configuration)
// The last main block is implemented as 4x64KB parameter blocks
#define MAIN_BLOCK_SIZE         0x00040000
#define MAIN_BLOCK_MASK         (~(MAIN_BLOCK_SIZE-1))
#define PARAM_BLOCK_SIZE        0x00010000
#define PARAM_BLOCK_MASK        (~(PARAM_BLOCK_SIZE-1))

// Macros to calculate first/last main/param block offsets
// Only "Top Configuration" supported, where last main block is used as parameter blocks
#define FIRST_MAIN_BLOCK(_S)    (0)
#define FIRST_PARAM_BLOCK(_S)   (((_S)-1) & MAIN_BLOCK_MASK)
#define LAST_MAIN_BLOCK(_S)     ((FIRST_PARAM_BLOCK(_S)-1) & MAIN_BLOCK_MASK)
#define LAST_PARAM_BLOCK(_S)    (((_S)-1) & PARAM_BLOCK_MASK)

// READ Commands
#define CMD_READ_DEVICE_ID                    0x0090
#define CMD_READ_STATUS_REGISTER              0x0070
#define CMD_CLEAR_STATUS_REGISTER             0x0050
#define CMD_READ_ARRAY                        0x00FF
#define CMD_READ_CFI_QUERY                    0x0098

// WRITE Commands
// Note buffered writes are simply written as they are received
#define CMD_WORD_PROGRAM_SETUP                0x0040
#define CMD_ALTERNATE_WORD_PROGRAM_SETUP      0x0010
#define CMD_BUFFERED_PROGRAM_SETUP            0x00E8
#define CMD_BUFFERED_PROGRAM_CONFIRM          0x00D0
#define CMD_BEFP_SETUP                        0x0080
#define CMD_BEFP_CONFIRM                      0x00D0

// ERASE Commands
#define CMD_BLOCK_ERASE_SETUP                 0x0020
#define CMD_BLOCK_ERASE_CONFIRM               0x00D0

// SUSPEND Commands
#define CMD_PROGRAM_OR_ERASE_SUSPEND          0x00B0
#define CMD_SUSPEND_RESUME                    0x00D0

// BLOCK LOCKING / UNLOCKING Commands
#define CMD_LOCK_BLOCK_SETUP                  0x0060
#define CMD_LOCK_BLOCK                        0x0001
#define CMD_UNLOCK_BLOCK                      0x00D0
#define CMD_LOCK_DOWN_BLOCK                   0x002F

// PROTECTION Commands
#define CMD_PROGRAM_PROTECTION_REGISTER_SETUP 0x00C0

// CONFIGURATION Commands
#define CMD_READ_CONFIGURATION_REGISTER_SETUP 0x0060
#define CMD_READ_CONFIGURATION_REGISTER       0x0003

// Read Device Identifier Data
// 0x0089 = Intel
#define READ_ID_MANUFACTURER                  0x0089
// 0x8919 = 256-MBit, Top Parameter
// TODO: Adjust this based on size of chips: 64/128/256 MBit
#define READ_ID_CODE                          0x8919
// Only default values for the Read Configuration Register are supported
#define READ_ID_RCR                           0xbfcf

// Read Device Identifier Data offsets
// NOTE: These are << 2 from the data sheet due to the 2x16 configuration
#define READ_ID_OFFSET_MANUFACTURER           0x00
#define READ_ID_OFFSET_CODE                   0x04
#define READ_ID_OFFSET_LOCK_CONFIG            0x08
#define READ_ID_OFFSET_RCR                    0x14

typedef enum flashStateE {
    state_READ_ARRAY = 0, // Initial state
    state_READ_ID,
    state_READ_CFI,
    state_READ_STATUS,
    state_PROGRAM,
    state_PROGRAM_BUFFERED_COUNT,
    state_PROGRAM_BUFFERED,
    state_PROGRAM_BUFFERED_DONE,
    state_ERASE,
    state_LOCK,
    state_PROTECT,
    state_CONFIG
} flashStateT;

#define STATE_ENUM_STRING(_N)  [state_##_N] = #_N
static const char *flashStateNames[] = {
    STATE_ENUM_STRING(READ_ARRAY),
    STATE_ENUM_STRING(READ_ID),
    STATE_ENUM_STRING(READ_CFI),
    STATE_ENUM_STRING(READ_STATUS),
    STATE_ENUM_STRING(PROGRAM),
    STATE_ENUM_STRING(PROGRAM_BUFFERED_COUNT),
    STATE_ENUM_STRING(PROGRAM_BUFFERED),
    STATE_ENUM_STRING(PROGRAM_BUFFERED_DONE),
    STATE_ENUM_STRING(ERASE),
    STATE_ENUM_STRING(LOCK),
    STATE_ENUM_STRING(PROTECT),
    STATE_ENUM_STRING(CONFIG)
};

typedef union flashStatusU {
    struct {
        Uns32   BWS: 1;   // BEFP Status (0=complete, 1=in progress)
        Uns32   BLS: 1;   // Block-lock Status (0=not locked, 1=locked, op aborted)
        Uns32   PSS: 1;   // Suspend Status (0=not in effect, 1=in effect)
        Uns32   VPPS:1;   // VPP Status (0=in range, 1=out of range)
        Uns32   PS:  1;   // Program Status (0=successful, 1=fail or sequence error)
        Uns32   ES:  1;   // Erase Status (0=successful, 1=fail or sequence error)
        Uns32   ESS: 1;   // Erase suspend Status (0=not in effect, 1=in effect)
        Uns32   DWS: 1;   // Device Write Status (0=Busy, 1=Ready)
    } flags;
    Uns32 value;
} flashStatusT;
static const flashStatusT sequenceError = { .flags = {.ES=1, .PS=1} };
static const flashStatusT clearStatus   = { .flags = {.DWS=1} };

//
// CFI Query Data
// (See section C.4 in Intel StrataFlash Embedded Memory P30 Family Datasheet)
//
static Uns8 cfiQueryData[] = {
/*00h*/ 0x00, 0x00, 0x00, 0x00, // Filler to data start at 0x10
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
/*10h*/ 'Q', 'R', 'Y',          // ID string
        0x01, 0x00,             // Vendor command set ID
        0x0a, 0x01,             // Extended query table primary address
        0x00, 0x00,             // Alternate vendor command set (none)
        0x00, 0x00,             // Secondary Extended Query table primary address (none)
/*1Bh*/ 0x17, 0x20, 0x85, 0x95, // System Interface (from data sheet)
        0x08, 0x09, 0x0a, 0x00,
        0x01, 0x01, 0x02, 0x00,
/*27h*/ 0x00, 0x00, 0x00, 0x00, // Device Geometry (per chip)
        0x00, 0x00, 0x00, 0x00, //  Set in setCFIGeometry() according to FLASH_SIZE
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
};

//
// CFI Extended Query Table Data
// (See section C.5 in Intel StrataFlash Embedded Memory P30 Family Datasheet)
// (p = offset = 0x10a)
//
static Uns8 cfiEQTData[] = {
/*p+00h*/ 'P', 'R', 'I',          // ID string
          '1', '4',               // Major/minor Version number
/*p+05h*/ 0x00, 0x00, 0x00,       // Optional features (none supported)
/*p+08h*/ 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00,
/*p+10h*/ 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00,
/*p+18h*/ 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00
};

// Current Command state
static flashStateT currentState = state_READ_ARRAY;

// Current Status register (initialize DWS=1 to indicate ready)
static flashStatusT currentStatus = { .flags = {.DWS=1} };

// Buffered writes remaining until done
static Uns32 bufferCount = 0;

// Flag indicating whether read callbacks are presently installed
// (only need to be installed while in state where reads return
//  other than value in memory)
static Bool readCallbackInstalled = False;

// Forward reference
static PPM_READ_CB(flashReadCB);

//
// Uninstall read callbacks
//
static void uninstallReadCallback() {

    if (readCallbackInstalled) {

        ppmInstallReadCallback (NULL,  NULL, FLASH, FLASH_SIZE);
        readCallbackInstalled = False;

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX"_RCU",
                "Read Callbacks uninstalled"
            );
        }
    }
}

//
// Install read callbacks
//
static void installReadCallback() {

    if (!readCallbackInstalled) {

        ppmInstallReadCallback (flashReadCB,  NULL, FLASH, FLASH_SIZE);
        readCallbackInstalled = True;

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX"_RCI",
                "Read Callbacks installed"
            );
        }
    }
}

//
// Do read Callbacks need to be installed?
//
static void checkReadCallback(flashStateT state) {
    switch (state) {
    case state_READ_STATUS:
    case state_PROGRAM_BUFFERED_COUNT:
    case state_READ_ID:
    case state_READ_CFI:
        // These are the only states that require the read callback be installed
        installReadCallback();
        break;
    default:
        // All others leave the callbacks unchanged
        break;
    }
}

//
// Issue fatal message if address range is not in the flash memory range
//
static void checkOffset(Uns32 offset, Uns32 bytes) {
    Uns32 high = bytes ? offset+bytes-1 : offset;
    if (high >= FLASH_SIZE) {
        bhmMessage(
            "F", PREFIX"_OOR",
            "Flash offset 0x%x exceeds flash size 0x%x",
            high,
            FLASH_SIZE
        );
        // Not reached
    }
}

//
// Return the block base offset and optionally the block size
// for a Flash memory offset (Offset may be in either
// a main block or a parameter block)
//
static Uns32 getBlockBase(Uns32 offset, Uns32 *size) {

    checkOffset(offset, 0);

    Uns32 base      = offset & MAIN_BLOCK_MASK;
    Uns32 blockSize = MAIN_BLOCK_SIZE;

    if (base == FIRST_PARAM_BLOCK(FLASH_SIZE)) {
        base = offset & PARAM_BLOCK_MASK;
        blockSize = PARAM_BLOCK_SIZE;
    }

    if (size) *size = blockSize;
    return base;

}

//
// Initialize the block of flash memory containing offset to all 1's
//
static void eraseBlock(Uns32 offset) {

    Uns32  blockSize;
    Uns32  blockBase = getBlockBase(offset, &blockSize);
    Uns8  *flash     = FLASH        + blockBase;
    Uns8  *back      = backingStore + blockBase;
    Uns8  *end       = flash        + blockSize;

    // Make sure we do not overflow the flash memory array
    if (end >= (FLASH + FLASH_SIZE)) {
        end = FLASH + FLASH_SIZE;
    }

    while (flash < end) {
        *(flash++) = *(back++) = 0xff;
    }
}

static void printData(
    Uns32        offset,
    const void  *value,
    Uns32        bytes,
    const char  *type
) {
    if (bytes == 4) {
        bhmMessage(
            "I", PREFIX"_FRW",
            "Flash %s: %d bytes at offset 0x%x (block base=0x%x): 0x%x",
            type,
            bytes,
            offset,
            getBlockBase(offset, NULL),
            *(Uns32 *)value
        );
    } else {
        bhmMessage(
            "I", PREFIX"_FRW",
            "Flash %s: %d bytes at 0x%x (block base=0x%x): ",
            type,
            bytes,
            offset,
            getBlockBase(offset, NULL)
        );
        bhmPrintf("\t");
        Uns32 i = 0;
        while (i < bytes) {
            unsigned char byte = *((unsigned char *)(value + i));
            bhmPrintf(" %02x", byte);
            if (((++i % 8) == 0) && (i < bytes)) {
                bhmPrintf("\n\t");
            }
        }
        bhmPrintf("\n");
    }
}

//
// write data to array
//
static void writeArray(Uns8 *to, Uns8 *from, Uns32 bytes) {
    while (bytes--) {
        *(to++) = *(from++);
    }
}

//
// program data into array (programming can only cause 1->0 transitions
//
static void programArray(Uns8 *to, Uns8 *old, Uns32 bytes) {
    while (bytes--) {
        *(to++) &= *(old++);
    }
}

//
// Called on writes to flash memory
//
static PPM_WRITE_CB(flashWriteCB) {

    Bool         writeData     = False;
    Bool         programData   = False;
    flashStateT  thisState     = currentState;
    flashStateT  nextState     = currentState;
    Uns32        offset        = (Uns8 *)addr - FLASH;

    checkOffset(offset, bytes);

    if (artifactAccess) {

        // Allow artifact accesses to write to the flash memory
        writeData = True;

    } else if (bytes != 4) {

        bhmMessage(
            "W", PREFIX"_IWS",
            "FLASH write with invalid size %d ignored. Only 4 byte writes supported",
            bytes
        );

    } else if (thisState == state_PROGRAM) {

        // Program the data
        programData = True;
        nextState   = state_READ_STATUS;

    } else if (thisState == state_PROGRAM_BUFFERED) {

        // Program the data and decrement the count
        programData = True;
        if (bufferCount) {
            bufferCount--;
        } else {
            nextState = state_PROGRAM_BUFFERED_DONE;
        }

    } else {

        if (!CMDS_MATCH(data)) {

            // In 2x16 configuration all commands must match high and low
            bhmMessage(
                "W", PREFIX"_CDM",
                "High and low flash commands do not match: 0x%x. Command ignored.",
                data
            );

        } else {

            // Write data is a command
            Uns16 cmd = LOW_CMD(data);

            switch (thisState) {
            case state_ERASE:
                if (cmd == CMD_BLOCK_ERASE_CONFIRM) {
                    eraseBlock(offset);
                } else {
                    currentStatus.value |= sequenceError.value;
                }
                nextState = state_READ_STATUS;
                break;

            case state_LOCK:
                if ((cmd == CMD_LOCK_BLOCK) ||
                    (cmd == CMD_UNLOCK_BLOCK) ||
                    (cmd == CMD_LOCK_DOWN_BLOCK)) {
                    // Block locking not supported - ignore and move to Ready state
                    nextState = state_READ_STATUS;
                } else {
                    currentStatus.value |= sequenceError.value;
                }
                nextState = state_READ_STATUS;
                break;

            case state_PROGRAM_BUFFERED_COUNT:
                // write of the buffer count
                bufferCount = cmd;
                nextState   = state_PROGRAM_BUFFERED;
                break;

            case state_PROGRAM_BUFFERED_DONE:
                if (cmd != CMD_BUFFERED_PROGRAM_CONFIRM) {
                    currentStatus.value |= sequenceError.value;
                }
                nextState = state_READ_STATUS;
                break;

            case state_PROTECT:
                // Protection not supported - ignore
                // Spec does not indicate the state should change (?)
                break;

            case state_CONFIG:
                // Configuration register not supported - ignore and move to Ready state
                nextState = state_READ_STATUS;

                // Warn if attempting to place into burst mode
                Uns32 newConfigVal = (offset & 0xffff);
                if ((newConfigVal & 0x8000) == 0) {
                    bhmMessage(
                        "W", PREFIX"_BMU",
                        "Attempt to place Flash into unsupported synchronous burst read mode ignored."
                    );
                }
                break;

            default:
                switch (cmd) {
                case CMD_READ_ARRAY:
                    nextState = state_READ_ARRAY;
                    break;
                case CMD_READ_STATUS_REGISTER:
                    nextState = state_READ_STATUS;
                    break;
                case CMD_READ_DEVICE_ID:
                    nextState = state_READ_ID;
                    break;
                case CMD_READ_CFI_QUERY:
                    nextState = state_READ_CFI;
                    break;
                case CMD_CLEAR_STATUS_REGISTER:
                    currentStatus.value = clearStatus.value;
                    break;
                case CMD_WORD_PROGRAM_SETUP:
                case CMD_ALTERNATE_WORD_PROGRAM_SETUP:
                    nextState = state_PROGRAM;
                    break;
                case CMD_BUFFERED_PROGRAM_SETUP:
                    nextState = state_PROGRAM_BUFFERED_COUNT;
                    break;
                case CMD_BLOCK_ERASE_SETUP:
                    nextState = state_ERASE;
                    break;
                case CMD_LOCK_BLOCK_SETUP:
                    nextState = state_LOCK;
                    break;
                case 0xf0:
                case 0xaa:
                case 0x55:
                    // These are commands in other devices that this device
                    // does not recognize, but are issued by Linux - ignore
                    break;
                default:
                    bhmMessage(
                        "W", PREFIX"_UFC",
                        "Unrecognized flash command 0x%x in state %s",
                        cmd,
                        flashStateNames[thisState]
                    );
                }
                break;
            }
        }
    }

    if (PSE_DIAG_MEDIUM) {
        if (thisState != nextState) {
            bhmMessage(
                "I", PREFIX"_FSC",
                "Flash State changed: %s->%s",
                flashStateNames[thisState],
                flashStateNames[nextState]
            );
        }
    }

    if (programData) {
        // do a program of the flash memory array
        programArray(addr, backingStore+offset, bytes);
    }

    if (writeData || programData) {
        // data has been written to flash memory array,
        // either by simulator or by programData call above,
        // now must update backingStore
        writeArray(backingStore+offset, addr, bytes);
        if (PSE_DIAG_MEDIUM) {
            printData(offset, addr, bytes, "write");
        }
    } else {
        // write ignored so restore data from backing store
        writeArray(addr, backingStore+offset, bytes);
    }

    currentState = nextState;

    // install/uninstall read callbacks based on new state
    checkReadCallback(currentState);

}

//
// Called on reads from flash memory
//
static PPM_READ_CB(flashReadCB) {

    Uns32 readValue = 0;
    Uns32 offset    = (Uns8 *)addr - FLASH;

    checkOffset(offset, bytes);

    if (artifactAccess || currentState == state_READ_ARRAY) {

        // do a normal read from the flash memory
        switch (bytes) {
        case 1: readValue = *(Uns8 *) addr; break;
        case 2: readValue = *(Uns16 *)addr; break;
        case 4: readValue = *(Uns32 *)addr; break;
        default:
            bhmMessage("E", PREFIX, "Unsupported %d byte read at offset %d (0x%x)", bytes, offset, offset);
            break;
        }

        if (!artifactAccess) {
            // Uninstall read callback only after first normal read to minimize thrashing
            uninstallReadCallback();
        }

    } else if (bytes != 4) {

        bhmMessage(
            "W", PREFIX"_IWS",
            "Invalid size %d for FLASH device non-array read. Only 4 byte reads supported",
            bytes
        );

    } else {

        const char *readType = "read";

        if ((currentState == state_READ_STATUS) ||
            (currentState == state_PROGRAM_BUFFERED_COUNT)
        ) {

            readValue = DUAL_VALUE((Uns32)currentStatus.value);
            readType = "read status";

        } else if (currentState == state_READ_ID) {

            // Return Device Identifier Info based on block offset of address
            Uns16 deviceIdInfo   = 0;
            Uns32 deviceIdOffset = offset - getBlockBase(offset, NULL);

            if (deviceIdOffset == READ_ID_OFFSET_MANUFACTURER) {
                deviceIdInfo = READ_ID_MANUFACTURER;
            } else if (deviceIdOffset == READ_ID_OFFSET_CODE) {
                deviceIdInfo = READ_ID_CODE;
            } else if (deviceIdOffset == READ_ID_OFFSET_LOCK_CONFIG) {
                // All blocks are always unlocked so just use constant value
                deviceIdInfo = 0;
            } else if (deviceIdOffset == READ_ID_OFFSET_RCR) {
                deviceIdInfo = READ_ID_RCR;
            } else {
                bhmMessage(
                    "W", PREFIX"_URI",
                    "Unsupported Read Device ID offset 0x%x",
                    deviceIdOffset
                );
            }

            readValue = DUAL_VALUE(deviceIdInfo);
            readType = "read id";

        } else if (currentState == state_READ_CFI) {

            // Return CFI Query Structure Info based on address
            // Note: must adjust offset for 2x16 bit chips
            Uns32 CFIoffset  = offset >> 2;
            Uns8  cfiQryInfo = 0;

            if ((CFIoffset >= 0x10) && (CFIoffset < sizeof(cfiQueryData))) {
                cfiQryInfo = cfiQueryData[CFIoffset];
            } else if ((CFIoffset >= 0x10a) && (CFIoffset < 0x10a + sizeof(cfiEQTData))) {
                // CFI Extended Query Table data starts at 0x10a
                cfiQryInfo = cfiEQTData[CFIoffset-0x10a];
            }

            readValue = DUAL_VALUE(cfiQryInfo);
            readType = "read cfi";

        } else {

            bhmMessage(
                "W", PREFIX"_UFS",
                "Unexpected state %s in Flash read callback",
                flashStateNames[currentState]
            );

        }

        if (PSE_DIAG_MEDIUM) {
            printData(offset, &readValue, bytes, readType);
        }
    }

    return readValue;
}

//
// Load a binary image file into flash memory
//
static void loadImageFile(const char *fileName, Uns32 offset) {

    if (offset >= FLASH_SIZE) {

        bhmMessage(
            "F", PREFIX "_OOR",
            "Image file offset %d out of range of Flash memory size %d",
            offset,
            FLASH_SIZE
        );

    } else {

        FILE *fp = fopen(fileName, "rb");

        if (!fp) {

            bhmMessage(
                "F", PREFIX "_IFE",
                "Unable to open Flash image file '%s': %s",
                fileName,
                strerror(errno)
            );
            // not reached

        } else {

            // Read data from Image file, but not past end of flash memory
            Uns32 bytesRead = fread(FLASH+offset, 1, FLASH_SIZE-offset, fp);

            // Copy data to the backingStore
            memcpy(backingStore, FLASH+offset, bytesRead);

            if (ferror(fp)) {

                bhmMessage(
                    "F", PREFIX "_IFE",
                    "Error reading Flash image file '%s': %s",
                    fileName,
                    strerror(errno)
                );
                // not reached

            } else {

                bhmMessage(
                    "I", PREFIX "_IFR",
                    "%d bytes loaded from Flash image file '%s' to offset 0x%x",
                    bytesRead,
                    fileName,
                    offset
                );

                // Are any bytes left in the image file?
                Uns32 dummy;
                if (fread(&dummy, 1, 1, fp) != 0) {
                    bhmMessage(
                        "W", PREFIX"_ILF",
                        "Flash image file '%s' loaded at offset 0x%x "
                        "overflows flash memory size of %d bytes",
                        fileName,
                        offset,
                        FLASH_SIZE
                    );
                }
            }
        }

        if (fclose(fp)!=0) {
            bhmMessage(
                "F", PREFIX "_ICE",
                "Error closing Flash image file '%s': %s",
                fileName,
                strerror(errno)
            );
            // not reached
        }
    }
}

//
// Parse fileName string of filename[@offset][,filename[@offset]]...
//
static void loadImageFiles(const char *fileNamesIn) {

    char *next;
    char *fileName = strdup(fileNamesIn);

    while (fileName && *fileName) {

        // look for multiple file names separated by ','
        next = strchr(fileName, ',');
        if (next) {
            // separate file names by replacing ',' delimiter with \0
            *(next++) = '\0';
        }

        // Look for an offset separated by '@'
        Uns32 offset    = 0;
        char *offsetStr = strchr(fileName, '@');
        if (offsetStr) {
            // separate file name and offset by replacing '@' delimiter with \0
            char *end;
            *(offsetStr++) = '\0';
            offset = strtoul(offsetStr, &end, 0);
            if (!end || *end != '\0') {
                bhmMessage(
                    "F", PREFIX"_IFS",
                    "Invalid offset '%s' in image file specification: '%s'",
                    offsetStr,
                    fileNamesIn
                );
            }
        }

        // Load this file
        loadImageFile(fileName, offset);

        // check next name, if specified
        fileName = next;
    }
}

//
// Initialize flash memory to all 1's
//
static void initFlashMemory() {

    Uns32 blockOffset;
    Uns32 firstMainBlock  = FIRST_MAIN_BLOCK (FLASH_SIZE);
    Uns32 lastMainBlock   = LAST_MAIN_BLOCK  (FLASH_SIZE);
    Uns32 firstParamBlock = FIRST_PARAM_BLOCK(FLASH_SIZE);
    Uns32 lastParamBlock  = LAST_PARAM_BLOCK (FLASH_SIZE);

    // Erase Main Blocks
    for (
         blockOffset =  firstMainBlock;
         blockOffset <= lastMainBlock;
         blockOffset += MAIN_BLOCK_SIZE
    ) {
        eraseBlock(blockOffset);
    }

    // Erase Parameter Blocks
    for (
         blockOffset =  firstParamBlock;
         blockOffset <= lastParamBlock;
         blockOffset += PARAM_BLOCK_SIZE
    ) {
        eraseBlock(blockOffset);
    }
}

//
// Return n such that value = 2^^n
// Value must be a power of 2
//
static Uns32 log2Int(Uns32 value) {
    Uns32 n = 0;
    if (value) {
        if (value & (value-1)) {
            bhmMessage(
                "F", PREFIX "_NP2",
                "Argument %d not a power of 2",
                value
            );
            // Not reached
        }
        while (!(value & 0x1)) {
            n++;
            value >>= 1;
        }
    }
    return n;
}

//
// Set the CFI Device geometry info according to the size of the memory defined
//
static void setCFIGeometry() {

    Uns32 size           = FLASH_SIZE;
    Uns32 numBlocks      = size / MAIN_BLOCK_SIZE;
    Uns32 numMainBlocks  = numBlocks - 1;
    Uns32 numParamBlocks = 4;

    // Check for legal flash memory size: power of 2 and at least 2 main blocks
    if (numBlocks < 2 || (size & (size-1))) {
        bhmMessage(
            "F", PREFIX "_IS",
            "Invalid Flash memory size 0x%x: must be power of 2 >= 0x%x",
            FLASH_SIZE,
            (2*MAIN_BLOCK_SIZE)
        );
    }

    // 0x27: n such that device size = 2n in number of bytes
    // Note: adjust size for single chip
    cfiQueryData[0x27] = log2Int(size/2);

    // 0x29:0x28: Flash device width: 1 => x16 bits
    cfiQueryData[0x28] = 1;
    cfiQueryData[0x29] = 0;

    // 0x2b:0x2b: Write buffer size
    cfiQueryData[0x2a] = 6;
    cfiQueryData[0x2b] = 0;

    // 0x2c: number of regions with different sizes
    cfiQueryData[0x2c] = 2;

    // 0x2e:0x2d: Number of same size blocks in region 1 minus 1
    cfiQueryData[0x2d] =  (numMainBlocks - 1)       & 0xff;
    cfiQueryData[0x2e] = ((numMainBlocks - 1) >> 8) & 0xff;

    // 0x30:0x2f: Size of blocks in region 1 divided by 256
    // Note: adjust BLOCK_SIZE for single chip
    cfiQueryData[0x2f] = ((MAIN_BLOCK_SIZE/2)>>8)  & 0xff;
    cfiQueryData[0x30] = ((MAIN_BLOCK_SIZE/2)>>16) & 0xff;

    // 0x32:0x31: Number of same size blocks in region 2 minus 1
    // Region 2 is last main block implemented as 4 parameter blocks
    cfiQueryData[0x31] =  (numParamBlocks - 1)       & 0xff;
    cfiQueryData[0x32] = ((numParamBlocks - 1) >> 8) & 0xff;

    // 0x34:0x33: Size of blocks in region 2 divided by 256
    // Note: adjust BLOCK_SIZE for single chip
    cfiQueryData[0x33] = ((PARAM_BLOCK_SIZE/2)>>8)  & 0xff;
    cfiQueryData[0x34] = ((PARAM_BLOCK_SIZE/2)>>16) & 0xff;

}

//
// Called to create the Flash model state.
//
static void flashNorCFIInit() {

    char imageFile[BHM_MAX_PATH];

    // Set the CFI configuration data
    setCFIGeometry();

    // Initialize flash memory to all 1's
    initFlashMemory();

    // Load image file(s), if specified
    if (bhmStringParamValue("image", (char *)imageFile, sizeof(imageFile))) {
        loadImageFiles(imageFile);
    } else {
        if (PSE_DIAG_LOW) {
            bhmMessage(
                "W", PREFIX "_NFI",
                "No image file(s) specified for initializing flash memory"
            );
        }
    }

}

PPM_CONSTRUCTOR_CB(constructor) {

    // Call the iGen-generated peripheral constructor code
    periphConstructor();

    // Initialize the flash memory
    flashNorCFIInit();

    // Install callbacks on write
    ppmInstallWriteCallback(flashWriteCB, NULL, FLASH, FLASH_SIZE);

}

PPM_DESTRUCTOR_CB(destructor) {
    // TODO: support saving image of flash memory state at simulation termination
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

