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

//
// Issue fatal message if address range is not in the flash memory range
//
void checkOffset(Uns32 offset, Uns32 bytes) {
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
Uns32 getBlockBase(Uns32 offset, Uns32 *size) {

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

Uns32 getSubBlockBase(Uns32 offset, Uns32 *size) {

    checkOffset(offset, 0);

    Uns32 base      = offset & MAIN_SUB_BLOCK_MASK;
    Uns32 blockSize = MAIN_SUB_BLOCK_SIZE;

    if (size) *size = blockSize;
    return base;

}

//
// Initialize the block of flash memory containing offset to all 1's
//
void eraseBlock(Uns32 offset, Bool subBlock) {

    Uns32  blockSize;
    Uns32  blockBase = 0;
    if (subBlock)
        blockBase = getSubBlockBase(offset, &blockSize);
    else
        blockBase = getBlockBase(offset, &blockSize);

    Uns8  *flash     = FLASH        + blockBase;
    Uns8  *end       = flash        + blockSize;

    // Make sure we do not overflow the flash memory array
    if (end >= (FLASH + FLASH_SIZE)) {
        end = FLASH + FLASH_SIZE;
    }

    while (flash < end) {
        *(flash++) = 0xff;
    }
}

void printData(
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
void writeArray(Uns8 *to, Uns8 *from, Uns32 bytes) {
    while (bytes--) {
        *(to++) = *(from++);
    }
}

//
// program data into array (programming can only cause 1->0 transitions
//
void programArray(Uns8 *to, Uns8 *old, Uns32 bytes) {
    while (bytes--) {
        *(to++) &= *(old++);
    }
}

//
// read data from array
//
void readArray(Uns8 *to, Uns8 *from, Uns32 bytes) {
    while (bytes--) {
        *(to++) = *(from++);
    }
}

//
// Load a binary image file into flash memory
//
void loadImageFile(const char *fileName, Uns32 offset) {

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

            if (ferror(fp)) {

                bhmMessage(
                    "F", PREFIX "_IFE",
                    "Error reading Flash image file '%s': %s",
                    fileName,
                    strerror(errno)
                );
                // not reached

            } else {

                if(PSE_DIAG_LOW)
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
// Load a binary image file into flash memory
//
void saveImageFile(const char *fileName, Uns32 offset, Uns32 size) {

    if (offset >= FLASH_SIZE) {

        bhmMessage(
            "F", PREFIX "_OOR",
            "Image file offset %d out of range of Flash memory size %d",
            offset,
            FLASH_SIZE
        );

    } else if ((offset+size) >= FLASH_SIZE) {

        bhmMessage(
            "F", PREFIX "_OSR",
            "Image file offset + size %d out of range of Flash memory size %d",
            offset+size,
            FLASH_SIZE
        );

    } else {

        FILE *fp = fopen(fileName, "wb");

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
            Uns32 bytesWritten = fwrite(FLASH+offset, 1, size, fp);

            if (ferror(fp)) {

                bhmMessage(
                    "F", PREFIX "_IFE",
                    "Error writting Flash image file '%s': %s",
                    fileName,
                    strerror(errno)
                );
                // not reached

            } else if(PSE_DIAG_LOW) {
                bhmMessage(
                    "I", PREFIX "_IFR",
                    "%d bytes saved to Flash image file '%s' from offset 0x%x",
                    bytesWritten,
                    fileName,
                    offset
                );
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
// Parse fileName string of filename[@offset][:size][,filename[@offset][:size]]...
// Size only used for saving image file, ignored when loading.
//
void processImageFiles(const char *fileNames, Bool loadImage) {

    char *next;
    char *fileName = strdup(fileNames);

    while (fileName && *fileName) {

        // look for multiple file names separated by ','
        next = strchr(fileName, ',');
        if (next) {
            // separate file names by replacing ',' delimiter with \0
            *(next++) = '\0';
        }
        unsigned int offset = 0;
        unsigned int size   = FLASH_SIZE;

        // Look for an offset separated by '@'
        char *offsetStr = strchr(fileName, '@');
        // Look for a size separated by ':'
        char *sizeStr = strchr(fileName, ':');

        if (offsetStr) {
            // separate file name and offset by replacing '@' delimiter with \0
            *(offsetStr++) = '\0';
        }
        if (sizeStr) {
            // separate file name and offset by replacing ':' delimiter with \0
            *(sizeStr++) = '\0';
        }

        if (offsetStr) {
            char *end;
            offset = strtoul(offsetStr, &end, 0);
            size   = FLASH_SIZE-offset; // maximum is reduced
            if (!end || *end != '\0') {
                bhmMessage(
                    "F", PREFIX"_IFS",
                    "Invalid offset '%s' in image file specification: '%s'\n",
                    offsetStr,
                    fileNames
                );
            }
        }

        if (sizeStr) {
            char *end;
            size = strtoul(sizeStr, &end, 0);
            if (!end || *end != '\0') {
                bhmMessage(
                    "F", PREFIX"_IFS",
                    "Invalid size '%s' in image file specification: '%s'",
                    sizeStr,
                    fileNames
                );
            }
        }

        if(loadImage) {
            // Load this file
            loadImageFile(fileName, offset);
        } else {
            // save image to this file
            saveImageFile(fileName, offset, size);
        }

        // check next name, if specified
        fileName = next;
    }
}


// NOTE: Replaced with processImageFiles()
#if 0
//
// Parse fileName string of filename[@offset][,filename[@offset]]...
//
void loadImageFiles(const char *fileNamesIn) {

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
#endif
//
// Initialize flash memory to all 1's
//
void initFlashMemory() {

    Uns32 blockOffset;
    Uns32 firstMainBlock  = FIRST_MAIN_BLOCK (FLASH_SIZE);
    Uns32 lastMainBlock   = LAST_MAIN_BLOCK  (FLASH_SIZE);
    Uns32 firstParamBlock = FIRST_PARAM_BLOCK(FLASH_SIZE);
    Uns32 lastParamBlock  = LAST_PARAM_BLOCK (FLASH_SIZE);

    // Erase Main Blocks (i
    for (
         blockOffset =  firstMainBlock;
         blockOffset <= lastMainBlock;
         blockOffset += MAIN_BLOCK_SIZE
    ) {
        eraseBlock(blockOffset, False);
    }

    // Erase Parameter Blocks (if they exist)
    if(PARAM_BLOCK_SIZE) {
        for (
             blockOffset =  firstParamBlock;
             blockOffset <= lastParamBlock;
             blockOffset += PARAM_BLOCK_SIZE
        ) {
            eraseBlock(blockOffset, False);
        }
    }
}

//
// Return n such that value = 2^^n
// Value must be a power of 2
//
Uns32 log2Int(Uns32 value) {
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

