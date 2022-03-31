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

// Set the macro 'PLB' to the base of port 'plb'
#ifndef PLB
#error PLB is undefined. It needs to be set to the port base address
#endif


#define PLB_REG_POFFSET                 0x0
#define PLB_REG_RXFIFO_POFFSET          0x0
#define PLB_REG_RXFIFO                  (PLB + PLB_REG_POFFSET + PLB_REG_RXFIFO_POFFSET)

#define PLB_REG_TXFIFO_POFFSET          0x4
#define PLB_REG_TXFIFO                  (PLB + PLB_REG_POFFSET + PLB_REG_TXFIFO_POFFSET)

#define PLB_REG_STAT_POFFSET            0x8
#define PLB_REG_STAT                    (PLB + PLB_REG_POFFSET + PLB_REG_STAT_POFFSET)
#define PLB_REG_STAT_RXFIFOVALIDDATA    0x1
#define PLB_REG_STAT_RXFIFOVALIDDATA_GET(_v)  (_v & 0x1)
#define PLB_REG_STAT_RXFIFOFULL         (0x1 << 1)
#define PLB_REG_STAT_RXFIFOFULL_GET(_v)  ((_v >> 1) & 0x1)
#define PLB_REG_STAT_TXFIFOEMPTY        (0x1 << 2)
#define PLB_REG_STAT_TXFIFOEMPTY_GET(_v)  ((_v >> 2) & 0x1)
#define PLB_REG_STAT_TXFIFOFULL         (0x1 << 3)
#define PLB_REG_STAT_TXFIFOFULL_GET(_v)  ((_v >> 3) & 0x1)
#define PLB_REG_STAT_INTRENABLED        (0x1 << 4)
#define PLB_REG_STAT_INTRENABLED_GET(_v)  ((_v >> 4) & 0x1)
#define PLB_REG_STAT_OVERRUNERROR       (0x1 << 5)
#define PLB_REG_STAT_OVERRUNERROR_GET(_v)  ((_v >> 5) & 0x1)
#define PLB_REG_STAT_FRAMEERROR         (0x1 << 6)
#define PLB_REG_STAT_FRAMEERROR_GET(_v)  ((_v >> 6) & 0x1)
#define PLB_REG_STAT_PARITYERROR        (0x1 << 7)
#define PLB_REG_STAT_PARITYERROR_GET(_v)  ((_v >> 7) & 0x1)

#define PLB_REG_CTRL_POFFSET            0xc
#define PLB_REG_CTRL                    (PLB + PLB_REG_POFFSET + PLB_REG_CTRL_POFFSET)
#define PLB_REG_CTRL_RSTTXFIFO          0x1
#define PLB_REG_CTRL_RSTTXFIFO_GET(_v)  (_v & 0x1)
#define PLB_REG_CTRL_RSTRXFIFO          (0x1 << 1)
#define PLB_REG_CTRL_RSTRXFIFO_GET(_v)  ((_v >> 1) & 0x1)
#define PLB_REG_CTRL_ENABLEINTR         (0x1 << 4)
#define PLB_REG_CTRL_ENABLEINTR_GET(_v)  ((_v >> 4) & 0x1)


#endif
