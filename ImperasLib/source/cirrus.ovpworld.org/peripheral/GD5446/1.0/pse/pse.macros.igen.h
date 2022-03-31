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

// Set the macro 'CONFIG' to the base of port 'config'
#ifndef CONFIG
#error CONFIG is undefined. It needs to be set to the port base address
#endif


#define CONFIG_AB_POFFSET               0x0
#define CONFIG_AB_CR_INDEX_POFFSET      0x4
#define CONFIG_AB_CR_INDEX              (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_CR_INDEX_POFFSET)

#define CONFIG_AB_CR_POFFSET            0x5
#define CONFIG_AB_CR                    (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_CR_POFFSET)

#define CONFIG_AB_GR_INDEX_POFFSET      0x1e
#define CONFIG_AB_GR_INDEX              (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_GR_INDEX_POFFSET)

#define CONFIG_AB_AR_INDEX_POFFSET      0x10
#define CONFIG_AB_AR_INDEX              (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_AR_INDEX_POFFSET)

#define CONFIG_AB_AR_POFFSET            0x11
#define CONFIG_AB_AR                    (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_AR_POFFSET)

#define CONFIG_AB_MSRWRITE_POFFSET      0x12
#define CONFIG_AB_MSRWRITE              (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_MSRWRITE_POFFSET)

#define CONFIG_AB_ST00_POFFSET          0x12
#define CONFIG_AB_ST00                  (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_ST00_POFFSET)

#define CONFIG_AB_GR_POFFSET            0x1f
#define CONFIG_AB_GR                    (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_GR_POFFSET)

#define CONFIG_AB_SR_INDEX_POFFSET      0x14
#define CONFIG_AB_SR_INDEX              (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_SR_INDEX_POFFSET)

#define CONFIG_AB_SR_POFFSET            0x15
#define CONFIG_AB_SR                    (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_SR_POFFSET)

#define CONFIG_AB_FCRWRITE_POFFSET      0xa
#define CONFIG_AB_FCRWRITE              (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_FCRWRITE_POFFSET)

#define CONFIG_AB_ST01_POFFSET          0xa
#define CONFIG_AB_ST01                  (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_ST01_POFFSET)

#define CONFIG_AB_DAC_READ_INDEX_POFFSET  0x17
#define CONFIG_AB_DAC_READ_INDEX        (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_DAC_READ_INDEX_POFFSET)

#define CONFIG_AB_DAC_WRITE_INDEX_POFFSET  0x18
#define CONFIG_AB_DAC_WRITE_INDEX       (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_DAC_WRITE_INDEX_POFFSET)

#define CONFIG_AB_DAC_CACHE_POFFSET     0x19
#define CONFIG_AB_DAC_CACHE             (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_DAC_CACHE_POFFSET)

#define CONFIG_AB_FCRREAD_POFFSET       0x1a
#define CONFIG_AB_FCRREAD               (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_FCRREAD_POFFSET)

#define CONFIG_AB_MSRREAD_POFFSET       0x1c
#define CONFIG_AB_MSRREAD               (CONFIG + CONFIG_AB_POFFSET + CONFIG_AB_MSRREAD_POFFSET)


#endif
