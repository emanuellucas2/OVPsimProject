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
 * This is the common PCI configuration code.
 * Called during start-up by PCI peripherals, it connects to the PCI configuration
 * bus, then calls each peripheral's mapping functions to map them into
 * PCI IO or Memory space.
 */

#include "string.h"

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#include "pci.h"

#define PREFIX               prefixString
#define PCI_BUS_ATTRIBUTE    "PCIbus"
#define PCI_SLOT_ATTRIBUTE   "PCIslot"
#define PCI_FN_ATTRIBUTE     "PCIfunction"
#define PCI_PORT_NAME        "PCIconfig"

// each function window is 2^8 for PCI or 2^12 for PCI Express
#define PCI_CONFIG_WINDOW   (1 << (PCI_CONFIG_WINDOW_BITS))

// masks for base address registers
#define ADDRESS_PROBE_MASK   0xFFFFFFFE
#define ADDRESS_PROBE        0xFFFFFFFE
#define MEM_SPACE_MASK       0xFFFFFFF0
#define IO_SPACE_MASK        0xFFFFFFFC
#define EXPANSION_MASK       0xFFFFF800

#define REGION_PREFETCH      0x00000008
#define REGION_4G            0x00000000
#define REGION_1M            0x00000002
#define REGION_64T           0x00000008
#define REGION_IO            0x00000001

// bits in command register
#define CMD_IO_ACCESS        0x0001
#define CMD_MEM_ACCESS       0x0002
#define CMD_MASTER_ENA       0x0004

static __attribute__((unused)) const char *pciCfg1Desc[0x40] = {
        [0x00] = "VendorID",              // 0
        [0x02] = "deviceID",              // 2
        [0x04] = "command",               // 4
        [0x06] = "status",                // 6
        [0x08] = "revisionID",            // 8
        [0x09] = "classCode[3]",          // 9-B
        [0x0a] = "classCode[3]",          // 9-B
        [0x0b] = "classCode[3]",          // 9-B
        [0x0c] = "cacheLineSize",         // C
        [0x0d] = "latencyTimer",          // D
        [0x0e] = "headerType",            // E
        [0x0f] = "BIST",                  // F
        [0x10] = "baseAddress[0]",        // 10
        [0x14] = "baseAddress[1]",        // 14
        [0x18] = "primaryBusNumber",      // 18
        [0x19] = "secondaryBusNumber",    // 19
        [0x1a] = "subordinateBusNumber",  // 1A
        [0x1b] = "secondaryLatencyTimer", // 1B
        [0x1c] = "ioBase",                // 1C
        [0x1d] = "ioLimit",               // 1D
        [0x1e] = "secondaryStatus",       // 1E
        [0x20] = "memoryBase",            // 20
        [0x22] = "memoryLimit",           // 22
        [0x24] = "prefetchMemoryBase",    // 24
        [0x26] = "prefetchMemoryLimit",   // 26
        [0x28] = "prefetchMemoryBaseUpper32Bits", // 28
        [0x2c] = "prefetchMemoryLimitUpper32Bits",// 2C
        [0x30] = "ioBaseUpper16Bits",     // 30
        [0x32] = "ioLimitUpper16Bits",    // 32
        [0x34] = "Cap Pointer",           // 34
        [0x35] = "reserved[3]",           // 35-37
        [0x36] = "reserved[3]",           // 35-37
        [0x37] = "reserved[3]",           // 35-37
        [0x38] = "expansionRomBaseAddress", // 38
        [0x3c] = "interruptLine",         // 3C
        [0x3d] = "interruptPin",          // 3D
        [0x3e] = "bridgeControl",         // 3E
};

static __attribute__((unused)) const char *pciCfgUnkownDesc[0x40] = {
        [0x00] = "VendorID",              // 0
        [0x02] = "deviceID",              // 2
        [0x04] = "command",               // 4
        [0x06] = "status",                // 6
        [0x08] = "revisionID",            // 8
        [0x09] = "classCode[3]",          // 9-B
        [0x0a] = "classCode[3]",          // 9-B
        [0x0b] = "classCode[3]",          // 9-B
        [0x0c] = "cacheLineSize",         // C
        [0x0d] = "latencyTimer",          // D
        [0x0e] = "headerType",            // E
        [0x0f] = "BIST",                  // F
        [0x34] = "Cap Pointer",           // 34
        [0x3c] = "interruptLine",         // 3C
        [0x3d] = "interruptPin",          // 3D
};

static __attribute__((unused)) const char *pciPowerCapDesc[0x8] = {
        [0x00] = "Power Cap ID",            // 0
        [0x01] = "Power Next Cap Pointer",  // 1
        [0x02] = "Power Cap Register",      // 2
        [0x04] = "Power Status",            // 4
        [0x06] = "Power BSE",               // 6
        [0x07] = "Power Data",              // 7
};

static __attribute__((unused)) const char *pciMsi32CapDesc[0x14] = {
        [0x00] = "MSI Cap ID",              // 0
        [0x01] = "MSI Next Cap Pointer",    // 1
        [0x02] = "MSI Control",             // 2
        [0x04] = "MSI Address",             // 4
        [0x08] = "MSI Data",                // 8
        [0x0C] = "MSI Mask",                // C
        [0x10] = "MSI Pending",             // 10
};

static __attribute__((unused)) const char *pciMsi64CapDesc[0x18] = {
        [0x00] = "MSI Cap ID",              // 0
        [0x01] = "MSI Next Cap Pointer",    // 1
        [0x02] = "MSI Control",             // 2
        [0x04] = "MSI Address",             // 4
        [0x08] = "MSI Upper Address",       // 8
        [0x0C] = "MSI Data",                // C
        [0x10] = "MSI Mask",                // 10
        [0x14] = "MSI Pending",             // 14
};

static __attribute__((unused)) const char *pcieCfgCapDesc[0x40] = {
        [0x00] = "PCIe Cap ID",             // 0
        [0x01] = "PCIe Next Cap Pointer",   // 1
        [0x02] = "PCIe Cap Register",       // 2
        [0x04] = "PCIe Device Cap",         // 4
        [0x08] = "PCIe Device Control",     // 8
        [0x0a] = "PCIe Device Status",      // A
        [0x0c] = "PCIe Link Cap",           // C
        [0x10] = "PCIe Link Control",       // 10
        [0x12] = "PCIe Link Status",        // 12
        [0x14] = "PCIe Slot Cap",           // 14
        [0x18] = "PCIe Slot Control",       // 18
        [0x1a] = "PCIe Slot Status",        // 1a
        [0x1c] = "PCIe Root Control",       // 1c
        [0x1e] = "PCIe Root Cap",           // 1e
        [0x20] = "PCIe Root Status",        // 20
        [0x24] = "PCIe Device Cap 2",       // 24
        [0x28] = "PCIe Device Control 2",   // 28
        [0x2a] = "PCIe Device Status 2",    // 2A
        [0x2c] = "PCIe Link Cap 2",         // 2C
        [0x30] = "PCIe Link Control 2",     // 30
        [0x32] = "PCIe Link Status 2",      // 32
        [0x34] = "PCIe Slot Cap 2",         // 34
        [0x38] = "PCIe Slot Control 2",     // 38
        [0x3a] = "PCIe Slot Status 2",      // 3a
};

//
// Areas where writes are allowed
//
typedef struct userRegionS {
    Uns32            regOffset;
    Uns32            bytes;
    writeCB          writeFn;
    void             *user;
    PCIuserRegDescCP regDesc;
} userRegion, *userRegionP;

// Window mapped to PCI configuration space
static Uns8 pciConfigWindow[PCI_CONFIG_WINDOW];

// static values of PCI config registers
PCIconfigurationHeader pciConfig;

//
// Required config capability entries for PCI Express
//
Uns32 pciPowerMgmtOffset;
Uns32 pciMsiOffset;
Uns32 pciExpressOffset;

//
// list of region base registers and their mappings
//
static PCIregion PCIregions[MAX_REGIONS];

//
// List of user-defined writable regions
//
static userRegion userRegions[MAX_REGIONS];
//
// Used in diagnostic output
//
static const char *prefixString;
static Uns32      diag = 0;

//
// Flags for PCI diagnostics
//
#define DIAG_PCI_LOW   BHM_DIAG_LOW
#define DIAG_PCI_HIGH  BHM_DIAG_HIGH

// One master port for all DMAs
ppmAddressSpaceHandle masterHandle;

//
// Next free slots
//
static Uns8       freeRegion           = 0;
static Uns8       freeUserRegion       = 0;

//
// Install a PCI region
//     region is the region number (0-5)
//     remap is the function called to remap the region
//
void pciInstallRegion(
    Uns32           regOffset,     // offset of the region baseAddress register
    Uns32           mask,          // see PCI spec
    void            *windowOrUser, // address of local window
    regionInstaller cb,            // optional cb to be called when mapped
    Uns32           size           // window size
)
{
    if (freeRegion >= MAX_REGIONS) {
        bhmMessage("F", PREFIX, "Installing too many address regions");
    }
    PCIregions[freeRegion].regOffset    = regOffset;
    PCIregions[freeRegion].mask         = mask;
    PCIregions[freeRegion].windowOrUser = windowOrUser;
    PCIregions[freeRegion].cb           = cb;
    PCIregions[freeRegion].size         = size;
    freeRegion++;
}

void pciInstallUserWritable(
    Uns32      regOffset,
    Uns32      bytes,
    writeCB    writeFn,
    void       *user
) {
    if (freeUserRegion >= MAX_REGIONS) {
        bhmMessage("F", PREFIX, "Installing too many user regions");
    }
    userRegions[freeUserRegion].regOffset = regOffset;
    userRegions[freeUserRegion].bytes     = bytes;
    userRegions[freeUserRegion].writeFn   = writeFn;
    userRegions[freeUserRegion].user      = user;
    freeUserRegion++;
}

void pciInstallUserWritableEx(
    Uns32            regOffset,
    Uns32            bytes,
    writeCB          writeFn,
    void             *user,
    PCIuserRegDescCP regDesc
)
{
    pciInstallUserWritable(regOffset, bytes, writeFn, user);
    userRegions[freeUserRegion - 1].regDesc = regDesc;
}

//
// Map the users region to the given place in the PCI IO or memory address space
//
static void installRegisterRegion(const char *port, Uns32 base, Bool io, void *window, Uns32 size)
{
    if (io) {
        ppmCreateDynamicSlavePort(port, base, size, window);
        if (DIAG_PCI_LOW) {
            bhmMessage("I", PREFIX, "Installing IO window 0x%x at 0x%x ", size, base);
        }
    } else {
        if (DIAG_PCI_LOW) {
            bhmMessage("W", PREFIX, "NOT Installing 0x%x byte ROM at 0x%x", size, base);
        }
    }
}

//
// Unmap the users region in the PCI IO or memory address space
//
static void uninstallRegisterRegion(const char *port, Uns32 base, Bool io, Uns32 size)
{
    if(io) {
        ppmDeleteDynamicSlavePort(port, base, size);
        if (DIAG_PCI_LOW) {
            bhmMessage("I", PREFIX, "Removing IO window 0x%x at 0x%x", size, base);
        }
    } else {
        // TODO : expansion ROM (though I don't know what's in it).
        if (DIAG_PCI_LOW) {
            bhmMessage("W", PREFIX, "Not Uninstalling 0x%x byte ROM at 0x%x", size, base);
        }
    }
}

//
// Map or unmap a region
//
static void updateRegionMapping(Uns8 region)
{
    const char *port = BUS_PORT_NAME;
    Uns32 size = PCIregions[region].size;
    if(size) {
        Bool  io     = ((PCIregions[region].mask & REGION_IO) != 0);
        Uns32 offset = PCIregions[region].regOffset;
        Bool  map;
        Uns32 addr;
        if (io) {
            addr = (CONFIG_ACCESS_32(offset) & IO_SPACE_MASK) | PCI_IO_BASE_ADDR;
            map  = ((pciConfig.command & CMD_IO_ACCESS) != 0);
        } else {
            addr = (CONFIG_ACCESS_32(offset) & MEM_SPACE_MASK) | PCI_MM_BASE_ADDR;
            map  = ((pciConfig.command & CMD_MEM_ACCESS) != 0);
        }
        if (PCIregions[region].mapped != map) {
            if(PCIregions[region].cb)
                PCIregions[region].cb(addr, size, map, PCIregions[region].windowOrUser);
            else {
                if (map) {
                    installRegisterRegion(port, addr, io, PCIregions[region].windowOrUser, size);
                } else {
                    uninstallRegisterRegion(port, addr, io, size);
                }
            }
            PCIregions[region].mapped = map;
        }
    }
}

//
// map or unmap all regions
//
static void updateRegionMappings(void)
{
    Uns8 i;
    for(i = 0; i < freeRegion; i++)
        updateRegionMapping(i);
}

//
// Changing the cmmand register might map or unmap all memory or IO
//
static void writeCommandStatus(Uns32 data)
{
    // clear any bits where the written word contains a 1
    pciConfig.status &= ~(data >> 16);

    data &= 0x0000FFFF;
    Uns16 change = (CMD_IO_ACCESS | CMD_MEM_ACCESS) & (data ^ pciConfig.command);
    pciConfig.command = data;
    if(change) {
        updateRegionMappings();
    }
}

static void updateBaseAddress(Uns32 regOffset, Uns32 data)
{
    Uns8 i;
    for(i= 0; i < freeRegion; i++) {
        if(regOffset == PCIregions[i].regOffset) {
            if((data & ADDRESS_PROBE) == ADDRESS_PROBE) {
                CONFIG_ACCESS_32(regOffset) = PCIregions[i].mask;
            } else {
                Uns32 new = data & PCIregions[i].mask;
                CONFIG_ACCESS_32(regOffset) = new;
                updateRegionMapping(i);
            }
            return;
        }
    }
    // No special BAR was installed, therefore it is read-only.
}

static void writeUserDefined(Uns32 regOffset, Uns32 data)
{
    Uns8 i;
    for(i= 0; i < freeUserRegion; i++) {
        Uns32 l = userRegions[i].regOffset;
        Uns32 h = l + userRegions[i].bytes-1;
        if(regOffset >= l && regOffset < h) {
            CONFIG_ACCESS_32(regOffset) = data;
            if(userRegions[i].writeFn) {
                userRegions[i].writeFn(userRegions[i].user, regOffset, data);
            }
            return;
        }
    }
    // no region found
    bhmMessage("W", PREFIX,
        "Write to a read-only  user defined register (0x%x)",
        regOffset
    );
}

static const PCIuserRegDesc powerRegDesc = {
    .desc = { .str = pciPowerCapDesc },
    .type = PCI_USER_REG_DESC_STRING,
};

//
// Install a user-writable region for the PCI power-management capability.
// Note the next pointer needs to be set after installation.
//
void pciInstallPowerMgmtCap(
    Uns32   regOffset,
    writeCB writeFn,
    void    *user
)
{
    pciInstallUserWritableEx(regOffset, sizeof(PCIpowerCap), writeFn, user, &powerRegDesc);

    CONFIG_ACCESS_8(regOffset) = PCI_POWER_CAP_ID;
}

static USER_REG_DESC_FN(getMsiRegDesc)
{
    const char * desc = NULL;

    union { PCImsiControl f; Uns16 u; } control = { .u = CONFIG_ACCESS_16(regOffset + 2) };

    if (control.f.address64Capable) {
        desc = pciMsi64CapDesc[delta];
    } else {
        desc = pciMsi32CapDesc[delta];
    }

    return desc;
}

static const PCIuserRegDesc msiRegDesc = {
    .desc = { .fn = getMsiRegDesc },
    .type = PCI_USER_REG_DESC_FN,
};

//
// Install the PCI [Express] MSI Capablity
// Note the next pointer needs to be set after installation.
//
void pciInstallMsiCap(
    Uns32   regOffset,
    Bool    has64BitAddressing,
    Bool    hasPerVectorMask,
    Uns32   multipleMessageCapable,
    writeCB writeFn,
    void    *user
)
{
    const Uns32 size[4] = { 12, 16, 20, 24 };
    Uns32 sizeIdx = 0;
    Uns16 control = 0;

    if (has64BitAddressing) {
        sizeIdx |= 1;
        control |= 1 << 7;
    }

    if (hasPerVectorMask) {
        sizeIdx |= 2;
        control |= 1 << 8;
    }

    if (multipleMessageCapable > 0x5) {
        bhmMessage("F", PREFIX,
            "Invalid MSI multiple message capable value %d is greater than 5.",
            multipleMessageCapable);
    }

    control |= multipleMessageCapable << 1;

    pciInstallUserWritableEx(regOffset, size[sizeIdx], writeFn, user, &msiRegDesc);

    CONFIG_ACCESS_8(regOffset) = PCI_MSI_CAP_ID;
    CONFIG_ACCESS_16(regOffset + 2) = control;
}

static const PCIuserRegDesc pcieRegDesc = {
    .desc = { .str = pcieCfgCapDesc },
    .type = PCI_USER_REG_DESC_STRING,
};

//
// Install the PCI Express Capability
// Note the next pointer needs to be set after installation.
//
void pciInstallPcieCap(
    Uns32   regOffset,
    writeCB writeFn,
    void    *user
)
{
    pciInstallUserWritableEx(regOffset, sizeof(PCIeCap), writeFn, user, &pcieRegDesc);

    CONFIG_ACCESS_8(regOffset) = PCI_PCIE_CAP_ID;
}

//
// Install the PCI Express Vendor-Specific Extended Capability
// Note the next pointer needs to be set after installation.
//
void pciInstallPcieVsec(
    Uns32               regOffset,
    Uns32               capVersion,
    Uns32               vsecID,
    Uns32               vsecVersion,
    Uns32               vsecLength,
    writeCB             writeFn,
    void                *user,
    PCIuserRegDescCP    regDesc
)
{
    pciInstallUserWritableEx(regOffset, vsecLength, writeFn, user, regDesc);

    PCIeVsecHeaderP vsec = (PCIeVsecHeaderP)((Uns8*)(&pciConfig) + regOffset);

    vsec->hdr.capID      = PCIE_VSEC_ID;
    vsec->hdr.capVersion = capVersion;
    vsec->vsecID         = vsecID;
    vsec->vsecVersion    = vsecVersion;
    vsec->vsecLength     = vsecLength;
}

static const char * getUserRegDesc(Uns32 regOffset)
{
    const char * desc = NULL;

    Uns8 i;
    for(i= 0; i < freeUserRegion; i++) {
        Uns32 l = userRegions[i].regOffset;
        Uns32 h = l + userRegions[i].bytes-1;
        if(regOffset >= l && regOffset < h) {
            if(userRegions[i].regDesc) {
                switch (userRegions[i].regDesc->type) {
                case PCI_USER_REG_DESC_STRING:
                    if (userRegions[i].regDesc->desc.str) {
                        desc = userRegions[i].regDesc->desc.str[regOffset - l];
                    }
                    break;

                case PCI_USER_REG_DESC_FN:
                    if (userRegions[i].regDesc->desc.fn) {
                        desc = userRegions[i].regDesc->desc.fn(l, regOffset - l);
                    }
                    break;

                default:
                    break;
                }
            }
            break;
        }
    }

    return desc;
}

static const char * getPciCfgDesc(Uns32 regOffset)
{
    const char *desc = NULL;

    switch (regOffset) {
    case 0x000 ... 0x03F:
        switch (CONFIG_ACCESS_8(0xE)) {
        case 0:
            desc = pciCfgDesc[regOffset];
            break;

        case 0x80:
            desc = pciCfg1Desc[regOffset];
            break;

        default:
            desc = pciCfgUnkownDesc[regOffset];
            break;
        }
        break;

    case 0x040 ... 0x07F:
    case 0x084 ... 0xFFF:
        desc = getUserRegDesc(regOffset);
        break;

    default:
        break;
    }

    if (desc == NULL || desc[0] == 0) {
        desc = "Unknown";
    }

    return desc;
}

//
// The read callback just returns the array values
//
static PPM_READ_CB(pciConfigRead) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(pciConfigWindow);
    Uns32 data   = 0;

    if(DIAG_PCI_HIGH) {
        bhmMessage("I", PREFIX, "pciConfigRead offset %d/0x%x bytes %d", offset, offset, bytes);
    }

    if (offset >= 0 && (offset + bytes) < PCI_CONFIG_WINDOW) {
        switch (bytes) {
        case 1:
            data = CONFIG_ACCESS_8(offset);
            break;

        case 2:
            data = CONFIG_ACCESS_16(offset);
            break;

        default:
            data = CONFIG_ACCESS_32(offset);
            break;
        }
    }

    // Always report error for tribyte access since it is not handled properly
    if(DIAG_PCI_LOW || bytes == 3) {
        const char * desc       = getPciCfgDesc(offset);
        const char * msgType[4] = { "I", "I", "E", "I" };
        const char * fmt    [4] = {
            "Read " PCI_TYPE_STR " config [%s] 0x%04x = 0x%02x",
            "Read " PCI_TYPE_STR " config [%s] 0x%04x = 0x%04x",
            "Read " PCI_TYPE_STR " config [%s] 0x%04x = 0x%08x (tribyte)",
            "Read " PCI_TYPE_STR " config [%s] 0x%04x = 0x%08x",
        };

        bhmMessage(msgType[bytes - 1], PREFIX, fmt[bytes - 1], desc, offset, data);
    }
    return data;
}

//
// Write Config Type 0 Header
//
static void configType0Write(Uns32 offset, Uns32 bytes, Uns32 data)
{
    switch (offset) {
    case 0x10 ... 0x24:
    case 0x30:
        if(DIAG_PCI_HIGH) {
            bhmMessage("I", PREFIX, "Write " PCI_TYPE_STR " base 0x%x <= 0x%08x", offset, data);
        }
        updateBaseAddress(offset, data);
        break;

    case 0x3C:
#ifdef PCI_EXPRESS
        // Only Interrupt Line is writable in PCI Express
        data = (data & 0xff) | (CONFIG_ACCESS_32(offset) & 0xff00);
#endif
        CONFIG_ACCESS_32(offset) = data;
        break;

    default:
        bhmMessage("W", PREFIX, "Attempting write to " PCI_TYPE_STR " (Read-only) 0x%x <= 0x%08x", offset, data);
        // all other registers are read-only
        break;
    }
}

//
// Write Config Type 1 Header
//
static void configType1Write(Uns32 offset, Uns32 bytes, Uns32 data)
{
    switch (offset) {
    case 0x10 ... 0x14:
    case 0x38:
        if(DIAG_PCI_HIGH) {
            bhmMessage("I", PREFIX, "Write " PCI_TYPE_STR " base 0x%x <= 0x%08x", offset, data);
        }
        updateBaseAddress(offset, data);
        break;

    case 0x18:
#ifdef PCI_EXPRESS
        // Secondary Latency Timer is read-only in PCI Express
        data = data & 0x00ffffff;
#endif
        if(DIAG_PCI_HIGH) {
            bhmMessage("I", PREFIX, "Write " PCI_TYPE_STR " bus number 0x%x <= 0x%08x", offset, data);
        }
        CONFIG_ACCESS_32(offset) = data;
        break;

    case 0x1C ... 0x30:
        if(DIAG_PCI_HIGH) {
            bhmMessage("I", PREFIX, "Write " PCI_TYPE_STR " base 0x%x <= 0x%08x", offset, data);
        }
        CONFIG_ACCESS_32(offset) = data;
        break;

    case 0x3C:
#ifdef PCI_EXPRESS
        // Interrupt Pin is read-only in PCI Express
        data = (data & 0x004300ff) | (CONFIG_ACCESS_32(offset) & 0xffbcff00);
#endif
        CONFIG_ACCESS_32(offset) = data;
        break;

    default:
        bhmMessage("W", PREFIX, "Attempting CFG Type 1 write to " PCI_TYPE_STR " (Read-only) 0x%x <= 0x%08x", offset, data);
        // all other registers are read-only
        break;
    }
}

//
// Write Config Type Unknown Header
//
static void configTypeUnknownWrite(Uns32 offset, Uns32 bytes, Uns32 data)
{
    switch (offset) {
    case 0x3C:
        CONFIG_ACCESS_8(offset) = (Uns8)data;
        break;

    default:
        bhmMessage("W", PREFIX, "Attempting CFG Type Unknown (0x%x) write to " PCI_TYPE_STR " (Read-only) 0x%x <= 0x%08x", CONFIG_ACCESS_8(0xE), offset, data);
        // all other registers are read-only
        break;
    }
}

//
// The write callback endures the registers have legal values
// and triggers changes to the address map.
//
static PPM_WRITE_CB(pciConfigWrite) {
    Uns32 mask     = -1;
    Uns32 offset   = PTR_TO_UNS32(addr) - PTR_TO_UNS32(pciConfigWindow);
    Uns32 shift    = offset & 3;
    Uns32 dwOffset = offset ^ shift;

    if(DIAG_PCI_HIGH) {
        bhmMessage("I", PREFIX, "pciConfigWrite offset %d/0x%x bytes %d", offset, offset, bytes);
    }

    shift = shift * 8;

    switch (bytes) {
    case 1:
        mask = 0xff;
        break;

    case 2:
        mask = 0xffff;
        break;

    case 3:
        bhmMessage("E", PREFIX, "Write " PCI_TYPE_STR " config unsupported tribyte access 0x%04x = %08x", offset, data);
        return;

    default:
        shift = 0;
        break;
    }

    // Default to original contents of memory.
    // Uns32 wrData = ((data & mask) << shift) | (CONFIG_ACCESS_32(dwOffset) & ~(mask << shift));

    // Always report error for tribyte access since it is not handled properly
    if(DIAG_PCI_LOW || bytes == 3) {
        const char * desc       = getPciCfgDesc(offset);
        const char * msgType[4] = { "I", "I", "E", "I" };
        const char * fmt    [4] = {
            "Write " PCI_TYPE_STR " config [%s] 0x%04x = 0x%02x",
            "Write " PCI_TYPE_STR " config [%s] 0x%04x = 0x%04x",
            "Write " PCI_TYPE_STR " config [%s] 0x%04x = 0x%08x (tribyte)",
            "Write " PCI_TYPE_STR " config [%s] 0x%04x = 0x%08x",
        };

        bhmMessage(msgType[bytes - 1], PREFIX, fmt[bytes - 1], desc, offset, ((data & mask) >> shift));
    }

    switch(dwOffset) {
        case 0x04:
            writeCommandStatus(data);
            break;

        case 0x0C:
            // Do not allow software to trash the config header type
#ifdef PCI_EXPRESS
            // PCI Express does not support the latency timer
            CONFIG_ACCESS_32(offset) = data & 0xff0000ff;
#else
            CONFIG_ACCESS_32(offset) = data & 0xff00ffff;
#endif
            break;

        // these are where we know base registers can live, there might be more.
        case 0x10 ... 0x3C:
            // check bit-7 header Type 0:single function 1:multi-function
            switch (CONFIG_ACCESS_8(0xE)) {
                case 0:
                    configType0Write(dwOffset, 4, data);
                    break;

                case 0x80:
                    configType1Write(dwOffset, 4, data);
                    break;

                default:
                    configTypeUnknownWrite(dwOffset, 4, data);
                    break;
            }
            break;

        case 0x80:
            if(DIAG_PCI_HIGH) {
                bhmMessage("I", PREFIX, "Write " PCI_TYPE_STR " base 0x%x <= 0x%08x", offset, data);
            }
            updateBaseAddress(offset, data);
            break;

        case 0x40 ... 0x7C:
        case 0x84 ... 0xFC:
#ifdef PCI_EXPRESS
        case 0x100 ... 0xFFC:
#endif
            if(DIAG_PCI_HIGH) {
                const char * desc = getUserRegDesc(offset);

                if (desc == NULL || desc[0] == 0) {
                    desc = "Unknown";
                }

                bhmMessage("I", PREFIX, "Write User Defined [%s] 0x%04x <= 0x%08x", desc, offset, data);
            }
            // user defined
            writeUserDefined(offset, data);
            break;

        default:
            bhmMessage("W", PREFIX, "Attempting CFG write to " PCI_TYPE_STR " (Read-only) 0x%x <= 0x%08x", offset, data);
            // all other registers are read-only
            break;
    }
}

//
// Initialise and connect the slave to PCI config bus.
// If slavePort is non-null, this override the default name.
//
void pciConnectConfigSlavePort(const char *prefix, const char *slavePort)
{
    if (!slavePort)
        slavePort = PCI_PORT_NAME;

#ifdef PCI_EXPRESS
    const char *busAttributeName   = PCI_BUS_ATTRIBUTE;
#endif
    const char *slotAttributeName  = PCI_SLOT_ATTRIBUTE;
    const char *fnAttributeName    = PCI_FN_ATTRIBUTE;

    Uns32 busNumber = 0;
    Uns32 slotNumber = 0;
    Uns32 fnNumber = 0;

    prefixString = prefix;
    diag         = bhmGetDiagnosticLevel();

#ifdef PCI_EXPRESS
    bhmUns32ParamValue(busAttributeName, &busNumber);
#endif
    bhmUns32ParamValue(slotAttributeName, &slotNumber);
    bhmUns32ParamValue(fnAttributeName, &fnNumber);

    Uns32 baseAddress = PCI_ECAM_OFFSET(busNumber, slotNumber, fnNumber, 0, 0);
    if(DIAG_PCI_HIGH) {
        bhmMessage("I", PREFIX, "PCI Config baseAddress=0x%08x\n", baseAddress);
    }

    // Wait for PCI controller to get ready
    bhmEventHandle started = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(started);

    if (!ppmCreateDynamicSlavePort(
        slavePort,
        baseAddress,
        sizeof(pciConfigWindow),
        pciConfigWindow
    )) {
        bhmMessage("W", PREFIX,
            "Failed to connect to " PCI_TYPE_STR " configuration bus (port %s)",
            slavePort
        );
        return;
    }

    if(DIAG_PCI_LOW) {
        bhmMessage("I", PREFIX,
            "Connected to " PCI_TYPE_STR " config bus (%s), slot:%d fn:%d (0x%x - 0x%x)",
            slavePort,
            slotNumber,
            fnNumber,
            baseAddress,
            (Uns32)(baseAddress+sizeof(pciConfigWindow)-1)
        );
    }
    ppmInstallWriteCallback(
        pciConfigWrite,
        0,
        pciConfigWindow,
        sizeof(pciConfigWindow)
    );
    ppmInstallReadCallback(
        pciConfigRead,
        0,
        pciConfigWindow,
        sizeof(pciConfigWindow)
    );
}

void pciConnectBusMaster(void)
{
    char *port = "dmaPort";
    masterHandle = ppmOpenAddressSpace(port);

    if(!masterHandle) {
        bhmMessage("F", PREFIX, "Failed to open master port '%s'\n", port);
    }
}

/*************************************************************
 * Byte Swapping Functions
 *************************************************************/

Bool endianBig = False;
ppmNetHandle pciEndianNetHandle;
