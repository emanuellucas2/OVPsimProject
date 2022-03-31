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

#include <string.h>
#include <stdio.h>

#include "hostapi/impTypes.h"
#include "types.h"
#include "cpu.h"
#include "bswap.h"
#include "vga_state.h"
#include "vga_display.h"
#include "vga_common.h"
#include "sdl.h"
#include "vmi/vmiMessage.h"

#define VGA_DIRTY_FLAG  0x01

#define cbswap_32(__x) \
((Uns32)( \
        (((Uns32)(__x) & (Uns32)0x000000ffUL) << 24) | \
        (((Uns32)(__x) & (Uns32)0x0000ff00UL) <<  8) | \
        (((Uns32)(__x) & (Uns32)0x00ff0000UL) >>  8) | \
        (((Uns32)(__x) & (Uns32)0xff000000UL) >> 24) ))


#ifdef WORDS_BIGENDIAN
#define GET_PLANE(data, p) (((data) >> (24 - (p) * 8)) & 0xff)
#else
#define GET_PLANE(data, p) (((data) >> ((p) * 8)) & 0xff)
#endif

#ifdef WORDS_BIGENDIAN
#define PAT(x) cbswap_32(x)
#else
#define PAT(x) (x)
#endif

static const Uns32 mask16[16] = {
    PAT(0x00000000),
    PAT(0x000000ff),
    PAT(0x0000ff00),
    PAT(0x0000ffff),
    PAT(0x00ff0000),
    PAT(0x00ff00ff),
    PAT(0x00ffff00),
    PAT(0x00ffffff),
    PAT(0xff000000),
    PAT(0xff0000ff),
    PAT(0xff00ff00),
    PAT(0xff00ffff),
    PAT(0xffff0000),
    PAT(0xffff00ff),
    PAT(0xffffff00),
    PAT(0xffffffff),
};


static void vga_reset(VGAState *s)
{
    memset(s, 0, sizeof(VGAState));
    s->graphic_mode = -1; /* force full update */
}

void vga_common_init(VGAState *s,Uns8 *vga_ram_base, Int32 vga_ram_size)
{
    vga_reset(s);
    s->vram_ptr = vga_ram_base;
    s->vram_size = vga_ram_size;
}

/* called for accesses between 0xa0000 and 0xc0000 */
Uns32 vga_mem_readb(void *opaque, Addr addr)
{
    VGAState *s = opaque;
    Int32 memory_map_mode, plane;
    Uns32 ret;

    /* convert to VGA memory offset */
    memory_map_mode = (s->gr[6] >> 2) & 3;
    addr &= 0x1ffff;
    switch(memory_map_mode) {
    case 0:
        break;
    case 1:
        if (addr >= 0x10000)
            return 0xff;
        addr += s->bank_offset;
        break;
    case 2:
        addr -= 0x10000;
        if (addr >= 0x8000)
            return 0xff;
        break;
    default:
    case 3:
        addr -= 0x18000;
        if (addr >= 0x8000)
            return 0xff;
        break;
    }

    if (s->sr[4] & 0x08) {
        /* chain 4 mode : simplest access */
        ret = s->vram_ptr[addr];
    } else if (s->gr[5] & 0x10) {
        /* odd/even mode (aka text mode mapping) */
        plane = (s->gr[4] & 2) | (addr & 1);
        ret = s->vram_ptr[((addr & ~1) << 1) | plane];
    } else {
        /* standard VGA latched access */
        s->latch = ((Uns32 *)s->vram_ptr)[addr];

        if (!(s->gr[5] & 0x08)) {
            /* read mode 0 */
            plane = s->gr[4];
            ret = GET_PLANE(s->latch, plane);
        } else {
            /* read mode 1 */
            ret = (s->latch ^ mask16[s->gr[2]]) & mask16[s->gr[7]];
            ret |= ret >> 16;
            ret |= ret >> 8;
            ret = (~ret) & 0xff;
        }
    }
    return ret;
}

/* called for accesses between 0xa0000 and 0xc0000 */
void vga_mem_writeb(void *opaque, Addr addr, Uns32 val)
{
    VGAState *s = opaque;
    Int32 memory_map_mode, plane, write_mode, b, func_select, mask;
    Uns32 write_mask, bit_mask, set_mask;

#ifdef DEBUG_VGA_MEM
    printf("vga: [0x%x] = 0x%02x\n", addr, val);
#endif
    /* convert to VGA memory offset */
    memory_map_mode = (s->gr[6] >> 2) & 3;
    addr &= 0x1ffff;
    switch(memory_map_mode) {
    case 0:
        break;
    case 1:
        if (addr >= 0x10000)
            return;
        addr += s->bank_offset;
        break;
    case 2:
        addr -= 0x10000;
        if (addr >= 0x8000)
            return;
        break;
    default:
    case 3:
        addr -= 0x18000;
        if (addr >= 0x8000)
            return;
        break;
    }

    if (s->sr[4] & 0x08) {
        /* chain 4 mode : simplest access */
        plane = addr & 3;
        mask = (1 << plane);
        if (s->sr[2] & mask) {
            s->vram_ptr[addr] = val;
#ifdef DEBUG_VGA_MEM
            printf("vga: chain4: [0x%x]\n", addr);
#endif
            s->plane_updated |= mask; /* only used to detect font change */
            //cpu_physical_memory_set_dirty(s->vram_offset + addr);
        }
    } else if (s->gr[5] & 0x10) {
        /* odd/even mode (aka text mode mapping) */
        plane = (s->gr[4] & 2) | (addr & 1);
        mask = (1 << plane);
        if (s->sr[2] & mask) {
            addr = ((addr & ~1) << 1) | plane;
            s->vram_ptr[addr] = val;
#ifdef DEBUG_VGA_MEM
            printf("vga: odd/even: [0x%x]\n", addr);
#endif
            s->plane_updated |= mask; /* only used to detect font change */
            //cpu_physical_memory_set_dirty(s->vram_offset + addr);
        }
    } else {
        /* standard VGA latched access */
        write_mode = s->gr[5] & 3;
        switch(write_mode) {
        default:
        case 0:
            /* rotate */
            b = s->gr[3] & 7;
            val = ((val >> b) | (val << (8 - b))) & 0xff;
            val |= val << 8;
            val |= val << 16;

            /* apply set/reset mask */
            set_mask = mask16[s->gr[1]];
            val = (val & ~set_mask) | (mask16[s->gr[0]] & set_mask);
            bit_mask = s->gr[8];
            break;
        case 1:
            val = s->latch;
            goto do_write;
        case 2:
            val = mask16[val & 0x0f];
            bit_mask = s->gr[8];
            break;
        case 3:
            /* rotate */
            b = s->gr[3] & 7;
            val = (val >> b) | (val << (8 - b));

            bit_mask = s->gr[8] & val;
            val = mask16[s->gr[0]];
            break;
        }

        /* apply logical operation */
        func_select = s->gr[3] >> 3;
        switch(func_select) {
        case 0:
        default:
            /* nothing to do */
            break;
        case 1:
            /* and */
            val &= s->latch;
            break;
        case 2:
            /* or */
            val |= s->latch;
            break;
        case 3:
            /* xor */
            val ^= s->latch;
            break;
        }

        /* apply bit mask */
        bit_mask |= bit_mask << 8;
        bit_mask |= bit_mask << 16;
        val = (val & bit_mask) | (s->latch & ~bit_mask);

    do_write:
        /* mask data according to sr[2] */
        mask = s->sr[2];
        s->plane_updated |= mask; /* only used to detect font change */
        write_mask = mask16[mask];
        ((Uns32 *)s->vram_ptr)[addr] =
            (((Uns32 *)s->vram_ptr)[addr] & ~write_mask) |
            (val & write_mask);
#ifdef DEBUG_VGA_MEM
            printf("vga: latch: [0x%x] mask=0x%08x val=0x%08x\n",
                   addr * 4, write_mask, val);
#endif
            //cpu_physical_memory_set_dirty(s->vram_offset + (addr << 2));
    }
}

void vga_invalidate_scanlines(VGAState *s, Int32 y1, Int32 y2)
{
    Int32 y;
    if (y1 >= VGA_MAX_HEIGHT)
        return;
    if (y2 >= VGA_MAX_HEIGHT)
        y2 = VGA_MAX_HEIGHT;
    for(y = y1; y < y2; y++) {
        s->invalidated_y_table[y >> 5] |= 1 << (y & 0x1f);
    }
}


typedef void vga_draw_glyph8_func(Uns8 *d, Int32 linesize,
                             const Uns8 *font_ptr, Int32 h,
                             Uns32 fgcol, Uns32 bgcol);
typedef void vga_draw_glyph9_func(Uns8 *d, Int32 linesize,
                                  const Uns8 *font_ptr, Int32 h,
                                  Uns32 fgcol, Uns32 bgcol, Int32 dup9);
typedef void vga_draw_line_func(VGAState *s1, Uns8 *d,
                                const Uns8 *s, Int32 width);


static Uns32 expand4[256];
static Uns16 expand2[256];
static Uns8 expand4to8[16];

void init_expand_tables(void) {
    Int32 i, j, v, b;

    for(i = 0;i < 256; i++) {
        v = 0;
        for(j = 0; j < 8; j++) {
            v |= ((i >> j) & 1) << (j * 4);
        }
        expand4[i] = v;

        v = 0;
        for(j = 0; j < 4; j++) {
            v |= ((i >> (2 * j)) & 3) << (j * 4);
        }
        expand2[i] = v;
    }
    for(i = 0; i < 16; i++) {
        v = 0;
        for(j = 0; j < 4; j++) {
            b = ((i >> j) & 1);
            v |= b << (2 * j);
            v |= b << (2 * j + 1);
        }
        expand4to8[i] = v;
    }
}

static Int32 cpu_physical_memory_get_dirty(Addr addr, Int32 dirty_flags)
{
    return 1;
}

static void cpu_physical_memory_reset_dirty(Addr start, Addr end, Int32 dirty_flags)
{
}

typedef Uns32 rgb_to_pixel_dup_func(Uns32 r, Uns32 g, Uns32 b);

static Uns32 rgb_to_pixel8_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel8(r, g, b);
    col |= col << 8;
    col |= col << 16;
    return col;
}

static Uns32 rgb_to_pixel15_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel15(r, g, b);
    col |= col << 16;
    return col;
}

static Uns32 rgb_to_pixel15bgr_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel15bgr(r, g, b);
    col |= col << 16;
    return col;
}

static Uns32 rgb_to_pixel16_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel16(r, g, b);
    col |= col << 16;
    return col;
}

static Uns32 rgb_to_pixel16bgr_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel16bgr(r, g, b);
    col |= col << 16;
    return col;
}

static Uns32 rgb_to_pixel32_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel32(r, g, b);
    return col;
}

static Uns32 rgb_to_pixel32bgr_dup(Uns32 r, Uns32 g, Uns32 b)
{
    Uns32 col;
    col = rgb_to_pixel32bgr(r, g, b);
    return col;
}


#define NB_DEPTHS 7

static rgb_to_pixel_dup_func *rgb_to_pixel_dup_table[NB_DEPTHS] = {
    rgb_to_pixel8_dup,
    rgb_to_pixel15_dup,
    rgb_to_pixel16_dup,
    rgb_to_pixel32_dup,
    rgb_to_pixel32bgr_dup,
    rgb_to_pixel15bgr_dup,
    rgb_to_pixel16bgr_dup,
};

static inline Int32 get_depth_index(DisplayStateP ds)
{
    switch(sdl_get_depth(ds)) {
        default:
        case 8:
            return 0;
        case 15:
            if (sdl_get_bgr(ds))
                return 5;
            else
                return 1;
        case 16:
            if (sdl_get_bgr(ds))
                return 6;
            else
                return 2;
        case 32:
            if (sdl_get_bgr(ds))
                return 4;
            else
                return 3;
    }
}


#ifdef WORDS_BIGENDIAN
#define DPAT(x) (x)
#else
#define DPAT(x) cbswap_32(x)
#endif


#ifdef WORDS_BIGENDIAN
#define BIG 1
#else
#define BIG 0
#endif


static const Uns32 dmask16[16] = {
    DPAT(0x00000000),
    DPAT(0x000000ff),
    DPAT(0x0000ff00),
    DPAT(0x0000ffff),
    DPAT(0x00ff0000),
    DPAT(0x00ff00ff),
    DPAT(0x00ffff00),
    DPAT(0x00ffffff),
    DPAT(0xff000000),
    DPAT(0xff0000ff),
    DPAT(0xff00ff00),
    DPAT(0xff00ffff),
    DPAT(0xffff0000),
    DPAT(0xffff00ff),
    DPAT(0xffffff00),
    DPAT(0xffffffff),
};

static const Uns32 dmask4[4] = {
    DPAT(0x00000000),
    DPAT(0x0000ffff),
    DPAT(0xffff0000),
    DPAT(0xffffffff),
};



#define DEPTH 8
#include "vga_template.h"

#define DEPTH 15
#include "vga_template.h"

#define BGR_FORMAT
#define DEPTH 15
#include "vga_template.h"

#define DEPTH 16
#include "vga_template.h"

#define BGR_FORMAT
#define DEPTH 16
#include "vga_template.h"

#define DEPTH 32
#include "vga_template.h"

#define BGR_FORMAT
#define DEPTH 32
#include "vga_template.h"


enum {
    VGA_DRAW_LINE2,
    VGA_DRAW_LINE2D2,
    VGA_DRAW_LINE4,
    VGA_DRAW_LINE4D2,
    VGA_DRAW_LINE8D2,
    VGA_DRAW_LINE8,
    VGA_DRAW_LINE15,
    VGA_DRAW_LINE16,
    VGA_DRAW_LINE24,
    VGA_DRAW_LINE32,
    VGA_DRAW_LINE_NB,
};

static vga_draw_line_func *vga_draw_line_table[NB_DEPTHS * VGA_DRAW_LINE_NB] = {
    vga_draw_line2_8,
    vga_draw_line2_16,
    vga_draw_line2_16,
    vga_draw_line2_32,
    vga_draw_line2_32,
    vga_draw_line2_16,
    vga_draw_line2_16,

    vga_draw_line2d2_8,
    vga_draw_line2d2_16,
    vga_draw_line2d2_16,
    vga_draw_line2d2_32,
    vga_draw_line2d2_32,
    vga_draw_line2d2_16,
    vga_draw_line2d2_16,

    vga_draw_line4_8,
    vga_draw_line4_16,
    vga_draw_line4_16,
    vga_draw_line4_32,
    vga_draw_line4_32,
    vga_draw_line4_16,
    vga_draw_line4_16,

    vga_draw_line4d2_8,
    vga_draw_line4d2_16,
    vga_draw_line4d2_16,
    vga_draw_line4d2_32,
    vga_draw_line4d2_32,
    vga_draw_line4d2_16,
    vga_draw_line4d2_16,

    vga_draw_line8d2_8,
    vga_draw_line8d2_16,
    vga_draw_line8d2_16,
    vga_draw_line8d2_32,
    vga_draw_line8d2_32,
    vga_draw_line8d2_16,
    vga_draw_line8d2_16,

    vga_draw_line8_8,
    vga_draw_line8_16,
    vga_draw_line8_16,
    vga_draw_line8_32,
    vga_draw_line8_32,
    vga_draw_line8_16,
    vga_draw_line8_16,

    vga_draw_line15_8,
    vga_draw_line15_15,
    vga_draw_line15_16,
    vga_draw_line15_32,
    vga_draw_line15_32bgr,
    vga_draw_line15_15bgr,
    vga_draw_line15_16bgr,

    vga_draw_line16_8,
    vga_draw_line16_15,
    vga_draw_line16_16,
    vga_draw_line16_32,
    vga_draw_line16_32bgr,
    vga_draw_line16_15bgr,
    vga_draw_line16_16bgr,

    vga_draw_line24_8,
    vga_draw_line24_15,
    vga_draw_line24_16,
    vga_draw_line24_32,
    vga_draw_line24_32bgr,
    vga_draw_line24_15bgr,
    vga_draw_line24_16bgr,

    vga_draw_line32_8,
    vga_draw_line32_15,
    vga_draw_line32_16,
    vga_draw_line32_32,
    vga_draw_line32_32bgr,
    vga_draw_line32_15bgr,
    vga_draw_line32_16bgr,
};

static vga_draw_glyph8_func *vga_draw_glyph8_table[NB_DEPTHS] = {
    vga_draw_glyph8_8,
    vga_draw_glyph8_16,
    vga_draw_glyph8_16,
    vga_draw_glyph8_32,
    vga_draw_glyph8_32,
    vga_draw_glyph8_16,
    vga_draw_glyph8_16,
};

static vga_draw_glyph8_func *vga_draw_glyph16_table[NB_DEPTHS] = {
    vga_draw_glyph16_8,
    vga_draw_glyph16_16,
    vga_draw_glyph16_16,
    vga_draw_glyph16_32,
    vga_draw_glyph16_32,
    vga_draw_glyph16_16,
    vga_draw_glyph16_16,
};

static vga_draw_glyph9_func *vga_draw_glyph9_table[NB_DEPTHS] = {
    vga_draw_glyph9_8,
    vga_draw_glyph9_16,
    vga_draw_glyph9_16,
    vga_draw_glyph9_32,
    vga_draw_glyph9_32,
    vga_draw_glyph9_16,
    vga_draw_glyph9_16,
};

static const Uns8 cursor_glyph[32 * 4] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

/* return true if the palette was modified */
static Int32 update_palette16(VGAState *s)
{
    Int32 full_update, i;
    Uns32 v, col, *palette;

    full_update = 0;
    palette = s->last_palette;
    for(i = 0; i < 16; i++) {
        v = s->ar[i];
        if (s->ar[0x10] & 0x80)
            v = ((s->ar[0x14] & 0xf) << 4) | (v & 0xf);
        else
            v = ((s->ar[0x14] & 0xc) << 4) | (v & 0x3f);
        v = v * 3;
        col = s->rgb_to_pixel(c6_to_8(s->palette[v]),
                              c6_to_8(s->palette[v + 1]),
                              c6_to_8(s->palette[v + 2]));
        if (col != palette[i]) {
            full_update = 1;
            palette[i] = col;
        }
    }
    return full_update;
}

/* return true if the palette was modified */
static Int32 update_palette256(VGAState *s)
{
    Int32 full_update, i;
    Uns32 v, col, *palette;

    full_update = 0;
    palette = s->last_palette;
    v = 0;
    for(i = 0; i < 256; i++) {
        if (s->dac_8bit) {
          col = s->rgb_to_pixel(s->palette[v],
                                s->palette[v + 1],
                                s->palette[v + 2]);
        } else {
          col = s->rgb_to_pixel(c6_to_8(s->palette[v]),
                                c6_to_8(s->palette[v + 1]),
                                c6_to_8(s->palette[v + 2]));
        }
        if (col != palette[i]) {
            full_update = 1;
            palette[i] = col;
        }
        v += 3;
    }
    return full_update;
}

/* update start_addr and line_offset. Return TRUE if modified */
static Int32 update_basic_params(VGAState *s)
{
    Int32 full_update;
    Uns32 start_addr, line_offset, line_compare;

    full_update = 0;

    s->get_offsets(s, &line_offset, &start_addr, &line_compare);

    if (line_offset != s->line_offset ||
        start_addr != s->start_addr ||
        line_compare != s->line_compare) {
        s->line_offset = line_offset;
        s->start_addr = start_addr;
        s->line_compare = line_compare;
        full_update = 1;
    }
    return full_update;
}


/*
 * Text mode update
 * Missing:
 * - double scan
 * - double width
 * - underline
 * - flashing
 */
static void vga_draw_text(VGAState *s, Int32 full_update, DisplayStateP ds)
{
    Int32 cx, cy, cheight, cw, ch, cattr, height, width, ch_attr;
    Int32 cx_min, cx_max, linesize, x_incr;
    Uns32 offset, fgcol, bgcol, v, cursor_offset;
    Uns8 *d1, *d, *src, *s1, *dest, *cursor_ptr;
    const Uns8 *font_ptr, *font_base[2];
    Int32 dup9, line_offset, depth_index;
    Uns32 *palette;
    Uns32 *ch_attr_ptr;
    vga_draw_glyph8_func *vga_draw_glyph8;
    vga_draw_glyph9_func *vga_draw_glyph9;


    full_update |= update_palette16(s);
    palette = s->last_palette;

    /* compute font data address (in plane 2) */
    v = s->sr[3];
    offset = (((v >> 4) & 1) | ((v << 1) & 6)) * 8192 * 4 + 2;
    if (offset != s->font_offsets[0]) {
        s->font_offsets[0] = offset;
        full_update = 1;
    }
    font_base[0] = s->vram_ptr + offset;

    offset = (((v >> 5) & 1) | ((v >> 1) & 6)) * 8192 * 4 + 2;
    font_base[1] = s->vram_ptr + offset;
    if (offset != s->font_offsets[1]) {
        s->font_offsets[1] = offset;
        full_update = 1;
    }
    if (s->plane_updated & (1 << 2)) {
        /* if the plane 2 was modified since the last display, it
           indicates the font may have been modified */
        s->plane_updated = 0;
        full_update = 1;
    }
    full_update |= update_basic_params(s);

    line_offset = s->line_offset;
    s1 = s->vram_ptr + (s->start_addr * 4);

    /* total width & height */
    cheight = (s->cr[9] & 0x1f) + 1;
    cw = 8;
    if (!(s->sr[1] & 0x01))
        cw = 9;
    if (s->sr[1] & 0x08)
        cw = 16; /* NOTE: no 18 pixel wide */
    x_incr = cw * ((sdl_get_depth(ds) + 7) >> 3);
    width = (s->cr[0x01] + 1);
    if (s->cr[0x06] == 100) {
        /* ugly hack for CGA 160x100x16 - explain me the logic */
        height = 100;
    } else {
        height = s->cr[0x12] |
            ((s->cr[0x07] & 0x02) << 7) |
            ((s->cr[0x07] & 0x40) << 3);
        height = (height + 1) / cheight;
    }
    if ((height * width) > CH_ATTR_SIZE) {
        /* better than nothing: exit if transient size is too big */
        return;
    }

    if (width != s->last_width || height != s->last_height ||
        cw != s->last_cw || cheight != s->last_ch) {
        s->last_scr_width = width * cw;
        s->last_scr_height = height * cheight;
        s->last_width = width;
        s->last_height = height;
        s->last_ch = cheight;
        s->last_cw = cw;
        full_update = 1;
    }
    cursor_offset = ((s->cr[0x0e] << 8) | s->cr[0x0f]) - s->start_addr;
    if (cursor_offset != s->cursor_offset ||
        s->cr[0xa] != s->cursor_start ||
        s->cr[0xb] != s->cursor_end) {
      /* if the cursor position changed, we update the old and new
         chars */
        if (s->cursor_offset < CH_ATTR_SIZE)
            s->last_ch_attr[s->cursor_offset] = -1;
        if (cursor_offset < CH_ATTR_SIZE)
            s->last_ch_attr[cursor_offset] = -1;
        s->cursor_offset = cursor_offset;
        s->cursor_start = s->cr[0xa];
        s->cursor_end = s->cr[0xb];
    }
    cursor_ptr = s->vram_ptr + (s->start_addr + cursor_offset) * 4;

    depth_index = get_depth_index(ds);
    if (cw == 16)
        vga_draw_glyph8 = vga_draw_glyph16_table[depth_index];
    else
        vga_draw_glyph8 = vga_draw_glyph8_table[depth_index];
    vga_draw_glyph9 = vga_draw_glyph9_table[depth_index];

    dest     = sdl_get_data(ds);
    linesize = sdl_get_linesize(ds);
    ch_attr_ptr = s->last_ch_attr;
    for(cy = 0; cy < height; cy++) {
        d1 = dest;
        src = s1;
        cx_min = width;
        cx_max = -1;
        for(cx = 0; cx < width; cx++) {
            ch_attr = *(Uns16 *)src;
            if (full_update || ch_attr != *ch_attr_ptr) {
                if (cx < cx_min)
                    cx_min = cx;
                if (cx > cx_max)
                    cx_max = cx;
                *ch_attr_ptr = ch_attr;
#ifdef WORDS_BIGENDIAN
                ch = ch_attr >> 8;
                cattr = ch_attr & 0xff;
#else
                ch = ch_attr & 0xff;
                cattr = ch_attr >> 8;
#endif
                font_ptr = font_base[(cattr >> 3) & 1];
                font_ptr += 32 * 4 * ch;
                bgcol = palette[cattr >> 4];
                fgcol = palette[cattr & 0x0f];
                if (cw != 9) {
                    vga_draw_glyph8(d1, linesize,
                                    font_ptr, cheight, fgcol, bgcol);
                } else {
                    dup9 = 0;
                    if (ch >= 0xb0 && ch <= 0xdf && (s->ar[0x10] & 0x04))
                        dup9 = 1;
                    vga_draw_glyph9(d1, linesize,
                                    font_ptr, cheight, fgcol, bgcol, dup9);
                }
                if (src == cursor_ptr &&
                    !(s->cr[0x0a] & 0x20)) {
                    Int32 line_start, line_last, h;
                    /* draw the cursor */
                    line_start = s->cr[0x0a] & 0x1f;
                    line_last = s->cr[0x0b] & 0x1f;
                    if (line_last > cheight - 1)
                        line_last = cheight - 1;
                    if (line_last >= line_start && line_start < cheight) {
                        h = line_last - line_start + 1;
                        d = d1 + linesize * line_start;
                        if (cw != 9) {
                            vga_draw_glyph8(d, linesize,
                                            cursor_glyph, h, fgcol, bgcol);
                        } else {
                            vga_draw_glyph9(d, linesize,
                                            cursor_glyph, h, fgcol, bgcol, 1);
                        }
                    }
                }
            }
            d1 += x_incr;
            src += 4;
            ch_attr_ptr++;
        }
        if (cx_max != -1) {
            sdl_update(ds,  cx_min * cw, cy * cheight, (cx_max - cx_min + 1) * cw, cheight);
        }
        dest += linesize * cheight;
        s1 += line_offset;
    }
}

static void vga_draw_blank(VGAState *s, Int32 full_update, DisplayStateP ds)
{
    Int32 i, w, val;
    Uns8 *d;

    if (!full_update)
        return ;
    if (s->last_scr_width <= 0 || s->last_scr_height <= 0)
        return;
    if (sdl_get_depth(ds) == 8)
        val = s->rgb_to_pixel(0, 0, 0);
    else
        val = 0;
    w = s->last_scr_width * ((sdl_get_depth(ds) + 7) >> 3);
    d = sdl_get_data(ds);
    for(i = 0; i < s->last_scr_height; i++) {
        memset(d, val, w);
        d += sdl_get_linesize(ds);
    }
    sdl_update(ds, 0, 0, s->last_scr_width, s->last_scr_height);
}

#ifdef SHOW_PALETTE
static void showPalette(VGAState *s){
    int i;
    vmiPrintf("Raw Palette\n");

    Uns8 *r = s->palette;
    for(i=0; i < 24; i++) {
        int c;
        for (c = 0; c < 32; c++) {
            vmiPrintf(" %02x", *r++);
        }
        vmiPrintf("\n");
    }
    vmiPrintf("\n");

    vmiPrintf("OP Palette\n");
    Uns32 *p = s->last_palette;
    for(i=0; i<32; i++) {
        int c;
        for (c = 0; c < 8; c++) {
            vmiPrintf(" %06x", *p++);
        }
        vmiPrintf("\n");
    }
    vmiPrintf("\n");
}
#endif
/*
 * graphic modes
 */
static void vga_draw_graphic(VGAState *s, Int32 full_update, DisplayStateP ds)
{
    Int32 y1, y, update, page_min, page_max, linesize, y_start, double_scan, mask;
    Int32 width, height, shift_control, line_offset, page0, page1, bwidth;
    Int32 disp_width, multi_scan, multi_run;
    Uns8 *d;
    Uns32 v, addr1, addr;
    vga_draw_line_func *vga_draw_line;

    full_update |= update_basic_params(s);

    s->get_resolution(s, &width, &height);
    disp_width = width;

    shift_control = (s->gr[0x05] >> 5) & 3;
    double_scan = (s->cr[0x09] >> 7);
    if (shift_control != 1) {
        multi_scan = (((s->cr[0x09] & 0x1f) + 1) << double_scan) - 1;
    } else {
        /* in CGA modes, multi_scan is ignored */
        /* XXX: is it correct ? */
        multi_scan = double_scan;
    }
    multi_run = multi_scan;
    if (shift_control != s->shift_control ||
        double_scan != s->double_scan) {
        full_update = 1;
        s->shift_control = shift_control;
        s->double_scan = double_scan;
    }

    if (shift_control == 0) {
        full_update |= update_palette16(s);
        if (s->sr[0x01] & 8) {
            v = VGA_DRAW_LINE4D2;
            disp_width <<= 1;
        } else {
            v = VGA_DRAW_LINE4;
        }
    } else if (shift_control == 1) {
        full_update |= update_palette16(s);
        if (s->sr[0x01] & 8) {
            v = VGA_DRAW_LINE2D2;
            disp_width <<= 1;
        } else {
            v = VGA_DRAW_LINE2;
        }
    } else {
        switch(s->get_bpp(s)) {
        default:
        case 0:
            full_update |= update_palette256(s);
            v = VGA_DRAW_LINE8D2;
            break;
        case 8:
            full_update |= update_palette256(s);
            v = VGA_DRAW_LINE8;
            break;
        case 15:
            v = VGA_DRAW_LINE15;
            break;
        case 16:
            v = VGA_DRAW_LINE16;
            break;
        case 24:
            v = VGA_DRAW_LINE24;
            break;
        case 32:
            v = VGA_DRAW_LINE32;
            break;
        }
    }
#ifdef SHOW_PALETTE
    showPalette(s);
#endif
    vga_draw_line = vga_draw_line_table[v * NB_DEPTHS + get_depth_index(ds)];

    if (disp_width != s->last_width ||
        height != s->last_height) {
        s->last_scr_width = disp_width;
        s->last_scr_height = height;
        s->last_width = disp_width;
        s->last_height = height;
        full_update = 1;
    }
    if (s->cursor_invalidate)
        s->cursor_invalidate(s);

    line_offset = s->line_offset;
#if 0
    printf("w=%d h=%d v=%d line_offset=%d cr[0x09]=0x%02x cr[0x17]=0x%02x linecmp=%d sr[0x01]=0x%02x\n",
           width, height, v, line_offset, s->cr[9], s->cr[0x17], s->line_compare, s->sr[0x01]);
#endif
    addr1    = (s->start_addr * 4);
    bwidth   = width * 4;
    y_start  = -1;
    page_min = 0x7fffffff;
    page_max = -1;
    d        = sdl_get_data(ds);
    linesize = sdl_get_linesize(ds);
    y1 = 0;
    for(y = 0; y < height; y++) {
        addr = addr1;
        if (!(s->cr[0x17] & 1)) {
            Int32 shift;
            /* CGA compatibility handling */
            shift = 14 + ((s->cr[0x17] >> 6) & 1);
            addr = (addr & ~(1 << shift)) | ((y1 & 1) << shift);
        }
        if (!(s->cr[0x17] & 2)) {
            addr = (addr & ~0x8000) | ((y1 & 2) << 14);
        }
        page0 = s->vram_offset + (addr & TARGET_PAGE_MASK);
        page1 = s->vram_offset + ((addr + bwidth - 1) & TARGET_PAGE_MASK);
        update = full_update |
            cpu_physical_memory_get_dirty(page0, VGA_DIRTY_FLAG) |
            cpu_physical_memory_get_dirty(page1, VGA_DIRTY_FLAG);
        if ((page1 - page0) > TARGET_PAGE_SIZE) {
            /* if wide line, can use another page */
            update |= cpu_physical_memory_get_dirty(page0 + TARGET_PAGE_SIZE,
                                                    VGA_DIRTY_FLAG);
        }
        /* explicit invalidation for the hardware cursor */
        update |= (s->invalidated_y_table[y >> 5] >> (y & 0x1f)) & 1;
        if (update) {
            if (y_start < 0)
                y_start = y;
            if (page0 < page_min)
                page_min = page0;
            if (page1 > page_max)
                page_max = page1;
            vga_draw_line(s, d, s->vram_ptr + addr, width);
            if (s->cursor_draw_line)
                s->cursor_draw_line(s, d, y);
        } else {
            if (y_start >= 0) {
                /* flush to display */
                sdl_update(ds, 0, y_start,disp_width, y - y_start);
                y_start = -1;
            }
        }
        if (!multi_run) {
            mask = (s->cr[0x17] & 3) ^ 3;
            if ((y1 & mask) == mask)
                addr1 += line_offset;
            y1++;
            multi_run = multi_scan;
        } else {
            multi_run--;
        }
        /* line compare acts on the displayed lines */
        if (y == s->line_compare)
            addr1 = 0;
        d += linesize;
    }
    if (y_start >= 0) {
        /* flush to display */
        sdl_update(ds, 0, y_start, disp_width, y - y_start);
    }
    /* reset modified pages */
    if (page_max != -1) {
        cpu_physical_memory_reset_dirty(page_min, page_max + TARGET_PAGE_SIZE,
                                        VGA_DIRTY_FLAG);
    }
    memset(s->invalidated_y_table, 0, ((height + 31) >> 5) * 4);
}



#define GMODE_TEXT     0
#define GMODE_GRAPH    1
#define GMODE_BLANK    2

void vga_update_display(VGAState *s, DisplayStateP ds)
{
    // if graphics is enabled or checksumming is enabled,
    if (s && ds && sdl_get_data(ds)) {
        Int32 graphic_mode;
        s->rgb_to_pixel = rgb_to_pixel_dup_table[get_depth_index(ds)];

        Int32 full_update = 0;
        if (!(s->ar_index & 0x20)) {
            graphic_mode = GMODE_BLANK;
        } else {
            graphic_mode = s->gr[6] & 1;
        }
        if (graphic_mode != s->graphic_mode) {
            s->graphic_mode = graphic_mode;
            full_update = 1;
        }
        switch(graphic_mode) {
            case GMODE_TEXT:
                vga_draw_text(s, full_update, ds);
                break;

            case GMODE_GRAPH:
                vga_draw_graphic(s, full_update, ds);
                break;

            case GMODE_BLANK:
            default:
                vga_draw_blank(s, full_update, ds);
                break;
        }
    }
}

