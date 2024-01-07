;///////////////////////////////////////////////////////////////////////////////
;//  Copyright Christopher Kormanyos 2024.
;//  Distributed under The Unlicense
;//

; crt0.s - C-runtime startup

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

__clock:
  ld a,#2
  ret

.area _GSINIT
gsinit:
  .area _GSFINAL
  ld a, #0x0
  ret
