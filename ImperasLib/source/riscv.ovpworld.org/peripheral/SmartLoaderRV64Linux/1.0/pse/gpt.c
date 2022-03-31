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

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "gpt.h"

#include "pse.igen.h"

#define PREFIX "SMARTLOADER_GPT"
//
// Utilities to access a disk image formatted with a GUID Partition Table
// (see https://en.wikipedia.org/wiki/GUID_Partition_Table)
//

// GUID Partition Table Header is in LBA 1
#define PTH_LBA 1

// PTH Signature ("EFI PART")
#define PTH_SIG 0x5452415020494645ULL

// Only supports images with 512 byte Logical Blocks
#define LBA_SIZE 512
// GUID size in bytes
#define GUID_SIZE sizeof(guidT)

// GUID string size (include room for 2 chars/byte plus 4 hyphens and terminating NULL)
#define GUID_STRING_SIZE ((2 * (GUID_SIZE)) + 5)

//
// Partition table header struct
// see https://en.wikipedia.org/wiki/GUID_Partition_Table#Partition_table_header_(LBA_1)
//
typedef struct pthS {
    Uns64   signature;
    Uns32   revision;
    Uns32   headerSize;
    Uns32   crc32;
    Uns32   reserved1;
    Uns64   currentLBA;
    Uns64   backupLBA;
    Uns64   firstUsableLBA;
    Uns64   lastUsableLBA;
    guidT   diskGUID;
    Uns64   firstPELBA;
    Uns32   numPE;
    Uns32   sizeofPE;
    Uns32   crc32PEArray;
} pthT, *pthP;

//
// Partition table entry struct
// see https://en.wikipedia.org/wiki/GUID_Partition_Table#Partition_entries_(LBA_2%E2%80%9333)
//
typedef struct peS {
    guidT   typeGUID;
    guidT   uniqueGUID;
    Uns64   firstLBA;
    Uns64   lastLBA;
    Uns64   flags;
    char    name[72];
} peT, *peP;

static Bool seekLBA(FILE *image, Uns32 lbaNum) {
    Uns32 position = LBA_SIZE * lbaNum;
    Bool  ok       = False;

    if (fseek(image, position, SEEK_SET) == -1) {

        bhmMessage("E", PREFIX,
            "Error attempting to fseek to position %d: %s",
            position, strerror(errno));

    } else {

        ok = True;

    }

    return ok;
}

static Bool readData(FILE *image, void *data, Uns32 bytes) {
    Bool ok = False;

    if (fread(data, bytes, 1, image) != 1) {
        bhmMessage("E", PREFIX, "Unable to read %d bytes from image file", bytes);
    } else {
        ok = True;
    }

    return ok;
}

static Bool readLBA(FILE *image, Uns32 lbaNum, void *data, Uns32 bytes) {
    Bool ok = False;

    if (!seekLBA(image, lbaNum)) {
        // Error message issued by seekLBA
    } else if (!readData(image, data, bytes)) {
        // Error message issued by readData
    } else {
        ok = True;
    }

    return ok;
}

static Bool readPTH(FILE *image, pthP pth) {
    Bool ok = False;

    if (!readLBA(image, PTH_LBA, pth, sizeof(*pth))) {

        // Error message issued by readLBA()

    } else if (pth->signature != PTH_SIG) {

        bhmMessage("E", PREFIX,
            "Invalid GUID Partition Table Header signature: 0x%llx, "
            "expected 0x%llx",
            pth->signature, PTH_SIG
        );

    } else {

        ok = True;

    }

    return ok;
}

static Bool loadMemory(FILE *image, Addr loadAddress, Uns64 bytes) {
    char  buf[LBA_SIZE];
    Addr  dest  = loadAddress;

    while (bytes) {
        Uns32 thisAccess = (bytes > sizeof(buf)) ? sizeof(buf) : bytes;

        if (fread(buf, thisAccess, 1, image) != 1) {

            bhmMessage("E", PREFIX, "Unable to read %d bytes", thisAccess);
            break;

        } else if (!ppmWriteAddressSpace(handles.mport, dest, thisAccess, buf)){

            bhmMessage(
                "E", PREFIX,
                "Unable to write to simulated memory at 0x%08llx",
                dest
            );
            break;

        }

        dest  += thisAccess;
        bytes -= thisAccess;
    }

    return bytes == 0;
}

static Bool loadPartition(FILE *image, peP pe, Addr loadAddress) {
    Int64 bytes = (pe->lastLBA - pe->firstLBA + 1) * LBA_SIZE;
    Bool  ok    = False;

    if (bytes < 0) {

        bhmMessage("E", PREFIX,
            "Invalid LBA range on partition %s: %lld:%lld",
            pe->name, pe->firstLBA, pe->lastLBA
        );


    } else if (!seekLBA(image, pe->firstLBA)) {

        // Error message issued by seekLBA

    } else if (!loadMemory(image, loadAddress, bytes)) {

        // Error message issued by loadMemory

    } else {

        // Data read successfully
        ok = True;

    }

    return ok;
}

static Bool guidsMatch(guidP g1, guidP g2) {
    return memcmp(g1, g2, sizeof(guidT)) == 0;
}

//
// Convert a GUID to a standard string description
// - returns pointer to standard buffer so previous value rashed on each call
//
static const char *guidToStr(guidP guid) {
    static char guidBuf[GUID_STRING_SIZE];

    snprintf(guidBuf, sizeof(guidBuf),
            "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            guid->timeLow, guid->timeMid, guid->timeHi,
            guid->clkSeqHi, guid->clkSeqLow,
            guid->node[0], guid->node[1], guid->node[2],
            guid->node[3], guid->node[4], guid->node[5]
    );

    return guidBuf;
}

//
// Read a partition from a GPT disk image file into simulated memory
// - Search for a partition in the disk image file whose type matches partitionType
// - Read the partition into simulated memory at loadAddress
// Return 1 on success, 0 on error
//
Bool readPartition(const char *imageFN, guidP partitionType, Addr loadAddress) {
    pthT  pth;
    FILE *image = fopen(imageFN, "r");
    Bool  ok    = False;

    if (!image) {

        bhmMessage("E", PREFIX,
            "Unable to open image file '%s': %s",
            imageFN, strerror(errno)
        );

    } else if (!readPTH(image, &pth)) {

        bhmMessage("E", PREFIX,
            "Image file '%s' is not a valid GPT image file (is it compressed?)",
            imageFN
        );

    } else {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX, "Image file '%s':", imageFN);
            bhmPrintf(
                "\tnumPE=%d, firstPELBA=%lld, sizeofPE=%d, diskGUID=%s\n",
                pth.numPE, pth.firstPELBA, pth.sizeofPE, guidToStr(&pth.diskGUID)
            );
        }

        if (pth.sizeofPE != sizeof(peT)) {
            bhmMessage("E", PREFIX,
                "Invalid PE size %d, expected %ld",
                pth.sizeofPE, sizeof(peT)
            );
        }

        if (seekLBA(image, pth.firstPELBA)) {
            Uns32 i;

            for (i = 0; i < pth.numPE; i++) {
                peT pe;

                if (!readData(image, &pe, sizeof(pe))) {
                    // Error message issued by readData
                    break;
                }

                if (pe.firstLBA == 0) {
                    // Skip empty Partition Entries
                    continue;
                }

                Bool match = guidsMatch(partitionType, &pe.typeGUID);

                if (PSE_DIAG_HIGH || (PSE_DIAG_MEDIUM && match)) {
                    bhmPrintf("\tPartition Entry %d: ", i);
                    bhmPrintf("firstLBA=%-8lld lastLBA=%-8lld ", pe.firstLBA, pe.lastLBA);
                    bhmPrintf("typeGUID=%s, ", guidToStr(&pe.typeGUID));
                    bhmPrintf("uniqueGUID=%s, name='%s'\n", guidToStr(&pe.uniqueGUID), pe.name);
                }

                if (match) {
                    ok = loadPartition(image, &pe, loadAddress);
                    break;
                }
            }
        }
    }

    return ok;
}
