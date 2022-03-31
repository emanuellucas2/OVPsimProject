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

// Set the macro 'APB' to the base of port 'apb'
#ifndef APB
#error APB is undefined. It needs to be set to the port base address
#endif


#define APB_REG_POFFSET                 0x0
#define APB_REG_US_CR_POFFSET           0x0
#define APB_REG_US_CR                   (APB + APB_REG_POFFSET + APB_REG_US_CR_POFFSET)
#define APB_REG_US_CR_SENDA             (0x1 << 12)
#define APB_REG_US_CR_SENDA_GET(_v)     ((_v >> 12) & 0x1)
#define APB_REG_US_CR_STTTO             (0x1 << 11)
#define APB_REG_US_CR_STTTO_GET(_v)     ((_v >> 11) & 0x1)
#define APB_REG_US_CR_STPBRK            (0x1 << 10)
#define APB_REG_US_CR_STPBRK_GET(_v)    ((_v >> 10) & 0x1)
#define APB_REG_US_CR_STTBRK            (0x1 << 9)
#define APB_REG_US_CR_STTBRK_GET(_v)    ((_v >> 9) & 0x1)
#define APB_REG_US_CR_RSTSTA            (0x1 << 8)
#define APB_REG_US_CR_RSTSTA_GET(_v)    ((_v >> 8) & 0x1)
#define APB_REG_US_CR_TXDIS             (0x1 << 7)
#define APB_REG_US_CR_TXDIS_GET(_v)     ((_v >> 7) & 0x1)
#define APB_REG_US_CR_TXEN              (0x1 << 6)
#define APB_REG_US_CR_TXEN_GET(_v)      ((_v >> 6) & 0x1)
#define APB_REG_US_CR_RXDIS             (0x1 << 5)
#define APB_REG_US_CR_RXDIS_GET(_v)     ((_v >> 5) & 0x1)
#define APB_REG_US_CR_RXEN              (0x1 << 4)
#define APB_REG_US_CR_RXEN_GET(_v)      ((_v >> 4) & 0x1)
#define APB_REG_US_CR_RSTTX             (0x1 << 3)
#define APB_REG_US_CR_RSTTX_GET(_v)     ((_v >> 3) & 0x1)
#define APB_REG_US_CR_RSTRX             (0x1 << 2)
#define APB_REG_US_CR_RSTRX_GET(_v)     ((_v >> 2) & 0x1)

#define APB_REG_US_MR_POFFSET           0x4
#define APB_REG_US_MR                   (APB + APB_REG_POFFSET + APB_REG_US_MR_POFFSET)
#define APB_REG_US_MR_CLKO              (0x1 << 18)
#define APB_REG_US_MR_CLKO_GET(_v)      ((_v >> 18) & 0x1)
#define APB_REG_US_MR_MODE9             (0x1 << 17)
#define APB_REG_US_MR_MODE9_GET(_v)     ((_v >> 17) & 0x1)
#define APB_REG_US_MR_CHMODE            (0x3 << 14)
#define APB_REG_US_MR_CHMODE_GET(_v)    ((_v >> 14) & 0x3)
#define APB_REG_US_MR_NBSTOP            (0x3 << 12)
#define APB_REG_US_MR_NBSTOP_GET(_v)    ((_v >> 12) & 0x3)
#define APB_REG_US_MR_PAR               (0x7 << 9)
#define APB_REG_US_MR_PAR_GET(_v)       ((_v >> 9) & 0x7)
#define APB_REG_US_MR_SYNC              (0x1 << 8)
#define APB_REG_US_MR_SYNC_GET(_v)      ((_v >> 8) & 0x1)
#define APB_REG_US_MR_CHRL              (0x3 << 6)
#define APB_REG_US_MR_CHRL_GET(_v)      ((_v >> 6) & 0x3)
#define APB_REG_US_MR_HSCLKS            (0x3 << 4)
#define APB_REG_US_MR_HSCLKS_GET(_v)    ((_v >> 4) & 0x3)

#define APB_REG_US_IER_POFFSET          0x8
#define APB_REG_US_IER                  (APB + APB_REG_POFFSET + APB_REG_US_IER_POFFSET)
#define APB_REG_US_IER_TXEMPTY          (0x1 << 9)
#define APB_REG_US_IER_TXEMPTY_GET(_v)  ((_v >> 9) & 0x1)
#define APB_REG_US_IER_TIMEOUT          (0x1 << 8)
#define APB_REG_US_IER_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define APB_REG_US_IER_PARE             (0x1 << 7)
#define APB_REG_US_IER_PARE_GET(_v)     ((_v >> 7) & 0x1)
#define APB_REG_US_IER_FRAME            (0x1 << 6)
#define APB_REG_US_IER_FRAME_GET(_v)    ((_v >> 6) & 0x1)
#define APB_REG_US_IER_OVRE             (0x1 << 5)
#define APB_REG_US_IER_OVRE_GET(_v)     ((_v >> 5) & 0x1)
#define APB_REG_US_IER_ENDTX            (0x1 << 4)
#define APB_REG_US_IER_ENDTX_GET(_v)    ((_v >> 4) & 0x1)
#define APB_REG_US_IER_ENDRX            (0x1 << 3)
#define APB_REG_US_IER_ENDRX_GET(_v)    ((_v >> 3) & 0x1)
#define APB_REG_US_IER_RXBRK            (0x1 << 2)
#define APB_REG_US_IER_RXBRK_GET(_v)    ((_v >> 2) & 0x1)
#define APB_REG_US_IER_TXRDY            (0x1 << 1)
#define APB_REG_US_IER_TXRDY_GET(_v)    ((_v >> 1) & 0x1)
#define APB_REG_US_IER_RXRDY            0x1
#define APB_REG_US_IER_RXRDY_GET(_v)    (_v & 0x1)

#define APB_REG_US_IDR_POFFSET          0xc
#define APB_REG_US_IDR                  (APB + APB_REG_POFFSET + APB_REG_US_IDR_POFFSET)
#define APB_REG_US_IDR_TXEMPTY          (0x1 << 9)
#define APB_REG_US_IDR_TXEMPTY_GET(_v)  ((_v >> 9) & 0x1)
#define APB_REG_US_IDR_TIMEOUT          (0x1 << 8)
#define APB_REG_US_IDR_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define APB_REG_US_IDR_PARE             (0x1 << 7)
#define APB_REG_US_IDR_PARE_GET(_v)     ((_v >> 7) & 0x1)
#define APB_REG_US_IDR_FRAME            (0x1 << 6)
#define APB_REG_US_IDR_FRAME_GET(_v)    ((_v >> 6) & 0x1)
#define APB_REG_US_IDR_OVRE             (0x1 << 5)
#define APB_REG_US_IDR_OVRE_GET(_v)     ((_v >> 5) & 0x1)
#define APB_REG_US_IDR_ENDTX            (0x1 << 4)
#define APB_REG_US_IDR_ENDTX_GET(_v)    ((_v >> 4) & 0x1)
#define APB_REG_US_IDR_ENDRX            (0x1 << 3)
#define APB_REG_US_IDR_ENDRX_GET(_v)    ((_v >> 3) & 0x1)
#define APB_REG_US_IDR_RXBRK            (0x1 << 2)
#define APB_REG_US_IDR_RXBRK_GET(_v)    ((_v >> 2) & 0x1)
#define APB_REG_US_IDR_TXRDY            (0x1 << 1)
#define APB_REG_US_IDR_TXRDY_GET(_v)    ((_v >> 1) & 0x1)
#define APB_REG_US_IDR_RXRDY            0x1
#define APB_REG_US_IDR_RXRDY_GET(_v)    (_v & 0x1)

#define APB_REG_US_IMR_POFFSET          0x10
#define APB_REG_US_IMR                  (APB + APB_REG_POFFSET + APB_REG_US_IMR_POFFSET)
#define APB_REG_US_IMR_TXEMPTY          (0x1 << 9)
#define APB_REG_US_IMR_TXEMPTY_GET(_v)  ((_v >> 9) & 0x1)
#define APB_REG_US_IMR_TIMEOUT          (0x1 << 8)
#define APB_REG_US_IMR_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define APB_REG_US_IMR_PARE             (0x1 << 7)
#define APB_REG_US_IMR_PARE_GET(_v)     ((_v >> 7) & 0x1)
#define APB_REG_US_IMR_FRAME            (0x1 << 6)
#define APB_REG_US_IMR_FRAME_GET(_v)    ((_v >> 6) & 0x1)
#define APB_REG_US_IMR_OVRE             (0x1 << 5)
#define APB_REG_US_IMR_OVRE_GET(_v)     ((_v >> 5) & 0x1)
#define APB_REG_US_IMR_ENDTX            (0x1 << 4)
#define APB_REG_US_IMR_ENDTX_GET(_v)    ((_v >> 4) & 0x1)
#define APB_REG_US_IMR_ENDRX            (0x1 << 3)
#define APB_REG_US_IMR_ENDRX_GET(_v)    ((_v >> 3) & 0x1)
#define APB_REG_US_IMR_RXBRK            (0x1 << 2)
#define APB_REG_US_IMR_RXBRK_GET(_v)    ((_v >> 2) & 0x1)
#define APB_REG_US_IMR_TXRDY            (0x1 << 1)
#define APB_REG_US_IMR_TXRDY_GET(_v)    ((_v >> 1) & 0x1)
#define APB_REG_US_IMR_RXRDY            0x1
#define APB_REG_US_IMR_RXRDY_GET(_v)    (_v & 0x1)

#define APB_REG_US_CSR_POFFSET          0x14
#define APB_REG_US_CSR                  (APB + APB_REG_POFFSET + APB_REG_US_CSR_POFFSET)
#define APB_REG_US_CSR_TXEMPTY          (0x1 << 9)
#define APB_REG_US_CSR_TXEMPTY_GET(_v)  ((_v >> 9) & 0x1)
#define APB_REG_US_CSR_TIMEOUT          (0x1 << 8)
#define APB_REG_US_CSR_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define APB_REG_US_CSR_PARE             (0x1 << 7)
#define APB_REG_US_CSR_PARE_GET(_v)     ((_v >> 7) & 0x1)
#define APB_REG_US_CSR_FRAME            (0x1 << 6)
#define APB_REG_US_CSR_FRAME_GET(_v)    ((_v >> 6) & 0x1)
#define APB_REG_US_CSR_OVRE             (0x1 << 5)
#define APB_REG_US_CSR_OVRE_GET(_v)     ((_v >> 5) & 0x1)
#define APB_REG_US_CSR_ENDTX            (0x1 << 4)
#define APB_REG_US_CSR_ENDTX_GET(_v)    ((_v >> 4) & 0x1)
#define APB_REG_US_CSR_ENDRX            (0x1 << 3)
#define APB_REG_US_CSR_ENDRX_GET(_v)    ((_v >> 3) & 0x1)
#define APB_REG_US_CSR_RXBRK            (0x1 << 2)
#define APB_REG_US_CSR_RXBRK_GET(_v)    ((_v >> 2) & 0x1)
#define APB_REG_US_CSR_TXRDY            (0x1 << 1)
#define APB_REG_US_CSR_TXRDY_GET(_v)    ((_v >> 1) & 0x1)
#define APB_REG_US_CSR_RXRDY            0x1
#define APB_REG_US_CSR_RXRDY_GET(_v)    (_v & 0x1)

#define APB_REG_US_RHR_POFFSET          0x18
#define APB_REG_US_RHR                  (APB + APB_REG_POFFSET + APB_REG_US_RHR_POFFSET)
#define APB_REG_US_RHR_RXCHR            0xff
#define APB_REG_US_RHR_RXCHR_GET(_v)    (_v & 0xff)

#define APB_REG_US_THR_POFFSET          0x1c
#define APB_REG_US_THR                  (APB + APB_REG_POFFSET + APB_REG_US_THR_POFFSET)
#define APB_REG_US_THR_TXCHR            0xff
#define APB_REG_US_THR_TXCHR_GET(_v)    (_v & 0xff)

#define APB_REG_US_BRGR_POFFSET         0x20
#define APB_REG_US_BRGR                 (APB + APB_REG_POFFSET + APB_REG_US_BRGR_POFFSET)
#define APB_REG_US_BRGR_CD              0xffff
#define APB_REG_US_BRGR_CD_GET(_v)      (_v & 0xffff)

#define APB_REG_US_RTOR_POFFSET         0x24
#define APB_REG_US_RTOR                 (APB + APB_REG_POFFSET + APB_REG_US_RTOR_POFFSET)
#define APB_REG_US_RTOR_TO              0xff
#define APB_REG_US_RTOR_TO_GET(_v)      (_v & 0xff)

#define APB_REG_US_TTGR_POFFSET         0x28
#define APB_REG_US_TTGR                 (APB + APB_REG_POFFSET + APB_REG_US_TTGR_POFFSET)
#define APB_REG_US_TTGR_TG              0xff
#define APB_REG_US_TTGR_TG_GET(_v)      (_v & 0xff)

#define APB_REG_US_RPR_POFFSET          0x30
#define APB_REG_US_RPR                  (APB + APB_REG_POFFSET + APB_REG_US_RPR_POFFSET)
#define APB_REG_US_RPR_RXPTR            0xffffffff
#define APB_REG_US_RPR_RXPTR_GET(_v)    (_v & 0xffffffff)

#define APB_REG_US_RCR_POFFSET          0x34
#define APB_REG_US_RCR                  (APB + APB_REG_POFFSET + APB_REG_US_RCR_POFFSET)
#define APB_REG_US_RCR_RXCTR            0xffff
#define APB_REG_US_RCR_RXCTR_GET(_v)    (_v & 0xffff)

#define APB_REG_US_TPR_POFFSET          0x38
#define APB_REG_US_TPR                  (APB + APB_REG_POFFSET + APB_REG_US_TPR_POFFSET)
#define APB_REG_US_TPR_TXPTR            0xffffffff
#define APB_REG_US_TPR_TXPTR_GET(_v)    (_v & 0xffffffff)

#define APB_REG_US_TCR_POFFSET          0x3c
#define APB_REG_US_TCR                  (APB + APB_REG_POFFSET + APB_REG_US_TCR_POFFSET)
#define APB_REG_US_TCR_TXCTR            0xffff
#define APB_REG_US_TCR_TXCTR_GET(_v)    (_v & 0xffff)


#endif
