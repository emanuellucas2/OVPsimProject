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


#ifndef MII_PHY_H
#define MII_PHY_H


#ifdef _PSE_
#    include "peripheral/impTypes.h"
#else
#    include "hostapi/impTypes.h"
#endif

void phyWriteData(void *data, unsigned int len);

unsigned int phyReadFrame(void *buf, unsigned int bufSize);

void mdioWrite(Uns8 reg, Uns16 data);

Uns16 mdioRead(Uns8 reg);

Bool isLinkUp(void);


void phyInit();


// From linux kernel 4.4.0 mii.h
/* Generic MII registers. */
#define MII_BMCR         0x00    /* Basic mode control register */
#define MII_BMSR         0x01    /* Basic mode status register  */
#define MII_PHYSID1      0x02    /* PHYS ID 1                   */
#define MII_PHYSID2      0x03    /* PHYS ID 2                   */
#define MII_ADVERTISE    0x04    /* Advertisement control reg   */
#define MII_LPA          0x05    /* Link partner ability reg    */
#define MII_EXPANSION    0x06    /* Expansion register          */
#define MII_CTRL1000     0x09    /* 1000BASE-T control          */
#define MII_STAT1000     0x0a    /* 1000BASE-T status           */
#define MII_MMD_CTRL     0x0d    /* MMD Access Control Register */
#define MII_MMD_DATA     0x0e    /* MMD Access Data Register */
#define MII_ESTATUS      0x0f    /* Extended Status             */
#define MII_DCOUNTER     0x12    /* Disconnect counter          */
#define MII_FCSCOUNTER   0x13    /* False carrier counter       */
#define MII_NWAYTEST     0x14    /* N-way auto-neg test reg     */
#define MII_RERRCOUNTER  0x15    /* Receive error counter       */
#define MII_SREVISION    0x16    /* Silicon revision            */
#define MII_RESV1        0x17    /* Reserved...                 */
#define MII_LBRERROR     0x18    /* Lpback, rx, bypass error    */
#define MII_PHYADDR      0x19    /* PHY address                 */
#define MII_RESV2        0x1a    /* Reserved...                 */
#define MII_TPISTATUS    0x1b    /* TPI status for 10mbps       */
#define MII_NCONFIG      0x1c    /* Network interface config    */


#endif
