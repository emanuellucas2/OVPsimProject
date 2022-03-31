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


#ifndef OPTYPEREFS_H
#define OPTYPEREFS_H


////////////////////////////////////////////////////////////////////////////////
// Opaque Structure References
////////////////////////////////////////////////////////////////////////////////

/// @struct optCmdParserS
/// Handle to instance of command line parser
typedef struct optCmdParserS            *optCmdParserP          , **optCmdParserPP;
/// @struct optCommandArgS
/// Model command argument
typedef struct optCommandArgS           *optCommandArgP         , **optCommandArgPP;
/// @struct optDocNodeS
/// Documentation node
typedef struct optDocNodeS              *optDocNodeP            , **optDocNodePP;
/// @struct optExceptionS
/// Processor exception descriptor
typedef struct optExceptionS            *optExceptionP          , **optExceptionPP;
/// @struct optFlatFIFOS
/// Flattened FIFO used for construction
typedef struct optFlatFIFOS             *optFlatFIFOP           , **optFlatFIFOPP;
/// @struct optFlatNetS
/// Flattened nets for run-time propagation
typedef struct optFlatNetS              *optFlatNetP            , **optFlatNetPP;
/// @struct optFlatPacketnetS
/// Flattened packetnets for run-time propagation
typedef struct optFlatPacketnetS        *optFlatPacketnetP      , **optFlatPacketnetPP;
/// @struct optModeS
/// Processor mode descriptor
typedef struct optModeS                 *optModeP               , **optModePP;
/// @struct optModuleObjectS
/// Module persistent data
typedef struct optModuleObjectS         *optModuleObjectP       , **optModuleObjectPP;
/// @struct optNetPortConnTableS
/// Table of net port connections
typedef struct optNetPortConnTableS     *optNetPortConnTableP   , **optNetPortConnTablePP;
/// @struct optDebugProcessorGroupS
/// RSP efficiency grouping of processors
typedef struct optDebugProcessorGroupS  *optDebugProcessorGroupP, **optDebugProcessorGroupPP;
/// @struct optRedirectS
/// Redirect object
typedef struct optRedirectS             *optRedirectP           , **optRedirectPP;
/// @struct optRegGroupS
/// Group of processor registers
typedef struct optRegGroupS             *optRegGroupP           , **optRegGroupPP;
/// @struct optRegS
/// The processor register
typedef struct optRegS                  *optRegP                , **optRegPP;
/// @struct optRootModuleDataS
/// Simulator structures only on root module
typedef struct optRootModuleDataS       *optRootModuleDataP     , **optRootModuleDataPP;
/// @struct optRestoreContextS
/// Context used by system when restoring system state
typedef struct optRestoreContextS       *optRestoreContextP     , **optRestoreContextPP;
/// @struct optSaveContextS
/// Context used by system when saving system state
typedef struct optSaveContextS          *optSaveContextP        , **optSaveContextPP;
/// @struct optSharedDataHandleS
/// Shared data handle
typedef struct optSharedDataHandleS     *optSharedDataHandleP   , **optSharedDataHandlePP;
/// @struct optTriggerEventS
/// Module attributes
typedef struct optTriggerEventS         *optTriggerEventP       , **optTriggerEventPP;
/// @struct optVLNVS
/// VLNV descriptor
typedef struct optVLNVS                 *optVLNVP               , **optVLNVPP;
/// @struct optWatchpointS
/// Watchpoint object
typedef struct optWatchpointS           *optWatchpointP         , **optWatchpointPP;


////////////////////////////////////////////////////////////////////////////////
// Public structure forward references
////////////////////////////////////////////////////////////////////////////////

typedef struct optDestCallbacksS         *optDestCallbacksP      , **optDestCallbacksPP;
typedef struct optBusPortConnectS        *optBusPortConnectP     , **optBusPortConnectPP;
typedef struct optNetPortConnectS        *optNetPortConnectP     , **optNetPortConnectPP;
typedef struct optPacketnetPortConnectS  *optPacketnetPortConnectP, **optPacketnetPortConnectPP;
typedef struct optFIFOPortConnectS       *optFIFOPortConnectP    , **optFIFOPortConnectPP;
typedef struct optBusPortInfoS           *optBusPortInfoP        , **optBusPortInfoPP;
typedef struct optFIFOPortInfoS          *optFIFOPortInfoP       , **optFIFOPortInfoPP;
typedef struct optNetPortInfoS           *optNetPortInfoP        , **optNetPortInfoPP;
typedef struct optEnumParamSpecS         *optEnumParamSpecP      , **optEnumParamSpecPP;
typedef struct optMemorySpecS            *optMemorySpecP         , **optMemorySpecPP;
typedef struct optParamSpecS             *optParamSpecP          , **optParamSpecPP;
typedef struct optParamArrayS            *optParamArrayP         , **optParamArrayPP;
typedef struct optPacketnetPortInfoS     *optPacketnetPortInfoP  , **optPacketnetPortInfoPP;
typedef struct optConnectionsS           *optConnectionsP        , **optConnectionsPP;
typedef struct optDebuggerNotifiersS     *optDebuggerNotifiersP  , **optDebuggerNotifiersPP;
typedef struct optObjectInfoS            *optObjectInfoP         , **optObjectInfoPP;
typedef struct optModuleAttrS            *optModuleAttrP         , **optModuleAttrPP;
typedef struct optArgStringListS         *optArgStringListP      , **optArgStringListPP;
typedef struct optParamSpecGroupS        *optParamSpecGroupP     , **optParamSpecGroupPP;
typedef struct optPersonalityS           *optPersonalityP        , **optPersonalityPP;
typedef struct optVFSS                   *optVFSP                , **optVFSPP;

#endif /* OPTYPEREFS_H */

