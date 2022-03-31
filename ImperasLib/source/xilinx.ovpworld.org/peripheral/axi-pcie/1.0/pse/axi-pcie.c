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

#define PCI_EXPRESS
#include "pse.igen.h"
#include "pci.h"
#include "axi-pcie.h"
#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

#define PREFIX              "XILINX_AXI_PCIE"
#define SLAVE_PREFIX        "XILINX_AXI_PCIE_SLAVE"

#define BUS_PORT_NAME    "busPort"
#define PCI_ACKPORT_NAME "PCIackM"

#define LOCAL_SLOT   0
#define BUS_WINDOW   0x1000
#define PCIE_WINDOW  0x10000
#define CONFIG_MASK  (PCIE_WINDOW-1)

#define PCI_ACK_WINDOW  1

#ifndef NUM_MEMBERS
#define NUM_MEMBERS(_A)         (sizeof(_A)/sizeof((_A)[0]))
#endif

enum root_cfg_reg {
    /* Interrupt Decode Register */
    ROOTCFG_INTDEC              = 0x138,

    /* Interrupt Mask Register */
    ROOTCFG_INTMASK             = 0x13c,
    /* INTx Interrupt Received */
#define ROOTCFG_INTMASK_INTX    (1 << 16)
    /* MSI Interrupt Received */
#define ROOTCFG_INTMASK_MSI     (1 << 17)

    /* PHY Status/Control Register */
    ROOTCFG_PSCR                = 0x144,
    /* Link Up */
#define ROOTCFG_PSCR_LINK_UP    (1 << 11)

    /* Root Port Status/Control Register */
    ROOTCFG_RPSCR               = 0x148,
    /* Bridge Enable */
#define ROOTCFG_RPSCR_BRIDGEEN  (1 << 0)
    /* Interrupt FIFO Not Empty */
#define ROOTCFG_RPSCR_INTNEMPTY (1 << 18)
    /* Interrupt FIFO Overflow */
#define ROOTCFG_RPSCR_INTOVF    (1 << 19)

    /* Root Port Interrupt FIFO Read Register 1 */
    ROOTCFG_RPIFR1              = 0x158,
#define ROOTCFG_RPIFR1_INT_LANE_SHIFT   27
#define ROOTCFG_RPIFR1_INT_ASSERT_SHIFT 29
#define ROOTCFG_RPIFR1_INT_VALID_SHIFT  31
    /* Root Port Interrupt FIFO Read Register 2 */
    ROOTCFG_RPIFR2              = 0x15c,
};

#if 1 // :FIXME:
//
// netPort handle
//
static ppmNetHandle intPortHandle;

#endif
//
// PCIe ACK masterPort handle
//
static ppmExternalBusHandle pciAckBus;

// PCI Enhanced Configuration Address Mapping window
//static Uns8 pciEcamWindow[PCI_ECAM_WINDOW];
// TODO : Hacked -size 0x10000000 -> 0x1000
static Uns8 pciEcamWindow[0x1000];

static XilinxPCIEHost pcie;

//
// Master window onto PCIe config bus.
// Note that the 1st slot's worth of this window is NOT exposed to the outside
// but is initialised with the config values.
//
static ppmAddressSpaceHandle configBusHandle;

//
// Master window onto PCIe ACK bus.
//
static Uns8 pciAckWindow[PCI_ACK_WINDOW];

#if 1
static void xilinx_pcie_update_intr(XilinxPCIEHost *s, Uns32 set, Uns32 clear)
{
    int level;

    s->intr |= set;
    s->intr &= ~clear;

    if (s->intr_fifo_r != s->intr_fifo_w) {
        s->intr |= ROOTCFG_INTMASK_INTX;
    }

    level = !!(s->intr & s->intr_mask);
    ppmWriteNet(intPortHandle, level);
}

static void xilinx_pcie_queue_intr(XilinxPCIEHost *s, Uns32 fifo_reg1, Uns32 fifo_reg2)
{
    XilinxPCIEInt *intr;
    unsigned int new_w;

    bhmMessage("I", PREFIX, "%s: fifo_reg1=%d fifo_reg2=%d\n", __func__, fifo_reg1, fifo_reg2);
    new_w = (s->intr_fifo_w + 1) % NUM_MEMBERS(s->intr_fifo);
    if (new_w == s->intr_fifo_r) {
        s->rpscr |= ROOTCFG_RPSCR_INTOVF;
        return;
    }

    intr = &s->intr_fifo[s->intr_fifo_w];
    s->intr_fifo_w = new_w;

    intr->fifo_reg1 = fifo_reg1;
    intr->fifo_reg2 = fifo_reg2;

    xilinx_pcie_update_intr(s, ROOTCFG_INTMASK_INTX, 0);
}

static void xilinx_pcie_set_irq(void *opaque, int irq_num, int level)
{
#if 0 // :FIXME:
    XilinxPCIEHost *s = XILINX_PCIE_HOST(opaque);
#else
    XilinxPCIEHost *s = (XilinxPCIEHost*)opaque;
#endif

    bhmMessage("I", PREFIX, "%s: irq_num=%d level=%d\n", __func__, irq_num, level);
    xilinx_pcie_queue_intr(s,
       (irq_num << ROOTCFG_RPIFR1_INT_LANE_SHIFT) |
           (level << ROOTCFG_RPIFR1_INT_ASSERT_SHIFT) |
           (1 << ROOTCFG_RPIFR1_INT_VALID_SHIFT),
       0);
}

#define HANDLE_INT(NAME, NUM) \
    static PPM_NET_CB(signalInt##NAME) { \
        bhmMessage("I", PREFIX, "%s: irq_num=%d level=%d\n", __func__, NUM, (Uns32)value); \
        xilinx_pcie_set_irq(userData, NUM, value); \
    }

HANDLE_INT(A, 0)
HANDLE_INT(B, 1)
HANDLE_INT(C, 2)
HANDLE_INT(D, 3)
#endif

//
// Connect net ports
//
void netPortConnections(void) {
    intPortHandle = handles.intOut;

    ppmInstallNetCallback(handles.intA, signalIntA, (void*)&pcie);
    ppmInstallNetCallback(handles.intB, signalIntB, (void*)&pcie);
    ppmInstallNetCallback(handles.intC, signalIntC, (void*)&pcie);
    ppmInstallNetCallback(handles.intD, signalIntD, (void*)&pcie);
}

PPM_WRITE_CB(writeEcam) {
    Uns32 addr2 = (Uns8*) addr - pciEcamWindow;

    const char * msgType[4] = { "I", "I", "E", "I" };
    const char * fmt [2][4] = {
        {   "Write " PCI_TYPE_STR " config bus:0x%04x <= 0x%02x",
            "Write " PCI_TYPE_STR " config bus:0x%04x <= 0x%04x",
            "Write " PCI_TYPE_STR " config bus:0x%04x <= 0x%08x (unsupported tribyte)",
            "Write " PCI_TYPE_STR " config bus:0x%04x <= 0x%08x"
        },
        {   "Write " PCI_TYPE_STR " config bus (%s):0x%04x => 0x%02x",
            "Write " PCI_TYPE_STR " config bus (%s):0x%04x => 0x%04x",
            "Write " PCI_TYPE_STR " config bus (%s):0x%04x => 0x%08x (unsupported tribyte)",
            "Write " PCI_TYPE_STR " config bus (%s):0x%04x => 0x%08x"
        }
    };

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(msgType[bytes - 1], PREFIX, fmt[0][bytes - 1], addr2, data);
    }

    // this write is mapped out onto the PCIe config bus
    //*(Uns32*) (pciConfigWindow + addr2) = data;
    Bool success = ppmTryWriteAddressSpace(configBusHandle, addr2, bytes);

    if(success) {
        ppmWriteAddressSpace(configBusHandle, addr2, bytes, &data);
    }

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(msgType[bytes - 1], PREFIX, fmt[1][bytes - 1], success ? "ok" : "no device", addr2, data);
    }
}

PPM_READ_CB(readEcam) {
    Uns32 addr2 = (Uns8*) addr - pciEcamWindow;

    const char * msgType[4] = { "I", "I", "E", "I" };
    const char * fmt    [4] = {
        "Read " PCI_TYPE_STR " config bus (%s,%s):0x%04x => 0x%02x",
        "Read " PCI_TYPE_STR " config bus (%s,%s):0x%04x => 0x%04x",
        "Read " PCI_TYPE_STR " config bus (%s,%s):0x%04x => 0x%08x (tribyte)",
        "Read " PCI_TYPE_STR " config bus (%s,%s):0x%04x => 0x%08x"
    };

    // this read is mapped out onto the PCIe config bus
    Uns32 data     = -1;
    Bool  mapped   = ppmTryReadAddressSpace(configBusHandle, addr2, bytes);
    Bool  complete = False;

    if(mapped) {
        complete = ppmReadAddressSpace(configBusHandle, addr2, bytes, &data);
    } else {
        data = 0xffffffff;
    }

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(msgType[bytes - 1], PREFIX, fmt[bytes - 1],
                mapped ? "mapped" : "unmapped", complete ? "complete" : "incomplete", addr2, data);
    }

    return data;
}

//
// Install a catcher for all empty PCIe configuration slots.
//
static void installPCIeCatchAll(void) {
}

static const char *vsec1RegDesc[0x38] = {
    [0x00] = "VSEC1 ECap ID",                           // 0
    [0x02] = "VSEC1 ECap Version/Next Cap Pointer",     // 2
    [0x03] = "VSEC1 Next Cap Pointer",                  // 2-3
    [0x04] = "VSEC1 Vendor ID",                         // 4-5
    [0x06] = "VSEC1 Version/Length",                    // 6
    [0x07] = "VSEC1 Length",                            // 6-7
    [0x08] = "VSEC1 Bridge Info",                       // 8
    [0x0C] = "VSEC1 Bridge Status and Control",         // C
    [0x10] = "VSEC1 Interrupt Decode",                  // 10
    [0x14] = "VSEC1 Interrupt Mask",                    // 14
    [0x18] = "VSEC1 Bus Location",                      // 18
    [0x1C] = "VSEC1 Phy Status and Control",            // 1C
    [0x20] = "VSEC1 Root Port Status and Control",      // 20
    [0x24] = "VSEC1 Root Port MSI Base 1",              // 24
    [0x28] = "VSEC1 Root Port MSI Base 2",              // 28
    [0x2C] = "VSEC1 Root Port Error FIFO Read",         // 2C
    [0x30] = "VSEC1 Root Port Interrupt FIFO Read 1",   // 30
    [0x34] = "VSEC1 Root Port Interrupt FIFO Read 2",   // 34
};

static const PCIuserRegDesc pcieVsec1RegDesc = {
    .desc = { .str = vsec1RegDesc },
    .type = PCI_USER_REG_DESC_STRING,
};

static const char *vsec2RegDesc[0x38] = {
    [0x00] = "VSEC2 ECap ID",                       // 0
    [0x02] = "VSEC2 ECap Version/Next Cap Pointer", // 2
    [0x03] = "VSEC2 Next Cap Pointer",              // 2-3
    [0x04] = "VSEC2 Vendor ID",                     // 4-5
    [0x06] = "VSEC2 Version/Length",                // 6
    [0x07] = "VSEC2 Length",                        // 6-7
    [0x08] = "VSEC2 AXI BAR to PCIe BAR 0 Upper",   // 8
    [0x0C] = "VSEC2 AXI BAR to PCIe BAR 0 Lower",   // C
    [0x10] = "VSEC2 AXI BAR to PCIe BAR 1 Upper",   // 10
    [0x14] = "VSEC2 AXI BAR to PCIe BAR 1 Lower",   // 14
    [0x18] = "VSEC2 AXI BAR to PCIe BAR 2 Upper",   // 18
    [0x1C] = "VSEC2 AXI BAR to PCIe BAR 2 Lower",   // 1C
    [0x20] = "VSEC2 AXI BAR to PCIe BAR 3 Upper",   // 20
    [0x24] = "VSEC2 AXI BAR to PCIe BAR 3 Lower",   // 24
    [0x28] = "VSEC2 AXI BAR to PCIe BAR 4 Upper",   // 28
    [0x2C] = "VSEC2 AXI BAR to PCIe BAR 4 Lower",   // 2C
    [0x30] = "VSEC2 AXI BAR to PCIe BAR 5 Upper",   // 30
    [0x34] = "VSEC2 AXI BAR to PCIe BAR 5 Lower",   // 34
};

static const PCIuserRegDesc pcieVsec2RegDesc = {
    .desc = { .str = vsec2RegDesc },
    .type = PCI_USER_REG_DESC_STRING,
};

//
///////////////////////////////// LOCAL PCIe CONFIG ///////////////////////////////////////
//
// As well as being the PCIe configuration bus master, this device occupies one slave.
//
void localPCIeInit(void) {

#define POWER_CAP_OFFSET        0x40
#define MSI_CAP_OFFSET          0x48
#define PCIE_CAP_OFFSET         0x60
#define SERIAL_ECAP_OFFSET      0x100
#define VSEC1_OFFSET            0x128
#define VSEC2_OFFSET            0x200

    XilinxAXI2PCIeConfP conf = (XilinxAXI2PCIeConfP)&pciConfig;

    conf->type1.vendorID = 0x10ee;
    conf->type1.deviceID = 0x7021;
    conf->type1.command = 0x0000;
#if 0
    conf->type1.status = 0x0010;
#else
    conf->type1.status = 0x00b0;
#endif
    conf->type1.revisionID = 0x0;
    conf->type1.classCode[0] = 0x00;
    conf->type1.classCode[1] = 0x04;
    conf->type1.classCode[2] = 0x06;

    conf->type1.headerType = 0x01;

    // Type 1: I/O Base (Uns8); I/O Limit (Uns8); Secondary Status (Uns16)
#if 0
    conf->type1.ioBase = 0x01;
    conf->type1.ioLimit = 0x01;
    conf->type1.secondaryStatus = 0x0000;
    conf->type1.interruptLine = 0xff;
#else
    conf->type1.ioBase = 0x00;
    conf->type1.ioLimit = 0x00;
    conf->type1.secondaryStatus = 0x00a0;
    conf->type1.prefetchMemoryBase = 0x0001;
    conf->type1.prefetchMemoryLimit = 0x0001;
    conf->type1.ioBaseUpper16Bits = 0x0080;
#endif

    conf->type1.capPointer = POWER_CAP_OFFSET;

#if 0
#define ALIGN_ASSERT(M, O) \
    do { \
        unsigned int offset = (unsigned int)&(((XilinxAXI2PCIeConfP)0)->M); \
        if (offset != (O)) { \
            bhmMessage("F", PREFIX, "%s should be %#x not %#x", #M, (O), offset); \
        } else { \
            bhmMessage("I", PREFIX, "%s is %#x which matches %#x", #M, offset, (O)); \
        } \
    } while (0)
#else
#define ALIGN_ASSERT(M, O)
#endif

    // PCI Power Management Capability (@ 0x40)
    ALIGN_ASSERT(power, POWER_CAP_OFFSET);
    pciInstallPowerMgmtCap(POWER_CAP_OFFSET, NULL, NULL);
    conf->power.hdr.nextCapPointer = MSI_CAP_OFFSET;
    conf->power.capRegister = 0x0023;
    conf->power.status = 0x0008;

    // MSI Capability (@ 0x48)
    ALIGN_ASSERT(msi, MSI_CAP_OFFSET);
    pciInstallMsiCap(MSI_CAP_OFFSET, True, True, 0, NULL, NULL);
    conf->msi.hdr.nextCapPointer = PCIE_CAP_OFFSET;

    // PCIe Capability (@ 0x60)
    ALIGN_ASSERT(pcie, PCIE_CAP_OFFSET);
    pciInstallPcieCap(PCIE_CAP_OFFSET, NULL, NULL);

    // Cap Version 2; Root Port of PCI Express Root Complex
    conf->pcie.capRegister = 0x42;

    // Max payload 256 B; No Phantom Functions; 8-bit Tag Field; Role-Based Error Reporting
    conf->pcie.deviceCap = 0x00008029;

    // Enable Relaxed Ordering; 128 B Max Payload Size; Enable No Snoop; 256 B Max Read Request Size
    conf->pcie.deviceControl = 0x2810;

    // 2.5 GT/s Link; Max Link Width x1; L0x Entry Support (ASPM); > 4 us L0s Exit Latency; > 64 us L1 Exit Latency; Data Link Layer Link Active Reporting Capable
    conf->pcie.linkCap = 0x0013f411;

    // 2.5 GT/s PCIe Link; x1 Negotiated Link Width; Slot Clock Configuration; Data Link Layer Link Active
    conf->pcie.linkStatus = 0x3011;

    // Card Present in slot
    conf->pcie.slotStatus = 0x0040;

    // 2.5 GT/s Target Link Speed
    conf->pcie.linkControl2 = 0x0001;

    // -6 dB Current De-emphasis Level
    conf->pcie.linkStatus2 = 0x0001;

    // PCIe Device Serial Number Extended Capability (@ 0x100)
    ALIGN_ASSERT(serial, SERIAL_ECAP_OFFSET);
    conf->serial.hdr.capID = PCIE_DEV_SERIAL_NUM_ID;
    conf->serial.hdr.capVersion = 1;
    conf->serial.hdr.nextCapOffset = VSEC1_OFFSET;

    // PCIe Vendor-Specific Extended Capability 1 (@ 0x128)
    ALIGN_ASSERT(vsec1, VSEC1_OFFSET);
    pciInstallPcieVsec(VSEC1_OFFSET, 1, 1, 0, 0x38, NULL, NULL, &pcieVsec1RegDesc);
    conf->vsec1.hdr.hdr.nextCapOffset = VSEC2_OFFSET;

    conf->vsec1.bridgeInfo = 0x00070002;
    conf->vsec1.phyStatusControl = 0x000008b0;

    // PCIe Vendor-Specific Extended Capability 2 (@ 0x200)
    ALIGN_ASSERT(vsec2, VSEC2_OFFSET);
    pciInstallPcieVsec(VSEC2_OFFSET, 1, 2, 0, 0x38, NULL, NULL, &pcieVsec2RegDesc);

    conf->vsec2.axiBar2PCIeBar0L = 0x16000000;

#if 0
    // Debug dump to verify versus hardware dump
    int offset;
    for (offset = 0; offset < 0x300; offset += 0x10) {
        bhmMessage("I", PREFIX, "0x%08x %08x %08x %08x %08x", 0xb4000000 + offset, CONFIG_ACCESS_32((offset + 0x00)), CONFIG_ACCESS_32((offset + 0x04)), CONFIG_ACCESS_32((offset + 0x08)), CONFIG_ACCESS_32((offset + 0x0c)));
    }

#endif
    pciConnectConfigSlavePort(SLAVE_PREFIX, NULL);
}

//
/////////////////////////////// Main for Xilinx PCIe /////////////////////////////////////
//
PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Starting");
    }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Open PCI ECAM Window %.1f MB\n", (double)(sizeof(pciEcamWindow)/(1024*1024)));
    }
    ppmOpenSlaveBusPort("ecam", pciEcamWindow, sizeof(pciEcamWindow));
    ppmInstallReadCallback(readEcam, NULL, pciEcamWindow, sizeof(pciEcamWindow));
    ppmInstallWriteCallback(writeEcam, NULL, pciEcamWindow, sizeof(pciEcamWindow));

    if (!(configBusHandle = handles.PCIconfigM)) {
        bhmMessage("F", PREFIX, "Missing PCI Express config bus master port");
    }
    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Connected to PCI Express config bus, as bus master");
    }

    // master port to connect the PCIe ACK cycle
    pciAckBus = ppmOpenMasterBusPort(PCI_ACKPORT_NAME, pciAckWindow,
            sizeof(pciAckWindow), 0);
    if (PSE_DIAG_MEDIUM) {
        bhmMessage("W", PREFIX,
        "%sconnecting PCI Express ACK bus master port", pciAckBus ? "" : "Not ");
    }

    installPCIeCatchAll();
    netPortConnections();
    localPCIeInit();

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Construction Complete");
    }
    bhmEventHandle waitStart = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(waitStart);

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Running\n");
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", PREFIX "_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", PREFIX "_RSNI", "Model does not implement save/restore");
}
