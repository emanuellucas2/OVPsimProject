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

#include <stdlib.h>
#include <string.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "pse.igen.h"

#define PREFIX "PL110_PSE"

// Normal diagnostics in SHL are only at start & end
#define DIAG_SH PSE_DIAG_LOW

#define BPORT1 0
#include "pse.macros.igen.h"

#define SCAN_DELAY_ATTRIBUTE  "scanDelay"
#define BUS_OFFSET_ATTRIBUTE  "busOffset"

#define STR(_name)  (bport1_ab_data. _name .value)

#define upbase      STR(upbase)

// lpbase is not used : only the upper panel is displayed
#define lpbase      STR(lpbase)

#define imsc        STR(imsc)
#define control     STR(control)
#define int_status  STR(int_status)

// if any control reg or pallette is changed, need to update the frame
static Bool   controlWritten = False;

static Uns32  int_mask      = 0;
static Uns32  timing[4]     = { 0 };

static double refreshPeriod = 20000; // TODO

typedef struct displaySpecS {
    Uns32 cols;
    Uns32 rows;
    Uns32 bpp;
} displaySpec;

static displaySpec display = {
    .cols       = 640,
    .rows       = 480,
    .bpp        = 16
};

typedef struct resolutionS  {
    const char *name;
    Uns32 width;
    Uns32 height;
    Uns32 bpp;
} resolutions;

resolutions supportedResolution[] = {{ "vga",  640, 480, 16},
                                     {"svga",  800, 600, 16},
                                     {"xvga", 1024, 768, 16},
                                     { "xga", 1024, 768, 16},
                                     {     0,    0,   0,  0}};

static Uns32 pallette[256];
static Uns32 rawPallette[128];

//////////////////////////////// INTERCEPTED FUNCTIONs ////////////////////////

#define FAILED_TO_INTERCEPT bhmMessage("F", PREFIX "_LCD_FI", "Failed to intercept %s", __FUNCTION__)

//
// Start the display and set the system constants
//
FUNCTOHOST(Uns32, displayInit,
    const char *title,
    Uns32 cols,
    Uns32 rows,
    Uns32 bpp,
    Uns32 palleteSize,
    void *pallet,
    Uns32 diagnostics,
    Uns32 artifactOffset,
    Uns32 packedPixels
)

//
// Set the base address of the video RAM
//
FUNCTOHOST(void, setVideoBase, Uns32 baseAddress)

//
// Use current Pallette and Video RAM to update the screen.
// Video RAM is mapped into Host space.
// Pallette has to be copied from PSE to host, but it's small
//
FUNCTOHOST(void, updateFrame, Uns32 controlReg, Uns32 update)

//
// Set the visible screen size
//
FUNCTOHOST(void, gp_resize, Uns32 width, Uns32 height, Uns32 bpp)

///////////////////////////////////////////////////////////////////////////////


static void getResolution(const char *resolution, Uns32 *width, Uns32 *height, Uns32 *bpp)
{
    Uns32 i;
    for (i=0; supportedResolution[i].name != NULL ; i++) {
        if (strcmp(resolution, supportedResolution[i].name) == 0) {
            *width = supportedResolution[i].width;
            *height = supportedResolution[i].height;
            *bpp = supportedResolution[i].bpp;
            return;
        }
    }
    bhmMessage("W", PREFIX "_NSR", "Unsupported/unknown resolution '%s', defaulting to '%s'",
                                        resolution,
                                        supportedResolution[0].name);
    *width = supportedResolution[0].width;
    *height = supportedResolution[0].height;
}

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

#define LcdBpp ((control >> 1) & 7)

Uns32 get_bits_per_pixel() {
    Uns32 bpp = 16;
    switch (LcdBpp) {
        case BPP_1:
            bpp = 1;
            break;
        case BPP_2:
            bpp = 2;
            break;
        case BPP_4:
            bpp = 4;
            break;
        case BPP_8:
            bpp = 8;
            break;
        case BPP_16:
            bpp = 16;
            break;
        case BPP_24:
            bpp = 24;
            break;
        case BPP_32:
            bpp = 32;
            break;
        default:
            bhmMessage("W", PREFIX "_BPP", "Unknown LcdBpp field coding %d, defaulting to 16 BPP", LcdBpp);
            bpp = 16;
            break;
    }
    return bpp;
}

#include "pixel.h"

static void update_pallette(int n)
{
    int i;
    Uns32 raw = rawPallette[n];

    n <<= 1;
    for (i = 0; i < 2; i++) {
        Uns32 r = (raw & 0x1f) << 3;

        raw >>= 5;
        Uns32 g = (raw & 0x1f) << 3;

        raw >>= 5;
        Uns32 b = (raw & 0x1f) << 3;

        raw >>= 6;
        switch (get_bits_per_pixel()) {
            case 8:
                pallette[n] = rgb_to_pixel8(r, g, b);
                break;
            case 15:
                pallette[n] = rgb_to_pixel15(r, g, b);
                break;
            case 16:
                pallette[n] = rgb_to_pixel16(r, g, b);
                break;
            case 24:
            case 32:
                pallette[n] = rgb_to_pixel32(r, g, b);
                break;
        }
        n++;
    }
}

static Bool enabled(void) {
    return (control & BPORT1_AB_CONTROL_EN) && (control & BPORT1_AB_CONTROL_PWR);
}

static void resize(int width, int height, int bpp)
{
    if (enabled() && (width != display.cols || height != display.rows || bpp != display.bpp)) {
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_RESIZE", "Resize height %d width %d bpp %d", height, width, bpp);
        }

        controlWritten = True;
        gp_resize(width, height, bpp);
        display.cols   = width;
        display.rows   = height;
        display.bpp    = bpp;
    }
}

////////////////////////////////////// CALLBACKS //////////////////////////////

PPM_NBYTE_READ_CB(readID) {
    static const Uns8 id[] ={ 0x10, 0x11, 0x04, 0x00, 0x0d, 0xf0, 0x05, 0xb1 };
    Uns32 reg   = (offset-0xfe0)/0x4;

    *(Uns32*)data = id[reg];
}

PPM_REG_READ_CB(readControl) {
    return control;
}

PPM_REG_READ_CB(readIMSC) {
    return int_mask;
}

PPM_REG_READ_CB(readLP) {
    return lpbase;
}

PPM_REG_READ_CB(readMIS) {
    return int_status & int_mask;
}

PPM_REG_READ_CB(readTiming) {
    return timing[PTR_TO_UNS32(user)];
}

PPM_REG_READ_CB(readUP) {
    return upbase;
}

PPM_REG_WRITE_CB(writeUP) {
    upbase = data;
    setVideoBase(upbase);
    controlWritten = True;
}

PPM_REG_WRITE_CB(writeLP) {
    // not used,.
    lpbase = data;
}

PPM_REG_WRITE_CB(writeICR) {
    int_status &= ~data;
    controlWritten = True;
}

PPM_REG_WRITE_CB(writeControl) {
    Bool old = enabled();
    control = data;
    if (old!=enabled() && (PSE_DIAG_MEDIUM)) {
        bhmMessage("I", PREFIX "_WC", "Enabled:%d", enabled());
    }
    Uns32 bpp = get_bits_per_pixel();
    if (enabled()) {
        resize(display.cols, display.rows, bpp);
    }
}

PPM_REG_WRITE_CB(writeIMSC) {
    int_mask = data;
    controlWritten = True;
}

PPM_REG_WRITE_CB(writeTiming) {
    Uns32 reg = PTR_TO_UNS32(user);
    timing[reg] = data;
    if(reg == 0) {
        Int32 n = ((data & 0xfc) + 4) * 4;
        resize(n, display.rows, display.bpp);
    } else if (reg == 1) {
        Int32 n = (data & 0x3ff) + 1;
        resize(display.cols, n, display.bpp);
    }
}

static PPM_READ_CB(readPallette) {
    Uns32 offset = addr - (handles.bport1+0x400);
    return rawPallette[offset];
}

PPM_WRITE_CB(writePallette) {
    Uns32 offset = addr - (handles.bport1+0x400);
    rawPallette[offset] = data;
    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX "_WP", "Pallette[%d] = 0x%x", offset, data);
    }
    update_pallette(offset);
    controlWritten = True;
}


static void refreshThread(void *user) {
    while(1) {
        bhmWaitDelay (refreshPeriod);
        if (enabled()) {
            updateFrame(control, controlWritten);
            controlWritten = False;
        }
    }
}

FUNCTOHOST(Bool, ImperasTestModeTimeout, double * timeout)

double ImperasTestTimeout = 0.0;
static void ImperasTestModeTimeoutThread(void *user) {
    bhmWaitDelay(ImperasTestTimeout*1000000); // timeout in seconds
    bhmFinish();
}

PPM_CONSTRUCTOR_CB(constructor) {

    if(ImperasTestModeTimeout(&ImperasTestTimeout)) {
        bhmCreateThread(ImperasTestModeTimeoutThread, 0, "ImperasTestModeTimeoutThread", 0);
    }

    Uns32 period;
    Uns32 busOffset;

    bhmUns32ParamValue(SCAN_DELAY_ATTRIBUTE,  &period);
    bhmUns32ParamValue(BUS_OFFSET_ATTRIBUTE, &busOffset);

    refreshPeriod = period;

    char title[32];
    bhmStringParamValue("title", title, sizeof(title));

    char resolution[16];
    if (bhmStringParamValue("resolution", resolution, sizeof(resolution)))
    {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX "_SR", "Set resolution to '%s'", resolution);
        }
        Uns32 width  = display.cols;
        Uns32 height = display.rows;
        Uns32 bpp    = display.bpp;
        getResolution(resolution, &width, &height, &bpp);
        display.cols       = width;
        display.rows       = height;
        display.bpp        = bpp;
    }
    Bool packedPixels;
    bhmBoolParamValue("packedPixels", &packedPixels);
    if (packedPixels) {
        bhmMessage("I", PREFIX "_PP", "Packed Pixel data buffer for 24BPP enabled");
    }

    periphConstructor();
    Uns32 palletteBase = 0x200;   // offset in bytes from port base address
    Uns32 palletteSize = 0x200;   // size in bytes

    ppmInstallReadCallback (readPallette,  0, handles.bport1 + palletteBase, palletteSize);
    ppmInstallWriteCallback(writePallette, 0, handles.bport1 + palletteBase, palletteSize);

    displayInit(
            title,
            display.cols,
            display.rows,
            32,
            sizeof(pallette),
            pallette,
            DIAG_SH,
            busOffset,
            packedPixels
    );

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_RF", "refresh starting.");
    }
    gp_resize(display.cols, display.rows ,display.bpp);
    bhmCreateThread(refreshThread, 0, "refreshThread", 0);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    if(phase==PPM_POST_SAVE_RESTORE) {
        setVideoBase(upbase);
        controlWritten = True;
        if(enabled()) {
            gp_resize(display.cols, display.rows ,display.bpp);
        }
    }
}

