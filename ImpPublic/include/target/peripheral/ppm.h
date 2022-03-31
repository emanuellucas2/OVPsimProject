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

/* ppm.h */

#ifndef PPM_PPM_H
#define PPM_PPM_H

#include "peripheral/impTypes.h"

// General behavioral modeling I/F
#include "bhm.h"

//
// PPM functions return a non-zero handle, or zero if they fail.
//
#define PPM_INVALID_HANDLE 0

//
// Min/Max values
//
#define PPM_MAXS32 (0x7FFFFFFF)
#define PPM_MINS32 (-VMI_MAXS32-1)
#define PPM_MAXU32 (-1)
#define PPM_MAXU64 (-1LL)

 #define UNUSED   __attribute__((unused))

///
/// Handle types. Hidden from the application, they are defined as pointers
/// to fictitious structures, to give type safety.
///

/// Handle to an external bus.
typedef struct ppmExternalBusHandleS    *ppmExternalBusHandle;

/// Functional (rather than window) access to external address space
typedef struct ppmAddressSpaceHandleS   *ppmAddressSpaceHandle;

/// Handle to a local bus.
typedef struct ppmLocalBusHandleS       *ppmLocalBusHandle;

/// Handle to a net
typedef struct ppmNetHandleS            *ppmNetHandle;

/// Handle to a packetnet
typedef struct ppmPacketnetHandleS      *ppmPacketnetHandle;

/// Handle to FIFO input port
typedef struct ppmConnInputHandleS      *ppmConnInputHandle;

/// Handle to FIFO output port
typedef struct ppmConnOutputHandleS     *ppmConnOutputHandle;

/// Handle to a dynamic bridge mapping
typedef struct ppmDynamicBridgeS        *ppmDynamicBridge;

/// Handle to a view object
typedef struct ppmViewObjectS           *ppmViewObject;

/// Handle to a view object
typedef struct ppmViewEventS            *ppmViewEvent;

// type carried by a net
typedef Uns64 ppmNetValue;

///
/// Callback prototypes.
///

/// Memory read callbacks. Deprecated. Please use PPM_NBYTE_READ_CB
#define PPM_READ_CB(_name) \
    Uns32(_name)(void *addr, Uns32 bytes, void *user, Bool artifactAccess)

typedef PPM_READ_CB((*ppmCBReadFunc));

/// Memory write callbacks Deprecated. Please use PPM_NBYTE_WRITE_CB
#define PPM_WRITE_CB(_name) \
    void  (_name)(void *addr, Uns32 bytes, void *user, Uns32 data, Bool artifactAccess)

typedef PPM_WRITE_CB((*ppmCBWriteFunc));

/// Register read callbacks. Deprecated. Please use PPM_NBYTE_READ_CB
#define PPM_REG_READ_CB(_name) \
    Uns32(_name)(void *addr, Uns32 bytes, void *user, Bool artifactAccess)

typedef PPM_REG_READ_CB((*ppmCBRegReadFunc));

/// Register write callbacks. Deprecated. Please use PPM_NBYTE_WRITE_CB
#define PPM_REG_WRITE_CB(_name) \
    void  (_name)(void *addr, Uns32 bytes, void *user, Uns32 data, Bool artifactAccess)

typedef PPM_REG_WRITE_CB((*ppmCBRegWriteFunc));

/// Deprecated. Please use PPM_NBYTE_VIEW_CB
#define PPM_VIEW_CB(_name) \
    void (_name)(void *user, void *data)

/// Please use ppmCBRegviewFunc in place of ppmCBviewFunc
typedef PPM_VIEW_CB((*ppmCBviewFunc));

/// Register view callback. Deprecated. Please use PPM_NBYTE_VIEW_CB
#define PPM_REG_VIEW_CB(_name) \
    void (_name)(void *user, void *data)

typedef PPM_REG_VIEW_CB((*ppmCBRegviewFunc));

/// Constructor callback
#define PPM_CONSTRUCTOR_CB(_name) \
    void (_name)(void)

/// Constructor callback
#define PPM_DESTRUCTOR_CB(_name) \
    void (_name)(void)

//
// Memory access privilege (bitmask)
//
typedef enum ppmPrivE {

    // access privilege options
    PPM_PRIV_NONE    = 0x00,    // no access permitted
    PPM_PRIV_R       = 0x01,    // read permitted
    PPM_PRIV_W       = 0x02,    // write permitted
    PPM_PRIV_X       = 0x04,    // execute permitted

    // compound privileges
    PPM_PRIV_RW      = (PPM_PRIV_R|PPM_PRIV_W           ),
    PPM_PRIV_RX      = (PPM_PRIV_R|           PPM_PRIV_X),
    PPM_PRIV_WX      = (           PPM_PRIV_W|PPM_PRIV_X),
    PPM_PRIV_RWX     = (PPM_PRIV_R|PPM_PRIV_W|PPM_PRIV_X),

} ppmPriv;

///
/// Install a callback on a read from this peripheral's mapped region
/// Deprecated. Please use ppmInstallNByteCallbacks
///
/// @param cb     The read Callback function.
/// @param user   User supplied argument, passed back in the callback.
/// @param lo     Low address
/// @param bytes  size of the region
///
void ppmInstallReadCallback(ppmCBReadFunc cb, void *user, void *lo, Uns32 bytes);

///
/// Install a callback on a write to this peripheral's mapped region
/// Deprecated. Please use ppmInstallNByteCallbacks
///
/// @param cb     The write Callback function.
/// @param user   User supplied argument, passed back in the callback.
/// @param lo     Low address
/// @param bytes  size of the region
///
void ppmInstallWriteCallback(ppmCBWriteFunc cb, void *user, void *lo, Uns32 bytes);

///
/// Install a callback on a write to this peripheral's mapped region that changes
/// the written value
///
/// @param cb     The write Callback function.
/// @param user   User supplied argument, passed back in the callback.
/// @param lo     Low address
/// @param bytes  size of the region
///
void ppmInstallChangeCallback(ppmCBWriteFunc cb, void *user, void *lo, Uns32 bytes);


/// Memory wide read callback
#define PPM_NBYTE_READ_CB(_name)  \
    void (_name)(                 \
        Uns32       offset,       \
        void       *data,         \
        Uns32       bytes,        \
        void       *userData,     \
        Bool        artifactAccess)


typedef PPM_NBYTE_READ_CB((*ppmNByteReadFunc));

/// Memory write write callback
#define PPM_NBYTE_WRITE_CB(_name) \
    void (_name)(                 \
        Uns32       offset,       \
        const void *data,         \
        Uns32       bytes,        \
        void       *userData,     \
        Bool        artifactAccess)

typedef PPM_NBYTE_WRITE_CB((*ppmNByteWriteFunc));

///
/// Install callbacks to make a local memory in this peripheral's mapped region
//////
/// @param read       The read   callback function.
/// @param write      The write  callback function.
/// @param userData   User supplied argument, passed back to the callback.
/// @param baseAddr   Low address in peripheral space (in a slave port region)
/// @param offset     The offset from baseAddr
/// @param bytes      Size of the region
/// @param readable   Region is readable
/// @param writable   Region is writable
/// @param isVolatile Will write even if not changed
/// @param endian     Big or little endian (controls byte swapping)
//
void ppmInstallNByteCallbacks(
    ppmNByteReadFunc  read,
    ppmNByteWriteFunc write,
    void             *userData,
    void             *baseAddr,
    Uns32             offset,
    Uns32             bytes,
    Bool              readable,
    Bool              writable,
    Bool              isVolatile,
    bhmEndian         endian
);

///
/// Sets the protection of the given region and removes any callbacks
/// (e.g. the default callbacks on a bus slave port region)
/// @param loAddr     Low address in peripheral space (in a slave port region)
/// @param bytes      Size of the region
/// @param priv       memory protection

void ppmCreateLocalMemory(
    void             *loAddr,
    Uns32             bytes,
    ppmPriv           priv
);

////////////////////////////////////////////////////////////////////////////////
// BUS INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// SimAddr is the type used to define an address in the simulated address space.
typedef Uns64 SimAddr;


////////////////////////////////////////////////////////////////////////////////
// BUS MASTER INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Create a bus bridge into an external bus address space by port name:
/// Reads and writes to the address range
/// localLoAddress:localLoAddress+sizeInBytes will be performed on the remote bus.
/// This interface should be used for devices that need to create a window
/// whose address is determined at run-time, or which needs to be changed on the fly.
/// @param  busPortName       Name of busPort connected to the bus to expose.
/// @param  localLoAddress    Lower extent of region in this address space.
/// @param  sizeInBytes       size in bytes of region in this address space.
/// @param  remoteLoAddress   Lower extent of region in remote address space.
/// @return handle to exposed region (for deletion) or null.

ppmExternalBusHandle ppmOpenMasterBusPort(
    const char     *busPortName,
    volatile void  *localLoAddress,
    Uns64          sizeInBytes,
    SimAddr        remoteLoAddress
);

/// Move the external bus window to view a different region of the remote
/// address space. (e.g. might be used by a plug-n-play device).
/// @param     h                   Handle to existing window.
/// @param     remoteLoAddress     New remote address.
/// @return    success/failure     (if the handle is invalid
///                                or address overlaps another region).

Bool ppmChangeRemoteLoAddress(ppmExternalBusHandle h, SimAddr remoteLoAddress);

// Direct Function access to remote bus by port name.

/// Open a window onto an address space
/// @param busPortName name of the bus master port connected to the bus
/// @return handle to opened address space

ppmAddressSpaceHandle ppmOpenAddressSpace(char *busPortName);

/// perform an atomic bus read operation
/// @param    addressSpace      handle to address space
/// @param    address           offset into the address space (added to port offset)
/// @param    bytes             number of bytes to read
/// @param    data              pointer to data to be filled
/// @return   1=success/0=failure
///
Bool ppmReadAddressSpace(
    ppmAddressSpaceHandle addressSpace,
    Uns64                 address,
    Uns32                 bytes,
    void                  *data
);

/// perform an atomic bus write operation
/// @param    addressSpace      handle to address space
/// @param    address           offset into the address space (added to port offset)
/// @param    bytes             number of bytes to write
/// @param    data              pointer to data to be copied
/// @return   1=success/0=failure
///
Bool ppmWriteAddressSpace(
    ppmAddressSpaceHandle addressSpace,
    Uns64                 address,
    Uns32                 bytes,
    void                  *data
);

/// see if an atomic bus read operation would complete (without doing it)
/// @param    addressSpace      handle to address space
/// @param    address           offset into the address space (added to port offset)
/// @param    bytes             number of bytes to read
/// @return   1=success/0=failure
///
Bool ppmTryReadAddressSpace(
    ppmAddressSpaceHandle addressSpace,
    Uns64                 address,
    Uns32                 bytes
);

/// see if an atomic bus write operation would complete (without doing it)
/// @param    addressSpace      handle to address space
/// @param    address           offset into the address space (added to port offset)
/// @param    bytes             number of bytes to write
/// @return   1=success/0=failure
///
Bool ppmTryWriteAddressSpace(
    ppmAddressSpaceHandle addressSpace,
    Uns64                 address,
    Uns32                 bytes
);

/// return address causing abort of preceding bus operation initiated by
/// ppmReadAddressSpace or ppmWriteAddressSpace, if they returned a failure
/// status code
/// @return   aborting address
///
SimAddr ppmGetAbortAddress(void);

/// close address space
/// @param    addressSpace      handle to address space
/// @return   1=success/0=failure
///
Bool ppmCloseAddressSpace( ppmAddressSpaceHandle addressSpace);


///////////////////////////////////////////////////////////////////////////////
// BUS SLAVE INTERFACE
///////////////////////////////////////////////////////////////////////////////

/// Expose part of the address space of the peripheral to an area of another address
/// space described by a peripheral bus port.
/// @param portName        name of bus port to be used to expose the bus.
/// @param localLoAddress  lower extent of region to be exposed locally.
/// @param sizeInBytes     size of extent to be exposed.
/// @return                Handle to exposed region.

ppmLocalBusHandle ppmOpenSlaveBusPort(const char *portName, void *localLoAddress, Uns64 sizeInBytes);

/// Allocate space in the peripheral and expose it to access by another bus,
/// described by a peripheral bus port.
/// Primarily for use with ppmCreateRegister
/// @param portName        name of bus port to be used to expose the bus.
/// @param sizeInBytes     size of extent to be exposed.
/// @return                Address of the exposed region

void *ppmCreateSlaveBusPort(const char *portName, Uns64 sizeInBytes);

/// Use this macro to expose a variable to be read/written by a device on a remote bus.
#define PPM_EXPOSE_BY_PORT(_portName, _variable)   \
       ppmOpenSlaveBusPort(_portName, _variable, sizeof(_variable))

/// Move the local bus window to expose a different region of the current
/// address space
/// @param  h               Handle of region to move
/// @param  localLoAddress  new address of lower extent of region.
/// @return  success/failure.

Bool ppmChangeLocalLoAddress(ppmLocalBusHandle h, void *localLoAddress);

/// Remove an exposed External memory region.
/// @param h    handle to region to be deleted.

Bool ppmDeleteExternalBusHandle(ppmExternalBusHandle h);


// Remove an exposed Local memory region.
/// @param h    handle to region to be deleted.

Bool ppmDeleteLocalBusHandle(ppmLocalBusHandle h);


/////////////////////////////////////////////////////////////////////////////////////
// DIRECT ACCESS TO BUS (not via a port)
// Provided for testing.
/////////////////////////////////////////////////////////////////////////////////////

/// Create a bus bridge into an external bus address space, by bus name:
/// Reads and writes to the address range localLoAddress:localLoAddress+sizeInBytes
/// will be performed on the remote bus.
/// Most peripherals will use  ppmOpenExternalBusPort.
///This interface might be used for devices that need to create a window
/// whose address is determined at run-time, or which needs to be changed on the fly.
/// @param  remoteBusName     Name of bus to expose.
/// @param  localLoAddress    Lower extent of region in this address space.
/// @param  sizeInBytes       Size in bytes of region in this address space.
/// @param  remoteLoAddress   Lower extent of region in remote address space.
/// @return handle to exposed region (for deletion) or null.

ppmExternalBusHandle ppmAccessExternalBus(
    const char     *remoteBusName,
    volatile void  *localLoAddress,
    Uns64          sizeInBytes,
    SimAddr        remoteLoAddress
);

/// Create a bus bridge that exposes part of the address space of the peripheral
/// to another address space. Only use this for software controlled windows -
/// e.g. plug&play devices.
/// Use ppmOpenSlaveBusPort for fixed address devices - the addresses will then be
/// visible to the simulator.
/// @param   remoteBusName     Name of bus to expose to this address space
/// @param   remoteLoAddress   Lower extent of region on remote bus.
/// @param   sizeInBytes       Size in bytes of region on remote bus.
/// @param   localLoAddress    Lower extent of region on this bus.
/// @return  handle to remote bus region/null.

ppmLocalBusHandle ppmExposeLocalBus(
    const char   *remoteBusName,
    SimAddr      remoteLoAddress,
    Uns64        sizeInBytes,
    void         *localLoAddress
);


////////////////////////////////////////////////////////////////////////////////
/// DYNAMIC BRIDGE INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Create a bridge between two buses connected to two ports of the peripheral.
/// The bridge can be removed at any time.
/// This feature is typically used for a system where address decoding
/// can be switched at run-time (e.g. PCI).

/// @param  slavePort        Name of port connected to bus with masters
/// @param  slaveLoAddress   Lower address on bus with masters
/// @param  sizeInBytes      Size of window
/// @param  masterPort       Name of port connected to bus with slaves
/// @param  masterLoAddress  Lower address on bus with slaves
/// @return  True if OK, False if Failed.

Bool ppmCreateDynamicBridge(
    const char   *slavePort,
    SimAddr      slaveLoAddress,
    Uns64        sizeInBytes,
    const char   *masterPort,
    SimAddr      masterLoAddress
);

/// Delete an existing bridge

/// @param  slavePort        Name of port connected to bus with masters
/// @param  slaveLoAddress   Lower address on bus with masters
/// @param  sizeInBytes      Size of window

void ppmDeleteDynamicBridge(
    const char  *slavePort,
    SimAddr     slaveLoAddress,
    Uns64       sizeInBytes
);

///
/// Create a dynamic window from a peripheral slave port onto the local memory
/// space of the peripheral. This is like ppmExposeLocalBus() but connect by
/// port name, rather than bus name.

/// @param  slavePort        Name of port connected to bus with masters
/// @param  slaveLoAddress   Lower address on bus with masters
/// @param  sizeInBytes      Size of window
/// @param  localLowAddress  Lower address on peripheral bus
/// @return  True if OK, False if Failed.

Bool ppmCreateDynamicSlavePort(
    const char *slavePort,
    SimAddr    slaveLoAddress,
    Uns64      sizeInBytes,
    void       *localLowAddress
);

/// Delete an dynamic slave port

/// @param  slavePort        Name of port connected to bus with masters
/// @param  slaveLoAddress   Lower address on bus with masters
/// @param  sizeInBytes      Size of window

void ppmDeleteDynamicSlavePort(
    const char     *slavePort,
    SimAddr        slaveLoAddress,
    Uns64          sizeInBytes
);


/// In a peripheral callback, signal that the read could not complete and has
/// been aborted

void ppmReadAbort(void);

/// In a peripheral callback, signal that the write could not complete and has
/// been aborted

void ppmWriteAbort(void);


////////////////////////////////////////////////////////////////////////////////
/// NET INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Type of function to be called back when an interrupt is applied.
//      value       New net value
//      userData    Pointer provided during installation

#define PPM_NET_CB(_NAME) void _NAME(ppmNetValue value, void *userData)

typedef PPM_NET_CB((*ppmCBNetFunc));

/// Return handle of an interrupt port in the context of this peripheral.
/// Use this handle to send interrupt assert/deassert events to other devices.
/// @param    portName    Name of the interrupt port.
/// @return               Handle to interrupt port.

ppmNetHandle ppmOpenNetPort(const char *portName);

/// Use this to raise an interrupt on a port, which via a platform net,
/// is propagated to other devices which can accept an interrupt.
/// @param     handle    Handle of net port.
/// @param     value     New value for net signal.

void ppmWriteNet(ppmNetHandle handle, ppmNetValue value);

/// Use this to read the current value of a net port.
/// @param     handle    Handle of interrupt port.

ppmNetValue ppmReadNet(ppmNetHandle handle);

/// Bind a callback to a net port. This replaces any previous callback.
/// @param    handle    Handle of interrupt port.
/// @param    cb        function to be called when port changes state.
/// @param    userData  data passed to callback verbatim.

void ppmInstallNetCallback(ppmNetHandle handle, ppmCBNetFunc cb, void *userData);

/////////////////////////////////////////////////////////////////////////////////////////////////
// PACKET NETWORK SUPPORT
/////////////////////////////////////////////////////////////////////////////////////////////////

/// Packetnet is used to model networks which broadcast packets of data from one of many
/// senders to all receivers. Packetnet is suitable for Ethernet, USB, CAN or GSM networks.
/// Each receiver will be notified by callback when a packet is received; the receiver must
/// use the data or not.
/// Data that is not read in the notifier callback will not persist so will be lost.

/// A call by a sender to ppmPacketnetWrite() will block until all receivers have been
/// notified. For this reason the notifier function must not take time.
/// Network latency, network data rate and network recovery time must be modeled
/// by delays added to the sender's process.

/// The order that receivers are called cannot be determined by the ppm interface, it depends
/// on the order of connections made in the platform.

/// Prototype for packetnet notifier.
/// Called when a packet arrives on the given channel.

#define PPM_PACKETNET_CB(_name) void _name(ppmPacketnetHandle handle, Uns32 bytes, void *data, void *userData)
typedef PPM_PACKETNET_CB((*ppmCBPacketnetFunc));

/// Send a packet of data to the packetnet with the given handle
/// @param  ch     The channel handle
/// @param  data   Pointer to the data to sent
/// @param  bytes  Number of bytes to send
/// @return        How many receivers received the packet

Uns32 ppmPacketnetWrite(ppmPacketnetHandle ch, void *data, Uns32 bytes);

////////////////////////////////////////////////////////////////////////////////
/// USER-VIEWABLE REGISTERS
////////////////////////////////////////////////////////////////////////////////

/// Function to implement register read, write or view

#define REGISTER_CALLBACK(_NAME) \
    void (*_NAME)(void *address, void *user)

typedef REGISTER_CALLBACK(registerCB);

/// Handle for a user-viewable register
typedef struct dummyRegister  *registerHandle;

/// Install a user-viewable memory-mapped register
/// Deprecated. Please use ppmCreateNByteRegister
/// @param    name         register name.
/// @param    description  short description
/// @param    base         base address of the window in the slave port
/// @param    offset       Offset from the base address of the window
/// @param    bytes        width of the register in bytes; also the access size
/// @param    readCB       callback to implement bus-read
/// @param    writeCB      callback to implement bus-write
/// @param    viewCB       callback to implement debug (non-disturbing) read
/// @param    userData     this is passed to the callback functions
/// @param    isVolatile   whether to write the register even if value has not changed

registerHandle ppmCreateRegister(
    const char      *name,
    const char      *description,
    void            *base,
    Uns32           offset,
    Uns32           bytes,
    ppmCBReadFunc   readCB,
    ppmCBWriteFunc  writeCB,
    ppmCBviewFunc   viewCB,
    void            *userData,
    Bool            isVolatile
);

/// Install a user-viewable internal register
/// Deprecated. Please use ppmCreateNByteInternalRegister
/// @param    name         register name.
/// @param    description  short description
/// @param    bytes        width of the register in bytes; also the access size
/// @param    viewCB       callback to implement debug (non-disturbing) read
/// @param    userData     this is passed to the callback functions

registerHandle ppmCreateInternalRegister(
    const char      *name,
    const char      *description,
    Uns32           bytes,
    registerCB      viewCB,
    void            *userData
);

/// Install a bit-field in a user-viewable memory-mapped register
/// @param    reg          the containing register
/// @param    name         field name.
/// @param    description  short description
/// @param    offset       address in the exposed window
/// @param    bits         width of the field in bits
/// @param    read         True if field can be read - otherwise zero
/// @param    write        True if field can be written

void ppmCreateRegisterField(
    registerHandle  reg,
    const char      *name,
    const char      *description,
    Uns32           offset,
    Uns32           bits,
    Bool            read,
    Bool            write
);

////////////////////////////////////////////////////////////////////////////////
/// WIDE REGISTERS
////////////////////////////////////////////////////////////////////////////////

//
// Callback implemented in the peripheral to view the register
// Arguments:
//    offset         :     offset from the base of the bus port
//    data           :     pointer to data - copy value from the register to here
//    userData       :     value passed to installation function
//
// (The number of bytes copied should match the register width)
//
#define PPM_NBYTE_VIEW_CB(_name) \
    void (_name)( \
        Uns32  offset,\
        void  *data,  \
        void  *userData)

typedef PPM_NBYTE_VIEW_CB((*ppmNByteViewFunc));


/// Install a user-viewable memory-mapped register any number of bytes wide
/// This should be used in preference to ppmCreateRegister which is limited to 4 bytes
///
/// @param    name         register name.
/// @param    description  short description
/// @param    base         base address of the windows in the slave port
/// @param    offset       offset from the base address
/// @param    bytes        width of the register in bytes; also the access size
/// @param    readCB       callback to implement bus-read
/// @param    writeCB      callback to implement bus-write
/// @param    viewCB       callback to implement debug (non-disturbing) read
/// @param    data         passed to the callback functions, this is where the data is stored
/// @param    userData     this is passed to the callback functions
/// @param    isVolatile   whether to write the register even if value has not changed
/// @param    readable     (if no read  callback) register is readable
/// @param    writable     (if no write callback) register is writeable
/// @param    endian       simulator will byte-swap reads and writes

registerHandle ppmCreateNByteRegister(
    const char            *name,
    const char            *description,
    void                  *base,
    Uns32                  offset,
    Uns32                  bytes,
    ppmNByteReadFunc       readCB,
    ppmNByteWriteFunc      writeCB,
    ppmNByteViewFunc       viewCB,
    void                  *data,
    void                  *userData,
    Bool                   isVolatile,
    Bool                   readable,
    Bool                   writable,
    bhmEndian              endian
);

/// Install a user-viewable memory-mapped register any number of bytes wide
/// This should be used in preference to ppmCreateInternalRegister which is limited to 4 bytes
///
/// @param    name         register name.
/// @param    description  short description
/// @param    bytes        width of the register in bytes; also the access size
/// @param    viewCB       callback to implement debug read
/// @param    data         passed to the callback functions, this is where the data is stored
/// @param    userData     this is passed to the callback functions

registerHandle ppmCreateNByteInternalRegister(
    const char            *name,
    const char            *description,
    Uns32                  bytes,
    ppmNByteViewFunc       viewCB,
    void                  *data,
    void                  *userData
);

////////////////////////////////////////////////////////////////////////////////
/// DEBUG VIEW INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// View object value type (e.g. returned by view object value function)
/// N.B. Values must match VMI_VVT_xxx enum
typedef enum {
    PPM_VVT_NOSPACE   = -1,  // No value returned. More buffer required.
    PPM_VVT_ERROR     = 0,   // No value returned

    PPM_VVT_BOOL      = 1,   // Primitive types
    PPM_VVT_SCHAR     = 2,
    PPM_VVT_UCHAR     = 3,
    PPM_VVT_INT8      = 4,
    PPM_VVT_UNS8      = 5,
    PPM_VVT_INT16     = 6,
    PPM_VVT_UNS16     = 7,
    PPM_VVT_INT32     = 8,
    PPM_VVT_UNS32     = 9,
    PPM_VVT_INT64     = 10,
    PPM_VVT_UNS64     = 11,
    PPM_VVT_ADDR      = 12,
    PPM_VVT_FLT64     = 13,

    PPM_VVT_STRING    = 14,  // Single line string
    PPM_VVT_MULTILINE = 15,  // Multi line string
} ppmViewValueType;

/// Create a view object.
/// @param  parent         Parent object (NULL for top level, i.e. peripheral instance).
/// @param  name           Object name.
/// @param  description    Optional one line description string.
/// @return                Handle to view object.

ppmViewObject ppmAddViewObject(ppmViewObject parent, const char *name, const char *description);

/// Set constant value for existing view object (value copied at time of call).
/// @param  object         Object for value.
/// @param  type           Type of value.
/// @param  pValue         Pointer to value in memory.

void ppmSetViewObjectConstValue(ppmViewObject object, ppmViewValueType type, void *pValue);

/// Set value pointer for existing view object (pointer dereferenced each time value is viewed).
/// Use this to associate a view object with a C variable in the model such that the variable
/// is automatically read when the view object is evaluated.
/// @param  object         Object for value.
/// @param  type           Type of value.
/// @param  pValue         Pointer to item in persistent memory (must be valid for lifetime of object)

void ppmSetViewObjectRefValue(ppmViewObject object, ppmViewValueType type, void *pValue);

/// Type of function to be called to get the value of a view object.
/// Callback should set bufferSize to the required size in bytes and return PPM_VVT_NOSPACE
/// if the supplied bufferSize is too small.
/// @param    userData    Data passed to callback verbatim.
/// @param    buffer      Memory to receive value (large enough for all primitive types).
/// @param    bufferSize  Size of memory result area
/// @return               Type of value returned (PPM_VVT_ERROR if no value returned).
typedef ppmViewValueType (*ppmCBViewValueFunc)(void *userData, void *buffer, Uns32 *bufferSize);

/// Set value callback for existing view object.
/// @param  object         Object for value.
/// @param  valueCB        Value callback function.
/// @param  userData       Optional data passed back to callback to allow one callback for many objects.

void ppmSetViewObjectValueCallback(ppmViewObject object, ppmCBViewValueFunc valueCB, void *userData);

/// Type of function to be called when an action is invoked on a view object.
/// @param    userData    Data passed to callback verbatim.
typedef void (*ppmCBViewActionFunc)(void *userData);

/// Add an action to a view object.
/// @param  object          Object for action (NULL for top level, i.e. peripheral instance).
/// @param  name            Action name.
/// @param  description     Optional one line description string.
/// @param  actionCB        Action callback.
/// @param  userData        Optional data passed back to action callback.

void ppmAddViewAction(ppmViewObject object, const char *name, const char *description, ppmCBViewActionFunc actionCB, void *userData);

/// Add an event to a view object.
/// @param  object          Object for event (NULL for top level, i.e. peripheral instance).
/// @param  name            Event name.
/// @param  description     Optional one line description string.
/// @return                 Handle to view event.

ppmViewEvent ppmAddViewEvent(ppmViewObject object, const char *name, const char *description);

/// Get the next view event from a view object.
/// @param  object          Object for event (NULL for top level, i.e. peripheral instance).
/// @param  old             The current view event (or NULL if the first is required).
/// @return                 Handle to next view event.

ppmViewEvent ppmNextViewEvent(ppmViewObject object, ppmViewEvent old);

/// Trigger a view event.
/// @param event            Handle to view event.

void ppmTriggerViewEvent(ppmViewEvent event);

/// Delete a view object (including any child objects).
/// @param  object         Object to delete

void ppmDeleteViewObject(ppmViewObject object);


////////////////////////////////////////////////////////////////////////////////
/// DOCUMENTATION  INTERFACE
////////////////////////////////////////////////////////////////////////////////
//
// Call these function from the ppmDocFn callback.
// Calling from main() is not allowed
//

typedef struct ppmDocNodeS *ppmDocNodeP;

/// Create a section
/// @param   node         Parent node or null if root
/// @param   name         Section header name (a few words only)
/// @return               The new node.

ppmDocNodeP  ppmDocAddSection(ppmDocNodeP node, const char *name);


/// Create a text node. The text will appear in the paragraph or section
/// @param   node         Parent node
/// @param   text         Unformatted text content.
/// @return               The new node.

ppmDocNodeP ppmDocAddText(ppmDocNodeP node, const char *text);

/// Create a field group node: This can represent a memory mapped register
/// @param   parent       Parent node
/// @param   name         Field group name
/// @param   width        Number of bits
/// @return               The new node.

ppmDocNodeP ppmDocAddFields(ppmDocNodeP parent, const char *name, Uns32 width);

/// Create a field node: This can represent a bit field in a memory mapped register
/// Field nodes must be not overlap. Gaps are permitted.
/// @param   parent       Parent node (must be a field group)
/// @param   name         Field name
/// @param   offset       Number of bits offset from LSB
/// @param   width        Number of bits
/// @return               The new node.

ppmDocNodeP ppmDocAddField(ppmDocNodeP parent, const char *name, Uns32 offset, Uns32 width);

/// Alternative form of ppmDocAddField, taking LSB and MSB

#define ppmDocAddFieldMSLS(_parent, _name, _msb, _lsb) \
        ppmDocAddField(_parent, _name, _lsb, (_msb)-(_lsb)+1)

/// Create a constant field node: This can represent a constant bit field in a memory mapped register
/// Field nodes must be created LSB first, MSB later. They must not overlap. Gaps are permitted.
/// @param   parent       Parent node (must be a field group)
/// @param   value        Constant value
/// @param   offset       Number of bits offset from LSB
/// @param   width        Number of bits
/// @return               The new node.

ppmDocNodeP ppmDocAddConstField(ppmDocNodeP parent, Uns64 value, Uns32 offset, Uns32 width);

/// Alternative form of ppmDocAddConstField, taking LSB and MSB

#define ppmDocAddConstFieldMSLS(_parent, _value, _msb, _lsb) \
        ppmDocAddConstField(_parent, _value, _lsb, (_msb)-(_lsb)+1)

///////////////////////////////////////////////////////////////////////////////
// PERIPHERAL MODEL ATTRIBUTES
///////////////////////////////////////////////////////////////////////////////

typedef const char          *ppmString;
typedef void                *ppmPtr;
typedef ppmNetHandle        *ppmHandlePtr;
typedef ppmPacketnetHandle  *ppmPacketnetHandlePtr;
typedef ppmConnInputHandle  *ppmConnInputHandlePtr;
typedef ppmConnOutputHandle *ppmConnOutputHandlePtr;

typedef ppmCBNetFunc         ppmNetFunc;          // call this to update a net
typedef ppmCBPacketnetFunc   ppmPacketnetFunc;    // call this to update a packetnet

// pointer to enum parameter structure
typedef struct ppmEnumParameterS *ppmEnumParameterP;

#include "peripheral/ppmAttrTypes.h"

///
/// Prototype for callback for bus port iterator function
///
#define PPM_BUS_PORT_FN(_name) ppmBusPortP _name(ppmBusPortP busPort)
typedef PPM_BUS_PORT_FN((*ppmBusPortSpecFn));

///
/// Prototype for callback for net port iterator function
///
#define PPM_NET_PORT_FN(_name) ppmNetPortP _name(ppmNetPortP netPort)
typedef PPM_NET_PORT_FN((*ppmNetPortSpecFn));

///
/// Prototype for callback for packetnet port iterator function
///
#define PPM_PACKETNET_PORT_FN(_name) ppmPacketnetPortP _name(ppmPacketnetPortP port)
typedef PPM_PACKETNET_PORT_FN((*ppmPacketnetPortSpecFn));

///
/// Prototype for callback for FIFO input port iterator function
///
#define PPM_CONN_INPUT_FN(_name) ppmConnInputPortP _name(ppmConnInputPortP port)
typedef PPM_CONN_INPUT_FN((*ppmConnInputPortSpecFn));

///
/// Prototype for callback for FIFO output port iterator function
///
#define PPM_CONN_OUTPUT_FN(_name) ppmConnOutputPortP _name(ppmConnOutputPortP port)
typedef PPM_CONN_OUTPUT_FN((*ppmConnOutputPortSpecFn));

///
/// Prototype for callback for parameter iterator function
///
#define PPM_PARAMETER_FN(_name) ppmParameterP _name(ppmParameterP parameter)
typedef PPM_PARAMETER_FN((*ppmParameterSpecFn));

///
/// FIFO Interface
///
/// Put value into a connection, if there is space (size of value determined by connection object)
/// @param   handle         Output port handle initialised by the simulator
/// @param   value          Pointer to the word to be sent (size is determined in the ppmConnOutputPort
///                         structure).
/// @return                 True if the data was sent, false if the FIFO was full.
Bool ppmConnPut(ppmConnOutputHandle handle, const void *value);

/// Get value from a connection, if there is an entry present (size of value determined by connection object).
/// @param   handle         Input port handle initialised by the simulator
/// @param   value          Pointer to the word to be filled (size is determined in the ppmConnOutputPort
/// @param   peek'          If True, the data that is read will not be removed from the connection object.
/// @return                 True if the data was read, false if the FIFO was empty.
Bool ppmConnGet(ppmConnInputHandle handle, void *value, Bool peek);

/// Register an event to be notified when space becomes available in the connection object.
/// @param   connHandle     Output port handle initialised by the simulator
/// @param   eventHandle    Event handle that has been allocated using bhmCreateEvent()
/// @return                 True if the binding was successful.
///                         False if not (perhaps connHandle is not connected).
Bool ppmRegisterConnOutputEvent(ppmConnOutputHandle connHandle, bhmEventHandle eventHandle);

/// Register an event to be notified when data becomes available in the connection object.
/// @param   connHandle     Input port handle initialised by the simulator
/// @param   eventHandle    Event handle that has been allocated using bhmCreateEvent()
/// @return                 True if the binding was successful.
///                         False if not (perhaps connHandle is not connected).
Bool ppmRegisterConnInputEvent(ppmConnInputHandle connHandle, bhmEventHandle eventHandle);

///
/// Structure filled to give information about a connection object
///
typedef struct ppmConnInfoS {
    Uns32 words;        /// number of words that the FIFO can hold
    Uns32 bits;         /// width in bits of one word
    Uns32 numFilled;    /// number of words with data in them
    Uns32 numEmpty;     /// number of free words
    Uns32 inputs;       /// number of connected inputs
    Uns32 outputs;      /// number of connected outputs
} ppmConnInfo, *ppmConnInfoP;

/// Fill the 'info' structure with information about the input connection
/// @param   handle         Input port handle initialised by the simulator
/// @param   info           Pointer to the ppmConnInfo structure
void ppmConnGetInputInfo(ppmConnInputHandle handle, ppmConnInfoP info);

/// Fill the 'info' structure with information about the output connection
/// @param   handle         Output port handle initialised by the simulator
/// @param   info           Pointer to the ppmConnInfo structure
void ppmConnGetOutputInfo(ppmConnOutputHandle handle, ppmConnInfoP info);

///
/// Save/restore phase. The save/restore process for each peripheral is as
/// follows:
///
/// 1. the save/restore function is called with phase PPM_PRE_SAVE_RESTORE
/// 2. the peripheral memory state is saved or restored.
/// 3. the save/restore function is called with phase PPM_POST_SAVE_RESTORE
///
/// If a peripheral implements dynamic threads, these are typically deleted
/// when the restore function is called with phase PPM_PRE_SAVE_RESTORE and
/// reinstated when the restore function is called with phase
/// PPM_POST_SAVE_RESTORE to reflect the restored memory state.
///
typedef enum ppmSaveRestorePhaseE {
    PPM_PRE_SAVE_RESTORE,
    PPM_POST_SAVE_RESTORE,
} ppmSaveRestorePhase;

///
/// Prototype for callback for state save function. This is called twice:
/// 1. first call (phase=0), before peripheral memory has been saved;
/// 2. second call (phase=1), after peripheral memory has been saved.
///
#define PPM_SAVE_STATE_FN(_name) void _name(ppmSaveRestorePhase phase)
typedef PPM_SAVE_STATE_FN((*ppmSaveStateFn));

///
/// Prototype for callback for state restore function. This is called twice:
/// 1. first call (phase=0), before peripheral memory has been restored;
/// 2. second call (phase=1), after peripheral memory has been restored.
///
#define PPM_RESTORE_STATE_FN(_name) void _name(ppmSaveRestorePhase phase)
typedef PPM_RESTORE_STATE_FN((*ppmRestoreStateFn));

///
/// Prototype for callback for function to install document nodes
///
#define PPM_DOC_FN(_name) void _name(void)
typedef PPM_DOC_FN((*ppmDocFn));

#include "peripheral/ppmAttrs.h"

#endif

