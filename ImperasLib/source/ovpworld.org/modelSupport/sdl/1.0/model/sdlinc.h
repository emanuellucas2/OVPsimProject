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

#ifndef SDL_H
#define SDL_H

#include "hostapi/impTypes.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiOSAttrs.h"

typedef struct DisplayStateS {
    Uns8         *data;      // reference to raw screen data
    Uns32         bytes;     // number of bytes in <data>
    Int32         linesize;
    Int32         depth;
    Int32         bgr;       // BGR color order instead of RGB. Only valid for depth == 32
    Int32         width;
    Int32         height;
    void         *screen;    // annon reference to screen structure
    char         *name;
    Bool          fullscreen;
    Bool          noframe;
    Bool          graphics;  // test mode sets this to false
    Bool          checksum;  // checksum the SDL screen buffer for regression tests.
} DisplayState;

typedef struct DisplayStateS *DisplayStateP;

//
// Start up the SDL environment
//
DisplayStateP sdl_display_init(
    vmiProcessorP processor,
    Bool          full_screen,  // Try to grab the full screen
    Bool          no_frame,     // no frame aruond SDL window
    char         *title,        // the title to display
    Uns32         width,        // width of display
    Uns32         height,       // height of display
    Uns32         bpp           // bits per pixel
);

void sdl_update_caption(DisplayStateP ds);

void sdl_update(DisplayStateP d, Uns32 x, Uns32 y, Uns32 width, Uns32 height);

void sdl_resize(DisplayStateP ds, Int32 w, Int32 h, Uns32 bpp);

void sdl_cleanup(DisplayStateP ds);

Uns32 sdl_get_depth(DisplayStateP ds);

Uns8 *sdl_get_data(DisplayStateP ds);

Uns32 sdl_get_linesize(DisplayStateP ds);

Uns32 sdl_get_bgr(DisplayStateP ds);

Bool  sdl_has_graphics(DisplayStateP ds);

Bool  sdl_needs_update(DisplayStateP ds);

#endif
