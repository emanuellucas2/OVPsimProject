/*
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


#ifndef GEM_MACB_H
#define GEM_MACB_H

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#else
#    include "hostapi/impTypes.h"
#endif


// MAC Tx status information
typedef union GemTxStatusS {
    unsigned int value;
    struct {
        unsigned int jabber_timeout:1;
        unsigned int underflow_error:1;
        unsigned int frame_flushed:1;
        unsigned int vlan_frame:1;
        unsigned int ip_header_error:1;
        unsigned int payload_error:1;
        unsigned int no_carrier:1;
    } bits;
} GemTxStatusT;

// MAC Rx status information
typedef union GemRxStatusS {
    unsigned int value;
    struct {
        unsigned int frame_length:14;
        unsigned int start_of_frame:1;
        unsigned int end_of_frame:1;
        unsigned int frame_type:1;
        unsigned int vlan_tag:1;
        unsigned int sa_filter_fail:1;
        unsigned int da_filter_fail:1;
        unsigned int length_error:1;
        unsigned int overflow_error:1;
        unsigned int receive_watchdog:1;
        unsigned int crc_error:1;
//      unsigned int dribbling:1;
//      unsigned int error_gmii:1;
//      unsigned int late_collision:1;
        unsigned int ipc_csum_error:1;
        unsigned int payload_csum_error:1;
    } bits;
} GemRxStatusT;

void gemMacbInit(void);

GemTxStatusT  gemMacbWriteData(void *data, unsigned int len);

int gemMacbCanRead(void);
GemRxStatusT gemMacbReadData(void *buf, unsigned int bufSize);

void updateInts(void);


#endif
