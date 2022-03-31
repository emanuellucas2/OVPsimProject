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


// VGA modules
#include "vga_display.h"
#include "vga_state.h"
#include "cirrus_vga.h"
#include "sdl.h"

// Measure time between wakeups
// #define VGA_TIMING

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

//
// Use this type to pass pointers between PSE and native code in a fashion that
// works on both 32-bit and 64-bit hosts
//
typedef union {
    void *pointer;
    Uns64 u64;
    Uns32 u32[2];
} handle;

typedef struct vmiosObjectS  {

    // count events
    Uns32        updates;
    Uns32        registerWrites;
    Uns32        screenRamWrites;

    // the VGA RAM mapped region
    memDomainP   domain;
    Addr         sizeM1;

    CirrusVGAStateP vgaState;

} vmiosObject;

//
// FWD references
//
VMI_MEM_READ_FN(vgaDisplayRead);
VMI_MEM_WRITE_FN(vgaDisplayWrite);

//
// Called to create a display. Returns the displayState object, which is opaque.
//
static Uns64 displayInit(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          titleAddr
) {
    char  title[32] = "CL GD54xx";
    char *titleP    = title;

    if(titleAddr) {

        memDomainP domain = vmirtGetProcessorDataDomain(processor);

        // read argument value
        vmirtReadNByteDomain(domain, titleAddr, &title, sizeof(title), 0, True);
    }

    handle h = {sdl_display_init(processor, 0,0, titleP, 640, 480, 32)};

    if (!h.pointer) {
        vmiMessage("E", "VGA_UIS", "Unable to initialize SDL display");
    }

    return h.u64;
}

//
// Called to create the VGA model state.
// Allocates space for the video ram then maps this directly into simulated
// ram according to the VGA model's port connection.
//
static Uns64 cirrusInit(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         vgaRamSize,
    Addr          port_nameAddr,
    Uns32         id
) {
    // get file name from data domain
    memDomainP  domain      = vmirtGetProcessorDataDomain(processor);
    const char *portName    = vmirtGetString(domain, port_nameAddr);
    void       *vgaRamBase  = malloc(vgaRamSize);
    if (!vgaRamBase) {
        vmiMessage("F", "VGA_NP", "Failed to allocate VGA ram");
    }

    // create a local domain and map native memory to it
    memDomainP      localDomain = vmirtNewDomain("tmp", 32);
    CirrusVGAStateP vgaState    = pci_cirrus_vga_init(vgaRamSize, vgaRamBase, id);
    handle          h           = {vgaState};

    Addr lo, hi;    // dummies
    Bool isMaster;
    Bool isDynamic;
    memDomainP portDomain = vmipsePlatformPortAttributes(
        processor,
        portName,
        &lo,
        &hi,
        &isMaster,
        &isDynamic
    );

    if (!portDomain || isMaster || !isDynamic) {
        vmiMessage("F", "VGA_NP", "Failed to find remappable slave port '%s'", portName);
    }

    vgaState->memDomain   = portDomain;
    vgaState->localDomain = localDomain;

    //
    // Setup callbacks for Display Memory
    //
    object->vgaState = vgaState;
    vmirtMapCallbacks(
            localDomain,
            0,
            vgaRamSize-1,
            vgaDisplayRead,
            vgaDisplayWrite,
            (void*)object
    );

    return h.u64;
}

//
// Map the VGA ram at the PCI requested address
//
static void mapDisplay(
    vmiosObjectP object,
    handle       vgaStateHandle,
    Uns32        base
) {
    CirrusVGAStateP vgaState = vgaStateHandle.pointer;
    Uns32           bytes    = vgaState->vram_size;

    if(vgaState->base != 0xFFFFFFFF) {
        // unmap the old region first
    }
    vgaState->base = base;
    if(base) {

        Addr lowAddr  = base;
        Addr highAddr = base + bytes - 1;

        object->sizeM1   = bytes-1;
        object->domain   = vgaState->localDomain;

        vmipseAliasMemory(
            vgaState->localDomain,
            "memory",
            lowAddr,
            highAddr
        );
    }
    // Here we should really map the other 6 apertures:
    // base+1 = LFB with byte swap
    // base+2 = LFB with byte swap
    // base+3 = LFB with byte swap
    // base+4 = bitblt ram
    // base+5 = bitblt ram
    // base+6 = bitblt ram
    // base+7 = empty
}

//
// Returns true if more than 50mS (wallclock) since it was last called.
// Used to limit the refresh rate on a fast computer,
// given that there's no point in updating the screen faster than 20Hz.
// USING THIS FUNCTION AFFECTS REPEATABILITY
//

//
// Called to update the display
//
static void vgaDisplay(
    vmiosObjectP object,
    handle       vgaStateHandle,
    handle       displayStateHandle
) {
    VGAStateP vgaState     = vgaStateHandle.pointer;
    void     *displayState = displayStateHandle.pointer;

    if ((object->screenRamWrites || object->registerWrites) && sdl_needs_update(displayState)) {
        object->updates++;
        #ifdef DISPLAY_OPTIMISATION_STATS
            vmiPrintf("Update:%6d",          object->updates);
            vmiPrintf("    ram:%6d",         object->screenRamWrites);
            vmiPrintf("    reg:%6d",         object->registerWrites);
        #endif
        object->screenRamWrites = 0;
        object->registerWrites  = 0;

        vga_update_display(vgaState, displayState);
    }
}

static Uns32 ioportRead(
    vmiosObjectP object,
    handle       vgaStateHandle,
    Uns32        address,
    Uns32        diag
) {
    CirrusVGAStateP vgaState = vgaStateHandle.pointer;

    return cirrus_vga_ioport_read(vgaState, address, diag);
}

static void ioportWrite(
    vmiosObjectP object,
    handle       vgaStateHandle,
    Uns32        address,
    Uns32        data,
    Uns32        diag
) {
    object->registerWrites++;

    CirrusVGAStateP vgaState = vgaStateHandle.pointer;

    cirrus_vga_ioport_write(vgaState, address, data, diag);
}

VMI_MEM_READ_FN(vgaDisplayRead) {
//    vmiMessage("I", __func__, "Address=0x%08x, Data=0x%08x, Bytes=%d", (Uns32)address, *(Uns32*)value, bytes);
    vmiosObjectP object = (vmiosObjectP) userData;
    CirrusVGAStateP vgaState = object->vgaState;

    switch (bytes) {
    case 1: {
        *(Uns8*)value = cirrus_linear_readb(vgaState, address);
        break;
    }
    case 2: {
        *(Uns32*)value = cirrus_linear_readw(vgaState, address);

        break;
    }
    case 4: {
        *(Uns32*)value = cirrus_linear_readl(vgaState, address);
        break;
    }
    case 8: {
        ((Uns32*)value)[0] = cirrus_linear_readl(vgaState, address);
        ((Uns32*)value)[1] = cirrus_linear_readl(vgaState, address + 4);
        break;
    }
    default:
        vmiMessage("F", __func__, "Cannot read %d bytes", bytes);
        break;
    }
}

void badwritecompare(Uns32 a, Uns32 b) {
    vmiPrintf("a=%x b=%x\n", a, b);
}

VMI_MEM_WRITE_FN(vgaDisplayWrite) {
//    vmiMessage("I", __func__, "Address=0x%08x, Data=0x%08x, Bytes=%d", (Uns32)address, *(Uns32*)value, bytes);

    vmiosObjectP object = (vmiosObjectP) userData;
    CirrusVGAStateP vgaState = object->vgaState;
    object->screenRamWrites++;

    // test the local write value

    switch (bytes) {
    case 1: {
        cirrus_linear_writeb(vgaState, address, *(Uns8*)value);
        break;
    }
    case 2: {
        cirrus_linear_writew(vgaState, address, *(Uns16*)value);
        break;
    }
    case 4: {
        cirrus_linear_writel(vgaState, address, *(Uns32*)value);
        break;
    }
    case 8: {
        cirrus_linear_writel(vgaState, address, ((Uns32*)value)[0]);
        cirrus_linear_writel(vgaState, address + 4, ((Uns32*)value)[1]);
        break;
    }
    default:
        vmiMessage("F", __func__, "Cannot write %d bytes", bytes);
        break;
    }

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
        vmiMessage("W", "VGA_SDL_TEST", "Imperas Test Mode Detected. Timeout %f", testTimeout);
        result = 1;
    }

    vmirtWriteNByteDomain(domain, timeoutP, &testTimeout, sizeof(testTimeout), 0, True);

    return result;
}


// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor)
{
    init_expand_tables();
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor)
{
    //vmiMessage("I" ,"VGA_DN", "Shutting down");
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
    .packageName    = "vga",                      // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "cirrus.ovpworld.org",
        .library = "peripheral",
        .name    = "GD5446",
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
    // -------------------          -------- ------  -----------------
    // Name                         Address  Opaque  Callback
    // -------------------          -------- ------  -----------------
    .intercepts = {
        {"displayInit",             0,       True,   VMIOS_ABI_INT('8', "poa",   displayInit)},
        {"cirrusInit",              0,       True,   VMIOS_ABI_INT('8', "po4a4", cirrusInit)},
        {"vgaDisplay",              0,       True,   VMIOS_ABI_INT(0,   "o88",   vgaDisplay)},
        {"mapDisplay",              0,       True,   VMIOS_ABI_INT(0,   "o84",   mapDisplay)},
        {"ioportRead",              0,       True,   VMIOS_ABI_INT('4', "o844",  ioportRead)},
        {"ioportWrite",             0,       True,   VMIOS_ABI_INT(0,   "o8444", ioportWrite)},
        {"ImperasTestModeTimeout",  0,       True,   VMIOS_ABI_INT('4', "poa",   ImperasTestModeTimeout)},
        {0}
    }
};


