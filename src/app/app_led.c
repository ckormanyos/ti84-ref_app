///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_led_util.h>

static void app_led_on (void);
static void app_led_off(void);
static void app_led_clr(void);

static bool app_led_is_on;

void app_led_init(void)
{
  app_led_util_init();
}

void app_led_task(void)
{
  app_led_clr();

  if(!app_led_is_on)
  {
    app_led_on();
  }
  else
  {
    app_led_off();
  }

  app_led_is_on = (!app_led_is_on);
}

static void app_led_on(void)
{
  app_led_util_home();
  app_led_util_putc('O');
  app_led_util_putc('N');
  app_led_util_putc(' ');
}

static void app_led_off(void)
{
  app_led_util_home();
  app_led_util_putc('O');
  app_led_util_putc('F');
  app_led_util_putc('F');
}

static void app_led_clr(void)
{
  app_led_util_home();
  app_led_util_putc(' ');
  app_led_util_putc(' ');
  app_led_util_putc(' ');
}
