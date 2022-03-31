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

/*
 * Arm PrimeCell PL110 Color LCD Controller
 *
 * Copyright (c) 2005 CodeSourcery, LLC.
 * Written by Paul Brook
 *
 * This code is licenced under the GNU LGPL
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

#include "sdl.h"
#include "pixel.h"

#define BPORT1 0
#include "pse.macros.igen.h"

#define INVALID_BASE 0xFFFFFFFF
#define PORT_NAME    "memory"

#define PREFIX       "PL110"
#define PL110_DEBUG  0

#define MAX_RAMBUFFER (128 * 1024 * 1024)

#define NUM_VIDEO_BUFFERS 2

typedef struct videoBufferS {

    // pointer and size of native video ram, mapped into simulated address space
    void        *videoRam;

    // address in simulated space
    Addr         videoBase;
    Addr         videoTop;

    // Optimisation
    Bool         screenWritten;
    Uns8        *lineChanged;         // map of lines that need updating
    Uns32        lowestRowChanged;    // remember the (vertical) region that was updated.
    Uns32        highestRowChanged;

} videoBufferT, *videoBufferP;


typedef struct vmiosObjectS  {

    // return register (standard ABI)
    vmiRegInfoCP result;

    // stack pointer (standard ABI)
    vmiRegInfoCP sp;

    memDomainP   pseDomain;
    memDomainP   videoRamDomain;

    // opaque handle to SDL display object
    void        *sdlDisplay;

    videoBufferT videoBuffer[NUM_VIDEO_BUFFERS];
    // pointer to currently used qBuff
    videoBufferP current;

    // pointer and size of native video ram, mapped into simulated address space
  //  void        *videoRam;
    Uns32        videoBytes;

    // address in simulated space
  //  Addr         videoBase;
  //  Addr         videoTop;

    // temporary hack to alow the model to be connected
    // to a bus bridged to a low address.
    Addr         artifactOffset;

    // screen spec
    Uns32        rows;
    Uns32        cols;
    Uns32        bpp;           // The actual number of bits per pixel (not control word encoding)
    Uns32        srcWidth;
    Uns32        controlReg;     // Copy of PSE control register (CR)
    Uns32        packedPixels;  // When 24BPP these may be stored as 24bit or in 32bit (8 bit padded)

    // the RAM mapped region
    memDomainP   portDomain;

    // Palette
    void        *palette;
    Uns32        paletteSize;
    Addr         paletteBase;

    // Optimisation
    Bool         optimise;
   // Bool         screenWritten;
    Uns32        noUpdate;            // updated avoided; no change
    Uns32        verbose;
  //  Uns8        *lineChanged;         // map of lines that need updating
  //  Uns32        lowestRowChanged;    // remember the (vertical) region that was updated.
  //  Uns32        highestRowChanged;

    // Statistics
    Uns64        refreshes;           // refresh called
    Uns64        updated;             // something was done
    Uns64        rowUpdates;          // number of rows updated
    Uns64        sdlRows;             // rows updated in SDL

} vmiosObject;


/////////////////////// VIDEO RAM to  SCREEN //////////////////////////////////





#define xglue(x, y) x ## y
#define glue(x, y) xglue(x, y)
#define bswap32(_x) _x

typedef void (*drawfn)(Uns32 *, Uns8 *, const Uns8 *, Int32);

typedef enum bppmodeE
{
    BPP_1,
    BPP_2,
    BPP_4,
    BPP_8,
    BPP_16,
    BPP_24,
    BPP_32
} bppmode;

#define BITS 8
#include "draw.h"
#define BITS 15
#include "draw.h"
#define BITS 16
#include "draw.h"
#define BITS 24
#include "draw.h"
#define BITS 32
#include "draw.h"

//
// Calculate which line was changed and prevent further callbacks
// on that line
//
static VMI_MEM_WATCH_FN(calledOnWrite) {
    vmiosObjectP object   = userData;

    videoBufferP buffer;
    Uns32 i;

    // find buffer
    for (i=0;i<NUM_VIDEO_BUFFERS;i++) {
        buffer = &object->videoBuffer[i];

        if((PL110_DEBUG == 2) && object->verbose) {
            vmiMessage("I", PREFIX "_WFB",
                "Address 0x" FMT_Ax " Try buffer %d 0x" FMT_Ax "- 0x" FMT_Ax,
                address, i, buffer->videoBase, buffer->videoTop
            );
        }

        if(buffer->videoBase != INVALID_BASE &&
           buffer->videoBase <= address && address <= buffer->videoTop) {
            // Found the buffer
            break;
        }
    }

    if(buffer->videoBase == INVALID_BASE) {
        if(object->verbose) {
            vmiMessage("W", PREFIX "_BNF",
                "Address 0x" FMT_Ax " Not found in video buffers - ignored", address
            );
        }
        return;
    }

    buffer->screenWritten = True;
    if(!(buffer->videoBase <= address) && (address <= buffer->videoTop)) {
        vmiMessage("F", PREFIX "_FA", "Writing outside screen at address 0x"FMT_Ax
                                        " buffer range 0x" FMT_Ax " to 0x" FMT_Ax,
                            address,
                            buffer->videoBase,
                            buffer->videoTop);
    }

    if (object->srcWidth) { // in case called too early

        // find the region used by this row
        Uns32 offset = address - buffer->videoBase;
        Uns32 row    = offset/object->srcWidth;
        if(!(row < object->rows*2)) {
            vmiMessage("F", PREFIX "_FR", "Row (%d) out of range (w=%d  offset=%d)",
                            row,
                            object->srcWidth,
                            offset
        );
        }

        Addr  lo     = buffer->videoBase + row * object->srcWidth;
        Addr  hi     = lo + object->srcWidth - 1;

        // desensitize this region so there are no more callbacks till next frame refresh.
        vmirtRemoveWriteCallback(object->portDomain, 0, lo, hi,calledOnWrite,object);

        if(PL110_DEBUG && object->verbose) {
            vmiMessage("I", PREFIX "_DES",
                "Desensitize wr:%d 0x"FMT_Ax "-0x"FMT_Ax " row:%d",
                offset, lo, hi, row
            );
        }

        // mark that this row has changed
        buffer->lineChanged[row] = True;

        // record the extent of the region changed
        if (row < buffer->lowestRowChanged) {
            buffer->lowestRowChanged  = row;
        }
        if (row > buffer->highestRowChanged) {
            buffer->highestRowChanged  = row;
        }
    }
}

//
// Install a callback on writes to VGA ram
//
static void installRamCallback(vmiosObjectP object)
{
    Uns32 bytes = (object->srcWidth * object->rows);
    if(bytes) {
        vmirtAddWriteCallback(
            object->portDomain,
            0,
            object->current->videoBase,
            object->current->videoBase + bytes -1,
            calledOnWrite,
            object
        );
    }
}


static inline Uns8 screenBitsPerPixel(vmiosObjectP object) {
    return object->bpp;
}

static inline Uns8 bitsPerPixel(vmiosObjectP object) {
    // BPP = bits 1-3
    return (object->controlReg >> 1) & 7;
}

static void calcSrcWidth(vmiosObjectP object) {
    object->srcWidth = object->cols;

    switch (bitsPerPixel(object)) {
        case BPP_1:
            object->srcWidth >>= 3;
            break;
        case BPP_2:
            object->srcWidth >>= 2;
            break;
        case BPP_4:
            object->srcWidth >>= 1;
            break;
        case BPP_8:
            break;
        case BPP_16:
            object->srcWidth <<= 1;
            break;
        case BPP_24:
            if(object->packedPixels) {
                object->srcWidth  *= 3;
            } else {
                object->srcWidth <<= 2;
            }
            break;
        case BPP_32:
            object->srcWidth <<= 2;
            break;
    }
}

static void  updateScreen(vmiosObjectP object) {

    if(object->sdlDisplay) {
        drawfn* fntable;
        Int32 dst_width;
        Uns8  depth = screenBitsPerPixel(object);
        switch (depth) {
            case 0:
                return;
            case 8:
                fntable = pl110_draw_fn_8;
                dst_width = 1;
                break;
            case 15:
                fntable = pl110_draw_fn_15;
                dst_width = 2;
                break;
            case 16:
                fntable = pl110_draw_fn_16;
                dst_width = 2;
                break;
            case 24:
                fntable = pl110_draw_fn_24;
                dst_width = 3;
                break;
            case 32:
                fntable = pl110_draw_fn_32;
                dst_width = 4;
                break;
            default:
                vmiMessage("F", "PL100_BCD", "Bad colour depth (%d)", depth);
                return;
        }

        Int32 bpp_offset;

        if (object->controlReg & BPORT1_AB_CONTROL_BGR)
            bpp_offset = 0;
        else
            bpp_offset = DRAWFN_RGB_OFFSET;

        drawfn fn;

        if (object->controlReg & BPORT1_AB_CONTROL_BEBO)
            fn = fntable[bitsPerPixel(object) + DRAWFN_BEBO_OFFSET + bpp_offset + object->packedPixels];
        else if (object->controlReg & BPORT1_AB_CONTROL_BEPO)
            fn = fntable[bitsPerPixel(object) + DRAWFN_BEPO_OFFSET + bpp_offset + object->packedPixels];
        else
            fn = fntable[bitsPerPixel(object) + bpp_offset + object->packedPixels];

        dst_width *= object->cols;
        Uns32 *pallette = object->palette;
        Uns8  *src      = object->current->videoRam;
        Uns8  *dst      = sdl_get_data(object->sdlDisplay);

        calcSrcWidth(object);
        Uns32 i;
        Uns32 rowsWritten = 0;
        if (object->optimise) {
            for (i = 0; i < object->rows; i++) {
                if (object->current->lineChanged[i]) {
                    fn(pallette, dst, src, object->cols);
                    object->current->lineChanged[i] = 0;
                    rowsWritten++;
                }
                dst  += dst_width;
                src  += object->srcWidth;
            }
            // re-install over the now fragmented sensitive region
            installRamCallback(object);

        } else {
            for (i = 0; i < object->rows; i++) {
                fn(pallette, dst, src, object->cols);
                dst  += dst_width;
                src  += object->srcWidth;
            }
            rowsWritten = object->rows;
            object->current->lowestRowChanged  = 0;
            object->current->highestRowChanged = object->rows;
        }
        if (PL110_DEBUG && object->verbose) {
            vmiMessage("I", "PL100_RR", "Rows written : %d", rowsWritten);
        }
        object->rowUpdates += rowsWritten;
    }
}

static void  resetLinesChanged(vmiosObjectP object) {
    int i;
    for(i = 0; i < object->rows; i++) {
        object->current->lineChanged[i] = 1;
    }
}

///////////////////////////////////////////////////////////////////////////////

static void getVideoBuffer(vmiosObjectP  object, Addr base)
{
    memDomainP  domain     = object->portDomain;
    videoBufferP buffer;
    Uns32 i;

    for (i=0;i<NUM_VIDEO_BUFFERS;i++) {
        buffer = &object->videoBuffer[i];

        if(object->verbose) {
            if(buffer->videoBase != INVALID_BASE) {
                vmiMessage("I", PREFIX "_AGB",
                    "Check for Frame Base 0x%x, buffer %u base 0x%x to %x at " FMT_NATx ,
                    (Uns32)base,
                    i,
                    (Uns32)buffer->videoBase,
                    (Uns32)buffer->videoTop,
                    (UnsPS)buffer->videoRam
                );
            } else {
                vmiMessage("I", PREFIX "_ABNF",
                    "Check for Frame Base 0x%x, buffer %u Not Allocated",
                    (Uns32)base,
                    i
                );

            }
        }

        // Hacked to just check if new base address falls into existing buffer, as
        // 0x800 offset used for boot logos was using up a buffer frame.
        if(base >= buffer->videoBase && base < buffer->videoTop) {
            object->current  = buffer;

            if(object->verbose) {
                vmiMessage("I", PREFIX "_SET",
                    "Set to video ram at %p",
                    buffer->videoRam
                );
            }
            return;
        } else if(buffer->videoBase == INVALID_BASE) {

            // Create a new buffer
            Uns32 videoBytes = object->videoBytes; //object->pitch*object->height;

            // Make space for video RAM
            if (videoBytes > MAX_RAMBUFFER) {
                // prevent a very large malloc
                vmiMessage("F", PREFIX "_UVRS", "Unlikely video ram size (%d)", videoBytes);
            }

            buffer->videoRam = calloc(videoBytes, 1);
            buffer->lineChanged = calloc(object->cols, 1); //height);

            if (!buffer->videoRam) {
                vmiMessage("F", PREFIX "_NVR", "Failed to allocate video ram");
            }

            if(object->verbose) {
                vmiMessage("I", PREFIX "_PMA",
                    "Video port '%s' has %d bytes allocated at %p",
                    PORT_NAME, //"",//object->portName,
                    videoBytes,
                    buffer->videoRam
                );
            }

            vmirtMapNativeMemory(
                    object->videoRamDomain,
                    videoBytes * i,
                    (videoBytes * (i+1)) -1,
                    buffer->videoRam);

            buffer->videoBase = base;
            buffer->videoTop = base + videoBytes -1;
            // set current buffer pointer
            object->current  = buffer;

            // Alias the memory to local memory starting address 0
            // All frames are the same size
            vmirtAliasMemory(
                object->videoRamDomain,
                domain,
                videoBytes * i,
                (videoBytes * (i+1)) -1,
                buffer->videoBase,
                NULL
            );

            return;

        }
    }
    vmiMessage("F", PREFIX "_NOBUFFERS", "Failed to allocate a new video buffer");
}

static void resetVideoBuffers(vmiosObjectP  object)
{
    memDomainP  domain     = object->portDomain;
    videoBufferP buffer;
    Uns32 i;

    for (i=0;i<NUM_VIDEO_BUFFERS;i++) {
        buffer = &object->videoBuffer[i];

        if(buffer->videoBase != INVALID_BASE) {

            Uns32 videoBytes = object->videoBytes; //object->pitch*object->height;
            if( buffer->videoTop != (buffer->videoBase + videoBytes -1)) {
                if(!buffer->videoRam || !buffer->lineChanged) {
                    vmiMessage("F", PREFIX "_NBA", "Attempting to re-allocate buffers but none allocated");
                }
                // size has changed re-allocate memory buffer
                buffer->videoRam = realloc(buffer->videoRam, videoBytes);
                buffer->lineChanged = realloc(buffer->lineChanged, object->cols); //height);

                if (!buffer->videoRam) {
                    vmiMessage("F", PREFIX "_RNVR", "Failed to re-allocate video ram");
                }

                if(object->verbose) {
                    vmiMessage("I", PREFIX "_PRA",
                        "Video port '%s' has %d bytes re-allocated at %p",
                        PORT_NAME, //"",//object->portName,
                        videoBytes,
                        buffer->videoRam
                    );
                }

                vmirtMapNativeMemory(
                        object->videoRamDomain,
                        videoBytes * i,
                        (videoBytes * (i+1)) -1,
                        buffer->videoRam);

                buffer->videoTop = buffer->videoBase + videoBytes -1;

                // Alias the memory to local memory starting address 0
                // All frames are the same size
                vmirtAliasMemory(
                    object->videoRamDomain,
                    domain,
                    videoBytes * i,
                    (videoBytes * (i+1)) -1,
                    buffer->videoBase,
                    NULL
                );
            }
        }
    }
}

Uns32 videoBufferBytes(Uns32 height, Uns32 width, Uns32 bpp, Uns32 packedPixels) {
    Uns32 videoBytes = height*width;
    switch (bpp) {
    case 1:
        videoBytes >>= 3;
        break;
    case 2:
        videoBytes >>= 2;
        break;
    case 4:
        videoBytes >>= 1;
        break;
    case 8:
        videoBytes = 1;
        break;
    case 15:
    case 16:
        videoBytes <<= 1;
        break;
    case 24:
        if(packedPixels) {
            videoBytes  *= 3;
        } else {
            videoBytes <<= 2;
        }
        break;
    case 32:
        videoBytes <<= 2;
        break;
    default:
        vmiMessage("W", PREFIX "_VBS", "No support for BPP %d, default 16", bpp);
        videoBytes = 1;
        break;
    }
    return videoBytes;
}

//
// Called to create a display.
// This is usually called 2nd, after the constructor
//
static Uns32 displayInit(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          titleAddr,
    Uns32         height,
    Uns32         width,
    Uns32         bpp,
    Uns32         palleteSize,
    Addr          paletteBase,
    Uns32         diagnostics,
    Uns32         artifactOffset,
    Uns32         packedPixels
) {
    char    title[32] = "LCD PL110";
    object->pseDomain    = vmirtGetProcessorDataDomain(processor);

    // fetch the Windows's title text.
    vmirtReadNByteDomain(object->pseDomain, titleAddr, &title, sizeof(title), 0, True);

    object->bpp            = bpp;
    object->paletteSize    = palleteSize;
    object->paletteBase    = paletteBase;
    object->verbose        = diagnostics;
    object->artifactOffset = artifactOffset;
    object->packedPixels   = packedPixels;

    object->videoBytes = videoBufferBytes(height, width, object->bpp, object->packedPixels);
    if(object->verbose) {
        vmiMessage("I", PREFIX "_INIT", "videoBytes %d height %d width %d bpp %d packed %d",
                            object->videoBytes, height, width, object->bpp, object->packedPixels);
    }

    // fetch the Windows's title text.
    vmirtReadNByteDomain(object->pseDomain, titleAddr, &title, sizeof(title), 0, True);

    // Get the video port domain and details & make sure it's the right kind of port.
    const char *portName = PORT_NAME;
    Addr lo, hi;    // dummies
    Bool isMaster;
    Bool isDynamic;
    object->portDomain = vmipsePlatformPortAttributes(
        processor,
        portName,
        &lo,
        &hi,
        &isMaster,
        &isDynamic
    );

    if (!object->portDomain || isMaster || !isDynamic) {
        vmiMessage("F", PREFIX "_NP", "Failed to find re-mappable slave port '%s'", portName);
    }

    // Make space for video RAM
    #define MAX_VIDEO_BUFFER (256 * 1024 * 1024)
    if (object->videoBytes > MAX_VIDEO_BUFFER) {
        // prevent a very large malloc
        vmiMessage("F", PREFIX "_UVRS", "Unlikely video ram size (%d), max is %d", object->videoBytes, MAX_VIDEO_BUFFER);
    }

    if(object->verbose) {
        vmiMessage("I", PREFIX "_PORT",
            "Video port '%s' has 0x%x bytes at 0x%p",
            portName,
            object->videoBytes,
            object->current->videoRam
        );
        vmiMessage("I", PREFIX "_PAL",
            "palette:0x%x bytes at 0x"FMT_Ax,
            object->paletteSize,
            object->paletteBase
        );
    }


    // Make space for the palette memory.
    object->palette = malloc(object->paletteSize);

    // map palette memory back into the PSE
    Uns32 top = object->paletteBase + object->paletteSize -1;
    vmirtMapNativeMemory(object->pseDomain, object->paletteBase, top, object->palette);

    object->videoRamDomain = vmirtNewDomain("videoRamDomain", 32);

    object->sdlDisplay = sdl_display_init(processor,0,0, title, height, width, object->bpp);

    if (!object->sdlDisplay) {
        vmiMessage("E", PREFIX "_UIS", "Unable to initialize SDL display");
    }

    Uns32 result = 0;
    return result;
}

//
// Map the PL110 ram at the PCI requested address
//
static void setVideoBase(vmiosObjectP object, Uns32 base) {

    if (object->videoBytes == 0) {
        vmiMessage("F", PREFIX "_INI", "Setting base before initialisation");
    }

    // MWH subtract any 'hack' offset caused by putting the model on
    // a local bus.
    base -= object->artifactOffset;

    if (object->verbose)
    {
        vmiMessage("I", PREFIX "_MAP", "port '" PORT_NAME "' 0x%x bytes at 0x%x", object->videoBytes, base);
    }

    getVideoBuffer(object, base);

    if(object->optimise) {
        installRamCallback(object);
    }
}

//
// Called to update the display
// Arg0: pointer to vga state structure.
// Arg1: pointer to display state structure.
//
static void updateFrame(vmiosObjectP object, Uns32 controlReg, Uns32 update) {

    // control register is passed for each frame update
    if (object->sdlDisplay && sdl_needs_update(object->sdlDisplay)) {
        object->controlReg = controlReg;
        if (update || object->current->screenWritten || !object->optimise) {
            object->updated++;
            if (PL110_DEBUG && object->verbose) {
                vmiMessage("I", PREFIX "_UP",
                    "control:%d   noUpdates:%d   range:%d-%d",
                    update,
                    object->noUpdate,
                    object->current->lowestRowChanged,
                    object->current->highestRowChanged
                );
            }
            updateScreen(object);
            if (object->current->highestRowChanged >= object->current->lowestRowChanged) {
                Uns32 rows = object->current->highestRowChanged - object->current->lowestRowChanged + 1;
                object->sdlRows  += rows;
                sdl_update(
                    object->sdlDisplay,
                    0,
                    object->current->lowestRowChanged,
                    object->cols,
                    rows
                );
            }
            // reset the range to nothing (-ve)
            object->current->lowestRowChanged  = object->rows;
            object->current->highestRowChanged = 0;

            object->noUpdate      = 0;
            object->current->screenWritten = False;
        } else {
            object->noUpdate++;
        }
    }
    object->refreshes++;
}

static void gp_resize(vmiosObjectP object, Uns32 width, Uns32 height, Uns32 bpp) {

    if (object->rows != height) {
        object->rows = height;
        if(object->optimise) {
            if (object->current->lineChanged) {
                object->current->lineChanged = realloc(object->current->lineChanged, height);
            } else {
                object->current->lineChanged = malloc(height);
            }
        }
        object->current->highestRowChanged = object->rows - 1;
        object->current->lowestRowChanged  = 0;
    }
    if(object->optimise) {
        resetLinesChanged(object);
    }

    object->cols = width;
    object->bpp = bpp;
    object->videoBytes = videoBufferBytes(height, width, bpp, object->packedPixels);
    calcSrcWidth(object);

    if(object->verbose) {
        vmiMessage("I", PREFIX "_RESIZE", "videoBytes %d height %d width %d bpp %d",
                            object->videoBytes, height, width, bpp);
    }

    if(object->sdlDisplay) {
        sdl_resize(object->sdlDisplay, width, height, bpp);
    }
    resetVideoBuffers(object);

}

static Bool ImperasTestModeTimeout(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          timeoutP
) {
    memDomainP domain      = vmirtGetProcessorDataDomain(processor);
    char      *testEnv     = getenv("IMPERAS_TESTMODE_TIMEOUT");
    double     testTimeout = 0;
    Bool       result      = False;

    if(testEnv) {
        testTimeout = atof(testEnv);
        vmiMessage("W", PREFIX "_SDL_TEST", "Imperas Test Mode Detected. Timeout %f", testTimeout);
        result = True;
    }

    vmirtWriteNByteDomain(domain, timeoutP, &testTimeout, sizeof(testTimeout), 0, True);

    return result;
}

// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
    Uns32 i;
    for(i=0;i<NUM_VIDEO_BUFFERS;i++) {
    object->videoBuffer[i].videoBase         = INVALID_BASE;
    object->videoBuffer[i].videoTop          = INVALID_BASE;
    object->videoBuffer[i].videoRam          = NULL;
    }
    object->videoBytes        = 0;

    object->optimise          = 1;
    object->verbose           = 0;

    object->refreshes         = 0;
    object->updated           = 0;
    object->rowUpdates        = 0;
    object->sdlRows           = 0;

    object->current  = &(object->videoBuffer[0]);
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
    if (object->verbose) {
        vmiPrintf("Info PL110 STATISTICS\n");
        vmiPrintf("Info   Refresh cycles    : " FMT_64u "\n", object->refreshes);
        vmiPrintf("Info   Actual updates    : " FMT_64u "\n", object->updated);
        vmiPrintf("Info   Screen row writes : " FMT_64u "\n", object->rowUpdates);
        vmiPrintf("Info   SDL row writes    : " FMT_64u "\n", object->sdlRows);
        vmiPrintf("Info ---------------------------------------------------\n");
    }
}

static VMIOS_SAVE_STATE_FN(saveState)
{
    // TODO: implement native code state save and delete peripheralSaveState
    // in user.c
}

static VMIOS_RESTORE_STATE_FN(restoreState)
{
    // TODO: implement native code state restore and delete peripheralRestoreState
    // in user.c
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,              // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,    // type
    .packageName    = "vga",                    // description
    .objectSize     = sizeof(vmiosObject),      // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "LcdPL110",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,              // object constructor
    .destructorCB   = destructor,               // object destructor

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB    = saveState,                     // state save
    .restoreCB = restoreState,                  // state restore

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                        // morph callback
    .nextPCCB       = 0,                        // get next instruction address
    .disCB          = 0,                        // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////
    // -------------------          -------- ------ -----------------
    // Name                         Address  Opaque Callback
    // -------------------          -------- ------ -----------------
    .intercepts = {
        {"displayInit",             0,       True,  VMIOS_ABI_INT('4', "poa4444a444", displayInit)},
        {"setVideoBase",            0,       True,  VMIOS_ABI_INT(0,   "o4",          setVideoBase)},
        {"updateFrame",             0,       True,  VMIOS_ABI_INT(0,   "o44",         updateFrame)},
        {"gp_resize",               0,       True,  VMIOS_ABI_INT(0,   "o444",        gp_resize)},
        {"ImperasTestModeTimeout",  0,       True,  VMIOS_ABI_INT('b', "poa",         ImperasTestModeTimeout)},
        {0}
    }
};
