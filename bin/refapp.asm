;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.4.0 #14620 (MINGW64)
;--------------------------------------------------------
	.module app_main
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _os_schedule
	.globl _mcal_gpt_de_init
	.globl _mcal_gpt_init
	.globl _app_lcd_util_init
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:11: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:19: mcal_gpt_init();
	call	_mcal_gpt_init
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:22: app_lcd_util_init();
	call	_app_lcd_util_init
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:27: os_schedule();
	call	_os_schedule
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:30: mcal_gpt_de_init();
	call	_mcal_gpt_de_init
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:39: ASM("rst 0x28\n" ".dw #0x4027\n");
	rst	0x28
	.dw	#0x4027
;c:\users\ckorm\documents\ks\uc_software\boards\ti84-ref_app\src\app\app_main.c:40: }
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
