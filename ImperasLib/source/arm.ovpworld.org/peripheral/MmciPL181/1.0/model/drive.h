/*
 * Copyright (c) 2003-2004 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
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
#ifndef DRIVE_H
#define DRIVE_H

#define BDRV_O_RDONLY      0x0000
#define BDRV_O_RDWR        0x0002
#define BDRV_O_ACCESS      0x0003
#define BDRV_O_CREAT       0x0004 /* create an empty file */
#define BDRV_O_SNAPSHOT    0x0008 /* open the file read only and save writes in a snapshot */
#define BDRV_O_FILE        0x0010 /* open as a raw file (do not try to
                                     use a disk image format on top of
                                     it (default for
                                     bdrv_file_open()) */

#define BDRV_TYPE_HD       0
#define BDRV_TYPE_CDROM    1
#define BDRV_TYPE_FLOPPY   2

#define BIOS_ATA_TRANSLATION_AUTO   0
#define BIOS_ATA_TRANSLATION_NONE   1
#define BIOS_ATA_TRANSLATION_LBA    2
#define BIOS_ATA_TRANSLATION_LARGE  3
#define BIOS_ATA_TRANSLATION_RECHS  4

#define SECT_SIZE   512

typedef struct BlockDriverStateS *BlockDriverStateP, **BlockDriverStatePP;
typedef struct BlockDriverAIOCBS *BlockDriverAIOCBP, **BlockDriverAIOCBPP;

void               bdrv_delete(BlockDriverStateP bs);
BlockDriverStateP  bdrv_open(Uns8 drive, const char *filename, Int32 flags, Uns32 diag);
void               bdrv_close(BlockDriverStateP bs);

Int32              bdrv_read(BlockDriverStateP bs, Uns64 sector_num, Uns8 *buf, Uns32 nb_sectors, Uns32 diag);
Int32              bdrv_write(BlockDriverStateP bs, Uns64 sector_num, const Uns8 *buf, Uns32 nb_sectors, Uns32 diag);

Int32              bdrv_truncate(BlockDriverStateP bs, Int64 offset);
Int64              bdrv_getlength(BlockDriverStateP bs);
void               bdrv_get_geometry(BlockDriverStateP bs, Uns64 *nb_sectors_ptr);
Int32              bdrv_commit(BlockDriverStateP bs);
void               bdrv_set_boot_sector(BlockDriverStateP bs, const Uns8 *data, Int32 size);

/* Ensure contents are flushed to disk.  */
void bdrv_flush(BlockDriverStateP bs);


void bdrv_set_geometry_hint(BlockDriverStateP bs,
                            Int32 cyls, Int32 heads, Int32 secs);

void bdrv_set_translation_hint(BlockDriverStateP bs, Int32 translation);

void bdrv_get_geometry_hint(BlockDriverStateP bs,
                            Int32 *pcyls, Int32 *pheads, Int32 *psecs);

Int32 bdrv_get_type_hint(BlockDriverStateP bs);
Int32 bdrv_get_translation_hint(BlockDriverStateP bs);

Bool bdrv_is_removable(BlockDriverStateP bs);
Bool bdrv_is_read_only(BlockDriverStateP bs);
Bool bdrv_is_inserted(BlockDriverStateP bs);
Bool bdrv_media_changed(BlockDriverStateP bs);
Bool bdrv_is_locked(BlockDriverStateP bs);

void bdrv_set_locked(BlockDriverStateP bs, Bool locked);
void bdrv_eject(BlockDriverStateP bs, Int32 eject_flag);
void bdrv_set_change_cb(BlockDriverStateP bs,
                        void (*change_cb)(void *opaque), void *opaque);
void bdrv_get_format(BlockDriverStateP bs, char *buf, Int32 buf_size);

void bdrvStats(void);
void bdrvShutdown(Uns32 diag);
void bdrvDelta(Uns32 i, Uns32 diag);

#endif /*DRIVE_H*/
