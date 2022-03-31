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

.global _start
_start:	l.addi		r1,r2,0
		l.addi		r1,r2,1
		l.addi		r1,r2,-1
		l.addic		r1,r2,1
		l.addic		r1,r2,-1
		l.addic		r1,r2,0
		l.andi		r1,r2,1
		l.andi		r1,r2,-1
		l.andi		r1,r2,0
		l.ori		r1,r2,1
		l.ori		r1,r2,-1
		l.ori		r1,r2,0
		l.xori		r1,r2,1
		l.xori		r1,r2,-1
		l.xori		r1,r2,0
		l.muli		r1,r2,1
		l.muli		r1,r2,-1
		l.muli		r1,r2,0
.global exit
exit:
		l.addi		r1,r2,0

