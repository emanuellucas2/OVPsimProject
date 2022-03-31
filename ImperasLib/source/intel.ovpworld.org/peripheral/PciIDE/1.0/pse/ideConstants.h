/*
 * QEMU IDE Disk and CD-ROM Emulator.
 *
 * Copyright (c) 2003-2004 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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


#ifndef IDECONSTANTS_H
#define IDECONSTANTS_H

/* Bits of HD_STATUS */
#define ERR_STAT        0x01
#define INDEX_STAT      0x02
#define ECC_STAT        0x04    /* Corrected error */
#define DRQ_STAT        0x08
#define SEEK_STAT       0x10
#define SRV_STAT        0x10
#define WRERR_STAT      0x20
#define READY_STAT      0x40
#define BUSY_STAT       0x80

/* Bits for HD_ERROR */
#define MARK_ERR        0x01    /* Bad address mark */
#define TRK0_ERR        0x02    /* couldn't find track 0 */
#define ABRT_ERR        0x04    /* Command aborted */
#define MCR_ERR         0x08    /* media change request */
#define ID_ERR          0x10    /* ID field not found */
#define MC_ERR          0x20    /* media changed */
#define ECC_ERR         0x40    /* Uncorrectable ECC error */
#define BBD_ERR         0x80    /* pre-EIDE meaning:  block marked bad */
#define ICRC_ERR        0x80    /* new meaning:  CRC error during transfer */

/* Bits of HD_NSECTOR */
#define CD              0x01
#define IO              0x02
#define REL             0x04
#define TAG_MASK        0xf8

#define IDE_CMD_RESET           0x04
#define IDE_CMD_DISABLE_IRQ     0x02

/* ATA/ATAPI Commands pre T13 Spec */
#define WIN_NOP                 0x00
/*
 *    0x01->0x02 Reserved
 */
#define CFA_REQ_EXT_ERROR_CODE  0x03 /* CFA Request Extended Error Code */
/*
 *    0x04->0x07 Reserved
 */
#define WIN_SRST                0x08 /* ATAPI soft reset command */
#define WIN_DEVICE_RESET        0x08
/*
 *    0x09->0x0F Reserved
 */
#define WIN_RECAL              0x10
#define WIN_RESTORE            WIN_RECAL
/*
 *    0x10->0x1F Reserved
 */
#define WIN_READ                0x20 /* 28-Bit */
#define WIN_READ_ONCE           0x21 /* 28-Bit without retries */
#define WIN_READ_LONG           0x22 /* 28-Bit */
#define WIN_READ_LONG_ONCE      0x23 /* 28-Bit without retries */
#define WIN_READ_EXT            0x24 /* 48-Bit */
#define WIN_READDMA_EXT         0x25 /* 48-Bit */
#define WIN_READDMA_QUEUED_EXT  0x26 /* 48-Bit */
#define WIN_READ_NATIVE_MAX_EXT 0x27 /* 48-Bit */
/*
 *    0x28
 */
#define WIN_MULTREAD_EXT        0x29 /* 48-Bit */
/*
 *    0x2A->0x2F Reserved
 */
#define WIN_WRITE               0x30 /* 28-Bit */
#define WIN_WRITE_ONCE          0x31 /* 28-Bit without retries */
#define WIN_WRITE_LONG          0x32 /* 28-Bit */
#define WIN_WRITE_LONG_ONCE     0x33 /* 28-Bit without retries */
#define WIN_WRITE_EXT           0x34 /* 48-Bit */
#define WIN_WRITEDMA_EXT        0x35 /* 48-Bit */
#define WIN_WRITEDMA_QUEUED_EXT 0x36 /* 48-Bit */
#define WIN_SET_MAX_EXT         0x37 /* 48-Bit */
#define CFA_WRITE_SECT_WO_ERASE 0x38 /* CFA Write Sectors without erase */
#define WIN_MULTWRITE_EXT       0x39 /* 48-Bit */
/*
 *    0x3A->0x3B Reserved
 */
#define WIN_WRITE_VERIFY        0x3C /* 28-Bit */
/*
 *    0x3D->0x3F Reserved
 */
#define WIN_VERIFY              0x40 /* 28-Bit - Read Verify Sectors */
#define WIN_VERIFY_ONCE         0x41 /* 28-Bit - without retries */
#define WIN_VERIFY_EXT          0x42 /* 48-Bit */
/*
 *    0x43->0x4F Reserved
 */
#define WIN_FORMAT              0x50
/*
 *    0x51->0x5F Reserved
 */
#define WIN_INIT                0x60
/*
 *    0x61->0x5F Reserved
 */
#define WIN_SEEK                0x70 /* 0x70-0x7F Reserved */
#define CFA_TRANSLATE_SECTOR    0x87 /* CFA Translate Sector */
#define WIN_DIAGNOSE            0x90
#define WIN_SPECIFY             0x91 /* set drive geometry translation */
#define WIN_DOWNLOAD_MICROCODE  0x92
#define WIN_STANDBYNOW2         0x94
#define CFA_IDLEIMMEDIATE       0x95 /* force drive to become "ready" */
#define WIN_STANDBY2            0x96
#define WIN_SETIDLE2            0x97
#define WIN_CHECKPOWERMODE2     0x98
#define WIN_SLEEPNOW2           0x99
/*
 *    0x9A VENDOR
 */
#define WIN_PACKETCMD                    0xA0 /* Send a packet command. */
#define WIN_PIDENTIFY                    0xA1 /* identify ATAPI device    */
#define WIN_QUEUED_SERVICE               0xA2
#define WIN_SMART                        0xB0 /* self-monitoring and reporting */
#define CFA_ACCESS_METADATA_STORAGE      0xB8
#define CFA_ERASE_SECTORS                0xC0 /* microdrives implement as NOP */
#define WIN_MULTREAD                     0xC4 /* read sectors using multiple mode*/
#define WIN_MULTWRITE                    0xC5 /* write sectors using multiple mode */
#define WIN_SETMULT                      0xC6 /* enable/disable multiple mode */
#define WIN_READDMA_QUEUED               0xC7 /* read sectors using Queued DMA transfers */
#define WIN_READDMA                      0xC8 /* read sectors using DMA transfers */
#define WIN_READDMA_ONCE                 0xC9 /* 28-Bit - without retries */
#define WIN_WRITEDMA                     0xCA /* write sectors using DMA transfers */
#define WIN_WRITEDMA_ONCE                0xCB /* 28-Bit - without retries */
#define WIN_WRITEDMA_QUEUED              0xCC /* write sectors using Queued DMA transfers */
#define CFA_WRITE_MULTI_WO_ERASE         0xCD /* CFA Write multiple without erase */
#define WIN_GETMEDIASTATUS               0xDA
#define WIN_ACKMEDIACHANGE               0xDB /* ATA-1, ATA-2 vendor */
#define WIN_POSTBOOT                     0xDC
#define WIN_PREBOOT                      0xDD
#define WIN_DOORLOCK                     0xDE /* lock door on removable drives */
#define WIN_DOORUNLOCK                   0xDF /* unlock door on removable drives */
#define WIN_STANDBYNOW1                  0xE0
#define WIN_IDLEIMMEDIATE                0xE1 /* force drive to become "ready" */
#define WIN_STANDBY                      0xE2 /* Set device in Standby Mode */
#define WIN_SETIDLE1                     0xE3
#define WIN_READ_BUFFER                  0xE4 /* force read only 1 sector */
#define WIN_CHECKPOWERMODE1              0xE5
#define WIN_SLEEPNOW1                    0xE6
#define WIN_FLUSH_CACHE                  0xE7
#define WIN_WRITE_BUFFER                 0xE8 /* force write only 1 sector */
#define WIN_WRITE_SAME                   0xE9 /* read ata-2 to use */
    /* SET_FEATURES 0x22 or 0xDD */
#define WIN_FLUSH_CACHE_EXT              0xEA /* 48-Bit */
#define WIN_IDENTIFY                     0xEC /* ask drive to identify itself    */
#define WIN_MEDIAEJECT                   0xED
#define WIN_IDENTIFY_DMA                 0xEE /* same as WIN_IDENTIFY, but DMA */
#define WIN_SETFEATURES                  0xEF /* set special drive features */
#define EXABYTE_ENABLE_NEST              0xF0
#define IBM_SENSE_CONDITION              0xF0 /* measure disk temperature */
#define WIN_SECURITY_SET_PASS            0xF1
#define WIN_SECURITY_UNLOCK              0xF2
#define WIN_SECURITY_ERASE_PREPARE       0xF3
#define WIN_SECURITY_ERASE_UNIT          0xF4
#define WIN_SECURITY_FREEZE_LOCK         0xF5
#define CFA_WEAR_LEVEL                   0xF5 /* microdrives implement as NOP */
#define WIN_SECURITY_DISABLE             0xF6
#define WIN_READ_NATIVE_MAX              0xF8 /* return the native maximum address */
#define WIN_SET_MAX                      0xF9
#define DISABLE_SEAGATE                  0xFB

/* set to 1 set disable mult support */
#define MAX_MULT_SECTORS 16

/* ATAPI defines */

#define ATAPI_PACKET_SIZE 12

/* The generic packet command opcodes for CD/DVD Logical Units,
 * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
#define GPCMD_BLANK                       0xa1
#define GPCMD_CLOSE_TRACK                 0x5b
#define GPCMD_FLUSH_CACHE                 0x35
#define GPCMD_FORMAT_UNIT                 0x04
#define GPCMD_GET_CONFIGURATION           0x46
#define GPCMD_GET_EVENT_STATUS_NOTIFICATION 0x4a
#define GPCMD_GET_PERFORMANCE             0xac
#define GPCMD_INQUIRY                     0x12
#define GPCMD_LOAD_UNLOAD                 0xa6
#define GPCMD_MECHANISM_STATUS            0xbd
#define GPCMD_MODE_SELECT_10              0x55
#define GPCMD_MODE_SENSE_10               0x5a
#define GPCMD_PAUSE_RESUME                0x4b
#define GPCMD_PLAY_AUDIO_10               0x45
#define GPCMD_PLAY_AUDIO_MSF              0x47
#define GPCMD_PLAY_AUDIO_TI               0x48
#define GPCMD_PLAY_CD                     0xbc
#define GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL  0x1e
#define GPCMD_READ_10                     0x28
#define GPCMD_READ_12                     0xa8
#define GPCMD_READ_CDVD_CAPACITY          0x25
#define GPCMD_READ_CD                     0xbe
#define GPCMD_READ_CD_MSF                 0xb9
#define GPCMD_READ_DISC_INFO              0x51
#define GPCMD_READ_DVD_STRUCTURE          0xad
#define GPCMD_READ_FORMAT_CAPACITIES      0x23
#define GPCMD_READ_HEADER                 0x44
#define GPCMD_READ_TRACK_RZONE_INFO       0x52
#define GPCMD_READ_SUBCHANNEL             0x42
#define GPCMD_READ_TOC_PMA_ATIP           0x43
#define GPCMD_REPAIR_RZONE_TRACK          0x58
#define GPCMD_REPORT_KEY                  0xa4
#define GPCMD_REQUEST_SENSE               0x03
#define GPCMD_RESERVE_RZONE_TRACK         0x53
#define GPCMD_SCAN                        0xba
#define GPCMD_SEEK                        0x2b
#define GPCMD_SEND_DVD_STRUCTURE          0xad
#define GPCMD_SEND_EVENT                  0xa2
#define GPCMD_SEND_KEY                    0xa3
#define GPCMD_SEND_OPC                    0x54
#define GPCMD_SET_READ_AHEAD              0xa7
#define GPCMD_SET_STREAMING               0xb6
#define GPCMD_START_STOP_UNIT             0x1b
#define GPCMD_STOP_PLAY_SCAN              0x4e
#define GPCMD_TEST_UNIT_READY             0x00
#define GPCMD_VERIFY_10                   0x2f
#define GPCMD_WRITE_10                    0x2a
#define GPCMD_WRITE_AND_VERIFY_10         0x2e
/* This is listed as optional in ATAPI 2.6, but is (curiously)
 * missing from Mt. Fuji, Table 57.  It _is_ mentioned in Mt. Fuji
 * Table 377 as an MMC command for SCSi devices though...  Most ATAPI
 * drives support it. */
#define GPCMD_SET_SPEED                   0xbb
/* This seems to be a SCSI specific CD-ROM opcode
 * to play data at track/index */
#define GPCMD_PLAYAUDIO_TI                0x48
/*
 * From MS Media Status Notification Support Specification. For
 * older drives only.
 */
#define GPCMD_GET_MEDIA_STATUS            0xda
#define GPCMD_MODE_SENSE_6                0x1a

/* Mode page codes for mode sense/set */
#define GPMODE_R_W_ERROR_PAGE             0x01
#define GPMODE_WRITE_PARMS_PAGE           0x05
#define GPMODE_AUDIO_CTL_PAGE             0x0e
#define GPMODE_POWER_PAGE                 0x1a
#define GPMODE_FAULT_FAIL_PAGE            0x1c
#define GPMODE_TO_PROTECT_PAGE            0x1d
#define GPMODE_CAPABILITIES_PAGE          0x2a
#define GPMODE_ALL_PAGES                  0x3f

/* Not in Mt. Fuji, but in ATAPI 2.6 -- depricated now in favor
 * of MODE_SENSE_POWER_PAGE */
#define GPMODE_CDROM_PAGE                0x0d

#define ATAPI_INT_REASON_CD              0x01 /* 0 = data transfer */
#define ATAPI_INT_REASON_IO              0x02 /* 1 = transfer to the host */
#define ATAPI_INT_REASON_REL             0x04
#define ATAPI_INT_REASON_TAG             0xf8

/* same constants as bochs */
#define ASC_ILLEGAL_OPCODE                   0x20
#define ASC_LOGICAL_BLOCK_OOR                0x21
#define ASC_INV_FIELD_IN_CMD_PACKET          0x24
#define ASC_MEDIUM_NOT_PRESENT               0x3a
#define ASC_SAVING_PARAMETERS_NOT_SUPPORTED  0x39

#define CFA_NO_ERROR            0x00
#define CFA_MISC_ERROR          0x09
#define CFA_INVALID_COMMAND     0x20
#define CFA_INVALID_ADDRESS     0x21
#define CFA_ADDRESS_OVERFLOW    0x2f

#define SENSE_NONE            0
#define SENSE_NOT_READY       2
#define SENSE_ILLEGAL_REQUEST 5
#define SENSE_UNIT_ATTENTION  6

#define BM_STATUS_DMAING 0x01
#define BM_STATUS_ERROR  0x02
#define BM_STATUS_INT    0x04

#define BM_CMD_START     0x01
#define BM_CMD_READ      0x08

#define IDE_TYPE_PIIX3   0
#define IDE_TYPE_CMD646  1
#define IDE_TYPE_PIIX4   2

/* CMD646 specific */
#define MRDMODE             0x71
#define MRDMODE_INTR_CH0    0x04
#define MRDMODE_INTR_CH1    0x08
#define MRDMODE_BLK_CH0     0x10
#define MRDMODE_BLK_CH1     0x20
#define UDIDETCR0           0x73
#define UDIDETCR1           0x7B


#endif /*IDECONSTANTS_H_*/
