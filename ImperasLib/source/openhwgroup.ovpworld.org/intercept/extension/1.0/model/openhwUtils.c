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


// Imperas header files
#include "hostapi/impTypes.h"

// VMI header files
#include "vmi/vmiTypes.h"
#include "vmi/vmiMessage.h"

// model header files
#include "openhwConfig.h"
#include "openhwMessage.h"
#include "openhwUtils.h"

// base model header files
#include "riscvStructure.h"


//
// Return OpenHW Ovpworld extension configuration for RISC-V processor
//
openhwConfigCP openhwExtConfig(riscvP riscv) {
    riscvExtConfigCP cfg = riscv->cb.getExtConfig(riscv, OPENHW_OVP_CONFIG_ID);
    VMI_ASSERT(cfg, "No Config with id 0x%x found", OPENHW_OVP_CONFIG_ID);
    return cfg->userData;
}
