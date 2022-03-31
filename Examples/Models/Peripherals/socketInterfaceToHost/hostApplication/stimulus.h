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

#ifndef _STIMULUS_H_
#define _STIMULUS_H_

#include "exchangeData.h"

#define BUFFSIZE 256

typedef struct inS {
    FILE          *fp;      // This is the FILE pointer to the associated file stream, either NULL or non-NULL
    unsigned int   now;     // Time at which Value is valid (now)
    unsigned int   next;    // Next time for transfer
} inT, *inP;

#if (IMPERAS_LINUX==1)
#define INT_MAX   (Int32)(-1)
#define ULONG_MAX (Uns32)(-1)
#endif

tExchangeDataStruct xchngDataIn;
tExchangeDataStruct xchngDataOut;

#define STEP 2000

int setNextStimLine(void);

int initStim(const char *);
int closeStim(void);

#endif
