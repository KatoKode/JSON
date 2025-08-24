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
;
%ifndef MEMMOVE64_ASM
%define MEMMOVE64_ASM 1
;
QW_SIZE     EQU     8
;
;-------------------------------------------------------------------------------
; C definition:
;
;   void * memmove64 (void *dst, void const *src, size_t sz);
;
; passed in:
;
;   rdi = dst
;   rsi = src
;   rdx = sz
;
; return:
;
;   rax = dst
;
; WARNING: this routine does not handle the overlapping source-destination
;          senario.
;-------------------------------------------------------------------------------
;
section .text
      global memmove64:function
memmove64:
      push      rdi
      mov       rax, rdx
      xor       rdx, rdx
      mov       r11, QW_SIZE
      div       r11
      mov       rcx, rax
      rep movsq
      mov       rcx, rdx
      rep movsb
      pop       rax
      ret
%endif
