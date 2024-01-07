;///////////////////////////////////////////////////////////////////////////////
;//  Copyright Christopher Kormanyos 2024.
;//  Distributed under The Unlicense
;//

; crt0.s
; Perform C-runtime startup including static initialization (i.e., bss/data clear/init).

   .module crt
   .globl _main
   .area _HEADER (ABS)
   .org #0x9D93

   .dw #0x6DBB

   call gsinit
   jp _main
   .org 0x9D9B
   .area _CODE
   .area _GSINIT
   .area _GSFINAL
   .area _DATA
   .area _BSS
   .area _INITIALIZED
   .area _INITIALIZER

.area _GSINIT
gsinit:
  ; Default-initialized global variables.
  ld  bc, #l__DATA
  ld  a, b
  or  a, c
  jr  Z, zeroed_data
  ld  hl, #s__DATA
  ld  (hl), #0x00
  dec bc
  ld  a, b
  or  a, c
  jr  Z, zeroed_data
  ld  e, l
  ld  d, h
  inc de
  ldir

zeroed_data:
  ; Explicitly initialized global variables.

  ld bc, #l__INITIALIZER
  ld a, b
  or a, c
  jr Z, gsinit_next
  ld de, #s__INITIALIZED
  ld hl, #s__INITIALIZER
  ldir

gsinit_next:

  .area _GSFINAL
  ret
