/*
 * SD Memory Card emulation.  Mostly correct for MMC too.
 *
 * Copyright (c) 2006 Andrzej Zaborowski  <balrog@zabor.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
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


#ifndef __hw_sd_h
#define __hw_sd_h       1


#include "drive.h"
#include "semihost.h"

typedef int qemu_irq ;

#define CHANGE_MEDIA    0x01
#define CHANGE_SIZE     0x02


#define OUT_OF_RANGE        (1 << 31)
#define ADDRESS_ERROR       (1 << 30)
#define BLOCK_LEN_ERROR     (1 << 29)
#define ERASE_SEQ_ERROR     (1 << 28)
#define ERASE_PARAM     (1 << 27)
#define WP_VIOLATION        (1 << 26)
#define CARD_IS_LOCKED      (1 << 25)
#define LOCK_UNLOCK_FAILED  (1 << 24)
#define COM_CRC_ERROR       (1 << 23)
#define ILLEGAL_COMMAND     (1 << 22)
#define CARD_ECC_FAILED     (1 << 21)
#define CC_ERROR        (1 << 20)
#define SD_ERROR        (1 << 19)
#define CID_CSD_OVERWRITE   (1 << 16)
#define WP_ERASE_SKIP       (1 << 15)
#define CARD_ECC_DISABLED   (1 << 14)
#define ERASE_RESET     (1 << 13)
#define CURRENT_STATE       (7 << 9)
#define READY_FOR_DATA      (1 << 8)
#define APP_CMD         (1 << 5)
#define AKE_SEQ_ERROR       (1 << 3)
#define OCR_CCS_BITN        30

typedef enum {
    sd_none = -1,
    sd_bc = 0,  /* broadcast -- no response */
    sd_bcr, /* broadcast with response */
    sd_ac,  /* addressed -- no data transfer */
    sd_adtc,    /* addressed with data transfer */
} sd_cmd_type_t;

typedef struct {
    Uns8 cmd;
    Uns32 arg;
    Uns8 crc;
} SDRequest;

typedef enum {
    sd_r0 = 0,    /* no response */
    sd_r1,        /* normal response command */
    sd_r2_i,      /* CID register */
    sd_r2_s,      /* CSD register */
    sd_r3,        /* OCR register */
    sd_r6 = 6,    /* Published RCA response */
    sd_r7,        /* Operating voltage */
    sd_r1b = -1,
    sd_illegal = -2,
} sd_rsp_type_t;

enum SDCardModes {
    sd_inactive,
    sd_card_identification_mode,
    sd_data_transfer_mode,
};

enum SDCardStates {
    sd_inactive_state = -1,
    sd_idle_state = 0,
    sd_ready_state,
    sd_identification_state,
    sd_standby_state,
    sd_transfer_state,
    sd_sendingdata_state,
    sd_receivingdata_state,
    sd_programming_state,
    sd_disconnect_state,
};

struct SDState {

    Uns32 mode;    /* current card mode, one of SDCardModes */
    Int32 state;    /* current card state, one of SDCardStates */
    Uns32 ocr;
    Uns8 scr[8];
    Uns8 cid[16];
    Uns8 csd[16];
    Uns8 ext_csd[512];
    Uns16 rca;
    Uns32 card_status;
    Uns8 sd_status[64];
    Uns32 vhs;
    Bool wp_switch;
    int *wp_groups;
    Int32 wpgrps_size;
    Uns64 size;
    int blk_len;
    Uns32 erase_start;
    Uns32 erase_end;
    Uns8 pwd[16];
    Uns32 pwd_len;
    Uns8 function_group[6];

    Bool spi, mmc;
    Uns8 current_cmd;
    /* True if we will handle the next command as an ACMD. Note that this does
     * *not* track the APP_CMD status bit!
     */
    Bool expecting_acmd;
    Uns32 blk_written;
    Uns64 data_start;
    Uns32 data_offset;
    Uns8 data[512];
    qemu_irq readonly_cb;
    qemu_irq inserted_cb;
    BlockDriverStateP bdrv;
    Uns8 *buf;

    Bool enable;
    int buswidth, highspeed;

    const char *processorName;    // debug only
};

typedef struct SDState SDState;

SDState *sd_init(vmiProcessorP processor, pseHandlesT pse, BlockDriverStateP bs, Bool is_spi, Bool is_mmc, Uns32 diag);
int sd_do_command(SDState *sd, SDRequest *req,
                  Uns8 *response, Uns32 diag);
void sd_write_data(SDState *sd, Uns8 value, Uns32 diag);
Uns8 sd_read_data(SDState *sd, Uns32 diag);
void sd_set_cb(SDState *sd, qemu_irq readonly, qemu_irq insert);

Bool sd_data_ready(SDState *sd);
void sd_enable(SDState *sd, Bool enable);
Bool sd_is_mmc(SDState *sd);

#endif  /* __hw_sd_h */
