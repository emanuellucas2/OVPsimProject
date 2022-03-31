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

#ifndef VGA_STATE_H
#define VGA_STATE_H

#include "sdl.h"

#define MSR_COLOR_EMULATION 0x01
#define MSR_PAGE_SELECT     0x20

#define ST01_V_RETRACE      0x08
#define ST01_DISP_ENABLE    0x01

/* bochs VBE support */
#define CONFIG_BOCHS_VBE

#define VBE_DISPI_MAX_XRES              1600
#define VBE_DISPI_MAX_YRES              1200
#define VBE_DISPI_MAX_BPP               32

#define VBE_DISPI_INDEX_ID              0x0
#define VBE_DISPI_INDEX_XRES            0x1
#define VBE_DISPI_INDEX_YRES            0x2
#define VBE_DISPI_INDEX_BPP             0x3
#define VBE_DISPI_INDEX_ENABLE          0x4
#define VBE_DISPI_INDEX_BANK            0x5
#define VBE_DISPI_INDEX_VIRT_WIDTH      0x6
#define VBE_DISPI_INDEX_VIRT_HEIGHT     0x7
#define VBE_DISPI_INDEX_X_OFFSET        0x8
#define VBE_DISPI_INDEX_Y_OFFSET        0x9
#define VBE_DISPI_INDEX_NB              0xa

#define VBE_DISPI_ID0                   0xB0C0
#define VBE_DISPI_ID1                   0xB0C1
#define VBE_DISPI_ID2                   0xB0C2
#define VBE_DISPI_ID3                   0xB0C3
#define VBE_DISPI_ID4                   0xB0C4

#define VBE_DISPI_DISABLED              0x00
#define VBE_DISPI_ENABLED               0x01
#define VBE_DISPI_GETCAPS               0x02
#define VBE_DISPI_8BIT_DAC              0x20
#define VBE_DISPI_LFB_ENABLED           0x40
#define VBE_DISPI_NOCLEARMEM            0x80

#define VBE_DISPI_LFB_PHYSICAL_ADDRESS  0xE0000000

#ifdef CONFIG_BOCHS_VBE

#define VGA_STATE_COMMON_BOCHS_VBE              \
    Uns16 vbe_index;                         \
    Uns16 vbe_regs[VBE_DISPI_INDEX_NB];      \
    Uns32 vbe_start_addr;                    \
    Uns32 vbe_line_offset;                   \
    Uns32 vbe_bank_mask;

#else

#define VGA_STATE_COMMON_BOCHS_VBE

#endif /* !CONFIG_BOCHS_VBE */

#define CH_ATTR_SIZE (160 * 100)

#define VGA_MAX_HEIGHT 2048

#define VGA_STATE_COMMON                                             \
    Uns8 *vram_ptr;                                                  \
    Uns32 vram_offset;                                               \
    Uns32 vram_size;                                                 \
    Uns32 bios_offset;                                               \
    Uns32 latch;                                                     \
    Uns8 sr_index;                                                   \
    Uns8 sr[256];                                                    \
    Uns8 gr_index;                                                   \
    Uns8 gr[256];                                                    \
    Uns8 ar_index;                                                   \
    Uns8 ar[21];                                                     \
    Int32 ar_flip_flop;                                              \
    Uns8 cr_index;                                                   \
    Uns8 cr[256]; /* CRT registers */                                \
    Uns8 msr; /* Misc Output Register */                             \
    Uns8 fcr; /* Feature Control Register */                         \
    Uns8 st00; /* status 0 */                                        \
    Uns8 st01; /* status 1 */                                        \
    Uns8 dac_state;                                                  \
    Uns8 dac_sub_index;                                              \
    Uns8 dac_read_index;                                             \
    Uns8 dac_write_index;                                            \
    Uns8 dac_cache[3]; /* used when writing */                       \
    Int32 dac_8bit;                                                  \
    Uns8 palette[768];                                               \
    Int32 bank_offset;                                               \
    Int32 (*get_bpp)(struct VGAState *s);                            \
    void (*get_offsets)(struct VGAState *s,                          \
                        Uns32 *pline_offset,                         \
                        Uns32 *pstart_addr,                          \
                        Uns32 *pline_compare);                       \
    void (*get_resolution)(struct VGAState *s,                       \
                        Int32 *pwidth,                               \
                        Int32 *pheight);                             \
    VGA_STATE_COMMON_BOCHS_VBE                                       \
    Uns32 font_offsets[2];                                           \
    Int32 graphic_mode;                                              \
    Uns8 shift_control;                                              \
    Uns8 double_scan;                                                \
    Uns32 line_offset;                                               \
    Uns32 line_compare;                                              \
    Uns32 start_addr;                                                \
    Uns32 plane_updated;                                             \
    Uns8 last_cw, last_ch;                                           \
    Uns32 last_width, last_height; /* in chars or pixels */          \
    Uns32 last_scr_width, last_scr_height; /* in pixels */           \
    Uns8 cursor_start, cursor_end;                                   \
    Uns32 cursor_offset;                                             \
    Uns32 (*rgb_to_pixel)(Uns32 r,  Uns32 g, Uns32 b);               \
    /* hardware mouse cursor support */                              \
    Uns32 invalidated_y_table[VGA_MAX_HEIGHT / 32];                  \
    void (*cursor_invalidate)(struct VGAState *s);                   \
    void (*cursor_draw_line)(struct VGAState *s, Uns8 *d, Int32 y);  \
    /* tell for each page if it has been updated since the last time */ \
    Uns32 last_palette[256];                                         \
    Uns32 last_ch_attr[CH_ATTR_SIZE]; /* XXX: make it dynamic */     \
                                                                     \
    /* display refresh support */                                    \
    DisplayStateP ds;                                                \

typedef struct VGAState {
    VGA_STATE_COMMON
} VGAState, *VGAStateP;

#endif
