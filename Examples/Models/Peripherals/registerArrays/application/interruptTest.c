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

#include "riscvInterrupts.h"

// Set the base address before the macros are included

#define SP1   0x80000000
#define INPUTS 32

#define CHANNEL_CONTROL_ENABLE            0x01
#define CHANNEL_CONTROL_USE_PRIORITY      0x02
#define CHANNEL_CONTROL_CURRENT_PRIORITY  0xF0

#define PIN_CONTROL_ENABLE                0x01
#define PIN_CONTROL_INVERT                0x02
#define PIN_CONTROL_ASSERT                0x04
#define PIN_CONTROL_RAW  T                0x08
#define PIN_CONTROL_PRIORITY              0xF0

#define PIN_MAX_PRIORITY                  15

#include "pse.macros.igen.h"

typedef unsigned int  Uns32;
typedef unsigned char Uns8;

volatile static Uns32 interruptCount = 0;

static inline void writeReg8(Uns32 address, Uns8 value) {
    *(volatile Uns8*) (address) = value;
}

void waitInt(void);

static inline Uns8 readReg8(Uns32 address) {
    return *(volatile Uns8*) (address);
}

static void intReset(Uns32 in){
    Uns8 r = readReg8(SP1_CH_PINCONTROL(0, in));
    writeReg8(SP1_CH_PINCONTROL(0, in), r & ~PIN_CONTROL_ASSERT);
}

void interruptHandler(void) {
    printf("APP: Interrupt.\n");
    Uns32 in;
    for(in = 0; in < INPUTS; in++) {
        Uns8 r = readReg8(SP1_CH_PINCONTROL(0, in));
        if(r & PIN_CONTROL_ASSERT) {
            interruptCount++;
            printf("APP:    Pin:%u   count:%u\n", in, interruptCount);
            intReset(in);
            return;
        }
    }

    printf("APP:    Error: Interrupt source not found\n");
}


static void intInit(void) {

	// Set MTVEC register to point to handler function in direct mode
	int handler_int = (int) interruptHandler & ~0x1;
	write_csr(mtvec, handler_int);

	// Enable Machine mode external interrupts
    set_csr(mie, MIE_MEIE);

    // enable interrupts
    set_csr(mstatus, MSTATUS_MIE);
}

int main(int argc, char **argv) {
    printf( "APP: enable interrupts\n");

    writeReg8(SP1_CH_CHANNELCONTROL(0), CHANNEL_CONTROL_ENABLE|CHANNEL_CONTROL_USE_PRIORITY);

    Uns32 in;
    for(in = 0; in < 16; in++) {
        Uns32 priority = in + 1;
        if(priority <= PIN_MAX_PRIORITY) {
            printf("APP: setting pin:%2u priority:%u\n", in, priority);
            writeReg8(SP1_CH_PINCONTROL(0, in), PIN_CONTROL_ENABLE|(PIN_CONTROL_PRIORITY & (priority<<4)));
        }
    }

    intInit();
    printf( "APP: waiting for interrupts\n");

    // infinite loop running RISCV wfi instruction
    while(1) {
        waitInt();
    }

    return 1;
}

