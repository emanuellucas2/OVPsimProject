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


/*
 * This file defines the protocol so must be included in every model
 * and testbench that uses it.
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef struct netPacketS {

    unsigned char head;      // Contains information about the sender
    unsigned char data[6];   // Payload
    unsigned char tail;      // Incremented by each receiver

} netPacket, *netPacketP;

#endif /* COMMON_H_ */