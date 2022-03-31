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
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "hostapi/hostMacros.h"

#if (IMPERAS_WINDOWS==1)
# define lseek _lseeki64
# ifndef ENOMEDIUM
#  define ENOMEDIUM ENODEV
# endif
#endif

#if (IMPERAS_LINUX==1)
# ifndef O_BINARY
# define O_BINARY 0
# endif
#endif


// VMI area includes
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiMessage.h"

#include "../pse/pse.igen.h"
#include "hostapi/impTypes.h"

#include "semihost.h"

#include "drive.h"
#include "delta.h"

#define DRIVE_PREFIX     PREFIX"_DRV"

#define DEBUG_DRIVE        0
#define DIAG_LEVEL_RW      DIAG_MED
#define DIAG_HIGH_DEBUG   (DIAG_HIGH && DEBUG_DRIVE)


#define MAX_DRIVES        1

typedef struct BlockDriverStateS {
    Uns32      number;
    Bool       present;
    Uns8       driveType;
    Uns32      heads;
    Uns32      sectors;
    Uns32      cylinders;
    Int32      fd;
    Uns64      totalSectors;

    Uns32      totalReads;
    Uns32      totalWrites;
    Uns64      totalReadBytes;
    Uns64      totalWriteBytes;
    Uns64      deltaReadBytes;      // reads from the delta FS
    Bool       locked;
    Uns32      translation;
    hashTableP delta;
} BlockDriverState;

typedef struct BlockDriverAIOCBS {
} BlockDriverAIOCB;

//
// TODO: The geometry should be found by peeping in the
// partition table at the start of the disk.
//
BlockDriverState drives[MAX_DRIVES] = {
    { .number=0, .present=False, .driveType=BDRV_TYPE_HD,    .heads=16, .sectors=63, .cylinders=0, .fd=-1},
 /*
    { .number=1, .present=False, .driveType=BDRV_TYPE_HD,    .heads=16, .sectors=128, .cylinders=0, .fd=-1},
    { .number=2, .present=False, .driveType=BDRV_TYPE_CDROM, .heads=1,  .sectors=63,  .cylinders=0, .fd=-1},
    { .number=3, .present=False, .driveType=BDRV_TYPE_HD,    .heads=0,  .sectors=63,  .cylinders=0, .fd=-1}
  */
};
static void initDriverState(BlockDriverStateP bs, Uns32 drive) {
    vmiMessage("I", DRIVE_PREFIX, "initDriverState:");
    bs->number    = drives[drive].number;
    bs->present   = drives[drive].present;
    bs->driveType = drives[drive].driveType;
    bs->heads     = drives[drive].heads;
    bs->sectors   = drives[drive].sectors;
    bs->cylinders = drives[drive].cylinders;
    bs->fd        = drives[drive].fd;
}


static const char *sectorString(Uns64 sector)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "sectorString:");
    // PSE/newlib 64-bit printf format (ll) does not work!
    // Work around this by printing 32-bit halves.
    static char buff[20];
    sprintf(buff, "0x%x%08x", (Uns32)(sector>>32), (Uns32) sector);
    return buff;
}

void bdrvDelta(Uns32 i, Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrvDelta:");
    drives[i].delta = deltaNew(SECT_SIZE);
    if(DIAG_LEVEL_RW)
        vmiMessage("I", DRIVE_PREFIX, "drive:%d enabled Copy On Write.",drives[i].number);
}

BlockDriverStateP bdrv_open(Uns8 drive, const char *filename, Int32 flags, Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_open:");
    static Bool init = False;
    if (!init) {
        init = True;
    }
    BlockDriverStateP bs = calloc(1, sizeof(BlockDriverState));
    initDriverState(bs, drive);
    Uns32 rw        = bs->delta ? O_RDONLY    : O_RDWR | O_BINARY;
    const char *how = bs->delta ? "read-only" : "read-write";
    if(DIAG_LEVEL_RW)
        vmiMessage("I", DRIVE_PREFIX, "Opening drive %d %s %s", bs->number, filename, how);

    if ((bs->fd = open(filename, rw)) >= 0) {
        struct stat st;
        if (fstat(bs->fd, &st) >= 0) {
            bs->present      = True;
            bs->totalSectors = st.st_size / SECT_SIZE;
            bs->cylinders    = bs->totalSectors / (bs->heads * bs->sectors);
            if(DIAG_HIGH_DEBUG)
                vmiMessage("I", DRIVE_PREFIX, "open drive '%s' result:%d (size " FMT_64d ")", filename, bs->fd, (Uns64)st.st_size);
            return bs;
        } else {
            bdrv_close(bs);
            return NULL;
        }
    } else {
        return NULL;
    }
}

void bdrv_close(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_close:");
    close(bs->fd);
}

static Int32 readDiskSectors(BlockDriverStateP bs,  Uns64 sector_num, Uns8 *buf, Uns32 sectors, Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "readDiskSectors");
    Uns64 offset = sector_num * SECT_SIZE;
    Uns64 act    = lseek(bs->fd, offset, SEEK_SET);
    Uns32 bytes  = sectors * SECT_SIZE;

    if(DIAG_HIGH_DEBUG) vmiMessage("I", DRIVE_PREFIX"_DEBUG", "act " FMT_6408x " offset " FMT_6408x " bytes %d", act, offset, bytes);

    if (act == offset) {
        Uns32 rd = read(bs->fd, buf, bytes);
        if(DIAG_HIGH_DEBUG) vmiMessage("I", DRIVE_PREFIX"_DEBUG", "read %d of %d requested bytes", rd, bytes);
        if (rd == bytes) {
            if(DIAG_LEVEL_RW)
                vmiMessage("I", DRIVE_PREFIX,
                    "Reading device:%d sectors:%d  bytes:%d, sector:%s",
                    bs->number,
                    sectors,
                    bytes,
                    sectorString(sector_num)
                );
           return 0;
        }
    }
    return -EINVAL;
}

static Int32 writeDiskSectors(BlockDriverStateP bs, Uns64 sector_num, const Uns8 *buf, Uns32 nb_sectors, Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "writeDiskSectors");
    Uns64 offset = sector_num * SECT_SIZE;
    Uns32 bytes  = nb_sectors * SECT_SIZE;

    Uns64 act = lseek(bs->fd, offset, SEEK_SET);
    if (act != offset) {
        if(DIAG_LEVEL_RW)
            vmiMessage("W", DRIVE_PREFIX,
                       "%s: Write Failed : act " FMT_6408x " offset " FMT_6408x ,__FUNCTION__, act, offset);
        return -EINVAL;
    }
    if(DIAG_LEVEL_RW)
        vmiMessage("I", DRIVE_PREFIX,
            "Writing to device %d sectors:%d  bytes:%d, sector:%s",
            bs->number,
            nb_sectors,
            bytes,
            sectorString(sector_num)
        );

    while(1) {
        Uns32 wr = write(bs->fd, buf, bytes);
        if (wr == -1) {
            return -errno;
        }
        if (wr == bytes) {
            return 0;
        }
        bytes -= wr;
        buf   += wr;
    }
}

Int32 bdrv_read(BlockDriverStateP bs, Uns64 sector_num, Uns8 *buf, Uns32 nb_sectors, Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_read");
    if (bs->fd < 0) {
        return -ENOMEDIUM;
    }

    if (bs->delta) {
        // Have to loop at this level because some sectors could be cached, and some not.
        while (nb_sectors) {
            if (deltaRead(bs->delta, sector_num, buf)) {
                bs->deltaReadBytes += SECT_SIZE;
            } else {
                if (readDiskSectors(bs, sector_num, buf, 1, diag) != 0) {
                    return -EINVAL;
                }
            }
            sector_num++;
            nb_sectors --;
            buf += SECT_SIZE;
        }
    } else {
        if (readDiskSectors(bs, sector_num, buf, nb_sectors, diag) != 0) {
            return -EINVAL;
        }
    }
    bs->totalReads++;
    bs->totalReadBytes += nb_sectors * SECT_SIZE;
    return 0;
}

Int32 bdrv_write(BlockDriverStateP bs, Uns64 sector_num, const Uns8 *buf, Uns32 nb_sectors, Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_write");
    if(bs->delta) {
        while(nb_sectors) {
            if(DIAG_LEVEL_RW) {
                vmiMessage("I", DRIVE_PREFIX,
                    "COW:%d  fd:%d sector:%s",
                    bs->number,
                    bs->fd,
                    sectorString(sector_num)
                 );
            }
            deltaWrite(bs->delta, sector_num, buf);
            sector_num++;
            buf += SECT_SIZE;
            nb_sectors--;
        }
    } else {
        if(DIAG_LEVEL_RW) {
            vmiMessage("I", DRIVE_PREFIX, "write:%d  fd:%d sectors:%d sector:%s",
                bs->number,
                bs->fd,
                nb_sectors,
                sectorString(sector_num)
            );
        }
        Int32 r = writeDiskSectors(bs, sector_num, buf, nb_sectors, diag);
        if(r != 0) {
            vmiMessage("E", DRIVE_PREFIX, "Failed to write to disk image");
            return r;
        }
    }
    bs->totalWrites++;
    bs->totalWriteBytes += (nb_sectors * SECT_SIZE);
    return 0;
}

void bdrv_get_geometry(BlockDriverStateP bs, Uns64 *nb_sectors_ptr)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_get_geometry");
    *nb_sectors_ptr = bs->totalSectors;
}

void bdrv_get_geometry_hint(
    BlockDriverStateP bs,
    Int32 *pcyls,
    Int32 *pheads,
    Int32 *psecs
){
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_get_geometry_hint");
    *pcyls  = bs->cylinders;
    *pheads = bs->heads;
    *psecs  = bs->sectors;
    return;
}


/* Ensure contents are flushed to disk.  */
void bdrv_flush(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_flush");
    // TODO: sync or fsync needs to be semihosted.
    // sync(bs->fd);
}

Int32 bdrv_get_type_hint(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_get_type_hint");
    return bs->driveType;
}

Bool bdrv_media_changed(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_media_changed");
    return 0;
}

Bool bdrv_is_removable(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_is_removable");
    return (bs->driveType != BDRV_TYPE_HD);
}

Bool bdrv_is_read_only(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_is_read_only");
     return (bs->driveType == BDRV_TYPE_CDROM);
}

void bdrv_set_geometry_hint(
    BlockDriverStateP bs,
    Int32 cyls,
    Int32 heads,
    Int32 secs
) {
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_set_geometry_hint");
    bs->heads     = heads;
    bs->sectors   = secs;
    bs->cylinders = cyls;
}

Bool bdrv_is_inserted(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_is_inserted");
    return (bs->fd >= 0);
}

void bdrv_set_translation_hint(BlockDriverStateP bs, Int32 translation)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_set_translation_hint");
    bs->translation = translation;
}

Int32 bdrv_get_translation_hint(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_get_translation_hint");
    return bs->translation;
}

Bool bdrv_is_locked(BlockDriverStateP bs)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_is_locked");
    return bs->locked;
}

void bdrv_set_locked(BlockDriverStateP bs, Bool locked)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrv_set_locked");
    bs->locked = locked;
}

void bdrv_eject(BlockDriverStateP bs, Int32 eject_flag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "drive %d ejected!", bs->number);
}

void bdrv_set_change_cb(BlockDriverStateP bs, void (*change_cb)(void *opaque), void *opaque)
{
    if(DEBUG_DRIVE) vmiMessage("W", DRIVE_PREFIX, "bdrv_set_change_cb unsupported");
}

void bdrvStats(void)
{
    Uns32 i;
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "Drive statistics:");
    vmiPrintf("#    read  write    rbyte delta-rd   wbytes\n");
    for(i= 0; i < MAX_DRIVES; i++) {
        vmiPrintf("%d  %6d %6d",
            drives[i].number,
            drives[i].totalReads,
            drives[i].totalWrites
        );
        vmiPrintf(" " FMT_648d, drives[i].totalReadBytes);
        vmiPrintf(" " FMT_648d, drives[i].deltaReadBytes);
        vmiPrintf(" " FMT_648d "\n", drives[i].totalWriteBytes);
    }
}

void bdrvShutdown(Uns32 diag)
{
    if(DEBUG_DRIVE) vmiMessage("I", DRIVE_PREFIX, "bdrvShutdown");
    Uns32 i;
    for(i= 0; i < MAX_DRIVES; i++) {
        if(drives[i].present && drives[i].fd >= 0) {
            bdrv_close(&drives[i]);
            if(DIAG_LEVEL_RW) {
                vmiMessage("I", DRIVE_PREFIX,
                    "Closing %d fd:%d",
                    drives[i].number,
                    drives[i].fd
                );
            }
        }
    }
}
