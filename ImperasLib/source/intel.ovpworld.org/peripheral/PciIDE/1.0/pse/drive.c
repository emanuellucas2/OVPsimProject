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

// obtain ENOMEDIUM
#define __LINUX_ERRNO_EXTENSIONS__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"

#include "drive.h"

#define PREFIX            "IDE_DRV"
#define DIAG_LEVEL_RW     4
#define MAX_DRIVES        4

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
    Bool       locked;
    Uns32      translation;
} BlockDriverState;

typedef struct BlockDriverAIOCBS {
} BlockDriverAIOCB;

static Uns32 diag;

//
// TODO: The geometry should be found by peeping in the
// partition table at the start of the disk.
//
BlockDriverState drives[MAX_DRIVES] = {
   // #    present  type             hds   sects  cyls   fd
    { 0,   False,   BDRV_TYPE_HD,    16,    63,    0,    -1},
    { 1,   False,   BDRV_TYPE_HD,    16,    128,   0,    -1},
    { 2,   False,   BDRV_TYPE_CDROM, 1,     63,    0,    -1},
    { 3,   False,   BDRV_TYPE_HD,    0,     63,    0,    -1}
};


////////////////////////////////////////////////////////////////////////////////
// INTERCEPTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// fstat64() and lseek64() are supported by PSE semi-hosting intercepts.
// Define these here for now as they are not in the standard PSE/newlib toolchain.
//
struct stat64 {
    Uns64 st_size;
    Uns32 st_mode;
    Uns32 st_blksize;
    Uns32 st_blocks;
    Uns32 st_atime;
    Uns32 st_mtime;
    Uns32 st_ctime;
};


FUNCTOHOST(int, fstat64, int fd, struct stat64 *s)

FUNCTOHOST(_off64_t, lseek64, int fd, _off64_t offset, int whence)

////////////////////////////////////////////////////////////////////////////////
// PRIMITIVE DISK OPERATIONS (WRAPPED BY RECORD/REPLAY)
////////////////////////////////////////////////////////////////////////////////

//
// This enumerates primitive disk operations
//
typedef enum drEventTypeE {
    DR_OPEN = 1,        // open() call
    DR_CLOSE,           // close() call
    DR_READ,            // read() call
    DR_READ_DATA,       // read() data block
    DR_WRITE,           // write() call
    DR_FSTAT64,         // fstat64() call
    DR_FSTAT64_DATA,    // fstat64() data block
    DR_LSEEK64,         // lseek64() call
} drEventType;

//
// These indicate whether record or replay mode is active
//
static Bool recording;
static Bool replaying;

//
// Record an event of a specific type
//
static void drRecordEventOfType(drEventType type, Uns32 bytes, void *data) {
    bhmRecordEvent(type, bytes, data);
}

//
// Replay an event of a required type
//
static void drReplayEventOfType(drEventType type, Uns32 bytes, void *data) {

    drEventType actualType;
    Int32       actualBytes = bhmReplayEvent(NULL, &actualType, bytes, data);

    if(actualBytes<0) {
        bhmMessage("F", PREFIX,
            "Replay file ended: no further replay is possible"
        );
    } else if(type!=actualType) {
        bhmMessage("F", PREFIX,
            "Unexpected record type (required=%u, actual=%u)",
            type,
            actualType
        );
    } else if(bytes!=actualBytes) {
        bhmMessage("F", PREFIX,
            "Unexpected record size (required=%u, actual=%u)",
            bytes,
            actualBytes
        );
    }
}

//
// open() call wrapped by record/replay
//
static Int32 drOpen(const char *fileName, Int32 flags) {

    Int32 result;

    if(replaying) {
        drReplayEventOfType(DR_OPEN, sizeof(result), &result);
    } else {
        result = open(fileName, flags);
        if(recording) {
            drRecordEventOfType(DR_OPEN, sizeof(result), &result);
        }
    }

    return result;
}

//
// close() call wrapped by record/replay
//
static Int32 drClose(Int32 fd) {

    Int32 result;

    if(replaying) {
        drReplayEventOfType(DR_CLOSE, sizeof(result), &result);
    } else {
        result = close(fd);
        if(recording) {
            drRecordEventOfType(DR_CLOSE, sizeof(result), &result);
        }
    }

    return result;
}

//
// read() call wrapped by record/replay
//
static Uns32 drRead(Int32 fd, void *buf, Uns32 count) {

    Uns32 result;

    if(replaying) {
        drReplayEventOfType(DR_READ, sizeof(result), &result);
        if(result && (result!=-1)) {
            drReplayEventOfType(DR_READ_DATA, result, buf);
        }
    } else {
        result = read(fd, buf, count);
        if(recording) {
            drRecordEventOfType(DR_READ, sizeof(result), &result);
            if(result && (result!=-1)) {
                drRecordEventOfType(DR_READ_DATA, result, buf);
            }
        }
    }

    return result;
}

//
// write() call wrapped by record/replay
//
static Uns32 drWrite(Int32 fd, const void *buf, Uns32 count) {

    Uns32 result;

    if(replaying) {
        drReplayEventOfType(DR_WRITE, sizeof(result), &result);
        // contents of buf are unused in replay mode
    } else {
        result = write(fd, buf, count);
        if(recording) {
            drRecordEventOfType(DR_WRITE, sizeof(result), &result);
        }
    }

    return result;
}

//
// fstat64() call wrapped by record/replay
//
static Int32 drFStat64(Int32 fd, struct stat64 *s) {

    Int32 result;

    if(replaying) {
        drReplayEventOfType(DR_FSTAT64,      sizeof(result), &result);
        drReplayEventOfType(DR_FSTAT64_DATA, sizeof(*s),     s);
    } else {
        result = fstat64(fd, s);
        if(recording) {
            drRecordEventOfType(DR_FSTAT64,      sizeof(result), &result);
            drRecordEventOfType(DR_FSTAT64_DATA, sizeof(*s),     s);
        }
    }

    return result;
}

//
// lseek64() call wrapped by record/replay
//
static Uns64 drLSeek64(Int32 fd, Uns64 offset, Int32 whence) {

    Uns64 result;

    if(replaying) {
        drReplayEventOfType(DR_LSEEK64, sizeof(result), &result);
    } else {
        result = lseek64(fd, offset, whence);
        if(recording) {
            drRecordEventOfType(DR_LSEEK64, sizeof(result), &result);
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
// HIGHER-LEVEL DISK OPERATIONS
////////////////////////////////////////////////////////////////////////////////

static const char *sectorString(Uns64 sector)
{
    // PSE/newlib 64-bit printf format (ll) does not work!
    // Work around this by printing 32-bit halves.
    static char buff[20];
    sprintf(buff, "0x%x%08x", (Uns32)(sector>>32), (Uns32) sector);
    return buff;
}

BlockDriverStateP bdrv_open(Uns8 drive, const char *filename, Int32 flags)
{
    static Bool init = False;
    if (!init) {
        init = True;
        diag = bhmGetDiagnosticLevel();
        recording = bhmRecordStart();
        replaying = bhmReplayStart();
    }
    BlockDriverStateP bs = &drives[drive];
    Uns32 rw        = O_RDWR;
    const char *how = "read-write";

    if(diag & DIAG_LEVEL_RW)
        bhmMessage("I", PREFIX, "Opening drive %d %s %s", bs->number, filename, how);

    if ((bs->fd = drOpen(filename, rw)) >= 0) {
        struct stat64 st;
        if (drFStat64(bs->fd, &st) >= 0) {
            bs->present      = True;
            bs->totalSectors = st.st_size / SECT_SIZE;
            bs->cylinders    = bs->totalSectors / (bs->heads * bs->sectors);
            if(diag & DIAG_LEVEL_RW)
                bhmMessage("I", PREFIX, "open drive %s result:%d", filename, bs->fd);
            return bs;
        } else {
            bdrv_close(bs);
            return NULL;
        }
    } else {
        return NULL;
    }
}

void bdrv_restore(void)
{
    recording = bhmRecordStart();
    replaying = bhmReplayStart();
}

void bdrv_close(BlockDriverStateP bs)
{
    drClose(bs->fd);
}

static Int32 readDiskSectors(BlockDriverStateP bs,  Uns64 sector_num, Uns8 *buf, Uns32 sectors)
{
    Uns64 offset = sector_num * SECT_SIZE;
    Uns64 act    = drLSeek64(bs->fd, offset, SEEK_SET);
    Uns32 bytes  = sectors * SECT_SIZE;

    if (act == offset) {
        Uns32 rd = drRead(bs->fd, buf, bytes);
        if (rd == bytes) {
            if(diag & DIAG_LEVEL_RW)
                bhmMessage("I", PREFIX,
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

static Int32 writeDiskSectors(BlockDriverStateP bs, Uns64 sector_num, const Uns8 *buf, Uns32 nb_sectors)
{
    Uns64 offset = sector_num * SECT_SIZE;
    Uns32 bytes  = nb_sectors * SECT_SIZE;

    Uns64 act = drLSeek64(bs->fd, offset, SEEK_SET);
    if (act != offset) {
        return -EINVAL;
    }
    if(diag & DIAG_LEVEL_RW)
        bhmMessage("I", PREFIX,
            "Writing to device %d sectors:%d  bytes:%d, sector:%s",
            bs->number,
            nb_sectors,
            bytes,
            sectorString(sector_num)
        );

    while(1) {
        Uns32 wr = drWrite(bs->fd, buf, bytes);
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

Int32 bdrv_read(BlockDriverStateP bs, Uns64 sector_num, Uns8 *buf, Uns32 nb_sectors)
{
    if (bs->fd < 0) {
        return -ENOMEDIUM;
    }

    if (readDiskSectors(bs, sector_num, buf, nb_sectors) != 0) {
        return -EINVAL;
    }

    bs->totalReads++;
    bs->totalReadBytes += nb_sectors * SECT_SIZE;
    return 0;
}

Int32 bdrv_write(BlockDriverStateP bs, Uns64 sector_num, const Uns8 *buf, Uns32 nb_sectors)
{
    if(diag & DIAG_LEVEL_RW) {
        bhmMessage("I", PREFIX, "write:%d  fd:%d sectors:%d sector:%s",
            bs->number,
            bs->fd,
            nb_sectors,
            sectorString(sector_num)
        );
    }
    Int32 r = writeDiskSectors(bs, sector_num, buf, nb_sectors);
    if(r != 0) {
        bhmMessage("E", PREFIX, "Failed to write to disk image");
        return r;
    }

    bs->totalWrites++;
    bs->totalWriteBytes += (nb_sectors * SECT_SIZE);
    return 0;
}

void bdrv_get_geometry(BlockDriverStateP bs, Uns64 *nb_sectors_ptr)
{
    *nb_sectors_ptr = bs->totalSectors;
}

void bdrv_get_geometry_hint(
    BlockDriverStateP bs,
    Int32 *pcyls,
    Int32 *pheads,
    Int32 *psecs
){
    *pcyls  = bs->cylinders;
    *pheads = bs->heads;
    *psecs  = bs->sectors;
    return;
}


/* Ensure contents are flushed to disk.  */
void bdrv_flush(BlockDriverStateP bs)
{
    // TODO: sync or fsync needs to be semihosted.
    // sync(bs->fd);
}

Int32 bdrv_get_type_hint(BlockDriverStateP bs)
{
    return bs->driveType;
}

Bool bdrv_media_changed(BlockDriverStateP bs)
{
    return 0;
}

Bool bdrv_is_removable(BlockDriverStateP bs)
{
    return (bs->driveType != BDRV_TYPE_HD);
}

Bool bdrv_is_read_only(BlockDriverStateP bs)
{
     return (bs->driveType == BDRV_TYPE_CDROM);
}

void bdrv_set_geometry_hint(
    BlockDriverStateP bs,
    Int32 cyls,
    Int32 heads,
    Int32 secs
) {
    bs->heads     = heads;
    bs->sectors   = secs;
    bs->cylinders = cyls;
}

Bool bdrv_is_inserted(BlockDriverStateP bs)
{
    return (bs->fd >= 0);
}

void bdrv_set_translation_hint(BlockDriverStateP bs, Int32 translation)
{
    bs->translation = translation;
}

Int32 bdrv_get_translation_hint(BlockDriverStateP bs)
{
    return bs->translation;
}

Bool bdrv_is_locked(BlockDriverStateP bs)
{
    return bs->locked;
}

void bdrv_set_locked(BlockDriverStateP bs, Bool locked)
{
    bs->locked = locked;
}

void bdrv_eject(BlockDriverStateP bs, Int32 eject_flag)
{
    bhmMessage("I", PREFIX, "drive %d ejected!", bs->number);
}

void bdrv_set_change_cb(BlockDriverStateP bs, void (*change_cb)(void *opaque), void *opaque)
{
    bhmMessage("W", PREFIX, "bdrv_set_change_cb unsupported");
}

void bdrvStats(void)
{
    Uns32 i;
    bhmMessage("I", PREFIX, "Drive statistics:");
    bhmPrintf("#    read  write    rbyte    wbytes\n");
    for(i= 0; i < MAX_DRIVES; i++) {
        bhmPrintf("%d  %6d %6d",
            drives[i].number,
            drives[i].totalReads,
            drives[i].totalWrites
        );
        bhmPrintf(" %8llu", drives[i].totalReadBytes);
        bhmPrintf(" %8llu\n", drives[i].totalWriteBytes);
    }
}

void bdrvShutdown(void)
{
    // this function is only called at the end of simulation
    replaying = False;

    Uns32 i;
    for(i= 0; i < MAX_DRIVES; i++) {
        if(drives[i].present && drives[i].fd >= 0) {
            bdrv_close(&drives[i]);
            if(diag & DIAG_LEVEL_RW) {
                bhmMessage("I", PREFIX,
                    "Closing %d fd:%d",
                    drives[i].number,
                    drives[i].fd
                );
            }
        }
    }

    bhmRecordFinish();
    bhmReplayFinish();
}
