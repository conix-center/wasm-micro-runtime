
/***** Atomics *****/
int wali_a_cas (wasm_exec_env_t exec_env, long p, int t, int s) {
  ATOM(a_cas);
	__asm__ __volatile__ (
		"lock ; cmpxchg %3, %1"
		: "=a"(t), "=m"(*MADDR(p)) : "a"(t), "r"(s) : "memory" );
	return t;

}

int wali_a_cas_p (wasm_exec_env_t exec_env, long p, long t, long s) {
  ATOM(a_cas_p);
  Addr tm = MADDR(t);
	__asm__( "lock ; cmpxchg %3, %1"
		: "=a"(tm), "=m"(*(void *volatile *)MADDR(p))
		: "a"(tm), "r"(MADDR(s)) : "memory" );
	return WADDR(tm);
}

int wali_a_swap (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_swap);
	__asm__ __volatile__(
		"xchg %0, %1"
		: "=r"(v), "=m"(*MADDR(p)) : "0"(v) : "memory" );
	return v;
}

int wali_a_fetch_add (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_fetch_add);
	__asm__ __volatile__(
		"lock ; xadd %0, %1"
		: "=r"(v), "=m"(*MADDR(p)) : "0"(v) : "memory" );
	return v;
}

void wali_a_and (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_and);
	__asm__ __volatile__(
		"lock ; and %1, %0"
		: "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_or (wasm_exec_env_t exec_env, long p, int v) {
  ATOM(a_or);
	__asm__ __volatile__(
		"lock ; or %1, %0"
		: "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_and_64 (wasm_exec_env_t exec_env, long p, long v) {
  ATOM(a_and_64);
	__asm__ __volatile(
		"lock ; and %1, %0"
		 : "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_or_64 (wasm_exec_env_t exec_env, long p, long v) {
  ATOM(a_or_64);
	__asm__ __volatile__(
		"lock ; or %1, %0"
		 : "=m"(*MADDR(p)) : "r"(v) : "memory" );
}

void wali_a_inc (wasm_exec_env_t exec_env, long p) {
  ATOM(a_inc);
  Addr pm = MADDR(p);
	__asm__ __volatile__(
		"lock ; incl %0"
		: "=m"(*pm) : "m"(*pm) : "memory" );
}

void wali_a_dec (wasm_exec_env_t exec_env, long p) {
  ATOM(a_dec);
  Addr pm = MADDR(p);
	__asm__ __volatile__(
		"lock ; decl %0"
		: "=m"(*pm) : "m"(*pm) : "memory" );
}

void wali_a_store (wasm_exec_env_t exec_env, long p, int x) {
  ATOM(a_store);
	__asm__ __volatile__(
		"mov %1, %0 ; lock ; orl $0,(%%rsp)"
		: "=m"(*MADDR(p)) : "r"(x) : "memory" );
}

void wali_a_barrier (wasm_exec_env_t exec_env) {
  ATOM(a_barrier);
	__asm__ __volatile__( "" : : : "memory" );
}

void wali_a_spin (wasm_exec_env_t exec_env) {
  ATOM(a_spin);
	__asm__ __volatile__( "pause" : : : "memory" );
}

void wali_a_crash (wasm_exec_env_t exec_env) {
  ATOM(a_crash);
	__asm__ __volatile__( "hlt" : : : "memory" );
}

int wali_a_ctz_64 (wasm_exec_env_t exec_env, long x) {
  ATOM(a_ctz_64);
	__asm__( "bsf %1,%0" : "=r"(x) : "r"(x) );
	return x;
}

int wali_a_clz_64 (wasm_exec_env_t exec_env, long x) {
  ATOM(a_clz_64);
	__asm__( "bsr %1,%0 ; xor $63,%0" : "=r"(x) : "r"(x) );
	return x;
}

/*************************/
