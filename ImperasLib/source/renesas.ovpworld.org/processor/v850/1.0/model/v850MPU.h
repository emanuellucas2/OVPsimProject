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

#ifndef V850_MPU_H
#define V850_MPU_H

#include "v850Structure.h"

Bool v850HasMPU(v850P v850);
Bool v850MPUMiss(v850P v850, memPriv action, Uns32 VA, memAccessAttrs attrs);
void v850WriteMPU_MCC(v850P v850, Uns32 value);
void v850WriteMPU_MPM(v850P v850, Uns32 value);
void v850WriteMPU_MPLA(v850P v850, Uns32 value, Uns32 idx);
void v850WriteMPU_MPUA(v850P v850, Uns32 value, Uns32 idx);
void v850WriteMPU_MPAT(v850P v850, Uns32 value, Uns32 idx);
void v850WriteMPU_MPRC(v850P v850, Uns32 value);
void v850PrintMPU(v850P v850, Uns8 mpu_size);

#endif // V850_MPU_H
