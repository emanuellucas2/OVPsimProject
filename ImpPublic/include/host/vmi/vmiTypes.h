/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

#pragma once

// basic types
#include "hostapi/impTypes.h"

// common types
#include "ocl/ocliaTypes.h"
#include "ocl/oclcnTypes.h"

// VMI types
#include "vmi/vmiTyperefs.h"

//
// Type of model
//
typedef enum vmiModelTypeE {
    VMI_PROCESSOR_MODEL = 0,
    VMI_INTERCEPT_LIBRARY,
    VMI_MMC_MODEL,
    VMI_MODULE,
    VMI_PERIPHERAL_MODEL,
    VMI_PLATFORM,
    VMI_XML_PLATFORM,
    VMI_INVALID_MODEL,
} vmiModelType;

//
// This type is used to define attributes of an SMP processor in the processor
// constructor (see macro VMI_CONSTRUCTOR_FN)
//
typedef struct vmiSMPContextS {
    Bool  isContainer;  // whether this processor is a container
    Uns32 numChildren;  // if a container, the initial number of children
    Uns32 numSubSlices; // if a container, the number of subslices
    Uns32 index;        // index number in schedule list
} vmiSMPContext, *vmiSMPContextP;

//
// This type is returned by vmirtGetSMPCpuType()
//
typedef enum vmiSMPCpuTypeE {
    SMP_TYPE_CONTAINER = 0x0,   // Container Processor
    SMP_TYPE_LEAF      = 0x1,   // Leaf processor
    SMP_TYPE_GROUP     = 0x2,   // Part of an SMP simulation group

    // simple leaf processor (not a member of an SMP simulation group)
    SMP_SIMPLE_LEAF = SMP_TYPE_LEAF,
    // leaf processor that is a member of an SMP simulation group
    SMP_GROUP_LEAF  = SMP_TYPE_LEAF     | SMP_TYPE_GROUP,
    // simple container processor
    SMP_CONTAINER   = SMP_TYPE_CONTAINER,
    // container processor that contains a group of SMP_GROUP_LEAF processors
    SMP_GROUP       = SMP_TYPE_CONTAINER | SMP_TYPE_GROUP,
} vmiSMPCpuType;

// Is a processor of vmiSMPCpuType _T a leaf processor
#define SMP_IS_LEAF(_T) ((_T) & SMP_TYPE_LEAF)

// Is a processor of vmiSMPCpuType _T an SMP group processor
#define SMP_IS_GROUP(_T) ((_T) & SMP_TYPE_GROUP)

//
// Use to describe activation and deactivation of processor at context switch
//
typedef enum vmiIASRunStateE {
    RS_RUN,         // processor about to be run
    RS_SUSPEND      // processor has just been suspended
} vmiIASRunState;

//
// Used to describe phase when checkpoint/restore is in progress
//
typedef enum vmiSaveRestorePhaseE {
    SRT_BEGIN,      // start save/restore for a processor (or SMP container)
    SRT_BEGIN_CORE, // start save/restore for a single SMP core
    SRT_END_CORE,   // end save/restore for a single SMP core
    SRT_END,        // end save/restore for a processor (or SMP container)
} vmiSaveRestorePhase;

//
// Used to describe status of save/restore operation
//
typedef enum vmiSaveRestoreStatusE {
    SRS_ERROR,      // error in save/restore restore
    SRS_OK,         // successful operation
    SRS_END_LIST    // end of list (vmirtSaveElement/vmirtRestoreElement only)
} vmiSaveRestoreStatus;

//
// Used to control disassembly
//
typedef enum vmiDisassAttrsE {
    DSA_NORMAL   = 0x00000000,  // normal disassembly
    DSA_UNCOOKED = 0x00000001,  // model-specific uncooked format
    DSA_BASE     = 0x00000002,  // use base model disassembly (not intercept)
    DSA_MODEL    = 0x80000000,  // model-specific mask
} vmiDisassAttrs;

//
// This bitmask is used with vmirtRead*/vmirtWrite* functions to describe the
// access characteristics. Valid values are:
//
// MEM_AA_FALSE: indicates that the access is an artifact read/write, which
// should not update processor state.
//
// MEM_AA_TRUE: indicates that the access is a true read/write which may update
// processor state (for example, it may initiate entry to an exception handler
// to handle an illegal address).
//
// MEM_AA_FETCH: indicates that the access is an artifact fetch, which should
// not update processor state.
//
// MEM_AA_TRUE|MEM_AA_FETCH: indicates that the access is a true fetch which may
// update processor state (for example, it may initiate entry to an exception
// handler to handle an illegal address).
//
typedef enum memAccessAttrsE {
    MEM_AA_FALSE = 0x0, // this is an artifact access
    MEM_AA_TRUE  = 0x1, // this is a true processor access
    MEM_AA_FETCH = 0x2, // this access is a fetch
} memAccessAttrs;

//
// Is the memory access a true access?
//
#define MEM_AA_IS_TRUE_ACCESS(_MA) (((_MA) & MEM_AA_TRUE) && True)

//
// Is the memory access an artifact access?
//
#define MEM_AA_IS_ARTIFACT_ACCESS(_MA) (!MEM_AA_IS_TRUE_ACCESS(_MA))

//
// Is the memory access a fetch?
//
#define MEM_AA_IS_FETCH(_MA) (((_MA) & MEM_AA_FETCH) && True)

//
// Deprecated memAccessAttrs value
//
#define MEM_AA_IGNORE_PRIV MEM_AA_TRUE

//
// Macros defining read and write functions used for callback-mapped memory (see
// vmirtMapCallbacks). Note that argument 'isFetch' is deprecated and will be
// removed in future; please use MEM_AA_IS_FETCH(attrs) instead.
//
#define VMI_MEM_READ_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,   \
    Addr           address,     \
    Uns32          bytes,       \
    void          *value,       \
    void          *userData,    \
    Addr           VA,          \
    Bool           isFetch,     \
    memAccessAttrs attrs        \
)
#define VMI_MEM_WRITE_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,   \
    Addr           address,     \
    Uns32          bytes,       \
    const void    *value,       \
    void          *userData,    \
    Addr           VA,          \
    memAccessAttrs attrs        \
)

//
// Prototypes for read and write functions used for callback-mapped memory (see
// vmirtMapCallbacks)
//
typedef VMI_MEM_READ_FN((*vmiMemReadFn));
typedef VMI_MEM_WRITE_FN((*vmiMemWriteFn));

//
// Macro defining read/write notification callback function (see
// vmirtAddReadCallback, vmirtRemoveReadCallback, vmirtAddWriteCallback and
// vmirtRemoveWriteCallback)
//
#define VMI_MEM_WATCH_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          address,      \
    Uns32         bytes,        \
    const void   *value,        \
    void         *userData,     \
    Addr          VA            \
)

//
// Prototype for read/write notification callback function (see
// vmirtAddReadCallback, vmirtRemoveReadCallback, vmirtAddWriteCallback and
// vmirtRemoveWriteCallback)
//
typedef VMI_MEM_WATCH_FN((*vmiMemWatchFn));

//
// Endianness for memory accesses
//
typedef enum memEndianE {
    MEM_ENDIAN_LITTLE = 0,  // little endian
    MEM_ENDIAN_BIG    = 1   // big endian
} memEndian;

//
// Access constraints for memory accesses (bitfield)
//
typedef enum memConstraintE {

    MEM_CONSTRAINT_NONE    = 0x0, // no constraint
    MEM_CONSTRAINT_ALIGNED = 0x1, // access must not be misaligned
    MEM_CONSTRAINT_USER1   = 0x2, // no access when privilege is MEM_PRIV_USER1
    MEM_CONSTRAINT_USER2   = 0x4, // no access when privilege is MEM_PRIV_USER2

    // legacy alias
    MEM_CONSTRAINT_NO_DEVICE = MEM_CONSTRAINT_USER1

} memConstraint;

//
// Type of preload
//
typedef enum memPreloadTypeE {
    MEM_PLT_LOAD,       // preload for likely load
    MEM_PLT_STORE,      // preload for likely store
    MEM_PLT_FETCH,      // preload for likely execute
} memPreloadType;

//
// Load/store mask action
//
typedef enum memLSMActionE {
    MEM_LSM_NONE = 0,   // no action
    MEM_LSM_0    = 1,   // fill masked section of the address with 0
    MEM_LSM_1    = 2    // fill masked section of the address with 1
} memLSMAction;

//
// Structure for management of MRU state on memory access
//
typedef struct memMRUSetS {
    const Uns32 *nextState;     // LUT giving next state from current state
    Uns32       *currentState;  // reference to current state
} memMRUSet;

//
// This defines memory that should use physically-mapped code dictionaries
//
#define MEM_MAP_PHYSICAL ((memMRUSetP)-1)

//
// This defines endianness of the host
//
#define MEM_ENDIAN_NATIVE MEM_ENDIAN_LITTLE

//
// Memory type
//
typedef enum memTypeE {
    MEM_ROM =1,         // read only memory
    MEM_RAM =2,         // read/write memory
} memType;

//
// Memory access privilege (bitmask)
//
typedef enum memPrivE {

    // access privilege options
    MEM_PRIV_NONE    = 0x00,    // no access permitted
    MEM_PRIV_R       = 0x01,    // read permitted
    MEM_PRIV_W       = 0x02,    // write permitted
    MEM_PRIV_X       = 0x04,    // execute permitted

    // other access constraints
    MEM_PRIV_ALIGN_R = 0x08,    // read alignment checks always enabled
    MEM_PRIV_ALIGN_W = 0x10,    // write alignment checks always enabled
    MEM_PRIV_USER1   = 0x20,    // user-defined restricted access
    MEM_PRIV_USER2   = 0x40,    // user-defined restricted access

    // user-defined access aliases
    MEM_PRIV_USER    = (MEM_PRIV_USER1|MEM_PRIV_USER2),
    MEM_PRIV_DEVICE  = MEM_PRIV_USER1,

    // compound privileges
    MEM_PRIV_RW      = (MEM_PRIV_R|MEM_PRIV_W           ),
    MEM_PRIV_RX      = (MEM_PRIV_R|           MEM_PRIV_X),
    MEM_PRIV_WX      = (           MEM_PRIV_W|MEM_PRIV_X),
    MEM_PRIV_RWX     = (MEM_PRIV_R|MEM_PRIV_W|MEM_PRIV_X),

    // compound access constraints
    MEM_PRIV_ALIGN   = (MEM_PRIV_ALIGN_R|MEM_PRIV_ALIGN_W)

} memPriv;

//
// Enumeration describing how addresses in a memory range are mapped
//
typedef enum memMappedE {
    MEM_MAP_NONE = 0,   // no addresses in the range mapped
    MEM_MAP_PART = 1,   // some addresses in the range mapped
    MEM_MAP_FULL = 2,   // all addresses in the range mapped
} memMapped;

//
// Enumeration describing whether a simulated address is ASID-mapped and, if so,
// whether that mapping is active in the simulator
//
typedef enum memMappedASIDE {
    ASID_MAP_NONE,      // address not ASID-mapped
    ASID_MAP_INACTIVE,  // address ASID-mapped but not active
    ASID_MAP_ACTIVE     // address ASID-mapped and active
} memMappedASID;

//
// How privilege mask is to be applied
//
typedef enum memPrivActionE {
    MEM_PRIV_SET,       // set privileges using mask
    MEM_PRIV_ADD,       // add privileges using mask
    MEM_PRIV_SUB        // remove privileges using mask
} memPrivAction;

//
// Macro to construct suitable return value for read and write alignment snap
// handlers when address snapping and/or value rotation are required. Parameter
// _SNAP indicates address alignment in bytes (typically 1, 2, 4 or 8) and
// parameter _ROTATE indicates rotation in bits.
//
#define MEM_SNAP(_SNAP, _ROTATE) (((Uns8)(_SNAP)) | ((_ROTATE)<<8))

//
// Enumeration of unary operation types
//
typedef enum vmiUnopE {
                                    // MOVE OPERATIONS
    vmi_MOV       = OCL_UN_MOV,     // d <- a
    vmi_SWP       = OCL_UN_SWP,     // d <- byteswap(a)

                                    // ARITHMETIC OPERATIONS
    vmi_NEG       = OCL_UN_NEG,     // d <- -a
    vmi_ABS       = OCL_UN_ABS,     // d <- (a<0) ? -a : a

                                    // SATURATED ARITHMETIC OPERATIONS
    vmi_NEGSQ     = OCL_UN_NEGSQ,   // d <- saturate_signed(-a)
    vmi_ABSSQ     = OCL_UN_ABSSQ,   // d <- (a<0) ? saturate_signed(-a) : a

                                    // BITWISE OPERATIONS
    vmi_NOT       = OCL_UN_NOT,     // d <- ~a
    vmi_RBIT      = OCL_UN_RBIT,    // d <- bit_reverse(a)

                                    // MISCELLANEOUS OPERATIONS
    vmi_CNTZ      = OCL_UN_CNTZ,    // d <- count_zeros(a)
    vmi_CNTO      = OCL_UN_CNTO,    // d <- count_ones(a)
    vmi_CLS       = OCL_UN_CLS,     // d <- count_leading_sign(a)
    vmi_CLZ       = OCL_UN_CLZ,     // d <- count_leading_zeros(a)
    vmi_CLO       = OCL_UN_CLO,     // d <- count_leading_ones(a)
    vmi_CTZ       = OCL_UN_CTZ,     // d <- count_trailing_zeros(a)
    vmi_CTO       = OCL_UN_CTO,     // d <- count_trailing_ones(a)
    vmi_BSFZ      = OCL_UN_BSFZ,    // d <- least_significant_zero_index(a)
    vmi_BSFO      = OCL_UN_BSFO,    // d <- least_significant_one_index(a)
    vmi_BSRZ      = OCL_UN_BSRZ,    // d <- most_significant_zero_index(a)
    vmi_BSRO      = OCL_UN_BSRO,    // d <- most_significant_one_index(a)

                                    // AES ENCRYPTION OPERATIONS
    vmi_AESMC     = OCL_UN_AESMC,   // d <- AES_mix_columns(a)
    vmi_AESIMC    = OCL_UN_AESIMC,  // d <- AES_inverse_mix_columns(a)

    vmi_UNOP_LAST = OCL_UN_LAST     // KEEP LAST

} vmiUnop;

//
// Enumeration of binary integral operation types
//
typedef enum vmiBinopE {
                                        // ARITHMETIC OPERATIONS
    vmi_ADD        = OCL_BIN_ADD,       // d <- a + b
    vmi_ADC        = OCL_BIN_ADC,       // d <- a + b + C
    vmi_SUB        = OCL_BIN_SUB,       // d <- a - b
    vmi_SBB        = OCL_BIN_SBB,       // d <- a - b - C
    vmi_RSBB       = OCL_BIN_RSBB,      // d <- b - a - C
    vmi_RSUB       = OCL_BIN_RSUB,      // d <- b - a
    vmi_IMUL       = OCL_BIN_IMUL,      // d <- a * b (signed)
    vmi_MUL        = OCL_BIN_MUL,       // d <- a * b (unsigned)
    vmi_IDIV       = OCL_BIN_IDIV,      // d <- a / b (signed)
    vmi_DIV        = OCL_BIN_DIV,       // d <- a / b (unsigned)
    vmi_IREM       = OCL_BIN_IREM,      // d <- a % b (signed)
    vmi_REM        = OCL_BIN_REM,       // d <- a % b (unsigned)
    vmi_CMP        = OCL_BIN_CMP,       // a - b

                                        // SATURATED ARITHMETIC OPERATIONS
    vmi_ADDSQ      = OCL_BIN_ADDSQ,     // d <- saturate_signed(a + b)
    vmi_ADCSQ      = OCL_BIN_ADCSQ,     // d <- saturate_signed(a + b + C)
    vmi_SUBSQ      = OCL_BIN_SUBSQ,     // d <- saturate_signed(a - b)
    vmi_SBBSQ      = OCL_BIN_SBBSQ,     // d <- saturate_signed(a - b - C)
    vmi_RSUBSQ     = OCL_BIN_RSUBSQ,    // d <- saturate_signed(b - a)
    vmi_RSBBSQ     = OCL_BIN_RSBBSQ,    // d <- saturate_signed(b - a - C)
    vmi_ADDUQ      = OCL_BIN_ADDUQ,     // d <- saturate_unsigned(a + b)
    vmi_ADCUQ      = OCL_BIN_ADCUQ,     // d <- saturate_unsigned(a + b + C)
    vmi_SUBUQ      = OCL_BIN_SUBUQ,     // d <- saturate_unsigned(a - b)
    vmi_SBBUQ      = OCL_BIN_SBBUQ,     // d <- saturate_unsigned(a - b - C)
    vmi_RSUBUQ     = OCL_BIN_RSUBUQ,    // d <- saturate_unsigned(b - a)
    vmi_RSBBUQ     = OCL_BIN_RSBBUQ,    // d <- saturate_unsigned(b - a - C)

                                        // HALVING ARITHMETIC OPERATIONS
    vmi_ADDSH      = OCL_BIN_ADDSH,     // d <- ((signed)(a + b)) / 2
    vmi_SUBSH      = OCL_BIN_SUBSH,     // d <- ((signed)(a - b)) / 2
    vmi_RSUBSH     = OCL_BIN_RSUBSH,    // d <- ((signed)(b - a)) / 2
    vmi_ADDUH      = OCL_BIN_ADDUH,     // d <- ((unsigned)(a + b)) / 2
    vmi_SUBUH      = OCL_BIN_SUBUH,     // d <- ((unsigned)(a - b)) / 2
    vmi_RSUBUH     = OCL_BIN_RSUBUH,    // d <- ((unsigned)(b - a)) / 2
    vmi_ADDSHR     = OCL_BIN_ADDSHR,    // d <- round(((signed)(a + b)) / 2)
    vmi_SUBSHR     = OCL_BIN_SUBSHR,    // d <- round(((signed)(a - b)) / 2)
    vmi_RSUBSHR    = OCL_BIN_RSUBSHR,   // d <- round(((signed)(b - a)) / 2)
    vmi_ADDUHR     = OCL_BIN_ADDUHR,    // d <- round(((unsigned)(a + b)) / 2)
    vmi_SUBUHR     = OCL_BIN_SUBUHR,    // d <- round(((unsigned)(a - b)) / 2)
    vmi_RSUBUHR    = OCL_BIN_RSUBUHR,   // d <- round(((unsigned)(b - a)) / 2)

                                        // BITWISE OPERATIONS
    vmi_OR         = OCL_BIN_OR,        // d <- a | b
    vmi_AND        = OCL_BIN_AND,       // d <- a & b
    vmi_XOR        = OCL_BIN_XOR,       // d <- a ^ b
    vmi_ORN        = OCL_BIN_ORN,       // d <- a | ~b
    vmi_ANDN       = OCL_BIN_ANDN,      // d <- a & ~b
    vmi_XORN       = OCL_BIN_XORN,      // d <- a ^ ~b
    vmi_NOR        = OCL_BIN_NOR,       // d <- ~(a | b)
    vmi_NAND       = OCL_BIN_NAND,      // d <- ~(a & b)
    vmi_XNOR       = OCL_BIN_XNOR,      // d <- ~(a ^ b)

                                        // SHIFT/ROTATE OPERATIONS
    vmi_ROL        = OCL_BIN_ROL,       // d <- a << b | a >> <bits>-b
    vmi_ROR        = OCL_BIN_ROR,       // d <- a >> b | a << <bits>-b
    vmi_RCL        = OCL_BIN_RCL,       // (d,c) <- (a,c) << b | (a,c) >> <bits>-b
    vmi_RCR        = OCL_BIN_RCR,       // (d,c) <- (a,c) >> b | (a,c) << <bits>-b
    vmi_SHL        = OCL_BIN_SHL,       // d <- a << b
    vmi_SHR        = OCL_BIN_SHR,       // d <- (unsigned)a >> b
    vmi_SAR        = OCL_BIN_SAR,       // d <- (signed)a >> b

                                        // SATURATED SHIFT OPERATIONS
    vmi_SHLSQ      = OCL_BIN_SHLSQ,     // d <- saturate_signed(a << b)
    vmi_SHLUQ      = OCL_BIN_SHLUQ,     // d <- saturate_unsigned(a << b)

                                        // ROUNDING SHIFT OPERATIONS
    vmi_SHRR       = OCL_BIN_SHRR,      // d <- round((unsigned)a >> b)
    vmi_SARR       = OCL_BIN_SARR,      // d <- round((signed)a >> b)

                                        // MIN/MAX OPERATIONS
    vmi_IMIN       = OCL_BIN_IMIN,      // d <- min_signed(a, b)
    vmi_MIN        = OCL_BIN_MIN,       // d <- min_unsigned(a, b)
    vmi_IMAX       = OCL_BIN_IMAX,      // d <- max_signed(a, b)
    vmi_MAX        = OCL_BIN_MAX,       // d <- max_unsigned(a, b)

                                        // WIDENING ARITHMETIC OPERATIONS
    vmi_IMULSU     = OCL_BIN_IMULSU,    // d <- a (signed) * b (unsigned)
    vmi_IMULUS     = OCL_BIN_IMULUS,    // d <- a (unsigned) * b (signed)

                                        // POLYNOMIAL ARITHMETIC OPERATIONS
    vmi_PMUL       = OCL_BIN_PMUL,      // d <- a * b (carryless)

                                        // AES ENCRYPTION OPERATIONS
    vmi_AESENC1    = OCL_BIN_AESENC1,   // d <- AES_encrypt1(a), not last round
    vmi_AESENC1L   = OCL_BIN_AESENC1L,  // d <- AES_encrypt1(a), last round
    vmi_AESDEC1    = OCL_BIN_AESDEC1,   // d <- AES_decrypt1(a), not last round
    vmi_AESDEC1L   = OCL_BIN_AESDEC1L,  // d <- AES_decrypt1(a), last round
    vmi_AESENC2    = OCL_BIN_AESENC2,   // d <- AES_encrypt2(a), not last round
    vmi_AESENC2L   = OCL_BIN_AESENC2L,  // d <- AES_encrypt2(a), last round
    vmi_AESDEC2    = OCL_BIN_AESDEC2,   // d <- AES_decrypt2(a), not last round
    vmi_AESDEC2L   = OCL_BIN_AESDEC2L,  // d <- AES_decrypt2(a), last round

    vmi_BINOP_LAST = OCL_BIN_LAST       // KEEP LAST

} vmiBinop;

//
// Enumeration of bit operation types
//
typedef enum vmiBitopE {
    vmi_BT         = OCL_BIT_BT,        // bit test
    vmi_BTR        = OCL_BIT_BTR,       // bit test and reset
    vmi_BTS        = OCL_BIT_BTS,       // bit test and set
    vmi_BTC        = OCL_BIT_BTC,       // bit test and complement
    vmi_BITOP_LAST = OCL_BIT_LAST,      // KEEP LAST
} vmiBitop;

//
// Enumeration of condition types
//
typedef enum vmiConditionE {
    vmi_COND_O   = 0,   // overflow                         (OF==1)
    vmi_COND_NO  = 1,   // no overflow                      (OF==0)
    vmi_COND_B   = 2,   // below (unsigned)                 (CF==1)
    vmi_COND_C   = 2,   // carry (alias of below)           (CF==1)
    vmi_COND_NB  = 3,   // not below (unsigned)             (CF==0)
    vmi_COND_NC  = 3,   // no carry (alias of not below)    (CF==0)
    vmi_COND_Z   = 4,   // zero                             (ZF==1)
    vmi_COND_EQ  = 4,   // equal (alias of zero)            (ZF==1)
    vmi_COND_NZ  = 5,   // not zero                         (ZF==0)
    vmi_COND_NE  = 5,   // not equal (alias of not zero)    (ZF==0)
    vmi_COND_BE  = 6,   // below or equal (unsigned)        (CF==1 || ZF==1)
    vmi_COND_NBE = 7,   // not below or equal (unsigned)    (CF==0 && ZF==0)
    vmi_COND_S   = 8,   // negative                         (SF==1)
    vmi_COND_NS  = 9,   // not negative                     (SF==0)
    vmi_COND_P   = 10,  // parity even                      (PF==1)
    vmi_COND_NP  = 11,  // not parity even                  (PF==0)
    vmi_COND_L   = 12,  // less (signed)                    (SF!=OF)
    vmi_COND_NL  = 13,  // not less (signed)                (SF==OF)
    vmi_COND_LE  = 14,  // less or equal (signed)           (ZF==1 || SF!=OF)
    vmi_COND_NLE = 15   // not less or equal (signed)       (ZF==0 && SF==OF)
} vmiCondition;

//
// Enumeration of count check required for vmimtZeroRV and vmimtMoveRRV
// operations
//
typedef enum vmiCheckCountE {
    vmi_CC_NONE,        // no count check required
    vmi_CC_EQ_ZERO,     // count check for zero required
    vmi_CC_LE_ZERO,     // count check for zero or negative required
} vmiCheckCount;

//
// Hint for jump types (call/return pairing and relative jump indication)
//
typedef enum vmiJumpHintE {

    vmi_JH_NONE      = OCL_JH_NONE,                 // no jump hint

    vmi_JH_CALL      = OCL_JH_CALL,                 // call
    vmi_JH_RETURN    = OCL_JH_RETURN,               // return
    vmi_JH_INT       = OCL_JH_INT,                  // interrupt
    vmi_JH_CALLINT   = vmi_JH_INT|vmi_JH_CALL,      // interrupt call
    vmi_JH_RETURNINT = vmi_JH_INT|vmi_JH_RETURN,    // interrupt return

    vmi_JH_RELATIVE  = OCL_JH_RELATIVE              // target is relative

} vmiJumpHint;

//
// Enumeration of unary floating point operation types
//
typedef enum vmiFUnopE {
                    // BASIC ARITHMETIC OPERATIONS
    vmi_FMOV,       // d <- a
    vmi_FABS,       // d <- abs(a), signalling
    vmi_FQABS,      // d <- abs(a), IEEE 754-2008 (clear sign bit only)
    vmi_FNEG,       // d <- -a,     signalling
    vmi_FQNEG,      // d <- -a,     IEEE 754-2008 (toggle sign bit only)
    vmi_FRECIP,     // d <- 1/a
    vmi_FSQRT,      // d <- sqrt(a)
    vmi_FRSQRT,     // d <- 1/sqrt(a)

                    // ROUNDING OPERATIONS
    vmi_FCEIL,      // d <- roundTowardsPositiveInfinity(a)
    vmi_FFLOOR,     // d <- roundTowardsNegativeInfinity(a)
    vmi_FNEAREST,   // d <- roundToNearest(a)
    vmi_FTRUNC,     // d <- roundTowardsZero(a)
    vmi_FROUNDC,    // d <- roundUsingCurrentRoundingMode(a)
    vmi_FAWAY,      // d <- roundToNearestTiesToAway(a)

                    // TRIGONOMETRIC OPERATIONS
    vmi_FSIN,       // d <- sin(a)
    vmi_FCOS,       // d <- cos(a)

                    // LOGARITHMIC OPERATIONS
    vmi_FLOG2,      // d <- log2(a)

                    // USER-DEFINED OPERATIONS
    vmi_FUNUD,      // (implemented with result handler functions)

    vmi_FUNOP_LAST  // KEEP LAST

} vmiFUnop;

//
// Enumeration of binary floating point operation types
//
typedef enum vmiFBinopE {
                    // BASIC ARITHMETIC OPERATIONS
    vmi_FADD,       // d <- a + b
    vmi_FSUB,       // d <- a - b
    vmi_FMUL,       // d <- a * b
    vmi_FDIV,       // d <- a / b

                    // MIN/MAX OPERATIONS
    vmi_FMIN,       // d <- min(a, b)
    vmi_FMAX,       // d <- max(a, b)

                    // SCALE OPERATIONS
    vmi_FSCALEF,    // d <- a * 2^b (floating point b)
    vmi_FSCALEI,    // d <- a * 2^b (integer b)

                    // QUIET COMPARISON OPERATIONS
    vmi_FQCMPEQ,    // d <-  (a == b)     ? all_ones : all_zeros
    vmi_FQCMPNEQ,   // d <- !(a == b)     ? all_ones : all_zeros
    vmi_FQCMPLT,    // d <-  (a <  b)     ? all_ones : all_zeros
    vmi_FQCMPNLT,   // d <- !(a <  b)     ? all_ones : all_zeros
    vmi_FQCMPLE,    // d <-  (a <= b)     ? all_ones : all_zeros
    vmi_FQCMPNLE,   // d <- !(a <= b)     ? all_ones : all_zeros
    vmi_FQCMPGT,    // d <-  (a >  b)     ? all_ones : all_zeros
    vmi_FQCMPNGT,   // d <- !(a >  b)     ? all_ones : all_zeros
    vmi_FQCMPGE,    // d <-  (a >= b)     ? all_ones : all_zeros
    vmi_FQCMPNGE,   // d <- !(a >= b)     ? all_ones : all_zeros
    vmi_FQCMPOR,    // d <-  ordered(a,b) ? all_ones : all_zeros
    vmi_FQCMPNOR,   // d <- !ordered(a,b) ? all_ones : all_zeros

                    // SIGNALLING COMPARISON OPERATIONS
    vmi_FSCMPEQ,    // d <-  (a == b)     ? all_ones : all_zeros
    vmi_FSCMPNEQ,   // d <- !(a == b)     ? all_ones : all_zeros
    vmi_FSCMPLT,    // d <-  (a <  b)     ? all_ones : all_zeros
    vmi_FSCMPNLT,   // d <- !(a <  b)     ? all_ones : all_zeros
    vmi_FSCMPLE,    // d <-  (a <= b)     ? all_ones : all_zeros
    vmi_FSCMPNLE,   // d <- !(a <= b)     ? all_ones : all_zeros
    vmi_FSCMPGT,    // d <-  (a >  b)     ? all_ones : all_zeros
    vmi_FSCMPNGT,   // d <- !(a >  b)     ? all_ones : all_zeros
    vmi_FSCMPGE,    // d <-  (a >= b)     ? all_ones : all_zeros
    vmi_FSCMPNGE,   // d <- !(a >= b)     ? all_ones : all_zeros
    vmi_FSCMPOR,    // d <-  ordered(a,b) ? all_ones : all_zeros
    vmi_FSCMPNOR,   // d <- !ordered(a,b) ? all_ones : all_zeros

                    // USER-DEFINED OPERATIONS
    vmi_FBINUD,     // (implemented with result handler functions)

    vmi_FBINOP_LAST // KEEP LAST

} vmiFBinop;

//
// Enumeration of ternary floating point operation types
//
typedef enum vmiFTernopE {
                    // UNFUSED OPERATION            FUSED OPERATION
    vmi_FMADD,      // d <- (a * b) + c             d <- ( a * b) + c
    vmi_FMSUB,      // d <- (a * b) - c             d <- ( a * b) - c
    vmi_FNMADD,     // d <- -((a * b) + c)          d <- (-a * b) - c
    vmi_FNMSUB,     // d <- -((a * b) - c)          d <- (-a * b) + c
    vmi_FMSUBR,     // d <- c - (a * b)             d <- (-a * b) + c
    vmi_FMADDH,     // d <- ((a * b) + c) / 2.0     d <- (( a * b) + c) / 2.0
    vmi_FMSUBH,     // d <- ((a * b) - c) / 2.0     d <- (( a * b) - c) / 2.0
    vmi_FMSUBRH,    // d <- (c - (a * b)) / 2.0     d <- ((-a * b) + c) / 2.0

                    // USER-DEFINED OPERATIONS
    vmi_FTERNUD,    // (implemented with result handler functions)

    vmi_FTERNOP_LAST// KEEP LAST

} vmiFTernop;

//
// Enumeration of floating point relations (bitmask)
//
typedef enum vmiFPRelationE {
    vmi_FPRL_UNORDERED = 0x1,   // unordered
    vmi_FPRL_EQUAL     = 0x2,   // equal
    vmi_FPRL_LESS      = 0x4,   // less than
    vmi_FPRL_GREATER   = 0x8    // greater than
} vmiFPRelation;

//
// These values are used to define types for floating point operations
//
#define VMI_FT_BITS     0x0ff8
#define VMI_FT_TYPE     0xf000
#define VMI_FT_IEEE_754 0x1000
#define VMI_FT_X87      0x2000
#define VMI_FT_INT      0x3000
#define VMI_FT_UNS      0x4000
#define VMI_FT_OP1      0x0001

//
// Enumeration of floating point argument types
//
typedef enum vmiFTypeE {

    // these values specify that evaluation should be performed using IEEE 754
    // semantics (intermediates are the same type)
    vmi_FT_16_IEEE_754 = 16 | VMI_FT_IEEE_754,  // 16-bit floating point
    vmi_FT_32_IEEE_754 = 32 | VMI_FT_IEEE_754,  // 32-bit floating point
    vmi_FT_64_IEEE_754 = 64 | VMI_FT_IEEE_754,  // 64-bit floating point

    // these values specify that evaluation should be performed using Intel x87
    // semantics (intermediates are promoted to 80-bit long double format)
    vmi_FT_32_X87      = 32 | VMI_FT_X87,       // 32-bit floating point
    vmi_FT_64_X87      = 64 | VMI_FT_X87,       // 64-bit floating point
    vmi_FT_80_X87      = 80 | VMI_FT_X87,       // 80-bit floating point

    // these values are valid in conversion operations only
    vmi_FT_8_INT       =  8 | VMI_FT_INT,       // 8-bit signed integer
    vmi_FT_16_INT      = 16 | VMI_FT_INT,       // 16-bit signed integer
    vmi_FT_32_INT      = 32 | VMI_FT_INT,       // 32-bit signed integer
    vmi_FT_64_INT      = 64 | VMI_FT_INT,       // 64-bit signed integer
    vmi_FT_8_UNS       =  8 | VMI_FT_UNS,       // 8-bit unsigned integer
    vmi_FT_16_UNS      = 16 | VMI_FT_UNS,       // 16-bit unsigned integer
    vmi_FT_32_UNS      = 32 | VMI_FT_UNS,       // 32-bit unsigned integer
    vmi_FT_64_UNS      = 64 | VMI_FT_UNS,       // 64-bit unsigned integer

    // this value specifies BFLOAT16 type, which is vmi_FT_32_IEEE_754 with
    // fraction truncated to 7 bits, giving a storage size of 16 bits
    vmi_FT_BFLOAT16    = 16 | VMI_FT_IEEE_754 | VMI_FT_OP1,

} vmiFType;

//
// Given a floating point type, return the size of that in bits
//
#define VMI_FTYPE_BITS(_T) ((_T) & VMI_FT_BITS)

//
// Given a floating point type, return the size of that in bits
//
#define VMI_FTYPE_TYPE(_T) ((_T) & VMI_FT_TYPE)

//
// Predicates for floating point type extraction
//
#define VMI_FTYPE_IS_IEEE_754(_T)   (VMI_FTYPE_TYPE(_T) == VMI_FT_IEEE_754)
#define VMI_FTYPE_IS_X87(_T)        (VMI_FTYPE_TYPE(_T) == VMI_FT_X87)
#define VMI_FTYPE_IS_INT(_T)        (VMI_FTYPE_TYPE(_T) == VMI_FT_INT)
#define VMI_FTYPE_IS_UNS(_T)        (VMI_FTYPE_TYPE(_T) == VMI_FT_UNS)

//
// Enumeration describing floating point rounding control
//
typedef enum vmiFPRCE {

    // these values are valid in both conversion functions and in the rounding
    // control field of vmiFPControlWord, below
    vmi_FPR_NEAREST = 0,    // round towards nearest (even)
    vmi_FPR_NEG_INF = 1,    // round towards negative infinity
    vmi_FPR_POS_INF = 2,    // round towards positive infinity
    vmi_FPR_ZERO    = 3,    // round towards zero
    vmi_FPR_AWAY    = 4,    // round towards nearest, tie away
    vmi_FPR_ODD     = 5,    // round to odd (Von Neumann rounding)

    // these values are valid in conversion functions only
    vmi_FPR_CURRENT = 6,    // use currently-active rounding control
    vmi_FPR_USER    = 0x10  // bitmask implying user-defined (implemented with
                            // result handler functions)
} vmiFPRC;

//
// Structure defining floating point control word - used with
// vmirtGetFPControlWord and vmirtSetFPControlWord
//
typedef struct vmiFPControlWordS {

                        // INTERRUPT MASKS
    Uns32   IM    : 1;  // invalid operation mask
    Uns32   DM    : 1;  // denormal mask
    Uns32   ZM    : 1;  // divide-by-zero mask
    Uns32   OM    : 1;  // overflow mask
    Uns32   UM    : 1;  // underflow mask
    Uns32   PM    : 1;  // precision mask
    Uns32   UD1M  : 1;  // user-defined flag 1 mask
    Uns32   UD2M  : 1;  // user-defined flag 2 mask

                        // ROUNDING AND PRECISION
    Uns32   RC    : 3;  // rounding control
    Uns32   FZ    : 1;  // flush to zero
    Uns32   DAZ   : 1;  // denormals are zeros flag

                        // HALF-PRECISION
    Uns32   AHP   : 1;  // use ARM AHP format
    Uns32   FZ16  : 1;  // flush to zero
    Uns32   DAZ16 : 1;  // denormals-are-zeros flag

} vmiFPControlWord;

//
// Structure defining floating point flags for the last floating point operation
//
typedef union vmiFPFlagsU {
    Uns8 bits;      // all flags
    struct {
        Uns32 I   : 1;  // invalid operation flag
        Uns32 D   : 1;  // denormal flag
        Uns32 Z   : 1;  // divide-by-zero flag
        Uns32 O   : 1;  // overflow flag
        Uns32 U   : 1;  // underflow flag
        Uns32 P   : 1;  // precision flag
        Uns32 UD1 : 1;  // user-defined flag 1
        Uns32 UD2 : 1;  // user-defined flag 2
    } f;
} vmiFPFlags;

//
// This can be used to decompose an Flt16 value
//
typedef struct Flt16PartsS {
    Uns32 fraction : 10;
    Uns32 exponent :  5;
    Bool  sign     :  1;
} Flt16Parts;

//
// This can be used to decompose an Flt32 value
//
typedef struct Flt32PartsS {
    Uns32 fraction : 23;
    Uns32 exponent :  8;
    Bool  sign     :  1;
} Flt32Parts;

//
// This can be used to decompose an Flt64 value
//
typedef struct Flt64PartsS {
    Uns64 fraction : 52;
    Uns32 exponent : 11;
    Bool  sign     :  1;
} Flt64Parts;

//
// This can be used to decompose an Flt80 value
//
typedef struct Flt80PartsS {
    Uns64 fraction : 64;
    Uns32 exponent : 15;
    Bool  sign     :  1;
} Flt80Parts;

//
// Structure used to hold argument values for floating point result handlers
//
#define VMI_FP_80_BYTES 10
typedef struct vmiFPArgS {
    vmiFType type;
    union {
        // use these for 8-bit types
        Uns8       u8;
        Int8       i8;
        // use these for 16-bit types
        Uns16      u16;
        Int16      i16;
        Flt16Parts f16Parts;
        // use these for 32-bit types
        Uns32      u32;
        Int32      i32;
        Flt32      f32;
        Flt32Parts f32Parts;
        // use these for 64-bit types
        Uns64      u64;
        Int64      i64;
        Flt64      f64;
        Flt64Parts f64Parts;
        // use these for 80-bit types
        Flt80      f80;
        Flt80Parts f80Parts;
        Uns8       bytes[VMI_FP_80_BYTES];
    };
} vmiFPArg;

//
// Union of a floating point value and its byte pattern
//
typedef union vmiFP80ArgU {
    Flt80      f80;
    Flt80Parts f80Parts;
    Uns8       bytes[VMI_FP_80_BYTES];
} vmiFP80Arg;

//
// This function defines a 16-bit QNaN result callback, called when a native
// floating point operation generates a 16-bit QNaN result. Arguments are:
// 1. The processor.
// 2. The 16-bit QNaN result from the operation.
// 3. A count of the number of NaN arguments to the native operation.
// 4. An ordered array of the NaN argument values.
// 5. A count of the total number of arguments to the native operation.
// 6. An ordered array of all argument values.
// It should return a 16-bit QNaN result value result based on these arguments.
//
#define VMI_FP_QNAN16_RESULT_FN(_NAME) Uns16 _NAME( \
    vmiProcessorP processor,    \
    Uns16         QNaN16,       \
    Uns32         NaNArgNum,    \
    vmiFPArgP     NaNArgs,      \
    Uns32         allArgNum,    \
    vmiFPArgP     allArgs       \
)
typedef VMI_FP_QNAN16_RESULT_FN((*vmiFPQNaN16ResultFn));

//
// This function defines a 32-bit QNaN result callback, called when a native
// floating point operation generates a 32-bit QNaN result. Arguments are:
// 1. The processor.
// 2. The 32-bit QNaN result from the operation.
// 3. A count of the number of NaN arguments to the native operation.
// 4. An ordered array of the NaN argument values.
// 5. A count of the total number of arguments to the native operation.
// 6. An ordered array of all argument values.
// It should return a 32-bit QNaN result value result based on these arguments.
//
#define VMI_FP_QNAN32_RESULT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    Uns32         QNaN32,       \
    Uns32         NaNArgNum,    \
    vmiFPArgP     NaNArgs,      \
    Uns32         allArgNum,    \
    vmiFPArgP     allArgs       \
)
typedef VMI_FP_QNAN32_RESULT_FN((*vmiFPQNaN32ResultFn));

//
// This function defines a 64-bit QNaN result callback, called when a native
// floating point operation generates a 64-bit QNaN result. Arguments are:
// 1. The processor.
// 2. The 64-bit QNaN result from the operation.
// 3. A count of the number of NaN arguments to the native operation.
// 4. An ordered array of the NaN argument values.
// 5. A count of the total number of arguments to the native operation.
// 6. An ordered array of all argument values.
// It should return a 64-bit QNaN result value result based on these arguments.
//
#define VMI_FP_QNAN64_RESULT_FN(_NAME) Uns64 _NAME( \
    vmiProcessorP processor,    \
    Uns64         QNaN64,       \
    Uns32         NaNArgNum,    \
    vmiFPArgP     NaNArgs,      \
    Uns32         allArgNum,    \
    vmiFPArgP     allArgs       \
)
typedef VMI_FP_QNAN64_RESULT_FN((*vmiFPQNaN64ResultFn));

//
// This function defines a 8-bit indeterminate result callback, called when a
// native floating point operation generates a 8-bit indeterminate result (as
// the result of a conversion operation). Argument 'value' holds the source
// operand value for which conversion failed. The function should return an
// Uns8 indeterminate result.
//
#define VMI_FP_IND8_RESULT_FN(_NAME) Uns8 _NAME( \
    vmiProcessorP processor,    \
    vmiFPArg      value,        \
    Bool          isSigned      \
)
typedef VMI_FP_IND8_RESULT_FN((*vmiFPInd8ResultFn));

//
// This function defines a 16-bit indeterminate result callback, called when a
// native floating point operation generates a 16-bit indeterminate result (as
// the result of a conversion operation). Argument 'value' holds the source
// operand value for which conversion failed. The function should return an
// Uns16 indeterminate result.
//
#define VMI_FP_IND16_RESULT_FN(_NAME) Uns16 _NAME( \
    vmiProcessorP processor,    \
    vmiFPArg      value,        \
    Bool          isSigned      \
)
typedef VMI_FP_IND16_RESULT_FN((*vmiFPInd16ResultFn));

//
// This function defines a 32-bit indeterminate result callback, called when a
// native floating point operation generates a 32-bit indeterminate result (as
// the result of a conversion operation). Argument 'value' holds the source
// operand value for which conversion failed. The function should return an
// Uns32 indeterminate result.
//
#define VMI_FP_IND32_RESULT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    vmiFPArg      value,        \
    Bool          isSigned      \
)
typedef VMI_FP_IND32_RESULT_FN((*vmiFPInd32ResultFn));

//
// This function defines a 64-bit indeterminate result callback, called when a
// native floating point operation generates a 64-bit indeterminate result (as
// the result of a conversion operation). Argument 'value' holds the source
// operand value for which conversion failed. The function should return an
// Uns64 indeterminate result.
//
#define VMI_FP_IND64_RESULT_FN(_NAME) Uns64 _NAME( \
    vmiProcessorP processor,    \
    vmiFPArg      value,        \
    Bool          isSigned      \
)
typedef VMI_FP_IND64_RESULT_FN((*vmiFPInd64ResultFn));

//
// This function defines a tiny result handler. The argument and the return
// value are unions holding the result value as an Flt80 type, Argument
// 'bits' indicates the required result size (16, 32 or 64). Argument
// 'isIntermediate' is True if the result is an intermediate result in a
// multiply-add operation and False otherwise. Argument 'setFlags' is a pointer
// to a flag structure which can be used to signal additional flags raised as a
// result of handling the tiny result.
//
#define VMI_FP_TINY_RESULT_FN(_NAME) vmiFP80Arg _NAME( \
    vmiProcessorP processor,        \
    vmiFP80Arg    value,            \
    Uns32         bits,             \
    Bool          isIntermediate,   \
    vmiFPFlagsP   setFlags          \
)
typedef VMI_FP_TINY_RESULT_FN((*vmiFPTinyResultFn));

//
// This function defines a tiny argument handler. The argument and the return
// value are unions holding the argument value as an Flt80 type.
//
#define VMI_FP_TINY_ARGUMENT_FN(_NAME) vmiFP80Arg _NAME( \
    vmiProcessorP processor,        \
    vmiFP80Arg    value,            \
    vmiFPFlagsP   setFlags          \
)
typedef VMI_FP_TINY_ARGUMENT_FN((*vmiFPTinyArgumentFn));

//
// This function defines a 8-bit general result callback, called after
// execution of a floating point operation generating a 8-bit floating point
// result. Arguments are:
// 1. The processor.
// 2. The operation result, as a 8-bit unsigned.
// 3. A count of the number of arguments to the operation.
// 4. An ordered array of all argument values.
// 5. A flag structure which can be used to signal additional flags raised.
// The function should return the final operation result and modify any flag
// settings as required.
//
#define VMI_FP_8_RESULT_FN(_NAME) Uns8 _NAME( \
    vmiProcessorP processor,    \
    Uns8          result8,      \
    Uns32         argNum,       \
    vmiFPArgP     args,         \
    vmiFPFlagsP   setFlags      \
)
typedef VMI_FP_8_RESULT_FN((*vmiFP8ResultFn));

//
// This function defines a 16-bit general result callback, called after
// execution of a floating point operation generating a 16-bit floating point
// result. Arguments are:
// 1. The processor.
// 2. The operation result, as a 16-bit unsigned.
// 3. A count of the number of arguments to the operation.
// 4. An ordered array of all argument values.
// 5. A flag structure which can be used to signal additional flags raised.
// The function should return the final operation result and modify any flag
// settings as required.
//
#define VMI_FP_16_RESULT_FN(_NAME) Uns16 _NAME( \
    vmiProcessorP processor,    \
    Uns16         result16,     \
    Uns32         argNum,       \
    vmiFPArgP     args,         \
    vmiFPFlagsP   setFlags      \
)
typedef VMI_FP_16_RESULT_FN((*vmiFP16ResultFn));

//
// This function defines a 32-bit general result callback, called after
// execution of a floating point operation generating a 32-bit floating point
// result. Arguments are:
// 1. The processor.
// 2. The operation result, as a 32-bit unsigned.
// 3. A count of the number of arguments to the operation.
// 4. An ordered array of all argument values.
// 5. A flag structure which can be used to signal additional flags raised.
// The function should return the final operation result and modify any flag
// settings as required.
//
#define VMI_FP_32_RESULT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    Uns32         result32,     \
    Uns32         argNum,       \
    vmiFPArgP     args,         \
    vmiFPFlagsP   setFlags      \
)
typedef VMI_FP_32_RESULT_FN((*vmiFP32ResultFn));

//
// This function defines a 64-bit general result callback, called after
// execution of a floating point operation generating a 64-bit floating point
// result. Arguments are:
// 1. The processor.
// 2. The operation result, as a 64-bit unsigned.
// 3. A count of the number of arguments to the operation.
// 4. An ordered array of all argument values.
// 5. A flag structure which can be used to signal additional flags raised.
// The function should return the final operation result and modify any flag
// settings as required.
//
#define VMI_FP_64_RESULT_FN(_NAME) Uns64 _NAME( \
    vmiProcessorP processor,    \
    Uns64         result64,     \
    Uns32         argNum,       \
    vmiFPArgP     args,         \
    vmiFPFlagsP   setFlags      \
)
typedef VMI_FP_64_RESULT_FN((*vmiFP64ResultFn));

//
// Enumeration describing how a floating point exception was handled
//
typedef enum vmiFloatExceptionResultE {
    VMI_FLOAT_UNHANDLED,        // not handled
    VMI_FLOAT_CONTINUE,         // handled, continue execution
} vmiFloatExceptionResult;

//
// Callback for floating point arithmetic exception handler
// Return value indicates how the exception was handled
//
#define VMI_FP_ARITH_EXCEPT_FN(_NAME) vmiFloatExceptionResult _NAME( \
    vmiProcessorP processor,    \
    vmiFPFlagsP   flags         \
)
typedef VMI_FP_ARITH_EXCEPT_FN((*vmiFPArithExceptFn));

//
// This type allows the effective values of certain flags in the MXCSR to be
// forced to either 0 or 1 if required
//
typedef enum vmiFPFlagForceE {
    vmi_FF_None,    // no force (use value in vmiFPControlWord)
    vmi_FF_0,       // force to 0 (ignore value in vmiFPControlWord)
    vmi_FF_1,       // force to 1 (ignore value in vmiFPControlWord)
} vmiFPFlagForce;

//
// This structure defines a floating point unit configuration. A configuration
// may be specified globally using vmirtConfigureFPU, or per-instruction using
// the final argument to VMI morph-time functions. If both a global
// configuration and a per-instruction configuration are specified, the
// per-instruction configuration takes precedence. Fields are as follows:
//
// QNaN16
// ------
// Default 16-bit QNaN (note that this defines the sense of the "quiet" bit in
// 16-bit QNaN/SNaN values.
//
// QNaN32
// ------
// Default 32-bit QNaN (note that this defines the sense of the "quiet" bit in
// 32-bit QNaN/SNaN values.
//
// QNaN64
// ------
// Default 64-bit QNaN (note that this defines the sense of the "quiet" bit in
// 64-bit QNaN/SNaN values.
//
// indeterminateUns8
// ------------------
// Default 8-bit integer/unsigned indeterminate value. See also field
// indeterminate8ResultCB.
//
// indeterminateUns16
// ------------------
// Default 16-bit integer/unsigned indeterminate value. See also field
// indeterminate16ResultCB.
//
// indeterminateUns32
// ------------------
// Default 32-bit integer/unsigned indeterminate value. See also field
// indeterminate32ResultCB.
//
// indeterminateUns64
// ------------------
// Default 64-bit integer/unsigned indeterminate value. See also field
// indeterminate64ResultCB.
//
// QNaN16ResultCB
// --------------
// If non-NULL, this function is called whenever a 16-bit QNaN result is
// generated by a floating point operation. It gives the model the opportunity
// to adjust the returned QNaN.
//
// QNaN32ResultCB
// --------------
// If non-NULL, this function is called whenever a 32-bit QNaN result is
// generated by a floating point operation. It gives the model the opportunity
// to adjust the returned QNaN.
//
// QNaN64ResultCB
// --------------
// If non-NULL, this function is called whenever a 64-bit QNaN result is
// generated by a floating point operation. It gives the model the opportunity
// to adjust the returned QNaN.
//
// indeterminate8ResultCB
// -----------------------
// If non-NULL, this function is called whenever a 8-bit integer/unsigned
// indeterminate result is generated by a floating point operation. It gives the
// model the opportunity to adjust the returned value.
//
// indeterminate16ResultCB
// -----------------------
// If non-NULL, this function is called whenever a 16-bit integer/unsigned
// indeterminate result is generated by a floating point operation. It gives the
// model the opportunity to adjust the returned value.
//
// indeterminate32ResultCB
// -----------------------
// If non-NULL, this function is called whenever a 32-bit integer/unsigned
// indeterminate result is generated by a floating point operation. It gives the
// model the opportunity to adjust the returned value.
//
// indeterminate64ResultCB
// -----------------------
// If non-NULL, this function is called whenever a 64-bit integer/unsigned
// indeterminate result is generated by a floating point operation. It gives the
// model the opportunity to adjust the returned value.
//
// tinyResultCB
// ------------
// If non-NULL, this function is called whenever a denormal result is generated
// and flush-to-zero mode (FZ mode) is active. It gives the model the
// opportunity to modify processor state when flush-to-zero occurs.
//
// tinyArgumentCB
// --------------
// If non-NULL, this function is called whenever a denormal argument is used
// as input to a floating-point operation. It gives the model the opportunity to
// modify processor state accordingly.
//
// fp8ResultCB
// ------------
// If non-NULL, this function is called whenever a 8-bit result is generated.
// It gives the model the opportunity to adjust the operation result and any
// flags. This callback will normally be specified for per-instruction
// configurations only.
//
// fp16ResultCB
// ------------
// If non-NULL, this function is called whenever a 16-bit result is generated.
// It gives the model the opportunity to adjust the operation result and any
// flags. This callback will normally be specified for per-instruction
// configurations only.
//
// fp32ResultCB
// ------------
// If non-NULL, this function is called whenever a 32-bit result is generated.
// It gives the model the opportunity to adjust the operation result and any
// flags. This callback will normally be specified for per-instruction
// configurations only.
//
// fp64ResultCB
// ------------
// If non-NULL, this function is called whenever a 64-bit result is generated.
// It gives the model the opportunity to adjust the operation result and any
// flags. This callback will normally be specified for per-instruction
// configurations only.
//
// fpArithExceptCB
// ---------------
// This specifies a floating-point exception handler function, called when
// enabled exceptions are detected and before results are committed.
//
// suppressFlags
// -------------
// This specifies a mask of floating point flags that are suppressed by
// operations using this configuration. Note that suppressing the Denormal
// Operand flag improves floating point operation efficiency, especially for
// SIMD operations.
//
// stickyFlags
// -----------
// This specifies whether flags generated by this operation are sticky. Sticky
// flags are combined with existing floating point flags using bitwise-OR
// without this having to be encoded specially in the model.
//
// fzClearsPF
// ----------
// This boolean specifies whether a flush-to-zero clears the precision flag.
// By default, flush-to-zero sets the precision flag.
//
// tininessBeforeRounding
// ----------------------
// This boolean specifies that detection of tiny numbers should be performed
// before rounding (if True) or after rounding (if False). It applies only to
// operations using IEEE 754 semantics; when Intel x87 semantics are used, it is
// ignored.
//
// perElementFlags
// ---------------
// If non-zero, this value specifies that the register indicating floating point
// operation flags is actually an array. The first member is the overall flag
// result (sticky or non-sticky) in the normal way. This flag is then followed
// by one more flag for each parallel operation (so one more flag for a non-SIMD
// operation or 'num' more flags for a SIMD operation). These flags are
// non-sticky and are assigned the operation flags for each parallel operation.
// If 'perElementFlags' is 1, the parallel operation flags are only valid in
// a simulated exception context (i.e., a call to fpArithExceptCB). If
// 'perElementFlags' is 2, the parallel operation flags are valid after every
// operation.
//
// forceAHP, forceFZ16, forceDAZ16
// -------------------------------
// These fields allow the effective value of the AHP, FZ16 and DAZ16 bits in the
// MXCSR to be ignored and instead treated as either 0 or 1
//
typedef struct vmiFPConfigS {
    Uns16               QNaN16;
    Uns32               QNaN32;
    Uns64               QNaN64;
    Uns8                indeterminateUns8;
    Uns16               indeterminateUns16;
    Uns32               indeterminateUns32;
    Uns64               indeterminateUns64;
    vmiFPQNaN16ResultFn QNaN16ResultCB;
    vmiFPQNaN32ResultFn QNaN32ResultCB;
    vmiFPQNaN64ResultFn QNaN64ResultCB;
    vmiFPInd8ResultFn   indeterminate8ResultCB;
    vmiFPInd16ResultFn  indeterminate16ResultCB;
    vmiFPInd32ResultFn  indeterminate32ResultCB;
    vmiFPInd64ResultFn  indeterminate64ResultCB;
    vmiFPTinyResultFn   tinyResultCB;
    vmiFPTinyArgumentFn tinyArgumentCB;
    vmiFP8ResultFn      fp8ResultCB;
    vmiFP16ResultFn     fp16ResultCB;
    vmiFP32ResultFn     fp32ResultCB;
    vmiFP64ResultFn     fp64ResultCB;
    vmiFPArithExceptFn  fpArithExceptCB;
    vmiFPFlags          suppressFlags;
    Bool                stickyFlags;
    Bool                fzClearsPF;
    Bool                tininessBeforeRounding;
    Uns8                perElementFlags;
    vmiFPFlagForce      forceAHP   : 2;
    vmiFPFlagForce      forceFZ16  : 2;
    vmiFPFlagForce      forceDAZ16 : 2;
} vmiFPConfig;

//
// This type defines a post-delay-slot function, called just before a delay slot
// branch or jump is taken
//
#define VMI_POST_SLOT_FN(_NAME) void _NAME(vmiProcessorP processor)
typedef VMI_POST_SLOT_FN((*vmiPostSlotFn));

//
// This type is used to define argument types for vmimtArgReg
//
typedef enum vmiRegArgTypeE {

    VPRRAT_8     =  8,              // 8-bit register argument
    VPRRAT_16    =  16,             // 16-bit register argument
    VPRRAT_32    =  32,             // 32-bit register argument
    VPRRAT_64    =  64,             // 64-bit register argument

    VPRRAT_FLT   = 0x80000000,      // floating-point argument identifier
    VPRRAT_FLT32 = 32|VPRRAT_FLT,   // 32-bit floating point
    VPRRAT_FLT64 = 64|VPRRAT_FLT    // 64-bit floating point

} vmiRegArgType;

//
// This type is used to define argument usage for vmimtArgRegP
//
typedef enum vmiRegPArgUsageE {
    VPRAU_R  = 0x1,                     // argument is read
    VPRAU_W  = 0x2,                     // argument is written
    VPRAU_RW = (VPRAU_R|VPRAU_W),       // argument is read and written
} vmiRegPArgUsage;

//
// This bitmask type is used to define attributes of a called function, enabling
// the JIT code generator to create better code in some cases and allowing
// handling of Flt64 results. Values are as follows:
//
// VMCA_NA
// -------
// No optimization assumptions can be made about the function - it could use
// or modify any state in the system. If in doubt, use this value.
//
// VMCA_PURE
// ---------
// The function is a pure function that operates only on the arguments passed
// to it using vmimtArg* functions and returns a result, but otherwise updates
// no state. The function can therefore be optimized using full data flow
// analysis. Pure functions must return a result which is assigned to a
// processor register using vmimtCallResultAttrs.
//
// VMCA_EXCEPTION
// --------------
// The function causes a simulated exception to be immediately taken so does
// not return (within the function, there is a call to a function such as
// vmirtSetPCException). Operations following the call can be safely eliminated
// by data flow analysis because they are unreachable.
//
// VMCA_NO_INVALIDATE
// ------------------
// This function cannot cause the current code block to be invalidated. This
// typically means that it does not call virtual memory manipulation functions
// (for example, vmirtAliasMemory) or any other functions that could flush
// processor code dictionaries (for example, vmirtFlushDict).
//
// VMCA_FP_RESTORE
// ---------------
// The called function uses floating point operations, so restore environment
// floating point state if required (avoids having to call vmirtRestoreFPState
// from the called function itself)
//
// VMCA_FLT32_RESULT
// -----------------
// The called function produces a result of type Flt32.
//
// VMCA_FLT64_RESULT
// -----------------
// The called function produces a result of type Flt64.
//
// VMCA_PURE and VMCA_EXCEPTION options are exclusive.
//
typedef enum vmiCallAttrsE {
    VMCA_NA            = 0x00,  // no attributes
    VMCA_PURE          = 0x01,  // this call is to a pure function
    VMCA_EXCEPTION     = 0x02,  // this call causes a simulated exception
    VMCA_NO_INVALIDATE = 0x04,  // this call cannot invalidate this block
    VMCA_FP_RESTORE    = 0x08,  // restore floating point state before call
    VMCA_FLT32_RESULT  = 0x10,  // function result is of type Flt32
    VMCA_FLT64_RESULT  = 0x20,  // function result is of type Flt64
} vmiCallAttrs;

//
// Callback function from morphed code
//
typedef void (*vmiCallFn)(void);

//
// Register description
//
typedef enum vmiRegTypeE {
    VRT_NOREG      = OCL_RT_NOREG,     // no register
    VRT_NORMAL     = OCL_RT_NORMAL,    // normal register
    VRT_FUNCRESULT = OCL_RT_FUNCRESULT // register holding function result
} vmiRegType;

//
// Register state
//
typedef enum vmiRegStateE {
    VRS_LIVE      = OCL_RS_LIVE,       // register is live
    VRS_WRITEBACK = OCL_RS_WRITEBACK,  // register must be written back
    VRS_KILL      = OCL_RS_KILL        // register can be killed
} vmiRegState;

//
// Processor register representation
//
typedef struct vmiRegS {
    IntPS index;
    struct {
        Uns32       iKey    :  4;
        Uns32       wKey    :  4;
        vmiRegType  type    :  2;
        vmiRegState state   :  2;
        Bool        temp    :  1;
        Bool        address :  1;
        Bool        address2:  1;
        Bool        wb      :  1;
        Uns32       iBytes  : 16;
    } attrs;
} vmiReg, *vmiRegP;

//
// Macro for filling vmiReg structure
//
#define VMI_REG_FILL(_INDEX, _TEMP, _ADDRESS, _TYPE) { \
    .index = _INDEX,            \
    .attrs = {                  \
        .iKey     = 0,          \
        .wKey     = 0,          \
        .type     = _TYPE,      \
        .state    = 0,          \
        .temp     = _TEMP,      \
        .address  = _ADDRESS,   \
        .address2 = 0,          \
        .wb       = 0,          \
        .iBytes   = 0           \
    }                           \
}

//
// Get properties of vmiReg
//
#define VMI_REG_INDEX(_R)       ((_R).index)
#define VMI_REG_ATTRS(_R)       ((_R).attrs)
#define VMI_REG_IKEY(_R)        (VMI_REG_ATTRS(_R).iKey)
#define VMI_REG_WKEY(_R)        (VMI_REG_ATTRS(_R).wKey)
#define VMI_REG_TYPE(_R)        (VMI_REG_ATTRS(_R).type)
#define VMI_REG_STATE(_R)       (VMI_REG_ATTRS(_R).state)
#define VMI_REG_TEMP(_R)        (VMI_REG_ATTRS(_R).temp)
#define VMI_REG_ADDRESS(_R)     (VMI_REG_ATTRS(_R).address)
#define VMI_REG_ADDRESS2(_R)    (VMI_REG_ATTRS(_R).address2)
#define VMI_REG_WB(_R)          (VMI_REG_ATTRS(_R).wb)
#define VMI_REG_IBYTES(_R)      (VMI_REG_ATTRS(_R).iBytes)

//
// Define for a normal register for VMI operations
//
#define VMI_REG_CONST(_I)       VMI_REG_FILL(_I, 0, 0, VRT_NORMAL)
#define VMI_REG(_I)             ((vmiReg)VMI_REG_CONST(_I))

//
// Define for an instruction-local temporary for VMI operations
//
#define VMI_TEMP_CONST(_I)      VMI_REG_FILL(_I, 1, 0, VRT_NORMAL)
#define VMI_TEMP(_I)            ((vmiReg)VMI_TEMP_CONST(_I))
#define VMI_ISTEMP(_R)          VMI_REG_TEMP(_R)

//
// Define for no register for VMI operations
//
#define VMI_NOREG_CONST         VMI_REG_FILL(0, 0, 0, VRT_NOREG)
#define VMI_NOREG               ((vmiReg)VMI_NOREG_CONST)
#define VMI_ISNOREG(_R)         (VMI_REG_TYPE(_R)!=VRT_NORMAL)

//
// This register code can be used to indicate the result of the previous
// embedded function call as the source argument of vmimtMoveRR
//
#define VMI_FUNCRESULT_CONST    VMI_REG_FILL(0, 0, 0, VRT_FUNCRESULT)
#define VMI_FUNCRESULT          ((vmiReg)VMI_FUNCRESULT_CONST)
#define VMI_ISFUNCRESULT(_R)    (VMI_REG_TYPE(_R)==VRT_FUNCRESULT)

//
// Macros converting from field in CPU to equivalent vmiReg structure
//
#define VMI_CPU_OFFSET(_TP, _F) \
    ((IntPS)((UChar *)(&(((_TP)0)->_F))))
#define VMI_CPU_REG(_TP, _F) \
    VMI_REG(VMI_CPU_OFFSET(_TP, _F))
#define VMI_CPU_REG_CONST(_TP, _F) \
    VMI_REG_CONST(VMI_CPU_OFFSET(_TP, _F))
#define VMI_CPU_TEMP(_TP, _F) \
    VMI_TEMP(VMI_CPU_OFFSET(_TP, _F))
#define VMI_CPU_TEMP_CONST(_TP, _F) \
    VMI_TEMP_CONST(VMI_CPU_OFFSET(_TP, _F))

//
// Macros converting from field in CPU to equivalent vmiReg structure with a
// further constant delta offset
//
#define VMI_CPU_OFFSET_DELTA(_TP, _F, _D) \
    ((IntPS)((UChar *)(&(((_TP)0)->_F)))+(_D))
#define VMI_CPU_REG_CONST_DELTA(_TP, _F, _D) \
    VMI_REG_CONST(VMI_CPU_OFFSET_DELTA(_TP, _F, _D))
#define VMI_CPU_REG_DELTA(_TP, _F, _D) \
    VMI_REG(VMI_CPU_OFFSET_DELTA(_TP, _F, _D))

//
// Generate a new vmiReg using an offset from the passed one
//
vmiReg vmimtRegDelta(vmiReg r, IntPS delta);
#define VMI_REG_DELTA(_R, _D) vmimtRegDelta(_R, _D)

//
// Are registers equal?
//
#define VMI_REG_EQUAL(_R1, _R2) ( \
    (VMI_REG_TYPE(_R1)==VMI_REG_TYPE(_R2)) &&   \
    (VMI_REG_IKEY(_R1)==VMI_REG_IKEY(_R2)) &&   \
    (VMI_REG_INDEX(_R1)==VMI_REG_INDEX(_R2))    \
)

//
// Flag identifiers for get & set of processor flags
//
typedef enum vmiFlagE {
    vmi_CF=0,           // carry flag
    vmi_PF=1,           // parity flag
    vmi_ZF=2,           // zero flag
    vmi_SF=3,           // sign flag
    vmi_OF=4,           // overflow flag
    vmi_LF=5            // KEEP LAST
} vmiFlag;

//
// Bitmask indicating whether particular flags should be negated
//
typedef enum vmiFlagNegateE {
    vmi_FN_NONE  =0x00, // empty negate mask
    vmi_FN_CF_IN =0x01, // negate carry in flag
    vmi_FN_CF_OUT=0x02, // negate carry out flag
    vmi_FN_PF    =0x04, // negate parity flag
    vmi_FN_ZF    =0x08, // negate zero flag
    vmi_FN_SF    =0x10, // negate sign flag
    vmi_FN_OF    =0x20, // negate overflow flag
} vmiFlagNegate;

//
// Processor flag-related structures
//
typedef struct vmiFlagsS {
    vmiReg        cin;          // register specifying carry in
    vmiReg        f[vmi_LF];    // registers to hold operation results
    vmiFlagNegate negate;       // bitmask of negated flags
} vmiFlags;

//
// Define for no no flags for VMI operations
//
#define VMI_NOFLAG       VMI_NOREG
#define VMI_NOFLAG_CONST VMI_NOREG_CONST

//
// Empty flag set
//
#define VMI_NOFLAGS {                   \
    VMI_NOFLAG_CONST,                   \
    {                                   \
        [vmi_CF] = VMI_NOFLAG_CONST,    \
        [vmi_PF] = VMI_NOFLAG_CONST,    \
        [vmi_ZF] = VMI_NOFLAG_CONST,    \
        [vmi_SF] = VMI_NOFLAG_CONST,    \
        [vmi_OF] = VMI_NOFLAG_CONST     \
    },                                  \
    vmi_FN_NONE                         \
}

//
// Callback function invoked by change of state on a net
//
#define VMI_NET_CHANGE_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    void         *userData,     \
    Uns64         newValue      \
)
typedef VMI_NET_CHANGE_FN((*vmiNetChangeFn));

//
// Callback function invoked by change of state on a connection object on which
// this processor is blocked. This function should restart the processor using
// vmirtRestartNow() or vmirtRestartNext() if required
//
#define VMI_CONN_UPDATE_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    void         *userData      \
)
typedef VMI_CONN_UPDATE_FN((*vmiConnUpdateFn));

//
// This structure is filled with information about a connection object by
// query functions (alias of common type)
//
typedef octcnConnInfo  vmiConnInfo;
typedef octcnConnInfoP vmiConnInfoP;

//
// vmimmcPort object is used to describe interconnections between MMC components
//
typedef struct vmimmcPortS {
    const char      *name;         // port name
    vmimmcComponentP component;    // associated component
} vmimmcPort;

//
// Enumeration describing action performed by fetch exception handler
//
typedef enum vmiFetchActionE {
    VMI_FETCH_NONE               = 0,
    VMI_FETCH_EXCEPTION_COMPLETE = 1,
    VMI_FETCH_EXCEPTION_PENDING  = 2
} vmiFetchAction;

//
// Enumeration describing action performed by load/store exception handler
//
typedef enum vmiLoadStoreActionE {
    VMI_LOAD_STORE_TERMINATE = 0,   // terminate the current load/store
    VMI_LOAD_STORE_CONTINUE  = 1    // continue the current load/store
} vmiLoadStoreAction;

//
// Enumeration describing subclass of integer exception (for integer exception
// handler)
//
typedef enum vmiIntegerExceptionTypeE {
    VMI_INTEGER_DIVIDE_BY_ZERO, // integer divide by zero
    VMI_INTEGER_OVERFLOW        // integer overflow
} vmiIntegerExceptionType;

//
// Enumeration describing how an integer exception was handled
//
typedef enum vmiIntegerExceptionResultE {
    VMI_INTEGER_UNHANDLED,      // not handled
    VMI_INTEGER_ABORT,          // handled, abort current instruction
    VMI_INTEGER_CONTINUE,       // handled, continue current instruction
} vmiIntegerExceptionResult;

//
// Deprecated vmiIntegerExceptionResult aliases
//
#define VMI_NUMERIC_UNHANDLED VMI_INTEGER_UNHANDLED
#define VMI_NUMERIC_ABORT     VMI_INTEGER_ABORT
#define VMI_NUMERIC_CONTINUE  VMI_INTEGER_CONTINUE

//
// This type is used to pass information about a divide/remainder operation that
// causes a divide-by-zero or integer overflow
//
typedef struct vmiDivideInfoS {
    Uns8  bits;         // bit size of operation (8, 16 ,32 or 64)
    Bool  isSigned;     // whether division is signed
    Uns64 dividendLSW;  // least-significant part of dividend
    Uns64 dividendMSW;  // most-significant part of dividend
    Uns64 divisor;      // divisor
} vmiDivideInfo;

//
// This type is used to give default results for a divide/remainder operation
// that causes a divide-by-zero or integer overflow
//
typedef struct vmiDivideResultS {
    Uns64 quotient;     // fill this with quotient
    Uns64 remainder;    // fill this with remainder
} vmiDivideResult;

//
// Enumeration describing exception context
//
typedef enum vmiExceptionContextE {
    VMI_EXCEPT_CXT_CODE = 0,    // in morphed code segment
    VMI_EXCEPT_CXT_CALL = 1     // in function called from morphed code
} vmiExceptionContext;

//
// Function type of a function called when a register changes value
//
#define VMI_REG_VALUE_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    vmiRegInfoCP  reg,          \
    Addr          simPC,        \
    void         *oldValue,     \
    void         *newValue,     \
    void         *userData      \
)
typedef VMI_REG_VALUE_FN((*vmiRegValueFn));

//
// Intercept notifier is called whenever an opaque function intercept is called
// (even if the intercept is handled by a different intercept library) - useful
// when writing analysis tools such as profilers which need to be aware of such
// intercepts since they will be followed by an immediate "return".
//
#define VMIOS_INTERCEPT_NOTIFIER_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    const char   *context,      \
    void         *userData      \
)
typedef VMIOS_INTERCEPT_NOTIFIER_FN((*vmiosInterceptNotifierFn));

//
// Shared data listener
//
#define VMI_SHARED_DATA_LISTENER_FN(_NAME) void _NAME( \
    void  *userObject,  \
    Int32 *ret,         \
    Int32  id,          \
    void  *userData     \
)
typedef VMI_SHARED_DATA_LISTENER_FN((*vmirtSharedDataListenerFn));

//
// Type of data returned by a vmiViewObject value callback
// (N.B. Values must match PPM_VVT_xxx enum for PSEs)
//
typedef enum vmiViewValueTypeE {
    VMI_VVT_NOSPACE   = -1, // No value returned. More buffer required.
    VMI_VVT_ERROR     = 0,  // No value returned

    VMI_VVT_BOOL      = 1,  // Primitive types
    VMI_VVT_SCHAR     = 2,
    VMI_VVT_UCHAR     = 3,
    VMI_VVT_INT8      = 4,
    VMI_VVT_UNS8      = 5,
    VMI_VVT_INT16     = 6,
    VMI_VVT_UNS16     = 7,
    VMI_VVT_INT32     = 8,
    VMI_VVT_UNS32     = 9,
    VMI_VVT_INT64     = 10,
    VMI_VVT_UNS64     = 11,
    VMI_VVT_ADDR      = 12,
    VMI_VVT_FLT64     = 13,

    VMI_VVT_STRING    = 14,  // Single line string
    VMI_VVT_MULTILINE = 15,  // Multi line string

} vmiViewValueType;

//
// Callback function invoked to return the value of a view object
//
// (Buffer is always large enough for primitive types. If a callback requires
// more space,  e.g. multi-line string response, it returns the desired buffer
// size and VMI_VVT_NOSPACE)
//
#define VMI_VIEW_VALUE_FN(_NAME) vmiViewValueType _NAME( \
    vmiViewObjectP object,      \
    void          *clientData,  \
    void          *buffer,      \
    Uns32         *bufferSize   \
)
typedef VMI_VIEW_VALUE_FN((*vmiViewValueFn));

//
// Callback function invoked to cause a view object action to occur
//
#define VMI_VIEW_ACTION_FN(_NAME) void _NAME(void *clientData)
typedef VMI_VIEW_ACTION_FN((*vmiViewActionFn));

//
// Callback function invoked when a view object is created or deleted
//
#define VMI_VIEW_OBJECT_NOTIFY_FN(_NAME) void _NAME( \
    vmiViewObjectP object,      \
    void          *userData,    \
    Bool           deleting     \
)
typedef VMI_VIEW_OBJECT_NOTIFY_FN((*vmiViewObjectNotifyFn));

//
// Callback function invoked when a view event is created or deleted
//
#define VMI_VIEW_EVENT_NOTIFY_FN(_NAME) void _NAME( \
    vmiViewEventP  event,       \
    void          *userData,    \
    Bool           deleting     \
)
typedef VMI_VIEW_EVENT_NOTIFY_FN((*vmiViewEventNotifyFn));

//
// Callback function invoked when a view event occurs
//
#define VMI_VIEW_EVENT_LISTENER_FN(_NAME) void _NAME( \
    vmiViewEventP  event,       \
    void          *userData     \
)
typedef VMI_VIEW_EVENT_LISTENER_FN((*vmiViewEventListenerFn));

//
// Callback function type applied to each SMP processor in a model
//
#define VMI_SMP_ITER_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    void         *userData      \
)
typedef VMI_SMP_ITER_FN((*vmiSMPIterFn));

//
// Callback after instruction count timer expires
//
#define VMI_ICOUNT_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,   \
    vmiModelTimerP timer,       \
    Uns64          iCount,      \
    void          *userData     \
)
typedef VMI_ICOUNT_FN((*vmiICountFn));

//
// Simulation time
//
typedef Flt80 vmiTime;

//
// Callback at start of new quantum
//
#define VMI_QUANTUM_TIMER_FN(_NAME) void _NAME( \
    vmiProcessorP    processor,     \
    vmiQuantumTimerP timer,         \
    void             *userData      \
)
typedef VMI_QUANTUM_TIMER_FN((*vmiQuantumTimerFn));

//
// This value may be passed as the 'scope' argument of vmirtAdd*Callback and
// vmirtRemove*Callback functions to indicate that the callback should only be
// triggered by a *master* access (note that a null scope will cause the
// callback to be triggered by either master or slave access)
//
#define VMI_MASTER_SCOPE ((vmiProcessorP)-1)

//
// Macro defining processor fetch notification callback function (see
// vmirtAddPCCallback and vmirtRemovePCCallback)
//
#define VMI_PC_WATCH_FN(_NAME) void _NAME( \
    void         *userData,     \
    vmiProcessorP processor,    \
    Addr          thisPC        \
)

//
// Prototype for processor fetch notification callback function (see
// vmirtAddPCCallback and vmirtRemovePCCallback)
//
typedef VMI_PC_WATCH_FN((*vmiPCWatchFn));

//
// This type specifies a block tag, used to implement conditional flushing of
// code blocks - see functions vmimtTagBlock and vmirtFlushTargetModeTagged.
//
typedef enum vmiBlockTagE {
    VBT_NA = 0,         // no tag
    VBT_1  = (1<<0),    // tag 1
    VBT_2  = (1<<1),    // tag 2
    VBT_3  = (1<<2),    // tag 3
    VBT_4  = (1<<3),    // tag 4
    VBT_5  = (1<<4),    // tag 5
    VBT_6  = (1<<5),    // tag 6
    VBT_7  = (1<<6),    // tag 7
    VBT_8  = (1<<7),    // tag 8
} vmiBlockTag;

//
// Control the visibility of the model in debug and introspection.
//
typedef enum vmiVisibilityE {
    VMI_VISIBLE,
    VMI_INVISIBLE
} vmiVisibility;

//
// Model release status
//
typedef enum vmiReleaseStatusE {
    VMI_UNSET,
    VMI_INTERNAL,
    VMI_RESTRICTED,
    VMI_IMPERAS,
    VMI_OVP,
} vmiReleaseStatus;

//
// This enumeration type is used with functions of type vmiStartEndBlockFn to
// indicate why the morpher callback (of type vmiMorphFn) is about to be called.
// The members have the following meanings:
//
// VMIMR_NEW_BLOCK
// ---------------
// A new block translation is about to start which should use the current
// processor state.
//
// VMIMR_RETRANSLATE
// -----------------
// A new block translation is about to start to replace a current partially
// executed block because assumptions that were made when that block was created
// no longer apply. The translation will begin with the first simulated address
// of the previously-generated block, which is not necessarily the processor
// current simulated PC. Any processor state that affects generated code will
// need to be reset to the values in force when the original code block was
// translated. This is required only in rare cases where execution state changes
// through a sequence of instructions (for example ARM Thumb-mode IT state,
// which affects conditional execution of a sequence of up to four following
// instructions).
//
// VMIMR_ATTRIBUTES
// ----------------
// The a translation is about to start to gather information about a single
// instruction for use with the instruction attributes API.
//
typedef enum vmiMorphReasonE {
    VMIMR_NEW_BLOCK,        // new block translation
    VMIMR_RETRANSLATE,      // retranslation of existing block
    VMIMR_ATTRIBUTES        // instruction attribute query
} vmiMorphReason;

//
// This enumeration type is passed to registered callbacks of type
// vmiBranchReasonFn to indicate why execution has been initiated at the given
// simulated PC. The members have the following meanings:
//
// VMIBR_UNCOND
// -------------
// Unconditional branch has been made to the given address.
//
// VMIBR_COND_TAKEN
// -----------------
// Conditional branch has been made to the given address.
//
// VMIBR_COND_NOT_TAKEN
// ---------------------
// A conditional branch has not been taken, and execution has fallen through
// to the next instruction address.
//
// VMIBR_PC_SET
// -------------
// The processor PC has been set by some branch idiom not encoded directly in
// an instruction (for example, entry to or exit from an exception handler).
//
typedef enum vmiBranchReasonE {
    VMIBR_UNCOND,           // unconditional branch taken
    VMIBR_COND_TAKEN,       // conditional branch taken
    VMIBR_COND_NOT_TAKEN,   // conditional branch not taken
    VMIBR_PC_SET,           // PC set by non instruction route (e.g. exception)
    VMIBR_LAST,             // KEEP LAST
} vmiBranchReason;

//
// This callback function type defines a notifier that is called whenever
// program control flow changes (see type vmiBranchReason above for more
// information about the reason codes). The callback is passed the address of
// the previous instruction (prevPC) and the address of the current instruction
// (thisPC).
//
#define VMI_BRANCH_REASON_FN(_NAME) void _NAME( \
    vmiProcessorP   processor,  \
    Addr            prevPC,     \
    Addr            thisPC,     \
    vmiBranchReason reason,     \
    void           *userData    \
)
typedef VMI_BRANCH_REASON_FN((*vmiBranchReasonFn));

//
// Operation type implemented by debug helper
//
typedef enum vmiStepOperationE {
    VMI_STEP_INTO,      // step one source line, into a subroutine
    VMI_STEP_OVER,      // step one source line, over a subroutine
    VMI_STEP_FINISH     // step out of the current subroutine
} vmiStepOperation;

//
// This enumeration is used to qualify the count returned by vmirtGetSkipCount.
// The members have the following meanings:
//
// VMIST_COMMITTED
// ---------------
// Return a count of skipped cycles which have been committed and will be
// included in the return value from vmirtGetICount.
//
// VMIST_PENDING
// -------------
// Return a count of skipped cycles which are pending and will not yet be
// included in the return value from vmirtGetICount. Pending skipped cycles are
// committed at a quantum boundary or by a call to vmirtAddSkipCount with
// immediate effect.
//
// VMIST_ALL
// ---------
// Return the total of committed and pending skipped cycles.
//
typedef enum vmiSkipTypeE {
    VMIST_COMMITTED,    // committed skipped cycles
    VMIST_PENDING,      // pending skipped cycles
    VMIST_ALL,          // committed and pending skipped cycles
} vmiSkipType;


