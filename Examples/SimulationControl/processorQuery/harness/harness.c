/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

/*
 * This example shows how information can be extracted from a processor model.
 * This information can be used to
 *     : create documentation
 *     : build a platform that makes few assumptions about the model.
 *     : build a debugger that adapts to the model.
 *
 * Note that each processor model can return different information, as can
 * different variants of the same model.
 *
 * Note that some functions shown here that return human readable strings have
 * sister functions that return enumerated types. You should not have to compare
 * strings to identify the types of registers, ports, modes etc.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define HARNESS_NAME "QUERY_PROCESSOR"

// local function definition
//   Instances a processor model
//   Uses the op query functions to obtain information about it's
//      Buses
//      Nets
//      Registers
//      Exceptions
//      Modes
//      Parameters
//      Description
//      Info
//      Documentation

static void queryProcessor(
    const char *instance,
    const char *vendor,
    const char *name,
    const char *endian,
    const char *variant);

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N                                  //
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {

    // Check each model exists before the query
    queryProcessor("i0", "arm.ovpworld.org",  "arm",    "little", "ARM920T"   );
    queryProcessor("i1", "arm.ovpworld.org",  "arm",    "little", "Cortex-A8" );
    queryProcessor("i2", "arm.ovpworld.org",  "arm",    "little",  NULL       );

    queryProcessor("i3", "arm.ovpworld.org",  "armm",   "little", "Cortex-M3" );
    queryProcessor("i4", "arm.ovpworld.org",  "armm",   "little",  NULL       );

    queryProcessor("i5", "mips.ovpworld.org", "mips32_r1r5", "little", "4Kc"       );
    queryProcessor("i6", "mips.ovpworld.org", "mips32_r1r5", "little", "24Kf"      );
    queryProcessor("i7", "mips.ovpworld.org", "mips32_r1r5", "little", "74Kf"      );
    queryProcessor("i8", "mips.ovpworld.org", "mips32_r1r5", "little",  NULL       );

    queryProcessor("i9", "xilinx.ovpworld.org", "microblaze", "little", NULL  );
    queryProcessor("i10", "ovpworld.org",      "or1k",        NULL,     NULL  );


    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}


//
// Callback for register query. This gets information about each register and how
// it can be used.
//
static OP_PROCESSOR_ITERATOR_FN(queryRegistersCB) {

    opPrintf("  REGISTERS\n");

    optRegGroupP group = NULL;

    // Are the registers in groups
    if(!opProcessorRegGroupNext(processor, group)) {

        // no register groups
        optRegP reg = NULL;

        if(!opProcessorRegNext(processor, reg)) {

            opPrintf("  NO REGISTER INFORMATION\n");

        } else {

            while((reg=opProcessorRegNext(processor, reg))) {

                const char *name     = opRegName(reg);
                const char *desc     = opRegDescription(reg);
                Uns32 regbits        = opRegBits(reg);

                // Usage as a string, (see opRegUsageEnum)
                const char *use      = opRegUsageString(reg);

                const char *readonly = opRegReadOnly(reg) ? "readonly" : "readwrite";

                opPrintf("    REGISTER (%2d bits) %-15s %-25s %-10s", regbits, use, name, readonly);
                if (desc) {
                    opPrintf(" (%s)", desc);
                }
                opPrintf("\n");
            }
        }

    } else {
        // iterate over register groups
        while((group=opProcessorRegGroupNext(processor, group))) {

            opPrintf("  GROUP %s\n", opRegGroupName(group));

            optRegP reg = NULL;

            if(!opRegGroupRegNext(processor, group, reg)) {

                opPrintf("    NO REGISTER INFORMATION\n");

            } else {

                while((reg=opRegGroupRegNext(processor, group, reg))) {

                    const char *name     = opRegName(reg);
                    const char *desc     = opRegDescription(reg);
                    Uns32 regbits        = opRegBits(reg);

                    // Usage as a string, (see opRegUsageEnum)
                    const char *use      = opRegUsageString(reg);

                    const char *readonly = opRegReadOnly(reg) ? "readonly" : "readwrite";
                    opPrintf("    REGISTER (%2d bits) %-15s %-25s %-10s", regbits, use, name, readonly);
                    if (desc) {
                        opPrintf(" (%s)", desc);
                    }
                    opPrintf("\n");
                }
            }
        }
    }
    opPrintf("\n");
}

//
// Query registers and register groups in the passed processor. This information can be used
// by a debugger to get a list of registers, their types, sizes (and values).
//
static void queryRegisters(optProcessorP processor) {
    queryRegistersCB(processor, 0);
    opProcessorIterDescendants(processor, queryRegistersCB, 0);
}

//
// Callback for exception query
//
static OP_PROCESSOR_ITERATOR_FN(queryExceptionsCB) {

    if(!opProcessorExceptionNext(processor, 0)) {

        opPrintf("  NO EXCEPTION INFORMATION\n");

    } else {

        opPrintf("  EXCEPTIONS\n");

        optExceptionP info = NULL;
        optExceptionP current = opProcessorExceptionCurrent(processor);

        while((info=opProcessorExceptionNext(processor, info))) {
            opPrintf(
                "    %-15s (code %u)%s\n",
                opExceptionName(info),
                opExceptionCode(info),
                (info==current?" [current]" : "")
            );
        }
    }

    opPrintf("\n");
}

//
// Query exceptions in the passed processor
//
static void queryExceptions(optProcessorP processor) {
    queryExceptionsCB(processor, 0);
    opProcessorIterDescendants(processor, queryExceptionsCB, 0);
}

//
// Callback for mode query
//
static OP_PROCESSOR_ITERATOR_FN(queryModesCB) {

    if(!opProcessorModeNext(processor, 0)) {

        opPrintf("  NO MODE INFORMATION\n");

    } else {

        opPrintf("  MODES\n");

        optModeP info = NULL;

        while((info=opProcessorModeNext(processor, info))) {
            const char *current = (opProcessorModeCurrent(processor) == info) ? " [current]" : "";
            const char *name    = opModeName(info);
            Uns32       code    = opModeCode(info);
            const char *desc    = opModeDescription(info);

            opPrintf("    %-15s (code %u) %s", name,code, current);
            if (desc) {
                opPrintf(" (%s)", desc);
            }
            opPrintf("\n");
        }

    }

    opPrintf("\n");
}

//
// Query modes in the passed processor
//
static void queryModes(optProcessorP processor) {
    queryModesCB(processor, 0);
    opProcessorIterDescendants(processor, queryModesCB, 0);
}

//
// Query parameters (special case for enumerated values)
//
static void enums(optFormalP formal) {
    opPrintf("        ENUMS: ");
    optFormalEnumP e = NULL;
    while((e = opFormalEnumNext(formal, e))) {
        const char *name = opObjectName(e);
        const char *desc = opFormalEnumDescription(e);
        Uns32       val  = opFormalEnumValue(e);
        opPrintf("\n           %3d = %s", val, name);
        if (desc) {
            opPrintf(" (%s)", desc);
        }
    }
    opPrintf("\n");
}

static void queryFormals(optProcessorP processor) {

    opPrintf("  PARAMETERS\n");

    optFormalP formal = NULL;
    while( (formal = opObjectFormalNext(processor, formal, OP_PARAM_MODEL))) {
        const char  *name = opObjectName(formal);

        // Usage as a string (see opFormalType)
        const char  *type = opFormalTypeString(formal);

        const char  *desc = opFormalDescription(formal);


        opPrintf("    PARAMETER: %-35s %-15s", name, type );
        if (desc) {
            opPrintf(" (%s)", desc);
        }
        opPrintf("\n");
        if (opFormalType(formal) == OP_PARAM_ENUM) {
            enums(formal);
        }
    }
    opPrintf("\n");
}

static void queryBuses(optProcessorP processor) {

    opPrintf(" BUSES\n");

    optBusPortP busport = NULL;
    while( (busport = opObjectBusPortNext(processor, busport))) {
        const char  *name = opObjectName(busport);
        const char  *desc = opBusPortDescription(busport);

        // Usage as a string (see opBusPortType)
        const char  *type = opBusPortTypeString(busport);

        Uns32        minBits = opBusPortAddrBitsMin(busport);
        Uns32        maxBits = opBusPortAddrBitsMax(busport);

        opPrintf("    BUS %-20s %-20s (%d-%d bits)", type, name, minBits, maxBits);
        if (desc) {
            opPrintf(" (%s)", desc);
        }
        opPrintf("\n");
    }
    opPrintf("\n");
}

static void queryNets(optProcessorP processor) {

    opPrintf("  NETS\n");

    optNetPortP netport = NULL;
    while( (netport = opObjectNetPortNext(processor, netport))) {
        const char  *name = opObjectName(netport);
        const char  *desc = opNetPortDescription(netport);

        // Usage as a string (see opNetPortType)
        const char  *type = opNetPortTypeString(netport);

        opPrintf("    NET %-20s %-20s ", type, name);
        if (desc) {
            opPrintf(" (%s)", desc);
        }
        opPrintf("\n");
    }
    opPrintf("\n");
}

//
// Indent to indicate the depth of hierarchy
//
static void indentText (Uns32 s) {
    while(s--) {
         opPrintf("  ");
    }
}

//
// Print the description and name of this processor, then recursively find all children
// Note the the description field is optional and is generally missing from single-core processors.
//
static void queryDescriptionCB(optProcessorP processor, Uns32 depth) {

    const char *desc = opProcessorDescription(processor);
    const char *name = opObjectName(processor);

    indentText(depth++);
    opPrintf("        %s:%s\n", name, desc ?: "(no description)");

    optProcessorP ch;
    for (ch= opProcessorChild(processor); ch ; ch = opProcessorSiblingNext(ch)) {
        queryDescriptionCB(ch, depth);
    }
}

static void queryDescription(optProcessorP processor) {
    opPrintf("    HIERARCHY\n");
    queryDescriptionCB(processor, 0);
    opPrintf("\n");
}

static void printVLNV(const char *what, optVLNVP vlnv) {
    if(vlnv) {
        opPrintf("%s %s/%s/%s/%s\n",
                what,
                opVLNVVendor(vlnv),
                opVLNVLibrary(vlnv),
                opVLNVName(vlnv),
                opVLNVVersion(vlnv));
    }
}

//
// Get other information embedded in the model
//
static void queryInfo(optProcessorP processor) {

    // the path to the gdb in the Imperas installation
    // This will select the correct gdb regardless of processor variant, host OS etc..,.
    const char *gdbpath     = opProcessorGdbPath(processor);

    // Any special flags required by the gdb when used in this context.
    const char *gdbflags    = opProcessorGdbFlags(processor);

    // This string is usually vendor-specific.
    // Other processors in this family will have the same string.
    const char *family      = opProcessorFamily(processor);

    // Where the processor is expecting to be stored. This can usually be ignored
    // since you knew where to find the processor in the first place.
    optVLNVP    model       = opObjectVLNV(processor);

    // A semihost library to be used with this processor by default.
    optVLNVP    semihost    = opProcessorDefaultSemihost(processor);

    // Which endian will this processor support? This is NOT the current endian.
    optEndian   endian      = opProcessorEndian(processor, True);

    // A list of ELF codes that this processor supports. Used in the case where
    // one or more GNU (or compatible) tool-chains are used to generate code for
    // this processor.
    Bool       defaultElf   = 0;
    Uns32      max          = 10;
    Uns32      elves[max];
    Uns32      actualElves  = opProcessorElfCodes(processor, elves, max, &defaultElf);
    if(actualElves > max) {
        // truncate the result - could allocate a larger array if required.
        actualElves = max;
    }

    opPrintf("  GENERAL INFORMATION\n");
    opPrintf("    GDB path         : %s\n", gdbpath    ?: "(none)");
    opPrintf("    GDB flags        : %s\n", gdbflags   ?: "(none)");
    opPrintf("    Processor family : %s\n", family     ?: "(none)");
    opPrintf("    Processor endian : %d\n", endian);

    printVLNV("    Model VLNV       :", model);
    printVLNV("    Semihost VLNV    :", semihost);

    opPrintf("    ELF Code(s)      :");
    Uns32 i;
    for(i=0; i < actualElves; i++) {
        opPrintf(" %d", elves[i]);
    }
    if(defaultElf) {
        opPrintf("    (This is the default processor for these ELF codes)\n");
    }
    opPrintf("\n");
}

//
// A model can supply documentation with arbitrary depth and detail. It is up the
// the consumer to format it as desired. The data is presented in a structure similar
// to the DOM used by some XML documents.
//
static void queryDocumentationNode(optDocNodeP node, Uns32 depth) {
    optDocNodeType type = opDocNodeType(node);
    indentText(depth++);
    switch(type) {
        case OP_DOC_NODE_TITLE :
            opPrintf("%s\n", opDocText(node));
            break;
        case OP_DOC_NODE_TEXT  :
            opPrintf("%s\n", opDocText(node));
            break;
        case OP_DOC_NODE_FIELDS:
            opPrintf("%s w:%u\n", opDocText(node), opDocFieldWidth(node));
            break;
        case OP_DOC_NODE_FIELD :
            opPrintf("%s w:%u o:%u\n", opDocText(node), opDocFieldWidth(node), opDocFieldOffset(node));
            break;
    }
    optDocNodeP ch = 0;
    while((ch = opDocChildNext(node, ch))) {
        queryDocumentationNode(ch, depth);
    }
}

static void queryDocumentation(optProcessorP processor) {
    opPrintf("  DOCUMENTATION:\n");
    optDocNodeP node = 0;
    while((node = opObjectDocNodeNext(processor, node))) {
        queryDocumentationNode(node, 1);
    }
    opPrintf("\n");
}

//
// Create a new processor instance, given the vendor, name and optional variant.
// If no variant is provided, the default processor is constructed.
// Some of these example processors might be missing from your installation.
//
static optProcessorP newProcessor(
    optModuleP mr,
    const char *instance,
    const char *path,
    const char *endian,
    const char *variant
) {
    optProcessorP processor = opProcessorNew(
                               mr,
                               path,
                               "cpu",
                               NULL,
                               OP_PARAMS (
                                   OP_PARAM_STRING_SET("endian",  endian),
                                   OP_PARAM_STRING_SET("variant", variant)
                               )
                              );
    return processor;
}

static void queryProcessor(
    const char *instance,
    const char *vendor,
    const char *name,
    const char *endian,
    const char *variant
) {

    opSessionInit(OP_VERSION);

    optModuleP mr = opRootModuleNew(0, HARNESS_NAME, 0);

    const char *path = opVLNVString(NULL, vendor, "processor", name, "1.0", OP_PROCESSOR, OP_VLNV_FATAL);

    if(path) {

        optProcessorP processor = newProcessor(mr, instance, path, endian, variant);

        if(processor) {
            opPrintf("PROCESSOR: Vendor: %s   Name: %s   Variant: %s\n", vendor, name, variant?: "(no variant)");
            queryBuses(processor);
            queryNets(processor);
            queryRegisters(processor);
            queryExceptions(processor);
            queryModes(processor);
            queryFormals(processor);
            queryDescription(processor);
            queryInfo(processor);
            queryDocumentation(processor);
        }
    }

    opSessionTerminate();

}

