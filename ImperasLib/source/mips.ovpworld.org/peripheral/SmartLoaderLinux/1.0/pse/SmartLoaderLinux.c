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


// smart loader model for Linux provides memory initialization for running a linux kernel

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "pse.igen.h"

#include "elfreader.h"
#include "libfdt.h"

#define BUFFERLENGTH 16
#define DEBUG 0
#define PREFIX "SMARTLOADER_LINUX"

// Calculate number of entries in an array
#define NUM_ENTRIES(_A) (sizeof(_A)/sizeof(*_A))

// Need to define the TLB page size used in the target processor
// this is used to align the loaded initrd onto the next page boundary
#define TARGET_PAGE_BITS_DEFAULT 12
Uns32 targetPageBits;
#define TARGET_PAGE_SIZE (1 << targetPageBits)
#define TARGET_PAGE_MASK ~(TARGET_PAGE_SIZE - 1)
#define TARGET_PAGE_ALIGN_UP(addr)   (((addr) + TARGET_PAGE_SIZE - 1) & TARGET_PAGE_MASK)
#define TARGET_PAGE_ALIGN_DOWN(addr) (((addr) - TARGET_PAGE_SIZE - 1) & TARGET_PAGE_MASK)

// The environment for the Linux kernel consists of
// 1. Command line arguments
// 2. environment variables
// environment variables are structured as paired entries ie name and value in separate entries
// and follow after the command line
#define VIRTUAL_BASE             0x80000000
#define ENVP_BASE                0x2000

#define ENVP_ADDR                ENVP_BASE
#define ENVP_NB_ENTRIES          16
#define ENVP_ENTRY_SIZE          256

#define MALTACORELVID             0x00000420

// Always two command line parameters passed
// 1 = kernel name (eg vmlinux)
// 2 = other command line arguments
#define KERNEL_COMMAND_LINE_ARGS  2
#define MEGA_BYTE                (1024*1024)
#define DEFAULT_MEMSIZE          128

#define WINDOW_KERNELARGS        ENVP_NB_ENTRIES*(4+ENVP_ENTRY_SIZE)

#define ADDRRESS_SPACE_PORT     "mport"
//#define WRITE_BOOT_VECTOR
#define BOOT_VECTOR              0x1fc00000
#define BOOT_MAPPING             0x1e000000
#define BOOT_MAX_SIZE           (1*1024*1024)

#ifndef MIN
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#endif

typedef struct tableS {
    Uns32 index[ENVP_NB_ENTRIES];
    char strings[ENVP_NB_ENTRIES][ENVP_ENTRY_SIZE];
} tableSS, *tableP;

union {
    char bytes[WINDOW_KERNELARGS];
    tableSS table;
} window_kernelargs;

Uns32 envpaddress;

ppmAddressSpaceHandle addressSpaceHandle;

// ***********************************************************

char window_bootrom[BOOT_MAX_SIZE];

/*************************************************************
 * Byte Swapping Functions
 *************************************************************/

Bool byteSwap = False;

//
// convert a half word for endian
//
static inline Uns16 BSWAP_UNS16(Uns16 p)
{
    return SWAP_2_BYTE_COND(p,byteSwap);
}

//
// convert a word for endian
//
static inline Uns32 BSWAP_UNS32_NM(Uns32 p)
{
    if (byteSwap) {
        return SWAP_4_BYTE_COND(p,byteSwap);
    } else {
        Uns16 upper = (Uns16)(p >> 16);
        Uns16 lower = (Uns16)p;
        return ((Uns32)lower << 16) | upper;
    }
}

//
// convert a word for endian
//
static inline Uns32 BSWAP_UNS32(Uns32 p)
{
    return SWAP_4_BYTE_COND(p,byteSwap);
}

#define PHYS_TO_VIRT(x) ((x) | ~(Uns32)0x7fffffff)
#define VIRT_TO_PHYS(x) ((x) &  (Uns32)0x7fffffff)

static void write_bootloader_goldfish (Uns32 kernel_entry, Uns32 kernel_args,
                              Uns32 envvp, Uns32 rams)
{
    Uns32 envva = PHYS_TO_VIRT(envvp);

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32(0x0bf00160);                                      /* j 0x1fc00580 */
    *p++ = BSWAP_UNS32(0x00000000);                                      /* nop */


    p = (Uns32 *)&window_bootrom[0x580];
    *p++ =  BSWAP_UNS32(0x3c040000 | ((envva >> 16) & 0xffff));         /* lui a0, high(ENVP_ADDR) */
    *p++ =  BSWAP_UNS32(0x34840000 | (envva & 0xffff));                 /* ori a0, a0, low(ENVP_ADDR) */
    *p++ =  BSWAP_UNS32(0x3c050000 | (rams >> 16));                     /* lui a1, high(ram_size) */
    *p++ =  BSWAP_UNS32(0x34a50000 | (rams & 0xffff));                  /* ori a1, a1, low(ram_size) */

    /* Jump to kernel code */
    *p++ =  BSWAP_UNS32(0x3c1f0000 | ((kernel_entry >> 16) & 0xffff));    /* lui ra, high(kernel_entry) */
    *p++ =  BSWAP_UNS32(0x37ff0000 | (kernel_entry & 0xffff));            /* ori ra, ra, low(kernel_entry) */
    *p++ =  BSWAP_UNS32(0x03e00009);                                      /* jalr $0,ra (in R6: jr ra) */
    *p++ =  BSWAP_UNS32(0x00000000);                                      /* nop */

}

//
// Copy code to setup gprs and BAR registers for calling the Linux kernel
// p is a pointer to an Uns32[] with sufficient space for the code
// Returns pointer to first entry in p past the loaded code
//
static Uns32 *copy_bootloader_linux_start(Uns32 *p , Uns32 kernel_entry, Uns32 kernel_args, Uns32 envva, Uns32 rams) {

    *p++ = BSWAP_UNS32(0x24040000 | kernel_args);                       /* addiu a0, zero, kernel_args*/
    *p++ = BSWAP_UNS32(0x3c1d0000 | (((envva - 64) >> 16) & 0xffff));   /* lui sp, high(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x37bd0000 | ((envva - 64) & 0xffff));           /* ori sp, sp, low(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x3c050000 | ((envva >> 16) & 0xffff));          /* lui a1, high(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x34a50000 | (envva & 0xffff));                  /* ori a1, a1, low(ENVP_ADDR) */
    *p++ = BSWAP_UNS32(0x3c060000 | (((envva + (kernel_args*4)) >> 16) & 0xffff));  /* lui a2, high(ENVP_ADDR + kernel_args*4) */
    *p++ = BSWAP_UNS32(0x34c60000 | ((envva + (kernel_args*4)) & 0xffff));          /* ori a2, a2, low(ENVP_ADDR + kernel_args*4) */
    *p++ = BSWAP_UNS32(0x3c070000 | (rams >> 16));                      /* lui a3, high(ram_size) */
    *p++ = BSWAP_UNS32(0x34e70000 | (rams & 0xffff));                   /* ori a3, a3, low(ram_size) */

    /* Load BAR registers as done by YAMON */
    *p++ = BSWAP_UNS32(0x3c09b400);                                     /* lui t1, 0xb400 */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c08df00)                           /* lui t0, 0xdf00 */
                    : 0x340800df;                                       /* ori t0, r0, 0x00df */
    *p++ = BSWAP_UNS32(0xad280068);                                     /* sw t0, 0x0068(t1) */

    *p++ = BSWAP_UNS32(0x3c09bbe0);                                     /* lui t1, 0xbbe0 */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c08c000)                           /* lui t0, 0xc000 */
                    : 0x340800c0;                                       /* ori t0, r0, 0x00c0 */
    *p++ = BSWAP_UNS32(0xad280048);                                     /* sw t0, 0x0048(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c084000)                           /* lui t0, 0x4000 */
                    : 0x34080040;                                       /* ori t0, r0, 0x0040 */
    *p++ = BSWAP_UNS32(0xad280050);                                     /* sw t0, 0x0050(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c088000)                           /* lui t0, 0x8000 */
                    : 0x34080080;                                       /* ori t0, r0, 0x0080 */
    *p++ = BSWAP_UNS32(0xad280058);                                     /* sw t0, 0x0058(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c083f00)                           /* lui t0, 0x3f00 */
                    : 0x3408003f;                                       /* ori t0, r0, 0x003f */
    *p++ = BSWAP_UNS32(0xad280060);                                     /* sw t0, 0x0060(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c08c100)                           /* lui t0, 0xc100 */
                    : 0x340800c1;                                       /* ori t0, r0, 0x00c1 */
    *p++ = BSWAP_UNS32(0xad280080);                                     /* sw t0, 0x0080(t1) */

    *p++ = byteSwap ? BSWAP_UNS32(0x3c085e00)                           /* lui t0, 0x5e00 */
                    : 0x3408005e;                                       /* ori t0, r0, 0x005e */
    *p++ = BSWAP_UNS32(0xad280088);                                     /* sw t0, 0x0088(t1) */

    /* Jump to kernel code */
    *p++ = BSWAP_UNS32(0x3c1f0000 | ((kernel_entry >> 16) & 0xffff));   /* lui ra, high(kernel_entry) */
    *p++ = BSWAP_UNS32(0x37ff0000 | (kernel_entry & 0xffff));           /* ori ra, ra, low(kernel_entry) */
    *p++ = BSWAP_UNS32(0x03e00009);                                     /* jalr $0,ra (in R6: jr ra)*/
    *p++ = BSWAP_UNS32(0x00000000);                                     /* nop */

    return p;

}

static void write_bootloader (Uns32 kernel_entry, Uns32 kernel_args,
                              Uns32 envpa, Uns32 rams)
{
    Uns32 envva = PHYS_TO_VIRT(envpa);

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32(0x0bf00160);                                      /* j 0x1fc00580 */
    *p++ = BSWAP_UNS32(0x00000000);                                      /* nop */

    /* YAMON service vector */
    p = (Uns32 *)&window_bootrom[0x500];
    *p++ =  BSWAP_UNS32(0xbfc00580);      /* start: */
    *p++ =  BSWAP_UNS32(0xbfc0083c);      /* print_count: */
    *p++ =  BSWAP_UNS32(0xbfc00580);      /* start: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* flush_cache: */
    *p++ =  BSWAP_UNS32(0xbfc00808);      /* print: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_cpu_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unred_cpu_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_ic_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unred_ic_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_esr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unreg_esr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* getchar: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* syscon_read: */

    p = (Uns32 *)&window_bootrom[0x580];
    p = copy_bootloader_linux_start(p , kernel_entry, kernel_args, envva, rams);

    /* YAMON subroutines */
    p = (Uns32 *)&window_bootrom[0x800];
    *p++ =  BSWAP_UNS32(0x03e00009);                                     /* jalr $0,ra (in R6: jr ra)*/
    *p++ =  BSWAP_UNS32(0x24020000);                                     /* li v0,0 */
   /* 808 YAMON print */
    *p++ =  BSWAP_UNS32(0x03e06821);                                     /* move t5,ra */
    *p++ =  BSWAP_UNS32(0x00805821);                                     /* move t3,a0 */
    *p++ =  BSWAP_UNS32(0x00a05021);                                     /* move t2,a1 */
    *p++ =  BSWAP_UNS32(0x91440000);                                     /* lbu a0,0(t2) */
    *p++ =  BSWAP_UNS32(0x254a0001);                                     /* addiu t2,t2,1 */
    *p++ =  BSWAP_UNS32(0x10800005);                                     /* beqz a0,834 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x0ff0021c);                                     /* jal 870 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x08000205);                                     /* j 814 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x01a00009);                                     /* jalr $0,t5 (in R6: jr t5)*/
    *p++ =  BSWAP_UNS32(0x01602021);                                     /* move a0,t3 */
    /* 0x83c YAMON print_count */
    *p++ =  BSWAP_UNS32(0x03e06821);                                     /* move t5,ra */
    *p++ =  BSWAP_UNS32(0x00805821);                                     /* move t3,a0 */
    *p++ =  BSWAP_UNS32(0x00a05021);                                     /* move t2,a1 */
    *p++ =  BSWAP_UNS32(0x00c06021);                                     /* move t4,a2 */
    *p++ =  BSWAP_UNS32(0x91440000);                                     /* lbu a0,0(t2) */
    *p++ =  BSWAP_UNS32(0x0ff0021c);                                     /* jal 870 */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x254a0001);                                     /* addiu t2,t2,1 */
    *p++ =  BSWAP_UNS32(0x258cffff);                                     /* addiu t4,t4,-1 */
    *p++ =  BSWAP_UNS32(0x1580fffa);                                     /* bnez t4,84c */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x01a00009);                                     /* jalr $0,t5 (in R6: jr t5)*/
    *p++ =  BSWAP_UNS32(0x01602021);                                     /* move a0,t3 */
    /* 0x870 */
    *p++ =  BSWAP_UNS32(0x3c08b800);                                     /* lui t0,0xb400 */
    *p++ =  BSWAP_UNS32(0x350803f8);                                     /* ori t0,t0,0x3f8 */
    *p++ =  BSWAP_UNS32(0x91090005);                                     /* lbu t1,5(t0) */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x31290040);                                     /* andi t1,t1,0x40 */
    *p++ =  BSWAP_UNS32(0x1120fffc);                                     /* beqz t1,878 <outch+0x8> */
    *p++ =  BSWAP_UNS32(0x00000000);                                     /* nop */
    *p++ =  BSWAP_UNS32(0x03e00009);                                     /* jalr $0,ra (in R6: jr ra)*/
    *p++ =  BSWAP_UNS32(0xa1040000);                                     /* sb a0,0(t0) */

    if ((char *)p > &window_bootrom[NUM_ENTRIES(window_bootrom)]) {
        bhmMessage("F", PREFIX, "overflow of window_bootrom buffer");
    }
}

static void write_bootloader_uhi(Uns32 kernel_entry, Uns32 fdt_addr)
{
    const Uns32 cm_base  = 0x16100000;
    const Uns32 gic_base = 0x16120000;
    const Uns32 cpc_base = 0x16200000;

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32(0x40087803);                                      /* mfc0 t0, cmgcrbase */
    *p++ = BSWAP_UNS32(0x00084100);                                      /* sll  t0, t0, 4 */
    *p++ = BSWAP_UNS32(0x3c09a000);                                      /* lui  t1, high(0xa0000000) */
    *p++ = BSWAP_UNS32(0x01094025);                                      /* or   t0, t0, t1 */

    *p++ = BSWAP_UNS32(0x3c0a0000 | ((cm_base >> 16) & 0xffff));         /* lui  t2, high(cm_base) */
    *p++ = BSWAP_UNS32(0xad0a0008);                                      /* sw   t2, 8(t0) */
    *p++ = BSWAP_UNS32(0x012a4025);                                      /* or   t0, t1, t2 */

    *p++ = BSWAP_UNS32(0x3c090000 | ((gic_base >> 16) & 0xffff));        /* lui  t1, high(gic_base) */
    *p++ = BSWAP_UNS32(0x35290001);                                      /* ori  t1, 1 */
    *p++ = BSWAP_UNS32(0xad090080);                                      /* sw   t1, 0x80(t0) */

    *p++ = BSWAP_UNS32(0x3c090000 | ((cpc_base >> 16) & 0xffff));        /* lui  t1, high(cpc_base) */
    *p++ = BSWAP_UNS32(0x35290001);                                      /* ori  t1, 1 */
    *p++ = BSWAP_UNS32(0xad090088);                                      /* sw   t1, 0x88(t0) */

    *p++ = BSWAP_UNS32(0x2404fffe);                                      /* li   a0, -2 */
    *p++ = BSWAP_UNS32(0x3c050000 | ((fdt_addr >> 16) & 0xffff));        /* lui  a1, high(fdt_addr) */
    *p++ = BSWAP_UNS32(0x34a50000 | (fdt_addr & 0xffff));                /* ori  a1, low(fdt_addr) */
    *p++ = BSWAP_UNS32(0x24060000);                                      /* li   a2, 0 */
    *p++ = BSWAP_UNS32(0x24070000);                                      /* li   a3, 0 */

    *p++ = BSWAP_UNS32(0x3c190000 | ((kernel_entry >> 16) & 0xffff));    /* lui  t9, high(kernel_entry) */
    *p++ = BSWAP_UNS32(0x37390000 | (kernel_entry & 0xffff));            /* ori  t9, low(kernel_entry) */
    *p++ = BSWAP_UNS32(0x03200009);                                      /* jr   t9 */
    *p++ = BSWAP_UNS32(0x00000000);                                      /* nop */
}

#undef HI
#define HI(_A)  (((_A) & 0x001ff000) | ((((_A) & 0x7fe00000) >> 21) << 2) | (((_A) >> 31) & 1))
#undef LO
#define LO(_A)  ((_A) & 0xfff)

static void write_bootloader_goldfish_nanomips (Uns32 kernel_entry, Uns32 kernel_args,
                              Uns32 envvp, Uns32 rams)
{
    Uns32 envva = PHYS_TO_VIRT(envvp);

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32_NM(0x2800057c);                                   /* bc 0x1fc00580 */


    p = (Uns32 *)&window_bootrom[0x580];
    *p++ =  BSWAP_UNS32_NM(0xe0800000 | HI(envva));                      /* lui a0, %hi(ENVP_ADDR) */
    *p++ =  BSWAP_UNS32_NM(0x80840000 | LO(envva))       ;               /* ori a0, a0, %lo(ENVP_ADDR) */
    *p++ =  BSWAP_UNS32_NM(0xe0a00000 | HI(rams));                       /* lui a1, %hi(ram_size) */
    *p++ =  BSWAP_UNS32_NM(0x80a50000 | LO(rams));                       /* ori a1, a1, %lo(ram_size) */

    /* Jump to kernel code */
    *p++ =  BSWAP_UNS32_NM(0xe3e00000 | HI(kernel_entry));               /* lui ra, %hi(kernel_entry) */
    *p++ =  BSWAP_UNS32_NM(0x83ff0000 | LO(kernel_entry));               /* ori ra, ra, %lo(kernel_entry) */
    *p++ =  BSWAP_UNS32_NM(0x481f0000);                                  /* jrc ra */

}

//
// Copy code to setup gprs and BAR registers for calling the Linux kernel
// p is a pointer to an Uns32[] with sufficient space for the code
// Returns pointer to first entry in p past the loaded code
//
static Uns32 *copy_bootloader_linux_start_nanomips(Uns32 *p , Uns32 kernel_entry, Uns32 kernel_args, Uns32 envva, Uns32 rams) {

    *p++ = BSWAP_UNS32_NM(0x00800000 | kernel_args);                    /* lo a0, kernel_args*/
    *p++ = BSWAP_UNS32_NM(0xe3a00000 | HI(envva - 64));                 /* lui sp, %hi(ENVP_ADDR) */
    *p++ = BSWAP_UNS32_NM(0x83bd0000 | LO(envva - 64));                 /* ori sp, sp, %lo(ENVP_ADDR) */
    *p++ = BSWAP_UNS32_NM(0xe0a00000 | HI(envva));                      /* lui a1, %hi(ENVP_ADDR) */
    *p++ = BSWAP_UNS32_NM(0x80a50000 | LO(envva));                      /* ori a1, a1, %lo(ENVP_ADDR) */
    *p++ = BSWAP_UNS32_NM(0xe0c00000 | HI(envva + (kernel_args*4)));    /* lui a2, %hi(ENVP_ADDR + kernel_args*4) */
    *p++ = BSWAP_UNS32_NM(0x80a60000 | LO(envva + (kernel_args*4)));    /* ori a2, a2, %lo(ENVP_ADDR + kernel_args*4) */
    *p++ = BSWAP_UNS32_NM(0xe0e00000 | HI(rams));                       /* lui a3, %hi(ram_size) */
    *p++ = BSWAP_UNS32_NM(0x80e70000 | LO(rams));                       /* ori a3, a3, %lo(ram_size) */

    /* Load BAR registers as done by YAMON */
    *p++ = BSWAP_UNS32_NM(0xe1a00681);                                  /* lui t1, 0xb400 */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe1800be1)                        /* lui t0, %hi(0xdf000000) */
                    : BSWAP_UNS32_NM(0x018000df);                       /* li t0, 0x0df */
    *p++ = BSWAP_UNS32_NM(0x858d9068);                                  /* sw t0, 0x0068(t1) */

    *p++ = BSWAP_UNS32_NM(0xe1a0077d);                                  /* lui t1, %hi(0xbbe00000) */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe1800801)                        /* lui t0, %hi(0xc0000000) */
                    : BSWAP_UNS32_NM(0x018000c0);                       /* li t0, 0x0c0 */
    *p++ = BSWAP_UNS32_NM(0x858d9048);                                  /* sw t0, 0x0048(t1) */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe1800800)                        /* lui t0, %hi(0x40000000) */
                    : BSWAP_UNS32_NM(0x018000df);                       /* li t0, 0x040 */
    *p++ = BSWAP_UNS32_NM(0x858d9050);                                  /* sw t0, 0x0050(t1) */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe1800001)                        /* lui t0, %hi(0x80000000) */
                    : BSWAP_UNS32_NM(0x01800080);                       /* li t0, 0x080 */
    *p++ = BSWAP_UNS32_NM(0x858d9058);                                  /* sw t0, 0x0058(t1) */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe18007e0)                        /* lui t0, %hi(0x3f000000) */
                    : BSWAP_UNS32_NM(0x0180003f);                       /* li t0, 0x03f */
    *p++ = BSWAP_UNS32_NM(0x858d9060);                                  /* sw t0, 0x0060(t1) */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe1800821)                        /* lui t0, %hi(0xc1000000) */
                    : BSWAP_UNS32_NM(0x018000c1);                       /* li t0, 0x0c1 */
    *p++ = BSWAP_UNS32_NM(0x858d9080);                                  /* sw t0, 0x0080(t1) */

    *p++ = byteSwap ? BSWAP_UNS32_NM(0xe1800bc0)                        /* lui t0, %hi(0x5e000000) */
                    : BSWAP_UNS32_NM(0x0180005e);                       /* li t0, 0x05e */
    *p++ = BSWAP_UNS32_NM(0x858d9088);                                  /* sw t0, 0x0088(t1) */

    /* Jump to kernel code */
    *p++ = BSWAP_UNS32_NM(0xe3e00000 | HI(kernel_entry));               /* lui ra, %hi(kernel_entry) */
    *p++ = BSWAP_UNS32_NM(0x83ff0000 | LO(kernel_entry));               /* ori ra, ra, %lo(kernel_entry) */
    *p++ = BSWAP_UNS32_NM(0x481f0000);                                  /* jrc ra */

    return p;

}

static void write_bootloader_nanomips (Uns32 kernel_entry, Uns32 kernel_args,
                              Uns32 envpa, Uns32 rams)
{
    Uns32 envva = PHYS_TO_VIRT(envpa);

    Uns32 *p;
    Uns16 *p16;

    p16 = (Uns16 *)window_bootrom;
    *p16++ = BSWAP_UNS16(0x2800);                                        /* bc 0x1fc00580 */
    *p16++ = BSWAP_UNS16(0x057c);

    /* YAMON service vector */
    p = (Uns32 *)&window_bootrom[0x500];
    *p++ =  BSWAP_UNS32(0xbfc00580);      /* start: */
    *p++ =  BSWAP_UNS32(0xbfc0081c);      /* print_count: */
    *p++ =  BSWAP_UNS32(0xbfc00580);      /* start: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* flush_cache: */
    *p++ =  BSWAP_UNS32(0xbfc00806);      /* print: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_cpu_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unred_cpu_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_ic_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unred_ic_isr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* reg_esr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* unreg_esr: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* getchar: */
    *p++ =  BSWAP_UNS32(0xbfc00800);      /* syscon_read: */

    p = (Uns32 *)&window_bootrom[0x580];
    p = copy_bootloader_linux_start_nanomips(p , kernel_entry, kernel_args, envva, rams);

    /* YAMON subroutines */
    p16 = (Uns16 *)&window_bootrom[0x800];
    *p16++ =  BSWAP_UNS16(0xd200);                                       /* li v0,0 */
    *p16++ =  BSWAP_UNS16(0x481f);                                       /* jrc ra */
    *p16++ =  BSWAP_UNS16(0x0000);
    /* 806 YAMON print */
    *p16++ =  BSWAP_UNS16(0x107f);                                       /* move t5,ra */
    *p16++ =  BSWAP_UNS16(0x11e4);                                       /* move t3,a0 */
    *p16++ =  BSWAP_UNS16(0x11c5);                                       /* move t2,a1 */
    *p16++ =  BSWAP_UNS16(0x848e);                                       /* lbu a0,0(t2) */
    *p16++ =  BSWAP_UNS16(0x2000);
    *p16++ =  BSWAP_UNS16(0x91c9);                                       /* addiu t2,t2,1 */
    *p16++ =  BSWAP_UNS16(0x9a04);                                       /* beqzc a0,818 */
    *p16++ =  BSWAP_UNS16(0x3820);                                       /* balc 826 */
    *p16++ =  BSWAP_UNS16(0x1bf5);                                       /* bc 80c */
    *p16++ =  BSWAP_UNS16(0x108f);                                       /* move a0,t3 */
    *p16++ =  BSWAP_UNS16(0xd860);                                       /* jrc t5 */
    /* 0x81c YAMON print_count */
    *p16++ =  BSWAP_UNS16(0x107f);                                       /* move t5,ra */
    *p16++ =  BSWAP_UNS16(0x11e4);                                       /* move t3,a0 */
    *p16++ =  BSWAP_UNS16(0x11c5);                                       /* move t2,a1 */
    *p16++ =  BSWAP_UNS16(0x1046);                                       /* move t4,a2 */
    *p16++ =  BSWAP_UNS16(0x848e);                                       /* lbu a0,0(t2) */
    *p16++ =  BSWAP_UNS16(0x2000);
    *p16++ =  BSWAP_UNS16(0x380c);                                       /* balc 836 */
    *p16++ =  BSWAP_UNS16(0x91c9);                                       /* addiu t2,t2,1 */
    *p16++ =  BSWAP_UNS16(0x905f);                                       /* addiu t4,t4,-1 */
    *p16++ =  BSWAP_UNS16(0xa840);                                       /* bnezc t4,824 */
    *p16++ =  BSWAP_UNS16(0x3ff3);
    *p16++ =  BSWAP_UNS16(0x108f);                                       /* move a0,t3 */
    *p16++ =  BSWAP_UNS16(0xd860);                                       /* jrc t5 */
    /* 0x836 outch */
    *p16++ =  BSWAP_UNS16(0xe180);                                       /* lui t0,%hi(0xb4000000) */
    *p16++ =  BSWAP_UNS16(0x0681);
    *p16++ =  BSWAP_UNS16(0x818c);                                       /* ori t0,t0,0x3f8 */
    *p16++ =  BSWAP_UNS16(0x03f8);
    *p16++ =  BSWAP_UNS16(0x85ac);                                       /* lbu t1,5(t0) */
    *p16++ =  BSWAP_UNS16(0x2005);
    *p16++ =  BSWAP_UNS16(0x81ad);                                       /* andi t1,t1,0x40 */
    *p16++ =  BSWAP_UNS16(0x2040);
    *p16++ =  BSWAP_UNS16(0x89a0);                                       /* beqzc t1,83e <outch+0x8> */
    *p16++ =  BSWAP_UNS16(0x3ff5);
    *p16++ =  BSWAP_UNS16(0x848c);                                       /* sb a0,0(t0) */
    *p16++ =  BSWAP_UNS16(0x1000);
    *p16++ =  BSWAP_UNS16(0xdbe0);                                       /* jrc ra */

    if ((char *)p > &window_bootrom[NUM_ENTRIES(window_bootrom)]) {
        bhmMessage("F", PREFIX, "overflow of window_bootrom buffer");
    }
}

static void write_bootloader_uhi_nanomips(Uns32 kernel_entry, Uns32 fdt_addr)
{
    const Uns32 cm_base  = 0x16100000;
    const Uns32 gic_base = 0x16120000;
    const Uns32 cpc_base = 0x16200000;

    Uns32 *p;

    p = (Uns32 *)window_bootrom;
    *p++ = BSWAP_UNS32_NM(0x210f1830);                                   /* mfc0 a4, cmgcrbase */
    *p++ = BSWAP_UNS32_NM(0x8108c004);                                   /* sll  a4, a4, 4 */
    *p++ = BSWAP_UNS32_NM(0xe1200401);                                   /* lui  a5, %hi(0xa0000000) */
    *p++ = BSWAP_UNS32_NM(0x21284290);                                   /* or   a4, a4, a5 */

    *p++ = BSWAP_UNS32_NM(0xe1400000 | HI(cm_base));                     /* lui  a6, %hi(cm_base) */
    *p++ = BSWAP_UNS32_NM(0xf4489008);                                   /* sw   a6, 8(a4) */
                                                                         /* nop */
    *p++ = BSWAP_UNS32_NM(0x21494290);                                   /* or   a4, a5, a6 */

    *p++ = BSWAP_UNS32_NM(0xe1200000 | HI(gic_base));                    /* lui  a5, %hi(gic_base) */
    *p++ = BSWAP_UNS32_NM(0x81290001);                                   /* ori  a5, 1 */
    *p++ = BSWAP_UNS32_NM(0x85289080);                                   /* sw   a5, 0x80(a4) */

    *p++ = BSWAP_UNS32_NM(0xe1200000 | HI(cpc_base));                    /* lui  a5, %hi(cpc_base) */
    *p++ = BSWAP_UNS32_NM(0x81290001);                                   /* ori  a5, 1 */
    *p++ = BSWAP_UNS32_NM(0x85289088);                                   /* sw   a5, 0x88(a4) */

    *p++ = BSWAP_UNS32_NM(0x80808002);                                   /* li   a0, -2 */
    *p++ = BSWAP_UNS32_NM(0xe0a00000 | HI(fdt_addr));                    /* lui  a1, %hi(fdt_addr) */
    *p++ = BSWAP_UNS32_NM(0x80a50000 | LO(fdt_addr));                    /* ori  a1, %lo(fdt_addr) */
    *p++ = BSWAP_UNS32_NM(0xd300d380);                                   /* li   a2, 0 */
                                                                         /* li   a3, 0 */

    *p++ = BSWAP_UNS32_NM(0xe3200000 | HI(kernel_entry));                /* lui  t9, %hi(kernel_entry) */
    *p++ = BSWAP_UNS32_NM(0x83390000 | LO(kernel_entry));                /* ori  t9, %lo(kernel_entry) */
    *p++ = BSWAP_UNS32_NM(0xdb209008);                                   /* jrc  t9 */
                                                                         /* nop */
}

static void write_bootimage (char *imageFile)
{
    FILE *fileout= fopen(imageFile, "w");
    // fail if we cannot open file
    if(!fileout) {
        bhmMessage("E", PREFIX, "Could not write fl file '%s'", imageFile);
    }

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Started boot image output to '%s'", imageFile);

    int idx;
    int address = -1;
    Uns32 *p = (Uns32 *)window_bootrom;
    for (idx=0; idx < BOOT_MAX_SIZE; idx++) {
        //printf("idx=%08x address=%08x *p=%08x\n", idx, address, *p);
        // Skip all zero address fields
        if (p[idx] != 0) {
            // if this address is not contiguous - output the address
            if (address++ != idx) {
                fprintf(fileout, "@%08x\n", idx*4);
                address = idx;
            }
            fprintf(fileout, "%08x\n", p[idx]);
        }
    }
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Completed boot image output to '%s'", imageFile);

    fclose(fileout);
}

static void read_bootimage (char *bootimage)
{
    FILE *bootimageFile;

    char *pline, line[256];
    int match;
    int byteAddress;
    int dataField;
    Uns32 *p;

    if(!(bootimageFile = fopen(bootimage, "r"))){
        bhmMessage("E", PREFIX, "Error opening bootimage file '%s' for reading", bootimage);
    }

    p = (Uns32 *)window_bootrom;

    while(fgets(line, 256, bootimageFile) != NULL) {

        pline = line;

        // Invalid chars for parsing so skip
        if (*pline=='#' || *pline=='!' || *pline=='>') {
            continue;
        }

        // Is this an address, or data
        if (*pline=='@') {
            pline++;
            match = sscanf(pline, "%8x", &byteAddress);
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX, "    load set 0x%08x", byteAddress);
            if (match == 1) {
                p = (Uns32 *)&window_bootrom[byteAddress & 0x3fffff];
            }
            continue;
        } else {
            match = sscanf(pline, "%8x", &dataField);
            *p++ = dataField;
            byteAddress+=4;
        }
    }
    fclose(bootimageFile);

}

static void prom_set(int index, const char *string, ...)
{
    va_list ap;
    Uns32 table_addr;

    if (index >= ENVP_NB_ENTRIES)
        return;

    if (string == NULL) {
        window_kernelargs.table.index[index] = 0;
        return;
    }

    table_addr = PHYS_TO_VIRT(envpaddress) + (4 * ENVP_NB_ENTRIES) + (index * ENVP_ENTRY_SIZE);

    window_kernelargs.table.index[index] = BSWAP_UNS32(table_addr);

    va_start(ap, string);
    vsnprintf (&window_kernelargs.table.strings[index][0], ENVP_ENTRY_SIZE, string, ap);
    va_end(ap);

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Kernel Command String, index %d, string '%s' table.index[%d]=%08x, table.strings[%d][]='%s' (%d)",
                                index, string,
                                index, window_kernelargs.table.index[index],
                                index, &window_kernelargs.table.strings[index][0],
                                (int)strlen((const char *)&window_kernelargs.table.strings[index][0])
                                );
}


/* return the size or -1 if error */
int getFileSize(const char * filetype, const char * filename)
{
    int fd, size;
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open %s '%s'", filetype, filename);
    }
    size = lseek(fd, 0, SEEK_END);
    close(fd);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Get %s Size: size %d of filename '%s'", filetype, size, filename);

    return size;
}

#define BYTES_PER_ACCESS  128
#ifndef O_BINARY
#define O_BINARY 0
#endif

/* return the size or 0 if error */
int load_file(const char *filetype, const char *filename, void **bufferP)
{
    Int32 fd, size;
    void * buffer;
    *bufferP = NULL;

    fd = open(filename, O_RDONLY | O_BINARY);
    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open %s '%s'", filetype, filename);
        return 0;
    }
    size = lseek(fd, 0, SEEK_END);
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Load %s: filename '%s' %u bytes", filetype, filename, size);
    }

    buffer = malloc(size);
    if (!buffer) {
        bhmMessage("E", PREFIX, "Cannot allocate %u bytes for %s '%s'", size, filetype, filename);
        close(fd);
        return 0;
    }

    lseek(fd, 0, SEEK_SET);
    if (read(fd, buffer, size) < 0) {
        bhmMessage("E", PREFIX, "Cannot read %u bytes for %s '%s'", size, filetype, filename);
        free(buffer);
        close(fd);
        return 0;
    }
    close(fd);

    *bufferP = buffer;

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Load %s: filename '%s' completed (%u bytes loaded)", filetype, filename, size);
    }

    return size;
}

/* return the size or -1 if error */
int load_image(const char *filename, Uns32 addr)
{
    Uns32 bytes;
    Uns32 dest = addr;
    char buff[BYTES_PER_ACCESS];
    Int32 fd, size;

    fd = open(filename, O_RDONLY | O_BINARY);
    if (fd < 0) {
        bhmMessage("E", PREFIX, "Cannot open Image %s", filename);
        return 0;
    }
    size = lseek(fd, 0, SEEK_END);
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Load Image: filename %s %u bytes to load to 0x%08x", filename, size, dest);
    lseek(fd, 0, SEEK_SET);

    bytes = size;
    while (bytes) {
        Uns32 thisAccess = (bytes > BYTES_PER_ACCESS) ? BYTES_PER_ACCESS : bytes;
        thisAccess = read(fd, buff, thisAccess);
        if(!ppmWriteAddressSpace(addressSpaceHandle, (Int64)(Int32)dest, thisAccess, buff)){
            bhmMessage("E", PREFIX, "Load Image: Failed to write %u bytes to 0x%08x", thisAccess, dest);
            return 0;
        }
        dest  += thisAccess;
        bytes -= thisAccess;
    }
    close(fd);
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Load Image: filename %s completed (%u bytes loaded)", filename, size);
    return size;
}

Uns32 idWindow;
PPM_READ_CB(readBoardId) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read Malta Board Id 0x%x", idWindow);
    return idWindow;
}
PPM_WRITE_CB(writeBoardId) {
    if(PSE_DIAG_LOW)
        bhmMessage("W", PREFIX, "Write to Malta Board Id location");
}

static void setBoardId() {

    Uns32 boardID;
    if(bhmUns32ParamValue("boardid", &boardID)) {
        idWindow = BSWAP_UNS32(boardID);
    } else {
        idWindow = BSWAP_UNS32(MALTACORELVID);
    }

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Set Malta Board Id 0x%x", idWindow);
    }
}

//
// write linux startup code to the indicated address
//
static void write_bootloader_linux_start(Uns32 fixupAddress, Uns32 kernel_entry, Uns32 kernel_args, Uns32 envvp, Uns32 rams) {

    Uns32 envva = PHYS_TO_VIRT(envvp);
    Uns32 kernelStartUp[32*4];

    // Get linux startup code
    Uns32 *p = copy_bootloader_linux_start(kernelStartUp, kernel_entry, kernel_args, envva, rams);

    if (p > &kernelStartUp[NUM_ENTRIES(kernelStartUp)]) {
        bhmMessage("F", PREFIX, "overflow of kernelStartUp buffer");
    }

    // Write linux startup code to indicated memory location
    if(!ppmWriteAddressSpace(addressSpaceHandle, VIRT_TO_PHYS(fixupAddress), sizeof(kernelStartUp), kernelStartUp)){
        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(kernelStartUp),VIRT_TO_PHYS(fixupAddress));
    }

}

//
// write linux startup code to the indicated address
//
static void write_bootloader_linux_start_nanomips(Uns32 fixupAddress, Uns32 kernel_entry, Uns32 kernel_args, Uns32 envvp, Uns32 rams) {

    Uns32 envva = PHYS_TO_VIRT(envvp);
    Uns32 kernelStartUp[32*4];

    // Get linux startup code
    Uns32 *p = copy_bootloader_linux_start_nanomips(kernelStartUp, kernel_entry, kernel_args, envva, rams);

    if (p > &kernelStartUp[NUM_ENTRIES(kernelStartUp)]) {
        bhmMessage("F", PREFIX, "overflow of kernelStartUp buffer");
    }

    // Write linux startup code to indicated memory location
    if(!ppmWriteAddressSpace(addressSpaceHandle, VIRT_TO_PHYS(fixupAddress), sizeof(kernelStartUp), kernelStartUp)){
        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(kernelStartUp),VIRT_TO_PHYS(fixupAddress));
    }

}

static Uns32 createKernelInitialisation(char * kernelfile, Uns32 kernel_entry, Uns32 kernel_low, Uns32 kernel_high, Uns32 *fdtAddrP, Bool goldfish){

    char dtbfile[BHM_MAX_PATH];
    char initrdfile[BHM_MAX_PATH];
    char rootHDA[128];
    char memsizeString[32];
    Uns32 memsize;
    Uns32 useDTB = 0;
    Uns32 useInitRD = 0;
    Uns32 useHDABoot = 0;
    Uns32 index = 0;

    // read the base address for ENVP
    if(!bhmUns32ParamValue("envpaddress", &envpaddress)){
        envpaddress = ENVP_ADDR;
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX, "Default ENVP Address being used 0x%08x", envpaddress);
        }
    }
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "ENVP Address 0x%08x", envpaddress);
    }

    if(!bhmUns32ParamValue("memsize", &memsize)){
        memsize = DEFAULT_MEMSIZE;    // default is 128MBytes
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX, "Default Memory size being used %u MBytes", memsize);
        }
    }
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Memory size %u MBytes (0x%08x)", memsize, memsize*MEGA_BYTE);
    }
    sprintf(memsizeString, "%u", memsize*MEGA_BYTE);

    /* Override page size if requested */
    if(!bhmUns32ParamValue("pagebits", &targetPageBits)){
        targetPageBits = TARGET_PAGE_BITS_DEFAULT;
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX, "Default page bits being used %u", targetPageBits);
        }
    }
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Page bits %d (page size %dKB)", targetPageBits, TARGET_PAGE_SIZE/1024);
    }

    // check for a DTB file
    useDTB = bhmStringParamValue("dtb", dtbfile, sizeof(dtbfile));
    if(useDTB && !(*dtbfile)) {
        bhmMessage("W", PREFIX, "Boot Method 'dtb' set to Null");
        useDTB = False;
    }

    // check for an initrd file
    useInitRD = bhmStringParamValue("initrd", initrdfile, sizeof(initrdfile));
    if(useInitRD && !(*initrdfile)) {
        bhmMessage("W", PREFIX, "Boot Method 'initrd' set to Null");
        useInitRD = False;
    }

    // check for boot from root on disk
    useHDABoot = bhmStringParamValue("root", rootHDA, sizeof(rootHDA));
    if(useHDABoot && !(*rootHDA)) {
        bhmMessage("W", PREFIX, "Boot Method 'root' set to Null");
        useHDABoot = False;
    }

// Allow both for Debian Stretch boot set root but also load init ramdisk
//    if(!(useHDABoot ^ useInitRD)) {
//        bhmMessage("E", PREFIX, "Error in boot method specified. "
//                                "Must specify one of 'initrd' or 'root' attribute. "
//                                "initrd '%s' root '%s'",
//                                useInitRD ? initrdfile : "not specified",
//                                useHDABoot ? rootHDA : "not specified");
//        return 0;
//    }

    /***** Create the Kernel Command String */
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Create kernel Command String");
    }

    char cmdStr[ENVP_ENTRY_SIZE] = "";

    /* Add any user defined commands */
    bhmStringParamValue("command", cmdStr, sizeof(cmdStr));

    /* Build up boot command line */
    if(useHDABoot) {
        Uns32 len = strlen(cmdStr);
        snprintf(cmdStr+len, sizeof(cmdStr)-len, " root=%s", rootHDA);
    }

    Bool useInitrdHighMemory;
    bhmBoolParamValue("initrdhigh", &useInitrdHighMemory);

    Uns32 dtb_size = 0;
    Uns32 fdt_size = 0;
    
    if (useInitrdHighMemory) {
        *fdtAddrP = (memsize*MEGA_BYTE) + VIRTUAL_BASE;
    } else {
        *fdtAddrP = TARGET_PAGE_ALIGN_UP(kernel_high);
    }

    if (useDTB) {
        dtb_size = getFileSize("DTB", dtbfile);
        fdt_size = dtb_size * 2;
        if (useInitrdHighMemory) {
            *fdtAddrP = TARGET_PAGE_ALIGN_DOWN(*fdtAddrP - fdt_size);
        }
        if(PSE_DIAG_MEDIUM) {
	        bhmMessage("I", PREFIX, "Loading DTB '%s' at 0x%08x kernel 0x%08x  (memsize %u MB 0x%08x size %d)",
                    dtbfile, *fdtAddrP, kernel_high, memsize, memsize*MEGA_BYTE, fdt_size);
        }

        if((kernel_high) >= (*fdtAddrP)) {
            bhmMessage("E", PREFIX, "Cannot load DTB '%s' at 0x%08x, kernel is at 0x%08x",
                    dtbfile, *fdtAddrP, kernel_high);
        }
    }

    if (useInitRD) {
        Uns32 size;
        Uns32 initrd_offset;

        size = getFileSize("Image", initrdfile);

        if(useInitrdHighMemory) {
            initrd_offset = TARGET_PAGE_ALIGN_DOWN(*fdtAddrP - size);
        } else {
            initrd_offset = TARGET_PAGE_ALIGN_UP(*fdtAddrP + fdt_size);
        }
        if(PSE_DIAG_MEDIUM) {
	        bhmMessage("I", PREFIX, "Loading initrd '%s' at 0x%08x kernel 0x%08x  (memsize %u MB 0x%08x size %d)",
                    initrdfile, initrd_offset, kernel_high, memsize, memsize*MEGA_BYTE, size);
        }

        if((kernel_high) >= (initrd_offset)) {
            bhmMessage("E", PREFIX, "Cannot load initrd '%s' at 0x%08x, kernel is at 0x%08x",
                    initrdfile, initrd_offset, kernel_high);
        }

        size = load_image(initrdfile, initrd_offset-VIRTUAL_BASE);

        Uns32 len = strlen(cmdStr);
        snprintf(cmdStr+len, sizeof(cmdStr)-len, " rd_start=0x%08x rd_size=%u", initrd_offset, size);
    }

    if (useDTB) {
        void *dtb = NULL;
        void *fdt = NULL;
        int result;

        do {
            if (load_file("DTB", dtbfile, &dtb) <= 0) {
                break;
            }

            fdt = malloc(fdt_size);
            if (!fdt) {
                bhmMessage("E", PREFIX, "Cannot allocate %u bytes for FDT", fdt_size);
                break;
            }

            result = fdt_open_into(dtb, fdt, fdt_size);
            if (result < 0) {
                bhmMessage("E", PREFIX, "Failed load DTB '%s'; %d", dtbfile, result);
                break;
            }

            result = fdt_path_offset(fdt, "/chosen");
            if (result < 0) {
                bhmMessage("E", PREFIX, "Could not find FDT node '/chosen'");
                break;
            }

            result = fdt_setprop_string(fdt, result, "bootargs", cmdStr);
            if (result < 0) {
                bhmMessage("E", PREFIX, "Could not set FDT /chosen/bootargs = %s", cmdStr);
                break;
            }

            Uns32 memorybytes = memsize * MEGA_BYTE;
            Uns32 low_ram_size = MIN(256 * MEGA_BYTE, memorybytes);
            Uns32 high_ram_size = memorybytes - low_ram_size;

            result = fdt_path_offset(fdt, "/memory@0");
            if (result < 0) {
                bhmMessage("E", PREFIX, "Could not find FDT node '/memory@0'");
                break;
            }

            // Assume host is little endian. So always swap.
            Uns32 memory[] = {
                0,
                cpu_to_fdt32(low_ram_size),
                cpu_to_fdt32(0x90000000),
                cpu_to_fdt32(high_ram_size),
            };

            result = fdt_setprop(fdt, result, "reg", memory, sizeof(memory));
            if (result < 0) {
                bhmMessage("E", PREFIX, "Could not set FDT /memory@0/reg");
                break;
            }

            fdt_size = fdt_totalsize(fdt);
            if(!ppmWriteAddressSpace(addressSpaceHandle, (Int64)(Int32)(*fdtAddrP - VIRTUAL_BASE), fdt_size, fdt)){
                bhmMessage("E", PREFIX, "Load DTB: Failed to write %u bytes to 0x%08x", fdt_size, (*fdtAddrP - VIRTUAL_BASE));
                break;
            }
        } while (False);

        if (dtb) {
            free(dtb);
        }

        if (fdt) {
            free(fdt);
        }
    } else {
        if (!goldfish) {
             /* Store command line.  */
            prom_set(index++, kernelfile);

            prom_set(index++, cmdStr);

            /* Setup minimum environment variables */
            prom_set(index++, "memsize");
            prom_set(index++, memsizeString);
            prom_set(index++, "modetty0");
            prom_set(index++, "38400n8r");

            /* Terminate kernel command line*/
            prom_set(index, NULL);            // always last

            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, "Kernel Command String Arguments %u", index);
            }

            // copy out to memory
            if(!ppmWriteAddressSpace(addressSpaceHandle, envpaddress, sizeof(window_kernelargs), (char *)&window_kernelargs.bytes)) {
                bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_kernelargs), envpaddress);
                return 0;
            }
        } else {
            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, "Kernel Command String '%s'", cmdStr);
            }

            // copy out to memory
            if (!ppmWriteAddressSpace(addressSpaceHandle, envpaddress, sizeof(cmdStr), (char *)&cmdStr)) {
                bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(cmdStr), envpaddress);
                return 0;
            }
        }
    }

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Initialized Kernel Arguments");
    return memsize;
}


static void getEndian() {
    char endianString[8];
    // check for an endian
    Bool setEndian = bhmStringParamValue("endian", endianString, sizeof(endianString));
    if(setEndian){
        if(!strcmp(endianString, "big")){
            byteSwap = True;
        }
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX, "Endian attribute found : Set Endian %s", byteSwap ? "BIG" : "LITTLE");
        }
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmEventHandle finished = bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION);
    bhmEventHandle started  = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);

    char kernelfile[BHM_MAX_PATH];
    Uns32 memsize = DEFAULT_MEMSIZE;

    addressSpaceHandle = handles.mport;

    Bool disable;
    bhmBoolParamValue("disable", &disable);
    if(disable){
        bhmMessage("W", PREFIX, "Platform Initialization Disabled");
    } else {

        getEndian();

        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Opening port %s", ADDRRESS_SPACE_PORT);
        }

        if(!addressSpaceHandle) {
            bhmMessage("F", PREFIX, "Failed to open port %s\n", ADDRRESS_SPACE_PORT);
        }

        Bool bootGenerationDisabled;
        bhmBoolParamValue("disablebootgen", &bootGenerationDisabled);
        if(bootGenerationDisabled){
            bhmMessage("I", PREFIX, "Boot loader code generation disabled");
        }

        // Check to see if we are modelling the goldfish platform
        Bool goldfish;
        bhmBoolParamValue("goldfish", &goldfish);

        char dtb[256];
        char *dtbP = NULL;
        if (bhmStringParamValue("dtb", dtb, sizeof(dtb))) {
            dtbP = dtb;
        }

        // Always read the boot loader file, if specified
        char bootimage[256];
        char *bootimageP = NULL;
        if (bhmStringParamValue("bootimage", bootimage, sizeof(bootimage))) {
            if(PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "Loading 'bootimage %s", bootimage);
            }
            read_bootimage(bootimage);
            bootimageP = bootimage;

            // copy out to memory (mapped space)
            if(!ppmWriteAddressSpace(addressSpaceHandle, goldfish ? BOOT_VECTOR : BOOT_MAPPING, sizeof(window_bootrom), window_bootrom)){
                bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_MAPPING);
            }
#ifdef WRITE_BOOT_VECTOR
            if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
            }
#endif
        }


        bhmWaitEvent(started);

        // Check to see if we are running Linux or want to load a standalone application
        // if stand alone we only need to generate the boot loader
        Bool noLinux;
        bhmBoolParamValue("nonelinux", &noLinux);

        if(!noLinux) {

            // check for kernel (or if none linux the executable)
            bhmStringParamValue("kernel", kernelfile, sizeof(kernelfile));

            if(PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Opening kernel file '%s'", kernelfile);
            }

            int fd = open(kernelfile, O_RDONLY);
            if (fd < 0) {
                bhmMessage("E", PREFIX, "Could not open kernel file '%s' for reading", kernelfile);
                return;
            }

            Uns32 kernel_entry, kernel_low, kernel_high;
            if (read_elf(fd, &kernel_entry, &kernel_low, &kernel_high) < 0) {
                bhmMessage("E", PREFIX, "Failed to extract required data from kernel file %s", kernelfile);
                return;
            }
            close(fd);

            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, "Information from kernel '%s': entry 0x%08x, low 0x%08x, high 0x%08x", kernelfile, kernel_entry, kernel_low-VIRTUAL_BASE, kernel_high-VIRTUAL_BASE);
            }

            Uns32 fdt_addr = 0;
            if(!(memsize = createKernelInitialisation(kernelfile, kernel_entry, kernel_low, kernel_high, &fdt_addr, goldfish))) {
                return;
            }

            if(dtbP) {
                if (nanoMIPS) {
                    write_bootloader_uhi_nanomips (kernel_entry, fdt_addr);
                } else {
                    write_bootloader_uhi (kernel_entry, fdt_addr);
                }
                if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                    bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
                    return;
                }
            } else if(goldfish){
                if (nanoMIPS) {
                    write_bootloader_goldfish_nanomips (kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                } else {
                    write_bootloader_goldfish (kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                }
                if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                    bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
                    return;
                }
            } else {
                // no boot loader specified, so write
                if(!bootimageP && !bootGenerationDisabled) {
                    if (nanoMIPS) {
                        write_bootloader_nanomips(kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                    } else {
                        write_bootloader(kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                    }
                    // copy out to memory (mapped space)
                    if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_MAPPING, sizeof(window_bootrom), window_bootrom)){
                        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_MAPPING);
                        return;
                    }
#ifdef WRITE_BOOT_VECTOR
                    if(!ppmWriteAddressSpace(addressSpaceHandle, BOOT_VECTOR, sizeof(window_bootrom), window_bootrom)){
                        bhmMessage("E", PREFIX, "Failed to write %u bytes to 0x%08x", (Uns32)sizeof(window_bootrom),BOOT_VECTOR);
                        return;
                    }
#endif
                }

                Uns32 fixupStart = 0;
                if(bhmUns32Attribute("fixuplinuxstart", &fixupStart)) {
                    // this overwrites parts of the ROM image loaded above
                    if (nanoMIPS) {
                        write_bootloader_linux_start_nanomips(fixupStart, kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                    } else {
                        write_bootloader_linux_start(fixupStart, kernel_entry, KERNEL_COMMAND_LINE_ARGS, envpaddress, memsize);
                    }
                }

            }

        }

        char bootFL[BHM_MAX_PATH];
        if (bhmStringParamValue("writebootimage", bootFL, sizeof(bootFL))) {
            if(PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Creating boot fl file '%s'", bootFL);
            }
            write_bootimage(bootFL);
        }

    }// disabled

    setBoardId();// This will write the board ID into the window_bootrom

    if(addressSpaceHandle) {
        ppmCloseAddressSpace(addressSpaceHandle);
    }

    /****************************************************************************/


    // now sit and wait for end of simulation
    bhmWaitEvent(finished);
    return;
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

