.global __libc_sigsetjmp_asm
.type __libc_sigsetjmp_asm,@function
__libc_sigsetjmp_asm:
	bnez a1, 1f
	tail __libc_setjmp_asm
1:

	sd ra, 208(a0)
	sd s0, 224(a0)
	mv s0, a0

	call __libc_setjmp_asm

	mv a1, a0
	mv a0, s0
	ld s0, 224(a0)
	ld ra, 208(a0)

.hidden __libc_sigsetjmp_tail
	tail __libc_sigsetjmp_tail

