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

#include "framebuffer.h"

#include "fbstate.h"

#define BPORT1 0

#define INVALID_BASE  0xFFFFFFFF
#define PORT_NAME     "mp"
#define PREFIX        "FRAMEBUFFER"

#define NUM_VIDEO_BUFFERS 10

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

////////////////////////////////////////

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

    memDomainP   pseDomain;
    memDomainP   videoRamDomain;

    // opaque handle to SDL display object
    void        *sdlDisplay;

    videoBufferT videoBuffer[NUM_VIDEO_BUFFERS];
    // pointer to currently used qBuff
    videoBufferP current;

    // temporary buffers used for video format conversion
    void        *tempInBuffer;
//    void        *tempOutBuffer;

    // frameBuffer State
    Addr            stateBase;
    fb_stateT       state;
    Addr            qBuffBase;
    QFrameBufferT   qBuff;

    // screen spec
    Uns32        height;
    Uns32        width;
    Uns32        pitch;
    Uns32        frameType;

    // the RAM mapped region
    char        *portName;
    memDomainP   portDomain;

    // Optimisation
    Uns32        noUpdate;            // updated avoided; no change
    Uns32        verbose;

} vmiosObject;

#define DIAG_HIGH(_d)    ((_d) >= 3)
#define DIAG_MEDIUM(_d)  ((_d) >= 2)
#define DIAG_LOW(_d)     ((_d) >= 1)

////////////////////////////////////////

void fb_init(fb_stateP state, QFrameBufferP qBuff)
{
    // Set to defaults
    qBuff->width          = 227;
    qBuff->height         = 227;
    qBuff->pitch          = 227*2;  // 16-bit RGB565
    qBuff->phys_width_mm  = 227*2;
    qBuff->phys_height_mm = 227*2;
    qBuff->rotation       = 0;
    qBuff->format         = QFRAME_BUFFER_RGB565;

}

static void  updateScreen(vmiosObjectP object) {

    Uns8  *src      = object->current->videoRam;
    Uns8  *dst      = sdl_get_data(object->sdlDisplay);

    Uns32 i;
    Uns32 rowsWritten = 0;
    if (object->state.blank)
    {
        // If blanking then fill memory
        memset( dst, 0, object->height*object->pitch );
    } else {
        for (i = 0; i < object->height; i++) {
            memcpy(dst, src, object->pitch);
            dst  += object->pitch;
            src  += object->pitch;
        }
        rowsWritten = object->height;
        object->current->lowestRowChanged  = 0;
        object->current->highestRowChanged = object->height;
        if (DIAG_HIGH(object->verbose)) {
            vmiMessage("I", PREFIX "_RR", "Rows written : %d", rowsWritten);
        }
    }
}

// copy from processor memory to internal video ram buffer
static void  copyFrameBuffer(vmiosObjectP object) {

    Uns32  src = object->current->videoBase;

    // Default is 3 channel RGB floating point (alexnet)
    if(object->frameType == 0) {
        // output video bytes
        Uns32 videoBytes  = object->pitch*object->height;
        // input
        Uns32 channels = 3;
        Uns32 videoPixels = object->width*object->height;

        if(DIAG_MEDIUM(object->verbose)) {
            vmiMessage("I", PREFIX "_CP",
                "Copy Buffer 0x"FMT_Ax", bytes %d to video ram at %p",
                object->current->videoBase,
                videoBytes,
                object->current->videoRam
            );
        }

        // conversion of storage format 3x float 32 to video format RGB656
        if(!object->tempInBuffer) object->tempInBuffer = calloc(videoPixels*channels, sizeof(Flt32));
    //    if(!object->tempOutBuffer) object->tempOutBuffer = calloc(videoBytes, sizeof(Uns8));

        vmirtReadNByteDomain (object->portDomain,  src,  object->tempInBuffer, videoPixels*channels*sizeof(Flt32), 0, False);

        Uns32 x,y;
        Uns16 *outPtr = object->current->videoRam;
        Flt32 *inPtr  = object->tempInBuffer;
        Uns32 indexIn;
        Uns32 indexOut = 0;

        for (y=0;y<object->height;y++) {
            for (x=0;x<object->width;x++) {
                // convert 3 32-bit float to one 16-bit RGB565
                Uns32 channelOffset = videoPixels;
                indexIn = x + (y*object->width);
                Flt32 Rin = inPtr[indexIn+(channelOffset*0)];
                Flt32 Gin = inPtr[indexIn+(channelOffset*1)];
                Flt32 Bin = inPtr[indexIn+(channelOffset*2)];
                Uns16 out = ((((Uns8)Rin) >>3) << 11) |
                            ((((Uns8)Gin) >>2) <<  5) |
                            ((((Uns8)Bin) >>3)      );
                indexOut=(y*(object->width+1))+x;

                outPtr[indexOut] = out;
            }
        }
    } else if(object->frameType == 1) {
        // numeric image (mnist)

// input 28x28 characters
#define INPUTGRID   28
// output convert pixel to 8x8
#define OUTPUTPIXEL  8
        // output video bytes
        Uns32 videoBytes  = object->pitch*object->height;

        if(DIAG_MEDIUM(object->verbose)) {
            vmiMessage("I", PREFIX "_CP",
                "Copy Buffer 0x"FMT_Ax", bytes %d to video ram at %p",
                object->current->videoBase,
                videoBytes,
                object->current->videoRam
            );
        }

        // conversion of storage format 28x28 uns8 to video format RGB656
        if(!object->tempInBuffer) object->tempInBuffer = calloc(INPUTGRID*INPUTGRID, sizeof(Uns8));

        vmirtReadNByteDomain (object->portDomain,  src,  object->tempInBuffer, INPUTGRID*INPUTGRID*sizeof(Uns8), 0, False);

        Uns32 xi,yi;
        Uns32 xo,yo;
        Uns16 *outPtr = object->current->videoRam;
        Uns8  *inPtr  = object->tempInBuffer;
        Uns32 indexIn;
        Uns32 indexOut = 0;

        for (xi=0;xi<INPUTGRID;xi++) {
            for (yi=0;yi<INPUTGRID;yi++) {
                // convert 1 to 8x8 grid 16-bit RGB565
                indexIn = xi + (yi*INPUTGRID);
                Uns8 in = inPtr[indexIn];
                Uns16 out = in ? 0xffff : 0;


                for (xo=0;xo<OUTPUTPIXEL;xo++) {
                    for (yo=0;yo<OUTPUTPIXEL;yo++) {
//                        indexOut=((xi*OUTPUTPIXEL)+xo) + (((yi*OUTPUTPIXEL)+yo)*object->width);
                        indexOut=(xi*OUTPUTPIXEL)+xo + (((yi*OUTPUTPIXEL)+yo)*(object->width+1));
//                        vmiMessage("I", PREFIX "_DBG",
//                            "xi %4u yi %4u indexIn %4u in %u indexOut %6u", xi, yi, indexIn, in, indexOut);
                        outPtr[indexOut] = out;
//                        vmiMessage("I", PREFIX "_DBG",
//                            "xi %4u yi %4u indexIn %4u in %u xo %4u yo %4u indexOut %4u out %x", xi, yi, indexIn, in, xi+xo, yi+yo, indexOut, out);
                    }
                }
            }
        }
    } else {
        vmiMessage("W", PREFIX "_FT","Frame Type %d not recognised", object->frameType);
    }


}

///////////////////////////////////////////////////////////////////////////////

static void getVideoBuffer(vmiosObjectP  object, Addr base)
{
    videoBufferP buffer;
    Uns32 i;

    for (i=0;i<NUM_VIDEO_BUFFERS;i++) {
        buffer = &object->videoBuffer[i];

        if(buffer->videoBase == base) {
            object->current  = buffer;

            if(DIAG_MEDIUM(object->verbose)) {
                vmiMessage("I", PREFIX "_SET",
                    "Buffer %d Set to video ram at %p",
                    i, buffer->videoRam
                );
            }
            return;

        } else if(buffer->videoBase == INVALID_BASE) {

            // Create a new buffer
            Uns32 videoBytes = object->pitch*object->height;

            // Make space for video RAM
            if (videoBytes > MAX_RAMBUFFER) {
                // prevent a very large malloc
                vmiMessage("F", PREFIX "_UVRS", "Unlikely video ram size (%d)", videoBytes);
            }

            // requires extra storage (see +1 in indexOut calculation in copyFrameBuffer function)
            buffer->videoRam = calloc(videoBytes, sizeof(Uns8)+128);

            if (!buffer->videoRam) {
                vmiMessage("F", PREFIX "_NVR", "Failed to allocate video ram");
            }

            if(DIAG_MEDIUM(object->verbose)) {
                vmiMessage("I", PREFIX "_PORT",
                    "Buffer %d. Video port '%s' has 0x%x bytes at %p",
                    i,
                    object->portName,
                    videoBytes,
                    buffer->videoRam
                );
            }

            buffer->videoBase = base;
            buffer->videoTop = base + videoBytes -1;
            // set current buffer pointer
            object->current  = buffer;

            // copy static data from memory to framebuffer
            copyFrameBuffer(object);

            return;

        }
    }
    vmiMessage("F", PREFIX "_NOBUFFERS", "Failed to allocate a new video buffer");
}

//
// Called to create a display.
// This is usually called 2nd, after the constructor
//
void displayInit(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          titleAddr,
    Addr          fbStateAddress,
    Addr          qBuffAddress,
    Uns32         diagnostics,
    Uns32         frameType
) {
    char    title[MAX_TITLE_LENGTH];

    object->pseDomain = vmirtGetProcessorDataDomain(processor);

    object->stateBase   = fbStateAddress;
    object->qBuffBase   = qBuffAddress;
    // semihost diagnostics bits 2 and 3
    object->verbose     = diagnostics >> 2;

    // fetch the Windows's title text.
    vmirtReadNByteDomain(object->pseDomain, titleAddr, &title, sizeof(title), 0, True);

    // Map the PSE state structure to native memory
    vmirtMapNativeMemory(object->pseDomain,
                         object->stateBase,
                         object->stateBase+sizeof(fb_stateT)-1,
                         &object->state);
    // initialize
    object->frameType = frameType;

    // Map the PSE qBuff structure to native memory
    vmirtMapNativeMemory(object->pseDomain,
                         object->qBuffBase,
                         object->qBuffBase+sizeof(QFrameBufferT)-1,
                         &object->qBuff);


    // Get the video port domain and details & make sure it's the right kind of port.
    object->portName = PORT_NAME;
    Addr lo, hi;    // dummies
    Bool isMaster;
    Bool isDynamic;
    object->portDomain = vmipsePlatformPortAttributes(
        processor,
        object->portName,
        &lo,
        &hi,
        &isMaster,
        &isDynamic
    );
    if (!object->portDomain || isMaster || !isDynamic) {
        vmiMessage("F", PREFIX "_NP", "Failed to find re-mappable slave port '%s'", object->portName);
    }

    // Initialise FrameBuffer state and pass address back
    fb_init(&object->state, &object->qBuff);

    object->width  = object->qBuff.width;
    object->height = object->qBuff.height;
    object->pitch  = object->qBuff.pitch;

    object->videoRamDomain = vmirtNewDomain("videoRamDomain", 32);

    object->sdlDisplay = sdl_display_init(processor, 0, 0,title,object->width,object->height,16);

    if (!object->sdlDisplay) {
        vmiMessage("F", PREFIX "_UIS", "Unable to initialize SDL display");
    }
}

void setTitle(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          titleAddr
) {
    char    title[MAX_TITLE_LENGTH];
    object->pseDomain = vmirtGetProcessorDataDomain(processor);

    // fetch the Windows's title text.
    vmirtReadNByteDomain(object->pseDomain, titleAddr, &title, sizeof(title), 0, True);

    char tmp[32];
    sprintf(tmp, " (%dx%d)", object->width, object->height);
    strcat(title, tmp);

    if(object->sdlDisplay) {
        DisplayStateP ds = (DisplayStateP)object->sdlDisplay;

        ds->name  = title;
        
        sdl_update_caption(ds);
    }

}

//
// Called to update the display
//
static void updateFrame(vmiosObjectP object) {
    if(object->state.fb_base && sdl_needs_update(object->sdlDisplay)) {
        if (DIAG_HIGH(object->verbose)) {
            vmiMessage("I", PREFIX "_UP",
                "Update: range:%d-%d",
                object->current->lowestRowChanged,
                object->current->highestRowChanged
            );
        }
        updateScreen(object);
        if (object->current->highestRowChanged >= object->current->lowestRowChanged) {
            Uns32 rows = object->current->highestRowChanged - object->current->lowestRowChanged;
            sdl_update(
                object->sdlDisplay,
                0,
                object->current->lowestRowChanged,
                object->width,
                rows
            );
        }
        // reset the range to nothing (-ve)
        object->current->lowestRowChanged  = object->height;
        object->current->highestRowChanged = 0;

    }
}

//
// Map the ram at the requested address
//
static void setVideoBase(vmiosObjectP object, Uns32 base) {

    Uns32 videoBytes = object->pitch*object->height;

    if (videoBytes == 0) {
        vmiMessage("F", PREFIX "_INI", "Setting base before initialisation");
    }

    if (DIAG_MEDIUM(object->verbose)) {
        vmiMessage("I", PREFIX "_MAP", "port '" PORT_NAME "' 0x%x bytes at 0x%x", videoBytes, base);
    }

    getVideoBuffer(object, base);

    updateFrame(object);
}

static Uns32 ImperasTestModeTimeout(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          timeoutP
) {
    memDomainP domain      = vmirtGetProcessorDataDomain(processor);
    char      *testEnv     = getenv("IMPERAS_TESTMODE_TIMEOUT");
    double     testTimeout = 0;
    Uns32      result      = 0;

    if(testEnv) {
        testTimeout = atof(testEnv);
        vmiMessage("W", PREFIX "_SDL_TEST", "Imperas Test Mode Detected - Graphics Disabled. Timeout %f", testTimeout);
        result = 1;
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
        object->videoBuffer[i].videoBase  = INVALID_BASE;
        object->videoBuffer[i].videoTop   = INVALID_BASE;
        object->videoBuffer[i].videoRam   = NULL;
    }

    object->verbose           = 0;

}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "framebuffer",              // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "internal",
        .library = "peripheral",
        .name    = "FrameBuffer",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                          // morph callback
    .nextPCCB       = 0,                          // get next instruction address
    .disCB          = 0,                          // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////
    // -------------------------   -------- ------ -----------------
    // Name                        Address  Opaque Callback
    // -------------------------   -------- ------ -----------------
    .intercepts = {
        {"displayInit",            0,       True,  VMIOS_ABI_INT(0,   "poaaa44", displayInit)},
        {"setTitle",               0,       True,  VMIOS_ABI_INT(0,   "poa",     setTitle)},
        {"setVideoBase",           0,       True,  VMIOS_ABI_INT(0,   "o4",      setVideoBase)},
        {"updateFrame",            0,       True,  VMIOS_ABI_INT(0,   "o",       updateFrame)},
        {"ImperasTestModeTimeout", 0,       True,  VMIOS_ABI_INT('4', "poa",     ImperasTestModeTimeout)},
        {0}
    }
};

