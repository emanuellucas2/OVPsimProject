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

#define LCLPREFIX PREFIX"_SPANSION_S25FL"

// Commands
// Micron/Spansion(Cyprus) N25Q128A (S25FL128SAGMFIR01)
// http://www.cypress.com/file/177966/download
// 001-98283_S25FL128S_S25FL256S_128_MBIT_16_MBYTE_256_MBIT_32_MBYTE_3.0V_SPI_FLASH_MEMORY

// Read Device Identification
#define CMD_READ_ID    0x90 // (REMS) Read Electronic Manufacturer Signature 90
#define CMD_RDID       0x9F // Read ID (JEDEC Manufacturer ID and JEDEC CFI) 9F
#define CMD_RES        0xAB // Read Electronic Signature AB
//Register Access
#define CMD_RDSR1      0x05 // Read Status Register-1
#define CMD_RDSR2      0x07 // Read Status Register-2
#define CMD_RDCR       0x35 // Read Configuration Register-1
#define CMD_WRR        0x01 // Write Register (Status-1, Configuration-1)
#define CMD_WRDI       0x04 // Write Disable
#define CMD_WREN       0x06 // Write Enable
#define CMD_CLSR       0x30 // Clear Status Register-1 - Erase/Prog. Fail Reset
#define CMD_ABRD       0x14 // AutoBoot Register Read
#define CMD_ABWR       0x15 // AutoBoot Register Write
#define CMD_BRRD       0x16 // Bank Register Read
#define CMD_BRWR       0x17 // Bank Register Write
#define CMD_BRAC       0xB9 // Bank Register Access (Legacy Command formerly used for Deep Power Down)
#define CMD_DLPRD      0x41 // Data Learning Pattern Read
#define CMD_PNVDLR     0x43 // Program NV Data Learning Register
#define CMD_WVDLR      0x4A // Write Volatile Data Learning Register
// Read Flash Array
#define CMD_READ       0x03 // Read (3- or 4-byte address) 03
#define CMD_4READ      0x13 // Read (4-byte address) 13
#define CMD_FAST_READ  0x0B // Fast Read (3- or 4-byte address) 0B
#define CMD_4FAST_READ 0x0C // Fast Read (4-byte address) 0C
#define CMD_DDRFR      0x0D // DDR Fast Read (3- or 4-byte address) 0D
#define CMD_4DDRFR     0x0E // DDR Fast Read (4-byte address) 0E
#define CMD_DOR        0x3B // Read Dual Out (3- or 4-byte address) 3B
#define CMD_4DOR       0x3C // Read Dual Out (4-byte address) 3C
#define CMD_QOR        0x6B // Read Quad Out (3- or 4-byte address) 6B
#define CMD_4QOR       0x6C // Read Quad Out (4-byte address) 6C
#define CMD_DIOR       0xBB // Dual I/O Read (3- or 4-byte address) BB
#define CMD_4DIOR      0xBC // Dual I/O Read (4-byte address) BC
#define CMD_DDRDIOR    0xBD // DDR Dual I/O Read (3- or 4-byte address) BD
#define CMD_4DDRDIOR   0xBE // DDR Dual I/O Read (4-byte address) BE
#define CMD_QIOR       0xEB // Quad I/O Read (3- or 4-byte address) EB
#define CMD_4QIOR      0xEC // Quad I/O Read (4-byte address) EC
#define CMD_DDRQIOR    0xED // DDR Quad I/O Read (3- or 4-byte address) ED
#define CMD_4DDRQIOR   0xEE // DDR Quad I/O Read (4-byte address) EE
// Program Flash Array
#define CMD_PP         0x02 // Page Program (3- or 4-byte address) 02
#define CMD_4PP        0x12 // Page Program (4-byte address) 12
#define CMD_QPPA       0x32 // Quad Page Program (3- or 4-byte address) 32
#define CMD_QPPB       0x38 // Quad Page Program - Alternate instruction (3- or 4-byte address) 38
#define CMD_4QPP       0x34 // Quad Page Program (4-byte address) 34
#define CMD_PGSP       0x85 // Program Suspend 85
#define CMD_PGRS       0x8A // Program Resume 8A
// Erase Flash Array
#define CMD_P4E        0x20 // Parameter 4-kB, sector Erase (3- or 4-byte address) 20
#define CMD_4P4E       0x21 // Parameter 4-kB, sector Erase (4-byte address) 21
#define CMD_BEA        0x60 // Bulk Erase 60
#define CMD_BEB        0xC7 // Bulk Erase (alternate command) C7
#define CMD_SE         0xD8 // Erase 64 kB or 256 kB (3- or 4-byte address) D8
#define CMD_4SE        0xDC // Erase 64 kB or 256 kB (4-byte address) DC
#define CMD_ERSP       0x75 // Erase Suspend 75
#define CMD_ERRS       0x7A // Erase Resume 7A
// One Time Program Array
#define CMD_OTPP       0x42 // OTP Program 42
#define CMD_OTPR       0x4B // OTP Read 4B
// Advanced Sector Protection
#define CMD_DYBRD      0xE0 // DYB Read E0
#define CMD_DYBWR      0xE1 // DYB Write E1
#define CMD_PPBRD      0xE2 // PPB Read E2
#define CMD_PPBP       0xE3 // PPB Program E3
#define CMD_PPBE       0xE4 // PPB Erase E4
#define CMD_ASPRD      0x2B // ASP Read 2B
#define CMD_ASPP       0x2F // ASP Program 2F
#define CMD_PLBRD      0xA7 // PPB Lock Bit Read A7
#define CMD_PLBWR      0xA6 // PPB Lock Bit Write A6
#define CMD_PASSRD     0xE7 // Password Read E7
#define CMD_PASSP      0xE8 // Password Program E8
#define CMD_PASSU      0xE9 // Password Unlock E9
// Reset
#define CMD_RESET      0xF0 // Software Reset F0
#define CMD_MBR        0xFF // Mode Bit Reset FF
// Reserved for Future Use
#define CMD_MPM        0xA3 // Reserved for Multi-I/O-High Perf Mode (MPM) A3
#define CMD_RFU18      0x18 // Reserved-18 Reserved 18
#define CMD_RFUE5      0xE5 // Reserved-E5 Reserved E5
#define CMD_RFUE6      0xE6 // Reserved-E6 Reserved E6

// Read Device Identifier Data CMD_READ_ID (REMS)
// 0x01 = Spansion
#define READ_ID_MANUFACTURER                  0x01
// 0x17 = 128-MBit
#define READ_ID_CODE                          0x17

typedef enum flashStateE {
    state_IDLE = 0,         // Initial state
    state_READ_ARRAY,
    state_DELAY_READ_ARRAY,
    state_READ_ID,
    state_READ_CFI,
    state_READ_STATUS,
    state_WRITE_ENABLE,
    state_PROGRAM,
    state_PAGE_PROGRAM,
    state_SECTOR_ERASE,
    state_BULK_ERASE,
    state_LOCK,
    state_PROTECT,
    state_CONFIG
} flashStateT;

#define STATE_ENUM_STRING(_N)  [state_##_N] = #_N
static const char *flashStateNames[] = {
    STATE_ENUM_STRING(IDLE),
    STATE_ENUM_STRING(READ_ARRAY),
    STATE_ENUM_STRING(DELAY_READ_ARRAY),
    STATE_ENUM_STRING(READ_ID),
    STATE_ENUM_STRING(READ_CFI),
    STATE_ENUM_STRING(READ_STATUS),
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
        Uns32   WIP:   1;   // Write In Progress (0=complete, 1=in progress)
        Uns32   WEL:   1;   // Write Enable Latch (0=ignore commands 1=accept)
        Uns32   BP:    3;   // Block Protection
        Uns32   E_ERR: 1;   // Erase Error
        Uns32   P_ERR: 1;   // Programming Error
        Uns32   SRWD:  1;   // Status Register Write Disable
    } flags;
    Uns32 value;
} flashStatusT;
//static const flashStatusT sequenceError = { .flags = {.ES=1, .PS=1} };
static const flashStatusT clearStatus   = { .value = 0 };
typedef union flashStatus2U {
    struct {
        Uns32   PS:   1;   // Program Suspend
        Uns32   ES:   1;   // Erase Suspend
        Uns32   RFU:  6;
    } flags;
    Uns32 value;
} flashStatus2T;
typedef union flashConfigU {
    struct {
        Uns32   FREEZE: 1;   // Lock BP OTP
        Uns32   QUAD:   1;   // Quad I/O Operation
        Uns32   TBPARM: 1;   // OTP
        Uns32   BPNV:   1;   // OTP
        Uns32   RFU:    1;   // Reserved
        Uns32   TBPROT: 1;   // OTP Block Protection
        Uns32   LC:     2;   // Latency Code
    } flags;
    Uns32 value;
} flashConfigT;
typedef union flashBankAddressU {
    struct {
        Uns32   BA24:   1;   // Bank Address
        Uns32   RFU:    6;   // Reserved
        Uns32   EXTADD: 1;   // Extended Address Enable
    } flags;
    Uns32 value;
} flashBankAddressT;

//
// CFI Query Data
// (See section C.4 in Intel StrataFlash Embedded Memory P30 Family Datasheet)
//
static Uns8 cfiQueryData[] = {
/*00h*/ 0x01, 0x20, 0x18, 0x4d, // Manufacturer and Device Id (128MB)
        0x01, 0x80, 'R',  0x00, // Model Number "R0"
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
/*10h*/ 'Q', 'R', 'Y',          // ID string
        0x02, 0x00,             // Vendor command set ID
        0x40, 0x01,             // Extended query table primary address
        0x53, 0x46,             // Alternate vendor command set
        0x51, 0x00,             // Secondary Extended Query table primary address
/*1Bh*/ 0x27, 0x36, 0x00, 0x00, // System Interface (from data sheet)
        0x06, 0x08, 0x08, 0x0f,
        0x02, 0x02, 0x03, 0x03,
/*27h*/ 0x18, 0x02, 0x01, 0x08, // Device Geometry (per chip)
        0x00, 0x02, 0x1f, 0x00, // Set in setCFIGeometry() according to FLASH_SIZE
        0x10, 0x00, 0xfd, 0x00,
        0x00, 0x01,
/*35h*/ 0xff, 0xff, 0xff, 0xff, // reserved
        0xff, 0xff, 0xff, 0xff,
        0xff, 0xff
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
static flashStateT currentState = state_IDLE;

// Current Status register (initialize DWS=1 to indicate ready)
static flashStatusT currentStatus = { .value = 0 };

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
            "F", LCLPREFIX "_IS",
            "Invalid Flash memory size 0x%x: must be power of 2 >= 0x%x",
            FLASH_SIZE,
            (2*MAIN_BLOCK_SIZE)
        );
    }

    // 0x27: n such that device size = 2n in number of bytes
    // Note: adjust size for single chip
    cfiQueryData[0x27] = log2Int(size/2);

    // 0x29:0x28: Flash device width: 5 => Multi I/O SPI 3-byte address
    cfiQueryData[0x28] = 5;
    cfiQueryData[0x29] = 0;

    // 0x2a:0x2b: Write buffer size
    cfiQueryData[0x2a] = 8;
    cfiQueryData[0x2b] = 0;

    // 0x2c: number of regions with different sizes
    cfiQueryData[0x2c] = 2;

    // 0x2e:0x2d: Number of same size blocks in region 1 minus 1
    cfiQueryData[0x2d] =  (numParamBlocks - 1)       & 0xff;
    cfiQueryData[0x2e] = ((numParamBlocks - 1) >> 8) & 0xff;

    // 0x30:0x2f: Size of blocks in region 1 divided by 256
    // Note: adjust BLOCK_SIZE for single chip
    cfiQueryData[0x2f] = ((PARAM_BLOCK_SIZE/2)>>8)  & 0xff;
    cfiQueryData[0x30] = ((PARAM_BLOCK_SIZE/2)>>16) & 0xff;

    // 0x32:0x31: Number of same size blocks in region 2 minus 1
    // Region 2 is last main block implemented as 4 parameter blocks
    cfiQueryData[0x31] =  (numMainBlocks - 1)       & 0xff;
    cfiQueryData[0x32] = ((numMainBlocks - 1) >> 8) & 0xff;

    // 0x34:0x33: Size of blocks in region 2 divided by 256
    // Note: adjust BLOCK_SIZE for single chip
    cfiQueryData[0x33] = ((MAIN_BLOCK_SIZE/2)>>8)  & 0xff;
    cfiQueryData[0x34] = ((MAIN_BLOCK_SIZE/2)>>16) & 0xff;

}

//
// Called to create the Flash model state.
//
void flashSpansionS25FLInit() {

    if(PSE_DIAG_HIGH)
        bhmMessage("I", LCLPREFIX"_INI", "Initialize");

    char imageFileString[BHM_MAX_PATH];

    // Set the CFI configuration data
    setCFIGeometry();

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
void flashSpansionS25FLDisable() {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", LCLPREFIX"_DIS", "Disable");

    currentState = state_IDLE;
}



//
// Called when an access is made to the flash memory
//
Uns32 flashSpansionS25FLAccess(Uns32 commandOrData, Uns32 size) {

    Bool         programData   = False;
    flashStateT  thisState     = currentState;
    flashStateT  nextState     = currentState;
    static Uns32 readValue     = 0;
    const char  *readType      = "read";
    static Uns32 readDelay     = 0;     // how many bytes are delayed on initial read data
    static Uns32 CFIoffset     = 0;     // index into CFI array while in state_READ_CFI

    if(PSE_DIAG_HIGH)
        bhmMessage(
        "I", LCLPREFIX"_FS",
        "Flash State : %s",
        flashStateNames[thisState]);

    if ((thisState == state_IDLE) ||
        (thisState == state_WRITE_ENABLE)){
        // Valid states to accept commands

        CFIoffset = 0;  // reset index

        // Write data is a command
        Uns8   cmd = GET_CMD(commandOrData);
        Uns32 addr = GET_ADDR24(commandOrData);

        if(PSE_DIAG_HIGH) {
            bhmMessage("I", LCLPREFIX"_CMD","Command:0x%x addr=0x%03x size:%d", cmd, addr, size);
        }

        switch (cmd) {
        case CMD_WREN:
            currentStatus.flags.WEL = 1;
            nextState = state_WRITE_ENABLE;
            break;
        case CMD_FAST_READ:
        case CMD_DOR:
        case CMD_QOR:
        case CMD_DIOR:
        case CMD_QIOR:
            readDelay = 1;
            flashAddress = addr;
            nextState = state_DELAY_READ_ARRAY;
            break;
        case CMD_READ:
            flashAddress = addr;
            nextState = state_DELAY_READ_ARRAY;
            break;
        case CMD_RDSR1:
            nextState = state_READ_STATUS;
            break;
        case CMD_READ_ID:
            nextState = state_READ_ID;
            break;
        case CMD_RDID:
            nextState = state_READ_CFI;
            readDelay = 1;
            break;
        case CMD_CLSR:
            currentStatus.value = clearStatus.value;
            break;
        case CMD_PP:
        case CMD_QPPA:
        case CMD_QPPB:
            flashAddress = addr;
            nextState = state_PAGE_PROGRAM;
            if(PSE_DIAG_MEDIUM) {
                bhmMessage(
                    "I", LCLPREFIX"_PP",
                    "Page Program 0x%08x", addr);
            }
            break;
        case CMD_PGSP:
        case CMD_PGRS:
            break;
        case CMD_P4E:
        case CMD_BEA:
        case CMD_BEB:
            flashAddress = addr;
            nextState = state_BULK_ERASE;
            break;
        case CMD_SE:
            flashAddress = addr;
            nextState = state_SECTOR_ERASE;
            break;
        case CMD_ERSP:
        case CMD_ERRS:
            break;

        case CMD_RESET:
            bhmMessage(
                "I", LCLPREFIX"_RST",
                "Software Reset"
            );
            break;

        case CMD_OTPP:
        case CMD_OTPR:
            bhmMessage(
                "W", LCLPREFIX"_OTP",
                "OTP Not Supported"
            );
            break;

        case CMD_DYBRD:
        case CMD_DYBWR:
        case CMD_PPBRD:
        case CMD_PPBP:
        case CMD_PPBE:
        case CMD_ASPRD:
        case CMD_ASPP:
        case CMD_PLBRD:
        case CMD_PLBWR:
        case CMD_PASSRD:
        case CMD_PASSP:
        case CMD_PASSU:
            bhmMessage(
                "W", LCLPREFIX"_ASP",
                "ASP Not Supported"
            );
            break;

        // The following are reserved commands
        case CMD_RDSR2:
        case CMD_MPM:
        case CMD_RFU18:
        case CMD_RFUE5:
        case CMD_RFUE6:
            bhmMessage(
                "W", LCLPREFIX"_RFU",
                "Reserved flash command 0x%x in state %s",
                cmd,
                flashStateNames[thisState]
            );
            break;

        // The following are extended addressing commands
        case CMD_4FAST_READ:
        case CMD_4READ:
        case CMD_4DOR:
        case CMD_4QOR:
        case CMD_4DIOR:
        case CMD_4QIOR:
        case CMD_4DDRFR:
        case CMD_4DDRDIOR:
        case CMD_4DDRQIOR:
        case CMD_4PP:
        case CMD_4QPP:
        case CMD_4P4E:
        case CMD_4SE:
            bhmMessage(
                "W", LCLPREFIX"_EXA",
                "Extended Addressing not supported, flash command 0x%x in state %s ignored",
                cmd,
                flashStateNames[thisState]
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

    if (programData) {
        // do a program of the flash memory array
        programArray(FLASH+flashAddress, (Uns8 *)&commandOrData, size);
        flashAddress += size;
    }

    currentState = nextState;

    if (currentState == state_READ_ARRAY) {

        // do a normal read from the flash memory
        readArray(((Uns8 *)&readValue)+readDelay, FLASH+flashAddress, size-readDelay);

        if (PSE_DIAG_MEDIUM) {
            printData(flashAddress, &readValue, size, readType);
        }
        flashAddress += (size-readDelay);
        readDelay=0;

    } else if (currentState == state_READ_STATUS) {

        readValue = currentStatus.value;
        readType  = "read status";

    } else if (currentState == state_READ_ID) {

        // Return Device Identifier Info
        Uns32 deviceIdInfo   = 0;
        Uns32 i;
        // The Manufacturer Id and Device Id shift in
        for (i=0;i<size;i++) {
            Uns32 shift = 8*(3-i);
            if(i & (flashAddress & 1)) {
                deviceIdInfo |= READ_ID_CODE << shift;
            } else {
                deviceIdInfo |= READ_ID_MANUFACTURER << shift;
            }
        }

        readValue = deviceIdInfo;
        readType  = "read id";

    } else if (currentState == state_READ_CFI) {

        // Return CFI Query Structure Info
        Uns32 cfiQryInfo = 0;

        if (CFIoffset < sizeof(cfiQueryData)) {
            // CFI Query Table data
            readArray(((Uns8 *)&cfiQryInfo)+readDelay, (Uns8 *)&cfiQueryData[CFIoffset], size-readDelay);
            if(PSE_DIAG_HIGH)
                bhmMessage(
                "I", LCLPREFIX"_CFI",
                "0x%x (0x%x)",cfiQryInfo, cfiQueryData[CFIoffset]);

        } else if (CFIoffset < (sizeof(cfiQueryData) + sizeof(cfiEQTData))) {
            // CFI Extended Query Table data
            readArray(((Uns8 *)&cfiQryInfo)+readDelay, (Uns8 *)&cfiEQTData[CFIoffset-sizeof(cfiQueryData)], size-readDelay);
            if(PSE_DIAG_HIGH)
                bhmMessage(
                "I", LCLPREFIX"_CFIE",
                "0x%x (0x%x)",cfiQryInfo, cfiEQTData[CFIoffset-sizeof(cfiQueryData)]);
        } else {
            if(PSE_DIAG_HIGH)
                bhmMessage(
                "I", LCLPREFIX"_CFI_OV", "CFI Index Overflowed");
        }
        CFIoffset+=size-readDelay;    // move to next element

        readDelay = 0;
        readValue = cfiQryInfo;
        readType  = "read cfi";

    }

    return readValue;
}

// defined in qpsi.user.c
extern char *imageFileP;
void flashSpansionS25FLFinish() {

    if(PSE_DIAG_HIGH)
        bhmMessage("I", LCLPREFIX"_FIN", "Finish");

    // write image back out if specified
    if (imageFileP) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", LCLPREFIX"_WIM", "Write Flash Image Output to %s", imageFileP);

        processImageFiles(imageFileP, False);
    }
}
