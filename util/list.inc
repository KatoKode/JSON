%ifndef LIST_INC
%define LIST_INC
; file:   list.inc
; date:   2024-01-01
; author: J.McIntosh
; brief:  object list implementation
;-------------------------------------------------------------------------------
;
struc list
    .o_size         resq      1     ; size (in bytes) of one object
    .s_size         resq      1     ; slot size == o_size rounded up to nearest
                                    ; 8-byte boundary
    .iter           resq      1     ; list iterator
    .next           resq      1     ; points to next available slot, and
    .blkend   EQU     .next         ; end of data block
    .bufend         resq      1     ; points to the end of the buffer
    .buffer         resq      1     ; points to the buffer on the heap
endstruc
;
%endif
