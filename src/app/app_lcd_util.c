///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_lcd_util.h>

static void app_lcd_util_putc(char c) ATTRIBUTE_NAKED;

void app_lcd_util_puts(const char* p_str)
{
  char c;

  while((p_str != nullptr) && ((c = *p_str) != '\0'))
  {
    app_lcd_util_putc(c);

    ++p_str;
  }
}

// See also: https://wikiti.brandonw.net/index.php?title=Category:83Plus:Ports:By_Address
// and also: https://education.ti.com/html/eguides/discontinued/computer-software/EN/SDK-TI-83-System-Routines_EN.pdf

void app_lcd_util_row(const uint8_t row) ATTRIBUTE_NAKED
{
  (void) row;

  // curRow #0x844B

  __asm__("ld (#0x844B), a\n");
  __asm__("ret\n");
}

void app_lcd_util_col(const uint8_t col) ATTRIBUTE_NAKED
{
  (void) col;

  // curCol #0x844C

  __asm__("ld (#0x844C), a\n");
  __asm__("ret\n");
}

void app_lcd_util_init(void) ATTRIBUTE_NAKED
{
  // _ClrLCDFull       #0x4540
  // _HomeUp           #0x4558

  __asm__("rst 0x28\n" ".dw #0x4540\n");
  __asm__("rst 0x28\n" ".dw #0x4558\n");
  __asm__("ret\n");
}

static void app_lcd_util_putc(char c) ATTRIBUTE_NAKED
{
  (void) c;

  // _PutC             #0x4504

  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ret\n");
}
