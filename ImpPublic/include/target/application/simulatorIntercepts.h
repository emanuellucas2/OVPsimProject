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


#ifndef SIMULATORINTERCEPTS_H
#define SIMULATORINTERCEPTS_H

#ifndef INTERCEPT_NORETURN
  #define INTERCEPT_NORETURN __attribute__((noreturn))
#endif

//
// Find the processor id from the platform configuration
//
int impProcessorId(void);

//
// Get the number of simulated instructions
//
int impProcessorInstructionCount(void);

// DEPRECATED/INTERNAL intercepts

// Exclude from Doxygen document
// @cond

//
// old way (pre gdb) of dumping cpu registers to stdout
//
void impReport(unsigned long value);

//
// atomic exchange
//
void impExchange(int *pFlag, int *pValue);

//
// synchronize the current processor (for MP)
//
void impMpSync(void);

//
// identify that the current processor is idling waiting for
// external stimulus
//
void impMpIdle(void);


//
// finish simulation
//
void INTERCEPT_NORETURN impFinish(void);

// @endcond

#endif
