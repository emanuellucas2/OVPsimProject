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

#ifndef _FDT_IMP_UTIL
#define _FDT_IMP_UTIL


#include "libfdt.h"

#define FDT_CHECK(code) \
    { \
        err = (code); \
        if (err) { \
            imperasMessage( \
                "E", PREFIX"_FDTERR", \
                #code ": %s", \
                fdt_strerror(err) \
            ); \
        } \
    }

//
// Print the dtb that has been loaded into memory
//
void fdtPrint(const void *fdt);

//
// Find or add the indicated subnode at the indicate path
//
Int32 fdtFindAddNode(void *fdt, const char *path, const char *node);

//
// Add memory reserve entries to fdt
//
void fdtReserveMemory(void *fdt, Addr start, Uns32 size);

//
// Set the initrd data in the fdt (info must already be set in config)
//
void fdtSetInitrd(void *fdt, Addr initrdStart, Uns32 initrdSize);

//
// Set the memory base and size
//
void fdtSetMemory(void *fdt, Addr memBase, Addr memSize);

//
// Set the enable-method and release address
// The only enable-method we support is spin-table - force it to that
//
void fdtSetEnableMethod(void *fdt, Addr releaseAddr);

//
// Set the command line data in the fdt
//
void fdtSetCommandLine(void *fdt, const char *command);

//
// Check if device with compatible string is present in fdt
//
Bool fdtCompatibleExists(void *fdt, const char *compatible);

//
// Read the device tree blob into memory
// If any problems issue error or fatal messages so that simulation will not proceed
//
void *fdtReadDTB(char *fn);

#endif /* _FDT_IMP_UTIL */
