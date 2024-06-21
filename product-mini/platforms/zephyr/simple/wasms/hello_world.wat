(module $hello_world.wasm
  (type (;0;) (func))
  (type (;1;) (func (param i32 i32) (result i32)))
  (type (;2;) (func (param i32)))
  (type (;3;) (func (param i32) (result i32)))
  (type (;4;) (func (result i32)))
  (type (;5;) (func (param i32 i32 i32) (result i32)))
  (type (;6;) (func (param f64 i32 i32 i32) (result i32)))
  (type (;7;) (func (param i32 i32 i32)))
  (type (;8;) (func (param i64 i32 i32) (result i32)))
  (type (;9;) (func (param f64 i32 i32 i32 i32) (result i32)))
  (type (;10;) (func (param i64 i32 i32 i32 i32 i32) (result i64)))
  (type (;11;) (func (param i64) (result i64)))
  (type (;12;) (func (param i64) (result i32)))
  (type (;13;) (func (param i64 i32 i32) (result i64)))
  (type (;14;) (func (param i32 i32)))
  (type (;15;) (func (param i64 i64 i32) (result i64)))
  (type (;16;) (func (param i32 i64 i64 i32)))
  (type (;17;) (func (param i32 i64 i64 i64 i64)))
  (import "wazi" "SYS_zephyr_fputc" (func $zephyr_fputc (type 1)))
  (func $__wasm_call_ctors (type 0))
  (func $__wasm_init_tls (type 2) (param i32))
  (func $undefined_weak:_init (type 0)
    unreachable)
  (func $__wasm_init_memory (type 0)
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          i32.const 1988
          i32.const 0
          i32.const 1
          i32.atomic.rmw.cmpxchg
          br_table 0 (;@3;) 1 (;@2;) 2 (;@1;)
        end
        i32.const 1024
        i32.const 0
        i32.const 916
        memory.init $.rodata
        i32.const 1940
        i32.const 0
        i32.const 28
        memory.init $.data
        i32.const 1968
        i32.const 0
        i32.const 17
        memory.fill
        i32.const 1988
        i32.const 2
        i32.atomic.store
        i32.const 1988
        i32.const -1
        memory.atomic.notify
        drop
        br 1 (;@1;)
      end
      i32.const 1988
      i32.const 1
      i64.const -1
      memory.atomic.wait32
      drop
    end
    data.drop $.rodata
    data.drop $.data)
  (func $__wasm_memory_grow (type 3) (param i32) (result i32)
    local.get 0
    memory.grow)
  (func $__wasm_memory_size (type 4) (result i32)
    memory.size)
  (func $_start (type 0)
    i32.const 0
    i32.const 0
    i32.const 0
    call $memcpy
    drop
    i32.const 0
    i32.const 0
    i32.const 0
    call $memset
    drop
    call $__libc_init_array
    i32.const 0
    i32.const 0
    call $main
    drop)
  (func $__original_main (type 4) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 0
    i32.const 48
    local.set 1
    local.get 0
    local.get 1
    i32.sub
    local.set 2
    local.get 2
    global.set $__stack_pointer
    i32.const 0
    local.set 3
    local.get 2
    local.get 3
    i32.store offset=44
    i32.const 10
    local.set 4
    local.get 4
    call $malloc
    local.set 5
    local.get 2
    local.get 5
    i32.store offset=40
    i32.const 40
    local.set 6
    local.get 6
    call $malloc
    local.set 7
    local.get 2
    local.get 7
    i32.store offset=36
    i32.const 0
    local.set 8
    local.get 2
    local.get 8
    i32.store offset=32
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=32
        local.set 9
        i32.const 10
        local.set 10
        local.get 9
        local.set 11
        local.get 10
        local.set 12
        local.get 11
        local.get 12
        i32.lt_s
        local.set 13
        i32.const 1
        local.set 14
        local.get 13
        local.get 14
        i32.and
        local.set 15
        local.get 15
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        i32.load offset=32
        local.set 16
        i32.const 63
        local.set 17
        local.get 16
        local.get 17
        i32.mul
        local.set 18
        local.get 2
        i32.load offset=36
        local.set 19
        local.get 2
        i32.load offset=32
        local.set 20
        i32.const 2
        local.set 21
        local.get 20
        local.get 21
        i32.shl
        local.set 22
        local.get 19
        local.get 22
        i32.add
        local.set 23
        local.get 23
        local.get 18
        i32.store
        local.get 2
        i32.load offset=32
        local.set 24
        i32.const 1
        local.set 25
        local.get 24
        local.get 25
        i32.add
        local.set 26
        local.get 2
        local.get 26
        i32.store offset=32
        br 0 (;@2;)
      end
    end
    i32.const 35
    local.set 27
    local.get 2
    local.get 27
    i32.store offset=28
    local.get 2
    i32.load offset=40
    local.set 28
    i32.const 1032
    local.set 29
    local.get 28
    local.get 29
    call $strcpy
    drop
    i32.const 1052
    local.set 30
    i32.const 0
    local.set 31
    local.get 30
    local.get 31
    call $printf
    drop
    local.get 2
    i32.load offset=40
    local.set 32
    local.get 2
    i32.load offset=28
    local.set 33
    local.get 2
    local.get 33
    i32.store offset=20
    local.get 2
    local.get 32
    i32.store offset=16
    i32.const 1065
    local.set 34
    i32.const 16
    local.set 35
    local.get 2
    local.get 35
    i32.add
    local.set 36
    local.get 34
    local.get 36
    call $printf
    drop
    i32.const 0
    local.set 37
    local.get 2
    local.get 37
    i32.store offset=24
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=24
        local.set 38
        i32.const 10
        local.set 39
        local.get 38
        local.set 40
        local.get 39
        local.set 41
        local.get 40
        local.get 41
        i32.lt_s
        local.set 42
        i32.const 1
        local.set 43
        local.get 42
        local.get 43
        i32.and
        local.set 44
        local.get 44
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        i32.load offset=24
        local.set 45
        local.get 2
        i32.load offset=36
        local.set 46
        local.get 2
        i32.load offset=24
        local.set 47
        i32.const 2
        local.set 48
        local.get 47
        local.get 48
        i32.shl
        local.set 49
        local.get 46
        local.get 49
        i32.add
        local.set 50
        local.get 50
        i32.load
        local.set 51
        local.get 2
        local.get 51
        i32.store offset=4
        local.get 2
        local.get 45
        i32.store
        i32.const 1091
        local.set 52
        local.get 52
        local.get 2
        call $printf
        drop
        local.get 2
        i32.load offset=24
        local.set 53
        i32.const 1
        local.set 54
        local.get 53
        local.get 54
        i32.add
        local.set 55
        local.get 2
        local.get 55
        i32.store offset=24
        br 0 (;@2;)
      end
    end
    i32.const 0
    local.set 56
    i32.const 48
    local.set 57
    local.get 2
    local.get 57
    i32.add
    local.set 58
    local.get 58
    global.set $__stack_pointer
    local.get 56
    return)
  (func $picolibc_putc (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get $__stack_pointer
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    global.set $__stack_pointer
    local.get 4
    local.get 0
    i32.store8 offset=15
    local.get 4
    local.get 1
    i32.store offset=8
    local.get 4
    i32.load8_u offset=15
    local.set 5
    i32.const 24
    local.set 6
    local.get 5
    local.get 6
    i32.shl
    local.set 7
    local.get 7
    local.get 6
    i32.shr_s
    local.set 8
    local.get 4
    i32.load offset=8
    local.set 9
    local.get 8
    local.get 9
    call $zephyr_fputc
    drop
    i32.const 0
    local.set 10
    i32.const 16
    local.set 11
    local.get 4
    local.get 11
    i32.add
    local.set 12
    local.get 12
    global.set $__stack_pointer
    local.get 10
    return)
  (func $main (type 1) (param i32 i32) (result i32)
    (local i32)
    call $__original_main
    local.set 2
    local.get 2
    return)
  (func $free (type 2) (param i32)
    (local i32 i32 i32)
    block  ;; label = @1
      local.get 0
      i32.eqz
      br_if 0 (;@1;)
      local.get 0
      i32.const 0
      i32.store
      i32.const 1984
      call $__retarget_lock_acquire_recursive
      local.get 0
      i32.const -4
      i32.add
      local.set 1
      i32.const 1976
      local.set 2
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            loop  ;; label = @5
              local.get 2
              i32.load
              local.tee 3
              i32.eqz
              br_if 1 (;@4;)
              local.get 1
              local.get 3
              i32.lt_u
              br_if 1 (;@4;)
              block  ;; label = @6
                local.get 3
                local.get 3
                i32.load
                local.tee 2
                i32.add
                local.get 1
                i32.ne
                br_if 0 (;@6;)
                local.get 3
                local.get 1
                i32.load
                local.get 2
                i32.add
                local.tee 2
                i32.store
                local.get 3
                local.set 1
                local.get 3
                i32.load offset=4
                local.set 3
                br 3 (;@3;)
              end
              block  ;; label = @6
                local.get 1
                local.get 3
                i32.ne
                br_if 0 (;@6;)
                i32.const 0
                i32.const 12
                i32.store offset=1980
                br 4 (;@2;)
              end
              local.get 3
              i32.const 4
              i32.add
              local.set 2
              br 0 (;@5;)
            end
          end
          local.get 0
          local.get 3
          i32.store
          local.get 2
          local.get 1
          i32.store
          local.get 1
          i32.load
          local.set 2
        end
        local.get 1
        local.get 2
        i32.add
        local.get 3
        i32.ne
        br_if 0 (;@2;)
        local.get 1
        local.get 3
        i32.load offset=4
        i32.store offset=4
        local.get 1
        local.get 3
        i32.load
        local.get 2
        i32.add
        i32.store
      end
      i32.const 1984
      call $__retarget_lock_release_recursive
    end)
  (func $__malloc_sbrk_aligned (type 3) (param i32) (result i32)
    (local i32 i32 i32)
    i32.const -1
    local.set 1
    block  ;; label = @1
      local.get 0
      i32.const 0
      i32.lt_s
      br_if 0 (;@1;)
      local.get 0
      call $sbrk
      local.tee 2
      i32.const -1
      i32.eq
      br_if 0 (;@1;)
      i32.const 0
      local.get 2
      local.get 0
      i32.add
      local.tee 3
      i32.store offset=1968
      block  ;; label = @2
        local.get 2
        i32.const 11
        i32.add
        i32.const -8
        i32.and
        i32.const -4
        i32.add
        local.tee 0
        local.get 2
        i32.eq
        br_if 0 (;@2;)
        local.get 0
        local.get 2
        i32.sub
        local.tee 2
        call $sbrk
        local.get 3
        i32.ne
        br_if 1 (;@1;)
        i32.const 0
        local.get 3
        local.get 2
        i32.add
        i32.store offset=1968
      end
      block  ;; label = @2
        i32.const 0
        i32.load offset=1972
        br_if 0 (;@2;)
        i32.const 0
        local.get 0
        i32.store offset=1972
      end
      local.get 0
      local.set 1
    end
    local.get 1)
  (func $__malloc_grow_chunk (type 1) (param i32 i32) (result i32)
    (local i32 i32)
    block  ;; label = @1
      local.get 0
      local.get 0
      i32.load
      local.tee 2
      i32.add
      local.tee 3
      i32.const 0
      i32.load offset=1968
      i32.ne
      br_if 0 (;@1;)
      block  ;; label = @2
        local.get 1
        local.get 2
        i32.sub
        local.tee 1
        i32.const 8
        local.get 1
        i32.const 8
        i32.gt_u
        select
        local.tee 2
        call $__malloc_sbrk_aligned
        local.tee 1
        local.get 3
        i32.ne
        br_if 0 (;@2;)
        local.get 0
        local.get 0
        i32.load
        local.get 2
        i32.add
        i32.store
        i32.const 1
        return
      end
      local.get 1
      i32.const -1
      i32.eq
      br_if 0 (;@1;)
      local.get 1
      local.get 2
      i32.store
      local.get 1
      i32.const 4
      i32.add
      call $free
    end
    i32.const 0)
  (func $malloc (type 3) (param i32) (result i32)
    (local i32 i32 i32 i32 i32)
    block  ;; label = @1
      local.get 0
      i32.const -20
      i32.lt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 12
      i32.store offset=1980
      i32.const 0
      return
    end
    i32.const 1984
    call $__retarget_lock_acquire_recursive
    local.get 0
    i32.const 7
    i32.add
    i32.const -8
    i32.and
    local.tee 1
    i32.const 8
    i32.add
    local.set 2
    i32.const 1976
    local.set 3
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          loop  ;; label = @4
            local.get 3
            local.tee 4
            i32.load
            local.tee 0
            i32.eqz
            br_if 1 (;@3;)
            block  ;; label = @5
              local.get 0
              i32.load
              local.tee 3
              local.get 2
              i32.lt_u
              br_if 0 (;@5;)
              block  ;; label = @6
                local.get 3
                local.get 2
                i32.sub
                local.tee 3
                i32.const 8
                i32.lt_u
                br_if 0 (;@6;)
                local.get 0
                local.get 2
                i32.add
                local.tee 5
                local.get 0
                i32.load offset=4
                i32.store offset=4
                local.get 5
                local.get 3
                i32.store
                local.get 4
                local.get 5
                i32.store
                br 4 (;@2;)
              end
              local.get 4
              local.get 0
              i32.load offset=4
              i32.store
              br 4 (;@1;)
            end
            local.get 0
            i32.const 4
            i32.add
            local.set 3
            local.get 0
            i32.load offset=4
            br_if 0 (;@4;)
            local.get 0
            local.get 2
            call $__malloc_grow_chunk
            i32.eqz
            br_if 0 (;@4;)
          end
          local.get 4
          local.get 3
          i32.load
          i32.store
          br 2 (;@1;)
        end
        local.get 2
        call $__malloc_sbrk_aligned
        local.tee 0
        i32.const -1
        i32.ne
        br_if 0 (;@2;)
        i32.const 0
        i32.const 12
        i32.store offset=1980
        i32.const 1984
        call $__retarget_lock_release_recursive
        i32.const 0
        return
      end
      local.get 0
      local.get 2
      i32.store
    end
    i32.const 1984
    call $__retarget_lock_release_recursive
    local.get 0
    i32.const 4
    i32.add
    local.tee 0
    i32.const 0
    local.get 1
    i32.const 4
    i32.or
    memory.fill
    local.get 0)
  (func $__libc_init_array (type 0)
    (local i32 i32)
    i32.const 0
    local.set 0
    i32.const 0
    i32.const 0
    i32.sub
    i32.const 2
    i32.shr_s
    local.set 1
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.load
        call_indirect (type 0)
        local.get 0
        i32.const 4
        i32.add
        local.set 0
        local.get 1
        i32.const -1
        i32.add
        local.set 1
        br 0 (;@2;)
      end
    end
    block  ;; label = @1
      i32.const 0
      i32.eqz
      br_if 0 (;@1;)
      call $undefined_weak:_init
    end
    i32.const 0
    local.set 0
    i32.const 0
    i32.const 0
    i32.sub
    i32.const 2
    i32.shr_s
    local.set 1
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.load
        call_indirect (type 0)
        local.get 0
        i32.const 4
        i32.add
        local.set 0
        local.get 1
        i32.const -1
        i32.add
        local.set 1
        br 0 (;@2;)
      end
    end)
  (func $__retarget_lock_init (type 2) (param i32))
  (func $__retarget_lock_init_recursive (type 2) (param i32))
  (func $__retarget_lock_close (type 2) (param i32))
  (func $__retarget_lock_close_recursive (type 2) (param i32))
  (func $__retarget_lock_acquire (type 2) (param i32))
  (func $__retarget_lock_acquire_recursive (type 2) (param i32))
  (func $__retarget_lock_release (type 2) (param i32))
  (func $__retarget_lock_release_recursive (type 2) (param i32))
  (func $memcpy (type 5) (param i32 i32 i32) (result i32)
    (local i32)
    i32.const 0
    local.set 3
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        local.get 3
        i32.eq
        br_if 1 (;@1;)
        local.get 0
        local.get 3
        i32.add
        local.get 1
        local.get 3
        i32.add
        i32.load8_u
        i32.store8
        local.get 3
        i32.const 1
        i32.add
        local.set 3
        br 0 (;@2;)
      end
    end
    local.get 0)
  (func $memset (type 5) (param i32 i32 i32) (result i32)
    (local i32)
    i32.const 0
    local.set 3
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        local.get 3
        i32.eq
        br_if 1 (;@1;)
        local.get 0
        local.get 3
        i32.add
        local.get 1
        i32.store8
        local.get 3
        i32.const 1
        i32.add
        local.set 3
        br 0 (;@2;)
      end
    end
    local.get 0)
  (func $strcpy (type 1) (param i32 i32) (result i32)
    (local i32 i32)
    i32.const 0
    local.set 2
    loop  ;; label = @1
      local.get 0
      local.get 2
      i32.add
      local.get 1
      local.get 2
      i32.add
      i32.load8_u
      local.tee 3
      i32.store8
      local.get 2
      i32.const 1
      i32.add
      local.set 2
      local.get 3
      br_if 0 (;@1;)
    end
    local.get 0)
  (func $sbrk (type 3) (param i32) (result i32)
    (local i32)
    i32.const 0
    i32.load offset=1964
    local.set 1
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.const -1
        i32.gt_s
        br_if 0 (;@2;)
        local.get 1
        i32.const 67536
        i32.sub
        i32.const 0
        local.get 0
        i32.sub
        i32.ge_u
        br_if 1 (;@1;)
        i32.const 0
        i32.const 12
        i32.store offset=1980
        i32.const -1
        return
      end
      i32.const 131072
      local.get 1
      i32.sub
      local.get 0
      i32.ge_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 12
      i32.store offset=1980
      i32.const -1
      return
    end
    i32.const 0
    local.get 1
    local.get 0
    i32.add
    i32.store offset=1964
    local.get 1)
  (func $printf (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 2
    global.set $__stack_pointer
    local.get 2
    local.get 1
    i32.store offset=12
    i32.const 0
    i32.load offset=1024
    local.get 0
    local.get 1
    call $vfprintf
    local.set 1
    local.get 2
    i32.const 16
    i32.add
    global.set $__stack_pointer
    local.get 1)
  (func $__dtox_engine (type 6) (param f64 i32 i32 i32) (result i32)
    (local i64 i64 i32 i32 i32 i32 i64 i64)
    local.get 1
    i32.const 48
    i32.store8 offset=5
    local.get 0
    i64.reinterpret_f64
    local.tee 4
    i64.const 52
    i64.shr_u
    local.tee 5
    i32.wrap_i64
    i32.const 2047
    i32.and
    local.set 6
    i32.const 49
    local.set 7
    block  ;; label = @1
      local.get 5
      i64.const 2047
      i64.and
      local.get 4
      i64.const 4503599627370495
      i64.and
      local.tee 5
      i64.or
      i64.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        local.get 6
        br_if 0 (;@2;)
        i32.const -1022
        local.set 6
        br 1 (;@1;)
      end
      local.get 1
      i32.const 49
      i32.store8 offset=5
      local.get 6
      i32.const -1023
      i32.add
      local.set 6
      i32.const 50
      local.set 7
    end
    local.get 1
    local.get 4
    i64.const 63
    i64.shr_u
    i32.wrap_i64
    local.tee 8
    i32.store8 offset=4
    block  ;; label = @1
      block  ;; label = @2
        local.get 2
        i32.const 0
        i32.ge_s
        br_if 0 (;@2;)
        i32.const 0
        local.set 2
        br 1 (;@1;)
      end
      block  ;; label = @2
        local.get 2
        i32.const 12
        i32.le_u
        br_if 0 (;@2;)
        i32.const 13
        local.set 2
        br 1 (;@1;)
      end
      i64.const 0
      i64.const 2
      i32.const 51
      local.get 2
      i32.const 2
      i32.shl
      local.tee 9
      i32.sub
      i64.extend_i32_u
      local.tee 4
      i64.shl
      local.tee 10
      i64.sub
      local.set 11
      block  ;; label = @2
        block  ;; label = @3
          local.get 10
          i64.const -1
          i64.add
          local.get 5
          i64.and
          i64.const 1
          local.get 4
          i64.shl
          local.tee 4
          i64.gt_u
          br_if 0 (;@3;)
          local.get 5
          i32.const 52
          local.get 9
          i32.sub
          i64.extend_i32_u
          i64.shr_u
          i64.const 1
          i64.and
          i64.eqz
          br_if 1 (;@2;)
        end
        local.get 4
        local.get 5
        i64.add
        local.tee 5
        i64.const 4503599627370496
        i64.lt_u
        br_if 0 (;@2;)
        local.get 1
        local.get 7
        i32.store8 offset=5
      end
      local.get 5
      local.get 11
      i64.and
      local.set 5
    end
    block  ;; label = @1
      block  ;; label = @2
        local.get 6
        i32.const 1024
        i32.eq
        br_if 0 (;@2;)
        i32.const 13
        local.set 7
        loop  ;; label = @3
          local.get 7
          i32.eqz
          br_if 2 (;@1;)
          block  ;; label = @4
            block  ;; label = @5
              local.get 5
              i32.wrap_i64
              i32.const 15
              i32.and
              local.tee 8
              br_if 0 (;@5;)
              local.get 7
              local.get 2
              i32.gt_s
              br_if 1 (;@4;)
            end
            local.get 1
            local.get 7
            i32.add
            i32.const 5
            i32.add
            local.get 8
            i32.const 48
            i32.or
            local.get 8
            local.get 3
            i32.sub
            i32.const 87
            i32.add
            local.get 8
            i32.const 10
            i32.lt_u
            select
            i32.store8
            local.get 7
            local.get 2
            local.get 7
            local.get 2
            i32.gt_s
            select
            local.set 2
          end
          local.get 5
          i64.const 4
          i64.shr_u
          local.set 5
          local.get 7
          i32.const -1
          i32.add
          local.set 7
          br 0 (;@3;)
        end
      end
      local.get 1
      i32.const 4
      i32.const 8
      local.get 5
      i64.eqz
      select
      local.get 8
      i32.or
      i32.store8 offset=4
    end
    local.get 1
    local.get 6
    i32.store
    local.get 2)
  (func $strnlen (type 1) (param i32 i32) (result i32)
    (local i32 i32)
    local.get 0
    local.get 1
    i32.add
    local.set 2
    local.get 0
    local.set 3
    loop (result i32)  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 1
          i32.eqz
          br_if 0 (;@3;)
          local.get 3
          i32.load8_u
          br_if 1 (;@2;)
          local.get 3
          local.set 2
        end
        local.get 2
        local.get 0
        i32.sub
        return
      end
      local.get 1
      i32.const -1
      i32.add
      local.set 1
      local.get 3
      i32.const 1
      i32.add
      local.set 3
      br 0 (;@1;)
    end)
  (func $vfprintf (type 5) (param i32 i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 f64 i32 i32 i32 i32 i32 i32 i32 i32 i32 i64 i64)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 3
    global.set $__stack_pointer
    local.get 3
    local.get 2
    i32.store offset=28
    i32.const -1
    local.set 4
    block  ;; label = @1
      local.get 0
      i32.load8_u offset=4
      i32.const 2
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 0
      i32.load offset=8
      local.set 5
      local.get 3
      local.get 3
      i32.load offset=28
      i32.store offset=24
      local.get 3
      i32.const 6
      i32.add
      local.set 6
      local.get 3
      i32.const 5
      i32.add
      local.set 7
      local.get 3
      i32.const -1
      i32.add
      local.set 8
      i32.const 0
      local.set 4
      local.get 1
      local.set 2
      block  ;; label = @2
        loop  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              block  ;; label = @6
                local.get 2
                i32.load8_u
                local.tee 9
                i32.const 37
                i32.eq
                br_if 0 (;@6;)
                local.get 9
                i32.eqz
                br_if 5 (;@1;)
                local.get 2
                i32.const 1
                i32.add
                local.set 2
                br 1 (;@5;)
              end
              local.get 2
              i32.const 2
              i32.add
              local.set 10
              local.get 2
              i32.load8_u offset=1
              local.tee 11
              i32.const 37
              i32.ne
              br_if 1 (;@4;)
              local.get 10
              local.set 2
            end
            local.get 4
            i32.const 1
            i32.add
            local.set 4
            local.get 9
            i32.extend8_s
            local.get 0
            local.get 5
            call_indirect (type 1)
            i32.const 0
            i32.ge_s
            br_if 1 (;@3;)
            br 2 (;@2;)
          end
          i32.const 0
          local.set 12
          i32.const 0
          local.set 13
          i32.const 0
          local.set 14
          i32.const 0
          local.set 9
          block  ;; label = @4
            loop  ;; label = @5
              local.get 10
              local.set 2
              local.get 11
              i32.extend8_s
              local.set 15
              block  ;; label = @6
                block  ;; label = @7
                  block  ;; label = @8
                    block  ;; label = @9
                      block  ;; label = @10
                        block  ;; label = @11
                          block  ;; label = @12
                            block  ;; label = @13
                              local.get 9
                              i32.const 65535
                              i32.and
                              local.tee 10
                              i32.const 31
                              i32.gt_u
                              br_if 0 (;@13;)
                              block  ;; label = @14
                                block  ;; label = @15
                                  block  ;; label = @16
                                    block  ;; label = @17
                                      block  ;; label = @18
                                        block  ;; label = @19
                                          local.get 11
                                          i32.const 255
                                          i32.and
                                          local.tee 16
                                          i32.const -39
                                          i32.add
                                          br_table 13 (;@6;) 7 (;@12;) 7 (;@12;) 7 (;@12;) 2 (;@17;) 7 (;@12;) 4 (;@15;) 7 (;@12;) 7 (;@12;) 1 (;@18;) 0 (;@19;)
                                        end
                                        local.get 16
                                        i32.const -32
                                        i32.add
                                        br_table 2 (;@16;) 6 (;@12;) 6 (;@12;) 4 (;@14;) 6 (;@12;)
                                      end
                                      local.get 9
                                      i32.const 1
                                      i32.or
                                      local.set 9
                                      br 11 (;@6;)
                                    end
                                    local.get 9
                                    i32.const 2
                                    i32.or
                                    local.set 9
                                  end
                                  local.get 9
                                  i32.const 4
                                  i32.or
                                  local.set 9
                                  br 9 (;@6;)
                                end
                                local.get 9
                                i32.const 8
                                i32.or
                                local.set 9
                                br 8 (;@6;)
                              end
                              local.get 9
                              i32.const 16
                              i32.or
                              local.set 9
                              br 7 (;@6;)
                            end
                            local.get 10
                            i32.const 127
                            i32.gt_u
                            br_if 1 (;@11;)
                          end
                          block  ;; label = @12
                            local.get 15
                            i32.const -48
                            i32.add
                            local.tee 16
                            i32.const 9
                            i32.gt_u
                            br_if 0 (;@12;)
                            block  ;; label = @13
                              local.get 10
                              i32.const 64
                              i32.lt_u
                              br_if 0 (;@13;)
                              local.get 16
                              local.get 13
                              i32.const 10
                              i32.mul
                              i32.add
                              local.set 13
                              br 7 (;@6;)
                            end
                            local.get 9
                            i32.const 32
                            i32.or
                            local.set 9
                            local.get 16
                            local.get 14
                            i32.const 10
                            i32.mul
                            i32.add
                            local.set 14
                            br 6 (;@6;)
                          end
                          block  ;; label = @12
                            local.get 11
                            i32.const 255
                            i32.and
                            local.tee 11
                            i32.const -104
                            i32.add
                            br_table 3 (;@9;) 8 (;@4;) 5 (;@7;) 8 (;@4;) 2 (;@10;) 0 (;@12;)
                          end
                          block  ;; label = @12
                            block  ;; label = @13
                              block  ;; label = @14
                                block  ;; label = @15
                                  local.get 11
                                  i32.const -42
                                  i32.add
                                  br_table 1 (;@14;) 11 (;@4;) 11 (;@4;) 11 (;@4;) 2 (;@13;) 0 (;@15;)
                                end
                                local.get 11
                                i32.const 36
                                i32.eq
                                br_if 2 (;@12;)
                                local.get 11
                                i32.const 76
                                i32.eq
                                br_if 6 (;@8;)
                                local.get 11
                                i32.const 116
                                i32.eq
                                br_if 8 (;@6;)
                                local.get 11
                                i32.const 122
                                i32.eq
                                br_if 8 (;@6;)
                                br 10 (;@4;)
                              end
                              local.get 12
                              br_if 7 (;@6;)
                              local.get 3
                              local.get 3
                              i32.load offset=24
                              local.tee 11
                              i32.const 4
                              i32.add
                              i32.store offset=24
                              local.get 11
                              i32.load
                              local.set 11
                              i32.const 0
                              local.set 12
                              block  ;; label = @14
                                local.get 10
                                i32.const 63
                                i32.le_u
                                br_if 0 (;@14;)
                                local.get 11
                                local.set 13
                                br 8 (;@6;)
                              end
                              block  ;; label = @14
                                local.get 11
                                i32.const -1
                                i32.le_s
                                br_if 0 (;@14;)
                                local.get 9
                                i32.const 32
                                i32.or
                                local.set 9
                                local.get 11
                                local.set 14
                                br 8 (;@6;)
                              end
                              local.get 9
                              i32.const 40
                              i32.or
                              local.set 9
                              i32.const 0
                              local.set 12
                              i32.const 0
                              local.get 11
                              i32.sub
                              local.set 14
                              br 7 (;@6;)
                            end
                            local.get 10
                            i32.const 63
                            i32.gt_u
                            br_if 11 (;@1;)
                            local.get 9
                            i32.const 64
                            i32.or
                            local.set 9
                            br 6 (;@6;)
                          end
                          block  ;; label = @12
                            local.get 12
                            br_if 0 (;@12;)
                            i32.const 0
                            local.set 13
                            local.get 14
                            local.set 12
                            i32.const 0
                            local.set 14
                            i32.const 0
                            local.set 9
                            br 6 (;@6;)
                          end
                          local.get 3
                          local.get 3
                          i32.load offset=28
                          i32.store offset=24
                          local.get 1
                          local.get 3
                          i32.const 24
                          i32.add
                          local.get 14
                          local.get 13
                          local.get 10
                          i32.const 64
                          i32.lt_u
                          local.tee 11
                          select
                          call $skip_to_arg
                          local.get 3
                          local.get 3
                          i32.load offset=24
                          local.tee 10
                          i32.const 4
                          i32.add
                          i32.store offset=24
                          local.get 10
                          i32.load
                          local.tee 10
                          local.get 14
                          local.get 11
                          select
                          local.set 14
                          local.get 13
                          local.get 10
                          local.get 11
                          select
                          local.set 13
                          br 5 (;@6;)
                        end
                        block  ;; label = @11
                          local.get 11
                          i32.const 255
                          i32.and
                          local.tee 11
                          i32.const -104
                          i32.add
                          br_table 2 (;@9;) 7 (;@4;) 4 (;@7;) 7 (;@4;) 1 (;@10;) 0 (;@11;)
                        end
                        local.get 11
                        i32.const 76
                        i32.eq
                        br_if 2 (;@8;)
                        local.get 11
                        i32.const 116
                        i32.eq
                        br_if 4 (;@6;)
                        local.get 11
                        i32.const 122
                        i32.eq
                        br_if 4 (;@6;)
                        br 6 (;@4;)
                      end
                      local.get 9
                      local.get 9
                      i32.const 2
                      i32.shl
                      i32.const 512
                      i32.and
                      i32.or
                      i32.const 128
                      i32.or
                      local.set 9
                      br 3 (;@6;)
                    end
                    local.get 9
                    local.get 9
                    i32.const 1
                    i32.shl
                    i32.const 512
                    i32.and
                    i32.or
                    i32.const 256
                    i32.or
                    local.set 9
                    br 2 (;@6;)
                  end
                  local.get 9
                  i32.const 640
                  i32.or
                  local.set 9
                  br 1 (;@6;)
                end
                local.get 9
                i32.const 128
                i32.or
                local.set 9
              end
              local.get 2
              i32.const 1
              i32.add
              local.set 10
              local.get 2
              i32.load8_u
              local.tee 11
              br_if 0 (;@5;)
            end
            i32.const 0
            local.set 15
            local.get 10
            local.set 2
          end
          block  ;; label = @4
            local.get 12
            i32.eqz
            br_if 0 (;@4;)
            local.get 3
            local.get 3
            i32.load offset=28
            i32.store offset=24
            local.get 1
            local.get 3
            i32.const 24
            i32.add
            local.get 12
            call $skip_to_arg
          end
          local.get 9
          i32.const -65
          i32.and
          local.get 9
          local.get 13
          i32.const 0
          i32.lt_s
          select
          local.set 10
          local.get 13
          i32.const 0
          local.get 13
          i32.const 0
          i32.gt_s
          select
          local.set 9
          local.get 15
          i32.const 32
          i32.or
          local.tee 11
          i32.const -101
          i32.add
          local.set 16
          block  ;; label = @4
            block  ;; label = @5
              block  ;; label = @6
                block  ;; label = @7
                  local.get 11
                  i32.const 97
                  i32.eq
                  br_if 0 (;@7;)
                  local.get 16
                  i32.const 2
                  i32.gt_u
                  br_if 1 (;@6;)
                end
                local.get 3
                local.get 3
                i32.load offset=24
                i32.const 7
                i32.add
                i32.const -8
                i32.and
                local.tee 13
                i32.const 8
                i32.add
                i32.store offset=24
                local.get 11
                local.get 15
                i32.sub
                local.set 15
                local.get 13
                f64.load
                local.set 17
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 11
                    i32.const 97
                    i32.ne
                    br_if 0 (;@8;)
                    i32.const 1
                    local.set 18
                    local.get 17
                    local.get 3
                    local.get 9
                    i32.const -1
                    local.get 10
                    i32.const 64
                    i32.and
                    select
                    local.get 15
                    i32.const 255
                    i32.and
                    call $__dtox_engine
                    local.tee 13
                    i32.const 1
                    i32.add
                    local.set 9
                    local.get 10
                    i32.const 6144
                    i32.or
                    local.set 10
                    i32.const 112
                    local.set 19
                    br 1 (;@7;)
                  end
                  local.get 9
                  i32.const 6
                  local.get 10
                  i32.const 64
                  i32.and
                  select
                  local.set 13
                  block  ;; label = @8
                    block  ;; label = @9
                      block  ;; label = @10
                        block  ;; label = @11
                          block  ;; label = @12
                            local.get 16
                            br_table 0 (;@12;) 1 (;@11;) 2 (;@10;)
                          end
                          local.get 10
                          i32.const 4096
                          i32.or
                          local.set 10
                          local.get 13
                          i32.const 1
                          i32.add
                          local.set 9
                          i32.const 0
                          local.set 11
                          i32.const 101
                          local.set 19
                          br 2 (;@9;)
                        end
                        local.get 10
                        i32.const 8192
                        i32.or
                        local.set 10
                        i32.const 1
                        local.set 16
                        i32.const 102
                        local.set 19
                        i32.const 17
                        local.set 9
                        local.get 13
                        local.set 11
                        br 2 (;@8;)
                      end
                      local.get 13
                      i32.const 1
                      local.get 13
                      i32.const 255
                      i32.and
                      select
                      local.set 9
                      local.get 11
                      i32.const -2
                      i32.add
                      local.set 19
                      i32.const 0
                      local.set 11
                    end
                    i32.const 0
                    local.set 16
                  end
                  i32.const 2
                  local.set 18
                  local.get 17
                  local.get 3
                  local.get 9
                  i32.const 255
                  i32.and
                  local.tee 9
                  i32.const 17
                  local.get 9
                  i32.const 17
                  i32.lt_u
                  select
                  local.get 16
                  local.get 11
                  call $__dtoa_engine
                  local.set 9
                end
                local.get 3
                i32.load
                local.set 16
                i32.const 45
                local.set 20
                i32.const 0
                local.set 12
                block  ;; label = @7
                  local.get 3
                  i32.load8_u offset=4
                  local.tee 11
                  i32.const 1
                  i32.and
                  br_if 0 (;@7;)
                  i32.const 43
                  local.set 20
                  local.get 10
                  i32.const 2
                  i32.and
                  br_if 0 (;@7;)
                  local.get 10
                  i32.const 65535
                  i32.and
                  i32.const 4
                  i32.and
                  local.tee 12
                  i32.const 3
                  i32.shl
                  local.set 20
                  local.get 12
                  i32.eqz
                  local.set 12
                end
                block  ;; label = @7
                  local.get 11
                  i32.const 12
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  i32.const 0
                  local.set 11
                  block  ;; label = @8
                    local.get 14
                    i32.const 3
                    i32.const 4
                    local.get 12
                    select
                    local.tee 9
                    i32.le_s
                    br_if 0 (;@8;)
                    block  ;; label = @9
                      local.get 10
                      i32.const 8
                      i32.and
                      i32.eqz
                      br_if 0 (;@9;)
                      local.get 14
                      local.get 9
                      i32.sub
                      local.set 11
                      br 1 (;@8;)
                    end
                    local.get 9
                    local.get 14
                    i32.sub
                    local.set 9
                    loop  ;; label = @9
                      i32.const 32
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.lt_s
                      br_if 7 (;@2;)
                      local.get 4
                      i32.const 1
                      i32.add
                      local.set 4
                      local.get 9
                      i32.const 1
                      i32.add
                      local.tee 9
                      br_if 0 (;@9;)
                    end
                  end
                  block  ;; label = @8
                    local.get 12
                    br_if 0 (;@8;)
                    local.get 20
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.lt_s
                    br_if 6 (;@2;)
                    local.get 4
                    i32.const 1
                    i32.add
                    local.set 4
                  end
                  i32.const 1028
                  i32.const 1041
                  local.get 3
                  i32.load8_u offset=4
                  i32.const 8
                  i32.and
                  select
                  local.set 9
                  loop  ;; label = @8
                    local.get 9
                    i32.load8_u
                    local.tee 10
                    i32.eqz
                    br_if 4 (;@4;)
                    local.get 4
                    i32.const 1
                    i32.add
                    local.set 4
                    local.get 9
                    i32.const 1
                    i32.add
                    local.set 9
                    local.get 10
                    local.get 15
                    i32.sub
                    i32.extend8_s
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.ge_s
                    br_if 0 (;@8;)
                    br 6 (;@2;)
                  end
                end
                i32.const 2
                local.get 18
                local.get 16
                i32.const -10
                i32.add
                i32.const -19
                i32.lt_u
                select
                local.set 18
                local.get 16
                i32.const -100
                i32.add
                local.tee 21
                i32.const -199
                i32.lt_u
                local.set 22
                block  ;; label = @7
                  local.get 10
                  i32.const 12288
                  i32.and
                  br_if 0 (;@7;)
                  local.get 10
                  i32.const 65535
                  i32.and
                  local.set 23
                  local.get 13
                  i32.const 1
                  local.get 13
                  i32.const 1
                  i32.gt_u
                  select
                  local.set 13
                  block  ;; label = @8
                    loop  ;; label = @9
                      local.get 9
                      i32.const 255
                      i32.and
                      local.tee 11
                      i32.eqz
                      br_if 1 (;@8;)
                      local.get 11
                      local.get 3
                      i32.add
                      i32.const 4
                      i32.add
                      i32.load8_u
                      i32.const 48
                      i32.ne
                      br_if 1 (;@8;)
                      local.get 9
                      i32.const -1
                      i32.add
                      local.set 9
                      br 0 (;@9;)
                    end
                  end
                  local.get 13
                  local.get 11
                  local.get 23
                  i32.const 16
                  i32.and
                  select
                  local.set 11
                  block  ;; label = @8
                    local.get 16
                    i32.const -4
                    i32.lt_s
                    br_if 0 (;@8;)
                    local.get 16
                    local.get 13
                    i32.ge_s
                    br_if 0 (;@8;)
                    local.get 10
                    i32.const 8192
                    i32.or
                    local.set 10
                    i32.const 0
                    local.set 13
                    local.get 16
                    local.get 11
                    i32.ge_s
                    br_if 1 (;@7;)
                    local.get 11
                    local.get 16
                    i32.const -1
                    i32.xor
                    i32.add
                    local.set 13
                    br 1 (;@7;)
                  end
                  local.get 11
                  i32.const -1
                  i32.add
                  local.set 13
                end
                i32.const 3
                local.get 18
                local.get 22
                select
                local.set 23
                local.get 16
                i32.const -1000
                i32.add
                local.set 22
                local.get 10
                i32.const 65535
                i32.and
                local.set 18
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 10
                    i32.const 8192
                    i32.and
                    local.tee 24
                    i32.eqz
                    br_if 0 (;@8;)
                    i32.const 1
                    local.get 16
                    i32.const 1
                    i32.add
                    local.get 16
                    i32.const 1
                    i32.lt_s
                    select
                    local.set 10
                    br 1 (;@7;)
                  end
                  i32.const 5
                  i32.const 3
                  local.get 18
                  i32.const 2048
                  i32.and
                  select
                  i32.const 4
                  local.get 23
                  local.get 22
                  i32.const -1999
                  i32.lt_u
                  select
                  i32.add
                  local.set 10
                end
                local.get 14
                local.get 13
                i32.const 1
                i32.add
                local.get 18
                i32.const 4
                i32.shr_u
                i32.const 1
                i32.and
                local.get 13
                select
                local.tee 25
                local.get 12
                i32.const 1
                i32.xor
                local.tee 26
                i32.add
                local.get 10
                i32.add
                local.tee 11
                i32.sub
                i32.const 0
                local.get 14
                local.get 11
                i32.gt_s
                select
                local.set 11
                block  ;; label = @7
                  local.get 18
                  i32.const 9
                  i32.and
                  br_if 0 (;@7;)
                  local.get 11
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 25
                  local.get 10
                  i32.add
                  local.get 26
                  i32.add
                  local.get 14
                  i32.sub
                  local.set 11
                  loop  ;; label = @8
                    i32.const 32
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.lt_s
                    br_if 6 (;@2;)
                    local.get 4
                    i32.const 1
                    i32.add
                    local.set 4
                    local.get 11
                    i32.const 1
                    i32.add
                    local.tee 11
                    br_if 0 (;@8;)
                  end
                  i32.const 0
                  local.set 11
                end
                block  ;; label = @7
                  local.get 12
                  br_if 0 (;@7;)
                  local.get 20
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.lt_s
                  br_if 5 (;@2;)
                  local.get 4
                  i32.const 1
                  i32.add
                  local.set 4
                end
                block  ;; label = @7
                  local.get 18
                  i32.const 2048
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  i32.const 48
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.lt_s
                  br_if 5 (;@2;)
                  i32.const 120
                  local.get 15
                  i32.sub
                  i32.extend8_s
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.lt_s
                  br_if 5 (;@2;)
                  local.get 4
                  i32.const 2
                  i32.add
                  local.set 4
                end
                block  ;; label = @7
                  local.get 18
                  i32.const 8
                  i32.and
                  br_if 0 (;@7;)
                  local.get 11
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 11
                  local.get 4
                  i32.add
                  local.set 4
                  loop  ;; label = @8
                    i32.const 48
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.lt_s
                    br_if 6 (;@2;)
                    local.get 11
                    i32.const -1
                    i32.add
                    local.tee 11
                    br_if 0 (;@8;)
                  end
                  i32.const 0
                  local.set 11
                end
                block  ;; label = @7
                  local.get 24
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 7
                  local.get 16
                  i32.add
                  local.set 20
                  i32.const 0
                  local.get 13
                  i32.sub
                  local.set 13
                  local.get 9
                  i32.const 255
                  i32.and
                  local.set 12
                  i32.const 0
                  local.get 16
                  i32.const 0
                  local.get 16
                  i32.const 0
                  i32.gt_s
                  select
                  local.tee 10
                  i32.sub
                  local.set 9
                  loop  ;; label = @8
                    block  ;; label = @9
                      local.get 9
                      i32.const 1
                      i32.ne
                      br_if 0 (;@9;)
                      i32.const 46
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.lt_s
                      br_if 7 (;@2;)
                      local.get 4
                      i32.const 1
                      i32.add
                      local.set 4
                    end
                    i32.const 48
                    local.set 15
                    block  ;; label = @9
                      local.get 16
                      local.get 9
                      i32.add
                      local.tee 14
                      i32.const 0
                      i32.lt_s
                      br_if 0 (;@9;)
                      local.get 14
                      local.get 12
                      i32.ge_s
                      br_if 0 (;@9;)
                      local.get 20
                      local.get 9
                      i32.add
                      i32.load8_u
                      local.set 15
                    end
                    block  ;; label = @9
                      local.get 10
                      local.get 13
                      i32.le_s
                      br_if 0 (;@9;)
                      local.get 10
                      i32.const -1
                      i32.add
                      local.set 10
                      local.get 9
                      i32.const 1
                      i32.add
                      local.set 9
                      local.get 4
                      i32.const 1
                      i32.add
                      local.set 4
                      local.get 15
                      i32.extend8_s
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.ge_s
                      br_if 1 (;@8;)
                      br 7 (;@2;)
                    end
                  end
                  block  ;; label = @8
                    local.get 14
                    i32.const -1
                    i32.ne
                    br_if 0 (;@8;)
                    block  ;; label = @9
                      local.get 3
                      i32.load8_s offset=5
                      local.tee 10
                      i32.const 53
                      i32.gt_s
                      br_if 0 (;@9;)
                      local.get 10
                      i32.const 53
                      i32.ne
                      br_if 1 (;@8;)
                      local.get 3
                      i32.load8_u offset=4
                      i32.const 16
                      i32.and
                      br_if 1 (;@8;)
                    end
                    i32.const 49
                    local.set 15
                  end
                  local.get 15
                  i32.extend8_s
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.lt_s
                  br_if 5 (;@2;)
                  local.get 4
                  i32.const 1
                  i32.add
                  local.set 10
                  local.get 18
                  i32.const 16
                  i32.and
                  i32.eqz
                  br_if 2 (;@5;)
                  local.get 9
                  br_if 2 (;@5;)
                  i32.const 46
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const -1
                  i32.le_s
                  br_if 5 (;@2;)
                  local.get 4
                  i32.const 2
                  i32.add
                  local.set 4
                  br 3 (;@4;)
                end
                block  ;; label = @7
                  local.get 3
                  i32.load8_s offset=5
                  local.tee 10
                  i32.const 49
                  i32.eq
                  br_if 0 (;@7;)
                  local.get 3
                  local.get 3
                  i32.load8_u offset=4
                  i32.const 239
                  i32.and
                  i32.store8 offset=4
                end
                local.get 10
                local.get 0
                local.get 5
                call_indirect (type 1)
                i32.const 0
                i32.lt_s
                br_if 4 (;@2;)
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 13
                    i32.const 1
                    i32.lt_s
                    br_if 0 (;@8;)
                    i32.const 46
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.lt_s
                    br_if 6 (;@2;)
                    local.get 9
                    i32.const 255
                    i32.and
                    local.set 14
                    local.get 13
                    local.get 4
                    i32.add
                    i32.const 2
                    i32.add
                    local.set 12
                    i32.const 0
                    local.set 9
                    loop  ;; label = @9
                      local.get 13
                      local.get 9
                      i32.eq
                      br_if 2 (;@7;)
                      i32.const 48
                      local.set 10
                      block  ;; label = @10
                        local.get 9
                        i32.const 1
                        i32.add
                        local.tee 4
                        local.get 14
                        i32.ge_u
                        br_if 0 (;@10;)
                        local.get 6
                        local.get 9
                        i32.add
                        i32.load8_u
                        local.set 10
                      end
                      local.get 4
                      local.set 9
                      local.get 10
                      i32.extend8_s
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.ge_s
                      br_if 0 (;@9;)
                      br 7 (;@2;)
                    end
                  end
                  block  ;; label = @8
                    local.get 18
                    i32.const 16
                    i32.and
                    br_if 0 (;@8;)
                    local.get 4
                    i32.const 1
                    i32.add
                    local.set 12
                    br 1 (;@7;)
                  end
                  i32.const 46
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.lt_s
                  br_if 5 (;@2;)
                  local.get 4
                  i32.const 2
                  i32.add
                  local.set 12
                end
                local.get 19
                local.get 15
                i32.sub
                i32.extend8_s
                local.get 0
                local.get 5
                call_indirect (type 1)
                i32.const 0
                i32.lt_s
                br_if 4 (;@2;)
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 16
                    i32.const 0
                    i32.lt_s
                    br_if 0 (;@8;)
                    i32.const 43
                    local.set 10
                    block  ;; label = @9
                      local.get 16
                      i32.eqz
                      br_if 0 (;@9;)
                      local.get 16
                      local.set 9
                      br 2 (;@7;)
                    end
                    i32.const 0
                    local.set 9
                    local.get 3
                    i32.load8_u offset=4
                    i32.const 16
                    i32.and
                    i32.eqz
                    br_if 1 (;@7;)
                  end
                  i32.const 0
                  local.get 16
                  i32.sub
                  local.set 9
                  i32.const 45
                  local.set 10
                end
                local.get 10
                local.get 0
                local.get 5
                call_indirect (type 1)
                i32.const 0
                i32.lt_s
                br_if 4 (;@2;)
                block  ;; label = @7
                  block  ;; label = @8
                    block  ;; label = @9
                      block  ;; label = @10
                        block  ;; label = @11
                          local.get 22
                          i32.const -2000
                          i32.gt_u
                          br_if 0 (;@11;)
                          local.get 9
                          i32.const 1000
                          i32.div_u
                          local.tee 4
                          i32.const 48
                          i32.add
                          i32.extend8_s
                          local.get 0
                          local.get 5
                          call_indirect (type 1)
                          i32.const 0
                          i32.lt_s
                          br_if 9 (;@2;)
                          local.get 12
                          i32.const 3
                          i32.add
                          local.set 10
                          local.get 9
                          local.get 4
                          i32.const 1000
                          i32.mul
                          i32.sub
                          local.set 9
                          br 1 (;@10;)
                        end
                        local.get 12
                        i32.const 2
                        i32.add
                        local.set 10
                        local.get 21
                        i32.const -200
                        i32.gt_u
                        br_if 1 (;@9;)
                      end
                      local.get 9
                      i32.const 100
                      i32.div_u
                      local.tee 4
                      i32.const 48
                      i32.add
                      i32.extend8_s
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.lt_s
                      br_if 7 (;@2;)
                      local.get 10
                      i32.const 1
                      i32.add
                      local.set 10
                      local.get 9
                      local.get 4
                      i32.const 100
                      i32.mul
                      i32.sub
                      local.set 9
                      br 1 (;@8;)
                    end
                    local.get 23
                    i32.const 2
                    i32.lt_u
                    br_if 1 (;@7;)
                  end
                  local.get 9
                  i32.const 10
                  i32.div_u
                  local.tee 4
                  i32.const 48
                  i32.add
                  i32.extend8_s
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.lt_s
                  br_if 5 (;@2;)
                  local.get 10
                  i32.const 1
                  i32.add
                  local.set 10
                  local.get 9
                  local.get 4
                  i32.const 10
                  i32.mul
                  i32.sub
                  local.set 9
                end
                local.get 9
                i32.const 48
                i32.add
                i32.extend8_s
                local.get 0
                local.get 5
                call_indirect (type 1)
                i32.const 0
                i32.lt_s
                br_if 4 (;@2;)
                local.get 10
                i32.const 1
                i32.add
                local.set 4
                br 2 (;@4;)
              end
              i32.const 8
              local.set 12
              i32.const 0
              local.set 16
              block  ;; label = @6
                block  ;; label = @7
                  block  ;; label = @8
                    block  ;; label = @9
                      block  ;; label = @10
                        block  ;; label = @11
                          block  ;; label = @12
                            block  ;; label = @13
                              block  ;; label = @14
                                block  ;; label = @15
                                  local.get 15
                                  i32.const -111
                                  i32.add
                                  br_table 7 (;@8;) 4 (;@11;) 5 (;@10;) 5 (;@10;) 1 (;@14;) 5 (;@10;) 6 (;@9;) 0 (;@15;)
                                end
                                block  ;; label = @15
                                  local.get 15
                                  i32.const -99
                                  i32.add
                                  br_table 0 (;@15;) 3 (;@12;) 5 (;@10;) 5 (;@10;) 5 (;@10;) 5 (;@10;) 3 (;@12;) 5 (;@10;)
                                end
                                local.get 3
                                local.get 3
                                i32.load offset=24
                                local.tee 11
                                i32.const 4
                                i32.add
                                i32.store offset=24
                                local.get 3
                                local.get 11
                                i32.load
                                i32.store8
                                i32.const 1
                                local.set 9
                                local.get 3
                                local.set 15
                                br 1 (;@13;)
                              end
                              local.get 3
                              local.get 3
                              i32.load offset=24
                              local.tee 11
                              i32.const 4
                              i32.add
                              i32.store offset=24
                              local.get 11
                              i32.load
                              local.tee 11
                              i32.const 1045
                              local.get 11
                              select
                              local.tee 15
                              local.get 9
                              i32.const -1
                              local.get 10
                              i32.const 64
                              i32.and
                              select
                              call $strnlen
                              local.set 9
                            end
                            local.get 10
                            i32.const 8
                            i32.and
                            br_if 6 (;@6;)
                            local.get 14
                            local.get 9
                            local.get 14
                            local.get 9
                            i32.lt_u
                            select
                            local.set 11
                            loop  ;; label = @13
                              block  ;; label = @14
                                local.get 14
                                local.get 9
                                i32.gt_u
                                br_if 0 (;@14;)
                                local.get 11
                                local.set 14
                                br 8 (;@6;)
                              end
                              i32.const 32
                              local.get 0
                              local.get 5
                              call_indirect (type 1)
                              i32.const 0
                              i32.lt_s
                              br_if 11 (;@2;)
                              local.get 14
                              i32.const -1
                              i32.add
                              local.set 14
                              local.get 4
                              i32.const 1
                              i32.add
                              local.set 4
                              br 0 (;@13;)
                            end
                          end
                          local.get 3
                          i32.load offset=24
                          local.set 11
                          block  ;; label = @12
                            block  ;; label = @13
                              local.get 10
                              i32.const 128
                              i32.and
                              i32.eqz
                              br_if 0 (;@13;)
                              local.get 3
                              local.get 11
                              i32.const 7
                              i32.add
                              i32.const -8
                              i32.and
                              local.tee 11
                              i32.const 8
                              i32.add
                              i32.store offset=24
                              local.get 11
                              i64.load
                              local.set 27
                              br 1 (;@12;)
                            end
                            local.get 3
                            local.get 11
                            i32.const 4
                            i32.add
                            i32.store offset=24
                            local.get 11
                            i32.load
                            local.set 11
                            block  ;; label = @13
                              local.get 10
                              i32.const 65535
                              i32.and
                              local.tee 16
                              i32.const 256
                              i32.and
                              br_if 0 (;@13;)
                              local.get 11
                              i64.extend_i32_s
                              local.set 27
                              br 1 (;@12;)
                            end
                            local.get 11
                            i64.extend_i32_u
                            local.set 27
                            block  ;; label = @13
                              local.get 16
                              i32.const 512
                              i32.and
                              i32.eqz
                              br_if 0 (;@13;)
                              local.get 27
                              i64.extend8_s
                              local.set 27
                              br 1 (;@12;)
                            end
                            local.get 27
                            i64.extend16_s
                            local.set 27
                          end
                          local.get 10
                          i32.const 1024
                          i32.or
                          local.get 10
                          local.get 27
                          i64.const 0
                          i64.lt_s
                          select
                          i32.const -17
                          i32.and
                          local.set 11
                          block  ;; label = @12
                            local.get 27
                            i64.const 0
                            i64.ne
                            br_if 0 (;@12;)
                            local.get 10
                            i32.const 64
                            i32.and
                            i32.eqz
                            br_if 0 (;@12;)
                            i32.const 0
                            local.set 10
                            local.get 13
                            i32.const 1
                            i32.lt_s
                            br_if 5 (;@7;)
                          end
                          local.get 27
                          local.get 27
                          i64.const 63
                          i64.shr_s
                          local.tee 28
                          i64.xor
                          local.get 28
                          i64.sub
                          local.get 3
                          i32.const 10
                          call $__ultoa_invert
                          local.get 3
                          i32.sub
                          local.set 10
                          br 4 (;@7;)
                        end
                        i32.const 16
                        local.set 12
                        local.get 10
                        i32.const 16
                        i32.or
                        local.set 10
                        i32.const 120
                        local.set 16
                        br 2 (;@8;)
                      end
                      block  ;; label = @10
                        local.get 11
                        i32.const 120
                        i32.ne
                        br_if 0 (;@10;)
                        i32.const 136
                        local.get 15
                        i32.sub
                        local.set 12
                        local.get 15
                        local.set 16
                        br 2 (;@8;)
                      end
                      i32.const 37
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.lt_s
                      br_if 7 (;@2;)
                      local.get 4
                      i32.const 2
                      i32.add
                      local.set 4
                      local.get 15
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.ge_s
                      br_if 6 (;@3;)
                      br 7 (;@2;)
                    end
                    local.get 10
                    i32.const 65519
                    i32.and
                    local.set 10
                    i32.const 10
                    local.set 12
                    i32.const 117
                    local.set 16
                  end
                  local.get 10
                  i32.const 65529
                  i32.and
                  local.set 11
                  local.get 3
                  i32.load offset=24
                  local.set 15
                  block  ;; label = @8
                    block  ;; label = @9
                      local.get 10
                      i32.const 128
                      i32.and
                      i32.eqz
                      br_if 0 (;@9;)
                      local.get 3
                      local.get 15
                      i32.const 7
                      i32.add
                      i32.const -8
                      i32.and
                      local.tee 15
                      i32.const 8
                      i32.add
                      i32.store offset=24
                      local.get 15
                      i64.load
                      local.set 27
                      br 1 (;@8;)
                    end
                    local.get 3
                    local.get 15
                    i32.const 4
                    i32.add
                    i32.store offset=24
                    local.get 15
                    i32.load
                    local.set 15
                    block  ;; label = @9
                      local.get 11
                      i32.const 256
                      i32.and
                      br_if 0 (;@9;)
                      local.get 15
                      i64.extend_i32_u
                      local.set 27
                      br 1 (;@8;)
                    end
                    block  ;; label = @9
                      local.get 11
                      i32.const 512
                      i32.and
                      i32.eqz
                      br_if 0 (;@9;)
                      local.get 15
                      i32.const 255
                      i32.and
                      i64.extend_i32_u
                      local.set 27
                      br 1 (;@8;)
                    end
                    local.get 15
                    i32.const 65535
                    i32.and
                    i64.extend_i32_u
                    local.set 27
                  end
                  block  ;; label = @8
                    block  ;; label = @9
                      local.get 27
                      i64.const 0
                      i64.ne
                      br_if 0 (;@9;)
                      local.get 10
                      i32.const 64
                      i32.and
                      i32.eqz
                      br_if 0 (;@9;)
                      local.get 13
                      i32.const 1
                      i32.ge_s
                      br_if 0 (;@9;)
                      local.get 10
                      i32.const 65513
                      i32.and
                      local.set 11
                      i32.const 0
                      local.set 10
                      br 1 (;@8;)
                    end
                    local.get 10
                    i32.const -23
                    i32.and
                    local.get 11
                    local.get 27
                    i64.eqz
                    select
                    local.set 11
                    local.get 27
                    local.get 3
                    local.get 12
                    call $__ultoa_invert
                    local.get 3
                    i32.sub
                    local.set 10
                  end
                  local.get 16
                  local.set 15
                end
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 11
                    i32.const 64
                    i32.and
                    i32.eqz
                    br_if 0 (;@8;)
                    local.get 11
                    i32.const 65534
                    i32.and
                    local.set 16
                    block  ;; label = @9
                      local.get 10
                      local.get 9
                      i32.lt_s
                      br_if 0 (;@9;)
                      local.get 16
                      local.set 11
                      br 1 (;@8;)
                    end
                    local.get 16
                    local.get 11
                    i32.const -18
                    i32.and
                    local.get 15
                    select
                    local.set 11
                    local.get 9
                    local.set 13
                    br 1 (;@7;)
                  end
                  local.get 10
                  local.set 13
                end
                local.get 11
                i32.const 65535
                i32.and
                local.set 16
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 11
                    i32.const 16
                    i32.and
                    local.tee 12
                    i32.eqz
                    br_if 0 (;@8;)
                    i32.const 2
                    i32.const 1
                    local.get 15
                    select
                    local.set 11
                    br 1 (;@7;)
                  end
                  local.get 16
                  i32.const 1030
                  i32.and
                  i32.const 0
                  i32.ne
                  local.set 11
                end
                local.get 11
                local.get 13
                i32.add
                local.set 11
                block  ;; label = @7
                  local.get 16
                  i32.const 8
                  i32.and
                  br_if 0 (;@7;)
                  block  ;; label = @8
                    local.get 16
                    i32.const 1
                    i32.and
                    i32.eqz
                    br_if 0 (;@8;)
                    block  ;; label = @9
                      local.get 11
                      local.get 14
                      i32.lt_s
                      br_if 0 (;@9;)
                      local.get 10
                      local.set 9
                      br 1 (;@8;)
                    end
                    local.get 10
                    local.get 14
                    i32.add
                    local.get 11
                    i32.sub
                    local.set 9
                    local.get 14
                    local.set 11
                  end
                  local.get 14
                  local.get 11
                  local.get 14
                  local.get 11
                  i32.gt_s
                  select
                  local.tee 13
                  local.get 11
                  i32.sub
                  local.set 11
                  loop  ;; label = @8
                    block  ;; label = @9
                      local.get 11
                      br_if 0 (;@9;)
                      local.get 13
                      local.set 11
                      br 2 (;@7;)
                    end
                    i32.const 32
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.lt_s
                    br_if 6 (;@2;)
                    local.get 11
                    i32.const -1
                    i32.add
                    local.set 11
                    local.get 4
                    i32.const 1
                    i32.add
                    local.set 4
                    br 0 (;@8;)
                  end
                end
                block  ;; label = @7
                  block  ;; label = @8
                    block  ;; label = @9
                      local.get 12
                      i32.eqz
                      br_if 0 (;@9;)
                      i32.const 48
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.lt_s
                      br_if 7 (;@2;)
                      local.get 15
                      i32.eqz
                      br_if 1 (;@8;)
                      local.get 15
                      local.get 0
                      local.get 5
                      call_indirect (type 1)
                      i32.const 0
                      i32.lt_s
                      br_if 7 (;@2;)
                      local.get 4
                      i32.const 2
                      i32.add
                      local.set 4
                      br 2 (;@7;)
                    end
                    local.get 16
                    i32.const 1030
                    i32.and
                    i32.eqz
                    br_if 1 (;@7;)
                    i32.const 45
                    i32.const 43
                    i32.const 32
                    local.get 16
                    i32.const 2
                    i32.and
                    select
                    local.get 16
                    i32.const 1024
                    i32.and
                    select
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.lt_s
                    br_if 6 (;@2;)
                  end
                  local.get 4
                  i32.const 1
                  i32.add
                  local.set 4
                end
                local.get 14
                local.get 11
                i32.sub
                local.set 11
                local.get 4
                local.get 10
                i32.add
                local.set 4
                block  ;; label = @7
                  loop  ;; label = @8
                    local.get 9
                    local.get 10
                    i32.le_s
                    br_if 1 (;@7;)
                    local.get 4
                    i32.const 1
                    i32.add
                    local.set 4
                    local.get 9
                    i32.const -1
                    i32.add
                    local.set 9
                    i32.const 48
                    local.get 0
                    local.get 5
                    call_indirect (type 1)
                    i32.const 0
                    i32.ge_s
                    br_if 0 (;@8;)
                    br 6 (;@2;)
                  end
                end
                loop  ;; label = @7
                  local.get 10
                  i32.eqz
                  br_if 3 (;@4;)
                  local.get 8
                  local.get 10
                  i32.add
                  local.set 9
                  local.get 10
                  i32.const -1
                  i32.add
                  local.set 10
                  local.get 9
                  i32.load8_s
                  local.get 0
                  local.get 5
                  call_indirect (type 1)
                  i32.const 0
                  i32.ge_s
                  br_if 0 (;@7;)
                  br 5 (;@2;)
                end
              end
              local.get 4
              local.get 9
              i32.add
              local.set 4
              local.get 14
              local.get 9
              i32.sub
              local.set 11
              loop  ;; label = @6
                local.get 9
                i32.eqz
                br_if 2 (;@4;)
                local.get 15
                i32.load8_s
                local.set 10
                local.get 15
                i32.const 1
                i32.add
                local.set 15
                local.get 9
                i32.const -1
                i32.add
                local.set 9
                local.get 10
                local.get 0
                local.get 5
                call_indirect (type 1)
                i32.const 0
                i32.ge_s
                br_if 0 (;@6;)
                br 4 (;@2;)
              end
            end
            local.get 10
            local.set 4
          end
          loop  ;; label = @4
            local.get 11
            i32.const 1
            i32.lt_s
            br_if 1 (;@3;)
            local.get 4
            i32.const 1
            i32.add
            local.set 4
            local.get 11
            i32.const -1
            i32.add
            local.set 11
            i32.const 32
            local.get 0
            local.get 5
            call_indirect (type 1)
            i32.const 0
            i32.ge_s
            br_if 0 (;@4;)
          end
        end
      end
      local.get 0
      local.get 0
      i32.load8_u offset=4
      i32.const 4
      i32.or
      i32.store8 offset=4
      i32.const -1
      local.set 4
    end
    local.get 3
    i32.const 32
    i32.add
    global.set $__stack_pointer
    local.get 4)
  (func $skip_to_arg (type 7) (param i32 i32 i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    i32.const 1
    local.set 3
    loop  ;; label = @1
      local.get 3
      local.get 2
      i32.ge_s
      local.set 4
      local.get 0
      local.set 5
      block  ;; label = @2
        loop  ;; label = @3
          local.get 4
          br_if 1 (;@2;)
          loop  ;; label = @4
            block  ;; label = @5
              local.get 5
              i32.load8_u
              local.tee 6
              i32.const 37
              i32.eq
              br_if 0 (;@5;)
              local.get 5
              i32.const 1
              i32.add
              local.set 5
              local.get 6
              br_if 1 (;@4;)
              br 3 (;@2;)
            end
            local.get 5
            i32.load8_u offset=1
            local.set 6
            local.get 5
            i32.const 2
            i32.add
            local.tee 7
            local.set 5
            local.get 6
            i32.const 37
            i32.eq
            br_if 0 (;@4;)
          end
          i32.const 0
          local.set 8
          i32.const 0
          local.set 9
          i32.const 0
          local.set 10
          block  ;; label = @4
            loop  ;; label = @5
              local.get 7
              local.set 5
              local.get 10
              local.set 7
              local.get 6
              i32.extend8_s
              local.set 11
              block  ;; label = @6
                block  ;; label = @7
                  block  ;; label = @8
                    block  ;; label = @9
                      block  ;; label = @10
                        block  ;; label = @11
                          block  ;; label = @12
                            block  ;; label = @13
                              block  ;; label = @14
                                local.get 8
                                i32.const 65535
                                i32.and
                                local.tee 10
                                i32.const 31
                                i32.gt_u
                                br_if 0 (;@14;)
                                local.get 6
                                i32.const 255
                                i32.and
                                local.tee 12
                                i32.const -39
                                i32.add
                                local.tee 10
                                i32.const 9
                                i32.gt_u
                                br_if 1 (;@13;)
                                i32.const 1
                                local.get 10
                                i32.shl
                                i32.const 593
                                i32.and
                                i32.eqz
                                br_if 1 (;@13;)
                                br 7 (;@7;)
                              end
                              local.get 10
                              i32.const 127
                              i32.le_u
                              br_if 1 (;@12;)
                              block  ;; label = @14
                                local.get 6
                                i32.const 255
                                i32.and
                                local.tee 6
                                i32.const -104
                                i32.add
                                br_table 4 (;@10;) 10 (;@4;) 6 (;@8;) 10 (;@4;) 3 (;@11;) 0 (;@14;)
                              end
                              local.get 6
                              i32.const 76
                              i32.eq
                              br_if 4 (;@9;)
                              local.get 6
                              i32.const 116
                              i32.eq
                              br_if 6 (;@7;)
                              local.get 7
                              local.set 10
                              local.get 6
                              i32.const 122
                              i32.eq
                              br_if 7 (;@6;)
                              br 9 (;@4;)
                            end
                            local.get 7
                            local.set 10
                            local.get 12
                            i32.const -32
                            i32.add
                            br_table 6 (;@6;) 0 (;@12;) 0 (;@12;) 6 (;@6;) 0 (;@12;)
                          end
                          block  ;; label = @12
                            local.get 11
                            i32.const -48
                            i32.add
                            local.tee 10
                            i32.const 9
                            i32.gt_u
                            br_if 0 (;@12;)
                            local.get 8
                            i32.const 32
                            i32.or
                            local.set 8
                            local.get 7
                            i32.const 10
                            i32.mul
                            local.get 10
                            i32.add
                            local.set 10
                            br 6 (;@6;)
                          end
                          block  ;; label = @12
                            local.get 6
                            i32.const 255
                            i32.and
                            local.tee 6
                            i32.const -104
                            i32.add
                            br_table 2 (;@10;) 8 (;@4;) 4 (;@8;) 8 (;@4;) 1 (;@11;) 0 (;@12;)
                          end
                          i32.const 0
                          local.set 10
                          block  ;; label = @12
                            local.get 6
                            i32.const -42
                            i32.add
                            br_table 6 (;@6;) 8 (;@4;) 8 (;@4;) 8 (;@4;) 6 (;@6;) 0 (;@12;)
                          end
                          local.get 6
                          i32.const 122
                          i32.eq
                          br_if 4 (;@7;)
                          local.get 6
                          i32.const 76
                          i32.eq
                          br_if 2 (;@9;)
                          local.get 6
                          i32.const 116
                          i32.eq
                          br_if 4 (;@7;)
                          local.get 6
                          i32.const 36
                          i32.ne
                          br_if 7 (;@4;)
                          block  ;; label = @12
                            local.get 9
                            br_if 0 (;@12;)
                            local.get 7
                            local.set 9
                            br 6 (;@6;)
                          end
                          local.get 7
                          local.get 3
                          i32.ne
                          br_if 5 (;@6;)
                          i32.const 99
                          local.set 11
                          local.get 3
                          local.set 9
                          br 7 (;@4;)
                        end
                        local.get 8
                        local.get 8
                        i32.const 2
                        i32.shl
                        i32.const 512
                        i32.and
                        i32.or
                        i32.const 128
                        i32.or
                        local.set 8
                        br 3 (;@7;)
                      end
                      local.get 8
                      local.get 8
                      i32.const 1
                      i32.shl
                      i32.const 512
                      i32.and
                      i32.or
                      i32.const 256
                      i32.or
                      local.set 8
                      br 2 (;@7;)
                    end
                    local.get 8
                    i32.const 640
                    i32.or
                    local.set 8
                    br 1 (;@7;)
                  end
                  local.get 8
                  i32.const 128
                  i32.or
                  local.set 8
                end
                local.get 7
                local.set 10
              end
              local.get 5
              i32.const 1
              i32.add
              local.set 7
              local.get 5
              i32.load8_u
              local.tee 6
              br_if 0 (;@5;)
            end
            i32.const 0
            local.set 11
            local.get 7
            local.set 5
          end
          local.get 9
          i32.eqz
          br_if 1 (;@2;)
          local.get 9
          local.get 3
          i32.ne
          br_if 0 (;@3;)
        end
        block  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              local.get 11
              i32.const 32
              i32.or
              local.tee 5
              i32.const 97
              i32.eq
              br_if 0 (;@5;)
              local.get 5
              i32.const -101
              i32.add
              i32.const 2
              i32.gt_u
              br_if 1 (;@4;)
            end
            local.get 1
            i32.load
            i32.const 7
            i32.add
            i32.const -8
            i32.and
            i32.const 8
            i32.add
            local.set 5
            br 1 (;@3;)
          end
          block  ;; label = @4
            block  ;; label = @5
              block  ;; label = @6
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 11
                    i32.const -99
                    i32.add
                    br_table 0 (;@8;) 1 (;@7;) 3 (;@5;) 3 (;@5;) 3 (;@5;) 3 (;@5;) 1 (;@7;) 2 (;@6;)
                  end
                  local.get 1
                  i32.load
                  i32.const 4
                  i32.add
                  local.set 5
                  br 4 (;@3;)
                end
                local.get 1
                i32.load
                local.set 5
                block  ;; label = @7
                  local.get 8
                  i32.const 128
                  i32.and
                  i32.eqz
                  br_if 0 (;@7;)
                  local.get 5
                  i32.const 7
                  i32.add
                  i32.const -8
                  i32.and
                  i32.const 8
                  i32.add
                  local.set 5
                  br 4 (;@3;)
                end
                local.get 5
                i32.const 4
                i32.add
                local.set 5
                br 3 (;@3;)
              end
              local.get 11
              i32.const 115
              i32.eq
              br_if 1 (;@4;)
            end
            local.get 1
            i32.load
            local.set 5
            block  ;; label = @5
              local.get 8
              i32.const 128
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 5
              i32.const 7
              i32.add
              i32.const -8
              i32.and
              i32.const 8
              i32.add
              local.set 5
              br 2 (;@3;)
            end
            local.get 5
            i32.const 4
            i32.add
            local.set 5
            br 1 (;@3;)
          end
          local.get 1
          i32.load
          i32.const 4
          i32.add
          local.set 5
        end
        local.get 1
        local.get 5
        i32.store
        local.get 3
        i32.const 1
        i32.add
        local.set 3
        br 1 (;@1;)
      end
    end)
  (func $__ultoa_invert (type 8) (param i64 i32 i32) (result i32)
    (local i32 i64 i64)
    i32.const 922746880
    local.get 2
    i32.const 24
    i32.shl
    i32.sub
    i32.const 24
    i32.shr_u
    local.set 3
    local.get 2
    i32.const 31
    i32.and
    i64.extend_i32_u
    local.set 4
    loop  ;; label = @1
      local.get 1
      local.get 3
      i32.const 0
      local.get 0
      local.get 0
      local.get 4
      i64.div_u
      local.tee 5
      local.get 4
      i64.mul
      i64.sub
      i32.wrap_i64
      local.tee 2
      i32.const 9
      i32.gt_u
      select
      local.get 2
      i32.add
      i32.const 48
      i32.add
      i32.store8
      local.get 1
      i32.const 1
      i32.add
      local.set 1
      local.get 0
      local.get 4
      i64.ge_u
      local.set 2
      local.get 5
      local.set 0
      local.get 2
      br_if 0 (;@1;)
    end
    local.get 1)
  (func $__dtoa_engine (type 9) (param f64 i32 i32 i32 i32) (result i32)
    (local i32 i64 i32 i32 i32 i64 i64 i32 i32 i32 i32 i32 i64 i32 i64 i64 i64)
    global.get $__stack_pointer
    i32.const 32
    i32.sub
    local.tee 5
    global.set $__stack_pointer
    local.get 0
    i64.reinterpret_f64
    local.tee 6
    i64.const 52
    i64.shr_u
    i32.wrap_i64
    i32.const 2047
    i32.and
    local.set 7
    local.get 6
    i64.const 63
    i64.shr_u
    i32.wrap_i64
    local.set 8
    block  ;; label = @1
      block  ;; label = @2
        local.get 6
        i64.const 4503599627370495
        i64.and
        local.tee 6
        i64.const 0
        i64.ne
        br_if 0 (;@2;)
        local.get 7
        br_if 0 (;@2;)
        local.get 1
        i32.const 48
        i32.store8 offset=5
        local.get 1
        i32.const 0
        i32.store
        local.get 1
        local.get 8
        i32.const 2
        i32.or
        i32.store8 offset=4
        i32.const 1
        local.set 9
        br 1 (;@1;)
      end
      block  ;; label = @2
        local.get 7
        i32.const 2047
        i32.ne
        br_if 0 (;@2;)
        local.get 1
        i32.const 4
        i32.const 8
        local.get 6
        i64.eqz
        select
        local.get 8
        i32.or
        i32.store8 offset=4
        i32.const 0
        local.set 9
        br 1 (;@1;)
      end
      local.get 6
      i64.const 0
      i64.ne
      local.get 7
      i32.const 2
      i32.lt_u
      i32.or
      local.set 9
      local.get 6
      i64.const 4503599627370496
      i64.or
      local.get 6
      local.get 7
      select
      local.tee 6
      i64.const 2
      i64.shl
      local.set 10
      local.get 6
      i64.const 1
      i64.and
      local.set 11
      i32.const 0
      local.set 12
      block  ;; label = @2
        block  ;; label = @3
          local.get 7
          i32.const -1077
          i32.add
          i32.const -1076
          local.get 7
          select
          local.tee 7
          i32.const 0
          i32.lt_s
          br_if 0 (;@3;)
          local.get 7
          call $__log10Pow2
          local.get 7
          i32.const 3
          i32.gt_u
          i32.sub
          local.tee 13
          call $__pow5bits
          local.set 14
          local.get 13
          local.get 5
          call $__double_computeInvPow5
          local.get 6
          local.get 5
          local.get 14
          local.get 13
          local.get 7
          i32.sub
          i32.add
          i32.const 124
          i32.add
          local.get 5
          i32.const 24
          i32.add
          local.get 5
          i32.const 16
          i32.add
          local.get 9
          call $mulShiftAll64
          local.set 6
          i32.const 0
          local.set 14
          local.get 13
          i32.const 21
          i32.gt_u
          br_if 1 (;@2;)
          i32.const 0
          local.set 14
          block  ;; label = @4
            local.get 10
            call $umulh
            i64.const 2
            i64.shr_u
            i32.wrap_i64
            i32.const -5
            i32.mul
            i32.const 0
            local.get 10
            i32.wrap_i64
            i32.sub
            i32.ne
            br_if 0 (;@4;)
            local.get 10
            call $__pow5Factor
            local.get 13
            i32.ge_u
            local.set 12
            br 2 (;@2;)
          end
          block  ;; label = @4
            local.get 11
            i64.const 0
            i64.ne
            br_if 0 (;@4;)
            local.get 9
            i64.extend_i32_u
            i64.const -1
            i64.xor
            local.get 10
            i64.add
            call $__pow5Factor
            local.get 13
            i32.ge_u
            local.set 14
            i32.const 0
            local.set 12
            br 2 (;@2;)
          end
          local.get 10
          i64.const 2
          i64.or
          call $__pow5Factor
          local.set 12
          local.get 5
          local.get 5
          i64.load offset=24
          local.get 12
          local.get 13
          i32.ge_u
          i64.extend_i32_u
          i64.sub
          i64.store offset=24
          i32.const 0
          local.set 12
          i32.const 0
          local.set 14
          br 1 (;@2;)
        end
        i32.const 0
        local.get 7
        i32.sub
        local.set 12
        local.get 12
        local.get 12
        call $__log10Pow5
        local.get 7
        i32.const -1
        i32.ne
        i32.sub
        local.tee 15
        i32.sub
        local.tee 12
        call $__pow5bits
        local.set 14
        local.get 12
        local.get 5
        call $__double_computePow5
        i32.const 1
        local.set 12
        local.get 6
        local.get 5
        local.get 15
        local.get 14
        i32.sub
        i32.const 125
        i32.add
        local.get 5
        i32.const 24
        i32.add
        local.get 5
        i32.const 16
        i32.add
        local.get 9
        call $mulShiftAll64
        local.set 6
        block  ;; label = @3
          block  ;; label = @4
            local.get 15
            i32.const 1
            i32.gt_u
            br_if 0 (;@4;)
            block  ;; label = @5
              local.get 11
              i64.eqz
              i32.eqz
              br_if 0 (;@5;)
              local.get 9
              local.set 14
              br 2 (;@3;)
            end
            local.get 5
            local.get 5
            i64.load offset=24
            i64.const -1
            i64.add
            i64.store offset=24
            i32.const 0
            local.set 14
            br 1 (;@3;)
          end
          i32.const 0
          local.set 14
          block  ;; label = @4
            local.get 15
            i32.const 62
            i32.le_u
            br_if 0 (;@4;)
            i32.const 0
            local.set 12
            br 1 (;@3;)
          end
          local.get 10
          i64.const -1
          local.get 15
          i64.extend_i32_u
          i64.shl
          i64.const -1
          i64.xor
          i64.and
          i64.eqz
          local.set 12
        end
        local.get 15
        local.get 7
        i32.add
        local.set 13
      end
      local.get 2
      local.set 16
      block  ;; label = @2
        local.get 3
        i32.eqz
        br_if 0 (;@2;)
        local.get 2
        local.get 13
        local.get 4
        i32.add
        local.get 6
        call $decimalLength17
        i32.add
        local.tee 7
        i32.const 1
        local.get 7
        i32.const 1
        i32.gt_s
        select
        local.tee 7
        local.get 2
        local.get 7
        i32.lt_s
        select
        local.set 16
      end
      local.get 5
      i64.load offset=16
      local.set 10
      local.get 5
      i64.load offset=24
      local.set 17
      i32.const 0
      local.set 9
      i32.const 0
      local.set 7
      i32.const 0
      local.set 18
      block  ;; label = @2
        loop  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              local.get 17
              call $div10
              local.tee 19
              local.get 10
              call $div10
              local.tee 20
              i64.le_u
              br_if 0 (;@5;)
              local.get 18
              local.set 15
              br 1 (;@4;)
            end
            local.get 6
            call $decimalLength17
            local.get 16
            i32.le_s
            br_if 2 (;@2;)
            i32.const 1
            local.set 15
            local.get 16
            i32.eqz
            local.get 6
            i64.eqz
            i32.and
            br_if 2 (;@2;)
          end
          local.get 14
          local.get 20
          i32.wrap_i64
          i32.const -10
          i32.mul
          i32.const 0
          local.get 10
          i32.wrap_i64
          i32.sub
          i32.eq
          i32.and
          local.set 14
          local.get 7
          i32.const 1
          i32.add
          local.set 7
          local.get 9
          i32.const 255
          i32.and
          i32.eqz
          local.get 12
          i32.and
          local.set 12
          local.get 6
          call $div10
          local.tee 21
          i32.wrap_i64
          i32.const -10
          i32.mul
          local.get 6
          i32.wrap_i64
          i32.add
          local.set 9
          local.get 20
          local.set 10
          local.get 19
          local.set 17
          local.get 21
          local.set 6
          local.get 15
          local.set 18
          br 0 (;@3;)
        end
      end
      i32.const 1
      local.set 15
      block  ;; label = @2
        local.get 14
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        loop  ;; label = @3
          local.get 10
          call $div10
          local.tee 20
          i32.wrap_i64
          i32.const -10
          i32.mul
          i32.const 0
          local.get 10
          i32.wrap_i64
          i32.sub
          i32.ne
          br_if 1 (;@2;)
          local.get 7
          i32.const 1
          i32.add
          local.set 7
          local.get 9
          i32.const 255
          i32.and
          i32.eqz
          local.get 12
          i32.and
          local.set 12
          local.get 17
          call $div10
          local.set 17
          local.get 6
          call $div10
          local.tee 19
          i32.wrap_i64
          i32.const -10
          i32.mul
          local.get 6
          i32.wrap_i64
          i32.add
          local.set 9
          local.get 20
          local.set 10
          local.get 19
          local.set 6
          br 0 (;@3;)
        end
      end
      block  ;; label = @2
        block  ;; label = @3
          local.get 18
          local.get 6
          local.get 10
          i64.ne
          i32.or
          i32.const 1
          i32.and
          br_if 0 (;@3;)
          local.get 11
          i64.eqz
          local.get 14
          i32.and
          i32.eqz
          br_if 1 (;@2;)
        end
        local.get 12
        i32.const -1
        i32.xor
        local.get 9
        i32.const 255
        i32.and
        local.tee 12
        i32.const 5
        i32.ne
        i32.or
        local.get 6
        i32.wrap_i64
        i32.or
        local.get 12
        i32.const 4
        i32.gt_u
        i32.and
        local.set 15
      end
      local.get 7
      local.get 13
      i32.add
      local.set 7
      local.get 6
      local.get 15
      i64.extend_i32_u
      i64.add
      local.tee 6
      call $decimalLength17
      local.set 12
      block  ;; label = @2
        local.get 15
        i32.eqz
        br_if 0 (;@2;)
        local.get 12
        local.get 16
        i32.le_s
        br_if 0 (;@2;)
        block  ;; label = @3
          local.get 3
          i32.eqz
          br_if 0 (;@3;)
          local.get 2
          local.get 7
          local.get 4
          i32.add
          local.get 12
          i32.add
          local.tee 9
          i32.const 0
          local.get 9
          i32.const 0
          i32.gt_s
          select
          local.tee 9
          local.get 2
          local.get 9
          i32.lt_s
          select
          local.set 16
        end
        local.get 12
        local.get 16
        i32.le_s
        br_if 0 (;@2;)
        local.get 12
        i32.const -1
        i32.add
        local.set 12
        local.get 7
        i32.const 1
        i32.add
        local.set 7
        local.get 6
        i64.const 5
        i64.add
        i64.const 10
        i64.div_u
        local.set 6
      end
      local.get 12
      local.get 16
      local.get 12
      local.get 16
      i32.lt_s
      select
      i32.extend16_s
      local.tee 9
      i32.const 0
      local.get 9
      i32.const 0
      i32.gt_s
      select
      local.set 12
      local.get 7
      i32.extend16_s
      i32.const -1
      i32.add
      local.set 14
      local.get 9
      local.get 1
      i32.add
      i32.const 4
      i32.add
      local.set 7
      block  ;; label = @2
        loop  ;; label = @3
          local.get 12
          i32.eqz
          br_if 1 (;@2;)
          local.get 7
          local.get 6
          local.get 6
          i64.const 10
          i64.div_u
          local.tee 10
          i64.const 10
          i64.mul
          i64.sub
          i32.wrap_i64
          i32.const 48
          i32.or
          i32.store8
          local.get 7
          i32.const -1
          i32.add
          local.set 7
          local.get 12
          i32.const -1
          i32.add
          local.set 12
          local.get 10
          local.set 6
          br 0 (;@3;)
        end
      end
      local.get 1
      local.get 8
      i32.store8 offset=4
      local.get 1
      local.get 14
      local.get 9
      i32.add
      i32.store
    end
    local.get 5
    i32.const 32
    i32.add
    global.set $__stack_pointer
    local.get 9)
  (func $mulShiftAll64 (type 10) (param i64 i32 i32 i32 i32 i32) (result i64)
    local.get 3
    local.get 0
    i64.const 2
    i64.shl
    local.tee 0
    i64.const 2
    i64.or
    local.get 1
    local.get 2
    call $mulShift64
    i64.store
    local.get 4
    local.get 0
    local.get 5
    i64.extend_i32_u
    i64.const -1
    i64.xor
    i64.add
    local.get 1
    local.get 2
    call $mulShift64
    i64.store
    local.get 0
    local.get 1
    local.get 2
    call $mulShift64)
  (func $umulh (type 11) (param i64) (result i64)
    (local i32)
    global.get $__stack_pointer
    i32.const 16
    i32.sub
    local.tee 1
    global.set $__stack_pointer
    local.get 0
    i64.const -3689348814741910323
    local.get 1
    i32.const 8
    i32.add
    call $__umul128
    drop
    local.get 1
    i64.load offset=8
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $decimalLength17 (type 12) (param i64) (result i32)
    (local i32 i64)
    i32.const 1
    local.set 1
    i64.const 10
    local.set 2
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        local.get 0
        i64.gt_u
        br_if 1 (;@1;)
        local.get 2
        i64.const 10
        i64.mul
        local.set 2
        local.get 1
        i32.const 1
        i32.add
        local.set 1
        br 0 (;@2;)
      end
    end
    local.get 1)
  (func $div10 (type 11) (param i64) (result i64)
    local.get 0
    call $umulh
    i64.const 3
    i64.shr_u)
  (func $mulShift64 (type 13) (param i64 i32 i32) (result i64)
    (local i32 i64)
    global.get $__stack_pointer
    i32.const 48
    i32.sub
    local.tee 3
    global.set $__stack_pointer
    local.get 3
    i32.const 16
    i32.add
    local.get 1
    i64.load
    i64.const 0
    local.get 0
    i64.const 0
    call $__multi3
    local.get 3
    i32.const 32
    i32.add
    local.get 1
    i64.load offset=8
    i64.const 0
    local.get 0
    i64.const 0
    call $__multi3
    local.get 3
    local.get 3
    i32.const 16
    i32.add
    i32.const 8
    i32.add
    i64.load
    local.tee 0
    local.get 3
    i64.load offset=32
    i64.add
    local.tee 4
    local.get 3
    i32.const 32
    i32.add
    i32.const 8
    i32.add
    i64.load
    local.get 4
    local.get 0
    i64.lt_u
    i64.extend_i32_u
    i64.add
    local.get 2
    i32.const -64
    i32.add
    call $__lshrti3
    local.get 3
    i64.load
    local.set 0
    local.get 3
    i32.const 48
    i32.add
    global.set $__stack_pointer
    local.get 0)
  (func $__log10Pow2 (type 3) (param i32) (result i32)
    local.get 0
    i32.const 78913
    i32.mul
    i32.const 18
    i32.shr_u)
  (func $__log10Pow5 (type 3) (param i32) (result i32)
    local.get 0
    i32.const 732923
    i32.mul
    i32.const 20
    i32.shr_u)
  (func $__pow5bits (type 3) (param i32) (result i32)
    local.get 0
    i32.const 1217359
    i32.mul
    i32.const 19
    i32.shr_u
    i32.const 1
    i32.add)
  (func $__pow5Factor (type 12) (param i64) (result i32)
    (local i32)
    i32.const -1
    local.set 1
    loop  ;; label = @1
      local.get 1
      i32.const 1
      i32.add
      local.set 1
      local.get 0
      i64.const -3689348814741910323
      i64.mul
      local.tee 0
      i64.const 3689348814741910324
      i64.lt_u
      br_if 0 (;@1;)
    end
    local.get 1)
  (func $__double_computePow5 (type 14) (param i32 i32)
    (local i32 i32 i32 i64 i64)
    global.get $__stack_pointer
    i32.const 64
    i32.sub
    local.tee 2
    global.set $__stack_pointer
    local.get 0
    i32.const 26
    i32.div_u
    local.tee 3
    i32.const 4
    i32.shl
    i32.const 1104
    i32.add
    local.set 4
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        local.get 3
        i32.const 26
        i32.mul
        local.tee 3
        i32.ne
        br_if 0 (;@2;)
        local.get 4
        i64.load offset=8
        local.set 5
        local.get 4
        i64.load
        local.set 6
        br 1 (;@1;)
      end
      local.get 2
      i32.const 16
      i32.add
      local.get 4
      i64.load
      i64.const 0
      local.get 0
      local.get 3
      i32.sub
      i32.const 3
      i32.shl
      i32.const 1312
      i32.add
      i64.load
      local.tee 5
      i64.const 0
      call $__multi3
      local.get 2
      i32.const 48
      i32.add
      local.get 4
      i64.load offset=8
      i64.const 0
      local.get 5
      i64.const 0
      call $__multi3
      local.get 0
      call $__pow5bits
      local.set 4
      local.get 3
      call $__pow5bits
      local.set 3
      local.get 2
      local.get 2
      i64.load offset=16
      local.get 2
      i32.const 16
      i32.add
      i32.const 8
      i32.add
      i64.load
      local.get 4
      local.get 3
      i32.sub
      local.tee 4
      call $__lshrti3
      local.get 2
      i32.const 32
      i32.add
      local.get 2
      i64.load offset=48
      local.get 2
      i32.const 48
      i32.add
      i32.const 8
      i32.add
      i64.load
      i32.const 64
      local.get 4
      i32.sub
      call $__ashlti3
      local.get 2
      i32.const 32
      i32.add
      i32.const 8
      i32.add
      i64.load
      local.get 2
      i32.const 8
      i32.add
      i64.load
      i64.add
      local.get 2
      i64.load offset=32
      local.tee 6
      local.get 2
      i64.load
      i64.add
      local.tee 5
      local.get 6
      i64.lt_u
      i64.extend_i32_u
      i64.add
      local.get 5
      local.get 0
      i32.const 2
      i32.shr_u
      i32.const 1073741820
      i32.and
      i32.const 1520
      i32.add
      i32.load
      local.get 0
      i32.const 1
      i32.shl
      i32.shr_u
      i32.const 3
      i32.and
      i64.extend_i32_u
      i64.add
      local.tee 6
      local.get 5
      i64.lt_u
      i64.extend_i32_u
      i64.add
      local.set 5
    end
    local.get 1
    local.get 5
    i64.store offset=8
    local.get 1
    local.get 6
    i64.store
    local.get 2
    i32.const 64
    i32.add
    global.set $__stack_pointer)
  (func $__double_computeInvPow5 (type 14) (param i32 i32)
    (local i32 i32 i32 i64 i64)
    global.get $__stack_pointer
    i32.const 64
    i32.sub
    local.tee 2
    global.set $__stack_pointer
    local.get 0
    i32.const 25
    i32.add
    i32.const 26
    i32.div_u
    local.tee 3
    i32.const 4
    i32.shl
    i32.const 1616
    i32.add
    local.set 4
    block  ;; label = @1
      block  ;; label = @2
        local.get 3
        i32.const 26
        i32.mul
        local.tee 3
        local.get 0
        i32.ne
        br_if 0 (;@2;)
        local.get 4
        i64.load offset=8
        local.set 5
        local.get 4
        i64.load
        local.set 6
        br 1 (;@1;)
      end
      local.get 2
      i32.const 48
      i32.add
      local.get 4
      i64.load
      i64.const -1
      i64.add
      i64.const 0
      local.get 3
      local.get 0
      i32.sub
      i32.const 3
      i32.shl
      i32.const 1312
      i32.add
      i64.load
      local.tee 5
      i64.const 0
      call $__multi3
      local.get 2
      i32.const 16
      i32.add
      local.get 4
      i64.load offset=8
      i64.const 0
      local.get 5
      i64.const 0
      call $__multi3
      local.get 3
      call $__pow5bits
      local.set 4
      local.get 0
      call $__pow5bits
      local.set 3
      local.get 2
      i32.const 32
      i32.add
      local.get 2
      i64.load offset=48
      local.get 2
      i32.const 48
      i32.add
      i32.const 8
      i32.add
      i64.load
      local.get 4
      local.get 3
      i32.sub
      local.tee 4
      call $__lshrti3
      local.get 2
      local.get 2
      i64.load offset=16
      local.get 2
      i32.const 16
      i32.add
      i32.const 8
      i32.add
      i64.load
      i32.const 64
      local.get 4
      i32.sub
      call $__ashlti3
      local.get 2
      i32.const 32
      i32.add
      i32.const 8
      i32.add
      i64.load
      local.get 2
      i32.const 8
      i32.add
      i64.load
      i64.add
      local.get 2
      i64.load offset=32
      local.tee 6
      local.get 2
      i64.load
      i64.add
      local.tee 5
      local.get 6
      i64.lt_u
      i64.extend_i32_u
      i64.add
      local.get 5
      local.get 0
      i32.const 2
      i32.shr_u
      i32.const 1073741820
      i32.and
      i32.const 1856
      i32.add
      i32.load
      local.get 0
      i32.const 1
      i32.shl
      i32.shr_u
      i32.const 3
      i32.and
      i64.extend_i32_u
      i64.add
      local.tee 6
      local.get 5
      i64.lt_u
      i64.extend_i32_u
      i64.add
      local.get 6
      i64.const 1
      i64.add
      local.tee 6
      i64.eqz
      i64.extend_i32_u
      i64.add
      local.set 5
    end
    local.get 1
    local.get 5
    i64.store offset=8
    local.get 1
    local.get 6
    i64.store
    local.get 2
    i32.const 64
    i32.add
    global.set $__stack_pointer)
  (func $__umul128 (type 15) (param i64 i64 i32) (result i64)
    (local i64 i64 i64)
    local.get 2
    local.get 1
    i64.const 4294967295
    i64.and
    local.tee 3
    local.get 0
    i64.const 4294967295
    i64.and
    local.tee 4
    i64.mul
    local.tee 5
    i64.const 32
    i64.shr_u
    local.get 3
    local.get 0
    i64.const 32
    i64.shr_u
    local.tee 0
    i64.mul
    i64.add
    local.tee 3
    i64.const 32
    i64.shr_u
    local.get 1
    i64.const 32
    i64.shr_u
    local.tee 1
    local.get 0
    i64.mul
    i64.add
    local.get 3
    i64.const 4294967295
    i64.and
    local.get 1
    local.get 4
    i64.mul
    i64.add
    local.tee 0
    i64.const 32
    i64.shr_u
    i64.add
    i64.store
    local.get 0
    i64.const 32
    i64.shl
    local.get 5
    i64.const 4294967295
    i64.and
    i64.or)
  (func $__shiftright128 (type 15) (param i64 i64 i32) (result i64)
    local.get 1
    i32.const 64
    local.get 2
    i32.sub
    i64.extend_i32_u
    i64.shl
    local.get 0
    local.get 2
    i64.extend_i32_u
    i64.shr_u
    i64.or)
  (func $__ashlti3 (type 16) (param i32 i64 i64 i32)
    (local i64)
    block  ;; label = @1
      block  ;; label = @2
        local.get 3
        i32.const 64
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 1
        local.get 3
        i32.const -64
        i32.add
        i64.extend_i32_u
        i64.shl
        local.set 2
        i64.const 0
        local.set 1
        br 1 (;@1;)
      end
      local.get 3
      i32.eqz
      br_if 0 (;@1;)
      local.get 1
      i32.const 64
      local.get 3
      i32.sub
      i64.extend_i32_u
      i64.shr_u
      local.get 2
      local.get 3
      i64.extend_i32_u
      local.tee 4
      i64.shl
      i64.or
      local.set 2
      local.get 1
      local.get 4
      i64.shl
      local.set 1
    end
    local.get 0
    local.get 1
    i64.store
    local.get 0
    local.get 2
    i64.store offset=8)
  (func $__lshrti3 (type 16) (param i32 i64 i64 i32)
    (local i64)
    block  ;; label = @1
      block  ;; label = @2
        local.get 3
        i32.const 64
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 2
        local.get 3
        i32.const -64
        i32.add
        i64.extend_i32_u
        i64.shr_u
        local.set 1
        i64.const 0
        local.set 2
        br 1 (;@1;)
      end
      local.get 3
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      i32.const 64
      local.get 3
      i32.sub
      i64.extend_i32_u
      i64.shl
      local.get 1
      local.get 3
      i64.extend_i32_u
      local.tee 4
      i64.shr_u
      i64.or
      local.set 1
      local.get 2
      local.get 4
      i64.shr_u
      local.set 2
    end
    local.get 0
    local.get 1
    i64.store
    local.get 0
    local.get 2
    i64.store offset=8)
  (func $__multi3 (type 17) (param i32 i64 i64 i64 i64)
    (local i64)
    local.get 0
    local.get 4
    local.get 1
    i64.mul
    local.get 2
    local.get 3
    i64.mul
    i64.add
    local.get 3
    i64.const 32
    i64.shr_u
    local.tee 2
    local.get 1
    i64.const 32
    i64.shr_u
    local.tee 4
    i64.mul
    i64.add
    local.get 3
    i64.const 4294967295
    i64.and
    local.tee 3
    local.get 1
    i64.const 4294967295
    i64.and
    local.tee 1
    i64.mul
    local.tee 5
    i64.const 32
    i64.shr_u
    local.get 3
    local.get 4
    i64.mul
    i64.add
    local.tee 3
    i64.const 32
    i64.shr_u
    i64.add
    local.get 3
    i64.const 4294967295
    i64.and
    local.get 2
    local.get 1
    i64.mul
    i64.add
    local.tee 1
    i64.const 32
    i64.shr_u
    i64.add
    i64.store offset=8
    local.get 0
    local.get 1
    i64.const 32
    i64.shl
    local.get 5
    i64.const 4294967295
    i64.and
    i64.or
    i64.store)
  (table (;0;) 2 2 funcref)
  (memory (;0;) 2 2 shared)
  (global $__stack_pointer (mut i32) (i32.const 67536))
  (global $__tls_base (mut i32) (i32.const 0))
  (global $__tls_size i32 (i32.const 0))
  (global $__tls_align i32 (i32.const 0))
  (global (;4;) i32 (i32.const 67536))
  (global (;5;) i32 (i32.const 131072))
  (global (;6;) i32 (i32.const 1992))
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "__heap_base" (global 4))
  (export "__heap_end" (global 5))
  (export "__data_end" (global 6))
  (export "wasm_memory_grow" (func $__wasm_memory_grow))
  (export "wasm_memory_size" (func $__wasm_memory_size))
  (start $__wasm_init_memory)
  (elem (;0;) (i32.const 1) func $picolibc_putc)
  (data $.rodata "\98\07\00\00nan\00Mystring\00inf\00(null)\00Hello World\0a\00String: %s | Testnum: %d\0a\00Num[%d]: %d\0a\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\10\00\00\00\00\00\00\00\00\b94\032\b7\f4\ad\14\10\db\1a\b3\08\92T\0e\0d0}\95\14G\ba\1af\08\8fM&\ad\c6m\f5\98\bf\85\e2\b7E\11\ca\96\85=\92\bd\1d\eb\fc\a1\18`\dc\efR\16<\92\ae\22\0b\b8\c1\b4\83\9d-[\05b\da\1c0L~\8fN\8b\b2[\16\f4R\9f\8bV\a5\12\fb\d4\82vC\ed\8a\f0\8f\e7\f91\15e\19\18P\f1\9b\d9J\13\ee\b4(L\f0\a6\86\c1%\1f\03_\c2p\cb\9eI\16\e6B\88\9cD\eb \14\b0e\086\adn\a5\85\85\f0\ca\14\e2\fd\03\1a\0b\89\99y\d5\b1=\09\d8\da\97:5\eb\cf\10\ac6?^s\bb8\cf>gR\faD\af\ba\15\01\00\00\00\00\00\00\00\05\00\00\00\00\00\00\00\19\00\00\00\00\00\00\00}\00\00\00\00\00\00\00q\02\00\00\00\00\00\005\0c\00\00\00\00\00\00\09=\00\00\00\00\00\00-1\01\00\00\00\00\00\e1\f5\05\00\00\00\00\00e\cd\1d\00\00\00\00\00\f9\02\95\00\00\00\00\00\dd\0e\e9\02\00\00\00\00QJ\8d\0e\00\00\00\00\95s\c2H\00\00\00\00\e9A\cck\01\00\00\00\8dI\fd\1a\07\00\00\00\c1o\f2\86#\00\00\00\c5.\bc\a2\b1\00\00\00\d9\e9\ac-x\03\00\00=\91`\e4X\11\00\001\d6\e2u\bcV\00\00\f5.nM\ae\b1\01\00\c9\ea&\83gx\08\00\ed\95\c2\8f\05Z*\00\a1\ed\cc\ce\1b\c2\d3\00%\a4\00\0a\8b\ca\22\04\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00@\95YiYUUTU\15UUV\04\05\15A\10TU@EQUD@EPDPUUE\00@\00@@\04D\96eUVUE@ETQA\15@U\91UUUU@Q\05\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00 4Pe\c0_\c9\a6R\bb\13\cb\ae\c4@\c2\18\06\c8\dfq\00\d5\a8|\f5o\0f\daX\fc'\13nGV5}$ e\02\c7\e7h\e4\8c\a4\1d\e9\e6\02h\d7\cd9ayw\fc\c2@[\ef\16y\8c\deC\ff\a7Q\f9\91\f3\b2x\f5\bd\be\11\e8W\e9\d6\e8\be\e8{\b0T\ac\8f\84\8du\1b\ea#\a4\99\e9\f9\d3\8b\b7\a3q@a\da>\15\ce\e3>\cbs\f9H\08\8c\97\b4'\d5\1bp\10\a2\bf\ef\b9\eb\852\15M\b4M\b4\9b\bbo\19\96\b6\07l\f8\e7\ee\ad6\d9\b4\f5\915\ae\13\22\22\18\afNjhM\91\da\aa=O@t\1e\9f\bd\9e\e0\06\a1\c0\98W\c2\a7\fd\a4\0e\90\17\0e}Iqs\e3 \8f\b2 \d8v\05\14;\12\85=t4\81\13C\b0\ad)z_'\f45\1cTETTEU\05\04\00\10\04\10\14\04@\00\00\00\01@UU\15AT\04\00\00D\00\01\00\00\00\00@A\00\00DPDEPT\00UUTUeQ\00@\00@\01\00\00\01\00\05\01\00\11TQQTUU\05\00\00\00\00\00\00\00\00\00\00\00\00")
  (data $.data "\04\00\00\00\00\00\00\00\02\00\00\00\01\00\00\00\00\00\00\00\00\00\00\00\d0\07\01\00"))
