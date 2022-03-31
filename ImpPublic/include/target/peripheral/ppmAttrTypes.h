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

/* ppmAttrTypes.h (do not include direction - include pph.h instead) */

#ifndef PPM_PPM_ATTR_TYPES_H
#define PPM_PPM_ATTR_TYPES_H


typedef enum ppmBusPortTypeE {
    PPM_BUS_PORT_ILLEGAL,    // Do not use
    PPM_MASTER_PORT,
    PPM_SLAVE_PORT,
    PPM_MASTERSLAVE_PORT    // Not yet supported
} ppmBusPortType;

typedef enum ppmNetPortTypeE {
    PPM_NET_PORT_ILLEGAL,            // Do not use
    PPM_INPUT_PORT,
    PPM_OUTPUT_PORT,
    PPM_INOUT_PORT
} ppmNetPortType;

//
// PPM bus port info.
//
typedef struct ppmBusPortS {
    Addr             addrHi;          // on slave port

    ppmString        name;
    ppmBusPortType   type;

    // On a master port, specify the allowed number of address bits
    Uns32            addrBits;        // legacy or default value
    Uns32            addrBitsMin;     // use this to set the legal lower limit
    Uns32            addrBitsMax;     // use this to set the legal upper limit

    // documentation
    ppmString        description;
    ppmPtr           descriptionDom;

    Bool             mustBeConnected;
    Bool             remappable;      // on slave port

} ppmBusPort, *ppmBusPortP;


//
// PPM net port info.
//
typedef struct ppmNetPortS {
    ppmString        name;
    ppmNetPortType   type;                        // direction

    // documentation
    ppmString        description;
    ppmPtr           descriptionDom;
    ppmHandlePtr     handlePtr;                   // use this handle to read/write
    ppmNetFunc       netCB;                       // net notification
    Bool             mustBeConnected;
    ppmPtr           userData;

} ppmNetPort, *ppmNetPortP;

//
// PPM net port info.
//
typedef struct ppmPacketnetPortS {
    ppmString        name;

    // documentation
    ppmString             description;
    ppmPtr                descriptionDom;
    ppmPacketnetHandlePtr handlePtr;              // used to write to the packetnet
    ppmPtr                sharedData;             // pointer to shared data
    Uns32                 sharedDataBytes;        // number of bytes of shared data
    ppmPacketnetFunc      packetnetCB;            // packetnet notification
    Bool                  mustBeConnected;
    ppmPtr                userData;               // passed back to packetnetCB

} ppmPacketnetPort, *ppmPacketnetPortP;

//
// PPM FIFO (Conn) port info.
//
typedef struct ppmConnInputPortS {
    ppmString              name;

    // documentation
    ppmString              description;
    ppmPtr                 descriptionDom;
    ppmConnInputHandlePtr  handlePtr;              // used to write to the packetnet
    Bool                   mustBeConnected;
    Uns32                  width;

} ppmConnInputPort, *ppmConnInputPortP;

//
// PPM FIFO (Conn) port info.
//
typedef struct ppmConnOutputPortS {
    ppmString              name;

    // documentation
    ppmString              description;
    ppmPtr                 descriptionDom;
    ppmConnOutputHandlePtr handlePtr;              // used to write to the packetnet
    Bool                   mustBeConnected;
    Uns32                  width;

} ppmConnOutputPort, *ppmConnOutputPortP;


typedef struct ppmVlnvInfoS {
    ppmString vendor;
    ppmString library;
    ppmString name;
    ppmString version;
} ppmVlnvInfo, *ppmVlnvInfoP;


//
// Model parameter types
//
typedef enum ppmParameterTypeE {
    ppm_PT_NONE,
    ppm_PT_BOOL,     // Boolean parameter. Can be 0,n,N,f,F,dis etc. or 1,y,Y,t,T,en
    ppm_PT_INT32,    // Signed integer parameter.
    ppm_PT_INT64,    // Signed long integer parameter.
    ppm_PT_UNS32,    // Unsigned integer parameter.
    ppm_PT_UNS64,    // Unsigned long integer parameter.
    ppm_PT_DOUBLE,   // Floating point parameter.
    ppm_PT_STRING,   // String parameter.
    ppm_PT_ENUM,     // Enum parameter.
    ppm_PT_ENDIAN,   // Endian parameter.
                     // Specified by a string from a set of strings.
                     // Returns an integer.
    ppm_PT_PTR,      // pointer
} ppmParameterType;

//
// Enumeration name/value pairs
//
typedef struct ppmEnumParameterS {
    ppmString   name;
    ppmString   description;
    Uns32       value;
    ppmPtr      descriptionDom;
} ppmEnumParameter;

//
// Specification of a model parameter
//
typedef struct ppmParameterS {
    ppmString        name;
    ppmParameterType type;

    // space for documentation
    ppmString        description;
    ppmPtr           descriptionDom;

    // specs of each parameter type
    union {

        struct ppmBoolParamS {
            Bool defaultValue;
        } boolParam;

        struct ppmInt32ParamS {
            Int32 defaultValue;
            Int32 min;
            Int32 max;
        } int32Param;

        struct ppmUns32ParamS {
            Uns32 defaultValue;
            Uns32 min;
            Uns32 max;
        } uns32Param;

        struct ppmInt64ParamS {
            Int64 defaultValue;
            Int64 min;
            Int64 max;
        } int64Param;

        struct ppmUns64ParamS {
            Uns64 defaultValue;
            Uns64 min;
            Uns64 max;
        } uns64Param;

        struct ppmDoubleParamS {
            double defaultValue;
            double min;
            double max;
        } doubleParam;

        struct ppmStringParamS {
            ppmString defaultValue;
            Uns32     maxLength;    // zero means unlimited
        } stringParam;

        struct ppmEnumParamS {
            ppmEnumParameterP legalValues;    // Array of values, first is the default,
        } enumParam;
    } u;

    ppmPtr valuePtr;
    Bool mustBeSpecified;
} ppmParameter, *ppmParameterP;

#endif

