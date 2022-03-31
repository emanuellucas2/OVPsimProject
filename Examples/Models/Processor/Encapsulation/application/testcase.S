#
# Example Assembler code
#

.org 0x100
.label _start
	movlo r0, 0x0
	movhi r0, 0x0

	movr r1, r0
	movr r2, r0
	movr r3, r0
	movr r4, r0
	movr r5, r0
	movr r6, r0
	movr r7, r0

#
# Loop for <n>
#
	movhi r7, 0x0000
	movlo r7, 0x0010

.label loop1
	movlo r0, 0x1000
	movlo r1, 0x0100

	add r2, r1, r0
	sub r3, r2, r1

	movlo r0, LO(loop1)
	movhi r0, HI(loop1)

	movhi r1, 0x0
	movlo r1, 0x1
	sub r7, r7, r1
	bgt r0, r7, r5

.label exit
	halt
