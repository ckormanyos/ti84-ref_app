///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_util.h>
#include <startup/clock.h>

static void app_led_on   (void);
static void app_led_off  (void);
static void app_led_clr  (void);
static void app_led_delay(void);

static uint8_t app_led_current_tick;
static bool    app_led_exit_flag;

void main(void)
{
  app_util_init();

  clock_seconds_start();

  app_led_current_tick = clock_seconds_get();

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

  clock_seconds_stop();

  // Exit the Application and return to the home screen
  // using the JForceCmdNoChar function. See also page 16
  // in "TI-83 Plus System Routines", Third Release,
  // (Jan. 25, 2002).

  __asm__("rst 0x28\n" ".dw #0x4027\n");
}

static void app_led_on(void)
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");

  __asm__("ld a,#0x4F\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x4E\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
}

static void app_led_off(void)
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");

  __asm__("ld a,#0x4F\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x46\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x46\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
}

static void app_led_clr(void)
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");

  __asm__("ld a,#0x20\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x20\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x20\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
}

static void app_led_delay(void)
{
  uint8_t next_tick;

  do
  {
    next_tick         = clock_seconds_get();
    app_led_exit_flag = app_util_wants_exit();
  }
  while((next_tick == app_led_current_tick) && (!app_led_exit_flag));

  app_led_current_tick = next_tick;
}
