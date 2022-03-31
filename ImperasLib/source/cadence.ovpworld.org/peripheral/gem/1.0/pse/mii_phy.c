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

#include "pse.igen.h"
#include "string.h"

#include "net.h"
#include "gem.h"

typedef struct PhyStateS {
    Uns32 ethHandle;

} PhyStateT;


static PhyStateT phyState;

#define NUM_FRAMES 8

Uns8 rxBuf[NUM_FRAMES][8192];
Uns16 rxLen[NUM_FRAMES];
Uns8 rdIndex, wrIndex;

Uns32 readFrame(Uns8 *buffer, Uns32 bufSize)
{
    if (rdIndex == wrIndex)
    {
        return 0;
    }

    unsigned int len = rxLen[rdIndex] < bufSize ? rxLen[rdIndex] : bufSize;
    memcpy(buffer, rxBuf[rdIndex], len);

    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Rx Frame Read idx %u bytes written %u", rdIndex, len);

    rdIndex++;
    if (rdIndex >= NUM_FRAMES) rdIndex = 0;

    return len;
}

Bool isLinkUp(void)
{
    return phyState.ethHandle != (Uns32)(-1);
}

static BHM_ETHER_PACKET_CB(rxFrame) {

    if (!isLinkUp()) {
        return;
    }

    if (((wrIndex + 1) % NUM_FRAMES) == rdIndex) {
        // Buffer full
        if (PSE_DIAG_LOW) bhmMessage("W", PREFIX, "Ethernet Rx Buffer Full");
        return;
    }

    memcpy (rxBuf[wrIndex], data, bytes);
    rxLen[wrIndex] = bytes;
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Rx Frame Buffer idx %u bytes written %u", wrIndex, bytes);

    wrIndex++;
    if (wrIndex >= NUM_FRAMES) wrIndex = 0;
}

void phyInit()
{
    phyState.ethHandle = bhmEthernetOpenAuto();
    bhmEthernetInstallCB(phyState.ethHandle, rxFrame, 0);
    rdIndex = 0;
    wrIndex = 0;
}

void phyWriteData(void *data, unsigned int len)
{
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Writing %u bytes to the PHY\n", len);

    // TODO: loopback when enabled

    // check link status?
    if (!isLinkUp()) {
        if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX, "Link is down while writing to PHY; dropping\n");
            //bport1_ab_data.net_status.bits.pcs_link_state = 0; // FIXME:
        return;
    }

    // write to the backend
    bhmEthernetWriteFrame(phyState.ethHandle, data, len);
}

unsigned int phyReadFrame(void *buf, unsigned int bufSize)
{
    // check link status?
    if (!isLinkUp()) {
        return 0U;
    }

    // read from the backend
    unsigned int len = readFrame(buf, bufSize);
    if ((len > 0U) && PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Read %u bytes from the PHY\n", len);
    return len;
}


void mdioWrite(Uns8 reg, Uns16 data) {


    switch(reg) {
        case MII_BMCR:
            data = data & ~0x8000; //~0x827F;
            break;
    }
    ((Uns16*) &phyport_ab_data)[reg] = data;

}

Uns16 mdioRead(Uns8 reg) {
    Uns16 data =   ((Uns16*) &phyport_ab_data)[reg] ;

    return data;
}
