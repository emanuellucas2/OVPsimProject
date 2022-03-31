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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Wed Jan 28 13:32:36 2015
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CANVERSION
#    define CANVERSION 1
#endif

#if   (CANVERSION == 1)
    //
    // PH03 CAN model version
    //
#elif (CANVERSION == 2)
    //
    // VFOREST CAN model version
    //
#endif

#define CAN_TX_DELAY 1000
#define POLL_DELAY   1000

char buf[16];
GMCTRL gmctrl                = {.reg=GMCTRL_RESET};
GMCS   gmcs                  = {.reg=GMCS_RESET};
GMCONF gmconf                = {.reg=GMCONF_RESET};
GMABTD gmabtd                = {.reg=GMABTD_RESET};
MASK   mask[5]               = {{.reg=MASK_RESET}};  // Actual registers are 1-4
CTRL   ctrl                  = {.reg=CTRL_RESET};
LEC    lec                   = {.reg=LEC_RESET};
INFO   info                  = {.reg=INFO_RESET};
ERC    erc                   = {.reg=ERC_RESET};
IE     ie                    = {.reg=IE_RESET};
INTS   ints                  = {.reg=INTS_RESET};
BRP    brp                   = {.reg=BRP_RESET};
BTR    btr                   = {.reg=BTR_RESET};
LIPT   lipt                  = {.reg=LIPT_RESET};
RGPT   rgpt                  = {.reg=RGPT_RESET};
LOPT   lopt                  = {.reg=LOPT_RESET};
TGPT   tgpt                  = {.reg=TGPT_RESET};
TS     ts                    = {.reg=TS_RESET};
MDLC   mdlc[CAN_MSG_BUFFERS] = {{.reg=MDLC_RESET}};
MCONF  mconf[CAN_MSG_BUFFERS]= {{.reg=MCONF_RESET}};
MID    mid[CAN_MSG_BUFFERS]  = {{.reg=MID_RESET}};
MCTRL  mctrl[CAN_MSG_BUFFERS]= {{.reg=MCTRL_RESET}};


//
// Receive/Transmit History List
//
#define RHLSIZE 24
#define THLSIZE 8
Uns8 rhl[RHLSIZE] = { 0 };
Uns8 liptidx=0, rgptidx=0;
Uns8 thl[THLSIZE] = { 0 };
Uns8 loptidx=0, tgptidx=0;

#define DBGL if (BHM_DIAG_LOW)
#define DBGM if (BHM_DIAG_MEDIUM)
#define DBGH if (BHM_DIAG_HIGH)

//
// Message memory 32x8 bytes = 256bytes
//
MDATA  mdata;
GMABT  gmabt                 = {.reg=GMABT_RESET};
E6A0CTL e6a0ctl              = {.reg=E6A0CTL_RESET};

//
// Virtual Can Packets
//
static vcan  vTX;
static vcanP pvTX = &vTX;
static vcanP pvRX;

#define ACCESS_TEST_V \
    if (gmctrl.rd.MBON==0) { \
        DBGM bhmMessage("I", "MBON_ACC", "Write disabled MBON==0"); \
        return; \
    }

#define ACCESS_TEST_ZERO \
    if (gmctrl.rd.MBON==0) { \
        DBGM bhmMessage("I", "MBON_ACC", "Read disabled MBON==0"); \
        return 0; \
    }

Uns32 modinc(Uns32 value, Uns32 modulus) {
    return ((value+1) % modulus);
}

void writeRHL(Uns8 mb) {
    lipt.bits.LIPT = rhl[liptidx] = mb;
    liptidx = modinc(liptidx, RHLSIZE);

    rgpt.rd.ROVF = (liptidx==rgptidx) ? 1 : rgpt.rd.ROVF;
    rgpt.rd.RHPM = (liptidx==rgptidx) ? 1 : 0;
}

void readRHL() {
    rgpt.rd.RGPT = rhl[rgptidx];
    rgptidx = modinc(rgptidx, RHLSIZE);

    rgpt.rd.RHPM = (liptidx==rgptidx) ? 1 : 0;
}

void writeTHL(Uns8 mb) {
    lopt.bits.LOPT = thl[loptidx] = mb;
    loptidx = modinc(loptidx, THLSIZE);

    tgpt.rd.TOVF = (loptidx==tgptidx) ? 1 : tgpt.rd.TOVF;
    tgpt.rd.THPM = (loptidx==tgptidx) ? 1 : 0;
}

void readTHL() {
    tgpt.rd.TGPT = thl[tgptidx];
    tgptidx = modinc(tgptidx, THLSIZE);

    tgpt.rd.THPM = (loptidx==tgptidx) ? 1 : 0;
}

#define STACK_SIZE  (256 *1024)

//
// Reset can take 550 CAN Cycles
//
Uns8 reset_stack[STACK_SIZE];
bhmThreadHandle reset_thread_handle;
static void reset_thread () {
    DBGH bhmMessage("I", "SOFT_RESET", "Enter Software Reset");
    gmctrl.rd.SR = 1;
    //
    // In reset, apply conditions
    //

    //
    // Clear the message buffers
    //
    Uns32 mb;
    for (mb=0; mb<CAN_MSG_BUFFERS; mb++) {
        mdlc[mb].reg  = MDLC_RESET;
        mconf[mb].reg = MCONF_RESET;
        mid[mb].reg   = MID_RESET;
        mctrl[mb].reg = MCTRL_RESET;
    }
    for(mb=0; mb<CAN_MSG_DATA_BYTES; mb++) {
        mdata.b[mb] = 0x00;
    }
    liptidx=0, rgptidx=0;
    loptidx=0, tgptidx=0;

    bhmWaitDelay(POLL_DELAY);
    gmctrl.rd.SR = 0;
    //
    // Out of reset
    //
    DBGH bhmMessage("I", "SOFT_RESET", "Exit Software Reset");

    return;
}

static void eval_interrupts() {
    ppmNetValue value;
    Uns8        next;

    //
    // INTTRX
    //
    value = ppmReadNet(handles.INTTRX);
    next  = (ints.rd.CINTS0 & ie.rd.CIE0);
    if (value != next) {
        DBGH if (next) bhmMessage("I", "CAN_INT", "Assert INTTRX");
        ppmWriteNet(handles.INTTRX, next);
        ppmWriteNet(handles.INTTRX, 0);
    }

    //
    // INTREC
    //
    value = ppmReadNet(handles.INTREC);
    next  = (ints.rd.CINTS1 & ie.rd.CIE1);
    if (value != next) {
        DBGH if (next) bhmMessage("I", "CAN_INT", "Assert INTREC");
        ppmWriteNet(handles.INTREC, next);
        ppmWriteNet(handles.INTREC, 0);
    }

    //
    // INTERR CINTS 2,3,4
    //
    value = ppmReadNet(handles.INTERR);
    next = (ints.rd.CINTS2 & ie.rd.CIE2)
         | (ints.rd.CINTS3 & ie.rd.CIE3)
         | (ints.rd.CINTS4 & ie.rd.CIE4);
    if (value != next) {
        DBGH if (next) bhmMessage("I", "CAN_INT", "Assert INTERR");
        ppmWriteNet(handles.INTERR, next);
        ppmWriteNet(handles.INTERR, 0);
    }

    //
    // INTWUP
    //
    value = ppmReadNet(handles.INTWUP);
    next  = (ints.rd.CINTS5 & ie.rd.CIE5);
    if (value != next) {
        DBGH if (next) bhmMessage("I", "CAN_INT", "Assert INTWUP");
        ppmWriteNet(handles.INTWUP, next);
        ppmWriteNet(handles.INTWUP, 0);
    }
}

static void rx_remote_frame() {
}

static void rx_data_frame() {
    Uns32 VCID  = 0;
    Uns8  VCDLC = 0;

    // ID and DLC
    VCID  = pvRX->frame.data.arb.bits.ID_28_18;
    if (pvRX->frame.data.arb.bits.IDE) {
        // Extended ID
        VCID  = (VCID << 18) | pvRX->frame.data.arb.bits.ID_17_00;
    }
    VCDLC = pvRX->frame.data.ctrl.bits.DLC;

    //
    // What indicates a receive mode ?
    //
    Uns8 mb;
    for (mb=0; mb<CAN_MSG_BUFFERS; mb++) {
        //
        // Enabled and in receive mode
        //
        Uns8 MT = mconf[mb].bits.MT;
        if (mconf[mb].bits.MA0==1 && (MT>0 && MT<6) && mctrl[mb].rd.RDY==1) {
            DBGM bhmMessage("I", "CAN_RX_THREAD", "mb[%d] Ready to Receive", mb);

            //
            // Match the ID taking into account the MASK
            //
            Uns8  MASKIDX = MT -1;
            Uns32 MASK    = mask[MASKIDX].bits.CMID;
            Uns32 ID      = mid[mb].bits.ID;
            if (mid[mb].bits.IDE) {
                DBGM bhmMessage("I", "CAN_RX_THREAD", "mb[%d] (EXT)IDE=0x%03X", mb, ID);
            } else {
                MASK >>= 18;
                ID   >>= 18;
                DBGM bhmMessage("I", "CAN_RX_THREAD", "mb[%d] (STD)IDE=0x%03X", mb, ID);
            }

            //
            // Compare IDE & VCIDE
            //
            Uns8 IDECMP = ((VCID & ~MASK) == (ID & ~MASK)) ? 1 : 0;
            if (IDECMP) {
                //
                // Compare OK assert ACK
                //
                DBGM bhmMessage("I", "CAN_RX_THREAD", "mb[%d] ID-Match MASK=%08x ID=%08x VCID=%08x",
                    mb, MASK, ID, VCID);

                //
                // Acknowledge receipt
                //
                pvRX->frame.data.ack.bits.SLOT = 0;

                //
                // Data Updating MUC/MOW/DN bit
                //
                if (mctrl[mb].rd.DN) {
                    mctrl[mb].rd.MOW = 1;
                }
                mctrl[mb].rd.DN = 1;

                //
                // Number of received bytes
                //
                mdlc[mb].bits.MDLC = VCDLC;

                //
                // Process message
                //
                Uns8 vcidx;
                for(vcidx=0; vcidx<VCDLC; vcidx++) {
                    Uns32 index = (mb<<3) | vcidx;
                    mdata.b[index] = pvRX->frame.data.data.b[vcidx];

                    DBGM bhmMessage("I", "CAN_RX_THREAD", "mb[%d] Data[%d]=0x%02x => MEM[%d]",
                            mb, vcidx, pvRX->frame.data.data.b[vcidx], index);
                }

                //
                // Update the last in pointer
                //
                writeRHL(mb);

                //
                // Interrupt updates
                //
                if (mctrl[mb].rd.IE) {
                    //
                    // message receive
                    //
                    ints.rd.CINTS1 = 1;
                }
            } else {
                DBGM bhmMessage("I", "CAN_RX_THREAD", "mb[%d] ID-Fail  MASK=%08x ID=%08x VCID=%08x",
                    mb, MASK, ID, VCID);
            }
        }
    }

    //
    // wake from sleep
    //
    if (ctrl.rd.PSMODE1==0 && ctrl.rd.PSMODE0==1) {
        ints.rd.CINTS5  = 1;
        ctrl.rd.PSMODE1 = 1; // Wake from sleep mode
    }
}

static void rx_error_frame() {
}

static void rx_overload_frame() {
}

/** Transmit Thread **/
Uns8 tx_stack[STACK_SIZE];
bhmThreadHandle tx_thread_handle;
static void tx_thread(void *data) {
    while (1) {
        //
        // Event/Poll Driven ?
        //
        bhmWaitDelay(POLL_DELAY);

        //
        // Check to see if enabled
        //
        if (gmctrl.rd.GOM==1) {
            Uns8  mb;
            Int8  select   = -1;
            Uns32 priority = 0xffffffff;
            Uns32 id;
            for (mb=0; mb<CAN_MSG_BUFFERS; mb++) {
                //
                // First search to find highest priority message
                // transmit that message, then wait for a time
                //
                if (mconf[mb].bits.MA0==1 && (mconf[mb].bits.MT==0) && mctrl[mb].rd.RDY==1) {
                    if (mctrl[mb].rd.TRQ==1) {
                        //
                        // Get the ID
                        //
                        if (mid[mb].bits.IDE == 1) {
                            //
                            // Extended
                            //
                            id = mid[mb].bits.ID;
                        } else {
                            //
                            // Standard
                            //
                            id = mid[mb].H.ID;
                        }
                        //
                        // Keep selecting the highest priority (lowest number)
                        //
                        priority = (id < priority) ? id : priority;
                        select   = mb;
                    }
                }
            }

            if (select>=0) {
                //
                // Transmit message
                //
                vcanInit(pvTX);

                Uns8 VCDLC = mdlc[select].bits.MDLC;
                DBGH bhmMessage("I", "CAN_TX_THREAD", "mb[%d] Ready to Send", select);

                pvTX->frameType = DATA_REMOTE_FRAME_TYPE;
                // ARB
                pvTX->frame.data.arb.bits.ID_28_18 = (mid[select].bits.ID >> 18);
                if (mid[select].bits.IDE==1) {
                    pvTX->frame.data.arb.bits.SRR = 1;
                    pvTX->frame.data.arb.bits.IDE = 1;
                } else {
                    pvTX->frame.data.arb.bits.IDE = 0;
                }
                pvTX->frame.data.arb.bits.ID_17_00 = (mid[select].bits.ID & 0x3FFFF);
                // CTRL
                pvTX->frame.data.ctrl.bits.DLC = VCDLC;
                // CRC
                pvTX->frame.data.crc.bits.CRC = 0; // TODO
                // DATA
                Uns8 vcidx;
                for(vcidx=0; vcidx<VCDLC; vcidx++) {
                    Uns32 index = (select<<3) | vcidx;
                    pvTX->frame.data.data.b[vcidx] = mdata.b[index];

                    DBGH bhmMessage("I", "CAN_TX_THREAD", "mb[%d] Data[%d]=0x%02x => MEM[%d]",
                            select, vcidx, pvRX->frame.data.data.b[vcidx], index);
                }

                DBGH bhmMessage("I", "CAN_TX_THREAD", "send message");
                ppmPacketnetWrite(handles.CAN, pvTX, sizeof(vcan));
                if (pvTX->frame.data.ack.bits.SLOT==0) {
                    DBGH bhmMessage("I", "CAN_TX_THREAD", "Message Acknowledged");
                }

                //
                // Delay for appropriate amount of time
                //
                bhmWaitDelay(CAN_TX_DELAY);

                mctrl[select].rd.TRQ=0;

                //
                // Interrupt updates
                //
                if (mctrl[select].rd.IE) {
                    //
                    // message sent
                    //
                    ints.rd.CINTS0 = 1;
                    eval_interrupts();
                }
            }
        }
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_PACKETNET_CB(canrx) {
    pvRX = data;

    //
    // Enables and interrupt
    //
    if (gmctrl.rd.GOM==1) {

        DBGM bhmMessage("I", "CAN_RX_THREAD", "Received Packet");

        VC_FRAME frameType = pvRX->frameType;

        switch (frameType) {
        case DATA_REMOTE_FRAME_TYPE:
            // Remote or Data
            if (pvRX->frame.data.arb.bits.RTR) {
                DBGM bhmMessage("I", "CAN_RX_THREAD", "Remote Frame");
                rx_remote_frame();
            } else {
                DBGM bhmMessage("I", "CAN_RX_THREAD", "Data Frame");
                rx_data_frame();
            }
            break;

        case ERROR_FRAME_TYPE:
            bhmMessage("F", "Error Frame", "Unsupported");
            rx_error_frame();
            break;

        case OVERLOAD_FRAME_TYPE:
            bhmMessage("F", "Overload Frame", "Unsupported");
            rx_overload_frame();
            break;
        }

        //
        // Evaluate any interrupts which may have been set
        //
        eval_interrupts();
    }
}

PPM_REG_WRITE_CB(writeGMCTRL) {

    CHECKMASK(data, GMCTRL_WR_MASK, "GMCTRL");

    GMCTRL next = {.reg=(data & GMCTRL_WR_MASK)};

    // Set EFSD
    //
    if (next.wr.SetEFSD) {
        next.rd.EFSD = 1;
    }

    //
    // Set/Clr GOM
    //
    if(next.wr.SetGOM==1 && next.wr.ClrGOM==0) {
        if (next.rd.EFSD==1) {
            bhmMessage("W", "GMCTRL_WRITE", "Caution be sure not to set the GOM and EFSD bits at the same time");
        }
        next.rd.GOM = 1;
        next.rd.MBON = 1;

        //
        // Create threads (if not running)
        //
        if (!tx_thread_handle) {
            tx_thread_handle = bhmCreateThread(tx_thread, NULL, "tx_thread", &tx_stack[STACK_SIZE]);
        }

    } else if (next.wr.SetGOM==0 && next.wr.ClrGOM==1) {
        next.rd.GOM = 0;
        next.rd.MBON = 0;

        //
        // Delete threads (if running)
        //
        if (tx_thread_handle && bhmDeleteThread(tx_thread_handle)) {
            tx_thread_handle = 0;
        }

    }

    //
    // Set SR
    //
    if (gmctrl.wr.SetSR==1) {
        if (gmctrl.rd.GOM==0 && next.rd.GOM==0) {
            if(reset_thread_handle) {
                bhmDeleteThread(reset_thread_handle);
            }
            reset_thread_handle = bhmCreateThread(reset_thread, NULL, "reset_thread", &reset_stack[STACK_SIZE]);

        } else if (gmctrl.rd.GOM==1 && next.rd.GOM==0) {
            bhmMessage("W", "GMCTRL_WRITE", "The SR bit cannot be set(1) at the same time as clearing the GOM bit(0)");

        } else if (next.rd.GOM==1) {
            bhmMessage("W", "GMCTRL_WRITE", "The SR bit can be set(1) only while the GOM bit is cleared(0)");

        }
    }

    //
    // Clr MBRE
    //
    if (next.wr.ClrMBRE==1) {
        if (next.rd.SR == 1) {
            bhmMessage("W", "GMCTRL_WRITE", "The MBRE bit cannot be cleared(0) while the SR bit is set(1)");
        } else {
            next.rd.MBRE = 0;
        }
    }

    //
    // Apply the read mask before saving
    //
    gmctrl.reg = next.reg & GMCTRL_RD_MASK;
}

PPM_REG_READ_CB(readGMCTRL) {
    return gmctrl.reg;
}

PPM_REG_VIEW_CB(viewGMCTRL) {
    *(Uns16*)data = gmctrl.reg;
}


PPM_REG_WRITE_CB(writeGMCS) {
    CHECKMASK(data, GMCS_WR_MASK, "GMCS");
    gmcs.rd = data & GMCS_RD_MASK;
}

PPM_REG_READ_CB(readGMCS) {
    // YOUR CODE HERE (readGMCS)
    bhmPrintf("Called readGMCS!!! \n");
    return gmcs.rd;
}

PPM_REG_VIEW_CB(viewGMCS) {
    *(Uns8*)data = gmcs.rd;
}

PPM_REG_WRITE_CB(writeGMABT) {
    CHECKMASK(data, GMABT_WR_MASK, "GMABT");

    //
    // First apply the write mask
    //
    gmabt.reg = data & GMABT_WR_MASK;

    //
    // Set ABTCLR
    //
    gmabt.rd.ABTCLR = gmabt.wr.SetABTCLR;

    //
    // Set/Clr ABTTRG
    //
    SCBIT(gmabt.rd.ABTTRG, gmabt.wr.SetABTTRG, gmabt.wr.ClrABTTRG);

    //
    // Apply the read mask before saving
    //
    gmabt.reg &= GMABT_RD_MASK;
}

PPM_REG_READ_CB(readGMABT) {
    return gmabt.reg;
}

PPM_REG_VIEW_CB(viewGMABT) {
    *(Uns16*)data = gmabt.reg;
}

PPM_REG_READ_CB(readGMCONF) {
    return gmconf.reg;
}

PPM_REG_VIEW_CB(viewGMCONF) {
    *(Uns16*)data = gmconf.reg;
}

PPM_REG_WRITE_CB(writeGMABTD) {
    CHECKMASK(data, GMABTD_WR_MASK, "GMABTD");

    //
    // First apply the write mask
    //
    gmabtd.reg = data & GMABTD_WR_MASK;

    if (gmabtd.reg > 0x10) {
        bhmMessage("W", "GMABTD_WRITE", "Setting prohibited 0x%02x", gmabtd.reg);
    }

    //
    // Apply the read mask before saving
    //
    gmabtd.reg &= GMABTD_RD_MASK;
}

PPM_REG_READ_CB(readGMABTD) {
    return gmabtd.reg;
}

PPM_REG_VIEW_CB(viewGMABTD) {
    *(Uns8*)data = gmabtd.reg;
}

PPM_REG_WRITE_CB(writeMASK) {
    CHECKMASK(data, MASK_WR_MASK, "MASK");

    Uns8 userdata = PTR_TO_UNS32(user);
    mask[userdata].reg = data & MASK_WR_MASK;

    mask[userdata].reg &= MASK_RD_MASK;
}

PPM_REG_WRITE_CB(writeMASKH) {
    CHECKMASK(data, MASKH_WR_MASK, "MASKH");

    Uns8 userdata = PTR_TO_UNS32(user);
    mask[userdata].r16.H = data & MASKH_WR_MASK;

    mask[userdata].r16.H &= MASKH_RD_MASK;
}

PPM_REG_WRITE_CB(writeMASKL) {
    CHECKMASK(data, MASKL_WR_MASK, "MASKL");

    Uns8 userdata = PTR_TO_UNS32(user);
    mask[userdata].r16.L = data & MASKL_WR_MASK;

    mask[userdata].r16.L &= MASKL_RD_MASK;
}

PPM_REG_READ_CB(readMASK) {
    Uns8 userdata = PTR_TO_UNS32(user);
    return mask[userdata].reg;
}

PPM_REG_READ_CB(readMASKH) {
    Uns8 userdata = PTR_TO_UNS32(user);
    return mask[userdata].r16.H;
}

PPM_REG_READ_CB(readMASKL) {
    Uns8 userdata = PTR_TO_UNS32(user);
    return mask[userdata].r16.L;
}

PPM_REG_VIEW_CB(viewMASK) {
    Uns8 userdata = PTR_TO_UNS32(user);
    *(Uns32*)data = mask[userdata].reg;
}

PPM_REG_VIEW_CB(viewMASKH) {
    Uns8 userdata = PTR_TO_UNS32(user);
    *(Uns16*)data = mask[userdata].r16.H;
}

PPM_REG_VIEW_CB(viewMASKL) {
    Uns8 userdata = PTR_TO_UNS32(user);
    *(Uns16*)data = mask[userdata].r16.L;
}


PPM_REG_WRITE_CB(writeCTRL) {
    CHECKMASK(data, CTRL_WR_MASK, "CTRL");

    CTRL next = {.reg=(data & CTRL_WR_MASK)};

    Uns8 opmode0 = (ctrl.rd.OPMODE2 << 2) |(ctrl.rd.OPMODE1 << 1) | ctrl.rd.OPMODE0;

    if (next.wr.SetCCERC) {
        ctrl.rd.CCERC = 1;
    }

    SCBIT(ctrl.rd.AL, next.wr.SetAL, next.wr.ClrAL);

    CBIT(ctrl.rd.VALID, next.wr.ClrVALID);

    SCBIT(ctrl.rd.OPMODE0, next.wr.SetOPMODE0, next.wr.ClrOPMODE0);
    SCBIT(ctrl.rd.OPMODE1, next.wr.SetOPMODE1, next.wr.ClrOPMODE1);
    SCBIT(ctrl.rd.OPMODE2, next.wr.SetOPMODE2, next.wr.ClrOPMODE2);
    SCBIT(ctrl.rd.PSMODE0, next.wr.SetPSMODE0, next.wr.ClrPSMODE0);
    SCBIT(ctrl.rd.PSMODE1, next.wr.SetPSMODE1, next.wr.ClrPSMODE1);

    //
    // Determine modes and any actions
    //
    Uns8 opmode1 = (ctrl.rd.OPMODE2 << 2) |(ctrl.rd.OPMODE1 << 1) | ctrl.rd.OPMODE0;
    if (opmode0!=0 && opmode1!=0) {
        bhmMessage("W", "CTRL_OPMODE", "Illegal transition from OPMODE=%d->%d", opmode0, opmode1);
    }
    switch(opmode1) {
    case 0:     // Init Mode
        break;
    case 1:     // Normal Operation Mode
        break;
    case 2:     // Normal Operation Mode + ABT
        break;
    case 3:     // Reception Only Mode
        break;
    case 4:     // Single Shot Mode
        break;
    case 5:     // Self Test mode
        break;
    case 6:     // Invalid mode
    case 7:
        break;
    }

    Uns8 psmode = (ctrl.rd.PSMODE1 << 1) | ctrl.rd.PSMODE0;
    switch(psmode) {
    case 0: // power mode not selected
        gmctrl.rd.MBON = 1;
        break;
    case 1: // CAN sleep mode
        gmctrl.rd.MBON = 0;
        break;
    case 2: // Prohibited
        break;
    case 3: // CAN stop mode
        gmctrl.rd.MBON = 0;
        break;
    }
}

PPM_REG_READ_CB(readCTRL) {
    return ctrl.reg;
}

PPM_REG_VIEW_CB(viewCTRL) {
    *(Uns16*)data = ctrl.reg;
}

PPM_REG_WRITE_CB(writeLEC) {
    CHECKMASK(data, LEC_WR_MASK, "LEC");

    lec.reg = data & LEC_WR_MASK;

    lec.reg &= LEC_RD_MASK;
}

PPM_REG_READ_CB(readLEC) {
    return lec.reg;
}

PPM_REG_VIEW_CB(viewLEC) {
    *(Uns8*)data = lec.reg;
}

PPM_REG_WRITE_CB(writeINFO) {
    CHECKMASK(data, INFO_WR_MASK, "INFO");

    info.reg = data & INFO_WR_MASK;

    info.reg &= INFO_RD_MASK;
}

PPM_REG_READ_CB(readINFO) {
    return info.reg;
}

PPM_REG_VIEW_CB(viewINFO) {
    *(Uns8*)data = info.reg;
}

PPM_REG_WRITE_CB(writeERC) {
    CHECKMASK(data, ERC_WR_MASK, "ERC");

    erc.reg = data & ERC_WR_MASK;

    erc.reg &= ERC_RD_MASK;
}

PPM_REG_READ_CB(readERC) {
    // YOUR CODE HERE (readERC)
    return *(Uns16*)user;
}

PPM_REG_VIEW_CB(viewERC) {
     *(Uns16*)data = *(Uns16*)user;
}

PPM_REG_WRITE_CB(writeIE) {
    CHECKMASK(data, IE_WR_MASK, "IE");

    IE next = {.reg=(data & IE_WR_MASK)};

    SCBIT(ie.rd.CIE0, next.wr.SetCIE0, next.wr.ClrCIE0);
    SCBIT(ie.rd.CIE1, next.wr.SetCIE1, next.wr.ClrCIE1);
    SCBIT(ie.rd.CIE2, next.wr.SetCIE2, next.wr.ClrCIE2);
    SCBIT(ie.rd.CIE3, next.wr.SetCIE3, next.wr.ClrCIE3);
    SCBIT(ie.rd.CIE4, next.wr.SetCIE4, next.wr.ClrCIE4);
    SCBIT(ie.rd.CIE5, next.wr.SetCIE5, next.wr.ClrCIE5);

    ie.reg &= IE_RD_MASK;
}

PPM_REG_READ_CB(readIE) {
    return ie.reg;
}

PPM_REG_VIEW_CB(viewIE) {
    *(Uns16*)data = ie.reg;
}


PPM_REG_WRITE_CB(writeINTS) {
    CHECKMASK(data, INTS_WR_MASK, "INTS");

    INTS next = {.reg=(data & INTS_WR_MASK)};

    CBIT(ints.rd.CINTS0, next.wr.ClrCINTS0);
    CBIT(ints.rd.CINTS1, next.wr.ClrCINTS1);
    CBIT(ints.rd.CINTS2, next.wr.ClrCINTS2);
    CBIT(ints.rd.CINTS3, next.wr.ClrCINTS3);
    CBIT(ints.rd.CINTS4, next.wr.ClrCINTS4);
    CBIT(ints.rd.CINTS5, next.wr.ClrCINTS5);

    ints.reg &= INTS_RD_MASK;

    //
    // Check to see if this has had an effect on interrupts
    //
    eval_interrupts();
}

PPM_REG_READ_CB(readINTS) {
    return ints.reg;
}

PPM_REG_VIEW_CB(viewINTS) {
    *(Uns16*)data = ints.reg;
}

PPM_REG_WRITE_CB(writeBRP) {
    CHECKMASK(data, BRP_WR_MASK, "BRP");

    brp.reg = data & BRP_WR_MASK;

    brp.reg &= BRP_RD_MASK;
}

PPM_REG_READ_CB(readBRP) {
    return brp.reg;
}

PPM_REG_VIEW_CB(viewBRP) {
    *(Uns8*)data = brp.reg;
}

PPM_REG_WRITE_CB(writeBTR) {
    CHECKMASK(data, BTR_WR_MASK, "BTR");

    btr.reg = data & BTR_WR_MASK;

    btr.reg &= BTR_RD_MASK;
}

PPM_REG_READ_CB(readBTR) {
    return btr.reg;
}

PPM_REG_VIEW_CB(viewBTR) {
    *(Uns16*)data = btr.reg;
}

PPM_REG_READ_CB(readLIPT) {
    ACCESS_TEST_ZERO

    return lipt.reg;
}

PPM_REG_VIEW_CB(viewLIPT) {
    *(Uns8*)data =  lipt.reg;
}

PPM_REG_WRITE_CB(writeRGPT) {
    ACCESS_TEST_V

    CHECKMASK(data, RGPT_WR_MASK, "RGPT");

    RGPT next = {.reg=(data & RGPT_WR_MASK)};

    CBIT(rgpt.rd.ROVF, next.wr.ClrROVF);

    rgpt.reg &= RGPT_RD_MASK;
}

PPM_REG_READ_CB(readRGPT) {
    ACCESS_TEST_ZERO

    readRHL();

    return rgpt.reg;
}

PPM_REG_VIEW_CB(viewRGPT) {
    *(Uns16*)data = rgpt.reg;
}

PPM_REG_READ_CB(readLOPT) {
    ACCESS_TEST_ZERO

    return lopt.reg;
}

PPM_REG_VIEW_CB(viewLOPT) {
    *(Uns8*)data = lopt.reg;
}

PPM_REG_WRITE_CB(writeTGPT) {
    ACCESS_TEST_V

    CHECKMASK(data, TGPT_WR_MASK, "TGPT");

    TGPT next = {.reg=(data & TGPT_WR_MASK)};

    CBIT(tgpt.rd.TOVF, next.wr.ClrTOVF);

    tgpt.reg &= TGPT_RD_MASK;
}

PPM_REG_READ_CB(readTGPT) {
    ACCESS_TEST_ZERO

    return tgpt.reg;
}

PPM_REG_VIEW_CB(viewTGPT) {
    *(Uns16*)data = tgpt.reg;
}

PPM_REG_WRITE_CB(writeTS) {
    CHECKMASK(data, TS_WR_MASK, "TS");

    TS next = {.reg=(data & TS_WR_MASK)};

    SCBIT(ts.rd.TSEN,   next.wr.SetTSEN,   next.wr.ClrTSEN);
    SCBIT(ts.rd.TSSEL,  next.wr.SetTSSEL,  next.wr.ClrTSSEL);
    SCBIT(ts.rd.TSLOCK, next.wr.SetTSLOCK, next.wr.ClrTSLOCK);

    ts.reg &= TS_RD_MASK;
}

PPM_REG_READ_CB(readTS) {
    return ts.reg;
}

PPM_REG_VIEW_CB(viewTS) {
    *(Uns16*)data = ts.reg;
}

//
// Data Access
//

// | MDATA7 | MDATA6 | MDATA5 | MDATA4 | MDATA3 | MDATA2 | MDATA1 | MDATA0 |
// |     MDATA76     |     MDATA54     |     MDATA32     |     MDATA10     |
// |             MDATA7654             |             MDATA3210             |

PPM_REG_WRITE_CB(writeMDATA) {
    ACCESS_TEST_V
    //
    // n byte write
    //
    Uns32 index = PTR_TO_UNS32(user);
    switch (bytes) {
    case 1:
        mdata.b[index] = data;
        break;
    case 2:
        mdata.s[index] = data;
        break;
    case 4:
        mdata.w[index] = data;
        break;
    }
}

PPM_REG_READ_CB(readMDATA) {
    ACCESS_TEST_ZERO
    //
    // n byte read
    //
    Uns32 index = PTR_TO_UNS32(user);
    switch (bytes) {
    case 1:
        return mdata.b[index];
        break;
    case 2:
        return mdata.s[index];
        break;
    case 4:
        return mdata.w[index];
        break;
    }

    //
    // Unreachable
    //
    return 0;
}

PPM_REG_WRITE_CB(writeMDLC) {
    ACCESS_TEST_V

    Uns32 index = PTR_TO_UNS32(user);

    mdlc[index].bits.MDLC = data;
    if (mdlc[index].bits.MDLC > 8) {
        bhmMessage("W", "MDLC_WRITE", "Setting prohibited mdlc%d=0x%02x", index, mdlc[index].bits.MDLC);
    }

    mdlc[index].bits.MDLC &= MDLC_RD_MASK;
}
PPM_REG_READ_CB(readMDLC) {
    ACCESS_TEST_ZERO

    Uns32 index = PTR_TO_UNS32(user);
    return mdlc[index].bits.MDLC;
}
PPM_REG_VIEW_CB(viewMDLC) {
    Uns32 index = PTR_TO_UNS32(user);
    *(Uns8*)data = mdlc[index].bits.MDLC;
}

PPM_REG_WRITE_CB(writeMCONF) {
    ACCESS_TEST_V
    CHECKMASK(data, MCONF_WR_MASK, "MCONF");

    Uns32 index = PTR_TO_UNS32(user);
    mconf[index].reg = data & MCONF_WR_MASK;

    mconf[index].reg &= MCONF_RD_MASK;
}
PPM_REG_READ_CB(readMCONF) {
    ACCESS_TEST_ZERO
    Uns32 index = PTR_TO_UNS32(user);

    return mconf[index].reg;
}
PPM_REG_VIEW_CB(viewMCONF) {
    Uns32 index = PTR_TO_UNS32(user);

    *(Uns8*)data = mconf[index].reg;
}

PPM_REG_WRITE_CB(writeMID) {
    ACCESS_TEST_V

    CHECKMASK(data, MID_WR_MASK, "MID");

    Uns32 index = PTR_TO_UNS32(user);
    mid[index].reg = data & MID_WR_MASK;

    mid[index].reg &= MID_RD_MASK;
}
PPM_REG_WRITE_CB(writeMIDH) {
    ACCESS_TEST_V

    CHECKMASK(data, MIDH_WR_MASK, "MIDH");

    Uns32 index = PTR_TO_UNS32(user);
    mid[index].HL.H = data & MIDH_WR_MASK;

    mid[index].HL.H &= MIDH_RD_MASK;
}
PPM_REG_WRITE_CB(writeMIDL) {
    ACCESS_TEST_V

    CHECKMASK(data, MIDL_WR_MASK, "MIDL");

    Uns32 index = PTR_TO_UNS32(user);
    mid[index].HL.L = data & MIDL_WR_MASK;

    mid[index].HL.L &= MIDL_RD_MASK;
}

PPM_REG_READ_CB(readMID) {
    ACCESS_TEST_ZERO

    Uns32 index = PTR_TO_UNS32(user);
    return mid[index].reg;
}
PPM_REG_READ_CB(readMIDH) {
    ACCESS_TEST_ZERO

    Uns32 index = PTR_TO_UNS32(user);
    return mid[index].HL.H;
}
PPM_REG_READ_CB(readMIDL) {
    ACCESS_TEST_ZERO

    Uns32 index = PTR_TO_UNS32(user);
    return mid[index].HL.L;
}

PPM_REG_VIEW_CB(viewMID) {
    Uns32 index = PTR_TO_UNS32(user);
    *(Uns32*)data = mid[index].reg;
}
PPM_REG_VIEW_CB(viewMIDH) {
    Uns32 index = PTR_TO_UNS32(user);
    *(Uns16*)data = mid[index].HL.H;
}
PPM_REG_VIEW_CB(viewMIDL) {
    Uns32 index = PTR_TO_UNS32(user);
    *(Uns16*)data = mid[index].HL.L;
}

PPM_REG_WRITE_CB(writeMCTRL) {
    ACCESS_TEST_V

    CHECKMASK(data, MCTRL_WR_MASK, "MCTRL");

    //
    // First apply the write mask
    //
    Uns32 index = PTR_TO_UNS32(user);
    MCTRL next = {.reg=(data & MCTRL_WR_MASK)};

    CBIT(mctrl[index].rd.MOW, next.wr.ClrMOW);
    SCBIT(mctrl[index].rd.IE, next.wr.SetIE, next.wr.ClrIE);
    CBIT(mctrl[index].rd.DN, next.wr.ClrDN);
    SCBIT(mctrl[index].rd.TRQ, next.wr.SetTRQ, next.wr.ClrTRQ);
    SCBIT(mctrl[index].rd.RDY, next.wr.SetRDY, next.wr.ClrRDY);

    //
    // Apply the read mask before saving
    //
    mctrl[index].reg &= MCTRL_RD_MASK;
}
PPM_REG_READ_CB(readMCTRL) {
    ACCESS_TEST_ZERO

    Uns32 index = PTR_TO_UNS32(user);
    return mctrl[index].reg;
}
PPM_REG_VIEW_CB(viewMCTRL) {
    Uns32 index = PTR_TO_UNS32(user);
    *(Uns16*)data = mctrl[index].reg;
}

PPM_REG_WRITE_CB(writeE6A0CTL) {
    CHECKMASK(data, E6A0CTL_WR_MASK, "E6A0CTL");

    e6a0ctl.reg = data & E6A0CTL_WR_MASK;

    e6a0ctl.reg &= E6A0CTL_RD_MASK;
}
PPM_REG_READ_CB(readE6A0CTL) {
    return e6a0ctl.reg;
}
PPM_REG_VIEW_CB(viewE6A0CTL) {
    *(Uns16*)data = e6a0ctl.reg;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    tx_thread_handle = 0;
    reset_thread_handle = bhmCreateThread(reset_thread, NULL, "reset_thread", &reset_stack[STACK_SIZE]);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

