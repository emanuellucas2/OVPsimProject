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

// Set arch size to 64 bits
#define RISCV_ARCH_BITS 64

#include "riscv.ovpworld.org/semihosting/riscvCommonNewlib/1.0/model/riscvCommonNewlib.c.h"

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,            // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,  // type
    .packageName    = "Newlib",               // description
    .objectSize     = sizeof(vmiosObject),    // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "riscv.ovpworld.org",
        .library = "semihosting",
        .name    = "riscv32Newlib",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB     = riscvNewLibSaveCB,            // model state save callback
    .restoreCB  = riscvNewLibRestoreCB,         // model state restore callback
    .srVersion  = 1,                            // model save/restore version

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,            // object constructor
    .destructorCB   = destructor,             // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                      // morph callback
    .nextPCCB       = 0,                      // get next instruction address
    .disCB          = 0,                      // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,        // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,    // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // ----------------- ------- ------ -----------------
        // Name              Address Opaque Callback
        // ----------------- ------- ------ -----------------
        //
        // newlib entries
        //
        { "kill",                   0,      True,  killCB           },
        { "time",                   0,      True,  timeCB           },
        { "close",                  0,      True,  closeCB          },
        { "_exit",                  0,      True,  exitCB           },
        { "fstat",                  0,      True,  fstatCB          },
        { "gettimeofday",           0,      True,  gettimeofdayCB   },
        { "lseek",                  0,      True,  lseekCB          },
        { "lstat",                  0,      True,  lstatCB          },
        { "open",                   0,      True,  openCB           },
        { "read",                   0,      True,  readCB           },
        { "stat",                   0,      True,  statCB           },
        { "times",                  0,      True,  timesCB          },
        { "unlink",                 0,      True,  unlinkCB         },
        { "write",                  0,      True,  writeCB          },

        //
        // provided by Proxy Kernel
        //
        { "sbrk",                   0,      True,  sbrkCB           },

        //
        // 7.1.1 gcc uses UNDERSCORE Prefix
        //
        { "_kill",                  0,      True,  killCB           },
        { "_time",                  0,      True,  timeCB           },
        { "_close",                 0,      True,  closeCB          },
        { "_exit",                  0,      True,  exitCB           },
        { "_fstat",                 0,      True,  fstatCB          },
        { "_gettimeofday",          0,      True,  gettimeofdayCB   },
        { "_lseek",                 0,      True,  lseekCB          },
        { "_lstat",                 0,      True,  lstatCB          },
        { "_open",                  0,      True,  openCB           },
        { "_read",                  0,      True,  readCB           },
        { "_stat",                  0,      True,  statCB           },
        { "_times",                 0,      True,  timesCB          },
        { "_unlink",                0,      True,  unlinkCB         },
        { "_write",                 0,      True,  writeCB          },

        //
        // provided by Proxy Kernel
        //
        { "_sbrk",                  0,      True,  sbrkCB           },

        //
        // Intercept main for argc, argv, env
        //
        { "main",                   0,      False, mainStackInitCB  },

        { 0 },
    }
};
