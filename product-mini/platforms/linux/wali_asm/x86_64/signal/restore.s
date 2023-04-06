.global __wali_restore_rt
.global __wali_restore
.type __wali_restore_rt,@function
.type __wali_restore,@function
__wali_restore_rt:
__wali_restore:
	movl $15, %eax
	syscall
