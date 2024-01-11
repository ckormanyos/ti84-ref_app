///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_lcd_util.h>

static void app_led_on (void);
static void app_led_off(void);
static void app_led_clr(void);

static bool app_led_is_on;

void app_led_init(void)
{
  app_lcd_util_init();
}

void app_led_task(void)
{
  app_led_clr();

  (!app_led_is_on) ? app_led_on() : app_led_off();

  app_led_is_on = (bool) (!app_led_is_on);
}

static void app_led_on(void)
{
  app_lcd_util_home1();
  app_lcd_util_puts("ON ");
}

static void app_led_off(void)
{
  app_lcd_util_home1();
  app_lcd_util_puts("OFF");
}

static void app_led_clr(void)
{
  app_lcd_util_home1();
  app_lcd_util_puts("   ");
}
