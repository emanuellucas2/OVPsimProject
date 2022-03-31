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

#ifndef POWERMONITOR_NATIVE_H
#define POWERMONITOR_NATIVE_H

// Define diagnostic levels
#define DIAG_LOW(_diag)        ((_diag & 3) > 0)
#define DIAG_MEDIUM(_diag)     ((_diag & 3) > 1)
#define DIAG_HIGH(_diag)       ((_diag & 3) > 2)

#include "ovpworld.org/modelSupport/powermonitor/1.0/pse/powermonitor.datatypes.h"

// name and version of Power Monitor Shared data channel
#define POWERMONITOR_CHANNEL_NAME    "PowerMonitor"
#define POWERMONITOR_CHANNEL_VERSION "3.0.0"

typedef struct sharedItemS {
    Uns32       ref;            // unique index of the rail in the platform
    Uns32       value;          // current value
    dataTypeE   dataType;       // indicates the voltage, current or power is being accessed
    dataFormatE dataFormat;     // type of register data being passed, indicates if linear16, linear11, XADC etc.
} sharedItemT, *sharedItemTP;

#endif
