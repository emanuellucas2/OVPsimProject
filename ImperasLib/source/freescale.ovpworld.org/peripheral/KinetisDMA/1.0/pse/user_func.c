/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "user_func.h"

//////////////////////////////////////////////////////////////////////////////
//
// The following define a fifo for use by the DMAThread. The current implemention
// just adds the latest request to the end of the que, and will take the next
// one off the top.
//////////////////////////////////////////////////////////////////////////////
#define QUE_ELEMENTS 100
#define QUE_SIZE (QUE_ELEMENTS + 1)

Uns32 requestQue[QUE_SIZE];
Uns32 queIn, queOut;


void initRequestQue(void)
{
    queIn = 0;
    queOut = 0;
}

Uns32 addRequest(Uns32 val)
{
    if (queIn == (( queOut - 1 + QUE_SIZE) % QUE_SIZE))
    {
        return (Uns32) -1; // queuFull
    }

    requestQue[queIn] = val;
    queIn = (queIn + 1) % QUE_SIZE;

    return 0;
}

Uns32 popRequest(Uns32 *val)
{
    if (isEmptyQue())
    {
        return (Uns32) -1;
    }

    *val = requestQue[queOut];
    queOut = (queOut + 1) % QUE_SIZE;

    return 0;
}

Uns32 isEmptyQue(void)
{
    return (queIn == queOut);
}
