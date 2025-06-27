%ifndef LIFO_INC
%define LIFO_INC
; file:   lifo.inc
; data:   2025-02-22
; author: J. McIntosh
; brief:  last-in-first-out (lifo) for 8-byte values
;-------------------------------------------------------------------------------
;
struc lifo
    .head:        resq    1     ; pointer to head of lifo
    .end:         resq    1     ; pointer to end of lifo buffer
    .buffer:      resq    1     ; pointer to lifo buffer
endstruc
;
;-------------------------------------------------------------------------------
%endif
