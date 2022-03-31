/*
 * QEMU AMD PC-Net II (Am79C970A) emulation
 *
 * Copyright (c) 2004 Antony T Curtis
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

/* This software was written to be compatible with the specification:
 * AMD Am79C970A PCnet-PCI II Ethernet Controller Data-Sheet
 * AMD Publication# 19436  Rev:E  Amendment/0  Issue Date: June 2000
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pse.igen.h"

#include "pci.h"
#include "net.h"

#ifndef USED
    #define USED     __attribute__((used))
#endif

#define PREFIX               "NET"
#define TIME_FMT             "%0.0f:"

#define MIN(_a,_b)   (((_a) < (_b)) ? (_a) : (_b))

#include "netConstants.h"

typedef struct interruptS {
    ppmNetHandle handle;
    Bool         v;       // current value
} intStr, *intStrP;


typedef struct PCNetState_st {
    Int32    rap,
             isr,
             lnkst,
             xmit_pos, recv_pos;
    Uns32    rdra, tdra;
    Uns8     prom[16];
    Uns16    csr[128];
    Uns16    bcr[32];
    Uns8     buffer[4096];
    Uns64    timer;
    Bool     tx_busy;
    intStr   interrupt;         // interrupt output
    Int32    ethHandle;

} PCNetState, *PCNetStateP;

struct ether_header {
    Uns8 ether_dhost[6];
    Uns8 ether_shost[6];
    Uns16 ether_type;
};

#define PHYSADDR(_S,_A) phsAddr(_S,_A)

static inline Uns32 phsAddr(PCNetState *s, Uns32 addr)
{
    if (!(s->bcr[BCR_SWS] & 0x0100))
        addr |= ((0xff00 & (Uns32)(s)->csr[2])<<16);
    return addr;
}

struct pcnet_initblk16 {
    Uns16 mode;
    Uns16 padr[3];
    Uns16 ladrf[4];
    Uns32 rdra;
    Uns32 tdra;
};

struct pcnet_initblk32 {
    Uns16 mode;
    Uns8 rlen;
    Uns8 tlen;
    Uns16 padr[3];
    Uns16 _res;
    Uns16 ladrf[4];
    Uns32 rdra;
    Uns32 tdra;
};

struct pcnet_TMD {
    Uns32 tbadr;
    Int16 length;
    Int16 status;
    Uns32 misc;
    Uns32 res;
};

struct pcnet_RMD {
    Uns32 rbadr;
    Int16 buf_length;
    Int16 status;
    Uns32 msg_length;
    Uns32 res;
};

///////////////////////// GLOBALS //////////////////////////

PCNetState netState = {0};

//
// MAC is supplied as an integer, then loaded into its array
//
static void setMac(Uns64 macInt, Uns8 *macArray)
{
    Uns32 i;
    if (macInt & 0xFFFF000000000000LL) {
        bhmMessage("F", PREFIX, "Illegal MAC address: must be 0x000000000000 >= addr >= 0xFFFFFFFFFFFF");
    }
    for(i=0; i < 6; i++) {
        macArray[5-i] = macInt & 0xff;
        macInt >>= 8;
    }
}

///////////////////////////////////////////////////////////////////////////

static void printPacket(const Uns8 *buf)
{
    Int32 i;
    Int32 show = 32;
    for(i = 0; i < show; i++) {
        bhmPrintf(" %02x", *buf++);
    }
    bhmPrintf("\n");
}

static void printTMD(struct pcnet_TMD *t)
{
    bhmMessage("I", PREFIX, TIME_FMT
        "TMD0 : TBADR=0x%08x",
        bhmGetCurrentTime(),
        t->tbadr
    );
    bhmMessage("I", PREFIX,
        "TMD1 : OWN=%d, ERR=%d, FCS=%d, LTI=%d, "
        "ONE=%d, DEF=%d, STP=%d, ENP=%d, BPE=%d, BCNT=%d",
        GET_FIELD(t->status, TMDS, OWN),
        GET_FIELD(t->status, TMDS, ERR),
        GET_FIELD(t->status, TMDS, NOFCS),
        GET_FIELD(t->status, TMDS, LTINT),
        GET_FIELD(t->status, TMDS, ONE),
        GET_FIELD(t->status, TMDS, DEF),
        GET_FIELD(t->status, TMDS, STP),
        GET_FIELD(t->status, TMDS, ENP),
        GET_FIELD(t->status, TMDS, BPE),
        4096-GET_FIELD(t->length, TMDL, BCNT)
    );
    bhmMessage("I", PREFIX,
        "TMD2 : BUF=%d, UFL=%d, EXD=%d, LCO=%d, "
        "LCA=%d, RTR=%d, TDR=%d, TRC=%d",
        GET_FIELD(t->misc, TMDM, BUFF),
        GET_FIELD(t->misc, TMDM, UFLO),
        GET_FIELD(t->misc, TMDM, EXDEF),
        GET_FIELD(t->misc, TMDM, LCOL),
        GET_FIELD(t->misc, TMDM, LCAR),
        GET_FIELD(t->misc, TMDM, RTRY),
        GET_FIELD(t->misc, TMDM, TDR),
        GET_FIELD(t->misc, TMDM, TRC)
    );
}

#define PRINT_RMD(R) bhmMessage("I", PREFIX,            \
        "RMD0 : RBADR=0x%08x\n"                         \
        "RMD1 : OWN=%d, ERR=%d, FRAM=%d, OFLO=%d, "     \
        "CRC=%d, BUFF=%d, STP=%d, ENP=%d,\n       "     \
        "BPE=%d, PAM=%d, LAFM=%d, BAM=%d, ONES=%d, BCNT=%d\n" \
        "RMD2 : RCC=%d, RPC=%d, MCNT=%d, ZEROS=%d\n",   \
        (R)->rbadr,                                     \
        GET_FIELD((R)->status, RMDS, OWN),              \
        GET_FIELD((R)->status, RMDS, ERR),              \
        GET_FIELD((R)->status, RMDS, FRAM),             \
        GET_FIELD((R)->status, RMDS, OFLO),             \
        GET_FIELD((R)->status, RMDS, CRC),              \
        GET_FIELD((R)->status, RMDS, BUFF),             \
        GET_FIELD((R)->status, RMDS, STP),              \
        GET_FIELD((R)->status, RMDS, ENP),              \
        GET_FIELD((R)->status, RMDS, BPE),              \
        GET_FIELD((R)->status, RMDS, PAM),              \
        GET_FIELD((R)->status, RMDS, LFAM),             \
        GET_FIELD((R)->status, RMDS, BAM),              \
        GET_FIELD((R)->buf_length, RMDL, ONES),         \
        4096-GET_FIELD((R)->buf_length, RMDL, BCNT),    \
        GET_FIELD((R)->msg_length, RMDM, RCC),          \
        GET_FIELD((R)->msg_length, RMDM, RPC),          \
        GET_FIELD((R)->msg_length, RMDM, MCNT),         \
        GET_FIELD((R)->msg_length, RMDM, ZEROS))

#define PCNET_RECV_STORE   \
{ \
    Int32 count = MIN(4096 - GET_FIELD(rmd.buf_length, RMDL, BCNT),size); \
    dmaWrite(PHYSADDR(s, rmd.rbadr), src, count, "PCNET_RECV_STORE", 0);  \
    src += count; size -= count;                                \
    SET_FIELD(&rmd.msg_length, RMDM, MCNT, count);              \
    SET_FIELD(&rmd.status, RMDS, OWN, 0);                       \
    RMDSTORE(&rmd, PHYSADDR(s,crda));                           \
    pktcount++;                                                 \
}


//////////////////////////////////////// UTILS ////////////////////////////////////////

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

static inline void le16_to_cpus(Uns16 *v)
{
    //Uns16 t = *v;
    //*v = ((t & 0x00ffU) << 8) | ((t & 0xff00U) >> 8);
}

static inline void le32_to_cpus(Uns32 *v)
{
    //Uns32 t = *v;
    //*v = ((t & 0x000000ffUL) << 24)
    //   | ((t & 0x0000ff00UL) << 8)
    //   | ((t & 0x00ff0000UL) >> 8)
    //   | ((t & 0xff000000UL) >> 24);
}

static inline Uns16 be16_to_cpu(Uns16 v)
{
    return v;
}

static void setInt(Uns8 v)
{
    if(netState.interrupt.handle) {
        if (v != netState.interrupt.v) {
            netState.interrupt.v = v;
            ppmWriteNet(netState.interrupt.handle, v);
        }
    }
}

//
// Some indication of the data that was DMA'd.
//
static Uns32 checksumBuffer(Uns32 bytes, void *buf)
{
    Uns8 *p = buf;
    Uns32 sum = 0;
    while(bytes-- > 0){
        sum += *p++;
    }
    return sum;
}

static void dmaRead(Addr addr, void *buf, Uns32 bytes, const char *what, Bool swap)
{
    ppmReadAddressSpace(masterHandle, addr, bytes, buf);
    if(BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, TIME_FMT "DMA read (%s) bytes:%d from:0x%llx  cksm:0x%x",
            bhmGetCurrentTime(),
            what, bytes, addr,
            checksumBuffer(bytes, buf)
        );
    }
}

static void dmaWrite(Addr addr, void *buf, Uns32 bytes, const char *what, Bool swap)
{
    if(BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, TIME_FMT "DMA write (%s) bytes:%d to:0x%llx  cksm:0x%x",
            bhmGetCurrentTime(),
            what, bytes, addr,
            checksumBuffer(bytes, buf)
        );
    }
    ppmWriteAddressSpace(masterHandle, addr, bytes, buf);
}

/////////////////////////////////////////////////////////////////////////////////////

static inline void pcnet_tmd_load(struct pcnet_TMD *tmd, Addr addr)
{
    PCNetState *s = &netState;
    if (!BCR_SSIZE32(s)) {
        struct {
            Uns32 tbadr;
            Int16 length;
            Int16 status;
        } xda;
        dmaRead(addr, &xda, sizeof(xda), "tmd_load xda", 0);
        tmd->tbadr = le32_to_cpu(xda.tbadr) & 0xffffff;
        tmd->length = le16_to_cpu(xda.length);
        tmd->status = (le32_to_cpu(xda.tbadr) >> 16) & 0xff00;
        tmd->misc = le16_to_cpu(xda.status) << 16;
        tmd->res = 0;
    } else {
        dmaRead(addr, tmd, sizeof(*tmd), "tmd_load tmd", 0);
        le32_to_cpus(&tmd->tbadr);
        le16_to_cpus((Uns16 *)&tmd->length);
        le16_to_cpus((Uns16 *)&tmd->status);
        le32_to_cpus(&tmd->misc);
        le32_to_cpus(&tmd->res);
        if (BCR_SWSTYLE(s) == 3) {
            Uns32 tmp = tmd->tbadr;
            tmd->tbadr = tmd->misc;
            tmd->misc = tmp;
        }
    }
}

static inline void pcnet_tmd_store(const struct pcnet_TMD *tmd, Addr addr)
{
    PCNetState *s = &netState;

    if (!BCR_SSIZE32(s)) {
        struct {
            Uns32 tbadr;
            Int16 length;
            Int16 status;
        } xda;
        xda.tbadr = cpu_to_le32((tmd->tbadr & 0xffffff) |
                                ((tmd->status & 0xff00) << 16));
        xda.length = cpu_to_le16(tmd->length);
        xda.status = cpu_to_le16(tmd->misc >> 16);
        dmaWrite(addr, &xda, sizeof(xda), "tmd_store xda",0);
    } else {
        struct {
            Uns32 tbadr;
            Int16 length;
            Int16 status;
            Uns32 misc;
            Uns32 res;
        } xda;
        xda.tbadr = cpu_to_le32(tmd->tbadr);
        xda.length = cpu_to_le16(tmd->length);
        xda.status = cpu_to_le16(tmd->status);
        xda.misc = cpu_to_le32(tmd->misc);
        xda.res = cpu_to_le32(tmd->res);
        if (BCR_SWSTYLE(s) == 3) {
            Uns32 tmp = xda.tbadr;
            xda.tbadr = xda.misc;
            xda.misc = tmp;
        }
        dmaWrite(addr, &xda, sizeof(xda), "tmd_store xda2",0);
    }
}

static inline void pcnet_rmd_load(PCNetState *s, struct pcnet_RMD *rmd,
                                  Addr addr)
{
    if (!BCR_SSIZE32(s)) {
        struct {
            Uns32 rbadr;
            Int16 buf_length;
            Int16 msg_length;
        } rda;
        dmaRead(addr, &rda, sizeof(rda), "rmd_load", 0);
        rmd->rbadr = le32_to_cpu(rda.rbadr) & 0xffffff;
        rmd->buf_length = le16_to_cpu(rda.buf_length);
        rmd->status = (le32_to_cpu(rda.rbadr) >> 16) & 0xff00;
        rmd->msg_length = le16_to_cpu(rda.msg_length);
        rmd->res = 0;
    } else {
        dmaRead(addr, rmd, sizeof(*rmd), "rmd_load32", 0);
        le32_to_cpus(&rmd->rbadr);
        le16_to_cpus((Uns16 *)&rmd->buf_length);
        le16_to_cpus((Uns16 *)&rmd->status);
        le32_to_cpus(&rmd->msg_length);
        le32_to_cpus(&rmd->res);
        if (BCR_SWSTYLE(s) == 3) {
            Uns32 tmp = rmd->rbadr;
            rmd->rbadr = rmd->msg_length;
            rmd->msg_length = tmp;
        }
    }
    if(BHM_DIAG_HIGH)bhmMessage("I",PREFIX, TIME_FMT
        "rmd_load rbaddr:0x%x buf:%d stat:0x%x mes:%d",
        bhmGetCurrentTime(),
        rmd->rbadr,
        rmd->buf_length,
        rmd->status,
        rmd->msg_length
    );
}

static inline void pcnet_rmd_store(PCNetState *s, struct pcnet_RMD *rmd,
                                   Addr addr)
{
    if (!BCR_SSIZE32(s)) {
        struct {
            Uns32 rbadr;
            Int16 buf_length;
            Int16 msg_length;
        } rda;
        rda.rbadr = cpu_to_le32((rmd->rbadr & 0xffffff) |
                                ((rmd->status & 0xff00) << 16));
        rda.buf_length = cpu_to_le16(rmd->buf_length);
        rda.msg_length = cpu_to_le16(rmd->msg_length);
        dmaWrite(addr, &rda, sizeof(rda), "rmd_store rda", 0);
    } else {
        struct {
            Uns32 rbadr;
            Int16 buf_length;
            Int16 status;
            Uns32 msg_length;
            Uns32 res;
        } rda;
        rda.rbadr = cpu_to_le32(rmd->rbadr);
        rda.buf_length = cpu_to_le16(rmd->buf_length);
        rda.status = cpu_to_le16(rmd->status);
        rda.msg_length = cpu_to_le32(rmd->msg_length);
        rda.res = cpu_to_le32(rmd->res);
        if (BCR_SWSTYLE(s) == 3) {
            Uns32 tmp = rda.rbadr;
            rda.rbadr = rda.msg_length;
            rda.msg_length = tmp;
        }
        dmaWrite(addr, &rda, sizeof(rda), "rmd_store rda2", 0);
    }
}

#define RMDLOAD(RMD,ADDR) pcnet_rmd_load(s,RMD,ADDR)

#define RMDSTORE(RMD,ADDR) pcnet_rmd_store(s,RMD,ADDR)

#define CHECK_RMD(ADDR,RES) do {                \
    struct pcnet_RMD rmd;                       \
    RMDLOAD(&rmd,(ADDR));                       \
    (RES) |= (GET_FIELD(rmd.buf_length, RMDL, ONES) != 15) \
          || (GET_FIELD(rmd.msg_length, RMDM, ZEROS) != 0); \
} while (0)

#define CHECK_TMD(ADDR,RES) do {                \
    struct pcnet_TMD tmd;                       \
    pcnet_tmd_load(&tmd,(ADDR));                       \
    (RES) |= (GET_FIELD(tmd.length, TMDL, ONES) != 15); \
} while (0)

#define PRINT_PKTHDR(BUF) do {                  \
    struct ether_header *hdr = (void *)(BUF); \
    bhmMessage("I", PREFIX, TIME_FMT "packet dhost=%02x:%02x:%02x:%02x:%02x:%02x, " \
           "shost=%02x:%02x:%02x:%02x:%02x:%02x, type=0x%04x",                      \
           bhmGetCurrentTime(),                                                     \
           hdr->ether_dhost[0],hdr->ether_dhost[1],hdr->ether_dhost[2], \
           hdr->ether_dhost[3],hdr->ether_dhost[4],hdr->ether_dhost[5], \
           hdr->ether_shost[0],hdr->ether_shost[1],hdr->ether_shost[2], \
           hdr->ether_shost[3],hdr->ether_shost[4],hdr->ether_shost[5], \
           be16_to_cpu(hdr->ether_type));       \
} while (0)

#define MULTICAST_FILTER_LEN 8

static inline Uns32 lnc_mchash(const Uns8 *ether_addr)
{
#define LNC_POLYNOMIAL          0xEDB88320UL
    Uns32 crc = 0xFFFFFFFF;
    Int32 idx, bit;
    Uns8 data;

    for (idx = 0; idx < 6; idx++) {
        for (data = *ether_addr++, bit = 0; bit < MULTICAST_FILTER_LEN; bit++) {
            crc = (crc >> 1) ^ (((crc ^ data) & 1) ? LNC_POLYNOMIAL : 0);
            data >>= 1;
        }
    }
    return crc;
#undef LNC_POLYNOMIAL
}

#define CRC(crc, ch)     (crc = (crc >> 8) ^ crctab[(crc ^ (ch)) & 0xff])

/* generated using the AUTODIN II polynomial
 *  x^32 + x^26 + x^23 + x^22 + x^16 +
 *  x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
 */
static USED const Uns32 crctab[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
    0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
    0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
    0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
    0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
    0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
    0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
    0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
    0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
    0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
    0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
    0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
    0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
    0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
    0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
    0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
    0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
    0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
    0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
    0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
    0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
    0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
    0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
    0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
    0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
    0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
    0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
    0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
    0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
    0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
    0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
    0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
    0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
    0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

static inline Int32 padr_match(PCNetState *s, const Uns8 *buf, Int32 size)
{
    struct ether_header *hdr = (void *)buf;
    Uns8 padr[6] = {
        s->csr[12] & 0xff, s->csr[12] >> 8,
        s->csr[13] & 0xff, s->csr[13] >> 8,
        s->csr[14] & 0xff, s->csr[14] >> 8
    };
    Int32 result = (!CSR_DRCVPA(s)) && !memcmp(hdr->ether_dhost, padr, 6);
    if(BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, TIME_FMT "packet dhost=%02x:%02x:%02x:%02x:%02x:%02x, "
           "padr=%02x:%02x:%02x:%02x:%02x:%02x   result=%d",
           bhmGetCurrentTime(),
           hdr->ether_dhost[0],hdr->ether_dhost[1],hdr->ether_dhost[2],
           hdr->ether_dhost[3],hdr->ether_dhost[4],hdr->ether_dhost[5],
           padr[0],padr[1],padr[2],padr[3],padr[4],padr[5], result);
   }
    return result;
}

static inline Int32 padr_bcast(PCNetState *s, const Uns8 *buf, Int32 size)
{
    static const Uns8 BCAST[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    struct ether_header *hdr = (void *)buf;
    Int32 result = !CSR_DRCVBC(s) && !memcmp(hdr->ether_dhost, BCAST, 6);
    if(BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, TIME_FMT "padr_bcast result=%d", bhmGetCurrentTime(), result);
    }
    return result;
}

static inline Int32 ladr_match(PCNetState *s, const Uns8 *buf, Int32 size)
{
    struct ether_header *hdr = (void *)buf;
    if ((*(hdr->ether_dhost)&0x01) &&
        ( s->csr[8] || s->csr[9] || s->csr[10] || s->csr[11])) {
        Uns8 ladr[8] = {
            s->csr[8] & 0xff, s->csr[8] >> 8,
            s->csr[9] & 0xff, s->csr[9] >> 8,
            s->csr[10] & 0xff, s->csr[10] >> 8,
            s->csr[11] & 0xff, s->csr[11] >> 8
        };
        Int32 index = lnc_mchash(hdr->ether_dhost) >> 26;
        return !!(ladr[index >> 3] & (1 << (index & 7)));
    }
    return 0;
}

static inline Addr pcnet_rdra_addr(PCNetState *s, Int32 idx)
{
    while (idx < 1) idx += CSR_RCVRL(s);
    return s->rdra + ((CSR_RCVRL(s) - idx) * (BCR_SWSTYLE(s) ? 16 : 8));
}


static void poll(void);
static void poll_timer(void);

static Uns32 pcnet_csr_readw(PCNetState *s, Uns32 rap);
static void pcnet_csr_writew(PCNetState *s, Uns32 rap, Uns32 new_value);
static void pcnet_bcr_writew(PCNetState *s, Uns32 rap, Uns32 val);
static Uns32 pcnet_bcr_readw(PCNetState *s, Uns32 rap);

static void softReset(PCNetState *s)
{
    if(BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, TIME_FMT "Soft reset", bhmGetCurrentTime());

    s->lnkst = 0x40;
    s->rdra = 0;
    s->tdra = 0;
    s->rap = 0;

    s->bcr[BCR_BSBC] &= ~0x0080;

    s->csr[0]   = 0x0004;
    s->csr[3]   = 0x0000;
    s->csr[4]   = 0x0115;
    s->csr[5]   = 0x0000;
    s->csr[6]   = 0x0000;
    s->csr[8]   = 0;
    s->csr[9]   = 0;
    s->csr[10]  = 0;
    s->csr[11]  = 0;
    s->csr[12]  = le16_to_cpu(((Uns16 *)&s->prom[0])[0]);
    s->csr[13]  = le16_to_cpu(((Uns16 *)&s->prom[0])[1]);
    s->csr[14]  = le16_to_cpu(((Uns16 *)&s->prom[0])[2]);
    s->csr[15] &= 0x21c4;
    s->csr[72]  = 1;
    s->csr[74]  = 1;
    s->csr[76]  = 1;
    s->csr[78]  = 1;
    s->csr[80]  = 0x1410;
    s->csr[88]  = 0x1003;
    s->csr[89]  = 0x0262;
    s->csr[94]  = 0x0000;
    s->csr[100] = 0x0200;
    s->csr[103] = 0x0105;
    s->csr[103] = 0x0105;
    s->csr[112] = 0x0000;
    s->csr[114] = 0x0000;
    s->csr[122] = 0x0000;
    s->csr[124] = 0x0000;

    s->tx_busy = False;
}

static void pcnet_update_irq(PCNetState *s)
{
    Int32 isr = 0;
    s->csr[0] &= ~0x0080;

#if 1
    if (((s->csr[0] & ~s->csr[3]) & 0x5f00) ||
        (((s->csr[4]>>1) & ~s->csr[4]) & 0x0115) ||
        (((s->csr[5]>>1) & s->csr[5]) & 0x0048))
#else
    if ((!(s->csr[3] & 0x4000) && !!(s->csr[0] & 0x4000)) /* BABL */ ||
        (!(s->csr[3] & 0x1000) && !!(s->csr[0] & 0x1000)) /* MISS */ ||
        (!(s->csr[3] & 0x0100) && !!(s->csr[0] & 0x0100)) /* IDON */ ||
        (!(s->csr[3] & 0x0200) && !!(s->csr[0] & 0x0200)) /* TINT */ ||
        (!(s->csr[3] & 0x0400) && !!(s->csr[0] & 0x0400)) /* RINT */ ||
        (!(s->csr[3] & 0x0800) && !!(s->csr[0] & 0x0800)) /* MERR */ ||
        (!(s->csr[4] & 0x0001) && !!(s->csr[4] & 0x0002)) /* JAB */ ||
        (!(s->csr[4] & 0x0004) && !!(s->csr[4] & 0x0008)) /* TXSTRT */ ||
        (!(s->csr[4] & 0x0010) && !!(s->csr[4] & 0x0020)) /* RCVO */ ||
        (!(s->csr[4] & 0x0100) && !!(s->csr[4] & 0x0200)) /* MFCO */ ||
        (!!(s->csr[5] & 0x0040) && !!(s->csr[5] & 0x0080)) /* EXDINT */ ||
        (!!(s->csr[5] & 0x0008) && !!(s->csr[5] & 0x0010)) /* MPINT */)
#endif
    {

        isr = CSR_INEA(s);
        s->csr[0] |= 0x0080;
    }

    if (!!(s->csr[4] & 0x0080) && CSR_INEA(s)) { /* UINT */
        s->csr[4] &= ~0x0080;
        s->csr[4] |= 0x0040;
        s->csr[0] |= 0x0080;
        isr = 1;
        if (BHM_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, TIME_FMT "user int", bhmGetCurrentTime());
    }

    if (((s->csr[5]>>1) & s->csr[5]) & 0x0500)
    {
        isr = 1;
        s->csr[0] |= 0x0080;
    }

    if (isr && isr != s->isr && BHM_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, TIME_FMT ": Interrupt", bhmGetCurrentTime());
    }
    setInt(isr);
    s->isr = isr;
}

static void pcnet_init(PCNetState *s)
{
    Int32 rlen, tlen;
    Uns16 padr[3], ladrf[4], mode;
    Uns32 rdra, tdra;

    if(BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, TIME_FMT "init addr=0x%08x",
            bhmGetCurrentTime(),
            PHYSADDR(s,CSR_IADR(s))
        );

    if (BCR_SSIZE32(s)) {
        struct pcnet_initblk32 initblk;
        dmaRead(PHYSADDR(s,CSR_IADR(s)), &initblk, sizeof(initblk), "init32", 0);
        mode = le16_to_cpu(initblk.mode);
        rlen = initblk.rlen >> 4;
        tlen = initblk.tlen >> 4;
        ladrf[0] = le16_to_cpu(initblk.ladrf[0]);
        ladrf[1] = le16_to_cpu(initblk.ladrf[1]);
        ladrf[2] = le16_to_cpu(initblk.ladrf[2]);
        ladrf[3] = le16_to_cpu(initblk.ladrf[3]);
        padr[0] = le16_to_cpu(initblk.padr[0]);
        padr[1] = le16_to_cpu(initblk.padr[1]);
        padr[2] = le16_to_cpu(initblk.padr[2]);
        rdra = le32_to_cpu(initblk.rdra);
        tdra = le32_to_cpu(initblk.tdra);
    } else {
        struct pcnet_initblk16 initblk;
        dmaRead(PHYSADDR(s,CSR_IADR(s)), &initblk, sizeof(initblk), "init", 0);
        mode = le16_to_cpu(initblk.mode);
        ladrf[0] = le16_to_cpu(initblk.ladrf[0]);
        ladrf[1] = le16_to_cpu(initblk.ladrf[1]);
        ladrf[2] = le16_to_cpu(initblk.ladrf[2]);
        ladrf[3] = le16_to_cpu(initblk.ladrf[3]);
        padr[0] = le16_to_cpu(initblk.padr[0]);
        padr[1] = le16_to_cpu(initblk.padr[1]);
        padr[2] = le16_to_cpu(initblk.padr[2]);
        rdra = le32_to_cpu(initblk.rdra);
        tdra = le32_to_cpu(initblk.tdra);
        rlen = rdra >> 29;
        tlen = tdra >> 29;
        rdra &= 0x00ffffff;
        tdra &= 0x00ffffff;
    }

    if(BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, TIME_FMT "rlen=%d tlen=%d", bhmGetCurrentTime(), rlen, tlen);

    CSR_RCVRL(s) = (rlen < 9) ? (1 << rlen) : 512;
    CSR_XMTRL(s) = (tlen < 9) ? (1 << tlen) : 512;
    s->csr[ 6] = (tlen << 12) | (rlen << 8);
    s->csr[15] = mode;
    s->csr[ 8] = ladrf[0];
    s->csr[ 9] = ladrf[1];
    s->csr[10] = ladrf[2];
    s->csr[11] = ladrf[3];
    s->csr[12] = padr[0];
    s->csr[13] = padr[1];
    s->csr[14] = padr[2];
    s->rdra = PHYSADDR(s, rdra);
    s->tdra = PHYSADDR(s, tdra);

    CSR_RCVRC(s) = CSR_RCVRL(s);
    CSR_XMTRC(s) = CSR_XMTRL(s);

    if(BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, TIME_FMT "ss32=%d rdra=0x%08x[%d] tdra=0x%08x[%d]",
            bhmGetCurrentTime(),
            BCR_SSIZE32(s),
            s->rdra, CSR_RCVRL(s), s->tdra, CSR_XMTRL(s));

    s->csr[0] |= 0x0101;
    s->csr[0] &= ~0x0004;       /* clear STOP bit */
}

static void start(PCNetState *s)
{
    if(BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, TIME_FMT "starting", bhmGetCurrentTime());

    if (!CSR_DTX(s))
        s->csr[0] |= 0x0010;    /* set TXON */

    if (!CSR_DRX(s))
        s->csr[0] |= 0x0020;    /* set RXON */

    s->csr[0] &= ~0x0004;       /* clear STOP bit */
    s->csr[0] |= 0x0002;
}

static void stop(PCNetState *s)
{
    if(BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, TIME_FMT  "stopping", bhmGetCurrentTime());

    s->csr[0] &= ~0x7feb;
    s->csr[0] |= 0x0014;
    s->csr[4] &= ~0x02c2;
    s->csr[5] &= ~0x0011;
    poll_timer();
}

static void rdte_poll(PCNetState *s)
{
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "rdte_poll", bhmGetCurrentTime());

    s->csr[28] = s->csr[29] = 0;
    if (s->rdra) {
        Int32 bad = 0;

        Addr crda = pcnet_rdra_addr(s, CSR_RCVRC(s));
        Addr nrda = pcnet_rdra_addr(s, -1 + CSR_RCVRC(s));
        Addr nnrd = pcnet_rdra_addr(s, -2 + CSR_RCVRC(s));

        CHECK_RMD(PHYSADDR(s,crda), bad);
        if (!bad) {
            CHECK_RMD(PHYSADDR(s,nrda), bad);
            if (bad || (nrda == crda)) nrda = 0;
            CHECK_RMD(PHYSADDR(s,nnrd), bad);
            if (bad || (nnrd == crda)) nnrd = 0;

            s->csr[28] = crda & 0xffff;
            s->csr[29] = crda >> 16;
            s->csr[26] = nrda & 0xffff;
            s->csr[27] = nrda >> 16;
            s->csr[36] = nnrd & 0xffff;
            s->csr[37] = nnrd >> 16;

            if (bad && BHM_DIAG_LOW) {
                bhmMessage("I", PREFIX, "BAD RMD RECORDS AFTER 0x%08x",
                       PHYSADDR(s,crda));
            }
        } else {
            bhmMessage("I", PREFIX, "BAD RMD RDA=0x%08x", PHYSADDR(s,crda));
        }
    }

    if (CSR_CRDA(s)) {
        struct pcnet_RMD rmd;
        RMDLOAD(&rmd, PHYSADDR(s,CSR_CRDA(s)));
        CSR_CRBC(s) = GET_FIELD(rmd.buf_length, RMDL, BCNT);
        CSR_CRST(s) = rmd.status;
        if(BHM_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "CRDA=0x%08x CRST=0x%04x RCVRC=%d RMDL=0x%04x RMDS=0x%04x RMDM=0x%08x",
                PHYSADDR(s,CSR_CRDA(s)), CSR_CRST(s), CSR_RCVRC(s),
                rmd.buf_length, rmd.status, rmd.msg_length);
            PRINT_RMD(&rmd);
        }
    } else {
        CSR_CRBC(s) = CSR_CRST(s) = 0;
    }

    if (CSR_NRDA(s)) {
        struct pcnet_RMD rmd;
        RMDLOAD(&rmd, PHYSADDR(s,CSR_NRDA(s)));
        CSR_NRBC(s) = GET_FIELD(rmd.buf_length, RMDL, BCNT);
        CSR_NRST(s) = rmd.status;
    } else {
        CSR_NRBC(s) = CSR_NRST(s) = 0;
    }

}

static Int32 pcnet_tdte_poll(PCNetState *s)
{
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "tdte_poll", bhmGetCurrentTime());
    s->csr[34] = s->csr[35] = 0;
    if (s->tdra) {
        Addr cxda = s->tdra +
            (CSR_XMTRL(s) - CSR_XMTRC(s)) *
            (BCR_SWSTYLE(s) ? 16 : 8);
        Int32 bad = 0;
        CHECK_TMD(PHYSADDR(s, cxda),bad);
        if (!bad) {
            if (CSR_CXDA(s) != cxda) {
                s->csr[60] = s->csr[34];
                s->csr[61] = s->csr[35];
                s->csr[62] = CSR_CXBC(s);
                s->csr[63] = CSR_CXST(s);
            }
            s->csr[34] = cxda & 0xffff;
            s->csr[35] = cxda >> 16;
            if(BHM_DIAG_HIGH)
                bhmMessage("I", PREFIX, "TMD XDA=0x%08x", PHYSADDR(s,cxda));
        }
    }

    if (CSR_CXDA(s)) {
        struct pcnet_TMD tmd;

        pcnet_tmd_load(&tmd, PHYSADDR(s,CSR_CXDA(s)));

        CSR_CXBC(s) = GET_FIELD(tmd.length, TMDL, BCNT);
        CSR_CXST(s) = tmd.status;
    } else {
        CSR_CXBC(s) = CSR_CXST(s) = 0;
    }
    Bool ok = !!(CSR_CXST(s) & 0x8000);
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "tdte_poll: %s", ok ? "ok" : "-");

    return ok;
}

static USED Int32 pcnet_can_receive(void)
{
    // TODO : this should be used
    PCNetState *s = &netState;
    if (CSR_STOP(s) || CSR_SPND(s))
        return 0;

    if (s->recv_pos > 0)
        return 0;

    return sizeof(s->buffer)-16;
}

#define MIN_BUF_SIZE 60

//
// Copy a packet into the RXQ.
//
void pcnet_receive(const Uns8 *buf, Int32 size)
{
    PCNetState *s = &netState;
    Int32 is_padr = 0, is_bcast = 0, is_ladr = 0;
    Uns8 buf1[60];

    if (CSR_DRX(s) || CSR_STOP(s) || CSR_SPND(s) || !size)
        return;

    if(BHM_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, TIME_FMT "rxpkt %d bytes", bhmGetCurrentTime(), size);
        printPacket(buf);
    }
    /* if too small buffer, then expand it */
    if (size < MIN_BUF_SIZE) {
        memcpy(buf1, buf, size);
        memset(buf1 + size, 0, MIN_BUF_SIZE - size);
        buf = buf1;
        size = MIN_BUF_SIZE;
    }

    if (CSR_PROM(s)
        || (is_padr=padr_match(s, buf, size))
        || (is_bcast=padr_bcast(s, buf, size))
        || (is_ladr=ladr_match(s, buf, size))) {

        rdte_poll(s);

        if (!(CSR_CRST(s) & 0x8000) && s->rdra) {
            struct pcnet_RMD rmd;
            Int32 rcvrc = CSR_RCVRC(s)-1,i;
            Addr nrda;
            for (i = CSR_RCVRL(s)-1; i > 0; i--, rcvrc--) {
                if (rcvrc <= 1)
                    rcvrc = CSR_RCVRL(s);
                nrda = s->rdra +
                    (CSR_RCVRL(s) - rcvrc) *
                    (BCR_SWSTYLE(s) ? 16 : 8 );
                RMDLOAD(&rmd, PHYSADDR(s,nrda));
                if (GET_FIELD(rmd.status, RMDS, OWN)) {
                    if(BHM_DIAG_HIGH)
                        bhmMessage("I", PREFIX,
                            "scan buffer: RCVRC=%d PREV_RCVRC=%d",
                            rcvrc, CSR_RCVRC(s)
                        );
                    CSR_RCVRC(s) = rcvrc;
                    rdte_poll(s);
                    break;
                }
            }
        }

        if (!(CSR_CRST(s) & 0x8000)) {
            if(BHM_DIAG_HIGH)
                bhmMessage("I", PREFIX, "no buffer: RCVRC=%d", CSR_RCVRC(s));
            s->csr[0] |= 0x1000; /* Set MISS flag */
            CSR_MISSC(s)++;
        } else {
            Uns8 *src = &s->buffer[8];
            Addr crda = CSR_CRDA(s);
            struct pcnet_RMD rmd;
            Int32 pktcount = 0;

            memcpy(src, buf, size);

            /* no need to compute the CRC */
            src[size] = 0;
            src[size + 1] = 0;
            src[size + 2] = 0;
            src[size + 3] = 0;
            size += 4;
            if(BHM_DIAG_HIGH) {
                PRINT_PKTHDR(buf);
            }
            RMDLOAD(&rmd, PHYSADDR(s,crda));
            /*if (!CSR_LAPPEN(s))*/
                SET_FIELD(&rmd.status, RMDS, STP, 1);

            PCNET_RECV_STORE;
            if ((size > 0) && CSR_NRDA(s)) {
                Addr nrda = CSR_NRDA(s);
                RMDLOAD(&rmd, PHYSADDR(s,nrda));
                if (GET_FIELD(rmd.status, RMDS, OWN)) {
                    crda = nrda;
                    PCNET_RECV_STORE;
                    if ((size > 0) && (nrda=CSR_NNRD(s))) {
                        RMDLOAD(&rmd, PHYSADDR(s,nrda));
                        if (GET_FIELD(rmd.status, RMDS, OWN)) {
                            crda = nrda;
                            PCNET_RECV_STORE;
                        }
                    }
                }
            }

            RMDLOAD(&rmd, PHYSADDR(s,crda));
            if (size == 0) {
                SET_FIELD(&rmd.status, RMDS, ENP, 1);
                SET_FIELD(&rmd.status, RMDS, PAM, !CSR_PROM(s) && is_padr);
                SET_FIELD(&rmd.status, RMDS, LFAM, !CSR_PROM(s) && is_ladr);
                SET_FIELD(&rmd.status, RMDS, BAM, !CSR_PROM(s) && is_bcast);
            } else {
                SET_FIELD(&rmd.status, RMDS, OFLO, 1);
                SET_FIELD(&rmd.status, RMDS, BUFF, 1);
                SET_FIELD(&rmd.status, RMDS, ERR, 1);
            }
            RMDSTORE(&rmd, PHYSADDR(s,crda));
            s->csr[0] |= 0x0400;

            if(BHM_DIAG_HIGH) {
                bhmMessage("I", PREFIX,
                    "RCVRC=%d CRDA=0x%08x BLKS=%d",
                    CSR_RCVRC(s), PHYSADDR(s,CSR_CRDA(s)), pktcount);

                PRINT_RMD(&rmd);
            }
            while (pktcount--) {
                if (CSR_RCVRC(s) <= 1)
                    CSR_RCVRC(s) = CSR_RCVRL(s);
                else
                    CSR_RCVRC(s)--;
            }
            rdte_poll(s);
        }
    }
    poll();
    pcnet_update_irq(s);
}

static void pcnet_transmit(void)
{
    PCNetStateP s = &netState;
    Addr xmit_cxda = 0;
    Int32 count = CSR_XMTRL(s)-1;
    s->xmit_pos = -1;

    if (!CSR_TXON(s)) {
        s->csr[0] &= ~0x0008;
        if(BHM_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, TIME_FMT "transmit: !TXON", bhmGetCurrentTime());
        return;
    }

    s->tx_busy = True;

    txagain:
    if (pcnet_tdte_poll(s)) {
        struct pcnet_TMD tmd;

        pcnet_tmd_load(&tmd, PHYSADDR(s,CSR_CXDA(s)));

        if(BHM_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "tmd_load 0x%08x", PHYSADDR(s,CSR_CXDA(s)));
            printTMD(&tmd);
        }
        if (GET_FIELD(tmd.status, TMDS, STP)) {
            s->xmit_pos = 0;
            if (!GET_FIELD(tmd.status, TMDS, ENP)) {
                Int32 bcnt = 4096 - GET_FIELD(tmd.length, TMDL, BCNT);
                dmaRead(PHYSADDR(s, tmd.tbadr), s->buffer, bcnt, "tx", CSR_BSWP(s));
                s->xmit_pos += bcnt;
            }
            xmit_cxda = PHYSADDR(s,CSR_CXDA(s));
        }
        if (GET_FIELD(tmd.status, TMDS, ENP) && (s->xmit_pos >= 0)) {
            Int32 bcnt = 4096 - GET_FIELD(tmd.length, TMDL, BCNT);
            dmaRead(PHYSADDR(s, tmd.tbadr), s->buffer + s->xmit_pos, bcnt, "tx", CSR_BSWP(s));
            s->xmit_pos += bcnt;

            if(BHM_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, TIME_FMT ":txpkt %d bytes", bhmGetCurrentTime(), s->xmit_pos);
                printPacket(s->buffer);
            }
            if (CSR_LOOP(s)) {
                pcnet_receive(s->buffer, s->xmit_pos);
            } else {
                bhmEthernetWriteFrameN(netState.ethHandle, s->buffer, s->xmit_pos);
            }
            s->csr[0] &= ~0x0008;   /* clear TDMD */
            s->csr[4] |= 0x0004;    /* set TXSTRT */
            s->xmit_pos = -1;
        } else {
            if(BHM_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, TIME_FMT ": no txpkt", bhmGetCurrentTime());
            }
        }

        SET_FIELD(&tmd.status, TMDS, OWN, 0);
        pcnet_tmd_store(&tmd, PHYSADDR(s,CSR_CXDA(s)));
        if (!CSR_TOKINTD(s) || (CSR_LTINTEN(s) && GET_FIELD(tmd.status, TMDS, LTINT)))
            s->csr[0] |= 0x0200;    /* set TINT */

        if (CSR_XMTRC(s)<=1)
            CSR_XMTRC(s) = CSR_XMTRL(s);
        else
            CSR_XMTRC(s)--;
        if (count--)
            goto txagain;

    } else if (s->xmit_pos >= 0) {
        struct pcnet_TMD tmd;
        pcnet_tmd_load(&tmd, PHYSADDR(s,xmit_cxda));
        SET_FIELD(&tmd.misc, TMDM, BUFF, 1);
        SET_FIELD(&tmd.misc, TMDM, UFLO, 1);
        SET_FIELD(&tmd.status, TMDS, ERR, 1);
        SET_FIELD(&tmd.status, TMDS, OWN, 0);
        pcnet_tmd_store(&tmd, PHYSADDR(s,xmit_cxda));
        s->csr[0] |= 0x0200;    /* set TINT */
        if (!CSR_DXSUFLO(s)) {
            s->csr[0] &= ~0x0010;
        } else if (count--)
          goto txagain;
    }
    s->tx_busy = False;
}

static void poll(void)
{
    PCNetStateP s = &netState;
    if (CSR_RXON(s)) {
        rdte_poll(s);
    }

    if (CSR_TDMD(s) ||
        (CSR_TXON(s) && !CSR_DPOLL(s) && pcnet_tdte_poll(s)))
    {
        /* prevent recursion */
        if (s->tx_busy)
            return;

        pcnet_transmit();
    }
}

#define CLOCK_DIVIDER 33

static void poll_timer(void)
{
    PCNetStateP s  = &netState;
    Bool        go = False;
    if (CSR_TDMD(s)) {
        pcnet_transmit();
    }
    pcnet_update_irq(s);

    if (!CSR_STOP(s) && !CSR_SPND(s) && !CSR_DPOLL(s)) {
        Uns64 microseconds = bhmGetCurrentTime();
        if(s->timer == 0) {
            // first time since polling was enabled.
            s->timer = microseconds;
        }
        Uns32 deltaTime = microseconds - s->timer;
        if(deltaTime) {
            // only update if time has moved on
            Uns32 ticks    = deltaTime * CLOCK_DIVIDER;
            Uns32 newcount = CSR_POLL(s) + ticks;
            if (newcount > 0xffffLL) {
                go = True;
                CSR_POLL(s) = CSR_PINT(s);
            } else {
                CSR_POLL(s) = newcount;
            }
            if (BHM_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, TIME_FMT
                    "CSR_POLL: delta:%u ticks:%u   new:%u  %s",
                    bhmGetCurrentTime(),
                    deltaTime,
                    ticks,
                    CSR_POLL(s),
                    go ? "poll" : "nopoll"
                );
            }
            if(go)
                poll();
            s->timer = microseconds;
        }
    }
}

static void pcnet_csr_writew(PCNetState *s, Uns32 rap, Uns32 new_value)
{
    Uns16 val = new_value;
    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "csr_writew rap=%d val=0x%04x",
            bhmGetCurrentTime(),
            rap, val
        );

    switch (rap) {
        case 0:
            s->csr[0] &= ~(val & 0x7f00); /* Clear any interrupt flags */

            s->csr[0] = (s->csr[0] & ~0x0040) | (val & 0x0048);

            val = (val & 0x007f) | (s->csr[0] & 0x7f00);

            /* IFF STOP, STRT and INIT are set, clear STRT and INIT */
            if ((val&7) == 7)
              val &= ~3;

            if (!CSR_STOP(s) && (val & 4))
                stop(s);

            if (!CSR_INIT(s) && (val & 1))
                pcnet_init(s);

            if (!CSR_STRT(s) && (val & 2))
                start(s);

            if (CSR_TDMD(s))
                pcnet_transmit();

            return;
        case 1:
        case 2:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 18: /* CRBAL */
        case 19: /* CRBAU */
        case 20: /* CXBAL */
        case 21: /* CXBAU */
        case 22: /* NRBAU */
        case 23: /* NRBAU */
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40: /* CRBC */
        case 41:
        case 42: /* CXBC */
        case 43:
        case 44:
        case 45:
        case 46: /* POLL */
        case 47: /* POLLINT */
        case 72:
        case 74:
        case 76: /* RCVRL */
        case 78: /* XMTRL */
        case 112:
           if (CSR_STOP(s) || CSR_SPND(s))
               break;
           return;
        case 3:
            break;
        case 4:
            s->csr[4] &= ~(val & 0x026a);
            val &= ~0x026a; val |= s->csr[4] & 0x026a;
            break;
        case 5:
            s->csr[5] &= ~(val & 0x0a90);
            val &= ~0x0a90; val |= s->csr[5] & 0x0a90;
            break;
        case 16:
            pcnet_csr_writew(s,1,val);
            return;
        case 17:
            pcnet_csr_writew(s,2,val);
            return;
        case 58:
            pcnet_bcr_writew(s,BCR_SWS,val);
            break;
        default:
            return;
    }
    s->csr[rap] = val;
}

static Uns32 pcnet_csr_readw(PCNetState *s, Uns32 rap)
{
    Uns32 val;
    switch (rap) {
        case 0:
            pcnet_update_irq(s);
            val = s->csr[0];
            val |= (val & 0x7800) ? 0x8000 : 0;
            break;
        case 16:
            return pcnet_csr_readw(s,1);
        case 17:
            return pcnet_csr_readw(s,2);
        case 58:
            return pcnet_bcr_readw(s,BCR_SWS);
        case 88:
            val = s->csr[89];
            val <<= 16;
            val |= s->csr[88];
            break;
        default:
            val = s->csr[rap];
    }
    if (BHM_DIAG_HIGH)
       bhmMessage("I", PREFIX, TIME_FMT "csr_readw rap=%d val=0x%04x",
           bhmGetCurrentTime(), rap, val);
    return val;
}

static void pcnet_bcr_writew(PCNetState *s, Uns32 rap, Uns32 val)
{
    rap &= 127;
    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "bcr_writew rap=%d val=0x%04x",
            bhmGetCurrentTime(), rap, val);
    switch (rap) {
        case BCR_SWS:
            if (!(CSR_STOP(s) || CSR_SPND(s)))
                 return;
            val &= ~0x0300;
            switch (val & 0x00ff) {
                case 0:
                    val |= 0x0200;
                    break;
                case 1:
                    val |= 0x0100;
                    break;
                case 2:
                case 3:
                    val |= 0x0300;
                    break;
                default:
                    val = 0x0200;
                    break;
            }
            if (BHM_DIAG_HIGH)
               bhmMessage("I", PREFIX, "BCR_SWS=0x%04x", val);
        case BCR_LNKST:
        case BCR_LED1:
        case BCR_LED2:
        case BCR_LED3:
        case BCR_MC:
        case BCR_FDC:
        case BCR_BSBC:
        case BCR_EECAS:
        case BCR_PLAT:
            s->bcr[rap] = val;
            break;
        default:
            break;
    }
}

static Uns32 pcnet_bcr_readw(PCNetState *s, Uns32 rap)
{
    Uns32 val;
    rap &= 127;
    switch (rap) {
    case BCR_LNKST:
    case BCR_LED1:
    case BCR_LED2:
    case BCR_LED3:
        val = s->bcr[rap] & ~0x8000;
        val |= (val & 0x017f & s->lnkst) ? 0x8000 : 0;
        break;
    default:
        val = rap < 32 ? s->bcr[rap] : 0;
        break;
    }
    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "bcr_readw rap=%d val=0x%04x",
            bhmGetCurrentTime(), rap, val
        );
    return val;
}

static void hardReset(void)
{
    PCNetState *s = &netState;
    Int32 i;
    Uns16 checksum;

    // default
    Uns8 macaddr[6] = { 0x52, 0x54, 0x00, 0x12, 0x34, 0x56 };

    // override from attribute
    Uns64 macUns64;
    if (bhmUns64ParamValue("macaddress", &macUns64)) {
        setMac(macUns64, macaddr);
    }
    if (BHM_DIAG_LOW) {
        bhmMessage("I", PREFIX, TIME_FMT
           "hardReset: MAC=%02x.%02x.%02x.%02x.%02x.%02x.",
            bhmGetCurrentTime(),
            macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5]
        );
    }
    memcpy(s->prom, macaddr, 6);
    s->prom[12] = s->prom[13] = 0x00;
    s->prom[14] = s->prom[15] = 0x57;

    for (i = 0,checksum = 0; i < 16; i++)
        checksum += s->prom[i];
    *(Uns16 *)&s->prom[12] = cpu_to_le16(checksum);

    s->bcr[BCR_MSRDA] = 0x0005;
    s->bcr[BCR_MSWRA] = 0x0005;
    s->bcr[BCR_MC   ] = 0x0002;
    s->bcr[BCR_LNKST] = 0x00c0;
    s->bcr[BCR_LED1 ] = 0x0084;
    s->bcr[BCR_LED2 ] = 0x0088;
    s->bcr[BCR_LED3 ] = 0x0090;
    s->bcr[BCR_FDC  ] = 0x0000;
    s->bcr[BCR_BSBC ] = 0x9001;
    s->bcr[BCR_EECAS] = 0x0002;
    s->bcr[BCR_SWS  ] = 0x0200;
    s->bcr[BCR_PLAT ] = 0xff06;

    softReset(s);
}

//
//////////////////////////////////  aprom access //////////////////////////////////
//
static void aprom_writeb(Uns32 addr, Uns32 val)
{
    PCNetState *s = &netState;
    /* Check APROMWE bit to enable write access */
    if (pcnet_bcr_readw(s,2) & 0x80)
        s->prom[addr & 15] = val;
}

static Uns32 aprom_readb(Uns32 addr)
{
    PCNetState *s = &netState;
    return s->prom[addr &= 15];
}

static void ioport_writew(Uns32 addr, Uns32 val)
{
    PCNetState *s = &netState;
    addr &= 0xf;
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "ioport_writew addr:0x%x <= 0x%x",
            bhmGetCurrentTime(),
            addr,
            val
        );
    poll_timer();
    if (!BCR_DWIO(s)) {
        switch (addr) {
        case 0x00: /* RDP */
            pcnet_csr_writew(s, s->rap, val);
            break;
        case 0x02:
            s->rap = val & 0x7f;
            break;
        case 0x06:
            pcnet_bcr_writew(s, s->rap, val);
            break;
        }
    }
    pcnet_update_irq(s);
}

static Uns32 ioport_readw(Uns32 addr)
{
    PCNetState *s = &netState;
    Uns32 val = -1;
    poll_timer();
    if (!BCR_DWIO(s)) {
        switch (addr & 0x0f) {
            case 0x00: /* RDP */
                val = pcnet_csr_readw(s, s->rap);
                break;
            case 0x02:
                val = s->rap;
                if(BHM_DIAG_HIGH)
                    bhmMessage("I", PREFIX, TIME_FMT "ioport_readw val=0x%x",
                        bhmGetCurrentTime(),
                        val
                    );
                 break;
            case 0x04:
                softReset(s);
                val = 0;
                break;
            case 0x06:
                val = pcnet_bcr_readw(s, s->rap);
                break;
        }
    }
    pcnet_update_irq(s);
    return val;
}

static void ioport_writel(Uns32 addr, Uns32 val)
{
    PCNetState *s = &netState;
    poll_timer();
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "ioport_writel addr=0x%08x val=0x%08x",
            bhmGetCurrentTime(),
            addr, val
        );

    if (BCR_DWIO(s)) {
        switch (addr & 0x0f) {
        case 0x00: /* RDP */
            pcnet_csr_writew(s, s->rap, val & 0xffff);
            break;
        case 0x04:
            s->rap = val & 0x7f;
            break;
        case 0x0c:
            pcnet_bcr_writew(s, s->rap, val & 0xffff);
            break;
        }
    } else
    if ((addr & 0x0f) == 0) {
        /* switch device to dword i/o mode */
        pcnet_bcr_writew(s, BCR_BSBC, pcnet_bcr_readw(s, BCR_BSBC) | 0x0080);

        if(BHM_DIAG_HIGH)
            bhmMessage("I", PREFIX, "switched to dword i/o mode");
    }
    pcnet_update_irq(s);
}

static Uns32 ioport_readl(Uns32 addr)
{
    PCNetState *s = &netState;
    Uns32 val = -1;
    poll_timer();
    if (BCR_DWIO(s)) {
        switch (addr & 0x0f) {
            case 0x00: /* RDP */
                val = pcnet_csr_readw(s, s->rap);
                break;
            case 0x04:
                val = s->rap;
                break;
            case 0x08:
                softReset(s);
                val = 0;
                break;
            case 0x0c:
                val = pcnet_bcr_readw(s, s->rap);
                break;
        }
    }
    pcnet_update_irq(s);
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, TIME_FMT "ioport_readl addr=0x%08x val=0x%08x",
            bhmGetCurrentTime(),
            addr, val
        );
    return val;
}

///////////////////////////////////// IOSPACE REGISTERS /////////////////////////////////////////

#define APROM_SIZE      16
#define REGS_SIZE       16

// Windows; must be consecutive
static Uns8 apromWindow[APROM_SIZE];
static Uns8 regsWindow [REGS_SIZE];

//
// The PCI IO callback
//
static PPM_WRITE_CB(apromWrite) {
    Uns32 offset = addr - (void*)&apromWindow[0];

    if(bytes == 1) {
        if (BHM_DIAG_HIGH)
            bhmMessage("I", PREFIX, TIME_FMT "apromWrite 0x%x <= 0x%x",
                bhmGetCurrentTime(),
                offset, data
            );
        aprom_writeb(offset, data);
    } else {
        bhmMessage("E", PREFIX, "Unsupported write");
    }
}

static PPM_READ_CB(apromRead) {
    Uns32 offset = addr - (void*)&apromWindow[0];
    if(bytes == 1) {
        Uns32 data = aprom_readb(offset);
        if (BHM_DIAG_HIGH)
            bhmMessage("I", PREFIX, TIME_FMT "apromRead 0x%x => 0x%x",
                bhmGetCurrentTime(),
                offset, data
            );
        return data;
    } else {
        bhmMessage("E", PREFIX, "Unsupported read");
        return 0;
    }
}

static PPM_WRITE_CB(regsWrite) {
    Uns32 offset = addr - (void*)&regsWindow[0];
    if(bytes == 2) {
        ioport_writew(offset, data);
    } else if (bytes == 4) {
        ioport_writel(offset, data);
    } else {
        bhmMessage("I", PREFIX, "unsupported");
    }
}

static PPM_READ_CB(regsRead) {
    Uns32 offset = addr - (void*)&regsWindow[0];
    if(bytes == 2) {
         return ioport_readw(offset);
     } else if (bytes == 4) {
         return ioport_readl(offset);
    } else {
        bhmMessage("I", PREFIX, "unsupported");
        return 0;
    }
}

static void installRegisterCallbacks(void)
{
    ppmInstallWriteCallback(apromWrite, 0, apromWindow, APROM_SIZE);
    ppmInstallReadCallback (apromRead,  0, apromWindow, APROM_SIZE);

    ppmInstallWriteCallback(regsWrite, 0, regsWindow, REGS_SIZE);
    ppmInstallReadCallback (regsRead,  0, regsWindow, REGS_SIZE);
}

///////////////////////////////////// PCI ////////////////////////////////////

static void pciHeaderInit(void)
{
    pciConfig.vendorID       = cpu_to_le16(0x1022);
    pciConfig.deviceID       = cpu_to_le16(0x2000);
    pciConfig.command        = cpu_to_le16(0x0004);   // was 7
    pciConfig.status         = cpu_to_le16(0x0280);

    pciConfig.revisionID     = 0x10;
    pciConfig.classCode[0]   = 0x00;
    pciConfig.classCode[1]   = 0x00;
    pciConfig.classCode[2]   = 0x02;

    pciConfig.headerType     = 0x00;

    pciConfig.baseAddress[0] = cpu_to_le32(0x00000001);  // I/O base
    pciConfig.baseAddress[1] = cpu_to_le32(0x00000000);  // MM  base

    pciConfig.interruptPin   = 1;       // interrupt pin 0
    pciConfig.minGnt         = 0x06;
    pciConfig.maxLat         = 0xFF;
}

static void pciMappingInit(void)
{
    // first region is I/O
    pciInstallRegion(0x10, 0xFFFFFFE1, &apromWindow, NULL, APROM_SIZE+REGS_SIZE);

    // 2nd region is memory mapped
    pciInstallRegion(0x14, 0xFFFFFFE0, &apromWindow, NULL, APROM_SIZE+REGS_SIZE);
}

static void connectNets(void)
{
    // interrupts are optional
    netState.interrupt.handle = handles.intOut0;
    netState.interrupt.v = 0;
}

static BHM_ETHER_PACKET_CB(receiveFrame) {
    bhmMessage("I", "NET", "rx pcnet_receive %u t:%f\n", bytes, (float)bhmGetCurrentTime());
    pcnet_receive(data, bytes);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    pciHeaderInit();
    pciMappingInit();

    netState.ethHandle = bhmEthernetOpenAuto();

    hardReset();
    pciConnectConfigSlavePort("NET_PCI", NULL);
    pciConnectBusMaster();
    connectNets();
    installRegisterCallbacks();
    
    bhmEthernetInstallCB(netState.ethHandle, receiveFrame, 0);
}

PPM_DESTRUCTOR_CB(destructor) {
    bhmEthernetClose(netState.ethHandle);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
