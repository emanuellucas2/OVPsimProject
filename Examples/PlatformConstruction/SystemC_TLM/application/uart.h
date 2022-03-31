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


// Interrupt Generator
//
// CSRs:
//  INT_VALUE:
//    read  - Returns currently set interrupt lines.
//    write - Updates currently set interrupt lines.
//  INT_SET:
//    read  - Returns currently set interrupt lines.
//    write - Sets selected bits.
//  INT_CLR:
//    read  - Returns currently set interrupt lines.
//    write - Clears selected bits.

#ifndef UART_H_
#define UART_H_

// generator
#define UART_BASE 0x90000000

#define UART_RBR 0
#define UART_TBR 0
#define UART_IER 1
#define UART_IIR 2
#define UART_LCR 3
#define UART_MCR 4
#define UART_LSR 5
#define UART_MSR 6
#define UART_SCR 7

#define UART_IER_THRI   0x02    /* Enable Transmitter holding register int. */
#define UART_IER_RDI    0x01    /* Enable receiver data interrupt */

#define UART_IIR_THRI   0x02    /* Transmitter holding register empty */
#define UART_IIR_RDI    0x04    /* Receiver data interrupt */

#define UART_LSR_TEMT   0x40    /* Transmitter empty */
#define UART_LSR_THRE   0x20    /* Transmit-hold-register empty */
#define UART_LSR_DR     0x01    /* Receiver data ready */

#endif /*UART_H_*/
