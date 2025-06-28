;-------------------------------------------------------------------------------
;   JSON Library Implementation in C with Assembly Language Support Libraries
;   Copyright (C) 2025  J. McIntosh
;
;   This program is free software; you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation; either version 2 of the License, or
;   (at your option) any later version.
;
;   This program is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License along
;   with this program; if not, write to the Free Software Foundation, Inc.,
;   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
;-------------------------------------------------------------------------------
%ifndef LIFO_ASM
%define LIFO_ASM  1
; file:   lifo.asm
; data:   2025-02-22
; author: J. McIntosh
; brief:  last-in-first-out (lifo) lifo for 8-byte values
;-------------------------------------------------------------------------------
;
extern bzero
extern calloc
extern free
;
QW_SIZE     EQU     8
;
%include "lifo.inc"
;
section .text
;
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   int lifo_empty (lifo_t *lifo);
;
; param:
;
;   rdi = lifo
;
; return:
;
;   rax = 0 (false) | 1 (true)
;-------------------------------------------------------------------------------
;
      global lifo_empty:function
lifo_empty:
; if (lifo->head == lifo->buffer) return 1
      mov       eax, 1
      mov       rcx, QWORD [rdi + lifo.head]
      cmp       rcx, QWORD [rdi + lifo.buffer]
      je        .return
; return 0
      xor       eax, eax
.return:
      ret
;
;-------------------------------------------------------------------------------
; C/C++ definitions:
;
;   int lifo_full (lifo_t *lifo);
;
; param:
;
;   rdi = lifo
;
; return:
;
;   rax = 0 (false) | 1 (true)
;-------------------------------------------------------------------------------
;
      global lifo_full:function
lifo_full:
; if (lifo->head == lifo->end) return 1
      mov       eax, 1
      mov       rcx, QWORD [rdi + lifo.head]
      cmp       rcx, QWORD [rdi + lifo.end]
      je        .return
; return 0
      xor       eax, eax
.return:
      ret
;
;-------------------------------------------------------------------------------
; C/C++ definitions:
;
;   int lifo_init (lifo_t *lifo, size_t count);
;
; param:
;
;   rdi = lifo
;   rsi = count
;
; return:
;
;   rax = 0 (success) | -1 (failure)
;
; stack:
;
;   QWORD [rbp - 8]   = rdi (lifo)
;   QWORD [rbp - 16]  = rsi (count)
;-------------------------------------------------------------------------------
;
      global lifo_init:function
lifo_init:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 16
; QWORD [rbp - 8] = rdi (lifo);
      mov       QWORD [rbp - 8], rdi
; QWORD [rbp - 16] = rsi (count);
      mov       QWORD [rbp - 16], rsi
; if ((lifo->buffer = calloc(1, buffer_size)) == NULL) return -1
      mov       rdi, rsi
      mov       rsi, QW_SIZE
      call      calloc wrt ..plt
      mov       rdi, QWORD [rbp - 8]
      mov       QWORD [rdi + lifo.buffer], rax
      mov       QWORD [rdi + lifo.head], rax
      test      rax, rax
      jnz       .calloc_ok
      mov       eax, -1
      jmp       .epilogue
.calloc_ok:
; lifo->end = lifo->buffer + buffer_size
      mov       rax, QW_SIZE
      mul       QWORD [rbp - 16]
      add       rax, QWORD [rdi + lifo.buffer]
      mov       QWORD [rdi + lifo.end], rax
; return 0
      xor       eax, eax
.epilogue:
      mov       rsp, rbp
      pop       rbp
      ret
;
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   void * lifo_pop (lifo_t *lifo)
;
; param:
;
;   rdi = lifo
;
; return:
;
;   rax = address (success) | NULL (failure)
;-------------------------------------------------------------------------------
;
      global lifo_pop:function
lifo_pop:
; if (lifo->head == lifo->buffer) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + lifo.head]
      cmp       rcx, QWORD [rdi + lifo.buffer]
      je        .return
; lifo->head -= QW_SIZE;
      sub       rcx, QW_SIZE
      mov       QWORD [rdi + lifo.head], rcx
; return *lifo->head;
      mov       rax, QWORD [rcx]
.return:
      ret
;
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   void * lifo_push (lifo_t *lifo, void *value)
;
; param:
;
;   rdi = lifo
;   rsi = value
;
; return:
;
;   rax = value (success) | NULL (failure)
;
; stack:
;
;   QWORD [rbp - 8]  = rdi (lifo}
;-------------------------------------------------------------------------------
;
section .text
      global lifo_push:function
lifo_push:
; if (lifo->head == lifo->end) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + lifo.head]
      cmp       rcx, QWORD [rdi + lifo.end]
      je        .return
; *list->head = *value;
      mov       rax, rsi  ; rax = value (success)
      mov       QWORD [rcx], rax
; lifo->head += QW_SIZE;
      add       rcx, QW_SIZE
      mov       QWORD [rdi + lifo.head], rcx
.return:
      ret
;
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   void lifo_term (lifo_t *lifo)
;
; param:
;
;   rdi = lifo
;
; lifo:
;
;   QWORD [rbp - 8] = rdi (lifo}
;-------------------------------------------------------------------------------
;
      global lifo_term:function
lifo_term:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 8
; QWORD [rbp - 8] = rdi (lifo}
      mov       QWORD [rbp - 8], rdi
; free item lifo memory
      mov       rax, QWORD [rdi + lifo.buffer]
      mov       rdi, rax
      call      free wrt ..plt
; zero out lifo structure
      mov       rdi, QWORD [rbp - 8]
      mov       rsi, lifo_size
      call      bzero wrt ..plt
; epilogue
      mov       rsp, rbp
      pop       rbp
      ret
;
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   void * lifo_top (lifo_t *lifo)
;
; param:
;
;   rdi = lifo
;
; return:
;
;   rax = address (success) | NULL (failure)
;-------------------------------------------------------------------------------
;
      global lifo_top:function
lifo_top:
; if (lifo->head == lifo->buffer) return NULL;
      xor       rax, rax
      mov       rcx, QWORD [rdi + lifo.head]
      cmp       rcx, QWORD [rdi + lifo.buffer]
      je        .return
; return *lifo->head;
      sub       rcx, QW_SIZE
      mov       rax, QWORD [rcx]
.return:
      ret
%endif
