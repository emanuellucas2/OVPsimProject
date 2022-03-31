/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#ifndef __EXCHANGE_DATA_STRUCT_H
#define __EXCHANGE_DATA_STRUCT_H

#ifdef _PSE_
#include "peripheral/impTypes.h"
#else
#include "hostapi/impTypes.h"
#endif

#define FRAME_DATA_MAX 32

struct sFrameData
{
    Uns32 data[FRAME_DATA_MAX];
    Uns32 length;
};
typedef struct sFrameData tFrameData;

struct sExchangeDataStruct
{
    tFrameData  fd;
    Uns32       time;
    Uns32       endSimulation;
    Uns32       num;
};
typedef struct sExchangeDataStruct tExchangeDataStruct;


#endif
