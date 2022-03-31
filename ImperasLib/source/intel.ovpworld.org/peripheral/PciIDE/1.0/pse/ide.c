/*
 * QEMU IDE disk and CD-ROM Emulator
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
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

// obtain ENOMEDIUM
#define __LINUX_ERRNO_EXTENSIONS__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pse.igen.h"

#include "pci.h"

#include "drive.h"
#include "cdrom.h"

#ifndef USED
    #define USED     __attribute__((used))
#endif

#define PREFIX               "IDE"
#define LABEL                "IDE MODEL"
#define VERSION              "1.0"

#define DRIVE_NAME_ATTR      "Drive%dName"
#define DRIVE_DELTA_ATTR     "Drive%dDelta"

#define MIN(_a,_b)   (((_a) < (_b)) ? (_a) : (_b))

#define USE_DMA_CDROM

#include "ideConstants.h"

typedef struct IDEStateS *IDEStateP;
typedef struct BMDMAStateS *BMDMAStateP;

typedef void BlockDriverCompletionFunc(BMDMAStateP bm, Int32 ret);
typedef void (*EndTransferFunc)(IDEStateP s);

//
// NOTE: IDEState represents one IDE channel
//
typedef struct IDEStateS {
    /* ide config */
    Bool is_cdrom;
    Bool is_cf;
    Int32 cylinders, heads, sectors;
    Int64 nb_sectors;
    Int32 mult_sectors;
    Int32 identify_set;
    Uns16 identify_data[256];

    Uns32 irqNumber;
    Uns8  ifn;

    BMDMAStateP bmdma;    // ptr to dma ch
    Int32 drive_serial;
    /* ide regs */
    Uns8 feature;
    Uns8 error;
    Uns32 nsector;
    Uns8 sector;
    Uns8 lcyl;
    Uns8 hcyl;
    /* other part of tf for lba48 support */
    Uns8 hob_feature;
    Uns8 hob_nsector;
    Uns8 hob_sector;
    Uns8 hob_lcyl;
    Uns8 hob_hcyl;

    Uns8 select;
    Uns8 status;

    /* 0x3f6 command, only meaningful for drive 0 */
    Uns8 cmd;
    /* set for lba48 access */
    Uns8 lba48;
    /* depends on bit 4 in select, only meaningful for drive 0 */
    struct IDEStateS *cur_drive;
    BlockDriverStateP bs;
    /* ATAPI specific */
    Uns8 sense_key;
    Uns8 asc;
    Int32 packet_transfer_size;
    Int32 elementary_transfer_size;
    Int32 io_buffer_index;
    Int32 lba;
    Int32 cd_sector_size;
    Int32 atapi_dma; /* true if dma is requested for the packet cmd */
    /* ATA DMA state */
    Int32 io_buffer_size;
    /* PIO transfer handling */
    Int32 req_nb_sectors; /* number of sectors per interrupt */
    EndTransferFunc end_transfer_func;
    Uns8 *data_ptr;
    Uns8 *data_end;
    Uns8 io_buffer[MAX_MULT_SECTORS*SECT_SIZE + 4];
    /* CF-ATA extended error */
    Uns8 ext_error;
    /* CF-ATA metadata storage */
    Uns32 mdata_size;
    Uns8 *mdata_storage;
    Int32 media_changed;
} IDEState;

//
// Describes a DMA channel
//
typedef struct BMDMAStateS {
    Uns8      chn;      // channel number (0/1)
    Uns8      cmd;
    Uns8      dmaStatus;
    Uns32     addr;

    /* current transfer state */
    Uns32     cur_addr;
    Uns32     cur_prd_last;
    Uns32     cur_prd_addr;
    Uns32     cur_prd_len;

    // Stats
    Uns32     totalReadBytes;      // big enough?
    Uns32     totalWriteBytes;
    Uns32     reads;
    Uns32     writes;

    IDEStateP ide_if;
    BlockDriverCompletionFunc *dma_cb;
} BMDMAState;


typedef struct DriveInfo {
    BlockDriverStateP bdrv;
    Uns32 bus;
    Uns32 unit;
} DriveInfo;

typedef struct interruptS {
    ppmNetHandle handle;  // connection
    Bool         v;       // current value
    Uns32        count;   // statistics
} interrupt, *interruptP;

/////////////////////////////////////// FWD REFS ///////////////////////////////////////

static void  bmdma_writeb(Uns8 ch, Uns32 addr, Uns32 val);
static Uns32 bmdma_readb(Uns8 ch, Uns32 addr);
static Uns32 bmdma_addr_readl(Uns8 ch, Uns32 addr);
static void  bmdma_addr_writel(Uns8 ch, Uns32 addr, Uns32 val);
static void  cmd646_update_irq(void);

//////////////////////////////////////// GLOBALS ////////////////////////////////////////

// up to 4 IDE interfaces
static IDEState ide_ifs[4];

// 2 DMAs
static BMDMAState bmdma[2];

// 2 interrupt connections
interrupt interrupts[2];

static Uns32 device_type = 0; /* see IDE_TYPE_xxx */

#define MAX_DRIVES   4 // QEMU had 32

static DriveInfo hd_table[MAX_DRIVES+1];

//////////////////////////////////////// UTILS ////////////////////////////////////////
#if 0
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void saveBuffer(Uns8 *p, Uns32 l)
{
    static int fd = -1;
    if(fd == -1) {
        fd = open("ReadData.log", O_WRONLY| O_CREAT);
        printf("opening rec file\n");
    }
    if(fd != -1) {
        write(fd, p, l);
        printf("writing rec file\n");
    }
}
#endif

static inline Uns32 le32_to_cpu(Uns32 p)
{
    return p;
}

static inline Uns16 cpu_to_le16(Uns16 p)
{
    return p;
}

static inline Uns16 le16_to_cpu(Uns16 p)
{
    return p;
}

static inline void cpu_to_be16wu(Uns16 *p, Uns16 v)
{
    *p = v;
}

static inline void cpu_to_be32wu(Uns32 *p, Uns32 v)
{
    *p = v;
}

static inline Uns32 cpu_to_le32(Uns32 p)
{
    return p;
}

static void ide_dma_start(IDEStateP s, BlockDriverCompletionFunc *dma_cb);
static void ide_atapi_cmd_read_dma_cb(BMDMAStateP bm, Int32 ret);

static void padstr(char *str, const char *src, Int32 len)
{
    Int32 i, v;
    for(i = 0; i < len; i++) {
        if (*src)
            v = *src++;
        else
            v = ' ';
        str[i^1] = v;
    }
}

static void padstr8(Uns8 *buf, Int32 buf_size, const char *src)
{
    Int32 i;
    for(i = 0; i < buf_size; i++) {
        if (*src)
            buf[i] = *src++;
        else
            buf[i] = ' ';
    }
}

static inline void put_le16(Uns16 *p, Uns32 v)
{
    *p = v;
}

//
////////////////////////////////// IDE //////////////////////////////////////////
//
static void ide_identify(IDEStateP s)
{
    Uns16 *p;
    Uns32 oldsize;
    char buf[20];
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "ide_identify ifn:%d", s->ifn);
    if (s->identify_set) {
        memcpy(s->io_buffer, s->identify_data, sizeof(s->identify_data));
        return;
    }
    memset(s->io_buffer, 0, 512);
    p = (Uns16 *)s->io_buffer;
    put_le16(p + 0, 0x0040);
    put_le16(p + 1, s->cylinders);
    put_le16(p + 3, s->heads);
    put_le16(p + 4, 512 * s->sectors); /* XXX: retired, remove ? */
    put_le16(p + 5, 512); /* XXX: retired, remove ? */
    put_le16(p + 6, s->sectors);
    snprintf(buf, sizeof(buf), "QM%05d", s->drive_serial);
    padstr((char *)(p + 10), buf, 20); /* serial number */
    put_le16(p + 20, 3); /* XXX: retired, remove ? */
    put_le16(p + 21, 512); /* cache size in sectors */
    put_le16(p + 22, 4); /* ecc bytes */
    padstr((char *)(p + 23), VERSION, 8); /* firmware version */
    padstr((char *)(p + 27), LABEL " HARDDISK", 40); /* model */
#if MAX_MULT_SECTORS > 1
    put_le16(p + 47, 0x8000 | MAX_MULT_SECTORS);
#endif
    put_le16(p + 48, 1); /* dword I/O */
    put_le16(p + 49, (1 << 11) | (1 << 9) | (1 << 8)); /* DMA and LBA supported */
    put_le16(p + 51, 0x200); /* PIO transfer cycle */
    put_le16(p + 52, 0x200); /* DMA transfer cycle */
    put_le16(p + 53, 1 | (1 << 1) | (1 << 2)); /* words 54-58,64-70,88 are valid */
    put_le16(p + 54, s->cylinders);
    put_le16(p + 55, s->heads);
    put_le16(p + 56, s->sectors);
    oldsize = s->cylinders * s->heads * s->sectors;
    put_le16(p + 57, oldsize);
    put_le16(p + 58, oldsize >> 16);
    if (s->mult_sectors)
        put_le16(p + 59, 0x100 | s->mult_sectors);
    put_le16(p + 60, s->nb_sectors);
    put_le16(p + 61, s->nb_sectors >> 16);
    put_le16(p + 63, 0x07); /* mdma0-2 supported */
    put_le16(p + 65, 120);
    put_le16(p + 66, 120);
    put_le16(p + 67, 120);
    put_le16(p + 68, 120);
    put_le16(p + 80, 0xf0); /* ata3 -> ata6 supported */
    put_le16(p + 81, 0x16); /* conforms to ata5 */
    put_le16(p + 82, (1 << 14));
    /* 13=flush_cache_ext,12=flush_cache,10=lba48 */
    put_le16(p + 83, (1 << 14) | (1 << 13) | (1 <<12) | (1 << 10));
    put_le16(p + 84, (1 << 14));
    put_le16(p + 85, (1 << 14));
    /* 13=flush_cache_ext,12=flush_cache,10=lba48 */
    put_le16(p + 86, (1 << 14) | (1 << 13) | (1 <<12) | (1 << 10));
    put_le16(p + 87, (1 << 14));
    put_le16(p + 88, 0x3f | (1 << 13)); /* udma5 set and supported */
    put_le16(p + 93, 1 | (1 << 14) | 0x2000);
    put_le16(p + 100, s->nb_sectors);
    put_le16(p + 101, s->nb_sectors >> 16);
    put_le16(p + 102, s->nb_sectors >> 32);
    put_le16(p + 103, s->nb_sectors >> 48);

    memcpy(s->identify_data, p, sizeof(s->identify_data));
    s->identify_set = 1;
}

static void ide_atapi_identify(IDEStateP s)
{
    Uns16 *p;
    char buf[20];

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "ide_atapi_identify ifn:%d", s->ifn);

    if (s->identify_set) {
    memcpy(s->io_buffer, s->identify_data, sizeof(s->identify_data));
    return;
    }

    memset(s->io_buffer, 0, 512);
    p = (Uns16 *)s->io_buffer;
    /* Removable CDROM, 50us response, 12 byte packets */
    put_le16(p + 0, (2 << 14) | (5 << 8) | (1 << 7) | (2 << 5) | (0 << 0));
    snprintf(buf, sizeof(buf), "QM%05d", s->drive_serial);
    padstr((char *)(p + 10), buf, 20); /* serial number */
    put_le16(p + 20, 3); /* buffer type */
    put_le16(p + 21, 512); /* cache size in sectors */
    put_le16(p + 22, 4); /* ecc bytes */
    padstr((char *)(p + 23), VERSION, 8); /* firmware version */
    padstr((char *)(p + 27), LABEL " CD-ROM", 40); /* model */
    put_le16(p + 48, 1); /* dword I/O (XXX: should not be set on CDROM) */
#ifdef USE_DMA_CDROM
    put_le16(p + 49, 1 << 9 | 1 << 8); /* DMA and LBA supported */
    put_le16(p + 53, 7); /* words 64-70, 54-58, 88 valid */
    put_le16(p + 63, 7);  /* mdma0-2 supported */
    put_le16(p + 64, 0x3f); /* PIO modes supported */
#else
    put_le16(p + 49, 1 << 9); /* LBA supported, no DMA */
    put_le16(p + 53, 3); /* words 64-70, 54-58 valid */
    put_le16(p + 63, 0x103); /* DMA modes XXX: may be incorrect */
    put_le16(p + 64, 1); /* PIO modes */
#endif
    put_le16(p + 65, 0xb4); /* minimum DMA multiword tx cycle time */
    put_le16(p + 66, 0xb4); /* recommended DMA multiword tx cycle time */
    put_le16(p + 67, 0x12c); /* minimum PIO cycle time without flow control */
    put_le16(p + 68, 0xb4); /* minimum PIO cycle time with IORDY flow control */

    put_le16(p + 71, 30); /* in ns */
    put_le16(p + 72, 30); /* in ns */

    put_le16(p + 80, 0x1e); /* support up to ATA/ATAPI-4 */
#ifdef USE_DMA_CDROM
    put_le16(p + 88, 0x3f | (1 << 13)); /* udma5 set and supported */
#endif
    memcpy(s->identify_data, p, sizeof(s->identify_data));
    s->identify_set = 1;
}

static void ide_cfata_identify(IDEStateP s)
{
    Uns16 *p;
    Uns32 cur_sec;
    char buf[20];

    p = (Uns16 *) s->identify_data;
    if (s->identify_set)
        goto fill_buffer;

    memset(p, 0, sizeof(s->identify_data));

    cur_sec = s->cylinders * s->heads * s->sectors;

    put_le16(p + 0, 0x848a);            /* CF Storage Card signature */
    put_le16(p + 1, s->cylinders);        /* Default cylinders */
    put_le16(p + 3, s->heads);            /* Default heads */
    put_le16(p + 6, s->sectors);        /* Default sectors per track */
    put_le16(p + 7, s->nb_sectors >> 16);    /* Sectors per card */
    put_le16(p + 8, s->nb_sectors);        /* Sectors per card */
    snprintf(buf, sizeof(buf), "QM%05d", s->drive_serial);
    padstr((char *)(p + 10), buf, 20);    /* Serial number in ASCII */
    put_le16(p + 22, 0x0004);            /* ECC bytes */
    padstr((char *) (p + 23), VERSION, 8);    /* Firmware Revision */
    padstr((char *) (p + 27), LABEL " MICRODRIVE", 40);/* Model number */
#if MAX_MULT_SECTORS > 1
    put_le16(p + 47, 0x8000 | MAX_MULT_SECTORS);
#else
    put_le16(p + 47, 0x0000);
#endif
    put_le16(p + 49, 0x0f00);            /* Capabilities */
    put_le16(p + 51, 0x0002);            /* PIO cycle timing mode */
    put_le16(p + 52, 0x0001);            /* DMA cycle timing mode */
    put_le16(p + 53, 0x0003);            /* Translation params valid */
    put_le16(p + 54, s->cylinders);        /* Current cylinders */
    put_le16(p + 55, s->heads);            /* Current heads */
    put_le16(p + 56, s->sectors);        /* Current sectors */
    put_le16(p + 57, cur_sec);            /* Current capacity */
    put_le16(p + 58, cur_sec >> 16);        /* Current capacity */
    if (s->mult_sectors)            /* Multiple sector setting */
        put_le16(p + 59, 0x100 | s->mult_sectors);
    put_le16(p + 60, s->nb_sectors);        /* Total LBA sectors */
    put_le16(p + 61, s->nb_sectors >> 16);    /* Total LBA sectors */
    put_le16(p + 63, 0x0203);            /* Multiword DMA capability */
    put_le16(p + 64, 0x0001);            /* Flow Control PIO support */
    put_le16(p + 65, 0x0096);            /* Min. Multiword DMA cycle */
    put_le16(p + 66, 0x0096);            /* Rec. Multiword DMA cycle */
    put_le16(p + 68, 0x00b4);            /* Min. PIO cycle time */
    put_le16(p + 82, 0x400c);            /* Command Set supported */
    put_le16(p + 83, 0x7068);            /* Command Set supported */
    put_le16(p + 84, 0x4000);            /* Features supported */
    put_le16(p + 85, 0x000c);            /* Command Set enabled */
    put_le16(p + 86, 0x7044);            /* Command Set enabled */
    put_le16(p + 87, 0x4000);            /* Features enabled */
    put_le16(p + 91, 0x4060);            /* Current APM level */
    put_le16(p + 129, 0x0002);            /* Current features option */
    put_le16(p + 130, 0x0005);            /* Reassigned sectors */
    put_le16(p + 131, 0x0001);            /* Initial power mode */
    put_le16(p + 132, 0x0000);            /* User signature */
    put_le16(p + 160, 0x8100);            /* Power requirement */
    put_le16(p + 161, 0x8001);            /* CF command set */

    s->identify_set = 1;

fill_buffer:
    memcpy(s->io_buffer, p, sizeof(s->identify_data));
}

static void ide_set_signature(IDEStateP s)
{
    s->select &= 0xf0; /* clear head */
    /* put signature */
    s->nsector = 1;
    s->sector = 1;
    if (s->is_cdrom) {
        s->lcyl = 0x14;
        s->hcyl = 0xeb;
    } else if (s->bs) {
        s->lcyl = 0;
        s->hcyl = 0;
    } else {
        s->lcyl = 0xff;
        s->hcyl = 0xff;
    }
}

static inline void ide_abort_command(IDEStateP s)
{
    s->status = READY_STAT | ERR_STAT;
    s->error = ABRT_ERR;
}

//
// suppress changes to the same state
//
static void setInt(Uns8 no, Bool v)
{
    if(interrupts[no].handle) {
        if (interrupts[no].v != v) {
            if(v) {
                if (PSE_DIAG_MEDIUM) {
                    bhmMessage("I", PREFIX, "Raising int %d", no);
                }
                interrupts[no].count++;
            }
            ppmWriteNet(interrupts[no].handle, v);
            interrupts[no].v = v;
        }
    }
}


static inline void ide_set_irq(IDEStateP s)
{
    if (!(s->cmd & IDE_CMD_DISABLE_IRQ)) {
        BMDMAState *bm = s->bmdma;
        if (bm) {
            bm->dmaStatus |= BM_STATUS_INT;
        }
        setInt(s->irqNumber, 1);
    }
}

/* prepare data transfer and tell what to do after */
static void ide_transfer_start(IDEStateP s, Uns8 *buf, Int32 size,
                               EndTransferFunc end_transfer_func, const char *why)
{
    s->end_transfer_func = end_transfer_func;
    s->data_ptr = buf;
    s->data_end = buf + size;
    if (!(s->status & ERR_STAT))
        s->status |= DRQ_STAT;
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "ide_transfer_start (%s) ifn:%d  status:0x%x", why, s->ifn, s->status);
}

static void ide_transfer_stop(IDEStateP s)
{
    s->end_transfer_func = ide_transfer_stop;
    s->data_ptr = s->io_buffer;
    s->data_end = s->io_buffer;
    s->status &= ~DRQ_STAT;
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "ide_transfer_stop ifn:%d  status:0x%x", s->ifn, s->status);
}

static Int64 ide_get_sector(IDEStateP s)
{
    Int64 sector_num;
    if (s->select & 0x40) {
        /* lba */
        if (!s->lba48) {
            sector_num = ((s->select & 0x0f) << 24) | (s->hcyl << 16) |
            (s->lcyl << 8) | s->sector;
        } else {
            sector_num = ((Int64)s->hob_hcyl << 40) |
            ((Int64) s->hob_lcyl << 32) |
            ((Int64) s->hob_sector << 24) |
            ((Int64) s->hcyl << 16) |
            ((Int64) s->lcyl << 8) | s->sector;
        }
    } else {
        sector_num = ((s->hcyl << 8) | s->lcyl) * s->heads * s->sectors +
            (s->select & 0x0f) * s->sectors + (s->sector - 1);
    }
    return sector_num;
}

static void ide_set_sector(IDEStateP s, Int64 sector_num)
{
    Uns32 cyl, r;
    if (s->select & 0x40) {
    if (!s->lba48) {
            s->select = (s->select & 0xf0) | (sector_num >> 24);
            s->hcyl = (sector_num >> 16);
            s->lcyl = (sector_num >> 8);
            s->sector = (sector_num);
    } else {
        s->sector = sector_num;
        s->lcyl = sector_num >> 8;
        s->hcyl = sector_num >> 16;
        s->hob_sector = sector_num >> 24;
        s->hob_lcyl = sector_num >> 32;
        s->hob_hcyl = sector_num >> 40;
    }
    } else {
        cyl = sector_num / (s->heads * s->sectors);
        r = sector_num % (s->heads * s->sectors);
        s->hcyl = cyl >> 8;
        s->lcyl = cyl;
        s->select = (s->select & 0xf0) | ((r / s->sectors) & 0x0f);
        s->sector = (r % s->sectors) + 1;
    }
}

//
// seems to use itself as the end_transfer_function
//
static void ide_sector_read(IDEStateP s)
{
    s->status = READY_STAT | SEEK_STAT;
    s->error = 0; /* not needed by IDE spec, but needed by Windows */
    Int64 sector_num = ide_get_sector(s);
    Int32 n          = s->nsector;
    if (n == 0) {
        /* no more sector to read from disk */
        ide_transfer_stop(s);
    } else {
        if (n > s->req_nb_sectors) {
            n = s->req_nb_sectors;
        }
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX,"read sector=%Ld %p %d", sector_num, s->io_buffer, n);
        bdrv_read(s->bs, sector_num, s->io_buffer, n);
        // TODO : errors?
        ide_transfer_start(s, s->io_buffer, 512 * n, ide_sector_read, "ide_sector_read");
        ide_set_irq(s);
        ide_set_sector(s, sector_num + n);
        s->nsector -= n;
    }
}

//
// set up DMA callback and point DMA at active IDE channel
//
static void setDMAcb(BMDMAState *bm, IDEStateP s, BlockDriverCompletionFunc *dma_cb)
{
    bm->dma_cb = dma_cb;
    bm->ide_if = s;
}

//
// Clear CB and active channel
//
static void clrDMAcb(BMDMAState *bm)
{
    bm->dma_cb = NULL;
    bm->ide_if = NULL;
}

//
// Fetch the size and address of block to be transferred, then do the transfer.
// Return 0 if buffer completed
//
static Int32 dma_buf_rw(BMDMAState *bm, Int32 is_write)
{
    IDEStateP s = bm->ide_if;
    struct {
        Uns32 addr;
        Uns32 size;
    } prd;

    for(;;) {
        Int32 l = s->io_buffer_size - s->io_buffer_index;
        if (l <= 0)
            break;
        if (bm->cur_prd_len == 0) {
            /* end of table (with a fail safe of one page) */
            if (bm->cur_prd_last || (bm->cur_addr - bm->addr) >= 4096)
                return 0;
            Uns32 bytes = sizeof(prd);
            ppmReadAddressSpace (masterHandle,  bm->cur_addr, bytes, &prd);
            bm->reads++;
            bm->totalReadBytes += bytes;
            bm->cur_addr += 8;
            prd.addr = le32_to_cpu(prd.addr);
            prd.size = le32_to_cpu(prd.size);
            Int32 len = prd.size & 0xfffe;
            if (len == 0)
                len = 0x10000;
            bm->cur_prd_len  = len;
            bm->cur_prd_addr = prd.addr;
            bm->cur_prd_last = (prd.size & 0x80000000);
        }
        if (l > bm->cur_prd_len)
            l = bm->cur_prd_len;
        if (l > 0) {
            if (is_write) {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX, "DMA writing 0x%x <= %d bytes",
                        bm->cur_prd_addr, l
                    );
                ppmWriteAddressSpace (
                    masterHandle,
                    bm->cur_prd_addr,
                    l,
                    s->io_buffer + s->io_buffer_index
                );
                bm->writes++;
                bm->totalWriteBytes += l;
            } else {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX, "DMA reading 0x%x => %d bytes",
                        bm->cur_prd_addr, l
                    );
                ppmReadAddressSpace (
                    masterHandle,
                    bm->cur_prd_addr,
                    l,
                    s->io_buffer + s->io_buffer_index
                );
                bm->reads++;
                bm->totalReadBytes += l;
            }
            bm->cur_prd_addr += l;
            bm->cur_prd_len -= l;
            s->io_buffer_index += l;
        }
    }
    return 1;
}

//
// Called from ->dma_cb
//
static void ide_read_dma(BMDMAState *bm, Int32 unused)
{
    IDEStateP s = bm->ide_if;

    while(1) {
        Int32 n = s->io_buffer_size >> 9;
        Int64 sector_num = ide_get_sector(s);
        if (n > 0) {
            sector_num += n;
            ide_set_sector(s, sector_num);
            s->nsector -= n;
            if (dma_buf_rw(bm, 1) == 0)
                goto eot;
        }
        /* end of transfer ? */
        if (s->nsector == 0) {
            s->status = READY_STAT | SEEK_STAT;
            ide_set_irq(s);
        eot:
            bm->dmaStatus &= ~BM_STATUS_DMAING;
            bm->dmaStatus |= BM_STATUS_INT;
            clrDMAcb(bm);
            return;
        }
        /* launch next transfer */
        n = s->nsector;
        if (n > MAX_MULT_SECTORS)
            n = MAX_MULT_SECTORS;
        s->io_buffer_index = 0;
        s->io_buffer_size = n * 512;
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "ide read sector:%lld", sector_num);
        bdrv_read(s->bs, sector_num, s->io_buffer, n);
    }
}

static void ide_sector_read_dma(IDEStateP s)
{
    s->status = READY_STAT | SEEK_STAT | DRQ_STAT | BUSY_STAT;
    s->io_buffer_index = 0;
    s->io_buffer_size = 0;
    ide_dma_start(s, ide_read_dma);
}

//static void ide_sector_write_timer_cb(void *opaque)
//{
//    IDEStateP s = opaque;
//    ide_set_irq(s);
//}

static void ide_sector_write(IDEStateP s)
{
    s->status = READY_STAT | SEEK_STAT;

    Int64 sector_num = ide_get_sector(s);
    Int32 n          = s->nsector;

    if (n > s->req_nb_sectors)
        n = s->req_nb_sectors;

    bdrv_write(s->bs, sector_num, s->io_buffer, n);
    s->nsector -= n;
    if (s->nsector == 0) {
        /* no more sectors to write */
        ide_transfer_stop(s);
    } else {
        Int32 n1 = s->nsector;
        if (n1 > s->req_nb_sectors)
            n1 = s->req_nb_sectors;
        ide_transfer_start(s, s->io_buffer, 512 * n1, ide_sector_write, "ide_sector_write");
    }
    ide_set_sector(s, sector_num + n);
    ide_set_irq(s);
}

//
// Called from ->dma_cb
//
static void ide_write_dma_cb(BMDMAState *bm, Int32 unused)
{
    IDEStateP s = bm->ide_if;
    Int32     n = s->io_buffer_size >> 9;
    while(1) {
        Int64 sector_num = ide_get_sector(s);
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX,
                "ide_write_dma_cb: dma:%d ifn:%d n=%d nsector=%d sector_num=%lld ",
                bm->chn,
                s->ifn,
                n,
                s->nsector,
                sector_num
            );

        if (n > 0) {
            sector_num += n;
            ide_set_sector(s, sector_num);
            s->nsector -= n;
        }
        /* end of transfer ? */
        if (s->nsector == 0) {
            s->status = READY_STAT | SEEK_STAT;
            ide_set_irq(s);
        eot:
            bm->dmaStatus &= ~BM_STATUS_DMAING;
            bm->dmaStatus |= BM_STATUS_INT;
            clrDMAcb(bm);
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"ide_write_dma_cb: nsector=0");
            return;
        }

        /* launch next transfer */
        n = s->nsector;
        if (n > MAX_MULT_SECTORS)
            n = MAX_MULT_SECTORS;
        s->io_buffer_index = 0;
        s->io_buffer_size = n * 512;

        if (dma_buf_rw(bm, 0) == 0) {
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"ide_write_dma_cb: dma_buf_rw()==0");
            goto eot;
        }
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX,"ide_write_dma_cb WRITE: sector_num=%lld n=%d", sector_num, n);

        bdrv_write(s->bs, sector_num, s->io_buffer, n);
    }
}

static void ide_sector_write_dma(IDEStateP s)
{
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"ide_sector_write_dma:%d  ns:%d", s->ifn, s->nsector);

    s->status = READY_STAT | SEEK_STAT | DRQ_STAT | BUSY_STAT;
    s->io_buffer_index = 0;
    s->io_buffer_size = 0;
    ide_dma_start(s, ide_write_dma_cb);
}

static void ide_atapi_cmd_ok(IDEStateP s)
{
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"atapi_cmd_ok");
    s->error = 0;
    s->status = READY_STAT;
    s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
    ide_set_irq(s);
}

static void ide_atapi_cmd_error(IDEStateP s, Int32 sense_key, Int32 asc)
{
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"atapi_cmd_error: sense=0x%x asc=0x%x", sense_key, asc);

    s->error = sense_key << 4;
    s->status = READY_STAT | ERR_STAT;
    s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
    s->sense_key = sense_key;
    s->asc = asc;
    ide_set_irq(s);
}

static inline void cpu_to_ube16(Uns8 *buf, Int32 val)
{
    buf[0] = val >> 8;
    buf[1] = val;
}

static inline void cpu_to_ube32(Uns8 *buf, Uns32 val)
{
    buf[0] = val >> 24;
    buf[1] = val >> 16;
    buf[2] = val >> 8;
    buf[3] = val;
}

static inline Int32 ube16_to_cpu(const Uns8 *buf)
{
    return (buf[0] << 8) | buf[1];
}

static inline Int32 ube32_to_cpu(const Uns8 *buf)
{
    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

static void lba_to_msf(Uns8 *buf, Int32 lba)
{
    lba += 150;
    buf[0] = (lba / 75) / 60;
    buf[1] = (lba / 75) % 60;
    buf[2] = lba % 75;
}

static void cd_data_to_raw(Uns8 *buf, Int32 lba)
{
    /* sync bytes */
    buf[0] = 0x00;
    memset(buf + 1, 0xff, 10);
    buf[11] = 0x00;
    buf += 12;
    /* MSF */
    lba_to_msf(buf, lba);
    buf[3] = 0x01; /* mode 1 data */
    buf += 4;
    /* data */
    buf += 2048;
    /* XXX: ECC not computed */
    memset(buf, 0, 288);
}

static Int32 cd_read_sector(BlockDriverStateP bs, Int32 lba, Uns8 *buf,
                           Int32 sector_size)
{
    Int32 ret;
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "cd_read_sector  lba:%d   size:%d", lba, sector_size);

    switch(sector_size) {
        case 2048:
            ret = bdrv_read(bs, (Int64)lba << 2, buf, 4);
            break;
        case 2352:
            ret = bdrv_read(bs, (Int64)lba << 2, buf + 16, 4);
            if (ret < 0)
                return ret;
            cd_data_to_raw(buf, lba);
            break;
        default:
            ret = -EIO;
            break;
    }
    return ret;
}

static void ide_atapi_io_error(IDEStateP s, Int32 ret)
{
    /* XXX: handle more errors */
    if (ret == -ENOMEDIUM) {
        ide_atapi_cmd_error(s, SENSE_NOT_READY,
                            ASC_MEDIUM_NOT_PRESENT);
    } else {
        ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                            ASC_LOGICAL_BLOCK_OOR);
    }
}

/* The whole ATAPI transfer logic is handled in this function */
static void ide_atapi_cmd_reply_end(IDEStateP s)
{
    Int32 byte_count_limit, size, ret;
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"ATAPI reply: tx_size=%d elem_tx_size=%d index=%d",
           s->packet_transfer_size,
           s->elementary_transfer_size,
           s->io_buffer_index);

    if (s->packet_transfer_size <= 0) {
        /* end of transfer */
        ide_transfer_stop(s);
        s->status = READY_STAT;
        s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
        ide_set_irq(s);
    } else {
        /* see if a new sector must be read */
        if (s->lba != -1 && s->io_buffer_index >= s->cd_sector_size) {
            ret = cd_read_sector(s->bs, s->lba, s->io_buffer, s->cd_sector_size);
            if (ret < 0) {
                ide_transfer_stop(s);
                ide_atapi_io_error(s, ret);
                return;
            }
            s->lba++;
            s->io_buffer_index = 0;
        }
        if (s->elementary_transfer_size > 0) {
            /* there are some data left to transmit in this elementary
               transfer */
            size = s->cd_sector_size - s->io_buffer_index;
            if (size > s->elementary_transfer_size)
                size = s->elementary_transfer_size;
            ide_transfer_start(s, s->io_buffer + s->io_buffer_index,
                               size, ide_atapi_cmd_reply_end ,"ide_atapi_cmd_reply_end: continue");
            s->packet_transfer_size -= size;
            s->elementary_transfer_size -= size;
            s->io_buffer_index += size;
        } else {
            /* a new transfer is needed */
            s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO;
            byte_count_limit = s->lcyl | (s->hcyl << 8);

            if (byte_count_limit == 0xffff)
                byte_count_limit--;
            size = s->packet_transfer_size;
            if (size > byte_count_limit) {
                /* byte count limit must be even if this case */
                if (byte_count_limit & 1)
                    byte_count_limit--;
                size = byte_count_limit;
            }
            s->lcyl = size;
            s->hcyl = size >> 8;
            s->elementary_transfer_size = size;
            /* we cannot transmit more than one sector at a time */
            if (s->lba != -1) {
                if (size > (s->cd_sector_size - s->io_buffer_index))
                    size = (s->cd_sector_size - s->io_buffer_index);
            }
            ide_transfer_start(s, s->io_buffer + s->io_buffer_index,
                               size, ide_atapi_cmd_reply_end, "new");
            s->packet_transfer_size -= size;
            s->elementary_transfer_size -= size;
            s->io_buffer_index += size;
            ide_set_irq(s);
        }
    }
}

/* send a reply of 'size' bytes in s->io_buffer to an ATAPI command */
static void ide_atapi_cmd_reply(IDEStateP s, Int32 size, Int32 max_size)
{
    if (size > max_size)
        size = max_size;
    s->lba = -1; /* no sector read */
    s->packet_transfer_size = size;
    s->io_buffer_size = size;    /* dma: send the reply data as one chunk */
    s->elementary_transfer_size = 0;
    s->io_buffer_index = 0;

    if (s->atapi_dma) {
        s->status = READY_STAT | DRQ_STAT;
        ide_dma_start(s, ide_atapi_cmd_read_dma_cb);
    } else {
        s->status = READY_STAT;
        ide_atapi_cmd_reply_end(s);
    }
}

/* start a CD-CDROM read command */
static void ide_atapi_cmd_read_pio(IDEStateP s, Int32 lba, Int32 nb_sectors,
                                  Int32 sector_size)
{
    s->lba = lba;
    s->packet_transfer_size = nb_sectors * sector_size;
    s->elementary_transfer_size = 0;
    s->io_buffer_index = sector_size;
    s->cd_sector_size = sector_size;

    s->status = READY_STAT;
    ide_atapi_cmd_reply_end(s);
}

/****************** ATAPI DMA support *********************/
//
// called from ->dma_cb
//
static void ide_atapi_cmd_read_dma_cb(BMDMAStateP bm, Int32 ret)
{
    IDEStateP s = bm->ide_if;
    Int32 data_offset, n;

    if (ret < 0) {
        ide_atapi_io_error(s, ret);
        goto eot;
    }

    if (s->io_buffer_size > 0) {
    /*
     * For a cdrom read sector command (s->lba != -1),
     * adjust the lba for the next s->io_buffer_size chunk
     * and dma the current chunk.
     * For a command != read (s->lba == -1), just transfer
     * the reply data.
     */
    if (s->lba != -1) {
        if (s->cd_sector_size == 2352) {
        n = 1;
        cd_data_to_raw(s->io_buffer, s->lba);
        } else {
        n = s->io_buffer_size >> 11;
        }
        s->lba += n;
    }
        s->packet_transfer_size -= s->io_buffer_size;
        if (dma_buf_rw(bm, 1) == 0)
            goto eot;
    }

    if (s->packet_transfer_size <= 0) {
        s->status = READY_STAT;
        s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
        ide_set_irq(s);
    eot:
        bm->dmaStatus &= ~BM_STATUS_DMAING;
        bm->dmaStatus |= BM_STATUS_INT;
        clrDMAcb(bm);
        return;
    }

    s->io_buffer_index = 0;
    if (s->cd_sector_size == 2352) {
        n = 1;
        s->io_buffer_size = s->cd_sector_size;
        data_offset = 16;
    } else {
        n = s->packet_transfer_size >> 11;
        if (n > (MAX_MULT_SECTORS / 4))
            n = (MAX_MULT_SECTORS / 4);
        s->io_buffer_size = n * 2048;
        data_offset = 0;
    }
    if (bdrv_read(s->bs, (Int64)s->lba << 2, s->io_buffer + data_offset, n*4) != 0 ) {
        ide_atapi_cmd_error(s, SENSE_NOT_READY,  ASC_MEDIUM_NOT_PRESENT);
    }
    goto eot;
}

/* start a CD-CDROM read command with DMA */
/* XXX: test if DMA is available */
static void ide_atapi_cmd_read_dma(IDEStateP s, Int32 lba, Int32 nb_sectors,
                                   Int32 sector_size)
{
    s->lba = lba;
    s->packet_transfer_size = nb_sectors * sector_size;
    s->io_buffer_index = 0;
    s->io_buffer_size = 0;
    s->cd_sector_size = sector_size;

    /* XXX: check if BUSY_STAT should be set */
    s->status = READY_STAT | DRQ_STAT | BUSY_STAT;
    ide_dma_start(s, ide_atapi_cmd_read_dma_cb);
}

static void ide_atapi_cmd_read(IDEStateP s, Int32 lba, Int32 nb_sectors,
                               Int32 sector_size)
{
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"read %s: LBA=%d nb_sectors=%d",
        s->atapi_dma ? "dma" : "pio", lba, nb_sectors);
    if (s->atapi_dma) {
        ide_atapi_cmd_read_dma(s, lba, nb_sectors, sector_size);
    } else {
        ide_atapi_cmd_read_pio(s, lba, nb_sectors, sector_size);
    }
}

static void ide_atapi_cmd(IDEStateP s)
{
    const Uns8 *packet;
    Uns8 *buf;
    Int32 max_len;

    packet = s->io_buffer;
    buf = s->io_buffer;
    if(PSE_DIAG_HIGH){
        Int32 i;
        bhmMessage("I", PREFIX,"ATAPI CMD:");
        for(i = 0; i < ATAPI_PACKET_SIZE; i++) {
            bhmPrintf(" %02x", packet[i]);
        }
        bhmPrintf("\n");
    }
    switch(s->io_buffer[0]) {
        case GPCMD_TEST_UNIT_READY:
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"GPCMD_TEST_UNIT_READY");

            if (bdrv_is_inserted(s->bs)) {
                ide_atapi_cmd_ok(s);
            } else {
                ide_atapi_cmd_error(s, SENSE_NOT_READY,
                                    ASC_MEDIUM_NOT_PRESENT);
            }
            break;
        case GPCMD_MODE_SENSE_6:
        case GPCMD_MODE_SENSE_10:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_MODE_SENSE");

                Int32 action, code;
                if (packet[0] == GPCMD_MODE_SENSE_10)
                    max_len = ube16_to_cpu(packet + 7);
                else
                    max_len = packet[4];
                action = packet[2] >> 6;
                code = packet[2] & 0x3f;
                switch(action) {
                case 0: /* current values */
                    switch(code) {
                    case 0x01: /* error recovery */
                        cpu_to_ube16(&buf[0], 16 + 6);
                        buf[2] = 0x70;
                        buf[3] = 0;
                        buf[4] = 0;
                        buf[5] = 0;
                        buf[6] = 0;
                        buf[7] = 0;

                        buf[8] = 0x01;
                        buf[9] = 0x06;
                        buf[10] = 0x00;
                        buf[11] = 0x05;
                        buf[12] = 0x00;
                        buf[13] = 0x00;
                        buf[14] = 0x00;
                        buf[15] = 0x00;
                        ide_atapi_cmd_reply(s, 16, max_len);
                        break;
                    case 0x2a:
                        cpu_to_ube16(&buf[0], 28 + 6);
                        buf[2] = 0x70;
                        buf[3] = 0;
                        buf[4] = 0;
                        buf[5] = 0;
                        buf[6] = 0;
                        buf[7] = 0;

                        buf[8] = 0x2a;
                        buf[9] = 0x12;
                        buf[10] = 0x00;
                        buf[11] = 0x00;

                        buf[12] = 0x70;
                        buf[13] = 3 << 5;
                        buf[14] = (1 << 0) | (1 << 3) | (1 << 5);
                        if (bdrv_is_locked(s->bs))
                            buf[6] |= 1 << 1;
                        buf[15] = 0x00;
                        cpu_to_ube16(&buf[16], 706);
                        buf[18] = 0;
                        buf[19] = 2;
                        cpu_to_ube16(&buf[20], 512);
                        cpu_to_ube16(&buf[22], 706);
                        buf[24] = 0;
                        buf[25] = 0;
                        buf[26] = 0;
                        buf[27] = 0;
                        ide_atapi_cmd_reply(s, 28, max_len);
                        break;
                    default:
                        goto error_cmd;
                    }
                    break;
                case 1: /* changeable values */
                    goto error_cmd;
                case 2: /* default values */
                    goto error_cmd;
                default:
                case 3: /* saved values */
                    ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                        ASC_SAVING_PARAMETERS_NOT_SUPPORTED);
                    break;
                }
            }
            break;
        case GPCMD_REQUEST_SENSE:
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"GPCMD_REQUEST_SENSE");
            max_len = packet[4];
            memset(buf, 0, 18);
            buf[0] = 0x70 | (1 << 7);
            buf[2] = s->sense_key;
            buf[7] = 10;
            buf[12] = s->asc;
            ide_atapi_cmd_reply(s, 18, max_len);
            break;
        case GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL:
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"GPCMD_PREVENT_MEDIUM_REMOVAL");
            if (bdrv_is_inserted(s->bs)) {
                bdrv_set_locked(s->bs, packet[4] & 1);
                ide_atapi_cmd_ok(s);
            } else {
                ide_atapi_cmd_error(s, SENSE_NOT_READY,
                                    ASC_MEDIUM_NOT_PRESENT);
            }
            break;
        case GPCMD_READ_10:
        case GPCMD_READ_12:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_READ");
                Int32 nb_sectors;

                if (packet[0] == GPCMD_READ_10)
                    nb_sectors = ube16_to_cpu(packet + 7);
                else
                    nb_sectors = ube32_to_cpu(packet + 6);
                Int32 lba = ube32_to_cpu(packet + 2);
                if (nb_sectors == 0) {
                    ide_atapi_cmd_ok(s);
                    break;
                }
                ide_atapi_cmd_read(s, lba, nb_sectors, 2048);
            }
            break;
        case GPCMD_READ_CD:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_READ_CD");

                Int32 nb_sectors = (packet[6] << 16) | (packet[7] << 8) | packet[8];
                Int32 lba = ube32_to_cpu(packet + 2);
                if (nb_sectors == 0) {
                    ide_atapi_cmd_ok(s);
                    break;
                }
                Int32 transfer_request = packet[9];
                switch(transfer_request & 0xf8) {
                case 0x00:
                    /* nothing */
                    ide_atapi_cmd_ok(s);
                    break;
                case 0x10:
                    /* normal read */
                    ide_atapi_cmd_read(s, lba, nb_sectors, 2048);
                    break;
                case 0xf8:
                    /* read all data */
                    ide_atapi_cmd_read(s, lba, nb_sectors, 2352);
                    break;
                default:
                    ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                        ASC_INV_FIELD_IN_CMD_PACKET);
                    break;
                }
            }
            break;
        case GPCMD_SEEK:
            {
               if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_SEEK");
                Uns64 total_sectors;
                bdrv_get_geometry(s->bs, &total_sectors);
                total_sectors >>= 2;
                if (total_sectors == 0) {
                    ide_atapi_cmd_error(s, SENSE_NOT_READY,
                                        ASC_MEDIUM_NOT_PRESENT);
                    break;
                }
                Uns32 lba = ube32_to_cpu(packet + 2);
                if (lba >= total_sectors) {
                    ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                        ASC_LOGICAL_BLOCK_OOR);
                    break;
                }
                ide_atapi_cmd_ok(s);
            }
            break;
        case GPCMD_START_STOP_UNIT:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_START_STOP_UNIT");

                Int32 start = packet[4] & 1;
                Int32 eject = (packet[4] >> 1) & 1;

                if (eject && !start) {
                    /* eject the disk */
                    bdrv_eject(s->bs, 1);
                } else if (eject && start) {
                    /* close the tray */
                    bdrv_eject(s->bs, 0);
                }
                ide_atapi_cmd_ok(s);
            }
            break;
        case GPCMD_MECHANISM_STATUS:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_MECHANISM_STATUS");
                max_len = ube16_to_cpu(packet + 8);
                cpu_to_ube16(buf, 0);
                /* no current LBA */
                buf[2] = 0;
                buf[3] = 0;
                buf[4] = 0;
                buf[5] = 1;
                cpu_to_ube16(buf + 6, 0);
                ide_atapi_cmd_reply(s, 8, max_len);
            }
            break;
        case GPCMD_READ_TOC_PMA_ATIP:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_READ_TOC_PMA_ATIP");

                Int32 len;
                Uns64 total_sectors;
                bdrv_get_geometry(s->bs, &total_sectors);
                total_sectors >>= 2;
                if (total_sectors == 0) {
                    ide_atapi_cmd_error(s, SENSE_NOT_READY,
                                        ASC_MEDIUM_NOT_PRESENT);
                    break;
                }
                max_len = ube16_to_cpu(packet + 7);
                Int32 format = packet[9] >> 6;
                Int32 msf = (packet[1] >> 1) & 1;
                Int32 start_track = packet[6];
                switch(format) {
                case 0:
                    len = cdrom_read_toc(total_sectors, buf, msf, start_track);
                    if (len < 0)
                        goto error_cmd;
                    ide_atapi_cmd_reply(s, len, max_len);
                    break;
                case 1:
                    /* multi session : only a single session defined */
                    memset(buf, 0, 12);
                    buf[1] = 0x0a;
                    buf[2] = 0x01;
                    buf[3] = 0x01;
                    ide_atapi_cmd_reply(s, 12, max_len);
                    break;
                case 2:
                    len = cdrom_read_toc_raw(total_sectors, buf, msf, start_track);
                    if (len < 0)
                        goto error_cmd;
                    ide_atapi_cmd_reply(s, len, max_len);
                    break;
                default:
                error_cmd:
                    ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                        ASC_INV_FIELD_IN_CMD_PACKET);
                    break;
                }
            }
            break;
        case GPCMD_READ_CDVD_CAPACITY:
            {
                Uns64 total_sectors;

                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_READ_CDVD_CAPACITY");
                bdrv_get_geometry(s->bs, &total_sectors);
                total_sectors >>= 2;
                if (total_sectors == 0) {
                    ide_atapi_cmd_error(s, SENSE_NOT_READY,
                                        ASC_MEDIUM_NOT_PRESENT);
                    break;
                }
                /* NOTE: it is really the number of sectors minus 1 */
                cpu_to_ube32(buf, total_sectors - 1);
                cpu_to_ube32(buf + 4, 2048);
                ide_atapi_cmd_reply(s, 8, 8);
            }
            break;
        case GPCMD_READ_DVD_STRUCTURE:
            {
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_READ_DVD_STRUCTURE");
                Int32 media = packet[1];
                Int32 layer = packet[6];
                Int32 format = packet[2];
                Uns64 total_sectors;

                if (media != 0 || layer != 0)
                {
                    ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                        ASC_INV_FIELD_IN_CMD_PACKET);
                }

                switch (format) {
                    case 0:
                        bdrv_get_geometry(s->bs, &total_sectors);
                        total_sectors >>= 2;
                        if (total_sectors == 0) {
                            ide_atapi_cmd_error(s, SENSE_NOT_READY,
                                                ASC_MEDIUM_NOT_PRESENT);
                            break;
                        }

                        memset(buf, 0, 2052);

                        buf[4] = 1;   // DVD-ROM, part version 1
                        buf[5] = 0xf; // 120mm disc, maximum rate unspecified
                        buf[6] = 0;   // one layer, embossed data
                        buf[7] = 0;

                        cpu_to_ube32(buf + 8, 0);
                        cpu_to_ube32(buf + 12, total_sectors - 1);
                        cpu_to_ube32(buf + 16, total_sectors - 1);

                        cpu_to_be16wu((Uns16 *)buf, 2048 + 4);

                        ide_atapi_cmd_reply(s, 2048 + 3, 2048 + 4);
                        break;

                    default:
                        ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                            ASC_INV_FIELD_IN_CMD_PACKET);
                        break;
                }
            }
            break;
        case GPCMD_SET_SPEED:
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"GPCMD_SET_SPEED");
            ide_atapi_cmd_ok(s);
            break;
        case GPCMD_INQUIRY:
             if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX,"GPCMD_INQUIRY");
            max_len = packet[4];
            buf[0] = 0x05; /* CD-ROM */
            buf[1] = 0x80; /* removable */
            buf[2] = 0x00; /* ISO */
            buf[3] = 0x21; /* ATAPI-2 (XXX: put ATAPI-4 ?) */
            buf[4] = 31; /* additional length */
            buf[5] = 0; /* reserved */
            buf[6] = 0; /* reserved */
            buf[7] = 0; /* reserved */
            padstr8(buf + 8, 8, LABEL);
            padstr8(buf + 16, 16, LABEL " CD-ROM");
            padstr8(buf + 32, 4, VERSION);
            ide_atapi_cmd_reply(s, 36, max_len);
            break;
        case GPCMD_GET_CONFIGURATION:
            {
                Uns64 total_sectors;
                if(PSE_DIAG_MEDIUM)
                    bhmMessage("I", PREFIX,"GPCMD_GET_CONFIGURATION");

                /* only feature 0 is supported */
                if (packet[2] != 0 || packet[3] != 0) {
                    ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                        ASC_INV_FIELD_IN_CMD_PACKET);
                    break;
                }
                memset(buf, 0, 32);
                bdrv_get_geometry(s->bs, &total_sectors);
                buf[3] = 16;
                buf[7] = total_sectors <= 1433600 ? 0x08 : 0x10; /* current profile */
                buf[10] = 0x10 | 0x1;
                buf[11] = 0x08; /* size of profile list */
                buf[13] = 0x10; /* DVD-ROM profile */
                buf[14] = buf[7] == 0x10; /* (in)active */
                buf[17] = 0x08; /* CD-ROM profile */
                buf[18] = buf[7] == 0x08; /* (in)active */
                ide_atapi_cmd_reply(s, 32, 32);
                break;
            }
        default:
            if(PSE_DIAG_MEDIUM)
                bhmMessage("W", PREFIX,"GPCMD UNKNOWN CMD???");
            ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,
                                ASC_ILLEGAL_OPCODE);
            break;
    }
}

static void ide_cfata_metadata_inquiry(IDEStateP s)
{
    Uns16 *p;
    Uns32 spd;

    p = (Uns16 *) s->io_buffer;
    memset(p, 0, 0x200);
    spd = ((s->mdata_size - 1) >> 9) + 1;

    put_le16(p + 0, 0x0001);                    /* Data format revision */
    put_le16(p + 1, 0x0000);                    /* Media property: silicon */
    put_le16(p + 2, s->media_changed);          /* Media status */
    put_le16(p + 3, s->mdata_size & 0xffff);    /* Capacity in bytes (low) */
    put_le16(p + 4, s->mdata_size >> 16);       /* Capacity in bytes (high) */
    put_le16(p + 5, spd & 0xffff);              /* Sectors per device (low) */
    put_le16(p + 6, spd >> 16);                 /* Sectors per device (high) */
}

static void ide_cfata_metadata_read(IDEStateP s)
{
    Uns16 *p;

    if (((s->hcyl << 16) | s->lcyl) << 9 > s->mdata_size + 2) {
        s->status = ERR_STAT;
        s->error = ABRT_ERR;
        return;
    }

    p = (Uns16 *) s->io_buffer;
    memset(p, 0, 0x200);

    put_le16(p + 0, s->media_changed);        /* Media status */
    memcpy(
        p + 1,
        s->mdata_storage + (((s->hcyl << 16) | s->lcyl) << 9),
        MIN(MIN(s->mdata_size - (((s->hcyl << 16) | s->lcyl) << 9),
                                s->nsector << 9), 0x200 - 2)
    );
}

static void ide_cfata_metadata_write(IDEStateP s)
{
    if (((s->hcyl << 16) | s->lcyl) << 9 > s->mdata_size + 2) {
        s->status = ERR_STAT;
        s->error = ABRT_ERR;
        return;
    }

    s->media_changed = 0;

    memcpy(
        s->mdata_storage + (((s->hcyl << 16) | s->lcyl) << 9),
        s->io_buffer + 2,
        MIN(MIN(s->mdata_size - (((s->hcyl << 16) | s->lcyl) << 9),
                                s->nsector << 9), 0x200 - 2)
    );
}

/* called when the inserted state of the media has changed */
static void cdrom_change_cb(void *opaque)
{
    IDEStateP s = opaque;
    Uns64 nb_sectors;

    /* XXX: send interrupt too */
    bdrv_get_geometry(s->bs, &nb_sectors);
    s->nb_sectors = nb_sectors;
}

static void ide_cmd_lba48_transform(IDEStateP s, Int32 lba48)
{
    s->lba48 = lba48;

    /* handle the 'magic' 0 nsector count conversion here. to avoid
     * fiddling with the rest of the read logic, we just store the
     * full sector count in ->nsector and ignore ->hob_nsector from now
     */
    if (!s->lba48) {
        if (!s->nsector)
            s->nsector = 256;
    } else {
        if (!s->nsector && !s->hob_nsector)
            s->nsector = 65536;
        else {
            Int32 lo = s->nsector;
            Int32 hi = s->hob_nsector;

            s->nsector = (hi << 8) | lo;
        }
    }
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,
            "ide_cmd_lba48_transform ifn: %d lba48:%d  nsector:%d",
            s->ifn,
            lba48,
            s->nsector
        );
}

static void ide_clear_hob(IDEStateP ide_if)
{
    /* any write clears HOB high bit of device control register */
    ide_if[0].select &= ~(1 << 7);
    ide_if[1].select &= ~(1 << 7);
}

static void ide_ioport_write(Uns8 ch, Uns32 addr, Uns32 val)
{
    IDEStateP s;
    Int32 n;
    Int32 lba48 = 0;
    IDEStateP ide_if = &ide_ifs[ch*2];

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,"ide_ioport_write ifn:%d 0x%x <= 0x%02x", ide_if->ifn, addr, val);
    }
    addr &= 7;
    switch(addr) {
    case 0:
        break;
    case 1:
        ide_clear_hob(ide_if);
        /* NOTE: data is written to the two drives */
        ide_if[0].hob_feature = ide_if[0].feature;
        ide_if[1].hob_feature = ide_if[1].feature;
        ide_if[0].feature = val;
        ide_if[1].feature = val;
        break;
    case 2:
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX,
                "ide_ioport_write ifn:%d nsector=%d",
                ide_if[0].ifn, val);
        }
        ide_clear_hob(ide_if);
        ide_if[0].hob_nsector = ide_if[0].nsector;
        ide_if[1].hob_nsector = ide_if[1].nsector;
        ide_if[0].nsector = val;
        ide_if[1].nsector = val;
        break;
    case 3:
        ide_clear_hob(ide_if);
        ide_if[0].hob_sector = ide_if[0].sector;
        ide_if[1].hob_sector = ide_if[1].sector;
        ide_if[0].sector = val;
        ide_if[1].sector = val;
        break;
    case 4:
        ide_clear_hob(ide_if);
        ide_if[0].hob_lcyl = ide_if[0].lcyl;
        ide_if[1].hob_lcyl = ide_if[1].lcyl;
        ide_if[0].lcyl = val;
        ide_if[1].lcyl = val;
        break;
    case 5:
        ide_clear_hob(ide_if);
        ide_if[0].hob_hcyl = ide_if[0].hcyl;
        ide_if[1].hob_hcyl = ide_if[1].hcyl;
        ide_if[0].hcyl = val;
        ide_if[1].hcyl = val;
        break;
    case 6:
        /* FIXME: HOB readback uses bit 7 */
        ide_if[0].select = (val & ~0x10) | 0xa0;
        ide_if[1].select = (val | 0x10) | 0xa0;
        /* select drive */
        Uns32 unit = (val >> 4) & 1;
        s = ide_if + unit;
        if((PSE_DIAG_MEDIUM) && (ide_if->cur_drive != s)) {
            bhmMessage("I", PREFIX, "Selecting ifn:%d=%d", ide_if->ifn, s->ifn);
        }
        ide_if->cur_drive = s;
        break;
    default:
    case 7:
        /* command */
        s = ide_if->cur_drive;

        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX,"ifn:%d  cmd:0x%02x", s->ifn, val);
        }
        /* ignore commands to non existant slave */
        if (s != ide_if && !s->bs)
            break;

        switch(val) {
        case WIN_IDENTIFY:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_IDENTIFY");
            if (s->bs && !s->is_cdrom) {
                if (!s->is_cf)
                    ide_identify(s);
                else
                    ide_cfata_identify(s);
                s->status = READY_STAT | SEEK_STAT;
                ide_transfer_start(s, s->io_buffer, 512, ide_transfer_stop, "WIN_IDENTIFY");
            } else {
                if (s->is_cdrom) {
                    ide_set_signature(s);
                }
                ide_abort_command(s);
            }
            ide_set_irq(s);
            break;
        case WIN_SPECIFY:
        case WIN_RECAL:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_SPECIFY | RECAL");
            s->error = 0;
            s->status = READY_STAT | SEEK_STAT;
            ide_set_irq(s);
            break;
        case WIN_SETMULT:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_SETMULT");
            if (s->is_cf && s->nsector == 0) {
                /* Disable Read and Write Multiple */
                s->mult_sectors = 0;
                s->status = READY_STAT;
            } else if ((s->nsector & 0xff) != 0 &&
                ((s->nsector & 0xff) > MAX_MULT_SECTORS ||
                 (s->nsector & (s->nsector - 1)) != 0)) {
                ide_abort_command(s);
            } else {
                s->mult_sectors = s->nsector & 0xff;
                s->status = READY_STAT;
            }
            ide_set_irq(s);
            break;
        case WIN_VERIFY_EXT:
            lba48 = 1;
        case WIN_VERIFY:
        case WIN_VERIFY_ONCE:
            /* do sector number check ? */
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_VERIFY");
            ide_cmd_lba48_transform(s, lba48);
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_READ_EXT:
            lba48 = 1;
        case WIN_READ:
        case WIN_READ_ONCE:
            if (!s->bs)
                goto abort_cmd;
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_READ");
            ide_cmd_lba48_transform(s, lba48);
            s->req_nb_sectors = 1;
            ide_sector_read(s);
            break;
        case WIN_WRITE_EXT:
            lba48 = 1;
        case WIN_WRITE:
        case WIN_WRITE_ONCE:
        case CFA_WRITE_SECT_WO_ERASE:
        case WIN_WRITE_VERIFY:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_WRITE");
            ide_cmd_lba48_transform(s, lba48);
            s->error = 0;
            s->status = SEEK_STAT | READY_STAT;
            s->req_nb_sectors = 1;
            ide_transfer_start(s, s->io_buffer, 512, ide_sector_write, "WIN_WRITE");
            s->media_changed = 1;
            break;
        case WIN_MULTREAD_EXT:
            lba48 = 1;
        case WIN_MULTREAD:
            if (!s->mult_sectors)
                goto abort_cmd;
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_MULTREAD");
            ide_cmd_lba48_transform(s, lba48);
            s->req_nb_sectors = s->mult_sectors;
            ide_sector_read(s);
            break;
        case WIN_MULTWRITE_EXT:
            lba48 = 1;
        case WIN_MULTWRITE:
        case CFA_WRITE_MULTI_WO_ERASE:
            if (!s->mult_sectors)
                goto abort_cmd;
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_MULTWRITE");
            ide_cmd_lba48_transform(s, lba48);
            s->error = 0;
            s->status = SEEK_STAT | READY_STAT;
            s->req_nb_sectors = s->mult_sectors;
            n = s->nsector;
            if (n > s->req_nb_sectors)
                n = s->req_nb_sectors;
            ide_transfer_start(s, s->io_buffer, 512 * n, ide_sector_write, "WIN_MULTWRITE");
            s->media_changed = 1;
            break;
        case WIN_READDMA_EXT:
            lba48 = 1;
        case WIN_READDMA:
        case WIN_READDMA_ONCE:
            if (!s->bs)
                goto abort_cmd;
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_READDMA");
            ide_cmd_lba48_transform(s, lba48);
            ide_sector_read_dma(s);
            break;
        case WIN_WRITEDMA_EXT:
            lba48 = 1;
        case WIN_WRITEDMA:
        case WIN_WRITEDMA_ONCE:
            if (!s->bs)
                goto abort_cmd;
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_WRITEDMA");
            ide_cmd_lba48_transform(s, lba48);
            ide_sector_write_dma(s);
            s->media_changed = 1;
            break;
        case WIN_READ_NATIVE_MAX_EXT:
            lba48 = 1;
        case WIN_READ_NATIVE_MAX:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_READNATIVE");
            ide_cmd_lba48_transform(s, lba48);
            ide_set_sector(s, s->nb_sectors - 1);
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_CHECKPOWERMODE1:
        case WIN_CHECKPOWERMODE2:
            s->nsector = 0xff; /* device active or idle */
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_SETFEATURES:
            if (!s->bs)
                goto abort_cmd;

            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_SETFEATURES 0x%x", s->feature);
            switch(s->feature) {
                case 0xcc: /* reverting to power-on defaults enable */
                case 0x66: /* reverting to power-on defaults disable */
                case 0x02: /* write cache enable */
                case 0x82: /* write cache disable */
                case 0xaa: /* read look-ahead enable */
                case 0x55: /* read look-ahead disable */
                case 0x05: /* set advanced power management mode */
                case 0x85: /* disable advanced power management mode */
                case 0x69: /* NOP */
                case 0x67: /* NOP */
                case 0x96: /* NOP */
                case 0x9a: /* NOP */
                case 0x42: /* enable Automatic Acoustic Mode */
                case 0xc2: /* disable Automatic Acoustic Mode */
                    s->status = READY_STAT | SEEK_STAT;
                    ide_set_irq(s);
                    break;
                case 0x03: { /* set transfer mode */
                    Uns8 val = s->nsector & 0x07;

                    switch (s->nsector >> 3) {
                        case 0x00: /* pio default */
                        case 0x01: /* pio mode */
                            put_le16(s->identify_data + 63,0x07);
                            put_le16(s->identify_data + 88,0x3f);
                            break;
                        case 0x04: /* mdma mode */
                            put_le16(s->identify_data + 63,0x07 | (1 << (val + 8)));
                            put_le16(s->identify_data + 88,0x3f);
                            break;
                        case 0x08: /* udma mode */
                            put_le16(s->identify_data + 63,0x07);
                            put_le16(s->identify_data + 88,0x3f | (1 << (val + 8)));
                            break;
                        default:
                            goto abort_cmd;
                    }
                    s->status = READY_STAT | SEEK_STAT;
                    ide_set_irq(s);
                    break;
                }
                default:
                    goto abort_cmd;
            }
            break;
        case WIN_FLUSH_CACHE:
        case WIN_FLUSH_CACHE_EXT:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN_FLUSH_CACHE");
            if (s->bs)
                bdrv_flush(s->bs);
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_STANDBY:
        case WIN_STANDBY2:
        case WIN_STANDBYNOW1:
        case WIN_STANDBYNOW2:
        case WIN_IDLEIMMEDIATE:
        case CFA_IDLEIMMEDIATE:
        case WIN_SETIDLE1:
        case WIN_SETIDLE2:
        case WIN_SLEEPNOW1:
        case WIN_SLEEPNOW2:
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
            /* ATAPI commands */
        case WIN_PIDENTIFY:
            if (s->is_cdrom) {
                ide_atapi_identify(s);
                s->status = READY_STAT | SEEK_STAT;
                ide_transfer_start(s, s->io_buffer, 512, ide_transfer_stop, "WIN_PIDENTIFY");
            } else {
                ide_abort_command(s);
            }
            ide_set_irq(s);
            break;
        case WIN_DIAGNOSE:
            ide_set_signature(s);
            s->status = 0x00; /* NOTE: READY is _not_ set */
            s->error = 0x01;
            ide_set_irq(s);
            break;
        case WIN_SRST:
            if (!s->is_cdrom)
                goto abort_cmd;
            ide_set_signature(s);
            s->status = 0x00; /* NOTE: READY is _not_ set */
            s->error = 0x01;
            break;
        case WIN_PACKETCMD:
            if (!s->is_cdrom)
                goto abort_cmd;
            /* overlapping commands not supported */
            if (s->feature & 0x02)
                goto abort_cmd;
            s->status = READY_STAT;
            s->atapi_dma = s->feature & 1;
            s->nsector = 1;
            ide_transfer_start(s, s->io_buffer, ATAPI_PACKET_SIZE, ide_atapi_cmd, "WIN_PACKETCMD");
            break;
        /* CF-ATA commands */
        case CFA_REQ_EXT_ERROR_CODE:
            if (!s->is_cf)
                goto abort_cmd;
            s->error = 0x09;    /* miscellaneous error */
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case CFA_ERASE_SECTORS:
        case CFA_WEAR_LEVEL:
            if (!s->is_cf)
                goto abort_cmd;
            if (val == CFA_WEAR_LEVEL)
                s->nsector = 0;
            if (val == CFA_ERASE_SECTORS)
                s->media_changed = 1;
            s->error = 0x00;
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case CFA_TRANSLATE_SECTOR:
            if (!s->is_cf)
                goto abort_cmd;
            s->error = 0x00;
            s->status = READY_STAT;
            memset(s->io_buffer, 0, 0x200);
            s->io_buffer[0x00] = s->hcyl;            /* Cyl MSB */
            s->io_buffer[0x01] = s->lcyl;            /* Cyl LSB */
            s->io_buffer[0x02] = s->select;            /* Head */
            s->io_buffer[0x03] = s->sector;            /* Sector */
            s->io_buffer[0x04] = ide_get_sector(s) >> 16;    /* LBA MSB */
            s->io_buffer[0x05] = ide_get_sector(s) >> 8;    /* LBA */
            s->io_buffer[0x06] = ide_get_sector(s) >> 0;    /* LBA LSB */
            s->io_buffer[0x13] = 0x00;                /* Erase flag */
            s->io_buffer[0x18] = 0x00;                /* Hot count */
            s->io_buffer[0x19] = 0x00;                /* Hot count */
            s->io_buffer[0x1a] = 0x01;                /* Hot count */
            ide_transfer_start(s, s->io_buffer, 0x200, ide_transfer_stop, "CFA_TRANSLATE_SECTOR");
            ide_set_irq(s);
            break;
        case CFA_ACCESS_METADATA_STORAGE:
            if (!s->is_cf)
                goto abort_cmd;
            switch (s->feature) {
                case 0x02:    /* Inquiry Metadata Storage */
                    ide_cfata_metadata_inquiry(s);
                    break;
                case 0x03:    /* Read Metadata Storage */
                    ide_cfata_metadata_read(s);
                    break;
                case 0x04:    /* Write Metadata Storage */
                    ide_cfata_metadata_write(s);
                    break;
                default:
                    goto abort_cmd;
            }
            ide_transfer_start(s, s->io_buffer, 0x200, ide_transfer_stop, "CFA_ACCESS_METADATA_STORAGE");
            s->status = 0x00; /* NOTE: READY is _not_ set */
            ide_set_irq(s);
            break;
        case IBM_SENSE_CONDITION:
            if (!s->is_cf)
                goto abort_cmd;
            switch (s->feature) {
                case 0x01:  /* sense temperature in device */
                    s->nsector = 0x50;      /* +20 C */
                    break;
                default:
                    goto abort_cmd;
            }
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        default:
        abort_cmd:
            if(PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "WIN (Abort)");
            ide_abort_command(s);
            ide_set_irq(s);
            break;
        }
    }
}

static Uns32 ide_ioport_read(Uns8 ch, Uns32 addr1)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s      = ide_if->cur_drive;
    Uns32 addr;
    Int32 ret, hob;

    addr = addr1 & 7;
    /* FIXME: HOB readback uses bit 7, but it's always set right now */
    //hob = s->select & (1 << 7);
    hob = 0;
    switch(addr) {
        case 0:
            ret = 0xff;
            break;
        case 1:
            if (!ide_if[0].bs && !ide_if[1].bs)
                ret = 0;
            else if (!hob)
                ret = s->error;
            else
                ret = s->hob_feature;
            break;
        case 2:
            if (!ide_if[0].bs && !ide_if[1].bs)
                ret = 0;
            else if (!hob)
                ret = s->nsector & 0xff;
            else
                ret = s->hob_nsector;
            break;
        case 3:
            if (!ide_if[0].bs && !ide_if[1].bs)
                ret = 0;
            else if (!hob)
                ret = s->sector;
            else
                ret = s->hob_sector;
            break;
        case 4:
            if (!ide_if[0].bs && !ide_if[1].bs)
                ret = 0;
            else if (!hob)
                ret = s->lcyl;
            else
                ret = s->hob_lcyl;
            break;
        case 5:
            if (!ide_if[0].bs && !ide_if[1].bs)
                ret = 0;
            else if (!hob)
                ret = s->hcyl;
            else
                ret = s->hob_hcyl;
            break;
        case 6:
            if (!ide_if[0].bs && !ide_if[1].bs)
                ret = 0;
            else
                ret = s->select;
            break;
        default:
        case 7:
            if ((!ide_if[0].bs && !ide_if[1].bs) || (s != ide_if && !s->bs)) {
                ret = 0;
            }
            else {
                ret = s->status;
            }
            setInt(s->irqNumber, 0);
            break;
    }
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,"ide_ioport_read ifn:%d cur:%d 0x%x => %02x", ide_if->ifn, s->ifn, addr1, ret);
    }
    return ret;
}

static Uns32 ide_status_read(Uns8 ch)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s      = ide_if->cur_drive;
    Int32 ret;

    if ((!ide_if[0].bs && !ide_if[1].bs) ||
        (s != ide_if && !s->bs))
        ret = 0;
    else
        ret = s->status;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ide_status_read ch:%d ifn:%d => %02x", ch, s->ifn, ret);
    }
    return ret;
}

static void ide_cmd_write(Uns8 ch, Uns32 val)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s;
    Int32 i;
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ide_cmd_write ifn:%d<= 0x%x", ide_if->ifn, val);
    }
    /* common for both drives */
    if (!(ide_if[0].cmd & IDE_CMD_RESET) &&
        (val & IDE_CMD_RESET)) {
        /* reset low to high */
        for(i = 0;i < 2; i++) {
            s = &ide_if[i];
            s->status = BUSY_STAT | SEEK_STAT;
            s->error = 0x01;
        }
    } else if ((ide_if[0].cmd & IDE_CMD_RESET) &&
               !(val & IDE_CMD_RESET)) {
        /* high to low */
        for(i = 0;i < 2; i++) {
            s = &ide_if[i];
            if (s->is_cdrom)
                s->status = 0x00; /* NOTE: READY is _not_ set */
            else
                s->status = READY_STAT | SEEK_STAT;
            ide_set_signature(s);
        }
    }
    ide_if[0].cmd = val;
    ide_if[1].cmd = val;
}

static void ide_data_writew(Uns8 ch, Uns32 val)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s      = ide_if->cur_drive;
    Uns8      *p     = s->data_ptr;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ide_data_writew ifn:%d <= 0x%x", s->ifn, val);
    }
    *(Uns16 *)p = le16_to_cpu(val);
    p += 2;
    s->data_ptr = p;
    if (p >= s->data_end) {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "    ide_data_writew end. calling end func.");
        }
        s->end_transfer_func(s);
    }
}

static Uns32 ide_data_readw(Uns8 ch, Uns32 addr)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s      = ide_if->cur_drive;
    Uns8      *p     = s->data_ptr;
    Uns32     ret    = cpu_to_le16(*(Uns16 *)p);
    p += 2;
    s->data_ptr = p;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ide_data_readw ifn:%d => 0x%04x", s->ifn, ret);
    }
    if (p >= s->data_end) {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "    ide_data_readw end. calling end func");
        }
        s->end_transfer_func(s);
    }
    return ret;
}

static void ide_data_writel(Uns8 ch, Uns32 val)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s      = ide_if->cur_drive;
    Uns8      *p     = s->data_ptr;
    *(Uns32 *)p      = le32_to_cpu(val);
    p += 4;
    s->data_ptr = p;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ide_data_writel ifn:%d <= 0x%x", s->ifn, val);
    }
    if (p >= s->data_end) {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "    ide_data_writel end. calling end func");
        }
        s->end_transfer_func(s);
    }
}

static Uns32 ide_data_readl(Uns8 ch, Uns32 addr)
{
    IDEStateP ide_if = &ide_ifs[ch*2];
    IDEStateP s      = ide_if->cur_drive;
    Uns8      *p     = s->data_ptr;
    Int32     ret    = cpu_to_le32(*(Uns32 *)p);
    p += 4;
    s->data_ptr = p;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "ide_data_readl ifn:%d => 0x%x", s->ifn, ret);
    }
    if (p >= s->data_end) {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "    ide_data_readl end. calling end func");
        }
        s->end_transfer_func(s);
    }
    return ret;
}

static void ide_dummy_transfer_stop(IDEStateP s)
{
    s->data_ptr     = s->io_buffer;
    s->data_end     = s->io_buffer;
    s->io_buffer[0] = 0xff;
    s->io_buffer[1] = 0xff;
    s->io_buffer[2] = 0xff;
    s->io_buffer[3] = 0xff;
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "ide_dummy_transfer_stop ifn:%d", s->ifn);
    }
}

static void ide_reset(IDEStateP s)
{
    if (s->is_cf)
        s->mult_sectors = 0;
    else
        s->mult_sectors = MAX_MULT_SECTORS;
    s->cur_drive = s;

    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "ide_reset  ifn:%d   current=%d", s->ifn, s->cur_drive->ifn);
    }

    s->select = 0xa0;
    s->status = READY_STAT;
    ide_set_signature(s);
    /* init the transfer handler so that 0xffff is returned on data
       accesses */
    s->end_transfer_func = ide_dummy_transfer_stop;
    ide_dummy_transfer_stop(s);
    s->media_changed = 0;
}

struct partition {
    Uns8 boot_ind;        /* 0x80 - active */
    Uns8 head;        /* starting head */
    Uns8 sector;        /* starting sector */
    Uns8 cyl;        /* starting cylinder */
    Uns8 sys_ind;        /* What partition type */
    Uns8 end_head;        /* end head */
    Uns8 end_sector;    /* end sector */
    Uns8 end_cyl;        /* end cylinder */
    Uns32 start_sect;    /* starting sector counting from 0 */
    Uns32 nr_sects;        /* nr of sectors in partition */
} __attribute__((packed));

/* try to guess the disk logical geometry from the MSDOS partition table. Return 0 if OK, -1 if could not guess */
static Int32 guess_disk_lchs(IDEStateP s,
                           Int32 *pcylinders, Int32 *pheads, Int32 *psectors)
{
    Uns8 buf[512];
    Int32 i, heads, sectors, cylinders;

    Int32 ret = bdrv_read(s->bs, 0, buf, 1);
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "guess_disk_lchs:%d bdrv_read returns %d", s->ifn, ret);
    if (ret < 0)
        return -1;
    /* test msdos magic */
    if (buf[510] != 0x55 || buf[511] != 0xaa) {
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "No DOS partition");
        return -1;
    }
    for(i = 0; i < 4; i++) {
        struct partition *p = ((struct partition *)(buf + 0x1be)) + i;
        Uns32 nr_sects = le32_to_cpu(p->nr_sects);
        if (nr_sects && p->end_head) {
            /* We make the assumption that the partition terminates on
               a cylinder boundary */
            heads = p->end_head + 1;
            sectors = p->end_sector & 63;
            if (sectors == 0)
                continue;
            cylinders = s->nb_sectors / (heads * sectors);
            if (cylinders < 1 || cylinders > 16383)
                continue;
            *pheads = heads;
            *psectors = sectors;
            *pcylinders = cylinders;
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX, "from partition table: hds:%d sec:%d cyl:%d", heads, sectors, cylinders);
            return 0;
        }
    }
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "No partition table");
    return -1;
}

static void initIDEchannel(
    IDEStateP ide_state,
    BlockDriverStateP hd0,
    BlockDriverStateP hd1
) {
    IDEStateP s;
    static Int32 drive_serial = 1;
    Int32 i, cylinders, heads, secs, translation, lba_detected = 0;
    Uns64 nb_sectors;

    for(i = 0; i < 2; i++) {
        s = ide_state + i;
        if (i == 0)
            s->bs = hd0;
        else
            s->bs = hd1;
        if (s->bs) {
            bdrv_get_geometry(s->bs, &nb_sectors);
            s->nb_sectors = nb_sectors;
            /* if a geometry hint is available, use it */
            bdrv_get_geometry_hint(s->bs, &cylinders, &heads, &secs);
            translation = bdrv_get_translation_hint(s->bs);
            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX,
                    "ifn:%d cylinders:%d  sectors:%d  heads:%d  total:%lld",
                    s->ifn, cylinders, secs, heads, nb_sectors
                );
            }
            if (cylinders != 0) {
                s->cylinders = cylinders;
                s->heads     = heads;
                s->sectors   = secs;
            } else {
                if (guess_disk_lchs(s, &cylinders, &heads, &secs) == 0) {
                    if (heads > 16) {
                        /* if heads > 16, it means that a BIOS LBA
                           translation was active, so the default
                           hardware geometry is OK */
                        lba_detected = 1;
                        goto default_geometry;
                    } else {
                        s->cylinders = cylinders;
                        s->heads     = heads;
                        s->sectors   = secs;
                        /* disable any translation to be in sync with
                           the logical geometry */
                        if (translation == BIOS_ATA_TRANSLATION_AUTO) {
                            bdrv_set_translation_hint(s->bs, BIOS_ATA_TRANSLATION_NONE);
                        }
                    }
                } else {
                default_geometry:
                    /* if no geometry, use a standard physical disk geometry */
                    cylinders = nb_sectors / (16 * 63);
                    if (cylinders > 16383)
                        cylinders = 16383;
                    else if (cylinders < 2)
                        cylinders = 2;
                    s->cylinders = cylinders;
                    s->heads = 16;
                    s->sectors = 63;
                    if ((lba_detected == 1) && (translation == BIOS_ATA_TRANSLATION_AUTO)) {
                        if ((s->cylinders * s->heads) <= 131072) {
                            bdrv_set_translation_hint(s->bs, BIOS_ATA_TRANSLATION_LARGE);
                        } else {
                            bdrv_set_translation_hint(s->bs, BIOS_ATA_TRANSLATION_LBA);
                        }
                    }
                }
                bdrv_set_geometry_hint(s->bs, s->cylinders, s->heads, s->sectors);
            }
            if (bdrv_get_type_hint(s->bs) == BDRV_TYPE_CDROM) {
                s->is_cdrom = 1;
                bdrv_set_change_cb(s->bs, cdrom_change_cb, s);
            }
        } else {
            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, "ifn:%d Absent", s->ifn);
            }
        }
        s->drive_serial = drive_serial++;
        //s->sector_write_timer = qemu_new_timer(vm_clock,
        //                                       ide_sector_write_timer_cb, s);
        ide_reset(s);
    }
}

static void ide_dma_start(IDEStateP s, BlockDriverCompletionFunc *dma_cb)
{
    BMDMAState *bm = s->bmdma;
    if(!bm)
        return;
    setDMAcb(bm, s, dma_cb);

    bm->cur_prd_last = 0;
    bm->cur_prd_addr = 0;
    bm->cur_prd_len = 0;
    if (bm->dmaStatus & BM_STATUS_DMAING) {
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "ide_dma_start ch%d ifn:%d  ns:%d",
                s->ifn, bm->chn, s->nsector);
        bm->dma_cb(bm, 0);
    } else {
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "ide_dma_start ch%d ifn:%d NOT START",
               s->ifn, bm->chn);
    }
}



static void bmdma_cmd_writeb(Uns8 ch, Uns32 val)
{
    BMDMAState *bm = &bmdma[ch];
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "bmdma_cmd_writeb ch:%d", ch);
    if (!(val & BM_CMD_START)) {
        if (bm->dmaStatus & BM_STATUS_DMAING) {
            bm->dmaStatus &= ~BM_STATUS_DMAING;
            /* cancel DMA request */
            clrDMAcb(bm);
            bhmMessage("W", PREFIX,"Cannot cancel request.");
        }
        bm->cmd = val & 0x09;
    } else {
        if (!(bm->dmaStatus & BM_STATUS_DMAING)) {
            bm->dmaStatus |= BM_STATUS_DMAING;
            /* start dma transfer */
            if (bm->dma_cb) {
                if(PSE_DIAG_MEDIUM) {
                    IDEStateP s  = bm->ide_if;
                    bhmMessage("I", PREFIX, "dma start.ns:%d", s->nsector);
                }
                bm->dma_cb(bm, 0);
            }
        }
        bm->cmd = val & 0x09;
    }
}

///////////////////////////////////// IOSPACE REGISTERS /////////////////////////////////////////

#define IO1_REGS_SIZE   0x20
#define IO2_REGS_SIZE   0x08
#define IO3_REGS_SIZE   0x01
#define IO4_REGS_SIZE   0x08

//
// 2 channels for each register region
//
static Uns8 io1Regs[2][IO1_REGS_SIZE];
static Uns8 io2Regs[2][IO2_REGS_SIZE];
static Uns8 io3Regs[2];
static Uns8 io4Regs[2][IO4_REGS_SIZE];

//
// The PCI IO callback
//
static PPM_WRITE_CB(io1RegWrite) {
    Uns32 ch     = PTR_TO_UNS32(user);
    Uns32 offset = addr - (void*)&io1Regs[ch];
    bhmMessage("W", "DMA_UNS", "PCI DMA ch:%d (%d) 0x%x <= 0x%x", ch, bytes, offset, data);
}

static PPM_READ_CB(io1RegRead) {
    Uns32 ch     = PTR_TO_UNS32(user);
    Uns32 offset = addr - (void*)&io1Regs[ch];
    bhmMessage("W", "DMA_UNS", "PCI DMA (%d) 0x%x", bytes, offset);
    return 0;
}

static PPM_WRITE_CB(io2RegWrite) {
    Uns32 ch     = PTR_TO_UNS32(user);
    Uns32 offset = addr - (void*)&io2Regs[ch];

    if(offset == 0) {
        if(bytes == 2) {
            ide_data_writew(ch, data);
        } else if(bytes ==4) {
            ide_data_writel(ch, data);
        } else {
            if (!artifactAccess) {
                bhmMessage("W", PREFIX "_IO2RWB", "Register Write %d bytes not supported", bytes);
            }
        }
    } else {
        ide_ioport_write(ch, offset, data);
    }
}

static PPM_READ_CB(io2RegRead) {
    Uns32 ch     = PTR_TO_UNS32(user);
    Uns32 offset = addr - (void*)&io2Regs[ch];
    Uns32 result = 0;

   if(offset == 0) {
        if(bytes == 2) {
            result = ide_data_readw(ch, offset);
        } else if (bytes == 4) {
            result = ide_data_readl(ch, offset);
        } else {
            if (!artifactAccess){
                bhmMessage("W", PREFIX "_IO2RRB", "Register Read %d bytes not supported", bytes);
            }
        }
    } else {
        result = ide_ioport_read(ch, offset);
    }
    return result;
}

static PPM_WRITE_CB(io3RegWrite) {
    Uns32 ch = PTR_TO_UNS32(user);
    ide_cmd_write(ch, data);
}

static PPM_READ_CB(io3RegRead) {
    Uns32 ch = PTR_TO_UNS32(user);
    Uns32 result = ide_status_read(ch);

    return result;
}

static PPM_WRITE_CB(io4RegWrite) {
    Uns32 ch     = PTR_TO_UNS32(user);
    Uns32 offset = addr - (void*)&io4Regs[ch];

    if(offset == 0) {
        bmdma_cmd_writeb(ch, data);
    } else {
        if(bytes ==1 ) {
            bmdma_writeb(ch, offset, data);
        } else if (bytes == 4) {
            bmdma_addr_writel(ch, offset, data);
        } else {
            bhmMessage("E", PREFIX, "%d Unsupported Write", bytes);
        }
    }
}

static PPM_READ_CB(io4RegRead) {
    Uns32 ch     = PTR_TO_UNS32(user);
    Uns32 offset = addr - (void*)&io4Regs[ch];
    Uns32 result;

    if(bytes == 1) {
        result = bmdma_readb(ch, offset);
    } else if (bytes == 4) {
        result = bmdma_addr_readl(ch, offset);
    } else {
        bhmMessage("E", PREFIX, "%d Unsupported Read", bytes);
        result = 0;
    }
    return result;
}

static void installRegisterCallbacks(Uns32 ch)
{
    // 0x000 & 0x0c0 : ISA DMA : does not do anything!
    ppmInstallWriteCallback(io1RegWrite, UNS32_TO_PTR(ch), &io1Regs[ch], IO1_REGS_SIZE);
    ppmInstallReadCallback (io1RegRead,  UNS32_TO_PTR(ch), &io1Regs[ch], IO1_REGS_SIZE);

    // 0x1f0 & 0x170 : IDE Control
    ppmInstallWriteCallback(io2RegWrite, UNS32_TO_PTR(ch), &io2Regs[ch], IO2_REGS_SIZE);
    ppmInstallReadCallback (io2RegRead,  UNS32_TO_PTR(ch), &io2Regs[ch], IO2_REGS_SIZE);

    // 0x376 & 0x3f6 : IDE Command
    ppmInstallWriteCallback(io3RegWrite, UNS32_TO_PTR(ch), &io3Regs[ch], IO3_REGS_SIZE);
    ppmInstallReadCallback (io3RegRead,  UNS32_TO_PTR(ch), &io3Regs[ch], IO3_REGS_SIZE);

    // dynamic mapped : BMDMA
    ppmInstallWriteCallback(io4RegWrite, UNS32_TO_PTR(ch), &io4Regs[ch], IO4_REGS_SIZE);
    ppmInstallReadCallback (io4RegRead,  UNS32_TO_PTR(ch), &io4Regs[ch], IO4_REGS_SIZE);
}

//
// Fixed register regions (I think)
//
static void installRegisterRegions(Uns8 ch)
{
    Uns32 io1 = (ch==0) ? 0x000 : 0x0c0;
    Uns32 io2 = (ch==0) ? 0x1f0 : 0x170;
    Uns32 io3 = (ch==0) ? 0x3f6 : 0x376;

    Uns32      base   = PCI_IO_BASE_ADDR;
    const char *port  = BUS_PORT_NAME;

    ppmCreateDynamicSlavePort(port, base+io1, IO1_REGS_SIZE, &io1Regs[ch]);
    ppmCreateDynamicSlavePort(port, base+io2, IO2_REGS_SIZE, &io2Regs[ch]);
    ppmCreateDynamicSlavePort(port, base+io3, IO3_REGS_SIZE, &io3Regs[ch]);
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Installing ch %d IO1 0x%x at 0x%x", ch, IO1_REGS_SIZE, base+io1);
        bhmMessage("I", PREFIX, "Installing ch %d IO2 0x%x at 0x%x", ch, IO2_REGS_SIZE, base+io2);
        bhmMessage("I", PREFIX, "Installing ch %d IO3 0x%x at 0x%x", ch, IO3_REGS_SIZE, base+io3);
    }
}

static void installIOregisters(void)
{
    Uns8 ch;
    for(ch=0; ch < 2; ch++) {
        installRegisterCallbacks(ch);
        installRegisterRegions(ch);
    }
}

///////////////////////////////////// PCI ////////////////////////////////////


static Uns8 readPCIconfig(Uns32 offset)
{
    return CONFIG_ACCESS_8(offset);
}

static void writePCIconfig(Uns32 offset, Uns8 d)
{
    CONFIG_ACCESS_8(offset) = d;
}

static Uns32 bmdma_readb(Uns8 ch, Uns32 addr)
{
    BMDMAState *bm = &bmdma[ch];
    Uns32 val;

    switch(addr & 3) {
        case 0:
            val = bm->cmd;
            break;
        case 1:
            if (device_type == IDE_TYPE_CMD646) {
                val = readPCIconfig(MRDMODE);
            } else {
                bhmMessage("w", PREFIX, "Reading unsupported register");
                val = 0xff;
            }
            break;
        case 2:
            val = bm->dmaStatus;
            break;
        case 3:
            if (device_type == IDE_TYPE_CMD646) {
                if (ch == 0)
                    val = readPCIconfig(UDIDETCR0);
                else
                    val = readPCIconfig(UDIDETCR1);
            } else {
                bhmMessage("w", PREFIX, "Reading unsupported register");
                val = 0xff;
            }
            break;
        default:
            bhmMessage("w", PREFIX, "Reading unsupported register");
            val = 0xff;
            break;
    }
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX,"bmdma: ch:%d  readb 0x%02x : 0x%02x", bm->chn, addr, val);
    return val;
}

static void bmdma_writeb(Uns8 ch, Uns32 addr, Uns32 val)
{
    BMDMAStateP bm = &bmdma[ch];

    if(PSE_DIAG_HIGH) {
         bhmMessage("I", PREFIX,"bmdma: ch:%d  writeb 0x%02x : 0x%02x", bm->chn, addr, val);
    }
    switch(addr & 3) {
        case 1:
            if (device_type == IDE_TYPE_CMD646) {
                Uns8 tmp = readPCIconfig(MRDMODE);
                writePCIconfig(MRDMODE, (tmp & ~0x30) | (val & 0x30));
                cmd646_update_irq();
            }
            break;
        case 2:
            bm->dmaStatus = (val & 0x60) | (bm->dmaStatus & 1) | (bm->dmaStatus & ~val & 0x06);
            break;
        case 3:
            if (device_type == IDE_TYPE_CMD646) {
                if (ch == 0)
                    writePCIconfig(UDIDETCR0, val);
                else
                    writePCIconfig(UDIDETCR1, val);
            }
            break;
    }
}

static Uns32 bmdma_addr_readl(Uns8 ch, Uns32 addr)
{
    BMDMAState *bm = &bmdma[ch];
    Uns32 val = bm->addr;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,"bmdma: ch:%d  bmdma_addr_readl => 0x%x", bm->chn, val);
    }
    return val;
}

static void bmdma_addr_writel(Uns8 ch, Uns32 addr, Uns32 val)
{
    BMDMAState *bm = &bmdma[ch];
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,"bmdma: ch:%d  bmdma_addr_writel <= 0x%x", bm->chn, val);
    }
    bm->addr = val & ~3;
    bm->cur_addr = bm->addr;
}

/* XXX: call it also when the MRDMODE is changed from the PCI config
   registers */
static void cmd646_update_irq(void)
{
    Uns8 mode = readPCIconfig(MRDMODE);
    Int32 pci_level = ((mode & MRDMODE_INTR_CH0) && !(mode & MRDMODE_BLK_CH0))
                   || ((mode & MRDMODE_INTR_CH1) && !(mode & MRDMODE_BLK_CH1));
    setInt(0, pci_level);
}

/* the PCI irq level is the logical OR of the two channels */
static USED void cmd646_set_irq(Int32 channel, Int32 level)
{
    Int32 irq_mask = MRDMODE_INTR_CH0 << channel;
    Uns8 mode = readPCIconfig(MRDMODE);
    if (level) {
        mode |= irq_mask;
    } else {
        mode &= ~irq_mask;
    }
    writePCIconfig(MRDMODE, mode);
    cmd646_update_irq();
}

//
// TODO : should be called from reset
//
static void piixReset(void)
{
    pciConfig.command        = 0x0000;
    pciConfig.status         = 0x0280;
    pciConfig.baseAddress[4] = 0x00000001;
}

static void pciInit(void)
{
    device_type            = IDE_TYPE_PIIX4;
    pciConfig.vendorID     = 0x8086;
    pciConfig.deviceID     = 0x7111;
    pciConfig.classCode[0] = 0x80;
    pciConfig.classCode[1] = 0x01;
    pciConfig.classCode[2] = 0x01;
    pciConfig.headerType   = 0x00;
    pciInstallRegion(0x20, 0xfffffff1, &io4Regs, NULL, IO4_REGS_SIZE*2);

    // Writable regs:
    // register 0x40 IDETIM
    // register 0x44 SIDETIM
    // register 0x48 UDMACTL
    // register 0x4A UDMATIM

    pciInstallUserWritable(0x40,12, NULL, NULL);

    piixReset();
}

static void connectBusMaster(void)
{
    masterHandle = handles.dmaPort;

    if(!masterHandle) {
        bhmMessage("F", PREFIX, "Failed to open master port\n");
    }
}


static void connectNets(void)
{
    // interrupts are optional
    interrupts[0].handle = handles.intOut0;
    interrupts[1].handle = handles.intOut1;

    interrupts[0].v = 0;
    interrupts[1].v = 0;
}

static void initIDE(void)
{
    // 1st 2 ide channels use irq0, last 2 use irq1
    ide_ifs[0].irqNumber = 0;
    ide_ifs[1].irqNumber = 0;
    ide_ifs[2].irqNumber = 1;
    ide_ifs[3].irqNumber = 1;

    Uns32 i;

    // channel numbering is only for debug output.
    for(i=0; i < 4; i++) {
        ide_ifs[i].ifn  = i;
    }

    // 1st 2 ide channels use dma0, last 2 use dma1
    for(i=0; i < 2; i++) {
        BMDMAState *bm = &bmdma[i];
        ide_ifs[2 * i    ].bmdma = bm;
        ide_ifs[2 * i + 1].bmdma = bm;
        bm->chn = i;
    }
}

//
// Look for hard-drives. Each is a file, named using the DRIVE_NAME_ATTR attribute
//
static void initDrives(void)
{
    Uns32 i;

    for(i = 0; i < MAX_DRIVES; i++) {
        char attr[128];
        char value[BHM_MAX_PATH];
        sprintf(attr, DRIVE_NAME_ATTR, i);
        if(bhmStringParamValue(attr, value, sizeof(value))) {
            hd_table[i].bdrv = bdrv_open(i, value, 0);
            if (hd_table[i].bdrv) {
                if(PSE_DIAG_LOW) {
                    bhmMessage("I", PREFIX, "Drive %d using file '%s'", i, value);
                }
            } else {
                bhmMessage("W", PREFIX, "Failed to open file '%s'", value);
            }
        }
        sprintf(attr, DRIVE_DELTA_ATTR, i);
        if(bhmStringParamValue(attr, value, sizeof(value))) {
            bhmMessage("I", PREFIX, "Delta writes unimplemented");
        }
    }
}

static void ideStats(void)
{
    Uns8 i;
    bhmMessage("I", PREFIX, "IDE statistics");
    bhmPrintf("irq    ocurrences\n");
    for(i=0; i < 2; i++) {
       bhmPrintf("%d      %d\n", i, interrupts[i].count);
    }

    bhmPrintf(    "%2s %6s %6s %9s %10s\n",
        "ch", "reads", "writes","readBytes", "writeBytes"
    );
    for(i=0; i < 2; i++) {
        bhmPrintf("%2d %6u %6u %9u %10u\n",
            i,
            bmdma[i].reads,
            bmdma[i].writes,
            bmdma[i].totalReadBytes,
            bmdma[i].totalWriteBytes
        );
    }
}



PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    initDrives();
    initIDE();
    pciInit();
    initIDEchannel(&ide_ifs[0], hd_table[0].bdrv, hd_table[1].bdrv);
    initIDEchannel(&ide_ifs[2], hd_table[2].bdrv, hd_table[3].bdrv);
    pciConnectConfigSlavePort(PREFIX, NULL);
    pciInstallUserWritable(0x48, 4, NULL, NULL);
    pciInstallUserWritable(0x54, 4, NULL, NULL);
    connectBusMaster();
    connectNets();
    installIOregisters();
}

PPM_DESTRUCTOR_CB(destructor) {
    if (PSE_DIAG_LOW) {
        bdrvStats();
        ideStats();
    }
    bdrvShutdown();
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    if(phase==PPM_POST_SAVE_RESTORE) {
        bdrv_restore();
    }
}

