///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_lcd_util.h>

static bool app_led_is_on;

void app_led_task(void)
{
  app_lcd_util_row((uint8_t) UINT8_C(2));
  app_lcd_util_col((uint8_t) UINT8_C(6));
  app_lcd_util_puts("   ");
  app_lcd_util_col((uint8_t) UINT8_C(6));

  (!app_led_is_on) ? app_lcd_util_puts("ON ") : app_lcd_util_puts("OFF");

  app_led_is_on = (bool) (!app_led_is_on);
}
