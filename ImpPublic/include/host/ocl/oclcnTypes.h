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


#ifndef OCLCNTYPES_H
#define OCLCNTYPES_H


////////////////////////////////////////////////////////////////////////////////
// Public structure forward references
////////////////////////////////////////////////////////////////////////////////

typedef struct octcnConnInfoS            *octcnConnInfoP         , **octcnConnInfoPP;


////////////////////////////////////////////////////////////////////////////////
// Public structures
////////////////////////////////////////////////////////////////////////////////

/// @struct octcnConnInfoS
/// Describes the state of a FIFO

typedef struct octcnConnInfoS {

    Uns32 words    ; ///< number of words that the FIFO can hold
    Uns32 bits     ; ///< width in bits of one word
    Uns32 numFilled; ///< number of words with data in them
    Uns32 numEmpty ; ///< number of free words 
    Uns32 inputs   ; ///< number of connected inputs
    Uns32 outputs  ; ///< number of connected outputs

} octcnConnInfo;



#endif /* OCLCNTYPES_H */

