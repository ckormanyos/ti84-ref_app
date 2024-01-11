///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <stdbool.h>

#include <app/app_lcd_util.h>

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
  app_lcd_util_home2();
  app_lcd_util_puts("hello");
}

static void app_hello_world(void)
{
  app_lcd_util_home2();
  app_lcd_util_puts("world");
}

static void app_hello_clear(void)
{
  app_lcd_util_home2();
  app_lcd_util_puts("     ");
}

