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
 * PLEASE USE ImpPublic/include/host/op/op.hpp
 */

#ifndef ICMCPUMANAGER_HPP_
#define ICMCPUMANAGER_HPP_

// START C++ LANGUAGE DEFINITIONS

#include <string>

#ifdef __BORLANDC__
    #include <sys/types.h>
#endif

using namespace std;

extern "C" {
#include "icmCpuManager.h"
}

namespace icmCpuManager {

/// ICM platform attributes can be combined using the "|" operator

static inline icmInitAttrs    operator| (icmInitAttrs    lhs, icmInitAttrs    rhs) {
    return (icmInitAttrs) ((int)lhs | (int)rhs);
}

/// ICM processor attributes can be combined using the "|" operator

static inline icmNewProcAttrs operator| (icmNewProcAttrs lhs, icmNewProcAttrs rhs) {
    return (icmNewProcAttrs) ((int)lhs | (int)rhs);
}

/// (For internal use only)

class icmCpuManagerItem {

    public:
        icmCpuManagerItem(void);
        icmCpuManagerItem(bool platform);
        ~icmCpuManagerItem(void);

    private:
        static bool _cpuManagerInited;
};

class icmProcessorObject;


/// The ICM Platform. Note that at present only one is allowed.

class icmPlatform : icmCpuManagerItem {

    public:
        /// Platform constructor
        /// @param name        Name of platform.
        /// @param simAttrs    Bit-field of (global) simulator options
        /// @param protocol    Optional protocol (only "rsp" is supported)
        /// @param port        Optional port number
        icmPlatform(
            const char  *name,
            icmInitAttrs simAttrs  = ICM_INIT_DEFAULT,
            const char  *protocol  = 0,
            Uns32        port      = 0
        );

        /// The destructor.
        /// Note that this is the only destructor that has an effect.

        ~icmPlatform(void) { }

        /// Set the simulation time precision.
        /// @param  precision   all event times are rounded to this granularity (default 1e-9 seconds)
        /// @return True if successful.

        bool setSimulationTimePrecision(icmTime precision) {
            return icmSetSimulationTimePrecision(precision);
        }

        /// Set the simulation time precision.
        /// @param  precision   all event times are rounded to this granularity (default 1e-9 seconds)
        /// @return True if successful.

        bool setSimulationTimePrecision(double precision) {
            return icmSetSimulationTimePrecisionDouble(precision);
        }

        /// Set the simulation time slice size (quantum).
        /// Only used by icmSimulatePlatform()
        /// Takes effect at the end of any current time slice
        /// @param  slice    New value of slice (quantum)
        /// @return True if successful.

        bool setSimulationTimeSlice(icmTime slice){
            return icmSetSimulationTimeSlice(slice);
        }

        /// Set the simulation time slice size (quantum).
        /// Only used by icmSimulatePlatform()
        /// Takes effect at the end of any current time slice
        /// @param  slice    New value of slice (quantum)
        /// @return True if successful.

        bool setSimulationTimeSlice(double slice) {
            return icmSetSimulationTimeSliceDouble(slice);
        }

        /// Set the simulation stop time (for icmSimulatePlatform) - takes effect at the
        /// end of any current time slice. icmSimulatePlatform will return when this stop
        /// time is reached
        /// @param  time     Time after which icmSimulatePlatform() will return,
        ///                  Unless some other event of error occurs.

        bool setSimulationStopTime(icmTime time) {
            return icmSetSimulationStopTime(time);
        }

        /// Set the simulation stop time (for icmSimulatePlatform) - takes effect at the
        /// end of any current time slice. icmSimulatePlatform will return when this stop
        /// time is reached
        /// @param  time     Time after which icmSimulatePlatform() will return,
        ///                  Unless some other event of error occurs.

        bool setSimulationStopTime(double time) {
            return icmSetSimulationStopTimeDouble(time);
        }

        /// Set an LFSR seed for randomizing the order in which processors are processed in
        /// a time slice. The default is no randomisation (seed=0).
        /// @param  seed        New 32bit seed value.

        void setSimulationRandomSeed(Uns32 seed) { icmSetSimulationRandomSeed(seed); }

        /// Set the wallclock factor
        /// @param  factor      Wallclock factor (1=try to run in realtime)

        void setWallClockFactor(double factor) { icmSetWallClockFactor(factor); }

        /// Simulate the platform using the default scheduling scheme, using time slice
        /// and stop time set by isetSimulationTimeSlice and setSimulationStopTime.
        /// The return value is the processor that has caused simulation to stop, or NULL
        /// if no processor has caused simulation to stop (e.g. the stop time has been
        /// reached). The reason why a processor caused simulation to stop can be found
        /// using getStopReason.
        ///
        /// If setDebugMode has been used to enable debug mode, go interative.
        /// @return     The last processor to be executed.
        icmProcessorObject *simulate();

        /// Prepare for simulation, when icmPlatform::simulate()
        /// or icmProcessor::simulate() are not used.
        /// Causes all PSEs and Processors to be initialised.

        void simulationStarting() { icmSimulationStarting(); }

        /// Tidy up after simulation. Normally this is not required.

        void simulationEnding() { icmSimulationEnding(); }

        /// Advance simulation time.
        /// @param time   ABSOLUTE (not relative) time.

        bool advanceTime(icmTime time) { return icmAdvanceTime(time); }

        /// Advance simulation time.
        /// @param time   ABSOLUTE (not relative) time.
        bool advanceTime(double time) { return icmAdvanceTimeDouble(time); }

        /// Get a pointer to the platform object. Note that the platform is a singleton.
        /// @return     Platform object.

        static icmPlatform* Instance() { return _singleton; }

        /// Print all platform nets and their connections.
        /// Used debug complex platform connectivity. Note that the list includes
        /// nets constructed by TLM wrappers.

        void printNetConnections() { icmPrintNetConnections(); }

    private:
        const char         *_name;       // for future use
        static icmPlatform *_singleton;  // pointer to single instance
};

/// This is the interface that a handler for a icmStopReason must implement
/// A icmProcessorObject (below) does not implement a default handler.

class icmHandleSimStop_if
{
 public:
    icmHandleSimStop_if() {};
    virtual ~icmHandleSimStop_if() {};

    /// Your implementation should overload this function.
    /// @param  processor      Current processor.
    /// @param  reason         Why the simulation stopped.

    virtual icmStopReason simStopHandler(icmProcessorObject* processor, icmStopReason reason ) = 0;
};

/// List of user defined attributes to be supplied to a model.

class icmAttrListObject: icmCpuManagerItem
{

public:
    /// User attribute list constructor.

    icmAttrListObject();

    /// User attribute list destructor (not usually called explicitly).

    ~icmAttrListObject() {}

    /// Add an int attribute.
    /// @param  name   Attribute name.
    /// @param  value  32-bit integer value.

    void addAttr(const char *name, int value);

    /// Add an Uns64 attribute.
    /// @param name   Attribute name.
    /// @param value  64-bit integer value.

    void addAttr(const char *name, Uns64 value);

    /// Add a double attribute.
    /// @param name   Attribute name.
    /// @param value  double value.

    void addAttr(const char *name, double value);

    /// Add a string attribute.
    /// @param name   Attribute name.
    /// @param value  string value.

    void addAttr(const char *name, const char *value);

    /// Add a pointer attribute.
    /// @param name   Attribute name.
    /// @param value  pointer value.

    void addAttr(const char *name, void *value);

    /// Get corresponding C attribute structure.
    /// @return  C list.
    icmAttrListP getUserAttrs();

private:
    icmAttrListP _userAttrs;
};

/// Add read and write callbacks to a memory region. This object is passed to the
/// mapExternalMemory() methods.

class icmMemCallback
{

public:
    typedef void (*readCallback)(
        Addr         address,
        Uns32        bytes,
        void        *value,
        void        *userData,
        const void  *processor
    );

    typedef void (*writeCallback)(
        Addr        address,
        Uns32       bytes,
        const void *value,
        void       *userData,
        const void *processor
    );

    /// Constructor
    /// @param rcb         Read callback function.
    /// @param wcb         Write callback function.
    /// @param userData    User data passed to callback.

    icmMemCallback(readCallback rcb, writeCallback wcb, void *userData);

    /// Used internally. Causes the callback to be made.
    void callRead (Addr address, Uns32 bytes, void *value, void *processor);

    /// Used internally. Causes the callback to be made.
    void callWrite(Addr address, Uns32 bytes, const void *value, void *processor);

    /// Used internally. Detect presence of read/write callbacks
    bool hasRCB() {return _rcb != 0;}
    bool hasWCB() {return _wcb != 0;}

private:
    readCallback  _rcb;
    writeCallback _wcb;
    void         *_user;

};

/// ICM bus object.
/// Represents an address space and the fabric that transports bus transactions.

class icmBusObject: icmCpuManagerItem
{

public:
    /// Constructor. Used in most circumstances.
    /// @param name        A unique instance name for this bus.
    /// @param addressBits Required number of address bits.

    icmBusObject(const char *name, Uns8 addressBits);

    /// Constructor. Used by TLM. The unique name is supplied as two parts
    /// for convenience and concatenated internally.
    /// @param prefix      1st part of the unique instance name for this bus.
    /// @param name        2nd part of the unique instance name for this bus.
    /// @param addressBits Required number of address bits.

    icmBusObject(const char *prefix, const char *name, Uns8 addressBits);

    /// The destructor.

    ~icmBusObject() {}


    /// Invoke read callback on read accesses
    /// @param scope     If non-null, restrict sensitivity to this processor.
    /// @param lowAddr   Lower limit of address range.
    /// @param highAddr  Upper limit of address range.
    /// @param readCB    Callback function.
    /// @param userData  (optional) User data passed to callback.

    void addReadCallback(
        icmProcessorObject *scope,
        Addr                lowAddr,
        Addr                highAddr,
        icmMemWatchFn       readCB,
        void               *userData = 0
    );

    /// Invoke read callback on write accesses
    /// @param scope     If non-null, restrict sensitivity to this processor.
    /// @param lowAddr   Lower limit of address range.
    /// @param highAddr  Upper limit of address range.
    /// @param writeCB   Callback function.
    /// @param userData  (optional) User data passed to callback.

    void addWriteCallback(
       icmProcessorObject *scope,
       Addr                lowAddr,
       Addr                highAddr,
       icmMemWatchFn       writeCB,
       void               *userData = 0
    );

    /// Invoke fetch callback on read accesses
    /// @param scope     If non-null, restrict sensitivity to this processor.
    /// @param lowAddr   Lower limit of address range.
    /// @param highAddr  Upper limit of address range.
    /// @param fetchCB   Callback function.
    /// @param userData  (optional) User data passed to callback.

    void addFetchCallback(
        icmProcessorObject *scope,
        Addr                lowAddr,
        Addr                highAddr,
        icmMemWatchFn       fetchCB,
        void               *userData = 0
    );

    /// Map the passed address range externally to the processor using callbacks
    /// @param portName   Name of the port to be created.
    /// @param priv       Set the read/write/execute permissions of this port.
    /// @param lowAddr    Lower boundary of address range.
    /// @param highAddr   Upper boundary of address range.
    /// @param readCB     Read callback
    /// @param writeCB    Write callback
    /// @param userData   User data passed to the callbacks.

    void mapExternalMemory(
        const char   *portName,
        icmPriv       priv,
        Addr          lowAddr,
        Addr          highAddr,
        icmMemReadFn  readCB,
        icmMemWriteFn writeCB,
        void         *userData
    );

    /// Map the passed address range externally to the processor using callbacks.
    /// Uses the icmMemCallback object instead of function pointers.
    /// @param portName   Provides a logical name for the mapped region.
    /// @param priv       Set the read/write/execute permissions of this port.
    /// @param lowAddr    Lower boundary of address range.
    /// @param highAddr   Upper boundary of address range.
    /// @param rcb        The icmMemCallback object

    void mapExternalMemory(
        const char     *portName,
        icmPriv         priv,
        Addr            lowAddr,
        Addr            highAddr,
        icmMemCallback *rcb
    );

    /// Map the passed address range externally to the processor using callbacks.
    /// Uses the icmMemCallback object instead of function pointers.
    /// @param portName   Provides a logical name for the mapped region.
    /// @param priv       Set the read/write/execute permissions of this port.
    /// @param lowAddr    Lower boundary of address range.
    /// @param highAddr   Upper boundary of address range.
    /// @param memory      Pointer to pre-allocated memory.
    /// @param rcb        The icmMemCallback object

    void mapExternalNativeMemory(
        const char     *portName,
        void           *memory,
        icmPriv         priv,
        Addr            lowAddr,
        Addr            highAddr,
        icmMemCallback *cb
    );

    /// Create ICM memory at the given address range. Note that large memories can be created
    /// without affecting performance; the underlying memory is not allocated until it is used.
    /// @param portName   Provides a logical name for the memory.
    /// @param priv       Set the read/write/execute permissions of this port.
    /// @param lowAddr    Lower boundary of address range.
    /// @param highAddr   Upper boundary of address range.

    void mapLocalMemory(
        const char *portName,
        icmPriv     priv,
        Addr        lowAddr,
        Addr        highAddr
    );

    /// Map some of the user's memory onto a bus.
    /// The use must allocate this space before calling this function.
    /// @param portName    Provide a unique logical name for the memory.
    /// @param memory      Pointer to pre-allocated memory.
    /// @param priv        Read/write/execute permissions of this memory range.
    /// @param lowAddress  Lower boundary of address range.
    /// @param hiAddress   Upper boundary of address range.

     void mapNativeMemory(
        void       *memory,
        icmPriv     priv,
        Addr        lowAddress,
        Addr        hiAddress
     );

    /// Create a bus bridge between this bus and another so that any access
    /// on this bus starting at lowAddrSlave will be mapped to the
    /// other bus. Addresses on the other bus will start at lowAddrMaster.
    /// @param master              The bus to bridge to.
    /// @param bridgeName          Name of the new bridge.
    /// @param portNameOnThis      Name to appear on this bus.
    /// @param portNameOnMaster    Name to appear on the master bus.
    /// @param lowAddrMaster       Lower boundary on remote bus.
    /// @param highAddrMaster      Upper boundary on remote bus.
    /// @param lowAddrSlave        Lower boundary of local bus.

    void newBridge(
        icmBusObject &master,
        const char   *bridgeName,
        const char   *portNameOnThis,
        const char   *portNameOnMaster,
        Addr          lowAddrMaster,
        Addr          highAddrMaster,
        Addr          lowAddrSlave
    );

    /// Load an object file onto this bus.
    /// @param objectFile     Path to the object file.
    /// @param loadPhysical   Use physical load addresses from the file, rather than logical.
    /// @param verbose        If true print a summary of the sections as they are loaded.

    bool loadMemory(
        const char     *objectFile,
        bool            loadPhysical,
        bool            verbose
    );

    /// Load an object file onto this bus.
    /// @param objectFile     Path to the object file.
    /// @param attrs          Loader control attributes

    bool loadMemory(
        const char     *objectFile,
        icmLoaderAttrs  attrs      = ICM_LOAD_DEFAULT
    );

    /// Print the master and slave connections on this bus
    void printConnections(void);

    /// Get corresponding C bus structure (for internal use).
    /// @return  The C structure.
    icmBusP getBus();

    /// Read data directly from this bus.
    /// Note that a peripheral on the given address on the  bus will be
    /// triggered as if the read originated in a processor or peripheral model.
    /// @param address        Base address of area to be read.
    /// @param data           Pointer to data to be copied to.
    /// @param bytes          Number of bytes to be copied.
    /// @param processor      Real access if non-zero (as opposed to simulation artifact).

    void read(Addr address, void *data, Uns32 bytes, void *processor);

    /// Write data directly to this bus.
    /// Note that a peripheral on the given address on this bus will be
    /// triggered as if the read originated in a processor or peripheral model.
    /// @param address        Base address of area to be read.
    /// @param data           Pointer to data to be copied to.
    /// @param bytes          Number of bytes to be copied.
    /// @param processor      Real access if non-zero (as opposed to simulation artifact).

    void write(Addr address, void *data, Uns32 bytes, void *processor);

    /// Create a temporary bridge to another bus.
    /// An access on the other bus within the region lowAddr:highAddr
    /// will access data on this bus.
    /// The address will be Addr-lowAddr+lowAddrSlave
    /// @param slave              The bus to bridge to.
    /// @param lowAddr            Lower boundary of local address range.
    /// @param highAddr           Upper boundary of local address range.
    /// @param lowAddrSlave       Base address on remote bus.
    void bridge(
        icmBusObject &slave,
        Addr          lowAddr,
        Addr          highAddr,
        Addr          lowAddrSlave
    );

    /// Remove a temporary bridge to another bus
    /// @param lowAddr            Lower boundary of local address range.
    /// @param highAddr           Upper boundary of local address range.

    void unbridge(
        Addr          lowAddr,
        Addr          highAddr
    );

private:
    icmBusP _bus;
};


/// The ICM Net object.
/// Represents a wire, typically used for interrupt or reset signalling.

class icmNetObject: icmCpuManagerItem
{

public:

    /// Constructor
    /// @param   name     A unique name for the net.
    icmNetObject(const char *name);

    /// Destructor.

    ~icmNetObject() {}

    /// Write a value to the net.
    /// @param   netValue   New value to write to the net.
    ///                     Note that calling the write function will cause net
    ///                     propagation, even if the value does not change.

    bool write(Uns32 netValue);

    /// Get the corresponding ICM C net structure (for internal use).
    icmNetP getNet();

    /// Add a callback triggered when the net is written.
    /// @param   cb      Function to be called.
    /// @param   user    User rdata passed to callback.

    void addCallback(icmNetFn cb, void *user);

private:
    icmNetP _net;
};

/// The ICM MMC Instance.

class icmMmcObject: icmCpuManagerItem
{

public:
    /// MMC constructor. Creates an MMC instance.
    /// @param name          Instance name.
    /// @param modelFile     Path to model (dll or shared object).
    /// @param modelSymbol   Name of attribute table in model.
    /// @param initialAttrs  List of user defined attributes to be passed to the instance.
    /// @param transparent   True if this model is be transparent
    ///                      (See the MMC modeling guide).

    icmMmcObject(
        const char        *name,
        const char        *modelFile,
        const char        *modelSymbol,
        icmAttrListObject *initialAttrs,
        bool               transparent
    );

    /// Destructor.

    ~icmMmcObject() {}

    /// Connect this MMC to a bus.
    /// @param bus       Bus to connect.
    /// @param portName  Name of a port which must exist on the MMC.
    /// @param isMaster  If true, this is a connection to a master port.
    ///                  If false, it is to a slave port

    void connect(
        icmBusObject &bus,
        const char   *portName,
        bool          isMaster
    );

    /// Return the ICM MMC structure (for internal use).
    icmMmcP getMMC();

private:
    icmMmcP _mmc;
};

/// The ICM memory Object.

class icmMemoryObject: icmCpuManagerItem
{

public:
    /// Memory constructor. Creates a memory instance.
    /// @param name      Unique name for this memory instance.
    /// @param priv      Required read/write/execute privilege.
    /// @param highAddr  Maximum address of this memory (0 is the minimum).

    icmMemoryObject(
        const char *name,
        icmPriv     priv,
        Addr        highAddr
    );

    /// Destructor.

    ~icmMemoryObject() {}

    /// Read bytes from the memory into a buffer.
    /// @param simAddress    Offset in the memory to start reading from.
    /// @param buffer        Buffer to receive the data (allocated by the user).
    /// @param size          Number of bytes to transfer.

    void read(Addr simAddress, void *buffer, Uns32 size);

    /// Write bytes into the memory from a buffer.
    /// @param simAddress    Offset in the memory to start writing to.
    /// @param buffer        Buffer to source the data.
    /// @param size          Number of bytes to transfer.

    void write(Addr simAddress, const void *buffer, Uns32 size);

    /// Inform the simulator that this range  has been modified
    /// by an external agent. This is required when the memory contains
    /// executable code because the dynamic code translator might have
    /// cached its translation. Code modification by PSE or Processor
    /// models is detected by the simulator so does not require notification.
    /// @param lowAddr    Lower end of range.
    /// @param highAddr   Upper end of range.

    void flush(Addr lowAddr, Addr highAddr) {
        icmFlushMemory(_memory, lowAddr, highAddr);
    }

    /// Connect a memory object to a bus.
    /// @param portName    Name of the memory port.
    /// @param bus         The bus to connect.
    /// @param lowAddr     Intended base address of the memory in the
    ///                    bus address space.
    void connect(
        const char   *portName,
        icmBusObject &bus,
        Addr         lowAddr
    );

    /// Get corresponding C shared memory structure (for internal use).
    icmMemoryP getMemory();

private:
    icmMemoryP _memory;
};

/// The ICM processor instance.

class icmProcessorObject: icmCpuManagerItem
{
protected:

/// Free a processor instance
void freeProcessor(void);

public:
    /// Processor instance constructor.
    /// @param name           Unique instance name.
    /// @param type           The type of the processor. Should match the 'N'
    ///                       in the VLNV.
    /// @param cpuId          An integer which should be unique
    ///                       among processor instances.
    /// @param cpuFlags       Mode control flags used by some processor models.
    /// @param addressBits    Number of bits used by code and data address buses.
    /// @param modelFile      Path to the model files (dll or shared object).
    /// @param modelSymbol    deprecated (supply null).
    /// @param procAttrs      (optional) processor simulator attributes.
    ///                       Used to control how the simulator treats this model.
    /// @param initialAttrs   (optional) list of user-defined attributes.
    ///                       Used to configure options in the model.
    /// @param semiHostFile   (optional) Path to semihost library (dll or shared object).
    /// @param semiHostSymbol (deprecated (supply null).)

    icmProcessorObject(
        const char        *name,
        const char        *type,
        Uns32              cpuId,
        Uns32              cpuFlags,
        Uns8               addressBits,
        const char        *modelFile,
        const char        *modelSymbol,
        icmNewProcAttrs    procAttrs      = ICM_ATTR_DEFAULT,
        icmAttrListObject *initialAttrs   = 0,
        const char        *semiHostFile   = 0,
        const char        *semiHostSymbol = 0
    );

    /// Processor instance constructor (without deprecated arguments)
    /// @param name           Unique instance name.
    /// @param cpuFlags       Mode control flags used by some processor models.
    /// @param modelFile      Path to the model files (dll or shared object).
    /// @param procAttrs      (optional) processor simulator attributes.
    ///                       Used to control how the simulator treats this model.
    /// @param initialAttrs   (optional) list of user-defined attributes.
    ///                       Used to configure options in the model.
    /// @param semiHostFile   (optional) Path to semihost library (dll or shared object).

    icmProcessorObject(
        const char        *name,
        const char        *modelFile,
        Uns32              cpuFlags       = 0,
        icmNewProcAttrs    procAttrs      = ICM_ATTR_DEFAULT,
        icmAttrListObject *initialAttrs   = 0,
        const char        *semiHostFile   = 0
    );

    // Return the object from the icm structure,
    // creating it if not already there
    static icmProcessorObject *object(icmProcessorP exist);

    // existing processor needs a C object
    icmProcessorObject(icmProcessorP exist);


    // The destructor.
    ~icmProcessorObject() {}

    /// Simulate for up to the passed number of clocks.
    /// @param instructions   Number of clocks.
    /// @return               Reason for stopping.
    /// Note that the simulation might stop early (for example, the processor
    /// may exit) in which case the returned icmStopReason can be used to
    /// determine the cause.

    icmStopReason simulate(Uns64 clocks);

    /// Return the ICM processor descriptor (for internal use).

    icmProcessorP getProcessorP(void) { return _proc; }

    /// Connect the processor to the instruction and data busses.
    /// @param instructionBus  The instruction bus. Code is fetched from here.
    /// @param dataBus         The data bus. Note that the processor can be
    ///                        connected to the same bus twice.
    /// Note that this method if not used if the processor is connected to
    /// transparent MMCs instead (see below).

    void connect(
        icmBusObject &instructionBus,
        icmBusObject &dataBus
    );

    /// Connect the processor to the given by by port name.
    /// @param portName        The name of the processor port.
    /// @param bus             The bus.
    ///                        connected to the same bus twice.
    /// Note that this method if not used if the processor is connected to
    /// transparent MMCs instead (see below).

    void connect(
        const char   *portName,
        icmBusObject &bus
    );

    /// connect the processor to ports on transparent MMCs
    /// @param instruction     MMC port for instructions. Code is fetched from here.
    /// @param instructionPort Name of a port on the MMC.
    /// @param data            MMC port for data.
    /// @param dataPort        Name of a port on the MMC.

    void connect(
        icmMmcObject &instruction,     // instruction MMC by ref
        const char   *instructionPort, // port on instruction MMC
        icmMmcObject &data,            // data MMC by ref
        const char   *dataPort         // port on data MMC
    );

    /// connect a processor net port to a net.
    /// @param net         Name of the connected net.
    /// @param portName    Name of an existing net port on the processor model.
    /// @param direction   Usually ICM_INPUT on a processor.

    void connect(
        icmNetObject &net,
        const char   *portName,
        icmDirection  direction
    );

    /// Add a supplementary intercept shared object for the processor.
    /// This method in not supported in OVPsim.
    /// @param instanceName     Unique instance name for this object.
    /// @param interceptFile    Path to the intercept object (dll or shared object).
    /// @param interceptSymbol  Name of the attributes table in the object file.
    /// @param userAttrs        (optional) List of user attributes to be applied
    ///                         to the instance.
    void addInterceptObject(
        const char        *instanceName,
        const char        *interceptFile,
        const char        *interceptSymbol,
        icmAttrListObject *userAttrs = 0
    );

    /// Invoke read callback on read accesses
    /// @param lowAddr   Lower limit of address range.
    /// @param highAddr  Upper limit of address range.
    /// @param readCB    Callback function.
    /// @param userData  (optional) User data passed to callback.

    void addReadCallback(
        Addr          lowAddr,
        Addr          highAddr,
        icmMemWatchFn readCB,
        void         *userData = 0
    );

    /// Invoke read callback on write accesses
    /// @param lowAddr   Lower limit of address range.
    /// @param highAddr  Upper limit of address range.
    /// @param writeCB   Callback function.
    /// @param userData  (optional) User data passed to callback.

    void addWriteCallback(
        Addr          lowAddr,
        Addr          highAddr,
        icmMemWatchFn writeCB,
        void         *userData = 0
    );

    /// Invoke fetch callback on read accesses
    /// @param lowAddr   Lower limit of address range.
    /// @param highAddr  Upper limit of address range.
    /// @param fetchCB   Callback function.
    /// @param userData  (optional) User data passed to callback.

    void addFetchCallback(
        Addr          lowAddr,
        Addr          highAddr,
        icmMemWatchFn fetchCB,
        void         *userData = 0
   );

    /// Add gdb path and start-up flags. The multiprocessor debugger
    /// needs to know this information.
    /// @param path   Full path to the debugger executable.
    /// @param flags  Any flags required by gdb to debug this processor configuration.

    void setGdbPath(
        const char *path,
        const char *flags
    );

    /// This processor must not use the supplied gdb.
    void setGdbBasic(void);

    /// Load the processor memory from an object file.
    /// @param objectFile   Path to the object file (currently ELF format only).
    /// @param loadPhysical If true, use the physical addresses from the object file
    ///                     (otherwise use the logical addresses).
    /// @param verbose      If true, print a summary of the sections as they are loaded.
    /// @param useEntry     If true, set the processor PC to the entry point
    ///                     (rather than the hardware reset address).

    bool loadLocalMemory(
        const char    *objectFile,
        bool           loadPhysical,
        bool           verbose,
        bool           useEntry
    );

    /// Load the processor memory from an object file.
    /// @param objectFile   Path to the object file (currently ELF format only).
    /// @param loadAttrs    ICM Loader attributes

    bool loadLocalMemory(
        const char    *objectFile,
        icmLoaderAttrs attrs      = ICM_LOAD_DEFAULT
    );

    /// Load the symbols but not the code.
    /// Use this when the contents is loaded by other means
    /// (such as a boot loader), but the symbols are required for
    /// symbolic  dissassembly, or symbolic interception.

    bool loadSymbols(
            const char     *objectFile,
            bool            loadPhysical = false
    );

    /// Read the file's header and fill the info structure.

    bool readObjectHeader(
        const char    *objectFile,
        ordObjectInfo *info
    );

    /// Load the processor memory with an object file
    /// @param objectFile   Path to the object file (currently ELF format only).

    icmProcessorObject& operator<< (const char *objectFile);

    /// Read from processor memory into a buffer.
    /// @param simAddress   Processor address to start the read.
    /// @param buffer       Buffer to receive the data (allocated by the user).
    /// @param size         Number of bytes to transfer.

    void readMemory(Addr simAddress, void *buffer, Uns32 size);


    /// Write into processor memory from a buffer.
    /// @param simAddress   Processor address to start the read.
    /// @param buffer       Buffer containing the data .
    /// @param size         Number of bytes to transfer.

    void writeMemory(Addr simAddress, const void *buffer, Uns32 size);

    /// Inform the simulator that this range  has been modified
    /// by an external agent. This is required when the memory contains
    /// executable code because the dynamic code translator might have
    /// cached its translation. Code modification by PSE or Processor
    /// models is detected by the simulator so does not require notification.
    /// @param lowAddr    Lower end of range.
    /// @param highAddr   Upper end of range.

    void flush(Addr lowAddr, Addr highAddr) {
        icmFlushProcessorMemory(_proc, lowAddr, highAddr);
    }

    /// Register a handler for the icmStopReason returned by the processor.
    /// @param simStopHnd  Reference to a icmHandleSimStop_if class instance.

    void icmRegisterSimStopHandler(icmHandleSimStop_if &simStopHnd);

    /// Run the processor for this many instructions.
    /// note that this does not advance simulator time or run any other processors
    /// or PSEs.
    /// @param instructions     Maximum number of instructions to run.
    ///                         Other events can curtail the run.
    icmProcessorObject& operator<< (Uns64 instructions);

    /// Return the processor name
    /// @param delimiter    String used to delimit the processor hierarchy.
    /// @return name (in a temporary c-string which cannot be relied on).

    const char *getName(const char *delimiter);

    /// Return the number of instructions executed by the processor
    /// @return total number of instructions executed by this processor so far.

    Uns64 getICount(void);

    /// Return the number of executed instructions and halted instructions of the processor
    /// @return total number of instructions executed by this processor so far.

    Uns64 getClocks(void);

    /// Call the processor-specific register dump. Output goes to the ICM output
    /// stream.

    void dumpRegisters(void);

    /// This iterator returns the next processor register description, given the
    /// previous description. Pass 0 to get the first register description for the
    /// processor.
    /// @param  previous    Previous register or 0 if this is the first call.
    /// @return handle to the processor object.

    icmRegInfoP nextReg(icmRegInfoP previous);

    /// Find a processor register by its index
    /// @param  index     The index
    /// @return handle to the register object.

    icmRegInfoP regByIndex(Uns32 index);

    /// Find a processor register by its name
    /// @param  name     The register name
    /// @return handle to the register object.

    icmRegInfoP regByName(const char *name);

    /// Read a register from a processor using an icmRegInfoP handle
    /// @param reg        handle to the register object.
    /// @param buffer     Pre-allocated space to receive the register value.
    ///                   (must be large enough to hold the value).
    /// @return True if the register is readable.

    bool readReg(icmRegInfoP reg, void *buffer);

    /// Write a register from a processor using an icmRegInfoP handle
    /// @param reg        handle to the register object.
    /// @param buffer     Space containing the register's new value.
    /// @return True if the register is writable.

    bool writeReg(icmRegInfoP reg, void *buffer);

    /// Read a named register from a processor.
    /// @param name       Register name.
    /// @param buffer     Pre-allocated space to receive the register value
    ///                   (must be large enough to hold the value).
    /// @return True if the register exits.

    bool readReg(const char *name, void *buffer);

    /// Write a named register in a processor
    /// @param name       Register name.
    /// @param buffer     Space containing the register's new value
    /// @return True if the register exits.

    bool writeReg(const char *name, void *buffer);

    /// Return the processor's current program counter
    /// @return PC value.

    Addr getPC(void);

    // Set the processor program counter.
    /// @param pc          New PC value.

    void setPC(Addr pc);

    /// Return the register usage-type enumeration
    /// @param reg   Handle to register object.
    /// @return      Register usage enumeration.

    icmRegUsage regUsage(icmRegInfoP reg);

    /// return the bit-width of the register
    /// @param reg   Handle to register object.
    /// @return      Register width in bits.

    Uns32 regBits(icmRegInfoP reg);

    /// Iterator for netPorts
    /// @param current   Handle to netPort or 0 if the first call.
    /// @return          Handle to next netPort or 0 if the last.

    icmNetPortP nextNetPort(icmNetPortP current);

    /// Find a net port by name
    /// @param name    Name of a net port (an interrupt or reset).
    /// @return        Handle to netPort or 0 if no such name.

    icmNetPortP findNetPort(const char *name);


    /// For processors without delay slots, or for a non-delay-slot
    /// instruction of a processor with delay slots, return the processor
    /// program counter and set 'delaySlotOffset' to zero. For a delay slot
    /// instruction, return the program counter of the preceding jump
    /// instruction and set 'delaySlotOffset' to the offset in bytes of the
    /// delay slot instruction.
    /// @param    delaySlotOffset  pointer to the delay slot offset.
    /// @return   Program counter of the preceding jump instruction.

    Addr getPCDS(Uns8 *delaySlotOffset);

    /// Disassemble an instruction.
    /// @param    simAddr    Processor address to disassemble.
    /// @return   text string (in temporary buffer which will be overwritten).

    const char *disassemble(Addr simAddr);

    /// Suspend execution of the current processor and return immediately
    /// from simulate() with icmStopReason ICM_SR_INTERRUPT.

    void interrupt(void);

    /// Suspend execution of the current processor and return immediately
    /// from simulate() with icmStopReason ICM_SR_YIELD (typically used within
    /// icmMemReadFn or icmMemWriteFn callback).

    void yield(void);

    /// Terminate execution of the current processor and return immediately
    /// from simulate() with icmStopReason ICM_SR_EXIT (typically used within
    /// icmMemReadFn or icmMemWriteFn callback).

    void exit(void);

    /// Terminate execution of the current processor and return immediately
    /// from simulate() with icmStopReason ICM_SR_FINISH (typically used within
    /// icmMemReadFn or icmMemWriteFn callback).
    /// This variant finishes with zero exit status

    void finish(void);

    /// Terminate execution of the current processor and return immediately
    /// from simulate() with icmStopReason ICM_SR_FINISH (typically used within
    /// icmMemReadFn or icmMemWriteFn callback).
    /// @param    status   the exit status

    void finish(Int32 status);

    /// Halt execution of the current processor and return immediately from
    /// simulate() with icmStopReason ICM_SR_HALT (typically used within
    /// icmMemReadFn or icmMemWriteFn callback).

    void halt(void);

    /// Return simulation finish status

    Int32 status(void);

    /// Enable tracing for the processor after 'iDelta' more instructions.
    /// Tracing goes to ICM output stream.
    /// @param    iDelta   number of instructions before tracing is turned on.

    void traceOnAfter(Uns64 iDelta);

    /// Disable tracing for the processor after 'iDelta' more instructions.
    /// @param    iDelta   number of instructions before tracing is turned off.

    void traceOffAfter(Uns64 iDelta);

    /// Enable trace buffer for this processor.
    /// The trace buffer records the last 256 instructions, and can be displayed when
    /// simulation stops. There is a smaller overhead than full tracing.

    void enableTraceBuffer(void);

    /// Disable trace buffer for this processor.

    void disableTraceBuffer(void);

    /// Dump the processor trace buffer.
    /// Output goes to the ICM output stream.

    void dumpTraceBuffer(void);

    /// Return the parent of this SMP processor.
    /// @return   icmProcessorObject

    icmProcessorObject *getSMPParent();

    /// Return the first child of this SMP processor.
    /// @return   icmProcessorObject

    icmProcessorObject *getSMPChild();

    /// Return the previous sibling of this SMP processor.
    /// @return   icmProcessorObject

    icmProcessorObject *getSMPPrevSibling();

    /// Return the next sibling of this SMP processor.
    /// @return   icmProcessorObject

    icmProcessorObject *getSMPNextSibling();

    /// Return the index number of this SMP processor.
    /// @return   index number (numbers start at zero).

    Uns32 getSMPIndex();

    /// Return the stop-handler.
    /// @return   pointer to stop-handler object.

    icmHandleSimStop_if *getSimStopHnd() { return _simStopHnd; }

    /// Get the reason (an enumeration) why this processor last stopped.
    /// @return stop reason.

    icmStopReason getStopReason() { return icmGetStopReason(_proc); }

    /// Nominate this processor to be attached to a debugger

    void debugThisProcessor() { icmDebugThisProcessor(_proc); }

    /// Set an address breakpoint on this processor

    void setAddressBreakpoint(Addr address);

    /// Clear an address breakpoint

    void clearAddressBreakpoint(Addr address);

    /// Set an instruction count breakpoint.
    /// This will replace any existing instruction count breakpoint.
    /// Hitting this will cause the simulator to return.

    void setICountBreakpoint(Uns64 delta);

    /// Clear the instruction count breakpoint, if it exists.

    void clearICountBreakpoint();

    /// Find processor object by name

    static icmProcessorObject *find(const char *name);

    /// Get number of clocks until the simulated time

    Uns64 getProcessorClocksUntilTime (icmTime time) {
        return icmGetProcessorClocksUntilTime(_proc, time);
    }

    /// Get number of clocks until the simulated time (as a double)

    Uns64 getProcessorClocksUntilTime (double time) {
        return icmGetProcessorClocksUntilTimeDouble(_proc, time);
    }

private:

    void newProcessorObject(
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
    );

    icmProcessorP        _proc;
    icmHandleSimStop_if *_simStopHnd;
};

/// The PSE instance object.

class icmPseObject: icmCpuManagerItem
{

public:
    /// Constructor of PSE instance
    /// @param name           Unique instance name.
    /// @param objectFile     Path to PSE object file.
    /// @param initialAttrs   (optional) list of user defined attributes
    /// @param semiHostFile   (optional dll or shared object) path to intercept library for this PSE.
    /// @param semiHostSymbol (must be supplied if path is supplied) name of attribute
    ///                       table in intercept library object.
    /// Note that the intercept library might be part of the basic functionality of the model.

    icmPseObject(
        const char        *name,
        const char        *objectFile,
        icmAttrListObject *initialAttrs   = 0,
        const char        *semiHostFile   = 0,
        const char        *semiHostSymbol = 0
    );

    /// PSE instance destructor.
    ~icmPseObject() {}

    /// Connect a PSE bus port to a bus.
    /// @param  bus       The bus to be connected.
    /// @param  portName  Name of the existing port in the PSE.
    /// @param  isMaster  True if this is master port, false if it's a slave.
    /// @param  lowAddr   Lower extent of the address space used by the port.
    /// @param  highAddr  Upper extent of the address space used by the port.
    void connect(
        icmBusObject &bus,
        const char   *portName,
        bool          isMaster,
        Addr          lowAddr,
        Addr          highAddr
    );

    /// Connect a PSE bus dynamic port. In a dynamic port, the address is set by the model.
    /// e.g. PCI plug and play devices.
    /// @param  bus       The bus to be connected.
    /// @param  portName  Name of the existing port in the PSE.
    /// @param  isMaster  True if this is master port, false if it's a slave.

    void connect(
        icmBusObject &bus,
        const char   *portName,
        bool          isMaster
    );

    /// connect a PSE net port to a net
    /// @param  net       The net to be connected.
    /// @param  portName  Name of the existing net port in the PSE.
    /// @param  direction ICM_INPUT or ICM_OUTPUT.

    void connect(
        icmNetObject &net,
        const char   *portName,
        icmDirection  direction
    );

    /// Add an intercept object (extension library) to this PSE.
    /// This allows extra functionality over the standard PSE model.
    /// @param  instanceName    Unique name of this instance.
    /// @param  interceptFile   Path to the intercept object.
    /// @param  interceptSymbol Name of the attribute table on the intercept object.
    /// @param  userAttrs       (optional) List of user defined attributes used to configure the
    ///                         intercept object.

    void addInterceptObject(
        const char       *instanceName,
        const char       *interceptFile,
        const char       *interceptSymbol,
        icmAttrListObject *userAttrs = 0
    );

    /// Set the path to the PSE gdb.
    /// This is required if multiprocessor debugger is to be used with a PSE.
    /// @param path   Full path to the debugger executable.
    /// @param flags  Any flags required by gdb to debug this processor configuration.

    void setGdbPath(
        const char   *path,
        const char   *flags
    );

    /// Iterator for netPorts
    /// @param current   Handle to netPort or 0 if the first call.
    /// @return          Handle to next netPort or 0 if the last.

    icmNetPortP nextNetPort(icmNetPortP current);

    /// Find a net port by name
    /// @param name    Name of a net port (an interrupt or reset).
    /// @return        Handle to netPort or 0 if no such name.

    icmNetPortP findNetPort(const char *name);

    /// Set PSE diagnostics level
    /// Refer to the PSE to see the effect of each level
    /// Debug level should be interpreted as follows:
    /// 0   no diagnostics.
    /// 1   startup and shutdown messages.
    /// 2   major operations and mode changes.
    /// 3   every register access.
    /// >3  module specific messages.
    /// @param level  The new level.

    void setDiagnosticLevel(Uns32 level) { icmSetPSEdiagnosticLevel(_pse, level); }

    /// Return the processor name
    /// @return name (in a temporary c-string which cannot be relied on).

    const char *getName();

    /// Instead of mapping this port to the given address range, call this function.
    /// @param  portName   Name of the port
    /// @param  cb         function to call when port is being mapped.
    /// @param  userData   data will be passed to the CB function

    void addPortMapCB(const char *portName, icmPsePortMapFn cb, void *userData) {
        icmAddPortMapCB(_pse, portName, cb, userData);
    }

    /// Return the ICM PSE descriptor (for internal use).

    icmPseP getPseP(void) { return _pse; }

private:
    icmPseP _pse;
};

class icmCLPObject
{

public:
    /// Command Line Parser instance
    /// @param clientName    Used for error reporting
    /// @param useMask       Bit mask to select which flags are installed

    icmCLPObject(const char *clientName, icmCLPArgClass select);

    ~icmCLPObject();

    /// Add an argument to be accepted by this parser
    /// The bit mask is used as follows:
    /// If the mask is zero , this flag will always be in the parser.
    /// If the mask is non-zero, the flag will be installed if the corresponding bit is set in the parse constructor.
    /// The flags are allocated as follows:
    ///   bit 0    : reserved for interal use.
    ///   bit 1    : for use in the standard product.
    ///   bits 2-4 : reserved for internal use.
    ///   bits 5-31: for use by external tools.">

    /// @param name           Argument name
    /// @param shortName      Optional short name
    /// @param argDesc        Optional description of the argument value (e.g. filename)
    /// @param group          Optional group (arguments are grouped for clarity)
    /// @param type           Argument type (enumeration)
    ///                       Use CLPA_ macros for function prototypes
    /// @param ptr            Pointer to the function or variable
    /// @param description    Appears with -help
    /// @param useMask        Use Mask. See function description.
    /// @param userData       Passed to function
    /// @param mandatory      if true, this argument must be specified

    void addArg(
        const char    *name,
        const char    *shortName,
        const char    *argDesc,
        const char    *group,
        icmCLPArgType type,
        void          *ptr,
        const char    *description,
        Uns32         useMask       = 0,
        Uns32         userData      = 0,
        Bool          mandatory     = 0
    );

    // Add a default error (help) message
    void usageMessage(const char *message);

    /// Parse a set of arguments passed from main()
    Bool parse(int argc, const char *argv[]);

    /// Parse a file containing arguments
    Bool parse(const char *filename);

    Bool argUsed(const char *argName);

private:
    icmCLPP _parser;
};

}; // namespace icmCpuManager


/*
 * THIS INTERFACE USES THE ICM  API WHICH IS DEPRECATED.
 * PLEASE USE ImpPublic/include/host/op/op.hpp
 */

#endif /*ICMCPUMANAGER_HPP_*/
