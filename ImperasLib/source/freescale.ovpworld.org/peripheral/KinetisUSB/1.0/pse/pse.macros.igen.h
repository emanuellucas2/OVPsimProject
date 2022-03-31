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
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_PERID_POFFSET         0x0
#define BPORT1_AB_PERID                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERID_POFFSET)
#define BPORT1_AB_PERID_ID              0x3f
#define BPORT1_AB_PERID_ID_GET(_v)      (_v & 0x3f)

#define BPORT1_AB_IDCOMP_POFFSET        0x4
#define BPORT1_AB_IDCOMP                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IDCOMP_POFFSET)
#define BPORT1_AB_IDCOMP_NID            0x3f
#define BPORT1_AB_IDCOMP_NID_GET(_v)    (_v & 0x3f)

#define BPORT1_AB_REV_POFFSET           0x8
#define BPORT1_AB_REV                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REV_POFFSET)
#define BPORT1_AB_REV_REV               0xff
#define BPORT1_AB_REV_REV_GET(_v)       (_v & 0xff)

#define BPORT1_AB_ADDINFO_POFFSET       0xc
#define BPORT1_AB_ADDINFO               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ADDINFO_POFFSET)
#define BPORT1_AB_ADDINFO_IEHOST        0x1
#define BPORT1_AB_ADDINFO_IEHOST_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ADDINFO_IRQNUM        (0x1f << 3)
#define BPORT1_AB_ADDINFO_IRQNUM_GET(_v)  ((_v >> 3) & 0x1f)

#define BPORT1_AB_OTGISTAT_POFFSET      0x10
#define BPORT1_AB_OTGISTAT              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGISTAT_POFFSET)
#define BPORT1_AB_OTGISTAT_AVBUSCHG     0x1
#define BPORT1_AB_OTGISTAT_AVBUSCHG_GET(_v)  (_v & 0x1)
#define BPORT1_AB_OTGISTAT_B_SESS_CHG   (0x1 << 2)
#define BPORT1_AB_OTGISTAT_B_SESS_CHG_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_OTGISTAT_IDCHG        (0x1 << 7)
#define BPORT1_AB_OTGISTAT_IDCHG_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_OTGISTAT_LINE_STATE_CHG  (0x1 << 5)
#define BPORT1_AB_OTGISTAT_LINE_STATE_CHG_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_OTGISTAT_ONEMSEC      (0x1 << 6)
#define BPORT1_AB_OTGISTAT_ONEMSEC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_OTGISTAT_SESSVLDCHG   (0x1 << 3)
#define BPORT1_AB_OTGISTAT_SESSVLDCHG_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_OTGICR_POFFSET        0x14
#define BPORT1_AB_OTGICR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGICR_POFFSET)
#define BPORT1_AB_OTGICR_AVBUSEN        0x1
#define BPORT1_AB_OTGICR_AVBUSEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_OTGICR_BSESSEN        (0x1 << 2)
#define BPORT1_AB_OTGICR_BSESSEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_OTGICR_IDEN           (0x1 << 7)
#define BPORT1_AB_OTGICR_IDEN_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_OTGICR_LINESTATEEN    (0x1 << 5)
#define BPORT1_AB_OTGICR_LINESTATEEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_OTGICR_ONEMSECEN      (0x1 << 6)
#define BPORT1_AB_OTGICR_ONEMSECEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_OTGICR_SESSVLDEN      (0x1 << 3)
#define BPORT1_AB_OTGICR_SESSVLDEN_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_OTGSTAT_POFFSET       0x18
#define BPORT1_AB_OTGSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGSTAT_POFFSET)
#define BPORT1_AB_OTGSTAT_AVBUSVLD      0x1
#define BPORT1_AB_OTGSTAT_AVBUSVLD_GET(_v)  (_v & 0x1)
#define BPORT1_AB_OTGSTAT_BSESSEND      (0x1 << 2)
#define BPORT1_AB_OTGSTAT_BSESSEND_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_OTGSTAT_ID            (0x1 << 7)
#define BPORT1_AB_OTGSTAT_ID_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_OTGSTAT_LINESTATESTABLE  (0x1 << 5)
#define BPORT1_AB_OTGSTAT_LINESTATESTABLE_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_OTGSTAT_ONEMSECEN     (0x1 << 6)
#define BPORT1_AB_OTGSTAT_ONEMSECEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_OTGSTAT_SESS_VLD      (0x1 << 3)
#define BPORT1_AB_OTGSTAT_SESS_VLD_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_OTGCTL_POFFSET        0x1c
#define BPORT1_AB_OTGCTL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGCTL_POFFSET)
#define BPORT1_AB_OTGCTL_DMLOW          (0x1 << 4)
#define BPORT1_AB_OTGCTL_DMLOW_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_OTGCTL_DPHIGH         (0x1 << 7)
#define BPORT1_AB_OTGCTL_DPHIGH_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_OTGCTL_DPLOW          (0x1 << 5)
#define BPORT1_AB_OTGCTL_DPLOW_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_OTGCTL_OTGEN          (0x1 << 2)
#define BPORT1_AB_OTGCTL_OTGEN_GET(_v)  ((_v >> 2) & 0x1)

#define BPORT1_AB_ISTAT_POFFSET         0x80
#define BPORT1_AB_ISTAT                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ISTAT_POFFSET)
#define BPORT1_AB_ISTAT_ATTACH          (0x1 << 6)
#define BPORT1_AB_ISTAT_ATTACH_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_ISTAT_ERROR           (0x1 << 1)
#define BPORT1_AB_ISTAT_ERROR_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_ISTAT_RESUME          (0x1 << 5)
#define BPORT1_AB_ISTAT_RESUME_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ISTAT_SLEEP           (0x1 << 4)
#define BPORT1_AB_ISTAT_SLEEP_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_ISTAT_SOFTOK          (0x1 << 2)
#define BPORT1_AB_ISTAT_SOFTOK_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ISTAT_STALL           (0x1 << 7)
#define BPORT1_AB_ISTAT_STALL_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_ISTAT_TOKDNE          (0x1 << 3)
#define BPORT1_AB_ISTAT_TOKDNE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ISTAT_USBRST          0x1
#define BPORT1_AB_ISTAT_USBRST_GET(_v)  (_v & 0x1)

#define BPORT1_AB_INTEN_POFFSET         0x84
#define BPORT1_AB_INTEN                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTEN_POFFSET)
#define BPORT1_AB_INTEN_ATTACHEN        (0x1 << 6)
#define BPORT1_AB_INTEN_ATTACHEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTEN_ERROREN         (0x1 << 1)
#define BPORT1_AB_INTEN_ERROREN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTEN_RESUMEEN        (0x1 << 5)
#define BPORT1_AB_INTEN_RESUMEEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTEN_SLEEPEN         (0x1 << 4)
#define BPORT1_AB_INTEN_SLEEPEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTEN_SOFTOKEN        (0x1 << 2)
#define BPORT1_AB_INTEN_SOFTOKEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTEN_STALLEN         (0x1 << 7)
#define BPORT1_AB_INTEN_STALLEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTEN_TOKDNEEN        (0x1 << 3)
#define BPORT1_AB_INTEN_TOKDNEEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTEN_USBRSTEN        0x1
#define BPORT1_AB_INTEN_USBRSTEN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_ERRSTAT_POFFSET       0x88
#define BPORT1_AB_ERRSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ERRSTAT_POFFSET)
#define BPORT1_AB_ERRSTAT_BTOERR        (0x1 << 4)
#define BPORT1_AB_ERRSTAT_BTOERR_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ERRSTAT_BTSERR        (0x1 << 7)
#define BPORT1_AB_ERRSTAT_BTSERR_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ERRSTAT_CRC16         (0x1 << 2)
#define BPORT1_AB_ERRSTAT_CRC16_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ERRSTAT_CRC5EOF       (0x1 << 1)
#define BPORT1_AB_ERRSTAT_CRC5EOF_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ERRSTAT_DFN8          (0x1 << 3)
#define BPORT1_AB_ERRSTAT_DFN8_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ERRSTAT_DMAERR        (0x1 << 5)
#define BPORT1_AB_ERRSTAT_DMAERR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ERRSTAT_PIDERR        0x1
#define BPORT1_AB_ERRSTAT_PIDERR_GET(_v)  (_v & 0x1)

#define BPORT1_AB_ERREN_POFFSET         0x8c
#define BPORT1_AB_ERREN                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ERREN_POFFSET)
#define BPORT1_AB_ERREN_BTOERREN        (0x1 << 4)
#define BPORT1_AB_ERREN_BTOERREN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ERREN_BTSERREN        (0x1 << 7)
#define BPORT1_AB_ERREN_BTSERREN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ERREN_CRC16EN         (0x1 << 2)
#define BPORT1_AB_ERREN_CRC16EN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ERREN_CRC5EOFEN       (0x1 << 1)
#define BPORT1_AB_ERREN_CRC5EOFEN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ERREN_DFN8EN          (0x1 << 3)
#define BPORT1_AB_ERREN_DFN8EN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ERREN_DMAERREN        (0x1 << 5)
#define BPORT1_AB_ERREN_DMAERREN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ERREN_PIDERREN        0x1
#define BPORT1_AB_ERREN_PIDERREN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_STAT_POFFSET          0x90
#define BPORT1_AB_STAT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STAT_POFFSET)
#define BPORT1_AB_STAT_ENDP             (0xf << 4)
#define BPORT1_AB_STAT_ENDP_GET(_v)     ((_v >> 4) & 0xf)
#define BPORT1_AB_STAT_ODD              (0x1 << 2)
#define BPORT1_AB_STAT_ODD_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_STAT_TX               (0x1 << 3)
#define BPORT1_AB_STAT_TX_GET(_v)       ((_v >> 3) & 0x1)

#define BPORT1_AB_CTL_POFFSET           0x94
#define BPORT1_AB_CTL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTL_POFFSET)
#define BPORT1_AB_CTL_HOSTMODEEN        (0x1 << 3)
#define BPORT1_AB_CTL_HOSTMODEEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_CTL_JSTATE            (0x1 << 7)
#define BPORT1_AB_CTL_JSTATE_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_CTL_ODDRST            (0x1 << 1)
#define BPORT1_AB_CTL_ODDRST_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_CTL_RESET             (0x1 << 4)
#define BPORT1_AB_CTL_RESET_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_CTL_RESUME            (0x1 << 2)
#define BPORT1_AB_CTL_RESUME_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_CTL_SE0               (0x1 << 6)
#define BPORT1_AB_CTL_SE0_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_CTL_TXSUSPENDTOKENBUSY  (0x1 << 5)
#define BPORT1_AB_CTL_TXSUSPENDTOKENBUSY_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_CTL_USBENSOFEN        0x1
#define BPORT1_AB_CTL_USBENSOFEN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_ADDR_POFFSET          0x98
#define BPORT1_AB_ADDR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ADDR_POFFSET)
#define BPORT1_AB_ADDR_ADDR             0x7f
#define BPORT1_AB_ADDR_ADDR_GET(_v)     (_v & 0x7f)
#define BPORT1_AB_ADDR_LSEN             (0x1 << 7)
#define BPORT1_AB_ADDR_LSEN_GET(_v)     ((_v >> 7) & 0x1)

#define BPORT1_AB_BDTPAGE1_POFFSET      0x9c
#define BPORT1_AB_BDTPAGE1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDTPAGE1_POFFSET)
#define BPORT1_AB_BDTPAGE1_BDTBA        (0x7f << 1)
#define BPORT1_AB_BDTPAGE1_BDTBA_GET(_v)  ((_v >> 1) & 0x7f)

#define BPORT1_AB_FRMNUML_POFFSET       0xa0
#define BPORT1_AB_FRMNUML               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FRMNUML_POFFSET)
#define BPORT1_AB_FRMNUML_FRM           0xff
#define BPORT1_AB_FRMNUML_FRM_GET(_v)   (_v & 0xff)

#define BPORT1_AB_FRMNUMH_POFFSET       0xa4
#define BPORT1_AB_FRMNUMH               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FRMNUMH_POFFSET)
#define BPORT1_AB_FRMNUMH_FRM           0x7
#define BPORT1_AB_FRMNUMH_FRM_GET(_v)   (_v & 0x7)

#define BPORT1_AB_TOKEN_POFFSET         0xa8
#define BPORT1_AB_TOKEN                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TOKEN_POFFSET)
#define BPORT1_AB_TOKEN_TOKENENDPT      0xf
#define BPORT1_AB_TOKEN_TOKENENDPT_GET(_v)  (_v & 0xf)
#define BPORT1_AB_TOKEN_TOKENPID        (0xf << 4)
#define BPORT1_AB_TOKEN_TOKENPID_GET(_v)  ((_v >> 4) & 0xf)

#define BPORT1_AB_SOFTHLD_POFFSET       0xac
#define BPORT1_AB_SOFTHLD               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOFTHLD_POFFSET)
#define BPORT1_AB_SOFTHLD_CNT           0xff
#define BPORT1_AB_SOFTHLD_CNT_GET(_v)   (_v & 0xff)

#define BPORT1_AB_BDTPAGE2_POFFSET      0xb0
#define BPORT1_AB_BDTPAGE2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDTPAGE2_POFFSET)
#define BPORT1_AB_BDTPAGE2_BDTBA        0xff
#define BPORT1_AB_BDTPAGE2_BDTBA_GET(_v)  (_v & 0xff)

#define BPORT1_AB_BDTPAGE3_POFFSET      0xb4
#define BPORT1_AB_BDTPAGE3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDTPAGE3_POFFSET)
#define BPORT1_AB_BDTPAGE3_BDTBA        0xff
#define BPORT1_AB_BDTPAGE3_BDTBA_GET(_v)  (_v & 0xff)

#define BPORT1_AB_ENDPOINT0_POFFSET     0xc0
#define BPORT1_AB_ENDPOINT0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT0_POFFSET)
#define BPORT1_AB_ENDPOINT0_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT0_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT0_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT0_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT0_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT0_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT0_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT0_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT0_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT0_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT0_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT0_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT0_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT0_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT1_POFFSET     0xc4
#define BPORT1_AB_ENDPOINT1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT1_POFFSET)
#define BPORT1_AB_ENDPOINT1_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT1_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT1_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT1_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT1_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT1_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT1_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT1_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT1_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT1_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT1_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT1_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT1_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT1_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT2_POFFSET     0xc8
#define BPORT1_AB_ENDPOINT2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT2_POFFSET)
#define BPORT1_AB_ENDPOINT2_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT2_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT2_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT2_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT2_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT2_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT2_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT2_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT2_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT2_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT2_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT2_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT2_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT2_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT3_POFFSET     0xcc
#define BPORT1_AB_ENDPOINT3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT3_POFFSET)
#define BPORT1_AB_ENDPOINT3_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT3_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT3_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT3_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT3_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT3_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT3_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT3_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT3_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT3_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT3_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT3_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT3_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT3_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT4_POFFSET     0xd0
#define BPORT1_AB_ENDPOINT4             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT4_POFFSET)
#define BPORT1_AB_ENDPOINT4_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT4_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT4_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT4_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT4_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT4_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT4_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT4_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT4_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT4_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT4_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT4_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT4_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT4_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT5_POFFSET     0xd4
#define BPORT1_AB_ENDPOINT5             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT5_POFFSET)
#define BPORT1_AB_ENDPOINT5_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT5_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT5_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT5_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT5_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT5_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT5_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT5_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT5_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT5_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT5_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT5_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT5_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT5_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT6_POFFSET     0xd8
#define BPORT1_AB_ENDPOINT6             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT6_POFFSET)
#define BPORT1_AB_ENDPOINT6_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT6_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT6_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT6_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT6_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT6_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT6_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT6_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT6_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT6_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT6_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT6_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT6_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT6_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT7_POFFSET     0xdc
#define BPORT1_AB_ENDPOINT7             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT7_POFFSET)
#define BPORT1_AB_ENDPOINT7_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT7_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT7_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT7_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT7_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT7_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT7_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT7_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT7_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT7_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT7_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT7_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT7_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT7_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT8_POFFSET     0xe0
#define BPORT1_AB_ENDPOINT8             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT8_POFFSET)
#define BPORT1_AB_ENDPOINT8_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT8_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT8_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT8_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT8_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT8_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT8_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT8_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT8_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT8_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT8_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT8_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT8_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT8_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT9_POFFSET     0xe4
#define BPORT1_AB_ENDPOINT9             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT9_POFFSET)
#define BPORT1_AB_ENDPOINT9_EPCTLDIS    (0x1 << 4)
#define BPORT1_AB_ENDPOINT9_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT9_EPHSHK      0x1
#define BPORT1_AB_ENDPOINT9_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT9_EPRXEN      (0x1 << 3)
#define BPORT1_AB_ENDPOINT9_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT9_EPSTALL     (0x1 << 1)
#define BPORT1_AB_ENDPOINT9_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT9_EPTXEN      (0x1 << 2)
#define BPORT1_AB_ENDPOINT9_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT9_HOSTWOHUB   (0x1 << 7)
#define BPORT1_AB_ENDPOINT9_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT9_RETRYDIS    (0x1 << 6)
#define BPORT1_AB_ENDPOINT9_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT10_POFFSET    0xe8
#define BPORT1_AB_ENDPOINT10            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT10_POFFSET)
#define BPORT1_AB_ENDPOINT10_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT10_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT10_EPHSHK     0x1
#define BPORT1_AB_ENDPOINT10_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT10_EPRXEN     (0x1 << 3)
#define BPORT1_AB_ENDPOINT10_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT10_EPSTALL    (0x1 << 1)
#define BPORT1_AB_ENDPOINT10_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT10_EPTXEN     (0x1 << 2)
#define BPORT1_AB_ENDPOINT10_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT10_HOSTWOHUB  (0x1 << 7)
#define BPORT1_AB_ENDPOINT10_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT10_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT10_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT11_POFFSET    0xec
#define BPORT1_AB_ENDPOINT11            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT11_POFFSET)
#define BPORT1_AB_ENDPOINT11_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT11_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT11_EPHSHK     0x1
#define BPORT1_AB_ENDPOINT11_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT11_EPRXEN     (0x1 << 3)
#define BPORT1_AB_ENDPOINT11_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT11_EPSTALL    (0x1 << 1)
#define BPORT1_AB_ENDPOINT11_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT11_EPTXEN     (0x1 << 2)
#define BPORT1_AB_ENDPOINT11_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT11_HOSTWOHUB  (0x1 << 7)
#define BPORT1_AB_ENDPOINT11_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT11_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT11_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT12_POFFSET    0xf0
#define BPORT1_AB_ENDPOINT12            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT12_POFFSET)
#define BPORT1_AB_ENDPOINT12_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT12_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT12_EPHSHK     0x1
#define BPORT1_AB_ENDPOINT12_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT12_EPRXEN     (0x1 << 3)
#define BPORT1_AB_ENDPOINT12_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT12_EPSTALL    (0x1 << 1)
#define BPORT1_AB_ENDPOINT12_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT12_EPTXEN     (0x1 << 2)
#define BPORT1_AB_ENDPOINT12_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT12_HOSTWOHUB  (0x1 << 7)
#define BPORT1_AB_ENDPOINT12_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT12_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT12_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT13_POFFSET    0xf4
#define BPORT1_AB_ENDPOINT13            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT13_POFFSET)
#define BPORT1_AB_ENDPOINT13_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT13_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT13_EPHSHK     0x1
#define BPORT1_AB_ENDPOINT13_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT13_EPRXEN     (0x1 << 3)
#define BPORT1_AB_ENDPOINT13_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT13_EPSTALL    (0x1 << 1)
#define BPORT1_AB_ENDPOINT13_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT13_EPTXEN     (0x1 << 2)
#define BPORT1_AB_ENDPOINT13_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT13_HOSTWOHUB  (0x1 << 7)
#define BPORT1_AB_ENDPOINT13_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT13_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT13_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT14_POFFSET    0xf8
#define BPORT1_AB_ENDPOINT14            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT14_POFFSET)
#define BPORT1_AB_ENDPOINT14_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT14_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT14_EPHSHK     0x1
#define BPORT1_AB_ENDPOINT14_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT14_EPRXEN     (0x1 << 3)
#define BPORT1_AB_ENDPOINT14_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT14_EPSTALL    (0x1 << 1)
#define BPORT1_AB_ENDPOINT14_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT14_EPTXEN     (0x1 << 2)
#define BPORT1_AB_ENDPOINT14_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT14_HOSTWOHUB  (0x1 << 7)
#define BPORT1_AB_ENDPOINT14_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT14_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT14_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_ENDPOINT15_POFFSET    0xfc
#define BPORT1_AB_ENDPOINT15            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPOINT15_POFFSET)
#define BPORT1_AB_ENDPOINT15_EPCTLDIS   (0x1 << 4)
#define BPORT1_AB_ENDPOINT15_EPCTLDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_ENDPOINT15_EPHSHK     0x1
#define BPORT1_AB_ENDPOINT15_EPHSHK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPOINT15_EPRXEN     (0x1 << 3)
#define BPORT1_AB_ENDPOINT15_EPRXEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ENDPOINT15_EPSTALL    (0x1 << 1)
#define BPORT1_AB_ENDPOINT15_EPSTALL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPOINT15_EPTXEN     (0x1 << 2)
#define BPORT1_AB_ENDPOINT15_EPTXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ENDPOINT15_HOSTWOHUB  (0x1 << 7)
#define BPORT1_AB_ENDPOINT15_HOSTWOHUB_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPOINT15_RETRYDIS   (0x1 << 6)
#define BPORT1_AB_ENDPOINT15_RETRYDIS_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_USBCTRL_POFFSET       0x100
#define BPORT1_AB_USBCTRL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBCTRL_POFFSET)
#define BPORT1_AB_USBCTRL_PDE           (0x1 << 6)
#define BPORT1_AB_USBCTRL_PDE_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_USBCTRL_SUSP          (0x1 << 7)
#define BPORT1_AB_USBCTRL_SUSP_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_OBSERVE_POFFSET       0x104
#define BPORT1_AB_OBSERVE               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OBSERVE_POFFSET)
#define BPORT1_AB_OBSERVE_DMPD          (0x1 << 4)
#define BPORT1_AB_OBSERVE_DMPD_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_OBSERVE_DPPD          (0x1 << 6)
#define BPORT1_AB_OBSERVE_DPPD_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_OBSERVE_DPPU          (0x1 << 7)
#define BPORT1_AB_OBSERVE_DPPU_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_CONTROL_POFFSET       0x108
#define BPORT1_AB_CONTROL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL_POFFSET)
#define BPORT1_AB_CONTROL_DPPULLUPNONOTG  (0x1 << 4)
#define BPORT1_AB_CONTROL_DPPULLUPNONOTG_GET(_v)  ((_v >> 4) & 0x1)

#define BPORT1_AB_USBTRC0_POFFSET       0x10c
#define BPORT1_AB_USBTRC0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBTRC0_POFFSET)
#define BPORT1_AB_USBTRC0_SYNC_DET      (0x1 << 1)
#define BPORT1_AB_USBTRC0_SYNC_DET_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_USBTRC0_USB_RESUME_INT  0x1
#define BPORT1_AB_USBTRC0_USB_RESUME_INT_GET(_v)  (_v & 0x1)
#define BPORT1_AB_USBTRC0_USBRESET      (0x1 << 7)
#define BPORT1_AB_USBTRC0_USBRESET_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_USBTRC0_USBRESMEN     (0x1 << 5)
#define BPORT1_AB_USBTRC0_USBRESMEN_GET(_v)  ((_v >> 5) & 0x1)

#define BPORT1_AB_USBFRMADJUST_POFFSET  0x114
#define BPORT1_AB_USBFRMADJUST          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBFRMADJUST_POFFSET)
#define BPORT1_AB_USBFRMADJUST_ADJ      0xff
#define BPORT1_AB_USBFRMADJUST_ADJ_GET(_v)  (_v & 0xff)


#endif
