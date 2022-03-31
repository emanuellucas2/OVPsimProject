
.text
.globl  undefexception
.globl  _start

undefexception:
	addi zero, zero, 0
_exit:
	addi zero, zero, 0
	# exit syscall=93
	addi a7, zero, 93
	ecall
_start:
	addi zero, zero, 0
