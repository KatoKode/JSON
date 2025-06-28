;-------------------------------------------------------------------------------
;   Assembly Language Implementation of a B-Tree
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
; file:   string.asm
; date:   2024-01-20
; author: J. McIntosh
; brief:  string operation routines
%ifndef STRING_ASM
%define STRING_ASM
;-------------------------------------------------------------------------------
extern calloc
extern strlen
extern toupper
extern memmove64
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   char* substring (char *src, size_t start, size_t end)
; 
; param:
;
;   rdi = src
;   rsi = start
;   rdx = end
;
; return:
;
;   rax = &substring | null
;
; stack:
;
; [rbp - 8]   = rdi (src)
; [rbp - 16]  = rsi (start)
; [rbp - 24]  = (end - start) = (size)
;
; NOTE: Memory is allocated (for substring) and address is returned in rax.
;
; WARNING: This routine does not check for:
;             - src == NULL
;             - Invalid start value
;             - Invalid end value
;
section .data
;
NULL        EQU     0
;
section .bss
;
section .text
      global substring:function
substring:
      push      rbp
      mov       rbp, rsp
      sub       rsp, 24
; store rdi (src), rsi (start), (size) = (end - start)
      mov       QWORD [rbp - 8], rdi
      mov       QWORD [rbp - 16], rsi
      mov       rax, rdx
      sub       rax, rsi
      mov       QWORD [rbp - 24], rax
; substring = calloc (1, size + 1)
      mov       rdi, 1
      mov       rsi, rax
      inc       rsi   ; for null-terminator
      call      calloc wrt ..plt
      cmp       rax, NULL
      je        .failure
; rax = memmove64(substring, &src[start], size);
      mov       rdi, rax
      mov       rsi, QWORD [rbp - 8]
      add       rsi, QWORD [rbp - 16]
      mov       rdx, QWORD [rbp - 24]
      call      memmove64 wrt ..plt
.failure:
      mov       rsp, rbp
      pop       rbp
      ret
;-------------------------------------------------------------------------------
; C/C++ definition:
;
;   char* strupper (char *src)
; 
; param:
;
;   rdi = src
;
; return:
;
;   rax = src | NULL
;
; stack:
;
;   [rbp - 8] = rdi (src)
;
; WARNING: this routine does not check for: src == null.
;
section .data
;
section .bss
;
section .text
      global strupper:function
strupper:
; prologue
      push      rbp
      mov       rbp, rsp
      sub       rsp, 8
; stor rdi (src) on stack
      mov       QWORD [rbp - 8], rdi
; r15 = src
      mov       r15, rdi
; convert src to uppercase
      xor       rdi, rdi
.loop:
      xor       al, al
      cmp       al, BYTE [r15]
      je        .epilogue
      mov       dil, BYTE [r15]
      call      toupper wrt ..plt
      mov       BYTE [r15], al
      inc       r15
      loop      .loop
.epilogue:
      mov       rax, QWORD [rbp - 8]
      mov       rsp, rbp
      pop       rbp
      ret
;-------------------------------------------------------------------------------
%endif

