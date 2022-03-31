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

/* ppmAttrs.h (do not include this file directly - include pph.h instead) */

#ifndef PPM_PPM_ATTRS_H
#define PPM_PPM_ATTRS_H

//
// Put this in the versionString field
//
#define PPM_VERSION_STRING  "2.5"

typedef enum ppmModelTypeE {
    PPM_MT_PERIPHERAL = 77
} ppmModelType;

//
// Control the visibility of the model in debug and introspection.
// Bit-mask or boolean.
//
typedef enum ppmVisibilityE {
    PPM_VISIBLE,
    PPM_INVISIBLE
} ppmVisibility;

//
// Model release status
//
typedef enum ppmReleaseStatusS {
    PPM_UNSET,
    PPM_INTERNAL,
    PPM_RESTRICTED,
    PPM_IMPERAS,
    PPM_OVP,
} ppmReleaseStatus;

typedef struct ppmModelAttrS {

    ////////////////////////////////////////////////////////////////////////
    // VERSION and IDENTIFICATION
    ////////////////////////////////////////////////////////////////////////

    ppmString              versionString;    // Must be PPM_VERSION_STRING
    ppmModelType           type;             // MUST be set to PPM_PERIPHERAL

    ////////////////////////////////////////////////////////////////////////
    // Model status
    ////////////////////////////////////////////////////////////////////////

    ppmVisibility          visibility;           // model instance is invisible
    ppmReleaseStatus       releaseStatus;        // model release status (enum)
    Bool                   saveRestore;          // model supports save and restore
    Bool                   noRecursiveCallbacks; // a callback cannot be triggered
                                                 // from within this model

    ////////////////////////////////////////////////////////////////////////
    // Callbacks
    ////////////////////////////////////////////////////////////////////////

    ppmBusPortSpecFn        busPortsCB;       // next bus port callback
    ppmNetPortSpecFn        netPortsCB;       // next net port callback
    ppmPacketnetPortSpecFn  packetnetPortsCB; // next net port callback
    ppmConnInputPortSpecFn  connInputsCB;     // next FIFO input port  callback
    ppmConnOutputPortSpecFn connOutputsCB;    // next FIFO output port  callback
    ppmParameterSpecFn      paramSpecCB;      // next parameter callback
    ppmSaveStateFn          saveCB;           // PSE state save callback
    ppmRestoreStateFn       restoreCB;        // PSE state restore callback
    ppmDocFn                docCB;            // This function installs
                                             // documentation nodes

    ////////////////////////////////////////////////////////////////////////
    // Data needed by a simulator for peripheral model.
    ////////////////////////////////////////////////////////////////////////

    // Location of this model
    ppmVlnvInfo vlnv;

    // Optional Extension library used when the model requires native code
    ppmString   extension;

    // Path to PDF documentation
    ppmString   doc;

     // Model family string
    ppmString   family;

} ppmModelAttr, *ppmModelAttrP;

#endif

