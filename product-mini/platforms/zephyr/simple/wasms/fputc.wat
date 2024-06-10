(module
  (type (;0;) (func (param i32) (result i32)))
  (type (;1;) (func (param i32 i32) (result i32)))
  (type (;2;) (func (param i32)))
  (import "env" "puts" (func (;0;) (type 0)))
  (import "env" "malloc" (func (;1;) (type 0)))
  (import "env" "printf" (func (;2;) (type 1)))
  (import "env" "free" (func (;3;) (type 2)))
  (import "wazi" "SYS_zephyr_fputc" (func (;4;) (type 1)))
  (func (;5;) (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    global.set 0
    i32.const 1051
    call 0
    drop
    block  ;; label = @1
      block  ;; label = @2
        i32.const 1024
        call 1
        local.tee 3
        br_if 0 (;@2;)
        i32.const 1064
        call 0
        drop
        i32.const -1
        local.set 4
        br 1 (;@1;)
      end
      local.get 2
      local.get 3
      i32.store offset=16
      i32.const 1024
      local.get 2
      i32.const 16
      i32.add
      call 2
      drop
      i32.const 0
      local.set 4
      local.get 3
      i32.const 4
      i32.add
      i32.const 0
      i32.load16_u offset=1041 align=1
      i32.store16 align=1
      local.get 3
      i32.const 0
      i32.load offset=1037 align=1
      i32.store align=1
      local.get 2
      local.get 3
      i32.store
      i32.const 1043
      local.get 2
      call 2
      drop
      local.get 3
      call 3
    end
    ;; fputc
    block 
      ;; stdout = (FILE*) 2
      i32.const 65
      i32.const 2
      call 4
      drop
      i32.const 66
      i32.const 2
      call 4
      drop
      i32.const 67
      i32.const 2
      call 4
      drop
      i32.const 10
      i32.const 2
      call 4
      drop
    end
    ;; end of fputc
    local.get 2
    i32.const 32
    i32.add
    global.set 0
    local.get 4)
  (table (;0;) 1 1 funcref)
  (memory (;0;) 1)
  (global (;0;) (mut i32) (i32.const 5184))
  (global (;1;) i32 (i32.const 1082))
  (global (;2;) i32 (i32.const 5184))
  (export "memory" (memory 0))
  (export "__data_end" (global 1))
  (export "__heap_base" (global 2))
  (export "main" (func 5))
  (data (;0;) (i32.const 1024) "buf ptr: %p\0a\001234\0a\00buf: %s\00Hello world!\00malloc buf failed\00"))
