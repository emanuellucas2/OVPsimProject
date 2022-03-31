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
#include <string.h>
#include <stdlib.h>

#include "dmacRegisters.h"

typedef unsigned int  Uns32;
typedef unsigned char Uns8;

#include "riscvInterrupts.h"

#define LOG(_FMT, ...)  printf( "TEST DMA: " _FMT,  ## __VA_ARGS__)

void int_init(void (*handler)()) {

	// Set MTVEC register to point to handler function in direct mode
	int handler_int = (int) handler & ~0x1;
	write_csr(mtvec, handler_int);

	// Enable Machine mode external interrupts
    set_csr(mie, MIE_MEIE);
}

void int_enable() {
    set_csr(mstatus, MSTATUS_MIE);
}

static inline void writeReg32(Uns32 address, Uns32 offset, Uns32 value)
{
    *(volatile Uns32*) (address + offset) = value;
}

static inline Uns32 readReg32(Uns32 address, Uns32 offset)
{
    return *(volatile Uns32*) (address + offset);
}

static inline void writeReg8(Uns32 address, Uns32 offset, Uns8 value)
{
    *(volatile Uns8*) (address + offset) = value;
}

static inline Uns8 readReg8(Uns32 address, Uns32 offset)
{
    return *(volatile Uns8*) (address + offset);
}

#define ENABLE      0x00000001
#define INTEN       0x00008000
// burst size is 1<<BURST_SIZE
#define BURST_SIZE       2

volatile static Uns32 interruptCount = 0;

void interruptHandler(void)
{
    LOG("Interrupt\n");
    Uns32 intStatus = readReg8(DMA_BASE, DMA_INT_TC_STATUS);    // read interrupt status

    // check channel 0 interrupts enabled and status indicates interrupt set
    if ( (readReg32(DMA_BASE, DMA_C0_CONFIGURATION) & 0x8000 ) &&
         (intStatus & 1<<0)){
        LOG("Interrupt ch0 0x%x (0x%02x)\n", readReg32(DMA_BASE, DMA_C0_CONFIGURATION),
                                             intStatus);
        writeReg32(DMA_BASE, DMA_C0_CONFIGURATION, 0);      // disable ch0 interrupt
        writeReg8(DMA_BASE, DMA_INT_TC_STATUS,     1<<0);   // clear ch0 interrupt
        interruptCount++;
    }

    // check channel 1 interrupts enabled and status indicates interrupt set
    if ( (readReg32(DMA_BASE, DMA_C1_CONFIGURATION) & 0x8000 ) &&
         (intStatus & 1<<1)){
        LOG("Interrupt ch1 0x%x (0x%02x)\n", readReg32(DMA_BASE, DMA_C1_CONFIGURATION),
                                             intStatus);
        writeReg32(DMA_BASE, DMA_C1_CONFIGURATION, 0);      // disable ch1 interrupt
        writeReg8(DMA_BASE, DMA_INT_TC_STATUS,     1<<1);   // clear ch1 interrupt
        interruptCount++;
    }
}

static void dmaBurst(Uns32 ch, void *from, void *to, Uns32 bytes)
{
    Uns32 offset = ch * DMA_CHANNEL_STRIDE;
    LOG("dmaBurst ch:%d  bytes:%d\n", ch, bytes);
    writeReg32(DMA_BASE, DMA_C0_SRC_ADDR + offset, (Uns32)from);
    writeReg32(DMA_BASE, DMA_C0_DST_ADDR + offset, (Uns32)to);
    writeReg32(DMA_BASE, DMA_C0_CONTROL  + offset, bytes);

    writeReg32(DMA_BASE, DMA_C0_CONFIGURATION + offset, ENABLE|INTEN);
}


int main(int argc, char **argv)
{
    char src1[4096] = "Hello world.";
    char dst1[4096] = "1111111111111111111111111111111111";

    char src2[4096] = "The whole world spread before you.";
    char dst2[4096] = "2222222222222222222222222222222222";

    int_init(trap_entry);
    int_enable();

    int i;
    for (i = 0; i < 3; i++) {

    	interruptCount = 0;

        writeReg8(DMA_BASE, DMA_CONFIGURATION, BURST_SIZE);     /* reset */

        LOG("initial dst1 '%s' dst2 '%s'\n", dst1, dst2);

        /* toggle strings to show changes when copying */
    	char *s1 = i&1 ? src1 : src2;
    	char *s2 = i&1 ? src2 : src1;

		/* write to DMAC registers to start burst */
		dmaBurst(0, s1, dst1, strlen(s1)+1);
		dmaBurst(1, s2, dst2, strlen(s2)+1);

		/* wait for burst to complete */
		LOG("Waiting for interrupts\n");
		while ( interruptCount < 2 ) {
			wfi();
		}
		LOG("%u interrupts received\n", interruptCount);

	    /* check results */
	    LOG("DMA result dst1 '%s' dst2 '%s'\n", dst1, dst2);
    }

    return 1;
}

