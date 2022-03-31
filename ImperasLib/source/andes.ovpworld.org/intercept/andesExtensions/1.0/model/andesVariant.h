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

#pragma once

//
// This enumerates architecture features defined by mmsc_cfg, micm_cfg and
// mdcm_cfg registers
//
typedef enum andesVariantE {

    ANV_NA        = 0,
                              // -------------
                              // BASIC ENTRIES
                              // -------------
    ANV_ECD       = (1<< 0),  // mmsc_cfg.ECD
    ANV_HSP       = (1<< 1),  // mmsc_cfg.HSP
    ANV_EV5MPE    = (1<< 2),  // mmsc_cfg.EV5MPE
    ANV_PFT       = (1<< 3),  // mmsc_cfg.PFT
    ANV_CCTLCSR   = (1<< 4),  // mmsc_cfg.CCTLCSR
    ANV_MSC_EXT   = (1<< 5),  // micm_cfg.MSC_EXT
    ANV_EFHW      = (1<< 6),  // mmsc_cfg.EFHW
    ANV_ILMB      = (1<< 7),  // micm_cfg.ILMB
    ANV_DLMB      = (1<< 8),  // mdcm_cfg.DLMB
    ANV_SZ        = (1<< 9),  // micm_cfg.ISZ || mdcm_cfg.DSZ
    ANV_DPMA      = (1<<10),  // mmsc_cfg.DPMA
    ANV_PMNDS     = (1<<11),  // mmsc_cfg.PMNDS
    ANV_BF16CVT   = (1<<12),  // mmsc_cfg.BF16CVT
    ANV_ZFH       = (1<<13),  // mmsc_cfg.ZFH
    ANV_VL4       = (1<<14),  // mmsc_cfg.VL4
    ANV_VPFH      = (1<<15),  // mmsc_cfg.VPFH
    ANV_VECCFG    = (1<<16),  // mmsc_cfg.VECCFG
    ANV_L2CMP_CFG = (1<<17),  // mmsc_cfg.L2CMP_CFG
    ANV_L2C       = (1<<18),  // mmsc_cfg.L2C

                              // ----------------
                              // COMPOUND ENTRIES
                              // ----------------

    ANV_CCTLCSR_SZ = (ANV_CCTLCSR|ANV_SZ),
    ANV_L2C_BASE   = (ANV_L2CMP_CFG|ANV_L2C)

} andesVariant;

