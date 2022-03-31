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

#ifndef CIRRUS_CONSTANTS_H_
#define CIRRUS_CONSTANTS_H_

// ID
#define CIRRUS_ID_CLGD5422  (0x23<<2)
#define CIRRUS_ID_CLGD5426  (0x24<<2)
#define CIRRUS_ID_CLGD5424  (0x25<<2)
#define CIRRUS_ID_CLGD5428  (0x26<<2)
#define CIRRUS_ID_CLGD5430  (0x28<<2)
#define CIRRUS_ID_CLGD5434  (0x2A<<2)
#define CIRRUS_ID_CLGD5436  (0x2B<<2)
#define CIRRUS_ID_CLGD5446  (0x2E<<2)

// sequencer 0x07
#define CIRRUS_SR7_BPP_VGA            0x00
#define CIRRUS_SR7_BPP_SVGA           0x01
#define CIRRUS_SR7_BPP_MASK           0x0e
#define CIRRUS_SR7_BPP_8              0x00
#define CIRRUS_SR7_BPP_16_DOUBLEVCLK  0x02
#define CIRRUS_SR7_BPP_24             0x04
#define CIRRUS_SR7_BPP_16             0x06
#define CIRRUS_SR7_BPP_32             0x08
#define CIRRUS_SR7_ISAADDR_MASK       0xe0

// sequencer 0x0f
#define CIRRUS_MEMSIZE_512k        0x08
#define CIRRUS_MEMSIZE_1M          0x10
#define CIRRUS_MEMSIZE_2M          0x18
#define CIRRUS_MEMFLAGS_BANKSWITCH 0x80    // bank switching is enabled.

// sequencer 0x12
#define CIRRUS_CURSOR_SHOW         0x01
#define CIRRUS_CURSOR_HIDDENPEL    0x02
#define CIRRUS_CURSOR_LARGE        0x04    // 64x64 if set, 32x32 if clear

// sequencer 0x17
#define CIRRUS_BUSTYPE_VLBFAST   0x10
#define CIRRUS_BUSTYPE_PCI       0x20
#define CIRRUS_BUSTYPE_VLBSLOW   0x30
#define CIRRUS_BUSTYPE_ISA       0x38
#define CIRRUS_MMIO_ENABLE       0x04
#define CIRRUS_MMIO_USE_PCIADDR  0x40    // 0xb8000 if cleared.
#define CIRRUS_MEMSIZEEXT_DOUBLE 0x80

// control 0x0b
#define CIRRUS_BANKING_DUAL             0x01
#define CIRRUS_BANKING_GRANULARITY_16K  0x20    // set:16k, clear:4k

// control 0x30
#define CIRRUS_BLTMODE_BACKWARDS        0x01
#define CIRRUS_BLTMODE_MEMSYSDEST       0x02
#define CIRRUS_BLTMODE_MEMSYSSRC        0x04
#define CIRRUS_BLTMODE_TRANSPARENTCOMP  0x08
#define CIRRUS_BLTMODE_PATTERNCOPY      0x40
#define CIRRUS_BLTMODE_COLOREXPAND      0x80
#define CIRRUS_BLTMODE_PIXELWIDTHMASK   0x30
#define CIRRUS_BLTMODE_PIXELWIDTH8      0x00
#define CIRRUS_BLTMODE_PIXELWIDTH16     0x10
#define CIRRUS_BLTMODE_PIXELWIDTH24     0x20
#define CIRRUS_BLTMODE_PIXELWIDTH32     0x30

// control 0x31
#define CIRRUS_BLT_BUSY                 0x01
#define CIRRUS_BLT_START                0x02
#define CIRRUS_BLT_RESET                0x04
#define CIRRUS_BLT_FIFOUSED             0x10
#define CIRRUS_BLT_AUTOSTART            0x80

// control 0x32
#define CIRRUS_ROP_0                    0x00
#define CIRRUS_ROP_SRC_AND_DST          0x05
#define CIRRUS_ROP_NOP                  0x06
#define CIRRUS_ROP_SRC_AND_NOTDST       0x09
#define CIRRUS_ROP_NOTDST               0x0b
#define CIRRUS_ROP_SRC                  0x0d
#define CIRRUS_ROP_1                    0x0e
#define CIRRUS_ROP_NOTSRC_AND_DST       0x50
#define CIRRUS_ROP_SRC_XOR_DST          0x59
#define CIRRUS_ROP_SRC_OR_DST           0x6d
#define CIRRUS_ROP_NOTSRC_OR_NOTDST     0x90
#define CIRRUS_ROP_SRC_NOTXOR_DST       0x95
#define CIRRUS_ROP_SRC_OR_NOTDST        0xad
#define CIRRUS_ROP_NOTSRC               0xd0
#define CIRRUS_ROP_NOTSRC_OR_DST        0xd6
#define CIRRUS_ROP_NOTSRC_AND_NOTDST    0xda

#define CIRRUS_ROP_NOP_INDEX 2
#define CIRRUS_ROP_SRC_INDEX 5

// control 0x33
#define CIRRUS_BLTMODEEXT_SOLIDFILL        0x04
#define CIRRUS_BLTMODEEXT_COLOREXPINV      0x02
#define CIRRUS_BLTMODEEXT_DWORDGRANULARITY 0x01

// memory-mapped IO
#define CIRRUS_MMIO_BLTBGCOLOR        0x00    // dword
#define CIRRUS_MMIO_BLTFGCOLOR        0x04    // dword
#define CIRRUS_MMIO_BLTWIDTH          0x08    // word
#define CIRRUS_MMIO_BLTHEIGHT         0x0a    // word
#define CIRRUS_MMIO_BLTDESTPITCH      0x0c    // word
#define CIRRUS_MMIO_BLTSRCPITCH       0x0e    // word
#define CIRRUS_MMIO_BLTDESTADDR       0x10    // dword
#define CIRRUS_MMIO_BLTSRCADDR        0x14    // dword
#define CIRRUS_MMIO_BLTWRITEMASK      0x17    // byte
#define CIRRUS_MMIO_BLTMODE           0x18    // byte
#define CIRRUS_MMIO_BLTROP            0x1a    // byte
#define CIRRUS_MMIO_BLTMODEEXT        0x1b    // byte
#define CIRRUS_MMIO_BLTTRANSPARENTCOLOR 0x1c    // word?
#define CIRRUS_MMIO_BLTTRANSPARENTCOLORMASK 0x20    // word?
#define CIRRUS_MMIO_LINEARDRAW_START_X 0x24    // word
#define CIRRUS_MMIO_LINEARDRAW_START_Y 0x26    // word
#define CIRRUS_MMIO_LINEARDRAW_END_X  0x28    // word
#define CIRRUS_MMIO_LINEARDRAW_END_Y  0x2a    // word
#define CIRRUS_MMIO_LINEARDRAW_LINESTYLE_INC 0x2c    // byte
#define CIRRUS_MMIO_LINEARDRAW_LINESTYLE_ROLLOVER 0x2d    // byte
#define CIRRUS_MMIO_LINEARDRAW_LINESTYLE_MASK 0x2e    // byte
#define CIRRUS_MMIO_LINEARDRAW_LINESTYLE_ACCUM 0x2f    // byte
#define CIRRUS_MMIO_BRESENHAM_K1      0x30    // word
#define CIRRUS_MMIO_BRESENHAM_K3      0x32    // word
#define CIRRUS_MMIO_BRESENHAM_ERROR   0x34    // word
#define CIRRUS_MMIO_BRESENHAM_DELTA_MAJOR 0x36    // word
#define CIRRUS_MMIO_BRESENHAM_DIRECTION 0x38    // byte
#define CIRRUS_MMIO_LINEDRAW_MODE     0x39    // byte
#define CIRRUS_MMIO_BLTSTATUS         0x40    // byte

// PCI 0x00: vendor, 0x02: device
#define PCI_VENDOR_CIRRUS             0x1013
#define PCI_DEVICE_CLGD5462           0x00d0
#define PCI_DEVICE_CLGD5465           0x00d6

// PCI 0x04: command(word), 0x06(word): status
#define PCI_COMMAND_IOACCESS                0x0001
#define PCI_COMMAND_MEMACCESS               0x0002
#define PCI_COMMAND_BUSMASTER               0x0004
#define PCI_COMMAND_SPECIALCYCLE            0x0008
#define PCI_COMMAND_hRITEINVALID         0x0010
#define PCI_COMMAND_PALETTESNOOPING         0x0020
#define PCI_COMMAND_PARITYDETECTION         0x0040
#define PCI_COMMAND_ADDRESSDATASTEPPING     0x0080
#define PCI_COMMAND_SERR                    0x0100
#define PCI_COMMAND_BACKTOBACKTRANS         0x0200

// PCI 0x08, 0xff000000 (0x09-0x0b:class,0x08:rev)
#define PCI_CLASS_BASE_DISPLAY        0x03

// PCI 0x08, 0x00ff0000
#define PCI_CLASS_SUB_VGA             0x00

// PCI 0x0c, 0x00ff0000 (0x0c:cacheline,0x0d:latency,0x0e:headertype,0x0f:Built-in self test)
#define PCI_CLASS_HEADERTYPE_00h  0x00

// 0x10-0x3f (headertype 00h)
// PCI 0x10,0x14,0x18,0x1c,0x20,0x24: base address mapping registers
//   0x10: MEMBASE, 0x14: IOBASE(hard-coded in XFree86 3.x)
#define PCI_MAP_MEM                 0x0
#define PCI_MAP_IO                  0x1
#define PCI_MAP_MEM_ADDR_MASK       (~0xf)
#define PCI_MAP_IO_ADDR_MASK        (~0x3)
#define PCI_MAP_MEMFLAGS_32BIT      0x0
#define PCI_MAP_MEMFLAGS_32BIT_1M   0x1
#define PCI_MAP_MEMFLAGS_64BIT      0x4
#define PCI_MAP_MEMFLAGS_CACHEABLE  0x8

// PCI 0x28: cardbus CIS pointer
// PCI 0x2c: subsystem vendor id, 0x2e: subsystem id
// PCI 0x30: expansion ROM base address
#define PCI_ROMBIOS_ENABLED         0x1

// PCI 0x34: 0xffffff00=reserved, 0x000000ff=capabilities pointer
// PCI 0x38: reserved
// PCI 0x3c: 0x3c=int-line, 0x3d=int-pin, 0x3e=min-gnt, 0x3f=maax-lat

#define CIRRUS_PNPMMIO_SIZE         0x1000

#define VGA_RAM_SIZE                0x400000

#endif /*CIRRUS_CONSTANTS_H_*/
