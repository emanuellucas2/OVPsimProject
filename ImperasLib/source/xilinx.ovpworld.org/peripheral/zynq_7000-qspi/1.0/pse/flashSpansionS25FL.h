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

#ifndef FLASH_SPANSION_S25FL_H_
#define FLASH_SPANSION_S25FL_H_

#include "pse.igen.h"

Uns32 flashSpansionS25FLAccess(Uns32, Uns32);    // perform an access and return result
void  flashSpansionS25FLDisable(void);           // flash diasbled (remove chip select)
void  flashSpansionS25FLInit(void);              // flash initialization
void  flashSpansionS25FLFinish(void);            // flash finish

#endif /* FLASH_SPANSION_S25FL_H_ */
