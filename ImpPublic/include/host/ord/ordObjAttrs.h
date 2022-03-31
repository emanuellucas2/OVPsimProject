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

#ifndef ORD_OBJ_ATTRS_H
#define ORD_OBJ_ATTRS_H

#include "ord/ordTypes.h"
#include "hostapi/impTypes.h"

//
// This file defines the entry points to a custom  object loader.
// Use this to create a shared object or DLL that will be loaded by
// the simulator so that you can load files of your own format.
//

//
// Do not change this
//
#define ORD_OBJREADER_VERSION      "1.4"

//
// CPU type
//
typedef Uns16 ordCpuType, *ordCpuTypeP;

//
// Types of object
//
typedef enum ordObjectTypeE {
    ORD_TYPE_ILLEGAL,      // not recognized
    ORD_TYPE_EXE,          // executable
    ORD_TYPE_SHARE,        // shared object/dll
} ordObjectType;


typedef enum ordProtectionE {
    ORD_PROT_NONE      = 0x0,
    ORD_PROT_READ      = 0x1,
    ORD_PROT_WRITE     = 0x2,
    ORD_PROT_EXECUTE   = 0x4,
} ordProtection;

//
// Information extracted from an object header
// (Not all info will be valid, depending on object type)
//
typedef struct ordObjectInfoS {
    Addr                   entry;
    ordObjectType          objType;
    Uns16                  cpuType;
    Uns16                  cpuSupp;
    ordCpuEndian           endian;
    ordCpuArch             cpuArch;

    // info for dynamic loader
    union {
        // ELF-specific fields
        struct {
            // info for dynamic loader
            Uns64                    phnum;
            Uns64                    phent;
            Uns64                    phdr;
            char*                    interpreter;
        } elf;
        // New fields can be added here
    } u;

} ordObjectInfo,  *ordObjectInfoP, **ordObjectInfoPP;

//
// Called for each memory section with a pointer to the data with which to
// fill that section.
//
#define ORD_LOADMEMORY_FN(_name)    \
    Bool _name (                    \
        const char *sectionName,    \
        Addr        addr,           \
        void       *buffer,         \
        Offset      bytes,          \
        Bool        isCode,         \
        void        *userData       \
    )

typedef ORD_LOADMEMORY_FN((*ordLoadMemoryFn));

//
// Called for each memory section without the data. 'PAtoVA' is an offset from
// the physical section address passed here to the virtual address of any
// symbols that will later be added into that section (usually zero).
//
#define ORD_SECTION_FN(_name)       \
    void _name (                    \
        const char *sectionName,    \
        Addr        addr,           \
        Uns32       filesz,         \
        Uns32       memsz,          \
        Bool        isCode,         \
        void       *userData        \
    )

typedef ORD_SECTION_FN((*ordSectionFn));

//
// Called to add a symbol. 'value' is a virtual symbol address.
//
#define ORD_ADDSYMBOL_FN(_name)     \
    void _name (                    \
        const char         *name,   \
        const char         *file,   \
        Addr               value,   \
        Addr               size,    \
        ordSymbolType      type,    \
        ordSymbolBinding   binding, \
        void              *userData \
    )

typedef ORD_ADDSYMBOL_FN((*ordAddSymbolFn));

//
// Called to print unformatted text
//
#define ORD_PRINT_FN(_name)  void _name (const char *fmt, ...)

typedef ORD_PRINT_FN((*ordPrintFn));

//
// Called to print with standard intro
//
#define ORD_MESSAGE_FN(_name)  void _name (const char *severity, const char *prefix, const char *fmt, ...)

typedef ORD_MESSAGE_FN((*ordMessageFn));

#define ORD_PROTECT_FN(_name)  void _name (Addr low, Addr high, ordProtection prot, Bool isCode)

typedef ORD_PROTECT_FN((*ordProtectFn));


//
// Table of callbacks into the simulator
//
typedef struct ordCallbacksS {
    ordSectionFn       listSection;
    ordLoadMemoryFn    loadSection;
    ordAddSymbolFn     addSymbol;
    ordPrintFn         print;
    ordMessageFn       message;
    ordProtectFn       protect;
} ordCallbacks, *ordCallbacksP;

//
// Generic object reader interface.
// The object reader must define this function.
//
#define OBJREADER_FN(_NAME) Bool _NAME (  \
    void              *userData,          \
    const char        *filename,          \
    ordObjectInfoP     info,              \
    ordLoaderAttrs     attrs,             \
    Uns64              loadUnitOffset,    \
    const char        *targetName,        \
    const char        *how,               \
    ordCallbacksP      callbacks,         \
    Uns32              codeAddressBits,   \
    Uns32              dataAddressBits    \
)

typedef OBJREADER_FN((*ordReadFn));

//////////////////////////// DEBUGGER INFO READER /////////////////////////////
//
// Add one line entry
//
#define DRD_ADDLINE_FN(_name)\
    void _name  (            \
        const char *file,    \
        Uns32       line,    \
        Uns32       col,     \
        Addr        value    \
    )

typedef DRD_ADDLINE_FN((*drdAddLineFn));

//
// Add one compilation unit
//
#define DRD_DONEUNIT_FN(_name) \
    void _name (           \
        Addr lowerBounds,  \
        Addr upperBounds   \
    )

typedef DRD_DONEUNIT_FN((*drdDoneUnitFn));

//
// Table of callbacks into the simulator
//
typedef struct drdCallbacksS {
    drdAddLineFn       addLine;
    drdDoneUnitFn      doneUnit;
    ordPrintFn         print;
    ordMessageFn       message;
} drdCallbacks, *drdCallbacksP;

//
// Generic interface to debugger line information reader
//
#define LINEREADER_FN(_NAME)                   \
    Bool _NAME (                               \
        const char       *filename,            \
        drdCallbacksP     callbacks,           \
        Bool              readFrames           \
    )

typedef LINEREADER_FN((*drdDebugReadFn));

//
// This structure defines the interface to your object file reader
// You must declare and initialize one of these in the shared object/dll
//
typedef struct ordObjReaderAttrsS {
    const char     *interfaceVersion;                   // Supported interface version, e.g. "1.2"
    const char     *readerName;                         // A unique short name for this reader
                                                        // e.g. "COBOL"
    const char     *description;                        // Optional longer description
    ordReadFn       objReader;                          // Object reader entry function
    drdDebugReadFn  debugReader;                        // Optional debug info reader function

} ordObjReaderAttrs, *ordObjReaderAttrsP;

#endif

