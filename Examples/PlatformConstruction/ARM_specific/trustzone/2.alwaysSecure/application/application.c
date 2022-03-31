/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <stdio.h>

// UART Registers
#define UART_BASE 0x10000000
#define UART_TX   ((volatile unsigned char *) (UART_BASE + 0x0 ))
#define UART_FR   ((volatile unsigned char *) (UART_BASE + 0x18))

// virtual memory translation table
unsigned int translationTable[4096] __attribute__ ((aligned (16384)));

// CP15 register access
#define WR_CP15(_OP1, _CRN, _CRM, _OP2, _VAL) \
    asm volatile("mcr p15, "#_OP1", %0, "#_CRN", "#_CRM", "#_OP2::"r"(_VAL))

#define RD_CP15(_OP1, _CRN, _CRM, _OP2, _VAL) \
    asm volatile("mrc p15, "#_OP1", %0, "#_CRN", "#_CRM", "#_OP2:"=r"(_VAL))

#define WR_SCTLR(_VAL) WR_CP15(0, c1, c0, 0, _VAL)
#define RD_SCTLR(_VAL) RD_CP15(0, c1, c0, 0, _VAL)
#define WR_SCR(_VAL)   WR_CP15(0, c1, c1, 0, _VAL)
#define RD_SCR(_VAL)   RD_CP15(0, c1, c1, 0, _VAL)
#define WR_TTBR0(_VAL) WR_CP15(0, c2, c0, 0, _VAL)
#define WR_DACR(_VAL)  WR_CP15(0, c3, c0, 0, _VAL)

// Add a section entry to the translation table mapping 1MB
// starting at VA to physical address PA
void addSection(unsigned int VA, unsigned int PA) {

    unsigned int index  = (VA >> 20);
    unsigned int entry  = (PA & 0xfff00000)             |  // Section base address
                          0x3 << 10                     |  // AP = read/write
                          0x2;                             // Section entry, PXN=0

    // Set the entry in the table to be a section
    translationTable[index] = entry;

}

// Setup translation table entries for first 2MB of memory and UART addresses
void setupTranslationTable() {
    addSection(0x00000000, 0x00000000);
    addSection(0x00100000, 0x00100000);
    addSection(UART_BASE, UART_BASE);
}

// Enable the TLB
void enableTLB() {

    // Write the translation table base register
    WR_TTBR0((unsigned int)translationTable);

    // Set DACR to 1 to enable client permissions for domain 0
    WR_DACR(1);

    // Set SCTLR.M (bit 0) to enable TLB
    unsigned int sctlr;
    RD_SCTLR(sctlr);
    WR_SCTLR(sctlr | 1);

}

// Enter non-secure mode by setting SCR.NS (bit 0)
void enterNonSecure() {
    unsigned int scr;
    RD_SCR(scr);
    WR_SCR(scr | 1);
}

// Write a string to the UART TX register
void putString(const char *s) {
    while (*s) {
        while ((*UART_FR & 0x80) == 0) {
            // Wait for Tx Holding Register Empty flag
        }
        *UART_TX = *s++;
    }
}

int main() {

    // Setup and enable the secure mode TLB
    // Note: Processor starts out in secure mode
    setupTranslationTable();
    enableTLB();

    printf ("\n*** Writing to uart from Secure Mode\n");
    putString("Hello from secure mode!\n");

    printf ("\n*** Entering Non-Secure Mode\n");
    enterNonSecure();

    // Enable the non-secure TLB (uses same translation table as secure mode)
    enableTLB();

    printf ("\n*** Writing to uart from Non-Secure Mode\n");
    putString("Hello from non-secure mode!\n");

}
