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


#ifndef USER_DEFINES_H_
#define USER_DEFINES_H_


#define S_TX_FIFO (BPORT1_AB_STATUS_S_TXACTIVE        \
                 | BPORT1_AB_STATUS_S_TXFIFOHALFEMPTY \
                 | BPORT1_AB_STATUS_S_TXFIFOFULL      \
                 | BPORT1_AB_STATUS_S_TXFIFOEMPTY     \
                 | BPORT1_AB_STATUS_S_TXDATAAVLBL)

#define S_RX_FIFO (BPORT1_AB_STATUS_S_RXACTIVE        \
                 | BPORT1_AB_STATUS_S_RXFIFOHALFFULL  \
                 | BPORT1_AB_STATUS_S_RXFIFOFULL      \
                 | BPORT1_AB_STATUS_S_RXFIFOEMPTY     \
                 | BPORT1_AB_STATUS_S_RXDATAAVLBL)


#define RWORD(n) ((response[n + 0] << 24) |  \
                  (response[n + 1] << 16) |  \
                  (response[n + 2] <<  8) |  \
                  (response[n + 3]      ))

#define FIFO_LEN   16
#define PREFIX     "PL181"

#define PORT_NAME  "bport1"

#endif /* USER_DEFINES_H_ */
