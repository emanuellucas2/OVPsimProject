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

// Set the macro 'INTCP0' to the base of port 'INTCP0'
#ifndef INTCP0
#error INTCP0 is undefined. It needs to be set to the port base address
#endif


#define INTCP0_REG0_POFFSET             0x0
#define INTCP0_REG0_IMR0_POFFSET        0x0
#define INTCP0_REG0_IMR0                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR0_POFFSET)

#define INTCP0_REG0_IMR1_POFFSET        0x2
#define INTCP0_REG0_IMR1                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR1_POFFSET)

#define INTCP0_REG0_IMR2_POFFSET        0x4
#define INTCP0_REG0_IMR2                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR2_POFFSET)

#define INTCP0_REG0_IMR3_POFFSET        0x6
#define INTCP0_REG0_IMR3                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR3_POFFSET)

#define INTCP0_REG0_IMR4_POFFSET        0x8
#define INTCP0_REG0_IMR4                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR4_POFFSET)

#define INTCP0_REG0_IMR5_POFFSET        0xa
#define INTCP0_REG0_IMR5                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR5_POFFSET)

#define INTCP0_REG0_IMR6_POFFSET        0xc
#define INTCP0_REG0_IMR6                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR6_POFFSET)

#define INTCP0_REG0_IMR7_POFFSET        0xe
#define INTCP0_REG0_IMR7                (INTCP0 + INTCP0_REG0_POFFSET + INTCP0_REG0_IMR7_POFFSET)

#define INTCP0_REG1_POFFSET             0x10
#define INTCP0_REG1_IC000_POFFSET       0x0
#define INTCP0_REG1_IC000               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC000_POFFSET)
#define INTCP0_REG1_IC000_IF            (0x1 << 7)
#define INTCP0_REG1_IC000_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC000_MK            (0x1 << 6)
#define INTCP0_REG1_IC000_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC000_PR            0x7
#define INTCP0_REG1_IC000_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC001_POFFSET       0x2
#define INTCP0_REG1_IC001               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC001_POFFSET)
#define INTCP0_REG1_IC001_IF            (0x1 << 7)
#define INTCP0_REG1_IC001_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC001_MK            (0x1 << 6)
#define INTCP0_REG1_IC001_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC001_PR            0x7
#define INTCP0_REG1_IC001_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC002_POFFSET       0x4
#define INTCP0_REG1_IC002               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC002_POFFSET)
#define INTCP0_REG1_IC002_IF            (0x1 << 7)
#define INTCP0_REG1_IC002_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC002_MK            (0x1 << 6)
#define INTCP0_REG1_IC002_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC002_PR            0x7
#define INTCP0_REG1_IC002_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC003_POFFSET       0x6
#define INTCP0_REG1_IC003               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC003_POFFSET)
#define INTCP0_REG1_IC003_IF            (0x1 << 7)
#define INTCP0_REG1_IC003_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC003_MK            (0x1 << 6)
#define INTCP0_REG1_IC003_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC003_PR            0x7
#define INTCP0_REG1_IC003_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC004_POFFSET       0x8
#define INTCP0_REG1_IC004               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC004_POFFSET)
#define INTCP0_REG1_IC004_IF            (0x1 << 7)
#define INTCP0_REG1_IC004_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC004_MK            (0x1 << 6)
#define INTCP0_REG1_IC004_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC004_PR            0x7
#define INTCP0_REG1_IC004_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC005_POFFSET       0xa
#define INTCP0_REG1_IC005               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC005_POFFSET)
#define INTCP0_REG1_IC005_IF            (0x1 << 7)
#define INTCP0_REG1_IC005_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC005_MK            (0x1 << 6)
#define INTCP0_REG1_IC005_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC005_PR            0x7
#define INTCP0_REG1_IC005_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC006_POFFSET       0xc
#define INTCP0_REG1_IC006               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC006_POFFSET)
#define INTCP0_REG1_IC006_IF            (0x1 << 7)
#define INTCP0_REG1_IC006_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC006_MK            (0x1 << 6)
#define INTCP0_REG1_IC006_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC006_PR            0x7
#define INTCP0_REG1_IC006_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC007_POFFSET       0xe
#define INTCP0_REG1_IC007               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC007_POFFSET)
#define INTCP0_REG1_IC007_IF            (0x1 << 7)
#define INTCP0_REG1_IC007_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC007_MK            (0x1 << 6)
#define INTCP0_REG1_IC007_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC007_PR            0x7
#define INTCP0_REG1_IC007_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC008_POFFSET       0x10
#define INTCP0_REG1_IC008               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC008_POFFSET)
#define INTCP0_REG1_IC008_IF            (0x1 << 7)
#define INTCP0_REG1_IC008_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC008_MK            (0x1 << 6)
#define INTCP0_REG1_IC008_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC008_PR            0x7
#define INTCP0_REG1_IC008_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC009_POFFSET       0x12
#define INTCP0_REG1_IC009               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC009_POFFSET)
#define INTCP0_REG1_IC009_IF            (0x1 << 7)
#define INTCP0_REG1_IC009_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC009_MK            (0x1 << 6)
#define INTCP0_REG1_IC009_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC009_PR            0x7
#define INTCP0_REG1_IC009_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC010_POFFSET       0x14
#define INTCP0_REG1_IC010               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC010_POFFSET)
#define INTCP0_REG1_IC010_IF            (0x1 << 7)
#define INTCP0_REG1_IC010_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC010_MK            (0x1 << 6)
#define INTCP0_REG1_IC010_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC010_PR            0x7
#define INTCP0_REG1_IC010_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC011_POFFSET       0x16
#define INTCP0_REG1_IC011               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC011_POFFSET)
#define INTCP0_REG1_IC011_IF            (0x1 << 7)
#define INTCP0_REG1_IC011_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC011_MK            (0x1 << 6)
#define INTCP0_REG1_IC011_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC011_PR            0x7
#define INTCP0_REG1_IC011_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC012_POFFSET       0x18
#define INTCP0_REG1_IC012               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC012_POFFSET)
#define INTCP0_REG1_IC012_IF            (0x1 << 7)
#define INTCP0_REG1_IC012_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC012_MK            (0x1 << 6)
#define INTCP0_REG1_IC012_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC012_PR            0x7
#define INTCP0_REG1_IC012_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC013_POFFSET       0x1a
#define INTCP0_REG1_IC013               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC013_POFFSET)
#define INTCP0_REG1_IC013_IF            (0x1 << 7)
#define INTCP0_REG1_IC013_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC013_MK            (0x1 << 6)
#define INTCP0_REG1_IC013_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC013_PR            0x7
#define INTCP0_REG1_IC013_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC014_POFFSET       0x1c
#define INTCP0_REG1_IC014               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC014_POFFSET)
#define INTCP0_REG1_IC014_IF            (0x1 << 7)
#define INTCP0_REG1_IC014_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC014_MK            (0x1 << 6)
#define INTCP0_REG1_IC014_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC014_PR            0x7
#define INTCP0_REG1_IC014_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC015_POFFSET       0x1e
#define INTCP0_REG1_IC015               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC015_POFFSET)
#define INTCP0_REG1_IC015_IF            (0x1 << 7)
#define INTCP0_REG1_IC015_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC015_MK            (0x1 << 6)
#define INTCP0_REG1_IC015_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC015_PR            0x7
#define INTCP0_REG1_IC015_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC016_POFFSET       0x20
#define INTCP0_REG1_IC016               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC016_POFFSET)
#define INTCP0_REG1_IC016_IF            (0x1 << 7)
#define INTCP0_REG1_IC016_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC016_MK            (0x1 << 6)
#define INTCP0_REG1_IC016_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC016_PR            0x7
#define INTCP0_REG1_IC016_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC017_POFFSET       0x22
#define INTCP0_REG1_IC017               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC017_POFFSET)
#define INTCP0_REG1_IC017_IF            (0x1 << 7)
#define INTCP0_REG1_IC017_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC017_MK            (0x1 << 6)
#define INTCP0_REG1_IC017_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC017_PR            0x7
#define INTCP0_REG1_IC017_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC018_POFFSET       0x24
#define INTCP0_REG1_IC018               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC018_POFFSET)
#define INTCP0_REG1_IC018_IF            (0x1 << 7)
#define INTCP0_REG1_IC018_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC018_MK            (0x1 << 6)
#define INTCP0_REG1_IC018_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC018_PR            0x7
#define INTCP0_REG1_IC018_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC019_POFFSET       0x26
#define INTCP0_REG1_IC019               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC019_POFFSET)
#define INTCP0_REG1_IC019_IF            (0x1 << 7)
#define INTCP0_REG1_IC019_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC019_MK            (0x1 << 6)
#define INTCP0_REG1_IC019_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC019_PR            0x7
#define INTCP0_REG1_IC019_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC020_POFFSET       0x28
#define INTCP0_REG1_IC020               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC020_POFFSET)
#define INTCP0_REG1_IC020_IF            (0x1 << 7)
#define INTCP0_REG1_IC020_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC020_MK            (0x1 << 6)
#define INTCP0_REG1_IC020_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC020_PR            0x7
#define INTCP0_REG1_IC020_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC021_POFFSET       0x2a
#define INTCP0_REG1_IC021               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC021_POFFSET)
#define INTCP0_REG1_IC021_IF            (0x1 << 7)
#define INTCP0_REG1_IC021_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC021_MK            (0x1 << 6)
#define INTCP0_REG1_IC021_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC021_PR            0x7
#define INTCP0_REG1_IC021_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC022_POFFSET       0x2c
#define INTCP0_REG1_IC022               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC022_POFFSET)
#define INTCP0_REG1_IC022_IF            (0x1 << 7)
#define INTCP0_REG1_IC022_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC022_MK            (0x1 << 6)
#define INTCP0_REG1_IC022_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC022_PR            0x7
#define INTCP0_REG1_IC022_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC023_POFFSET       0x2e
#define INTCP0_REG1_IC023               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC023_POFFSET)
#define INTCP0_REG1_IC023_IF            (0x1 << 7)
#define INTCP0_REG1_IC023_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC023_MK            (0x1 << 6)
#define INTCP0_REG1_IC023_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC023_PR            0x7
#define INTCP0_REG1_IC023_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC024_POFFSET       0x30
#define INTCP0_REG1_IC024               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC024_POFFSET)
#define INTCP0_REG1_IC024_IF            (0x1 << 7)
#define INTCP0_REG1_IC024_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC024_MK            (0x1 << 6)
#define INTCP0_REG1_IC024_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC024_PR            0x7
#define INTCP0_REG1_IC024_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC025_POFFSET       0x32
#define INTCP0_REG1_IC025               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC025_POFFSET)
#define INTCP0_REG1_IC025_IF            (0x1 << 7)
#define INTCP0_REG1_IC025_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC025_MK            (0x1 << 6)
#define INTCP0_REG1_IC025_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC025_PR            0x7
#define INTCP0_REG1_IC025_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC026_POFFSET       0x34
#define INTCP0_REG1_IC026               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC026_POFFSET)
#define INTCP0_REG1_IC026_IF            (0x1 << 7)
#define INTCP0_REG1_IC026_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC026_MK            (0x1 << 6)
#define INTCP0_REG1_IC026_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC026_PR            0x7
#define INTCP0_REG1_IC026_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC027_POFFSET       0x36
#define INTCP0_REG1_IC027               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC027_POFFSET)
#define INTCP0_REG1_IC027_IF            (0x1 << 7)
#define INTCP0_REG1_IC027_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC027_MK            (0x1 << 6)
#define INTCP0_REG1_IC027_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC027_PR            0x7
#define INTCP0_REG1_IC027_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC028_POFFSET       0x38
#define INTCP0_REG1_IC028               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC028_POFFSET)
#define INTCP0_REG1_IC028_IF            (0x1 << 7)
#define INTCP0_REG1_IC028_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC028_MK            (0x1 << 6)
#define INTCP0_REG1_IC028_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC028_PR            0x7
#define INTCP0_REG1_IC028_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC029_POFFSET       0x3a
#define INTCP0_REG1_IC029               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC029_POFFSET)
#define INTCP0_REG1_IC029_IF            (0x1 << 7)
#define INTCP0_REG1_IC029_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC029_MK            (0x1 << 6)
#define INTCP0_REG1_IC029_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC029_PR            0x7
#define INTCP0_REG1_IC029_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC030_POFFSET       0x3c
#define INTCP0_REG1_IC030               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC030_POFFSET)
#define INTCP0_REG1_IC030_IF            (0x1 << 7)
#define INTCP0_REG1_IC030_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC030_MK            (0x1 << 6)
#define INTCP0_REG1_IC030_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC030_PR            0x7
#define INTCP0_REG1_IC030_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC031_POFFSET       0x3e
#define INTCP0_REG1_IC031               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC031_POFFSET)
#define INTCP0_REG1_IC031_IF            (0x1 << 7)
#define INTCP0_REG1_IC031_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC031_MK            (0x1 << 6)
#define INTCP0_REG1_IC031_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC031_PR            0x7
#define INTCP0_REG1_IC031_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC032_POFFSET       0x40
#define INTCP0_REG1_IC032               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC032_POFFSET)
#define INTCP0_REG1_IC032_IF            (0x1 << 7)
#define INTCP0_REG1_IC032_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC032_MK            (0x1 << 6)
#define INTCP0_REG1_IC032_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC032_PR            0x7
#define INTCP0_REG1_IC032_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC033_POFFSET       0x42
#define INTCP0_REG1_IC033               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC033_POFFSET)
#define INTCP0_REG1_IC033_IF            (0x1 << 7)
#define INTCP0_REG1_IC033_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC033_MK            (0x1 << 6)
#define INTCP0_REG1_IC033_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC033_PR            0x7
#define INTCP0_REG1_IC033_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC034_POFFSET       0x44
#define INTCP0_REG1_IC034               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC034_POFFSET)
#define INTCP0_REG1_IC034_IF            (0x1 << 7)
#define INTCP0_REG1_IC034_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC034_MK            (0x1 << 6)
#define INTCP0_REG1_IC034_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC034_PR            0x7
#define INTCP0_REG1_IC034_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC035_POFFSET       0x46
#define INTCP0_REG1_IC035               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC035_POFFSET)
#define INTCP0_REG1_IC035_IF            (0x1 << 7)
#define INTCP0_REG1_IC035_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC035_MK            (0x1 << 6)
#define INTCP0_REG1_IC035_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC035_PR            0x7
#define INTCP0_REG1_IC035_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC036_POFFSET       0x48
#define INTCP0_REG1_IC036               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC036_POFFSET)
#define INTCP0_REG1_IC036_IF            (0x1 << 7)
#define INTCP0_REG1_IC036_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC036_MK            (0x1 << 6)
#define INTCP0_REG1_IC036_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC036_PR            0x7
#define INTCP0_REG1_IC036_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC037_POFFSET       0x4a
#define INTCP0_REG1_IC037               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC037_POFFSET)
#define INTCP0_REG1_IC037_IF            (0x1 << 7)
#define INTCP0_REG1_IC037_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC037_MK            (0x1 << 6)
#define INTCP0_REG1_IC037_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC037_PR            0x7
#define INTCP0_REG1_IC037_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC038_POFFSET       0x4c
#define INTCP0_REG1_IC038               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC038_POFFSET)
#define INTCP0_REG1_IC038_IF            (0x1 << 7)
#define INTCP0_REG1_IC038_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC038_MK            (0x1 << 6)
#define INTCP0_REG1_IC038_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC038_PR            0x7
#define INTCP0_REG1_IC038_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC039_POFFSET       0x4e
#define INTCP0_REG1_IC039               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC039_POFFSET)
#define INTCP0_REG1_IC039_IF            (0x1 << 7)
#define INTCP0_REG1_IC039_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC039_MK            (0x1 << 6)
#define INTCP0_REG1_IC039_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC039_PR            0x7
#define INTCP0_REG1_IC039_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC040_POFFSET       0x50
#define INTCP0_REG1_IC040               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC040_POFFSET)
#define INTCP0_REG1_IC040_IF            (0x1 << 7)
#define INTCP0_REG1_IC040_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC040_MK            (0x1 << 6)
#define INTCP0_REG1_IC040_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC040_PR            0x7
#define INTCP0_REG1_IC040_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC041_POFFSET       0x52
#define INTCP0_REG1_IC041               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC041_POFFSET)
#define INTCP0_REG1_IC041_IF            (0x1 << 7)
#define INTCP0_REG1_IC041_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC041_MK            (0x1 << 6)
#define INTCP0_REG1_IC041_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC041_PR            0x7
#define INTCP0_REG1_IC041_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC042_POFFSET       0x54
#define INTCP0_REG1_IC042               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC042_POFFSET)
#define INTCP0_REG1_IC042_IF            (0x1 << 7)
#define INTCP0_REG1_IC042_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC042_MK            (0x1 << 6)
#define INTCP0_REG1_IC042_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC042_PR            0x7
#define INTCP0_REG1_IC042_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC043_POFFSET       0x56
#define INTCP0_REG1_IC043               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC043_POFFSET)
#define INTCP0_REG1_IC043_IF            (0x1 << 7)
#define INTCP0_REG1_IC043_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC043_MK            (0x1 << 6)
#define INTCP0_REG1_IC043_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC043_PR            0x7
#define INTCP0_REG1_IC043_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC044_POFFSET       0x58
#define INTCP0_REG1_IC044               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC044_POFFSET)
#define INTCP0_REG1_IC044_IF            (0x1 << 7)
#define INTCP0_REG1_IC044_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC044_MK            (0x1 << 6)
#define INTCP0_REG1_IC044_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC044_PR            0x7
#define INTCP0_REG1_IC044_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC045_POFFSET       0x5a
#define INTCP0_REG1_IC045               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC045_POFFSET)
#define INTCP0_REG1_IC045_IF            (0x1 << 7)
#define INTCP0_REG1_IC045_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC045_MK            (0x1 << 6)
#define INTCP0_REG1_IC045_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC045_PR            0x7
#define INTCP0_REG1_IC045_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC046_POFFSET       0x5c
#define INTCP0_REG1_IC046               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC046_POFFSET)
#define INTCP0_REG1_IC046_IF            (0x1 << 7)
#define INTCP0_REG1_IC046_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC046_MK            (0x1 << 6)
#define INTCP0_REG1_IC046_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC046_PR            0x7
#define INTCP0_REG1_IC046_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC047_POFFSET       0x5e
#define INTCP0_REG1_IC047               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC047_POFFSET)
#define INTCP0_REG1_IC047_IF            (0x1 << 7)
#define INTCP0_REG1_IC047_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC047_MK            (0x1 << 6)
#define INTCP0_REG1_IC047_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC047_PR            0x7
#define INTCP0_REG1_IC047_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC048_POFFSET       0x60
#define INTCP0_REG1_IC048               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC048_POFFSET)
#define INTCP0_REG1_IC048_IF            (0x1 << 7)
#define INTCP0_REG1_IC048_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC048_MK            (0x1 << 6)
#define INTCP0_REG1_IC048_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC048_PR            0x7
#define INTCP0_REG1_IC048_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC049_POFFSET       0x62
#define INTCP0_REG1_IC049               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC049_POFFSET)
#define INTCP0_REG1_IC049_IF            (0x1 << 7)
#define INTCP0_REG1_IC049_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC049_MK            (0x1 << 6)
#define INTCP0_REG1_IC049_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC049_PR            0x7
#define INTCP0_REG1_IC049_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC050_POFFSET       0x64
#define INTCP0_REG1_IC050               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC050_POFFSET)
#define INTCP0_REG1_IC050_IF            (0x1 << 7)
#define INTCP0_REG1_IC050_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC050_MK            (0x1 << 6)
#define INTCP0_REG1_IC050_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC050_PR            0x7
#define INTCP0_REG1_IC050_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC051_POFFSET       0x66
#define INTCP0_REG1_IC051               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC051_POFFSET)
#define INTCP0_REG1_IC051_IF            (0x1 << 7)
#define INTCP0_REG1_IC051_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC051_MK            (0x1 << 6)
#define INTCP0_REG1_IC051_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC051_PR            0x7
#define INTCP0_REG1_IC051_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC052_POFFSET       0x68
#define INTCP0_REG1_IC052               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC052_POFFSET)
#define INTCP0_REG1_IC052_IF            (0x1 << 7)
#define INTCP0_REG1_IC052_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC052_MK            (0x1 << 6)
#define INTCP0_REG1_IC052_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC052_PR            0x7
#define INTCP0_REG1_IC052_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC053_POFFSET       0x6a
#define INTCP0_REG1_IC053               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC053_POFFSET)
#define INTCP0_REG1_IC053_IF            (0x1 << 7)
#define INTCP0_REG1_IC053_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC053_MK            (0x1 << 6)
#define INTCP0_REG1_IC053_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC053_PR            0x7
#define INTCP0_REG1_IC053_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC054_POFFSET       0x6c
#define INTCP0_REG1_IC054               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC054_POFFSET)
#define INTCP0_REG1_IC054_IF            (0x1 << 7)
#define INTCP0_REG1_IC054_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC054_MK            (0x1 << 6)
#define INTCP0_REG1_IC054_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC054_PR            0x7
#define INTCP0_REG1_IC054_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC055_POFFSET       0x6e
#define INTCP0_REG1_IC055               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC055_POFFSET)
#define INTCP0_REG1_IC055_IF            (0x1 << 7)
#define INTCP0_REG1_IC055_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC055_MK            (0x1 << 6)
#define INTCP0_REG1_IC055_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC055_PR            0x7
#define INTCP0_REG1_IC055_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC056_POFFSET       0x70
#define INTCP0_REG1_IC056               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC056_POFFSET)
#define INTCP0_REG1_IC056_IF            (0x1 << 7)
#define INTCP0_REG1_IC056_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC056_MK            (0x1 << 6)
#define INTCP0_REG1_IC056_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC056_PR            0x7
#define INTCP0_REG1_IC056_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC057_POFFSET       0x72
#define INTCP0_REG1_IC057               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC057_POFFSET)
#define INTCP0_REG1_IC057_IF            (0x1 << 7)
#define INTCP0_REG1_IC057_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC057_MK            (0x1 << 6)
#define INTCP0_REG1_IC057_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC057_PR            0x7
#define INTCP0_REG1_IC057_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC058_POFFSET       0x74
#define INTCP0_REG1_IC058               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC058_POFFSET)
#define INTCP0_REG1_IC058_IF            (0x1 << 7)
#define INTCP0_REG1_IC058_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC058_MK            (0x1 << 6)
#define INTCP0_REG1_IC058_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC058_PR            0x7
#define INTCP0_REG1_IC058_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC059_POFFSET       0x76
#define INTCP0_REG1_IC059               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC059_POFFSET)
#define INTCP0_REG1_IC059_IF            (0x1 << 7)
#define INTCP0_REG1_IC059_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC059_MK            (0x1 << 6)
#define INTCP0_REG1_IC059_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC059_PR            0x7
#define INTCP0_REG1_IC059_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC060_POFFSET       0x78
#define INTCP0_REG1_IC060               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC060_POFFSET)
#define INTCP0_REG1_IC060_IF            (0x1 << 7)
#define INTCP0_REG1_IC060_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC060_MK            (0x1 << 6)
#define INTCP0_REG1_IC060_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC060_PR            0x7
#define INTCP0_REG1_IC060_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC061_POFFSET       0x7a
#define INTCP0_REG1_IC061               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC061_POFFSET)
#define INTCP0_REG1_IC061_IF            (0x1 << 7)
#define INTCP0_REG1_IC061_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC061_MK            (0x1 << 6)
#define INTCP0_REG1_IC061_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC061_PR            0x7
#define INTCP0_REG1_IC061_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC062_POFFSET       0x7c
#define INTCP0_REG1_IC062               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC062_POFFSET)
#define INTCP0_REG1_IC062_IF            (0x1 << 7)
#define INTCP0_REG1_IC062_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC062_MK            (0x1 << 6)
#define INTCP0_REG1_IC062_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC062_PR            0x7
#define INTCP0_REG1_IC062_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC063_POFFSET       0x7e
#define INTCP0_REG1_IC063               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC063_POFFSET)
#define INTCP0_REG1_IC063_IF            (0x1 << 7)
#define INTCP0_REG1_IC063_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC063_MK            (0x1 << 6)
#define INTCP0_REG1_IC063_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC063_PR            0x7
#define INTCP0_REG1_IC063_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC064_POFFSET       0x80
#define INTCP0_REG1_IC064               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC064_POFFSET)
#define INTCP0_REG1_IC064_IF            (0x1 << 7)
#define INTCP0_REG1_IC064_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC064_MK            (0x1 << 6)
#define INTCP0_REG1_IC064_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC064_PR            0x7
#define INTCP0_REG1_IC064_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC065_POFFSET       0x82
#define INTCP0_REG1_IC065               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC065_POFFSET)
#define INTCP0_REG1_IC065_IF            (0x1 << 7)
#define INTCP0_REG1_IC065_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC065_MK            (0x1 << 6)
#define INTCP0_REG1_IC065_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC065_PR            0x7
#define INTCP0_REG1_IC065_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC066_POFFSET       0x84
#define INTCP0_REG1_IC066               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC066_POFFSET)
#define INTCP0_REG1_IC066_IF            (0x1 << 7)
#define INTCP0_REG1_IC066_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC066_MK            (0x1 << 6)
#define INTCP0_REG1_IC066_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC066_PR            0x7
#define INTCP0_REG1_IC066_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC067_POFFSET       0x86
#define INTCP0_REG1_IC067               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC067_POFFSET)
#define INTCP0_REG1_IC067_IF            (0x1 << 7)
#define INTCP0_REG1_IC067_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC067_MK            (0x1 << 6)
#define INTCP0_REG1_IC067_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC067_PR            0x7
#define INTCP0_REG1_IC067_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC068_POFFSET       0x88
#define INTCP0_REG1_IC068               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC068_POFFSET)
#define INTCP0_REG1_IC068_IF            (0x1 << 7)
#define INTCP0_REG1_IC068_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC068_MK            (0x1 << 6)
#define INTCP0_REG1_IC068_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC068_PR            0x7
#define INTCP0_REG1_IC068_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC069_POFFSET       0x8a
#define INTCP0_REG1_IC069               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC069_POFFSET)
#define INTCP0_REG1_IC069_IF            (0x1 << 7)
#define INTCP0_REG1_IC069_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC069_MK            (0x1 << 6)
#define INTCP0_REG1_IC069_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC069_PR            0x7
#define INTCP0_REG1_IC069_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC070_POFFSET       0x8c
#define INTCP0_REG1_IC070               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC070_POFFSET)
#define INTCP0_REG1_IC070_IF            (0x1 << 7)
#define INTCP0_REG1_IC070_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC070_MK            (0x1 << 6)
#define INTCP0_REG1_IC070_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC070_PR            0x7
#define INTCP0_REG1_IC070_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC071_POFFSET       0x8e
#define INTCP0_REG1_IC071               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC071_POFFSET)
#define INTCP0_REG1_IC071_IF            (0x1 << 7)
#define INTCP0_REG1_IC071_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC071_MK            (0x1 << 6)
#define INTCP0_REG1_IC071_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC071_PR            0x7
#define INTCP0_REG1_IC071_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC072_POFFSET       0x90
#define INTCP0_REG1_IC072               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC072_POFFSET)
#define INTCP0_REG1_IC072_IF            (0x1 << 7)
#define INTCP0_REG1_IC072_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC072_MK            (0x1 << 6)
#define INTCP0_REG1_IC072_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC072_PR            0x7
#define INTCP0_REG1_IC072_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC073_POFFSET       0x92
#define INTCP0_REG1_IC073               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC073_POFFSET)
#define INTCP0_REG1_IC073_IF            (0x1 << 7)
#define INTCP0_REG1_IC073_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC073_MK            (0x1 << 6)
#define INTCP0_REG1_IC073_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC073_PR            0x7
#define INTCP0_REG1_IC073_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC074_POFFSET       0x94
#define INTCP0_REG1_IC074               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC074_POFFSET)
#define INTCP0_REG1_IC074_IF            (0x1 << 7)
#define INTCP0_REG1_IC074_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC074_MK            (0x1 << 6)
#define INTCP0_REG1_IC074_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC074_PR            0x7
#define INTCP0_REG1_IC074_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC075_POFFSET       0x96
#define INTCP0_REG1_IC075               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC075_POFFSET)
#define INTCP0_REG1_IC075_IF            (0x1 << 7)
#define INTCP0_REG1_IC075_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC075_MK            (0x1 << 6)
#define INTCP0_REG1_IC075_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC075_PR            0x7
#define INTCP0_REG1_IC075_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC076_POFFSET       0x98
#define INTCP0_REG1_IC076               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC076_POFFSET)
#define INTCP0_REG1_IC076_IF            (0x1 << 7)
#define INTCP0_REG1_IC076_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC076_MK            (0x1 << 6)
#define INTCP0_REG1_IC076_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC076_PR            0x7
#define INTCP0_REG1_IC076_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC077_POFFSET       0x9a
#define INTCP0_REG1_IC077               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC077_POFFSET)
#define INTCP0_REG1_IC077_IF            (0x1 << 7)
#define INTCP0_REG1_IC077_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC077_MK            (0x1 << 6)
#define INTCP0_REG1_IC077_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC077_PR            0x7
#define INTCP0_REG1_IC077_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC078_POFFSET       0x9c
#define INTCP0_REG1_IC078               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC078_POFFSET)
#define INTCP0_REG1_IC078_IF            (0x1 << 7)
#define INTCP0_REG1_IC078_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC078_MK            (0x1 << 6)
#define INTCP0_REG1_IC078_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC078_PR            0x7
#define INTCP0_REG1_IC078_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC079_POFFSET       0x9e
#define INTCP0_REG1_IC079               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC079_POFFSET)
#define INTCP0_REG1_IC079_IF            (0x1 << 7)
#define INTCP0_REG1_IC079_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC079_MK            (0x1 << 6)
#define INTCP0_REG1_IC079_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC079_PR            0x7
#define INTCP0_REG1_IC079_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC080_POFFSET       0xa0
#define INTCP0_REG1_IC080               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC080_POFFSET)
#define INTCP0_REG1_IC080_IF            (0x1 << 7)
#define INTCP0_REG1_IC080_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC080_MK            (0x1 << 6)
#define INTCP0_REG1_IC080_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC080_PR            0x7
#define INTCP0_REG1_IC080_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC081_POFFSET       0xa2
#define INTCP0_REG1_IC081               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC081_POFFSET)
#define INTCP0_REG1_IC081_IF            (0x1 << 7)
#define INTCP0_REG1_IC081_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC081_MK            (0x1 << 6)
#define INTCP0_REG1_IC081_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC081_PR            0x7
#define INTCP0_REG1_IC081_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC082_POFFSET       0xa4
#define INTCP0_REG1_IC082               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC082_POFFSET)
#define INTCP0_REG1_IC082_IF            (0x1 << 7)
#define INTCP0_REG1_IC082_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC082_MK            (0x1 << 6)
#define INTCP0_REG1_IC082_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC082_PR            0x7
#define INTCP0_REG1_IC082_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC083_POFFSET       0xa6
#define INTCP0_REG1_IC083               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC083_POFFSET)
#define INTCP0_REG1_IC083_IF            (0x1 << 7)
#define INTCP0_REG1_IC083_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC083_MK            (0x1 << 6)
#define INTCP0_REG1_IC083_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC083_PR            0x7
#define INTCP0_REG1_IC083_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC084_POFFSET       0xa8
#define INTCP0_REG1_IC084               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC084_POFFSET)
#define INTCP0_REG1_IC084_IF            (0x1 << 7)
#define INTCP0_REG1_IC084_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC084_MK            (0x1 << 6)
#define INTCP0_REG1_IC084_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC084_PR            0x7
#define INTCP0_REG1_IC084_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC085_POFFSET       0xaa
#define INTCP0_REG1_IC085               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC085_POFFSET)
#define INTCP0_REG1_IC085_IF            (0x1 << 7)
#define INTCP0_REG1_IC085_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC085_MK            (0x1 << 6)
#define INTCP0_REG1_IC085_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC085_PR            0x7
#define INTCP0_REG1_IC085_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC086_POFFSET       0xac
#define INTCP0_REG1_IC086               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC086_POFFSET)
#define INTCP0_REG1_IC086_IF            (0x1 << 7)
#define INTCP0_REG1_IC086_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC086_MK            (0x1 << 6)
#define INTCP0_REG1_IC086_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC086_PR            0x7
#define INTCP0_REG1_IC086_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC087_POFFSET       0xae
#define INTCP0_REG1_IC087               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC087_POFFSET)
#define INTCP0_REG1_IC087_IF            (0x1 << 7)
#define INTCP0_REG1_IC087_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC087_MK            (0x1 << 6)
#define INTCP0_REG1_IC087_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC087_PR            0x7
#define INTCP0_REG1_IC087_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC088_POFFSET       0xb0
#define INTCP0_REG1_IC088               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC088_POFFSET)
#define INTCP0_REG1_IC088_IF            (0x1 << 7)
#define INTCP0_REG1_IC088_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC088_MK            (0x1 << 6)
#define INTCP0_REG1_IC088_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC088_PR            0x7
#define INTCP0_REG1_IC088_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC089_POFFSET       0xb2
#define INTCP0_REG1_IC089               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC089_POFFSET)
#define INTCP0_REG1_IC089_IF            (0x1 << 7)
#define INTCP0_REG1_IC089_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC089_MK            (0x1 << 6)
#define INTCP0_REG1_IC089_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC089_PR            0x7
#define INTCP0_REG1_IC089_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC090_POFFSET       0xb4
#define INTCP0_REG1_IC090               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC090_POFFSET)
#define INTCP0_REG1_IC090_IF            (0x1 << 7)
#define INTCP0_REG1_IC090_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC090_MK            (0x1 << 6)
#define INTCP0_REG1_IC090_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC090_PR            0x7
#define INTCP0_REG1_IC090_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC091_POFFSET       0xb6
#define INTCP0_REG1_IC091               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC091_POFFSET)
#define INTCP0_REG1_IC091_IF            (0x1 << 7)
#define INTCP0_REG1_IC091_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC091_MK            (0x1 << 6)
#define INTCP0_REG1_IC091_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC091_PR            0x7
#define INTCP0_REG1_IC091_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC092_POFFSET       0xb8
#define INTCP0_REG1_IC092               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC092_POFFSET)
#define INTCP0_REG1_IC092_IF            (0x1 << 7)
#define INTCP0_REG1_IC092_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC092_MK            (0x1 << 6)
#define INTCP0_REG1_IC092_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC092_PR            0x7
#define INTCP0_REG1_IC092_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC093_POFFSET       0xba
#define INTCP0_REG1_IC093               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC093_POFFSET)
#define INTCP0_REG1_IC093_IF            (0x1 << 7)
#define INTCP0_REG1_IC093_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC093_MK            (0x1 << 6)
#define INTCP0_REG1_IC093_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC093_PR            0x7
#define INTCP0_REG1_IC093_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC094_POFFSET       0xbc
#define INTCP0_REG1_IC094               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC094_POFFSET)
#define INTCP0_REG1_IC094_IF            (0x1 << 7)
#define INTCP0_REG1_IC094_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC094_MK            (0x1 << 6)
#define INTCP0_REG1_IC094_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC094_PR            0x7
#define INTCP0_REG1_IC094_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC095_POFFSET       0xbe
#define INTCP0_REG1_IC095               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC095_POFFSET)
#define INTCP0_REG1_IC095_IF            (0x1 << 7)
#define INTCP0_REG1_IC095_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC095_MK            (0x1 << 6)
#define INTCP0_REG1_IC095_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC095_PR            0x7
#define INTCP0_REG1_IC095_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC096_POFFSET       0xc0
#define INTCP0_REG1_IC096               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC096_POFFSET)
#define INTCP0_REG1_IC096_IF            (0x1 << 7)
#define INTCP0_REG1_IC096_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC096_MK            (0x1 << 6)
#define INTCP0_REG1_IC096_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC096_PR            0x7
#define INTCP0_REG1_IC096_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC097_POFFSET       0xc2
#define INTCP0_REG1_IC097               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC097_POFFSET)
#define INTCP0_REG1_IC097_IF            (0x1 << 7)
#define INTCP0_REG1_IC097_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC097_MK            (0x1 << 6)
#define INTCP0_REG1_IC097_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC097_PR            0x7
#define INTCP0_REG1_IC097_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC098_POFFSET       0xc4
#define INTCP0_REG1_IC098               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC098_POFFSET)
#define INTCP0_REG1_IC098_IF            (0x1 << 7)
#define INTCP0_REG1_IC098_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC098_MK            (0x1 << 6)
#define INTCP0_REG1_IC098_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC098_PR            0x7
#define INTCP0_REG1_IC098_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC099_POFFSET       0xc6
#define INTCP0_REG1_IC099               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC099_POFFSET)
#define INTCP0_REG1_IC099_IF            (0x1 << 7)
#define INTCP0_REG1_IC099_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC099_MK            (0x1 << 6)
#define INTCP0_REG1_IC099_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC099_PR            0x7
#define INTCP0_REG1_IC099_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC100_POFFSET       0xc8
#define INTCP0_REG1_IC100               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC100_POFFSET)
#define INTCP0_REG1_IC100_IF            (0x1 << 7)
#define INTCP0_REG1_IC100_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC100_MK            (0x1 << 6)
#define INTCP0_REG1_IC100_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC100_PR            0x7
#define INTCP0_REG1_IC100_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC101_POFFSET       0xca
#define INTCP0_REG1_IC101               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC101_POFFSET)
#define INTCP0_REG1_IC101_IF            (0x1 << 7)
#define INTCP0_REG1_IC101_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC101_MK            (0x1 << 6)
#define INTCP0_REG1_IC101_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC101_PR            0x7
#define INTCP0_REG1_IC101_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC102_POFFSET       0xcc
#define INTCP0_REG1_IC102               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC102_POFFSET)
#define INTCP0_REG1_IC102_IF            (0x1 << 7)
#define INTCP0_REG1_IC102_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC102_MK            (0x1 << 6)
#define INTCP0_REG1_IC102_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC102_PR            0x7
#define INTCP0_REG1_IC102_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC103_POFFSET       0xce
#define INTCP0_REG1_IC103               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC103_POFFSET)
#define INTCP0_REG1_IC103_IF            (0x1 << 7)
#define INTCP0_REG1_IC103_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC103_MK            (0x1 << 6)
#define INTCP0_REG1_IC103_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC103_PR            0x7
#define INTCP0_REG1_IC103_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC104_POFFSET       0xd0
#define INTCP0_REG1_IC104               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC104_POFFSET)
#define INTCP0_REG1_IC104_IF            (0x1 << 7)
#define INTCP0_REG1_IC104_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC104_MK            (0x1 << 6)
#define INTCP0_REG1_IC104_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC104_PR            0x7
#define INTCP0_REG1_IC104_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC105_POFFSET       0xd2
#define INTCP0_REG1_IC105               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC105_POFFSET)
#define INTCP0_REG1_IC105_IF            (0x1 << 7)
#define INTCP0_REG1_IC105_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC105_MK            (0x1 << 6)
#define INTCP0_REG1_IC105_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC105_PR            0x7
#define INTCP0_REG1_IC105_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC106_POFFSET       0xd4
#define INTCP0_REG1_IC106               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC106_POFFSET)
#define INTCP0_REG1_IC106_IF            (0x1 << 7)
#define INTCP0_REG1_IC106_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC106_MK            (0x1 << 6)
#define INTCP0_REG1_IC106_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC106_PR            0x7
#define INTCP0_REG1_IC106_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC107_POFFSET       0xd6
#define INTCP0_REG1_IC107               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC107_POFFSET)
#define INTCP0_REG1_IC107_IF            (0x1 << 7)
#define INTCP0_REG1_IC107_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC107_MK            (0x1 << 6)
#define INTCP0_REG1_IC107_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC107_PR            0x7
#define INTCP0_REG1_IC107_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC108_POFFSET       0xd8
#define INTCP0_REG1_IC108               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC108_POFFSET)
#define INTCP0_REG1_IC108_IF            (0x1 << 7)
#define INTCP0_REG1_IC108_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC108_MK            (0x1 << 6)
#define INTCP0_REG1_IC108_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC108_PR            0x7
#define INTCP0_REG1_IC108_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC109_POFFSET       0xda
#define INTCP0_REG1_IC109               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC109_POFFSET)
#define INTCP0_REG1_IC109_IF            (0x1 << 7)
#define INTCP0_REG1_IC109_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC109_MK            (0x1 << 6)
#define INTCP0_REG1_IC109_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC109_PR            0x7
#define INTCP0_REG1_IC109_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC110_POFFSET       0xdc
#define INTCP0_REG1_IC110               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC110_POFFSET)
#define INTCP0_REG1_IC110_IF            (0x1 << 7)
#define INTCP0_REG1_IC110_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC110_MK            (0x1 << 6)
#define INTCP0_REG1_IC110_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC110_PR            0x7
#define INTCP0_REG1_IC110_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC111_POFFSET       0xde
#define INTCP0_REG1_IC111               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC111_POFFSET)
#define INTCP0_REG1_IC111_IF            (0x1 << 7)
#define INTCP0_REG1_IC111_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC111_MK            (0x1 << 6)
#define INTCP0_REG1_IC111_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC111_PR            0x7
#define INTCP0_REG1_IC111_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC112_POFFSET       0xe0
#define INTCP0_REG1_IC112               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC112_POFFSET)
#define INTCP0_REG1_IC112_IF            (0x1 << 7)
#define INTCP0_REG1_IC112_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC112_MK            (0x1 << 6)
#define INTCP0_REG1_IC112_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC112_PR            0x7
#define INTCP0_REG1_IC112_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC113_POFFSET       0xe2
#define INTCP0_REG1_IC113               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC113_POFFSET)
#define INTCP0_REG1_IC113_IF            (0x1 << 7)
#define INTCP0_REG1_IC113_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC113_MK            (0x1 << 6)
#define INTCP0_REG1_IC113_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC113_PR            0x7
#define INTCP0_REG1_IC113_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC114_POFFSET       0xe4
#define INTCP0_REG1_IC114               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC114_POFFSET)
#define INTCP0_REG1_IC114_IF            (0x1 << 7)
#define INTCP0_REG1_IC114_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC114_MK            (0x1 << 6)
#define INTCP0_REG1_IC114_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC114_PR            0x7
#define INTCP0_REG1_IC114_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC115_POFFSET       0xe6
#define INTCP0_REG1_IC115               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC115_POFFSET)
#define INTCP0_REG1_IC115_IF            (0x1 << 7)
#define INTCP0_REG1_IC115_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC115_MK            (0x1 << 6)
#define INTCP0_REG1_IC115_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC115_PR            0x7
#define INTCP0_REG1_IC115_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_IC116_POFFSET       0xe8
#define INTCP0_REG1_IC116               (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_IC116_POFFSET)
#define INTCP0_REG1_IC116_IF            (0x1 << 7)
#define INTCP0_REG1_IC116_IF_GET(_v)    ((_v >> 7) & 0x1)
#define INTCP0_REG1_IC116_MK            (0x1 << 6)
#define INTCP0_REG1_IC116_MK_GET(_v)    ((_v >> 6) & 0x1)
#define INTCP0_REG1_IC116_PR            0x7
#define INTCP0_REG1_IC116_PR_GET(_v)    (_v & 0x7)

#define INTCP0_REG1_ISPR_POFFSET        0xea
#define INTCP0_REG1_ISPR                (INTCP0 + INTCP0_REG1_POFFSET + INTCP0_REG1_ISPR_POFFSET)
#define INTCP0_REG1_ISPR_ISPR0          0x1
#define INTCP0_REG1_ISPR_ISPR0_GET(_v)  (_v & 0x1)
#define INTCP0_REG1_ISPR_ISPR1          (0x1 << 1)
#define INTCP0_REG1_ISPR_ISPR1_GET(_v)  ((_v >> 1) & 0x1)
#define INTCP0_REG1_ISPR_ISPR2          (0x1 << 2)
#define INTCP0_REG1_ISPR_ISPR2_GET(_v)  ((_v >> 2) & 0x1)
#define INTCP0_REG1_ISPR_ISPR3          (0x1 << 3)
#define INTCP0_REG1_ISPR_ISPR3_GET(_v)  ((_v >> 3) & 0x1)
#define INTCP0_REG1_ISPR_ISPR4          (0x1 << 4)
#define INTCP0_REG1_ISPR_ISPR4_GET(_v)  ((_v >> 4) & 0x1)
#define INTCP0_REG1_ISPR_ISPR5          (0x1 << 5)
#define INTCP0_REG1_ISPR_ISPR5_GET(_v)  ((_v >> 5) & 0x1)
#define INTCP0_REG1_ISPR_ISPR6          (0x1 << 6)
#define INTCP0_REG1_ISPR_ISPR6_GET(_v)  ((_v >> 6) & 0x1)
#define INTCP0_REG1_ISPR_ISPR7          (0x1 << 7)
#define INTCP0_REG1_ISPR_ISPR7_GET(_v)  ((_v >> 7) & 0x1)


#endif
