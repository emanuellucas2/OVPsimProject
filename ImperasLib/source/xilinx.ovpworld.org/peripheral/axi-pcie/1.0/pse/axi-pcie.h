/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 * Copyright (c) 2012-2018 MIPS Tech, LLC, www.mips.com
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

#include "peripheral/impTypes.h"

#ifndef XILINX_PCIE_H
#define XILINX_PCIE_H

#if 1
#define TYPE_XILINX_PCIE_HOST "xilinx-pcie-host"
#define XILINX_PCIE_HOST(obj) \
     OBJECT_CHECK(XilinxPCIEHost, (obj), TYPE_XILINX_PCIE_HOST)

#define TYPE_XILINX_PCIE_ROOT "xilinx-pcie-root"
#define XILINX_PCIE_ROOT(obj) \
     OBJECT_CHECK(XilinxPCIERoot, (obj), TYPE_XILINX_PCIE_ROOT)

typedef struct XilinxPCIERoot {
#if 0 // :FIXME:
    PCIBridge parent_obj;
#else
    Uns32 parent_obj;
#endif
} XilinxPCIERoot;

typedef struct XilinxPCIEInt {
    Uns32 fifo_reg1;
    Uns32 fifo_reg2;
} XilinxPCIEInt;

typedef struct XilinxPCIEHost {
#if 0 // :FIXME:
    PCIExpressHost parent_obj;
#else
    Uns32 parent_obj;
#endif

    char name[16];

    Uns32 bus_nr;
    Uns64 cfg_base, cfg_size;
    Uns64 mmio_base, mmio_size;
    Bool link_up;
    ppmNetHandle irq;

    ppmAddressSpaceHandle mmio, io;

    XilinxPCIERoot root;

    Uns32 intr;
    Uns32 intr_mask;
    XilinxPCIEInt intr_fifo[16];
    unsigned int intr_fifo_r, intr_fifo_w;
    Uns32 rpscr;
} XilinxPCIEHost;

#endif
// Xilinx PCIe Vendor-Specific Extended Capability Type 1
typedef struct XilinxVsec1CapS {
    PCIeVsecHeader  hdr;                        // 0-7
    Uns32           bridgeInfo;                 // 8-B
    Uns32           bridgeStatusControl;        // C-F
    Uns32           interruptDecode;            // 10-13
    Uns32           interruptMask;              // 14-17
    Uns32           busLocation;                // 18-1B
    Uns32           phyStatusControl;           // 1C-1F
    Uns32           rootPortStatusControl;      // 20-23
    Uns32           rootPortMSIBase1;           // 24-27
    Uns32           rootPortMSIBase2;           // 28-2B
    Uns32           rootPortErrorFIFORead;      // 2C-2F
    Uns32           rootPortInterruptFIFORead1; // 30-33
    Uns32           rootPortInterruptFIFORead2; // 34-37
} XilinxVsec1Cap, *XilinxVsec1CapP, **XilinxVsec1CapPP;

// Xilinx PCIe Vendor-Specific Extended Capability Type 2
typedef struct XilinxVsec2CapS {
    PCIeVsecHeader  hdr;                        // 0-7
    Uns32           axiBar2PCIeBar0U;           // 8-B
    Uns32           axiBar2PCIeBar0L;           // C-F
    Uns32           axiBar2PCIeBar1U;           // 10-13
    Uns32           axiBar2PCIeBar1L;           // 14-17
    Uns32           axiBar2PCIeBar2U;           // 18-1B
    Uns32           axiBar2PCIeBar2L;           // 1C-1F
    Uns32           axiBar2PCIeBar3U;           // 20-23
    Uns32           axiBar2PCIeBar3L;           // 24-27
    Uns32           axiBar2PCIeBar4U;           // 28-2B
    Uns32           axiBar2PCIeBar4L;           // 2C-2F
    Uns32           axiBar2PCIeBar5U;           // 30-33
    Uns32           axiBar2PCIeBar5L;           // 34-37
} XilinxVsec2Cap, *XilinxVsec2CapP, **XilinxVsec2CapPP;

// Xilinx AXI to PCIe Configuration
typedef struct XilinxAXI2PCIeConfS {
    PCIconfigType1Header    type1;              // 00-3F
    PCIpowerCap             power;              // 40-47
    PCImsiCap               msi;                // 48-5F
    PCIeCap                 pcie;               // 60-9B
    union {                                     // 9C-FF
        Uns32 words [25];
        Uns16 halves[25*2];
        Uns8  bytes [25*4];
    } user;
    PCIeDevSerialNumCap     serial;             // 100-107
    Uns32                   reserved0[7];       // 108-127
    XilinxVsec1Cap          vsec1;              // 128-15F
    Uns32                   reserved1[40];      // 160-1FF
    XilinxVsec2Cap          vsec2;              // 200-237
    union {
        Uns32 words [882];
        Uns16 halves[882*2];
        Uns8  bytes [882*4];
    } user1;
} XilinxAXI2PCIeConf, *XilinxAXI2PCIeConfP, **XilinxAXI2PCIeConfPP;

#endif /* XILINX_PCIE_H */
