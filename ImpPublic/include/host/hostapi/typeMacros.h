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

#ifdef _PSE_
#error "This header file should not be included in Peripheral PSE code"
#endif

#ifndef TYPEMACROS_H
#define TYPEMACROS_H

#define DEFINE_S(t)   typedef       struct t##S  * t##P,  ** t##PP
#define DEFINE_U(t)   typedef       union  t##U  * t##P,  ** t##PP
#define DEFINE_E(t)   typedef       enum   t##E  * t##P,  ** t##PP
#define DEFINE_CS(t)  typedef const struct t##S  * t##CP, ** t##CPP
#define DEFINE_CU(t)  typedef const union  t##U  * t##CP, ** t##CPP
#define DEFINE_CE(t)  typedef const enum   t##E  * t##CP, ** t##CPP

#endif /*TYPEMACROS_H*/
