.global __libc_sigsetjmp_asm
.type __libc_sigsetjmp_asm,@function
__libc_sigsetjmp_asm:
	cbz x1,__libc_setjmp_asm

	str x30,[x0,#176]
	str x19,[x0,#176+8+8]
	mov x19,x0

	bl __libc_setjmp_asm

	mov w1,w0
	mov x0,x19
	ldr x30,[x0,#176]
	ldr x19,[x0,#176+8+8]

.hidden __libc_sigsetjmp_tail
	b __libc_sigsetjmp_tail
