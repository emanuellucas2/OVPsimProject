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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

#define PREFIX "FlashDevice"
//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

typedef enum flashCommandE {
    state_READ       = 0,
    state_COMMAND1,
    state_COMMAND2,
    state_COMMAND_AUTO,
    state_COMMAND_ERASE,
    state_COMMAND_PROGRAM,
    state_COMMAND_ERASE_UNLOCK_ONE,
    state_COMMAND_ERASE_UNLOCK_TWO,
    state_LAST                  // KEEP LAST
} flashCommand;

#define COMMAND_ADDRESS_MASK 0x7ff
#define DATA_MASK            0xff

#define ID_MANUFACTURER 0x01
#define ID_DEVICE       0x22b9
#define SECTOR_OK       0x00

static Bool inline isCommandReset(Addr address, Uns32 data){
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if (thisData == 0xf0) {
        return True;
    }
    return False;
}
static Bool inline isCommandUnlockOne(Addr address, Uns32 data){
    Uns32 thisAddress = (Uns32)address & COMMAND_ADDRESS_MASK;
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if ((thisAddress == 0x555) && (thisData == 0xaa)) {
        return True;
    }
    return False;
}
static Bool inline isCommandUnlockTwo(Addr address, Uns32 data){
    Uns32 thisAddress = (Uns32)address & COMMAND_ADDRESS_MASK;
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if ((thisAddress == 0x2aa) && (thisData == 0x55)) {
        return True;
    }
    return False;
}
static Bool inline isCommandAutoSelect(Addr address, Uns32 data){
    Uns32 thisAddress = (Uns32)address & COMMAND_ADDRESS_MASK;
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if ((thisAddress == 0x555) && (thisData == 0x90)) {
        return True;
    }
    return False;
}
static Bool inline isCommandProgram(Addr address, Uns32 data){
    Uns32 thisAddress = (Uns32)address & COMMAND_ADDRESS_MASK;
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if ((thisAddress == 0x555) && (thisData == 0xa0)) {
        return True;
    }
    return False;
}
static Bool inline isCommandErase(Addr address, Uns32 data){
    Uns32 thisAddress = (Uns32)address & COMMAND_ADDRESS_MASK;
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if ((thisAddress == 0x555) && (thisData == 0x80)) {
        return True;
    }
    return False;
}
static Bool inline isCommandEraseSector(Uns32 data){
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if (thisData == 0x30) {
        return True;
    }
    return False;
}
static Bool inline isCommandEraseChip(Addr address, Uns32 data){
    Uns32 thisAddress = (Uns32)address & COMMAND_ADDRESS_MASK;
    Uns32 thisData = (Uns32)data & DATA_MASK;
    if ((thisAddress == 0x555) && (thisData == 0x10)) {
        return True;
    }
    return False;
}

typedef struct vmiosObjectS  {

    // Command state
    Uns32        state;

    // Buffer
    void*        flashBase;
    Uns32        flashSize;

    // the Flash RAM mapped region
    memDomainP   domain;
    Addr         lowAddr;
    Addr         highAddr;

    // diagnostics
    Uns32 diagLevel;
} vmiosObject;

//
// FWD references
//
static void uninstallFlashReadCallback(vmiosObjectP object);
static void installFlashReadCallback(vmiosObjectP object);


static VMI_MEM_WATCH_FN(calledOnWrite) {
    vmiosObjectP object = userData;
    Uns32 data;

    if(bytes==1) {
        data = *(Uns8 *)value;
    } else if(bytes==2) {
        data = *(Uns16 *)value;
    } else if(bytes==4) {
        data = *(Uns32 *)value;
    } else {
        vmiMessage("I", PREFIX "_WRITE_CB", "illegal byte size %u", bytes);
        data = 0;
    }

    if(object->diagLevel)
        vmiMessage("I", PREFIX "_WRITE_CB", "address 0x%08x bytes %u 0x%08x state %u",
                            (Uns32)address, bytes, data, object->state);


    switch(object->state) {
        case state_READ:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State READ");
            if (isCommandUnlockOne(address, data)) {
                installFlashReadCallback(object);
                object->state = state_COMMAND1;
            }
            break;
        case state_COMMAND1:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State COMMAND1");
            if (isCommandUnlockTwo(address, data)) {
                object->state = state_COMMAND2;
            } else {
                uninstallFlashReadCallback(object);
                object->state = state_READ;
            }
            break;
        case state_COMMAND2:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State COMMAND2");
            if (isCommandAutoSelect(address, data)){
                object->state = state_COMMAND_AUTO;
            } else if (isCommandErase(address, data)){
                uninstallFlashReadCallback(object);
                object->state = state_COMMAND_ERASE;
            } else if (isCommandProgram(address, data)){
                uninstallFlashReadCallback(object);
                object->state = state_COMMAND_PROGRAM;
            } else {
                uninstallFlashReadCallback(object);
                object->state = state_READ;
            }
            break;
        case state_COMMAND_PROGRAM:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State COMMAND PROGRAM");
            // Program byte/word
            vmiMessage("I", PREFIX , "Program 0x%08x = 0x%08x", (Uns32)address, data);
            Uns8 *ptr = (Uns8 *)object->flashBase + ((Uns8)address & (Uns8)(object->flashSize-1));
            *ptr = (data & 0xff);
            object->state = state_READ;
            break;
        case state_COMMAND_ERASE:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State COMMAND ERASE");
            if (isCommandUnlockOne(address, data)){
                object->state = state_COMMAND_ERASE_UNLOCK_ONE;
            } else {
                object->state = state_READ;
            }
            break;
        case state_COMMAND_ERASE_UNLOCK_ONE:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State COMMAND ERASE UNLOCK ONE");
            if (isCommandUnlockTwo(address, data)){
                object->state = state_COMMAND_ERASE_UNLOCK_TWO;
            } else {
                object->state = state_READ;
            }
            break;
        case state_COMMAND_ERASE_UNLOCK_TWO:
            if(object->diagLevel) vmiMessage("I", PREFIX "_WR", "State COMMAND ERASE UNLOCK TWO");
            if (isCommandEraseChip(address, data)){
                // Erase Chip
                vmiMessage("I", PREFIX , "Erase Chip 0x%08x %u", (Uns32)(UnsPS)object->flashBase, object->flashSize);
                Uns32 *ptr = (Uns32 *)object->flashBase;
                Uns32 i=0;
                while(i<object->flashSize/4){
                    *ptr = 0xffffffff;
                    i++; ptr++;
                }
            } else if (isCommandEraseSector(data)){
                // Erase Sector
                vmiMessage("I", PREFIX , "Erase Sector 0x%08x", (Uns32)address);
            }
            object->state = state_READ;
            break;
        default:
            vmiMessage("W", PREFIX "_US", "Unknown State");
    }
}

static VMI_MEM_WATCH_FN(calledOnRead) {
    Uns32 result = 0;
    vmiosObjectP object = userData;

    if(object->diagLevel)
        vmiMessage("I", PREFIX "_READ_CB", "address 0x%08x bytes %u state %u",
                                        (Uns32)address, bytes, object->state);

    if(object->state == state_COMMAND_AUTO) {
        uninstallFlashReadCallback(object);
        object->state = state_READ;
        switch((Uns32)address & 0xf) {
        case 0:
            result = ID_MANUFACTURER;
            if(object->diagLevel) vmiMessage("I", PREFIX "_RD", "Read Manufacturer Id %d", result);
            break;
        case 2:
            result = ID_DEVICE;
            if(object->diagLevel) vmiMessage("I", PREFIX "_RD", "Read Device Id %d", result);
            break;
        case 4:
            result = SECTOR_OK;
            if(object->diagLevel) vmiMessage("I", PREFIX "_RD", "Read Sector Ok %d", result);
            break;
        default:
            break;
        }
    }

    if(bytes==1) {
        *(Uns8 *)value = result;
    } else if(bytes==2) {
        *(Uns16 *)value = result;
    } else if(bytes==4) {
        *(Uns32 *)value = result;
    } else {
        vmiMessage("I", PREFIX "_READ_CB", "illegal byte size %u", bytes);
    }
}

//
// Install a callback on writes to FLASH ram
//
static void installFlashWriteCallback(vmiosObjectP object)
{
    vmirtAddWriteCallback(
        object->domain,
        0,
        object->lowAddr,
        object->highAddr,
        calledOnWrite,
        object
    );
}
//
// Install a callback on reads of FLASH ram
// used when command sequence for autoselect
//
static void installFlashReadCallback(vmiosObjectP object)
{
    vmirtAddReadCallback(
        object->domain,
        0,
        object->lowAddr,
        object->highAddr,
        calledOnRead,
        object
    );
}

//
// Remove the callback from the VGA ram
//
static void uninstallFlashReadCallback(vmiosObjectP object)
{
    vmirtRemoveReadCallback(
        object->domain,
        0,
        object->lowAddr,
        object->highAddr,
        calledOnRead,
        object
    );
}

int parseLine(char *theline, Uns32 lineData[], Uns32 *addr, Uns32 *num, Uns32 *lineType)
{
    int sum, len, cksum;
    char *ptr;

    *num = 0;
    // first character must be ':'
    if (theline[0] != ':')
        return 0;
    if (strlen(theline) < 11)
        return 0;
    ptr = theline+1;
    // get length field
    if (!sscanf(ptr, "%02x", &len))
        return 0;
    ptr += 2;
    if ( strlen(theline) < (11 + (len * 2)) )
        return 0;
    // get address offset
    if (!sscanf(ptr, "%04x", addr))
        return 0;
    ptr += 4;
    // get record type
    if (!sscanf(ptr, "%02x", lineType))
        return 0;
    ptr += 2;
    sum = (len & 0xff) + ((*addr >> 8) & 0xff) + (*addr & 0xff) + (*lineType & 0xff);
    // get data
    while(*num != len) {
        if (!sscanf(ptr, "%02x", &lineData[*num])) return 0;
        ptr += 2;
        sum += lineData[*num] & 0xff;
        (*num)++;
        if (*num >= 256)
            return 0;
    }
    // checksum
    if (!sscanf(ptr, "%02x", &cksum))
        return 0;
    if ( ((sum & 0xff) + (cksum & 0xff)) & 0xff )
        return 0; /* checksum error */

    // successfully parsed
    return 1;
}

/* loads an intel hex file into the global memory[] array */
/* filename is a string of the file to be opened */



//
// Load a hex file into memory
//
#define MAX_LINE_LENGTH 256

static int loadHexFile(vmiosObjectP object, const char *fileName, Bool swap) {

    FILE *fp;
    char inBuf[MAX_LINE_LENGTH + 1];
    Uns32 addr, addrBase, dataLength, lineType;
    Uns32 lineData[256];
    Uns32 i, lineno=1;

    fp = fopen(fileName, "r");

    if (!fp) {
        vmiMessage("F", PREFIX "_HLF", "Failed to open Memory Initialization File %s\n", fileName);
        // never reaches here
    }

    if (object->diagLevel)
        vmiMessage("I", PREFIX "_HL","Loading Hex file %s\n", fileName);

    while (!feof(fp) && !ferror(fp)) {
        inBuf[0] = '\0';
        if (fgets(inBuf, MAX_LINE_LENGTH, fp) == NULL) {
            continue;
        }
        // Remove garbage from end of line
        if (inBuf[strlen(inBuf)-1] == '\n') inBuf[strlen(inBuf)-1] = '\0';
        if (inBuf[strlen(inBuf)-1] == '\r') inBuf[strlen(inBuf)-1] = '\0';
        // Parse the next line
        if (parseLine(inBuf, lineData, &addr, &dataLength, &lineType)) {
            if (lineType == 4) {  // set address
                addrBase = 0;
                for(i=0; i<=(dataLength-1)&&i<4; i++) {
                    addrBase += lineData[i] << (24-(i*8));
                }
                if (object->diagLevel)
                    vmiMessage("I", PREFIX "_HLL","Set Address 0x%08x", addrBase);
            }
            if (lineType == 0) {  // data
                if (object->diagLevel)
                    vmiMessage("I", PREFIX "_HLL","Load Line at 0x%08x", addr);

                for(i=0; i<=(dataLength-1); i++) {
                    if(addr+i > object->flashSize)
                        vmiMessage("F", PREFIX "_HLO","Address (0x%08x) out of range for Memory Size (0x%08x)",
                                                    addr+i, object->flashSize);

                    if (object->diagLevel)
                        vmiPrintf ("  0x%08x -> 0x%02x\n", addr+i, lineData[i] & 0xff);
                    *(Uns8 *)(object->flashBase+addr+i) = (lineData[i] & 0xff);
                }

                if (object->diagLevel)
                    vmiPrintf ("\n");
            }
            if (lineType == 1) {  // end of file
                break;
            }
            if (lineType == 2) ;  // start of file
        } else {
            vmiMessage("F", PREFIX "_HLP", "Error: '%s'. Failed parse on line: %d\n", fileName, lineno);
        }
        lineno++;
    }
    if (object->diagLevel)
        vmiMessage("I", PREFIX "_HLC","Load Complete");

    if (fclose(fp)!=0) {
        vmiMessage("F", PREFIX "_HLCF", "Failed to close Initialization File '%s'", fileName);
        // never reaches here
    }

    return 0;
}

static void flashSetDiag(vmiosObjectP object, Uns32 diag)
{
    object->diagLevel = diag;
    if(object->diagLevel)
        vmiMessage("I", PREFIX "_DIAG", "Level Set to %d", object->diagLevel);
}

//
// Called to create the Flash model state.
// Allocates space for the Flash memory then maps this directly into simulated
// ram according to the Flash model's port connection.
//
static void flashInit(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          port_nameAddr,
    Addr          fileToLoadAddr,
    Addr          endianAddr
) {
    // get file name from data domain
    memDomainP  domain    = vmirtGetProcessorPhysicalDataDomain(processor);
    const char *portName  = vmirtGetString(domain, port_nameAddr);

    Addr lo, hi;
    Bool isMaster;
    Bool isDynamic;
    memDomainP portDomain = vmipsePlatformPortAttributes(
        processor,
        portName,
        &lo,
        &hi,
        &isMaster,
        &isDynamic
    );
    if (!portDomain || isMaster) {
        vmiMessage("F", PREFIX "_NP", "Failed to find slave port '%s'", portName);
    }

    memDomainP localDomain = vmirtNewDomain("local", 32);

    Uns32 flashSize = hi - lo + 1;
    void *flashBase = malloc(flashSize);
    if (!flashBase) {
        vmiMessage("F", PREFIX "_NP", "Failed to allocate FLASH ram for port %s at 0x"FMT_A08x" to 0x"FMT_A08x" (%u bytes)",
                                       portName, lo, hi, flashSize);
    }
    vmirtMapNativeMemory(localDomain, 0, flashSize-1, flashBase);

    object->domain = portDomain;
    object->lowAddr = lo;
    object->highAddr = hi;
    object->flashBase = flashBase;
    object->flashSize = flashSize;

    //vmirtMapNativeMemory(object->domain, object->lowAddr, object->highAddr, flashBase);
    vmirtAliasMemory(localDomain,
                     object->domain,        // virtual
                     0,
                     flashSize -1,
                     object->lowAddr,
                     NULL);


    installFlashWriteCallback(object);

    vmiMessage("I", PREFIX "_NP", "Allocated FLASH ram for port %s at 0x"FMT_A08x" to 0x"FMT_A08x" (%u bytes)",
                                   portName, lo, hi, flashSize);


    const char *fileName  = vmirtGetString(domain, fileToLoadAddr);
    const char *endian  = vmirtGetString(domain, endianAddr);

    if(fileName) {
        vmiMessage("I", PREFIX "_FN", "Initialization file found '%s' ", fileName);

        loadHexFile(object, fileName, strcmp(endian, "little"));
    }
}


// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "FlashDevice",              // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "ovpworld.org",
        .library = "peripheral",
        .name    = "FlashDevice",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                          // morph callback
    .nextPCCB       = 0,                          // get next instruction address
    .disCB          = 0,                          // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////
    // -------------------   ----------- ------ -----------------
    // Name                  Address     Opaque Callback
    // -------------------   ----------- ------ -----------------
    .intercepts = {
        {"flashInit",        0,          True,  VMIOS_ABI_INT(0, "poaaa", flashInit)},
        {"flashSetDiag",     0,          True,  VMIOS_ABI_INT(0, "p4",    flashSetDiag)},
        {0}
    }
};
