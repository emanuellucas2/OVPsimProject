/*
 * QEMU VGA Emulator.
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

#ifndef CIRRUS_VGA_H
#define CIRRUS_VGA_H

#include "hostapi/impTypes.h"
#include "types.h"

typedef void CPUWriteMemoryFunc(void *opaque, Addr addr, Uns32 value);
typedef Uns32 CPUReadMemoryFunc(void *opaque, Addr addr);

typedef struct CirrusVGAStateS *CirrusVGAStateP;

typedef void (*cirrus_bitblt_rop_t) (
    CirrusVGAStateP s,
    Uns8*           dst,
    const Uns8*     src,
    Int32           dstpitch,
    Int32           srcpitch,
    Int32           bltwidth,
    Int32           bltheight
);

typedef void (*cirrus_fill_t)(
    CirrusVGAStateP s,
    Uns8            *dst,
    Int32            dst_pitch,
    Int32            width,
    Int32            height
);

typedef struct CirrusVGAStateS {
    VGA_STATE_COMMON

    Int32 cirrus_linear_bitblt_io_addr;
    Int32 cirrus_mmio_io_addr;
    Uns32 cirrus_addr_mask;
    Uns32 linear_mmio_mask;
    Uns8 cirrus_shadow_gr0;
    Uns8 cirrus_shadow_gr1;
    Uns8 cirrus_hidden_dac_lockindex;
    Uns8 cirrus_hidden_dac_data;
    Uns32 cirrus_bank_base[2];
    Uns32 cirrus_bank_limit[2];
    Uns8 cirrus_hidden_palette[48];
    Uns32 hw_cursor_x;
    Uns32 hw_cursor_y;
    Int32 cirrus_blt_pixelwidth;
    Int32 cirrus_blt_width;
    Int32 cirrus_blt_height;
    Int32 cirrus_blt_dstpitch;
    Int32 cirrus_blt_srcpitch;
    Uns32 cirrus_blt_fgcol;
    Uns32 cirrus_blt_bgcol;
    Uns32 cirrus_blt_dstaddr;
    Uns32 cirrus_blt_srcaddr;
    Uns8 cirrus_blt_mode;
    Uns8 cirrus_blt_modeext;
    cirrus_bitblt_rop_t cirrus_rop;
#define CIRRUS_BLTBUFSIZE (2048 * 4) /* one line width */
    Uns8 cirrus_bltbuf[CIRRUS_BLTBUFSIZE];
    Uns8 *cirrus_srcptr;
    Uns8 *cirrus_srcptr_end;
    Uns32 cirrus_srccounter;
    /* hwcursor display state */
    Int32 last_hw_cursor_size;
    Int32 last_hw_cursor_x;
    Int32 last_hw_cursor_y;
    Int32 last_hw_cursor_y_start;
    Int32 last_hw_cursor_y_end;
    Int32 real_vram_size; /* XXX: suppress that */
    CPUWriteMemoryFunc **cirrus_linear_write;

    void *memDomain;
    void *localDomain;
    Uns32 base;
} CirrusVGAState;

CirrusVGAStateP pci_cirrus_vga_init(Uns32 vgaRamSize, void *vgaRamBase, Uns32 id);

Uns32 cirrus_vga_ioport_read(CirrusVGAStateP s, Uns32 addr, Uns32 diag);
void cirrus_vga_ioport_write(CirrusVGAStateP s, Uns32 addr, Uns32 val, Uns32 diag);

Uns32 cirrus_vga_display_read(CirrusVGAStateP s, Uns32 address, Uns32 base, Uns32 bytes, Uns32 diag);
void cirrus_vga_display_write(CirrusVGAStateP s, Uns32 address, Uns32 base, Uns32 data, Uns32 bytes, Uns32 diag);

void cirrus_vga_mem_writeb(void *opaque, Addr addr, Uns32 val);
void cirrus_vga_mem_writew(void *opaque, Addr addr, Uns32 val);
void cirrus_vga_mem_writel(void *opaque, Addr addr, Uns32 val);

void cirrus_linear_writeb(void *opaque, Addr addr, Uns32 val);
void cirrus_linear_writew(void *opaque, Addr addr, Uns32 val);
void cirrus_linear_writel(void *opaque, Addr addr, Uns32 val);
Uns32 cirrus_linear_readb(void *opaque, Addr addr);
Uns32 cirrus_linear_readw(void *opaque, Addr addr);
Uns32 cirrus_linear_readl(void *opaque, Addr addr);

#endif
