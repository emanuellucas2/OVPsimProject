/*
 * QEMU System Controller.
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

/*
 * The GT64120 has several functions:
 * It maps part of the main address space onto a PCI bus memory address space
 * It maps part of the main address space onto a PCI bus IO address space
 * It maps part of the main address space onto local registers
 *     Two of these registers form the address and data for access to a PCI configuration bus
 * Using these registers, it is the PCI configuration bus master
 * It implements the first slot (slot-0, function-0) on the PCI configuration bus.
 * It handles PCI configuration bus accesses to empty slots.
 * Another register gives access to the interrupt acknowledge register of an i8259, if connected.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pse.igen.h"

#include "pci.h"

#include "sysControl.h"

#define PREFIX           "GT64120"
#define SLAVE_PREFIX     "GT64120_SLAVE"

// diagnostic bits. Please keep iGen doc up to date.
#define DIAG_PCI_SLAVE           0x03
#define DIAG_PCI_CONFIG_MASTER   0x04
#define DIAG_PCI_EMPTY           0x08
#define DIAG_INT_ACK             0x10
#define DIAG_MAIN_BUS            0x20
#define DIAG_INFO                0x40

#define BUS_PORT_NAME    "busPort"
#define PCI_ACKPORT_NAME "PCIackM"

#define LOCAL_SLOT   0
#define BUS_WINDOW   0x1000
#define PCI_WINDOW   0x10000
#define CONFIG_MASK  (PCI_WINDOW-1)

#define PCI_ACK_WINDOW   1

//
// netPort handle
//
static ppmNetHandle intPortHandle;
//
// PCI ACK masterPort handle
//
static ppmExternalBusHandle pciAckBus;

typedef struct GT64120State {
    Uns32 regs[GT_REGS];
    Uns32 pci_config_reg;

    Uns32 PCI0IO_start;
    Uns32 PCI0IO_length;

    Uns32 ISD_start;
    Uns32 ISD_length;

} GT64120State;

// create state
static GT64120State s;

static Uns8 sysCtrlWindow[BUS_WINDOW];

//
// Master window onto PCI config bus.
// Note that the 1st slot's worth of this window is NOT exposed to the outside
// but is initialised with the config values.
//
//static Uns8 pciConfigWindow[PCI_WINDOW];
static ppmAddressSpaceHandle configBusHandle;

//
// Master window onto PCI ACK bus.
//
static Uns8 pciAckWindow[PCI_ACK_WINDOW];

static void gt64120_isd_mapping(GT64120State *s);
static void gt64120_pci_mapping(GT64120State *s);
static void gt64120_sdram_mapping(GT64120State *s);

//
// Nothing writes to this yet
//
void writeInt(Uns32 v) {
    if (intPortHandle) {
        ppmWriteNet(intPortHandle, v);
    }
}

static void configBusWrite(Uns32 byte, Uns32 bytes, Uns32 val) {
    if (s.pci_config_reg & (1u << 31)) {
        Uns32 address = (s.pci_config_reg & CONFIG_MASK) + byte;
        if (bytes != 4) {
            bhmMessage("F", PREFIX, "Only 4-byte access supported");
        }
        if (PSE_DIAG_LOW & DIAG_PCI_CONFIG_MASTER)
            bhmMessage("I", PREFIX, "Write PCI config bus:0x%04x <= 0x%08x",
                    address, val);

        // this write is mapped out onto the PCI config bus
        //*(Uns32*) (pciConfigWindow + address) = val;
        Bool success = ppmTryWriteAddressSpace(configBusHandle, address, bytes);
        if(success) {
            ppmWriteAddressSpace(configBusHandle,address,bytes,&val);
        }
        if (PSE_DIAG_LOW & DIAG_PCI_CONFIG_MASTER)
            bhmMessage("I", PREFIX, "Write PCI config bus (%s):0x%04x => 0x%08x",
                    success ? "ok" : "no device", address, val);
    } else {
        bhmMessage("W", PREFIX, "configBusWrite out of range 0x%x",
                s.pci_config_reg);
    }
}

static Uns32 configBusRead(Uns32 byte, Uns32 bytes) {
    if (s.pci_config_reg & (1u << 31)) {
        Uns32 address = (s.pci_config_reg & CONFIG_MASK) + byte;
        if (bytes != 4) {
            bhmMessage("F", PREFIX, "Only 4-byte access supported");
        }
        // this read is mapped out onto the PCI config bus
        Uns32 val = -1;
        Bool  mapped   = ppmTryReadAddressSpace(configBusHandle, address, bytes);
        Bool  complete = False;

        if(mapped) {
            complete = ppmReadAddressSpace(configBusHandle,address,bytes,&val);
        } else {
            val = 0xffffffff;
        }
        if (PSE_DIAG_LOW & DIAG_PCI_CONFIG_MASTER)
            bhmMessage("I", PREFIX, "Read PCI config bus (%s,%s):0x%04x => 0x%08x",
                    mapped ? "mapped" : "unmapped", complete ? "complete" : "incomplete", address, val);
        return val;
    } else {
        bhmMessage("W", PREFIX, "configBusRead out of range 0x%x", s.pci_config_reg);
        return 0xffffffff;
    }
}

static PPM_WRITE_CB(writeRegs) {
    Bool  said  = False;
    Uns32 addr2 = (Uns8*) addr - sysCtrlWindow;
    Uns32 byte = PTR_TO_UNS32(addr) & 3;
    Uns32 dbgAddr = (s.regs[GT_ISD] << 21) + addr2;

    (void)said;    // Not used for some reason, so need this to avoid compiler warning

    if (!(s.regs[GT_CPU] & 0x1000)) {
        if (PSE_DIAG_LOW & DIAG_INFO)
            bhmMessage("I", PREFIX, "CPU Interface Byte swapping");
    }

    Uns32 saddr = (addr2 & 0xfff) >> 2;
    if (BHM_DIAG_LOW) {
        if (!regDesc[saddr]) bhmMessage("W", "REG_DECODE", "Cannot decode Register Name addr=%x\n", addr2);
        bhmMessage("I", PREFIX, "Register Write [%s] *0x%08x(0x%x)=0x%08x(%u)\n", regDesc[saddr], dbgAddr, addr2, data, bytes);
    }

    switch (saddr) {

    //
    // Newly added for yamon
    //
    case GT_SCS10LD:
    case GT_SCS32LD:
        data &= 0x7fff;
        s.regs[saddr] = data;
        gt64120_sdram_mapping(&s);
        break;
    case GT_SCS10HD:
    case GT_SCS32HD:
        data &= 0x7f;
        s.regs[saddr] = data;
        gt64120_sdram_mapping(&s);
        break;

    /* CPU Configuration */
    case GT_CPU:
        s.regs[GT_CPU] = data;
        break;

    case GT_MULTI:
        /* Read-only register as only one GT64xxx is present on the CPU bus */
        break;

        /* CPU Address Decode */
    case GT_PCI0IOLD:
        s.regs[GT_PCI0IOLD] = data & 0x00007fff;
        s.regs[GT_PCI0IOREMAP] = data & 0x000007ff;
        gt64120_pci_mapping(&s);
        said = True;
        break;
    case GT_PCI0M0LD:
        s.regs[GT_PCI0M0LD] = data & 0x00007fff;
        s.regs[GT_PCI0M0REMAP] = data & 0x000007ff;
        break;
    case GT_PCI0M1LD:
        s.regs[GT_PCI0M1LD] = data & 0x00007fff;
        s.regs[GT_PCI0M1REMAP] = data & 0x000007ff;
        break;
    case GT_PCI1IOLD:
        s.regs[GT_PCI1IOLD] = data & 0x00007fff;
        s.regs[GT_PCI1IOREMAP] = data & 0x000007ff;
        break;
    case GT_PCI1M0LD:
        s.regs[GT_PCI1M0LD] = data & 0x00007fff;
        s.regs[GT_PCI1M0REMAP] = data & 0x000007ff;
        break;
    case GT_PCI1M1LD:
        s.regs[GT_PCI1M1LD] = data & 0x00007fff;
        s.regs[GT_PCI1M1REMAP] = data & 0x000007ff;
        break;
    case GT_PCI0IOHD:
        s.regs[saddr] = data & 0x0000007f;
        gt64120_pci_mapping(&s);
        break;
    case GT_PCI0M0HD:
    case GT_PCI0M1HD:
    case GT_PCI1IOHD:
    case GT_PCI1M0HD:
    case GT_PCI1M1HD:
        s.regs[saddr] = data & 0x0000007f;
        break;
    case GT_ISD:
        s.regs[saddr] = data & 0x00007fff;
        gt64120_isd_mapping(&s);
        said = True;
        break;

    case GT_PCI0IOREMAP:
    case GT_PCI0M0REMAP:
    case GT_PCI0M1REMAP:
    case GT_PCI1IOREMAP:
    case GT_PCI1M0REMAP:
    case GT_PCI1M1REMAP:
        s.regs[saddr] = data & 0x000007ff;
        break;

        /* CPU Error Report */
    case GT_CPUERR_ADDRLO:
    case GT_CPUERR_ADDRHI:
    case GT_CPUERR_DATALO:
    case GT_CPUERR_DATAHI:
    case GT_CPUERR_PARITY:
        /* Read-only registers, do nothing */
        break;

        /* CPU Sync Barrier */
    case GT_PCI0SYNC:
    case GT_PCI1SYNC:
        /* Read-only registers, do nothing */
        break;

        /* SDRAM and Device Address Decode */
    case GT_SCS0LD:
    case GT_SCS0HD:
    case GT_SCS1LD:
    case GT_SCS1HD:
    case GT_SCS2LD:
    case GT_SCS2HD:
    case GT_SCS3LD:
    case GT_SCS3HD:
    case GT_CS0LD:
    case GT_CS0HD:
    case GT_CS1LD:
    case GT_CS1HD:
    case GT_CS2LD:
    case GT_CS2HD:
    case GT_CS3LD:
    case GT_CS3HD:
    case GT_BOOTLD:
    case GT_BOOTHD:
        s.regs[saddr] = data;
        gt64120_sdram_mapping(&s);
        break;

    case GT_ADERR:
        /* SDRAM Configuration */
    case GT_SDRAM_CFG:
    case GT_SDRAM_OPMODE:
    case GT_SDRAM_BM:
    case GT_SDRAM_ADDRDEC:
        /* Accept and ignore SDRAM interleave configuration */
        s.regs[saddr] = data;
        break;

        /* Device Parameters */
    case GT_DEV_B0:
    case GT_DEV_B1:
    case GT_DEV_B2:
    case GT_DEV_B3:
    case GT_DEV_BOOT:
        /* Not implemented */
        bhmMessage("W", PREFIX, "Unimplemented device register offset 0x%x\n",
                addr2);
        said = True;
        break;

        /* ECC */
    case GT_ECC_ERRDATALO:
    case GT_ECC_ERRDATAHI:
    case GT_ECC_MEM:
    case GT_ECC_CALC:
    case GT_ECC_ERRADDR:
        /* Read-only registers, do nothing */
        break;

        /* DMA Record */
    case GT_DMA0_CNT:
    case GT_DMA1_CNT:
    case GT_DMA2_CNT:
    case GT_DMA3_CNT:
    case GT_DMA0_SA:
    case GT_DMA1_SA:
    case GT_DMA2_SA:
    case GT_DMA3_SA:
    case GT_DMA0_DA:
    case GT_DMA1_DA:
    case GT_DMA2_DA:
    case GT_DMA3_DA:
    case GT_DMA0_NEXT:
    case GT_DMA1_NEXT:
    case GT_DMA2_NEXT:
    case GT_DMA3_NEXT:
    case GT_DMA0_CUR:
    case GT_DMA1_CUR:
    case GT_DMA2_CUR:
    case GT_DMA3_CUR:
        /* Not implemented */
        bhmMessage("W", PREFIX,"Unimplemented DMA register offset 0x%x\n", addr2);
        said = True;
        break;

        /* DMA Channel Control */
    case GT_DMA0_CTRL:
    case GT_DMA1_CTRL:
    case GT_DMA2_CTRL:
    case GT_DMA3_CTRL:
        /* Not implemented */
        bhmMessage("W", PREFIX,"Unimplemented DMA register offset 0x%x\n", addr2);
        said = True;
        break;

        /* DMA Arbiter */
    case GT_DMA_ARB:
        /* Not implemented */
        bhmMessage("W", PREFIX,"Unimplemented DMA register offset 0x%x\n", addr2);
        said = True;
        break;

        /* Timer/Counter */
    case GT_TC0:
    case GT_TC1:
    case GT_TC2:
    case GT_TC3:
    case GT_TC_CONTROL:
        /* Not implemented */
        bhmMessage("W", PREFIX,"Unimplemented timer register offset 0x%x\n",
                addr2);
        said = True;
        break;

        /* PCI Internal */
    case GT_PCI0_CMD:
    case GT_PCI1_CMD:
        if (PSE_DIAG_LOW & DIAG_INFO)
            if ((data & 0x00010001) != (s.regs[saddr] & 0x00010001)) {
                bhmMessage("I", PREFIX,"Changing PCI Endian Swap Support");
            }
        s.regs[saddr] = data & 0x0401fc0f;
        break;

    case GT_PCI0_TOR:
    case GT_PCI0_BS_SCS10:
    case GT_PCI0_BS_SCS32:
    case GT_PCI0_BS_CS20:
    case GT_PCI0_BS_CS3BT:
    case GT_PCI1_IACK:
    case GT_PCI0_IACK:
    case GT_PCI0_BARE:
    case GT_PCI0_PREFMBR:
    case GT_PCI0_SCS10_BAR:
    case GT_PCI0_SCS32_BAR:
    case GT_PCI0_CS20_BAR:
    case GT_PCI0_CS3BT_BAR:
    case GT_PCI0_SSCS10_BAR:
    case GT_PCI0_SSCS32_BAR:
    case GT_PCI0_SCS3BT_BAR:
    case GT_PCI1_TOR:
    case GT_PCI1_BS_SCS10:
    case GT_PCI1_BS_SCS32:
    case GT_PCI1_BS_CS20:
    case GT_PCI1_BS_CS3BT:
    case GT_PCI1_BARE:
    case GT_PCI1_PREFMBR:
    case GT_PCI1_SCS10_BAR:
    case GT_PCI1_SCS32_BAR:
    case GT_PCI1_CS20_BAR:
    case GT_PCI1_CS3BT_BAR:
    case GT_PCI1_SSCS10_BAR:
    case GT_PCI1_SSCS32_BAR:
    case GT_PCI1_SCS3BT_BAR:
    case GT_PCI1_CFGADDR:
    case GT_PCI1_CFGDATA:
        /* not implemented */
        break;
    case GT_PCI0_CFGADDR:
        s.pci_config_reg = data & 0x80fffffc;
        said = True;
        break;

    case GT_PCI0_CFGDATA:
        configBusWrite(byte, bytes, data);
        said = True;
        break;

        /* Interrupts */
    case GT_INTRCAUSE:
        /* not really implemented */
        s.regs[saddr] = ~(~(s.regs[saddr]) | ~(data & 0xfffffffe));
        s.regs[saddr] |= !!(s.regs[saddr] & 0xfffffffe);
        if (PSE_DIAG_LOW & DIAG_MAIN_BUS)
            bhmMessage("I", PREFIX, "Write INTRCAUSE %x\n", data);
        said = True;
        break;
    case GT_INTRMASK:
        s.regs[saddr] = data & 0x3c3ffffe;
        if (PSE_DIAG_LOW & DIAG_MAIN_BUS)
            bhmMessage("I", PREFIX, "Write INTRMASK %x\n", data);
        said = True;
        break;
    case GT_PCI0_ICMASK:
        s.regs[saddr] = data & 0x03fffffe;
        if (PSE_DIAG_LOW & DIAG_MAIN_BUS)
            bhmMessage("I", PREFIX, "Write ICMASK %x\n", data);
        said = True;
        break;
    case GT_PCI0_SERR0MASK:
        s.regs[saddr] = data & 0x0000003f;
        if (PSE_DIAG_LOW & DIAG_MAIN_BUS)
            bhmMessage("I", PREFIX, "Write SERR0MASK %x\n", data);
        said = True;
        break;

        /* Reserved when only PCI_0 is configured. */
    case GT_HINTRCAUSE:
    case GT_CPU_INTSEL:
    case GT_PCI0_INTSEL:
    case GT_HINTRMASK:
    case GT_PCI0_HICMASK:
    case GT_PCI1_SERR1MASK:
        /* not implemented */
        break;

        /* SDRAM Parameters */
    case GT_SDRAM_B0:
    case GT_SDRAM_B1:
    case GT_SDRAM_B2:
    case GT_SDRAM_B3:
        /* We don't simulate electrical parameters of the SDRAM.
         Accept, but ignore the dataues. */
        s.regs[saddr] = data;
        break;

    default:
        bhmMessage("W", PREFIX,"Bad Write register offset 0x%x = 0x%x\n",
                (int) addr2, data);
        said = True;
        break;
    }
}

static PPM_READ_CB(readRegs) {
    Bool  said = False;
    Uns32 addr2 = (Uns8*) addr - sysCtrlWindow;
    Uns32 byte  = PTR_TO_UNS32(addr) & 3;
    Uns32 data  = 0;
    Uns32 saddr = (addr2 & 0xfff) >> 2;
    Uns32 dbgAddr = (s.regs[GT_ISD] << 21) + addr2;

    (void)said;    // Not used for some reason, so need this to avoid compiler warning

    switch (saddr) {

    /* CPU Configuration */
    case GT_MULTI:
        /* Only one GT64xxx is present on the CPU bus, return
         the initial value */
        data = s.regs[saddr];
        break;

        /* CPU Error Report */
    case GT_CPUERR_ADDRLO:
    case GT_CPUERR_ADDRHI:
    case GT_CPUERR_DATALO:
    case GT_CPUERR_DATAHI:
    case GT_CPUERR_PARITY:
        /* Emulated memory has no error, always return the initial
         values */
        data = s.regs[saddr];
        break;

        /* CPU Sync Barrier */
    case GT_PCI0SYNC:
    case GT_PCI1SYNC:
        /* Reading those register should empty all FIFO on the PCI
         bus, which are not emulated. The return value should be
         a random value that should be ignored. */
        data = 0xc000ffee;
        break;

        /* ECC */
    case GT_ECC_ERRDATALO:
    case GT_ECC_ERRDATAHI:
    case GT_ECC_MEM:
    case GT_ECC_CALC:
    case GT_ECC_ERRADDR:
        /* Emulated memory has no error, always return the initial
         values */
        data = s.regs[saddr];
        break;

    case GT_CPU:
    case GT_SCS10LD:
    case GT_SCS10HD:
    case GT_SCS32LD:
    case GT_SCS32HD:
    case GT_CS20LD:
    case GT_CS20HD:
    case GT_CS3BOOTLD:
    case GT_CS3BOOTHD:
    case GT_SCS10AR:
    case GT_SCS32AR:
    case GT_CS20R:
    case GT_CS3BOOTR:
    case GT_PCI0IOLD:
    case GT_PCI0M0LD:
    case GT_PCI0M1LD:
    case GT_PCI1IOLD:
    case GT_PCI1M0LD:
    case GT_PCI1M1LD:
    case GT_PCI0IOHD:
    case GT_PCI0M0HD:
    case GT_PCI0M1HD:
    case GT_PCI1IOHD:
    case GT_PCI1M0HD:
    case GT_PCI1M1HD:
    case GT_PCI0IOREMAP:
    case GT_PCI0M0REMAP:
    case GT_PCI0M1REMAP:
    case GT_PCI1IOREMAP:
    case GT_PCI1M0REMAP:
    case GT_PCI1M1REMAP:
    case GT_ISD:
        data = s.regs[saddr];
        break;
    case GT_PCI0_IACK:
        /* Read the IRQ number */
        if (!pciAckBus) {
            if (PSE_DIAG_LOW & DIAG_INT_ACK)
                bhmMessage("W",
                        PREFIX,"No PCI ACK bus connected cannot perform ACK\n");
        } else {
            data = *(Uns8*) (pciAckWindow);
            if (PSE_DIAG_LOW & DIAG_INT_ACK)
                bhmMessage("I", PREFIX,"PCI ACK returns %d\n", data);
        }
        said = True;
        break;

        /* SDRAM and Device Address Decode */
    case GT_SCS0LD:
    case GT_SCS0HD:
    case GT_SCS1LD:
    case GT_SCS1HD:
    case GT_SCS2LD:
    case GT_SCS2HD:
    case GT_SCS3LD:
    case GT_SCS3HD:
    case GT_CS0LD:
    case GT_CS0HD:
    case GT_CS1LD:
    case GT_CS1HD:
    case GT_CS2LD:
    case GT_CS2HD:
    case GT_CS3LD:
    case GT_CS3HD:
    case GT_BOOTLD:
    case GT_BOOTHD:
    case GT_ADERR:
        data = s.regs[saddr];
        break;

        /* SDRAM Configuration */
    case GT_SDRAM_CFG:
    case GT_SDRAM_OPMODE:
    case GT_SDRAM_BM:
    case GT_SDRAM_ADDRDEC:
        data = s.regs[saddr];
        break;

        /* SDRAM Parameters */
    case GT_SDRAM_B0:
    case GT_SDRAM_B1:
    case GT_SDRAM_B2:
    case GT_SDRAM_B3:
        /* We don't simulate electrical parameters of the SDRAM.
         Just return the last written dataue. */
        data = s.regs[saddr];
        break;

        /* Device Parameters */
    case GT_DEV_B0:
    case GT_DEV_B1:
    case GT_DEV_B2:
    case GT_DEV_B3:
    case GT_DEV_BOOT:
        data = s.regs[saddr];
        break;

        /* DMA Record */
    case GT_DMA0_CNT:
    case GT_DMA1_CNT:
    case GT_DMA2_CNT:
    case GT_DMA3_CNT:
    case GT_DMA0_SA:
    case GT_DMA1_SA:
    case GT_DMA2_SA:
    case GT_DMA3_SA:
    case GT_DMA0_DA:
    case GT_DMA1_DA:
    case GT_DMA2_DA:
    case GT_DMA3_DA:
    case GT_DMA0_NEXT:
    case GT_DMA1_NEXT:
    case GT_DMA2_NEXT:
    case GT_DMA3_NEXT:
    case GT_DMA0_CUR:
    case GT_DMA1_CUR:
    case GT_DMA2_CUR:
    case GT_DMA3_CUR:
        data = s.regs[saddr];
        break;

        /* DMA Channel Control */
    case GT_DMA0_CTRL:
    case GT_DMA1_CTRL:
    case GT_DMA2_CTRL:
    case GT_DMA3_CTRL:
        data = s.regs[saddr];
        break;

        /* DMA Arbiter */
    case GT_DMA_ARB:
        data = s.regs[saddr];
        break;

        /* Timer/Counter */
    case GT_TC0:
    case GT_TC1:
    case GT_TC2:
    case GT_TC3:
    case GT_TC_CONTROL:
        data = s.regs[saddr];
        break;

        /* PCI Internal */
    case GT_PCI0_CFGADDR:
        data = s.pci_config_reg;
        break;
    case GT_PCI0_CFGDATA:
        data = configBusRead(byte, bytes);
        said = True;
        break;

    case GT_PCI0_CMD:
    case GT_PCI0_TOR:
    case GT_PCI0_BS_SCS10:
    case GT_PCI0_BS_SCS32:
    case GT_PCI0_BS_CS20:
    case GT_PCI0_BS_CS3BT:
    case GT_PCI1_IACK:
    case GT_PCI0_BARE:
    case GT_PCI0_PREFMBR:
    case GT_PCI0_SCS10_BAR:
    case GT_PCI0_SCS32_BAR:
    case GT_PCI0_CS20_BAR:
    case GT_PCI0_CS3BT_BAR:
    case GT_PCI0_SSCS10_BAR:
    case GT_PCI0_SSCS32_BAR:
    case GT_PCI0_SCS3BT_BAR:
    case GT_PCI1_CMD:
    case GT_PCI1_TOR:
    case GT_PCI1_BS_SCS10:
    case GT_PCI1_BS_SCS32:
    case GT_PCI1_BS_CS20:
    case GT_PCI1_BS_CS3BT:
    case GT_PCI1_BARE:
    case GT_PCI1_PREFMBR:
    case GT_PCI1_SCS10_BAR:
    case GT_PCI1_SCS32_BAR:
    case GT_PCI1_CS20_BAR:
    case GT_PCI1_CS3BT_BAR:
    case GT_PCI1_SSCS10_BAR:
    case GT_PCI1_SSCS32_BAR:
    case GT_PCI1_SCS3BT_BAR:
    case GT_PCI1_CFGADDR:
    case GT_PCI1_CFGDATA:
        data = s.regs[saddr];
        break;

        /* Interrupts */
    case GT_INTRCAUSE:
        data = s.regs[saddr];
        if (PSE_DIAG_LOW & DIAG_INT_ACK)
            bhmMessage("I", PREFIX, "Read INTRCAUSE %x\n", data);
        said = True;
        break;
    case GT_INTRMASK:
        data = s.regs[saddr];
        if (PSE_DIAG_LOW & DIAG_INT_ACK)
            bhmMessage("I", PREFIX, "Read INTRMASK %x\n", data);
        said = True;
        break;
    case GT_PCI0_ICMASK:
        data = s.regs[saddr];
        if (PSE_DIAG_LOW & DIAG_INT_ACK)
            bhmMessage("I", PREFIX, "Read ICMASK %x\n", data);
        said = True;
        break;
    case GT_PCI0_SERR0MASK:
        data = s.regs[saddr];
        if (PSE_DIAG_LOW & DIAG_INT_ACK)
            bhmMessage("I", PREFIX, "Read SERR0MASK %x\n", data);
        said = True;
        break;

        /* Reserved when only PCI_0 is configured. */
    case GT_HINTRCAUSE:
    case GT_CPU_INTSEL:
    case GT_PCI0_INTSEL:
    case GT_HINTRMASK:
    case GT_PCI0_HICMASK:
    case GT_PCI1_SERR1MASK:
        data = s.regs[saddr];
        break;

    default:
        data = s.regs[saddr];
        bhmMessage("I", PREFIX,"Bad register offset 0x%x\n", PTR_TO_UNS32(addr));
        said = True;
        break;
    }

    if (!(s.regs[GT_CPU] & 0x1000)) {
        if (PSE_DIAG_LOW & DIAG_INFO)
            bhmMessage("I", PREFIX, "Byte swapping result 0x%08x\n", data);
    }

    if (BHM_DIAG_LOW) {
        if (!regDesc[saddr]) bhmMessage("W", "REG_DECODE", "Cannot decode Register Name addr=0x%x\n", addr2);
        bhmMessage("I", PREFIX, "Register Read [%s] *0x%08x(0x%08x)=0x%08x(%u)\n", regDesc[saddr], dbgAddr, addr2, data, bytes);
    }
    return data;
}

static void gt64120_reset(void) {
    if (PSE_DIAG_LOW & DIAG_INFO)
        bhmMessage("I", PREFIX, "reset");

    /* FIXME: Malta specific hw assumptions ahead */
    /* CPU Configuration */
    if (endianBig) {
        s.regs[GT_CPU] = 0x00000000;
    } else {
        s.regs[GT_CPU] = 0x00001000;
    }
    s.regs[GT_MULTI] = 0x00000003;

    /* CPU Address decode */
    s.regs[GT_SCS10LD] = 0x00000000;
    s.regs[GT_SCS10HD] = 0x00000007;
    s.regs[GT_SCS32LD] = 0x00000008;
    s.regs[GT_SCS32HD] = 0x0000000f;
    s.regs[GT_CS20LD] = 0x000000e0;
    s.regs[GT_CS20HD] = 0x00000070;
    s.regs[GT_CS3BOOTLD] = 0x000000f8;
    s.regs[GT_CS3BOOTHD] = 0x0000007f;

    s.regs[GT_PCI0IOLD] = 0x00000080;
    s.regs[GT_PCI0IOHD] = 0x0000000f;
    s.regs[GT_PCI0M0LD] = 0x00000090;
    s.regs[GT_PCI0M0HD] = 0x0000001f;
    s.regs[GT_ISD] = 0x000000a0;
    s.regs[GT_PCI0M1LD] = 0x00000790;
    s.regs[GT_PCI0M1HD] = 0x0000001f;
    s.regs[GT_PCI1IOLD] = 0x00000100;
    s.regs[GT_PCI1IOHD] = 0x0000000f;
    s.regs[GT_PCI1M0LD] = 0x00000110;
    s.regs[GT_PCI1M0HD] = 0x0000001f;
    s.regs[GT_PCI1M1LD] = 0x00000120;
    s.regs[GT_PCI1M1HD] = 0x0000002f;

    s.regs[GT_SCS10AR] = 0x00000000;
    s.regs[GT_SCS32AR] = 0x00000008;
    s.regs[GT_CS20R] = 0x000000e0;
    s.regs[GT_CS3BOOTR] = 0x000000f8;

    s.regs[GT_PCI0IOREMAP] = 0x00000080;
    s.regs[GT_PCI0M0REMAP] = 0x00000090;
    s.regs[GT_PCI0M1REMAP] = 0x00000790;
    s.regs[GT_PCI1IOREMAP] = 0x00000100;
    s.regs[GT_PCI1M0REMAP] = 0x00000110;
    s.regs[GT_PCI1M1REMAP] = 0x00000120;

    /* CPU Error Report */
    s.regs[GT_CPUERR_ADDRLO] = 0x00000000;
    s.regs[GT_CPUERR_ADDRHI] = 0x00000000;
    s.regs[GT_CPUERR_DATALO] = 0xffffffff;
    s.regs[GT_CPUERR_DATAHI] = 0xffffffff;
    s.regs[GT_CPUERR_PARITY] = 0x000000ff;

    /* CPU Sync Barrier */
    s.regs[GT_PCI0SYNC] = 0x00000000;
    s.regs[GT_PCI1SYNC] = 0x00000000;

    /* SDRAM and Device Address Decode */
    s.regs[GT_SCS0LD] = 0x00000000;
    s.regs[GT_SCS0HD] = 0x00000007;
    s.regs[GT_SCS1LD] = 0x00000008;
    s.regs[GT_SCS1HD] = 0x0000000f;
    s.regs[GT_SCS2LD] = 0x00000010;
    s.regs[GT_SCS2HD] = 0x00000017;
    s.regs[GT_SCS3LD] = 0x00000018;
    s.regs[GT_SCS3HD] = 0x0000001f;
    s.regs[GT_CS0LD] = 0x000000c0;
    s.regs[GT_CS0HD] = 0x000000c7;
    s.regs[GT_CS1LD] = 0x000000c8;
    s.regs[GT_CS1HD] = 0x000000cf;
    s.regs[GT_CS2LD] = 0x000000d0;
    s.regs[GT_CS2HD] = 0x000000df;
    s.regs[GT_CS3LD] = 0x000000f0;
    s.regs[GT_CS3HD] = 0x000000fb;
    s.regs[GT_BOOTLD] = 0x000000fc;
    s.regs[GT_BOOTHD] = 0x000000ff;
    s.regs[GT_ADERR] = 0xffffffff;

    /* SDRAM Configuration */
    s.regs[GT_SDRAM_CFG] = 0x00000200;
    s.regs[GT_SDRAM_OPMODE] = 0x00000000;
    s.regs[GT_SDRAM_BM] = 0x0000000d; //0x00000fff; // 11:3, 3, 1:0 must b 0x1
    s.regs[GT_SDRAM_ADDRDEC] = 0x00000002;

    /* SDRAM Parameters */
    s.regs[GT_SDRAM_B0] = 0x00000005;
    s.regs[GT_SDRAM_B1] = 0x00000005;
    s.regs[GT_SDRAM_B2] = 0x00000005;
    s.regs[GT_SDRAM_B3] = 0x00000005;

    /* ECC */
    s.regs[GT_ECC_ERRDATALO] = 0x00000000;
    s.regs[GT_ECC_ERRDATAHI] = 0x00000000;
    s.regs[GT_ECC_MEM] = 0x00000000;
    s.regs[GT_ECC_CALC] = 0x00000000;
    s.regs[GT_ECC_ERRADDR] = 0x00000000;

    /* Device Parameters */
    s.regs[GT_DEV_B0] = 0x386fffff;
    s.regs[GT_DEV_B1] = 0x386fffff;
    s.regs[GT_DEV_B2] = 0x386fffff;
    s.regs[GT_DEV_B3] = 0x386fffff;
    s.regs[GT_DEV_BOOT] = 0x146fffff;

    /* DMA registers are all zeroed at reset */

    /* Timer/Counter */
    s.regs[GT_TC0] = 0xffffffff;
    s.regs[GT_TC1] = 0x00ffffff;
    s.regs[GT_TC2] = 0x00ffffff;
    s.regs[GT_TC3] = 0x00ffffff;
    s.regs[GT_TC_CONTROL] = 0x00000000;

    /* PCI Internal */
    if (endianBig) {
        s.regs[GT_PCI0_CMD] = 0x00000000;
    } else {
        s.regs[GT_PCI0_CMD] = 0x00010001;
    }
    s.regs[GT_PCI0_TOR] = 0x0000070f;
    s.regs[GT_PCI0_BS_SCS10] = 0x00fff000;
    s.regs[GT_PCI0_BS_SCS32] = 0x00fff000;
    s.regs[GT_PCI0_BS_CS20] = 0x01fff000;
    s.regs[GT_PCI0_BS_CS3BT] = 0x00fff000;
    s.regs[GT_PCI1_IACK] = 0x00000000;
    s.regs[GT_PCI0_IACK] = 0x00000000;
    s.regs[GT_PCI0_BARE] = 0x0000000f;
    s.regs[GT_PCI0_PREFMBR] = 0x00000040;
    s.regs[GT_PCI0_SCS10_BAR] = 0x00000000;
    s.regs[GT_PCI0_SCS32_BAR] = 0x01000000;
    s.regs[GT_PCI0_CS20_BAR] = 0x1c000000;
    s.regs[GT_PCI0_CS3BT_BAR] = 0x1f000000;
    s.regs[GT_PCI0_SSCS10_BAR] = 0x00000000;
    s.regs[GT_PCI0_SSCS32_BAR] = 0x01000000;
    s.regs[GT_PCI0_SCS3BT_BAR] = 0x1f000000;
    if (endianBig) {
        s.regs[GT_PCI1_CMD] = 0x00000000;
    } else {
        s.regs[GT_PCI1_CMD] = 0x00010001;
    }
    s.regs[GT_PCI1_TOR] = 0x0000070f;
    s.regs[GT_PCI1_BS_SCS10] = 0x00fff000;
    s.regs[GT_PCI1_BS_SCS32] = 0x00fff000;
    s.regs[GT_PCI1_BS_CS20] = 0x01fff000;
    s.regs[GT_PCI1_BS_CS3BT] = 0x00fff000;
    s.regs[GT_PCI1_BARE] = 0x0000000f;
    s.regs[GT_PCI1_PREFMBR] = 0x00000040;
    s.regs[GT_PCI1_SCS10_BAR] = 0x00000000;
    s.regs[GT_PCI1_SCS32_BAR] = 0x01000000;
    s.regs[GT_PCI1_CS20_BAR] = 0x1c000000;
    s.regs[GT_PCI1_CS3BT_BAR] = 0x1f000000;
    s.regs[GT_PCI1_SSCS10_BAR] = 0x00000000;
    s.regs[GT_PCI1_SSCS32_BAR] = 0x01000000;
    s.regs[GT_PCI1_SCS3BT_BAR] = 0x1f000000;
    s.regs[GT_PCI1_CFGADDR] = 0x00000000;
    s.regs[GT_PCI1_CFGDATA] = 0x00000000;
    s.regs[GT_PCI0_CFGADDR] = 0x00000000;
    s.regs[GT_PCI0_CFGDATA] = 0x00000000;

    /* Interrupt registers are all zeroed at reset */

    gt64120_isd_mapping(&s);
    gt64120_pci_mapping(&s);
    gt64120_sdram_mapping(&s);
}

/* Adjust range to avoid touching space which isn't mappable via PCI */
/* XXX: Hardcoded values for Malta: 0x1e000000 - 0x1f100000
 0x1fc00000 - 0x1fd00000  */
void check_reserved_space(Uns32 *start, Uns32 *length) {
    Uns32 begin = *start;
    Uns32 end = *start + *length;

    if (end >= 0x1e000000LL && end < 0x1f100000LL)
        end = 0x1e000000LL;
    if (begin >= 0x1e000000LL && begin < 0x1f100000LL)
        begin = 0x1f100000LL;
    if (end >= 0x1fc00000LL && end < 0x1fd00000LL)
        end = 0x1fc00000LL;
    if (begin >= 0x1fc00000LL && begin < 0x1fd00000LL)
        begin = 0x1fd00000LL;
    /* XXX: This is broken when a reserved range splits the requested range */
    if (end >= 0x1f100000LL && begin < 0x1e000000LL)
        end = 0x1e000000LL;
    if (end >= 0x1fd00000LL && begin < 0x1fc00000LL)
        end = 0x1fc00000LL;

    if (PSE_DIAG_LOW & DIAG_INFO) {
        bhmMessage("I",
                PREFIX, "Check Reserved Space: begin %x end %x length %d\n",
                begin, end, end - begin);
    }

    *start = begin;
    *length = end - begin;
}

//
// Use the value in the ISD register to remap the device slave port.
//
static void gt64120_isd_mapping(GT64120State *s) {
    //
    // The value of the offset is derived by shifting GT_ISD << 21
    //
    Uns32 start = s->regs[GT_ISD] << 21;
    Uns32 length = BUS_WINDOW;

    if (PSE_DIAG_LOW & DIAG_MAIN_BUS) {
        bhmMessage("I", PREFIX, "ISD: mapping 0x%x bytes to 0x%x", length,
                start);
    }

    if (s->ISD_length) {
        ppmDeleteDynamicSlavePort(BUS_PORT_NAME, s->ISD_start, s->ISD_length);
    }
    check_reserved_space(&start, &length);

    /* Map new address */
    s->ISD_start = start;
    s->ISD_length = length;
    Bool ok = ppmCreateDynamicSlavePort(BUS_PORT_NAME, s->ISD_start,
            s->ISD_length, sysCtrlWindow);
    if (!ok) {
        bhmMessage("F", PREFIX, "Failed to connect port '%s'", BUS_PORT_NAME);
    }
}

static void gt64120_pci_mapping(GT64120State *s) {
    /* Update IO mapping */
    if ((s->regs[GT_PCI0IOLD] & 0x7f) <= s->regs[GT_PCI0IOHD]) {
        /* Unmap old IO address */
        //      if (s->PCI0IO_length)
        //      {
        //        cpu_register_physical_memory(s->PCI0IO_start, s->PCI0IO_length, IO_MEM_UNASSIGNED);
        //      }
        /* Map new IO address */
        s->PCI0IO_start = s->regs[GT_PCI0IOLD] << 21;
        s->PCI0IO_length = ((s->regs[GT_PCI0IOHD] + 1) - (s->regs[GT_PCI0IOLD]
                & 0x7f)) << 21;
        //      isa_mem_base = s->PCI0IO_start;
        //      isa_mmio_init(s->PCI0IO_start, s->PCI0IO_length);
        if (PSE_DIAG_LOW & DIAG_INFO) {
            bhmMessage("I", PREFIX,
            "PCI0IO mapping base:0x%x  bytes:0x%x", s->PCI0IO_start,
                    s->PCI0IO_length);
        }
    }
}

static Uns32 kseg0Conv (Uns32 addr) {
    return (addr | 0x80000000);
}
static Uns32 kseg1Conv (Uns32 addr) {
    return (addr | 0xA0000000);
}
static void decodeStage1(const char *id, Uns32 decLo, Uns32 decHi, Uns32 *base) {
    Uns64 addrLo = decLo << 21;
    Uns64 addrHi = decHi << 21;
    addrHi |= (addrLo & 0xFF0000000ULL); // bits 35:28

    //
    // Set bits 20:0
    //
    addrHi |= 0x1fffff;
    *base = PTR_TO_UNS32(addrLo & 0xFF0000000ULL);

    if (addrLo <= addrHi) {
        bhmPrintf("Region %s = 0x%08x:0x%08x (kseg0/1 0x%08x:0x%08x, 0x%08x:0x%08x)\n",
                id,
                PTR_TO_UNS32(addrLo), PTR_TO_UNS32(addrHi),
                kseg0Conv(addrLo), kseg0Conv(addrHi),
                kseg1Conv(addrLo), kseg1Conv(addrHi)
                );
    } else {
        bhmPrintf("Region %s Disabled\n", id);
    }
    return;
}

static void decodeStage2 (const char *id, Uns32 base, Uns32 decLo, Uns32 decHi) {
    Uns64 addrLo = base + (decLo << 20);
    Uns64 addrHi = base + (decHi << 20);
    addrHi |= 0xfffff;

    if (addrLo <= addrHi) {
        bhmPrintf("Region %s = 0x%08x:0x%08x (kseg0/1 0x%08x:0x%08x, 0x%08x:0x%08x)\n",
                id,
                PTR_TO_UNS32(addrLo), PTR_TO_UNS32(addrHi),
                kseg0Conv(addrLo), kseg0Conv(addrHi),
                kseg1Conv(addrLo), kseg1Conv(addrHi)
                );
    } else {
        bhmPrintf("Region %s Disabled\n", id);
    }
}

static void gt64120_sdram_mapping(GT64120State *s) {
    /* Update SDRAM mapping */

    // Just Print some info
    if (BHM_DIAG_LOW) {
        Uns32 base;
        bhmPrintf("Memory Decoding\n");
        decodeStage1("SCS[1:0]", s->regs[GT_SCS10LD], s->regs[GT_SCS10HD], &base);
        decodeStage2("SCS0    ", base, s->regs[GT_SCS0LD], s->regs[GT_SCS0HD]);
        decodeStage2("SCS1    ", base, s->regs[GT_SCS1LD], s->regs[GT_SCS1HD]);
        decodeStage1("SCS[3:2]", s->regs[GT_SCS32LD], s->regs[GT_SCS32HD], &base);
        decodeStage2("SCS2    ", base, s->regs[GT_SCS2LD], s->regs[GT_SCS2HD]);
        decodeStage2("SCS3    ", base, s->regs[GT_SCS3LD], s->regs[GT_SCS3HD]);

        bhmPrintf("Device Decoding\n");
        decodeStage1("CS[2:0]   ", s->regs[GT_CS20LD], s->regs[GT_CS20HD], &base);
        decodeStage2("CS0       ", base, s->regs[GT_CS0LD], s->regs[GT_CS0HD]);
        decodeStage2("CS1       ", base, s->regs[GT_CS1LD], s->regs[GT_CS1HD]);
        decodeStage2("CS2       ", base, s->regs[GT_CS2LD], s->regs[GT_CS2HD]);
        decodeStage1("CS[3]&BOOT", s->regs[GT_CS3BOOTLD], s->regs[GT_CS3BOOTHD], &base);
        decodeStage2("CS3       ", base, s->regs[GT_CS3LD], s->regs[GT_CS3HD]);
        decodeStage2("BOOT      ", base, s->regs[GT_BOOTLD], s->regs[GT_BOOTHD]);
    }
}

//
// Connect net ports
//
void netPortConnections(void) {
    intPortHandle = handles.timerInt;
}

//////////////////////////////// CATCHALL /////////////////////////////////////////////

//
// Slave Window from PCI bus.
// This is used to map the whole PCI configuration space.
// As devices install themselves, they replace parts of this region.
//
//static Uns8 pciConfigSlaveWindow[PCI_WINDOW];

//
// What is read from an empty slot
//
#define PCI_CONFIG_DEFAULT  0xFFFFFFFF

//
// catchall callbacks
//
//static PPM_READ_CB(readEmptyPCI) {
//    if (PSE_DIAG_LOW & DIAG_PCI_EMPTY) {
//        Uns32 offset = (Uns8*) addr - pciConfigSlaveWindow;
//        bhmMessage("I", PREFIX, "Read empty slot 0x%x", offset);
//    }
//    return PCI_CONFIG_DEFAULT;
//}
//
//static PPM_WRITE_CB(writeEmptyPCI) {
//    if (PSE_DIAG_LOW & DIAG_PCI_EMPTY) {
//        Uns32 offset = (Uns8*) addr - pciConfigSlaveWindow;
//        bhmMessage("I", PREFIX, "Write empty slot 0x%x", offset);
//    }
//}

//
// Install a catcher for all empty PCI configuration slots.
//
static void installPCIcatchAll(void) {
    // PCI config bus slave port
//    if (!ppmOpenSlaveBusPort(PCI_SPORT_NAME, pciConfigSlaveWindow,
//            sizeof(pciConfigSlaveWindow))) {
//        bhmMessage("F", PREFIX, "Missing PCI config bus slave port");
//    }

//    ppmInstallReadCallback(readEmptyPCI, 0, pciConfigSlaveWindow,
//            sizeof(pciConfigSlaveWindow));
//    ppmInstallWriteCallback(writeEmptyPCI, 0, pciConfigSlaveWindow,
//            sizeof(pciConfigSlaveWindow));
//    if (PSE_DIAG_LOW & DIAG_PCI_EMPTY) {
//        bhmMessage("I", PREFIX, "Catching access to PCI empty slots");
//    }
}
//
///////////////////////////////// LOCAL PCI CONFIG ///////////////////////////////////////
//
// As well as being the PCI configuration bus master, this device occupies one slave.
//
void localPCIinit(void) {
    pciConfig.vendorID = 0x11AB;
    pciConfig.deviceID = 0x4620;
    pciConfig.command = 0x0000;
    pciConfig.status = 0x0280;
    pciConfig.revisionID = 0x10;
    pciConfig.classCode[0] = 0x00;
    pciConfig.classCode[1] = 0x00;
    pciConfig.classCode[2] = 0x06;

    pciConfig.baseAddress[0] = 0x00000008;
    pciConfig.baseAddress[1] = 0x01000008;
    pciConfig.baseAddress[2] = 0x1C000000;
    pciConfig.baseAddress[3] = 0x1F000000;
    pciConfig.baseAddress[4] = 0x14000000;
    pciConfig.baseAddress[5] = 0x14000001;

    pciConfig.interruptPin = 0x01;

    pciConnectConfigSlavePort(SLAVE_PREFIX, NULL);
}

//
/////////////////////////////// Main for  sysControl /////////////////////////////////////
//
PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Starting\n");

    ppmInstallReadCallback(readRegs, 0, sysCtrlWindow, sizeof(sysCtrlWindow));
    ppmInstallWriteCallback(writeRegs, 0, sysCtrlWindow, sizeof(sysCtrlWindow));
    if (!(configBusHandle = handles.PCIconfigM)) {
        bhmMessage("F", PREFIX, "Missing PCI config bus master port");
    }
    if (PSE_DIAG_LOW & DIAG_PCI_CONFIG_MASTER) {
        bhmMessage("I", PREFIX, "Connected to PCI config bus, as bus master");
    }

    // master port to connect the PCI ACK cycle
    pciAckBus = ppmOpenMasterBusPort(PCI_ACKPORT_NAME, pciAckWindow,
            sizeof(pciAckWindow), 0);
    if (PSE_DIAG_LOW & DIAG_INT_ACK) {
        bhmMessage("W", PREFIX,
        "%sconnecting PCI ACK bus master port", pciAckBus ? "" : "Not ");
    }
    installPCIcatchAll();

    netPortConnections();
    localPCIinit();
    gt64120_reset();

    bhmEventHandle waitStart = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(waitStart);

    // write to other peripherals to configure after simulation starts
    if (pciEndianNetHandle) {
        if (PSE_DIAG_LOW & DIAG_INFO) {
            bhmMessage("I", PREFIX,
            "PCI Byte Swap %s", s.regs[GT_PCI0_CMD] & 1 ? "Disabled" : "Enabled");
        }
        ppmWriteNet(pciEndianNetHandle, s.regs[GT_PCI0_CMD] & 1 ? 0 : 1);
    }

    if (BHM_DIAG_LOW)
        bhmMessage("I", PREFIX, "Running");
}


PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
