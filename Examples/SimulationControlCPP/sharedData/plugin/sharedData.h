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

/*
 * This data is used used by both the platform and the plug-in
 */

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include "hostapi/impTypes.h"


typedef struct sharedDataContainerS {

    const char *object1;
    const char *object2;
    
} sharedDataContainer, *sharedDataContainerP;

#endif
