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

//
// Smart loader peripheral model for Linux:
//   Loads the Linux Kernel, device tree blob and optional initrd.
//
//   For a description of some of what the heck is going on here see the file:
//      Documentation/arm64/booting.txt
//   in the Linux source tree.
//
//   This peripheral takes the place of the Boot monitor and U-Boot functions
//
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pse.igen.h"

#include "fdt_imp_util.h"

#define PREFIX "SMARTLOADER_LINUX"

#define FNSIZE 256

struct arm_boot_info {
    Addr  memBase;           // address of start of memory
    Addr  kernelAddr;        // address in simulated memory of kernel
    Addr  fdtAddr;           // address in simulated memory of flattened device tree
    Addr  initrdAddr;        // address in simulated memory of initrd
    Uns32 initrdSize;        // size of initrd file in bytes
    Addr  releaseAddr;       // cpu release address for device tree spin-table enable-method
    char  kernelFn[FNSIZE];  // name of kernel file to load
    char  dtbFn[FNSIZE];     // name of device tree blob file to load
    char  initrdFn[FNSIZE];  // name of initrd file to load (optional)
    Bool  gicv3Mode;         // run in gicv3 mode
};

// Structure to hold configuration info, initialized with defaults
static struct arm_boot_info config = {
    .kernelAddr = 0x80000ULL,   // default is this + memBase setting
};

//
// The tiny bootloader.  Set registers to values expected by Linux then jump to kernel.
// (assumes it is being run in EL3)
//
static Uns32 bootloader[] = {
    //
    // ARM V8 Linux Boot code
    // Compatible only with:
    //    spin-table CPU enable method
    //    gic V2 or V3 at 0x2c000000
    //
    // Derived from Regression_Tests/Explorer/dev/straus/LinuxAArch64/boot.s

        // <_start>:
            0xd53e1103,  //  mrs x3, scr_el3
            0xd280a024,  //  mov x4, #0x501                  // #1281
            0xaa040063,  //  orr x3, x3, x4
            0xd51e1103,  //  msr scr_el3, x3
            0xd5380404,  //  mrs x4, id_aa64pfr0_el1
            0xf268009f,  //  tst x4, #0x1000000
            0x54000940,  //  b.eq    140 <setup_gicv2>

        // <setup_gicv3>:
            0x58000ce2,  //  ldr x2, 1b8 <gicv3Mode>
            0xb40005c2,  //  cbz x2, d8 <setup_gicv3_compat>
            0xd53ecca5,  //  mrs x5, s3_6_c12_c12_5
            0xb2400ca5,  //  orr x5, x5, #0xf
            0xd51ecca5,  //  msr s3_6_c12_c12_5, x5
            0xd5033fdf,  //  isb
            0xd51ecc9f,  //  msr s3_6_c12_c12_4, xzr
            0xd5033fdf,  //  isb
            0xd53800a3,  //  mrs x3, mpidr_el1
            0xf2401c7f,  //  tst x3, #0xff
            0x540009e1,  //  b.ne    180 <secondary_cpu>
            0xd2a5e001,  //  mov x1, #0x2f000000             // #788529152
            0x528000e0,  //  mov w0, #0x7                    // #7
            0x321c0400,  //  orr w0, w0, #0x30
            0xb9000020,  //  str w0, [x1]
            0xd2a5e202,  //  mov x2, #0x2f100000             // #789577728
            0x2a3f03e5,  //  mvn w5, wzr

        // <next_rdist>:
            0x12800046,  //  mov w6, #0xfffffffd             // #-3
            0xb9401444,  //  ldr w4, [x2,#20]
            0x0a060084,  //  and w4, w4, w6
            0xb9001444,  //  str w4, [x2,#20]
            0xd5033e9f,  //  dsb st
            0xd5033fdf,  //  isb
            0xb9401444,  //  ldr w4, [x2,#20]
            0x721e009f,  //  tst w4, #0x4
            0x54ffffc1,  //  b.ne    78 <next_rdist+0x18>
            0x91404043,  //  add x3, x2, #0x10, lsl #12
            0xb9008065,  //  str w5, [x3,#128]
            0xb90d007f,  //  str wzr, [x3,#3328]
            0xb9400844,  //  ldr w4, [x2,#8]
            0x91404063,  //  add x3, x3, #0x10, lsl #12
            0x36080044,  //  tbz w4, #1, a0 <next_rdist+0x40>
            0x91408063,  //  add x3, x3, #0x20, lsl #12
            0xaa0303e2,  //  mov x2, x3
            0x3627fde4,  //  tbz w4, #4, 60 <next_rdist>
            0xb9400422,  //  ldr w2, [x1,#4]
            0x12001042,  //  and w2, w2, #0x1f
            0x34000602,  //  cbz w2, 170 <gic_done>
            0x51000442,  //  sub w2, w2, #0x1
            0x340005c2,  //  cbz w2, 170 <gic_done>
            0x91021023,  //  add x3, x1, #0x84
            0x91341024,  //  add x4, x1, #0xd04
            0xb8004465,  //  str w5, [x3],#4
            0xb800449f,  //  str wzr, [x4],#4
            0x51000442,  //  sub w2, w2, #0x1
            0x35ffffa2,  //  cbnz    w2, c4 <next_rdist+0x64>
            0x14000027,  //  b   170 <gic_done>

        // <setup_gicv3_compat>:
            0xd2a58004,  //  mov x4, #0x2c000000             // #738197504
            0x52801005,  //  mov w5, #0x80                   // #128
            0xb9000485,  //  str w5, [x4,#4]
            0xd53ecca5,  //  mrs x5, s3_6_c12_c12_5
            0xb27d00a5,  //  orr x5, x5, #0x8
            0xb24000a5,  //  orr x5, x5, #0x1
            0xd51ecca5,  //  msr s3_6_c12_c12_5, x5
            0xd2a5e004,  //  mov x4, #0x2f000000             // #788529152
            0xb9400485,  //  ldr w5, [x4,#4]
            0x120010a5,  //  and w5, w5, #0x1f
            0x531e74a5,  //  lsl w5, w5, #2
            0xf2801004,  //  movk    x4, #0x80
            0x8b0400a5,  //  add x5, x5, x4
            0x2a3f03e3,  //  mvn w3, wzr
            0xb8004483,  //  str w3, [x4],#4
            0xeb05009f,  //  cmp x4, x5
            0x54ffffcb,  //  b.lt    110 <setup_gicv3_compat+0x38>
            0xd2a5e204,  //  mov x4, #0x2f100000             // #789577728
            0xd53800a3,  //  mrs x3, mpidr_el1
            0x12001c63,  //  and w3, w3, #0xff
            0x530f3863,  //  lsl w3, w3, #17
            0x0b030084,  //  add w4, w4, w3
            0xb9401485,  //  ldr w5, [x4,#20]
            0x121e78a5,  //  and w5, w5, #0xfffffffd
            0xb9001485,  //  str w5, [x4,#20]
            0x1400000d,  //  b   170 <gic_done>

        // <setup_gicv2>:
            0xd2a58004,  //  mov x4, #0x2c000000             // #738197504
            0x52801005,  //  mov w5, #0x80                   // #128
            0xb9200485,  //  str w5, [x4,#8196]
            0xb9500485,  //  ldr w5, [x4,#4100]
            0x120010a5,  //  and w5, w5, #0x1f
            0x531e74a5,  //  lsl w5, w5, #2
            0xf2821004,  //  movk    x4, #0x1080
            0x8b0400a5,  //  add x5, x5, x4
            0x2a3f03e3,  //  mvn w3, wzr
            0xb8004483,  //  str w3, [x4],#4
            0xeb05009f,  //  cmp x4, x5
            0x54ffffcb,  //  b.lt    164 <setup_gicv2+0x24>

        // <gic_done>:
            0x580002c1,  //  ldr x1, 1c8 <kernel>
            0xd53800a3,  //  mrs x3, mpidr_el1
            0xf2401c7f,  //  tst x3, #0xff
            0x540000a0,  //  b.eq    190 <start_core>

        // <secondary_cpu>:
            0xd503205f,  //  wfe
            0x58000261,  //  ldr x1, 1d0 <release>
            0xf100003f,  //  cmp x1, #0x0
            0x54ffffa0,  //  b.eq    180 <secondary_cpu>

        // <start_core>:
            0xd53e4003,  //  mrs x3, spsr_el3
            0x927be863,  //  and x3, x3, #0xffffffffffffffe0
            0xb27d0063,  //  orr x3, x3, #0x8
            0xd51e4003,  //  msr spsr_el3, x3
            0xd51e4021,  //  msr elr_el3, x1
            0x580000e0,  //  ldr x0, 1c0 <dtb>
            0xaa1f03e1,  //  mov x1, xzr
            0xaa1f03e2,  //  mov x2, xzr
            0xaa1f03e3,  //  mov x3, xzr
            0xd69f03e0,  //  eret

    // Following are set by smartLoader
    // Note: Must be aligned to 8 bytes and must be last 4 entries in this array

    // gicv3Mode: .quad 0  // Set Affinity Routing Enable bits when true
    0x0, 0x0,

    // dtb:       .quad 0  //  Fill with PA of dtb
    0x0, 0x0,

    // kernel:    .quad 0  //  Fill with PA of kernel entry
    0x0, 0x0,

    // release:   .quad 0  //  spin-table cpu-release-addr
                           //  - Address is added to the device tree
                           //  - to be set by kernel
    0x0, 0x0,
};

// Indexes for the address entries to be filled in
#define BOOT_ENTRIES (sizeof(bootloader)/sizeof(bootloader[0]))
#define ENTRIES_PER_UNS64 (sizeof(Uns64)/sizeof(bootloader[0]))
#define BOOT_GICV3   (BOOT_ENTRIES - (4*ENTRIES_PER_UNS64))
#define BOOT_FDT     (BOOT_ENTRIES - (3*ENTRIES_PER_UNS64))
#define BOOT_KERNEL  (BOOT_ENTRIES - (2*ENTRIES_PER_UNS64))
#define BOOT_RELEASE (BOOT_ENTRIES - (1*ENTRIES_PER_UNS64))

// ***************************************************************

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

//
// Write to simulated memory
//
static Bool writeSimMemory(
    const char *name,
    Addr        addr,
    Uns32       size,
    void       *data
) {

    if (PSE_DIAG_MEDIUM) {
        bhmMessage(
            "I", PREFIX,
            "Writing %s (%d bytes at 0x%08llx)",
            name, size, addr
        );
    }

    if (!ppmWriteAddressSpace(handles.mport, addr, size, data)) {

        bhmMessage(
            "E", PREFIX,
            "Failed trying to write %s (%d bytes at 0x%08llx)",
            name, size, addr
        );
        return False;

    }

    return True;

}

//
// Return the size of a file given its file descriptor
// (resets file pointer to the beginning of the file)
//
static Uns32 fileSize(Int32 fd) {

    // Get the size of the file
    size_t size = lseek(fd, 0, SEEK_END);

    // Seek back to the beginning
    lseek(fd, 0, SEEK_SET);

    return size;
}

//
// Load the file to the indicated simulated memory address
// Returns number of bytes loaded or 0 if an error
//
static Uns32 loadImage(char *name, const char *filename, Addr addr) {

    Int32 fd = open(filename, O_RDONLY | O_BINARY);

    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open %s image file '%s'", name, filename);
        return 0;
    }

    // Get the size of the file
    Uns32 size = fileSize(fd);

    // Copy the file to simulated memory
    Uns32 bytes = size;
    Addr  dest  = addr;
    char buff[BYTES_PER_ACCESS];
    while (bytes) {

        size_t thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;

        thisAccess = read(fd, buff, thisAccess);

        if (!ppmWriteAddressSpace(handles.mport, dest, thisAccess, buff)) {

            bhmMessage(
                "E", PREFIX,
                "Unable to write %s image file '%s' to simulated memory: failed at 0x%08llx",
                name, filename, dest
            );

            close(fd);
            return 0;

        }

        dest += thisAccess;
        bytes -= thisAccess;

    }

    close(fd);

    if (PSE_DIAG_LOW) {
        bhmMessage(
            "I", PREFIX,
            "%s image file '%s' loaded (%d bytes at 0x%08llx)",
            name, filename, size, addr
        );
    }

    return size;
}

static Bool setAddrParameter(char *name, Addr *val) {

    Addr attrVal;

    if (bhmUns64ParamValue(name, &attrVal)) {
        *val = attrVal;
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "%s: set to 0x%08llx", name, *val);
        }
        return True;
    } else if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "%s: using default value 0x%08llx", name, *val);
    }
    return False;
}

static Bool setStringParameter(char *name, char *str, Uns32 size) {

    if (bhmStringParamValue(name, str, size)) {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "%s: set to '%s'", name, str);
        }
        return True;
    }
    return False;
}

//
// Align pointer to the indicated byte boundary
//
static inline Addr alignPointer(Addr ptr, Uns32 align) {
    Addr mask = align - 1;
    return (ptr + mask) & ~mask;
}

//
// Access all attributes to inhibit unused warning messages
//
static void touchParameters() {

    Uns64 dummy;
    char dummyStr[4];

    bhmUns64ParamValue ("kerneladdr", &dummy);
    bhmUns64ParamValue ("kerneladdr", &dummy);
    bhmStringParamValue("kernel",      dummyStr, sizeof(dummyStr));
    bhmStringParamValue("command",     dummyStr, sizeof(dummyStr));
    bhmStringParamValue("append",      dummyStr, sizeof(dummyStr));
    bhmStringParamValue("initrd",      dummyStr, sizeof(dummyStr));
    bhmStringParamValue("dtb",         dummyStr, sizeof(dummyStr));

}

PPM_CONSTRUCTOR_CB(constructor) {

    bhmEventHandle started  = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(started);

    Addr writePointer;

    periphConstructor();

    Bool disable;
    bhmBoolParamValue("disable", &disable);
    if (disable) {

        bhmMessage("W", PREFIX"_SLD", "Linux Smart Loader Disabled");
        touchParameters();

    } else {

        //
        // Override defaults with any attributes set from platform
        //
        setAddrParameter("physicalbase", &config.memBase);
        config.kernelAddr += config.memBase;
        setAddrParameter("kerneladdr",   &config.kernelAddr);

        //
        // Write kernel image to memory
        //
        if (!setStringParameter("kernel", config.kernelFn, sizeof(config.kernelFn))) {
            bhmMessage(
                "I", PREFIX,
                "kernel: using default value '%s'",
                config.kernelFn
            );
        }
        writePointer  = config.kernelAddr;
        writePointer += loadImage("kernel", config.kernelFn, writePointer);

        // Align write pointer to next 16MB page, to make sure it is past kernel's BSS
        writePointer  = alignPointer(writePointer, 16*1024*1024);

        //
        // if an initrd image file was specified,
        // copy it into simulated memory (Aligned to 4096 bytes)
        //
        setStringParameter("initrd", config.initrdFn, sizeof(config.initrdFn));
        if (*config.initrdFn != '\0') {
            writePointer      = alignPointer(writePointer, 4096);
            config.initrdAddr = writePointer;
            config.initrdSize = loadImage("initrd", config.initrdFn, config.initrdAddr);
            writePointer      += config.initrdSize;
        }

        //
        // Read dtb file into host memory and add any additional settings to the fdt
        // Copy the fdt to simulated memory immediately following the bootloader (aligned to 8 bytes)
        // (Note: Must be done after initrd has been read)
        //
        if (!setStringParameter("dtb", config.dtbFn, sizeof(config.dtbFn))) {

            bhmMessage("E", PREFIX"_MDF", "dtb file name must be specified using the dtb parameter");

        } else {

            void *fdt = fdtReadDTB(config.dtbFn);

            if (fdt) {

                // Set initrd info in fdt
                fdtSetInitrd(fdt, config.initrdAddr, config.initrdSize);

                // Set enable-method in fdt
                fdtSetEnableMethod(fdt, config.memBase + (BOOT_RELEASE * sizeof(bootloader[0])));

                // set command line info in fdt
                char cmdLine[1024] = "";
                char append[512]   = "";
                setStringParameter("command", cmdLine, sizeof(cmdLine));
                setStringParameter("append",  append, sizeof(append));
                if (*append) {
                    Uns32 len = strlen(cmdLine);
                    snprintf(cmdLine+len, sizeof(cmdLine)-len, " %s", append);
                }
                fdtSetCommandLine(fdt, cmdLine);

                // Search for a gicv3 compatible node
                config.gicv3Mode = fdtCompatibleExists(fdt, "arm,gic-v3");

                if (PSE_DIAG_HIGH) {
                    fdtPrint(fdt);
                }

                // Get size of the fdt
                Uns32 fdtSize = fdt_totalsize(fdt);

                config.fdtAddr = alignPointer(config.memBase + sizeof(bootloader), 0x1000);
                if (config.fdtAddr + fdtSize >= config.kernelAddr) {
                    bhmMessage("F", PREFIX"_DTB", "Device tree too big: %d bytes", fdtSize);
                }

                // Copy fdt to simulated memory
                writeSimMemory("dtb", config.fdtAddr, fdtSize, fdt);

            }
        }

        // Place fdtAddr and kernelAddr in boot code
        *(Uns64 *)(bootloader+BOOT_GICV3)   = config.gicv3Mode ? 1ULL : 0ULL;
        *(Uns64 *)(bootloader+BOOT_FDT)     = config.fdtAddr;
        *(Uns64 *)(bootloader+BOOT_KERNEL)  = config.kernelAddr;
        *(Uns64 *)(bootloader+BOOT_RELEASE) = 0ULL; // will be set by kernel

        // Write bootloader to beginning of simulated memory
        writeSimMemory("bootloader", config.memBase, sizeof(bootloader), bootloader);

    }

    // No longer used so close it
    ppmCloseAddressSpace(handles.mport);

}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

