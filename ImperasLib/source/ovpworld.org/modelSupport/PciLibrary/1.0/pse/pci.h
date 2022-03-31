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
 * PCI configuration bus interface.
 */

#ifndef PCI_H
#define PCI_H

#include "peripheral/impTypes.h"
#include "peripheral/ppm.h"

//
// temporarily here
//
#define PCI_IO_BASE_ADDR        0x18000000
#define PCI_MM_BASE_ADDR        0x08000000
#define BUS_PORT_NAME           "busPort"

// 32-bit read/write from pciConfig
#define CONFIG_ACCESS_32(_offset)   *(Uns32*)((Uns8*)(&pciConfig) + _offset)
#define CONFIG_ACCESS_16(_offset)   *(Uns16*)((Uns8*)(&pciConfig) + _offset)
#define CONFIG_ACCESS_8(_offset)    *(Uns8*)((Uns8*)(&pciConfig) + _offset)

#ifdef PCI_EXPRESS
#define PCI_TYPE_STR            "PCIe"
#define PCI_CONFIG_WINDOW_BITS  12
#else
#define PCI_TYPE_STR            "PCI"
#define PCI_CONFIG_WINDOW_BITS  8
#endif

#define PCI_MAX_REGISTER        (((1 << (PCI_CONFIG_WINDOW_BITS)) / 4) - 1)

// Generate the offset from the Enhanced Configuration Address Mapping base
// address given:
// B - bus number (0-255)
// D - device number (0-31)
// F - function number (0-7)
// R - [extended] register number (0-1023)
// O - offset (0-3)
#define PCI_ECAM_OFFSET(B, D, F, R, O) \
    (((B) << ((PCI_CONFIG_WINDOW_BITS) + 8)) | \
     ((D) << ((PCI_CONFIG_WINDOW_BITS) + 3)) | \
     ((F) <<  (PCI_CONFIG_WINDOW_BITS)) | \
     ((R) << 2) | \
     (O))

// Extract the bus number from an ECAM address
#define PCI_ECAM_BUS(A)         (((A) >> ((PCI_CONFIG_WINDOW_BITS) + 8)) & 0xff)

// Extract the device number from an ECAM address
#define PCI_ECAM_DEVICE(A)      (((A) >> ((PCI_CONFIG_WINDOW_BITS) + 3)) & 0x1f)

// Extract the function number from an ECAM address
#define PCI_ECAM_FUNCTION(A)    (((A) >> (PCI_CONFIG_WINDOW_BITS)) & 0x7)

// Extract the register number from an ECAM address
#define PCI_ECAM_REGISTER(A)    (((A) >> 2) & 0x3ff)

// Maximum ECAM address window size
#define PCI_ECAM_WINDOW         ((PCI_ECAM_OFFSET(255, 31, 7, (PCI_MAX_REGISTER), 3)) + 1)

typedef struct PCIconfigCommonHeaderS {
    Uns16 vendorID;              // 0
    Uns16 deviceID;              // 2

    Uns16 command;               // 4
    Uns16 status;                // 6

    Uns8  revisionID;            // 8
    Uns8  classCode[3];          // 9-B

    Uns8  cacheLineSize;         // C
    Uns8  latencyTimer;          // D
    Uns8  headerType;            // E
    Uns8  BIST;                  // F

    Uns32 reserved0[9];          // 10-33

    Uns8  capPointer;            // 34
    Uns8  reserved1;             // 35
    Uns16 reserved2;             // 36
    Uns32 reserved3;             // 38

    Uns8  interruptLine;         // 3C
    Uns8  interruptPin;          // 3D
    Uns16 reserved4;             // 3E
} PCIconfigCommonHeader, *PCIconfigCommonHeaderP, **PCIconfigCommonHeaderPP;

typedef struct PCIconfigType0HeaderS {
    Uns16 vendorID;                     // 0
    Uns16 deviceID;                     // 2

    Uns16 command;                      // 4
    Uns16 status;                       // 6

    Uns8  revisionID;                   // 8
    Uns8  classCode[3];                 // 9-B

    Uns8  cacheLineSize;                // C
    Uns8  latencyTimer;                 // D
    Uns8  headerType;                   // E
    Uns8  BIST;                         // F

    Uns32 baseAddress[6];               // 10-27
    Uns32 cardbusAddress;               // 28-2B

    Uns16 subsystemVendorID;            // 2c
    Uns16 subsystemID;                  // 2E

    Uns32 expansionROMaddress;          // 30

    Uns8  capPointer;                   // 34
    Uns8  reserved0;                    // 35
    Uns16 reserved1;                    // 36
    Uns32 reserved2;                    // 38

    Uns8  interruptLine;                // 3C
    Uns8  interruptPin;                 // 3D
    Uns8  minGnt;                       // 3E
    Uns8  maxLat;                       // 3F
} PCIconfigType0Header, *PCIconfigType0HeaderP, **PCIconfigType0HeaderPP;

typedef struct PCIconfigType1HeaderS {
    Uns16 vendorID;                     // 0
    Uns16 deviceID;                     // 2

    Uns16 command;                      // 4
    Uns16 status;                       // 6

    Uns8  revisionID;                   // 8
    Uns8  classCode[3];                 // 9-B

    Uns8  cacheLineSize;                // C
    Uns8  latencyTimer;                 // D
    Uns8  headerType;                   // E
    Uns8  BIST;                         // F

    Uns32 baseAddress[2];               // 10-17

    Uns8  primaryBusNumber;             // 18
    Uns8  secondaryBusNumber;           // 19
    Uns8  subordinateBusNumber;         // 1A
    Uns8  secondaryLatencyTimer;        // 1B

    Uns8  ioBase;                       // 1C
    Uns8  ioLimit;                      // 1D
    Uns16 secondaryStatus;              // 1E

    Uns16 memoryBase;                   // 20
    Uns16 memoryLimit;                  // 22

    Uns16 prefetchMemoryBase;           // 24
    Uns16 prefetchMemoryLimit;          // 26

    Uns32 prefetchBaseUpper32Bits;      // 28
    Uns32 prefetchLimitUpper32Bits;     // 2C

    Uns16 ioBaseUpper16Bits;            // 30
    Uns16 ioLimitUpper16Bits;           // 32

    Uns8  capPointer;                   // 34
    Uns8  reserved0;                    // 35
    Uns16 reserved1;                    // 36

    Uns32 expansionRomBaseAddress;      // 38

    Uns8  interruptLine;                // 3C
    Uns8  interruptPin;                 // 3D
    Uns16 bridgeControl;                // 3E
} PCIconfigType1Header, *PCIconfigType1HeaderP, **PCIconfigType1HeaderPP;

//
// This maps directly into PCI space
//
typedef struct PCIconfigurationHeaderS {
    Uns16 vendorID;              // 0
    Uns16 deviceID;              // 2

    Uns16 command;               // 4
    Uns16 status;                // 6

    Uns8  revisionID;            // 8
    Uns8  classCode[3];          // 9-B

    Uns8  cacheLineSize;         // C
    Uns8  latencyTimer;          // D
    Uns8  headerType;            // E
    Uns8  BIST;                  // F

    Uns32 baseAddress[6];               // 10-27
    Uns32 cardbusAddress;               // 28-2B

    Uns16 subsystemVendorID;            // 2C
    Uns16 subsystemID;                  // 2E

    Uns32 expansionROMaddress;          // 30

    Uns8  capPointer;                   // 34
    Uns8  reserved0;                    // 35
    Uns16 reserved1;                    // 36
    Uns32 reserved2;                    // 38

    Uns8  interruptLine;                // 3C
    Uns8  interruptPin;                 // 3D
    Uns8  minGnt;                       // 3E
    Uns8  maxLat;                       // 3F
    union {
        Uns32 words [48];               // 40-FF
        Uns16 halves[48*2];
        Uns8  bytes [48*4];
    } user;

#ifdef PCI_EXPRESS
    union {
        Uns32 words [960];              // 100-FFF
        Uns16 halves[960*2];
        Uns8  bytes [960*4];
    } pcie;

#endif
} PCIconfigurationHeader, *PCIconfigurationHeaderP, *PCIconfigurationHeaderPP;

typedef struct pciCfgInfoS {
    const char *desc;
    Uns8        bytes;
} pciCfgInfo;

static __attribute__((unused)) const char *pciCfgDesc[0x40] = {
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
        [0x10] = "baseAddress[0]",        // 10-27
        [0x14] = "baseAddress[1]",        // 10-27
        [0x18] = "baseAddress[2]",        // 10-27
        [0x1c] = "baseAddress[3]",        // 10-27
        [0x20] = "baseAddress[4]",        // 10-27
        [0x24] = "baseAddress[5]",        // 10-27
        [0x28] = "cardbusAddress",        // 28-2B
        [0x2c] = "subsystemVendorID",     // 2C
        [0x2e] = "subsystemID",           // 2E
        [0x30] = "expansionROMaddress",   // 30
        [0x34] = "Cap Pointer",           // 34
        [0x35] = "reserved[3]",           // 35-37
        [0x36] = "reserved[3]",           // 35-37
        [0x37] = "reserved[3]",           // 35-37
        [0x38] = "reserved[4]",           // 38
        [0x3c] = "interruptLine",         // 3C
        [0x3d] = "interruptPin",          // 3D
        [0x3e] = "minGnt",                // 3E
        [0x3f] = "maxLat",                // 3F
};

// PCI capability header
typedef struct PCIcapHeaderS {
    Uns8  capID;                // 0
    Uns8  nextCapPointer;       // 1
} PCIcapHeader, *PCIcapHeaderP, **PCIcapHeaderPP;

// PCI Power Management Capability Structure
typedef struct PCIpowerCapS {
    PCIcapHeader hdr;           // 0-1
#define PCI_POWER_CAP_ID 1

    // Names derived from freebsd/sys/dev/pci/pcireg.h
    Uns16 capRegister;          // 2
    Uns16 status;               // 4
    Uns8  bse;                  // 6
    Uns8  data;                 // 7
} PCIpowerCap, *PCIpowerCapP, **PCIpowerCapPP;

typedef struct PCImsiControlS {
    Uns16   enable                      : 1;
    Uns16   multipleMessageCapable      : 3;
    Uns16   multipleMessageEnable       : 3;
    Uns16   address64Capable            : 1;
    Uns16   perVectorMaskCapable        : 1;
    Uns16   reserved                    : 7;
} PCImsiControl;

// MSI Capability Structure
// There are 4 different MSI sizes. We simply use the largest.
typedef struct PCImsiCapS {
    PCIcapHeader hdr;           // 0-1
#define PCI_MSI_CAP_ID 5

    Uns16 control;              // 2
    Uns32 address;              // 4

    union {
        struct {
            Uns16 data;         // 8
            Uns16 reserved0;    // A
            Uns32 mask;         // C
            Uns32 pending;      // 10
            Uns32 reserved1;    // 14
        } dev32;

        struct {
            Uns32 upperAddress; // 8
            Uns16 data;         // C
            Uns16 reserved0;    // E
            Uns32 mask;         // 10
            Uns32 pending;      // 14
        } dev64;
    } u;
} PCImsiCap, *PCImsiCapP, **PCImsiCapPP;

// PCI Express Capability Structure
typedef struct PCIeCapS {
    PCIcapHeader hdr;           // 0-1
#define PCI_PCIE_CAP_ID 0x10
    Uns16 capRegister;          // 2
    Uns32 deviceCap;            // 4
    Uns16 deviceControl;        // 8
    Uns16 deviceStatus;         // A
    Uns32 linkCap;              // C
    Uns16 linkControl;          // 10
    Uns16 linkStatus;           // 12
    Uns32 slotCap;              // 14
    Uns16 slotControl;          // 18
    Uns16 slotStatus;           // 1A
    Uns16 rootControl;          // 1C
    Uns16 rootCap;              // 1E
    Uns32 rootStatus;           // 20
    Uns32 deviceCap2;           // 24
    Uns16 deviceControl2;       // 28
    Uns16 deviceStatus2;        // 2A
    Uns32 linkCap2;             // 2C
    Uns16 linkControl2;         // 30
    Uns16 linkStatus2;          // 32
    Uns32 slotCap2;             // 34
    Uns16 slotControl2;         // 38
    Uns16 slotStatus2;          // 3A
} PCIeCap, *PCIeCapP, **PCIeCapPP;

// PCI Express Extended Capability Header
typedef struct PCIextCapHeaderS {
    Uns16 capID;                // 0-1
    Uns16 capVersion    : 4;    // 2
    Uns16 nextCapOffset : 12;   // 2-3
} PCIextCapHeader, *PCIextCapHeaderP, **PCIextCapHeaderPP;

// PCIe Device Serial Number Extended Capability
typedef struct PCIeDevSerialNumCapS {
    PCIextCapHeader hdr;        // 0-3
#define PCIE_DEV_SERIAL_NUM_ID 0x0003

    Uns32 serialNumberLower;    // 4
    Uns32 serialNumberUpper;    // 8
} PCIeDevSerialNumCap, *PCIeDevSerialNumCapP, **PCIeDevSerialNumCapPP;

// Vendor-Specific Extended Capability Header
typedef struct PCIeVsecHeaderS {
    PCIextCapHeader hdr;        // 0-3
#define PCIE_VSEC_ID 0x000b

    Uns16 vsecID;               // 4-5
    Uns16 vsecVersion : 4;      // 6
    Uns16 vsecLength  : 12;     // 6-7
} PCIeVsecHeader, *PCIeVsecHeaderP, **PCIeVsecHeaderPP;

//
// A PCI device can have this many mappable regions
//
#ifdef PCI_EXPRESS
#define MAX_REGIONS     12
#else
#define MAX_REGIONS     6
#endif

//
// Function called to install a PCI region
// install=0 implies uninstall
//
typedef void (*regionInstaller)(Uns32 base, Uns32 bytes, Bool install, void *user);

//
// One of these for each baseAddress
//
typedef struct PCIregionS {
    Uns32           regOffset;     // offset of the region's baseAddress register
    Uns32           mask;          // mask reply to probe request
    Uns32           mapping;       // current base address
    void            *windowOrUser; // ptr to window or user data pased to cb
    regionInstaller cb;
    Uns32           size;       // window size in bytes
    Bool            mapped;     // Has been mapped already
} PCIregion, *PCIregionP, **PCIregionPP;

#define ASSERT(_e,_str)  if(!(_e)) bhmMessage("F", PREFIX, "Assertion Faulure:" _str);

//
// Export to the user
//
extern PCIconfigurationHeader pciConfig;

extern ppmAddressSpaceHandle masterHandle;

//
// Install a PCI region
//     region is the region number (0-5)
//     remap is the function called to remap the region
//     Either window or cb must be specified, not both
//
void pciInstallRegion(
    Uns32           regOffset,     // offset of the region baseAddress register
    Uns32           mask,          // see PCI spec
    void            *windowOrUser, // address of local window
    regionInstaller cb,            // called when a region is mapped
    Uns32           size           // window size
);

//
// Callback when a user-writable register is written
//
typedef void (*writeCB)(void *user, Uns32 offset, Uns32 data);

//
// Tell the PCI implementation it's OK to write to this region
// (and get a callback if required)
//
void pciInstallUserWritable(
    Uns32      regOffset,
    Uns32      bytes,
    writeCB    writeFn,
    void       *user
);

#define USER_REG_DESC_FN(NAME) const char *(NAME)(Uns32 regOffset, Uns32 delta)

typedef USER_REG_DESC_FN(*userRegDescFn);

typedef struct PCIuserRegDescS {
    union {
        const char    ** str;
        userRegDescFn    fn;
    } desc;

    Uns32 type; 
#define PCI_USER_REG_DESC_STRING    0
#define PCI_USER_REG_DESC_FN        1

} PCIuserRegDesc, *PCIuserRegDescP, **PCIuserRegDescPP;

typedef const PCIuserRegDesc *PCIuserRegDescCP;

//
// Tell the PCI implementation it's OK to write to this region
// (and get a callback if required)
// Provides a table of register names to display.
//
void pciInstallUserWritableEx(
    Uns32            regOffset,
    Uns32            bytes,
    writeCB          writeFn,
    void             *user,
    PCIuserRegDescCP regDesc
);

//
// Install the PCI [Express] Power Management Capability
//
void pciInstallPowerMgmtCap(
    Uns32   regOffset,
    writeCB writeFn,
    void    *user
);

//
// Install the PCI [Express] MSI Capablity
//
void pciInstallMsiCap(
    Uns32   regOffset,
    Bool    has64BitAddressing,
    Bool    hasPerVectorMask,
    Uns32   multipleMessageCapable,
    writeCB writeFn,
    void    *user
);

//
// Install the PCI Express Capability
//
void pciInstallPcieCap(
    Uns32   regOffset,
    writeCB writeFn,
    void    *user
);

//
// Install the PCI Express Vendor-Specific Extended Capability
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
);

// Initialise and connect the slave to PCI config bus.
// If slavePort is non-null, this override the default name.
//
void pciConnectConfigSlavePort(const char *prefix, const char *slavePort);

//
// Initialise and connect master to bus.
//
void pciConnectBusMaster(void);

Bool endianBig;
#define PCIENDIANNET "swapBytes"
ppmNetHandle pciEndianNetHandle;

#endif /*PCI_H*/
