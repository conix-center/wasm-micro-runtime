.global __libc_sigsetjmp_asm
.type __libc_sigsetjmp_asm,@function
__libc_sigsetjmp_asm:
	test %esi,%esi
	jz 1f

	popq 64(%rdi)
	mov %rbx,72+8(%rdi)
	mov %rdi,%rbx

	call __libc_setjmp_asm@PLT

	pushq 64(%rbx)
	mov %rbx,%rdi
	mov %eax,%esi
	mov 72+8(%rbx),%rbx

.hidden __libc_sigsetjmp_tail
	jmp __libc_sigsetjmp_tail

1:	jmp __libc_setjmp_asm@PLT
