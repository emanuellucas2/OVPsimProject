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


#ifndef OP_H
#define OP_H

#define OP_VERSION "3.7.1"

#include "op/opTyperefs.h"
#include "op/opTypes.h"

////////////////////////////////////////////////////////////////////////////////
// OP Functions
////////////////////////////////////////////////////////////////////////////////

/// Return the control features that were specified when this application was
/// loaded
/// @return A Bit-mask of the control features
/// @param application The application object returned by
///                    opProcessorApplicationLoad() or other loader functions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00130'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00530'>PlatformConstruction/walker</a>

optLoaderControls opApplicationControls (
    optApplicationP application
);

/// Return the elf code of a loaded application program
/// @return The ELF code, which is a small integer. Refer to 'man (5) elf'
/// @param application The application object returned by
///                    opProcessorApplicationLoad() or other loader functions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00131'>SimulationControl/loadingApplicationPrograms</a>

Uns32 opApplicationElfCode (
    optApplicationP application
);

/// Return the endian of a loaded application program
/// @return The endian as an enumerated type
/// @param application The application object returned by
///                    opProcessorApplicationLoad() or other loader functions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00132'>SimulationControl/loadingApplicationPrograms</a>

optEndian opApplicationEndian (
    optApplicationP application
);

/// Return the entry address of a loaded application program
/// @return The entry point of the program
/// @param application The application object returned by
///                    opProcessorApplicationLoad() or other loader functions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00104'>SimulationControl/loadingApplicationPrograms</a>

Addr opApplicationEntry (
    optApplicationP application
);

/// Read the header of an application file, trying each of the available
/// application readers in turn until one is successful. All simulator products
/// include an ELF format reader, other products include other format readers,
/// such as COFF. Custom loaders can also be installed in the product.
/// @return True if read successfully.
/// @param file The application program file to be read.
/// @param info The pointer to the info structure, filled in by this call.
///             Refer to the ordObjectInfoP structure in
///             ImpPublic/include/host/ord/ordTypes.h
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @sa
/// opApplicationLoaderInstall

Bool opApplicationHeaderRead (
    const char*    file,
    ordObjectInfoP info
);

/// Install a custom loader for application programs. Refer to the Custom Object
/// Reader Guide.
/// @return True if installed successfully.
/// @param file The filename of the custom loader shared object
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// The custom loader must be loaded before an application is loaded. Note that
/// each loader type is tried in turn until one is successful. Custom loaders
/// are tried before the standard loaders, so can replace them.
/// @par Examples:
/// - <a href='./SimulationControl_2customApplicationLoader_2harness_2harness_8c_source.html#l00039'>SimulationControl/customApplicationLoader</a>

Bool opApplicationLoaderInstall (
    const char* file
);

/// Return the address offset that was specified when this application was
/// loaded
/// @return Offset to be added to the load addresses
/// @param application The application object returned by
///                    opProcessorApplicationLoad() or other loader functions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00532'>PlatformConstruction/walker</a>

Addr opApplicationOffset (
    optApplicationP application
);

/// Return the path to a loaded application program
/// @return The cannonical path to the program object file
/// @param application The application object returned by
///                    opProcessorApplicationLoad() or other loader functions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00134'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00528'>PlatformConstruction/walker</a>

const char * opApplicationPath (
    optApplicationP application
);

/// Print the product banner (this function does nothing if --nobanner is
/// specified on the command line)
/// @par Phase:
/// Can be used in any phase

void opBanner (void);

/// Connect a bridge to a bus
/// @return The new connection
/// @param bridge   The bridge instance
/// @param bus      The bus instance
/// @param portName The name of the port
/// @param isMaster True if the connection is a master, false if a slave
/// @param addrLo   The lower address limit
/// @param addrHi   The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opBridgeBusConnect (
    optBridgeP   bridge,
    optBusP      bus,
    const char * portName,
    Bool         isMaster,
    Addr         addrLo,
    Addr         addrHi
);

/// Add an instance of a bridge to a module. A bridge connects two buses. There
/// must be one bus master connection and one bus slave. Use the OP_CONNECTIONS,
/// OP_BUS_CONNECTIONS and OP_BUS_CONNECT macros. The bus slave connection
/// connects to the bus that will initiate transactions, and specifies the range
/// of addresses on the initiator that will pass over the bridge. The bus master
/// connection connects to the target bus and specifies the address range
/// generated on this bus. Note that the number of bytes on each bus must be the
/// same. Note that a bridge does not affect the size or type of transaction.
/// @return The new bridge instance
/// @param module      The parent module instance
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./opBridgeNew_8c_source.html#l00001'>Simple example</a>

optBridgeP opBridgeNew (
    optModuleP      module,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// This function returns the next bridge from a module. To get the first
/// object, bridge should be null.
/// @param module The parent object.
/// @param bridge The iterator. Pass null to get the first object.
/// @return Returns the next bridge, or null when there are no more objects.
/// @par Example:
/// @code
///optBridgeP obj = 0;
///while((obj = opBridgeNext(parent, obj))) {
///    opPrintf("found bridge called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00891'>PlatformConstruction/walker</a>
optBridgeP opBridgeNext (
    optModuleP module,
    optBridgeP bridge
);

/// Set a watchpoint to occur on a bus access. When a watchpoint is triggered,
/// if the notifierCB is specified, it will be called. If it returns True,
/// simulation will continue, otherwise it will stop. If the function is not
/// specified the simulator will stop. The simulator stops by returning to its
/// caller immediately after the access has completed.
/// @return New watchpoint
/// @param bus        The bus instance
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./opBusAccessWatchpointNew_8c_source.html#l00001'>Simple example</a>

optWatchpointP opBusAccessWatchpointNew (
    optBusP                      bus,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Return the number of address bits used on this bus
/// @return The number of bits used to represent an address
/// @param bus The bus instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00547'>PlatformConstruction/walker</a>
/// @sa
/// opBusMaxAddress

Uns32 opBusAddrBits (
    optBusP bus
);

/// Read an application and load it via the specified bus, using the installed
/// readers.
/// @return The new application object
/// @param bus        The bus instance
/// @param path       Application program file
/// @param controls   Bitmask to control the loader behavior.
/// @param loadOffset Add this offset to all load addresses
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00093'>SimulationControl/loadingApplicationPrograms</a>
/// @sa
/// optLoaderControls

optApplicationP opBusApplicationLoad (
    optBusP           bus,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset
);

/// Add a fetch callback to the given address range on a bus. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param bus       The bus instance
/// @param processor Optional pointer limits the callback to only this
///                  processor. If this is null, any processor will cause the
///                  callback
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param wcb       Callback
/// @param userData  The user data to be returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00098'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00136'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00068'>SimulationControl/monitoringMemoryInModule</a>

void opBusFetchMonitorAdd (
    optBusP       bus,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  wcb,
    void*         userData
);

/// Remove a fetch callback from the given address range on a bus if it exists
/// @param bus       The bus instance
/// @param processor Optional pointer limits the callback to only this
///                  processor. If this is null, any processor will cause the
///                  callback
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param wcb       Callback
/// @param userData  The user data to be returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opBusFetchMonitorDelete (
    optBusP       bus,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  wcb,
    void*         userData
);

/// Scan addresses starting from address *addrLoP up to *addrHiP to find the
/// next region of mapped memory. If a region is found, update *addrLoP and
/// *addrHiP with its bounds and return True. If no mapped region is
/// found,return False.
/// @return True if a range was found and lowAddrP /hiAddrP were updated
/// @param bus     The bus instance
/// @param addrLoP Pointer to the initial low address and then to the start
///                of a region if found.
/// @param addrHiP Pointer to the initial high address and then to the end of
///                a region if found.
/// @par Phase:
/// Can be used in any phase

Bool opBusMappedRangeNext (
    optBusP bus,
    Addr*   addrLoP,
    Addr*   addrHiP
);

/// Return the maximum address supported on this bus
/// @return The maximum supported address
/// @param bus The bus instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00093'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00095'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00065'>SimulationControl/monitoringMemoryInModule</a>
/// @sa
/// opBusAddrBits

Addr opBusMaxAddress (
    optBusP bus
);

/// Add an instance of a bus to a module (with an optional external bus port).
/// @return The new bus instance
/// @param module   The parent module instance
/// @param name     The name of the new instance. This string is copied so
///                 need not persist.
/// @param addrBits Number of bits implementing the address bus. This
///                 dictates the maximum address that can be represented.
/// @param portName If specified, this parameter creates a module bus port of
///                 this name so that other modules can connect to this bus.
/// @param params   A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2dynamicBridge_2harness_2harness_8c_source.html#l00091'>SimulationControl/dynamicBridge</a>
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00055'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00027'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00027'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./PlatformConstruction_2busHierarchy_2harness_2harness_8c_source.html#l00069'>PlatformConstruction/busHierarchy</a>

optBusP opBusNew (
    optModuleP  module,
    const char* name,
    Uns32       addrBits,
    const char* portName,
    optParamP   params
);

/// This function returns the next bus from a module. To get the first object,
/// bus should be null.
/// @param module The parent object.
/// @param bus The iterator. Pass null to get the first object.
/// @return Returns the next bus, or null when there are no more objects.
/// @par Example:
/// @code
///optBusP obj = 0;
///while((obj = opBusNext(parent, obj))) {
///    opPrintf("found bus called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00092'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00898'>PlatformConstruction/walker</a>
/// - <a href='./PlatformConstruction_2usingExternalMemory_2module_2module_8c_source.html#l00074'>PlatformConstruction/usingExternalMemory</a>
/// - <a href='./PlatformConstruction_2nativeMemory_2module_2module_8c_source.html#l00051'>PlatformConstruction/nativeMemory</a>
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00121'>SimulationControl/monitoringAccesses</a>
optBusP opBusNext (
    optModuleP module,
    optBusP    bus
);

/// Return the bus port default number of address bits
/// @return Default number of address bits
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00579'>PlatformConstruction/walker</a>

Uns32 opBusPortAddrBitsDefault (
    optBusPortP busPort
);

/// Return the bus port maximum allowed number of address bits
/// @return Number of address bits
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00583'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00311'>SimulationControl/processorQuery</a>

Uns32 opBusPortAddrBitsMax (
    optBusPortP busPort
);

/// Return the bus port minimum allowed number of address bits
/// @return Number of address bits
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00581'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00310'>SimulationControl/processorQuery</a>

Uns32 opBusPortAddrBitsMin (
    optBusPortP busPort
);

/// Return the bus port maximum address (only valid for a slave port)
/// @return Maximum address in this window
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00577'>PlatformConstruction/walker</a>

Addr opBusPortAddrHi (
    optBusPortP busPort
);

/// Return the upper address limit from a bus port connection
/// @return The upper address limit
/// @param busPortConn The bus port connection
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00597'>PlatformConstruction/walker</a>

Addr opBusPortConnAddrHi (
    optBusPortConnP busPortConn
);

/// Return the lower address limit from a bus port connection
/// @return The lower address limit
/// @param busPortConn The bus port connection
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00599'>PlatformConstruction/walker</a>

Addr opBusPortConnAddrLo (
    optBusPortConnP busPortConn
);

/// Return the connected bus
/// @return The bus connected to a bus port connection
/// @param busPortConn The bus port connection
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00603'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00094'>SimulationControl/monitoringAccesses</a>

optBusP opBusPortConnBus (
    optBusPortConnP busPortConn
);

/// Return true if the connected bus port slave decode is dynamic (the address
/// range can change at run-time).
/// @return True if dynamic decode
/// @param list The bus port connection
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00601'>PlatformConstruction/walker</a>

Bool opBusPortConnIsDynamic (
    optBusPortConnP list
);

/// Install a callback to give notification when a port mapping changes. Port
/// mappings are typically changed by a peripheral model, for instance when an
/// address decoder is reconfigured by writing to a register. This feature
/// allows other parts of the platform to be notified.
/// @return Returns true if the function was installed correctly
/// @param busPort  The bus port connection
/// @param cb       The callback function
/// @param userData The user data to be returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./opBusPortConnMapNotify_8c_source.html#l00001'>Simple example</a>

Bool opBusPortConnMapNotify (
    optBusPortConnP busPort,
    optPortMapFn    cb,
    void*           userData
);

/// This function returns the next busPortConn from a bus. To get the first
/// object, busPortConn should be null.
/// @param bus The parent object.
/// @param busPortConn The iterator. Pass null to get the first object.
/// @return Returns the next busPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optBusPortConnP obj = 0;
///while((obj = opBusPortConnNext(parent, obj))) {
///    opPrintf("found busPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00098'>PlatformConstruction/walker</a>
optBusPortConnP opBusPortConnNext (
    optBusP         bus,
    optBusPortConnP busPortConn
);

/// Return the bus port connection type as an enumerated type
/// @return type
/// @param list The bus port connection
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00595'>PlatformConstruction/walker</a>

optBusPortType opBusPortConnType (
    optBusPortConnP list
);

/// Return the bus port connection type as a string
/// @return type as a string
/// @param list The bus port connection
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opBusPortConnTypeString_8c_source.html#l00001'>Simple example</a>

const char * opBusPortConnTypeString (
    optBusPortConnP list
);

/// Return the bus port descriptor
/// @return A description
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00571'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00305'>SimulationControl/processorQuery</a>

const char* opBusPortDescription (
    optBusPortP busPort
);

/// Return the bus port domain type from the descriptor
/// @return The type of domain (code or data)
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00575'>PlatformConstruction/walker</a>

optDomainType opBusPortDomainType (
    optBusPortP busPort
);

/// Return the bus port domain type from the descriptor as a string
/// @return The type of domain
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char* opBusPortDomainTypeString (
    optBusPortP busPort
);

/// Return true if the connected bus port slave decode is dynamic (the address
/// range can change at run-time).
/// @return True if this bus port is dynamic
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00587'>PlatformConstruction/walker</a>

Bool opBusPortIsDynamic (
    optBusPortP busPort
);

/// This function returns the next prev from a busPort. To get the first object,
/// prev should be null.
/// @param busPort The parent object.
/// @param prev The iterator. Pass null to get the first object.
/// @return Returns the next prev, or null when there are no more objects.
/// @par Example:
/// @code
///optMMRegisterP obj = 0;
///while((obj = opBusPortMMRegisterNext(parent, obj))) {
///    opPrintf("found prev called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01003'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2peripheralRegisterAccess_2harness_2harness_8c_source.html#l00050'>SimulationControl/peripheralRegisterAccess</a>
optMMRegisterP opBusPortMMRegisterNext (
    optBusPortP    busPort,
    optMMRegisterP prev
);

/// Return true if this port cannot be left unconnected
/// @return True if this bus port must be connected
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00585'>PlatformConstruction/walker</a>

Bool opBusPortMustConnect (
    optBusPortP busPort
);

/// Return the bus port type from the descriptor
/// @return The type
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00573'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00307'>SimulationControl/processorQuery</a>

optBusPortType opBusPortType (
    optBusPortP busPort
);

/// Return the bus port type from the descriptor as a string
/// @return The type of port
/// @param busPort The bus port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00308'>SimulationControl/processorQuery</a>

const char* opBusPortTypeString (
    optBusPortP busPort
);

/// Set the privilege of the given address region
/// @return True if the setting was successful
/// @param bus    The bus instance
/// @param addrLo The lower address limit
/// @param addrHi The upper address limit
/// @param priv   The read-write-execute access privilege
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

Bool opBusPrivSet (
    optBusP bus,
    Addr    addrLo,
    Addr    addrHi,
    optPriv priv
);

/// Read data from a bus in the context of a processor
/// @return True if success
/// @param bus       The bus instance to read
/// @param processor Optional processor context (can be null)
/// @param address   The bus address
/// @param buffer    Native buffer
/// @param bytes     Number of bytes
/// @param debug     True if this should not perturb the platform state
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2busHierarchy_2harness_2harness_8c_source.html#l00108'>PlatformConstruction/busHierarchy</a>

Bool opBusRead (
    optBusP       bus,
    optProcessorP processor,
    Addr          address,
    void*         buffer,
    Uns32         bytes,
    Bool          debug
);

/// Add a read callback on the given address range of a bus. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param bus       The bus instance
/// @param processor optional processor pointer
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00137'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00069'>SimulationControl/monitoringMemoryInModule</a>

void opBusReadMonitorAdd (
    optBusP       bus,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Remove a read callback from the given address range of a bus if it exists
/// @param bus       The bus instance
/// @param processor optional processor pointer
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Simulation
/// - Pre-simulation

void opBusReadMonitorDelete (
    optBusP       bus,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Set a watchpoint to occur on a bus read. When a watchpoint is triggered, if
/// the notifierCB is specified, it will be called. If it returns True,
/// simulation will continue, otherwise it will stop. If the function is not
/// specified the simulator will stop. The simulator stops by returning to its
/// caller immediately after the access has completed.
/// @return New watchpoint
/// @param bus        The bus instance
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00080'>SimulationControl/interruptSimulation</a>
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00065'>SimulationControl/addingWatchpoints</a>

optWatchpointP opBusReadWatchpointNew (
    optBusP                      bus,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Display a summary of the static connections to a bus
/// @param bus The bus instance to show
/// @par Phase:
/// Can be used in any phase
/// @par Restrictions:
/// Dynamic (run-time) mapping between buses and other models will not be
/// visible. Refer to opModuleDomainDebug to see run-time mappings.
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00128'>SimulationControl/monitoringAccesses</a>

void opBusShow (
    optBusP bus
);

/// Return the upper address limit of a callback
/// @return The bus callback upper address limit
/// @param callback The bus slave instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00564'>PlatformConstruction/walker</a>

Addr opBusSlaveAddrHi (
    optBusSlaveP callback
);

/// Return the lower address limit of a callback
/// @return The bus callback lower address limit
/// @param callback The bus slave instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00562'>PlatformConstruction/walker</a>

Addr opBusSlaveAddrLo (
    optBusSlaveP callback
);

/// Implement an address region as a combination of callbacks or native memory.
/// Read and write operations to the range from addrLo to addrHi will cause the
/// rcb and wcb functions to be called. Arguments rcb or wcb can be set to null,
/// in which case the native memory will be used instead. In this case
/// nativeMemory must be passed a pointer to host memory that was pre-allocated
/// with sufficient size by the user. (When allocating very large memories, be
/// careful not to exhaust the finite resources of your host computer).
/// Additionally, the privilege argument can be used to prevent read or write
/// access to the region. Refer to optPriv. Violation of the specified privilege
/// causes a privilege exception in the initiating device. Use the
/// OP_BUS_SLAVE_READ_FN and OP_BUS_SLAVE_WRITE_FN macros to define the
/// callbacks. If name is supplied, the slave will be a permanent part of the
/// platform; if null, the slave will be temporary and not checked for overlap
/// with other devices on the bus.
/// @return Returns the new bus slave if successful.
/// @param bus          The bus instance
/// @param name         The name of the slave address region
/// @param proc         Optional processor context. If valid, only this
///                     processor will trigger the callback.
/// @param privilege    The read-write-execute access privilege
/// @param addrLo       The lower address limit
/// @param addrHi       The upper address limit
/// @param rcb          The function called to implement bus reads
/// @param wcb          The function called to implement bus writes
/// @param nativeMemory Pointer to native memory
/// @param userData     The user data
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2usingExternalMemory_2module_2module_8c_source.html#l00075'>PlatformConstruction/usingExternalMemory</a>
/// - <a href='./SimulationControl_2dynamicBridge_2harness_2harness_8c_source.html#l00098'>SimulationControl/dynamicBridge</a>
/// - <a href='./PlatformConstruction_2busHierarchy_2harness_2harness_8c_source.html#l00097'>PlatformConstruction/busHierarchy</a>

optBusSlaveP opBusSlaveNew (
    optBusP            bus,
    const char *       name,
    optProcessorP      proc,
    optPriv            privilege,
    Addr               addrLo,
    Addr               addrHi,
    optBusSlaveReadFn  rcb,
    optBusSlaveWriteFn wcb,
    void*              nativeMemory,
    void*              userData
);

/// This function returns the next prev from a bus. To get the first object,
/// prev should be null.
/// @param bus The parent object.
/// @param prev The iterator. Pass null to get the first object.
/// @return Returns the next prev, or null when there are no more objects.
/// @par Example:
/// @code
///optBusSlaveP obj = 0;
///while((obj = opBusSlaveNext(parent, obj))) {
///    opPrintf("found prev called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00905'>PlatformConstruction/walker</a>
optBusSlaveP opBusSlaveNext (
    optBusP      bus,
    optBusSlaveP prev
);

/// Return the access privilege of this bus slave
/// @return The read-write-execute access privilege
/// @param callback The bus slave instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00560'>PlatformConstruction/walker</a>

optPriv opBusSlavePriv (
    optBusSlaveP callback
);

/// Write data to a bus in the context of a processor.
/// @return Returns true if successful
/// @param bus       The bus instance to write
/// @param processor Optional processor context (can be null)
/// @param address   The bus address
/// @param buffer    Native buffer
/// @param bytes     Number of bytes
/// @param debug     True if this should not perturb the platform state
///                  (other than the memory location)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2busHierarchy_2harness_2harness_8c_source.html#l00109'>PlatformConstruction/busHierarchy</a>

Bool opBusWrite (
    optBusP       bus,
    optProcessorP processor,
    Addr          address,
    const void*   buffer,
    Uns32         bytes,
    Bool          debug
);

/// Add a write callback on the given address range on a bus. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param bus       The bus instance
/// @param processor optional processor pointer
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param wcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00138'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00070'>SimulationControl/monitoringMemoryInModule</a>

void opBusWriteMonitorAdd (
    optBusP       bus,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  wcb,
    void*         userData
);

/// Delete a write callback from the given address range on a bus
/// @param bus       The bus instance
/// @param processor optional processor pointer
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param wcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opBusWriteMonitorDelete (
    optBusP       bus,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  wcb,
    void*         userData
);

/// Set a watchpoint on a bus write write. When a watchpoint is triggered, if
/// the notifierCB is specified, it will be called. If it returns True,
/// simulation will continue, otherwise it will stop. If the function is not
/// specified the simulator will stop. The simulator stops by returning to its
/// caller immediately after the access has completed.
/// @return New watchpoint
/// @param bus        The bus instance
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00075'>SimulationControl/interruptSimulation</a>
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00073'>SimulationControl/addingWatchpoints</a>

optWatchpointP opBusWriteWatchpointNew (
    optBusP                      bus,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// A query function to determine if the named argument has been used in this
/// session.
/// @return Returns how many times the argument is specified on the command
///         line or in the control file
/// @param parser The command parser
/// @param name   The name of the flag (without the '-')
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./PlatformConstruction_2ARM_specific_2trustzone_24_8programControl_2platform_2platform_8c_source.html#l00087'>PlatformConstruction/ARM_specific</a>
/// - <a href='./PlatformConstruction_2ARM_specific_2trustzone_22_8alwaysSecure_2platform_2platform_8c_source.html#l00088'>PlatformConstruction/ARM_specific</a>
/// - <a href='./SimulationControl_2addingNewCommandLineArguments_2harness_2harness_8c_source.html#l00048'>SimulationControl/addingNewCommandLineArguments</a>
/// - <a href='./PlatformConstruction_2ARM_specific_2trustzone_21_8ignoreTrustZone_2platform_2platform_8c_source.html#l00087'>PlatformConstruction/ARM_specific</a>
/// - <a href='./PlatformConstruction_2ARM_specific_2trustzone_23_8alwaysNonSecure_2platform_2platform_8c_source.html#l00087'>PlatformConstruction/ARM_specific</a>

Uns32 opCmdArgUsed (
    optCmdParserP parser,
    const char  * name
);

/// Return the application specified on the command line.
/// @return The application specified on the command line
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Notes:
/// This function is for use in Imperas Products. It cannot be used if more than
/// one application is specified.
/// @par Examples:
/// - <a href='./SimulationControl_2addingNewCommandLineArguments_2harness_2harness_8c_source.html#l00068'>SimulationControl/addingNewCommandLineArguments</a>

const char * opCmdDefaultApplication (void);

/// Install a handler to be called when a flag is not recognized.
/// @param parser   The command parser
/// @param handler  The handler to be called when flag is not recognized
/// @param userData The user data passed to error handler
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2addingNewCommandLineArguments_2harness_2harness_8c_source.html#l00044'>SimulationControl/addingNewCommandLineArguments</a>
/// @sa
/// optCmdErrorHandlerFn

void opCmdErrorHandler (
    optCmdParserP        parser,
    optCmdErrorHandlerFn handler,
    void*                userData
);

/// Parse the program arguments using the currently installed flags. This
/// function takes the argc and argv arguments typically passed to main from a
/// Windows or Linux command line. The arguments are parsed using simulator
/// options and user defined options installed using opCmdParserAdd, according
/// to the mask passed to opCmdParserNew
/// @return True if arguments were parsed with no errors (note that some
///         errors cannot be detected until the platform is constructed)
/// @param parser The command parser
/// @param argc   The number of arguments
/// @param argv   A null terminated array of strings, such as those passed to
///               a program main.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00035'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00061'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00053'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00099'>PlatformConstruction/staticBridgeHierarchy</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00044'>SimulationControl/startingApplicationDebug</a>
/// @sa
/// opCmdParserNew

Bool opCmdParseArgs (
    optCmdParserP parser,
    Uns32         argc,
    const char ** argv
);

/// Parse a control file using the currently installed flags. Refer to the
/// control file user guide.
/// @return True if file was parsed with no errors
/// @param parser The command parser
/// @param path   The path to an existing control file.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2readControlFile_2harness_2harness_8c_source.html#l00030'>SimulationControl/readControlFile</a>

Bool opCmdParseFile (
    optCmdParserP parser,
    const char *  path
);

/// Single function to create a standard parser and parse an argument list in
/// one operation. Use this to allow the passing of options to the simulator if
/// no custom arguments are required. It does not return if errors are detected.
/// @param client  The name of the client (usually the program, argv[0])
/// @param useMask Bit fields to choose which flag classes are included. Use
///                the macros beginning OP_AC_
/// @param argc    The number of arguments to parse
/// @param argv    Array of strings such as passed to main.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00091'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2moduleParametersWithHarness_2harness_2harness_8c_source.html#l00033'>SimulationControl/moduleParametersWithHarness</a>
/// - <a href='./HelloWorld_2usingHarnessInC_2harness_2harness_8c_source.html#l00027'>HelloWorld/usingHarnessInC</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2harness_2harness_8c_source.html#l00026'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./SimulationControl_2minimalHarness_2harness_2harness_8c_source.html#l00027'>SimulationControl/minimalHarness</a>

void opCmdParseStd (
    const char*   client,
    optArgClass   useMask,
    Uns32         argc,
    const char ** argv
);

/// Add an option to the parser. The parser will then be able to parse the
/// option and its following argument and take the action specified. Actions are
/// to either update a variable of the correct type, pointed to by the pointer
/// argument, or to call a function of correct type, pointed to by the pointer
/// argument.
/// @param parser      The parser instance
/// @param name        The new flag name
/// @param shortName   Optional single character alternative name
/// @param argDesc     Optional description of the value that must follow
///                    this argument
/// @param group       Optional group. All options with the same group will
///                    appear together when -help is specified.
/// @param type        Argument type (see the FlagType enumerated type)
/// @param pointer     Pointer to either a callback function, or to the data
///                    item to be modified
/// @param description This is printed when -help is specified
/// @param useMask     A bit-mask to control if this flag is visible under
///                    -help. The mask corresponds to the ArgClass passed to
///                    opCmdParserNew.
/// @param userData    The user data to be passed to a callback function
/// @param mandatory   If true, this argument must be specified
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Adding an argument name or a short name that already exists will cause a
/// fatal error. The argument type and the type of object pointed to by the
/// pointer argument must agree, otherwise the program will produce a
/// segmentation violation.
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00033'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00050'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00040'>SimulationControl/recordReplay</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00042'>SimulationControl/startingApplicationDebug</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00057'>PlatformConstruction/walker</a>
/// @sa
/// opCmdParserNew
/// opCmdParserReplace

void opCmdParserAdd (
    optCmdParserP parser,
    const char*   name,
    const char*   shortName,
    const char*   argDesc,
    const char*   group,
    optFlagType   type,
    void*         pointer,
    const char*   description,
    optArgClass   useMask,
    Uns32         userData,
    Bool          mandatory
);

/// Delete a parser after use and free its resources.
/// @param parser The command parser to be deleted
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opCmdParserDelete (
    optCmdParserP parser
);

/// Create the command parser, ready to parse a control file or the program
/// command line arguments.
/// @return The new parser instance
/// @param client  The name of the client (usually the program, argv[0])
/// @param useMask Bit-mask controlling which flags are visible. Note that
///                -helpall will display all flags.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00032'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00049'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00051'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00097'>PlatformConstruction/staticBridgeHierarchy</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00041'>SimulationControl/startingApplicationDebug</a>

optCmdParserP opCmdParserNew (
    const char* client,
    optArgClass useMask
);

/// Replace an existing option in the parser. This command is similar to
/// opCmdParserAdd, but replaces an existing argument. Use this function with
/// care; replacing an option might have unintended consequences.
/// @param parser      The parser instance
/// @param name        The new flag name
/// @param shortName   Optional single character alternative name
/// @param argDesc     Optional description of the value that must follow
///                    this argument
/// @param group       Optional group. All options with the same group will
///                    appear together when -help is specified.
/// @param type        Argument type (see the FlagType enumerated type)
/// @param pointer     Pointer to either a callback function, or to the data
///                    item to be modified
/// @param description This is printed when -help is specified
/// @param useMask     A bit-mask to control if this flag is visible under
///                    -help. The mask corresponds to the ArgClass passed to
///                    opCmdParserNew.
/// @param userData    The user data to be passed to a callback function
/// @param mandatory   If true, this argument must be specified
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Replacing a vital argument will make the product unusable. The argument type
/// and the type of object pointed to by the pointer argument must agree,
/// otherwise the program will produce a segmentation violation.
/// @sa
/// opCmdParserAdd

void opCmdParserReplace (
    optCmdParserP parser,
    const char*   name,
    const char*   shortName,
    const char*   argDesc,
    const char*   group,
    optFlagType   type,
    void*         pointer,
    const char*   description,
    optArgClass   useMask,
    Uns32         userData,
    Bool          mandatory
);

/// Print this message if command line errors are found or if the -help argument
/// is parsed
/// @param parser  The command parser
/// @param message The help message. Note that the sequence (percent)E will
///                be replaced by the program name
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2dynamicHarness_2harness_2harness_8c_source.html#l00097'>SimulationControl/dynamicHarness</a>

void opCmdUsageMessage (
    optCmdParserP parser,
    const char *  message
);

/// Return a description of a model command argument
/// @return Command argument description
/// @param arg Model command argument
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00506'>PlatformConstruction/walker</a>

const char * opCommandArgDescription (
    optCommandArgP arg
);

/// Call the given callback for each argument accepted by the given command
/// @param command  Model command
/// @param cb       Command argument callback
/// @param userData User data passed to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00514'>PlatformConstruction/walker</a>

void opCommandArgIterAll (
    optCommandP     command,
    optCommandArgFn cb,
    void*           userData
);

/// Return the name of a model command argument
/// @return Command argument name
/// @param arg Model command argument
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00502'>PlatformConstruction/walker</a>

const char * opCommandArgName (
    optCommandArgP arg
);

/// Return the type of a model command argument
/// @return Command argument type (these are the same as parameter types)
/// @param arg Model command argument
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optParamType opCommandArgType (
    optCommandArgP arg
);

/// Return the argument type from the descriptor as a string
/// @return The type
/// @param arg Model command argument
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00504'>PlatformConstruction/walker</a>

const char* opCommandArgTypeString (
    optCommandArgP arg
);

/// Call the given model command with the arguments provided in the argc, argv
/// list.
/// @return The string returned by the command
/// @param command The command instance
/// @param argc    Number of arguments
/// @param argv    Array of pointers to string arguments
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2callingInstalledCommands_2harness_2harness_8c_source.html#l00077'>SimulationControl/callingInstalledCommands</a>

const char * opCommandCall (
    optCommandP   command,
    Uns32         argc,
    const char ** argv
);

/// For internal use only. It is preferable to use opObjectByName() to find the
/// command, then use opCommandCall() to call the command.
/// @return The string returned by the command
/// @param root     The root module
/// @param instance The name of the model instance
/// @param plugin   If the command applies to a plugin, then this is it's
///                 instance name, otherwise null
/// @param command  The name of the command
/// @param argc     The number of items in the argv array, including the
///                 command name
/// @param argv     An array of strings comprising the command name in
///                 position zero, followed by one command argument in each
///                 following position.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opCommandCallByName (
    optModuleP    root,
    const char *  instance,
    const char *  plugin,
    const char *  command,
    Uns32         argc,
    const char ** argv
);

/// Return the help string associated with a command
/// @return Help string from the command
/// @param command The command (which can be obtained using opObjectByName)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opCommandHelp (
    optCommandP command
);

/// Call the given callback on all commands on all models in this module
/// @param module   The module instance
/// @param cb       Command callback
/// @param userData The user data passed to callback
/// @param New      Only newly created commands
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opCommandIterAll_8c_source.html#l00001'>Simple example</a>

void opCommandIterAll (
    optModuleP   module,
    optCommandFn cb,
    void*        userData,
    Bool         New
);

/// Call a command by name relative to a place in the module hierarchy
/// @return String returned by the command, or null if the command failed. If
///         the command is specified with wildcards (globbing) the return
///         value is from the first matching command, so is not normally of
///         any use.
/// @param root    The command must be named relative to this place in the
///                hierarchy
/// @param command Hierarchical name of the command, including globbing, if
///                required
/// @param argc    Number of members in argv
/// @param argv    List of arguments, beginning with the bare command name
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2callingInstalledCommands_2harness_2harness_8c_source.html#l00059'>SimulationControl/callingInstalledCommands</a>

const char * opCommandStringCall (
    optModuleP    root,
    const char *  command,
    Uns32         argc,
    const char ** argv
);

/// Return the next child of the given document node
/// @return The next document node or null if there are no more
/// @param parent The current parent document node
/// @param child  The current document child node or null to begin
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00480'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00468'>SimulationControl/processorQuery</a>

optDocNodeP opDocChildNext (
    optDocNodeP parent,
    optDocNodeP child
);

/// Get the field offset from a node that has one (returns zero if it does not).
/// @return Field offset.
/// @param node Document node.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00475'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00464'>SimulationControl/processorQuery</a>
/// @sa
/// opDocNodeType

Uns32 opDocFieldOffset (
    optDocNodeP node
);

/// Get the field width from a node that has one (returns zero if it does not).
/// @return Field width.
/// @param node Document node.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00472'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00461'>SimulationControl/processorQuery</a>
/// @sa
/// opDocNodeType

Uns32 opDocFieldWidth (
    optDocNodeP node
);

/// Deprecated. Use opDocNodeType.
/// @return True if this is a title, False otherwise.
/// @param node Document node.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opDocIsTitle (
    optDocNodeP node
);

/// Return the type of documentation node
/// @return Enumeration type of node
/// @param node Document node.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00460'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00451'>SimulationControl/processorQuery</a>
/// @sa
/// opDocText
/// opDocFieldOffset
/// opDocFieldWidth

optDocNodeType opDocNodeType (
    optDocNodeP node
);

/// Create a documentation node representing a section heading. A module can
/// create its own documentation using opDocSectionAdd and opDocTextAdd, so that
/// it can be used in other designs without publishing its source. Use
/// opDocSectionAdd to create a root node, then use opDocSectionAdd to create a
/// section heading and opDocTextAdd to create paragraphs following the heading.
/// Use opDocSectionAdd to create sub-section headings.
/// @return The new documentation node
/// @param parent The parent node
/// @param name   The section name
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./opDocSectionAdd_8c_source.html#l00001'>Simple example</a>

optDocNodeP opDocSectionAdd (
    optDocNodeP parent,
    const char* name
);

/// Get title or content text from this node (use opDocNodeType to find which it
/// is).
/// @return Pointer to text.
/// @param node Document node.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00466'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00455'>SimulationControl/processorQuery</a>
/// @sa
/// opDocNodeType

const char * opDocText (
    optDocNodeP node
);

/// Create a documentation node representing a section body
/// @return The new documentation node
/// @param parent The parent node
/// @param text   The document text
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optDocNodeP opDocTextAdd (
    optDocNodeP parent,
    const char* text
);

/// Create dynamic bridge between two buses.
/// @return True if the bridge was created.
/// @param slave        The initiating bus instance
/// @param master       The responding bus instance
/// @param addrLoSlave  The lowest address of the decoded region on the
///                     initiating bus
/// @param addrHiSlave  The highest address of the decoded region on the
///                     initiating bus
/// @param addrLoMaster The lowest address of the region where accesses are
///                     initiated on the responding bus
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2dynamicBridge_2harness_2harness_8c_source.html#l00126'>SimulationControl/dynamicBridge</a>

Bool opDynamicBridge (
    optBusP slave,
    optBusP master,
    Addr    addrLoSlave,
    Addr    addrHiSlave,
    Addr    addrLoMaster
);

/// Remove dynamic bridge between two buses.
/// @return True if the bridge was removed
/// @param slave        The initiating bus instance
/// @param addrLoMaster The lowest address on the initiating bus.
/// @param addrHiMaster The highest address on the initiating bus.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2dynamicBridge_2harness_2harness_8c_source.html#l00144'>SimulationControl/dynamicBridge</a>
/// @sa
/// opDynamicBridge

Bool opDynamicUnbridge (
    optBusP slave,
    Addr    addrLoMaster,
    Addr    addrHiMaster
);

/// Return how many messages with Error status have been printed so far in this
/// session
/// @return Number of errors so far in this session
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00062'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00180'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00153'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00076'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00105'>PlatformConstruction/staticBridgeHierarchy</a>
/// @sa
/// opResetErrors

Uns32 opErrors (void);

/// Return the time of the next scheduled event. Note that a new event could be
/// scheduled during this period
/// @return The absolute time of the next scheduled event.
/// @param root The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optTime opEventTimeNext (
    optModuleP root
);

/// Return the model-specific exception code
/// @return Exception code
/// @param exception The exception descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00383'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00196'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00181'>DebuggerIntegration/modeAndException</a>

Uns32 opExceptionCode (
    optExceptionP exception
);

/// Return a description of the exception
/// @return Exception description
/// @param exception The exception descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00385'>PlatformConstruction/walker</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00183'>DebuggerIntegration/modeAndException</a>

const char* opExceptionDescription (
    optExceptionP exception
);

/// Return the name of the exception from the descriptor
/// @return Exception name (note that this string does not persist)
/// @param exception The exception descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00381'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00195'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00182'>DebuggerIntegration/modeAndException</a>

const char* opExceptionName (
    optExceptionP exception
);

/// Return the extension library that this elaborated extension is derived from
/// @return The originating extension
/// @param ext The elaborated extension library
/// @par Phase:
/// Can be used in any phase

optExtensionP opExtElabExtension (
    optExtElabP ext
);

/// Add an instance of an extension to a module (this feature is not yet
/// supported)
/// @return The new extension instance
/// @param module The parent module instance
/// @param path   Path to an extension library
/// @param name   The name of the new instance. This string is copied so need
///               not persist.
/// @param params A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optExtensionP opExtensionNew (
    optModuleP  module,
    const char* path,
    const char* name,
    optParamP   params
);

/// Return the path to file implementing this extension
/// @return Cannonical path to extension object
/// @param extension The module instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00612'>PlatformConstruction/walker</a>

const char * opExtensionPath (
    optExtensionP extension
);

/// Return the depth of a FIFO (in words)
/// @return The name
/// @param fifo The FIFO instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00628'>PlatformConstruction/walker</a>

Uns32 opFIFODepth (
    optFIFOP fifo
);

/// Add an instance of a FIFO to a module (with an optional external FIFO port)
/// @return The new FIFO instance
/// @param module   The parent module instance
/// @param name     The name of the new instance. This string is copied so
///                 need not persist.
/// @param depth    The maximum number of words that can be stored in the
///                 FIFO.
/// @param portName If specified, create an module external FIFO port for
///                 this FIFO.
/// @param params   A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./opFIFONew_8c_source.html#l00001'>Simple example</a>

optFIFOP opFIFONew (
    optModuleP  module,
    const char* name,
    Uns32       depth,
    const char* portName,
    optParamP   params
);

/// This function returns the next fifo from a module. To get the first object,
/// fifo should be null.
/// @param module The parent object.
/// @param fifo The iterator. Pass null to get the first object.
/// @return Returns the next fifo, or null when there are no more objects.
/// @par Example:
/// @code
///optFIFOP obj = 0;
///while((obj = opFIFONext(parent, obj))) {
///    opPrintf("found fifo called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00947'>PlatformConstruction/walker</a>
optFIFOP opFIFONext (
    optModuleP module,
    optFIFOP   fifo
);

/// Return the connected FIFO
/// @return The FIFO connected to this port connection
/// @param fifoPortConn The current port connection
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00651'>PlatformConstruction/walker</a>

optFIFOP opFIFOPortConnFIFO (
    optFIFOPortConnP fifoPortConn
);

/// This function returns the next fifoPortConn from a fifo. To get the first
/// object, fifoPortConn should be null.
/// @param fifo The parent object.
/// @param fifoPortConn The iterator. Pass null to get the first object.
/// @return Returns the next fifoPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optFIFOPortConnP obj = 0;
///while((obj = opFIFOPortConnNext(parent, obj))) {
///    opPrintf("found fifoPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00108'>PlatformConstruction/walker</a>
optFIFOPortConnP opFIFOPortConnNext (
    optFIFOP         fifo,
    optFIFOPortConnP fifoPortConn
);

/// Return the width of the FIFO port connection in bits
/// @return The width of one word in bits
/// @param fifoPortConn Current FIFO port connection
/// @par Phase:
/// Can be used in any phase

Uns32 opFIFOPortConnWidth (
    optFIFOPortConnP fifoPortConn
);

/// Return the FIFO ports description
/// @return Description of the FIFO port
/// @param fifoPort The FIFO port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00638'>PlatformConstruction/walker</a>

const char* opFIFOPortDescription (
    optFIFOPortP fifoPort
);

/// Return true if this FIFO port cannot be left unconnected
/// @return True if this FIFO port must be connected
/// @param fifoPort The FIFO port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00644'>PlatformConstruction/walker</a>

Bool opFIFOPortMustConnect (
    optFIFOPortP fifoPort
);

/// Return the FIFO port type (OP_FIFO_INPUT or OP_FIFO_INPUT) from the given
/// descriptor
/// @return The FIFO port type (OP_FIFO_INPUT or OP_FIFO_INPUT)
/// @param fifoPort The FIFO port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00642'>PlatformConstruction/walker</a>

optFIFOPortType opFIFOPortType (
    optFIFOPortP fifoPort
);

/// Return the FIFO port type (input or output) from the descriptor
/// @return The FIFO port type (direction of use) as a string
/// @param fifoPort The FIFO port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char* opFIFOPortTypeString (
    optFIFOPortP fifoPort
);

/// Return the width (in bits) of each item of data sent through this port
/// @return The FIFO port width, in bits
/// @param fifoPort The FIFO port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00640'>PlatformConstruction/walker</a>

Uns32 opFIFOPortWidth (
    optFIFOPortP fifoPort
);

/// Print connection information about this FIFO
/// @param fifo The FIFO instance
/// @par Phase:
/// Can be used in any phase

void opFIFOShow (
    optFIFOP fifo
);

/// Restore the state of the given FIFO by calling the callback one or more
/// times. The callback must return the data in the same size chunks as it was
/// saved. The userData passed to the callback should be used to refer to the
/// state of the storage mechanism.
/// @return Success or failure.
/// @param FIFO     The FIFO to restore
/// @param cb       The function used to restore data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opFIFOStateRestore (
    optFIFOP     FIFO,
    optRestoreFn cb,
    void *       userData
);

/// Restore the state of the given FIFO from the given file.
/// @return Success or failure.
/// @param FIFO The FIFO to restore
/// @param file Restore the FIFO contents from this file. The function will
///             return with an error if the file does not exist.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opFIFOStateRestoreFile (
    optFIFOP     FIFO,
    const char * file
);

/// Save the state of the given FIFO by calling the callback one or more times.
/// The callback decides how the data is stored. The userData passed to the
/// callback should be used to refer to the state of the storage mechanism.
/// @return Success or failure.
/// @param FIFO     The FIFO to save
/// @param cb       The function used to save data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opFIFOStateSave (
    optFIFOP  FIFO,
    optSaveFn cb,
    void *    userData
);

/// Save the state of the given FIFO to a file
/// @return Success or failure.
/// @param FIFO The FIFO to save
/// @param file The file to hold the contents. The file will be overwritten
///             if it already exists.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opFIFOStateSaveFile (
    optFIFOP     FIFO,
    const char * file
);

/// For internal use only
/// @return The new root module instance
/// @param path     Path to module shared object, usually calculated by
///                 opVLNVString()
/// @param name     Instance name
/// @param params   A list of parameters to configure the simulator
/// @param userData Client specific data
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optModuleP opFixedModuleNew (
    const char * path,
    const char * name,
    optParamP    params,
    void*        userData
);

/// Return the boolean formal default value
/// @return The default boolean value
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00232'>PlatformConstruction/walker</a>

Bool opFormalBoolDefaultValue (
    optFormalP formal
);

/// Return the formal parameter description from the descriptor
/// @return A description
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00223'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00283'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectName
/// opFormalType
/// opFormalTypeString
/// opFormalEnumNext

const char* opFormalDescription (
    optFormalP formal
);

/// Return the enumerated type formal default value
/// @return The default enumerated type
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optFormalEnumP opFormalEnumDefault (
    optFormalP formal
);

/// Return the description of a formal parameter enumeration
/// @return The enumeration description
/// @param enumval The current enumeration
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00667'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00262'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectName
/// opFormalType
/// opFormalTypeString
/// opFormalDescription

const char* opFormalEnumDescription (
    optFormalEnumP enumval
);

/// This function returns the next enumval from a paramInfo. To get the first
/// object, enumval should be null.
/// @param paramInfo The parent object.
/// @param enumval The iterator. Pass null to get the first object.
/// @return Returns the next enumval, or null when there are no more objects.
/// @par Example:
/// @code
///optFormalEnumP obj = 0;
///while((obj = opFormalEnumNext(parent, obj))) {
///    opPrintf("found enumval called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00982'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00260'>SimulationControl/processorQuery</a>
optFormalEnumP opFormalEnumNext (
    optFormalP     paramInfo,
    optFormalEnumP enumval
);

/// Return the integer value of a formal parameter enumeration
/// @return The enumeration integer value value
/// @param enumval The current enumeration
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00669'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00263'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectName
/// opFormalType
/// opFormalTypeString
/// opFormalDescription

Uns32 opFormalEnumValue (
    optFormalEnumP enumval
);

/// Return the formal group from the formal parameter, or null if the formal is
/// not in a group
/// @return The format parameter group if it exists
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optFormalGroupP opFormalGroup (
    optFormalP formal
);

/// Return the optional description of a formal parameter group
/// @return The group description, or null
/// @param formal The formal parameter group
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00660'>PlatformConstruction/walker</a>

const char * opFormalGroupDescription (
    optFormalGroupP formal
);

/// Return the name of a formal parameter group
/// @return The group name
/// @param formal The formal parameter group
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opFormalGroupName (
    optFormalGroupP formal
);

/// Return the Int32 formal parameter limits
/// @return True if it was possible to retrieve the limits
/// @param formal The formal parameter
/// @param min    Pointer to the minimum value
/// @param max    Pointer to the maximum value
/// @param dflt   Pointer to the default value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00238'>PlatformConstruction/walker</a>

Bool opFormalInt32Limits (
    optFormalP formal,
    Int32*     min,
    Int32*     max,
    Int32*     dflt
);

/// Return the Int64 formal parameter limits
/// @return True if it was possible to retrieve the limits
/// @param formal The formal parameter
/// @param min    Pointer to the minimum value
/// @param max    Pointer to the maximum value
/// @param dflt   Pointer to the default value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00249'>PlatformConstruction/walker</a>

Bool opFormalInt64Limits (
    optFormalP formal,
    Int64*     min,
    Int64*     max,
    Int64*     dflt
);

/// Return the string formal default value
/// @return The default string value or null if there is no default
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00295'>PlatformConstruction/walker</a>

const char * opFormalStringDefaultValue (
    optFormalP formal
);

/// Return the string formal maximum length
/// @return The maximum string length allowed in this parameter
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00295'>PlatformConstruction/walker</a>

Uns32 opFormalStringMaxLength (
    optFormalP formal
);

/// Return true of this is a system parameter (rather than model specific)
/// @return True if a system parameter
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00217'>PlatformConstruction/walker</a>

Bool opFormalSystem (
    optFormalP formal
);

/// Return the formal parameter type from the descriptor
/// @return The type
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00225'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00280'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectName
/// opFormalTypeString
/// opFormalDescription
/// opFormalEnumNext

optParamType opFormalType (
    optFormalP formal
);

/// Return the formal parameter type from the descriptor as a string
/// @return The type
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00221'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00281'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectName
/// opFormalType
/// opFormalDescription
/// opFormalEnumNext

const char* opFormalTypeString (
    optFormalP formal
);

/// Return the Uns32 formal parameter limits
/// @return True if it was possible to retrieve the limits
/// @param formal The formal parameter
/// @param min    Pointer to the minimum value
/// @param max    Pointer to the maximum value
/// @param dflt   Pointer to the default value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00260'>PlatformConstruction/walker</a>

Bool opFormalUns32Limits (
    optFormalP formal,
    Uns32*     min,
    Uns32*     max,
    Uns32*     dflt
);

/// Return the Uns64 formal parameter limits
/// @return True if it was possible to retrieve the limits
/// @param formal The formal parameter
/// @param min    Pointer to the minimum value
/// @param max    Pointer to the maximum value
/// @param dflt   Pointer to the default value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00272'>PlatformConstruction/walker</a>

Bool opFormalUns64Limits (
    optFormalP formal,
    Uns64*     min,
    Uns64*     max,
    Uns64*     dflt
);

/// Return the origin of the value of this formal
/// @return The origin of the value
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optParameterValueOrigin opFormalValueOrigin (
    optFormalP formal
);

/// Return the origin of the value of this formal as a string
/// @return The origin of the value
/// @param formal The formal parameter
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opFormalValueOriginString (
    optFormalP formal
);

/// Return the double formal parameter limits
/// @return True if it was possible to retrieve the limits
/// @param formal The formal parameter
/// @param min    Pointer to the minimum value
/// @param max    Pointer to the maximum value
/// @param dflt   Pointer to the default value
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00284'>PlatformConstruction/walker</a>

Bool opFormaldoubleLimits (
    optFormalP formal,
    double*    min,
    double*    max,
    double*    dflt
);

/// This and opInterruptRSP are the only OP functions that are safe to call in a
/// signal handler. This function causes any currently-executing simulation
/// thread to stop as soon as possible in a safe state so that other ICM
/// functions can be called. The stop is signalled by a return code stop reason
/// of OP_SR_INTERRUPT. The thread stops just before the next code block is
/// executed; typically, this will be a few instructions on from the
/// icmInterrupt call. It is safe to use opInterrupt in non-signal-handler
/// contexts (e.g. memory callbacks) but you may want to consider the use of
/// opProcessorYield in this context.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// Do not call this function from another host thread unless the simulator
/// thread has been stopped.
/// @par Examples:
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00040'>SimulationControl/interruptSimulation</a>
/// - <a href='./SimulationControl_2interruptSimulation_2harness_2harness_8c_source.html#l00050'>SimulationControl/interruptSimulation</a>

void opInterrupt (void);

/// This and opInterrupt are the only OP functions that are safe to call in a
/// signal handler. This function causes simulation to stop and return control
/// to a debugger connected through RSP. If no debugger is attached, simulation
/// continues.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// Do not call this function from another host thread unless the simulator
/// thread has been stopped.

void opInterruptRSP (void);

/// Returns the last message to be printed
/// @return String or empty string
/// @par Phase:
/// Can be used in any phase

const char* opLastMessage (void);

/// Deprecated
/// @param personality Personality string
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opLicPersonalitySet (
    const char* personality
);

/// Connect an MMC to a bus
/// @return The new connection
/// @param mmc      MMC
/// @param bus      The bus instance
/// @param portName The name of the port on the MMC
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opMMCBusConnect (
    optMMCP      mmc,
    optBusP      bus,
    const char * portName
);

/// Load an MMC shared object and create an MMC instance. An MMC model can model
/// a cache or similar bus-oriented device. Refer to the OVP VMI Memory Model
/// Component Function Reference. An MMC must be connected to two or more buses.
/// An MMC is a target on the bus connected to its slave port and is an
/// initiator on the bus connected to its master port.
/// @return The new MMC instance
/// @param module      The parent module instance
/// @param path        Path to MMC model (refer to opVLNVString())
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./opMMCNew_8c_source.html#l00001'>Simple example</a>

optMMCP opMMCNew (
    optModuleP      module,
    const char*     path,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// This function returns the next mmc from a module. To get the first object,
/// mmc should be null.
/// @param module The parent object.
/// @param mmc The iterator. Pass null to get the first object.
/// @return Returns the next mmc, or null when there are no more objects.
/// @par Example:
/// @code
///optMMCP obj = 0;
///while((obj = opMMCNext(parent, obj))) {
///    opPrintf("found mmc called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00996'>PlatformConstruction/walker</a>
optMMCP opMMCNext (
    optModuleP module,
    optMMCP    mmc
);

/// Return the path to the file that implements the MMC
/// @return The path to the file that implements the MMC
/// @param mmc The MMC instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00690'>PlatformConstruction/walker</a>

const char * opMMCPath (
    optMMCP mmc
);

/// Restore the state of the given MMC by calling the callback one or more
/// times. The callback must return the data in the same size chunks as it was
/// saved. The userData passed to the callback should be used to refer to the
/// state of the storage mechanism.
/// @return Success or failure.
/// @param MMC      The MMC to restore
/// @param cb       The function used to restore data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opMMCStateRestore (
    optMMCP      MMC,
    optRestoreFn cb,
    void *       userData
);

/// Restore the state of the given MMC from the given file.
/// @return Success or failure.
/// @param MMC  The MMC to restore
/// @param file Restore the net contents from this file. The function will
///             return with an error if the file does not exist.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opMMCStateRestoreFile (
    optMMCP      MMC,
    const char * file
);

/// Save the state of the given MMC by calling the callback one or more times.
/// The callback decides how the data is stored. The userData passed to the
/// callback should be used to refer to the state of the storage mechanism.
/// @return Success or failure.
/// @param MMC      The MMC to save
/// @param cb       The function used to save data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opMMCStateSave (
    optMMCP   MMC,
    optSaveFn cb,
    void *    userData
);

/// Save the state of the given MMC to a file
/// @return Success or failure.
/// @param MMC  The MMC to save
/// @param file The file to hold the contents. The file will be overwritten
///             if it already exists.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opMMCStateSaveFile (
    optMMCP      MMC,
    const char * file
);

/// Return true if this MMC is transparent
/// @return True if this MMC is transparent
/// @param mmc The MMC instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00692'>PlatformConstruction/walker</a>

Bool opMMCTransparent (
    optMMCP mmc
);

/// Return the memory mapped register width in bits
/// @return Width of register in bits
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00709'>PlatformConstruction/walker</a>

Uns32 opMMRegisterBits (
    optMMRegisterP mmr
);

/// Return the memory mapped register description
/// @return Description of register
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00705'>PlatformConstruction/walker</a>

const char * opMMRegisterDescription (
    optMMRegisterP mmr
);

/// Return the register field number of bits
/// @return Number of bits in this field
/// @param field The register bit field
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00729'>PlatformConstruction/walker</a>

Uns32 opMMRegisterFieldBits (
    optMMRegisterFieldP field
);

/// Return the register field short description
/// @return Description
/// @param field The register bit field
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00725'>PlatformConstruction/walker</a>

const char * opMMRegisterFieldDescription (
    optMMRegisterFieldP field
);

/// This function returns the next prev from a reg. To get the first object,
/// prev should be null.
/// @param reg The parent object.
/// @param prev The iterator. Pass null to get the first object.
/// @return Returns the next prev, or null when there are no more objects.
/// @par Example:
/// @code
///optMMRegisterFieldP obj = 0;
///while((obj = opMMRegisterFieldNext(parent, obj))) {
///    opPrintf("found prev called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01010'>PlatformConstruction/walker</a>
optMMRegisterFieldP opMMRegisterFieldNext (
    optMMRegisterP      reg,
    optMMRegisterFieldP prev
);

/// Return the register field offset in bits from the LSB (starts at zero)
/// @return Field offset from LSB in bits
/// @param field The register bit field
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00727'>PlatformConstruction/walker</a>

Uns32 opMMRegisterFieldOffset (
    optMMRegisterFieldP field
);

/// Return true if the register field can be read
/// @return This field can be read
/// @param field The register bit field
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00731'>PlatformConstruction/walker</a>

Bool opMMRegisterFieldReadable (
    optMMRegisterFieldP field
);

/// Return the reset value
/// @return Reset or constant value of this field
/// @param field The register bit field
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00735'>PlatformConstruction/walker</a>

Uns64 opMMRegisterFieldReset (
    optMMRegisterFieldP field
);

/// Return true if the register field can be written
/// @return This field can be written
/// @param field The register bit field
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00733'>PlatformConstruction/walker</a>

Bool opMMRegisterFieldWritable (
    optMMRegisterFieldP field
);

/// Return the register index
/// @return index, starting at 1
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00717'>PlatformConstruction/walker</a>

Uns32 opMMRegisterIndex (
    optMMRegisterP mmr
);

/// Return true if this is a volatile register
/// @return True if reading the register might change its value
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00711'>PlatformConstruction/walker</a>

Bool opMMRegisterIsVolatile (
    optMMRegisterP mmr
);

/// Return the memory mapped register name
/// @return The name of the register
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase

const char * opMMRegisterName (
    optMMRegisterP mmr
);

/// Return the memory mapped register offset in bytes
/// @return Offset of register in bytes from the base of the bus port
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00707'>PlatformConstruction/walker</a>

Addr opMMRegisterOffset (
    optMMRegisterP mmr
);

/// Read the given memory mapped peripheral register (with side-effects)
/// @return True if the write was successful
/// @param mmr  The register descriptor
/// @param data Pointer to space holding the new value.
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2peripheralRegisterAccess_2harness_2harness_8c_source.html#l00084'>SimulationControl/peripheralRegisterAccess</a>

Bool opMMRegisterRead (
    optMMRegisterP mmr,
    void*          data
);

/// Return true if this register can be read
/// @return True if the register can be read
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00713'>PlatformConstruction/walker</a>

Bool opMMRegisterReadable (
    optMMRegisterP mmr
);

/// Read the given memory mapped peripheral register without side-effects
/// @return True if the read was successful
/// @param mmr  The register descriptor
/// @param data Pointer to space holding the new value.
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2peripheralRegisterAccess_2harness_2harness_8c_source.html#l00059'>SimulationControl/peripheralRegisterAccess</a>

Bool opMMRegisterView (
    optMMRegisterP mmr,
    void*          data
);

/// Return true if this register can be written
/// @return True if the register can be written
/// @param mmr The register descriptor
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00715'>PlatformConstruction/walker</a>

Bool opMMRegisterWritable (
    optMMRegisterP mmr
);

/// Write to the given memory mapped peripheral register (with side-effects)
/// @return True if the write was successful
/// @param mmr  The register descriptor
/// @param data Pointer to space holding the new value.
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2peripheralRegisterAccess_2harness_2harness_8c_source.html#l00068'>SimulationControl/peripheralRegisterAccess</a>

Bool opMMRegisterWrite (
    optMMRegisterP mmr,
    void*          data
);

/// Set a watchpoint to occur on a memory access. When a watchpoint is
/// triggered, if the notifierCB is specified, it will be called. If it returns
/// True, simulation will continue, otherwise it will stop. If the function is
/// not specified the simulator will stop. The simulator stops by returning to
/// its caller immediately after the access has completed.
/// @return New watchpoint
/// @param memory     The memory
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./opMemoryAccessWatchpointNew_8c_source.html#l00001'>Simple example</a>

optWatchpointP opMemoryAccessWatchpointNew (
    optMemoryP                   memory,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Load an application program into a memory using the installed program
/// loaders. All simulators will load ELF files, whereas some basic products
/// cannot load COFF. The user's own application program loaders can be
/// installed prior to calling this function.
/// @return The new application object
/// @param memory     The memory instance
/// @param path       The application object file
/// @param controls   Bitmask to control the loader behavior
/// @param loadOffset Add this to all load addresses
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00085'>SimulationControl/loadingApplicationPrograms</a>

optApplicationP opMemoryApplicationLoad (
    optMemoryP        memory,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset
);

/// Connect a memory bus port by name
/// @return The new connection
/// @param memory   The memory instance
/// @param bus      The bus instance
/// @param portName The name of the port on the memory
/// @param addrLo   The lower address limit
/// @param addrHi   The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opMemoryBusConnect (
    optMemoryP   memory,
    optBusP      bus,
    const char * portName,
    Addr         addrLo,
    Addr         addrHi
);

/// Add a fetch callback to the given address range on a memory. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param memory    memory
/// @param processor Optional processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00165'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00085'>SimulationControl/monitoringMemoryInModule</a>

void opMemoryFetchMonitorAdd (
    optMemoryP    memory,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Delete a fetch callback from the given address range on a memory if it
/// exists
/// @param memory    memory
/// @param processor Optional processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Simulation
/// - Pre-simulation

void opMemoryFetchMonitorDelete (
    optMemoryP    memory,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Signal that code memory has been changed and that any processors using the
/// given address range should invalidate cached JIT translations
/// @param memory Memory to flush
/// @param addrLo The lower address limit
/// @param addrHi The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opMemoryFlush (
    optMemoryP memory,
    Addr       addrLo,
    Addr       addrHi
);

/// Return the memory's maximum (byte) address. This is one byte less than the
/// size of the memory.
/// @return The maximum address of this memory instance
/// @param memory Memory
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00678'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00159'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00082'>SimulationControl/monitoringMemoryInModule</a>

Addr opMemoryMaxAddress (
    optMemoryP memory
);

/// Map native memory onto a bus at run-time. The memory must be pre-allocated
/// by the user.
/// @return True if the mapping was accepted
/// @param bus          The bus instance on which the bridge receives an
///                     access.
/// @param addrLo       The lowest address on the bus
/// @param addrHi       The highest address on the bus
/// @param nativeMemory The native memory to be mapped
/// @param priv         The access privilege for the new mapping
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opMemoryNativeDynamic (
    optBusP bus,
    Addr    addrLo,
    Addr    addrHi,
    void*   nativeMemory,
    optPriv priv
);

/// Inform the simulator that the given native region has changed value so that
/// the JIT simulator can invalidate any code cached from this region.
/// @param root  Platform root module
/// @param base  Native memory region
/// @param bytes Number of bytes in the region
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opMemoryNativeFlush (
    optModuleP  root,
    const void* base,
    UnsPS       bytes
);

/// Add an instance of a memory to a module, using pre-allocated native memory.
/// The memory must be a single contiguous region.
/// @return The new memory instance
/// @param module       The parent module instance
/// @param name         The name of the new instance. This string is copied
///                     so need not persist.
/// @param priv         The read-write-execute access privilege
/// @param maxAddress   Maximum address (size-1)
/// @param nativeMemory Pre-allocated memory
/// @param connections  Lists of connections. Refer to the optConnectionsP
///                     structure.
/// @param params       A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Be careful when allocating an amount of memory that could exhaust the host's
/// resources.
/// @par Examples:
/// - <a href='./PlatformConstruction_2nativeMemory_2module_2module_8c_source.html#l00056'>PlatformConstruction/nativeMemory</a>

optMemoryP opMemoryNativeNew (
    optModuleP      module,
    const char*     name,
    optPriv         priv,
    Addr            maxAddress,
    void*           nativeMemory,
    optConnectionsP connections,
    optParamP       params
);

/// Add an instance of a memory instance to a module, using an efficient sparse
/// memory implementation.
/// @return The new memory instance
/// @param module      The parent module instance
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param priv        The read-write-execute access privilege
/// @param maxAddress  The maximum address in bytes, equivalent to the memory
///                    size-1. This value can be larger than the available
///                    host memory
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00085'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00083'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00082'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./HelloWorld_2usingOP_2platform_2platform_8c_source.html#l00089'>HelloWorld/usingOP</a>
/// - <a href='./SimulationControl_2simplePlatformInHarnessUsingOP_2harness_2harness_8c_source.html#l00087'>SimulationControl/simplePlatformInHarnessUsingOP</a>

optMemoryP opMemoryNew (
    optModuleP      module,
    const char*     name,
    optPriv         priv,
    Addr            maxAddress,
    optConnectionsP connections,
    optParamP       params
);

/// This function returns the next memory from a module. To get the first
/// object, memory should be null.
/// @param module The parent object.
/// @param memory The iterator. Pass null to get the first object.
/// @return Returns the next memory, or null when there are no more objects.
/// @par Example:
/// @code
///optMemoryP obj = 0;
///while((obj = opMemoryNext(parent, obj))) {
///    opPrintf("found memory called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00084'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00989'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2loadingApplicationProgramIntelHexFormatFile_2harness_2harness_8c_source.html#l00071'>SimulationControl/loadingApplicationProgramIntelHexFormatFile</a>
/// - <a href='./SimulationControl_2loadingApplicationProgramBinaryFormatFile_2harness_2harness_8c_source.html#l00071'>SimulationControl/loadingApplicationProgramBinaryFormatFile</a>
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00157'>SimulationControl/monitoringAccesses</a>
optMemoryP opMemoryNext (
    optModuleP module,
    optMemoryP memory
);

/// Return the memory access privilege.
/// @return The read-write-execute access privilege
/// @param memory Memory
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00676'>PlatformConstruction/walker</a>

optPriv opMemoryPriv (
    optMemoryP memory
);

/// Read data from a memory, specifying the address within the memory (rather
/// than the address on the bus to which it is connected).
/// @return True if success
/// @param memory  Memory to read
/// @param address Memory address
/// @param buffer  Native buffer
/// @param bytes   Number of bytes
/// @param debug   Set this to true if the read should be treated as a debug
///                access (which does not perturb the platform state)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opMemoryRead (
    optMemoryP memory,
    Addr       address,
    void*      buffer,
    Uns32      bytes,
    Bool       debug
);

/// Add a read callback to the given address range on a memory. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param memory    memory
/// @param processor Optional processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00166'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00086'>SimulationControl/monitoringMemoryInModule</a>

void opMemoryReadMonitorAdd (
    optMemoryP    memory,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Delete a read callback from the given address range on a memory if it exists
/// @param memory    memory
/// @param processor Optional processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opMemoryReadMonitorDelete (
    optMemoryP    memory,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Set a watchpoint to occur on a memory read. When a watchpoint is triggered,
/// if the notifierCB is specified, it will be called. If it returns True,
/// simulation will continue, otherwise it will stop. If the function is not
/// specified the simulator will stop. The simulator stops by returning to its
/// caller immediately after the access has completed.
/// @return New watchpoint
/// @param memory     The memory
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00084'>SimulationControl/addingWatchpoints</a>

optWatchpointP opMemoryReadWatchpointNew (
    optMemoryP                   memory,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Parse a memory specification in the form
/// [name:]addrLo:addrHi[:priv[:shared]][,repeat]. Privilege must be a
/// combination of r,w,x and - (case insensitive). Memories without a name will
/// be called mem0, mem1 etc. Memories without privilege will be rwx.
/// @return The number of parsed memory specifications
/// @param spec      The memory specification string
/// @param specArray Array of memory specifications to be filled
/// @param max       Number of entries in the array (will not be exceeded)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Notes:
/// If the names are not specified, names mem0, mem1 etc are created, without
/// regard for any other names in existence. Care should be taken to avoid
/// clashes with other objects in the same scope.
/// @sa
/// opMemoryNew

Uns32 opMemorySpecParse (
    const char *   spec,
    optMemorySpecP specArray,
    Uns32          max
);

/// Restore the state of the given memory by calling the callback one or more
/// times. The callback must return the data in the same size chunks as it was
/// saved. The userData passed to the callback should be used to refer to the
/// state of the storage mechanism.
/// @return Success or failure.
/// @param memory   The memory to restore
/// @param cb       The function used to restore data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00154'>SimulationControl/processorModelSaveRestoreValidation</a>

optSaveRestoreStatus opMemoryStateRestore (
    optMemoryP   memory,
    optRestoreFn cb,
    void *       userData
);

/// Restore the state of the given memory from the given file.
/// @return Success or failure.
/// @param memory The memory to restore
/// @param file   Restore the memory contents from this file. The function
///               will return with an error if the file does not exist.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opMemoryStateRestoreFile (
    optMemoryP   memory,
    const char * file
);

/// Save the state of the given memory by calling the callback one or more
/// times. The callback decides how the data is stored. The userData passed to
/// the callback should be used to refer to the state of the storage mechanism.
/// @return Success or failure.
/// @param memory   The memory to save
/// @param cb       The function used to save data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00140'>SimulationControl/processorModelSaveRestoreValidation</a>

optSaveRestoreStatus opMemoryStateSave (
    optMemoryP memory,
    optSaveFn  cb,
    void *     userData
);

/// Save the state of the given memory to a file
/// @return Success or failure.
/// @param memory The memory to save
/// @param file   The file to hold the contents. The file will be overwritten
///               if it already exists.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opMemoryStateSaveFile (
    optMemoryP   memory,
    const char * file
);

/// Write data to a memory
/// @return Returns true if successful
/// @param memory  Memory to write
/// @param address Memory address
/// @param buffer  Native buffer
/// @param bytes   Number of bytes
/// @param debug   True if this should not perturb the platform state (other
///                than the memory location)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationProgramIntelHexFormatFile_2harness_2harness_8c_source.html#l00156'>SimulationControl/loadingApplicationProgramIntelHexFormatFile</a>
/// - <a href='./SimulationControl_2loadingApplicationProgramBinaryFormatFile_2harness_2harness_8c_source.html#l00116'>SimulationControl/loadingApplicationProgramBinaryFormatFile</a>

Bool opMemoryWrite (
    optMemoryP  memory,
    Addr        address,
    const void* buffer,
    Uns32       bytes,
    Bool        debug
);

/// Add a write callback to the given address range on a memory. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param memory    memory
/// @param processor Optional processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00167'>SimulationControl/monitoringAccesses</a>
/// - <a href='./SimulationControl_2monitoringMemoryInModule_2module_2module_8c_source.html#l00087'>SimulationControl/monitoringMemoryInModule</a>

void opMemoryWriteMonitorAdd (
    optMemoryP    memory,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Remove a write callback from the given address range on a memory if it
/// exists
/// @param memory    memory
/// @param processor Optional processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opMemoryWriteMonitorDelete (
    optMemoryP    memory,
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Set a watchpoint on a memory write write. When a watchpoint is triggered, if
/// the notifierCB is specified, it will be called. If it returns True,
/// simulation will continue, otherwise it will stop. If the function is not
/// specified the simulator will stop. The simulator stops by returning to its
/// caller immediately after the access has completed.
/// @return New watchpoint
/// @param memory     The memory
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00092'>SimulationControl/addingWatchpoints</a>

optWatchpointP opMemoryWriteWatchpointNew (
    optMemoryP                   memory,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Send formatted text to the simulator output stream. The text is prefixed
/// with the severity and a prefix code which should be a short string. Use this
/// for user-level diagnostics.
/// @param severity I=Info, W=Warning, E=Error, F=Fatal (aborts the
///                 simulator)
/// @param ident    A short, easily searched code to identify this message
/// @param fmt      Printf format string (see gnu printf for details)
/// @param ...      This is a vararg function
/// @par Phase:
/// Can be used in any phase
/// @par Notes:
/// If the message does not end with a newline, opMessage inserts a newline at
/// the end of the text
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00081'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00062'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00036'>SimulationControl/interruptSimulation</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00045'>SimulationControl/startingApplicationDebug</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00080'>PlatformConstruction/walker</a>

void opMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
                ...
) __attribute__(( format (printf, 3,4)));

/// Suppress the printing of messages with an identifier beginning with the
/// given string
/// @param ident The start of the identifier to be suppressed. e.g. 'OP_'
///              turns off messages beginning OP_
/// @par Phase:
/// Can be used in any phase
/// @sa
/// opMessage
/// opMessageEnable

void opMessageDisable (
    const char* ident
);

/// Do not suppress the printing of messages with an identifier beginning with
/// the given string
/// @param ident The start of the identifier not to be suppressed. e.g. 'OP_'
///              turns off messages beginning OP_
/// @par Phase:
/// Can be used in any phase
/// @sa
/// opMessage
/// opMessageDisable

void opMessageEnable (
    const char* ident
);

/// Returns the value of the simulator command line -quiet flag. A model should
/// use this to suppress all non-essential messages.
/// @return True if -quiet is specified.
/// @par Phase:
/// Can be used in any phase

Bool opMessageQuiet (void);

/// Make the simulator session suppress warning messages
/// @return The old value
/// @param quiet True to suppress warning messages
/// @par Phase:
/// Can be used in any phase

Bool opMessageSetNoWarn (
    Bool quiet
);

/// Make the simulator session suppress non-essential messages.
/// @return The old value
/// @param quiet Set true to suppress non-essential messages
/// @par Phase:
/// Can be used in any phase

Bool opMessageSetQuiet (
    Bool quiet
);

/// Return the value of the simulator command line -verbose flag. A model should
/// use this to turn on printing of extra information.
/// @return True if -verbose is specified
/// @par Phase:
/// Can be used in any phase

Bool opMessageVerbose (void);

/// Return the model-specific mode code from the descriptor
/// @return The mode code (a small integer)
/// @param mode Processor mode descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00367'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00231'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00160'>DebuggerIntegration/modeAndException</a>

Uns32 opModeCode (
    optModeP mode
);

/// Return the description of the mode from the descriptor
/// @return Mode description
/// @param mode Processor mode descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00369'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00232'>SimulationControl/processorQuery</a>

const char* opModeDescription (
    optModeP mode
);

/// Return the name of the mode from the descriptor
/// @return Mode name (note that this string does not persist)
/// @param mode Processor mode descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00365'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00230'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00161'>DebuggerIntegration/modeAndException</a>

const char* opModeName (
    optModeP mode
);

/// Display all the buses in the given module. Refer also to opBusShow.
/// @param module The module containing the buses
/// @par Phase:
/// Can be used in any phase

void opModuleBusShow (
    optModuleP module
);

/// Display a summary of all commands installed in models in the given module
/// (and sub-modules)
/// @param module Root of the module hierarchy to show. If null then all then
///               modules will be shown.
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2callingInstalledCommands_2harness_2harness_8c_source.html#l00092'>SimulationControl/callingInstalledCommands</a>

void opModuleCommandsShow (
    optModuleP module
);

/// Return the current time of the simulation that contains this module
/// instance,
/// @return The current time
/// @param module The module instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2module_2module_8c_source.html#l00059'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./SimulationControl_2customScheduler_2harness_2harness_8c_source.html#l00121'>SimulationControl/customScheduler</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00038'>SimulationControl/behavioralCcodeInModule</a>

optTime opModuleCurrentTime (
    optModuleP module
);

/// Set the diagnostic level in the given module (if the module supports this
/// operation). Values > 15 will also turn on system diagnostics.
/// @param module The module instance
/// @param level  The new diagnostic level (values > 15 will turn on system
///               diagnostics)
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opModuleDiagnosticLevelSet (
    optModuleP module,
    Uns32      level
);

/// Add documentation section to a module
/// @return The new (root) document node
/// @param module The module being documented
/// @param name   The name of the new section
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optDocNodeP opModuleDocSectionAdd (
    optModuleP   module,
    const char * name
);

/// Print a report of each of the domains in the given module.
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opModuleDomainDebug (
    optModuleP module
);

/// Signal that this module wants to terminate the session
/// @param module Current module instance
/// @param status Specify the return code for the program. This will be used
///               if the simulator calls exit
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opModuleFinish (
    optModuleP module,
    Int32      status
);

/// Return the finish status of this root module
/// @return The finish status
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Int32 opModuleFinishStatus (
    optModuleP module
);

/// Display all the formal parameters (overrides) of all models, modules and
/// sub-modules starting with the given module.
/// @param module     The root of the hierarchy to show. If null then all
///                   root modules will be shown
/// @param paramClass Choose to show system, model or all
/// @par Phase:
/// Can be used in any phase

void opModuleFormalsShow (
    optModuleP    module,
    optParamClass paramClass
);

/// Start an HTTP server for this model
/// @return Handle to the newly created channel
/// @param module   The module
/// @param methods  Structure containing the server's callbacks.
/// @param portNum  Port number (or zero to get a port from the pool)
/// @param fileRoot Root of files for this model. If null this defaults to a
///                 directory 'httpvis' under the directory that contains the
///                 peripheral executable.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

octHTTPChannelP opModuleHTTPOpen (
    optModuleP      module,
    octHTTPMethodsP methods,
    Uns32           portNum,
    const char *    fileRoot
);

/// Add an instance of a module to another module by loading a module file. This
/// function does the following steps, with error detection at each stage. -
/// Locate and load the passed shared object (DLL) - Find the symbol
/// 'modelAttrs' to locate the entry point structure. - Check that the shared
/// object is the right type - a module. - Check the version field against this
/// simulator. - Allocate space for the module's persistent data if required. -
/// Call the iterator functions to verify the parameters, bus, net, FIFO and
/// packetnet connections against those expected. - Call the constructor. Note
/// that this will cause the construction of sub-modules and other model
/// instances.
/// @return The new module instance
/// @param module      The parent module instance
/// @param path        Path to the module, usually calculated by
///                    opVLNVString()
/// @param name        The name of the new instance or null. This string is
///                    copied so need not persist. If null the name is taken
///                    from the model (but only one instance like this will
///                    be allowed)
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Notes:
/// The object file will be loaded the first time it is referenced by this
/// function. Subsequent references will re-use the object. Thus any data
/// declared 'static' in the module, will be shared by all instances.
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00039'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00096'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00067'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00070'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00065'>PlatformConstruction/staticBridgeHierarchy</a>
/// @sa
/// opVLNVString
/// opRootModuleNew

optModuleP opModuleNew (
    optModuleP      module,
    const char*     path,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// Add an instance of a module to another module using a module modelAttrs
/// structure. This is similar to opModuleNew, but uses a modelAttrs structure
/// (and the functions it refers to) from code that is already loaded - probably
/// part of this file.
/// @return The new module instance
/// @param module      The parent module instance
/// @param attrs       The attributes table
/// @param name        The name of the new instance or null. The string is
///                    copied so need not persist. If null the name is taken
///                    from the model (but only one instance like this will
///                    be allowed)
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optModuleP opModuleNewFromAttrs (
    optModuleP      module,
    optModuleAttrP  attrs,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// This function returns the next module from a parent. To get the first
/// object, module should be null.
/// If parent is null, this function returns the next root module.
/// @param parent The parent object.
/// @param module The iterator. Pass null to get the first object.
/// @return Returns the next module, or null when there are no more objects.
/// @par Example:
/// @code
///optModuleP obj = 0;
///while((obj = opModuleNext(parent, obj))) {
///    opPrintf("found module called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01017'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2customApplicationLoader_2harness_2harness_8c_source.html#l00047'>SimulationControl/customApplicationLoader</a>
optModuleP opModuleNext (
    optModuleP parent,
    optModuleP module
);

/// Return the module object (persistent data)
/// @return The object
/// @param module Module
/// @par Phase:
/// Can be used in any phase

optModuleObjectP opModuleObject (
    optModuleP module
);

/// Return the file path to the object that implements this module
/// @return Cannonical path to module object
/// @param module Module
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00742'>PlatformConstruction/walker</a>

const char * opModulePath (
    optModuleP module
);

/// Return the purpose of this module. Purpose is a string used by product
/// packaging tools.
/// @return The module's purpose.
/// @param module Module
/// @par Phase:
/// Can be used in any phase

optPurpose opModulePurpose (
    optModuleP module
);

/// Display a summary all modules, sub-modules, models, formals and actual
/// parameters.
/// @param module The root of hierarchy to show, or null for all
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00201'>SimulationControl/monitoringAccesses</a>

void opModuleShow (
    optModuleP module
);

/// Schedule a call to the the given function when the given time has elapsed.
/// @return Trigger object (if required, use this to delete the trigger
///         before it occurs)
/// @param module       The parent module instance
/// @param relativeTime Time into the future
/// @param cb           The callback
/// @param userData     The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

optTriggerEventP opModuleTriggerAdd (
    optModuleP   module,
    optTime      relativeTime,
    optTriggerFn cb,
    void*        userData
);

/// Remove a trigger event, so the callback will not be called.
/// @param module The parent module instance
/// @param event  The trigger event to delete
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opModuleTriggerDelete (
    optModuleP       module,
    optTriggerEventP event
);

/// This function returns the next netmonitor from a net. To get the first
/// object, netmonitor should be null.
/// @param net The parent object.
/// @param netmonitor The iterator. Pass null to get the first object.
/// @return Returns the next netmonitor, or null when there are no more objects.
/// @par Example:
/// @code
///optNetMonitorP obj = 0;
///while((obj = opNetMonitorNext(parent, obj))) {
///    opPrintf("found netmonitor called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01031'>PlatformConstruction/walker</a>
optNetMonitorP opNetMonitorNext (
    optNetP        net,
    optNetMonitorP netmonitor
);

/// Add an instance of a net to a module (with an optional external net port)
/// @return The new net instance
/// @param module   The parent module instance
/// @param name     The name of the new instance. This string is copied so
///                 need not persist.
/// @param portName If specified, this parameter creates a module net port of
///                 this name so that other modules can connect to this net.
/// @param params   A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00060'>SimulationControl/processorExternalInterruptControl</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00031'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00031'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00057'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./PlatformConstruction_2netHierarchy_2harness_2harness_8c_source.html#l00067'>PlatformConstruction/netHierarchy</a>

optNetP opNetNew (
    optModuleP  module,
    const char* name,
    const char* portName,
    optParamP   params
);

/// This function returns the next net from a module. To get the first object,
/// net should be null.
/// @param module The parent object.
/// @param net The iterator. Pass null to get the first object.
/// @return Returns the next net, or null when there are no more objects.
/// @par Example:
/// @code
///optNetP obj = 0;
///while((obj = opNetNext(parent, obj))) {
///    opPrintf("found net called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01024'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2monitoringNets_2harness_2harness_8c_source.html#l00040'>SimulationControl/monitoringNets</a>
/// - <a href='./SimulationControl_2monitoringNetsInModule_2module_2module_8c_source.html#l00064'>SimulationControl/monitoringNetsInModule</a>
optNetP opNetNext (
    optModuleP module,
    optNetP    net
);

/// Return the net connected to this net port connection
/// @return The net instance
/// @param netPort The current net port connection
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00799'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00063'>SimulationControl/processorExternalInterruptControl</a>

optNetP opNetPortConnNet (
    optNetPortConnP netPort
);

/// This function returns the next netPortConn from a net. To get the first
/// object, netPortConn should be null.
/// @param net The parent object.
/// @param netPortConn The iterator. Pass null to get the first object.
/// @return Returns the next netPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optNetPortConnP obj = 0;
///while((obj = opNetPortConnNext(parent, obj))) {
///    opPrintf("found netPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00119'>PlatformConstruction/walker</a>
optNetPortConnP opNetPortConnNext (
    optNetP         net,
    optNetPortConnP netPortConn
);

/// Return the net port connection type from the descriptor
/// @return The type of port
/// @param netPort The net port connection
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00797'>PlatformConstruction/walker</a>

optNetPortType opNetPortConnType (
    optNetPortConnP netPort
);

/// Return a description of the net port supplied by the model
/// @return A description of the net port
/// @param netPort The net port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00786'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00329'>SimulationControl/processorQuery</a>

const char* opNetPortDescription (
    optNetPortP netPort
);

/// Return true if this port cannot be left unconnected
/// @return True if this bus port must be connected
/// @param netPort The net port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00790'>PlatformConstruction/walker</a>

Bool opNetPortMustConnect (
    optNetPortP netPort
);

/// Return the net port type from the net port descriptor
/// @return The type of port (OP_INPUT or OP_OUTPUT)
/// @param netPort The net port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00788'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00331'>SimulationControl/processorQuery</a>

optNetPortType opNetPortType (
    optNetPortP netPort
);

/// Return the net port type from the descriptor as a string
/// @return The type
/// @param netPort The net port descriptor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00332'>SimulationControl/processorQuery</a>

const char* opNetPortTypeString (
    optNetPortP netPort
);

/// Print connection information about this net
/// @param net The net instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00105'>SimulationControl/behavioralCcodeInModule</a>

void opNetShow (
    optNetP net
);

/// Restore the state of the given net by calling the callback one or more
/// times. The callback must return the data in the same size chunks as it was
/// saved. The userData passed to the callback should be used to refer to the
/// state of the storage mechanism.
/// @return Success or failure.
/// @param net      The net to restore
/// @param cb       The function used to restore data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opNetStateRestore (
    optNetP      net,
    optRestoreFn cb,
    void *       userData
);

/// Restore the state of the given net from the given file.
/// @return Success or failure.
/// @param net  The net to restore
/// @param file Restore the net contents from this file. The function will
///             return with an error if the file does not exist.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opNetStateRestoreFile (
    optNetP      net,
    const char * file
);

/// Save the state of the given net by calling the callback one or more times.
/// The callback decides how the data is stored. The userData passed to the
/// callback should be used to refer to the state of the storage mechanism.
/// @return Success or failure.
/// @param net      The net to save
/// @param cb       The function used to save data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opNetStateSave (
    optNetP   net,
    optSaveFn cb,
    void *    userData
);

/// Save the state of the given net to a file
/// @return Success or failure.
/// @param net  The net to save
/// @param file The file to hold the contents. The file will be overwritten
///             if it already exists.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opNetStateSaveFile (
    optNetP      net,
    const char * file
);

/// Read the current value of a net
/// @return Returns the net value.
/// @param net The net instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opNetValue_8c_source.html#l00001'>Simple example</a>

Uns64 opNetValue (
    optNetP net
);

/// Read a net's previous value
/// @return Returns the net value prior to the most recent write.
/// @param net The net instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Uns64 opNetValuePrevious (
    optNetP net
);

/// Write a value to a net.
/// @return Returns True if anything was triggered by the write.
/// @param net   The net instance
/// @param value New value
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2module_2module_8c_source.html#l00062'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00054'>SimulationControl/processorResetControl</a>
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00073'>SimulationControl/processorExternalInterruptControl</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00081'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./PlatformConstruction_2netHierarchy_2module_2module_8c_source.html#l00057'>PlatformConstruction/netHierarchy</a>

Bool opNetWrite (
    optNetP net,
    Uns64   value
);

/// Install a callback to be called when a net is written by one of its drivers.
/// Use the macro OP_NET_WRITE_FN to define the callback.
/// @param net      The net instance to carry the callback
/// @param cb       The function to be called when the net is written
/// @param userData The user data to be passed to the callback.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2module_2module_8c_source.html#l00093'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00051'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./PlatformConstruction_2netHierarchy_2module_2module_8c_source.html#l00081'>PlatformConstruction/netHierarchy</a>
/// - <a href='./SimulationControl_2monitoringNets_2harness_2harness_8c_source.html#l00042'>SimulationControl/monitoringNets</a>
/// - <a href='./SimulationControl_2monitoringNetsInModule_2module_2module_8c_source.html#l00066'>SimulationControl/monitoringNetsInModule</a>

void opNetWriteMonitorAdd (
    optNetP       net,
    optNetWriteFn cb,
    void*         userData
);

/// Return the state of the --nobanner flag from the command line
/// @return True if the banners should not be printed
/// @par Phase:
/// Can be used in any phase

Bool opNoBanner (void);

/// This function returns the next application from a object. To get the first
/// object, application should be null.
/// @param object The parent object.
/// @param application The iterator. Pass null to get the first object.
/// @return Returns the next application, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optApplicationP obj = 0;
///while((obj = opObjectApplicationNext(parent, obj))) {
///    opPrintf("found application called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00128'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00884'>PlatformConstruction/walker</a>
optApplicationP opObjectApplicationNext (
    optObjectP      object,
    optApplicationP application
);

/// This function returns the next busPortConn from a object. To get the first
/// object, busPortConn should be null.
/// @param object The parent object.
/// @param busPortConn The iterator. Pass null to get the first object.
/// @return Returns the next busPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optBusPortConnP obj = 0;
///while((obj = opObjectBusPortConnNext(parent, obj))) {
///    opPrintf("found busPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00919'>PlatformConstruction/walker</a>
optBusPortConnP opObjectBusPortConnNext (
    optObjectP      object,
    optBusPortConnP busPortConn
);

/// This function returns the next busPort from a object. To get the first
/// object, busPort should be null.
/// @param object The parent object.
/// @param busPort The iterator. Pass null to get the first object.
/// @return Returns the next busPort, or null when there are no more objects.
/// @par Example:
/// @code
///optBusPortP obj = 0;
///while((obj = opObjectBusPortNext(parent, obj))) {
///    opPrintf("found busPort called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00912'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00303'>SimulationControl/processorQuery</a>
optBusPortP opObjectBusPortNext (
    optObjectP  object,
    optBusPortP busPort
);

/// Find any object by its hierarchical name. The hierarchy delimiter is '/'.
/// Wildcards '*' and '?' are allowed between delimiters. If a wildcard matches
/// multiple objects, the first will be returned.
/// @return Platform object of any type
/// @param object The root of the search
/// @param name   The hierarchical name (names separated by the '/'
///               character).
/// @param mask   A bitmask of types to find
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optBridgeP
/// - optBusP
/// - optFIFOP
/// - optExtensionP
/// - optExtElabP
/// - optMemoryP
/// - optMMCP
/// - optMMRegisterP
/// - optModuleP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// - optProcessorP
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00050'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00104'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00113'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00071'>SimulationControl/interruptSimulation</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00074'>PlatformConstruction/walker</a>

optObjectP opObjectByName (
    optObjectP  object,
    const char* name,
    optStrType  mask
);

/// Return the object class instance
/// @return The class instance (could be null)
/// @param object The object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optBridgeP
/// - optBusP
/// - optFIFOP
/// - optExtensionP
/// - optExtElabP
/// - optMemoryP
/// - optMMCP
/// - optMMRegisterP
/// - optNetP
/// - optModuleP
/// - optPeripheralP
/// - optProcessorP
/// - optProcessorP

void* opObjectClass (
    optObjectP object
);

/// Set the object class instance
/// @param object        The object
/// @param classInstance The class instance
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optBridgeP
/// - optBusP
/// - optFIFOP
/// - optExtensionP
/// - optExtElabP
/// - optMemoryP
/// - optMMCP
/// - optMMRegisterP
/// - optNetP
/// - optModuleP
/// - optPeripheralP
/// - optProcessorP
/// - optProcessorP

void opObjectClassSet (
    optObjectP object,
    void *     classInstance
);

/// This function returns the next current from a object. To get the first
/// object, current should be null.
/// @param object The parent object.
/// @param current The iterator. Pass null to get the first object.
/// @return Returns the next current, or null when there are no more objects.
/// @par Example:
/// @code
///optCommandP obj = 0;
///while((obj = opObjectCommandNext(parent, obj))) {
///    opPrintf("found current called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00926'>PlatformConstruction/walker</a>
optCommandP opObjectCommandNext (
    optObjectP  object,
    optCommandP current
);

/// Return the next document node attached to the given instance
/// @return The next document node or null if there are no more
/// @param object  The parent instance
/// @param docNode The current node or null
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optProcessorP
/// - optPeripheralP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00491'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00476'>SimulationControl/processorQuery</a>

optDocNodeP opObjectDocNodeNext (
    optObjectP  object,
    optDocNodeP docNode
);

/// This function returns the next extElab from a object. To get the first
/// object, extElab should be null.
/// @param object The parent object.
/// @param extElab The iterator. Pass null to get the first object.
/// @return Returns the next extElab, or null when there are no more objects.
/// @par Example:
/// @code
///optExtElabP obj = 0;
///while((obj = opObjectExtElabNext(parent, obj))) {
///    opPrintf("found extElab called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00940'>PlatformConstruction/walker</a>
optExtElabP opObjectExtElabNext (
    optObjectP  object,
    optExtElabP extElab
);

/// This function returns the next extension from a object. To get the first
/// object, extension should be null.
/// @param object The parent object.
/// @param extension The iterator. Pass null to get the first object.
/// @return Returns the next extension, or null when there are no more objects.
/// @par Example:
/// @code
///optExtensionP obj = 0;
///while((obj = opObjectExtensionNext(parent, obj))) {
///    opPrintf("found extension called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00933'>PlatformConstruction/walker</a>
optExtensionP opObjectExtensionNext (
    optObjectP    object,
    optExtensionP extension
);

/// This function returns the next FIFOPortConn from a object. To get the first
/// object, FIFOPortConn should be null.
/// @param object The parent object.
/// @param FIFOPortConn The iterator. Pass null to get the first object.
/// @return Returns the next FIFOPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optFIFOPortConnP obj = 0;
///while((obj = opObjectFIFOPortConnNext(parent, obj))) {
///    opPrintf("found FIFOPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00961'>PlatformConstruction/walker</a>
optFIFOPortConnP opObjectFIFOPortConnNext (
    optObjectP       object,
    optFIFOPortConnP FIFOPortConn
);

/// This function returns the next FIFOPort from a object. To get the first
/// object, FIFOPort should be null.
/// @param object The parent object.
/// @param FIFOPort The iterator. Pass null to get the first object.
/// @return Returns the next FIFOPort, or null when there are no more objects.
/// @par Example:
/// @code
///optFIFOPortP obj = 0;
///while((obj = opObjectFIFOPortNext(parent, obj))) {
///    opPrintf("found FIFOPort called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00954'>PlatformConstruction/walker</a>
optFIFOPortP opObjectFIFOPortNext (
    optObjectP   object,
    optFIFOPortP FIFOPort
);

/// Iterator for formal parameter groups of the given type.
/// @return Return the next formal group of the given type or null
/// @param object Any structural object in a platform
/// @param formal Current formal parameter group or null to get the first one
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optBusP
/// - optMemoryP
/// - optMMCP
/// - optModuleP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00975'>PlatformConstruction/walker</a>

optFormalGroupP opObjectFormalGroupNext (
    optObjectP      object,
    optFormalGroupP formal
);

/// Iterator for formal parameters of the given type.
/// @return Return the next formal of the given type or null
/// @param object Any structural object in a platform
/// @param formal Current formal parameter or null to get the first one
/// @param clss   Class: system, model or all
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optBridgeP
/// - optBusP
/// - optFIFOP
/// - optExtElabP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optModuleP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00968'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00277'>SimulationControl/processorQuery</a>

optFormalP opObjectFormalNext (
    optObjectP    object,
    optFormalP    formal,
    optParamClass clss
);

/// Return the hierarchical name of any platform object, using the '/' as a
/// separator.
/// @return The hierarchical name, if the object has one, otherwise null
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP
/// @par Restrictions:
/// The returned string will be re-used next time this function is used. Not all
/// platform objects have a hierarchical name.
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00139'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00037'>SimulationControl/interruptSimulation</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00100'>PlatformConstruction/walker</a>
/// - <a href='./PlatformConstruction_2usingExternalMemory_2module_2module_8c_source.html#l00035'>PlatformConstruction/usingExternalMemory</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2module_2module_8c_source.html#l00060'>SimulationControl/behavioralCcodeInModule</a>

const char* opObjectHierName (
    optObjectP object
);

/// Return the SystemC compatible hierarchical name of any platform object. This
/// will have no '.' or '/' delimiters
/// @return The hierarchical name, '/' and '.' replaced with '_'.
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP
/// @par Restrictions:
/// See opObjectHierName()

const char* opObjectHierSCName (
    optObjectP object
);

/// Return the module immediately containing the given object
/// @return The parent module
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP

optModuleP opObjectModule (
    optObjectP object
);

/// Return the local name of a platform object (this name does not include the
/// object's hierarchy).
/// @return The name of the object if it exists (some OP objects have no
///         name). The returned string is static.
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP
/// @par Restrictions:
/// The returned string is static so can be relied on to persist. Not all
/// platform objects have a name.
/// @par Notes:
/// A processor can have more than one processing element, each with its own
/// name which represents its position in the hierarchy inside the processor.
/// The name is created within the model and might reflect this hierarchy.
/// @par Examples:
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00070'>SimulationControl/startingApplicationDebug</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00310'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00261'>SimulationControl/processorQuery</a>
/// - <a href='./PlatformConstruction_2nativeMemory_2module_2module_8c_source.html#l00053'>PlatformConstruction/nativeMemory</a>
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00076'>SimulationControl/processorResetControl</a>

const char* opObjectName (
    optObjectP object
);

/// Connect a net to an instance by name. (The usual way to connect a net is
/// with the OP_CONNECTIONS macro). Use this function when making a temporary
/// connection in a test-harness.
/// @return The new connection
/// @param object   The object instance
/// @param net      The net instance
/// @param portName The name of the port on the instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optProcessorP
/// - optPeripheralP
/// @par Examples:
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00061'>SimulationControl/processorExternalInterruptControl</a>

optNetPortConnP opObjectNetConnect (
    optObjectP   object,
    optNetP      net,
    const char * portName
);

/// This function returns the next netPortConn from a object. To get the first
/// object, netPortConn should be null.
/// @param object The parent object.
/// @param netPortConn The iterator. Pass null to get the first object.
/// @return Returns the next netPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optNetPortConnP obj = 0;
///while((obj = opObjectNetPortConnNext(parent, obj))) {
///    opPrintf("found netPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01045'>PlatformConstruction/walker</a>
optNetPortConnP opObjectNetPortConnNext (
    optObjectP      object,
    optNetPortConnP netPortConn
);

/// This function returns the next netPort from a object. To get the first
/// object, netPort should be null.
/// @param object The parent object.
/// @param netPort The iterator. Pass null to get the first object.
/// @return Returns the next netPort, or null when there are no more objects.
/// @par Example:
/// @code
///optNetPortP obj = 0;
///while((obj = opObjectNetPortNext(parent, obj))) {
///    opPrintf("found netPort called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01038'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00327'>SimulationControl/processorQuery</a>
optNetPortP opObjectNetPortNext (
    optObjectP  object,
    optNetPortP netPort
);

/// This function returns the next packetnetPortConn from a object. To get the
/// first object, packetnetPortConn should be null.
/// @param object The parent object.
/// @param packetnetPortConn The iterator. Pass null to get the first object.
/// @return Returns the next packetnetPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optPacketnetPortConnP obj = 0;
///while((obj = opObjectPacketnetPortConnNext(parent, obj))) {
///    opPrintf("found packetnetPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01073'>PlatformConstruction/walker</a>
optPacketnetPortConnP opObjectPacketnetPortConnNext (
    optObjectP            object,
    optPacketnetPortConnP packetnetPortConn
);

/// This function returns the next netPort from a object. To get the first
/// object, netPort should be null.
/// @param object The parent object.
/// @param netPort The iterator. Pass null to get the first object.
/// @return Returns the next netPort, or null when there are no more objects.
/// @par Example:
/// @code
///optPacketnetPortP obj = 0;
///while((obj = opObjectPacketnetPortNext(parent, obj))) {
///    opPrintf("found netPort called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01066'>PlatformConstruction/walker</a>
optPacketnetPortP opObjectPacketnetPortNext (
    optObjectP        object,
    optPacketnetPortP netPort
);

/// Fetch a parameter value as a boolean
/// @return The value
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00317'>PlatformConstruction/walker</a>

Bool opObjectParamBoolValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Fetch a parameter value as a double precision float (will attempt to convert
/// the value to this type)
/// @return The value
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00322'>PlatformConstruction/walker</a>

double opObjectParamDoubleValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Return the value of an endian parameter
/// @return The endian enumeration
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00323'>PlatformConstruction/walker</a>

optEndian opObjectParamEndianValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Fetch a parameter value as an enum (will attempt to convert the value to
/// this type)
/// @return The enum value as an Uns32
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00324'>PlatformConstruction/walker</a>

Uns32 opObjectParamEnumValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Fetch a parameter value as an Int32 (will attempt to convert the value to
/// this type)
/// @return The value as an Int32
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00318'>PlatformConstruction/walker</a>

Int32 opObjectParamInt32Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Fetch a parameter value as an Int64 (will attempt to convert the value to
/// this type)
/// @return The value as an Int64
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00319'>PlatformConstruction/walker</a>

Int64 opObjectParamInt64Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// This function returns the next param from a object. To get the first object,
/// param should be null.
/// @param object The parent object.
/// @param param The iterator. Pass null to get the first object.
/// @return Returns the next param, or null when there are no more objects.
/// @par Example:
/// @code
///optParamP obj = 0;
///while((obj = opObjectParamNext(parent, obj))) {
///    opPrintf("found param called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01080'>PlatformConstruction/walker</a>
optParamP opObjectParamNext (
    optObjectP object,
    optParamP  param
);

/// Fetch a parameter value as a pointer
/// @return The value
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00325'>PlatformConstruction/walker</a>

void* opObjectParamPtrValue (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Fetch a parameter value as a string (will convert when possible)
/// @return The value as a string (the string must be used or copied)
/// @param object The object with the parameter
/// @param name   The parameter name
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00317'>PlatformConstruction/walker</a>

const char * opObjectParamStringValue (
    optObjectP   object,
    const char * name
);

/// Fetch a parameter value as an Uns32 (will attempt to convert the value to
/// this type)
/// @return The value as an Uns32
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00320'>PlatformConstruction/walker</a>

Uns32 opObjectParamUns32Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Fetch a parameter value as an Uns64 (will attempt to convert the value to
/// this type)
/// @return The value as an Uns64
/// @param object The object with the parameter
/// @param name   The parameter name
/// @param set    This boolean is set if the parameter has been set
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optProcessorP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00321'>PlatformConstruction/walker</a>

Uns64 opObjectParamUns64Value (
    optObjectP   object,
    const char * name,
    Bool*        set
);

/// Return the parent of the given object
/// @return The parent object
/// @param object The current object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00311'>PlatformConstruction/walker</a>

optObjectP opObjectParent (
    optObjectP object
);

/// Return the release status of the given object
/// @return Current release status (used by packaging and documentation
///         tools)
/// @param object The object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optExtensionP
/// - optModuleP
/// - optMMCP
/// - optPeripheralP
/// - optProcessorP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00426'>PlatformConstruction/walker</a>

optReleaseStatus opObjectReleaseStatus (
    optObjectP object
);

/// Return the release status of the given object as a string
/// @return Current release status (used by packaging and documentation
///         tools)
/// @param object The object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optExtensionP
/// - optModuleP
/// - optMMCP
/// - optPeripheralP
/// - optProcessorP

const char * opObjectReleaseStatusString (
    optObjectP object
);

/// Return the root module containing this object
/// @return The root module instance
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP
/// @par Examples:
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2module_2module_8c_source.html#l00059'>SimulationControl/behavioralCcodeInModule</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00038'>SimulationControl/behavioralCcodeInModule</a>

optModuleP opObjectRootModule (
    optObjectP object
);

/// Return true if this object supports save/restore
/// @return true if this model supports save/restore, False if not or if this
///         is not applicable
/// @param object An object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optPeripheralP

Bool opObjectSaveRestoreSupported (
    optObjectP object
);

/// Return the current simulator phase of the platform that contains this
/// object.
/// @return The current phase of the platform
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP

optSimulatorPhase opObjectSimulatorPhase (
    optObjectP object
);

/// Return the current simulator phase of the platform that contains this object
/// as a string
/// @return The current phase of the platform
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP

const char* opObjectSimulatorPhaseString (
    optObjectP object
);

/// Return the type of an OP object. See optStrType
/// @return The enumerated type of the object
/// @param object Any structural object in a platform
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01100'>PlatformConstruction/walker</a>

optStrType opObjectType (
    optObjectP object
);

/// Return the VLNV spec of the given object.
/// @return Pointer to VLNV structure.
/// @param object The object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optMMCP
/// - optExtensionP
/// - optExtElabP
/// - optProcessorP
/// - optPeripheralP
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00454'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00405'>SimulationControl/processorQuery</a>

optVLNVP opObjectVLNV (
    optObjectP object
);

/// Return the visibility of this object. Objects that do not support this
/// feature will be reported as visible
/// @return The visibility (enum)
/// @param object An object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optExtensionP
/// - optMMCP
/// - optModuleP
/// - optPeripheralP
/// - optProcessorP

optVisibility opObjectVisibility (
    optObjectP object
);

/// Return the visibility of this object as a string. Objects that do not
/// support this feature will be reported as visible
/// @return The visibility
/// @param object An object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optExtensionP
/// - optMMCP
/// - optModuleP
/// - optPeripheralP
/// - optProcessorP

const char * opObjectVisibilityString (
    optObjectP object
);

/// Return the maximum number of bytes that one packet can carry in the given
/// packetnet
/// @return Maximum number of bytes or zero
/// @param packetnet The packetnet instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00809'>PlatformConstruction/walker</a>

Uns32 opPacketnetMaxBytes (
    optPacketnetP packetnet
);

/// This function returns the next packetnetMonitor from a packetnet. To get the
/// first object, packetnetMonitor should be null.
/// @param packetnet The parent object.
/// @param packetnetMonitor The iterator. Pass null to get the first object.
/// @return Returns the next packetnetMonitor, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optPacketnetMonitorP obj = 0;
///while((obj = opPacketnetMonitorNext(parent, obj))) {
///    opPrintf("found packetnetMonitor called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01059'>PlatformConstruction/walker</a>
optPacketnetMonitorP opPacketnetMonitorNext (
    optPacketnetP        packetnet,
    optPacketnetMonitorP packetnetMonitor
);

/// Add an instance of a packetnet to a module (with an optional external
/// packetnet port)
/// @return The new packetnet instance
/// @param module   The parent module instance
/// @param name     The name of the new instance. This string is copied so
///                 need not persist.
/// @param portName If specified, this parameter creates a module packetnet
///                 port of this name so that other modules can connect to
///                 this packetnet.
/// @param params   A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./PlatformConstruction_2packetnetHierarchy_2harness_2harness_8c_source.html#l00122'>PlatformConstruction/packetnetHierarchy</a>

optPacketnetP opPacketnetNew (
    optModuleP   module,
    const char * name,
    const char*  portName,
    optParamP    params
);

/// This function returns the next packetnet from a module. To get the first
/// object, packetnet should be null.
/// @param module The parent object.
/// @param packetnet The iterator. Pass null to get the first object.
/// @return Returns the next packetnet, or null when there are no more objects.
/// @par Example:
/// @code
///optPacketnetP obj = 0;
///while((obj = opPacketnetNext(parent, obj))) {
///    opPrintf("found packetnet called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01052'>PlatformConstruction/walker</a>
optPacketnetP opPacketnetNext (
    optModuleP    module,
    optPacketnetP packetnet
);

/// This function returns the next packetnetPortConn from a packetnet. To get
/// the first object, packetnetPortConn should be null.
/// @param packetnet The parent object.
/// @param packetnetPortConn The iterator. Pass null to get the first object.
/// @return Returns the next packetnetPortConn, or null when there are no more
/// objects.
/// @par Example:
/// @code
///optPacketnetPortConnP obj = 0;
///while((obj = opPacketnetPortConnNext(parent, obj))) {
///    opPrintf("found packetnetPortConn called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00130'>PlatformConstruction/walker</a>
optPacketnetPortConnP opPacketnetPortConnNext (
    optPacketnetP         packetnet,
    optPacketnetPortConnP packetnetPortConn
);

/// Return the packetnet connected to this packetnet port connection
/// @return The packetnet instance or null
/// @param packetnetPortConn Current packetnet port connection or null
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00834'>PlatformConstruction/walker</a>

optPacketnetP opPacketnetPortConnPacketnet (
    optPacketnetPortConnP packetnetPortConn
);

/// Return the description of a packetnet port definition
/// @return Short text description
/// @param packetnet A packetnet port handle
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00825'>PlatformConstruction/walker</a>

const char * opPacketnetPortDescription (
    optPacketnetPortP packetnet
);

/// Return the description of a packetnet port definition
/// @return True if this packetnet port must be connected
/// @param packetnet A packetnet port handle
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00827'>PlatformConstruction/walker</a>

Bool opPacketnetPortMustConnect (
    optPacketnetPortP packetnet
);

/// Print connection information about this packetnet
/// @param net The packetnet instance
/// @par Phase:
/// Can be used in any phase

void opPacketnetShow (
    optPacketnetP net
);

/// Write data to a packetnet, which will cause a callbacks in each receiver
/// connected to this packetnet.
/// @return Number of receivers that received the packet
/// @param packetnet The packetnet instance
/// @param data      Data
/// @param bytes     Number of data bytes to send
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2packetnetHierarchy_2harness_2harness_8c_source.html#l00090'>PlatformConstruction/packetnetHierarchy</a>
/// @sa
/// opPacketnetNew
/// opPacketnetWriteMonitorAdd

Uns32 opPacketnetWrite (
    optPacketnetP packetnet,
    void*         data,
    Uns32         bytes
);

/// Add a callback to a packetnet
/// @param packetnet The packetnet instance
/// @param cb        The callback function
/// @param userData  The user data passed to callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2packetnetHierarchy_2harness_2harness_8c_source.html#l00142'>PlatformConstruction/packetnetHierarchy</a>

void opPacketnetWriteMonitorAdd (
    optPacketnetP       packetnet,
    optPacketnetWriteFn cb,
    void*               userData
);

/// Override a boolean parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed
/// @par Examples:
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00055'>SimulationControl/recordReplay</a>
/// - <a href='./SimulationControl_2configureRootModule_2harness_2harness_8c_source.html#l00033'>SimulationControl/configureRootModule</a>
/// - <a href='./SimulationControl_2enablingImperasApplicationIntercepts_2harness_2harness_8c_source.html#l00052'>SimulationControl/enablingImperasApplicationIntercepts</a>
/// - <a href='./SimulationControl_2controllingTracing_2harness_2harness_8c_source.html#l00053'>SimulationControl/controllingTracing</a>

void opParamBoolOverride (
    optObjectP  object,
    const char* name,
    Bool        value
);

/// Create a Bool parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamBoolSet (
    optParamP   list,
    const char* name,
    Bool        value
);

/// Override a double parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed
/// @par Examples:
/// - <a href='./SimulationControl_2configureRootModule_2harness_2harness_8c_source.html#l00045'>SimulationControl/configureRootModule</a>

void opParamDoubleOverride (
    optObjectP  object,
    const char* name,
    double      value
);

/// Create a double precision parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamDoubleSet (
    optParamP   list,
    const char* name,
    double      value
);

/// Override an endian parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  Endian value (enumerated type)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed

void opParamEndianOverride (
    optObjectP  object,
    const char* name,
    optEndian   value
);

/// Create an endian parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value Endian value (enumerated type)
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamEndianSet (
    optParamP   list,
    const char* name,
    optEndian   value
);

/// Override an enum parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed

void opParamEnumOverride (
    optObjectP  object,
    const char* name,
    const char* value
);

/// Create an enum parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamEnumSet (
    optParamP   list,
    const char* name,
    const char* value
);

/// Override an int32 parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed

void opParamInt32Override (
    optObjectP  object,
    const char* name,
    Int32       value
);

/// Create an Int32 parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamInt32Set (
    optParamP   list,
    const char* name,
    Int32       value
);

/// Override an Int64 parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed

void opParamInt64Override (
    optObjectP  object,
    const char* name,
    Int64       value
);

/// Create an Int64 parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamInt64Set (
    optParamP   list,
    const char* name,
    Int64       value
);

/// Create a new parameter list from a parameter array. This function is used by
/// the OP_PARAMS macro
/// @return The head of the parameter list
/// @param array A null terminated parameter array
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamListFromArray (
    optParamArrayP array
);

/// Override a pointer parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Parameter or hierarchical name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must set the parameter before the model constructor is
/// executed

void opParamPtrOverride (
    optObjectP  object,
    const char* name,
    void*       value
);

/// Create an pointer parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamPtrSet (
    optParamP   list,
    const char* name,
    void*       value
);

/// Fetch a parameter value as a pointer
/// @return The value
/// @param param The parameter
/// @par Phase:
/// Can be used in any phase

void* opParamPtrValue (
    optParamP param
);

/// Override a string parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed
/// @par Examples:
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00057'>SimulationControl/recordReplay</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00061'>SimulationControl/startingApplicationDebug</a>

void opParamStringOverride (
    optObjectP  object,
    const char* name,
    const char* value
);

/// Create a string parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleParametersWithHarness_2harness_2harness_8c_source.html#l00058'>SimulationControl/moduleParametersWithHarness</a>
/// - <a href='./SimulationControl_2dynamicHarness_2harness_2harness_8c_source.html#l00152'>SimulationControl/dynamicHarness</a>

optParamP opParamStringSet (
    optParamP   list,
    const char* name,
    const char* value
);

/// Return the parameter type from the actual parameter
/// @return The actual parameter type
/// @param param The actual parameter
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00306'>PlatformConstruction/walker</a>

optParamType opParamType (
    optParamP param
);

/// Return the formal parameter type from the descriptor as a string
/// @return The type
/// @param param The actual parameter
/// @par Phase:
/// Can be used in any phase

const char* opParamTypeString (
    optParamP param
);

/// Override an Uns32 parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed
/// @par Examples:
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00062'>SimulationControl/recordReplay</a>

void opParamUns32Override (
    optObjectP  object,
    const char* name,
    Uns32       value
);

/// Create an Uns32 parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optParamP opParamUns32Set (
    optParamP   list,
    const char* name,
    Uns32       value
);

/// Override an Uns64 parameter on a model relative to the given module, or
/// relative to the top level if the object is null
/// @param object An object or null
/// @param name   Hierarchical parameter name
/// @param value  The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Objects:
/// Can be applied to these objects
/// - optModuleP
/// - optBridgeP
/// - optBusP
/// - optExtensionP
/// - optExtElabP
/// - optFIFOP
/// - optMemoryP
/// - optMMCP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP
/// @par Restrictions:
/// This function must be called before the model constructor is executed
/// @par Examples:
/// - <a href='./SimulationControl_2controllingTracing_2harness_2harness_8c_source.html#l00055'>SimulationControl/controllingTracing</a>

void opParamUns64Override (
    optObjectP  object,
    const char* name,
    Uns64       value
);

/// Create an Uns64 parameter in this list
/// @return The head of the parameter list
/// @param list  The list or null
/// @param name  The new parameter name
/// @param value The value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleParametersWithHarness_2harness_2harness_8c_source.html#l00045'>SimulationControl/moduleParametersWithHarness</a>

optParamP opParamUns64Set (
    optParamP   list,
    const char* name,
    Uns64       value
);

/// Connect a peripheral to a bus
/// @return The new connection
/// @param peripheral The peripheral instance
/// @param bus        The bus instance
/// @param portName   The name of the port on the peripheral
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opPeripheralBusConnectMaster (
    optPeripheralP peripheral,
    optBusP        bus,
    const char *   portName,
    Addr           addrLo,
    Addr           addrHi
);

/// Connect a peripheral to a bus
/// @return The new connection
/// @param peripheral The peripheral instance
/// @param bus        The bus instance
/// @param portName   The name of the port on the peripheral
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opPeripheralBusConnectSlave (
    optPeripheralP peripheral,
    optBusP        bus,
    const char *   portName,
    Addr           addrLo,
    Addr           addrHi
);

/// Connect a peripheral to a bus with a dynamic slave port
/// @return The new connection
/// @param peripheral The peripheral instance
/// @param bus        The bus instance
/// @param portName   The name of the port on the peripheral
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opPeripheralBusConnectSlaveDynamic (
    optPeripheralP peripheral,
    optBusP        bus,
    const char *   portName
);

/// Mark this peripheral to be attached to the debugger
/// @param peripheral Peripheral to be debugged
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opPeripheralDebug (
    optPeripheralP peripheral
);

/// Set the diagnostic level on the given peripheral. Refer to the OVP
/// Peripheral Modeling Guide.
/// @param peripheral Peripheral
/// @param level      The new diagnostic level. An interpretation used by
///                   many peripheral models is to use the least significant
///                   two bits to give 4 levels of detail from non(0) to
///                   maximum detail(3). The simulator interprets the next
///                   two bits in the same way to report activity on the
///                   model's interfaces.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Construction

void opPeripheralDiagnosticLevelSet (
    optPeripheralP peripheral,
    Uns32          level
);

/// Add an instance of an extension to a peripheral
/// @return The new extension instance
/// @param peripheral Parent peripheral
/// @param path       Path to extension file
/// @param name       The name of the new instance. This string is copied so
///                   need not persist.
/// @param params     A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optExtensionP opPeripheralExtensionNew (
    optPeripheralP peripheral,
    const char*    path,
    const char*    name,
    optParamP      params
);

/// Connect a peripheral FIFO port to a FIFO
/// @return The new connection
/// @param peripheral The peripheral instance
/// @param fifo       The FIFO instance
/// @param portName   The name of the port on the peripheral
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optFIFOPortConnP opPeripheralFIFOConnect (
    optPeripheralP peripheral,
    optFIFOP       fifo,
    const char *   portName
);

/// Add an instance of a peripheral to a module
/// @return The new peripheral instance
/// @param module      The parent module instance
/// @param path        Path to peripheral (refer to opVLNVString())
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00123'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00122'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./SimulationControl_2simplePlatformInHarnessUsingOP_2harness_2harness_8c_source.html#l00127'>SimulationControl/simplePlatformInHarnessUsingOP</a>

optPeripheralP opPeripheralNew (
    optModuleP      module,
    const char*     path,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// This function returns the next current from a module. To get the first
/// object, current should be null.
/// @param module The parent object.
/// @param current The iterator. Pass null to get the first object.
/// @return Returns the next current, or null when there are no more objects.
/// @par Example:
/// @code
///optPeripheralP obj = 0;
///while((obj = opPeripheralNext(parent, obj))) {
///    opPrintf("found current called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01087'>PlatformConstruction/walker</a>
optPeripheralP opPeripheralNext (
    optModuleP     module,
    optPeripheralP current
);

/// Connect a Peripheral to a packetnet. (The usual way to connect a packetnet
/// is with the OP_CONNECTIONS macro). Use this function when making a temporary
/// connection in a test-harness.
/// @return The new connection
/// @param peripheral The peripheral instance
/// @param packetnet  The packetnet instance
/// @param portName   The name of the packetnet port on the peripheral
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optPacketnetPortConnP opPeripheralPacketnetConnect (
    optPeripheralP peripheral,
    optPacketnetP  packetnet,
    const char *   portName
);

/// Return the path to the file that implements the peripheral model
/// @return The path to the file that implements the peripheral model
/// @param peripheral The peripheral instance
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00843'>PlatformConstruction/walker</a>

const char * opPeripheralPath (
    optPeripheralP peripheral
);

/// Notify when a serial connection is made
/// @param peripheral Peripheral expected to make a serial connection
/// @param cb         Notifier function
/// @param userData   User data passed to notifier
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opPeripheralSerialNotify (
    optPeripheralP  peripheral,
    optSerialOpenFn cb,
    void*           userData
);

/// Return the reason why the given peripheral stopped
/// @return The reason why this peripheral stopped executing.
/// @param peripheral The peripheral instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// This function should be used only in the callback optSimulatePostPeriphFn

optStopReason opPeripheralStopReason (
    optPeripheralP peripheral
);

/// Send formatted text to the simulator output stream
/// @param fmt Printf format string (see gnu printf for details)
/// @param ... varargs
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00043'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00131'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00070'>SimulationControl/startingApplicationDebug</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00034'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00096'>SimulationControl/processorQuery</a>

void opPrintf (
    const char* fmt,
                ...
) __attribute__(( format (printf, 1,2)));

/// Send formatted text to the simulator instruction trace file, if open
/// @return True if the simulator trace file is open
/// @param fmt Printf format string (see gnu printf for details)
/// @param ... varargs
/// @par Phase:
/// Can be used in any phase

Bool opPrintfTrace (
    const char* fmt,
                ...
) __attribute__(( format (printf, 1,2)));

/// If the subject is a multi-core processor, this function must be applied to
/// the root. Returns true if this processor is an asymmetric multiprocessor,
/// according to the processor information supplied by the model.
/// @return True if this processor (cluster) is an asymmetric multiprocessor,
///         i.e. the components of this processor are not all of the same
///         type.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opProcessorAMP (
    optProcessorP processor
);

/// Return an object for use in OCL
/// @return Pointer to an object as used in oclAppSymbol.h
/// @param processor The processor
/// @par Phase:
/// Can be used in any phase

octASObjP opProcessorASObj (
    optProcessorP processor
);

/// Set a watchpoint to trigger when processor performs a memory access in the
/// given address range. When a watchpoint is triggered, if the notifierCB is
/// specified, it will be called. If it returns True, simulation will continue,
/// otherwise it will stop. If the function is not specified the simulator will
/// stop. The simulator stops by returning to its caller immediately after the
/// access has completed.
/// @return New watchpoint
/// @param processor  The processor instance
/// @param physical   Use physical addresses
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00096'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00106'>DebuggerIntegration/multiProcessor</a>

optWatchpointP opProcessorAccessWatchpointNew (
    optProcessorP                processor,
    Bool                         physical,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// (no longer used)
/// @return Alternative name of this processor or null if not defined.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opProcessorAlternateName (
    optProcessorP processor
);

/// Use the installed readers to load an application via a processor. This route
/// can also set the PC of the processor to the application entry point and can
/// associate the applications symbol tables with the processor to allow
/// symbolic interception of functions, and disassembly of labels.
/// @return The new application object
/// @param processor  The processor instance
/// @param path       The application object file
/// @param controls   Bitmask to control the loader behavior
/// @param loadOffset The offset to be added to program
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00077'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00233'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00270'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2customApplicationLoader_2harness_2harness_8c_source.html#l00051'>SimulationControl/customApplicationLoader</a>

optApplicationP opProcessorApplicationLoad (
    optProcessorP     processor,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset
);

/// Read the specified application file, but instead of loading the code, call
/// the user's callbacks for each region found. This allows the user to use the
/// contents of an object file without re-writing the object loader.
/// @return The new application object
/// @param processor  The processor instance
/// @param path       The application object file
/// @param controls   Bitmask to control the loader behavior
/// @param loadOffset The offset to be added to program
/// @param cbs        Table of functions to be called
/// @param userData   The user data
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

optApplicationP opProcessorApplicationRead (
    optProcessorP     processor,
    const char*       path,
    optLoaderControls controls,
    Addr              loadOffset,
    ordCallbacksP     cbs,
    void*             userData
);

/// Add a mapping from an address to a symbol for the application running on the
/// given processor. This function can be used when the application is not
/// loaded from an ELF file (which contains symbol mappings), or when the
/// application program file has no symbols.
/// @param processor The processor instance
/// @param name      Symbol name
/// @param value     Symbol address value
/// @param size      Symbol address size in bytes
/// @param type      Symbol type. Refer to ord.h
/// @param binding   Symbol binding. Refer to ord.h
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationProgramHexFormatFile_2harness_2harness_8c_source.html#l00113'>SimulationControl/loadingApplicationProgramHexFormatFile</a>
/// @sa
/// opProcessorApplicationLoad

void opProcessorApplicationSymbolAdd (
    optProcessorP    processor,
    const char *     name,
    Addr             value,
    Addr             size,
    ordSymbolType    type,
    ordSymbolBinding binding
);

/// Clear a breakpoint from the given address.
/// @param processor The processor instance
/// @param addr      The bus address
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00068'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00082'>DebuggerIntegration/multiProcessor</a>

void opProcessorBreakpointAddrClear (
    optProcessorP processor,
    Addr          addr
);

/// Set an instruction breakpoint on the given processor. If the processor
/// fetches an instruction from the given address, the simulator will stop
/// immediately BEFORE the instruction is executed. and return to the caller.
/// The optStopReason will be OP_SR_BP_ADDRESS.
/// @param processor The processor instance
/// @param addr      The address
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00056'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00070'>DebuggerIntegration/multiProcessor</a>

void opProcessorBreakpointAddrSet (
    optProcessorP processor,
    Addr          addr
);

/// Clear the ICount breakpoint from the given processor.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opProcessorBreakpointICountClear (
    optProcessorP processor
);

/// Stop this processor after this many more instructions.
/// @param processor The processor instance
/// @param delta     After this many instructions from now
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Restrictions:
/// There is only one active ICount breakpoint on any processor; a second call
/// to this function (before the count is reached) will replace the previous
/// value. When the ICount breakpoint is reached, the breakpoint deletes itself.
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00051'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00109'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00252'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00296'>DebuggerIntegration/multiProcessor</a>

void opProcessorBreakpointICountSet (
    optProcessorP processor,
    Uns64         delta
);

/// Connect a processor bus master port by name (note that the function name
/// does not indicate the type of port)
/// @return The new connection
/// @param processor The processor instance
/// @param bus       The bus instance
/// @param portName  The name of the master port on the processor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @sa
/// opProcessorBusConnectMaster

optBusPortConnP opProcessorBusConnect (
    optProcessorP processor,
    optBusP       bus,
    const char *  portName
);

/// Connect a processor bus master port by name
/// @return The new connection
/// @param processor The processor instance
/// @param bus       The bus instance
/// @param portName  The name of the master port on the processor
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opProcessorBusConnectMaster (
    optProcessorP processor,
    optBusP       bus,
    const char *  portName
);

/// Connect a processor bus slave port by name
/// @return The new connection
/// @param processor The processor instance
/// @param bus       The bus instance
/// @param portName  The name of the port on the processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optBusPortConnP opProcessorBusConnectSlave (
    optProcessorP processor,
    optBusP       bus,
    const char *  portName,
    Addr          addrLo,
    Addr          addrHi
);

/// Return the first child of the given SMP processor or null if there are no
/// children.
/// @return The first child processor or null if there are none
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00400'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00365'>SimulationControl/processorQuery</a>
/// @sa
/// opProcessorParent
/// opProcessorSiblingNext
/// opProcessorSiblingPrevious
/// opProcessorIndex
/// opProcessorIsLeaf

optProcessorP opProcessorChild (
    optProcessorP processor
);

/// Return the total number of instructions and halted instructions executed by
/// the given processor
/// @return Total number of instructions and halted instructions since the
///         beginning of the simulation
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorICount
/// opProcessorTime

Uns64 opProcessorClocks (
    optProcessorP processor
);

/// Return how many more clocks this processor will execute until the given time
/// @return The number of extra clocks
/// @param processor The processor instance
/// @param time      New absolute time
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Uns64 opProcessorClocksUntilTime (
    optProcessorP processor,
    optTime       time
);

/// Issue the callback on all commands attached to this processor (includes
/// those on extensions)
/// @param processor The processor instance
/// @param cb        Command callback
/// @param userData  The user data passed to callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2callingInstalledCommands_2harness_2harness_8c_source.html#l00026'>SimulationControl/callingInstalledCommands</a>

void opProcessorCommandIterAll (
    optProcessorP processor,
    optCommandFn  cb,
    void*         userData
);

/// Return the current processor. This function should only be used from within
/// a callback.
/// @return The current processor context.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optProcessorP opProcessorCurrent (void);

/// Return the exact number of instructions executed by the given processor
/// since the beginning of the simulation.
/// @return Exact number of instructions executed, including those when the
///         simulator requested the processor to execute but it was in an
///         internal halt-state.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorClocks
/// opProcessorTime

Uns64 opProcessorCycleCount (
    optProcessorP processor
);

/// For internal use only. Do not use this function.
/// @return pointer to raw processor data
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void * opProcessorData (
    optProcessorP processor
);

/// Mark this processor to be attached to the debugger
/// @param processor Processor to be debugged
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00072'>SimulationControl/startingApplicationDebug</a>

void opProcessorDebug (
    optProcessorP processor
);

/// Return the VLNV specification of the debugger helper for this processor, if
/// available.
/// @return VLNV of processor debugger helper plugin
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optVLNVP opProcessorDebugHelper (
    optProcessorP processor
);

/// Return the VLNV of the semihost library to be used by default with this
/// processor.
/// @return Pointer to semihost library VLNV structure.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00453'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00408'>SimulationControl/processorQuery</a>

optVLNVP opProcessorDefaultSemihost (
    optProcessorP processor
);

/// Return the cumulative delay for this processor
/// @return cumulative delay for this processor
/// @param processor Processor object.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optTime opProcessorDelay (
    optProcessorP processor
);

/// This function indicates that the current processor should do nothing for a
/// number of clocks corresponding to the given delay. The purpose of this is to
/// enable after-the-event timing emulation.
/// @param processor Processor object.
/// @param time      Relative time.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorSkipCyclesAdd

void opProcessorDelayAdd (
    optProcessorP processor,
    optTime       time
);

/// This function sets an external de-rate factor for a processor (0-100%,
/// default 0%). This enables the simulation environment to indicate that the
/// processor should execute at a reduced percentage of its configured MIPS
/// rate. This is necessary for the platform to be able to simulate the effect
/// of reduced-rate clocking, for example.
/// @param processor Processor object.
/// @param factor    De-rating factor
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opProcessorDerate (
    optProcessorP processor,
    double        factor
);

/// Return a description of this processor
/// @return Single name indicating this processor's function in the model.
///         e.g. TC, VPE, CPU, CMP
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00358'>SimulationControl/processorQuery</a>

const char* opProcessorDescription (
    optProcessorP processor
);

/// Disassemble the instruction at this address, using the given processor
/// model.
/// @return Disassembly string.
/// @param processor The processor instance
/// @param addr      Address
/// @param attrs     How to disassemble
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// This function re-uses the return string each time it is called; the string
/// must be used before the function is called again.
/// @par Examples:
/// - <a href='./SimulationControl_2customProcessorTrace_2harness_2harness_8c_source.html#l00048'>SimulationControl/customProcessorTrace</a>
/// - <a href='./SimulationControl_2processorRegisterAccess_2harness_2harness_8c_source.html#l00061'>SimulationControl/processorRegisterAccess</a>
/// @sa
/// opProcessorPCNext

const char * opProcessorDisassemble (
    optProcessorP  processor,
    Addr           addr,
    optDisassAttrs attrs
);

/// Fills an array with the ELF codes supported by this processor.
/// @return Returns how many different ELF codes are supported by this
///         processor.
/// @param processor  The processor instance
/// @param codes      An array of codes to be filled in by this function
/// @param maxCodes   Size of the array to be filled
/// @param defaultElf This is the default processor for this ELF code (no
///                   longer used).
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00442'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00419'>SimulationControl/processorQuery</a>

Uns32 opProcessorElfCodes (
    optProcessorP processor,
    Uns32*        codes,
    Uns32         maxCodes,
    Bool*         defaultElf
);

/// Return the current endian configuration of the given processor. If the
/// processor can have different code and data endian configurations, then the
/// data argument is used to select which endian is queried.
/// @return Endian supported by this processor.
/// @param processor The processor instance
/// @param data      Return the current data endian if true, the current code
///                  endian if false
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00436'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00411'>SimulationControl/processorQuery</a>

optEndian opProcessorEndian (
    optProcessorP processor,
    Bool          data
);

/// Returns the current processor exception descriptor, or null if the model
/// does not implement exceptions. A processor exception is represented by a
/// pointer (optExceptionP) from which can be return a name, a description and a
/// number. A processor that implements exceptions has a current exception state
/// returned by this function and can be queried for the other exception states.
/// @return Exception description
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00190'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00180'>DebuggerIntegration/modeAndException</a>
/// @sa
/// opExceptionName
/// opExceptionCode
/// opExceptionDescription
/// opProcessorExceptionNext

optExceptionP opProcessorExceptionCurrent (
    optProcessorP processor
);

/// This function returns the next exception from a processor. To get the first
/// object, exception should be null.
/// Use opProcessorExceptionCurrent to find the current exception state of a
/// processor
/// @param processor The parent object.
/// @param exception The iterator. Pass null to get the first object.
/// @return Returns the next exception, or null when there are no more objects.
/// @par Example:
/// @code
///optExceptionP obj = 0;
///while((obj = opProcessorExceptionNext(parent, obj))) {
///    opPrintf("found exception called '%s'\n", opExceptionName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00379'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00181'>SimulationControl/processorQuery</a>
optExceptionP opProcessorExceptionNext (
    optProcessorP processor,
    optExceptionP exception
);

/// Set a watchpoint to trigger when processor performs an exception. When a
/// watchpoint is triggered, if the notifierCB is specified, it will be called.
/// If it returns True, simulation will continue, otherwise it will stop. If the
/// function is not specified the simulator will stop. The simulator stops by
/// returning to its caller immediately after the instruction has completed.
/// @return New watchpoint
/// @param processor  The processor instance
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00125'>DebuggerIntegration/modeAndException</a>

optWatchpointP opProcessorExceptionWatchpointNew (
    optProcessorP                processor,
    void*                        userData,
    optProcWatchpointConditionFn notifierCB
);

/// Terminate execution of the current processor and return immediately from
/// opProcessorSimulate with optStopReason OP_SR_EXIT. If they exists, other
/// processors can continue simulation
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorFinish

void opProcessorExit (
    optProcessorP processor
);

/// Add an instance of an extension to a processor
/// @return The new extension instance
/// @param processor The parent processor instance
/// @param path      Extension master
/// @param name      The name of the new instance. This string is copied so
///                  need not persist.
/// @param params    A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00073'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00073'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./HelloWorld_2usingOP_2platform_2platform_8c_source.html#l00086'>HelloWorld/usingOP</a>
/// - <a href='./SimulationControl_2simplePlatformInHarnessUsingOP_2harness_2harness_8c_source.html#l00077'>SimulationControl/simplePlatformInHarnessUsingOP</a>
/// - <a href='./SimulationControl_2simpleSemihosting_2harness_2harness_8c_source.html#l00035'>SimulationControl/simpleSemihosting</a>

optExtensionP opProcessorExtensionNew (
    optProcessorP processor,
    const char*   path,
    const char*   name,
    optParamP     params
);

/// Connect a processor bus port by name
/// @return The new connection
/// @param processor The processor instance
/// @param fifo      The FIFO instance
/// @param portName  The name of the port on the processor
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optFIFOPortConnP opProcessorFIFOConnect (
    optProcessorP processor,
    optFIFOP      fifo,
    const char *  portName
);

/// Return the family name of this processor.
/// @return Family name of this processor or null if not defined.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00429'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00401'>SimulationControl/processorQuery</a>

const char * opProcessorFamily (
    optProcessorP processor
);

/// Return by reference the fault address of the given processor. Following an
/// exception, when the simulator has returned to the caller, this function
/// finds the address at which the exception occurred. The exception address
/// could be where the processor was executing, or a data value being read or
/// written.
/// @return True if a fault address was found
/// @param processor The processor instance
/// @param address   Pointer to address to be set to the current fault
///                  address.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opProcessorFaultAddress_8c_source.html#l00001'>Simple example</a>

Bool opProcessorFaultAddress (
    optProcessorP processor,
    Addr*         address
);

/// Add a fetch callback to the given address range on a processor. This
/// function should be used as a passive monitor, rather than as part of the
/// platform.
/// @param processor processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00101'>SimulationControl/monitoringAccesses</a>

void opProcessorFetchMonitorAdd (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Remove a fetch callback from the given address range on a processor if it
/// exists
/// @param processor processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opProcessorFetchMonitorDelete (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Terminate execution of the simulation and return immediately from
/// opProcessorSimulate or opRootModuleSimulate with optStopReason OP_SR_FINISH.
/// @param processor The processor instance
/// @param status    Return status
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorExit

void opProcessorFinish (
    optProcessorP processor,
    Int32         status
);

/// Signal that code memory has been changed and that the processor should
/// invalidate cached JIT translations
/// @param processor processor to flush
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opProcessorFlush (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi
);

/// Following this function call, the given processor will not be scheduled to
/// run any instructions until opProcessorUnfreeze is called. If queried, the
/// stop reason will be OP_SR_FREEZE.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorUnfreeze

void opProcessorFreeze (
    optProcessorP processor
);

/// Indicate if this processor is in the frozen state.
/// @return True if this processor is in the frozen state.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opProcessorFrozen (
    optProcessorP processor
);

/// Processor models that have a GDB that works with the model and is shipped
/// with this product, and requires specific flags to be passed to the GDB which
/// is starts, have these flags embedded in the model. This function returns the
/// flags as a string. Processor models that require different flags according
/// to their configuration will return the correct flags via this function.
/// @return GDB Flags.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00422'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00397'>SimulationControl/processorQuery</a>

const char* opProcessorGdbFlags (
    optProcessorP processor
);

/// Processor models that have a GDB that works with the model and is shipped
/// with this product, have the path to the GDB embedded in the model. This
/// function returns the path to this GDB. Processor models that require
/// different GDBs according to their configuration will return the correct GDB
/// via this function.
/// @return Path to GDB.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00420'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00394'>SimulationControl/processorQuery</a>

const char* opProcessorGdbPath (
    optProcessorP processor
);

/// Return the group name of this processor.
/// @return Group name (more significant) of this processor or null if not
///         defined.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00431'>PlatformConstruction/walker</a>

const char * opProcessorGroupH (
    optProcessorP processor
);

/// Return the group name of this processor.
/// @return Group name (less significant) of this processor or null if not
///         defined.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00433'>PlatformConstruction/walker</a>

const char * opProcessorGroupL (
    optProcessorP processor
);

/// Halt execution of the current processor and return immediately from
/// opProcessorSimulate with the optStopReason OP_SR_HALT
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// This function should be called from within a read or write callback

void opProcessorHalt (
    optProcessorP processor
);

/// Return the VLNV specification of the helper for this processor. Refer to
/// Imperas VAP Tools User Guide
/// @return VLNV of processor helper plugin
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00452'>PlatformConstruction/walker</a>

optVLNVP opProcessorHelper (
    optProcessorP processor
);

/// Return the total number of instructions executed by the given processor
/// since the beginning of the simulation.
/// @return Total number of instructions executed, excluding those when the
///         simulator requested the processor to execute but it was in an
///         internal halt-state.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00077'>SimulationControl/processorResetControl</a>
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00090'>SimulationControl/processorExternalInterruptControl</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00274'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00320'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2customProcessorTrace_2harness_2harness_8c_source.html#l00046'>SimulationControl/customProcessorTrace</a>
/// @sa
/// opProcessorClocks
/// opProcessorTime

Uns64 opProcessorICount (
    optProcessorP processor
);

/// Return the index number of the passed SMP processor. Each processor in the
/// cluster is guaranteed a unique index number
/// @return The unique index number.
/// @param processor A processor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorParent
/// opProcessorSiblingNext
/// opProcessorChild
/// opProcessorSiblingPrevious
/// opProcessorIsLeaf

Uns32 opProcessorIndex (
    optProcessorP processor
);

///  Return the instruction attribute object for the instruction at the given
/// simulated address. Data gathered is chosen by the 'select' bit field
/// enumeration.
/// @return The attribute object for the given instruction
/// @param processor The processor instance
/// @param simPC     The address of the instruction
/// @param select    Select which data to gather
/// @param applyDFA   Specifies whether data flow optimization should be
///                  performed before deriving attributes (may result in
///                  elimination of some apparent dependencies)
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

octiaAttrP opProcessorInstructionAttributes (
    optProcessorP processor,
    Addr          simPC,
    Uns32         select,
    Bool          applyDFA
);

/// Return the number of bytes in the instruction at the given address
/// @return Number of bytes
/// @param processor The processor instance
/// @param addr      Address
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Uns32 opProcessorInstructionBytes (
    optProcessorP processor,
    Addr          addr
);

/// Return true if the SMP processor is a leaf. A leaf process can execute code;
/// other processors in a cluster represent containers of shared resources such
/// as leaf processors and caches. Simple processors have a cluster of just one,
/// which will be the root and also reported as a leaf.
/// @return True if is a leaf
/// @param processor The current processor
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00398'>PlatformConstruction/walker</a>
/// @sa
/// opProcessorParent
/// opProcessorSiblingNext
/// opProcessorChild
/// opProcessorSiblingPrevious
/// opProcessorIndex

Bool opProcessorIsLeaf (
    optProcessorP processor
);

/// Call the given callback for the processor instance and each of its
/// descendants
/// @param processor The processor instance
/// @param iterCB    The function to call
/// @param userData  The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opProcessorIterAll_8c_source.html#l00001'>Simple example</a>

void opProcessorIterAll (
    optProcessorP          processor,
    optProcessorIteratorFn iterCB,
    void*                  userData
);

/// Call the given callback for each child of the processor instance. This will
/// report
/// @param processor The processor instance
/// @param iterCB    The function to call
/// @param userData  The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opProcessorIterChildren_8c_source.html#l00001'>Simple example</a>

void opProcessorIterChildren (
    optProcessorP          processor,
    optProcessorIteratorFn iterCB,
    void*                  userData
);

/// Call the given callback for each descendant of the processor instance
/// @param processor The processor instance
/// @param iterCB    The function to call
/// @param userData  The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00173'>SimulationControl/processorQuery</a>

void opProcessorIterDescendants (
    optProcessorP          processor,
    optProcessorIteratorFn iterCB,
    void*                  userData
);

/// Returns true if this processor always requires the use of physical
/// addresses.
/// @return True if physical addresses required (legacy feature).
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opProcessorLoadPhysical (
    optProcessorP processor
);

/// Returns the current processor mode description , or null if the model does
/// not implement modes. A processor mode is represented by a pointer
/// (optExceptionP) from which can be return a name, a description and a number.
/// A processor that implements modes has a current mode returned by this
/// function and can be queried for the other modes.
/// @return Current mode
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00229'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00159'>DebuggerIntegration/modeAndException</a>
/// @sa
/// opModeName
/// opModeCode
/// opModeDescription
/// opProcessorModeNext

optModeP opProcessorModeCurrent (
    optProcessorP processor
);

/// This function returns the next mode from a processor. To get the first
/// object, mode should be null.
/// @param processor The parent object.
/// @param mode The iterator. Pass null to get the first object.
/// @return Returns the next mode, or null when there are no more objects.
/// @par Example:
/// @code
///optModeP obj = 0;
///while((obj = opProcessorModeNext(parent, obj))) {
///    opPrintf("found mode called '%s'\n", opModeName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00363'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00218'>SimulationControl/processorQuery</a>
optModeP opProcessorModeNext (
    optProcessorP processor,
    optModeP      mode
);

/// Set a watchpoint to trigger when processor changes mode. When a watchpoint
/// is triggered, if the notifierCB is specified, it will be called. If it
/// returns True, simulation will continue, otherwise it will stop. If the
/// function is not specified the simulator will stop. The simulator stops by
/// returning to its caller immediately after the instruction has completed.
/// @return New watchpoint
/// @param processor  The processor instance
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00118'>DebuggerIntegration/modeAndException</a>

optWatchpointP opProcessorModeWatchpointNew (
    optProcessorP                processor,
    void*                        userData,
    optProcWatchpointConditionFn notifierCB
);

/// Used to create a new processor instance
/// @return The new processor instance
/// @param module      The parent module instance
/// @param path        This is the path to the dynamic load library (.dll or
///                    .so) implementing the processor model. The file
///                    extension can be ignored. If the path is a directory
///                    rather than a file, the file model.so or model.dll is
///                    assumed. (refer to opVLNVString())
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00494'>SimulationControl/processorQuery</a>
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00067'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00046'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00046'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./HelloWorld_2usingOP_2platform_2platform_8c_source.html#l00073'>HelloWorld/usingOP</a>

optProcessorP opProcessorNew (
    optModuleP      module,
    const char*     path,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// Add an instance of a processor to a module using modelAttrs structure
/// @return The new processor instance
/// @param module      The parent module instance
/// @param iasAttrs    Processor attribute table
/// @param stubs       Processor stub functions table
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optProcessorP opProcessorNewFromAttrs (
    optModuleP      module,
    void *          iasAttrs,
    void *          stubs,
    const char*     name,
    optConnectionsP connections,
    optParamP       params
);

/// Add an instance of a processor to a module with semihosting installed (for
/// ICM compatibility)
/// @return The new processor instance
/// @param module      The parent module instance
/// @param path        Path to processor model
/// @param name        The name of the new instance. This string is copied so
///                    need not persist.
/// @param connections Lists of connections. Refer to the optConnectionsP
///                    structure.
/// @param params      A list of parameters to configure the new instance
/// @param semihost    Path to semihost library
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optProcessorP opProcessorNewWithSemihost (
    optModuleP      module,
    const char*     path,
    const char*     name,
    optConnectionsP connections,
    optParamP       params,
    const char*     semihost
);

/// This function returns the next processor from a module. To get the first
/// object, processor should be null.
/// @param module The parent object.
/// @param processor The iterator. Pass null to get the first object.
/// @return Returns the next processor, or null when there are no more objects.
/// @par Example:
/// @code
///optProcessorP obj = 0;
///while((obj = opProcessorNext(parent, obj))) {
///    opPrintf("found processor called '%s'\n", opObjectName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00070'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2startingApplicationDebug_2harness_2harness_8c_source.html#l00069'>SimulationControl/startingApplicationDebug</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l01094'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00073'>SimulationControl/processorResetControl</a>
/// - <a href='./SimulationControl_2customScheduler_2harness_2harness_8c_source.html#l00065'>SimulationControl/customScheduler</a>
optProcessorP opProcessorNext (
    optModuleP    module,
    optProcessorP processor
);

/// Return the current value of the PC of a processor
/// @return The current PC value.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00283'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00329'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2customProcessorTrace_2harness_2harness_8c_source.html#l00047'>SimulationControl/customProcessorTrace</a>
/// - <a href='./SimulationControl_2processorRegisterAccess_2harness_2harness_8c_source.html#l00054'>SimulationControl/processorRegisterAccess</a>

Addr opProcessorPC (
    optProcessorP processor
);

/// Return the current value of the PC and the delay slot offset. Refer to the
/// VMI processor documentation for a description of the delay slot.
/// @return Current PC value
/// @param processor The processor instance
/// @param delay     Pointer to delay slot offset
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opProcessorPCDS_8c_source.html#l00001'>Simple example</a>

Addr opProcessorPCDS (
    optProcessorP processor,
    Uns8*         delay
);

/// Query if the PC of the given processor is in a delay slot
/// @return True if the PC is in a delay slot
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opProcessorPCInDS (
    optProcessorP processor
);

/// Return the address of the instruction following the instruction at the given
/// address.
/// @return The following instruction address
/// @param processor The processor instance
/// @param pc        The preceding instruction address
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorDisassemble

Addr opProcessorPCNext (
    optProcessorP processor,
    Addr          pc
);

/// Set the current PC of a processor. This is the first address to be executed
/// when simulation proceeds.
/// @param processor The processor instance
/// @param addr      New PC value
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00104'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2loadingApplicationProgramHexFormatFile_2harness_2harness_8c_source.html#l00129'>SimulationControl/loadingApplicationProgramHexFormatFile</a>

void opProcessorPCSet (
    optProcessorP processor,
    Addr          addr
);

/// Return the parent of the given SMP processor or null if there is no parent.
/// @return The SMP parent processor
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorChild
/// opProcessorSiblingPrevious
/// opProcessorIndex
/// opProcessorIsLeaf

optProcessorP opProcessorParent (
    optProcessorP processor
);

/// Returns the path to the file that implements the processor model
/// @return Path to the file that implements the processor model
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00863'>PlatformConstruction/walker</a>

const char* opProcessorPath (
    optProcessorP processor
);

/// Return True if this processor does support QuantumLeap mode
/// @return True if this processor supports QuantumLeap.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00424'>PlatformConstruction/walker</a>

Bool opProcessorQLQualified (
    optProcessorP processor
);

/// Read memory using virtual address in processor context.
/// @return True if successful
/// @param processor   The processor instance
/// @param simAddress  Processor virtual address
/// @param buffer      Pointer to location of data
/// @param objectSize  Number of bytes in one object
/// @param objects     Number of objects to read
/// @param debugAccess True if artifact access
/// @param hostEndian  Specify the endian of buffer
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationProgramHexFormatFile_2harness_2harness_8c_source.html#l00163'>SimulationControl/loadingApplicationProgramHexFormatFile</a>
/// @sa
/// OP_MAX_OBJECT_SIZE

Bool opProcessorRead (
    optProcessorP processor,
    Addr          simAddress,
    void*         buffer,
    Uns32         objectSize,
    Uns32         objects,
    Bool          debugAccess,
    optHostEndian hostEndian
);

/// Abort the current read access.
/// @param processor The processor, or null if no current processor
/// @param addr      The address that failed.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// This function must be called from a memory read callback
/// @par Examples:
/// - <a href='./PlatformConstruction_2usingExternalMemory_2module_2module_8c_source.html#l00050'>PlatformConstruction/usingExternalMemory</a>
/// @sa
/// opBusSlaveNew

void opProcessorReadAbort (
    optProcessorP processor,
    Addr          addr
);

/// Add a read callback to the given address range on a processor. This function
/// should be used as a passive monitor, rather than as part of the platform.
/// @param processor processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00102'>SimulationControl/monitoringAccesses</a>

void opProcessorReadMonitorAdd (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Remove a read callback from the given address range on a processor if it
/// exists
/// @param processor processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opProcessorReadMonitorDelete (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Set a watchpoint to trigger when processor performs a memory read in the
/// given address range. When a watchpoint is triggered, if the notifierCB is
/// specified, it will be called. If it returns True, simulation will continue,
/// otherwise it will stop. If the function is not specified the simulator will
/// stop. The simulator stops by returning to its caller immediately after the
/// access has completed.
/// @return New watchpoint
/// @param processor  The processor instance
/// @param physical   Use physical addresses
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00104'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00114'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00103'>SimulationControl/addingWatchpoints</a>

optWatchpointP opProcessorReadWatchpointNew (
    optProcessorP                processor,
    Bool                         physical,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Find a register from the given processor by index
/// @return The processor register
/// @param processor The processor instance
/// @param index     The required register gdb index
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorRegGroupNext
/// opProcessorRegGroupByName
/// opProcessorRegNext
/// opProcessorRegByName
/// opProcessorRegByUsage

optRegP opProcessorRegByIndex (
    optProcessorP processor,
    Uns32         index
);

/// Finds an instance of a Reg with the given name.
/// @return Returns the optRegP object, or null if not found.
/// @param processor The parent object.
/// @param name The name to find (not hierarchical).
/// @par Example:
/// @code
///const char *name = "u1";
///optRegP obj = opProcessorRegByName(parent, name);
///if(obj) {
///    opPrintf("found Reg called '%s'\n", name);
///}
/// @endcode
optRegP opProcessorRegByName (
    optProcessorP processor,
    const char *  name
);

/// Find a register from a processor by its usage. If more than one register has
/// this usage, the first will be returned.
/// @return The processor register
/// @param processor The processor instance
/// @param usage     The required usage
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00145'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opProcessorRegGroupNext
/// opProcessorRegGroupByName
/// opProcessorRegNext
/// opProcessorRegByIndex
/// opProcessorRegByName

optRegP opProcessorRegByUsage (
    optProcessorP processor,
    optRegUsage   usage
);

/// Print all the registers of the given processor. If the model has its own
/// print routine, this will be used, otherwise it will print the contents of
/// four registers per line.
/// @param processor A processor
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorRegisterAccess_2harness_2harness_8c_source.html#l00070'>SimulationControl/processorRegisterAccess</a>

void opProcessorRegDump (
    optProcessorP processor
);

/// Finds an instance of a RegGroup with the given name.
/// @return Returns the optRegGroupP object, or null if not found.
/// @param processor The parent object.
/// @param name The name to find (not hierarchical).
/// @par Example:
/// @code
///const char *name = "u1";
///optRegGroupP obj = opProcessorRegGroupByName(parent, name);
///if(obj) {
///    opPrintf("found RegGroup called '%s'\n", name);
///}
/// @endcode
optRegGroupP opProcessorRegGroupByName (
    optProcessorP processor,
    const char*   name
);

/// This function returns the next group from a processor. To get the first
/// object, group should be null.
/// @param processor The parent object.
/// @param group The iterator. Pass null to get the first object.
/// @return Returns the next group, or null when there are no more objects.
/// @par Example:
/// @code
///optRegGroupP obj = 0;
///while((obj = opProcessorRegGroupNext(parent, obj))) {
///    opPrintf("found group called '%s'\n", opRegGroupName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00350'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00101'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00163'>DebuggerIntegration/multiProcessor</a>
optRegGroupP opProcessorRegGroupNext (
    optProcessorP processor,
    optRegGroupP  group
);

/// processor register is from a processor extension
/// @return true if from a processor extension
/// @param processor The processor instance
/// @param reg       The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opProcessorRegIsExtension (
    optProcessorP processor,
    optRegP       reg
);

/// This function returns the next reg from a processor. To get the first
/// object, reg should be null.
/// @param processor The parent object.
/// @param reg The iterator. Pass null to get the first object.
/// @return Returns the next reg, or null when there are no more objects.
/// @par Example:
/// @code
///optRegP obj = 0;
///while((obj = opProcessorRegNext(parent, obj))) {
///    opPrintf("found reg called '%s'\n", opRegName(obj));
///}
/// @endcode
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00106'>SimulationControl/processorQuery</a>
/// - <a href='./SimulationControl_2basicProcessorIntrospection_2harness_2harness_8c_source.html#l00043'>SimulationControl/basicProcessorIntrospection</a>
optRegP opProcessorRegNext (
    optProcessorP processor,
    optRegP       reg
);

/// This function returns the next reg from a processor. To get the first
/// object, reg should be null.
/// @param processor The parent object.
/// @param reg The iterator. Pass null to get the first object.
/// @return Returns the next reg, or null when there are no more objects.
/// @par Example:
/// @code
///optRegP obj = 0;
///while((obj = opProcessorRegNextGPacket(parent, obj))) {
///    opPrintf("found reg called '%s'\n", opRegName(obj));
///}
/// @endcode
optRegP opProcessorRegNextGPacket (
    optProcessorP processor,
    optRegP       reg
);

/// This function returns the next reg from a processor. To get the first
/// object, reg should be null.
/// @param processor The parent object.
/// @param reg The iterator. Pass null to get the first object.
/// @return Returns the next reg, or null when there are no more objects.
/// @par Example:
/// @code
///optRegP obj = 0;
///while((obj = opProcessorRegNextPPacket(parent, obj))) {
///    opPrintf("found reg called '%s'\n", opRegName(obj));
///}
/// @endcode
optRegP opProcessorRegNextPPacket (
    optProcessorP processor,
    optRegP       reg
);

/// Read the current value of a processor register
/// @return True if read was successful
/// @param processor The processor instance
/// @param reg       The processor register
/// @param buffer    Pointer to a data buffer that must be large enough to
///                  hold the data.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Notes:
/// Processor registers are stored with the same endian as the host computer,
/// not the target.
/// @par Examples:
/// - <a href='./opProcessorRegRead_8c_source.html#l00001'>Simple example</a>
/// @sa
/// opProcessorRegWrite
/// opProcessorRegReadByName
/// opProcessorRegWriteByName

Bool opProcessorRegRead (
    optProcessorP processor,
    optRegP       reg,
    void *        buffer
);

/// Read a processor register by name
/// @return True if read was successful
/// @param processor The processor instance
/// @param name      The name of the register
/// @param buffer    Pointer to a data buffer that must be large enough to
///                  hold the data.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opProcessorRegReadByName_8c_source.html#l00001'>Simple example</a>
/// @sa
/// opProcessorRegRead
/// opProcessorRegWrite
/// opProcessorRegWriteByName

Bool opProcessorRegReadByName (
    optProcessorP processor,
    const char *  name,
    void *        buffer
);

/// Set a watchpoint on a processor register. The notifier function will be
/// called when the register changes value. When a watchpoint is triggered, if
/// the notifierCB is specified, it will be called. If it returns True,
/// simulation will continue, otherwise it will stop. If the function is not
/// specified the simulator will stop. The simulator stops by returning to its
/// caller immediately after the instruction has completed.
/// @return New watchpoint
/// @param processor  Processor containing the watched register
/// @param reg        The register to be watched
/// @param mode       Mode: see optRegWatchpointMode
/// @param userData   The user data passed to the callback
/// @param notifierCB Notifier function called when the register changes
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00136'>DebuggerIntegration/multiProcessor</a>

optWatchpointP opProcessorRegWatchpointNew (
    optProcessorP                processor,
    optRegP                      reg,
    optRegWatchpointMode         mode,
    void*                        userData,
    optProcWatchpointConditionFn notifierCB
);

/// Write a processor register
/// @return True if write was successful
/// @param processor The processor instance
/// @param reg       The processor register
/// @param buffer    Pointer to a data buffer that was pre-loaded with the
///                  data.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Notes:
/// Processor registers are stored with the same endian as the host computer,
/// not the target.
/// @par Examples:
/// - <a href='./opProcessorRegWrite_8c_source.html#l00001'>Simple example</a>
/// @sa
/// opProcessorRegRead
/// opProcessorRegReadByName
/// opProcessorRegWriteByName

Bool opProcessorRegWrite (
    optProcessorP processor,
    optRegP       reg,
    const void *  buffer
);

/// Write a register
/// @return True if write was successful
/// @param processor The processor instance
/// @param name      The name of the register
/// @param buffer    A buffer containing the data to be written
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorRegRead
/// opProcessorRegWrite
/// opProcessorRegReadByName

Bool opProcessorRegWriteByName (
    optProcessorP processor,
    const char *  name,
    const void *  buffer
);

/// Return the next sibling in this cluster of the given processor
/// @return The next sibling or null if there are no more objects.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00400'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00365'>SimulationControl/processorQuery</a>
/// @sa
/// opProcessorParent
/// opProcessorChild
/// opProcessorSiblingPrevious
/// opProcessorIndex

optProcessorP opProcessorSiblingNext (
    optProcessorP processor
);

/// Return the previous sibling of the given SMP processor
/// @return The previous sibling processor or null if there are no more
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorParent
/// opProcessorSiblingNext
/// opProcessorChild
/// opProcessorIndex
/// opProcessorIsLeaf

optProcessorP opProcessorSiblingPrevious (
    optProcessorP processor
);

/// Simulate a processor for a number of clocks.
/// @return The reason for stopping
/// @param processor The processor instance
/// @param clocks    Maximum number of clocks for which to simulate
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Restrictions:
/// Do not mix the use of opProcessorSimulate (which assumes that the user is
/// managing processor scheduling), with opRootModuleSimulate (which uses the
/// built-in simulator scheduler).
/// @par Examples:
/// - <a href='./SimulationControl_2customScheduler_2harness_2harness_8c_source.html#l00094'>SimulationControl/customScheduler</a>
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00070'>SimulationControl/processorExternalInterruptControl</a>
/// - <a href='./SimulationControl_2dynamicBridge_2harness_2harness_8c_source.html#l00065'>SimulationControl/dynamicBridge</a>
/// - <a href='./SimulationControl_2customProcessorTrace_2harness_2harness_8c_source.html#l00044'>SimulationControl/customProcessorTrace</a>
/// - <a href='./SimulationControl_2callingInstalledCommands_2harness_2harness_8c_source.html#l00049'>SimulationControl/callingInstalledCommands</a>

optStopReason opProcessorSimulate (
    optProcessorP processor,
    Uns64         clocks
);

/// Return the count of skipped cycles for the processor. The type argument
/// indicates whether the count should be committed skipped cycles, pending
/// skipped cycles, or the total of committed and pending skipped cycles.
/// @return Number of skipped cycles
/// @param processor Processor object.
/// @param type      Qualifier. See optCycleSkipType
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorSkipCyclesAdd

Uns64 opProcessorSkipCycles (
    optProcessorP    processor,
    optCycleSkipType type
);

/// This function indicates that the current processor should do nothing for the
/// given number of clocks. The purpose of this is to enable after-the-event
/// timing emulation.
/// @param processor Processor object.
/// @param skipCount Number of cycles to skip.
/// @param defer     If True, this number of nominal cycles is added to the
///                  pending skipped cycles count for the processor. If
///                  False, Processor state is immediately updated to reflect
///                  the skipped cycles count (and any uncommitted pending
///                  skipped cycles).
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorDelayAdd

void opProcessorSkipCyclesAdd (
    optProcessorP processor,
    Uns64         skipCount,
    Bool          defer
);

/// Restore the state of the given processor by calling the callback one or more
/// times. The callback must return the data in the same size chunks as it was
/// saved. The userData passed to the callback should be used to refer to the
/// state of the storage mechanism.
/// @return Success or failure.
/// @param processor The processor instance to restore
/// @param cb        The function used to restore data
/// @param userData  The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00155'>SimulationControl/processorModelSaveRestoreValidation</a>

optSaveRestoreStatus opProcessorStateRestore (
    optProcessorP processor,
    optRestoreFn  cb,
    void *        userData
);

/// Restore the state of the given processor from a file
/// @return Success or failure.
/// @param processor The processor to restore
/// @param file      The file
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opProcessorStateRestoreFile (
    optProcessorP processor,
    const char *  file
);

/// Save the state of the given processor by calling the callback one or more
/// times. The callback decides how the data is stored. The userData passed to
/// the callback should be used to refer to the state of the storage mechanism.
/// @return Success or failure.
/// @param processor The processor to save
/// @param cb        The function used to save data
/// @param userData  The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00141'>SimulationControl/processorModelSaveRestoreValidation</a>

optSaveRestoreStatus opProcessorStateSave (
    optProcessorP processor,
    optSaveFn     cb,
    void *        userData
);

/// Save the state of the given processor to a file
/// @return Success or failure.
/// @param processor The processor instance to save
/// @param file      The file
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opProcessorStateSaveFile (
    optProcessorP processor,
    const char *  file
);

/// Install a callback to be called when a processor stops for an exception.
/// @param processor   The processor instance
/// @param stopHandler The handler function
/// @param userData    User data passed to the handler
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// @par Notes:
/// The stop handler will be called (if simulated exceptions are enabled or not)
/// if any of the following occur: read, write privilege violation, alignment
/// error, read or write abort, arithmetic error.

void opProcessorStopHandlerAdd (
    optProcessorP    processor,
    optStopHandlerFn stopHandler,
    void*            userData
);

/// Remove a callback that was called when a processor stops for an exception.
/// @param processor   The processor instance
/// @param stopHandler The handler function
/// @param userData    User data passed to the handler
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opProcessorStopHandlerDelete (
    optProcessorP    processor,
    optStopHandlerFn stopHandler,
    void*            userData
);

/// Return the reason why the given processor stopped after a previous
/// simulation using opProcessorSimulate() or opRootModuleSimulate(). The stop
/// reason is valid only for leaf level processors or an MT group: processor
/// objects that are containers of independently-executable cores always return
/// a stopReason of OP_SR_SCHED, because each of the sub-cores may have a
/// different stopReason.
/// @return The reason why this processor stopped executing.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Notes:
/// The simulator can stop execution of a particular processor because: - the
/// processor cannot continue for a specific reason. - the processor has
/// executed a quantum's worth of instructions and it's now the turn of another
/// processor. The stop reason will be OP_SR_SCHED (This occurs even when there
/// is only one processor in the design).
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00130'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00078'>SimulationControl/processorResetControl</a>
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00091'>SimulationControl/processorExternalInterruptControl</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00261'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00307'>DebuggerIntegration/multiProcessor</a>

optStopReason opProcessorStopReason (
    optProcessorP processor
);

/// Return the processor local view of time (configured MIPS rate * current
/// clocks)
/// @return Implied processor time
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorICount
/// opProcessorClocks

optTime opProcessorTime (
    optProcessorP processor
);

/// Disable the processor trace buffer.
/// @param processor A processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @sa
/// opProcessorTraceBufferDump

void opProcessorTraceBufferDisable (
    optProcessorP processor
);

/// Print the processor trace buffer contents (if it is enabled).
/// @param processor A processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./opProcessorTraceBufferDump_8c_source.html#l00001'>Simple example</a>

void opProcessorTraceBufferDump (
    optProcessorP processor
);

/// Enable the processor trace buffer. The trace buffer records the last 512
/// instructions executed. Simulation is much slower with trace buffer enabled,
/// but much faster than with tracing enabled.
/// @param processor A processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @sa
/// opProcessorTraceBufferDump

void opProcessorTraceBufferEnable (
    optProcessorP processor
);

/// Trace only instructions with this PC or lower.
/// @param processor A processor instance
/// @param delta     High PC of traced instruction range
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @sa
/// opProcessorTraceLowPCSet

void opProcessorTraceHighPCSet (
    optProcessorP processor,
    Addr          delta
);

/// Trace only instructions with this PC or higher.
/// @param processor A processor instance
/// @param delta     Low PC of traced instruction range
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @sa
/// opProcessorTraceHighPCSet

void opProcessorTraceLowPCSet (
    optProcessorP processor,
    Addr          delta
);

/// Turn off processor tracing after it has executed the given number of
/// instructions.
/// @param processor A processor instance
/// @param delta     The action happens after this many more instructions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @sa
/// opProcessorTraceOnAfter

void opProcessorTraceOffAfter (
    optProcessorP processor,
    Uns64         delta
);

/// Turn on processor tracing after it has executed the given number of
/// instructions.
/// @param processor A processor instance
/// @param delta     The action happens after this many more instructions
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./opProcessorTraceOnAfter_8c_source.html#l00001'>Simple example</a>
/// @sa
/// opProcessorTraceOffAfter

void opProcessorTraceOnAfter (
    optProcessorP processor,
    Uns64         delta
);

/// Following this function call, the given processor will be scheduled
/// normally. If as a result of being in the frozen state, this processor has
/// executed fewer instructions than other processors, it will be scheduled to
/// run until it has caught up, thus minimizing any disturbance caused by the
/// use of opProcessorFreeze.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @sa
/// opProcessorFreeze

void opProcessorUnfreeze (
    optProcessorP processor
);

/// Return the variant of the given processor .
/// @return Variant name of this processor or null if the variant is not
///         defined.
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opProcessorVariant (
    optProcessorP processor
);

/// Write memory using virtual address in processor context.
/// @return True if successful
/// @param processor   The processor instance
/// @param simAddress  Processor virtual address
/// @param buffer      Pointer to location of data
/// @param objectSize  Number of bytes in one object
/// @param objects     Number of objects to write
/// @param debugAccess True if artifact access
/// @param hostEndian  Specify the endian of buffer
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2loadingApplicationProgramHexFormatFile_2harness_2harness_8c_source.html#l00148'>SimulationControl/loadingApplicationProgramHexFormatFile</a>
/// @sa
/// OP_MAX_OBJECT_SIZE

Bool opProcessorWrite (
    optProcessorP processor,
    Addr          simAddress,
    const void*   buffer,
    Uns32         objectSize,
    Uns32         objects,
    Bool          debugAccess,
    optHostEndian hostEndian
);

/// Abort the current write access
/// @param processor The processor, or null if no current processor
/// @param addr      The address that failed.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// This function must be called from a memory write callback
/// @par Examples:
/// - <a href='./PlatformConstruction_2usingExternalMemory_2module_2module_8c_source.html#l00055'>PlatformConstruction/usingExternalMemory</a>
/// @sa
/// opBusSlaveNew

void opProcessorWriteAbort (
    optProcessorP processor,
    Addr          addr
);

/// Add a write callback to the given address range on a processor. This
/// function should be used as a passive monitor, rather than as part of the
/// platform.
/// @param processor processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2monitoringAccesses_2harness_2harness_8c_source.html#l00103'>SimulationControl/monitoringAccesses</a>

void opProcessorWriteMonitorAdd (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Remove a write callback from the given address range on a processor if it
/// exists
/// @param processor processor
/// @param addrLo    The lower address limit
/// @param addrHi    The upper address limit
/// @param rcb       Callback
/// @param userData  The user data returned in the callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opProcessorWriteMonitorDelete (
    optProcessorP processor,
    Addr          addrLo,
    Addr          addrHi,
    optMonitorFn  rcb,
    void*         userData
);

/// Set a watchpoint to trigger when processor performs a memory write in the
/// given address range. When a watchpoint is triggered, if the notifierCB is
/// specified, it will be called. If it returns True, simulation will continue,
/// otherwise it will stop. If the function is not specified the simulator will
/// stop. The simulator stops by returning to its caller immediately after the
/// access has completed.
/// @return New watchpoint
/// @param processor  The processor instance
/// @param physical   Use physical addresses
/// @param addrLo     The lower address limit
/// @param addrHi     The upper address limit
/// @param userData   Pointer available in the watchpoint
/// @param notifierCB Notifier function
/// @par Phase:
/// Can be used in these phases:
/// - Simulation
/// - Pre-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00111'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00122'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00111'>SimulationControl/addingWatchpoints</a>

optWatchpointP opProcessorWriteWatchpointNew (
    optProcessorP                processor,
    Bool                         physical,
    Addr                         addrLo,
    Addr                         addrHi,
    void*                        userData,
    optAddrWatchpointConditionFn notifierCB
);

/// Suspend execution of the current processor and return immediately from
/// opProcessorSimulate with optStopReason OP_SR_YIELD
/// @param processor The processor instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// This function should be called from within a read or write callback
/// @par Examples:
/// - <a href='./SimulationControl_2interruptSimulation_2module_2module_8c_source.html#l00044'>SimulationControl/interruptSimulation</a>

void opProcessorYield (
    optProcessorP processor
);

/// (for internal use only)
/// @param name (for internal use only)
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opProductSet (
    const char* name
);

/// Return the access mode enumeration of a processor register
/// @return Access mode of the processor register
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optRegAccess opRegAccessEnum (
    optRegP reg
);

/// Return the access mode of a processor register as a string
/// @return Return a string describing the access mode of a processor
///         register
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

const char * opRegAccessString (
    optRegP reg
);

/// Return the number of bits in a processor register
/// @return Bit-width of the processor register
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00339'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00116'>SimulationControl/processorQuery</a>
/// - <a href='./SimulationControl_2basicProcessorIntrospection_2harness_2harness_8c_source.html#l00045'>SimulationControl/basicProcessorIntrospection</a>

Uns32 opRegBits (
    optRegP reg
);

/// Convert from instruction attributes register object to OP register object.
/// @return Register object
/// @param regInfo Instruction attributes register object
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optRegP opRegConvert (
    octiaRegInfoP regInfo
);

/// Return the description of the processor register (from the model)
/// @return Description of the processor register
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00343'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00115'>SimulationControl/processorQuery</a>

const char * opRegDescription (
    optRegP reg
);

/// Return the register group that contains this processor register
/// @return Processor register group
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optRegGroupP opRegGroup (
    optRegP reg
);

/// Get name of a processor register group
/// @return The name of the register group
/// @param group Processor register group
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00352'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00135'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00165'>DebuggerIntegration/multiProcessor</a>

const char * opRegGroupName (
    optRegGroupP group
);

/// Return the next processor register in the given processor register group
/// @return The next processor register in the group or null
/// @param processor The processor instance
/// @param group     Processor register group
/// @param reg       The current processor register or null to get the first
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00335'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00139'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00169'>DebuggerIntegration/multiProcessor</a>

optRegP opRegGroupRegNext (
    optProcessorP processor,
    optRegGroupP  group,
    optRegP       reg
);

/// Return the unique index number of the processor register
/// @return The unique index number
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Notes:
/// All registers should have an index number. This number generally follows the
/// numbers used by GDB. If the register is not understood by GDB, then number
/// should be larger than the number of the largest known register.

Uns32 opRegIndex (
    optRegP reg
);

/// processor register is an alias of another
/// @return true if a register alias
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Bool opRegIsAlias (
    optRegP reg
);

/// Return name of a processor register
/// @return The name of the register
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00337'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00114'>SimulationControl/processorQuery</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00170'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2basicProcessorIntrospection_2harness_2harness_8c_source.html#l00044'>SimulationControl/basicProcessorIntrospection</a>

const char * opRegName (
    optRegP reg
);

/// Return true if this processor register is read-only
/// @return True if this processor register is read-only
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00121'>SimulationControl/processorQuery</a>

Bool opRegReadOnly (
    optRegP reg
);

/// Return the usage enumeration of a processor register
/// @return Enumerated type describing the usage of the processor register
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00118'>SimulationControl/processorQuery</a>
/// - <a href='./SimulationControl_2basicProcessorIntrospection_2harness_2harness_8c_source.html#l00049'>SimulationControl/basicProcessorIntrospection</a>

optRegUsage opRegUsageEnum (
    optRegP reg
);

/// Return the usage of a processor register as a string
/// @return A string describing how a processor register is used.
/// @param reg The processor register
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00341'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00119'>SimulationControl/processorQuery</a>
/// - <a href='./SimulationControl_2basicProcessorIntrospection_2harness_2harness_8c_source.html#l00050'>SimulationControl/basicProcessorIntrospection</a>

const char * opRegUsageString (
    optRegP reg
);

/// OP messages with Error status add to the simulator's total error count. A
/// non-zero error count prevents the simulator from moving from one phase to
/// the next e.g. an error during construction prevents simulation. Using this
/// function to reset the error count to zero will allow the simulator to
/// continue. Use with care; the simulation might continue with a potentially
/// fatal error.
/// @return The current error count prior to this call
/// @param count The required error count
/// @par Phase:
/// Can be used in any phase
/// @sa
/// opErrors

Uns32 opResetErrors (
    Uns32 count
);

/// Return the dummy root module instance
/// @return The dummy root module
/// @par Phase:
/// Can be used in any phase

optModuleP opRoot (void);

/// Delete a root module and all its children
/// @param mi Root module instance
/// @par Phase:
/// Can be used in any phase

void opRootModuleDelete (
    optModuleP mi
);

/// Return the simulation time slice size (used by opRootModuleSimulate). Note
/// that this function cannot give a correct value until all models have been
/// elaborated.
/// @return The new time slice..
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation

optTime opRootModuleGetSimulationTimeSlice (
    optModuleP module
);

/// Create a root module instance. Use this when constructing a test harness
/// @return The new root module instance
/// @param attrs  Attribute table. The attribute table is used to install
///               callbacks for each phase.
/// @param name   The name of the root module (optional). The string is
///               copied so need not persist.
/// @param params List of parameters to the new instance. These will be
///               simulation control parameters. See parameter definitions
///               beginning 'OP_FP_'
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00037'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00093'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00065'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00069'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00101'>PlatformConstruction/staticBridgeHierarchy</a>

optModuleP opRootModuleNew (
    optModuleAttrP attrs,
    const char*    name,
    optParamP      params
);

/// This function can be called on a root module before opRootModuleSimulate. It
/// performs all actions after elaboration but before simulation.
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Notes:
/// This function is not required in normal use; use opRootModuleSimulate.
/// @par Notes:
/// When called the first time, this function will call the post-elaborate
/// callbacks. When called again it has no effect.
/// @sa
/// opRootModulePreSimulate
/// opRootModulePostSimulate
/// opRootModuleSimulate

void opRootModulePostElaborate (
    optModuleP module
);

/// This function can be called on a root module before opSessionTerminate.
/// Performs end-of-simulation actions without destroying the platform.
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// - Report
/// @par Notes:
/// This function is not required in normal use; use opRootModuleSimulate.
/// @sa
/// opRootModulePreSimulate
/// opRootModuleSimulate
/// opRootModulePostElaborate

void opRootModulePostSimulate (
    optModuleP module
);

/// This function can be called on a root module before opRootModuleSimulate. It
/// runs the start-of-simulation but returns before running any application
/// processors.
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Notes:
/// This function is not required in normal use; use opRootModuleSimulate.
/// @par Notes:
/// When called the first time, this function will call the post-elaborate
/// callbacks, then the pre-simulate callbacks in all sub-modules. When called
/// again it has no effect.
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00040'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00108'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00100'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00069'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00046'>SimulationControl/processorResetControl</a>
/// @sa
/// opRootModulePostSimulate
/// opRootModuleSimulate
/// opRootModulePostElaborate

void opRootModulePreSimulate (
    optModuleP module
);

/// Set the stop time (for opRootModuleSimulate). The call takes effect at the
/// end of the current time slice. When this time expires the simulator will
/// return control to the debugger, if attached.
/// @return True if successful.
/// @param module      The root module instance
/// @param newStopTime The new absolute stop time in seconds.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

Bool opRootModuleSetDebugStopTime (
    optModuleP module,
    optTime    newStopTime
);

/// Set a seed for randomizing the order in which processors are processed a
/// time slice. The default is no randomization (seed=0).
/// @param module   The parent module instance
/// @param lfsrSeed New seed.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

void opRootModuleSetSimulationRandomSeed (
    optModuleP module,
    Uns32      lfsrSeed
);

/// Set the simulation stop time (for opRootModuleSimulate). This takes effect
/// at the end of any current time slice. opRootModuleSimulate will return when
/// this time is reached
/// @return True if successful.
/// @param module      The root module instance
/// @param newStopTime The new absolute stop time in seconds.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00058'>SimulationControl/processorResetControl</a>
/// - <a href='./SimulationControl_2behavioralCcodeInModule_2harness_2harness_8c_source.html#l00077'>SimulationControl/behavioralCcodeInModule</a>

Bool opRootModuleSetSimulationStopTime (
    optModuleP module,
    optTime    newStopTime
);

/// Set the simulation time precision - all event times are rounded to this.
/// @return True if successful.
/// @param module    The parent module instance
/// @param precision The new time precision in seconds.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

Bool opRootModuleSetSimulationTimePrecision (
    optModuleP module,
    optTime    precision
);

/// Set the simulation time slice size (used by opRootModuleSimulate). The call
/// takes effect at the end of the current time slice.
/// @return True if successful.
/// @param module       The root module instance
/// @param newSliceSize The new time slice duration in seconds.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

Bool opRootModuleSetSimulationTimeSlice (
    optModuleP module,
    optTime    newSliceSize
);

/// When running in wallclock mode (wallclock specified), this gives the maximum
/// multiple of real time at which the simulation should run. The default is
/// 1.0, implying no faster than real time. An value of 2.0 implies no faster
/// than twice real time; a value of 0.5 implies no faster than half realtime
/// @return Returns the new factor, or zero if it could not be set
/// @param module The parent module instance
/// @param factor Wallclock factor to apply.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation

double opRootModuleSetWallClockFactor (
    optModuleP module,
    double     factor
);

/// Simulate a platform using the simulator's built-in scheduler.
/// @return The processor that was running when the simulation stopped
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// - Pre-simulation
/// - Simulation
/// @par Notes:
/// When called the first time, this function will call the post-elaborate
/// callbacks, then the pre-simulate callbacks in all sub-modules. Every time it
/// is called (until simulation is finished) it will call the simulate callbacks
/// then begin processor simulation.
/// @par Restrictions:
/// Do not mix the use of opRootModuleSimulate (which uses the built-in
/// simulator scheduler), with opProcessorSimulate (which assumes that the user
/// is managing processor scheduling). If using this function, do not use
/// opRootModuleTimeAdvance.
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00047'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00127'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00149'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00072'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00102'>PlatformConstruction/staticBridgeHierarchy</a>

optProcessorP opRootModuleSimulate (
    optModuleP module
);

/// Restore the state of the given module and its hierarchy by calling the given
/// callback one or more times
/// @return Success or failure.
/// @param module   The root module to restore
/// @param cb       The function used to restore data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opRootModuleStateRestore (
    optModuleP   module,
    optRestoreFn cb,
    void *       userData
);

/// Restore the state of the given module and its hierarchy from a file
/// @return Success or failure.
/// @param module The root module to restore
/// @param file   The file
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00044'>SimulationControl/moduleSaveRestore</a>

optSaveRestoreStatus opRootModuleStateRestoreFile (
    optModuleP   module,
    const char * file
);

/// Save the state of the given module and its hierarchy by calling the given
/// callback one or more times
/// @return Success or failure.
/// @param module   The root module to save
/// @param cb       The function used to save data
/// @param userData The user data to be passed back to the callback
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSaveRestoreStatus opRootModuleStateSave (
    optModuleP module,
    optSaveFn  cb,
    void *     userData
);

/// Save the state of the given module and its hierarchy to a file
/// @return Success or failure.
/// @param module The root module to save
/// @param file   The file
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00055'>SimulationControl/moduleSaveRestore</a>

optSaveRestoreStatus opRootModuleStateSaveFile (
    optModuleP   module,
    const char * file
);

/// Return the reason why simulation stopped after a previous call to
/// opProcessorSimulate() or opRootModuleSimulate().
/// @return The reason for stopping
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2interruptSimulation_2harness_2harness_8c_source.html#l00137'>SimulationControl/interruptSimulation</a>

optStopReason opRootModuleStopReason (
    optModuleP module
);

/// Move time forward for this platform, processing any pending events due in
/// the period since the last call to this function. Pending events include
/// delays scheduled in peripheral models, time-triggered callbacks in OP
/// platform code, finish-time
/// @return True if successful
/// @param module       A root module instance
/// @param absoluteTime The new absolute time in seconds
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// @par Restrictions:
/// Use this function only if writing a custom scheduler in which case it should
/// be used in conjunction with opProcessorSimulate. Do NOT use in conjunction
/// with opRootModuleSimulate.
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00070'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2customScheduler_2harness_2harness_8c_source.html#l00086'>SimulationControl/customScheduler</a>

Bool opRootModuleTimeAdvance (
    optModuleP module,
    optTime    absoluteTime
);

/// Returns the next triggered watchpoint.
/// @return pointer to the triggered watchpoint
/// @param module The root module instance
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Restrictions:
/// Calling this function removes that watchpoint from the list, so the
/// watchpoint must be queried before this function is called again.
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00148'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00182'>DebuggerIntegration/multiProcessor</a>

optWatchpointP opRootModuleWatchpointNext (
    optModuleP module
);

/// Add to the list of functions to be called when opSessionExit is called.
/// @param fn Function to be called
/// @par Phase:
/// Can be used in any phase

void opSessionAtExit (
    optExitFn fn
);

///  Return the date that product was built
/// @return The product date as a constant string. e.g. 1 Apr 2001
/// @param english It true, returns human readable date. If false, returns
///                yyyymmdd number
/// @par Phase:
/// Can be used in these phases:
/// - Construction

const char * opSessionBuildDate (
    Bool english
);

/// Remove the redirection
/// @param redir Redirection object
/// @par Phase:
/// Can be used in any phase
/// @sa
/// opSessionTextRedirect

void opSessionCancelTextRedirect (
    optRedirectP redir
);

/// Install callbacks for a debugger integration. The callbacks are passed in
/// the notifiers structure. Each callback passes control to the debugger. The
/// debugger code must then take appropriate action. In the callbacks, the
/// simulator is stopped and stable. It is therefore safe to examine memory and
/// processors, add or remove breakpoints, watchpoints etc. This function can be
/// called before the root module is created - pass null to the root parameter.
/// @param root      The root module instance
/// @param notifiers Callback structure
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Although the simulator can have more than one root module in a session, only
/// one root module can be connected to a debugger. This function must be called
/// after the root module is constructed but before its contents are added.
/// @sa
/// optDebuggerNotifiers

void opSessionDebuggerNotifiersAdd (
    optModuleP            root,
    optDebuggerNotifiersP notifiers
);

/// Set callbacks to be called when objects are destroyed
/// @param callbacks The functions to be called
/// @param userData  User data to be passed to the callbacks
/// @par Phase:
/// Can be used in any phase

void opSessionDestFnSet (
    optDestCallbacksP callbacks,
    void *            userData
);

/// Use this to exit the program instead of exit()
/// @param returnCode The program return code
/// @par Phase:
/// Can be used in any phase
/// @par Examples:
/// - <a href='./SimulationControl_2dynamicHarness_2harness_2harness_8c_source.html#l00065'>SimulationControl/dynamicHarness</a>

void opSessionExit (
    Uns32 returnCode
);

/// (for internal use only)
/// @param module   (for internal use only)
/// @param features (for internal use only)
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opSessionFeaturesSet (
    optModuleP module,
    Uns64      features
);

/// Start a session. Each session is started with opSessionInit() and finished
/// with opSessionTerminate(). This sequence can be repeated. Finally call
/// opSessionExit() to exit the process.
/// @return If the environment variable IMPERAS_SESSION_ERROR_RETURN=1 :
///         Returns OP_SESSION_OK if successful or an error code if not. If
///         IMPERAS_SESSION_ERROR_RETURN=0 or unset : Does not return;
///         session will finish.
/// @param version API Version string (must be the macro OP_VERSION)
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Each call of opSessionInit() should be matched with opSessionTerminate().
/// opSessionExit() should be called to exit the process.
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00030'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00090'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00047'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00049'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00096'>PlatformConstruction/staticBridgeHierarchy</a>
/// @sa
/// opSessionTerminate
/// opSessionExit

optSessionStatus opSessionInit (
    const char* version
);

/// Do not use
/// @return Do not use
/// @param version     Do not use
/// @param personality Do not use
/// @param vfs         Do not use
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optSessionStatus opSessionInit2 (
    const char *    version,
    optPersonalityP personality,
    optVFSP         vfs
);

/// Start a session and set the personality, ignoring the IMPERAS_PERSONALITY
/// environment variable. Use this instead of opSessionInit if you wish to avoid
/// using the environment variable.
/// @return If the environment variable IMPERAS_SESSION_ERROR_RETURN=1 :
///         Returns OP_SESSION_OK if successful or an error code if not. If
///         IMPERAS_SESSION_ERROR_RETURN=0 or unset : Does not return;
///         session will finish.
/// @param version         API Version string (must be the macro OP_VERSION)
/// @param personalityName The personality name. Imperas will have told you
///                        which product personality to use.
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optSessionStatus opSessionInit3 (
    const char * version,
    const char * personalityName
);

///  Return the product name
/// @return The product name as a constant string. e.g. OVPsim
/// @par Phase:
/// Can be used in these phases:
/// - Construction

const char * opSessionProductName (void);

///  Return the product version
/// @return The product version as a constant string. e.g. 20160323.0 or
///         Eng.20160323.3
/// @par Phase:
/// Can be used in these phases:
/// - Construction

const char * opSessionProductVersion (void);

/// Ends the session. Used to free simulator resources and release licenses.
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2harness_2harness_8c_source.html#l00060'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00178'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2loadingApplicationPrograms_2harness_2harness_8c_source.html#l00151'>SimulationControl/loadingApplicationPrograms</a>
/// - <a href='./SimulationControl_2recordReplay_2harness_2harness_8c_source.html#l00074'>SimulationControl/recordReplay</a>
/// - <a href='./PlatformConstruction_2staticBridgeHierarchy_2harness_2harness_8c_source.html#l00103'>PlatformConstruction/staticBridgeHierarchy</a>
/// @sa
/// opSessionInit
/// opSessionExit

void opSessionTerminate (void);

/// Direct all text output generated by the simulator to these callbacks,
/// preventing it going to the standard output
/// @return Redirection object used to cancel the redirection
/// @param outputcb The text output function
/// @param quitcb   The function called before simulator exits (use this to
///                 flush your text)
/// @param userData The user data to be passed back to the callbacks
/// @par Phase:
/// Can be used in any phase
/// @sa
/// opSessionCancelTextRedirect

optRedirectP opSessionTextRedirect (
    optTextOutputFn outputcb,
    optQuitFn       quitcb,
    void*           userData
);

/// Remove an existing shared data object
/// @param mi      The module instance
/// @param handle  Handle to existing data
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Post-simulation
/// - Report
/// - Destruction

void opSharedDataDelete (
    optModuleP           mi,
    optSharedDataHandleP handle 
);

/// Return an existing shared data object
/// @return Existing share data handle
/// @param mi      The module instance
/// @param version Version string
/// @param key     Hierarchical key name
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSharedDataHandleP opSharedDataFind (
    optModuleP  mi,
    const char* version,
    const char* key
);

/// Return a new or existing shared data object
/// @return Existing share data handle
/// @param mi      The module instance
/// @param version Version string
/// @param key     Hierarchical key name
/// @param data    Pointer to data to be shared
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

optSharedDataHandleP opSharedDataFindAdd (
    optModuleP  mi,
    const char* version,
    const char* key,
    void*       data
);

/// Install a callback on a shared data object
/// @param mi         The module instance
/// @param handle     Handle to existing data
/// @param listenerCB Listener
/// @param object     Pointer to data to be shared
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opSharedDataListenerRegister (
    optModuleP              mi,
    optSharedDataHandleP    handle ,
    optSharedDataListenerFn listenerCB,
    void*                   object
);

/// Uninstall a callback on a shared data object
/// @param mi         The module instance
/// @param handle     Handle to existing data
/// @param listenerCB Listener
/// @param object     Pointer to data to be shared
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// - Report

void opSharedDataListenerUnregister (
    optModuleP              mi,
    optSharedDataHandleP    handle ,
    optSharedDataListenerFn listenerCB,
    void*                   object
);

/// Trigger any installed listeners
/// @return Returns the status written by a listener
/// @param handle   Handle to existing data
/// @param id       Number passed to the listeners
/// @param userData Pointer passed to listeners
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

Int32 opSharedDataListenersWrite (
    optSharedDataHandleP handle ,
    Int32                id,
    void*                userData
);

/// Get data from an existing shared object
/// @return Data from an existing shared object
/// @param handle  Handle to existing data
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void* opSharedDataValueGet (
    optSharedDataHandleP handle 
);

/// Remove an existing shared object
/// @param handle  Handle to existing data
/// @param data    Pointer to data to be shared
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation

void opSharedDataValueSet (
    optSharedDataHandleP handle ,
    void*                data
);

/// Create a temporary formatted string. Refer to GNU documentation for printf
/// @return A temporary string containing the formatted text
/// @param fmt format string
/// @param ... varargs
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Note that opSprintf allocates a limited number of buffers, so do not rely on
/// the data persisting beyond the next use of this function. Therefore the
/// string should be immediately passed to the construction function. (Note that
/// construction functions keep a copy of their string arguments).
/// @par Examples:
/// - <a href='./opSprintf_8c_source.html#l00001'>Simple example</a>

const char* opSprintf (
    const char * fmt,
                 ...
) __attribute__(( format (printf, 1,2)));

/// Restore one key/value item using the currently active restore method.
/// @return Success or failure
/// @param context Pointer to anonymous context that was passed to the
///                restore function
/// @param name    The item name
/// @param bytes   The number of bytes to restore
/// @param data    The data bytes to restore
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00042'>SimulationControl/moduleSaveRestore</a>

optSaveRestoreStatus opStateItemRestore (
    optRestoreContextP context,
    const char *       name,
    Uns32              bytes,
    void *             data
);

/// Save one key/value item using the currently active save method.
/// @return Success or failure
/// @param context Pointer to anonymous context that was passed to the save
///                function
/// @param name    The item name
/// @param bytes   The number of bytes to save
/// @param data    The data bytes to save
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00037'>SimulationControl/moduleSaveRestore</a>

optSaveRestoreStatus opStateItemSave (
    optSaveContextP context,
    const char *    name,
    Uns32           bytes,
    void *          data
);

/// Convert a stop reason code to a string
/// @return The stop reason as a string
/// @param stopReason The stop reason as an enumerated type.
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./SimulationControl_2processorModelSaveRestoreValidation_2harness_2harness_8c_source.html#l00131'>SimulationControl/processorModelSaveRestoreValidation</a>
/// - <a href='./SimulationControl_2processorResetControl_2harness_2harness_8c_source.html#l00078'>SimulationControl/processorResetControl</a>
/// - <a href='./SimulationControl_2customScheduler_2harness_2harness_8c_source.html#l00100'>SimulationControl/customScheduler</a>
/// - <a href='./SimulationControl_2processorExternalInterruptControl_2harness_2harness_8c_source.html#l00091'>SimulationControl/processorExternalInterruptControl</a>
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00303'>DebuggerIntegration/modeAndException</a>
/// @sa
/// opProcessorStopReason

const char * opStopReasonString (
    optStopReason stopReason
);

/// For internal use only. Do not use this function.
/// @param ident A short, easily searched code to identify this message
/// @param fmt   Printf format string (see gnu printf for details)
/// @param ap    Varargs list
/// @par Phase:
/// Can be used in any phase

void opVAbort (
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// VLNV Iterator function. Calls the given function on all model files that
/// match the given VLNV and model specification.
/// @param vlnvroot Path (or semicolon separated list of paths) to root of
///                 the directory(s) to search. If null, the environment
///                 variable IMPERAS_VLNV is used
/// @param vendor   Vendor directory e.g. yourcompany.com. This can be null
///                 or include glob characters
/// @param library  Library directory e.g. processor This can be null or
///                 include glob characters
/// @param name     The name directory e.g. risc32 This can be null or
///                 include glob characters
/// @param version  Version directory e.g. 1.0 This can be null or include
///                 glob characters
/// @param type     Type of model file to be found
/// @param cb       The callback
/// @param userData The user data passed to callback
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opVLNVIter (
    const char*  vlnvroot,
    const char*  vendor,
    const char*  library,
    const char*  name,
    const char*  version,
    optModelType type,
    optFileFn    cb,
    void*        userData
);

/// Return the 'library' part of the VLNV
/// @return Pointer to text.
/// @param vlnv A VLNV object
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00412'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00381'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectVLNV

const char * opVLNVLibrary (
    optVLNVP vlnv
);

/// Return the 'name' part of the VLNV
/// @return Pointer to text.
/// @param vlnv A VLNV object
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00413'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00382'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectVLNV

const char * opVLNVName (
    optVLNVP vlnv
);

/// Internal function to create a temporary VLNV object
/// @return New VLNV structure
/// @param vendor  Vendor directory e.g. yourcompany.com
/// @param library Library directory e.g. processor
/// @param name    The name directory e.g. risc32.
/// @param version Version directory e.g. 1.0
/// @par Phase:
/// Can be used in these phases:
/// - Construction

optVLNVP opVLNVNew (
    const char* vendor,
    const char* library,
    const char* name,
    const char* version
);

/// Internal function to destroy a temporary VLNV object
/// @param old structure to be destroyed
/// @par Phase:
/// Can be used in these phases:
/// - Construction

void opVLNVOld (
    optVLNVP old
);

/// Synthesize a VLNV path string given the vendor, library, name and version of
/// the library object you wish to load, and see if it exists. If models are
/// stored according to Imperas guidelines, this should successfully locate any
/// model. If all arguments are plain strings, constructs a path such as
/// 'vlnvroot/vendor/library/name/version/objtype', otherwise the following
/// rules are used: If vlnvroot is null, the default installation path is used.
/// vlnvroot may be a list of paths separated by ':' (on Linux) or ';' (on
/// Windows)
/// @return Null if no file is found, otherwise a file path
/// @param vlnvroot     Path or list of paths to root of directory(s)
///                     containing modelsT
/// @param vendor       Vendor directory e.g. yourcompany.com. This can be
///                     null or include glob characters
/// @param library      Library directory e.g. processor. This can be null or
///                     include glob characters
/// @param name         The name directory e.g. risc32. This can be null or
///                     include glob characters
/// @param version      Version directory e.g. 1.0. This can be null or
///                     include glob characters
/// @param type         Type of model to be found.
/// @param reportErrors The action when a single model cannot be found
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Examples:
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00519'>SimulationControl/processorQuery</a>
/// - <a href='./SimulationControl_2moduleSaveRestore_2module_2module_8c_source.html#l00057'>SimulationControl/moduleSaveRestore</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOP_2module_2module_8c_source.html#l00036'>PlatformConstruction/simpleCpuMemoryUartUsingOP</a>
/// - <a href='./PlatformConstruction_2simpleCpuMemoryUartUsingOPandHarnessExe_2module_2module_8c_source.html#l00036'>PlatformConstruction/simpleCpuMemoryUartUsingOPandHarnessExe</a>
/// - <a href='./SimulationControl_2dynamicHarness_2harness_2harness_8c_source.html#l00123'>SimulationControl/dynamicHarness</a>

const char* opVLNVString (
    const char*  vlnvroot,
    const char*  vendor,
    const char*  library,
    const char*  name,
    const char*  version,
    optModelType type,
    optVLNVError reportErrors
);

/// Return the 'vendor' part of the VLNV
/// @return Pointer to text.
/// @param vlnv A VLNV object
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00411'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00380'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectVLNV

const char * opVLNVVendor (
    optVLNVP vlnv
);

/// Return the 'version' part of the VLNV
/// @return Pointer to text.
/// @param vlnv A VLNV object
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./PlatformConstruction_2walker_2harness_2harness_8c_source.html#l00414'>PlatformConstruction/walker</a>
/// - <a href='./SimulationControl_2processorQuery_2harness_2harness_8c_source.html#l00383'>SimulationControl/processorQuery</a>
/// @sa
/// opObjectVLNV

const char * opVLNVVersion (
    optVLNVP vlnv
);

/// As for opMessage, but using a va_list. Please refer to libC documentation
/// for details of the va_list.
/// @param severity I=Info, W=Warning, E=Error, F=Fatal (aborts the
///                 simulator)
/// @param ident    A short, easily searched code to identify this message
/// @param fmt      Printf format string (see gnu printf for details)
/// @param ap       Varargs list
/// @par Phase:
/// Can be used in any phase

void opVMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// Send formatted text to the simulator output stream
/// @param fmt Printf format string (see gnu printf for details)
/// @param ap  Varargs list header
/// @par Phase:
/// Can be used in any phase

void opVPrintf (
    const char* fmt,
    va_list     ap
);

/// Create a temporary formatted string using varargs. Refer to GNU
/// documentation for printf
/// @return A temporary string containing the formatted text
/// @param fmt Printf format string (see gnu printf for details)
/// @param ap  Varargs list header
/// @par Phase:
/// Can be used in these phases:
/// - Construction
/// @par Restrictions:
/// Note that opVSprintf allocates a limited number of buffers, so do not rely
/// on the data persisting beyond the next use of this function. Therefore the
/// string should be immediately passed to the construction function. (Note that
/// construction functions keep a copy of their string arguments).

const char* opVSprintf (
    const char* fmt,
    va_list     ap
);

/// This function is the same as opObjectByName, which finds any object by its
/// hierarchical name, but with the optObjectP return value cast to (void *).
/// This should be used in place of opObjectByName when compiling with g++
/// because g++ does not support the transparent union used for the optObjectP
/// type.
/// @return Void pointer to platform object of any type
/// @param object The root of the search
/// @param name   The hierarchical name (names separated by the '/'
///               character).
/// @param mask   A bitmask of types to find
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optBridgeP
/// - optBusP
/// - optFIFOP
/// - optExtensionP
/// - optExtElabP
/// - optMemoryP
/// - optMMCP
/// - optMMRegisterP
/// - optModuleP
/// - optNetP
/// - optPacketnetP
/// - optPeripheralP
/// - optProcessorP

void * opVoidByName (
    optObjectP  object,
    const char* name,
    optStrType  mask
);

/// This function is the same as opObjectParent, which finds the parent of any
/// object, but with the optObjectP return value cast to (void *). This should
/// be used in place of opObjectParent when compiling with g++ because g++ does
/// not support the transparent union used for the optObjectP type.
/// @return Void pointer to the parent object
/// @param object The current object
/// @par Phase:
/// Can be used in any phase
/// @par Objects:
/// Can be applied to these objects
/// - optApplicationP
/// - optBridgeP
/// - optBusP
/// - optBusPortConnP
/// - optBusPortP
/// - optBusSlaveP
/// - optCmdParserP
/// - optCommandArgP
/// - optCommandP
/// - optDebugProcessorGroupP
/// - optDocNodeP
/// - optExceptionP
/// - optExtElabP
/// - optExtensionP
/// - optFIFOP
/// - optFIFOPortConnP
/// - optFIFOPortP
/// - optFlatFIFOP
/// - optFlatNetP
/// - optFlatPacketnetP
/// - optFormalEnumP
/// - optFormalGroupP
/// - optFormalP
/// - optMMCP
/// - optMMRegisterFieldP
/// - optMMRegisterP
/// - optMemoryP
/// - optModeP
/// - optModuleObjectP
/// - optModuleP
/// - optNetMonitorP
/// - optNetP
/// - optNetPortConnP
/// - optNetPortConnTableP
/// - optNetPortP
/// - optPacketnetMonitorP
/// - optPacketnetP
/// - optPacketnetPortConnP
/// - optPacketnetPortP
/// - optParamP
/// - optPeripheralP
/// - optProcRootP
/// - optProcessorP
/// - optRedirectP
/// - optRegGroupP
/// - optRegP
/// - optRestoreContextP
/// - optRootModuleDataP
/// - optSaveContextP
/// - optSharedDataHandleP
/// - optTriggerEventP
/// - optVLNVP
/// - optWatchpointP

void * opVoidParent (
    optObjectP object
);

/// Return the upper address limit of a watchpoint region
/// @return The upper address limit of a watchpoint region
/// @param watchpoint The watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00227'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointUserData

Addr opWatchpointAddressHi (
    optWatchpointP watchpoint
);

/// Return the lower address limit of a watchpoint region
/// @return The lower address limit of a watchpoint region
/// @param watchpoint The watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00226'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressHi
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointUserData

Addr opWatchpointAddressLo (
    optWatchpointP watchpoint
);

/// Delete a watchpoint. No more notifications will occur for this watchpoint.
/// @param watchpoint The watchpoint to be deleted
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00209'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressLo
/// opWatchpointAddressHi
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointTriggeredBy
/// opWatchpointUserData

void opWatchpointDelete (
    optWatchpointP watchpoint
);

/// If the given watchpoint is of type OP_WP_REG, and has been triggered, return
/// the register that changed
/// @return The register that changed
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00193'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressHi
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointTriggeredBy
/// opWatchpointUserData

optRegP opWatchpointReg (
    optWatchpointP watchpoint
);

/// If the given watchpoint is of type OP_WP_REG, and has been triggered, return
/// a pointer to the register's current value
/// @return Pointer to previous value data
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00194'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressLo
/// opWatchpointAddressHi
/// opWatchpointDelete
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointTriggeredBy
/// opWatchpointUserData

void* opWatchpointRegCurrentValue (
    optWatchpointP watchpoint
);

/// If the given watchpoint is of type OP_WP_REG, and has been triggered, return
/// a pointer to the register's previous value
/// @return Pointer to previous value data
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00195'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressHi
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointTriggeredBy
/// opWatchpointUserData

void* opWatchpointRegPreviousValue (
    optWatchpointP watchpoint
);

/// Reset the given watchpoint to its un-triggered state.
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00172'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00211'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressHi
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointType
/// opWatchpointTriggeredBy
/// opWatchpointUserData

void opWatchpointReset (
    optWatchpointP watchpoint
);

/// Return the processor that triggered this watchpoint (i.e. the processor that
/// was executing at the time)
/// @return The processor that triggered the watchpoint
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00151'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00185'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointType
/// opWatchpointUserData

optProcessorP opWatchpointTriggeredBy (
    optWatchpointP watchpoint
);

/// Return the type of this watchpoint
/// @return The type of the watchpoint
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00152'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00186'>DebuggerIntegration/multiProcessor</a>
/// - <a href='./SimulationControl_2addingWatchpoints_2harness_2harness_8c_source.html#l00032'>SimulationControl/addingWatchpoints</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointTriggeredBy
/// opWatchpointUserData

optWatchpointType opWatchpointType (
    optWatchpointP watchpoint
);

/// Return the user data that was passed to the function that created the
/// watchpoint
/// @return User data passed when the watchpoint was created.
/// @param watchpoint The current watchpoint
/// @par Phase:
/// Can be used in these phases:
/// - Pre-simulation
/// - Simulation
/// - Post-simulation
/// @par Examples:
/// - <a href='./DebuggerIntegration_2modeAndException_2harness_2harness_8c_source.html#l00076'>DebuggerIntegration/modeAndException</a>
/// - <a href='./DebuggerIntegration_2multiProcessor_2harness_2harness_8c_source.html#l00090'>DebuggerIntegration/multiProcessor</a>
/// @sa
/// opRootModuleWatchpointNext
/// opWatchpointAddressLo
/// opWatchpointDelete
/// opWatchpointRegCurrentValue
/// opWatchpointRegPreviousValue
/// opWatchpointReg
/// opWatchpointReset
/// opWatchpointTriggeredBy
/// opWatchpointType

void* opWatchpointUserData (
    optWatchpointP watchpoint
);

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamBoolCreate (

    const char * name,
    Bool         value
){ optParamArray v = { 0, OP_PARAM_BOOL, { 0 }};   v.name = name; v.u.boolValue = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamDoubleCreate (

    const char * name,
    double       value
){ optParamArray v = { 0, OP_PARAM_DOUBLE, { 0 }}; v.name = name; v.u.doubleValue = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamEndianCreate (

    const char * name,
    optEndian    value
){ optParamArray v = { 0, OP_PARAM_ENDIAN, { 0 }}; v.name = name; v.u.endianValue = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamEnumCreate (

    const char * name,
    const char * value
){ optParamArray v = { 0, OP_PARAM_ENUM, { 0 }}; v.name = name; v.u.enumValue = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamInt32Create (

    const char * name,
    Int32        value
){ optParamArray v = { 0, OP_PARAM_INT32, { 0 }}; v.name = name; v.u.int32Value = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamInt64Create (

    const char * name,
    Int64        value
){ optParamArray v = { 0, OP_PARAM_INT64, { 0 }}; v.name = name; v.u.int64Value = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamPointerCreate (

    const char * name,
    void*        value
){ optParamArray v = { 0, OP_PARAM_PTR, { 0 }}; v.name = name; v.u.pointerValue = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamStringCreate (

    const char * name,
    const char * value
){ optParamArray v = { 0, OP_PARAM_STRING, { 0 }}; v.name = name; v.u.stringValue = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamUns32Create (

    const char * name,
    Uns32        value
){ optParamArray v = { 0 , OP_PARAM_UNS32, { 0 }}; v.name = name; v.u.uns32Value = value; return v; }

/// Used by instance parameter macros. Do not use this function

static inline optParamArray opParamUns64Create (

    const char * name,
    Uns64        value
){ optParamArray v = { 0, OP_PARAM_UNS64, { 0 }}; v.name = name; v.u.uns64Value = value; return v; }


#endif /* OP_H */

