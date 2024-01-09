///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <stdbool.h>

#include <app/app_led_util.h>

static void app_hello_hello(void);
static void app_hello_world(void);
static void app_hello_clear(void);

static bool app_hello_is_hello;


void app_hello_init(void)
{
}

void app_hello_task(void)
{
  app_hello_clear();

  (!app_hello_is_hello) ? app_hello_hello() : app_hello_world();

  app_hello_is_hello = (bool) (!app_hello_is_hello);
}

static void app_hello_hello(void)
{
  app_led_util_home2();
  app_led_util_putc('h');
  app_led_util_putc('e');
  app_led_util_putc('l');
  app_led_util_putc('l');
  app_led_util_putc('o');
}

static void app_hello_world(void)
{
  app_led_util_home2();
  app_led_util_putc('w');
  app_led_util_putc('o');
  app_led_util_putc('r');
  app_led_util_putc('l');
  app_led_util_putc('d');
}

static void app_hello_clear(void)
{
  app_led_util_home2();
  app_led_util_putc(' ');
  app_led_util_putc(' ');
  app_led_util_putc(' ');
  app_led_util_putc(' ');
  app_led_util_putc(' ');
}

