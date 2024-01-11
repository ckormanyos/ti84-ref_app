///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <stdbool.h>

#include <app/app_lcd_util.h>

static bool app_hello_is_hello;

void app_hello_init(void)
{
}

void app_hello_task(void)
{
  app_lcd_util_row((uint8_t) UINT8_C(3));
  app_lcd_util_col((uint8_t) UINT8_C(6));
  app_lcd_util_puts("     ");
  app_lcd_util_col((uint8_t) UINT8_C(6));

  (!app_hello_is_hello) ? app_lcd_util_puts("hello") : app_lcd_util_puts("world");

  app_hello_is_hello = (bool) (!app_hello_is_hello);
}
