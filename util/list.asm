;-------------------------------------------------------------------------------
;   JSON (JSON) Library Implementation in C with Assembly Language Support
;   Libraries
;
;   Copyright (C) 2025  J. McIntosh
;
;   JSON is free software; you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation; either version 2 of the License, or
;   (at your option) any later version.
;
;   JSON is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License along
;   with JSON; if not, write to the Free Software Foundation, Inc.,
;   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
;-------------------------------------------------------------------------------
%ifndef LIST_ASM
%define LIST_ASM  1
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern bsearch
extern bzero
extern calloc
extern free
extern qsort
extern memmove64
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
LIST_COUNT    EQU     16
;
ALIGN_SIZE_8  EQU     8
ALIGN_MASK_8  EQU     ~(ALIGN_SIZE_8 - 1)
;
ALIGN_SIZE_16 EQU     16
ALIGN_MASK_16 EQU     ~(ALIGN_SIZE_16 - 1)
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
%macro ALIGN_STACK_AND_CALL 2-4
      mov     %1, rsp                   ; backup stack pointer (rsp)
      and     rsp, QWORD ALIGN_MASK_16  ; align stack pointer (rsp) to
                                        ; 16-byte boundary
      call    %2 %3 %4                  ; call C function
      mov     rsp, %1                   ; restore stack pointer (rsp)
%endmacro
;
; Example: Call LIBC function
;         ALIGN_STACK_AND_CALL r15, calloc, wrt, ..plt
;
; Example: Call C callback function with address in register (rcx)
;         ALIGH_STACK_AND_CALL r12, rcx
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
%include "list.inc"
;
section .text
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   int list_add (list_t *list, void const *object);
;
; param:
;
;   rdi = list
;   rsi = object
;
; return:
;
;   rax = 0 (success) | -1 (failure)
;
; stack:
;
;   [rbp - 8]   = rdi (list)
;   [rbp - 16]  = rsi (object)
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_add:function
list_add:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 16
; store rdi (list) and rsi (object) on stack
      mov       QWORD [rbp - 8], rdi
      mov       QWORD [rbp - 16], rsi
; if (list->next >= list->bufend) {
      mov       rcx, QWORD [rdi + list.next]
      cmp       rcx, QWORD [rdi + list.bufend]
      jb        .continue
;   if (list_new(list) == NULL)) return -1;
      call      list_new
      test      rax, rax
      jnz       .continue
      mov       eax, -1
      jmp       .epilogue
; }
.continue:
; (void) memmove64(list->next, object, list->o_size);
      mov       rdi, QWORD [rbp - 8]
      mov       rdx, QWORD [rdi + list.o_size]
      mov       rsi, QWORD [rbp - 16]
      mov       rdi, QWORD [rdi + list.next]
      call      memmove64 wrt ..plt
; list->next += list->s_size;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rdi + list.next]
      add       rax, QWORD [rdi + list.s_size]
      mov       QWORD [rdi + list.next], rax
; return 0;
      xor       eax, eax
.epilogue:
      mov       rsp, rbp
      pop       rbp
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_at (list_t *list, size_t const index);
;
; param:
;
;   rdi = list
;   rsi = index 
;
; return:
;
;   rax = address of object at index | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_at:function
list_at:
; void *ptr = list->buffer + (list->s_size * index);
      mov       rax, QWORD [rdi + list.s_size]
      mul       rsi
      add       rax, QWORD [rdi + list.buffer]
; if (ptr < list->blkend) return ptr;
      cmp       rax, QWORD [rdi + list.blkend]
      jb       .return
; return NULL;
      xor       rax, rax
.return:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_begin (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = &list->buffer[ 0 ] | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_begin:function
list_begin:
; if (list->buffer >= list->next) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.buffer]
      cmp       rcx, QWORD [rdi + list.blkend]
      jae       .epilogue
; list->iter = list->buffer;
      mov       QWORD [rdi + list.iter], rcx
; return list->iter;
      mov       rax, rcx
.epilogue:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   size_t list_count (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   number of objects in list
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
section .text
      global list_count:function
list_count:
; size_t blk_size = list->blkend - list->buffer;
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, QWORD [rdi + list.buffer]
      jz        .return
; return (blk_size / list->s_size);
      xor       rdx, rdx
      div       QWORD [rdi + list.s_size]
.return:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_curr (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = list->iter | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_curr:function
list_curr:
; if (list->iter <= list->buffer) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.iter]
      cmp       rcx, QWORD [rdi + list.buffer]
      jb        .epilogue
; if (list->iter >= list->blkend) return NULL;
      cmp       rcx, QWORD [rdi + list.blkend]
      jae       .epilogue
; return list->iter;
      mov       rax, rcx
.epilogue:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;
; int list_delete(list_t *list, void const *key,
;     int (*find_cb) (void const *, void const *),
;     void (*delete_cb) (void *));
;
; param:
;
;   rdi = list
;   rsi = key
;   rdx = find_cb
;   rcx = delete_cb
;
; return:
;
;   0 (success) | -1 (failure)
;
; stack:
;
;   QWORD [rbp - 8]   = rdi (list)
;   QWORD [rbp - 16]  = rcx (delete_cb)
;   QWORD [rbp - 24]  = (void *target)
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
section .text
      global list_delete:function
list_delete:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 24
      push      r12
; QWORD [rbp - 8] = rdi (list)
      mov       QWORD [rbp - 8], rdi
; QWORD [rbp - 16] = rcx (delete_cb)
      mov       QWORD [rbp - 16], rcx
; if ((target = list_find(list, key, find_cb)) == NULL) return -1;
      call      list_find
      mov       QWORD [rbp - 24], rax
      test      rax, rax
      jnz       .target_found
      mov       eax, -1
      jmp       .epilogue
.target_found:
; delete_cb(target);
      mov       rcx, QWORD [rbp - 16]
      test      rcx, rcx
      jz        .no_delete_cb
      mov       rdi, rax
      ALIGN_STACK_AND_CALL r12, rcx
.no_delete_cb:
; if (target == (list->blkend - list->s_size)) goto .skip_move;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, QWORD [rdi + list.s_size]
      cmp       rax, QWORD [rbp - 24]
      je       .skip_move
;---------------------------------------
; move objects left one slot to fill gap
; left by deleted object (target)
;---------------------------------------
; blkhead = target + list->s_size;
      mov       rcx, QWORD [rbp - 24]
      add       rcx, QWORD [rdi + list.s_size]
; blksize = (list->blkend - blkhead);
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, rcx
; memmove64(target, blkhead, blksize);
      mov       rdx, rax
      mov       rsi, rcx
      mov       rdi, QWORD [rbp - 24]
      call      memmove64 wrt ..plt
.skip_move:
; list->next -= list->s_size;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, QWORD [rdi + list.s_size]
      mov       QWORD [rdi + list.blkend], rax
; return 0;
      xor       eax, eax
.epilogue:
      pop       r12
      mov       rsp, rbp
      pop       rbp
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_end (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = &list->buffer[ list->count ] | NULL
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      global list_end:function
list_end:
; if (list->next <= list->buffer) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.blkend]
      cmp       rcx, QWORD [rdi + list.buffer]
      jbe       .epilogue
; list->iter = list->blkend - list->s_size;
      sub       rcx, QWORD [rdi + list.s_size]
      mov       QWORD [rdi + list.iter], rcx
; return list->iter;
      mov       rax, rcx
.epilogue:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C declaration:
;
;   void * list_find (list_t const *list, void const *key,
;       int (*find_cb) (void const *, void const *));
;
; param:
;
;   rdi = list
;   rsi = key
;   rdx = find_cb
;
; return:
;
;   eax = iter (address of matching object) | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_find:function
list_find:
      push      rsi
      mov       r8, rdx
      mov       rcx, QWORD [rdi + list.s_size]
      call      list_count
      mov       rdx, rax
      mov       rsi, QWORD [rdi + list.buffer]
      pop       rdi
      call      bsearch wrt ..plt
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   int list_init (list_t *list, size_t const obj_size);
;
; param:
;
;   rdi = list
;   rsi = obj_size
;
; return:
;
;   rax = 0 (success) | -1 (failure)
;
; stack:
;
;   QWORD [rbp - 8]   = rdi (list)
;   QWORD [rbp - 16]  = buffer_size
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_init:function
list_init:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 16
; QWORD [rbp - 8] = rdi (list)
      mov       QWORD [rbp - 8], rdi
; list->o_size = obj_size;
      mov       QWORD [rdi + list.o_size], rsi
; list->s_size = (obj_size + ALIGN_SIZE_8 - 1) & ALIGN_MASK_8;
      mov       rax, rsi
      add       rax, QWORD ALIGN_SIZE_8
      dec       rax
      and       rax, QWORD ALIGN_MASK_8
      test      rax, rax  ; test for 0 and adjust up to 8
      jnz       .not_zero
      mov       rax, QWORD ALIGN_SIZE_8
.not_zero:
      mov       QWORD [rdi + list.s_size], rax
; (rax) buffer_size = list->s_size * LIST_COUNT;
      mov       rcx, QWORD LIST_COUNT
      mul       rcx
      mov       QWORD [rbp - 16], rax
; if ((list->buffer = calloc(1, (rax) buffer_size)) == NULL) return -1;
      mov       rdi, 1
      mov       rsi, rax
      call      calloc wrt ..plt
      mov       rdi, QWORD [rbp - 8]
      mov       QWORD [rdi + list.buffer], rax
      test      rax, rax
      jnz       .continue
      mov       eax, -1
      jmp       .epilogue
.continue:
; list->next = list->buffer;
      mov       rax, QWORD [rdi + list.buffer]
      mov       QWORD [rdi + list.next], rax
; list->bufend = list->buffer + buffer_size;
      mov       rax, QWORD [rdi + list.buffer]
      add       rax, QWORD [rbp - 16]
      mov       QWORD [rdi + list.bufend], rax
; return 0;
      xor       eax, eax
.epilogue:
      mov       rsp, rbp
      pop       rbp
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_new (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = new address in list->buffer | NULL
;
; stack:
;
;   QWORD [rbp - 8]   = rdi (list)
;   QWROD [rbp - 16]  = old_buffer_size
;   QWORD [rbp - 24]  = new_buffer_size
;   QWORD [rbp - 32]  = new_buffer
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_new:function hidden
list_new:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 32
; QWORD [rbp - 8] = rdi (list)
      mov       QWORD [rbp - 8], rdi
; old_buffer_size = (list->bufend - list->buffer);
      mov       rax, QWORD [rdi + list.bufend]
      sub       rax, QWORD [rdi + list.buffer]
      mov       QWORD [rbp - 16], rax
; additional_size = (list->s_size * LIST_COUNT);
      mov       rax, QWORD [rdi + list.s_size]
      mov       rcx, QWORD LIST_COUNT
      mul       rcx
; new_buffer_size = additional_size + old_buffer_size;
      add       rax, QWORD [rbp - 16]
      mov       QWORD [rbp - 24], rax
; if ((new_buffer = calloc(1, new_buffer_size)) == NULL) return NULL;
      mov       rdi, 1
      mov       rsi, rax
      call      calloc wrt ..plt
      test      rax, rax
      jz        .epilogue
      mov       QWORD [rbp - 32], rax
; (void) memmove64(new_buffer, list->buffer, old_buffer_size);
      mov       rdi, QWORD [rbp - 8]
      mov       rdx, QWORD [rbp - 16]
      mov       rsi, QWORD [rdi + list.buffer]
      mov       rdi, QWORD [rbp - 32]
      call      memmove64 wrt ..plt
; list->next = new_buffer + old_buffer_size;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rbp - 32]
      add       rax, QWORD [rbp - 16]
      mov       QWORD [rdi + list.next], rax
; free(list->buffer);
      mov       rdi, QWORD [rdi + list.buffer]
      call      free wrt ..plt
; list->buffer = new_buffer;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rbp - 32]
      mov       QWORD [rdi + list.buffer], rax
; list->bufend = new_buffer + new_buffer_size;
      add       rax, QWORD [rbp - 24]
      mov       QWORD [rdi + list.bufend], rax 
; return new_buffer;
      mov       rax, QWORD [rbp - 32]
.epilogue:
      mov       rsp, rbp
      pop       rbp
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_next (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = list->iter | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_next:function
list_next:
; if ((list->iter + list->s_size) >= list->next) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.iter]
      add       rcx, QWORD [rdi + list.s_size]
      cmp       rcx, QWORD [rdi + list.blkend]
      jae       .return
; list->iter += list->s_size;
      mov       QWORD [rdi + list.iter], rcx
; return list->iter;
      mov       rax, rcx
.return:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   size_t list_object_size (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = list->o_size
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_object_size:function
list_object_size:
      mov       rax, QWORD [rdi + list.o_size]
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_pred (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = (list->iter - list->s_size) | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_pred:function
list_pred:
; if (list->iter <= list->buffer) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.iter]
      cmp       rcx, QWORD [rdi + list.buffer]
      jbe       .return
; void * iter = list->iter - list->s_size;
      sub       rcx, QWORD [rdi + list.s_size]
; return iter;
      mov       rax, rcx
.return:
      ret
;
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_prev (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = list->iter | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_prev:function
list_prev:
; if (list->iter <= list->buffer) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.iter]
      cmp       rcx, QWORD [rdi + list.buffer]
      jbe       .return
; list->iter -= list->s_size;
      sub       rcx, QWORD [rdi + list.s_size]
      mov       QWORD [rdi + list.iter], rcx
; return list->iter;
      mov       rax, rcx
.return:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void list_remove (list_t *list, void const *target,
;       void (*delete_cb) (void *));
;
; param:
;
;   rdi = list
;   rsi = target
;   rdx = delete_cb
;
; stack:
;
;   QWORD [rbp - 8]   = rdi (list)
;   QWORD [rbp - 16]  = rsi (target)
;   QWORD [rbp - 24 ] = rdx (delete_cb)
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_remove:function
list_remove:
; prologue:
      push      rbp
      mov       rbp, rsp
      sub       rsp, 8
      push      r12
; QWORD [rbp - 8] = rdi (list)
      mov       QWORD [rbp - 8], rdi
; QWORD [rbp - 16]  = rsi (target)
      mov       QWORD [rbp - 16], rsi
; QWORD [rbp - 24]  = rdx (delete_cb)
      mov       QWORD [rbp - 24], rdx
; if (target < list->buffer || target > list->blkend) return;
      cmp       rsi, QWORD [rdi + list.buffer]
      jb        .epilogue
      cmp       rsi, QWORD [rdi + list.blkend]
      jae       .epilogue
; if (((target - list->buffer) / list->s_size) != 0L) return;
      xor       rdx, rdx
      mov       rax, rsi
      sub       rax, QWORD [rdi + list.buffer]
      mov       rcx, QWORD [rdi + list.s_size]
      div       rcx
      test      rdx, rdx
      jnz       .epilogue
; if (delect_cb != NULL) delete_cb(object);
      mov       rdx, QWORD [rbp - 24]
      test      rdx, rdx
      jz        .no_delete_cb
      mov       rdi, rsi
      mov       rcx, rdx
      ALIGN_STACK_AND_CALL r12, rcx
.no_delete_cb:
; if (target == (list->blkend - list->s_size)) goto .skip_move;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, QWORD [rdi + list.s_size]
      cmp       rax, QWORD [rbp - 16]
      je       .skip_move
;---------------------------------------
; move objects left one slot to fill gap
; left by deleted object (target)
;---------------------------------------
; blkhead = target + list->s_size;
      mov       rcx, QWORD [rbp - 16]
      add       rcx, QWORD [rdi + list.s_size]
; blksize = (list->blkend - blkhead);
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, rcx
; memmove64(target, blkhead, blksize);
      mov       rdx, rax
      mov       rsi, rcx
      mov       rdi, QWORD [rbp - 16]
      call      memmove64 wrt ..plt
.skip_move:
; list->blkend -= list->s_size;
      mov       rdi, QWORD [rbp - 8]
      mov       rax, QWORD [rdi + list.blkend]
      sub       rax, QWORD [rdi + list.s_size]
      mov       QWORD [rdi + list.blkend], rax
.epilogue:
      pop       r12
      mov       rsp, rbp
      pop       rbp
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   size_t list_slot_size (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = list->o_size
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_slot_size:function
list_slot_size:
      mov       rax, QWORD [rdi + list.s_size]
      ret;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void list_sort (list_t *list, int (*sort_cb) (void const *, void const *));
;
; param:
;
;   rdi = list
;   rsi = sort_cb
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_sort:function
list_sort:
      call      list_count
      mov       rcx, rsi
      mov       rdx, QWORD [rdi + list.o_size]
      mov       rsi, rax
      mov       rdi, QWORD [rdi + list.buffer]
      call      qsort wrt ..plt
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void * list_succ (list_t *list);
;
; param:
;
;   rdi = list
;
; return:
;
;   rax = (list->iter + list->s_size) | NULL
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_succ:function
list_succ:
; if ((list->iter + list->s_size) >= list->next) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + list.iter]
      add       rcx, QWORD [rdi + list.s_size]
      cmp       rcx, QWORD [rdi + list.blkend]
      jae       .return
; return (list->iter + list->s_size);
      mov       rax, rcx
.return:
      ret
;
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
; C definition:
;
;   void list_term (list_t *list)
;
; param:
;
;   rdi = list
;
; stack:
;
;   QWORD [rbp - 8] = rdi (list)
;- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;
      global list_term:function
list_term:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 8
; QWORD [rbp - 8] = rdi (list)
      mov       QWORD [rbp - 8], rdi
; free(list->buffer);
      mov       rdi, QWORD [rdi + list.buffer]
      call      free wrt ..plt
; bzero(list, sizeof(list_t));
      mov       rdi, QWORD [rbp - 8]
      mov       rsi, QWORD list_size
      call      bzero wrt ..plt
; epilogue
      mov       rsp, rbp
      pop       rbp
      ret
%endif

