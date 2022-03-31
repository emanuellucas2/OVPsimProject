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

#include "vmi/vmiTyperefs.h"
#include "hostapi/impTypes.h"

//
// Model parameter types
//
typedef enum vmiParameterTypeE {
    vmi_PT_BOOL,     // Boolean parameter. Can be 0,n,N,f,F,dis etc. or 1,y,Y,t,T,en
    vmi_PT_INT32,    // Signed integer parameter.
    vmi_PT_INT64,    // Signed integer parameter.
    vmi_PT_UNS32,    // Unsigned integer parameter.
    vmi_PT_UNS64,    // Unsigned long integer parameter.
    vmi_PT_DOUBLE,   // Floating point parameter.
    vmi_PT_STRING,   // String parameter.
    vmi_PT_ENUM,     // Enum parameter.
                     // Specified by a string from a set of strings.
                     // Returns an integer.
    vmi_PT_ENDIAN,   // Takes one of two values; little or big
    vmi_PT_PTR,      // Pointer parameter.
} vmiParameterType;

//
// Enumeration name/value pairs
//
typedef struct vmiEnumParameterS {
    const char *name;
    Uns32       value;
    const char *description;
    void       *descriptionDom;
} vmiEnumParameter;

typedef struct vmiParameterGroupS {
    const char *name;          // name of the group
    const char *description;   // not used at present
} vmiParameterGroup;

#define VMI_PARAM_GROUP_SPEC(_NAME, _DESC)  vmiParameterGroup _NAME = {  .name = #_NAME, .description  = _DESC };


//
// Specification of a model parameter
//
typedef struct vmiParameterS {
    const char      *name;
    vmiParameterType type;

    // for safety, record the size
    Uns8             sizeOf;

    // byte offset into the model's parameter table
    Uns32            valueOffset;

    // byte offset into the model's 'parameter is set' table
    Uns32            setBitOffset;

    // space for documentation
    const char        *description;
    void              *descriptionDom;

    // Point a group of parameters to the same group structure
    // If null, parameter is in the default group
    vmiParameterGroupCP group;

    // specs of each parameter type
    union {

        struct boolParamS {
            Bool defaultValue;
        } boolParam;

        struct int32ParamS {
            Int32 defaultValue;
            Int32 min;
            Int32 max;
        } int32Param;

        struct uns32ParamS {
            Uns32 defaultValue;
            Uns32 min;
            Uns32 max;
        } uns32Param;

        struct int64ParamS {
            Int64 defaultValue;
            Int64 min;
            Int64 max;
        } int64Param;

        struct uns64ParamS {
            Uns64 defaultValue;
            Uns64 min;
            Uns64 max;
        } uns64Param;

        struct ptrParamS {
            void *defaultValue;
        } ptrParam;

        struct doubleParamS {
            double defaultValue;
            double min;
            double max;
        } doubleParam;

        struct stringParamS {
            const char *defaultValue;
        } stringParam;

        struct enumParamS {
            // Null terminated array of vmiEnumParameter structures
            // The first is the default value unless the following
            // member is non-null.
            vmiEnumParameterCP legalValues;

            // Specify the default enumeration be setting this to point
            // to the default member of the preceding array
            vmiEnumParameterCP defaultValue;
        } enumParam;
    } u;
} vmiParameter;

//
// Offset of parameter data in instance structure.
// Used in this file (not by users).
//
#define VMI_PARAM_OFFSET(_STRUCT, _MEMBER) \
    ((UnsPS)(&(((_STRUCT ## P)0)->_MEMBER)))

#define SETBIT(_MEMBER)  _MEMBER ## __ ## set

//
// macros to initialize parameter spec entries
//

#define VMI_BOOL_PARAM_SPEC(_STR, _NAME, _DEFAULT, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_BOOL, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.boolParam.defaultValue   = _DEFAULT, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Bool) \
}

#define VMI_BOOL_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_BOOL, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.boolParam.defaultValue   = _DEFAULT, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Bool), \
    .group                      = _GROUP  \
}

#define VMI_INT32_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_INT32, \
    .u.int32Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.int32Param.min           = _MIN, \
    .u.int32Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Int32) \
}

#define VMI_INT32_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_INT32, \
    .u.int32Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.int32Param.min           = _MIN, \
    .u.int32Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Int32), \
    .group                      = _GROUP  \
}

#define VMI_UNS32_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_UNS32, \
    .u.uns32Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.uns32Param.min           = _MIN, \
    .u.uns32Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Uns32) \
}

#define VMI_UNS32_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_UNS32, \
    .u.uns32Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.uns32Param.min           = _MIN, \
    .u.uns32Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Uns32), \
    .group                      = _GROUP \
}

#define VMI_INT64_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_INT64, \
    .u.int64Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.int64Param.min           = _MIN, \
    .u.int64Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Int64) \
}

#define VMI_INT64_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_INT64, \
    .u.int64Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.int64Param.min           = _MIN, \
    .u.int64Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Int64), \
    .group                      = _GROUP  \
}

#define VMI_UNS64_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_UNS64, \
    .u.uns64Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.uns64Param.min           = _MIN, \
    .u.uns64Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Uns64) \
}

#define VMI_UNS64_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_UNS64, \
    .u.uns64Param.defaultValue  = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.uns64Param.min           = _MIN, \
    .u.uns64Param.max           = _MAX, \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Uns64), \
    .group                      = _GROUP  \
}

#define VMI_PTR_PARAM_SPEC(_STR, _NAME, _DEFAULT, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_PTR, \
    .u.ptrParam.defaultValue    = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC, \
    .sizeOf                     = sizeof(void*) \
}

#define VMI_PTR_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_PTR, \
    .u.ptrParam.defaultValue    = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC, \
    .sizeOf                     = sizeof(void*), \
    .group                      = _GROUP \
}

#define VMI_DBL_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_DOUBLE, \
    .u.doubleParam.defaultValue = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.doubleParam.min          = _MIN, \
    .u.doubleParam.max          = _MAX, \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(double) \
}

#define VMI_DBL_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _MIN, _MAX, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_DOUBLE, \
    .u.doubleParam.defaultValue = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .u.doubleParam.min          = _MIN, \
    .u.doubleParam.max          = _MAX, \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(double), \
    .group                      = _GROUP \
}

#define VMI_ENUM_PARAM_SPEC(_STR, _NAME, _LIST, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_ENUM, \
    .u.enumParam.legalValues    = _LIST, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(Uns32) \
}

#define VMI_ENUM_GROUP_PARAM_SPEC(_STR, _NAME, _LIST, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_ENUM, \
    .u.enumParam.legalValues    = _LIST, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(Uns32), \
    .group                      = _GROUP \
}

#define VMI_ENUM_PARAM_SPEC_WITH_DEFAULT(_STR, _NAME, _LIST, _DEFAULT, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_ENUM, \
    .u.enumParam.legalValues    = _LIST, \
    .u.enumParam.defaultValue   = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(Uns32) \
}

#define VMI_ENUM_GROUP_PARAM_SPEC_WITH_DEFAULT(_STR, _NAME, _LIST, _DEFAULT, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_ENUM, \
    .u.enumParam.legalValues    = _LIST, \
    .u.enumParam.defaultValue   = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(Uns32), \
    .group                      = _GROUP \
}

#define VMI_ENDIAN_PARAM_SPEC(_STR, _NAME, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_ENDIAN, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Uns32) \
}

#define VMI_ENDIAN_GROUP_PARAM_SPEC(_STR, _NAME, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_ENDIAN, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .setBitOffset               = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)), \
    .description                = _DESC, \
    .sizeOf                     = sizeof(Uns32), \
    .group                      = _GROUP \
}

#define VMI_STRING_PARAM_SPEC(_STR, _NAME, _DEFAULT, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_STRING, \
    .u.stringParam.defaultValue = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(char*) \
}

#define VMI_STRING_GROUP_PARAM_SPEC(_STR, _NAME, _DEFAULT, _GROUP, _DESC) { \
    .name                       = #_NAME, \
    .type                       = vmi_PT_STRING, \
    .u.stringParam.defaultValue = _DEFAULT, \
    .valueOffset                = VMI_PARAM_OFFSET(_STR, _NAME), \
    .description                = _DESC,  \
    .sizeOf                     = sizeof(char*), \
    .group                      = _GROUP \
}

//
// Use this to terminate the list
//
#define VMI_END_PARAM  { .name= 0 }

//
// Declare an attribute value ...       here   .. and the flag here
#define VMI_BOOL_PARAM(_NAME)    Bool   _NAME;   Bool SETBIT(_NAME);
#define VMI_INT32_PARAM(_NAME)   Int32  _NAME;   Bool SETBIT(_NAME);
#define VMI_INT64_PARAM(_NAME)   Int64  _NAME;   Bool SETBIT(_NAME);
#define VMI_UNS32_PARAM(_NAME)   Uns32  _NAME;   Bool SETBIT(_NAME);
#define VMI_UNS64_PARAM(_NAME)   Uns64  _NAME;   Bool SETBIT(_NAME);
#define VMI_PTR_PARAM(_NAME)     void * _NAME;   Bool SETBIT(_NAME);
#define VMI_DBL_PARAM(_NAME)     double _NAME;   Bool SETBIT(_NAME);
#define VMI_ENUM_PARAM(_NAME)    Uns32  _NAME;   Bool SETBIT(_NAME);
#define VMI_ENDIAN_PARAM(_NAME)  Uns32  _NAME;   Bool SETBIT(_NAME);
#define VMI_STRING_PARAM(_NAME)  char * _NAME;

//
// Min/Max values
//
#define VMI_MAXS32 (0x7FFFFFFF)
#define VMI_MINS32 (-VMI_MAXS32-1)
#define VMI_MAXU32 (-1)
#define VMI_MAXU64 (-1LL)


