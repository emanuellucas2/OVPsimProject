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

// prefix for messages from this extension
#define PREFIX     "TM"
#define CPU_PREFIX "TM"

// standard includes
#include <stdio.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI area includes
#include "vmi/vmiDoc.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"

// extension header files
#include "tmConfig.h"
#include "tmCSR.h"

// processor model header files
#include "extensionConfig.h"

// base model header files
#include "riscvDisassembleFormats.h"
#include "riscvStructure.h"


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSR IDENTIFIERS
////////////////////////////////////////////////////////////////////////////////

typedef enum extCSRIdE {

    // TM configuration control and status registers
    XCSR_ID (tm_cfg),       // 0xFD0

    // keep last (used to define size of the enumeration)
    XCSR_ID (LAST)

} extCSRId;


////////////////////////////////////////////////////////////////////////////////
// TM EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

//
// Number of GPRs and FPRs (for saving banked registers)
//
#define RISCV_GPR_NUM 32
#define RISCV_FPR_NUM 32

//
// Maximum number of cached lines
//
#define CACHE_MAX_LINES 16

//
// Size of TM cache line in bytes
//
#define CACHE_LINE_BYTES 32

//
// Sanity check cache configuration
//
#if ((CACHE_LINE_BYTES-1) & CACHE_LINE_BYTES) != 0
#  error "CACHE_LINE_BYTES must be a power of 2"
#endif

//
// This represents a cached line
//
typedef struct cacheLineS {
    Addr       PA;                      // line physical address
    Uns8       line[CACHE_LINE_BYTES];  // line data
    Bool       dirty;                   // whether line is dirty
    Bool       readCallbackInstalled;   // read callbacks installed
    Bool       writeCallbackInstalled;  // write callbacks installed
} cacheLine, *cacheLineP;

//
// Abort types
//
typedef enum {
    TM_OK                 = 0x00, // valid transaction active
    TM_ABORT_MEM_CONFLICT = 0x01, // aborted due to memory conflict
    TM_ABORT_NESTED       = 0x02, // aborted due to nested begin
    TM_ABORT_INST         = 0x04, // xabort instruction executed
    TM_ABORT_EXCEPTION    = 0x08, // aborted due to exception occurence
    TM_ABORT_OVERFLOW     = 0x10, // aborted due to cache line overflow
    TM_NOTACTIVE          = 0x20  // no transaction is active
} tmStatusE;

//
// Command values
//
typedef struct cmdArgValuesS {
    struct diagnosticStrS {
        Uns32 level;
    } diagnosticStr;
} cmdArgValues, *cmdArgValuesP;

//
// Diagnostic level check macros
//
#define DIAG_LEVEL(_O)  ((_O)->cmdArgs.diagnosticStr.level)
#define DIAG_LOW        (DIAG_LEVEL(object) > 0)
#define DIAG_MED        (DIAG_LEVEL(object) > 1)
#define DIAG_HIGH       (DIAG_LEVEL(object) > 2)

//
// This represents data added by this extension library
//
typedef struct vmiosObjectS {

    // associated processor
    riscvP           riscv;

    // is this extension enabled?
    Bool             enabled;

    // configuration (including CSR reset values)
    tmConfig         config;

    // TM extension CSR registers info
    tmCSRs           csr;                   // TM extension CSR values
    riscvCSRAttrs    csrs[XCSR_ID(LAST)];   // modified CSR definitions

    // Transaction state info
    memDomainP       physicalMem;           // physical memory domain
    memRegionP       regionCache;           // cached physical memory region
    tmStatusE        tmStatus;              // current TM status
    Uns32            numPending;            // number of lines currently pending
    cacheLine        pending[CACHE_MAX_LINES]; // current transaction cached lines

    // Abort state info
    Uns32            xbeginReg;             // index of xbegin register
    Uns64            abortCode;             // xabort code
    Addr             abortPC;               // PC to jump to on abort
    Uns64            x[RISCV_GPR_NUM];      // GPR bank
    Uns64            f[RISCV_FPR_NUM];      // FPR bank

    // extended instruction decode table
    vmidDecodeTableP decode32;

    // command argument values
    cmdArgValues     cmdArgs;

    // extension callbacks
    riscvExtCB       extCB;

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return name of processor for the extension
//
static const char *getName(vmiosObjectP object) {
    return vmirtProcessorName((vmiProcessorP)object->riscv);
}

//
// Returns true if processor is currently in transactional memory mode
// (OK to use at run-time or morph-time)
//
static Bool getTMode(riscvP riscv) {
    return riscv->cb.getTMode(riscv);
}

//
// Enable or disable transactional memory mode on the processor
// using the model support callback function setTMode.
// (Use this at run-time ONLY)
//
// IMPORTANT NOTE:
//    Any instruction that can change the transactional memory mode (i.e. calls
//    setTMode) MUST include a call to vmimtEndBlock() at MORPH time.
//    (This is already done by the base model for instructions that call the
//    RISCV_TSTORE_FN or RISCV_TLOAD_FN callbacks, so it is OK for those
//    functions to change the mode.)
//
static void setTMode(riscvP riscv, Bool enable) {
    riscv->cb.setTMode(riscv, enable);
}

//
// Return TM configuration
//
static tmConfigCP getExtConfig(riscvP riscv) {
    riscvExtConfigCP cfg = riscv->cb.getExtConfig(riscv, EXTID_TM);
    VMI_ASSERT(cfg, "TM config not found");
    return cfg->userData;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSRS
////////////////////////////////////////////////////////////////////////////////

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //            name    num    arch extension attrs    description         rCB rwCB wCB
    XCSR_ATTR_T__(tm_cfg, 0xFD0, 0,   EXT_TM,   0,0,0,0, "TM Configuration", 0,  0,   0)
};

//
// Validate the presence of one extension
//
#define EXTENSION_CHECK(_OBJ, _REQUIRED, _REG, _FIELD, _EXT) \
    if((_REQUIRED & _EXT) && !RD_XCSR_FIELD(object, _REG, _FIELD)) {    \
        return False;                                                   \
    }

//
// Indicate whether the TM extension is present
//
static Bool extensionPresent(vmiosObjectP object, tmVariant required) {

    // validate TM register presence
    EXTENSION_CHECK(object, required, tm_cfg, tmPresent, EXT_TM);

    return True;
}

//
// Initialize CSR registers
//
static void tmCSRInit(vmiosObjectP object) {

    riscvP   riscv = object->riscv;
    extCSRId id;

    // initialise CSR values that have configuration values defined
    WR_XCSR(object, tm_cfg, object->config.csr.tm_cfg.u64.bits);

    // register each CSR with the base model
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        if(extensionPresent(object, src->extension)) {
            riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF TRANSACTION INSTRUCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Emit debug of cache line
//
static void debugLine(
    vmiosObjectP object,
    cacheLineP   this,
    Uns32        offset,
    Uns32        bytes,
    Bool         dirty
) {
    Uns32 hartid = RD_CSR(object->riscv, mhartid);
    char  mode;
    Uns32 i;

    // show updated section in line if required
    if(bytes) {

        vmiPrintf(PREFIX"%u:           "FMT_Ax" ", hartid, this->PA);

        for(i=0; i<sizeof(this->line); i++) {
            if((i<offset) || (i>=(offset+bytes))) {
                vmiPrintf("..");
            } else if(dirty) {
                vmiPrintf("ww");
            } else {
                vmiPrintf("rr");
            }
        }

        vmiPrintf("\n");
    }

    if(bytes) {
        mode = dirty?'W':'R';
    } else {
        mode = object->tmStatus!=TM_OK ? 'X' : (dirty?'C':' ');
    }

    // show line contents
    vmiPrintf(PREFIX"%u:    LINE %c "FMT_Ax" ", hartid, mode, this->PA);

    for(i=0; i<sizeof(this->line); i++) {
        vmiPrintf("%02x", this->line[i]);
    }

    vmiPrintf("\n");
}

//
// Return line low address
//
inline static Addr getLineLowPA(cacheLineP this) {
    return this->PA;
}

//
// Return line high address
//
inline static Addr getLineHighPA(cacheLineP this) {
    return this->PA + sizeof(this->line) - 1;
}

//
// Forward reference
//
static VMI_MEM_WATCH_FN(memoryConflict);

//
// Install monitors on all cache lines that are used by an active transaction
//
static void installCacheMonitor(vmiosObjectP object) {

    if (object->tmStatus != TM_OK) {

        // ignore if not in transaction or there has already been an abort event

    } else {

        memDomainP domain = object->physicalMem;
        cacheLineP this;
        Uns32      i;

        for(i = 0; i < object->numPending; i++) {

            this = &object->pending[i];

            Addr lo = getLineLowPA(this);
            Addr hi = getLineHighPA(this);

            // register for a callback if any current line is written
            if (!this->writeCallbackInstalled) {
                vmirtAddWriteCallback(domain, 0, lo, hi, memoryConflict, object);
                this->writeCallbackInstalled = True;
            }

            // register for a callback if any dirty line is read
            if(this->dirty && !this->readCallbackInstalled) {
                vmirtAddReadCallback(domain, 0, lo, hi, memoryConflict, object);
                this->readCallbackInstalled = True;
            }
        }
    }
}

//
// Remove any monitors that were added on cache lines
//
static void removeCacheMonitor(vmiosObjectP object) {

    memDomainP domain = object->physicalMem;
    cacheLineP this;
    Uns32      i;

    for(i = 0; i < object->numPending; i++) {

        this = &object->pending[i];

        Addr lo = getLineLowPA(this);
        Addr hi = getLineHighPA(this);

        if (this->writeCallbackInstalled) {
            vmirtRemoveWriteCallback(domain, 0, lo, hi, memoryConflict, object);
            this->writeCallbackInstalled = False;
        }

        if (this->readCallbackInstalled) {
            vmirtRemoveReadCallback(domain, 0, lo, hi, memoryConflict, object);
            this->readCallbackInstalled = False;
        }
    }
}

//
// If this memory access callback is triggered by a real access,
// then flag a memory conflict abort for the transaction
//
static VMI_MEM_WATCH_FN(memoryConflict) {

    if(!processor) {
        // Ignore artifact accesses
    } else {

        vmiosObjectP object = userData;

        if (processor == (vmiProcessorP)object->riscv) {
            // Ignore accesses made by this processor
        } else {

            if (DIAG_LOW) {
                vmiMessage("I", PREFIX"_MC",
                    "%s: Conflict @"FMT_Ax" (PA="FMT_Ax") from processor %s\n",
                    getName(object),
                    VA,
                    address,
                    vmirtProcessorName(processor)
                );
            }

            object->tmStatus |= TM_ABORT_MEM_CONFLICT;

            // No need to continue monitoring
            removeCacheMonitor(object);
        }
    }
}

//
// Notifier called when trap is taken
//
static RISCV_TRAP_NOTIFIER_FN(riscvTrapNotifier) {

    vmiosObjectP object = clientData;

    if(object->tmStatus == TM_NOTACTIVE) {

        // ignore exceptions outside of transactions

    } else {

        if(DIAG_LOW) {
            vmiMessage("I", PREFIX"_MC",
                "%s: Exception occurred during transaction. "
                "Aborting transaction.",
                getName(object)
            );
        }

        // update status to abort transaction
        object->tmStatus |= TM_ABORT_EXCEPTION;

        // clear transaction mode during exception so memory updates will occur
        // normally during exception
        setTMode(object->riscv, False);
    }
}

//
// Notifier called when eret occurs is taken
//
static RISCV_TRAP_NOTIFIER_FN(riscvERETNotifier) {

    vmiosObjectP object = clientData;

    if(object->tmStatus == TM_NOTACTIVE) {

        // ignore exception returns outside of transactions

    } else {

        // issue message if ransaction was started from inside handler
        if(!(object->tmStatus & TM_ABORT_EXCEPTION)) {
            if (DIAG_LOW) {
                vmiMessage("I", PREFIX"_MC",
                    "%s: Exception return occurred during transaction. "
                    "Aborting transaction.",
                    getName(object)
                );
            }
        }

        // update status to abort transaction
        object->tmStatus |= TM_ABORT_EXCEPTION;

        // restore transaction mode after exception so transaction abort will
        // occur on next activity
        setTMode(object->riscv, True);
    }
}

//
// Get cache line containing the given physical address and return
// pointer to data value in that line
//
static Uns8 *getCacheAddress(
    vmiosObjectP object,
    Addr         PA,
    Uns32       *bytes,
    Bool         dirty
) {
    Uns32      offset = PA & (CACHE_LINE_BYTES-1);
    Addr       PAline = PA - offset;
    cacheLineP this   = NULL;
    Uns32      i;

    // Adjust byte count to what fits in this line
    if (*bytes > CACHE_LINE_BYTES - offset) {
        *bytes = CACHE_LINE_BYTES - offset;
    }

    // find any matching line
    for(i = 0; i < object->numPending; i++) {
        if(object->pending[i].PA==PAline) {
            break;
        }
    }

    if (i < object->numPending) {

        // found match - get existing line
        this = &object->pending[i];

    } else if (i >= object->numPending) {

        // get new line
        if (i >= CACHE_MAX_LINES) {

            // no more room - abort transaction
            if (DIAG_LOW) {
                vmiMessage("I", PREFIX"_MC",
                    "%s: Maximum of %d cache lines exceeded. Aborting transaction.\n",
                    getName(object),
                    CACHE_MAX_LINES
                );
            }
            return NULL;

        } else {

            // allocate new entry
            this = &object->pending[object->numPending++];

            // fill new entry
            this->PA                     = PAline;
            this->dirty                  = False;
            this->readCallbackInstalled  = False;
            this->writeCallbackInstalled = False;

            // Initialize line contents.
            // (If we are already in an abort state make the access an
            //  artifact access so we won't cause other transactions to abort.)
            vmirtReadNByteDomain(
                object->physicalMem,
                this->PA,
                this->line,
                sizeof(this->line),
                &object->regionCache,
                object->tmStatus == TM_OK ? MEM_AA_TRUE : MEM_AA_FALSE
            );
        }
    }

    if (dirty && !this->dirty && object->tmStatus == TM_OK) {
        // Do a write of the cached line when it first becomes dirty
        // to trigger callbacks used to detect memory conflicts.
        // Note we are writing back the clean contents of the line, so this
        // will not change the value of the memory. It is only intended
        // to trigger the relevent callbacks.
        vmirtWriteNByteDomain(
            object->physicalMem,
            this->PA,
            this->line,
            sizeof(this->line),
            &object->regionCache,
            MEM_AA_TRUE
        );
    }

    // update dirty state
    this->dirty |= dirty;

    if (DIAG_HIGH) {
        // show line contents before update and hilight updated section
        debugLine(object, this, offset, *bytes, dirty);
    }

    // return address to update
    return &this->line[offset];
}

//
// Called on processor switch to another context
//
static RISCV_IASSWITCH_FN(riscvSwitch) {

    vmiosObjectP object = clientData;

    if (DIAG_HIGH) {
        vmiMessage("I", PREFIX"_AT",
            "%s: switch: %s\n",
            getName(object),
            state==RS_SUSPEND ? "Suspend" : "Run"
        );
    }

    if(state==RS_SUSPEND) {
        installCacheMonitor(object);
    }
}

//
// Commit all live transactions
//
static void xCommit(vmiosObjectP object) {

    cacheLineP this;
    Uns32      i;

    for(i = 0; i < object->numPending; i++) {

        this = &object->pending[i];

        if (DIAG_MED) {
            // debug committed line
            debugLine(object, this, 0, 0, this->dirty);
        }

        // commit results if dirty and not aborting
        if(this->dirty && (object->tmStatus == TM_OK)) {
            vmirtWriteNByteDomain(
                object->physicalMem,
                this->PA,
                this->line,
                sizeof(this->line),
                &object->regionCache,
                MEM_AA_TRUE
            );
        }
    }

    // Remove any monitors currently installed
    removeCacheMonitor(object);

    // Clear pending lines
    object->numPending = 0;
}

//
// Deactivate a transaction
//
static void deactivate(vmiosObjectP object) {

    if (DIAG_LOW) {
        if (object->tmStatus != TM_OK) {
            vmiMessage("I", PREFIX"_AT",
                "%s: Aborted transaction: status=0x%x abort code=0x"FMT_64x"\n",
                getName(object),
                object->tmStatus,
                object->abortCode
            );
        }
    }

    xCommit(object);

    setTMode(object->riscv, False);
    object->tmStatus  = TM_NOTACTIVE;
    object->abortCode = 0;
}

//
// Map virtual address to physical address
//
static Bool mapVAToPA(vmiosObjectP object, Addr VA, Addr *simAddrP) {

    vmiProcessorP processor  = (vmiProcessorP)object->riscv;
    memDomainP    fromDomain = vmirtGetProcessorDataDomain(processor);
    memDomainP    toDomain   = object->physicalMem;
    Bool          ok;

    *simAddrP = VA;
    ok = vmirtMapToDomain(toDomain, fromDomain, simAddrP);

    if(!ok) {
        vmiMessage(
            "E", PREFIX"_UMA",
            "%s: Unable to map address 0x"FMT_Ax" to physical memory\n",
            getName(object),
            VA
        );
    }

    return ok;
}

//
// Save registers when entering transaction mode
//
static void saveRegs(vmiosObjectP object) {

    riscvP riscv = object->riscv;
    Uns32  i;

    for(i=1; i<RISCV_GPR_NUM; i++) {
        object->x[i] = riscv->x[i];
    }
    for(i=0; i<RISCV_FPR_NUM; i++) {
        object->f[i] = riscv->f[i];
    }
}

//
// Restore registers when leaving transaction mode
//
static void restoreRegs(vmiosObjectP object) {

    riscvP riscv = object->riscv;
    Uns32  i;

    for(i=1; i<RISCV_GPR_NUM; i++) {
        riscv->x[i] = object->x[i];
    }
    for(i=0; i<RISCV_FPR_NUM; i++) {
        riscv->f[i] = object->f[i];
    }
}

//
// Set the xbegin register to the given value
//
static void setXbeginReturnValue(vmiosObjectP object, Uns64 value) {

    riscvP riscv  = object->riscv;
    Uns32  regIdx = object->xbeginReg;

    if(regIdx) {
        riscv->x[regIdx] = value;
    }
}

//
// Do an abort
// NOTE: may ONLY be called from a morphed instruction run time call back
//       or a TLoad/TStore callback
//
static void doAbort(vmiosObjectP object) {

    if (object->tmStatus == TM_NOTACTIVE) {

        // Not active so nothing to abort - ignore

    } else {

        vmiProcessorP proc = (vmiProcessorP)object->riscv;

        // restore values of RISCV GPRs
        restoreRegs(object);

        // compute and set return value for xbegin
        Uns64 returnValue = (
            (object->tmStatus  & 0xff) |
            ((object->abortCode & 0xff) << 8)
        );
        setXbeginReturnValue(object, returnValue);

        // clear current transaction
        deactivate(object);

        // set PC of next instruction (to be executed on abort)
        vmirtSetPC(proc, object->abortPC);
    }
}

//
// Called to implement a transactional load
//
static RISCV_TLOAD_FN(riscvTLoad) {

    vmiosObjectP object = clientData;

    if (object->tmStatus != TM_OK) {

        // abort is pending
        doAbort(object);

    } else {

        Uns8  *buffer8 = buffer;
        Addr  PA;
        Uns32 thisBytes;
        Uns32 i;

        while ((thisBytes = bytes) > 0) {

            if(mapVAToPA(object, VA, &PA)) {

                // get pointer to data in cache (loads cache line if required)
                Uns8 *data = getCacheAddress(object, PA, &thisBytes, False);

                if (!data) {

                    object->tmStatus |= TM_ABORT_OVERFLOW;
                    doAbort(object);

                } else {

                    for(i=0; i<thisBytes; i++) {
                        buffer8[i] = data[i];
                    }

                    if (DIAG_MED) {
                        // show result
                        char buf[(thisBytes*2)+1], *b = buf;
                        for(i=0; i<thisBytes; i++) {
                            sprintf(b, "%02x", data[i]);
                            b += 2;
                        }
                        *b = '\0';

                        vmiMessage(
                            "I", PREFIX"_TLD", "%s: TLoad  VA=0x"FMT_Ax" PA=0x"FMT_Ax" bytes=%u data=%s\n",
                            getName(object),
                            VA,
                            PA,
                            thisBytes,
                            buf
                        );
                    }
                }
            }

            // reduce byte count by count of bytes on this line
            bytes -= thisBytes;
            VA    += thisBytes;
        }
    }
}

//
// Called to implement a transactional store
//
static RISCV_TSTORE_FN(riscvTStore) {

    vmiosObjectP object  = clientData;

    if (object->tmStatus != TM_OK) {

        // abort is pending
        doAbort(object);

    } else {

        const Uns8  *buffer8 = buffer;
        Addr         PA;
        Uns32        thisBytes;
        Uns32        i;

        while ((thisBytes = bytes) > 0) {

            if(mapVAToPA(object, VA, &PA)) {

                // get pointer to data in cache (loads cache line if required)
                Uns8 *data = getCacheAddress(object, PA, &thisBytes, True);

                if (!data) {

                    object->tmStatus |= TM_ABORT_OVERFLOW;
                    doAbort(object);

                } else {

                    for(i=0; i<thisBytes; i++) {
                        data[i] = buffer8[i];
                    }

                    if (DIAG_MED) {
                        // show result
                        char buf[(thisBytes*2)+1], *b = buf;
                        for(i=0; i<thisBytes; i++) {
                            sprintf(b, "%02x", data[i]);
                            b += 2;
                        }
                        *b = '\0';

                        vmiMessage(
                            "I", PREFIX"_TST", "%s: TStore VA=0x"FMT_Ax" PA=0x"FMT_Ax" bytes=%u data=%s\n",
                            getName(object),
                            VA,
                            PA,
                            thisBytes,
                            buf
                        );
                    }
                }
            }

            // reduce byte count by count of bytes on this line
            bytes -= thisBytes;
            VA    += thisBytes;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION INSTRUCTION DECODE
////////////////////////////////////////////////////////////////////////////////

//
// This enumerates generic instructions
//
typedef enum riscvExtITypeE {

    // custom instructions
    EXT_IT_XBEGIN,
    EXT_IT_XEND,
    EXT_IT_XABORT,
    EXT_IT_WFE,

    // KEEP LAST: for sizing the array
    EXT_IT_LAST

} riscvExtIType;

//
// This specifies attributes for each 32-bit opcode
//
const static riscvExtInstrAttrs attrsArray32[] = {
    //                                                                          |   dec | rs2 | rs1 |fn3| rd  | dec   |
    EXT_INSTRUCTION(EXT_IT_XBEGIN, "xbegin", RVANY, RVIP_RD_RS1_RS2, FMT_R1,   "|0000000|00000|00000|011|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_XEND,   "xend",   RVANY, RVIP_RD_RS1_RS2, FMT_NONE, "|0000000|00000|00000|010|00000|0001011|"),
    EXT_INSTRUCTION(EXT_IT_XABORT, "xabort", RVANY, RVIP_RD_RS1_RS2, FMT_R1,   "|0000000|00000|00000|100|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_WFE,    "wfe",    RVANY, RVIP_RD_RS1_RS2, FMT_NONE, "|0000000|00000|00000|101|00000|0001011|")
};

//
// Decode instruction at the given address
//
static riscvExtIType decode(
    riscvP             riscv,
    vmiosObjectP       object,
    riscvAddr          thisPC,
    riscvExtInstrInfoP info
) {
    return riscv->cb.fetchInstruction(
        riscv, thisPC, info, &object->decode32, attrsArray32, EXT_IT_LAST, 32
    );
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Runtime implementation of transaction start
//
static void xBegin(vmiosObjectP object, Uns32 regIdx, Uns64 thisPC) {

    if(object->tmStatus != TM_NOTACTIVE) {

        // Nested transactions not supported
        object->tmStatus |= TM_ABORT_NESTED;
        doAbort(object);

    } else {

        // save PC of next instruction (to be executed on abort)
        object->abortPC   = thisPC+4;
        object->abortCode = 0;

        // save xbegin instruction destination register index
        object->xbeginReg = regIdx;

        // save current values of registers for abort, if necessary
        saveRegs(object);

        // start a new transaction
        object->tmStatus = TM_OK;
        setTMode(object->riscv, True);

        // set value in xbegin destination register
        setXbeginReturnValue(object, object->tmStatus);
    }
}

//
// Runtime implementation of transaction end
//
static void xEnd(vmiosObjectP object) {

    if(object->tmStatus != TM_OK) {

        // abort is pending
        doAbort(object);

    } else {

        // end current transaction
        deactivate(object);
    }
}

//
// Runtime implementation of transaction abort
//
static void xAbort(vmiosObjectP object, Uns32 regIdx) {

    // get value from xabort source register
    object->abortCode = object->riscv->x[regIdx];

    // flag that this abort was from an instruction
    object->tmStatus |= TM_ABORT_INST;

    doAbort(object);
}


////////////////////////////////////////////////////////////////////////////////
// BASE MODEL INSTUCTION UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Return riscvRegDesc for the indexed register
//
inline static riscvRegDesc getRVReg(riscvExtMorphStateP state, Uns32 argNum) {
    return state->info.r[argNum];
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION TRANSLATION
////////////////////////////////////////////////////////////////////////////////

//
// Emit code implementing XBEGIN instruction
//
static EXT_MORPH_FN(emitXBEGIN) {

    // get abstract register operands
    riscvRegDesc rd = getRVReg(state, 0);

    // emit call implementing XBEGIN instruction
    vmimtArgNatAddress(state->object);
    vmimtArgUns32(getRIndex(rd));
    vmimtArgSimPC(64);
    vmimtCall((vmiCallFn)xBegin);

    // transaction mode change possible so end this code block
    vmimtEndBlock();
}

//
// Emit code implementing XEND instruction
//
static EXT_MORPH_FN(emitXEND) {

    // XEND instruction is a NOP when not in a transaction
    if(getTMode(state->riscv)) {

        // emit call implementing XEND instruction
        vmimtArgNatAddress(state->object);
        vmimtCall((vmiCallFn)xEnd);

        // transaction mode change possible so end this code block
        vmimtEndBlock();
    }
}

//
// Emit code implementing XABORT instruction
//
static EXT_MORPH_FN(emitXABORT) {

    // XABORT instruction is a NOP when not in a transaction
    if(getTMode(state->riscv)) {

        // get abstract register operands
        riscvRegDesc rs = getRVReg(state, 0);

        // emit call implementing XABORT instruction
        vmimtArgNatAddress(state->object);
        vmimtArgUns32(getRIndex(rs));
        vmimtCall((vmiCallFn)xAbort);

        // transaction mode change possible so end this code block
        vmimtEndBlock();
    }
}

//
// Emit code implementing WFE instruction
//
static EXT_MORPH_FN(emitWFE) {
    vmimtIdle();
}

//
// Dispatch table for instruction translation
//
const static riscvExtMorphAttr dispatchTable[] = {
    [EXT_IT_XBEGIN] = {morph:emitXBEGIN, variant:EXT_TM },
    [EXT_IT_XEND]   = {morph:emitXEND,   variant:EXT_TM },
    [EXT_IT_XABORT] = {morph:emitXABORT, variant:EXT_TM },
    [EXT_IT_WFE]    = {morph:emitWFE,    variant:EXT_WFE},
};

//
// Validate that the instruction is supported and enabled and return a reason
// string if not
//
static const char *getDisableReason(vmiosObjectP object, tmVariant variant) {

    tmVariant   availableVariants = object->config.variant;
    const char *result            = 0;

    // validate feature is present
    if(!object->enabled || ((availableVariants & variant) != variant)) {
        result = "Unimplemented on this variant";
    }

    return result;
}

//
// Instruction translation
//
static VMIOS_MORPH_FN(tmMorph) {

    riscvP             riscv = (riscvP)processor;
    riscvExtMorphState state = {riscv:riscv, object:object};

    // decode instruction
    riscvExtIType type = decode(riscv, object, thisPC, &state.info);

    // action is only required if the instruction is implemented by this
    // extension
    if(type != EXT_IT_LAST) {

        riscvExtMorphAttrCP attrs  = &dispatchTable[type];
        const char         *reason = getDisableReason(object, attrs->variant);

        // fill translation attributes
        state.attrs = attrs;

        // translate instruction
        riscv->cb.morphExternal(&state, reason, opaque);
    }

    // no callback function is required
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION INSTRUCTION DISASSEMBLY
////////////////////////////////////////////////////////////////////////////////

//
// Disassembler, VMI interface
//
static VMIOS_DISASSEMBLE_FN(tmDisassemble) {

    riscvP            riscv  = (riscvP)processor;
    const char       *result = 0;
    riscvExtInstrInfo info;

    // action is only required if the instruction is implemented by this
    // extension
    if(decode(riscv, object, thisPC, &info) != EXT_IT_LAST) {
        result = riscv->cb.disassInstruction(riscv, &info, attrs);
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION
////////////////////////////////////////////////////////////////////////////////

//
// Add documentation for custom instructions
//
static void docCustom(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc,
    Bool        r
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, "Custom0 0001011",   0, 7);
    vmidocAddField(inst, r ? "00000" : "r",   7, 5);
    vmidocAddField(inst, decode,             12, 3);
    vmidocAddField(inst, "00000",            15, 5);
    vmidocAddField(inst, "00000",            20, 5);
    vmidocAddField(inst, "0000000",          25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for Custom instructions
//
static VMIOS_DOC_FN(tmDoc) {

    if (object->enabled) {

        vmiDocNodeP custom = vmidocAddSection(0, "Instruction Extensions");

        // description
        vmidocAddText(
            custom,
            "RISCV processors may add various custom extensions to the basic "
            "RISC-V architecture. This processor has been extended, using an "
            "extension library, to add Transactional Memory instructions to "
            "the Custom0 opcode space."
        );
        vmidocAddText(
            custom,
            "To enable this extension the read-only CSR register \"tm_cfg\" must "
            "be initialized to the value 1."
        );
        vmiDocNodeP insts = vmidocAddSection(custom, "Custom Instructions");

        vmidocAddText(
            insts,
            "This model includes the following custom instructions."
        );

        docCustom(insts, "xend", "010", "end transaction", False);
        vmidocAddText(
            insts,
            "The xend instruction will terminate an active transaction, "
            "committing the cached memory values to memory."
        );
        vmidocAddText(
            insts,
            "If no transaction is currently active the xabort instruction is a "
            "nop."
        );

        docCustom(insts, "xbegin", "011", "begin transaction", True);
        vmidocAddText(
            insts,
            "The value returned in the rd register by the xbegin instruction "
            "will be 0 when the transaction has successfully started."
        );
        vmidocAddText(
            insts,
            "If the transaction subsequently aborts, a jump to the instruction "
            "following the xbegin instruction with the register state of the "
            "processor restored to the values when the xbegin instruction was "
            "executed but with the following bits set in the rd register "
            "indicating the cause(s) for the abort:"
        );
        vmidocAddText(
            insts,
            "Bit 0: a memory conflict occurred with another transaction."
        );
        vmidocAddText(
            insts,
            "Bit 1: another xbegin instruction was executed while this "
            "transaction was active. "
        );
        vmidocAddText(
            insts,
            "Bit 2: an xabort instruction executed during transaction "
            "(See bits 8:15)."
        );
        vmidocAddText(
            insts,
            "Bit 3: an exception or return from exception occurred during the "
            "transaction."
        );
        vmidocAddText(
            insts,
            "Bit 4: TM buffer overflow - too many cache lines needed."
        );
        vmidocAddText(
            insts,
            "Bits 8:15: if bit 2 is set then bits 8:15 = bits 7:0 of value "
            "passed to xabort, otherwise 0."
        );

        docCustom(insts, "xabort", "100", "abort transaction", True);
        vmidocAddText(
            insts,
            "The xabort transaction instruction will cause a current "
            "transaction to abort. The code returned to the aborted xbegin "
            "instruction will have bit 2 set and bits 7:15 of the code will "
            "contain bits 0:7 of the rsrc register specified on the xabort "
            "instruction."
        );
        vmidocAddText(
            insts,
            "If no transaction is currently active the xabort instruction is a "
            "nop."
        );

        docCustom(insts, "wfe", "10", "wait for event hint", True);
        vmidocAddText(
            insts,
            "The wfe instruction is a hint that the processor is waiting for "
            "an external event before it can proceed. In the simulator, this "
            "tells the model to suspend execution until the end of the current "
            "simulated quantum of instructions for this processor. "
            "(This is the equivalent of executing NOP instructions for the "
            "remainder of the quantum, but is more efficient for the "
            "simulator.)"
        );
        vmidocAddText(
            insts,
            "Hardware implementations might put the processor in a low power "
            "mode until an interrupt or other signal occurs."
        );

        vmidocProcessor(processor, custom);
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Parameters
//
typedef struct formalValuesS {
    VMI_UNS32_PARAM(diagnosticlevel);
    VMI_UNS32_PARAM(variant);
} formalValues, *formalValuesP;

//
// Parameter table
//
static vmiParameter parameters[] = {
    VMI_UNS32_PARAM_SPEC(formalValues, diagnosticlevel,       0, 0,       3, "Override the initial diagnostic level"),
    VMI_UNS32_PARAM_SPEC(formalValues, variant,         EXT_ALL, 1, EXT_ALL, "Override the configured variant"),
    { 0 }
};

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(tmParamSpecs) {
    if(!prev) {
        prev = parameters;
    } else {
        prev++;
    }
    return prev->name ? prev : 0;
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(tmParamTableSize) {
    return sizeof(formalValues);
}


////////////////////////////////////////////////////////////////////////////////
// COMMANDS
////////////////////////////////////////////////////////////////////////////////

//
// Command functions
//
VMIOS_COMMAND_PARSE_FN(diagnosticCB) {
    if (DIAG_LOW) {
        vmiMessage(
            "I", CPU_PREFIX, "%s: diagnostic level set to %d",
            getName(object),
            DIAG_LEVEL(object)
        );
    }
    return "";
}

//
// Add commands
//
static void addCommands(vmiosObjectP object, cmdArgValuesP argValues){

    vmiCommandP cmd;

    cmd = vmiosAddCommandParse(
        object,
        "diagnostic",
        "Set how much additional information is reported for the library",
        diagnosticCB,
        VMI_CT_QUERY|VMI_CO_DIAG|VMI_CA_REPORT
    );
    vmirtAddArg(
        cmd,
        "level",
        "Higher numbers print more diagnostic information\n"
        "                                         0 = off (initial)\n"
        "                                         1 = startup and shutdown\n"
        "                                         2 = changes of major modes, infrequent commands\n"
        "                                         3 = full noisy",
        VMI_CA_INT32,
        VMI_CAA_MENU,
        0,
        &(argValues->diagnosticStr.level)
    );
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR AND POST-CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(tmConstructor) {

    riscvP        riscv  = (riscvP)processor;
    formalValuesP params = parameterValues;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // initialize diagnostic setting to value set for parameter
    DIAG_LEVEL(object) = params->diagnosticlevel;

    // add commands
    addCommands(object, &object->cmdArgs);

    // initialize base model callbacks
    object->extCB.switchCB     = riscvSwitch;
    object->extCB.tLoad        = riscvTLoad;
    object->extCB.tStore       = riscvTStore;
    object->extCB.trapNotifier = riscvTrapNotifier;
    object->extCB.ERETNotifier = riscvERETNotifier;

    // register extension with base model
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_TM);

    // set status to not active to start
    object->tmStatus = TM_NOTACTIVE;

    // copy configuration from template
    object->config = *getExtConfig(riscv);

    // override configured variant
    object->config.variant = params->variant;

    // initialize CSRs
    tmCSRInit(object);

    // is extension enabled in config info?
    object->enabled = RD_XCSR_FIELD(object, tm_cfg, tmPresent);
}

//
// Use the post constructor for any activities that query or set processor or
// memory state using the VMI interface, specifically:
// 1. Register access using vmirtRegRead, vmirtRegWrite etc; and
// 2. Memory access using vmirtGetProcessorExternalDataDomain,
//    vmirtReadNByteDomain, vmirtWriteNByteDomain etc.
// Using these functions in the constructor may prevent correct initialization
// when multiple extensions are loaded on a single processor.
//
static VMIOS_POST_CONSTRUCTOR_FN(tmPostConstructor) {

    // record the processor physical memory domain
    object->physicalMem = vmirtGetProcessorExternalDataDomain(processor);
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "transactionalMemory", // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB     = tmConstructor,     // object constructor
    .postConstructorCB = tmPostConstructor, // object post-constructor
    .docCB             = tmDoc,             // documentation constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = tmMorph,               // instruction morph callback
    .disCB         = tmDisassemble,         // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = tmParamSpecs,       // iterate parameter declarations
    .paramValueSizeCB = tmParamTableSize,   // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};

