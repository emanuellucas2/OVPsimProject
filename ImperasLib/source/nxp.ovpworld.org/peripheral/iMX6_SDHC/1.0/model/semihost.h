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


#ifndef SEMIHOST_H
#define SEMIHOST_H

#ifndef PREFIX
#define PREFIX "SDHC_NATIVE"
#endif

typedef struct pseHandlesS {
    Uns32 irq;
    Uns32 cardin;
    Uns32 wprot;
} pseHandlesT, *pseHandlesTP;

#define DIAG_HIGH (diag >= 3)
#define DIAG_MED  (diag >= 2)
#define DIAG_LOW  (diag >= 1)

#define DIAG_SEMIHOST_HIGH (((object->diag&0xc)>>2) >= 3)
#define DIAG_SEMIHOST_MED  (((object->diag&0xc)>>2) >= 2)
#define DIAG_SEMIHOST_LOW  (((object->diag&0xc)>>2) >= 1)

#define RWORD(n) ((response[n + 0] << 24) |  \
                  (response[n + 1] << 16) |  \
                  (response[n + 2] <<  8) |  \
                  (response[n + 3]      ))

#define FIFO_LEN 128

#endif
