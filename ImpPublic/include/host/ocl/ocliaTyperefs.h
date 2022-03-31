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


#ifndef OCLIATYPEREFS_H
#define OCLIATYPEREFS_H


////////////////////////////////////////////////////////////////////////////////
// Opaque Structure References
////////////////////////////////////////////////////////////////////////////////

typedef struct octiaAttrS               *octiaAttrP             , **octiaAttrPP;
typedef struct octiaFetchRecordS        *octiaFetchRecordP      , **octiaFetchRecordPP;
typedef struct octiaRawRangeS           *octiaRawRangeP         , **octiaRawRangePP;
typedef struct octiaRegListS            *octiaRegListP          , **octiaRegListPP;
typedef struct octiaNextPCS             *octiaNextPCP           , **octiaNextPCPP;
typedef struct octiaMemAccessS          *octiaMemAccessP        , **octiaMemAccessPP;
typedef struct octiaRegInfoS            *octiaRegInfoP          , **octiaRegInfoPP;


////////////////////////////////////////////////////////////////////////////////
// Public structure forward references
////////////////////////////////////////////////////////////////////////////////

typedef struct octiaAddrExpExtendS       *octiaAddrExpExtendP    , **octiaAddrExpExtendPP;
typedef struct octiaAddrExpUnaryS        *octiaAddrExpUnaryP     , **octiaAddrExpUnaryPP;
typedef struct octiaAddrExpBinaryS       *octiaAddrExpBinaryP    , **octiaAddrExpBinaryPP;
typedef struct octiaAddrExpLoadS         *octiaAddrExpLoadP      , **octiaAddrExpLoadPP;
typedef struct octiaAddrExpS             *octiaAddrExpP          , **octiaAddrExpPP;

#endif /* OCLIATYPEREFS_H */

