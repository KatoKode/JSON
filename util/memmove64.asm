; file:   memmove64.asm
; date:   2023-11-24
; author: J. McIntosh
; brief:  quadword (64-bits) memory move routine
%ifndef MEMMOVE64_ASM
%define MEMMOVE64_ASM
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
