/*
 * (Am79C970A)
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
 
 #ifndef NETCONSTANTS_H_
#define NETCONSTANTS_H_


#define PCNET_IOPORT_SIZE       0x20
#define PCNET_PNPMMIO_SIZE      0x20

/* BUS CONFIGURATION REGISTERS */
#define BCR_MSRDA    0
#define BCR_MSWRA    1
#define BCR_MC       2
#define BCR_LNKST    4
#define BCR_LED1     5
#define BCR_LED2     6
#define BCR_LED3     7
#define BCR_FDC      9
#define BCR_BSBC     18
#define BCR_EECAS    19
#define BCR_SWS      20
#define BCR_PLAT     22

#define BCR_DWIO(S)      !!((S)->bcr[BCR_BSBC] & 0x0080)
#define BCR_SSIZE32(S)   !!((S)->bcr[BCR_SWS ] & 0x0100)
#define BCR_SWSTYLE(S)     ((S)->bcr[BCR_SWS ] & 0x00FF)

#define CSR_INIT(S)      !!(((S)->csr[0])&0x0001)
#define CSR_STRT(S)      !!(((S)->csr[0])&0x0002)
#define CSR_STOP(S)      !!(((S)->csr[0])&0x0004)
#define CSR_TDMD(S)      !!(((S)->csr[0])&0x0008)
#define CSR_TXON(S)      !!(((S)->csr[0])&0x0010)
#define CSR_RXON(S)      !!(((S)->csr[0])&0x0020)
#define CSR_INEA(S)      !!(((S)->csr[0])&0x0040)
#define CSR_BSWP(S)      !!(((S)->csr[3])&0x0004)
#define CSR_LAPPEN(S)    !!(((S)->csr[3])&0x0020)
#define CSR_DXSUFLO(S)   !!(((S)->csr[3])&0x0040)
#define CSR_ASTRP_RCV(S) !!(((S)->csr[4])&0x0800)
#define CSR_DPOLL(S)     !!(((S)->csr[4])&0x1000)
#define CSR_SPND(S)      !!(((S)->csr[5])&0x0001)
#define CSR_LTINTEN(S)   !!(((S)->csr[5])&0x4000)
#define CSR_TOKINTD(S)   !!(((S)->csr[5])&0x8000)
#define CSR_DRX(S)       !!(((S)->csr[15])&0x0001)
#define CSR_DTX(S)       !!(((S)->csr[15])&0x0002)
#define CSR_LOOP(S)      !!(((S)->csr[15])&0x0004)
#define CSR_DRCVPA(S)    !!(((S)->csr[15])&0x2000)
#define CSR_DRCVBC(S)    !!(((S)->csr[15])&0x4000)
#define CSR_PROM(S)      !!(((S)->csr[15])&0x8000)

#define CSR_CRBC(S)      ((S)->csr[40])
#define CSR_CRST(S)      ((S)->csr[41])
#define CSR_CXBC(S)      ((S)->csr[42])
#define CSR_CXST(S)      ((S)->csr[43])
#define CSR_NRBC(S)      ((S)->csr[44])
#define CSR_NRST(S)      ((S)->csr[45])
#define CSR_POLL(S)      ((S)->csr[46])
#define CSR_PINT(S)      ((S)->csr[47])
#define CSR_RCVRC(S)     ((S)->csr[72])
#define CSR_XMTRC(S)     ((S)->csr[74])
#define CSR_RCVRL(S)     ((S)->csr[76])
#define CSR_XMTRL(S)     ((S)->csr[78])
#define CSR_MISSC(S)     ((S)->csr[112])

#define CSR_IADR(S)      ((S)->csr[ 1] | ((S)->csr[ 2] << 16))
#define CSR_CRBA(S)      ((S)->csr[18] | ((S)->csr[19] << 16))
#define CSR_CXBA(S)      ((S)->csr[20] | ((S)->csr[21] << 16))
#define CSR_NRBA(S)      ((S)->csr[22] | ((S)->csr[23] << 16))
#define CSR_BADR(S)      ((S)->csr[24] | ((S)->csr[25] << 16))
#define CSR_NRDA(S)      ((S)->csr[26] | ((S)->csr[27] << 16))
#define CSR_CRDA(S)      ((S)->csr[28] | ((S)->csr[29] << 16))
#define CSR_BADX(S)      ((S)->csr[30] | ((S)->csr[31] << 16))
#define CSR_NXDA(S)      ((S)->csr[32] | ((S)->csr[33] << 16))
#define CSR_CXDA(S)      ((S)->csr[34] | ((S)->csr[35] << 16))
#define CSR_NNRD(S)      ((S)->csr[36] | ((S)->csr[37] << 16))
#define CSR_NNXD(S)      ((S)->csr[38] | ((S)->csr[39] << 16))
#define CSR_PXDA(S)      ((S)->csr[60] | ((S)->csr[61] << 16))
#define CSR_NXBA(S)      ((S)->csr[64] | ((S)->csr[65] << 16))


#define TMDL_BCNT_MASK  0x0fff
#define TMDL_BCNT_SH    0
#define TMDL_ONES_MASK  0xf000
#define TMDL_ONES_SH    12

#define TMDS_BPE_MASK   0x0080
#define TMDS_BPE_SH     7
#define TMDS_ENP_MASK   0x0100
#define TMDS_ENP_SH     8
#define TMDS_STP_MASK   0x0200
#define TMDS_STP_SH     9
#define TMDS_DEF_MASK   0x0400
#define TMDS_DEF_SH     10
#define TMDS_ONE_MASK   0x0800
#define TMDS_ONE_SH     11
#define TMDS_LTINT_MASK 0x1000
#define TMDS_LTINT_SH   12
#define TMDS_NOFCS_MASK 0x2000
#define TMDS_NOFCS_SH   13
#define TMDS_ERR_MASK   0x4000
#define TMDS_ERR_SH     14
#define TMDS_OWN_MASK   0x8000
#define TMDS_OWN_SH     15

#define TMDM_TRC_MASK   0x0000000f
#define TMDM_TRC_SH     0
#define TMDM_TDR_MASK   0x03ff0000
#define TMDM_TDR_SH     16
#define TMDM_RTRY_MASK  0x04000000
#define TMDM_RTRY_SH    26
#define TMDM_LCAR_MASK  0x08000000
#define TMDM_LCAR_SH    27
#define TMDM_LCOL_MASK  0x10000000
#define TMDM_LCOL_SH    28
#define TMDM_EXDEF_MASK 0x20000000
#define TMDM_EXDEF_SH   29
#define TMDM_UFLO_MASK  0x40000000
#define TMDM_UFLO_SH    30
#define TMDM_BUFF_MASK  0x80000000
#define TMDM_BUFF_SH    31


#define RMDL_BCNT_MASK  0x0fff
#define RMDL_BCNT_SH    0
#define RMDL_ONES_MASK  0xf000
#define RMDL_ONES_SH    12

#define RMDS_BAM_MASK   0x0010
#define RMDS_BAM_SH     4
#define RMDS_LFAM_MASK  0x0020
#define RMDS_LFAM_SH    5
#define RMDS_PAM_MASK   0x0040
#define RMDS_PAM_SH     6
#define RMDS_BPE_MASK   0x0080
#define RMDS_BPE_SH     7
#define RMDS_ENP_MASK   0x0100
#define RMDS_ENP_SH     8
#define RMDS_STP_MASK   0x0200
#define RMDS_STP_SH     9
#define RMDS_BUFF_MASK  0x0400
#define RMDS_BUFF_SH    10
#define RMDS_CRC_MASK   0x0800
#define RMDS_CRC_SH     11
#define RMDS_OFLO_MASK  0x1000
#define RMDS_OFLO_SH    12
#define RMDS_FRAM_MASK  0x2000
#define RMDS_FRAM_SH    13
#define RMDS_ERR_MASK   0x4000
#define RMDS_ERR_SH     14
#define RMDS_OWN_MASK   0x8000
#define RMDS_OWN_SH     15

#define RMDM_MCNT_MASK  0x00000fff
#define RMDM_MCNT_SH    0
#define RMDM_ZEROS_MASK 0x0000f000
#define RMDM_ZEROS_SH   12
#define RMDM_RPC_MASK   0x00ff0000
#define RMDM_RPC_SH     16
#define RMDM_RCC_MASK   0xff000000
#define RMDM_RCC_SH     24

#define SET_FIELD(regp, name, field, value)             \
  (*(regp) = (*(regp) & ~(name ## _ ## field ## _MASK)) \
             | ((value) << name ## _ ## field ## _SH))

#define GET_FIELD(reg, name, field)                     \
  (((reg) & name ## _ ## field ## _MASK) >> name ## _ ## field ## _SH)

#endif /*NETCONSTANTS_H_*/
