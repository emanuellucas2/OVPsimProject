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

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fdt_imp_util.h"

#ifndef PREFIX
#define PREFIX "FDT_IMP_UTIL"
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

static void fdtShowHeader(const void *fdt) {
    Uns32 magic = fdt_magic(fdt);
    Uns32 off_dt_struct = fdt_off_dt_struct(fdt);
    Uns32 off_dt_strings = fdt_off_dt_strings(fdt);
    Uns32 off_mem_rsvmap = fdt_off_mem_rsvmap(fdt);
    Uns32 version = fdt_version(fdt);
    Uns32 last_comp_version = fdt_last_comp_version(fdt);
    Uns32 size_dt_strings = fdt_size_dt_strings(fdt);
    Uns32 size_dt_struct = fdt_size_dt_struct(fdt);
    imperasMessage("I", PREFIX"_FDT", "Header magic 0x%x", magic);
    imperasMessage("I", PREFIX"_FDT", "Header off_dt_struct 0x%x", off_dt_struct);
    imperasMessage("I", PREFIX"_FDT", "Header off_dt_strings 0x%x", off_dt_strings);
    imperasMessage("I", PREFIX"_FDT", "Header off_mem_rsvmap 0x%x", off_mem_rsvmap);
    imperasMessage("I", PREFIX"_FDT", "Header version 0x%x", version);
    imperasMessage("I", PREFIX"_FDT", "Header last_comp_version 0x%x", last_comp_version);
    imperasMessage("I", PREFIX"_FDT", "Header size_dt_strings 0x%x", size_dt_strings);
    imperasMessage("I", PREFIX"_FDT", "Header size_dt_struct 0x%x", size_dt_struct);
}

static Bool isStringProp(const char *prop, int propLen) {

    int i;
    char c = ' ';
    Bool printableFound = False;

    for (i = 0; i < propLen; i++) {

        c = prop[i];

        if (isprint(c)) {
            printableFound = True;
        } else if (c != '\0') {
            return False;
        }
    }

    // String must contain at least one printable character
    // and the last character must be'\0'
    return printableFound && c == '\0';
}

static void fdtShowProp(const char *propName, const void *prop, int propLen) {

    if (prop) {

        imperasPrintf(
            "  prop: '%s', len=%d",
            propName, propLen
        );

        if (propLen) {

            imperasPrintf(" value:");

            if (isStringProp(prop, propLen)) {

                // Print as list of strings
                int i = 0;
                while (i < propLen) {
                    char *s = ((char *)prop) + i;
                    imperasPrintf("%s'%s'", i > 0 ? ", " : " ", s);
                    i += strlen(s) + 1;
                }

            } else if ((propLen % 4) == 0) {

                // Print as array of big endian 32 bit ints
                imperasPrintf(" < ");
                int i;
                for (i = 0; i < propLen/4; i++) {
                    Uns32 val = ((Uns32 *)prop)[i];
                    val = SWAP_4_BYTE(val);
                    imperasPrintf("%s0x%x",  i > 0 ? ", " : " ", val);
                }
                imperasPrintf(" > ");

            } else {

                // Unknown type - print as bytes
                int i;
                for (i = 0; i < propLen; i++) {
                    Uns8 val = ((Uns8 *)prop)[i];
                    imperasPrintf(" 0x%2x ('%c')", val, isprint(val) ? val : '.');
                }
            }
        }

        imperasPrintf("\n");

    }
}

static void fdtShowNode(const void *fdt, int nodeOffset) {

    int err;
    int offset;
    char path[256];

    FDT_CHECK(fdt_get_path(fdt, nodeOffset, path, sizeof(path)));

    if (!err) {

        imperasMessage("I", PREFIX"_FDT", "Path: %s", path);

        // List properties
        for (offset=fdt_first_property_offset(fdt, nodeOffset);
             offset >= 0;
             offset=fdt_next_property_offset(fdt, offset)) {

            const void *prop;
            const char *propName;
            int         propLen;

            prop = fdt_getprop_by_offset(fdt, offset, &propName, &propLen);
            fdtShowProp(propName, prop, propLen);

        }

        // list subnodes
        for (offset=fdt_first_subnode(fdt, nodeOffset);
             offset >= 0;
             offset=fdt_next_subnode(fdt, offset)) {

            fdtShowNode(fdt, offset);

        }
    }
}

//
// Print Memory nodes
//
//static void fdtShowMemory(const void *fdt) {
//
//    Uns64 addr;
//    Uns64 size;
//    int i;
//
//    for (i = 0, size = -1ULL; size != 0; i++) {
//        fdt_get_mem_rsv(fdt, i, &addr, &size);
//        if (size) {
//            // TODO: work around bug with 64 bit arguments in imperasMessage
//            union { Uns64 u64; Uns32 u32[2]; } addrX={.u64=addr}, sizeX={.u64=size};
//            imperasMessage(
//                "I", PREFIX"_FDT",
//                "MemRsv: At: 0x%08x%08x Size: 0x%08x%08x",
//                addrX.u32[1], addrX.u32[0], sizeX.u32[1], sizeX.u32[0]
//            );
//        }
//    }
//}

//
// Print the Memory Reserve table in the fdt
//
static void fdtShowMemRsv(const void *fdt) {

    Uns64 addr;
    Uns64 size;
    int i;

    for (i = 0, size = -1ULL; size != 0; i++) {
        fdt_get_mem_rsv(fdt, i, (uint64_t *)&addr, (uint64_t *)&size);
        if (size) {
            // TODO: work around bug with 64 bit arguments in imperasMessage
            union { Uns64 u64; Uns32 u32[2]; } addrX={.u64=addr}, sizeX={.u64=size};
            imperasMessage(
                "I", PREFIX"_FDT",
                "MemRsv: At: 0x%08x%08x Size: 0x%08x%08x",
                addrX.u32[1], addrX.u32[0], sizeX.u32[1], sizeX.u32[0]
            );
        }
    }
}

//
// Print the dtb that has been loaded into memory
//
void fdtPrint(const void *fdt) {
    fdtShowHeader(fdt);
    fdtShowNode(fdt, 0);
    fdtShowMemRsv(fdt);
}

//
// Find or add the indicated subnode at the indicate path
//
Int32 fdtFindAddNode(void *fdt, const char *path, const char *node) {

    Int32 parentOffset = fdt_path_offset(fdt, path);
    Int32 offset;

    if (parentOffset < 0) {

        // Error finding parent node
        offset = parentOffset;

    }  else {

        offset = fdt_subnode_offset(fdt, parentOffset, node);
        if (offset == -FDT_ERR_NOTFOUND) {
            // Must add the node
            offset = fdt_add_subnode(fdt, parentOffset, node);
        }

    }

    if (offset < 0) {
        imperasMessage(
            "E", PREFIX"_ECN",
            "Error creating FDT node '%s%s%s': %s",
            path,
            (*path && path[strlen(path)-1] == '/') ? "" : "/",
            node,
            fdt_strerror(offset)
        );
    }

    return offset;
}

//
// Add memory reserve entries to fdt
//
void fdtReserveMemory(void *fdt, Addr start, Uns32 size) {

    Int32 err;

    FDT_CHECK(fdt_add_mem_rsv(fdt, start, size));

}

//
// Set the initrd data in the fdt
//
void fdtSetInitrd(void *fdt, Addr initrdStart, Uns32 initrdSize) {

    if (initrdSize) {

        Int32 chosenOffset = fdtFindAddNode(fdt, "/", "chosen");
        if (chosenOffset >= 0) {

            Addr initrdEnd   = initrdStart + initrdSize;

            fdt_setprop_u64(fdt, chosenOffset, "linux,initrd-start", initrdStart);
            fdt_setprop_u64(fdt, chosenOffset, "linux,initrd-end",   initrdEnd);

            fdtReserveMemory(fdt, initrdStart, initrdSize);

        }
    }
}

//
// Set the command line data in the fdt
//
void fdtSetCommandLine(void *fdt, const char *command) {

    int err;

    if (command && *command) {

        Int32 chosenOffset = fdtFindAddNode(fdt, "/", "chosen");

        if (chosenOffset >= 0) {

            FDT_CHECK(fdt_setprop_string(fdt, chosenOffset, "bootargs", command));

            if (IMP_DIAG_LOW) {
                imperasMessage(
                    "I", PREFIX"_LCL",
                    "Linux kernel command line set to: '%s'",
                    command
                );
            }
        }
    }
}

//
// Convert words in an Uns64 array to fdt32 array
// Word swap the hi and lo words of each Uns64
// then byte swap the words
//
static void uns64_to_fdt32_array(Uns64 *array, Uns32 size) {
    Uns32 *array32 = (Uns32 *)array;
    while (size >= sizeof(*array)) {
        Uns32 temp = cpu_to_fdt32(array32[0]);
        array32[0] = cpu_to_fdt32(array32[1]);
        array32[1] = temp;
        array32   += 2;
        size      -= sizeof(*array);
    }
}

//
// Set the memory base and size
//
void fdtSetMemory(void *fdt, Addr memBase, Addr memSize) {

    if (memBase && memSize) {

        char *propValue  = "memory";
        Uns32 propLen    = strlen(propValue) + 1;
        Int32 memOffset  = fdtFindAddNode(fdt, "/", "memory");

        if (memOffset >= 0) {

            int   err;
            Uns64 reg[2] = { memBase, memSize };

            // set reg node with memory values
            uns64_to_fdt32_array(reg, sizeof(reg));
            FDT_CHECK(fdt_setprop(fdt, memOffset, "reg", reg, sizeof(reg)));

            // Add device-type if missing
            if (fdt_getprop(fdt, memOffset, "device-type", NULL) < 0) {
                FDT_CHECK(fdt_setprop(fdt, memOffset, "device-type", propValue, propLen));
            }
        }
    }
}

//
// Set the enable-method and release address
// The only enable-method we support is spin-table - force it to that
//
void fdtSetEnableMethod(void *fdt, Addr releaseAddr) {

    int err;

    Int32 cpusOffset = fdt_path_offset(fdt, "/cpus");
    if (cpusOffset < 0) {

        imperasMessage(
            "E", PREFIX"_UFC",
            "Unable to find node '/cpus' in dtb: %s",
            fdt_strerror(cpusOffset)
        );

    } else {

        int cpuOffset;

        for (cpuOffset=fdt_first_subnode(fdt, cpusOffset);
             cpuOffset >= 0;
             cpuOffset=fdt_next_subnode(fdt, cpuOffset)) {

            FDT_CHECK(fdt_setprop_string(fdt, cpuOffset, "enable-method", "spin-table"));
            FDT_CHECK(fdt_setprop_u64   (fdt, cpuOffset, "cpu-release-addr", releaseAddr));

        }
    }
}

//
// Check if device with compatible string is present in fdt
//
Bool fdtCompatibleExists(void *fdt, const char *compatible) {

    int  offset = fdt_node_offset_by_compatible(fdt, -1, compatible);
    Bool found  = (offset != -FDT_ERR_NOTFOUND);

    if (found && IMP_DIAG_LOW) {
        imperasMessage(
            "I", PREFIX,
            "Device with compatible='%s' found in device tree",
            compatible
        );
    }

    return found;

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
// Read the device tree blob into memory
// If any problems issue error or fatal messages so that simulation will not proceed
//
void *fdtReadDTB(char *fn) {

    Int32 fd = open(fn, O_RDONLY | O_BINARY);
    if (fd < 0) {
        imperasMessage("E", PREFIX"_UOD", "Unable to open dtb file '%s'", fn);
        return NULL;
    }

    // Allocate a buffer to hold the dtb file + room for adding some data
    Uns32 origDTBsize = fileSize(fd);
    Uns32 DTBsize     = origDTBsize + 1024;
    void *dtb         = malloc(DTBsize);
    if (!dtb) {
        imperasMessage("F", PREFIX"_UAD", "Unable to allocate %d bytes for dtb", DTBsize);
        return NULL;   // Not reached
    }

    // load the dtb into the allocated buffer
    Int32 rc = read(fd, dtb, origDTBsize);
    close(fd);
    if (rc != origDTBsize) {
        imperasMessage("E", PREFIX"_URD", "Unable to read dtb file '%s'", fn);
        free(dtb);
        return NULL;
    }

    // Let fdt know about the extra space available
    fdt_set_totalsize(dtb, DTBsize);

    // Check that dtb file just loaded is valid
    rc = fdt_check_header(dtb);
    if (rc != 0) {
        imperasMessage("E", PREFIX"_DFI", "dtb file '%s' invalid: %s", fn, fdt_strerror(rc));
        return NULL;
    }

    if (IMP_DIAG_LOW) {
        imperasMessage("I", PREFIX"_DFL", "dtb file '%s' loaded (%d bytes)", fn, origDTBsize);
    }

    return dtb;

}
