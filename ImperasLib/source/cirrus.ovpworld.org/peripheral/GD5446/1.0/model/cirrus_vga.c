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


/*
 * Reference: Finn Thogersons' VGADOC4b
 *   available at http://home.worldonline.dk/~finth/
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hostapi/impTypes.h"
#include "types.h"
#include "vga_state.h"
#include "vga_display.h"
#include "vga_common.h"
#include "cirrus_vga.h"
#include "cirrus_constants.h"
#include "bswap.h"

#include "vmi/vmiMessage.h"

//#define TRCDEBUG
#ifdef TRCDEBUG
FILE *vga_trcf = NULL;
#define TRCOPEN  if(!vga_trcf) vga_trcf = fopen("cirrus_vga.log", "w");
#define TRCCLOSE fclose(vga_trcf);
#define TRC(F) \
    { \
        fprintf(vga_trcf, "cirrus_vga.c:%s\n", F); \
        fflush(vga_trcf); \
    }
// usage TRC(__func__)
#else
#define TRCOPEN
#define TRCCLOSE
#define TRC(F)
#endif

#define PREFIX_WRITE  "VGA_IOW"
#define PREFIX_READ   "VGA_IOR"
#define PREFIX_DBG    "VGA_DBG"

/***************************************
 *
 *  definitions
 *
 ***************************************/

/* I/O and memory hook */
#define CIRRUS_HOOK_NOT_HANDLED 0
#define CIRRUS_HOOK_HANDLED 1

static Uns8 rop_to_index[256];

static const Uns8 sr_mask[8] = {
    (Uns8)~0xfc,
    (Uns8)~0xc2,
    (Uns8)~0xf0,
    (Uns8)~0xc0,
    (Uns8)~0xf1,
    (Uns8)~0xff,
    (Uns8)~0xff,
    (Uns8)~0x00,
};

static const Uns8 gr_mask[16] = {
    (Uns8)~0xf0, /* 0x00 */
    (Uns8)~0xf0, /* 0x01 */
    (Uns8)~0xf0, /* 0x02 */
    (Uns8)~0xe0, /* 0x03 */
    (Uns8)~0xfc, /* 0x04 */
    (Uns8)~0x84, /* 0x05 */
    (Uns8)~0xf0, /* 0x06 */
    (Uns8)~0xf0, /* 0x07 */
    (Uns8)~0x00, /* 0x08 */
    (Uns8)~0xff, /* 0x09 */
    (Uns8)~0xff, /* 0x0a */
    (Uns8)~0xff, /* 0x0b */
    (Uns8)~0xff, /* 0x0c */
    (Uns8)~0xff, /* 0x0d */
    (Uns8)~0xff, /* 0x0e */
    (Uns8)~0xff, /* 0x0f */
};


/***************************************
 *
 *  prototypes.
 *
 ***************************************/


static void cirrus_bitblt_reset(CirrusVGAStateP s);
static void cirrus_update_memory_access(CirrusVGAStateP s);

void vga_draw_cursor_line_8(Uns8 *d1, const Uns8 *src1,
                            Int32 poffset, Int32 w,
                            Uns32 color0, Uns32 color1,
                            Uns32 color_xor);

void vga_draw_cursor_line_16(Uns8 *d1, const Uns8 *src1,
                             Int32 poffset, Int32 w,
                             Uns32 color0, Uns32 color1,
                             Uns32 color_xor);

void vga_draw_cursor_line_32(Uns8 *d1, const Uns8 *src1,
                             Int32 poffset, Int32 w,
                             Uns32 color0, Uns32 color1,
                             Uns32 color_xor);

/***************************************
 *
 *  raster operations
 *
 ***************************************/

static void cirrus_bitblt_rop_nop(CirrusVGAStateP s,
                                  Uns8 *dst,const Uns8 *src,
                                  Int32 dstpitch,Int32 srcpitch,
                                  Int32 bltwidth,Int32 bltheight)
{
}

static void cirrus_bitblt_fill_nop(CirrusVGAStateP s,
                                   Uns8 *dst,
                                   Int32 dstpitch, Int32 bltwidth,Int32 bltheight)
{
}

#define ROP_NAME 0
#define ROP_OP(d, s) d = 0
#include "cirrus_vga_rop.h"

#define ROP_NAME src_and_dst
#define ROP_OP(d, s) d = (s) & (d)
#include "cirrus_vga_rop.h"

#define ROP_NAME src_and_notdst
#define ROP_OP(d, s) d = (s) & (~(d))
#include "cirrus_vga_rop.h"

#define ROP_NAME notdst
#define ROP_OP(d, s) d = ~(d)
#include "cirrus_vga_rop.h"

#define ROP_NAME src
#define ROP_OP(d, s) d = s
#include "cirrus_vga_rop.h"

#define ROP_NAME 1
#define ROP_OP(d, s) d = ~0
#include "cirrus_vga_rop.h"

#define ROP_NAME notsrc_and_dst
#define ROP_OP(d, s) d = (~(s)) & (d)
#include "cirrus_vga_rop.h"

#define ROP_NAME src_xor_dst
#define ROP_OP(d, s) d = (s) ^ (d)
#include "cirrus_vga_rop.h"

#define ROP_NAME src_or_dst
#define ROP_OP(d, s) d = (s) | (d)
#include "cirrus_vga_rop.h"

#define ROP_NAME notsrc_or_notdst
#define ROP_OP(d, s) d = (~(s)) | (~(d))
#include "cirrus_vga_rop.h"

#define ROP_NAME src_notxor_dst
#define ROP_OP(d, s) d = ~((s) ^ (d))
#include "cirrus_vga_rop.h"

#define ROP_NAME src_or_notdst
#define ROP_OP(d, s) d = (s) | (~(d))
#include "cirrus_vga_rop.h"

#define ROP_NAME notsrc
#define ROP_OP(d, s) d = (~(s))
#include "cirrus_vga_rop.h"

#define ROP_NAME notsrc_or_dst
#define ROP_OP(d, s) d = (~(s)) | (d)
#include "cirrus_vga_rop.h"

#define ROP_NAME notsrc_and_notdst
#define ROP_OP(d, s) d = (~(s)) & (~(d))
#include "cirrus_vga_rop.h"

static const cirrus_bitblt_rop_t cirrus_fwd_rop[16] = {
    cirrus_bitblt_rop_fwd_0,
    cirrus_bitblt_rop_fwd_src_and_dst,
    cirrus_bitblt_rop_nop,
    cirrus_bitblt_rop_fwd_src_and_notdst,
    cirrus_bitblt_rop_fwd_notdst,
    cirrus_bitblt_rop_fwd_src,
    cirrus_bitblt_rop_fwd_1,
    cirrus_bitblt_rop_fwd_notsrc_and_dst,
    cirrus_bitblt_rop_fwd_src_xor_dst,
    cirrus_bitblt_rop_fwd_src_or_dst,
    cirrus_bitblt_rop_fwd_notsrc_or_notdst,
    cirrus_bitblt_rop_fwd_src_notxor_dst,
    cirrus_bitblt_rop_fwd_src_or_notdst,
    cirrus_bitblt_rop_fwd_notsrc,
    cirrus_bitblt_rop_fwd_notsrc_or_dst,
    cirrus_bitblt_rop_fwd_notsrc_and_notdst,
};

static const cirrus_bitblt_rop_t cirrus_bkwd_rop[16] = {
    cirrus_bitblt_rop_bkwd_0,
    cirrus_bitblt_rop_bkwd_src_and_dst,
    cirrus_bitblt_rop_nop,
    cirrus_bitblt_rop_bkwd_src_and_notdst,
    cirrus_bitblt_rop_bkwd_notdst,
    cirrus_bitblt_rop_bkwd_src,
    cirrus_bitblt_rop_bkwd_1,
    cirrus_bitblt_rop_bkwd_notsrc_and_dst,
    cirrus_bitblt_rop_bkwd_src_xor_dst,
    cirrus_bitblt_rop_bkwd_src_or_dst,
    cirrus_bitblt_rop_bkwd_notsrc_or_notdst,
    cirrus_bitblt_rop_bkwd_src_notxor_dst,
    cirrus_bitblt_rop_bkwd_src_or_notdst,
    cirrus_bitblt_rop_bkwd_notsrc,
    cirrus_bitblt_rop_bkwd_notsrc_or_dst,
    cirrus_bitblt_rop_bkwd_notsrc_and_notdst,
};

#define TRANSP_ROP(name) {\
    name ## _8,\
    name ## _16,\
        }
#define TRANSP_NOP(func) {\
    func,\
    func,\
        }

static const cirrus_bitblt_rop_t cirrus_fwd_transp_rop[16][2] = {
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_0),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src_and_dst),
    TRANSP_NOP(cirrus_bitblt_rop_nop),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src_and_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_1),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_notsrc_and_dst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src_xor_dst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src_or_dst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_notsrc_or_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src_notxor_dst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_src_or_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_notsrc),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_notsrc_or_dst),
    TRANSP_ROP(cirrus_bitblt_rop_fwd_transp_notsrc_and_notdst),
};

static const cirrus_bitblt_rop_t cirrus_bkwd_transp_rop[16][2] = {
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_0),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src_and_dst),
    TRANSP_NOP(cirrus_bitblt_rop_nop),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src_and_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_1),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_notsrc_and_dst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src_xor_dst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src_or_dst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_notsrc_or_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src_notxor_dst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_src_or_notdst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_notsrc),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_notsrc_or_dst),
    TRANSP_ROP(cirrus_bitblt_rop_bkwd_transp_notsrc_and_notdst),
};

#define ROP2(name) {\
    name ## _8,\
    name ## _16,\
    name ## _24,\
    name ## _32,\
        }

#define ROP_NOP2(func) {\
    func,\
    func,\
    func,\
    func,\
        }

static const cirrus_bitblt_rop_t cirrus_patternfill[16][4] = {
    ROP2(cirrus_patternfill_0),
    ROP2(cirrus_patternfill_src_and_dst),
    ROP_NOP2(cirrus_bitblt_rop_nop),
    ROP2(cirrus_patternfill_src_and_notdst),
    ROP2(cirrus_patternfill_notdst),
    ROP2(cirrus_patternfill_src),
    ROP2(cirrus_patternfill_1),
    ROP2(cirrus_patternfill_notsrc_and_dst),
    ROP2(cirrus_patternfill_src_xor_dst),
    ROP2(cirrus_patternfill_src_or_dst),
    ROP2(cirrus_patternfill_notsrc_or_notdst),
    ROP2(cirrus_patternfill_src_notxor_dst),
    ROP2(cirrus_patternfill_src_or_notdst),
    ROP2(cirrus_patternfill_notsrc),
    ROP2(cirrus_patternfill_notsrc_or_dst),
    ROP2(cirrus_patternfill_notsrc_and_notdst),
};

static const cirrus_bitblt_rop_t cirrus_colorexpand_transp[16][4] = {
    ROP2(cirrus_colorexpand_transp_0),
    ROP2(cirrus_colorexpand_transp_src_and_dst),
    ROP_NOP2(cirrus_bitblt_rop_nop),
    ROP2(cirrus_colorexpand_transp_src_and_notdst),
    ROP2(cirrus_colorexpand_transp_notdst),
    ROP2(cirrus_colorexpand_transp_src),
    ROP2(cirrus_colorexpand_transp_1),
    ROP2(cirrus_colorexpand_transp_notsrc_and_dst),
    ROP2(cirrus_colorexpand_transp_src_xor_dst),
    ROP2(cirrus_colorexpand_transp_src_or_dst),
    ROP2(cirrus_colorexpand_transp_notsrc_or_notdst),
    ROP2(cirrus_colorexpand_transp_src_notxor_dst),
    ROP2(cirrus_colorexpand_transp_src_or_notdst),
    ROP2(cirrus_colorexpand_transp_notsrc),
    ROP2(cirrus_colorexpand_transp_notsrc_or_dst),
    ROP2(cirrus_colorexpand_transp_notsrc_and_notdst),
};

static const cirrus_bitblt_rop_t cirrus_colorexpand[16][4] = {
    ROP2(cirrus_colorexpand_0),
    ROP2(cirrus_colorexpand_src_and_dst),
    ROP_NOP2(cirrus_bitblt_rop_nop),
    ROP2(cirrus_colorexpand_src_and_notdst),
    ROP2(cirrus_colorexpand_notdst),
    ROP2(cirrus_colorexpand_src),
    ROP2(cirrus_colorexpand_1),
    ROP2(cirrus_colorexpand_notsrc_and_dst),
    ROP2(cirrus_colorexpand_src_xor_dst),
    ROP2(cirrus_colorexpand_src_or_dst),
    ROP2(cirrus_colorexpand_notsrc_or_notdst),
    ROP2(cirrus_colorexpand_src_notxor_dst),
    ROP2(cirrus_colorexpand_src_or_notdst),
    ROP2(cirrus_colorexpand_notsrc),
    ROP2(cirrus_colorexpand_notsrc_or_dst),
    ROP2(cirrus_colorexpand_notsrc_and_notdst),
};

static const cirrus_bitblt_rop_t cirrus_colorexpand_pattern_transp[16][4] = {
    ROP2(cirrus_colorexpand_pattern_transp_0),
    ROP2(cirrus_colorexpand_pattern_transp_src_and_dst),
    ROP_NOP2(cirrus_bitblt_rop_nop),
    ROP2(cirrus_colorexpand_pattern_transp_src_and_notdst),
    ROP2(cirrus_colorexpand_pattern_transp_notdst),
    ROP2(cirrus_colorexpand_pattern_transp_src),
    ROP2(cirrus_colorexpand_pattern_transp_1),
    ROP2(cirrus_colorexpand_pattern_transp_notsrc_and_dst),
    ROP2(cirrus_colorexpand_pattern_transp_src_xor_dst),
    ROP2(cirrus_colorexpand_pattern_transp_src_or_dst),
    ROP2(cirrus_colorexpand_pattern_transp_notsrc_or_notdst),
    ROP2(cirrus_colorexpand_pattern_transp_src_notxor_dst),
    ROP2(cirrus_colorexpand_pattern_transp_src_or_notdst),
    ROP2(cirrus_colorexpand_pattern_transp_notsrc),
    ROP2(cirrus_colorexpand_pattern_transp_notsrc_or_dst),
    ROP2(cirrus_colorexpand_pattern_transp_notsrc_and_notdst),
};

static const cirrus_bitblt_rop_t cirrus_colorexpand_pattern[16][4] = {
    ROP2(cirrus_colorexpand_pattern_0),
    ROP2(cirrus_colorexpand_pattern_src_and_dst),
    ROP_NOP2(cirrus_bitblt_rop_nop),
    ROP2(cirrus_colorexpand_pattern_src_and_notdst),
    ROP2(cirrus_colorexpand_pattern_notdst),
    ROP2(cirrus_colorexpand_pattern_src),
    ROP2(cirrus_colorexpand_pattern_1),
    ROP2(cirrus_colorexpand_pattern_notsrc_and_dst),
    ROP2(cirrus_colorexpand_pattern_src_xor_dst),
    ROP2(cirrus_colorexpand_pattern_src_or_dst),
    ROP2(cirrus_colorexpand_pattern_notsrc_or_notdst),
    ROP2(cirrus_colorexpand_pattern_src_notxor_dst),
    ROP2(cirrus_colorexpand_pattern_src_or_notdst),
    ROP2(cirrus_colorexpand_pattern_notsrc),
    ROP2(cirrus_colorexpand_pattern_notsrc_or_dst),
    ROP2(cirrus_colorexpand_pattern_notsrc_and_notdst),
};

static const cirrus_fill_t cirrus_fill[16][4] = {
    ROP2(cirrus_fill_0),
    ROP2(cirrus_fill_src_and_dst),
    ROP_NOP2(cirrus_bitblt_fill_nop),
    ROP2(cirrus_fill_src_and_notdst),
    ROP2(cirrus_fill_notdst),
    ROP2(cirrus_fill_src),
    ROP2(cirrus_fill_1),
    ROP2(cirrus_fill_notsrc_and_dst),
    ROP2(cirrus_fill_src_xor_dst),
    ROP2(cirrus_fill_src_or_dst),
    ROP2(cirrus_fill_notsrc_or_notdst),
    ROP2(cirrus_fill_src_notxor_dst),
    ROP2(cirrus_fill_src_or_notdst),
    ROP2(cirrus_fill_notsrc),
    ROP2(cirrus_fill_notsrc_or_dst),
    ROP2(cirrus_fill_notsrc_and_notdst),
};

static inline void cirrus_bitblt_fgcol(CirrusVGAStateP s)
{
    Uns32 color;
    switch (s->cirrus_blt_pixelwidth) {
    case 1:
        s->cirrus_blt_fgcol = s->cirrus_shadow_gr1;
        break;
    case 2:
        color = s->cirrus_shadow_gr1 | (s->gr[0x11] << 8);
        s->cirrus_blt_fgcol = le16_to_cpu(color);
        break;
    case 3:
        s->cirrus_blt_fgcol = s->cirrus_shadow_gr1 |
            (s->gr[0x11] << 8) | (s->gr[0x13] << 16);
        break;
    default:
    case 4:
        color = s->cirrus_shadow_gr1 | (s->gr[0x11] << 8) |
            (s->gr[0x13] << 16) | (s->gr[0x15] << 24);
        s->cirrus_blt_fgcol = le32_to_cpu(color);
        break;
    }
}

static inline void cirrus_bitblt_bgcol(CirrusVGAStateP s)
{
    Uns32 color;
    switch (s->cirrus_blt_pixelwidth) {
    case 1:
        s->cirrus_blt_bgcol = s->cirrus_shadow_gr0;
        break;
    case 2:
        color = s->cirrus_shadow_gr0 | (s->gr[0x10] << 8);
        s->cirrus_blt_bgcol = le16_to_cpu(color);
        break;
    case 3:
        s->cirrus_blt_bgcol = s->cirrus_shadow_gr0 |
            (s->gr[0x10] << 8) | (s->gr[0x12] << 16);
        break;
    default:
    case 4:
        color = s->cirrus_shadow_gr0 | (s->gr[0x10] << 8) |
            (s->gr[0x12] << 16) | (s->gr[0x14] << 24);
        s->cirrus_blt_bgcol = le32_to_cpu(color);
        break;
    }
}

static void cirrus_invalidate_region(CirrusVGAStateP  s, Int32 off_begin,
                     Int32 off_pitch, Int32 bytesperline,
                     Int32 lines)
{
    Int32 y;
    Int32 off_cur;
    Int32 off_cur_end;

    for (y = 0; y < lines; y++) {
    off_cur = off_begin;
    off_cur_end = off_cur + bytesperline;
    off_cur &= TARGET_PAGE_MASK;
    while (off_cur < off_cur_end) {
        //cpu_physical_memory_set_dirty(s->vram_offset + off_cur);
        off_cur += TARGET_PAGE_SIZE;
    }
    off_begin += off_pitch;
    }
}

static Int32 cirrus_bitblt_common_patterncopy(CirrusVGAStateP  s,
                        const Uns8 * src)
{
    Uns8 *dst;

    dst = s->vram_ptr + s->cirrus_blt_dstaddr;
    (*s->cirrus_rop) (s, dst, src,
                      s->cirrus_blt_dstpitch, 0,
                      s->cirrus_blt_width, s->cirrus_blt_height);
    cirrus_invalidate_region(s, s->cirrus_blt_dstaddr,
                             s->cirrus_blt_dstpitch, s->cirrus_blt_width,
                             s->cirrus_blt_height);
    return 1;
}

/* fill */

static Int32 cirrus_bitblt_solidfill(CirrusVGAStateP s, Int32 blt_rop)
{
    TRC(__func__)
    cirrus_fill_t rop_func;

    rop_func = cirrus_fill[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
    rop_func(s, s->vram_ptr + s->cirrus_blt_dstaddr,
             s->cirrus_blt_dstpitch,
             s->cirrus_blt_width, s->cirrus_blt_height);
    cirrus_invalidate_region(s, s->cirrus_blt_dstaddr,
                 s->cirrus_blt_dstpitch, s->cirrus_blt_width,
                 s->cirrus_blt_height);
    cirrus_bitblt_reset(s);
    return 1;
}

/***************************************
 *
 *  bitblt (video-to-video)
 *
 ***************************************/

static Int32 cirrus_bitblt_videotovideo_patterncopy(CirrusVGAStateP  s)
{
    return cirrus_bitblt_common_patterncopy(s,
                        s->vram_ptr +
                                            (s->cirrus_blt_srcaddr & ~7));
}

static void cirrus_do_copy(CirrusVGAStateP s, Int32 dst, Int32 src, Int32 w, Int32 h)
{
    Int32 sx, sy;
    Int32 dx, dy;
    Int32 width, height;
    Int32 depth;
    Int32 notify = 0;

    depth = s->get_bpp((VGAState *)s) / 8;
    s->get_resolution((VGAState *)s, &width, &height);

    /* extra x, y */
    sx = (src % (width * depth)) / depth;
    sy = (src / (width * depth));
    dx = (dst % (width *depth)) / depth;
    dy = (dst / (width * depth));

    /* normalize width */
    w /= depth;

    /* if we're doing a backward copy, we have to adjust
       our x/y to be the upper left corner (instead of the lower
       right corner) */
    if (s->cirrus_blt_dstpitch < 0) {
    sx -= (s->cirrus_blt_width / depth) - 1;
    dx -= (s->cirrus_blt_width / depth) - 1;
    sy -= s->cirrus_blt_height - 1;
    dy -= s->cirrus_blt_height - 1;
    }

    /* are we in the visible portion of memory? */
    if (sx >= 0 && sy >= 0 && dx >= 0 && dy >= 0 &&
    (sx + w) <= width && (sy + h) <= height &&
    (dx + w) <= width && (dy + h) <= height) {
    notify = 1;
    }

    /* make to sure only copy if it's a plain copy ROP */
    if (*s->cirrus_rop != cirrus_bitblt_rop_fwd_src &&
    *s->cirrus_rop != cirrus_bitblt_rop_bkwd_src)
    notify = 0;

    /* we have to flush all pending changes so that the copy
       is generated at the appropriate moment in time */
    //if (notify)
    //vga_hw_update();

    (*s->cirrus_rop) (s, s->vram_ptr + s->cirrus_blt_dstaddr,
              s->vram_ptr + s->cirrus_blt_srcaddr,
              s->cirrus_blt_dstpitch, s->cirrus_blt_srcpitch,
              s->cirrus_blt_width, s->cirrus_blt_height);

#ifdef IMPERAS_USED
    if (notify)
        s->ds->dpy_copy(s->ds,
            sx, sy, dx, dy,
            s->cirrus_blt_width / depth,
            s->cirrus_blt_height);
#endif
    /* we don't have to notify the display that this portion has
       changed since dpy_copy implies this */

    if (!notify)
    cirrus_invalidate_region(s, s->cirrus_blt_dstaddr,
                 s->cirrus_blt_dstpitch, s->cirrus_blt_width,
                 s->cirrus_blt_height);
}

static Int32 cirrus_bitblt_videotovideo_copy(CirrusVGAStateP  s)
{
    if (1 /* IMPERAS s->ds->dpy_copy*/) {
    cirrus_do_copy(s, s->cirrus_blt_dstaddr - s->start_addr,
               s->cirrus_blt_srcaddr - s->start_addr,
               s->cirrus_blt_width, s->cirrus_blt_height);
    } else {
    (*s->cirrus_rop) (s, s->vram_ptr + s->cirrus_blt_dstaddr,
              s->vram_ptr + s->cirrus_blt_srcaddr,
              s->cirrus_blt_dstpitch, s->cirrus_blt_srcpitch,
              s->cirrus_blt_width, s->cirrus_blt_height);

    cirrus_invalidate_region(s, s->cirrus_blt_dstaddr,
                 s->cirrus_blt_dstpitch, s->cirrus_blt_width,
                 s->cirrus_blt_height);
    }

    return 1;
}

/***************************************
 *
 *  bitblt (cpu-to-video)
 *
 ***************************************/

static void cirrus_bitblt_cputovideo_next(CirrusVGAStateP  s)
{
    TRC(__func__)
    Int32 copy_count;
    Uns8 *end_ptr;

    if (s->cirrus_srccounter > 0) {
        if (s->cirrus_blt_mode & CIRRUS_BLTMODE_PATTERNCOPY) {
            cirrus_bitblt_common_patterncopy(s, s->cirrus_bltbuf);
        the_end:
            s->cirrus_srccounter = 0;
            cirrus_bitblt_reset(s);
        } else {
            /* at least one scan line */
            do {
                (*s->cirrus_rop)(s, s->vram_ptr + s->cirrus_blt_dstaddr,
                                 s->cirrus_bltbuf, 0, 0, s->cirrus_blt_width, 1);
                cirrus_invalidate_region(s, s->cirrus_blt_dstaddr, 0,
                                         s->cirrus_blt_width, 1);
                s->cirrus_blt_dstaddr += s->cirrus_blt_dstpitch;
                s->cirrus_srccounter -= s->cirrus_blt_srcpitch;
                if (s->cirrus_srccounter <= 0)
                    goto the_end;
                /* more bytes than needed can be transfered because of
                   word alignment, so we keep them for the next line */
                /* XXX: keep alignment to speed up transfer */
                end_ptr = s->cirrus_bltbuf + s->cirrus_blt_srcpitch;
                copy_count = s->cirrus_srcptr_end - end_ptr;
                memmove(s->cirrus_bltbuf, end_ptr, copy_count);
                s->cirrus_srcptr = s->cirrus_bltbuf + copy_count;
                s->cirrus_srcptr_end = s->cirrus_bltbuf + s->cirrus_blt_srcpitch;
            } while (s->cirrus_srcptr >= s->cirrus_srcptr_end);
        }
    }
}

/***************************************
 *
 *  bitblt wrapper
 *
 ***************************************/

static void cirrus_bitblt_reset(CirrusVGAStateP  s)
{
    TRC(__func__)
//    fprintf(vga_trcf, "cirrus_vga.c:->%s gr[0x31]=0x%02x\n",
//            __func__, s->gr[0x31]); fflush(vga_trcf);

    s->gr[0x31] &=
    ~(CIRRUS_BLT_START | CIRRUS_BLT_BUSY | CIRRUS_BLT_FIFOUSED);
    s->cirrus_srcptr = &s->cirrus_bltbuf[0];
    s->cirrus_srcptr_end = &s->cirrus_bltbuf[0];
    s->cirrus_srccounter = 0;
//    fprintf(vga_trcf, "cirrus_vga.c:%s gr[0x31]=0x%02x\n",
//            __func__, s->gr[0x31]); fflush(vga_trcf);
    cirrus_update_memory_access(s);
//    fprintf(vga_trcf, "cirrus_vga.c:<-%s gr[0x31]=0x%02x\n",
//            __func__, s->gr[0x31]); fflush(vga_trcf);
}

static Int32 cirrus_bitblt_cputovideo(CirrusVGAStateP  s)
{
    Int32 w;

    s->cirrus_blt_mode &= ~CIRRUS_BLTMODE_MEMSYSSRC;
    s->cirrus_srcptr = &s->cirrus_bltbuf[0];
    s->cirrus_srcptr_end = &s->cirrus_bltbuf[0];

    if (s->cirrus_blt_mode & CIRRUS_BLTMODE_PATTERNCOPY) {
    if (s->cirrus_blt_mode & CIRRUS_BLTMODE_COLOREXPAND) {
        s->cirrus_blt_srcpitch = 8;
    } else {
            /* XXX: check for 24 bpp */
        s->cirrus_blt_srcpitch = 8 * 8 * s->cirrus_blt_pixelwidth;
    }
    s->cirrus_srccounter = s->cirrus_blt_srcpitch;
    } else {
    if (s->cirrus_blt_mode & CIRRUS_BLTMODE_COLOREXPAND) {
        w = s->cirrus_blt_width / s->cirrus_blt_pixelwidth;
        if (s->cirrus_blt_modeext & CIRRUS_BLTMODEEXT_DWORDGRANULARITY)
            s->cirrus_blt_srcpitch = ((w + 31) >> 5);
        else
            s->cirrus_blt_srcpitch = ((w + 7) >> 3);
    } else {
        /* always align input size to 32 bits */
        s->cirrus_blt_srcpitch = (s->cirrus_blt_width + 3) & ~3;
    }
        s->cirrus_srccounter = s->cirrus_blt_srcpitch * s->cirrus_blt_height;
    }
    s->cirrus_srcptr = s->cirrus_bltbuf;
    s->cirrus_srcptr_end = s->cirrus_bltbuf + s->cirrus_blt_srcpitch;
    cirrus_update_memory_access(s);
    return 1;
}

static Int32 cirrus_bitblt_videotocpu(CirrusVGAStateP  s)
{
    /* XXX */
#ifdef DEBUG_BITBLT
    vmiMessage("I", "VGA_NOTIMP", "cirrus: bitblt (video to cpu) is not implemented yet\n");
#endif
    return 0;
}

static Int32 cirrus_bitblt_videotovideo(CirrusVGAStateP  s)
{
    TRC(__func__)
    Int32 ret;

    if (s->cirrus_blt_mode & CIRRUS_BLTMODE_PATTERNCOPY) {
    ret = cirrus_bitblt_videotovideo_patterncopy(s);
    } else {
    ret = cirrus_bitblt_videotovideo_copy(s);
    }
    if (ret)
    cirrus_bitblt_reset(s);
    return ret;
}

static void cirrus_bitblt_start(CirrusVGAStateP  s)
{
    Uns8 blt_rop;

//    fprintf(vga_trcf, "cirrus_vga.c:->%s gr[0x31]=0x%02x\n",
//            __func__, s->gr[0x31]); fflush(vga_trcf);

    s->gr[0x31] |= CIRRUS_BLT_BUSY;

    s->cirrus_blt_width = (s->gr[0x20] | (s->gr[0x21] << 8)) + 1;
    s->cirrus_blt_height = (s->gr[0x22] | (s->gr[0x23] << 8)) + 1;
    s->cirrus_blt_dstpitch = (s->gr[0x24] | (s->gr[0x25] << 8));
    s->cirrus_blt_srcpitch = (s->gr[0x26] | (s->gr[0x27] << 8));
    s->cirrus_blt_dstaddr =
    (s->gr[0x28] | (s->gr[0x29] << 8) | (s->gr[0x2a] << 16));
    s->cirrus_blt_srcaddr =
    (s->gr[0x2c] | (s->gr[0x2d] << 8) | (s->gr[0x2e] << 16));
    s->cirrus_blt_mode = s->gr[0x30];
    s->cirrus_blt_modeext = s->gr[0x33];
    blt_rop = s->gr[0x32];

#ifdef DEBUG_BITBLT
    vmiMessage("I", "VGA_BITBLT", "rop=0x%02x mode=0x%02x modeext=0x%02x w=%d h=%d dpitch=%d spitch=%d daddr=0x%08x saddr=0x%08x writemask=0x%02x\n",
           blt_rop,
           s->cirrus_blt_mode,
           s->cirrus_blt_modeext,
           s->cirrus_blt_width,
           s->cirrus_blt_height,
           s->cirrus_blt_dstpitch,
           s->cirrus_blt_srcpitch,
           s->cirrus_blt_dstaddr,
           s->cirrus_blt_srcaddr,
           s->gr[0x2f]);
#endif

    switch (s->cirrus_blt_mode & CIRRUS_BLTMODE_PIXELWIDTHMASK) {
    case CIRRUS_BLTMODE_PIXELWIDTH8:
    s->cirrus_blt_pixelwidth = 1;
    break;
    case CIRRUS_BLTMODE_PIXELWIDTH16:
    s->cirrus_blt_pixelwidth = 2;
    break;
    case CIRRUS_BLTMODE_PIXELWIDTH24:
    s->cirrus_blt_pixelwidth = 3;
    break;
    case CIRRUS_BLTMODE_PIXELWIDTH32:
    s->cirrus_blt_pixelwidth = 4;
    break;
    default:
#ifdef DEBUG_BITBLT
    vmiMessage("I", "VGA_BITBLT", "cirrus: bitblt - pixel width is unknown\n");
#endif
    goto bitblt_ignore;
    }
    s->cirrus_blt_mode &= ~CIRRUS_BLTMODE_PIXELWIDTHMASK;

    if ((s->
     cirrus_blt_mode & (CIRRUS_BLTMODE_MEMSYSSRC |
                CIRRUS_BLTMODE_MEMSYSDEST))
    == (CIRRUS_BLTMODE_MEMSYSSRC | CIRRUS_BLTMODE_MEMSYSDEST)) {
#ifdef DEBUG_BITBLT
    vmiMessage("I", "VGA_BITBLT", "cirrus: bitblt - memory-to-memory copy is requested\n");
#endif
    goto bitblt_ignore;
    }

    if ((s->cirrus_blt_modeext & CIRRUS_BLTMODEEXT_SOLIDFILL) &&
        (s->cirrus_blt_mode & (CIRRUS_BLTMODE_MEMSYSDEST |
                               CIRRUS_BLTMODE_TRANSPARENTCOMP |
                               CIRRUS_BLTMODE_PATTERNCOPY |
                               CIRRUS_BLTMODE_COLOREXPAND)) ==
         (CIRRUS_BLTMODE_PATTERNCOPY | CIRRUS_BLTMODE_COLOREXPAND)) {
        cirrus_bitblt_fgcol(s);
        cirrus_bitblt_solidfill(s, blt_rop);
    } else {
        if ((s->cirrus_blt_mode & (CIRRUS_BLTMODE_COLOREXPAND |
                                   CIRRUS_BLTMODE_PATTERNCOPY)) ==
            CIRRUS_BLTMODE_COLOREXPAND) {

            if (s->cirrus_blt_mode & CIRRUS_BLTMODE_TRANSPARENTCOMP) {
                if (s->cirrus_blt_modeext & CIRRUS_BLTMODEEXT_COLOREXPINV)
                    cirrus_bitblt_bgcol(s);
                else
                    cirrus_bitblt_fgcol(s);
                s->cirrus_rop = cirrus_colorexpand_transp[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
            } else {
                cirrus_bitblt_fgcol(s);
                cirrus_bitblt_bgcol(s);
                s->cirrus_rop = cirrus_colorexpand[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
            }
        } else if (s->cirrus_blt_mode & CIRRUS_BLTMODE_PATTERNCOPY) {
            if (s->cirrus_blt_mode & CIRRUS_BLTMODE_COLOREXPAND) {
                if (s->cirrus_blt_mode & CIRRUS_BLTMODE_TRANSPARENTCOMP) {
                    if (s->cirrus_blt_modeext & CIRRUS_BLTMODEEXT_COLOREXPINV)
                        cirrus_bitblt_bgcol(s);
                    else
                        cirrus_bitblt_fgcol(s);
                    s->cirrus_rop = cirrus_colorexpand_pattern_transp[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
                } else {
                    cirrus_bitblt_fgcol(s);
                    cirrus_bitblt_bgcol(s);
                    s->cirrus_rop = cirrus_colorexpand_pattern[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
                }
            } else {
                s->cirrus_rop = cirrus_patternfill[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
            }
        } else {
        if (s->cirrus_blt_mode & CIRRUS_BLTMODE_TRANSPARENTCOMP) {
        if (s->cirrus_blt_pixelwidth > 2) {
            vmiMessage("I", "VGA_BITBLT", "src transparent without colorexpand must be 8bpp or 16bpp\n");
            goto bitblt_ignore;
        }
        if (s->cirrus_blt_mode & CIRRUS_BLTMODE_BACKWARDS) {
            s->cirrus_blt_dstpitch = -s->cirrus_blt_dstpitch;
            s->cirrus_blt_srcpitch = -s->cirrus_blt_srcpitch;
            s->cirrus_rop = cirrus_bkwd_transp_rop[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
        } else {
            s->cirrus_rop = cirrus_fwd_transp_rop[rop_to_index[blt_rop]][s->cirrus_blt_pixelwidth - 1];
        }
        } else {
        if (s->cirrus_blt_mode & CIRRUS_BLTMODE_BACKWARDS) {
            s->cirrus_blt_dstpitch = -s->cirrus_blt_dstpitch;
            s->cirrus_blt_srcpitch = -s->cirrus_blt_srcpitch;
            s->cirrus_rop = cirrus_bkwd_rop[rop_to_index[blt_rop]];
        } else {
            s->cirrus_rop = cirrus_fwd_rop[rop_to_index[blt_rop]];
        }
        }
    }
        // setup bitblt engine.
        if (s->cirrus_blt_mode & CIRRUS_BLTMODE_MEMSYSSRC) {
            if (!cirrus_bitblt_cputovideo(s))
                goto bitblt_ignore;
        } else if (s->cirrus_blt_mode & CIRRUS_BLTMODE_MEMSYSDEST) {
            if (!cirrus_bitblt_videotocpu(s))
                goto bitblt_ignore;
        } else {
            if (!cirrus_bitblt_videotovideo(s))
                goto bitblt_ignore;
        }
    }
    return;
  bitblt_ignore:;
    cirrus_bitblt_reset(s);
//    fprintf(vga_trcf, "cirrus_vga.c:<-%s gr[0x31]=0x%02x\n",
//            __func__, s->gr[0x31]); fflush(vga_trcf);
}

static void cirrus_write_bitblt(CirrusVGAStateP  s, Uns32 reg_value)
{
    TRC(__func__)
//    fprintf(vga_trcf, "cirrus_vga.c:->%s value=0x%02x gr[0x31]=0x%02x\n",
//            __func__, reg_value, s->gr[0x31]); fflush(vga_trcf);

    Uns32 old_value;

    old_value = s->gr[0x31];
    s->gr[0x31] = reg_value;

    if (((old_value & CIRRUS_BLT_RESET) != 0) &&
    ((reg_value & CIRRUS_BLT_RESET) == 0)) {
    cirrus_bitblt_reset(s);
    } else if (((old_value & CIRRUS_BLT_START) == 0) &&
           ((reg_value & CIRRUS_BLT_START) != 0)) {
    cirrus_bitblt_start(s);
    }

//    fprintf(vga_trcf, "cirrus_vga.c:<-%s value=0x%02x gr[0x31]=0x%02x\n",
//            __func__, reg_value, s->gr[0x31]); fflush(vga_trcf);
}


/***************************************
 *
 *  basic parameters
 *
 ***************************************/

static void cirrus_get_offsets(VGAState *s1,
                               Uns32 *pline_offset,
                               Uns32 *pstart_addr,
                               Uns32 *pline_compare)
{
    CirrusVGAStateP  s = (CirrusVGAStateP )s1;
    Uns32 start_addr, line_offset, line_compare;
    line_offset = s->cr[0x13]
    | ((s->cr[0x1b] & 0x10) << 4);
    line_offset <<= 3;
    *pline_offset = line_offset;

    start_addr = (s->cr[0x0c] << 8)
    | s->cr[0x0d]
    | ((s->cr[0x1b] & 0x01) << 16)
    | ((s->cr[0x1b] & 0x0c) << 15)
    | ((s->cr[0x1d] & 0x80) << 12);
    *pstart_addr = start_addr;

    line_compare = s->cr[0x18] |
        ((s->cr[0x07] & 0x10) << 4) |
        ((s->cr[0x09] & 0x40) << 3);
    *pline_compare = line_compare;
}

static Uns32 cirrus_get_bpp16_depth(CirrusVGAStateP  s)
{
    Uns32 ret = 16;

    switch (s->cirrus_hidden_dac_data & 0xf) {
    case 0:
    ret = 15;
    break;            /* Sierra HiColor */
    case 1:
    ret = 16;
    break;            /* XGA HiColor */
    default:
#ifdef DEBUG_CIRRUS
    vmiMessage("I", "VGA_INVDAC", "cirrus: invalid DAC value %x in 16bpp\n",
           (s->cirrus_hidden_dac_data & 0xf));
#endif
    ret = 15;        /* XXX */
    break;
    }
    return ret;
}

static Int32 cirrus_get_bpp(VGAState *s1)
{
    CirrusVGAStateP  s = (CirrusVGAStateP )s1;
    Uns32 ret = 8;
    if ((s->sr[0x07] & 0x01) != 0) {
    switch (s->sr[0x07] & CIRRUS_SR7_BPP_MASK) {
    case CIRRUS_SR7_BPP_8:
        ret = 8;
        break;
    case CIRRUS_SR7_BPP_16_DOUBLEVCLK:
        ret = cirrus_get_bpp16_depth(s);
        break;
    case CIRRUS_SR7_BPP_24:
        ret = 24;
        break;
    case CIRRUS_SR7_BPP_16:
        ret = cirrus_get_bpp16_depth(s);
        break;
    case CIRRUS_SR7_BPP_32:
        ret = 32;
        break;
    default:
#ifdef DEBUG_CIRRUS
        vmiMessage("I", "VGA_UBPP", "cirrus: unknown bpp - sr7=%x\n", s->sr[0x7]);
#endif
        ret = 8;
        break;
    }
    } else {
    /* VGA */
    ret = 0;
    }

    return ret;
}

static void cirrus_get_resolution(VGAState *s, Int32 *pwidth, Int32 *pheight)
{
    Int32 width, height;
    width = (s->cr[0x01] + 1) * 8;
    height = s->cr[0x12] |
        ((s->cr[0x07] & 0x02) << 7) |
        ((s->cr[0x07] & 0x40) << 3);
    height = (height + 1);
    /* interlace support */
    if (s->cr[0x1a] & 0x01)
        height = height * 2;
    *pwidth = width;
    *pheight = height;
}

/***************************************
 *
 * bank memory
 *
 ***************************************/

static void cirrus_update_bank_ptr(CirrusVGAStateP  s, Uns32 bank_index)
{
    Uns32 offset;
    Uns32 limit;

    if ((s->gr[0x0b] & 0x01) != 0)    /* dual bank */
    offset = s->gr[0x09 + bank_index];
    else            /* single bank */
    offset = s->gr[0x09];

    if ((s->gr[0x0b] & 0x20) != 0)
    offset <<= 14;
    else
    offset <<= 12;

    if (s->real_vram_size <= offset)
    limit = 0;
    else
    limit = s->real_vram_size - offset;

    if (((s->gr[0x0b] & 0x01) == 0) && (bank_index != 0)) {
    if (limit > 0x8000) {
        offset += 0x8000;
        limit -= 0x8000;
    } else {
        limit = 0;
    }
    }

    if (limit > 0) {
    s->cirrus_bank_base[bank_index] = offset;
    s->cirrus_bank_limit[bank_index] = limit;
    } else {
    s->cirrus_bank_base[bank_index] = 0;
    s->cirrus_bank_limit[bank_index] = 0;
    }
}

/***************************************
 *
 *  I/O access between 0x3c4-0x3c5
 *
 ***************************************/

static int
cirrus_hook_read_sr(CirrusVGAStateP  s, Uns32 reg_index, Uns32 *reg_value)
{
    switch (reg_index) {
    case 0x00:            // Standard VGA
    case 0x01:            // Standard VGA
    case 0x02:            // Standard VGA
    case 0x03:            // Standard VGA
    case 0x04:            // Standard VGA
    return CIRRUS_HOOK_NOT_HANDLED;
    case 0x06:            // Unlock Cirrus extensions
    *reg_value = s->sr[reg_index];
    break;
    case 0x10:
    case 0x30:
    case 0x50:
    case 0x70:            // Graphics Cursor X
    case 0x90:
    case 0xb0:
    case 0xd0:
    case 0xf0:            // Graphics Cursor X
    *reg_value = s->sr[0x10];
    break;
    case 0x11:
    case 0x31:
    case 0x51:
    case 0x71:            // Graphics Cursor Y
    case 0x91:
    case 0xb1:
    case 0xd1:
    case 0xf1:            // Graphics Cursor Y
    *reg_value = s->sr[0x11];
    break;
    case 0x05:            // ???
    case 0x07:            // Extended Sequencer Mode
    case 0x08:            // EEPROM Control
    case 0x09:            // Scratch Register 0
    case 0x0a:            // Scratch Register 1
    case 0x0b:            // VCLK 0
    case 0x0c:            // VCLK 1
    case 0x0d:            // VCLK 2
    case 0x0e:            // VCLK 3
    case 0x0f:            // DRAM Control
    case 0x12:            // Graphics Cursor Attribute
    case 0x13:            // Graphics Cursor Pattern Address
    case 0x14:            // Scratch Register 2
    case 0x15:            // Scratch Register 3
    case 0x16:            // Performance Tuning Register
    case 0x17:            // Configuration Readback and Extended Control
    case 0x18:            // Signature Generator Control
    case 0x19:            // Signal Generator Result
    case 0x1a:            // Signal Generator Result
    case 0x1b:            // VCLK 0 Denominator & Post
    case 0x1c:            // VCLK 1 Denominator & Post
    case 0x1d:            // VCLK 2 Denominator & Post
    case 0x1e:            // VCLK 3 Denominator & Post
    case 0x1f:            // BIOS Write Enable and MCLK select
#ifdef DEBUG_CIRRUS
        vmiMessage("I", PREFIX_READ, "sr_index[%02x\n = 0x%x", reg_index, s->sr[reg_index]);
#endif
        *reg_value = s->sr[reg_index];
    break;
    default:
#ifdef DEBUG_CIRRUS
        vmiMessage("I", PREFIX_DBG, "sr_index %02x = 0xff\n", reg_index);
#endif
        *reg_value = 0xff;
    break;
    }

    return CIRRUS_HOOK_HANDLED;
}

static int cirrus_vga_write_sr(CirrusVGAStateP  s, Uns32 reg_index, Int32 reg_value, Uns32 diag)
{
    TRC(__func__)
    Uns32 newCursor, newValue;
    switch (reg_index) {
    case 0x00:            // Standard VGA
    case 0x01:            // Standard VGA
    case 0x02:            // Standard VGA
    case 0x03:            // Standard VGA
    case 0x04:            // Standard VGA
    return CIRRUS_HOOK_NOT_HANDLED;
    case 0x06:            // Unlock Cirrus extensions
    reg_value &= 0x17;
    if (reg_value != 0x12)
        reg_value = 0x0f;
    s->sr[reg_index] = reg_value;
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "sr[%d] = 0x%02x", reg_index, reg_value);
    break;

    case 0x10:
    case 0x30:
    case 0x50:
    case 0x70:            // Graphics Cursor X
    case 0x90:
    case 0xb0:
    case 0xd0:
    case 0xf0:            // Graphics Cursor X
    s->sr[0x10] = reg_value;
    newCursor = (reg_value << 3) | (reg_index >> 5);
    s->hw_cursor_x = newCursor;
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "hw_cursor_x = 0x%x", newCursor);
    break;

    case 0x11:
    case 0x31:
    case 0x51:
    case 0x71:            // Graphics Cursor Y
    case 0x91:
    case 0xb1:
    case 0xd1:
    case 0xf1:            // Graphics Cursor Y
    s->sr[0x11] = reg_value;
    newCursor = (reg_value << 3) | (reg_index >> 5);
    s->hw_cursor_y = newCursor;
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "hw_cursor_y = 0x%x", newCursor);

    break;

    case 0x07:            // Extended Sequencer Mode
    case 0x08:            // EEPROM Control
    case 0x09:            // Scratch Register 0
    case 0x0a:            // Scratch Register 1
    case 0x0b:            // VCLK 0
    case 0x0c:            // VCLK 1
    case 0x0d:            // VCLK 2
    case 0x0e:            // VCLK 3
    case 0x0f:            // DRAM Control
    case 0x12:            // Graphics Cursor Attribute
    case 0x13:            // Graphics Cursor Pattern Address
    case 0x14:            // Scratch Register 2
    case 0x15:            // Scratch Register 3
    case 0x16:            // Performance Tuning Register
    case 0x18:            // Signature Generator Control
    case 0x19:            // Signature Generator Result
    case 0x1a:            // Signature Generator Result
    case 0x1b:            // VCLK 0 Denominator & Post
    case 0x1c:            // VCLK 1 Denominator & Post
    case 0x1d:            // VCLK 2 Denominator & Post
    case 0x1e:            // VCLK 3 Denominator & Post
    case 0x1f:            // BIOS Write Enable and MCLK select
    s->sr[reg_index] = reg_value;
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "sr[%d] = 0x%x", reg_index, reg_value);
    break;
    case 0x17:            // Configuration Readback and Extended Control
    newValue = (s->sr[reg_index] & 0x38) | (reg_value & 0xc7);
    s->sr[reg_index] =newValue ;
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "sr[%d] = 0x%x (extended)", reg_index, newValue);
    cirrus_update_memory_access(s);
    break;

    default:
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "(no action)");
    break;
    }

    return CIRRUS_HOOK_HANDLED;
}

/***************************************
 *
 *  I/O access at 0x3c6
 *
 ***************************************/

static void cirrus_read_hidden_dac(CirrusVGAStateP  s, Uns32 *reg_value)
{
    *reg_value = 0xff;
    if (++s->cirrus_hidden_dac_lockindex == 5) {
        *reg_value = s->cirrus_hidden_dac_data;
        s->cirrus_hidden_dac_lockindex = 0;
    }
}

static void cirrus_write_hidden_dac(CirrusVGAStateP  s, Uns32 reg_value, Uns32 diag)
{
    if (s->cirrus_hidden_dac_lockindex == 4) {
        s->cirrus_hidden_dac_data = reg_value;
        if(diag >= 3) vmiMessage("I", PREFIX_DBG, "write hidden DAC, value %02x\n", reg_value);
    }
    s->cirrus_hidden_dac_lockindex = 0;
}

/***************************************
 *
 *  I/O access at 0x3c9
 *
 ***************************************/

static Int32 cirrus_hook_read_palette(CirrusVGAStateP  s, Uns32 *reg_value)
{
    if (!(s->sr[0x12] & CIRRUS_CURSOR_HIDDENPEL))
    return CIRRUS_HOOK_NOT_HANDLED;
    *reg_value =
        s->cirrus_hidden_palette[(s->dac_read_index & 0x0f) * 3 +
                                 s->dac_sub_index];
    if (++s->dac_sub_index == 3) {
        s->dac_sub_index = 0;
        s->dac_read_index++;
    }
    return CIRRUS_HOOK_HANDLED;
}

static Int32 cirrus_hook_write_palette(CirrusVGAStateP  s, Uns32 reg_value, Uns32 diag)
{
    if (!(s->sr[0x12] & CIRRUS_CURSOR_HIDDENPEL))
    return CIRRUS_HOOK_NOT_HANDLED;
    if(diag >= 3)
        vmiMessage("I", PREFIX_WRITE, "dac_cache[%d] <= 0x%02x\n", s->dac_sub_index, reg_value);
    s->dac_cache[s->dac_sub_index] = reg_value;
    if (++s->dac_sub_index == 3) {
        memcpy(&s->cirrus_hidden_palette[(s->dac_write_index & 0x0f) * 3],
               s->dac_cache, 3);
        /* XXX update cursor */
        s->dac_sub_index = 0;
        s->dac_write_index++;
    }
    return CIRRUS_HOOK_HANDLED;
}

/***************************************
 *
 *  I/O access between 0x3ce-0x3cf
 *
 ***************************************/

static Int32 cirrus_vga_read_gr(CirrusVGAStateP  s, Uns32 reg_index, Uns32 *reg_value, Uns32 diag)
{
//    fprintf(vga_trcf, "cirrus_vga.c:%s index=0x%02x\n",
//            __func__, reg_index); fflush(vga_trcf);
    switch (reg_index) {
    case 0x00: // Standard VGA, BGCOLOR 0x000000ff
        *reg_value = s->cirrus_shadow_gr0;
        if(diag >= 3) {
          vmiMessage("I", PREFIX_READ, "shadow_gr0 => %02x\n", s->cirrus_shadow_gr0);
        }
        return CIRRUS_HOOK_HANDLED;
    case 0x01: // Standard VGA, FGCOLOR 0x000000ff
        if(diag >= 3) {
          vmiMessage("I", PREFIX_READ, "shadow_gr1 => %02x\n", s->cirrus_shadow_gr1);
        }
        *reg_value = s->cirrus_shadow_gr1;
        return CIRRUS_HOOK_HANDLED;
    case 0x02:            // Standard VGA
    case 0x03:            // Standard VGA
    case 0x04:            // Standard VGA
    case 0x06:            // Standard VGA
    case 0x07:            // Standard VGA
    case 0x08:            // Standard VGA
        *reg_value = s->gr[s->gr_index];
        if(diag >= 3) {
            vmiMessage("I", PREFIX_READ, "s->gr[%d] => %02x\n", s->gr_index, *reg_value);
        }
        return CIRRUS_HOOK_HANDLED;
    case 0x05:            // Standard VGA, Cirrus extended mode
    default:
    break;
    }

    if (reg_index < 0x3a) {
//        fprintf(vga_trcf, "cirrus_vga.c:%s index=0x%02x val=0x%02x\n",
//                __func__, reg_index, s->gr[reg_index]); fflush(vga_trcf);
        *reg_value = s->gr[reg_index];
    } else {
        *reg_value = 0xff;
    }
    if(diag >= 3) {
        vmiMessage("I", PREFIX_READ, "gr[%d] => %02x\n", reg_index, *reg_value);
    }
    return CIRRUS_HOOK_HANDLED;
}

static int
cirrus_vga_write_gr(CirrusVGAStateP  s, Uns32 reg_index, Uns32 reg_value, Uns32 diag)
{
    TRC(__func__)
//    fprintf(vga_trcf, "cirrus_vga.c:%s index=0x%02x value=0x%02x\n",
//            __func__, reg_index, reg_value); fflush(vga_trcf);
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= %02x\n", reg_index, reg_value);
    switch (reg_index) {
    case 0x00:            // Standard VGA, BGCOLOR 0x000000ff
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "shadow_gr0 <= 0x%02x\n", reg_value);
    s->cirrus_shadow_gr0 = reg_value;
    return CIRRUS_HOOK_NOT_HANDLED;
    case 0x01:            // Standard VGA, FGCOLOR 0x000000ff
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "shadow_gr1 <= 0x%02x\n", reg_value);
    s->cirrus_shadow_gr1 = reg_value;
    return CIRRUS_HOOK_NOT_HANDLED;
    case 0x02:            // Standard VGA
    case 0x03:            // Standard VGA
    case 0x04:            // Standard VGA
    case 0x06:            // Standard VGA
    case 0x07:            // Standard VGA
    case 0x08:            // Standard VGA
    return CIRRUS_HOOK_NOT_HANDLED;
    case 0x05:            // Standard VGA, Cirrus extended mode
    s->gr[reg_index] = reg_value & 0x7f;
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x\n", reg_index, reg_value);
    cirrus_update_memory_access(s);
    break;
    case 0x09:            // bank offset #0
    case 0x0A:            // bank offset #1
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x and bank ptrs\n", reg_index, reg_value);
    s->gr[reg_index] = reg_value;
    cirrus_update_bank_ptr(s, 0);
    cirrus_update_bank_ptr(s, 1);
        break;
    case 0x0B:
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x and bank ptrs and mem access\n", reg_index, reg_value);
    s->gr[reg_index] = reg_value;
    cirrus_update_bank_ptr(s, 0);
    cirrus_update_bank_ptr(s, 1);
    cirrus_update_memory_access(s);
    break;
    case 0x10:            // BGCOLOR 0x0000ff00
    case 0x11:            // FGCOLOR 0x0000ff00
    case 0x12:            // BGCOLOR 0x00ff0000
    case 0x13:            // FGCOLOR 0x00ff0000
    case 0x14:            // BGCOLOR 0xff000000
    case 0x15:            // FGCOLOR 0xff000000
    case 0x20:            // BLT WIDTH 0x0000ff
    case 0x22:            // BLT HEIGHT 0x0000ff
    case 0x24:            // BLT DEST PITCH 0x0000ff
    case 0x26:            // BLT SRC PITCH 0x0000ff
    case 0x28:            // BLT DEST ADDR 0x0000ff
    case 0x29:            // BLT DEST ADDR 0x00ff00
    case 0x2c:            // BLT SRC ADDR 0x0000ff
    case 0x2d:            // BLT SRC ADDR 0x00ff00
    case 0x2f:                  // BLT WRITEMASK
    case 0x30:            // BLT MODE
    case 0x32:            // RASTER OP
    case 0x33:            // BLT MODEEXT
    case 0x34:            // BLT TRANSPARENT COLOR 0x00ff
    case 0x35:            // BLT TRANSPARENT COLOR 0xff00
    case 0x38:            // BLT TRANSPARENT COLOR MASK 0x00ff
    case 0x39:            // BLT TRANSPARENT COLOR MASK 0xff00
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x\n", reg_index, reg_value);
    s->gr[reg_index] = reg_value;
    break;
    case 0x21:            // BLT WIDTH 0x001f00
    case 0x23:            // BLT HEIGHT 0x001f00
    case 0x25:            // BLT DEST PITCH 0x001f00
    case 0x27:            // BLT SRC PITCH 0x001f00
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x\n", reg_index, reg_value & 0x1f);
    s->gr[reg_index] = reg_value & 0x1f;
    break;
    case 0x2a:            // BLT DEST ADDR 0x3f0000
    if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x\n", reg_index, reg_value & 0x3f);
    s->gr[reg_index] = reg_value & 0x3f;
        /* if auto start mode, starts bit blt now */
        if (s->gr[0x31] & CIRRUS_BLT_AUTOSTART) {
            cirrus_bitblt_start(s);
        }
    break;
    case 0x2e:            // BLT SRC ADDR 0x3f0000
    s->gr[reg_index] = reg_value & 0x3f;
    break;
    case 0x31:            // BLT STATUS/START
    cirrus_write_bitblt(s, reg_value);
    break;
    default:
    break;
    }

    return CIRRUS_HOOK_HANDLED;
}

/***************************************
 *
 *  I/O access between 0x3d4-0x3d5
 *
 ***************************************/

static int cirrus_vga_read_cr(CirrusVGAStateP  s, Uns32 reg_index, Uns32 *reg_value, Uns32 diag)
{
//    fprintf(vga_trcf, "cirrus_vga.c:%s reg_index=0x%02x\n",
//            __func__, reg_index); fflush(vga_trcf);
    switch (reg_index) {
    case 0x00:            // Standard VGA
    case 0x01:            // Standard VGA
    case 0x02:            // Standard VGA
    case 0x03:            // Standard VGA
    case 0x04:            // Standard VGA
    case 0x05:            // Standard VGA
    case 0x06:            // Standard VGA
    case 0x07:            // Standard VGA
    case 0x08:            // Standard VGA
    case 0x09:            // Standard VGA
    case 0x0a:            // Standard VGA
    case 0x0b:            // Standard VGA
    case 0x0c:            // Standard VGA
    case 0x0d:            // Standard VGA
    case 0x0e:            // Standard VGA
    case 0x0f:            // Standard VGA
    case 0x10:            // Standard VGA
    case 0x11:            // Standard VGA
    case 0x12:            // Standard VGA
    case 0x13:            // Standard VGA
    case 0x14:            // Standard VGA
    case 0x15:            // Standard VGA
    case 0x16:            // Standard VGA
    case 0x17:            // Standard VGA
    case 0x18:            // Standard VGA
        return CIRRUS_HOOK_NOT_HANDLED;

    case 0x24:            // Attribute Controller Toggle Readback (R)
        *reg_value = (s->ar_flip_flop << 7);
        if (diag >= 3)
            vmiMessage("I", PREFIX_READ, "ar_flip_flop => 0x%x", *reg_value);
    break;

    case 0x19:            // Interlace End
    case 0x1a:            // Miscellaneous Control
    case 0x1b:            // Extended Display Control
    case 0x1c:            // Sync Adjust and Genlock
    case 0x1d:            // Overlay Extended Control
    case 0x22:            // Graphics Data Latches Readback (R)
    case 0x25:            // Part Status
    case 0x27:            // Part ID (R)
        *reg_value = s->cr[reg_index];
        if (diag >= 3)
            vmiMessage("I", PREFIX_READ, "cr[%d] => 0x%x", reg_index, *reg_value);
    break;

    case 0x26:            // Attribute Controller Index Readback (R)
        *reg_value = s->ar_index & 0x3f;
        if (diag >= 3)
            vmiMessage("I", PREFIX_READ, "cr[%d] => 0x%x", s->ar_index & 0x3f, *reg_value);
    break;

    default:
        *reg_value = 0xff;
        if (diag >= 3)
            vmiMessage("I", PREFIX_READ, "read_cr => 0xff");
    break;
    }

    return CIRRUS_HOOK_HANDLED;
}

static int cirrus_hook_write_cr(CirrusVGAStateP  s, Uns32 reg_index, Uns32 reg_value, Uns32 diag)
{
    switch (reg_index) {
    case 0x00:            // Standard VGA
    case 0x01:            // Standard VGA
    case 0x02:            // Standard VGA
    case 0x03:            // Standard VGA
    case 0x04:            // Standard VGA
    case 0x05:            // Standard VGA
    case 0x06:            // Standard VGA
    case 0x07:            // Standard VGA
    case 0x08:            // Standard VGA
    case 0x09:            // Standard VGA
    case 0x0a:            // Standard VGA
    case 0x0b:            // Standard VGA
    case 0x0c:            // Standard VGA
    case 0x0d:            // Standard VGA
    case 0x0e:            // Standard VGA
    case 0x0f:            // Standard VGA
    case 0x10:            // Standard VGA
    case 0x11:            // Standard VGA
    case 0x12:            // Standard VGA
    case 0x13:            // Standard VGA
    case 0x14:            // Standard VGA
    case 0x15:            // Standard VGA
    case 0x16:            // Standard VGA
    case 0x17:            // Standard VGA
    case 0x18:            // Standard VGA
    return CIRRUS_HOOK_NOT_HANDLED;
    case 0x19:            // Interlace End
    case 0x1a:            // Miscellaneous Control
    case 0x1b:            // Extended Display Control
    case 0x1c:            // Sync Adjust and Genlock
    case 0x1d:            // Overlay Extended Control
        s->cr[reg_index] = reg_value;
        if(diag >= 3)
            vmiMessage("I", PREFIX_WRITE, "cr[%d] <= %02x\n",reg_index, reg_value);
    break;
    case 0x22:            // Graphics Data Latches Readback (R)
    case 0x24:            // Attribute Controller Toggle Readback (R)
    case 0x26:            // Attribute Controller Index Readback (R)
    case 0x27:            // Part ID (R)
    break;
    case 0x25:            // Part Status
    default:
    break;
    }
    return CIRRUS_HOOK_HANDLED;
}

/***************************************
 *
 *  memory-mapped I/O (bitblt)
 *
 ***************************************/

static Uns8 cirrus_mmio_blt_read(CirrusVGAStateP  s, Uns32 address, Uns32 diag)
{
    Uns32 value = 0xff;

    switch (address) {
    case (CIRRUS_MMIO_BLTBGCOLOR + 0):
    cirrus_vga_read_gr(s, 0x00, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTBGCOLOR + 1):
    cirrus_vga_read_gr(s, 0x10, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTBGCOLOR + 2):
    cirrus_vga_read_gr(s, 0x12, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTBGCOLOR + 3):
    cirrus_vga_read_gr(s, 0x14, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 0):
    cirrus_vga_read_gr(s, 0x01, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 1):
    cirrus_vga_read_gr(s, 0x11, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 2):
    cirrus_vga_read_gr(s, 0x13, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 3):
    cirrus_vga_read_gr(s, 0x15, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTWIDTH + 0):
    cirrus_vga_read_gr(s, 0x20, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTWIDTH + 1):
    cirrus_vga_read_gr(s, 0x21, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTHEIGHT + 0):
    cirrus_vga_read_gr(s, 0x22, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTHEIGHT + 1):
    cirrus_vga_read_gr(s, 0x23, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTPITCH + 0):
    cirrus_vga_read_gr(s, 0x24, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTPITCH + 1):
    cirrus_vga_read_gr(s, 0x25, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCPITCH + 0):
    cirrus_vga_read_gr(s, 0x26, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCPITCH + 1):
    cirrus_vga_read_gr(s, 0x27, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 0):
    cirrus_vga_read_gr(s, 0x28, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 1):
    cirrus_vga_read_gr(s, 0x29, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 2):
    cirrus_vga_read_gr(s, 0x2a, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCADDR + 0):
    cirrus_vga_read_gr(s, 0x2c, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCADDR + 1):
    cirrus_vga_read_gr(s, 0x2d, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCADDR + 2):
    cirrus_vga_read_gr(s, 0x2e, &value, diag);
    break;
    case CIRRUS_MMIO_BLTWRITEMASK:
    cirrus_vga_read_gr(s, 0x2f, &value, diag);
    break;
    case CIRRUS_MMIO_BLTMODE:
    cirrus_vga_read_gr(s, 0x30, &value, diag);
    break;
    case CIRRUS_MMIO_BLTROP:
    cirrus_vga_read_gr(s, 0x32, &value, diag);
    break;
    case CIRRUS_MMIO_BLTMODEEXT:
    cirrus_vga_read_gr(s, 0x33, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLOR + 0):
    cirrus_vga_read_gr(s, 0x34, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLOR + 1):
    cirrus_vga_read_gr(s, 0x35, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLORMASK + 0):
    cirrus_vga_read_gr(s, 0x38, &value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLORMASK + 1):
    cirrus_vga_read_gr(s, 0x39, &value, diag);
    break;
    case CIRRUS_MMIO_BLTSTATUS:
    cirrus_vga_read_gr(s, 0x31, &value, diag);
    break;
    default:
    if (diag >= 3)
        vmiMessage("I", PREFIX_DBG, "mmio read 0x%x\n", value);
    break;
    }
//    fprintf(vga_trcf, "cirrus_vga.c:%s addr=0x%08x val=0x%02x\n",
//            __func__, address, value); fflush(vga_trcf);
    return (Uns8) value;
}

static void cirrus_mmio_blt_write(CirrusVGAStateP  s, Uns32 address,
                  Uns8 value, Uns32 diag)
{
//    fprintf(vga_trcf, "cirrus_vga.c:%s addr=0x%08x val=0x%02x\n",
//            __func__, address, value); fflush(vga_trcf);
    switch (address) {
    case (CIRRUS_MMIO_BLTBGCOLOR + 0):
    cirrus_vga_write_gr(s, 0x00, value, diag);
    break;
    case (CIRRUS_MMIO_BLTBGCOLOR + 1):
    cirrus_vga_write_gr(s, 0x10, value, diag);
    break;
    case (CIRRUS_MMIO_BLTBGCOLOR + 2):
    cirrus_vga_write_gr(s, 0x12, value, diag);
    break;
    case (CIRRUS_MMIO_BLTBGCOLOR + 3):
    cirrus_vga_write_gr(s, 0x14, value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 0):
    cirrus_vga_write_gr(s, 0x01, value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 1):
    cirrus_vga_write_gr(s, 0x11, value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 2):
    cirrus_vga_write_gr(s, 0x13, value, diag);
    break;
    case (CIRRUS_MMIO_BLTFGCOLOR + 3):
    cirrus_vga_write_gr(s, 0x15, value, diag);
    break;
    case (CIRRUS_MMIO_BLTWIDTH + 0):
    cirrus_vga_write_gr(s, 0x20, value, diag);
    break;
    case (CIRRUS_MMIO_BLTWIDTH + 1):
    cirrus_vga_write_gr(s, 0x21, value, diag);
    break;
    case (CIRRUS_MMIO_BLTHEIGHT + 0):
    cirrus_vga_write_gr(s, 0x22, value, diag);
    break;
    case (CIRRUS_MMIO_BLTHEIGHT + 1):
    cirrus_vga_write_gr(s, 0x23, value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTPITCH + 0):
    cirrus_vga_write_gr(s, 0x24, value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTPITCH + 1):
    cirrus_vga_write_gr(s, 0x25, value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCPITCH + 0):
    cirrus_vga_write_gr(s, 0x26, value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCPITCH + 1):
    cirrus_vga_write_gr(s, 0x27, value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 0):
    cirrus_vga_write_gr(s, 0x28, value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 1):
    cirrus_vga_write_gr(s, 0x29, value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 2):
    cirrus_vga_write_gr(s, 0x2a, value, diag);
    break;
    case (CIRRUS_MMIO_BLTDESTADDR + 3):
    /* ignored */
    break;
    case (CIRRUS_MMIO_BLTSRCADDR + 0):
    cirrus_vga_write_gr(s, 0x2c, value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCADDR + 1):
    cirrus_vga_write_gr(s, 0x2d, value, diag);
    break;
    case (CIRRUS_MMIO_BLTSRCADDR + 2):
    cirrus_vga_write_gr(s, 0x2e, value, diag);
    break;
    case CIRRUS_MMIO_BLTWRITEMASK:
    cirrus_vga_write_gr(s, 0x2f, value, diag);
    break;
    case CIRRUS_MMIO_BLTMODE:
    cirrus_vga_write_gr(s, 0x30, value, diag);
    break;
    case CIRRUS_MMIO_BLTROP:
    cirrus_vga_write_gr(s, 0x32, value, diag);
    break;
    case CIRRUS_MMIO_BLTMODEEXT:
    cirrus_vga_write_gr(s, 0x33, value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLOR + 0):
    cirrus_vga_write_gr(s, 0x34, value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLOR + 1):
    cirrus_vga_write_gr(s, 0x35, value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLORMASK + 0):
    cirrus_vga_write_gr(s, 0x38, value, diag);
    break;
    case (CIRRUS_MMIO_BLTTRANSPARENTCOLORMASK + 1):
    cirrus_vga_write_gr(s, 0x39, value, diag);
    break;
    case CIRRUS_MMIO_BLTSTATUS:
    cirrus_vga_write_gr(s, 0x31, value, diag);
    break;
    default:
#ifdef DEBUG_CIRRUS
    vmiMessage("I", PREFIX_DBG, "cirrus: mmio write - addr 0x%04x val 0x%02x (ignored)\n",
           address, value);
#endif
    break;
    }
}

/***************************************
 *
 *  write mode 4/5
 *
 * assume TARGET_PAGE_SIZE >= 16
 *
 ***************************************/

static void cirrus_mem_writeb_mode4and5_8bpp(CirrusVGAStateP  s,
                         Uns32 mode,
                         Uns32 offset,
                         Uns32 mem_value)
{
    Int32 x;
    Uns32 val = mem_value;
    Uns8 *dst;

    dst = s->vram_ptr + offset;
    for (x = 0; x < 8; x++) {
    if (val & 0x80) {
        *dst = s->cirrus_shadow_gr1;
    } else if (mode == 5) {
        *dst = s->cirrus_shadow_gr0;
    }
    val <<= 1;
    dst++;
    }
}

static void cirrus_mem_writeb_mode4and5_16bpp(CirrusVGAStateP  s,
                          Uns32 mode,
                          Uns32 offset,
                          Uns32 mem_value)
{
    Int32 x;
    Uns32 val = mem_value;
    Uns8 *dst;

    dst = s->vram_ptr + offset;
    for (x = 0; x < 8; x++) {
    if (val & 0x80) {
        *dst = s->cirrus_shadow_gr1;
        *(dst + 1) = s->gr[0x11];
    } else if (mode == 5) {
        *dst = s->cirrus_shadow_gr0;
        *(dst + 1) = s->gr[0x10];
    }
    val <<= 1;
    dst += 2;
    }
}

/***************************************
 *
 *  memory access between 0xa0000-0xbffff
 *
 ***************************************/

static Uns32 cirrus_vga_mem_readb(void *opaque, Addr addr)
{
    CirrusVGAStateP s = opaque;
    Uns32 bank_index;
    Uns32 bank_offset;
    Uns32 val;

    if ((s->sr[0x07] & 0x01) == 0) {
    return vga_mem_readb(s, addr);
    }

    addr &= 0x1ffff;

    if (addr < 0x10000) {
    /* XXX handle bitblt */
    /* video memory */
    bank_index = addr >> 15;
    bank_offset = addr & 0x7fff;
    if (bank_offset < s->cirrus_bank_limit[bank_index]) {
        bank_offset += s->cirrus_bank_base[bank_index];
        if ((s->gr[0x0B] & 0x14) == 0x14) {
        bank_offset <<= 4;
        } else if (s->gr[0x0B] & 0x02) {
        bank_offset <<= 3;
        }
        bank_offset &= s->cirrus_addr_mask;
        val = *(s->vram_ptr + bank_offset);
    } else
        val = 0xff;
    } else if (addr >= 0x18000 && addr < 0x18100) {
    /* memory-mapped I/O */
    val = 0xff;
    if ((s->sr[0x17] & 0x44) == 0x04) {
        val = cirrus_mmio_blt_read(s, addr & 0xff, 0);
    }
    } else {
    val = 0xff;
#ifdef DEBUG_CIRRUS
    vmiMessage("I", PREFIX_DBG, "mem_readb %06llx\n", addr);
#endif
    }
    vmiMessage("I", PREFIX_DBG, "mem_readb(0x" FMT_64x "); // %x\n", addr, val);
    return val;
}

Uns32 cirrus_vga_mem_readw(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_vga_mem_readb(opaque, addr) << 8;
    v |= cirrus_vga_mem_readb(opaque, addr + 1);
#else
    v = cirrus_vga_mem_readb(opaque, addr);
    v |= cirrus_vga_mem_readb(opaque, addr + 1) << 8;
#endif
    return v;
}

Uns32 cirrus_vga_mem_readl(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_vga_mem_readb(opaque, addr) << 24;
    v |= cirrus_vga_mem_readb(opaque, addr + 1) << 16;
    v |= cirrus_vga_mem_readb(opaque, addr + 2) << 8;
    v |= cirrus_vga_mem_readb(opaque, addr + 3);
#else
    v = cirrus_vga_mem_readb(opaque, addr);
    v |= cirrus_vga_mem_readb(opaque, addr + 1) << 8;
    v |= cirrus_vga_mem_readb(opaque, addr + 2) << 16;
    v |= cirrus_vga_mem_readb(opaque, addr + 3) << 24;
#endif
    return v;
}

void cirrus_vga_mem_writeb(void *opaque, Addr addr,
        Uns32 mem_value)
{
    TRC(__func__)
    CirrusVGAStateP s = opaque;
    Uns32 bank_index;
    Uns32 bank_offset;
    Uns32 mode;

//    vmiMessage("I", PREFIX_DBG, "cirrus_vga_mem_writeb(ref, 0x" FMT_64x ", 0x%x);\n", addr, mem_value);

    if ((s->sr[0x07] & 0x01) == 0) {
        vga_mem_writeb(s, addr, mem_value);
        return;
    }

    static int wrmode = 0;
    addr &= 0x1ffff;

    if (addr < 0x10000) {
        if (s->cirrus_srcptr != s->cirrus_srcptr_end) {
            if (wrmode != 1) {
                wrmode = 1;
                vmiPrintf ("Writing to bitblt\n");
            }
            /* bitblt */
            *s->cirrus_srcptr++ = (Uns8) mem_value;
            if (s->cirrus_srcptr >= s->cirrus_srcptr_end) {
                cirrus_bitblt_cputovideo_next(s);
            }
        } else {
            if (wrmode != 2) {
                wrmode = 2;
                vmiPrintf ("Writing to video memory\n");
            }
            /* video memory */
            bank_index = addr >> 15;
            bank_offset = addr & 0x7fff;
            if (bank_offset < s->cirrus_bank_limit[bank_index]) {
                bank_offset += s->cirrus_bank_base[bank_index];
                if ((s->gr[0x0B] & 0x14) == 0x14) {
                    bank_offset <<= 4;
                } else if (s->gr[0x0B] & 0x02) {
                    bank_offset <<= 3;
                }
                bank_offset &= s->cirrus_addr_mask;
                mode = s->gr[0x05] & 0x7;
                if (mode < 4 || mode > 5 || ((s->gr[0x0B] & 0x4) == 0)) {
                    *(s->vram_ptr + bank_offset) = mem_value;
                    //cpu_physical_memory_set_dirty(s->vram_offset +bank_offset);
                } else {
                    if ((s->gr[0x0B] & 0x14) != 0x14) {
                    cirrus_mem_writeb_mode4and5_8bpp(s, mode,
                                     bank_offset,
                                     mem_value);
                    } else {
                    cirrus_mem_writeb_mode4and5_16bpp(s, mode,
                                      bank_offset,
                                      mem_value);
                    }
                }
            }
        }
    } else if (addr >= 0x18000 && addr < 0x18100) {
        if (wrmode != 3) {
            wrmode = 3;
            vmiPrintf ("Writing to memory-mapped I/O\n");
        }
        /* memory-mapped I/O */
        if ((s->sr[0x17] & 0x44) == 0x04) {
            cirrus_mmio_blt_write(s, addr & 0xff, mem_value, 0);
        } else {
            vmiMessage("I", __func__, "memory-mapped I/O " FMT_6408x" value %02x\n", addr, mem_value);
        }
    } else {
        vmiMessage("I", __func__, "???? " FMT_6408x " value %02x\n", addr, mem_value);
    }
}

void cirrus_vga_mem_writew(void *opaque, Addr addr, Uns32 val)
{
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_vga_mem_writeb(opaque, addr, (val >> 8) & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 1, val & 0xff);
#else
    cirrus_vga_mem_writeb(opaque, addr, val & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 1, (val >> 8) & 0xff);
#endif
}

void cirrus_vga_mem_writel(void *opaque, Addr addr, Uns32 val)
{
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_vga_mem_writeb(opaque, addr, (val >> 24) & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 1, (val >> 16) & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 2, (val >> 8) & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 3, val & 0xff);
#else
    cirrus_vga_mem_writeb(opaque, addr, val & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 1, (val >> 8) & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 2, (val >> 16) & 0xff);
    cirrus_vga_mem_writeb(opaque, addr + 3, (val >> 24) & 0xff);
#endif
}

/***************************************
 *
 *  hardware cursor
 *
 ***************************************/

static inline void invalidate_cursor1(CirrusVGAStateP s)
{
    if (s->last_hw_cursor_size) {
        vga_invalidate_scanlines((VGAState *)s,
                                 s->last_hw_cursor_y + s->last_hw_cursor_y_start,
                                 s->last_hw_cursor_y + s->last_hw_cursor_y_end);
    }
}

static inline void cirrus_cursor_compute_yrange(CirrusVGAStateP s)
{
    const Uns8 *src;
    Uns32 content;
    Int32 y, y_min, y_max;

    src = s->vram_ptr + s->real_vram_size - 16 * 1024;
    if (s->sr[0x12] & CIRRUS_CURSOR_LARGE) {
        src += (s->sr[0x13] & 0x3c) * 256;
        y_min = 64;
        y_max = -1;
        for(y = 0; y < 64; y++) {
            content = ((Uns32 *)src)[0] |
                ((Uns32 *)src)[1] |
                ((Uns32 *)src)[2] |
                ((Uns32 *)src)[3];
            if (content) {
                if (y < y_min)
                    y_min = y;
                if (y > y_max)
                    y_max = y;
            }
            src += 16;
        }
    } else {
        src += (s->sr[0x13] & 0x3f) * 256;
        y_min = 32;
        y_max = -1;
        for(y = 0; y < 32; y++) {
            content = ((Uns32 *)src)[0] |
                ((Uns32 *)(src + 128))[0];
            if (content) {
                if (y < y_min)
                    y_min = y;
                if (y > y_max)
                    y_max = y;
            }
            src += 4;
        }
    }
    if (y_min > y_max) {
        s->last_hw_cursor_y_start = 0;
        s->last_hw_cursor_y_end = 0;
    } else {
        s->last_hw_cursor_y_start = y_min;
        s->last_hw_cursor_y_end = y_max + 1;
    }
}

/* NOTE: we do not currently handle the cursor bitmap change, so we
   update the cursor only if it moves. */
static void cirrus_cursor_invalidate(VGAState *s1)
{
    CirrusVGAStateP s = (CirrusVGAStateP )s1;
    Int32 size;
    //vmiMessage("I", PREFIX_DBG, "cirrus_cursor_invalidate\n");
    if (!s->sr[0x12] & CIRRUS_CURSOR_SHOW) {
        size = 0;
    } else {
        if (s->sr[0x12] & CIRRUS_CURSOR_LARGE)
            size = 64;
        else
            size = 32;
    }
    /* invalidate last cursor and new cursor if any change */
    if (s->last_hw_cursor_size != size ||
        s->last_hw_cursor_x != s->hw_cursor_x ||
        s->last_hw_cursor_y != s->hw_cursor_y) {

        invalidate_cursor1(s);

        s->last_hw_cursor_size = size;
        s->last_hw_cursor_x = s->hw_cursor_x;
        s->last_hw_cursor_y = s->hw_cursor_y;
        /* compute the real cursor min and max y */
        cirrus_cursor_compute_yrange(s);
        invalidate_cursor1(s);
    }
}

static void cirrus_cursor_draw_line(VGAState *s1, Uns8 *d1, Int32 scr_y)
{
    CirrusVGAStateP s = (CirrusVGAStateP )s1;
    Int32 w, h, bpp, x1, x2, poffset __attribute__((unused));
    Uns32 color0 __attribute__((unused)), color1 __attribute__((unused));
    const Uns8 *palette, *src;
    Uns32 content;

    if (!(s->sr[0x12] & CIRRUS_CURSOR_SHOW))
        return;
    /* fast test to see if the cursor intersects with the scan line */
    if (s->sr[0x12] & CIRRUS_CURSOR_LARGE) {
        h = 64;
    } else {
        h = 32;
    }
    if (scr_y < s->hw_cursor_y ||
        scr_y >= (s->hw_cursor_y + h))
        return;

    src = s->vram_ptr + s->real_vram_size - 16 * 1024;
    if (s->sr[0x12] & CIRRUS_CURSOR_LARGE) {
        src += (s->sr[0x13] & 0x3c) * 256;
        src += (scr_y - s->hw_cursor_y) * 16;
        poffset = 8;
        content = ((Uns32 *)src)[0] |
            ((Uns32 *)src)[1] |
            ((Uns32 *)src)[2] |
            ((Uns32 *)src)[3];
    } else {
        src += (s->sr[0x13] & 0x3f) * 256;
        src += (scr_y - s->hw_cursor_y) * 4;
        poffset = 128;
        content = ((Uns32 *)src)[0] |
            ((Uns32 *)(src + 128))[0];
    }
    /* if nothing to draw, no need to continue */
    if (!content)
        return;
    w = h;

    x1 = s->hw_cursor_x;
    if (x1 >= s->last_scr_width)
        return;
    x2 = s->hw_cursor_x + w;
    if (x2 > s->last_scr_width)
        x2 = s->last_scr_width;
    w = x2 - x1;
    palette = s->cirrus_hidden_palette;
    color0 = s->rgb_to_pixel(c6_to_8(palette[0x0 * 3]),
                             c6_to_8(palette[0x0 * 3 + 1]),
                             c6_to_8(palette[0x0 * 3 + 2]));
    color1 = s->rgb_to_pixel(c6_to_8(palette[0xf * 3]),
                             c6_to_8(palette[0xf * 3 + 1]),
                             c6_to_8(palette[0xf * 3 + 2]));
    bpp = ((sdl_get_depth(s->ds) + 7) >> 3);
    d1 += x1 * bpp;
    vmiMessage("F", "ABT", "Trying to draw a cursor line");
//     switch(s->ds->depth) {
//     default:
//         break;
//     case 8:
//         vga_draw_cursor_line_8(d1, src, poffset, w, color0, color1, 0xff);
//         break;
//     case 15:
//         vga_draw_cursor_line_16(d1, src, poffset, w, color0, color1, 0x7fff);
//         break;
//     case 16:
//         vga_draw_cursor_line_16(d1, src, poffset, w, color0, color1, 0xffff);
//         break;
//     case 32:
//         vga_draw_cursor_line_32(d1, src, poffset, w, color0, color1, 0xffffff);
//         break;
//     }
}

/***************************************
 *
 *  LFB memory access
 *
 ***************************************/

Uns32 cirrus_linear_readb(void *opaque, Addr addr)
{
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;
    Uns32 ret;

    addr &= s->cirrus_addr_mask;

    if (((s->sr[0x17] & 0x44) == 0x44) &&
        ((addr & s->linear_mmio_mask) == s->linear_mmio_mask)) {
        /* memory-mapped I/O */
        ret = cirrus_mmio_blt_read(s, addr & 0xff, 0);
    } else if (0) {
        /* XXX handle bitblt */
        ret = 0xff;
    } else {
        /* video memory */
        if ((s->gr[0x0B] & 0x14) == 0x14) {
            addr <<= 4;
        } else if (s->gr[0x0B] & 0x02) {
            addr <<= 3;
        }
        addr &= s->cirrus_addr_mask;
        ret = *(s->vram_ptr + addr);
    }
//    vmiMessage("I", PREFIX_DBG, "cirrus_linear_readb(0x" FMT_64x ");  // 0x%x\n", addr, ret);
    return ret;
}

Uns32 cirrus_linear_readw(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_linear_readb(opaque, addr) << 8;
    v |= cirrus_linear_readb(opaque, addr + 1);
#else
    v = cirrus_linear_readb(opaque, addr);
    v |= cirrus_linear_readb(opaque, addr + 1) << 8;
#endif
    return v;
}

Uns32 cirrus_linear_readl(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_linear_readb(opaque, addr) << 24;
    v |= cirrus_linear_readb(opaque, addr + 1) << 16;
    v |= cirrus_linear_readb(opaque, addr + 2) << 8;
    v |= cirrus_linear_readb(opaque, addr + 3);
#else
    v = cirrus_linear_readb(opaque, addr);
    v |= cirrus_linear_readb(opaque, addr + 1) << 8;
    v |= cirrus_linear_readb(opaque, addr + 2) << 16;
    v |= cirrus_linear_readb(opaque, addr + 3) << 24;
#endif
    return v;
}

void cirrus_linear_writeb(void *opaque, Addr addr,
                 Uns32 val)
{
    TRC(__func__)
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;
    Uns32 mode;

    addr &= s->cirrus_addr_mask;

    if (((s->sr[0x17] & 0x44) == 0x44) &&
        ((addr & s->linear_mmio_mask) ==  s->linear_mmio_mask)) {
        /* memory-mapped I/O */
        cirrus_mmio_blt_write(s, addr & 0xff, val, 0);
    } else if (s->cirrus_srcptr != s->cirrus_srcptr_end) {
        /* bitblt */
        *s->cirrus_srcptr++ = (Uns8) val;
        if (s->cirrus_srcptr >= s->cirrus_srcptr_end) {
            cirrus_bitblt_cputovideo_next(s);
        }
    } else {
        /* video memory */
        if ((s->gr[0x0B] & 0x14) == 0x14) {
            addr <<= 4;
        } else if (s->gr[0x0B] & 0x02) {
            addr <<= 3;
        }
        addr &= s->cirrus_addr_mask;

        mode = s->gr[0x05] & 0x7;
        if (mode < 4 || mode > 5 || ((s->gr[0x0B] & 0x4) == 0)) {
            *(s->vram_ptr + addr) = (Uns8) val;
        } else {
            if ((s->gr[0x0B] & 0x14) != 0x14) {
            cirrus_mem_writeb_mode4and5_8bpp(s, mode, addr, val);
            } else {
            cirrus_mem_writeb_mode4and5_16bpp(s, mode, addr, val);
            }
        }
    }
}

void cirrus_linear_writew(void *opaque, Addr addr,
                 Uns32 val)
{
    TRC(__func__)
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_linear_writeb(opaque, addr, (val >> 8) & 0xff);
    cirrus_linear_writeb(opaque, addr + 1, val & 0xff);
#else
    cirrus_linear_writeb(opaque, addr, val & 0xff);
    cirrus_linear_writeb(opaque, addr + 1, (val >> 8) & 0xff);
#endif
}

void cirrus_linear_writel(void *opaque, Addr addr,
                 Uns32 val)
{
    TRC(__func__)
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_linear_writeb(opaque, addr, (val >> 24) & 0xff);
    cirrus_linear_writeb(opaque, addr + 1, (val >> 16) & 0xff);
    cirrus_linear_writeb(opaque, addr + 2, (val >> 8) & 0xff);
    cirrus_linear_writeb(opaque, addr + 3, val & 0xff);
#else
    cirrus_linear_writeb(opaque, addr, val & 0xff);
    cirrus_linear_writeb(opaque, addr + 1, (val >> 8) & 0xff);
    cirrus_linear_writeb(opaque, addr + 2, (val >> 16) & 0xff);
    cirrus_linear_writeb(opaque, addr + 3, (val >> 24) & 0xff);
#endif
}

void cirrus_linear_mem_writeb(void *opaque, Addr addr,
                                     Uns32 val)
{
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;

    addr &= s->cirrus_addr_mask;
    *(s->vram_ptr + addr) = val;
}

void cirrus_linear_mem_writew(void *opaque, Addr addr,
                                     Uns32 val)
{
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;

    addr &= s->cirrus_addr_mask;
    cpu_to_le16w((Uns16 *)(s->vram_ptr + addr), val);
}

void cirrus_linear_mem_writel(void *opaque, Addr addr,
                                     Uns32 val)
{
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;

    addr &= s->cirrus_addr_mask;
    cpu_to_le32w((Uns32 *)(s->vram_ptr + addr), val);
}

/***************************************
 *
 *  system to screen memory access
 *
 ***************************************/


Uns32 cirrus_linear_bitblt_readb(void *opaque, Addr addr)
{
    Uns32 ret;

    /* XXX handle bitblt */
    ret = 0xff;
    return ret;
}

Uns32 cirrus_linear_bitblt_readw(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_linear_bitblt_readb(opaque, addr) << 8;
    v |= cirrus_linear_bitblt_readb(opaque, addr + 1);
#else
    v = cirrus_linear_bitblt_readb(opaque, addr);
    v |= cirrus_linear_bitblt_readb(opaque, addr + 1) << 8;
#endif
    return v;
}

Uns32 cirrus_linear_bitblt_readl(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_linear_bitblt_readb(opaque, addr) << 24;
    v |= cirrus_linear_bitblt_readb(opaque, addr + 1) << 16;
    v |= cirrus_linear_bitblt_readb(opaque, addr + 2) << 8;
    v |= cirrus_linear_bitblt_readb(opaque, addr + 3);
#else
    v = cirrus_linear_bitblt_readb(opaque, addr);
    v |= cirrus_linear_bitblt_readb(opaque, addr + 1) << 8;
    v |= cirrus_linear_bitblt_readb(opaque, addr + 2) << 16;
    v |= cirrus_linear_bitblt_readb(opaque, addr + 3) << 24;
#endif
    return v;
}

void cirrus_linear_bitblt_writeb(void *opaque, Addr addr, Uns32 val)
{
    TRC(__func__)
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;
    vmiMessage("I", PREFIX_WRITE, "linear_bitblt_writeb(ref, 0x" FMT_64x ", 0x%x);\n", addr, val);
    if (s->cirrus_srcptr != s->cirrus_srcptr_end) {
        /* bitblt */
        *s->cirrus_srcptr++ = (Uns8) val;
        if (s->cirrus_srcptr >= s->cirrus_srcptr_end) {
            cirrus_bitblt_cputovideo_next(s);
        }
    }
}

void cirrus_linear_bitblt_writew(void *opaque, Addr addr,Uns32 val)
{
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_linear_bitblt_writeb(opaque, addr, (val >> 8) & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 1, val & 0xff);
#else
    cirrus_linear_bitblt_writeb(opaque, addr, val & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 1, (val >> 8) & 0xff);
#endif
}

void cirrus_linear_bitblt_writel(void *opaque, Addr addr,
                 Uns32 val)
{
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_linear_bitblt_writeb(opaque, addr, (val >> 24) & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 1, (val >> 16) & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 2, (val >> 8) & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 3, val & 0xff);
#else
    cirrus_linear_bitblt_writeb(opaque, addr, val & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 1, (val >> 8) & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 2, (val >> 16) & 0xff);
    cirrus_linear_bitblt_writeb(opaque, addr + 3, (val >> 24) & 0xff);
#endif
}


// static CPUReadMemoryFunc *cirrus_linear_bitblt_read[3] = {
//     cirrus_linear_bitblt_readb,
//     cirrus_linear_bitblt_readw,
//     cirrus_linear_bitblt_readl,
// };
//
// static CPUWriteMemoryFunc *cirrus_linear_bitblt_write[3] = {
//     cirrus_linear_bitblt_writeb,
//     cirrus_linear_bitblt_writew,
//     cirrus_linear_bitblt_writel,
// };

/* Compute the memory access functions */
void cirrus_update_memory_access(CirrusVGAStateP s)
{
    TRC(__func__)
    // not supported
    return;
    if ((s->sr[0x17] & 0x44) == 0x44) {
        goto generic_io;
    } else if (s->cirrus_srcptr != s->cirrus_srcptr_end) {
        goto generic_io;
    } else {
    if ((s->gr[0x0B] & 0x14) == 0x14) {
        goto generic_io;
    } else if (s->gr[0x0B] & 0x02) {
        goto generic_io;
    }

    Uns32 mode = s->gr[0x05] & 0x7;
    if (mode < 4 || mode > 5 || ((s->gr[0x0B] & 0x4) == 0)) {
            s->cirrus_linear_write[0] = cirrus_linear_mem_writeb;
            s->cirrus_linear_write[1] = cirrus_linear_mem_writew;
            s->cirrus_linear_write[2] = cirrus_linear_mem_writel;
        } else {
        generic_io:
            s->cirrus_linear_write[0] = cirrus_linear_writeb;
            s->cirrus_linear_write[1] = cirrus_linear_writew;
            s->cirrus_linear_write[2] = cirrus_linear_writel;
        }
    }
}

/* I/O ports */
Uns32 cirrus_vga_ioport_read(CirrusVGAStateP s, Uns32 addr, Uns32 diag)
{
    Uns32 index;
    Uns32 val;
    Bool  said = 0;
    /* check port range access depending on color/monochrome mode */
    if ((addr >= 0x3b0 && addr <= 0x3bf && (s->msr & MSR_COLOR_EMULATION))
    || (addr >= 0x3d0 && addr <= 0x3df
        && !(s->msr & MSR_COLOR_EMULATION))) {
        val = 0xff;
    } else {
        switch (addr) {
            case 0x3c0:
                if (s->ar_flip_flop == 0) {
                    val = s->ar_index;
                } else {
                    val = 0;
                }
                break;
            case 0x3c1:
                index = s->ar_index & 0x1f;
                if (index < 21)
                    val = s->ar[index];
                else
                    val = 0;
                break;
            case 0x3c2:
                val = s->st00;
                break;
            case 0x3c4:
                val = s->sr_index;
                break;
            case 0x3c5:
                if (cirrus_hook_read_sr(s, s->sr_index, &val))
                break;
                val = s->sr[s->sr_index];
                if (diag >= 3) {
                    vmiMessage("I", PREFIX_READ, "read sr[%d] => 0x%x", s->sr_index, val);
                    said = 1;
                }
                break;
            case 0x3c6:
                cirrus_read_hidden_dac(s, &val);
                break;
            case 0x3c7:
                val = s->dac_state;
                break;
            case 0x3c8:
                val = s->dac_write_index;
                s->cirrus_hidden_dac_lockindex = 0;
                break;
                case 0x3c9:
                if (cirrus_hook_read_palette(s, &val))
                break;
                val = s->palette[s->dac_read_index * 3 + s->dac_sub_index];
                if (++s->dac_sub_index == 3) {
                    s->dac_sub_index = 0;
                    s->dac_read_index++;
                }
                break;
            case 0x3ca:
                val = s->fcr;
                break;
            case 0x3cc:
                val = s->msr;
                break;
            case 0x3ce:
                val = s->gr_index;
                break;
            case 0x3cf:
                if (cirrus_vga_read_gr(s, s->gr_index, &val, diag)) {
                    said = 1;
                    break;
                }
                val = s->gr[s->gr_index];
                if (diag >= 3) {
                    vmiMessage("I", PREFIX_READ, "read gr[%d] => 0x%x", s->gr_index, val);
                    said = 1;
                }
                break;
            case 0x3b4:
            case 0x3d4:
                val = s->cr_index;
                break;
            case 0x3b5:
            case 0x3d5:
                if (cirrus_vga_read_cr(s, s->cr_index, &val, diag))
                break;
                val = s->cr[s->cr_index];
                break;
            case 0x3ba:
            case 0x3da:
                /* just toggle to fool polling */
                s->st01 ^= ST01_V_RETRACE | ST01_DISP_ENABLE;
                val = s->st01;
                s->ar_flip_flop = 0;
                break;
            default:
                val = 0x00;
                break;
        }
    }
//    fprintf(vga_trcf, "cirrus_vga.c:%s addr=0x%08x val=0x%02x\n",
//            __func__, addr, val); fflush(vga_trcf);
    if (diag >= 3 && !said) vmiMessage("I", PREFIX_READ, "read 0x%x => 0x%x", addr, val);
    return val;
}

void cirrus_vga_ioport_write(CirrusVGAStateP s, Uns32 addr, Uns32 val, Uns32 diag)
{
    Int32 index;

    /* check port range access depending on color/monochrome mode */
    Uns8 MCE = s->msr & MSR_COLOR_EMULATION;
    if ((addr >= 0x3b0 && addr <= 0x3bf && MCE) || (addr >= 0x3d0 && addr <= 0x3df && !MCE)) {
        if (diag > 1) vmiMessage("I", PREFIX_WRITE, "write ignored (MCE)\n");
        return;
    }
//    fprintf(vga_trcf, "cirrus_vga.c:%s addr=0x%08x val=0x%02x\n",
//            __func__, addr, val); fflush(vga_trcf);
    switch (addr) {
        case 0x3c0:
        if (s->ar_flip_flop == 0) {
            val &= 0x3f;
            s->ar_index = val;
            if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "ar_index=%d", val);
        } else {
            index = s->ar_index & 0x1f;

            switch (index) {
                case 0x00 ... 0x0f:
                s->ar[index] = val & 0x3f;
                break;
                case 0x10:
                s->ar[index] = val & ~0x10;
                break;
                case 0x11:
                s->ar[index] = val;
                break;
                case 0x12:
                s->ar[index] = val & ~0xc0;
                break;
                case 0x13:
                s->ar[index] = val & ~0xf0;
                break;
                case 0x14:
                s->ar[index] = val & ~0xf0;
                break;
                default:
                break;
            }
            if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "ar[%d] <= 0x%02x", s->ar_index & 0x1f, s->ar[index]);
        }
        s->ar_flip_flop ^= 1;
        break;
        case 0x3c2:
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "msr <= 0x%02x", val);
        s->msr = val & ~0x10;
        break;
        case 0x3c4:
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "sr_index <= 0x%02x", val);
        s->sr_index = val;
        break;
        case 0x3c5:
        if (cirrus_vga_write_sr(s, s->sr_index, val, diag))
            break;
        Uns8 v = val & sr_mask[s->sr_index];
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "sr[%d] <= 0x%02x", s->sr_index, v);
        s->sr[s->sr_index] = v;
        break;
        case 0x3c6:
        cirrus_write_hidden_dac(s, val, diag);
        break;
        case 0x3c7:
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "dac_read_index <= %d\n", val);
        s->dac_read_index = val;
        s->dac_sub_index = 0;
        s->dac_state = 3;
        break;
        case 0x3c8:
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "dac_write_index <= %d\n", val);
        s->dac_write_index = val;
        s->dac_sub_index = 0;
        s->dac_state = 0;
        break;
        case 0x3c9:
        if (cirrus_hook_write_palette(s, val, diag))
            break;
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "dac_cache[%d] <= 0x%02x\n", s->dac_sub_index, val);
        s->dac_cache[s->dac_sub_index] = val;
        if (++s->dac_sub_index == 3) {
            memcpy(&s->palette[s->dac_write_index * 3], s->dac_cache, 3);
            s->dac_sub_index = 0;
            if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "dac[%d] (increment index)\n", s->dac_write_index);
            s->dac_write_index++;
        }
        break;
        case 0x3ce:
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr_index <= %d\n", val);
        s->gr_index = val;
        break;
        case 0x3cf:
        if (cirrus_vga_write_gr(s, s->gr_index, val, diag))
            break;

        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "gr[%d] <= 0x%02x\n", s->gr_index, val);
        s->gr[s->gr_index] = val & gr_mask[s->gr_index];
        break;
        case 0x3b4:
        case 0x3d4:
        if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "cr_index <= %d\n", val);
        s->cr_index = val;
        break;
        case 0x3b5:
        case 0x3d5:
        if (cirrus_hook_write_cr(s, s->cr_index, val, diag))
            break;
        /* handle CR0-7 protection */
        if ((s->cr[0x11] & 0x80) && s->cr_index <= 7) {
            /* can always write bit 4 of CR7 */
            if (s->cr_index == 7) {
                if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "cr[7] <= 0x%x", val);
                s->cr[7] = (s->cr[7] & ~0x10) | (val & 0x10);
            }
            return;
        }
        switch (s->cr_index) {
        case 0x01:        /* horizontal display end */
        case 0x07:
        case 0x09:
        case 0x0c:
        case 0x0d:
        case 0x12:        /* vertical display end */
            if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "cr[%d] <= 0x%02x\n", s->cr_index, val);
            s->cr[s->cr_index] = val;
            break;

        default:
            if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "cr[%d] <= 0x%02x\n", s->cr_index, val);
            s->cr[s->cr_index] = val;
            break;
        }
        break;
        case 0x3ba:
        case 0x3da:
            if (diag >= 3) vmiMessage("I", PREFIX_WRITE, "fcr <= 0x%02x\n", val & 0x10);
            s->fcr = val & 0x10;
            break;
    }
}

/***************************************
 *
 *  memory-mapped I/O access
 *
 ***************************************/

Uns32 cirrus_mmio_readb(void *opaque, Addr addr)
{
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;

    addr &= CIRRUS_PNPMMIO_SIZE - 1;

    if (addr >= 0x100) {
        return cirrus_mmio_blt_read(s, addr - 0x100, 0);
    } else {
        return cirrus_vga_ioport_read(s, addr + 0x3c0, 0);
    }
}

Uns32 cirrus_mmio_readw(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_mmio_readb(opaque, addr) << 8;
    v |= cirrus_mmio_readb(opaque, addr + 1);
#else
    v = cirrus_mmio_readb(opaque, addr);
    v |= cirrus_mmio_readb(opaque, addr + 1) << 8;
#endif
    return v;
}

Uns32 cirrus_mmio_readl(void *opaque, Addr addr)
{
    Uns32 v;
#ifdef TARGET_WORDS_BIGENDIAN
    v = cirrus_mmio_readb(opaque, addr) << 24;
    v |= cirrus_mmio_readb(opaque, addr + 1) << 16;
    v |= cirrus_mmio_readb(opaque, addr + 2) << 8;
    v |= cirrus_mmio_readb(opaque, addr + 3);
#else
    v = cirrus_mmio_readb(opaque, addr);
    v |= cirrus_mmio_readb(opaque, addr + 1) << 8;
    v |= cirrus_mmio_readb(opaque, addr + 2) << 16;
    v |= cirrus_mmio_readb(opaque, addr + 3) << 24;
#endif
    return v;
}

void cirrus_mmio_writeb(void *opaque, Addr addr, Uns32 val)
{
    CirrusVGAStateP s = (CirrusVGAStateP ) opaque;
    vmiMessage("I", PREFIX_WRITE, "mmio_writeb(0x" FMT_64x ", 0x%x)\n", addr, val);

    addr &= CIRRUS_PNPMMIO_SIZE - 1;

    if (addr >= 0x100) {
    cirrus_mmio_blt_write(s, addr - 0x100, val, 0);
    } else {
        cirrus_vga_ioport_write(s, addr + 0x3c0, val, 0);
    }
}

void cirrus_mmio_writew(void *opaque, Addr addr,
                   Uns32 val)
{
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_mmio_writeb(opaque, addr, (val >> 8) & 0xff);
    cirrus_mmio_writeb(opaque, addr + 1, val & 0xff);
#else
    cirrus_mmio_writeb(opaque, addr, val & 0xff);
    cirrus_mmio_writeb(opaque, addr + 1, (val >> 8) & 0xff);
#endif
}

void cirrus_mmio_writel(void *opaque, Addr addr,
                   Uns32 val)
{
#ifdef TARGET_WORDS_BIGENDIAN
    cirrus_mmio_writeb(opaque, addr, (val >> 24) & 0xff);
    cirrus_mmio_writeb(opaque, addr + 1, (val >> 16) & 0xff);
    cirrus_mmio_writeb(opaque, addr + 2, (val >> 8) & 0xff);
    cirrus_mmio_writeb(opaque, addr + 3, val & 0xff);
#else
    cirrus_mmio_writeb(opaque, addr, val & 0xff);
    cirrus_mmio_writeb(opaque, addr + 1, (val >> 8) & 0xff);
    cirrus_mmio_writeb(opaque, addr + 2, (val >> 16) & 0xff);
    cirrus_mmio_writeb(opaque, addr + 3, (val >> 24) & 0xff);
#endif
}

/***************************************
 *
 *  initialize
 *
 ***************************************/

static void initTables(void)
{
    static Int32 inited;

    if (!inited) {
        inited = 1;
        Int32 i;
        for(i = 0;i < 256; i++)
            rop_to_index[i] = CIRRUS_ROP_NOP_INDEX; /* nop rop */
        rop_to_index[CIRRUS_ROP_0] = 0;
        rop_to_index[CIRRUS_ROP_SRC_AND_DST] = 1;
        rop_to_index[CIRRUS_ROP_NOP] = 2;
        rop_to_index[CIRRUS_ROP_SRC_AND_NOTDST] = 3;
        rop_to_index[CIRRUS_ROP_NOTDST] = 4;
        rop_to_index[CIRRUS_ROP_SRC] = 5;
        rop_to_index[CIRRUS_ROP_1] = 6;
        rop_to_index[CIRRUS_ROP_NOTSRC_AND_DST] = 7;
        rop_to_index[CIRRUS_ROP_SRC_XOR_DST] = 8;
        rop_to_index[CIRRUS_ROP_SRC_OR_DST] = 9;
        rop_to_index[CIRRUS_ROP_NOTSRC_OR_NOTDST] = 10;
        rop_to_index[CIRRUS_ROP_SRC_NOTXOR_DST] = 11;
        rop_to_index[CIRRUS_ROP_SRC_OR_NOTDST] = 12;
        rop_to_index[CIRRUS_ROP_NOTSRC] = 13;
        rop_to_index[CIRRUS_ROP_NOTSRC_OR_DST] = 14;
        rop_to_index[CIRRUS_ROP_NOTSRC_AND_NOTDST] = 15;
    }
}

static void cirrus_init_common(CirrusVGAStateP s, Int32 device_id, Int32 is_pci)
{
    s->sr[0x06] = 0x0f;
    if (device_id == CIRRUS_ID_CLGD5446) {
        /* 4MB 64 bit memory config, always PCI */
        s->sr[0x1F] = 0x2d;        // MemClock
        s->gr[0x18] = 0x0f;        // fastest memory configuration
#if 1
        s->sr[0x0f] = 0x98;
        s->sr[0x17] = 0x20;
        s->sr[0x15] = 0x04; /* memory size 4=4MB */
        s->real_vram_size = VGA_RAM_SIZE;
#else
        s->sr[0x0f] = 0x18;
        s->sr[0x17] = 0x20;
        s->sr[0x15] = 0x03; /* memory size 3=2MB */
        s->real_vram_size = VGA_RAM_SIZE;
#endif
    } else {
        s->sr[0x1F] = 0x22;        // MemClock
        s->sr[0x0F] = CIRRUS_MEMSIZE_2M;
        if (is_pci)
            s->sr[0x17] = CIRRUS_BUSTYPE_PCI;
        else
            s->sr[0x17] = CIRRUS_BUSTYPE_ISA;
        s->real_vram_size = 2048 * 1024;
        s->sr[0x15] = 0x03; /* memory size, 3=2MB, 4=4MB */
    }
    s->cr[0x27] = device_id;
    if (s->real_vram_size != s->vram_size) {
        vmiMessage("I", "VGA_RE", "Ram is wrong size 0x%x vs 0x%x", s->vram_size, s->real_vram_size);
    }

    /* Win2K assumes that the pattern buffer is 0xff  */
    memset(s->vram_ptr, 0xff, s->real_vram_size);

    s->cirrus_hidden_dac_lockindex = 5;
    s->cirrus_hidden_dac_data      = 0;

    /* XXX: s->vram_size must be a power of two */
    s->cirrus_addr_mask = s->real_vram_size - 1;
    s->linear_mmio_mask = s->real_vram_size - 256;

    s->get_bpp = cirrus_get_bpp;
    s->get_offsets = cirrus_get_offsets;
    s->get_resolution = cirrus_get_resolution;
    s->cursor_invalidate = cirrus_cursor_invalidate;
    s->cursor_draw_line = cirrus_cursor_draw_line;
}

/***************************************
 *  Startup
 ***************************************/

CirrusVGAStateP pci_cirrus_vga_init(Uns32 vgaRamSize, void *vgaRamBase, Uns32 device_id)
{
    TRCOPEN
    CirrusVGAStateP s = malloc(sizeof(CirrusVGAState));
    memset(s, 0, sizeof(CirrusVGAState));
    vga_common_init((VGAState*)s, vgaRamBase, vgaRamSize);
    cirrus_init_common(s, device_id, 1);
    initTables();
    return s;
}
