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


/*
 * THIS INTERFACE USES THE ICM  API WHICH IS DEPRECATED.
 * PLEASE USE ImpPublic/host/source/op/op.cpp
 */


#include "icm/icmCpuManager.hpp"

using namespace icmCpuManager;

////////////////////////////////////////////////////////////////////////////////
//
// icmCpuManagerItem
//
////////////////////////////////////////////////////////////////////////////////

// public

// Constructor
icmCpuManagerItem::icmCpuManagerItem(void)
{
    if(!_cpuManagerInited) {
        icmInitPlatform(ICM_VERSION, ICM_INIT_DEFAULT, 0, 0, NULL);
        _cpuManagerInited = true;
    }
}

icmCpuManagerItem::icmCpuManagerItem(bool platform)
{
    if(_cpuManagerInited) {
        icmMessage("F", "ICM_API++", "Calling platform constructor more than once");
    }
    _cpuManagerInited = true;
}

icmCpuManagerItem::~icmCpuManagerItem(void)
{
    if(_cpuManagerInited) {
        icmTerminate();
        _cpuManagerInited = false;
    }
}

// statics

bool icmCpuManagerItem::_cpuManagerInited = false;

////////////////////////////////////////////////////////////////////////////////
//
// icmPlatform
//
////////////////////////////////////////////////////////////////////////////////

icmPlatform *icmPlatform::_singleton = NULL;

// Constructors
icmPlatform::icmPlatform(
    const char  *name,
    icmInitAttrs simAttrs,
    const char  *dbgHostName,
    Uns32        dbgPort
) : icmCpuManagerItem(true)
{
    // do not pass the name of the platform - SystemC appends the name where required.
    icmInitPlatform(ICM_VERSION, simAttrs, dbgHostName, dbgPort, 0);
    _name      = name;
    _singleton = this;
}

// run the platform
icmProcessorObject *icmPlatform::simulate() {
    icmProcessorP proc = icmSimulatePlatform();
    if(proc) {
        icmProcessorObject* pobj = (icmProcessorObject*)icmGetProcessorHandle(proc);

        // if there is a handler for the reason then invoke it
        icmHandleSimStop_if *hnd = pobj->getSimStopHnd();
        if (hnd) {
            hnd->simStopHandler(pobj, pobj->getStopReason());
        }
        return pobj;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// icmAttrListObject
//
////////////////////////////////////////////////////////////////////////////////

// public

// Constructor
icmAttrListObject::icmAttrListObject()
{
    _userAttrs = icmNewAttrList();
}

// Add an Uns64 attribute to the user attributes object
void icmAttrListObject::addAttr(const char *name, Uns64 value)
{
    icmAddUns64Attr(_userAttrs, name, value);
}

// Add an int attribute to the user attributes object
void icmAttrListObject::addAttr(const char *name, int value)
{
    icmAddUns32Attr(_userAttrs, name, value);
}

// Add a double attribute to the user attributes object
void icmAttrListObject::addAttr(const char *name, double value)
{
    icmAddDoubleAttr(_userAttrs, name, value);
}

// Add a atring attribute to the user attributes object
void icmAttrListObject::addAttr(const char *name, const char *value)
{
    icmAddStringAttr(_userAttrs, name, value);
}

// Add a Pointer attribute to the user attributes object
void icmAttrListObject::addAttr(const char *name, void *value)
{
    icmAddPtrAttr(_userAttrs, name, value);
}

// Return userAttrs for object
icmAttrListP icmAttrListObject::getUserAttrs()
{
    return _userAttrs;
}

////////////////////////////////////////////////////////////////////////////////
//
// icmMemCallback
//
////////////////////////////////////////////////////////////////////////////////

icmMemCallback::icmMemCallback(readCallback rcb, writeCallback wcb, void *userData) {
    _user = userData;
    _rcb  = rcb;
    _wcb  = wcb;
}

void icmMemCallback::callRead(Addr address, Uns32 bytes, void *value, void *processor) {
    _rcb(address, bytes, value, _user, processor);
}

void icmMemCallback::callWrite(Addr address, Uns32 bytes, const void *value, void *processor) {
    _wcb(address, bytes, value, _user, processor);
}

static ICM_MEM_READ_FN(genericReadCB) {
    icmMemCallback *cp = (icmMemCallback*)userData;
    cp->callRead(address, bytes, value, processor);
}

static ICM_MEM_WRITE_FN(genericWriteCB) {
    icmMemCallback *cp = (icmMemCallback*)userData;
    cp->callWrite(address, bytes, (void*)value, processor);
}

////////////////////////////////////////////////////////////////////////////////
//
// icmBusObject
//
////////////////////////////////////////////////////////////////////////////////

// public

// Constructors
icmBusObject::icmBusObject(const char *name, Uns8 addressBits)
{
    _bus = icmNewBus(name, addressBits);
}

icmBusObject::icmBusObject(const char *prefix, const char *name, Uns8 addressBits)
{
    string s = prefix;
    s += "_";
    s += name;

    _bus = icmNewBus(s.c_str(), addressBits);
}

// Invoke callback on read accesses to the address range lowAddr:highAddr
void icmBusObject::addReadCallback(
    icmProcessorObject *scope,
    Addr                lowAddr,
    Addr                highAddr,
    icmMemWatchFn       readCB,
    void               *userData
) {
    icmProcessorP _scope = scope ? scope->getProcessorP() : NULL;
    icmAddBusReadCallback(_bus, _scope, lowAddr, highAddr, readCB, userData);
}

// Invoke callback on write accesses to the address range lowAddr:highAddr
void icmBusObject::addWriteCallback(
    icmProcessorObject *scope,
    Addr                lowAddr,
    Addr                highAddr,
    icmMemWatchFn       writeCB,
    void               *userData
) {
    icmProcessorP _scope = scope ? scope->getProcessorP() : NULL;
    icmAddBusWriteCallback(_bus, _scope, lowAddr, highAddr, writeCB, userData);
}

// Invoke callback on fetch accesses to the address range lowAddr:highAddr
void icmBusObject::addFetchCallback(
    icmProcessorObject *scope,
    Addr                lowAddr,
    Addr                highAddr,
    icmMemWatchFn       fetchCB,
    void               *userData
) {
    icmProcessorP _scope = scope ? scope->getProcessorP() : NULL;
    icmAddBusFetchCallback(_bus, _scope, lowAddr, highAddr, fetchCB, userData);
}

// Map the passed address range externally to the processor using the callbacks
void icmBusObject::mapExternalMemory(
    const char   *portName,
    icmPriv       priv,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemReadFn  readCB,
    icmMemWriteFn writeCB,
    void         *userData
) {
    icmMapExternalMemory(
        _bus, portName, priv, lowAddr, highAddr, readCB, writeCB, userData
    );
}

// Map the passed address range externally to the processor using  callback object
void icmBusObject::mapExternalMemory(
    const char     *portName,
    icmPriv         priv,
    Addr            lowAddr,
    Addr            highAddr,
    icmMemCallback *cb
) {
    icmMapExternalMemory(
        _bus, portName, priv, lowAddr, highAddr, genericReadCB, genericWriteCB, (void*)cb
    );
}

// Map the passed address range externally to the processor using  callback object
void icmBusObject::mapExternalNativeMemory(
    const char     *portName,
    void           *memory,
    icmPriv         priv,
    Addr            lowAddr,
    Addr            highAddr,
    icmMemCallback *cb
) {
    icmMapExternalNativeMemory(
        _bus,
        portName,
        priv,
        lowAddr,
        highAddr,
        cb->hasRCB() ? genericReadCB : 0,
        cb->hasWCB() ? genericWriteCB: 0,
        memory,
        (void*)cb
    );
}

// Map the passed address range using a local anonymous memory
void icmBusObject::mapLocalMemory(
    const char *portName,
    icmPriv     priv,
    Addr        lowAddr,
    Addr        highAddr
) {
    icmMapLocalMemory(_bus, portName, priv, lowAddr, highAddr);
}

// Map some of the user's memory onto a bus.
void icmBusObject::mapNativeMemory(
    void       *memory,
    icmPriv     priv,
    Addr        lowAddress,
    Addr        hiAddress
) {
    icmMapNativeMemory(_bus, priv, lowAddress, hiAddress, memory);
}

// Create a bus bridge between this bus and master so that the region
// lowAddr:highAddr on this bus accesses the region starting at lowAddrMaster.

void icmBusObject::newBridge(
    icmBusObject &master,
    const char   *bridgeName,
    const char   *portNameOnThis,
    const char   *portNameOnMaster,
    Addr          lowAddr,
    Addr          highAddr,
    Addr          lowAddrMaster
) {
    icmNewBusBridge(
        _bus, master.getBus(), bridgeName, portNameOnThis, portNameOnMaster, lowAddr, highAddr,
        lowAddrMaster
    );
}

// dynamic bridge to another bus
void icmBusObject::bridge(
    icmBusObject &slave,
    Addr          lowAddr,
    Addr          highAddr,
    Addr          lowAddrSlave
) {
    icmBridgeBuses(_bus, slave.getBus(),lowAddr, highAddr, lowAddrSlave);
}

// remove dynamic bridge to another bus
void icmBusObject::unbridge(
    Addr          lowAddr,
    Addr          highAddr
) {
    icmUnbridgeBuses(_bus, lowAddr, highAddr);
}

// Load an object file onto this bus
bool icmBusObject::loadMemory(
    const char    *objectFile,
    bool           loadPhysical,
    bool           verbose
) {
    icmLoaderAttrs      attrs = ICM_LOAD_DEFAULT;
    if (loadPhysical)   attrs = (icmLoaderAttrs)(attrs | ICM_LOAD_PHYSICAL);
    if (verbose)        attrs = (icmLoaderAttrs)(attrs | ICM_LOAD_VERBOSE);

    return (icmLoadBus(_bus, objectFile, attrs, 0) != 0);
}

// Load an object file onto this bus
bool icmBusObject::loadMemory(
    const char    *objectFile,
    icmLoaderAttrs attrs
) {
    return (icmLoadBus(_bus, objectFile, attrs, 0) != 0);
}

//
// Print the master and slave connections on a bus
//
void icmBusObject::printConnections(void)
{
    icmPrintBusConnections(_bus);
}

// Get corresponding C bus structure
icmBusP icmBusObject::getBus()
{
    return _bus;
}

// direct bus read and write
void icmBusObject::read(Addr address, void *data, Uns32 bytes, void *processor)
{
    icmReadBus((icmProcessorP)processor, _bus, address, data, bytes);
}

void icmBusObject::write(Addr address, void *data, Uns32 bytes, void *processor)
{
    icmWriteBus((icmProcessorP)processor, _bus, address, data, bytes);
}

////////////////////////////////////////////////////////////////////////////////
//
// icmNetObject
//
////////////////////////////////////////////////////////////////////////////////

// public

// Constructors
icmNetObject::icmNetObject(const char *name)
{
    _net = icmNewNet(name);
}

// Write the value to the net
bool icmNetObject::write(Uns32 netValue)
{
    return icmWriteNet(_net, netValue)==True ? true : false;
}

// Get corresponding C net structure
icmNetP icmNetObject::getNet()
{
    return _net;
}

void icmNetObject::addCallback(icmNetFn cb, void *user) {
    icmAddNetCallback(_net, cb, user);
}

////////////////////////////////////////////////////////////////////////////////
//
// icmMmcObject
//
////////////////////////////////////////////////////////////////////////////////

icmMmcObject::icmMmcObject(
    const char        *name,
    const char        *modelFile,
    const char        *modelSymbol,
    icmAttrListObject *initialAttrs,
    bool               transparent
) {
    icmAttrListP _userAttrs = initialAttrs ? initialAttrs->getUserAttrs() : 0;

    _mmc = icmNewMMC(
        name,
        modelFile,
        modelSymbol,
        _userAttrs,
        0,
        transparent
    );
}

// connect to a bus
void icmMmcObject::connect(
    icmBusObject &bus,
    const char   *portName,
    bool          isMaster    // otherwise a slave port
){
    icmConnectMMCBus(
        _mmc,
        bus.getBus(),
        portName,
        isMaster
    );
}

icmMmcP icmMmcObject::getMMC() {
    return _mmc;
}

////////////////////////////////////////////////////////////////////////////////
//
// icmMemoryObject
//
////////////////////////////////////////////////////////////////////////////////

// public

// Constructors
icmMemoryObject::icmMemoryObject(
    const char *name,
    icmPriv     priv,
    Uns64       highAddr
) {
    _memory = icmNewMemory(name, priv, highAddr);
}

// Read bytes from shared memory into a buffer
void icmMemoryObject::read(
    Addr  simAddress,
    void *buffer,
    Uns32 size
) {
    icmReadMemory(_memory, simAddress, buffer, size);
}

// Write bytes into shared memory from a buffer
void icmMemoryObject::write(
    Addr        simAddress,
    const void *buffer,
    Uns32       size
) {
    icmWriteMemory(_memory, simAddress, buffer, size);
}

// Connect a memory object and a bus, using the named memory port
void icmMemoryObject::connect(
    const char   *portName,
    icmBusObject &bus,
    Addr          lowAddr
) {
    icmConnectMemoryToBus(bus.getBus(), portName, _memory, lowAddr);
}

// Return shared memory for object
icmMemoryP icmMemoryObject::getMemory()
{
    return _memory;
}


////////////////////////////////////////////////////////////////////////////////
//
// icmProcessorObject
//
////////////////////////////////////////////////////////////////////////////////

// protected

bool icmProcessorObject::loadLocalMemory(
                        const char    *objectFile,
                        bool           loadPhysical,
                        bool           verbose,
                        bool           useEntry
) {
    return (icmLoadProcessorMemory(
        _proc,
        objectFile,
        loadPhysical ? ICM_LOAD_PHYSICAL : ICM_LOAD_DEFAULT,
        verbose      ? True : False,
        useEntry     ? True : False
    ) != 0);
}

bool icmProcessorObject::loadLocalMemory(
                        const char    *objectFile,
                        icmLoaderAttrs attrs
) {
    return (icmLoadProcessorMemory(
        _proc,
        objectFile,
        attrs,
        0,
        0
    ) != 0);
}

bool icmProcessorObject::loadSymbols(
        const char    *objectFile,
        Bool          loadPhysical
) {
    return icmLoadSymbols(_proc, objectFile, loadPhysical);
}

/// Read the file's header and fill the info structure.

bool icmProcessorObject::readObjectHeader(
     const char    *objectFile,
     ordObjectInfo *info
) {
    return icmReadObjectFileHeaderInfo(objectFile, info);
}

void icmProcessorObject::freeProcessor(void) {}

icmStopReason icmProcessorObject::simulate(Uns64 clocks)
{
    return icmSimulate(_proc, clocks);
}

// public

// Constructors
icmProcessorObject::icmProcessorObject(
                        const char        *name,
                        const char        *type,
                        Uns32              cpuId,
                        Uns32              cpuFlags,
                        Uns8               addressBits,
                        const char        *modelFile,
                        const char        *modelSymbol,
                        icmNewProcAttrs    procAttrs,
                        icmAttrListObject *userAttrs,
                        const char        *semiHostFile,
                        const char        *semiHostSymbol
) {
    newProcessorObject(
        name, type, cpuId, cpuFlags, addressBits, modelFile, modelSymbol,
        procAttrs, userAttrs, semiHostFile, semiHostSymbol
    );
}

icmProcessorObject::icmProcessorObject(
                        const char        *name,
                        const char        *modelFile,
                        Uns32              cpuFlags,
                        icmNewProcAttrs    procAttrs,
                        icmAttrListObject *userAttrs,
                        const char        *semiHostFile
) {
    newProcessorObject(
        name, 0, 0, cpuFlags, 0, modelFile, 0,
        procAttrs, userAttrs, semiHostFile, 0
    );
}

icmProcessorObject::icmProcessorObject(icmProcessorP exist) {
    _proc = exist;
    _simStopHnd = 0;
}


// Private functions
void icmProcessorObject::newProcessorObject(
                        const char        *name,
                        const char        *type,
                        Uns32              cpuId,
                        Uns32              cpuFlags,
                        Uns8               addressBits,
                        const char        *modelFile,
                        const char        *modelSymbol,
                        icmNewProcAttrs    procAttrs,
                        icmAttrListObject *userAttrs,
                        const char        *semiHostFile,
                        const char        *semiHostSymbol
) {
    try {

        icmAttrListP _userAttrs = userAttrs ? userAttrs->getUserAttrs() : 0;

        _proc = icmNewProcessorWithHandle(
            name,           // processor name
            type,           // processor type
            cpuId,          // processor cpuId
            cpuFlags,       // processor model flags
            addressBits,    // address bits
            modelFile,      // model file
            modelSymbol,    // morpher attributes
            procAttrs,      // processor attributes
            _userAttrs,     // user-defined attributes
            semiHostFile,   // semihosting file
            semiHostSymbol, // semihosting attributes
            (void*)this
        );
        if (!_proc) throw 1;

        // No default implementation for icmHandleSimStop_if
        _simStopHnd = 0;

    } catch (int i) {

        // the catch will allow us not to check for _proc
        // at every use of member functions.

        icmMessage("F", "ICM_API++",
            "Except %d: Processor model '%s' could not be instantiated.\n",
            i,
            modelFile
        );

    }
}

// PROCESSOR MEMORY CONFIGURATION

// Connect the processor to the passed instruction and data buses
void icmProcessorObject::connect(
    icmBusObject &instructionBus,
    icmBusObject &dataBus
) {
    icmConnectProcessorBusses(_proc, instructionBus.getBus(), dataBus.getBus());
}

// Connect the processor to the passed bus by port name
void icmProcessorObject::connect(
    const char   *portName,
    icmBusObject &bus
) {
    icmConnectProcessorBusByName(_proc, portName, bus.getBus());
}

// Connect a processor net port with the passed name and direction to a net
void icmProcessorObject::connect(
    icmNetObject &net,
    const char   *portName,
    icmDirection  direction
) {
    icmConnectProcessorNet(_proc, net.getNet(), portName, direction);
}

// Add a supplementary intercept shared object for the processor. The shared
// object has the passed instance name.
void icmProcessorObject::addInterceptObject(
    const char        *instanceName,
    const char        *interceptFile,
    const char        *interceptSymbol,
    icmAttrListObject *userAttrs
) {
    icmAttrListP _userAttrs = userAttrs ? userAttrs->getUserAttrs() : 0;
    icmAddInterceptObject(
        _proc,
        instanceName,
        interceptFile,
        interceptSymbol,
        _userAttrs
    );
}

// CALLBACKS

// Invoke callback on read accesses to the address range lowAddr:highAddr
void icmProcessorObject::addReadCallback(
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn readCB,
    void         *userData
) {
    icmAddReadCallback(_proc, lowAddr, highAddr, readCB, userData);
}

// Invoke callback on write accesses to the address range lowAddr:highAddr
void icmProcessorObject::addWriteCallback(
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void         *userData
) {
    icmAddWriteCallback(_proc, lowAddr, highAddr, writeCB, userData);
}

// Invoke callback on fetch accesses to the address range lowAddr:highAddr
void icmProcessorObject::addFetchCallback(
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn fetchCB,
    void         *userData
) {
    icmAddFetchCallback(_proc, lowAddr, highAddr, fetchCB, userData);
}



// add gdb path and start-up flags
void icmProcessorObject::setGdbPath(
    const char *path,
    const char *flags
) {
    icmSetProcessorGdbPath(_proc, path, flags);
}

// Do not use gdb
void icmProcessorObject::setGdbBasic() {
    icmSetProcessorGdbBasic(_proc);
}

// Register a handler for the icmStopReason returned by the processor
void icmProcessorObject::icmRegisterSimStopHandler(icmHandleSimStop_if &simStopHnd)
{
    _simStopHnd = &simStopHnd;
}

// PROCESSOR MEMORY ACCESS

// Load the processor memory with the passed object file
icmProcessorObject& icmProcessorObject::operator<< (const char *objectFile)
{
    loadLocalMemory(objectFile, ICM_LOAD_DEFAULT, false, True);
    return *this;
}

// Read bytes from processor memory into a buffer
void icmProcessorObject::readMemory(Addr simAddress, void *buffer, Uns32 size)
{
    icmReadProcessorMemory(_proc, simAddress, buffer, size);
}

// Write bytes into processor memory from a buffer
void icmProcessorObject::writeMemory(Addr simAddress, const void *buffer, Uns32 size)
{
    icmWriteProcessorMemory(_proc, simAddress, buffer, size);
}

// RUN TIME

icmProcessorObject& icmProcessorObject::operator<< (Uns64 instructions)
{
    // simulate instructions and store the reason for stopping
    icmStopReason reason = simulate(instructions);

    // if there is a handler for the reason then invoke it
    if (_simStopHnd) {
        _simStopHnd->simStopHandler(this, reason);
    }

    // return the processor object
    return *this;
}

// Return the processor name
const char *icmProcessorObject::getName(const char *delimiter)
{
    return icmGetProcessorName(_proc, delimiter);
}

// Return the number of instructions executed by the processor
Uns64 icmProcessorObject::getICount(void)
{
    return icmGetProcessorICount(_proc);
}

// Return the number of instructions and halted instructions executed by the processor
Uns64 icmProcessorObject::getClocks(void)
{
    return icmGetProcessorClocks(_proc);
}

// This iterator returns the next processor register description, given the
// previous description. Pass NULL to get the first register description for the
// processor
icmRegInfoP icmProcessorObject::nextReg(icmRegInfoP previous)
{
    return icmGetNextReg(_proc, previous);
}

// Find a processor register by its index
icmRegInfoP icmProcessorObject::regByIndex(Uns32 index)
{
    return icmGetRegByIndex(_proc, index);
}

// Find a processor register by its name
icmRegInfoP icmProcessorObject::regByName(const char *name)
{
    return icmGetRegByName(_proc, name);
}

// Read a register from a processor using an icmRegInfoP handle
bool icmProcessorObject::readReg(icmRegInfoP reg, void *buffer)
{
    return icmReadRegInfoValue(_proc, reg, buffer);
}

// Write a register from a processor using an icmRegInfoP handle
bool icmProcessorObject::writeReg(icmRegInfoP reg, void *buffer)
{
    return icmWriteRegInfoValue(_proc, reg, buffer);
}

// Read a named register from a processor
bool icmProcessorObject::readReg(const char *name, void *buffer)
{
    return icmReadReg(_proc, name, buffer);
}

// Write a named register in a processor
bool icmProcessorObject::writeReg(const char *name, void *buffer)
{
    return icmWriteReg(_proc, name, buffer);
}

// Return the processor program counter
Addr icmProcessorObject::getPC(void)
{
    icmProcessorP p = icmGetSMPChild(_proc);

    //
    // For MP processors, return the PC of CPU0
    //
    return p ? icmGetPC(p) : icmGetPC(_proc);
}

ICM_SMP_ITERATOR_FN(setStartAddress)
{
    Addr start = *(Addr *)userData;
    icmSetPC(processor, start);
}

// Set the processor program counter
void icmProcessorObject::setPC(Addr pc)
{
     icmProcessorP p = icmGetSMPChild(_proc);

     //
     // For MP processors, set the PC on all child procesor objects
     //
     if( p )
         icmIterAllChildren(_proc, setStartAddress, (void *)&pc);
     else
     {
         icmSetPC(_proc, pc);
     }
}

// return the register usage-type enumeration
icmRegUsage icmProcessorObject::regUsage(icmRegInfoP reg)
{
    return icmGetRegInfoUsage(reg);
}

// return the bit-width of the register
Uns32 icmProcessorObject::regBits(icmRegInfoP reg)
{
    return icmGetRegInfoBits(reg);
}

icmNetPortP icmProcessorObject::nextNetPort(icmNetPortP current)
{
    return icmNextProcessorNetPort(_proc, current);
}

icmNetPortP icmProcessorObject::findNetPort(const char *name) {
    return icmFindProcessorNetPort(_proc, name);
}

// For processors without delay slots, or for a non-delay-slot instruction
// of a processor with delay slots, return the processor program counter and
// set 'delaySlotOffset' to zero. For a delay slot instruction, return the
// program counter of the preceding jump instruction and set 'delaySlotOffset'
// to the offset in bytes of the delay slot instruction.
Addr icmProcessorObject::getPCDS(Uns8 *delaySlotOffset)
{
    return icmGetPCDS(_proc, delaySlotOffset);
}

// Call the processor-specific register dump
void icmProcessorObject::dumpRegisters(void)
{
    return icmDumpRegisters(_proc);
}

// Disassemble the instruction at the passed address
const char* icmProcessorObject::disassemble(Addr simAddr)
{
    return icmDisassemble(_proc, simAddr);
}

// Suspend execution of the current processor and return immediately from
// simulate with icmStopReason ICM_SR_INTERRUPT.
void icmProcessorObject::interrupt(void)
{
    icmInterrupt();
}

// Suspend execution of the current processor and return immediately from
// simulate with icmStopReason ICM_SR_YIELD (typically used within icmMemReadFn
// or icmMemWriteFn callback).
void icmProcessorObject::yield(void)
{
    icmYield(_proc);
}

// Terminate execution of the current processor and return immediately from
// simulate with icmStopReason ICM_SR_EXIT (typically used within icmMemReadFn
// or icmMemWriteFn callback).
void icmProcessorObject::exit(void)
{
    icmExit(_proc);
}

// Terminate execution of the current processor and return immediately from
// simulate with icmStopReason ICM_SR_FINISH (typically used within icmMemReadFn
// or icmMemWriteFn callback).
void icmProcessorObject::finish(void)
{
    icmFinish(_proc, 0);
}

// Terminate execution of the current processor and return immediately from
// simulate with icmStopReason ICM_SR_FINISH (typically used within icmMemReadFn
// or icmMemWriteFn callback).
void icmProcessorObject::finish(Int32 status)
{
    icmFinish(_proc, status);
}

// Halt execution of the current processor and return immediately from simulate
// with icmStopReason ICM_SR_HALT (typically used within icmMemReadFn or
// icmMemWriteFn callback).
void icmProcessorObject::halt(void)
{
    icmHalt(_proc);
}

/// Return simulation finish status
Int32 icmProcessorObject::status(void)
{
    return icmGetStatus();
}

// Enable tracing for the processor after 'iDelta' more instructions
void icmProcessorObject::traceOnAfter(Uns64 iDelta)
{
    icmTraceOnAfter(_proc, iDelta);
}

// Disable tracing for the processor after 'iDelta' more instructions
void icmProcessorObject::traceOffAfter(Uns64 iDelta)
{
    icmTraceOffAfter(_proc, iDelta);
}

// Enable trace buffer for the passed processor
void icmProcessorObject::enableTraceBuffer(void)
{
    icmEnableTraceBuffer(_proc);
}

// Disable trace buffer for the passed processor
void icmProcessorObject::disableTraceBuffer(void)
{
    icmDisableTraceBuffer(_proc);
}

// Dump the processor trace buffer (if tracing enabled by ICM_ATTR_TRACE_BUFFER)
void icmProcessorObject::dumpTraceBuffer(void)
{
    icmDumpTraceBuffer(_proc);
}

// Return the object from the icm structure,
// creating it if not already there
icmProcessorObject *icmProcessorObject::object(icmProcessorP proc) {
    void *p = icmGetProcessorHandle(proc);
    if(!p) {
        icmProcessorObject *n = new icmProcessorObject(proc);
        icmSetProcessorHandle(proc, n);
        p = n;
    }
    return (icmProcessorObject*) p;
}

// Return the parent of this SMP processor
icmProcessorObject *icmProcessorObject::getSMPParent() {
    icmProcessorP n = icmGetSMPParent(_proc);
    if(n) {
        return object(n);
    } else {
        return NULL;
    }
}

// Return the first child of this SMP processor
icmProcessorObject *icmProcessorObject::getSMPChild() {
    icmProcessorP n = icmGetSMPChild(_proc);
    if(n) {
        return object(n);
    } else {
        return NULL;
    }
}

// Return the previous sibling of this SMP processor
icmProcessorObject *icmProcessorObject::getSMPPrevSibling() {
    icmProcessorP n = icmGetSMPPrevSibling(_proc);
    if(n) {
        return object(n);
    } else {
        return NULL;
    }
}

// Return the next sibling of this SMP processor
icmProcessorObject *icmProcessorObject::getSMPNextSibling() {
    icmProcessorP n = icmGetSMPNextSibling(_proc);
    if(n) {
        return object(n);
    } else {
        return NULL;
    }
}

// Return the index number of this SMP processor
Uns32 icmProcessorObject::getSMPIndex() {
    return icmGetSMPIndex(_proc);
}

// Set an address breakpoint.
// Hitting this will cause the simulator to return.
void icmProcessorObject::setAddressBreakpoint(Addr address) {
    icmSetAddressBreakpoint(_proc, address);
}

// Clear an address breakpoint
void icmProcessorObject::clearAddressBreakpoint(Addr address) {
    icmClearAddressBreakpoint(_proc, address);
}

// Set an instruction count breakpoint.
// This will replace any existing instruction count breakpoint.
// Hitting this will cause the simulator to return.
void icmProcessorObject::setICountBreakpoint(Uns64 delta) {
    icmSetICountBreakpoint(_proc, delta);
}

// Clear the instruction count breakpoint, if it exists.
void icmProcessorObject::clearICountBreakpoint() {
    icmClearICountBreakpoint(_proc);
}

/// Find processor object by name

icmProcessorObject *icmProcessorObject::find(const char *name) {
    icmProcessorObject* pobj = 0;
    icmProcessorP proc = icmFindProcessorByName(name);
    if(proc) {
        pobj = icmProcessorObject::object(proc);
    }
    return pobj;
}


////////////////////////////////////////////////////////////////////////////////
//
// icmPseObject
//
////////////////////////////////////////////////////////////////////////////////

// public

// Constructor

icmPseObject::icmPseObject(
    const char        *name,
    const char        *objectFile,
    icmAttrListObject *userAttrs,
    const char        *semiHostFile,
    const char        *semiHostSymbol
) {
    icmAttrListP _userAttrs = userAttrs ? userAttrs->getUserAttrs() : 0;
    _pse = icmNewPSE(name, objectFile, _userAttrs, semiHostFile, semiHostFile ? semiHostSymbol : 0);
}

// Connect a PSE bus port to the range lowAddr:highAddr of the bus.
// 'isMaster' specifies whether the port is a bus master (i.e. written
// by the PSE) or a slave (read by the PSE).
void icmPseObject::connect(
    icmBusObject &bus,
    const char   *portName,
    bool          isMaster,
    Addr          lowAddr,
    Addr          highAddr
) {
    icmConnectPSEBus(
        _pse, bus.getBus(), portName, isMaster?True:False, lowAddr, highAddr
    );
}

void icmPseObject::connect(
    icmBusObject &bus,
    const char   *portName,
    bool          isMaster
) {
    icmConnectPSEBusDynamic(_pse, bus.getBus(), portName, isMaster?True:False);
}


// Connect a PSE instance port to a net
void icmPseObject::connect(
    icmNetObject &net,
    const char   *portName,
    icmDirection  direction
) {
    icmConnectPSENet(_pse, net.getNet(), portName, direction);
}

// Add an intercept shared object to a PSE
void icmPseObject::addInterceptObject(
    const char        *instanceName,
    const char        *interceptFile,
    const char        *interceptSymbol,
    icmAttrListObject *userAttrs
) {
    icmAttrListP _userAttrs = userAttrs ? userAttrs->getUserAttrs() : 0;

    icmAddPseInterceptObject(
        _pse,
        instanceName,
        interceptFile,
        interceptSymbol,
        _userAttrs
    );
}

// tell MPD where to get the PSE gdb, and any special flags
void icmPseObject::setGdbPath(
    const char   *path,     // path to gdb exe
    const char   *flags     // special flags required by this gdb
) {
    icmSetPSEGdbPath(_pse, path, flags);
}

// Return next netPort
icmNetPortP icmPseObject::nextNetPort(icmNetPortP current)
{
    return icmNextPseNetPort(_pse, current);
}

// search for a net port by name
icmNetPortP icmPseObject::findNetPort(const char *name) {
    return icmFindPseNetPort(_pse, name);
}

// Return the processor name
const char *icmPseObject::getName() {
    return icmGetPSEName(_pse);
}

////////////////////////////////// CLP Class //////////////////////////////////

icmCLPObject::icmCLPObject(const char *clientName, icmCLPArgClass select) {
    _parser = icmCLParser(clientName, select);
}

icmCLPObject::~icmCLPObject() {
    icmCLParserOld(_parser);
}

void icmCLPObject::addArg(
    const char    *name,
    const char    *shortName,
    const char    *argDesc,
    const char    *group,
    icmCLPArgType type,
    void         *ptr,
    const char    *description,
    Uns32         useMask,
    Uns32         userData,
    Bool          mandatory
) {
    icmCLParserAdd (
        _parser,
        name,
        shortName,
        group,
        argDesc,
        type,
        ptr,
        description,
        useMask,
        userData,
        mandatory
    );
}

void icmCLPObject::usageMessage(const char *message) {
    icmCLParserUsageMessage(_parser, message);
}


Bool icmCLPObject::parse(int argc, const char *argv[]) {
    return icmCLParseArgs(_parser, argc, argv);
}

Bool icmCLPObject::parse(const char *file) {
    return icmCLParseFile(_parser, file);
}

Bool icmCLPObject::argUsed(const char *argName) {
    return icmCLParseArgUsed(_parser, argName);
}


