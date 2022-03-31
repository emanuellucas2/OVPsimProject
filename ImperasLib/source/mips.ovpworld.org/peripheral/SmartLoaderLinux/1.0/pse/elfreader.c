/*
 * QEMU ELF File Reader.
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "elf.h"

#define PREFIX "ELFREADER"

struct syminfo {
    unsigned int disas_num_syms;
    void *disas_symtab;
    const char *disas_strtab;
    struct syminfo *next;
} *syminfos;


#define elf_word        Uns32
#define elf_sword       Int32
#define ELF_MACHINE     EM_MIPS

// If the file endian-ness does not match the proc arch, need to swap bytes.
Bool byteSwap;
Bool nanoMIPS;

//
// read a short from the ELF file - endian-corrected
//
static inline Uns16 ELF_UNS16_H(Uns16 p)
{
    if (byteSwap)
        return (((p & 0x00ff) << 8) |
                ((p & 0xff00) >> 8));
    else
        return p;
 }

//
// read a long from the ELF file - endian-corrected
//
static inline Uns32 ELF_UNS32_H(Uns32 p)
{
    if (byteSwap)
        return (((p & 0x000000ff) << 24) |
                ((p & 0x0000ff00) << 8) |
                ((p & 0x00ff0000) >> 8) |
                ((p & 0xff000000) >> 24));
    else
        return p;
}

static int read_elf32(int fd,
                      Uns32 *pentry,
                      Uns32 *lowaddr,
                      Uns32 *highaddr,
                      struct elf32_hdr *ehdr)
{
    struct elf32_phdr *phdr = NULL, *ph;
    int size, i, total_size;
    elf_word mem_size;
    Uns32 addr, low = 0, high = 0;
    Uns8 *data = NULL;
    Uns16 em;

    if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
        byteSwap = 1;
    else if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
        byteSwap = 0;
    else {
        bhmMessage("E", PREFIX, "ELF file endian-ness not specified\n");
        return 0;
    }

    em = ELF_UNS16_H(ehdr->e_machine);
    if (ELF_MACHINE != em && EM_NANOMIPS != em) {
        bhmMessage("F", PREFIX, "%s: ELF_MACHINE 0x%08x != ehdr.e_machine 0x%08x",
                            __FUNCTION__, ELF_MACHINE, ELF_UNS16_H(ehdr->e_machine));
        goto fail;
    }
    nanoMIPS = EM_NANOMIPS == em;

    if (pentry){
        *pentry = (Uns64)(elf_sword)ELF_UNS32_H(ehdr->e_entry);
    }

    size = ELF_UNS16_H(ehdr->e_phnum) * sizeof(phdr[0]);
    lseek(fd, ELF_UNS32_H(ehdr->e_phoff), SEEK_SET);
    phdr = malloc(size);
    if (!phdr) {
        bhmMessage("F", PREFIX, "%s: !phdr", __FUNCTION__);
        goto fail;
    }
    if (read(fd, phdr, size) != size){
        bhmMessage("F", PREFIX, "%s: read(fd, phdr, size) != size", __FUNCTION__);
        goto fail;
    }
    total_size = 0;
    for(i = 0; i < ELF_UNS16_H(ehdr->e_phnum); i++) {
        ph = &phdr[i];
        if (ELF_UNS32_H(ph->p_type) == PT_LOAD) {
            mem_size = ELF_UNS32_H(ph->p_memsz);
            /* XXX: avoid allocating */
            data = malloc(mem_size);
            if (ELF_UNS32_H(ph->p_filesz) > 0) {
                if (lseek(fd, ELF_UNS32_H(ph->p_offset), SEEK_SET) < 0) {
                    bhmMessage("F", PREFIX, "%s: lseek(fd, ph->p_offset, SEEK_SET) < 0", __FUNCTION__);
                    goto fail;
                }
                if (read(fd, data, ELF_UNS32_H(ph->p_filesz)) != ELF_UNS32_H(ph->p_filesz)) {
                    bhmMessage("F", PREFIX, "%s: read(fd, data, ph->p_filesz) != ph->p_filesz ", __FUNCTION__);
                    goto fail;
                }
            }

            addr = ELF_UNS32_H(ph->p_vaddr);
            total_size += mem_size;
            if (!low || addr < low) {
                low = addr;
            }
            if (!high || (addr + mem_size) > high) {
                high = addr + mem_size;
            }

            free(data);
            data = NULL;
        }
    }
    free(phdr);
    if (lowaddr)
        *lowaddr = (Uns64)(elf_sword)low;
    if (highaddr)
        *highaddr = (Uns64)(elf_sword)high;
    return total_size;
fail:
    free(data);
    free(phdr);
    return -1;
}

static int read_elf64(int fd, Uns32 *pentry,
                              Uns32 *lowaddr,
                              Uns32 *highaddr,
                              struct elf64_hdr *ehdr)
{
    struct elf64_phdr *phdr = NULL, *ph;
    int size, i, total_size;
    elf_word mem_size;
    Uns64 addr, low = 0, high = 0;
    Uns8 *data = NULL;

    if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
        byteSwap = 1;
    else if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
        byteSwap = 0;
    else {
        bhmMessage("E", PREFIX, "ELF file endian-ness not specified\n");
        return 0;
    }

    if (ELF_MACHINE != ELF_UNS16_H(ehdr->e_machine)) {
        bhmMessage("F", PREFIX, "%s: ELF_MACHINE 0x%08x != ehdr->e_machine 0x%08x",
                            __FUNCTION__, ELF_MACHINE, ELF_UNS16_H(ehdr->e_machine));
        goto fail;
    }

    if (pentry){
        *pentry = (Uns64)(elf_sword)ELF_UNS32_H(ehdr->e_entry);
    }

    size = ELF_UNS16_H(ehdr->e_phnum) * sizeof(phdr[0]);
    lseek(fd, ELF_UNS32_H(ehdr->e_phoff), SEEK_SET);
    phdr = malloc(size);
    if (!phdr) {
        bhmMessage("F", PREFIX, "%s: !phdr", __FUNCTION__);
        goto fail;
    }
    if (read(fd, phdr, size) != size){
        bhmMessage("F", PREFIX, "%s: read(fd, phdr, size) != size", __FUNCTION__);
        goto fail;
    }
    total_size = 0;
    for(i = 0; i < ELF_UNS16_H(ehdr->e_phnum); i++) {
        ph = &phdr[i];
        if (ELF_UNS32_H(ph->p_type) == PT_LOAD) {
            mem_size = ELF_UNS32_H(ph->p_memsz);
            /* XXX: avoid allocating */
            data = malloc(mem_size);
            if (ELF_UNS32_H(ph->p_filesz) > 0) {
                if (lseek(fd, ELF_UNS32_H(ph->p_offset), SEEK_SET) < 0) {
                    bhmMessage("F", PREFIX, "%s: lseek(fd, ph->p_offset, SEEK_SET) < 0", __FUNCTION__);
                    goto fail;
                }
                if (read(fd, data, ELF_UNS32_H(ph->p_filesz)) != ELF_UNS32_H(ph->p_filesz)) {
                    bhmMessage("F", PREFIX, "%s: read(fd, data, ph->p_filesz) != ph->p_filesz ", __FUNCTION__);
                    goto fail;
                }
            }

            addr = ELF_UNS32_H(ph->p_vaddr);
            total_size += mem_size;
            if (!low || addr < low) {
                low = addr;
            }
            if (!high || (addr + mem_size) > high) {
                high = addr + mem_size;
            }

            free(data);
            data = NULL;
        }
    }
    free(phdr);
    if (lowaddr)
        *lowaddr = (Uns64)(elf_sword)low;
    if (highaddr)
        *highaddr = (Uns64)(elf_sword)high;
    return total_size;
 fail:
    free(data);
    free(phdr);
    return -1;
}

int read_elf(int fd, Uns32 *pentry,
                     Uns32 *lowaddr,
                     Uns32 *highaddr)
{
    struct elf32_hdr ehdr32;
    struct elf64_hdr ehdr64;

    Uns32 rdLen = read(fd, &ehdr32, sizeof(ehdr32));
    if (rdLen != sizeof(ehdr32)) {
        bhmMessage("F", PREFIX, "%s: read(fd, &ehdr, sizeof(ehdr)) 0x%08x %d != sizeof(ehdr) 0x%08x %d",
            __FUNCTION__, rdLen, rdLen, (Uns32)sizeof(ehdr32), (Uns32)sizeof(ehdr32));
        return -1;
    }
    if (ehdr32.e_phoff != 0 && ehdr32.e_phoff != ~0) {
        /* Elf32 image. */
        return read_elf32(fd, pentry, lowaddr, highaddr, &ehdr32);
    }

    /* Elf64 image. */
    lseek (fd, (off_t) 0, 0);
    rdLen = read(fd, &ehdr64, sizeof(ehdr64));
    if (rdLen != sizeof(ehdr64)) {
        bhmMessage("F", PREFIX, "%s: read(fd, &ehdr, sizeof(ehdr)) 0x%08x %d != sizeof(ehdr) 0x%08x %d",
            __FUNCTION__, rdLen, rdLen, (Uns32)sizeof(ehdr64), (Uns32)sizeof(ehdr64));
        return -1;
    }
    return read_elf64(fd, pentry, lowaddr, highaddr, &ehdr64);
}
