///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_led_util.h>
#include <mcal/mcal_gpt.h>

static void app_led_on   (void);
static void app_led_off  (void);
static void app_led_clr  (void);
static void app_led_delay(void);

static uint8_t app_led_current_tick;
static bool    app_led_exit_flag;

void main(void)
{
  app_led_util_init();

  mcal_gpt_init();

  app_led_current_tick = mcal_gpt_get_time_elapsed();

  for(;;)
  {
    app_led_clr();
    app_led_on();
    app_led_delay();

    if(app_led_exit_flag)
    {
      break;
    }

    app_led_clr();
    app_led_off();
    app_led_delay();

    if(app_led_exit_flag)
    {
      break;
    }
  }

  mcal_gpt_de_init();

  // Exit the Application and return to the home screen
  // using the JForceCmdNoChar function. See also page 16
  // in "TI-83 Plus System Routines", Third Release,
  // (Jan. 25, 2002).

  __asm__("rst 0x28\n" ".dw #0x4027\n");
}

static void app_led_on(void)
{
  app_led_util_home();
  app_led_util_putc('O');
  app_led_util_putc('N');
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

static void app_led_delay(void)
{
  uint8_t next_tick;

  do
  {
    next_tick         = mcal_gpt_get_time_elapsed();
    app_led_exit_flag = app_led_util_wants_exit();
  }
  while((next_tick == app_led_current_tick) && (!app_led_exit_flag));

  app_led_current_tick = next_tick;
}
