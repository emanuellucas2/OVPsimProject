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


#include <SDL.h>
#include <stdlib.h>
#ifndef _WInt32
#include <signal.h>
#endif

#include "sdlinc.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

#if (IMPERAS_WINDOWS==1)
#include <sys/types.h>
#include <sys/timeb.h>

static Uns32 getWallclock(void)
{
    Uns32 curtime;
    struct _timeb tb;
    _ftime(&tb);

    curtime = (Uns32)tb.time * (Uns32)1000;
    curtime += (Uns32)tb.millitm;
    return curtime;
}
#else
#include <sys/time.h>

static Uns32 getWallclock(void)
{
    Uns32 curtime;
    struct timeval tt;
    gettimeofday(&tt, 0);

    curtime = (Uns32)tt.tv_sec * (Uns32)1000;
    curtime += (Uns32)tt.tv_usec / (Uns32)1000;

    if ((tt.tv_usec % 1000) >= 500)
       curtime++;
    return curtime;
}
#endif

//
// Simple checksum which adds each word shifted by a amount which cycles
// round prime number (23) so that the position of the data is significant
// in its contribution to the checksum, and a any accidental corruption or
// shift of the video data  (other than by 23 words) will be detected.
//
static void printChecksum(DisplayStateP ds) {
    Uns32 words = ds->bytes/4;   // if not modulo 4(!), lose the last 1-3 bytes.
    Uns32 *p   = (Uns32*)ds->data;
    Uns32 *end = p + words;
    Uns64 cksum = 0;
    Uns32 shiftReg = 0x4567;

    while(p < end) {
        Uns32 shift = shiftReg%23;
        cksum += (*p++ << (shift));
        shiftReg *= 0xABCD;
    }
    vmiMessage("I", "SDL_CKS", "%d:0x" FMT_64x, ds->bytes, cksum);
}
//
// Call this at the desired screen refresh rate
//
void sdl_update(DisplayStateP ds, Uns32 x, Uns32 y, Uns32 w, Uns32 h) {
    if (ds->graphics) {
        SDL_Surface *screen = (SDL_Surface*)ds->screen;
        SDL_UpdateRect(screen, x, y, w, h);
    }

    if (ds->checksum) {
        printChecksum(ds);
    }
}

void sdl_resize(DisplayStateP ds, Int32  w, Int32  h, Uns32 bpp)
{
    Int32 flags = SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_HWACCEL;

    if (ds->fullscreen)
        flags |= SDL_FULLSCREEN;
    if (ds->noframe)
        flags |= SDL_NOFRAME;

    again:
    if (ds->graphics) {
        SDL_Surface *screen = SDL_SetVideoMode(w, h, bpp, flags);
        if (!screen) {
            vmiMessage("F", "SDL_FSVM", "Failed to set SDL Video Mode");
        }
        if (!screen->pixels && (flags & SDL_HWSURFACE) && (flags & SDL_FULLSCREEN)) {
            flags &= ~SDL_HWSURFACE;
            goto again;
        }

        if (!screen->pixels) {
            vmiMessage("F", "SDL_NPM", "No SDL pixel map.\n");
        }
        ds->data     = screen->pixels;
        ds->linesize = screen->pitch;
        ds->depth    = screen->format->BitsPerPixel;
        ds->bytes    = ds->linesize * ds->height;
        if (screen->format->Bshift > screen->format->Rshift) {
            ds->bgr = 1;
        } else {
            ds->bgr = 0;
        }
        ds->screen = screen;   // void ptr to SDL screen info

    } else if (ds->checksum){
        if (ds->data) {
            // free the old buffer if there was one
            free(ds->data);
        }
        // set up dimensions and allocate ram as if SDL was running.
        ds->linesize = w * (bpp/8);
        ds->bytes    = w * (bpp/8) * h;
        ds->data     = calloc(ds->bytes, 1);
        ds->depth    = bpp;
        if (!ds->data) {
            vmiMessage("F", "SDL_FAC", "Failed to allocate memory\n");
        }

    }
    ds->width = w;
    ds->height = h;

//    vmiMessage("I", "SDL_DEBUG_RESIZE", "ds->linesize %d ds->depth %d ds->bytes %d "
//                                        "ds->height %d ds->width %d ds->bgr %d",
//                                         ds->linesize,   ds->depth,   ds->bytes,
//                                         ds->height,   ds->width,   ds->bgr);
}

void sdl_update_caption(DisplayStateP ds)
{
    if(ds->graphics) {
        SDL_WM_SetCaption(ds->name ? ds->name : "Graphics Adapter", "Graphics");
    }
}

void sdl_cleanup(DisplayStateP ds)
{
    if(ds->graphics) {
        SDL_Quit();
    }
}

DisplayStateP sdl_display_init(
    vmiProcessorP processor,
    Bool          full_screen,  // Try to grab the full screen
    Bool          no_frame,     // no frame aruond SDL window
    char         *title,        // the title to display
    Uns32         width,        // width of display
    Uns32         height,       // height of display
    Uns32         bpp           // bits per pixel
){
    DisplayStateP ds = calloc(1, sizeof(DisplayState));
    if (!ds) {
        vmiMessage("F", "SDL_FAD", "Failed to allocate display");
    }
    if(!width || !height) {
        vmiMessage("F", "SDL_SIZE", "Failed to set display width/height");
    }
    ds->graphics     = True;
    ds->checksum     = False;
    ds->noframe      = no_frame;
    ds->fullscreen   = full_screen;
    ds->width        = width;
    ds->height       = height;
    if(title) {
        char tmp[32];
        sprintf(tmp, " (%dx%d)", width, height);
        strcat(title, tmp);
        ds->name         = title;
    } else {
        ds->name     = "CL GD54xx";    // Default Title
    }

    if (vmirtProcessorBoolAttribute(processor, "pixelChecksum", NULL)
     || getenv("IMPERAS_PIXEL_CHECKSUM")) {
        ds->checksum = True;
    }
    if (vmirtProcessorBoolAttribute(processor, "noGraphics", NULL)
     || getenv("IMPERAS_NO_GRAPHICS")) {
        ds->graphics = False;
    }

    if(ds->graphics) {
        if (SDL_WasInit(SDL_INIT_VIDEO)==0) {
            Int32  flags = SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE;
            if (SDL_Init(flags)) {
                vmiMessage("E", "SDL_FIS", "Could not initialize SDL");
                return 0;
            }
        }
    }
    sdl_resize(ds, width, height, bpp);
    sdl_update_caption(ds);

    if (ds->graphics) {
        // TODO: These are required for the keyboard interface
        //       Need to create a common SDL interface layer
        SDL_EnableKeyRepeat(250, 50);
        SDL_EnableUNICODE(1);
    }
    return ds;
}

//
// Returns true if at least 50mS has elapsed since the previous call
//
static Bool nextRealTimeSlot(void) {
    static Uns32 lastTime = 0;
    Uns32 thisTime = getWallclock();

    if((thisTime-lastTime)>=50) {

        lastTime = thisTime;
        return True;
    }
    return False;
}


Uns32 sdl_get_depth   (DisplayStateP ds) { return ds->depth;    }

Uns8 *sdl_get_data    (DisplayStateP ds) { return ds->data;     }

Uns32 sdl_get_linesize(DisplayStateP ds) { return ds->linesize; }

Uns32 sdl_get_bgr     (DisplayStateP ds) { return ds->bgr;      }

//
// Returns true if graphics windows exists.
//
Bool  sdl_has_graphics(DisplayStateP ds) { return ds->graphics; }

//
// Returns true if a graphics adapter MUST update the SDL pixel memory.
// Returns false if the update is not required.
//
Bool  sdl_needs_update(DisplayStateP ds) { return ((ds->graphics && nextRealTimeSlot()) || ds->checksum); }
