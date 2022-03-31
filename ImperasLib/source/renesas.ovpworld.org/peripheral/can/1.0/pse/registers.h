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

#ifndef _REGISTERS_H_
#define _REGISTERS_H_

//
// GMCTRL Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16      GOM : 1;
        Uns16     EFSD : 1;
        Uns16    _pad0 : 2;
        Uns16       SR : 1;
        Uns16     MBRE : 1;
        Uns16    _pad1 : 2;
        Uns16    _pad2 : 7;
        Uns16     MBON : 1;
    } rd;
    struct {
        Uns16   ClrGOM : 1;
        Uns16    _pad0 : 4;
        Uns16  ClrMBRE : 1;
        Uns16    _pad1 : 2;
        Uns16   SetGOM : 1;
        Uns16    _pad2 : 2;
        Uns16    SetSR : 1;
        Uns16  SetEFSD : 1;
        Uns16    _pad3 : 3;
    } wr;
} GMCTRL;
#define GMCTRL_RESET   0x0010
#define GMCTRL_RD_MASK 0x8033
#define GMCTRL_WR_MASK 0x1321

//
// GMCS Register Definition
//
typedef union {
    Uns8 reg;
    Uns8 rd;
    Uns8 wr;
} GMCS;
#define GMCS_RESET   0x0F
#define GMCS_RD_MASK 0x0F
#define GMCS_WR_MASK 0x0F

//
// GMABT Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16      ABTTRG : 1;
        Uns16      ABTCLR : 1;
    } rd;
    struct {
        Uns16   ClrABTTRG : 1;
        Uns16       _pad0 : 7;
        Uns16   SetABTTRG : 1;
        Uns16   SetABTCLR : 1;
    } wr;
} GMABT;
#define GMABT_RESET   0x0000
#define GMABT_RD_MASK 0x0003
#define GMABT_WR_MASK 0x0301

typedef union {
    Uns16 reg;
    Uns16 rd;
    Uns16 wr;
} GMCONF;
#define GMCONF_RESET   0x0011
#define GMCONF_RD_MASK 0x001F

//
// GMABTD Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8      ABTD0 : 1;
        Uns8      ABTD1 : 1;
        Uns8      ABTD2 : 1;
        Uns8      ABTD3 : 1;
    } rd;
    struct {
        Uns8      ABTD0 : 1;
        Uns8      ABTD1 : 1;
        Uns8      ABTD2 : 1;
        Uns8      ABTD3 : 1;
    } wr;
} GMABTD;
#define GMABTD_RESET   0x00
#define GMABTD_RD_MASK 0x0F
#define GMABTD_WR_MASK 0x0F

//
// MASK Register Definition
//
typedef union {
    Uns32 reg;
    struct {
        Uns32        L : 16;
        Uns32        H : 13;
        Uns32    _pad0 :  3;
    } r16;
    struct {
        Uns32     CMID : 29;
    } bits;
} MASK;
#define MASK_RESET    0x00000000
#define MASK_RD_MASK  0x1FFFFFFF
#define MASK_WR_MASK  0x1FFFFFFF
#define MASKL_RD_MASK 0xFFFF
#define MASKL_WR_MASK 0xFFFF
#define MASKH_RD_MASK 0x1FFF
#define MASKH_WR_MASK 0x1FFF


//
// CTRL Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16    OPMODE0 : 1;
        Uns16    OPMODE1 : 1;
        Uns16    OPMODE2 : 1;
        Uns16    PSMODE0 : 1;   // 00 normal mode
        Uns16    PSMODE1 : 1;   // 01 sleep mode, 10 stop mode
        Uns16      VALID : 1;
        Uns16         AL : 1;
        Uns16      CCERC : 1;
        Uns16      TSTAT : 1;
        Uns16      RSTAT : 1;
    } rd;
    struct {
        Uns16 ClrOPMODE0 : 1;
        Uns16 ClrOPMODE1 : 1;
        Uns16 ClrOPMODE2 : 1;
        Uns16 ClrPSMODE0 : 1;
        Uns16 ClrPSMODE1 : 1;
        Uns16   ClrVALID : 1;
        Uns16      ClrAL : 1;
        Uns16      _pad0 : 1;
        Uns16 SetOPMODE0 : 1;
        Uns16 SetOPMODE1 : 1;
        Uns16 SetOPMODE2 : 1;
        Uns16 SetPSMODE0 : 1;
        Uns16 SetPSMODE1 : 1;
        Uns16      _pad1 : 1;
        Uns16      SetAL : 1;
        Uns16   SetCCERC : 1;
    } wr;
} CTRL;
#define CTRL_RESET   0x0000
#define CTRL_RD_MASK 0x003F
#define CTRL_WR_MASK 0xDF7F

//
// LEC Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8      LEC0 : 1;
        Uns8      LEC1 : 1;
        Uns8      LEC2 : 1;
    } bits;
} LEC;
#define LEC_RESET   0x00
#define LEC_RD_MASK 0x07
#define LEC_WR_MASK 0x07

//
// INFO Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8     RECS0 : 1;
        Uns8     RECS1 : 1;
        Uns8     TECS0 : 1;
        Uns8     TECS1 : 1;
        Uns8      BOFF : 1;
    } bits;
} INFO;
#define INFO_RESET   0x00
#define INFO_RD_MASK 0x1F
#define INFO_WR_MASK 0x1F

//
// ERC Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16     TEC : 8;
        Uns16     REC : 7;
        Uns16    REPS : 1;
    } bits;
} ERC;
#define ERC_RESET    0x0000
#define ERC_RD_MASK  0xFFFF
#define ERC_WR_MASK  0xFFFF

//
// IE Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16    CIE0 : 1;
        Uns16    CIE1 : 1;
        Uns16    CIE2 : 1;
        Uns16    CIE3 : 1;
        Uns16    CIE4 : 1;
        Uns16    CIE5 : 1;
    } rd;
    struct {
        Uns16 ClrCIE0 : 1;
        Uns16 ClrCIE1 : 1;
        Uns16 ClrCIE2 : 1;
        Uns16 ClrCIE3 : 1;
        Uns16 ClrCIE4 : 1;
        Uns16 ClrCIE5 : 1;
        Uns16   _pad1 : 2;
        Uns16 SetCIE0 : 1;
        Uns16 SetCIE1 : 1;
        Uns16 SetCIE2 : 1;
        Uns16 SetCIE3 : 1;
        Uns16 SetCIE4 : 1;
        Uns16 SetCIE5 : 1;
        Uns16   _pad0 : 2;
    } wr;
} IE;
#define IE_RESET    0x0000
#define IE_RD_MASK  0x003F
#define IE_WR_MASK  0x3F3F

//
// INTS Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16    CINTS0 : 1;    // Normal Transmission end Interrupt
        Uns16    CINTS1 : 1;    // Interrupt indicating valid message receive
        Uns16    CINTS2 : 1;    // CAN module error status interrupt
        Uns16    CINTS3 : 1;    // CAN module protocol error interrupt
        Uns16    CINTS4 : 1;    // CAN module arbitration loss interrupt
        Uns16    CINTS5 : 1;    // Interrupt to wake up can module from sleep
    } rd;
    struct {
        Uns16 ClrCINTS0 : 1;
        Uns16 ClrCINTS1 : 1;
        Uns16 ClrCINTS2 : 1;
        Uns16 ClrCINTS3 : 1;
        Uns16 ClrCINTS4 : 1;
        Uns16 ClrCINTS5 : 1;
    } wr;
} INTS;
#define INTS_RESET    0x0000
#define INTS_RD_MASK  0x003F
#define INTS_WR_MASK  0x003F

//
// BRP Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8     TQPRS : 8;
    } bits;
} BRP;
#define BRP_RESET   0xFF
#define BRP_RD_MASK 0xFF
#define BRP_WR_MASK 0xFF

//
// BTR Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16    TSEG10 : 1;
        Uns16    TSEG11 : 1;
        Uns16    TSEG12 : 1;
        Uns16    TSEG13 : 1;
        Uns16     _pad0 : 4;
        Uns16    TSEG20 : 1;
        Uns16    TSEG21 : 1;
        Uns16    TSEG22 : 1;
        Uns16     _pad1 : 1;
        Uns16      SJW0 : 1;
        Uns16      SJW1 : 1;
    } bits;
} BTR;
#define BTR_RESET    0x370F
#define BTR_RD_MASK  0x370F
#define BTR_WR_MASK  0x370F

//
// LIPT Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8     LIPT : 8;
    } bits;
} LIPT;
#define LIPT_RESET   0x00
#define LIPT_RD_MASK 0xFF
#define LIPT_WR_MASK 0xFF

//
// RGPT Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16    ROVF : 1;
        Uns16    RHPM : 1;
        Uns16   _pad0 : 6;
        Uns16    RGPT : 8;
    } rd;
    struct {
        Uns16 ClrROVF : 1;
    } wr;
} RGPT;
#define RGPT_RESET    0x0002
#define RGPT_RD_MASK  0xFF03
#define RGPT_WR_MASK  0x0001

//
// LOPT Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8     LOPT : 8;
    } bits;
} LOPT;
#define LOPT_RESET   0x00
#define LOPT_RD_MASK 0xFF

//
// TGTP Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16    TOVF : 1;
        Uns16    THPM : 1;
        Uns16   _pad0 : 6;
        Uns16    TGPT : 8;
    } rd;
    struct {
        Uns16 ClrTOVF : 1;
    } wr;
} TGPT;
#define TGPT_RESET    0x0002
#define TGPT_RD_MASK  0xFF03
#define TGPT_WR_MASK  0x0001

//
// TS Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16       TSEN : 1;
        Uns16      TSSEL : 1;
        Uns16     TSLOCK : 1;
    } rd;
    struct {
        Uns16    ClrTSEN : 1;
        Uns16   ClrTSSEL : 1;
        Uns16  ClrTSLOCK : 1;
        Uns16      _pad0 : 5;
        Uns16    SetTSEN : 1;
        Uns16   SetTSSEL : 1;
        Uns16  SetTSLOCK : 1;
    } wr;
} TS;
#define TS_RESET    0x0000
#define TS_RD_MASK  0x0007
#define TS_WR_MASK  0x0707

#define CAN_MSG_DATA_BYTES 256
typedef union {
    Uns8  b[CAN_MSG_DATA_BYTES];
    Uns16 s[CAN_MSG_DATA_BYTES/2];
    Uns32 w[CAN_MSG_DATA_BYTES/4];
} MDATA;

//
// MDLC Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8     MDLC : 4;
    } bits;
} MDLC;
#define MDLC_RESET   0x00
#define MDLC_RD_MASK 0x0F
#define MDLC_WR_MASK 0x0F

//
// MCONF Register Definition
//
typedef union {
    Uns8 reg;
    struct {
        Uns8     MA0 : 1;
        Uns8   _pad0 : 2;
        Uns8      MT : 3;
        Uns8     RTR : 1;
        Uns8     OWS : 1;
    } bits;
} MCONF;
#define MCONF_RESET   0x00
#define MCONF_RD_MASK 0xF9
#define MCONF_WR_MASK 0xF9

//
// MID Register Definition
//
typedef union {
    Uns32 reg;
    struct {
        Uns32     ID : 29;
        Uns32  _pad0 : 2;
        Uns32    IDE : 1;
    } bits;
    struct {
        Uns32     ID : 16;
        Uns32  _pad0 : 16;
    } L;
    struct {
        Uns32  _pad0 : 16;
        Uns32     ID : 13;
        Uns32  _pad1 : 2;
        Uns32    IDE : 1;
    } H;
    struct {
        Uns32      L : 16;
        Uns32      H : 16;
    } HL;
} MID;
#define MID_RESET    0x00000000
#define MID_RD_MASK  0x9FFFFFFF
#define MID_WR_MASK  0x9FFFFFFF
#define MIDL_RD_MASK 0xFFFF
#define MIDL_WR_MASK 0xFFFF
#define MIDH_RD_MASK 0x9FFF
#define MIDH_WR_MASK 0x9FFF

//
// MCTRL Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16      RDY : 1;
        Uns16      TRQ : 1;
        Uns16       DN : 1;
        Uns16       IE : 1;
        Uns16      MOW : 1;
        Uns16    _pad0 : 3;
        Uns16    _pad1 : 5;
        Uns16      MUC : 1;
        Uns16    _pad2 : 2;
    } rd;
    struct {
        Uns16   ClrRDY : 1;
        Uns16   ClrTRQ : 1;
        Uns16    ClrDN : 1;
        Uns16    ClrIE : 1;
        Uns16   ClrMOW : 1;
        Uns16    _pad0 : 3;
        Uns16   SetRDY : 1;
        Uns16   SetTRQ : 1;
        Uns16    _pad1 : 1;
        Uns16    SetIE : 1;
        Uns16    _pad2 : 4;
    } wr;
} MCTRL;
#define MCTRL_RESET   0x0000
#define MCTRL_RD_MASK 0x201f
#define MCTRL_WR_MASK 0x0b1f

//
// E6A0CTL Register Definition
//
typedef union {
    Uns16 reg;
    struct {
        Uns16      _pad0 : 1;
        Uns16    ECCECA0 : 1;
        Uns16    ECCER20 : 1;
        Uns16      _pad1 : 6;
        Uns16      ECAC0 : 1;
        Uns16      ER2C0 : 1;
    } bits;
} E6A0CTL;
#define E6A0CTL_RESET   0x0000
#define E6A0CTL_RD_MASK 0x0606
#define E6A0CTL_WR_MASK 0x0606

//
// Set or Clr a bit
// SC=00 nochange
// SC=01 0
// SC=10 1
// SC=11 nochange
//
#define SCBIT(_VAL,_SET,_CLR) _VAL = (_SET ^ _CLR) ? _SET : _VAL

//
// Clear only
//
#define CBIT(_VAL,_CLR) _VAL = _CLR ? 0 : _VAL

//
// Set only
//
#define SBIT(_VAL,_SET) _VAL = _SET ? 1 : _VAL

//
// Bitmask write check
//
#define CHECKMASK(_VAL,_MASK,_REG) { \
    if (_VAL & ~(_MASK)) { \
        bhmMessage("W", "WRITE_ERR", "Illegal Bit Write %s=0x%x\n", _REG, _VAL); \
    } \
}

//
// Number of message buffers
//
#define CAN_MSG_BUFFERS 32

#endif  // _REGISTERS_H_
