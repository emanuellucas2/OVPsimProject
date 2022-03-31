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

extern "C" {
#include "op/op.h"
}

#include <iostream>

namespace op {

//
// FWD references to OP classes
//
class application;
class bridge;
class bus;
class busDMISlave;
class busPort;
class busPortConn;
class busSlave;
class command;
class commandArg;
class docNode;
class exception;
class extension;
class extElab;
class FIFO;
class FIFOPort;
class FIFOPortConn;
class formal;
class formalEnum;
class memory;
class mode;
class module;
class monitor;
class MMC;
class MMRegister;
class net;
class netPort;
class netPortConn;
class object;
class packetnet;
class packetnetPort;
class packetnetPortConn;
class params;
class peripheral;
class processor;
class ram;
class reg;
class regGroup;
class rmm;
class triggerEvent;
class vlnv;
class watchpoint;

#define GET_METHOD_PROTO(_CLASS, _TYPE)               \
    static _CLASS *classGet(_TYPE existing);

#define EXISTING_CONSTRUCTOR_PROTO(_CLASS, _TYPE)     \
    _CLASS(_TYPE existing)

#define HANDLE_METHOD(_TYPE)                          \
    _TYPE handle() { return (_TYPE)h; }

#define FIRST_METHOD(_CLASS, _TYPE, _ITERATOR)     \
    _CLASS *_CLASS ## First (void) {               \
        _TYPE o = _ITERATOR((optModuleP)h, 0);     \
        return o ? (_CLASS *)opObjectClass(o) : 0; \
    }


//
// Macros for classes that use cast object pointers
//
#define CAST_HANDLE_METHOD(_TYPE) \
    _TYPE handle() { return (_TYPE)this; }

#define CAST_CLASS_GET_METHOD(_CLASS,_TYPE) \
     static _CLASS *classGet(_TYPE r) { return (_CLASS*) r; }

///////////////////////////////////////////// OBJECT //////////////////////////////////////////////

class object {

  public:
    optObjectP h;            // pointer to the OP object that this represents
    Bool       allocated;    // If true, this OP++ object needs to be deleted

    object(void) {
        h         = 0;
        allocated = false;
    }

    std::string  name(void)       { return opObjectName(h); }
    std::string  hierName(void)   { return opObjectHierName(h); }
    const char  *hierCName(void)  { return opObjectHierName(h); }

    void    classSet(void)        { opObjectClassSet(h, this); }
    void    classClr(void)        { opObjectClassSet(h, 0);    }
    object* classGet(void)        { return (object*)opObjectClass(h); }

    void readAbort (Addr addr);
    void writeAbort(Addr addr);
};

////////////////////////////////////////// TRIGGER EVENT //////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class triggerEvent {

  public:
    CAST_HANDLE_METHOD(optTriggerEventP)
    CAST_CLASS_GET_METHOD(triggerEvent,optTriggerEventP)
};

////////////////////////////////////////////// VLNV ///////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class vlnv {

  public:
    CAST_HANDLE_METHOD(optVLNVP)
    CAST_CLASS_GET_METHOD(vlnv,optVLNVP)

    static std::string string(
        std::string   vendor,
        std::string   library,
        std::string   name,
        std::string   version,
        optModelType  type,
        optVLNVError  reportErrors=OP_VLNV_FATAL
    );

    //
    // Methods for class VLNV
    //
    // Return the 'library' part of the VLNV
    std::string library(void){
        return opVLNVLibrary(handle());
    }

    // Return the 'name' part of the VLNV
    std::string name(void){
        return opVLNVName(handle());
    }

    // Internal function to destroy a temporary VLNV object
    void old(void){
        opVLNVOld(handle());
    }

    // Return the 'vendor' part of the VLNV
    std::string vendor(void){
        return opVLNVVendor(handle());
    }

    // Return the 'version' part of the VLNV
    std::string version(void){
        return opVLNVVersion(handle());
    }

};
////////////////////////////////////////// APPLICATION ////////////////////////////////////////////

class application : public object {

public:
    CAST_HANDLE_METHOD(optApplicationP)
    CAST_CLASS_GET_METHOD(application,optApplicationP)

    static bool headerRead(std::string path, ordObjectInfoP info) {
        return opApplicationHeaderRead(path.c_str(), info);
    }

    static bool loaderInstall(std::string path) {
        return opApplicationLoaderInstall(path.c_str());
    }

    //
    // Methods for class application
    //
    // Return the control features that were specified when this application was
    // loaded
    optLoaderControls controls(void){
        return opApplicationControls(handle());
    }

    // Return the elf code of a loaded application program
    Uns32 elfCode(void){
        return opApplicationElfCode(handle());
    }

    // Return the endian of a loaded application program
    optEndian endian(void){
        return opApplicationEndian(handle());
    }

    // Return the entry address of a loaded application program
    Addr entry(void){
        return opApplicationEntry(handle());
    }

    // Return the address offset that was specified when this application was
    // loaded
    Addr offset(void){
        return opApplicationOffset(handle());
    }

    // Return the path to a loaded application program
    std::string path(void){
        return opApplicationPath(handle());
    }

};

///////////////////////////////////////// COMMAND ARGUMENT /////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class commandArg {
    
public:
    CAST_HANDLE_METHOD(optCommandArgP)
    CAST_CLASS_GET_METHOD(commandArg,optCommandArgP)
    
    const char  *name()       { return opCommandArgName       (handle()); }
    optParamType type()       { return opCommandArgType       (handle()); }
    const char  *typeString() { return opCommandArgTypeString (handle()); }
    const char  *desc()       { return opCommandArgDescription(handle()); }
    
private:
    static OP_COMMAND_ARG_FN(eachArgNotifier);
    
protected:
    virtual void eachNotifier(command *cmd, commandArg *arg);
};

////////////////////////////////////////// COMMAND ARGUMENTS ///////////////////////////////////////

// Interface class to take control of the callback for each command

class commandArgs {
private:
    static OP_COMMAND_ARG_FN(eachCommandArgStatic);
    
public:
    commandArgs();
    void all(command &cmd);
    void all(command *cmd);

protected:
    virtual void eachCommandArg(commandArg *a);
};

///////////////////////////////////////////// COMMAND /////////////////////////////////////////////

class command {

public:
    CAST_HANDLE_METHOD(optCommandP)
    CAST_CLASS_GET_METHOD(command,optCommandP)

    const char *call(Uns32 argc, const char *argv[]) {
        return opCommandCall(handle(), argc, argv);
    }
    
    const char *helpC() {
        return opCommandHelp(handle());
    }
    
    const char *name() {
        return opObjectName(handle());
    }

    //
    // Methods for class command
    //
    // Return the help string associated with a command
    std::string help(void){
        return opCommandHelp(handle());
    }

};

///////////////////////////////////////////// COMMANDS /////////////////////////////////////////////

// Interface class to take control of the callback for each command

class commands {
private:
    static OP_COMMAND_FN(eachCommandStatic);
    
public:
    commands();
    void all(processor &proc);
    
protected:
    virtual void eachCommand(command *c);
};

///////////////////////////////////////////// DOC NODE ////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class docNode {

public:
    CAST_HANDLE_METHOD(optDocNodeP)
    CAST_CLASS_GET_METHOD(docNode,optDocNodeP)

    bool        isTitle(void) { return opDocIsTitle(handle()); }
    std::string text  (void)  { return opDocText(handle()); }

    docNode *childNext(docNode *prev) {
        return classGet(opDocChildNext(handle(), prev->handle()));
    }

    docNode *sectionAdd(std::string text) {
        return classGet(opDocSectionAdd(handle(), text.c_str()));
    }

    docNode *textAdd(std::string text) {
        return classGet(opDocTextAdd(handle(), text.c_str()));
    }

};

//////////////////////////////////////////// EXCEPTION ////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class exception {

  public:
    CAST_HANDLE_METHOD(optExceptionP)
    CAST_CLASS_GET_METHOD(exception,optExceptionP)

    //
    // Methods for class exception
    //
    // Return the name of the exception from the descriptor
    std::string name(void){
        return opExceptionName(handle());
    }

};

/////////////////////////////////////////// EXTENSION /////////////////////////////////////////////

class extension : public object {

public:
    HANDLE_METHOD(optExtensionP)
    GET_METHOD_PROTO(extension,optExtensionP)

    extension(optExtensionP existing);

    extension(module     &parent, std::string path, std::string name, params p);
    extension(module     &parent, std::string path, std::string name);

    extension(processor  &parent, std::string path, std::string name, params p);
    extension(processor  &parent, std::string path, std::string name);

    extension(peripheral &parent, std::string path, std::string name, params p);
    extension(peripheral &parent, std::string path, std::string name);

    vlnv *VLNV() { return vlnv::classGet(opObjectVLNV(handle())); }

    optReleaseStatus releaseStatus() { return opObjectReleaseStatus(handle()); }

    optVisibility visibility() { return opObjectVisibility(handle()); }

    //
    // Methods for class extension
    //
    // Return the path to file implementing this extension
    std::string path(void){
        return opExtensionPath(handle());
    }

};

/////////////////////////////////////////// EXTELAB ///////////////////////////////////////////////

class extElab : public object {

public:
    HANDLE_METHOD(optExtElabP)
    GET_METHOD_PROTO(extElab,optExtElabP)

    extElab(optExtElabP existing);

    vlnv *VLNV() { return vlnv::classGet(opObjectVLNV(handle())); }

    command *commandNext(command *prev);
    formal  *formalNext (formal  *prev);

    //
    // Methods for class extElab
    //
    // Return the extension library that this elaborated extension is derived
    // from
    optExtensionP extension(void){
        return opExtElabExtension(handle());
    }

};

/////////////////////////////////////////////// REG ///////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class reg {

public:
    CAST_HANDLE_METHOD(optRegP)
    CAST_CLASS_GET_METHOD(reg,optRegP)

    regGroup *group(void) { return (regGroup*) opRegGroup(handle()); }

    //
    // Methods for class reg
    //
    // Return the access mode enumeration of a processor register
    optRegAccess accessEnum(void){
        return opRegAccessEnum(handle());
    }

    // Return the access mode of a processor register as a string
    std::string accessString(void){
        return opRegAccessString(handle());
    }

    // Return the number of bits in a processor register
    Uns32 bits(void){
        return opRegBits(handle());
    }

    // Return the description of the processor register (from the model)
    std::string description(void){
        return opRegDescription(handle());
    }

    // Return the unique index number of the processor register
    Uns32 index(void){
        return opRegIndex(handle());
    }

    // processor register is an alias of another
    Bool isAlias(void){
        return opRegIsAlias(handle());
    }

    // Return name of a processor register
    std::string name(void){
        return opRegName(handle());
    }

    // Return true if this processor register is read-only
    Bool readOnly(void){
        return opRegReadOnly(handle());
    }

    // Return the usage enumeration of a processor register
    optRegUsage usageEnum(void){
        return opRegUsageEnum(handle());
    }

    // Return the usage of a processor register as a string
    std::string usageString(void){
        return opRegUsageString(handle());
    }

};

//////////////////////////////////////////// REG GROUP ////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class regGroup {
  public:
    CAST_HANDLE_METHOD(optRegGroupP)
    CAST_CLASS_GET_METHOD(regGroup,optRegGroupP)

    //
    // Methods for class regGroup
    //
    // Get name of a processor register group
    std::string name(void){
        return opRegGroupName(handle());
    }

};

///////////////////////////////////// MEMORY MAPPED REGISTER //////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class MMRegister {

  public:
    CAST_HANDLE_METHOD(optMMRegisterP)
    CAST_CLASS_GET_METHOD(MMRegister,optMMRegisterP)

    //
    // Methods for class MMRegister
    //
    // Return the memory mapped register width in bits
    Uns32 bits(void){
        return opMMRegisterBits(handle());
    }

    // Return the memory mapped register description
    std::string description(void){
        return opMMRegisterDescription(handle());
    }

    // Return the register index
    Uns32 index(void){
        return opMMRegisterIndex(handle());
    }

    // Return true if this is a volatile register
    Bool isVolatile(void){
        return opMMRegisterIsVolatile(handle());
    }

    // Return the memory mapped register name
    std::string name(void){
        return opMMRegisterName(handle());
    }

    // Return the memory mapped register offset in bytes
    Addr offset(void){
        return opMMRegisterOffset(handle());
    }

    // Read the given memory mapped peripheral register (with side-effects)
    Bool read(
        void*           data
    ){
        return opMMRegisterRead(handle(),data);
    }

    // Return true if this register can be read
    Bool readable(void){
        return opMMRegisterReadable(handle());
    }

    // Read the given memory mapped peripheral register without side-effects
    Bool view(
        void*           data
    ){
        return opMMRegisterView(handle(),data);
    }

    // Return true if this register can be written
    Bool writable(void){
        return opMMRegisterWritable(handle());
    }

    // Write to the given memory mapped peripheral register (with side-effects)
    Bool write(
        void*           data
    ){
        return opMMRegisterWrite(handle(),data);
    }

};

////////////////////////////////////////////// PARAM //////////////////////////////////////////////

class params : public object {

  private:
    optParamP h;

  public:
    params() { h = 0; }

    // C++ gets confused if value is a string
    void set(std::string name, const char *value) { h = opParamStringSet(h, name.c_str(), value); }
    void set(std::string name, bool        value) { h = opParamBoolSet  (h, name.c_str(), value); }
    void set(std::string name, double      value) { h = opParamDoubleSet(h, name.c_str(), value); }
    void set(std::string name, Int32       value) { h = opParamInt32Set (h, name.c_str(), value); }
    void set(std::string name, Int64       value) { h = opParamInt64Set (h, name.c_str(), value); }
    void set(std::string name, Uns32       value) { h = opParamUns32Set (h, name.c_str(), value); }
    void set(std::string name, Uns64       value) { h = opParamUns64Set (h, name.c_str(), value); }
    void set(std::string name, optEndian   value) { h = opParamEndianSet(h, name.c_str(), value); }
    void set(optEndian value)                     { h = opParamEndianSet(h, "endian",     value); }
    void set(std::string name, void       *value) { h = opParamPtrSet   (h, name.c_str(), value); }

    optParamP handle() { return h; }
};

///////////////////////////////////////// FORMAL ENUM /////////////////////////////////////////////

class formalEnum : public object {
public:
    // return the OP handle
    HANDLE_METHOD(optFormalEnumP);

    // Create a class wrapper only if required
    GET_METHOD_PROTO(formalEnum,optFormalEnumP)

    //
    // Methods for class formalEnum
    //
    // Return the description of a formal parameter enumeration
    std::string description(void){
        return opFormalEnumDescription(handle());
    }

    // Return the integer value of a formal parameter enumeration
    Uns32 value(void){
        return opFormalEnumValue(handle());
    }

};

/////////////////////////////////////////// FORMAL ////////////////////////////////////////////////

class formal : public object {
public:
    // return the OP handle
    HANDLE_METHOD(optFormalP);

    // Create a class wrapper only if required
    GET_METHOD_PROTO(formal,optFormalP)

    formal(optFormalP existing);

    formalEnum *formalEnumNext(formalEnum *prev) {
        return formalEnum::classGet(opFormalEnumNext(handle(), prev->handle()));
    }

    //
    // Methods for class formal
    //
    // Return the boolean formal default value
    Bool boolDefaultValue(void){
        return opFormalBoolDefaultValue(handle());
    }

    // Return the formal parameter description from the descriptor
    std::string description(void){
        return opFormalDescription(handle());
    }

    // Return the formal group from the formal parameter, or null if the formal
    // is not in a group
    optFormalGroupP group(void){
        return opFormalGroup(handle());
    }

    // Return the Int32 formal parameter limits
    Bool int32Limits(
        Int32*          min
       ,Int32*          max
       ,Int32*          dflt
    ){
        return opFormalInt32Limits(handle(),min,max,dflt);
    }

    // Return the Int64 formal parameter limits
    Bool int64Limits(
        Int64*          min
       ,Int64*          max
       ,Int64*          dflt
    ){
        return opFormalInt64Limits(handle(),min,max,dflt);
    }

    // Return the string formal default value
    std::string stringDefaultValue(void){
        return opFormalStringDefaultValue(handle());
    }

    // Return the string formal maximum length
    Uns32 stringMaxLength(void){
        return opFormalStringMaxLength(handle());
    }

    // Return true of this is a system parameter (rather than model specific)
    Bool system(void){
        return opFormalSystem(handle());
    }

    // Return the formal parameter type from the descriptor
    optParamType type(void){
        return opFormalType(handle());
    }

    // Return the formal parameter type from the descriptor as a string
    std::string typeString(void){
        return opFormalTypeString(handle());
    }

    // Return the Uns32 formal parameter limits
    Bool uns32Limits(
        Uns32*          min
       ,Uns32*          max
       ,Uns32*          dflt
    ){
        return opFormalUns32Limits(handle(),min,max,dflt);
    }

    // Return the Uns64 formal parameter limits
    Bool uns64Limits(
        Uns64*          min
       ,Uns64*          max
       ,Uns64*          dflt
    ){
        return opFormalUns64Limits(handle(),min,max,dflt);
    }

    // Return the origin of the value of this formal
    optParameterValueOrigin valueOrigin(void){
        return opFormalValueOrigin(handle());
    }

    // Return the origin of the value of this formal as a string
    std::string valueOriginString(void){
        return opFormalValueOriginString(handle());
    }

    // Return the double formal parameter limits
    Bool doubleLimits(
        double*         min
       ,double*         max
       ,double*         dflt
    ){
        return opFormaldoubleLimits(handle(),min,max,dflt);
    }

};

//////////////////////////////////////////// MODULE ///////////////////////////////////////////////

class module : public object {

  public:
    // regular module instance
    module(module &parent, std::string path, std::string name);
    module(module &parent, std::string path, std::string name, params p);

    // Root module
    module(void);
    module(std::string name);
    module(std::string name, params p);
    module(const char *name, params p);

    // Create a class wrapper for an existing OP instance
    // created by OP (not C++) code
    module(optModuleP existing);

    // return the OP handle
    HANDLE_METHOD(optModuleP);

    // Create a class wrapper only if required
    GET_METHOD_PROTO(module,optModuleP)

    ~module() {
        // if this module class is explicitly deleted, make sure the OP module
        // does not still refer to it, otherwise it will be deleted twice.
        classClr();
    }

    processor* simulate(void);

    void override    (std::string name, Bool        value)  { opParamBoolOverride  (h, name.c_str(), value);         }
    void override    (std::string name, std::string value)  { opParamStringOverride(h, name.c_str(), value.c_str()); }
    void override    (std::string name, double      value)  { opParamDoubleOverride(h, name.c_str(), value);         }
    void override    (std::string name, Int32       value)  { opParamInt32Override (h, name.c_str(), value);         }
    void override    (std::string name, Int64       value)  { opParamInt64Override (h, name.c_str(), value);         }
    void override    (std::string name, Uns32       value)  { opParamUns32Override (h, name.c_str(), value);         }
    void override    (std::string name, Uns64       value)  { opParamUns64Override (h, name.c_str(), value);         }
    void override    (std::string name, optEndian   value)  { opParamEndianOverride(h, name.c_str(), value);         }
    void overrideEnum(std::string name, std::string value)  { opParamEnumOverride  (h, name.c_str(), value.c_str()); }

    Bool        boolValue  (std::string name, bool *set=0) { return opObjectParamBoolValue  (h, name.c_str(), set); }
    double      doubleValue(std::string name, bool *set=0) { return opObjectParamDoubleValue(h, name.c_str(), set); }
    optEndian   endianValue(std::string name, bool *set=0) { return opObjectParamEndianValue(h, name.c_str(), set); }
    Uns32       enumValue  (std::string name, bool *set=0) { return opObjectParamEnumValue  (h, name.c_str(), set); }
    Int32       int32Value (std::string name, bool *set=0) { return opObjectParamInt32Value (h, name.c_str(), set); }
    Int64       int64Value (std::string name, bool *set=0) { return opObjectParamInt64Value (h, name.c_str(), set); }
    Uns32       uns32Value (std::string name, bool *set=0) { return opObjectParamUns32Value (h, name.c_str(), set); }
    Uns64       uns64Value (std::string name, bool *set=0) { return opObjectParamUns64Value (h, name.c_str(), set); }
    void       *ptrValue   (std::string name, bool *set=0) { return opObjectParamPtrValue   (h, name.c_str(), set); }
    std::string stringValue(std::string name)              { return opObjectParamStringValue(h, name.c_str());      }

    formal     *formalNext(formal *prev, optParamClass c=OP_PARAM_ALL) { return formal::classGet(opObjectFormalNext(h, prev->handle(), c)); }

    module    *parent(void) {  return classGet((optModuleP)opVoidParent(h)); }

    std::string name() { return opObjectName(h); }

    // ByName methods to find contents of this module
    bridge       *bridgeByName    (std::string name);
    memory       *memoryByName    (std::string name);
    MMC          *MMCByName       (std::string name);
    module       *moduleByName    (std::string name);
    peripheral   *peripheralByName(std::string name);
    processor    *processorByName (std::string name);

    bus          *busByName       (std::string name);
    FIFO         *FIFOByName      (std::string name);
    net          *netByName       (std::string name);
    packetnet    *packetnetByName (std::string name);
    busPort      *busPortByName   (std::string name);
    netPort      *netPortByName   (std::string name);

    // Iterators of module contents
    bridge      *bridgeNext       (bridge     *prev);
    memory      *memoryNext       (memory     *prev);
    MMC         *MMCNext          (MMC        *prev);
    module      *moduleNext       (module     *prev);
    peripheral  *peripheralNext   (peripheral *prev);
    processor   *processorNext    (processor  *prev);

    bus         *busNext          (bus        *prev);
    FIFO        *FIFONext         (FIFO       *prev);
    net         *netNext          (net        *prev);
    packetnet   *packetnetNext    (packetnet  *prev);

    busPort           *busPortNext      (busPort          *prev);
    FIFOPort          *FIFOPortNext     (FIFOPort         *prev);
    netPort           *netPortNext      (netPort          *prev);
    packetnetPort     *packetnetPortNext(packetnetPort    *prev);

    busPortConn       *busPortConnNext      (busPortConn       *prev);
    FIFOPortConn      *FIFOPortConnNext     (FIFOPortConn      *prev);
    netPortConn       *netPortConnNext      (netPortConn       *prev);
    packetnetPortConn *packetnetPortConnNext(packetnetPortConn *prev);

    void debuggerNotifiersAdd(optDebuggerNotifiersP n) { opSessionDebuggerNotifiersAdd(handle(), n); }

    vlnv *VLNV() { return vlnv::classGet(opObjectVLNV(handle())); }

    docNode *docNodeNext(docNode *prev);
    docNode *docSectionAdd(std::string name);

    // Request a C callback after a given time
    // Refer to class moduleTrigger for a C++ solution
    
    triggerEvent *triggerAdd(optTime t, optTriggerFn cb, void *userData) {
        return triggerEvent::classGet(opModuleTriggerAdd(handle(), t, cb, userData));
    }

    void triggerDelete(triggerEvent *t) {
        opModuleTriggerDelete(handle(), t->handle());
    }

    watchpoint *watchpointNext();

    std::string stopReasonString(void) {
        optStopReason sr = opRootModuleStopReason(handle());
        return opStopReasonString(sr);
    }

    const char *commandCall(const char *command, Uns32 argc, const char *argv[]) {
        return opCommandStringCall(handle(), command, argc, argv);
    }

    command *commandByName (std::string name);

    optSimulatorPhase phase(void) { return opObjectSimulatorPhase(handle()); }

    std::string phaseString(void) { return opObjectSimulatorPhaseString(handle()); }

    bool saveRestoreSupported() { return opObjectSaveRestoreSupported(handle()); }

    optReleaseStatus releaseStatus() { return opObjectReleaseStatus(handle()); }

    optVisibility visibility() { return opObjectVisibility(handle()); }

    octHTTPChannelP HTTPOpen (octHTTPMethodsP methods, Uns32 portNum, const char *fileRoot) {
        return opModuleHTTPOpen(handle(), methods, portNum, fileRoot);
    }

    //
    // Methods for class module
    //
    // Return the time of the next scheduled event. Note that a new event could
    // be scheduled during this period
    optTime eventTimeNext(void){
        return opEventTimeNext(handle());
    }

    // Inform the simulator that the given native region has changed value so
    // that the JIT simulator can invalidate any code cached from this region.
    void memoryNativeFlush(
        const void*     base
       ,UnsPS           bytes
    ){
        opMemoryNativeFlush(handle(),base,bytes);
    }

    // Display all the buses in the given module. Refer also to opBusShow.
    void busShow(void){
        opModuleBusShow(handle());
    }

    // Display a summary of all commands installed in models in the given module
    // (and sub-modules)
    void commandsShow(void){
        opModuleCommandsShow(handle());
    }

    // Return the current time of the simulation that contains this module
    // instance,
    optTime currentTime(void){
        return opModuleCurrentTime(handle());
    }

    // Set the diagnostic level in the given module (if the module supports this
    // operation). Values > 15 will also turn on system diagnostics.
    void diagnosticLevelSet(
        Uns32           level
    ){
        opModuleDiagnosticLevelSet(handle(),level);
    }

    // Print a report of each of the domains in the given module.
    void domainDebug(void){
        opModuleDomainDebug(handle());
    }

    // Signal that this module wants to terminate the session
    void finish(
        Int32           status
    ){
        opModuleFinish(handle(),status);
    }

    // Return the finish status of this root module
    Int32 finishStatus(void){
        return opModuleFinishStatus(handle());
    }

    // Display all the formal parameters (overrides) of all models, modules and
    // sub-modules starting with the given module.
    void formalsShow(
        optParamClass   paramClass
    ){
        opModuleFormalsShow(handle(),paramClass);
    }

    // Return the file path to the object that implements this module
    std::string path(void){
        return opModulePath(handle());
    }

    // Return the purpose of this module. Purpose is a string used by product
    // packaging tools.
    optPurpose purpose(void){
        return opModulePurpose(handle());
    }

    // Display a summary all modules, sub-modules, models, formals and actual
    // parameters.
    void show(void){
        opModuleShow(handle());
    }

    // Return the simulation time slice size (used by opRootModuleSimulate).
    // Note that this function cannot give a correct value until all models have
    // been elaborated.
    optTime getSimulationTimeSlice(void){
        return opRootModuleGetSimulationTimeSlice(handle());
    }

    // This function can be called on a root module before opRootModuleSimulate.
    // It performs all actions after elaboration but before simulation.
    void postElaborate(void){
        opRootModulePostElaborate(handle());
    }

    // This function can be called on a root module before opSessionTerminate.
    // Performs end-of-simulation actions without destroying the platform.
    void postSimulate(void){
        opRootModulePostSimulate(handle());
    }

    // This function can be called on a root module before opRootModuleSimulate.
    // It runs the start-of-simulation but returns before running any
    // application processors.
    void preSimulate(void){
        opRootModulePreSimulate(handle());
    }

    // Set the stop time (for opRootModuleSimulate). The call takes effect at
    // the end of the current time slice. When this time expires the simulator
    // will return control to the debugger, if attached.
    Bool setDebugStopTime(
        optTime         newStopTime
    ){
        return opRootModuleSetDebugStopTime(handle(),newStopTime);
    }

    // Set a seed for randomizing the order in which processors are processed a
    // time slice. The default is no randomization (seed=0).
    void setSimulationRandomSeed(
        Uns32           lfsrSeed
    ){
        opRootModuleSetSimulationRandomSeed(handle(),lfsrSeed);
    }

    // Set the simulation stop time (for opRootModuleSimulate). This takes
    // effect at the end of any current time slice. opRootModuleSimulate will
    // return when this time is reached
    Bool setSimulationStopTime(
        optTime         newStopTime
    ){
        return opRootModuleSetSimulationStopTime(handle(),newStopTime);
    }

    // Set the simulation time precision - all event times are rounded to this.
    Bool setSimulationTimePrecision(
        optTime         precision
    ){
        return opRootModuleSetSimulationTimePrecision(handle(),precision);
    }

    // Set the simulation time slice size (used by opRootModuleSimulate). The
    // call takes effect at the end of the current time slice.
    Bool setSimulationTimeSlice(
        optTime         newSliceSize
    ){
        return opRootModuleSetSimulationTimeSlice(handle(),newSliceSize);
    }

    // When running in wallclock mode (wallclock specified), this gives the
    // maximum multiple of real time at which the simulation should run. The
    // default is 1.0, implying no faster than real time. An value of 2.0
    // implies no faster than twice real time; a value of 0.5 implies no faster
    // than half realtime
    double setWallClockFactor(
        double          factor
    ){
        return opRootModuleSetWallClockFactor(handle(),factor);
    }

    // Restore the state of the given module and its hierarchy by calling the
    // given callback one or more times
    optSaveRestoreStatus stateRestore(
        optRestoreFn    cb
       ,void *          userData
    ){
        return opRootModuleStateRestore(handle(),cb,userData);
    }

    // Restore the state of the given module and its hierarchy from a file
    optSaveRestoreStatus stateRestoreFile(
        const char *    file
    ){
        return opRootModuleStateRestoreFile(handle(),file);
    }

    // Save the state of the given module and its hierarchy by calling the given
    // callback one or more times
    optSaveRestoreStatus stateSave(
        optSaveFn       cb
       ,void *          userData
    ){
        return opRootModuleStateSave(handle(),cb,userData);
    }

    // Save the state of the given module and its hierarchy to a file
    optSaveRestoreStatus stateSaveFile(
        const char *    file
    ){
        return opRootModuleStateSaveFile(handle(),file);
    }

    // Return the reason why simulation stopped after a previous call to
    // opProcessorSimulate() or opRootModuleSimulate().
    optStopReason stopReason(void){
        return opRootModuleStopReason(handle());
    }

    // Move time forward for this platform, processing any pending events due in
    // the period since the last call to this function. Pending events include
    // delays scheduled in peripheral models, time-triggered callbacks in OP
    // platform code, finish-time
    Bool timeAdvance(
        optTime         absoluteTime
    ){
        return opRootModuleTimeAdvance(handle(),absoluteTime);
    }

};

///////////////////////////////////////////// MONITOR////////////////////////////////////////////////

class monitor {
  private:
    static OP_MONITOR_FN(notifier);
    bool write;
    Addr hi;
    Addr lo;
    processor *proc;
    bus       *bs;
    memory    *mem;
    
  public:
    monitor(processor &p,            bool write, Addr lo, Addr hi);
    monitor(bus &b, processor &p,    bool write, Addr lo, Addr hi);
    monitor(bus &b,                  bool write, Addr lo, Addr hi);
    monitor(memory &m, processor &p, bool write, Addr lo, Addr hi);
    monitor(memory &m,               bool write, Addr lo, Addr hi);

    virtual ~monitor();

  protected:
    virtual void triggered(processor *p, Addr PA, Addr VA, Uns32 bytes, const void *data);
};

///////////////////////////////////////////// BRIDGE ////////////////////////////////////////////////

class bridge : public object {

  public:
    bridge(module &parent, std::string name, params p);

    bridge(module &parent, std::string name);

    EXISTING_CONSTRUCTOR_PROTO(bridge, optBridgeP);

    HANDLE_METHOD(optBridgeP);

    GET_METHOD_PROTO(bridge, optBridgeP);
};


/////////////////////////////////////////// PROCESSOR ///////////////////////////////////////////////

/// loader controls can be combined using the "|" operator

static inline optLoaderControls    operator| (optLoaderControls lhs, optLoaderControls rhs) {
    return (optLoaderControls) ((Uns32)lhs | (Uns32)rhs);
}

class processor : public object {

public:

    processor(module &parent, std::string path, std::string name);

    processor(module &parent, std::string path, std::string name, params p);

    EXISTING_CONSTRUCTOR_PROTO(processor, optProcessorP);

    HANDLE_METHOD(optProcessorP);

    GET_METHOD_PROTO(processor, optProcessorP)

    std::string name() { return opObjectName(h); }

    application *applicationLoad(std::string path, optLoaderControls ctrl = OP_LDR_DEFAULT, Addr offset = 0) {
        optApplicationP r = opProcessorApplicationLoad(handle(), path.c_str(), ctrl, offset);
        return application::classGet(r);
    }

    application *applicationRead(std::string path, optLoaderControls ctrl, Addr offset, ordCallbacksP cb, void *userData) {
        optApplicationP r = opProcessorApplicationRead(handle(), path.c_str(), ctrl, offset, cb, userData);
        return application::classGet(r);
    }

    bool isLeaf(void) {
        return opProcessorIsLeaf(handle());
    }

    reg *regNext(reg *prev) {
        optRegP r  = opProcessorRegNext(handle(), prev->handle());
        return reg::classGet(r);
    }

    reg *regByName(std::string name) {
        optRegP r  = opProcessorRegByName(handle(), name.c_str());
        return reg::classGet(r);
    }

    reg *regByUsage(optRegUsage usage) {
        optRegP r  = opProcessorRegByUsage(handle(), usage);
        return reg::classGet(r);
    }

    reg *regByIndex(Uns32 index) {
        optRegP r  = opProcessorRegByIndex(handle(), index);
        return reg::classGet(r);
    }

    regGroup *regGroupNext(regGroup *prev) {
        optRegGroupP r  = opProcessorRegGroupNext(handle(), prev->handle());
        return regGroup::classGet(r);
    }

    regGroup *regGroupByName(std::string name) {
        optRegGroupP r  = opProcessorRegGroupByName(handle(), name.c_str());
        return regGroup::classGet(r);
    }

    reg *regGroupRegNext(regGroup *group, reg *prev) {
        optRegP r = opRegGroupRegNext(handle(), group->handle(), prev->handle());
        return reg::classGet(r);
    }

    bool regRead(reg *r, void *buffer) {
        return opProcessorRegRead(handle(), r->handle(), buffer);
    }

    bool regWrite(reg *r, void *buffer) {
        return opProcessorRegWrite(handle(), r->handle(), buffer);
    }

    bool regRead(std::string name, void *buffer) {
        return opProcessorRegReadByName(handle(), name.c_str(), buffer);
    }

    bool regWrite(std::string name, void *buffer) {
        return opProcessorRegWriteByName(handle(), name.c_str(), buffer);
    }

    Uns64 clocksUntilTime(double endTime) {
        return opProcessorClocksUntilTime(handle(), endTime);
    }

    std::string disassemble(Addr addr ,optDisassAttrs attrs = OP_DSA_NORMAL){
        return opProcessorDisassemble(handle(), addr, attrs);
    }

    busPort      *busPortByName   (std::string name);
    netPort      *netPortByName   (std::string name);

    busPortConn  *busPortConnNext(busPortConn *prev);
    busPort      *busPortNext(busPort *prev);
    netPortConn  *netPortConnNext(netPortConn *prev);
    netPort      *netPortNext(netPort *prev);
    FIFOPortConn *FIFOPortConnNext(FIFOPortConn *prev);
    FIFOPort     *FIFOPortNext(FIFOPort *prev);

    static processor *current(void) {
        return classGet(opProcessorCurrent());
    }

    vlnv *VLNV() { return vlnv::classGet(opObjectVLNV(handle())); }

    docNode *docNodeNext(docNode *prev);

    exception *exceptionNext(exception *prev);
    exception *exceptionCurrent(void);

    mode *modeNext (mode *prev);
    mode *modeCurrent(void);

    std::string stopReasonString(void) {
        optStopReason sr = opProcessorStopReason(handle());
        return opStopReasonString(sr);
    }

    command *commandNext(command *prev);

    vlnv *DefaultSemihost(void);
    vlnv *Helper(void);
    vlnv *DebugHelper(void);

    application *applicationNext(application *prev) {
        return application::classGet(opObjectApplicationNext(handle(), prev->handle()));
    }

    watchpoint *accessWatchpointNew(Addr lo, Addr hi, bool ph, void *userData, optAddrWatchpointConditionFn notifierCB);

    watchpoint *readWatchpointNew  (Addr lo, Addr hi, bool ph, void *userData, optAddrWatchpointConditionFn notifierCB);

    watchpoint *writeWatchpointNew (Addr lo, Addr hi, bool ph, void *userData, optAddrWatchpointConditionFn notifierCB);

    watchpoint *modeWatchpointNew  (void *userData, optProcWatchpointConditionFn notifierCB);

    watchpoint *exceptionWatchpointNew(void *userData, optProcWatchpointConditionFn notifierCB);

    extension *extensionNext(extension *prev) {
        return extension::classGet(opObjectExtensionNext(handle(), prev ? prev->handle(): 0));
    }

    extElab *extElabNext(extElab *prev) {
        return extElab::classGet(opObjectExtElabNext(handle(), prev ? prev->handle(): 0));
    }

    bool saveRestoreSupported() { return opObjectSaveRestoreSupported(handle()); }

    optReleaseStatus releaseStatus() { return opObjectReleaseStatus(handle()); }

    formal *formalNext(formal *prev, optParamClass c=OP_PARAM_ALL) { return formal::classGet(opObjectFormalNext(h, prev->handle(), c)); }

    optVisibility visibility() { return opObjectVisibility(handle()); }

    //
    // Methods for class processor
    //
    // If the subject is a multi-core processor, this function must be applied
    // to the root. Returns true if this processor is an asymmetric
    // multiprocessor, according to the processor information supplied by the
    // model.
    Bool AMP(void){
        return opProcessorAMP(handle());
    }

    // (no longer used)
    std::string alternateName(void){
        return opProcessorAlternateName(handle());
    }

    // Use the installed readers to load an application via a processor. This
    // route can also set the PC of the processor to the application entry point
    // and can associate the applications symbol tables with the processor to
    // allow symbolic interception of functions, and disassembly of labels.
    optApplicationP applicationLoad(
        const char*     path
       ,optLoaderControls controls
       ,Addr            loadOffset
    ){
        return opProcessorApplicationLoad(handle(),path,controls,loadOffset);
    }

    // Read the specified application file, but instead of loading the code,
    // call the user's callbacks for each region found. This allows the user to
    // use the contents of an object file without re-writing the object loader.
    optApplicationP applicationRead(
        const char*     path
       ,optLoaderControls controls
       ,Addr            loadOffset
       ,ordCallbacksP   cbs
       ,void*           userData
    ){
        return opProcessorApplicationRead(handle(),path,controls,loadOffset,cbs,userData);
    }

    // Add a mapping from an address to a symbol for the application running on
    // the given processor. This function can be used when the application is
    // not loaded from an ELF file (which contains symbol mappings), or when the
    // application program file has no symbols.
    void applicationSymbolAdd(
        const char *    name
       ,Addr            value
       ,Addr            size
       ,ordSymbolType   type
       ,ordSymbolBinding binding
    ){
        opProcessorApplicationSymbolAdd(handle(),name,value,size,type,binding);
    }

    // Clear a breakpoint from the given address.
    void breakpointAddrClear(
        Addr            addr
    ){
        opProcessorBreakpointAddrClear(handle(),addr);
    }

    // Set an instruction breakpoint on the given processor. If the processor
    // fetches an instruction from the given address, the simulator will stop
    // immediately BEFORE the instruction is executed. and return to the caller.
    // The optStopReason will be OP_SR_BP_ADDRESS.
    void breakpointAddrSet(
        Addr            addr
    ){
        opProcessorBreakpointAddrSet(handle(),addr);
    }

    // Clear the ICount breakpoint from the given processor.
    void breakpointICountClear(void){
        opProcessorBreakpointICountClear(handle());
    }

    // Stop this processor after this many more instructions.
    void breakpointICountSet(
        Uns64           delta
    ){
        opProcessorBreakpointICountSet(handle(),delta);
    }

    // Return the first child of the given SMP processor or null if there are no
    // children.
    processor* child(void){
        return classGet(opProcessorChild(handle()));
    }

    // Return the total number of instructions and halted instructions executed
    // by the given processor
    Uns64 clocks(void){
        return opProcessorClocks(handle());
    }

    // Return how many more clocks this processor will execute until the given
    // time
    Uns64 clocksUntilTime(
        optTime         time
    ){
        return opProcessorClocksUntilTime(handle(),time);
    }

    // Return the exact number of instructions executed by the given processor
    // since the beginning of the simulation.
    Uns64 cycleCount(void){
        return opProcessorCycleCount(handle());
    }

    // Mark this processor to be attached to the debugger
    void debug(void){
        opProcessorDebug(handle());
    }

    // Return the cumulative delay for this processor
    optTime delay(void){
        return opProcessorDelay(handle());
    }

    // This function indicates that the current processor should do nothing for
    // a number of clocks corresponding to the given delay. The purpose of this
    // is to enable after-the-event timing emulation.
    void delayAdd(
        optTime         time
    ){
        opProcessorDelayAdd(handle(),time);
    }

    // This function sets an external de-rate factor for a processor (0-100%,
    // default 0%). This enables the simulation environment to indicate that the
    // processor should execute at a reduced percentage of its configured MIPS
    // rate. This is necessary for the platform to be able to simulate the
    // effect of reduced-rate clocking, for example.
    void derate(
        double          factor
    ){
        opProcessorDerate(handle(),factor);
    }

    // Return a description of this processor
    std::string description(void){
        return opProcessorDescription(handle());
    }

    // Fills an array with the ELF codes supported by this processor.
    Uns32 elfCodes(
        Uns32*          codes
       ,Uns32           maxCodes
       ,Bool*           defaultElf
    ){
        return opProcessorElfCodes(handle(),codes,maxCodes,defaultElf);
    }

    // Return the current endian configuration of the given processor. If the
    // processor can have different code and data endian configurations, then
    // the data argument is used to select which endian is queried.
    optEndian endian(
        Bool            data
    ){
        return opProcessorEndian(handle(),data);
    }

    // Terminate execution of the current processor and return immediately from
    // opProcessorSimulate with optStopReason OP_SR_EXIT. If they exists, other
    // processors can continue simulation
    void exit(void){
        opProcessorExit(handle());
    }

    // Return the family name of this processor.
    std::string family(void){
        return opProcessorFamily(handle());
    }

    // Return by reference the fault address of the given processor. Following
    // an exception, when the simulator has returned to the caller, this
    // function finds the address at which the exception occurred. The exception
    // address could be where the processor was executing, or a data value being
    // read or written.
    Bool faultAddress(
        Addr*           address
    ){
        return opProcessorFaultAddress(handle(),address);
    }

    // Add a fetch callback to the given address range on a processor. This
    // function should be used as a passive monitor, rather than as part of the
    // platform.
    void fetchMonitorAdd(
        Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opProcessorFetchMonitorAdd(handle(),addrLo,addrHi,rcb,userData);
    }

    // Remove a fetch callback from the given address range on a processor if it
    // exists
    void fetchMonitorDelete(
        Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opProcessorFetchMonitorDelete(handle(),addrLo,addrHi,rcb,userData);
    }

    // Terminate execution of the simulation and return immediately from
    // opProcessorSimulate or opRootModuleSimulate with optStopReason
    // OP_SR_FINISH.
    void finish(
        Int32           status
    ){
        opProcessorFinish(handle(),status);
    }

    // Signal that code memory has been changed and that the processor should
    // invalidate cached JIT translations
    void flush(
        Addr            addrLo
       ,Addr            addrHi
    ){
        opProcessorFlush(handle(),addrLo,addrHi);
    }

    // Following this function call, the given processor will not be scheduled
    // to run any instructions until opProcessorUnfreeze is called. If queried,
    // the stop reason will be OP_SR_FREEZE.
    void freeze(void){
        opProcessorFreeze(handle());
    }

    // Indicate if this processor is in the frozen state.
    Bool frozen(void){
        return opProcessorFrozen(handle());
    }

    // Processor models that have a GDB that works with the model and is shipped
    // with this product, and requires specific flags to be passed to the GDB
    // which is starts, have these flags embedded in the model. This function
    // returns the flags as a string. Processor models that require different
    // flags according to their configuration will return the correct flags via
    // this function.
    std::string gdbFlags(void){
        return opProcessorGdbFlags(handle());
    }

    // Processor models that have a GDB that works with the model and is shipped
    // with this product, have the path to the GDB embedded in the model. This
    // function returns the path to this GDB. Processor models that require
    // different GDBs according to their configuration will return the correct
    // GDB via this function.
    std::string gdbPath(void){
        return opProcessorGdbPath(handle());
    }

    // Return the group name of this processor.
    std::string groupH(void){
        return opProcessorGroupH(handle());
    }

    // Return the group name of this processor.
    std::string groupL(void){
        return opProcessorGroupL(handle());
    }

    // Halt execution of the current processor and return immediately from
    // opProcessorSimulate with the optStopReason OP_SR_HALT
    void halt(void){
        opProcessorHalt(handle());
    }

    // Return the total number of instructions executed by the given processor
    // since the beginning of the simulation.
    Uns64 ICount(void){
        return opProcessorICount(handle());
    }

    // Return the index number of the passed SMP processor. Each processor in
    // the cluster is guaranteed a unique index number
    Uns32 index(void){
        return opProcessorIndex(handle());
    }

    // Return the number of bytes in the instruction at the given address
    Uns32 instructionBytes(
        Addr            addr
    ){
        return opProcessorInstructionBytes(handle(),addr);
    }

    // Returns true if this processor always requires the use of physical
    // addresses.
    Bool loadPhysical(void){
        return opProcessorLoadPhysical(handle());
    }

    // Return the current value of the PC of a processor
    Addr PC(void){
        return opProcessorPC(handle());
    }

    // Return the current value of the PC and the delay slot offset. Refer to
    // the VMI processor documentation for a description of the delay slot.
    Addr PCDS(
        Uns8*           delay
    ){
        return opProcessorPCDS(handle(),delay);
    }

    // Query if the PC of the given processor is in a delay slot
    Bool PCInDS(void){
        return opProcessorPCInDS(handle());
    }

    // Return the address of the instruction following the instruction at the
    // given address.
    Addr PCNext(
        Addr            pc
    ){
        return opProcessorPCNext(handle(),pc);
    }

    // Set the current PC of a processor. This is the first address to be
    // executed when simulation proceeds.
    void PCSet(
        Addr            addr
    ){
        opProcessorPCSet(handle(),addr);
    }

    // Return the parent of the given SMP processor or null if there is no
    // parent.
    processor* parent(void){
        return classGet(opProcessorParent(handle()));
    }

    // Returns the path to the file that implements the processor model
    std::string path(void){
        return opProcessorPath(handle());
    }

    // Return True if this processor does support QuantumLeap mode
    Bool QLQualified(void){
        return opProcessorQLQualified(handle());
    }

    // Read memory using virtual address in processor context.
    Bool read(
        Addr            simAddress
       ,void*           buffer
       ,Uns32           objectSize
       ,Uns32           objects
       ,Bool            debugAccess
       ,optHostEndian   hostEndian
    ){
        return opProcessorRead(handle(),simAddress,buffer,objectSize,objects,debugAccess,hostEndian);
    }

    // Abort the current read access.
    void readAbort(
        Addr            addr
    ){
        opProcessorReadAbort(handle(),addr);
    }

    // Add a read callback to the given address range on a processor. This
    // function should be used as a passive monitor, rather than as part of the
    // platform.
    void readMonitorAdd(
        Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opProcessorReadMonitorAdd(handle(),addrLo,addrHi,rcb,userData);
    }

    // Remove a read callback from the given address range on a processor if it
    // exists
    void readMonitorDelete(
        Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opProcessorReadMonitorDelete(handle(),addrLo,addrHi,rcb,userData);
    }

    // Print all the registers of the given processor. If the model has its own
    // print routine, this will be used, otherwise it will print the contents of
    // four registers per line.
    void regDump(void){
        opProcessorRegDump(handle());
    }

    // Return the next sibling in this cluster of the given processor
    processor* siblingNext(void){
        return classGet(opProcessorSiblingNext(handle()));
    }

    // Return the previous sibling of the given SMP processor
    processor* siblingPrevious(void){
        return classGet(opProcessorSiblingPrevious(handle()));
    }

    // Simulate a processor for a number of clocks.
    optStopReason simulate(
        Uns64           clocks
    ){
        return opProcessorSimulate(handle(),clocks);
    }

    // Return the count of skipped cycles for the processor. The type argument
    // indicates whether the count should be committed skipped cycles, pending
    // skipped cycles, or the total of committed and pending skipped cycles.
    Uns64 skipCycles(
        optCycleSkipType type
    ){
        return opProcessorSkipCycles(handle(),type);
    }

    // This function indicates that the current processor should do nothing for
    // the given number of clocks. The purpose of this is to enable
    // after-the-event timing emulation.
    void skipCyclesAdd(
        Uns64           skipCount
       ,Bool            defer
    ){
        opProcessorSkipCyclesAdd(handle(),skipCount,defer);
    }

    // Restore the state of the given processor by calling the callback one or
    // more times. The callback must return the data in the same size chunks as
    // it was saved. The userData passed to the callback should be used to refer
    // to the state of the storage mechanism.
    optSaveRestoreStatus stateRestore(
        optRestoreFn    cb
       ,void *          userData
    ){
        return opProcessorStateRestore(handle(),cb,userData);
    }

    // Restore the state of the given processor from a file
    optSaveRestoreStatus stateRestoreFile(
        const char *    file
    ){
        return opProcessorStateRestoreFile(handle(),file);
    }

    // Save the state of the given processor by calling the callback one or more
    // times. The callback decides how the data is stored. The userData passed
    // to the callback should be used to refer to the state of the storage
    // mechanism.
    optSaveRestoreStatus stateSave(
        optSaveFn       cb
       ,void *          userData
    ){
        return opProcessorStateSave(handle(),cb,userData);
    }

    // Save the state of the given processor to a file
    optSaveRestoreStatus stateSaveFile(
        const char *    file
    ){
        return opProcessorStateSaveFile(handle(),file);
    }

    // Install a callback to be called when a processor stops for an exception.
    void stopHandlerAdd(
        optStopHandlerFn stopHandler
       ,void*           userData
    ){
        opProcessorStopHandlerAdd(handle(),stopHandler,userData);
    }

    // Remove a callback that was called when a processor stops for an
    // exception.
    void stopHandlerDelete(
        optStopHandlerFn stopHandler
       ,void*           userData
    ){
        opProcessorStopHandlerDelete(handle(),stopHandler,userData);
    }

    // Return the reason why the given processor stopped after a previous
    // simulation using opProcessorSimulate() or opRootModuleSimulate(). The
    // stop reason is valid only for leaf level processors or an MT group:
    // processor objects that are containers of independently-executable cores
    // always return a stopReason of OP_SR_SCHED, because each of the sub-cores
    // may have a different stopReason.
    optStopReason stopReason(void){
        return opProcessorStopReason(handle());
    }

    // Return the processor local view of time (configured MIPS rate * current
    // clocks)
    optTime time(void){
        return opProcessorTime(handle());
    }

    // Disable the processor trace buffer.
    void traceBufferDisable(void){
        opProcessorTraceBufferDisable(handle());
    }

    // Print the processor trace buffer contents (if it is enabled).
    void traceBufferDump(void){
        opProcessorTraceBufferDump(handle());
    }

    // Enable the processor trace buffer. The trace buffer records the last 512
    // instructions executed. Simulation is much slower with trace buffer
    // enabled, but much faster than with tracing enabled.
    void traceBufferEnable(void){
        opProcessorTraceBufferEnable(handle());
    }

    // Trace only instructions with this PC or lower.
    void traceHighPCSet(
        Addr            delta
    ){
        opProcessorTraceHighPCSet(handle(),delta);
    }

    // Trace only instructions with this PC or higher.
    void traceLowPCSet(
        Addr            delta
    ){
        opProcessorTraceLowPCSet(handle(),delta);
    }

    // Turn off processor tracing after it has executed the given number of
    // instructions.
    void traceOffAfter(
        Uns64           delta
    ){
        opProcessorTraceOffAfter(handle(),delta);
    }

    // Turn on processor tracing after it has executed the given number of
    // instructions.
    void traceOnAfter(
        Uns64           delta
    ){
        opProcessorTraceOnAfter(handle(),delta);
    }

    // Following this function call, the given processor will be scheduled
    // normally. If as a result of being in the frozen state, this processor has
    // executed fewer instructions than other processors, it will be scheduled
    // to run until it has caught up, thus minimizing any disturbance caused by
    // the use of opProcessorFreeze.
    void unfreeze(void){
        opProcessorUnfreeze(handle());
    }

    // Return the variant of the given processor .
    std::string variant(void){
        return opProcessorVariant(handle());
    }

    // Write memory using virtual address in processor context.
    Bool write(
        Addr            simAddress
       ,const void*     buffer
       ,Uns32           objectSize
       ,Uns32           objects
       ,Bool            debugAccess
       ,optHostEndian   hostEndian
    ){
        return opProcessorWrite(handle(),simAddress,buffer,objectSize,objects,debugAccess,hostEndian);
    }

    // Abort the current write access
    void writeAbort(
        Addr            addr
    ){
        opProcessorWriteAbort(handle(),addr);
    }

    // Add a write callback to the given address range on a processor. This
    // function should be used as a passive monitor, rather than as part of the
    // platform.
    void writeMonitorAdd(
        Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opProcessorWriteMonitorAdd(handle(),addrLo,addrHi,rcb,userData);
    }

    // Remove a write callback from the given address range on a processor if it
    // exists
    void writeMonitorDelete(
        Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opProcessorWriteMonitorDelete(handle(),addrLo,addrHi,rcb,userData);
    }

    // Suspend execution of the current processor and return immediately from
    // opProcessorSimulate with optStopReason OP_SR_YIELD
    void yield(void){
        opProcessorYield(handle());
    }


};

/////////////////////////////////////////// PERIPHERAL ///////////////////////////////////////////////

class peripheral : public object {

public:
    peripheral(module &parent, std::string path, std::string name, params p);
    peripheral(module &parent, std::string path, std::string name);

    // Peripheral that already exists in OP
    EXISTING_CONSTRUCTOR_PROTO(peripheral, optPeripheralP);

    // Create a class wrapper only if required
    GET_METHOD_PROTO(peripheral, optPeripheralP)

    HANDLE_METHOD(optPeripheralP)

    bool addPortMapCB(std::string portName, optPortMapFn cb, void *userData);

    busPortConn       *busPortConnNext      (busPortConn *prev);
    busPort           *busPortNext          (busPort     *prev);
    netPortConn       *netPortConnNext      (netPortConn *prev);
    netPort           *netPortNext          (netPort *prev);
    packetnetPortConn *packetnetPortConnNext(packetnetPortConn *prev);
    packetnetPort     *packetnetPortNext    (packetnetPort *prev);

    busPort           *busPortByName        (std::string name);
    netPort           *netPortByName        (std::string name);

    vlnv *VLNV() { return vlnv::classGet(opObjectVLNV(handle())); }

    docNode *docNodeNext(docNode *prev);

    std::string stopReasonString(void) {
        optStopReason sr = opPeripheralStopReason(handle());
        return opStopReasonString(sr);
    }

    bool saveRestoreSupported() { return opObjectSaveRestoreSupported(handle()); }

    optReleaseStatus releaseStatus() { return opObjectReleaseStatus(handle()); }

    formal     *formalNext(formal *prev, optParamClass c=OP_PARAM_ALL) { return formal::classGet(opObjectFormalNext(h, prev->handle(), c)); }

    optVisibility visibility() { return opObjectVisibility(handle()); }

    //
    // Methods for class peripheral
    //
    // Mark this peripheral to be attached to the debugger
    void debug(void){
        opPeripheralDebug(handle());
    }

    // Set the diagnostic level on the given peripheral. Refer to the OVP
    // Peripheral Modeling Guide.
    void diagnosticLevelSet(
        Uns32           level
    ){
        opPeripheralDiagnosticLevelSet(handle(),level);
    }

    // Return the path to the file that implements the peripheral model
    std::string path(void){
        return opPeripheralPath(handle());
    }

    // Notify when a serial connection is made
    void serialNotify(
        optSerialOpenFn cb
       ,void*           userData
    ){
        opPeripheralSerialNotify(handle(),cb,userData);
    }

    // Return the reason why the given peripheral stopped
    optStopReason stopReason(void){
        return opPeripheralStopReason(handle());
    }

};

/////////////////////////////////////////// MEMORY ///////////////////////////////////////////////

class memory : public object {

public:
    memory(module &parent, std::string name, Addr maxAddress, optPriv priv, params p);
    memory(module &parent, std::string name, Addr maxAddress, optPriv priv = OP_PRIV_RWX);
    memory(module &parent, std::string name, Addr maxAddress, void *native, optPriv priv = OP_PRIV_RWX);
    memory(module &parent, std::string name, Addr maxAddress, void *native, optPriv priv, params p);

    // Memory that already exists in OP
    EXISTING_CONSTRUCTOR_PROTO(memory, optMemoryP);

    // Create a class wrapper only if required
    GET_METHOD_PROTO(memory, optMemoryP)

    HANDLE_METHOD(optMemoryP)

    busPortConn *busPortConnNext(busPortConn *prev);

    busPort     *busPortNext(busPort *prev);

    application *applicationNext(application *prev) {
        return application::classGet(opObjectApplicationNext(handle(), prev->handle()));
    }
    //
    // Methods for class memory
    //
    // Load an application program into a memory using the installed program
    // loaders. All simulators will load ELF files, whereas some basic products
    // cannot load COFF. The user's own application program loaders can be
    // installed prior to calling this function.
    optApplicationP applicationLoad(
        const char*     path
       ,optLoaderControls controls
       ,Addr            loadOffset
    ){
        return opMemoryApplicationLoad(handle(),path,controls,loadOffset);
    }

    // Add a fetch callback to the given address range on a memory. This
    // function should be used as a passive monitor, rather than as part of the
    // platform.
    void fetchMonitorAdd(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opMemoryFetchMonitorAdd(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Delete a fetch callback from the given address range on a memory if it
    // exists
    void fetchMonitorDelete(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opMemoryFetchMonitorDelete(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Signal that code memory has been changed and that any processors using
    // the given address range should invalidate cached JIT translations
    void flush(
        Addr            addrLo
       ,Addr            addrHi
    ){
        opMemoryFlush(handle(),addrLo,addrHi);
    }

    // Return the memory's maximum (byte) address. This is one byte less than
    // the size of the memory.
    Addr maxAddress(void){
        return opMemoryMaxAddress(handle());
    }

    // Return the memory access privilege.
    optPriv priv(void){
        return opMemoryPriv(handle());
    }

    // Read data from a memory, specifying the address within the memory (rather
    // than the address on the bus to which it is connected).
    Bool read(
        Addr            address
       ,void*           buffer
       ,Uns32           bytes
       ,Bool            debug
    ){
        return opMemoryRead(handle(),address,buffer,bytes,debug);
    }

    // Add a read callback to the given address range on a memory. This function
    // should be used as a passive monitor, rather than as part of the platform.
    void readMonitorAdd(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opMemoryReadMonitorAdd(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Delete a read callback from the given address range on a memory if it
    // exists
    void readMonitorDelete(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opMemoryReadMonitorDelete(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Restore the state of the given memory by calling the callback one or more
    // times. The callback must return the data in the same size chunks as it
    // was saved. The userData passed to the callback should be used to refer to
    // the state of the storage mechanism.
    optSaveRestoreStatus stateRestore(
        optRestoreFn    cb
       ,void *          userData
    ){
        return opMemoryStateRestore(handle(),cb,userData);
    }

    // Restore the state of the given memory from the given file.
    optSaveRestoreStatus stateRestoreFile(
        const char *    file
    ){
        return opMemoryStateRestoreFile(handle(),file);
    }

    // Save the state of the given memory by calling the callback one or more
    // times. The callback decides how the data is stored. The userData passed
    // to the callback should be used to refer to the state of the storage
    // mechanism.
    optSaveRestoreStatus stateSave(
        optSaveFn       cb
       ,void *          userData
    ){
        return opMemoryStateSave(handle(),cb,userData);
    }

    // Save the state of the given memory to a file
    optSaveRestoreStatus stateSaveFile(
        const char *    file
    ){
        return opMemoryStateSaveFile(handle(),file);
    }

    // Write data to a memory
    Bool write(
        Addr            address
       ,const void*     buffer
       ,Uns32           bytes
       ,Bool            debug
    ){
        return opMemoryWrite(handle(),address,buffer,bytes,debug);
    }

    // Add a write callback to the given address range on a memory. This
    // function should be used as a passive monitor, rather than as part of the
    // platform.
    void writeMonitorAdd(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opMemoryWriteMonitorAdd(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Remove a write callback from the given address range on a memory if it
    // exists
    void writeMonitorDelete(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opMemoryWriteMonitorDelete(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

};

class ram : public memory {
    public:
        ram(module &parent, std::string name, Addr maxAddress)
            : memory(parent, name, maxAddress)
        {
        }
};

class rom : public memory {
    public:
        rom(module &parent, std::string name, Addr maxAddress)
            : memory(parent, name, maxAddress, OP_PRIV_RX)
        {
        }
};

/////////////////////////////////////////// MMC ///////////////////////////////////////////////

class MMC : public object {

  public:
    MMC(module &parent, std::string path, std::string name, params p);

    MMC(module &parent, std::string path, std::string name);

    // MMC that already exists in OP
    EXISTING_CONSTRUCTOR_PROTO(MMC, optMMCP);

    // Create a class wrapper only if required
    GET_METHOD_PROTO(MMC, optMMCP)

    HANDLE_METHOD(optMMCP)

    busPortConn  *busPortConnNext(busPortConn *prev);
    busPort      *busPortNext(busPort *prev);

    busPort      *busPortByName   (std::string name);

    vlnv *VLNV() { return vlnv::classGet(opObjectVLNV(handle())); }

    optReleaseStatus releaseStatus() { return opObjectReleaseStatus(handle()); }

    optVisibility visibility() { return opObjectVisibility(handle()); }

    //
    // Methods for class MMC
    //
    // Return the path to the file that implements the MMC
    std::string path(void){
        return opMMCPath(handle());
    }

    // Restore the state of the given MMC by calling the callback one or more
    // times. The callback must return the data in the same size chunks as it
    // was saved. The userData passed to the callback should be used to refer to
    // the state of the storage mechanism.
    optSaveRestoreStatus stateRestore(
        optRestoreFn    cb
       ,void *          userData
    ){
        return opMMCStateRestore(handle(),cb,userData);
    }

    // Restore the state of the given MMC from the given file.
    optSaveRestoreStatus stateRestoreFile(
        const char *    file
    ){
        return opMMCStateRestoreFile(handle(),file);
    }

    // Save the state of the given MMC by calling the callback one or more
    // times. The callback decides how the data is stored. The userData passed
    // to the callback should be used to refer to the state of the storage
    // mechanism.
    optSaveRestoreStatus stateSave(
        optSaveFn       cb
       ,void *          userData
    ){
        return opMMCStateSave(handle(),cb,userData);
    }

    // Save the state of the given MMC to a file
    optSaveRestoreStatus stateSaveFile(
        const char *    file
    ){
        return opMMCStateSaveFile(handle(),file);
    }

    // Return true if this MMC is transparent
    Bool transparent(void){
        return opMMCTransparent(handle());
    }

};

////////////////////////////////////////// INITIATOR //////////////////////////////////////////////

class initiator {

public:
    static object *classGet(optObjectP existing);

};

/////////////////////////////////////////// DECODE ///////////////////////////////////////////////

enum DMIaccess { RD, WR, RW };

class decode {

    Addr lo, hi;
    decode  *link;

  public:
    virtual bool read(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        void*         data,
        void*         userData,
        Addr          VA,
        Bool          isFetch
    ) = 0;

    virtual bool write(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        const void*   data,
        void*         userData,
        Addr          VA
    ) = 0;

    virtual void *getDMI(
        Addr        addr,
        Uns32       bytes,
        Addr       &addrLo,
        Addr       &addrHi,
        DMIaccess &rw
    ) = 0;

    decode(Addr loAddr, Addr hiAddr, decode  *prev);

    virtual ~decode() {}

    decode *find(Addr addr);

    decode  *next(void)      { return link; }
    void    next(decode  *n) { link = n;    }
};

/////////////////////////////////////////// FIFO ///////////////////////////////////////////////

class FIFO : public object {

  public:
    FIFO(module &parent, std::string name);

    EXISTING_CONSTRUCTOR_PROTO(FIFO,optFIFOP);

    GET_METHOD_PROTO(FIFO, optFIFOP);

    HANDLE_METHOD(optFIFOP);

    void connect(processor &p, std::string portName) {
        opProcessorFIFOConnect(p.handle(), handle(), portName.c_str());
    }

    //
    // Methods for class FIFO
    //
    // Return the depth of a FIFO (in words)
    Uns32 depth(void){
        return opFIFODepth(handle());
    }

    // Print connection information about this FIFO
    void show(void){
        opFIFOShow(handle());
    }

    // Restore the state of the given FIFO by calling the callback one or more
    // times. The callback must return the data in the same size chunks as it
    // was saved. The userData passed to the callback should be used to refer to
    // the state of the storage mechanism.
    optSaveRestoreStatus stateRestore(
        optRestoreFn    cb
       ,void *          userData
    ){
        return opFIFOStateRestore(handle(),cb,userData);
    }

    // Restore the state of the given FIFO from the given file.
    optSaveRestoreStatus stateRestoreFile(
        const char *    file
    ){
        return opFIFOStateRestoreFile(handle(),file);
    }

    // Save the state of the given FIFO by calling the callback one or more
    // times. The callback decides how the data is stored. The userData passed
    // to the callback should be used to refer to the state of the storage
    // mechanism.
    optSaveRestoreStatus stateSave(
        optSaveFn       cb
       ,void *          userData
    ){
        return opFIFOStateSave(handle(),cb,userData);
    }

    // Save the state of the given FIFO to a file
    optSaveRestoreStatus stateSaveFile(
        const char *    file
    ){
        return opFIFOStateSaveFile(handle(),file);
    }

};

/////////////////////////////////////////// PACKETNET ///////////////////////////////////////////////

class packetnet : public object {

public:
    packetnet(module &parent, std::string name);

    // Packetnet that already exists in OP
    EXISTING_CONSTRUCTOR_PROTO(packetnet,optPacketnetP);

    GET_METHOD_PROTO(packetnet, optPacketnetP);

    HANDLE_METHOD(optPacketnetP);

    void connect(peripheral &p, std::string portName) {
        opPeripheralPacketnetConnect(p.handle(), handle(), portName.c_str());
    }

    packetnetPortConn *packetnetPortConnNext (packetnetPortConn *o);

    //
    // Methods for class packetnet
    //
    // Return the maximum number of bytes that one packet can carry in the given
    // packetnet
    Uns32 maxBytes(void){
        return opPacketnetMaxBytes(handle());
    }

    // Print connection information about this packetnet
    void show(void){
        opPacketnetShow(handle());
    }

    // Write data to a packetnet, which will cause a callbacks in each receiver
    // connected to this packetnet.
    Uns32 write(
        void*           data
       ,Uns32           bytes
    ){
        return opPacketnetWrite(handle(),data,bytes);
    }

    // Add a callback to a packetnet
    void writeMonitorAdd(
        optPacketnetWriteFn cb
       ,void*           userData
    ){
        opPacketnetWriteMonitorAdd(handle(),cb,userData);
    }

};

/////////////////////////////////////////// NET /////////////////////////////////////////

class net : public object {

public:
    net(module &parent, std::string name);

    // Net that already exists in OP
    EXISTING_CONSTRUCTOR_PROTO(net,optNetP);

    GET_METHOD_PROTO(net, optNetP);

    HANDLE_METHOD(optNetP);

    void connect(processor &p, std::string portName) {
        opObjectNetConnect(p.handle(), handle(), portName.c_str());
    }

    void connect(peripheral &p, std::string portName) {
        opObjectNetConnect(p.handle(), handle(), portName.c_str());
    }

    netPortConn *netPortConnNext (netPortConn  *o);

    //
    // Methods for class net
    //
    // Print connection information about this net
    void show(void){
        opNetShow(handle());
    }

    // Restore the state of the given net by calling the callback one or more
    // times. The callback must return the data in the same size chunks as it
    // was saved. The userData passed to the callback should be used to refer to
    // the state of the storage mechanism.
    optSaveRestoreStatus stateRestore(
        optRestoreFn    cb
       ,void *          userData
    ){
        return opNetStateRestore(handle(),cb,userData);
    }

    // Restore the state of the given net from the given file.
    optSaveRestoreStatus stateRestoreFile(
        const char *    file
    ){
        return opNetStateRestoreFile(handle(),file);
    }

    // Save the state of the given net by calling the callback one or more
    // times. The callback decides how the data is stored. The userData passed
    // to the callback should be used to refer to the state of the storage
    // mechanism.
    optSaveRestoreStatus stateSave(
        optSaveFn       cb
       ,void *          userData
    ){
        return opNetStateSave(handle(),cb,userData);
    }

    // Save the state of the given net to a file
    optSaveRestoreStatus stateSaveFile(
        const char *    file
    ){
        return opNetStateSaveFile(handle(),file);
    }

    // Read the current value of a net
    Uns64 value(void){
        return opNetValue(handle());
    }

    // Read a net's previous value
    Uns64 valuePrevious(void){
        return opNetValuePrevious(handle());
    }

    // Write a value to a net.
    Bool write(
        Uns64           value
    ){
        return opNetWrite(handle(),value);
    }

};

class netWithCallback : public net {

private:

    static OP_NET_WRITE_FN(notifier) {
        netWithCallback *p = (netWithCallback*)userData;
        p->written(value);
    }

  public :
    virtual void written(Uns32 value) = 0;

    netWithCallback(module &parent, std::string name);
};

/////////////////////////////////////////// PARSER ///////////////////////////////////////////////

class parser {
  private:
    optCmdParserP h;
    
    static OP_CMD_ERROR_HANDLER_FN(errorCallback);

  public:
    // construct simple parser without options and parse the argc/argv array
    // Note that this cannnot be used if you wish to overload the error function error() below:
    // In this case please use parser(std::string name, optArgClass useMask), then parse()
    parser(int argc, const char *argv[]);

    parser(std::string name, optArgClass useMask);

    bool parse(int argc, const char *argv[]) {
        return opCmdParseArgs(h, argc, argv);
    }

    bool parse(std::string file) {
        return opCmdParseFile(h, file.c_str());
    }

    void add(
        std::string name,
        const char *shortName,
        const char *argDesc,
        const char *group,
        optFlagType type,
        void       *ptr,
        const char * description,
        optArgClass mask      = OP_AC_NONE,
        Uns32       userData  = 0,
        bool        mandatory = false
    ) {
        opCmdParserAdd(h, name.c_str(), shortName, argDesc, group, type, ptr, description, mask, userData, mandatory);
    }

    Uns32 used(std::string name) {
        return opCmdArgUsed(h, name.c_str());
    }
    
    // default error handler
    virtual bool error(const char *flag);

    // legacy interface for C callback
    void errorHandlerAdd(optCmdErrorHandlerFn cb, void *userData) {
        opCmdErrorHandler(h, cb, userData);
    }

    void usageMessage(std::string message) {
        opCmdUsageMessage(h, message.c_str());
    }
};

//////////////////////////////////////////// FIFO PORT ////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class FIFOPort {

public:
    CAST_HANDLE_METHOD(optFIFOPortP)
    CAST_CLASS_GET_METHOD(FIFOPort,optFIFOPortP)

    std::string name()     { return opObjectName(handle());     }
    std::string hierName() { return opObjectHierName(handle()); }

    //
    // Methods for class FIFOPort
    //
    // Return the FIFO ports description
    std::string description(void){
        return opFIFOPortDescription(handle());
    }

    // Return true if this FIFO port cannot be left unconnected
    Bool mustConnect(void){
        return opFIFOPortMustConnect(handle());
    }

    // Return the FIFO port type (OP_FIFO_INPUT or OP_FIFO_INPUT) from the given
    // descriptor
    optFIFOPortType type(void){
        return opFIFOPortType(handle());
    }

    // Return the FIFO port type (input or output) from the descriptor
    std::string typeString(void){
        return opFIFOPortTypeString(handle());
    }

    // Return the width (in bits) of each item of data sent through this port
    Uns32 width(void){
        return opFIFOPortWidth(handle());
    }

};

///////////////////////////////////////////// NET PORT ////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class netPort {

public:
    CAST_HANDLE_METHOD(optNetPortP)
    CAST_CLASS_GET_METHOD(netPort,optNetPortP)

    std::string name()     { return opObjectName(handle());     }
    std::string hierName() { return opObjectHierName(handle()); }

    //
    // Methods for class netPort
    //
    // Return a description of the net port supplied by the model
    std::string description(void){
        return opNetPortDescription(handle());
    }

    // Return true if this port cannot be left unconnected
    Bool mustConnect(void){
        return opNetPortMustConnect(handle());
    }

    // Return the net port type from the net port descriptor
    optNetPortType type(void){
        return opNetPortType(handle());
    }

    // Return the net port type from the descriptor as a string
    std::string typeString(void){
        return opNetPortTypeString(handle());
    }

};

////////////////////////////////////////// PACKETNET PORT /////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class packetnetPort {

public:
    CAST_HANDLE_METHOD(optPacketnetPortP)
    CAST_CLASS_GET_METHOD(packetnetPort,optPacketnetPortP)

    std::string hierName() { return opObjectHierName(handle()); }

    //
    // Methods for class packetnetPort
    //
    // Return the description of a packetnet port definition
    std::string description(void){
        return opPacketnetPortDescription(handle());
    }

    // Return the description of a packetnet port definition
    Bool mustConnect(void){
        return opPacketnetPortMustConnect(handle());
    }

};

/////////////////////////////////////////// FIFO PORTCONN /////////////////////////////////////////

class FIFOPortConn : public object {

  public:
    CAST_HANDLE_METHOD(optFIFOPortConnP)
    CAST_CLASS_GET_METHOD(FIFOPortConn,optFIFOPortConnP)

    // Note non-standard spelling
    FIFO *fifo() { return FIFO::classGet(opFIFOPortConnFIFO(handle())); }

    //
    // Methods for class FIFOPortConn
    //
    // Return the width of the FIFO port connection in bits
    Uns32 width(void){
        return opFIFOPortConnWidth(handle());
    }

};

/////////////////////////////////////////// NET PORTCONN /////////////////////////////////////////

class netPortConn : public object {

  public:
    CAST_HANDLE_METHOD(optNetPortConnP)
    CAST_CLASS_GET_METHOD(netPortConn,optNetPortConnP)

    // Note non-standard spelling
    net *Net() { return net::classGet(opNetPortConnNet(handle())); }

    //
    // Methods for class netPortConn
    //
    // Return the net port connection type from the descriptor
    optNetPortType type(void){
        return opNetPortConnType(handle());
    }

};

//////////////////////////////////////// PACKETNET PORTCONN ///////////////////////////////////////

class packetnetPortConn : public object {

  public:
    CAST_HANDLE_METHOD(optPacketnetPortConnP)
    CAST_CLASS_GET_METHOD(packetnetPortConn,optPacketnetPortConnP)

    // Note non-standard spelling
    packetnet *Packetnet() { return packetnet::classGet(opPacketnetPortConnPacketnet(handle())); }

};

/////////////////////////////////////////////// MODE //////////////////////////////////////////////

class mode {

  public:
    CAST_HANDLE_METHOD(optModeP)
    CAST_CLASS_GET_METHOD(mode,optModeP)

    //
    // Methods for class mode
    //
    // Return the model-specific mode code from the descriptor
    Uns32 code(void){
        return opModeCode(handle());
    }

    // Return the description of the mode from the descriptor
    std::string description(void){
        return opModeDescription(handle());
    }

    // Return the name of the mode from the descriptor
    std::string name(void){
        return opModeName(handle());
    }

};

/////////////////////////////////////////// SESSION ///////////////////////////////////////////////

#define DEST(_CLASS,_TYPE)                        \
    (void) userData;                              \
    _CLASS *n = (_CLASS*)opObjectClass(object);   \
        if(n && n->allocated) {                   \
            delete n;                             \
        }


class session {

    // Pass a table of constructors and destructors to the simulator.

    static OP_DEST_BUS_FN(oldBus);

    static OP_DEST_FIFOFN(oldFIFO);

    static OP_DEST_NET_FN(oldNet);

    static OP_DEST_PACKETNET_FN(oldPacketnet);

    static OP_DEST_BUS_PORT_CONN_FN(oldBusPortConn);

    static OP_DEST_FIFOPORT_CONN_FN(oldFIFOPortConn);

    static OP_DEST_NET_PORT_CONN_FN(oldNetPortConn);

    static OP_DEST_PACKETNET_PORT_CONN_FN(oldPacketnetPortConn);

    static OP_DEST_BRIDGE_FN(oldBridge);

    static OP_DEST_MEMORY_FN(oldMemory);

    static OP_DEST_MODULE_FN(oldModule);

    static OP_DEST_PROCESSOR_FN(oldProcessor);

    static OP_DEST_PERIPHERAL_FN(oldPeripheral);

    void constructorNotifierInstaller(void);

  public:
    session();

    void textRedirect(optTextOutputFn outputcb, optQuitFn quitcb, void* userData) {
        opSessionTextRedirect(outputcb, quitcb, userData);
    }

    ~session() { opSessionTerminate(); }

    std::string productVersion(void) {
        return opSessionProductVersion();
    }

    void atExit(optExitFn fn) { return opSessionAtExit(fn); }

    void exit(Uns32 code) { opSessionExit(code); }

    void interrupt(void) { opInterrupt(); }

    void interruptRSP(void) { opInterruptRSP(); }
};

///////////////////////////////////////////// MESSAGE /////////////////////////////////////////////

class message {

public:
    // equivalent to opMessage
    static void print  (const char *severity, const char *ident, const char *fmt, ...);

    // equivalent to opVMessage
    static void vprint (const char *severity, const char *ident, const char *fmt, va_list ap);

    static void printf (const char *fmt, ...);
    static void vprintf(const char *fmt, va_list ap);
    static void vabort (const char *ident, const char *fmt, va_list ap);

    static void disable(const char *ident);
    static void enable (const char *ident);

    static const char *sprintf(const char *fmt, ...);

    static bool quiet (void)   { return opMessageQuiet();      }
    static bool quiet (bool q) { return opMessageSetQuiet(q);  }
    static bool noWarn(bool q) { return opMessageSetNoWarn(q); }
    static bool noBanner(void) { return opNoBanner(); }

    static bool verbose(void) { return opMessageVerbose(); }

    static Uns32 errors(void)    { return opErrors();       }
    static Uns32 errors(Uns32 e) { return opResetErrors(e); }

    static const char *last(void){ return opLastMessage();  }

    static void banner(void) { opBanner(); }
};

/////////////////////////////////////////// WATCHPOINT ///////////////////////////////////////////

class watchpoint {

  private:
    static OP_ADDR_WATCHPOINT_CONDITION_FN(addrNotifier);
    static OP_PROC_WATCHPOINT_CONDITION_FN(procNotifier);
    
  public:
    CAST_HANDLE_METHOD(optWatchpointP)
    CAST_CLASS_GET_METHOD(watchpoint,optWatchpointP)
    
    watchpoint (
        bus              &parent,
        optWatchpointType tp,
        Addr              addrLo,
        Addr              addrHi
    );
    
    watchpoint (
        memory           &parent,
        optWatchpointType tp,
        Addr              addrLo,
        Addr              addrHi
    );
    
    watchpoint (
        processor        &parent,
        optWatchpointType tp,
        Bool              physical=0,
        Addr              addrLo=0,
        Addr              addrHi=0
    );

    watchpoint (
        processor           &parent,
        optRegWatchpointMode mode,
        reg                 &r
    );
    
    reg *Reg() { return reg::classGet(opWatchpointReg(handle())); }

    processor *triggeredBy() { return processor::classGet(opWatchpointTriggeredBy(handle())); }
    
  protected:
    optWatchpointP    wpHandle;
    virtual bool triggered(processor *proc, Addr PA, Addr VA, Uns32 bytes, void *data);
    virtual bool triggered() {return 0;}
    virtual ~watchpoint() {  opWatchpointDelete(wpHandle); };
    
    //
    // Methods for class watchpoint
    //
    // Return the upper address limit of a watchpoint region
    Addr addressHi(void){
        return opWatchpointAddressHi(handle());
    }

    // Return the lower address limit of a watchpoint region
    Addr addressLo(void){
        return opWatchpointAddressLo(handle());
    }

    // If the given watchpoint is of type OP_WP_REG, and has been triggered,
    // return a pointer to the register's current value
    void* regCurrentValue(void){
        return opWatchpointRegCurrentValue(handle());
    }

    // If the given watchpoint is of type OP_WP_REG, and has been triggered,
    // return a pointer to the register's previous value
    void* regPreviousValue(void){
        return opWatchpointRegPreviousValue(handle());
    }

    // Reset the given watchpoint to its un-triggered state.
    void reset(void){
        opWatchpointReset(handle());
    }

    // Return the type of this watchpoint
    optWatchpointType type(void){
        return opWatchpointType(handle());
    }

    // Return the user data that was passed to the function that created the
    // watchpoint
    void* userData(void){
        return opWatchpointUserData(handle());
    }

};

///////////////////////////////////////////// BUS /////////////////////////////////////////////////

class bus : public object {

public:
    bus(module &parent, std::string name, Uns32 bits, params p);

    bus(module &parent, std::string name, Uns32 bits);

    ~bus() { }

    // Bus that already exists in OP
    EXISTING_CONSTRUCTOR_PROTO(bus, optBusP);

    GET_METHOD_PROTO(bus, optBusP);

    HANDLE_METHOD(optBusP);

    busPortConn *connect(processor &p, std::string portName);

    busPortConn *connect(memory &p, std::string portName, Addr lo, Addr hi);

    busPortConn *connect (peripheral &p, std::string portName);

    busPortConn *connect (peripheral &p, std::string portName, Addr lo, Addr hi);

    busPortConn *connectSlave(peripheral &p, std::string portName, Addr lo, Addr hi);

    busPortConn *connectSlave(peripheral &p, std::string portName);

    busPortConn *connectMaster(peripheral &p, std::string portName);

    busPortConn *connectSlave(bridge &p, std::string portName, Addr lo, Addr hi);

    busPortConn *connectMaster(bridge &p, std::string portName);

    busPortConn *connectMaster(bridge &p, std::string portName, Addr lo, Addr hi);

    busPortConn *connect(MMC &p, std::string portName);

    busPortConn *busPortConnNext (busPortConn *o);

    busSlave *busSlaveNext (busSlave *o);

    void dynamicBridge(bus *master, Addr loAddrSlave, Addr hiAddrSlave, Addr loAddrMaster) {
        opDynamicBridge(handle(), master->handle(), loAddrSlave, hiAddrSlave, loAddrMaster);
    }

    application *applicationNext(application *prev) {
        return application::classGet(opObjectApplicationNext(handle(), prev->handle()));
    }

    watchpoint *accessWatchpointNew(Addr lo, Addr hi, void *userData, optAddrWatchpointConditionFn notifierCB);

    watchpoint *readWatchpointNew(Addr lo, Addr hi, void *userData, optAddrWatchpointConditionFn notifierCB);

    watchpoint *writeWatchpointNew(Addr lo, Addr hi, void *userData, optAddrWatchpointConditionFn notifierCB);

    //
    // Methods for class bus
    //
    // Return the number of address bits used on this bus
    Uns32 addrBits(void){
        return opBusAddrBits(handle());
    }

    // Read an application and load it via the specified bus, using the
    // installed readers.
    optApplicationP applicationLoad(
        const char*     path
       ,optLoaderControls controls
       ,Addr            loadOffset
    ){
        return opBusApplicationLoad(handle(),path,controls,loadOffset);
    }

    // Add a fetch callback to the given address range on a bus. This function
    // should be used as a passive monitor, rather than as part of the platform.
    void fetchMonitorAdd(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    wcb
       ,void*           userData
    ){
        opBusFetchMonitorAdd(handle(),processor ? processor->handle() : 0,addrLo,addrHi,wcb,userData);
    }

    // Remove a fetch callback from the given address range on a bus if it
    // exists
    void fetchMonitorDelete(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    wcb
       ,void*           userData
    ){
        opBusFetchMonitorDelete(handle(),processor ? processor->handle() : 0,addrLo,addrHi,wcb,userData);
    }

    // Scan addresses starting from address *addrLoP up to *addrHiP to find the
    // next region of mapped memory. If a region is found, update *addrLoP and
    // *addrHiP with its bounds and return True. If no mapped region is
    // found,return False.
    Bool mappedRangeNext(
        Addr*           addrLoP
       ,Addr*           addrHiP
    ){
        return opBusMappedRangeNext(handle(),addrLoP,addrHiP);
    }

    // Return the maximum address supported on this bus
    Addr maxAddress(void){
        return opBusMaxAddress(handle());
    }

    // Set the privilege of the given address region
    Bool privSet(
        Addr            addrLo
       ,Addr            addrHi
       ,optPriv         priv
    ){
        return opBusPrivSet(handle(),addrLo,addrHi,priv);
    }

    // Read data from a bus in the context of a processor
    Bool read(
        processor*      processor
       ,Addr            address
       ,void*           buffer
       ,Uns32           bytes
       ,Bool            debug
    ){
        return opBusRead(handle(),processor ? processor->handle() : 0,address,buffer,bytes,debug);
    }

    // Add a read callback on the given address range of a bus. This function
    // should be used as a passive monitor, rather than as part of the platform.
    void readMonitorAdd(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opBusReadMonitorAdd(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Remove a read callback from the given address range of a bus if it exists
    void readMonitorDelete(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    rcb
       ,void*           userData
    ){
        opBusReadMonitorDelete(handle(),processor ? processor->handle() : 0,addrLo,addrHi,rcb,userData);
    }

    // Display a summary of the static connections to a bus
    void show(void){
        opBusShow(handle());
    }

    // Write data to a bus in the context of a processor.
    Bool write(
        processor*      processor
       ,Addr            address
       ,const void*     buffer
       ,Uns32           bytes
       ,Bool            debug
    ){
        return opBusWrite(handle(),processor ? processor->handle() : 0,address,buffer,bytes,debug);
    }

    // Add a write callback on the given address range on a bus. This function
    // should be used as a passive monitor, rather than as part of the platform.
    void writeMonitorAdd(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    wcb
       ,void*           userData
    ){
        opBusWriteMonitorAdd(handle(),processor ? processor->handle() : 0,addrLo,addrHi,wcb,userData);
    }

    // Delete a write callback from the given address range on a bus
    void writeMonitorDelete(
        processor*      processor
       ,Addr            addrLo
       ,Addr            addrHi
       ,optMonitorFn    wcb
       ,void*           userData
    ){
        opBusWriteMonitorDelete(handle(),processor ? processor->handle() : 0,addrLo,addrHi,wcb,userData);
    }

    // Remove dynamic bridge between two buses.
    Bool dynamicUnbridge(
        Addr            addrLoMaster
       ,Addr            addrHiMaster
    ){
        return opDynamicUnbridge(handle(),addrLoMaster,addrHiMaster);
    }

    // Map native memory onto a bus at run-time. The memory must be
    // pre-allocated by the user.
    Bool memoryNativeDynamic(
        Addr            addrLo
       ,Addr            addrHi
       ,void*           nativeMemory
       ,optPriv         priv
    ){
        return opMemoryNativeDynamic(handle(),addrLo,addrHi,nativeMemory,priv);
    }

};

///////////////////////////////////////////// BUS PORT ////////////////////////////////////////////

// The class is never constructed. A class pointer is cast from the simulator structure.

class busPort {

public:
    CAST_HANDLE_METHOD(optBusPortP)
    CAST_CLASS_GET_METHOD(busPort,optBusPortP)

    optBusPortType  type()                { return opBusPortType(handle()); }

    Addr            addrHi()              { return opBusPortAddrHi(handle()); }
    Uns32           addrBitsDefault()     { return opBusPortAddrBitsDefault(handle()); }
    Uns32           addrBitsMax()         { return opBusPortAddrBitsMax(handle()); }
    Uns32           addrBitsMin()         { return opBusPortAddrBitsMin(handle()); }
    bool            mustConnect()         { return opBusPortMustConnect(handle()); }
    bool            isDynamic()           { return opBusPortIsDynamic(handle());   }

    std::string     name()                { return opObjectName(handle());        }
    std::string     hierName()            { return opObjectHierName(handle());    }
    std::string     typeString()          { return opBusPortTypeString(handle()); }
    std::string     description()         { return opBusPortDescription(handle());}

    MMRegister     *MMRegisterNext(MMRegister *prev);
};

/////////////////////////////////////////// BUS PORTCONN //////////////////////////////////////////

class busPortConn : public object {

public:
    CAST_HANDLE_METHOD(optBusPortConnP)
    CAST_CLASS_GET_METHOD(busPortConn,optBusPortConnP)

    // Note non-standard spelling
    bus *Bus(void) { return bus::classGet(opBusPortConnBus(handle())); }

    //
    // Methods for class busPortConn
    //
    // Return the upper address limit from a bus port connection
    Addr addrHi(void){
        return opBusPortConnAddrHi(handle());
    }

    // Return the lower address limit from a bus port connection
    Addr addrLo(void){
        return opBusPortConnAddrLo(handle());
    }

    // Return true if the connected bus port slave decode is dynamic (the
    // address range can change at run-time).
    Bool isDynamic(void){
        return opBusPortConnIsDynamic(handle());
    }

    // Install a callback to give notification when a port mapping changes. Port
    // mappings are typically changed by a peripheral model, for instance when
    // an address decoder is reconfigured by writing to a register. This feature
    // allows other parts of the platform to be notified.
    Bool mapNotify(
        optPortMapFn    cb
       ,void*           userData
    ){
        return opBusPortConnMapNotify(handle(),cb,userData);
    }

    // Return the bus port connection type as an enumerated type
    optBusPortType type(void){
        return opBusPortConnType(handle());
    }

    // Return the bus port connection type as a string
    std::string typeString(void){
        return opBusPortConnTypeString(handle());
    }

};

/////////////////////////////////////////// BUS SLAVE ///////////////////////////////////////////////

class busSlave : public object {

public:

    GET_METHOD_PROTO(busSlave, optBusSlaveP);

    EXISTING_CONSTRUCTOR_PROTO(busSlave, optBusSlaveP);

    HANDLE_METHOD(optBusSlaveP);

    virtual void read(
            object       *initator,
            Addr          addr,
            Uns32         bytes,
            void*         data,
            void*         userData,
            Addr          VA,
            Bool          isFetch
    ) {
        (void) initator;
        (void) addr;
        (void) bytes;
        (void) data;
        (void) userData;
        (void) VA;
        (void) isFetch;

        std::cout << "Error : busSlave::read function not implemented" << std::endl;
    }

    virtual void write(
            object       *initator,
            Addr          addr,
            Uns32         bytes,
            const void*   data,
            void*         userData,
            Addr          VA
    ) {
        (void) initator;
        (void) addr;
        (void) bytes;
        (void) data;
        (void) userData;
        (void) VA;
        std::cout << "Error : busSlave::write function not implemented" << std::endl;
    }

    void readAbort(processor *p, Addr addr) {
        opProcessorReadAbort(p->handle(), addr);
    }

    void writeAbort(processor *p, Addr addr) {
        opProcessorWriteAbort(p->handle(), addr);
    }

    void readAbort(Addr addr) {
        opProcessorReadAbort(0, addr);
    }

    void writeAbort(Addr addr) {
        opProcessorWriteAbort(0, addr);
    }

private:
    void *_userData;

    static OP_BUS_SLAVE_READ_FN(busRead);

    static OP_BUS_SLAVE_WRITE_FN(busWrite);

public:

    // just user-allocated memory
    busSlave(
        bus        &bus,
        std::string name,
        processor  *proc,
        optPriv     privilege,
        Addr        addrLo,
        Addr        addrHi,
        void*       nativeMemory
    );

    // mixture of user-allocated memory and callbacks
    busSlave (
        bus        &bus,
        std::string name,
        processor  *proc,
        optPriv     privilege,
        Addr        addrLo,
        Addr        addrHi,
        bool        rcb,
        bool        wcb,
        void*       userData,
        void*       nativeMemory
    );

    ~busSlave() {}
};

////////////////////////////////////// BUS SLAVE WITH DMI //////////////////////////////////////

class busDMISlave : public object {

private:
    optBusSlaveP h;
    std::string  slaveName;
    Addr         addrMin;
    Addr         addrMax;
    bus         &parentBus;
    optPriv      priv;
    Uns32        nextNameNum;
    bool         allowDMI;
    void        *iUserData;

    std::string nextName(void) {
        return slaveName;
    }

  public:

    virtual void *getDMI(
        Addr        addr,
        Uns32       bytes,
        Addr       &addrLo,
        Addr       &addrHi,
        DMIaccess  &rw,
        void       *userData
    ) = 0;

    virtual bool read(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        void*         data,
        void*         userData,
        Addr          VA,
        Bool          isFetch,
        bool          &dmiAllowed
    ) = 0;

    virtual bool write(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        const void*   data,
        void*         userData,
        Addr          VA,
        bool          &dmiAllowed
    ) = 0;

    void invalidateDMI(Addr addrLo, Addr addrHi) {
        opBusSlaveNew (
            parentBus.handle(),
            nextName().c_str(),
            0,
            OP_PRIV_RWX,
            addrLo,
            addrHi,
            allowDMI ? busReadTryDMI  : busReadNoDMI,
            allowDMI ? busWriteTryDMI : busWriteNoDMI,
            0,
            this
        );
    }

    void dmi(bool on) { allowDMI = on; }
    bool dmi(void)    { return allowDMI; }

  private:
    static OP_BUS_SLAVE_READ_FN(busReadNoDMI);

    static OP_BUS_SLAVE_WRITE_FN(busWriteNoDMI);

    static OP_BUS_SLAVE_READ_FN(busReadTryDMI);

    static OP_BUS_SLAVE_WRITE_FN(busWriteTryDMI);

    void tryDMI(Addr addr, Uns32 bytes);

  public:
    busDMISlave (
        bus        &bus,
        std::string name,
        processor  *proc,
        optPriv     privilege,
        Addr        addrLo,
        Addr        addrHi,
        Bool        enableDMI,
        void       *userData
    );

    busDMISlave (
        bus          &bus,
        std::string   name,
        processor    *proc,
        Bool          enableDMI
    );

    busDMISlave (
        bus       &bus,
        std::string     name,
        optPriv    privilege,
        Addr       addrLo,
        Addr       addrHi,
        Bool       enableDMI
    );

    busDMISlave (
        bus        &bus,
        std::string name,
        Bool        enableDMI
    );

};

/////////////////////////////////////////// MODULE TRIGGER ////////////////////////////////////////

class moduleTrigger {

private:
    static OP_TRIGGER_FN(notifier);
    optTriggerEventP event;
    module          &parent;
    optTime          period;

public:
    moduleTrigger(module &parent, optTime interval);
    ~moduleTrigger();
    void retrigger();
    void retrigger(optTime interval);

protected :
    virtual void triggered(optTime now) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class sharedData {
    
private:
    optSharedDataHandleP h;
    module              *r;
    
public:
    module              *root()   { return r; }
    optSharedDataHandleP handle() { return h; }
    sharedData(module &root, const char* version, const char* key, Bool add);
    virtual ~sharedData();
    Int32  write(Int32, void *data);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class sharedDataTrigger {

public:
    sharedDataTrigger(sharedData &data);
    ~sharedDataTrigger();

private:
    sharedData &data;
    static OP_SHARED_DATA_LISTENER_FN(notifier);

protected :
    virtual void triggered(Int32 id, void *userData) = 0;
};

} // end namespace op

