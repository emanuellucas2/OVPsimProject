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

#include <string.h>
#include <stdlib.h>

#define PREFIX "LAN91C111"

typedef struct macRegS {
    union {
        Uns16 value;
        struct {
            unsigned BS0 : 1;
            unsigned BS1 : 1;
            unsigned BS2 : 1;
            unsigned __pad1 : 13;
        } bits;
    } BANK;
    union {
        Uns16 value;
        struct {
            unsigned ENABLE : 1;
            unsigned LOOP : 1;
            unsigned FORCOL : 1;
            unsigned __pad1 : 4;
            unsigned PAD_EN : 1;
            unsigned NOCRC : 1;
            unsigned __pad2 : 1;
            unsigned MON_CSR : 1;
            unsigned FDUPLX : 1;
            unsigned STP_SQET : 1;
            unsigned EHP_LOOP : 1;
            unsigned __pad3 : 1;
            unsigned SWFDUP : 1;
        } bits;
    } TCR;
    union {
        Uns16 value;
        struct {
            unsigned TX_SUC      : 1;
            unsigned SNGL_COL : 1;
            unsigned MUL_COL  : 1;
            unsigned LTX_MULT : 1;
            unsigned COL16      : 1;
            unsigned SQET      : 1;
            unsigned LTXBRD      : 1;
            unsigned TXDEFR      : 1;
            unsigned __pad1 : 1;
            unsigned LATCOL      : 1;
            unsigned LOSTCARR : 1;
            unsigned EXC_DEF  : 1;
            unsigned CTR_ROL  : 1;
            unsigned __pad2 : 1;
            unsigned LINK_OK  : 1;
            unsigned __pad3 : 1;
        } bits;
    } EPH_STATUS;
    union {
        Uns16 value;
        struct {
            unsigned RX_ABORT   : 1;
            unsigned PRMS        : 1;
            unsigned ALMUL        : 1;
            unsigned __pad1 : 5;
            unsigned RXEN        : 1;
            unsigned STRIP_CRC  : 1;
            unsigned __pad2 : 3;
            unsigned ABORT_ENB  : 1;
            unsigned FILT_CAR   : 1;
            unsigned SOFTRST    : 1;
        } bits;
    } RCR;
    union {
        Uns16 value;
        struct {
            unsigned SINGLE_COL   : 4;
            unsigned MULTIPLE_COL   : 4;
            unsigned DEF_TX   : 4;
            unsigned EXC_DEF_TX  : 4;
        } bits;
    } COUNTER;
    union {
        Uns16 value;
        struct {
            unsigned MEM_SIZE   : 8;
            unsigned MEM_FREE   : 8;
        } bits;
    } MIR;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 2;
            unsigned LS0B         : 1;
            unsigned LS1B         : 1;
            unsigned LS2B         : 1;
            unsigned LS0A         : 1;
            unsigned LS1A         : 1;
            unsigned LS2A         : 1;
            unsigned __pad2 : 3;
            unsigned ANEG         : 1;
            unsigned DPLX         : 1;
            unsigned SPEED         : 1;
            unsigned __pad3 : 2;
        } bits;
    } RPCR;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 9;
            unsigned EXT_PHY : 1;
            unsigned GPCNTRL : 1;
            unsigned __pad2 : 1;
            unsigned NO_WAIT : 1;
            unsigned __pad3 : 2;
            unsigned EPH_POWER_EN : 1;
        } bits;
    } CONFIG;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } BASE;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } IA0_1;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } IA2_3;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } IA4_5;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } GP;
    union {
        Uns16 value;
        struct {
            unsigned STORE : 1;
            unsigned RELOAD : 1;
            unsigned EEPROM_SEL : 1;
            unsigned __pad1 : 2;
            unsigned TE_ENABLE : 1;
            unsigned CR_ENABLE : 1;
            unsigned LE_ENABLE : 1;
            unsigned __pad2 : 3;
            unsigned AUTO_RELEASE : 1;
            unsigned __pad3 : 2;
            unsigned RCV_BAD : 1;
            unsigned __pad4 : 1;
        } bits;
    } CONTROL;
    union {
        Uns16 value;
        struct {
            unsigned BUSY : 1;
            unsigned __pad1 : 4;
            unsigned COMMAND : 3;
            unsigned __pad2 : 8;
        } bits;
    } MMU_CMD;
    union {
        Uns16 value;
        struct {
            unsigned TX_PKT_NUM : 6;
            unsigned __pad1 : 2;
            unsigned ALLOC_PKT_NUM : 6;
            unsigned __pad2 : 1;
            unsigned FAILED : 1;
        } bits;
    } PNR;
    union {
        Uns16 value;
        struct {
            unsigned TX_PKT_NUM : 6;
            unsigned __pad1 : 1;
            unsigned TEMPTY : 1;
            unsigned RX_PKT_NUM : 6;
            unsigned __pad2 : 1;
            unsigned REMPTY : 1;
        } bits;
    } FIFO_PORTS;
    union {
        Uns16 value;
        struct {
            unsigned POINTER : 11;
            unsigned NOT_EMPTY : 1;
            unsigned __pad1 : 1;
            unsigned READ : 1;
            unsigned AUTO_INCR : 1;
            unsigned RCV : 1;
        } bits;
    } POINTER;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } DATA;
    union {
        Uns16 value;
        struct {
            unsigned RCV_INT : 1;
            unsigned TX_INT : 1;
            unsigned TX_EMPTY_INT : 1;
            unsigned ALLOC_INT : 1;
            unsigned RX_OVRN_INT : 1;
            unsigned EPH_INT : 1;
            unsigned __pad1 : 1;
            unsigned MDINT : 1;
            unsigned RCV_INT_MASK : 1;
            unsigned TX_INT_MASK : 1;
            unsigned TX_EMPTY_INT_MASK : 1;
            unsigned ALLOC_INT_MASK : 1;
            unsigned RX_OVRN_INT_MASK : 1;
            unsigned EPH_INT_MASK : 1;
            unsigned __pad2 : 1;
            unsigned MDINT_MASK : 1;
        } bits;
    } INTERRUPT;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } MT0_1;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } MT2_3;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } MT4_5;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } MT6_7;
    union {
        Uns16 value;
        struct {
            unsigned MDO : 1;
            unsigned MDI : 1;
            unsigned MCLK : 1;
            unsigned MDOE : 1;
            unsigned __pad1 : 12;
        } bits;
    } MGMT;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } REVISION;
    union {
        Uns16 value;
        struct {
            unsigned __pad1 : 16;
        } bits;
    } RCV;
} macRegT;



macRegT macReg;
Uns16 phyReg[20];

#define THREAD_STACK      (8*1024)


#define PHY_CONTROL_REG 0
#define PHY_STATUS_REG 1  //Status
#define PHY_PHY1_REG 2    // PHY ID#1
#define PHY_PHY2_REG 3    //PHY ID#2
#define PHY_AA_REG 4      //AutoNegotiation Advertisement
#define PHY_ARE_REG 5     //AutoNegotiation Remote End Capability
#define PHY_CFG1_REG 16
#define PHY_CFG2_REG 17
#define PHY_STATUS_OUT_REG 18
#define PHY_MASK_REG 19



#define PAGE_LENGTH 2048
#define NUM_PAGES 4
#define MAX_PKT_NUM 4

struct {

    Uns32 ethHandle;

    Uns8 page_allocated[NUM_PAGES];
    Uns8 packet_nums[NUM_PAGES];

    Uns8 fifo_mem[NUM_PAGES][PAGE_LENGTH];

    Uns8 rx_packet_buf[2048];

    Uns8 rx_page_list[NUM_PAGES];
    Uns8 num_rx_pages;

    Uns32 mii_cmd;
    Uns32 mii_idle_count;

    Uns32 mii_data_value;
    Uns32 mii_data_count;

    Int32 eeprom_writable;
    Uns32 eeprom[128];

    Uns8 stack[THREAD_STACK];

    Uns8 previousIrq;
} state;

void doPhyReset() {
    int i;

    for (i = 0; i < 20; i++) {
        phyReg[i] = 0;
    }
    phyReg[PHY_PHY1_REG]       = 0x0016;
    phyReg[PHY_PHY2_REG]       = 0xF840;
    phyReg[PHY_CONTROL_REG]    = 0x3400;
    phyReg[PHY_STATUS_REG]     = 0x780D;
    phyReg[PHY_AA_REG]         = 0x01E1;
    phyReg[PHY_CFG1_REG]       = 0x0022;
    phyReg[PHY_CFG2_REG]       = 0xFF00;
    phyReg[PHY_STATUS_OUT_REG] = 0x0080;
    phyReg[PHY_MASK_REG]       = 0xFFC0;

}

void doReset() {

    macReg.REVISION.value = 0x3392;

    state.mii_cmd = 0;
    state.mii_idle_count = 0;

    state.mii_data_value = 0;
    state.mii_data_count = 0;

    state.previousIrq = 0;

    state.num_rx_pages = 0;

    doPhyReset();


    Uns64  mac;
    bhmUns64ParamValue("macaddress", &mac);

    macReg.IA0_1.value = (mac >>  0) & 0xffff;  // 0x1200;
    macReg.IA2_3.value = (mac >> 16) & 0xffff;  // 0x5634;
    macReg.IA4_5.value = (mac >> 32) & 0xffff;  // 0x9a78;

    macReg.INTERRUPT.value = 0x0004;
}

static void updateInts()
{
    Uns8 newIrq = (macReg.INTERRUPT.value & 0x00BF) & ((macReg.INTERRUPT.value >> 8) & 0x00BF);

    // update the interrupt pin;  TODO: support interrupt de-assertion interval
    if (newIrq != state.previousIrq) {
        ppmWriteNet(handles.irq, (newIrq != 0));
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Pin IRQ %sasserted  value=%d", (newIrq != 0 ? "" : "de-"), newIrq);
    }
    state.previousIrq = newIrq;
}

void phy_write(Uns16 index, Uns16 value)
{
    phyReg[index] = value;

    if ((index == PHY_CONTROL_REG) && (value & 0x8000)) {
        // do PHY reset
        doPhyReset();
    }

}

void mii_write(Uns16 value) {
    // check for clock rising edge
    if (!macReg.MGMT.bits.MCLK && (value & 0x0004)) {

        // Check for 32 idle bits being shifted in
        if (state.mii_idle_count < 32) {
            if (value & 0x01)
                state.mii_idle_count++;
            else
                state.mii_idle_count = 0;
        // Check for start bits 01
        } else if (state.mii_data_count == 0 && !(value & 0x01)) {
            state.mii_data_count++;
            state.mii_cmd = 0;
        } else if (state.mii_data_count == 1) {
            if (value & 0x01) {
                state.mii_data_count++;
                state.mii_cmd = 0x01;
            } else {
                state.mii_data_count = 0;
            }
        // Check for read/write
        } else if (state.mii_data_count < 16) {
            state.mii_data_count++;
            state.mii_cmd = (state.mii_cmd << 1) | (value & 0x01);
            // Check if read command
            if (state.mii_data_count == 16 && state.mii_cmd & 0x2000) {
                state.mii_data_value = phyReg[(state.mii_cmd >> 2) & 0x1f];
                macReg.MGMT.bits.MDI = (state.mii_data_value & 0x8000) ? 1 : 0;
                state.mii_data_value = (state.mii_data_value << 1) & 0xFFFF;
            } else {
                state.mii_data_value = 0;
            }
        } else if (state.mii_data_count < 32) {
            state.mii_data_count++;
            if (state.mii_cmd & 0x2000) {
                macReg.MGMT.bits.MDI = (state.mii_data_value & 0x8000) ? 1 : 0;
                state.mii_data_value = (state.mii_data_value << 1) & 0xFFFF;
            } else {
                state.mii_data_value = (state.mii_data_value << 1) | (value & 0x01);
                if (state.mii_data_count == 32)
                    phy_write((state.mii_cmd >> 2) & 0x1f,state.mii_data_value & 0xFFFF);

            }
        }
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "mii Write idl_cnt=%d, data_cnt=%d cmd=0x%04x, data=0x%04x", state.mii_idle_count, state.mii_data_count, state.mii_cmd, state.mii_data_value);
        }
    }
    if  (state.mii_data_count >= 32) {
            // todo support multi-reg access
            state.mii_data_count = 0;
            state.mii_idle_count = 0;
    }
    macReg.MGMT.bits.MCLK = value & 0x0004;
}

void writeFifoData(Uns32 data,Uns32 bytes)
{

    Uns16 cur_page;

    if (macReg.POINTER.bits.RCV) {
        cur_page = macReg.FIFO_PORTS.bits.RX_PKT_NUM;
    } else {
        cur_page = macReg.FIFO_PORTS.bits.TX_PKT_NUM;
    }



    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "writeFifoData: page=%d, pointer=%d, value=%x",cur_page,macReg.POINTER.bits.POINTER, data);
    }

    Uns8 *ptr;

    if (macReg.POINTER.bits.READ) {
        // Error?
    }

    ptr = &state.fifo_mem[cur_page][macReg.POINTER.bits.POINTER];

    memcpy(ptr,&data,bytes);

    if (macReg.POINTER.bits.AUTO_INCR) {
        macReg.POINTER.bits.POINTER += bytes;
    }
}

void allocate_tx_page()
{
    int i;
    macReg.PNR.bits.FAILED = 1;
    for (i = 0; i < NUM_PAGES; i++) {
        if (state.page_allocated[i] == 0) {
            state.page_allocated[i] = 1;
            macReg.PNR.bits.FAILED = 0;
            macReg.PNR.bits.ALLOC_PKT_NUM = i;
            macReg.INTERRUPT.bits.ALLOC_INT = 1;
            updateInts();
            return;
        }
    }
}

void send_tx_packet(Uns8 packet_num)
{
    if (packet_num > MAX_PKT_NUM) {
        //error
        bhmMessage("W", PREFIX, "send_tx_packet: Invalid packet number %d", packet_num);
        return;
    }

    if (!state.page_allocated[packet_num]) {
        // error
        bhmMessage("W", PREFIX, "send_tx_packet: Memory page not allocated for packet %d", packet_num);
        return;
    }

    Uns32 length = ((state.fifo_mem[packet_num][3] & 0x7) << 8) | (state.fifo_mem[packet_num][2] & 0xFE);

    if (state.fifo_mem[packet_num][length+10] & 0x20) {

        // Overwrite first CRC byte (end of data section) with last (odd) byte
        state.fifo_mem[packet_num][length+5] = state.fifo_mem[packet_num][length+9];
        length++;
    }

    if (PSE_DIAG_LOW) {
        double t = bhmGetCurrentTime();
        Uns32  timeMS = t / 1000; // mS
        bhmMessage("I", "ETH_TX", "Time: %u packet num=%d, write %d bytes", timeMS, packet_num, length);
    }

   Uns32 result = bhmEthernetWriteFrame(state.ethHandle, &state.fifo_mem[packet_num][4], length);

   if (!result) {
       bhmMessage("I", "ETH_TXE", "Failed to transmit");
   } else {

        state.fifo_mem[packet_num][0] = 0x01;
        macReg.EPH_STATUS.value = 0x01;

        if (macReg.CONTROL.bits.AUTO_RELEASE) {
            state.page_allocated[packet_num] = 0;
        }

        macReg.INTERRUPT.bits.TX_EMPTY_INT = 1;
        macReg.FIFO_PORTS.bits.TEMPTY = 0;
        updateInts();
    }
}

Uns32 readFifoData(Uns32 bytes)
{
    Uns8 *ptr;
    Uns32 data = 0;

    Uns16 cur_page;

    if (macReg.POINTER.bits.RCV) {
        cur_page = macReg.FIFO_PORTS.bits.RX_PKT_NUM;
    } else {
        cur_page = macReg.FIFO_PORTS.bits.TX_PKT_NUM;
    }

    if (!macReg.POINTER.bits.READ) {
        // Error?
    }

    ptr = &state.fifo_mem[cur_page][macReg.POINTER.bits.POINTER];

    memcpy(&data,ptr,bytes);

    if (macReg.POINTER.bits.AUTO_INCR) {
        macReg.POINTER.bits.POINTER += bytes;
    }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "readFifoData: page=%d, pointer=%d, value=%x",cur_page,macReg.POINTER.bits.POINTER, data);
    }

    return data;
}


static void pushRxFrame(Uns8 *frame, int len)
{
    int index = 0;
    Uns16 frame_len;
    Bool odd_len;
    int packet_num;
    for (packet_num = 0; packet_num < NUM_PAGES; packet_num++) {
        if (state.page_allocated[packet_num] == 0) {
            state.page_allocated[packet_num] = 1;
            break;
        }
    }
    if (packet_num == NUM_PAGES) {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "Buffer overrun   bytesd:%u",len);
        }
        macReg.INTERRUPT.bits.RX_OVRN_INT = 1;
        updateInts();
        return;
    }

    state.rx_page_list[state.num_rx_pages++] = packet_num;

    frame_len = (len & 0x7FE) + 10;

    if (macReg.RCR.bits.STRIP_CRC) {
        frame_len = frame_len - 4;
    }

    odd_len = (len & 0x01);

    state.fifo_mem[packet_num][index++] = 0;
    state.fifo_mem[packet_num][index++] = 0 | ((odd_len) ? 0x10 : 0);


    state.fifo_mem[packet_num][index++] = frame_len & 0x00FE;
    state.fifo_mem[packet_num][index++] = (frame_len >> 8) & 0x07;

    memcpy(&state.fifo_mem[packet_num][index],frame,(len & 0x7FE));

    index = index + (len & 0x7FE);

    if (!macReg.RCR.bits.STRIP_CRC) {
        // todo: fill in crc
        index = index + 4;
    }

    if (odd_len) {
        state.fifo_mem[packet_num][index++] = frame[len-1];
    }

    state.fifo_mem[packet_num][index++] = 0x40 | (odd_len ? 0x20 : 0x0);

    if (macReg.FIFO_PORTS.bits.REMPTY) {
        macReg.FIFO_PORTS.bits.RX_PKT_NUM = packet_num;
        macReg.FIFO_PORTS.bits.REMPTY = 0;
    }

    macReg.INTERRUPT.bits.RCV_INT = 1;
    updateInts();

}

void remove_rx_frame()
{
    int i;
    if (state.num_rx_pages == 0) {
        // no frames to remove
        return;
    }

    state.num_rx_pages--;

    if (state.num_rx_pages > 0) { // New packet waiting, put into FIFO

        macReg.FIFO_PORTS.bits.RX_PKT_NUM = state.rx_page_list[0];
        macReg.FIFO_PORTS.bits.REMPTY = 0;
        macReg.INTERRUPT.bits.RCV_INT = 1;
        updateInts();


        for (i = 0; i < state.num_rx_pages-1; i++) {
            state.rx_page_list[i] = state.rx_page_list[i+1];
        }

    } else { // No more packets waiting
        macReg.FIFO_PORTS.bits.REMPTY = 1;
        macReg.INTERRUPT.bits.RCV_INT = 0;
        updateInts();
    }
}

PPM_REG_READ_CB(readReg16) {
    Uns32 index = PTR_TO_UNS32(user);
    Uns32 value = 0;

    Uns32 bank = (macReg.BANK.value & 0x7);


    // BANK 0
    if (bank == 0) {
        switch (index) {
            case 0x0:
                value = macReg.TCR.value;
                break;
            case 0x2:
                value = macReg.EPH_STATUS.value;
                break;
            case 0x4:
                value = macReg.RCR.value;
                break;
            case 0x6:
                value = macReg.COUNTER.value;
                break;
            case 0x8:
                value = macReg.MIR.value;
                break;
            case 0xA:
                value = macReg.RPCR.value;
                break;
            case 0xC:
                bhmMessage("E", PREFIX, "Read from undefined register bank = %d, offset = %d", bank, index);
                break;
            case 0xE: // BANK SELECT
                value = 0x3300 | bank;
                break;
            default:
                bhmMessage("E", PREFIX, "Read from undefined register bank = %d, offset = %d", bank, index);
        }
    // BANK 1
    } else if (bank == 1) {
        switch (index) {
            case 0x0:
                value = macReg.CONFIG.value;
                break;
            case 0x2:
                value = macReg.BASE.value;
                break;
            case 0x4:
                value = macReg.IA0_1.value;
                break;
            case 0x6:
                value = macReg.IA2_3.value;
                break;
            case 0x8:
                value = macReg.IA4_5.value;
                break;
            case 0xA:
                value = macReg.GP.value;
                break;
            case 0xC:
                value = macReg.CONTROL.value;
                break;
            case 0xE: // BANK SELECT
                value = 0x3300 | bank;
                break;
            default:
                bhmMessage("E", PREFIX, "Read from undefined register bank = %d, offset = %d", bank, index);
        }
    // BANK 2
     } else if (bank == 2) {
         switch (index) {
            case 0x0:
                value = (macReg.MMU_CMD.value & 0x01);
                break;
            case 0x2:
                value = macReg.PNR.value;
                break;
            case 0x4:
                value = macReg.FIFO_PORTS.value;
                break;
            case 0x6:
                value = macReg.POINTER.value;
                break;
            case 0x8:
                value = readFifoData(bytes);
                break;
            case 0xC:
                value = macReg.INTERRUPT.value;

                // Needed to deassert IRQ pin
                if (macReg.INTERRUPT.bits.ALLOC_INT) {
                    macReg.INTERRUPT.bits.ALLOC_INT = 0;
                    updateInts();
                }
                break;
            case 0xE: // BANK SELECT
                value = 0x3300 | bank;
                break;
            default:
                bhmMessage("E", PREFIX, "Read from undefined register bank = %d, offset = %d", bank, index);
        }
    // BANK 3
     } else if (bank == 3) {
         switch (index) {
            case 0x0:
                value = macReg.MT0_1.value;
                break;
            case 0x2:
                value = macReg.MT2_3.value;
                break;
            case 0x4:
                value = macReg.MT4_5.value;
                break;
            case 0x6:
                value = macReg.MT6_7.value;
                break;
            case 0x8:
                value = macReg.MGMT.value;
                break;
            case 0xA:
                value = macReg.REVISION.value;
                break;
            case 0xC:
                value = macReg.RCV.value;
                break;
            case 0xE: // BANK SELECT
                value = 0x3300 | bank;
                break;
            default:
                bhmMessage("E", PREFIX, "Read from undefined register bank = %d, offset = %d", bank, index);
        }
     } else {
        bhmMessage("E", PREFIX, "Read from undefined bank %d, offset = %d", bank, index);
     }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read register bank=%d, index=0x%02x, bytes=%d, value=0x%08x", bank, index, bytes, value);
    }

    return value;
}

PPM_REG_WRITE_CB(writeReg16) {
    Uns32 index = PTR_TO_UNS32(user);
    Uns32 bank = (macReg.BANK.value & 0x7);

    // BANK 0
    if (bank == 0) {
        switch (index) {
            case 0x0:
                macReg.TCR.value = data;
                break;
            case 0x2:
                bhmMessage("W", PREFIX, "Write to read-only register bank = %d, offset = %d", bank, index);
                break;
            case 0x4:
                macReg.RCR.value = data;
                break;
            case 0x6:
                bhmMessage("W", PREFIX, "Write to read-only register bank = %d, offset = %d", bank, index);
                break;
            case 0x8:
                bhmMessage("W", PREFIX, "Write to read-only register bank = %d, offset = %d", bank, index);
                break;
            case 0xA:
                macReg.RPCR.value = data;
                break;
            case 0xC:
                bhmMessage("E", PREFIX, "Write to undefined register bank = %d, offset = %d", bank, index);
                break;
            case 0xE: // BANK SELECT
                macReg.BANK.value = 0x3300 | (data & 0x7);
                break;
            default:
                bhmMessage("E", PREFIX, "Write to undefined register bank = %d, offset = %d", bank, index);
        }
    // BANK 1
    } else if (bank == 1) {
        switch (index) {
            case 0x0:
                macReg.CONFIG.value = data;
                break;
            case 0x2:
                macReg.BASE.value = data;
                break;
            case 0x4:
                macReg.IA0_1.value = data;
                break;
            case 0x6:
                macReg.IA2_3.value = data;
                break;
            case 0x8:
                macReg.IA4_5.value = data;
                break;
            case 0xA:
                macReg.GP.value = data;
                break;
            case 0xC:
                macReg.CONTROL.value = data;
                break;
            case 0xE: // BANK SELECT
                macReg.BANK.value = 0x3300 | (data & 0x7);
                break;
            default:
                bhmMessage("E", PREFIX, "Write to undefined register bank = %d, offset = %d", bank, index);
        }
    // BANK 2
     } else if (bank == 2) {
         switch (index) {
            case 0x0:
                switch ((data >> 5) & 0x7) {
                    case 0: // NOP
                        break;
                    case 1: // ALLOCATE TX MEM
                        allocate_tx_page();
                        break;
                    case 2: // RESET MMU
                        break;
                    case 3: // REMOVE FRAME FROM RX FIFO
                        remove_rx_frame();
                        break;
                    case 4: // REMOVE AND RELEASE RX FIFO
                        if (macReg.FIFO_PORTS.bits.RX_PKT_NUM > MAX_PKT_NUM) {
                            //error
                            break;
                        }
                        state.page_allocated[macReg.FIFO_PORTS.bits.RX_PKT_NUM] = 0;
                        remove_rx_frame();

                        break;
                    case 5: // RELEASE SPECIFIC PACKET
                        if (macReg.PNR.bits.TX_PKT_NUM > MAX_PKT_NUM) {
                            //error
                        }
                        state.page_allocated[macReg.PNR.bits.TX_PKT_NUM] = 0;
                        break;
                    case 6: // ENQUE PACKET IN TX FIFO
                        send_tx_packet(macReg.PNR.bits.TX_PKT_NUM);
                        break;
                    case 7: // RESET TX FIFOs
                        break;
                }

                break;
            case 0x2:
                macReg.PNR.value = (data & 0x00FF);
                macReg.FIFO_PORTS.bits.TX_PKT_NUM = macReg.PNR.bits.TX_PKT_NUM;

                break;
            case 0x4:
                bhmMessage("W", PREFIX, "Write to read-only register bank = %d, offset = %d", bank, index);
                break;
            case 0x6:
                macReg.POINTER.value = (macReg.POINTER.value & 0x0800) | (data & 0xF7FF);
                //state.cur_page = data & 0x7FF;

                // Linux Driver doesn't appear to remove packet from FIFO during RX ISR, so clear bit when RX data is read
                if (macReg.POINTER.bits.RCV) {
                    macReg.INTERRUPT.bits.RCV_INT = 0;
                    updateInts();
                }

                break;
            case 0x8:
            case 0x9:
            case 0xA:
            case 0xB:
                writeFifoData(data,bytes);
                macReg.DATA.value = data;
                break;
            case 0xC:
                macReg.INTERRUPT.value = (data & 0xBF00) | ((macReg.INTERRUPT.value & 0x0029) & ~(data & 0x0096));
                updateInts();
                break;
            case 0xE: // BANK SELECT
                macReg.BANK.value = 0x3300 | (data & 0x7);
                break;
            default:
                bhmMessage("E", PREFIX, "Write to undefined register bank = %d, offset = %d", bank, index);
        }
    // BANK 3
     } else if (bank == 3) {
         switch (index) {
            case 0x0:
                macReg.MT0_1.value = data;
                break;
            case 0x2:
                macReg.MT2_3.value = data;
                break;
            case 0x4:
                macReg.MT4_5.value = data;
                break;
            case 0x6:
                macReg.MT6_7.value = data;
                break;
            case 0x8:
                mii_write(data);
                break;
            case 0xA:
                bhmMessage("W", PREFIX, "Write to read-only register bank = %d, offset = %d", bank, index);
                break;
            case 0xC:
                macReg.RCV.value = data;
                break;
            case 0xE: // BANK SELECT
                macReg.BANK.value = 0x3300 | (data & 0x7);
                break;
            default:
                bhmMessage("E", PREFIX, "Write to undefined register bank = %d, offset = %d", bank, index);
        }
     } else {

        bhmMessage("E", PREFIX, "Write to undefined bank %d, offset = %d", bank, index);
     }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write register bank=%d, index=0x%02x, bytes=%d, value=0x%08x", bank, index, bytes, data);
    }
}

static BHM_ETHER_PACKET_CB(rxPacket) {
    if (PSE_DIAG_LOW) {
        double t = bhmGetCurrentTime();
        Uns32  timeMS = t / 1000; // mS
        bhmMessage("I", "ETH_RX", "Time: %u Read %d bytes", timeMS, bytes);
    }
    pushRxFrame(data, bytes);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();
    // Initialize semihosting
    state.ethHandle = bhmEthernetOpenAuto();
    doReset();

    bhmEthernetInstallCB(state.ethHandle, rxPacket, 0);
}

PPM_DESTRUCTOR_CB(destructor) {
    bhmEthernetClose(state.ethHandle);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

