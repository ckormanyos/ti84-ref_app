///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_lcd_util.h>

#define NULL_PTR (void*) 0

static void app_lcd_util_putc(char c) ATTRIBUTE_NAKED;

void app_lcd_util_puts(const char* p_str)
{
  char c;

  while((p_str != NULL_PTR) && ((c = *p_str) != '\0'))
  {
    app_lcd_util_putc(c);

    ++p_str;
  }
}

void app_lcd_util_home1(void) ATTRIBUTE_NAKED
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x06\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");
  __asm__("ret\n");
}

void app_lcd_util_home2(void) ATTRIBUTE_NAKED
{
  __asm__("ld b,#0x03\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x06\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");
  __asm__("ret\n");
}

void app_lcd_util_init(void) ATTRIBUTE_NAKED
{
  __asm__("rst 0x28\n" ".dw #0x4540\n");
  __asm__("rst 0x28\n" ".dw #0x4558\n");
  __asm__("ret\n");
}

static void app_lcd_util_putc(char c) ATTRIBUTE_NAKED
{
  (void) c;

  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ret\n");
}
