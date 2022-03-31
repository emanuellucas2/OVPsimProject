
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

#define PREFIX        "MEM_WATCH"
#define PLUGIN_PREFIX PREFIX
#define CPU_PREFIX    PREFIX

// iGen generated includes
#include "memoryWatcher.igen.h"
#include "memoryWatcher.macros.igen.h"


//////////////////////////////////// Object ////////////////////////////////////

typedef struct vmiosObjectS {
    vmiProcessorP  processor;
    const char    *name;
    cmdArgValues   cmdArgs;
    Uns32          level;              // diagnostics level
    memDomainP     watchDomain;        // domain containing watched symbol
} vmiosObject;

//////////////////////////////// User functions ////////////////////////////////

// Add your functionality to these routines

//
// Write callback - triggered on every memory write
//
VMI_MEM_WATCH_FN(writeCB) {

    // we are interested only in writes made by processors (not arifacts of
    // simulation or memory accesses by other plugins, for example) so take
    // action only if processor is non null
    if(processor) {
        vmiMessage("I", PREFIX "_WCB", ": cpu %s write %d bytes @ 0x" FMT_Ax " (after "FMT_64u" instructions)",
                vmirtProcessorName(processor),
                bytes, address,
                vmirtGetICount(processor)
                );
    }
}

//
// Debug print arguments
//
static void printArgs(const char *name, Uns32 argc, vmiArgValueP arg) {
    vmiPrintf("calling %s\n", name);
    Uns32 i;
    for(i = 0; i < argc; i++, arg++) {
        vmiPrintf("%-20s %s %s ", arg->name, arg->isSet ? "set" : " - ", arg->changed ? "chg" : " - ");

        switch(arg->type) {
            case VMI_CA_NONE:
                break;
            case VMI_CA_BOOL :
                vmiPrintf("%s\n", arg->u.flag ? "T": "F");
                break;
            case VMI_CA_ENDIAN:
                vmiPrintf("%u\n", arg->u.uns32);
                break;
            case VMI_CA_ENUM:
                vmiPrintf("%u\n", arg->u.uns32);
                break;
            case VMI_CA_DOUBLE:
                vmiPrintf("%f\n", (float)arg->u.flt);
                break;
            case VMI_CA_INT32:
                vmiPrintf("%d\n", arg->u.int32);
                break;
            case VMI_CA_INT64:
                vmiPrintf(FMT_64d "\n", arg->u.int64);
                break;
            case VMI_CA_PTR:
                vmiPrintf("%p\n", arg->u.ptr);
                break;
            case VMI_CA_STRING:
                vmiPrintf("%s\n", arg->u.string ?: "(null)");
                break;
            case VMI_CA_UNS32:
                vmiPrintf("%u\n", arg->u.uns32);
                break;
            case VMI_CA_UNS64:
                vmiPrintf(FMT_64u "\n", arg->u.uns64);
                break;
        }
    }
}

VMIOS_COMMAND_PARSE_FN(memoryCB){
    if(object->level) {
        printArgs("memory", argc, &argv[0]);
    }

    if(argc != AI_memory_LAST) {
        vmiPrintf("Incorrect arguments, expected %d, found %d", AI_memory_LAST, argc);
        return "0";
    }

    vmiArgValueP addrArg = &argv[AI_memory_address];
    vmiArgValueP szArg   = &argv[AI_memory_size];

    if(addrArg->isSet && szArg->isSet) {
        // Add Memory Region
        object->watchDomain = vmirtGetProcessorDataDomain(object->processor);

        if(object->watchDomain) {

            // install a watchpoint callback at the passed address if lookup
            // succeeded
            vmirtAddWriteCallback(
                object->watchDomain,
                0,
                addrArg->u.addr,
                addrArg->u.addr + szArg->u.uns32 - 1,
                writeCB,
                0
            );
        }
    }

    return "1";
}

VMIOS_COMMAND_PARSE_FN(diagnosticCB){

    if(object->level) {
        printArgs("diagnostic", argc, &argv[0]);
    }

    if(argc != AI_diagnostic_LAST) {
        vmiPrintf("Incorrect arguments, expected %d, found %d", AI_diagnostic_LAST, argc);
        return "0";
    }

    vmiArgValueP level = &argv[AI_diagnostic_level];

    if(level->isSet) {
        object->level = level->u.uns32;
        if(object->level) {
            vmiPrintf("Diagnostics %d\n", object->level);
        }
    }

    return "1";
}

static VMIOS_CONSTRUCTOR_FN(constructor) {
    constructParser(object, &object->cmdArgs);

    object->name      = strdup(vmirtProcessorName(processor));
    object->processor = processor;

}

static VMIOS_DESTRUCTOR_FN(destructor) {
}

///////////////////////////// Model Attribute Table ////////////////////////////

vmiosAttr modelAttrs = {

    .versionString    = VMI_VERSION,
    .modelType        = VMI_INTERCEPT_LIBRARY,
    .packageName      = "memoryWatcher",
    .objectSize       = sizeof(vmiosObject),    // size in bytes of OSS object

    // object constructor and destructor
    .constructorCB    = constructor,
    .destructorCB     = destructor,

    .morphCB          = 0,                      // morph callback
    .nextPCCB         = 0,                      // get next instruction address
    .disCB            = 0,                      // disassemble instruction

    .paramSpecsCB     = nextParameter,
    .paramValueSizeCB = getTableSize,

    .releaseStatus  = VMI_UNSET,
    .visibility     = VMI_VISIBLE,

    .intercepts       = { {0} }                 // intercepts
};
