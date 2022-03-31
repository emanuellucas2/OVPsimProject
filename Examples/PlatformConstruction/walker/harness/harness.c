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


#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define HARNESS_NAME    "harness"
#define MODULE_DIR      "module"
#define MODULE_INSTANCE "u1"

//
// Indent to indicate the depth of hierarchy
//
static void indentText (Uns32 s) {
    while(s--) {
         opPrintf(".   ");
    }
}

static void walkModule(Uns32 indent, optModuleP mi);
static void walkObject(Uns32 indent, optObjectP object);

static void walkBusPortConnList      (Uns32 indent, optBusP       bus);
static void walkFIFOPortConnList     (Uns32 indent, optFIFOP      fifo);
static void walkNetPortConnList      (Uns32 indent, optNetP       net);
static void walkPacketnetPortConnList(Uns32 indent, optPacketnetP packetnet);
static void walkCommand              (Uns32 indent, optCommandP   o);


struct optionsS {
    const char *modulepath;
    const char *hierName;
} options = { 0 };

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    optCmdParserP parser = opCmdParserNew(HARNESS_NAME, OP_AC_ALL);
    opCmdParserAdd(parser, "modulepath"   , "", "file", "input", OP_FT_STRINGVAL, &options.modulepath, "path to a module",         OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "objectname"   , "", "path", "input", OP_FT_STRINGVAL, &options.hierName,   "hierarchical object name", OP_AC_ALL, 0, 0);
    opCmdParseArgs(parser, argc, argv);

    if(opErrors() == 0) {

        optModuleP mi = opRootModuleNew(0, 0, 0);
        if(!options.modulepath) {
            options.modulepath = MODULE_DIR;
        }
        opModuleNew(mi, options.modulepath, MODULE_INSTANCE, 0, 0);

        opRootModulePreSimulate(mi);
        opRootModuleTimeAdvance(mi, 0);

        // call the walker
        if(options.hierName) {
            optObjectP startObject = opObjectByName(mi, options.hierName, 0);

            // Was an object found - need to check [any] member of the union for non-zero?
            if(startObject.Module) {
                walkObject(0, startObject);
            } else {
                opMessage("E", "HARNESS_ONF", "Object '%s' not found", options.hierName);
            }
        } else {
           walkModule(0, mi);
        }
    }

    opSessionTerminate();
    return 0;
}

static void walkBusPortConnList(Uns32 indent, optBusP bus) {
    indentText(indent);
    opPrintf("max address : 0x" FMT_Ax "\n", opBusMaxAddress(bus));
    indentText(indent++);
    opPrintf("connections:\n");

    optBusPortConnP obj = 0;
    while((obj = opBusPortConnNext(bus, obj))) {
        indentText(indent);
        opPrintf("%s\n", opObjectHierName(obj));
    }
}
static void walkFIFOPortConnList(Uns32 indent, optFIFOP fifo) {
    indentText(indent++);
    opPrintf("connections:\n");

    optFIFOPortConnP obj = 0;
    while((obj = opFIFOPortConnNext(fifo, obj))) {
        indentText(indent);
        opPrintf("%s\n", opObjectHierName(obj));
    }
}

static void walkNetPortConnList(Uns32 indent, optNetP net) {
    indentText(indent++);
    opPrintf("connections:\n");

    optNetPortConnP obj = 0;
    while((obj = opNetPortConnNext(net, obj))) {
        indentText(indent);
        opPrintf("%s\n", opObjectHierName(obj));
    }
}

static void walkPacketnetPortConnList(Uns32 indent, optPacketnetP pkn) {
    indentText(indent++);
    opPrintf("connections:\n");

    optPacketnetPortConnP obj = 0;
    while((obj = opPacketnetPortConnNext(pkn, obj))) {
        indentText(indent);
        opPrintf("%s\n", opObjectHierName(obj));
    }
}







////////////////////////////////////////////////////////////////////////////////
// Forward references for contents
////////////////////////////////////////////////////////////////////////////////

static void walkApplication(Uns32 indent, optApplicationP o);
static void walkBridge(Uns32 indent, optBridgeP o);
static void walkBus(Uns32 indent, optBusP o);
static void walkBusSlave(Uns32 indent, optBusSlaveP o);
static void walkBusPort(Uns32 indent, optBusPortP o);
static void walkBusPortConn(Uns32 indent, optBusPortConnP o);
static void walkExtension(Uns32 indent, optExtensionP o);
static void walkExtElab(Uns32 indent, optExtElabP o);
static void walkFIFO(Uns32 indent, optFIFOP o);
static void walkFIFOPort(Uns32 indent, optFIFOPortP o);
static void walkFIFOPortConn(Uns32 indent, optFIFOPortConnP o);
static void walkFormalGroup(Uns32 indent, optFormalGroupP o);
static void walkFormalEnum(Uns32 indent, optFormalEnumP o);
static void walkMemory(Uns32 indent, optMemoryP o);
static void walkMMC(Uns32 indent, optMMCP o);
static void walkMMRegister(Uns32 indent, optMMRegisterP o);
static void walkMMRegisterField(Uns32 indent, optMMRegisterFieldP o);
static void walkModule(Uns32 indent, optModuleP o);
static void walkNet(Uns32 indent, optNetP o);
static void walkNetMonitor(Uns32 indent, optNetMonitorP o);
static void walkNetPort(Uns32 indent, optNetPortP o);
static void walkNetPortConn(Uns32 indent, optNetPortConnP o);
static void walkPacketnet(Uns32 indent, optPacketnetP o);
static void walkPacketnetMonitor(Uns32 indent, optPacketnetMonitorP o);
static void walkPacketnetPort(Uns32 indent, optPacketnetPortP o);
static void walkPacketnetPortConn(Uns32 indent, optPacketnetPortConnP o);
static void walkPeripheral(Uns32 indent, optPeripheralP o);
static void walkProcessor(Uns32 indent, optProcessorP o);

////////////////////////////////////////////////////////////////////////////////
// Forward references for iterators
////////////////////////////////////////////////////////////////////////////////

static void walkApplications(Uns32 indent, optObjectP o);
static void walkBridges(Uns32 indent, optModuleP o);
static void walkBuses(Uns32 indent, optModuleP o);
static void walkBusSlaves(Uns32 indent, optBusP o);
static void walkBusPorts(Uns32 indent, optObjectP o);
static void walkBusPortConns(Uns32 indent, optObjectP o);
static void walkCommands(Uns32 indent, optObjectP o);
static void walkExtensions(Uns32 indent, optObjectP o);
static void walkExtElabs(Uns32 indent, optObjectP o);
static void walkFIFOs(Uns32 indent, optModuleP o);
static void walkFIFOPorts(Uns32 indent, optObjectP o);
static void walkFIFOPortConns(Uns32 indent, optObjectP o);
static void walkFormals(Uns32 indent, optObjectP o);
static void walkFormalGroups(Uns32 indent, optObjectP o);
static void walkFormalEnums(Uns32 indent, optFormalP o);
static void walkMemorys(Uns32 indent, optModuleP o);
static void walkMMCs(Uns32 indent, optModuleP o);
static void walkMMRegisters(Uns32 indent, optBusPortP o);
static void walkMMRegisterFields(Uns32 indent, optMMRegisterP o);
static void walkModules(Uns32 indent, optModuleP o);
static void walkNets(Uns32 indent, optModuleP o);
static void walkNetMonitors(Uns32 indent, optNetP o);
static void walkNetPorts(Uns32 indent, optObjectP o);
static void walkNetPortConns(Uns32 indent, optObjectP o);
static void walkPacketnets(Uns32 indent, optModuleP o);
static void walkPacketnetMonitors(Uns32 indent, optPacketnetP o);
static void walkPacketnetPorts(Uns32 indent, optObjectP o);
static void walkPacketnetPortConns(Uns32 indent, optObjectP o);
static void walkParams(Uns32 indent, optObjectP o);
static void walkPeripherals(Uns32 indent, optModuleP o);
static void walkProcessors(Uns32 indent, optModuleP o);


static void walkFormal(Uns32 indent, optFormalP o) {
    indentText(indent++);
    opPrintf(
        "Formal: \"%s\" (%s)\n",
        opObjectHierName(o),
        opFormalSystem(o) ? "system" : "model"
    );

    indentText(indent);
    opPrintf("Type: \"%s\"\n", opFormalTypeString(o));
    indentText(indent);
    opPrintf("Desc: \"%s\"\n", opFormalDescription(o));

    if(opFormalType(o) == OP_PARAM_ENUM) {
        walkFormalEnums(indent, o);
    } else {

        switch(opFormalType(o)) {
            case OP_PARAM_BOOL   :
                indentText(indent);
                opPrintf("default:%u\n",      opFormalBoolDefaultValue(o));
                break;

            case OP_PARAM_INT32: {
                indentText(indent);
                Int32 min,max,dflt;
                opFormalInt32Limits(o, &min, &max, &dflt);
                if(min == max) {
                    opPrintf("[no limits] default:%d\n", dflt);
                } else {
                    opPrintf("min:%d max:%d default:%d\n", min, max, dflt);
                }
                break;
            }
            case OP_PARAM_INT64: {
                indentText(indent);
                Int64 min,max,dflt;
                opFormalInt64Limits(o, &min, &max, &dflt);
                if(min == max) {
                    opPrintf("[no limits] default:" FMT_64d  "\n", dflt);
                } else {
                    opPrintf("min:" FMT_64d  " max:" FMT_64d  " default:" FMT_64d  "\n", min, max, dflt);
                }
                break;
            }
            case OP_PARAM_UNS32: {
                indentText(indent);
                Uns32 min,max,dflt;
                opFormalUns32Limits(o, &min, &max, &dflt);
                if(min == max) {
                    opPrintf("[no limits] default:%u\n", dflt);
                } else {
                    opPrintf("min:%u max:%u default:%u\n", min, max, dflt);
                }
                break;
            }

            case OP_PARAM_UNS64: {
                indentText(indent);
                Uns64 min,max,dflt;
                opFormalUns64Limits(o, &min, &max, &dflt);
                if(min == max) {
                    opPrintf("[no limits] default:" FMT_64u  "\n", dflt);
                } else {
                    opPrintf("min:" FMT_64u  " max:" FMT_64u  " default:" FMT_64u  "\n", min, max, dflt);
                }
                break;
            }

            case OP_PARAM_DOUBLE: {
                indentText(indent);
                double min,max,dflt;
                opFormaldoubleLimits(o, &min, &max, &dflt);
                if(min == max) {
                    opPrintf("[no limits] default:" FMT_DBL  "\n", dflt);
                } else {
                    opPrintf("min:" FMT_DBL  " max:" FMT_DBL  " default:" FMT_DBL  "\n", min, max, dflt);
                }
                break;
            }

            case OP_PARAM_STRING :
                indentText(indent);
                opPrintf("max:%u default:(%s)\n", opFormalStringMaxLength(o), opFormalStringDefaultValue(o));
                break;

            default              :
                break;
        }
    }
}

static void walkParam(Uns32 indent, optParamP o) {
    indentText(indent++);
    if(opParamType(o) == OP_PARAM_NONE) {
        opPrintf("Parameter: (cursor)\n");
    } else {

        const char *name  = opObjectName(o);
        optObjectP parent = opObjectParent(o);
        Bool set = False;

        opPrintf("Parameter: \"%s\"    ", opObjectHierName(o));

        switch(opParamType(o)) {
            case OP_PARAM_BOOL   :    opPrintf("%u  (%s)\n",      opObjectParamBoolValue  (parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_INT32  :    opPrintf("%d (%s)\n",       opObjectParamInt32Value (parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_INT64  :    opPrintf(FMT_64d " (%s)\n", opObjectParamInt64Value (parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_UNS32  :    opPrintf("%u (%s)\n",       opObjectParamUns32Value (parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_UNS64  :    opPrintf(FMT_64u " (%s)\n", opObjectParamUns64Value (parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_DOUBLE :    opPrintf(FMT_DBL " (%s)\n", opObjectParamDoubleValue(parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_ENDIAN :    opPrintf("%u (%s)\n",       opObjectParamEndianValue(parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_ENUM   :    opPrintf("%u (%s)\n",       opObjectParamEnumValue  (parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_PTR    :    opPrintf("0x%x (%s)\n",     (Uns32)(UnsPS)opObjectParamPtrValue(parent, name, &set),   opObjectParamStringValue(parent, name)); break;
            case OP_PARAM_STRING :    opPrintf("%s\n",            opObjectParamStringValue(parent, name));          break;
            default              :    opPrintf("(unable to print)\n");
        }
    }
}

static void walkRegs(Uns32 indent, optProcessorP o, optRegGroupP group) {

    optRegP reg = 0;
    while((reg = opRegGroupRegNext(o, group, reg))) {
        indentText(indent);
        opPrintf("reg: \"%s/%s\"\n", opObjectHierName(o), opRegName(reg));
        indentText(indent+1);
        opPrintf("bits       : %u\n", opRegBits(reg));
        indentText(indent+1);
        opPrintf("usage      : %s\n", opRegUsageString(reg));
        indentText(indent+1);
        opPrintf("description: %s\n", opRegDescription(reg));
    }
}

static void walkRegGroups(Uns32 indent, optProcessorP o) {

    optRegGroupP group = 0;
    while((group = opProcessorRegGroupNext(o, group))) {
        indentText(indent);
        opPrintf("reg group \"%s/%s\"\n", opObjectHierName(o), opRegGroupName(group));
        walkRegs(indent+1, o, group);
    }
}

static void walkModes(Uns32 indent, optProcessorP o) {

    indentText(indent++);
    opPrintf("processor modes:\n");

    optModeP mode = 0;
    while((mode = opProcessorModeNext(o, mode))) {
        indentText(indent);
        opPrintf("name         : %s\n",   opModeName(mode));
        indentText(indent);
        opPrintf("  code       : 0x%x\n", opModeCode(mode));
        indentText(indent);
        opPrintf("  description: %s\n",   opModeDescription(mode));
    }
}

static void walkExceptions(Uns32 indent, optProcessorP o) {

    indentText(indent++);
    opPrintf("processor exceptions:\n");

    optExceptionP ex = 0;
    while((ex = opProcessorExceptionNext(o, ex))) {
        indentText(indent);
        opPrintf("name         : %s\n",   opExceptionName(ex));
        indentText(indent);
        opPrintf("  code       : 0x%x\n", opExceptionCode(ex));
        indentText(indent);
        opPrintf("  description: %s\n",   opExceptionDescription(ex));
    }
}

static void walkMPParts(Uns32 indent, optProcessorP o) {
    indentText(indent++);
    opPrintf("Processor: \"%s\"\n", opObjectHierName(o));

    walkRegGroups (indent, o);
    walkModes     (indent, o);
    walkExceptions(indent, o);
    walkCommands  (indent, o);

    if(!opProcessorIsLeaf(o)) {
        optProcessorP ch;
        for(ch = opProcessorChild(o); ch; ch = opProcessorSiblingNext(ch)) {
            walkMPParts(indent, ch);
        }
    }
}

static void walkVLNV(Uns32 indent, const char *what, optVLNVP v) {
    indentText(indent++);
    opPrintf(
        "%s: %s/%s/%s/%s\n",
        what,
        opVLNVVendor(v),
        opVLNVLibrary(v),
        opVLNVName(v),
        opVLNVVersion(v)
    );
}

static void walkMP(Uns32 indent, optProcessorP o) {
    indentText(indent);
    opPrintf("GdbPath       : %s\n",  opProcessorGdbPath(o));
    indentText(indent);
    opPrintf("GdbFlags      : %s\n",  opProcessorGdbFlags(o));
    indentText(indent);
    opPrintf("QL            : %u\n",  opProcessorQLQualified(o));
    indentText(indent);
    opPrintf("Release state : %u\n",  opObjectReleaseStatus(o));

    indentText(indent);
    opPrintf("family        : %s\n", opProcessorFamily(o));
    indentText(indent);
    opPrintf("groupH        : %s\n", opProcessorGroupH(o));
    indentText(indent);
    opPrintf("groupL        : %s\n", opProcessorGroupL(o));

    indentText(indent);
    opPrintf("Endian Data   : %u\n", opProcessorEndian(o, 1));
    indentText(indent);
    opPrintf("Endian Code   : %u\n", opProcessorEndian(o, 0));

    Uns32 elf[8];
    Bool  notUsed;
    Uns32 n = opProcessorElfCodes(o, (Uns32*)&elf, 8, &notUsed);

    indentText(indent);
    opPrintf("ELF codes     : ");
    Uns32 i;
    for(i=0; i < n; i++) {
        opPrintf(" %u", elf[i]);
    }
    opPrintf("\n");

    walkVLNV(indent, "helper",    opProcessorHelper(o));
    walkVLNV(indent, "semihost",  opProcessorDefaultSemihost(o));
    walkVLNV(indent, "vlnv",      opObjectVLNV(o));
    walkMPParts(indent, o);
}

static void walkDocNode(Uns32 indent, optDocNodeP o) {

    optDocNodeType type = opDocNodeType(o);
    indentText(indent++);
    opPrintf("DocNode:\n");
    indentText(indent);
    switch(type) {
        case OP_DOC_NODE_TITLE :
            opPrintf("Title  : %s\n", opDocText(o));
            break;
        case OP_DOC_NODE_TEXT  :
            opPrintf("Text   : %s\n", opDocText(o));
            break;
        case OP_DOC_NODE_FIELDS:
            opPrintf("Fields : %s w:%u\n", opDocText(o), opDocFieldWidth(o));
            break;
        case OP_DOC_NODE_FIELD :
            opPrintf("Field  : %s w:%u o:%u\n", opDocText(o), opDocFieldWidth(o), opDocFieldOffset(o));
            break;
    }

    optDocNodeP ch = 0;
    while((ch = opDocChildNext(o, ch))) {
        walkDocNode(indent, ch);
    }
}

//
// Entry from objects with documentation
//
static void walkDocNodes(Uns32 indent, optObjectP o) {

    optDocNodeP dn = 0;
    while((dn = opObjectDocNodeNext(o, dn))) {
        walkDocNode(indent, dn);
    }
}

static void walkCommandArg(optCommandArgP o, void *userData){

    Uns32 indent = *(Uns32*)userData;
    indentText(indent);
    opPrintf("Command Argument:\n");
    indentText(indent+1);
    opPrintf("name : \"%s\"\n", opCommandArgName(o));
    indentText(indent+1);
    opPrintf("type : \"%s\"\n", opCommandArgTypeString(o));
    indentText(indent+1);
    opPrintf("description : \"%s\"\n", opCommandArgDescription(o));
}

static void walkCommand(Uns32 indent, optCommandP o){
    indentText(indent);
    indent++;
    opPrintf("Command;%s\n", opObjectHierName(o));

    opCommandArgIterAll(o, walkCommandArg, &indent);
}




////////////////////////////////////////////////////////////////////////////////
// Contents walkers
////////////////////////////////////////////////////////////////////////////////

static void walkApplication(Uns32 indent, optApplicationP o){
    indentText(indent++);
    opPrintf("Application\n");
    indentText(indent);
    opPrintf("path : \"%s\"\n", opApplicationPath(o));
    indentText(indent);
    opPrintf("controls : %d\n", opApplicationControls(o));
    indentText(indent);
    opPrintf("offset : 0x" FMT_Ax "\n", opApplicationOffset(o));
}

static void walkBridge(Uns32 indent, optBridgeP o){
    indentText(indent++);
    opPrintf("Bridge;'%s'\n", opObjectHierName(o));
    walkBusPortConns(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
}

static void walkBus(Uns32 indent, optBusP o){
    indentText(indent++);
    opPrintf("Bus;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("addrBits : %d\n", opBusAddrBits(o));
    walkBusPortConnList(indent, o);
    walkBusSlaves(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
    walkFormalGroups(indent, o);
    walkApplications(indent, o);
}

static void walkBusSlave(Uns32 indent, optBusSlaveP o){
    indentText(indent++);
    opPrintf("BusSlave;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("priv : %d\n", opBusSlavePriv(o));
    indentText(indent);
    opPrintf("addrLo : 0x" FMT_Ax "\n", opBusSlaveAddrLo(o));
    indentText(indent);
    opPrintf("addrHi : 0x" FMT_Ax "\n", opBusSlaveAddrHi(o));
}

static void walkBusPort(Uns32 indent, optBusPortP o){
    indentText(indent++);
    opPrintf("BusPort;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opBusPortDescription(o));
    indentText(indent);
    opPrintf("type : %d\n", opBusPortType(o));
    indentText(indent);
    opPrintf("domainType : %d\n", opBusPortDomainType(o));
    indentText(indent);
    opPrintf("addrHi : 0x" FMT_Ax "\n", opBusPortAddrHi(o));
    indentText(indent);
    opPrintf("addrBitsDefault : %d\n", opBusPortAddrBitsDefault(o));
    indentText(indent);
    opPrintf("addrBitsMin : %d\n", opBusPortAddrBitsMin(o));
    indentText(indent);
    opPrintf("addrBitsMax : %d\n", opBusPortAddrBitsMax(o));
    indentText(indent);
    opPrintf("mustConnect : %d\n", opBusPortMustConnect(o));
    indentText(indent);
    opPrintf("isDynamic : %d\n", opBusPortIsDynamic(o));
    walkMMRegisters(indent, o);
}

static void walkBusPortConn(Uns32 indent, optBusPortConnP o){
    indentText(indent++);
    opPrintf("BusPortConn;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("type : %d\n", opBusPortConnType(o));
    indentText(indent);
    opPrintf("addrHi : 0x" FMT_Ax "\n", opBusPortConnAddrHi(o));
    indentText(indent);
    opPrintf("addrLo : 0x" FMT_Ax "\n", opBusPortConnAddrLo(o));
    indentText(indent);
    opPrintf("isDynamic : %d\n", opBusPortConnIsDynamic(o));
    indentText(indent);
    if(opBusPortConnBus(o)) {
        opPrintf("Bus: %s\n", opObjectHierName(opBusPortConnBus(o)));
    }
}

static void walkExtension(Uns32 indent, optExtensionP o){
    indentText(indent++);
    opPrintf("Extension;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("path : \"%s\"\n", opExtensionPath(o));
    walkParams(indent, o);
}

static void walkExtElab(Uns32 indent, optExtElabP o){
    indentText(indent++);
    opPrintf("ExtElab;'%s'\n", opObjectHierName(o));
    walkCommands(indent, o);
    walkFormals(indent, o);
    walkParams(indent, o);
}

static void walkFIFO(Uns32 indent, optFIFOP o){
    indentText(indent++);
    opPrintf("FIFO;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("depth : %d\n", opFIFODepth(o));
    walkFIFOPortConnList(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
}

static void walkFIFOPort(Uns32 indent, optFIFOPortP o){
    indentText(indent++);
    opPrintf("FIFOPort;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opFIFOPortDescription(o));
    indentText(indent);
    opPrintf("width : %d\n", opFIFOPortWidth(o));
    indentText(indent);
    opPrintf("type : %d\n", opFIFOPortType(o));
    indentText(indent);
    opPrintf("mustConnect : %d\n", opFIFOPortMustConnect(o));
}

static void walkFIFOPortConn(Uns32 indent, optFIFOPortConnP o){
    indentText(indent++);
    opPrintf("FIFOPortConn;'%s'\n", opObjectHierName(o));
    indentText(indent);
    if(opFIFOPortConnFIFO(o)) {
        opPrintf("FIFO: %s\n", opObjectHierName(opFIFOPortConnFIFO(o)));
    }
}

static void walkFormalGroup(Uns32 indent, optFormalGroupP o){
    indentText(indent++);
    opPrintf("FormalGroup;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opFormalGroupDescription(o));
}

static void walkFormalEnum(Uns32 indent, optFormalEnumP o){
    indentText(indent++);
    opPrintf("FormalEnum;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opFormalEnumDescription(o));
    indentText(indent);
    opPrintf("value : %d\n", opFormalEnumValue(o));
}

static void walkMemory(Uns32 indent, optMemoryP o){
    indentText(indent++);
    opPrintf("Memory;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("priv : %d\n", opMemoryPriv(o));
    indentText(indent);
    opPrintf("maxAddress : 0x" FMT_Ax "\n", opMemoryMaxAddress(o));
    walkBusPorts(indent, o);
    walkBusPortConns(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
    walkApplications(indent, o);
}

static void walkMMC(Uns32 indent, optMMCP o){
    indentText(indent++);
    opPrintf("MMC;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("path : \"%s\"\n", opMMCPath(o));
    indentText(indent);
    opPrintf("transparent : %d\n", opMMCTransparent(o));
    walkFormalGroups(indent, o);
    walkCommands(indent, o);
    walkBusPorts(indent, o);
    walkBusPortConns(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
}

static void walkMMRegister(Uns32 indent, optMMRegisterP o){
    indentText(indent++);
    opPrintf("MMRegister;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opMMRegisterDescription(o));
    indentText(indent);
    opPrintf("offset : 0x" FMT_Ax "\n", opMMRegisterOffset(o));
    indentText(indent);
    opPrintf("bits : %d\n", opMMRegisterBits(o));
    indentText(indent);
    opPrintf("isVolatile : %d\n", opMMRegisterIsVolatile(o));
    indentText(indent);
    opPrintf("readable : %d\n", opMMRegisterReadable(o));
    indentText(indent);
    opPrintf("writable : %d\n", opMMRegisterWritable(o));
    indentText(indent);
    opPrintf("index : %d\n", opMMRegisterIndex(o));
    walkMMRegisterFields(indent, o);
}

static void walkMMRegisterField(Uns32 indent, optMMRegisterFieldP o){
    indentText(indent++);
    opPrintf("MMRegisterField;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opMMRegisterFieldDescription(o));
    indentText(indent);
    opPrintf("offset : %d\n", opMMRegisterFieldOffset(o));
    indentText(indent);
    opPrintf("bits : %d\n", opMMRegisterFieldBits(o));
    indentText(indent);
    opPrintf("readable : %d\n", opMMRegisterFieldReadable(o));
    indentText(indent);
    opPrintf("writable : %d\n", opMMRegisterFieldWritable(o));
    indentText(indent);
    opPrintf("reset : 0x" FMT_64x " \n", opMMRegisterFieldReset(o));
}

static void walkModule(Uns32 indent, optModuleP o){
    indentText(indent++);
    opPrintf("Module;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("path : \"%s\"\n", opModulePath(o));
    walkDocNodes(indent, o);
    walkFormalGroups(indent, o);
    walkBridges(indent, o);
    walkBuses(indent, o);
    walkBusPorts(indent, o);
    walkBusPortConns(indent, o);
    walkExtensions(indent, o);
    walkFIFOs(indent, o);
    walkFIFOPorts(indent, o);
    walkFIFOPortConns(indent, o);
    walkFormals(indent, o);
    walkMemorys(indent, o);
    walkMMCs(indent, o);
    walkModules(indent, o);
    walkNets(indent, o);
    walkNetPorts(indent, o);
    walkNetPortConns(indent, o);
    walkPacketnets(indent, o);
    walkPacketnetPorts(indent, o);
    walkPacketnetPortConns(indent, o);
    walkParams(indent, o);
    walkPeripherals(indent, o);
    walkProcessors(indent, o);
}

static void walkNet(Uns32 indent, optNetP o){
    indentText(indent++);
    opPrintf("Net;'%s'\n", opObjectHierName(o));
    walkNetPortConnList(indent, o);
    walkNetMonitors(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
}

static void walkNetMonitor(Uns32 indent, optNetMonitorP o){
    indentText(indent++);
    opPrintf("NetMonitor\n");
}

static void walkNetPort(Uns32 indent, optNetPortP o){
    indentText(indent++);
    opPrintf("NetPort;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opNetPortDescription(o));
    indentText(indent);
    opPrintf("type : %d\n", opNetPortType(o));
    indentText(indent);
    opPrintf("mustConnect : %d\n", opNetPortMustConnect(o));
}

static void walkNetPortConn(Uns32 indent, optNetPortConnP o){
    indentText(indent++);
    opPrintf("NetPortConn;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("type : %d\n", opNetPortConnType(o));
    indentText(indent);
    if(opNetPortConnNet(o)) {
        opPrintf("Net: %s\n", opObjectHierName(opNetPortConnNet(o)));
    }
}

static void walkPacketnet(Uns32 indent, optPacketnetP o){
    indentText(indent++);
    opPrintf("Packetnet;'%s'\n", opObjectHierName(o));
    walkPacketnetPortConnList(indent, o);
    indentText(indent);
    opPrintf("maxBytes : %d\n", opPacketnetMaxBytes(o));
    walkFormalGroups(indent, o);
    walkPacketnetMonitors(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
}

static void walkPacketnetMonitor(Uns32 indent, optPacketnetMonitorP o){
    indentText(indent++);
    opPrintf("PacketnetMonitor\n");
}

static void walkPacketnetPort(Uns32 indent, optPacketnetPortP o){
    indentText(indent++);
    opPrintf("PacketnetPort;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("description : \"%s\"\n", opPacketnetPortDescription(o));
    indentText(indent);
    opPrintf("mustConnect : %d\n", opPacketnetPortMustConnect(o));
}

static void walkPacketnetPortConn(Uns32 indent, optPacketnetPortConnP o){
    indentText(indent++);
    opPrintf("PacketnetPortConn;'%s'\n", opObjectHierName(o));
    indentText(indent);
    if(opPacketnetPortConnPacketnet(o)) {
        opPrintf("Packetnet: %s\n", opObjectHierName(opPacketnetPortConnPacketnet(o)));
    }
}

static void walkPeripheral(Uns32 indent, optPeripheralP o){
    indentText(indent++);
    opPrintf("Peripheral;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("path : \"%s\"\n", opPeripheralPath(o));
    walkFormalGroups(indent, o);
    walkBusPorts(indent, o);
    walkBusPortConns(indent, o);
    walkExtElabs(indent, o);
    walkExtensions(indent, o);
    walkFIFOPorts(indent, o);
    walkFIFOPortConns(indent, o);
    walkNetPorts(indent, o);
    walkNetPortConns(indent, o);
    walkPacketnetPorts(indent, o);
    walkPacketnetPortConns(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
}

static void walkProcessor(Uns32 indent, optProcessorP o){
    indentText(indent++);
    opPrintf("Processor;'%s'\n", opObjectHierName(o));
    indentText(indent);
    opPrintf("path : \"%s\"\n", opProcessorPath(o));
    walkFormalGroups(indent, o);
    walkBusPorts(indent, o);
    walkBusPortConns(indent, o);
    walkFIFOPorts(indent, o);
    walkFIFOPortConns(indent, o);
    walkNetPorts(indent, o);
    walkNetPortConns(indent, o);
    walkParams(indent, o);
    walkFormals(indent, o);
    walkApplications(indent, o);
    walkMP(indent, o);
}


////////////////////////////////////////////////////////////////////////////////
// Iterators
////////////////////////////////////////////////////////////////////////////////

static void walkApplications(Uns32 indent, optObjectP o){
    optApplicationP ch = 0;
    while((ch = opObjectApplicationNext(o,ch))) {
        walkApplication(indent, ch);
    }
}

static void walkBridges(Uns32 indent, optModuleP o){
    optBridgeP ch = 0;
    while((ch = opBridgeNext(o,ch))) {
        walkBridge(indent, ch);
    }
}

static void walkBuses(Uns32 indent, optModuleP o){
    optBusP ch = 0;
    while((ch = opBusNext(o,ch))) {
        walkBus(indent, ch);
    }
}

static void walkBusSlaves(Uns32 indent, optBusP o){
    optBusSlaveP ch = 0;
    while((ch = opBusSlaveNext(o,ch))) {
        walkBusSlave(indent, ch);
    }
}

static void walkBusPorts(Uns32 indent, optObjectP o){
    optBusPortP ch = 0;
    while((ch = opObjectBusPortNext(o,ch))) {
        walkBusPort(indent, ch);
    }
}

static void walkBusPortConns(Uns32 indent, optObjectP o){
    optBusPortConnP ch = 0;
    while((ch = opObjectBusPortConnNext(o,ch))) {
        walkBusPortConn(indent, ch);
    }
}

static void walkCommands(Uns32 indent, optObjectP o){
    optCommandP ch = 0;
    while((ch = opObjectCommandNext(o,ch))) {
        walkCommand(indent, ch);
    }
}

static void walkExtensions(Uns32 indent, optObjectP o){
    optExtensionP ch = 0;
    while((ch = opObjectExtensionNext(o,ch))) {
        walkExtension(indent, ch);
    }
}

static void walkExtElabs(Uns32 indent, optObjectP o){
    optExtElabP ch = 0;
    while((ch = opObjectExtElabNext(o,ch))) {
        walkExtElab(indent, ch);
    }
}

static void walkFIFOs(Uns32 indent, optModuleP o){
    optFIFOP ch = 0;
    while((ch = opFIFONext(o,ch))) {
        walkFIFO(indent, ch);
    }
}

static void walkFIFOPorts(Uns32 indent, optObjectP o){
    optFIFOPortP ch = 0;
    while((ch = opObjectFIFOPortNext(o,ch))) {
        walkFIFOPort(indent, ch);
    }
}

static void walkFIFOPortConns(Uns32 indent, optObjectP o){
    optFIFOPortConnP ch = 0;
    while((ch = opObjectFIFOPortConnNext(o,ch))) {
        walkFIFOPortConn(indent, ch);
    }
}

static void walkFormals(Uns32 indent, optObjectP o){
    optFormalP ch = 0;
    while((ch = opObjectFormalNext(o,ch, OP_PARAM_ALL))) {
        walkFormal(indent, ch);
    }
}

static void walkFormalGroups(Uns32 indent, optObjectP o){
    optFormalGroupP ch = 0;
    while((ch = opObjectFormalGroupNext(o,ch))) {
        walkFormalGroup(indent, ch);
    }
}

static void walkFormalEnums(Uns32 indent, optFormalP o){
    optFormalEnumP ch = 0;
    while((ch = opFormalEnumNext(o,ch))) {
        walkFormalEnum(indent, ch);
    }
}

static void walkMemorys(Uns32 indent, optModuleP o){
    optMemoryP ch = 0;
    while((ch = opMemoryNext(o,ch))) {
        walkMemory(indent, ch);
    }
}

static void walkMMCs(Uns32 indent, optModuleP o){
    optMMCP ch = 0;
    while((ch = opMMCNext(o,ch))) {
        walkMMC(indent, ch);
    }
}

static void walkMMRegisters(Uns32 indent, optBusPortP o){
    optMMRegisterP ch = 0;
    while((ch = opBusPortMMRegisterNext(o,ch))) {
        walkMMRegister(indent, ch);
    }
}

static void walkMMRegisterFields(Uns32 indent, optMMRegisterP o){
    optMMRegisterFieldP ch = 0;
    while((ch = opMMRegisterFieldNext(o,ch))) {
        walkMMRegisterField(indent, ch);
    }
}

static void walkModules(Uns32 indent, optModuleP o){
    optModuleP ch = 0;
    while((ch = opModuleNext(o,ch))) {
        walkModule(indent, ch);
    }
}

static void walkNets(Uns32 indent, optModuleP o){
    optNetP ch = 0;
    while((ch = opNetNext(o,ch))) {
        walkNet(indent, ch);
    }
}

static void walkNetMonitors(Uns32 indent, optNetP o){
    optNetMonitorP ch = 0;
    while((ch = opNetMonitorNext(o,ch))) {
        walkNetMonitor(indent, ch);
    }
}

static void walkNetPorts(Uns32 indent, optObjectP o){
    optNetPortP ch = 0;
    while((ch = opObjectNetPortNext(o,ch))) {
        walkNetPort(indent, ch);
    }
}

static void walkNetPortConns(Uns32 indent, optObjectP o){
    optNetPortConnP ch = 0;
    while((ch = opObjectNetPortConnNext(o,ch))) {
        walkNetPortConn(indent, ch);
    }
}

static void walkPacketnets(Uns32 indent, optModuleP o){
    optPacketnetP ch = 0;
    while((ch = opPacketnetNext(o,ch))) {
        walkPacketnet(indent, ch);
    }
}

static void walkPacketnetMonitors(Uns32 indent, optPacketnetP o){
    optPacketnetMonitorP ch = 0;
    while((ch = opPacketnetMonitorNext(o,ch))) {
        walkPacketnetMonitor(indent, ch);
    }
}

static void walkPacketnetPorts(Uns32 indent, optObjectP o){
    optPacketnetPortP ch = 0;
    while((ch = opObjectPacketnetPortNext(o,ch))) {
        walkPacketnetPort(indent, ch);
    }
}

static void walkPacketnetPortConns(Uns32 indent, optObjectP o){
    optPacketnetPortConnP ch = 0;
    while((ch = opObjectPacketnetPortConnNext(o,ch))) {
        walkPacketnetPortConn(indent, ch);
    }
}

static void walkParams(Uns32 indent, optObjectP o){
    optParamP ch = 0;
    while((ch = opObjectParamNext(o,ch))) {
        walkParam(indent, ch);
    }
}

static void walkPeripherals(Uns32 indent, optModuleP o){
    optPeripheralP ch = 0;
    while((ch = opPeripheralNext(o,ch))) {
        walkPeripheral(indent, ch);
    }
}

static void walkProcessors(Uns32 indent, optModuleP o){
    optProcessorP ch = 0;
    while((ch = opProcessorNext(o,ch))) {
        walkProcessor(indent, ch);
    }
}

void walkObject(Uns32 indent, optObjectP object) {
    switch(opObjectType(object)) {
        case OP_APPLICATION_EN        : walkApplication(indent, object.Application); break;
        case OP_BRIDGE_EN             : walkBridge(indent, object.Bridge); break;
        case OP_BUS_EN                : walkBus(indent, object.Bus); break;
        case OP_BUSSLAVE_EN           : walkBusSlave(indent, object.BusSlave); break;
        case OP_BUSPORT_EN            : walkBusPort(indent, object.BusPort); break;
        case OP_BUSPORTCONN_EN        : walkBusPortConn(indent, object.BusPortConn); break;
        case OP_EXTENSION_EN          : walkExtension(indent, object.Extension); break;
        case OP_EXTELAB_EN            : walkExtElab(indent, object.ExtElab); break;
        case OP_FIFO_EN               : walkFIFO(indent, object.FIFO); break;
        case OP_FIFOPORT_EN           : walkFIFOPort(indent, object.FIFOPort); break;
        case OP_FIFOPORTCONN_EN       : walkFIFOPortConn(indent, object.FIFOPortConn); break;
        case OP_FORMALGROUP_EN        : walkFormalGroup(indent, object.FormalGroup); break;
        case OP_FORMALENUM_EN         : walkFormalEnum(indent, object.FormalEnum); break;
        case OP_MEMORY_EN             : walkMemory(indent, object.Memory); break;
        case OP_MMC_EN                : walkMMC(indent, object.MMC); break;
        case OP_MMREGISTER_EN         : walkMMRegister(indent, object.MMRegister); break;
        case OP_MMREGISTERFIELD_EN    : walkMMRegisterField(indent, object.MMRegisterField); break;
        case OP_MODULE_EN             : walkModule(indent, object.Module); break;
        case OP_NET_EN                : walkNet(indent, object.Net); break;
        case OP_NETMONITOR_EN         : walkNetMonitor(indent, object.NetMonitor); break;
        case OP_NETPORT_EN            : walkNetPort(indent, object.NetPort); break;
        case OP_NETPORTCONN_EN        : walkNetPortConn(indent, object.NetPortConn); break;
        case OP_PACKETNET_EN          : walkPacketnet(indent, object.Packetnet); break;
        case OP_PACKETNETMONITOR_EN   : walkPacketnetMonitor(indent, object.PacketnetMonitor); break;
        case OP_PACKETNETPORT_EN      : walkPacketnetPort(indent, object.PacketnetPort); break;
        case OP_PACKETNETPORTCONN_EN  : walkPacketnetPortConn(indent, object.PacketnetPortConn); break;
        case OP_PERIPHERAL_EN         : walkPeripheral(indent, object.Peripheral); break;
        case OP_PROCESSOR_EN          : walkProcessor(indent, object.Processor); break;
        default: break;
    }
}
