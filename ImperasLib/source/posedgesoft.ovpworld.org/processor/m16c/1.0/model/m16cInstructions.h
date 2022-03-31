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


// Definition of masks for m16c instructions

#ifndef M16C_INSTRUCTIONS_H
#define M16C_INSTRUCTIONS_H

//
// strip _VEC, _HI downto _LO, and position at _ORIGIN
//
#define VECINDEX(_VEC, _HI, _LO, _ORIGIN) (((Uns32) -1 >> (31 - (_HI) + (_LO))) & ((_VEC) >> (_LO))) << _ORIGIN

//
// Sign extend _VEC, from _POS all the way to left
//
#define SEXTEND(_VEC, _POS) ((Int32)(0x80000000 & ((_VEC) << (31 - (_POS)))) >> (31 - (_POS))) | (_VEC)

//
// ZERO extend _VEC, after _POS all the way left
//
#define ZERO(_VEC, _POS) ((Uns32)((_VEC) << (31 - (_POS))) >> (31 - (_POS)))

//
// SHIFTL _VEC _SHIFT
//
#define SHIFTL(_VEC, _SHIFT) ((Uns32)((_VEC) << (_SHIFT)))

//
// SHIFTR _VEC _SHIFT
//
#define SHIFTR(_VEC, _SHIFT) ((Uns32)((_VEC) >> (_SHIFT)))

#endif

