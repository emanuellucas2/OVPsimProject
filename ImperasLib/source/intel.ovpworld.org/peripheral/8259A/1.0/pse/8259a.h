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

#ifndef I8259A_H_
#define I8259A_H_

#define PREFIX "I8259"

#define D0 0x01
#define D1 0x02
#define D2 0x04
#define D3 0x08
#define D4 0x10
#define D5 0x20
#define D6 0x40
#define D7 0x80

enum {ready, icw2, icw3, icw4} nextState;

typedef struct regS {
    union {
        Uns8 byte;
        struct {
            unsigned ic4 : 1;
            unsigned sngl : 1;
            unsigned adi : 1;
            unsigned ltim : 1;
            unsigned d4 : 1;
            unsigned a7to5 : 3;
        } bits;
    } icw1;
    union {
        Uns8 byte;
        struct {
            unsigned a10to8 : 3;
            unsigned a15to11: 5;
        } bits;
    } icw2;
    union {
        Uns8 byte;
        struct {
            unsigned s0 : 1;
            unsigned s1 : 1;
            unsigned s2 : 1;
            unsigned s3 : 1;
            unsigned s4 : 1;
            unsigned s5 : 1;
            unsigned s6 : 1;
            unsigned s7 : 1;
        } bits;
    } icw3;
    union {
        Uns8 byte;
        struct {
            unsigned upm : 1;
            unsigned aeoi : 1;
            unsigned ms : 1;
            unsigned buf : 1;
            unsigned sfnm : 1;
        } bits;
    } icw4;
    union {
        Uns8 byte;
        struct {
            unsigned m0 : 1;
            unsigned m1 : 1;
            unsigned m2 : 1;
            unsigned m3 : 1;
            unsigned m4 : 1;
            unsigned m5 : 1;
            unsigned m6 : 1;
            unsigned m7 : 1;
        } bits;
    } ocw1;
    union {
        Uns8 byte;
        struct {
            unsigned l : 3;
            unsigned unused0 : 2;
            unsigned eoi : 1;
            unsigned sl : 1;
            unsigned r : 1;
        } bits;
    } ocw2;
    union {
        Uns8 byte;
        struct {
            unsigned ris : 1;
            unsigned rr : 1;
            unsigned p : 1;
            unsigned unused0 : 2;
            unsigned smm : 1;
            unsigned esmm : 1;
        } bits;
    } ocw3;
    Uns8 irr;
    Uns8 isr;
    Uns8 priority[8];
    Uns8 irqack;
} regT;

//
// Upper 8bits contain last value, lower 8 bits current value
//
typedef struct pinS {
    union {
        Uns8 byte;
        struct {
            unsigned value : 1;
            unsigned last  : 1;
        };
    } ir[8];
    Uns8 intp;
    Bool intack;
    Bool eoi;
} pinT;

static regT reg;
static pinT pin;


#endif /* I8259A_H_ */
