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

#include "hostapi/impTypes.h"
#include "vmi/vmiModelInfo.h"
#include "vmi/vmiPorts.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"
#include "vmi/vmiVersion.h"


////////////////////////////////////////////////////////////////////////////////
// MMC CONSTRUCTOR, NETLIST AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

#define VMIMMC_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmimmcComponentP component,         \
    Bool             transparent,       \
    void            *parameterValues    \
)
typedef VMIMMC_CONSTRUCTOR_FN((*vmimmcConstructorFn));

#define VMIMMC_LINK_FN(_NAME) void _NAME(vmimmcComponentP component)
typedef VMIMMC_LINK_FN((*vmimmcLinkFn));

#define VMIMMC_DESTRUCTOR_FN(_NAME) void _NAME(vmimmcComponentP component)
typedef VMIMMC_DESTRUCTOR_FN((*vmimmcDestructorFn));


////////////////////////////////////////////////////////////////////////////////
// SAVE / RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type is used to implement model save
//
#define VMIMMC_SAVE_STATE_FN(_NAME) void _NAME( \
    vmimmcComponentP component,     \
    vmiSaveContextP  cxt,           \
    Uns32            srVersion      \
)
typedef VMIMMC_SAVE_STATE_FN((*vmimmcSaveStateFn));

//
// This callback function type is used to implement model restore
//
#define VMIMMC_RESTORE_STATE_FN(_NAME) void _NAME( \
    vmimmcComponentP   component,   \
    vmiRestoreContextP cxt,         \
    Uns32              srVersion    \
)
typedef VMIMMC_RESTORE_STATE_FN((*vmimmcRestoreStateFn));


////////////////////////////////////////////////////////////////////////////////
// MODEL REFRESH (AT START OF TIME SLICE)
////////////////////////////////////////////////////////////////////////////////

#define VMIMMC_REFRESH_FN(_NAME) void _NAME( \
    vmimmcComponentP component, \
    vmiIASRunState   state      \
)
typedef VMIMMC_REFRESH_FN((*vmimmcRefreshFn));


////////////////////////////////////////////////////////////////////////////////
// BUS PORTS
////////////////////////////////////////////////////////////////////////////////

#define VMIMMC_BUSPORT_FN(_NAME) vmiBusPortP _NAME( \
    vmimmcComponentP component, \
    vmiBusPortP      prev       \
)
typedef VMIMMC_BUSPORT_FN((*vmimmcBusPortFn));


////////////////////////////////////////////////////////////////////////////////
// FORMALS
////////////////////////////////////////////////////////////////////////////////

//
// Type of function called by simulator to get info about the parameters of this
// model
//
#define VMIMMC_PARAM_SPEC_FN(_NAME) vmiParameterP _NAME( \
    vmimmcComponentP component, \
    vmiParameterP    prev       \
)
typedef VMIMMC_PARAM_SPEC_FN((*vmimmcParamSpecFn));

//
// Type of function called by simulator to get the size of the parameter value
// table
//
#define VMIMMC_PARAM_TABLE_SIZE_FN(_NAME) Uns32 _NAME ( \
    vmimmcComponentP component  \
)
typedef VMIMMC_PARAM_TABLE_SIZE_FN((*vmimmcParamValueSizeFn));


//
// This structure defines attributes for a memory model component
//
typedef struct vmimmcAttrS {

    ////////////////////////////////////////////////////////////////////////
    // VERSION & TYPE
    ////////////////////////////////////////////////////////////////////////

    const char            *versionString;       // version string
    vmiModelType           modelType;           // type of model (enum)
    Uns32                  componentSize;       // size in bytes

    ////////////////////////////////////////////////////////////////////////
    // MODEL STATUS
    ////////////////////////////////////////////////////////////////////////

    vmiVisibility          visibility;          // model visibility (enum)
    vmiReleaseStatus       releaseStatus;       // model release status (enum)

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmimmcSaveStateFn      saveCB;              // model state save callback
    vmimmcRestoreStateFn   restoreCB;           // model state restore callback
    Uns32                  srVersion;           // model save/restore version

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmimmcConstructorFn    constructorCB;       // constructor
    vmimmcLinkFn           linkCB;              // link netlist
    vmimmcDestructorFn     destructorCB;        // destructor

    ////////////////////////////////////////////////////////////////////////
    // MODEL REFRESH (AT START OF TIME SLICE)
    ////////////////////////////////////////////////////////////////////////

    vmimmcRefreshFn        refreshCB;           // refresh

    ////////////////////////////////////////////////////////////////////////
    // FULL MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    vmiMemReadFn           readNFullCB;         // N-byte read callback
    vmiMemWriteFn          writeNFullCB;        // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // TRANSPARENT MODEL CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    vmiMemWatchFn          readNTransparentCB;  // N-byte read callback
    vmiMemWatchFn          writeNTransparentCB; // N-byte write callback

    ////////////////////////////////////////////////////////////////////////
    // FORMAL PARAMETERS iterators to find parameters accepted by this model
    ////////////////////////////////////////////////////////////////////////

    vmimmcParamSpecFn      paramSpecsCB;        // callback for next formal param
    vmimmcParamValueSizeFn paramValueSizeCB;    // callback to get size of table

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES iterators to find the bus ports
    ////////////////////////////////////////////////////////////////////////

    vmimmcBusPortFn        busPortSpecsCB;      // callback for next bus port

    ////////////////////////////////////////////////////////////////////////
    // MODEL VLNV
    ////////////////////////////////////////////////////////////////////////

    vmiVlnvInfo  vlnv;

} vmimmcAttr;


