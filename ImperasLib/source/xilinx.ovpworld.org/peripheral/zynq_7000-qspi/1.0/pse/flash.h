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
#ifndef FLASH_COMMON_H_
#define FLASH_COMMON_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pse.igen.h"

#ifndef PREFIX
#define PREFIX "FLASH"
#endif
#ifndef FLASH_SIZE
#define FLASH_SIZE BPAXI_ABM_FLASH_SIZE
#endif

// Pointer to simulator allocated flash memory space
#define FLASH ((Uns8 *)handles.bpAXI)


#define GET_CMD(_c)             (_c & 0xff)
#define GET_DATA8(_d)           ((_d >> 8) & 0x000000ff)
#define GET_DATA16(_d)          ((_d >> 8) & 0x0000ffff)
#define GET_DATA24(_d)          ((_d >> 8) & 0x00ffffff)

// order of the bytes in the address following the data
#define GET_ADDR24(_d)          (((_d & 0x0000ff00) <<  8) | \
                                 ((_d & 0x00ff0000) >>  8) | \
                                 ((_d & 0xff000000) >> 16))

// Micron Flash
// Blocks are organized as 256 x 64KB blocks
#define MAIN_SUB_BLOCK_SIZE     0x00001000
#define MAIN_SUB_BLOCK_MASK     (~(MAIN_SUB_BLOCK_SIZE-1))
#define MAIN_BLOCK_SIZE         0x00010000
#define MAIN_BLOCK_MASK         (~(MAIN_BLOCK_SIZE-1))
#define PARAM_BLOCK_SIZE        0x00000000
#define PARAM_BLOCK_MASK        (~(PARAM_BLOCK_SIZE-1))

// Macros to calculate first/last main/param block offsets
// Only "Bottom Configuration" supported, where last main block is used as parameter blocks
#define FIRST_PARAM_BLOCK(_S)  (0)
#define FIRST_MAIN_BLOCK(_S)   (((_S)-1) & PARAM_BLOCK_MASK)
#define LAST_PARAM_BLOCK(_S)   ((FIRST_MAIN_BLOCK(_S)-1) & PARAM_BLOCK_MASK)
#define LAST_MAIN_BLOCK(_S)    (((_S)-1) & MAIN_BLOCK_MASK)


//
// Issue fatal message if address range is not in the flash memory range
//
void checkOffset(Uns32 offset, Uns32 bytes);

//
// Return the block base offset and optionally the block size
// for a Flash memory offset (Offset may be in either
// a main block or a parameter block)
//
Uns32 getBlockBase(Uns32 offset, Uns32 *size);
Uns32 getSubBlockBase(Uns32 offset, Uns32 *size);

//
// Initialize the block of flash memory containing offset to all 1's
//
void eraseBlock(Uns32 offset, Bool subBlock);

void printData(
    Uns32        offset,
    const void  *value,
    Uns32        bytes,
    const char  *type
);
//
// write data to array
//
void writeArray(Uns8 *to, Uns8 *from, Uns32 bytes);

//
// program data into array (programming can only cause 1->0 transitions
//
void programArray(Uns8 *to, Uns8 *old, Uns32 bytes);

//
// read data from array
//
void readArray(Uns8 *to, Uns8 *from, Uns32 bytes);

//
// Load a binary image file into flash memory
//
void loadImageFile(const char *fileName, Uns32 offset);

//
// Parse fileName string of filename[@offset][,filename[@offset]]...
//
void loadImageFiles(const char *fileNamesIn);

//
// Parse fileName string of filename[@offset][:size][,filename[@offset][:size]]...
// Size only used for saving image file, ignored when loading.
//
void processImageFiles(const char *fileNames, Bool loadImage);


//
// Initialize flash memory to all 1's
//
void initFlashMemory(void);

//
// Return n such that value = 2^^n
// Value must be a power of 2
//
Uns32 log2Int(Uns32 value);

#endif /* FLASH_COMMON_H_ */
