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
#include <stdlib.h>
#include <assert.h>
#include "dataSortRegisters.h"
#include "arm7_support.h"

// this is the size in words of each data block
#define ARRAY_SIZE 0x500000

// this defines the number of interrupts that are acknowledged before the
// application exits
#define MAX_INTERRUPTS 6

volatile static Uns32 interruptCount = 0;

static Uns32 *memory;

#define LOG(_FMT, ...)  printf( "TEST DATASORT: " _FMT,  ## __VA_ARGS__)

#ifndef PERIPHERALS
#error Number of Peripherals required must be defined.
#endif

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

//
// Get memory-mapped control block base of sort peripheral 'index'
//
inline static Uns32 getControlBase(Uns32 index) {
    return DATASORTSPBASE + (index*DATASORTSPSIZE);
}

//
// Get memory-mapped data block base of sort peripheral 'index'
//
inline static Uns32 *getDataBase(Uns32 index) {
    return memory + index*ARRAY_SIZE*sizeof(Uns32);
}

//
// Generate new pseudo-random number
//
inline static Uns32 random() {
    static Uns32 lfsr = 0x1234;
    lfsr = ((lfsr >> 1) ^ (-(Int32)(lfsr & 1) & 0x8000000bu));
    return lfsr;
}

//
// Fill data block of sort peripheral 'index' with new pseudo-random data set
//
void fillRandom(Uns32 index) {

    Uns32  i;
    Uns32 *base   = getDataBase(index);

    LOG("filling 0x%x words at 0x%p with random data\n", ARRAY_SIZE, base);
    for(i = 0; i < ARRAY_SIZE; i++) {
        base[i] = random();
    }
}

//
// print a sample range from the sorted data block
//
static printSample(Uns32 index) {

    Uns32 *base   = getDataBase(index);
    Uns32  stride = ARRAY_SIZE/10;
    Uns32 *p;
    Uns32  i;

    // print a sample range from the sorted data block
    for (p=base, i=0; i<10; p+=stride, i++) {
        printf("sorted[%d] = 0x%x\n", i*stride, *p);
    }
}

//
// FIQ handler - called when any sort peripheral signals completion
//
static void fiq_handler(void *ud)
{
    Uns32 active = 0;
    Uns32 periph;

    LOG("FIQ Interrupt\n");

    // find active peripherals
    for (periph=0; periph<PERIPHERALS; periph++) {

        Uns32 controlBase = getControlBase(periph);

        LOG("check peripheral sort%d\n", periph);

        // is the indexed sort peripheral signaling an interrupt?
        if(readReg8(controlBase, DATASORTSP_AB8_START)) {

            LOG("active peripheral sort%d\n", periph);
            active |= 1<<periph;

            // print a sample range from the sorted data block
            printSample(periph);

            // increment interrupt count
            interruptCount++;

            // acknowledge interrupt
            writeReg8(controlBase, DATASORTSP_AB8_START, 0);

        }
    }

    // restart all peripherals that have signalled an interrupt unless the
    // maximum number of signalled interrupts has been reached
    if (interruptCount<MAX_INTERRUPTS) {
        for (periph=0; periph<PERIPHERALS; periph++ ) {
            if (active & (1<<periph)) {

                // refill data block with new pseudo-random data set
                // if application is in control of this
                if (APPLICATIONGENERATESDATA) {
                    LOG("reseeding peripheral sort%d\n", periph);
                    fillRandom(periph);
                }
            }
        }

        // restart all peripherals after completed reseeding data
        for (periph=0; periph<PERIPHERALS; periph++ ) {
            if (active & (1<<periph)) {

                // restart each peripheral that has signalled completion
                Uns32 controlBase = getControlBase(periph);
                LOG("restarting peripheral sort%d\n", periph);
                writeReg8(controlBase, DATASORTSP_AB8_START, 1);

            }
        }
    }
}

//
// Dhrystones benchmark code
//
int dhry();

//
// Main routine
//
int main(int argc, char **argv)
{
    // allocate memory region used by sort peripherals
    Uns32 bytes = (ARRAY_SIZE * sizeof(Uns32) * PERIPHERALS);
    memory = malloc(bytes);
    assert(memory);

    // configure FIQ interrupt handler and enable interrupts
    CPU_INIT();
    REGISTER_ISR(fiq, fiq_handler, (void *)NULL);
    ENABLE_INTERRUPTS();

    // configure each sort peripheral
    Uns32 periph;
    for (periph = 0; periph < PERIPHERALS; periph++) {

        Uns32  controlBase = getControlBase(periph);
        Uns32 *dataBase    = getDataBase(periph);

        // configure address range for sort0 peripheral
        writeReg8 (controlBase, DATASORTSP_AB8_START, 0);
        writeReg32(controlBase, DATASORTSP_AB32CH0_DATASIZE, ARRAY_SIZE);
        writeReg32(controlBase, DATASORTSP_AB32CH0_SRCADDR,  (Uns32)dataBase);

        // fill memory with pseudo-random data to sort if application is in
        // control of this
        if (APPLICATIONGENERATESDATA) {
            fillRandom(periph);
        }
    }

    // start each sort peripheral
    for (periph = 0; periph < PERIPHERALS; periph++) {
        writeReg8(getControlBase(periph), DATASORTSP_AB8_START, 1);
    }

    // execute Dhrystones as a foreground task until a certain number of
    // interrupts have been taken
    while (interruptCount<MAX_INTERRUPTS) {
        dhry();
    }

    LOG("%u interrupts received\n", interruptCount);

    return 1;
}

